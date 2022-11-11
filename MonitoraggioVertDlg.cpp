#include "stdafx.h"
#include "Endox.h"
#include "Endox.h"
#include "MonitoraggioVertDlg.h"
#include "MonitoraggioUtils.h"
#include "EsamiView.h"
#include "EsamiSet.h"
#include "InfermieriSet.h"

#include "VitalSignDispositiviSet.h"

#include "DLL_Imaging\h\AmLogin.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMonitoraggioVertDlg, CDialog)

CMonitoraggioVertDlg::CMonitoraggioVertDlg(CWnd* pParent, CEsamiView* pEsamiView, long lRecord)
: CDialog(CMonitoraggioVertDlg::IDD, pParent),
m_listaFarmaciDosi(TRUE, TRUE, FALSE)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_lRecord = lRecord;

	m_nPuntiScore1 = 0;
	m_nPuntiScore2 = 0;
	m_nPuntiScore3 = 0;
	m_nPuntiScore4 = 0;
	m_nTotalScore = 0;

	m_nPuntiScore1Glasgow = 0;
	m_nPuntiScore2Glasgow = 0;
	m_nPuntiScore3Glasgow = 0;
	m_nTotalScoreGlasgow = 0;
}

CMonitoraggioVertDlg::~CMonitoraggioVertDlg()
{
	m_setRecord.CloseRecordset("CMonitoraggioVertDlg::~CMonitoraggioVertDlg");
}

BEGIN_MESSAGE_MAP(CMonitoraggioVertDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, OnCbnSelchangeCombo4)

	ON_CBN_SELCHANGE(IDC_COMBO1_GLASGOW, OnCbnSelchangeCombo1Glasgow)
	ON_CBN_SELCHANGE(IDC_COMBO2_GLASGOW, OnCbnSelchangeCombo2Glasgow)
	ON_CBN_SELCHANGE(IDC_COMBO3_GLASGOW2, OnCbnSelchangeCombo3Glasgow)

	ON_BN_CLICKED(IDC_INSERT, OnBnClickedInsert)
	ON_BN_CLICKED(IDC_REMOVE, OnBnClickedRemove)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTA_FARMACI, OnLvnItemchangedListaFarmaci)

	ON_CBN_EDITCHANGE(IDC_COMBO_FARMACI, OnCbnEditChangeComboFarmaci)
	ON_CBN_SELCHANGE(IDC_COMBO_FARMACI, OnCbnSelChangeComboFarmaci)
	ON_CBN_SELCHANGE(IDC_COMBO_VENTILAZIONE, OnCbnSelchangeComboVentilazione)
	ON_CBN_SELCHANGE(IDC_COMBO_DOLORE_SCALA, OnCbnSelchangeComboDoloreScala)
	ON_CBN_SELCHANGE(IDC_COMBO_DOLORE_LOCALIZZAZIONE, &CMonitoraggioVertDlg::OnCbnSelchangeComboDoloreLocalizzazione)
	ON_CBN_SELCHANGE(IDC_COMBO_CCPO_1, &CMonitoraggioVertDlg::OnCbnSelchangeComboCcpo1)
	ON_CBN_SELCHANGE(IDC_COMBO_CCPO_2, &CMonitoraggioVertDlg::OnCbnSelchangeComboCcpo2)
	ON_CBN_SELCHANGE(IDC_COMBO_CCPO_3, &CMonitoraggioVertDlg::OnCbnSelchangeComboCcpo3)
	ON_CBN_SELCHANGE(IDC_COMBO_CCPO_4, &CMonitoraggioVertDlg::OnCbnSelchangeComboCcpo4)
	ON_CBN_SELCHANGE(IDC_COMBO_CCPO_5, &CMonitoraggioVertDlg::OnCbnSelchangeComboCcpo5)
END_MESSAGE_MAP()

void CMonitoraggioVertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_ORA, m_ctrlEditOra);
	DDX_Control(pDX, IDC_EDIT_FC, m_ctrlEditFC);
	DDX_Control(pDX, IDC_EDIT_PA_MIN, m_ctrlEditPAMin);
	DDX_Control(pDX, IDC_EDIT_PA_MAX, m_ctrlEditPAMax);
	DDX_Control(pDX, IDC_EDIT_SAT, m_ctrlEditSat);
	DDX_Control(pDX, IDC_EDIT_O2, m_ctrlEditO2);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlCombo1);
	DDX_Control(pDX, IDC_COMBO2, m_ctrlCombo2);
	DDX_Control(pDX, IDC_COMBO3, m_ctrlCombo3);
	DDX_Control(pDX, IDC_COMBO4, m_ctrlCombo4);
	DDX_Control(pDX, IDC_STATIC_SCORE, m_ctrlStaticScore);

	DDX_Control(pDX, IDC_EDIT_ETCO2, m_ctrlEditETCO2);
	DDX_Control(pDX, IDC_COMBO_POLSO, m_ctrlComboPolso);
	DDX_Control(pDX, IDC_COMBO_INTUBAZIONE, m_ctrlComboIntubazione);
	DDX_Control(pDX, IDC_COMBO_VENTILAZIONE, m_ctrlComboVentilazione);	

	DDX_Control(pDX, IDC_EDIT_VENT_VT, m_ctrlEditVentilazioneVt);
	DDX_Control(pDX, IDC_EDIT_VENT_FR, m_ctrlEditVentilazioneFr);

	DDX_Control(pDX, IDC_COMBO1_GLASGOW, m_ctrlCombo1Glasgow);
	DDX_Control(pDX, IDC_COMBO2_GLASGOW, m_ctrlCombo2Glasgow);
	DDX_Control(pDX, IDC_COMBO3_GLASGOW2, m_ctrlCombo3Glasgow);
	DDX_Control(pDX, IDC_STATIC_SCORE_GLASGOW, m_ctrlStaticScoreGlasgow);

	DDX_Control(pDX, IDC_COMBO_FARMACI, m_ctrlFarmaci);
	DDX_Control(pDX, IDC_EDIT_DOSI, m_ctrlDosi);
	DDX_Control(pDX, IDC_LISTA_FARMACI, m_listaFarmaciDosi);
	DDX_Control(pDX, IDC_INSERT, m_btnInserisci);
	DDX_Control(pDX, IDC_REMOVE, m_btnRimuovi);
	DDX_Control(pDX, IDC_COMBO_INFERMIERE, m_ctrlComboInfermiere);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_STATIC_13, m_ctrlStatic13);
	DDX_Control(pDX, IDC_STATIC_14, m_ctrlStatic14);
	DDX_Control(pDX, IDC_STATIC_15, m_ctrlStatic15);
	DDX_Control(pDX, IDC_STATIC_16, m_ctrlStatic16);
	DDX_Control(pDX, IDC_STATIC_17, m_ctrlStatic17);
	DDX_Control(pDX, IDC_STATIC_18, m_ctrlStatic18);
	DDX_Control(pDX, IDC_STATIC_19, m_ctrlStatic19);
	DDX_Control(pDX, IDC_STATIC_20, m_ctrlStatic20);
	DDX_Control(pDX, IDC_STATIC_21, m_ctrlStatic21);
	DDX_Control(pDX, IDC_STATIC_22, m_ctrlStatic22);
	DDX_Control(pDX, IDC_STATIC_23, m_ctrlStatic23);
	DDX_Control(pDX, IDC_STATIC_24, m_ctrlStatic24);
	DDX_Control(pDX, IDC_STATIC_25, m_ctrlStatic25);
	DDX_Control(pDX, IDC_STATIC_26, m_ctrlStatic26);
	DDX_Control(pDX, IDC_STATIC_27, m_ctrlStatic27);
	DDX_Control(pDX, IDC_STATIC_28, m_ctrlStatic28);
	DDX_Control(pDX, IDC_STATIC_29, m_ctrlStatic29);
	DDX_Control(pDX, IDC_STATIC_30, m_ctrlStatic30);
	DDX_Control(pDX, IDC_STATIC_31, m_ctrlStatic31);
	DDX_Control(pDX, IDC_STATIC_32, m_ctrlStatic32);
	DDX_Control(pDX, IDC_STATIC_33, m_ctrlStatic33);
	DDX_Control(pDX, IDC_STATIC_34, m_ctrlStatic34);
	DDX_Control(pDX, IDC_STATIC_35, m_ctrlStatic35);
	DDX_Control(pDX, IDC_STATIC_36, m_ctrlStatic36);
	DDX_Control(pDX, IDC_STATIC_37, m_ctrlStatic37);
	DDX_Control(pDX, IDC_STATIC_38, m_ctrlStatic38);
	DDX_Control(pDX, IDC_STATIC_39, m_ctrlStatic39);	

	DDX_Control(pDX, IDC_STATIC_FARMACI, m_ctrlStaticFarmaci);
	DDX_Control(pDX, IDC_STATIC_LABEL3, m_ctrlStaticLabel3);
	DDX_Control(pDX, IDC_STATIC_LABEL6, m_ctrlStaticLabel6);
	DDX_Control(pDX, IDC_STATIC_LABEL7, m_ctrlStaticLabel7);

	DDX_Control(pDX, IDC_STATIC_1_GLASGOW, m_ctrlStatic1Glasgow);
	DDX_Control(pDX, IDC_STATIC_2_GLASGOW, m_ctrlStatic2Glasgow);
	DDX_Control(pDX, IDC_STATIC_3_GLASGOW, m_ctrlStatic3Glasgow);
	DDX_Control(pDX, IDC_STATIC_4_GLASGOW, m_ctrlStatic4Glasgow);

	DDX_Control(pDX, IDC_COMBO_DOLORE_SCALA, m_ctrlComboDoloreScala);
	DDX_Control(pDX, IDC_COMBO_DOLORE_VAS, m_ctrlComboDoloreVAS);
	DDX_Control(pDX, IDC_COMBO_DOLORE_NRS, m_ctrlComboDoloreNRS);
	DDX_Control(pDX, IDC_COMBO_DOLORE_WB, m_ctrlComboDoloreWB);
	DDX_Control(pDX, IDC_COMBO_CCPO_1, m_ctrlComboDoloreCCPO1);
	DDX_Control(pDX, IDC_COMBO_CCPO_2, m_ctrlComboDoloreCCPO2);
	DDX_Control(pDX, IDC_COMBO_CCPO_3, m_ctrlComboDoloreCCPO3);
	DDX_Control(pDX, IDC_COMBO_CCPO_4, m_ctrlComboDoloreCCPO4);
	DDX_Control(pDX, IDC_COMBO_CCPO_5, m_ctrlComboDoloreCCPO5);
	DDX_Control(pDX, IDC_COMBO_DOLORE_LOCALIZZAZIONE, m_ctrlComboDoloreLocalizzazione);
	DDX_Control(pDX, IDC_EDIT_LOCALIZZAZIONE_DETT, m_ctrlEditDoloreLocalizzazioneDettaglio);
	DDX_Control(pDX, IDC_COMBO_DOLORE_CARATTERISTICHE, m_ctrlComboDoloreCaratteristiche);
	DDX_Control(pDX, IDC_COMBO_DOLORE_FREQUENZA, m_ctrlComboDoloreFrequenza);
	DDX_Control(pDX, IDC_COMBO_DOLORE_DURATA, m_ctrlComboDoloreDurata);
	DDX_Control(pDX, IDC_COMBO_RAMSEY, m_ctrlComboRamsey);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);		

	// Non posso più fare così altrimenti settare il valore di default mi diventa complicatissimo
	//DDX_FieldInfermieriCombo(pDX, IDC_COMBO_INFERMIERE, m_setRecord.m_lIdInfermiere, &m_setRecord);	

	//Primo step, metto lo zero se trovo vuoto
	CString temp;
	GetDlgItem(IDC_STATIC_SCORE)->GetWindowText(temp);
	temp.Format("%li", atoi(temp));
	GetDlgItem(IDC_STATIC_SCORE)->SetWindowText(temp);
	GetDlgItem(IDC_STATIC_SCORE_GLASGOW)->GetWindowText(temp);
	temp.Format("%li", atoi(temp));
	GetDlgItem(IDC_STATIC_SCORE_GLASGOW)->SetWindowText(temp);

	//Secondo step, scambio il campo
	DDX_Text(pDX, IDC_STATIC_SCORE, m_nTotalScore);
	DDX_Text(pDX, IDC_STATIC_SCORE_GLASGOW, m_nTotalScoreGlasgow);

	//Terzo step, tolgo l'eventuale zero
	if (m_nTotalScore == 0)
		GetDlgItem(IDC_STATIC_SCORE)->SetWindowText("");
	if (m_nTotalScoreGlasgow == 0)
		GetDlgItem(IDC_STATIC_SCORE_GLASGOW)->SetWindowText("");
	//	

	if (m_nTotalScore < 4)
	{
		m_colorScore = theApp.m_color[0]; // rosso
	}
	else
	{
		if (m_nTotalScore < 12)
		{
			m_colorScore = theApp.m_color[1]; // giallo
		}
		else
		{
			if (m_nTotalScore < 16)
			{
				m_colorScore = theApp.m_color[2]; // verde
			}
			else
			{
				if (m_nTotalScore < 20)
					m_colorScore = theApp.m_color[3]; // azzurro
				else
					m_colorScore = theApp.m_color[4]; // blu
			}
		}
	}

	//Per Glasgow il colore del punteggio lo lascio nero
	//

	GetDlgItem(IDC_STATIC_17)->RedrawWindow();
	m_ctrlStaticScore.RedrawWindow();
	GetDlgItem(IDC_STATIC_4_GLASGOW)->RedrawWindow();
	m_ctrlStaticScoreGlasgow.RedrawWindow();
	DDX_Control(pDX, IDC_COMBO_FASE, m_ctrlFase);
	//DDX_Control(pDX, IDC_COMBO_DOLORE, m_ctrlDolore);
}

