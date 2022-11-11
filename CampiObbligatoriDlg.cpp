#include "stdafx.h"
#include "Endox.h"
#include "Endox.h"
#include "CampiObbligatoriDlg.h"
#include "VistaCampiObbligatoriDistinctSet.h"
#include "EsamiView.h"
#include "FasiEsameSet.h"
#include "CampiObbligatoriInsModDlg.h"
#include "FieldDlg.h"
#include "CampiObbligatoriSet.h"
#include "ProvenienzaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCampiObbligatoriDlg, CDialog)

CCampiObbligatoriDlg::CCampiObbligatoriDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CCampiObbligatoriDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CCampiObbligatoriDlg::~CCampiObbligatoriDlg()
{
}

BEGIN_MESSAGE_MAP(CCampiObbligatoriDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_NUOVO, OnBnClickedBtnNuovo)
	ON_BN_CLICKED(IDC_BTN_MODIFICA, OnBnClickedBtnModifica)
	ON_BN_CLICKED(IDC_BTN_CANCELLA, OnBnClickedBtnCancella)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

END_MESSAGE_MAP()

void CCampiObbligatoriDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_BTN_NUOVO, m_ctrlBtnNew);
	DDX_Control(pDX, IDC_BTN_MODIFICA, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_CANCELLA, m_ctrlBtnDel);
	DDX_Control(pDX, IDOK, m_ctrlBtnExit);
}

BOOL CCampiObbligatoriDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	if (theApp.m_nApplication == PRG_IMAGENT)
	{
		m_ctrlList.InsertColumn(0, "Tipo esame", LVCFMT_CENTER, 0);
		m_ctrlList.InsertColumn(1, "Provenienza", LVCFMT_CENTER, 0);
		m_ctrlList.InsertColumn(2, "Fase", LVCFMT_CENTER, 0);
		m_ctrlList.InsertColumn(3, "Campo", LVCFMT_LEFT, 600);
	}
	else
	{
		m_ctrlList.InsertColumn(0, "Tipo esame", LVCFMT_CENTER, 200);
		m_ctrlList.InsertColumn(1, "Provenienza", LVCFMT_CENTER, 100);
		m_ctrlList.InsertColumn(2, "Fase", LVCFMT_CENTER, 150);
		m_ctrlList.InsertColumn(3, "Campo", LVCFMT_LEFT, 300);
	}

	RiempiLista();

	theApp.LocalizeDialog(this, CCampiObbligatoriDlg::IDD, "CampiObbligatoriDlg");
	return TRUE;
}

void CCampiObbligatoriDlg::OnBnClickedBtnNuovo()
{
	CCampiObbligatoriInsModDlg dlg(this, m_pEsamiView, -1);
	if (dlg.DoModal() == IDOK)
		RiempiLista();
}

void CCampiObbligatoriDlg::OnBnClickedBtnModifica()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		CCampiObbligatoriInsModDlg dlg(this, m_pEsamiView, (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos)));
		if (dlg.DoModal() == IDOK)
			RiempiLista();
	}
}

void CCampiObbligatoriDlg::OnBnClickedBtnCancella()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONFIRM_DELETE_FIELD), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			long lToDel = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

			CCampiObbligatoriSet set;
			CString strFilter;
			strFilter.Format("ID = %li", lToDel);
			set.SetOpenFilter(strFilter);
			if (set.OpenRecordset("CCampiObbligatoriDlg::OnBnClickedBtnCancella"))
			{
				if (!set.IsEOF() && set.DeleteRecordset("CCampiObbligatoriDlg::OnBnClickedBtnCancella"))
					RiempiLista();
				set.CloseRecordset("CCampiObbligatoriDlg::OnBnClickedBtnCancella");
			}
		}
	}
}

void CCampiObbligatoriDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_ctrlBtnEdt.EnableWindow(m_ctrlList.GetFirstSelectedItemPosition() != NULL);
	m_ctrlBtnDel.EnableWindow(m_ctrlList.GetFirstSelectedItemPosition() != NULL);

	*pResult = 0;
}

