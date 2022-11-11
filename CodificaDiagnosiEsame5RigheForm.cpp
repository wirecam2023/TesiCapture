#include "stdafx.h"
#include "Endox.h"
#include "CodificaDiagnosiEsame5RigheForm.h"

#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "MstOrganoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int CCodificaDiagnosiEsame5RigheForm::m_nSearchMode = 0;

CCodificaDiagnosiEsame5RigheForm::CCodificaDiagnosiEsame5RigheForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CCodificaDiagnosiEsame5RigheForm::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 5;
}

CCodificaDiagnosiEsame5RigheForm::~CCodificaDiagnosiEsame5RigheForm()
{
}

BEGIN_MESSAGE_MAP(CCodificaDiagnosiEsame5RigheForm, CSubForm)
	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_ORGANO_1, OnChangeOrgano1)
	ON_EN_CHANGE(IDC_ORGANO_2, OnChangeOrgano2)
	ON_EN_CHANGE(IDC_ORGANO_3, OnChangeOrgano3)
	ON_EN_CHANGE(IDC_ORGANO_4, OnChangeOrgano4)
	ON_EN_CHANGE(IDC_ORGANO_5, OnChangeOrgano5)
	ON_EN_CHANGE(IDC_SEDE_1, OnChangeSede1)
	ON_EN_CHANGE(IDC_SEDE_2, OnChangeSede2)
	ON_EN_CHANGE(IDC_SEDE_3, OnChangeSede3)
	ON_EN_CHANGE(IDC_SEDE_4, OnChangeSede4)
	ON_EN_CHANGE(IDC_SEDE_5, OnChangeSede5)
	ON_EN_CHANGE(IDC_MST_1, OnChangeCodificaDiagnosiEsame1)
	ON_EN_CHANGE(IDC_MST_2, OnChangeCodificaDiagnosiEsame2)
	ON_EN_CHANGE(IDC_MST_3, OnChangeCodificaDiagnosiEsame3)
	ON_EN_CHANGE(IDC_MST_4, OnChangeCodificaDiagnosiEsame4)
	ON_EN_CHANGE(IDC_MST_5, OnChangeCodificaDiagnosiEsame5)
END_MESSAGE_MAP()

void CCodificaDiagnosiEsame5RigheForm::DoDataExchange(CDataExchange* pDX)
{
	static UINT nID_Numero        [5] = { IDC_NUM_1, IDC_NUM_2, IDC_NUM_3_1, IDC_NUM_4, IDC_NUM_5 };
	static UINT nID_Organo        [5] = { IDC_ORGANO_1, IDC_ORGANO_2, IDC_ORGANO_3, IDC_ORGANO_4, IDC_ORGANO_5 };
	static UINT nID_Sede          [5] = { IDC_SEDE_1, IDC_SEDE_2, IDC_SEDE_3, IDC_SEDE_4, IDC_SEDE_5 };
	static UINT nID_CodificaDiagnosiesame[5] = { IDC_MST_1, IDC_MST_2, IDC_MST_3, IDC_MST_4, IDC_MST_5 };
	
	CSubForm::DoDataExchange(pDX);

	for(int i = 0; i < m_nIndexPage; i++)
	{
		DDX_Control(pDX, nID_Organo[i], m_ctrlOrgano[i]);
		DDX_Control(pDX, nID_Sede[i], m_ctrlSede[i]);
	}

	if (m_pEsamiView->m_pEsamiSet->IsOpen())
	{
		for(int i = 0; i < m_nIndexPage; i++)
		{
			DDX_Organo(pDX, nID_Organo[i], m_ctrLine[m_nIndexLine+i].m_Set.m_lOrgano);
			DDX_Text(pDX, nID_Sede[i], m_ctrLine[m_nIndexLine+i].m_Set.m_sSede);
			DDX_Text(pDX, nID_CodificaDiagnosiesame[i], m_ctrLine[m_nIndexLine+i].m_Set.m_sDiagnosiEsame);
		}
	}

	if (!pDX->m_bSaveAndValidate)
		for(int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine+i+1);

	DDX_Radio(pDX, IDC_RADIO_AND, m_nSearchMode);
}

