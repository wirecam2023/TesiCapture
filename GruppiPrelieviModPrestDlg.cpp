#include "stdafx.h"
#include "Endox.h"
#include "GruppiPrelieviModPrestDlg.h"

#include "AnatomiaPatologicaIntervSet.h"
#include "GruppiPrelieviItemSet.h"
#include "GruppiPrelieviItemView.h"
#include "SediEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiPrelieviModPrestDlg, CDialog)

CGruppiPrelieviModPrestDlg::CGruppiPrelieviModPrestDlg(CWnd* pParent, long lIDGruppo, long lRecord)
	: CDialog(CGruppiPrelieviModPrestDlg::IDD, pParent)
{
	m_lIDGruppo = lIDGruppo;
	m_lRecord = lRecord;
}

CGruppiPrelieviModPrestDlg::~CGruppiPrelieviModPrestDlg()
{
}

BEGIN_MESSAGE_MAP(CGruppiPrelieviModPrestDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_TIPO, OnCbnSelchangeComboTipo)
END_MESSAGE_MAP()

void CGruppiPrelieviModPrestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_TIPO, m_ctrlComboTipo);
	DDX_Control(pDX, IDC_COMBO_INTERVENTO, m_ctrlComboIntervento);
	DDX_Control(pDX, IDC_EDIT_PRELIEVI, m_ctrlEditPrelievi);
	DDX_Control(pDX, IDC_EDIT_DESCRIZIONE, m_ctrlEditDescrizione);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
}

BOOL CGruppiPrelieviModPrestDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	//

	theApp.LocalizeDialog(this, CGruppiPrelieviModPrestDlg::IDD, "GruppiPrelieviModPrestDlg");

	//

	// EDT CAMPIONE //

	// CMB TIPO //
	m_ctrlComboTipo.AddString(theApp.GetMessageString(IDS_CITOLOGICO));
	m_ctrlComboTipo.AddString(theApp.GetMessageString(IDS_ISTOLOGICO));

	// CMB INTERVENTO //

	// EDT PRELIEVI //

	// EDT DESCRIZIONE //
	// Sandro 28/09/2010 // modificato SOLO per Trento perchè Petardo a Monselice ha deciso così //
	m_ctrlEditDescrizione.SetLimitText(255);

	if (m_lRecord <= 0)
	{
		// NEW //
		SetWindowText(theApp.GetMessageString(IDS_NUOVO_PRELIEVO));

		// CMB TIPO //
		m_ctrlComboTipo.SetCurSel(1);
		OnCbnSelchangeComboTipo();

		// CMB INTERVENTO //
		m_ctrlComboIntervento.SetFocus();
		m_ctrlComboIntervento.ShowDropDown(TRUE);
	}
	else
	{
		// EDIT //
		SetWindowText(theApp.GetMessageString(IDS_MODIFICA_PRELIEVO));

		CString strFilter;
		strFilter.Format("ID=%li", m_lRecord);

		CGruppiPrelieviItemView setTemp;
		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CGruppiPrelieviModPrestDlg::OnInitDialog"))
		{
			if (!setTemp.IsEOF())
			{
				int nIndexFound;
				CString strTemp;

				// CMB TIPO //
				nIndexFound = m_ctrlComboTipo.FindString(-1, setTemp.m_sTipo);
				if (nIndexFound >= 0)
				{
					m_ctrlComboTipo.SetCurSel(nIndexFound);
					OnCbnSelchangeComboTipo();
				}

				// CMB INTERVENTO //
				nIndexFound = m_ctrlComboIntervento.FindStringExact(-1, setTemp.m_sIntervento);
				if (nIndexFound >= 0)
					m_ctrlComboIntervento.SetCurSel(nIndexFound);

				// EDT PRELIEVI //
				if (!setTemp.IsFieldNull(&setTemp.m_lPrelievi) && setTemp.m_lPrelievi > 0)
				{
					strTemp.Format("%li", setTemp.m_lPrelievi);
					m_ctrlEditPrelievi.SetWindowText(strTemp);
				}

				// EDT DESCRIZIONE //
				m_ctrlEditDescrizione.SetWindowText(setTemp.m_sDescrizione);

			}
			setTemp.CloseRecordset("CGruppiPrelieviModPrestDlg::OnInitDialog");
		}
	}

	return bReturn;
}

