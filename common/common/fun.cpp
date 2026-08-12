#include "pch.h"
#include "fun.h"
#include "HKey.h"

#include "conio.h"  //系统头文件
#include <Iphlpapi.h>
#include <ShlObj.h>
//#include <atlbase.h>
#include <ShellApi.h>
#pragma comment(lib,"Iphlpapi.lib")
#pragma comment(lib,"ws2_32.lib")
#include <psapi.h>
#pragma comment(lib,"psapi.lib")

#include <Tlhelp32.h>
#include <algorithm>

std::string mem_get_str(const char *arr, size_t size)
{
	if (arr == NULL || size <= 0)
	{
		return "";
	}

	//屏蔽'\0'后面的字符
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] == '\0')
		{
			size = i;
		}
	}

	return std::string().append(arr, size);
}

void mem_set_str(char *addr, size_t addrSize, const std::string &v)
{
	size_t len = v.length();

	if (len > addrSize)
	{
		len = addrSize;
	}

	memcpy(addr, v.c_str(), len);
}

std::string fs_get_exe_path()
{
	std::string fullname = fs_get_exe_fullname();
	fullname = fullname.substr(0, fullname.rfind('\\'));

	return fullname;
}

std::string fs_get_exe_filename()
{
	std::string fullname = fs_get_exe_fullname();
	std::string filename = fullname.substr(fullname.rfind('\\') + 1);

	return filename;
}

std::string fs_get_exe_fullname()
{
	char exe[MAX_PATH] = {0};

	GetModuleFileNameA(NULL, exe, sizeof(exe));

	return exe;
}

std::string fs_path_strip_path(const std::string &f)
{
	std::string s = f;
	PathStripPathA((char *)s.c_str());

	return s.c_str();
}

