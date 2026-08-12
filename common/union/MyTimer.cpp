#include "stdafx.h"
#include "MyTimer.h"
#include "GameType.h"

MyTimer::MyTimer()
{
	m_nIndex = -1;
	m_nTimes = 0;
	m_uSpaceMilliSecond = 0;
	m_uLastTime = 0;
	m_pTimerParam = NULL;
}

MyTimer::MyTimer(UINT uSpaceMilliSecond, UINT uLastTime, VOID* pTimerParam, INT nTimes)
{
	m_uSpaceMilliSecond = uSpaceMilliSecond;
	m_uLastTime = uLastTime;
	m_nTimes = nTimes;
	m_pTimerParam = pTimerParam;
}

MyTimer::~MyTimer()
{
	Clear();
}

VOID MyTimer::Clear()
{
	m_uSpaceMilliSecond = 0;
	m_nTimes = 0;
	m_uLastTime = 0;
	m_pTimerParam = NULL;
}


// 初始化
VOID MyTimer::Init(UINT uIndex)
{
	
}

// 设置索引
VOID MyTimer::SetIndex(INT nIndex)
{
	m_nIndex = -1;
}

// 获取索引
INT MyTimer::GetIndex()
{
	return m_nIndex;
}

// 获取定时器次数
INT MyTimer::GetTimerTimes()
{
	return m_nTimes;
}

// 设置定时器次数
VOID MyTimer::SetTimerTimes(INT nTimes)
{
	m_nTimes = nTimes;
}

// 获取定时器时间间隔(毫秒)
UINT MyTimer::GetTimerSpaceMilliSecond()
{
	return m_uSpaceMilliSecond;
}

// 设置定时器时间间隔(毫秒)
VOID MyTimer::SetTimerSpaceMilliSecond(UINT uSpaceMilliSecond)
{
	m_uSpaceMilliSecond = uSpaceMilliSecond;
}

// 到期时间
UINT MyTimer::GetLastTime()
{
	return m_uLastTime;
}

// 设置到期时间
VOID MyTimer::SetLastTime(UINT uLastTime)
{
	m_uLastTime = uLastTime;
}
	
// 获取定时器参数
VOID* MyTimer::GetTimerParam()
{
	return m_pTimerParam;
}

// 设置定时器参数
VOID MyTimer::SetTimerParam(VOID *pTimerParam)
{
	m_pTimerParam = pTimerParam;
}

// 设置定时器数据
VOID MyTimer::SetTimerData(UINT uSpaceMilliSecond, UINT uLastTime, VOID *pTimerParam, INT nTimes)
{
	m_uSpaceMilliSecond = uSpaceMilliSecond;
	m_uLastTime = uLastTime;
	m_nTimes = nTimes;
	m_pTimerParam = pTimerParam;
}