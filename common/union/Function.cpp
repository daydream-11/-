#include "StdAfx.h"
#include "shellapi.h"
#include "Function.h"

static const TCHAR pszWWWInputBegin[3][10] = 
{
	{_T("www")}
};

static const TCHAR pszWebInputBegin[2][10] = 
{
	{_T("bbs")},
	{_T("mail")}
};
	
/** @name 构造和虚构函数 */////////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： CFunction
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
CFunction::CFunction(void)
{
	m_pUpdateLayeredWindow = NULL;
	m_hInstanceUser32 = LoadLibrary(_T("User32.DLL")); 
	if(m_hInstanceUser32 != NULL)
	{
		m_pUpdateLayeredWindow = (UpdateLayeredWindowFun)GetProcAddress(m_hInstanceUser32, "UpdateLayeredWindow");
	}
	GetModuleFileName(NULL, m_szExePath, MAX_PATH);
	*(_tcsrchr(m_szExePath, '\\') + 1) = 0;
}

/**********************************************************************
* 函数名称： ~CFunction
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
CFunction::~CFunction(void)
{

}

/// @}




/** @name 公共成员函数 *///////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： CHARToTCHAR
* 功能描述： char字符串指针转换为TCHAR字符串指针
* 输入参数： 
* <param name="pszCHAR"></param>
* <param name="pszTCHAR"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::CHARToTCHAR(const char * pszCHAR, TCHAR * pszTCHAR)
{
	#if _UNICODE
		int nNum = MultiByteToWideChar(CP_ACP, 0, pszCHAR, -1, 0, 0);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszCHAR, -1, pszTCHAR, nNum);
	#else
		sprintf(pszTCHAR, "%s", pszCHAR);
	#endif
}

