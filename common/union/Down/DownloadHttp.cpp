#include "stdafx.h"
#include "DownloadHttp.h"

CDownloadHttp::CDownloadHttp(void)
{
	m_pPageContent = NULL;
}

CDownloadHttp::~CDownloadHttp(void)
{
	if ( m_pPageContent != NULL)
	{
		delete[] m_pPageContent;
		m_pPageContent = NULL;
	}
}


int CDownloadHttp::RequestHttpData(BOOL bGet, char * szTailData, int * pnTailSize)
{
	int nTailSizeTemp = 0;
	BOOL bRetryRequest = TRUE;
	BOOL bFlag = FALSE;
	while (bRetryRequest)
	{
		CString strRequest = GetRequestStr(bGet);
		CString strResponse = _T("");
		nTailSizeTemp = pnTailSize ? (*pnTailSize) : 0;
		bFlag = SendRequest(strRequest, strResponse, szTailData, &nTailSizeTemp);
		if (!bFlag)
		{
			// 没有请求到数据，需要重新请求
			return 0;
		}
		CString strOldReferer = m_strReferer;
		CString strOldDownloadUrl = m_strDownloadUrl;
		CString strOldServer = m_strServer;
		CString strOldObject = m_strObject;
		int nOldPort = m_nPort;
		CString strOldProtocolType = m_strProtocolType;
		bFlag = ParseResponseString(strResponse, bRetryRequest);
		if (!bFlag)
		{
			// 可能是发生页面错误（如：404错误）
			return -1;
			/*if (!m_strDownloadCookies.IsEmpty())
			{
				m_strDownloadCookies.Empty();
				return FALSE;
			}
			m_strReferer = strOldReferer;
			m_strDownloadUrl = strOldDownloadUrl;
			m_strServer = strOldServer;
			m_strObject = strOldObject;
			m_nPort = nOldPort;
			m_strProtocolType = strOldProtocolType;
			m_strDownloadCookies = "Flag=UUIISPoweredByUUSoft";
			bRetryRequest = TRUE;*/
		}
	}
	if (pnTailSize)
	{
		*pnTailSize = nTailSizeTemp;
	}
	return 1;
}


//
// 获取远程站点信息，如：是否支持断点续传、要下载的文件大小和创建时间等
//
int CDownloadHttp::GetRemoteSitePro()
{
	int nReturnStatus = CDownloadInfo::GetRemoteSitePro();
	if (nReturnStatus == -1)
	{
		return -1;
	}
	nReturnStatus = RequestHttpData(TRUE);
	if (nReturnStatus == -1)
	{
		return -1;
	}
	return nReturnStatus;
}


BOOL CDownloadHttp::DownloadOnce()
{
	this->WriteAppointLog(_T("CDownloadHttp::DownloadOnce Start"));
	BOOL bReturn = FALSE;
	// 本次应该下载的字节数
	int nWillDownloadSize = GetWillDownloadSize();
	// 已下载字节数
	int nDownloadedSize = GetDownloadedSize();
	if ((nWillDownloadSize > 0) && (nDownloadedSize >= nWillDownloadSize))
	{
		DownloadEnd(TRUE);
		this->WriteAppointLog(_T("CDownloadHttp::DownloadOnce CDownloadInfo::nDownloadedSize >= nWillDownloadSize Is TRUE"));
		return TRUE;
	}
	if (!CDownloadInfo::DownloadOnce())
	{
		DownloadEnd(FALSE);
		this->WriteAppointLog(_T("CDownloadHttp::DownloadOnce CDownloadInfo::DownloadOnce Is FALSE"));
		return FALSE;
	}
	char szTailData[MAX_BUFFER_SIZE] = {'0'};
	int nTailSize = sizeof(szTailData);
	if (!RequestHttpData(TRUE, szTailData, &nTailSize))
	{
		DownloadEnd(FALSE);
		this->WriteAppointLog(_T("CDownloadHttp::DownloadOnce RequestHttpData Is FALSE"));
		return FALSE;
	}
	// 从HTTP服务器中读取数据，并保存到文件中
	bReturn = RecvDataAndSaveToFile(m_WnSocketClient, szTailData, nTailSize);
	DownloadEnd(bReturn);
	this->WriteAppointLog(_T("CDownloadHttp::DownloadOnce End"));
	return bReturn;
}

