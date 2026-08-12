#include "stdafx.h"
#include "DownloadInfo.h"


CDownloadInfo::CDownloadInfo(void)
{
	m_hThread = NULL;
	m_pPageContent = NULL;
	m_nPageLength = 0;
	m_strMoudlePath = _T("");
	m_strDownloadUrl = _T("");
	m_strServer = _T("");
	m_strObject = _T("");
	m_strProtocolType = _T("");
	m_strContentDispositionFileName = _T("");
	m_nPort = 0;
	m_nWillDownloadStartPos = 0;
	m_nWillDownloadSize = -1;
	m_nDownloadedSize = 0;
	m_nTempSaveBytes = 0;
	m_bDownloadSuccess = FALSE;
	m_nIndex = -1;
	m_nThradCount = 0;
	m_bSupportResume = FALSE;
	m_pCallbackSaveDownloadInfoProc = NULL;
	m_wCallbackSaveDownloadInfoParam = NULL;
	m_pCurSingleDownloadInfo = NULL;
	m_nRetryTimes = 100;
	m_nSleepMilliSecond = 5 * 1000;
	m_nFileTotalSize = 0;
	m_hEvtEndModule = ::CreateEvent(NULL, TRUE, FALSE, NULL);
}

CDownloadInfo::~CDownloadInfo(void)
{
	ClearThreadHandle();
	if (m_pPageContent != NULL)
	{
		delete[] m_pPageContent;
		m_pPageContent = NULL;
	}
}

void CDownloadInfo::ClearDownloadInfo()
{
	ClearThreadHandle();
	m_nWillDownloadStartPos		= 0;
	m_nWillDownloadSize			= -1;
	m_nDownloadedSize			= 0;
	m_nTempSaveBytes			= 0;
	m_bDownloadSuccess			= FALSE;
}


void CDownloadInfo::ClearThreadHandle()
{
	CLOSE_HANDLE(m_hThread);
}


void CDownloadInfo::StopDownload()
{
	m_WnSocketClient.CancelBlockingCall();
	if (HANDLE_IS_VALID(m_hEvtEndModule))
	{
		::SetEvent(m_hEvtEndModule);
		if (::WaitForSingleObject(m_hThread, 30 * 1000) == WAIT_TIMEOUT)
		{
			::TerminateThread(m_hThread, 0);
		}
		CLOSE_HANDLE (m_hEvtEndModule);
		m_hEvtEndModule = NULL;
		ClearThreadHandle();
	}
}

BOOL CDownloadInfo::Connect()
{
	if (!HANDLE_IS_VALID(m_hEvtEndModule))
	{
		return FALSE;
	}
	if ( m_strServer.IsEmpty() )
	{
		return FALSE;
	}
	m_WnSocketClient.SetEventOfEndModule(m_hEvtEndModule);
	m_WnSocketClient.m_nIndex = m_nIndex;
	// 连接到服务器
	if (!m_WnSocketClient.Connect(m_strServer, m_nPort))
	{
		return FALSE;
	}
	return TRUE;
}


int CDownloadInfo::GetRemoteSitePro()
{
	return 1;
}

BOOL CDownloadInfo::IsSupportResume()
{
	return m_bSupportResume; 
}

HANDLE CDownloadInfo::GetThreadHandle()
{
	return m_hThread;
}

BOOL CDownloadInfo::OpenFileForSave()
{
	BOOL bFlag = OpenFileForContent();
	if (!bFlag)
	{
		return FALSE;
	}
	//
	bFlag = OpenFileForThread();
	if (!bFlag)
	{
		return FALSE;
	}
	//
	this->SaveThreadDataToFile();
	return TRUE;
}

// 打开文件要保存内容的操作（m_fileForContent）
BOOL CDownloadInfo::OpenFileForContent()
{
	if (HANDLE_IS_VALID(m_fileForContent.m_hFile))
	{
		m_fileForContent.Close();
	}
	BOOL bReturn = FALSE;
	UINT uOpenFlags = CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::typeBinary | CFile::shareDenyNone;
	BOOL bFlag = m_fileForContent.Open( m_strSaveFileName, uOpenFlags);
	if (!bFlag)
	{
		return FALSE;
	}
	int nWillDownloadStartPos = GetWillDownloadStartPos();
	nWillDownloadStartPos += GetDownloadedSize();
	int nSeekReturn = m_fileForContent.Seek(nWillDownloadStartPos, CFile::begin);
	if (nSeekReturn == nWillDownloadStartPos)
	{
		bReturn = TRUE;
	}
	return bReturn;
}

