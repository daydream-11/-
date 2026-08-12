
#include "stdafx.h"
#include "CmdLineParser.h"

const TCHAR CCmdLineParser::m_sDelimeters[] = _T("-/");


CCmdLineParser::CCmdLineParser(LPCTSTR sCmdLine)
{
	if(sCmdLine) 
    {
		Parse(sCmdLine);
	}
}

CCmdLineParser::~CCmdLineParser()
{
	m_ValsVector.clear();
}

bool CCmdLineParser::Parse(LPCTSTR sCmdLine)
{
	if(!sCmdLine)
    {
        return false;
    }
	m_ValsVector.clear();

	int nArgs = 0;
	LPCTSTR sCurrent = sCmdLine;
	while(true)
    {
        if (!sCurrent)
        {
            break;
        }
		if(_tcslen(sCurrent) == 0) 
        { 
            break;
        }
		LPCTSTR sArg = wcsstr(sCurrent, m_sDelimeters);;
		if(!sArg)
        {
            break; 
        }
        if (_tcslen(sArg) <= _tcslen(m_sDelimeters))
        {
            break; 
        }
        sArg = sArg + _tcslen(m_sDelimeters);
		if(_tcslen(sArg) == 0) 
        {
            break; 
        }
		LPCTSTR sVal = wcsstr(sArg, m_sDelimeters);;
        if (sVal != NULL)
        {
            xstring csKey(sArg, sVal - sArg);
            if ((csKey.size() > 1) && (csKey[csKey.size() - 1] == ' '))
            {
                csKey = csKey.erase(csKey.size() - 1, 1);
            }
            m_ValsVector.push_back(csKey);
        }
        else
        {
            m_ValsVector.push_back(sArg);
        }
        sCurrent = sVal;
	}
    return !m_ValsVector.empty();
}

vector<xstring>& CCmdLineParser::GetCmdValue()
{
    return m_ValsVector;
}