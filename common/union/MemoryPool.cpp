#include "stdafx.h"
#include "MemoryPool.h"

MemoryPool::MemoryPool()
{
	m_pMemoryPool = NULL;
	m_pMemoryBlockConfig = NULL;
	m_pMemoryBlockPtr = NULL;
}

MemoryPool::~MemoryPool()
{
	SAFE_DELETE(m_pMemoryBlockConfig);
	SAFE_DELETE_ARRAY(m_pMemoryPool);
	SAFE_DELETE_ARRAY(m_pMemoryBlockPtr);
}

BOOL MemoryPool::Init(const CHAR * szIniFile)
{
	m_pMemoryBlockConfig = new MemoryBlockConfig();
	if (m_pMemoryBlockConfig == NULL)
	{
		return FALSE;
	}
	m_pMemoryBlockConfig->LoadMemoryBlockConfig(szIniFile);
	// 计算出总内存池大小和内存块数量
	m_pMemoryBlockConfig->CalcBlockAndByteSize();
	
	// 向操作系统申请内存
	m_pMemoryPool = new CHAR[m_pMemoryBlockConfig->m_uTotalMemorySize];
	if (m_pMemoryPool == NULL)
	{
		return FALSE;
	}
	memset(m_pMemoryPool, 0, m_pMemoryBlockConfig->m_uTotalMemorySize);
	//
	m_pMemoryBlockPtr = new MemoryBlockPtr[m_pMemoryBlockConfig->m_uTotalBlockCount];
	if (m_pMemoryBlockPtr == NULL)
	{
		return FALSE;
	}
	//
	UINT uMemoryBlockPtrSize = sizeof(MemoryBlockPtr);
	UINT uZeroMemorySize = m_pMemoryBlockConfig->m_uTotalBlockCount * uMemoryBlockPtrSize;
	memset(m_pMemoryBlockPtr, 0, uZeroMemorySize);
	//
	// 设置MemoryBlockConfig配置中每块的起始位置
	UINT uMemoryPos = (UINT)(MemoryBlockPtr*)(&(m_pMemoryBlockPtr[0]));
	for (UINT i = 0; i < m_pMemoryBlockConfig->m_uBlockConfigCount; i++)
	{
		MemoryBlockInfo *pMemoryBlockInfo = m_pMemoryBlockConfig->GetMemoryBlockInfoOfIndex(i);
		pMemoryBlockInfo->InitNoUseBlock();
		//
		for (UINT j = 0; j < pMemoryBlockInfo->uBlockCount; j++)
		{
			pMemoryBlockInfo->m_pNoUseBlock[j] = (VOID*)uMemoryPos;
			uMemoryPos += uMemoryBlockPtrSize;
		}
	}
	// 设置每一块对象
	uMemoryPos = (UINT)(CHAR*)(&(m_pMemoryPool[0]));
	UINT uIndex = 0;
	for (UINT i = 0; i < m_pMemoryBlockConfig->m_uBlockConfigCount; i++)
	{
		MemoryBlockInfo *pMemoryBlockInfo = m_pMemoryBlockConfig->GetMemoryBlockInfoOfIndex(i);
		for(UINT j = 0; j < pMemoryBlockInfo->uBlockCount; j++)
		{
			m_pMemoryBlockPtr[uIndex].m_pData = (CHAR*)uMemoryPos;
			m_pMemoryBlockPtr[uIndex].m_uDataLen = pMemoryBlockInfo->uMemorySize;
			m_pMemoryBlockPtr[uIndex].m_pMemoryBlockInfo = pMemoryBlockInfo;
			uMemoryPos += pMemoryBlockInfo->uMemorySize;
			uIndex++;
		}
	}

	return TRUE;
}

MemoryBlockPtr* MemoryPool::GetMemory(UINT uSize)
{
	AutoLockT myAutoLockT(m_Lock);
	MemoryBlockPtr *pMemoryBlockPtr = NULL;
	//首先根据所要获取的内存大小，决定从那一种内存块中取得
	MemoryBlockInfo *pMemoryBlockInfo = m_pMemoryBlockConfig->GetMemoryBlockInfo(uSize);
	if (pMemoryBlockInfo != NULL)
	{
		pMemoryBlockPtr = (MemoryBlockPtr*)pMemoryBlockInfo->GetNoUserBlock();
		if (pMemoryBlockPtr != NULL)
		{
			return pMemoryBlockPtr;
		}
	}
	return NewMemoryBlockPtr(uSize);
}

MemoryBlockPtr* MemoryPool::NewMemoryBlockPtr(UINT uSize)
{
	MemoryBlockPtr *pMemoryBlockPtr = new MemoryBlockPtr();
	memset(pMemoryBlockPtr, 0, sizeof(pMemoryBlockPtr));
	//
	pMemoryBlockPtr->m_uDataLen = uSize;
	pMemoryBlockPtr->NewData();
	return pMemoryBlockPtr;
}

BOOL MemoryPool::BackMemory(MemoryBlockPtr* pRemoveMemoryBlockPtr)
{
	AutoLockT myAutoLockT(m_Lock);
	pRemoveMemoryBlockPtr->BackMemory();
	MemoryBlockInfo *pMemoryBlockInfo = (MemoryBlockInfo*)pRemoveMemoryBlockPtr->m_pMemoryBlockInfo;
	if (pMemoryBlockInfo == NULL)
	{
		pRemoveMemoryBlockPtr->DeleteData();
		delete pRemoveMemoryBlockPtr;
		pRemoveMemoryBlockPtr = NULL;
		return TRUE;
	}
	pMemoryBlockInfo->ClearAlreadyUserBlock(pRemoveMemoryBlockPtr);
	return TRUE;
}
