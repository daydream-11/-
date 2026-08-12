#include "framework.h"
#include "HttpPageClient.h"
#include <queue>

static char s_errorBuffer[CURL_ERROR_SIZE];


// Callback function used by libcurl for collect pHttpPageResponse data
size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream)
{
	std::vector<char> *recvBuffer = (std::vector<char>*)stream;
    size_t sizes = size * nmemb;
    
    // add data to the end of recvBuffer
    // write data maybe called more than once in a single request
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+sizes);
	//
    return sizes;
}


CHttpPageClient::CHttpPageClient()
{
	m_dwThreadID = 0;
	m_hThread = NULL;
	m_pHttpPageRequest = NULL;
	m_pHttpPageResponse = NULL;
	_timeoutForRead = 60;
	_timeoutForConnect = 30;
}

CHttpPageClient::~CHttpPageClient()
{
	SAFE_DELETE(m_pHttpPageRequest);
	SAFE_DELETE(m_pHttpPageResponse);

	if (m_hThread)
		CloseHandle(m_hThread);
		
}

// 
void CHttpPageClient::RequestHttpPageClient()
{    
	m_hThread = ::CreateThread (NULL, 0, HttpPageClientThread, LPVOID(this), 0, &m_dwThreadID);
	if (m_hThread == NULL)
	{
		return;
	}
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return;
	}
	int nResult = (int)::WaitForSingleObject(m_hThread, INFINITE) - WAIT_OBJECT_0;
	//CloseHandle(m_hThread);
}

// 请求Http上传文件
void CHttpPageClient::RequestHttpUpFile()
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
	//CloseHandle(m_hThread);
}

// 设置POST 数据
void CHttpPageClient::SetPostVectorData(_tagUrlRequestData &data)
{
	m_vtCurlRequest.push_back(data);
}

// 请求Http
void CHttpPageClient::HttpGetRequest(const char *lpszHttpUrl)
{
	m_pHttpPageRequest = new CHttpPageRequest();
	m_pHttpPageRequest->setUrl(lpszHttpUrl);
	m_pHttpPageRequest->setRequestType(CHttpPageRequest::kHttpPost);
	m_pHttpPageRequest->setTag("GET test1");
	//
	this->RequestHttpPageClient();
}


// 请求Http
void CHttpPageClient::SendHttpRequestByGet(const char *lpszHttpUrl)
{
	m_pHttpPageRequest = new CHttpPageRequest();
	m_pHttpPageRequest->setUrl(lpszHttpUrl);
	m_pHttpPageRequest->setRequestType(CHttpPageRequest::kHttpGet);
	m_pHttpPageRequest->setTag("GET test1");
	//
	this->RequestHttpPageClient();
}

// 请求Http
void CHttpPageClient::HttpUpFileRequest(const char *lpszHttpUrl, const char *lpszFilePath, const char *lpszUseraID, const char *lpszPlateForm)
{
	m_strUpFile = lpszFilePath;
	m_strUserID = lpszUseraID;
	m_strPlateForm = lpszPlateForm;
	m_pHttpPageRequest = new CHttpPageRequest();
	m_pHttpPageRequest->setUrl(lpszHttpUrl);
	m_pHttpPageRequest->setRequestType(CHttpPageRequest::kHttpPost);
	m_pHttpPageRequest->setTag("POST test1");
	//
	this->RequestHttpUpFile();
}

// 获取Http返回结果
CHttpPageResponse* CHttpPageClient::GetHttpPageResponse()
{
	return m_pHttpPageResponse;
}


DWORD WINAPI CHttpPageClient::HttpPageClientThread(LPVOID lpParameter)
{
	CHttpPageClient *pHttpPageClient = (CHttpPageClient*)lpParameter;
	pHttpPageClient->DoHttpPageClientProc();
	return 1;
}


// 请求Http上传文件线程
DWORD WINAPI CHttpPageClient::HttpUpFileThread(LPVOID lpParameter)
{
	CHttpPageClient *pHttpPageClient = (CHttpPageClient*)lpParameter;
	pHttpPageClient->DoHttpUpFileProc();
	return 1;
}


