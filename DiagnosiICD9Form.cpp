#include "stdafx.h"
#include "Endox.h"
#include "DiagnosiICD9Form.h"

#include "EsamiView.h"
#include "Common.h"
#include "EsamiSet.h"
#include "GruppiDiagnosiICD9UseDlg.h"
#include "GruppiDiagnosiICD9DiagnosiICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDiagnosiICD9Form::CDiagnosiICD9Form(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CDiagnosiICD9Form::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 3;

	m_nSearchMode = 0;
}

CDiagnosiICD9Form::~CDiagnosiICD9Form()
{
}

BEGIN_MESSAGE_MAP(CDiagnosiICD9Form, CSubForm)
	ON_WM_CTLCOLOR()

	ON_CBN_EDITCHANGE	(IDC_DIAGNOSI_1,		OnChangeDiagnosi1)
	ON_CBN_SELCHANGE	(IDC_DIAGNOSI_1,		OnChangeDiagnosi1)
	ON_CBN_EDITCHANGE	(IDC_DIAGNOSI_2,		OnChangeDiagnosi2)
	ON_CBN_SELCHANGE	(IDC_DIAGNOSI_2,		OnChangeDiagnosi2)
	ON_CBN_EDITCHANGE	(IDC_DIAGNOSI_3,		OnChangeDiagnosi3)
	ON_CBN_SELCHANGE	(IDC_DIAGNOSI_3,		OnChangeDiagnosi3)

	ON_BN_CLICKED(IDC_BTN_GRUPPI, OnBnClickedBtnGruppi)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBnClickedBtnReset)
END_MESSAGE_MAP()

void CDiagnosiICD9Form::DoDataExchange(CDataExchange* pDX)
{
	static UINT nID_Numero [3] = { IDC_NUM_1, IDC_NUM_2, IDC_NUM_3 };
	static UINT nID_Diagnosi[3] = { IDC_DIAGNOSI_1, IDC_DIAGNOSI_2, IDC_DIAGNOSI_3 };

	CSubForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SURE_00, m_ctrlStatic);

	for(int i = 0; i < m_nIndexPage; i++)
		DDX_Control(pDX, nID_Diagnosi[i], m_ctrlDiagnosi[i]);

	if (m_pEsamiView->m_pEsamiSet->IsOpen())
	{
		for(int i = 0; i < m_nIndexPage; i++)
		{
			DDX_DiagnosiICD9(pDX, nID_Diagnosi[i], m_ctrLine[m_nIndexLine+i].m_Set.m_lIDDiagnosi, m_pEsamiView->m_pEsamiSet->m_lProvenienza);
		}
	}

	if (!pDX->m_bSaveAndValidate)
		for(int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine+i+1);

	DDX_Control(pDX, IDC_BTN_GRUPPI, m_ctrlButtonGruppi);
	DDX_Control(pDX, IDC_BTN_RESET, m_ctrlButtonReset);

	DDX_Radio(pDX, IDC_RADIO_AND, m_nSearchMode);
}

void CDiagnosiICD9Form::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_diagnosiicd9] == NULL)
	{
		pEsamiView->m_pDynForm[sub_diagnosiicd9] = new CDiagnosiICD9Form(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_diagnosiicd9] != NULL)
		{
			pEsamiView->m_pDynForm[sub_diagnosiicd9]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_diagnosiicd9]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_diagnosiicd9]->m_lIDFaseBlocco = lIDFaseBlocco;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_diagnosiicd9]->CreateChildForm(CDiagnosiICD9Form::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CDiagnosiICD9Form::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		case IDC_DIAGNOSI_1:
		case IDC_DIAGNOSI_2:
		case IDC_DIAGNOSI_3:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CDiagnosiICD9Form::OnInitDialog() 
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
	AddAnchor(IDC_DIAGNOSI_1, CSize(0, 45), CSize(100, 45));
	AddAnchor(IDC_DIAGNOSI_2, CSize(0, 55), CSize(100, 55));
	AddAnchor(IDC_DIAGNOSI_3, CSize(0, 65), CSize(100, 65));

	GetDlgItem(IDC_SURE_00)->SetFont(&theApp.m_fontBold, TRUE);

	theApp.LocalizeDialog(this, CDiagnosiICD9Form::IDD, "DiagnosiICD9Form");
	return TRUE;
}

