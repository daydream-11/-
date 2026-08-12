#pragma once
#ifndef __EASYFUNCTIONS__
#define __EASYFUNCTIONS__
#include <tchar.h>
#include <string>
#include <vector>
#include <windows.h>
#include <Winsvc.h>
#include <shlobj.h>
#include <algorithm>
#include <WinCrypt.h>
#include <time.h>
#include <atlbase.h>
#include <shlwapi.h>
#include <shellapi.h>
#include <shlobj.h>
#include <comdef.h>
#include <ShObjIdl.h>
#include <Shlguid.h>

using namespace std;

#pragma comment(lib,"shell32.lib")
#pragma comment(lib, "Version.lib")


FORCEINLINE  wstring GetModuleDir();
FORCEINLINE  wstring  ExtractFileDir(wstring fullName);

FORCEINLINE
std::wstring Replace(std::wstring str, const std::wstring old_value, const std::wstring new_value)
{
	try
	{
		std::wstring::size_type pos(0);
		if ((pos = str.find(old_value)) != std::wstring::npos)  //查找  
		{
			str.replace(pos, old_value.size(), new_value);
		}

		return str;
	}
	catch (...)
	{

		return str;
	}
}



FORCEINLINE
wstring  FixPath(wstring fullName)
{

	struct MacroItem
	{
		std::wstring szName;
		DWORD        dwValue;
	};

	MacroItem  MacoMap[63] = {
		{__T("%DESKTOP%"),                                    CSIDL_DESKTOP                    },
		{__T("%INTERNET%"),                                   CSIDL_INTERNET                   },
		{__T("%PROGRAMS%"),                                   CSIDL_PROGRAMS                   },
		{__T("%CONTROLS%"),                                   CSIDL_CONTROLS                   },
		{__T("%PRINTERS%"),                                   CSIDL_PRINTERS                   },
		{__T("%PERSONAL%"),                                   CSIDL_PERSONAL                   },
		{__T("%FAVORITES%"),                                  CSIDL_FAVORITES                  },
		{__T("%STARTUP%"),                                    CSIDL_STARTUP                    },
		{__T("%RECENT%"),                                     CSIDL_RECENT                     },
		{__T("%SENDTO%"),                                     CSIDL_SENDTO                     },
		{__T("%BITBUCKET%"),                                  CSIDL_BITBUCKET                  },
		{__T("%STARTMENU%"),                                  CSIDL_STARTMENU                  },
		{__T("%MYDOCUMENTS%"),                                CSIDL_MYDOCUMENTS                },
		{__T("%MYMUSIC%"),                                    CSIDL_MYMUSIC                    },
		{__T("%MYVIDEO%"),                                    CSIDL_MYVIDEO                    },
		{__T("%DESKTOPDIRECTORY%"),                           CSIDL_DESKTOPDIRECTORY           },
		{__T("%DRIVES%"),                                     CSIDL_DRIVES                     },
		{__T("%NETWORK%"),                                    CSIDL_NETWORK                    },
		{__T("%NETHOOD%"),                                    CSIDL_NETHOOD                    },
		{__T("%FONTS%"),                                      CSIDL_FONTS                      },
		{__T("%TEMPLATES%"),                                  CSIDL_TEMPLATES                  },
		{__T("%COMMON_STARTMENU%"),                           CSIDL_COMMON_STARTMENU           },
		{__T("%COMMON_PROGRAMS%"),                            CSIDL_COMMON_PROGRAMS            },
		{__T("%COMMON_STARTUP%"),                             CSIDL_COMMON_STARTUP             },
		{__T("%COMMON_DESKTOPDIRECTORY%"),                    CSIDL_COMMON_DESKTOPDIRECTORY    },
		{__T("%APPDATA%"),                                    CSIDL_APPDATA                    },
		{__T("%PRINTHOOD%"),                                  CSIDL_PRINTHOOD                  },
		{__T("%LOCAL_APPDATA%"),                              CSIDL_LOCAL_APPDATA              },
		{__T("%ALTSTARTUP%"),                                 CSIDL_ALTSTARTUP                 },
		{__T("%COMMON_ALTSTARTUP%"),                          CSIDL_COMMON_ALTSTARTUP          },
		{__T("%COMMON_FAVORITES%"),                           CSIDL_COMMON_FAVORITES           },
		{__T("%INTERNET_CACHE%"),                             CSIDL_INTERNET_CACHE             },
		{__T("%COOKIES%"),                                    CSIDL_COOKIES                    },
		{__T("%HISTORY%"),                                    CSIDL_HISTORY                    },
		{__T("%COMMON_APPDATA%"),                             CSIDL_COMMON_APPDATA             },
		{__T("%WINDOWS%"),                                    CSIDL_WINDOWS                    },
		{__T("%SYSTEM%"),                                     CSIDL_SYSTEM                     },
		{__T("%PROGRAM_FILES%"),                              CSIDL_PROGRAM_FILES              },
		{__T("%MYPICTURES%"),                                 CSIDL_MYPICTURES                 },
		{__T("%PROFILE%"),                                    CSIDL_PROFILE                    },
		{__T("%SYSTEMX86%"),                                  CSIDL_SYSTEMX86                  },
		{__T("%PROGRAM_FILESX86%"),                           CSIDL_PROGRAM_FILESX86           },
		{__T("%PROGRAM_FILES_COMMON%"),                       CSIDL_PROGRAM_FILES_COMMON       },
		{__T("%PROGRAM_FILES_COMMONX86%"),                    CSIDL_PROGRAM_FILES_COMMONX86    },
		{__T("%COMMON_TEMPLATES%"),                           CSIDL_COMMON_TEMPLATES           },
		{__T("%COMMON_DOCUMENTS%"),                           CSIDL_COMMON_DOCUMENTS           },
		{__T("%COMMON_ADMINTOOLS%"),                          CSIDL_COMMON_ADMINTOOLS          },
		{__T("%ADMINTOOLS%"),                                 CSIDL_ADMINTOOLS                 },
		{__T("%CONNECTIONS%"),                                CSIDL_CONNECTIONS                },
		{__T("%COMMON_MUSIC%"),                               CSIDL_COMMON_MUSIC               },
		{__T("%COMMON_PICTURES%"),                            CSIDL_COMMON_PICTURES            },
		{__T("%COMMON_VIDEO%"),                               CSIDL_COMMON_VIDEO               },
		{__T("%RESOURCES%"),                                  CSIDL_RESOURCES                  },
		{__T("%RESOURCES_LOCALIZED%"),                        CSIDL_RESOURCES_LOCALIZED        },
		{__T("%COMMON_OEM_LINKS%"),                           CSIDL_COMMON_OEM_LINKS           },
		{__T("%CDBURN_AREA%"),                                CSIDL_CDBURN_AREA                },
		{__T("%COMPUTERSNEARME%"),                            CSIDL_COMPUTERSNEARME            },
		{__T("%FLAG_CREATE%"),                                CSIDL_FLAG_CREATE                },
		{__T("%FLAG_DONT_VERIFY%"),                           CSIDL_FLAG_DONT_VERIFY           },
		{__T("%FLAG_DONT_UNEXPAND%"),                         CSIDL_FLAG_DONT_UNEXPAND         },
		{__T("%FLAG_NO_ALIAS%"),                              CSIDL_FLAG_NO_ALIAS              },
		{__T("%FLAG_PER_USER_INIT%"),                         CSIDL_FLAG_PER_USER_INIT         },
		{__T("%FLAG_MASK%"),                                  CSIDL_FLAG_MASK                  }
	};


	const std::wstring macro_parentdir = _T("..");
	const std::wstring macro_currentdir = _T(".");

	typedef BOOL (WINAPI * FNSHGetSpecialFolderPath)(HWND hwndOwner,LPTSTR lpszPath,int nFolder,BOOL fCreate);
	FNSHGetSpecialFolderPath  fnSHGetSpecialFolderPath = (FNSHGetSpecialFolderPath)GetProcAddress(LoadLibrary(__T("shell32.dll")), "SHGetSpecialFolderPathW");
	TCHAR  realDir[MAX_PATH] = {0};

	for(int i =0; i < (sizeof(MacoMap)/sizeof(MacroItem)); i++)
	{
		if(fullName.find(MacoMap[i].szName) != fullName.npos)
		{ 
			fnSHGetSpecialFolderPath(NULL, realDir,MacoMap[i].dwValue,0); 
			return Replace(fullName, MacoMap[i].szName, realDir); 
		}
	}

    //
	if(fullName.substr(0,macro_parentdir.size()) == macro_parentdir)
	{
        return ExtractFileDir(GetModuleDir()) + fullName.substr(macro_parentdir.size());
	}
	else if(fullName.substr(0,macro_currentdir.size()) == macro_currentdir)
	{
		return GetModuleDir() + fullName.substr(macro_currentdir.size());
	}

	
	return fullName;
}