VOID CHttpPageClient::DoHttpPageClientProc()
{
	//
	m_pHttpPageResponse = new CHttpPageResponse(m_pHttpPageRequest);
	//
	int responseCode = -1;
	//
	int retValue = 0;
	//
	switch (m_pHttpPageRequest->getRequestType())
	{
	case CHttpPageRequest::kHttpGet: // HTTP GET
		{
			retValue = processGetTask(
				m_pHttpPageRequest 
				, writeData 
				, m_pHttpPageResponse->getResponseData() 
				, &responseCode
				);
			break;
		}

	case CHttpPageRequest::kHttpPost: // HTTP POST
		{
			retValue = processPostTask
				(
				m_pHttpPageRequest
				, writeData 
				, m_pHttpPageResponse->getResponseData() 
				, &responseCode

				);
			break;
		}
	default:
		{
			break;
		}
	}
	// write data to HttpPageResponse
	m_pHttpPageResponse->setResponseCode(responseCode);
	//
	if (retValue != 0) 
	{
		m_pHttpPageResponse->setSucceed(false);
		m_pHttpPageResponse->setErrorBuffer(s_errorBuffer);
	}
	else
	{
		m_pHttpPageResponse->setSucceed(true);
	}
}

VOID CHttpPageClient::DoHttpUpFileProc()
{
	//
	m_pHttpPageResponse = new CHttpPageResponse(m_pHttpPageRequest);
	//
	int responseCode = -1;
	//
	int retValue = 0;
	//
	switch (m_pHttpPageRequest->getRequestType())
	{
	case CHttpPageRequest::kHttpGet: // HTTP GET
		{
			retValue = processGetTask
				(
				m_pHttpPageRequest 
				, writeData 
				, m_pHttpPageResponse->getResponseData() 
				, &responseCode
				);
			break;
		}

	case CHttpPageRequest::kHttpPost: // HTTP POST
		{
			retValue = processPostUpFileTask
				(
				m_pHttpPageRequest
				, writeData 
				, m_pHttpPageResponse->getResponseData() 
				, &responseCode
				);
			break;
		}
	default:
		{
			break;
		}
	}
	// write data to HttpPageResponse
	m_pHttpPageResponse->setResponseCode(responseCode);
	//
	if (retValue != 0) 
	{
		m_pHttpPageResponse->setSucceed(false);
		m_pHttpPageResponse->setErrorBuffer(s_errorBuffer);
	}
	else
	{
		m_pHttpPageResponse->setSucceed(true);
	}
}



//Configure curl's timeout property
bool CHttpPageClient::configureCURL(CURL *handle)
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
int CHttpPageClient::processGetTask(CHttpPageRequest *request, write_callback callback, void *stream, int *responseCode)
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
int CHttpPageClient::processPostTask(CHttpPageRequest *request, write_callback callback, void *stream, int *responseCode)
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
		//
		struct curl_httppost *formpost = 0;
		struct curl_httppost *lastptr  = 0;
		
		for (UINT i = 0; i < m_vtCurlRequest.size(); i++)
		{
			_tagUrlRequestData data = m_vtCurlRequest[i];
			curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, data.strField.c_str(), CURLFORM_COPYCONTENTS, data.strValue.c_str(), CURLFORM_END);
		}
		
		//
		code = curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
		//
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
		//
		curl_formfree(formpost);
		//
	} while (0);
	if (curl) {
		curl_easy_cleanup(curl);
	}

	return (code == CURLE_OK ? 0 : 1);    
}


int CHttpPageClient::processPostUpFileTask(CHttpPageRequest *request, write_callback callback, void *stream, int *responseCode)
{
	CHAR szTempCode[500];
	char szCode[MAX_PATH] = {'\0'};
	char szTime[MAX_PATH] = {'\0'};
	INT nTime = time(NULL);
	//
	sprintf_s(szTime, "%d%", nTime);
	//
	sprintf_s(szTempCode, "UserID=%s&Time=%s&Platform=%s", m_strUserID.c_str(), szTime, m_strPlateForm.c_str());
	MD5 myMD5(szTempCode);
	strcpy_s(szCode, myMD5.toString().c_str());
	//
	CURLcode code = CURL_LAST;
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl = curl_easy_init();
	// 
	do 
	{
		if (!configureCURL(curl)) 
		{
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
		//
		struct curl_httppost *formpost = 0;
		struct curl_httppost *lastptr  = 0;
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "userid", CURLFORM_COPYCONTENTS, m_strUserID.c_str(), CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "platform", CURLFORM_COPYCONTENTS, m_strPlateForm.c_str(), CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "time", CURLFORM_COPYCONTENTS, szTime, CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "code", CURLFORM_COPYCONTENTS, szCode, CURLFORM_END);
		//
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "file", CURLFORM_FILE, m_strUpFile.c_str(), CURLFORM_END);
		//
		//curl_easy_setopt(curl, CURLOPT_URL, request->getUrl());
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
		//
		if (code != CURLE_OK) 
		{
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
		//
		curl_formfree(formpost);
		//curl_formfree(lastptr);
	} while (0);
	if (curl) {
		curl_easy_cleanup(curl);
	}

	return (code == CURLE_OK ? 0 : 1);    
}