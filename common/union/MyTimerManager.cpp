#include "stdafx.h"
#include "MyTimerManager.h"
#include "Log.h"

MyTimerManager * g_pMyTimerManager = NULL;

MyTimerManager::MyTimerManager( )
{
	__ENTER_FUNCTION

	m_pMyTimerObjectPool = NULL;

	__LEAVE_FUNCTION
}

MyTimerManager::~MyTimerManager( )
{
	__ENTER_FUNCTION

	SAFE_DELETE(m_pMyTimerObjectPool);

	__LEAVE_FUNCTION
}

BOOL MyTimerManager::Init(UINT uMyTimerNum)
{
	__ENTER_FUNCTION

	m_pMyTimerObjectPool = new ObjectPool<MyTimer>();
	if (m_pMyTimerObjectPool == NULL)
	{
		return FALSE;
	}

	BOOL bReturn = m_pMyTimerObjectPool->Init(uMyTimerNum);
	if (!bReturn)
	{
		return FALSE;
	}
	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

VOID MyTimerManager::ReleaseMyTimer(MyTimer *pMyTimer)
{
	if (m_pMyTimerObjectPool != NULL)
	{
		pMyTimer->Clear();
		m_pMyTimerObjectPool->RemoveT(pMyTimer);
	}
}

MyTimer* MyTimerManager::GetNoUseMyTimer()
{
	__ENTER_FUNCTION

	if (m_pMyTimerObjectPool == NULL)
	{
		return NULL;
	}
	return m_pMyTimerObjectPool->GetNewT();

	__LEAVE_FUNCTION

	return NULL;
}