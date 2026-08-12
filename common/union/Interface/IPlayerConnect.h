#ifndef __I_PLAYER_CONNECT_H__
#define __I_PLAYER_CONNECT_H__

#include "IOCPInterface.h"
#include "IPlayer.h"


// 连接的模式
enum EConnectMode
{
	// 正常连接（会有心跳包，心跳会断开）
	ENormalConnected,
	// 安全策略连接（会有心跳包，心跳会断开）
	ESafetyConnected,
	// 一直连接（不会有心跳，一直连接着）
	EStraightConnected
};

class IPlayerConnect
{
public:
	virtual ~IPlayerConnect()
	{

	}
public:
	// 发送网络消息
	virtual BOOL SendNetMsg(const char * pSendMsg, INT nMsgLen) = 0;
	// 发送客户端消息
	virtual BOOL SendClientMsg(const char * pSendMsg, INT nMsgLen) = 0;
	// 获取玩家信息
	virtual IPlayer* GetPlayer() = 0;
	// 设置日志信息
	virtual VOID SetLog(CHAR* msg, ... ) = 0;
	// 设置设置写入日志文件名
	virtual VOID SetLogName(CHAR *szLogName) = 0;
	// 获取连接IP
	virtual const CHAR* GetIP() = 0;
	// 设置连接模式
	virtual VOID SetConnectMode(EConnectMode eConnectMode) = 0;
	// 断开连接
	virtual VOID DisConnect() = 0;
	// 判断是否已经连接状态
	virtual BOOL IsAlreadyConnected() = 0;
#if defined (__LINUX__)
	virtual VOID* GetEpollObjectInfo() = 0;
#endif
};


#endif	// __I_PLAYER_CONNECT_H__