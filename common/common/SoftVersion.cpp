#include "pch.h"
#include "SoftVersion.h"

#include <regex>
#include <sstream>


SoftVersion::SoftVersion( int major, int minor, int release, int build )
{
	version[0] = major;
	version[1] = minor;
	version[2] = release;
	version[3] = build;
}

SoftVersion::SoftVersion( const std::string& verstr )
{
	std::tr1::regex pattern("^(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+)$");
	std::tr1::smatch matchresult;
	bool match = std::tr1::regex_search(verstr, matchresult, pattern);

	for (size_t i = 0; i < 4; ++i) {
		if (match)
			version[i] = atoi(std::string(matchresult[i + 1]).c_str());
		else
			version[i] = 0;
	}
}

std::string SoftVersion::ToString()
{
	std::stringstream stringbuild;
	stringbuild << version[0] << ".";
	stringbuild << version[1] << ".";
	stringbuild << version[2] << ".";
	stringbuild << version[3];

	return stringbuild.str();
}

int SoftVersion::Compare( const SoftVersion& rhs )
{
	int ret = 0;

	for (int i = 0; i < 4; i++) {
		ret = version[i] - rhs.version[i];
		if (ret != 0)
			break;
	}

	return ret;
}

bool SoftVersion::operator==( const SoftVersion& rhs )
{
	return Compare(rhs) == 0;
}

bool SoftVersion::operator!=( const SoftVersion& rhs )
{
	return (Compare(rhs) != 0);
}

bool SoftVersion::operator<( const SoftVersion& rhs )
{
	return (Compare(rhs) < 0);
}

bool SoftVersion::operator<=( const SoftVersion& rhs )
{
	return (Compare(rhs) <= 0);
}

bool SoftVersion::operator>( const SoftVersion& rhs )
{
	return (Compare(rhs) > 0);
}

bool SoftVersion::operator>=( const SoftVersion& rhs )
{
	return (Compare(rhs) >= 0);
}