BOOL CMonitoraggioVertDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();					

	RiempiComboFase();
	RiempiCombo1();
	RiempiCombo2();
	RiempiCombo3();
	RiempiCombo4();
	RiempiComboInfermieri();
	RiempiComboPolso();
	RiempiComboIntubazione();
	RiempiComboVentilazione();	
	RiempiComboDoloreScala();
	RiempiComboDoloreVAS();
	RiempiComboDoloreNRS();
	RiempiComboDoloreWB();
	RiempiComboDoloreCCPO1();
	RiempiComboDoloreCCPO2();
	RiempiComboDoloreCCPO3();
	RiempiComboDoloreCCPO4();
	RiempiComboDoloreCCPO5();
	RiempiComboDoloreLocalizzazione();
	RiempiComboDoloreCaratteristiche();
	RiempiComboDoloreFrequenza();
	RiempiComboDoloreDurata();
	RiempiComboRamsey();
	RiempiComboGlasgow();
	RiempiListaFarmaci();	

	GetDlgItem(IDC_STATIC_CCPO_TOTALE)->SetFont(&theApp.m_fontBold);

	theApp.LocalizeDialog(this, CMonitoraggioVertDlg::IDD, "MonitoraggioVertDlg");

	if (m_lRecord <= 0)
	{
		//Se decido di acquisire con Vital Sign, non mostro nemmeno i dati da inserire. Parte il PRE
		if (theApp.m_bVitalSignIntegrazioneAttiva && theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MONITORAGGIO_AVVIARE_DISPOSITIVO), MB_YESNO) == IDYES)
		{
			CDialog::OnOK();
			return TRUE;
		}

		CString strFilter;
		strFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		SetWindowText(theApp.GetMessageString(IDS_MONITORAGGIO_NEW));

		m_setRecord.SetOpenFilter(strFilter);
		m_setRecord.OpenRecordset("CMonitoraggioDlg::OnInitDialog");		

		SYSTEMTIME stime;
		GetLocalTime(&stime);

		CString strTemp;
		strTemp.Format("%02d.%02d.%02d", stime.wHour, stime.wMinute, stime.wSecond);
		m_ctrlEditOra.SetWindowText(strTemp);		

		if (theApp.m_bMostraScoreMonitoraggio)
		{
			m_ctrlCombo1.SetCurSel(0);
			m_ctrlCombo2.SetCurSel(0);
			m_ctrlCombo3.SetCurSel(0);
			m_ctrlCombo4.SetCurSel(0);
			//m_ctrlDolore.SetCurSel(0);

			m_ctrlCombo1Glasgow.SetCurSel(4);
			m_ctrlCombo2Glasgow.SetCurSel(5);
			m_ctrlCombo3Glasgow.SetCurSel(6);

			if (theApp.m_bUsaScoreDiGlasgow)
				RecalculateGlasgow();
			else
				OnCbnSelchangeCombo4();
		}		

		//Setto l'infermiere attualmente collegato
		long lUserId = -1;
		AMLogin_GetUserID(&lUserId);
		if (lUserId > 0)
		{
			long idInfermiere = CInfermieriSet().GetContatoreFromUserID(lUserId);

			if (idInfermiere > 0)
			{
				for (int i = 0; i < m_ctrlComboInfermiere.GetCount(); i++)
				{
					if (m_ctrlComboInfermiere.GetItemData(i) == idInfermiere)
					{
						m_ctrlComboInfermiere.SetCurSel(i);
						break;
					}
				}
			}
		}

		
		m_ctrlComboDoloreVAS.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreNRS.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreWB.ShowWindow(SW_HIDE);		
		m_ctrlStatic34.ShowWindow(SW_HIDE);
		m_ctrlStatic35.ShowWindow(SW_HIDE);
		m_ctrlStatic36.ShowWindow(SW_HIDE);
		m_ctrlStatic37.ShowWindow(SW_HIDE);
		m_ctrlStatic38.ShowWindow(SW_HIDE);
		m_ctrlStatic39.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO1.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO2.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO3.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO4.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO5.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CCPO_TOTALE)->ShowWindow(SW_HIDE);

		m_ctrlComboDoloreScala.SetCurSel(theApp.m_nMonitoraggioDoloreDefault);
		DoloreScalaSelChange();
	}
	else
	{
		CString strFilter;
		strFilter.Format("ID=%li", m_lRecord);

		SetWindowText(theApp.GetMessageString(IDS_MONITORAGGIO_MOD));

		m_setRecord.SetOpenFilter(strFilter);
		if (m_setRecord.OpenRecordset("CMonitoraggioDlg::OnInitDialog"))
		{
			if (!m_setRecord.IsEOF())
			{
				CString strTemp;

				if (!m_setRecord.IsFieldNull(&m_setRecord.m_lQuando))
					m_ctrlFase.SetCurSel(m_setRecord.m_lQuando-1);
				else
					m_ctrlFase.SetCurSel(0);

				m_ctrlEditOra.SetWindowText(m_setRecord.m_strOra);
				
				//Carico l'infermiere
				for (int i = 0; i < m_ctrlComboInfermiere.GetCount(); i++)
				{
					if (m_ctrlComboInfermiere.GetItemData(i) == m_setRecord.m_lIdInfermiere)
					{
						m_ctrlComboInfermiere.SetCurSel(i);
						break;
					}
				}

				//

				m_ctrlEditFC.SetWindowText(m_setRecord.m_strFC);

				for (int i = 0; i < m_ctrlComboPolso.GetCount(); i++)
				{
					if (m_ctrlComboPolso.GetItemData(i) == m_setRecord.m_lFCPolso)
					{
						m_ctrlComboPolso.SetCurSel(i);
						break;
					}
				}

				int iMiddle = m_setRecord.m_strPA.Find("/");
				CString PAMin = m_setRecord.m_strPA.Left(iMiddle);
				CString PAMax = m_setRecord.m_strPA.Right(m_setRecord.m_strPA.GetLength() - (iMiddle + 1));
				m_ctrlEditPAMin.SetWindowText(PAMin);
				m_ctrlEditPAMax.SetWindowText(PAMax);
				m_ctrlEditSat.SetWindowText(m_setRecord.m_strSat);
				m_ctrlEditO2.SetWindowText(m_setRecord.m_strO2);
				m_ctrlEditETCO2.SetWindowText(m_setRecord.m_strETCO2);

				for (int i = 0; i < m_ctrlComboIntubazione.GetCount(); i++)
				{
					if (m_ctrlComboIntubazione.GetItemData(i) == m_setRecord.m_lIntubazione)
					{
						m_ctrlComboIntubazione.SetCurSel(i);
						break;
					}
				}

				for (int i = 0; i < m_ctrlComboVentilazione.GetCount(); i++)
				{
					if (m_ctrlComboVentilazione.GetItemData(i) == m_setRecord.m_lVentilazione)
					{
						m_ctrlComboVentilazione.SetCurSel(i);
						CheckVentilazione();
						break;
					}
				}

				m_ctrlEditVentilazioneVt.SetWindowText(m_setRecord.m_strVentilazioneVt);
				m_ctrlEditVentilazioneFr.SetWindowText(m_setRecord.m_strVentilazioneFr);

				//

				for (int i = 0; i < m_ctrlComboDoloreScala.GetCount(); i++)
				{
					if (m_ctrlComboDoloreScala.GetItemData(i) == m_setRecord.m_lDoloreScala)
					{
						m_ctrlComboDoloreScala.SetCurSel(i);
						break;
					}
				}

				if (m_setRecord.m_lDoloreScala == 1) //VAS
				{
					m_ctrlComboDoloreVAS.ShowWindow(SW_SHOW);
					m_ctrlComboDoloreNRS.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreWB.ShowWindow(SW_HIDE);
					m_ctrlStatic34.ShowWindow(SW_HIDE);
					m_ctrlStatic35.ShowWindow(SW_HIDE);
					m_ctrlStatic36.ShowWindow(SW_HIDE);
					m_ctrlStatic37.ShowWindow(SW_HIDE);
					m_ctrlStatic38.ShowWindow(SW_HIDE);
					m_ctrlStatic39.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO1.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO2.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO3.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO4.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO5.ShowWindow(SW_HIDE);
					GetDlgItem(IDC_STATIC_CCPO_TOTALE)->ShowWindow(SW_HIDE);

					for (int i = 0; i < m_ctrlComboDoloreVAS.GetCount(); i++)
					{
						if (m_ctrlComboDoloreVAS.GetItemData(i) == m_setRecord.m_lDoloreVAS)
						{
							m_ctrlComboDoloreVAS.SetCurSel(i);
							break;
						}
					}
				}
				else if (m_setRecord.m_lDoloreScala == 2) //NRS
				{
					m_ctrlComboDoloreVAS.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreNRS.ShowWindow(SW_SHOW);
					m_ctrlComboDoloreWB.ShowWindow(SW_HIDE);
					m_ctrlStatic34.ShowWindow(SW_HIDE);
					m_ctrlStatic35.ShowWindow(SW_HIDE);
					m_ctrlStatic36.ShowWindow(SW_HIDE);
					m_ctrlStatic37.ShowWindow(SW_HIDE);
					m_ctrlStatic38.ShowWindow(SW_HIDE);
					m_ctrlStatic39.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO1.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO2.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO3.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO4.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO5.ShowWindow(SW_HIDE);
					GetDlgItem(IDC_STATIC_CCPO_TOTALE)->ShowWindow(SW_HIDE);

					for (int i = 0; i < m_ctrlComboDoloreNRS.GetCount(); i++)
					{
						if (m_ctrlComboDoloreNRS.GetItemData(i) == m_setRecord.m_lDoloreNRS)
						{
							m_ctrlComboDoloreNRS.SetCurSel(i);
							break;
						}
					}
				}
				else if (m_setRecord.m_lDoloreScala == 3) //WB
				{
					m_ctrlComboDoloreVAS.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreNRS.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreWB.ShowWindow(SW_SHOW);
					m_ctrlStatic34.ShowWindow(SW_HIDE);
					m_ctrlStatic35.ShowWindow(SW_HIDE);
					m_ctrlStatic36.ShowWindow(SW_HIDE);
					m_ctrlStatic37.ShowWindow(SW_HIDE);
					m_ctrlStatic38.ShowWindow(SW_HIDE);
					m_ctrlStatic39.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO1.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO2.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO3.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO4.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreCCPO5.ShowWindow(SW_HIDE);
					GetDlgItem(IDC_STATIC_CCPO_TOTALE)->ShowWindow(SW_HIDE);

					for (int i = 0; i < m_ctrlComboDoloreWB.GetCount(); i++)
					{
						if (m_ctrlComboDoloreWB.GetItemData(i) == m_setRecord.m_lDoloreWB)
						{
							m_ctrlComboDoloreWB.SetCurSel(i);
							break;
						}
					}
				}
				else if (m_setRecord.m_lDoloreScala == 4) //CCPO
				{
					m_ctrlComboDoloreVAS.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreNRS.ShowWindow(SW_HIDE);
					m_ctrlComboDoloreWB.ShowWindow(SW_HIDE);
					m_ctrlStatic34.ShowWindow(SW_SHOW);
					m_ctrlStatic35.ShowWindow(SW_SHOW);
					m_ctrlStatic36.ShowWindow(SW_SHOW);
					m_ctrlStatic37.ShowWindow(SW_SHOW);
					m_ctrlStatic38.ShowWindow(SW_SHOW);
					m_ctrlStatic39.ShowWindow(SW_SHOW);
					m_ctrlComboDoloreCCPO1.ShowWindow(SW_SHOW);
					m_ctrlComboDoloreCCPO2.ShowWindow(SW_SHOW);
					m_ctrlComboDoloreCCPO3.ShowWindow(SW_SHOW);
					m_ctrlComboDoloreCCPO4.ShowWindow(SW_SHOW);
					m_ctrlComboDoloreCCPO5.ShowWindow(SW_SHOW);
					GetDlgItem(IDC_STATIC_CCPO_TOTALE)->ShowWindow(SW_SHOW);

					for (int i = 0; i < m_ctrlComboDoloreCCPO1.GetCount(); i++)
					{
						if (m_ctrlComboDoloreCCPO1.GetItemData(i) == m_setRecord.m_lDoloreCCPO1)
						{
							m_ctrlComboDoloreCCPO1.SetCurSel(i);
							break;
						}
					}

					for (int i = 0; i < m_ctrlComboDoloreCCPO2.GetCount(); i++)
					{
						if (m_ctrlComboDoloreCCPO2.GetItemData(i) == m_setRecord.m_lDoloreCCPO2)
						{
							m_ctrlComboDoloreCCPO2.SetCurSel(i);
							break;
						}
					}

					for (int i = 0; i < m_ctrlComboDoloreCCPO3.GetCount(); i++)
					{
						if (m_ctrlComboDoloreCCPO3.GetItemData(i) == m_setRecord.m_lDoloreCCPO3)
						{
							m_ctrlComboDoloreCCPO3.SetCurSel(i);
							break;
						}
					}

					for (int i = 0; i < m_ctrlComboDoloreCCPO4.GetCount(); i++)
					{
						if (m_ctrlComboDoloreCCPO4.GetItemData(i) == m_setRecord.m_lDoloreCCPO4)
						{
							m_ctrlComboDoloreCCPO4.SetCurSel(i);
							break;
						}
					}

					for (int i = 0; i < m_ctrlComboDoloreCCPO5.GetCount(); i++)
					{
						if (m_ctrlComboDoloreCCPO5.GetItemData(i) == m_setRecord.m_lDoloreCCPO5)
						{
							m_ctrlComboDoloreCCPO5.SetCurSel(i);
							break;
						}
					}
				}				

				for (int i = 0; i < m_ctrlComboDoloreLocalizzazione.GetCount(); i++)
				{
					if (m_ctrlComboDoloreLocalizzazione.GetItemData(i) == m_setRecord.m_lDoloreLocalizzazione)
					{
						m_ctrlComboDoloreLocalizzazione.SetCurSel(i);
						break;
					}
				}

				m_ctrlEditDoloreLocalizzazioneDettaglio.SetWindowText(m_setRecord.m_sDoloreLocalizzazioneDettaglio);
				if (m_setRecord.m_lDoloreLocalizzazione > 0)
					m_ctrlEditDoloreLocalizzazioneDettaglio.EnableWindow(TRUE);
				
				for (int i = 0; i < m_ctrlComboDoloreCaratteristiche.GetCount(); i++)
				{
					if (m_ctrlComboDoloreCaratteristiche.GetItemData(i) == m_setRecord.m_lDoloreCaratteristiche)
					{
						m_ctrlComboDoloreCaratteristiche.SetCurSel(i);
						break;
					}
				}

				for (int i = 0; i < m_ctrlComboDoloreFrequenza.GetCount(); i++)
				{
					if (m_ctrlComboDoloreFrequenza.GetItemData(i) == m_setRecord.m_lDoloreFrequenza)
					{
						m_ctrlComboDoloreFrequenza.SetCurSel(i);
						break;
					}
				}

				for (int i = 0; i < m_ctrlComboDoloreDurata.GetCount(); i++)
				{
					if (m_ctrlComboDoloreDurata.GetItemData(i) == m_setRecord.m_lDoloreDurata)
					{
						m_ctrlComboDoloreDurata.SetCurSel(i);
						break;
					}
				}

				for (int i = 0; i < m_ctrlComboRamsey.GetCount(); i++)
				{
					if (m_ctrlComboRamsey.GetItemData(i) == m_setRecord.m_lRamsay)
					{
						m_ctrlComboRamsey.SetCurSel(i);
						break;
					}
				}

				//

				if (theApp.m_bMostraScoreMonitoraggio)
				{
					for (int i = 0; i < m_ctrlCombo1.GetCount(); i++)
					{
						if (m_ctrlCombo1.GetItemData(i) == m_setRecord.m_lPuntiScore1)
						{
							m_ctrlCombo1.SetCurSel(i);
							break;
						}
					}

					for (int i = 0; i < m_ctrlCombo2.GetCount(); i++)
					{
						if (m_ctrlCombo2.GetItemData(i) == m_setRecord.m_lPuntiScore2)
						{
							m_ctrlCombo2.SetCurSel(i);
							break;
						}
					}

					for (int i = 0; i < m_ctrlCombo3.GetCount(); i++)
					{
						if (m_ctrlCombo3.GetItemData(i) == m_setRecord.m_lPuntiScore3)
						{
							m_ctrlCombo3.SetCurSel(i);
							break;
						}
					}

					for (int i = 0; i < m_ctrlCombo4.GetCount(); i++)
					{
						if (m_ctrlCombo4.GetItemData(i) == m_setRecord.m_lPuntiScore4)
						{
							m_ctrlCombo4.SetCurSel(i);
							break;
						}
					}

					//GLASGOW
					for (int i = 0; i < m_ctrlCombo1Glasgow.GetCount(); i++)
					{
						if (m_ctrlCombo1Glasgow.GetItemData(i) == m_setRecord.m_lPuntiScore1Glasgow)
						{
							m_ctrlCombo1Glasgow.SetCurSel(i);
							break;
						}
					}

					for (int i = 0; i < m_ctrlCombo2Glasgow.GetCount(); i++)
					{
						if (m_ctrlCombo2Glasgow.GetItemData(i) == m_setRecord.m_lPuntiScore2Glasgow)
						{
							m_ctrlCombo2Glasgow.SetCurSel(i);
							break;
						}
					}

					for (int i = 0; i < m_ctrlCombo3Glasgow.GetCount(); i++)
					{
						if (m_ctrlCombo3Glasgow.GetItemData(i) == m_setRecord.m_lPuntiScore3Glasgow)
						{
							m_ctrlCombo3Glasgow.SetCurSel(i);
							break;
						}
					}
				}

				//

				CFarmaciMonitoraggioSet setFarmaci;
				CString filter;
				filter.Format("IDMonitoraggio = %li", m_setRecord.m_lID);
				m_monitoraggioFarmaciDosiSet.SetOpenFilter(filter);
				if (m_monitoraggioFarmaciDosiSet.OpenRecordset("CMonitoraggioVertDlg::OnInitDialog"))
				{
					while (!m_monitoraggioFarmaciDosiSet.IsEOF())
					{
						int riga = m_listaFarmaciDosi.GetItemCount();
						CString filterFar;
						filterFar.Format("Id = %li", m_monitoraggioFarmaciDosiSet.m_lIDFarmaco);
						setFarmaci.SetOpenFilter(filterFar);
						if (setFarmaci.OpenRecordset("CMonitoraggioVertDlg::OnInitDialog"))
						{
							m_listaFarmaciDosi.InsertItem(riga, setFarmaci.m_sNome);
							m_listaFarmaciDosi.SetItemData(riga, m_monitoraggioFarmaciDosiSet.m_lIDFarmaco);
							m_listaFarmaciDosi.SetItemText(riga, 1, m_monitoraggioFarmaciDosiSet.m_sDose);
							setFarmaci.CloseRecordset("CMonitoraggioVertDynForm::OnFormLoad");
						}
						m_monitoraggioFarmaciDosiSet.MoveNext();
					}

					m_monitoraggioFarmaciDosiSet.CloseRecordset("CMonitoraggioVertDynForm::OnFormLoad");
				}				

				UpdateData(FALSE);

				if (theApp.m_bMostraScoreMonitoraggio)
				{
					if (theApp.m_bUsaScoreDiGlasgow)
						RecalculateGlasgow();
					else
						OnCbnSelchangeCombo4();
				}
			}
		}
	}

	m_btnInserisci.EnableWindow(FALSE);

	//Se uso lo score di glasgow mostro i controlli e nascondo quelli di Chernik
	CRect scoreRect;
	m_ctrlStatic20.GetWindowRect(&scoreRect);
	m_ctrlStatic20.ShowWindow(theApp.m_bMostraScoreMonitoraggio);

	//Glasgow
	m_ctrlStatic1Glasgow.ShowWindow(theApp.m_bMostraScoreMonitoraggio && theApp.m_bUsaScoreDiGlasgow);
	m_ctrlStatic2Glasgow.ShowWindow(theApp.m_bMostraScoreMonitoraggio && theApp.m_bUsaScoreDiGlasgow);
	m_ctrlStatic3Glasgow.ShowWindow(theApp.m_bMostraScoreMonitoraggio && theApp.m_bUsaScoreDiGlasgow);
	m_ctrlStatic4Glasgow.ShowWindow(theApp.m_bMostraScoreMonitoraggio && theApp.m_bUsaScoreDiGlasgow);
	m_ctrlStaticScoreGlasgow.ShowWindow(theApp.m_bMostraScoreMonitoraggio && theApp.m_bUsaScoreDiGlasgow);
	m_ctrlCombo1Glasgow.ShowWindow(theApp.m_bMostraScoreMonitoraggio && theApp.m_bUsaScoreDiGlasgow);
	m_ctrlCombo2Glasgow.ShowWindow(theApp.m_bMostraScoreMonitoraggio && theApp.m_bUsaScoreDiGlasgow);
	m_ctrlCombo3Glasgow.ShowWindow(theApp.m_bMostraScoreMonitoraggio && theApp.m_bUsaScoreDiGlasgow);

	//Chernik
	m_ctrlStatic13.ShowWindow(theApp.m_bMostraScoreMonitoraggio && !theApp.m_bUsaScoreDiGlasgow);
	m_ctrlStatic14.ShowWindow(theApp.m_bMostraScoreMonitoraggio && !theApp.m_bUsaScoreDiGlasgow);
	m_ctrlStatic15.ShowWindow(theApp.m_bMostraScoreMonitoraggio && !theApp.m_bUsaScoreDiGlasgow);
	m_ctrlStatic16.ShowWindow(theApp.m_bMostraScoreMonitoraggio && !theApp.m_bUsaScoreDiGlasgow);
	m_ctrlStatic17.ShowWindow(theApp.m_bMostraScoreMonitoraggio && !theApp.m_bUsaScoreDiGlasgow);
	m_ctrlStaticScore.ShowWindow(theApp.m_bMostraScoreMonitoraggio && !theApp.m_bUsaScoreDiGlasgow);
	m_ctrlCombo1.ShowWindow(theApp.m_bMostraScoreMonitoraggio && !theApp.m_bUsaScoreDiGlasgow);
	m_ctrlCombo2.ShowWindow(theApp.m_bMostraScoreMonitoraggio && !theApp.m_bUsaScoreDiGlasgow);
	m_ctrlCombo3.ShowWindow(theApp.m_bMostraScoreMonitoraggio && !theApp.m_bUsaScoreDiGlasgow);
	m_ctrlCombo4.ShowWindow(theApp.m_bMostraScoreMonitoraggio && !theApp.m_bUsaScoreDiGlasgow);	

	if (!theApp.m_bMostraScoreMonitoraggio)
	{
		CRect dialogRect;
		GetWindowRect(&dialogRect);

		dialogRect.right = dialogRect.right - scoreRect.Width();		
		SetWindowPos(NULL, dialogRect.left, dialogRect.top, dialogRect.right, dialogRect.bottom, SWP_NOOWNERZORDER);

		CenterWindow();
	}

	return bReturn;
}

