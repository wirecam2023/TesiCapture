#include "stdafx.h"
#include "Endox.h"
#include "QueryDlg.h"

#include <math.h>

#include "DLL_Imaging\h\AmLogin.h"

#include "AnatomiaPatologicaForm.h"
#include "IstologiaTotForm.h"
#include "CaricaReport.h"
#include "CodificaDiagnosiEsameForm.h"
#include "ComboAltreAnomalieSet.h"
#include "ComboBoxSet.h"
#include "ComboCauseNonCompletamentoSet.h"
#include "ComboComplicanzeSet.h"
#include "ComboConclusioniColonSet.h"
#include "ComboConclusioniScreeningSet.h"
#include "ComboDiagnosiFinaleSet.h"
#include "ComboPuliziaSet.h"
#include "ComboTolleranzaSet.h"
#include "ComuniSet.h"
#include "CustomDate.h"
#include "ElemReportSet.h"
#include "EsamiView.h"
#include "ExportCSV.h"
#include "ExportExcel.h"
#include "ExportFileDlg.h"
#include "ExportHtml.h"
#include "ExportWaitDlg.h"
#include "FieldDlg.h"
#include "InfermieriSet.h"
#include "InviantiSet.h"
#include "IstologiaSet.h"
#include "IstologiaTotForm5Righe.h"
#include "IstologiaTotForm5RighePlus.h"
#include "JoinEsamiSet.h"
#include "MalattieSet.h"
#include "MediciSet.h"
#include "ModelessDlg.h"
#include "MosaicDlg.h"
#include "RegioneSet.h"
#include "SediEsameSet.h"
#include "StudiSet.h"
#include "TipoEsameSet.h"
#include "UnificazioneAnagraficheDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CQueryDlg::CQueryDlg(CEsamiView* pEsamiView, BOOL bVerifyDuplicated, CString strTitle, BOOL bModale, BOOL bSoloRicerca, BOOL bMostraTastoUnificazione)
	: CResizableDialog(CQueryDlg::IDD, (CWnd*)pEsamiView)
{
	ASSERT(pEsamiView != NULL);

	m_strTitolo = "";
	m_lTotale = 0;
	m_StrAssociato = "";
	m_StrPrincipale = "";

	m_pEsamiView = pEsamiView;
	m_bVerifyDuplicated = bVerifyDuplicated;

	m_pPazientiSet = NULL;
	m_pJoinEsamiSet = NULL;

	m_strPazFilter = "";
	m_strEsameFrom = "";
	m_strEsameWhere = "";
	m_lRelazione = PAZIENTI_ESAMI;
	m_lCurrentPri = 0;
	m_lCurrentSec = 0;

	m_bCercaPaziente = FALSE;

	m_pEsamiSet = m_pEsamiView->m_pEsamiSet;

	m_bAddNew = FALSE;

	m_nCurExam = 0;
	m_nTotExam = 0;

	m_pReportElemSet = NULL;

	m_strTitle = strTitle;

	m_bModale = bModale;
	m_bSoloRicerca = bSoloRicerca;

	m_bMostraTastoUnificazione = bMostraTastoUnificazione;
}

CQueryDlg::~CQueryDlg()
{
	m_EsamiSet.CloseRecordset("CQueryDlg::~CQueryDlg");

	if (!m_bVerifyDuplicated)
	{
		if (m_pPazientiSet)
			delete m_pPazientiSet;

		if (m_pJoinEsamiSet)
			delete m_pJoinEsamiSet;

		m_pPazientiSet = NULL;
		m_pJoinEsamiSet = NULL;
	}

	if (m_pReportElemSet)
		delete m_pReportElemSet;	
}

void CQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STR_PRINCIPALE, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STR_PRINCIPALE2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_PRINCIPALE, m_ctrlPrincipale);

	DDX_Control(pDX, IDC_STR_STORICO, m_ctrlStaticStorico);
	
	DDX_Control(pDX, IDC_EXAM_1, m_ctrlStatic3);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDC_NEW, m_ctrlButtonNew);

	DDX_Control(pDX, IDC_LIST, m_ctrlLista);
	DDX_Control(pDX, IDC_LIST_ESAMI, m_ctrlListEsami);
	DDX_Control(pDX, IDC_LIST_STORICO, m_ctrlListaStorico);
	DDX_Control(pDX, IDC_BTN_UNIFICAZIONEANAGRAFICHE, m_ctrlBtnUnificazioneAnagrafiche);

	DDX_Text(pDX, IDC_TITOLO, m_strTitolo);
	DDX_Text(pDX, IDC_ASSOCIATO, m_StrAssociato);
	DDX_Text(pDX, IDC_PRINCIPALE, m_StrPrincipale);

	BOOL bEnablePrev = FALSE;
	BOOL bEnableNext = FALSE;
	CString strTemp;

	if ((m_pJoinEsamiSet != NULL) && (m_pJoinEsamiSet->IsOpen() == TRUE))
	{
		if ((m_pJoinEsamiSet->IsBOF() == FALSE) && (m_pJoinEsamiSet->IsEOF() == FALSE))
		{
			m_pJoinEsamiSet->MovePrev();
			if (m_pJoinEsamiSet->IsBOF() == TRUE)
			{
				m_pJoinEsamiSet->MoveFirst();
			}
			else
			{
				bEnablePrev = TRUE;

				m_pJoinEsamiSet->MoveNext();
			}

			m_pJoinEsamiSet->MoveNext();
			if (m_pJoinEsamiSet->IsEOF() == TRUE)
			{
				m_pJoinEsamiSet->MoveLast();
			}
			else
			{
				bEnableNext = TRUE;

				m_pJoinEsamiSet->MovePrev();
			}
		}
	}

	GetDlgItem(IDC_PREV)->EnableWindow(bEnablePrev);
	GetDlgItem(IDC_NEXT)->EnableWindow(bEnableNext);

	strTemp.Format("%d %s %d", m_nCurExam, theApp.GetMessageString(IDS_DI), m_nTotExam);
	SetDlgItemText(IDC_EXAM_2, strTemp);
}

BEGIN_MESSAGE_MAP(CQueryDlg, CResizableDialog)

	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_ALBUM, OnAlbum)
	ON_BN_CLICKED(IDC_STAMPA, OnStampa)
	ON_BN_CLICKED(IDC_REPORT, OnReport)
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	ON_BN_CLICKED(IDC_BTN_UNIFICAZIONEANAGRAFICHE, OnBnClickedBtnUnificazioneanagrafiche)

	ON_LBN_DBLCLK(IDC_LIST, OnOK)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelChangeLista)

	ON_MESSAGE(EM_SHOW_QUERY_WND, OnShowQueryWnd)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ESAMI, OnLvnItemChangedListEsami)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ESAMI, OnNMDblClkListEsami)

	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()

END_MESSAGE_MAP()


void CQueryDlg::CreateModelessDialog(CWnd* pParent)
{	
	Create(CQueryDlg::IDD, pParent);
}

void CQueryDlg::SelectListRow(long lRowNum)
{
	m_lCurrentPri = (long)m_ctrlLista.GetItemData(lRowNum);
	RiempiListeDati();
}

void CQueryDlg::RiempiListaQuery()
{
	m_lTotale = 0;

	m_ctrlBtnUnificazioneAnagrafiche.ShowWindow(SW_HIDE);

	switch(m_lRelazione)
	{
		case SOLO_PAZIENTI:
		{
			BOOL bTrovatiOmonimi = FALSE;

			if (m_pPazientiSet->IsOpen())
			{
				CString strSezione;
				int nPosInList = 0;

				MSG msg;
				CModelessDlg dlg(m_pEsamiView, IDS_MODELESS_TITLE_4);

				dlg.CreateModeless(m_pEsamiView);

				CString sCognPrev = "";
				CString sNomePrev = "";

				while(!m_pPazientiSet->IsEOF())
				{
					if (theApp.m_bMostraSecondoCognome)
					{
						m_pPazientiSet->m_sCognome.Trim();
						m_pPazientiSet->m_sCognome2.Trim();

						m_pPazientiSet->m_sCognome += " " + m_pPazientiSet->m_sCognome2;

						m_pPazientiSet->m_sCognome.Trim();
					}

					if (!bTrovatiOmonimi)
					{
						if ((m_pPazientiSet->m_sCognome.CompareNoCase(sCognPrev) == 0) && (m_pPazientiSet->m_sNome.CompareNoCase(sNomePrev) == 0))
						{
							bTrovatiOmonimi = TRUE;
						}
						else
						{
							sCognPrev = m_pPazientiSet->m_sCognome;
							sNomePrev = m_pPazientiSet->m_sNome;
						}
					}

					if (!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lNatoIlCustom) && (m_pPazientiSet->m_lNatoIlCustom > 0))
					{
						CCustomDate dateTemp;
						dateTemp.SetDate(m_pPazientiSet->m_lNatoIlCustom);
						strSezione = m_pPazientiSet->m_sCognome + " " + m_pPazientiSet->m_sNome + " (" + dateTemp.GetDate("%d/%m/%Y") + ")";
					}
					else
					{
						strSezione = m_pPazientiSet->m_sCognome + " " + m_pPazientiSet->m_sNome;
					}
						
					//m_ctrlLista.InsertString(nPosInList, strSezione);
					if (theApp.m_bDisabilitaEsamiPazientiSenzaAssiden && (m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_sAssIden) || m_pPazientiSet->m_sAssIden == ""))
						m_ctrlLista.InsertString(nPosInList, strSezione, RGB(255,0,0), RGB(255,255,255));
					else
						m_ctrlLista.InsertString(nPosInList, strSezione);

					if ((m_ctrlLista.SetItemData(nPosInList, (DWORD)m_pPazientiSet->m_lContatore)) == LB_ERR)
					{
						m_ctrlLista.DeleteString(nPosInList);
		        	
						break;
					}
					else
					{
						m_lTotale++;
					}
		
					while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}

					if (dlg.m_bStop)
						break;

					m_pPazientiSet->MoveNext();
					nPosInList++;
				}

				dlg.DestroyWindow();

				if (m_lTotale > 0)
				{
					m_ctrlLista.SetCurSel(0);
					m_lCurrentPri = (long)m_ctrlLista.GetItemData(0);
				}
			}

			m_ctrlBtnUnificazioneAnagrafiche.ShowWindow(theApp.m_bMostraTastoUnificazioneAnagrafiche && m_bMostraTastoUnificazione && bTrovatiOmonimi ? SW_SHOW : SW_HIDE);
			break;
		}
		case PAZIENTI_ESAMI:
		case SOLO_ESAMI:
		{
			if (m_pJoinEsamiSet->IsOpen())
			{
				CModelessDlg dlg(m_pEsamiView, IDS_MODELESS_TITLE_3);
				dlg.CreateModeless(m_pEsamiView);

				while(!m_pJoinEsamiSet->IsEOF())
				{
					CString strFiltro;
					strFiltro.Format("Contatore=%li", m_pJoinEsamiSet->m_lPaziente);

					if (!m_strPazFilter.IsEmpty())
						strFiltro += " AND " + m_strPazFilter;

					BOOL bError = FALSE;
					if (m_pPazientiSet->RecordsetReOpen(bError, strFiltro, "", "CQueryDlg::RiempiListaQuery"))
					{
						CString strSezione = m_pPazientiSet->m_sCognome + " " + m_pPazientiSet->m_sNome;

						if (!m_pJoinEsamiSet->IsFieldNull(&m_pJoinEsamiSet->m_lData) && (m_pJoinEsamiSet->m_lData != 0))
							strSezione += CCustomDate(m_pJoinEsamiSet->m_lData).GetDate(" (" + theApp.GetMessageString(IDS_ESAME_DEL) + " %d/%m/%y %H:%M)");
				
						int nPosInList = m_ctrlLista.AddString(strSezione);
						if (nPosInList >= 0)
						{
							if ((m_ctrlLista.SetItemData(nPosInList, (DWORD)m_pJoinEsamiSet->m_lEsame)) == LB_ERR)
							{
								m_ctrlLista.DeleteString(nPosInList);
								nPosInList = -1;
							}
						}
		
						if (nPosInList >= 0)
						{
							m_lTotale++;
							dlg.SetInfo(strSezione);
						}
						else
						{
							break;
						}
					}

					MSG msg;
					while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
	
					if (dlg.m_bStop)
						break;
				
					m_pJoinEsamiSet->MoveNext();
				}
		
		  		dlg.DestroyWindow();

				if (m_lTotale)
				{
					m_ctrlLista.SetCurSel(0);
					m_lCurrentPri = (long)m_ctrlLista.GetItemData(0);
				}
			}

			break;
		}
		case PAZIENTI_ESAMI_ONLYPATIENTS:
		case SOLO_ESAMI_ONLYPATIENTS:
		{
			if (m_pJoinEsamiSet->IsOpen())
			{
				CModelessDlg dlg(m_pEsamiView, IDS_MODELESS_TITLE_4);
				dlg.CreateModeless(m_pEsamiView);

				CList<itemlistapazienti> xList;
				while(!m_pJoinEsamiSet->IsEOF())
				{
					BOOL bAlreadyPresent = FALSE;
					POSITION pos = xList.GetHeadPosition();
					while(pos != NULL)
					{
						if (xList.GetAt(pos).lID == m_pJoinEsamiSet->m_lPaziente)
						{
							bAlreadyPresent = TRUE;
							break;
						}

						xList.GetNext(pos);
					}

					if (!bAlreadyPresent)
					{
						CString strFiltro;
						strFiltro.Format("Contatore=%li", m_pJoinEsamiSet->m_lPaziente);

						if (!m_strPazFilter.IsEmpty())
							strFiltro += " AND " + m_strPazFilter;

						BOOL bError = FALSE;
						if (m_pPazientiSet->RecordsetReOpen(bError, strFiltro, "", "CQueryDlg::RiempiListaQuery"))
						{
							dlg.SetInfo(m_pPazientiSet->m_sCognome + " " + m_pPazientiSet->m_sNome);

							itemlistapazienti itemTemp;
							itemTemp.lID = m_pPazientiSet->m_lContatore;
							itemTemp.sCognome = m_pPazientiSet->m_sCognome;
							itemTemp.sNome = m_pPazientiSet->m_sNome;
							itemTemp.lDataNascita = (m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lNatoIlCustom) ? 0 : m_pPazientiSet->m_lNatoIlCustom);

							switch(xList.GetCount())
							{
								case 0:
								{
									xList.AddHead(itemTemp);

									break;
								}
								case 1:
								{
									itemlistapazienti itemFirst = xList.GetHead();
									if (IsBefore(&itemTemp, &itemFirst))
										xList.AddHead(itemTemp);
									else
										xList.AddTail(itemTemp);

									break;
								}
								default:
								{
									itemlistapazienti itemFirst = xList.GetHead();
									if (IsBefore(&itemTemp, &itemFirst))
									{
										// aggiungo in testa //
										xList.AddHead(itemTemp);
									}
									else
									{
										itemlistapazienti itemLast = xList.GetTail();
										if (IsAfter(&itemTemp, &itemLast))
										{
											// aggiungo in coda //
											xList.AddTail(itemTemp);
										}
										else
										{
											POSITION pos1 = xList.GetHeadPosition();
											POSITION pos2 = xList.GetHeadPosition();
											xList.GetNext(pos2);

											while((pos1 != NULL) && (pos2 != NULL))
											{
												itemlistapazienti item1 = xList.GetAt(pos1);
												itemlistapazienti item2 = xList.GetAt(pos2);

												if (IsAfter(&itemTemp, &item1) && IsBefore(&itemTemp, &item2))
												{
													// aggiungo in mezzo //
													xList.InsertAfter(pos1, itemTemp);

													break;
												}

												xList.GetNext(pos1);
												xList.GetNext(pos2);
											}
										}
									}

									break;
								}
							}
						}
					}

					MSG msg;
					while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
	
					if (dlg.m_bStop)
						break;
				
					m_pJoinEsamiSet->MoveNext();
				}

				POSITION pos = xList.GetHeadPosition();
				while(pos != NULL)
				{
					itemlistapazienti item = xList.GetAt(pos);

					CString sSezione = item.sCognome + " " + item.sNome;
					if (item.lDataNascita > 0)
						sSezione += " (" + CCustomDate(item.lDataNascita).GetDate("%d/%m/%Y") + ")";

					m_ctrlLista.InsertString(m_lTotale, sSezione);
					m_ctrlLista.SetItemData(m_lTotale, (DWORD)item.lID);

					dlg.SetInfo(sSezione);

					m_lTotale++;
					xList.GetNext(pos);
				}
		
		  		dlg.DestroyWindow();

				xList.RemoveAll();

				if (m_lTotale)
				{
					m_ctrlLista.SetCurSel(0);
					m_lCurrentPri = (long)m_ctrlLista.GetItemData(0);
				}
			}

			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}

	for(int i = 0; i < m_lTotale; i++)
	{
		DWORD nCodice = m_ctrlLista.GetItemData(i);
		m_ArrayCode.Add(nCodice);
	}
    
	UpdateData (FALSE);
}

