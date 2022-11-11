#include "stdafx.h"
#include "Endox.h"
#include "LinguettaDlg.h"
#include "Report.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CLinguettaDlg, CDialog)

CLinguettaDlg::CLinguettaDlg(CWnd* pParent, BOOL bAddNew, CTabCtrl* pTabCtrl)
	: CDialog(CLinguettaDlg::IDD, pParent)
{
	ASSERT(pTabCtrl != NULL);

	m_bAddNew = bAddNew;
	m_pTabCtrl = pTabCtrl;

	m_sOldEditText = "";
	m_lOldAlbum = 0;
	m_nRadioAlbum = 0;
	m_bOldCheck = TRUE;
	m_bCheck = TRUE;

	m_lIndex = m_pTabCtrl->GetCurSel();
	m_lOldIndex = m_lIndex;
	if (m_lIndex >= 0)
	{
		char szBuffer[1024];
		ZeroMemory(szBuffer, 1024 * sizeof(char));

		TCITEM item;
		item.mask = TCIF_PARAM | TCIF_TEXT;
		item.pszText = szBuffer;
		item.cchTextMax = 1024;

		m_pTabCtrl->GetItem(m_lIndex, &item);

		m_LParam = item.lParam;
		m_sEditText = szBuffer;

		m_sOldEditText = m_sEditText;
		m_lOldAlbum = ((STRUCT_LINGUETTA*)m_LParam)->lMostraAlbum;
		m_nRadioAlbum = ((STRUCT_LINGUETTA*)m_LParam)->lMostraAlbum;
		m_bOldCheck = ((STRUCT_LINGUETTA*)m_LParam)->bVisualizzaSempre;
		m_bCheck = ((STRUCT_LINGUETTA*)m_LParam)->bVisualizzaSempre;
	}
}

CLinguettaDlg::~CLinguettaDlg()
{
}

BEGIN_MESSAGE_MAP(CLinguettaDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT, OnEnChangeEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, OnDeltaposSpin)
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO4, OnBnClickedRadio)
END_MESSAGE_MAP()

void CLinguettaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_7, m_ctrlStatic7);
	DDX_Control(pDX, IDCANCEL,     m_ctrlButton1);
	DDX_Control(pDX, IDOK,         m_ctrlButton2);

	DDX_Control(pDX, IDC_SPIN, m_ctrlSpin);
	DDX_Radio(pDX, IDC_RADIO1, m_nRadioAlbum);
	DDX_Check(pDX, IDC_CHECK, m_bCheck);
}

void CLinguettaDlg::OnCancel()
{
	// if (theApp.AfxMessageBoxEndo(Uscire annullando le modifiche effettuate?, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
	{
		if (m_bAddNew == FALSE)
		{
			m_pTabCtrl->DeleteItem(m_lIndex);

			((STRUCT_LINGUETTA*)m_LParam)->lMostraAlbum = m_lOldAlbum;
			((STRUCT_LINGUETTA*)m_LParam)->bVisualizzaSempre = m_bOldCheck;

			TCITEM item;
			item.mask = TCIF_PARAM | TCIF_TEXT;
			item.lParam = m_LParam;
			item.pszText = (LPTSTR)((LPCTSTR)m_sOldEditText);
			item.cchTextMax = 1024;

			if (m_lOldIndex >= 0)
				m_pTabCtrl->InsertItem(m_lOldIndex, &item);
		}

		CDialog::OnCancel();
	}
}

BOOL CLinguettaDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CLinguettaDlg::IDD, "LinguettaDlg");

	SetWindowText(theApp.GetMessageString(m_bAddNew ? IDS_LINGUETTA_TITLE_1 : IDS_LINGUETTA_TITLE_2));
	SetDlgItemText(IDC_EDIT, m_sEditText);

	UDACCEL pAccel[1];
	pAccel[0].nSec = 0;
	pAccel[0].nInc = 1;

	m_ctrlSpin.SetRange32(0, m_pTabCtrl->GetItemCount() - 1);
	m_ctrlSpin.SetPos32(m_lIndex);
	m_ctrlSpin.SetAccel(1, pAccel);

	return bReturn;
}

void CLinguettaDlg::OnEnChangeEdit()
{
	char buffer[1024];
	GetDlgItemText(IDC_EDIT, buffer, 1024);

	TCITEM tabItem;
	tabItem.mask = TCIF_TEXT;
	tabItem.pszText = buffer;
	tabItem.cchTextMax = 1024;

	m_pTabCtrl->SetItem(m_lIndex, &tabItem);
}

void CLinguettaDlg::OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	m_pTabCtrl->DeleteItem(pNMUpDown->iPos);

	char buffer[1024];
	GetDlgItemText(IDC_EDIT, buffer, 1024);

	TCITEM tabItem;
	tabItem.mask = TCIF_PARAM | TCIF_TEXT;
	tabItem.lParam = m_LParam;
	tabItem.pszText = buffer;
	tabItem.cchTextMax = 1024;

	if (pNMUpDown->iDelta < 0)
		m_lIndex = max(0, pNMUpDown->iPos + pNMUpDown->iDelta);
	else
		m_lIndex = min(m_pTabCtrl->GetItemCount(), pNMUpDown->iPos + pNMUpDown->iDelta);

	m_pTabCtrl->InsertItem(m_lIndex, &tabItem);

	*pResult = 0;
}

void CLinguettaDlg::OnBnClickedRadio()
{
	STRUCT_LINGUETTA* m_pLinguetta = (STRUCT_LINGUETTA*)m_LParam;

	if (m_pLinguetta != NULL)
	{
		UpdateData(TRUE);
		m_pLinguetta->lMostraAlbum = m_nRadioAlbum;
		m_pParentWnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE);
	}
}