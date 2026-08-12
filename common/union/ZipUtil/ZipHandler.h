//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   ZLibWrapLib.h
//    Author:      Streamlet
//    Create Time: 2010-09-14
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __ZIP_WRAP__
#define __ZIP_WRAP__

#include "Zip/zip.h"
#include "Zip/unzip.h"

#include <Windows.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

#ifdef _UNICODE
typedef std::wstring xstring;
#else
typedef std::string xstring;
#endif


typedef std::vector<BYTE> ByteArr;

class CZipHandler
{
public:

	/** zip格式压缩
    @param [in] lpszSourceFiles 需要压缩文件所在的文件夹绝对路径
    @param [in] lpszDestFile 目标文件绝对路径
    @param [in] bUtf8 是否UTF-8编码
    @return 成功返回TRUE, 否则返回FALSE
    */
    BOOL ZipCompress(const xstring& lpszSourceFiles, const xstring& lpszDestFile, bool bUtf8 = false);

    /** zip格式解压缩
    @param [in] lpszSourceFile 需要压缩的文件绝对路径
    @param [in] lpszDestFolder 解压后文件路径
    @return 成功返回TRUE, 否则返回FALSE
    */
    BOOL ZipExtract(const xstring& lpszSourceFile, const xstring& lpszDestFolder);

    /** zip格式解压缩全部文件到内存
    @param [in] lpszSourceFile 需要压缩的文件绝对路径
    @param [in] filesData 解压后文件缓存（使用vector在内部分配内存）
    @return 成功返回TRUE, 否则返回FALSE
    */
    BOOL ZipExtractAllToMemery(const xstring& lpszSourceFile, map<xstring, ByteArr>& filesData);

    /** zip格式解压缩指定文件到内存
    @param [in] lpszSourceFile 需要压缩的文件绝对路径
    @param [in] fileName 压缩包内文件名
    @param [in] filesVec 解压后文件缓存（使用vector在内部分配内存）
    @return 成功返回TRUE, 否则返回FALSE
    */
    BOOL ZipExtractOneFileToMemery(const xstring& lpszSourceFile, const xstring& fileName, vector<BYTE>& filesVec);

private:

    BOOL ZipAddFile(zipFile zf, const xstring& lpszFileNameInZip, const xstring& lpszFilePath, bool bUtf8 = false);
    BOOL ZipAddFiles(zipFile zf, const xstring& lpszFileNameInZip, const xstring& lpszFiles, bool bUtf8 = false);
    BOOL ZipExtractCurrentFile(unzFile uf, LPCTSTR lpszDestFolder);
    BOOL ZipExtractCurrentFileToMemery(unzFile uf, vector<BYTE>& filesVec);

private:
    wstring ANSIToUCS2(const string &strANSI, UINT uCodePage = CP_ACP);
    string UCS2ToANSI(const wstring &strUCS2, UINT uCodePage = CP_ACP);
};

#endif // __ZIP_WRAP__
