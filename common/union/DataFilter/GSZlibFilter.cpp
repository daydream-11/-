#include "stdafx.h"
#include "GSZlibFilter.h"
#include "RCBuffer.h"
#include "GSWinFile.h"

#ifdef _DEBUG
	#pragma comment(lib, "zlibstaticd.lib")
#else
	#pragma comment(lib, "zlibstatic.lib")
#endif

/** 一次读写数据缓存大小
*/
#define CHUNK 16384

GSZlibFilter::GSZlibFilter()
{
    
}

GSZlibFilter::~GSZlibFilter()
{

}

bool GSZlibFilter::UnCompressFromMemToMem(BYTE* inputBuffer, UINT32 inBufferSize, BYTE* outputBuffer, UINT32 outBufferSize, UINT32& outputSize)
{
    //简单解压
    if (!inputBuffer || !outputBuffer)
    {
        assert(0);
        return false;
    }

    z_stream zlibStream;
    zlibStream.zalloc = Z_NULL;
    zlibStream.zfree  = Z_NULL;
    zlibStream.opaque = Z_NULL;
    zlibStream.avail_in = 0;
    zlibStream.next_in = Z_NULL;
    INT ret = inflateInit(&zlibStream);
    if (ret != Z_OK)
    {
        return false;
    }

    zlibStream.avail_in = inBufferSize;
    zlibStream.next_in = inputBuffer;
    zlibStream.avail_out = outBufferSize;
    zlibStream.next_out = outputBuffer;

    ret = inflate(&zlibStream, Z_NO_FLUSH);
    if (ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR)
    {
        inflateEnd(&zlibStream);
        return false;
    }
    outputSize = zlibStream.total_out;
    ret = inflateEnd(&zlibStream);

    return ret == Z_OK ? true : false;
}

bool GSZlibFilter::CompressToMemory(const xstring srcName, vector<BYTE>& output, CompressLevel level)
{
    FILE *inStream = _tfopen(srcName.c_str(), _T("rb"));
    if (inStream == NULL)
    {
        return false;
    }
    RCBuffer<BYTE> inTempBuffer(CHUNK);
    RCBuffer<BYTE> outTempBuffer(CHUNK);

    BYTE* inBuffer = inTempBuffer.data();
    BYTE* outBuffer = outTempBuffer.data();

    z_stream zlibStream;
    zlibStream.zalloc = Z_NULL;
    zlibStream.zfree  = Z_NULL;
    zlibStream.opaque = Z_NULL;
    INT ret = deflateInit(&zlibStream, level);
    if (ret != Z_OK)
    {
        fclose(inStream);
        return false;
    }

    INT32 flush ;
    vector<BYTE> outBuf;
    // compress until end of file
    do 
    {
        zlibStream.avail_in = fread(inBuffer, 1, CHUNK, inStream);
        if (ferror(inStream)) 
        {
            deflateEnd(&zlibStream);
            fclose(inStream);
            return false;
        }
        flush = feof(inStream) ? Z_FINISH : Z_NO_FLUSH;
        zlibStream.next_in = inBuffer;
        
        // run deflate() on input until output buffer not full, finish compression if all of source has been read in 
        do 
        {
            zlibStream.avail_out = CHUNK;
            zlibStream.next_out = outBuffer;
            ret = deflate(&zlibStream, flush);
            if (ret == Z_STREAM_ERROR)
            {
                assert(0);
            }

            //递增压缩数据缓存
            UINT32 wirteSize = CHUNK - zlibStream.avail_out;
            UINT32 currentSize = outBuf.size();
            outBuf.resize(currentSize + wirteSize);
            memcpy(&outBuf[currentSize], outBuffer, wirteSize);

        } while (zlibStream.avail_out == 0);
        if (zlibStream.avail_in != 0)
        {
            assert(zlibStream.avail_in == 0);
            fclose(inStream);
            return false;
        }
    } while (flush != Z_FINISH);
    if (ret != Z_STREAM_END)
    {
        assert(0);
        fclose(inStream);
        return false;
    }
    output.swap(outBuf);
    deflateEnd(&zlibStream);
    fclose(inStream);

    return true;
}

bool GSZlibFilter::UnCompressToMemory(const xstring srcName, vector<BYTE>& output)
{
    FILE *inStream = _tfopen(srcName.c_str(), _T("rb"));
    if (inStream == NULL)
    {
        return false;
    }

    RCBuffer<BYTE> inTempBuffer(CHUNK);
    RCBuffer<BYTE> outTempBuffer(CHUNK);

    BYTE* inBuffer = inTempBuffer.data();
    BYTE* outBuffer = outTempBuffer.data();

    z_stream zlibStream;
    zlibStream.zalloc = Z_NULL;
    zlibStream.zfree  = Z_NULL;
    zlibStream.opaque = Z_NULL;
    zlibStream.avail_in = 0;
    zlibStream.next_in = Z_NULL;
    INT ret = inflateInit(&zlibStream);
    if (ret != Z_OK)
    {
        fclose(inStream);
        return false;
    }

    vector<BYTE> outBuf;
    // decompress until deflate stream ends or end of file 
    do
    {
        zlibStream.avail_in = fread(inBuffer, 1, CHUNK, inStream);
        if (ferror(inStream)) 
        {
            inflateEnd(&zlibStream);
            fclose(inStream);
            return false;
        }
        if (zlibStream.avail_in == 0)
        {
            break;
        }
        zlibStream.next_in = inBuffer;
        do
        {
            zlibStream.avail_out = CHUNK;
            zlibStream.next_out = outBuffer;

            ret = inflate(&zlibStream, Z_NO_FLUSH);
            if (ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR)
            {
                inflateEnd(&zlibStream);
                fclose(inStream);
                return false;
            }
            //递增解压数据缓存
            UINT32 wirteSize = CHUNK - zlibStream.avail_out;
            UINT32 currentSize = outBuf.size();
            outBuf.resize(currentSize + wirteSize);
            memcpy(&outBuf[currentSize], outBuffer, wirteSize);

        } while (zlibStream.avail_out == 0);
    } while (ret != Z_STREAM_END);

    output.swap(outBuf);
    inflateEnd(&zlibStream);
    fclose(inStream);

    return ret == Z_STREAM_END ? true : false;
}

