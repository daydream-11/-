#include "StdAfx.h"
#include "MemoryFile.h"
#include "stdarg.h"

CMemoryFile::CMemoryFile(void)
{
	// 申请临时内存空间
	m_pMemoryBuffer = NULL;
	// 当前指向的内存空间
	m_pCurrentAppointBuffer = NULL;
	// 申请临时内存空间大小
	m_nMemoryBufferSize = 0;
	// 当前指向的内存位置
	m_nCurrentAppointPosition = 0;
	// 最大使用的内存位置
	m_nMaxUseMemoryPosition = 0;
}

CMemoryFile::~CMemoryFile(void)
{
	SAFE_DELETE_ARRAY(m_pMemoryBuffer);
}


// 初始化
VOID CMemoryFile::Init(INT nMemoryBufferSize)
{
	m_nMemoryBufferSize = nMemoryBufferSize;
	if (m_pMemoryBuffer != NULL)
	{
		delete[] m_pMemoryBuffer;
		m_pMemoryBuffer = NULL;
	}
	m_pMemoryBuffer = new BYTE[m_nMemoryBufferSize];
	memset(m_pMemoryBuffer, 0, m_nMemoryBufferSize);
	m_pCurrentAppointBuffer = m_pMemoryBuffer;
	m_nCurrentAppointPosition = 0;
	m_nMaxUseMemoryPosition = 0;
}


// 重置
VOID CMemoryFile::Reset()
{
	memset(m_pMemoryBuffer, 0, m_nMemoryBufferSize);
	m_pCurrentAppointBuffer = m_pMemoryBuffer;
	m_nCurrentAppointPosition = 0;
	m_nMaxUseMemoryPosition = 0;
}

// 写入内存
VOID CMemoryFile::WriteFile(VOID *lpWriteBuffer, INT nWriteBufferSize)
{
	INT nSurplusBufferSize = m_nMemoryBufferSize - m_nCurrentAppointPosition;
	if (nSurplusBufferSize < nWriteBufferSize)
	{
		INT nTempMemoryBufferSize = m_nMemoryBufferSize;
		BYTE *pTempMemoryBuffer = new BYTE[nTempMemoryBufferSize * 2];
		memset(pTempMemoryBuffer, 0, nTempMemoryBufferSize * 2);
		memcpy(pTempMemoryBuffer, m_pMemoryBuffer, m_nMemoryBufferSize);
		//
		SAFE_DELETE_ARRAY(m_pMemoryBuffer);
		//
		m_pMemoryBuffer = pTempMemoryBuffer;
		m_nMemoryBufferSize = nTempMemoryBufferSize * 2;
		//
		m_pCurrentAppointBuffer = m_pMemoryBuffer + m_nCurrentAppointPosition;
	}
	memcpy(m_pCurrentAppointBuffer, lpWriteBuffer, nWriteBufferSize);
	m_pCurrentAppointBuffer += nWriteBufferSize;
	m_nCurrentAppointPosition += nWriteBufferSize;
	if (m_nCurrentAppointPosition > m_nMaxUseMemoryPosition)
	{
		m_nMaxUseMemoryPosition = m_nCurrentAppointPosition;
	}
}


// 指向内存位置
VOID CMemoryFile::SetFilePointer(INT nMemoryPointer)
{
	m_pCurrentAppointBuffer = m_pMemoryBuffer + nMemoryPointer;
	m_nCurrentAppointPosition = nMemoryPointer;
}


// 指向内存最后位置
VOID CMemoryFile::SetMemoryEndPosition()
{
	m_pCurrentAppointBuffer = m_pMemoryBuffer + m_nMaxUseMemoryPosition;
	m_nCurrentAppointPosition = m_nMaxUseMemoryPosition;
}



// 获取内存空间开始位置
BYTE* CMemoryFile::GetMemoryBufferBegin()
{
	return m_pMemoryBuffer;
}

// 获取内存空间结束位置
BYTE* CMemoryFile::GetMemoryBufferEnd()
{
	return m_pMemoryBuffer + m_nMaxUseMemoryPosition;
}

// 最大使用的内存位置
INT CMemoryFile::GetMaxUseMemoryPosition()
{
	return m_nMaxUseMemoryPosition;
}

// 获取当前指向的位置
INT CMemoryFile::GetCurrentAppointPosition()
{
	return m_nCurrentAppointPosition;
}

// 是否已经有日志写如内存
BOOL CMemoryFile::IsHaveWritedMemory()
{
	return m_nCurrentAppointPosition > 0;
}

// 保存数据
VOID CMemoryFile::Save(CHAR* filename)
{
	if ( this->IsHaveWritedMemory())
	{

		FILE* f = fopen( filename, "ab+" ) ;
		fwrite( m_pMemoryBuffer, 1, strlen((CHAR*)m_pMemoryBuffer), f ) ;
		fclose(f) ;
		this->Reset();
		return ;
	}
}