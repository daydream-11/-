
//file: lunarday.cpp
//author: cuichao@gmail.com
//2007-02-13 11:22:48
//2008-08-02 15:30:49 解决部分年份不正确的bug

#include "Stdafx.h"
#include "Lunarday.h"
#include <ctime>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;
using lunar::Date;


//使用比特位记录每年的情况
//0~4 共5bit 春节日份
//5~6 共2bit 春节月份
//7~19 共13bit 13个月的大小月情况(如果无闰月，最后位无效)，大月为1,小月为0
//20~23 共4bit 记录闰月的月份，如果没有闰月为0
static const int BEGIN_YEAR = 1901;
static const int NUMBER_YEAR = 199;
static const unsigned int LUNAR_YEARS[199] = {
     0x3a953, 0x752c8, 0x5b253d, 0x325d0, 0x54dc4,    //1901-1905
     0x4aab39, 0x2b54d, 0x5acc2, 0x2ba936, 0x3a94a,   //1906-1910
     0x6d92be, 0x592d2, 0x525c6, 0x5a55ba, 0x156ce,   //1911-1915
     0x2b5c3, 0x25b4b7, 0x6d4cb, 0x7ec941, 0x74954,   //1916-1920
     0x692c8, 0x5d26bc, 0x52b50, 0x15b45, 0x4adab8,   //1921-1925
     0x36a4d, 0x754c2, 0x2f4937, 0x7494a, 0x66933e,   //1926-1930
     0x295d1, 0x52bc6, 0x596b3a, 0x5ad4e, 0x36a44,    //1931-1935
     0x3764b8, 0x3a4cb, 0x7b49bf, 0x549d3, 0x295c8,   //1936-1940
     0x652dbb, 0x556cf, 0x2b545, 0x4daab9, 0x5d24d,   //1941-1945
     0x5a4c2, 0x2d49b6, 0x54aca, 0x7a96bd, 0x29b51,   //1946-1950
     0x556c6, 0x5ad53b, 0x2d94e, 0x5d2c3, 0x3ea538,   //1951-1955
     0x5a54c, 0x854abf, 0x54bd2, 0x2ab48, 0x655abc,   //1956-1960
     0x56acf, 0x36945, 0x4752b9, 0x752cd, 0x32542,    //1961-1965
     0x364bb5, 0x54dc9, 0x7aad3e, 0x2b551, 0x5b4c6,   //1966-1970
     0x5ba93b, 0x5a94f, 0x592c3, 0x4b25b7, 0x525cb,   //1971-1975
     0x8a55bf, 0x156d2, 0x2d6c7, 0x65b4bc, 0x6d4d0,   //1976-1980
     0x6c945, 0x4e92b9, 0x692cd, 0xad26c2, 0x52b54,   //1981-1985
     0x15b49, 0x62dabd, 0x36ad1, 0x754c6, 0x5f493b,   //1986-1990
     0x7494f, 0x69344, 0x352b37, 0x52bca, 0x8a6b3f,   //1991-1995
     0x1ad53, 0x36ac7, 0x5b64bc, 0x3a4d0, 0x349c5,    //1996-2000
     0x4a95b8, 0x295cc, 0x52dc1, 0x2aad36, 0x2b549,   //2001-2005
     0x7daabd, 0x5d252, 0x5a4c7, 0x5d49ba, 0x54ace,   //2006-2010
     0x296c3, 0x4556b7, 0x55aca, 0x9ad53f, 0x2e953,   //2011-2015
     0x6d2c8, 0x6ea53c, 0x6a550, 0x64ac5, 0x4a9739,   //2016-2020
     0x2ab4c, 0x55ac1, 0x2ad936, 0x3694a, 0x6752bd,   //2021-2025
     0x392d1, 0x325c6, 0x564bba, 0x655cd, 0x2ad43,    //2026-2030
     0x356b37, 0x5b4cb, 0xbba93f, 0x5a953, 0x592c8,   //2031-2035
     0x6d25bc, 0x525cf, 0x255c4, 0x52adb8, 0x2d6cc,   //2036-2040
     0x5b541, 0x2da936, 0x6c94a, 0x7e92be, 0x692d1,   //2041-2045
     0x52ac6, 0x5a56ba, 0x25b4e, 0x2dac2,0x355B37,    //2041-2050
     0x0764cb,0x8497C1,0x049753,0x064B48,0x66A53C,
     0x052bcf,0x06B244,0x4AB638,0x03aacc,0x03a4c2,   //2051-2060
     0x3C9735,0x0349c9,0x7D4ABD,0x0295d1,0x052dc5,
     0x55AABA,0x056A4E,0x05b2c3,0x452EB7,0x052D4B,   //2061-2070
     0x8A95BF,0x054ad3,0x0296c7,0x6B553B,0x055acf,
     0x055A45,0x4A5D38,0x06d2cc,0x052B42,0x3A93B6,   //2071-2080
     0x069349,0x7729BD,0x06AA51,0x055ac6,0x54DABA,
     0x04B64E,0x0752c3,0x452738,0x0325ca,0x8E933E,   //2081-2090
     0x0255d2,0x02adc7,0x66B53B,0x056D4F,0x04AE45,
     0x4A4EB9,0x0592cc,0x0545c1,0x2D92B5             //2091-2099  
};

