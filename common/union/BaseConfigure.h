#pragma once
typedef wstring xstring;

class CBaseConfigure
{
protected:

	// 是否发现配置目录
	BYTE m_byFindCfgRootPath;
	// 是否发现配置目录
	BYTE m_byFindCfgUserPath;
	// 配置用户目录
	xstring m_strCfgUserPath;
	// 配置的根目录
	xstring m_strCfgRootPath;
	// 配置文件路径
	xstring m_strConfigFile;
	// 软件安装目录
	xstring m_strInstallRootPath;
	// 软件安装目录
	xstring m_strInstallPath;
	// 保存统计相关文件
	xstring m_strUseVestigeFile;

public:
	
	CBaseConfigure(void);
	~CBaseConfigure(void);

public:

	// 初始化
	BOOL Init(void);
	// 初始化配置的跟路径
	void InitCfgRootPath(void);
	// 初始化配置的跟路径
	void InitCfgUserPath(void);
	// 初始化软件配置目录
	void InitSoftCfgRootPath(void);
	// 初始化软件的用户目录
	void InitSoftCfgUserPath(void);
	// 初始化配置文件
	void InitConfigFile(void);
	// 初始化保存使用痕迹配置相关文件
	void InitUseVestigeFile(void);
	// 初始化安装路径
	void InitInstallPath(void);
	// 获取安装路径
	const TCHAR * GetInstallPath(void);
	// 获取安装根路径
	const TCHAR * GetInstallRootPath(void);
	// 获取保存配置跟路径
	const TCHAR * GetCfgRootPath(void);
	// 获取保存配置跟路径
	const TCHAR * GetCfgUserPath(void);
	// 获取配置文件
	const TCHAR * GetConfigFile(void);
	// 获取保存统计相关文件
	const TCHAR * GetUseVestigeFile(void);
	// 获取运行程序名字
	const TCHAR * GetRunProcessName(void);
	// 确认是否是Vista版的操作系统
	BOOL IsVistaOrWin7System();
	// 获取AppData路径
	void GetApplicationDataCfgRootPath();
	// 获取AppData路径
	void GetApplicationDataCfgUserPath();
	// 写入配置文件路径到注册表
	void WriteConfigPathToRegedit(void);
	// 写入配置文件路径到SoftApp.ini
	void WriteConfigPathToSoftAppIni(void);
};
