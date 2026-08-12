#pragma once

#include "DownloadInfo.h"

class CDownloadHttp : public CDownloadInfo
{
public:
	CDownloadHttp(void);
	~CDownloadHttp(void);
public:
	//
	// 获取远程站点信息，如：是否支持断点续传、要下载的文件大小和创建时间等
	//
	virtual int GetRemoteSitePro();
	virtual BOOL DownloadOnce();
	// 下载页面内容
	virtual BOOL DownloadPageContent();
	CString FindAfterFlagString(LPCTSTR strFoundValue, CString strOrgValue);
	CString GetContentDispositionFileName(CString strContentDisposition);
	BOOL ParseResponseString(CString strResponseValue, BOOL &bRetryRequest);
	DWORD GetResponseCode(CString strLineValue);
	BOOL SendRequest ( LPCTSTR lpszReq, OUT CString &csResponse, char *szTailData=NULL, int *pnTailSize=NULL );
	CString GetRequestStr ( BOOL bGet );
	int RequestHttpData(BOOL bGet, char * szTailData = NULL, int * pnTailSize = NULL);
public:
	CTime ConvertHttpTimeString(CString strTimeGMT);
};
