#include "stdafx.h"
#include "Endox.h"
#include "MonitoraggioOrizDlg.h"

#include "EsamiSet.h"
#include "EsamiView.h"

#include "VitalSignDispositiviSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMonitoraggioOrizDlg, CDialog)

CMonitoraggioOrizDlg::CMonitoraggioOrizDlg(CWnd* pParent, CEsamiView* pEsamiView, long lRecord)
	: CDialog(CMonitoraggioOrizDlg::IDD, pParent)
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

CMonitoraggioOrizDlg::~CMonitoraggioOrizDlg()
{
	m_setRecord.CloseRecordset("CMonitoraggioOrizDlg::~CMonitoraggioOrizDlg");
}

BEGIN_MESSAGE_MAP(CMonitoraggioOrizDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, OnCbnSelchangeCombo4)

	ON_CBN_SELCHANGE(IDC_COMBO1_GLASGOW, OnCbnSelchangeCombo1Glasgow)
	ON_CBN_SELCHANGE(IDC_COMBO2_GLASGOW, OnCbnSelchangeCombo2Glasgow)
	ON_CBN_SELCHANGE(IDC_COMBO3_GLASGOW, OnCbnSelchangeCombo3Glasgow)
END_MESSAGE_MAP()

void CMonitoraggioOrizDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_ORA, m_ctrlEditOra);
	DDX_Control(pDX, IDC_EDIT_FC, m_ctrlEditFC);
	DDX_Control(pDX, IDC_EDIT_PA, m_ctrlEditPA);
	DDX_Control(pDX, IDC_EDIT_SAT, m_ctrlEditSat);
	DDX_Control(pDX, IDC_EDIT_O2, m_ctrlEditO2);
	DDX_Control(pDX, IDC_EDIT_MIDA, m_ctrlEditMida);
	DDX_Control(pDX, IDC_EDIT_PETI, m_ctrlEditPeti);
	DDX_Control(pDX, IDC_EDIT_ATRO, m_ctrlEditAtro);
	DDX_Control(pDX, IDC_EDIT_NALO, m_ctrlEditNalo);
	DDX_Control(pDX, IDC_EDIT_FLUM, m_ctrlEditFlum);
	DDX_Control(pDX, IDC_EDIT_SCOP, m_ctrlEditScop);
	DDX_Control(pDX, IDC_EDIT_GLUC, m_ctrlEditGluc);
	DDX_Control(pDX, IDC_EDIT_ALTRI, m_ctrlEditAltri);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlCombo1);
	DDX_Control(pDX, IDC_COMBO2, m_ctrlCombo2);
	DDX_Control(pDX, IDC_COMBO3, m_ctrlCombo3);
	DDX_Control(pDX, IDC_COMBO4, m_ctrlCombo4);
	DDX_Control(pDX, IDC_STATIC_SCORE, m_ctrlStaticScore);
	DDX_Control(pDX, IDC_COMBO1_GLASGOW, m_ctrlCombo1Glasgow);
	DDX_Control(pDX, IDC_COMBO2_GLASGOW, m_ctrlCombo2Glasgow);
	DDX_Control(pDX, IDC_COMBO3_GLASGOW, m_ctrlCombo3Glasgow);
	DDX_Control(pDX, IDC_STATIC_SCORE_GLASGOW, m_ctrlStaticScoreGlasgow);

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

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_06, m_ctrlStatic06);
	DDX_Control(pDX, IDC_STATIC_07, m_ctrlStatic07);
	DDX_Control(pDX, IDC_STATIC_08, m_ctrlStatic08);
	DDX_Control(pDX, IDC_STATIC_09, m_ctrlStatic09);
	DDX_Control(pDX, IDC_STATIC_10, m_ctrlStatic10);
	DDX_Control(pDX, IDC_STATIC_11, m_ctrlStatic11);
	DDX_Control(pDX, IDC_STATIC_12, m_ctrlStatic12);
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

	DDX_Control(pDX, IDC_STATIC_1_GLASGOW, m_ctrlStatic1Glasgow);
	DDX_Control(pDX, IDC_STATIC_2_GLASGOW, m_ctrlStatic2Glasgow);
	DDX_Control(pDX, IDC_STATIC_3_GLASGOW, m_ctrlStatic3Glasgow);
	DDX_Control(pDX, IDC_STATIC_4_GLASGOW, m_ctrlStatic4Glasgow);

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
	DDX_Control(pDX, IDC_COMBO_DOLORE, m_ctrlDolore);
}

