#ifndef __CCHTTPREQUEST_H__
#define __CCHTTPREQUEST_H__

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "RegisterTemplate.h"
#include "curl/curl.h"

typedef size_t (*write_callback)(void *ptr, size_t size, size_t nmemb, void *stream);

class CHttpClient
{
private:
	DWORD m_dwThreadID;
	HANDLE m_hThread;
	int _timeoutForConnect;
	int _timeoutForRead;
	string m_strLocalFilePath;
	CHttpRequest *m_pHttpRequest;
	CHttpResponse *m_pHttpResponse;
public:
	CHttpClient();
	virtual ~CHttpClient();
public:
 
	static DWORD WINAPI HttpClientThread(LPVOID lpParameter);
	// 请求Http上传文件线程
	static DWORD WINAPI HttpUpFileThread(LPVOID lpParameter);
	// 请求Http下载文件线程
	static DWORD WINAPI HttpDownFileThread(LPVOID lpParameter);

	//
	VOID DoHttpClientProc();
	// Http上传文件过程
	VOID DoHttpUpFileProc();
	// Http下载文件过程
	VOID DoHttpDownFileProc();

public:
	// 请求Http
	void HttpGetRequest(const char *lpszHttpUrl);
	// 请求Http
	void HttpUpFileRequest(const char *lpszHttpUrl);
	// 请求Http下载文件
	void HttpDownFileRequest(const char *lpszHttpUrl, const char *lpszLocalFilePath);
	// 获取Http返回结果
	CHttpResponse* GetHttpResponse();
private:

	// 请求Http
	void RequestHttpClient();
	// 请求Http上传文件
	void RequestHttpUpFile();
	// 请求Http下载文件
	void RequestHttpDownFile();
private:
    
    /**
     * Change the connect timeout
     * @param timeout 
     * @return NULL
     */
    inline void setTimeoutForConnect(int value) {_timeoutForConnect = value;};
    
    /**
     * Get connect timeout
     * @return int
     *
     */
    inline int getTimeoutForConnect() {return _timeoutForConnect;}
    
    
    /**
     * Change the download timeout
     * @param timeout
     * @return NULL
     */
    inline void setTimeoutForRead(int value) {_timeoutForRead = value;};
    

    /**
     * Get download timeout
     * @return int
     */
    inline int getTimeoutForRead() {return _timeoutForRead;};
        

	// Prototypes
	bool configureCURL(CURL *handle);
	int processGetTask(CHttpRequest *request, write_callback callback, void *stream, int *errorCode);
	int processPostTask(CHttpRequest *request, write_callback callback, void *stream, int *errorCode);
	// 处理下载文件任务
	int processDownFileTask(CHttpRequest *request, write_callback callback, void *stream, int *responseCode);
};


#endif //__CCHTTPREQUEST_H__