void CMonitoraggioVertDlg::OnOK()
{
	if (m_ctrlFase.GetItemData(m_ctrlFase.GetCurSel()) <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MONITORAGGIO_SELEZIONAREFASE));
		return;
	}

	if (m_lRecord <= 0) // addnew //
	{
		if (m_setRecord.AddNewRecordset("CMonitoraggioDlg::OnOK"))
		{
			m_setRecord.m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;

			UpdateDB();

			if (m_setRecord.UpdateRecordset("CMonitoraggioDlg::OnOK"))
				m_lRecord = m_setRecord.GetLastAdd();
		}
	}
	else // edit //
	{
		if (m_setRecord.EditRecordset("CMonitoraggioDlg::OnOK"))
		{	
			UpdateDB();

			if (m_setRecord.UpdateRecordset("CMonitoraggioDlg::OnOK"))
				m_lRecord = m_setRecord.m_lID;
		}
	}

	// Elimino tutti i riferimenti al monitoraggio se esistono
	CString strFilter;
	strFilter.Format("IDMonitoraggio=%li", m_lRecord);

	m_monitoraggioFarmaciDosiSet.SetOpenFilter(strFilter);
	if (m_monitoraggioFarmaciDosiSet.OpenRecordset("CMonitoraggioVertDlg::OnOk"))
	{
		while (!m_monitoraggioFarmaciDosiSet.IsEOF())
		{
			m_monitoraggioFarmaciDosiSet.DeleteRecordset("CMonitoraggioVertDlg::OnOk");
			m_monitoraggioFarmaciDosiSet.MoveNext();
		}

		m_monitoraggioFarmaciDosiSet.CloseRecordset("CMonitoraggioVertDlg::OnOk");
	}

	// Inserisco i farmaci relativi al monitoraggio
	if (m_monitoraggioFarmaciDosiSet.OpenRecordset("CMonitoraggioVertDlg::OnOk"))
	{
		for (int i = 0; i < m_listaFarmaciDosi.GetItemCount(); i++)
		{
			int idFarmaco = m_listaFarmaciDosi.GetItemData(i);
			CString strDose, strDurata;
			strDose = m_listaFarmaciDosi.GetItemText(i, 1);
			if (m_monitoraggioFarmaciDosiSet.AddNewRecordset("CMonitoraggioVertDlg::OnOk"))
			{
				m_monitoraggioFarmaciDosiSet.m_lIDMonitoraggio = m_lRecord;
				m_monitoraggioFarmaciDosiSet.m_lIDFarmaco = idFarmaco;
				m_monitoraggioFarmaciDosiSet.m_sDose = strDose;
				m_monitoraggioFarmaciDosiSet.UpdateRecordset("CMonitoraggioVertDlg::OnOk");
			}
		}

		m_monitoraggioFarmaciDosiSet.CloseRecordset("CMonitoraggioVertDlg::OnOk");
	}

	CDialog::OnOK();
}

