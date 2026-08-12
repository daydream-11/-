
#ifndef __GSWinMD5_h_
#define __GSWinMD5_h_  1


/** MD5签名生成类, Windows平台实现
*/
class GSWinMD5
{    
public:

    /** 默认构造函数
    */
    GSWinMD5() ;
    
    /** 默认析构函数
    */
    ~GSWinMD5() ;
    
public:
    
    /** 执行初始化
    */
    void Init(void) ;
    
    /** 执行数据校验
    @param [in] data 需要计算的数据
    @param [in] size 数据长度
    */
    void Update(const BYTE* data, UINT32 size) ;
    
    /** 数据校验完成
    */
    void Finish(BYTE digest[16]) ;

    /** 生成的MD5字串
    */
    xstring GetMD5String(BYTE digest[16]);
    
private:
    
    /** 按照MSDN中的说明, 定义函数原型
    */
    typedef struct   
    {  
        ULONG i[2];  
        ULONG buf[4];  
        unsigned char in[64];  
        unsigned char digest[16];
    } MD5_CTX ;
    
    
    typedef void (CALLBACK* PFN_MD5Init)(MD5_CTX* context) ;
    typedef void (CALLBACK* PFN_MD5Update)(MD5_CTX* context, unsigned char* input, unsigned int inlen) ;
    typedef void (CALLBACK* PFN_MD5Final)(MD5_CTX* context) ;  
    
private:
    
    /** Cryptdll.dll 的句柄
    */
    HINSTANCE m_hDLL ;
    
    /** MD5初始化函数
    */
    PFN_MD5Init m_pfnMD5Init ;  
    
    /** MD5初计算函数
    */
    PFN_MD5Update m_pfnMD5Update ;
    
    /** MD5结束函数
    */
    PFN_MD5Final m_pfnMD5Final ;
    
    /** MD5 Context
    */
    MD5_CTX m_md5Context ;
};


#endif //__GSWinMD5_h_
