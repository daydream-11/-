#ifndef __GSWinFile_h_
#define __GSWinFile_h_ 1

#include "stdafx.h"

class GSWinFile
{
public:

    /** 默认构造函数
    */
    GSWinFile() ;
    
    /** 默认析构函数
    */
    ~GSWinFile() ;
    
public:

    /** 创建文件
    @param [in] fileName 文件名
    @param [in] desiredAccess 访问属性
    @param [in] shareMode 共享属性
    @param [in] creationDisposition 创建属性
    @param [in] flagsAndAttributes 标记位
    @return 成功返回true, 否则返回false
    */
    bool Create(const xstring& fileName,
                DWORD desiredAccess,
                DWORD shareMode, 
                DWORD creationDisposition,  
                DWORD flagsAndAttributes) ;
    
    /** 关闭文件
    @return 关闭成功返回true, 否则返回false
    */
    bool Close() ;
    
    /** 获取当前文件位置偏移
    @param [out] position 返回当前文件位置偏移
    @return 成功返回true, 否则返回false
    */
    bool GetPosition(UINT64& position) const;
    
    /** 获取当前文件长度
    @param [out] length 返回当前文件长度
    @return 成功返回true, 否则返回false
    */
    bool GetLength(UINT64& length) const;

    /** 读取文件数据
    @param [out] data 数据缓冲区
    @param [in] size 期望读取的数据大小
    @param [in] processedSize 实际读取的大小
    @return 成功返回true, 失败返回false
    */
    bool Read(void* data, UINT32 size, UINT32& processedSize);

    /** 写入数据
    @param [in] data 数据缓冲区
    @param [in] size 数据长度
    @param [out] processedSize 实际写入的数据长度
    @return 成功返回true, 失败返回false
    */
    bool Write(const void* data, UINT32 size, UINT32& processedSize) ;
    
    /** 定位文件位置
    @param [in] distanceToMove 移动偏移量
    @param [in] moveMethod 移动方法
    @param [out] newPosition 移动后新的文件位置偏移
    @return 成功返回true, 否则返回false
    */
    bool Seek(INT64 distanceToMove, DWORD moveMethod, UINT64& newPosition) const ;
    
    /** 定位文件位置
    @param [in] position 移动偏移量
    @param [out] newPosition 移动后新的文件位置偏移
    @return 成功返回true, 否则返回false
    */
    bool Seek(UINT64 position, UINT64& newPosition);
    
    /** 定位文件偏移到文件首
    @return 成功返回true, 否则返回false
    */
    bool SeekToBegin();
    
    /** 定位文件偏移到文件尾
    @param [out] newPosition 移动后新的文件位置偏移
    @return 成功返回true, 否则返回false
    */
    bool SeekToEnd(UINT64& newPosition);
    
    /** 取当前文件名
    @return 返回当前文件名，含完整路径
    */
    const xstring& GetFileName() const ;
    
protected:
    
    /** 文件句柄
    */
    HANDLE m_handle ;
    
    /** 文件名
    */
    xstring m_fileName ;
};

#endif //__GSWinFile_h_