void fs_delete_file(const std::string &filename)
{
	if (!::DeleteFileA(filename.c_str()))
	{
		std::string delFile = filename + "." + num2str(int(GetTickCount()));
		rename(filename.c_str(), delFile.c_str());
		::MoveFileExA(delFile.c_str(), NULL, MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
	}
}

std::string fs_get_special_folder_path(int csidl)
{
	char path[MAX_PATH] = {0};

	SHGetSpecialFolderPathA(NULL, path, csidl, false);

	return path;
}

std::string fs_get_tmp_filename(const char *prefix)
{
	char path[MAX_PATH] = {0};
	GetTempFileNameA(fs_get_tmp_path().c_str(), prefix, 0, path);

	return path;
}

std::string fs_get_tmp_path()
{
	char path[MAX_PATH] = {0};

	int res = GetTempPathA(MAX_PATH, path);

	return path;
}

//void fs_find(std::list<std::string> &lts, const std::string &path, const char *filter)
//{
//	CFileFind finder;
//	BOOL res = finder.FindFile( CString((path+filter).c_str()) );	
//
//	while (res)
//	{
//		res = finder.FindNextFile();
//
//		if (finder.IsDots())
//		{
//			continue;
//		}
//
//		if (!finder.IsDirectory())
//		{
//			CStringA fileName(finder.GetFileName());
//
//			if (!fileName.IsEmpty())
//			{
//				lts.push_back(path+"\\"+fileName.GetBuffer());
//			}
//		}
//	}
//}
//
//void fs_find_recursion(std::list<std::string> &lts, const std::string &path, const char *filter)
//{
//	CFileFind finder;
//	BOOL res = finder.FindFile( CString((path+"\\*.*").c_str()) );	
//
//	fs_find(lts, path, filter);
//
//	while (res)
//	{
//		res = finder.FindNextFile();
//
//		if (finder.IsDots())
//		{
//			continue;
//		}
//
//		if (finder.IsDirectory())
//		{
//			CStringA fileName(finder.GetFileName());
//			fs_find_recursion(lts, path+"\\"+fileName.GetBuffer(), filter);
//		}
//	}
//}

std::string string_makeupper(const std::string &s)
{
	std::string str = s;
	std::transform(str.begin(), str.end(), str.begin(), toupper);
	return str;
}

bool process_id(const std::string &filename, std::list<int> &ids)
{
	PROCESSENTRY32 proEntry32 = {'\0'};

	HANDLE processSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (processSnap == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	proEntry32.dwSize = sizeof(PROCESSENTRY32); 

	if (Process32First(processSnap, &proEntry32)) 
	{  
		do 
		{
			std::string fn = unicode2gbk(proEntry32.szExeFile);

			if (!lstrcmpiA(fn.c_str(), filename.c_str())) //string_makeupper(fn) == string_makeupper(filename))
			{
				ids.push_back(proEntry32.th32ProcessID);
			}
		} 
		while (Process32Next(processSnap, &proEntry32)); 
	}

	CloseHandle (processSnap);

	return true;
}
//
////进程有关
//unsigned int process_id(const std::string &filename)
//{ 
//#if 0
//	DWORD aProcesses[1024] = {0};
//	DWORD cbNeeded = 0;
//	DWORD cProcesses = 0;
//
//	if (EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
//	{
//		cProcesses = cbNeeded / sizeof(DWORD);
//
//		for (int i = 0; i<cProcesses; i++)
//		{
//			if (aProcesses[i] == 0)
//			{
//				continue;;
//			}
//
//			std::string fn = process_filename(aProcesses[i]);
//
//			if (stricmp(fn.c_str(), filename.c_str()) == 0)
//			{
//				return aProcesses[i];
//			}
//		}
//	}
//
//	return 0;
//#else
//	HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//	DWORD id = 0;
//
//	if (hSnapshot != INVALID_HANDLE_VALUE)
//	{
//		PROCESSENTRY32 pe;
//		ZeroMemory(&pe, sizeof(pe));
//		pe.dwSize=sizeof(PROCESSENTRY32);
//
//		if (Process32First(hSnapshot,&pe))
//		{
//			CStringW fn(filename.c_str());
//			do 
//			{
//				if (fn.CompareNoCase(pe.szExeFile) == 0)
//				{
//					id = pe.th32ProcessID;
//					break;
//				}
//			}while (Process32Next(hSnapshot, &pe));
//		}
//
//		CloseHandle(hSnapshot);
//	}
//	
//	return id;
//#endif
//}

//
//unsigned int net_ip_str2net(const std::string &ip)
//{
//	return inet_addr(ip.c_str());
//}
//
//unsigned int net_ip_str2host(const std::string &ip)
//{
//	return net_ip_net2host(net_ip_str2net(ip));
//}
//
//std::string net_ip_net2str(unsigned int ip)
//{
//	in_addr v;
//	v.S_un.S_addr = ip;
//	return std::string(inet_ntoa(v));
//}
//
//std::string net_ip_host2str(unsigned int ip)
//{
//	return net_ip_net2str(net_ip_net2host(ip));
//}
//
//unsigned int net_ip_host2net(unsigned int ip)
//{
//	return htonl(ip);
//}
//
//unsigned int net_ip_net2host(unsigned int ip)
//{
//	return ntohl(ip);
//}
//
//int net_socket_name(unsigned int sock, int &port, std::string &ip)
//{
//	struct sockaddr_in addr = {0};
//	int addrLen = sizeof(addr);
//
//	int res = getsockname(sock, (struct sockaddr *)&addr, &addrLen);
//
//	ip = inet_ntoa(addr.sin_addr);
//	port = ntohs(addr.sin_port);
//
//	return res;
//}
//
//int net_peer_name(unsigned int sock, int &port, std::string &ip)
//{
//	struct sockaddr_in addr = {0};
//	int addrLen = sizeof(addr);
//
//	int res = getpeername(sock, (struct sockaddr *)&addr, &addrLen);
//
//	ip = inet_ntoa(addr.sin_addr);
//	port = ntohs(addr.sin_port);
//
//	return res;
//}

std::string num2str(int v)
{
	char buf[33] = {0};

	sprintf_s(buf, "%d", v);

	return buf;
}

std::string num2str(unsigned int v)
{
	char buf[33] = {0};

	sprintf_s(buf, "%u", v);

	return buf;
}

std::string num2str(long long v)
{
	char buf[65] = {0};

	sprintf_s(buf, "%I64d", v);

	return buf;
}

std::string num2str(float v)
{
	char buf[33] = {0};

	sprintf_s(buf, "%f", v);

	return buf;
}

static char toChar(unsigned char v)
{
	char a[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F'};

	return a[v];
}

std::string binary2Hex(const char *data, int len, const char *space)
{
	std::string str;

	for (int i = 0; i < len; i++)
	{
		char v[] = {toChar( (data[i] >> 4 & 0x0F) ), toChar(data[i] & 0x0F), '\0'};

		str.append(v);

		if (space != NULL)
		{
			str.append(space);
		}
	}

	return str;
}

std::string utf82gbk(const char *utf8)
{
#if 1
	std::string str;

	if (utf8 != NULL)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);  
		std::wstring strW;

		strW.resize(len);

		MultiByteToWideChar(CP_UTF8, 0, utf8, -1, (LPWSTR)strW.data(), len);  

		len = WideCharToMultiByte(936, 0, strW.data(), len-1, NULL, 0, NULL, NULL);		//len-1:去除最后一个0

		str.resize(len);

		WideCharToMultiByte(936,0, strW.data(), -1, (LPSTR)str.data(), len, NULL, NULL);  
	}

	return str;
#else
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);  
	LPWSTR wszGBK = new WCHAR[len + 1];  

	memset(wszGBK, 0, len * 2 + 2);  
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wszGBK, len);  

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);  
	char *szGBK = new char[len + 1];  
	memset(szGBK, 0, len + 1);  
	WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGBK, len, NULL, NULL);  
	//utf8 = szGBK;  

	std::string str(szGBK); 

	delete[]szGBK;  
	delete[]wszGBK;  

	return str;