// 下载页面内容
BOOL CDownloadHttp::DownloadPageContent()
{
	this->WriteAppointLog(_T("CDownloadHttp::DownloadOnce Start"));
	BOOL bReturn = FALSE;
	// 本次应该下载的字节数
	int nWillDownloadSize = GetWillDownloadSize();
	// 已下载字节数
	int nDownloadedSize = GetDownloadedSize();
	if ((nWillDownloadSize > 0) && (nDownloadedSize >= nWillDownloadSize))
	{
		DownloadEnd(TRUE);
		this->WriteAppointLog(_T("CDownloadHttp::DownloadOnce CDownloadInfo::nDownloadedSize >= nWillDownloadSize Is TRUE"));
		return TRUE;
	}
	if (!CDownloadInfo::DownloadPageContent())
	{
		DownloadEnd(FALSE);
		this->WriteAppointLog(_T("CDownloadHttp::DownloadOnce CDownloadInfo::DownloadOnce Is FALSE"));
		return FALSE;
	}
	char szTailData[MAX_BUFFER_SIZE] = {'0'};
	int nTailSize = sizeof(szTailData);
	if (!RequestHttpData(TRUE, szTailData, &nTailSize))
	{
		DownloadEnd(FALSE);
		this->WriteAppointLog(_T("CDownloadHttp::DownloadOnce RequestHttpData Is FALSE"));
		return FALSE;
	}
	if (m_pPageContent != NULL)
	{
		delete[] m_pPageContent;
		m_pPageContent = NULL;
	}
	m_nPageLength = nTailSize;
	m_pPageContent = new CHAR[m_nPageLength + 1];
	memset(m_pPageContent, 0, m_nPageLength + 1);
	memcpy(m_pPageContent, szTailData, m_nPageLength);
	DownloadEnd(bReturn);
	this->WriteAppointLog(_T("CDownloadHttp::DownloadOnce End"));
	return TRUE;
}



CString CDownloadHttp::GetRequestStr(BOOL bGet)
{
	CString strVerb;
	if (bGet)
	{
		strVerb = _T("GET ");
	}
	else
	{
		strVerb = _T("HEAD ");
	}

	CString strRequest = _T("");
	CString strAuth = _T("");
	CString strRange = _T("");
	strRequest  = strVerb  + m_strObject + _T(" HTTP/1.1\r\n");
	//
	CString strPort = _T("");
	if ( m_nPort != DEFAULT_HTTP_PORT )
	{
		strPort.Format (_T(":%d"), m_nPort);
	}
	strRequest += _T("Host: ") + m_strServer + strPort + _T("\r\n");
	strRequest += _T("Accept: */*\r\n");
	strRequest += _T("Pragma: no-cache\r\n"); 
	strRequest += _T("Cache-Control: no-cache\r\n");
	strRequest += _T("User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.2; SV1; .NET CLR 1.1.4322; .NET CLR 2.0.50727)\r\n");
	if( m_strReferer.IsEmpty() )
	{
		m_strReferer = GetRefererFromURL();
	}
	strRequest += _T("Referer: ") + m_strDownloadUrl + _T("\r\n");
	strRequest += _T("Connection: close\r\n");
	// 指定要下载的文件范围
	CString csEndPos;
	int nWillDownloadStartPos = GetWillDownloadStartPos ();	// 开始位置
	int nWillDownloadSize = GetWillDownloadSize();				// 本次应该下载的字节数
	int nDownloadedSize = GetDownloadedSize ();				// 已下载字节数
	if (nWillDownloadSize > 0)
	{
		csEndPos.Format(_T("%d"), nWillDownloadStartPos + nWillDownloadSize - 1);
	}
	strRange.Format(_T("Range: bytes=%d-%s\r\n"), nWillDownloadStartPos + nDownloadedSize, csEndPos);

	strRequest += strRange;
	strRequest += _T("\r\n");
	
	return strRequest;
}


