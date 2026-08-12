#include "stdafx.h"
#include "BaseConfigure.h"
#include <tlhelp32.h>
#include <shlobj.h>
#include "CommonUtil.h"

CBaseConfigure::CBaseConfigure(void)
{
	m_byFindCfgRootPath = 0;
	m_byFindCfgUserPath = 0;
	// 配置的根目录
	m_strCfgRootPath = _T("");
	// 配置用户目录
	m_strCfgUserPath = _T("");
	// 软件安装目录
	m_strInstallRootPath = _T("");
	// 软件安装目录
	m_strInstallPath = _T("");
	// 配置文件
	m_strConfigFile = _T("");
	// 保存统计相关文件
	m_strUseVestigeFile = _T("");
}

CBaseConfigure::~CBaseConfigure(void)
{
	
}

// 初始化
BOOL CBaseConfigure::Init(void)
{
	InitSoftCfgRootPath();
	InitSoftCfgUserPath();
	if (!m_byFindCfgRootPath)
	{
		InitCfgRootPath();
	}
	if (!m_byFindCfgUserPath)
	{
		InitCfgUserPath();
	}
	InitInstallPath();
	InitConfigFile();
	InitUseVestigeFile();
	WriteConfigPathToSoftAppIni();
	return TRUE;
}

// 初始化配置的跟路径
void CBaseConfigure::InitCfgRootPath(void)
{
	BOOL bFindVistaOrWin7 = FALSE;
	BOOL bFindLocal = FALSE;
	BOOL bFindLocalLow = FALSE;
	BOOL bFindRoaming = FALSE;
	TCHAR szSpecialFolderPath[MAX_PATH] = {'\0'};
	TCHAR szLocalPath[MAX_PATH] = {'\0'};
	TCHAR szLocalLowPath[MAX_PATH] = {'\0'};
	TCHAR szRoamingPath[MAX_PATH] = {'\0'};
	TCHAR szAppDataPath[MAX_PATH] = {'\0'};
	TCHAR szCfgRootPath[MAX_PATH] = {'\0'};
	// 是否IE保护模式
	BOOL bIEProtect = FALSE;
	int nTextLen = 0;
	// 备注：在IE保护模式下，获取临时目录为\Local\Temp\Low\，而非保护模式下获取临时目录为\Local\Temp\/
	SHGetSpecialFolderPath(NULL, szSpecialFolderPath, CSIDL_APPDATA, 0);
	_tcscpy(szAppDataPath, szSpecialFolderPath);
	nTextLen = (int)_tcslen(szAppDataPath);
	TCHAR * pszFindAppDataPath = NULL;
	pszFindAppDataPath = _tcsrchr(szAppDataPath, '\\');
	if (pszFindAppDataPath == NULL)
	{
		GetApplicationDataCfgRootPath();
		return;
	}
	*(pszFindAppDataPath) = '\0';
	//
	_tcscpy(szLocalPath, szAppDataPath);
	_tcscat(szLocalPath, _T("\\Local"));
	if (PathFileExists(szLocalPath))
	{
		bFindLocal = TRUE;
	}
	//
	_tcscpy(szLocalLowPath, szAppDataPath);
	_tcscat(szLocalLowPath, _T("\\LocalLow"));
	if (PathFileExists(szLocalLowPath))
	{
		bFindLocalLow = TRUE;
	}
	//
	_tcscpy(szRoamingPath, szAppDataPath);
	_tcscat(szRoamingPath, _T("\\Roaming"));
	if (PathFileExists(szRoamingPath))
	{
		bFindRoaming = TRUE;
	}
	if (bFindLocal && bFindLocalLow && bFindRoaming)
	{
		if (IsVistaOrWin7System())
		{
			bFindVistaOrWin7 = TRUE;
		}
	}
	if (bFindVistaOrWin7)
	{
		_stprintf(szCfgRootPath, _T("%s\\%s\\"), szLocalLowPath, SOFT_CFG_PATH);
		if (!PathFileExists(szCfgRootPath))
		{
			CommonUtil::CreateDirectoryPath(szCfgRootPath);
		}
		m_strCfgRootPath = szCfgRootPath;
	}
	else
	{
		GetApplicationDataCfgRootPath();
	}
}


