#ifndef __SERVER_PACKET_H__
#define __SERVER_PACKET_H__

#include "BasePacket.h"
#include "GameDefine.h"

#pragma pack(push,1)				//网络消息定义，一律要字节对齐

// 请求初始化服务器
struct ReqInitServerSystem : public PacketHeader
{
	//
	void serialize()
	{
		PacketHeader::serialize(REQ_INIT_SERVER_SYSTEM, (USHORT)sizeof(ReqInitServerSystem));
	}
};

// 请求打开事务状态
struct ReqOpenTransactionStatus : public PacketHeader
{
	//
	void serialize()
	{
		PacketHeader::serialize(REQ_OPEN_TRANSACTION_STATUS, (USHORT)sizeof(ReqOpenTransactionStatus));
	}
};

// 请求关闭事务状态
struct ReqCloseTransactionStatus : public PacketHeader
{
	//
	void serialize()
	{
		PacketHeader::serialize(REQ_CLOSE_TRANSACTION_STATUS, (USHORT)sizeof(ReqCloseTransactionStatus));
	}
};


// 请求查询活跃用户
struct ReqQueryActiveUserInfo : public PacketHeader
{
	// 查询开始日期
	INT nStartDate;
	// 查询的天数
	INT nQueryDay;
	// 推广商标示符
	CHAR szAdvertIdentifier[MAX_ADVERT_IDENTIFIER_LENGTH];
	//
	void serialize
		(
		INT nStartDate,
		INT nQueryDay,
		const CHAR * szAdvertIdentifier
		)
	{
		this->nStartDate = nStartDate;
		this->nQueryDay = nQueryDay;
		strcpy(this->szAdvertIdentifier, szAdvertIdentifier);
		PacketHeader::serialize(REQ_QUERY_ACTIVE_USER_INFO, (USHORT)sizeof(ReqQueryActiveUserInfo));
	}
};

// 请求发送玩家卸载信息
struct ReqPlayerUninstInfo : public PacketHeader
{
	// 玩家标示符
	CHAR szPlayerIdentifier[MAX_PLAYER_IDENTIFIER_LENGTH];
	// 软件标示符
	CHAR szSoftIdentifier[MAX_SOFT_IDENTIFIER_LENGTH];
	// 软件版本
	CHAR szSoftVer[MAX_SOFT_VER_LENGTH];
	// 推广商标示符
	CHAR szAdvertIdentifier[MAX_ADVERT_IDENTIFIER_LENGTH];
	//
	void serialize
		(
		const CHAR * szPlayerIdentifier,
		const CHAR * szSoftIdentifier,
		const CHAR * szSoftVer,
		const CHAR * szAdvertIdentifier
		)
	{
		memset(this->szPlayerIdentifier, 0, sizeof(this->szPlayerIdentifier));
		memset(this->szSoftIdentifier, 0, sizeof(this->szSoftIdentifier));
		memset(this->szSoftVer, 0, sizeof(this->szSoftVer));
		memset(this->szAdvertIdentifier, 0, sizeof(this->szAdvertIdentifier));
        LimitLengthStrcpy(this->szPlayerIdentifier, szPlayerIdentifier, MAX_PLAYER_IDENTIFIER_LENGTH - 1);
		LimitLengthStrcpy(this->szSoftIdentifier, szSoftIdentifier, MAX_SOFT_IDENTIFIER_LENGTH - 1);
		LimitLengthStrcpy(this->szSoftVer, szSoftVer, MAX_SOFT_VER_LENGTH - 1);
		LimitLengthStrcpy(this->szAdvertIdentifier, szAdvertIdentifier, MAX_ADVERT_IDENTIFIER_LENGTH - 1);
		PacketHeader::serialize(REQ_PLAYER_UNINST_INFO, (USHORT)sizeof(ReqPlayerUninstInfo));
	}
};

