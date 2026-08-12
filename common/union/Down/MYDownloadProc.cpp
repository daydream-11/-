#include "stdafx.h"
#include "MYDownloadProc.h"
#include "DownloadHttp.h"
#include "CommonUtil.h"

CMYDownloadProc::CMYDownloadProc(void)
{
	// 是否下载成功
	m_bDownloadFlag = FALSE;
	m_hThread = NULL;
	m_bAllThreadRun = FALSE;
	m_dwDownloadStartTime = 0;
	m_strSavePath = _T("");
	m_strSaveOnlyFileName = _T("");
	m_strDownloadURL = _T("");
	m_pDownloadInfo = NULL;
	m_pPageContent = NULL;
	// 多线程下载对象
	m_pMultiThreadDownloadInfo = NULL;
	m_pMultiSingleDownloadInfo = NULL;
	m_BaseDownloadInfo.dwThreadCount = 0;
	m_bForceDownload = FALSE;
	m_nThreadCount = 0;
	m_nThisTimeDownloadedTotalSize = 0;
	m_dwFrontDownloadCalculateTime = 0;
	m_dwFrontCalculateSpeedDownloadTime = 0;
	m_nThreadCount = 10;
	// 重试次数
	m_nRetryTimes = 100;
	// 重试次数每次暂停次数
	m_nRetryTimesSleepMilliSecond = 5000;
	//
	m_pVectorDownloadSpeed = NULL;
	m_hEvtEndModule = ::CreateEvent(NULL, TRUE, FALSE, NULL);
}

CMYDownloadProc::~CMYDownloadProc(void)
{
	if (m_pVectorDownloadSpeed != NULL)
	{
		delete m_pVectorDownloadSpeed;
		m_pVectorDownloadSpeed = NULL;
	}
	if (m_pPageContent != NULL)
	{
		delete[] m_pPageContent;
		m_pPageContent = NULL;
	}
	if ( m_pDownloadInfo != NULL)
	{
		delete m_pDownloadInfo;
		m_pDownloadInfo = NULL;
	}
	if ( m_pMultiThreadDownloadInfo != NULL)
	{
		delete[] m_pMultiThreadDownloadInfo;
		m_pMultiThreadDownloadInfo = NULL;
	}
	if ( m_pMultiSingleDownloadInfo != NULL)
	{
		delete[] m_pMultiSingleDownloadInfo;
		m_pMultiSingleDownloadInfo = NULL;
	}
}


