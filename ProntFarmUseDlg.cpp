#include "stdafx.h"
#include "Endox.h"
#include "ProntFarmUseDlg.h"

#include "EsamiView.h"
#include "FarmaciSet.h"
#include "FarmaciDistinctSet.h"
#include "FarmaciUnionSet.h"
#include ".\prontfarmusedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CProntFarmUseDlg, CDialog)

CProntFarmUseDlg::CProntFarmUseDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL bSingleSelection)
	: CDialog(CProntFarmUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_bSingleSelection = bSingleSelection;

	m_strFarmaci = "";
}

BEGIN_MESSAGE_MAP(CProntFarmUseDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_LBN_SELCHANGE(IDC_LIST_00, OnLbnSelchangeList00)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_02, OnLvnItemchangedList02)

	ON_BN_CLICKED(IDC_BTN_AGGIUNGI, OnBnClickedBtnAggiungi)
	ON_BN_CLICKED(IDC_BTN_AZZERA, OnBnClickedBtnAzzera)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBnClickedBtnReset)

	ON_EN_CHANGE(IDC_EDIT_RICERCA, OnEnChangeEditRicerca)
END_MESSAGE_MAP()

void CProntFarmUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_00, m_ctrlList00);
	DDX_Control(pDX, IDC_LIST_02, m_ctrlList02);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_BTN_AGGIUNGI, m_ctrlBtnAggiungi);
	DDX_Control(pDX, IDC_BTN_AZZERA, m_ctrlBtnAzzera);
	DDX_Control(pDX, IDC_BTN_RESET, m_ctrlBtnReset);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);

	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //
}

BOOL CProntFarmUseDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	// theApp.AfxMessageBoxEndo(m_strFarmaci);

	m_ctrlBtnAggiungi.ShowWindow(!m_bSingleSelection);
	m_ctrlBtnAzzera.ShowWindow(!m_bSingleSelection);
	m_ctrlBtnReset.ShowWindow(m_bSingleSelection);
	GetDlgItem(IDC_EDIT)->ShowWindow(!m_bSingleSelection);

	m_ctrlList02.SetExtendedStyle(m_ctrlList02.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlList02.InsertColumn(0, "");
	m_ctrlList02.InsertColumn(1, "AIC", LVCFMT_CENTER, 68);
	m_ctrlList02.InsertColumn(2, "DESCRIZIONE", LVCFMT_LEFT, 272);
	m_ctrlList02.InsertColumn(3, "CL.", LVCFMT_CENTER, 34);
	m_ctrlList02.InsertColumn(4, "N1", LVCFMT_CENTER, 34);
	m_ctrlList02.InsertColumn(5, "N2", LVCFMT_CENTER, 34);
	m_ctrlList02.InsertColumn(6, "DITTA", LVCFMT_LEFT, 136);

	m_ctrlList02.SetColumnWidth(0, 0);

	BeginWaitCursor();

	m_ctrlList00.ResetContent();
	m_ctrlList02.DeleteAllItems();

	SetDlgItemText(IDC_EDIT, m_strFarmaci);

	if ((m_bSingleSelection) && (!m_strFarmaci.IsEmpty()))
	{
		// cerco di riselezionare il farmaco //
		CFarmaciUnionSet setUnion;

		CString strFilter = "DescrizioneMassima='" + m_strFarmaci + "'";

		setUnion.SetOpenFilter(strFilter);
		if (setUnion.OpenRecordset("CProntFarmUseDlg::OnInitDialog"))
		{
			if (!setUnion.IsEOF())
			{
				int nIndex = m_ctrlList00.FindStringExact(-1, setUnion.m_sDescrizioneMedia);

				if (nIndex >= 0)
				{
					m_ctrlList00.SetCurSel(nIndex);
					OnLbnSelchangeList00();

					for(int i = 0; i < m_ctrlList02.GetItemCount(); i++)
					{
						if (m_ctrlList02.GetItemText(i, 2) == setUnion.m_sDescrizione)
						{
							m_ctrlList02.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
							break;
						}
					}
				}
			}

			setUnion.CloseRecordset("CProntFarmUseDlg::OnInitDialog");
		}
	}

	EndWaitCursor();

	theApp.LocalizeDialog(this, CProntFarmUseDlg::IDD, "ProntFarmUseDlg");

	return bReturn;
}

