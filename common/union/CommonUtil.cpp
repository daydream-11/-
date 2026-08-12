#include "stdafx.h"
#include "tlhelp32.h"
#include <time.h>
#include <Shellapi.h>
#include <shobjidl.h>
#include "Public.h"
#include <vector>
#include <ShlObj.h>
#include <Shlwapi.h>
#include "CommonUtil.h"
#include "Type.h"

	// 获取全屏宽度
INT CommonUtil::GetFullScreenWidth(void)
{
	HWND hTrayWnd = NULL; 
	HWND hDeskTopWnd = NULL;
	RECT rectTrayWnd;
	RECT rectDeskTop;
	RECT rcWorkArea;
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, FALSE);
	// 查找任务栏窗口
	hTrayWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	// 查找桌面窗口
	hDeskTopWnd = ::GetDesktopWindow();
	GetWindowRect(hDeskTopWnd, &rectDeskTop);
	GetWindowRect(hTrayWnd, &rectTrayWnd);
	INT nScreenWidth = rectDeskTop.right - rectDeskTop.left;
	return nScreenWidth;
}

// 获取全屏高度
INT CommonUtil::GetFullScreenHeight(void)
{
	HWND hTrayWnd = NULL; 
	HWND hDeskTopWnd = NULL;
	RECT rectTrayWnd;
	RECT rectDeskTop;
	RECT rcWorkArea;
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, FALSE);
	// 查找任务栏窗口
	hTrayWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	// 查找桌面窗口
	hDeskTopWnd = ::GetDesktopWindow();
	GetWindowRect(hDeskTopWnd, &rectDeskTop);
	GetWindowRect(hTrayWnd, &rectTrayWnd);
	INT nScreenHeight = rectDeskTop.bottom - rectDeskTop.top;
	return nScreenHeight;
}

// 获取可以使用屏幕宽度
INT CommonUtil::GetUseScreenWidth(void)
{
	HWND hTrayWnd = NULL; 
	HWND hDeskTopWnd = NULL;
	RECT rectTrayWnd;
	RECT rectDeskTop;
	RECT rcWorkArea;
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, FALSE);
	// 查找任务栏窗口
	hTrayWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	// 查找桌面窗口
	hDeskTopWnd = ::GetDesktopWindow();
	GetWindowRect(hDeskTopWnd, &rectDeskTop);
	GetWindowRect(hTrayWnd, &rectTrayWnd);
	INT nUseScreenWidth = rcWorkArea.right - rcWorkArea.left;
	return nUseScreenWidth;
}


// 获取可以使用屏幕高度
INT CommonUtil::GetUseScreenHeight(void)
{
	HWND hTrayWnd = NULL; 
	HWND hDeskTopWnd = NULL;
	RECT rectTrayWnd;
	RECT rectDeskTop;
	RECT rcWorkArea;
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, FALSE);
	// 查找任务栏窗口
	hTrayWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	// 查找桌面窗口
	hDeskTopWnd = ::GetDesktopWindow();
	GetWindowRect(hDeskTopWnd, &rectDeskTop);
	GetWindowRect(hTrayWnd, &rectTrayWnd);
	INT nUseScreenWidth = rcWorkArea.bottom - rcWorkArea.top;
	return nUseScreenWidth;
}

// 创建目录
BOOL CommonUtil::CreateDirectoryPath(LPCTSTR strDirectoryPath)
{
	INT nLen = (INT)_tcslen(strDirectoryPath);
	TCHAR * szBuffer = new TCHAR[nLen + 1];
	_tcscpy(szBuffer, strDirectoryPath);
	bool bFlag = true;
	for (INT pos = 0, start = 0 ; pos <= nLen ; pos++)
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

// char字符串指针转换为TCHAR字符串指针
void CommonUtil::CHARToTCHAR(const char * pszCHAR, TCHAR * pszTCHAR)
{
#if _UNICODE
	INT nNum = MultiByteToWideChar(CP_ACP, 0, pszCHAR, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszCHAR, -1, pszTCHAR, nNum);
#else
	sprintf(pszTCHAR, "%s", pszCHAR);
#endif
}

// TCHAR字符串指针转换为WCHAR字符串指针
void CommonUtil::TCHARToWCHAR(const TCHAR * pszTCHAR, WCHAR * pszWCHAR)
{
#if _UNICODE
	swprintf(pszWCHAR, L"%s", pszTCHAR);
#else
	//INT nNum = ::MultiByteToWideChar(CP_ACP, 0, pszTCHAR, -1, 0, 0, 0, 0);
	::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszTCHAR, -1, pszWCHAR, MAX_PATH);
#endif
}

// TCHAR字符串指针转换为char字符串指针
void CommonUtil::TCHARToCHAR(const TCHAR * pszTCHAR, char * pszCHAR)
{
#if _UNICODE
	INT nNum = WideCharToMultiByte(CP_OEMCP, 0, pszTCHAR, -1, 0, 0, 0, 0);
	WideCharToMultiByte(CP_OEMCP, NULL, pszTCHAR, -1, pszCHAR, nNum, NULL, FALSE);
#else
	sprintf(pszCHAR, "%s", pszTCHAR);
#endif
}

// Unicode字符串指针转换为UTF-8字符串指针
void CommonUtil::UnicodeToUTF8(const TCHAR * pszTCHAR, char * pszCHAR, INT & nSize)
{
	nSize = WideCharToMultiByte(CP_UTF8, 0, pszTCHAR, -1, 0, 0, 0, 0 );
	::WideCharToMultiByte(CP_UTF8, 0, pszTCHAR, -1, (char*)pszCHAR, nSize, 0, 0 );
}

// UTF8字符串指针转换为TCHAR字符串指针
void CommonUtil::UTF8ToTCHAR(const char * pszCHAR, TCHAR * pszTCHAR)
{
	INT nNum = MultiByteToWideChar(CP_UTF8, 0, pszCHAR, -1, NULL, 0);
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

// 繁体到big5
void CommonUtil::TCHARToBIG5(const TCHAR * pszTCHAR, TCHAR * pszBIG5)
{
	UINT nCodePage = 950; //BIG5
	INT nLength = WideCharToMultiByte(nCodePage, 0, pszTCHAR, -1, NULL, 0, NULL, NULL);
	char * pBuffer = new char[nLength + 1];
	WideCharToMultiByte(nCodePage, 0, pszTCHAR, -1, pBuffer, nLength, NULL, NULL);
	pBuffer[nLength ] = 0;
	CHARToTCHAR(pBuffer, pszBIG5);
	delete[] pBuffer;
	pBuffer = NULL;
}

// TCHAR转换为UTF-8
void CommonUtil::TCHARToUTF8(const TCHAR * pszTCHAR, char * pszCHAR)
{
#if _UNICODE
	int nNum = WideCharToMultiByte(CP_OEMCP, 0, pszTCHAR, -1, 0, 0, 0, 0);
	WideCharToMultiByte(CP_UTF8, NULL, pszTCHAR, -1, pszCHAR, nNum * 3, NULL, FALSE);
#else
	sprintf(pszCHAR, "%s", pszTCHAR);
#endif
}


// 做为解Url使用   
char CommonUtil::CharToInt(char ch)
{  
	if (ch >= '0' && ch <= '9')
	{
		return (char)(ch - '0');
	}
	if (ch >= 'a' && ch <= 'f')
	{
		return (char)(ch - 'a' + 10);
	}
	if (ch >='A' && ch <= 'F')
	{
		return (char)(ch - 'A' + 10);
	}
	return -1;  
}  

// 做为解Url使用
char CommonUtil::StrToBin(char *str)
{  
	char tempWord[2];  
	char chn;  
	// make the B to 11 -- 00001011
	tempWord[0] = CharToInt(str[0]);
	// make the 0 to 0  -- 00000000
	tempWord[1] = CharToInt(str[1]);   
	//to change the BO to 10110000
	chn = (tempWord[0] << 4) | tempWord[1];
	return chn;  
} 

// 把url GB2312解码   
string CommonUtil::UrlGB2312Decode(string str)
{  
	string output="";  
	char tmp[2];  
	int i=0,idx=0,len=str.length();  

	while(i<len){  
		if(str[i]=='%'){  
			tmp[0]=str[i+1];  
			tmp[1]=str[i+2];  
			output += StrToBin(tmp);  
			i=i+3;  
		}  
		else if(str[i]=='+'){  
			output+=' ';  
			i++;  
		}  
		else{  
			output+=str[i];  
			i++;  
		}  
	}  

	return output;  
}  


// 把Url utf8解码   
string CommonUtil::UrlUTF8Decode(string str)
{  
	string output = "";  

	string temp =UrlGB2312Decode(str);//   

	UTF_8ToGB2312(output,(char *)temp.data(),strlen(temp.data()));  

	return output;  

}  

// GB2312 转为 Unicode
void CommonUtil::GB2312ToConveyUnicode(WCHAR * pReturnUnicode,char * strGB2312Value)
{
	::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, strGB2312Value, 2, pReturnUnicode, 1);
	return;
}

