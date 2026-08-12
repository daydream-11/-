#pragma once


#include "BaseDownload.h"
#include "RegisterTemplate.h"

class CDownloadInterface
	: public VectorRegister<IDownloadProcEvent>
{
protected:
	CString m_strDownloadURL;
	CString m_strSaveFileName;

public:
	CDownloadInterface(void);
public:
	virtual ~CDownloadInterface(void);
public:
	//
	virtual BOOL Init();
	// 
	virtual BOOL DoDownloadFile(const TCHAR * strDownloadUrl, const TCHAR * strSaveFileName);
	// 
	virtual BOOL DoWaitDownloadFile(const TCHAR * strDownloadUrl, const TCHAR * strSaveFileName);
	// 请求http 文件时间
	virtual BOOL DoRequestHttpFileTime(const TCHAR * strHttpFileName, TCHAR * strReturnTime);
	// 请求http 文件内容
	virtual CHAR* DoRequestHttpPageContent(const TCHAR * strHttpFileName);
	// 设置重试次数
	virtual VOID SetRetryTimes(int nRetryTimes);
	// 设置循环下载暂停时间
	virtual VOID SetRetryTimesSleepMilliSecond(int nRetryTimesSleepMilliSecond);
protected:
	// 设置下载的文件大小
	void OnSetDownloadFileSize(int nDownloadFileSize);
	// 设置已经下载的大小
	void OnSetAlreadyDownloadSize(int nAlreadyDownloadSize);
	// 设置当前下载速度
	void OnSetCurrentDownloadSpeed(float fCurrentDownloadSpeed);
	// 设置已经下载完成
	void OnSetDownloadFinish();
	// 设置已经下载失败
	void OnSetDownloadFail();
};
