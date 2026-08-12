/*********************************************************************
* 版权所有 (C)2008
* 
* 文件名称： WnVectorParameter.h
* 文件标识： 
* 内容摘要： 提供表情相关的参数操作类，包括主要模块、函数及其功能的说明
* 其它说明： 
* 当前版本： 1.0.20080820
* 作    者： 黄根平
* 完成日期： 2008-08-20
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
**********************************************************************/
#ifndef __VECTOR_PARAMETER_H__
#define __VECTOR_PARAMETER_H__

#include <vector>
#include "Public.h"

template <class T>
class VectorParameter
{
public:

	/** @name 公共的成员变量 */////////////////////////////////////////////////////
    /// @{

	typedef vector< pair<xstring, T> > TVectorParameter;

	//要设置的参数MAP
	TVectorParameter m_vectorParameter;

	/// @}

public:

	/** @name 构造与析构 */////////////////////////////////////////////////////
    /// @{
	
	/**********************************************************************
	* 函数名称： VectorParameter
	* 功能描述： 向量参数操作类构造函数
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
	VectorParameter();
	
	/**********************************************************************
	* 函数名称： VectorParameter
	* 功能描述： 向量参数操作类析构函数
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
	~VectorParameter();

	/// @}

public:

	/** @name 公共成员函数 *///////////////////////////////////////////////////
    /// @{

