#include "stdafx.h"
#include "GSDataEncrypt.h"
#include "gost.h"
#include<assert.h>


GSEncryptDataHeader::GSEncryptDataHeader(bool isNeedAlign)
: m_isNeedAlign(isNeedAlign)
{

}

GSEncryptDataHeader::~GSEncryptDataHeader()
{

}


UINT32 GSEncryptDataHeader::Encode(vector<BYTE>& output) const
{
    WriteInt32(m_crc, output) ;
    WriteInt32(m_dataLen, output) ;

    if (m_isNeedAlign)
    {
        WriteInt32(m_dummyLen, output) ;
        return sizeof(UINT32)*3 ;
    }
    else
    {
        return sizeof(UINT32)*2 ;
    }
    
}

UINT32 GSEncryptDataHeader::Decode(const BYTE* input, UINT32 inputLen)
{
    if(inputLen < sizeof(UINT32)*3)
    {
        return 0 ;
    }
    UINT32 offset = 0 ;
    ReadInt32(input + offset, m_crc) ;
    offset += sizeof(UINT32) ;
    ReadInt32(input + offset, m_dataLen) ;
    if (m_isNeedAlign)
    {
        offset += sizeof(UINT32) ;
        ReadInt32(input + offset, m_dummyLen) ;
        return sizeof(UINT32)*3 ;
    }
    else
    {
        return sizeof(UINT32)*2 ;
    }
}

UINT32 GSEncryptDataHeader::GetCrc(const BYTE* input, UINT32 inputLen) const
{
    return 0 ;
}

void GSEncryptDataHeader::WriteInt32(UINT32 data, vector<BYTE>& output) const
{
    output.push_back((BYTE)(data >> 24)) ;
    output.push_back((BYTE)(data >> 16)) ;
    output.push_back((BYTE)(data >> 8)) ;
    output.push_back((BYTE)(data)) ;
}

void GSEncryptDataHeader::ReadInt32(const BYTE* input, UINT32& value) const
{
    UINT32 offset = 0 ;
    value = (input[offset++]  << 24) ;
    value |= (input[offset++] << 16) ;
    value |= (input[offset++] <<  8) ;
    value |= (input[offset++]) ;
}

GSDataEncrypt::GSDataEncrypt()
{
    //初始化Gost加密的算法密匙
    memcpy(&m_key[0], "光速---", 4);
    memcpy(&m_key[1], "输入---", 4);
    memcpy(&m_key[2], "五笔---", 4);
    memcpy(&m_key[3], "拼音---", 4);
    memcpy(&m_key[4], "用户---", 4);
    memcpy(&m_key[5], "词库---", 4);
    memcpy(&m_key[6], "系统---", 4);
    memcpy(&m_key[7], "词库---", 4);

    for(UINT32 i = 0 ; i < 8 ; ++i)
    {
        m_key[i] <<= 1 ;
        m_key[i] += i ; 
    }
}

GSDataEncrypt::~GSDataEncrypt()
{

}

bool GSDataEncrypt::EncodeData(const BYTE* input, UINT inputLen, vector<BYTE>& output)
{
  if (input == NULL)
  {
      return false;
  }
  if (inputLen == 0)
  {
      output.clear();
      return true;
  }

  //数据补8字节对齐
  UINT32 dummyLen = inputLen % 8;
  if (dummyLen > 0)
  {
    dummyLen = 8 - dummyLen;
  }
  UINT32 exceptedLen = inputLen + dummyLen;

  vector<BYTE> inputData ;
  inputData.resize(exceptedLen) ;
  memcpy(&inputData[0], input, exceptedLen);

  for(UINT32 index = inputLen; index < (UINT32)inputData.size(); ++index)
  {
      inputData[index] = 0 ;
  }

  //生成加密头数据
  GSEncryptDataHeader header ;
  header.m_dataLen  = inputLen ;
  header.m_dummyLen = dummyLen ;
  header.m_crc      = header.GetCrc(input, inputLen) ;

  vector<BYTE> outputBuf ;
  UINT32 headerLen = header.Encode(outputBuf) ;
  assert(headerLen == outputBuf.size()) ;

  outputBuf.resize(outputBuf.size() + inputData.size()) ;

  //执行加密
  if(EncryptData(&inputData[0], (UINT32)inputData.size(), &outputBuf[headerLen], true))
  {
      output.swap(outputBuf) ;
      return true ;
  }
  return false ;    
}


bool GSDataEncrypt::DncodeData(const BYTE* input, UINT inputLen, vector<BYTE>& output)
{
    if(input == NULL)
    {
        return false ;
    }
    if(inputLen == 0)
    {
        output.clear() ;
        return true ;
    }

    GSEncryptDataHeader header ;
    UINT headerLen = header.Decode(input, inputLen) ;
    if( (headerLen == 0) || (headerLen >= inputLen) )
    {
        return false ;
    }

    vector<BYTE> outputBuf ;
    UINT32 readDataLen = inputLen - headerLen ;
    UINT32 nUnit = sizeof(UINT32) * 2 ;
    if((readDataLen % nUnit) != 0)
    {
        return false ;
    }
    outputBuf.resize(readDataLen) ;    
    if(EncryptData(input + headerLen, readDataLen, &outputBuf[0], false))
    {
        if(header.m_dummyLen >= outputBuf.size())
        {
            return false ;
        }

        if(header.m_dummyLen > 0)
        {
            outputBuf.resize(outputBuf.size() - header.m_dummyLen) ;
        }
        if(outputBuf.size() != header.m_dataLen)
        {
            return false ;
        }
        //数据校验
        UINT32 crc = header.GetCrc(&outputBuf[0], (UINT32)outputBuf.size()) ;
        if(crc != header.m_crc)
        {
            return false ;
        }
        outputBuf.swap(output) ;
        return true ;
    }
    return false;
}

bool GSDataEncrypt::EncryptData(const BYTE* input, UINT inputLen, BYTE* output, bool isEncrypt)
{
    if( (output == NULL) || (input == NULL) || (inputLen < sizeof(UINT32)) )
    {
        return false ;
    }

     kboxinit(); //初始化加密环境

     UINT32 nTimes = inputLen/8 ; //需要加密/解密的次数
     word32 plain[2];    //明文
     word32 cipher[2];    //加密/解密后的数据

     for (UINT32 nIndex = 0; nIndex < nTimes; ++nIndex)
     {
        word32* pBeginAddr = (word32*)(input + nIndex*8);
        plain[0] = *pBeginAddr ;
        plain[1] = *(pBeginAddr+1) ;
        if(isEncrypt)
        {
            gostcrypt(plain,cipher,m_key) ; //加密
        }
        else
        {
            gostdecrypt(plain,cipher,m_key) ; //解密
        }

        //保存结果
        pBeginAddr = (word32*)(output + nIndex*8);
        *pBeginAddr = cipher[0] ;
        *(pBeginAddr+1) = cipher[1] ;
     }

     return true;
}