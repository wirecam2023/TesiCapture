#include "stdafx.h"
#include "Endox.h"
#include "MonitoraggioOrizDynForm.h"

#include "ArchivioStampeDlg.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "MonitoraggioOrizDlg.h"
#include "MonitoraggioSet.h"
#include "PdfManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMonitoraggioOrizDynForm::CMonitoraggioOrizDynForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CMonitoraggioBaseDynForm(CMonitoraggioOrizDynForm::IDD, pParent, pEsamiView), m_ctrlList(FALSE,TRUE, FALSE)
{
}

CMonitoraggioOrizDynForm::~CMonitoraggioOrizDynForm(void)
{
}

BEGIN_MESSAGE_MAP(CMonitoraggioOrizDynForm, CMonitoraggioBaseDynForm)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_BTN_ADD, OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	// ON_BN_CLICKED(IDC_BTN_REFRESH, OnBnClickedBtnRef)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemChangedList)

	ON_MESSAGE(WM_MONITORAGGIOLISTEV, OnMonitoraggioListEv)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CMonitoraggioOrizDynForm::OnBnClickedBtnRefresh)
END_MESSAGE_MAP()

void CMonitoraggioOrizDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_monitoraggio_oriz] == NULL)
	{
		pEsamiView->m_pDynForm[sub_monitoraggio_oriz] = new CMonitoraggioOrizDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_monitoraggio_oriz] != NULL)
		{
			pEsamiView->m_pDynForm[sub_monitoraggio_oriz]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_monitoraggio_oriz]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_monitoraggio_oriz]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_monitoraggio_oriz]->CreateChildForm(CMonitoraggioOrizDynForm::IDD, pParent, rectFrame);
		}
	}
}

void CMonitoraggioOrizDynForm::DoDataExchange(CDataExchange* pDX)
{
	CMonitoraggioBaseDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_STATIC_LABEL1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_LABEL2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_LABEL3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_BTN_ADD, m_ctrlBtnAdd);
	DDX_Control(pDX, IDC_BTN_EDIT, m_ctrlBtnEdit);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);
	// DDX_Control(pDX, IDC_BTN_REFRESH, m_ctrlBtnRef);

	DDX_FieldText(pDX, IDC_EDIT_NOTE, m_pEsamiView->m_pEsamiSet->m_sNoteMonitoraggio, m_pEsamiView->m_pEsamiSet->GetRecordset());

	// INFERMIERE //

	DDX_Control(pDX, IDC_COMBO_INFERMIERE, m_ctrlInfermiere);
	DDX_Control(pDX, IDC_EDIT_INFERMIERE, m_ctrlInfermiereTxt);
	DDX_FieldInfermieriCombo(pDX, IDC_COMBO_INFERMIERE, m_pEsamiView->m_pEsamiSet->m_lInfermiereMonitoraggio, m_pEsamiView->m_pEsamiSet);
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		DDX_Text(pDX, IDC_EDIT_INFERMIERE, m_ctrlInfermiereTxt.m_strRicercaView);
	else
		DDX_FieldInfermieriEdit(pDX, IDC_EDIT_INFERMIERE, m_pEsamiView->m_pEsamiSet->m_lInfermiereMonitoraggio, m_pEsamiView->m_pEsamiSet);

	// Sandro 03/08/2015 //

	if (!pDX->m_bSaveAndValidate)
	{
		BOOL bEnable = m_pEsamiView->m_bPazientiValid && m_pEsamiView->m_bEsamiValid && (m_pEsamiView->m_pEsamiSet->m_lContatore > 0) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto;

		if ((m_pEsamiView->m_pEsamiSet->m_bLocked == TRUE) && (m_lIDFaseBlocco <= 0)) // Davide - in ricerca m_bLocked è uguale a 2
			bEnable = FALSE;

		if ((m_pEsamiView->m_pEsamiSet->m_bSuperLocked == TRUE) && (m_lIDFaseBlocco <= 1)) // Sandro // in ricerca m_bSuperLocked è uguale a 2 //
			bEnable = FALSE;

		m_ctrlBtnAdd.EnableWindow(bEnable);
		m_ctrlBtnEdit.EnableWindow(bEnable && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
		m_ctrlBtnDel.EnableWindow(bEnable && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));

		if (m_pEsamiView->m_bMonitoraggioAttivo)
		{
			GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_EDIT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
			return;
		}
	}
}

