#include "stdafx.h"
#include "HttpClient.h"
#include <queue>

static char s_errorBuffer[CURL_ERROR_SIZE];


// Callback function used by libcurl for collect pHttpResponse data
size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::vector<char> *recvBuffer = (std::vector<char>*)stream;
    size_t sizes = size * nmemb;
    
    // add data to the end of recvBuffer
    // write data maybe called more than once in a single request
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+sizes);
    
    return sizes;
}


// Callback function used by libcurl for collect pHttpResponse data
size_t writeFileData(void *ptr, size_t size, size_t nmemb, void *stream)
{
	FILE * pFile = (FILE*)stream;
	if (pFile != NULL)
	{
		return fwrite(ptr, size, nmemb, pFile) ;
	}
	return size * nmemb;
}


CHttpClient::CHttpClient()
{
	m_dwThreadID = 0;
	m_hThread = NULL;
	m_pHttpRequest = NULL;
	m_pHttpResponse = NULL;
	_timeoutForRead = 60;
	_timeoutForConnect = 30;
}

CHttpClient::~CHttpClient()
{
	SAFE_DELETE(m_pHttpRequest);
	SAFE_DELETE(m_pHttpResponse);
}

// 
void CHttpClient::RequestHttpClient()
{    
	m_hThread = ::CreateThread (NULL, 0, HttpClientThread, LPVOID(this), 0, &m_dwThreadID);
	if (m_hThread == NULL)
	{
		return;
	}
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return;
	}
	int nResult = (int)::WaitForSingleObject(m_hThread, INFINITE) - WAIT_OBJECT_0;
}

// 请求Http上传文件
void CHttpClient::RequestHttpUpFile()
{    
	m_hThread = ::CreateThread (NULL, 0, HttpUpFileThread, LPVOID(this), 0, &m_dwThreadID);
	if (m_hThread == NULL)
	{
		return;
	}
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return;
	}
	int nResult = (int)::WaitForSingleObject(m_hThread, INFINITE) - WAIT_OBJECT_0;
}



// 请求Http下载文件
void CHttpClient::RequestHttpDownFile()
{    
	m_hThread = ::CreateThread (NULL, 0, HttpDownFileThread, LPVOID(this), 0, &m_dwThreadID);
	if (m_hThread == NULL)
	{
		return;
	}
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return;
	}
	int nResult = (int)::WaitForSingleObject(m_hThread, INFINITE) - WAIT_OBJECT_0;
}


// 请求Http
void CHttpClient::HttpGetRequest(const char *lpszHttpUrl)
{
	m_pHttpRequest = new CHttpRequest();
	m_pHttpRequest->setUrl(lpszHttpUrl);
	m_pHttpRequest->setRequestType(CHttpRequest::kHttpGet);
	m_pHttpRequest->setTag("GET test1");
	//
	this->RequestHttpClient();
}


// 请求Http
void CHttpClient::HttpUpFileRequest(const char *lpszHttpUrl)
{
	m_pHttpRequest = new CHttpRequest();
	m_pHttpRequest->setUrl(lpszHttpUrl);
	m_pHttpRequest->setRequestType(CHttpRequest::kHttpPost);
	m_pHttpRequest->setTag("POST test1");
	//
	this->RequestHttpUpFile();
}


// 请求Http下载文件
void CHttpClient::HttpDownFileRequest(const char *lpszHttpUrl, const char *lpszLocalFilePath)
{
	m_strLocalFilePath = lpszLocalFilePath;
	m_pHttpRequest = new CHttpRequest();
	m_pHttpRequest->setUrl(lpszHttpUrl);
	m_pHttpRequest->setRequestType(CHttpRequest::kHttpPost);
	m_pHttpRequest->setTag("POST test1");
	//
	this->RequestHttpDownFile();
}

// 获取Http返回结果
CHttpResponse* CHttpClient::GetHttpResponse()
{
	return m_pHttpResponse;
}


