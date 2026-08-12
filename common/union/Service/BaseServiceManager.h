#ifndef __BASE_SERVICE_MANAGER_H__
#define __BASE_SERVICE_MANAGER_H__

#include "DLL.h"

class CBaseServiceManager : public CDllClass
{
public:
	// 开始运行服务
	virtual VOID StartService() = 0;
	// 测试运行服务
	virtual VOID TestService() = 0;
};

#endif	// __BASE_SERVICE_MANAGER_H__

