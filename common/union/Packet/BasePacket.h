#ifndef __BASE_PACKET_H__
#define __BASE_PACKET_H__

#include "BaseType.h"


/*****************************************发送代理服务器消息开始*****************************************/

// 定义客户端发送给服务器服务器最小消息号
#define CLIENT_SEND_SERVER_PACKET_NONE 0x0500
// 定义客户端发送给代理服务器最大消息号
#define CLIENT_SEND_SERVER_PACKET_MAX CLIENT_SEND_SERVER_PACKET_NONE + 50

// 定义服务端发送给服务器最小消息号
#define SERVER_SEND_SERVER_PACKET_NONE CLIENT_SEND_SERVER_PACKET_MAX + 1
// 定义服务端发送给服务器最大消息号
#define SERVER_SEND_SERVER_PACKET_MAX SERVER_SEND_SERVER_PACKET_NONE + 50

/*****************************************发送代理服务器消息结束*****************************************/

// 定义客户端发送给服务器共用消息
#define CLIENT_SEND_COMMON_PACKET_NODE 0x4F00
	
// 定义服务器发送给客户端最小消息编号
#define SERVER_SEND_CLIENT_PACKET_NODE 0x5000

// 登陆服务器发送给客户端消息
#define LOGIN_SEND_CLIENT_PACKET_NONE 0x5101

// 定义服务器发送给客户端最大消息编号
#define SERVER_SEND_CLIENT_PACKET_MAX 0xEFFF

// 定义客户端错误消息开始编号
#define CLIENT_ERROR_BEGIN_CODE		0x5000
// 定义客户端错误消息开始编号
#define CLIENT_SUCCEED_BEGIN_CODE	0x0000



// 客户端发送服务器
enum CLIENT_SEND_SERVER_PACKET_DEFINE
{
	// 请求初始化服务器
	REQ_INIT_SERVER_SYSTEM = CLIENT_SEND_SERVER_PACKET_NONE + 1,
	// 请求发送玩家安装信息
	REQ_PLAYER_INSTALL_INFO = CLIENT_SEND_SERVER_PACKET_NONE + 2,
	// 请求发送玩家在线信息
	REQ_PLAYER_ONLINE_INFO = CLIENT_SEND_SERVER_PACKET_NONE + 3,
	// 请求发送玩家卸载信息
	REQ_PLAYER_UNINST_INFO = CLIENT_SEND_SERVER_PACKET_NONE + 4,
	// 请求发送玩家安装过去数据
	REQ_PLAYER_INSTALL_PAST = CLIENT_SEND_SERVER_PACKET_NONE + 5,
	// 请求发送玩家升级数据
	REQ_PLAYER_UPGRADE_INFO = CLIENT_SEND_SERVER_PACKET_NONE + 6,
	// 请求发送玩家安装信息
	REQ_PLAYER_INSTALL_INFOV1 = CLIENT_SEND_SERVER_PACKET_NONE + 7,
	// 请求发送玩家安装过去数据
	REQ_PLAYER_INSTALL_PASTV1 = CLIENT_SEND_SERVER_PACKET_NONE + 8,
	// 请求其他软件安装信息
	REQ_OTHER_SOFT_INSTALL_INFO = CLIENT_SEND_SERVER_PACKET_NONE + 9,
	// 请求其他软件在线信息
	REQ_OTHER_SOFT_ONLINE_INFO = CLIENT_SEND_SERVER_PACKET_NONE + 10,
	// 请求发送玩家安装信息
	REQ_PLAYER_INSTALL_INFOV2 = CLIENT_SEND_SERVER_PACKET_NONE + 11,
	// 请求发送玩家安装过去数据
	REQ_PLAYER_INSTALL_PASTV2 = CLIENT_SEND_SERVER_PACKET_NONE + 12,
	// 请求发送玩家访问迷你数据
	REQ_PLAYER_BROWSE_MINI_INFO = CLIENT_SEND_SERVER_PACKET_NONE + 13,
	// 请求发送玩家安装信息
	REQ_PLAYER_INSTALL_INFOV3 = CLIENT_SEND_SERVER_PACKET_NONE + 14,
	// 请求发送玩家安装过去数据
	REQ_PLAYER_INSTALL_PASTV3 = CLIENT_SEND_SERVER_PACKET_NONE + 15,
	// 请求发送玩家安装信息
	REQ_PLAYER_INSTALL_INFOV4 = CLIENT_SEND_SERVER_PACKET_NONE + 16,
};

