//
#include "SDKDDKVER.h"
#include "stdafx.h"
#include "blackjack2.h"
#include "blackjack2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// Cblackjack2Dlg ��ȭ ����




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


// Cblackjack2Dlg �޽��� ó����

BOOL Cblackjack2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void Cblackjack2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR Cblackjack2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cblackjack2Dlg::OnPlay()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//GiveCard(FALSE); //ī�� �߰� ��� ����

	//if(m_nManScore >= 21)  ��� �ʰ� ���� ����
		//OnStand();
	CDC MemDC;
	CClientDC dc(this);
	MemDC.CreateCompatibleDC(&dc);

	m_Hit.ShowWindow(SW_HIDE);
	m_Stand.ShowWindow(SW_HIDE);

	MemDC.SelectObject(m_bmpLose); //�й� �޽����� �޸𸮿� �׸���.
	dc.BitBlt(200, 200, 156, 26, &MemDC, 0, 0, SRCCOPY); //ȭ�� ������ ȭ�鿡 �׸���.
	SetTimer(IDT_LOSEGAME, 2000, NULL); //�й� Ÿ�̸� ����


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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GiveCard(TRUE);
	m_Hit.ShowWindow(SW_HIDE);
	m_Stand.ShowWindow(SW_HIDE);
	SetTimer(IDT_DOCOMPUT, 500, NULL);

	
}

void Cblackjack2Dlg::DoComputer()
{
CClientDC dc(this); //�޽����� ����ϱ� ���� ȭ�� �� ��ü ����
CDC MemDC; //�޸� �� ��ü
MemDC.CreateCompatibleDC(&dc); //�� ���� ȣȯ��Ŵ

if (m_nManScore > m_nComputerScore) { //����� ������ ��ǻ�� �������� ������
	KillTimer(IDT_DOCOMPUT);
	MemDC.SelectObject(m_bmpWin); //�¸� �޽����� �޸𸮿� �׸���.
	dc.BitBlt(200, 200, 226, 26, &MemDC, 0, 0, SRCCOPY);  //ȭ�� ������ ȭ�鿡 �׸���.
	m_Hit.ShowWindow(SW_HIDE);
	m_Stand.ShowWindow(SW_HIDE);
	SetTimer(IDT_WINGAME, 2000, NULL); //�¸� Ÿ�̸� ����
	m_ComputerPanel.SetValue(m_nComputerScore); //��ǻ�� ������
	m_ManPanel.SetValue(m_nManScore); //��� ������
}
else if (m_nComputerScore > m_nManScore) { //��ǻ�Ͱ� ������� ������
	KillTimer(IDT_DOCOMPUT); //Ÿ�̸� ����, ���̻� DoComputer()�Լ� ȣ������ ����
	MemDC.SelectObject(m_bmpLose); //�й� �޽����� �޸𸮿� �׸���.
	dc.BitBlt(200, 200, 156, 26, &MemDC, 0, 0, SRCCOPY); //ȭ�� ������ ȭ�鿡 �׸���.
	SetTimer(IDT_LOSEGAME, 2000, NULL); //�й� Ÿ�̸� ����
	m_ComputerPanel.SetValue(m_nComputerScore); //��ǻ�� ������
	m_ManPanel.SetValue(m_nManScore); // ��� ������
}
else if (m_nManScore == m_nComputerScore) {   //���º�
	m_ComputerPanel.SetValue(m_nComputerScore);
	m_ManPanel.SetValue(m_nManScore);// ��� ������
	OnPlay();
}
/*if(m_nManScore > 21)  { //����� ������ 21�� �̻��̸� ������ ��ǻ�Ͱ� �̱�

KillTimer(IDT_DOCOMPUT); //Ÿ�̸� ����, ���̻� DoComputer()�Լ� ȣ������ ����
MemDC.SelectObject(m_bmpLose); //�й� �޽����� �޸𸮿� �׸���.
dc.BitBlt(200, 200, 156,26, &MemDC, 0, 0, SRCCOPY); //ȭ�� ������ ȭ�鿡 �׸���.
SetTimer(IDT_LOSEGAME, 2000, NULL); //�й� Ÿ�̸� ����
}
else if(m_nComputerScore < 21 
         && 21-m_nManScore < 21-m_nComputerScore) {
GiveCard(FALSE);
}
else  {
KillTimer(IDT_DOCOMPUT);  //Ÿ�̸� ����, ���̻� DoComputer()�Լ� ȣ������ ����
m_Hit.ShowWindow(SW_HIDE);
m_Stand.ShowWindow(SW_HIDE);

if(m_nComputerScore > 21)  {  //����� �¸�
MemDC.SelectObject(m_bmpWin); //�¸� �޽����� �޸𸮿� �׸���.
dc.BitBlt(200, 200, 226, 26, &MemDC, 0, 0, SRCCOPY);  //ȭ�� ������ ȭ�鿡 �׸���.
m_Hit.ShowWindow(SW_HIDE);
m_Stand.ShowWindow(SW_HIDE);
SetTimer(IDT_WINGAME, 2000, NULL); //�¸� Ÿ�̸� ����
}
else if(21-m_nManScore < 21-m_nComputerScore) {  //����� �¸�
MemDC.SelectObject(m_bmpWin);//�¸� �޽����� �޸𸮿� �׸���.
dc.BitBlt(200, 200, 226,26, &MemDC, 0, 0, SRCCOPY); //ȭ�� ������ ȭ�鿡 �׸���.
m_Hit.ShowWindow(SW_HIDE);
m_Stand.ShowWindow(SW_HIDE);
SetTimer(IDT_WINGAME, 2000, NULL);  //�¸� Ÿ�̸� ����
}
else if(m_nManScore == m_nComputerScore) {   //���º�
OnPlay();
}
else { //��ǻ���� �¸�
MemDC.SelectObject(m_bmpLose); //�й� �޽����� �޸𸮿� �׸���
dc.BitBlt(200, 200, 156,26, &MemDC, 0, 0, SRCCOPY); //ȭ�� ������ ȭ�鿡 �׸���.
m_Hit.ShowWindow(SW_HIDE);
m_Stand.ShowWindow(SW_HIDE);
SetTimer(IDT_LOSEGAME, 2000, NULL);  //�й� Ÿ�̸� ����
}
}*/
}

void Cblackjack2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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

KillTimer(IDT_WINGAME);  //Ÿ�̸� ���� ����
MemDC.SelectObject(m_bmpBackground); //�޸𸮿� ����� �׸���.
dc.BitBlt(200, 200, 226,26, &MemDC, 200, 200, SRCCOPY);
    //�¸� �޽��� �κ��� �ٽ� �������� ����
m_Paly.ShowWindow(SW_SHOW); //Let's Play�� ���̰� �Ѵ�.
}

void Cblackjack2Dlg::LoseGame()
{
CClientDC dc(this);
CDC MemDC;
MemDC.CreateCompatibleDC(&dc);

KillTimer(IDT_LOSEGAME);   //Ÿ�̸� ���� ����
MemDC.SelectObject(m_bmpBackground);  //�޸𸮿� ����� �׸���.
dc.BitBlt(200, 200, 226,26, &MemDC, 200, 200, SRCCOPY);
//�й� �޽��� �κ��� �ٽ� �������� ����
m_Paly.ShowWindow(SW_SHOW); //Let's Play�� ���̰� �Ѵ�.
}


BOOL Cblackjack2Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CDialogEx::OnEraseBkgnd(pDC);
}


