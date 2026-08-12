#ifndef __I_PLAYER_H__
#define __I_PLAYER_H__

class IPlayer
{
public:
	virtual ~IPlayer()
	{

	}
public:

	// 设置索引
	virtual VOID SetIndex(UINT uIndex) = 0;
	// 获取索引
	virtual UINT GetIndex() = 0;
	// 设置玩家ID
	virtual VOID SetPlayerID(UINT uPlayerID) = 0;
	// 获取玩家ID
	virtual UINT GetPlayerID() = 0;
	// 设置玩家索引
	virtual VOID SetPlayerIndex(UINT uPlayerIndex) = 0;
	// 获取玩家索引
	virtual UINT GetPlayerIndex() = 0;
};


#endif	// __I_PLAYER_H__