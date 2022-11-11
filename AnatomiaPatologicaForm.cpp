#include "stdafx.h"
#include "Endox.h"
#include "AnatomiaPatologicaForm.h"

#include <io.h>

#include "AnatomiaPatologicaEsamiPrestSet.h"
#include "AnatomiaPatologicaNewEdtDlg.h"
#include "AnatomiaPatologicaSearchDlg.h"
#include "AnatomiaPatologicaSet.h"
#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "GruppiPrelieviItemView.h"
#include "GruppiPrelieviUseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAnatomiaPatologicaForm::CAnatomiaPatologicaForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_ctrlList.m_pEsamiView = pEsamiView;

	m_wpReadOnly = (WPARAM)TRUE;

	m_bEsameOK = FALSE;

	m_nSearchMode = 0;
}

CAnatomiaPatologicaForm::~CAnatomiaPatologicaForm()
{
}

BEGIN_MESSAGE_MAP(CAnatomiaPatologicaForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_RADIO_NO, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_SI, OnBnClickedRadio)

	ON_BN_CLICKED(IDC_BTN_GRUPPI, OnBnClickedGruppi)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedDel)
	ON_BN_CLICKED(IDC_BTN_STAMPATUTTI, OnBnClickedStampaTutti)

	ON_BN_CLICKED(IDC_BTN_NEW_SEARCH, OnBnClickedNewSearch)
	ON_BN_CLICKED(IDC_BTN_DEL_SEARCH, OnBnClickedDelSearch)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemChangedList) 
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SEARCH, OnLvnItemChangedListSearch) 
END_MESSAGE_MAP()

void CAnatomiaPatologicaForm::CreateFormEx(UINT nID, CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_anatomiapatologica] == NULL)
	{
		pEsamiView->m_pDynForm[sub_anatomiapatologica] = new CAnatomiaPatologicaForm(nID, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_anatomiapatologica] != NULL)
		{
			pEsamiView->m_pDynForm[sub_anatomiapatologica]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_anatomiapatologica]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_anatomiapatologica]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_anatomiapatologica]->CreateChildForm(nID, pParent, rectFrame);
		}
	}
}

BOOL CAnatomiaPatologicaForm::CreateFormEx(UINT nID, CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, CAnatomiaPatologicaForm** pForm)
{
	BOOL bResult = FALSE;

	if ((*pForm) == NULL)
	{
		(*pForm) = new CAnatomiaPatologicaForm(nID, NULL, pEsamiView);
		if ((*pForm) != NULL)
		{
			(*pForm)->m_pParentFrame = pParentFrame;
			(*pForm)->m_lColore = -1;
			(*pForm)->m_lIDFaseBlocco = 2;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pParent->ScreenToClient(&rectFrame); // Sandro 19/10/2015 //
			bResult = (*pForm)->CreateChildForm(nID, pParent, rectFrame);
		}
	}
	
	return bResult;
}

void CAnatomiaPatologicaForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_PRELIEVI, m_ctrlStaticPrelievi);
	DDX_Control(pDX, IDC_RADIO_NO, m_ctrlRadioNo);
	DDX_Control(pDX, IDC_RADIO_SI, m_ctrlRadioSi);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_LIST_SEARCH, m_ctrlListSearch);

	DDX_Control(pDX, IDC_BTN_GRUPPI, m_ctrlButtonGruppi);
	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlButtonDel);
	DDX_Control(pDX, IDC_BTN_STAMPATUTTI, m_ctrlButtonStampaTutti);

	DDX_Control(pDX, IDC_BTN_NEW_SEARCH, m_ctrlBtnNewSearch);
	DDX_Control(pDX, IDC_BTN_DEL_SEARCH, m_ctrlBtnDelSearch);
	DDX_Control(pDX, IDC_RADIO_AND, m_ctrlBtnRadioAnd);
	DDX_Control(pDX, IDC_RADIO_OR, m_ctrlBtnRadioOr);

	if (!pDX->m_bSaveAndValidate)
	{
		m_bEsameOK = (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore)) && (m_pEsamiView->m_pEsamiSet->m_lContatore > 0);
		OnFormReadOnly(m_wpReadOnly, 0);
	}

	DDX_Radio(pDX, IDC_RADIO_NO, m_pEsamiView->m_pEsamiSet->m_nAPEseguitiPrelievi);
	DDX_Radio(pDX, IDC_RADIO_AND, m_nSearchMode);
}

HBRUSH CAnatomiaPatologicaForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_LIST:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CAnatomiaPatologicaForm::OnInitDialog() 
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_PRELIEVI, CSize(0,0), CSize(0,0));
	AddAnchor(IDC_RADIO_NO, CSize(0,0), CSize(0,0));
	AddAnchor(IDC_RADIO_SI, CSize(0,0), CSize(0,0));
	AddAnchor(IDC_LIST, CSize(0,0), CSize(100,100));
	AddAnchor(IDC_LIST_SEARCH, CSize(0,0), CSize(100,100));
	AddAnchor(IDC_BTN_GRUPPI, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_BTN_NEW, CSize(0,100), CSize(0,100));
	AddAnchor(IDC_BTN_EDT, CSize(0,100), CSize(0,100));
	AddAnchor(IDC_BTN_DEL, CSize(0,100), CSize(0,100));
	AddAnchor(IDC_BTN_STAMPATUTTI, CSize(100,100), CSize(100,100));
	AddAnchor(IDC_BTN_NEW_SEARCH, CSize(0,100), CSize(0,100));
	AddAnchor(IDC_BTN_DEL_SEARCH, CSize(0,100), CSize(0,100));
	AddAnchor(IDC_RADIO_AND, CSize(100,100), CSize(100,100));
	AddAnchor(IDC_RADIO_OR, CSize(100,100), CSize(100,100));

	m_ctrlImageList.Create(62, 22, ILC_COLOR32, 2, 0);
	m_ctrlImageList.Add(AfxGetApp()->LoadIcon(IDI_BTN_STAMPA));
	m_ctrlImageList.Add(AfxGetApp()->LoadIcon(IDI_BTN_STAMPA_DIS));

	m_ctrlList.m_pStampaRigaFunction = StampaRiga;
	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlList.SetImageList(&m_ctrlImageList, LVSIL_SMALL);
	m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "", LVCFMT_RIGHT, 30);
	m_ctrlList.InsertColumn(2, "ID Campione", LVCFMT_CENTER, 90);
	m_ctrlList.InsertColumn(3, "Tipo", LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(4, "Intervento", LVCFMT_LEFT, 330);
	m_ctrlList.InsertColumn(5, "Prelievi", LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(6, "Commento", LVCFMT_LEFT, 301);
	m_ctrlList.InsertColumn(7, "", LVCFMT_LEFT, 62);
	m_ctrlList.InsertColumn(8, "Topografia", LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(9, "Snomed1", LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(10, "Snomed2", LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(11, "Snomed3", LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(12, "", LVCFMT_LEFT, 0);

	m_ctrlListSearch.SetExtendedStyle(m_ctrlListSearch.GetExtendedStyle() | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlListSearch.InsertColumn(0, "Codice", LVCFMT_LEFT, 100);
	m_ctrlListSearch.InsertColumn(1, "Descrizione", LVCFMT_LEFT, 300);

	theApp.LocalizeDialog(this, IDD_SUBFORM_ANATOMIAPATOLOGICA, "AnatomiaPatologicaForm");

	RiempiLista();

	return bReturn;
}

long CAnatomiaPatologicaForm::GetContenuto()
{
	return sub_anatomiapatologica;
}

BOOL CAnatomiaPatologicaForm::CampoObbligatorioValido()
{
	BOOL bReturn = FALSE;

	if (m_pEsamiView->m_pEsamiSet->m_nAPEseguitiPrelievi == 0)
		bReturn = TRUE;
	else
		bReturn = (m_ctrlList.GetItemCount() > 0);

	return bReturn;
}

void CAnatomiaPatologicaForm::OnBnClickedRadio()
{
	UpdateData(TRUE);
	OnFormReadOnly(m_wpReadOnly, 0);
}

void CAnatomiaPatologicaForm::OnBnClickedGruppi()
{
	m_ctrlButtonGruppi.SetCheck(BST_UNCHECKED);

	CGruppiPrelieviUseDlg dlg(this, m_pEsamiView);
	if (dlg.DoModal() == IDOK)
	{
		CString strFilter1;
		strFilter1.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CAnatomiaPatologicaSet setAP;
		setAP.SetOpenFilter(strFilter1);
		if (setAP.OpenRecordset("CAnatomiaPatologicaForm::OnBnClickedGruppi"))
		{
			long lIDCampione = 1;

			if (!setAP.IsEOF())
			{
				CString strQuery;
				strQuery.Format("SELECT MAX(IDCampione) AS CONTEGGIO FROM AnatomiaPatologica WHERE IDEsame=%li AND Eliminato=0", m_pEsamiView->m_pEsamiSet->m_lContatore);

				CRecordset setCount(&theApp.m_dbEndox); // è solo per il conteggio //
				setCount.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);
				if (!setCount.IsEOF())
				{
					// con i driver Oracle 9.2 si pianta tutto //
					// CDBVariant dbVariant;
					// setCount.GetFieldValue((short)0 oppure "CONTEGGIO", dbVariant, SQL_C_SLONG);
					// lIDCampione = (dbVariant.m_lVal % 100) + 1;

					// così sembra funzionare invece //
					CString sValue;
					setCount.GetFieldValue("CONTEGGIO", sValue);
					if (sValue.GetLength() > 2)
						sValue = sValue.Right(2);
					lIDCampione = (atol(sValue) % 100) + 1;
				}
				setCount.Close();
			}

			CString strFilter2;
			strFilter2.Format("IDGruppo=%li", dlg.m_lReturn);

			CGruppiPrelieviItemView setItems;
			setItems.SetOpenFilter(strFilter2);
			if (setItems.OpenRecordset("CAnatomiaPatologicaForm::OnBnClickedGruppi"))
			{
				while(!setItems.IsEOF())
				{
					if (setAP.AddNewRecordset("CAnatomiaPatologicaForm::OnBnClickedGruppi"))
					{
						CAnatomiaPatologicaEsamiPrestSet setPrestEsame;

						setAP.m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
						setAP.m_sIDCampione.Format("%08li%02li", m_pEsamiView->m_pEsamiSet->m_lContatore, lIDCampione);
						setAP.m_sTipo = setItems.m_sTipo;
						setAP.m_sIntervCodice = setItems.m_sCodice;
						setAP.m_sIntervProcedura = setItems.m_sIntervento;
						setAP.m_lPrelievi = setItems.m_lPrelievi;
						setAP.m_sDescrizione = setItems.m_sDescrizione;
						// setAP.m_lIDPrestazioneAssociata = setPrestEsame.AddPrestazione(m_pEsamiView->m_pEsamiSet->m_lContatore, lIDPrestazione);
						// setAP.m_sDescrizioneAnatomia = sDescrizioneAnatomia;

						if (setAP.UpdateRecordset("CAnatomiaPatologicaForm::OnBnClickedGruppi"))
							lIDCampione++;
					}

					setItems.MoveNext();
				}

				setItems.CloseRecordset("CAnatomiaPatologicaForm::OnBnClickedGruppi");
			}

			setAP.CloseRecordset("CAnatomiaPatologicaForm::OnBnClickedGruppi");
		}

		RiempiLista();
		OnLvnItemChangedList(NULL, NULL);

		if (m_ctrlList.GetItemCount() > 0)
		{
			// segno che sono stati eseguiti dei prelievi //
			m_pEsamiView->m_pEsamiSet->m_nAPEseguitiPrelievi = 1;
			UpdateData(FALSE);
		}
	}
}

void CAnatomiaPatologicaForm::OnBnClickedNew()
{
	m_ctrlButtonNew.SetCheck(BST_UNCHECKED);

	CAnatomiaPatologicaNewEdtDlg dlg(this, m_pEsamiView, -1);
	if (dlg.DoModal() == IDOK)
	{
		RiempiLista();
		OnLvnItemChangedList(NULL, NULL);

		if (m_ctrlList.GetItemCount() > 0)
		{
			// segno che sono stati eseguiti dei prelievi //
			m_pEsamiView->m_pEsamiSet->m_nAPEseguitiPrelievi = 1;
			UpdateData(FALSE);
		}
	}
}

void CAnatomiaPatologicaForm::OnBnClickedEdt()
{
	m_ctrlButtonEdt.SetCheck(BST_UNCHECKED);

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlList.GetNextSelectedItem(pos);

		CAnatomiaPatologicaNewEdtDlg dlg(this, m_pEsamiView, m_ctrlList.GetItemData(iCurSel));
		if (dlg.DoModal() == IDOK)
			RiempiLista();
	}
}

void CAnatomiaPatologicaForm::OnBnClickedDel()
{
	m_ctrlButtonDel.SetCheck(BST_UNCHECKED);

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlList.GetNextSelectedItem(pos);

		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATOMIAPATOLOGIA_DELETERECORD), MB_YESNO | MB_ICONSTOP) == IDYES)
		{
			CString strFilter;
			strFilter.Format("ID=%li", m_ctrlList.GetItemData(iCurSel));

			CAnatomiaPatologicaSet setTemp;
			setTemp.SetOpenFilter(strFilter);

			if (setTemp.OpenRecordset("CAnatomiaPatologicaForm::OnBnClickedBtnDel"))
			{
				if (!setTemp.IsEOF())
				{
					CAnatomiaPatologicaEsamiPrestSet setPrestEsame;
					setPrestEsame.DelPrestazione(setTemp.m_lIDPrestazioneAssociata);

					setTemp.DeleteRecordset("CAnatomiaPatologicaForm::OnBnClickedBtnDel");
				}

				setTemp.CloseRecordset("CAnatomiaPatologicaForm::OnBnClickedBtnDel");
			}
			
			RiempiLista();
			OnLvnItemChangedList(NULL, NULL);
		}
	}
}

