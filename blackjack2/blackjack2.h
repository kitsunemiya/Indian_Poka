
// blackjack2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cblackjack2App:
// �� Ŭ������ ������ ���ؼ��� blackjack2.cpp�� �����Ͻʽÿ�.
//

class Cblackjack2App : public CWinApp
{
public:
	Cblackjack2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cblackjack2App theApp;