#include "stdafx.h"
#include "Endox.h"
#include "MeasurementsAliasMappingSet.h"
#include "MeasurementsMappingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMeasurementsMappingDlg, CDialog)

CMeasurementsMappingDlg::CMeasurementsMappingDlg(CWnd* pParent)
: CDialog(CMeasurementsMappingDlg::IDD, pParent)
{
	m_sVariableName = "";
	m_sNomeParametro = "";
	m_sAlias = "";
	m_bAddNew = FALSE;
}

CMeasurementsMappingDlg::~CMeasurementsMappingDlg()
{
}

BEGIN_MESSAGE_MAP(CMeasurementsMappingDlg, CDialog)
	ON_BN_CLICKED(IDC_EDT, OnBnClickedEdt)
	ON_BN_CLICKED(IDC_SAVE, OnBnClickedSave)
	ON_BN_CLICKED(IDC_UNDO, OnBnClickedUndo)
	ON_BN_CLICKED(IDC_NEW, OnBnClickedNew)
	ON_BN_CLICKED(IDC_DEL, OnBnClickedDel)
	ON_LBN_SELCHANGE(IDC_LISTA_MEDIDAS, OnLbnSelchangeListaMedidas)
	ON_BN_CLICKED(IDCANCEL, &CMeasurementsMappingDlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnCbnSelchangeComboType)
END_MESSAGE_MAP()

void CMeasurementsMappingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LISTA_MEDIDAS, m_ctrlListaVar);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4); //Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5); //Gabriel - BUG 5533 V2 - Cálculo medidas biométricas

	DDX_Control(pDX, IDC_EDT, m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_UNDO, m_ctrlButtonUndo);
	DDX_Control(pDX, IDC_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_DEL, m_ctrlButtonDelete);

	DDX_Text(pDX, IDC_VARIABLENAME, m_sVariableName);
	DDX_Text(pDX, IDC_NOMEPARAMETRO, m_sNomeParametro);
	DDX_Text(pDX, IDC_ALIAS, m_sAlias);
	DDX_Text(pDX, IDC_DECIMALS, m_sDecimals); //Gabriel - BUG 5533 V2 - Cálculo medidas biométricas

	DDX_Control(pDX, IDC_COMBO_TYPE, m_ctrlComboType); //Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
}

BOOL CMeasurementsMappingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_1)->SetFont(&theApp.m_fontBold);	
	GetDlgItem(IDC_STATIC_2)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_3)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_4)->SetFont(&theApp.m_fontBold); //Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
	GetDlgItem(IDC_STATIC_5)->SetFont(&theApp.m_fontBold);
		
	GetDlgItem(IDC_EDT)->EnableWindow(m_ctrlListaVar.GetCurSel() >= 0);
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);	
	GetDlgItem(IDC_NEW)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_VARIABLENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOMEPARAMETRO)->EnableWindow(FALSE);
	
	//GetDlgItem(IDC_ALIAS)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ALIAS)->EnableWindow(FALSE);
	SetDlgItemText(IDC_ALIAS, "");

	GetDlgItem(IDC_DECIMALS)->EnableWindow(FALSE);

	m_ctrlListaVar.EnableWindow(TRUE);

	RiempiLista();

	//Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
	if (theApp.m_bAtivaEspermograma)
	{
		GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_5)->ShowWindow(SW_SHOW);
		m_ctrlComboType.ShowWindow(SW_SHOW);
		m_ctrlComboType.EnableWindow(FALSE);
		GetDlgItem(IDC_DECIMALS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DECIMALS)->EnableWindow(FALSE);

		m_ctrlComboType.InsertString(0, "");
		m_ctrlComboType.InsertString(1, "Texto");
		m_ctrlComboType.InsertString(2, "Numérico");
	}
	else
	{
		GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_HIDE);
		m_ctrlComboType.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DECIMALS)->ShowWindow(SW_HIDE);
	}

	theApp.LocalizeDialog(this, CMeasurementsMappingDlg::IDD, "MeasurementsMappingDlg");

	RedrawWindow();

	return TRUE;
}