/**********************************************************************
* 函数名称： TCHARToWCHAR
* 功能描述： TCHAR字符串指针转换为WCHAR字符串指针
* 输入参数： 
* <param name="pszTCHAR"></param>
* <param name="pszWCHAR"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::TCHARToWCHAR(const TCHAR * pszTCHAR, WCHAR * pszWCHAR)
{
	#if _UNICODE
		swprintf(pszWCHAR, L"%s", pszTCHAR);
	#else
		//int nNum = ::MultiByteToWideChar(CP_ACP, 0, pszTCHAR, -1, 0, 0, 0, 0);
		::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszTCHAR, -1, pszWCHAR, MAX_PATH);
	#endif
}
/**********************************************************************
* 函数名称： TCHARToCHAR
* 功能描述： TCHAR字符串指针转换为char字符串指针
* 输入参数： 
* <param name="pszTCHAR"></param>
* <param name="pszCHAR"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::TCHARToCHAR(const TCHAR * pszTCHAR, char * pszCHAR)
{
	#if _UNICODE
		int nNum = WideCharToMultiByte(CP_OEMCP, 0, pszTCHAR, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_OEMCP, NULL, pszTCHAR, -1, pszCHAR, nNum, NULL, FALSE);
	#else
		sprintf(pszCHAR, "%s", pszTCHAR);
	#endif
}

/**********************************************************************
* 函数名称： UnicodeToUTF8
* 功能描述： TCHAR字符串指针转换为UTF-8字符串指针
* 输入参数： 
* <param name="pszTCHAR"></param>
* <param name="pszCHAR"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::UnicodeToUTF8(const TCHAR * pszTCHAR, char * pszCHAR, int & nSize)
{
	nSize = WideCharToMultiByte(CP_UTF8, 0, pszTCHAR, -1, 0, 0, 0, 0 );
	::WideCharToMultiByte(CP_UTF8, 0, pszTCHAR, -1, (char*)pszCHAR, nSize, 0, 0 );
 }

/**********************************************************************
* 函数名称： UTF8ToTCHAR
* 功能描述： UTF8字符串指针转换为TCHAR字符串指针
* 输入参数： 
* <param name="pszCHAR"></param>
* <param name="pszTCHAR"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::UTF8ToTCHAR(const char * pszCHAR, TCHAR * pszTCHAR)
{
	int nNum = MultiByteToWideChar(CP_UTF8, 0, pszCHAR, -1, NULL, 0);
	#if _UNICODE
		::MultiByteToWideChar(CP_UTF8, 0, pszCHAR, -1, pszTCHAR, nNum);
	#else
		wchar_t * strSrc;
		//获得临时变量的大小
		strSrc = new wchar_t[nNum + 1];
		// 先转换为UNICODE
		MultiByteToWideChar(CP_UTF8, 0, pszCHAR, -1, strSrc, nNum);
		//获得临时变量的大小
		nNum = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
		// 在转换为ANSI
		WideCharToMultiByte(CP_ACP, 0, strSrc, -1, pszTCHAR, nNum, NULL, NULL);
		delete[] strSrc;

	#endif
}

//
/**********************************************************************
* 函数名称： TCHARToBIG5
* 功能描述： 繁体到big5
* 输入参数： 
* <param name="pszCHAR"></param>
* <param name="pszTCHAR"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::TCHARToBIG5(const TCHAR * pszTCHAR, TCHAR * pszBIG5)
{
	UINT nCodePage = 950; //BIG5
	int nLength = WideCharToMultiByte(nCodePage, 0, pszTCHAR, -1, NULL, 0, NULL, NULL);
    char * pBuffer = new char[nLength + 1];
    WideCharToMultiByte(nCodePage, 0, pszTCHAR, -1, pBuffer, nLength, NULL, NULL);
    pBuffer[nLength ] = 0;
	CHARToTCHAR(pBuffer, pszBIG5);
	delete[] pBuffer;
	pBuffer = NULL;
}

/**********************************************************************
* 函数名称： 
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 200904/01		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::RunUpdateLayeredWindow(HWND hWnd, HDC hdcDst, POINT* pptDst, SIZE* psize, HDC hdcSrc, POINT* pptSrc, COLORREF crKey, BLENDFUNCTION* pblend, DWORD dwFlags)
{
	if (m_pUpdateLayeredWindow == NULL)
	{
		return FALSE;
	}
	return m_pUpdateLayeredWindow(hWnd, hdcDst, pptDst, psize, hdcSrc, pptSrc, crKey, pblend, dwFlags);
}

/**********************************************************************
* 函数名称： GetColorRef
* 功能描述： 
* 输入参数： 
* <param name="pszColor"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
COLORREF CFunction::GetColorRef(const TCHAR * pszColor)
{
	TCHAR szColor[MAX_PATH] = {'\0'};
	int nTextLen = (int)_tcslen(pszColor);
	const TCHAR * pszTempColor = pszColor;
	int nR = 0;
	int nG = 0;
	int nB = 0;
	if (nTextLen > 2)
	{
		memset(szColor, 0, sizeof(szColor));
		_tcscpy(szColor, _T("0x"));
		_tcsncat(szColor, pszTempColor + 1, 2);
		nR = (int)_tcstol(szColor, NULL, 16);
	}
	if (nTextLen > 4)
	{
		memset(szColor, 0, sizeof(szColor));
		_tcscpy(szColor, _T("0x"));
		_tcsncat(szColor, pszTempColor + 3, 2);
		nG = (int)_tcstol(szColor, NULL, 16);
	}
	if (nTextLen > 6)
	{
		memset(szColor, 0, sizeof(szColor));
		_tcscpy(szColor, _T("0x"));
		_tcsncat(szColor, pszTempColor + 5, 2);
		nB = (int)_tcstol(szColor, NULL, 16);
	}
	return RGB(nR, nG, nB);
}

/**********************************************************************
* 函数名称： CreateUIProcess
* 功能描述： 创建有界面的进程
* 输入参数： 
* <param name="strProcess"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::CreateUIProcess(LPCTSTR strProcess)
{
	if( _tcslen(strProcess) == 0)
	{
		return FALSE;
	}
	SHELLEXECUTEINFO ExecInfo;
	memset( &ExecInfo, 0, sizeof(ExecInfo));
	ExecInfo.lpVerb = _T("open");
	ExecInfo.fMask = SEE_MASK_DOENVSUBST;
	ExecInfo.lpParameters = strProcess;
	ExecInfo.nShow = SW_SHOWNORMAL;

	if ((DWORD)ShellExecute( NULL, _T("open"), strProcess, NULL, NULL,SW_SHOWNORMAL) <= 32)
	{
		CreateRunProcess(strProcess);
	}
	return TRUE;
}

/**********************************************************************
* 函数名称： CreateRunProcess
* 功能描述： 创建运行进程
* 输入参数： 
* <param name="strProcess"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::CreateRunProcess(LPCTSTR strProcess)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	TCHAR szExe[1000];
	_stprintf(szExe, _T("%s"), strProcess);
	if (!CreateProcess(NULL, szExe, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
	{
		return FALSE;	
	}
	CloseHandle(pi.hProcess );
	CloseHandle(pi.hThread );
	return TRUE;
}

/**********************************************************************
* 函数名称： CreateRunProcess
* 功能描述： 创建运行进程（处于等待状态）
* 输入参数： 
* <param name="strProcess"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::CreateWaitProcess(LPCTSTR strProcess)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	TCHAR szExe[1000];
	_stprintf(szExe, _T("%s"), strProcess);
	if (!CreateProcess(NULL, szExe, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
	{
		return FALSE;	
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	DWORD bSuccess;
	GetExitCodeProcess (pi.hProcess, &bSuccess);
	CloseHandle(pi.hProcess );
	CloseHandle(pi.hThread );
	return TRUE;
}

/**********************************************************************
* 函数名称： CreateBrowseUrl
* 功能描述： 打开浏览网页
* 输入参数： 
* <param name="strProcess"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::CreateBrowseUrl(LPCTSTR pszURL)
{
	if( _tcslen(pszURL) == 0)
	{
		return FALSE;
	}
	TCHAR szChar[MAX_PATH];
	::GetWindowsDirectory(szChar, MAX_PATH);
	_tcscpy(szChar + sizeof(_T("c:")), _T("\\Program Files\\Internet Explorer\\iexplore.exe "));
	_tcscat(szChar, pszURL);
	SHELLEXECUTEINFO ExecInfo;
	memset( &ExecInfo, 0, sizeof(ExecInfo));
	ExecInfo.lpVerb = _T("open");
	ExecInfo.fMask = SEE_MASK_DOENVSUBST;
	ExecInfo.lpParameters = pszURL;
	ExecInfo.nShow = SW_SHOWNORMAL;

	if ((DWORD)ShellExecute( NULL, _T("open"), pszURL, NULL, NULL,SW_SHOWNORMAL) <= 32)
	{
		CreateRunProcess(szChar);
	}
	return TRUE;
}

/**********************************************************************
* 函数名称： DeleteDirectory
* 功能描述： 删除制定目录
* 输入参数： 
* <param name="strDirectory"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::DeleteDirectory(const TCHAR * strDirectory)
{
	WIN32_FIND_DATA findData;
	BOOL bFindNext;
	TCHAR tempFileFind[1000];   
	TCHAR szFile[1000];   
	_stprintf(tempFileFind, _T("%s*.*"), strDirectory);
	HANDLE hFind = FindFirstFile(tempFileFind, &findData);   
	while (hFind != INVALID_HANDLE_VALUE)
	{
		bFindNext = FindNextFile(hFind, &findData);
		if (!bFindNext )
		{
			break;
		}
		if (findData.cFileName[0] == _T('.'))
		{
			continue;
		}
		if (findData.cFileName[1] == _T('\0'))
		{
			continue;
		}
		if (findData.cFileName[1] == _T('.') && findData.cFileName[2] == _T('\0'))
		{
			continue;
		}
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			TCHAR szChildDirectory[MAX_PATH] = {'\0'};
			_stprintf(szChildDirectory, _T("%s%s\\"), strDirectory, findData.cFileName);
			DeleteDirectory(szChildDirectory);
		}
		_stprintf(szFile, _T("%s%s"), strDirectory, findData.cFileName);
		::DeleteFile(szFile);
	}
	FindClose(hFind);
}

/**********************************************************************
* 函数名称： CreateDirectoryPath
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::CreateDirectoryPath(LPCTSTR strDirectoryPath)
{
	int nLen = (int)_tcslen(strDirectoryPath);
	TCHAR * szBuffer = new TCHAR[nLen + 1];
	_tcscpy(szBuffer, strDirectoryPath);
	bool bFlag = true;
	for (int pos = 0, start = 0 ; pos <= nLen ; pos++)
	{
		if ((szBuffer[pos] == _T('\\')))
		{
			TCHAR nSave = szBuffer[pos];
			szBuffer[pos] = 0;
			if (!PathFileExists(szBuffer))
			{
				if (!CreateDirectory(szBuffer, NULL))
				{
					bFlag = false;
					break;
				}
			}
			szBuffer[pos] = nSave;
			start = pos + 1;
		}
	}
	delete[] szBuffer;
	return bFlag;
}

/**********************************************************************
* 函数名称： SimplifiedToTraditional
* 功能描述： 简体转繁体中文
* 输入参数： 
* <param name="pszSimplified"></param>
* <param name="pszTraditional"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::SimplifiedToTraditional(const TCHAR * pszSimplified, TCHAR * pszTraditional)
{
	 if ((pszSimplified == NULL))
	{
        return;
	}
	int nTextLen = (int)_tcslen(pszSimplified);
	if (nTextLen == 0)
	{
		return;
	}
	DWORD dwLCID = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_CHINESE_PRC);
    int nReturn = LCMapString(dwLCID, LCMAP_TRADITIONAL_CHINESE, pszSimplified, nTextLen, NULL, 0);
    if (!nReturn)
	{
        return;
	}
    TCHAR * pszBuf = new TCHAR[nReturn + 1];
	memset(pszBuf, 0, nReturn + 1);
    __try
    {
        dwLCID = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_CHINESE_PRC);
        LCMapString(dwLCID, LCMAP_TRADITIONAL_CHINESE, pszSimplified, nReturn, pszBuf, nReturn + 1);
		_tcsncpy(pszTraditional, pszBuf, nReturn);
    }
    __finally
    {
        delete[] pszBuf;
    }
}

/**********************************************************************
* 函数名称： NumberToCapitalChineseNumber
* 功能描述： 数字转换为汉字数字
* 输入参数： 
* <param name="pszNumber"></param>
* <param name="pszReturn"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::NumberToCapitalChineseNumber(const TCHAR * pszNumber, TCHAR * pszReturn)
{
	TCHAR szValue[MAX_PATH] = {'\0'};
	int nTextLen = (int)_tcslen(pszNumber);
	for (int i = 0; i < nTextLen; i++)
	{
		_tcsncpy(szValue, pszNumber + i, 1);
		int nNum = _ttoi(szValue);
		_tcscat(pszReturn, pszChineseNumber[nNum]);
	}
}

/**********************************************************************
* 函数名称： NumberToCapitalLettersNumber
* 功能描述： 数字转换为大写数字
* 输入参数： 
* <param name="pszNumber"></param>
* <param name="pszReturn"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::NumberToCapitalLettersNumber(const TCHAR * pszNumber, TCHAR * pszReturn)
{
	TCHAR szValue[MAX_PATH] = {'\0'};
	int nTextLen = (int)_tcslen(pszNumber);
	for (int i = 0; i < nTextLen; i++)
	{
		_tcsncpy(szValue, pszNumber + i, 1);
		int nNum = _ttoi(szValue);
		_tcscat(pszReturn, pszCapitalNumber[nNum]);
	}
}

/**********************************************************************
* 函数名称： NumberToCapitalLettersMoney
* 功能描述： 数字转换为大写金额
* 输入参数： 
* <param name="dMoney"></param>
* <param name="pszReturn"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::NumberToCapitalLettersMoney(const TCHAR * pszNumber, TCHAR * pszReturn)
{
	TCHAR szMoney[MAX_PATH] = {'\0'};
	TCHAR szIntegerMoney[MAX_PATH] = {'\0'};
	TCHAR szDecimalMoney[MAX_PATH] = {'\0'};
	TCHAR szNum[MAX_PATH] = {'\0'};
	xstring strMoney = pszNumber;
	int nIndexOf = (int)strMoney.find('.');
	int nTextLen = 0;
	xstring strIntegerMoney = _T("");
	xstring strDecimalMoney = _T("");
	if (nIndexOf > -1)
	{
		_tcsncat(szIntegerMoney, pszNumber, nIndexOf);
	}
	else
	{
		_tcscat(szIntegerMoney, pszNumber);
	}
	int nNumber = 0;
	int nCount = 0;
	TCHAR szValue[MAX_PATH] = {'\0'};
	int nSection = 0;
	int nIntegerLen = (int)_tcslen(szIntegerMoney);
	BOOL bFrontZero = FALSE;
	BOOL bSectionFrontZero = FALSE;
	BOOL bFrontWanYi = FALSE;
	int nAddSectionNum = 0;
	for (int i = nIntegerLen - 1; i >= 0; i--)
	{
		_tcsncpy(szNum, szIntegerMoney + i, 1);
		nNumber = _ttoi(szNum);
		if (nCount % 4 == 0 && nCount > 0)
		{
			_tcscat(pszReturn, _T(""));
		}
		if (nCount == 0)
		{
			int nReturnLen = (int)_tcslen(pszReturn);
			if (nReturnLen == 0)
			{
				_stprintf(pszReturn, _T("%s"), _T("元"));
			}
			if (nNumber > 0)
			{
				bFrontZero = FALSE;
				bFrontWanYi = FALSE;
				_stprintf(szValue, _T("%s%s"), pszCapitalNumber[nNumber], pszReturn);
				_stprintf(pszReturn, _T("%s"), szValue);
			}
			else
			{
				bFrontZero = TRUE;
			}
		}
		else if (nCount == 1)
		{
			if (nNumber > 0)
			{
				bSectionFrontZero = FALSE;
				bFrontZero = FALSE;
				bFrontWanYi = FALSE;
				_stprintf(szValue, _T("%s拾%s"), pszCapitalNumber[nNumber], pszReturn);
				_stprintf(pszReturn, _T("%s"), szValue);
			}
			else
			{
				if (!bFrontWanYi)
				{
					if (!bFrontZero)
					{
						_stprintf(szValue, _T("%s%s"), pszCapitalNumber[nNumber], pszReturn);
						_stprintf(pszReturn, _T("%s"), szValue);
					}
				}
				bFrontZero = TRUE;
			}
		}
		else if (nCount == 2)
		{
			if (nNumber > 0)
			{
				bSectionFrontZero = FALSE;
				bFrontZero = FALSE;
				bFrontWanYi = FALSE;
				_stprintf(szValue, _T("%s佰%s"), pszCapitalNumber[nNumber], pszReturn);
				_stprintf(pszReturn, _T("%s"), szValue);
			}
			else
			{
				if (!bFrontWanYi)
				{
					if (!bFrontZero)
					{
						_stprintf(szValue, _T("%s%s"), pszCapitalNumber[nNumber], pszReturn);
						_stprintf(pszReturn, _T("%s"), szValue);
					}
				}
				bFrontZero = TRUE;
			}
		}
		else if (nCount == 3)
		{
			if (nNumber > 0)
			{
				bSectionFrontZero = FALSE;
				bFrontZero = FALSE;
				bFrontWanYi = FALSE;
				_stprintf(szValue, _T("%s仟%s"), pszCapitalNumber[nNumber], pszReturn);
				_stprintf(pszReturn, _T("%s"), szValue);
			}
			else
			{
				if (!bFrontWanYi)
				{
					if (!bFrontZero)
					{
						_stprintf(szValue, _T("%s%s"), pszCapitalNumber[nNumber], pszReturn);
						_stprintf(pszReturn, _T("%s"), szValue);
					}
				}
				bFrontZero = TRUE;
			}
		}
		else if (nCount == 4)
		{
			nAddSectionNum++;
			if (nNumber > 0)
			{
				if (bSectionFrontZero)
				{
					if (nAddSectionNum < 3)
					{
						TCHAR szTempValue[MAX_PATH] = {'\0'};
						_tcscpy(szTempValue, pszReturn + 1);
						_tcscpy(pszReturn, szTempValue);
					}
				}
				bSectionFrontZero = FALSE;
				bFrontZero = FALSE;
				if (nSection == 0)
				{
					_stprintf(szValue, _T("%s万%s"), pszCapitalNumber[nNumber], pszReturn);
					nSection++;
				}
				else
				{
					_stprintf(szValue, _T("%s亿%s"), pszCapitalNumber[nNumber], pszReturn);
					nSection = 0;
				}
				_stprintf(pszReturn, _T("%s"), szValue);
			}
			else
			{
				if (bSectionFrontZero)
				{
					if (nAddSectionNum < 3)
					{
						TCHAR szTempValue[MAX_PATH] = {'\0'};
						_tcscpy(szTempValue, pszReturn + 1);
						_tcscpy(pszReturn, szTempValue);
					}
				}
				bSectionFrontZero = TRUE;
				if (nSection == 0)
				{
					_stprintf(szValue, _T("万%s"), pszReturn);
					nSection++;
				}
				else
				{
					_stprintf(szValue, _T("亿%s"), pszReturn);
					nSection = 0;
				}
				_stprintf(pszReturn, _T("%s"), szValue);
			}
			bFrontWanYi = TRUE;
		}
		nCount++;
		if (nCount >= 5)
		{
			nCount = 1;
		}
	}
	if (nIndexOf == -1)
	{
		return;
	}
	if (_tcscmp(pszReturn, _T("元")) == 0) // 为此种情况（如：0.15）
	{
		_tcscpy(pszReturn, _T(""));
	}
	int nDecimalLen = (int)strMoney.length();
	if (nDecimalLen > nIndexOf + 1) // 获取角分
	{
		BOOL bExistDimeMoney = FALSE;
		_tcscat(szDecimalMoney, pszNumber + nIndexOf + 1);
		nTextLen = (int)_tcslen(szDecimalMoney);
		if (nTextLen > 0) // 存在角
		{
			_tcsncpy(szNum, szDecimalMoney, 1);
			nNumber = _ttoi(szNum);
			if (nNumber > 0)
			{
				bExistDimeMoney = TRUE;
				_stprintf(szValue, _T("%s%s角"), pszReturn, pszCapitalNumber[nNumber]);
				_stprintf(pszReturn, _T("%s"), szValue);
			}
		}
		if (nTextLen > 1) // 存在分
		{
			_tcsncpy(szNum, szDecimalMoney + 1, 1);
			nNumber = _ttoi(szNum);
			if (nNumber > 0)
			{
				if (bExistDimeMoney)
				{
					_stprintf(szValue, _T("%s%s分"), pszReturn, pszCapitalNumber[nNumber]);
				}
				else
				{
					_stprintf(szValue, _T("%s零%s分"), pszReturn, pszCapitalNumber[nNumber]);
				}
				_stprintf(pszReturn, _T("%s"), szValue);
			}
		}
	}
}

/**********************************************************************
* 函数名称： IsNumberAddH
* 功能描述： 是否符合数字+H模式（此模式输出汉字对应的数字）
* 输入参数： 
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsNumberAddH(const TCHAR * pszValue)
{
	int nTextLen = (int)_tcslen(pszValue);
	if (nTextLen <= 3)
	{
		return FALSE;
	}
	if (pszValue[nTextLen - 1] != 'h')
	{
		return FALSE;
	}
	TCHAR szReciprocalSecond = pszValue[nTextLen - 2];
	if ((szReciprocalSecond != '+') && (szReciprocalSecond < '0' || szReciprocalSecond > '9'))
	{
		return FALSE;
	}
	for (int i = 2; i < nTextLen - 2; i++)
	{
		if (i > 2)
		{
			if (pszValue[i] == '.')
			{
				continue;
			}
		}
		if (pszValue[i] < '0' ||  pszValue[i] > '9')
		{
			return FALSE;
		}
	}
	return TRUE;
}

/**********************************************************************
* 函数名称： IsNumberAddJ
* 功能描述： 是否符合数字+J模式（此模式输出大写金额）
* 输入参数： 
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsNumberAddJ(const TCHAR * pszValue)
{
	int nTextLen = (int)_tcslen(pszValue);
	if (nTextLen <= 3)
	{
		return FALSE;
	}
	if (pszValue[nTextLen - 1] != 'j')
	{
		return FALSE;
	}
	TCHAR szReciprocalSecond = pszValue[nTextLen - 2];
	if ((szReciprocalSecond != '+') && (szReciprocalSecond < '0' || szReciprocalSecond > '9'))
	{
		return FALSE;
	}
	for (int i = 2; i < nTextLen - 2; i++)
	{
		if (i > 2)
		{
			if (pszValue[i] == '.')
			{
				continue;
			}
		}
		if (pszValue[i] < '0' ||  pszValue[i] > '9')
		{
			return FALSE;
		}
	}
	return TRUE;
}

/**********************************************************************
* 函数名称： IsNumberAddD
* 功能描述： 是否符合数字+D模式（此模式输出大写数字）
* 输入参数： 
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsNumberAddD(const TCHAR * pszValue)
{
	int nTextLen = (int)_tcslen(pszValue);
	if (nTextLen <= 3)
	{
		return FALSE;
	}
	if (pszValue[nTextLen - 1] != 'd')
	{
		return FALSE;
	}
	TCHAR szReciprocalSecond = pszValue[nTextLen - 2];
	if ((szReciprocalSecond != '+') && (szReciprocalSecond < '0' || szReciprocalSecond > '9'))
	{
		return FALSE;
	}
	for (int i = 2; i < nTextLen - 2; i++)
	{
		if (pszValue[i] < '0' ||  pszValue[i] > '9')
		{
			return FALSE;
		}
	}
	return TRUE;
}

/**********************************************************************
* 函数名称： IsWWWBegin
* 功能描述： 是否以www开头输入模式
* 输入参数： 
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsWWWBegin(const TCHAR * pszValue)
{
	TCHAR szValue[50] = {'\0'};
	int nTextLen = (int)_tcslen(_T("www"));
	_tcsncat(szValue, pszValue, nTextLen);
	if (_tcscmp(szValue, _T("www")) == 0)
	{
		return TRUE;
	}
	return FALSE;
}

/**********************************************************************
* 函数名称： IsWWWInput
* 功能描述： 是否以www.开头输入模式
* 输入参数： 
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsWWWInput(const TCHAR * pszValue)
{
	TCHAR szValue[50] = {'\0'};
	TCHAR szMatch[50] = {'\0'};
	int nTextLen = (int)_tcslen(_T("www"));
	_tcsncat(szValue, pszValue, nTextLen + 1);
	_stprintf(szMatch, _T("%s."), _T("www"));
	if (_tcscmp(szValue, szMatch) == 0)
	{
		return TRUE;
	}
	return FALSE;
}

/**********************************************************************
* 函数名称： IsWebBegin
* 功能描述： 是否以ftp.、mail.开头输入模式
* 输入参数： 
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsWebBegin(const TCHAR * pszValue)
{
	for (int i = 0; i < 2; i++)
	{
		TCHAR szValue[50] = {'\0'};
		int nTextLen = (int)_tcslen(pszWebInputBegin[i]);
		_tcsncat(szValue, pszValue, nTextLen);
		if (_tcscmp(szValue, pszWebInputBegin[i]) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

/**********************************************************************
* 函数名称： IsWebInput
* 功能描述： 是否以www.开头输入模式
* 输入参数： 
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsWebInput(const TCHAR * pszValue)
{
	for (int i = 0; i < 2; i++)
	{
		TCHAR szValue[50] = {'\0'};
		TCHAR szMatch[50] = {'\0'};
		int nTextLen = (int)_tcslen(pszWebInputBegin[i]);
		_tcsncat(szValue, pszValue, nTextLen + 1);
		_stprintf(szMatch, _T("%s."), pszWebInputBegin[i]);
		if (_tcscmp(szValue, szMatch) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

/**********************************************************************
* 函数名称： IsFtpBegin
* 功能描述： 是否以ftp开头输入模式
* 输入参数： 
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsFtpBegin(const TCHAR * pszValue)
{
	TCHAR szValue[5] = {'\0'};
	_tcsncat(szValue, pszValue, 4);
	if (_tcscmp(szValue, _T("ftp")) == 0)
	{
		return TRUE;
	}
	return FALSE;
}

/**********************************************************************
* 函数名称： IsFtpInput
* 功能描述： 是否以ftp:开头输入模式
* 输入参数： 
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsFtpInput(const TCHAR * pszValue)
{
	TCHAR szValue[50] = {'\0'};
	_tcsncat(szValue, pszValue, 4);
	if (_tcscmp(szValue, _T("ftp:")) == 0)
	{
		return TRUE;
	}
	return FALSE;
}

/**********************************************************************
* 函数名称： IsHttpBegin
* 功能描述： 是否以http开头输入模式
* 输入参数： 
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsHttpBegin(const TCHAR * pszValue)
{
	TCHAR szValue[5] = {'\0'};
	_tcsncat(szValue, pszValue, 4);
	if (_tcscmp(szValue, _T("http")) == 0)
	{
		return TRUE;
	}
	return FALSE;
}

/**********************************************************************
* 函数名称： IsHttpInput
* 功能描述： 是否以http.开头输入模式
* 输入参数： 
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsHttpInput(const TCHAR * pszValue)
{
	TCHAR szValue[50] = {'\0'};
	_tcsncat(szValue, pszValue, 5);
	if (_tcscmp(szValue, _T("http:")) == 0)
	{
		return TRUE;
	}
	return FALSE;
}

/**********************************************************************
* 函数名称： IsMailInput
* 功能描述： 是否为@邮箱模式输入
* 输入参数： 
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsMailInput(const TCHAR * pszValue)
{
	int nTextLen = (int)_tcslen(pszValue);
	for (int i = 0; i < nTextLen; i++)
	{
		if (pszValue[i] == _T('@'))
		{
			return TRUE;
		}
	}
	return FALSE;
}

/**********************************************************************
* 函数名称： IsSimpleWbInputMode
* 功能描述： 判断是否是纯五笔输入模式
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/05/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsSimpleWbInputMode()
{
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(IS_USE_PY_MODE))
	{
		return FALSE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(EN_INPUT_MODE))
	{
		return FALSE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(KB_INPUT_MODE))
	{
		return FALSE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(BH_INPUT_MODE))
	{
		return FALSE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(IS_USE_WB_MODE))
	{
		return TRUE;
	}
	return FALSE;
}

/**********************************************************************
* 函数名称： IsSimplePyInputMode
* 功能描述： 判断是否是纯拼音输入模式
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/05/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsSimplePyInputMode()
{
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(IS_USE_WB_MODE))
	{
		return FALSE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(EN_INPUT_MODE))
	{
		return FALSE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(KB_INPUT_MODE))
	{
		return FALSE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(BH_INPUT_MODE))
	{
		return FALSE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(IS_USE_PY_MODE))
	{
		return TRUE;
	}
	return FALSE;
}

/**********************************************************************
* 函数名称： IsSimpleBhInputMode
* 功能描述： 判断是否是纯笔画输入模式
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/05/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsSimpleBhInputMode()
{
	/*if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(IS_USE_WB_MODE))
	{
		return FALSE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(IS_USE_PY_MODE))
	{
		return FALSE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(EN_INPUT_MODE))
	{
		return FALSE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(KB_INPUT_MODE))
	{
		return FALSE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(BH_INPUT_MODE))
	{
		return TRUE;
	}*/
	return FALSE;
}