FORCEINLINE
wstring  ExtractFileDir(wstring fullName)
{
	return fullName.substr(0, fullName.rfind(__T('\\')));
}

FORCEINLINE
wstring  ExtractFilePath(wstring fullName)
{
	return fullName.substr(0, fullName.rfind(__T('\\')) + 1);
}

FORCEINLINE
BOOL DirectoryExists(wstring Directory)
{
	DWORD  Code = GetFileAttributes(Directory.c_str());
	return (Code != INVALID_FILE_ATTRIBUTES) && ((FILE_ATTRIBUTE_DIRECTORY & Code) != 0);
}

FORCEINLINE
BOOL ExistsLockedOrShared(wstring FileName)
{
	WIN32_FIND_DATA    FindData;
	HANDLE              LHandle = FindFirstFile(FileName.c_str(), &FindData);
	if(LHandle != INVALID_HANDLE_VALUE)
	{
		FindClose(LHandle);
		return ((FindData.dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY) == 0);
	}
	else
		return FALSE;
}

FORCEINLINE
wstring  ExtractFileName(wstring fullName)
{
	return fullName.substr(fullName.rfind(__T('\\')) + 1);
}

FORCEINLINE
wstring  ExtractFileExtName(wstring fullName)
{
	wstring ret;
	wstring fn = ExtractFileName(fullName);
	wstring::size_type start =fn.rfind(__T('.'));
	if(start == wstring::npos)
       return ret;   
	ret = fn.substr(start);
	return ret;
}

FORCEINLINE
wstring  ExtractUrlFileName(wstring fullName)
{
	return fullName.substr(fullName.rfind(__T('/')) + 1);
}

FORCEINLINE
wstring  ExtractFileNoExtName(wstring fullName)
{
	wstring tmp = ExtractFileName(fullName);
	wstring::size_type i = tmp.rfind(__T('.'));
	if(i!= wstring::npos)
	{
		return  tmp.substr(0, i);
	}
	return __T("");
}

FORCEINLINE
BOOL FileExists(wstring FileName)
{
	int Code =  (int)GetFileAttributes(FileName.c_str());
	if(Code != -1)
	{
		return (FILE_ATTRIBUTE_DIRECTORY & Code) == 0;
	}
	else
	{
		DWORD LastError = GetLastError();
		return (LastError != ERROR_FILE_NOT_FOUND) &&
			(LastError != ERROR_PATH_NOT_FOUND) &&
			(LastError != ERROR_INVALID_NAME) && ExistsLockedOrShared(FileName);
	}
}


FORCEINLINE
BOOL ForceDirectories(wstring dir)
{
	if(dir.size() <= 0)
		return FALSE;
	if(dir[dir.size()-1] == __T('\\'))
	{
		dir[dir.size()-1] = 0;
		dir = dir.c_str();
	}
	if((dir.size() < 3) || DirectoryExists(dir))
		return TRUE;
	return ForceDirectories(ExtractFilePath(dir)) && CreateDirectory(dir.c_str(), NULL);
}

FORCEINLINE
wstring GetAppDir()
{
	wstring    ret;
	TCHAR      CurrentDir[MAX_PATH] = {0};

	GetModuleFileName(NULL, CurrentDir, MAX_PATH);

	ret = ExtractFileDir(CurrentDir);
	return ret;
}

FORCEINLINE
wstring GetModuleFullName()
{
	TCHAR      CurrentDir[MAX_PATH] = {0};
	HMODULE    h = NULL;

	if(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS| GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR )GetModuleFullName, &h))
	{
		GetModuleFileName(h, CurrentDir, MAX_PATH);
	}
	else
	{
		GetModuleFileName(NULL, CurrentDir, MAX_PATH);
	}
	return CurrentDir;
}


