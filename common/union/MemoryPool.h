/**************************************************************
MemoryPool类
一个简单算法的内存池类
lizhi 2010-12-11

设计原理：
1：把内存分成64，128，256至到4096等七种不同大小的类型块
2：申请一个大的一块整块内存
3：把这个大块内存人为划分成七种不同类型大小的若干个内存块
4：每一个内存块都有一个NMemBlockPtr的结构来进行描述和管理，这个类有个指针指向了对应的内存区，但这个类本身并不包含内存段
5：调用者申请内存的时候，内存池根据其申请大小决定返回某种类型的内存块。如果调用者只申请32个字节内存，会返回一个64个字节的
内存块。（这会有内存浪费，但这种浪费是可以承受的）
6、内存池可在多线程中使用

调用说明：
1、此类设计最初目的是用于网络引擎IOCP。因为IOCP的IO线程内存分配有一定机率出错
2、复杂类对象不宜使用此内存池，如果类对象中本身在构造函数中会需要在堆中分配内存，那不能使用此内存池
***************************************************************/

#ifndef __MEMORY_POOL_H__
#define __MEMORY_POOL_H__

#include "BaseType.h"
#include "Ini.h"
#include "FileDefine.h"

struct MemoryBlockInfo
{
	// 分配内存块大小
	UINT uMemorySize;
	// 分配内存块数量
	UINT uBlockCount;
	//
	void* *m_pNoUseBlock;
	// 没有使用快的大小
	UINT m_uNoUseSize;
	MemoryBlockInfo()
	{
		uMemorySize = 0;
		uBlockCount = 0;
		m_uNoUseSize = 0;
		m_pNoUseBlock = NULL;
	}
	~MemoryBlockInfo()
	{
		SAFE_DELETE_ARRAY(m_pNoUseBlock);
	}
	void InitNoUseBlock()
	{
		m_pNoUseBlock = new void*[uBlockCount];
		m_uNoUseSize = uBlockCount;
	}
	void* GetNoUserBlock()
	{
		void* pMemoryBlock = NULL;
		if (m_uNoUseSize == 0)
		{
			return NULL;
		}
		pMemoryBlock = m_pNoUseBlock[m_uNoUseSize - 1];
		m_pNoUseBlock[m_uNoUseSize - 1] = NULL;
		m_uNoUseSize--;
		return pMemoryBlock;
	}
	void ClearAlreadyUserBlock(void *pAlreadyUserBlock)
	{
		m_pNoUseBlock[m_uNoUseSize] = pAlreadyUserBlock;
		m_uNoUseSize++;
	}
};

struct MemoryBlockConfig
{	
	// 内存块配置信息
	MemoryBlockInfo *m_pMemoryBlockArray;
	// 内存块配置数量
	UINT m_uBlockConfigCount;
	// 整个内存池的字节数
	UINT m_uTotalMemorySize;
	// 内存池的块数量
	UINT m_uTotalBlockCount;

	MemoryBlockConfig()
	{
		m_pMemoryBlockArray = NULL;
		m_uBlockConfigCount = 0;
		m_uTotalMemorySize = 0;
		m_uTotalBlockCount = 0;
	};
	~MemoryBlockConfig()
	{
		SAFE_DELETE_ARRAY(m_pMemoryBlockArray);
		m_uBlockConfigCount = 0;
		m_uTotalMemorySize = 0;
		m_uTotalBlockCount = 0;
	};
	void LoadMemoryBlockConfig(const CHAR * szIniFile)
	{
		Ini myIni(szIniFile) ;
		//
		m_uBlockConfigCount = myIni.ReadInt("MemoryConfig", "ConfigCount");
		//
		m_pMemoryBlockArray = new MemoryBlockInfo[m_uBlockConfigCount];
		memset(m_pMemoryBlockArray, 0, m_uBlockConfigCount * sizeof(MemoryBlockInfo));
		//

		CHAR szKey[50] = {'\0'};
		for (UINT i = 1; i <= m_uBlockConfigCount; i++)
		{
			MemoryBlockInfo *pMemoryBlockInfo = &m_pMemoryBlockArray[i - 1];
			//
			sprintf(szKey, "MemorySize%d", i);
			pMemoryBlockInfo->uMemorySize = (UINT)(myIni.ReadInt("MemoryConfig", szKey)) ;
			//
			sprintf(szKey, "BlockCount%d", i);
			pMemoryBlockInfo->uBlockCount = (UINT)myIni.ReadInt("MemoryConfig", szKey);
		}
	}
	void CalcBlockAndByteSize()
	{
		m_uTotalMemorySize = 0;
		m_uTotalBlockCount = 0;
		for (UINT i = 0; i < m_uBlockConfigCount; i++)
		{
			m_uTotalBlockCount += m_pMemoryBlockArray[i].uBlockCount;
			m_uTotalMemorySize += (m_pMemoryBlockArray[i].uBlockCount * m_pMemoryBlockArray[i].uMemorySize);
		}
	}
	MemoryBlockInfo* GetMemoryBlockInfo(UINT uSize)
	{
		for (UINT uIndex = 0; uIndex < m_uBlockConfigCount; uIndex++)
		{
			if (uSize <= m_pMemoryBlockArray[uIndex].uMemorySize)
			{
				return &m_pMemoryBlockArray[uIndex];
			}
		}
		return NULL;
	}
	MemoryBlockInfo* GetMemoryBlockInfoOfIndex(UINT uIndex)
	{
		return &m_pMemoryBlockArray[uIndex];
	}

};