// 打开文件要保存线程的操作（m_fileForThread）
BOOL CDownloadInfo::OpenFileForThread()
{
	if ( HANDLE_IS_VALID(m_fileForThread.m_hFile))
	{
		m_fileForThread.Close ();
	}
	BOOL bReturn = FALSE;
	UINT uOpenFlags = CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::typeBinary | CFile::shareDenyNone;
	BOOL bFlag = m_fileForThread.Open( m_strSaveFileName, uOpenFlags);
	if (!bFlag)
	{
		return FALSE;
	}
	int nSingleDownloadInfoSize = sizeof(TSingleDownloadInfo);
	int nFileLength = m_fileForThread.GetLength();
	int nThreadExtraSize = m_nThradCount * nSingleDownloadInfoSize + sizeof(TBaseDownloadInfo);
	int nCurThradFallPos = nThreadExtraSize - m_nIndex * nSingleDownloadInfoSize;
	int nCurThreadBeginSeek = nFileLength - nCurThradFallPos;
	int nSeekReturn = m_fileForThread.Seek(-nCurThradFallPos, CFile::end);
	if (nSeekReturn == nCurThreadBeginSeek)
	{
		bReturn = TRUE;
	}
	return bReturn;
}

BOOL CDownloadInfo::DownloadOnce()
{
	this->WriteAppointLog(_T("CDownloadInfo::DownloadOnce Start"));
	// 打开文件
	BOOL bFlag = OpenFileForSave();
	if (!bFlag)
	{
		this->WriteAppointLog(_T("CDownloadInfo::DownloadOnce OpenFileForSave FALSE"));
		return FALSE;
	}
	// 是否已经连接到服务器
	BOOL bConnected = m_WnSocketClient.IsConnected();
	if (bConnected)
	{
		this->WriteAppointLog(_T("CDownloadInfo::DownloadOnce bConnected TRUE"));
		return TRUE;	
	}
	// 连接到服务器
	BOOL bConnectFlag = Connect();
	if (!bConnectFlag)
	{
		this->WriteAppointLog(_T("CDownloadInfo::DownloadOnce bConnectFlag FALSE"));
		return FALSE;
	}
	this->WriteAppointLog(_T("CDownloadInfo::DownloadOnce End"));
	return TRUE;
}


// 下载页面内容
BOOL CDownloadInfo::DownloadPageContent()
{
	// 是否已经连接到服务器
	BOOL bConnected = m_WnSocketClient.IsConnected();
	if (bConnected)
	{
		this->WriteAppointLog(_T("CDownloadInfo::DownloadPageContent bConnected TRUE"));
		return TRUE;	
	}
	// 连接到服务器
	BOOL bConnectFlag = Connect();
	if (!bConnectFlag)
	{
		this->WriteAppointLog(_T("CDownloadInfo::DownloadPageContent bConnectFlag FALSE"));
		return FALSE;
	}
	this->WriteAppointLog(_T("CDownloadInfo::DownloadPageContent End"));
	return TRUE;
}