// 初始化配置的跟路径
void CBaseConfigure::InitCfgUserPath(void)
{
	BOOL bFindVistaOrWin7 = FALSE;
	BOOL bFindLocal = FALSE;
	BOOL bFindLocalLow = FALSE;
	BOOL bFindRoaming = FALSE;
	TCHAR szSpecialFolderPath[MAX_PATH] = {'\0'};
	TCHAR szLocalPath[MAX_PATH] = {'\0'};
	TCHAR szLocalLowPath[MAX_PATH] = {'\0'};
	TCHAR szRoamingPath[MAX_PATH] = {'\0'};
	TCHAR szAppDataPath[MAX_PATH] = {'\0'};
	TCHAR szCfgUserPath[MAX_PATH] = {'\0'};
	// 是否IE保护模式
	BOOL bIEProtect = FALSE;
	int nTextLen = 0;
	// 备注：在IE保护模式下，获取临时目录为\Local\Temp\Low\，而非保护模式下获取临时目录为\Local\Temp\/
	SHGetSpecialFolderPath(NULL, szSpecialFolderPath, CSIDL_APPDATA, 0);
	_tcscpy(szAppDataPath, szSpecialFolderPath);
	nTextLen = (int)_tcslen(szAppDataPath);
	TCHAR * pszFindAppDataPath = NULL;
	pszFindAppDataPath = _tcsrchr(szAppDataPath, '\\');
	if (pszFindAppDataPath == NULL)
	{
		GetApplicationDataCfgUserPath();
		return;
	}
	*(pszFindAppDataPath) = '\0';
	//
	_tcscpy(szLocalPath, szAppDataPath);
	_tcscat(szLocalPath, _T("\\Local"));
	if (PathFileExists(szLocalPath))
	{
		bFindLocal = TRUE;
	}
	//
	_tcscpy(szLocalLowPath, szAppDataPath);
	_tcscat(szLocalLowPath, _T("\\LocalLow"));
	if (PathFileExists(szLocalLowPath))
	{
		bFindLocalLow = TRUE;
	}
	//
	_tcscpy(szRoamingPath, szAppDataPath);
	_tcscat(szRoamingPath, _T("\\Roaming"));
	if (PathFileExists(szRoamingPath))
	{
		bFindRoaming = TRUE;
	}
	if (bFindLocal && bFindLocalLow && bFindRoaming)
	{
		if (IsVistaOrWin7System())
		{
			bFindVistaOrWin7 = TRUE;
		}
	}
	if (bFindVistaOrWin7)
	{
		_stprintf(szCfgUserPath, _T("%s\\%s\\"), szLocalLowPath, SOFT_USER_PATH);
		if (!PathFileExists(szCfgUserPath))
		{
			CommonUtil::CreateDirectoryPath(szCfgUserPath);
		}
		m_strCfgUserPath = szCfgUserPath;
	}
	else
	{
		GetApplicationDataCfgUserPath();
	}
}