// Unicode 转为 UTF8
void CommonUtil::UnicodeToConveyUTF8(char * strReturnUTF8, WCHAR * strInputUnicode)
{
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后
	char * pszChar = (char *)strInputUnicode;

	strReturnUTF8[0] = (0xE0 | ((pszChar[1] & 0xF0) >> 4));
	strReturnUTF8[1] = (0x80 | ((pszChar[1] & 0x0F) << 2)) + ((pszChar[0] & 0xC0) >> 6);
	strReturnUTF8[2] = (0x80 | (pszChar[0] & 0x3F));

	return;
}

// UTF8 转为 Unicode
void CommonUtil::UTF8ToConveyUnicode(WCHAR* pOut,char *pText)
{  
	char* uchar = (char *)pOut;  
	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);  
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);  
	return;  
}  


// Unicode 转为 GB2312
void CommonUtil::UnicodeToConveyGB2312(char* pOut,WCHAR uData) 
{  
	WideCharToMultiByte(CP_ACP, NULL, &uData, 1, pOut, sizeof(WCHAR), NULL, NULL);  
	return;  
}  



//UTF_8 转gb2312   
void CommonUtil::UTF_8ToGB2312(string &pOut, char *pText, int pLen)  
{  
	char buf[4];  
	char* rst = new char[pLen + (pLen >> 2) + 2];  
	memset(buf,0,4);  
	memset(rst,0,pLen + (pLen >> 2) + 2);  

	int i =0;  
	int j = 0;  

	while(i < pLen)  
	{  
		if(*(pText + i) >= 0)  
		{  

			rst[j++] = pText[i++];  
		}  
		else                   
		{  
			WCHAR Wtemp;  


			UTF8ToConveyUnicode(&Wtemp,pText + i);  

			UnicodeToConveyGB2312(buf,Wtemp);  

			unsigned short int tmp = 0;  
			tmp = rst[j] = buf[0];  
			tmp = rst[j+1] = buf[1];  
			tmp = rst[j+2] = buf[2];  

			//newBuf[j] = Ctemp[0];   
			//newBuf[j + 1] = Ctemp[1];   

			i += 3;      
			j += 2;     
		}  

	}  
	rst[j]='\0';  
	pOut = rst;   
	delete []rst;  
}  


// GB2312 转为 UTF-8
void CommonUtil::GB2312ToConveyUTF8(string & strReturnUTF8, char * strGB2312Value, int nGB2312ValueLen)
{
	char szBuffer[4] = {'\0'};
	int i = 0;
	while (i < nGB2312ValueLen)
	{
		// 如果是英文直接复制就可以
		if (strGB2312Value[i] >= 0)
		{
			char szAscii[2] = {'\0'};
			szAscii[0] = (strGB2312Value[i++]);
			strReturnUTF8.append(szAscii);
		}
		else
		{
			WCHAR strReturnUnicode;
			// GB2312 转为 Unicode
			GB2312ToConveyUnicode(&strReturnUnicode, strGB2312Value + i);
			// Unicode 转为 UTF8
			UnicodeToConveyUTF8(szBuffer, &strReturnUnicode);
			//
			strReturnUTF8.append(szBuffer);
			i += 2;
		}
	}

	return;
}

// char转GB2312网址
string CommonUtil::CharToConveyGB2312Url(char * strOriginal)
{
	// char转换后的UTF-8字符
	string strReturnGB2312URL = "";
	int nTextLen = (int)strlen(strOriginal);
	for (int i = 0 ;i < nTextLen ; i++)
	{
		if(isalnum((BYTE)strOriginal[i]))
		{
			char szBuffer[2];
			sprintf(szBuffer,"%c",strOriginal[i]);
			strReturnGB2312URL.append(szBuffer);
		}
		else if (isspace((BYTE)strOriginal[i]))
		{
			strReturnGB2312URL.append("+");
		}
		else
		{
			char szBuffer[4];
			sprintf(szBuffer,"%%%X%X",((BYTE*)strOriginal)[i] >>4,((BYTE*)strOriginal)[i] %16);
			strReturnGB2312URL.append(szBuffer);
		}

	}
	return strReturnGB2312URL;
}

// char转UTF-8网址
string CommonUtil::CharToConveyUTF8URL(char * strOriginal)
{
	// GB2312转换后的UTF-8字符
	string strToConveyUTF8ByGB2312 = "";
	string strReturnUTF8URL = "";
	int nTextLen = (int)strlen(strOriginal);
	GB2312ToConveyUTF8(strToConveyUTF8ByGB2312, strOriginal, nTextLen);

	nTextLen = (int)strToConveyUTF8ByGB2312.size();
	for (int i = 0 ; i < nTextLen; i++)
	{
		if(isalnum((BYTE)strToConveyUTF8ByGB2312.at(i)))
		{
			char szBuffer[2] = {'\0'};
			sprintf(szBuffer, "%c", (BYTE)strToConveyUTF8ByGB2312.at(i));
			strReturnUTF8URL.append(szBuffer);
		}
		else if (isspace((BYTE)strToConveyUTF8ByGB2312.at(i)))
		{
			strReturnUTF8URL.append("+");
		}
		else
		{
			char szBuffer[4];
			sprintf(szBuffer,"%%%X%X",((BYTE)strToConveyUTF8ByGB2312.at(i)) >> 4,((BYTE)strToConveyUTF8ByGB2312.at(i)) % 16);
			strReturnUTF8URL.append(szBuffer);
		}

	}
	return strReturnUTF8URL;
}


// Url转换Char
void CommonUtil::UrlToConveyChar(const char * strUrlSource, char * strUrlDest)
{
	if (strUrlSource == NULL)
	{
		return;
	}
	int i = 0;
	int j = 0;
	const char *pszUrlSource = strUrlSource;
	char p[2] = {'\0'};
	unsigned int nTemp = 0;
	for (i = 0; i < (int)strlen(pszUrlSource); i++)
	{
		memset(p, '\0', 2);
		if (pszUrlSource[i] != '%')
		{
			strUrlDest[j++] = pszUrlSource[i];
			continue;
		}
		else if (pszUrlSource[i] == '%' 
			&& ((pszUrlSource[i + 1] >= '0' && pszUrlSource[i + 1] <= '9') || 
			(pszUrlSource[i + 1] >= 'A' && pszUrlSource[i + 1] <= 'F') || 
			(pszUrlSource[i + 1] >= 'a' && pszUrlSource[i + 1] <= 'f')))
		{
			p[0] = pszUrlSource[++i];
			p[1] = pszUrlSource[++i];
			sscanf(p, "%x", &nTemp);
			sprintf(p, "%c", nTemp);
			strUrlDest[j++] = p[0];
		}
		else
		{
			strUrlDest[j++] = pszUrlSource[i];
		}
	}
	strUrlDest[j] = '\0';
}