void CMonitoraggioVertDlg::UpdateDB()
{
	m_setRecord.m_lQuando = m_ctrlFase.GetItemData(m_ctrlFase.GetCurSel());

	m_ctrlEditOra.GetWindowText(m_setRecord.m_strOra);
	m_setRecord.m_lIdInfermiere = m_ctrlComboInfermiere.GetItemData(m_ctrlComboInfermiere.GetCurSel());

	//

	m_ctrlEditFC.GetWindowText(m_setRecord.m_strFC);
	m_setRecord.m_lFCPolso = m_ctrlComboPolso.GetItemData(m_ctrlComboPolso.GetCurSel());
	CString PAMin, PAMax;
	m_ctrlEditPAMin.GetWindowText(PAMin);
	m_ctrlEditPAMax.GetWindowText(PAMax);
	m_setRecord.m_strPA.Format("%s/%s", PAMin, PAMax);
	m_ctrlEditSat.GetWindowText(m_setRecord.m_strSat);
	m_ctrlEditO2.GetWindowText(m_setRecord.m_strO2);
	m_ctrlEditETCO2.GetWindowText(m_setRecord.m_strETCO2);
	m_setRecord.m_lIntubazione = m_ctrlComboIntubazione.GetItemData(m_ctrlComboIntubazione.GetCurSel());
	m_setRecord.m_lVentilazione = m_ctrlComboVentilazione.GetItemData(m_ctrlComboVentilazione.GetCurSel());
	m_ctrlEditVentilazioneVt.GetWindowText(m_setRecord.m_strVentilazioneVt);
	m_ctrlEditVentilazioneFr.GetWindowText(m_setRecord.m_strVentilazioneFr);

	//

	m_setRecord.m_lDoloreScala = m_ctrlComboDoloreScala.GetItemData(m_ctrlComboDoloreScala.GetCurSel());

	if (m_setRecord.m_lDoloreScala == 1)
	{
		m_setRecord.m_lDoloreNRS = 0;
		m_setRecord.m_lDoloreWB = 0;
		m_setRecord.m_lDoloreVAS = m_ctrlComboDoloreVAS.GetItemData(m_ctrlComboDoloreVAS.GetCurSel());
		m_setRecord.m_lDoloreCCPO1 = 0;
		m_setRecord.m_lDoloreCCPO2 = 0;
		m_setRecord.m_lDoloreCCPO3 = 0;
		m_setRecord.m_lDoloreCCPO4 = 0;
		m_setRecord.m_lDoloreCCPO5 = 0;
	}
	else if (m_setRecord.m_lDoloreScala == 2)
	{
		m_setRecord.m_lDoloreVAS = 0;
		m_setRecord.m_lDoloreWB = 0;
		m_setRecord.m_lDoloreNRS = m_ctrlComboDoloreNRS.GetItemData(m_ctrlComboDoloreNRS.GetCurSel());
		m_setRecord.m_lDoloreCCPO1 = 0;
		m_setRecord.m_lDoloreCCPO2 = 0;
		m_setRecord.m_lDoloreCCPO3 = 0;
		m_setRecord.m_lDoloreCCPO4 = 0;
		m_setRecord.m_lDoloreCCPO5 = 0;
	}
	else if (m_setRecord.m_lDoloreScala == 3)
	{
		m_setRecord.m_lDoloreVAS = 0;
		m_setRecord.m_lDoloreNRS = 0;
		m_setRecord.m_lDoloreWB = m_ctrlComboDoloreWB.GetItemData(m_ctrlComboDoloreWB.GetCurSel());
		m_setRecord.m_lDoloreCCPO1 = 0;
		m_setRecord.m_lDoloreCCPO2 = 0;
		m_setRecord.m_lDoloreCCPO3 = 0;
		m_setRecord.m_lDoloreCCPO4 = 0;
		m_setRecord.m_lDoloreCCPO5 = 0;
	}
	else if (m_setRecord.m_lDoloreScala == 4)
	{
		m_setRecord.m_lDoloreVAS = 0;
		m_setRecord.m_lDoloreNRS = 0;
		m_setRecord.m_lDoloreWB = 0;
		m_setRecord.m_lDoloreCCPO1 = m_ctrlComboDoloreCCPO1.GetItemData(m_ctrlComboDoloreCCPO1.GetCurSel());
		m_setRecord.m_lDoloreCCPO2 = m_ctrlComboDoloreCCPO2.GetItemData(m_ctrlComboDoloreCCPO2.GetCurSel());
		m_setRecord.m_lDoloreCCPO3 = m_ctrlComboDoloreCCPO3.GetItemData(m_ctrlComboDoloreCCPO3.GetCurSel());
		m_setRecord.m_lDoloreCCPO4 = m_ctrlComboDoloreCCPO4.GetItemData(m_ctrlComboDoloreCCPO4.GetCurSel());
		m_setRecord.m_lDoloreCCPO5 = m_ctrlComboDoloreCCPO5.GetItemData(m_ctrlComboDoloreCCPO5.GetCurSel());
	}

	m_setRecord.m_lDoloreLocalizzazione = m_ctrlComboDoloreLocalizzazione.GetItemData(m_ctrlComboDoloreLocalizzazione.GetCurSel());
	m_ctrlEditDoloreLocalizzazioneDettaglio.GetWindowText(m_setRecord.m_sDoloreLocalizzazioneDettaglio);
	m_setRecord.m_lDoloreCaratteristiche = m_ctrlComboDoloreCaratteristiche.GetItemData(m_ctrlComboDoloreCaratteristiche.GetCurSel());
	m_setRecord.m_lDoloreFrequenza = m_ctrlComboDoloreFrequenza.GetItemData(m_ctrlComboDoloreFrequenza.GetCurSel());
	m_setRecord.m_lDoloreDurata = m_ctrlComboDoloreDurata.GetItemData(m_ctrlComboDoloreDurata.GetCurSel());
	m_setRecord.m_lRamsay = m_ctrlComboRamsey.GetItemData(m_ctrlComboRamsey.GetCurSel());

	//

	if (theApp.m_bMostraScoreMonitoraggio)
	{
		m_setRecord.m_lPuntiScore1 = m_ctrlCombo1.GetItemData(m_ctrlCombo1.GetCurSel());
		m_setRecord.m_lPuntiScore2 = m_ctrlCombo1.GetItemData(m_ctrlCombo2.GetCurSel());
		m_setRecord.m_lPuntiScore3 = m_ctrlCombo1.GetItemData(m_ctrlCombo3.GetCurSel());
		m_setRecord.m_lPuntiScore4 = m_ctrlCombo1.GetItemData(m_ctrlCombo4.GetCurSel());
		m_setRecord.m_lTotalScore = m_setRecord.m_lPuntiScore1 + m_setRecord.m_lPuntiScore2 + m_setRecord.m_lPuntiScore3 + m_setRecord.m_lPuntiScore4;

		m_setRecord.m_lPuntiScore1Glasgow = m_ctrlCombo1Glasgow.GetItemData(m_ctrlCombo1Glasgow.GetCurSel());
		m_setRecord.m_lPuntiScore2Glasgow = m_ctrlCombo2Glasgow.GetItemData(m_ctrlCombo2Glasgow.GetCurSel());
		m_setRecord.m_lPuntiScore3Glasgow = m_ctrlCombo3Glasgow.GetItemData(m_ctrlCombo3Glasgow.GetCurSel());
		m_setRecord.m_lTotalScoreGlasgow = m_setRecord.m_lPuntiScore1Glasgow + m_setRecord.m_lPuntiScore2Glasgow + m_setRecord.m_lPuntiScore3Glasgow;
	}
}