/**********************************************************************
* 函数名称： IsContainPyInputMode
* 功能描述： 判断是否包含纯拼音输入模式
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/05/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsContainPyInputMode()
{
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(IS_USE_PY_MODE))
	{
		return TRUE;
	}
	return FALSE;
}


/**********************************************************************
* 函数名称： IsContainWbInputMode
* 功能描述： 判断是否包含五笔输入模式
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/05/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsContainWbInputMode()
{
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(IS_USE_WB_MODE))
	{
		return TRUE;
	}
	return FALSE;
}


/**********************************************************************
* 函数名称： IsBlendWbInputMode
* 功能描述： 判断是否是五笔混合输入模式
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/05/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsBlendWbInputMode()
{
	BOOL bOtherInputMode = FALSE;
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(IS_USE_PY_MODE))
	{
		bOtherInputMode = TRUE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(EN_INPUT_MODE))
	{
		bOtherInputMode = TRUE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(KB_INPUT_MODE))
	{
		bOtherInputMode = TRUE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(BH_INPUT_MODE))
	{
		bOtherInputMode = TRUE;
	}
	if (g_pGlobals->GetCommonVariable()->GetShareParameterValue(IS_USE_WB_MODE))
	{
		if (bOtherInputMode)
		{
			return TRUE;
		}
	}
	return FALSE;
}

/**********************************************************************
* 函数名称： GetClipboardDataLen
* 功能描述： 获取剪贴板内存长度
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/05/25		V1.0	    huanggenping	创建版本
***********************************************************************/
int CFunction::GetClipboardDataLen(HWND & hWnd)
{
	if (!IsClipboardFormatAvailable(CF_TEXT)) 
	{
		return 0;
	}
	HANDLE hGlobal;
	char * pszGlobal ;
	if (!OpenClipboard(hWnd))
	{
		return 0;
	}
	hGlobal = GetClipboardData(CF_TEXT);
	if (hGlobal == NULL)		
	{
		return  0;
	}
	pszGlobal = (LPSTR)GlobalLock(hGlobal);
	if (pszGlobal == NULL) 
	{
		return  0;
	}
	int nTextLen = (int)strlen(pszGlobal);
	GlobalUnlock(hGlobal);
	CloseClipboard();
	return nTextLen;
}

