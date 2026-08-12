#include "pch.h"
#include "ReportWrite.h"
#include "fun.h"
#include "WinRegistryKey.h"
#include "Crypter.h"

void ReportWriteReg(std::string& sReg, std::string& sPath, CReportCode& code)
{
	std::string sCode = code.ToString();
	ReportWriteReg(sReg, sPath, sCode);
	//Crypter cry;

	//cry.Cr4Buffer((char *)sPath.c_str(), sPath.length());
	//cry.Cr4Buffer((char *)sCode.c_str(), sCode.length());

	//helper::WinRegistryKey WinKey(HKEY_CURRENT_USER, sReg.c_str(), false);

	//std::vector<char> vsCode;
	//std::vector<char> vsPath;

	//for (int i = 0; i < sCode.length(); i++)
	//	vsCode.push_back(sCode.at(i));

	//for (int i = 0; i < sPath.length(); i++)
	//	vsPath.push_back(sPath.at(i));

	//WinKey.setBinary("code", vsCode);
	//WinKey.setBinary("path", vsPath);
}

void ReportWriteReg(std::string& sReg, std::string& sPath, std::string& sCode)
{
	Crypter cry;

	cry.Cr4Buffer((char *)sPath.c_str(), sPath.length());
	cry.Cr4Buffer((char *)sCode.c_str(), sCode.length());

	helper::WinRegistryKey WinKey(HKEY_CURRENT_USER, sReg.c_str(), false);

	std::vector<char> vsCode;
	std::vector<char> vsPath;

	for (int i = 0; i < sCode.length(); i++)
		vsCode.push_back(sCode.at(i));

	for (int i = 0; i < sPath.length(); i++)
		vsPath.push_back(sPath.at(i));

	WinKey.setBinary("code", vsCode);
	WinKey.setBinary("path", vsPath);
}