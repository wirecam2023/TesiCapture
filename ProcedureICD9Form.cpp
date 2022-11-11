#include "stdafx.h"
#include "Endox.h"
#include "ProcedureICD9Form.h"

#include "EsamiView.h"
#include "Common.h"
#include "EsamiSet.h"
#include "GruppiProcedureICD9UseDlg.h"
#include "GruppiProcedureICD9ProcedureICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CProcedureICD9Form::CProcedureICD9Form(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CProcedureICD9Form::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 3;

	m_nSearchMode = 0;
}

CProcedureICD9Form::~CProcedureICD9Form()
{
}

BEGIN_MESSAGE_MAP(CProcedureICD9Form, CSubForm)
	ON_WM_CTLCOLOR()

	ON_CBN_EDITCHANGE	(IDC_PROCEDURA_1,		OnChangeProcedura1)
	ON_CBN_SELCHANGE	(IDC_PROCEDURA_1,		OnChangeProcedura1)
	ON_CBN_EDITCHANGE	(IDC_PROCEDURA_2,		OnChangeProcedura2)
	ON_CBN_SELCHANGE	(IDC_PROCEDURA_2,		OnChangeProcedura2)
	ON_CBN_EDITCHANGE	(IDC_PROCEDURA_3,		OnChangeProcedura3)
	ON_CBN_SELCHANGE	(IDC_PROCEDURA_3,		OnChangeProcedura3)

	ON_BN_CLICKED(IDC_BTN_GRUPPI, OnBnClickedBtnGruppi)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBnClickedBtnReset)
END_MESSAGE_MAP()

void CProcedureICD9Form::DoDataExchange(CDataExchange* pDX)
{
	static UINT nID_Numero [3] = { IDC_NUM_1, IDC_NUM_2, IDC_NUM_3 };
	static UINT nID_Procedure[3] = { IDC_PROCEDURA_1, IDC_PROCEDURA_2, IDC_PROCEDURA_3 };

	CSubForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SURE_00, m_ctrlStatic);

	for(int i = 0; i < m_nIndexPage; i++)
		DDX_Control(pDX, nID_Procedure[i], m_ctrlProcedure[i]);

	if (m_pEsamiView->m_pEsamiSet->IsOpen())
		for(int i = 0; i < m_nIndexPage; i++)
			DDX_ProcedureICD9(pDX, nID_Procedure[i], m_ctrLine[m_nIndexLine+i].m_Set.m_lIDProcedura, m_pEsamiView->m_pEsamiSet->m_lProvenienza);

	if (!pDX->m_bSaveAndValidate)
		for(int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine+i+1);

	DDX_Control(pDX, IDC_BTN_GRUPPI, m_ctrlButtonGruppi);
	DDX_Control(pDX, IDC_BTN_RESET, m_ctrlButtonReset);

	DDX_Radio(pDX, IDC_RADIO_AND, m_nSearchMode);
}

void CProcedureICD9Form::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_procedureicd9] == NULL)
	{
		pEsamiView->m_pDynForm[sub_procedureicd9] = new CProcedureICD9Form(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_procedureicd9] != NULL)
		{
			pEsamiView->m_pDynForm[sub_procedureicd9]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_procedureicd9]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_procedureicd9]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_procedureicd9]->CreateChildForm(CProcedureICD9Form::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CProcedureICD9Form::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_SURE_00:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_NUM_1:
		case IDC_NUM_2:
		case IDC_NUM_3:
		case IDC_PROCEDURA_1:
		case IDC_PROCEDURA_2:
		case IDC_PROCEDURA_3:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CProcedureICD9Form::OnInitDialog() 
{
	CSubForm::OnInitDialog();
	
	AddAnchor(IDC_SURE_00, CSize(0, 35), CSize(40, 35));
	AddAnchor(IDC_SURE_01, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_RADIO_AND, CSize(40, 35), CSize(45, 35));
	AddAnchor(IDC_RADIO_OR, CSize(45, 35), CSize(50, 35));
	AddAnchor(IDC_BTN_GRUPPI, CSize(50, 35), CSize(75, 35));
	AddAnchor(IDC_BTN_RESET, CSize(75, 35), CSize(100, 35));
	AddAnchor(IDC_SCROLL, CSize(100, 45), CSize(100, 65));
	AddAnchor(IDC_NUM_1, CSize(0, 45), CSize(0, 45));
	AddAnchor(IDC_NUM_2, CSize(0, 55), CSize(0, 55));
	AddAnchor(IDC_NUM_3, CSize(0, 65), CSize(0, 65));
	AddAnchor(IDC_PROCEDURA_1, CSize(0, 45), CSize(100, 45));
	AddAnchor(IDC_PROCEDURA_2, CSize(0, 55), CSize(100, 55));
	AddAnchor(IDC_PROCEDURA_3, CSize(0, 65), CSize(100, 65));

	GetDlgItem(IDC_SURE_00)->SetFont(&theApp.m_fontBold, TRUE);

	theApp.LocalizeDialog(this, CProcedureICD9Form::IDD, "ProcedureICD9Form");
	return TRUE;
}

void CProcedureICD9Form::ModificaForm()
{
	for(int i = 0; i < m_nIndexPage; i++)
		m_ctrlProcedure[i].SetParam(m_pEsamiView, &m_ctrLine[m_nIndexLine+i].m_Set.m_lIDProcedura); // m_pProcedureICD9Set);
}

LRESULT CProcedureICD9Form::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CProcedureICD9Form::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CProcedureEsamiSet setProcedureEsami;
		setProcedureEsami.SetOpenFilter(sFilter);
		if (setProcedureEsami.OpenRecordset("CProcedureICD9Form::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setProcedureEsami.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setProcedureEsami, nCounter, FALSE);

				nCounter++;
				setProcedureEsami.MoveNext();
			}

			setProcedureEsami.CloseRecordset("CProcedureICD9Form::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CProcedureICD9Form::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	UINT pControlID2[] = {
		IDC_PROCEDURA_1,
		IDC_PROCEDURA_2,
		IDC_PROCEDURA_3,
		IDC_BTN_GRUPPI,
		IDC_BTN_RESET
	};

	UINT pControlID3[] = {
		IDC_RADIO_AND,
		IDC_RADIO_OR
	};

	for(i = 0; i < (sizeof(pControlID2) / sizeof(UINT)); i++)
		GetDlgItem(pControlID2[i])->EnableWindow(!(BOOL)wParam);

	for(i = 0; i < (sizeof(pControlID3) / sizeof(UINT)); i++)
		GetDlgItem(pControlID3[i])->ShowWindow((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) != 0 ? SW_SHOW : SW_HIDE);

	GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);

	return 1;
}