#endif
}

std::string gbk2utf8(const char *gbk)
{
	std::string str;

	if (gbk != NULL)
	{
		int len = MultiByteToWideChar(936, 0, gbk, -1, NULL, 0);  
		std::wstring strW;

		strW.resize(len);

		MultiByteToWideChar(936, 0, gbk, -1, (LPWSTR)strW.data(), len);  

		len = WideCharToMultiByte(CP_UTF8, 0, strW.data(), len-1, NULL, 0, NULL, NULL);		//len-1:去除最后一个0

		str.resize(len);

		WideCharToMultiByte(CP_UTF8,0, strW.data(), -1, (LPSTR)str.data(), len, NULL, NULL);  
	}

	return str;
}

std::string unicode2gbk(const wchar_t *unicode)
{
	std::string str;

	if (unicode != NULL)
	{
		int len = WideCharToMultiByte(936, 0, unicode, -1, NULL, 0, NULL, NULL)-1;  
		str.resize(len);

		len = WideCharToMultiByte(936, 0, unicode, -1, (LPSTR)str.data(), len, NULL, NULL);  
	}

	return str;
}

std::wstring utf8_to_unicode(const char *utf8)
{
	if (utf8 != NULL)
	{
		size_t utf8Len = strlen(utf8);
		int nChar = MultiByteToWideChar(CP_UTF8, 0, utf8, utf8Len, NULL, 0);
		std::wstring res;

		nChar = MultiByteToWideChar(CP_UTF8, 0, utf8, utf8Len, (wchar_t*)res.assign(nChar+1, 0).c_str(), nChar);

		if(nChar != 0)
		{
			return res.c_str();
		}
	}

	return L"";
}

std::string unicode_to_utf8(const wchar_t *unicode)
{
	if (unicode != NULL)
	{
		size_t unicodeLen = wcslen(unicode);
		int len = WideCharToMultiByte(CP_UTF8, 0, unicode, unicodeLen, NULL, 0, NULL, NULL);  
		std::string res;

		len = WideCharToMultiByte(CP_UTF8, 0, unicode, unicodeLen, (char *)res.assign(len+1, 0).c_str(), len, NULL, NULL);

		if(len != 0)
		{
			return res.c_str();
		}
	}

	return "";
}

