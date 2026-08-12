#ifndef __CmdLineParser_h_
#define __CmdLineParser_h_

#include "Public.h"
#include <vector>
using std::vector;

/** 命令行参数分析类，以 -/作为参数分割符号，例如：
    -/param1 -/param2表示带有参数启动参数param1, param2
*/
class CCmdLineParser 
{
public:
	CCmdLineParser(LPCTSTR sCmdLine = NULL);
	virtual ~CCmdLineParser();

	bool Parse(LPCTSTR sCmdLine);

    vector<xstring>& GetCmdValue();

private:
	CString          m_sCmdLine;
	vector<xstring>	 m_ValsVector;

private:
	static const TCHAR m_sDelimeters[];
};

#endif //__CmdLineParser_h_
