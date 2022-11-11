#include "stdafx.h"
#include "Endox.h"
#include "MstProcedureTerapeuticheUseDlg.h"
#include "EsamiView.h"
#include "MstProcedureTerapeuticheSet.h"
#include "EsamiSet.h"
#include "TipiEsamiOrganiSet.h"
#include "MstOrganoSet.h"
#include "SedeSet.h"
#include "RicercaProcTeraSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstProcedureTerapeuticheUseDlg, CDialog)

CMstProcedureTerapeuticheUseDlg::CMstProcedureTerapeuticheUseDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CMstProcedureTerapeuticheUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_pTipoEsame = &m_pEsamiView->m_pEsamiSet->m_lIDEsame;
}

CMstProcedureTerapeuticheUseDlg::~CMstProcedureTerapeuticheUseDlg()
{
}

BEGIN_MESSAGE_MAP(CMstProcedureTerapeuticheUseDlg, CDialog)
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
	ON_BN_CLICKED(IDC_AGGIUNGI, OnBnClickedAggiungi)
	ON_BN_CLICKED(IDC_DESELECT, OnBnClickedDeselect)
END_MESSAGE_MAP()

void CMstProcedureTerapeuticheUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LABEL_ORGANO,   m_ctrlStaticOrgano);
	DDX_Control(pDX, IDC_STATIC_SEDE,    m_ctrlStaticSede);
	DDX_Control(pDX, IDC_STATIC_TERMINI, m_ctrlStaticTerm);
	DDX_Control(pDX, IDC_AGGIUNGI,       m_ctrlButtonAdd);
	DDX_Control(pDX, IDC_DESELECT,       m_ctrlButtonDeselect);
	DDX_Control(pDX, IDCANCEL,           m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK,               m_ctrlButtonOK);

	DDX_Control(pDX, IDC_LIST_ORGANI, m_ctrlListOrgani);
	DDX_Control(pDX, IDC_TREE_SEDI, m_ctrlTreeSedi);

	DDX_Control(pDX, IDC_LIST_LEVEL0, m_ctrlListLevel0);
	DDX_Control(pDX, IDC_LIST_LEVEL1, m_ctrlListLevel1);
	DDX_Control(pDX, IDC_LIST_LEVEL2, m_ctrlListLevel2);
	DDX_Control(pDX, IDC_LIST_LEVEL3, m_ctrlListLevel3);
	DDX_Control(pDX, IDC_LIST_LEVEL4, m_ctrlListLevel4);
	DDX_Control(pDX, IDC_LIST_LEVEL5, m_ctrlListLevel5);
	DDX_Control(pDX, IDC_LIST_LEVEL7, m_ctrlListLevel6);
}

HBRUSH CMstProcedureTerapeuticheUseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

BOOL CMstProcedureTerapeuticheUseDlg::OnInitDialog()
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

	theApp.LocalizeDialog(this, CMstProcedureTerapeuticheUseDlg::IDD, "MstProcedureTerapeuticheUseDlg");
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		SetDlgItemText(IDOK, theApp.GetMessageString(IDS_MSTDIAGNOSIUSE_OK));

	return bReturn;
}

CString CMstProcedureTerapeuticheUseDlg::GetValue()
{
	return m_strValue;
}

void CMstProcedureTerapeuticheUseDlg::SetValue(CString sValue)
{
	m_strValue = sValue;
}

void CMstProcedureTerapeuticheUseDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT_PROCEDURE, m_strValue);

	OnOK();
}

void CMstProcedureTerapeuticheUseDlg::CreaFrase()
{
	if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0)
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
	else
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

				strValue = strValue + "% " + strTemp;
			}

			iTemp = m_ctrlListLevel2.GetCurSel();
			if (iTemp >= 0)
			{
				m_ctrlListLevel2.GetText(iTemp, strTemp);

				strValue = strValue + "% " + strTemp;
			}

			iTemp = m_ctrlListLevel3.GetCurSel();
			if (iTemp >= 0)
			{
				m_ctrlListLevel3.GetText(iTemp, strTemp);

				strValue = strValue + "% " + strTemp;
			}

			iTemp = m_ctrlListLevel4.GetCurSel();
			if (iTemp >= 0)
			{
				m_ctrlListLevel4.GetText(iTemp, strTemp);

				strValue = strValue + "% " + strTemp;
			}

			iTemp = m_ctrlListLevel5.GetCurSel();
			if (iTemp >= 0)
			{
				m_ctrlListLevel5.GetText(iTemp, strTemp);

				strValue = strValue + "% " + strTemp;
			}

			iTemp = m_ctrlListLevel6.GetCurSel();
			if (iTemp >= 0)
			{
				m_ctrlListLevel6.GetText(iTemp, strTemp);

				strValue = strValue + "% " + strTemp;
			}
		}

		SetDlgItemText(IDC_EDIT_FRASE, strValue);
	}
}