std::string w2a(const wchar_t *s)
{
	std::string str;

	if (s != NULL)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, s, -1, NULL, 0, NULL, NULL)-1;

		if (len > 0)
		{//测试数据: s=神界 len=4
			str.reserve(len+1);
			str.resize(len); 
			len = WideCharToMultiByte(CP_ACP, 0, s, -1, (LPSTR)str.data(), len, NULL, NULL); 
		}
	}

	return str.c_str();
}

std::wstring a2w(const char *s)
{
	std::wstring str;

	if (s != NULL)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, s, -1, NULL, 0); 

		if (len > 0)
		{//测试数据: s=神界 len=3
			str.reserve(len);
			str.resize(len-1); 
			MultiByteToWideChar(CP_ACP, 0, s, -1, (LPWSTR)str.data(), len); 
		}
	}

	return str.c_str();
}

bool reg_key_is_exist(const char* keyName)
{
	AutoHKey hKey1;

	if(RegOpenKeyA(HKEY_LOCAL_MACHINE, keyName, &hKey1) != ERROR_SUCCESS)
	{ 
		return false;
	}

	int res = RegQueryValueA(hKey1, NULL, NULL, 0);

	return res == ERROR_SUCCESS;
}

bool is_wang_ba()
{
	//bool e0 = reg_key_is_exist("SOFTWARE\\Hintsoft");
	//bool e1 = reg_key_is_exist("SOFTWARE\\Sicent");
	//bool e2 = reg_key_is_exist("SOFTWARE\\Goyoo");
	//bool e3 = reg_key_is_exist("SOFTWARE\\杭州顺网信息技术有限公司");

	//return e0 || e1 || e2 || e3;

	std::list<std::string> wangbaFiles;
	wangbaFiles.emplace_back("ikeeper");
	wangbaFiles.emplace_back("DbntCli");
	wangbaFiles.emplace_back("呼叫网管");
	wangbaFiles.emplace_back("BarClientView");
	wangbaFiles.emplace_back("lock");
	wangbaFiles.emplace_back("BarMonitor");
	wangbaFiles.emplace_back("DF5Serv");
	wangbaFiles.emplace_back("PBSClient");
	wangbaFiles.emplace_back("Clsmn");
	wangbaFiles.emplace_back("knbclient");
	wangbaFiles.emplace_back("cgmmenu");
	wangbaFiles.emplace_back("nmenu_client");
	wangbaFiles.emplace_back("nmenu");
	wangbaFiles.emplace_back("JKNBMS");
	wangbaFiles.emplace_back("wtcasapi32");
	wangbaFiles.emplace_back("netbarclient");
	wangbaFiles.emplace_back("净网先锋");
	wangbaFiles.emplace_back("mainpro");
	wangbaFiles.emplace_back("rzxclient");
	wangbaFiles.emplace_back("barclient");
	wangbaFiles.emplace_back("NBS_Client");
	wangbaFiles.emplace_back("iv3client");
	wangbaFiles.emplace_back("CoobarClt");
	wangbaFiles.emplace_back("lh_client");
	wangbaFiles.emplace_back("ClientSerivce");
	wangbaFiles.emplace_back("JKNBMS");
	wangbaFiles.emplace_back("nbms");
	wangbaFiles.emplace_back("CulClientViev");
	wangbaFiles.emplace_back("PCultBarclt");
	wangbaFiles.emplace_back("Cyber");

	for (const auto& file : wangbaFiles)
	{
		std::string sWangbaFile = file;
		sWangbaFile += ".";
		sWangbaFile += "e";
		sWangbaFile += "x";
		sWangbaFile += "e";
		std::list<int> ids;

		if (process_id(sWangbaFile, ids) && ids.size() > 0)
		{
			return true;
		}
	}

	return false;
}

int  mem_use_percent()
{
	MEMORYSTATUSEX memStatus;	
	memStatus.dwLength=sizeof(MEMORYSTATUSEX);
	::GlobalMemoryStatusEx(&memStatus);

	return  (int)memStatus.dwMemoryLoad;
}

