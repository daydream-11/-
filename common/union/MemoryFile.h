#pragma once

#include "SingletonTemplate.h"
#ifndef _MEMORYFILE_H_
#define _MEMORYFILE_H_

class CMemoryFile
{
private:
	// 申请临时内存空间
	BYTE *m_pMemoryBuffer;
	// 当前指向的内存空间
	BYTE *m_pCurrentAppointBuffer;
	// 申请临时内存空间大小
	INT m_nMemoryBufferSize;
	// 当前指向的内存位置
	INT m_nCurrentAppointPosition;
	// 最大使用的内存位置
	INT m_nMaxUseMemoryPosition;
public:
	CMemoryFile(void);
public:
	~CMemoryFile(void);
public:
	// 初始化
	VOID Init(INT nMemoryBufferSize);
	// 重置
	VOID Reset();
	// 写入内存
	VOID WriteFile(VOID *lpWriteBuffer, INT nWriteBufferSize);
	// 指向内存位置
	VOID SetFilePointer(INT nMemoryPointer);
	// 指向内存最后位置
	VOID SetMemoryEndPosition();
	// 获取内存空间开始位置
	BYTE* GetMemoryBufferBegin();
	// 获取内存空间结束位置
	BYTE* GetMemoryBufferEnd();
	// 最大使用的内存位置
	INT GetMaxUseMemoryPosition();
	// 获取当前指向的位置
	INT GetCurrentAppointPosition();
	// 是否已经有日志写如内存
	BOOL IsHaveWritedMemory();
	// 保存数据
	VOID Save(CHAR* filename);

};

typedef ChaSingleton<CMemoryFile> CMemoryFileInstance;
#endif //_MEMORYFILE_H_
