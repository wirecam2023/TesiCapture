#include "stdafx.h"
#include "Endox.h"
#include "MstComplicanze2UseDlg.h"

#include "EsamiSet.h"
#include "EsamiView.h"
#include "MstComplicanze2Set.h"
#include "MstOrganoSet.h"
#include "SedeSet.h"
#include "TipiEsamiOrganiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstComplicanze2UseDlg, CDialog)

CMstComplicanze2UseDlg::CMstComplicanze2UseDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CMstComplicanze2UseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CMstComplicanze2UseDlg::~CMstComplicanze2UseDlg()
{
}

BEGIN_MESSAGE_MAP(CMstComplicanze2UseDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_LBN_SELCHANGE(IDC_LIST_ORGANI, OnLbnSelchangeListOrgani)

	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_SEDI, OnTvnSelchangedTreeSedi)

	ON_LBN_SELCHANGE(IDC_LIST_LEVEL0, OnLbnSelchangeListLevel0)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL1, OnLbnSelchangeListLevel1)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL2, OnLbnSelchangeListLevel2)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL3, OnLbnSelchangeListLevel3)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL4, OnLbnSelchangeListLevel4)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL5, OnLbnSelchangeListLevel5)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL7, OnLbnSelchangeListLevel6)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_AGGIUNGI,        OnBnClickedAggiungi)
	ON_BN_CLICKED(IDC_DESELECT,        OnBnClickedDeselect)
END_MESSAGE_MAP()

void CMstComplicanze2UseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_ORGANI, m_ctrlListOrgani);
	DDX_Control(pDX, IDC_TREE_SEDI, m_ctrlTreeSedi);

	DDX_Control(pDX, IDC_LIST_LEVEL0, m_ctrlListLevel0);
	DDX_Control(pDX, IDC_LIST_LEVEL1, m_ctrlListLevel1);
	DDX_Control(pDX, IDC_LIST_LEVEL2, m_ctrlListLevel2);
	DDX_Control(pDX, IDC_LIST_LEVEL3, m_ctrlListLevel3);
	DDX_Control(pDX, IDC_LIST_LEVEL4, m_ctrlListLevel4);
	DDX_Control(pDX, IDC_LIST_LEVEL5, m_ctrlListLevel5);
	DDX_Control(pDX, IDC_LIST_LEVEL7, m_ctrlListLevel6);

	DDX_Control(pDX, IDC_LABEL_ORGANO,   m_ctrlStaticOrgano);
	DDX_Control(pDX, IDC_STATIC_SEDE,    m_ctrlStaticSede);
	DDX_Control(pDX, IDC_STATIC_TERMINI, m_ctrlStaticTerm);
	DDX_Control(pDX, IDC_AGGIUNGI,       m_ctrlButtonAdd);
	DDX_Control(pDX, IDC_DESELECT,       m_ctrlButtonDeselect);
	DDX_Control(pDX, IDCANCEL,           m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK,               m_ctrlButtonOK);
}

HBRUSH CMstComplicanze2UseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_LABEL_ORGANO:
		case IDC_LIST_ORGANI:
			pDC->SetTextColor(theApp.m_color[0]);
			break;

		case IDC_STATIC_SEDE:
		case IDC_TREE_SEDI:
			pDC->SetTextColor(theApp.m_color[1]);
			break;

		case IDC_STATIC_TERMINI:
		case IDC_LIST_LEVEL0:
		case IDC_LIST_LEVEL1:
		case IDC_LIST_LEVEL2:
		case IDC_LIST_LEVEL3:
		case IDC_LIST_LEVEL4:
		case IDC_LIST_LEVEL5:
		case IDC_LIST_LEVEL7:
			pDC->SetTextColor(theApp.m_color[2]);
			break;
	}

	return hBrush;
}

