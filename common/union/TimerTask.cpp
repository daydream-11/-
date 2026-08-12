#include "stdafx.h"
#include "TimerTask.h"
#include "MainTask.h"
#include "MemoryPoolManager.h"
#include "MyTimerManager.h"
#include "TimeManager.h"

TimerTask*	g_pTimerTask = NULL;

TimerTask::TimerTask()
{
	__ENTER_FUNCTION

	m_pJoinVectorMyTimer = NULL;
	m_pWaitVectorMyTimer = NULL;
	m_pProcessTimerProc = NULL;

	__LEAVE_FUNCTION
}

TimerTask::~TimerTask()
{
	__ENTER_FUNCTION

	Exit();

	__LEAVE_FUNCTION
}

BOOL TimerTask::Init(ProcessTimerProc pProcessTimerProc)
{
	__ENTER_FUNCTION
	
	m_pProcessTimerProc = pProcessTimerProc;
	//
	m_pJoinVectorMyTimer = new TVectorMyTimer();
	if (m_pJoinVectorMyTimer == NULL)
	{
		return FALSE;
	}
	m_pWaitVectorMyTimer = new TVectorMyTimer();
	if (m_pWaitVectorMyTimer == NULL)
	{
		return FALSE;
	}
	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

BOOL TimerTask::Exit()
{
	__ENTER_FUNCTION

	SAFE_DELETE(m_pJoinVectorMyTimer);
	SAFE_DELETE(m_pWaitVectorMyTimer);

	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

VOID TimerTask::Run()
{
	MyTimer *pMyTimer = NULL;
	while (m_bRunning)
	{
		UINT uCurTickCount = (UINT)g_pTimeManager->GetCurrentTime();
		for (TVectorMyTimer::iterator iter = m_pJoinVectorMyTimer->begin(); iter != m_pJoinVectorMyTimer->end();)
		{
			pMyTimer = *iter;
			UINT uLastTime = pMyTimer->GetLastTime();
			if ( (uCurTickCount - uLastTime) >= pMyTimer->GetTimerSpaceMilliSecond() )
			{
				// 定时器时间到达
				BOOL bErase = RunOutTimer(pMyTimer, uCurTickCount);
				if ( bErase )
				{
					iter = m_pJoinVectorMyTimer->erase(iter);
				}
				else
				{
					iter++;
				}				
			}
			else
			{
				 iter++;
			}
		}
		LoadWaitTask();
		SleepEx(5);
	}
}

VOID TimerTask::LoadWaitTask()
{
	__ENTER_FUNCTION
		
	AutoLockT myAutoLockT(m_Lock);
	for (TVectorMyTimer::iterator iter = m_pWaitVectorMyTimer->begin(); iter != m_pWaitVectorMyTimer->end(); iter++)
	{
		MyTimer *pMyTimer = *iter;
		m_pJoinVectorMyTimer->push_back(pMyTimer);
	}
	m_pWaitVectorMyTimer->clear();

	__LEAVE_FUNCTION
}

// 运行已经到达的定时器
BOOL TimerTask::RunOutTimer(MyTimer * & pMyTimer, UINT uCurTickCount)
{
	if (g_pMainTask != NULL)
	{
		if (m_pProcessTimerProc != NULL)
		{
			m_pProcessTimerProc((VOID*)pMyTimer);
		}
	}
	//
	pMyTimer->SetLastTime(uCurTickCount);
	if (g_pMyTimerManager != NULL)
	{
		INT nTimerTimes = pMyTimer->GetTimerTimes();
		if ( -1 == nTimerTimes )
		{
			return FALSE;
		}
		if ( nTimerTimes > 0 )
		{
			nTimerTimes--;
			pMyTimer->SetTimerTimes(nTimerTimes);
		}
		if ( pMyTimer->GetTimerTimes() == 0 )
		{
			if (pMyTimer->GetIndex() > -1)
			{
				g_pMyTimerManager->ReleaseMyTimer(pMyTimer);
			}
			else
			{
				delete pMyTimer;
				pMyTimer = NULL;
			}
			//
			return TRUE;
		}
	}
	//
	return FALSE;
}

// 运行秒定时器
BOOL TimerTask::RunSecondTimer(UINT uSecond, VOID *pTimerParam, INT nTimerTimes)
{
	__ENTER_FUNCTION

	return RunMilliSecondTimer(uSecond * 1000, pTimerParam, nTimerTimes);

	__LEAVE_FUNCTION

	return FALSE;
}

// 运行毫秒定时器
BOOL TimerTask::RunMilliSecondTimer(UINT uMilliSecond, VOID *pTimerParam, INT nTimerTimes)
{
	__ENTER_FUNCTION

	UINT uCurTickCount = g_pTimeManager->GetCurrentTime();
	MyTimer *pMyTimer = g_pMyTimerManager->GetNoUseMyTimer();
	if (pMyTimer != NULL)
	{
		pMyTimer->SetTimerData(uMilliSecond, uCurTickCount, pTimerParam, nTimerTimes);
	}
	else
	{
		pMyTimer = new MyTimer(uMilliSecond, uCurTickCount, pTimerParam, nTimerTimes);
		if (pMyTimer == NULL)
		{
			return FALSE;
		}
	}
	InsertWaitVectorMyTimer(pMyTimer);

	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

// 添加正在排队的定时器数据
VOID TimerTask::InsertWaitVectorMyTimer(MyTimer *pMyTimer)
{
	__ENTER_FUNCTION
		
	AutoLockT myAutoLockT(m_Lock);

	m_pWaitVectorMyTimer->push_back(pMyTimer);

	__LEAVE_FUNCTION
}