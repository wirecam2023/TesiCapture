#include "stdafx.h"
#include "Endox.h"
#include "RichiesteAnatomiaPatologicaDlg.h"
#include "MmSystem.h"

#include <io.h>

#include "AnatomiaPatologicaSet.h"
#include "CustomDate.h"
#include "DistrettiSediEsamiSet.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "IntervalloDateDlg.h"
#include "MediciSet.h"
#include "PazientiSet.h"
#include "RGL.h"
#include "RichiesteAnatomiaPatologicaEdtDlg.h"
#include "SediEsameSet.h"
#include "TipoEsameSet.h"
#include "VistaAnatomiaPatologicaRichSet.h"
#include "VistaAnatomiaPatologicaStampaSet.h"

#include "LogFileWriter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRichiesteAnatomiaPatologicaDlg, CEndoxResizableDlg)

CRichiesteAnatomiaPatologicaDlg::CRichiesteAnatomiaPatologicaDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(CRichiesteAnatomiaPatologicaDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_ctrlList.m_pEsamiView = pEsamiView;

	m_bInitializing = FALSE;
}

CRichiesteAnatomiaPatologicaDlg::~CRichiesteAnatomiaPatologicaDlg()
{
}

BEGIN_MESSAGE_MAP(CRichiesteAnatomiaPatologicaDlg, CEndoxResizableDlg)
	ON_WM_CTLCOLOR()

	ON_MESSAGE(EM_SHOW_SOSPESIISTOLOGICI_WND, OnShowSospesiIstologiciWnd)

	ON_BN_CLICKED(IDC_BTN_AGGIORNA, OnBnClickedBtnAggiorna)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_PRINT, OnBnClickedBtnStampa) // DA CANCELLARE //
	ON_BN_CLICKED(IDC_CHECK_ARCHIVIATE, OnBnClickedCheckArchiviate)
	
	ON_CBN_SELCHANGE(IDC_COMBO_SEDE, OnCbnSelchangeComboSede)
	ON_CBN_SELCHANGE(IDC_COMBO_MEDICO, OnCbnSelchangeComboMedico)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_NEW, OnLvnItemchangedList) 
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NEW, OnNMDblclkList)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_NEW, OnNMRclickListNew)

END_MESSAGE_MAP()

void CRichiesteAnatomiaPatologicaDlg::CreateModelessDialog(CWnd* pParent)
{	
	Create(CRichiesteAnatomiaPatologicaDlg::IDD, pParent);
}

void CRichiesteAnatomiaPatologicaDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_NEW, m_ctrlList);
	DDX_Control(pDX, IDC_COMBO_SEDE, m_ctrlComboSede);
	DDX_Control(pDX, IDC_COMBO_MEDICO, m_ctrlComboMedico);
	DDX_Control(pDX, IDC_CHECK_ARCHIVIATE, m_ctrlCheckArchiviate);
}

