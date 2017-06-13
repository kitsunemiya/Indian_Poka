// DigitalPanel.cpp : 구현 파일입니다.
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



// CDigitalPanel 메시지 처리기입니다.




int CDigitalPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_Bitmap.LoadBitmapW(IDB_SCORE);

	return 0;
}


void CDigitalPanel::OnPaint()
{
CPaintDC dc(this); //화면 펜 객체 생성
CDC MemDC;   //메모리 펜 객체 생성
MemDC.CreateCompatibleDC(&dc);
MemDC.SelectObject(&m_Bitmap); //메모리에 숫자 이미지를 그린다.

int nValue = m_nValue; //점수 지정
int i, nDigit, nRadix = 1;

for(i=0 ; i<m_nRange-1 ; i++)   nRadix *= 10; 
//가장 큰 자릿수 계산, 점수 5234 일 때 5의 자리수 => 1000 

for(i=0 ; i<m_nRange ; i++) { //가장 왼쪽 숫자부터 처리
nDigit = nValue/nRadix;
dc.BitBlt(  i*DIGIT_PANEL_X, 0, DIGIT_PANEL_X, DIGIT_PANEL_Y, 
            &MemDC, DIGIT_PANEL_X*nDigit, 0, SRCCOPY);
//메모리에서 nDigit에 해당하는 숫자를 가져와 화면에 그린다.
nValue -= nDigit*nRadix;  //  5243일 때 5243-5000이므로 nValue는 243
nRadix /= 10; //다음 자리수, 가장 큰 자리수가 1000이면 다음 자리수는 100
}
}


BOOL CDigitalPanel::Create(int x, int y, int nRange, CWnd* pParentWnd)
{
m_nRange = nRange; //점수의 자리수 지정
CRect rect = CRect( x, //생성할 점수판의 크기
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


