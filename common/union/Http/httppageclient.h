#ifndef __HTTP_PAGE_CLIENT_H__
#define __HTTP_PAGE_CLIENT_H__

#include "HttpPageRequest.h"
#include "HttpPageResponse.h"
#include "../Curl/curl.h"

typedef size_t (*write_callback)(void *ptr, size_t size, size_t nmemb, void *stream);

struct _tagUrlRequestData
{
	string strField;
	string strValue;
	//
	_tagUrlRequestData()
	{
		strField = "";
		strValue = "";
	}
};

class CHttpPageClient
{
private:
	vector<_tagUrlRequestData> m_vtCurlRequest;
	DWORD m_dwThreadID;
	HANDLE m_hThread;
	int _timeoutForConnect;
	int _timeoutForRead;
	string m_strUpFile;
	string m_strUserID;
	string m_strPlateForm;
	CHttpPageRequest *m_pHttpPageRequest;
	CHttpPageResponse *m_pHttpPageResponse;
public:
	CHttpPageClient();
	virtual ~CHttpPageClient();
public:
 
	static DWORD WINAPI HttpPageClientThread(LPVOID lpParameter);
	// 请求Http上传文件线程
	static DWORD WINAPI HttpUpFileThread(LPVOID lpParameter);

	//
	VOID DoHttpPageClientProc();
	//
	VOID DoHttpUpFileProc();

public:
	// 设置POST 数据
	void SetPostVectorData(_tagUrlRequestData &data);
	// 请求Http
	void HttpGetRequest(const char *lpszHttpUrl);
	// 请求Http
	void SendHttpRequestByGet(const char *lpszHttpUrl);
	// 请求Http
	void HttpUpFileRequest(const char *lpszHttpUrl, const char *lpszFilePath, const char *lpszUseraID, const char *lpszPlateForm);
	// 获取Http返回结果
	CHttpPageResponse* GetHttpPageResponse();
private:

	// 请求Http
	void RequestHttpPageClient();
	// 请求Http上传文件
	void RequestHttpUpFile();
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
	int processGetTask(CHttpPageRequest *request, write_callback callback, void *stream, int *errorCode);
	int processPostTask(CHttpPageRequest *request, write_callback callback, void *stream, int *errorCode);
	int processPostUpFileTask(CHttpPageRequest *request, write_callback callback, void *stream, int *errorCode);

};


#endif //__HTTP_PAGE_CLIENT_H__
