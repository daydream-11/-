#ifndef __AROUND_RECT_H__
#define __AROUND_RECT_H__

class CAroundRect
{

public:

	/** @name 私有成员变量 *///////////////////////////////////////////////
    /// @{
	
	// 绘制周围的左边坐标
	int m_nLeftAround;
	// 绘制周围的顶部坐标
	int m_nTopAround;
	// 绘制周围的宽度
	int m_nWidthAround;
	// 绘制周围的高度
	int m_nHeightAround;
	
	/// @}

public:
	CAroundRect(void)
	{
		m_nLeftAround = 0;
		m_nTopAround = 0;
		m_nWidthAround = 0;
		m_nHeightAround = 0;
	}
	~CAroundRect(void)
	{

	}

public:

	void SetAroundRect(const TCHAR * strName, const TCHAR * strValue)
	{
		
	}
};

#endif	// __AROUND_RECT_H__