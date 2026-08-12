#ifndef __I_SERVER_MANAGER_H__
#define __I_SERVER_MANAGER_H__

#include "IOCPInterface.h"

class IServerManager
{
public:
	virtual ~IServerManager()
	{

	}
	// 初始化服务器
	virtual BOOL Init(SConnectConfig *pSConnectConfig, ProcessNetworkMsgProc pProcessNetworkMsgProc, ProcessSetLogProc pProcessSetLogProc) = 0;
	// 通过索引获取连接对象
	virtual VOID* GetPlayerConnect(UINT uPlayerConnectIndex) = 0;
	// 关闭客户端连接
	virtual VOID ClosePlayerConnect(VOID *pPlayerConnect) = 0;
};

IServerManager* GetStaticServerManager();

#endif	// __I_SERVER_MANAGER_H__