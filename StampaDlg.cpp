#include "stdafx.h"
#include "Endox.h"
#include "StampaDlg.h"

#include "EsamiDoc.h"
#include "EsamiView.h"
#include "HeaderFooterSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CStampaDlg::CStampaDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CStampaDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	m_pEsamiView = pEsamiView;

	m_bPrintComment = theApp.m_bStampaImmaginiStampaCommenti;
	m_bPrintPazData = theApp.m_bStampaImmaginiStampaDatiPaziente;
	m_bStampaNumero = theApp.m_bStampaImmaginiStampaNumero;
	m_nDistImmagini = theApp.m_nStampaImmaginiDistanzaImmagini;
	m_nTypePrintImage = theApp.m_nStampaImmaginiTipoDiStampa;
	m_lIDStampante = theApp.m_lIDStampanteImmagini;

	// Sandro 26/10/2015 //
	if (theApp.m_bStampaImmaginiUsaHFPerUO)
	{
		m_lIDHeader = theApp.m_lStampaImmaginiIDHeaderGlobal;
		m_lIDFooter = theApp.m_lStampaImmaginiIDFooterGlobal;
	}
	else
	{
		m_lIDHeader = theApp.m_lStampaImmaginiIDHeaderLocal;
		m_lIDFooter = theApp.m_lStampaImmaginiIDFooterLocal;
	}
}

void CStampaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ABILITA_HEADER, m_ctrlStatic1);
	DDX_Control(pDX, IDC_ABILITA_FOOTER, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_003, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_STAMPANTE, m_ctrlStaticStampante);
	DDX_Control(pDX, IDC_ABILITA_COMMENTI, m_ctrlButton06);
	DDX_Control(pDX, IDC_ABILITA_DATI_PAZ, m_ctrlButton07);
	DDX_Control(pDX, IDC_ABILITA_NUMERI, m_ctrlButton08);
	DDX_Control(pDX, IDC_STAMPA1, m_ctrlRadioStampa1);
	DDX_Control(pDX, IDC_STAMPA2, m_ctrlRadioStampa2);
	DDX_Control(pDX, IDC_STAMPA3, m_ctrlRadioStampa3);
	DDX_Control(pDX, IDC_STAMPA4, m_ctrlRadioStampa4);
	DDX_Control(pDX, IDC_STAMPA5, m_ctrlRadioStampa5);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);

	DDX_Control(pDX, IDC_SPIN, m_ctrlSpin);
	DDX_Radio(pDX, IDC_STAMPA1, m_nTypePrintImage);
	DDX_Check(pDX, IDC_ABILITA_COMMENTI, m_bPrintComment);
	DDX_Check(pDX, IDC_ABILITA_DATI_PAZ, m_bPrintPazData);
	DDX_Check(pDX, IDC_ABILITA_NUMERI, m_bStampaNumero);
	DDX_Text(pDX, IDC_DISTANZA, m_nDistImmagini);
	DDX_Control(pDX, IDC_COMBO_HEADER, m_ctrlComboHeader);
	DDX_Control(pDX, IDC_COMBO_FOOTER, m_ctrlComboFooter);
	DDX_Control(pDX, IDC_COMBO_STAMPANTE, m_ctrlComboStampante);
}

BEGIN_MESSAGE_MAP(CStampaDlg, CDialog)

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()

	ON_BN_CLICKED(IDC_STAMPA1, OnChangeStampa)
	ON_BN_CLICKED(IDC_STAMPA2, OnChangeStampa)
	ON_BN_CLICKED(IDC_STAMPA3, OnChangeStampa)
	ON_BN_CLICKED(IDC_STAMPA4, OnChangeStampa)
	ON_BN_CLICKED(IDC_STAMPA5, OnChangeStampa)
	ON_BN_CLICKED(IDC_ABILITA_FOOTER, OnChangeStampa)
	ON_BN_CLICKED(IDC_ABILITA_HEADER, OnChangeStampa)
	ON_BN_CLICKED(IDC_ABILITA_COMMENTI, OnChangeStampa)
	ON_BN_CLICKED(IDC_ABILITA_DATI_PAZ, OnChangeStampa)
	ON_BN_CLICKED(IDC_ABILITA_NUMERI, OnChangeStampa)
	ON_EN_CHANGE(IDC_DISTANZA, OnChangeDistanza)