/**********************************************************************
* 函数名称： GetClipboardDataInfo
* 功能描述： 获取剪贴板数据信息
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/05/25		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::GetClipboardDataInfo(HWND & hWnd, char * pszClipboardData)
{
	if (!IsClipboardFormatAvailable(CF_TEXT)) 
	{
		return;
	}
	HANDLE hGlobal;
	char * pszGlobal ;
	if (!hWnd)
	{
		return;
	}
	if (!OpenClipboard(hWnd))
	{
		return;
	}
	hGlobal = GetClipboardData(CF_TEXT);
	if (hGlobal == NULL)		
	{
		return;
	}
	pszGlobal = (LPSTR)GlobalLock(hGlobal);
	if (pszGlobal == NULL) 
	{
		return;
	}
	strcpy(pszClipboardData, pszGlobal);
	GlobalUnlock(hGlobal);
//	EmptyClipboard();
	CloseClipboard();
}

/**********************************************************************
* 函数名称： IsOnlyHaveLowerCase
* 功能描述： 判断字符是否为26个小写字母
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/17		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsOnlyHaveLowerCase(const TCHAR * pszValue)
{
	int nTextLen = (int)_tcslen(pszValue);
	for (int i = 0; i < nTextLen; i++)
	{
		TCHAR szValue = pszValue[i];
		if (szValue < _T('a') || szValue > _T('z'))
		{
			return FALSE;
		}
	}
	return TRUE;
}

/**********************************************************************
* 函数名称： GetIsFullScreen
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/05/20		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::GetIsFullScreen(HWND hWnd)
{
	static BOOL bFrontFullScreen = FALSE;
	static BOOL bSetDesktop = FALSE;
	static INT nDesktopLeft = 0;
	static INT nDesktopTop = 0;
	static INT nDesktopRight = 0;
	static INT nDesktopBottom = 0;
	const TCHAR * pszRunProcessName = g_pGlobals->GetConfigure()->GetRunProcessName();
	if(_tcscmp(pszRunProcessName, _T("explorer.exe")) == 0)
	{
		return FALSE;
	}
	if (hWnd == NULL)
	{
		if (bFrontFullScreen)
		{
			return TRUE;
		}
		return FALSE;
	}
	HWND hTopWnd = hWnd;
	RECT clientRect, rectDesktop;
	while (GetParent(hTopWnd))
	{
		hTopWnd = GetParent(hTopWnd);
	}
	GetWindowRect(hTopWnd, &clientRect);
	TCHAR szValue[MAX_PATH] = {'\0'};
	BOOL bUnusualDesktop = FALSE;
	if (!bSetDesktop)
	{
		::GetWindowRect(::GetDesktopWindow(), &rectDesktop);
		nDesktopLeft = rectDesktop.left;
		nDesktopTop = rectDesktop.top;
		nDesktopRight = rectDesktop.right;
		nDesktopBottom = rectDesktop.bottom;
	}
	else
	{
		::GetWindowRect(::GetDesktopWindow(), &rectDesktop);
		INT nIntervalWidth = rectDesktop.right - rectDesktop.left;
		INT nIntervalHeight = rectDesktop.bottom - rectDesktop.top;
		if (nIntervalWidth < 0 || nIntervalHeight < 0)
		{
			bUnusualDesktop = TRUE;
		}
		if (nIntervalWidth > 10000 || nIntervalHeight > 10000)
		{
			bUnusualDesktop = TRUE;
		}
		if (bUnusualDesktop)
		{
			rectDesktop.left = nDesktopLeft;
			rectDesktop.top = nDesktopTop;
			rectDesktop.right = nDesktopRight;
			rectDesktop.bottom = nDesktopBottom;
		}
	}
	/*_stprintf
		(
		szValue
		, _T("bUnusualDesktop:%d(hWnd:%x)(hTopWnd:%x)|%d:%d|%d:%d|%d:%d|%d:%d|")
		, bUnusualDesktop
		, hWnd
		, hTopWnd
		, clientRect.left
		, rectDesktop.left
		, clientRect.top
		, rectDesktop.top
		, clientRect.right
		, rectDesktop.right
		, clientRect.bottom
		, rectDesktop.bottom
		);*/
	if (
		(clientRect.left == rectDesktop.left) 
		&& (clientRect.right == rectDesktop.right) 
		&& (clientRect.top == rectDesktop.top) 
		&& (clientRect.bottom == rectDesktop.bottom)
		)
	{
		bFrontFullScreen = TRUE;
		return TRUE;
	}
	int nCXScreen = GetSystemMetrics(SM_CXSCREEN);
	int nCYScreen = GetSystemMetrics(SM_CYSCREEN);
	if (
		(nCXScreen == clientRect.right)
		&& (nCYScreen == clientRect.bottom)
		)
	{
		bFrontFullScreen = TRUE;
		return TRUE;
	}
	if (
		(clientRect.left == 0) 
		&& (clientRect.top == 0)
		&& (clientRect.right == 0)
		&& (clientRect.bottom == 0)
		)
	{
		bFrontFullScreen = TRUE;
		return TRUE;
	}
	bFrontFullScreen = FALSE;
	return FALSE; 
}