// Url转换结果
void CommonUtil::UrlToCoverResult(const char * strUrlSource, char * strUrlResult)
{
	int nWideByte = 0;
	int nGbkLen = 0;
	char * pszBuffer   = NULL;
	char szBuffer[4096] = {'\0'};
	//
	UrlToConveyChar(strUrlSource, szBuffer);
	pszBuffer    = szBuffer;
	int nTextLen = strlen(pszBuffer);
	//
	for (int i = 0; i < nTextLen; i++)
	{
		if (pszBuffer[i] < 0)
		{
			nWideByte++;
		}
	}
	// GBK STR
	nGbkLen = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, pszBuffer, -1, NULL, 0);
	if (nGbkLen > 0 && (nTextLen - (nWideByte / 2)) == (nGbkLen - 1))
	{
		strcpy(strUrlResult, pszBuffer);
	}
	// UTF8 STR
	nGbkLen = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, pszBuffer, -1, NULL, 0);
	if (nGbkLen > 0 &&(nWideByte % 3 == 0) && (nTextLen - (2 * nWideByte / 3)) == (nGbkLen - 1))
	{
		LPWSTR szWChar = new WCHAR[nGbkLen];
		MultiByteToWideChar(CP_UTF8, 0, pszBuffer, -1, szWChar, nGbkLen);
		int astrLen     = WideCharToMultiByte(CP_ACP, 0, szWChar, -1, NULL, 0, NULL, NULL);
		char * szConverted = new char[astrLen];
		WideCharToMultiByte(CP_ACP, 0, szWChar, -1, szConverted, astrLen, NULL, NULL);
		strcpy(strUrlResult, szConverted);
		delete[] szWChar;
		delete[] szConverted;
		return;
	}
	strcpy(strUrlResult, pszBuffer);
}

// 获取随机数(包含两数)
INT CommonUtil::GetRand(INT nMin, INT nMax)
{
	static INT nSeed = ::GetTickCount();

	nSeed = 214013 * nSeed + 2531011;

	if ( nMin < nMax )
	{
		return nMin + (nSeed ^ nSeed >> 15) % (nMax - nMin + 1);
	}
	else
	{
		return nMax + (nSeed ^ nSeed >> 15) % (nMin - nMax + 1);
	}

	return nMax;
}

// 获得今天的日期如：20120921
UINT CommonUtil::GetCurrentDay()
{
	UINT uTime = (UINT)time(NULL);
	return GetMyDate(uTime);
}

// 获得昨天的日期如：20120920
UINT CommonUtil::GetYesterDay()
{
	UINT uTime = (UINT)time(NULL);
	uTime -= 24 * 3600;
	return GetMyDate(uTime);
}

// 获取时间 20120921
UINT CommonUtil::GetMyDate(UINT uTime)
{
	time_t theCurrentTime = (time_t)uTime;
	tm * myCurrentTime = localtime(&theCurrentTime);
	char szTime[10] = {'0'};
	sprintf(szTime, "%d%.2d%.2d", myCurrentTime->tm_year + 1900, myCurrentTime->tm_mon + 1, myCurrentTime->tm_mday);
	UINT uNowTime = (UINT)atoi(szTime);
	return uNowTime;
}

// 获得时间
UINT CommonUtil::GetMyTime(UINT uTime)
{
	time_t theCurrentTime = (time_t)(uTime);
	tm * myCurrentTime = localtime(&theCurrentTime);
	char szTime[10] = {'0'};
	sprintf(szTime, "%d%.2d%.2d", myCurrentTime->tm_hour, myCurrentTime->tm_min, myCurrentTime->tm_sec);
	UINT uNowTime = (UINT)atoi(szTime);
	return uNowTime;
}


// 获得指定时间的日期
VOID CommonUtil::GetAppointDay_YY(UINT uTime, TCHAR *szMyTime)
{
	time_t theCurrentTime = (time_t)(uTime);
	tm * myCurrentTime = localtime(&theCurrentTime);
	_stprintf(szMyTime, _T("%d-%.2d-%.2d"), myCurrentTime->tm_year + 1900, myCurrentTime->tm_mon + 1, myCurrentTime->tm_mday);
}


// 获得指定时间的时间
VOID CommonUtil::GetAppointDay_Time(UINT uTime, TCHAR *szMyTime)
{
	time_t theCurrentTime = (time_t)(uTime);
	tm * myCurrentTime = localtime(&theCurrentTime);
	_stprintf
		(
		szMyTime
		, _T("%d-%.2d-%.2d %.2d:%.2d:%.2d")
		, myCurrentTime->tm_year + 1900
		, myCurrentTime->tm_mon + 1
		, myCurrentTime->tm_mday
		, myCurrentTime->tm_hour
		, myCurrentTime->tm_min
		, myCurrentTime->tm_sec
		);
}

// 获得指定时间的日期获取Unix时间戳
UINT CommonUtil::GetUnixOfTime(const TCHAR *szMyTime)
{
	TCHAR szTempTime[100] = {'\0'};
	TCHAR szDay[100] = {'\0'};
	TCHAR szTime[100] = {'\0'};
	_tcscpy(szTempTime, szMyTime);
	vector<xstring> myVectorString;
	vector<xstring> myVectorDate;
	vector<xstring> myVectorTime;
	TCHAR szSplit[] = _T(" ");
	TCHAR szSplitDate[] = _T("-");
	TCHAR szSplitTime[] = _T(":");
	TCHAR *pSplitBuffer = _tcstok(szTempTime, szSplit);
	while (pSplitBuffer != NULL)
	{
		myVectorString.push_back(pSplitBuffer);
		pSplitBuffer = _tcstok(NULL, szSplit);
	}
	if (myVectorString.size() == 0)
	{
		return 0;
	}
	INT nYear = 0;
	INT nMonth = 0;
	INT nDay = 0;
	INT nHour = 0;
	INT nMinute = 0;
	INT nSecond = 0;
	INT nSize = 0;
	xstring strDate = myVectorString[0];
	_tcscpy(szDay, strDate.c_str());
	if (strDate != _T(""))
	{
		pSplitBuffer = _tcstok(szDay, szSplitDate);
		while (pSplitBuffer != NULL)
		{
			myVectorDate.push_back(pSplitBuffer);
			pSplitBuffer = _tcstok(NULL, szSplitDate);
		}
		nSize = myVectorDate.size();
		if (nSize > 0)
		{
			nYear = _ttoi(myVectorDate[0].c_str());
		}
		if (nSize > 1)
		{
			nMonth = _ttoi(myVectorDate[1].c_str());
		}
		if (nSize > 2)
		{
			nDay = _ttoi(myVectorDate[2].c_str());
		}
	}
	xstring strTime = _T("");
	if (myVectorString.size() > 1)
	{
		strTime = myVectorString[1];
	}
	if (strTime != _T(""))
	{
		_tcscpy(szTime, strTime.c_str());
		pSplitBuffer = _tcstok(szTime, szSplitTime);
		while (pSplitBuffer != NULL)
		{
			myVectorTime.push_back(pSplitBuffer);
			pSplitBuffer = _tcstok(NULL, szSplitTime);
		}
		nSize = myVectorTime.size();
		if (nSize > 0)
		{
			nHour = _ttoi(myVectorTime[0].c_str());
		}
		if (nSize > 1)
		{
			nMinute = _ttoi(myVectorTime[1].c_str());
		}
		if (nSize > 2)
		{
			nSecond = _ttoi(myVectorTime[2].c_str());
		}
	}
	tm myTM;
	myTM.tm_year = nYear - 1900;
	myTM.tm_mon = nMonth - 1;
	myTM.tm_mday = nDay;
	myTM.tm_hour = nHour;
	myTM.tm_min = nMinute;
	myTM.tm_sec = nSecond;
	return mktime(&myTM);
}

// 获取年份(年(4位)2012、2013)
UINT CommonUtil::GetYear()
{
	time_t theCurrentTime = (time_t)time(NULL);
	tm * myCurrentTime = localtime(&theCurrentTime);
	return myCurrentTime->tm_year + 1900;
}


