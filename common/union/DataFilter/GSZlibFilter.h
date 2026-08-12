#ifndef  __GSZlIB_FILTER_h_
#define  __GSZlIB_FILTER_h_

#include "../zlib/zlib.h"
#include<assert.h>

typedef enum CompressLevel
{
    ZLIB_LEVEL_NO_COMPRESSION = 0,
    ZLIB__LEVEL_BEST_SPEED = 1,
    ZLIB__LEVEL_BEST_COMPRESSION = 9,
    ZLIB__LEVEL_DEFAULT_COMPRESSION = (-1)
} ;

/** zlib文件压缩解压实现
*/
class GSZlibFilter
{
public:

    /** 默认构造函数
    */
    GSZlibFilter();

    /** 默认析构函数
    */
    ~GSZlibFilter();

    bool UnCompressFromMemToMem(BYTE* inputBuffer, UINT32 inBufferSize, BYTE* outputBuffer, UINT32 outBufferSize, UINT32& outputSize);

    /** 文件压缩到内存
    @param [in] srcName 压缩源文件
    @param [in] output 压缩后数据缓存
    */
    bool CompressToMemory(const xstring srcName, vector<BYTE>& output, CompressLevel level);

    /** 文件压缩到内存
    @param [in] srcName 压缩源文件
    @param [in] output 解压后数据缓存
    */
    bool UnCompressToMemory(const xstring srcName, vector<BYTE>& output);

    /** 文件压缩
    @param [in] srcName 压缩源文件
    @param [in] destName 压缩生成的目标文件
    @param [in] level 压缩等级
    */
    bool CompressFile(const xstring srcName,const xstring destName, CompressLevel level);

    /** 文件解压
    @param [in] srcName 需要解压的压缩文件
    @param [in] destName 解压后目标文件
    */
    bool UnCompressFile(const xstring srcName,const xstring destName);
    
};

#endif // __GSZlIB_FILTER_h_

