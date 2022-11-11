#include "stdafx.h"
#include "Endox.h"
#include "MonitoraggioVertDynForm.h"

#include "EsamiView.h"
#include "EsamiSet.h"
#include "MonitoraggioVertDlg.h"
#include "MonitoraggioSet.h"
#include "MonitoraggioFarmaciDosiSet.h"
#include "MonitoraggioUtils.h"
#include "FarmaciMonitoraggioSet.h"
#include "DosiMonitoraggioSet.h"
#include "InfermieriSet.h"
#include "UtentiSet.h"
#include "VitalSignMisurazioniDettaglioDlg.h"
#include "VitalSignMisurazioniHeaderSet.h"

#include "DLL_Imaging\h\AmLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMonitoraggioVertDynForm::CMonitoraggioVertDynForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CMonitoraggioBaseDynForm(CMonitoraggioVertDynForm::IDD, pParent, pEsamiView), m_ctrlListVitalSign(FALSE, TRUE, FALSE)
{
}

CMonitoraggioVertDynForm::~CMonitoraggioVertDynForm(void)
{
}

BEGIN_MESSAGE_MAP(CMonitoraggioVertDynForm, CMonitoraggioBaseDynForm)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_BTN_ADD, OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)

	ON_MESSAGE(WM_MONITORAGGIOLISTEV, OnMonitoraggioListEv)
	ON_MESSAGE(WM_MONITORAGGIO_VITALSIGN_LISTEV, OnMonitoraggio_VitalSign_ListEv)

	ON_BN_CLICKED(IDC_BTN_REFRESH, &CMonitoraggioVertDynForm::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_COPIA, &CMonitoraggioVertDynForm::OnBnClickedBtnCopia)
END_MESSAGE_MAP()

void CMonitoraggioVertDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_monitoraggio_vert] == NULL)
	{
		pEsamiView->m_pDynForm[sub_monitoraggio_vert] = new CMonitoraggioVertDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_monitoraggio_vert] != NULL)
		{
			pEsamiView->m_pDynForm[sub_monitoraggio_vert]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_monitoraggio_vert]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_monitoraggio_vert]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_monitoraggio_vert]->CreateChildForm(CMonitoraggioVertDynForm::IDD, pParent, rectFrame);
		}
	}
}

void CMonitoraggioVertDynForm::DoDataExchange(CDataExchange* pDX)
{
	CMonitoraggioBaseDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_LIST_VITALISIGN, m_ctrlListVitalSign);
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

		if (m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco) || (theApp.m_nProgramMode & FILTER_RECORD_ESAMI))
			bEnable = FALSE;

		m_ctrlBtnAdd.EnableWindow(bEnable);
		m_ctrlBtnEdit.EnableWindow(bEnable && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
		m_ctrlBtnDel.EnableWindow(bEnable && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));

		if (m_pEsamiView->m_bMonitoraggioAttivo)
		{
			GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_EDIT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
		}		
	}	
}

HBRUSH CMonitoraggioVertDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CMonitoraggioBaseDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_LABEL1:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}
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

BOOL CMonitoraggioVertDynForm::OnInitDialog()
{
	CMonitoraggioBaseDynForm::OnInitDialog();

	GetDlgItem(IDC_STATIC_LABEL1)->SetFont(&theApp.m_fontBold);

	AddAnchor(IDC_STATIC_LABEL1, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_BTN_COPIA, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 75));
	AddAnchor(IDC_LIST_VITALISIGN, CSize(0, 75), CSize(100, 75));
	AddAnchor(IDC_STATIC_LABEL3, CSize(0, 75), CSize(0, 75));
	AddAnchor(IDC_COMBO_INFERMIERE, CSize(10, 75), CSize(30, 75));
	AddAnchor(IDC_EDIT_INFERMIERE, CSize(10, 75), CSize(30, 75));
	AddAnchor(IDC_BTN_REFRESH, CSize(100, 75), CSize(100, 75));
	AddAnchor(IDC_BTN_ADD, CSize(100, 75), CSize(100, 75));
	AddAnchor(IDC_BTN_EDIT, CSize(100, 75), CSize(100, 75));
	AddAnchor(IDC_BTN_DEL, CSize(100, 75), CSize(100, 75));	
	AddAnchor(IDC_STATIC_LABEL2, CSize(0, 75), CSize(100, 75));
	AddAnchor(IDC_EDIT_NOTE, CSize(0, 75), CSize(100, 100));

	m_ctrlInfermiereTxt.SetParam(this, m_pEsamiView->m_pEsamiSet);

	m_ctrlList.SetNotificationChangeValueMessage(WM_MONITORAGGIOLISTEV);
	m_ctrlListVitalSign.SetNotificationChangeValueMessage(WM_MONITORAGGIO_VITALSIGN_LISTEV);

	GetDlgItem(IDC_BTN_COPIA)->ShowWindow(theApp.m_bMonitoraggioPermettiCopia);

	theApp.LocalizeDialog(this, CMonitoraggioVertDynForm::IDD, "MonitoraggioVertDynForm");

	return TRUE;
}

