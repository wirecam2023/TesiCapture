// CSendPneuDLG.cpp : implementation file
//

#include "stdafx.h"
#include "Endox.h"
#include "SendPneuDLG.h"
#include "afxdialogex.h"


// CSendPneuDLG dialog

IMPLEMENT_DYNAMIC(CSendPneuDLG, CDialog)

CSendPneuDLG::CSendPneuDLG(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SENDPNEU, pParent)
{
	IsCancel = false;
	IsOnlyCard = false;
	IsWithPneu = false;
}

CSendPneuDLG::~CSendPneuDLG()
{
}

void CSendPneuDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSendPneuDLG, CDialog)
	ON_BN_CLICKED(ID_CANCEL, &CSendPneuDLG::OnBnClickedCancel)
	ON_BN_CLICKED(ID_ONLY_CARD, &CSendPneuDLG::OnBnClickedOnlyCard)
	ON_BN_CLICKED(ID_WITH_PNEU, &CSendPneuDLG::OnBnClickedWithPneu)
END_MESSAGE_MAP()


// CSendPneuDLG message handlers
