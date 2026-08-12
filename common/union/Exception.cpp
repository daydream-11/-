#include "stdafx.h"
#include "Exception.h"
#include <windows.h>
#include <stdio.h>
#include <imagehlp.h>
#pragma comment(lib, "dbghelp.lib")



// 安装软件路径
TCHAR szInstallPath[MAX_PATH] = {'\0'};
// 配置文件路径
TCHAR szCfgRootPath[MAX_PATH] = {'\0'};

LONG WINAPI ExceptionCallBack(_EXCEPTION_POINTERS* pExcp)
{
	typedef int (WINAPI* DUMP_WRITE)(HANDLE, DWORD, HANDLE, MINIDUMP_TYPE, 
		const PMINIDUMP_EXCEPTION_INFORMATION, 
		const PMINIDUMP_USER_STREAM_INFORMATION, 
		const PMINIDUMP_CALLBACK_INFORMATION);
	HMODULE hDll = ::LoadLibrary(_T("DBGHELP.DLL"));
	DUMP_WRITE pWriteFunc = (DUMP_WRITE)::GetProcAddress(hDll, "MiniDumpWriteDump");

	TCHAR szPath[512] = {'\0'};
	TCHAR szExeName[512] = {'\0'};
	TCHAR szDmpFile[512] = {'\0'};
	GetModuleFileName(NULL, szPath, MAX_PATH);
	_tcscpy(szExeName, _tcsrchr(szPath, '\\') + 1);

	SYSTEMTIME mySystemTime = {'\0'};
	::GetLocalTime(&mySystemTime);

	_stprintf(szDmpFile, _T("%s_%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d.dmp"), szExeName, mySystemTime.wYear, mySystemTime.wMonth, mySystemTime.wDay, mySystemTime.wHour, mySystemTime.wMinute, mySystemTime.wSecond);
	_stprintf(szPath, _T("%sDmp\\"), szCfgRootPath);
	if (!::PathFileExists(szPath))
	{
		::CreateDirectory(szPath, NULL);
	}
	_tcscat(szPath, szDmpFile);
	HANDLE hFile = ::CreateFile(szPath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile != INVALID_HANDLE_VALUE)
	{		
		_MINIDUMP_EXCEPTION_INFORMATION exinfo = {0};
		exinfo.ThreadId = ::GetCurrentThreadId();
		exinfo.ExceptionPointers = pExcp;
		exinfo.ClientPointers = 0;
		(*pWriteFunc)(::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, MiniDumpNormal, &exinfo, 0, 0);
		::CloseHandle(hFile);
		//
		TCHAR szUseVestigeFile[MAX_PATH] = {'\0'};
		_stprintf(szUseVestigeFile, _T("%sConfig\\UseVestige.ini"), szCfgRootPath);
		int uUpDmpLastDay = GetPrivateProfileInt(_T("Setting"), _T("UpDmpLastDay"), -1, szUseVestigeFile);
		//
		if (uUpDmpLastDay != mySystemTime.wDay)
		{
			//
			TCHAR szRunExe[MAX_PATH] = {'\0'};
			
			TCHAR szMutualExe[MAX_PATH] = {'\0'};
			_tcscpy(szMutualExe, g_pGlobals->GetConfigure()->GetInstallPath());
			_tcscat(szMutualExe, MUTUAL_EXE_NAME);
			//
			_tcscpy(szRunExe, _T("\""));
			_tcscat(szRunExe, szMutualExe);
			_tcscat(szRunExe, _T("\" UpDmpInfo "));
			_tcscat(szRunExe, szDmpFile);
			Sleep(2000);
			
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&si, sizeof(si) );
			si.cb = sizeof(si);
			ZeroMemory( &pi, sizeof(pi) );
			TCHAR szExe[1000];
			_stprintf(szExe, _T("%s"), szRunExe);
			if (CreateProcess(NULL, szExe, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
			{
				CloseHandle(pi.hProcess );
				CloseHandle(pi.hThread );
			}
			// 
			TCHAR szTodayNum[10] = {'\0'};
			_stprintf(szTodayNum, _T("%d"), mySystemTime.wDay);
			WritePrivateProfileString(_T("Setting"), _T("UpDmpLastDay"), szTodayNum, szUseVestigeFile);
		}
	}
	::FreeLibrary(hDll);

	return EXCEPTION_EXECUTE_HANDLER;
}

//LONG WINAPI ExceptionCallBack(PEXCEPTION_POINTERS excpInfo)
//{
//	if (excpInfo == NULL)
//	{
//		return 0;
//	} 
//	else
//	{
//		TCHAR szPath[512] = {'\0'};
//		TCHAR szExeName[512] = {'\0'};
//		TCHAR szDmpFile[512] = {'\0'};
//		GetModuleFileName(NULL, szPath, MAX_PATH);
//		_tcscpy(szExeName, _tcsrchr(szPath, '\\') + 1);
//
//		SYSTEMTIME mySystemTime = {'\0'};
//		::GetLocalTime(&mySystemTime);
//
//		_stprintf(szDmpFile, _T("%s_%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d.dmp"), szExeName, mySystemTime.wYear, mySystemTime.wMonth, mySystemTime.wDay, mySystemTime.wHour, mySystemTime.wMinute, mySystemTime.wSecond);
//		_stprintf(szPath, _T("%sDmp\\"), szCfgRootPath);
//		if (!::PathFileExists(szPath))
//		{
//			::CreateDirectory(szPath, NULL);
//		}
//		_tcscat(szPath, szDmpFile);
//		HANDLE hFile = 
//			CreateFile( szPath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
//
//		OutputDebugString(_T("writing minidumprn"));
//		MINIDUMP_EXCEPTION_INFORMATION eInfo;
//		eInfo.ThreadId = GetCurrentThreadId(); //把需要的信息添进去
//		eInfo.ExceptionPointers = excpInfo;
//		eInfo.ClientPointers = FALSE;
//		//输出栈数据
//		//fwrite((void*)excpInfo->ContextRecord->Esp, g_pStackStart - (char*)excpInfo->ContextRecord->Esp, 1, _tfopen(dmpfile, _T("wb")));
//
//		// 调用, 生成Dump. 98不支持
//		// Dump的类型是小型的, 节省空间. 可以参考MSDN生成更详细的Dump.
//		MiniDumpWriteDump(
//			GetCurrentProcess(),
//			GetCurrentProcessId(),
//			hFile,
//			(MINIDUMP_TYPE)(MiniDumpWithDataSegs | MiniDumpWithHandleData | MiniDumpFilterMemory | MiniDumpWithPrivateReadWriteMemory | MiniDumpWithFullMemory),
//			excpInfo ? &eInfo : NULL,
//			NULL,
//			NULL);
//		CloseHandle( hFile );
//	}
//	return 1;
//}

VOID DisableSetUnhandledExceptionFilter()
{
	void *pProcAddress = (void*)GetProcAddress(LoadLibrary(_T("kernel32.dll")),	"SetUnhandledExceptionFilter");

	if (pProcAddress != NULL)
	{
		unsigned char szCode[16];
		INT nSize = 0;
		szCode[nSize++] = 0x33;
		szCode[nSize++] = 0xC0;
		szCode[nSize++] = 0xC2;
		szCode[nSize++] = 0x04;
		szCode[nSize++] = 0x00;

		DWORD dwOldFlag = 0;
		DWORD dwTempFlag = 0;
		VirtualProtect(pProcAddress, nSize, PAGE_READWRITE, &dwOldFlag);
		WriteProcessMemory(GetCurrentProcess(), pProcAddress, szCode, nSize, NULL);
		VirtualProtect(pProcAddress, nSize, dwOldFlag, &dwTempFlag);
	}
}

VOID InitExceptionHandler(const TCHAR *lpszInstallPath, const TCHAR *lpszCfgRootPath)
{
	_tcscpy(szInstallPath, lpszInstallPath);
	_tcscpy(szCfgRootPath, lpszCfgRootPath);
	::SetUnhandledExceptionFilter(ExceptionCallBack);
//#ifndef _DEBUG
//	DisableSetUnhandledExceptionFilter();			//release模式下，必须使用API HOOK拦截系统的异常处理
//#endif
}