BOOL CMonitoraggioOrizDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	m_ctrlFase.ResetContent();

	m_ctrlFase.InsertString(0, "");
	m_ctrlFase.InsertString(1, theApp.GetMessageString(IDS_PRE));
	m_ctrlFase.SetItemData(1, MonitoringPhase::pre);
	m_ctrlFase.InsertString(2, theApp.GetMessageString(IDS_INTRA));
	m_ctrlFase.SetItemData(2, MonitoringPhase::intra);
	m_ctrlFase.InsertString(3, theApp.GetMessageString(IDS_POST));
	m_ctrlFase.SetItemData(3, MonitoringPhase::post);
	m_ctrlFase.InsertString(4, theApp.GetMessageString(IDS_SALA_RISVEGLIO));
	m_ctrlFase.SetItemData(4, MonitoringPhase::recoveryRoom);
	m_ctrlFase.InsertString(5, theApp.GetMessageString(IDS_DIMISSIONE));
	m_ctrlFase.SetItemData(5, MonitoringPhase::discharge);

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

	m_ctrlCombo2.ResetContent();
	m_ctrlCombo2.InsertString(0, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_5));
	m_ctrlCombo1.SetItemData(0, 5);
	m_ctrlCombo2.InsertString(1, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_4));
	m_ctrlCombo1.SetItemData(1, 4);
	m_ctrlCombo2.InsertString(2, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_3));
	m_ctrlCombo1.SetItemData(2, 3);
	m_ctrlCombo2.InsertString(3, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_2));
	m_ctrlCombo1.SetItemData(3, 2);
	m_ctrlCombo2.InsertString(4, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO2_1));
	m_ctrlCombo1.SetItemData(4, 0);

	m_ctrlCombo3.ResetContent();
	m_ctrlCombo3.InsertString(0, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_4));
	m_ctrlCombo1.SetItemData(0, 5);
	m_ctrlCombo3.InsertString(1, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_3));
	m_ctrlCombo1.SetItemData(1, 4);
	m_ctrlCombo3.InsertString(2, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_2));
	m_ctrlCombo1.SetItemData(2, 3);
	m_ctrlCombo3.InsertString(3, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO3_1));
	m_ctrlCombo1.SetItemData(3, 0);

	m_ctrlCombo4.ResetContent();
	m_ctrlCombo4.InsertString(0, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO4_4));
	m_ctrlCombo1.SetItemData(0, 5);
	m_ctrlCombo4.InsertString(1, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO4_3));
	m_ctrlCombo1.SetItemData(1, 4);
	m_ctrlCombo4.InsertString(2, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO4_2));
	m_ctrlCombo1.SetItemData(2, 3);
	m_ctrlCombo4.InsertString(3, theApp.GetMessageString(IDS_MONITORAGGIO_COMBO4_1));
	m_ctrlCombo1.SetItemData(3, 0);

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

	theApp.LocalizeDialog(this, CMonitoraggioOrizDlg::IDD, "MonitoraggioOrizDlg");

	if (m_lRecord <= 0)
	{
		CString strFilter;
		strFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		SetWindowText(theApp.GetMessageString(IDS_MONITORAGGIO_NEW));

		m_setRecord.SetOpenFilter(strFilter);
		m_setRecord.OpenRecordset("CMonitoraggioOrizDlg::OnInitDialog");

		SYSTEMTIME stime;
		GetLocalTime(&stime);

		CString strTemp;
		strTemp.Format("%02d.%02d.%02d", stime.wHour, stime.wMinute, stime.wSecond);
		m_ctrlEditOra.SetWindowText(strTemp);

		m_ctrlFase.SetCurSel(0);
		m_ctrlCombo1.SetCurSel(0);
		m_ctrlCombo2.SetCurSel(0);
		m_ctrlCombo3.SetCurSel(0);
		m_ctrlCombo4.SetCurSel(0);
		m_ctrlDolore.SetCurSel(0);

		m_ctrlCombo1Glasgow.SetCurSel(4);
		m_ctrlCombo2Glasgow.SetCurSel(5);
		m_ctrlCombo3Glasgow.SetCurSel(6);

		if (theApp.m_bUsaScoreDiGlasgow)
			RecalculateGlasgow();
		else
			OnCbnSelchangeCombo4();
	}
	else
	{
		CString strFilter;
		strFilter.Format("ID=%li", m_lRecord);

		SetWindowText(theApp.GetMessageString(IDS_MONITORAGGIO_MOD));

		m_setRecord.SetOpenFilter(strFilter);
		if (m_setRecord.OpenRecordset("CMonitoraggioOrizDlg::OnInitDialog"))
		{
			if (!m_setRecord.IsEOF())
			{
				CString strTemp;

				if (theApp.m_bVitalSignIntegrazioneAttiva)
				{
					m_ctrlFase.SetCurSel(0);
				}
				else
				{
					if (!m_setRecord.IsFieldNull(&m_setRecord.m_lQuando))
						m_ctrlFase.SetCurSel(m_setRecord.m_lQuando);
					else
						m_ctrlFase.SetCurSel(0);
				}

				m_ctrlEditOra.SetWindowText(m_setRecord.m_strOra);
				m_ctrlEditFC.SetWindowText(m_setRecord.m_strFC);
				m_ctrlEditPA.SetWindowText(m_setRecord.m_strPA);
				m_ctrlEditSat.SetWindowText(m_setRecord.m_strSat);
				m_ctrlEditO2.SetWindowText(m_setRecord.m_strO2);
				m_ctrlEditMida.SetWindowText(m_setRecord.m_strMida);
				m_ctrlEditPeti.SetWindowText(m_setRecord.m_strPeti);
				m_ctrlEditAtro.SetWindowText(m_setRecord.m_strAtro);
				m_ctrlEditNalo.SetWindowText(m_setRecord.m_strNalo);
				m_ctrlEditFlum.SetWindowText(m_setRecord.m_strFlum);
				m_ctrlEditScop.SetWindowText(m_setRecord.m_strScop);
				m_ctrlEditGluc.SetWindowText(m_setRecord.m_strGluc);
				m_ctrlEditAltri.SetWindowText(m_setRecord.m_strAltri);

				if (!m_setRecord.IsFieldNull(&m_setRecord.m_lDoloreVAS))
					m_ctrlDolore.SetCurSel(m_setRecord.m_lDoloreVAS);
				else
					m_ctrlDolore.SetCurSel(0);

				strTemp.Format("%d", m_setRecord.m_lPuntiScore1);
				m_ctrlCombo1.SetCurSel(m_ctrlCombo1.FindString(-1, strTemp.Left(1)));

				strTemp.Format("%d", m_setRecord.m_lPuntiScore2);
				m_ctrlCombo2.SetCurSel(m_ctrlCombo2.FindString(-1, strTemp.Left(1)));

				strTemp.Format("%d", m_setRecord.m_lPuntiScore3);
				m_ctrlCombo3.SetCurSel(m_ctrlCombo3.FindString(-1, strTemp.Left(1)));

				strTemp.Format("%d", m_setRecord.m_lPuntiScore4);
				m_ctrlCombo4.SetCurSel(m_ctrlCombo4.FindString(-1, strTemp.Left(1)));

				//GLASGOW
				for (int i = 0; i<m_ctrlCombo1Glasgow.GetCount(); i++)
				{
					if (m_ctrlCombo1Glasgow.GetItemData(i) == m_setRecord.m_lPuntiScore1Glasgow)
					{
						m_ctrlCombo1Glasgow.SetCurSel(i);
						break;
					}
				}

				for (int i = 0; i<m_ctrlCombo2Glasgow.GetCount(); i++)
				{
					if (m_ctrlCombo2Glasgow.GetItemData(i) == m_setRecord.m_lPuntiScore2Glasgow)
					{
						m_ctrlCombo2Glasgow.SetCurSel(i);
						break;
					}
				}

				for (int i = 0; i<m_ctrlCombo3Glasgow.GetCount(); i++)
				{
					if (m_ctrlCombo3Glasgow.GetItemData(i) == m_setRecord.m_lPuntiScore3Glasgow)
					{
						m_ctrlCombo3Glasgow.SetCurSel(i);
						break;
					}
				}
				//

				UpdateData(FALSE);

				if (theApp.m_bUsaScoreDiGlasgow)
					RecalculateGlasgow();
				else
					OnCbnSelchangeCombo4();
			}
		}
	}

	//Se uso lo score di glasgow mostro i controlli e nascondo quelli di Chernik
	if (theApp.m_bUsaScoreDiGlasgow)
	{
		//Glasgow
		m_ctrlStatic1Glasgow.ShowWindow(SW_SHOW);
		m_ctrlStatic2Glasgow.ShowWindow(SW_SHOW);
		m_ctrlStatic3Glasgow.ShowWindow(SW_SHOW);
		m_ctrlStatic4Glasgow.ShowWindow(SW_SHOW);
		m_ctrlStaticScoreGlasgow.ShowWindow(SW_SHOW);
		m_ctrlCombo1Glasgow.ShowWindow(SW_SHOW);
		m_ctrlCombo2Glasgow.ShowWindow(SW_SHOW);
		m_ctrlCombo3Glasgow.ShowWindow(SW_SHOW);

		//Chernik
		m_ctrlStatic13.ShowWindow(SW_HIDE);
		m_ctrlStatic14.ShowWindow(SW_HIDE);
		m_ctrlStatic15.ShowWindow(SW_HIDE);
		m_ctrlStatic16.ShowWindow(SW_HIDE);
		m_ctrlStatic17.ShowWindow(SW_HIDE);
		m_ctrlStaticScore.ShowWindow(SW_HIDE);
		m_ctrlCombo1.ShowWindow(SW_HIDE);
		m_ctrlCombo2.ShowWindow(SW_HIDE);
		m_ctrlCombo3.ShowWindow(SW_HIDE);
		m_ctrlCombo4.ShowWindow(SW_HIDE);
	}

	return bReturn;
}

