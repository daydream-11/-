#include "pch.h"
#include "crypter.h"
#include <fstream>
#include "easyFunctions.h"
#include "fun.h"

void crypter_buffer(char *buf, int bufLen)
{
	Crypter cry;

	cry.Cr4Buffer(buf, bufLen);
}

void crypter_str(const std::string &s)
{
	Crypter cry;

	crypter_buffer((char *)s.c_str(), s.length());
}

static std::string num2str(int v)
{
	char buf[33] = {0};

	sprintf_s(buf, "%d", v);

	return buf;
}

Crypter::Crypter(void)
{

}
Crypter::~Crypter(void)
{

}

bool Crypter::Cr4File(const char *filename)
{
	return Cr4File(filename, filename);
}

bool Crypter::Cr4File(const char *srcFilename, const char *dstFilename)
{
	if (srcFilename == NULL)
	{
		printf("Error. Filename is null.");
		return false;
	}

	std::ifstream ifs;

	ifs.open(a2w(srcFilename).c_str(), ios_base::binary);

	if (!ifs.is_open())
	{
		printf("Error. Open failed. %s", srcFilename);
		return false;
	}

	ifs.seekg(0, ios_base::end);

	int bufLen = ifs.tellg();
	char *buf = new char[bufLen];

	if (buf)
	{
		ifs.seekg(0);

		ifs.read(buf, bufLen);
	}

	ifs.close();

	if (buf == NULL)
	{
		printf("Error. Buffer is null.");
		return false;
	}

	if (!Cr4Buffer(buf, bufLen))
	{
		return false;
	}

	std::ofstream ofs;

	ofs.open(a2w(dstFilename).c_str(), ios_base::binary|ios_base::out);

	if (!ofs.is_open())
	{
		printf("Error. Open write failed.");
		return false;
	}

	ofs.write(buf, bufLen);
	
	return true;
}

bool Crypter::Cr4Buffer(char *buf, int bufLen)
{
	std::string key = num2str(bufLen);

	rc4(key, buf, bufLen);

	return true;
}