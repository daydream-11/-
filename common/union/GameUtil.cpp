#include "stdafx.h"
#include "GameType.h"
#include "GameUtil.h"
#include "TimeManager.h"

VOID SleepEx(UINT uMillionSeconds)
{
#if defined(__WINDOWS__)
	Sleep(uMillionSeconds);
#elif defined(__LINUX__)
	usleep(uMillionSeconds * 1000);
#endif
}

TID GetCurrentThreadIDEx()
{
#if defined(__WINDOWS__)
	return GetCurrentThreadId();
#else
	return 0;
#endif
}


// 是否有效服务器ID
BOOL IsValidServerID(UINT uServerID)
{
	return FALSE;
}

// 获取时间 20120921
UINT GetMyDate(UINT uTime)
{
	time_t theCurrentTime = (time_t)uTime;
	tm * myCurrentTime = localtime(&theCurrentTime);
	char szTime[10] = {'0'};
	sprintf(szTime, "%d%.2d%.2d", myCurrentTime->tm_year+1900, myCurrentTime->tm_mon+1, myCurrentTime->tm_mday);
	UINT uNowTime = (UINT)atoi(szTime);
	return uNowTime;
}

// 获取当前日期如：20120921
UINT GetCurrentDate()
{
	UINT uTime = (UINT)time(NULL);
	return GetMyDate(uTime);
}