//
// 向服务器提交请求，并得到返回字符串
//
BOOL CDownloadHttp::SendRequest(LPCTSTR lpszReq, CString &strResponse, char *szTailData/*=NULL*/, int *pnTailSize/*=NULL*/ )
{
	m_WnSocketClient.Disconnect();
	BOOL bFlag = FALSE;
	bFlag = Connect();
	if (!bFlag)
	{
		return FALSE;
	}
	bFlag = m_WnSocketClient.SendString(lpszReq);
	if (!bFlag)
	{
		return FALSE;
	}

	for ( int i = 0; ; i++ )
	{
		char szRecvBuffer[MAX_BUFFER_SIZE] = {0};
		int nReadSize = m_WnSocketClient.Receive(szRecvBuffer, sizeof(szRecvBuffer));
		if (nReadSize <= 0)
		{
			return FALSE;
		}
		strResponse += szRecvBuffer;
		char *p = strstr(szRecvBuffer, "\r\n\r\n");
		if (p)
		{
			if ( szTailData && pnTailSize && *pnTailSize > 0 )
			{
				p += 4;
				int nOtioseSize = nReadSize - int( p - szRecvBuffer );
				*pnTailSize = MIN ( nOtioseSize, *pnTailSize );
				memcpy ( szTailData, p, *pnTailSize );
			}
#ifdef _DEBUG
			int nPos = strResponse.Find (_T("\r\n\r\n"), 0 );
			CString csDump;
			if ( nPos >= 0 ) 
			{
				csDump = strResponse.Left ( nPos );
			}
			else csDump = strResponse;
			{
				
			}
#endif
			break;
		}
	}

	return TRUE;
}

DWORD CDownloadHttp::GetResponseCode(CString strLineValue)
{
	strLineValue.MakeLower();
	int nPos = strLineValue.Find (_T(" "), 0);
	if (nPos < 0) 
	{
		return 0;
	}
	CString strCodeValue = strLineValue.Mid(nPos + 1);
	strCodeValue.TrimLeft(); 
	strCodeValue.TrimRight();
	nPos = strCodeValue.Find(_T(" "), 0);
	if (nPos < 0) 
	{
		nPos = strCodeValue.GetLength();
	}
	strCodeValue = strCodeValue.Left(nPos);
	return (DWORD)_ttoi(strCodeValue);
}