void CMonitoraggioOrizDlg::OnOK()
{
	UpdateData(TRUE);

	if (m_lRecord <= 0) // addnew //
	{
		if (m_setRecord.AddNewRecordset("CMonitoraggioOrizDlg::OnOK"))
		{
			CString strTemp;

			m_setRecord.m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
			
			m_setRecord.m_lQuando = m_ctrlFase.GetItemData(m_ctrlFase.GetCurSel());

			m_ctrlEditOra.GetWindowText(m_setRecord.m_strOra);
			m_ctrlEditFC.GetWindowText(m_setRecord.m_strFC);
			m_ctrlEditPA.GetWindowText(m_setRecord.m_strPA);
			m_ctrlEditSat.GetWindowText(m_setRecord.m_strSat);
			m_ctrlEditO2.GetWindowText(m_setRecord.m_strO2);
			m_ctrlEditMida.GetWindowText(m_setRecord.m_strMida);
			m_ctrlEditPeti.GetWindowText(m_setRecord.m_strPeti);
			m_ctrlEditAtro.GetWindowText(m_setRecord.m_strAtro);
			m_ctrlEditNalo.GetWindowText(m_setRecord.m_strNalo);
			m_ctrlEditFlum.GetWindowText(m_setRecord.m_strFlum);
			m_ctrlEditScop.GetWindowText(m_setRecord.m_strScop);
			m_ctrlEditGluc.GetWindowText(m_setRecord.m_strGluc);
			m_ctrlEditAltri.GetWindowText(m_setRecord.m_strAltri);
			m_setRecord.m_lDoloreVAS = m_ctrlDolore.GetCurSel();

			m_setRecord.m_lPuntiScore1 = m_ctrlCombo1.GetItemData(m_ctrlCombo1.GetCurSel());
			m_setRecord.m_lPuntiScore2 = m_ctrlCombo1.GetItemData(m_ctrlCombo2.GetCurSel());
			m_setRecord.m_lPuntiScore3 = m_ctrlCombo1.GetItemData(m_ctrlCombo3.GetCurSel());
			m_setRecord.m_lPuntiScore4 = m_ctrlCombo1.GetItemData(m_ctrlCombo4.GetCurSel());
			m_setRecord.m_lTotalScore = m_setRecord.m_lPuntiScore1 + m_setRecord.m_lPuntiScore2 + m_setRecord.m_lPuntiScore3 + m_setRecord.m_lPuntiScore4;

			m_setRecord.m_lPuntiScore1Glasgow = m_ctrlCombo1Glasgow.GetItemData(m_ctrlCombo1Glasgow.GetCurSel());
			m_setRecord.m_lPuntiScore2Glasgow = m_ctrlCombo2Glasgow.GetItemData(m_ctrlCombo2Glasgow.GetCurSel());
			m_setRecord.m_lPuntiScore3Glasgow = m_ctrlCombo3Glasgow.GetItemData(m_ctrlCombo3Glasgow.GetCurSel());
			m_setRecord.m_lTotalScoreGlasgow = m_setRecord.m_lPuntiScore1Glasgow + m_setRecord.m_lPuntiScore2Glasgow + m_setRecord.m_lPuntiScore3Glasgow;

			m_setRecord.m_strPA.Replace("/", "");
			int nMiddlePA = (m_setRecord.m_strPA.GetLength() + 1) / 2;
			if (nMiddlePA > 0)
				m_setRecord.m_strPA = m_setRecord.m_strPA.Left(nMiddlePA) + "/" + m_setRecord.m_strPA.Right(m_setRecord.m_strPA.GetLength() - nMiddlePA);

			m_setRecord.UpdateRecordset("CMonitoraggioOrizDlg::OnOK");

			m_lRecord = m_setRecord.GetLastAdd();

		}
	}
	else // edit //
	{
		if (m_setRecord.EditRecordset("CMonitoraggioOrizDlg::OnOK"))
		{
			CString strTemp;

			m_setRecord.m_lQuando = m_ctrlFase.GetItemData(m_ctrlFase.GetCurSel());
			m_ctrlEditOra.GetWindowText(m_setRecord.m_strOra);
			m_ctrlEditFC.GetWindowText(m_setRecord.m_strFC);
			m_ctrlEditPA.GetWindowText(m_setRecord.m_strPA);
			m_ctrlEditSat.GetWindowText(m_setRecord.m_strSat);
			m_ctrlEditO2.GetWindowText(m_setRecord.m_strO2);
			m_ctrlEditMida.GetWindowText(m_setRecord.m_strMida);
			m_ctrlEditPeti.GetWindowText(m_setRecord.m_strPeti);
			m_ctrlEditAtro.GetWindowText(m_setRecord.m_strAtro);
			m_ctrlEditNalo.GetWindowText(m_setRecord.m_strNalo);
			m_ctrlEditFlum.GetWindowText(m_setRecord.m_strFlum);
			m_ctrlEditScop.GetWindowText(m_setRecord.m_strScop);
			m_ctrlEditGluc.GetWindowText(m_setRecord.m_strGluc);
			m_ctrlEditAltri.GetWindowText(m_setRecord.m_strAltri);
			m_setRecord.m_lDoloreVAS = m_ctrlDolore.GetCurSel();

			m_setRecord.m_lPuntiScore1 = m_ctrlCombo1.GetItemData(m_ctrlCombo1.GetCurSel());
			m_setRecord.m_lPuntiScore2 = m_ctrlCombo1.GetItemData(m_ctrlCombo2.GetCurSel());
			m_setRecord.m_lPuntiScore3 = m_ctrlCombo1.GetItemData(m_ctrlCombo3.GetCurSel());
			m_setRecord.m_lPuntiScore4 = m_ctrlCombo1.GetItemData(m_ctrlCombo4.GetCurSel());
			m_setRecord.m_lTotalScore = m_setRecord.m_lPuntiScore1 + m_setRecord.m_lPuntiScore2 + m_setRecord.m_lPuntiScore3 + m_setRecord.m_lPuntiScore4;

			m_setRecord.m_lPuntiScore1Glasgow = m_ctrlCombo1Glasgow.GetItemData(m_ctrlCombo1Glasgow.GetCurSel());
			m_setRecord.m_lPuntiScore2Glasgow = m_ctrlCombo2Glasgow.GetItemData(m_ctrlCombo2Glasgow.GetCurSel());
			m_setRecord.m_lPuntiScore3Glasgow = m_ctrlCombo3Glasgow.GetItemData(m_ctrlCombo3Glasgow.GetCurSel());
			m_setRecord.m_lTotalScoreGlasgow = m_setRecord.m_lPuntiScore1Glasgow + m_setRecord.m_lPuntiScore2Glasgow + m_setRecord.m_lPuntiScore3Glasgow;

			m_setRecord.m_strPA.Replace("/", "");
			int nMiddlePA = (m_setRecord.m_strPA.GetLength() + 1) / 2;
			if (nMiddlePA > 0)
				m_setRecord.m_strPA = m_setRecord.m_strPA.Left(nMiddlePA) + "/" + m_setRecord.m_strPA.Right(m_setRecord.m_strPA.GetLength() - nMiddlePA);

			m_setRecord.UpdateRecordset("CMonitoraggioOrizDlg::OnOK");
		}
	}

	CDialog::OnOK();
}