void CMonitoraggioVertDlg::OnCbnSelchangeCombo1()
{
	CString strTemp;

	UpdateData(TRUE);

	m_ctrlCombo1.GetLBText(m_ctrlCombo1.GetCurSel(), strTemp);
	switch (atoi(strTemp.Left(1)))
	{
		case 1:
		{
			m_ctrlCombo2.SetCurSel(4);
			m_ctrlCombo2.EnableWindow(FALSE);
			m_ctrlCombo3.SetCurSel(3);
			m_ctrlCombo3.EnableWindow(FALSE);
			m_ctrlCombo4.SetCurSel(3);
			m_ctrlCombo4.EnableWindow(FALSE);
			break;
		}
		case 2:
		{
			m_ctrlCombo2.SetCurSel(3);
			m_ctrlCombo2.EnableWindow(FALSE);
			m_ctrlCombo3.SetCurSel(3);
			m_ctrlCombo3.EnableWindow(FALSE);
			m_ctrlCombo4.SetCurSel(3);
			m_ctrlCombo4.EnableWindow(FALSE);
			break;
		}
		default:
		{
			if (m_ctrlCombo2.GetCurSel() < m_ctrlCombo1.GetCurSel())
				m_ctrlCombo2.SetCurSel(m_ctrlCombo1.GetCurSel());
			m_ctrlCombo2.EnableWindow(TRUE);
			if (m_ctrlCombo3.GetCurSel() < m_ctrlCombo1.GetCurSel())
				m_ctrlCombo3.SetCurSel(m_ctrlCombo1.GetCurSel());
			m_ctrlCombo3.EnableWindow(TRUE);
			if (m_ctrlCombo4.GetCurSel() < m_ctrlCombo1.GetCurSel())
				m_ctrlCombo4.SetCurSel(m_ctrlCombo1.GetCurSel());
			m_ctrlCombo4.EnableWindow(TRUE);
			break;
		}
	}

	/*m_ctrlCombo1.GetLBText(m_ctrlCombo1.GetCurSel(), strTemp);
	m_nPuntiScore1 = atoi(strTemp.Left(1));
	m_ctrlCombo2.GetLBText(m_ctrlCombo2.GetCurSel(), strTemp);
	m_nPuntiScore2 = atoi(strTemp.Left(1));
	m_ctrlCombo3.GetLBText(m_ctrlCombo3.GetCurSel(), strTemp);
	m_nPuntiScore3 = atoi(strTemp.Left(1));
	m_ctrlCombo4.GetLBText(m_ctrlCombo4.GetCurSel(), strTemp);
	m_nPuntiScore4 = atoi(strTemp.Left(1));*/

	m_nPuntiScore1 = m_ctrlCombo1.GetItemData(m_ctrlCombo1.GetCurSel());
	m_nPuntiScore2 = m_ctrlCombo2.GetItemData(m_ctrlCombo2.GetCurSel());
	m_nPuntiScore3 = m_ctrlCombo3.GetItemData(m_ctrlCombo3.GetCurSel());
	m_nPuntiScore4 = m_ctrlCombo4.GetItemData(m_ctrlCombo4.GetCurSel());

	m_nTotalScore = m_nPuntiScore1 + m_nPuntiScore2 + m_nPuntiScore3 + m_nPuntiScore4;

	UpdateData(FALSE);
}

void CMonitoraggioVertDlg::OnCbnSelchangeCombo2()
{
	CString strTemp;

	UpdateData(TRUE);

	m_ctrlCombo2.GetLBText(m_ctrlCombo1.GetCurSel(), strTemp);
	switch (atoi(strTemp.Left(1)))
	{
		case 2:
		{
			m_ctrlCombo3.SetCurSel(3);
			m_ctrlCombo3.EnableWindow(FALSE);
			m_ctrlCombo4.SetCurSel(3);
			m_ctrlCombo4.EnableWindow(FALSE);
			break;
		}
		default:
		{
			if (m_ctrlCombo3.GetCurSel() < m_ctrlCombo2.GetCurSel())
				m_ctrlCombo3.SetCurSel(m_ctrlCombo2.GetCurSel());
			m_ctrlCombo3.EnableWindow(TRUE);
			if (m_ctrlCombo4.GetCurSel() < m_ctrlCombo2.GetCurSel())
				m_ctrlCombo4.SetCurSel(m_ctrlCombo2.GetCurSel());
			m_ctrlCombo4.EnableWindow(TRUE);
			break;
		}
	}

	m_nPuntiScore1 = m_ctrlCombo1.GetItemData(m_ctrlCombo1.GetCurSel());
	m_nPuntiScore2 = m_ctrlCombo2.GetItemData(m_ctrlCombo2.GetCurSel());
	m_nPuntiScore3 = m_ctrlCombo3.GetItemData(m_ctrlCombo3.GetCurSel());
	m_nPuntiScore4 = m_ctrlCombo4.GetItemData(m_ctrlCombo4.GetCurSel());

	m_nTotalScore = m_nPuntiScore1 + m_nPuntiScore2 + m_nPuntiScore3 + m_nPuntiScore4;

	UpdateData(FALSE);
}

void CMonitoraggioVertDlg::OnCbnSelchangeCombo3()
{
	CString strTemp;

	UpdateData(TRUE);

	if (m_ctrlCombo4.GetCurSel() < m_ctrlCombo3.GetCurSel())
		m_ctrlCombo4.SetCurSel(m_ctrlCombo3.GetCurSel());

	m_nPuntiScore1 = m_ctrlCombo1.GetItemData(m_ctrlCombo1.GetCurSel());
	m_nPuntiScore2 = m_ctrlCombo2.GetItemData(m_ctrlCombo2.GetCurSel());
	m_nPuntiScore3 = m_ctrlCombo3.GetItemData(m_ctrlCombo3.GetCurSel());
	m_nPuntiScore4 = m_ctrlCombo4.GetItemData(m_ctrlCombo4.GetCurSel());

	m_nTotalScore = m_nPuntiScore1 + m_nPuntiScore2 + m_nPuntiScore3 + m_nPuntiScore4;

	UpdateData(FALSE);
}

void CMonitoraggioVertDlg::OnCbnSelchangeCombo4()
{
	CString strTemp;

	UpdateData(TRUE);

	/*m_ctrlCombo1.GetLBText(m_ctrlCombo1.GetCurSel(), strTemp);
	m_nPuntiScore1 = atoi(strTemp.Left(1));
	m_ctrlCombo2.GetLBText(m_ctrlCombo2.GetCurSel(), strTemp);
	m_nPuntiScore2 = atoi(strTemp.Left(1));
	m_ctrlCombo3.GetLBText(m_ctrlCombo3.GetCurSel(), strTemp);
	m_nPuntiScore3 = atoi(strTemp.Left(1));
	m_ctrlCombo4.GetLBText(m_ctrlCombo4.GetCurSel(), strTemp);
	m_nPuntiScore4 = atoi(strTemp.Left(1));*/

	m_nPuntiScore1 = m_ctrlCombo1.GetItemData(m_ctrlCombo1.GetCurSel());
	m_nPuntiScore2 = m_ctrlCombo2.GetItemData(m_ctrlCombo2.GetCurSel());
	m_nPuntiScore3 = m_ctrlCombo3.GetItemData(m_ctrlCombo3.GetCurSel());
	m_nPuntiScore4 = m_ctrlCombo4.GetItemData(m_ctrlCombo4.GetCurSel());

	m_nTotalScore = m_nPuntiScore1 + m_nPuntiScore2 + m_nPuntiScore3 + m_nPuntiScore4;

	UpdateData(FALSE);
}

void CMonitoraggioVertDlg::OnCbnSelchangeCombo1Glasgow()
{
	CString strTemp;

	UpdateData(TRUE);

	RecalculateGlasgow();

	UpdateData(FALSE);
}

void CMonitoraggioVertDlg::OnCbnSelchangeCombo2Glasgow()
{
	CString strTemp;

	UpdateData(TRUE);

	RecalculateGlasgow();

	UpdateData(FALSE);
}

void CMonitoraggioVertDlg::OnCbnSelchangeCombo3Glasgow()
{
	CString strTemp;

	UpdateData(TRUE);

	RecalculateGlasgow();

	UpdateData(FALSE);
}

void CMonitoraggioVertDlg::RecalculateGlasgow()
{
	CString strTemp;

	UpdateData(TRUE);

	m_nPuntiScore1Glasgow = m_ctrlCombo1Glasgow.GetItemData(m_ctrlCombo1Glasgow.GetCurSel());
	m_nPuntiScore2Glasgow = m_ctrlCombo2Glasgow.GetItemData(m_ctrlCombo2Glasgow.GetCurSel());
	m_nPuntiScore3Glasgow = m_ctrlCombo3Glasgow.GetItemData(m_ctrlCombo3Glasgow.GetCurSel());

	m_nTotalScoreGlasgow = m_nPuntiScore1Glasgow + m_nPuntiScore2Glasgow + m_nPuntiScore3Glasgow;

	UpdateData(FALSE);
}

HBRUSH CMonitoraggioVertDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_17:
		case IDC_STATIC_SCORE:
		{
			pDC->SetTextColor(m_colorScore);
			break;
		}
		case IDC_STATIC_CCPO_TOTALE:
		{
			int ccpo1 = m_ctrlComboDoloreCCPO1.GetItemData(m_ctrlComboDoloreCCPO1.GetCurSel());
			int ccpo2 = m_ctrlComboDoloreCCPO2.GetItemData(m_ctrlComboDoloreCCPO2.GetCurSel());
			int ccpo3 = m_ctrlComboDoloreCCPO3.GetItemData(m_ctrlComboDoloreCCPO3.GetCurSel());
			int ccpo4 = m_ctrlComboDoloreCCPO4.GetItemData(m_ctrlComboDoloreCCPO4.GetCurSel());
			int ccpo5 = m_ctrlComboDoloreCCPO5.GetItemData(m_ctrlComboDoloreCCPO5.GetCurSel());

			if ((ccpo1 + ccpo2 + ccpo3 + ccpo4 + ccpo5) >= 7)
				pDC->SetTextColor(RGB(255,0,0));

			break;
		}
	}

	return hBrush;
}

void CMonitoraggioVertDlg::OnCbnEditChangeComboFarmaci()
{
	// TRACE("- OnCbnEditChange\n");

	// Sandro 06/05/2010 - Devo farlo io a mano perchè non lo fa lui in automatico //
	OnCbnSelChangeComboFarmaci();
}

void CMonitoraggioVertDlg::OnCbnSelChangeComboFarmaci()
{
	// TRACE("- OnCbnSelChange\n");

	m_btnInserisci.EnableWindow(m_ctrlFarmaci.GetCurSel() >= 0);
}

void CMonitoraggioVertDlg::OnBnClickedInsert()
{
	//Controllo se il farmaco è già stato inserito
	for (int i = 0; i < m_listaFarmaciDosi.GetItemCount(); i++)
	{
		int iItemTest = m_listaFarmaciDosi.GetItemData(i);
		if (iItemTest == m_ctrlFarmaci.GetItemData(m_ctrlFarmaci.GetCurSel()))
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FARMACO_GIA_INSERITO));
			m_ctrlFarmaci.SetCurSel(0);
			m_ctrlDosi.SetWindowText("");
			m_btnInserisci.EnableWindow(FALSE);
			return;
		}
	}

	TCHAR testoFarTemp[255], testoDoseTemp[255];
	m_ctrlFarmaci.GetWindowTextA(testoFarTemp, 255);
	m_ctrlDosi.GetWindowTextA(testoDoseTemp, 255);
	int item = m_listaFarmaciDosi.InsertItem(m_listaFarmaciDosi.GetItemCount(), testoFarTemp);
	m_listaFarmaciDosi.SetItemData(item, m_ctrlFarmaci.GetItemData(m_ctrlFarmaci.GetCurSel()));
	m_listaFarmaciDosi.SetItemText(item, 1, testoDoseTemp);
	m_ctrlFarmaci.SetCurSel(-1);
	m_ctrlDosi.SetWindowText("");
	m_btnInserisci.EnableWindow(FALSE);
	m_listaFarmaciDosi.RedrawWindow();
}

void CMonitoraggioVertDlg::OnLvnItemchangedListaFarmaci(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	POSITION pos = m_listaFarmaciDosi.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		m_btnRimuovi.EnableWindow(TRUE);
		m_rigaSelezionata = m_listaFarmaciDosi.GetNextSelectedItem(pos);
	}
	else
	{
		m_btnRimuovi.EnableWindow(FALSE);
		m_rigaSelezionata = -1;
	}

	*pResult = 0;
}