struct SinglePlayerInfo
{
	// 在线日期
	UINT uOnlineDate;
	// 打字总数
	UINT uTypeWrite;
	//
	void serialize
		(
		UINT uOnlineDate,
		UINT uTypeWrite
		)
	{
		this->uOnlineDate = uOnlineDate;
		this->uTypeWrite = uTypeWrite;
	}
};
// 请求发送玩家在线信息
struct ReqPlayerOnlineInfo : public PacketHeader
{
	// 在线日期
	UINT uCount;
	// 玩家标示符
	CHAR szPlayerIdentifier[MAX_PLAYER_IDENTIFIER_LENGTH];
	// 软件标示符
	CHAR szSoftIdentifier[MAX_SOFT_IDENTIFIER_LENGTH];
	// 软件版本
	CHAR szSoftVer[MAX_SOFT_VER_LENGTH];
	// 推广商标示符
	CHAR szAdvertIdentifier[MAX_ADVERT_IDENTIFIER_LENGTH];
	//
	void serialize
		(
		UINT uCount,
		const CHAR * szPlayerIdentifier,
		const CHAR * szSoftIdentifier,
		const CHAR * szSoftVer,
		const CHAR * szAdvertIdentifier
		)
	{
		this->uCount = uCount;
		strcpy(this->szPlayerIdentifier, szPlayerIdentifier);
		strcpy(this->szSoftIdentifier, szSoftIdentifier);
		strcpy(this->szSoftVer, szSoftVer);
		strcpy(this->szAdvertIdentifier, szAdvertIdentifier);
		PacketHeader::serialize(REQ_PLAYER_ONLINE_INFO, (USHORT)(sizeof(ReqPlayerOnlineInfo) + uCount * sizeof(SinglePlayerInfo)));
	}
	//
	inline SinglePlayerInfo & operator[](UINT uIndex)
	{
		return ((SinglePlayerInfo*)((char*)this + sizeof(ReqPlayerOnlineInfo)))[uIndex];
	}
};

// 请求发送玩家升级信息
struct ReqPlayerUpgradeInfo : public PacketHeader
{
	// 玩家标示符
	CHAR szPlayerIdentifier[MAX_PLAYER_IDENTIFIER_LENGTH];
	// 软件标示符
	CHAR szSoftIdentifier[MAX_SOFT_IDENTIFIER_LENGTH];
	// 旧的软件版本
	CHAR szOldSoftVer[MAX_SOFT_VER_LENGTH];
	// 新的软件版本
	CHAR szNewSoftVer[MAX_SOFT_VER_LENGTH];
	// 推广商标示符
	CHAR szAdvertIdentifier[MAX_ADVERT_IDENTIFIER_LENGTH];
	//
	void serialize
		(
		const CHAR * szPlayerIdentifier,
		const CHAR * szSoftIdentifier,
		const CHAR * szOldSoftVer,
		const CHAR * szNewSoftVer,
		const CHAR * szAdvertIdentifier
		)
	{
		strcpy(this->szPlayerIdentifier, szPlayerIdentifier);
		strcpy(this->szSoftIdentifier, szSoftIdentifier);
		strcpy(this->szOldSoftVer, szOldSoftVer);
		strcpy(this->szNewSoftVer, szNewSoftVer);
		strcpy(this->szAdvertIdentifier, szAdvertIdentifier);
		PacketHeader::serialize(REQ_PLAYER_UPGRADE_INFO, (USHORT)sizeof(ReqPlayerUpgradeInfo));
	}
};


struct StringValueLength
{
	// 字符串长度
	INT nValueLength;
};


