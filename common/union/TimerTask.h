
#ifndef __TIMER_TASK_H__
#define __TIMER_TASK_H__

#include "GameType.h"
#include "Thread.h"
#include "MyTimer.h"

// 处理定时器消息
typedef VOID(WINAPI* ProcessTimerProc)(VOID *pTimerMsg);

typedef vector<MyTimer*> TVectorMyTimer;
// 处理定时器任务
class TimerTask : public Thread
{
private:
	// 同步锁
	MyLock m_Lock;
	// 正在处理的定时器
	TVectorMyTimer *m_pJoinVectorMyTimer;
	// 正在排队的定时器
	TVectorMyTimer *m_pWaitVectorMyTimer;
	// 处理定时器消息过程函数
	ProcessTimerProc m_pProcessTimerProc;
public :
	TimerTask();
	~TimerTask();
public:
	// 初始化
	BOOL Init(ProcessTimerProc pProcessTimerProc);
	BOOL Exit();
private:
	virtual VOID Run();
	// 加载正在排队的定时器到处理队列中去
	VOID LoadWaitTask();
private:
	// 运行已经到达的定时器
	BOOL RunOutTimer(MyTimer * & pMyTimer, UINT uCurTickCount);
	// 添加正在排队的定时器数据
	VOID InsertWaitVectorMyTimer(MyTimer *pMyTimer);
public:
	// 运行秒定时器
	BOOL RunSecondTimer(UINT uSecond, VOID *pTimerParam, INT nTimerTimes = 1);
	// 运行毫秒定时器
	BOOL RunMilliSecondTimer(UINT uMilliSecond, VOID *pTimerParam, INT nTimerTimes = 1);
};

extern TimerTask* g_pTimerTask ;


#endif // __TIMER_TASK_H__
