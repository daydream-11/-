
#ifndef __THREAD_CONTROL_H__
#define __THREAD_CONTROL_H__

class ThreadControl
{
private:
#if defined(__WINDOWS__)
	HANDLE m_hHandle;
#endif
	int m_nThreadID;
public:
	ThreadControl(void);
	~ThreadControl(void);
public:
#if defined(__WINDOWS__)
	 ThreadControl(HANDLE hHandle, int nThreadID);
#endif
	 bool operator == (const ThreadControl & myThreadControl);
	 bool operator != (const ThreadControl & myThreadControl);
public:

	// 等待线程
	void Join();
	// 暂停线程
	void Suspend();
	// 恢复线程
	void Resume();
	// 停止线程
	void Terminate();
	//
	void Detach();
};

#endif	// __THREAD_CONTROL_H__