BOOL CMstComplicanze2UseDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_PROCEDURE, m_strValue);
	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_LABEL_ORGANO)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_SEDE)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_TERMINI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_DESELECT)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_AGGIUNGI)->SetFont(&theApp.m_fontBold);

	m_ctrlTreeSedi.SetTextColor(theApp.m_color[1]);

	RiempiListOrgani();
	RiempiListLevel0();

	theApp.LocalizeDialog(this, CMstComplicanze2UseDlg::IDD, "MstComplicanze2UseDlg");
	
	SetWindowText(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_367));
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		SetDlgItemText(IDOK, theApp.GetMessageString(IDS_MSTDIAGNOSIUSE_OK));

	return bReturn;
}

CString CMstComplicanze2UseDlg::GetValue()
{
	return m_strValue;
}

void CMstComplicanze2UseDlg::SetValue(CString sValue)
{
	m_strValue = sValue;
}

void CMstComplicanze2UseDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT_PROCEDURE, m_strValue);

	if (m_strValue.Right(4) == " OR ")
		m_strValue = m_strValue.Left(m_strValue.GetLength() - 4);

	OnOK();
}

void CMstComplicanze2UseDlg::CreaFrase()
{
	int iTemp;
	CString strTemp;
	CString strValue = "";

	iTemp = m_ctrlListLevel0.GetCurSel();
	if (iTemp >= 0)
	{
		m_ctrlListLevel0.GetText(iTemp, strValue);

		iTemp = m_ctrlListOrgani.GetCurSel();
		if (iTemp >= 0)
		{
			HTREEITEM hPadre;
			HTREEITEM hSelez;

			m_ctrlListOrgani.GetText(iTemp, strTemp);

			strValue = strValue + " " + theApp.GetMessageString(IDS_IN) + " " + strTemp;

			hSelez = m_ctrlTreeSedi.GetSelectedItem();
			if (hSelez != NULL)
			{
				hPadre = m_ctrlTreeSedi.GetParentItem(hSelez);

				if (hPadre != NULL)
					strValue = strValue + " " + m_ctrlTreeSedi.GetItemText(hPadre);

				if (hPadre != hSelez)
					strValue = strValue + " " + m_ctrlTreeSedi.GetItemText(hSelez);
			}
		}

		iTemp = m_ctrlListLevel1.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel1.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}

		iTemp = m_ctrlListLevel2.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel2.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}

		iTemp = m_ctrlListLevel3.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel3.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}

		iTemp = m_ctrlListLevel4.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel4.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}

		iTemp = m_ctrlListLevel5.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel5.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}

		iTemp = m_ctrlListLevel6.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel6.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}
	}

	SetDlgItemText(IDC_EDIT_FRASE, strValue);
}

void CMstComplicanze2UseDlg::RiempiListOrgani()
{
	int iTemp;
	long lTipoEsame = m_pEsamiView->m_pEsamiSet->m_lIDEsame;

	m_ctrlListOrgani.ResetContent();

	if (lTipoEsame == 0 || m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lIDEsame))
	{
		CMstOrganoSet setTemp;

		if (setTemp.OpenRecordset("CMstComplicanze2UseDlg::RiempiListOrgani") == TRUE)
		{
			while (!setTemp.IsEOF())
			{
				iTemp = m_ctrlListOrgani.AddString(setTemp.m_sOrgano);
				m_ctrlListOrgani.SetItemData(iTemp, (long)setTemp.m_lContatore);
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMstComplicanze2UseDlg::RiempiListOrgani");
		}
	}
	else
	{
		CString strTemp;
		CTipiEsamiOrganiSet setJoin;
		CMstOrganoSet setOrgano;
		
		strTemp.Format("TipoEsame=%li", lTipoEsame);
		setJoin.SetOpenFilter(strTemp);

		if (setJoin.OpenRecordset("CMstComplicanze2UseDlg::RiempiListOrgani") == TRUE)
		{
			while(setJoin.IsEOF() == FALSE)
			{
				strTemp.Format("Contatore=%li", setJoin.m_lOrgano);
				setOrgano.SetOpenFilter(strTemp);

				if (setOrgano.OpenRecordset("CMstComplicanze2UseDlg::RiempiListOrgani") == TRUE)
				{
					if (setOrgano.IsEOF() == FALSE)
					{
						iTemp = m_ctrlListOrgani.AddString(setOrgano.m_sOrgano);
						m_ctrlListOrgani.SetItemData(iTemp, (long)setOrgano.m_lContatore);
					}
				}

				setJoin.MoveNext();
			}

			setOrgano.CloseRecordset("CMstComplicanze2UseDlg::RiempiListOrgani");
			setJoin.CloseRecordset("CMstComplicanze2UseDlg::RiempiListOrgani");
		}
	}
}

