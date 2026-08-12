
#ifndef __GAME_UTIL_H__
#define __GAME_UTIL_H__

#include "BaseType.h"
#include "GameDefine.h"

// 当前线程挂起一定时间
extern VOID SleepEx(UINT uMillionSeconds = 0);
// 获取当前线程
extern TID GetCurrentThreadIDEx();
// 是否有效服务器ID
extern BOOL IsValidServerID(UINT uServerID);
// 获取时间 20120921
extern UINT GetMyDate(UINT uTime);
// 获取当前日期如：20120921
extern UINT GetCurrentDate();
// 
#endif