// 服务器发送服务器
enum SERVER_SEND_SERVER_PACKET_DEFINE
{
	// 请求打开事务状态
	REQ_OPEN_TRANSACTION_STATUS = SERVER_SEND_SERVER_PACKET_NONE + 1,
	// 请求关闭事务
	REQ_CLOSE_TRANSACTION_STATUS = SERVER_SEND_SERVER_PACKET_NONE + 2,
	// 请求查询活跃用户
	REQ_QUERY_ACTIVE_USER_INFO = SERVER_SEND_SERVER_PACKET_NONE + 3,
};


// UTF8格式字符串拷贝
static void LimitLengthStrcpy(char* szDest, const char* szSource, UINT uCopyLen)
{
    if (!szSource || !szDest || uCopyLen == 0)
    {
        return;
    }
    memcpy(szDest, szSource, uCopyLen);
}

// 发送消息额外分配字节大小
#define EXTRA_MALLC_SIZE 4
// 消息包内存块
struct PacketMemoryBlock
{
	// 连接对象的内存
	VOID* pPlayerConnect;
	// 指向消息头内存
	VOID* pPacketHeader;
	// 保存预分配消息的内存池
	VOID *pPacketBlock;
};

#pragma pack(push,1)				//网络消息定义，一律要字节对齐


struct PacketPlayerConnect
{
	VOID *pPlayerConnect;
};

struct PacketHeader			
{
	// 包头
	BYTE byHead[2];
	// 消息包ID
	PacketID packetID;
	// 消息长度
	USHORT uPacketLen;
	VOID serialize(PacketID packetID, USHORT uPacketLen)
	{
		byHead[0] = 0x7B;			//'{'字符
		byHead[1] = 0x7D;			//'}'字符
		this->packetID = packetID;
		this->uPacketLen = uPacketLen;
	}
	// 设置消息长度
	VOID SetPacketLen(USHORT uPacketLen)
	{
		this->uPacketLen = uPacketLen;
	}
	// 获取连接对象（此连接对象，一般是客户端跟代理服务器的连接）
	VOID* GetPlayerConnect()
	{
		PacketPlayerConnect *pPacketPlayerConnect = (PacketPlayerConnect*)((char*)this + (uPacketLen - 4));
		return pPacketPlayerConnect->pPlayerConnect;
	}
	// 设置额外附加的数据（一般是客户端跟代理服务器的连接）
	VOID SetExtraData(VOID *pPlayerConnect)
	{
		PacketPlayerConnect *pPacketPlayerConnect = (PacketPlayerConnect*)((char*)this + uPacketLen);
		pPacketPlayerConnect->pPlayerConnect = pPlayerConnect;
		uPacketLen += sizeof(pPlayerConnect);
	}
};

// 定义客户端向服务器发送的消息
struct ServerPacketHeader : public PacketHeader		
{
	// 玩家ID（一般是客户端玩家在游戏中的玩家索引，不是真实的玩家在数据库中的玩家ID）
	UINT uPlayerID;
	//
	void serialize(UINT uPlayerID, PacketID nPacketID, USHORT packetLen)
	{
		this->uPlayerID = uPlayerID;
		PacketHeader::serialize(nPacketID, packetLen);
	}
};

// 定义机器人客户端
#if defined ROBOT_CLIENT
struct ClientPacketHeader : public PacketHeader
{
	//
	void serialize(UINT uPlayerID, PacketID nPacketID, USHORT packetLen)
	{
		PacketHeader::serialize(nPacketID, packetLen);
	}
};
#else if
// 定义非机器人客户端
struct ClientPacketHeader : public PacketHeader		
{
	// 玩家ID
	UINT uPlayerID;
	//
	void serialize(UINT uPlayerID, PacketID nPacketID, USHORT packetLen)
	{
		this->uPlayerID = uPlayerID;
		PacketHeader::serialize(nPacketID, packetLen);
	}
};

#endif

#pragma pack(pop)			//取消字节对齐

#define	PACKET_HEADER_SIZE sizeof(PacketHeader)

#endif	// __BASE_PACKET_H__