void CMstComplicanze2UseDlg::RiempiTreeSedi()
{
	HTREEITEM hPadre;

	CString strTemp;
	strTemp.Format("Organo=%d and Padre=0", (int)m_ctrlListOrgani.GetItemData(m_ctrlListOrgani.GetCurSel()));

	m_ctrlTreeSedi.DeleteAllItems();

	CMstSediSet setTemp1;
	setTemp1.SetSortRecord("Descrizione");

	CMstSediSet setTemp2;
	setTemp2.SetSortRecord("Descrizione");

	setTemp1.SetBaseFilter(strTemp);
	if (setTemp1.OpenRecordset("CMstComplicanze2UseDlg::RiempiTreeSedi") == FALSE)
		return;

	while(setTemp1.IsEOF() == FALSE)
	{
		hPadre = m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp1.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp1.m_lContatore, TVI_ROOT, TVI_LAST);

		strTemp.Format("Padre=%li", setTemp1.m_lContatore);
		setTemp2.SetOpenFilter(strTemp);
		if (setTemp2.OpenRecordset("CMstComplicanze2UseDlg::RiempiTreeSedi") == TRUE)
		{
			while(setTemp2.IsEOF() == FALSE)
			{
				m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp2.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp2.m_lContatore, hPadre, TVI_LAST);

				setTemp2.MoveNext();
			}

			setTemp2.CloseRecordset("CMstComplicanze2UseDlg::RiempiTreeSedi");
		}

		m_ctrlTreeSedi.Expand(hPadre, TVE_EXPAND);

		setTemp1.MoveNext();
	}

	setTemp1.CloseRecordset("CMstComplicanze2UseDlg::RiempiTreeSedi");
}

void CMstComplicanze2UseDlg::RiempiListLevel0()
{
	int iTemp = 0;
	CMstComplicanze2Set setTemp;

	setTemp.SetOpenFilter("Padre=0 AND Livello=0");
	setTemp.SetSortRecord("Descrizione");

	m_ctrlListLevel0.ResetContent();

	if (setTemp.OpenRecordset("CMstProcedureDiagnosticheModDlg::RiempiListLevel0") == TRUE)
	{
		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListLevel0.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListLevel0.SetItemData(iTemp, (DWORD)setTemp.m_lID);
			
			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMstProcedureDiagnosticheModDlg::RiempiListLevel0");
	}
}

void CMstComplicanze2UseDlg::RiempiListSubLevels()
{
	CListBox* pListLevel[] = { &m_ctrlListLevel1, &m_ctrlListLevel2, &m_ctrlListLevel3, &m_ctrlListLevel4, &m_ctrlListLevel5, &m_ctrlListLevel6 };

	int iTemp;
	int nTemp;
	long lPadre = m_ctrlListLevel0.GetCurSel();
	CString strTemp;
	CMstComplicanze2Set setTemp;

	setTemp.SetSortRecord("Descrizione");

	if (lPadre >= 0)
		lPadre = (long)m_ctrlListLevel0.GetItemData(lPadre);

	for(nTemp = 0; nTemp < 6; nTemp++)
	{
		iTemp = 0;

		pListLevel[nTemp]->ResetContent();

		strTemp.Format("Padre=%li AND Livello=%d", lPadre, nTemp + 1);
		setTemp.SetOpenFilter(strTemp);

		if (setTemp.OpenRecordset("CMstProcedureDiagnosticheModDlg::RiempiListSubLevels") == TRUE)
		{
			while(setTemp.IsEOF() == FALSE)
			{
				pListLevel[nTemp]->InsertString(iTemp, setTemp.m_sDescrizione);
				pListLevel[nTemp]->SetItemData(iTemp, (DWORD)setTemp.m_lID);

				iTemp++;
				setTemp.MoveNext();
			}
		}
	}

	setTemp.CloseRecordset("CMstProcedureDiagnosticheModDlg::RiempiListSubLevels");
}

