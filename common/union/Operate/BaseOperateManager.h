#ifndef __BASE_OPERATE_MANAGER_H__
#define __BASE_OPERATE_MANAGER_H__

#include "DLL.h"

class CBaseOperateManager : public CDllClass
{
public:
	// 
	virtual VOID DoRunLoadDataEngine() = 0;
	// 
	virtual VOID DoLoadDataEngine() = 0;
};

#endif	// __BASE_OPERATE_MANAGER_H__


