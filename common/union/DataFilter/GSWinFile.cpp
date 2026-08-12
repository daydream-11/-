#include "stdafx.h"
#include "GSWinFile.h"

#define CHUNK_SIZE_MAX (1024*64)

GSWinFile::GSWinFile():
    m_handle(INVALID_HANDLE_VALUE)    
{
}

GSWinFile::~GSWinFile()
{
    Close() ;
}

bool GSWinFile::Close()
{
    if (m_handle == INVALID_HANDLE_VALUE)
    {
        return true ;
    }
    if (!::CloseHandle(m_handle))
    {
        return false;
    }
    m_fileName.clear() ;
    m_handle = INVALID_HANDLE_VALUE;
    return true ;
}


bool GSWinFile::Create(const xstring& fileName,
                           DWORD desiredAccess,
                           DWORD shareMode, 
                           DWORD creationDisposition,  
                           DWORD flagsAndAttributes)
{
    if (!Close())
    {
        return false ;
    }
    m_handle = ::CreateFile( fileName.c_str(), 
                            desiredAccess, 
                            shareMode,
                            (LPSECURITY_ATTRIBUTES)NULL,
                            creationDisposition,
                            flagsAndAttributes | FILE_FLAG_SEQUENTIAL_SCAN, 
                            (HANDLE)NULL) ;  
    m_fileName = fileName ;
    return (m_handle != INVALID_HANDLE_VALUE) ;
}

bool GSWinFile::GetPosition(UINT64 &position) const
{
    return Seek(0, FILE_CURRENT, position) ;
}

bool GSWinFile::GetLength(UINT64 &length) const
{
    DWORD sizeHigh = 0 ;
    DWORD sizeLow = ::GetFileSize(m_handle, &sizeHigh) ;
    if (sizeLow == 0xFFFFFFFF)
    {
        if (::GetLastError() != NO_ERROR)
        {
            return false ;
        }
    }
    length = (((UINT64)sizeHigh) << 32) + sizeLow ;
    return true ;
}

bool GSWinFile::Seek(INT64 distanceToMove, DWORD moveMethod, UINT64 &newPosition) const
{
    LARGE_INTEGER value;
    value.QuadPart = distanceToMove;
    value.LowPart = ::SetFilePointer(m_handle, value.LowPart, &value.HighPart, moveMethod);
    if (value.LowPart == 0xFFFFFFFF)
    {
        if (::GetLastError() != NO_ERROR)
        {
            return false;
        }
    }
    newPosition = value.QuadPart ;
    return true ;
}

bool GSWinFile::Seek(UINT64 position, UINT64 &newPosition)
{
    return Seek(position, FILE_BEGIN, newPosition) ;
}

bool GSWinFile::SeekToBegin()
{
    UINT64 newPosition = 0 ;
    return Seek(0, newPosition) ;
}

bool GSWinFile::SeekToEnd(UINT64 &newPosition)
{
    return Seek(0, FILE_END, newPosition);
}

const xstring& GSWinFile::GetFileName() const
{
    return m_fileName ;
}

/** 一次读取过大时，性能较差,且可能出错，综合测试每次读取64KB时性能较佳
*/

bool GSWinFile::Read(void* data, UINT32 size, UINT32& processedSize)
{
    bool res = false;
    UINT32 nRemainSize = size;
    processedSize = 0;
    do
    {
        UINT32 nReadSize = 0;
        if (nRemainSize > CHUNK_SIZE_MAX)
        {
            nReadSize = CHUNK_SIZE_MAX ;
        }
        else
        {
            nReadSize = nRemainSize;
        }
        DWORD processedLoc = 0;
        res = (::ReadFile(m_handle, data, nReadSize, &processedLoc, NULL) != FALSE) ? true : false ;
        if (!res)
        {
            return false ;
        }
        processedSize += (UINT32)processedLoc;
        if (processedLoc == 0)
        {
            return true;
        }
        data = (void *)((BYTE *)data + processedLoc);
        nRemainSize -= processedLoc;
    } while (nRemainSize > 0);
    return true ;
}

bool GSWinFile::Write(const void *data, UINT32 size, UINT32& processedSize)
{
    bool res = false;
    UINT32 nRemainSize = size;
    processedSize = 0;
    do
    {
        UINT32 nWriteSize = 0;
        if (nRemainSize > CHUNK_SIZE_MAX)
        {
            nWriteSize = CHUNK_SIZE_MAX ;
        }
        else
        {
            nWriteSize = nRemainSize;
        }
        DWORD processedLoc = 0;
        res = (::WriteFile(m_handle, data, nWriteSize, &processedLoc, NULL) != FALSE ) ? true : false ;
        if (!res)
        {
            return false;
        }
        processedSize += (UINT32)processedLoc;

        if (processedLoc == 0)
        {
            return true;
        }
        data = (const void *)((const BYTE *)data + processedLoc);
        nRemainSize -= processedLoc;
    }
    while (nRemainSize > 0);
    return true;
}
