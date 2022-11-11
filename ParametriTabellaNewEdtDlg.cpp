#include "stdafx.h"
#include "Endox.h"
#include "ParametriTabellaNewEdtDlg.h"

#include <cctype>

#include "TabellaParametriSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CParametriTabellaNewEdtDlg, CDialog)

CParametriTabellaNewEdtDlg::CParametriTabellaNewEdtDlg(CWnd* pParent, long lIDParametro, long lIDStruttura, long lOrdine)
	: CDialog(CParametriTabellaNewEdtDlg::IDD, pParent)
{
	ASSERT((lIDParametro > 0) || (lOrdine > 0));

	m_lIDParametro = lIDParametro;
	m_lIDStruttura = lIDStruttura;
	m_lOrdine = lOrdine;

	m_lLastAdd = 0;
}

CParametriTabellaNewEdtDlg::~CParametriTabellaNewEdtDlg()
{
}

BEGIN_MESSAGE_MAP(CParametriTabellaNewEdtDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)

END_MESSAGE_MAP()

void CParametriTabellaNewEdtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_PARAMETRO, m_ctrlEditParametro);
	DDX_Control(pDX, IDC_EDIT_FORMULA, m_ctrlEditFormula);
	DDX_Control(pDX, IDC_EDIT_DECIMALI, m_ctrlEditDecimali);
	DDX_Control(pDX, IDC_EDIT_UNITADIMISURA, m_ctrlEditUnitaDiMisura);
	DDX_Control(pDX, IDC_EDIT_M, m_ctrlEditRifM);
	DDX_Control(pDX, IDC_EDIT_M_MIN, m_ctrlEditRifMmin);
	DDX_Control(pDX, IDC_EDIT_M_MAX, m_ctrlEditRifMmax);
	DDX_Control(pDX, IDC_EDIT_F, m_ctrlEditRifF);
	DDX_Control(pDX, IDC_EDIT_F_MIN, m_ctrlEditRifFmin);
	DDX_Control(pDX, IDC_EDIT_F_MAX, m_ctrlEditRifFmax);
	DDX_Control(pDX, IDC_EDIT_P00, m_ctrlEditRifPed00);
	DDX_Control(pDX, IDC_EDIT_P00_MIN, m_ctrlEditRifPed00min);
	DDX_Control(pDX, IDC_EDIT_P00_MAX, m_ctrlEditRifPed00max);
	DDX_Control(pDX, IDC_EDIT_P01, m_ctrlEditRifPed01);
	DDX_Control(pDX, IDC_EDIT_P01_MIN, m_ctrlEditRifPed01min);
	DDX_Control(pDX, IDC_EDIT_P01_MAX, m_ctrlEditRifPed01max);
	DDX_Control(pDX, IDC_EDIT_P02, m_ctrlEditRifPed02);
	DDX_Control(pDX, IDC_EDIT_P02_MIN, m_ctrlEditRifPed02min);
	DDX_Control(pDX, IDC_EDIT_P02_MAX, m_ctrlEditRifPed02max);
	DDX_Control(pDX, IDC_EDIT_P03, m_ctrlEditRifPed03);
	DDX_Control(pDX, IDC_EDIT_P03_MIN, m_ctrlEditRifPed03min);
	DDX_Control(pDX, IDC_EDIT_P03_MAX, m_ctrlEditRifPed03max);
	DDX_Control(pDX, IDC_EDIT_P04, m_ctrlEditRifPed04);
	DDX_Control(pDX, IDC_EDIT_P04_MIN, m_ctrlEditRifPed04min);
	DDX_Control(pDX, IDC_EDIT_P04_MAX, m_ctrlEditRifPed04max);
	DDX_Control(pDX, IDC_EDIT_P05, m_ctrlEditRifPed05);
	DDX_Control(pDX, IDC_EDIT_P05_MIN, m_ctrlEditRifPed05min);
	DDX_Control(pDX, IDC_EDIT_P05_MAX, m_ctrlEditRifPed05max);
	DDX_Control(pDX, IDC_EDIT_P06, m_ctrlEditRifPed06);
	DDX_Control(pDX, IDC_EDIT_P06_MIN, m_ctrlEditRifPed06min);
	DDX_Control(pDX, IDC_EDIT_P06_MAX, m_ctrlEditRifPed06max);

	DDX_Control(pDX, IDC_SPIN_DECIMALI, m_ctrlSpinDecimali);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_06, m_ctrlStatic06);
	DDX_Control(pDX, IDC_STATIC_07, m_ctrlStatic07);
	DDX_Control(pDX, IDC_STATIC_08, m_ctrlStatic08);
	DDX_Control(pDX, IDC_STATIC_09, m_ctrlStatic09);
	DDX_Control(pDX, IDC_STATIC_10, m_ctrlStatic10);
	DDX_Control(pDX, IDC_STATIC_11, m_ctrlStatic11);
	DDX_Control(pDX, IDC_STATIC_12, m_ctrlStatic12);
	DDX_Control(pDX, IDC_STATIC_13, m_ctrlStatic13);
	DDX_Control(pDX, IDC_STATIC_14, m_ctrlStatic14);
	DDX_Control(pDX, IDC_STATIC_15, m_ctrlStatic15);
	DDX_Control(pDX, IDC_STATIC_16, m_ctrlStatic16);
}