DWORD WINAPI CHttpClient::HttpClientThread(LPVOID lpParameter)
{
	CHttpClient *pHttpClient = (CHttpClient*)lpParameter;
	pHttpClient->DoHttpClientProc();
	//SAFE_DELETE(pHttpClient);
	return 1;
}

// 请求Http上传文件线程
DWORD WINAPI CHttpClient::HttpUpFileThread(LPVOID lpParameter)
{
	CHttpClient *pHttpClient = (CHttpClient*)lpParameter;
	pHttpClient->DoHttpUpFileProc();
	return 1;
}

// 请求Http下载文件线程
DWORD WINAPI CHttpClient::HttpDownFileThread(LPVOID lpParameter)
{
	CHttpClient *pHttpClient = (CHttpClient*)lpParameter;
	pHttpClient->DoHttpDownFileProc();
	return 1;
}

VOID CHttpClient::DoHttpClientProc()
{
	//
	m_pHttpResponse = new CHttpResponse(m_pHttpRequest);
	//
	int responseCode = -1;
	//
	int retValue = 0;
	//
	switch (m_pHttpRequest->getRequestType())
	{
	case CHttpRequest::kHttpGet: // HTTP GET
		{
			retValue = processGetTask
				(
				m_pHttpRequest 
				, writeData 
				, m_pHttpResponse->getResponseData() 
				, &responseCode
				);
			break;
		}

	case CHttpRequest::kHttpPost: // HTTP POST
		{
			retValue = processPostTask
				(
				m_pHttpRequest
				, writeData 
				, m_pHttpResponse->getResponseData() 
				, &responseCode
				);
			break;
		}
	default:
		{
			break;
		}
	}
	// write data to HttpResponse
	m_pHttpResponse->setResponseCode(responseCode);
	//
	if (retValue != 0) 
	{
		m_pHttpResponse->setSucceed(false);
		m_pHttpResponse->setErrorBuffer(s_errorBuffer);
	}
	else
	{
		m_pHttpResponse->setSucceed(true);
	}
}

// Http上传文件过程
VOID CHttpClient::DoHttpUpFileProc()
{
	//
	m_pHttpResponse = new CHttpResponse(m_pHttpRequest);
	//
	int responseCode = -1;
	//
	int retValue = 0;
	//
	switch (m_pHttpRequest->getRequestType())
	{
	case CHttpRequest::kHttpGet: // HTTP GET
		{
			retValue = processGetTask
				(
				m_pHttpRequest 
				, writeData 
				, m_pHttpResponse->getResponseData() 
				, &responseCode
				);
			break;
		}

	case CHttpRequest::kHttpPost: // HTTP POST
		{
			retValue = processPostTask
				(
				m_pHttpRequest
				, writeData 
				, m_pHttpResponse->getResponseData() 
				, &responseCode
				);
			break;
		}
	default:
		{
			break;
		}
	}
	// write data to HttpResponse
	m_pHttpResponse->setResponseCode(responseCode);
	//
	if (retValue != 0) 
	{
		m_pHttpResponse->setSucceed(false);
		m_pHttpResponse->setErrorBuffer(s_errorBuffer);
	}
	else
	{
		m_pHttpResponse->setSucceed(true);
	}
}

// Http下载文件过程
VOID CHttpClient::DoHttpDownFileProc()
{
	//
	m_pHttpResponse = new CHttpResponse(m_pHttpRequest);
	//
	int responseCode = -1;
	//
	FILE * pFile = fopen(m_strLocalFilePath.c_str(), "ab" );
	//
	int nReturn = processDownFileTask
		(
		m_pHttpRequest 
		, writeFileData 
		, pFile
		, &responseCode
		);
	// write data to HttpResponse
	m_pHttpResponse->setResponseCode(responseCode);
	//
	if (nReturn != 0) 
	{
		m_pHttpResponse->setSucceed(false);
		m_pHttpResponse->setErrorBuffer(s_errorBuffer);
	}
	else
	{
		m_pHttpResponse->setSucceed(true);
	}
}


