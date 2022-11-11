#include "stdafx.h"
#include "Endox.h"
#include "ListaOsservazioniDlg.h"

#include "EsamiSet.h"
#include "EsamiView.h"
#include "ListaCodificaDiagnosiEsameSet.h"
#include "ListaOsservazioniSet.h"
#include "ListaSnomedSet.h"
#include "CustomDate.h"
#include "TipoEsameSet.h"
#include "MstOrganoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CListaOsservazioniDlg::CListaOsservazioniDlg(CWnd* pParent, CEsamiView* pEsamiView, long lIDPaziente, CString sPaziente, BOOL bLanciatoDaReferto)
	: CEndoxResizableDlg(CListaOsservazioniDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_lIDPaziente = lIDPaziente;
	m_sPaziente = sPaziente;
	m_bReferto = bLanciatoDaReferto;

	m_lIDEsame = -1;
}

CListaOsservazioniDlg::~CListaOsservazioniDlg()
{
}

BEGIN_MESSAGE_MAP(CListaOsservazioniDlg, CEndoxResizableDlg)

	ON_BN_CLICKED(IDC_STAMPA, OnBnClickedStampa)
	ON_BN_CLICKED(IDC_EXPORT, OnBnClickedExport)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ESAMI, OnDblclkListEsami)

END_MESSAGE_MAP()

void CListaOsservazioniDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_ESAMI, m_ctrlListEsami);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
}

