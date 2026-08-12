
#ifndef __MY_TIMER_MANAGER_H__
#define __MY_TIMER_MANAGER_H__

#include "Type.h"
#include "ObjectPool.h"
#include "MyTimer.h"

class MyTimerManager
{
private:
	ObjectPool<MyTimer> *m_pMyTimerObjectPool;
public :
	MyTimerManager();
	~MyTimerManager();
public:
	BOOL Init(UINT uMyTimerNum);
public:
	VOID ReleaseMyTimer(MyTimer *pMyTimer);
	MyTimer* GetNoUseMyTimer();
};
extern MyTimerManager * g_pMyTimerManager;



#endif	// __MY_TIMER_MANAGER_H__
