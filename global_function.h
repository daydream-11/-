#ifndef GLOBAL_FUNCTION_HPP
#define GLOBAL_FUNCTION_HPP

#include <iostream>
#include <string>

#ifdef Q_OS_WIN
#include <Windows.h>
#include <IPTypes.h>
#include <iphlpapi.h>
#include <shlwapi.h>

// 判断网卡是否为物理网卡 (Windows only)
int IsPhysicalNetworkCard(LPCTSTR pszGuid);
#endif

// 获取mac地址 (跨平台)
std::string GetMac();

#endif