LRESULT CProcedureICD9Form::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_lID = 0;
	}

	return 1;
}

LRESULT CProcedureICD9Form::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CProcedureEsamiSet setProcedureEsami;
	setProcedureEsami.SetOpenFilter("ID=0");
	if (setProcedureEsami.OpenRecordset("CProcedureICD9Form::OnFormSave"))
	{
		SaveForm(FALSE, &m_pEsamiView->m_pEsamiSet->m_lContatore, &setProcedureEsami, &setProcedureEsami.m_lID, &setProcedureEsami.m_lIDEsame);
		setProcedureEsami.CloseRecordset("CProcedureICD9Form::OnFormSave");
	}

	return 1;
}

LRESULT CProcedureICD9Form::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	// cerco se è stata valorizzata almeno una prestazione //
	BOOL bProceed = FALSE;
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		if ((m_ctrLine[i].m_Set.m_lIDProcedura > 0) && (m_ctrLine[i].m_Set.m_lIDProcedura < 1246576928))
		{
			bProceed = TRUE;
			break;
		}
	}

	// se è stata trovata almeno una prestazione compongo il filtro //
	if (bProceed)
	{
		CString strTempWhere = "";

		for(int i = 0; i < MAX_OBJ_X_FORM; i++)
			if ((m_ctrLine[i].m_Set.m_lIDProcedura > 0) && (m_ctrLine[i].m_Set.m_lIDProcedura < 1246576928))
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "ProcedureEsami", i, "IDEsame", "IDProcedura", m_ctrLine[i].m_Set.m_lIDProcedura, m_nSearchMode%2, MODE_UGUALE);

		strTempWhere.Trim();
		if (!strTempWhere.IsEmpty())
		{
			if (!pStrWhere->IsEmpty())
				(*pStrWhere) += " AND ";

			(*pStrWhere) += "(" + strTempWhere + ")";
		}
	}

	return 1;
}

long CProcedureICD9Form::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_lID;
}

BOOL CProcedureICD9Form::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_lIDProcedura != 0);
}

void CProcedureICD9Form::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CProcedureEsamiSet* pSet = (CProcedureEsamiSet*)pBaseSet;
	if (bToSet)
	{
		pSet->CopyFieldFrom(&m_ctrLine[nCounter].m_Set);
	}
	else
	{
		m_ctrLine[nCounter].m_Set.CopyFieldFrom(pSet);
		m_ctrLine[nCounter].m_nStato = RECORD_FULL;
		m_ctrLine[nCounter].m_lID = pSet->m_lID;
	}
}

BOOL CProcedureICD9Form::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

void CProcedureICD9Form::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void CProcedureICD9Form::OnChangeProcedura1()
{
	UpdateData(TRUE);
	SetLineDirty(m_nIndexLine+0, TRUE);
	UpdateData(FALSE);
}

void CProcedureICD9Form::OnChangeProcedura2()
{
	UpdateData(TRUE);
	SetLineDirty(m_nIndexLine+1, TRUE);
	UpdateData(FALSE);
}