FORCEINLINE
wstring GetModuleDir()
{
	wstring    ret;
	TCHAR      CurrentDir[MAX_PATH] = {0};
	HMODULE    h = NULL;

	if(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS| GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR )GetModuleDir, &h))
	{
	    GetModuleFileName(h, CurrentDir, MAX_PATH);
	}
	else
	{
        GetModuleFileName(NULL, CurrentDir, MAX_PATH);
	}

	ret = ExtractFileDir(CurrentDir);
	return ret;
}

FORCEINLINE
std::string WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen<= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen -1] = 0;
	std::string strTemp(pszDst);
	delete [] pszDst;
	return strTemp;
}

FORCEINLINE
string ws2s(wstring inputws)
{ 
	return WChar2Ansi(inputws.c_str()); 
}
//Converting a Ansi string to WChar string

FORCEINLINE
std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen)
{
	UINT  code = CP_ACP;
	//如果有UTF8头
	if(nLen >=3 && (BYTE)pszSrc[0] == 0xef && (BYTE)pszSrc[1] == 0xbb && (BYTE)pszSrc[2] == 0xbf)
	{
		pszSrc = (LPCSTR)&pszSrc[3];
		nLen -= 3;
		code = CP_UTF8;
	}
	int nSize = MultiByteToWideChar(code, 0, pszSrc, nLen, 0, 0);
	if(nSize <= 0) return __T("");
	WCHAR *pwszDst = new WCHAR[nSize+1];
	if( NULL == pwszDst) return __T("");
	MultiByteToWideChar(code, 0,pszSrc, nLen, pwszDst, nSize);
	pwszDst[nSize] = 0;
	if( pwszDst[0] == 0xFEFF) // skip Oxfeff
		for(int i = 0; i < nSize; i ++)
			pwszDst[i] = pwszDst[i+1];
	wstring wcharString(pwszDst);
	delete pwszDst;
	return wcharString;
}

FORCEINLINE
std::wstring s2ws(const string s)
{
	return Ansi2WChar(s.c_str(),s.size());
}

FORCEINLINE
int split(const std::wstring& str, vector<std::wstring>& ret_, std::wstring sep)
{
	if (str.empty())
	{
		return 0;
	}

	std::wstring tmp;
	std::wstring::size_type pos_begin = str.find_first_not_of(sep);
	std::wstring::size_type comma_pos = 0;

	while (pos_begin != std::wstring::npos)
	{
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != std::wstring::npos)
		{
			tmp = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = str.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
			ret_.push_back(tmp);
			tmp.clear();
		}
	}
	return 0;
}

FORCEINLINE
std::wstring toUpper(std::wstring value)
{
	std::transform(value.begin(), value.end(), value.begin(), towupper); 
	return  value;
}

FORCEINLINE
std::wstring toLower(std::wstring value)
{
	std::transform(value.begin(), value.end(), value.begin(), towlower); 
	return  value;
}

FORCEINLINE
std::wstring Base16(const LPVOID buf, DWORD len)
{
	std::wstring ret;
    PWCHAR retBuf = new WCHAR[2*len + 1];
    for(DWORD i=0; i< len; i++) {
        _stprintf_s(&retBuf[i*2], 3, __T("%0.2x"), ((const PBYTE)buf)[i]);
	}
	ret = retBuf;
	delete [] retBuf;
    return ret;
}

#define  FILE_BUFFER_SIZE (4096)
//4096
FORCEINLINE
std::wstring CalculateMD5( std::wstring filepath)
{
	std::wstring  ret;
	HCRYPTPROV hCryptProv = 0;
	HCRYPTHASH hHash = 0;
	unsigned char fileBuffer[FILE_BUFFER_SIZE] = {0};
	if(CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) || CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, 0))
	{
		FILE* pFile = _tfopen(filepath.c_str(), TEXT("rb"));
		if (pFile)
		{
			CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash);
			for (int i=0; i<256; i++)
			{
				while(!feof(pFile))
				{
					memset(fileBuffer, 0, FILE_BUFFER_SIZE);
					size_t count = fread(fileBuffer, 1, FILE_BUFFER_SIZE, pFile);
					CryptHashData(hHash, fileBuffer, count, 0);
				}
			}
			fclose(pFile);

			DWORD dwCount = 16;
			BYTE  md5[16] = {0};
			CryptGetHashParam(hHash, HP_HASHVAL, md5, &dwCount, 0);
			CryptDestroyHash(hHash);
			ret = Base16(md5, 16);

		}
		CryptReleaseContext(hCryptProv, 0);
	}
	return ret;
}  

FORCEINLINE
std::wstring CalculateMD5(const LPVOID buf, DWORD len)
{
	std::wstring  ret;
	HCRYPTPROV hCryptProv = 0;
	HCRYPTHASH hHash = 0;
	if(CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) || CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, 0))
	{

		if (buf)
		{
			CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash);
		    CryptHashData(hHash, (const BYTE*)buf, len, 0);

			DWORD dwCount = 16;
			BYTE  md5[16] = {0};
			CryptGetHashParam(hHash, HP_HASHVAL, md5, &dwCount, 0);
			CryptDestroyHash(hHash);
			ret = Base16(md5, 16);

		}
		CryptReleaseContext(hCryptProv, 0);
	}
	return ret;
}

//RC4
namespace EASY_RC4
{
	typedef struct rc4_key 
	{      
		unsigned char state[256];      
		unsigned char x;      
		unsigned char y; 
	} rc4_key; 

	FORCEINLINE
		void swap_byte(unsigned char *a, unsigned char *b); 

	FORCEINLINE
		void prepare_key(unsigned char *key_data_ptr, int key_data_len, 
		rc4_key *key) 
	{ 
		unsigned char index1; 
		unsigned char index2; 
		unsigned char* state; 

		state = &key->state[0];        
		for(short counter = 0; counter < 256; counter++)          
			state[counter] = counter;            
		key->x = 0;    
		key->y = 0;    
		index1 = 0;    
		index2 = 0;          
		for(short counter = 0; counter < 256; counter++)      
		{            
			index2 = (key_data_ptr[index1] + state[counter] + 
				index2) % 256;            
			swap_byte(&state[counter], &state[index2]);          

			index1 = (index1 + 1) % key_data_len;  
		} 
	} 

