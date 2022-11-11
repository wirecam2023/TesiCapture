#include "stdafx.h"
#include "Endox.h"
#include "EditCodiceDescrizioneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEditCodiceDescrizioneDlg, CDialog)

CEditCodiceDescrizioneDlg::CEditCodiceDescrizioneDlg(CWnd* pParent, const CString &strTitle, const CString &sCodice, const CString &sDescrizione)
	: CDialog(CEditCodiceDescrizioneDlg::IDD, pParent)
{
	m_sTitle = strTitle;
	m_sCodice = sCodice;
	m_sDescrizione = sDescrizione;
}

CEditCodiceDescrizioneDlg::CEditCodiceDescrizioneDlg(CWnd* pParent, UINT idTitle, const CString &sCodice, const CString &sDescrizione)
	: CDialog(CEditCodiceDescrizioneDlg::IDD, pParent)
{
	m_sTitle = theApp.GetMessageString(idTitle);
	m_sCodice = sCodice;
	m_sDescrizione = sDescrizione;
}

CEditCodiceDescrizioneDlg::~CEditCodiceDescrizioneDlg()
{
}

void CEditCodiceDescrizioneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
}

BEGIN_MESSAGE_MAP(CEditCodiceDescrizioneDlg, CDialog)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_CODICE, OnEnChangeEditValue)
	ON_EN_CHANGE(IDC_EDIT_DESCRIZIONE, OnEnChangeEditValue)

END_MESSAGE_MAP()

BOOL CEditCodiceDescrizioneDlg::OnInitDialog()
{   
	BOOL bReturn = CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CEditCodiceDescrizioneDlg::IDD, "EditCodiceDescrizioneDlg");

	SetWindowText(m_sTitle);
	SetDlgItemText(IDC_EDIT_CODICE, m_sCodice);
	SetDlgItemText(IDC_EDIT_DESCRIZIONE, m_sDescrizione);

	// Sandro 03/06/2013 // Attivo il tasto "Conferma" solo se c'è qualcosa di scritto //
	m_ctrlButtonOK.EnableWindow(!m_sCodice.IsEmpty() && !m_sDescrizione.IsEmpty());

	//
	return bReturn;
}

void CEditCodiceDescrizioneDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT_CODICE, m_sCodice);
	GetDlgItemText(IDC_EDIT_DESCRIZIONE, m_sDescrizione);

	OnOK();
}

CString CEditCodiceDescrizioneDlg::GetCodice()
{
	return m_sCodice;
}

CString CEditCodiceDescrizioneDlg::GetDescrizione()
{
	return m_sDescrizione;
}

void CEditCodiceDescrizioneDlg::OnEnChangeEditValue()
{
	// Sandro 03/06/2013 // Attivo il tasto "Conferma" solo se c'è qualcosa di scritto //

	CString sCodTemp;
	GetDlgItemText(IDC_EDIT_CODICE, sCodTemp);
	sCodTemp.Trim();

	CString sDescTemp;
	GetDlgItemText(IDC_EDIT_DESCRIZIONE, sDescTemp);
	sDescTemp.Trim();

	m_ctrlButtonOK.EnableWindow(!sCodTemp.IsEmpty() && !sDescTemp.IsEmpty());
}
