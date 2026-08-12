//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   ZLibWrapLib.cpp
//    Author:      Streamlet
//    Create Time: 2010-09-16
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "ScopeGuard.h"

#include "ZipHandler.h"


#define ZIP_GPBF_LANGUAGE_ENCODING_FLAG 0x800

wstring CZipHandler::ANSIToUCS2(const string &strANSI, UINT uCodePage /*= CP_ACP*/)
{
    int size = MultiByteToWideChar(uCodePage, 0, strANSI.c_str(), -1, NULL, 0);
    if (size == 0)
    {
        return L"";
    }

    WCHAR *szUCS2 = new WCHAR[size];
    if (MultiByteToWideChar(uCodePage, 0, strANSI.c_str(), -1, szUCS2, size) == 0)
    {
        delete[] szUCS2;
        return L"";
    }

    wstring ret = szUCS2;
    delete[] szUCS2;

    return ret;
}

string CZipHandler::UCS2ToANSI(const wstring &strUCS2, UINT uCodePage /*= CP_ACP*/)
{
    int size = WideCharToMultiByte(uCodePage, 0, strUCS2.c_str(), -1, NULL, 0, NULL, NULL);

    if (size == 0)
    {
        return "";
    }

    CHAR *szANSI = new CHAR[size];

    if (WideCharToMultiByte(uCodePage, 0, strUCS2.c_str(), -1, szANSI, size, NULL, NULL) == 0)
    {
        delete[] szANSI;
        return "";
    }

    string ret = szANSI;
    delete[] szANSI;

    return ret;
}