void CMonitoraggioOrizDlg::OnCbnSelchangeCombo1()
{
	CString strTemp;

	UpdateData(TRUE);

	m_ctrlCombo1.GetLBText(m_ctrlCombo1.GetCurSel(), strTemp);
	switch(atoi(strTemp.Left(1)))
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

	m_ctrlCombo1.GetLBText(m_ctrlCombo1.GetCurSel(), strTemp);
	m_nPuntiScore1 = atoi(strTemp.Left(1));
	m_ctrlCombo2.GetLBText(m_ctrlCombo2.GetCurSel(), strTemp);
	m_nPuntiScore2 = atoi(strTemp.Left(1));
	m_ctrlCombo3.GetLBText(m_ctrlCombo3.GetCurSel(), strTemp);
	m_nPuntiScore3 = atoi(strTemp.Left(1));
	m_ctrlCombo4.GetLBText(m_ctrlCombo4.GetCurSel(), strTemp);
	m_nPuntiScore4 = atoi(strTemp.Left(1));

	m_nTotalScore = m_nPuntiScore1 + m_nPuntiScore2 + m_nPuntiScore3 + m_nPuntiScore4;

	UpdateData(FALSE);
}

void CMonitoraggioOrizDlg::OnCbnSelchangeCombo2()
{
	CString strTemp;

	UpdateData(TRUE);

	m_ctrlCombo2.GetLBText(m_ctrlCombo1.GetCurSel(), strTemp);
	switch(atoi(strTemp.Left(1)))
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

	m_ctrlCombo1.GetLBText(m_ctrlCombo1.GetCurSel(), strTemp);
	m_nPuntiScore1 = atoi(strTemp.Left(1));
	m_ctrlCombo2.GetLBText(m_ctrlCombo2.GetCurSel(), strTemp);
	m_nPuntiScore2 = atoi(strTemp.Left(1));
	m_ctrlCombo3.GetLBText(m_ctrlCombo3.GetCurSel(), strTemp);
	m_nPuntiScore3 = atoi(strTemp.Left(1));
	m_ctrlCombo4.GetLBText(m_ctrlCombo4.GetCurSel(), strTemp);
	m_nPuntiScore4 = atoi(strTemp.Left(1));

	m_nTotalScore = m_nPuntiScore1 + m_nPuntiScore2 + m_nPuntiScore3 + m_nPuntiScore4;

	UpdateData(FALSE);
}