void CMstProcedureTerapeuticheUseDlg::RiempiListOrgani()
{
	int iTemp;

	m_ctrlListOrgani.ResetContent();

	CString strTemp;
	CTipiEsamiOrganiSet setJoin;
	CMstOrganoSet setOrgano;
	
	strTemp.Format("TipoEsame=%li", *m_pTipoEsame);
	setJoin.SetOpenFilter(strTemp);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		CMstOrganoSet setTemp;

		if (setTemp.OpenRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListOrgani") == TRUE)
		{
			while (!setTemp.IsEOF())
			{
				iTemp = m_ctrlListOrgani.AddString(setTemp.m_sOrgano);
				m_ctrlListOrgani.SetItemData(iTemp, (long)setTemp.m_lContatore);
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListOrgani");
		}
	}
	else if (setJoin.OpenRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListOrgani") == TRUE)
	{
		while(setJoin.IsEOF() == FALSE)
		{
			strTemp.Format("Contatore=%li", setJoin.m_lOrgano);
			setOrgano.SetOpenFilter(strTemp);

			if (setOrgano.OpenRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListOrgani") == TRUE)
			{
				if (setOrgano.IsEOF() == FALSE)
				{
					iTemp = m_ctrlListOrgani.AddString(setOrgano.m_sOrgano);
					m_ctrlListOrgani.SetItemData(iTemp, (long)setOrgano.m_lContatore);
				}
			}

			setJoin.MoveNext();
		}

		setOrgano.CloseRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListOrgani");
		setJoin.CloseRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListOrgani");
	}
}

void CMstProcedureTerapeuticheUseDlg::RiempiTreeSedi()
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
	if (setTemp1.OpenRecordset("CMstProcedureTerapeuticheUseDlg::RiempiTreeSedi") == FALSE)
		return;

	while(setTemp1.IsEOF() == FALSE)
	{
		hPadre = m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp1.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp1.m_lContatore, TVI_ROOT, TVI_LAST);

		strTemp.Format("Padre=%li", setTemp1.m_lContatore);
		setTemp2.SetOpenFilter(strTemp);
		if (setTemp2.OpenRecordset("CMstProcedureTerapeuticheUseDlg::RiempiTreeSedi") == TRUE)
		{
			while(setTemp2.IsEOF() == FALSE)
			{
				m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp2.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp2.m_lContatore, hPadre, TVI_LAST);

				setTemp2.MoveNext();
			}

			setTemp2.CloseRecordset("CMstProcedureTerapeuticheUseDlg::RiempiTreeSedi");
		}

		m_ctrlTreeSedi.Expand(hPadre, TVE_EXPAND);

		setTemp1.MoveNext();
	}

	setTemp1.CloseRecordset("CMstProcedureTerapeuticheUseDlg::RiempiTreeSedi");
}

void CMstProcedureTerapeuticheUseDlg::RiempiListLevel0()
{
	if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0)
	{
		// modalità normale //

		int iTemp = 0;
		CString strTemp;
		CMstProcedureTerapeuticheSet setTemp;

		strTemp.Format("TipoEsame=%li", *m_pTipoEsame);
		setTemp.SetBaseFilter(strTemp);
		setTemp.SetOpenFilter("Padre=0 AND Livello=0");
		setTemp.SetSortRecord("Descrizione");

		m_ctrlListLevel0.ResetContent();

		if (setTemp.OpenRecordset("CMstProcedureTerapeuticheModDlg::RiempiListLevel0") == TRUE)
		{
			while(setTemp.IsEOF() == FALSE)
			{
				m_ctrlListLevel0.InsertString(iTemp, setTemp.m_sDescrizione);
				m_ctrlListLevel0.SetItemData(iTemp, (DWORD)setTemp.m_lContatore);
				
				iTemp++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMstProcedureTerapeuticheModDlg::RiempiListLevel0");
		}

		if (m_ctrlListLevel0.GetCount() == 0)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MSTPROCEDURE_EXAM_TYPE));
			EndDialog(IDCANCEL);
		}
	}
	else
	{
		// modalità ricerca //

		CRicercaProcTeraSet setTemp;

		m_ctrlListLevel0.ResetContent();

		if (setTemp.OpenRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListLevel0"))
		{
			CString strPrev = "";

			while(!setTemp.IsEOF())
			{
				if (strPrev != setTemp.m_sDescr1)
				{
					strPrev = setTemp.m_sDescr1;

					m_ctrlListLevel0.AddString(setTemp.m_sDescr1);
				}

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListLevel0");
		}
	}
}

void CMstProcedureTerapeuticheUseDlg::RiempiListSubLevels()
{
	CListBox* pListLevel[] = { &m_ctrlListLevel1, &m_ctrlListLevel2, &m_ctrlListLevel3, &m_ctrlListLevel4, &m_ctrlListLevel5, &m_ctrlListLevel6 };

	if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0)
	{
		// modalità normale //

		int iTemp;
		int nTemp;
		long lPadre = m_ctrlListLevel0.GetCurSel();
		CString strTemp;

		CMstProcedureTerapeuticheSet setTemp;
		setTemp.SetSortRecord("Descrizione");

		if (lPadre >= 0)
			lPadre = (long)m_ctrlListLevel0.GetItemData(lPadre);

		for(nTemp = 0; nTemp < 6; nTemp++)
		{
			iTemp = 0;

			pListLevel[nTemp]->ResetContent();

			strTemp.Format("TipoEsame=%li", *m_pTipoEsame);
			if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0)
				setTemp.SetBaseFilter(strTemp);

			strTemp.Format("Padre=%li AND Livello=%d", lPadre, nTemp + 1);
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CMstProcedureTerapeuticheModDlg::RiempiListSubLevels") == TRUE)
			{
				while(setTemp.IsEOF() == FALSE)
				{
					pListLevel[nTemp]->InsertString(iTemp, setTemp.m_sDescrizione);
					pListLevel[nTemp]->SetItemData(iTemp, (DWORD)setTemp.m_lContatore);

					iTemp++;
					setTemp.MoveNext();
				}
			}
		}

		setTemp.CloseRecordset("CMstProcedureTerapeuticheModDlg::RiempiListSubLevels");
	}
	else
	{
		// modalità ricerca //

		int nCurSel = m_ctrlListLevel0.GetCurSel();

		for(int i = 0; i < 6; i++)
			pListLevel[i]->ResetContent();

		if (nCurSel >= 0)
		{
			CRicercaProcTeraSet setTemp;

			CString strTemp;
			m_ctrlListLevel0.GetText(nCurSel, strTemp);
			strTemp.Replace("'", "''");

			setTemp.SetOpenFilter("DESCR1='" + strTemp + "'");
			if (setTemp.OpenRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListSubLevels"))
			{
				while(!setTemp.IsEOF())
				{
					if (!setTemp.IsFieldNull(&setTemp.m_lLevel2))
						if ((setTemp.m_lLevel2 > 0) && (setTemp.m_lLevel2 <= 6))
							pListLevel[setTemp.m_lLevel2 - 1]->AddString(setTemp.m_sDescr2);

					setTemp.MoveNext();
				}

				setTemp.CloseRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListSubLevels");
			}
		}
	}
}