void CMonitoraggioVertDynForm::OnSize(UINT nType, int cx, int cy)
{
	CMonitoraggioBaseDynForm::OnSize(nType, cx, cy);

	if (!theApp.m_bVitalSignIntegrazioneAttiva && m_ctrlListVitalSign.GetSafeHwnd() && m_ctrlList.GetSafeHwnd())
	{
		CRect vitalSignRect;
		m_ctrlListVitalSign.GetWindowRect(&vitalSignRect);

		CRect monitoraggioRect;
		m_ctrlList.GetWindowRect(&monitoraggioRect);
		ScreenToClient(&monitoraggioRect);
		m_ctrlList.SetWindowPos(NULL, monitoraggioRect.left, monitoraggioRect.top, monitoraggioRect.Width(), monitoraggioRect.Height() + vitalSignRect.Height(), 0);

		m_ctrlListVitalSign.ShowWindow(SW_HIDE);
	}
}

long CMonitoraggioVertDynForm::GetContenuto()
{
	return sub_monitoraggio_vert;
}

BOOL CMonitoraggioVertDynForm::CampoObbligatorioValido()
{
	return GetListNumCol() > 0 && m_pEsamiView->m_pEsamiSet->m_lInfermiereMonitoraggio > 0;
}

void CMonitoraggioVertDynForm::OnBnClickedBtnAdd()
{
	m_ctrlBtnAdd.SetCheck(BST_UNCHECKED);

	CMonitoraggioVertDlg dlg(this, m_pEsamiView, -1);
	if (dlg.DoModal() == IDOK)
	{		
		if (theApp.m_bVitalSignIntegrazioneAttiva && dlg.m_lRecord <= 0) //Significa che ho scelto di utilizzare Vital Sign (non ho ancora alcun monitoraggio inserito)
		{
			m_pEsamiView->PostMessage(EPM_THREAD_STARTMONITORAGGIO, MonitoringPhase::pre);
		}
		else
		{
			RiempiLista();
			m_ctrlBtnDel.EnableWindow(FALSE);
			m_ctrlBtnEdit.EnableWindow(FALSE);
		}
	}
}

void CMonitoraggioVertDynForm::OnBnClickedBtnEdit()
{
	m_ctrlBtnEdit.SetCheck(BST_UNCHECKED);

	int idMonitoraggio = 0;
	for(int i = 1; i < m_ctrlList.GetColumnCount(); i++)
	{	
		int checked = m_ctrlList.GetSubItemData(0, i);
		if (checked > 0)
		{
			POSITION pos = m_idMonitoraggioList.GetHeadPosition();
			for(int j=0; j<=i; j++)
			{
				idMonitoraggio = m_idMonitoraggioList.GetNext(pos);
			}
		}

		if (idMonitoraggio > 0)
		{
			CMonitoraggioVertDlg dlg(this, m_pEsamiView, idMonitoraggio);
			if (dlg.DoModal() == IDOK)	
			{
				RiempiLista();
				m_ctrlBtnDel.EnableWindow(FALSE);
				m_ctrlBtnEdit.EnableWindow(FALSE);
			}


			break;
		}
	}	
}

