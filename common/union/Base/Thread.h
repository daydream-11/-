#ifndef __THREAD_H__
#define __THREAD_H__

#include "Lock.h"
#include "ThreadControl.h"

class Thread
{
private:
#if defined(__WINDOWS__)
	HANDLE m_hHandle;
#endif
	TID  m_TID;
protected:
	MyLock m_Lock;
	bool m_bStarted;
	bool m_bRunning;
public:
	Thread(void);
	~Thread(void);
public:
	virtual void Run() = 0;

	VOID Start();

	ThreadControl GetThreadControl();

	bool IsAlive();

	void Done();
};

#if defined (__LINUX__)
	VOID* MyThreadProcess(VOID *pParam);
#elif defined(__WINDOWS__)
	DWORD WINAPI MyThreadProcess(VOID *pParam);
#endif

#endif // __THREAD_H__