void CCodificaDiagnosiEsame5RigheForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_codificadiagnosiesame5righe] == NULL)
	{
		pEsamiView->m_pDynForm[sub_codificadiagnosiesame5righe] = new CCodificaDiagnosiEsame5RigheForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_codificadiagnosiesame5righe] != NULL)
		{
			pEsamiView->m_pDynForm[sub_codificadiagnosiesame5righe]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_codificadiagnosiesame5righe]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_codificadiagnosiesame5righe]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_codificadiagnosiesame5righe]->CreateChildForm(CCodificaDiagnosiEsame5RigheForm::IDD, pParent, rectFrame);
		}
	}
}

BOOL CCodificaDiagnosiEsame5RigheForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, CCodificaDiagnosiEsame5RigheForm** pForm)
{
	BOOL bResult = FALSE;

	if ((*pForm) == NULL)
	{
		(*pForm) = new CCodificaDiagnosiEsame5RigheForm(NULL, pEsamiView);
		if ((*pForm) != NULL)
		{
			(*pForm)->m_pParentFrame = pParentFrame;
			(*pForm)->m_lColore = -1;
			(*pForm)->m_lIDFaseBlocco = 2;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pParent->ScreenToClient(&rectFrame); // Sandro 19/10/2015 //
			bResult = (*pForm)->CreateChildForm(CCodificaDiagnosiEsame5RigheForm::IDD, pParent, rectFrame);
		}
	}
	
	return bResult;
}

HBRUSH CCodificaDiagnosiEsame5RigheForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_NUM_1:
		case IDC_NUM_2:
		case IDC_NUM_3_1:
		case IDC_NUM_4:
		case IDC_NUM_5:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			/*if (m_bCampoObbligatorio)
				pDC->SetBkColor(RGB_OBBLIG);*/

			break;
		}

		case IDC_ORGANO_1:
		case IDC_ORGANO_2:
		case IDC_ORGANO_3:
		case IDC_ORGANO_4:
		case IDC_ORGANO_5:
		case IDC_SEDE_1:
		case IDC_SEDE_2:
		case IDC_SEDE_3:
		case IDC_SEDE_4:
		case IDC_SEDE_5:
		case IDC_MST_1:
		case IDC_MST_2:
		case IDC_MST_3:
		case IDC_MST_4:
		case IDC_MST_5:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CCodificaDiagnosiEsame5RigheForm::OnInitDialog() 
{
	CSubForm::OnInitDialog();

	AddAnchor(IDC_SCROLL, CSize(100,0), CSize(100,100));
	AddAnchor(IDC_RADIO_AND, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_RADIO_OR, CSize(100,0), CSize(100,0));

	AddAnchor(IDC_NUM_1, CSize(0,0), CSize(0,0));
	AddAnchor(IDC_ORGANO_1, CSize(0,0), CSize(50,0));
	AddAnchor(IDC_SEDE_1, CSize(50,0), CSize(100,0));
	AddAnchor(IDC_MST_1, CSize(0,0), CSize(100,20));

	AddAnchor(IDC_NUM_2, CSize(0,20), CSize(0,20));
	AddAnchor(IDC_ORGANO_2, CSize(0,20), CSize(50,20));
	AddAnchor(IDC_SEDE_2, CSize(50,20), CSize(100,20));
	AddAnchor(IDC_MST_2, CSize(0,20), CSize(100,40));

	AddAnchor(IDC_NUM_3_1, CSize(0,40), CSize(0,40));
	AddAnchor(IDC_ORGANO_3, CSize(0,40), CSize(50,40));
	AddAnchor(IDC_SEDE_3, CSize(50,40), CSize(100,40));
	AddAnchor(IDC_MST_3, CSize(0,40), CSize(100,60));

	AddAnchor(IDC_NUM_4, CSize(0,60), CSize(0,60));
	AddAnchor(IDC_ORGANO_4, CSize(0,60), CSize(50,60));
	AddAnchor(IDC_SEDE_4, CSize(50,60), CSize(100,60));
	AddAnchor(IDC_MST_4, CSize(0,60), CSize(100,80));

	AddAnchor(IDC_NUM_5, CSize(0,80), CSize(0,80));
	AddAnchor(IDC_ORGANO_5, CSize(0,80), CSize(50,80));
	AddAnchor(IDC_SEDE_5, CSize(50,80), CSize(100,80));
	AddAnchor(IDC_MST_5, CSize(0,80), CSize(100,100));

	m_ctrlOrgano[0].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_1), GetDlgItem(IDC_SEDE_1));
	m_ctrlOrgano[1].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_2), GetDlgItem(IDC_SEDE_2));
	m_ctrlOrgano[2].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_3), GetDlgItem(IDC_SEDE_3));
	m_ctrlOrgano[3].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_4), GetDlgItem(IDC_SEDE_4));
	m_ctrlOrgano[4].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_5), GetDlgItem(IDC_SEDE_5));
	m_ctrlSede[0].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_1), GetDlgItem(IDC_SEDE_1));
	m_ctrlSede[1].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_2), GetDlgItem(IDC_SEDE_2));
	m_ctrlSede[2].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_3), GetDlgItem(IDC_SEDE_3));
	m_ctrlSede[3].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_4), GetDlgItem(IDC_SEDE_4));
	m_ctrlSede[4].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_5), GetDlgItem(IDC_SEDE_5));

	return TRUE;
}

