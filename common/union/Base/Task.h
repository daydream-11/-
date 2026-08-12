#ifndef __TASK_H__
#define __TASK_H__

#include "Thread.h"

#define TASK_BUFF_SIZE 2048

template <typename T>
class Task
{
public:
	// 线程，用于回调Task::run
	class Call : public Thread
	{
	public:
		Call(Task<T> *pTask)
		{
			m_pTask = pTask;
		}
		void Run() 
		{
			m_pTask->Run();
		}
		Task<T> *m_pTask;
	};
private:
	// 输入消息锁
	MyLock m_PutLock;
	// 输出消息锁
	MyLock m_OutLock;
private:
	// 线程池，生命周期由Handle管理
	Call **m_pThreadPool;
	// 线程池数
	int m_nThreadNum;
public:
	// 是否运行，用于标志线程
	bool m_bRunning;
	// 停止任务
	bool m_bStopTask;
	// 暂停任务
	bool m_bSuspendTask;
public:
	// 输入消息队列缓存
	T *m_ppInputTaskBuf;
	// 输出消息队列缓存
	T *m_ppOutputTaskBuf;
public:
	// 输入消息队列的缓存大小
	int m_nInputTaskSize;
	// 输出消息队列的缓存大小
	int m_nOutputTaskSize;
	// 输入消息队列中的消息数量
	int m_nInputTask;
	// 输出消息队列中的消息数量
	int m_nOutputTask;
	// 输出当前消息队列中的数量
	int m_nOutputCurrentTask;
public:
	Task(void);
	virtual ~Task(void);
public:
	// 调用该函数处理消息队列
	virtual void Run();
	// 单线程进入
	void RunSingle();
	// 多线程进入
	void RunMultit();
	//
	void RunSingleRound();
	//
	int RunMultitRound();
public:
	// 转换队列
	void ChangePutQueue();
	// 转换队列
	void ChangeOutQueue();
	// 改变消息队列
	void ChangeQueue();
	// 使用者需要实现该函数，线程会调用该函数
	virtual void Prase(T & myT) = 0;
	// 注意：该函数不支持多线程调用
	bool StartTask(int nThreadNum);
	// 注意：该函数不支持多线程调用
	void StopTask();
	// 暂停任务
	void SuspendTask();
	// 恢复任务
	void ResumeTask();
	// 终止任务
	void TerminateTask();
	// 进入消息
	bool PutQueue(const T & myT);
	// 输出消息
	int GetQueue(T & myT);
};


template <typename T>
Task<T>::Task(void)
{
	m_bRunning = false;
	m_bStopTask = true;
	m_bSuspendTask = true;
	m_nThreadNum = 0;
	m_ppInputTaskBuf = new T[TASK_BUFF_SIZE];
	m_ppOutputTaskBuf = new T[TASK_BUFF_SIZE];

	m_nInputTaskSize = TASK_BUFF_SIZE;
	m_nOutputTaskSize = TASK_BUFF_SIZE;
	m_nInputTask = 0;
	m_nOutputTask = 0;
	m_nOutputCurrentTask = 0;
}

template <typename T>
Task<T>::~Task(void)
{
	StopTask();
	if (m_ppInputTaskBuf != NULL)
	{
		delete[] m_ppInputTaskBuf;
		m_ppInputTaskBuf = NULL;
	}
	if (m_ppOutputTaskBuf != NULL)
	{
		delete[] m_ppOutputTaskBuf;
		m_ppOutputTaskBuf = NULL;
	}
}

// 注意：该函数不支持多线程调用
template <typename T>
bool Task<T>::StartTask(int nThreadNum)
{
	if (m_bRunning) 
	{
		m_bSuspendTask = false;
		ResumeTask();
		return false;
	}
	m_bRunning = true;
	m_bStopTask = false;
	m_bSuspendTask = false;
	// 创建线程池，并启动它们
	m_nThreadNum = nThreadNum;
	if (m_nThreadNum > 0)
	{
		m_pThreadPool = new Call*[m_nThreadNum];

		for (int i = 0; i < m_nThreadNum; i++)
		{
			m_pThreadPool[i] = new Call(this);
			m_pThreadPool[i]->Start();
		}
	}

	return true;
}

// 注意：该函数不支持多线程调用
template <typename T>
void Task<T>::StopTask()
{
	if (!m_bRunning)
	{
		return;
	}
	ResumeTask();
	m_bStopTask = true;
	m_bRunning = false;
	if (m_pThreadPool != NULL)
	{
		// 等待调用run的线程退出
		if (m_nThreadNum > 0)
		{
			for (int i = 0; i < m_nThreadNum; i++)
			{
				m_pThreadPool[i]->GetThreadControl().Join();
			}
			for (int i = 0; i < m_nThreadNum; i++)
			{
				Call *pCall = m_pThreadPool[i];
				delete pCall;
				pCall = NULL;
			}
			// 清理
			if (m_pThreadPool !=- NULL)
			{
				delete [] m_pThreadPool;
				m_pThreadPool = NULL;
			}
		}
	}
	m_nThreadNum = 0;
	m_bRunning = false;
}