void CMonitoraggioVertDynForm::OnBnClickedBtnDel()
{
	m_ctrlBtnDel.SetCheck(BST_UNCHECKED);

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DELETE_MONIT_ROWS), MB_YESNO) == IDYES)
	{
		CMonitoraggioSet setTemp;

		int idMonitoraggio = 0;
		for(int i = 1; i < m_ctrlList.GetColumnCount(); i++)
		{	
			int checked = m_ctrlList.GetSubItemData(0, i);
			if (checked > 0)
			{
				POSITION pos = m_idMonitoraggioList.GetHeadPosition();
				for(int j=0; j<=i; j++)
				{
					idMonitoraggio = m_idMonitoraggioList.GetNext(pos);
				}
				CString strFilter;
				strFilter.Format("ID=%li", idMonitoraggio);

				setTemp.SetOpenFilter(strFilter);
				if (setTemp.OpenRecordset("CMonitoraggioVertDynForm::OnBnClickedBtnDel"))
				{
					BOOL bDeleted = FALSE;

					if (!setTemp.IsEOF())
						bDeleted = setTemp.DeleteRecordset("CMonitoraggioVertDynForm::OnBnClickedBtnDel");

					setTemp.CloseRecordset("CMonitoraggioVertDynForm::OnBnClickedBtnDel");
				}
			}
		}

		OnFormLoad(NULL, NULL);

		m_ctrlBtnDel.EnableWindow(FALSE);
		m_ctrlBtnEdit.EnableWindow(FALSE);
	}
}

/*
void CMonitoraggioVertDynForm::OnBnClickedBtnRef()
{
	m_ctrlBtnRef.SetCheck(BST_UNCHECKED);

	RiempiLista();
}
*/

int CMonitoraggioVertDynForm::RicercaFarmaco(int lID)
{
	for (int i = 0; i<m_ctrlList.GetItemCount(); i++)
	{
		int iTemp = m_ctrlList.GetItemData(i);
		if (iTemp == lID)
			return i;
	}

	return -1;
}