void CCodificaDiagnosiEsame5RigheForm::ModificaForm()
{
}

LRESULT CCodificaDiagnosiEsame5RigheForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CCodificaDiagnosiEsame5RigheForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		OnFormReset(0, 0);
		GoToFirst();

		if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
		{
			CString sFilter;
			sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

			CCodificaDiagnosiEsameSet setTemp;
			setTemp.SetOpenFilter(sFilter);
			if (setTemp.OpenRecordset("CCodificaDiagnosiEsame5RigheForm::OnFormLoad"))
			{
				int nCounter = 0;
				while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
				{
					UpdateDataLine(&setTemp, nCounter, FALSE);

					nCounter++;
					setTemp.MoveNext();
				}

				setTemp.CloseRecordset("CCodificaDiagnosiEsame5RigheForm::OnFormLoad");
			}
		}
	}
	else
	{
		CCodificaDiagnosiEsame5RigheForm* pForm = (CCodificaDiagnosiEsame5RigheForm*)wParam;

		OnFormReset(0, 0);

		for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		{
			m_ctrLine[i].m_Set.CopyFieldFrom(&(pForm->m_ctrLine[i].m_Set));
			m_ctrLine[i].m_nStato = pForm->m_ctrLine[i].m_nStato;
			m_ctrLine[i].m_nContatore = pForm->m_ctrLine[i].m_nContatore;
		}
	}

	return 1;
}

LRESULT CCodificaDiagnosiEsame5RigheForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	UINT pControlID1[] = {
		IDC_ORGANO_1,
		IDC_SEDE_1,
		IDC_MST_1,
		IDC_ORGANO_2,
		IDC_SEDE_2,
		IDC_MST_2,
		IDC_ORGANO_3,
		IDC_SEDE_3,
		IDC_MST_3,
		IDC_ORGANO_4,
		IDC_SEDE_4,
		IDC_MST_4,
		IDC_ORGANO_5,
		IDC_SEDE_5,
		IDC_MST_5
	};

	UINT pControlID2[] = {
		IDC_RADIO_AND,
		IDC_RADIO_OR
	};

	for(i = 0; i < (sizeof(pControlID1) / sizeof(UINT)); i++)
		SendDlgItemMessage(pControlID1[i], EM_SETREADONLY, wParam, lParam);

	for(i = 0; i < (sizeof(pControlID2) / sizeof(UINT)); i++)
		GetDlgItem(pControlID2[i])->ShowWindow((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) != 0 ? SW_SHOW : SW_HIDE);

	GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);

	///////////////////////////////////////////
	// imposto le dimensioni della scrollbar //
	///////////////////////////////////////////

	CRect rectScroll;
	GetDlgItem(IDC_SCROLL)->GetWindowRect(&rectScroll);
	ScreenToClient(rectScroll);

	CRect rectSede;
	if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) != 0) 
		GetDlgItem(IDC_SEDE_2)->GetWindowRect(&rectSede); // siamo in ricerca //
	else
		GetDlgItem(IDC_SEDE_1)->GetWindowRect(&rectSede); // NON siamo in ricerca //
	ScreenToClient(rectSede);

	int iX = rectScroll.left;
	int iY = rectSede.top;
	int iCX = rectScroll.Width();
	int iCY = rectScroll.bottom - rectSede.top;
	GetDlgItem(IDC_SCROLL)->SetWindowPos(NULL, iX, iY, iCX, iCY, SWP_NOOWNERZORDER | SWP_NOZORDER);

	return 1;
}