/**********************************************************************
* 函数名称： SetThreadCount
* 功能描述： 设置下载的线程数
* 输入参数：
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CMYDownloadProc::SetThreadCount(int nThreadCount)
{
	if (nThreadCount <= 0 || nThreadCount > MAX_DOWNLOAD_THREAD_COUNT)
	{
		return FALSE;
	}
	m_nThreadCount = nThreadCount;
	return TRUE;
}

/**********************************************************************
* 函数名称： SetThreadCount
* 功能描述： 获取下载所消耗的时间（毫秒），可用来计算下载速度和推算剩余时间
* 输入参数：
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
DWORD CMYDownloadProc::GetDownloadElapsedTime()
{
	return (GetTickCount() - m_dwDownloadStartTime);
}

/**********************************************************************
* 函数名称： GetTotalDownloadedSizeThisTimes
* 功能描述： 获取本次下载大小
* 输入参数：
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
int CMYDownloadProc::GetTotalDownloadedSizeThisTimes()
{
	int nThisTimeDownloadedTotalSize = 0;
	m_csThisTimeDownloadedTotalSize.Lock();
	nThisTimeDownloadedTotalSize = m_nThisTimeDownloadedTotalSize;
	m_csThisTimeDownloadedTotalSize.Unlock();
	return nThisTimeDownloadedTotalSize;
}


// 初始化下载过程类
BOOL CMYDownloadProc::Init()
{
	if (m_pDownloadInfo != NULL)
	{
		delete m_pDownloadInfo;
		m_pDownloadInfo = NULL;
	}
	m_pDownloadInfo  = new CDownloadHttp();
	if  (m_pDownloadInfo == NULL)
	{
		return FALSE;
	}
	if (m_pVectorDownloadSpeed != NULL)
	{
		delete m_pVectorDownloadSpeed;
		m_pVectorDownloadSpeed = NULL;
	}
	m_pVectorDownloadSpeed = new CVectorDownloadSpeed();
	if (m_pVectorDownloadSpeed == NULL)
	{
		return FALSE;
	}
	TCHAR szModulePath[MAX_PATH] = {'\0'};
	GetModuleFileName(NULL, szModulePath, MAX_PATH);
	TCHAR * pszFindValue = _tcsrchr(szModulePath,'\\');
	*(pszFindValue + 1) = '\0';
	m_strMoudlePath = szModulePath;
	 return TRUE;
}


// 设置重试次数
VOID CMYDownloadProc::SetRetryTimes(int nRetryTimes)
{
	m_pDownloadInfo->SetRetryTimes(nRetryTimes);
	m_nRetryTimes = nRetryTimes;
}


// 设置循环下载暂停时间
void CMYDownloadProc::SetRetryTimesSleepMilliSecond(int nRetryTimesSleepMilliSecond)
{
	m_pDownloadInfo->SetSleepMilliSecond(nRetryTimesSleepMilliSecond);
	m_nRetryTimesSleepMilliSecond = nRetryTimesSleepMilliSecond;
}


// 多线程断点续传下载一个文件
BOOL CMYDownloadProc::DoDownloadFile(const TCHAR * strDownloadUrl, const TCHAR * strSaveFileName)
{
	if (m_pMultiSingleDownloadInfo != NULL)
	{
		delete[] m_pMultiSingleDownloadInfo;
		m_pMultiSingleDownloadInfo = NULL;
	}
	if (m_pMultiThreadDownloadInfo != NULL)
	{
		delete[] m_pMultiThreadDownloadInfo;
		m_pMultiThreadDownloadInfo = NULL;
	}
	m_bForceDownload = FALSE;
	m_bAllThreadRun = FALSE;
	m_strDownloadURL = strDownloadUrl;
	m_strSavePathFileName = strSaveFileName;
	m_strSaveFileName = m_strSavePathFileName;
	m_strSaveFileName += _T(".download");
	CString strServer = _T("");
	CString strObject = _T("");
	CString strProtocolType = _T("");
	int nPort = 0;
	m_pDownloadInfo->ParseURL(m_strDownloadURL, strServer, strObject, nPort, m_strProtocolType);
	//
	m_pDownloadInfo->SetDownloadUrl(m_strDownloadURL);

	// 创建一个下载线程
	DWORD dwThreadID = 0;
	m_hThread = ::CreateThread (NULL, 0, DoDownloadFileThread, LPVOID(this), 0, &dwThreadID);
	if (m_hThread == NULL)
	{
		return FALSE;
	}
	return TRUE;
}


// 多线程断点续传下载一个文件
BOOL CMYDownloadProc::DoWaitDownloadFile(const TCHAR * strDownloadUrl, const TCHAR * strSaveFileName)
{
	if (m_pMultiSingleDownloadInfo != NULL)
	{
		delete[] m_pMultiSingleDownloadInfo;
		m_pMultiSingleDownloadInfo = NULL;
	}
	if (m_pMultiThreadDownloadInfo != NULL)
	{
		delete[] m_pMultiThreadDownloadInfo;
		m_pMultiThreadDownloadInfo = NULL;
	}
	m_bForceDownload = FALSE;
	m_bAllThreadRun = FALSE;
	m_strDownloadURL = strDownloadUrl;
	m_strSavePathFileName = strSaveFileName;
	m_strSaveFileName = m_strSavePathFileName;
	m_strSaveFileName += _T(".download");
	CString strServer = _T("");
	CString strObject = _T("");
	CString strProtocolType = _T("");
	int nPort = 0;
	m_pDownloadInfo->ParseURL(m_strDownloadURL, strServer, strObject, nPort, m_strProtocolType);
	//
	m_pDownloadInfo->SetDownloadUrl(m_strDownloadURL);
	//
	m_bDownloadFlag = FALSE;
	// 创建一个下载线程
	DWORD dwThreadID = 0;
	m_hThread = ::CreateThread (NULL, 0, DoDownloadFileThread, LPVOID(this), 0, &dwThreadID);
	if (m_hThread == NULL)
	{
		return FALSE;
	}
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	int nResult = (int)::WaitForSingleObject(m_hThread, INFINITE) - WAIT_OBJECT_0;
	return m_bDownloadFlag;
}


// 请求http 文件时间
BOOL CMYDownloadProc::DoRequestHttpFileTime(const TCHAR * strHttpFileName, TCHAR * strReturnTime)
{
	if (m_pMultiSingleDownloadInfo != NULL)
	{
		delete[] m_pMultiSingleDownloadInfo;
		m_pMultiSingleDownloadInfo = NULL;
	}
	if (m_pMultiThreadDownloadInfo != NULL)
	{
		delete[] m_pMultiThreadDownloadInfo;
		m_pMultiThreadDownloadInfo = NULL;
	}
	m_bForceDownload = FALSE;
	m_bAllThreadRun = FALSE;
	m_strDownloadURL = strHttpFileName;
	CString strServer = _T("");
	CString strObject = _T("");
	CString strProtocolType = _T("");
	int nPort = 0;
	m_pDownloadInfo->ParseURL(m_strDownloadURL, strServer, strObject, nPort, m_strProtocolType);
	//
	m_pDownloadInfo->SetDownloadUrl(m_strDownloadURL);

	// 创建一个下载线程
	DWORD dwThreadID = 0;
	m_hThread = ::CreateThread (NULL, 0, DoRequestHttpFileTimeThread, LPVOID(this), 0, &dwThreadID);
	if (m_hThread == NULL)
	{
		return FALSE;
	}
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	int nResult = (int)::WaitForSingleObject(m_hThread, INFINITE) - WAIT_OBJECT_0;
	_tcscpy(strReturnTime, m_strLastModifyTime.GetBuffer());
	return TRUE;
}


// 请求http 文件内容
CHAR* CMYDownloadProc::DoRequestHttpPageContent(const TCHAR * strHttpFileName)
{
	if (m_pMultiSingleDownloadInfo != NULL)
	{
		delete[] m_pMultiSingleDownloadInfo;
		m_pMultiSingleDownloadInfo = NULL;
	}
	if (m_pMultiThreadDownloadInfo != NULL)
	{
		delete[] m_pMultiThreadDownloadInfo;
		m_pMultiThreadDownloadInfo = NULL;
	}
	m_bForceDownload = FALSE;
	m_bAllThreadRun = FALSE;
	m_strDownloadURL = strHttpFileName;
	CString strServer = _T("");
	CString strObject = _T("");
	CString strProtocolType = _T("");
	int nPort = 0;
	m_pDownloadInfo->ParseURL(m_strDownloadURL, strServer, strObject, nPort, m_strProtocolType);
	//
	m_pDownloadInfo->SetDownloadUrl(m_strDownloadURL);

	// 创建一个下载线程
	DWORD dwThreadID = 0;
	m_hThread = ::CreateThread (NULL, 0, DoRequestHttpPageContentThread, LPVOID(this), 0, &dwThreadID);
	if (m_hThread == NULL)
	{
		return NULL;
	}
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	int nResult = (int)::WaitForSingleObject(m_hThread, INFINITE) - WAIT_OBJECT_0;
	return m_pPageContent;
}

/**********************************************************************
* 函数名称： DoRunSuspendThread
* 功能描述： 暂停下载的线程
* 输入参数：
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CMYDownloadProc::DoRunSuspendThread(void)
{
	DWORD dwReturn = SuspendThread(m_hThread);
	if (dwReturn == 0xFFFFFFFF)
	{
		return FALSE;
	}
	if (m_pDownloadInfo != NULL)
	{
		m_pDownloadInfo->DoRunSuspendThread();
	}
	if (m_pMultiThreadDownloadInfo != NULL)
	{
		for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++)
		{
			m_pMultiThreadDownloadInfo[nIndex].DoRunSuspendThread();
		}
	}
	m_pVectorDownloadSpeed->clear();
	return TRUE;
}

/**********************************************************************
* 函数名称： DoRunResumeThread
* 功能描述： 恢复下载的线程
* 输入参数：
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CMYDownloadProc::DoRunResumeThread(void)
{
	if (m_pDownloadInfo != NULL)
	{
		m_pDownloadInfo->DoRunResumeThread();
	}
	if (m_pMultiThreadDownloadInfo != NULL)
	{
		for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++)
		{
			m_pMultiThreadDownloadInfo[nIndex].DoRunResumeThread();
		}
	}
	DWORD dwReturn = ResumeThread(m_hThread);
	if (dwReturn == 0xFFFFFFFF)
	{
		return FALSE;
	}
	return TRUE;
}

/**********************************************************************
* 函数名称： DoRunTerminateThread
* 功能描述： 终结下载的线程
* 输入参数：
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
void CMYDownloadProc::DoRunTerminateThread(void)
{
	if (m_pDownloadInfo != NULL)
	{
		m_pDownloadInfo->DoRunTerminateThread();
	}
	if (m_pMultiThreadDownloadInfo != NULL)
	{
		for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++)
		{
			m_pMultiThreadDownloadInfo[nIndex].DoRunTerminateThread();
		}
	}
	if (m_hThread != NULL)
	{
		DWORD dwExitCode = 0;
		GetExitCodeThread(m_hThread, &dwExitCode); 
		TerminateThread(m_hThread, dwExitCode);
		m_hThread = NULL;
	}
	m_pVectorDownloadSpeed->clear();
}



// 下载文件线程
DWORD WINAPI CMYDownloadProc::DoDownloadFileThread(LPVOID lpParameter)
{
	CMYDownloadProc *pWnMYDownloadProc = (CMYDownloadProc*)lpParameter;
	pWnMYDownloadProc->DoDownloadFileProc();
	return TRUE;
}

// 请求http文件时间线程
DWORD WINAPI CMYDownloadProc::DoRequestHttpFileTimeThread(LPVOID lpParameter)
{
	CMYDownloadProc *pWnMYDownloadProc = (CMYDownloadProc*)lpParameter;
	pWnMYDownloadProc->DoRequestHttpFileTimeProc();
	return TRUE;
}

// 请求http页面内容
DWORD WINAPI CMYDownloadProc::DoRequestHttpPageContentThread(LPVOID lpParameter)
{
	CMYDownloadProc *pWnMYDownloadProc = (CMYDownloadProc*)lpParameter;
	pWnMYDownloadProc->DoRequestHttpPageContentProc();
	return TRUE;
}



// 下载文件过程
BOOL CMYDownloadProc::DoDownloadFileProc()
{
	this->WriteDebugLog(_T("CMYDownloadProc::DoDownloadFileProc Start"));
	BOOL bReturn = FALSE;
	bReturn = DoStartDownloadFile();
	if (!bReturn) 
	{
		m_bDownloadFlag = FALSE;
		//
		bReturn = HandleDownloadFinished(ENUM_DOWNLOAD_RESULT_FAILED);
		//
		this->WriteDebugLog(_T("CMYDownloadProc::DoDownloadFileProc DoStartDownloadFile Is FALSE"));
		//
		return bReturn;
	}
	// 等待所有线程下载完成
	ENUM_DOWNLOAD_RESULT myDownloadResult = DoWaitForDownloadFinish();
	if (myDownloadResult == ENUM_DOWNLOAD_RESULT_SUCCESS && !GetDownloadResult ())
	{
		myDownloadResult = ENUM_DOWNLOAD_RESULT_FAILED;
		//
		this->WriteDebugLog(_T("CMYDownloadProc::DoDownloadFileProc GetDownloadResult Is FALSE"));
	}
	//
	m_bDownloadFlag = HandleDownloadFinished(myDownloadResult);
	//
	this->WriteDebugLog(_T("CMYDownloadProc::DoDownloadFileProc End"));
	//
	return m_bDownloadFlag;
}


// 请求文件时间线程过程函数
BOOL CMYDownloadProc::DoRequestHttpFileTimeProc()
{
	this->WriteDebugLog(_T("CMYDownloadProc::DoRequestHttpFileTimeProc Start"));
	BOOL bReturn = FALSE;
	BOOL bFlag = m_pDownloadInfo->GetRemoteSiteInfo();
	if (!bFlag)
	{
		return FALSE;
	}
	TCHAR szModifyTime[MAX_PATH] = {'\0'};
	INT nModifyTime = m_pDownloadInfo->GetTimeLastModified();
	CommonUtil::GetAppointDay_Time(nModifyTime, szModifyTime);
	m_strLastModifyTime = szModifyTime;
	return TRUE;
}


// 请求文件文件内容函数过程
BOOL CMYDownloadProc::DoRequestHttpPageContentProc()
{
	m_nThreadCount = 1;
	CDownloadHttp *pDownloadHttp = new CDownloadHttp();
	if (pDownloadHttp == NULL)
	{
		return FALSE;
	}
	int nFileTotalSize = 100 * 1024;
	pDownloadHttp->m_nIndex = 0;
	pDownloadHttp->m_nThradCount = m_nThreadCount;
	pDownloadHttp->RegListener(this);
	pDownloadHttp->SetDownloadUrl(m_strDownloadURL);
	pDownloadHttp->SetSaveFileName(m_strSaveFileName);
	pDownloadHttp->SetMoudlePath(m_strMoudlePath);
	pDownloadHttp->DoRequestPageContent(nFileTotalSize, 0);
	CHAR *lpRevePageContent = pDownloadHttp->GetPageContent();
	INT nPageLength = pDownloadHttp->GetPageLength();
	if (m_pPageContent != NULL)
	{
		delete[] m_pPageContent;
		m_pPageContent = NULL;
	}
	m_pPageContent = new CHAR[nPageLength + 1];
	memset(m_pPageContent, 0, nPageLength + 1);
	memcpy(m_pPageContent, lpRevePageContent, nPageLength);
	delete pDownloadHttp;
	pDownloadHttp = NULL;
	return TRUE;
}


// 下载的回调函数
BOOL CMYDownloadProc::GetDownloadResult()
{
	for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++)
	{
		BOOL bDownloadSuccess = m_pMultiThreadDownloadInfo[nIndex].IsDownloadSuccess();
		if (!bDownloadSuccess)
		{
			return FALSE;
		}
	}
	return TRUE;
}

// 下载的回调函数
BOOL CMYDownloadProc::HandleDownloadFinished(ENUM_DOWNLOAD_RESULT myDownloadResult)
{
	this->WriteDebugLog(_T("CMYDownloadProc::HandleDownloadFinished Start"));
	CFileStatus myFileStatus;
	BOOL bReturn = FALSE;
	CFile myFile;
	if (myDownloadResult != ENUM_DOWNLOAD_RESULT_SUCCESS)
	{
		this->WriteDebugLog(_T("CMYDownloadProc::HandleDownloadFinished myDownloadResult != ENUM_DOWNLOAD_RESULT_SUCCESS"));
		this->OnSetDownloadFail();
		return FALSE;
	}
	BOOL bSupportResume = m_pDownloadInfo->IsSupportResume();
	int nFileTotalSize = m_pDownloadInfo->GetFileTotalSize();
	// 设置文件大小
	if (bSupportResume && nFileTotalSize > 0)
	{
		TRY
		{
			UINT uOptionFlags = CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::typeBinary | CFile::shareDenyNone;
			myFile.Open (m_strSaveFileName, uOptionFlags);
			myFile.SetLength(nFileTotalSize);
			bReturn = TRUE;
		}
		CATCH( CFileException, e)
		{
			e->Delete();
			bReturn = FALSE;
		}
		END_CATCH
		if (HANDLE_IS_VALID(myFile.m_hFile))
		{
			myFile.Close();
		}
		if (!bReturn)
		{
			myDownloadResult = ENUM_DOWNLOAD_RESULT_FAILED;
			this->WriteDebugLog(_T("CMYDownloadProc::HandleDownloadFinished myDownloadResult = ENUM_DOWNLOAD_RESULT_FAILED1111"));
			return FALSE;
		}
	}
	// 将文件改名
	bReturn = FALSE;
	::DeleteFile( m_strSavePathFileName);
	TRY
	{
		CFile::Rename(m_strSaveFileName, m_strSavePathFileName);
		this->WriteDebugLog(_T("CMYDownloadProc::HandleDownloadFinished CFile::Rename(%s,%s)"), m_strSaveFileName.GetBuffer(), m_strSavePathFileName.GetBuffer());
		bReturn = TRUE;
	}
	CATCH (CFileException, e)
	{
		e->Delete();
		bReturn = FALSE;
	}
	END_CATCH
	if (!bReturn)
	{
		myDownloadResult = ENUM_DOWNLOAD_RESULT_FAILED;
		this->WriteDebugLog(_T("CMYDownloadProc::HandleDownloadFinished myDownloadResult = ENUM_DOWNLOAD_RESULT_FAILED2222"));
		return FALSE;
	}
	// 设置文件属性，时间设置和服务器一致
	bReturn = FALSE;
	if (CFile::GetStatus(m_strSavePathFileName, myFileStatus))
	{
		myFileStatus.m_mtime = m_pDownloadInfo->GetTimeLastModified();
		myFileStatus.m_attribute = CFile::normal;
		CFile::SetStatus( m_strSavePathFileName, myFileStatus);
		bReturn = TRUE;
	}
	if (!bReturn)
	{
		myDownloadResult = ENUM_DOWNLOAD_RESULT_FAILED;
		this->WriteDebugLog(_T("CMYDownloadProc::HandleDownloadFinished myDownloadResult = ENUM_DOWNLOAD_RESULT_FAILED3333"));
		return FALSE;
	}
	//
	this->OnSetAlreadyDownloadSize(nFileTotalSize);
	this->OnSetDownloadFinish();
	this->WriteDebugLog(_T("CMYDownloadProc::HandleDownloadFinished End"));
	return TRUE;
}

// 下载的回调函数
void CallBackSaveDownloadInfoProc( int nIndex, int nDownloadedSize, int nSimpleSaveSize, WPARAM wParam )
{
	CMYDownloadProc *pWnMYDownloadProc = (CMYDownloadProc*)wParam;
	pWnMYDownloadProc->CallBackSaveDownloadInfoProc(nIndex, nDownloadedSize, nSimpleSaveSize);
}

// 下载的回调函数
void CMYDownloadProc::CallBackSaveDownloadInfoProc(int nIndex, int nDownloadedSize, int nSimpleSaveSize)
{
	if (nIndex >= 0 && nIndex < m_nThreadCount)
	{
		m_pMultiSingleDownloadInfo[nIndex].nDownloadedSize = nDownloadedSize;
		if ( nDownloadedSize > 0 )
		{
			m_csThisTimeDownloadedTotalSize.Lock();
			m_nThisTimeDownloadedTotalSize += nSimpleSaveSize;
			m_csThisTimeDownloadedTotalSize.Unlock();
		}
	}
}


// 下载的回调函数
void CallbackDownloadProgressInfoProc(WPARAM wParam)
{
	CMYDownloadProc *pWnMYDownloadProc = (CMYDownloadProc*)wParam;
	pWnMYDownloadProc->CallbackDownloadProgressInfoProc();
}

// 下载进度的回调函数
void CMYDownloadProc::CallbackDownloadProgressInfoProc()
{
	m_csSetDownloadProgressInfo.Lock();
	if (m_bAllThreadRun)
	{
		DWORD dwCurDownloadCalculateTime = GetTickCount();
		DWORD dwDifferDownloadCalculateTime = dwCurDownloadCalculateTime - m_dwFrontDownloadCalculateTime;
		if (dwDifferDownloadCalculateTime > 50)
		{
			m_dwFrontDownloadCalculateTime = dwCurDownloadCalculateTime;
			int nTotalDownloadedSize = GetTotalDownloadedSize();
			this->OnSetAlreadyDownloadSize(nTotalDownloadedSize);
			// 计算下载速度
			int nTotalDownloadedSizeThisTimes = GetTotalDownloadedSizeThisTimes();
			int nElapsedTime = GetDownloadElapsedTime();
			if (nElapsedTime > 5 * 1000 || (nElapsedTime > 2 * 1000 && nTotalDownloadedSizeThisTimes > 1024))
			{
				DWORD dwDifferCalculateSpeedDownloadTime = dwCurDownloadCalculateTime - m_dwFrontCalculateSpeedDownloadTime;
				if (dwDifferCalculateSpeedDownloadTime > 1000)
				{
					int nVectorSize = m_pVectorDownloadSpeed->size();
					int nFrontDownloadSize = 0;
					int nFrontDownloadTime = 0;
					int nIntervalDownloadSize = 0;
					int nIntervalDownloadTime = 0;
					if (nVectorSize < 10)
					{
						m_pVectorDownloadSpeed->push_back(pair<int, int>(nTotalDownloadedSizeThisTimes, dwCurDownloadCalculateTime));
					}
					else
					{
						m_pVectorDownloadSpeed->erase(m_pVectorDownloadSpeed->begin());
						m_pVectorDownloadSpeed->push_back(pair<int, int>(nTotalDownloadedSizeThisTimes, dwCurDownloadCalculateTime));
					}
					nFrontDownloadSize = m_pVectorDownloadSpeed->begin()->first;
					nFrontDownloadTime = m_pVectorDownloadSpeed->begin()->second;
					//
					nIntervalDownloadSize = nTotalDownloadedSizeThisTimes - nFrontDownloadSize;
					nIntervalDownloadTime = dwCurDownloadCalculateTime - nFrontDownloadTime;
					m_dwFrontCalculateSpeedDownloadTime = dwCurDownloadCalculateTime;
					//
					float fDownloadSpeed = 0.0;
					if (nIntervalDownloadSize == 0)
					{
						dwDifferCalculateSpeedDownloadTime = dwCurDownloadCalculateTime - m_dwDownloadStartTime;
						fDownloadSpeed = (float)(nTotalDownloadedSizeThisTimes / 1024.0) / ((double)dwDifferCalculateSpeedDownloadTime / 1000.0);
					}
					else
					{
						fDownloadSpeed = (float)(nIntervalDownloadSize / 1024.0) / ((double)nIntervalDownloadTime / 1000.0);
					}
					this->OnSetCurrentDownloadSpeed(fDownloadSpeed);
				}
			}
		}
	}
	m_csSetDownloadProgressInfo.Unlock();
}


// 开始下载文件
BOOL CMYDownloadProc::DoStartDownloadFile()
{
	this->WriteDebugLog(_T("CMYDownloadProc::DoStartDownloadFile Start"));
	m_dwDownloadStartTime = GetTickCount();
	m_dwFrontDownloadCalculateTime = m_dwDownloadStartTime;
	m_dwFrontCalculateSpeedDownloadTime = m_dwDownloadStartTime;
	this->WriteDebugLog(_T("CMYDownloadProc::DoStartDownloadFile GetRemoteSiteInfo Start"));
	BOOL bFlag = m_pDownloadInfo->GetRemoteSiteInfo();
	this->WriteDebugLog(_T("CMYDownloadProc::DoStartDownloadFile GetRemoteSiteInfo End"));
	if (!bFlag)
	{
		this->WriteDebugLog(_T("CMYDownloadProc::DoStartDownloadFile::m_pDownloadInfo->GetRemoteSiteInfo() Is FALSE"));
		return FALSE;
	}
	CFileStatus myFileStatus;
	BOOL bMustCreateNullFile = TRUE;
	BOOL bSupportResume = m_pDownloadInfo->IsSupportResume();
	int nFileTotalSize = m_pDownloadInfo->GetFileTotalSize();
	this->OnSetDownloadFileSize(nFileTotalSize);
	int nWholeSize = GetDownloadInfoWholeSize();
	// 读取下载信息，如果能读到说明上次下载尚未完成
	if ((!m_bForceDownload) && (bSupportResume))
	{
		BOOL bFlag = CFile::GetStatus(m_strSaveFileName, myFileStatus);
		if (bFlag)
		{
			if (myFileStatus.m_size == (nFileTotalSize + nWholeSize))
			{
				if (ReadDownloadInfo())
				{
					bMustCreateNullFile = FALSE;
				}
			}
		}
	}
	if (bMustCreateNullFile)
	{
		int nTempFileSize = nFileTotalSize + nWholeSize;
		int nNeedMaxThreadCount = 1;
		int nUseThreadCount = 10;
		if (nFileTotalSize <= 1024 * 10)
		{
			nNeedMaxThreadCount = 1;
		}
		else
		{
			int nThreadCountResult = (nFileTotalSize / (1024 * 10));
			if (nThreadCountResult <= nUseThreadCount)
			{
				nNeedMaxThreadCount = nThreadCountResult;
			}
			else
			{
				nNeedMaxThreadCount = nUseThreadCount;
			}
		}
		//
		m_nThreadCount = nNeedMaxThreadCount;
		m_BaseDownloadInfo.dwThreadCount = m_nThreadCount;
		// 创建一个用来保存下载数据的空文件
		if (!CreateNullFile(m_strSaveFileName, nTempFileSize))
		{
			this->WriteDebugLog(_T("CMYDownloadProc::DoStartDownloadFile::CreateNullFile Is FALSE"));
			return FALSE;
		}
	}
	// 分配下载任务
	bFlag = DoAssignDownloadTask();
	if (!bFlag)
	{
		this->WriteDebugLog(_T("CMYDownloadProc::DoStartDownloadFile::DoAssignDownloadTask Is FALSE"));
		return FALSE;
	}
	m_dwDownloadStartTime = GetTickCount();
	this->WriteDebugLog(_T("CMYDownloadProc::DoStartDownloadFile End"));
	return TRUE;
}

// 从下载信息文件中读取下载信息
int CMYDownloadProc::ReadDownloadInfo()
{
	CFile myFile;
	UINT nOptionFlags = CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::typeBinary | CFile::shareDenyNone;
	BOOL bFlag = FALSE;
	bFlag = myFile.Open( m_strSaveFileName, nOptionFlags);
	if (!bFlag)
	{
		return FALSE;
	}
	int nBaseDownloadInfoSize = sizeof(TBaseDownloadInfo);
	int nFileLength = myFile.GetLength();
	int nSeekReturn = myFile.Seek(-nBaseDownloadInfoSize, CFile::end);
	if (nSeekReturn != nFileLength - nBaseDownloadInfoSize)
	{
		myFile.Close();
		return FALSE;
	}
	int nReadReturn = myFile.Read(&m_BaseDownloadInfo, nBaseDownloadInfoSize);
	if (nReadReturn != nBaseDownloadInfoSize)
	{
		myFile.Close();
		return FALSE;
	}
	DWORD dwThreadCount = m_BaseDownloadInfo.dwThreadCount;
	if (dwThreadCount <= 0 && dwThreadCount > MAX_DOWNLOAD_THREAD_COUNT)
	{
		myFile.Close();
		return FALSE;
	}
	SetThreadCount(dwThreadCount);
	bFlag = DoCreateDownloadObject();
	if (!bFlag)
	{
		myFile.Close();
		return FALSE;
	}
	int nWholeSize = GetDownloadInfoWholeSize();
	nSeekReturn = myFile.Seek(-nWholeSize, CFile::end);
	if (nSeekReturn != nFileLength - nWholeSize)
	{
		myFile.Close();
		return FALSE;
	}
	int nMultiTSingleDownloadInfoSize = m_nThreadCount * sizeof(TSingleDownloadInfo);
	nReadReturn = myFile.Read(m_pMultiSingleDownloadInfo, nMultiTSingleDownloadInfoSize);
	if (nReadReturn != nMultiTSingleDownloadInfoSize)
	{
		memset(m_pMultiSingleDownloadInfo, 0, nMultiTSingleDownloadInfoSize);
		myFile.Close();
		return FALSE;
	}
	return TRUE;
}

// 创建一个空文件
BOOL CMYDownloadProc::CreateNullFile(LPCTSTR lpszFileName, int nFileSize)
{
	::DeleteFile( lpszFileName );
	BOOL bReturn = TRUE;
	CFile myFile;
	TRY
	{
		bReturn = myFile.Open(lpszFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		if (bReturn && nFileSize > 0)
		{
			myFile.SetLength(nFileSize);
			int nBaseDownloadInfoSize = sizeof(TBaseDownloadInfo);
			int nSeekReturn = myFile.Seek(-nBaseDownloadInfoSize, CFile::end);
			if (nSeekReturn == (nFileSize - nBaseDownloadInfoSize))
			{
				myFile.Write(&m_BaseDownloadInfo, nBaseDownloadInfoSize);
			}
		}
	}
	CATCH( CFileException, e)
	{
		e->Delete();
		bReturn = FALSE;
	}
	END_CATCH
	if (HANDLE_IS_VALID(myFile.m_hFile))
	{
		myFile.Close();
	}
	return bReturn;
}

// 获取下载的完整数据大小
int CMYDownloadProc::GetDownloadInfoWholeSize()
{
	int nWholeSize = 0;
	nWholeSize = m_nThreadCount * sizeof(TSingleDownloadInfo) + sizeof(TBaseDownloadInfo);
	return nWholeSize;
}

// 删除下载对象
void CMYDownloadProc::DeleteDownloadObject(CDownloadInfo *pDeleteWnDownloadInfo)
{
	if (m_strProtocolType.CompareNoCase(_T("http")) == 0)
	{
		delete[] ((CDownloadHttp*)pDeleteWnDownloadInfo);
	}
	else
	{
		delete[] pDeleteWnDownloadInfo;
	}
}

// 删除多线程下载使用的对象和数据缓冲
void CMYDownloadProc::DoDeleteDownloadObject()
{
	if (m_pMultiThreadDownloadInfo != NULL)
	{
		DeleteDownloadObject(m_pMultiThreadDownloadInfo);
		m_pMultiThreadDownloadInfo = NULL;
	}
	if (m_pMultiSingleDownloadInfo != NULL)
	{
		delete[] m_pMultiSingleDownloadInfo;
		m_pMultiSingleDownloadInfo = NULL;
	}
}

// 创建下载对象
CDownloadInfo* CMYDownloadProc::CreateDownloadObject(int nCount)
{
	if (nCount < 1)
	{
		return NULL;
	}
	CDownloadInfo *pWnDownloadInfo = NULL;
	if (m_strProtocolType.CompareNoCase(_T("http")) == 0)
	{
		pWnDownloadInfo = (CDownloadInfo*) new CDownloadHttp[nCount];
		pWnDownloadInfo->SetRetryTimes(m_nRetryTimes);
		pWnDownloadInfo->SetSleepMilliSecond(m_nRetryTimesSleepMilliSecond);
	}
	else 
	{
		return NULL;
	}
	return pWnDownloadInfo;
}

// 创建多线程下载使用的对象和数据缓冲
BOOL CMYDownloadProc::DoCreateDownloadObject()
{
	DoDeleteDownloadObject();
	// 创建多线程下载配置
	m_pMultiSingleDownloadInfo = new TSingleDownloadInfo[m_nThreadCount];
	if (m_pMultiSingleDownloadInfo != NULL)
	{
		memset(m_pMultiSingleDownloadInfo, 0, m_nThreadCount * sizeof(TSingleDownloadInfo));
	}
	// 创建多线程下载对象
	m_pMultiThreadDownloadInfo = CreateDownloadObject(m_nThreadCount);
	// 设置多线程下载使用的对象的参数
	if (m_pMultiThreadDownloadInfo != NULL)
	{
		for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++)
		{
			m_pMultiThreadDownloadInfo[nIndex].m_nIndex = nIndex;
			m_pMultiThreadDownloadInfo[nIndex].m_nThradCount = m_nThreadCount;
			m_pMultiThreadDownloadInfo[nIndex].RegListener(this);
			m_pMultiThreadDownloadInfo[nIndex].SetCurSingleDownloadInfo(&m_pMultiSingleDownloadInfo[nIndex]);
			m_pMultiThreadDownloadInfo[nIndex].SetCallbackSaveDownloadInfo(::CallBackSaveDownloadInfoProc, WPARAM(this));
			m_pMultiThreadDownloadInfo[nIndex].SetCallbackDownloadProgressInfo(::CallbackDownloadProgressInfoProc, WPARAM(this));
			m_pMultiThreadDownloadInfo[nIndex].SetDownloadUrl(m_strDownloadURL);
			m_pMultiThreadDownloadInfo[nIndex].SetSaveFileName(m_strSaveFileName);
			m_pMultiThreadDownloadInfo[nIndex].SetMoudlePath(m_strMoudlePath);
		}
	}
	
	if (m_pMultiThreadDownloadInfo != NULL && m_pMultiSingleDownloadInfo != NULL)
	{
		return TRUE;
	}
	return FALSE;

}

// 下载信息是否有效
BOOL CMYDownloadProc::IsHavaValidDownloadInfo()
{
	BOOL bHaveValid = FALSE;
	int nIndex = 0;
	if (m_pMultiSingleDownloadInfo == NULL)
	{
		DoClearRelevanceDownloadInfo();
		return FALSE;
	}
	if ((m_BaseDownloadInfo.dwThreadCount < 1) || (m_BaseDownloadInfo.dwThreadCount > MAX_DOWNLOAD_THREAD_COUNT))
	{
		DoClearRelevanceDownloadInfo();
		return FALSE;
	}	
	for (nIndex = 0; nIndex < m_nThreadCount; nIndex++)
	{
		if (m_pMultiSingleDownloadInfo[nIndex].nWillDownloadSize > 0)
		{
			bHaveValid = TRUE;
			break;
		}
	}
	for (nIndex = 0; nIndex < m_nThreadCount; nIndex++)
	{
		if (m_pMultiSingleDownloadInfo[nIndex].nWillDownloadSize == 0 && m_pMultiSingleDownloadInfo[nIndex].nWillDownloadStartPos == 0 && m_pMultiSingleDownloadInfo[nIndex].nDownloadedSize == 0)
		{
			bHaveValid = FALSE;
			break;
		}
	}
	if (!bHaveValid) 
	{
		DoClearRelevanceDownloadInfo();
		return FALSE;
	}
	return TRUE;
}

// 清空相关联的下载信息
void CMYDownloadProc::DoClearRelevanceDownloadInfo()
{
	if (m_pMultiSingleDownloadInfo != NULL)
	{
		memset(m_pMultiSingleDownloadInfo, 0, m_nThreadCount * sizeof(TSingleDownloadInfo));
	}
	memset(&m_BaseDownloadInfo, 0, sizeof(TBaseDownloadInfo));
}

// 分配下载任务
BOOL CMYDownloadProc::DoAssignDownloadTask()
{
	BOOL bSupportResume = m_pDownloadInfo->IsSupportResume();
	int nFileTotalSize = m_pDownloadInfo->GetFileTotalSize();
	int nWillDownloadSize = -1;
	int nWillDownloadStartPos = 0;
	int nDownloadedSize = 0;
	int nNoAssignSize = 0;
	// 不是断点续传
	if (!bSupportResume)
	{
		DoDeleteDownloadObject();
	}
	// 文件大小未知，采用单线程
	if (nFileTotalSize <= 0 || !bSupportResume)
	{
		if (m_nThreadCount != 1)
		{
			DoDeleteDownloadObject();
			SetThreadCount(1);
		}
	}
	BOOL bNeedCreateDownObject = FALSE;
	if (!IsHavaValidDownloadInfo())
	{
		bNeedCreateDownObject = TRUE;
	}
	if (m_pMultiThreadDownloadInfo == NULL)
	{
		bNeedCreateDownObject = TRUE;
	}
	if (m_pMultiSingleDownloadInfo == NULL)
	{
		bNeedCreateDownObject = TRUE;
	}
	// 需要创建下载对象
	if (bNeedCreateDownObject)
	{
		if (!DoCreateDownloadObject())
		{
			return FALSE;
		}
	}
	// 下载任务尚未分配
	if (!IsHavaValidDownloadInfo())
	{
		nWillDownloadSize = -1;
		nWillDownloadStartPos = 0;
		nNoAssignSize = 0;
		if (nFileTotalSize > 0)
		{
			nWillDownloadSize = nFileTotalSize / m_nThreadCount;
			// 均分后剩下的部分，让第一个线程来承担下载
			nNoAssignSize = nFileTotalSize % m_nThreadCount;
		}
		//
		for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++)
		{
			m_pMultiSingleDownloadInfo[nIndex].nWillDownloadStartPos = nWillDownloadStartPos;
			m_pMultiSingleDownloadInfo[nIndex].nWillDownloadSize = nWillDownloadSize;
			if (nIndex == 0 && nFileTotalSize > 0)
			{
				m_pMultiSingleDownloadInfo[nIndex].nWillDownloadSize += nNoAssignSize;
			}
			nWillDownloadStartPos += m_pMultiSingleDownloadInfo[nIndex].nWillDownloadSize;
		}
	}
	int nAlreadyDownloadSize = GetAlreadyDownloadSize();
	//
	// 启动下载任务
	for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++)
	{
		nWillDownloadStartPos = m_pMultiSingleDownloadInfo[nIndex].nWillDownloadStartPos;
		nWillDownloadSize = m_pMultiSingleDownloadInfo[nIndex].nWillDownloadSize;
		nDownloadedSize = m_pMultiSingleDownloadInfo[nIndex].nDownloadedSize;
		BOOL bFlag = m_pMultiThreadDownloadInfo[nIndex].DoRunDownloadFile(nWillDownloadStartPos, nWillDownloadSize, nDownloadedSize);
		if (!bFlag)
		{
			return FALSE;
		}
	}
	m_bAllThreadRun = TRUE;
	m_BaseDownloadInfo.dwThreadCount = m_nThreadCount;
	return TRUE;
}

// 找到剩余未下载的数量最大的那个对象编号
int CMYDownloadProc::GetMaxUnDownloadBytes(int & nUnDownloadBytes)
{
	nUnDownloadBytes = 0;
	int nMaxIndex = -1;
	for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++)
	{
		int nTempUnDownloadBytes = m_pMultiThreadDownloadInfo[nIndex].GetUnDownloadBytes();
		if (nUnDownloadBytes < nTempUnDownloadBytes)
		{
			nUnDownloadBytes = nTempUnDownloadBytes;
			nMaxIndex = nIndex;
		}
	}
	return nMaxIndex;
}

// 编号为 nIndex 的对象调度任务，为下载任务最繁重的对象减轻负担
BOOL CMYDownloadProc::AttemperDownloadTask(int nIndex)
{
	if (m_nThreadCount <= 1 || m_pMultiSingleDownloadInfo[nIndex].nWillDownloadSize == -1)
	{
		return FALSE;
	}
	int nUnDownloadBytes = 0;
	int nHeavyIndex = GetMaxUnDownloadBytes(nUnDownloadBytes);
	if ( nHeavyIndex == -1 || nHeavyIndex == nIndex)
	{
		return FALSE;
	}
	BOOL bThreadRunning = m_pMultiThreadDownloadInfo[nHeavyIndex].IsThreadRunning();
	if (bThreadRunning && nUnDownloadBytes < 100 * 1024)
	{
		return FALSE;
	}
	// 给空闲下载对象分配新任务
	int nNewWillDownloadSize = 0;
	int nNewWillDownloadStartPos = 0;
	int nHeavyWillDownloadStartPos = 0;
	int nHeavyWillDownloadSize = 0;
	if (bThreadRunning)
	{
		nNewWillDownloadSize = nUnDownloadBytes / 2;
	}
	else
	{
		nNewWillDownloadSize = nUnDownloadBytes;
	}
	//

	m_pMultiSingleDownloadInfo[nIndex].nWillDownloadSize = nNewWillDownloadSize;
	// 获取繁忙线程的将要下载位置
	nHeavyWillDownloadStartPos = m_pMultiThreadDownloadInfo[nHeavyIndex].GetWillDownloadStartPos();
	nHeavyWillDownloadSize = m_pMultiThreadDownloadInfo[nHeavyIndex].GetWillDownloadSize();
	nNewWillDownloadStartPos = nHeavyWillDownloadStartPos + nHeavyWillDownloadSize - nNewWillDownloadSize;
	m_pMultiSingleDownloadInfo[nIndex].nWillDownloadStartPos = nNewWillDownloadStartPos;
	m_pMultiSingleDownloadInfo[nIndex].nDownloadedSize = 0;
	
	// 启动空闲下载对象的下载任务
	if ( m_pMultiSingleDownloadInfo[nIndex].nWillDownloadSize == 0)
	{
		return FALSE;
	}
	m_pMultiThreadDownloadInfo[nIndex].ClearDownloadInfo();
	BOOL bFlag = m_pMultiThreadDownloadInfo[nIndex].DoRunDownloadFile(nNewWillDownloadStartPos, nNewWillDownloadSize, 0);
	if (!bFlag)
	{
		return FALSE;
	}
	// 减轻繁忙下载对象的任务
	m_pMultiSingleDownloadInfo[nHeavyIndex].nWillDownloadSize -= nNewWillDownloadSize;
	nHeavyWillDownloadSize = m_pMultiSingleDownloadInfo[nHeavyIndex].nWillDownloadSize;
	m_pMultiThreadDownloadInfo[nHeavyIndex].SetWillDownloadSize(nHeavyWillDownloadSize);
	return TRUE;
}

// 获取已下载的字节数
int CMYDownloadProc::GetAlreadyDownloadSize()
{
	int nAlreadyDownloadSize = 0;
	for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++ )
	{
		nAlreadyDownloadSize += m_pMultiSingleDownloadInfo[nIndex].nDownloadedSize;
	}
	return nAlreadyDownloadSize;
}

// 获取已下载的字节数，包括以前下载的和本次下载的
int CMYDownloadProc::GetTotalDownloadedSize()
{
	if (m_pDownloadInfo == NULL) 
	{
		return -1;
	}
	int nTotalUnDownloadBytes = 0;
	for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++ )
	{
		nTotalUnDownloadBytes += m_pMultiThreadDownloadInfo[nIndex].GetUnDownloadBytes();
	}
	int nFileSize = m_pDownloadInfo->GetFileTotalSize();
	if ( nFileSize < 1 ) 
	{
		return -1;
	}
	// 文件大小减去未完成的，就是已下载的
	return (nFileSize - nTotalUnDownloadBytes);
}

// 查找线程句柄的索引位置
int CMYDownloadProc::FindIndexByThreadHandle(HANDLE hThread)
{
	for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++)
	{
		HANDLE hTempHandle = m_pMultiThreadDownloadInfo[nIndex].GetThreadHandle();
		if ((HANDLE_IS_VALID(hTempHandle)) && (hTempHandle == hThread))
		{
			return nIndex;
		}
	}
	return -1;
}

// 等待下载结束
ENUM_DOWNLOAD_RESULT CMYDownloadProc::DoWaitForDownloadFinish()
{
	int nCount = m_nThreadCount + 1;
	HANDLE *pHandleArray = new HANDLE[nCount];
	if (pHandleArray == NULL ) 
	{
		return ENUM_DOWNLOAD_RESULT_FAILED;
	}
	ENUM_DOWNLOAD_RESULT myDownloadResult = ENUM_DOWNLOAD_RESULT_FAILED;
	int nFileTotalSize = m_pDownloadInfo->GetFileTotalSize();
	while (TRUE)
	{
		nCount = 0;
		for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++)
		{
			HANDLE hThread = m_pMultiThreadDownloadInfo[nIndex].GetThreadHandle();
			if (HANDLE_IS_VALID(hThread))
			{
				pHandleArray[nCount++] = hThread;
			}
		}
		pHandleArray[nCount++] = m_hEvtEndModule;
	
		if (nCount == 1)
		{
			if (GetTotalDownloadedSize() >= nFileTotalSize)
			{
				myDownloadResult = ENUM_DOWNLOAD_RESULT_SUCCESS;
			}
			else
			{
				myDownloadResult = ENUM_DOWNLOAD_RESULT_FAILED;
			}
			break;
		}
		int nResult = (int)WaitForMultipleObjects(nCount, pHandleArray, FALSE, INFINITE ) - WAIT_OBJECT_0;
		// 某下载对象完成任务了
		if (nResult >= 0 && nResult < nCount - 1)
		{
			int nIndex = FindIndexByThreadHandle (pHandleArray[nResult]);
			if (( nIndex >= 0) && (nIndex < m_nThreadCount))
			{
				BOOL bDownloadSuccess = m_pMultiThreadDownloadInfo[nIndex].IsDownloadSuccess();
				BOOL bDownloadTaskFlag = AttemperDownloadTask(nIndex);
				if (!bDownloadSuccess || !bDownloadTaskFlag)
				{
					m_pMultiThreadDownloadInfo[nIndex].ClearThreadHandle();
				}
			}
			else
			{
				myDownloadResult = ENUM_DOWNLOAD_RESULT_CANCEL;
				break;
			}
		}
		// 模块结束		
		else
		{
			myDownloadResult = ENUM_DOWNLOAD_RESULT_CANCEL;
			break;
		}
	}
	// 等待所有下载线程结束
	if (myDownloadResult != ENUM_DOWNLOAD_RESULT_SUCCESS)
	{
		// 等待所有下载线程结束
		nCount = 0;
		for (int nIndex = 0; nIndex < m_nThreadCount; nIndex++)
		{
			HANDLE hThread = m_pMultiThreadDownloadInfo[nIndex].GetThreadHandle();
			if (HANDLE_IS_VALID(hThread))
			{
				pHandleArray[nCount++] = hThread;
			}
		}
		WaitForMultipleObjects(nCount, pHandleArray, TRUE, 500 * 1000);
	}
	if (pHandleArray != NULL)
	{
		delete[] pHandleArray;
		pHandleArray = NULL;
	}
	return myDownloadResult;
}


// 写入调试日志
void CMYDownloadProc::WriteDebugLog(TCHAR * strMsg, ...)
{
#ifndef _DEBUG
	return;
#endif
	m_csLog.Lock();
	int nMsgMaxLen = 500;
	FILE * pFile;
	TCHAR szLog[1000] = {'\0'};
	TCHAR szMsg[1000] = {'\0'};
	TCHAR szLogFile[MAX_PATH];
	time_t theCurrentTime = time(NULL);
	tm *pThisTime = localtime(&theCurrentTime);
	_stprintf(szLogFile, _T("%slog.txt"), m_strMoudlePath.GetBuffer());
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