void CDiagnosiICD9Form::ModificaForm()
{
	for(int i = 0; i < m_nIndexPage; i++)
		m_ctrlDiagnosi[i].SetParam(m_pEsamiView, &m_ctrLine[m_nIndexLine+i].m_Set.m_lIDDiagnosi); // m_pDiagnosiICD9Set);
}

LRESULT CDiagnosiICD9Form::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CDiagnosiICD9Form::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CDiagnosiEsamiSet setDiagnosiEsami;
		setDiagnosiEsami.SetOpenFilter(sFilter);
		if (setDiagnosiEsami.OpenRecordset("CDiagnosiICD9Form::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setDiagnosiEsami.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setDiagnosiEsami, nCounter, FALSE);

				nCounter++;
				setDiagnosiEsami.MoveNext();
			}

			setDiagnosiEsami.CloseRecordset("CDiagnosiICD9Form::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CDiagnosiICD9Form::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	UINT pControlID2[] = {
		IDC_DIAGNOSI_1,
		IDC_DIAGNOSI_2,
		IDC_DIAGNOSI_3,
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

LRESULT CDiagnosiICD9Form::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_lID = 0;
	}

	return 1;
}

LRESULT CDiagnosiICD9Form::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CDiagnosiEsamiSet setDiagnosiEsami;
	setDiagnosiEsami.SetOpenFilter("ID=0");
	if (setDiagnosiEsami.OpenRecordset("CDiagnosiICD9Form::OnFormSave"))
	{
		SaveForm(FALSE, &m_pEsamiView->m_pEsamiSet->m_lContatore, &setDiagnosiEsami, &setDiagnosiEsami.m_lID, &setDiagnosiEsami.m_lIDEsame);
		setDiagnosiEsami.CloseRecordset("CDiagnosiICD9Form::OnFormSave");
	}

	return 1;
}

LRESULT CDiagnosiICD9Form::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	// cerco se è stata valorizzata almeno una prestazione //
	BOOL bProceed = FALSE;
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		if ((m_ctrLine[i].m_Set.m_lIDDiagnosi > 0) && (m_ctrLine[i].m_Set.m_lIDDiagnosi < 1246576928))
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
			if ((m_ctrLine[i].m_Set.m_lIDDiagnosi > 0) && (m_ctrLine[i].m_Set.m_lIDDiagnosi < 1246576928))
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "DiagnosiEsami", i, "IDEsame", "IDDiagnosi", m_ctrLine[i].m_Set.m_lIDDiagnosi, m_nSearchMode%2, MODE_UGUALE);

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

long CDiagnosiICD9Form::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_lID;
}

BOOL CDiagnosiICD9Form::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_lIDDiagnosi != 0);
}

void CDiagnosiICD9Form::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CDiagnosiEsamiSet* pSet = (CDiagnosiEsamiSet*)pBaseSet;
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

BOOL CDiagnosiICD9Form::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

void CDiagnosiICD9Form::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
	{
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	}
	else
	{
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
	}
}

void CDiagnosiICD9Form::OnChangeDiagnosi1()
{
	UpdateData(TRUE);
	SetLineDirty(m_nIndexLine+0, TRUE);
	UpdateData(FALSE);
}

void CDiagnosiICD9Form::OnChangeDiagnosi2()
{
	UpdateData(TRUE);
	SetLineDirty(m_nIndexLine+1, TRUE);
	UpdateData(FALSE);
}

void CDiagnosiICD9Form::OnChangeDiagnosi3()
{
	UpdateData(TRUE);
	SetLineDirty(m_nIndexLine+2, TRUE);
	UpdateData(FALSE);
}

