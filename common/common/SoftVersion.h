#pragma once
#include <string>


class SoftVersion
{
public:
	explicit SoftVersion(int major, int minor, int release, int build);

	// reg ^\d+\.{3}\d+$
	explicit SoftVersion(const std::string& verstr);

	std::string ToString();
	
	int Compare(const SoftVersion& rhs);

	bool operator == (const SoftVersion& rhs);
	bool operator != (const SoftVersion& rhs);
	bool operator < (const SoftVersion& rhs);
	bool operator <= (const SoftVersion& rhs);
	bool operator > (const SoftVersion& rhs);
	bool operator >= (const SoftVersion& rhs);

private:
	// 0 major
	// 1 minor
	// 2 release
	// 3 build
	short version[4];
};