void CQueryDlg::FiltraPazienti()
{
	BOOL bError;
	CString	strFiltro;

	switch(m_lRelazione)
	{
		case SOLO_PAZIENTI:
		{
			strFiltro.Format("Contatore=%li", m_lCurrentPri);
			break;
		}
		case PAZIENTI_ESAMI:
		case SOLO_ESAMI:
		{
			strFiltro.Format("Contatore=%li", m_lCurrentSec);
			break;
		}
		case PAZIENTI_ESAMI_ONLYPATIENTS:
		case SOLO_ESAMI_ONLYPATIENTS:
		{
			strFiltro.Format("Contatore=%li", m_lCurrentPri);
			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}

	if (m_pPazientiSet->RecordsetReOpen(bError, strFiltro, "", "CQueryDlg::FiltraPazienti"))
	{
		switch(m_lRelazione)
		{
			case SOLO_PAZIENTI:
			{
				break;
			}
			case PAZIENTI_ESAMI:
			case SOLO_ESAMI:
			{
				m_lCurrentSec = m_pPazientiSet->m_lContatore;
				break;
			}
			case PAZIENTI_ESAMI_ONLYPATIENTS:
			case SOLO_ESAMI_ONLYPATIENTS:
			{
				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
			}
		}
	}
	else
	{
		m_lCurrentSec = 0;
	}
}

void CQueryDlg::FiltraEsami()
{
	CString strFiltro;
	long* pContatore = NULL;
	long* pPaziente = NULL;

	switch(m_lRelazione)
	{
		case SOLO_PAZIENTI:
		{
			strFiltro.Format("EESAMI.PAZIENTE=%li", m_lCurrentPri);

			pContatore = &m_pJoinEsamiSet->m_lEsame;
			pPaziente = NULL;

			// Sandro 03/09/2013 //
			CString strUO;
			strUO.Format("EESAMI.UO=%li", theApp.m_lUO);
			if (strFiltro.IsEmpty())
			{
				strFiltro = "EESAMI.RECORDSENZAACCESSO=0 AND " + strUO + " AND EESAMI.ELIMINATO=0";
			}
			else
			{
				if (strFiltro.Find("EESAMI.RECORDSENZAACCESSO") < 0)
					strFiltro += " AND EESAMI.RECORDSENZAACCESSO=0";

				if (strFiltro.Find("EESAMI.UO") < 0)
					strFiltro += " AND " + strUO;

				if (strFiltro.Find("EESAMI.ELIMINATO") < 0)
					strFiltro += " AND EESAMI.ELIMINATO=0";
			}

			break;
		}
		case PAZIENTI_ESAMI:
		case SOLO_ESAMI:
		{
			strFiltro.Format("EEsami.Contatore=%li", m_lCurrentPri);

			pContatore = NULL;
			pPaziente = &m_pJoinEsamiSet->m_lPaziente;

			if (!m_strEsameWhere.IsEmpty())
				strFiltro += " AND " + m_strEsameWhere;

			break;
		}
		case PAZIENTI_ESAMI_ONLYPATIENTS:
		case SOLO_ESAMI_ONLYPATIENTS:
		{
			strFiltro.Format("EESAMI.PAZIENTE=%li", m_lCurrentPri);

			pContatore = &m_pJoinEsamiSet->m_lEsame;
			pPaziente = NULL;

			// Sandro 29/08/2013 // RAS 20130121 //
			// mettendo questo, nella QueryDlg compaiono solo gli esami che rispondono al criterio di ricerca impostato //
			// togliendo questo (commentandolo), nella QueryDlg comparirebbero tutti gli esami del paziente senza ulteriori filtri //
			if (!m_strEsameWhere.IsEmpty())
				strFiltro += " AND " + m_strEsameWhere;

			// Sandro 03/09/2013 //
			CString strUO;
			strUO.Format("EESAMI.UO=%li", theApp.m_lUO);
			if (strFiltro.IsEmpty())
			{
				strFiltro = "EESAMI.RECORDSENZAACCESSO=0 AND " + strUO + " AND EESAMI.ELIMINATO=0";
			}
			else
			{
				if (strFiltro.Find("EESAMI.RECORDSENZAACCESSO") < 0)
					strFiltro += " AND EESAMI.RECORDSENZAACCESSO=0";

				if (strFiltro.Find("EESAMI.UO") < 0)
					strFiltro += " AND " + strUO;

				if (strFiltro.Find("EESAMI.ELIMINATO") < 0)
					strFiltro += " AND EESAMI.ELIMINATO=0";
			}

			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}

	m_lCurrentSec = 0;
	m_nCurExam = 0;
	m_nTotExam = 0;

	if (m_pJoinEsamiSet != NULL)
	{
		m_pJoinEsamiSet->CloseRecordset("CQueryDlg::FiltraEsami");
		m_pJoinEsamiSet->SetFromWhere(m_strEsameFrom, strFiltro);
		m_pJoinEsamiSet->SetSortRecord("EEsami.Data, EEsami.Contatore"); // Sandro 23/05/2013 // impongo lo stesso ordine degli esami nell'interfaccia principale //
		m_pJoinEsamiSet->OpenRecordset("CQueryDlg::FiltraEsami");

		m_nTotExam = 0;
		while(m_pJoinEsamiSet->IsEOF() == FALSE)
		{
			m_pJoinEsamiSet->MoveNext();
			m_nTotExam++;
		}
		m_nCurExam = m_nTotExam;

		if (m_nTotExam > 0)
			m_pJoinEsamiSet->MoveLast();

		FiltraSubEsami();
	
		if (pPaziente)
		{
			m_lCurrentSec = *pPaziente;
		}
		else
		{
			if (m_nTotExam > 0)
				m_lCurrentSec = *pContatore;
		}
	}
}

void CQueryDlg::FiltraSubEsami()
{
	if (m_pJoinEsamiSet->IsOpen() && !m_pJoinEsamiSet->IsEOF())
	{
		BOOL	bError;
		CString	strFiltro;

		strFiltro.Format("Contatore=%li", m_pJoinEsamiSet->m_lEsame);

		m_EsamiSet.RecordsetReOpen(bError, strFiltro, "", "CQueryDlg::FiltraSubEsami");
	}
}

void CQueryDlg::MostraDatiPaziente(CString* pStrEdit)
{
	*pStrEdit = "";
	
	if ((m_pPazientiSet != NULL) && (m_pPazientiSet->IsOpen()))
	{
		if (!m_pPazientiSet->IsBOF() && !m_pPazientiSet->IsEOF())
		{
			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sCognome,		theApp.GetMessageString(IDS_QUERYDLG_PATIENT_01),	"\r\n");
			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sNome,			theApp.GetMessageString(IDS_QUERYDLG_PATIENT_02),	"\r\n");
			MakeStringDate	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_lNatoIlCustom,	theApp.GetMessageString(IDS_QUERYDLG_PATIENT_06),	"\r\n");
			MakeStringSesso	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_lSessoPaz,		theApp.GetMessageString(IDS_QUERYDLG_PATIENT_05),	"\r\n");
			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sNatoA,			theApp.GetMessageString(IDS_QUERYDLG_PATIENT_07),	"\r\n");
			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sCodFisc,		theApp.GetMessageString(IDS_QUERYDLG_PATIENT_03),	"\r\n");
			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sCodSanit,		theApp.GetMessageString(IDS_QUERYDLG_PATIENT_04),	"\r\n");

			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sVia,			theApp.GetMessageString(IDS_QUERYDLG_PATIENT_08),	"\r\n");
			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sCitta,			theApp.GetMessageString(IDS_QUERYDLG_PATIENT_09),	"\r\n");
			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sCAP,			theApp.GetMessageString(IDS_QUERYDLG_PATIENT_10),	"\r\n");
			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sProvincia,		theApp.GetMessageString(IDS_QUERYDLG_PATIENT_11),	"\r\n");
			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sTelefono1,		theApp.GetMessageString(IDS_QUERYDLG_PATIENT_12),	"\r\n");
			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sTelefono2,		theApp.GetMessageString(IDS_QUERYDLG_PATIENT_13),	"\r\n");
			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sCellulare1,		theApp.GetMessageString(IDS_QUERYDLG_PATIENT_15),	"\r\n");
			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sCellulare2,		theApp.GetMessageString(IDS_QUERYDLG_PATIENT_16),	"\r\n");

			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sMedicoCurante,	theApp.GetMessageString(IDS_QUERYDLG_PATIENT_22),	"\r\n");

			MakeStringText	(*pStrEdit, m_pPazientiSet, &m_pPazientiSet->m_sDenSegnalato,	theApp.GetMessageString(IDS_QUERYDLG_PATIENT_21),	"\r\n");
		}
	}
}

void CQueryDlg::MostraDatiEsame(CString* pStrEdit)
{
	if (m_lCurrentSec == 0 || !m_EsamiSet.IsOpen())
	{
		*pStrEdit = "";

		return;
	}

	CString strScore('_', 18);
	CString strLabel[NUM_LABEL_TESTO];

	*pStrEdit = "";

	for(int i = 0; i < NUM_LABEL_TESTO; i++)
	{
		int j;

		strLabel[i] = theApp.m_sLabelText[i];

		for(j = strLabel[i].GetLength() - 1; j >= 0; j--)
			if (strLabel[i].GetAt(j) != ' ' && strLabel[i].GetAt(j) != ':')
				break;

		j = min(18, j + 1);

		strLabel[i] = strLabel[i].Left(j);
		strLabel[i] += strScore.Left(18 - strLabel[i].GetLength()) + CString(": ");
	}
	
	if (!m_EsamiSet.IsBOF() && !m_EsamiSet.IsEOF())
	{
		MakeStringIdEsame	(*pStrEdit,	&m_EsamiSet, &m_EsamiSet.m_lIDEsame,		"",						"");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_lContatore,		theApp.GetMessageString(IDS_QUERYDLG_EXAM_02),	"] ");
		MakeStringDate		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_lData, 			theApp.GetMessageString(IDS_QUERYDLG_EXAM_03),	"\r\n");
		MakeStringMedico	(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_lMedico, 		theApp.GetMessageString(IDS_QUERYDLG_EXAM_04),	"\t");
		MakeStringMedico	(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_lAssistente, 	"",												"\r\n");
		MakeStringInfermiere(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_lInfermiere1,	"",												"\r\n");
		MakeStringInfermiere(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_lInfermiere2,	"",												"\r\n");
		
		MakeStringText (*pStrEdit, "",	"\r\n");

		if ((m_EsamiSet.IsFieldNull(&m_EsamiSet.m_lProvenienza) == FALSE) && ((m_EsamiSet.m_lProvenienza == 0) || (m_EsamiSet.m_lProvenienza == 1)))
		{
			MakeStringProvenienza(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_lProvenienza, theApp.GetMessageString(IDS_QUERYDLG_EXAM_05), "\r\n");
			MakeStringInviatoDa(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_lInviante, theApp.GetMessageString(IDS_QUERYDLG_EXAM_06), "\r\n", m_EsamiSet.m_lProvenienza);
			MakeStringText(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_lCamera, theApp.GetMessageString(IDS_QUERYDLG_EXAM_40), "\r\n");
		}
		
		MakeStringText			(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sInvMedico,	theApp.GetMessageString(IDS_QUERYDLG_EXAM_07),	"\r\n");

		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sIndicazioni,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_08),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sFarmacoTrial,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_09),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sStudio,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_10),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sTipoVisita,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_11),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sPremedicazioni,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_13),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sStrumenti,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_14),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sAccessori,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_15),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sValutazione,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_16),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sComplicanzeOld,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_17),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sComplicanze1,	theApp.GetMessageString(IDS_QUERYDLG_EXAM_18),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sComplicanze2,	theApp.GetMessageString(IDS_QUERYDLG_EXAM_19),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sComplicanze3,	theApp.GetMessageString(IDS_QUERYDLG_EXAM_20),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sGuarigione,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_21),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sQuadro,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_22),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto000,			strLabel[0],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto001,			strLabel[1],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto002,			strLabel[2],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto003,			strLabel[3],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto004,			strLabel[4],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto005,			strLabel[5],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto006,			strLabel[6],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto007,			strLabel[7],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto008,			strLabel[8],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto009,			strLabel[9],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto010,			strLabel[10],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto011,			strLabel[11],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto012,			strLabel[12],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto013,			strLabel[13],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto014,			strLabel[14],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto015,			strLabel[15],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto016,			strLabel[16],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto017,			strLabel[17],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto018,			strLabel[18],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto019,			strLabel[19],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto020,			strLabel[20],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto021,			strLabel[21],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto022,			strLabel[22],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto023,			strLabel[23],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto024,			strLabel[24],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto025,			strLabel[25],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto026,			strLabel[26],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto027,			strLabel[27],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto028,			strLabel[28],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto029,			strLabel[29],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto030,			strLabel[30],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto031,			strLabel[31],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto032,			strLabel[32],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto033,			strLabel[33],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto034,			strLabel[34],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto035,			strLabel[35],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto036,			strLabel[36],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto037,			strLabel[37],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto038,			strLabel[38],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto039,			strLabel[39],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto040,			strLabel[40],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto041,			strLabel[41],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto042,			strLabel[42],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto043,			strLabel[43],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto044,			strLabel[44],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto045,			strLabel[45],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto046,			strLabel[46],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto047,			strLabel[47],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto048,			strLabel[48],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto049,			strLabel[49],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto050,			strLabel[50],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto051,			strLabel[51],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto052,			strLabel[52],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto053,			strLabel[53],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto054,			strLabel[54],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto055,			strLabel[55],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto056,			strLabel[56],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto057,			strLabel[57],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto058,			strLabel[58],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto059,			strLabel[59],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto060,			strLabel[60],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto061,			strLabel[61],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto062,			strLabel[62],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto063,			strLabel[63],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto064,			strLabel[64],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto065,			strLabel[65],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto066,			strLabel[66],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto067,			strLabel[67],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto068,			strLabel[68],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto069,			strLabel[69],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto070,			strLabel[70],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto071,			strLabel[71],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto072,			strLabel[72],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto073,			strLabel[73],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto074,			strLabel[74],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto075,			strLabel[75],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto076,			strLabel[76],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto077,			strLabel[77],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto078,			strLabel[78],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto079,			strLabel[79],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto080,			strLabel[80],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto081,			strLabel[81],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto082,			strLabel[82],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto083,			strLabel[83],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto084,			strLabel[84],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto085,			strLabel[85],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto086,			strLabel[86],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto087,			strLabel[87],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto088,			strLabel[88],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto089,			strLabel[89],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto090,			strLabel[90],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto091,			strLabel[91],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto092,			strLabel[92],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto093,			strLabel[93],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto094,			strLabel[94],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto095,			strLabel[95],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto096,			strLabel[96],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto097,			strLabel[97],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto098,			strLabel[98],			"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet.m_setEP, &m_EsamiSet.m_setEP.m_sTesto099,			strLabel[99],			"\r\n");

		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sTerapia,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_23),	"\r\n");
		MakeStringDate		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_lDataControllo,	theApp.GetMessageString(IDS_QUERYDLG_EXAM_24),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_lDurata,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_25),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_lDifficolta,		theApp.GetMessageString(IDS_QUERYDLG_EXAM_41),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sEstensione,		theApp.GetMessageString(IDS_QUERYDLG_EXAM_26),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sMetodo,			theApp.GetMessageString(IDS_QUERYDLG_EXAM_27),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sProcTerapeutiche,theApp.GetMessageString(IDS_QUERYDLG_EXAM_28),	"\r\n");
		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sProcDiagnostiche,theApp.GetMessageString(IDS_QUERYDLG_EXAM_29),	"\r\n");
		// MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sMstComplicanze1, theApp.GetMessageString(IDS_QUERYDLG_EXAM_32),	"\r\n");
		// MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sMstComplicanze2, theApp.GetMessageString(IDS_QUERYDLG_EXAM_33),	"\r\n");
		// MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sMstComplicanze3, theApp.GetMessageString(IDS_QUERYDLG_EXAM_34),	"\r\n");

		MakeStringText		(*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sIntegrazioni,	theApp.GetMessageString(IDS_QUERYDLG_EXAM_30),	"\r\n");
		MakeStringText      (*pStrEdit, &m_EsamiSet, &m_EsamiSet.m_sAppunti, 		theApp.GetMessageString(IDS_QUERYDLG_EXAM_31),	"\r\n");

		CCodificaDiagnosiEsameSet setTemp;
		(*pStrEdit) += setTemp.GetStringForQuery(m_EsamiSet.m_lContatore);
	}
}