void CProntFarmUseDlg::OnBnClickedOk()
{
	if (m_bSingleSelection)
	{
		m_strFarmaci = "";

		POSITION pos = m_ctrlList02.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nItem = m_ctrlList02.GetNextSelectedItem(pos);

			CString strList;
			m_ctrlList00.GetText(m_ctrlList00.GetCurSel(), strList);

			m_strFarmaci = strList + " " + m_ctrlList02.GetItemText(nItem, 2);
		}
		else
		{
			int iCurSel = m_ctrlList00.GetCurSel();
			if (iCurSel >= 0)
				m_ctrlList00.GetText(iCurSel, m_strFarmaci);
		}
	}
	else
	{
		GetDlgItemText(IDC_EDIT, m_strFarmaci);
	}

	OnOK();
}

void CProntFarmUseDlg::OnLbnSelchangeList00()
{
	m_ctrlTextControl.ResetContents();

	int nIndex = m_ctrlList00.GetCurSel();

	BeginWaitCursor();
	m_ctrlList02.DeleteAllItems();

	if (nIndex >= 0)
	{
		int nTemp1;
		int nTemp2;
		int nAdded = 0;

		CString strTemp;
		m_ctrlList00.GetText(nIndex, strTemp);
		strTemp.Replace("'", "''");

		nTemp1 = strTemp.Find('(') + 1;
		CString strPrincipio = strTemp.Left(nTemp1 - 2);

		nTemp2 = strTemp.Find(')', nTemp1);
		CString strNome = strTemp.Mid(nTemp1, nTemp2 - nTemp1);

		CFarmaciSet setFarmaci;
		setFarmaci.SetOpenFilter("Nome='" + strNome + "' AND PrincipioAttivo='" + strPrincipio +"'");
		setFarmaci.SetSortRecord("Descrizione, Ditta");
		if (setFarmaci.OpenRecordset("CProntFarmModDlg::OnLbnSelchangeList00"))
		{
			while(!setFarmaci.IsEOF())
			{
				m_ctrlList02.InsertItem(nAdded, "");
				m_ctrlList02.SetItemData(nAdded, setFarmaci.m_lID);

				if (!setFarmaci.IsFieldNull(&setFarmaci.m_sAIC))
					m_ctrlList02.SetItemText(nAdded, 1, setFarmaci.m_sAIC);

				if (!setFarmaci.IsFieldNull(&setFarmaci.m_sDescrizione))
					m_ctrlList02.SetItemText(nAdded, 2, setFarmaci.m_sDescrizione);
				
				if (!setFarmaci.IsFieldNull(&setFarmaci.m_sClasse))
					m_ctrlList02.SetItemText(nAdded, 3, setFarmaci.m_sClasse);
				
				if (!setFarmaci.IsFieldNull(&setFarmaci.m_sNota1))
					m_ctrlList02.SetItemText(nAdded, 4, setFarmaci.m_sNota1);
				
				if (!setFarmaci.IsFieldNull(&setFarmaci.m_sNota2))
					m_ctrlList02.SetItemText(nAdded, 5, setFarmaci.m_sNota2);
				
				if (!setFarmaci.IsFieldNull(&setFarmaci.m_sDitta))
					m_ctrlList02.SetItemText(nAdded, 6, setFarmaci.m_sDitta);
				
				nAdded++;
				setFarmaci.MoveNext();
			}

			setFarmaci.CloseRecordset("CProntFarmModDlg::OnLbnSelchangeList00");
		}
	}
	EndWaitCursor();
}