// MemoryBlockPtr类，此类只是一个指针，并不有具体数据
class MemoryBlockPtr
{
public:
	// 指向本向所属的数据的内存
	char* m_pData;
	// 所属数据区的长度
	UINT m_uDataLen;
	// 指向保存的结构体
	void* m_pMemoryBlockInfo;
public:
	MemoryBlockPtr()
	{
		m_pData = NULL;
		m_uDataLen =0;
		m_pMemoryBlockInfo = NULL;
	};
	~MemoryBlockPtr()
	{
	};
public:
	char* GetMemory()
	{
		return m_pData;
	}
	void BackMemory()
	{
		memset(m_pData, 0, m_uDataLen);
	}
	void NewData()
	{
		m_pData = new char[m_uDataLen];
	}
	void DeleteData()
	{
		delete[] m_pData;
		m_pData = NULL;
	}
	void SetMemory(const char * pMemoryData, UINT uDataLen)
	{
		memcpy(m_pData, pMemoryData, uDataLen);
	}
};

class MemoryPool
{
private:
	
	/** @name 私有成员变量 *///////////////////////////////////////////////////
    /// @{
	
	// 预分配内存池的配置文件
	MemoryBlockConfig *m_pMemoryBlockConfig;
	// 内存池
	char * m_pMemoryPool;
	// 内存块指针池
	MemoryBlockPtr *m_pMemoryBlockPtr;
	// 分配内存池的互斥锁
	MyLock m_Lock;

	/// @}

public:
	MemoryPool();
	~MemoryPool();
public:

	/** @name 公共成员函数 *///////////////////////////////////////////////////
    /// @{
	
	/**********************************************************************
	* 函数名称： Init
	* 功能描述： 初始化内存池
	* 输入参数： 
	* <param name="szIniFile">内存池的配置文件</param>
	* 输出参数：
	* 返 回 值： 初始化内存池成功、返回TRUE，失败返回FALSE
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2011/09/09		V1.0	    huanggenping	创建版本
	***********************************************************************/
	BOOL Init(const CHAR * szIniFile);

	/**********************************************************************
	* 函数名称： GetMemory
	* 功能描述： 通过大小获取内存池数据
	* 输入参数： 
	* <param name="uSize">获取uSize大小的内存块</param>
	* 输出参数：
	* 返 回 值： 初始化内存池成功、返回TRUE，失败返回FALSE
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2011/09/09		V1.0	    huanggenping	创建版本
	***********************************************************************/
	MemoryBlockPtr* GetMemory(UINT uSize);
	
	/**********************************************************************
	* 函数名称： NewMemoryBlockPtr
	* 功能描述： 当内存池用完的情况，自己重新new一个空间出来
	* 输入参数： 
	* <param name="uSize">分配内存大小</param>
	* 输出参数：
	* 返 回 值： 返回重新new出来的指针
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2011/09/09		V1.0	    huanggenping	创建版本
	***********************************************************************/
	MemoryBlockPtr* NewMemoryBlockPtr(UINT uSize);
	
	/**********************************************************************
	* 函数名称： BackMemory
	* 功能描述： 收回内存，这里有可能是内存池中预分配的内存，也有可能是重新new出来的内存
	* 输入参数： 
	* <param name="pRemoveMemoryBlockPtr">需要收回内存的信息</param>
	* 输出参数：
	* 返 回 值： 
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2011/09/09		V1.0	    huanggenping	创建版本
	***********************************************************************/
	BOOL BackMemory(MemoryBlockPtr* pRemoveMemoryBlockPtr);

	/// @}

};

#endif // __MEMORY_POOL_H__