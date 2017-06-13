//
#include "SDKDDKVER.h"
#include "stdafx.h"
#include "blackjack2.h"
#include "blackjack2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cblackjack2Dlg 대화 상자




Cblackjack2Dlg::Cblackjack2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cblackjack2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nWin = 20000;
	m_nManNum = m_nComputerNum = m_nManScore = m_nComputerScore = 0;
	m_nSequence = 0;
	for(int i=0; i<52; i++)
		m_bReleased[i] = FALSE;;
}

void Cblackjack2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Hit, m_Hit);
	DDX_Control(pDX, IDC_Play, m_Paly);
	DDX_Control(pDX, IDC_STAND, m_Stand);
}

BEGIN_MESSAGE_MAP(Cblackjack2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Play, &Cblackjack2Dlg::OnPlay)
	ON_BN_CLICKED(IDC_Hit, &Cblackjack2Dlg::OnHit)
	ON_BN_CLICKED(IDC_STAND, &Cblackjack2Dlg::OnStand)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// Cblackjack2Dlg 메시지 처리기

BOOL Cblackjack2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_bmpCard.LoadBitmap(IDB_Card);
	m_bmpBackground.LoadBitmap(IDB_back);
	m_bmpLose.LoadBitmap(IDB_lose);
	m_bmpWin.LoadBitmap(IDB_win);
	m_bmpCardMask.LoadBitmap(IDB_CardMask);

	m_Hit.ShowWindow(SW_HIDE);
	m_Stand.ShowWindow(SW_HIDE);

	m_ManPanel.Create(120, 206, 2, this);
	m_ComputerPanel.Create(120, 22, 2, this);
	m_WinPanel.Create(540, 30, 6, this);

	m_WinPanel.SetValue(m_nWin);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cblackjack2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cblackjack2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC MemDC;
		MemDC.CreateCompatibleDC(&dc);
		MemDC.SelectObject(&m_bmpBackground);
		dc.BitBlt(0, 0, rect.right, rect.bottom, &MemDC, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cblackjack2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cblackjack2Dlg::OnPlay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Paly.ShowWindow(SW_HIDE);
	InvalidateRect(NULL);

	m_nManNum = m_nComputerNum = 0;
	m_nManScore = m_nComputerScore = 0;
	m_nSequence = 0;
	for(int i=0; i<52 ; i++)
		m_bReleased[i] = FALSE;
	SetTimer(IDT_DISTCARD, 1000, NULL);
	m_ComputerPanel.SetValue(m_nComputerScore);
	m_ManPanel.SetValue(m_nManScore);
	
}


void Cblackjack2Dlg::OnHit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//GiveCard(FALSE); //카드 추가 배분 제거

	//if(m_nManScore >= 21)  사람 초과 숫자 제거
		//OnStand();
	CDC MemDC;
	CClientDC dc(this);
	MemDC.CreateCompatibleDC(&dc);

	m_Hit.ShowWindow(SW_HIDE);
	m_Stand.ShowWindow(SW_HIDE);

	MemDC.SelectObject(m_bmpLose); //패배 메시지를 메모리에 그린다.
	dc.BitBlt(200, 200, 156, 26, &MemDC, 0, 0, SRCCOPY); //화면 펜으로 화면에 그린다.
	SetTimer(IDT_LOSEGAME, 2000, NULL); //패배 타이머 설정


}

void Cblackjack2Dlg::CalcScore(int *nCard, int &nNum, int &nScore)
{
	int nS;
	BOOL bAce[4];
	nScore = 0;

	bAce[0] = bAce[1] = bAce[2] = bAce[3] = FALSE;
	for(int i = 0; i < nNum ; i++)
	{
		if(nCard[i] == 0) {
			bAce[0] = TRUE; nScore += 11;
		} else if(nCard[i] == 13) {
			bAce[1] = TRUE; nScore += 11;
		} else if(nCard[i] == 26) {
			bAce[2] = TRUE; nScore += 11;
		} else if(nCard[i] == 39) {
			bAce[3] = TRUE; nScore += 11;
		} else {
			nS = nCard[i] - 13*(nCard[i]/13)+1;
			if(nS > 10) nS = 10;
			nScore += nS;
		}
	}
	for(int i= 0; i < 4; i++)
		if(nScore > 21 && bAce[i]) nScore -= 10;
}


void Cblackjack2Dlg::OnStand()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GiveCard(TRUE);
	m_Hit.ShowWindow(SW_HIDE);
	m_Stand.ShowWindow(SW_HIDE);
	SetTimer(IDT_DOCOMPUT, 500, NULL);

	
}

