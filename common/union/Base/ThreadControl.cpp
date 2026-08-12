#include "stdafx.h"
#include "ThreadControl.h"

ThreadControl::ThreadControl(void)
{
#if defined(__WINDOWS__)
	m_hHandle = NULL;
#endif
	m_nThreadID = 0;
}

ThreadControl::~ThreadControl(void)
{
}


#if defined(__WINDOWS__)
ThreadControl::ThreadControl(HANDLE hHandle, int nThreadID)
{
	m_hHandle = hHandle;
	m_nThreadID = nThreadID;
}

#endif

// 等待线程
void ThreadControl::Join()
{
#if defined(__WINDOWS__)
	if (m_hHandle == NULL)
	{
		//throw BadThreadControlException(__FILE__, __LINE__);
	}

	int nReturn = WaitForSingleObject(m_hHandle, INFINITE);
	if (nReturn != WAIT_OBJECT_0)
	{
		//throw ThreadSyscallException(__FILE__, __LINE__, GetLastError());
	}

	Detach();
#endif
}

// 暂停线程
void ThreadControl::Suspend()
{
#if defined(__WINDOWS__)
	DWORD dwReturn = SuspendThread(m_hHandle);
	if (dwReturn == 0xFFFFFFFF)
	{
		return;
	}
#endif
}

// 恢复线程
void ThreadControl::Resume()
{
#if defined(__WINDOWS__)
	DWORD dwReturn = ResumeThread(m_hHandle);
	if (dwReturn == 0xFFFFFFFF)
	{
		return;
	}
#endif
}

// 停止线程
void ThreadControl::Terminate()
{
#if defined(__WINDOWS__)
	DWORD dwExitCode = 0;
	GetExitCodeThread(m_hHandle, &dwExitCode); 
	TerminateThread(m_hHandle, dwExitCode);
	CloseHandle(m_hHandle);
	m_hHandle = NULL;
#endif
}

void ThreadControl::Detach()
{
#if defined(__WINDOWS__)
	if(m_hHandle == NULL)
	{
		//throw BadThreadControlException(__FILE__, __LINE__);
	}

	if (CloseHandle(m_hHandle) == 0)
	{
		//throw ThreadSyscallException(__FILE__, __LINE__, GetLastError());
	}
#endif
}

bool ThreadControl::operator == (const ThreadControl & myThreadControl)
{
	return m_nThreadID == myThreadControl.m_nThreadID;
}

bool ThreadControl::operator != (const ThreadControl & myThreadControl)
{
	return m_nThreadID != myThreadControl.m_nThreadID;
}