// 请求其他软件安装信息
struct ReqOtherSoftInstallInfo : public PacketHeader
{
	// 进程个数
	INT nProgressNum;
	// 玩家标示符
	CHAR szPlayerIdentifier[MAX_PLAYER_IDENTIFIER_LENGTH];
	//
	void serialize
		(
		INT nProgressNum,
		const CHAR * szPlayerIdentifier
		)
	{
		this->nProgressNum = nProgressNum;
		strcpy(this->szPlayerIdentifier, szPlayerIdentifier);
		PacketHeader::serialize(REQ_OTHER_SOFT_INSTALL_INFO, (USHORT)sizeof(ReqOtherSoftInstallInfo));
	}
	// 设置字符串的长度
	VOID SetValueLength(INT nValueLength)
	{
		StringValueLength *pStringValueLength = (StringValueLength*)((char*)this + uPacketLen);
		pStringValueLength->nValueLength = nValueLength;
		uPacketLen += sizeof(nValueLength);
	}
	// 获取字符串的长度
	INT GetValueLength(INT nPostion)
	{
		StringValueLength *pStringValueLength = (StringValueLength*)((char*)this + (sizeof(ReqOtherSoftInstallInfo) + nPostion));
		return pStringValueLength->nValueLength;
	}
	// 设置字符串信息
	void SetValue(const CHAR *lpszValue)
	{
		INT nTextLen = (INT)strlen(lpszValue);
		//
		this->SetValueLength(nTextLen);
		//
		CHAR *szValue = ((char*)this + uPacketLen);
		strcpy(szValue, lpszValue);
		uPacketLen += (nTextLen + 1);
	}
	// 获取字符串信息
	const CHAR* GetValue(INT nValueLength)
	{
		CHAR *lpszValue = ((char*)this + sizeof(ReqOtherSoftInstallInfo) + nValueLength);
		return lpszValue;
	}
};


// 请求其他软件在线信息
struct ReqOtherSoftOnlineInfo : public PacketHeader
{
	// 在线日期
	INT nOnlineDate;
	// 进程个数
	INT nProgressNum;
	// 玩家标示符
	CHAR szPlayerIdentifier[MAX_PLAYER_IDENTIFIER_LENGTH];
	//
	void serialize
		(
		INT nOnlineDate,
		INT nProgressNum,
		const CHAR * szPlayerIdentifier
		)
	{
		this->nOnlineDate = nOnlineDate;
		this->nProgressNum = nProgressNum;
		strcpy(this->szPlayerIdentifier, szPlayerIdentifier);
		PacketHeader::serialize(REQ_OTHER_SOFT_ONLINE_INFO, (USHORT)sizeof(ReqOtherSoftOnlineInfo));
	}
	// 设置字符串的长度
	VOID SetValueLength(INT nValueLength)
	{
		StringValueLength *pStringValueLength = (StringValueLength*)((char*)this + uPacketLen);
		pStringValueLength->nValueLength = nValueLength;
		uPacketLen += sizeof(nValueLength);
	}
	// 获取字符串的长度
	INT GetValueLength(INT nPostion)
	{
		StringValueLength *pStringValueLength = (StringValueLength*)((char*)this + (sizeof(ReqOtherSoftOnlineInfo) + nPostion));
		return pStringValueLength->nValueLength;
	}
	// 设置字符串信息
	void SetValue(const CHAR *lpszValue)
	{
		INT nTextLen = (INT)strlen(lpszValue);
		//
		this->SetValueLength(nTextLen);
		//
		CHAR *szValue = ((char*)this + uPacketLen);
		strcpy(szValue, lpszValue);
		uPacketLen += (nTextLen + 1);
	}
	// 获取字符串信息
	const CHAR* GetValue(INT nValueLength)
	{
		CHAR *lpszValue = ((char*)this + sizeof(ReqOtherSoftOnlineInfo) + nValueLength);
		return lpszValue;
	}
};

// 请求访问迷你广告信息
struct ReqPlayerBrowseMiNiInfo : public PacketHeader
{
	// 迷你网页ID
	INT nMiNiWebID;
	// 迷你分类ID
	INT nMiNiClassID;
	//
	void serialize
		(
		INT nMiNiWebID
		, INT nMiNiClassID
		)
	{
		this->nMiNiWebID = nMiNiWebID;
		this->nMiNiClassID = nMiNiClassID;
		PacketHeader::serialize(REQ_PLAYER_BROWSE_MINI_INFO, (USHORT)sizeof(ReqPlayerBrowseMiNiInfo));
	}
};

#pragma pack(pop)			//取消字节对齐

#endif	// __SERVER_PACKET_H__