void CCampiObbligatoriDlg::RiempiLista()
{
	CVistaCampiObbligatoriDistinctSet setTemp;
	int nIndex = 0;

	// Sandro 29/05/2013 //

	CString sTestoFisso = theApp.GetMessageString(IDS_TESTOFISSO);
	long lLenTestoFisso = sTestoFisso.GetLength();

	//

	m_ctrlList.DeleteAllItems();
	if (setTemp.OpenRecordset("CCampiObbligatoriDlg::RiempiLista"))
	{
		while(!setTemp.IsEOF())
		{
			if (!setTemp.IsFieldNull(&setTemp.m_sTipiEsame))
				m_ctrlList.InsertItem(nIndex, setTemp.m_sTipiEsame);
			else
				m_ctrlList.InsertItem(nIndex, theApp.GetMessageString(IDS_INVIANTE_TUTTI));
			m_ctrlList.SetItemData(nIndex, setTemp.m_lID);

			m_ctrlList.SetItemText(nIndex, 1, setTemp.m_sProvenienze);

			//if (setTemp.m_lIDFaseNew > 0)
			//{
				m_ctrlList.SetItemText(nIndex, 2, CFasiEsameSet().GetDescrizione(setTemp.m_lIDFaseNew));
			//}
			/*else
			{
				switch (setTemp.m_lFase)
				{
					case CO_FASE_CHIUSURA_STAMPA:
					{
						m_ctrlList.SetItemText(nIndex, 2, theApp.GetMessageString(IDS_CO_CHIUSURA_STAMPA));
						break;
					}
					case CO_FASE_CONVALIDA:
					{
						m_ctrlList.SetItemText(nIndex, 2, theApp.GetMessageString(IDS_CO_CONVALIDA));
						break;
					}
				}
			}*/

			for (int i = 0; i < form_list_total; i++)
			{
				if (g_FormCaract[i].lID == setTemp.m_lCampo)
				{
					// Sandro 29/05/2013 //

					CString sToAdd = g_FormCaract[i].sDescrizione;
					if (sToAdd.GetLength() > lLenTestoFisso)
					{
						if (sToAdd.Right(lLenTestoFisso).CompareNoCase(sTestoFisso) == 0)
						{
							sToAdd = sToAdd.Left(sToAdd.GetLength() - lLenTestoFisso);
							sToAdd.Trim();
						}
					}

					m_ctrlList.SetItemText(nIndex, 3, sToAdd);

					//

					break;
				}
			}

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CCampiObbligatoriDlg::RiempiLista");
	}

	m_ctrlList.SortItems(CCampiObbligatoriDlg::MyCompareProc, (LPARAM)&m_ctrlList);

	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_ctrlList.GetDlgItem(0);	
	for (int h = 0; h<pHeader->GetItemCount(); h++)
		m_ctrlList.SetColumnWidth(h, LVSCW_AUTOSIZE_USEHEADER);

}

int CALLBACK CCampiObbligatoriDlg::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
   CListCtrl* pListCtrl = (CListCtrl*)lParamSort;

   int nItems = pListCtrl->GetItemCount();
   int nIndex1 = -1;
   int nIndex2 = -1;
   int i;

   for(i = 0; i < nItems; i++)
   {
	   if (pListCtrl->GetItemData(i) == lParam1)
	   {
		   nIndex1 = i;
		   break;
	   }
   }
   for(i = 0; i < nItems; i++)
   {
	   if (pListCtrl->GetItemData(i) == lParam2)
	   {
		   nIndex2 = i;
		   break;
	   }
   }

   if ((nIndex1 >= 0) && (nIndex2 >= 0))
   {
		int nResult = strcmp(pListCtrl->GetItemText(nIndex1, 0), pListCtrl->GetItemText(nIndex2, 0));
		if (nResult != 0)
			return nResult;

		nResult = strcmp(pListCtrl->GetItemText(nIndex1, 1), pListCtrl->GetItemText(nIndex2, 1));
		if (nResult != 0)
			return nResult;

		nResult = strcmp(pListCtrl->GetItemText(nIndex1, 2), pListCtrl->GetItemText(nIndex2, 2));
		if (nResult != 0)
			return nResult;

		return strcmp(pListCtrl->GetItemText(nIndex1, 3), pListCtrl->GetItemText(nIndex2, 3));
   }

   return 0;
}