//int cpu_use_percent()
//{
//	HANDLE hEvent;
//	BOOL res ;
//
//	FILETIME preidleTime;
//	FILETIME prekernelTime;
//	FILETIME preuserTime;
//
//	FILETIME idleTime;
//	FILETIME kernelTime;
//	FILETIME userTime;
//
//	res = GetSystemTimes( &idleTime, &kernelTime, &userTime );
//	preidleTime = idleTime;
//	prekernelTime = kernelTime;
//	preuserTime = userTime ;
//
//	// 初始值为 nonsignaled ，并且每次触发后自动设置为nonsignaled
//	hEvent = CreateEvent (NULL,FALSE,FALSE,NULL); 
//
//	WaitForSingleObject( hEvent,1000 ); //等待500毫秒
//	res = GetSystemTimes( &idleTime, &kernelTime, &userTime );
//
//	int idle = CompareFileTime( &preidleTime,&idleTime);
//	int kernel = CompareFileTime( &prekernelTime, &kernelTime);
//	int user = CompareFileTime(&preuserTime, &userTime);
//
//	return (kernel +user - idle) *100/(kernel+user);
//}
double FileTimeToDouble(FILETIME &filetime)
{
	return (double)(filetime.dwHighDateTime * 4.294967296E9) + (double)filetime.dwLowDateTime;
}
//
//int cpu_use_percent()
//{
//	static double prevCPUIdleTime = 0;
//	static double prevCPUKernelTime = 0;
//	static double prevCPUUserTime = 0;
//
//	FILETIME ftIdle;
//	FILETIME ftKernel;
//	FILETIME ftUser;
//
//	if (!GetSystemTimes(&ftIdle, &ftKernel, &ftUser))
//	{
//		return 0;
//	}
//
//	double curCPUIdleTime  = FileTimeToDouble(ftIdle);
//	double curCPUKernelTime = FileTimeToDouble(ftKernel);
//	double curCPUUserTime = FileTimeToDouble(ftUser);
//
//	double total = curCPUKernelTime-prevCPUKernelTime+curCPUUserTime-prevCPUUserTime+0.0000001;	//防止出现0
//	int use = 100-(curCPUIdleTime-prevCPUIdleTime)/total*100;
//
//	prevCPUIdleTime = curCPUIdleTime;
//	prevCPUKernelTime = curCPUKernelTime;
//	prevCPUUserTime = curCPUUserTime;
//
//	return use;
//}

