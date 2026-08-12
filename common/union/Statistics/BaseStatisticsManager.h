#ifndef __BASE_STATISTICS_MANAGER_H__
#define __BASE_STATISTICS_MANAGER_H__

#include "DLL.h"

class CBaseStatisticsManager 
{
public:
	//// 豌豆荚打开统计
	//virtual VOID DoWdjOpenStatistics(INT nOpenType, const TCHAR *lpszAdvertIdentifier, int nUserOperation = 0, DWORD dwTickCount = 0) = 0;
	//// 豌豆荚安装应用统计
	//virtual VOID DoWdjInstallAppStatistics(INT nOpenType, const TCHAR *lpszAdvertIdentifier, int nFlag, int nAppID, const TCHAR *lpszAppName) = 0;
	//// 豌豆荚展示应用统计 szAppID = 1|2|3|4; 
	//virtual VOID DoWdjShowApkStatics(const TCHAR *lpszAdvertIdentifier, const TCHAR *szAppID, const TCHAR *lpszAppName) = 0;
public:
	// 发送软件安装信息
	virtual BOOL DoSendSoftInstallInfo(const CHAR *lpszInstallParam){return true;};
	// 发送软件在线信息
	//virtual VOID DoSendSoftOnlineInfo(const CHAR *lpszInstallParam) = 0;
	/// 发送软件活跃信息
	//virtual BOOL DoSendSoftActiveInfo(const CHAR *lpszActiveParam) = 0;
	// 发送软件卸载信息
	//virtual VOID DoSendSoftUninstInfo(const CHAR *lpszInstallParam) = 0;
};

#endif	// __BASE_STATISTICS_MANAGER_H__