	FORCEINLINE
		void rc4(unsigned char *buffer_ptr, int buffer_len, rc4_key *key) 
	{  
		unsigned char x; 
		unsigned char y; 
		unsigned char* state; 
		unsigned char xorIndex; 
		short counter;          

		x = key->x;    
		y = key->y;    

		state = &key->state[0];        
		for(counter = 0; counter < buffer_len; counter ++)      
		{            
			x = (x + 1) % 256;                
			y = (state[x] + y) % 256;            
			swap_byte(&state[x], &state[y]);                  

			xorIndex = (state[x] + state[y]) % 256;            

			buffer_ptr[counter] ^= state[xorIndex];        
		}            
		key->x = x;    
		key->y = y; 
	} 

	FORCEINLINE
		void swap_byte(unsigned char *a, unsigned char *b) 
	{ 
		unsigned char swapByte;  

		swapByte = *a;  
		*a = *b;      
		*b = swapByte; 
	}
}
FORCEINLINE
void rc4(std::wstring key, const LPVOID buffer_ptr, const ULONG buffer_len) 
{
	EASY_RC4::rc4_key  rc4key;   
	EASY_RC4::prepare_key((unsigned char*)key.c_str(), sizeof(WCHAR)*key.size(), &rc4key);
	EASY_RC4::rc4((unsigned char*)buffer_ptr, buffer_len, &rc4key);
}

FORCEINLINE
void rc4(std::string key, const LPVOID buffer_ptr, const ULONG buffer_len) 
{
	EASY_RC4::rc4_key  rc4key;   
	EASY_RC4::prepare_key((unsigned char*)key.c_str(), sizeof(char)*key.size(), &rc4key);
	EASY_RC4::rc4((unsigned char*)buffer_ptr, buffer_len, &rc4key);
}

FORCEINLINE
void rc4(const LPVOID key, const ULONG key_len, const LPVOID buffer_ptr, const ULONG buffer_len) 
{
	EASY_RC4::rc4_key  rc4key;   
	EASY_RC4::prepare_key((unsigned char*)key, (int)key_len, &rc4key);
	EASY_RC4::rc4((unsigned char*)buffer_ptr, buffer_len, &rc4key);
}
//end RC4


