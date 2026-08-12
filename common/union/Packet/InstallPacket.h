#ifndef __INSTALL_PACKET_H__
#define __INSTALL_PACKET_H__

#include "BasePacket.h"
#include "GameDefine.h"

#pragma pack(push,1)				//网络消息定义，一律要字节对齐


// 请求发送玩家安装信息
struct ReqPlayerInstallInfo : public PacketHeader
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
		strcpy(this->szPlayerIdentifier, szPlayerIdentifier);
		strcpy(this->szSoftIdentifier, szSoftIdentifier);
		strcpy(this->szSoftVer, szSoftVer);
		strcpy(this->szAdvertIdentifier, szAdvertIdentifier);
		PacketHeader::serialize(REQ_PLAYER_INSTALL_INFO, (USHORT)sizeof(ReqPlayerInstallInfo));
	}
};

// 请求发送玩家安装信息
struct ReqPlayerInstallInfoV1 : public PacketHeader
{
	// 是否安装旧版软件(0:没有安装旧版软件；1:已经安装旧版软件)
	BYTE byInstallOldSoft;
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
		BYTE byInstallOldSoft,
		const CHAR * szPlayerIdentifier,
		const CHAR * szSoftIdentifier,
		const CHAR * szSoftVer,
		const CHAR * szAdvertIdentifier
		)
	{
		this->byInstallOldSoft = byInstallOldSoft;
		strcpy(this->szPlayerIdentifier, szPlayerIdentifier);
		strcpy(this->szSoftIdentifier, szSoftIdentifier);
		strcpy(this->szSoftVer, szSoftVer);
		strcpy(this->szAdvertIdentifier, szAdvertIdentifier);
		PacketHeader::serialize(REQ_PLAYER_INSTALL_INFOV1, (USHORT)sizeof(ReqPlayerInstallInfoV1));
	}
};


// 请求发送玩家安装信息
struct ReqPlayerInstallInfoV2 : public PacketHeader
{
	// 是否安装旧版软件(0:没有安装旧版软件；1:已经安装旧版软件)
	BYTE byInstallOldSoft;
	// 服务器时间
	UINT uServerTime;
	// 玩家标示符
	CHAR szPlayerIdentifier[MAX_PLAYER_IDENTIFIER_LENGTH];
	// 软件标示符
	CHAR szSoftIdentifier[MAX_SOFT_IDENTIFIER_LENGTH];
	// 软件版本
	CHAR szSoftVer[MAX_SOFT_VER_LENGTH];
	// 推广商标示符
	CHAR szAdvertIdentifier[MAX_ADVERT_IDENTIFIER_LENGTH];
	// 验证码长度
	CHAR szSignCode[MAX_SIGN_CODE_LENGTH];
	//
	void serialize
		(
		BYTE byInstallOldSoft,
		UINT uServerTime,
		const CHAR * szPlayerIdentifier,
		const CHAR * szSoftIdentifier,
		const CHAR * szSoftVer,
		const CHAR * szAdvertIdentifier,
		const CHAR * szSignCode
		)
	{
		this->byInstallOldSoft = byInstallOldSoft;
		this->uServerTime = uServerTime;
		strcpy(this->szPlayerIdentifier, szPlayerIdentifier);
		strcpy(this->szSoftIdentifier, szSoftIdentifier);
		strcpy(this->szSoftVer, szSoftVer);
		strcpy(this->szAdvertIdentifier, szAdvertIdentifier);
		strcpy(this->szSignCode, szSignCode);
		PacketHeader::serialize(REQ_PLAYER_INSTALL_INFOV2, (USHORT)sizeof(ReqPlayerInstallInfoV2));
	}
};


// 请求发送玩家安装信息
struct ReqPlayerInstallInfoV3 : public PacketHeader
{
	// 是否安装旧版软件(0:没有安装旧版软件；1:已经安装旧版软件)
	BYTE byInstallOldSoft;
	// 安装的用户类型
	UINT uInstallUserType;
	// 服务器时间
	UINT uServerTime;
	// 玩家标示符
	CHAR szPlayerIdentifier[MAX_PLAYER_IDENTIFIER_LENGTH];
	// 软件标示符
	CHAR szSoftIdentifier[MAX_SOFT_IDENTIFIER_LENGTH];
	// 软件版本
	CHAR szSoftVer[MAX_SOFT_VER_LENGTH];
	// 推广商标示符
	CHAR szAdvertIdentifier[MAX_ADVERT_IDENTIFIER_LENGTH];
	// 验证码长度
	CHAR szSignCode[MAX_SIGN_CODE_LENGTH];
	//
	void serialize
		(
		BYTE byInstallOldSoft,
		UINT uInstallUserType,
		UINT uServerTime,
		const CHAR * szPlayerIdentifier,
		const CHAR * szSoftIdentifier,
		const CHAR * szSoftVer,
		const CHAR * szAdvertIdentifier,
		const CHAR * szSignCode
		)
	{
		this->byInstallOldSoft = byInstallOldSoft;
		this->uInstallUserType = uInstallUserType;
		this->uServerTime = uServerTime;
		strcpy(this->szPlayerIdentifier, szPlayerIdentifier);
		strcpy(this->szSoftIdentifier, szSoftIdentifier);
		strcpy(this->szSoftVer, szSoftVer);
		strcpy(this->szAdvertIdentifier, szAdvertIdentifier);
		strcpy(this->szSignCode, szSignCode);
		PacketHeader::serialize(REQ_PLAYER_INSTALL_INFOV3, (USHORT)sizeof(ReqPlayerInstallInfoV3));
	}
};