void CParametriTabellaNewEdtDlg::OnCancel()
{
}

BOOL CParametriTabellaNewEdtDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	UDACCEL pAccel[1];
	pAccel[0].nSec = 0;
	pAccel[0].nInc = 1;

	m_ctrlSpinDecimali.SetAccel(1, pAccel);
	m_ctrlSpinDecimali.SetRange32(0, 5);
	m_ctrlSpinDecimali.SetPos32(0);

	//

	if (m_lIDParametro <= 0)
	{
		SetWindowText(theApp.GetMessageString(IDS_PARAMETRITABELLA_NEW_TITLE));
	}
	else
	{
		SetWindowText(theApp.GetMessageString(IDS_PARAMETRITABELLA_EDT_TITLE));

		//

		CString sFilter;
		sFilter.Format("ID=%li", m_lIDParametro);

		CTabellaParametriSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CParametriTabellaNewEdtDlg::OnInitDialog"))
		{
			if (!setTemp.IsEOF())
			{
				m_ctrlEditParametro.SetWindowText(setTemp.m_sParametro);
				m_ctrlEditFormula.SetWindowText(setTemp.m_sFormula);
				m_ctrlSpinDecimali.SetPos32(setTemp.m_lDecimali);
				m_ctrlEditUnitaDiMisura.SetWindowText(setTemp.m_sUnitaDiMisura);
				m_ctrlEditRifM.SetWindowText(setTemp.m_sRiferimentoM);
				m_ctrlEditRifMmin.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoMmin));
				m_ctrlEditRifMmax.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoMmax));
				m_ctrlEditRifF.SetWindowText(setTemp.m_sRiferimentoF);
				m_ctrlEditRifFmin.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoFmin));
				m_ctrlEditRifFmax.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoFmax));
				m_ctrlEditRifPed00.SetWindowText(setTemp.m_sRiferimentoPed00);
				m_ctrlEditRifPed00min.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed00min));
				m_ctrlEditRifPed00max.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed00max));
				m_ctrlEditRifPed01.SetWindowText(setTemp.m_sRiferimentoPed01);
				m_ctrlEditRifPed01min.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed01min));
				m_ctrlEditRifPed01max.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed01max));
				m_ctrlEditRifPed02.SetWindowText(setTemp.m_sRiferimentoPed02);
				m_ctrlEditRifPed02min.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed02min));
				m_ctrlEditRifPed02max.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed02max));
				m_ctrlEditRifPed03.SetWindowText(setTemp.m_sRiferimentoPed03);
				m_ctrlEditRifPed03min.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed03min));
				m_ctrlEditRifPed03max.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed03max));
				m_ctrlEditRifPed04.SetWindowText(setTemp.m_sRiferimentoPed04);
				m_ctrlEditRifPed04min.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed04min));
				m_ctrlEditRifPed04max.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed04max));
				m_ctrlEditRifPed05.SetWindowText(setTemp.m_sRiferimentoPed05);
				m_ctrlEditRifPed05min.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed05min));
				m_ctrlEditRifPed05max.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed05max));
				m_ctrlEditRifPed06.SetWindowText(setTemp.m_sRiferimentoPed06);
				m_ctrlEditRifPed06min.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed06min));
				m_ctrlEditRifPed06max.SetWindowText(GetValueStr(&setTemp, &setTemp.m_fRiferimentoPed06max));
			}

			setTemp.CloseRecordset("CParametriTabellaNewEdtDlg::OnInitDialog");
		}
	}

	theApp.LocalizeDialog(this, CParametriTabellaNewEdtDlg::IDD, "ParametriTabellaNewEdtDlg");
	return TRUE;
}

