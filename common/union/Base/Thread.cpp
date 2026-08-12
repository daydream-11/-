#include "stdafx.h"
#include "Thread.h"
#if defined(__WINDOWS__)
#include <process.h>
#elif defined (__LINUX__)
#include <pthread.h>
#endif

Thread::Thread(void)
{
	m_bStarted = false;
	m_bRunning = false;
#if defined(__WINDOWS__)
	m_hHandle = NULL;
#endif
	m_TID = 0;
}

Thread::~Thread(void)
{
}

#if defined (__LINUX__)
VOID* MyThreadProcess(VOID *pParam)
{
	Thread *pThread = (Thread*)pParam;
	if (pThread != NULL)
	{
		pThread->Run();
	}
	return NULL;
}
#elif defined (__WINDOWS__)
DWORD WINAPI MyThreadProcess(VOID *pParam)
{
	Thread *pThread = (Thread*)pParam;
	if (pThread != NULL)
	{
		pThread->Run();
	}
	return 0;
}
#endif


VOID Thread::Start()
{
	m_bRunning = true;
	
#if defined(__LINUX__)
	pthread_create( &m_TID, NULL , MyThreadProcess , this );
#elif defined(__WINDOWS__)
	m_hHandle = ::CreateThread( NULL, 0, MyThreadProcess , this, 0, (DWORD*)&m_TID);
#endif

	m_bStarted = true;
}

bool Thread::IsAlive()
{
	AutoLockT myAutoLockT(m_Lock);
	return m_bRunning;
}

void Thread::Done()
{
	AutoLockT myAutoLockT(m_Lock);
	m_bRunning = false;
}

ThreadControl Thread::GetThreadControl()
{
	AutoLockT myAutoLockT(m_Lock);
	if (!m_bStarted)
	{
		//throw ThreadNotStartedException(__FILE__, __LINE__);
	}
#if defined(__WINDOWS__)
	return ThreadControl(m_hHandle, m_TID);
#else
	return ThreadControl();
#endif
}