bool GSZlibFilter::CompressFile(const xstring srcName,const xstring destName, CompressLevel level)
{
    FILE *inStream = _tfopen(srcName.c_str(), _T("rb"));
    if (inStream == NULL)
    {
        return false;
    }

    FILE *outStream = _tfopen(destName.c_str(), _T("wb"));
    if (outStream == NULL)
    {
        fclose(inStream);
        return false;
    }

    RCBuffer<BYTE> inTempBuffer(CHUNK);
    RCBuffer<BYTE> outTempBuffer(CHUNK);

    BYTE* inBuffer = inTempBuffer.data();
    BYTE* outBuffer = outTempBuffer.data();

    z_stream zlibStream;
    zlibStream.zalloc = Z_NULL;
    zlibStream.zfree  = Z_NULL;
    zlibStream.opaque = Z_NULL;
    INT ret = deflateInit(&zlibStream, level);
    if (ret != Z_OK)
    {
        fclose(inStream);
        fclose(outStream);
        return false;
    }

    int flush = 0;
    // compress until end of file
    do 
    {
        zlibStream.avail_in = fread(inBuffer, 1, CHUNK, inStream);
        if (ferror(inStream)) 
        {
            deflateEnd(&zlibStream);
            fclose(inStream);
            fclose(outStream);
            return false;
        }
        flush = feof(inStream) ? Z_FINISH : Z_NO_FLUSH;
        zlibStream.next_in = inBuffer;

        // run deflate() on input until output buffer not full, finish compression if all of source has been read in 
        do 
        {
            zlibStream.avail_out = CHUNK;
            zlibStream.next_out = outBuffer;
            ret = deflate(&zlibStream, flush);
            if (ret == Z_STREAM_ERROR)
            {
                assert(0);
            }
            unsigned remainSize = CHUNK - zlibStream.avail_out;
            if ((fwrite(outBuffer, 1, remainSize, outStream) != remainSize) || ferror(outStream)) 
            {
                deflateEnd(&zlibStream);
                fclose(inStream);
                fclose(outStream);
                return false;
            }
        } while (zlibStream.avail_out == 0);
        if (zlibStream.avail_in != 0)
        {
            assert(zlibStream.avail_in == 0);
            fclose(inStream);
            fclose(outStream);
            return false;
        }
    } while (flush != Z_FINISH);
    if (ret != Z_STREAM_END)
    {
        assert(0);
        fclose(inStream);
        fclose(outStream);
        return false;
    }
    deflateEnd(&zlibStream);
    fclose(inStream);
    fclose(outStream);

    return true;
}


bool GSZlibFilter::UnCompressFile(const xstring srcName,const xstring destName)
{

    FILE *inStream = _tfopen(srcName.c_str(), _T("rb"));
    if (inStream == NULL)
    {
        return false;
    }

    FILE *outStream = _tfopen(destName.c_str(), _T("wb"));
    if (outStream == NULL)
    {
        return false;
    }

    RCBuffer<BYTE> inTempBuffer(CHUNK);
    RCBuffer<BYTE> outTempBuffer(CHUNK);

    BYTE* inBuffer = inTempBuffer.data();
    BYTE* outBuffer = outTempBuffer.data();

    z_stream zlibStream;
    zlibStream.zalloc = Z_NULL;
    zlibStream.zfree  = Z_NULL;
    zlibStream.opaque = Z_NULL;
    zlibStream.avail_in = 0;
    zlibStream.next_in = Z_NULL;
    INT ret = inflateInit(&zlibStream);
    if (ret != Z_OK)
    {
        fclose(inStream);
        fclose(outStream);
        return false;
    }

    // decompress until deflate stream ends or end of file 
    do
    {
        zlibStream.avail_in = fread(inBuffer, 1, CHUNK, inStream);
        if (ferror(inStream)) 
        {
            inflateEnd(&zlibStream);
            fclose(inStream);
            fclose(outStream);
            return false;
        }
        if (zlibStream.avail_in == 0)
        {
            break;
        }
        zlibStream.next_in = inBuffer;

       // run inflate() on input until output buffer not full
        do
        {
            zlibStream.avail_out = CHUNK;
            zlibStream.next_out = outBuffer;
            ret = inflate(&zlibStream, Z_NO_FLUSH);
            if (ret == Z_NEED_DICT  ||
                ret == Z_DATA_ERROR ||
                ret == Z_MEM_ERROR )
            {
                inflateEnd(&zlibStream);
                fclose(inStream);
                fclose(outStream);
                return false;
            }
            unsigned remainSize = CHUNK - zlibStream.avail_out;
            if ((fwrite(outBuffer, 1, remainSize, outStream) != remainSize) || ferror(outStream)) 
            {
                (void)inflateEnd(&zlibStream);
                fclose(inStream);
                fclose(outStream);
                return false;
            }
        } while (zlibStream.avail_out == 0);
    } while (ret != Z_STREAM_END);

    inflateEnd(&zlibStream);
    fclose(inStream);
    fclose(outStream);

    return ret == Z_STREAM_END ? true : false;
}