FORCEINLINE
std::wstring GetPEFileVersion(const std::wstring filePath) 
{
	std::wstring version = __T("0.0.0.0");
	TCHAR fullpath[MAX_PATH + 10];

	if (filePath.size() == 0) {
		GetModuleFileName(0, fullpath, MAX_PATH + 10);
	} else {
		const wchar_t* filePathChars = filePath.c_str();  
		for (size_t i = 0; i < filePath.size(); i++) {
			fullpath[i] = filePathChars[i];
		}
		fullpath[filePath.size()] = _T('\0');
	}

	TCHAR *str = new TCHAR[_tcslen(fullpath) + 1];
	_tcscpy(str, fullpath);
	DWORD tmp = 0;
	LPVOID pBlock = NULL;
	DWORD len = GetFileVersionInfoSize(str, &tmp);
	if(0 == len)
	{
		goto OUTWAY;
	}
	pBlock = new char[len];
	if(!GetFileVersionInfo(str, 0, len, pBlock))
	{
		goto OUTWAY;
	}
	LPVOID ptr;
	UINT ptrlen;

	struct LANGANDCODEPAGE {
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;

	UINT cbTranslate;

	if (!VerQueryValue(pBlock, 
		_T("\\VarFileInfo\\Translation"),
		(LPVOID*)&lpTranslate,
		&cbTranslate))
	{
		goto OUTWAY;
	}


	if (VerQueryValue(pBlock, _T("\\"), &ptr, &ptrlen)) {
		VS_FIXEDFILEINFO *fi = (VS_FIXEDFILEINFO*)ptr;

		TCHAR szVersion[512] = {0};
		_stprintf(szVersion, _T("%d.%d.%d.%d"),
			HIWORD(fi->dwFileVersionMS), LOWORD(fi->dwFileVersionMS),
			HIWORD(fi->dwFileVersionLS), LOWORD(fi->dwFileVersionLS));
		version = szVersion;
	}
	else
	{
		int e = GetLastError();
		if(e)
		{
			GetTickCount();
		}
	}
OUTWAY:
	if(NULL != str)
	   delete [] str;
	if(NULL != pBlock)
	   delete [] pBlock;
	return version;
}

FORCEINLINE
bool  RegParserKeyPath(std::wstring Path, HKEY&  rootKey, std::wstring& subKey, std::wstring& valueName)
{
    bool   ret = false;
    
	const wstring szHKEY_CLASSES_ROOT = __T("HKEY_CLASSES_ROOT");
	const wstring szHKEY_CURRENT_USER = __T("HKEY_CURRENT_USER");
	const wstring szHKEY_LOCAL_MACHINE = __T("HKEY_LOCAL_MACHINE");
	const wstring szHKEY_USERS = __T("HKEY_USERS");
	const wstring szHKEY_PERFORMANCE_DATA = __T("HKEY_PERFORMANCE_DATA");
	const wstring szHKEY_CURRENT_CONFIG = __T("HKEY_CURRENT_CONFIG");
	const wstring szHKEY_DYN_DATA = __T("HKEY_DYN_DATA");

	std::wstring root = Path.substr(0, Path.find(__T('\\')));
	Path = Path.substr(Path.find(__T('\\')) + 1);
	valueName = Path.substr(Path.rfind(__T('\\')) + 1);
	subKey = Path.substr(0, Path.rfind(__T('\\')));

	if(szHKEY_CLASSES_ROOT == root)
	{
		rootKey =  HKEY_CLASSES_ROOT;
	}else
		if(szHKEY_CURRENT_USER == root)
		{
			rootKey =  HKEY_CURRENT_USER;
		}
		else
			if(szHKEY_LOCAL_MACHINE == root)
			{
				rootKey =  HKEY_LOCAL_MACHINE;
			}
			else
				if(szHKEY_USERS == root)
				{
					rootKey =  HKEY_USERS;
				}
				else
					if(szHKEY_PERFORMANCE_DATA == root)
					{
						rootKey =  HKEY_PERFORMANCE_DATA;
					}
					else
						if(szHKEY_CURRENT_CONFIG == root)
						{
							rootKey =  HKEY_CURRENT_CONFIG;
						}
						else
							if(szHKEY_DYN_DATA == root)
							{
								rootKey =  HKEY_DYN_DATA;
							}
							ret = true;
							return  ret;
}


FORCEINLINE
bool  RegValueExist(std::wstring Path)
{
	bool             ret = false;
	HKEY             rootKey = NULL;
	HKEY             tmpKey = NULL;
	std::wstring     subPath, valueName;
	if(!RegParserKeyPath(Path, rootKey, subPath, valueName))
		return false;
	if(rootKey == HKEY_CURRENT_USER)
	{
		if (ERROR_SUCCESS != RegOpenCurrentUser(KEY_ALL_ACCESS, &rootKey))
		{
			rootKey = HKEY_CURRENT_USER;
		}

	}
	//
	DWORD     dwDisposition = 0;
	if(ERROR_SUCCESS == RegOpenKeyEx(rootKey, (LPCTSTR)subPath.c_str(), 0, KEY_READ, &tmpKey))
	{
		if ((ERROR_SUCCESS == RegQueryValueEx(tmpKey, (LPCTSTR)valueName.c_str(), NULL, NULL, NULL, NULL)))
		{
			if (ERROR_SUCCESS == RegQueryValueEx(tmpKey, (LPCTSTR)valueName.c_str(), NULL, NULL, NULL, NULL))
			{
				ret = true;
			}
		}
		RegCloseKey(tmpKey);
	}
	//
	if((((DWORD)rootKey) & 0x80000000) != 0x80000000)
	{ 
		RegCloseKey(rootKey);
	}
	return ret;
}

FORCEINLINE
bool  RegKeyExist(std::wstring Path)
{
	bool             ret = false;
	HKEY             rootKey = NULL;
	HKEY             tmpKey = NULL;
	std::wstring     subPath, valueName;
	if(!RegParserKeyPath(Path, rootKey, subPath, valueName))
		return false;
	//因为是只要分解成root和subpath,而不需要valuename
	subPath += __T("\\");
    subPath += valueName;

	if(rootKey == HKEY_CURRENT_USER)
	{
		if (ERROR_SUCCESS != RegOpenCurrentUser(KEY_ALL_ACCESS, &rootKey))
		{
			rootKey = HKEY_CURRENT_USER;
		}

	}
	//
	DWORD     dwDisposition = 0;
	if(ERROR_SUCCESS == RegOpenKeyEx(rootKey, (LPCTSTR)subPath.c_str(), 0, KEY_READ, &tmpKey))
	{
		return true;
		RegCloseKey(tmpKey);
	}
	//
	if((((DWORD)rootKey) & 0x80000000) != 0x80000000)
	{ 
		RegCloseKey(rootKey);
	}
	return ret;
}

FORCEINLINE
bool  RegGetValue(std::wstring Path, DWORD ValType, PBYTE& pVal, DWORD& cbData)
{
	 bool             ret = false;
     HKEY             rootKey = NULL;
	 HKEY             tmpKey = NULL;
	 std::wstring     subPath, valueName;
     if(!RegParserKeyPath(Path, rootKey, subPath, valueName))
	     return false;
	 
     if(rootKey == HKEY_CURRENT_USER)
	 {
		 if (ERROR_SUCCESS != RegOpenCurrentUser(KEY_ALL_ACCESS, &rootKey))
		 {
             rootKey = HKEY_CURRENT_USER;
		 }

	 }
	 //
	 DWORD     dwDisposition = 0;
     if(ERROR_SUCCESS == RegOpenKeyEx(rootKey, (LPCTSTR)subPath.c_str(), 0, KEY_READ, &tmpKey))
	 {
		 
		 DWORD  MyValType = 0;
		 DWORD  BufSize = 0;
         if ((ERROR_SUCCESS == RegQueryValueEx(tmpKey, (LPCTSTR)valueName.c_str(), NULL, &MyValType, NULL, &BufSize))&&
			 (MyValType == ValType))
		 {
             PBYTE   buf = new BYTE[BufSize];
			 if (ERROR_SUCCESS == RegQueryValueEx(tmpKey, (LPCTSTR)valueName.c_str(), NULL, &MyValType, buf, &BufSize))
			 {
                  pVal = buf;
				  cbData = BufSize;
				  ret = true;
			 }
			 else
			 {
				 delete []buf;
			 }

		 }
         RegCloseKey(tmpKey);
	 }
	 //
	 if((((DWORD)rootKey) & 0x80000000) != 0x80000000)
	 { 
         RegCloseKey(rootKey);
	 }
	 return ret;
}

FORCEINLINE
bool  RegSetValue(std::wstring Path, DWORD ValType, const BYTE* pVal, DWORD cbData)
{
	bool             ret = false;
	HKEY             rootKey = NULL;
	HKEY             tmpKey = NULL;
	std::wstring     subPath, valueName;
	if(!RegParserKeyPath(Path, rootKey, subPath, valueName))
		return false;
	if(rootKey == HKEY_CURRENT_USER)
	{
		if (ERROR_SUCCESS != RegOpenCurrentUser(KEY_ALL_ACCESS, &rootKey))
		{
			rootKey = HKEY_CURRENT_USER;
		}

	}
	//
	DWORD     dwDisposition = 0;
	if(ERROR_SUCCESS == RegCreateKeyEx(rootKey, (LPCTSTR)subPath.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_WRITE, NULL, &tmpKey, &dwDisposition))
	{
		ret = ERROR_SUCCESS == RegSetValueEx(tmpKey, (LPCTSTR)valueName.c_str(), 0, ValType, pVal, cbData);
		RegCloseKey(tmpKey);
	}
	//
	if((((DWORD)rootKey) & 0x80000000) != 0x80000000)
	{ 
		RegCloseKey(rootKey);
	}
	return ret;
}

FORCEINLINE
std::wstring RegGetStr(std::wstring Path, std::wstring DefValue = std::wstring(__T("")))
{
	std::wstring  ret;
    PBYTE  buf = NULL;
	DWORD  len = 0;
    if(RegGetValue(Path, REG_SZ, buf, len))
	{
		
		if((NULL != buf)&&(len > 0))
		{
			//ret.resize(len / sizeof(WCHAR));
            //memcpy((void*)ret.c_str(), buf, len);
            ret = (PWCHAR)buf;
			delete [] buf;
		}
	}
	else
	{
		ret = DefValue;
	}
	return  ret;
}

FORCEINLINE
DWORD RegGetDWORD(std::wstring Path, DWORD DefValue = 0)
{
	DWORD  ret = DefValue;
	PBYTE  buf = NULL;
	DWORD  len = 0;
	if(RegGetValue(Path, REG_DWORD, buf, len))
	{
		if((NULL != buf)&&(len > 0))
		{
			//ret.resize(len / sizeof(WCHAR));
			//memcpy((void*)ret.c_str(), buf, len);
			ret = *((PDWORD)buf);
			delete [] buf;
		}
	}
	else
	{
		ret = DefValue;
	}
	return  ret;
}

FORCEINLINE
bool RegSetStr(std::wstring Path, std::wstring Value)
{
	return  RegSetValue(Path, REG_SZ, (const BYTE*)Value.c_str(), Value.size()*sizeof(WCHAR));
}

FORCEINLINE
bool RegSetDWORD(std::wstring Path, DWORD Value)
{
	return  RegSetValue(Path, REG_DWORD, (const PBYTE)&Value, sizeof(Value));
}


FORCEINLINE
BOOL GetProcessElevation(TOKEN_ELEVATION_TYPE* pElevationType, BOOL* pIsAdmin) {

	HANDLE hToken = NULL;
	DWORD dwSize; 

	// Get current process token
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
		return(FALSE);

	BOOL bResult = FALSE;

	// Retrieve elevation type information 
	if (GetTokenInformation(hToken, TokenElevationType, 
		pElevationType, sizeof(TOKEN_ELEVATION_TYPE), &dwSize)) {
			// Create the SID corresponding to the Administrators group
			byte adminSID[SECURITY_MAX_SID_SIZE];
			dwSize = sizeof(adminSID);
			CreateWellKnownSid(WinBuiltinAdministratorsSid, NULL, &adminSID, 
				&dwSize);

			if (*pElevationType == TokenElevationTypeLimited) {
				// Get handle to linked token (will have one if we are lua)
				HANDLE hUnfilteredToken = NULL;
				GetTokenInformation(hToken, TokenLinkedToken, (VOID*) 
					&hUnfilteredToken, sizeof(HANDLE), &dwSize);

				// Check if this original token contains admin SID
				if (CheckTokenMembership(hUnfilteredToken, &adminSID, pIsAdmin)) {
					bResult = TRUE;
				}

				// Don't forget to close the unfiltered token
				CloseHandle(hUnfilteredToken);
			} else {
				*pIsAdmin = IsUserAnAdmin();
				bResult = TRUE;
			}
	}

	// Don't forget to close the process token
	CloseHandle(hToken);

	return(bResult);
}

FORCEINLINE
std::wstring GetProcessUsername(HANDLE hProcess) {
	std::wstring  ret;
	HANDLE		tok = 0;
	TOKEN_USER	*ptu;

	DWORD
		nlen, 
		dlen;

	WCHAR	name[300],	dom[300],	tubuf[300];
	WCHAR   userName[1024] = {0};
	DWORD   userNameLen = 1024;
	int iUse;

	if (OpenProcessToken(hProcess,TOKEN_QUERY,&tok))
	{
		ptu = (TOKEN_USER*)tubuf;
		if (GetTokenInformation(tok,(TOKEN_INFORMATION_CLASS)1,ptu,300,&nlen))
		{
			dlen = 300;	nlen = 300;
			if (LookupAccountSid(0, ptu->User.Sid, name, &nlen, dom, &dlen, (PSID_NAME_USE)&iUse))
			{
				nlen = min(userNameLen-1,(int)nlen);
				_tcsnccpy(userName, name, nlen);
				userName[nlen] = 0;
                ret = userName;
				return ret;
			}
		}
	}

	if (tok) CloseHandle(tok);
	return ret;
}

FORCEINLINE
std::wstring GetPCName() 
{
	TCHAR szHostName[MAX_PATH]={0};
	DWORD dwSize   =   MAX_PATH;
	GetComputerName(   szHostName,   &dwSize   );
	return wstring( szHostName);
}

FORCEINLINE
bool  IsRunInService()
{
    return toUpper(GetProcessUsername(GetCurrentProcess())) == __T("SYSTEM");
}

FORCEINLINE
BOOL ServiceExists(std::wstring ServiceName)
{
	BOOL    ret = FALSE;
	SC_HANDLE   schService = NULL;
	SC_HANDLE   schSCManager = NULL;

	do 
	{
		schSCManager = OpenSCManager(
			NULL,                   // machine (NULL == local)
			NULL,                   // database (NULL == default)
			SC_MANAGER_ALL_ACCESS   // access required
			);
		if(!schSCManager)
		{
			break;
		}

		schService = OpenService(schSCManager, ServiceName.c_str(), SERVICE_ALL_ACCESS);
		if(!schService)
		{

			break;	
		}
		else
		{
			SERVICE_STATUS  ss = {0};
			ret =QueryServiceStatus(schService, &ss) &&(ss.dwCurrentState == SERVICE_RUNNING);

		}


	} while (0);

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);

	return ret;
}

