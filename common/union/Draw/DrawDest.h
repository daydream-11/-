#ifndef __DRAW_DEST_H__
#define __DRAW_DEST_H__

class CDrawDest
{

public:

	/** @name 私有成员变量 *///////////////////////////////////////////////
    /// @{
	
	// 绘制左边坐标
	int m_nLeftDest;
	// 绘制顶部坐标
	int m_nTopDest;
	// 绘制宽度
	int m_nWidthDest;
	// 绘制高度
	int m_nHeightDest;
	
	/// @}

public:
	CDrawDest(void)
	{
		m_nLeftDest = 0;
		m_nTopDest = 0;
		m_nWidthDest = 0;
		m_nHeightDest = 0;
	}
	~CDrawDest(void)
	{

	}

public:

	void SetDrawDest(const TCHAR * strName, const TCHAR * strValue)
	{
		if ((_tcscmp(strName, _T("leftDest")) == 0))
		{
			m_nLeftDest = _ttoi(strValue);
			return;
		}
		if (_tcscmp(strName, _T("topDest")) == 0)
		{
			m_nTopDest = _ttoi(strValue);
			return;
		}
		if (_tcscmp(strName, _T("widthDest")) == 0)
		{
			m_nWidthDest = _ttoi(strValue);
			return;
		}
		if (_tcscmp(strName, _T("heightDest")) == 0)
		{
			m_nHeightDest = _ttoi(strValue);
			return;
		}
	}
};

#endif	// __DRAW_DEST_H__