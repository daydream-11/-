

#ifndef __MEMORY_POOL_MANAGER_H__
#define __MEMORY_POOL_MANAGER_H__

#include "GameType.h"
#include "MemoryPool.h"

class MemoryPoolManager
{
private:
	MemoryPool *m_pMemoryPool;
public :
	MemoryPoolManager();
	~MemoryPoolManager();
public:
	//初始化模块
	BOOL Init(const CHAR * szMemoryPoolFile) ;
	// 获取内存池
	MemoryPool* GetMemoryPool();
	// 预分配给服务器消息内存
	MemoryBlockPtr* GetPacketMemoryBlockPtr(PacketHeader *pPacketHeader, void* pPlayerConnect,int nNetMsgLen);
	// 预分配给代理服务器消息内存
	MemoryBlockPtr* GetAgentMemoryBlockPtr(PacketHeader *pPacketHeader, void* pPlayerConnect,int nNetMsgLen);
	//
	VOID ClearPacketMemoryBlockPtr(MemoryBlockPtr *pPacketMemoryBlockPtr);
};

extern MemoryPoolManager* g_pMemoryPoolManager;

#endif // __MEMORY_POOL_MANAGER_H__
