#include "stdafx.h"
#include "Endox.h"
#include "OsservazioniForm.h"

#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COsservazioniForm::COsservazioniForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(COsservazioniForm::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 2;
}

COsservazioniForm::~COsservazioniForm()
{
}

BEGIN_MESSAGE_MAP(COsservazioniForm, CSubForm)
	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_MST_1, OnChangeOsservazioni1)
	ON_EN_CHANGE(IDC_MST_2, OnChangeOsservazioni2)
	ON_EN_CHANGE(IDC_ORGANO_1, OnChangeOrgano1)
	ON_EN_CHANGE(IDC_ORGANO_2, OnChangeOrgano2)
	ON_EN_CHANGE(IDC_SEDE_1, OnChangeSede1)
	ON_EN_CHANGE(IDC_SEDE_2, OnChangeSede2)
END_MESSAGE_MAP()

void COsservazioniForm::DoDataExchange(CDataExchange* pDX)
{
	static UINT nID_Numero      [2] = { IDC_NUM_1, IDC_NUM_2 };
	static UINT nID_Organo      [2] = { IDC_ORGANO_1, IDC_ORGANO_2 };
	static UINT nID_Sede        [2] = { IDC_SEDE_1, IDC_SEDE_2 };
	static UINT nID_Osservazioni[2] = { IDC_MST_1, IDC_MST_2 };
	
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
			DDX_Text(pDX, nID_Osservazioni[i], m_ctrLine[m_nIndexLine+i].m_Set.m_sOsservazioni);
		}
	}

	if (!pDX->m_bSaveAndValidate)
		for(int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine+i+1);
}

void COsservazioniForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_osservazioni] == NULL)
	{
		pEsamiView->m_pDynForm[sub_osservazioni] = new COsservazioniForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_osservazioni] != NULL)
		{
			pEsamiView->m_pDynForm[sub_osservazioni]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_osservazioni]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_osservazioni]->m_lIDFaseBlocco = lIDFaseBlocco;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_osservazioni]->CreateChildForm(COsservazioniForm::IDD, pParent, rectFrame);
		}
	}
}

BOOL COsservazioniForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, COsservazioniForm** pForm)
{
	BOOL bResult = FALSE;

	if ((*pForm) == NULL)
	{
		(*pForm) = new COsservazioniForm(NULL, pEsamiView);
		if ((*pForm) != NULL)
		{
			(*pForm)->m_pParentFrame = pParentFrame;
			(*pForm)->m_lColore = -1;
			(*pForm)->m_lIDFaseBlocco = 2;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pParent->ScreenToClient(&rectFrame); // Sandro 19/10/2015 //
			bResult = (*pForm)->CreateChildForm(COsservazioniForm::IDD, pParent, rectFrame);
		}
	}
	
	return bResult;
}

HBRUSH COsservazioniForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_NUM_1:
		case IDC_NUM_2:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			/*if (m_bCampoObbligatorio)
				pDC->SetBkColor(RGB_OBBLIG);*/

			break;
		}

		case IDC_ORGANO_1:
		case IDC_ORGANO_2:
		case IDC_SEDE_1:
		case IDC_SEDE_2:
		case IDC_MST_1:
		case IDC_MST_2:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL COsservazioniForm::OnInitDialog() 
{
	BOOL bResult = CSubForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_SCROLL)->GetSafeHwnd(), CSize(100,0), CSize(100,100));
	AddAnchor(GetDlgItem(IDC_NUM_1)->GetSafeHwnd(), CSize(0,0), CSize(0,0));
	AddAnchor(GetDlgItem(IDC_ORGANO_1)->GetSafeHwnd(), CSize(0,0), CSize(50,0));
	AddAnchor(GetDlgItem(IDC_SEDE_1)->GetSafeHwnd(), CSize(50,0), CSize(100,0));
	AddAnchor(GetDlgItem(IDC_MST_1)->GetSafeHwnd(), CSize(0,0), CSize(100,50));
	AddAnchor(GetDlgItem(IDC_NUM_2)->GetSafeHwnd(), CSize(0,50), CSize(0,50));
	AddAnchor(GetDlgItem(IDC_ORGANO_2)->GetSafeHwnd(), CSize(0,50), CSize(50,50));
	AddAnchor(GetDlgItem(IDC_SEDE_2)->GetSafeHwnd(), CSize(50,50), CSize(100,50));
	AddAnchor(GetDlgItem(IDC_MST_2)->GetSafeHwnd(), CSize(0,50), CSize(100,100));

	m_ctrlOrgano[0].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_1), GetDlgItem(IDC_SEDE_1));
	m_ctrlOrgano[1].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_2), GetDlgItem(IDC_SEDE_2));
	m_ctrlSede[0].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_1), GetDlgItem(IDC_SEDE_1));
	m_ctrlSede[1].SetParam(m_pEsamiView, GetDlgItem(IDC_ORGANO_2), GetDlgItem(IDC_SEDE_2));

	return bResult;
}

void COsservazioniForm::ModificaForm()
{
}