void CGruppiPrelieviModPrestDlg::OnOK()
{
	// EDT CAMPIONE //

	// CMB TIPO //
	CString sTipo = "";
	m_ctrlComboTipo.GetWindowText(sTipo);
	if (sTipo.GetLength() <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPAT_ERROR1));
		return;
	}
	sTipo = sTipo.Left(1);

	// CMB INTERVENTO //
	long lIDIntervento = 0;
	int nIndexFound = m_ctrlComboIntervento.GetCurSel();
	if (nIndexFound >= 0)
	{
		lIDIntervento = (long)m_ctrlComboIntervento.GetItemData(nIndexFound);
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPAT_ERROR2));
		return;
	}

	// EDT PRELIEVI //
	CString sPrelieviTemp;
	m_ctrlEditPrelievi.GetWindowText(sPrelieviTemp);
	long lPrelievi = atol(sPrelieviTemp);
	if (lPrelievi <= 0)
	{
		// Sandro 01/03/2010 - RAS 20100009 //
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPAT_ERROR4));
		return;
	}

	// EDT DESCRIZIONE //
	CString sDescrizione;
	m_ctrlEditDescrizione.GetWindowText(sDescrizione);

	if (m_lRecord <= 0)
	{
		// NEW //

		CGruppiPrelieviItemSet setAP;
		if (setAP.OpenRecordset("CGruppiPrelieviModPrestDlg::OnOK"))
		{
			if (setAP.AddNewRecordset("CGruppiPrelieviModPrestDlg::OnOK"))
			{
				setAP.m_lIDGruppo = m_lIDGruppo;
				setAP.m_lIDIntervento = lIDIntervento;
				setAP.m_lPrelievi = lPrelievi;
				setAP.m_sDescrizione = sDescrizione;

				setAP.UpdateRecordset("CGruppiPrelieviModPrestDlg::OnOK");
			}
			setAP.CloseRecordset("CGruppiPrelieviModPrestDlg::OnOK");
		}
	}
	else
	{
		// EDIT //

		CString strFilter;
		strFilter.Format("ID=%li", m_lRecord);

		CGruppiPrelieviItemSet setAP;
		setAP.SetOpenFilter(strFilter);
		if (setAP.OpenRecordset("CGruppiPrelieviModPrestDlg::OnOK"))
		{
			if (!setAP.IsEOF())
			{
				if (setAP.EditRecordset("CGruppiPrelieviModPrestDlg::OnOK"))
				{
					setAP.m_lIDIntervento = lIDIntervento;
					setAP.m_lPrelievi = lPrelievi;
					setAP.m_sDescrizione = sDescrizione;

					setAP.UpdateRecordset("CGruppiPrelieviModPrestDlg::OnOK");
				}
			}
			setAP.CloseRecordset("CGruppiPrelieviModPrestDlg::OnOK");
		}
	}

	CDialog::OnOK();
}

void CGruppiPrelieviModPrestDlg::OnCbnSelchangeComboTipo()
{
	CString strComboTipo;
	m_ctrlComboTipo.GetWindowText(strComboTipo);

	m_ctrlComboIntervento.ResetContent();

	if (strComboTipo.GetLength() > 0)
	{
		strComboTipo = strComboTipo.Left(1);

		CString strFilter;
		strFilter.Format("Tipo='%s' AND APSede='%s'", strComboTipo, CSediEsameSet().GetAPSede(theApp.m_lIDSedeEsameDefault));

		CAnatomiaPatologicaIntervSet setTemp;
		setTemp.SetOpenFilter(strFilter);
		setTemp.SetSortRecord("ID");
		if (setTemp.OpenRecordset("CGruppiPrelieviModPrestDlg::OnCbnSelchangeComboTipo"))
		{
			int nTemp;
			while(!setTemp.IsEOF())
			{
				nTemp = m_ctrlComboIntervento.AddString(setTemp.m_sDescrizione);
				m_ctrlComboIntervento.SetItemData(nTemp, (DWORD)setTemp.m_lID);

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CGruppiPrelieviModPrestDlg::OnCbnSelchangeComboTipo");
		}
	}
}