void CMonitoraggioVertDynForm::RiempiListaVitalSign()
{
	if (theApp.m_bVitalSignIntegrazioneAttiva)
	{
		m_ctrlListVitalSign.SetRedraw(FALSE);

		m_ctrlListVitalSign.DeleteAllItems();
		m_idMisurazioniVitalSignHeaderList.RemoveAll();

		for (int i = m_ctrlListVitalSign.GetHeaderCtrl()->GetItemCount() - 1; i >= 0; i--)
			m_ctrlListVitalSign.DeleteColumn(i);

		CVitalSignMisurazioniHeaderSet vsMisurazioniHeaderSet;
		CString sFilter;
		sFilter.Format("IDESAME=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);
		vsMisurazioniHeaderSet.SetOpenFilter(sFilter);

		if (vsMisurazioniHeaderSet.OpenRecordset("CMonitoraggioVertDynForm::RiempiListaVitalSign"))
		{
			int index = 0;

			m_ctrlListVitalSign.InsertColumn(index++, "", LVCFMT_LEFT, 0);
			m_idMisurazioniVitalSignHeaderList.AddTail(-1);

			m_ctrlListVitalSign.InsertColumn(index++, "");
			m_ctrlListVitalSign.InsertItem(0, "");
			m_ctrlListVitalSign.SetItemText(0, 1, theApp.GetMessageString(IDS_ORE));
			m_ctrlListVitalSign.InsertItem(1, "");
			m_ctrlListVitalSign.SetItemText(1, 1, theApp.GetMessageString(IDS_DETTAGLI));
			m_idMisurazioniVitalSignHeaderList.AddTail(-1);

			m_ctrlListVitalSign.SetSubItemBkColor(-1, 1, RGB(192, 192, 192));

			while (!vsMisurazioniHeaderSet.IsEOF())
			{

				m_idMisurazioniVitalSignHeaderList.AddTail(vsMisurazioniHeaderSet.m_lID);				

				CString sFase = CMonitoraggioUtils::DecodeFase(vsMisurazioniHeaderSet.m_lFase);				

				m_ctrlListVitalSign.InsertColumn(index, sFase, LVCFMT_CENTER);
				m_ctrlListVitalSign.SetItemText(0, index, vsMisurazioniHeaderSet.m_sOra);

				if (vsMisurazioniHeaderSet.m_bTerminato)
					m_ctrlListVitalSign.SetSubItemCheck(1, index);

				vsMisurazioniHeaderSet.MoveNext();

				index++;
			}

			vsMisurazioniHeaderSet.CloseRecordset("CMonitoraggioVertDynForm::RiempiListaVitalSign");
		}

		for (int i = 1; i < m_ctrlListVitalSign.GetHeaderCtrl()->GetItemCount(); i++) //salto la prima colonna che è quella nascosta
			m_ctrlListVitalSign.SetColumnWidth(i, 100);

		m_ctrlListVitalSign.SetRedraw(TRUE);
	}
}

void CMonitoraggioVertDynForm::RiempiLista()
{
	m_ctrlList.SetRedraw(FALSE);

	CMonitoraggioSet setTemp;
	CMonitoraggioFarmaciDosiSet monitoraggioFarmaciDosiSet;
	CFarmaciMonitoraggioSet monitoraggioFarmaciSet;
	
	CString strFilter;
	strFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	setTemp.SetOpenFilter(strFilter);
	setTemp.SetSortRecord("Ora, ID");

	m_ctrlList.DeleteAllItems();
	m_idMonitoraggioList.RemoveAll();

	while(m_ctrlList.GetColumnCount() > 0)
		m_ctrlList.DeleteColumn(0);

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_GRIDLINES);	

	m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_idMonitoraggioList.AddTail(-1);

	m_ctrlList.InsertColumn(1, "", LVCFMT_LEFT , 130);
	m_ctrlList.SetSubItemBkColor(-1, 1, RGB(192,192,192));
	m_idMonitoraggioList.AddTail(-1);

	// Inserisco le voci fisse //
	int index = 0;
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_SELEZIONA));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetSubItemBkColor(index, 1, theApp.m_color[m_lColore]);
	m_ctrlList.SetItemText(index++, 1, "");	
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_FASE));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_ORE));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_INFERMIERE));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_FC));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_FC_POLSO));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_PA));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_SAT));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_O2));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_ETCO2));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_INTUBAZIONE));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_VENTILAZIONE));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_VT));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_FR));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_DOLORE_SCALA));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_DOLORE));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_DOLORE_LOCALIZZAZIONE));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_DOLORE_CARATTERISTICHE));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_DOLORE_FREQUENZA));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_DOLORE_DURATA));
	m_ctrlList.InsertItem(index, "");
	m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_RAMSAY));

	if (theApp.m_bMostraScoreMonitoraggio)
	{
		m_ctrlList.InsertItem(index, "");
		m_ctrlList.SetItemText(index++, 1, theApp.GetMessageString(IDS_SCORE));
	}
	
	if (setTemp.OpenRecordset("CMonitoraggioVertDynForm::RiempiLista"))
	{
		while (!setTemp.IsEOF())
		{
			int nNewColumn = m_ctrlList.GetColumnCount();

			int rowIndex = 0;

			m_ctrlList.InsertColumn(nNewColumn, "", LVCFMT_LEFT, 80);
			m_ctrlList.SetSubItemCheck(rowIndex++, nNewColumn);
			m_idMonitoraggioList.AddTail(setTemp.m_lID);
			m_ctrlList.SetItemText(rowIndex, nNewColumn, "");
			m_ctrlList.SetSubItemBkColor(rowIndex++, nNewColumn, theApp.m_color[m_lColore]);

			m_ctrlList.SetItemText(rowIndex++, nNewColumn, CMonitoraggioUtils::DecodeFase(setTemp.m_lQuando));

			//ORA
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, setTemp.m_strOra);

			//INFERMIERE
			CInfermieriSet infermieriSet;
			CString inf, filter;
			filter.Format("contatore = %li", setTemp.m_lIdInfermiere);
			infermieriSet.SetOpenFilter(filter);
			if (infermieriSet.OpenRecordset("CMonitoraggioVertDynForm::RiempiLista"))
			{
				if (!infermieriSet.IsEOF())
					inf.Format("%s %s", infermieriSet.m_sCognome, infermieriSet.m_sNome);

				infermieriSet.CloseRecordset("CMonitoraggioVertDynForm::RiempiLista");
			}

			m_ctrlList.SetItemText(rowIndex++, nNewColumn, inf);

			//FC
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, setTemp.m_strFC);

			//FC POLSO
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, CMonitoraggioUtils::DecodePolso(setTemp.m_lFCPolso));

			//PA
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, setTemp.m_strPA);
			//SAT
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, setTemp.m_strSat);
			//O2
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, setTemp.m_strO2);
			//ETCO2
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, setTemp.m_strETCO2);
			//INTUBAZIONE
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, CMonitoraggioUtils::DecodeIntubazione(setTemp.m_lIntubazione));
			//VENTILAZIONE
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, CMonitoraggioUtils::DecodeVentilazione(setTemp.m_lVentilazione));
			//VT
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, setTemp.m_strVentilazioneVt);
			//FR
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, setTemp.m_strVentilazioneFr);
			//DOLORE SCALA
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, CMonitoraggioUtils::DecodeDoloreScala(setTemp.m_lDoloreScala));
			//DOLORE VALORE
			if (setTemp.m_lDoloreScala == 1)
				m_ctrlList.SetItemText(rowIndex++, nNewColumn, CMonitoraggioUtils::DecodeDoloreVAS(setTemp.m_lDoloreVAS));
			else if (setTemp.m_lDoloreScala == 2)
				m_ctrlList.SetItemText(rowIndex++, nNewColumn, CMonitoraggioUtils::DecodeDoloreNRS(setTemp.m_lDoloreNRS));
			else if (setTemp.m_lDoloreScala == 3)
				m_ctrlList.SetItemText(rowIndex++, nNewColumn, CMonitoraggioUtils::DecodeDoloreWB(setTemp.m_lDoloreWB));
			else if (setTemp.m_lDoloreScala == 4)
			{		
				CString temp;
				temp.Format("%li", setTemp.m_lDoloreCCPO1 + setTemp.m_lDoloreCCPO2 + setTemp.m_lDoloreCCPO3 + setTemp.m_lDoloreCCPO4 + setTemp.m_lDoloreCCPO5);
				m_ctrlList.SetItemText(rowIndex++, nNewColumn, temp);
			}
			//DOLORE LOCALIZZAZIONE
			CString doloreLocalizzazione = CMonitoraggioUtils::DecodeDoloreLocalizzazione(setTemp.m_lDoloreLocalizzazione);
			if (!setTemp.m_sDoloreLocalizzazioneDettaglio.IsEmpty())
				doloreLocalizzazione.Append(" " + setTemp.m_sDoloreLocalizzazioneDettaglio);
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, doloreLocalizzazione);
			//DOLORE CARATTERISTICHE
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, CMonitoraggioUtils::DecodeDoloreCaratteristiche(setTemp.m_lDoloreCaratteristiche));
			//DOLORE FREQUENZA
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, CMonitoraggioUtils::DecodeDoloreFrequenza(setTemp.m_lDoloreFrequenza));
			//DOLORE DURATA
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, CMonitoraggioUtils::DecodeDoloreDurata(setTemp.m_lDoloreDurata));
			//RAMSAY
			m_ctrlList.SetItemText(rowIndex++, nNewColumn, CMonitoraggioUtils::DecodeRamsay(setTemp.m_lRamsay));

			if (theApp.m_bMostraScoreMonitoraggio)
			{
				if (theApp.m_bUsaScoreDiGlasgow)
				{
					if (!setTemp.IsFieldNull(&setTemp.m_lTotalScoreGlasgow))
					{
						CString strTemp;
						if (setTemp.m_lTotalScoreGlasgow > 0)
							strTemp.Format("%li", setTemp.m_lTotalScoreGlasgow);
						else
							strTemp = "";
						m_ctrlList.SetItemText(rowIndex++, nNewColumn, strTemp);
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
						m_ctrlList.SetItemText(rowIndex++, nNewColumn, strTemp);
					}
				}
			}
			
			filter.Format("IDMonitoraggio = %li", setTemp.m_lID);
			monitoraggioFarmaciDosiSet.SetOpenFilter(filter);
			if (monitoraggioFarmaciDosiSet.OpenRecordset("CMonitoraggioVertDynForm::RiempiLista"))
			{
				while(!monitoraggioFarmaciDosiSet.IsEOF())
				{
					// Cerca se il farmaco è già stato inserito tramite ricerca id, se è così aggiorna la riga altrimenti aggiunge il farmaco
					int rigaFarmaco = RicercaFarmaco(monitoraggioFarmaciDosiSet.m_lIDFarmaco);
					if (rigaFarmaco == -1)
					{
						int riga = m_ctrlList.GetItemCount();
						CString filterFar, filterDosi;
						filterFar.Format("Id = %li", monitoraggioFarmaciDosiSet.m_lIDFarmaco);
						monitoraggioFarmaciSet.SetOpenFilter(filterFar);
						if (monitoraggioFarmaciSet.OpenRecordset("CMonitoraggioVertDynForm::RiempiLista"))
						{
							m_ctrlList.InsertItem(riga, "");
							m_ctrlList.SetItemText(riga, 1, monitoraggioFarmaciSet.m_sNome);
							m_ctrlList.SetItemData(riga, monitoraggioFarmaciDosiSet.m_lIDFarmaco);
							m_ctrlList.SetItemText(riga, nNewColumn, monitoraggioFarmaciDosiSet.m_sDose);
							monitoraggioFarmaciSet.CloseRecordset("CMonitoraggioVertDynForm::RiempiLista");
						}
					}
					else
					{
						m_ctrlList.SetItemText(rigaFarmaco, nNewColumn, monitoraggioFarmaciDosiSet.m_sDose);	
					}
					monitoraggioFarmaciDosiSet.MoveNext();
				}
				monitoraggioFarmaciDosiSet.CloseRecordset("CMonitoraggioVertDynForm::RiempiLista");
			}

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMonitoraggioVertDynForm::RiempiLista");
	}

	m_ctrlList.InsertColumn(m_ctrlList.GetColumnCount(), "", LVCFMT_LEFT, 0);
	for(int i = 1; i < m_ctrlList.GetColumnCount() - 1; i++) //tralascio la prima colonna che è quella nascosta
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList.SetRedraw(TRUE);
}

