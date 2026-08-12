// WnMBManager.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#include "stdafx.h"


class DataFilterManagerApp : public CWinApp
{
public:
	DataFilterManagerApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

public:
    void RecursiveFilterFile(const CString& strPath, bool isEncode);

public:
    bool FilterFileToMemory(xstring inFilePath, vector<BYTE>& output);
    bool RestoreFileToMemory(xstring inFilePath, vector<BYTE>& output);

    bool FilterFileToFile(xstring inFilePath, xstring outFilePath);
    bool RestoreFileToFile(xstring inFilePath, xstring outFilePath);
};

extern DataFilterManagerApp theApp;