void Cblackjack2Dlg::DoComputer()
{
CClientDC dc(this); //메시지를 출력하기 위한 화면 펜 객체 생성
CDC MemDC; //메모리 펜 객체
MemDC.CreateCompatibleDC(&dc); //두 펜을 호환시킴

if (m_nManScore > m_nComputerScore) { //사람의 점수가 컴퓨터 점수보다 높으면
	KillTimer(IDT_DOCOMPUT);
	MemDC.SelectObject(m_bmpWin); //승리 메시지를 메모리에 그린다.
	dc.BitBlt(200, 200, 226, 26, &MemDC, 0, 0, SRCCOPY);  //화면 펜으로 화면에 그린다.
	m_Hit.ShowWindow(SW_HIDE);
	m_Stand.ShowWindow(SW_HIDE);
	SetTimer(IDT_WINGAME, 2000, NULL); //승리 타이머 설정
	m_ComputerPanel.SetValue(m_nComputerScore); //컴퓨터 점수판
	m_ManPanel.SetValue(m_nManScore); //사람 점수판
}
else if (m_nComputerScore > m_nManScore) { //컴퓨터가 사람보다 많으면
	KillTimer(IDT_DOCOMPUT); //타이머 해제, 더이상 DoComputer()함수 호출하지 않음
	MemDC.SelectObject(m_bmpLose); //패배 메시지를 메모리에 그린다.
	dc.BitBlt(200, 200, 156, 26, &MemDC, 0, 0, SRCCOPY); //화면 펜으로 화면에 그린다.
	SetTimer(IDT_LOSEGAME, 2000, NULL); //패배 타이머 설정
	m_ComputerPanel.SetValue(m_nComputerScore); //컴퓨터 점수판
	m_ManPanel.SetValue(m_nManScore); // 사람 점수판
}
else if (m_nManScore == m_nComputerScore) {   //무승부
	m_ComputerPanel.SetValue(m_nComputerScore);
	m_ManPanel.SetValue(m_nManScore);// 사람 점수판
	OnPlay();
}
/*if(m_nManScore > 21)  { //사람의 점수가 21점 이상이면 무조건 컴퓨터가 이김

KillTimer(IDT_DOCOMPUT); //타이머 해제, 더이상 DoComputer()함수 호출하지 않음
MemDC.SelectObject(m_bmpLose); //패배 메시지를 메모리에 그린다.
dc.BitBlt(200, 200, 156,26, &MemDC, 0, 0, SRCCOPY); //화면 펜으로 화면에 그린다.
SetTimer(IDT_LOSEGAME, 2000, NULL); //패배 타이머 설정
}
else if(m_nComputerScore < 21 
         && 21-m_nManScore < 21-m_nComputerScore) {
GiveCard(FALSE);
}
else  {
KillTimer(IDT_DOCOMPUT);  //타이머 해제, 더이상 DoComputer()함수 호출하지 않음
m_Hit.ShowWindow(SW_HIDE);
m_Stand.ShowWindow(SW_HIDE);

if(m_nComputerScore > 21)  {  //사람이 승리
MemDC.SelectObject(m_bmpWin); //승리 메시지를 메모리에 그린다.
dc.BitBlt(200, 200, 226, 26, &MemDC, 0, 0, SRCCOPY);  //화면 펜으로 화면에 그린다.
m_Hit.ShowWindow(SW_HIDE);
m_Stand.ShowWindow(SW_HIDE);
SetTimer(IDT_WINGAME, 2000, NULL); //승리 타이머 설정
}
else if(21-m_nManScore < 21-m_nComputerScore) {  //사람이 승리
MemDC.SelectObject(m_bmpWin);//승리 메시지를 메모리에 그린다.
dc.BitBlt(200, 200, 226,26, &MemDC, 0, 0, SRCCOPY); //화면 펜으로 화면에 그린다.
m_Hit.ShowWindow(SW_HIDE);
m_Stand.ShowWindow(SW_HIDE);
SetTimer(IDT_WINGAME, 2000, NULL);  //승리 타이머 설정
}
else if(m_nManScore == m_nComputerScore) {   //무승부
OnPlay();
}
else { //컴퓨터의 승리
MemDC.SelectObject(m_bmpLose); //패배 메시지를 메모리에 그린다
dc.BitBlt(200, 200, 156,26, &MemDC, 0, 0, SRCCOPY); //화면 펜으로 화면에 그린다.
m_Hit.ShowWindow(SW_HIDE);
m_Stand.ShowWindow(SW_HIDE);
SetTimer(IDT_LOSEGAME, 2000, NULL);  //패배 타이머 설정
}
}*/
}