LRESULT CMonitoraggioVertDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	RiempiLista();
	RiempiListaVitalSign();

	return 1;
}

LRESULT CMonitoraggioVertDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{	
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	BOOL bReadOnly = (BOOL)wParam;

	SendDlgItemMessage(IDC_EDIT_NOTE, EM_SETREADONLY, bReadOnly, lParam);

	if (((theApp.m_nProgramMode & ADD_RECORD_ESAMI) || (theApp.m_nProgramMode & MODIFY_RECORD_ESAMI)) && !m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
	{
		GetDlgItem(IDC_COMBO_INFERMIERE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_INFERMIERE)->ShowWindow(SW_HIDE);
	}
	else 
	{
		GetDlgItem(IDC_COMBO_INFERMIERE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_INFERMIERE)->ShowWindow(SW_SHOW);
		SendDlgItemMessage(IDC_EDIT_INFERMIERE, EM_SETREADONLY, bReadOnly, lParam);
	}

	UpdateData(FALSE);

	return 1;
}

LRESULT CMonitoraggioVertDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlInfermiereTxt.m_strRicerca = "";
	m_ctrlInfermiereTxt.m_strRicercaView = "";

	return 1;
}

LRESULT CMonitoraggioVertDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CMonitoraggioVertDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	ComponiRicercaEx(pStrWhere, m_ctrlInfermiereTxt.m_strRicerca, "EEsami.InfermiereMonitoraggio", TRUE, TRUE);

	return 1;
}

