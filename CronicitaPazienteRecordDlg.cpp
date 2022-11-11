#include "stdafx.h"
#include "Endox.h"
#include "CronicitaPazienteRecordDlg.h"

#include "ComboBoxSet.h"
#include "Common.h"
#include "CustomDate.h"
#include "EsamiFarmaciCroniciSet.h"
#include "EsamiView.h"
#include "FarmaciPazientiCroniciSet.h"
#include "MalattieCronicheCampiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCronicitaPazienteRecordDlg, CDialog)

CCronicitaPazienteRecordDlg::CCronicitaPazienteRecordDlg(CWnd* pParent, CEsamiView* pEsamiView, long lIDMalattiaCronica, long lIDEsame)
	: CDialog(CCronicitaPazienteRecordDlg::IDD, pParent),
	m_ctrlList(FALSE, TRUE, FALSE)
{
	ASSERT(pEsamiView != NULL);
	ASSERT(lIDMalattiaCronica > 0);

	m_pEsamiView = pEsamiView;
	m_lIDMalattiaCronica = lIDMalattiaCronica;
	m_lIDEsame = lIDEsame;

	m_lNumeroRighe = 0;
	m_pRighe = NULL;

	//

	CString sFilter;
	sFilter.Format("Contatore=%li", m_lIDEsame);

	m_setEsami.SetBaseFilter("(RecordSenzaAccesso=0 OR RecordSenzaAccesso=1)");
	m_setEsami.SetOpenFilter(sFilter);
}

CCronicitaPazienteRecordDlg::~CCronicitaPazienteRecordDlg()
{
	if (m_pRighe != NULL)
	{
		delete m_pRighe;
		m_pRighe = NULL;
	}
}

BEGIN_MESSAGE_MAP(CCronicitaPazienteRecordDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_ANNULLA, OnBnClickedBtnAnnulla)
	ON_BN_CLICKED(IDC_BTN_CONFERMA, OnBnClickedBtnConferma)

END_MESSAGE_MAP()

void CCronicitaPazienteRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_BTN_ANNULLA, m_ctrlBtnAnnulla);
	DDX_Control(pDX, IDC_BTN_CONFERMA, m_ctrlBtnConferma);
}

void CCronicitaPazienteRecordDlg::OnCancel()
{
}

BOOL CCronicitaPazienteRecordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	if (m_pRighe != NULL)
	{
		delete m_pRighe;
		m_pRighe = NULL;
	}

	// conto il numero di righe e popolo l'array della struttura che conterrà i dati utili //

	CString sFilter;
	sFilter.Format("IDMalattia=%li", m_lIDMalattiaCronica);

	CMalattieCronicheCampiSet setMCC;
	setMCC.SetOpenFilter(sFilter);
	setMCC.SetSortRecord("Ordine, ID");
	if (setMCC.OpenRecordset("CCronicitaPazienteDlg::OnInitDialog"))
	{
		if (!setMCC.IsEOF())
		{
			while(!setMCC.IsEOF())
			{
				m_lNumeroRighe++;
				setMCC.MoveNext();
			}
			setMCC.MoveFirst();

			m_pRighe = new STRUCT_RIGA[m_lNumeroRighe];
			if (m_pRighe != NULL)
			{
				int nIndex = 0;

				while(!setMCC.IsEOF())
				{
					switch(setMCC.m_lTipoCampo)
					{
						case TIPOCAMPO_LIBERO:
						{
							FillDatiCampoLibero(setMCC.m_lIDCampo, &m_pRighe[nIndex]);
							break;
						}
						case TIPOCAMPO_SCORE:
						{
							FillDatiCampoScore(setMCC.m_lIDCampo, &m_pRighe[nIndex]);
							break;
						}
						case TIPOCAMPO_FARMACO:
						{
							FillDatiCampoFarmaco(setMCC.m_lIDCampo, &m_pRighe[nIndex]);
							break;
						}
						default:
						{
							ASSERT(FALSE);
							break;
						}
					}

					nIndex++;
					setMCC.MoveNext();
				}
			}
		}

		setMCC.CloseRecordset("CCronicitaPazienteDlg::OnInitDialog");
	}

	// riempio la lista //

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, "");
	m_ctrlList.InsertColumn(1, "");
	m_ctrlList.InsertColumn(2, "");
	m_ctrlList.SetColumnWidth(0, 0);
	m_ctrlList.SetColumnWidth(1, 300);
	m_ctrlList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList.InsertItem(0, "");
	m_ctrlList.SetItemText(0, 1, theApp.GetMessageString(IDS_DATA));
	m_ctrlList.SetSubItemEditDateTime(0, 2);
	for(int i = 0; i < m_lNumeroRighe; i++)
	{
		m_ctrlList.InsertItem(i + 1, "");
		m_ctrlList.SetItemText(i + 1, 1, m_pRighe[i].szTitoloRiga);

		switch(m_pRighe[i].lTipoCampo)
		{
			case FT_NUMERICO:
			{
				m_ctrlList.SetSubItemEdit(i + 1, 2, TRUE);
				break;
			}
			case FT_TESTOLIBERO:
			{
				m_ctrlList.SetSubItemEdit(i + 1, 2, FALSE);
				break;
			}
			case FT_LISTAVELOCE:
			{
				CStringIDList listTemp;

				tagLISTCOMBO tagTemp;
				tagTemp.lID = 0;
				tagTemp.strName = "";
				listTemp.AddTail(tagTemp);

				long lComboNumber = CMB_ESA_LIBERO000 + (m_pRighe[i].lIDCampo - edt_libero000);
				if ((lComboNumber >= CMB_ESA_LIBERO000) && (lComboNumber <= CMB_ESA_LIBERO099))
				{
					CComboBoxSet setComboBox(lComboNumber);
					if (setComboBox.OpenRecordset("CCronicitaPazienteRecordDlg::OnInitDialog"))
					{
						while (!setComboBox.IsEOF())
						{
							tagTemp.lID = setComboBox.m_lContatore;
							tagTemp.strName = setComboBox.m_sTesto;
							listTemp.AddTail(tagTemp);

							setComboBox.MoveNext();
						}

						setComboBox.CloseRecordset("CCronicitaPazienteRecordDlg::OnInitDialog");
					}
				}

				m_ctrlList.SetSubItemCombo(i + 1, 2, listTemp);
				break;
			}
			case FT_CUSTOM_DATAORA:
			{
				m_ctrlList.SetSubItemEditDateTime(i + 1, 2);
				break;
			}
			case FT_CUSTOM_SOLODATA:
			{
				m_ctrlList.SetSubItemEditDate(i + 1, 2);
				break;
			}
			case FT_CUSTOM_SOLOORA:
			{
				m_ctrlList.SetSubItemEditTime(i + 1, 2);
				break;
			}
			case FT_SCORE:
			{
				m_ctrlList.SetSubItemEdit(i + 1, 2, TRUE);
				break;
			}
			case FT_FARMACO:
			{
				CStringIDList listTemp;
				tagLISTCOMBO tagTemp;

				tagTemp.lID = 0;
				tagTemp.strName = "";
				listTemp.AddTail(tagTemp);

				tagTemp.lID = 1;
				tagTemp.strName = theApp.GetMessageString(IDS_FARMACO_INIZIO);
				listTemp.AddTail(tagTemp);

				tagTemp.lID = 2;
				tagTemp.strName = theApp.GetMessageString(IDS_FARMACO_CONTINUA);
				listTemp.AddTail(tagTemp);

				tagTemp.lID = 3;
				tagTemp.strName = theApp.GetMessageString(IDS_FARMACO_FINE);
				listTemp.AddTail(tagTemp);

				m_ctrlList.SetSubItemCombo(i + 1, 2, listTemp);
				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
			}
		}
	}

	//

	if (m_lIDEsame <= 0)
	{
		// nuovo record --> inserisco solo la data e gli eventuali farmaci //

		m_ctrlList.SetItemText(0, 2, CCustomDate(TRUE, TRUE).GetDate("%d/%m/%Y - %H:%M"));

		for(int i = 0; i < m_lNumeroRighe; i++)
		{
			if (m_pRighe[i].lTipoCampo == FT_FARMACO)
			{
				switch(m_pRighe[i].lFaseFarmaco)
				{
					case FARMACO_NIENTE:
					{
						m_ctrlList.SetItemText(i + 1, 2, "");
						break;
					}
					case FARMACO_INIZIO:
					{
						m_ctrlList.SetItemText(i + 1, 2, theApp.GetMessageString(IDS_FARMACO_INIZIO));
						break;
					}
					case FARMACO_CONTINUA:
					{
						m_ctrlList.SetItemText(i + 1, 2, theApp.GetMessageString(IDS_FARMACO_CONTINUA));
						break;
					}
					case FARMACO_FINE:
					{
						m_ctrlList.SetItemText(i + 1, 2, theApp.GetMessageString(IDS_FARMACO_FINE));
						break;
					}
					default:
					{
						ASSERT(FALSE);
						break;
					}
				}
			}
		}
	}
	else
	{
		// modifico record preesistente --> carico tutti i dati compresi i farmaci //

		if (m_setEsami.OpenRecordset("CCronicitaPazienteRecordDlg::OnInitDialog"))
		{
			if (!m_setEsami.IsEOF())
			{
				m_ctrlList.SetItemText(0, 2, CCustomDate(m_setEsami.m_lData).GetDate("%d/%m/%Y - %H:%M"));

				for(int i = 0; i < m_lNumeroRighe; i++)
				{
					switch(m_pRighe[i].lTipoCampo)
					{
						case FT_NUMERICO:
						case FT_TESTOLIBERO:
						case FT_LISTAVELOCE:
						{
							CString sTemp = (*(CString*)m_pRighe[i].pCampo);
							m_ctrlList.SetItemText(i + 1, 2, sTemp);

							break;
						}
						case FT_CUSTOM_DATAORA:
						{
							CString sTemp = CCustomDate(*(long*)m_pRighe[i].pCampo).GetDate("%d/%m/%Y - %H:%M");
							m_ctrlList.SetItemText(i + 1, 2, sTemp);

							break;
						}
						case FT_CUSTOM_SOLODATA:
						{
							CString sTemp = CCustomDate(*(long*)m_pRighe[i].pCampo).GetDate("%d/%m/%Y");
							m_ctrlList.SetItemText(i + 1, 2, sTemp);

							break;
						}
						case FT_CUSTOM_SOLOORA:
						{
							CString sTemp = CCustomDate(*(long*)m_pRighe[i].pCampo).GetDate("%H:%M");
							m_ctrlList.SetItemText(i + 1, 2, sTemp);

							break;
						}
						case FT_SCORE:
						{
							CString sTemp = (*(CString*)m_pRighe[i].pCampo);
							m_ctrlList.SetItemText(i + 1, 2, sTemp);

							break;
						}
						case FT_FARMACO:
						{
							switch(m_pRighe[i].lFaseFarmaco)
							{
								case FARMACO_NIENTE:
								{
									m_ctrlList.SetItemText(i + 1, 2, "");
									break;
								}
								case FARMACO_INIZIO:
								{
									m_ctrlList.SetItemText(i + 1, 2, theApp.GetMessageString(IDS_FARMACO_INIZIO));
									break;
								}
								case FARMACO_CONTINUA:
								{
									m_ctrlList.SetItemText(i + 1, 2, theApp.GetMessageString(IDS_FARMACO_CONTINUA));
									break;
								}
								case FARMACO_FINE:
								{
									m_ctrlList.SetItemText(i + 1, 2, theApp.GetMessageString(IDS_FARMACO_FINE));
									break;
								}
								default:
								{
									ASSERT(FALSE);
									break;
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
			}

			m_setEsami.CloseRecordset("CCronicitaPazienteRecordDlg::OnInitDialog");
		}
	}

	//

	theApp.LocalizeDialog(this, CCronicitaPazienteRecordDlg::IDD, "CronicitaPazienteRecordDlg");
	return TRUE;
}

void CCronicitaPazienteRecordDlg::OnOK()
{
}

void CCronicitaPazienteRecordDlg::OnBnClickedBtnAnnulla()
{
	CDialog::OnCancel();
}

void CCronicitaPazienteRecordDlg::OnBnClickedBtnConferma()
{
	BeginWaitCursor();
	if (m_lIDEsame <= 0)
	{
		// nuovo record //

		if (m_setEsami.OpenRecordset("CCronicitaPazienteRecordDlg::OnBnClickedBtnConferma"))
		{
			if (m_setEsami.AddNewRecordset("CCronicitaPazienteRecordDlg::OnBnClickedBtnConferma"))
			{
				m_setEsami.m_lPaziente = m_pEsamiView->m_pPazientiSet->m_lContatore;
				m_setEsami.m_lIDSedeEsame = theApp.m_lIDSedeEsameDefault;
				m_setEsami.m_sSalaEsame = theApp.m_sSalaEsameDefault;
				m_setEsami.m_lIDMalattiaCronica = m_pEsamiView->m_pPazientiSet->m_lIDMalattiaCronica;
				m_setEsami.m_bRecordSenzaAccesso = TRUE;
				RiempiRecordset();

				if (m_setEsami.UpdateRecordset("CCronicitaPazienteRecordDlg::OnBnClickedBtnConferma"))
				{
					// aggiungo gli eventuali farmaci //

					long lIDEsame = m_setEsami.GetLastAdd();

					for(int i = 0; i < m_lNumeroRighe; i++)
					{
						switch(m_pRighe[i].lTipoCampo)
						{
							case FT_NUMERICO:
							case FT_TESTOLIBERO:
							case FT_LISTAVELOCE:
							case FT_CUSTOM_DATAORA:
							case FT_CUSTOM_SOLODATA:
							case FT_CUSTOM_SOLOORA:
							case FT_SCORE:
							{
								break;
							}
							case FT_FARMACO:
							{
								CString sTemp = m_ctrlList.GetItemText(i + 1, 2);

								if (sTemp == theApp.GetMessageString(IDS_FARMACO_INIZIO))
								{
									CEsamiFarmaciCroniciSet().AddRow(lIDEsame, m_pRighe[i].lIDCampo, FARMACO_INIZIO);
								}
								else if (sTemp == theApp.GetMessageString(IDS_FARMACO_CONTINUA))
								{
									CEsamiFarmaciCroniciSet().AddRow(lIDEsame, m_pRighe[i].lIDCampo, FARMACO_CONTINUA);
								}
								else if (sTemp == theApp.GetMessageString(IDS_FARMACO_FINE))
								{
									CEsamiFarmaciCroniciSet().AddRow(lIDEsame, m_pRighe[i].lIDCampo, FARMACO_FINE);
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
				}
			}

			m_setEsami.CloseRecordset("CCronicitaPazienteRecordDlg::OnBnClickedBtnConferma");
		}
	}
	else
	{
		// modifico record preesistente //

		if (m_setEsami.OpenRecordset("CCronicitaPazienteRecordDlg::OnBnClickedBtnConferma"))
		{
			if (!m_setEsami.IsEOF())
			{
				if (m_setEsami.EditRecordset("CCronicitaPazienteRecordDlg::OnBnClickedBtnConferma"))
				{
					RiempiRecordset();

					if (m_setEsami.UpdateRecordset("CCronicitaPazienteRecordDlg::OnBnClickedBtnConferma"))
					{
						CEsamiFarmaciCroniciSet().DelAllRows(m_setEsami.m_lContatore);

						for(int i = 0; i < m_lNumeroRighe; i++)
						{
							switch(m_pRighe[i].lTipoCampo)
							{
								case FT_NUMERICO:
								case FT_TESTOLIBERO:
								case FT_LISTAVELOCE:
								case FT_CUSTOM_DATAORA:
								case FT_CUSTOM_SOLODATA:
								case FT_CUSTOM_SOLOORA:
								case FT_SCORE:
								{
									break;
								}
								case FT_FARMACO:
								{
									CString sTemp = m_ctrlList.GetItemText(i + 1, 2);

									if (sTemp == theApp.GetMessageString(IDS_FARMACO_INIZIO))
									{
										CEsamiFarmaciCroniciSet().AddRow(m_setEsami.m_lContatore, m_pRighe[i].lIDCampo, FARMACO_INIZIO);
									}
									else if (sTemp == theApp.GetMessageString(IDS_FARMACO_CONTINUA))
									{
										CEsamiFarmaciCroniciSet().AddRow(m_setEsami.m_lContatore, m_pRighe[i].lIDCampo, FARMACO_CONTINUA);
									}
									else if (sTemp == theApp.GetMessageString(IDS_FARMACO_FINE))
									{
										CEsamiFarmaciCroniciSet().AddRow(m_setEsami.m_lContatore, m_pRighe[i].lIDCampo, FARMACO_FINE);
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
					}
				}
			}

			m_setEsami.CloseRecordset("CCronicitaPazienteRecordDlg::OnBnClickedBtnConferma");
		}
	}
	EndWaitCursor();

	CDialog::OnOK();
}

void CCronicitaPazienteRecordDlg::FillDatiCampoLibero(long lIDCampo, STRUCT_RIGA* pRiga)
{
	ASSERT(((lIDCampo >= edt_libero000) && (lIDCampo <= edt_libero099)) || ((lIDCampo >= edt_liberodataora000) && (lIDCampo <= edt_liberodataora019)));

	CString sTemp = g_FormCaract[lIDCampo].sDescrizione.Left(1023);
	memcpy(pRiga->szTitoloRiga, sTemp.GetBuffer(), sTemp.GetLength() + 1);
	sTemp.ReleaseBuffer();

	//

	pRiga->lIDCampo = lIDCampo;

	//

	pRiga->lTipoCampo = FT_BOH;

	if ((lIDCampo >= edt_libero000) && (lIDCampo <= edt_libero099))
	{
		if (theApp.m_bComboNumerico[lIDCampo - edt_libero000])
			pRiga->lTipoCampo = FT_NUMERICO;
		else if (theApp.m_bComboActive[lIDCampo - edt_libero000])
			pRiga->lTipoCampo = FT_LISTAVELOCE;
		else
			pRiga->lTipoCampo = FT_TESTOLIBERO;
	}
	else if ((lIDCampo >= edt_liberodataora000) && (lIDCampo <= edt_liberodataora019))
	{
		switch(theApp.m_iRadioDate[lIDCampo - edt_liberodataora000])
		{
			case DATA_ORA:
			{
				pRiga->lTipoCampo = FT_CUSTOM_DATAORA;
				break;
			}
			case SOLO_DATA:
			{
				pRiga->lTipoCampo = FT_CUSTOM_SOLODATA;
				break;
			}
			case SOLO_ORA:
			{
				pRiga->lTipoCampo = FT_CUSTOM_SOLOORA;
				break;
			}
		}
	}

	//

	switch(lIDCampo)
	{
		case edt_libero000:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto000;
			break;
		}
		case edt_libero001:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto001;
			break;
		}
		case edt_libero002:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto002;
			break;
		}
		case edt_libero003:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto003;
			break;
		}
		case edt_libero004:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto004;
			break;
		}
		case edt_libero005:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto005;
			break;
		}
		case edt_libero006:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto006;
			break;
		}
		case edt_libero007:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto007;
			break;
		}
		case edt_libero008:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto008;
			break;
		}
		case edt_libero009:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto009;
			break;
		}
		case edt_libero010:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto010;
			break;
		}
		case edt_libero011:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto011;
			break;
		}
		case edt_libero012:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto012;
			break;
		}
		case edt_libero013:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto013;
			break;
		}
		case edt_libero014:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto014;
			break;
		}
		case edt_libero015:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto015;
			break;
		}
		case edt_libero016:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto016;
			break;
		}
		case edt_libero017:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto017;
			break;
		}
		case edt_libero018:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto018;
			break;
		}
		case edt_libero019:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto019;
			break;
		}
		case edt_libero020:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto020;
			break;
		}
		case edt_libero021:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto021;
			break;
		}
		case edt_libero022:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto022;
			break;
		}
		case edt_libero023:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto023;
			break;
		}
		case edt_libero024:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto024;
			break;
		}
		case edt_libero025:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto025;
			break;
		}
		case edt_libero026:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto026;
			break;
		}
		case edt_libero027:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto027;
			break;
		}
		case edt_libero028:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto028;
			break;
		}
		case edt_libero029:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto029;
			break;
		}
		case edt_libero030:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto030;
			break;
		}
		case edt_libero031:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto031;
			break;
		}
		case edt_libero032:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto032;
			break;
		}
		case edt_libero033:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto033;
			break;
		}
		case edt_libero034:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto034;
			break;
		}
		case edt_libero035:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto035;
			break;
		}
		case edt_libero036:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto036;
			break;
		}
		case edt_libero037:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto037;
			break;
		}
		case edt_libero038:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto038;
			break;
		}
		case edt_libero039:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto039;
			break;
		}
		case edt_libero040:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto040;
			break;
		}
		case edt_libero041:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto041;
			break;
		}
		case edt_libero042:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto042;
			break;
		}
		case edt_libero043:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto043;
			break;
		}
		case edt_libero044:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto044;
			break;
		}
		case edt_libero045:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto045;
			break;
		}
		case edt_libero046:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto046;
			break;
		}
		case edt_libero047:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto047;
			break;
		}
		case edt_libero048:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto048;
			break;
		}
		case edt_libero049:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto049;
			break;
		}
		case edt_libero050:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto050;
			break;
		}
		case edt_libero051:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto051;
			break;
		}
		case edt_libero052:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto052;
			break;
		}
		case edt_libero053:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto053;
			break;
		}
		case edt_libero054:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto054;
			break;
		}
		case edt_libero055:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto055;
			break;
		}
		case edt_libero056:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto056;
			break;
		}
		case edt_libero057:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto057;
			break;
		}
		case edt_libero058:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto058;
			break;
		}
		case edt_libero059:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto059;
			break;
		}
		case edt_libero060:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto060;
			break;
		}
		case edt_libero061:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto061;
			break;
		}
		case edt_libero062:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto062;
			break;
		}
		case edt_libero063:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto063;
			break;
		}
		case edt_libero064:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto064;
			break;
		}
		case edt_libero065:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto065;
			break;
		}
		case edt_libero066:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto066;
			break;
		}
		case edt_libero067:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto067;
			break;
		}
		case edt_libero068:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto068;
			break;
		}
		case edt_libero069:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto069;
			break;
		}
		case edt_libero070:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto070;
			break;
		}
		case edt_libero071:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto071;
			break;
		}
		case edt_libero072:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto072;
			break;
		}
		case edt_libero073:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto073;
			break;
		}
		case edt_libero074:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto074;
			break;
		}
		case edt_libero075:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto075;
			break;
		}
		case edt_libero076:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto076;
			break;
		}
		case edt_libero077:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto077;
			break;
		}
		case edt_libero078:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto078;
			break;
		}
		case edt_libero079:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto079;
			break;
		}
		case edt_libero080:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto080;
			break;
		}
		case edt_libero081:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto081;
			break;
		}
		case edt_libero082:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto082;
			break;
		}
		case edt_libero083:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto083;
			break;
		}
		case edt_libero084:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto084;
			break;
		}
		case edt_libero085:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto085;
			break;
		}
		case edt_libero086:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto086;
			break;
		}
		case edt_libero087:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto087;
			break;
		}
		case edt_libero088:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto088;
			break;
		}
		case edt_libero089:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto089;
			break;
		}
		case edt_libero090:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto090;
			break;
		}
		case edt_libero091:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto091;
			break;
		}
		case edt_libero092:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto092;
			break;
		}
		case edt_libero093:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto093;
			break;
		}
		case edt_libero094:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto094;
			break;
		}
		case edt_libero095:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto095;
			break;
		}
		case edt_libero096:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto096;
			break;
		}
		case edt_libero097:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto097;
			break;
		}
		case edt_libero098:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto098;
			break;
		}
		case edt_libero099:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto099;
			break;
		}
		case edt_liberodataora000:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra000;
			break;
		}
		case edt_liberodataora001:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra001;
			break;
		}
		case edt_liberodataora002:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra002;
			break;
		}
		case edt_liberodataora003:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra003;
			break;
		}
		case edt_liberodataora004:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra004;
			break;
		}
		case edt_liberodataora005:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra005;
			break;
		}
		case edt_liberodataora006:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra006;
			break;
		}
		case edt_liberodataora007:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra007;
			break;
		}
		case edt_liberodataora008:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra008;
			break;
		}
		case edt_liberodataora009:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra009;
			break;
		}
		case edt_liberodataora010:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra010;
			break;
		}
		case edt_liberodataora011:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra011;
			break;
		}
		case edt_liberodataora012:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra012;
			break;
		}
		case edt_liberodataora013:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra013;
			break;
		}
		case edt_liberodataora014:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra014;
			break;
		}
		case edt_liberodataora015:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra015;
			break;
		}
		case edt_liberodataora016:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra016;
			break;
		}
		case edt_liberodataora017:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra017;
			break;
		}
		case edt_liberodataora018:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra018;
			break;
		}
		case edt_liberodataora019:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra019;
			break;
		}
		default:
		{
			pRiga->pCampo = NULL;
			break;
		}
	}

	//

	pRiga->lFaseFarmaco = FARMACO_NIENTE;
}