	/**********************************************************************
	* 函数名称： GetVectorParameter
	* 功能描述： 函数用于当前命令参数向量，纯虚函数
	* 输入参数： 
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 返回用于当前命令参数向量
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    //virtual VectorParameter GetVectorParameter();

	/**********************************************************************
	* 函数名称： AppendParameter
	* 功能描述： 函数用于为命令行添加一个新参数
	* 输入参数： strName	要添加的参数名
	* 输入参数： myT	要添加的参数值
	* 输出参数：
	* 返 回 值： 执行成功，返回true；执行失败，返回false
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual bool AppendParameter(const xstring & strName, const T & myT);

	/**********************************************************************
	* 函数名称： AppendFrontParameter
	* 功能描述： 函数用于为参数添加一个新参数位于参数（strFrontName）前面
	* 输入参数： strName		要添加的参数名
	* 输入参数： myT			要添加的参数值
	* 输入参数： strFrontName	参照参数
	* 输出参数：
	* 返 回 值： 执行成功，返回true；执行失败，返回false
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual bool AppendFrontParameter(const xstring & strName, const T & myT, const xstring & strFrontName);

	/**********************************************************************
	* 函数名称： AppendFrontParameter
	* 功能描述： 函数用于为参数添加一个新参数位于参数（myFrontT）前面
	* 输入参数： strName		要添加的参数名
	* 输入参数： myT			要添加的参数值
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 执行成功，返回true；执行失败，返回false
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual bool AppendFrontParameter(const xstring & strName, const T & myT, const T & myFrontT);
    
	/**********************************************************************
	* 函数名称： AppendBackParameter
	* 功能描述： 函数用于为参数添加一个新参数位于参数（strBackName）后面
	* 输入参数： strName		要添加的参数名
	* 输入参数： myT			要添加的参数值
	* 输入参数： strBackName	参照参数
	* 输出参数：
	* 返 回 值： 执行成功，返回true；执行失败，返回false
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual bool AppendBackParameter(const xstring & strName, const T & myT, const xstring & strBackName);

	/**********************************************************************
	* 函数名称： AppendBackParameter
	* 功能描述： 函数用于为参数添加一个新参数位于参数（myBackT）后面
	* 输入参数： strName		要添加的参数名
	* 输入参数： myT			要添加的参数值
	* 输入参数： myBackT		参照参数
	* 输出参数：
	* 返 回 值： 执行成功，返回true；执行失败，返回false
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual bool AppendBackParameter(const xstring & strName, const T & myT, const T & myBackT);

	/**********************************************************************
	* 函数名称： AppendParameter
	* 功能描述： 函数用于从当前命令行修改一个参数
	* 输入参数： strName	要修改的参数名，如果不存在，将会导致操作失败
	* 输入参数： myT	要修改的参数值
	* 输出参数：
	* 返 回 值： 执行成功，返回true；执行失败，返回false
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual bool ModifyParameter(const xstring & strName, const T & myT);
    
	/**********************************************************************
	* 函数名称： ModifyParameter
	* 功能描述： 函数用于从当前命令行修改一个参数
	* 输入参数： _nIndex	要修改的参数索引，如果不存在，将会导致操作失败
	* 输入参数： myT	要修改的参数值
	* 输出参数：
	* 返 回 值： 执行成功，返回true；执行失败，返回false
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual bool ModifyParameter(int _nIndex, const T & myT);
    
	/**********************************************************************
	* 函数名称： DeleteParameter
	* 功能描述： 函数用于从当前命令行删除一个参数
	* 输入参数： strName	要删除的参数名，如果不存在，将会导致操作失败
	* 输出参数：
	* 返 回 值： 执行成功，返回true；执行失败，返回false
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual bool DeleteParameter(const xstring & strName);
    
	/**********************************************************************
	* 函数名称： DeleteParameter
	* 功能描述： 函数用于按索引获取参数的名称
	* 输入参数： _nIndex	要删除的参数索引，如果不存在，将会导致操作失败
	* 输出参数：
	* 返 回 值： 执行成功，返回true；执行失败，返回false
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual bool DeleteParameter(int _nIndex);

	/**********************************************************************
	* 函数名称： DeleteAllParameter
	* 功能描述： 函数用于从当前命令行删除所有参数
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 执行成功，返回true；执行失败，返回false
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual bool DeleteAllParameter();
    
	/**********************************************************************
	* 函数名称： GetParameterValue
	* 功能描述： 函数用于按索引获取参数的值
	* 输入参数： nIndex	要获取的参数名的参数索引
	* 输出参数：
	* 返 回 值： 成功则返回该参数的名称，否则返回空
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual const T* GetParameterValue(int nIndex);

	/**********************************************************************
	* 函数名称： GetParameterValue
	* 功能描述： 函数用于按索引获取参数的值
	* 输入参数： nIndex	要获取的参数名的参数索引
	* 输出参数：
	* 返 回 值： 成功则返回该参数的名称，否则返回空
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual const T* GetParameterPointer(int nIndex);
	
	/**********************************************************************
	* 函数名称： GetParameterObject
	* 功能描述： 函数用于按索引获取参数的值
	* 输入参数： nIndex	要获取的参数名的参数索引
	* 输出参数：
	* 返 回 值： 成功则返回该参数的名称，否则返回空
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual const T GetParameterObject(int nIndex);

	/**********************************************************************
	* 函数名称： GetParameterValue
	* 功能描述： 函数用于参数名获取参数的值
	* 输入参数： strParamName	要获取的参数值的参数名
	* 输出参数：
	* 返 回 值： 成功则返回该参数的名称，否则返回空
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual const T GetParameterValue(const xstring & strParamName);

	/**********************************************************************
	* 函数名称： GetParameterValue
	* 功能描述： 函数用于参数名获取参数的值
	* 输入参数： strParamName	要获取的参数值的参数名
	* 输出参数：
	* 返 回 值： 成功则返回该参数的名称，否则返回空
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual const T* GetParameterPointer(const xstring & strParamName);

	/**********************************************************************
	* 函数名称： GetParameterObject
	* 功能描述： 函数用于参数名获取参数的值
	* 输入参数： strParamName	要获取的参数值的参数名
	* 输出参数：
	* 返 回 值： 成功则返回该参数的名称，否则返回空
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual const T GetParameterObject(const xstring & strParamName);

	/**********************************************************************
	* 函数名称： GetParameterName
	* 功能描述： 
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 成功则返回该参数的名称，否则返回空
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual xstring GetParameterName(const T & myT);

    /**********************************************************************
	* 函数名称： 
	* 功能描述： 重载的[]操作符用于按索引获取参数的值
	* 输入参数： _nIndex	要获取的参数值的参数索引
	* 输出参数：
	* 返 回 值： 成功则返回该参数的值，否则返回空
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
    virtual const T* operator[](int _nIndex);
    
	/**********************************************************************
	* 函数名称： 
	* 功能描述： 重载的[]操作符用于按参数名获取参数的值
	* 输入参数： _strParamName	要获取的参数值的参数名
	* 输出参数：
	* 返 回 值： 成功则返回该参数的值，否则返回空
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
	virtual const T* operator[](const xstring & _strParamName);
    
	/**********************************************************************
	* 函数名称： GetParameterCount
	* 功能描述： 函数用于获取参数的个数
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 返回当前命令参数的个数
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
	virtual int GetParameterCount();

	/**********************************************************************
	* 函数名称： GetParameterCount
	* 功能描述： 函数用于获取参数的个数
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 返回当前命令参数的个数
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2008/05/10		V1.0	    huanggenping	创建版本
	***********************************************************************/
	virtual int IsExistParameter(const xstring & strParamName);

	/// @}

};


