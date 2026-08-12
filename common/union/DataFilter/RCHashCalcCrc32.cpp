#include "stdafx.h"
#include "RCHashCalcCrc32.h"
#include "7zCrc.h"

RCHashCalcCrc32::RCHashCalcCrc32()
{
    CrcGenerateTable() ;
}

RCHashCalcCrc32::~RCHashCalcCrc32()
{

}

void RCHashCalcCrc32::Init(void) 
{
    m_crcValue = CRC_INIT_VAL ;
}

void RCHashCalcCrc32::Update(const BYTE* data, UINT32 size)
{
    m_crcValue = CrcUpdate(m_crcValue, data, size);
}

void RCHashCalcCrc32::Finish(void)
{
    m_crcValue = m_crcValue ^ 0xFFFFFFFF ;
}

UINT32 RCHashCalcCrc32::GetValue()
{
    /*RCString::value_type crcValue[32] = {0} ;
    swprintf_s(crcValue, 32, L"%08X", m_impl->m_crc) ;*/

    return m_crcValue;
}

bool RCHashCalcCrc32::GetRawValue(BYTE* data, UINT32 size) 
{
    if((data == NULL) || (size < sizeof(m_crcValue)))
    {
        return false ;
    }
    memcpy(data, &(m_crcValue), sizeof(m_crcValue)) ;
    return true ;
}