void CQueryDlg::RiempiListeDati()
{
	BeginWaitCursor();

	m_lCurrentSec	= 0L;

	switch(m_lRelazione)
	{
		case SOLO_PAZIENTI:
		{
			FiltraPazienti();
			MostraDatiPaziente(&m_StrPrincipale);

			FiltraEsami();
			MostraDatiEsame(&m_StrAssociato);

			break;
		}
		case PAZIENTI_ESAMI:
		case SOLO_ESAMI:
		{
			FiltraEsami();
			MostraDatiEsame(&m_StrAssociato);

			FiltraPazienti();
			MostraDatiPaziente(&m_StrPrincipale);

			break;
		}
		case PAZIENTI_ESAMI_ONLYPATIENTS:
		case SOLO_ESAMI_ONLYPATIENTS:
		{
			FiltraPazienti();
			MostraDatiPaziente(&m_StrPrincipale);

			FiltraEsami();
			MostraDatiEsame(&m_StrAssociato);

			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}

	UpdateData(FALSE);

	m_ctrlLista.SetFocus();

	MostraEsameSelezionato();

	EndWaitCursor();
}

void CQueryDlg::MostraEsameSelezionato()
{
	if (m_bVerifyDuplicated || !m_ctrlLista.GetCount())
		return;

	int lCurPazCode = m_lCurrentPri;
	int lCurExamCode = m_lCurrentSec;

	switch(m_lRelazione)
	{
		case SOLO_PAZIENTI:
		{
			break;
		}
		case PAZIENTI_ESAMI:
		case SOLO_ESAMI:
		{
			lCurPazCode = m_lCurrentSec;
			lCurExamCode = m_lCurrentPri;

			break;
		}
		case PAZIENTI_ESAMI_ONLYPATIENTS:
		case SOLO_ESAMI_ONLYPATIENTS:
		{
			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}

	if (m_pEsamiView->RicercaCodicePaziente(lCurPazCode, lCurExamCode, FALSE, FALSE))
		m_pEsamiView->MovePazientiAndEsami(NULL, FALSE, TRUE);
	else
		m_pEsamiView->MovePazientiAndEsami(NULL, TRUE, TRUE);
}

BOOL CQueryDlg::OnInitDialog()
{
	CResizableDialog::OnInitDialog();

	AddAnchor(IDC_TITOLO, CSize(0, 0), CSize(33, 0));
	AddAnchor(IDC_LIST, CSize(0, 0), CSize(33, 100));
	
	// Luiz - 21/02/2019 - P3 - Ajuste do Form para monitores de baixa resolução
	//AddAnchor(IDC_STATIC_FRAME0, CSize(0, 100), CSize(33, 100));
	//AddAnchor(IDOK, CSize(0, 100), CSize(11, 100));
	//AddAnchor(IDC_STATIC_FRAME1, CSize(33, 100), CSize(66, 100));
	//AddAnchor(IDC_LIST_STORICO, CSize(66, 33), CSize(100, 100));
	//AddAnchor(IDC_PREV, CSize(33, 100), CSize(33, 100));
	//AddAnchor(IDC_EXAM_1, CSize(33, 100), CSize(33, 100));
	//AddAnchor(IDC_EXAM_2, CSize(33, 100), CSize(33, 100));
	//AddAnchor(IDC_NEXT, CSize(33, 100), CSize(33, 100));
	AddAnchor(IDOK, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_EXAM_1, CSize(100, 33), CSize(100, 33));
	AddAnchor(IDC_EXAM_2, CSize(100, 33), CSize(100, 33));
	AddAnchor(IDC_PREV, CSize(100, 33), CSize(100, 33));
	AddAnchor(IDC_NEXT, CSize(100, 33), CSize(100, 33));

	AddAnchor(IDC_NEW, CSize(11, 100), CSize(22, 100));
	AddAnchor(IDC_BTN_UNIFICAZIONEANAGRAFICHE, CSize(22, 100), CSize(33, 100));

	AddAnchor(IDC_STR_PRINCIPALE, CSize(33, 0), CSize(100, 0));
	AddAnchor(IDC_PRINCIPALE, CSize(33, 0), CSize(100, 0));
	AddAnchor(IDC_STR_PRINCIPALE2, CSize(33, 33), CSize(66, 33));
	AddAnchor(IDC_STR_STORICO, CSize(66, 33), CSize(100, 33));
	AddAnchor(IDC_ASSOCIATO, CSize(33, 33), CSize(100, 100));
	AddAnchor(IDC_LIST_ESAMI, CSize(33, 33), CSize(66, 100));	
	
	AddAnchor(IDC_EXPORT, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_STAMPA, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_REPORT, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_ALBUM, CSize(100, 100), CSize(100, 100));

	m_PrevButton.AutoLoad(IDC_PREV, this);
	m_NextButton.AutoLoad(IDC_NEXT, this);
	m_btnExport.AutoLoad(IDC_EXPORT, this);
	m_AlbumButton.AutoLoad(IDC_ALBUM, this);
	m_PrintButton.AutoLoad(IDC_STAMPA, this);
	m_ReportButton.AutoLoad(IDC_REPORT, this);

	GetDlgItem(IDC_TITOLO)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_STR_PRINCIPALE)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_STR_PRINCIPALE2)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_STR_STORICO)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_EXAM_1)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EXAM_2)->SetFont(&theApp.m_fontBold);

	m_ctrlListEsami.SetExtendedStyle(m_ctrlListEsami.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListEsami.InsertColumn(0, "Numero", LVCFMT_LEFT, 100);
	m_ctrlListEsami.InsertColumn(1, "Tipo", LVCFMT_LEFT, 400);
	m_ctrlListEsami.InsertColumn(2, "Data", LVCFMT_LEFT, 100);

	// m_ctrlBtnUnificazioneAnagrafiche.ShowWindow(theApp.m_bMostraTastoUnificazioneAnagrafiche && m_bMostraTastoUnificazione ? SW_SHOW : SW_HIDE);
	m_ctrlBtnUnificazioneAnagrafiche.EnableWindow(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01);

	theApp.LocalizeDialog(this, CQueryDlg::IDD, "QueryDlg");
	CenterWindow();
	
	switch(m_lRelazione)
	{
		case SOLO_PAZIENTI:
		{
			break;
		}
		case PAZIENTI_ESAMI:
		case SOLO_ESAMI:
		{
			if (m_pPazientiSet)
			{
				m_pPazientiSet->CloseRecordset("CQueryDlg::OnInitDialog");

				m_pPazientiSet->SetSortRecord("Cognome, Nome, NatoIlCustom");
				m_pPazientiSet->OpenRecordset("CQueryDlg::OnInitDialog", TRUE, TRUE);
			}

			if (m_pJoinEsamiSet)
			{
				m_pJoinEsamiSet->CloseRecordset("CQueryDlg::OnInitDialog");
				m_pJoinEsamiSet->OpenRecordset("CQueryDlg::OnInitDialog");
			}

			break;
		}
		case PAZIENTI_ESAMI_ONLYPATIENTS:
		case SOLO_ESAMI_ONLYPATIENTS:
		{
			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}

	RiempiListaQuery();

	switch(m_lRelazione)
	{
		case SOLO_PAZIENTI:
		{
			m_strTitolo.Format(theApp.GetMessageString(IDS_QUERYDLG_TITLE_2), m_lTotale);
		
			m_PrevButton.ShowWindow(SW_SHOW);
			m_NextButton.ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EXAM_1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EXAM_2)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_ASSOCIATO)->ShowWindow(SW_SHOW);
			m_ctrlListEsami.ShowWindow(SW_HIDE);

			break;
		}
		case PAZIENTI_ESAMI:
		case SOLO_ESAMI:
		{
			m_strTitolo.Format(theApp.GetMessageString(IDS_QUERYDLG_TITLE_1), m_lTotale);
		
			m_PrevButton.ShowWindow(SW_HIDE);
			m_NextButton.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EXAM_1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EXAM_2)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_ASSOCIATO)->ShowWindow(SW_SHOW);
			m_ctrlListEsami.ShowWindow(SW_HIDE);

			break;
		}
		case PAZIENTI_ESAMI_ONLYPATIENTS:
		case SOLO_ESAMI_ONLYPATIENTS:
		{
			m_strTitolo.Format(theApp.GetMessageString(IDS_QUERYDLG_TITLE_2), m_lTotale);
		
			m_PrevButton.ShowWindow(SW_SHOW);
			m_NextButton.ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EXAM_1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EXAM_2)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_ASSOCIATO)->ShowWindow(SW_SHOW);
			m_ctrlListEsami.ShowWindow(SW_HIDE);

			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}

	if (m_bCercaPaziente || m_bVerifyDuplicated)
	{
		SetDlgItemText(IDOK, theApp.GetMessageString(IDS_QUERYDLG_BUTTON_1));

		GetDlgItem(IDC_NEW)->ShowWindow(SW_SHOW);
	}
    else
	{
		switch(m_lRelazione)
		{
			case SOLO_PAZIENTI:
			{
				SetDlgItemText(IDOK, theApp.GetMessageString(IDS_QUERYDLG_BUTTON_3));
				break;
			}
			case PAZIENTI_ESAMI:
			case SOLO_ESAMI:
			{
				SetDlgItemText(IDOK, theApp.GetMessageString(IDS_QUERYDLG_BUTTON_2));
				break;
			}
			case PAZIENTI_ESAMI_ONLYPATIENTS:
			case SOLO_ESAMI_ONLYPATIENTS:
			{
				SetDlgItemText(IDOK, theApp.GetMessageString(IDS_QUERYDLG_BUTTON_3));
				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
			}
		}
	}

	if (m_lTotale > 0)
	{
		//theApp.AfxMessageBoxEndo("riempi liste dati");
		RiempiListeDati();
		//theApp.AfxMessageBoxEndo("fine riempi liste dati");

		UpdateData(FALSE); 
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RICERCA_NO_RESULTS));
		CResizableDialog::OnCancel();
		return FALSE;
	}

	m_pReportElemSet = new CElemReportSet;

	if (!m_strTitle.IsEmpty())
		SetWindowText(m_strTitle);

	if (m_bSoloRicerca)
		GetDlgItem(IDC_NEW)->ShowWindow(FALSE);

	ShowWindow(SW_SHOW);

	CRect storicoRect;
	m_ctrlListaStorico.GetWindowRect(&storicoRect);
	m_ctrlListaStorico.ShowWindow(SW_HIDE);
	m_ctrlStaticStorico.ShowWindow(SW_HIDE);

	CRect pazienteRect;
	m_ctrlPrincipale.GetWindowRect(&pazienteRect);

	CRect titoloPazienteRect;
	m_ctrlStatic1.GetWindowRect(&titoloPazienteRect);

	// Luiz - 19/02/2019 - P3 - Ajuste do Form para monitores de baixa resolução
	pazienteRect.top = (int)44;
	pazienteRect.left = (int)393;
	pazienteRect.bottom = (int)200;
	pazienteRect.right = (int)555;
	m_ctrlPrincipale.SetWindowPos(NULL, pazienteRect.left, pazienteRect.top, pazienteRect.right, pazienteRect.bottom, SWP_NOOWNERZORDER);

	titoloPazienteRect.top = (int)10;
	titoloPazienteRect.left = (int)300;
	titoloPazienteRect.right = (int)500;
	titoloPazienteRect.bottom = (int)15;

	m_ctrlStatic1.SetWindowPos(NULL, titoloPazienteRect.left, titoloPazienteRect.top, titoloPazienteRect.right, titoloPazienteRect.bottom, SWP_NOOWNERZORDER);

	//pazienteRect.right = pazienteRect.right - storicoRect.Width();
	//m_ctrlPrincipale.SetWindowPos(NULL, pazienteRect.left, pazienteRect.top, pazienteRect.right, pazienteRect.bottom, SWP_NOOWNERZORDER);

	//titoloPazienteRect.right = titoloPazienteRect.right - storicoRect.Width();
	//m_ctrlStatic1.SetWindowPos(NULL, titoloPazienteRect.left, titoloPazienteRect.top, titoloPazienteRect.right, titoloPazienteRect.bottom, SWP_NOOWNERZORDER);		

	CRect dialogRect;
	GetWindowRect(&dialogRect);
	//dialogRect.right = dialogRect.right - storicoRect.Width();
	SetWindowPos(NULL, dialogRect.left, dialogRect.top, dialogRect.right, dialogRect.bottom, SWP_NOOWNERZORDER);		

	CenterWindow();

	return TRUE;
}

void CQueryDlg::OnSelChangeLista()
{
	int nCurPos = m_ctrlLista.GetCurSel();

	if (nCurPos == LB_ERR)
	{
       	theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_QUERYDLG_NO_RECORD));
       	return;
	}
		
	DWORD dwData = m_ctrlLista.GetItemData(nCurPos);

	/*
	CString temp;
	temp.Format("Code selezionato: %li", dwData);
	theApp.AfxMessageBoxEndo(temp);
	*/

	if (dwData == LB_ERR)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_QUERYDLG_ERR));
		return;
	}

	m_lCurrentPri = (long)dwData;
	
	RiempiListeDati();	
}

void CQueryDlg::OnNext()
{
	if (!m_pJoinEsamiSet->IsBOF() && !m_pJoinEsamiSet->IsEOF())
	{
		m_pJoinEsamiSet->MoveNext();
		
		m_lCurrentSec = m_pJoinEsamiSet->m_lEsame;

		FiltraSubEsami();

		MostraDatiEsame(&m_StrAssociato);

		m_nCurExam++;
	}
	else
	{
		m_StrAssociato = "";
	}

	UpdateData(FALSE);

	m_ctrlLista.SetFocus();

	MostraEsameSelezionato();
}