//Configure curl's timeout property
bool CHttpClient::configureCURL(CURL *handle)
{
	if (!handle) 
	{
		return false;
	}

	int code;
	code = curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, s_errorBuffer);
	if (code != CURLE_OK) {
		return false;
	}
	code = curl_easy_setopt(handle, CURLOPT_TIMEOUT, this->getTimeoutForRead());
	if (code != CURLE_OK) {
		return false;
	}
	code = curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, this->getTimeoutForConnect());
	if (code != CURLE_OK) {
		return false;
	}

	return true;
}

//Process Get Request
int CHttpClient::processGetTask(CHttpRequest *request, write_callback callback, void *stream, int *responseCode)
{
	CURLcode code = CURL_LAST;
	CURL *curl = curl_easy_init();

	do {
		if (!configureCURL(curl)) 
		{
			break;
		}

		code = curl_easy_setopt(curl, CURLOPT_URL, request->getUrl());
		if (code != CURLE_OK) 
		{
			break;
		}

		code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, request->getUrl());
		if (code != CURLE_OK)
		{
			break;
		}

		code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
		if (code != CURLE_OK) 
		{
			break;
		}

		code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, stream);
		if (code != CURLE_OK) 
		{
			break;
		}

		code = curl_easy_perform(curl);
		if (code != CURLE_OK) 
		{
			break;
		}

		code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, responseCode); 
		if (code != CURLE_OK || *responseCode != 200) 
		{
			code = CURLE_HTTP_RETURNED_ERROR;
		}
	} while (0);

	if (curl) {
		curl_easy_cleanup(curl);
	}

	return (code == CURLE_OK ? 0 : 1);
}

//Process POST Request
int CHttpClient::processPostTask(CHttpRequest *request, write_callback callback, void *stream, int *responseCode)
{
	CURLcode code = CURL_LAST;
	CURL *curl = curl_easy_init();

	do {
		if (!configureCURL(curl)) {
			break;
		}

		code = curl_easy_setopt(curl, CURLOPT_URL, request->getUrl());
		if (code != CURLE_OK) {
			break;
		}
		code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
		if (code != CURLE_OK) {
			break;
		}
		code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, stream);
		if (code != CURLE_OK) {
			break;
		}
		code = curl_easy_setopt(curl, CURLOPT_POST, 1);
		if (code != CURLE_OK) {
			break;
		}
		code = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request->getRequestData());
		if (code != CURLE_OK) {
			break;
		}
		code = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, request->getRequestDataSize());
		if (code != CURLE_OK) {
			break;
		}
		code = curl_easy_perform(curl);
		if (code != CURLE_OK) {
			break;
		}

		code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, responseCode); 
		if (code != CURLE_OK || *responseCode != 200) {
			code = CURLE_HTTP_RETURNED_ERROR;
		}
	} while (0);
	if (curl) {
		curl_easy_cleanup(curl);
	}

	return (code == CURLE_OK ? 0 : 1);    
}


// 处理下载文件任务
int CHttpClient::processDownFileTask(CHttpRequest *request, write_callback callback, void *stream, int *responseCode)
{
	CURLcode code = CURL_LAST;

	CURL *curl = curl_easy_init();

	do
	{
		if (!configureCURL(curl))
		{
			break;
		}
		code = curl_easy_setopt(curl, CURLOPT_URL, request->getUrl());
		if (code != CURLE_OK) 
		{
			break;
		}
		code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
		if (code != CURLE_OK)
		{
			break;
		}
		code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, stream);
		if (code != CURLE_OK) 
		{
			break;
		}
		// curl的进度条声明 　　
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
		code = curl_easy_perform(curl);
		if (code != CURLE_OK) {
			break;
		}
		code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, responseCode); 
		if (code != CURLE_OK || *responseCode != 200) 
		{
			code = CURLE_HTTP_RETURNED_ERROR;
		}
	} while (0);
	if (curl) {
		curl_easy_cleanup(curl);
	}

	return (code == CURLE_OK ? 0 : 1);    
}