BOOL CRichiesteAnatomiaPatologicaDlg::OnInitDialog() 
{
	BOOL bReturn = CEndoxResizableDlg::OnInitDialog();

	m_bInitializing = TRUE;

	AddAnchor(IDC_CHECK_ARCHIVIATE, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_BTN_PRINT, CSize(0,0), CSize(0,0));
	AddAnchor(IDC_LIST_NEW, CSize(0,0), CSize(100,100));
	AddAnchor(IDC_BTN_EDIT, CSize(0,100), CSize(0,100));
	AddAnchor(IDOK, CSize(100,100), CSize(100,100));

	m_ctrlImageList.Create(62, 22, ILC_COLOR32, 0, 1);
	m_ctrlImageList.Add(AfxGetApp()->LoadIcon(IDI_BTN_STAMPA));

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	GetDlgItem(IDC_STATIC1)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_COMBO_SEDE)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC2)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_COMBO_MEDICO)->SetFont(&theApp.m_fontBold);

	long lIDDistretto = CDistrettiSediEsamiSet().GetIDDistretto(theApp.m_lIDSedeEsameDefault);
	if (lIDDistretto > 0)
	{
		CString strFilter;
		strFilter.Format("IDDistretto=%li", lIDDistretto);

		CDistrettiSediEsamiSet setTemp;
		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CRichiesteAnatomiaPatologicaDlg::OnInitDialog"))
		{
			int nCurr = m_ctrlComboSede.AddString("");
			m_ctrlComboSede.SetItemData(nCurr, 0);

			while(!setTemp.IsEOF())
			{
				int nCurr = m_ctrlComboSede.AddString(CSediEsameSet().GetDescrizione(setTemp.m_lIDSedeEsame, FALSE));
				m_ctrlComboSede.SetItemData(nCurr, setTemp.m_lIDSedeEsame);

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CRichiesteAnatomiaPatologicaDlg::OnInitDialog");
		}
	}

	//

	m_ctrlComboMedico.AddString(" ");

	CMediciSet setMedici;
	setMedici.SetOpenFilter("ELIMINATO=0");
	if (theApp.m_bPersonalizzazioniBrasileEinstein)
		setMedici.SetSortRecord("Nome, Cognome");
	else
		setMedici.SetSortRecord("Cognome, Nome");
	if (setMedici.OpenRecordset("CRichiesteAnatomiaPatologicaDlg::OnInitDialog"))
	{
		while(!setMedici.IsEOF())
		{
			// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
			int nCurr;
			if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
				nCurr = m_ctrlComboMedico.AddString(setMedici.m_sNome + " " + setMedici.m_sCognome);
			else
				nCurr = m_ctrlComboMedico.AddString(setMedici.m_sCognome + " " + setMedici.m_sNome);
			m_ctrlComboMedico.SetItemData(nCurr, setMedici.m_lContatore);
			setMedici.MoveNext();
		}

		setMedici.CloseRecordset("CRichiesteAnatomiaPatologicaDlg::OnInitDialog");
	}

	m_ctrlList.m_pStampaRigaFunction = StampaRiga; // DA CANCELLARE //
	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlList.SetImageList(&m_ctrlImageList, LVSIL_SMALL);
	m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(2, "Paziente", LVCFMT_LEFT, 200);
	m_ctrlList.InsertColumn(3, "Esame", LVCFMT_LEFT, 200);
	m_ctrlList.InsertColumn(4, "Medico", LVCFMT_LEFT, 130);
	m_ctrlList.InsertColumn(5, "Prov.", LVCFMT_CENTER, 150);
	m_ctrlList.InsertColumn(6, "Stato", LVCFMT_CENTER, 200);
	m_ctrlList.InsertColumn(7, "Referto", LVCFMT_CENTER, 110);
	m_ctrlList.InsertColumn(8, "Verificato", LVCFMT_CENTER, 110);
	m_ctrlList.InsertColumn(9, "Spedito/ritirato", LVCFMT_CENTER, 110);
	m_ctrlList.InsertColumn(10, "", LVCFMT_LEFT, 62);

	CString strSede = CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, FALSE);
	m_ctrlComboSede.SetCurSel(m_ctrlComboSede.FindStringExact(-1, strSede));
	OnCbnSelchangeComboSede();

	m_ctrlComboMedico.SetCurSel(-1);

	m_bInitializing = FALSE;

	RiempiLista();

	theApp.LocalizeDialog(this, CRichiesteAnatomiaPatologicaDlg::IDD, "RichiesteAnatomiaPatologicaDlg");

	return bReturn;
}

void CRichiesteAnatomiaPatologicaDlg::OnOK()
{
	m_pEsamiView->PostMessage(EM_HIDE_SOSPESIISTOLOGICI_WND);
}

