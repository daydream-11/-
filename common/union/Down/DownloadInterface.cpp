#include "stdafx.h"
#include "Export.h"
#include "DownloadInterface.h"

CDownloadInterface::CDownloadInterface(void)
	: m_strDownloadURL(_T(""))
	, m_strSaveFileName(_T(""))
{

}

CDownloadInterface::~CDownloadInterface(void)
{

}

BOOL CDownloadInterface::Init()
{
	return TRUE;
}

// 
BOOL CDownloadInterface::DoDownloadFile(const TCHAR * strDownloadUrl, const TCHAR * strSaveFileName)
{
	m_strDownloadURL = strDownloadUrl;
	m_strSaveFileName = strSaveFileName;
	return TRUE;
}

// 
BOOL CDownloadInterface::DoWaitDownloadFile(const TCHAR * strDownloadUrl, const TCHAR * strSaveFileName)
{
	m_strDownloadURL = strDownloadUrl;
	m_strSaveFileName = strSaveFileName;
	return TRUE;
}


// 请求http 文件时间
BOOL CDownloadInterface::DoRequestHttpFileTime(const TCHAR * strHttpFileName, TCHAR * strReturnTime)
{
	return TRUE;
}


// 请求http 文件内容
CHAR* CDownloadInterface::DoRequestHttpPageContent(const TCHAR * strHttpFileName)
{
	return NULL;
}


// 设置重试次数
VOID CDownloadInterface::SetRetryTimes(int nRetryTimes)
{

}

// 设置循环下载暂停时间
VOID CDownloadInterface::SetRetryTimesSleepMilliSecond(int nRetryTimesSleepMilliSecond)
{

}

// 设置需要下载的大小
void CDownloadInterface::OnSetDownloadFileSize(int nDownloadFileSize)
{
	IDownloadProcEvent *pEventDelegate(NULL);
	TVectorRegContainer::iterator iter = m_vectorRegContainer.begin();
	TVectorRegContainer::iterator iEnd = m_vectorRegContainer.end();
	for (; iter != iEnd; ++iter) {
		if (NULL == *iter) {
			continue ;
		}
		pEventDelegate = (IDownloadProcEvent *)*iter;
		pEventDelegate->OnSetDownloadFileSize(nDownloadFileSize);
	}
}



// 设置已经下载的大小
void CDownloadInterface::OnSetAlreadyDownloadSize(int nAlreadyDownloadSize)
{
	IDownloadProcEvent *pEventDelegate(NULL);
	TVectorRegContainer::iterator iter = m_vectorRegContainer.begin();
	TVectorRegContainer::iterator iEnd = m_vectorRegContainer.end();
	for (; iter != iEnd; ++iter) {
		if (NULL == *iter) {
			continue ;
		}
		pEventDelegate = (IDownloadProcEvent *)*iter;
		pEventDelegate->OnSetAlreadyDownloadSize(nAlreadyDownloadSize);
	}
}

// 设置当前下载速度
void CDownloadInterface::OnSetCurrentDownloadSpeed(float fCurrentDownloadSpeed)
{
	IDownloadProcEvent *pEventDelegate(NULL);
	TVectorRegContainer::iterator iter = m_vectorRegContainer.begin();
	TVectorRegContainer::iterator iEnd = m_vectorRegContainer.end();
	for (; iter != iEnd; ++iter) {
		if (NULL == *iter) {
			continue ;
		}
		pEventDelegate = (IDownloadProcEvent *)*iter;
		pEventDelegate->OnSetCurrentDownloadSpeed(fCurrentDownloadSpeed);
	}
}

// 设置已经下载完成
void CDownloadInterface::OnSetDownloadFinish()
{
	IDownloadProcEvent *pEventDelegate(NULL);
	TVectorRegContainer::iterator iter = m_vectorRegContainer.begin();
	TVectorRegContainer::iterator iEnd = m_vectorRegContainer.end();
	for (; iter != iEnd; ++iter) {
		if (NULL == *iter) {
			continue ;
		}
		pEventDelegate = (IDownloadProcEvent *)*iter;
		pEventDelegate->OnSetDownloadFinish();
	}
}



// 设置已经下载失败
void CDownloadInterface::OnSetDownloadFail()
{
	IDownloadProcEvent *pEventDelegate(NULL);
	TVectorRegContainer::iterator iter = m_vectorRegContainer.begin();
	TVectorRegContainer::iterator iEnd = m_vectorRegContainer.end();
	for (; iter != iEnd; ++iter) {
		if (NULL == *iter) {
			continue ;
		}
		pEventDelegate = (IDownloadProcEvent *)*iter;
		pEventDelegate->OnSetDownloadFail();
	}
}