void CMonitoraggioVertDlg::OnBnClickedRemove()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DELETE_ROW), MB_YESNO) == IDYES)
		m_listaFarmaciDosi.DeleteItem(m_rigaSelezionata);

	m_btnRimuovi.EnableWindow(FALSE);
}

void CMonitoraggioVertDlg::OnCbnSelchangeComboVentilazione()
{
	CheckVentilazione();
}

void CMonitoraggioVertDlg::CheckVentilazione()
{
	BOOL bEnable = FALSE;

	if (m_ctrlComboVentilazione.GetItemData(m_ctrlComboVentilazione.GetCurSel()) == 2)
	{
		bEnable = TRUE;
	}
	else
	{
		m_ctrlEditVentilazioneVt.SetWindowText("");
		m_ctrlEditVentilazioneFr.SetWindowText("");
	}

	m_ctrlStatic26.EnableWindow(bEnable);
	m_ctrlStatic27.EnableWindow(bEnable);
	m_ctrlEditVentilazioneVt.EnableWindow(bEnable);
	m_ctrlEditVentilazioneFr.EnableWindow(bEnable);
}

void CMonitoraggioVertDlg::RiempiComboFase()
{
	m_ctrlFase.ResetContent();
	m_ctrlFase.InsertString(0, theApp.GetMessageString(IDS_PRE));
	m_ctrlFase.SetItemData(0, MonitoringPhase::pre);
	m_ctrlFase.InsertString(1, theApp.GetMessageString(IDS_INTRA));
	m_ctrlFase.SetItemData(1, MonitoringPhase::intra);
	m_ctrlFase.InsertString(2, theApp.GetMessageString(IDS_POST));
	m_ctrlFase.SetItemData(2, MonitoringPhase::post);
	m_ctrlFase.InsertString(3, theApp.GetMessageString(IDS_SALA_RISVEGLIO));
	m_ctrlFase.SetItemData(3, MonitoringPhase::recoveryRoom);
	m_ctrlFase.InsertString(4, theApp.GetMessageString(IDS_DIMISSIONE));
	m_ctrlFase.SetItemData(4, MonitoringPhase::discharge);
	m_ctrlFase.SetCurSel(0);
}



void CMonitoraggioVertDlg::RiempiCombo1()
{
	m_ctrlCombo1.ResetContent();
	m_ctrlCombo1.InsertString(0, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO1_5));
	m_ctrlCombo1.SetItemData(0, 5);
	m_ctrlCombo1.InsertString(1, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO1_4));
	m_ctrlCombo1.SetItemData(1, 4);
	m_ctrlCombo1.InsertString(2, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO1_3));
	m_ctrlCombo1.SetItemData(2, 3);
	m_ctrlCombo1.InsertString(3, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO1_2));
	m_ctrlCombo1.SetItemData(3, 2);
	m_ctrlCombo1.InsertString(4, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO1_1));
	m_ctrlCombo1.SetItemData(4, 1);
}

void CMonitoraggioVertDlg::RiempiCombo2()
{
	m_ctrlCombo2.ResetContent();
	m_ctrlCombo2.InsertString(0, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_5));
	m_ctrlCombo2.SetItemData(0, 5);
	m_ctrlCombo2.InsertString(1, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_4));
	m_ctrlCombo2.SetItemData(1, 4);
	m_ctrlCombo2.InsertString(2, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_3));
	m_ctrlCombo2.SetItemData(2, 3);
	m_ctrlCombo2.InsertString(3, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_2));
	m_ctrlCombo2.SetItemData(3, 2);
	m_ctrlCombo2.InsertString(4, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_1));
	m_ctrlCombo2.SetItemData(4, 0);
}

void CMonitoraggioVertDlg::RiempiCombo3()
{
	m_ctrlCombo3.ResetContent();
	m_ctrlCombo3.InsertString(0, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_4));
	m_ctrlCombo3.SetItemData(0, 5);
	m_ctrlCombo3.InsertString(1, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_3));
	m_ctrlCombo3.SetItemData(1, 4);
	m_ctrlCombo3.InsertString(2, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_2));
	m_ctrlCombo3.SetItemData(2, 3);
	m_ctrlCombo3.InsertString(3, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_1));
	m_ctrlCombo3.SetItemData(3, 0);
}

void CMonitoraggioVertDlg::RiempiCombo4()
{
	m_ctrlCombo4.ResetContent();
	m_ctrlCombo4.InsertString(0, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO4_4));
	m_ctrlCombo4.SetItemData(0, 5);
	m_ctrlCombo4.InsertString(1, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO4_3));
	m_ctrlCombo4.SetItemData(1, 4);
	m_ctrlCombo4.InsertString(2, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO4_2));
	m_ctrlCombo4.SetItemData(2, 3);
	m_ctrlCombo4.InsertString(3, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO4_1));
	m_ctrlCombo4.SetItemData(3, 0);
}

void CMonitoraggioVertDlg::RiempiComboInfermieri()
{
	CInfermieriSet infermieriSet;
	if (infermieriSet.OpenRecordset("CMonitoraggioVertDlg::OnInitDialog"))
	{
		long index = 0;
		while (!infermieriSet.IsEOF())
		{
			m_ctrlComboInfermiere.InsertString(index, infermieriSet.m_sTitolo + " " + infermieriSet.m_sNome + " " + infermieriSet.m_sCognome);
			m_ctrlComboInfermiere.SetItemData(index, infermieriSet.m_lContatore);

			index++;
			infermieriSet.MoveNext();
		}

		infermieriSet.CloseRecordset("CMonitoraggioVertDlg::OnInitDialog");
	}
}