void CMstProcedureTerapeuticheUseDlg::OnBnClickedDeselect()
{
	m_ctrlListOrgani.SetCurSel(-1);
	RiempiTreeSedi();

	CreaFrase();
}

void CMstProcedureTerapeuticheUseDlg::OnLbnSelchangeListOrgani()
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

void CMstProcedureTerapeuticheUseDlg::OnTvnSelchangedTreeSedi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	m_ctrlListLevel1.ResetContent();
	m_ctrlListLevel2.ResetContent();
	m_ctrlListLevel3.ResetContent();
	m_ctrlListLevel4.ResetContent();
	m_ctrlListLevel5.ResetContent();
	m_ctrlListLevel6.ResetContent();

	m_ctrlListLevel0.SetCurSel(-1);

	GetDlgItem(IDC_EDIT_FRASE)->SetWindowText("");

	CreaFrase();

	*pResult = 0;
}

void CMstProcedureTerapeuticheUseDlg::OnLbnSelchangeListLevel0()
{
	RiempiListSubLevels();

	CreaFrase();
}

void CMstProcedureTerapeuticheUseDlg::OnLbnSelchangeListLevel1()
{
	CreaFrase();
}

void CMstProcedureTerapeuticheUseDlg::OnLbnSelchangeListLevel2()
{
	CreaFrase();
}

void CMstProcedureTerapeuticheUseDlg::OnLbnSelchangeListLevel3()
{
	CreaFrase();
}

void CMstProcedureTerapeuticheUseDlg::OnLbnSelchangeListLevel4()
{
	CreaFrase();
}

void CMstProcedureTerapeuticheUseDlg::OnLbnSelchangeListLevel5()
{
	CreaFrase();
}

void CMstProcedureTerapeuticheUseDlg::OnLbnSelchangeListLevel6()
{
	CreaFrase();
}

void CMstProcedureTerapeuticheUseDlg::OnBnClickedAggiungi()
{
	CString strFrase;
	CString strProcedureTerapeutiche;

	GetDlgItemText(IDC_EDIT_FRASE, strFrase);
	if (strFrase.IsEmpty() == FALSE)
	{
		GetDlgItemText(IDC_EDIT_PROCEDURE, strProcedureTerapeutiche);

		if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		{
			if (strProcedureTerapeutiche.IsEmpty())
				SetDlgItemText(IDC_EDIT_PROCEDURE, strFrase);
			else
				SetDlgItemText(IDC_EDIT_PROCEDURE, strProcedureTerapeutiche + " OR " + strFrase);
		}
		else
		{
			if (strProcedureTerapeutiche.IsEmpty())
				SetDlgItemText(IDC_EDIT_PROCEDURE, strFrase);
			else
				SetDlgItemText(IDC_EDIT_PROCEDURE, strProcedureTerapeutiche + "\r\n" + strFrase);
		}
	
	}
}