void CQueryDlg::OnPrev()
{
	if ((m_pJoinEsamiSet->IsBOF() == FALSE) && (m_pJoinEsamiSet->IsEOF() == FALSE))
	{
		m_pJoinEsamiSet->MovePrev();

		m_lCurrentSec = m_pJoinEsamiSet->m_lEsame;

		FiltraSubEsami();

		MostraDatiEsame(&m_StrAssociato);

		m_nCurExam--;
	}
	else
	{
		m_StrAssociato = "";
	}

	UpdateData(FALSE);

	m_ctrlLista.SetFocus();

	MostraEsameSelezionato();
}

void CQueryDlg::OnNew() 
{
	if (!m_bVerifyDuplicated)
	{
		// non deve succedere...
		// DestroyWindow();
	}
	else
	{
		if (theApp.MessageBoxEndo(theApp.GetMessageString(IDS_QUERYDLG_CONFIRMINSERT2), theApp.GetMessageString(IDS_ACHTUNG), MB_YESNO | MB_ICONSTOP) == IDYES)
		{
			m_bAddNew = TRUE;
			OnOK();
		}
	}
}

void CQueryDlg::OnOK() 
{
	if (!m_bVerifyDuplicated)
	{
		if (!m_bModale)
			m_pEsamiView->PostMessage(EM_HIDE_QUERY_WND);
		else
			CResizableDialog::OnOK();
	}
	else
	{
		CResizableDialog::OnOK();
	}
}

void CQueryDlg::OnCancel() 
{
	if (!m_bVerifyDuplicated)
	{
		m_pEsamiView->PostMessage(EM_HIDE_QUERY_WND);
	}
	else
	{
		CResizableDialog::OnCancel();
	}
}

void CQueryDlg::OnAlbum() 
{
	if (m_lTotale)
	{
		CMosaicDlg dlg(this, m_pEsamiView);

		dlg.DoModal();
	}
}

HBRUSH CQueryDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CResizableDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_TITOLO:
		case IDC_LIST:
		{
			pDC->SetTextColor(theApp.m_color[0]);
			break;
		}
		case IDC_STR_PRINCIPALE:
		case IDC_PRINCIPALE:
		{
			pDC->SetTextColor(theApp.m_color[1]);
			break;
		}
		case IDC_STR_PRINCIPALE2:
		case IDC_STR_STORICO:
		case IDC_ASSOCIATO:
		case IDC_LIST_ESAMI:
		case IDC_LIST_STORICO:
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
	}

	return hBrush;
}

void CQueryDlg::OnExport() 
{
	CExportFileDlg dlg;
	int nModalita;

	if (dlg.DoModal() == IDOK)
	{
		nModalita = dlg.m_nTipoExport;

		CString strFilter;
		CString strFileReport = "";
		CString strFileExport;
		CString strFiltro = "";
		CString strSezione;
		CString strTipo;
		CString strEtichetta;
		CString strField;
		BOOL bContinue = FALSE;
		BOOL bError;
		BOOL bSelectOnlyPatient;
		int nRiga = 0;
		
		CExportExcel excel;
		CExportHtml  html;
		CExportCSV   csv;

		strFilter = "Report ricerca (*.rps)|*.rps|Tutti i file|*.*|";

		CFileDialog ReportDlg(TRUE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, strFilter, this, 0, FALSE);
		ReportDlg.GetOFN().lpstrInitialDir = theApp.m_sEditRep; // Sandro Gallina - 04/05/2004 //
		
		if (ReportDlg.DoModal() == IDOK)
		{
			// Sandro Gallina - 04/05/2004 --> //
			if (theApp.m_bCheckRep == FALSE)
			{
				int iTemp = 0;
				int iLastSlash = 0;
				CString strTemp = ReportDlg.GetPathName();

				while(iTemp >= 0)
				{
					iTemp = strTemp.Find('\\', iLastSlash);
					if (iTemp >= 0)
						iLastSlash = iTemp + 1;
				}
				
				theApp.m_sEditRep = strTemp.Left(iLastSlash - 1);
				WritePrivateProfileString(szPercorsi, szEditRep, theApp.m_sEditRep, theApp.m_sFileConfig);
			}
			// <-- Sandro Gallina - 04/05/2004 //

			strFileReport = ReportDlg.GetPathName();
			bContinue = TRUE;
		}

		if (bContinue)
		{
			switch (nModalita)
			{
				case 0:
				{
					strFilter = "File Microsoft Excel (*.xls)|*.xls|Tutti i file|*.*|";
					break;
				}
				case 1:
				{
					strFilter = "File HTML (*.htm)|*.htm|Tutti i file|*.*|";
					break;
				}
				case 2:
				{
					strFilter = "File CSV (*.csv)|*.csv|Tutti i file|*.*|";
					break;
				}
			}

			CFileDialog FileDlg(FALSE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, strFilter, this, 0, FALSE);
			if (FileDlg.DoModal() == IDOK)
			{
				strFileExport = FileDlg.GetPathName();

				switch(nModalita)
				{
					case 0:
					{
						if (strFileExport.Right(4).CompareNoCase(".xls") != 0)
							strFileExport += ".xls";

						bContinue = excel.CreateFile(strFileExport);
						break;
					}
					case 1:
					{
						if (strFileExport.Right(4).CompareNoCase(".htm") != 0)
							strFileExport += ".htm";

						bContinue = html.CreateFile(strFileExport, theApp.GetMessageString(IDS_EXPORTING_DATA) + " " + theApp.m_sNomeProgramma, 0);
						break;
					}
					case 2:
					{
						if (strFileExport.Right(4).CompareNoCase(".csv") != 0)
							strFileExport += ".csv";

						bContinue = csv.CreateFile(strFileExport);
						break;
					}
				}
				
				if (!bContinue)
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_QUERYDLG_CANNOT_CREATE_FILE) + strFileExport);
			}	
			else
			{
				bContinue = FALSE;
			}
		}

		if (bContinue)
		{
			CExportWaitDlg dlgWait(m_lTotale, this);
			dlgWait.Create(IDD_EXPORT_WAIT, this);
			dlgWait.ShowWindow(SW_SHOW);
			
			int i = 0;
			CCaricaReport Report;

			Report.OpenReportFile(strFileReport, TRUE);
			bSelectOnlyPatient = SelectOnlyPatient(&Report);
			Report.MoveFirst();

			long nItemData;
			BOOL bContinue;

			for(i = -1; i < m_lTotale; i++)
			{
				if (i >= 0)
				{
					nItemData = m_ctrlLista.GetItemData(i);

					switch(m_lRelazione)
					{
						case SOLO_PAZIENTI:
						{
							strFiltro.Format("contatore=%li", nItemData);
							m_pPazientiSet->RecordsetReOpen(bError, strFiltro, "", "CQueryDlg::OnExport");
						
							bContinue = !m_pPazientiSet->IsEOF() && !m_pPazientiSet->IsBOF();
						
							if (!bSelectOnlyPatient && bContinue)
							{
								strFiltro.Format("Paziente=%li", nItemData);
								m_pEsamiSet->RecordsetReOpen(bError, strFiltro, "", "CQueryDlg::OnExport");
						
								bContinue = !m_pEsamiSet->IsEOF() && !m_pEsamiSet->IsBOF();
							}

							break;
						}
						case PAZIENTI_ESAMI:
						case SOLO_ESAMI:
						{
							strFiltro.Format("contatore=%li", nItemData);
							m_pEsamiSet->RecordsetReOpen(bError, strFiltro, "", "CQueryDlg::OnExport");
						
							strFiltro.Format("contatore=%li", m_pEsamiSet->m_lPaziente);
							m_pPazientiSet->RecordsetReOpen(bError, strFiltro, "", "CQueryDlg::OnExport");
					
							bContinue = !m_pPazientiSet->IsEOF() && !m_pPazientiSet->IsBOF() && !m_pEsamiSet->IsEOF() && !m_pEsamiSet->IsBOF();

							break;
						}
						case PAZIENTI_ESAMI_ONLYPATIENTS:
						case SOLO_ESAMI_ONLYPATIENTS:
						{
							strFiltro.Format("contatore=%li", nItemData);
							m_pPazientiSet->RecordsetReOpen(bError, strFiltro, "", "CQueryDlg::OnExport");
						
							bContinue = !m_pPazientiSet->IsEOF() && !m_pPazientiSet->IsBOF();
						
							if (!bSelectOnlyPatient && bContinue)
							{
								strFiltro.Format("Paziente=%li", nItemData);
								m_pEsamiSet->RecordsetReOpen(bError, strFiltro, "", "CQueryDlg::OnExport");
						
								bContinue = !m_pEsamiSet->IsEOF() && !m_pEsamiSet->IsBOF();
							}

							break;
						}
						default:
						{
							ASSERT(FALSE);
							break;
						}
					}
				}
				
				if (i == -1)
				{
					EsportaRigaRisultato(i, nRiga, nModalita, &excel, &html, &csv, &Report);					
					nRiga++;
				}
				else if (bContinue)
				{
					switch(m_lRelazione)
					{
						case SOLO_PAZIENTI:
						{
							if (bSelectOnlyPatient)
							{
								EsportaRigaRisultato(i, nRiga, nModalita, &excel, &html, &csv, &Report);					
								nRiga++;
							}
							else
							{
								// altrimenti scorro ed esporto tutti gli esami di quel paziente //

								while(!m_pEsamiSet->IsEOF())
								{
									EsportaRigaRisultato(i, nRiga, nModalita, &excel, &html, &csv, &Report);

									m_pEsamiSet->MoveNext();
									nRiga++;
								}
							}

							break;
						}
						case PAZIENTI_ESAMI:
						case SOLO_ESAMI:
						{
							EsportaRigaRisultato(i, nRiga, nModalita, &excel, &html, &csv, &Report);					
							nRiga++;

							break;
						}
						case PAZIENTI_ESAMI_ONLYPATIENTS:
						case SOLO_ESAMI_ONLYPATIENTS:
						{
							if (bSelectOnlyPatient)
							{
								EsportaRigaRisultato(i, nRiga, nModalita, &excel, &html, &csv, &Report);					
								nRiga++;
							}
							else
							{
								// altrimenti scorro ed esporto tutti gli esami di quel paziente //

								while(!m_pEsamiSet->IsEOF())
								{
									EsportaRigaRisultato(i, nRiga, nModalita, &excel, &html, &csv, &Report);

									m_pEsamiSet->MoveNext();
									nRiga++;
								}
							}

							break;
						}
						default:
						{
							ASSERT(FALSE);
							break;
						}
					}
				}

				dlgWait.m_ctrlProgress.SetPos(i);
				dlgWait.RedrawWindow();
			}

			// -------------------------------------------------------------------------
			// Riempio controlli RTF con testo header/footer se necessario
			// BOOL bHeader = Report.GetHeader();
			// BOOL bFooter = Report.GetFooter();

			Report.CloseReportFile();
			
			switch(nModalita)
			{
				case 0:
				{
					//Opzioni pagina Excel
					//excel.SetRowsHeight(15);

					excel.SetFont("Arial", 10, xlsNoFormat);
					excel.SetFont("Arial", 10, xlsBold);
					
					excel.PrintGridLines(TRUE);
					excel.CloseFile();
					break;
				}
				case 1:
				{
					html.CloseFile();
					break;
				}
				case 2:
				{
					csv.CloseFile("");
					break;
				}
			}
		
			dlgWait.DestroyWindow();
		}
	}
}

BOOL CQueryDlg::SelectOnlyPatient(CCaricaReport* Report)
{
	//Funzione per capire se il report di ricerca contiene solo campi relativi a pazienti
	//o anche relativi ad esami
	CString strEtichetta;
	BOOL bReturn = TRUE;

	Report->MoveFirst();
	while (!Report->IsEOF())
	{
		if (Report->GetFieldType() == "Field")
		{
			strEtichetta = Report->GetFieldValue();

			if (strEtichetta.Left(strEtichetta.Find(".", 0)) != "Anagrafico")
			{
				bReturn = FALSE;
				break;
			}
		}
	
		Report->MoveNext();
	}

	return bReturn;
}

void CQueryDlg::EsportaRigaRisultato(int i, short nRiga, int nModalita, CExportExcel* excel, CExportHtml* html, CExportCSV* csv, CCaricaReport* Report)
{
	CString strSezione, strTipo, strEtichetta, strField;
	long nPosCol = 1;
	int nSection = 1, nTotField;

	Report->MoveFirst();
	nTotField = Report->GetNumberOfFields();

	CString strFilter;
	strFilter.Format("Contatore=%li", m_pPazientiSet->m_lContatore);

	CPazientiSet setPaz;
	setPaz.SetOpenFilter(strFilter);
	if (setPaz.OpenRecordset("CQueryDlg::EsportaRigaRisultato"))
	{
		if (!setPaz.IsEOF())
		{
			while(!Report->IsEOF())
			{
				strTipo = Report->GetFieldType();

				if (strTipo == "Field")
				{
					strEtichetta = Report->GetFieldValue();
					if (nRiga == 0)
					{
						switch (nModalita)
						{
							case 0:
							{
								excel->WriteValue(ReturnLabel(strEtichetta), i + 1, (short)nPosCol - 1, xlsFont1, xlsGeneralAlign, xlsNormal);
								excel->SetColumnWidth((char)nPosCol - 1, (char)nPosCol - 1, 25);
								break;
							}
							case 1:
							{
								html->WriteValue(ReturnLabel(strEtichetta));
								if (nPosCol < nTotField)
									html->WriteNewColumn();
								break;
							}
							case 2:
							{
								csv->WriteValue(ReturnLabel(strEtichetta));
								csv->WriteNewColumn();
								break;
							}
						}
					}
					else						
					{
						strField = ReturnField(strTipo, strEtichetta, &setPaz);
						switch (nModalita)
						{
							case 0:
							{
								excel->WriteValue(strField, nRiga, (short)nPosCol - 1, xlsFont0, xlsGeneralAlign, xlsNormal);
								break;
							}
							case 1:
							{
								html->WriteValue(strField);
								if (nPosCol < nTotField)
									html->WriteNewColumn();
								break;
							}
							case 2:
							{
								csv->WriteValue(strField);
								csv->WriteNewColumn();
								break;
							}
						}
					}
					nPosCol++;
				}

				Report->MoveNext();
				nSection++;
			}

			switch (nModalita)
			{
				case 1:
				{
					html->WriteNewRow();
					break;
				}
				case 2:
				{
					csv->WriteNewRow();
					break;
				}
				default:
				{
					break;
				}
			}
		}

		setPaz.CloseRecordset("CQueryDlg::EsportaRigaRisultato");
	}
}