void CCronicitaPazienteRecordDlg::FillDatiCampoScore(long lIDCampo, STRUCT_RIGA* pRiga)
{
	ASSERT((lIDCampo == EDT_PAZIENTICRONICI_SCORE_HB) || (lIDCampo == EDT_PAZIENTICRONICI_SCORE_S));

	//

	switch(lIDCampo)
	{
		case EDT_PAZIENTICRONICI_SCORE_HB:
		{
			CString sTemp = theApp.GetMessageString(IDS_SCORE_HB);
			memcpy(pRiga->szTitoloRiga, sTemp.GetBuffer(), sTemp.GetLength() + 1);
			sTemp.ReleaseBuffer();

			break;
		}
		case EDT_PAZIENTICRONICI_SCORE_S:
		{
			CString sTemp = theApp.GetMessageString(IDS_SCORE_S);
			memcpy(pRiga->szTitoloRiga, sTemp.GetBuffer(), sTemp.GetLength() + 1);
			sTemp.ReleaseBuffer();

			break;
		}
		default:
		{
			memcpy(pRiga->szTitoloRiga, "", 1);
			break;
		}
	}

	//

	pRiga->lIDCampo = lIDCampo;

	//

	pRiga->lTipoCampo = FT_SCORE;

	//

	switch(lIDCampo)
	{
		case EDT_PAZIENTICRONICI_SCORE_HB:
		{
			pRiga->pCampo = &m_setEsami.m_sPazientiCroniciScoreHB;
			break;
		}
		case EDT_PAZIENTICRONICI_SCORE_S:
		{
			pRiga->pCampo = &m_setEsami.m_sPazientiCroniciScoreS;
			break;
		}
		default:
		{
			pRiga->pCampo = NULL;
			break;
		}
	}

	//

	pRiga->lFaseFarmaco = FARMACO_NIENTE;
}