// 获取年份(年(2位)01、02)
UINT CommonUtil::GetYear_YY()
{
	UINT uYear = GetYear();
	UINT uYearYY = uYear -  100 * (uYear / 100);
	return uYearYY;
}

// 获取月份
UINT CommonUtil::GetMonth()
{
	time_t theCurrentTime = (time_t)time(NULL);
	tm * myCurrentTime = localtime(&theCurrentTime);
	return myCurrentTime->tm_mon + 1;
}


// 获取日
UINT CommonUtil::GetDay()
{
	time_t theCurrentTime = (time_t)time(NULL);
	tm * myCurrentTime = localtime(&theCurrentTime);
	return myCurrentTime->tm_mday;
}

// 获取时
UINT CommonUtil::GetHour()
{
	time_t theCurrentTime = (time_t)time(NULL);
	tm * myCurrentTime = localtime(&theCurrentTime);
	return myCurrentTime->tm_hour;
}

// 获取分
UINT CommonUtil::GetMinute()
{
	time_t theCurrentTime = (time_t)time(NULL);
	tm * myCurrentTime = localtime(&theCurrentTime);
	return myCurrentTime->tm_min;
}

// 获取秒
UINT CommonUtil::GetSecond()
{
	time_t theCurrentTime = (time_t)time(NULL);
	tm * myCurrentTime = localtime(&theCurrentTime);
	return myCurrentTime->tm_sec;
}

// 获取星期
UINT CommonUtil::GetWeekday()
{
	time_t theCurrentTime = (time_t)time(NULL);
	tm * myCurrentTime = localtime(&theCurrentTime);
	return myCurrentTime->tm_wday;
}

// 获得今日过了0点多少秒 
UINT CommonUtil::GetTodayAfterSecond()
{
	UINT uTime = (UINT)time(NULL);
	time_t theCurrentTime = (time_t)(uTime);
	tm * myCurrentTime = localtime(&theCurrentTime);
	myCurrentTime->tm_hour = 0;
	myCurrentTime->tm_min = 0;
	myCurrentTime->tm_sec = 0;
	time_t uTodayStartTime = mktime(myCurrentTime);
	UINT nIntervalTime = uTime - uTodayStartTime;
	return nIntervalTime;
}


// 获取x的n次幂
INT CommonUtil::GetXPowerN(INT nX, INT nN)
{
	INT nResult = 1;
	while (nN--)
	{
		nResult *= nX;
	}
	return nResult;
}

// 获取IE安装的位置
BOOL CommonUtil::GetIExplorerExePath(TCHAR *lpszIExplorerExe)
{
	HKEY hKey = NULL;
	LONG lReturn = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\IEXPLORE.EXE"), 0, KEY_READ, &hKey);
	// 此键不存在
	if (lReturn != ERROR_SUCCESS)
	{
		return FALSE;
	}
	TCHAR szKeyValue[MAX_PATH] = {'\0'};
	DWORD nDataLen = MAX_PATH;
	DWORD dwType = REG_SZ;
	::RegQueryValueEx(hKey, _T(""), NULL, &dwType, (LPBYTE)(szKeyValue), &nDataLen);
	if (!::PathFileExists(szKeyValue))
	{
		RegCloseKey(hKey);
		TCHAR szDefaultInstallPath[MAX_PATH] = {'\0'};
		//
		#ifdef _WIN64
				SHGetSpecialFolderPath(NULL, szDefaultInstallPath, CSIDL_PROGRAM_FILESX86, FALSE);
		#else
				SHGetSpecialFolderPath(NULL, szDefaultInstallPath, CSIDL_PROGRAM_FILES, FALSE);
		#endif
		_tcscat(szDefaultInstallPath, _T("\\Internet Explorer\\iexplore.exe"));
		if (!::PathFileExists(szDefaultInstallPath))
		{
			return FALSE;
		}
		_tcscpy(lpszIExplorerExe, szDefaultInstallPath);
		return TRUE;
	}
	_tcscpy(lpszIExplorerExe, szKeyValue);
	RegCloseKey(hKey);
	return TRUE;
}


// 判断默认浏览器是否存在
BOOL CommonUtil::IsDefaultBrowseExist()
{
	HKEY hKey = NULL;
	HKEY hShellKey = NULL;
	HKEY hShellCommandKey = NULL;
	HKEY hOwnKey = NULL;
	LONG lReturn = 0;
	int nTextLen = 0;
	DWORD nDataLen = 0;
	TCHAR szKeyValue[MAX_PATH] = {'\0'};
	TCHAR szSubKey[MAX_PATH] = {'\0'};
	DWORD dwValueName = MAX_PATH;
	DWORD dwValueType = REG_SZ;
	lReturn = ::RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("http"), 0, KEY_READ, &hKey);
	// 此键不存在
	if (lReturn != ERROR_SUCCESS)
	{
		return FALSE;
	}
	lReturn = ::RegOpenKeyEx(hKey, _T("shell"), 0, KEY_READ, &hShellKey);
	// 此键不存在
	if (lReturn != ERROR_SUCCESS)
	{
		return FALSE;
	}
	lReturn = ::RegOpenKeyEx(hShellKey, _T("open\\command"), 0, KEY_READ, &hShellCommandKey);
	// 此键不存在
	if (lReturn != ERROR_SUCCESS)
	{
		return FALSE;
	}
	nDataLen = MAX_PATH;
	DWORD dwType = REG_SZ;
	::RegQueryValueEx(hShellCommandKey, _T(""), NULL, &dwType, (LPBYTE)(szKeyValue), &nDataLen);
	RegCloseKey(hShellKey);
	RegCloseKey(hShellCommandKey);
	TCHAR *lpszLwrKeyValue = _tcslwr(szKeyValue);
	TCHAR *lpszFindValue = _tcsstr(lpszLwrKeyValue, _T("\""));
	if (lpszFindValue == NULL)
	{
		return FALSE;
	}
	lpszLwrKeyValue = lpszFindValue + 1;
	//
	TCHAR *lpszDefaultBrowseExePath = lpszLwrKeyValue;
	//
	lpszFindValue = _tcsstr(lpszLwrKeyValue, _T("\""));
	if (lpszFindValue == NULL)
	{
		return FALSE;
	}
	*lpszFindValue = '\0';
	if (!::PathFileExists(lpszDefaultBrowseExePath))
	{
		return FALSE;
	}
	return TRUE;
}

// 判断是否遨游浏览器为默认的
BOOL CommonUtil::IsMaxthonDefaultBrowse()
{
	HKEY hKey = NULL;
	HKEY hShellKey = NULL;
	HKEY hShellCommandKey = NULL;
	HKEY hOwnKey = NULL;
	LONG lReturn = 0;
	int nTextLen = 0;
	DWORD nDataLen = 0;
	TCHAR szKeyValue[MAX_PATH] = {'\0'};
	TCHAR szSubKey[MAX_PATH] = {'\0'};
	DWORD dwValueName = MAX_PATH;
	DWORD dwValueType = REG_SZ;
	lReturn = ::RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("http"), 0, KEY_READ, &hKey);
	// 此键不存在
	if (lReturn != ERROR_SUCCESS)
	{
		return FALSE;
	}
	lReturn = ::RegOpenKeyEx(hKey, _T("shell"), 0, KEY_READ, &hShellKey);
	// 此键不存在
	if (lReturn != ERROR_SUCCESS)
	{
		return FALSE;
	}
	lReturn = ::RegOpenKeyEx(hShellKey, _T("open\\command"), 0, KEY_READ, &hShellCommandKey);
	// 此键不存在
	if (lReturn != ERROR_SUCCESS)
	{
		return FALSE;
	}
	nDataLen = MAX_PATH;
	DWORD dwType = REG_SZ;
	::RegQueryValueEx(hShellCommandKey, _T(""), NULL, &dwType, (LPBYTE)(szKeyValue), &nDataLen);
	RegCloseKey(hShellKey);
	RegCloseKey(hShellCommandKey);
	TCHAR *lpszLwrKeyValue = _tcslwr(szKeyValue);
	TCHAR *lpszFindMaxthon = _tcsstr(lpszLwrKeyValue, _T("maxthon"));
	if (lpszFindMaxthon == NULL)
	{
		return FALSE;
	}
	return TRUE;
}