// 初始化软件配置目录
void CBaseConfigure::InitSoftCfgRootPath()
{
	TCHAR szCommonFiles[MAX_PATH] = {'\0'};
	TCHAR szCfgRootPath[MAX_PATH] = {'\0'};
	//
#ifdef _WIN64
	SHGetSpecialFolderPath(NULL, szCommonFiles, CSIDL_PROGRAM_FILES_COMMONX86, FALSE);
#else
	SHGetSpecialFolderPath(NULL, szCommonFiles, CSIDL_PROGRAM_FILES_COMMON, FALSE);
#endif
	_tcscat(szCommonFiles, _T("\\"));
	_tcscat(szCommonFiles, SOFT_FILE_PATH);
	_tcscat(szCommonFiles, _T("\\"));
	_tcscat(szCommonFiles, SOFT_FILE_NAME);
	_tcscat(szCommonFiles, _T(".ini"));
	GetPrivateProfileString(_T("Globals"), _T("CfgRootPath"), _T(""), szCfgRootPath, MAX_PATH, szCommonFiles);
	//
	if (PathFileExists(szCfgRootPath))
	{
		m_strCfgRootPath = szCfgRootPath;
		m_byFindCfgRootPath = TRUE;
		return;
	}
	// 获取注册表中软件安装位置
	TCHAR szRegKey[MAX_PATH] = {'\0'};
	_tcscpy(szRegKey, _T("SOFTWARE\\"));
	_tcscat(szRegKey, SOFT_FILE_PATH);
	HKEY hKey;
	long lReturn = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, szRegKey, 0, KEY_ALL_ACCESS, &hKey);
	if (lReturn == ERROR_SUCCESS)
	{
		DWORD dwSize = MAX_PATH;
		lReturn = RegQueryValueEx(hKey, _T("CfgRootPath"), 0, NULL, (LPBYTE)szCfgRootPath, &dwSize);
		if (lReturn == ERROR_SUCCESS)
		{
			//
			if (PathFileExists(szCfgRootPath))
			{
				RegCloseKey(hKey);
				m_strCfgRootPath = szCfgRootPath;
				m_byFindCfgRootPath = TRUE;
				return;
			}
		}
	}
	RegCloseKey(hKey);
	TCHAR szModuleName[MAX_PATH];
	GetModuleFileName(NULL, szModuleName, MAX_PATH);
	*(_tcsrchr(szModuleName, '\\') + 1) = '\0';

	TCHAR szSoftAppIni[MAX_PATH] = {'\0'};
	_stprintf(szSoftAppIni, _T("%sSoftApp.ini"), szModuleName);
	GetPrivateProfileString(_T("AppInfo"), _T("CfgRootPath"), _T(""), szCfgRootPath, MAX_PATH, szSoftAppIni);
	//
	if (PathFileExists(szCfgRootPath))
	{
		m_strCfgRootPath = szCfgRootPath;
		m_byFindCfgRootPath = TRUE;
		return;
	}
	m_byFindCfgRootPath = FALSE;
}

// 初始化软件的用户目录
void CBaseConfigure::InitSoftCfgUserPath()
{
	TCHAR szCommonFiles[MAX_PATH] = {'\0'};
	TCHAR szCfgUserPath[MAX_PATH] = {'\0'};
	//
#ifdef _WIN64
	SHGetSpecialFolderPath(NULL, szCommonFiles, CSIDL_PROGRAM_FILES_COMMONX86, FALSE);
#else
	SHGetSpecialFolderPath(NULL, szCommonFiles, CSIDL_PROGRAM_FILES_COMMON, FALSE);
#endif
	_tcscat(szCommonFiles, _T("\\"));
	_tcscat(szCommonFiles, SOFT_FILE_PATH);
	_tcscat(szCommonFiles, _T("\\"));
	_tcscat(szCommonFiles, SOFT_FILE_NAME);
	_tcscat(szCommonFiles, _T(".ini"));
	GetPrivateProfileString(_T("Globals"), _T("CfgUserPath"), _T(""), szCfgUserPath, MAX_PATH, szCommonFiles);
	//
	if (PathFileExists(szCfgUserPath))
	{
		m_strCfgUserPath = szCfgUserPath;
		m_byFindCfgUserPath = TRUE;
		return;
	}
	// 获取注册表中软件安装位置
	TCHAR szRegKey[MAX_PATH] = {'\0'};
	_tcscpy(szRegKey, _T("SOFTWARE\\"));
	_tcscat(szRegKey, SOFT_FILE_PATH);
	HKEY hKey;
	long lReturn = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, szRegKey, 0, KEY_ALL_ACCESS, &hKey);
	if (lReturn == ERROR_SUCCESS)
	{
		DWORD dwSize = MAX_PATH;
		lReturn = RegQueryValueEx(hKey, _T("CfgUserPath"), 0, NULL, (LPBYTE)szCfgUserPath, &dwSize);
		if (lReturn == ERROR_SUCCESS)
		{
			//
			if (PathFileExists(szCfgUserPath))
			{
				RegCloseKey(hKey);
				m_strCfgUserPath = szCfgUserPath;
				m_byFindCfgUserPath = TRUE;
				return;
			}
		}
	}
	RegCloseKey(hKey);
	TCHAR szModuleName[MAX_PATH];
	GetModuleFileName(NULL, szModuleName, MAX_PATH);
	*(_tcsrchr(szModuleName, '\\') + 1) = '\0';

	TCHAR szSoftAppIni[MAX_PATH] = {'\0'};
	_stprintf(szSoftAppIni, _T("%sSoftApp.ini"), szModuleName);
	GetPrivateProfileString(_T("AppInfo"), _T("CfgUserPath"), _T(""), szCfgUserPath, MAX_PATH, szSoftAppIni);
	//
	if (PathFileExists(szCfgUserPath))
	{
		m_strCfgUserPath = szCfgUserPath;
		m_byFindCfgUserPath = TRUE;
		return;
	}
	m_byFindCfgUserPath = FALSE;
}