void CProntFarmUseDlg::OnLvnItemchangedList02(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_ctrlTextControl.ResetContents();

	POSITION pos = m_ctrlList02.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		CString strFilter;
		strFilter.Format("ID=%li", m_ctrlList02.GetItemData(m_ctrlList02.GetNextSelectedItem(pos)));

		CFarmaciSet setFarmaci;
		setFarmaci.SetOpenFilter(strFilter);
		if (setFarmaci.OpenRecordset("CProntFarmUseDlg::OnLvnItemchangedList02"))
		{
			if (!setFarmaci.IsEOF())
			{
				if (setFarmaci.m_sBugiardinoRTF.IsEmpty())
				{
					m_ctrlTextControl.SetText(setFarmaci.m_sBugiardinoTXT);
				}
				else
				{
					try
					{
						m_ctrlTextControl.SetRTFSelText(setFarmaci.m_sBugiardinoRTF);
					}
					catch(...)
					{
						m_ctrlTextControl.SetText(setFarmaci.m_sBugiardinoRTF);
					}
				}
			}

			setFarmaci.CloseRecordset("CProntFarmUseDlg::OnLvnItemchangedList02");
		}
	}
}

CString CProntFarmUseDlg::GetFarmaci()
{
	return m_strFarmaci;
}

void CProntFarmUseDlg::SetFarmaci(CString strFarmaci)
{
	m_strFarmaci = strFarmaci;
}

void CProntFarmUseDlg::OnBnClickedBtnAggiungi()
{
	POSITION pos = m_ctrlList02.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_ctrlList02.GetNextSelectedItem(pos);

		CString strList;
		m_ctrlList00.GetText(m_ctrlList00.GetCurSel(), strList);

		strList = strList + " " + m_ctrlList02.GetItemText(nItem, 2);

		CString strEdit;
		GetDlgItemText(IDC_EDIT, strEdit);
		if (!strEdit.IsEmpty())
			strEdit += "\r\n";
		SetDlgItemText(IDC_EDIT, strEdit + strList);

		m_ctrlList00.SetCurSel(-1);
		OnLbnSelchangeList00();
	}
}

void CProntFarmUseDlg::OnBnClickedBtnAzzera()
{
	SetDlgItemText(IDC_EDIT, "");
}

void CProntFarmUseDlg::OnBnClickedBtnReset()
{
	m_ctrlList00.SetCurSel(-1);
	OnLbnSelchangeList00();
}

void CProntFarmUseDlg::OnEnChangeEditRicerca()
{
	CString sRicerca;
	GetDlgItemText(IDC_EDIT_RICERCA, sRicerca);

	BeginWaitCursor();
	m_ctrlList00.SetRedraw(FALSE);

	m_ctrlList00.ResetContent();
	if (sRicerca.GetLength() > 2)
	{
		sRicerca.Replace("%", "");
		sRicerca.Replace("'", "''");

		CString sFilter;
		sFilter.Format("Nome LIKE '%%%s%%' OR PRINCIPIOATTIVO LIKE '%%%s%%'", sRicerca, sRicerca);

		CFarmaciDistinctSet setFarmaciDistinct;
		setFarmaciDistinct.SetOpenFilter(sFilter);
		if (setFarmaciDistinct.OpenRecordset("CProntFarmModDlg::OnInitDialog"))
		{
			while(!setFarmaciDistinct.IsEOF())
			{
				CString strTemp;

				// Sandro 04/01/2014 // RAS 20130176 //

				if (!setFarmaciDistinct.IsFieldNull(&setFarmaciDistinct.m_sPrincipioAttivo))
					strTemp = setFarmaciDistinct.m_sPrincipioAttivo;
				if (!setFarmaciDistinct.IsFieldNull(&setFarmaciDistinct.m_sNome))
					strTemp = strTemp + " (" + setFarmaciDistinct.m_sNome + ")";

				m_ctrlList00.AddString(strTemp);

				setFarmaciDistinct.MoveNext();
			}

			setFarmaciDistinct.CloseRecordset("CProntFarmModDlg::OnInitDialog");
		}
	}

	m_ctrlList00.SetRedraw(TRUE);
	EndWaitCursor();
}