// 判断是指定浏览器为默认的
BOOL CommonUtil::IsAppointDefaultBrowse(const TCHAR *lpszBrowseName)
{
	HKEY hKey = NULL;
	HKEY hShellKey = NULL;
	HKEY hShellCommandKey = NULL;
	HKEY hOwnKey = NULL;
	LONG lReturn = 0;
	int nTextLen = 0;
	DWORD nDataLen = 0;
	TCHAR szKeyValue[MAX_PATH] = {'\0'};
	TCHAR szSubKey[MAX_PATH] = {'\0'};
	DWORD dwValueName = MAX_PATH;
	DWORD dwValueType = REG_SZ;
	lReturn = ::RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("htmlfile"), 0, KEY_READ, &hKey);
	// 此键不存在
	if (lReturn != ERROR_SUCCESS)
	{
		return FALSE;
	}
	lReturn = ::RegOpenKeyEx(hKey, _T("shell"), 0, KEY_READ, &hShellKey);
	// 此键不存在
	if (lReturn != ERROR_SUCCESS)
	{
		return FALSE;
	}
	lReturn = ::RegOpenKeyEx(hShellKey, _T("open\\command"), 0, KEY_READ, &hShellCommandKey);
	// 此键不存在
	if (lReturn != ERROR_SUCCESS)
	{
		return FALSE;
	}
	nDataLen = MAX_PATH;
	DWORD dwType = REG_SZ;
	::RegQueryValueEx(hShellCommandKey, _T(""), NULL, &dwType, (LPBYTE)(szKeyValue), &nDataLen);
	RegCloseKey(hShellKey);
	RegCloseKey(hShellCommandKey);
	TCHAR *lpszLwrKeyValue = _tcslwr(szKeyValue);
	TCHAR *lpszFind = _tcsstr(lpszLwrKeyValue, lpszBrowseName);
	if (lpszFind == NULL)
	{
		return FALSE;
	}
	return TRUE;
}


// 判断是否没有问题的浏览器为默认的
BOOL CommonUtil::IsNoQuestionDefaultBrowse()
{
	if (IsAppointDefaultBrowse(_T("360se.exe")))
	{
		return TRUE;
	}
	if (IsAppointDefaultBrowse(_T("sogouexplorer.exe")))
	{
		return TRUE;
	}
	return FALSE;
}

// 打开浏览网页
VOID CommonUtil::CreateBrowseUrlByUser(LPCTSTR pszURL)
{
	if( _tcslen(pszURL) == 0)
	{
		return;
	}
	if (IsNoQuestionDefaultBrowse())
	{
		CreateBrowseUrlByDefault(pszURL);
		return;
	}
	CreateBrowseUrlByIE(pszURL);
}

// 打开浏览网页通过IE
VOID CommonUtil::CreateBrowseUrlByIE(LPCTSTR pszURL)
{
	// 如果默认浏览器是遨游，则用IE打开
	TCHAR szIEXploreExe[MAX_PATH] = {'\0'};
	BOOL bReturn = CommonUtil::GetIExplorerExePath(szIEXploreExe);
	if (!bReturn)
	{
		CreateBrowseUrlByDefault(pszURL);
		return;
	}
	TCHAR szRunExe[2000] = {'\0'};
	_stprintf(szRunExe, _T("\"%s\" %s"), szIEXploreExe, pszURL);
	CreateRunProcess(szRunExe);
}


// 打开浏览网页通过默认浏览器
VOID CommonUtil::CreateBrowseUrlByDefault(LPCTSTR pszURL)
{
	TCHAR szChar[2000];
	::GetWindowsDirectory(szChar, 2000);
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
}


// 打开浏览网页
VOID CommonUtil::CreateBrowseUrl(LPCTSTR pszURL)
{
	BOOL bDefaultBrowseExist = IsDefaultBrowseExist();
	if (bDefaultBrowseExist)
	{
		CreateBrowseUrlByDefault(pszURL);
	}
	else
	{
		CreateBrowseUrlByIE(pszURL);
	}
}

// 打开进程
VOID CommonUtil::CreateUIProcess(LPCTSTR strProcess)
{
	if( _tcslen(strProcess) == 0)
	{
		return;
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
	
}

// 打开进程
VOID CommonUtil::CreateRunProcess(LPCTSTR strProcess)
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
		return;	
	}
	CloseHandle(pi.hProcess );
	CloseHandle(pi.hThread );
}

// 打开进程
bool CommonUtil::CreateRunProcessRes(LPCTSTR strProcess)
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
		return false;	
	}
	CloseHandle(pi.hProcess );
	CloseHandle(pi.hThread );

	return true;
}

// 创建运行进程（处于等待状态）
VOID CommonUtil::CreateWaitProcess(LPCTSTR strProcess)
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
		return;	
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	DWORD bSuccess;
	GetExitCodeProcess (pi.hProcess, &bSuccess);
	CloseHandle(pi.hProcess );
	CloseHandle(pi.hThread );
	return;
}

// 创建按用户的进程
VOID CommonUtil::CreateUserProcess(TCHAR *lpszProcess)
{
	BOOL bResult = FALSE;
	HANDLE hToken = GetTokenOfName(_T("EXPLORER.EXE"));
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	//
	PROCESS_INFORMATION pi;
	bResult = CreateProcessAsUser(hToken, NULL, lpszProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	//
	CloseHandle(pi.hProcess); 
	CloseHandle(pi.hThread);
	CloseHandle(hToken);
}


// 创建管理员进程
BOOL CommonUtil::CreateAdminProcess(LPCTSTR strProcess, LPCTSTR strParameter)
{
	SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };
	sei.lpVerb = _T("runas");
	sei.lpFile = strProcess;
	sei.fMask = SEE_MASK_DOENVSUBST;
	sei.nShow = SW_SHOWNORMAL;
	sei.lpParameters = strParameter;

	if (!ShellExecuteEx(&sei)) {
		DWORD dwStatus = GetLastError();

		if (dwStatus == ERROR_CANCELLED) {
			// The user refused to allow privileges elevation.
		}
		else
			if (dwStatus == ERROR_FILE_NOT_FOUND) {
				// The file defined by lpFile was not found and
				// an error message popped up.
			}
	}
	return TRUE;
}

// 获取进程ID
INT CommonUtil::GetProcessIDOfName(TCHAR *lpszProcessName)
{
	if (lpszProcessName == NULL)
	{
		return 0;
	}
	TCHAR szProcessName[MAX_PATH] = {'\0'};
	TCHAR szExeFile[MAX_PATH] = {'\0'};
	_tcscpy(szProcessName, lpszProcessName);
	const TCHAR *lpUprProcessName = _tcsupr(szProcessName);
	BOOL bReturn = FALSE; 
	HANDLE hProcessSnap = NULL; 
	PROCESSENTRY32 myProcessEntry32 = {'\0'};
	//
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	//
	myProcessEntry32.dwSize = sizeof(PROCESSENTRY32); 
	//
	if (Process32First(hProcessSnap, &myProcessEntry32)) 
	{  
		do 
		{
			_tcscpy(szExeFile, myProcessEntry32.szExeFile);
			const TCHAR *lpUprExeFile = _tcsupr(szExeFile);
			if (_tcscmp(lpUprExeFile, lpUprProcessName) == 0)
			{
				CloseHandle (hProcessSnap); 
				return myProcessEntry32.th32ProcessID;
			}
		} 
		while (Process32Next(hProcessSnap, &myProcessEntry32)); 
	}
	CloseHandle (hProcessSnap); 
	return 0;
}