void CParametriTabellaNewEdtDlg::OnOK()
{
}

void CParametriTabellaNewEdtDlg::OnBnClickedBtnSave()
{
	CString sParametro;
	m_ctrlEditParametro.GetWindowText(sParametro);

	sParametro.Trim();
	if (sParametro.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(IDS_ERRORE_PARAMETRO_VUOTO);
		return;
	}

	if (m_lIDParametro <= 0)
	{
		// NEW //

		CTabellaParametriSet setTemp;
		setTemp.SetOpenFilter("ID=0");
		if (setTemp.OpenRecordset("CParametriTabellaNewEdtDlg::OnBnClickedBtnSave"))
		{
			if (setTemp.AddNewRecordset("CParametriTabellaNewEdtDlg::OnBnClickedBtnSave"))
			{
				setTemp.m_lIDStruttura = m_lIDStruttura;
				setTemp.m_lOrdine = m_lOrdine;
				setTemp.m_sParametro = sParametro;
				m_ctrlEditFormula.GetWindowText(setTemp.m_sFormula);
				setTemp.m_lDecimali = m_ctrlSpinDecimali.GetPos32();
				m_ctrlEditUnitaDiMisura.GetWindowText(setTemp.m_sUnitaDiMisura);
				m_ctrlEditRifM.GetWindowText(setTemp.m_sRiferimentoM);
				SetValueReal(IDC_EDIT_M_MIN, &setTemp, &setTemp.m_fRiferimentoMmin);
				SetValueReal(IDC_EDIT_M_MAX, &setTemp, &setTemp.m_fRiferimentoMmax);
				m_ctrlEditRifF.GetWindowText(setTemp.m_sRiferimentoF);
				SetValueReal(IDC_EDIT_F_MIN, &setTemp, &setTemp.m_fRiferimentoFmin);
				SetValueReal(IDC_EDIT_F_MAX, &setTemp, &setTemp.m_fRiferimentoFmax);
				m_ctrlEditRifPed00.GetWindowText(setTemp.m_sRiferimentoPed00);
				SetValueReal(IDC_EDIT_P00_MIN, &setTemp, &setTemp.m_fRiferimentoPed00min);
				SetValueReal(IDC_EDIT_P00_MAX, &setTemp, &setTemp.m_fRiferimentoPed00max);
				m_ctrlEditRifPed01.GetWindowText(setTemp.m_sRiferimentoPed01);
				SetValueReal(IDC_EDIT_P01_MIN, &setTemp, &setTemp.m_fRiferimentoPed01min);
				SetValueReal(IDC_EDIT_P01_MAX, &setTemp, &setTemp.m_fRiferimentoPed01max);
				m_ctrlEditRifPed02.GetWindowText(setTemp.m_sRiferimentoPed02);
				SetValueReal(IDC_EDIT_P02_MIN, &setTemp, &setTemp.m_fRiferimentoPed02min);
				SetValueReal(IDC_EDIT_P02_MAX, &setTemp, &setTemp.m_fRiferimentoPed02max);
				m_ctrlEditRifPed03.GetWindowText(setTemp.m_sRiferimentoPed03);
				SetValueReal(IDC_EDIT_P03_MIN, &setTemp, &setTemp.m_fRiferimentoPed03min);
				SetValueReal(IDC_EDIT_P03_MAX, &setTemp, &setTemp.m_fRiferimentoPed03max);
				m_ctrlEditRifPed04.GetWindowText(setTemp.m_sRiferimentoPed04);
				SetValueReal(IDC_EDIT_P04_MIN, &setTemp, &setTemp.m_fRiferimentoPed04min);
				SetValueReal(IDC_EDIT_P04_MAX, &setTemp, &setTemp.m_fRiferimentoPed04max);
				m_ctrlEditRifPed05.GetWindowText(setTemp.m_sRiferimentoPed05);
				SetValueReal(IDC_EDIT_P05_MIN, &setTemp, &setTemp.m_fRiferimentoPed05min);
				SetValueReal(IDC_EDIT_P05_MAX, &setTemp, &setTemp.m_fRiferimentoPed05max);
				m_ctrlEditRifPed06.GetWindowText(setTemp.m_sRiferimentoPed06);
				SetValueReal(IDC_EDIT_P06_MIN, &setTemp, &setTemp.m_fRiferimentoPed06min);
				SetValueReal(IDC_EDIT_P06_MAX, &setTemp, &setTemp.m_fRiferimentoPed06max);

				if (setTemp.UpdateRecordset("CParametriTabellaNewEdtDlg::OnBnClickedBtnSave"))
					m_lLastAdd = setTemp.GetLastAdd();
			}

			setTemp.CloseRecordset("CParametriTabellaNewEdtDlg::OnBnClickedBtnSave");
		}
	}
	else
	{
		// EDT //

		CString sFilter;
		sFilter.Format("ID=%li", m_lIDParametro);

		CTabellaParametriSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CParametriTabellaNewEdtDlg::OnBnClickedBtnSave"))
		{
			if (!setTemp.IsEOF())
			{
				if (setTemp.EditRecordset("CParametriTabellaNewEdtDlg::OnBnClickedBtnSave"))
				{
					setTemp.m_sParametro = sParametro;
					m_ctrlEditFormula.GetWindowText(setTemp.m_sFormula);
					setTemp.m_lDecimali = m_ctrlSpinDecimali.GetPos32();
					m_ctrlEditUnitaDiMisura.GetWindowText(setTemp.m_sUnitaDiMisura);
					m_ctrlEditRifM.GetWindowText(setTemp.m_sRiferimentoM);
					SetValueReal(IDC_EDIT_M_MIN, &setTemp, &setTemp.m_fRiferimentoMmin);
					SetValueReal(IDC_EDIT_M_MAX, &setTemp, &setTemp.m_fRiferimentoMmax);
					m_ctrlEditRifF.GetWindowText(setTemp.m_sRiferimentoF);
					SetValueReal(IDC_EDIT_F_MIN, &setTemp, &setTemp.m_fRiferimentoFmin);
					SetValueReal(IDC_EDIT_F_MAX, &setTemp, &setTemp.m_fRiferimentoFmax);
					m_ctrlEditRifPed00.GetWindowText(setTemp.m_sRiferimentoPed00);
					SetValueReal(IDC_EDIT_P00_MIN, &setTemp, &setTemp.m_fRiferimentoPed00min);
					SetValueReal(IDC_EDIT_P00_MAX, &setTemp, &setTemp.m_fRiferimentoPed00max);
					m_ctrlEditRifPed01.GetWindowText(setTemp.m_sRiferimentoPed01);
					SetValueReal(IDC_EDIT_P01_MIN, &setTemp, &setTemp.m_fRiferimentoPed01min);
					SetValueReal(IDC_EDIT_P01_MAX, &setTemp, &setTemp.m_fRiferimentoPed01max);
					m_ctrlEditRifPed02.GetWindowText(setTemp.m_sRiferimentoPed02);
					SetValueReal(IDC_EDIT_P02_MIN, &setTemp, &setTemp.m_fRiferimentoPed02min);
					SetValueReal(IDC_EDIT_P02_MAX, &setTemp, &setTemp.m_fRiferimentoPed02max);
					m_ctrlEditRifPed03.GetWindowText(setTemp.m_sRiferimentoPed03);
					SetValueReal(IDC_EDIT_P03_MIN, &setTemp, &setTemp.m_fRiferimentoPed03min);
					SetValueReal(IDC_EDIT_P03_MAX, &setTemp, &setTemp.m_fRiferimentoPed03max);
					m_ctrlEditRifPed04.GetWindowText(setTemp.m_sRiferimentoPed04);
					SetValueReal(IDC_EDIT_P04_MIN, &setTemp, &setTemp.m_fRiferimentoPed04min);
					SetValueReal(IDC_EDIT_P04_MAX, &setTemp, &setTemp.m_fRiferimentoPed04max);
					m_ctrlEditRifPed05.GetWindowText(setTemp.m_sRiferimentoPed05);
					SetValueReal(IDC_EDIT_P05_MIN, &setTemp, &setTemp.m_fRiferimentoPed05min);
					SetValueReal(IDC_EDIT_P05_MAX, &setTemp, &setTemp.m_fRiferimentoPed05max);
					m_ctrlEditRifPed06.GetWindowText(setTemp.m_sRiferimentoPed06);
					SetValueReal(IDC_EDIT_P06_MIN, &setTemp, &setTemp.m_fRiferimentoPed06min);
					SetValueReal(IDC_EDIT_P06_MAX, &setTemp, &setTemp.m_fRiferimentoPed06max);

					setTemp.UpdateRecordset("CParametriTabellaNewEdtDlg::OnBnClickedBtnSave");
				}
			}

			setTemp.CloseRecordset("CParametriTabellaNewEdtDlg::OnBnClickedBtnSave");
		}
	}

	CDialog::OnOK();
}

