#pragma once
class CReportCode
{
public:
	CReportCode();
	~CReportCode();

public:
	std::string ToString();

	CReportCode& operator << (const char* lpValue);
	CReportCode& operator << (const std::string& sValue);
	CReportCode& operator << (bool bValue);
	CReportCode& operator << (int nValue);

private:
	std::string m_sCode;

};

