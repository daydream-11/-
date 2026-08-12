
#include "stdafx.h"
#include "GSWinMD5.h"

GSWinMD5::GSWinMD5()
: m_hDLL(NULL)
,m_pfnMD5Init(NULL)
,m_pfnMD5Update(NULL)
,m_pfnMD5Final(NULL)

{
    m_hDLL = ::LoadLibrary(TEXT("Cryptdll.dll")) ;
    if (m_hDLL != NULL)
    {
        m_pfnMD5Init    = (PFN_MD5Init)::GetProcAddress(m_hDLL, "MD5Init");  
        m_pfnMD5Update  = (PFN_MD5Update)::GetProcAddress(m_hDLL, "MD5Update");  
        m_pfnMD5Final   = (PFN_MD5Final)::GetProcAddress(m_hDLL, "MD5Final");
    }
}

GSWinMD5::~GSWinMD5()
{
    if (m_hDLL != NULL)
    {
        ::FreeLibrary(m_hDLL);
    }
}

void GSWinMD5::Init(void)
{
    if(m_pfnMD5Init)
    {
        m_pfnMD5Init(&m_md5Context) ;
    }
}


void GSWinMD5::Update(const BYTE* data, UINT32 size)
{
    if(m_pfnMD5Update)
    {
        m_pfnMD5Update(&m_md5Context, (unsigned char*)data, size) ;
    }
}

void GSWinMD5::Finish(BYTE digest[16])
{
    if(m_pfnMD5Final)
    {
        m_pfnMD5Final(&m_md5Context) ;
        for(size_t index = 0; index < 16; ++index)
        {
            digest[index] = m_md5Context.digest[index] ;
        }
    }
}

xstring GSWinMD5::GetMD5String(BYTE digest[16])
{
    const INT32 I_COUNT = 16;
    xstring::value_type output[I_COUNT*2 + 2] ;
    for (INT32 i = 0; i < I_COUNT; i++)
    {
        swprintf_s(output + i * 2, (I_COUNT - i + 1)*2, _T("%02X"), digest[i]);
    }
    return xstring(output) ;
}