#ifndef __DRAW_ARROW_H__
#define __DRAW_ARROW_H__

class CDrawArrow
{

public:

	/** @name 私有成员变量 *///////////////////////////////////////////////
    /// @{
	
	// 绘制周围的左边坐标
	int m_nLeftArrow;
	// 绘制周围的顶部坐标
	int m_nTopArrow;
	// 绘制周围的宽度
	int m_nWidthArrow;
	// 绘制周围的高度
	int m_nHeightArrow;
	
	/// @}

public:
	CDrawArrow(void)
	{
		m_nLeftArrow = 0;
		m_nTopArrow = 0;
		m_nWidthArrow = 0;
		m_nHeightArrow = 0;
	}
	~CDrawArrow(void)
	{

	}

public:

	void SetDrawArrow(const TCHAR * strName, const TCHAR * strValue)
	{
		if ((_tcscmp(strName, _T("leftArrow")) == 0))
		{
			m_nLeftArrow = _ttoi(strValue);
			return;
		}
		if (_tcscmp(strName, _T("topArrow")) == 0)
		{
			m_nTopArrow = _ttoi(strValue);
			return;
		}
		if (_tcscmp(strName, _T("widthArrow")) == 0)
		{
			m_nWidthArrow = _ttoi(strValue);
			return;
		}
		if (_tcscmp(strName, _T("heightArrow")) == 0)
		{
			m_nHeightArrow = _ttoi(strValue);
			return;
		}
	}
};

#endif	// __DRAW_ARROW_H__