void Cblackjack2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch(nIDEvent)
	{
	case IDT_DISTCARD: DistributeCard(); break;
case IDT_DOCOMPUT: DoComputer(); break;
case IDT_LOSEGAME: LoseGame(); break;
case IDT_WINGAME : WinGame(); break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void Cblackjack2Dlg::DistributeCard()
{
	switch(m_nSequence)
	{
	case 0:
	{GiveCard(FALSE); 
	//KillTimer(IDT_DISTCARD);
	//m_Hit.ShowWindow(SW_SHOW);
	//m_Stand.ShowWindow(SW_SHOW);
	//m_nSequence + 1;
	break;
	}
	case 1://GiveCard(TRUE);
		break;
	case 2:KillTimer(IDT_DISTCARD);
		m_Hit.ShowWindow(SW_SHOW);
		m_Stand.ShowWindow(SW_SHOW);
		break;
	}
	m_nSequence++;
}

void Cblackjack2Dlg::GiveCard(BOOL bMan)
{
	int nCard;
	srand(GetCurrentTime());
	do
	{
		nCard = rand()*51/(RAND_MAX+1);
	}while(m_bReleased[nCard] != FALSE);
	m_bReleased[nCard] = TRUE;
	if(bMan)
	{
		m_nManCard[m_nManNum] = nCard;
		DrawCard(nCard,m_nManNum+19, YPOSMAN);
		m_nManNum++;
		CalcScore(m_nManCard, m_nManNum, m_nManScore);
		
		
	}
	else
	{
		m_nComputerCard[m_nComputerNum] = nCard;
		DrawCard(nCard, MARGIN+m_nComputerNum*(CARDWIDTH+GAP), YPOSCOM);
		m_nComputerNum++;
		CalcScore(m_nComputerCard, m_nComputerNum, m_nComputerScore);
		//m_nManCard[m_nManNum] = nCard;
		DrawCardMan(nCard, MARGIN + m_nManNum*(CARDWIDTH + GAP), YPOSMAN);
		//m_nManNum++;
		CalcScore(m_nManCard, m_nManNum, m_nManScore);
		
	}
}

void Cblackjack2Dlg::DrawCard(int nCard, int x, int y)
{
	int nX = nCard/13;
	int nY = nCard%13;

	CClientDC dc(this);
	CDC MemDC;

	MemDC.CreateCompatibleDC(&dc);
	MemDC.SelectObject(&m_bmpCardMask);
	dc.BitBlt(x, y, CARDWIDTH, CARDHEIGHT, &MemDC, 0, 0, SRCAND);
	MemDC.SelectObject(&m_bmpCard);
	dc.BitBlt(x, y, CARDWIDTH, CARDHEIGHT, &MemDC, nX*CARDWIDTH, nY*CARDHEIGHT, SRCPAINT);
}
void Cblackjack2Dlg::DrawCardMan(int nCard, int x, int y)
{
	int nX = nCard / 13;
	int nY = nCard % 13;

	CClientDC dc(this);
	CDC MemDC;

	MemDC.CreateCompatibleDC(&dc);
	MemDC.SelectObject(&m_bmpCardMask);
	dc.BitBlt(x, y, CARDWIDTH, CARDHEIGHT, &MemDC, 0, 0, SRCAND);
	MemDC.SelectObject(&m_bmpCard);
	dc.BitBlt(x, y, CARDWIDTH, CARDHEIGHT, &MemDC, nX*CARDWIDTH, nY*CARDHEIGHT, SRCPAINT);
	MemDC.SelectObject(&m_bmpCardMask);
	dc.BitBlt(x, y, CARDWIDTH, CARDHEIGHT, &MemDC, 0, 0, SRCAND);
}

void Cblackjack2Dlg::WinGame()
{
CClientDC dc(this);
CDC MemDC;
MemDC.CreateCompatibleDC(&dc);

KillTimer(IDT_WINGAME);  //타이머 설정 해제
MemDC.SelectObject(m_bmpBackground); //메모리에 배경을 그린다.
dc.BitBlt(200, 200, 226,26, &MemDC, 200, 200, SRCCOPY);
    //승리 메시지 부분을 다시 배경색으로 돌림
m_Paly.ShowWindow(SW_SHOW); //Let's Play를 보이게 한다.
}

void Cblackjack2Dlg::LoseGame()
{
CClientDC dc(this);
CDC MemDC;
MemDC.CreateCompatibleDC(&dc);

KillTimer(IDT_LOSEGAME);   //타이머 설정 해제
MemDC.SelectObject(m_bmpBackground);  //메모리에 배경을 그린다.
dc.BitBlt(200, 200, 226,26, &MemDC, 200, 200, SRCCOPY);
//패배 메시지 부분을 다시 배경색으로 돌림
m_Paly.ShowWindow(SW_SHOW); //Let's Play를 보이게 한다.
}


BOOL Cblackjack2Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


