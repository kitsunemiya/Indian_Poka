// DigitalPanel.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "blackjack2.h"
#include "DigitalPanel.h"


// CDigitalPanel

IMPLEMENT_DYNAMIC(CDigitalPanel, CWnd)

CDigitalPanel::CDigitalPanel()
{

}

CDigitalPanel::~CDigitalPanel()
{
}


BEGIN_MESSAGE_MAP(CDigitalPanel, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CDigitalPanel �޽��� ó�����Դϴ�.




int CDigitalPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_Bitmap.LoadBitmapW(IDB_SCORE);

	return 0;
}


void CDigitalPanel::OnPaint()
{
CPaintDC dc(this); //ȭ�� �� ��ü ����
CDC MemDC;   //�޸� �� ��ü ����
MemDC.CreateCompatibleDC(&dc);
MemDC.SelectObject(&m_Bitmap); //�޸𸮿� ���� �̹����� �׸���.

int nValue = m_nValue; //���� ����
int i, nDigit, nRadix = 1;

for(i=0 ; i<m_nRange-1 ; i++)   nRadix *= 10; 
//���� ū �ڸ��� ���, ���� 5234 �� �� 5�� �ڸ��� => 1000 

for(i=0 ; i<m_nRange ; i++) { //���� ���� ���ں��� ó��
nDigit = nValue/nRadix;
dc.BitBlt(  i*DIGIT_PANEL_X, 0, DIGIT_PANEL_X, DIGIT_PANEL_Y, 
            &MemDC, DIGIT_PANEL_X*nDigit, 0, SRCCOPY);
//�޸𸮿��� nDigit�� �ش��ϴ� ���ڸ� ������ ȭ�鿡 �׸���.
nValue -= nDigit*nRadix;  //  5243�� �� 5243-5000�̹Ƿ� nValue�� 243
nRadix /= 10; //���� �ڸ���, ���� ū �ڸ����� 1000�̸� ���� �ڸ����� 100
}
}


BOOL CDigitalPanel::Create(int x, int y, int nRange, CWnd* pParentWnd)
{
m_nRange = nRange; //������ �ڸ��� ����
CRect rect = CRect( x, //������ �������� ũ��
y,
x+nRange*DIGIT_PANEL_X+2,
y+DIGIT_PANEL_Y );
return CWnd::Create(NULL, NULL, WS_CHILD|WS_VISIBLE , rect, pParentWnd, 0);}void CDigitalPanel::SetValue(int nValue)
{

int i, nDigit, nRadix = 1;
CClientDC dc(this);
CDC MemDC;
MemDC.CreateCompatibleDC(&dc);
MemDC.SelectObject(&m_Bitmap);

m_nValue = nValue;
for(i=0 ; i<m_nRange-1 ; i++)  nRadix *= 10;

for(i=0 ; i<m_nRange ; i++)   {
nDigit = nValue/nRadix;
dc.BitBlt( i*DIGIT_PANEL_X, 0, DIGIT_PANEL_X, DIGIT_PANEL_Y, 
&MemDC, DIGIT_PANEL_X*nDigit, 0, SRCCOPY);
nValue -= nDigit*nRadix;
nRadix /= 10;
}
}


