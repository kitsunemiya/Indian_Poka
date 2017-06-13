#pragma once


// CDigitalPanel

#define DIGIT_PANEL_X 15
#define DIGIT_PANEL_Y 20

class CDigitalPanel : public CWnd
{
	DECLARE_DYNAMIC(CDigitalPanel)


public:
	CDigitalPanel();
	virtual ~CDigitalPanel();

private:
	int m_nValue;
	int m_nRange;
	CBitmap m_Bitmap;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	BOOL Create(int x, int y, int nRange, CWnd* pParentWnd ); 
	void SetValue(int nValue); 
};


