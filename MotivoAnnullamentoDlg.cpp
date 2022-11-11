#include "stdafx.h"
#include "Endox.h"
#include "MotivoAnnullamentoDlg.h"

#include "MotivoAnnullamentoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMotivoAnnullamentoDlg, CDialog)

CMotivoAnnullamentoDlg::CMotivoAnnullamentoDlg(CWnd* pParent)
	: CDialog(CMotivoAnnullamentoDlg::IDD, pParent)
{
	m_lIDMotivo = 0;
}

CMotivoAnnullamentoDlg::~CMotivoAnnullamentoDlg()
{
}

void CMotivoAnnullamentoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_COMBO, m_ctrlComboMotivo);
}

BEGIN_MESSAGE_MAP(CMotivoAnnullamentoDlg, CDialog)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_CBN_SELCHANGE(IDC_COMBO, OnCbnSelchangeCombo)

END_MESSAGE_MAP()

BOOL CMotivoAnnullamentoDlg::OnInitDialog()
{   
	CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CMotivoAnnullamentoDlg::IDD, "MotivoAnnullamentoDlg");

	SetWindowText(theApp.GetMessageString(IDS_MOTIVO_ANNULLAMENTO));

	RiempiCombo();

	return TRUE;
}

void CMotivoAnnullamentoDlg::OnBnClickedOk()
{
	m_lIDMotivo = 0;

	int nCurSel = m_ctrlComboMotivo.GetCurSel();
	if (nCurSel > 0)
		m_lIDMotivo = m_ctrlComboMotivo.GetItemData(nCurSel);

	if (m_lIDMotivo > 0)
		OnOK();
}

void CMotivoAnnullamentoDlg::RiempiCombo()
{
	m_ctrlComboMotivo.ResetContent();
	m_ctrlComboMotivo.InsertString(0, "");
	m_ctrlComboMotivo.SetItemData(0, 0);

	CMotivoAnnullamentoSet setTemp;
	setTemp.SetSortRecord("DESCRIZIONE");
	if (setTemp.OpenRecordset("CMotivoAnnullamentoDlg::RiempiCombo"))
	{
		int nIndex = 1;
		while (!setTemp.IsEOF())
		{
			m_ctrlComboMotivo.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlComboMotivo.SetItemData(nIndex, setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMotivoAnnullamentoDlg::RiempiCombo");
	}

	m_ctrlComboMotivo.SetCurSel(0);
}

void CMotivoAnnullamentoDlg::OnCbnSelchangeCombo()
{
	// Sandro 03/06/2013 // Attivo il tasto "Conferma" solo se c'è qualcosa di scritto //
	m_ctrlButtonOK.EnableWindow(m_ctrlComboMotivo.GetCurSel() > 0);
}

long CMotivoAnnullamentoDlg::GetIDMotivo()
{
	return m_lIDMotivo;
}