BOOL CListaOsservazioniDlg::OnInitDialog() 
{
	CEndoxResizableDlg::OnInitDialog();

	m_BtnStampa.AutoLoad(IDC_STAMPA, this);
	m_BtnExport.AutoLoad(IDC_EXPORT, this);

	AddAnchor(IDC_LIST_ESAMI, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_STAMPA, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_EXPORT, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //
	
	theApp.LocalizeDialog(this, CListaOsservazioniDlg::IDD, "ListaOsservazioniDlg");

	m_ctrlListEsami.SetExtendedStyle(m_ctrlListEsami.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	if (m_bReferto)
	{
		SetWindowText(theApp.GetMessageString(IDS_LISTAOSSERVAZIONI_TITLE_1));

		m_ctrlListEsami.InsertColumn(COL_DATAES, theApp.GetMessageString(IDS_DATA), LVCFMT_CENTER, 80);
		m_ctrlListEsami.InsertColumn(COL_TIPOES, theApp.GetMessageString(IDS_TIPOESAME), LVCFMT_LEFT, 120);
		m_ctrlListEsami.InsertColumn(COL_ORGANO, "", LVCFMT_LEFT, 0);
		m_ctrlListEsami.InsertColumn(COL_OSSERV, "", LVCFMT_LEFT, 0);

		m_BtnStampa.ShowWindow(SW_HIDE);
		m_BtnExport.ShowWindow(SW_HIDE);
	}
	else
	{
		CString strTitle;
		strTitle.Format(theApp.GetMessageString(IDS_LISTAOSSERVAZIONI_TITLE_2), m_sPaziente);
		SetWindowText(strTitle);

		m_ctrlListEsami.InsertColumn(COL_DATAES, theApp.GetMessageString(IDS_DATA), LVCFMT_CENTER, 75);
		m_ctrlListEsami.InsertColumn(COL_TIPOES, theApp.GetMessageString(IDS_TIPOESAME), LVCFMT_LEFT, 225);
		m_ctrlListEsami.InsertColumn(COL_ORGANO, theApp.GetMessageString(IDS_LISTAOSSERVAZIONI_TITLE_4), LVCFMT_LEFT, 225);
		m_ctrlListEsami.InsertColumn(COL_OSSERV, theApp.GetMessageString(IDS_LISTAOSSERVAZIONI_TITLE_3), LVCFMT_LEFT, 450);

		m_ctrlListEsami.InsertColumn(COL_SNOCOD, "", LVCFMT_LEFT, 0);
	}
	RiempiLista();

	return TRUE;
}

void CListaOsservazioniDlg::OnBnClickedExport()
{
	CString strTemp;
	GetWindowText(strTemp);

	m_ctrlListEsami.Export(strTemp);
}

void CListaOsservazioniDlg::OnBnClickedStampa()
{
	CString strTemp;
	GetWindowText(strTemp);

	m_ctrlListEsami.SetNotePiePagina(strTemp);
	m_ctrlListEsami.Print();
}

void CListaOsservazioniDlg::OnDblclkListEsami(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_bReferto)
	{
		POSITION pos = m_ctrlListEsami.GetFirstSelectedItemPosition();

		if (pos != NULL)
		{
			m_lIDEsame = m_ctrlListEsami.GetItemData(m_ctrlListEsami.GetNextSelectedItem(pos));
			OnOK();
		}
	}
	else
	{
		POSITION pos = m_ctrlListEsami.GetFirstSelectedItemPosition();

		if (pos != NULL)
		{
			m_lIDEsame = (long)m_ctrlListEsami.GetItemData(m_ctrlListEsami.GetNextSelectedItem(pos));

			if (m_lIDEsame > 0)
			{
				m_pEsamiView->MoveEsamiRecordset(ID_RECORD_FIRST);
				while(m_lIDEsame != m_pEsamiView->m_pEsamiSet->m_lContatore)
				{
					if (!m_pEsamiView->MoveEsamiRecordset(ID_RECORD_NEXT))
						break;
				}

				m_pEsamiView->OnEsamiMove(NULL);

				OnOK();
			}
		}
	}

	*pResult = 0;
}

void CListaOsservazioniDlg::RiempiLista() 
{
	if (m_bReferto)
	{
		RiempiListaReferto();
	}
	else
	{
		RiempiListaOsservazioni();
	}
}

void CListaOsservazioniDlg::RiempiListaReferto()
{
	CEsamiSet setEsami;
	CTipoEsameSet setTipiEsami;

	CString strWhere;
	strWhere.Format("PAZIENTE=%li", m_lIDPaziente);

	setEsami.SetOpenFilter(strWhere);
	setEsami.SetSortRecord("CONTATORE DESC");

	setEsami.OpenRecordset("Lista esami");

	CString strTmp;
	int nRow = 0;
	CCustomDate dataTmp;

	while(setEsami.IsEOF() == FALSE)
	{
		if (setEsami.m_lContatore != m_pEsamiView->m_pEsamiSet->m_lContatore)
		{
			dataTmp.SetDate(setEsami.m_lData);
			m_ctrlListEsami.InsertItem(nRow, dataTmp.GetDate("%d/%m/%Y"));
			m_ctrlListEsami.SetItemData(nRow, setEsami.m_lContatore);

			m_ctrlListEsami.SetItemText(nRow, COL_TIPOES, setTipiEsami.GetDescrizione(setEsami.m_lIDEsame));

			// strTmp.Format("%li", setEsami.m_lContatore);
			// m_ctrlList.SetItemText(nRow, COL_CONTES, strTmp);

			nRow++;
		}

		setEsami.MoveNext();
	}

	setEsami.CloseRecordset("Lista esami");
}

void CListaOsservazioniDlg::RiempiListaOsservazioni()
{
	CListaOsservazioniSet setOsservazioni;

	CMstOrganoSet setOrgani;

	CString strWhere;
	strWhere.Format("PAZIENTE=%li", m_lIDPaziente);

	setOsservazioni.SetOpenFilter(strWhere);
	setOsservazioni.SetSortRecord("DATA DESC, CONTATORE DESC");

	setOsservazioni.OpenRecordset("Lista osservazioni");

	if ((setOsservazioni.IsBOF()) && (setOsservazioni.IsEOF()))
	{
		setOsservazioni.CloseRecordset("Lista osservazioni");
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PRESTAZIONE_EMPTY));
		OnOK();
		return;
	}

	CString strTmp;
	CCustomDate dataTmp;
	int nIndex;
	int nRow = 0;
	long lEsamePrev = -1;

	while(!setOsservazioni.IsEOF())
	{
		if (lEsamePrev == setOsservazioni.m_lContatore)
		{
			nIndex = m_ctrlListEsami.InsertItem(nRow, "");
			m_ctrlListEsami.SetItemData(nIndex, (DWORD)setOsservazioni.m_lContatore);
		}
		else
		{
			if (lEsamePrev != -1)
			{
				nIndex = m_ctrlListEsami.InsertItem(nRow, "");
				//m_ctrlList.SetItemData(nIndex, (DWORD)setOsservazioni.m_lContatore);
				nRow++;
			}

			lEsamePrev = setOsservazioni.m_lContatore;

			dataTmp.SetDate(setOsservazioni.m_lData);
			nIndex = m_ctrlListEsami.InsertItem(nRow, dataTmp.GetDate("%d/%m/%Y"));
			m_ctrlListEsami.SetItemData(nIndex, (DWORD)setOsservazioni.m_lContatore);

			m_ctrlListEsami.SetItemText(nRow, COL_TIPOES, setOsservazioni.m_sTipoEsame);
		}

		m_ctrlListEsami.SetItemText(nRow, COL_ORGANO, setOrgani.GetFieldText(setOsservazioni.m_lOrgano) + " " + setOsservazioni.m_sSede);

		CString strOss = setOsservazioni.m_sOsservazioni;
		strOss.Replace("\r\n", theApp.m_sTestiConcatenatiSeparatore);
		m_ctrlListEsami.SetItemText(nRow, COL_OSSERV, strOss);

		nRow++;
		setOsservazioni.MoveNext();
	}

	setOsservazioni.CloseRecordset("Lista osservazioni");

	//

	for(int i = 0; i < COL_SNOCOD; i++)
		m_ctrlListEsami.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
}

