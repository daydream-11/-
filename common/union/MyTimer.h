#ifndef __MY_TIMER_H__
#define __MY_TIMER_H__


class MyTimer
{
private:
	// 索引
	INT m_nIndex;
	// 定时器次数(-1无限次)
	INT m_nTimes;
	// 时间间隔(毫秒)
	UINT m_uSpaceMilliSecond;
	// 上次时间
	UINT m_uLastTime;
	// 定时器参数
	VOID *m_pTimerParam;
public:
	MyTimer();
	MyTimer(UINT uSpaceMilliSecond, UINT uLastTime, VOID* pTimerParam, INT nTimes = 1);
	~MyTimer();
public:
	VOID Clear();
public:
	// 初始化
	VOID Init(UINT uIndex);
	// 设置索引
	VOID SetIndex(INT nIndex);
	// 获取索引
	INT GetIndex();
	// 获取定时器次数
	INT GetTimerTimes();
	// 设置定时器次数
	VOID SetTimerTimes(INT nTimes);
	// 获取定时器时间间隔(毫秒)
	UINT GetTimerSpaceMilliSecond();
	// 设置定时器时间间隔(毫秒)
	VOID SetTimerSpaceMilliSecond(UINT uSpaceMilliSecond);
	// 获取上次时间
	UINT GetLastTime();
	// 设置上次时间
	VOID SetLastTime(UINT uLastTime);
	// 获取定时器参数
	VOID* GetTimerParam();
	// 设置定时器参数
	VOID SetTimerParam(VOID *pTimerParam);
	// 设置定时器数据
	VOID SetTimerData(UINT uSpaceMilliSecond, UINT uLastTime, VOID *pTimerParam, INT nTimes = 1);
};

#endif	// __MY_TIMER_H__

