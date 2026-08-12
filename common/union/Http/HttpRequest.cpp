#include "StdAfx.h"
#include "HttpRequest.h"
#include "Wininet.h"
#pragma comment (lib,"Wininet.lib")

/** @name 构造和虚构函数 */////////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： CHttpRequest
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/05/15		V1.0	    huanggenping	创建版本
***********************************************************************/
CHttpRequest::CHttpRequest(void)
{

}

/**********************************************************************
* 函数名称： ~CHttpRequest
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/05/15		V1.0	    huanggenping	创建版本
***********************************************************************/
CHttpRequest::~CHttpRequest(void)
{

}

/// @}

/** @name 公共成员函数 *///////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： InitHttpRequest
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
void CHttpRequest::InitHttpRequest(void)
{
	m_hSession = NULL;
	m_hConnect = NULL;
	m_hRequest = NULL;
	m_strBoundary = _T("---------------------------7d9138187173a");
}

/**********************************************************************
* 函数名称： AddHttpRequestHeaders
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CHttpRequest::AddHttpRequestHeaders(UINT uType)
{
	BOOL bFlag = FALSE;
	TCHAR szRequestHeader[500] = {'\0'};
	// 
	_tcscpy(szRequestHeader, _T("Accept: */*\r\n"));
	bFlag = ::HttpAddRequestHeaders(m_hRequest, szRequestHeader, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	// 
	_tcscpy(szRequestHeader, _T("Referer: http://user.gswubi.com/client/temp.htm"));
	bFlag = ::HttpAddRequestHeaders(m_hRequest, szRequestHeader, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	// 
	_tcscpy(szRequestHeader, _T("Accept-Language: zh-cn\r\n"));
	bFlag = ::HttpAddRequestHeaders(m_hRequest, szRequestHeader, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	//
	switch(uType)
	{
	case 0:
	    _stprintf(szRequestHeader, _T("Content-Type: application/x-www-form-urlencoded\r\n"));
		break;
	case 1:
		_stprintf(szRequestHeader, _T("Content-Type: multipart/form-data; boundary=---------------------------7d99c1b1055e\r\n"));
		break;
	}
	bFlag = ::HttpAddRequestHeaders(m_hRequest, szRequestHeader, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	// 
	_tcscpy(szRequestHeader, _T("UA-CPU: x86\r\n"));
	bFlag = ::HttpAddRequestHeaders(m_hRequest, szRequestHeader, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	//
	_tcscpy(szRequestHeader, _T("Accept-Encoding: gzip, deflate\r\n"));
	bFlag = ::HttpAddRequestHeaders(m_hRequest, szRequestHeader, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	// 
	_tcscpy(szRequestHeader, _T("User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.2; SV1; Maxthon; .NET CLR 1.1.4322; .NET CLR 2.0.50727)\r\n"));
	bFlag = ::HttpAddRequestHeaders(m_hRequest, szRequestHeader, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	// 
	_stprintf(szRequestHeader, _T("%s"), _T("Host: user.gswubi.com\r\n"));
	bFlag = ::HttpAddRequestHeaders(m_hRequest, szRequestHeader, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	// 

	_tcscpy(szRequestHeader, _T("Connection: Keep-Alive\r\n"));
	bFlag = ::HttpAddRequestHeaders(m_hRequest, szRequestHeader, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	//
	_tcscpy(szRequestHeader, _T("Cache-Control: no-cache"));
	bFlag = ::HttpAddRequestHeaders(m_hRequest, szRequestHeader, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
	if (!bFlag)
	{
		ClearHInternet();
		return FALSE;
	}
	return TRUE;
}

/**********************************************************************
* 函数名称： OpenHInternet
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CHttpRequest::OpenHInternet()
{
	m_hSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (m_hSession == NULL)
	{
		ClearHInternet();
		return FALSE;
	}
	m_hConnect = InternetConnect(m_hSession, m_strDomainName, INTERNET_DEFAULT_HTTP_PORT, NULL,  NULL, INTERNET_SERVICE_HTTP, 0, 0);
	if (m_hConnect == NULL)
	{
		ClearHInternet();
		return FALSE;
	}
	m_hRequest = HttpOpenRequest(m_hConnect,  m_strMethodType,  m_strPageUrl, NULL, NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if (m_hRequest == NULL)
	{
		ClearHInternet();
		return FALSE;
	}
	return TRUE;
}

/**********************************************************************
* 函数名称： OnSendHttpRequest
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CHttpRequest::OnSendHttpRequest(const char * pszSendData)
{
	int nDataLen = (int)strlen(pszSendData);
	INTERNET_BUFFERS myInternetBuffers;   
	myInternetBuffers.dwStructSize = sizeof(INTERNET_BUFFERS);  
	myInternetBuffers.Next = NULL;    
	myInternetBuffers.lpcszHeader = NULL;   
	myInternetBuffers.dwHeadersLength = 0;   
	myInternetBuffers.dwHeadersTotal = 0;   
	myInternetBuffers.lpvBuffer = NULL;                   
	myInternetBuffers.dwBufferLength = 0;  
	myInternetBuffers.dwBufferTotal = nDataLen;  
	myInternetBuffers.dwOffsetLow = 0;   
	myInternetBuffers.dwOffsetHigh = 0;  
	BOOL bFlag = ::HttpSendRequestEx(m_hRequest,&myInternetBuffers, NULL, 0, 2);
	if (!bFlag)
	{
		return FALSE;
	}
	DWORD dwNumberOfBytesWritten = 0;
	int nIntervalByte = 1024;
	int nSpareByte = nDataLen;
	int nAlreadyWriteByte = 0;
	while (nAlreadyWriteByte < nDataLen)
	{
		DWORD dwNumberOfBytesToWrite = nDataLen - nAlreadyWriteByte;
		bFlag = ::InternetWriteFile(m_hRequest, pszSendData + nAlreadyWriteByte, dwNumberOfBytesToWrite, &dwNumberOfBytesWritten);
		nAlreadyWriteByte += dwNumberOfBytesWritten;
	}
	HttpEndRequest(m_hRequest, NULL, 0, 2);
	return TRUE;
}

/**********************************************************************
* 函数名称： OnGetHttpRequest
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
char * CHttpRequest::OnGetHttpRequest()
{
	HTTPINFO myHttpInfo;
	LPBYTE			lpData			= NULL;
	DWORD			dwSize			= 0;
	DWORD			dwRet			= 0;
	DWORD			dwByteRead		= 0;
	DWORD			dwContentLen	= 0;
	DWORD			dwByteAvailable = 0;
	DWORD			dwMaxBuffer		= 0;
	BOOL bFlag = FALSE;

	dwSize = sizeof(myHttpInfo.strContentType);
	HttpQueryInfo(m_hRequest, HTTP_QUERY_CONTENT_TYPE, &myHttpInfo.strContentType, &dwSize, 0); 
	dwSize = sizeof(myHttpInfo.strContentLength);
	HttpQueryInfo(m_hRequest, HTTP_QUERY_CONTENT_LENGTH, &myHttpInfo.strContentLength, &dwSize, 0); 
	dwSize = sizeof(myHttpInfo.strQueryDate);
	HttpQueryInfo(m_hRequest, HTTP_QUERY_DATE, &myHttpInfo.strQueryDate, &dwSize, 0);   
	dwSize = sizeof(myHttpInfo.strServer);
	HttpQueryInfo(m_hRequest, HTTP_QUERY_SERVER, &myHttpInfo.strServer, &dwSize, 0);   
	dwSize = sizeof(myHttpInfo.strStatusCode);
	HttpQueryInfo(m_hRequest, HTTP_QUERY_STATUS_CODE, &myHttpInfo.strStatusCode, &dwSize, 0);  
	dwSize = sizeof(myHttpInfo.strStatusText);
	HttpQueryInfo(m_hRequest, HTTP_QUERY_STATUS_TEXT, &myHttpInfo.strStatusText, &dwSize, 0);
	DWORD dwStatusCode = _ttoi(myHttpInfo.strStatusCode);
	if (dwStatusCode != 200)
	{
		ClearHInternet();
		return 0;
	}
	DWORD dwLength = 0;
	DWORD dwLengthSize = sizeof(dwLength);
	HttpQueryInfo(m_hRequest, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER ,&dwLength, &dwLengthSize,NULL);
	dwMaxBuffer = dwLength + 1;
	char * pOutput = new char[dwMaxBuffer * 2];
	memset(pOutput, 0, sizeof(pOutput));
	
	while (InternetQueryDataAvailable(m_hRequest, &dwByteAvailable, 0, 0))
	{
		if (dwByteAvailable > 0)
		{
			dwContentLen += dwByteAvailable;
			lpData = (LPBYTE)LocalAlloc(LPTR, dwByteAvailable + 1);
			dwRet = InternetReadFile(m_hRequest, lpData, dwByteAvailable, &dwByteRead);
			if (((long)strlen((LPSTR)pOutput) + (long)dwByteAvailable) < dwMaxBuffer)
			{
				strncat((LPSTR)pOutput, (LPSTR)lpData, dwByteAvailable);
			}
			if (lpData != NULL) 
			{
				LocalFree((LPBYTE)lpData);
			}
			lpData = NULL;
		}
		else
		{
			break;
		}
	}
	ClearHInternet();

	return pOutput;
}

/**********************************************************************
* 函数名称： DoUploadConfig
* 功能描述： 上传配置文件
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
const char * CHttpRequest::DoUploadConfig(const char * pszUpCfgData)
{
	BOOL bFlag = FALSE;
	bFlag = OpenHInternet();
	if (!bFlag)
	{
		return NULL;
	}
	bFlag = AddHttpRequestHeaders(1);
	if (!bFlag)
	{
		return NULL;
	}
	bFlag = OnSendHttpRequest(pszUpCfgData);
	if (!bFlag)
	{
		return NULL;
	}
	return OnGetHttpRequest();

}

//
void CHttpRequest::SetUserID(int nUserID)
{
	m_nUserID = nUserID;
}

//获取安全码
const char * CHttpRequest::DoRequestCode(void)
{
	BOOL bFlag = FALSE;
	bFlag = OpenHInternet();
	if (!bFlag)
	{
		return NULL;
	}
	bFlag = AddHttpRequestHeaders();
	if (!bFlag)
	{
		return NULL;
	}
	
	char * pszSendData = new char[1024];	
	sprintf(pszSendData, "userid=%d\r\n", m_nUserID);
	bFlag = OnSendHttpRequest(pszSendData);
	if (!bFlag)
	{
		return NULL;
	}
	delete[] pszSendData;
	pszSendData = NULL;
	return OnGetHttpRequest();
}

/**********************************************************************
* 函数名称： SetDomainName
* 功能描述： 设置连接的域名
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
void CHttpRequest::SetDomainName(const TCHAR * pszDomainName)
{
	_stprintf(m_strDomainName, _T("%s"), pszDomainName);
}

/**********************************************************************
* 函数名称： SetMethodType
* 功能描述： 设置连接的类型
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
void CHttpRequest::SetMethodType(const TCHAR * pszMethodType)
{
	_stprintf(m_strMethodType, _T("%s"), pszMethodType);
}

/**********************************************************************
* 函数名称： SetPageUrl
* 功能描述： 设置连接的页面链接
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
void CHttpRequest::SetPageUrl(const TCHAR * pszPageUrl)
{
	_stprintf(m_strPageUrl, _T("%s"), pszPageUrl);
}

/**********************************************************************
* 函数名称： ClearHInternet
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
void CHttpRequest::ClearHInternet()
{
	if (m_hSession != NULL)
	{
		InternetCloseHandle(m_hSession);
		m_hSession = NULL;
	}
	if (m_hConnect != NULL)
	{
		InternetCloseHandle(m_hConnect);
		m_hConnect = NULL;
	}
	if (m_hRequest != NULL)
	{
		InternetCloseHandle(m_hRequest);
		m_hRequest = NULL;
	}
}

/**********************************************************************
* 函数名称： SetWnShareDlg
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/16		V1.0	    huanggenping	创建版本
***********************************************************************/
void CHttpRequest::SetWnShareDlg(CShareDlg *pWnShareDlg)
{
	m_pWnShareDlg = pWnShareDlg;
}

/// @}
