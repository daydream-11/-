
#ifndef __RCHashCalcCrc32_h_
#define __RCHashCalcCrc32_h_ 1

#include "RCHashCalcCrc32.h"

/** 数据签名计算类
*/
class RCHashCalcCrc32
{
public:
    
    /** 构造函数
    */
    RCHashCalcCrc32() ;
    
    /** 析构函数
    */
    ~RCHashCalcCrc32() ;
    
public:
    
    /** 执行初始化
    */
    virtual void Init(void) ;
    
    /** 执行数据校验
    @param [in] data 需要计算的数据
    @param [in] size 数据长度
    */
    virtual void Update(const BYTE* data, UINT32 size) ;
    
    /** 数据校验完成
    */
    virtual void Finish(void) ;
    
    /** 获取数据校验值
    @return 获取计算结果字符串值
    */
    virtual UINT32 GetValue() ;

    /** 获取原始的校验值:
        MD5的长度为16，SHA1的长度为20，CRC32的长度为4
    @param [in] data 缓冲区地址
    @param [in] size 缓冲区大小
    @return 成功返回true, 如果缓冲区不足，则返回false
    */
    virtual bool GetRawValue(BYTE* data, UINT32 size) ;
    
private:

    UINT32 m_crcValue;
};

#endif //__RCHashCalcCrc32_h_