LRESULT CCodificaDiagnosiEsame5RigheForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_nContatore = 0;
	}

	return 1;
}

LRESULT CCodificaDiagnosiEsame5RigheForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CCodificaDiagnosiEsameSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("CChirurgiciDynForm::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lContatore, &setTemp.m_lEsame);
		setTemp.CloseRecordset("CChirurgiciDynForm::OnFormSave");
	}

	return 1;
}

LRESULT CCodificaDiagnosiEsame5RigheForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	// cerco se è stata valorizzata almeno una riga //
	BOOL bProceed = FALSE;
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		if (((m_ctrLine[i].m_Set.m_lContatore > 0) && (m_ctrLine[i].m_Set.m_lContatore < 1246576928)) || (!m_ctrLine[i].m_Set.m_sSede.IsEmpty()) || (!m_ctrLine[i].m_Set.m_sDiagnosiEsame.IsEmpty()))
		{
			bProceed = TRUE;
			break;
		}
	}

	// se è stata trovata almeno una riga compongo il filtro //
	if (bProceed)
	{
		CString strTotWhere = "";

		for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		{
			if (((m_ctrLine[i].m_Set.m_lContatore > 0) && (m_ctrLine[i].m_Set.m_lContatore < 1246576928)) || (!m_ctrLine[i].m_Set.m_sSede.IsEmpty()) || (!m_ctrLine[i].m_Set.m_sDiagnosiEsame.IsEmpty()))
			{
				CString strTempWhere = "";

				// tra uno e l'altro ci metto sempre l'AND  che logicamente parlando è giusto, ma nell'operatore passo o OPER_AND (se faccio un AND) o OPER_AND_SPEC (se faccio un OR) che mi trascura il parametro lTable //
				ComponiRicercaNewLong  (pStrFrom, &strTempWhere, "CodificaDiagnosiEsame", i, "Esame", "Organo",			m_ctrLine[i].m_Set.m_lOrgano,			(m_nSearchMode%2) * 2, MODE_UGUALE);
				ComponiRicercaNewString(pStrFrom, &strTempWhere, "CodificaDiagnosiEsame", i, "Esame", "Sede",			m_ctrLine[i].m_Set.m_sSede,				(m_nSearchMode%2) * 2, MODE_LIKE2, FALSE);
				ComponiRicercaNewString(pStrFrom, &strTempWhere, "CodificaDiagnosiEsame", i, "Esame", "DiagnosiEsame",	m_ctrLine[i].m_Set.m_sDiagnosiEsame,	(m_nSearchMode%2) * 2, MODE_LIKE2, FALSE);

				// concateno le singole stringhe all'interno di una più grande divisa da AND o da OR a seconda dei casi //
				strTempWhere.Trim();
				if (!strTempWhere.IsEmpty())
				{
					if (!strTotWhere.IsEmpty())
						strTotWhere += " " + strOperators[m_nSearchMode%2] + " ";

					strTotWhere += "(" + strTempWhere + ")";
				}
			}
		}

		// unisco la stringona grande composita al WHERE generale mettendoci eventualmente un AND davanti //
		strTotWhere.Trim();
		if (!strTotWhere.IsEmpty())
		{
			if (!pStrWhere->IsEmpty())
				(*pStrWhere) += " " + strOperators[OPER_AND] + " ";

			(*pStrWhere) += "(" + strTotWhere + ")";
		}
	}

	return 1;
}

long CCodificaDiagnosiEsame5RigheForm::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_nContatore;
}