std::string time_cur_data_time()
{
	char buf[40]={0};
	SYSTEMTIME st;

	GetLocalTime(&st);

	sprintf_s(buf, "%04d/%02d/%02d %02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	return buf;
}

std::string time_cur_data()
{
	char buf[20]={0};
	SYSTEMTIME st;

	GetLocalTime(&st);

	sprintf_s(buf, "%04d/%02d/%02d", st.wYear, st.wMonth, st.wDay);

	return buf;
}

std::string time_cur_time()
{
	char buf[20]={0};
	SYSTEMTIME st;

	GetLocalTime(&st);

	sprintf_s(buf, "%02d:%02d:%02d.%03d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	return buf;
}

long long filetime2timestamp(const FILETIME &fm)
{
	ULARGE_INTEGER ull = { 0 };

	ull.LowPart = fm.dwLowDateTime;
	ull.HighPart = fm.dwHighDateTime;

	return (ull.QuadPart - 116444736000000000ULL) / 10000000ULL;
}

time_t systemtime2timet(const SYSTEMTIME& st)
{
	struct tm gm = {st.wSecond, st.wMinute, st.wHour, st.wDay, st.wMonth-1, st.wYear-1900, st.wDayOfWeek, 0, 0};

	return mktime(&gm);
}

int atoi(const std::string &s)
{
	return atoi(s.c_str());
}

const char *strstri(const char *str, const char *sub)
{
	const char *p = StrStrIA(str, sub);

	return p;
}

const char *strstri(const std::string &str, const char *sub)
{
	return strstri(str.c_str(), sub);
}

/******* 系统有关 ********/
std::string get_user_name()
{
	char buf[200]={0};
	DWORD len = sizeof(buf);

	GetUserNameA(buf, &len);

	return buf;
}

bool is_64bit_system()
{
	SYSTEM_INFO si;

	GetNativeSystemInfo(&si);

	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64
		|| si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
	{
		return true;
	}

	return false;
}

void win_exec(const std::string exe, const char *cmdLine, int show)
{
	if (exe.find(":") != exe.npos
		&& !PathFileExistsA(exe.c_str()))
	{//如果是全路劲，则判断文件是否存在
		return;
	}

	std::string s = "\"" + exe + "\" ";

	if (cmdLine != NULL)
	{
		s.append(cmdLine);
	}

	WinExec(s.c_str(), show);
}

void shell_execute(const char *path, const char *filename, const char *cmdLine, int showCmd)
{
	std::string exe;

	if (path)
	{
		exe = std::string(path)+"\\"+filename; 
	}
	else
	{
		exe = filename;
	}

	ShellExecuteA(NULL, "open", exe.c_str(), cmdLine, path, showCmd);
}

//注册表
bool reg_get_value_str(std::string &res, HKEY hKey, const char *subKey, const char *valueName, int valueMaxLen, int samDesired)
{

	HKEY hKey2 = NULL;

	LONG lRet = RegOpenKeyExA(hKey, subKey, 0, samDesired, &hKey2);

	if (ERROR_SUCCESS == lRet)
	{
		return false;
	}

	std::string buf;
	int type = 0;

	buf.resize(valueMaxLen);

	RegQueryValueExA(hKey2, valueName, NULL, (LPDWORD)&type, (LPBYTE)res.data(), (LPDWORD)&valueMaxLen);

	RegCloseKey(hKey2);

	res = buf.c_str();

	return true;
}


//注册表
std::string reg_get_value_str(HKEY hKey, const char *subKey, const char *valueName, int valueMaxLen, int samDesired)
{
	std::string res;

	HKEY hKey2 = NULL;

	LONG lRet = RegOpenKeyExA(hKey, subKey, 0, samDesired, &hKey2);

	if (ERROR_SUCCESS == lRet)
	{
		int type = 0;

		res.resize(valueMaxLen);

		RegQueryValueExA(hKey2, valueName, NULL, (LPDWORD)&type, (LPBYTE)res.data(), (LPDWORD)&valueMaxLen);

		RegCloseKey(hKey2);
	}

	return res.data();
}

void reg_set_value_str(HKEY hKey, const char *subKey, const char *valueName, const std::string &value, int samDesired)
{
	//RegSetKeyValueA(hKey, subKey, valueName, REG_SZ, value.data(), int(value.length()));	//该函数只支持Vista以上系统
	HKEY hKey2 = NULL;

	LONG lRet = RegOpenKeyExA(hKey, subKey, 0, samDesired, &hKey2);

	if (ERROR_SUCCESS == lRet)
	{
		RegSetValueExA(hKey2, valueName, NULL, REG_SZ, (LPBYTE)value.data(), int(value.length()));

		RegCloseKey(hKey2);
	}
}

void reg_create_node(HKEY hKey, const char *subKey, const char *keyName, int samDesired)
{
	HKEY hKey2 = NULL;

	LONG lRet = RegOpenKeyExA(hKey, subKey, 0, samDesired, &hKey2);

	if (ERROR_SUCCESS == lRet)
	{
		HKEY hKey3 = NULL;

		lRet = RegCreateKeyA(hKey2, keyName, &hKey3);

		if (lRet == ERROR_SUCCESS)
		{
			RegCloseKey(hKey3);
		}

		RegCloseKey(hKey2);
	}
}

bool reg_node_is_exist(HKEY hKey, const char *subKey)
{
	HKEY hKey1 = NULL;

	if (RegOpenKeyA(hKey, subKey, &hKey1) != ERROR_SUCCESS)
	{
		return false;
	}

	int res = RegQueryValueA(hKey1, NULL, NULL, 0);

	RegCloseKey(hKey1);

	return res == ERROR_SUCCESS;
}

bool reg_value_is_exist(HKEY hKey, const char *subKey, const char *valueName)
{
	HKEY hKey1 = NULL;

	if (RegOpenKeyA(hKey, subKey, &hKey1) != ERROR_SUCCESS)
	{
		return false;
	}

	int res = RegQueryValueExA(hKey1, valueName, NULL, NULL, NULL, NULL);

	RegCloseKey(hKey1);

	return res == ERROR_SUCCESS;
}

void reg_value_delete(HKEY hKey, const char *subKey, const char *valueName)				//删除属性
{
	HKEY hKey1 = NULL;

	if (RegOpenKeyA(hKey, subKey, &hKey1) == ERROR_SUCCESS)
	{
		RegDeleteValueA(hKey1, valueName);
	}
}

void reg_node_delete(HKEY hKey, const char *subKey)
{
	HKEY hKey1 = NULL;
}


/* *
  * 函数名称：IsForegroundFullscreen
  * 功能说明：判断当前正在与用户交互的当前激活窗口是否是全屏的。
  * 参数说明：无
  * 返回说明：true：是。
             false：否。
  * 线程安全：是
  * 调用样例：IsForegroundFullscreen ()，表示判断当前正在与用户交互的当前激活窗口是否是全屏的
  */

bool is_foreground_fullscreen()
{
    bool bFullscreen = false;//存放当前激活窗口是否是全屏的，true表示是，false表示不是
    HWND hWnd;
    RECT rcApp;
	RECT rcDesk;

	hWnd = GetForegroundWindow ();//获取当前正在与用户交互的当前激活窗口句柄

    if ((hWnd != GetDesktopWindow ()) && (hWnd != GetShellWindow ()))//如果当前激活窗口不是桌面窗口，也不是控制台窗口
	{
		GetWindowRect (hWnd, &rcApp);//获取当前激活窗口的坐标
		GetWindowRect (GetDesktopWindow(), &rcDesk);//根据桌面窗口句柄，获取整个屏幕的坐标

        if (rcApp.left <= rcDesk.left && //如果当前激活窗口的坐标完全覆盖住桌面窗口，就表示当前激活窗口是全屏的
            rcApp.top <= rcDesk.top &&
            rcApp.right >= rcDesk.right &&
            rcApp.bottom >= rcDesk.bottom)
        {            
			char szTemp[100] = {0};

			if (GetClassNameA(hWnd, szTemp, sizeof(szTemp)) > 0)//如果获取当前激活窗口的类名成功
			{
				if (strcmp(szTemp, "WorkerW") != 0)//如果不是桌面窗口的类名，就认为当前激活窗口是全屏窗口
					bFullscreen = true;
			}
			else 
				bFullscreen = true;//如果获取失败，就认为当前激活窗口是全屏窗口
        }
    }//如果当前激活窗口是桌面窗口，或者是控制台窗口，就直接返回不是全屏

    return bFullscreen;
}

bool is_fullscreen()														//当前是否为全屏 
{ 
	//声明4个句柄，用于获取屏幕角落的的四个点 
	HWND     pWnd1     =     NULL; 
	HWND     pWnd2     =     NULL; 
	HWND     pWnd3     =     NULL; 
	HWND     pWnd4     =     NULL; 
	//获取当前屏幕分辨率 Width 
	int iCx=GetSystemMetrics(SM_CXSCREEN); 
	//获取当前屏幕分辨率 Height 
	int iCy=GetSystemMetrics(SM_CYSCREEN); 

	POINT     pt1; 
	pt1.x     =     1; 
	pt1.y     =     1; 
	POINT     pt2; 
	pt2.x     =     1; 
	pt2.y     =     iCy-1; 
	POINT     pt3; 
	pt3.x     =     iCx-1; 
	pt3.y     =     1; 
	POINT     pt4; 
	pt4.x     =     iCx-1; 
	pt4.y     =     iCy-1; 

	pWnd1     =     WindowFromPoint(pt1); 
	pWnd2     =     WindowFromPoint(pt2); 
	pWnd3     =     WindowFromPoint(pt3); 
	pWnd4     =     WindowFromPoint(pt4); 

	if (pWnd1 == pWnd2
		&& pWnd2 == pWnd3
		&& pWnd3 == pWnd4)
	{ 
		return true;
	}

	return false; 
} 