void CCronicitaPazienteRecordDlg::FillDatiCampoFarmaco(long lIDCampo, STRUCT_RIGA* pRiga)
{
	// Sandro 05/09/2013 //

	CString sTemp = CFarmaciPazientiCroniciSet().GetDescrizione(lIDCampo);
	memcpy(pRiga->szTitoloRiga, sTemp.GetBuffer(), sTemp.GetLength() + 1);
	sTemp.ReleaseBuffer();

	//

	pRiga->lIDCampo = lIDCampo;

	//

	pRiga->lTipoCampo = FT_FARMACO;

	//

	pRiga->pCampo = NULL;

	//

	if (m_lIDEsame <= 0)
	{
		// prendo i dati dell'esame precedente //

		long lFaseTemp = CEsamiFarmaciCroniciSet().GetFase(CEsamiSet().GetLastPatientExam(m_pEsamiView->m_pPazientiSet->m_lContatore), lIDCampo);
		if ((lFaseTemp == FARMACO_INIZIO) || (lFaseTemp == FARMACO_CONTINUA))
			pRiga->lFaseFarmaco = FARMACO_CONTINUA;
		else
			pRiga->lFaseFarmaco = FARMACO_NIENTE;
	}
	else
	{
		// prendo i dati dell'esame attuale //

		pRiga->lFaseFarmaco = CEsamiFarmaciCroniciSet().GetFase(m_lIDEsame, lIDCampo);
	}
}

