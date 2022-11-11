#include "stdafx.h"
#include "Endox.h"
#include "EtichetteAnamnesiDlg.h"

#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEtichetteAnamnesiDlg::CEtichetteAnamnesiDlg(CWnd* pParent)
	: CDialog(CEtichetteAnamnesiDlg::IDD, pParent)
{
	for(int i = 0; i < NUM_FIELD_ANAM; i++)
	{
		m_sAnamText[i] = "";
		m_bAnamVisi[i] = FALSE;
		m_bAnamAuto[i] = FALSE;
	}
}


void CEtichetteAnamnesiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_15, m_ctrlStatic15);
	DDX_Control(pDX, IDC_STATIC_16, m_ctrlStatic16);
	DDX_Control(pDX, IDC_STATIC_17, m_ctrlStatic17);
	DDX_Control(pDX, IDC_STATIC_18, m_ctrlStatic18);
	DDX_Control(pDX, IDC_STATIC_19, m_ctrlStatic19);
	DDX_Control(pDX, IDC_STATIC_20, m_ctrlStatic20);
	DDX_Control(pDX, IDC_STATIC_21, m_ctrlStatic21);
	DDX_Control(pDX, IDC_STATIC_22, m_ctrlStatic22);
	DDX_Control(pDX, IDC_STATIC_23, m_ctrlStatic23);
	DDX_Control(pDX, IDC_STATIC_24, m_ctrlStatic24);
	DDX_Control(pDX, IDC_STATIC_25, m_ctrlStatic25);

	DDX_Control(pDX, IDC_STATIC_30, m_ctrlStatic30);
	DDX_Control(pDX, IDC_STATIC_31, m_ctrlStatic31);
	DDX_Control(pDX, IDC_STATIC_32, m_ctrlStatic32);
	DDX_Control(pDX, IDC_STATIC_33, m_ctrlStatic33);
	DDX_Control(pDX, IDC_STATIC_34, m_ctrlStatic34);
	DDX_Control(pDX, IDC_STATIC_35, m_ctrlStatic35);
	DDX_Control(pDX, IDC_STATIC_36, m_ctrlStatic36);
	DDX_Control(pDX, IDC_STATIC_37, m_ctrlStatic37);
	DDX_Control(pDX, IDC_STATIC_38, m_ctrlStatic38);
	DDX_Control(pDX, IDC_STATIC_39, m_ctrlStatic39);
	DDX_Control(pDX, IDC_STATIC_40, m_ctrlStatic40);

	DDX_Control(pDX, IDOK,     m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);

	if (!pDX->m_bSaveAndValidate)
	{
		DDX_Text(pDX, IDC_OLD_ANAM_1, theApp.m_sAnamText[0]);
		DDX_Text(pDX, IDC_OLD_ANAM_2, theApp.m_sAnamText[1]);
		DDX_Text(pDX, IDC_OLD_ANAM_3, theApp.m_sAnamText[2]);
		DDX_Text(pDX, IDC_OLD_ANAM_4, theApp.m_sAnamText[3]);
		DDX_Text(pDX, IDC_OLD_ANAM_5, theApp.m_sAnamText[4]);
		DDX_Text(pDX, IDC_OLD_ANAM_6, theApp.m_sAnamText[5]);
		DDX_Text(pDX, IDC_OLD_ANAM_7, theApp.m_sAnamText[6]);
		DDX_Text(pDX, IDC_OLD_ANAM_8, theApp.m_sAnamText[7]);
		DDX_Text(pDX, IDC_OLD_ANAM_9, theApp.m_sAnamText[8]);
		DDX_Text(pDX, IDC_OLD_ANAM_10, theApp.m_sAnamText[9]);
		DDX_Text(pDX, IDC_OLD_ANAM_11, theApp.m_sAnamText[10]);
	}

	DDX_Text(pDX, IDC_NEW_ANAM_1, m_sAnamText[0]);
	DDX_Text(pDX, IDC_NEW_ANAM_2, m_sAnamText[1]);
	DDX_Text(pDX, IDC_NEW_ANAM_3, m_sAnamText[2]);
	DDX_Text(pDX, IDC_NEW_ANAM_4, m_sAnamText[3]);
	DDX_Text(pDX, IDC_NEW_ANAM_5, m_sAnamText[4]);
	DDX_Text(pDX, IDC_NEW_ANAM_6, m_sAnamText[5]);
	DDX_Text(pDX, IDC_NEW_ANAM_7, m_sAnamText[6]);
	DDX_Text(pDX, IDC_NEW_ANAM_8, m_sAnamText[7]);
	DDX_Text(pDX, IDC_NEW_ANAM_9, m_sAnamText[8]);
	DDX_Text(pDX, IDC_NEW_ANAM_10, m_sAnamText[9]);
	DDX_Text(pDX, IDC_NEW_ANAM_11, m_sAnamText[10]);

	DDX_Check(pDX, IDC_VIS_ANAM_1, m_bAnamVisi[0]);
	DDX_Check(pDX, IDC_VIS_ANAM_2, m_bAnamVisi[1]);
	DDX_Check(pDX, IDC_VIS_ANAM_3, m_bAnamVisi[2]);
	DDX_Check(pDX, IDC_VIS_ANAM_4, m_bAnamVisi[3]);
	DDX_Check(pDX, IDC_VIS_ANAM_5, m_bAnamVisi[4]);
	DDX_Check(pDX, IDC_VIS_ANAM_6, m_bAnamVisi[5]);
	DDX_Check(pDX, IDC_VIS_ANAM_7, m_bAnamVisi[6]);
	DDX_Check(pDX, IDC_VIS_ANAM_8, m_bAnamVisi[7]);
	DDX_Check(pDX, IDC_VIS_ANAM_9, m_bAnamVisi[8]);
	DDX_Check(pDX, IDC_VIS_ANAM_10, m_bAnamVisi[9]);
	DDX_Check(pDX, IDC_VIS_ANAM_11, m_bAnamVisi[10]);

	DDX_Check(pDX, IDC_AUTO_ANAM_1, m_bAnamAuto[0]);
	DDX_Check(pDX, IDC_AUTO_ANAM_2, m_bAnamAuto[1]);
	DDX_Check(pDX, IDC_AUTO_ANAM_3, m_bAnamAuto[2]);
	DDX_Check(pDX, IDC_AUTO_ANAM_4, m_bAnamAuto[3]);
	DDX_Check(pDX, IDC_AUTO_ANAM_5, m_bAnamAuto[4]);
	DDX_Check(pDX, IDC_AUTO_ANAM_6, m_bAnamAuto[5]);
	DDX_Check(pDX, IDC_AUTO_ANAM_7, m_bAnamAuto[6]);
	DDX_Check(pDX, IDC_AUTO_ANAM_8, m_bAnamAuto[7]);
	DDX_Check(pDX, IDC_AUTO_ANAM_9, m_bAnamAuto[8]);
	DDX_Check(pDX, IDC_AUTO_ANAM_10, m_bAnamAuto[9]);
	DDX_Check(pDX, IDC_AUTO_ANAM_11, m_bAnamAuto[10]);
}

