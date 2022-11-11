#include "stdafx.h"
#include "Endox.h"
#include "GruppiPrelieviOldModPrestDlg.h"

#include "Common.h"
#include "GruppiPrelieviOldItemSet.h"
#include "IstologiaProcedureSet.h"
#include "IstologiaTipiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiPrelieviOldModPrestDlg, CDialog)

CGruppiPrelieviOldModPrestDlg::CGruppiPrelieviOldModPrestDlg(CWnd* pParent, long lIDGruppoOld, long lRecord)
	: CDialog(CGruppiPrelieviOldModPrestDlg::IDD, pParent)
{
	m_lIDGruppoOld = lIDGruppoOld;
	m_lRecord = lRecord;

	m_setItem.SetEmpty();
}

CGruppiPrelieviOldModPrestDlg::~CGruppiPrelieviOldModPrestDlg()
{
}

BEGIN_MESSAGE_MAP(CGruppiPrelieviOldModPrestDlg, CDialog)
END_MESSAGE_MAP()

void CGruppiPrelieviOldModPrestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TIPO, m_ctrlTipo);
	DDX_Control(pDX, IDC_ORGANO, m_ctrlOrgano);
	DDX_Control(pDX, IDC_SEDE, m_ctrlSede);
	DDX_Control(pDX, IDC_PROVETTA, m_ctrlProvetta);
	DDX_Control(pDX, IDC_PROCEDURA, m_ctrlProcedura);
	DDX_Control(pDX, IDC_DIAGNOSI, m_ctrlDiagnosi);

	// Sandro 13/01/2014 // RAS 20130203 //
	
	if (pDX->m_bSaveAndValidate)
	{
		m_setItem.m_lTipo = 0;

		int nCurSel = m_ctrlTipo.GetCurSel();
		if (nCurSel > 0)
			m_setItem.m_lTipo = m_ctrlTipo.GetItemData(nCurSel);

		//

		m_setItem.m_lProcedura = 0;

		nCurSel = m_ctrlProcedura.GetCurSel();
		if (nCurSel > 0)
			m_setItem.m_lProcedura = m_ctrlProcedura.GetItemData(nCurSel);
	}
	else
	{
		int nCurSel = 0;

		for(int i = 1; i < m_ctrlTipo.GetCount(); i++)
		{
			if (m_ctrlTipo.GetItemData(i) == m_setItem.m_lTipo)
			{
				nCurSel = i;
				break;
			}
		}

		m_ctrlTipo.SetCurSel(nCurSel);

		//

		nCurSel = 0;

		for (int i = 1; i < m_ctrlProcedura.GetCount(); i++)
		{
			if (m_ctrlProcedura.GetItemData(i) == m_setItem.m_lProcedura)
			{
				nCurSel = i;
				break;
			}
		}

		m_ctrlProcedura.SetCurSel(nCurSel);
	}
	
	//

	DDX_Organo(pDX, IDC_ORGANO, m_setItem.m_lOrgano);
	DDX_Text(pDX, IDC_SEDE, m_setItem.m_sSede);
	DDX_Text(pDX, IDC_PROVETTA, m_setItem.m_sProvette);
	DDX_Text(pDX, IDC_DIAGNOSI, m_setItem.m_sDiagnosi);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_06, m_ctrlStatic06);
}

BOOL CGruppiPrelieviOldModPrestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	m_ctrlOrgano.SetParam(NULL, GetDlgItem(IDC_ORGANO), GetDlgItem(IDC_SEDE), GetDlgItem(IDC_DIAGNOSI));
	m_ctrlSede.SetParam(NULL, GetDlgItem(IDC_ORGANO), GetDlgItem(IDC_SEDE), GetDlgItem(IDC_DIAGNOSI));
	m_ctrlDiagnosi.SetParam(NULL, GetDlgItem(IDC_ORGANO), GetDlgItem(IDC_SEDE), GetDlgItem(IDC_DIAGNOSI));

	// Sandro 13/01/2014 // RAS 20130203 //

	m_ctrlTipo.ResetContent();
	m_ctrlTipo.InsertString(0, "");
	m_ctrlTipo.SetItemData(0, 0);

	CIstologiaTipiSet setIstT;
	setIstT.SetSortRecord("Descrizione");
	if (setIstT.OpenRecordset("CGruppiPrelieviOldModPrestDlg::OnInitDialog"))
	{
		int nIndex = 1;

		while (!setIstT.IsEOF())
		{
			m_ctrlTipo.InsertString(nIndex, setIstT.m_sDescrizione);
			m_ctrlTipo.SetItemData(nIndex, setIstT.m_lID);

			nIndex++;
			setIstT.MoveNext();
		}

		setIstT.CloseRecordset("CGruppiPrelieviOldModPrestDlg::OnInitDialog");
	}

	m_ctrlTipo.SetCurSel(0);

	// Sandro 27/03/2015 //

	m_ctrlProcedura.ResetContent();
	m_ctrlProcedura.InsertString(0, "");
	m_ctrlProcedura.SetItemData(0, 0);

	CIstologiaProcedureSet setIP;
	setIP.SetSortRecord("Descrizione");
	if (setIP.OpenRecordset("CGruppiPrelieviOldModPrestDlg::OnInitDialog"))
	{
		int nIndex = 1;

		while (!setIP.IsEOF())
		{
			m_ctrlProcedura.InsertString(nIndex, setIP.m_sDescrizione);
			m_ctrlProcedura.SetItemData(nIndex, setIP.m_lID);

			nIndex++;
			setIP.MoveNext();
		}

		setIP.CloseRecordset("CGruppiPrelieviOldModPrestDlg::OnInitDialog");
	}

	m_ctrlProcedura.SetCurSel(0);

	//

	CString strFilter;
	strFilter.Format("ID=%li", m_lRecord);

	m_setItem.SetOpenFilter(strFilter);
	if (m_setItem.OpenRecordset("CGruppiPrelieviOldModPrestDlg::OnInitDialog"))
	{
		if (m_setItem.IsEOF())
			m_setItem.SetEmpty();
	}
	UpdateData(FALSE);

	//

	theApp.LocalizeDialog(this, CGruppiPrelieviOldModPrestDlg::IDD, "GruppiPrelieviOldModPrestDlg");

	//

	if (m_lRecord <= 0)
	{
		// NEW //
		SetWindowText(theApp.GetMessageString(IDS_NUOVO_PRELIEVO));
	}
	else
	{
		// EDIT //
		SetWindowText(theApp.GetMessageString(IDS_MODIFICA_PRELIEVO));
	}

	return TRUE;
}

void CGruppiPrelieviOldModPrestDlg::OnOK()
{
	UpdateData(TRUE);

	if (m_setItem.m_lTipo < 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPATOLD_ERROR1));
		return;
	}

	if (m_setItem.m_lOrgano <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPATOLD_ERROR2));
		return;
	}

	if (m_setItem.m_sSede.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPATOLD_ERROR3));
		return;
	}

	if (m_setItem.IsEOF())
	{
		// NEW //

		if (m_setItem.AddNewRecordset("CGruppiPrelieviOldModPrestDlg::OnOK"))
		{
			m_setItem.m_lIDGruppoOld = m_lIDGruppoOld;
			UpdateData(TRUE);
			m_setItem.UpdateRecordset("CGruppiPrelieviOldModPrestDlg::OnOK");
		}
	}
	else
	{
		// EDIT //

		if (m_setItem.EditRecordset("CGruppiPrelieviOldModPrestDlg::OnOK"))
		{
			UpdateData(TRUE);
			m_setItem.UpdateRecordset("CGruppiPrelieviOldModPrestDlg::OnOK");
		}
	}
	m_setItem.CloseRecordset("CGruppiPrelieviOldModPrestDlg::OnOK");

	CDialog::OnOK();
}