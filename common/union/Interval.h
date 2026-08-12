#ifndef __MY_INTERVAL_H__
#define __MY_INTERVAL_H__
#include "CommonUtil.h"

class CMyInterval
{
public:
	LARGE_INTEGER m_liBeginTime;
	LARGE_INTEGER m_liEndTime;
	LARGE_INTEGER m_liFreqcy;
public :
	CMyInterval()
	{
		QueryPerformanceFrequency(&m_liFreqcy);
	};
	~CMyInterval()
	{
	};
public:
	void OnInterval()
	{
		QueryPerformanceCounter(&m_liBeginTime);
	};
	void UnInterval()
	{
		QueryPerformanceCounter(&m_liEndTime);
	};
	LONGLONG GetInterval()
	{
		return ((m_liEndTime.QuadPart - m_liBeginTime.QuadPart) * 1000) / m_liFreqcy.QuadPart;
	}
};
class CAutoIntervalT
{
public:
	CAutoIntervalT(const TCHAR *lpszLogValue)
	{
		m_strLogValue = lpszLogValue;
		OnInterval();
	}
	~CAutoIntervalT()
	{
		UnInterval();
		CommonUtil::WriteDebugLog(_T("%s(%d)"), m_strLogValue.c_str(), m_myInterval.GetInterval());
	}
private:
	inline void OnInterval()
	{
		m_myInterval.OnInterval();
	}
	inline void UnInterval() 
	{
		m_myInterval.UnInterval();
	}
private:
	xstring m_strLogValue;
	CMyInterval m_myInterval;
};



#endif // __MY_INTERVAL_H__