FORCEINLINE
BOOL szWildMatch(const PCTSTR pat, const PCTSTR str) {
	switch (*pat) {
	  case __T('\0'):
		  return !*str;
	  case __T('*') :
		  return szWildMatch(pat+1, str) || *str && szWildMatch(pat, str+1);
	  case __T('?') :
		  return *str && (*str != __T('.')) && szWildMatch(pat+1, str+1);
	  default  :
		  return (*str == *pat) &&
			  szWildMatch(pat+1, str+1);
	} 
}

template<typename _WTy>
//typedef wstring _WTy;
FORCEINLINE
BOOL szWildMatch(const _WTy pat, const _WTy str) {
	if(pat.size() <= 0)
		return !str.size();
	switch (pat[0]) {
	  case ('*') :
		  return szWildMatch(pat.substr(1), str) || str.size() && szWildMatch(pat, str.substr(1));
	  case ('?') :
		  return (str.size() > 0) && (str[0] != ('.')) && szWildMatch(pat.substr(1), str.substr(1));
	  default  :
		  return (str.size() > 0 && str[0] == pat[0]) &&
			  szWildMatch(pat.substr(1), str.substr(1));
	} 
}

template<typename _WTy>
//typedef wstring _WTy;
FORCEINLINE
BOOL szWildMatchICase(const _WTy pat, const _WTy str) 
{
    return szWildMatch(toLower(pat), toLower(str));
}

