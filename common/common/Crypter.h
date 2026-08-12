#pragma once
 
#include <string>  
#include <windows.h>  
#include <wincrypt.h>  

class Crypter
{
public:
	Crypter(void);
	~Crypter(void);

public:
	//Cr4 File  解压到同一个文件
	bool Cr4File(const char *filename);

	//Cr4 File
	bool Cr4File(const char *srcFilename, const char *dstFilename);

	//Cr4 转换
	bool Cr4Buffer(char *buf, int bufLen);
};

void crypter_buffer(char *buf, int bufLen);

void crypter_str(std::string &s);