// 获取进程个数
INT CommonUtil::GetProcessNumOfName(TCHAR *lpszProcessName)
{
	INT nProcessNum = 0;

	BOOL bReturn = FALSE; 
	HANDLE hProcessSnap = NULL; 
	PROCESSENTRY32 myProcessEntry32 = {'\0'};
	//
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return nProcessNum;
	}
	//
	myProcessEntry32.dwSize = sizeof(PROCESSENTRY32); 
	//
	if (Process32First(hProcessSnap, &myProcessEntry32)) 
	{  
		do 
		{
			if (_tcscmp(_tcsupr(myProcessEntry32.szExeFile), _tcsupr(lpszProcessName)) == 0)
			{
				nProcessNum ++;
			}
		} 
		while (Process32Next(hProcessSnap, &myProcessEntry32)); 
	}
	CloseHandle (hProcessSnap); 
	return nProcessNum;
}

// 获取进程相关的Token
HANDLE CommonUtil::GetTokenOfProcessID(DWORD dwProcessID) 
{
	HANDLE hProcess	  = NULL;
	HANDLE hToken     = NULL;
	HANDLE g_hToken   = NULL;

	PSECURITY_DESCRIPTOR pSD = NULL;

	try {	
		// Get the handle to the process
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID);
		if (hProcess == NULL) 	 return NULL;

		// Get the token (All access so we can change and launch things
		if (!OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken)) 
		{
			CloseHandle(hProcess);
			return NULL;
		}

		// Get memory for an SD
		pSD = (PSECURITY_DESCRIPTOR) GlobalAlloc(GPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
		if (pSD == NULL) 
		{
			CloseHandle(hToken);
			CloseHandle(hProcess);
			return NULL;
		}

		// Initialize it
		if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION)) 
		{
			GlobalFree(pSD);
			CloseHandle(hToken);
			CloseHandle(hProcess);
			return NULL;
		}

		// Add a NULL DACL to the security descriptor..
		if (!SetSecurityDescriptorDacl(pSD, TRUE, (PACL) NULL, FALSE)) 
		{
			GlobalFree(pSD);
			CloseHandle(hToken);
			CloseHandle(hProcess);
			return NULL;
		}

		// We made the security descriptor just in case they want a duplicate.
		// We make the duplicate have all access to everyone.
		SECURITY_ATTRIBUTES sa;
		sa.nLength              = sizeof(sa);
		sa.lpSecurityDescriptor = pSD;
		sa.bInheritHandle       = TRUE;

		// If the user chooses not to copy the token, then changes made to it
		// will effect the owning process
		//        if (IDNO == ::MessageBox(NULL, TEXT("Would you like to make a copy of ")
		//            TEXT("this process token?\n(Selecting \"No\" will cause the ")
		//            TEXT("\"AdjustToken\" and \"SetToken\"\nfeatures to affect the ")
		//            TEXT("owning process.) "), TEXT("Duplicate Token?"), MB_YESNO)) 

		// Duplicate the token
		if (!DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, &sa,
			SecurityImpersonation, TokenPrimary, &g_hToken)) 
		{
			CloseHandle(hToken);
			CloseHandle(hProcess);
			GlobalFree(pSD);
			return NULL;
		}
	} 
	catch(...) 
	{}

	CloseHandle(hToken);
	CloseHandle(hProcess);
	GlobalFree(pSD);
	return g_hToken;
}


// 获取进程相关的Token
HANDLE CommonUtil::GetTokenOfName(TCHAR *lpszProcessName)
{
	INT nProcessID = GetProcessIDOfName(lpszProcessName);
	if (nProcessID == 0)
	{
		return NULL;
	}
	return GetTokenOfProcessID(nProcessID);
}

// 从字符串中获取文件后缀名
VOID CommonUtil::GetFileNameOfFileFullPath(const TCHAR *lpszFileFullPath, TCHAR *lpszFileName)
{
	TCHAR szTempFileFullPath[MAX_PATH] = {'\0'};
	_tcscpy(szTempFileFullPath, lpszFileFullPath);
	TCHAR *lpszTempValue = _tcsrchr(szTempFileFullPath, '\\');
	if (lpszTempValue == NULL)
	{
		lpszTempValue = _tcsrchr(szTempFileFullPath, '/');
		if (lpszTempValue == NULL)
		{
			return;
		}
		_tcscpy(lpszFileName, lpszTempValue + 1);
		return;
	}
	_tcscpy(lpszFileName, lpszTempValue + 1);
}


// 从字符串中获取文件的名字
VOID CommonUtil::GetFileNameOnlyName(TCHAR *lpszFileName, TCHAR *lpszOnlyName)
{
	TCHAR szTempFileName[MAX_PATH] = {'\0'};
	_tcscpy(szTempFileName, lpszFileName);
	TCHAR *lpszTempValue = _tcsrchr(szTempFileName, '.');
	if (lpszTempValue == NULL)
	{
		_tcscpy(lpszOnlyName, szTempFileName);
		return;
	}
	*lpszTempValue = '\0';
	_tcscpy(lpszOnlyName, szTempFileName);
}

// 从字符串中获取文件后缀名
VOID CommonUtil::GetFileNameExtension(TCHAR *lpszFileName, TCHAR *lpszExtension)
{
	TCHAR *lpszTempValue = _tcsrchr(lpszFileName, '.');
	if (lpszTempValue == NULL)
	{
		return;
	}
	_tcscpy(lpszExtension, lpszTempValue);
}

// 从字符串中获取文件名
VOID CommonUtil::GetFileNameFromHttpString(const TCHAR *lpszString, TCHAR *lpszFileName)
{
	TCHAR szTempString[1000] = {'\0'};
	_tcscpy(szTempString, lpszString);
	const TCHAR *lpszFind = _tcsrchr(lpszString, '/');
	if (lpszFind == NULL)
	{
		return;
	}
	_tcscpy(lpszFileName,  lpszFind + 1);
}