CString CQueryDlg::ReturnField(CString strTipo, CString strEtichetta, CPazientiSet* pPazientiSet)
{
	CString strField = "";

	int nTipo = -1;
	if (strTipo == "Text")
	{
		nTipo = 1;
	}
	else
	{
		if (strTipo == "Param")
		{
			nTipo = 2;
		}
		else
		{
			if (strTipo == "Label")
			{
				nTipo = 3;
			}
			else
			{
				if (strTipo == "Field")
					nTipo = 4;
			}
		}
	}

	switch(nTipo)
	{
		case 1: // testo generico //
		{
			strField = strEtichetta;

			break;
		}
		case 2: // parametri //
		{
			CCustomDate DataOggi(TRUE, TRUE);

			if (strEtichetta == szParamData)
			{
				strField = DataOggi.GetDate("%d/%m/%Y");
			}
			else
			{
				if (strEtichetta == szParamDataLarga)
				{
					strField = DataOggi.GetDate("%d/%m/%Y");
				}
				else
				{
					if (strEtichetta == szParamOra)
					{
						strField = DataOggi.GetDate("%H:%M");
					}
				}
			}

			break;
		}
		case 3: // etichette impostate //
		{
			strField = ReturnLabel(strEtichetta);

			break;
		}
		case 4: // campi del database //
		{
			int x = -1;
			for(int i = 0; i < endox_report_field_num_total; i++)
			{
				if (CFieldDlg::m_strFieldEndox[i].sReport == strEtichetta)
				{
					x = i;
					break;
				}
			}
			switch(x)
			{
				case paziente_progressivo:
				{
					strField.Format("%li", pPazientiSet->m_lContatore);
					break;
				}
				case paziente_codicefiscale:
				{
					strField = pPazientiSet->m_sCodFisc;
					break;
				}
				case paziente_codicefiscale_largo:
				{
					strField = pPazientiSet->m_sCodFisc;
					break;
				}
				case paziente_codicesanitario:
				{
					strField = pPazientiSet->m_sCodSanit;
					break;
				}
				case paziente_cognome:
				{
					strField = pPazientiSet->m_sCognome;
					break;
				}
				case paziente_nome:
				{
					strField = pPazientiSet->m_sNome;
					break;
				}
				case paziente_nominativo_cn:
				{
					strField = pPazientiSet->m_sCognome;
					strField.Trim();
					strField += " " + pPazientiSet->m_sNome;
					strField.Trim();
					break;
				}
				case paziente_nominativo_nc:
				{
					strField = pPazientiSet->m_sNome;
					strField.Trim();
					strField += " " + pPazientiSet->m_sCognome;
					strField.Trim();
					break;
				}
				case paziente_sesso:
				{
					switch (pPazientiSet->m_lSessoPaz)
					{
						case -1:
							strField = theApp.GetMessageString(IDS_PAZIENTIDLG_ND);
							break;
						case 0:
							strField = theApp.GetMessageString(IDS_PAZIENTIDLG_MALE);
							break;
						case 1:
							strField = theApp.GetMessageString(IDS_PAZIENTIDLG_FEMALE);
							break;
						case 2:
							strField = theApp.GetMessageString(IDS_PAZIENTIDLG_AMBIGOUS);
							break;
						case 3:
							strField = theApp.GetMessageString(IDS_PAZIENTIDLG_NOTAPPLICABLE);
							break;
						case 4:
							strField = theApp.GetMessageString(IDS_PAZIENTIDLG_OTHER);
							break;
						default:
							break;
					}					
				}
				case paziente_natoil:
				{
					CCustomDate tempDate(pPazientiSet->m_lNatoIlCustom);
					strField = tempDate.GetDate("%d/%m/%Y");
					break;
				}
				case paziente_natoa:
				{
					strField = pPazientiSet->m_sNatoA;
					break;
				}
				case paziente_professione:
				{
					strField = pPazientiSet->m_sProfessione;
					break;
				}
				case paziente_via:
				{
					strField = pPazientiSet->m_sVia;
					break;
				}
				case paziente_citta:
				{
					strField = pPazientiSet->m_sCitta;
					break;
				}
				case paziente_cap:
				{
					strField = pPazientiSet->m_sCAP;
					break;
				}
				case paziente_provincia:
				{
					strField = pPazientiSet->m_sProvincia;
					break;
				}
				case paziente_recapito:
				{
					strField = m_pEsamiView->m_PazTempSet.m_sCAP;
					strField.Trim();
					strField += " " + m_pEsamiView->m_PazTempSet.m_sCitta;
					strField.Trim();
					if (!m_pEsamiView->m_PazTempSet.m_sProvincia.IsEmpty())
						strField += " (" + m_pEsamiView->m_PazTempSet.m_sProvincia + ")";

					break;
				}
				case paziente_telefono1:
				{
					strField = pPazientiSet->m_sTelefono1;
					break;
				}
				case paziente_telefono2:
				{
					strField = pPazientiSet->m_sTelefono2;
					break;
				}
				case paziente_fax:
				{
					strField = pPazientiSet->m_sFax;
					break;
				}
				case paziente_cellulare1:
				{
					strField = pPazientiSet->m_sCellulare1;
					break;
				}
				case paziente_cellulare2:
				{
					strField = pPazientiSet->m_sCellulare2;
					break;
				}
				case paziente_email:
				{
					strField = pPazientiSet->m_sEmail;
					break;
				}
				case paziente_medicocurante:
				{
					strField = pPazientiSet->m_sMedicoCurante;
					break;
				}
				case paziente_medicotelefono:
				{
					strField = pPazientiSet->m_sMedicoTel;
					break;
				}
				case paziente_medicoindirizzo:
				{
					strField = pPazientiSet->m_sMedicoIndirizzo;
					break;
				}
				case paziente_medicoemail:
				{
					strField = pPazientiSet->m_sMedicoEmail;
					break;
				}
				case paziente_dasegnalare:
				{
					strField = pPazientiSet->m_sDenSegnalato;
					break;
				}
				case paziente_codicecliente:
				{
					strField = pPazientiSet->m_sCodiceCliente;
					break;
				}
				case paziente_cognome2:
				{
					strField = pPazientiSet->m_sCognome2;
					break;
				}
				case paziente_nominativopadre:
				{
					strField = pPazientiSet->m_sNominativoPadre;
					break;
				}
				case paziente_nominativomadre:
				{
					strField = pPazientiSet->m_sNominativoMadre;
					break;
				}
				case paziente_eta:
				{
					strField = GetStringEta(m_pPazientiSet->m_lNatoIlCustom, m_pEsamiSet->m_lData, FormatoEta::AnnoMeseGiornoAbbreviato); //Gabriel BUG 6225 - Lista DO
					break;
				}
				case paziente_eta_soloanni:
				{
					strField = GetStringEta(m_pPazientiSet->m_lNatoIlCustom, m_pEsamiSet->m_lData, FormatoEta::SoloAnno); //Gabriel BUG 6225 - Lista DO
					break;
				}
				case paziente_indirizzoricetta:
				{
					strField = m_pPazientiSet->m_sVia;
					strField.Trim();
					strField += " " + m_pPazientiSet->m_sCitta;
					strField.Trim();
					if (!m_pPazientiSet->m_sProvincia.IsEmpty())
						strField += " (" + m_pPazientiSet->m_sProvincia + ")";

					break;
				}
				case paziente_assiden:
				{
					strField = pPazientiSet->m_sAssIden;
					break;
				}
				case paziente_codalfa:
				{
					strField = pPazientiSet->m_sCodAlfa;
					break;
				}

				case anamnesi_fumo:
				{
					strField = CComboBoxSet(CMB_ANA_FUMO).GetFieldText(m_pEsamiSet->m_lFumo);
					break;
				}
				case anamnesi_sigarette:
				{
					strField = CComboBoxSet(CMB_ANA_SIGA).GetFieldText(m_pEsamiSet->m_lSigarette);
					break;
				}
				case anamnesi_alcol:
				{
					strField = CComboBoxSet(CMB_ANA_ALCO).GetFieldText(m_pEsamiSet->m_lAlcool);
					break;
				}
				case anamnesi_superalcolici:
				{
					strField = CComboBoxSet(CMB_ANA_SUPE).GetFieldText(m_pEsamiSet->m_lSuperAlcolici);
					break;
				}
				case anamnesi_caffe:
				{
					strField = CComboBoxSet(CMB_ANA_CAFF).GetFieldText(m_pEsamiSet->m_lCaffe);
					break;
				}
				case anamnesi_farmaci:
				{
					strField = m_pEsamiSet->m_sDenFarmaci;
					break;
				}
				case anamnesi_assunzione:
				{
					strField = CComboBoxSet(CMB_ANA_ASSU).GetFieldText(m_pEsamiSet->m_lAssunzione);
					break;
				}
				case anamnesi_peso:
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fPeso))
						strField.Format("%.2f", m_pEsamiSet->m_fPeso);
					break;
				}
				case anamnesi_altezza:
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fAltezza))
						strField.Format("%.2f", m_pEsamiSet->m_fAltezza);
					break;
				}
				case anamnesi_bmi:
				{
					if ((!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fPeso)) && (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fAltezza)))
						if ((m_pEsamiSet->m_fPeso > 0) && (m_pEsamiSet->m_fAltezza > 0))
							strField.Format("%.2f", (m_pEsamiSet->m_fPeso * 10000.0f) / (m_pEsamiSet->m_fAltezza * m_pEsamiSet->m_fAltezza));
					break;
				}
				case anamnesi_bsa:
				{
					if ((!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fPeso)) && (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fAltezza)))
						if ((m_pEsamiSet->m_fPeso > 0) && (m_pEsamiSet->m_fAltezza > 0))
							strField.Format("%.2f", m_pEsamiSet->m_fBSA);
					break;
				}

				case preliminari_progressivo:
				{
					strField.Format("%li", m_pEsamiSet->m_lContatore);
					break;
				}
				case preliminari_data:
				{
					strField = CCustomDate(m_pEsamiSet->m_lData).GetDate("%d/%m/%Y");
					break;
				}
				case preliminari_data_eng:
				{
					strField = CCustomDate(m_pEsamiSet->m_lData).GetDate("%m/%d/%Y");
					break;
				}
				case preliminari_ora:
				{
					strField = CCustomDate(m_pEsamiSet->m_lData).GetDate("%H:%M");
					break;
				}
				case preliminari_tipoesame:
				{
					strField = CTipoEsameSet().GetDescrizione(m_pEsamiSet->m_lIDEsame);
					break;
				}
				case preliminari_tipoesame_codice:
				{
					strField.Format("%li", m_pEsamiSet->m_lIDEsame);
					break;
				}
				case preliminari_sedeesame:
				{
					strField = CSediEsameSet().GetDescrizione(m_pEsamiSet->m_lIDSedeEsame, FALSE);
					break;
				}
				case preliminari_salaesame:
				{
					strField = m_pEsamiSet->m_sSalaEsame;
					break;
				}
				case preliminari_progressivoannuale:
				{
					strField = m_pEsamiSet->m_sProgressivoAnno;
					break;
				}
				case preliminari_codiceprenotazione:
				{
					strField = m_pEsamiSet->m_sCodicePrenotazione;
					break;
				}
				case preliminari_internoesterno:
				{
					strField = (m_pEsamiSet->m_lProvenienza == 0 ? "Interno" : "Esterno");
					break;
				}
				case preliminari_inviante1:
				{
					switch(m_pEsamiSet->m_lProvenienza)
					{
						case 0: // interno //
						{
							strField = CComboBoxSet(CMB_ESA_OSPEDALE).GetFieldText(m_pEsamiSet->m_lOspedale);
							break;
						}
						case 1: // esterno //
						{
							CInviantiSet setTemp;
							setTemp.SetTableName("EInviantiEsterni");
							strField = setTemp.GetFieldText(m_pEsamiSet->m_lInviante);
							break;
						}
						default: // BOH! //
						{
							strField = "";
							break;
						}
					}
					break;
				}
				case preliminari_inviante2:
				{
					switch(m_pEsamiSet->m_lProvenienza)
					{
						case 0: // interno //
						{
							CInviantiSet setTemp;
							setTemp.SetTableName("EInviantiInterni");
							strField = setTemp.GetFieldText(m_pEsamiSet->m_lInviante);
							break;
						}
						case 1: // esterno //
						{
							strField = m_pEsamiSet->m_sInvMedico;
							break;
						}
						default: // BOH! //
						{
							strField = "";
							break;
						}
					}
					break;
				}
				case preliminari_inviante3:
				{
					switch(m_pEsamiSet->m_lProvenienza)
					{
						case 0: // interno //
						{
							strField = CComboBoxSet(CMB_ESA_TIPODEGENZAINT).GetFieldText(m_pEsamiSet->m_lTipoDegenzaInterno);
							break;
						}
						case 1: // esterno //
						{
							strField = CComboBoxSet(CMB_ESA_TIPODEGENZAEST).GetFieldText(m_pEsamiSet->m_lTipoDegenzaEsterno);
							break;
						}
						default: // BOH! //
						{
							strField = "";
							break;
						}
					}
					break;
				}
				case preliminari_inviante_codice:
				{
					strField.Format("%li", m_pEsamiSet->m_lInviante);
					break;
				}
				case preliminari_medico1:
				{
					strField = CMediciSet().GetFieldTextFromContatore(m_pEsamiSet->m_lMedico);
					break;
				}
				case preliminari_medico1_firma0:
				case preliminari_medico1_firma1:
				case preliminari_medico1_firma2:
				case preliminari_medico1_firma3:
				case preliminari_medico1_firma4:
				case preliminari_medico1_firma5:
				case preliminari_medico1_firma6:
				case preliminari_medico1_firma7:
				case preliminari_medico1_firma8:
				case preliminari_medico1_firma9:
				{
					int nIndexTemp = x - preliminari_medico1_firma0;
					ASSERT((nIndexTemp >= 0) && (nIndexTemp <= 9));

					strField = CMediciSet().GetFieldFirmaFromContatore(m_pEsamiSet->m_lMedico, nIndexTemp);
					break;
				}
				case preliminari_medico1_immaginefirma:
				{
					strField = "";
					break;
				}
				case preliminari_medico2:
				{
					CMediciSet setTemp;
					strField = setTemp.GetFieldTextFromContatore(m_pEsamiSet->m_lAssistente);
					break;
				}
				case preliminari_medico2_firma0:
				case preliminari_medico2_firma1:
				case preliminari_medico2_firma2:
				case preliminari_medico2_firma3:
				case preliminari_medico2_firma4:
				case preliminari_medico2_firma5:
				case preliminari_medico2_firma6:
				case preliminari_medico2_firma7:
				case preliminari_medico2_firma8:
				case preliminari_medico2_firma9:
				{
					int nIndexTemp = x - preliminari_medico2_firma0;
					ASSERT((nIndexTemp >= 0) && (nIndexTemp <= 9));

					strField = CMediciSet().GetFieldFirmaFromContatore(m_pEsamiSet->m_lAssistente, nIndexTemp);
					break;
				}
				case preliminari_medico2_immaginefirma:
				{
					strField = "";
					break;
				}
				case preliminari_infermiere1:
				{
					strField = CInfermieriSet().GetFieldText(m_pEsamiSet->m_lInfermiere1);
					break;
				}
				case preliminari_infermiere1_matricola:
				{
					strField = CInfermieriSet().GetMatricola(m_pEsamiSet->m_lInfermiere1);
					break;
				}
				case preliminari_infermiere2:
				{
					strField = CInfermieriSet().GetFieldText(m_pEsamiSet->m_lInfermiere2);
					break;
				}
				case preliminari_infermiere2_matricola:
				{
					strField = CInfermieriSet().GetMatricola(m_pEsamiSet->m_lInfermiere2);
					break;
				}
				case preliminari_anestesista:
				{
					strField = m_pEsamiSet->m_sAnestesista;
					break;
				}
				case preliminari_camera:
				{
					strField.Format("%li", m_pEsamiSet->m_lCamera);
					break;
				}
				case preliminari_indicazioni:
				case preliminari_indicazioni_grande:
				{
					strField = m_pEsamiSet->m_sIndicazioni;
					break;
				}
				case preliminari_farmacotrial:
				{
					strField = m_pEsamiSet->m_sFarmacoTrial;
					break;
				}
				case preliminari_premedicazioni:
				{
					strField = m_pEsamiSet->m_sPremedicazioni;
					break;
				}

				case esame_procdiag_fisso:
				case esame_procdiag_grande:
				{
					strField = m_pEsamiSet->m_sProcDiagnostiche;
					break;
				}
				case esame_proctera_fisso:
				case esame_proctera_grande:
				{
					strField = m_pEsamiSet->m_sProcTerapeutiche;
					break;
				}
				case esame_mst_complicanze1_fisso:
				case esame_mst_complicanze1_grande:
				{
					strField = m_pEsamiSet->m_sMstComplicanze1;
					break;
				}
				case esame_mst_complicanze2_fisso:
				case esame_mst_complicanze2_grande:
				{
					strField = m_pEsamiSet->m_sMstComplicanze2;
					break;
				}
				case esame_mst_complicanze3_fisso:
				case esame_mst_complicanze3_grande:
				{
					strField = m_pEsamiSet->m_sMstComplicanze3;
					break;
				}
				case esame_condottofino:
				{
					strField = m_pEsamiSet->m_sEstensione;
					break;
				}

				case altridati_valutazione:
				{
					strField = m_pEsamiSet->m_sValutazione;
					break;
				}
				case altridati_prossimocontrollo:
				{
					CCustomDate tempDate(m_pEsamiSet->m_lDataControllo);
					strField = tempDate.GetDate("%d/%m/%Y");
					break;
				}
				case altridati_complicanze:
				{
					strField = m_pEsamiSet->m_sComplicanzeOld;
					break;
				}
				case altridati_terapia:
				{
					strField = m_pEsamiSet->m_sComplicanze1;
					break;
				}
				case altridati_provvedimenti:
				{
					strField = m_pEsamiSet->m_sComplicanze2;
					break;
				}
				case altridati_esito:
				{
					strField = m_pEsamiSet->m_sComplicanze3;
					break;
				}
				case altridati_tipovisita:
				{
					strField = m_pEsamiSet->m_sTipoVisita;
					break;
				}
				case altridati_studio:
				{
					strField = m_pEsamiSet->m_sStudio;
					break;
				}
				case altridati_quadro:
				{
					strField = m_pEsamiSet->m_sQuadro;
					break;
				}
				case altridati_guarigione:
				{
					strField = m_pEsamiSet->m_sGuarigione;
					break;
				}
				case altridati_durata:
				{
					strField.Format("%li", m_pEsamiSet->m_lDurata);
					break;
				}
				case altridati_difficolta:
				{
					strField.Format("%li", m_pEsamiSet->m_lDifficolta);
					break;
				}
				case altridati_terapiaconsigliata:
				{
					strField = m_pEsamiSet->m_sTerapia;
					break;
				}
				case altridati_strumenti:
				{
					strField = m_pEsamiSet->m_sStrumenti;
					break;
				}
				case altridati_accessori:
				{
					strField = m_pEsamiSet->m_sAccessori;
					break;
				}
				case altridati_note:
				{
					strField = m_pEsamiSet->m_sAppunti;
					break;
				}
				case altridati_biopsie:
				{
					strField = CIstologiaSet().GetEseguitoPrelievo(m_pEsamiSet->m_lContatore);
					break;
				}

				case referto_referto_fisso:
				{
					break;
				}
				case referto_referto_grande:
				{
					break;
				}

				case libero_riferimento:
				{
					strField = m_pEsamiSet->m_sCodEsame;
					break;
				}
				case libero_000:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto000;
					break;
				}
				case libero_001:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto001;
					break;
				}
				case libero_002:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto002;
					break;
				}
				case libero_003:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto003;
					break;
				}
				case libero_004:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto004;
					break;
				}
				case libero_005:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto005;
					break;
				}
				case libero_006:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto006;
					break;
				}
				case libero_007:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto007;
					break;
				}
				case libero_008:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto008;
					break;
				}
				case libero_009:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto009;
					break;
				}
				case libero_010:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto010;
					break;
				}
				case libero_011:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto011;
					break;
				}
				case libero_012:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto012;
					break;
				}
				case libero_013:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto013;
					break;
				}
				case libero_014:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto014;
					break;
				}
				case libero_015:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto015;
					break;
				}
				case libero_016:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto016;
					break;
				}
				case libero_017:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto017;
					break;
				}
				case libero_018:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto018;
					break;
				}
				case libero_019:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto019;
					break;
				}
				case libero_020:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto020;
					break;
				}
				case libero_021:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto021;
					break;
				}
				case libero_022:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto022;
					break;
				}
				case libero_023:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto023;
					break;
				}
				case libero_024:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto024;
					break;
				}
				case libero_025:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto025;
					break;
				}
				case libero_026:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto026;
					break;
				}
				case libero_027:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto027;
					break;
				}
				case libero_028:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto028;
					break;
				}
				case libero_029:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto029;
					break;
				}
				case libero_030:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto030;
					break;
				}
				case libero_031:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto031;
					break;
				}
				case libero_032:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto032;
					break;
				}
				case libero_033:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto033;
					break;
				}
				case libero_034:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto034;
					break;
				}
				case libero_035:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto035;
					break;
				}
				case libero_036:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto036;
					break;
				}
				case libero_037:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto037;
					break;
				}
				case libero_038:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto038;
					break;
				}
				case libero_039:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto039;
					break;
				}
				case libero_040:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto040;
					break;
				}
				case libero_041:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto041;
					break;
				}
				case libero_042:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto042;
					break;
				}
				case libero_043:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto043;
					break;
				}
				case libero_044:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto044;
					break;
				}
				case libero_045:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto045;
					break;
				}
				case libero_046:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto046;
					break;
				}
				case libero_047:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto047;
					break;
				}
				case libero_048:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto048;
					break;
				}
				case libero_049:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto049;
					break;
				}
				case libero_050:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto050;
					break;
				}
				case libero_051:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto051;
					break;
				}
				case libero_052:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto052;
					break;
				}
				case libero_053:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto053;
					break;
				}
				case libero_054:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto054;
					break;
				}
				case libero_055:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto055;
					break;
				}
				case libero_056:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto056;
					break;
				}
				case libero_057:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto057;
					break;
				}
				case libero_058:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto058;
					break;
				}
				case libero_059:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto059;
					break;
				}
				case libero_060:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto060;
					break;
				}
				case libero_061:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto061;
					break;
				}
				case libero_062:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto062;
					break;
				}
				case libero_063:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto063;
					break;
				}
				case libero_064:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto064;
					break;
				}
				case libero_065:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto065;
					break;
				}
				case libero_066:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto066;
					break;
				}
				case libero_067:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto067;
					break;
				}
				case libero_068:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto068;
					break;
				}
				case libero_069:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto069;
					break;
				}
				case libero_070:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto070;
					break;
				}
				case libero_071:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto071;
					break;
				}
				case libero_072:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto072;
					break;
				}
				case libero_073:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto073;
					break;
				}
				case libero_074:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto074;
					break;
				}
				case libero_075:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto075;
					break;
				}
				case libero_076:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto076;
					break;
				}
				case libero_077:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto077;
					break;
				}
				case libero_078:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto078;
					break;
				}
				case libero_079:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto079;
					break;
				}
				case libero_080:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto080;
					break;
				}
				case libero_081:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto081;
					break;
				}
				case libero_082:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto082;
					break;
				}
				case libero_083:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto083;
					break;
				}
				case libero_084:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto084;
					break;
				}
				case libero_085:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto085;
					break;
				}
				case libero_086:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto086;
					break;
				}
				case libero_087:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto087;
					break;
				}
				case libero_088:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto088;
					break;
				}
				case libero_089:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto089;
					break;
				}
				case libero_090:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto090;
					break;
				}
				case libero_091:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto091;
					break;
				}
				case libero_092:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto092;
					break;
				}
				case libero_093:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto093;
					break;
				}
				case libero_094:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto094;
					break;
				}
				case libero_095:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto095;
					break;
				}
				case libero_096:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto096;
					break;
				}
				case libero_097:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto097;
					break;
				}
				case libero_098:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto098;
					break;
				}
				case libero_099:
				{
					strField = m_pEsamiSet->m_setEP.m_sTesto099;
					break;
				}
				case libero_rtf_000_fisso:
				case libero_rtf_000_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt000;
					break;
				}
				case libero_rtf_001_fisso:
				case libero_rtf_001_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt001;
					break;
				}
				case libero_rtf_002_fisso:
				case libero_rtf_002_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt002;
					break;
				}
				case libero_rtf_003_fisso:
				case libero_rtf_003_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt003;
					break;
				}
				case libero_rtf_004_fisso:
				case libero_rtf_004_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt004;
					break;
				}
				case libero_rtf_005_fisso:
				case libero_rtf_005_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt005;
					break;
				}
				case libero_rtf_006_fisso:
				case libero_rtf_006_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt006;
					break;
				}
				case libero_rtf_007_fisso:
				case libero_rtf_007_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt007;
					break;
				}
				case libero_rtf_008_fisso:
				case libero_rtf_008_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt008;
					break;
				}
				case libero_rtf_009_fisso:
				case libero_rtf_009_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt009;
					break;
				}
				case libero_rtf_010_fisso:
				case libero_rtf_010_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt010;
					break;
				}
				case libero_rtf_011_fisso:
				case libero_rtf_011_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt011;
					break;
				}
				case libero_rtf_012_fisso:
				case libero_rtf_012_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt012;
					break;
				}
				case libero_rtf_013_fisso:
				case libero_rtf_013_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt013;
					break;
				}
				case libero_rtf_014_fisso:
				case libero_rtf_014_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt014;
					break;
				}
				case libero_rtf_015_fisso:
				case libero_rtf_015_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt015;
					break;
				}
				case libero_rtf_016_fisso:
				case libero_rtf_016_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt016;
					break;
				}
				case libero_rtf_017_fisso:
				case libero_rtf_017_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt017;
					break;
				}
				case libero_rtf_018_fisso:
				case libero_rtf_018_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt018;
					break;
				}
				case libero_rtf_019_fisso:
				case libero_rtf_019_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoTxt019;
					break;
				}
				case libero_cl_000_fisso:
				case libero_cl_000_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt000;
					break;
				}
				case libero_cl_001_fisso:
				case libero_cl_001_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt001;
					break;
				}
				case libero_cl_002_fisso:
				case libero_cl_002_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt002;
					break;
				}
				case libero_cl_003_fisso:
				case libero_cl_003_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt003;
					break;
				}
				case libero_cl_004_fisso:
				case libero_cl_004_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt004;
					break;
				}
				case libero_cl_005_fisso:
				case libero_cl_005_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt005;
					break;
				}
				case libero_cl_006_fisso:
				case libero_cl_006_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt006;
					break;
				}
				case libero_cl_007_fisso:
				case libero_cl_007_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt007;
					break;
				}
				case libero_cl_008_fisso:
				case libero_cl_008_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt008;
					break;
				}
				case libero_cl_009_fisso:
				case libero_cl_009_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt009;
					break;
				}
				case libero_cl_010_fisso:
				case libero_cl_010_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt010;
					break;
				}
				case libero_cl_011_fisso:
				case libero_cl_011_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt011;
					break;
				}
				case libero_cl_012_fisso:
				case libero_cl_012_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt012;
					break;
				}
				case libero_cl_013_fisso:
				case libero_cl_013_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt013;
					break;
				}
				case libero_cl_014_fisso:
				case libero_cl_014_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt014;
					break;
				}
				case libero_cl_015_fisso:
				case libero_cl_015_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt015;
					break;
				}
				case libero_cl_016_fisso:
				case libero_cl_016_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt016;
					break;
				}
				case libero_cl_017_fisso:
				case libero_cl_017_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt017;
					break;
				}
				case libero_cl_018_fisso:
				case libero_cl_018_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt018;
					break;
				}
				case libero_cl_019_fisso:
				case libero_cl_019_grande:
				{
					strField = m_pEsamiSet->m_setEP.m_sTestoCLTxt019;
					break;
				}
				//Julio 26/01/2018
				case libero_dataora_000:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra000);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break;
				}
				case libero_dataora_001:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra001);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_002:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra002);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_003:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra003);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_004:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra004);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_005:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra005);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_006:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra006);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_007:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra007);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_008:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra008);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_009:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra009);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_010:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra010);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_011:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra011);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_012:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra012);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_013:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra013);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_014:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra014);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_015:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra015);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_016:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra016);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_017:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra017);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_018:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra018);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				case libero_dataora_019:
				{
					CCustomDate tempDate(m_pEsamiSet->m_setEP.m_lDataOra019);
					strField = tempDate.GetDate("%d/%m/%Y %H:%M");
					break; 
				}
				//
				case libero_integrazioni:
				{
					strField = m_pEsamiSet->m_sIntegrazioni;
					break;
				}
				case form_codificadiagnosi_fisso:
				case form_codificadiagnosi_grande:
				{
					strField = CCodificaDiagnosiEsameSet().GetCodificaDiagnosiEsame(m_pEsamiSet->m_lContatore);
					break;
				}
				case form_codificaregionale_fisso:
				case form_codificaregionale_grande:
				case form_codificaregionale_5righe:
				{
					strField = CRegioneSet().GetFieldText(m_pEsamiSet->m_lContatore);
					break;
				}
				case form_diagnosi_fisso:
				case form_diagnosi_grande:
				{
					CDiagnosiSet setTemp;
					strField = setTemp.GetDiagnosi(m_pEsamiSet->m_lContatore);
					break;
				}
				/*
				case form_indaginipregresse:
				{
					if ((m_pEsamiView != NULL) && (m_pEsamiView->m_pDynForm[sub_indagini] != NULL))
						m_pEsamiView->m_pDynForm[sub_indagini]->SendMessage(MSG_FORM_PRINT, (WPARAM)&structTemp);
					break;
				}
				case form_pregressiesamistrumentali:
				{
					if ((m_pEsamiView != NULL) && (m_pEsamiView->m_pDynForm[sub_esamipregressi] != NULL))
						m_pEsamiView->m_pDynForm[sub_esamipregressi]->SendMessage(MSG_FORM_PRINT, (WPARAM)&structTemp);
					break;
				}
				case form_interventichirurgici:
				{
					if ((m_pEsamiView != NULL) && (m_pEsamiView->m_pDynForm[sub_chirurgici] != NULL))
						m_pEsamiView->m_pDynForm[sub_chirurgici]->SendMessage(MSG_FORM_PRINT, (WPARAM)&structTemp);
					break;
				}
				case form_interventiendoscopici:
				{
					if ((m_pEsamiView != NULL) && (m_pEsamiView->m_pDynForm[sub_endoscopici] != NULL))
						m_pEsamiView->m_pDynForm[sub_endoscopici]->SendMessage(MSG_FORM_PRINT, (WPARAM)&structTemp);
					break;
				}
				*/
				case form_istologia_fisso:
				case form_istologia_fisso_plus:
				case form_istologia_grande:
				case form_istologia_grande_plus:
				{
					CIstologiaSet setTemp;
					setTemp.GetFieldText(strField, m_pEsamiSet->m_lContatore);
					break;
				}
				case form_malattieprecedenti:
				{
					CMalattieSet().GetFieldText(strField, m_pEsamiSet->m_lContatore);
					break;
				}
				case form_accessori:
				{
					strField = CEsamiAccessoriSet().GetFieldText(m_pEsamiSet->m_lContatore);
					break;
				}
				case subanatomia_campioni:
				{
					break;
				}
				case subanatomia_inviorichiesta:
				{
					break;
				}
				case subanatomia_idcampione:
				{
					if (m_pEsamiView->m_pDynForm[sub_anatomiapatologica] != NULL)
					{
						CAnatomiaPatologicaForm* pForm = (CAnatomiaPatologicaForm*)m_pEsamiView->m_pDynForm[sub_anatomiapatologica];
						strField = pForm->GetField(2);
					}
					break;
				}
				case subanatomia_tipo:
				{
					if (m_pEsamiView->m_pDynForm[sub_anatomiapatologica] != NULL)
					{
						CAnatomiaPatologicaForm* pForm = (CAnatomiaPatologicaForm*)m_pEsamiView->m_pDynForm[sub_anatomiapatologica];
						strField = pForm->GetField(3);
					}
					break;
				}
				case subanatomia_intervento:
				{
					if (m_pEsamiView->m_pDynForm[sub_anatomiapatologica] != NULL)
					{
						CAnatomiaPatologicaForm* pForm = (CAnatomiaPatologicaForm*)m_pEsamiView->m_pDynForm[sub_anatomiapatologica];
						strField = pForm->GetField(4);
					}
					break;
				}
				case subanatomia_nrcampione:
				{
					if (m_pEsamiView->m_pDynForm[sub_anatomiapatologica] != NULL)
					{
						CAnatomiaPatologicaForm* pForm = (CAnatomiaPatologicaForm*)m_pEsamiView->m_pDynForm[sub_anatomiapatologica];
						strField = pForm->GetField(1);
					}
					break;
				}
				case subanatomia_notecampione:
				{
					if (m_pEsamiView->m_pDynForm[sub_anatomiapatologica] != NULL)
					{
						CAnatomiaPatologicaForm* pForm = (CAnatomiaPatologicaForm*)m_pEsamiView->m_pDynForm[sub_anatomiapatologica];
						strField = pForm->GetField(6);
					}
					break;
				}
				case subistologia_riga:
				{
					if (m_pEsamiView->m_pDynForm[sub_istopatologia] != NULL)
					{
						CIstologiaTotForm* pForm = (CIstologiaTotForm*)m_pEsamiView->m_pDynForm[sub_istopatologia];
						strField = pForm->GetField(0);
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe] != NULL)
					{
						CIstologiaTotForm5Righe* pForm = (CIstologiaTotForm5Righe*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe];
						strField = pForm->GetField(0);
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus] != NULL)
					{
						CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus];
						strField = pForm->GetField(0);
					}
					break;
				}
				case subistologia_tipo:
				{
					if (m_pEsamiView->m_pDynForm[sub_istopatologia] != NULL)
					{
						CIstologiaTotForm* pForm = (CIstologiaTotForm*)m_pEsamiView->m_pDynForm[sub_istopatologia];
						strField = pForm->GetField(1);
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe] != NULL)
					{
						CIstologiaTotForm5Righe* pForm = (CIstologiaTotForm5Righe*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe];
						strField = pForm->GetField(1);
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus] != NULL)
					{
						CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus];
						strField = pForm->GetField(1);
					}
					break;
				}
				case subistologia_organo:
				{
					if (m_pEsamiView->m_pDynForm[sub_istopatologia] != NULL)
					{
						CIstologiaTotForm* pForm = (CIstologiaTotForm*)m_pEsamiView->m_pDynForm[sub_istopatologia];
						strField = pForm->GetField(2);
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe] != NULL)
					{
						CIstologiaTotForm5Righe* pForm = (CIstologiaTotForm5Righe*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe];
						strField = pForm->GetField(2);
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus] != NULL)
					{
						CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus];
						strField = pForm->GetField(2);
					}
					break;
				}
				case subistologia_sede:
				{
					if (m_pEsamiView->m_pDynForm[sub_istopatologia] != NULL)
					{
						CIstologiaTotForm* pForm = (CIstologiaTotForm*)m_pEsamiView->m_pDynForm[sub_istopatologia];
						strField = pForm->GetField(3);
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe] != NULL)
					{
						CIstologiaTotForm5Righe* pForm = (CIstologiaTotForm5Righe*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe];
						strField = pForm->GetField(3);
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus] != NULL)
					{
						CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus];
						strField = pForm->GetField(3);
					}
					break;
				}
				case subistologia_numero:
				{
					if (m_pEsamiView->m_pDynForm[sub_istopatologia] != NULL)
					{
						CIstologiaTotForm* pForm = (CIstologiaTotForm*)m_pEsamiView->m_pDynForm[sub_istopatologia];
						strField = pForm->GetField(4);
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe] != NULL)
					{
						CIstologiaTotForm5Righe* pForm = (CIstologiaTotForm5Righe*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe];
						strField = pForm->GetField(4);
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus] != NULL)
					{
						CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus];
						strField = pForm->GetField(4);
					}
					break;
				}
				case subistologia_procedura:
				{
					if (m_pEsamiView->m_pDynForm[sub_istopatologia] != NULL)
					{
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe] != NULL)
					{
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus] != NULL)
					{
						CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus];
						strField = pForm->GetField(5);
					}
					break;
				}
				case subistologia_diagnosi:
				{
					if (m_pEsamiView->m_pDynForm[sub_istopatologia] != NULL)
					{
						CIstologiaTotForm* pForm = (CIstologiaTotForm*)m_pEsamiView->m_pDynForm[sub_istopatologia];
						strField = pForm->GetField(5);
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe] != NULL)
					{
						CIstologiaTotForm5Righe* pForm = (CIstologiaTotForm5Righe*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe];
						strField = pForm->GetField(5);
					}
					else if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus] != NULL)
					{
						CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus];
						strField = pForm->GetField(6);
					}
					break;
				}
				case preliminari_inviante_i:
				{
					CInviantiSet setTemp;
					setTemp.SetTableName("EInviantiInterni");
					strField = setTemp.GetFieldText(m_pEsamiSet->m_lInviante);

					break;
				}
				case preliminari_inviante_e:
				{
					strField = m_pEsamiSet->m_sInvMedico;
					break;
				}
				case form_sedeprevista:
				{
					strField = m_pEsamiSet->m_sSedePrevista;
					break;
				}
				//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
				case medico_inviante2:
				{
					strField = m_pEsamiSet->m_sInvMedico2;
					break;
				}
				case medico_inviante3:
				{
					strField = m_pEsamiSet->m_sInvMedico3;
					break;
				}
				case medico_inviante4:
				{
					strField = m_pEsamiSet->m_sInvMedico4;
					break;
				}
				case form_sederaggiunta:
				{
					strField = m_pEsamiSet->m_sSedeRaggiunta;
					break;
				}
				case screening_complicanzeimmediate:
				{
					strField = CComboComplicanzeSet(FALSE).GetDescrizione(m_pEsamiSet->m_lIDComplicanzeImmediate);
					break;
				}
				case screening_complicanzetardive:
				{
					strField = CComboComplicanzeSet(TRUE).GetDescrizione(m_pEsamiSet->m_lIDComplicanzeTardive);
					break;
				}
				case screening_pulizia:
				{
					strField = CComboPuliziaSet().GetDescrizione(m_pEsamiSet->m_lIDPulizia);
					break;
				}
				case screening_causenoncompletamento:
				{
					strField = CComboCauseNonCompletamentoSet().GetDescrizione(m_pEsamiSet->m_lIDCausaNonCompleto);
					break;
				}
				case screening_tolleranza:
				{
					strField = CComboTolleranzaSet().GetDescrizione(m_pEsamiSet->m_lIDTolleranza);
					break;
				}
				case screening_conclusioniscreening:
				{
					strField = CComboConclusioniScreeningSet().GetDescrizione(m_pEsamiSet->m_lIDConclusioniScreening);
					break;
				}
				case screening_conclusionicolon:
				{
					strField = CComboConclusioniColonSet().GetDescrizione(m_pEsamiSet->m_lIDConclusioniColon);
					break;
				}
				case screening_diagnosifinale:
				{
					strField = CComboDiagnosiFinaleSet().GetDescrizione(m_pEsamiSet->m_lIDDiagnosiFinale);
					break;
				}
				case screening_altreanomalie:
				{
					strField = CComboAltreAnomalieSet().GetDescrizione(m_pEsamiSet->m_lIDAltreAnomalie);
					break;
				}

				case preliminari_premedposologia:
				{
					strField = m_pEsamiSet->m_sPremedPosologia;
					break;
				}

				case form_breathtest_hp_risultato:
				{
					strField = theApp.GetMessageString(IDS_DUBBIO);

					if (m_pEsamiSet->m_iBreathTestHP == 0)
					{
						if ((m_pEsamiSet->m_fBreathTestHPDiff >= 0.0f) && (m_pEsamiSet->m_fBreathTestHPDiff < theApp.m_fSogliaBreathTestHP))
							strField = theApp.GetMessageString(IDS_NEGATIVO);
						else if (m_pEsamiSet->m_fBreathTestHPDiff >= theApp.m_fSogliaBreathTestHP)
							strField = theApp.GetMessageString(IDS_POSITIVO);
					}
					break;
				}
				case form_breathtest_hp_valore1:
				{
					strField = "-";
					if (m_pEsamiSet->m_iBreathTestHP == 0)
						if (m_pEsamiSet->m_fBreathTestHPVal1 > -99.0f)
							strField.Format("%.1f", m_pEsamiSet->m_fBreathTestHPVal1);
					break;
				}
				case form_breathtest_hp_valore2:
				{
					strField = "-";
					if (m_pEsamiSet->m_iBreathTestHP == 0)
						if (m_pEsamiSet->m_fBreathTestHPVal2 > -99.0f)
							strField.Format("%.1f", m_pEsamiSet->m_fBreathTestHPVal2);
					break;
				}
				case form_breathtest_hp_differenza:
				{
					strField = "-";
					if (m_pEsamiSet->m_iBreathTestHP == 0)
						if (m_pEsamiSet->m_fBreathTestHPDiff >= 0.0f)
							strField.Format("%.1f", m_pEsamiSet->m_fBreathTestHPDiff);
					break;
				}
				case form_sospensione_si_no:
				{
					strField = "-";
					switch(m_pEsamiSet->m_iSospeso)
					{
						case 0:
						{
							strField = theApp.GetMessageString(IDS_NO);
							break;
						}
						case 1:
						{
							strField = theApp.GetMessageString(IDS_YES);
							break;
						}
					}
					break;
				}
				case form_sospensione_data:
				{
					strField = CCustomDate(m_pEsamiSet->m_lDataScadenzaSospensione).GetDate("%d/%m/%Y");
					break;
				}
				case form_sospensione_motivo:
				{
					strField = m_pEsamiSet->m_sMotivoSospensione;
					break;
				}
				case esame_codesame:
				{
					int nTokenPos = m_pEsamiSet->m_sCodEsame.Find("#");
					if (nTokenPos >= 0)
						strField = m_pEsamiSet->m_sCodEsame.Left(nTokenPos);
					else
						strField = m_pEsamiSet->m_sCodEsame;

					break;
				}
				case esame_tempochiusura:
				{
					if ((m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_sDataOraSuperLock) || m_pEsamiSet->m_sDataOraSuperLock.IsEmpty()))
					{
						strField = theApp.GetMessageString(IDS_ESAMEINCORSO);
					}
					else
					{
						CCustomDate customStart = CCustomDate(m_pEsamiSet->m_lData);
						COleDateTime oledtStart = COleDateTime(customStart.GetYear(), customStart.GetMonth(), customStart.GetDay(), customStart.GetHour(), customStart.GetMinute(), 0);
						COleDateTime oledtStop = COleDateTime(atoi(m_pEsamiSet->m_sDataOraSuperLock.Left(4)), atoi(m_pEsamiSet->m_sDataOraSuperLock.Mid(4, 2)), atoi(m_pEsamiSet->m_sDataOraSuperLock.Mid(6, 2)), atoi(m_pEsamiSet->m_sDataOraSuperLock.Mid(8, 2)), atoi(m_pEsamiSet->m_sDataOraSuperLock.Mid(10, 2)), 0);
						COleDateTimeSpan timeDiff = oledtStop - oledtStart;

						strField.Format("%li %s %li %s %li %s", timeDiff.GetDays(), theApp.GetMessageString(IDS_GIORNI), timeDiff.GetHours(), theApp.GetMessageString(IDS_ORE), timeDiff.GetMinutes(), theApp.GetMessageString(IDS_MINUTI));
					}

					break;
				}
				case esame_tempoconvalida:
				{
					if ((m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_sDataOraLock) || m_pEsamiSet->m_sDataOraLock.IsEmpty()))
					{
						strField = theApp.GetMessageString(IDS_ESAMEINCORSO);
					}
					else
					{
						CCustomDate customStart = CCustomDate(m_pEsamiSet->m_lData);
						COleDateTime oledtStart = COleDateTime(customStart.GetYear(), customStart.GetMonth(), customStart.GetDay(), customStart.GetHour(), customStart.GetMinute(), 0);
						COleDateTime oledtStop = COleDateTime(atoi(m_pEsamiSet->m_sDataOraLock.Left(4)), atoi(m_pEsamiSet->m_sDataOraLock.Mid(4, 2)), atoi(m_pEsamiSet->m_sDataOraLock.Mid(6, 2)), atoi(m_pEsamiSet->m_sDataOraLock.Mid(8, 2)), atoi(m_pEsamiSet->m_sDataOraLock.Mid(10, 2)), 0);
						COleDateTimeSpan timeDiff = oledtStop - oledtStart;

						strField.Format("%li %s %li %s %li %s", timeDiff.GetDays(), theApp.GetMessageString(IDS_GIORNI), timeDiff.GetHours(), theApp.GetMessageString(IDS_ORE), timeDiff.GetMinutes(), theApp.GetMessageString(IDS_MINUTI));
					}

					break;
				}
				case esame_codicericovero:
				{
					strField = m_pEsamiSet->m_sRicovero;
					break;
				}
				case esame_barcodericovero:
				{
					strField = m_pEsamiSet->m_sIdEpisodioRicovero;
					break;
				}
				case esame_dataoralock:
				{
					if (m_pEsamiSet->m_sDataOraLock.GetLength() == 14)
					{
						strField.Format("%s/%s/%s %s:%s:%s", m_pEsamiSet->m_sDataOraLock.Mid(6, 2), m_pEsamiSet->m_sDataOraLock.Mid(4, 2), m_pEsamiSet->m_sDataOraLock.Left(4), m_pEsamiSet->m_sDataOraLock.Mid(8, 2), m_pEsamiSet->m_sDataOraLock.Mid(10, 2), m_pEsamiSet->m_sDataOraLock.Mid(12, 2));
					}
					else
					{
						CTime now = CTime::GetCurrentTime();
						strField = now.Format("%d/%m/%Y %H:%M:%S");
					}
					break;
				}
				case esame_dataorasuperlock:
				{
					if (m_pEsamiSet->m_sDataOraSuperLock.GetLength() == 14)
					{
						strField.Format("%s/%s/%s %s:%s:%s", m_pEsamiSet->m_sDataOraSuperLock.Mid(6, 2), m_pEsamiSet->m_sDataOraSuperLock.Mid(4, 2), m_pEsamiSet->m_sDataOraSuperLock.Left(4), m_pEsamiSet->m_sDataOraSuperLock.Mid(8, 2), m_pEsamiSet->m_sDataOraSuperLock.Mid(10, 2), m_pEsamiSet->m_sDataOraSuperLock.Mid(12, 2));
					}
					else
					{
						CTime now = CTime::GetCurrentTime();
						strField = now.Format("%d/%m/%Y %H:%M:%S");
					}
					break;
				}
				case esamestrumentale_orainizio:
				{
					strField = CCustomDate(m_pEsamiSet->m_lCustomDataOraInizioAcq).GetDate("%H:%M");
					break;
				}
				case esamestrumentale_orafine:
				{
					strField = CCustomDate(m_pEsamiSet->m_lCustomDataOraFineAcq).GetDate("%H:%M");
					break;
				}
				case esamestrumentale_durata_oreminuti:
				{
					strField = GetStringOreDifferenza(m_pEsamiSet->m_lCustomDataOraInizioAcq, m_pEsamiSet->m_lCustomDataOraFineAcq, FALSE);
					break;
				}
				case esamestrumentale_durata_solominuti:
				{
					strField = GetStringOreDifferenza(m_pEsamiSet->m_lCustomDataOraInizioAcq, m_pEsamiSet->m_lCustomDataOraFineAcq, TRUE);
					break;
				}
				case bostonscore_score_dx:
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreDx) && (m_pEsamiSet->m_lBostonScoreDx >= 0))
					{
						switch (m_pEsamiSet->m_lBostonScoreDx)
						{
						case 0:
						{
							strField = theApp.GetMessageString(IDS_BOSTONSCORE_0);
							break;
						}
						case 1:
						{
							strField = theApp.GetMessageString(IDS_BOSTONSCORE_1);
							break;
						}
						case 2:
						{
							strField = theApp.GetMessageString(IDS_BOSTONSCORE_2);
							break;
						}
						case 3:
						{
							strField = theApp.GetMessageString(IDS_BOSTONSCORE_3);
							break;
						}
						}
					}
					break;
				}
				case bostonscore_score_mid:
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreMid) && (m_pEsamiSet->m_lBostonScoreMid >= 0))
					{
						switch (m_pEsamiSet->m_lBostonScoreMid)
						{
						case 0:
						{
							strField = theApp.GetMessageString(IDS_BOSTONSCORE_0);
							break;
						}
						case 1:
						{
							strField = theApp.GetMessageString(IDS_BOSTONSCORE_1);
							break;
						}
						case 2:
						{
							strField = theApp.GetMessageString(IDS_BOSTONSCORE_2);
							break;
						}
						case 3:
						{
							strField = theApp.GetMessageString(IDS_BOSTONSCORE_3);
							break;
						}
						}
					}
					break;
				}
				case bostonscore_score_sx:
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreSx) && (m_pEsamiSet->m_lBostonScoreSx >= 0))
					{
						switch (m_pEsamiSet->m_lBostonScoreSx)
						{
						case 0:
						{
							strField = theApp.GetMessageString(IDS_BOSTONSCORE_0);
							break;
						}
						case 1:
						{
							strField = theApp.GetMessageString(IDS_BOSTONSCORE_1);
							break;
						}
						case 2:
						{
							strField = theApp.GetMessageString(IDS_BOSTONSCORE_2);
							break;
						}
						case 3:
						{
							strField = theApp.GetMessageString(IDS_BOSTONSCORE_3);
							break;
						}
						}
					}
					break;
				}
				case bostonscore_score_totale:
				{
					long lScoreTot = 0;

					if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
					{
						if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreDx) && (m_pEsamiSet->m_lBostonScoreDx >= 0))
							lScoreTot += m_pEsamiSet->m_lBostonScoreDx;

						if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreMid) && (m_pEsamiSet->m_lBostonScoreMid >= 0))
							lScoreTot += m_pEsamiSet->m_lBostonScoreMid;

						if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreSx) && (m_pEsamiSet->m_lBostonScoreSx >= 0))
							lScoreTot += m_pEsamiSet->m_lBostonScoreSx;
					}

					if ((lScoreTot >= 0) && (lScoreTot <= 9))
						strField.Format("%li", lScoreTot);

					break;
				}
				case bostonscore_descrizione_totale:
				{
					long lScoreTot = 0;

					if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
					{
						if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreDx) && (m_pEsamiSet->m_lBostonScoreDx >= 0))
							lScoreTot += m_pEsamiSet->m_lBostonScoreDx;

						if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreMid) && (m_pEsamiSet->m_lBostonScoreMid >= 0))
							lScoreTot += m_pEsamiSet->m_lBostonScoreMid;

						if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreSx) && (m_pEsamiSet->m_lBostonScoreSx >= 0))
							lScoreTot += m_pEsamiSet->m_lBostonScoreSx;
					}

					if ((lScoreTot >= 0) && (lScoreTot <= 9))
					{
						strField = theApp.m_sBostonScore[lScoreTot];
						strField.Trim();
					}

					break;
				}
				case worklist_note:
				{
					strField = "";
					break;
				}
				case worklist_assiden:
				{
					strField = "";
					break;
				}
				case worklist_cognome:
				{
					strField = "";
					break;
				}
				case worklist_cognome2:
				{
					strField = "";
					break;
				}
				case worklist_nome:
				{
					strField = "";
					break;
				}
				case worklist_datanascita:
				{
					strField = "";
					break;
				}
				case worklist_comunenascita:
				{
					strField = "";
					break;
				}
				case worklist_indirizzoresidenza:
				{
					strField = "";
					break;
				}
				case worklist_comuneresidenza:
				{
					strField = "";
					break;
				}
				case worklist_capresidenza:
				{
					strField = "";
					break;
				}
				case worklist_telefono1:
				{
					strField = "";
					break;
				}
				case worklist_telefono2:
				{
					strField = "";
					break;
				}
				case worklist_cellulare1:
				{
					strField = "";
					break;
				}
				case worklist_cellulare2:
				{
					strField = "";
					break;
				}
				case worklist_codicefiscale:
				{
					strField = "";
					break;
				}
				case worklist_codicesanitario:
				{
					strField = "";
					break;
				}
				case worklist_codicestp:
				{
					strField = "";
					break;
				}
				case worklist_codiceteam:
				{
					strField = "";
					break;
				}
				case worklist_sesso:
				{
					strField = "";
					break;
				}
				case worklist_medicocurante:
				{
					strField = "";
					break;
				}
				case worklist_cittadinanza:
				{
					strField = "";
					break;
				}
				case worklist_provincia:
				{
					strField = "";
					break;
				}
				case utenteconvalida_anagrafica:
				{
					strField = "";
					break;
				}
				case utenteconvalida_firma0:
				case utenteconvalida_firma1:
				case utenteconvalida_firma2:
				case utenteconvalida_firma3:
				case utenteconvalida_firma4:
				case utenteconvalida_firma5:
				case utenteconvalida_firma6:
				case utenteconvalida_firma7:
				case utenteconvalida_firma8:
				case utenteconvalida_firma9:
				{
					int nIndexTemp = x - utenteconvalida_firma0;
					ASSERT((nIndexTemp >= 0) && (nIndexTemp <= 9));

					strField = CMediciSet().GetFieldFirmaFromUserID(m_pEsamiSet->m_lIdUtenteLock, nIndexTemp);
					break;
				}
				case utenteconvalida_immaginefirma:
				{
					strField = "";
					break;
				}
				case utentechiusura_anagrafica:
				{
					strField = "";
					break;
				}
				case utentechiusura_firma0:
				case utentechiusura_firma1:
				case utentechiusura_firma2:
				case utentechiusura_firma3:
				case utentechiusura_firma4:
				case utentechiusura_firma5:
				case utentechiusura_firma6:
				case utentechiusura_firma7:
				case utentechiusura_firma8:
				case utentechiusura_firma9:
				{
					int nIndexTemp = x - utentechiusura_firma0;
					ASSERT((nIndexTemp >= 0) && (nIndexTemp <= 9));

					strField = CMediciSet().GetFieldFirmaFromUserID(m_pEsamiSet->m_lIdUtenteSuperLock, nIndexTemp);
					break;
				}
				case utentechiusura_immaginefirma:
				{
					strField = "";
					break;
				}
				/*case form_diagnosiicd9ex:
				{
					if ((m_pEsamiView != NULL) && (m_pEsamiView->m_pDynForm[sub_endoscopici] != NULL))
						m_pEsamiView->m_pDynForm[sub_endoscopici]->SendMessage(MSG_FORM_PRINT, (WPARAM)&structTemp);
					break;
				}*/
				case form_fluoroscopia:
				{
					if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
					{
						if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lFluoroscopiaMinuti) && !m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lFluoroscopiaSecondi) && !m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fFluoroscopiaDose))
						{
							strField.Format(theApp.GetMessageString(IDS_FLUOROSCOPIA_STAMPA), m_pEsamiSet->m_lFluoroscopiaMinuti, m_pEsamiSet->m_lFluoroscopiaSecondi, m_pEsamiSet->m_fFluoroscopiaDose);
							strField.Trim();
						}
					}

					break;
				}
				case esame_urgente:
				{
					if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
					{
						if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lLivelloUrgenza))
						{
							switch (m_pEsamiSet->m_lLivelloUrgenza)
							{
								case 0:
								{
									strField = theApp.GetMessageString(IDS_ESAME_NONURGENTE);
									break;
								}
								case 1:
								{
									strField = theApp.GetMessageString(IDS_ESAME_URGENTE);
									break;
								}
							}
							strField.Trim();
						}
					}

					break;
				}
			}

			break;
		}
	}

	return strField;
}