FORCEINLINE
std::wstring genTmpFileName()
{
	TCHAR   path[MAX_PATH] = {0}, fileName[MAX_PATH] = {0}; 
	GetTempPath(MAX_PATH, path);
	GetTempFileName(path, __T("SDO"), 0, fileName);
	return fileName;
}

FORCEINLINE
time_t GetTimeStampByStr( std::wstring szDateTime)   
{ 
	const WCHAR* pDate = szDateTime.c_str(); 
	const WCHAR* pStart = pDate; 

	WCHAR szYear[5], szMonth[3], szDay[3], szHour[3], szMin[3], szSec[3]; 

	szYear[0]   = *pDate++; 
	szYear[1]   = *pDate++; 
	szYear[2]   = *pDate++; 
	szYear[3]   = *pDate++; 
	szYear[4]   = 0x0; 

	++pDate; 

	szMonth[0]  = *pDate++; 
	szMonth[1]  = *pDate++; 
	szMonth[2]  = 0x0; 

	++pDate; 

	szDay[0]    = *pDate++;   
	szDay[1]    = *pDate++; 
	szDay[2]    = 0x0; 

	++pDate; 

	szHour[0]   = *pDate++; 
	szHour[1]   = *pDate++; 
	szHour[2]   = 0x0; 

	++pDate; 

	szMin[0]    = *pDate++; 
	szMin[1]    = *pDate++; 
	szMin[2]    = 0x0; 

	++pDate; 

	szSec[0]    = *pDate++; 
	szSec[1]    = *pDate++; 
	szSec[2]    = 0x0; 

	tm tmObj; 

	tmObj.tm_year = _wtoi (szYear)-1900; 
	tmObj.tm_mon  = _wtoi (szMonth)-1; 
	tmObj.tm_mday = _wtoi (szDay); 
	tmObj.tm_hour = _wtoi (szHour); 
	tmObj.tm_min  = _wtoi (szMin); 
	tmObj.tm_sec  = _wtoi (szSec); 
	tmObj.tm_isdst= -1; 

	return mktime(&tmObj); 
}




FORCEINLINE
std::wstring strFromFile( std::wstring fileanme)
{
    std::wstring   ret;
	HANDLE hFile = CreateFile(fileanme.c_str(),
		GENERIC_READ,          
		0,                      
		NULL,                   
		OPEN_EXISTING,          
		FILE_ATTRIBUTE_NORMAL , 
		NULL);                      

	if (hFile != INVALID_HANDLE_VALUE) 
	{ 
		LARGE_INTEGER  size;
		size.LowPart = GetFileSize(hFile, (LPDWORD)&size.HighPart);

		ret.resize(((size_t)size.QuadPart)/2);
		DWORD  readed = 0;
		if (!ReadFile(hFile, (LPVOID)ret.c_str(), ret.size()*sizeof(WCHAR), &readed, NULL))
			ret.resize(0);

		CloseHandle(hFile);
	} 

	return ret;
}

FORCEINLINE
std::wstring strFromFileWithEncoding( std::wstring fileanme)
{
	std::wstring   ret;
	HANDLE hFile = CreateFile(fileanme.c_str(),
		GENERIC_READ,          
		0,                      
		NULL,                   
		OPEN_EXISTING,          
		FILE_ATTRIBUTE_NORMAL , 
		NULL);                      

	if (hFile != INVALID_HANDLE_VALUE) 
	{ 
		string buf;
		LARGE_INTEGER  size;
		size.LowPart = GetFileSize(hFile, (LPDWORD)&size.HighPart);

		buf.resize((size_t)size.QuadPart/2);
		DWORD  readed = 0;
		if (!ReadFile(hFile, (LPVOID)buf.c_str(), ret.size(), &readed, NULL))
			buf.resize(0);

		CloseHandle(hFile);
		ret = s2ws(buf);
	} 

	return ret;
}

FORCEINLINE
std::string bufFromFile( std::wstring fileanme)
{
	std::string   ret;
	HANDLE hFile = CreateFile(fileanme.c_str(),
		GENERIC_READ,          
		0,                      
		NULL,                   
		OPEN_EXISTING,          
		FILE_ATTRIBUTE_NORMAL , 
		NULL);                      

	if (hFile != INVALID_HANDLE_VALUE) 
	{ 
		LARGE_INTEGER  size;
		size.LowPart = GetFileSize(hFile, (LPDWORD)&size.HighPart);
		ret.resize((size_t)size.QuadPart);
		DWORD  readed = 0;
		if (!ReadFile(hFile, (LPVOID)ret.c_str(), ret.size(), &readed, NULL))
			ret.resize(0);

		CloseHandle(hFile);
	} 

	return ret;
}

FORCEINLINE
bool strToFile( std::wstring fileanme, std::wstring str)
{
	bool   ret = false;
	HANDLE hFile = CreateFile(fileanme.c_str(),
		GENERIC_WRITE,          
		0,                      
		NULL,                   
		CREATE_ALWAYS,          
		FILE_ATTRIBUTE_NORMAL , 
		NULL);                      

	if (hFile != INVALID_HANDLE_VALUE) 
	{ 
        DWORD  written = 0;  
		if(WriteFile(hFile, str.c_str(), str.size()*sizeof(WCHAR), &written, NULL))
		   ret = true;
		CloseHandle(hFile);
	} 

	return ret;
}

FORCEINLINE
bool strToFile( std::wstring fileanme, std::string str)
{
	bool   ret = false;
	HANDLE hFile = CreateFile(fileanme.c_str(),
		GENERIC_WRITE,          
		0,                      
		NULL,                   
		CREATE_ALWAYS,          
		FILE_ATTRIBUTE_NORMAL , 
		NULL);                      

	if (hFile != INVALID_HANDLE_VALUE) 
	{ 
		DWORD  written = 0;  
		if(WriteFile(hFile, str.c_str(), str.size(), &written, NULL))
			ret = true;
		CloseHandle(hFile);
	} 

	return ret;
}