// 初始化配置文件
void CBaseConfigure::InitConfigFile(void)
{
	TCHAR szConfigFile[MAX_PATH];
	_stprintf(szConfigFile, _T("%s%s\\"), m_strCfgRootPath.c_str(), CONFIG_PATH);
	if (!PathFileExists(szConfigFile))
	{
		CommonUtil::CreateDirectoryPath(szConfigFile);
	}
	_tcscat(szConfigFile, CONFIG_FILE);
	m_strConfigFile = szConfigFile;
}


// 初始化保存使用痕迹配置相关文件
void CBaseConfigure::InitUseVestigeFile(void)
{
	TCHAR szUseVestigeFile[MAX_PATH];
	_stprintf(szUseVestigeFile, _T("%s%s\\%s"), m_strCfgRootPath.c_str(), CONFIG_PATH, USEVESTIGE_FILE);
	m_strUseVestigeFile = szUseVestigeFile;
}


// 初始化安装路径
void CBaseConfigure::InitInstallPath()
{
	TCHAR szModuleName[MAX_PATH] = {'\0'};
	GetModuleFileName(NULL, szModuleName, MAX_PATH);
	*(_tcsrchr(szModuleName, '\\') + 1) = '\0';

	//TCHAR szFullPath[MAX_PATH] = {'\0'};
	//GetModuleFileName(NULL, szFullPath, MAX_PATH);

	m_strInstallPath = szModuleName;
}


// 获取安装路径
const TCHAR * CBaseConfigure::GetInstallPath()
{
	return m_strInstallPath.c_str();
}

// 获取安装根路径
const TCHAR * CBaseConfigure::GetInstallRootPath(void)
{
	return m_strInstallRootPath.c_str();
}
// 获取保存配置跟路径
const TCHAR * CBaseConfigure::GetCfgRootPath(void)
{
	return m_strCfgRootPath.c_str();
}

// 获取保存配置跟路径
const TCHAR * CBaseConfigure::GetCfgUserPath(void)
{
	return m_strCfgUserPath.c_str();
}


// 获取配置文件
const TCHAR * CBaseConfigure::GetConfigFile(void)
{
	return m_strConfigFile.c_str();
}

// 获取保存统计相关文件
const TCHAR * CBaseConfigure::GetUseVestigeFile(void)
{
	return m_strUseVestigeFile.c_str();
}

