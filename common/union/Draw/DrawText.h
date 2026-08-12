#ifndef __DRAW_TEXT_H__
#define __DRAW_TEXT_H__

class CDrawText
{

public:

	/** @name 私有成员变量 *///////////////////////////////////////////////
    /// @{
	
	// 绘制周围的左边坐标
	int m_nLeftText;
	// 绘制周围的顶部坐标
	int m_nTopText;
	// 绘制周围的宽度
	int m_nWidthText;
	// 绘制周围的高度
	int m_nHeightText;
	
	/// @}

public:
	CDrawText(void)
	{
		m_nLeftText = 0;
		m_nTopText = 0;
		m_nWidthText = 0;
		m_nHeightText = 0;
	}
	~CDrawText(void)
	{

	}

public:

	void SetDrawText(const TCHAR * strName, const TCHAR * strValue)
	{
		
	}

};

#endif	// __DRAW_TEXT_H__