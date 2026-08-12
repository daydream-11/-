
#ifndef __COMMON_UTIL_H__
#define __COMMON_UTIL_H__

class CommonUtil
{
public:
	// 获取全屏宽度
	static INT GetFullScreenWidth(void);
	// 获取全屏高度
	static INT GetFullScreenHeight(void);
	// 获取可以使用屏幕宽度
	static INT GetUseScreenWidth(void);
	// 获取可以使用屏幕高度
	static INT GetUseScreenHeight(void);
	// 创建目录
	static BOOL CreateDirectoryPath(LPCTSTR strDirectoryPath);
	// TCHAR字符串指针转换为char字符串指针
	static void TCHARToCHAR(const TCHAR * pszTCHAR, char * pszCHAR);
	// TCHAR字符串指针转换为WCHAR字符串指针
	static void TCHARToWCHAR(const TCHAR * pszTCHAR, WCHAR * pszWCHAR);
	// char字符串指针转换为TCHAR字符串指针
	static void CHARToTCHAR(const char * pszCHAR, TCHAR * pszTCHAR);
	// Unicode字符串指针转换为UTF-8字符串指针
	static void UnicodeToUTF8(const TCHAR * pszTCHAR, char * pszCHAR, INT & nSize);
	// UTF8字符串指针转换为TCHAR字符串指针
	static void UTF8ToTCHAR(const char * pszCHAR, TCHAR * pszTCHAR);
	// 繁体到big5
	static void TCHARToBIG5(const TCHAR * pszTCHAR, TCHAR * pszBIG5);
	// TCHAR转换为UTF-8
	static void TCHARToUTF8(const TCHAR * pszTCHAR, char * pszCHAR);
	// 做为解Url使用   
	static char CharToInt(char ch);
	// 做为解Url使用
	static char StrToBin(char *str);
	// 把url GB2312解码   
	static string UrlGB2312Decode(string str);
	// 把Url utf8解码   
	static string UrlUTF8Decode(string str);
	//UTF_8 转gb2312   
	static void UTF_8ToGB2312(string &pOut, char *pText, int pLen);
	// Unicode 转为 GB2312
	static void UnicodeToConveyGB2312(char* pOut,WCHAR uData);
	// GB2312 转为 Unicode
	static void GB2312ToConveyUnicode(WCHAR * pReturnUnicode,char * strGB2312Value);
	// Unicode 转为 UTF8
	static void UnicodeToConveyUTF8(char * strReturnUTF8, WCHAR * strInputUnicode);
	// UTF8 转为 Unicode
	static void UTF8ToConveyUnicode(WCHAR* pOut,char *pText);
	// GB2312 转为 UTF-8
 	static void GB2312ToConveyUTF8(string & strOutput, char * strGB2312Value, int nGB2312ValueLen);
	// char转GB2312网址
	static string CharToConveyGB2312Url(char * strOriginal);
	// char转UTF-8网址
	static string CharToConveyUTF8URL(char * strOriginal);
	// Url转换Char
	static void UrlToConveyChar(const char * strUrlSource, char * strUrlDest);
	// Url转换结果
	static void UrlToCoverResult(const char * strUrlSource, char * strUrlResult);
	// 判断是否GB2312编码
	static int IsGB2312Code(const string & str);
	// 获取随机数(包含两数)
	static INT GetRand(INT nMin, INT nMax);
	// 获得今天的日期如：20120921
	static UINT GetCurrentDay();
	// 获得昨天的日期如：20120920
	static UINT GetYesterDay();
	// 获取时间 20120921
	static UINT GetMyDate(UINT uTime);
	// 获得时间
	static UINT GetMyTime(UINT uTime);
	// 获得指定时间的日期
	static VOID GetAppointDay_YY(UINT uTime, TCHAR *szMyTime);
	// 获得指定时间的时间
	static VOID GetAppointDay_Time(UINT uTime, TCHAR *szMyTime);
	// 获得指定时间的日期获取Unix时间戳
	static UINT GetUnixOfTime(const TCHAR *szMyTime);
	// 获取年份
	static UINT GetYear();
	// 获取年份(年(2位)01、02)
	static UINT GetYear_YY();
	// 获取月份
	static UINT GetMonth();
	// 获取日
	static UINT GetDay();
	// 获取时
	static UINT GetHour();
	// 获取分
	static UINT GetMinute();
	// 获取秒
	static UINT GetSecond();
	// 获取星期
	static UINT GetWeekday();
	// 获得今日过了0点多少秒 
	static UINT GetTodayAfterSecond();
	// 获取x的n次幂
	static INT GetXPowerN(INT nX, INT nN);
	// 打开浏览网页
	static VOID CreateBrowseUrlByUser(LPCTSTR pszURL);
	// 打开浏览网页通过IE
	static VOID CreateBrowseUrlByIE(LPCTSTR pszURL);
	// 打开浏览网页通过默认浏览器
	static VOID CreateBrowseUrlByDefault(LPCTSTR pszURL);
	// 打开网页
	static VOID CreateBrowseUrl(LPCTSTR pszURL);
	// 判断默认浏览器是否存在
	static BOOL IsDefaultBrowseExist();
	// 判断是否遨游浏览器为默认的
	static BOOL IsMaxthonDefaultBrowse();
	//
	static BOOL IsAppointDefaultBrowse(const TCHAR *lpszBrowseName);
	// 判断是否没有问题的浏览器为默认的
	static BOOL IsNoQuestionDefaultBrowse();
	// 获取IE安装的位置
	static BOOL GetIExplorerExePath(TCHAR *lpszIExplorerExe);
	// 打开进程
	static VOID CreateUIProcess(LPCTSTR strProcess);
	// 打开进程
	static VOID CreateRunProcess(LPCTSTR strProcess);
	// 打开进程
	static bool CreateRunProcessRes(LPCTSTR strProcess);
	// 创建运行进程（处于等待状态）
	static VOID CreateWaitProcess(LPCTSTR strProcess);
	// 创建按用户的进程
	static VOID CreateUserProcess(TCHAR *lpszProcess);
	// 创建管理员进程
	static BOOL CreateAdminProcess(LPCTSTR strProcess, LPCTSTR strParameter);
	// 获取进程ID
	static INT GetProcessIDOfName(TCHAR *lpszProcessName);
	// 获取进程个数
	static INT GetProcessNumOfName(TCHAR *lpszProcessName);
	// 获取进程相关的Token
	static HANDLE GetTokenOfProcessID(DWORD dwProcessID);
	// 获取进程相关的Token
	static HANDLE GetTokenOfName(TCHAR *lpszProcessName);
	// 从字符串中获取文件后缀名
	static VOID GetFileNameOfFileFullPath(const TCHAR *lpszFileFullPath, TCHAR *lpszFileName);
	// 从字符串中获取文件的名字
	static VOID GetFileNameOnlyName(TCHAR *lpszFileName, TCHAR *lpszOnlyName);
	// 从字符串中获取文件后缀名
	static VOID GetFileNameExtension(TCHAR *lpszFileName, TCHAR *lpszExtension);
	// 从字符串中获取文件名
	static VOID GetFileNameFromHttpString(const TCHAR *lpszString, TCHAR *lpszFileName);
	// 获取Json格式的其实位置
	static char* GetJsonStartPosition(char *pszResult);
	// 移动文件
	static void MoveFileOfReName(const TCHAR * lpszExistingFileName, const TCHAR * lpNewFileName, bool bDeleteOrg);
	// 复制新文件
	static void CopyFileOfNewFile(const TCHAR * lpszExistingFileName, const TCHAR * lpNewFileName);
	// 重命名文件，重启后删除
	static void ReNameOfReRebootDelete(TCHAR * lpszExistingFileName);
	// 删除文件（当前删除不了，移动当临时目录，重启后删除）
	static void DeleteFileOfRemoveTempRebotDelete(const TCHAR * lpszExistingFileName);
	// 获取错误信息
	static xstring GetErrorMessage();
	// 创建注册表运行一次程序
	static BOOL CreateRegeditRunOnce(const TCHAR *lpszRunOneName, const TCHAR *lpszRunOneExe);
	// 拷贝文件到临时目录
	static VOID CopyFileToTempPath();
	//
	static void WriteDebugLog(TCHAR * strMsg, ...);
	// string 装换为xstring
	static xstring StrToXStr(const string & str);
	// xstring 装换为string
	static string XStrToStr(const xstring& xstr);
	// 一个单引号变两个单引号
	static BOOL QuotesOneToTwo(xstring& xstr);
#ifdef _UNICODE
	static BOOL QuotesOneToTwo(string& xstr);
#endif
	// 去掉单引号
	static void DeleteQuotes(xstring& xstr);
	// 文件中是否包含标示符
	static BOOL IsContainIdentifier(const TCHAR * pszFileName);
    static tm ConvertFormatStringToTime(const WCHAR* timeStr);
	// 是否含有字符a-z
	static BOOL IsContainAToZ(const xstring& strWord);
	// 检测进程中某个程序的数量
	static int GetProcessCount(const TCHAR* szExeName);
	// 是否仅仅小写26个字母
	static BOOL IsOnlyHaveLowerCase(const TCHAR * pszValue);
	// 确认是否是Vista版的操作系统
	static BOOL IsVistaOrWin7System();
	// 是否含有某个字符
	static BOOL IsContainChar(const xstring& strWord, const TCHAR ch);
	// 重新设置剪贴板信息
	static BOOL SetClipboardDataInfo(HWND hWnd, const TCHAR * strClipboardData);
	// 重新设置剪贴板信息
	static BOOL SetClipboardDataCharInfo(HWND hWnd, const CHAR * strClipboardData);
	// 重新获取剪贴板信息
	static BOOL GetClipboardDataCharInfo(HWND hWnd, TCHAR * strClipboardData);
};
// 
#endif // __COMMON_UTIL_H__
