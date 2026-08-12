#ifndef __VECTOR_SPLIT_PY_PARSE_ORDER_H__
#define __VECTOR_SPLIT_PY_PARSE_ORDER_H__

#include "DBStruct.h"

// 
struct SVectorSplitPYParseOrder
{
	TVectorSplitPYParse mVectorSplitPYParse;
	// 升序排序时必须写的函数
	bool operator < (const SVectorSplitPYParseOrder & myVectorSplitPYParseOrder) const
	{
		int nSize = (int)mVectorSplitPYParse.size();
		int nTempSize = (int)myVectorSplitPYParseOrder.mVectorSplitPYParse.size();
		if (nSize < nTempSize)
		{
			// 组合个数短的放前面
			return true;
		}
		if (nSize > nTempSize)
		{
			// 组合个数短的放后面
			return false;
		}
		return false;
	}
};


#endif	// __VECTOR_SPLIT_PY_PARSE_ORDER_H__