static const TCHAR *CH_NUMBER_V[] =
{
	_T("零"),
	_T("一"),
	_T("二"),
	_T("三"),
	_T("四"),
	_T("五"),
	_T("六"),
	_T("七")
	_T("八"),
	_T("九"),
	_T("十")
};

static const TCHAR *CH_MONTH_V[] =
{	
	_T("*"),
	_T("正"),
	_T("二"),
	_T("三"),
	_T("四"),
	_T("五"),
	_T("六"),
	_T("七"),
	_T("八"),
	_T("九"),
	_T("十"),
	_T("十一"),
	_T("腊")
};

static const TCHAR *CH_DAY_V[] =
{
	_T("*"),
	_T("初一"),
	_T("初二"),
	_T("初三"),
	_T("初四"),
	_T("初五"),
	_T("初六"),
	_T("初七"),
	_T("初八"),
	_T("初九"),
	_T("初十"),
	_T("十一"),
	_T("十二"),
	_T("十三"),
	_T("十四"),
	_T("十五"),
	_T("十六"),
	_T("十七"),
	_T("十八"),
	_T("十九"),
	_T("二十"),
	_T("廿一"),
	_T("廿二"),
	_T("廿三"),
	_T("廿四"),
	_T("廿五"),
	_T("廿六"),
	_T("廿七"),
	_T("廿八"),
	_T("廿九"),
	_T("三十")
};

static const TCHAR *CH_YEAR = _T("年");
static const TCHAR *CH_MONTH = _T("月");
static const TCHAR *CH_DAY = _T("日");
static const TCHAR *CH_SP = _T("");
static const TCHAR *CH_LEAP = _T("闰");


//计算这个公历日期是一年中的第几天
static int DayOfSolarYear(int year, int month, int day )
{
     //为了提高效率，记录每月一日是一年中的第几天
     static const int NORMAL_YDAY[12] = {1,32,60,91,121,152,
					 182,213,244,274,305,335};
     //闰年的情况
     static const int LEAP_YDAY[12] = {1,32,61,92,122,153,
				       183,214,245,275,306,336};     
     const int *t_year_yday_ = NORMAL_YDAY;    
     
     //判断是否是公历闰年
     if( year % 4 ==0 )
     {
	  if(year%100 != 0)	  
	       t_year_yday_ = LEAP_YDAY;
	  if(year%400 == 0)
	       t_year_yday_ = LEAP_YDAY;	  	  	  
     }     
     return t_year_yday_[month -1] + (day -1);      
}