void CAnatomiaPatologicaForm::OnBnClickedStampaTutti()
{
	m_ctrlButtonStampaTutti.SetCheck(BST_UNCHECKED);

	for(int i = 0; i < m_ctrlList.GetItemCount(); i++)
	{
		m_ctrlList.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
		StampaRiga((long)m_ctrlList.GetItemData(i), m_pEsamiView);
	}
}

void CAnatomiaPatologicaForm::RiempiLista()
{
	int nItem = 0;

	CAnatomiaPatologicaSet setTemp;

	CString strFilter;
	strFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	m_ctrlList.ShowWindow(SW_HIDE);
	m_ctrlList.DeleteAllItems();

	setTemp.SetOpenFilter(strFilter);
	setTemp.SetSortRecord("ID");
	if (setTemp.OpenRecordset("CAnatomiaPatologicaForm::RiempiLista"))
	{
		while(!setTemp.IsEOF())
		{
			m_ctrlList.InsertItem(nItem, "", -1);
			m_ctrlList.SetItemData(nItem, (DWORD)setTemp.m_lID);

			CString strTemp;

			strTemp.Format("%li", nItem + 1);
			m_ctrlList.SetItemText(nItem, 1, strTemp);
			m_ctrlList.SetItemText(nItem, 2, setTemp.m_sIDCampione);
			m_ctrlList.SetItemText(nItem, 3, setTemp.m_sTipo);
			m_ctrlList.SetItemText(nItem, 4, /*setTemp.m_sIntervCodice + ": " +*/ setTemp.m_sIntervProcedura);
			if (!setTemp.IsFieldNull(&setTemp.m_lPrelievi))
			{
				strTemp.Format("%li", setTemp.m_lPrelievi);
				m_ctrlList.SetItemText(nItem, 5, strTemp);
			}
			else
			{
				m_ctrlList.SetItemText(nItem, 5, "0");
			}
			m_ctrlList.SetItemText(nItem, 6, setTemp.m_sDescrizione);

			m_ctrlList.SetItem(nItem, 7, LVIF_IMAGE, NULL, (int)m_wpReadOnly, 0, 0, 0);

			m_ctrlList.SetItemText(nItem, 8, setTemp.m_sTopografia);
			m_ctrlList.SetItemText(nItem, 9, setTemp.m_sSnomed1);
			m_ctrlList.SetItemText(nItem, 10, setTemp.m_sSnomed2);
			m_ctrlList.SetItemText(nItem, 11, setTemp.m_sSnomed3);

			nItem++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAnatomiaPatologicaForm::RiempiLista");
	}

	int i;

	for(i = 1; i < 7; i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	for(i = 8; i <= 11; i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList.ShowWindow(SW_SHOW);
}

void CAnatomiaPatologicaForm::StampaRiga(long lRecord, CEsamiView* pEsamiView)
{
	pEsamiView->UpdateData(TRUE);
	long lPdfId = 0;
	pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, theApp.m_sEditRep + "\\Etichette.rpa", FALSE, 1, &lPdfId, "");
}

void CAnatomiaPatologicaForm::OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_bEsameOK = (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore)) && (m_pEsamiView->m_pEsamiSet->m_lContatore > 0);
	OnFormReadOnly(m_wpReadOnly, 0);

	if (pResult != NULL)
		*pResult = 0;
}

