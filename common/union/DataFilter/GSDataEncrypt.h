#ifndef  __GSData_Encrypt_h_
#define  __GSData_Encrypt_h_

#include <stdio.h>

class GSEncryptDataHeader
{
public:
    
    /** 构造函数
    @param [in] isNeedAlign 是否需要对齐
    */
    GSEncryptDataHeader(bool isNeedAlign = true);

    /** 析构函数
    */
    ~GSEncryptDataHeader();

    /** 将数据输出到缓冲区
    @param [out] output 输出缓冲区
    @return 返回加密后的字节数
    */
    UINT32 Encode(vector<BYTE>& output) const ;
    
    /** 从缓冲区构造数据
    @param [in] input 输入缓冲区数据
    @param [in] inputLen 输入缓冲区数据长度
    @return 返回解密后的字节数
    */
    UINT32 Decode(const BYTE* input, UINT32 inputLen) ;
    
    /** 获取数据的CRC校验
    @param [in] input 输入缓冲区数据
    @param [in] inputLen 输入缓冲区数据长度
    @return 返回数据的CRC校验码
    */
    UINT32 GetCrc(const BYTE* input, UINT32 inputLen) const ;

private:
    
    /** 将32位整型数写入流
    */
    void WriteInt32(UINT32 data, vector<BYTE>& output) const ;
    
    /** 从流中读取32位整型
    */
    void ReadInt32(const BYTE* input, UINT32& value) const ;
    
public:
    
    /** 原始数据长度
    */
    UINT32 m_dataLen ;
    
    /** 数据的补足位长度
    */
    UINT32 m_dummyLen ;
    
    /** 原始数据的CRC32校验值
    */
    UINT32 m_crc ;

    /** 是否需要数据对齐
    */
    bool m_isNeedAlign;
};

class GSDataEncrypt
{
public:

    /** 默认构造函数
    */
    GSDataEncrypt();

    /** 默认析构函数
    */
    ~GSDataEncrypt();

    /** 加密数据
    @param [in] input  输入数据缓冲区
    @param [in] inputLen 输入数据长度
    @param [out] output 输出加密后的数据
    @return 成功返回true, 否则返回false
    */
    bool EncodeData(const BYTE* input, UINT inputLen, vector<BYTE>& output);

    /** 解密数据
    @param [in] input  输入数据缓冲区
    @param [in] inputLen 输入数据长度
    @param [out] output 输出加密后的数据
    @return 成功返回true, 否则返回false
    */
    bool DncodeData(const BYTE* input, UINT inputLen, vector<BYTE>& output);

    /** 加密或者解密数据
    @param [in] input  输入数据缓冲区
    @param [in] inputLen 输入数据长度
    @param [out] output 输出加密或者后的数据
    @param [out] isEncrypt 是加密或者解密
    @return 成功返回true, 否则返回false
    */
    bool EncryptData(const BYTE* input, UINT inputLen, BYTE* output, bool isEncrypt);

private:
    
    /** 数据加密的最小单位长度
    */
    static const UINT32 GS_DATA_ENCRYPT_KEY_LEN = 8 ;
    
    /** 加密的密钥
    */
    UINT32 m_key[GS_DATA_ENCRYPT_KEY_LEN] ;
    
};

#endif // __GSData_Encrypt_h_

