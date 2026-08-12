#include "stdafx.h"
#include "MemoryPoolManager.h"
#ifdef LOAD_AGENT_SERVER_CONFIG
#include "IPlayerConnect.h"
#endif

MemoryPoolManager* g_pMemoryPoolManager = NULL ;

MemoryPoolManager::MemoryPoolManager( )
{
	__ENTER_FUNCTION
	
	m_pMemoryPool = NULL;

	__LEAVE_FUNCTION
}

MemoryPoolManager::~MemoryPoolManager()
{
	__ENTER_FUNCTION
	
	SAFE_DELETE(m_pMemoryPool);

	__LEAVE_FUNCTION
}

BOOL MemoryPoolManager::Init(const CHAR * szMemoryPoolFile)
{
	__ENTER_FUNCTION

	m_pMemoryPool = new MemoryPool();
	if (m_pMemoryPool == NULL)
	{
		return FALSE;
	}
	
	BOOL bReturn = m_pMemoryPool->Init(szMemoryPoolFile);
	if (!bReturn)
	{
		return FALSE;
	}

	return TRUE;
	
	__LEAVE_FUNCTION

	return FALSE;
}

// 获取内存池
MemoryPool* MemoryPoolManager::GetMemoryPool()
{
	return m_pMemoryPool;
}

MemoryBlockPtr* MemoryPoolManager::GetPacketMemoryBlockPtr(PacketHeader *pPacketHeader, void* pPlayerConnect,int nNetMsgLen)
{
	// 首先分配保存消息快内存
	MemoryBlockPtr* pNetworkMemoryBlockPtr = m_pMemoryPool->GetMemory(nNetMsgLen);
	if (pNetworkMemoryBlockPtr == NULL)
	{
		return NULL;
	}
	pNetworkMemoryBlockPtr->SetMemory((const char*)pPacketHeader, nNetMsgLen);
	// 然后分配PacketMemoryBlock（保存消息快和连接内存）
	MemoryBlockPtr *pPacketMemoryBlockPtr = m_pMemoryPool->GetMemory(sizeof(PacketMemoryBlock));
	if (pPacketMemoryBlockPtr == NULL)
	{
		return NULL;
	}
	PacketMemoryBlock* pPacketMemoryBlock = (PacketMemoryBlock*)pPacketMemoryBlockPtr->GetMemory();
	if (pPacketMemoryBlock == NULL)
	{
		return NULL;
	}
	//
	pPacketMemoryBlock->pPlayerConnect = pPlayerConnect;
	pPacketMemoryBlock->pPacketHeader = pNetworkMemoryBlockPtr->GetMemory();
	pPacketMemoryBlock->pPacketBlock = pNetworkMemoryBlockPtr;
	return pPacketMemoryBlockPtr;
}

MemoryBlockPtr* MemoryPoolManager::GetAgentMemoryBlockPtr(PacketHeader *pPacketHeader, VOID* pPlayerConnect,int nNetMsgLen)
{
#ifdef LOAD_AGENT_SERVER_CONFIG
	INT nMallocLen = nNetMsgLen;
	BOOL bClientToAgent = FALSE;
	if (pPacketHeader->packetID < 0x5000)
	{
		if (pPlayerConnect != NULL)
		{
			IPlayerConnect *pTempPlayerConnect = (IPlayerConnect*)pPlayerConnect;
			UINT uServerIdentifierID = pTempPlayerConnect->GetPlayer()->GetPlayerID();
			if (uServerIdentifierID == 0)
			{
				bClientToAgent = TRUE;
				// 客户端发送给代理服务器，需要在包装消息增加4个字节，在完整消息结尾放入4个字节的跟客户端连接对象(IPlayerConnect)
				// 方便消息传递给其他服务器，在转发到代理服务器
				nMallocLen += 4;
			}
			else if (uServerIdentifierID > 10000)
			{
				UINT uPlayerIndex = pTempPlayerConnect->GetPlayer()->GetPlayerIndex();
				ServerPacketHeader *pServerPacketHeader = (ServerPacketHeader*)pPacketHeader;
				UINT uSendPlayerIndex = pServerPacketHeader->uPlayerID;
				if (uSendPlayerIndex != 0)
				{
					if (uSendPlayerIndex != uPlayerIndex)
					{
						return NULL;
					}
				}
				bClientToAgent = TRUE;
				// 客户端发送给代理服务器，需要在包装消息增加4个字节，在完整消息结尾放入4个字节的跟客户端连接对象(IPlayerConnect)
				// 方便消息传递给其他服务器，在转发到代理服务器
				nMallocLen += 4;
			}
		}
	}
	// 首先分配保存消息快内存
	MemoryBlockPtr* pNetworkMemoryBlockPtr = m_pMemoryPool->GetMemory(nMallocLen);
	if (pNetworkMemoryBlockPtr == NULL)
	{
		return NULL;
	}
	char *pszMemory = pNetworkMemoryBlockPtr->GetMemory();
	// 拷贝完整消息到预分配内存中
	memcpy(pszMemory, (const char*)pPacketHeader, nNetMsgLen);
	if (bClientToAgent)
	{
		PacketHeader *pTempPacketHeader = (PacketHeader*)pszMemory;
		// 把跟客户端连接的对象拷贝到预分配内存中
		if (pPlayerConnect != NULL)
		{
			pTempPacketHeader->SetExtraData(pPlayerConnect);
		}
	}
	// 然后分配PacketMemoryBlock（保存消息快和连接内存）
	MemoryBlockPtr *pPacketMemoryBlockPtr = m_pMemoryPool->GetMemory(sizeof(PacketMemoryBlock));
	if (pPacketMemoryBlockPtr == NULL)
	{
		return NULL;
	}
	PacketMemoryBlock* pPacketMemoryBlock = (PacketMemoryBlock*)pPacketMemoryBlockPtr->GetMemory();
	if (pPacketMemoryBlock == NULL)
	{
		return NULL;
	}
	//
	pPacketMemoryBlock->pPlayerConnect = pPlayerConnect;
	pPacketMemoryBlock->pPacketHeader = pNetworkMemoryBlockPtr->GetMemory();
	pPacketMemoryBlock->pPacketBlock = pNetworkMemoryBlockPtr;
	return pPacketMemoryBlockPtr;
#endif
	
	return NULL;

}

//
VOID MemoryPoolManager::ClearPacketMemoryBlockPtr(MemoryBlockPtr *pPacketMemoryBlockPtr)
{
	PacketMemoryBlock *pPacketMemoryBlock = (PacketMemoryBlock*)pPacketMemoryBlockPtr->GetMemory();
	//
	MemoryBlockPtr *pNetworkMemoryBlockPtr = (MemoryBlockPtr*)pPacketMemoryBlock->pPacketBlock;
	// 释放生成组装消息分配内存
	m_pMemoryPool->BackMemory(pPacketMemoryBlockPtr);
	// 释放网络消息包释放的内存
	m_pMemoryPool->BackMemory(pNetworkMemoryBlockPtr);
}