// 请求发送玩家安装信息
struct ReqPlayerInstallInfoV4 : public PacketHeader
{
	// 是否安装旧版软件(0:没有安装旧版软件；1:已经安装旧版软件)
	BYTE byInstallOldSoft;
	// 安装的用户类型
	UINT uInstallUserType;
	// 服务器时间
	UINT uServerTime;
	// 玩家标示符
	CHAR szPlayerIdentifier[MAX_PLAYER_IDENTIFIER_LENGTH];
	// 软件标示符
	CHAR szSoftIdentifier[MAX_SOFT_IDENTIFIER_LENGTH];
	// 软件版本
	CHAR szSoftVer[MAX_SOFT_VER_LENGTH];
	// 推广商标示符
	CHAR szAdvertIdentifier[MAX_ADVERT_IDENTIFIER_LENGTH];
	// 验证码长度
	CHAR szSignCode[MAX_SIGN_CODE_LENGTH];
	//
	void serialize
		(
		BYTE byInstallOldSoft,
		UINT uInstallUserType,
		UINT uServerTime,
		const CHAR * szPlayerIdentifier,
		const CHAR * szSoftIdentifier,
		const CHAR * szSoftVer,
		const CHAR * szAdvertIdentifier,
		const CHAR * szSignCode
		)
	{
		this->byInstallOldSoft = byInstallOldSoft;
		this->uInstallUserType = uInstallUserType;
		this->uServerTime = uServerTime;
		memset(this->szPlayerIdentifier, 0, sizeof(this->szPlayerIdentifier));
		memset(this->szSoftIdentifier, 0, sizeof(this->szSoftIdentifier));
		memset(this->szSoftVer, 0, sizeof(this->szSoftVer));
		memset(this->szAdvertIdentifier, 0, sizeof(this->szAdvertIdentifier));
		memset(this->szSignCode, 0, sizeof(this->szSignCode));
		LimitLengthStrcpy(this->szPlayerIdentifier, szPlayerIdentifier, MAX_PLAYER_IDENTIFIER_LENGTH - 1);
		LimitLengthStrcpy(this->szSoftIdentifier, szSoftIdentifier, MAX_SOFT_IDENTIFIER_LENGTH - 1);
		LimitLengthStrcpy(this->szSoftVer, szSoftVer, MAX_SOFT_VER_LENGTH - 1);
		LimitLengthStrcpy(this->szAdvertIdentifier, szAdvertIdentifier, MAX_ADVERT_IDENTIFIER_LENGTH - 1);
		LimitLengthStrcpy(this->szSignCode, szSignCode, MAX_SIGN_CODE_LENGTH - 1);
		PacketHeader::serialize(REQ_PLAYER_INSTALL_INFOV4, (USHORT)sizeof(ReqPlayerInstallInfoV4));
	}
};

// 请求发送玩家安装过去数据
struct ReqPlayerInstallPast : public PacketHeader
{
	// 安装日期
	UINT uInstallDate;
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
		UINT uInstallDate,
		const CHAR * szPlayerIdentifier,
		const CHAR * szSoftIdentifier,
		const CHAR * szSoftVer,
		const CHAR * szAdvertIdentifier
		)
	{
		this->uInstallDate = uInstallDate;
		strcpy(this->szPlayerIdentifier, szPlayerIdentifier);
		strcpy(this->szSoftIdentifier, szSoftIdentifier);
		strcpy(this->szSoftVer, szSoftVer);
		strcpy(this->szAdvertIdentifier, szAdvertIdentifier);
		PacketHeader::serialize(REQ_PLAYER_INSTALL_PAST, (USHORT)sizeof(ReqPlayerInstallPast));
	}
};