HBRUSH CMonitoraggioOrizDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CMonitoraggioBaseDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_LABEL1:
		case IDC_STATIC_LABEL2:
		case IDC_STATIC_LABEL3:
		case IDC_COMBO_INFERMIERE:
		case IDC_EDIT_INFERMIERE:
		case IDC_EDIT_NOTE:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	if (m_lColore >= 0)
		m_ctrlList.SetTextColor(theApp.m_color[m_lColore]);

	return hReturn;
}

BOOL CMonitoraggioOrizDynForm::OnInitDialog()
{
	BOOL bReturn = CMonitoraggioBaseDynForm::OnInitDialog();

	GetDlgItem(IDC_STATIC_LABEL1)->SetFont(&theApp.m_fontBold);

	AddAnchor(IDC_STATIC_LABEL1, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 75));
	AddAnchor(IDC_STATIC_LABEL3, CSize(0, 75), CSize(10, 75));
	AddAnchor(IDC_COMBO_INFERMIERE, CSize(10, 75), CSize(30, 75));
	AddAnchor(IDC_EDIT_INFERMIERE, CSize(10, 75), CSize(30, 75));
	AddAnchor(IDC_BTN_ADD, CSize(100, 75), CSize(100, 75));
	AddAnchor(IDC_BTN_EDIT, CSize(100, 75), CSize(100, 75));
	AddAnchor(IDC_BTN_DEL, CSize(100, 75), CSize(100, 75));
	AddAnchor(IDC_BTN_REFRESH, CSize(100, 75), CSize(100, 75));
	AddAnchor(IDC_STATIC_LABEL2, CSize(0, 75), CSize(100, 75));
	AddAnchor(IDC_EDIT_NOTE, CSize(0, 75), CSize(100, 100));

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "PDF", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(2, theApp.GetMessageString(IDS_FASE), LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(3, theApp.GetMessageString(IDS_ORE), LVCFMT_CENTER, 65);
	m_ctrlList.InsertColumn(4, theApp.GetMessageString(IDS_MONITORAGGIOFORM_COL02), LVCFMT_RIGHT, 65);
	m_ctrlList.InsertColumn(5, theApp.GetMessageString(IDS_MONITORAGGIOFORM_COL03), LVCFMT_RIGHT, 65);
	m_ctrlList.InsertColumn(6, theApp.GetMessageString(IDS_MONITORAGGIOFORM_COL04), LVCFMT_RIGHT, 65);
	m_ctrlList.InsertColumn(7, theApp.GetMessageString(IDS_O2), LVCFMT_RIGHT, 65);
	m_ctrlList.InsertColumn(8, theApp.GetMessageString(IDS_MONITORAGGIOFORM_COL06), LVCFMT_RIGHT, 70);
	m_ctrlList.InsertColumn(9, theApp.GetMessageString(IDS_MONITORAGGIOFORM_COL07), LVCFMT_RIGHT, 70);
	m_ctrlList.InsertColumn(10, theApp.GetMessageString(IDS_MONITORAGGIOFORM_COL08), LVCFMT_RIGHT, 70);
	m_ctrlList.InsertColumn(11, theApp.GetMessageString(IDS_MONITORAGGIOFORM_COL09), LVCFMT_RIGHT, 70);
	m_ctrlList.InsertColumn(12, theApp.GetMessageString(IDS_MONITORAGGIOFORM_COL10), LVCFMT_RIGHT, 70);
	m_ctrlList.InsertColumn(13, theApp.GetMessageString(IDS_MONITORAGGIOFORM_COL11), LVCFMT_RIGHT, 70);
	m_ctrlList.InsertColumn(14, theApp.GetMessageString(IDS_MONITORAGGIOFORM_COL12), LVCFMT_RIGHT, 70);
	m_ctrlList.InsertColumn(15, theApp.GetMessageString(IDS_MONITORAGGIOFORM_COL13), LVCFMT_RIGHT, 70);
	m_ctrlList.InsertColumn(16, theApp.GetMessageString(IDS_DOLORE), LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(17, theApp.GetMessageString(IDS_SCORE), LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(18, "Score1", LVCFMT_RIGHT, 0);
	m_ctrlList.InsertColumn(19, "Score2", LVCFMT_RIGHT, 0);
	m_ctrlList.InsertColumn(20, "Score3", LVCFMT_RIGHT, 0);

	if (!theApp.m_bUsaScoreDiGlasgow)
		m_ctrlList.InsertColumn(21, "Score4", LVCFMT_RIGHT, 0);

	m_ctrlInfermiereTxt.SetParam(this, m_pEsamiView->m_pEsamiSet);

	m_ctrlList.SetNotificationChangeValueMessage(WM_MONITORAGGIOLISTEV);

	theApp.LocalizeDialog(this, CMonitoraggioOrizDynForm::IDD, "MonitoraggioDynForm");

	// RiempiLista();

	return bReturn;
}

long CMonitoraggioOrizDynForm::GetContenuto()
{
	return sub_monitoraggio_oriz;
}

BOOL CMonitoraggioOrizDynForm::CampoObbligatorioValido()
{
	return TRUE;
}

void CMonitoraggioOrizDynForm::OnBnClickedBtnAdd()
{
	m_ctrlBtnAdd.SetCheck(BST_UNCHECKED);

	CMonitoraggioOrizDlg dlg(this, m_pEsamiView, -1);
	if (dlg.DoModal() == IDOK)
	{
		RiempiLista();
		OnLvnItemChangedList(NULL, NULL);

		/*if (theApp.m_bVitalSignIntegrazioneAttiva && dlg.m_lRecord > 0)
			m_pEsamiView->PostMessage(EPM_THREAD_STARTMONITORAGGIO, dlg.m_lRecord, 0);*/
	}
}

void CMonitoraggioOrizDynForm::OnBnClickedBtnEdit()
{
	m_ctrlBtnEdit.SetCheck(BST_UNCHECKED);

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlList.GetNextSelectedItem(pos);

		CMonitoraggioOrizDlg dlg(this, m_pEsamiView, m_ctrlList.GetItemData(iCurSel));
		if (dlg.DoModal() == IDOK)
			RiempiLista();
	}
}

void CMonitoraggioOrizDynForm::OnBnClickedBtnDel()
{
	m_ctrlBtnDel.SetCheck(BST_UNCHECKED);

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DELETE_MONIT_ROW), MB_YESNO) == IDYES)
		{
			CMonitoraggioSet setTemp;

			int nIndex = m_ctrlList.GetNextSelectedItem(pos);
			if (nIndex >= 0)
			{
				long lID = (long)m_ctrlList.GetItemData(nIndex);

				if (lID > 0)
				{
					CString strFilter;
					strFilter.Format("ID=%li", lID);

					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CMonitoraggioOrizDynForm::OnBnClickedBtnDel"))
					{
						BOOL bDeleted = FALSE;

						if (!setTemp.IsEOF())
							bDeleted = setTemp.DeleteRecordset("CMonitoraggioOrizDynForm::OnBnClickedBtnDel");

						setTemp.CloseRecordset("CMonitoraggioOrizDynForm::OnBnClickedBtnDel");

						if (bDeleted)
							OnFormLoad(NULL, NULL);
					}
				}
				else
				{
					m_ctrlList.DeleteItem(nIndex);
				}
			}

			OnLvnItemChangedList(NULL, NULL);
		}
	}
}