void CMonitoraggioOrizDlg::OnCbnSelchangeCombo3()
{
	CString strTemp;

	UpdateData(TRUE);

	if (m_ctrlCombo4.GetCurSel() < m_ctrlCombo3.GetCurSel())
		m_ctrlCombo4.SetCurSel(m_ctrlCombo3.GetCurSel());

	m_ctrlCombo1.GetLBText(m_ctrlCombo1.GetCurSel(), strTemp);
	m_nPuntiScore1 = atoi(strTemp.Left(1));
	m_ctrlCombo2.GetLBText(m_ctrlCombo2.GetCurSel(), strTemp);
	m_nPuntiScore2 = atoi(strTemp.Left(1));
	m_ctrlCombo3.GetLBText(m_ctrlCombo3.GetCurSel(), strTemp);
	m_nPuntiScore3 = atoi(strTemp.Left(1));
	m_ctrlCombo4.GetLBText(m_ctrlCombo4.GetCurSel(), strTemp);
	m_nPuntiScore4 = atoi(strTemp.Left(1));

	m_nTotalScore = m_nPuntiScore1 + m_nPuntiScore2 + m_nPuntiScore3 + m_nPuntiScore4;

	UpdateData(FALSE);
}

void CMonitoraggioOrizDlg::OnCbnSelchangeCombo4()
{
	CString strTemp;

	UpdateData(TRUE);

	m_ctrlCombo1.GetLBText(m_ctrlCombo1.GetCurSel(), strTemp);
	m_nPuntiScore1 = atoi(strTemp.Left(1));
	m_ctrlCombo2.GetLBText(m_ctrlCombo2.GetCurSel(), strTemp);
	m_nPuntiScore2 = atoi(strTemp.Left(1));
	m_ctrlCombo3.GetLBText(m_ctrlCombo3.GetCurSel(), strTemp);
	m_nPuntiScore3 = atoi(strTemp.Left(1));
	m_ctrlCombo4.GetLBText(m_ctrlCombo4.GetCurSel(), strTemp);
	m_nPuntiScore4 = atoi(strTemp.Left(1));

	m_nTotalScore = m_nPuntiScore1 + m_nPuntiScore2 + m_nPuntiScore3 + m_nPuntiScore4;

	UpdateData(FALSE);
}