LRESULT COsservazioniForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT COsservazioniForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		OnFormReset(0, 0);
		GoToFirst();

		if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
		{
			CString sFilter;
			sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

			COsservazioniSet setTemp;
			setTemp.SetOpenFilter(sFilter);
			if (setTemp.OpenRecordset("COsservazioniForm::OnFormLoad"))
			{
				int nCounter = 0;
				while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
				{
					UpdateDataLine(&setTemp, nCounter, FALSE);

					nCounter++;
					setTemp.MoveNext();
				}
				setTemp.CloseRecordset("COsservazioniForm::OnFormLoad");
			}
		}
	}
	else
	{
		COsservazioniForm* pForm = (COsservazioniForm*)wParam;

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

LRESULT COsservazioniForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	if (((BOOL)wParam == FALSE) && ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)))
	{
		static UINT pControlID[] = {
			IDC_ORGANO_1,
			IDC_SEDE_1,
			IDC_MST_1
		};

		for(i = 0; i < (sizeof(pControlID) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlID[i], EM_SETREADONLY, wParam, lParam);

		m_ctrlScroll.SetScrollPos(0);
		GetDlgItem(IDC_SCROLL)->EnableWindow(FALSE);

		m_nIndexLine = 0;

		ModificaForm();

		UpdateData(FALSE);
	}
	else
	{
		static UINT pControlID[] = {
			IDC_ORGANO_1,
			IDC_SEDE_1,
			IDC_MST_1,
			IDC_ORGANO_2,
			IDC_SEDE_2,
			IDC_MST_2
		};

		for(i = 0; i < (sizeof(pControlID) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlID[i], EM_SETREADONLY, wParam, lParam);

		GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);
	}

	return 1;
}

LRESULT COsservazioniForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_nContatore = 0;
	}

	return 1;
}

LRESULT COsservazioniForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	COsservazioniSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("COsservazioniForm::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lContatore, &setTemp.m_lEsame);
		setTemp.CloseRecordset("COsservazioniForm::OnFormSave");
	}

	return 1;
}

LRESULT COsservazioniForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	COsservazioniSet* pSet = &m_ctrLine[0].m_Set;

	ComponiRicercaString(pStrWhere, pSet, &pSet->m_sSede, "EOsservazioni.Sede", 1);

	if (pSet->m_lOrgano != -1)
		ComponiRicercaLong(pStrWhere, pSet, &pSet->m_lOrgano, "EOsservazioni.Organo", 0, "AND");

	ComponiRicercaString(pStrWhere, pSet, &pSet->m_sOsservazioni, "EOsservazioni.Osservazioni", 1);

	return 1;
}

long COsservazioniForm::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_nContatore;
}

BOOL COsservazioniForm::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

BOOL COsservazioniForm::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_sOsservazioni != "");
}

void COsservazioniForm::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void COsservazioniForm::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	COsservazioniSet* pSet = (COsservazioniSet*)pBaseSet;
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

BOOL COsservazioniForm::UpdateNewDataLine(COsservazioniSet* pNewSet)
{
	BOOL bFound = FALSE;
	int i;

	COsservazioniSet setTemp;
	setTemp.CopyFieldFrom(pNewSet);

	//cerco un record con le stessse caratteristiche....
	for(i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
		{
			if ((m_ctrLine[i].m_Set.m_lOrgano == setTemp.m_lOrgano) && (m_ctrLine[i].m_Set.m_sSede == setTemp.m_sSede) && (m_ctrLine[i].m_Set.m_sOsservazioni.Find(setTemp.m_sOsservazioni) >= 0))
			{
				bFound = TRUE;
				break;
			}
		}
	}

	//se esiste non aggiungo nulla....
	if (!bFound)
	{
		//Se esiste già un record gli aggiungo la nuova descrizione e la nuova codifica...
		for(i = 0; i < MAX_OBJ_X_FORM; i++)
		{
			if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			{
				if ((m_ctrLine[i].m_Set.m_lOrgano == setTemp.m_lOrgano) && (m_ctrLine[i].m_Set.m_sSede == setTemp.m_sSede))
				{
					m_ctrLine[i].m_Set.m_sOsservazioni = AddStringWithoutRepeatition(m_ctrLine[i].m_Set.m_sOsservazioni, setTemp.m_sOsservazioni);
					
					m_ctrLine[i].m_nStato |= RECORD_FULL;
					
					bFound = TRUE;
					break;
				}
			}
		}
		
		if (bFound == FALSE)
		{
			//Aggiungo solo se non ce ne' un'altro uguale...
			for(i = 0; i < MAX_OBJ_X_FORM; i++)
			{
				if (m_ctrLine[i].m_nStato == RECORD_EMPTY)
				{
					m_ctrLine[i].m_Set.CopyFieldFrom(&setTemp);
					m_ctrLine[i].m_nStato = RECORD_DIRTY | RECORD_FULL;
					m_ctrLine[i].m_nContatore = 0;

					bFound = TRUE;
					break;
				}
			}
		}
	}
	else
	{
		//errore...
		bFound = FALSE;
	}

	return bFound;
}

void COsservazioniForm::OnChangeOsservazioni1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void COsservazioniForm::OnChangeOsservazioni2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void COsservazioniForm::OnChangeOrgano1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void COsservazioniForm::OnChangeOrgano2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void COsservazioniForm::OnChangeSede1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void COsservazioniForm::OnChangeSede2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void COsservazioniForm::OnChangeCodifica1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void COsservazioniForm::OnChangeCodifica2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

long COsservazioniForm::GetContenuto()
{
	return sub_osservazioni;
}

BOOL COsservazioniForm::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}