BOOL CZipHandler::ZipAddFile(zipFile zf, const xstring& lpszFileNameInZip, const xstring& lpszFilePath, bool bUtf8 /*= false*/)
{
    DWORD dwFileAttr = GetFileAttributes(lpszFilePath.c_str());

    if (dwFileAttr == INVALID_FILE_ATTRIBUTES)
    {
        return false;
    }

    DWORD dwOpenAttr = (dwFileAttr & FILE_ATTRIBUTE_DIRECTORY) != 0 ? FILE_FLAG_BACKUP_SEMANTICS : 0;
    HANDLE hFile = CreateFile(lpszFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, dwOpenAttr, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    LOKI_ON_BLOCK_EXIT(CloseHandle, hFile);
    
    FILETIME ftUTC, ftLocal;

    GetFileTime(hFile, NULL, NULL, &ftUTC);
    FileTimeToLocalFileTime(&ftUTC, &ftLocal);

    WORD wDate, wTime;
    FileTimeToDosDateTime(&ftLocal, &wDate, &wTime);

    zip_fileinfo FileInfo;
    ZeroMemory(&FileInfo, sizeof(FileInfo));

    FileInfo.dosDate = ((((DWORD)wDate) << 16) | (DWORD)wTime);
    FileInfo.external_fa |= dwFileAttr;

    if (bUtf8)
    {
        string strFileNameInZipA = UCS2ToANSI(lpszFileNameInZip, CP_UTF8);

        if (zipOpenNewFileInZip4(zf, strFileNameInZipA.c_str(), &FileInfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, 9,
                                 0, -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, NULL, 0, 0, ZIP_GPBF_LANGUAGE_ENCODING_FLAG) != ZIP_OK)
        {
            return FALSE;
        }
    }
    else
    {
        string strFileNameInZipA = UCS2ToANSI(lpszFileNameInZip);

        if (zipOpenNewFileInZip(zf, strFileNameInZipA.c_str(), &FileInfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, 9) != ZIP_OK)
        {
            return FALSE;
        }
    }

    LOKI_ON_BLOCK_EXIT(zipCloseFileInZip, zf);

    if ((dwFileAttr & FILE_ATTRIBUTE_DIRECTORY) != 0)
    {
        return TRUE;
    }

    const DWORD BUFFER_SIZE = 4096;
    BYTE byBuffer[BUFFER_SIZE];

    LARGE_INTEGER li = {};

    if (!GetFileSizeEx(hFile, &li))
    {
        return FALSE;
    }

    while (li.QuadPart > 0)
    {
        DWORD dwSizeToRead = li.QuadPart > (LONGLONG)BUFFER_SIZE ? BUFFER_SIZE : (DWORD)li.LowPart;
        DWORD dwRead = 0;

        if (!ReadFile(hFile, byBuffer, dwSizeToRead, &dwRead, NULL))
        {
            return FALSE;
        }

        if (zipWriteInFileInZip(zf, byBuffer, dwRead) < 0)
        {
            return FALSE;
        }

        li.QuadPart -= (LONGLONG)dwRead;
    }

    return TRUE;
}

BOOL CZipHandler::ZipAddFiles(zipFile zf, const xstring& lpszFileNameInZip, const xstring& lpszFiles, bool bUtf8 /*= false*/)
{
	WIN32_FIND_DATA fd;
	HANDLE hf;
	xstring strFilePath = lpszFiles;
	xstring strFile = lpszFiles;
	strFile += _T("*.*");
	hf = FindFirstFile(strFile.c_str(), &fd);
	xstring strFileNameInZip = lpszFileNameInZip;
	if(hf == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	do
	{
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (fd.cFileName[0] == _T('.'))
			{
				continue;
			}
			/*_tcscpy(szFileName, strFromFileDir);
			_tcscat(szFileName, fd.cFileName);
			_tcscat(szFileName, _T("\\"));
			BOOL bFlag = GetAllFileName(szFileName, vectorFileName);
			if (!bFlag)
			{
				return FALSE;
			}*/
		}
		else
		{
			if (!ZipAddFile(zf, strFileNameInZip + fd.cFileName, strFilePath + fd.cFileName, bUtf8))
			{
				return FALSE;
			}
		}
	}
	while(FindNextFile(hf,&fd));
	FindClose(hf);
	return TRUE;
}

BOOL CZipHandler::ZipCompress(const xstring& lpszSourceFiles, const xstring& lpszDestFile, bool bUtf8 /*= false*/)
{
    string strDestFile = UCS2ToANSI(lpszDestFile);

    zipFile zf = zipOpen64(strDestFile.c_str(), 0);

    if (zf == NULL)
    {
        return FALSE;
    }

    LOKI_ON_BLOCK_EXIT(zipClose, zf, (const char *)NULL);

    if (!ZipAddFiles(zf, _T(""), lpszSourceFiles, bUtf8))
    {
        return FALSE;
    }

    return TRUE;
}

BOOL CZipHandler::ZipExtractCurrentFile(unzFile uf, LPCTSTR lpszDestFolder)
{
    char szFilePathA[MAX_PATH];
    unz_file_info64 FileInfo;

    if (unzGetCurrentFileInfo64(uf, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0) != UNZ_OK)
    {
        return FALSE;
    }

    if (unzOpenCurrentFile(uf) != UNZ_OK)
    {
        return FALSE;
    }
    
    LOKI_ON_BLOCK_EXIT(unzCloseCurrentFile, uf);

    wstring strDestPath = lpszDestFolder;
    wstring strFileName;

    if ((FileInfo.flag & ZIP_GPBF_LANGUAGE_ENCODING_FLAG) != 0)
    {
        strFileName = ANSIToUCS2(szFilePathA, CP_UTF8);
    }
    else
    {
        strFileName = ANSIToUCS2(szFilePathA);
    }

    int nLength = (int)strFileName.size();

    TCHAR lpszFileName[MAX_PATH*2] = {0};
    memcpy_s(lpszFileName, sizeof(TCHAR)*MAX_PATH*2, strFileName.c_str(), sizeof(TCHAR)*strFileName.size());
    LPTSTR lpszCurrentFile = lpszFileName;

    for (int i = 0; i <= nLength; ++i)
    {
        if (lpszFileName[i] == _T('\0'))
        {
            strDestPath += lpszCurrentFile;
            break;
        }

        if (lpszFileName[i] == '\\' || lpszFileName[i] == '/')
        {
            lpszFileName[i] = '\0';

            strDestPath += lpszCurrentFile;
            strDestPath += _T("\\");

            CreateDirectory(strDestPath.c_str(), NULL);
            
            lpszCurrentFile = lpszFileName + i + 1;
        }
    }

    if (lpszCurrentFile[0] == _T('\0'))
    {
        return TRUE;
    }

    HANDLE hFile = CreateFile(strDestPath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
         return FALSE;
    }

    LOKI_ON_BLOCK_EXIT(CloseHandle, hFile);
    
    const DWORD BUFFER_SIZE = 4096;
    BYTE byBuffer[BUFFER_SIZE];

    while (true)
    {
        int nSize = unzReadCurrentFile(uf, byBuffer, BUFFER_SIZE);

        if (nSize < 0)
        {
            return FALSE;
        }
        else if (nSize == 0)
        {
            break;
        }
        else
        {
            DWORD dwWritten = 0;

            if (!WriteFile(hFile, byBuffer, (DWORD)nSize, &dwWritten, NULL) || dwWritten != (DWORD)nSize)
            {
                return FALSE;
            }
        }
    }

    FILETIME ftLocal, ftUTC;

    DosDateTimeToFileTime((WORD)(FileInfo.dosDate>>16), (WORD)FileInfo.dosDate, &ftLocal);
    LocalFileTimeToFileTime(&ftLocal, &ftUTC);
    SetFileTime(hFile, &ftUTC, &ftUTC, &ftUTC);
    
    return TRUE;
}

BOOL CZipHandler::ZipExtract(const xstring& lpszSourceFile, const xstring& lpszDestFolder)
{
    string strSourceFileA = UCS2ToANSI(lpszSourceFile);
    unzFile uf = unzOpen64(strSourceFileA.c_str());
    if (uf == NULL)
    {
        return FALSE;
    }

    LOKI_ON_BLOCK_EXIT(unzClose, uf);

    unz_global_info64 gi;

    if (unzGetGlobalInfo64(uf, &gi) != UNZ_OK)
    {
        return FALSE;
    }
    xstring strDestFolder = lpszDestFolder;

    CreateDirectory(lpszDestFolder.c_str(), NULL);

    if (!strDestFolder.empty() && strDestFolder[strDestFolder.length() - 1] != _T('\\'))
    {
        strDestFolder += _T("\\");
    }
    
    for (int i = 0; i < gi.number_entry; ++i)
    {
        if (!ZipExtractCurrentFile(uf, strDestFolder.c_str()))
        {
            return FALSE;
        }
        
        if (i < gi.number_entry - 1)
        {
            if (unzGoToNextFile(uf) != UNZ_OK)
            {
                return FALSE;
            }
        }
    }
  
    return TRUE;
}

BOOL CZipHandler::ZipExtractCurrentFileToMemery(unzFile uf, vector<BYTE>& filesVec)
{
    if (unzOpenCurrentFile(uf) != UNZ_OK)
    {
        return FALSE;
    }

    LOKI_ON_BLOCK_EXIT(unzCloseCurrentFile, uf);

    int nFileSize = (int)filesVec.size();
    int nRemainSize = nFileSize;
    const DWORD BUFFER_SIZE = 4096;
    BYTE byBuffer[BUFFER_SIZE];

    while (true)
    {
        int nSize = unzReadCurrentFile(uf, byBuffer, BUFFER_SIZE);

        if (nSize < 0)
        {
            return FALSE;
        }
        else if (nSize == 0)
        {
            break;
        }
        else
        {
            DWORD dwWritten = 0;

            if (nRemainSize < nSize)
            {
                //缓存不足
                return FALSE;
            }
            memcpy_s(&filesVec[nFileSize - nRemainSize], nRemainSize, byBuffer, nSize);
            nRemainSize -= nSize;
        }
    }
    return TRUE;
}


BOOL CZipHandler::ZipExtractAllToMemery(const xstring& lpszSourceFile, map<xstring, ByteArr>& filesData)
{
    filesData.clear();
    string strSourceFileA = UCS2ToANSI(lpszSourceFile);

    unzFile uf = unzOpen64(strSourceFileA.c_str());

    if (uf == NULL)
    {
        return FALSE;
    }

    LOKI_ON_BLOCK_EXIT(unzClose, uf);

    unz_global_info64 gi;

    if (unzGetGlobalInfo64(uf, &gi) != UNZ_OK)
    {
        return FALSE;
    }

    
    for (int i = 0; i < gi.number_entry; ++i)
    {
        //获取文件名
        char szFilePath[MAX_PATH] = {0};
        unz_file_info64 FileInfo;
        if (unzGetCurrentFileInfo64(uf, &FileInfo, szFilePath, sizeof(szFilePath), NULL, 0, NULL, 0) != UNZ_OK)
        {
            return FALSE;
        }

        //获取文件数据
        vector<BYTE> curFilesData;
        int nFileSize = (int)FileInfo.uncompressed_size;
        curFilesData.resize(nFileSize);
        if (!ZipExtractCurrentFileToMemery(uf, curFilesData))
        {
            return FALSE;
        }
        if (szFilePath != NULL)
        {
            filesData.insert(std::make_pair(ANSIToUCS2(szFilePath), curFilesData));
        }

        //继续解压下一个文件
        if (i < gi.number_entry - 1)
        {
            if (unzGoToNextFile(uf) != UNZ_OK)
            {
                return FALSE;
            }
        }
    }

    return TRUE;
}

BOOL CZipHandler::ZipExtractOneFileToMemery(const xstring& lpszSourceFile, const xstring& fileName, vector<BYTE>& filesVec)
{
    string strSourceFileA = UCS2ToANSI(lpszSourceFile);
    unzFile uf = unzOpen64(strSourceFileA.c_str());

    if (uf == NULL)
    {
        return FALSE;
    }
    LOKI_ON_BLOCK_EXIT(unzClose, uf);

    unz_global_info64 gi;
    if (unzGetGlobalInfo64(uf, &gi) != UNZ_OK)
    {
        return FALSE;
    }

    for (int i = 0; i < gi.number_entry; ++i)
    {
        char szFilePath[MAX_PATH] = {0};
        unz_file_info64 FileInfo;
        if (unzGetCurrentFileInfo64(uf, &FileInfo, szFilePath, sizeof(szFilePath), NULL, 0, NULL, 0) != UNZ_OK)
        {
            return FALSE;
        }
        int nFileSize = (int)FileInfo.uncompressed_size;
        filesVec.resize(nFileSize);

        wstring filePath = ANSIToUCS2(szFilePath);
        if (!filePath.compare(fileName))
        {
            if (!ZipExtractCurrentFileToMemery(uf, filesVec))
            {
                return FALSE;
            }
            return TRUE;
        }
        //未找到继续查找
        if (i < gi.number_entry - 1)
        {
            if (unzGoToNextFile(uf) != UNZ_OK)
            {
                return FALSE;
            }
        }
    }
    return FALSE;
}