// 确认是否是Vista版的操作系统
BOOL CBaseConfigure::IsVistaOrWin7System()
{
	OSVERSIONINFOEX myOsVersionInfoEx;
	ZeroMemory(&myOsVersionInfoEx,sizeof(myOsVersionInfoEx));
    myOsVersionInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO*)&myOsVersionInfoEx);
	if (myOsVersionInfoEx.dwMajorVersion == 6)
	{
		if (myOsVersionInfoEx.dwMinorVersion == 0 || myOsVersionInfoEx.dwMinorVersion == 1)
		{
			if (myOsVersionInfoEx.wProductType == VER_NT_WORKSTATION )
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

// 获取AppData路径
void CBaseConfigure::GetApplicationDataCfgRootPath()
{
	TCHAR szCfgRootPath[MAX_PATH];
	SHGetSpecialFolderPath(NULL, szCfgRootPath, CSIDL_APPDATA, 0);
	INT nTextLen = (INT)_tcslen(szCfgRootPath);
	if (nTextLen == 0)
	{
		return;
	}
	_tcscat(szCfgRootPath, _T("\\"));

	_tcscat(szCfgRootPath, SOFT_CFG_PATH);
	_tcscat(szCfgRootPath, _T("\\"));
	//
	if (!PathFileExists(szCfgRootPath))
	{
		CommonUtil::CreateDirectoryPath(szCfgRootPath);
	}
	m_strCfgRootPath = szCfgRootPath;
}

// 获取AppData路径
void CBaseConfigure::GetApplicationDataCfgUserPath()
{
	TCHAR szCfgUserPath[MAX_PATH];
	SHGetSpecialFolderPath(NULL, szCfgUserPath, CSIDL_APPDATA, 0);
	INT nTextLen = (INT)_tcslen(szCfgUserPath);
	if (nTextLen == 0)
	{
		return;
	}
	_tcscat(szCfgUserPath, _T("\\"));
	_tcscat(szCfgUserPath, SOFT_USER_PATH);
	_tcscat(szCfgUserPath, _T("\\"));
	//
	if (!PathFileExists(szCfgUserPath))
	{
		CommonUtil::CreateDirectoryPath(szCfgUserPath);
	}
	m_strCfgUserPath = szCfgUserPath;
}

// 写入配置文件路径到注册表
void CBaseConfigure::WriteConfigPathToRegedit(void)
{
	TCHAR szCfgRootPath[MAX_PATH];
	TCHAR szCfgUserPath[MAX_PATH];
	// 获取注册表中软件安装位置
	TCHAR szRegKey[MAX_PATH] = {'\0'};
	_tcscpy(szRegKey, _T("SOFTWARE\\"));
	_tcscat(szRegKey, SOFT_FILE_PATH);
	_tcscpy(szCfgRootPath, m_strCfgRootPath.c_str());
	_tcscpy(szCfgUserPath, m_strCfgUserPath.c_str());
	HKEY hKey;
	long lReturn = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, szRegKey, 0, KEY_SET_VALUE, &hKey);
	if (lReturn == ERROR_SUCCESS)
	{
		RegSetValueEx(hKey, _T("CfgRootPath"), 0, REG_SZ, (LPBYTE)szCfgRootPath, MAX_PATH);
		RegSetValueEx(hKey, _T("CfgUserPath"), 0, REG_SZ, (LPBYTE)szCfgUserPath, MAX_PATH);
	}
	RegCloseKey(hKey);
}

// 写入配置文件路径到SoftApp.ini
void CBaseConfigure::WriteConfigPathToSoftAppIni(void)
{
	TCHAR szSoftAppIni[MAX_PATH] = {'\0'};
	_stprintf(szSoftAppIni, _T("%sSoftApp.ini"), m_strInstallPath.c_str());
	WritePrivateProfileString(_T("AppInfo"), _T("CfgRootPath"), m_strCfgRootPath.c_str(), szSoftAppIni);
	WritePrivateProfileString(_T("AppInfo"), _T("CfgUserPath"), m_strCfgUserPath.c_str(), szSoftAppIni);
}