void CMonitoraggioVertDynForm::AggiungiRiga()
{
	OnBnClickedBtnAdd();
}

int CMonitoraggioVertDynForm::GetListItemCount()
{
	//return m_ctrlList.GetItemCount();
	return m_ctrlList.GetHeaderCtrl()->GetItemCount()-2;
}

CString CMonitoraggioVertDynForm::GetListItemText(int nItem, int nSubItem)
{
	return m_ctrlList.GetItemText(nItem+2, nSubItem+1);
}

CString CMonitoraggioVertDynForm::GetFarmaciList(int nMonitoraggio)
{
	CString sReturn = "";

	int righeTotali = m_ctrlList.GetItemCount();
	int primoFarmaco = 11;

	for(int i=primoFarmaco; i<righeTotali; i++)
	{
		CString farmaco = m_ctrlList.GetItemText(i, 1);
		CString dose = m_ctrlList.GetItemText(i, nMonitoraggio+1);

		if (dose != "")
		{
			if (sReturn == "")
				sReturn = farmaco + " " + dose;
			else
				sReturn += ", " + farmaco + " " + dose;
		}
	}

	return sReturn;
}

CString CMonitoraggioVertDynForm::GetTotaleFarmaciList()
{
	CString sReturn = "";

	int righeTotali = m_ctrlList.GetItemCount();
	int primoFarmaco = 11;

	for (int i = primoFarmaco; i<righeTotali; i++)
	{
		CString farmaco = m_ctrlList.GetItemText(i, 1);
		int totaleFarmaco = 0;

		for (int h = 2; h < righeTotali; h++)
		{
			CString dose = m_ctrlList.GetItemText(i, h);

			int iDose = atoi(dose);
			if (iDose > 0)
				totaleFarmaco += iDose;

		}

		if (totaleFarmaco > 0)
		{
			if (sReturn == "")
				sReturn.Format("%s %li", farmaco, totaleFarmaco);
			else
				sReturn.AppendFormat(", %s %li", farmaco, totaleFarmaco);
		}
	}

	return sReturn;
}