void CMeasurementsMappingDlg::OnBnClickedEdt()
{	
	m_bAddNew = FALSE;	

	//GetDlgItem(IDC_ALIAS)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ALIAS)->EnableWindow(FALSE);

	SetDlgItemText(IDC_ALIAS, "");

	m_ctrlListaVar.EnableWindow(FALSE);
	GetDlgItem(IDC_VARIABLENAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_NOMEPARAMETRO)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_EDT)->EnableWindow(FALSE);	
	GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_UNDO)->EnableWindow(TRUE);
	GetDlgItem(IDC_NEW)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	// Deseleziono tutti gli elementi dalle liste delle prestazioni //
	m_ctrlListaVar.SelItemRange(FALSE, 0, m_ctrlListaVar.GetCount() - 1);	

	//Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
	if (theApp.m_bAtivaEspermograma)
	{
		GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
		m_ctrlComboType.ShowWindow(SW_SHOW);
		m_ctrlComboType.EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DECIMALS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DECIMALS)->EnableWindow(TRUE);
	}

	UpdateData(FALSE);
	RedrawWindow();

}


void CMeasurementsMappingDlg::OnBnClickedSave()
{
	UpdateData(TRUE);

	if (m_sVariableName.IsEmpty() || m_sNomeParametro.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MEASURENTSMAPPING_FIELDEMPTY), MB_ICONINFORMATION);
		return;
	}
	if (m_bAddNew)
	{
		if (m_sAlias.IsEmpty())
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MEASURENTSMAPPING_FIELDEMPTY), MB_ICONINFORMATION);
			return;
		}
		
		//Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
		if (theApp.m_bAtivaEspermograma)
		{
			CString sType;
			m_ctrlComboType.GetLBText(m_ctrlComboType.GetCurSel(), sType);

			long lDecimals;
			lDecimals = atol(m_sDecimals);

			CMeasurementsAliasMappingSet setTemp;
			setTemp.AddRow(m_sAlias, m_sVariableName, m_sNomeParametro, sType, lDecimals);
		}
		else
		{
			CMeasurementsAliasMappingSet setTemp;
			setTemp.AddRow(m_sAlias, m_sVariableName, m_sNomeParametro);
		}
	}
	else
	{
		int nIndex = m_ctrlListaVar.GetCurSel();

		if (nIndex >= 0)
		{
			CString strFilter;
			if (theApp.m_bAtivaEspermograma)
				strFilter.Format("ID=%li AND UO = %li", (long)m_ctrlListaVar.GetItemData(nIndex), theApp.m_lUO);
			else
				strFilter.Format("ID=%li", (long)m_ctrlListaVar.GetItemData(nIndex));

			CMeasurementsAliasMappingSet setTemp;
			setTemp.SetOpenFilter(strFilter);

			if (setTemp.OpenRecordset("CMeasurementsMapping::OnBnClickedSave"))
			{
				if (!setTemp.IsEOF())
				{
					if (setTemp.EditRecordset("CMeasurementsMapping::OnBnClickedSave"))
					{
						setTemp.m_sVariableName = m_sVariableName;
						setTemp.m_sNomeParametro = m_sNomeParametro;
						//Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
						if (theApp.m_bAtivaEspermograma)
						{
							CString sType;
							m_ctrlComboType.GetLBText(m_ctrlComboType.GetCurSel(), sType);
							setTemp.m_sValueType = sType;

							long lDecimals;
							lDecimals = atol(m_sDecimals);
							setTemp.m_lDecimals = lDecimals;
						}

						setTemp.UpdateRecordset("CMeasurementsMapping::OnBnClickedSave");
					}
				}
				setTemp.CloseRecordset("CMeasurementsMapping::OnBnClickedSave");
			}
		}
	}

	m_bAddNew = FALSE;

	//GetDlgItem(IDC_ALIAS)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ALIAS)->EnableWindow(FALSE);
	m_sAlias = "";

	m_ctrlListaVar.EnableWindow(TRUE);
	GetDlgItem(IDC_VARIABLENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOMEPARAMETRO)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDT)->EnableWindow(m_ctrlListaVar.GetCurSel() >= 0);
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);	
	GetDlgItem(IDC_NEW)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	//Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
	if (theApp.m_bAtivaEspermograma)
	{
		m_ctrlComboType.ShowWindow(SW_SHOW);
		m_ctrlComboType.EnableWindow(FALSE);
		GetDlgItem(IDC_DECIMALS)->EnableWindow(FALSE);
	}

	RiempiLista();
	RedrawWindow();
}