void CMonitoraggioOrizDlg::OnCbnSelchangeCombo1Glasgow()
{
	CString strTemp;

	UpdateData(TRUE);

	RecalculateGlasgow();

	UpdateData(FALSE);
}

void CMonitoraggioOrizDlg::OnCbnSelchangeCombo2Glasgow()
{
	CString strTemp;

	UpdateData(TRUE);

	RecalculateGlasgow();

	UpdateData(FALSE);
}

void CMonitoraggioOrizDlg::OnCbnSelchangeCombo3Glasgow()
{
	CString strTemp;

	UpdateData(TRUE);

	RecalculateGlasgow();

	UpdateData(FALSE);
}

void CMonitoraggioOrizDlg::RecalculateGlasgow()
{
	CString strTemp;

	UpdateData(TRUE);

	m_nPuntiScore1Glasgow = m_ctrlCombo1Glasgow.GetItemData(m_ctrlCombo1Glasgow.GetCurSel());
	m_nPuntiScore2Glasgow = m_ctrlCombo2Glasgow.GetItemData(m_ctrlCombo2Glasgow.GetCurSel());
	m_nPuntiScore3Glasgow = m_ctrlCombo3Glasgow.GetItemData(m_ctrlCombo3Glasgow.GetCurSel());

	m_nTotalScoreGlasgow = m_nPuntiScore1Glasgow + m_nPuntiScore2Glasgow + m_nPuntiScore3Glasgow;

	UpdateData(FALSE);
}

HBRUSH CMonitoraggioOrizDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_17:
		case IDC_STATIC_SCORE:
		{
			pDC->SetTextColor(m_colorScore);
			break;
		}
	}

	return hBrush;
}