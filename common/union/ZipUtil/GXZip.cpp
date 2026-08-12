
//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-09-14
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "zipHandler.h"
#include <assert.h>

bool GetAllFileData()
{
    map<xstring, ByteArr> filesData;
    return CZipHandler::ZipExtractAllToMemery(_T("e:\\file.zip"), filesData) == TRUE;
}

int _tmain(int argc, TCHAR *argv[])
{
    BOOL isSuccess = false;
    __try 
    {

       GetAllFileData();
    }
    __except(1)
    {
        assert(_T("Ω‚—π¥ÌŒÛ"));
    }
    return 0;
}