void CCronicitaPazienteRecordDlg::RiempiRecordset()
{
	m_setEsami.m_lData = ConvertMaskString2Date(m_ctrlList.GetItemText(0, 2));

	for(int i = 0; i < m_lNumeroRighe; i++)
	{
		CString sTemp = m_ctrlList.GetItemText(i + 1, 2);

		switch(m_pRighe[i].lTipoCampo)
		{
			case FT_NUMERICO:
			case FT_TESTOLIBERO:
			case FT_LISTAVELOCE:
			{
				(*(CString*)m_pRighe[i].pCampo) = sTemp;
				break;
			}
			case FT_CUSTOM_DATAORA:
			{
				(*(long*)m_pRighe[i].pCampo) = ConvertMaskString2Date(sTemp);
				break;
			}
			case FT_CUSTOM_SOLODATA:
			{
				(*(long*)m_pRighe[i].pCampo) = CCustomDate().SetDate(sTemp);
				break;
			}
			case FT_CUSTOM_SOLOORA:
			{
				(*(long*)m_pRighe[i].pCampo) = CCustomDate().SetTime(sTemp);
				break;
			}
			case FT_SCORE:
			{
				(*(CString*)m_pRighe[i].pCampo) = sTemp;
				break;
			}
			case FT_FARMACO:
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
}