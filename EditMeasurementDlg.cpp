// EditMeasurementDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Endox.h"
#include "EditMeasurementDlg.h"
#include "afxdialogex.h"
#include "MeasurementsSet.h"
#include "MeasurementsAliasMappingSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEditMeasurementDlg, CDialog)

CEditMeasurementDlg::CEditMeasurementDlg(CWnd* pParent, long lID, BOOL bAddNew)
	: CDialog(CEditMeasurementDlg::IDD, pParent)
{
	m_lID = lID;
	m_bAddNew = bAddNew;
}

CEditMeasurementDlg::~CEditMeasurementDlg()
{
}

void CEditMeasurementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_ALIAS, m_sAlias);
	DDX_Text(pDX, IDC_EDIT_NUMERIC, m_sNumeric);
	DDX_Text(pDX, IDC_EDIT_CODE, m_sCode);
	DDX_Control(pDX, IDC_COMBO_NOMEPARAMETRO, m_ctrlComboNomeParametro);

	GetDlgItem(IDC_EDIT_NUMERIC)->SetFocus();
}


BEGIN_MESSAGE_MAP(CEditMeasurementDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CEditMeasurementDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_ALIAS, &CEditMeasurementDlg::OnEnChangeEditValue)
	ON_EN_CHANGE(IDC_EDIT_NUMERIC, &CEditMeasurementDlg::OnEnChangeEditValue)
	ON_EN_CHANGE(IDC_EDIT_CODE, &CEditMeasurementDlg::OnEnChangeEditValue)
	ON_CBN_SELCHANGE(IDC_COMBO_NOMEPARAMETRO, &CEditMeasurementDlg::OnCbnSelchangeComboNomeparametro)
END_MESSAGE_MAP()


BOOL CEditMeasurementDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CEditMeasurementDlg::IDD, "EditMeasurementDlg");

	if (m_bAddNew)
	{
		RiempiCombo();
		GetDlgItem(IDC_COMBO_NOMEPARAMETRO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_ALIAS)->ShowWindow(SW_HIDE);
	}
	else
	{
	CString sFilter;
	sFilter.Format("ID=%li", m_lID);
	CMeasurementsSet set;
	set.SetOpenFilter(sFilter);
	if (set.OpenRecordset("CEditMeasurementDlg::OnInitDialog"))
	{
		if (!set.IsEOF())
		{
			SetDlgItemText(IDC_EDIT_ALIAS, set.m_sAlias);
			SetDlgItemText(IDC_EDIT_NUMERIC, set.m_sNumericValue);
			SetDlgItemText(IDC_EDIT_CODE, set.m_sCodeValue);
		}
		set.CloseRecordset("CEditMeasurementDlg::OnInitDialog");
	}
	}
	
	GetDlgItem(IDC_EDIT_NUMERIC)->SetFocus();

	return bReturn;
}

void CEditMeasurementDlg::RiempiCombo()
{
	CString sFilter;	
	sFilter.Format("ALIAS NOT IN (SELECT ALIAS FROM MEASUREMENTS WHERE ELIMINATO = 0 AND IDESAME = %li)", m_lID);
	
	CMeasurementsAliasMappingSet set;
	set.SetOpenFilter(sFilter);

	m_ctrlComboNomeParametro.Clear();	

	if (set.OpenRecordset("CEditMeasurementDlg::RiempiCombo"))
	{
		while (!set.IsEOF())
		{
			if (m_ctrlComboNomeParametro.FindString(0, set.m_sNomeParametro) >= 0)
			{
				set.MoveNext();
				continue;
			}
			else
			{
				int nCurr = m_ctrlComboNomeParametro.AddString(set.m_sNomeParametro);
				m_ctrlComboNomeParametro.SetItemData(nCurr, set.m_lID);
				set.MoveNext();
			}			
		}
		set.CloseRecordset("CEditMeasurementDlg::RiempiCombo");
	}

	if (m_ctrlComboNomeParametro.GetCount() == 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MEASUREMENTS_ZEROPARAMETERS));
		OnCancel();
	}
}

void CEditMeasurementDlg::OnBnClickedOk()
{
	CString sFilter;
	CMeasurementsSet set;
	
	if (m_bAddNew)
	{
		set.AddRow(m_lID, m_sAlias, m_sNumeric, m_sCode, theApp.m_sUtenteLoggato);
	}
	else
	{
		sFilter.Format("ID=%li", m_lID);

		set.SetOpenFilter(sFilter);
		if (set.OpenRecordset("CEditMeasurementDlg::OnBnClickedOk"))
		{
			if (set.EditRecordset("CEditMeasurementDlg::OnBnClickedOk"))
			{
				set.m_sNumericValue = m_sNumeric;
				set.m_sCodeValue = m_sCode;

				set.UpdateRecordset("CEditMeasurementDlg::OnBnClickedOk");
			}
			set.CloseRecordset("CEditMeasurementDlg::OnBnClickedOk");
		}
	}

	CDialog::OnOK();
}

void CEditMeasurementDlg::OnEnChangeEditValue()
{	
	CString sTemp1;
	GetDlgItemText(IDC_EDIT_ALIAS, sTemp1);
	sTemp1.Trim();
	m_sAlias = sTemp1;

	CString sTemp2;
	GetDlgItemText(IDC_EDIT_NUMERIC, sTemp2);
	sTemp2.Trim();
	m_sNumeric = sTemp2;

	CString sTemp3;
	GetDlgItemText(IDC_EDIT_CODE, sTemp3);
	sTemp3.Trim();
	m_sCode = sTemp3;
}


void CEditMeasurementDlg::OnCbnSelchangeComboNomeparametro()
{
	int nTemp = m_ctrlComboNomeParametro.GetCurSel();
	if (nTemp >= 0)
	{		
		long lID = m_ctrlComboNomeParametro.GetItemData(nTemp);
		CString sFilter;
		sFilter.Format("ID=%li", lID);
		
		CMeasurementsAliasMappingSet set;
		set.SetOpenFilter(sFilter);		

		if (set.OpenRecordset("CEditMeasurementDlg::RiempiCombo"))
		{
			if(!set.IsEOF())
			{
				SetDlgItemText(IDC_EDIT_ALIAS, set.m_sAlias);
			}
			set.CloseRecordset("CEditMeasurementDlg::RiempiCombo");
		}		
	}
}