void CRichiesteAnatomiaPatologicaDlg::RiempiLista()
{
	if (!m_bInitializing)
	{
		CVistaAnatomiaPatologicaRichSet setTemp;

		CString strComboSede = "";
		int nComboSede = m_ctrlComboSede.GetCurSel();
		if (nComboSede >= 0)
		{
			long lIDSedeEsame = (long)m_ctrlComboSede.GetItemData(nComboSede);
			if (lIDSedeEsame > 0)
			{
				strComboSede.Format(" AND IDSedeEsame=%li", lIDSedeEsame);
			}
			else
			{
				// prendo tutte e sole le sedi del mio distretto //
				CString strFilterTemp = "";
				for(int i = 0; i < m_ctrlComboSede.GetCount(); i++)
				{
					lIDSedeEsame = m_ctrlComboSede.GetItemData(i);
					if (lIDSedeEsame > 0)
					{
						CString strTemp;
						strTemp.Format("IDSedeEsame=%li", lIDSedeEsame);

						if (strFilterTemp.IsEmpty())
							strFilterTemp = strTemp;
						else
							strFilterTemp += " OR " + strTemp;
					}
				}

				if (!strFilterTemp.IsEmpty())
					strComboSede.Format(" AND (%s)", strFilterTemp);
			}
		}

		CString strComboMedico = "";
		int nComboMedico = m_ctrlComboMedico.GetCurSel();
		if (nComboMedico > 0)
			strComboMedico.Format(" AND Medico=%li", (long)m_ctrlComboMedico.GetItemData(nComboMedico));

		// Sandro 03/08/2015 //

		CString sFieldFilterNew = "SpeditoRitirato";
		if (theApp.m_bSospesiIstologiciNascondiVerificati)
			sFieldFilterNew = "Verificato";

		//

		CString strFilter;
		if (m_ctrlCheckArchiviate.GetCheck() == BST_CHECKED)
		{
			strFilter = "(Stato IN (0,5) OR (Stato=4 AND " + sFieldFilterNew + "<>0) OR (Stato=6 AND " + sFieldFilterNew + "<>0))" + strComboSede + strComboMedico;
		}
		else
		{
			strFilter = "(Stato IN (1,2,3) OR (Stato=4 AND " + sFieldFilterNew + "=0) OR (Stato=6 AND " + sFieldFilterNew + "=0) OR (Stato=-1 AND (SELECT COUNT(*) FROM AnatomiaPatologica WHERE Eliminato=0 and AnatomiaPatologica.IDEsame=VistaAnatomiaPatologicaRich.IDEsame) > 0))" + strComboSede + strComboMedico;
		}

		strFilter.MakeUpper();

		m_ctrlList.ShowWindow(SW_HIDE);
		m_ctrlList.DeleteAllItems();

		GetDlgItem(IDC_BTN_EDIT)->EnableWindow(FALSE);

		BeginWaitCursor();
		theApp.m_dbEndox.SetQueryTimeout(300);

		setTemp.SetOpenFilter(strFilter);

		if (setTemp.OpenRecordset("CRichiesteAnatomiaPatologicaDlg::RiempiLista"))
		{
			int nItem = 0;

			// long durata = timeGetTime();

			while(!setTemp.IsEOF())
			{
				// ricostruisco i dati del paziente //
				CCustomDate datePaziente(setTemp.m_lNatoIlCustom);

				CString strPaziente = setTemp.m_sCognome;
				strPaziente.Trim();
				if (!strPaziente.IsEmpty())
					strPaziente += " ";
				strPaziente += setTemp.m_sNome;
				strPaziente.Trim();
				strPaziente += datePaziente.GetDate(" (%d/%m/%Y)");
				strPaziente.Trim();

				// ricostruisco i dati dell'esame //
				CCustomDate dateEsame(setTemp.m_lData);
				CTipoEsameSet setTipoEsame;

				CString strEsame = dateEsame.GetDate("%d/%m/%Y - ") + setTipoEsame.GetSigla(setTemp.m_lTipoEsame);
				strEsame.Trim();
				strEsame.Replace("  ", " ");
				
				// ricostruisco i nomi dei medici //
				CMediciSet setMedici;

				CString strMedici = setMedici.GetCognomeNomeFromContatore(setTemp.m_lMedico);
				strMedici.Trim();

				///
				CString strTemp;

				strTemp.Format("%li", setTemp.m_lIDPaziente);
				m_ctrlList.InsertItem(nItem, strTemp);
				m_ctrlList.SetItemData(nItem, setTemp.m_lIDEsame);

				strTemp.Format("%li", setTemp.m_lIDEsame);
				m_ctrlList.SetItemText(nItem, 1, strTemp);

				m_ctrlList.SetItemText(nItem, 2, strPaziente);

				m_ctrlList.SetItemText(nItem, 3, strEsame);

				m_ctrlList.SetItemText(nItem, 4, strMedici);

				if (!setTemp.IsFieldNull(&setTemp.m_lProvenienza))
				{
					if (setTemp.m_lProvenienza == 0)
					{
						m_ctrlList.SetItemText(nItem, 5, setTemp.m_sProvenienza2);
					}
					else
					{
						m_ctrlList.SetItemText(nItem, 5, "Esterno");
					}
				}

				m_ctrlList.SetItemText(nItem, 6, GetStatoText(setTemp.m_lStato));

				UINT uiSpedireRitirare[3] = { IDS_ANATOMIA_SPEDIRE, IDS_ANATOMIA_SPEDIREALTRO, IDS_ANATOMIA_RITIRO};
				m_ctrlList.SetItemText(nItem, 7, theApp.GetMessageString(uiSpedireRitirare[setTemp.m_nAnatomiaSpedireRitirare % 3]));

				if (setTemp.m_bAnatomiaVerificato)
				{
					CString strTemp = theApp.GetMessageString(IDS_YES);
					if (!setTemp.IsFieldNull(&setTemp.m_sDataAnatomiaVerificato))
					{
						if (setTemp.m_sDataAnatomiaVerificato.GetLength() > 0)
							strTemp += " (" + setTemp.m_sDataAnatomiaVerificato + ")";
					}

					m_ctrlList.SetItemText(nItem, 8, strTemp);
				}
				else
				{
					m_ctrlList.SetItemText(nItem, 8, theApp.GetMessageString(IDS_NO));
				}

				if (setTemp.m_bAnatomiaSpeditoRitirato)
				{
					CString strTemp = theApp.GetMessageString(IDS_YES);

					if (!setTemp.IsFieldNull(&setTemp.m_sDataAnatomiaSpeditoRitirato))
					{
						if (setTemp.m_sDataAnatomiaSpeditoRitirato.GetLength() > 0)
							strTemp += " (" + setTemp.m_sDataAnatomiaSpeditoRitirato + ")";
					}

					m_ctrlList.SetItemText(nItem, 9, strTemp);
				}
				else
				{
					m_ctrlList.SetItemText(nItem, 9, theApp.GetMessageString(IDS_NO));
				}

				if ((setTemp.m_nAnatomiaSpedireRitirare % 3 == 0) || (setTemp.m_nAnatomiaSpedireRitirare % 3 == 1))
				{
					if (setTemp.m_lProvenienza != 0)
						m_ctrlList.SetItem(nItem, 10, LVIF_IMAGE, NULL, 0, 0, 0, 0);
				}

				/*
				// a Trento colorerei la riga di giallo per lo SCREENING... ma non ci riesco //
				if (theApp.m_bAnagrafeTrento)
				{
					//COSI DOVREBBE FUNZIONARE....
					if (setTemp.m_lTipoDegenzaEsterno == 1196)
						m_ctrlList.SetSubItemBkColor(nItem, -1, RGB(255, 255, 0));
					
				}
				*/

				// durata = timeGetTime() - durata;

				// CString log;
				// log.Format("Elaborazione record numero %li....... %li ms", nItem, durata);
				// CLogFileWriter::Get()->WriteLogLine(log);

				// durata = timeGetTime();

				nItem++;

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CRichiesteAnatomiaPatologicaDlg::RiempiLista");
		}

		theApp.m_dbEndox.SetQueryTimeout(15);
		EndWaitCursor();

		m_ctrlList.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(6, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(7, LVSCW_AUTOSIZE_USEHEADER);

		m_ctrlList.ShowWindow(SW_SHOW);
	}
}

void CRichiesteAnatomiaPatologicaDlg::OnCbnSelchangeComboSede()
{
	RiempiLista();
}

void CRichiesteAnatomiaPatologicaDlg::OnCbnSelchangeComboMedico()
{
	RiempiLista();
}

void CRichiesteAnatomiaPatologicaDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	GetDlgItem(IDC_BTN_EDIT)->EnableWindow(pos != NULL);

	if (pos != NULL)
	{
		int nCurSel = m_ctrlList.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			m_pEsamiView->RicercaCodicePaziente(atol(m_ctrlList.GetItemText(nCurSel, 0)), atol(m_ctrlList.GetItemText(nCurSel, 1)), FALSE, TRUE);
			m_pEsamiView->MovePazientiAndEsami(NULL, FALSE, TRUE);
		}
	}

	*pResult = 0;
}