/*
void CMonitoraggioOrizDynForm::OnBnClickedBtnRef()
{
	m_ctrlBtnRef.SetCheck(BST_UNCHECKED);

	RiempiLista();
}
*/

void CMonitoraggioOrizDynForm::RiempiLista()
{
	CMonitoraggioSet setTemp;
	
	CString strFilter;
	strFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	setTemp.SetOpenFilter(strFilter);
	setTemp.SetSortRecord("Ora, ID");

	m_ctrlList.DeleteAllItems();

	if (setTemp.OpenRecordset("CMonitoraggioOrizDynForm::OnFormLoad"))
	{
		while(!setTemp.IsEOF())
		{
			int nIndex = m_ctrlList.GetItemCount();

			m_ctrlList.InsertItem(nIndex, "");
			m_ctrlList.SetItemData(nIndex, (DWORD)setTemp.m_lID);

			//Check per la stampa del pdf
			if (!setTemp.IsFieldNull(&setTemp.m_lIdPdf) && setTemp.m_lIdPdf > 0)
				m_ctrlList.SetSubItemCheck(nIndex, 1);

			if (!setTemp.IsFieldNull(&setTemp.m_lQuando))
			{
				switch(setTemp.m_lQuando)
				{
					case MonitoringPhase::pre:
					{
						m_ctrlList.SetItemText(nIndex, 2, theApp.GetMessageString(IDS_PRE));
						break;
					}
					case MonitoringPhase::intra:
					{
						m_ctrlList.SetItemText(nIndex, 2, theApp.GetMessageString(IDS_INTRA));
						break;
					}
					case MonitoringPhase::post:
					{
						m_ctrlList.SetItemText(nIndex, 2, theApp.GetMessageString(IDS_POST));
						break;
					}
					case MonitoringPhase::recoveryRoom:
					{
						m_ctrlList.SetItemText(nIndex, 2, theApp.GetMessageString(IDS_SALA_RISVEGLIO));
						break;
					}
					case MonitoringPhase::discharge:
					{
						m_ctrlList.SetItemText(nIndex, 2, theApp.GetMessageString(IDS_DIMISSIONE));
						break;
					}

				}
			}

			m_ctrlList.SetItemText(nIndex, 3, setTemp.m_strOra);
			m_ctrlList.SetItemText(nIndex, 4, setTemp.m_strFC);
			m_ctrlList.SetItemText(nIndex, 5, setTemp.m_strPA);
			m_ctrlList.SetItemText(nIndex, 6, setTemp.m_strSat);
			m_ctrlList.SetItemText(nIndex, 7, setTemp.m_strO2);
			m_ctrlList.SetItemText(nIndex, 8, setTemp.m_strMida);
			m_ctrlList.SetItemText(nIndex, 9, setTemp.m_strPeti);
			m_ctrlList.SetItemText(nIndex, 10, setTemp.m_strAtro);
			m_ctrlList.SetItemText(nIndex, 11, setTemp.m_strNalo);
			m_ctrlList.SetItemText(nIndex, 12, setTemp.m_strFlum);
			m_ctrlList.SetItemText(nIndex, 13, setTemp.m_strScop);
			m_ctrlList.SetItemText(nIndex, 14, setTemp.m_strGluc);
			m_ctrlList.SetItemText(nIndex, 15, setTemp.m_strAltri);

			if (!setTemp.IsFieldNull(&setTemp.m_lDoloreVAS))
			{
				CString strTemp;
				strTemp.Format("%li", setTemp.m_lDoloreVAS);
				m_ctrlList.SetItemText(nIndex, 16, strTemp);
			}			

			if (theApp.m_bUsaScoreDiGlasgow)
			{
				if (!setTemp.IsFieldNull(&setTemp.m_lTotalScoreGlasgow))
				{
					CString strTemp;
					if (setTemp.m_lTotalScoreGlasgow > 0)
						strTemp.Format("%li", setTemp.m_lTotalScoreGlasgow);
					else
						strTemp = "";
					m_ctrlList.SetItemText(nIndex, 17, strTemp);
				}
				if (!setTemp.IsFieldNull(&setTemp.m_lPuntiScore1Glasgow))
				{
					CString strTemp;
					strTemp.Format("%li", setTemp.m_lPuntiScore1Glasgow);
					m_ctrlList.SetItemText(nIndex, 18, strTemp);
				}
				if (!setTemp.IsFieldNull(&setTemp.m_lPuntiScore2Glasgow))
				{
					CString strTemp;
					strTemp.Format("%li", setTemp.m_lPuntiScore2Glasgow);
					m_ctrlList.SetItemText(nIndex, 19, strTemp);
				}
				if (!setTemp.IsFieldNull(&setTemp.m_lPuntiScore3Glasgow))
				{
					CString strTemp;
					strTemp.Format("%li", setTemp.m_lPuntiScore3Glasgow);
					m_ctrlList.SetItemText(nIndex, 20, strTemp);
				}
			}
			else
			{
				if (!setTemp.IsFieldNull(&setTemp.m_lTotalScore))
				{
					CString strTemp;
					if (setTemp.m_lTotalScore > 0)
						strTemp.Format("%li", setTemp.m_lTotalScore);
					else
						strTemp = "";
					m_ctrlList.SetItemText(nIndex, 17, strTemp);
				}
				if (!setTemp.IsFieldNull(&setTemp.m_lPuntiScore1))
				{
					CString strTemp;
					strTemp.Format("%li", setTemp.m_lPuntiScore1);
					m_ctrlList.SetItemText(nIndex, 18, strTemp);
				}
				if (!setTemp.IsFieldNull(&setTemp.m_lPuntiScore2))
				{
					CString strTemp;
					strTemp.Format("%li", setTemp.m_lPuntiScore2);
					m_ctrlList.SetItemText(nIndex, 19, strTemp);
				}
				if (!setTemp.IsFieldNull(&setTemp.m_lPuntiScore3))
				{
					CString strTemp;
					strTemp.Format("%li", setTemp.m_lPuntiScore3);
					m_ctrlList.SetItemText(nIndex, 20, strTemp);
				}
				if (!setTemp.IsFieldNull(&setTemp.m_lPuntiScore4))
				{
					CString strTemp;
					strTemp.Format("%li", setTemp.m_lPuntiScore4);
					m_ctrlList.SetItemText(nIndex, 21, strTemp);
				}
			}

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMonitoraggioOrizDynForm::OnFormLoad");
	}

	for(int i = 0; i < m_ctrlList.GetHeaderCtrl()->GetItemCount(); i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	// UpdateData(FALSE);
}

void CMonitoraggioOrizDynForm::OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_ctrlBtnEdit.EnableWindow((m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bEsamiBusy) && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	m_ctrlBtnDel.EnableWindow((m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bEsamiBusy) && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));

	

	if (pResult != NULL)
		*pResult = 0;
}

LRESULT CMonitoraggioOrizDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	RiempiLista();

	return 1;
}