void CListaOsservazioniDlg::RiempiListaDiagnosiSnomed()
{
	CMstOrganoSet setOrgani;

	CString strWhere;

	m_ctrlListEsami.DeleteAllItems();

	// mi carico in memoria tutta la lista degli esami associati al paziente corrente //

	CList<SINGOLO_ESAME> listEsami;

	CEsamiSet setEsamiTemp;
	strWhere.Format("PAZIENTE=%li", m_lIDPaziente);
	setEsamiTemp.SetOpenFilter(strWhere);
	setEsamiTemp.SetSortRecord("DATA, CONTATORE");
	if (setEsamiTemp.OpenRecordset("CListaOsservazioniDlg::RiempiListaOsservazioniSnomed"))
	{
		while(!setEsamiTemp.IsEOF())
		{
			CTipoEsameSet setTipoEsameTemp;

			SINGOLO_ESAME seTemp;
			seTemp.lID = setEsamiTemp.m_lContatore;
			seTemp.lData = setEsamiTemp.m_lData;
			seTemp.sDescrizione = setTipoEsameTemp.GetDescrizione(setEsamiTemp.m_lIDEsame);

			listEsami.AddHead(seTemp);

			setEsamiTemp.MoveNext();
		}

		setEsamiTemp.CloseRecordset("CListaOsservazioniDlg::RiempiListaOsservazioniSnomed");
	}

	// comincio a buttare dentro tutti gli esami e per ciascuno le sue eventuali diagnosi e snomed //
	if (listEsami.GetCount() > 0)
	{
		CListaCodificaDiagnosiEsameSet setDiagnosi;
		strWhere.Format("IDPAZIENTE=%li", m_lIDPaziente);
		setDiagnosi.SetOpenFilter(strWhere);
		setDiagnosi.SetSortRecord("DATA DESC, IDESAME DESC");
		if (setDiagnosi.OpenRecordset("CListaOsservazioniDlg::RiempiListaOsservazioniSnomed"))
		{
			CListaSnomedSet setSnomed;
			strWhere.Format("IDPAZIENTE=%li", m_lIDPaziente);
			setSnomed.SetOpenFilter(strWhere);
			setSnomed.SetSortRecord("DATA DESC, IDESAME DESC");
			if (setSnomed.OpenRecordset("CListaOsservazioniDlg::RiempiListaOsservazioniSnomed"))
			{
				int nItem = -1;

				for(int i = 0; i < listEsami.GetCount(); i++)
				{
					SINGOLO_ESAME seTemp = listEsami.GetAt(listEsami.FindIndex(i));

					// inserisco due righe vuote tra un esame e l'altro //
					if (i > 0)
					{
						CString strSeparator = ""; // "---------------";

						nItem++;
						m_ctrlListEsami.InsertItem(nItem, strSeparator);

						m_ctrlListEsami.SetItemText(nItem, COL_TIPOES, strSeparator);
						m_ctrlListEsami.SetItemText(nItem, COL_ORGANO, strSeparator);
						m_ctrlListEsami.SetItemText(nItem, COL_OSSERV, strSeparator);
						m_ctrlListEsami.SetItemText(nItem, COL_SNOCOD, strSeparator);
						m_ctrlListEsami.SetItemText(nItem, COL_SNODES, strSeparator);
					}

					// inserisco la riga dell'esame //
					CCustomDate dataTmp;
					dataTmp.SetDate(seTemp.lData);
					nItem++;
					m_ctrlListEsami.InsertItem(nItem, dataTmp.GetDate("%d/%m/%Y"));
					m_ctrlListEsami.SetItemData(nItem, seTemp.lID);
					m_ctrlListEsami.SetItemText(nItem, COL_TIPOES, seTemp.sDescrizione);

					// inserisco le righe dell diagnosi e dello snomed //
					InsertDiagnosiSnomed(seTemp.lID, &setDiagnosi, &setSnomed, nItem);
				}

				setSnomed.CloseRecordset("CListaOsservazioniDlg::RiempiListaOsservazioniSnomed");
			}

			setDiagnosi.CloseRecordset("CListaOsservazioniDlg::RiempiListaOsservazioniSnomed");
		}

		for(int i = 0; i < COL_LASTEM; i++)
			m_ctrlListEsami.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_LISTAESAMI_EMPTY));
		OnOK();
		return;
	}
}