void CRichiesteAnatomiaPatologicaDlg::OnBnClickedBtnEdit()
{
	CRichiesteAnatomiaPatologicaEdtDlg dlg(this, m_pEsamiView, &m_ctrlList);
	dlg.DoModal();
}

void CRichiesteAnatomiaPatologicaDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnOK();
	*pResult = 0;
}

void CRichiesteAnatomiaPatologicaDlg::OnNMRclickListNew(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedBtnEdit();
	*pResult = 0;
}

LRESULT CRichiesteAnatomiaPatologicaDlg::OnShowSospesiIstologiciWnd(WPARAM, LPARAM)
{
	ShowWindow(SW_SHOW);

	return 1;
}

void CRichiesteAnatomiaPatologicaDlg::StampaRiga(long lPaziente, long lEsame, CEsamiView* pEsamiView, BOOL bAltroIndirizzo)
{
	pEsamiView->RicercaCodicePaziente(lPaziente, lEsame, FALSE, TRUE);
	pEsamiView->MovePazientiAndEsami(NULL, FALSE, TRUE);

	long lPdfId = 0;
	if (bAltroIndirizzo)
		pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, theApp.m_sEditRep + "\\IndirizziAltro.rpa", FALSE, 1, &lPdfId,"");
	else
		pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, theApp.m_sEditRep + "\\Indirizzi.rpa", FALSE, 1, &lPdfId,"");
}

