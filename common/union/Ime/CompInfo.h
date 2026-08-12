/*********************************************************************
* 版权所有 (C)2008
* 
* 文件名称： CompInfo.h
* 文件标识： 
* 内容摘要： 提供给单个候选词的管理类，包括主要模块、函数及其功能的说明
* 其它说明： 
* 当前版本： 1.0.20090319
* 作    者： huanggenping
* 完成日期： 2009-03-19
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
**********************************************************************/

#ifndef __COMP_INFO_H__
#define __COMP_INFO_H__

#include <utility>
#include "Public.h"

#if defined (__UI_SYSTEM__)
#include "DrawPaint.h"
#endif

struct TPyPartCand
{
	xstring strPyCode;
	xstring strPyWord;
	xstring strOrgWord;
	xstring strPyIndex;
};

//typedef pair <xstring, xstring> CPairPyPartCand;
typedef vector< TPyPartCand > CVectorPyPartCand;

class CCompInfo
{
public:

	/** @name 公用成员变量 */////////////////////////////////////////////////////
	/// @{
	
	// 输入的原始编码
	TCHAR m_strOriginalComp[MAX_PATH];
	// 解析以后的码表
	TCHAR m_strAnalyzeComp[MAX_PATH];
	// 部分已经上屏的候选汉字
	CVectorPyPartCand *m_pVectorPyPartCand;
	// 编码类型
	int m_nType;
	// 部分上屏候选字区域
	RECT m_rectPartCand;
	// 光标前面编码的左坐标
	int m_nPrevLeft;
	// 光标前面编码的上坐标
	int m_nPrevTop;
	// 光标前面编码的右坐标
	int m_nPrevRight;
	// 光标前面编码的下坐标
	int m_nPrevBottom;
	// 光标后面编码的左坐标
	int m_nBackLeft;
	// 光标后面编码的上坐标
	int m_nBackTop;
	// 光标后面编码的右坐标
	int m_nBackRight;
	// 光标后面编码的下坐标
	int m_nBackBottom;
	// 光标位置
	int m_nCursorPos;
	// 光标的起始位置的左坐标
	int m_nCursorLeft1;
	// 光标的起始位置的上坐标
	int m_nCursorTop1;
	// 光标的结束位置的左坐标
	int m_nCursorLeft2;
	// 光标的结束位置的上坐标
	int m_nCursorTop2;
	// 编码区提示文字最左边坐标
	int m_nHintLeft;
	// 编码区提示文字最上变坐标
	int m_nHintTop;
	// 编码区提示文字最右边坐标
	int m_nHintRight;
	// 编码区提示文字最下边坐标
	int m_nHintBottom;

	// 编码区最右边坐标
	int m_nRight;
	// 编码区最下边坐标
	int m_nBottom;
	// 是否是拼音分割编码
	BOOL m_bPySplitComp;
	// 是否网址直达
	int m_nWebSiteNonstop;
	// 是否网址补全（0：正常模式，-1：网址不补全，1：网址补全）
	int m_nWebSiteMatch;
	// 打字速度
	int m_nOutputSpeed;
	// 是否为测试编码
	BOOL m_bTestComp;
	// 是否选中提示区域
	BOOL m_bChooseHint;
	// 网址直达名字
	xstring m_strWebSiteNonstopName;
	// 网址直达信息
	xstring m_strWebSiteNonstopInfo;
	// 网址直达Url
	xstring m_strWebSiteNonstopUrl;

#if defined (__UI_SYSTEM__)
	CDrawPaint *m_pPartCandDrawPaint;
	//
	CDrawPaint *m_pPrevDrawPaint;
	//
	CDrawPaint *m_pBackDrawPaint;
	//
	CDrawPaint *m_pHintDrawPaint;
	//
	CDrawPaint *m_pCursorDrawPaint;
#endif

	/// @}

public:

	/** @name 构造和虚构函数 */////////////////////////////////////////////////////
    /// @{

	/**********************************************************************
	* 函数名称： CCompInfo
	* 功能描述： 
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2009/03/17		V1.0	    huanggenping	创建版本
	***********************************************************************/
	CCompInfo();
	
	/**********************************************************************
	* 函数名称： ~CCompInfo
	* 功能描述： 
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2009/03/17		V1.0	    huanggenping	创建版本
	***********************************************************************/
	~CCompInfo();

	/// @}

public:

	/** @name 公共成员函数 */////////////////////////////////////////////////////
    /// @{

	/**********************************************************************
	* 函数名称： Init
	* 功能描述： 
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2009/03/17		V1.0	    huanggenping	创建版本
	***********************************************************************/
	BOOL Init();

	/**********************************************************************
	* 函数名称： Clear
	* 功能描述： 
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2009/03/17		V1.0	    huanggenping	创建版本
	***********************************************************************/
	void Clear();
	
	/**********************************************************************
	* 函数名称： SetTempCompInfo
	* 功能描述： 
	* 输入参数： 
	* 输出参数：
	* 返 回 值： 
	* 其它说明： 
	* 修改日期			版本号		修改人			修改内容
	* ---------------------------------------------------------------------
	* 2009/03/17		V1.0	    huanggenping	创建版本
	***********************************************************************/
	void SetTempCompInfo();
	// 设置网址直达
	void SetWebSiteNonstopInfo(const TCHAR *lpszWebSiteNonstopName, const TCHAR *lpszWebSiteNonstopUrl, const TCHAR *lpszWebSiteNonstopHotKey);
	// 清空网址直达
	void ClearWebSiteNonstopInfo();
	// 部分已经上屏的候选汉字
	INT GetVectorPyPartCandSize();

	/// @}
};

#endif	// __COMP_INFO_H__