Date lunar::LuanrDate(int solar_year,int solar_month,int solar_day)
{
     Date luanr_date ;     
     luanr_date.year = solar_year;
     luanr_date.month = 0;
     luanr_date.day = 0;
     luanr_date.leap = false;
     
     //越界检查，如果越界，返回无效日期
     if(solar_year <= BEGIN_YEAR || solar_year > BEGIN_YEAR + NUMBER_YEAR - 1 )
     	  return luanr_date;
          
     int year_index = solar_year - BEGIN_YEAR;
     
     //计算春节的公历日期
     int spring_ny_month = ( LUNAR_YEARS[year_index] & 0x60 ) >> 5;
     int spring_ny_day = ( LUNAR_YEARS[year_index] & 0x1f);     
     
     //计算今天是公历年的第几天
     int today_solar_yd = DayOfSolarYear(solar_year,solar_month,solar_day);
     //计算春节是公历年的第几天
     int spring_ny_yd = DayOfSolarYear(solar_year,spring_ny_month,spring_ny_day);
     //计算今天是农历年的第几天
     int today_luanr_yd = today_solar_yd - spring_ny_yd + 1;
     //如果今天在春节的前面，重新计算today_luanr_yd
     if ( today_luanr_yd <= 0 ) 
     {
 	  //农历年比当前公历年小1
	  year_index --;
	  luanr_date.year --;
	  //越界，返回无效日期
	  if(year_index <0)
	       return luanr_date;
	  spring_ny_month = ( LUNAR_YEARS[year_index] & 0x60 ) >> 5;
	  spring_ny_day = ( LUNAR_YEARS[year_index] & 0x1f);	  
	  spring_ny_yd = DayOfSolarYear(solar_year,spring_ny_month,spring_ny_day);
	  	  
	  int year_total_day = DayOfSolarYear(luanr_date.year,12,31);	  	  
	  today_luanr_yd = today_solar_yd + year_total_day - spring_ny_yd + 1;	  
     }
     
     int luanr_month = 1;
     //计算月份和日期
     for(;luanr_month<=13;luanr_month++)
     {	  
	  int month_day  = 29;	  
	  if( (LUNAR_YEARS[year_index] >> (6 + luanr_month)) & 0x1 )
	       month_day = 30;	       
	  if( today_luanr_yd <= month_day )
	       break;   
	  else
	       today_luanr_yd -= month_day;	       
     }
     luanr_date.day = today_luanr_yd;
     //处理闰月
     int leap_month = (LUNAR_YEARS[year_index] >>20)  & 0xf;     
     if(leap_month > 0 && leap_month < luanr_month )
     {	  
	  luanr_month --;
	  //如果当前月为闰月，设置闰月标志
	  if( luanr_month == leap_month )	  
	       luanr_date.leap = true;	  	  
     }
     assert(leap_month <= 12);     
     luanr_date.month = luanr_month;          
     return luanr_date;     
}



const TCHAR * lunar::to_ch_str(const Date &lunar_date)
{
     static TCHAR buf[MAX_CH_DATE_LEN+1];
     return to_ch_str_r(lunar_date,buf);     
}

const TCHAR * lunar::to_ch_str_r(const Date &lunar_date,TCHAR *buf)
{
     
     TCHAR *pbuf = buf;
     
     int t_idx = 0; 
     
     _tcscpy(pbuf,CH_SP);     
     pbuf += _tcslen(CH_SP);
     
     if(lunar_date.leap)
     {
	  _tcscpy(pbuf,CH_LEAP);	  
	  pbuf += _tcslen(CH_LEAP);	  
     }

     t_idx = lunar_date.month;
     _tcscpy(pbuf,CH_MONTH_V[t_idx]);
     pbuf += _tcslen(CH_MONTH_V[t_idx]);
     
     _tcscpy(pbuf,CH_MONTH);
     pbuf += _tcslen(CH_MONTH);

     t_idx = lunar_date.day;     
     _tcscpy(pbuf,CH_DAY_V[t_idx]);
     pbuf += _tcslen(CH_DAY_V[t_idx]);     
     pbuf = '\0';
     assert(pbuf - buf <= MAX_CH_DATE_LEN);     
     
     return buf;     
}   