void CRichiesteAnatomiaPatologicaDlg::OnBnClickedCheckArchiviate()
{
	UpdateData(TRUE);
	RiempiLista();
}

void CRichiesteAnatomiaPatologicaDlg::OnBnClickedBtnAggiorna()
{
	UpdateData(TRUE);
	RiempiLista();
}

void CRichiesteAnatomiaPatologicaDlg::OnBnClickedBtnStampa()
{
	CIntervalloDateDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		// sede //
		CString strComboSede;
		m_ctrlComboSede.GetWindowText(strComboSede);
		strComboSede.Trim();

		// Sandro 26/03/2013 //
		CString sDateFilter = dlg.GetFilter();
		sDateFilter.Trim();

		// filtro complessivo //
		CString strFilter;
		if (sDateFilter.IsEmpty())
			strFilter.Format("SedeEsame='%s'", strComboSede);
		else
			strFilter.Format("SedeEsame='%s' AND %s", strComboSede, sDateFilter);

		CVistaAnatomiaPatologicaStampaSet setVistaASP;
		setVistaASP.SetOpenFilter(strFilter);

		if (setVistaASP.OpenRecordset("CRichiesteAnatomiaPatologicaDlg::OnBnClickedBtnStampa"))
		{
			if (!setVistaASP.IsEOF())
			{
				CString strFileRgx = theApp.m_sEditRep + "\\EsamiIstologici.rgx";
				CString strFileRgf = theApp.m_sDirProg + "\\RGL\\EsamiIstologici.rgf";

				if (_access(strFileRgx, 00) != 0)
				{
					CString strError;
					strError.Format(theApp.GetMessageString(IDS_ERROR_PRINT_RGL_2), strFileRgx);
					theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
				}
				else
				{
					CRGL rgl;
					if (rgl.Create())
					{
						int nNumero = 1;

						// data di oggi //
						SYSTEMTIME SystemTime;
						GetLocalTime(&SystemTime);	

						// titolo 1 //
						CString strTitle1 = "Richieste esami istologici";
						if (!strComboSede.IsEmpty())
							strTitle1 = strComboSede + " - " + strTitle1;

						// titolo 2 //
						CString strTitle2 = "Inviate dal " + dlg.GetDataOraIniz() + " al " + dlg.GetDataOraFine();

						// sottotitolo //
						CString strSubtitle;
						strSubtitle.Format("Stampato il %02d/%02d/%04d %02d:%02d", SystemTime.wDay, SystemTime.wMonth, SystemTime.wYear, SystemTime.wHour, SystemTime.wMinute);

						//
						rgl.Get()->SetReportName(strFileRgx);
						rgl.Get()->StartReport(strFileRgf);

						rgl.Get()->Select("", "");

							rgl.Get()->Select("IteratedPort", "TArea");

								rgl.Get()->WriteField("Title1",   COleVariant(strTitle1));
								rgl.Get()->WriteField("Title2",   COleVariant(strTitle2));
								rgl.Get()->WriteField("Subtitle", COleVariant(strSubtitle));

								while(!setVistaASP.IsEOF())
								{
									// numero //
									CString strNumero;
									strNumero.Format("%02d", nNumero);

									// cognome e nome //
									CString strCognomeNome = setVistaASP.m_sCognome + " " + setVistaASP.m_sNome;
									strCognomeNome.Trim();

									// data di nascita //
									CString strDataNascita = "";
									if (!setVistaASP.IsFieldNull(&setVistaASP.m_lDataNascita))
										strDataNascita = CCustomDate(setVistaASP.m_lDataNascita).GetDate("%d/%m/%Y");

									// data esame //
									CString strDataEsame = "";
									if (!setVistaASP.IsFieldNull(&setVistaASP.m_lDataEsame))
										strDataEsame = CCustomDate(setVistaASP.m_lDataEsame).GetDate("%d/%m %H:%M");

									// ospedale //
									CString strOspedale = "";
									if (setVistaASP.m_lProvenienza == 0) // interno //
										strOspedale = setVistaASP.m_sOspedale;

									// reparto //
									CString strReparto = "";
									if (setVistaASP.m_lProvenienza == 0) // interno //
										strReparto = setVistaASP.m_sReparto;

									// --- //

									rgl.Get()->Select("IteratedPort", "TRecord");

										rgl.Get()->WriteField("Numero", COleVariant(strNumero));
										rgl.Get()->WriteField("CognomeNome", COleVariant(strCognomeNome));
										rgl.Get()->WriteField("DataNascita", COleVariant(strDataNascita));
										rgl.Get()->WriteField("DataEsame", COleVariant(strDataEsame));
										rgl.Get()->WriteField("Ospedale", COleVariant(strOspedale));
										rgl.Get()->WriteField("Reparto", COleVariant(strReparto));

										strFilter.Format("IDEsame=%li AND Eliminato=0", setVistaASP.m_lIDEsame);

										CAnatomiaPatologicaSet setAP;
										setAP.SetOpenFilter(strFilter);

										if (setAP.OpenRecordset("CRichiesteAnatomiaPatologicaDlg::OnBnClickedBtnStampa"))
										{
											int nProgressivo = 1;

											while(!setAP.IsEOF())
											{
												// progressivo //
												CString strProgressivo;
												strProgressivo.Format("%02d", nProgressivo);

												// prelievi //
												CString strPrelievi;
												strPrelievi.Format("%li", setAP.m_lPrelievi);

												rgl.Get()->Select("IteratedPort", "TMateriale");
													rgl.Get()->WriteField("Progressivo", COleVariant(strProgressivo));
													rgl.Get()->WriteField("Codice", COleVariant(setAP.m_sIDCampione));
													rgl.Get()->WriteField("Prestazione", COleVariant(setAP.m_sIntervCodice));
													rgl.Get()->WriteField("Descrizione", COleVariant(setAP.m_sIntervProcedura));
													rgl.Get()->WriteField("Numero", COleVariant(strPrelievi));
												rgl.Get()->Back();

												nProgressivo++;
												setAP.MoveNext();
											}

											setAP.CloseRecordset("CRichiesteAnatomiaPatologicaDlg::OnBnClickedBtnStampa");
										}

									rgl.Get()->Back();

									nNumero++;
									setVistaASP.MoveNext();
								}

								rgl.Get()->Select("FooterPort", "TFooter");
								rgl.Get()->Back();

							rgl.Get()->Back();

						rgl.Get()->Back();
						rgl.ExecutePrint(strFileRgf);
					}
				}
			}

			setVistaASP.CloseRecordset("CRichiesteAnatomiaPatologicaDlg::OnBnClickedBtnStampa");
		}
	}
}