void CAnatomiaPatologicaForm::OnLvnItemChangedListSearch(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_bEsameOK = (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore)) && (m_pEsamiView->m_pEsamiSet->m_lContatore > 0);
	OnFormReadOnly(m_wpReadOnly, 0);

	if (pResult != NULL)
		*pResult = 0;
}

LRESULT CAnatomiaPatologicaForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	RiempiLista();

	m_ctrlListSearch.DeleteAllItems();

	return 1;
}

LRESULT CAnatomiaPatologicaForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	if (m_wpReadOnly != wParam)
	{
		m_wpReadOnly = wParam;
		
		for(int i = 0; i < m_ctrlList.GetItemCount(); i++)
			m_ctrlList.SetItem(i, 7, LVIF_IMAGE, NULL, (int)m_wpReadOnly, 0, 0, 0);
		m_ctrlList.SetReadOnly((BOOL)m_wpReadOnly);
	}

	BOOL bStatoModificabile = FALSE;
	if ((!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore)) && (m_pEsamiView->m_pEsamiSet->m_lContatore > 0))
		bStatoModificabile = ((m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_TEMP) || (m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_ANNULLATA) || (m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_SCARTATA));

	// abilitazione del tasto "Elimina" /
	BOOL bElimina = FALSE;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
		bElimina = (m_ctrlList.GetNextSelectedItem(pos) == m_ctrlList.GetItemCount() - 1);

	// abilitazione del tasto "Elimina criterio di ricerca" /
	BOOL bEliminaSearch = FALSE;
	if (m_ctrlListSearch.GetFirstSelectedItemPosition() != NULL)
		bEliminaSearch = TRUE;

	if (m_ctrlList.GetItemCount() > 0)
		m_pEsamiView->m_pEsamiSet->m_nAPEseguitiPrelievi = 1;

	int nEseguitiPrelievi = 0;
	if ((m_pEsamiView->m_pEsamiSet != NULL) && (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_nAPEseguitiPrelievi)))
		nEseguitiPrelievi = m_pEsamiView->m_pEsamiSet->m_nAPEseguitiPrelievi;

	m_ctrlStaticPrelievi.ShowWindow((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0 ? SW_SHOW : SW_HIDE);
	m_ctrlRadioNo.ShowWindow((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0 ? SW_SHOW : SW_HIDE);
	m_ctrlRadioSi.ShowWindow((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0 ? SW_SHOW : SW_HIDE);
	m_ctrlList.ShowWindow((((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0) && (nEseguitiPrelievi != 0)) ? SW_SHOW : SW_HIDE);
	m_ctrlButtonGruppi.ShowWindow((((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0) && (nEseguitiPrelievi != 0)) ? SW_SHOW : SW_HIDE);
	m_ctrlButtonNew.ShowWindow((((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0) && (nEseguitiPrelievi != 0)) ? SW_SHOW : SW_HIDE);
	m_ctrlButtonEdt.ShowWindow((((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0) && (nEseguitiPrelievi != 0)) ? SW_SHOW : SW_HIDE);
	m_ctrlButtonDel.ShowWindow((((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0) && (nEseguitiPrelievi != 0)) ? SW_SHOW : SW_HIDE);
	m_ctrlButtonStampaTutti.ShowWindow((((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0) && (nEseguitiPrelievi != 0)) ? SW_SHOW : SW_HIDE);

	m_ctrlListSearch.ShowWindow((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0 ? SW_HIDE : SW_SHOW);
	m_ctrlBtnNewSearch.ShowWindow((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0 ? SW_HIDE : SW_SHOW);
	m_ctrlBtnDelSearch.ShowWindow((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0 ? SW_HIDE : SW_SHOW);
	m_ctrlBtnRadioAnd.ShowWindow((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0 ? SW_HIDE : SW_SHOW);
	m_ctrlBtnRadioOr.ShowWindow((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0 ? SW_HIDE : SW_SHOW);

	m_ctrlRadioNo.EnableWindow((!(BOOL)m_wpReadOnly) && bStatoModificabile && m_bEsameOK && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetItemCount() <= 0));
	m_ctrlRadioSi.EnableWindow((!(BOOL)m_wpReadOnly) && bStatoModificabile && m_bEsameOK && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetItemCount() <= 0));
	GetDlgItem(IDC_BTN_GRUPPI)->EnableWindow((!(BOOL)m_wpReadOnly) && bStatoModificabile && m_bEsameOK && (!m_pEsamiView->m_bPazientiBusy));
	GetDlgItem(IDC_BTN_NEW)->EnableWindow((!(BOOL)m_wpReadOnly) && bStatoModificabile && m_bEsameOK && (!m_pEsamiView->m_bPazientiBusy));
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!(BOOL)m_wpReadOnly) && bStatoModificabile && m_bEsameOK && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!(BOOL)m_wpReadOnly) && bStatoModificabile && m_bEsameOK && (!m_pEsamiView->m_bPazientiBusy) && (bElimina));
	GetDlgItem(IDC_BTN_STAMPATUTTI)->EnableWindow((!(BOOL)m_wpReadOnly) && m_bEsameOK && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetItemCount() > 0));

	GetDlgItem(IDC_BTN_DEL_SEARCH)->EnableWindow((!(BOOL)m_wpReadOnly) && (bEliminaSearch));

	return 1;
}

LRESULT CAnatomiaPatologicaForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	// cerco se è stato impostato almeno un criterio di ricerca //
	if (m_ctrlListSearch.GetItemCount() > 0)
	{
		CString strTotWhere = "";

		for(int i = 0; i < m_ctrlListSearch.GetItemCount(); i++)
		{
			CString strTempWhere = "";

			// tra uno e l'altro ci metto sempre l'OR che logicamente parlando è giusto, ma nell'operatore passo o OPER_OR_SPEC (se faccio un AND) o OPER_OR (se faccio un OR) che mi considera il parametro lTable //
			ComponiRicercaNewString(pStrFrom, &strTempWhere, "AnatomiaPatologica", i, "IDEsame", "Snomed1", m_ctrlListSearch.GetItemText(i, 0), ((1 - (m_nSearchMode % 2)) * 2) + 1, MODE_UGUALE, FALSE);
			ComponiRicercaNewString(pStrFrom, &strTempWhere, "AnatomiaPatologica", i, "IDEsame", "Snomed2", m_ctrlListSearch.GetItemText(i, 0), ((1 - (m_nSearchMode % 2)) * 2) + 1, MODE_LIKE2, FALSE);
			ComponiRicercaNewString(pStrFrom, &strTempWhere, "AnatomiaPatologica", i, "IDEsame", "Snomed3", m_ctrlListSearch.GetItemText(i, 0), ((1 - (m_nSearchMode % 2)) * 2) + 1, MODE_LIKE2, FALSE);

			// concateno le singole stringhe all'interno di una più grande divisa da AND o da OR a seconda dei casi //
			strTempWhere.Trim();
			if (!strTempWhere.IsEmpty())
			{
				if (!strTotWhere.IsEmpty())
					strTotWhere += " " + strOperators[m_nSearchMode%2] + " ";

				strTotWhere += "(" + strTempWhere + ")";
			}
		}

		// unisco la stringona grande composita al WHERE generale mettendoci eventualmente un AND davanti //
		strTotWhere.Trim();
		if (!strTotWhere.IsEmpty())
		{
			if (!pStrWhere->IsEmpty())
				(*pStrWhere) += " " + strOperators[OPER_AND] + " ";

			(*pStrWhere) += "(" + strTotWhere + ")";
		}
	}

	return 1;
}

CString CAnatomiaPatologicaForm::GetField(int nSubItem)
{
	CString strReturn = "";
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nItem = m_ctrlList.GetNextSelectedItem(pos);

		if (nItem >= 0)
			strReturn = m_ctrlList.GetItemText(nItem, nSubItem);

		if ((nSubItem == 1) && (strReturn.GetLength() == 1))
			strReturn = "0" + strReturn;
	}

	return strReturn;
}


long CAnatomiaPatologicaForm::GetNumRows()
{
	return m_ctrlList.GetItemCount();
}

// Sandro 19/09/2013 // RAS 20130099 //
void CAnatomiaPatologicaForm::StampaTutteLeRighe()
{
	OnBnClickedStampaTutti();
}

void CAnatomiaPatologicaForm::OnBnClickedNewSearch()
{
	m_ctrlBtnNewSearch.SetCheck(BST_UNCHECKED);

	CAnatomiaPatologicaSearchDlg dlg(this, &m_ctrlListSearch);
	dlg.DoModal();
}

void CAnatomiaPatologicaForm::OnBnClickedDelSearch()
{
	m_ctrlBtnDelSearch.SetCheck(BST_UNCHECKED);

	POSITION pos = m_ctrlListSearch.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlListSearch.GetNextSelectedItem(pos);
		if (iCurSel >= 0)
			m_ctrlListSearch.DeleteItem(iCurSel);
	}
}