/**********************************************************************
* 函数名称： GetRandom
* 功能描述： 
* 输入参数： 
* <param name="nMin"></param>
* <param name="nMax"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/23		V1.0	    huanggenping	创建版本
***********************************************************************/
int CFunction::GetRandom(int nMin, int nMax)   
{   
	if (nMin >= nMax)   
	{
		return nMin;   
	} 
	srand((unsigned)time(NULL));
	return nMin + rand() % (nMax - nMin + 1);   
}

/**********************************************************************
* 函数名称： SetEncrypt
* 功能描述： 
* 输入参数： 
* <param name="strOrgEncrypt"></param>
* <param name="strResultEncrypt"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/23		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::SetEncrypt(const TCHAR * strOrgEncrypt, TCHAR * strResultEncrypt)
{
	TCHAR szSingleNum[10] = {'\0'};
	TCHAR szTempNum[100] = {'\0'};
	int nOrgLen = 0;
	int nTextLen = 0;
	nTextLen = (int)_tcslen(strOrgEncrypt);
	nOrgLen = nTextLen;
	int nSumResidue = 0;
	int nAllSum = 0;
	int nSinguleNum = 0;
	TCHAR tchnSumResidue = '0';
	TCHAR tchSingleNum = '0';
	TCHAR tchSingleSum = '0';
	TCHAR tchXorResult = '0';
	TCHAR tchXorSource = _T('A');
	for (int i = 0; i < nTextLen; i++)
	{
		tchSingleNum = strOrgEncrypt[i];
		_tcsncpy(szSingleNum, strOrgEncrypt + i, 1);
		nSinguleNum = _ttoi(szSingleNum);
		nAllSum += nSinguleNum;
		tchXorResult = tchSingleNum ^ tchXorSource;
		strResultEncrypt[i] = tchXorResult;
		tchXorSource++;
	}
	nSumResidue = nAllSum % 10;
	_stprintf(szTempNum, _T("%d"), nSumResidue);
	tchnSumResidue = szTempNum[0];
	tchXorResult = tchnSumResidue ^ tchXorSource;
	strResultEncrypt[nOrgLen] = tchXorResult;
}

/**********************************************************************
* 函数名称： GetDecrypt
* 功能描述： 
* 输入参数： 
* <param name="strOrgDecrypt"></param>
* <param name="strResultDecrypt"></param>
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/23		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::GetDecrypt(const TCHAR * strOrgDecrypt, TCHAR * strResultDecrypt)
{
	int nTextLen = 0;
	nTextLen = (int)_tcslen(strOrgDecrypt);
	TCHAR tchXorSource = _T('A');
	TCHAR tchXorResult = '0';
	TCHAR tchSingleNum = '0';
	for (int i = 0; i < nTextLen; i++)
	{
		tchSingleNum = strOrgDecrypt[i];
		tchXorResult = tchSingleNum ^ tchXorSource;
		strResultDecrypt[i] = tchXorResult;
		tchXorSource++;
	}
}

/**********************************************************************
* 函数名称： GetChineseDate
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/23		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::GetChineseDate(TCHAR * strResultDate1, TCHAR * strResultDate2, TCHAR * strResultDate3)
{
	SYSTEMTIME mySystemTime;
	GetLocalTime(&mySystemTime);
	//
	_stprintf(strResultDate1, _T("%.4d年%d月%d日"), mySystemTime.wYear, mySystemTime.wMonth, mySystemTime.wDay);
	//
	_stprintf(strResultDate2, _T("%.4d-%d-%d"), mySystemTime.wYear, mySystemTime.wMonth, mySystemTime.wDay);
	//
	int nValue = mySystemTime.wYear;
	TCHAR szValue[20] = {'\0'};
	int nResidue = nValue / 1000;
	_tcscat(szValue, pszChineseNumber[nResidue]);
	nValue = nValue - nResidue * 1000;
	//
	nResidue = nValue / 100;
	_tcscat(szValue, pszChineseNumber[nResidue]);
	nValue = nValue - nResidue * 100;
	//
	nResidue = nValue / 10;
	_tcscat(szValue, pszChineseNumber[nResidue]);
	nValue = nValue - nResidue * 10;
	//
	nResidue = nValue;
	_tcscat(szValue, pszChineseNumber[nResidue]);
	//
	_tcscpy(strResultDate3, szValue);
	_tcscat(strResultDate3, _T("年"));
	//
	nValue = mySystemTime.wMonth;
	if (nValue <= 10)
	{
		_tcscat(strResultDate3, pszChineseNumber[nValue]);
	}
	else
	{
		nValue = nValue - 10;
		_tcscat(strResultDate3, pszChineseNumber[10]);
		_tcscat(strResultDate3, pszChineseNumber[nValue]);
	}
	_tcscat(strResultDate3, _T("月"));
	//
	nValue = mySystemTime.wDay;
	if (nValue <= 10)
	{
		_tcscat(strResultDate3, pszChineseNumber[nValue]);
	}
	else
	{
		nResidue = nValue / 10;
		if (nResidue > 1)
		{
			_tcscat(strResultDate3, pszChineseNumber[nResidue]);
		}
		_tcscat(strResultDate3, pszChineseNumber[10]);
		nValue = nValue - 10 * nResidue;
		if (nValue > 0)
		{
			_tcscat(strResultDate3, pszChineseNumber[nValue]);
		}
	}
	_tcscat(strResultDate3, _T("日"));
}

/**********************************************************************
* 函数名称： GetChineseTime
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/23		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::GetChineseTime(TCHAR * strResultTime1, TCHAR * strResultTime2, TCHAR * strResultTime3)
{
	SYSTEMTIME mySystemTime;
	GetLocalTime(&mySystemTime);
	//
	_stprintf(strResultTime1, _T("%.4d年%d月%d日%d时%d分%d秒"), mySystemTime.wYear, mySystemTime.wMonth, mySystemTime.wDay, mySystemTime.wHour, mySystemTime.wMinute, mySystemTime.wSecond);
	//
	_stprintf(strResultTime2, _T("%.4d-%d-%d %d:%d:%d"), mySystemTime.wYear, mySystemTime.wMonth, mySystemTime.wDay, mySystemTime.wHour, mySystemTime.wMinute, mySystemTime.wSecond);
	//
	int nValue = mySystemTime.wYear;
	TCHAR szValue[20] = {'\0'};
	int nResidue = nValue / 1000;
	_tcscat(szValue, pszChineseNumber[nResidue]);
	nValue = nValue - nResidue * 1000;
	//
	nResidue = nValue / 100;
	_tcscat(szValue, pszChineseNumber[nResidue]);
	nValue = nValue - nResidue * 100;
	//
	nResidue = nValue / 10;
	_tcscat(szValue, pszChineseNumber[nResidue]);
	nValue = nValue - nResidue * 10;
	//
	nResidue = nValue;
	_tcscat(szValue, pszChineseNumber[nResidue]);
	//
	_tcscpy(strResultTime3, szValue);
	_tcscat(strResultTime3, _T("年"));
	//
	nValue = mySystemTime.wMonth;
	if (nValue <= 10)
	{
		_tcscat(strResultTime3, pszChineseNumber[nValue]);
	}
	else
	{
		nValue = nValue - 10;
		_tcscat(strResultTime3, pszChineseNumber[10]);
		_tcscat(strResultTime3, pszChineseNumber[nValue]);
	}
	_tcscat(strResultTime3, _T("月"));
	//
	nValue = mySystemTime.wDay;
	if (nValue <= 10)
	{
		_tcscat(strResultTime3, pszChineseNumber[nValue]);
	}
	else
	{
		nResidue = nValue / 10;
		if (nResidue > 1)
		{
			_tcscat(strResultTime3, pszChineseNumber[nResidue]);
		}
		_tcscat(strResultTime3, pszChineseNumber[10]);
		nValue = nValue - 10 * nResidue;
		if (nValue > 0)
		{
			_tcscat(strResultTime3, pszChineseNumber[nValue]);
		}
	}
	_tcscat(strResultTime3, _T("日"));
	//
	nValue = mySystemTime.wHour;
	if (nValue <= 10)
	{
		_tcscat(strResultTime3, pszChineseNumber[nValue]);
	}
	else
	{
		nResidue = nValue / 10;
		if (nResidue > 1)
		{
			_tcscat(strResultTime3, pszChineseNumber[nResidue]);
		}
		_tcscat(strResultTime3, pszChineseNumber[10]);
		nValue = nValue - 10 * nResidue;
		if (nValue > 0)
		{
			_tcscat(strResultTime3, pszChineseNumber[nValue]);
		}
	}
	_tcscat(strResultTime3, _T("点"));
	//
	nValue = mySystemTime.wMinute;
	if (nValue <= 10)
	{
		_tcscat(strResultTime3, pszChineseNumber[nValue]);
	}
	else
	{
		nResidue = nValue / 10;
		if (nResidue > 1)
		{
			_tcscat(strResultTime3, pszChineseNumber[nResidue]);
		}
		_tcscat(strResultTime3, pszChineseNumber[10]);
		nValue = nValue - 10 * nResidue;
		if (nValue > 0)
		{
			_tcscat(strResultTime3, pszChineseNumber[nValue]);
		}
	}
	_tcscat(strResultTime3, _T("分"));
	//
	nValue = mySystemTime.wSecond;
	if (nValue <= 10)
	{
		_tcscat(strResultTime3, pszChineseNumber[nValue]);
	}
	else
	{
		nResidue = nValue / 10;
		if (nResidue > 1)
		{
			_tcscat(strResultTime3, pszChineseNumber[nResidue]);
		}
		_tcscat(strResultTime3, pszChineseNumber[10]);
		nValue = nValue - 10 * nResidue;
		if (nValue > 0)
		{
			_tcscat(strResultTime3, pszChineseNumber[nValue]);
		}
	}
	_tcscat(strResultTime3, _T("秒"));
}

/**********************************************************************
* 函数名称： IsContainIdentifier
* 功能描述：
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/25		V1.0	    huanggenping	创建版本
***********************************************************************/
BOOL CFunction::IsContainIdentifier(const TCHAR * pszFileName)
{
	if (!::PathFileExists(pszFileName))
	{
		return FALSE;
	}
	INT  nSize = 0;
	HANDLE hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		nSize = ::GetFileSize((HANDLE)hFile, NULL);
	}
	char * lpszBuffer = new char[nSize + 1];
	DWORD dwRead = 0;
	ReadFile(hFile, lpszBuffer, nSize + 1, &dwRead, NULL);
	CloseHandle(hFile);
	char szIdentifier[MAX_PATH] = "identifierBegin:abcdefghijklmnopqrstuvwxyz:identifierEnd";
	int nIdentifierLen = strlen(szIdentifier);
	int nBegin = 0;
	int nSameNum = 0;
	BOOL bFind = FALSE;
	for (int i = 0; i < nSize; i++)
	{
		if (lpszBuffer[i] == szIdentifier[0])
		{
			if (bFind)
			{
				break;
			}
			nBegin = i;
			nSameNum = 0;
			for (int j = 0; j < nIdentifierLen; j++)
			{
				if (lpszBuffer[nBegin + j] == szIdentifier[j])
				{
					nSameNum++;
					if (nSameNum == nIdentifierLen)
					{
						delete lpszBuffer;
						lpszBuffer = NULL;
						return TRUE;
					}
				}
				else
				{
					nBegin = 0;
					break;
				}
			}
		}
	}
	delete lpszBuffer;
	lpszBuffer = NULL;
	return FALSE;
}

