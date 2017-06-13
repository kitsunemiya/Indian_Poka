#include "DigitalPanel.h"
// blackjack2Dlg.h : ��� ����
//

#pragma once

#define IDT_DISTCARD 0
#define IDT_DOCOMPUT 1
#define IDT_LOSEGAME 2
#define IDT_WINGAME 3
#define CARDWIDTH 71
#define CARDHEIGHT 96
#define MARGIN 20 // ������ ������ �Ÿ�
#define GAP 10 // ī�� ������ �Ÿ�
#define YPOSMAN 260
#define YPOSCOM 70


// Cblackjack2Dlg ��ȭ ����
class Cblackjack2Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	Cblackjack2Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BLACKJACK2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_Hit;
	CButton m_Paly;
	CButton m_Stand;
	afx_msg void OnPlay();
	afx_msg void OnHit();
	afx_msg void OnStand();

private:
	int m_nWin;
	int m_nSequence;
	int m_nManNum;
	int m_nComputerNum;
	int m_nManScore;
	int m_nComputerScore;
	int m_nManCard[10];
	int m_nComputerCard[10];
	bool m_bReleased[52];
	bool gameEnd;

	CBitmap m_bmpCard;
	CBitmap m_bmpCardMask;
	CBitmap m_bmpBackground;
	CBitmap m_bmpLose;
	CBitmap m_bmpWin;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void DistributeCard();
	void GiveCard(BOOL bMan);
	void DrawCard(int nCard,int x, int y);
	void DrawCardMan(int nCard, int x, int y);
	void CalcScore( int Card[], int &Num, int &Score);
	void DoComputer();
	void WinGame();
	void LoseGame();
	CDigitalPanel m_ManPanel; // ���� (���)
CDigitalPanel m_ComputerPanel; // ���� (��ǻ��)
CDigitalPanel m_WinPanel; // ���� ������ �ִ� �ݾ�
};
