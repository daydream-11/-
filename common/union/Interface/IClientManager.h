#ifndef __I_CLIENT_MANAGER_H__
#define __I_CLIENT_MANAGER_H__

#include "IOCPInterface.h"
#include "IPlayerConnect.h"

class IClientManager
{
public:
	virtual ~IClientManager()
	{

	}
	// 初始化服务器
	virtual BOOL Init(SClientConfig *pSClientConfig, ProcessNetworkMsgProc pProcessNetworkMsgProc, ProcessSetLogProc pProcessSetLogProc) = 0;
	// 获取指定的连接对象
	virtual IPlayerConnect* GetPlayerConnect(UINT uIndex) = 0;
	// 获取没有分配的连接
	virtual IPlayerConnect* GetNoUsePlayerConnect() = 0;
	// 连接服务器
	virtual IPlayerConnect* Connect(const CHAR * lpszhost, UINT uPort) = 0;
	// 连接服务器
	virtual BOOL Connect(IPlayerConnect *pPlayerConnect, const CHAR * lpszhost, UINT uPort) = 0;
	// 断开服务器
	virtual BOOL DisConnect(IPlayerConnect *pPlayerConnect) = 0;
};

IClientManager* GetStaticClientManager();

#endif	// __I_CLIENT_MANAGER_H__