void CMeasurementsMappingDlg::OnBnClickedDel()
{
	UpdateData(TRUE);

	if (m_sVariableName.IsEmpty() || m_sNomeParametro.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MEASURENTSMAPPING_FIELDEMPTY), MB_ICONINFORMATION);
		return;
	}
	
	int nIndex = m_ctrlListaVar.GetCurSel();

	if (nIndex >= 0)
	{
		CString strFilter;
		if (theApp.m_bAtivaEspermograma)
			strFilter.Format("ID=%li AND UO = %li", (long)m_ctrlListaVar.GetItemData(nIndex), theApp.m_lUO);
		else
			strFilter.Format("ID=%li", (long)m_ctrlListaVar.GetItemData(nIndex));

		CMeasurementsAliasMappingSet setTemp;
		setTemp.SetOpenFilter(strFilter);

		if (setTemp.OpenRecordset("CMeasurementsMapping::OnBnClickedDel"))
		{
			if (!setTemp.IsEOF())
			{
				setTemp.DeleteRecordset("CMeasurementsMapping::OnBnClickedDel");
			}
			setTemp.CloseRecordset("CMeasurementsMapping::OnBnClickedDel");
		}
	}
	

	m_bAddNew = FALSE;

	//GetDlgItem(IDC_ALIAS)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ALIAS)->EnableWindow(FALSE);
	m_sAlias = "";

	m_ctrlListaVar.EnableWindow(TRUE);
	GetDlgItem(IDC_VARIABLENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOMEPARAMETRO)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDT)->EnableWindow(m_ctrlListaVar.GetCurSel() >= 0);
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_NEW)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	//Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
	if (theApp.m_bAtivaEspermograma)
	{
		m_ctrlComboType.ShowWindow(SW_SHOW);
		m_ctrlComboType.EnableWindow(FALSE);
		GetDlgItem(IDC_DECIMALS)->EnableWindow(FALSE);
	}

	RiempiLista();
	RedrawWindow();
}


void CMeasurementsMappingDlg::OnBnClickedUndo()
{
	m_bAddNew = FALSE;

	SetDlgItemText(IDC_ALIAS, "");
	SetDlgItemText(IDC_VARIABLENAME, "");
	SetDlgItemText(IDC_NOMEPARAMETRO, "");

	//GetDlgItem(IDC_ALIAS)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ALIAS)->EnableWindow(FALSE);

	m_ctrlListaVar.EnableWindow(TRUE);
	GetDlgItem(IDC_VARIABLENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOMEPARAMETRO)->EnableWindow(FALSE);
		
	GetDlgItem(IDC_EDT)->EnableWindow(m_ctrlListaVar.GetCurSel() >= 0);
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);
	GetDlgItem(IDC_NEW)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	//Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
	if (theApp.m_bAtivaEspermograma)
	{
		m_ctrlComboType.ShowWindow(SW_SHOW);
		m_ctrlComboType.EnableWindow(FALSE);
		GetDlgItem(IDC_DECIMALS)->EnableWindow(FALSE);
	}

	RiempiLista();
	OnLbnSelchangeListaMedidas();
	RedrawWindow();
}

void CMeasurementsMappingDlg::OnBnClickedNew()
{
	m_bAddNew = TRUE;
	
	m_ctrlListaVar.SetCurSel(-1);
	
	SetDlgItemText(IDC_ALIAS, "");
	SetDlgItemText(IDC_VARIABLENAME, "");
	SetDlgItemText(IDC_NOMEPARAMETRO, "");
	SetDlgItemText(IDC_DECIMALS, "0");

	//GetDlgItem(IDC_ALIAS)->ShowWindow(SW_SHOW);
	//GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ALIAS)->EnableWindow(TRUE);


	m_ctrlListaVar.EnableWindow(FALSE);
	GetDlgItem(IDC_VARIABLENAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_NOMEPARAMETRO)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_UNDO)->EnableWindow(TRUE);
	GetDlgItem(IDC_NEW)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);	

	//Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
	if (theApp.m_bAtivaEspermograma)
	{
		m_ctrlComboType.ShowWindow(SW_SHOW);
		m_ctrlComboType.EnableWindow(TRUE);
	}
}