void CMstComplicanze2UseDlg::OnBnClickedDeselect()
{
	m_ctrlListOrgani.SetCurSel(-1);
	RiempiTreeSedi();

	CreaFrase();
}

void CMstComplicanze2UseDlg::OnLbnSelchangeListOrgani()
{
	RiempiTreeSedi();

	m_ctrlListLevel1.ResetContent();
	m_ctrlListLevel2.ResetContent();
	m_ctrlListLevel3.ResetContent();
	m_ctrlListLevel4.ResetContent();
	m_ctrlListLevel5.ResetContent();
	m_ctrlListLevel6.ResetContent();

	m_ctrlListLevel0.SetCurSel(-1);

	GetDlgItem(IDC_EDIT_FRASE)->SetWindowText("");

	CreaFrase();
}

void CMstComplicanze2UseDlg::OnTvnSelchangedTreeSedi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	CreaFrase();

	m_ctrlListLevel1.ResetContent();
	m_ctrlListLevel2.ResetContent();
	m_ctrlListLevel3.ResetContent();
	m_ctrlListLevel4.ResetContent();
	m_ctrlListLevel5.ResetContent();
	m_ctrlListLevel6.ResetContent();

	m_ctrlListLevel0.SetCurSel(-1);

	GetDlgItem(IDC_EDIT_FRASE)->SetWindowText("");

	*pResult = 0;
}

void CMstComplicanze2UseDlg::OnLbnSelchangeListLevel0()
{
	RiempiListSubLevels();

	CreaFrase();
}

void CMstComplicanze2UseDlg::OnLbnSelchangeListLevel1()
{
	CreaFrase();
}

void CMstComplicanze2UseDlg::OnLbnSelchangeListLevel2()
{
	CreaFrase();
}

void CMstComplicanze2UseDlg::OnLbnSelchangeListLevel3()
{
	CreaFrase();
}

void CMstComplicanze2UseDlg::OnLbnSelchangeListLevel4()
{
	CreaFrase();
}

void CMstComplicanze2UseDlg::OnLbnSelchangeListLevel5()
{
	CreaFrase();
}

void CMstComplicanze2UseDlg::OnLbnSelchangeListLevel6()
{
	CreaFrase();
}

void CMstComplicanze2UseDlg::OnBnClickedAggiungi()
{
	CString strFrase;
	CString strProcedureDiagnostiche;

	GetDlgItemText(IDC_EDIT_FRASE, strFrase);
	if (strFrase.IsEmpty() == FALSE)
	{
		GetDlgItemText(IDC_EDIT_PROCEDURE, strProcedureDiagnostiche);

		if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		{
			if (strProcedureDiagnostiche.IsEmpty())
				SetDlgItemText(IDC_EDIT_PROCEDURE, strFrase);
			else
				SetDlgItemText(IDC_EDIT_PROCEDURE, strProcedureDiagnostiche + " OR " + strFrase);
		}
		else
		{
			if (strProcedureDiagnostiche.IsEmpty())
				SetDlgItemText(IDC_EDIT_PROCEDURE, strFrase);
			else
				SetDlgItemText(IDC_EDIT_PROCEDURE, strProcedureDiagnostiche + "\r\n" + strFrase);
		}

		// Sandro 23/05/2011 // richiesta di Perego (Gottardo) //
		m_ctrlListOrgani.SetCurSel(-1);
		OnLbnSelchangeListOrgani();
	}
}