BEGIN_MESSAGE_MAP(CEtichetteAnamnesiDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

HBRUSH CEtichetteAnamnesiDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_OLD_ANAM_1:
		case IDC_OLD_ANAM_2:
		case IDC_OLD_ANAM_3:
		case IDC_OLD_ANAM_4:
		case IDC_OLD_ANAM_5:
		case IDC_OLD_ANAM_6:
		case IDC_OLD_ANAM_7:
		case IDC_OLD_ANAM_8:
		case IDC_OLD_ANAM_9:
		case IDC_OLD_ANAM_10:
		case IDC_OLD_ANAM_11:
		case IDC_NEW_ANAM_1:
		case IDC_NEW_ANAM_2:
		case IDC_NEW_ANAM_3:
		case IDC_NEW_ANAM_4:
		case IDC_NEW_ANAM_5:
		case IDC_NEW_ANAM_6:
		case IDC_NEW_ANAM_7:
		case IDC_NEW_ANAM_8:
		case IDC_NEW_ANAM_9:
		case IDC_NEW_ANAM_10:
		case IDC_NEW_ANAM_11:
		case IDC_STATIC_15:
		case IDC_STATIC_16:
		case IDC_STATIC_17:
		case IDC_STATIC_18:
		case IDC_STATIC_19:
		case IDC_STATIC_20:
		case IDC_STATIC_21:
		case IDC_STATIC_22:
		case IDC_STATIC_23:
		case IDC_STATIC_24:
		case IDC_STATIC_25:
		case IDC_STATIC_30:
		case IDC_STATIC_31:
		case IDC_STATIC_32:
		case IDC_STATIC_33:
		case IDC_STATIC_34:
		case IDC_STATIC_35:
		case IDC_STATIC_36:
		case IDC_STATIC_37:
		case IDC_STATIC_38:
		case IDC_STATIC_39:
		case IDC_STATIC_40:

			pDC->SetTextColor(theApp.m_color[4]);
			break;
	}

	return hBrush;
}

BOOL CEtichetteAnamnesiDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	for(int i = 0; i < NUM_FIELD_ANAM; i++)
	{
		m_sAnamText[i] = theApp.m_sAnamText[i];
		m_bAnamVisi[i] = theApp.m_bAnamVisi[i];
		m_bAnamAuto[i] = theApp.m_bAnamAuto[i];
	}

	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);

	UpdateData(FALSE);

	theApp.LocalizeDialog(this, CEtichetteAnamnesiDlg::IDD, "LabelAnamnesiDlg");
	return TRUE;
}

void CEtichetteAnamnesiDlg::OnOK() 
{
	UpdateData(TRUE);

	for(int i = 0; i < NUM_FIELD_ANAM; i++)
	{
		theApp.m_sAnamText[i] = m_sAnamText[i];
		theApp.m_bAnamVisi[i] = m_bAnamVisi[i];
		theApp.m_bAnamAuto[i] = m_bAnamAuto[i];
	}

	CDialog::OnOK();
}
