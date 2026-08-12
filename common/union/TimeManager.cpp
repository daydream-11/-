#include "stdafx.h"
#include "TimeManager.h"

TimeManager * g_pTimeManager = NULL;

TimeManager::TimeManager()
{
	__ENTER_FUNCTION

	m_uCurrentTime = 0;

	__LEAVE_FUNCTION
}

TimeManager::~TimeManager()
{
	__ENTER_FUNCTION


	__LEAVE_FUNCTION
}

BOOL TimeManager::Init()
{
	__ENTER_FUNCTION

#if defined (__WINDOWS__)
	m_uStartTime = ::GetTickCount();
	m_uCurrentTime = ::GetTickCount();
#elif defined(__LINUX__)
	m_uStartTime = 0;
	m_uCurrentTime = 0;
	gettimeofday(&_tstart, &tz);
#endif
	SetTime();

	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

UINT TimeManager::GetCurrentTime()
{
	__ENTER_FUNCTION

#if defined(__WINDOWS__)
	m_uCurrentTime = ::GetTickCount() ;
#elif defined(__LINUX__)
	gettimeofday(&_tend,&tz);
	double t1, t2;
	t1 =  (double)_tstart.tv_sec*1000 + (double)_tstart.tv_usec/1000;
	t2 =  (double)_tend.tv_sec*1000 + (double)_tend.tv_usec/1000;
	m_uCurrentTime = (UINT)(t2-t1);
#endif

	return m_uCurrentTime;

	__LEAVE_FUNCTION

	return 0 ;
}

// 取得服务器端程序启动时的时间计数值
UINT TimeManager::GetStartTime()
{
	return m_uStartTime; 
}

// 取得服务器启动后的运行时间（毫秒）
UINT TimeManager::RunTime()
{ 
	GetCurrentTime() ;
	return (m_uCurrentTime - m_uStartTime);  
}


UINT TimeManager::CurrentDate()
{
	__ENTER_FUNCTION

	SetTime() ;
	UINT Date;
	ConvertTU(&m_TM,Date);

	return Date;

	__LEAVE_FUNCTION

		return 0;
}


VOID TimeManager::SetTime()
{
	__ENTER_FUNCTION

	time( &m_SetTime ) ;
	tm* ptm = localtime( &m_SetTime ) ;
	m_TM = *ptm ;

	__LEAVE_FUNCTION
}

// 得到标准时间
time_t TimeManager::GetANSITime()
{
	__ENTER_FUNCTION

	SetTime();

	__LEAVE_FUNCTION

	return m_SetTime;
}

UINT TimeManager::Time2DWORD()
{
	__ENTER_FUNCTION

	SetTime() ;

	UINT uRet=0 ;

	uRet += GetYear() ;
	uRet -= 2000 ;
	uRet =uRet*100 ;

	uRet += GetMonth()+1 ;
	uRet =uRet*100 ;

	uRet += GetDay() ;
	uRet =uRet*100 ;

	uRet += GetHour() ;
	uRet =uRet*100 ;

	uRet += GetMinute() ;

	return uRet ;

	__LEAVE_FUNCTION

	return 0 ;
}

UINT TimeManager::DiffTime( UINT Date1, UINT Date2 )
{
	__ENTER_FUNCTION

	tm S_D1, S_D2 ;
	ConvertUT( Date1, &S_D1 ) ;
	ConvertUT( Date2, &S_D2 ) ;
	time_t t1,t2 ;
	t1 = mktime(&S_D1) ;
	t2 = mktime(&S_D2) ;
	UINT dif = (UINT)(difftime(t2,t1)*1000) ;
	return dif ;

	__LEAVE_FUNCTION

	return 0 ;
}

VOID TimeManager::ConvertUT( UINT Date, tm* TM )
{
	__ENTER_FUNCTION

	Assert(TM) ;
	memset( TM, 0, sizeof(tm) ) ;
	TM->tm_year = (Date>>26)&0xf ;
	TM->tm_mon  = (Date>>22)&0xf ;
	TM->tm_mday = (Date>>17)&0x1f ;
	TM->tm_hour = (Date>>12)&0x1f ;
	TM->tm_min  = (Date>>6) &0x3f ;
	TM->tm_sec  = (Date)    &0x3f ;

	__LEAVE_FUNCTION
}

VOID TimeManager::ConvertTU( tm* TM, UINT& Date )
{
	__ENTER_FUNCTION

	Assert( TM ) ;
	Date = 0 ;
	Date += (TM->tm_yday%10) & 0xf ;
	Date = (Date<<4) ;
	Date += TM->tm_mon & 0xf ;
	Date = (Date<<4) ;
	Date += TM->tm_mday & 0x1f ;
	Date = (Date<<5) ;
	Date += TM->tm_hour & 0x1f ;
	Date = (Date<<5) ;
	Date += TM->tm_min & 0x3f ;
	Date = (Date<<6) ;
	Date += TM->tm_sec & 0x3f ;

	__LEAVE_FUNCTION
}

UINT TimeManager::GetDayTime()
{
	__ENTER_FUNCTION

	time_t st ;
	time( &st ) ;
	tm* ptm = localtime( &m_SetTime ) ;

	UINT uRet=0 ;

	uRet  = (ptm->tm_year-100)*1000 ;
	uRet += ptm->tm_yday ;

	return uRet ;

	__LEAVE_FUNCTION

	return 0 ;
}

INT TimeManager::GetTodayTime()
{
	__ENTER_FUNCTION
	time_t st ;
	time( &st ) ;
	tm* ptm = localtime( &m_SetTime ) ;

	INT uRet=0 ;

	uRet  = ptm->tm_hour*100 ;
	uRet += ptm->tm_min ;

	return uRet ;

__LEAVE_FUNCTION

return 0 ;
}

BOOL TimeManager::FormatTodayTime(INT& nTime)
{
	__ENTER_FUNCTION
	BOOL ret = FALSE;

	INT wHour = nTime / 100;
	INT wMin = nTime % 100;
	INT wAddHour = 0;
	if( wMin > 59 )
	{
		wAddHour = wMin / 60;
		wMin = wMin % 60;
	}
	wHour += wAddHour;
	if( wHour > 23 )
	{
		ret = TRUE;
		wHour = wHour % 60;
	}

	return ret;

	__LEAVE_FUNCTION

return FALSE ;
}