CString CQueryDlg::ReturnLabel(CString strEtichetta)
{
	CString strReturn = "";

	for(int i = 0; i < endox_report_field_num_total; i++)
	{
		if (CFieldDlg::m_strFieldEndox[i].sReport == strEtichetta)
		{
			strReturn = CFieldDlg::m_strFieldEndox[i].sCombo;
			break;
		}
	}

	return strReturn;
}

void CQueryDlg::OnStampa() 
{
	CString strFilter = "";
	strFilter = "Report ricerca (*.rps)|*.rps|Tutti i file|*.*|";

	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, strFilter, this, 0, FALSE);
	dlgFile.GetOFN().lpstrInitialDir = theApp.m_sEditRep;
	if (dlgFile.DoModal() != IDOK)
		return;

	long lPdfId = 0;
	m_pEsamiView->AnteprimaStampaReport(ANTEPRIMA, FALSE, dlgFile.GetPathName(), TRUE, 1, &lPdfId,"");
}

void CQueryDlg::OnReport()
{
	MSG msg;
	CModelessDlg dlg;
	dlg.CreateModeless(this);
	dlg.SetTitle("Invio documenti in stampa");

	char szFileReport[] =  
	{	
		"Report (*.rpt)|*.rpt|"
		"Tutti i file|*.*|"
	};
	CFileDialog FileDlg(TRUE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, szFileReport, this, 0, FALSE);
	FileDlg.GetOFN().lpstrInitialDir = theApp.m_sEditRep;
	if (FileDlg.DoModal() == IDOK)
	{
		CString sReportFile = FileDlg.GetPathName();

		if (theApp.m_bCheckRep == FALSE)
		{
			int iTemp = 0;
			int iLastSlash = 0;

			while(iTemp >= 0)
			{
				iTemp = sReportFile.Find('\\', iLastSlash);
				if (iTemp >= 0)
					iLastSlash = iTemp + 1;
			}
			
			theApp.m_sEditRep = sReportFile.Left(iLastSlash - 1);
			WritePrivateProfileString(szPercorsi, szEditRep, theApp.m_sEditRep, theApp.m_sFileConfig);
		}

		CString strTemp;
		int nCurSel = m_ctrlLista.GetCurSel();

		for(int i = 0; i < m_ctrlLista.GetCount(); i++)
		{
			m_ctrlLista.SetCurSel(i);
			OnSelChangeLista();

			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (dlg.m_bStop)
				break;

			m_ctrlLista.GetText(i, strTemp);
			dlg.SetInfo(strTemp);

			long lPdfId = 0;
			m_pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, sReportFile, FALSE, 1, &lPdfId,"");
		}

		m_ctrlLista.SetCurSel(nCurSel);
		OnSelChangeLista();
	}

 	dlg.DestroyWindow();

	if (m_pEsamiView->m_hDevMode)
		GlobalFree(m_pEsamiView->m_hDevMode);
	if (m_pEsamiView->m_hDevNames)
		GlobalFree(m_pEsamiView->m_hDevNames);
	m_pEsamiView->m_hDevMode = NULL;
	m_pEsamiView->m_hDevNames = NULL;
}