// 获取Json格式的其实位置
char* CommonUtil::GetJsonStartPosition(char *pszResult)
{
	int nSize = (int)strlen(pszResult);
	char szBegin[MAX_PATH] = "{";
	int nBegin = 0;
	int nSameNum = 0;
	BOOL bFind = FALSE;
	for (int i = 0; i < nSize; i++)
	{
		if (pszResult[i] == szBegin[0])
		{
			if (bFind)
			{
				break;
			}
			nBegin = i;
			nSameNum = 0;
			for (int j = 0; j < 1; j++)
			{
				if (pszResult[nBegin + j] == szBegin[j])
				{
					nSameNum++;
					if (nSameNum == 1)
					{
						bFind = TRUE;
						break;
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
	return pszResult + nBegin;
}

// 移动文件
void CommonUtil::MoveFileOfReName(const TCHAR * lpszExistingFileName, const TCHAR * lpNewFileName, bool bDeleteOrg)
{
	TCHAR szExistingFileName[MAX_PATH] = {'\0'};
	TCHAR szNewFileName[MAX_PATH] = {'\0'};
	_tcscpy(szExistingFileName, lpszExistingFileName);
	_tcscpy(szNewFileName, lpNewFileName);
	_tcslwr(szExistingFileName);
	_tcslwr(szNewFileName);
	if (_tcscmp(szExistingFileName, szNewFileName) == 0)
	{
		return;
	}
	BOOL bReturn = FALSE;
	int nCopyTimes = 0;
	while (TRUE)
	{
		TCHAR szBakNewFileName[MAX_PATH] = {'\0'};
		if (nCopyTimes == 0)
		{
			//
			_stprintf(szBakNewFileName, _T("%s.bak"), lpNewFileName);
		}
		else
		{
			//
			_stprintf(szBakNewFileName, _T("%s.bak%d"), lpNewFileName, nCopyTimes);
		}
		//
		if (PathFileExists(szBakNewFileName))
		{
			::DeleteFile(szBakNewFileName);
		}
		//
		_trename(lpNewFileName, szBakNewFileName);
		// 暂时隐掉便于调试，完全开发完再打开2014.9.29
		bReturn = CopyFile(lpszExistingFileName, lpNewFileName, 0);
		if (bReturn)
		{
			//
			::MoveFileEx(szBakNewFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
			break;
		}
		if (bDeleteOrg)
		{
			::DeleteFile(szBakNewFileName);
			::DeleteFile(lpszExistingFileName);
		}
		//
		::MoveFileEx(szBakNewFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
		if (nCopyTimes >= 10)
		{
			return;
		}
		nCopyTimes++;
	}
}


// 复制新文件
void CommonUtil::CopyFileOfNewFile(const TCHAR * lpszExistingFileName, const TCHAR * lpNewFileName)
{
	TCHAR szExistingFileName[MAX_PATH] = {'\0'};
	TCHAR szNewFileName[MAX_PATH] = {'\0'};
	_tcscpy(szExistingFileName, lpszExistingFileName);
	_tcscpy(szNewFileName, lpNewFileName);
	_tcslwr(szExistingFileName);
	_tcslwr(szNewFileName);
	if (_tcscmp(szExistingFileName, szNewFileName) == 0)
	{
		return;
	}
	BOOL bReturn = FALSE;
	int nCopyTimes = 0;
	while (TRUE)
	{
		TCHAR szBakNewFileName[MAX_PATH] = {'\0'};
		if (nCopyTimes == 0)
		{
			//
			_stprintf(szBakNewFileName, _T("%s.bak"), lpNewFileName);
		}
		else
		{
			//
			_stprintf(szBakNewFileName, _T("%s.bak%d"), lpNewFileName, nCopyTimes);
		}
		//
		if (PathFileExists(szBakNewFileName))
		{
			::DeleteFile(szBakNewFileName);
		}
		//
		_trename(lpNewFileName, szBakNewFileName);
		//
		::DeleteFile(szBakNewFileName);
		//
		bReturn = CopyFile(lpszExistingFileName, lpNewFileName, 0);
		if (bReturn)
		{
			//
			::MoveFileEx(szBakNewFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
			break;
		}
		//
		::MoveFileEx(szBakNewFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
		if (nCopyTimes >= 10)
		{
			return;
		}
		nCopyTimes++;
	}
	::MoveFileEx(lpszExistingFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
}

// 重命名文件，重启后删除
void CommonUtil::ReNameOfReRebootDelete(TCHAR * lpszExistingFileName)
{
	TCHAR *lpszFindDel = _tcsstr(lpszExistingFileName, _T(".del"));
	if (lpszFindDel != NULL)
	{
		::MoveFileEx(lpszExistingFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
		return;
	}
	BOOL bReturn = FALSE;
	int nCopyTimes = 0;
	while (TRUE)
	{
		BOOL bFlag = TRUE;
		TCHAR szBakNewFileName[MAX_PATH] = {'\0'};
		if (nCopyTimes == 0)
		{
			//
			_stprintf(szBakNewFileName, _T("%s.del"), lpszExistingFileName);
		}
		else
		{
			//
			_stprintf(szBakNewFileName, _T("%s.del%d"), lpszExistingFileName, nCopyTimes);
		}
		//
		if (PathFileExists(szBakNewFileName))
		{
			bFlag = ::DeleteFile(szBakNewFileName);
		}
		if (!bFlag)
		{
			if (nCopyTimes >= 10)
			{
				return;
			}
			nCopyTimes++;
			continue;
		}
		//
		_trename(lpszExistingFileName, szBakNewFileName);
		//
		::MoveFileEx(szBakNewFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
		return;
	}
	::MoveFileEx(lpszExistingFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
}


// 删除文件（当前删除不了，移动当临时目录，重启后删除）
void CommonUtil::DeleteFileOfRemoveTempRebotDelete(const TCHAR * lpszExistingFileName)
{
	if (!::PathFileExists(lpszExistingFileName))
	{
		return;
	}
	BOOL bDeleteFlag = ::DeleteFile(lpszExistingFileName);
	if (bDeleteFlag)
	{
		return;
	}
	TCHAR szFileName[MAX_PATH] = {'\0'};
	TCHAR szTempPath[MAX_PATH] = {'\0'};
	//
	GetTempPath(MAX_PATH, szTempPath);
	//
	GetFileNameOfFileFullPath(lpszExistingFileName, szFileName);
	//
	BOOL bReturn = FALSE;
	int nCopyTimes = 0;
	while (TRUE)
	{
		BOOL bFlag = TRUE;
		TCHAR szBakNewFileName[MAX_PATH] = {'\0'};
		if (nCopyTimes == 0)
		{
			//
			_stprintf(szBakNewFileName, _T("%s%s.del"), szTempPath, szFileName);
		}
		else
		{
			//
			_stprintf(szBakNewFileName, _T("%s%s.del%d"), szTempPath, szFileName, nCopyTimes);
		}
		//
		if (PathFileExists(szBakNewFileName))
		{
			bFlag = ::DeleteFile(szBakNewFileName);
		}
		if (!bFlag)
		{
			if (nCopyTimes >= 10)
			{
				return;
			}
			nCopyTimes++;
			continue;
		}
		//
		_trename(lpszExistingFileName, szBakNewFileName);
		//
		::MoveFileEx(szBakNewFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
		return;
	}
}

// 获取错误信息
xstring CommonUtil::GetErrorMessage()
{
	xstring strError = _T("");
	LPVOID lpMsgBuf;
	if (
		FormatMessage
		( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0,
		NULL
		)
		)
	{
		strError = (LPTSTR)lpMsgBuf;
	}
	LocalFree(lpMsgBuf );
	return strError;
}

// 创建注册表运行一次程序
BOOL CommonUtil::CreateRegeditRunOnce(const TCHAR *lpszRunOneName, const TCHAR *lpszRunOneExe)
{
	HKEY hKey = NULL;
	HKEY hSubKey = NULL;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion"), 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
	{
		return FALSE;
	}
	if ((RegOpenKeyEx(hKey, _T("RunOnce"), 0, KEY_ALL_ACCESS, &hSubKey) == ERROR_SUCCESS || RegCreateKeyExA(hKey, "RunOnceEx", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hSubKey, NULL) == ERROR_SUCCESS))
	{
		RegSetValueEx(hSubKey, lpszRunOneName, 0, REG_SZ, (LPBYTE)lpszRunOneExe, (DWORD)_tcslen(lpszRunOneExe) * 2);
		RegCloseKey(hSubKey);
		RegCloseKey(hKey);
		return TRUE;
	}
	return FALSE;
}


// 拷贝文件到临时目录
VOID CommonUtil::CopyFileToTempPath()
{
	TCHAR szExeName[MAX_PATH]={'\0'};
	TCHAR szTempPath[MAX_PATH]={'\0'};
	TCHAR szTempFile[MAX_PATH]={'\0'};
	TCHAR szModuleFileName[MAX_PATH]={'\0'};
	INT nCopyTimes = 0;
	//
	GetTempPath(MAX_PATH, szTempPath);
	GetModuleFileName(NULL, szModuleFileName, MAX_PATH);
	_tcscpy(szExeName, _tcsrchr(szModuleFileName, '\\') + 1);
	_tcscpy(szTempFile, szTempPath);
	_tcscat(szTempFile, szExeName);
	//
	while (!CopyFile(szModuleFileName, szTempFile, 0))
	{
		TCHAR szNewFileName[MAX_PATH] = {'\0'};
		//
		_stprintf(szNewFileName, _T("%s.bak%d"), szTempFile, nCopyTimes);
		//
		_trename(szTempFile, szNewFileName);
		//
		::MoveFileEx(szNewFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT | MOVEFILE_REPLACE_EXISTING);
		if (nCopyTimes >= 10)
		{
			return;
		}
		nCopyTimes++;
	}
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
void CommonUtil::WriteDebugLog(TCHAR * strMsg, ...)
{

#ifndef _DEBUG
	//return;
#endif
	TCHAR szTempPath[MAX_PATH] = {'\0'};
	//GetTempPath(MAX_PATH, szTempPath);
	GetModuleFileName(NULL, szTempPath, MAX_PATH);
	*(_tcsrchr(szTempPath, '\\') + 1) = '\0';

	int nMsgMaxLen = 500;
	FILE * pFile;
	TCHAR szMsg[500] = {'\0'};
	TCHAR szLogFile[MAX_PATH];
	_stprintf(szLogFile, _T("%sxxxx.log"), szTempPath);
	/*if (!::PathFileExists(szLogFile))
	{
		return;
	}*/
	_stprintf(szLogFile, _T("%slog.txt"), szTempPath);
	/*static int nStaticNum = 0;
	if (nStaticNum == 0)
	{
		::MessageBox(NULL, szLogFile, NULL, NULL);
		nStaticNum++;
	}*/
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

// string 装换为xstring
xstring CommonUtil::StrToXStr(const string & str)
{
	wstring result;
#ifdef _UNICODE
	setlocale(LC_ALL, "chs");
	const char* _Source = str.c_str();
	size_t _Dsize = str.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	result = _Dest;
	delete []_Dest;

	setlocale(LC_ALL, "C");
#else
	result = str;
#endif
	 	return result;
}
// xstring 装换为string
string CommonUtil::XStrToStr(const xstring& xstr)
{
	string result;
#ifdef _UNICODE
	string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";

	setlocale(LC_ALL, "chs");

	const wchar_t* _Source = xstr.c_str();
	size_t _Dsize = 2 * xstr.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	result = _Dest;
	delete []_Dest;

	setlocale(LC_ALL, curLocale.c_str());
#else
	result = str;
#endif
		return result;
}
// 一个单引号变两个单引号
BOOL CommonUtil::QuotesOneToTwo(xstring& xstr)
{
	BOOL bHaveQuotes = FALSE;
	xstring temp(xstr);
	xstring strComp = _T("");
	xstring::size_type pos = xstr.find(_T("'"));
	while(pos != xstring::npos)
	{
		int len = xstr.length();
		strComp += xstr.substr(0, pos) + _T("''");
		xstr = xstr.substr(pos +1, len - pos -1);
		pos = xstr.find(_T("'"));
		bHaveQuotes = TRUE;
	}
	strComp += xstr;
	xstr = strComp;
	return bHaveQuotes;
}
#ifdef _UNICODE
BOOL CommonUtil::QuotesOneToTwo(string& xstr)
{
	BOOL bHaveQuotes = FALSE;
	string temp(xstr);
	string strComp = "";
	string::size_type pos = xstr.find("'");
	while(pos != string::npos)
	{
		int len = xstr.length();
		strComp += xstr.substr(0, pos) + "''";
		xstr = xstr.substr(pos +1, len - pos -1);
		pos = xstr.find("'");
		bHaveQuotes = TRUE;
	}
	strComp += xstr;
	xstr = strComp;
	return bHaveQuotes;
}
#endif
// 去掉单引号
void CommonUtil::DeleteQuotes(xstring& xstr)
{
	for (xstring::iterator it = xstr.begin(); it != xstr.end();)
	{
		if (*it != _T('\''))
		{
			++it;
			continue;
		}
		it = xstr.erase(it);
	}
}
// 文件中是否包含标示符
BOOL CommonUtil::IsContainIdentifier(const TCHAR * pszFileName)
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
	return FALSE;
}

tm CommonUtil::ConvertFormatStringToTime(const WCHAR* timeStr)
{
    tm time = {0};
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    swscanf_s(timeStr,_T("%d-%d-%d %d:%d:%d"), &year, &month, &day, &hour, &minute, &second);
    time.tm_year  = year - 1900;
    time.tm_mon   = month - 1;
    time.tm_mday  = day;
    time.tm_hour  = hour;
    time.tm_min   = minute;
    time.tm_sec   = second;
    return time;
}

// 是否含有字符a-z
BOOL CommonUtil::IsContainAToZ(const xstring& strWord)
{
	foreach_const(xstring, strWord, itor)
	{
		if ( *itor >= _T('a') && *itor <= _T('z'))
		{
			return TRUE;
		}
	}
	return FALSE;
}

// 检测进程中某个程序的数量
int CommonUtil::GetProcessCount(const TCHAR* szExeName)
{
	TCHAR sztarget[MAX_PATH]={0};
	lstrcpy(sztarget, szExeName);
	CharLowerBuff(sztarget, MAX_PATH);

	int nCount = 0;
	PROCESSENTRY32 my;
	HANDLE l = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (((int)l) != -1)
	{
		my.dwSize = sizeof(my);
		if (Process32First(l, &my))
		{
			do
			{
				CharLowerBuff(my.szExeFile, MAX_PATH);
				TCHAR *szTemp = _tcsstr(my.szExeFile, sztarget);
				if (szTemp != NULL)
				{
					nCount++;
				}
			}while (Process32Next(l, &my));
		}
		CloseHandle(l);
	}
	return nCount;
}

BOOL CommonUtil::IsOnlyHaveLowerCase(const TCHAR * pszValue)
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

// 确认是否是Vista版的操作系统
BOOL CommonUtil::IsVistaOrWin7System()
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

// 是否含有某个字符
BOOL CommonUtil::IsContainChar(const xstring& strWord, const TCHAR ch)
{
	foreach_const(xstring, strWord, it)
	{
		if ( *it == ch)
		{
			return TRUE;
		}
	}
	return FALSE;
}

// 重新设置剪贴板信息
BOOL CommonUtil::SetClipboardDataInfo(HWND hWnd, const TCHAR * strClipboardData)
{
	BOOL bFlag = FALSE;
	bFlag = ::OpenClipboard(hWnd);
	if (!bFlag)
	{
		return FALSE;
	}
	bFlag = ::EmptyClipboard();
	if (!bFlag)
	{
		return FALSE;
	}
	HANDLE hGlobal;
	TCHAR * pGlobal;
	hGlobal = GlobalAlloc(GHND | GMEM_SHARE, (_tcslen(strClipboardData) * sizeof(TCHAR)) + 10);
	if (hGlobal == NULL)	
	{
		return FALSE;
	}
	pGlobal = (LPTSTR)GlobalLock(hGlobal);
	_tcscpy(pGlobal, strClipboardData);
	GlobalUnlock(hGlobal);
	SetClipboardData(CF_UNICODETEXT, hGlobal);
	bFlag = CloseClipboard();
	if (!bFlag)
	{
		return FALSE;
	}
	return TRUE;
}


// 重新设置剪贴板信息
BOOL CommonUtil::SetClipboardDataCharInfo(HWND hWnd, const CHAR * strClipboardData)
{
	BOOL bFlag = FALSE;
	bFlag = ::OpenClipboard(hWnd);
	if (!bFlag)
	{
		return FALSE;
	}
	bFlag = ::EmptyClipboard();
	if (!bFlag)
	{
		return FALSE;
	}
	HANDLE hGlobal;
	CHAR * pGlobal;
	hGlobal = GlobalAlloc(GHND | GMEM_SHARE, (strlen(strClipboardData) * sizeof(CHAR)) + 1);
	if (hGlobal == NULL)	
	{
		return FALSE;
	}
	pGlobal = (LPSTR)GlobalLock(hGlobal);
	strcpy(pGlobal, strClipboardData);
	GlobalUnlock(hGlobal);
	SetClipboardData(CF_TEXT, hGlobal);
	bFlag = CloseClipboard();
	if (!bFlag)
	{
		return FALSE;
	}
	return TRUE;
}

// 重新获取剪贴板信息
BOOL CommonUtil::GetClipboardDataCharInfo(HWND hWnd, TCHAR * strClipboardData)
{
	BOOL bFlag = FALSE;
	HGLOBAL hMem = NULL;
	LPCTSTR lpStr = NULL;
	UINT uFormat = NULL;
	bFlag = ::OpenClipboard(hWnd);
	if (!bFlag)
	{
		return FALSE;
	}
	hMem = ::GetClipboardData(CF_TEXT);
	lpStr = (LPCTSTR)::GlobalLock(hMem);
	bFlag = CloseClipboard();
	
	if (!bFlag)
	{
		return FALSE;
	}

	if (lpStr != NULL)
	{
		_tcscpy(strClipboardData, lpStr);
	}

	return TRUE;
}