LRESULT CMonitoraggioOrizDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	SendDlgItemMessage(IDC_EDIT_NOTE, EM_SETREADONLY, wParam, lParam);

	if (((theApp.m_nProgramMode & ADD_RECORD_ESAMI) || (theApp.m_nProgramMode & MODIFY_RECORD_ESAMI)) && !m_pEsamiView->m_pEsamiSet->m_bLocked && !m_pEsamiView->m_pEsamiSet->m_bSuperLocked)
	{
		GetDlgItem(IDC_COMBO_INFERMIERE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_INFERMIERE)->ShowWindow(SW_HIDE);
	}
	else 
	{
		GetDlgItem(IDC_COMBO_INFERMIERE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_INFERMIERE)->ShowWindow(SW_SHOW);
		SendDlgItemMessage(IDC_EDIT_INFERMIERE, EM_SETREADONLY, wParam, lParam);
	}

	GetDlgItem(IDC_BTN_ADD)->EnableWindow(!m_pEsamiView->m_bMonitoraggioAttivo);
	GetDlgItem(IDC_BTN_EDIT)->EnableWindow(!m_pEsamiView->m_bMonitoraggioAttivo);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(!m_pEsamiView->m_bMonitoraggioAttivo);

	return 1;
}

LRESULT CMonitoraggioOrizDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlInfermiereTxt.m_strRicerca = "";
	m_ctrlInfermiereTxt.m_strRicercaView = "";

	return 1;
}