END_MESSAGE_MAP()

BOOL CStampaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ctrlSpin.SetRange(0, LIMITE_SUPERIORE_DIST);

	CHeaderFooterSet setHF;
	int nIndex;

	// HEADER //

	setHF.SetOpenFilter("Tipo=1");
	nIndex = m_ctrlComboHeader.AddString("");
	m_ctrlComboHeader.SetItemData(nIndex, -1);
	if (setHF.OpenRecordset("CStampaDlg::OnInitDialog"))
	{
		while(!setHF.IsEOF())
		{
			nIndex = m_ctrlComboHeader.AddString(setHF.m_sDescrizione);
			m_ctrlComboHeader.SetItemData(nIndex, setHF.m_lID);

			setHF.MoveNext();
		}

		setHF.CloseRecordset("CStampaDlg::OnInitDialog");
	}
	m_ctrlComboHeader.SetCurSel(0);
	for(nIndex = 0; nIndex < m_ctrlComboHeader.GetCount(); nIndex++)
	{
		if (m_ctrlComboHeader.GetItemData(nIndex) == m_lIDHeader)
		{
			m_ctrlComboHeader.SetCurSel(nIndex);
			break;
		}
	}

	// FOOTER //

	setHF.SetOpenFilter("Tipo=2");
	nIndex = m_ctrlComboFooter.AddString("");
	m_ctrlComboFooter.SetItemData(nIndex, -1);
	if (setHF.OpenRecordset("CStampaDlg::OnInitDialog"))
	{
		while(!setHF.IsEOF())
		{
			nIndex = m_ctrlComboFooter.AddString(setHF.m_sDescrizione);
			m_ctrlComboFooter.SetItemData(nIndex, setHF.m_lID);

			setHF.MoveNext();
		}

		setHF.CloseRecordset("CStampaDlg::OnInitDialog");
	}
	m_ctrlComboFooter.SetCurSel(0);
	for(nIndex = 0; nIndex < m_ctrlComboFooter.GetCount(); nIndex++)
	{
		if (m_ctrlComboFooter.GetItemData(nIndex) == m_lIDFooter)
		{
			m_ctrlComboFooter.SetCurSel(nIndex);
			break;
		}
	}

	// STAMPANTI //

	m_ctrlComboStampante.ResetContent();
	m_ctrlComboStampante.InsertString(0, theApp.GetMessageString(IDS_IMMAGINI));
	m_ctrlComboStampante.SetItemData(0, (DWORD)Printer_Immagini);
	m_ctrlComboStampante.InsertString(1, "1");
	m_ctrlComboStampante.SetItemData(1, (DWORD)Printer_Report1);
	m_ctrlComboStampante.InsertString(2, "2");
	m_ctrlComboStampante.SetItemData(2, (DWORD)Printer_Report2);
	m_ctrlComboStampante.InsertString(3, "3");
	m_ctrlComboStampante.SetItemData(3, (DWORD)Printer_Report3);
	m_ctrlComboStampante.InsertString(4, "4");
	m_ctrlComboStampante.SetItemData(4, (DWORD)Printer_Report4);
	m_ctrlComboStampante.InsertString(5, "5");
	m_ctrlComboStampante.SetItemData(5, (DWORD)Printer_Report5);
	m_ctrlComboStampante.InsertString(6, "6");
	m_ctrlComboStampante.SetItemData(6, (DWORD)Printer_Report6);
	m_ctrlComboStampante.InsertString(7, "7");
	m_ctrlComboStampante.SetItemData(7, (DWORD)Printer_Report7);
	m_ctrlComboStampante.InsertString(8, "8");
	m_ctrlComboStampante.SetItemData(8, (DWORD)Printer_Report8);
	m_ctrlComboStampante.InsertString(9, "9");
	m_ctrlComboStampante.SetItemData(9, (DWORD)Printer_Report9);

	m_ctrlComboStampante.SetCurSel(0);
	for (nIndex = 0; nIndex < m_ctrlComboStampante.GetCount(); nIndex++)
	{
		if (m_ctrlComboStampante.GetItemData(nIndex) == m_lIDStampante)
		{
			m_ctrlComboStampante.SetCurSel(nIndex);
			break;
		}
	}

	// - //

	theApp.LocalizeDialog(this, CStampaDlg::IDD, "StampaDlg");
	return TRUE;
}

