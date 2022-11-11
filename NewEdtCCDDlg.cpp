#include "stdafx.h"
#include "Endox.h"
#include "NewEdtCCDDlg.h"

#include "CodiciClassificazioneDiagnosticaSet.h"
#include "EsamiCodiciClassDiagnostSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CNewEdtCCDDlg, CDialog)

CNewEdtCCDDlg::CNewEdtCCDDlg(CWnd* pParent, UINT idTitle, long lIDEsame, long lIDCCD)
	: CDialog(CNewEdtCCDDlg::IDD, pParent)
{
	m_sTitle = theApp.GetMessageString(idTitle);
	m_lIDEsame = lIDEsame;
	m_lIDCCD = lIDCCD;

	m_lIDCurSelForSearch = 0;
}

CNewEdtCCDDlg::~CNewEdtCCDDlg()
{
}

void CNewEdtCCDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_COMBO, m_ctrlCCD);
}

BEGIN_MESSAGE_MAP(CNewEdtCCDDlg, CDialog)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_CBN_SELCHANGE(IDC_COMBO, OnCbnSelchangeCombo)

END_MESSAGE_MAP()

BOOL CNewEdtCCDDlg::OnInitDialog()
{   
	BOOL bReturn = CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CNewEdtCCDDlg::IDD, "NewEdtCCDDlg");

	SetWindowText(m_sTitle);

	RiempiCombo();

	// Sandro 03/06/2013 // Attivo il tasto "Conferma" solo se c'è qualcosa di scritto //
	m_ctrlButtonOK.EnableWindow(m_ctrlCCD.GetCurSel() > 0);

	//
	return bReturn;
}

void CNewEdtCCDDlg::OnBnClickedOk()
{
	//
	m_lIDCurSelForSearch = m_ctrlCCD.GetItemData(m_ctrlCCD.GetCurSel());

	// se non sono in ricerca salvo direttamente su DB //
	if (m_lIDEsame > 0)
	{
		// se sono in "edit" cancello il vecchio prima di aggiungere il nuovo //
		if (m_lIDCCD > 0)
			CEsamiCodiciClassDiagnostSet().DelRecord(m_lIDEsame, m_lIDCCD);

		//
		CEsamiCodiciClassDiagnostSet().AddRecord(m_lIDEsame, m_lIDCurSelForSearch);
	}

	//
	OnOK();
}

void CNewEdtCCDDlg::RiempiCombo()
{
	int nItemToSel = 0;

	m_ctrlCCD.ResetContent();
	m_ctrlCCD.InsertString(0, "");
	m_ctrlCCD.SetItemData(0, 0);

	CCodiciClassificazioneDiagnostSet setTemp;
	setTemp.SetSortRecord("DESCRIZIONE");
	if (setTemp.OpenRecordset("CNewEdtCCDDlg::RiempiCombo"))
	{
		int nIndex = 1;
		while (!setTemp.IsEOF())
		{
			m_ctrlCCD.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlCCD.SetItemData(nIndex, setTemp.m_lID);

			if ((m_lIDCCD > 0) && (setTemp.m_lID == m_lIDCCD))
				nItemToSel = nIndex;

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CNewEdtCCDDlg::RiempiCombo");
	}

	m_ctrlCCD.SetCurSel(nItemToSel);
}

void CNewEdtCCDDlg::OnCbnSelchangeCombo()
{
	// Sandro 03/06/2013 // Attivo il tasto "Conferma" solo se c'è qualcosa di scritto //
	m_ctrlButtonOK.EnableWindow(m_ctrlCCD.GetCurSel() > 0);
}

long CNewEdtCCDDlg::GetIDCurSelForSearch()
{
	return m_lIDCurSelForSearch;
}