/**********************************************************************
* 函数名称： RecvDataAndSaveToFile
* 功能描述： 从服务器接收数据并保存到文件中
* 输入参数：
* <param name="pWriteBuffer">要写入文件的信息</param>
* <param name="nWriteSize">要写入文件的大小</param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
int CDownloadInfo::SaveDataToFile(char * pWriteBuffer, int nWriteSize)
{
	this->WriteAppointLog(_T("CDownloadInfo::SaveDataToFile Start[nWriteSize:%d]"), nWriteSize);
	if (pWriteBuffer == NULL)
	{
		return -1;
	}
	if (nWriteSize < 0)
	{
		return -1;
	}
	int nDownloadedSize = -1;
	m_fileForContent.Write(pWriteBuffer, nWriteSize);
	//
	nDownloadedSize = GetDownloadedSize();
	nDownloadedSize += nWriteSize;
	SetDownloadedSize(nDownloadedSize);
	if (m_pCallbackSaveDownloadInfoProc != NULL)
	{
		m_pCallbackSaveDownloadInfoProc(m_nIndex, nDownloadedSize, nWriteSize, m_wCallbackSaveDownloadInfoParam);
	}
	this->SaveThreadDataToFile();
	this->WriteAppointLog(_T("CDownloadInfo::SaveDataToFile End"));
	return nDownloadedSize;
}


/**********************************************************************
* 函数名称： SaveThreadDataToFile
* 功能描述： 保存线程数据到文件
* 输入参数：
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
void CDownloadInfo::SaveThreadDataToFile()
{
	if (m_pCurSingleDownloadInfo == NULL)
	{
		return;
	}
	int nSingleDownloadInfoSize = sizeof(TSingleDownloadInfo);
	m_fileForThread.Write(m_pCurSingleDownloadInfo, nSingleDownloadInfoSize);
	m_fileForThread.Seek(-nSingleDownloadInfoSize, CFile::current);
	this->WriteAppointLog(_T("CDownloadInfo::SaveThreadDataToFile[nWillDownloadStartPos:%d][nWillDownloadSize:%d][nDownloadedSize:%d]"), m_pCurSingleDownloadInfo->nWillDownloadStartPos, m_pCurSingleDownloadInfo->nWillDownloadSize, m_pCurSingleDownloadInfo->nDownloadedSize);
}


// 获取页面内容
CHAR* CDownloadInfo::GetPageContent()
{
	return m_pPageContent;
}


// 获取页面长度
INT CDownloadInfo::GetPageLength()
{
	return m_nPageLength;
}



/**********************************************************************
* 函数名称： RecvDataAndSaveToFile
* 功能描述： 从服务器接收数据并保存到文件中
* 输入参数：
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CDownloadInfo::RecvDataAndSaveToFile(CSocketClient & myWnSocketClient,char * szTailData, int nTailSize)
{
	this->WriteAppointLog(_T("CDownloadInfo::RecvDataAndSaveToFile Start"));
	int nDownloadedSize = GetDownloadedSize();
	if (szTailData && nTailSize > 0)
	{
		nDownloadedSize = SaveDataToFile(szTailData, nTailSize);
		if ( nDownloadedSize < 0 )
		{
			this->WriteAppointLog(_T("CDownloadInfo::RecvDataAndSaveToFile nDownloadedSize < 0"));
			return FALSE;
		}
	}

	char szRecvBuf[MAX_BUFFER_SIZE] = {0};
	char *szTempSaveBuf = new char[TEMP_SAVE_BUFFER_SIZE];
	if (!szTempSaveBuf )
	{
		this->WriteAppointLog(_T("CDownloadInfo::RecvDataAndSaveToFile szTempSaveBuf is null"));
		return FALSE;
	}
	m_nTempSaveBytes = 0;
	while ( TRUE )
	{
		BOOL bDownloadFinished = FALSE;
		int nReadSize = 0;
		int nTempSaveBytes = GetTempSaveBytes();
		// 保存在文件中的字节数加上临时缓冲中的字节数就是总共接收到字节数
		int nRecvTotalBytes = nDownloadedSize + nTempSaveBytes;
		int nWillDownloadSize = GetWillDownloadSize ();
		if	(
				// 从字节数判断，本次下载已经完成了。
				( nWillDownloadSize > 0 && nRecvTotalBytes >= nWillDownloadSize )
				||
				// 模块结束事件有信号，要结束了。
				( ::WaitForSingleObject ( m_hEvtEndModule, 1 ) == WAIT_OBJECT_0 )
			)
		{
			this->WriteAppointLog(_T("CDownloadInfo::RecvDataAndSaveToFile::DownloadFinished(nWillDownloadSize:%d,nRecvTotalBytes:%d)"), nWillDownloadSize, nRecvTotalBytes);
			bDownloadFinished = TRUE;
		}
		else
		{
			int nRecvBytesThisTimes = sizeof(szRecvBuf);
			if (nWillDownloadSize > 0)
			{
				nRecvBytesThisTimes = nWillDownloadSize - nRecvTotalBytes;
			}
			ASSERT ( nRecvBytesThisTimes >= 0 );
			//
			nRecvBytesThisTimes = MIN(nRecvBytesThisTimes, sizeof(szRecvBuf));
			this->WriteAppointLog(_T("CDownloadInfo::RecvDataAndSaveToFile::Receive Start"));
			nReadSize = myWnSocketClient.Receive(szRecvBuf, nRecvBytesThisTimes);
			this->WriteAppointLog(_T("CDownloadInfo::RecvDataAndSaveToFile::Receive End(nReadSize:%d)"), nReadSize);
			// 读不到数据了，所以认为下载已经完成
			if (nReadSize == 0)
			{
				if (nWillDownloadSize <= 0)
				{
					bDownloadFinished = TRUE;
				}
			}
			else if (nReadSize < 0)
			{
				// 网络链接失败了
				break;
			}
		}

		// 先将数据保存到临时缓冲中
		if (nReadSize > 0)
		{
			nReadSize = MIN(nReadSize, TEMP_SAVE_BUFFER_SIZE - nTempSaveBytes);
			memcpy (szTempSaveBuf+nTempSaveBytes, szRecvBuf, nReadSize);
			nTempSaveBytes += nReadSize;
			ASSERT ( nTempSaveBytes < TEMP_SAVE_BUFFER_SIZE );
		}
		// 当下载已完成或者收到的数据超过一定数量时才保存到文件中
		if (bDownloadFinished || nTempSaveBytes >= WRITE_TEMP_SAVE_MIN_BYTES)
		{
			this->WriteAppointLog(_T("CDownloadInfo::RecvDataAndSaveToFile SaveDataToFile (bDownloadFinished:%d) (nTempSaveBytes is %d)"), bDownloadFinished, nTempSaveBytes);
			// 保存文件失败，下载也应该终止
			nDownloadedSize = SaveDataToFile( szTempSaveBuf, nTempSaveBytes);
			if ( nDownloadedSize < 0 )
			{
				break;
			}
			nTempSaveBytes = 0;
		}
		SetTempSaveBytes(nTempSaveBytes);

		if (bDownloadFinished)
		{
			break;
		}
	}

	if (szTempSaveBuf != NULL)
	{
		delete[] szTempSaveBuf;
		szTempSaveBuf = NULL;
	}
	BOOL bRes = FALSE;
	int nWillDownloadSize = GetWillDownloadSize();
	if ( nWillDownloadSize != -1 )
	{
		if (nDownloadedSize >= nWillDownloadSize)
		{
			bRes = TRUE;
		}
	}
	else if ( nDownloadedSize > 0 )
	{
		bRes = TRUE;
	}
	this->WriteAppointLog(_T("CDownloadInfo::RecvDataAndSaveToFile End"));
	return bRes;
}

// 重试多少次
int g_nRetryTimes = 100;

BOOL CDownloadInfo::GetRemoteSiteInfo()
{
	int nReturnStatus = -1;
	for ( int i = 0; i < m_nRetryTimes; i++ )
	{
		AfxSocketInit();
		nReturnStatus = GetRemoteSitePro(); 
		if (nReturnStatus == 1)
		{
			m_WnSocketClient.Disconnect();
			return TRUE;
		}
		else if (nReturnStatus == 0)
		{
			SLEEP_RETURN_Down(m_nSleepMilliSecond);
		}
		else
		{
			break;
		}
	}
	m_WnSocketClient.Disconnect();
	return FALSE;
}


// 访问Php获取网页内容
BOOL CDownloadInfo::GetBrowsePageContent()
{
	return TRUE;
}

CString CDownloadInfo::GetOneLine(CString & str)
{
	int nPos = str.Find(_T("\r\n"), 0);
	if ( nPos < 0 ) 
	{
		return _T("");
	}
	CString strOneLine = str.Left (nPos);
	str = str.Mid (nPos + 2);
	return strOneLine;
}


//
// 下载结束
//
BOOL CDownloadInfo::DownloadEnd(BOOL bRes)
{
	m_bDownloadSuccess = bRes;
	m_WnSocketClient.Disconnect();
	if (HANDLE_IS_VALID(m_fileForContent.m_hFile))
	{
		m_fileForContent.Close();
	}
	if (HANDLE_IS_VALID(m_fileForThread.m_hFile))
	{
		m_fileForThread.Close();
	}
	if (bRes)
	{
		this->WriteDebugLog(_T("[%d]下载完成"), m_nIndex);
	}
	else
	{
		this->WriteDebugLog(_T("[%d]下载失败"), m_nIndex);
	}
	return bRes;
}

int CDownloadInfo::GetWillDownloadStartPos() 
{
	return m_nWillDownloadStartPos; 
}


void CDownloadInfo::SetWillDownloadSize(int nWillDownloadSize)
{
	m_csWillDownloadSize.Lock ();
	m_nWillDownloadSize = nWillDownloadSize;
	m_csWillDownloadSize.Unlock ();
	//DownloadNotify ( m_nIndex, NOTIFY_TYPE_WILL_DOWNLOAD_SIZE, (LPVOID)m_nWillDownloadSize, m_pDownloadMTR );
}

int CDownloadInfo::GetWillDownloadSize()
{
	int nWillDownloadSize = 0;
	m_csWillDownloadSize.Lock ();
	nWillDownloadSize = m_nWillDownloadSize;
	m_csWillDownloadSize.Unlock ();
	return nWillDownloadSize;
}

void CDownloadInfo::SetDownloadedSize(int nDownloadedSize)
{
	m_csDownloadedSize.Lock();
	m_nDownloadedSize = nDownloadedSize;
	m_csDownloadedSize.Unlock();
	if (m_pCallbackSaveDownloadInfoProc != NULL)
	{
		m_pCallbackDownloadProgressInfoProc(m_pCallbackDownloadProgressInfoParam);
	};
}


int CDownloadInfo::GetDownloadedSize()
{
	int nDownloadedSize = 0;
	m_csDownloadedSize.Lock();
	nDownloadedSize = m_nDownloadedSize;
	m_csDownloadedSize.Unlock();
	return nDownloadedSize;
}


void CDownloadInfo::SetTempSaveBytes(int nTempSaveBytes)
{
	m_csTempSaveBytes.Lock();
	m_nTempSaveBytes = nTempSaveBytes;
	m_csTempSaveBytes.Unlock();
}

int CDownloadInfo::GetTempSaveBytes()
{
	int nTempSaveBytes = 0;
	m_csTempSaveBytes.Lock();
	nTempSaveBytes = m_nTempSaveBytes;
	m_csTempSaveBytes.Unlock();
	return nTempSaveBytes;
}

// 获取尚未下载的字节数，写到文件中的和临时缓冲里的都算是已经下载的
int CDownloadInfo::GetUnDownloadBytes()
{
	// 总共需要下载的字节数减去已经下载的字节数
	int nWillDownloadSize = GetWillDownloadSize();
	int nDownloadedSize = GetDownloadedSize();
	int nTempSaveBytes = GetTempSaveBytes();
	return nWillDownloadSize - (nDownloadedSize + nTempSaveBytes);
}

// 获取是否下载成功
BOOL CDownloadInfo::IsDownloadSuccess() 
{
	return m_bDownloadSuccess; 
}
	

int CDownloadInfo::GetFileTotalSize()
{
	return m_nFileTotalSize; 
}

// 线程是否正在运行
BOOL CDownloadInfo::IsThreadRunning()
{
	if (!HANDLE_IS_VALID(m_hThread))
	{
		return FALSE;
	}
	return (::WaitForSingleObject(m_hThread, 0) != WAIT_OBJECT_0);
}

time_t CDownloadInfo::GetTimeLastModified()
{ 
	return m_TimeLastModified.GetTime();
}


// 设置当前的指向下载信息
void CDownloadInfo::SetCurSingleDownloadInfo(TSingleDownloadInfo* pCurSingleDownloadInfo)
{
	m_pCurSingleDownloadInfo = pCurSingleDownloadInfo;
}

CString CDownloadInfo::GetRefererFromURL()
{
	int nPos = m_strDownloadUrl.ReverseFind(_T('/'));
	if (nPos < 0)
	{
		return _T("");
	}
	return m_strDownloadUrl.Left(nPos);
}

BOOL CDownloadInfo::SetDownloadUrl(LPCTSTR strDownloadUrl)
{
	if (strDownloadUrl == NULL) 
	{
		return FALSE;
	}
	m_strDownloadUrl = strDownloadUrl;
	// 检验要下载的URL是否为空
	m_strDownloadUrl.TrimLeft();
	m_strDownloadUrl.TrimRight();
	if( m_strDownloadUrl.IsEmpty())
	{
		return FALSE;
	}
	// 检验要下载的URL是否有效
	if (!ParseURL(m_strDownloadUrl, m_strServer, m_strObject, m_nPort, m_strProtocolType))
	{
		return FALSE;
	}

	return TRUE;
}


//
// 设置保存下载信息回调函数
//
void CDownloadInfo::SetCallbackSaveDownloadInfo(FunCallbackSaveDownloadInfo pCallbackSaveDownloadInfoProc, WPARAM wParam)
{
	m_pCallbackSaveDownloadInfoProc = pCallbackSaveDownloadInfoProc;
	m_wCallbackSaveDownloadInfoParam = wParam;
}

//
// 设置保存下载进度回调函数
//
void CDownloadInfo::SetCallbackDownloadProgressInfo(FunCallbackDownloadProgressInfo pCallbackDownloadProgressInfoProc, WPARAM wParam)
{
	m_pCallbackDownloadProgressInfoProc = pCallbackDownloadProgressInfoProc;
	m_pCallbackDownloadProgressInfoParam = wParam;
}


void CDownloadInfo::SetSaveFileName(LPCTSTR strSaveFileName)
{
	m_strSaveFileName = strSaveFileName;
}


// 设置模块的路径
void CDownloadInfo::SetMoudlePath(LPCTSTR strMoudlePath)
{
	m_strMoudlePath = strMoudlePath;	
}

// 从URL里面拆分出Server、Object、协议类型等信息，其中 Object 里的值是区分大小写的，否则有些网站可能会下载不了
BOOL CDownloadInfo::ParseURL(LPCTSTR lpszURL, CString & strServer, CString & strObject, int & nPort, CString & strProtocolType)
{
	if (lpszURL == NULL)
	{
		return FALSE;
	}
	int nTextLen = (int)_tcslen(lpszURL);
	if ( nTextLen < 1 ) 
	{
		return FALSE;
	}
	CString strLowerUrl(lpszURL);
	strLowerUrl.TrimLeft();
	strLowerUrl.TrimRight();
	strLowerUrl.Replace (_T("\\"), _T("/"));
	CString strTempUrl = strLowerUrl;
	strLowerUrl.MakeLower ();
	
	// 清除数据
	strServer = _T("");
	strObject = _T("");
	nPort	  = 0;

	int nPos = strLowerUrl.Find(_T("://"));
	if( nPos == -1 )
	{
		strLowerUrl.Insert(0, _T("http://"));
		strTempUrl.Insert (0, _T("http://"));
		nPos = 4;
	}
	strProtocolType = strLowerUrl.Left(nPos);
	//
	strLowerUrl = strLowerUrl.Mid(strProtocolType.GetLength() + 3);
	strTempUrl = strTempUrl.Mid(strProtocolType.GetLength() + 3);
	nPos = strLowerUrl.Find(_T('/'));
	if (nPos == -1)
	{
		return FALSE;
	}
	strObject = strTempUrl.Mid(nPos);
	CString strServerAndPort = strLowerUrl.Left(nPos);

	// 查找是否有端口号，站点服务器域名一般用小写
	nPos = strServerAndPort.Find(_T(":"));
	if (nPos == -1)
	{
		strServer	= strServerAndPort;
		nPort		= DEFAULT_HTTP_PORT;
		if (strProtocolType == _T("ftp"))
		{
			nPort	= DEFAULT_FTP_PORT;
		}
	}
	else
	{
		strServer = strServerAndPort.Left( nPos );
		strServerAndPort	  = strServerAndPort.Mid( nPos+1 );
		nPort	  = (USHORT)_ttoi((LPCTSTR)strServerAndPort);
	}
	return TRUE;
}

// 创建线程下载文件
BOOL CDownloadInfo::DoRunDownloadFile(int nWillDownloadStartPos, int nWillDownloadSize, int nDownloadedSize)
{
	this->WriteDebugLog(_T("[%d]重新下载[nWillDownloadStartPos:%d][nWillDownloadSize:%d][nDownloadedSize:%d]"), m_nIndex, nWillDownloadStartPos, nWillDownloadSize, nDownloadedSize);
	if (nWillDownloadSize == 0)
	{
		return TRUE;
	}
	// 设置下载参数
	m_nWillDownloadStartPos	= nWillDownloadStartPos;
	SetWillDownloadSize(nWillDownloadSize);
	if (m_nFileTotalSize > 0 && GetWillDownloadSize() > m_nFileTotalSize)
	{
		SetWillDownloadSize(m_nFileTotalSize);
	}
	SetDownloadedSize(nDownloadedSize);

	// 创建一个下载线程
	DWORD dwThreadID = 0;
	m_hThread = CreateThread(NULL, 0, DoDownloadThread, LPVOID(this), 0, &dwThreadID);
	if ((m_hThread == NULL) || (m_hThread == INVALID_HANDLE_VALUE))
	{
		return FALSE;
	}
	return TRUE;
}

// 创建线程下载文件
BOOL CDownloadInfo::DoRequestPageContent(int nWillDownloadSize, int nDownloadedSize)
{
	if (nWillDownloadSize == 0)
	{
		return TRUE;
	}
	// 设置下载参数
	m_nWillDownloadStartPos	= 0;
	SetWillDownloadSize(nWillDownloadSize);
	if (m_nFileTotalSize > 0 && GetWillDownloadSize() > m_nFileTotalSize)
	{
		SetWillDownloadSize(m_nFileTotalSize);
	}
	SetDownloadedSize(nDownloadedSize);

	// 创建一个下载线程
	DWORD dwThreadID = 0;
	m_hThread = CreateThread(NULL, 0, DoRequestPageContentThread, LPVOID(this), 0, &dwThreadID);
	if ((m_hThread == NULL) || (m_hThread == INVALID_HANDLE_VALUE))
	{
		return FALSE;
	}
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	int nResult = (int)::WaitForSingleObject(m_hThread, INFINITE) - WAIT_OBJECT_0;
	return TRUE;
}


// 下载任务的线程函数
DWORD WINAPI CDownloadInfo::DoDownloadThread(LPVOID lpParameter)
{
	CDownloadInfo *pWnDownloadInfo = (CDownloadInfo*)lpParameter;
	return pWnDownloadInfo->DoDownloadProcedure();
}

// 下载任务的线程函数
DWORD WINAPI CDownloadInfo::DoRequestPageContentThread(LPVOID lpParameter)
{
	CDownloadInfo *pWnDownloadInfo = (CDownloadInfo*)lpParameter;
	return pWnDownloadInfo->DoRequestPageContentProcedure();
}

// 下载任务的过程函数
DWORD CDownloadInfo::DoDownloadProcedure(void)
{
	this->WriteAppointLog(_T("CDownloadInfo::DoDownloadProcedure Start"));
	BOOL bReturn = FALSE;
	for ( int i = 0; i < g_nRetryTimes; i++ )
	{
		AfxSocketInit();
		if (DownloadOnce())
		{
			bReturn = TRUE;
			break;
		}
		this->WriteAppointLog(_T("DoDownloadProcedure DownloadOnce(%d)"), i);
		SLEEP_RETURN_Down(5 * 1000);
	}
	DownloadEnd( bReturn );
	this->WriteAppointLog(_T("CDownloadInfo::DoDownloadProcedure End"));
	return 1;
}


// 下载任务的过程函数
DWORD CDownloadInfo::DoRequestPageContentProcedure(void)
{
	this->WriteAppointLog(_T("CDownloadInfo::DoRequestPageContentProcedure Start"));
	BOOL bReturn = FALSE;
	for ( int i = 0; i < g_nRetryTimes; i++ )
	{
		AfxSocketInit();
		if (DownloadPageContent())
		{
			bReturn = TRUE;
			break;
		}
		this->WriteAppointLog(_T("CDownloadInfo::DoRequestPageContentProcedure DownloadOnce(%d)"), i);
		SLEEP_RETURN_Down(5 * 1000);
	}
	DownloadEnd( bReturn );
	this->WriteAppointLog(_T("CDownloadInfo::DoRequestPageContentProcedure End"));
	return 1;
}


// 暂停下载的线程
BOOL CDownloadInfo::DoRunSuspendThread(void)
{
	DWORD dwReturn = SuspendThread(m_hThread);
	if (dwReturn == 0xFFFFFFFF)
	{
		return FALSE;
	}
	return TRUE;
}

// 恢复下载的线程
BOOL CDownloadInfo::DoRunResumeThread(void)
{
	DWORD dwReturn = ResumeThread(m_hThread);
	if (dwReturn == 0xFFFFFFFF)
	{
		return FALSE;
	}
	return TRUE;
}

// 终结下载的线程
void CDownloadInfo::DoRunTerminateThread(void)
{
	if (m_hThread != NULL)
	{
		DWORD dwExitCode = 0;
		GetExitCodeThread(m_hThread, &dwExitCode); 
		TerminateThread(m_hThread, dwExitCode);
		m_hThread = NULL;
	}
	ClearDownloadInfo();
	if (HANDLE_IS_VALID(m_fileForContent.m_hFile))
	{
		m_fileForContent.Close();
	}
	if (HANDLE_IS_VALID(m_fileForThread.m_hFile))
	{
		m_fileForThread.Close();
	}
}

// 设置循环下载次数
void CDownloadInfo::SetRetryTimes(int nRetryTimes)
{
	m_nRetryTimes = nRetryTimes;
}

// 设置循环下载暂停时间
void CDownloadInfo::SetSleepMilliSecond(int nSleepMilliSecond)
{
	m_nSleepMilliSecond = nSleepMilliSecond;
}


// 写入调试日志
void CDownloadInfo::WriteDebugLog(TCHAR * strMsg, ...)
{
#ifndef _DEBUG
	return;
#endif
	int nMsgMaxLen = 500;
	TCHAR szLog[1000] = {'\0'};
	TCHAR szMsg[500] = {'\0'};
	TCHAR szLogFile[MAX_PATH];
	time_t theCurrentTime = time(NULL);
	tm *pThisTime = localtime(&theCurrentTime);
	_stprintf(szLogFile, _T("%slog_%d.txt"), m_strMoudlePath.GetBuffer(), m_nIndex);
	va_list         list;               // 可变参数指针
	// 格式化组合字串
	va_start(list, strMsg);
	_vsntprintf(szMsg, nMsgMaxLen - 1, strMsg, list);
	szMsg[nMsgMaxLen - 1] = 0;
	_stprintf
		(
		szLog, 
		_T("[%d-%d-%d %d-%d-%d]: %s"), 
		pThisTime->tm_year + 1900,
		pThisTime->tm_mon + 1,
		pThisTime->tm_mday,
		pThisTime->tm_hour,
		pThisTime->tm_min,
		pThisTime->tm_sec,	
		szMsg
		);
	IDownloadInfoEvent *pEventDelegate(NULL);
	TVectorRegContainer::iterator iter = m_vectorRegContainer.begin();
	TVectorRegContainer::iterator iEnd = m_vectorRegContainer.end();
	for (; iter != iEnd; ++iter) {
		if (NULL == *iter) {
			continue ;
		}
		pEventDelegate = *iter;
		pEventDelegate->WriteDebugLog(szMsg);
	}
}

// 写入调试日志
void CDownloadInfo::WriteAppointLog(TCHAR * strMsg, ...)
{
	return;
	m_csLog.Lock();
	int nMsgMaxLen = 500;
	FILE * pFile;
	TCHAR szLog[1000] = {'\0'};
	TCHAR szMsg[1000] = {'\0'};
	TCHAR szLogFile[MAX_PATH];
	time_t theCurrentTime = time(NULL);
	tm *pThisTime = localtime(&theCurrentTime);
	_stprintf(szLogFile, _T("%slog_%d.txt"), m_strMoudlePath.GetBuffer(), m_nIndex);
	va_list         list;               // 可变参数指针
	// 格式化组合字串
	va_start(list, strMsg);
	_vsntprintf(szMsg, nMsgMaxLen - 1, strMsg, list);
	szMsg[nMsgMaxLen - 1] = 0;
	_stprintf
		(
		szLog, 
		_T("[%d-%d-%d %d-%d-%d]: %s"), 
		pThisTime->tm_year + 1900,
		pThisTime->tm_mon + 1,
		pThisTime->tm_mday,
		pThisTime->tm_hour,
		pThisTime->tm_min,
		pThisTime->tm_sec,	
		szMsg
		);
	BOOL bFind = FALSE;
	if (PathFileExists(szLogFile))
	{
		bFind = TRUE;
	}
	if ((pFile = _tfopen(szLogFile, _T("a+b"))) != NULL)
	{
		if (!bFind)
		{
			WORD wUnicode = 0xFEFF;
			fwrite(&wUnicode, 1, 2, pFile);
		}
		int nTextLen = (int)_tcslen(szLog);
		fwrite(szLog, 1, nTextLen * 2, pFile);
		WORD wLine = 0x000D;
		fwrite(&wLine, 1, 2, pFile);
		wLine = 0x000A;
		fwrite(&wLine, 1, 2, pFile);
		fclose(pFile);
	}
	m_csLog.Unlock();
}