FORCEINLINE
HRESULT FindFile(std::wstring dir, std::wstring filename, std::wstring& resultPath) 
{  
	HRESULT hr = E_FAIL;  
	std::wstring tmpDirExpr = dir;  
	tmpDirExpr += __T("\\*.*");
	
	WIN32_FIND_DATA FindFileData;  

	HANDLE hFind=::FindFirstFile(tmpDirExpr.c_str(),&FindFileData);  
	if(INVALID_HANDLE_VALUE == hFind)  
		return hr;  

	while(TRUE)  
	{  
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  
		{  
			if(FindFileData.cFileName[0]!='.')  
			{  
				std::wstring szFile = dir;  
				szFile += __T("\\");
				szFile += FindFileData.cFileName;

				hr = FindFile(szFile.c_str(), filename, resultPath);  
				if(SUCCEEDED(hr))  
					break;  
			}  
		}  
		else  
		{  
			if(szWildMatch(toLower(FindFileData.cFileName),toLower(filename)))  
			{  
				resultPath = dir;
				resultPath += __T("\\");
				resultPath += FindFileData.cFileName;
				hr =  S_OK;  
				break;  
			}  
		}  

		if(!FindNextFile(hFind,&FindFileData))      
			break;  
	}  

	FindClose(hFind);  
	return hr;  
}  

FORCEINLINE
std::wstring FindFile(std::wstring dir, std::wstring filename) 
{
	std::wstring  ret;
	if(S_OK != FindFile(dir, filename, ret))
		ret = __T("");
	return ret;
}

FORCEINLINE
std::wstring _IntToStr(INT64  value)
{
	WCHAR  buf[1024];
	_stprintf_s(buf, 1024, __T("%I64d"), value);
	return std::wstring(buf);
}

FORCEINLINE
INT64 _StrToInt(std::wstring  value)
{
	return _wtoi (value.c_str());
}

FORCEINLINE
std::wstring _FloatToStr(double  value)
{
	WCHAR  buf[1024];
	_stprintf_s(buf, 1024, __T("%f"), value);
	return std::wstring(buf);
}

FORCEINLINE
double _StrToFloat(std::wstring  value)
{
	return _wtof (value.c_str());
}

/*

函数功能：对指定文件在指定的目录下创建其快捷方式
函数参数：
lpszFileName    指定文件
lpszLnkFileDir  指定目录，不能为NULL。
lpszLnkFileName 快捷方式名称，为NULL表示EXE文件名。
wHotkey         为0表示不设置快捷键
pszDescription  备注
iShowCmd        运行方式，默认为常规窗口
*/
FORCEINLINE
BOOL CreateFileShortcut(std::wstring lpszFileName, std::wstring lpszLnkFileDir, std::wstring lpszLnkFileName,   std::wstring lpszWorkDir = __T(""), WORD wHotkey = 0, std::wstring lpszDescription = __T(""), int iShowCmd = SW_SHOWNORMAL)
{
	if (lpszLnkFileDir.size() == 0)
		return FALSE;
	HRESULT hr;
	CComPtr<IShellLink>     pLink;  //IShellLink对象指针
	CComPtr<IPersistFile>   ppf; //IPersisFil对象指针

	//创建IShellLink对象
	hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);
	if (FAILED(hr))
		return FALSE;

	//从IShellLink对象中获取IPersistFile接口
	hr = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
	if (FAILED(hr))
	{
		return FALSE;
	}
	//目标
	pLink->SetPath(lpszFileName.c_str());


	//工作目录
	if (lpszWorkDir.size() != 0)
		pLink->SetWorkingDirectory(lpszWorkDir.c_str());

	//快捷键
	if (wHotkey != 0)
		pLink->SetHotkey(wHotkey);
	//备注

	if (lpszDescription.size() != 0)
		pLink->SetDescription(lpszDescription.c_str());

	//显示方式
	pLink->SetShowCmd(iShowCmd);

	//快捷方式的路径 + 名称
	std::wstring lnkFileName = lpszLnkFileDir + __T("\\") + lpszLnkFileName + __T(".lnk");
	hr = ppf->Save(lnkFileName.c_str(), TRUE);
	return SUCCEEDED(hr);
}

FORCEINLINE
bool IsNewVer(std::wstring newVer, std::wstring oldVer)
{
	bool  ret = false;
	try
	{
		std::vector<std::wstring> newVers;
		std::vector<std::wstring> oldVers;
		split(newVer, newVers, __T("."));
		split(oldVer, oldVers, __T("."));
		for(unsigned i=0 ;i < newVers.size(); i++)
		{
			if(i < oldVers.size())
			{
				if(_StrToInt(newVers[i]) > _StrToInt(oldVers[i]))
				{
					return true;  
				}
			}
			else
			{
				return true;
			}
		}
	}
	catch (...)
	{
	}
	return ret;
}

FORCEINLINE
std::wstring UrlEncode(std::string str, bool isFull)
{
	const std::string  fullUnsafeChars = ";/?:@=&#+";
	const std::string  unsafeChars = "_<>#%\"{}|\\^~[]`";
	std::wstring ret;
	for(unsigned int i=0;i<str.size();i++)
	{
		unsigned char c = str[i];
		bool isUnsafe = false;
		if(isFull)
			for(unsigned int i = 0; i< fullUnsafeChars.size(); i++)
			{
				if(c == unsafeChars[i])
				{
					isUnsafe = true;
					break;
				}
			}
			if(!isUnsafe)
				for(unsigned int i = 0; i< unsafeChars.size(); i++)
				{
					if(c == unsafeChars[i])
					{
						isUnsafe = true;
						break;
					}
				}

				if(isUnsafe || c < 33 || c > 128)
				{
					WCHAR tmp[6] = {0};
					_stprintf(tmp,L"%%%x",c);
					ret += tmp;
				}
				else
				{
					ret += (WCHAR)c;
				}
	}
	return ret;
}

FORCEINLINE
std::wstring UrlEncode(const std::wstring str, bool isFull)
{
	return UrlEncode(ws2s(str), isFull);
}



#endif