// 暂停任务
template <typename T>
void Task<T>::SuspendTask()
{
	if (!m_bRunning)
	{
		return;
	}
	char * myT = NULL;
	int nFlag = 0;
	m_bSuspendTask = true;
	while (TRUE)
	{
		if (m_nOutputTask == 0)
		{
			break;
		}
		SleepEx(100);
	}
	// 暂停线程
	for (int i = 0; i < m_nThreadNum; i++)
	{
		m_pThreadPool[i]->GetThreadControl().Suspend();
	}
}

// 恢复任务
template <typename T>
void Task<T>::ResumeTask()
{
	if (!m_bRunning)
	{
		return;
	}
	// 恢复线程
	for (int i = 0; i < m_nThreadNum; i++)
	{
		m_pThreadPool[i]->GetThreadControl().Resume();
	}
}

// 终止任务
template <typename T>
void Task<T>::TerminateTask()
{
	if (!m_bRunning)
	{
		return;
	}
	if (m_pThreadPool != NULL)
	{
		// 恢复线程
		for (int i = 0; i < m_nThreadNum; i++)
		{
			m_pThreadPool[i]->GetThreadControl().Terminate();
		}
	}
}

template <typename T> 
void Task<T>::Run()
{
	if (m_nThreadNum == 1)
	{
		RunSingle();
	}
	else
	{
		RunMultit();
	}
}

// 单线程处理消息队列
template <typename T> 
void Task<T>::RunSingle()
{
	while (m_bRunning)
	{
		RunSingleRound();
		SleepEx(5);
	}
}

// 单线程处理消息队列
template <typename T> 
void Task<T>::RunSingleRound()
{
	for(int i = 0; i < m_nOutputTask; i++)
	{
		Prase(m_ppOutputTaskBuf[i]);
	}
	ChangeQueue();
}

// 多线程处理消息队列
template <typename T> 
void Task<T>::RunMultit()
{
	while (m_bRunning)
	{
		if (RunMultitRound() != 1)
		{
			SleepEx(5);
		}
	}
}

// 多线程处理消息队列
template <typename T> 
int Task<T>::RunMultitRound()
{
	T myT;
	int nFlag = 0;
	nFlag = GetQueue(myT);
	if (nFlag > -1)
	{
		Prase(myT);
	}
	return nFlag;
}

template <typename T> 
int Task<T>::GetQueue(T & myT)
{
	if (!m_bRunning) 
	{
		return -1;
	}
	AutoLockT myAutoLockT(m_OutLock);
	if (m_nOutputTask == 0)
	{
		ChangeQueue();
		return -1;
	}
	myT = m_ppOutputTaskBuf[m_nOutputCurrentTask];
	m_nOutputCurrentTask++;
	if (m_nOutputCurrentTask >= m_nOutputTask)
	{
		ChangeQueue();
		return 0;
	}
	return 1;
}

template <typename T> 
bool Task<T>::PutQueue(const T & myT)
{
	if (!m_bRunning) 
	{
		return false;
	}
	if (m_bStopTask || m_bSuspendTask)
	{
		return false;
	}
	AutoLockT myAutoLockT(m_PutLock);
	if (m_nInputTask >= m_nInputTaskSize)
	{
		int nElemSize = sizeof(T);
		T *ppT = new T[m_nInputTaskSize * 2];
		memcpy(ppT, m_ppInputTaskBuf, m_nInputTask * nElemSize);
		delete[] m_ppInputTaskBuf;
		m_ppInputTaskBuf = ppT;
		m_nInputTaskSize = m_nInputTaskSize * 2;
	}
	m_ppInputTaskBuf[m_nInputTask] = myT;
	m_nInputTask++;
	return true;
}

// 转换队列
template <typename T> 
void Task<T>::ChangeQueue()
{
	AutoLockT myAutoLockT(m_PutLock);
	// 交换输入输出缓存队列
	T *ppTemp = m_ppOutputTaskBuf;
	m_ppOutputTaskBuf = m_ppInputTaskBuf;
	m_ppInputTaskBuf = ppTemp;

	// 重置队列消息数
	m_nOutputCurrentTask = 0;
	m_nOutputTask = m_nInputTask;
	m_nInputTask = 0;

	//交换缓存队列大小
	int nTemp = m_nOutputTaskSize;
	m_nOutputTaskSize = m_nInputTaskSize;
	m_nInputTaskSize = nTemp;
}

#endif // __TASK_H__