void CListaOsservazioniDlg::InsertDiagnosiSnomed(long lIDEsame, CListaCodificaDiagnosiEsameSet* pDia, CListaSnomedSet* pSno, int& nItem)
{
	BOOL bFirst = TRUE;

	while(((!pDia->IsEOF()) && (pDia->m_lIDEsame == lIDEsame)) && ((!pSno->IsEOF()) && (pSno->m_lIDEsame == lIDEsame)))
	{
		if (bFirst)
		{
			bFirst = FALSE;
		}
		else
		{
			nItem++;
			m_ctrlListEsami.InsertItem(nItem, "");
			m_ctrlListEsami.SetItemData(nItem, lIDEsame);
		}

		CMstOrganoSet setOrgani;
		m_ctrlListEsami.SetItemText(nItem, COL_ORGANO, pDia->m_sOrgano + " " + pDia->m_sSede);

		CString strOss = pDia->m_sDiagnosi;
		strOss.Replace("\r\n", theApp.m_sTestiConcatenatiSeparatore);
		m_ctrlListEsami.SetItemText(nItem, COL_OSSERV, strOss);

		m_ctrlListEsami.SetItemText(nItem, COL_SNOCOD, pSno->m_sCodici);
		m_ctrlListEsami.SetItemText(nItem, COL_SNODES, pSno->m_sDescrizioni);

		pDia->MoveNext();
		pSno->MoveNext();
	}

	while((!pDia->IsEOF()) && (pDia->m_lIDEsame == lIDEsame))
	{
		if (bFirst)
		{
			bFirst = FALSE;
		}
		else
		{
			nItem++;
			m_ctrlListEsami.InsertItem(nItem, "");
			m_ctrlListEsami.SetItemData(nItem, lIDEsame);
		}

		CMstOrganoSet setOrgani;
		m_ctrlListEsami.SetItemText(nItem, COL_ORGANO, pDia->m_sOrgano + " " + pDia->m_sSede);

		CString strOss = pDia->m_sDiagnosi;
		strOss.Replace("\r\n", theApp.m_sTestiConcatenatiSeparatore);
		m_ctrlListEsami.SetItemText(nItem, COL_OSSERV, strOss);

		m_ctrlListEsami.SetItemText(nItem, COL_SNOCOD, "");
		m_ctrlListEsami.SetItemText(nItem, COL_SNODES, "");

		pDia->MoveNext();
	}

	while((!pSno->IsEOF()) && (pSno->m_lIDEsame == lIDEsame))
	{
		if (bFirst)
		{
			bFirst = FALSE;
		}
		else
		{
			nItem++;
			m_ctrlListEsami.InsertItem(nItem, "");
			m_ctrlListEsami.SetItemData(nItem, lIDEsame);
		}

		m_ctrlListEsami.SetItemText(nItem, COL_ORGANO, "");
		m_ctrlListEsami.SetItemText(nItem, COL_OSSERV, "");

		m_ctrlListEsami.SetItemText(nItem, COL_SNOCOD, pSno->m_sCodici);
		m_ctrlListEsami.SetItemText(nItem, COL_SNODES, pSno->m_sDescrizioni);

		pSno->MoveNext();
	}
}

long CListaOsservazioniDlg::GetIDEsame()
{
	return m_lIDEsame;
}