LRESULT CMonitoraggioOrizDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CMonitoraggioOrizDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	ComponiRicercaEx(pStrWhere, m_ctrlInfermiereTxt.m_strRicerca, "EEsami.InfermiereMonitoraggio", TRUE, TRUE);

	return 1;
}

void CMonitoraggioOrizDynForm::AggiungiRiga()
{
	OnBnClickedBtnAdd();
}

int CMonitoraggioOrizDynForm::GetListItemCount()
{
	return m_ctrlList.GetItemCount();
}

CString CMonitoraggioOrizDynForm::GetListItemText(int nItem, int nSubItem)
{
	return m_ctrlList.GetItemText(nItem, nSubItem);
}

CString CMonitoraggioOrizDynForm::GetFarmaciList(int nMonitoraggio)
{
	CString sReturn = "";

	return sReturn;
}

CString CMonitoraggioOrizDynForm::GetTotaleFarmaciList()
{
	CString sReturn = "";

	return sReturn;
}

long CMonitoraggioOrizDynForm::GetListNumCol()
{
	return 0;
}

long CMonitoraggioOrizDynForm::GetListNumRig()
{
	return 0;
}

LRESULT CMonitoraggioOrizDynForm::OnMonitoraggioListEv(WPARAM wParam, LPARAM lParam)
{
	if (m_pEsamiView->m_bMonitoraggioAttivo)
	{
		GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_EDIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
		return 0;
	}

	//Se è stato cliccato il flag per visualizzare il pdf, apro il documento
	if ((int)lParam == 1)
	{
		int idMonitoraggio = m_ctrlList.GetItemData(wParam);	

		if (idMonitoraggio > 0)
		{			
			CMonitoraggioSet tempSet;
			CString filter;
			filter.Format("id=%li", idMonitoraggio);
			tempSet.SetOpenFilter(filter);

			if (tempSet.OpenRecordset("CMonitoraggioVertDynForm::OnMonitoraggioListEv"))
			{
				if (!tempSet.IsEOF())
				{
					CPdfManager pdfManager;					
					CString pdfPath = pdfManager.GetPdfPath(tempSet.m_lIdPdf);

					CArchivioStampeDlg::tagPDFVIEW pdfView;
					pdfView.lID = tempSet.m_lIdPdf;
					strcpy_s(pdfView.szNote, "");
					strcpy_s(pdfView.szData, "");
					strcpy_s(pdfView.szFile, pdfPath);
					pdfView.bFitToPage = FALSE;
					pdfView.bFirmato = FALSE;
					pdfView.bSospeso = FALSE;
					pdfView.bAnnullato = FALSE;
					pdfView.bCriptato = FALSE;
					strcpy_s(pdfView.szDisco, "H");
					strcpy_s(pdfView.szPercorsoFileRemoto, "");

					CList<CArchivioStampeDlg::tagPDFVIEW> listViewPdf;
					listViewPdf.AddTail(pdfView);
	
					CString sTitle = "";

					CArchivioStampeDlg dlg(this, m_pEsamiView, &listViewPdf, sTitle, FALSE);
					dlg.DoModal();
				}

				tempSet.CloseRecordset("CMonitoraggioVertDynForm::OnMonitoraggioListEv");
			}
		}

		m_ctrlList.SetSubItemData(wParam, lParam, 0);
	}

	return 1;
}

void CMonitoraggioOrizDynForm::Reload()
{
	OnFormLoad(-1, -1);
}

void CMonitoraggioOrizDynForm::OnBnClickedBtnRefresh()
{
	RiempiLista();
}
