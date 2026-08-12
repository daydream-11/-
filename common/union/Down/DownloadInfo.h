#pragma once

#include "SocketClient.h"
#include "RegisterTemplate.h"
#include <afxmt.h>
#include "DownStruct.h"

class IDownloadInfoEvent
{
public:
	// 设置调试日志
	virtual void WriteDebugLog(TCHAR * strMsg, ...){};
};

class CDownloadInfo
	: public VectorRegister<IDownloadInfoEvent>
{
private:
	// 线程句柄
	HANDLE m_hThread;
public:
	// 端口信息
	int m_nPort;
	// 是否下载成功
	BOOL m_bDownloadSuccess;
	// 下载索引
	int m_nIndex;
	// 下载线程数
	int m_nThradCount;
	// 待下载URL
	CString m_strDownloadUrl;
	// 服务器信息
	CString m_strServer;
	// 对象信息
	CString m_strObject;
	// 协议类型
	CString m_strProtocolType;
	// 保存文件名
	CString m_strSaveFileName;
	// 模块运行地址
	CString m_strMoudlePath;
	// 重定向文件名
	CString m_strContentDispositionFileName;
	// 页面内容
	CHAR *m_pPageContent;
	// 页面长度
	INT m_nPageLength;
public:

	// 文件日期(远程文件的信息)
	CTime m_TimeLastModified;
	// Referer
	CString m_strReferer;
	// UserAgent
	CString m_strUserAgent;
	// 是否支持断点续传
	BOOL m_bSupportResume;
	// 重复次数
	int m_nRetryTimes;
	// 请求一次暂停时间
	int m_nSleepMilliSecond;
public:

	// 保存下载信息的回调函数
	FunCallbackSaveDownloadInfo m_pCallbackSaveDownloadInfoProc;
	// 保存下载信息的回调参数
	WPARAM m_wCallbackSaveDownloadInfoParam;
	// 保存下载进度的回调函数
	FunCallbackDownloadProgressInfo m_pCallbackDownloadProgressInfoProc;
	// 保存下载进度的回调参数
	WPARAM m_pCallbackDownloadProgressInfoParam;
private:
	// 当前的指向下载信息
	TSingleDownloadInfo *m_pCurSingleDownloadInfo;
public:
	
	// 文件总的大小，-1表示未知文件大小
	int	 m_nFileTotalSize;		
	// 要下载文件的开始位置
	int m_nWillDownloadStartPos;
	// 本次需要下载的大小，-1表示不知道文件大小，所以下载到服务器关闭连接为止
	int	m_nWillDownloadSize;
	// 访问 m_nWillDownloadSize 变量的互斥锁
	CCriticalSection	m_csWillDownloadSize;
	// 存放在临时缓冲中的字节数
	int m_nTempSaveBytes;
	// 已下载的字节数，指完全写到文件中的字节数，不包含临时缓冲里的数据
	int m_nDownloadedSize;
private:
	// 访问 m_nTempSaveBytes 变量的互斥锁
	CCriticalSection m_csTempSaveBytes;
	// 访问 m_nDownloadedSize 变量的互斥锁
	CCriticalSection	m_csDownloadedSize;
	// 日志锁
	CCriticalSection m_csLog;
public:

	// 模块结束事件
	HANDLE m_hEvtEndModule;
	// 连接服务器的 Socket
	CSocketClient m_WnSocketClient;
	
public:
	// 操作关于下载信息
	CFile m_fileForContent;
	// 操作关于写入线程相关信息
	CFile m_fileForThread;
public:
	CDownloadInfo(void);
	~CDownloadInfo(void);
public:
	virtual int GetRemoteSitePro();
	virtual BOOL DownloadOnce();
	// 下载页面内容
	virtual BOOL DownloadPageContent();
	void ClearDownloadInfo();
	void ClearThreadHandle();
	void StopDownload();
	// 下载结束
	BOOL DownloadEnd(BOOL bRes);
	BOOL Connect();
	CString GetOneLine(CString &str);
public:
	// 获取下载的起始位置
	int GetWillDownloadStartPos();
	// 设置要下载的大小
	void SetWillDownloadSize(int nWillDownloadSize);
	// 获取要下载的大小
	int GetWillDownloadSize();
	// 设置已经下载的大小
	void SetDownloadedSize(int nDownloadedSize);
	// 获取已经下载的大小
	int GetDownloadedSize();
	// 设置存放在临时缓冲中的字节数
	void SetTempSaveBytes(int nTempSaveBytes);
	// 获取存放在临时缓冲中的字节数
	int GetTempSaveBytes();
	// 获取文件总的大小
	int GetFileTotalSize();
	// 获取尚未下载的字节数，写到文件中的和临时缓冲里的都算是已经下载的
	int GetUnDownloadBytes();
	// 获取是否下载成功
	BOOL IsDownloadSuccess() ;
	// 线程是否正在运行
	BOOL IsThreadRunning();
	// 最后修改时间
	time_t GetTimeLastModified();
	// 设置当前的指向下载信息
	void SetCurSingleDownloadInfo(TSingleDownloadInfo* pCurSingleDownloadInfo);
public:

	BOOL OpenFileForSave();
	// 打开文件要保存内容的操作（m_fileForContent）
	BOOL OpenFileForContent();
	// 打开文件要保存线程的操作（m_fileForThread）
	BOOL OpenFileForThread();
	//
	BOOL IsSupportResume();
	HANDLE GetThreadHandle();
public:

	BOOL GetRemoteSiteInfo();
	BOOL SetDownloadUrl(LPCTSTR strDownloadUrl);
	CString GetRefererFromURL();
	// 访问Php获取网页内容
	BOOL GetBrowsePageContent();
	
	// 设置保存下载信息回调函数
	void SetCallbackSaveDownloadInfo(FunCallbackSaveDownloadInfo pCallbackSaveDownloadInfoProc, WPARAM wParam);
	// 设置保存下载进度回调函数
	void SetCallbackDownloadProgressInfo(FunCallbackDownloadProgressInfo pCallbackDownloadProgressInfoProc, WPARAM wParam);
	// 保存文件的路径
	void SetSaveFileName(LPCTSTR strSaveFileName);
	// 设置模块的路径
	void SetMoudlePath(LPCTSTR strMoudlePath);
	// 从URL里面拆分出Server、Object、协议类型等信息，其中 Object 里的值是区分大小写的，否则有些网站可能会下载不了
	BOOL ParseURL(LPCTSTR lpszURL, CString & strServer, CString & strObject,int & nPort, CString & strProtocolType);
	// 创建线程下载文件
	BOOL DoRunDownloadFile(int nWillDownloadStartPos, int nWillDownloadSize, int nDownloadedSize);
	// 创建线程下载文件
	BOOL DoRequestPageContent(int nWillDownloadSize, int nDownloadedSize);
	// 下载任务的线程函数
	static DWORD WINAPI DoDownloadThread(LPVOID lpParameter);
	// 下载任务的线程函数
	static DWORD WINAPI DoRequestPageContentThread(LPVOID lpParameter);
	// 下载任务的过程函数
	DWORD DoDownloadProcedure(void);
	// 下载任务的过程函数
	DWORD DoRequestPageContentProcedure(void);
	// 从服务器接收数据并保存到文件中
	BOOL RecvDataAndSaveToFile(CSocketClient & myWnSocketClient,char * szTailData = NULL, int nTailSize = 0);
	// 从服务器接收数据并保存到文件中
	int SaveDataToFile(char * pWriteBuffer, int nWriteSize);
	// 保存线程数据到文件
	void SaveThreadDataToFile();
	// 获取页面内容
	CHAR* GetPageContent();
	// 获取页面长度
	INT GetPageLength();

public:

	
	// 暂停下载的线程
	BOOL DoRunSuspendThread(void);
	// 恢复下载的线程
	BOOL DoRunResumeThread(void);
	// 终结下载的线程
	void DoRunTerminateThread(void);
	// 设置循环下载次数
	void SetRetryTimes(int nRetryTimes);
	// 设置循环下载暂停时间
	void SetSleepMilliSecond(int nSleepMilliSecond);
	// 写入调试日志
	void WriteDebugLog(TCHAR * strMsg, ...);
	// 写入调试日志
	void WriteAppointLog(TCHAR * strMsg, ...);
	
};