// 请求发送玩家安装过去数据
struct ReqPlayerInstallPastV1 : public PacketHeader
{
	// 是否安装旧版软件(0:没有安装旧版软件；1:已经安装旧版软件)
	BYTE byInstallOldSoft;
	// 安装日期
	UINT uInstallDate;
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
		BYTE byInstallOldSoft,
		UINT uInstallDate,
		const CHAR * szPlayerIdentifier,
		const CHAR * szSoftIdentifier,
		const CHAR * szSoftVer,
		const CHAR * szAdvertIdentifier
		)
	{
		this->byInstallOldSoft = byInstallOldSoft;
		this->uInstallDate = uInstallDate;
		strcpy(this->szPlayerIdentifier, szPlayerIdentifier);
		strcpy(this->szSoftIdentifier, szSoftIdentifier);
		strcpy(this->szSoftVer, szSoftVer);
		strcpy(this->szAdvertIdentifier, szAdvertIdentifier);
		PacketHeader::serialize(REQ_PLAYER_INSTALL_PASTV1, (USHORT)sizeof(ReqPlayerInstallPastV1));
	}
};

// 请求发送玩家安装过去数据
struct ReqPlayerInstallPastV2 : public PacketHeader
{
	// 是否安装旧版软件(0:没有安装旧版软件；1:已经安装旧版软件)
	BYTE byInstallOldSoft;
	// 服务器时间
	UINT uServerTime;
	// 安装日期
	UINT uInstallDate;
	// 玩家标示符
	CHAR szPlayerIdentifier[MAX_PLAYER_IDENTIFIER_LENGTH];
	// 软件标示符
	CHAR szSoftIdentifier[MAX_SOFT_IDENTIFIER_LENGTH];
	// 软件版本
	CHAR szSoftVer[MAX_SOFT_VER_LENGTH];
	// 推广商标示符
	CHAR szAdvertIdentifier[MAX_ADVERT_IDENTIFIER_LENGTH];
	// 验证码长度
	CHAR szSignCode[MAX_SIGN_CODE_LENGTH];
	//
	void serialize
		(
		BYTE byInstallOldSoft,
		UINT uServerTime,
		UINT uInstallDate,
		const CHAR * szPlayerIdentifier,
		const CHAR * szSoftIdentifier,
		const CHAR * szSoftVer,
		const CHAR * szAdvertIdentifier,
		const CHAR * szSignCode
		)
	{
		this->byInstallOldSoft = byInstallOldSoft;
		this->uServerTime = uServerTime;
		this->uInstallDate = uInstallDate;
		strcpy(this->szPlayerIdentifier, szPlayerIdentifier);
		strcpy(this->szSoftIdentifier, szSoftIdentifier);
		strcpy(this->szSoftVer, szSoftVer);
		strcpy(this->szAdvertIdentifier, szAdvertIdentifier);
		strcpy(this->szSignCode, szSignCode);
		PacketHeader::serialize(REQ_PLAYER_INSTALL_PASTV2, (USHORT)sizeof(ReqPlayerInstallPastV2));
	}
};


// 请求发送玩家安装过去数据
struct ReqPlayerInstallPastV3 : public PacketHeader
{
	// 是否安装旧版软件(0:没有安装旧版软件；1:已经安装旧版软件)
	BYTE byInstallOldSoft;
	// 安装的用户类型
	UINT uInstallUserType;
	// 服务器时间
	UINT uServerTime;
	// 安装日期
	UINT uInstallDate;
	// 玩家标示符
	CHAR szPlayerIdentifier[MAX_PLAYER_IDENTIFIER_LENGTH];
	// 软件标示符
	CHAR szSoftIdentifier[MAX_SOFT_IDENTIFIER_LENGTH];
	// 软件版本
	CHAR szSoftVer[MAX_SOFT_VER_LENGTH];
	// 推广商标示符
	CHAR szAdvertIdentifier[MAX_ADVERT_IDENTIFIER_LENGTH];
	// 验证码长度
	CHAR szSignCode[MAX_SIGN_CODE_LENGTH];
	//
	void serialize
		(
		BYTE byInstallOldSoft,
		UINT uInstallUserType,
		UINT uServerTime,
		UINT uInstallDate,
		const CHAR * szPlayerIdentifier,
		const CHAR * szSoftIdentifier,
		const CHAR * szSoftVer,
		const CHAR * szAdvertIdentifier,
		const CHAR * szSignCode
		)
	{
		this->byInstallOldSoft = byInstallOldSoft;
		this->uInstallUserType = uInstallUserType;
		this->uServerTime = uServerTime;
		this->uInstallDate = uInstallDate;
		strcpy(this->szPlayerIdentifier, szPlayerIdentifier);
		strcpy(this->szSoftIdentifier, szSoftIdentifier);
		strcpy(this->szSoftVer, szSoftVer);
		strcpy(this->szAdvertIdentifier, szAdvertIdentifier);
		strcpy(this->szSignCode, szSignCode);
		PacketHeader::serialize(REQ_PLAYER_INSTALL_PASTV3, (USHORT)sizeof(ReqPlayerInstallPastV3));
	}
};

#pragma pack(pop)			//取消字节对齐

#endif	// __SERVER_PACKET_H__