/** @name 构造与析构 */////////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： VectorParameter
* 功能描述： 向量参数操作类构造函数
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
VectorParameter<T>::VectorParameter()
{
	
}

/**********************************************************************
* 函数名称： VectorParameter
* 功能描述： 向量参数操作类析构函数
* 输入参数： 
* 输出参数：
* 返 回 值： 
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
VectorParameter<T>::~VectorParameter()
{
	DeleteAllParameter();
}

/// @}

/** @name 公共成员函数 *///////////////////////////////////////////////////
/// @{

/**********************************************************************
* 函数名称： GetVectorParameter
* 功能描述： 函数用于当前命令参数向量，纯虚函数
* 输入参数： 
* 输入参数： 
* 输出参数：
* 返 回 值： 返回用于当前命令参数向量
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
//template <class T>
//VectorParameter CParameter<T>::GetVectorParameter()
//{
//	return NULL;
//}

/**********************************************************************
* 函数名称： AppendParameter
* 功能描述： 函数用于为命令行添加一个新参数
* 输入参数： strName	要添加的参数名
* 输入参数： myT	要添加的参数值
* 输出参数：
* 返 回 值： 执行成功，返回true；执行失败，返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
bool VectorParameter<T>::AppendParameter(const xstring & strName, const T & myT)
{
	m_vectorParameter.push_back(TVectorParameter::value_type(strName, myT));
	return true;
}

/**********************************************************************
* 函数名称： AppendFrontParameter
* 功能描述： 函数用于为参数行添加一个新参数
* 输入参数： strName	要添加的参数名
* 输入参数： myT	要添加的参数值
* 输出参数：
* 返 回 值： 执行成功，返回true；执行失败，返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
bool VectorParameter<T>::AppendFrontParameter(const xstring & strName, const T & myT, const xstring & strFrontName)
{
	TVectorParameter::iterator *pIterFront = NULL;
	bool bFind = false;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (iter->first == strFrontName)
		{
			bFind = true;
			break;
		}
		pIterFront = &iter;
	}
	if (pIterFront == NULL)
	{
		m_vectorParameter.insert(m_vectorParameter.begin(), TVectorParameter::value_type(strName, myT));
		return true;
	}
	if (bFind)
	{
		m_vectorParameter.insert(*pIterFront, TVectorParameter::value_type(strName, myT));
		return true;
	}
	AppendParameter(strName, myT);
	return true;
}

/**********************************************************************
* 函数名称： AppendFrontParameter
* 功能描述： 函数用于为参数行添加一个新参数
* 输入参数： strName	要添加的参数名
* 输入参数： myT	要添加的参数值
* 输出参数：
* 返 回 值： 执行成功，返回true；执行失败，返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
bool VectorParameter<T>::AppendFrontParameter(const xstring & strName, const T & myT, const T & myFrontT)
{
	TVectorParameter::iterator *pIterFront = NULL;
	T *pT = NULL;
	bool bFind = false;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		pT = &iter->second;
		if (*pT == myFrontT)
		{
			bFind = true;
			break;
		}
		pIterFront = &iter;
	}
	if (pIterFront == NULL)
	{
		m_vectorParameter.insert(m_vectorParameter.begin(), TVectorParameter::value_type(strName, myT));
		return true;
	}
	if (bFind)
	{
		m_vectorParameter.insert(*pIterFront, TVectorParameter::value_type(strName, myT));
		return true;
	}
	AppendParameter(strName, myT);
	return true;
}

/**********************************************************************
* 函数名称： AppendBackParameter
* 功能描述： 函数用于为参数添加一个新参数位于参数（strBackName）后面
* 输入参数： strName		要添加的参数名
* 输入参数： myT			要添加的参数值
* 输入参数： strBackName	参照参数
* 输出参数：
* 返 回 值： 执行成功，返回true；执行失败，返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
bool VectorParameter<T>::AppendBackParameter(const xstring & strName, const T & myT, const xstring & strBackName)
{
	TVectorParameter::iterator *pIterBack = NULL;
	bool bFind = FALSE;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (iter->first == strBackName)
		{
			bFind = true;
			continue;
		}
		if (bFind)
		{
			pIterBack = &iter;
			break;
		}
	}
	if (pIterBack == NULL)
	{
		AppendParameter(strName, myT);
		return true;
	}
	if (bFind)
	{
		m_vectorParameter.insert(*pIterBack, TVectorParameter::value_type(strName, myT));
		return true;
	}
	AppendParameter(strName, myT);
	return true;
}

/**********************************************************************
* 函数名称： AppendBackParameter
* 功能描述： 函数用于为参数添加一个新参数位于参数（strBackName）后面
* 输入参数： strName		要添加的参数名
* 输入参数： myT			要添加的参数值
* 输入参数： strBackName	参照参数
* 输出参数：
* 返 回 值： 执行成功，返回true；执行失败，返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
bool VectorParameter<T>::AppendBackParameter(const xstring & strName, const T & myT, const T & myBackT)
{
	TVectorParameter::iterator *pIterBack = NULL;
	T *pT = NULL;
	bool bFind = FALSE;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		pT = &iter->second;
		if (*pT == myBackT)
		{
			bFind = true;
			continue;
		}
		if (bFind)
		{
			pIterBack = &iter;
			break;
		}
	}
	if (pIterBack == NULL)
	{
		AppendParameter(strName, myT);
		return true;
	}
	if (bFind)
	{
		m_vectorParameter.insert(*pIterBack, TVectorParameter::value_type(strName, myT));
		return true;
	}
	AppendParameter(strName, myT);
	return true;
}

/**********************************************************************
* 函数名称： ModifyParameter
* 功能描述： 函数用于从当前命令行修改一个参数
* 输入参数： strName	要修改的参数名，如果不存在，将会导致操作失败
* 输入参数： myT	要修改的参数值
* 输出参数：
* 返 回 值： 执行成功，返回true；执行失败，返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
bool VectorParameter<T>::ModifyParameter(const xstring & strName, const T & myT)
{
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (iter->first == strName)
		{
			iter->second = myT;
			return true;
		}
	}
	return false;
}

/**********************************************************************
* 函数名称： ModifyParameter
* 功能描述： 函数用于从当前命令行修改一个参数
* 输入参数： _nIndex	要修改的参数索引，如果不存在，将会导致操作失败
* 输入参数： myT	要修改的参数值
* 输出参数：
* 返 回 值： 执行成功，返回true；执行失败，返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
bool VectorParameter<T>::ModifyParameter(int _nIndex, const T & myT)
{
	int num = 0;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (num == _nIndex)
		{
			iter->second = myT;
			return true;
		}
		num++;
	}
	return false;
}

/**********************************************************************
* 函数名称： DeleteParameter
* 功能描述： 函数用于从当前命令行删除一个参数
* 输入参数： strName	要删除的参数名，如果不存在，将会导致操作失败
* 输出参数：
* 返 回 值： 执行成功，返回true；执行失败，返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
bool VectorParameter<T>::DeleteParameter(const xstring & strName)
{
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (iter->first == strName)
		{
			m_vectorParameter.erase(iter);
			return true;
		}
	}
	return false;
}

/**********************************************************************
* 函数名称： DeleteParameter
* 功能描述： 函数用于按索引获取参数的名称
* 输入参数： _nIndex	要删除的参数索引，如果不存在，将会导致操作失败
* 输出参数：
* 返 回 值： 执行成功，返回true；执行失败，返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
bool VectorParameter<T>::DeleteParameter(int _nIndex)
{
	int num = 0;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (num == _nIndex)
		{
			m_vectorParameter.erase(iter);
			return true;
		}
		num++;
	}
	return false;
}

/**********************************************************************
* 函数名称： DeleteAllParameter
* 功能描述： 函数用于从当前命令行删除所有参数
* 输入参数： 
* 输出参数：
* 返 回 值： 执行成功，返回true；执行失败，返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
bool VectorParameter<T>::DeleteAllParameter()
{
	m_vectorParameter.clear();
	return true;
}

/**********************************************************************
* 函数名称： GetParameterValue
* 功能描述： 函数用于按索引获取参数的值
* 输入参数： _nIndex	要获取的参数名的参数索引
* 输出参数：
* 返 回 值： 成功则返回该参数的名称，否则返回空
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
const T* VectorParameter<T>::GetParameterValue(int nIndex)
{
	T * pT = NULL;
	int num = 0;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (num == nIndex)
		{
			pT = &iter->second;
			break;
		}
		num++;
	}
	return pT;
}

/**********************************************************************
* 函数名称： GetParameterValue
* 功能描述： 函数用于按索引获取参数的值
* 输入参数： _nIndex	要获取的参数名的参数索引
* 输出参数：
* 返 回 值： 成功则返回该参数的名称，否则返回空
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
const T* VectorParameter<T>::GetParameterPointer(int nIndex)
{
	T * pT = NULL;
	int num = 0;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (num == nIndex)
		{
			pT = &iter->second;
			break;
		}
		num++;
	}
	return pT;
}


/**********************************************************************
* 函数名称： GetParameterValue
* 功能描述： 函数用于按索引获取参数的值
* 输入参数： _nIndex	要获取的参数名的参数索引
* 输出参数：
* 返 回 值： 成功则返回该参数的名称，否则返回空
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
const T VectorParameter<T>::GetParameterObject(int nIndex)
{
	T * pT = NULL;
	int num = 0;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (num == nIndex)
		{
			pT = &iter->second;
			break;
		}
		num++;
	}
	return *pT;
}

/**********************************************************************
* 函数名称： GetParameterName
* 功能描述： 
* 输入参数： 
* 输出参数：
* 返 回 值： 成功则返回该参数的名称，否则返回空
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
xstring VectorParameter<T>::GetParameterName(const T & myT)
{
	T * pT = NULL;
	int num = 0;
	xstring strParamName = _T("");
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		pT = &iter->second;
		if (*pT == myT)
		{
			strParamName = iter->first;
			break;
		}
	}
	return strParamName;
}

/**********************************************************************
* 函数名称： GetParameterValue
* 功能描述： 函数用于参数名获取参数的值
* 输入参数： strParamName	要获取的参数值的参数名
* 输出参数：
* 返 回 值： 成功则返回该参数的名称，否则返回空
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
const T VectorParameter<T>::GetParameterValue(const xstring & strParamName)
{
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (iter->first == strParamName)
		{
			return iter->second;
		}
	}
	return NULL;
}

/**********************************************************************
* 函数名称： GetParameterValue
* 功能描述： 函数用于参数名获取参数的值
* 输入参数： strParamName	要获取的参数值的参数名
* 输出参数：
* 返 回 值： 成功则返回该参数的名称，否则返回空
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
const T* VectorParameter<T>::GetParameterPointer(const xstring & strParamName)
{
	T * pT = NULL;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (iter->first == strParamName)
		{
			pT = &iter->second;
			break;
		}
	}
	return pT;
}

/**********************************************************************
* 函数名称： GetParameterObject
* 功能描述： 函数用于参数名获取参数的值
* 输入参数： strParamName	要获取的参数值的参数名
* 输出参数：
* 返 回 值： 成功则返回该参数的名称，否则返回空
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
const T VectorParameter<T>::GetParameterObject(const xstring & strParamName)
{
	T * pT = NULL;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (iter->first == strParamName)
		{
			pT = &iter->second;
			break;
		}
	}
	return *pT;
}

/**********************************************************************
* 函数名称： 
* 功能描述： 重载的[]操作符用于按索引获取参数的值
* 输入参数： _nIndex	要获取的参数值的参数索引
* 输出参数：
* 返 回 值： 成功则返回该参数的值，否则返回空
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
const T* VectorParameter<T>::operator[](int _nIndex)
{
	T * pT = NULL;
	int num = 0;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (num == _nIndex)
		{
			pT = &iter->second;
			break;
		}
		num++;
	}
	return pT;
}

/**********************************************************************
* 函数名称： 
* 功能描述： 重载的[]操作符用于按参数名获取参数的值
* 输入参数： _strParamName	要获取的参数值的参数名
* 输出参数：
* 返 回 值： 成功则返回该参数的值，否则返回空
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
const T* VectorParameter<T>::operator[](const xstring & _strParamName)
{
	T * pT = NULL;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (iter->first == _strParamName)
		{
			pT = &iter->second;
			break;
		}
	}
	return pT;
}

/**********************************************************************
* 函数名称： GetParameterCount
* 功能描述： 函数用于获取参数的个数
* 输入参数： 
* 输出参数：
* 返 回 值： 返回当前命令参数的个数
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
int VectorParameter<T>::GetParameterCount()
{
	return (int)m_vectorParameter.size();
}

/**********************************************************************
* 函数名称： IsExistParameter
* 功能描述： 判断是否存在此参数
* 输入参数： 
* 输出参数：
* 返 回 值： 存在此参数返回true,否则返回false
* 其它说明： 
* 修改日期			版本号		修改人			修改内容
* ---------------------------------------------------------------------
* 2008/05/10		V1.0	    huanggenping	创建版本
***********************************************************************/
template <class T>
int VectorParameter<T>::IsExistParameter(const xstring & strParamName)
{
	bool bExist = false;
	for (TVectorParameter::iterator iter = m_vectorParameter.begin() ; iter != m_vectorParameter.end() ; iter++)
	{
		if (iter->first == strParamName)
		{
			bExist = true;
			break;
		}
	}
	return bExist;
}

/// @}

#endif	//__VECTOR_PARAMETER_H__