BOOL CCodificaDiagnosiEsame5RigheForm::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

BOOL CCodificaDiagnosiEsame5RigheForm::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_sDiagnosiEsame != "");
}

void CCodificaDiagnosiEsame5RigheForm::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void CCodificaDiagnosiEsame5RigheForm::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CCodificaDiagnosiEsameSet* pSet = (CCodificaDiagnosiEsameSet*)pBaseSet;
	if (bToSet)
	{
		pSet->CopyFieldFrom(&m_ctrLine[nCounter].m_Set);
	}
	else
	{
		m_ctrLine[nCounter].m_Set.CopyFieldFrom(pSet);
		m_ctrLine[nCounter].m_nStato = RECORD_FULL;
		m_ctrLine[nCounter].m_nContatore = pSet->m_lContatore;
	}
}

BOOL CCodificaDiagnosiEsame5RigheForm::UpdateNewDataLine(CCodificaDiagnosiEsameSet* pNewSet)
{
	BOOL bFound = FALSE;
	int i;

	CCodificaDiagnosiEsameSet setTemp;
	setTemp.CopyFieldFrom(pNewSet);

	// cerco un record con le stessse caratteristiche....
	for(i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
		{
			if ((m_ctrLine[i].m_Set.m_lOrgano == setTemp.m_lOrgano) && (m_ctrLine[i].m_Set.m_sSede == setTemp.m_sSede) && (m_ctrLine[i].m_Set.m_sDiagnosiEsame.Find(setTemp.m_sDiagnosiEsame) >= 0))
			{
				bFound = TRUE;
				break;
			}
		}
	}

	// se esiste non aggiungo nulla....
	if (!bFound)
	{
		// Se esiste già un record gli aggiungo la nuova descrizione e la nuova codifica...
		for(i = 0; i < MAX_OBJ_X_FORM; i++)
		{
			if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			{
				if ((m_ctrLine[i].m_Set.m_lOrgano == setTemp.m_lOrgano) && (m_ctrLine[i].m_Set.m_sSede == setTemp.m_sSede))
				{
					m_ctrLine[i].m_Set.m_sDiagnosiEsame = AddStringWithoutRepeatition(m_ctrLine[i].m_Set.m_sDiagnosiEsame, setTemp.m_sDiagnosiEsame);
					
					m_ctrLine[i].m_nStato |= RECORD_FULL;
					
					bFound = TRUE;
					break;
				}
			}
		}
		
		if (bFound == FALSE)
		{
			// Aggiungo solo se non ce ne' un'altro uguale...
			for(i = 0; i < MAX_OBJ_X_FORM; i++)
			{
				if (m_ctrLine[i].m_nStato == RECORD_EMPTY)
				{
					m_ctrLine[i].m_Set.CopyFieldFrom(&setTemp);
					m_ctrLine[i].m_nStato		= RECORD_DIRTY | RECORD_FULL;
					m_ctrLine[i].m_nContatore	= 0;

					bFound = TRUE;
					break;
				}
			}
		}
	}
	else
	{
		// errore...
		bFound = FALSE;
	}

	return bFound;
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeCodificaDiagnosiEsame1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeCodificaDiagnosiEsame2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeCodificaDiagnosiEsame3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeCodificaDiagnosiEsame4()
{
	SetLineDirty(m_nIndexLine+3, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeCodificaDiagnosiEsame5()
{
	SetLineDirty(m_nIndexLine+4, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeOrgano1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeOrgano2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeOrgano3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeOrgano4()
{
	SetLineDirty(m_nIndexLine+3, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeOrgano5()
{
	SetLineDirty(m_nIndexLine+4, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeSede1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeSede2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeSede3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeSede4()
{
	SetLineDirty(m_nIndexLine+3, TRUE);
}

void CCodificaDiagnosiEsame5RigheForm::OnChangeSede5()
{
	SetLineDirty(m_nIndexLine+4, TRUE);
}

long CCodificaDiagnosiEsame5RigheForm::GetContenuto()
{
	return sub_codificadiagnosiesame5righe;
}

BOOL CCodificaDiagnosiEsame5RigheForm::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}