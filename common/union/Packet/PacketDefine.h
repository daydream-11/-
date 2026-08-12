#ifndef __PACKET_DEFINE_H__
#define __PACKET_DEFINE_H__

#include "GameDefine.h"
#include "ServerPacket.h"
#include "InstallPacket.h"

// 请求服务端消息
enum CLIENT_SEND_COMMON_PACKET_DEFINE
{
	// 请求心跳包数据
	REQ_PLAYER_HEART_BEAT = CLIENT_SEND_COMMON_PACKET_NODE + 2,
};


// 服务器跟服务器之间消息连接
enum SERVER_CONNECT_SERVER_PACKET_DEFINE
{
	// 请求连接服务器标识符
	REQ_CONNECT_SERVER_IDENTIFIER = 0xFF00,
	// 请求反馈服务器标识符
	REQ_REPLY_SERVER_IDENTIFIER = 0xFF01,
	// 请求断开服务器标识符
	REQ_DIS_CONNECT_SERVER_IDENTIFIER = 0xFF02,
	// 请求通知服务器场景信息
	REQ_INFORM_SCENE_PUT_UP_INFO = 0xFF03,
	// 请求设置玩家标识符
	REQ_PLAYER_SET_IDENTIFIER = 0xFF04,
	// 请求处理玩家重复标识符
	REQ_PLAYER_REPEAT_IDENTIFIER = 0xFF05,
	// 请求通知服务器战斗信息
	REQ_INFORM_FIGHT_PUT_UP_INFO = 0xFF06,
	// 请求通知服务器副本信息
	REQ_INFORM_ECTYPE_PUT_UP_INFO = 0xFF07,
	// 请求暂停日志
	REQ_SUSPEND_LOG = 0xFFF0,
	// 请求恢复日志
	REQ_ALLOW_LOG = 0xFFF1,
	// 请求清空日志
	REQ_CLEAR_LOG = 0xFFF2,
	// 请求查看服务器在线人数
	REQ_LOOK_SERVER_ONLINE_PLAYER_NUM = 0xFFF3,
	// 请求查看服务器内存对象使用
	REQ_LOOK_SERVER_MEMORY_OBJECT_USE = 0xFFF4,
	
};

/***************************************************************************
// 服务器ID范围定义
***************************************************************************/
enum SERVER_BOUND
{
	// 服务器起始编号
	SERVER_APPLICATION_IDENTIFIER_BEGIN = 1000,
	// 代理服务器编号
	MMORPG_AGENT_SERVER = 1900,
	// 场景服务器编号
	MMORPG_SCENE_START_SERVER = 2000,
	// 场景服务器编号
	MMORPG_SCENE_END_SERVER = 3000,
	// 登陆服务器编号
	MMORPG_LOGIN_SERVER = 3100,
	// 中心服务器编号
	MMORPG_CENTER_SERVER = 3101,
	// 数据库服务器编号
	MMORPG_DBSERVER_SERVER = 3102,
	// 世界服务器编号
	MMORPG_WORLD_SERVER = 3103,
	// 日志服务器编号
	MMORPG_LOG_SERVER = 3104,
	// 平台服务器编号
	MMORPG_PLATFORM_SERVER = 3105,
	// 市场服务器编号
	MMORPG_MARKET_SERVER = 3106,
	// 附加服务器编号
	MMORPG_SUBJOIN_SERVER = 3107,
	// 战斗服务器起始编号
	MMORPG_FIGHT_START_SERVER = 4000,
	// 战斗服务器结束编号
	MMORPG_FIGHT_END_SERVER = 5000,
	// 服务器结束编号
	SERVER_APPLICATION_IDENTIFIER_END = 5001
};

#pragma pack(push,1)				//网络消息定义，一律要字节对齐

// 请求心跳包数据
struct ReqPlayerHeartBeat: public ServerPacketHeader
{
	//
	void serialize(UINT uPlayerID)
	{
		ServerPacketHeader::serialize(uPlayerID, REQ_PLAYER_HEART_BEAT, (USHORT)sizeof(ReqPlayerHeartBeat));
	}
};


// 请求连接服务器标识符
struct ReqConnectServerIdentifier: public PacketHeader
{
	UINT uServerIdentifierID;
	//
	void serialize(UINT uServerIdentifierID)
	{
		this->uServerIdentifierID = uServerIdentifierID;
		PacketHeader::serialize(REQ_CONNECT_SERVER_IDENTIFIER, (USHORT)sizeof(ReqConnectServerIdentifier));
	}
};

// 请求反馈服务器标识符
struct ReqReplyServerIdentifier: public PacketHeader
{
	UINT uServerIdentifierID;
	//
	void serialize(UINT uServerIdentifierID)
	{
		this->uServerIdentifierID = uServerIdentifierID;
		PacketHeader::serialize(REQ_REPLY_SERVER_IDENTIFIER, (USHORT)sizeof(ReqReplyServerIdentifier));
	}
};

// 请求断开服务器标识符
struct ReqDisConnectServerIdentifier: public PacketHeader
{
	UINT uServerIdentifierID;
	UINT uServerIdentifierIndex;
	//
	void serialize(UINT uServerIdentifierID, UINT uServerIdentifierIndex)
	{
		this->uServerIdentifierID = uServerIdentifierID;
		this->uServerIdentifierIndex = uServerIdentifierIndex;
		PacketHeader::serialize(REQ_DIS_CONNECT_SERVER_IDENTIFIER, (USHORT)sizeof(ReqDisConnectServerIdentifier));
	}
};


// 请求暂停日志
struct ReqSuspendLog: public PacketHeader
{
	//
	VOID serialize()
	{
		PacketHeader::serialize(REQ_SUSPEND_LOG, (USHORT)sizeof(ReqSuspendLog));
	}
};

// 请求恢复日志
struct ReqAllowLog: public PacketHeader
{
	//
	VOID serialize()
	{
		PacketHeader::serialize(REQ_ALLOW_LOG, (USHORT)sizeof(ReqAllowLog));
	}
};

// 请求清空日志
struct ReqClearLog: public PacketHeader
{
	//
	VOID serialize()
	{
		PacketHeader::serialize(REQ_CLEAR_LOG, (USHORT)sizeof(ReqClearLog));
	}
};

// 请求查看服务器在线人数
struct ReqLookServerOnlinePlayerNum: public PacketHeader
{
	//
	VOID serialize()
	{
		PacketHeader::serialize(REQ_LOOK_SERVER_ONLINE_PLAYER_NUM, (USHORT)sizeof(ReqLookServerOnlinePlayerNum));
	}
};

// 请求查看内存对象使用情况
struct ReqLookServerMemoryObjectUse : public PacketHeader
{
	//
	VOID serialize()
	{
		PacketHeader::serialize(REQ_LOOK_SERVER_MEMORY_OBJECT_USE, (USHORT)sizeof(ReqLookServerMemoryObjectUse));
	}
};


#pragma pack(pop)			// 取消字节对齐

#endif	// __PACKET_DEFINE_H__

