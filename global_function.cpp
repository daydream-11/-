//
// Created by miaog on 2024/11/7.
//
#include "global_function.h"

#ifdef Q_OS_WIN

// 判断网卡是否为物理网卡
int IsPhysicalNetworkCard(LPCTSTR pszGuid)
{
    int ret = -1;
    HKEY hKey = NULL;
    CHAR szSubKey[256] = { '\0' };
    sprintf_s(szSubKey, ("SYSTEM\\CurrentControlSet\\Control\\Network\\{4D36E972-E325-11CE-BFC1-08002BE10318}\\%s\\Connection"), (char*)pszGuid);
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, szSubKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        TCHAR szInstId[1024] = { 0 };
        DWORD dwSize = sizeof(szInstId);
        if (RegQueryValueEx(hKey, TEXT("PnpInstanceID"), NULL, NULL, (LPBYTE)szInstId, &dwSize) == ERROR_SUCCESS) {
            if (StrIsIntlEqual(false, szInstId, TEXT("PCI"), 3)) {
                DWORD dwSubType = 0;
                DWORD dwSize = sizeof(DWORD);
                LONG lRet = RegQueryValueEx(hKey, TEXT("MediaSubType"), NULL, NULL, (LPBYTE)&dwSubType, &dwSize);
                if (lRet == ERROR_FILE_NOT_FOUND || (lRet == ERROR_SUCCESS && dwSubType == 1)) {
                    ret = 0;
                }
                else if (lRet == ERROR_SUCCESS && dwSubType == 2) {
                    ret = 1;
                }
            }
        }
        RegCloseKey(hKey);
    }
    return ret;
}

// 获取mac地址 (Windows)
std::string GetMac() {
    BYTE bMacAddr[6] = { 0 };
    ULONG ulOutBufLen = 0;
    GetAdaptersInfo(NULL, &ulOutBufLen);
    IP_ADAPTER_INFO* AdapterInfo = (IP_ADAPTER_INFO*)GlobalAlloc(GPTR, ulOutBufLen);

    if (AdapterInfo != NULL)
    {
        if (GetAdaptersInfo(AdapterInfo, &ulOutBufLen) == NO_ERROR)
        {
            for (PIP_ADAPTER_INFO pAdapter = AdapterInfo; pAdapter != NULL; pAdapter = pAdapter->Next)
            {
                int ret = IsPhysicalNetworkCard((LPCTSTR)pAdapter->AdapterName);

                if (ret == 0 || ret == 1)
                {
                    memcpy(bMacAddr, pAdapter->Address, sizeof(bMacAddr));

                    if (ret == 0)
                    {
                        break;
                    }
                }
            }
        }
    }

    char szMac[MAX_PATH] = { 0 };
    sprintf_s(szMac, "%02X-%02X-%02X-%02X-%02X-%02X", bMacAddr[0], bMacAddr[1], bMacAddr[2], bMacAddr[3], bMacAddr[4], bMacAddr[5]);
    std::string result(szMac);
    return result;
}

#elif defined(Q_OS_MACOS)

#include <ifaddrs.h>
#include <net/if_dl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>

std::string GetMac() {
    struct ifaddrs *ifaddr = nullptr;
    if (getifaddrs(&ifaddr) == -1)
        return "";

    std::string result;
    for (struct ifaddrs *ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr || ifa->ifa_addr->sa_family != AF_LINK)
            continue;

        // Prefer en0 (Wi-Fi) or en1 (Ethernet), fallback to any en*
        if (strncmp(ifa->ifa_name, "en", 2) != 0)
            continue;

        struct sockaddr_dl *sdl = (struct sockaddr_dl *)ifa->ifa_addr;
        unsigned char *mac = (unsigned char *)LLADDR(sdl);

        // Skip zeroed MAC addresses
        bool allZero = true;
        for (int i = 0; i < 6; i++) {
            if (mac[i] != 0) { allZero = false; break; }
        }
        if (allZero) continue;

        char szMac[18];
        snprintf(szMac, sizeof(szMac), "%02X-%02X-%02X-%02X-%02X-%02X",
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        result = szMac;
        break;
    }
    freeifaddrs(ifaddr);
    return result;
}

#else

// Fallback for other platforms (Linux, etc.)
#include <cstdio>
#include <fstream>

std::string GetMac() {
    std::ifstream ifs("/sys/class/net/eth0/address");
    if (!ifs.is_open()) {
        ifs.open("/sys/class/net/enp0s3/address");
    }
    if (!ifs.is_open()) {
        ifs.open("/sys/class/net/wlan0/address");
    }
    if (ifs.is_open()) {
        std::string mac;
        std::getline(ifs, mac);
        if (!mac.empty()) {
            // Convert to uppercase XX-XX-XX-XX-XX-XX format
            for (auto &c : mac) {
                if (c == ':') c = '-';
                else c = toupper(c);
            }
            if (!mac.empty() && mac.back() == '\n')
                mac.pop_back();
            return mac;
        }
    }
    return "";
}

#endif