/**********************************************************************
* 函数名称： WriteDebugLog
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2009/03/17		V1.0	    huanggenping	创建版本
***********************************************************************/
void CFunction::WriteDebugLog(TCHAR * strMsg, ...)
{
#ifndef _DEBUG
	return;
#endif
	TCHAR szTempPath[MAX_PATH] = {'\0'};
	GetTempPath(MAX_PATH, szTempPath);
	int nMsgMaxLen = 500;
	FILE * pFile;
	TCHAR szMsg[500] = {'\0'};
	TCHAR szLogFile[MAX_PATH];
	_stprintf(szLogFile, _T("%s\\log.txt"), szTempPath);
	va_list         list;               // 可变参数指针
	// 格式化组合字串
	va_start(list, strMsg);
	_vsntprintf(szMsg, nMsgMaxLen - 1, strMsg, list);
	szMsg[nMsgMaxLen - 1] = 0;
	BOOL bFind = FALSE;
	if (PathFileExists(szLogFile))
	{
		bFind = TRUE;
	}
	if ((pFile = _tfopen(szLogFile, _T("a+b"))) != NULL)
	{
		if (!bFind)
		{
			WORD wUnicode = 0xFEFF;
			fwrite(&wUnicode, 1, 2, pFile);
		}
		int nTextLen = (int)_tcslen(szMsg);
		fwrite(szMsg, 1, nTextLen * 2, pFile);
		WORD wLine = 0x000D;
		fwrite(&wLine, 1, 2, pFile);
		wLine = 0x000A;
		fwrite(&wLine, 1, 2, pFile);
		fclose(pFile);
	}
}

//获取exe路径
LPCTSTR CFunction::GetExePath()
{
	return m_szExePath;
}

/// @}