long CDiagnosiICD9Form::GetContenuto()
{
	return sub_diagnosiicd9;
}

BOOL CDiagnosiICD9Form::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}

void CDiagnosiICD9Form::OnBnClickedBtnGruppi()
{
	m_ctrlButtonGruppi.SetCheck(BST_UNCHECKED);
	UpdateData(TRUE);

	CGruppiDiagnosiICD9UseDlg dlg(this, m_pEsamiView, m_pEsamiView->m_pEsamiSet->m_lIDEsame);
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_lReturn > 0)
		{
			CString strFilter;
			strFilter.Format("IDGruppo=%li", dlg.m_lReturn);

			CGruppiDiagnosiICD9DiagnosiICD9Set setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CDiagnosiICD9Form::OnBnClickedBtnGruppi"))
			{
				for(int i = 0; i < MAX_OBJ_X_FORM; i++)
				{
					if ((m_ctrLine[i].m_nStato == RECORD_EMPTY) || (m_ctrLine[i].m_Set.m_lIDDiagnosi <= 0))
					{
						if (setTemp.IsEOF())
							break;

						// m_ctrLine[i].m_Set.m_Contatore = 0;
						m_ctrLine[i].m_Set.m_lIDEsame = 0;
						m_ctrLine[i].m_Set.m_lIDDiagnosi = setTemp.m_lIDDiagnosi;
						m_ctrLine[i].m_nStato = RECORD_FULL | RECORD_DIRTY;
						// m_ctrLine[i].m_nContatore = 0;

						setTemp.MoveNext();
					}
				}
				setTemp.CloseRecordset("CDiagnosiICD9Form::OnBnClickedBtnGruppi");
			}

			UpdateData(FALSE);
		}
	}
}

void CDiagnosiICD9Form::OnBnClickedBtnReset()
{
	m_ctrlButtonReset.SetCheck(BST_UNCHECKED);

	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
		{
			m_ctrLine[i].m_Set.m_lIDDiagnosi = 0;
			m_ctrLine[i].m_nStato = RECORD_EMPTY;
			SetLineDirty(i, TRUE);
		}
	}

	m_ctrlScroll.SetScrollPos(0);
	m_nIndexLine = 0;

	UpdateData(FALSE);
}

void CDiagnosiICD9Form::SaveForm(BOOL bPaziente, long* pParamOfFilter, CBaseSet* pSet, long* pCounterSet, long* pParamSet)
{
	BOOL bError;
	CString strFilter;

	CDiagnosiEsamiSet tempDiagnosiEsamiSet;

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
		
					if (pSet->RecordsetReOpen(bError, strFilter, "ID", "CDiagnosiICD9Form::SaveForm"))
						bSave = pSet->EditRecordset("CDiagnosiICD9Form::SaveForm");
				}
				else
				{
					bSave = pSet->AddNewRecordset("CDiagnosiICD9Form::SaveForm");
				}
			}
			else
			{
				lID = GetCounterSetOfLine(nCounter);
				
				if (lID > 0)
				{
					strFilter.Format("ID=%li", lID);
		
					if (pSet->RecordsetReOpen(bError, strFilter, "ID", "CDiagnosiICD9Form::SaveForm"))
						pSet->DeleteRecordset("CDiagnosiICD9Form::SaveForm");
				}
			}
		}

		if (bSave)
		{
			UpdateDataLine(pSet, nCounter, TRUE); // era m_pSet //

			if (lID > 0)
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

			if (pSet->UpdateRecordset("CDiagnosiICD9Form::SaveForm"))
			{
				SetLineDirty(nCounter, FALSE);
			}
			else
			{
				pSet->NoEditRecordset("CDiagnosiICD9Form::SaveForm");
				
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_SUBFORM_DONT_SAVE), "CDiagnosiICD9Form::SaveForm", nCounter);
				theApp.AfxMessageBoxEndo(strError);
			}

		}
	}
}