LRESULT CQueryDlg::OnShowQueryWnd(WPARAM, LPARAM)
{
	ShowWindow(SW_SHOW);
	OnSelChangeLista();

	return 1;
}

void CQueryDlg::OnDestroy()
{
	CResizableDialog::OnDestroy();
}

void CQueryDlg::RiempiListaEsami()
{
	int nItem = 0;
	CString strTemp;

	m_ctrlListEsami.DeleteAllItems();

	if (m_nTotExam > 0)
	{
		m_pJoinEsamiSet->MoveFirst();
		while(!m_pJoinEsamiSet->IsEOF())
		{
			strTemp.Format("%li", m_pJoinEsamiSet->m_lEsame);
			m_ctrlListEsami.InsertItem(nItem, strTemp);
			m_ctrlListEsami.SetItemData(nItem, (DWORD)m_pJoinEsamiSet->m_lEsame);

			m_ctrlListEsami.SetItemText(nItem, 1, CTipoEsameSet().GetDescrizione(CEsamiSet().GetTipoEsame(m_pJoinEsamiSet->m_lEsame)));

			m_ctrlListEsami.SetItemText(nItem, 2, CCustomDate(m_pJoinEsamiSet->m_lData).GetDate("%d/%m/%Y"));

			nItem++;
			m_pJoinEsamiSet->MoveNext();
		}

		m_ctrlListEsami.SetItemState(nItem - 1, TVIS_SELECTED, TVIS_SELECTED);
	}
}