void CParametriTabellaNewEdtDlg::OnBnClickedBtnUndo()
{
	CDialog::OnCancel();
}

void CParametriTabellaNewEdtDlg::OnDeltaposSpinDecimali(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int nLower;
	int nUpper;
	m_ctrlSpinDecimali.GetRange32(nLower, nUpper);

	int nDecimali;
	if (pNMUpDown->iDelta < 0)
		nDecimali = max(nLower, pNMUpDown->iPos + pNMUpDown->iDelta);
	else
		nDecimali = min(nUpper, pNMUpDown->iPos + pNMUpDown->iDelta);

	*pResult = 0;
}

long CParametriTabellaNewEdtDlg::GetLastAdd()
{
	return m_lLastAdd;
}

CString CParametriTabellaNewEdtDlg::GetValueStr(CTabellaParametriSet* pSet, float* pField)
{
	CString sReturn = "";

	if (!pSet->IsFieldNull(pField))
	{
		CString sFormat;
		sFormat.Format("%%.%df", m_ctrlSpinDecimali.GetPos32());

		sReturn.Format(sFormat, *pField);
	}

	return sReturn;
}

void CParametriTabellaNewEdtDlg::SetValueReal(UINT uiControl, CTabellaParametriSet* pSet, float* pField)
{
	CString strText;
	GetDlgItemText(uiControl, strText);

	strText.Replace(',', '.');
	strText.Trim();
	if (strText.Right(1).Compare(".") == 0)
		strText = strText.Left(strText.GetLength() - 1);

	BOOL bNull = strText.IsEmpty();
	for (int i = 0; i < strText.GetLength(); i++)
	{
		if (!std::isdigit(strText[i]) && (strText[i] != '.') && (strText[i] != ','))
		{
			bNull = TRUE;
			break;
		}
	}

	if (bNull)
	{
		pSet->SetFieldDirty(pField, TRUE);
		pSet->SetFieldNull(pField, TRUE);
	}
	else
	{
		*pField = (float)atof(strText);
	}
}