void CMeasurementsMappingDlg::OnLbnSelchangeListaMedidas()
{
	m_bAddNew = FALSE;

	int nCurPos = m_ctrlListaVar.GetCurSel();

	GetDlgItem(IDC_EDT)->EnableWindow(nCurPos >= 0);	

	if (nCurPos >= 0)
	{
		long lID = (long)m_ctrlListaVar.GetItemData(nCurPos);

		if (lID >= 0)
		{
			//Gabriel - BUG 5533 V2 - Filtro por UO
			CString strFilter;
			if (theApp.m_bAtivaEspermograma)
				strFilter.Format("ID=%li AND UO = %li", lID, theApp.m_lUO);
			else
				strFilter.Format("ID=%li", lID);

			CMeasurementsAliasMappingSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CMeasurementsMapping::OnLbnSelchangeListaMedidas"))
			{
				if (!setTemp.IsEOF())
				{
					m_sAlias = setTemp.m_sAlias;
					m_sVariableName = setTemp.m_sVariableName;
					m_sNomeParametro = setTemp.m_sNomeParametro;
					//Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
					if (theApp.m_bAtivaEspermograma)
					{
						CString sType = setTemp.m_sValueType;
						if (sType == "Texto")
							m_ctrlComboType.SetCurSel(1);
						else if (sType == "Numérico")
							m_ctrlComboType.SetCurSel(2);
						else
							m_ctrlComboType.SetCurSel(0);

						CString sDecimals;
						sDecimals.Format("%li", setTemp.m_lDecimals);
						m_sDecimals = sDecimals == "1246576928" ? "0" : sDecimals;

						AggiornaCombo();
					}
				}
				setTemp.CloseRecordset("CMeasurementsMapping::OnLbnSelchangeListaMedidas");
			}
			UpdateData(FALSE);
		}
	}
	else
	{
		m_ctrlListaVar.SelItemRange(FALSE, 0, m_ctrlListaVar.GetCount() - 1);
	}
}

void CMeasurementsMappingDlg::RiempiLista()
{
	//Gabriel - BUG 5533 V2 - Filtro por UO
	CString sFilter;
	sFilter.Format("UO = %li", theApp.m_lUO);
	
	CMeasurementsAliasMappingSet setTemp;
	
	m_ctrlListaVar.ResetContent();

	if (theApp.m_bAtivaEspermograma)
		setTemp.SetOpenFilter(sFilter);
	setTemp.SetSortRecord("Alias");
	if (setTemp.OpenRecordset("CMeasurementsMapping::RiempiLista") == TRUE)
	{
		int iTemp = 0;

		while (setTemp.IsEOF() == FALSE)
		{
			m_ctrlListaVar.InsertString(iTemp, setTemp.m_sAlias);
			m_ctrlListaVar.SetItemData(iTemp, (DWORD)setTemp.m_lID);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMeasurementsMapping::RiempiLista");
	}
}

void CMeasurementsMappingDlg::OnBnClickedCancel()
{	
	CDialog::OnCancel();
}

void CMeasurementsMappingDlg::OnCbnSelchangeComboType()
{
	AggiornaCombo();
}

void CMeasurementsMappingDlg::AggiornaCombo()
{
	long lType = m_ctrlComboType.GetCurSel();
	switch (lType)
	{
		case 0:
		case 1:
		default:
			GetDlgItem(IDC_STATIC_5)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_DECIMALS)->ShowWindow(SW_HIDE);
			break;
		case 2:
			GetDlgItem(IDC_STATIC_5)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_DECIMALS)->ShowWindow(SW_SHOW);
			break;
	}
}