void CMonitoraggioVertDlg::RiempiComboPolso()
{
	m_ctrlComboPolso.ResetContent();
	m_ctrlComboPolso.InsertString(0, CMonitoraggioUtils::DecodePolso(1));
	m_ctrlComboPolso.SetItemData(0, 1);
	m_ctrlComboPolso.InsertString(1, CMonitoraggioUtils::DecodePolso(2));
	m_ctrlComboPolso.SetItemData(1, 2);
	m_ctrlComboPolso.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboIntubazione()
{
	m_ctrlComboIntubazione.ResetContent();
	m_ctrlComboIntubazione.InsertString(0, CMonitoraggioUtils::DecodeIntubazione(0));
	m_ctrlComboIntubazione.SetItemData(0, 0);
	m_ctrlComboIntubazione.InsertString(1, CMonitoraggioUtils::DecodeIntubazione(1));
	m_ctrlComboIntubazione.SetItemData(1, 1);
	m_ctrlComboIntubazione.InsertString(2, CMonitoraggioUtils::DecodeIntubazione(2));
	m_ctrlComboIntubazione.SetItemData(2, 2);
	m_ctrlComboIntubazione.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboVentilazione()
{
	m_ctrlComboVentilazione.ResetContent();
	m_ctrlComboVentilazione.InsertString(0, CMonitoraggioUtils::DecodeVentilazione(1));
	m_ctrlComboVentilazione.SetItemData(0, 1);
	m_ctrlComboVentilazione.InsertString(1, CMonitoraggioUtils::DecodeVentilazione(2));
	m_ctrlComboVentilazione.SetItemData(1, 2);
	m_ctrlComboVentilazione.SetCurSel(0);
	CheckVentilazione();
}

void CMonitoraggioVertDlg::RiempiComboDoloreVAS()
{
	m_ctrlComboDoloreVAS.ResetContent();
	m_ctrlComboDoloreVAS.InsertString(0, CMonitoraggioUtils::DecodeDoloreVAS(0));
	m_ctrlComboDoloreVAS.SetItemData(0, 0);
	m_ctrlComboDoloreVAS.InsertString(1, CMonitoraggioUtils::DecodeDoloreVAS(1));
	m_ctrlComboDoloreVAS.SetItemData(1, 1);
	m_ctrlComboDoloreVAS.InsertString(2, CMonitoraggioUtils::DecodeDoloreVAS(2));
	m_ctrlComboDoloreVAS.SetItemData(2, 2);
	m_ctrlComboDoloreVAS.InsertString(3, CMonitoraggioUtils::DecodeDoloreVAS(3));
	m_ctrlComboDoloreVAS.SetItemData(3, 3);
	m_ctrlComboDoloreVAS.InsertString(4, CMonitoraggioUtils::DecodeDoloreVAS(4));
	m_ctrlComboDoloreVAS.SetItemData(4, 4);
	m_ctrlComboDoloreVAS.InsertString(5, CMonitoraggioUtils::DecodeDoloreVAS(5));
	m_ctrlComboDoloreVAS.SetItemData(5, 5);
	m_ctrlComboDoloreVAS.InsertString(6, CMonitoraggioUtils::DecodeDoloreVAS(6));
	m_ctrlComboDoloreVAS.SetItemData(6, 6);
	m_ctrlComboDoloreVAS.InsertString(7, CMonitoraggioUtils::DecodeDoloreVAS(7));
	m_ctrlComboDoloreVAS.SetItemData(7, 7);
	m_ctrlComboDoloreVAS.InsertString(8, CMonitoraggioUtils::DecodeDoloreVAS(8));
	m_ctrlComboDoloreVAS.SetItemData(8, 8);
	m_ctrlComboDoloreVAS.InsertString(9, CMonitoraggioUtils::DecodeDoloreVAS(9));
	m_ctrlComboDoloreVAS.SetItemData(9, 9);
	m_ctrlComboDoloreVAS.InsertString(10, CMonitoraggioUtils::DecodeDoloreVAS(10));
	m_ctrlComboDoloreVAS.SetItemData(10, 10);
	m_ctrlComboDoloreVAS.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboDoloreNRS()
{
	m_ctrlComboDoloreNRS.ResetContent();
	m_ctrlComboDoloreNRS.InsertString(0, CMonitoraggioUtils::DecodeDoloreNRS(0));
	m_ctrlComboDoloreNRS.SetItemData(0, 0);
	m_ctrlComboDoloreNRS.InsertString(1, CMonitoraggioUtils::DecodeDoloreNRS(1));
	m_ctrlComboDoloreNRS.SetItemData(1, 1);
	m_ctrlComboDoloreNRS.InsertString(2, CMonitoraggioUtils::DecodeDoloreNRS(2));
	m_ctrlComboDoloreNRS.SetItemData(2, 2);
	m_ctrlComboDoloreNRS.InsertString(3, CMonitoraggioUtils::DecodeDoloreNRS(3));
	m_ctrlComboDoloreNRS.SetItemData(3, 3);
	m_ctrlComboDoloreNRS.InsertString(4, CMonitoraggioUtils::DecodeDoloreNRS(4));
	m_ctrlComboDoloreNRS.SetItemData(4, 4);
	m_ctrlComboDoloreNRS.InsertString(5, CMonitoraggioUtils::DecodeDoloreNRS(5));
	m_ctrlComboDoloreNRS.SetItemData(5, 5);
	m_ctrlComboDoloreNRS.InsertString(6, CMonitoraggioUtils::DecodeDoloreNRS(6));
	m_ctrlComboDoloreNRS.SetItemData(6, 6);
	m_ctrlComboDoloreNRS.InsertString(7, CMonitoraggioUtils::DecodeDoloreNRS(7));
	m_ctrlComboDoloreNRS.SetItemData(7, 7);
	m_ctrlComboDoloreNRS.InsertString(8, CMonitoraggioUtils::DecodeDoloreNRS(8));
	m_ctrlComboDoloreNRS.SetItemData(8, 8);
	m_ctrlComboDoloreNRS.InsertString(9, CMonitoraggioUtils::DecodeDoloreNRS(9));
	m_ctrlComboDoloreNRS.SetItemData(9, 9);
	m_ctrlComboDoloreNRS.InsertString(10, CMonitoraggioUtils::DecodeDoloreNRS(10));
	m_ctrlComboDoloreNRS.SetItemData(10, 10);
	m_ctrlComboDoloreNRS.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboDoloreWB()
{
	m_ctrlComboDoloreWB.ResetContent();
	m_ctrlComboDoloreWB.InsertString(0, CMonitoraggioUtils::DecodeDoloreWB(0));
	m_ctrlComboDoloreWB.SetItemData(0, 0);
	m_ctrlComboDoloreWB.InsertString(1, CMonitoraggioUtils::DecodeDoloreWB(1));
	m_ctrlComboDoloreWB.SetItemData(1, 1);
	m_ctrlComboDoloreWB.InsertString(2, CMonitoraggioUtils::DecodeDoloreWB(2));
	m_ctrlComboDoloreWB.SetItemData(2, 2);
	m_ctrlComboDoloreWB.InsertString(3, CMonitoraggioUtils::DecodeDoloreWB(3));
	m_ctrlComboDoloreWB.SetItemData(3, 3);
	m_ctrlComboDoloreWB.InsertString(4, CMonitoraggioUtils::DecodeDoloreWB(4));
	m_ctrlComboDoloreWB.SetItemData(4, 4);
	m_ctrlComboDoloreWB.InsertString(5, CMonitoraggioUtils::DecodeDoloreWB(5));
	m_ctrlComboDoloreWB.SetItemData(5, 5);	
	m_ctrlComboDoloreWB.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboDoloreCCPO1()
{
	m_ctrlComboDoloreCCPO1.ResetContent();
	m_ctrlComboDoloreCCPO1.InsertString(0, CMonitoraggioUtils::DecodeDoloreCCPO1(0));
	m_ctrlComboDoloreCCPO1.SetItemData(0, 0);
	m_ctrlComboDoloreCCPO1.InsertString(1, CMonitoraggioUtils::DecodeDoloreCCPO1(1));
	m_ctrlComboDoloreCCPO1.SetItemData(1, 1);
	m_ctrlComboDoloreCCPO1.InsertString(2, CMonitoraggioUtils::DecodeDoloreCCPO1(2));
	m_ctrlComboDoloreCCPO1.SetItemData(2, 2);
	m_ctrlComboDoloreCCPO1.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboDoloreCCPO2()
{
	m_ctrlComboDoloreCCPO2.ResetContent();
	m_ctrlComboDoloreCCPO2.InsertString(0, CMonitoraggioUtils::DecodeDoloreCCPO2(0));
	m_ctrlComboDoloreCCPO2.SetItemData(0, 0);
	m_ctrlComboDoloreCCPO2.InsertString(1, CMonitoraggioUtils::DecodeDoloreCCPO2(1));
	m_ctrlComboDoloreCCPO2.SetItemData(1, 1);
	m_ctrlComboDoloreCCPO2.InsertString(2, CMonitoraggioUtils::DecodeDoloreCCPO2(2));
	m_ctrlComboDoloreCCPO2.SetItemData(2, 2);
	m_ctrlComboDoloreCCPO2.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboDoloreCCPO3()
{
	m_ctrlComboDoloreCCPO3.ResetContent();
	m_ctrlComboDoloreCCPO3.InsertString(0, CMonitoraggioUtils::DecodeDoloreCCPO3(0));
	m_ctrlComboDoloreCCPO3.SetItemData(0, 0);
	m_ctrlComboDoloreCCPO3.InsertString(1, CMonitoraggioUtils::DecodeDoloreCCPO3(1));
	m_ctrlComboDoloreCCPO3.SetItemData(1, 1);
	m_ctrlComboDoloreCCPO3.InsertString(2, CMonitoraggioUtils::DecodeDoloreCCPO3(2));
	m_ctrlComboDoloreCCPO3.SetItemData(2, 2);
	m_ctrlComboDoloreCCPO3.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboDoloreCCPO4()
{
	m_ctrlComboDoloreCCPO4.ResetContent();
	m_ctrlComboDoloreCCPO4.InsertString(0, CMonitoraggioUtils::DecodeDoloreCCPO4(-1));
	m_ctrlComboDoloreCCPO4.SetItemData(0, 0);
	m_ctrlComboDoloreCCPO4.InsertString(1, CMonitoraggioUtils::DecodeDoloreCCPO4(0));
	m_ctrlComboDoloreCCPO4.SetItemData(1, 0);
	m_ctrlComboDoloreCCPO4.InsertString(2, CMonitoraggioUtils::DecodeDoloreCCPO4(1));
	m_ctrlComboDoloreCCPO4.SetItemData(2, 1);
	m_ctrlComboDoloreCCPO4.InsertString(3, CMonitoraggioUtils::DecodeDoloreCCPO4(2));
	m_ctrlComboDoloreCCPO4.SetItemData(3, 2);
	m_ctrlComboDoloreCCPO4.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboDoloreCCPO5()
{
	m_ctrlComboDoloreCCPO5.ResetContent();
	m_ctrlComboDoloreCCPO5.InsertString(0, CMonitoraggioUtils::DecodeDoloreCCPO5(-1));
	m_ctrlComboDoloreCCPO5.SetItemData(0, 0);
	m_ctrlComboDoloreCCPO5.InsertString(1, CMonitoraggioUtils::DecodeDoloreCCPO5(0));
	m_ctrlComboDoloreCCPO5.SetItemData(1, 0);
	m_ctrlComboDoloreCCPO5.InsertString(2, CMonitoraggioUtils::DecodeDoloreCCPO5(1));
	m_ctrlComboDoloreCCPO5.SetItemData(2, 1);
	m_ctrlComboDoloreCCPO5.InsertString(3, CMonitoraggioUtils::DecodeDoloreCCPO5(2));
	m_ctrlComboDoloreCCPO5.SetItemData(3, 2);
	m_ctrlComboDoloreCCPO5.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboDoloreScala()
{
	m_ctrlComboDoloreScala.ResetContent();
	m_ctrlComboDoloreScala.InsertString(0, CMonitoraggioUtils::DecodeDoloreScala(1));
	m_ctrlComboDoloreScala.SetItemData(0, 1);
	m_ctrlComboDoloreScala.InsertString(1, CMonitoraggioUtils::DecodeDoloreScala(2));
	m_ctrlComboDoloreScala.SetItemData(1, 2);
	m_ctrlComboDoloreScala.InsertString(2, CMonitoraggioUtils::DecodeDoloreScala(3));
	m_ctrlComboDoloreScala.SetItemData(2, 3);
	m_ctrlComboDoloreScala.InsertString(3, CMonitoraggioUtils::DecodeDoloreScala(4));
	m_ctrlComboDoloreScala.SetItemData(3, 4);
	m_ctrlComboDoloreScala.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboDoloreLocalizzazione()
{
	m_ctrlComboDoloreLocalizzazione.ResetContent();
	m_ctrlComboDoloreLocalizzazione.InsertString(0, CMonitoraggioUtils::DecodeDoloreLocalizzazione(0));
	m_ctrlComboDoloreLocalizzazione.SetItemData(0, 0);
	m_ctrlComboDoloreLocalizzazione.InsertString(1, CMonitoraggioUtils::DecodeDoloreLocalizzazione(1));
	m_ctrlComboDoloreLocalizzazione.SetItemData(1, 1);
	m_ctrlComboDoloreLocalizzazione.InsertString(2, CMonitoraggioUtils::DecodeDoloreLocalizzazione(2));
	m_ctrlComboDoloreLocalizzazione.SetItemData(2, 2);
	m_ctrlComboDoloreLocalizzazione.InsertString(3, CMonitoraggioUtils::DecodeDoloreLocalizzazione(3));
	m_ctrlComboDoloreLocalizzazione.SetItemData(3, 3);
	m_ctrlComboDoloreLocalizzazione.InsertString(4, CMonitoraggioUtils::DecodeDoloreLocalizzazione(4));
	m_ctrlComboDoloreLocalizzazione.SetItemData(4, 4);
	m_ctrlComboDoloreLocalizzazione.InsertString(5, CMonitoraggioUtils::DecodeDoloreLocalizzazione(5));
	m_ctrlComboDoloreLocalizzazione.SetItemData(5, 5);
	m_ctrlComboDoloreLocalizzazione.InsertString(6, CMonitoraggioUtils::DecodeDoloreLocalizzazione(6));
	m_ctrlComboDoloreLocalizzazione.SetItemData(6, 6);
	m_ctrlComboDoloreLocalizzazione.InsertString(7, CMonitoraggioUtils::DecodeDoloreLocalizzazione(7));
	m_ctrlComboDoloreLocalizzazione.SetItemData(7, 7);
	m_ctrlComboDoloreLocalizzazione.InsertString(8, CMonitoraggioUtils::DecodeDoloreLocalizzazione(8));
	m_ctrlComboDoloreLocalizzazione.SetItemData(8, 8);
	m_ctrlComboDoloreLocalizzazione.InsertString(9, CMonitoraggioUtils::DecodeDoloreLocalizzazione(9));
	m_ctrlComboDoloreLocalizzazione.SetItemData(9, 9);
	

}

void CMonitoraggioVertDlg::RiempiComboDoloreCaratteristiche()
{
	m_ctrlComboDoloreCaratteristiche.ResetContent();
	m_ctrlComboDoloreCaratteristiche.InsertString(0, CMonitoraggioUtils::DecodeDoloreCaratteristiche(0));
	m_ctrlComboDoloreCaratteristiche.SetItemData(0, 0);
	m_ctrlComboDoloreCaratteristiche.InsertString(1, CMonitoraggioUtils::DecodeDoloreCaratteristiche(1));
	m_ctrlComboDoloreCaratteristiche.SetItemData(1, 1);
	m_ctrlComboDoloreCaratteristiche.InsertString(2, CMonitoraggioUtils::DecodeDoloreCaratteristiche(2));
	m_ctrlComboDoloreCaratteristiche.SetItemData(2, 2);
	m_ctrlComboDoloreCaratteristiche.InsertString(3, CMonitoraggioUtils::DecodeDoloreCaratteristiche(3));
	m_ctrlComboDoloreCaratteristiche.SetItemData(3, 3);
	m_ctrlComboDoloreCaratteristiche.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboDoloreFrequenza()
{
	m_ctrlComboDoloreFrequenza.ResetContent();
	m_ctrlComboDoloreFrequenza.InsertString(0, CMonitoraggioUtils::DecodeDoloreFrequenza(0));
	m_ctrlComboDoloreFrequenza.SetItemData(0, 0);
	m_ctrlComboDoloreFrequenza.InsertString(1, CMonitoraggioUtils::DecodeDoloreFrequenza(1));
	m_ctrlComboDoloreFrequenza.SetItemData(1, 1);
	m_ctrlComboDoloreFrequenza.InsertString(2, CMonitoraggioUtils::DecodeDoloreFrequenza(2));
	m_ctrlComboDoloreFrequenza.SetItemData(2, 2);
	m_ctrlComboDoloreFrequenza.InsertString(3, CMonitoraggioUtils::DecodeDoloreFrequenza(3));
	m_ctrlComboDoloreFrequenza.SetItemData(3, 3);
	m_ctrlComboDoloreFrequenza.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboDoloreDurata()
{
	m_ctrlComboDoloreDurata.ResetContent();
	m_ctrlComboDoloreDurata.InsertString(0, CMonitoraggioUtils::DecodeDoloreDurata(0));
	m_ctrlComboDoloreDurata.SetItemData(0, 0);
	m_ctrlComboDoloreDurata.InsertString(1, CMonitoraggioUtils::DecodeDoloreDurata(1));
	m_ctrlComboDoloreDurata.SetItemData(1, 1);
	m_ctrlComboDoloreDurata.InsertString(2, CMonitoraggioUtils::DecodeDoloreDurata(2));
	m_ctrlComboDoloreDurata.SetItemData(2, 2);
	m_ctrlComboDoloreDurata.InsertString(3, CMonitoraggioUtils::DecodeDoloreDurata(3));
	m_ctrlComboDoloreDurata.SetItemData(3, 3);
	m_ctrlComboDoloreDurata.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboRamsey()
{
	m_ctrlComboRamsey.ResetContent();
	m_ctrlComboRamsey.InsertString(0, CMonitoraggioUtils::DecodeRamsay(0));
	m_ctrlComboRamsey.SetItemData(0, 0);
	m_ctrlComboRamsey.InsertString(1, CMonitoraggioUtils::DecodeRamsay(1));
	m_ctrlComboRamsey.SetItemData(1, 1);
	m_ctrlComboRamsey.InsertString(2, CMonitoraggioUtils::DecodeRamsay(2));
	m_ctrlComboRamsey.SetItemData(2, 2);
	m_ctrlComboRamsey.InsertString(3, CMonitoraggioUtils::DecodeRamsay(3));
	m_ctrlComboRamsey.SetItemData(3, 3);
	m_ctrlComboRamsey.InsertString(4, CMonitoraggioUtils::DecodeRamsay(4));
	m_ctrlComboRamsey.SetItemData(4, 4);
	m_ctrlComboRamsey.InsertString(5, CMonitoraggioUtils::DecodeRamsay(5));
	m_ctrlComboRamsey.SetItemData(5, 5);
	m_ctrlComboRamsey.InsertString(6, CMonitoraggioUtils::DecodeRamsay(6));
	m_ctrlComboRamsey.SetItemData(6, 6);
	m_ctrlComboRamsey.SetCurSel(0);
}

void CMonitoraggioVertDlg::RiempiComboGlasgow()
{
	if (!theApp.m_bMostraScoreMonitoraggio)
		return;

	//GLASGOW
	m_ctrlCombo1Glasgow.ResetContent();
	m_ctrlCombo1Glasgow.InsertString(0, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO1_GLASGOW_4));
	m_ctrlCombo1Glasgow.SetItemData(0, 4);
	m_ctrlCombo1Glasgow.InsertString(1, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO1_GLASGOW_3));
	m_ctrlCombo1Glasgow.SetItemData(1, 3);
	m_ctrlCombo1Glasgow.InsertString(2, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO1_GLASGOW_2));
	m_ctrlCombo1Glasgow.SetItemData(2, 2);
	m_ctrlCombo1Glasgow.InsertString(3, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO1_GLASGOW_1));
	m_ctrlCombo1Glasgow.SetItemData(3, 1);
	m_ctrlCombo1Glasgow.InsertString(4, "");
	m_ctrlCombo1Glasgow.SetItemData(4, 0);

	m_ctrlCombo2Glasgow.ResetContent();
	m_ctrlCombo2Glasgow.InsertString(0, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_GLASGOW_5));
	m_ctrlCombo2Glasgow.SetItemData(0, 5);
	m_ctrlCombo2Glasgow.InsertString(1, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_GLASGOW_4));
	m_ctrlCombo2Glasgow.SetItemData(1, 4);
	m_ctrlCombo2Glasgow.InsertString(2, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_GLASGOW_3));
	m_ctrlCombo2Glasgow.SetItemData(2, 3);
	m_ctrlCombo2Glasgow.InsertString(3, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_GLASGOW_2));
	m_ctrlCombo2Glasgow.SetItemData(3, 2);
	m_ctrlCombo2Glasgow.InsertString(4, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_GLASGOW_1));
	m_ctrlCombo2Glasgow.SetItemData(4, 1);
	m_ctrlCombo2Glasgow.InsertString(5, "");
	m_ctrlCombo2Glasgow.SetItemData(5, 0);

	m_ctrlCombo3Glasgow.ResetContent();
	m_ctrlCombo3Glasgow.InsertString(0, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_GLASGOW_6));
	m_ctrlCombo3Glasgow.SetItemData(0, 6);
	m_ctrlCombo3Glasgow.InsertString(1, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_GLASGOW_5));
	m_ctrlCombo3Glasgow.SetItemData(1, 5);
	m_ctrlCombo3Glasgow.InsertString(2, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_GLASGOW_4));
	m_ctrlCombo3Glasgow.SetItemData(2, 4);
	m_ctrlCombo3Glasgow.InsertString(3, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_GLASGOW_3));
	m_ctrlCombo3Glasgow.SetItemData(3, 3);
	m_ctrlCombo3Glasgow.InsertString(4, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_GLASGOW_2));
	m_ctrlCombo3Glasgow.SetItemData(4, 2);
	m_ctrlCombo3Glasgow.InsertString(5, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_GLASGOW_1));
	m_ctrlCombo3Glasgow.SetItemData(5, 1);
	m_ctrlCombo3Glasgow.InsertString(6, "");
	m_ctrlCombo3Glasgow.SetItemData(6, 0);

	GetDlgItem(IDC_STATIC_17)->SetFont(&theApp.m_fontBold);
	m_ctrlStaticScore.SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_STATIC_4_GLASGOW)->SetFont(&theApp.m_fontBold);
	m_ctrlStaticScoreGlasgow.SetFont(&theApp.m_fontBold);
}

