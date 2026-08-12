
#ifndef __PUBLIC_H__
#define __PUBLIC_H__


#include <string>
#include <xstring>
using namespace std;
	
#if _UNICODE
	typedef wstring xstring;
#else
	typedef string xstring;
#endif

#endif	// __PUBLIC_H__