void CQueryDlg::OnLvnItemChangedListEsami(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListEsami.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		m_lCurrentSec = m_ctrlListEsami.GetItemData(m_ctrlListEsami.GetNextSelectedItem(pos));
		MostraEsameSelezionato();
	}
}

void CQueryDlg::OnNMDblClkListEsami(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_ctrlListEsami.GetFirstSelectedItemPosition() != NULL)
		OnOK();
}

BOOL CQueryDlg::IsAfter(itemlistapazienti* pItemToInsert, itemlistapazienti* pItemOnList)
{
	if (pItemToInsert->sCognome > pItemOnList->sCognome)
	{
		return TRUE;
	}
	else if (pItemToInsert->sCognome == pItemOnList->sCognome)
	{
		if (pItemToInsert->sNome > pItemOnList->sNome)
		{
			return TRUE;
		}
		else if (pItemToInsert->sNome == pItemOnList->sNome)
		{
			if (pItemToInsert->lDataNascita >= pItemOnList->lDataNascita)
				return TRUE;
		}
	}

	return FALSE;
}

BOOL CQueryDlg::IsBefore(itemlistapazienti* pItemToInsert, itemlistapazienti* pItemOnList)
{
	if (pItemToInsert->sCognome < pItemOnList->sCognome)
	{
		return TRUE;
	}
	else if (pItemToInsert->sCognome == pItemOnList->sCognome)
	{
		if (pItemToInsert->sNome < pItemOnList->sNome)
		{
			return TRUE;
		}
		else if (pItemToInsert->sNome == pItemOnList->sNome)
		{
			if (pItemToInsert->lDataNascita < pItemOnList->lDataNascita)
				return TRUE;
		}
	}

	return FALSE;
}

void CQueryDlg::OnBnClickedBtnUnificazioneanagrafiche()
{
	CList<STRUCT_PAZIENTE> listPazienti;

	for(int i = 0; i < m_ctrlLista.GetCount(); i++)
	{
		STRUCT_PAZIENTE structTemp;

		structTemp.lID = m_ctrlLista.GetItemData(i);
		m_ctrlLista.GetText(i, structTemp.sNominativo);

		listPazienti.AddTail(structTemp);
	}

	if (!listPazienti.IsEmpty())
	{
		CUnificazioneAnagraficheDlg dlg(this, m_pEsamiView, &listPazienti);
		if (dlg.DoModal() == IDOK)
		{
			// chiudo la finestra corrente //
			m_pEsamiView->PostMessage(EM_DESTROY_QUERY_WND);
		}
	}

	listPazienti.RemoveAll();
}