void CProcedureICD9Form::OnChangeProcedura3()
{
	UpdateData(TRUE);
	SetLineDirty(m_nIndexLine+2, TRUE);
	UpdateData(FALSE);
}

long CProcedureICD9Form::GetContenuto()
{
	return sub_procedureicd9;
}

BOOL CProcedureICD9Form::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}

void CProcedureICD9Form::OnBnClickedBtnGruppi()
{
	m_ctrlButtonGruppi.SetCheck(BST_UNCHECKED);
	UpdateData(TRUE);

	CGruppiProcedureICD9UseDlg dlg(this, m_pEsamiView, m_pEsamiView->m_pEsamiSet->m_lIDEsame);
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_lReturn > 0)
		{
			CString strFilter;
			strFilter.Format("IDGruppo=%li", dlg.m_lReturn);

			CGruppiProcedureICD9ProcedureICD9Set setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CProcedureICD9Form::OnBnClickedBtnGruppi"))
			{
				for(int i = 0; i < MAX_OBJ_X_FORM; i++)
				{
					if ((m_ctrLine[i].m_nStato == RECORD_EMPTY) || (m_ctrLine[i].m_Set.m_lIDProcedura <= 0))
					{
						if (setTemp.IsEOF())
							break;

						// m_ctrLine[i].m_Set.m_Contatore = 0;
						m_ctrLine[i].m_Set.m_lIDEsame = 0;
						m_ctrLine[i].m_Set.m_lIDProcedura = setTemp.m_lIDProcedura;
						m_ctrLine[i].m_nStato = RECORD_FULL | RECORD_DIRTY;
						// m_ctrLine[i].m_nContatore = 0;

						setTemp.MoveNext();
					}
				}
				setTemp.CloseRecordset("CProcedureICD9Form::OnBnClickedBtnGruppi");
			}

			UpdateData(FALSE);
		}
	}
}

void CProcedureICD9Form::OnBnClickedBtnReset()
{
	m_ctrlButtonReset.SetCheck(BST_UNCHECKED);

	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
		{
			m_ctrLine[i].m_Set.m_lIDProcedura = 0;
			m_ctrLine[i].m_nStato = RECORD_EMPTY;
			SetLineDirty(i, TRUE);
		}
	}

	m_ctrlScroll.SetScrollPos(0);
	m_nIndexLine = 0;

	UpdateData(FALSE);
}

void CProcedureICD9Form::SaveForm(BOOL bPaziente, long* pParamOfFilter, CBaseSet* pSet, long* pCounterSet, long* pParamSet)
{
	BOOL bError;
	CString strFilter;

	CProcedureEsamiSet tempProcedureEsamiSet;

	for(int nCounter = 0; nCounter < MAX_OBJ_X_FORM; nCounter++)
	{
		BOOL bSave		= FALSE;
		long lID = 0;
		
		if (IsLineDirty(nCounter))
		{
			if (IsValidSet(nCounter))
			{
				lID = GetCounterSetOfLine(nCounter);
				
				if (lID > 0)
				{
					strFilter.Format("ID=%li", lID);
		
					if (pSet->RecordsetReOpen(bError, strFilter, "ID", "CProcedureICD9Form::SaveForm"))
						bSave = pSet->EditRecordset("CProcedureICD9Form::SaveForm");
				}
				else
				{
					bSave = pSet->AddNewRecordset("CProcedureICD9Form::SaveForm");
				}
			}
			else
			{
				lID = GetCounterSetOfLine(nCounter);
				
				if (lID > 0)
				{
					strFilter.Format("ID=%li", lID);
		
					if (pSet->RecordsetReOpen(bError, strFilter, "ID", "CProcedureICD9Form::SaveForm"))
						pSet->DeleteRecordset("CProcedureICD9Form::SaveForm");
				}
			}
		}

		if (bSave)
		{
			UpdateDataLine(pSet, nCounter, TRUE); // era m_pSet //

			if (lID)
			{
				//sono in Edit...
				*pParamSet = *pParamOfFilter;

				pSet->SetFieldDirty(pCounterSet, FALSE);
			}
			else
			{
				//sono in AddNew...
				*pParamSet = *pParamOfFilter;
				
				pSet->SetFieldDirty(pCounterSet, FALSE);
				pSet->SetFieldNull (pCounterSet, TRUE);
			}

			if (pSet->UpdateRecordset("CProcedureICD9Form::SaveForm"))
			{
				SetLineDirty(nCounter, FALSE);
			}
			else
			{
				pSet->NoEditRecordset("CProcedureICD9Form::SaveForm");
				
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_SUBFORM_DONT_SAVE), "CProcedureICD9Form::SaveForm", nCounter);
				theApp.AfxMessageBoxEndo(strError);
			}

		}
	}
}