BOOL CDownloadHttp::ParseResponseString (CString strResponseValue, BOOL & bRetryRequest)
{
	bRetryRequest = FALSE;
	// 获取返回代码
	CString strOneLine = GetOneLine(strResponseValue);
	DWORD dwResponseCode = GetResponseCode(strOneLine);
	if (dwResponseCode < 1)
	{
		return FALSE;
	}
	int nPos = 0;
	// 请求文件被重定向
	if (dwResponseCode >= 300 && dwResponseCode < 400)
	{
		bRetryRequest = TRUE;
		// 得到请求文件新的URL
		CString strRedirectFileName = FindAfterFlagString(_T("location:"), strResponseValue);
		
		// 设置 Referer
		m_strReferer = GetRefererFromURL ();
		
		// 重定向到其他的服务器
		nPos = strRedirectFileName.Find(_T("://"));
		if (nPos >= 0)
		{
			m_strDownloadUrl = strRedirectFileName;
			// 检验要下载的URL是否有效
			if (!ParseURL ( m_strDownloadUrl, m_strServer, m_strObject, m_nPort, m_strProtocolType ) )
			{
				return FALSE;
			}
			return TRUE;
		}
		
		// 重定向到本服务器的其他地方
		strRedirectFileName.Replace(_T("\\"), _T("/"));
		// 重定向于根目录
		if (strRedirectFileName[0] == _T('/'))
		{
			m_strObject = strRedirectFileName;
			//DownloadNotify ( -1, NOTIFY_TYPE_GOT_REMOTE_FILENAME, (LPVOID)(LPCTSTR)(GetDownloadObjectFileName()), m_pDownloadMTR );
			return TRUE;
		}
		
		// 定向于相对当前目录
		int nParentDirCount = 0;
		nPos = strRedirectFileName.Find (_T("../"));
		while ( nPos >= 0 )
		{
			strRedirectFileName = strRedirectFileName.Mid(nPos+3);
			nParentDirCount++;
			nPos = strRedirectFileName.Find(_T("../"));
		}
		for (int i=0; i<=nParentDirCount; i++)
		{
			nPos = m_strDownloadUrl.ReverseFind(_T('/'));
			if (nPos != -1)
				m_strDownloadUrl = m_strDownloadUrl.Left(nPos);
		}
		if ( strRedirectFileName.Find (_T("./"), 0 ) == 0 )
			strRedirectFileName.Delete ( 0, 2 );
		m_strDownloadUrl = m_strDownloadUrl + _T("/")+strRedirectFileName;
		
		return ParseURL( m_strDownloadUrl, m_strServer, m_strObject, m_nPort, m_strProtocolType);
	}
	// 请求被成功接收、理解和接受
	else if( dwResponseCode >= 200 && dwResponseCode < 300 )
	{
		if (m_nIndex == -1)	// 主线程才需要获取文件大小的信息
		{
			// 获取 Content-Length
			CString strDownFileLen = FindAfterFlagString(_T("content-length:"), strResponseValue);
			m_nFileTotalSize = (int) _ttoi((LPCTSTR)strDownFileLen);
			// 开始位置
			int nWillDownloadStartPos = GetWillDownloadStartPos();
			// 本次应该下载的字节数
			int nWillDownloadSize = GetWillDownloadSize();
			// 已下载字节数
			int nDownloadedSize = GetDownloadedSize();
			if (m_nFileTotalSize > 0 && (nWillDownloadSize - nDownloadedSize > m_nFileTotalSize))
			{
				SetWillDownloadSize ( m_nFileTotalSize - nDownloadedSize );
			}
		}
		
		// 获取服务器文件的最后修改时间
		CString strModifiedTime = FindAfterFlagString(_T("last-modified:"), strResponseValue);
		// 获取文件名称
		CString strContentDisposition = FindAfterFlagString(_T("content-disposition:"), strResponseValue);
		if (strContentDisposition != _T(""))
		{
			m_strContentDispositionFileName = GetContentDispositionFileName(strContentDisposition);
		}
		if (!strModifiedTime.IsEmpty())
		{
			m_TimeLastModified = ConvertHttpTimeString(strModifiedTime);
		}

		if ( dwResponseCode == 206 )	// 支持断点续传
		{
			m_bSupportResume = TRUE;
		}
		else							// 不支持断点续传
		{
			m_bSupportResume = FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

CString CDownloadHttp::FindAfterFlagString(LPCTSTR strFoundValue, CString strOrgValue)
{
	CString strReturn = _T("");
	CString strFound = strFoundValue;
	strFound.MakeLower();
	CString strOrgLower = strOrgValue;
	strOrgLower.MakeLower();
	int nPos = strOrgLower.Find(strFound);
	if (nPos < 0)
	{
		return _T("");
	}
	strReturn = strOrgValue.Mid(nPos + strFound.GetLength());
	nPos = strReturn.Find(_T("\r\n"));
	if (nPos < 0) 
	{
		return _T("");
	}
	strReturn = strReturn.Left(nPos);
	strReturn.TrimLeft();
	strReturn.TrimRight();
	return strReturn;
}

CString CDownloadHttp::GetContentDispositionFileName(CString strContentDisposition)
{
	CString strReturn = _T("");
	CString strFound = _T("filename=\"");
	CString strContentDispositionLower = strContentDisposition;
	strContentDispositionLower.MakeLower();
	int nPos = strContentDispositionLower.Find(strFound);
	if (nPos < 0)
	{
		strFound = _T("filename=");
		nPos = strContentDispositionLower.Find(strFound);
		if (nPos < 0)
		{
			return _T("");
		}
		strReturn = strContentDispositionLower.Mid(nPos + strFound.GetLength());
		return strReturn;
	}
	strReturn = strContentDispositionLower.Mid(nPos + strFound.GetLength());
	nPos = strReturn.Find(_T("\""));
	if (nPos < 0) 
	{
		return _T("");
	}
	strReturn = strReturn.Left(nPos);
	strReturn.TrimLeft();
	strReturn.TrimRight();
	return strReturn;
}


int GetMouthByShortStr (LPCTSTR lpszShortMonth )
{
	const TCHAR * szConstMonth[12] =
	{
		_T("jan"), 
		_T("feb"),
		_T("mar"), 
		_T("apr"), 
		_T("may"), 
		_T("jun"), 
		_T("jul"), 
		_T("aug"), 
		_T("sep"), 
		_T("oct"), 
		_T("nov"), 
		_T("dec")
	};

	CString strMonth = lpszShortMonth;
	strMonth.MakeLower();
	for (int i = 0; i < 12; i++)
	{
		if ( _tcscmp(strMonth.GetBuffer(), szConstMonth[i]) == 0)
		{
			return (i + 1);
		}
	}
	return -1;
};

//
// 将 HTTP 服务器表示的时间转换为 CTime 格式，如：Wed, 16 May 2007 14:29:53 GMT
//
CTime CDownloadHttp::ConvertHttpTimeString(CString strTimeGMT)
{
	CString strYear = _T("");
	CString strMonth = _T("");
	CString strDay = _T("");
	CString strHour = _T("");
	CString strMinute = _T("");
	CString strSecond = _T("");
	CString strTime = _T("");
	//
	int nYear = 0;
	int nMonth = 0;
	int nDay = 0;
	int nHour = 0;
	int nMinute = 0;
	int nSecond = 0;
	//
	CTime myReturnTime = -1;
	int nPos = strTimeGMT.Find(_T(","), 0);
	if (nPos < 0 || nPos >= strTimeGMT.GetLength() - 1)
	{
		return myReturnTime;
	}
	strTimeGMT = strTimeGMT.Mid(nPos + 1);
	strTimeGMT.TrimLeft(); 
	strTimeGMT.TrimRight();

	// 日
	nPos = strTimeGMT.Find(_T(" "), 0);
	if ((nPos < 0) || (nPos >= strTimeGMT.GetLength() - 1))
	{
		return myReturnTime;
	}
	strDay = strTimeGMT.Left(nPos);
	strTimeGMT = strTimeGMT.Mid(nPos + 1);
	strTimeGMT.TrimLeft();
	strTimeGMT.TrimRight();

	// 月
	nPos = strTimeGMT.Find(_T(" "), 0);
	if ((nPos < 0) || (nPos >= strTimeGMT.GetLength() - 1))
	{
		return myReturnTime;
	}
	strMonth = strTimeGMT.Left(nPos);
	nMonth = GetMouthByShortStr(strMonth);
	strMonth.Format(_T("%02d"), nMonth);
	strTimeGMT = strTimeGMT.Mid(nPos + 1);
	strTimeGMT.TrimLeft(); 
	strTimeGMT.TrimRight();

	// 年
	nPos = strTimeGMT.Find(_T(" "), 0);
	if ((nPos < 0) || (nPos >= strTimeGMT.GetLength() - 1))
	{
		return myReturnTime;
	}
	strYear = strTimeGMT.Left(nPos);
	strTimeGMT = strTimeGMT.Mid(nPos + 1);
	strTimeGMT.TrimLeft();
	strTimeGMT.TrimRight();

	// 时间
	nPos = strTimeGMT.Find(_T(" "), 0);
	if ((nPos < 0) || (nPos >= strTimeGMT.GetLength() - 1))
	{
		return myReturnTime;
	}
	strTime = strTimeGMT.Left(nPos);
	// 时
	nPos = strTime.Find(_T(":"), 0);
	if ((nPos < 0) || (nPos >= strTime.GetLength() - 1))
	{
		return myReturnTime;
	}
	strHour = strTime.Left(nPos);
	strTime = strTime.Mid(nPos + 1);
	// 分
	nPos = strTime.Find(_T(":"), 0);
	if ((nPos < 0) || (nPos >= strTime.GetLength() - 1))
	{
		return myReturnTime;
	}
	strMinute = strTime.Left(nPos);
	strTime = strTime.Mid(nPos + 1);
	// 秒
	strSecond = strTime;
	//
	nYear = _ttoi(strYear);
	nDay = _ttoi(strDay);
	nHour = _ttoi(strHour);
	nMinute = _ttoi(strMinute);
	nSecond = _ttoi(strSecond);
	CTime myTime(nYear, nMonth, nDay, nHour, nMinute, nSecond);
	return myTime;
}

