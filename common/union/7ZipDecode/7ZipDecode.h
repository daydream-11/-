
#if !defined(AFX_7ZIPDECODE_H__390B1D85_C108_4EF5_9FAF_0A0B86644670__INCLUDED_)
#define AFX_7ZIPDECODE_H__390B1D85_C108_4EF5_9FAF_0A0B86644670__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

//typedef void (*extract_callback_fun)(size_t size, size_t total);

class IExtractCallback
{
public:
    virtual void ExtractCallback(UINT uSize , UINT uTotal) = 0;
};

int DoRunCompress(const wchar_t *lpszExtractPath, const char *lpszCompressFile, IExtractCallback* pExtractCallback);

#endif // !defined(AFX_7ZIPDECODE_H__390B1D85_C108_4EF5_9FAF_0A0B86644670__INCLUDED_)