long CMonitoraggioVertDynForm::GetListNumCol()
{
	return m_ctrlList.GetHeaderCtrl()->GetItemCount() - 2;
}

long CMonitoraggioVertDynForm::GetListNumRig()
{
	return m_ctrlList.GetItemCount() - 2; // scarto le prime due righe di "intestazione" //
}


/*void CMonitoraggioVertDynForm::OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int numCheck = 0;

	for(int a = 1; a < m_ctrlList.GetColumnCount(); a++)
	{
		int check = m_ctrlList.GetSubItemData(0, a);
		if (check > 0)
			numCheck++;
	}

	if (numCheck > 0)
	{
		if (numCheck == 1)
		{
			m_ctrlBtnEdit.EnableWindow((m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bEsamiBusy) && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
			m_ctrlBtnDel.EnableWindow((m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bEsamiBusy) && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
		}
		else
		{
			m_ctrlBtnEdit.EnableWindow(FALSE);
			m_ctrlBtnDel.EnableWindow((m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bEsamiBusy) && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
		}
	}
	else
	{
		m_ctrlBtnDel.EnableWindow(FALSE);
		m_ctrlBtnEdit.EnableWindow(FALSE);
	}

	if (pResult != NULL)
		*pResult = 0;
}*/

LRESULT CMonitoraggioVertDynForm::OnMonitoraggioListEv(WPARAM wParam, LPARAM lParam)
{
	if (m_pEsamiView->m_bMonitoraggioAttivo || (theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
	{
		GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_EDIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
		return 0;
	}

	//Se è cambiata una delle check di selezione, conto quante check sono selezionate per decidere quali bottoni attivare
	if ((int)wParam == 0)
	{
		int numCheck = 0;

		for(int a = 1; a < m_ctrlList.GetColumnCount(); a++)
		{
			int check = m_ctrlList.GetSubItemData(0, a);
			if (check > 0)
				numCheck++;
		}

		if (numCheck > 0)
		{
			if (numCheck == 1)
			{
				m_ctrlBtnEdit.EnableWindow((m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bEsamiBusy) && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
				m_ctrlBtnDel.EnableWindow((m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bEsamiBusy) && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
			}
			else
			{
				m_ctrlBtnEdit.EnableWindow(FALSE);
				m_ctrlBtnDel.EnableWindow((m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bEsamiBusy) && (!m_pEsamiView->m_bPazientiBusy) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
			}
		}
		else
		{
			m_ctrlBtnDel.EnableWindow(FALSE);
			m_ctrlBtnEdit.EnableWindow(FALSE);
		}
	}

	//Se è stato cliccato il flag per visualizzare il pdf, apro il documento
	/*if ((int)wParam == 11)
	{
		int idMonitoraggio = 0;
		POSITION pos = m_idMonitoraggioList.GetHeadPosition();
		
		for(int j=0; j<=lParam; j++)
			idMonitoraggio = m_idMonitoraggioList.GetNext(pos);	

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
	}*/

	return 1;
}

LRESULT CMonitoraggioVertDynForm::OnMonitoraggio_VitalSign_ListEv(WPARAM wParam, LPARAM lParam)
{
	//Se è stato cliccato il flag per visualizzare il dettaglio, apro la dialog
	if ((int)wParam == 1)
	{		
		m_ctrlListVitalSign.SetSubItemData(wParam, lParam, 0);

		int idRecord = 0;
		POSITION pos = m_idMisurazioniVitalSignHeaderList.GetHeadPosition();

		for (int j = 0; j <= lParam; j++)
			idRecord = m_idMisurazioniVitalSignHeaderList.GetNext(pos);

		CVitalSignMisurazioniDettaglioDlg vsDetailDlg(this, m_pEsamiView, idRecord);
		vsDetailDlg.DoModal();

		RiempiLista();
	}

	return 1;
}

void CMonitoraggioVertDynForm::Reload()
{
	OnFormLoad(-1, -1);
}

void CMonitoraggioVertDynForm::OnBnClickedBtnRefresh()
{
	RiempiLista();	
	RiempiListaVitalSign();
}




void CMonitoraggioVertDynForm::OnBnClickedBtnCopia()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MONITORAGGIO_COPIA), MB_YESNO) == IDYES)
	{
		CString sFilter;
		sFilter.Format("PAZIENTE = %li AND DATA <= %li AND CONTATORE <> %li", m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lData, m_pEsamiView->m_pEsamiSet->m_lContatore);
		CEsamiSet esamiSet;
		esamiSet.SetOpenFilter(sFilter);
		esamiSet.SetSortRecord("CONTATORE DESC");

		if (esamiSet.OpenRecordset("CMonitoraggioVertDynForm::OnBnClickedBtnCopia"))
		{
			if (!esamiSet.IsEOF())
			{
				sFilter.Format("IDESAME = %li", esamiSet.m_lContatore);
				CMonitoraggioSet monitoraggioSet;				
				monitoraggioSet.SetOpenFilter(sFilter);
				monitoraggioSet.SetSortRecord("ID");

				if (monitoraggioSet.OpenRecordset("CMonitoraggioVertDynForm::OnBnClickedBtnCopia"))
				{
					CMonitoraggioSet monitoraggioSet2; // Apro il recordset per l'inserimento prima del while in modo da non aprirlo e chiuderlo 100 volte
					if (monitoraggioSet2.OpenRecordset("CMonitoraggioVertDynForm::OnBnClickedBtnCopia"))
					{
						while (!monitoraggioSet.IsEOF())
						{
							if (monitoraggioSet2.AddNewRecordset("CMonitoraggioVertDynForm::OnBnClickedBtnCopia"))
							{
								monitoraggioSet2.m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
								monitoraggioSet2.CopyFrom(&monitoraggioSet);

								monitoraggioSet2.UpdateRecordset("CMonitoraggioVertDynForm::OnBnClickedBtnCopia");
							}

							monitoraggioSet.MoveNext();
						}

						monitoraggioSet2.CloseRecordset("CMonitoraggioVertDynForm::OnBnClickedBtnCopia");
					}

					monitoraggioSet.CloseRecordset("CMonitoraggioVertDynForm::OnBnClickedBtnCopia");
				}

			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MONITORAGGIO_COPIA_NOPRECEDENTI));
			}

			esamiSet.CloseRecordset("CMonitoraggioVertDynForm::OnBnClickedBtnCopia");
		}

		RiempiLista();
		RiempiListaVitalSign();
	}
}
