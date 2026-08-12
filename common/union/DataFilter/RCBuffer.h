
#ifndef __RCBuffer_h_
#define __RCBuffer_h_ 1

#include <algorithm>
#include <cstring>

template <typename T> 
class RCBuffer
{
public:

    /** 默认构造函数
    */
    RCBuffer() ;
    
    /** 默认析构函数
    */
    virtual ~RCBuffer() ;
    
    /** 指定大小的构造函数
    @param [in] size 缓冲区大小
    */
    explicit RCBuffer(size_t size) ;
    
    /** 拷贝构造函数
    @param [in] from 复制的对象
    */
    RCBuffer(const RCBuffer& from) ;
    
    /** 赋值操作符
    @param [in] from 复制的对象
    */
    RCBuffer& operator= (const RCBuffer& from) ;
    
public:
    
    /** 获取缓冲区大小
    @return 返回缓冲区大小
    */
    size_t GetCapacity() const ;
    
    /** 设置缓冲区大小
    @param [in] newCapacity 新的缓冲区大小
    */
    void SetCapacity(size_t newCapacity) ;
    
    /** 释放缓冲区
    */
    void Free() ;
    
    /** 获取缓冲区地址
    @return 返回缓冲区地址
    */
    T* data() ;
    
    /** 只读方式获取缓冲区地址
    @return 返回缓冲区地址
    */
    const T* data() const ;
    
    /** 设置数据长度
    @param [in] dataLen 数据长度
    */
    void SetDataLength(size_t dataLen) ;
    
    /** 获取数据长度
    @return 返回数据长度
    */
    size_t GetDataLength(void) const ;
    
    /** operator []
    @param [in] index 数值下标
    @return 返回下标对应的值
    */
    const T operator [] (size_t index) const ;
    
protected:
    
    /** 缓冲区大小
    */
    size_t m_capacity;
    
    /** 缓冲区数据
    */
    T* m_data ;
    
    /** 数据大小
    */
    size_t m_dataLen ;
};

/** 字节类型的缓冲区
*/
typedef RCBuffer<BYTE> RCByteBuffer ;

#include "RCBuffer.inl"

#endif //__RCBuffer_h_
