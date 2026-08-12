#ifndef __LOCK_H__
#define __LOCK_H__

#include "BaseType.h"

class MyLock
{
public:
	CRITICAL_SECTION m_Lock ;
	//volatile long val_;
public :
	MyLock()
	{
		InitializeCriticalSection(&m_Lock);
		//val_ = 0;
	};

	~MyLock()
	{
		DeleteCriticalSection(&m_Lock); 
	};
public:
	void Lock()
	{
		EnterCriticalSection(&m_Lock);
		/*while (atomic_cas(&val_, 0, 1) != 0)
		{
			SleepEx(0);
		}*/
	};

	void UnLock()
	{
		LeaveCriticalSection(&m_Lock);
		//val_ = 0;
	};
};
class AutoLockT
{
public:
	AutoLockT(MyLock & myMyLock)
	{
		m_pMyLock = &myMyLock;
		Lock();
	}
	~AutoLockT()
	{
		UnLock();
	}
private:
	inline void Lock()
	{
		m_pMyLock->Lock();
	}
	inline void UnLock() 
	{
		m_pMyLock->UnLock();
	}
private:
	MyLock* m_pMyLock;
};



#endif // __LOCK_H__
