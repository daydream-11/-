#pragma once

#include "DownloadInfo.h"
#include "DownloadInterface.h"
typedef vector< pair<int, int> > CVectorDownloadSpeed;



class CMYDownloadProc
	: public IDownloadInfoEvent
	, public CDownloadInterface
{

private:
	CString m_strMoudlePath;
	CString m_strSavePath;
	CString m_strSaveOnlyFileName;
	CString m_strDownloadURL;
	BOOL m_bForceDownload;
	int m_nThreadCount;
	CString		m_strProtocolType;
	CString m_strSavePathFileName;
	CString m_strSaveFileName;
	// 最后更新时间
	CString m_strLastModifyTime;
	// 是否所有线程都运行
	BOOL m_bAllThreadRun;
	CHAR *m_pPageContent;
private:
	// 模块结束事件
	HANDLE m_hEvtEndModule;
	HANDLE m_hThread;
	DWORD m_dwDownloadStartTime;
	DWORD m_dwFrontDownloadCalculateTime;
	// 上一次计算下载速度时间
	DWORD m_dwFrontCalculateSpeedDownloadTime;
	// 用来计算平均下载速率（定有10秒左右的平均下载速度）
	CVectorDownloadSpeed *m_pVectorDownloadSpeed;
	// 是否下载成功
	BOOL m_bDownloadFlag;
	// 重试次数
	int m_nRetryTimes;
	// 重试次数每次暂停次数
	int m_nRetryTimesSleepMilliSecond;
private:

	// 取站点信息对象
	CDownloadInfo *m_pDownloadInfo;
	// 多线程下载对象
	CDownloadInfo *m_pMultiThreadDownloadInfo;
	// 各个下载对象的参数
	TSingleDownloadInfo *m_pMultiSingleDownloadInfo;
	// 下载的基本信息
	TBaseDownloadInfo m_BaseDownloadInfo;
	// 表示这次启动下载任务以来总共下载的字节数
	int m_nThisTimeDownloadedTotalSize;
	CCriticalSection m_csThisTimeDownloadedTotalSize;
	CCriticalSection m_csSetDownloadProgressInfo;
	CCriticalSection m_csLog;
public:
	CMYDownloadProc(void);
	~CMYDownloadProc(void);

public:

	// 初始化下载过程类
	BOOL Init();
	// 设置重试次数
	virtual VOID SetRetryTimes(int nRetryTimes);
	// 设置循环下载暂停时间
	virtual VOID SetRetryTimesSleepMilliSecond(int nRetryTimesSleepMilliSecond);
	// 多线程断点续传下载一个文件
	BOOL DoDownloadFile(const TCHAR * strDownloadUrl, const TCHAR * strSaveFileName);
	// 多线程断点续传下载一个文件
	BOOL DoWaitDownloadFile(const TCHAR * strDownloadUrl, const TCHAR * strSaveFileName);
	// 请求http 文件时间
	BOOL DoRequestHttpFileTime(const TCHAR * strHttpFileName, TCHAR * strReturnTime);
	// 请求http 文件内容
	CHAR* DoRequestHttpPageContent(const TCHAR * strHttpFileName);
public:
	// 下载文件过程
	BOOL DoDownloadFileProc();
	// 请求文件时间线程过程函数
	BOOL DoRequestHttpFileTimeProc();
	// 请求文件文件内容函数过程
	BOOL DoRequestHttpPageContentProc();
private:
	// 开始下载文件
	BOOL DoStartDownloadFile();
	// 写入调试日志
	virtual void WriteDebugLog(TCHAR * strMsg, ...);
public:
	// 暂停下载的线程
	BOOL DoRunSuspendThread(void);
	// 恢复下载的线程
	BOOL DoRunResumeThread(void);
	// 终结下载的线程
	void DoRunTerminateThread(void);
	// 设置下载的线程数
	BOOL SetThreadCount(int nThreadCount);
	// 获取下载所消耗的时间（毫秒），可用来计算下载速度和推算剩余时间
	DWORD GetDownloadElapsedTime();
	// 获取本次下载大小
	int GetTotalDownloadedSizeThisTimes();
	// 获取下载的完整数据大小
	int GetDownloadInfoWholeSize();
	// 从下载信息文件中读取下载信息
	int ReadDownloadInfo();
	// 创建一个空文件
	BOOL CreateNullFile(LPCTSTR lpszFileName, int nFileSize);
	// 删除下载对象
	void DeleteDownloadObject(CDownloadInfo *pDeleteWnDownloadInfo);
	// 删除多线程下载使用的对象和数据缓冲
	void DoDeleteDownloadObject();
	// 创建下载对象
	CDownloadInfo* CreateDownloadObject(int nCount);
	// 创建多线程下载使用的对象和数据缓冲
	BOOL DoCreateDownloadObject();
	// 下载信息是否有效
	BOOL IsHavaValidDownloadInfo();
	// 清空相关联的下载信息
	void DoClearRelevanceDownloadInfo();
	// 分配下载任务
	BOOL DoAssignDownloadTask();
	// 获取已下载的字节数
	int GetAlreadyDownloadSize();
	// 获取已下载的字节数，包括以前下载的和本次下载的
	int GetTotalDownloadedSize();
	// 查找线程句柄的索引位置
	int FindIndexByThreadHandle(HANDLE hThread);
	// 找到剩余未下载的数量最大的那个对象编号
	int GetMaxUnDownloadBytes(int & nUnDownloadBytes);
	// 编号为 nIndex 的对象调度任务，为下载任务最繁重的对象减轻负担
	BOOL AttemperDownloadTask(int nIndex);
	// 等待下载结束
	ENUM_DOWNLOAD_RESULT DoWaitForDownloadFinish();
	// 下载的回调函数
	BOOL GetDownloadResult();
	// 下载的回调函数
	BOOL HandleDownloadFinished(ENUM_DOWNLOAD_RESULT myDownloadResult);
	// 下载的回调函数
	void CallBackSaveDownloadInfoProc(int nIndex, int nDownloadedSize, int nSimpleSaveSize);
	// 下载进度的回调函数
	void CallbackDownloadProgressInfoProc();

public:
	// 下载文件线程
	static DWORD WINAPI DoDownloadFileThread(LPVOID lpParameter);
	// 请求http文件时间线程
	static DWORD WINAPI DoRequestHttpFileTimeThread(LPVOID lpParameter);
	// 请求http页面内容
	static DWORD WINAPI DoRequestHttpPageContentThread(LPVOID lpParameter);
	
};