void CMonitoraggioVertDlg::RiempiListaFarmaci()
{
	// Preparo le combo lista farmaci
	CFarmaciMonitoraggioSet setFarmaci;
	setFarmaci.SetSortRecord("Nome");
	if (setFarmaci.OpenRecordset("CMonitoraggioVertDynForm::OnInitDialog"))
	{
		while (!setFarmaci.IsEOF())
		{
			int index = m_ctrlFarmaci.AddString(setFarmaci.m_sNome);
			m_ctrlFarmaci.SetItemData(index, setFarmaci.m_lID);

			setFarmaci.MoveNext();
		}

		setFarmaci.CloseRecordset("CMonitoraggioVertDynForm::OnInitDialog");
	}

	m_listaFarmaciDosi.SetExtendedStyle(m_listaFarmaciDosi.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_AUTOSIZECOLUMNS);
	m_listaFarmaciDosi.InsertColumn(0, "Farmaco", LVCFMT_LEFT, 250);
	m_listaFarmaciDosi.InsertColumn(1, "Dose", LVCFMT_LEFT, 250);

	m_listaFarmaciDosi.SetColumnPercSize(0, 40);
	m_listaFarmaciDosi.SetColumnPercSize(1, 30);
}

void CMonitoraggioVertDlg::OnCbnSelchangeComboDoloreScala()
{
	DoloreScalaSelChange();
}


void CMonitoraggioVertDlg::OnCbnSelchangeComboDoloreLocalizzazione()
{
	if (m_ctrlComboDoloreLocalizzazione.GetCurSel() > 0)
	{
		m_ctrlEditDoloreLocalizzazioneDettaglio.EnableWindow(TRUE);
	}
	else
	{
		m_ctrlEditDoloreLocalizzazioneDettaglio.SetWindowText("");
		m_ctrlEditDoloreLocalizzazioneDettaglio.EnableWindow(FALSE);
	}
}


void CMonitoraggioVertDlg::OnCbnSelchangeComboCcpo1()
{
	UpdateCCPO();
}


void CMonitoraggioVertDlg::OnCbnSelchangeComboCcpo2()
{
	UpdateCCPO();
}


void CMonitoraggioVertDlg::OnCbnSelchangeComboCcpo3()
{
	UpdateCCPO();
}


void CMonitoraggioVertDlg::OnCbnSelchangeComboCcpo4()
{
	if (m_ctrlComboDoloreCCPO4.GetCurSel() >= 0)
	{
		m_ctrlComboDoloreCCPO5.SetCurSel(0);
	}

	UpdateCCPO();
}


void CMonitoraggioVertDlg::OnCbnSelchangeComboCcpo5()
{
	if (m_ctrlComboDoloreCCPO5.GetCurSel() >= 0)
	{
		m_ctrlComboDoloreCCPO4.SetCurSel(0);
	}

	UpdateCCPO();
}

void CMonitoraggioVertDlg::UpdateCCPO()
{
	int ccpo1 = m_ctrlComboDoloreCCPO1.GetItemData(m_ctrlComboDoloreCCPO1.GetCurSel());
	int ccpo2 = m_ctrlComboDoloreCCPO2.GetItemData(m_ctrlComboDoloreCCPO2.GetCurSel());
	int ccpo3 = m_ctrlComboDoloreCCPO3.GetItemData(m_ctrlComboDoloreCCPO3.GetCurSel());
	int ccpo4 = m_ctrlComboDoloreCCPO4.GetItemData(m_ctrlComboDoloreCCPO4.GetCurSel());
	int ccpo5 = m_ctrlComboDoloreCCPO5.GetItemData(m_ctrlComboDoloreCCPO5.GetCurSel());

	CString sTotale;
	sTotale.Format("Totale %li", ccpo1 + ccpo2 + ccpo3 + ccpo4 + ccpo5);

	GetDlgItem(IDC_STATIC_CCPO_TOTALE)->SetWindowText(sTotale);
}

void CMonitoraggioVertDlg::DoloreScalaSelChange()
{
	if (m_ctrlComboDoloreScala.GetItemData(m_ctrlComboDoloreScala.GetCurSel()) == 1)
	{
		m_ctrlComboDoloreVAS.ShowWindow(SW_SHOW);
		m_ctrlComboDoloreNRS.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreWB.ShowWindow(SW_HIDE);
		m_ctrlStatic34.ShowWindow(SW_HIDE);
		m_ctrlStatic35.ShowWindow(SW_HIDE);
		m_ctrlStatic36.ShowWindow(SW_HIDE);
		m_ctrlStatic37.ShowWindow(SW_HIDE);
		m_ctrlStatic38.ShowWindow(SW_HIDE);
		m_ctrlStatic39.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO1.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO2.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO3.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO4.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO5.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CCPO_TOTALE)->ShowWindow(SW_HIDE);
	}
	else if (m_ctrlComboDoloreScala.GetItemData(m_ctrlComboDoloreScala.GetCurSel()) == 2)
	{
		m_ctrlComboDoloreVAS.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreNRS.ShowWindow(SW_SHOW);
		m_ctrlComboDoloreWB.ShowWindow(SW_HIDE);
		m_ctrlStatic34.ShowWindow(SW_HIDE);
		m_ctrlStatic35.ShowWindow(SW_HIDE);
		m_ctrlStatic36.ShowWindow(SW_HIDE);
		m_ctrlStatic37.ShowWindow(SW_HIDE);
		m_ctrlStatic38.ShowWindow(SW_HIDE);
		m_ctrlStatic39.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO1.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO2.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO3.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO4.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO5.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CCPO_TOTALE)->ShowWindow(SW_HIDE);
	}
	else if (m_ctrlComboDoloreScala.GetItemData(m_ctrlComboDoloreScala.GetCurSel()) == 3)
	{
		m_ctrlComboDoloreVAS.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreNRS.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreWB.ShowWindow(SW_SHOW);
		m_ctrlStatic34.ShowWindow(SW_HIDE);
		m_ctrlStatic35.ShowWindow(SW_HIDE);
		m_ctrlStatic36.ShowWindow(SW_HIDE);
		m_ctrlStatic37.ShowWindow(SW_HIDE);
		m_ctrlStatic38.ShowWindow(SW_HIDE);
		m_ctrlStatic39.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO1.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO2.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO3.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO4.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreCCPO5.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CCPO_TOTALE)->ShowWindow(SW_HIDE);
	}
	else if (m_ctrlComboDoloreScala.GetItemData(m_ctrlComboDoloreScala.GetCurSel()) == 4)
	{
		m_ctrlComboDoloreVAS.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreNRS.ShowWindow(SW_HIDE);
		m_ctrlComboDoloreWB.ShowWindow(SW_HIDE);
		m_ctrlStatic34.ShowWindow(SW_SHOW);
		m_ctrlStatic35.ShowWindow(SW_SHOW);
		m_ctrlStatic36.ShowWindow(SW_SHOW);
		m_ctrlStatic37.ShowWindow(SW_SHOW);
		m_ctrlStatic38.ShowWindow(SW_SHOW);
		m_ctrlStatic39.ShowWindow(SW_SHOW);
		m_ctrlComboDoloreCCPO1.ShowWindow(SW_SHOW);
		m_ctrlComboDoloreCCPO2.ShowWindow(SW_SHOW);
		m_ctrlComboDoloreCCPO3.ShowWindow(SW_SHOW);
		m_ctrlComboDoloreCCPO4.ShowWindow(SW_SHOW);
		m_ctrlComboDoloreCCPO5.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CCPO_TOTALE)->ShowWindow(SW_SHOW);
	}
}