void CStampaDlg::OnChangeStampa() 
{
	UpdateData(TRUE);
}

void CStampaDlg::OnChangeDistanza() 
{
	if (m_ctrlSpin.GetSafeHwnd())
	{
		UpdateData(TRUE);

		if (m_nDistImmagini > LIMITE_SUPERIORE_DIST)
			m_nDistImmagini = LIMITE_SUPERIORE_DIST;

		UpdateData(FALSE);
	}
}

void CStampaDlg::OnOK() 
{
	UpdateData(TRUE);

	theApp.m_bStampaImmaginiStampaCommenti = m_bPrintComment;
	theApp.m_bStampaImmaginiStampaDatiPaziente = m_bPrintPazData;
	theApp.m_bStampaImmaginiStampaNumero = m_bStampaNumero;
	theApp.m_nStampaImmaginiDistanzaImmagini = m_nDistImmagini;
	theApp.m_nStampaImmaginiTipoDiStampa = m_nTypePrintImage;
	theApp.m_lIDStampanteImmagini = m_ctrlComboStampante.GetItemData(m_ctrlComboStampante.GetCurSel());

	// Sandro 26/10/2015 //
	if (theApp.m_bStampaImmaginiUsaHFPerUO)
	{
		theApp.m_lStampaImmaginiIDHeaderGlobal = m_ctrlComboHeader.GetItemData(m_ctrlComboHeader.GetCurSel());
		theApp.m_lStampaImmaginiIDFooterGlobal = m_ctrlComboFooter.GetItemData(m_ctrlComboFooter.GetCurSel());
	}
	else
	{
		theApp.m_lStampaImmaginiIDHeaderLocal = m_ctrlComboHeader.GetItemData(m_ctrlComboHeader.GetCurSel());
		theApp.m_lStampaImmaginiIDFooterLocal = m_ctrlComboFooter.GetItemData(m_ctrlComboFooter.GetCurSel());
	}

	// Sandro 18/06/2015 //

	m_pEsamiView->GetDocument()->SetBoolValue("Stampa immagini - Stampa commenti", theApp.m_bStampaImmaginiStampaCommenti);
	m_pEsamiView->GetDocument()->SetBoolValue("Stampa immagini - Stampa dati paziente", theApp.m_bStampaImmaginiStampaDatiPaziente);
	m_pEsamiView->GetDocument()->SetBoolValue("Stampa immagini - Stampa numero", theApp.m_bStampaImmaginiStampaNumero);

	m_pEsamiView->GetDocument()->SetIntValue("Stampa immagini - Distanza immagini", theApp.m_nStampaImmaginiDistanzaImmagini);
	m_pEsamiView->GetDocument()->SetIntValue("Stampa immagini - Tipo di stampa", theApp.m_nStampaImmaginiTipoDiStampa);

	m_pEsamiView->GetDocument()->SetLongValue("Numero stampante immagini", theApp.m_lIDStampanteImmagini);
	m_pEsamiView->GetDocument()->SetLongValue("Stampa immagini - ID Header", theApp.m_lStampaImmaginiIDHeaderGlobal);
	m_pEsamiView->GetDocument()->SetLongValue("Stampa immagini - ID Footer", theApp.m_lStampaImmaginiIDFooterGlobal);

	//

	CDialog::OnOK();
}