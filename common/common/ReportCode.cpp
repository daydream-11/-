#include "pch.h"
#include "ReportCode.h"
#include "fun.h"

CReportCode::CReportCode()
{
}

CReportCode::~CReportCode()
{
}

std::string CReportCode::ToString()
{
	return m_sCode;
}

CReportCode& CReportCode::operator << (const char* lpValue)
{
	if (lpValue)
		m_sCode.append(lpValue).append("\t");

	return *this;
}

CReportCode& CReportCode::operator << (const std::string& sValue)
{
	return operator << (sValue.c_str());
}

CReportCode& CReportCode::operator << (bool bValue)
{
	return operator << (num2str(bValue).c_str());
}

CReportCode& CReportCode::operator << (int nValue)
{
	return operator << (num2str(nValue).c_str());
}
