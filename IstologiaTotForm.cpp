#include "stdafx.h"
#include "Endox.h"
#include "IstologiaTotForm.h"

#include <io.h>

#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "IstologiaTipiSet.h"
#include "MstOrganoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CIstologiaTotForm::CIstologiaTotForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CIstologiaTotForm::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 3;

	m_rigaSelezionata = 0;
}

CIstologiaTotForm::~CIstologiaTotForm()
{
}

BEGIN_MESSAGE_MAP(CIstologiaTotForm, CSubForm)
	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_ORGANO_1, OnChangeOrgano1)
	ON_EN_CHANGE(IDC_ORGANO_2, OnChangeOrgano2)
	ON_EN_CHANGE(IDC_ORGANO_3, OnChangeOrgano3)
	ON_EN_CHANGE(IDC_SEDE_1, OnChangeSede1)
	ON_EN_CHANGE(IDC_SEDE_2, OnChangeSede2)
	ON_EN_CHANGE(IDC_SEDE_3, OnChangeSede3)
	ON_EN_CHANGE(IDC_PROVETTA_1, OnChangeProvette1)
	ON_EN_CHANGE(IDC_PROVETTA_2, OnChangeProvette2)
	ON_EN_CHANGE(IDC_PROVETTA_3, OnChangeProvette3)
	ON_CBN_SELCHANGE(IDC_TIPO_1, OnChangeTipo1)
	ON_CBN_SELCHANGE(IDC_TIPO_2, OnChangeTipo2)
	ON_CBN_SELCHANGE(IDC_TIPO_3, OnChangeTipo3)
	ON_EN_CHANGE(IDC_DIAGNOSI_1, OnChangeDiagnosi1)
	ON_EN_CHANGE(IDC_DIAGNOSI_2, OnChangeDiagnosi2)
	ON_EN_CHANGE(IDC_DIAGNOSI_3, OnChangeDiagnosi3)
	ON_BN_CLICKED(IDC_STAMPA_TUTTE, OnBnClickedStampaTutte)
	ON_BN_CLICKED(IDC_STAMPA_1, OnBnClickedStampa1)
	ON_BN_CLICKED(IDC_STAMPA_2, OnBnClickedStampa2)
	ON_BN_CLICKED(IDC_STAMPA_3, OnBnClickedStampa3)
END_MESSAGE_MAP()

void CIstologiaTotForm::DoDataExchange(CDataExchange* pDX)
{
	static UINT nID_Numero  [3] = { IDC_NUM_1,      IDC_NUM_2,      IDC_NUM_3 };
	static UINT nID_Organo  [3] = { IDC_ORGANO_1,   IDC_ORGANO_2,   IDC_ORGANO_3 };
	static UINT nID_Sede    [3] = { IDC_SEDE_1,     IDC_SEDE_2,     IDC_SEDE_3 };
	static UINT nID_Provette[3] = { IDC_PROVETTA_1, IDC_PROVETTA_2, IDC_PROVETTA_3 };
	static UINT nID_Tipo    [3] = { IDC_TIPO_1,     IDC_TIPO_2,     IDC_TIPO_3 };
	static UINT nID_Diagnosi[3] = { IDC_DIAGNOSI_1, IDC_DIAGNOSI_2, IDC_DIAGNOSI_3 };
	static UINT nID_Stampa  [3] = { IDC_STAMPA_1,	IDC_STAMPA_2,	IDC_STAMPA_3 };

	CSubForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ORGANO, m_ctrlStatic[0]);
	DDX_Control(pDX, IDC_SUIS_00, m_ctrlStatic[1]);
	DDX_Control(pDX, IDC_SUIS_01, m_ctrlStatic[2]);
	DDX_Control(pDX, IDC_SUIS_02, m_ctrlStatic[3]);
	DDX_Control(pDX, IDC_SUIS_03, m_ctrlStatic[4]);

	DDX_Control(pDX, IDC_STAMPA_TUTTE, m_ctrlButtonStampaTutte);
	
	for(int i = 0; i < m_nIndexPage; i++)
	{
		DDX_Control(pDX, nID_Organo[i], m_ctrlOrgano[i]);
		DDX_Control(pDX, nID_Sede[i], m_ctrlSede[i]);
		DDX_Control(pDX, nID_Tipo[i], m_ctrlTipo[i]);
		DDX_Control(pDX, nID_Diagnosi[i], m_ctrlDiagnosi[i]);
		DDX_Control(pDX, nID_Stampa[i], m_ctrlStampa[i]);
	}

	if (m_pEsamiView->m_pEsamiSet->IsOpen())
	{
		for(int i = 0; i < m_nIndexPage; i++)
		{
			DDX_Organo(pDX, nID_Organo[i], m_ctrLine[m_nIndexLine+i].m_Set.m_lOrgano);
			DDX_Text(pDX, nID_Sede[i], m_ctrLine[m_nIndexLine+i].m_Set.m_sSede);
			DDX_Text(pDX, nID_Provette[i], m_ctrLine[m_nIndexLine+i].m_Set.m_sProvette);

			// Sandro 13/01/2014 // RAS 20130203 //

			if (pDX->m_bSaveAndValidate)
			{
				m_ctrLine[m_nIndexLine + i].m_Set.m_lTipo = 0;

				int nCurSel = m_ctrlTipo[i].GetCurSel();
				if (nCurSel > 0)
					m_ctrLine[m_nIndexLine + i].m_Set.m_lTipo = m_ctrlTipo[i].GetItemData(nCurSel);
			}
			else
			{
				int nCurSel = 0;

				if (m_ctrLine[m_nIndexLine + i].m_Set.m_lTipo > 0)
				{
					for(int j = 1; j < m_ctrlTipo[i].GetCount(); j++)
					{
						if (m_ctrlTipo[i].GetItemData(j) == m_ctrLine[m_nIndexLine + i].m_Set.m_lTipo)
						{
							nCurSel = j;
							break;
						}
					}
				}

				m_ctrlTipo[i].SetCurSel(nCurSel);
			}

			//

			DDX_Text(pDX, nID_Diagnosi[i], m_ctrLine[m_nIndexLine+i].m_Set.m_sDiagnosi);

			// Sandro 29/07/2014 // modifico tutta la roba sotto perché così com'era non si riuscivano a cancellare righe //

			if (theApp.m_nProgramMode == NOTHING_MODE)
				m_ctrlStampa[i].EnableWindow(IsValidSet(m_nIndexLine + i));
			else
				m_ctrlStampa[i].EnableWindow(FALSE);

			/*
			if ((m_ctrLine[m_nIndexLine + i].m_Set.m_lTipo > 0))
			{
				SetLineDirty(m_nIndexLine + i, TRUE);
				if (!(theApp.m_nProgramMode & MODIFY_RECORD_ESAMI))
					m_ctrlStampa[i].EnableWindow(TRUE);
				else
					m_ctrlStampa[i].EnableWindow(FALSE);
			}
			else
			{
				SetLineDirty(m_nIndexLine + i, FALSE);
				m_ctrlStampa[i].EnableWindow(FALSE);
			}
			*/
		}
	}

	if (!(theApp.m_nProgramMode & MODIFY_RECORD_ESAMI))
		GetDlgItem(IDC_STAMPA_TUTTE)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_STAMPA_TUTTE)->EnableWindow(FALSE);

	if (!pDX->m_bSaveAndValidate)
	{
		for(int i = 0; i < m_nIndexPage; i++)
		{
			// Sandro 05/11/2013 // RAS 20130163 //
			if (theApp.m_bIstopatologiaMostraLettera)
			{
				CString sTemp = "";

				int lTemp = m_nIndexLine + i;

				if (lTemp < 26)
					sTemp.Format("%c", 'A' + lTemp);
				else
					sTemp.Format("%c%c", 'A' + (lTemp / 26) - 1, 'A' + (lTemp % 26));

				SetDlgItemText(nID_Numero[i], sTemp);
			}
			else
			{
				SetDlgItemInt(nID_Numero[i], m_nIndexLine + i + 1);
			}
		}
	}
}

void CIstologiaTotForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_istopatologia] == NULL)
	{
		pEsamiView->m_pDynForm[sub_istopatologia] = new CIstologiaTotForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_istopatologia] != NULL)
		{
			pEsamiView->m_pDynForm[sub_istopatologia]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_istopatologia]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_istopatologia]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_istopatologia]->CreateChildForm(CIstologiaTotForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CIstologiaTotForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_ORGANO:
		case IDC_SUIS_00:
		case IDC_SUIS_01:
		case IDC_SUIS_02:
		case IDC_SUIS_03:
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
		case IDC_ORGANO_1:
		case IDC_ORGANO_2:
		case IDC_ORGANO_3:
		case IDC_SEDE_1:
		case IDC_SEDE_2:
		case IDC_SEDE_3:
		case IDC_TIPO_1:
		case IDC_TIPO_2:
		case IDC_TIPO_3:
		case IDC_PROVETTA_1:
		case IDC_PROVETTA_2:
		case IDC_PROVETTA_3:
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

BOOL CIstologiaTotForm::OnInitDialog() 
{
	CSubForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_SCROLL)->GetSafeHwnd(), CSize(100,0), CSize(100,100));
	AddAnchor(GetDlgItem(IDC_NUM_1)->GetSafeHwnd(), CSize(0,1), CSize(0,34));
	AddAnchor(GetDlgItem(IDC_NUM_2)->GetSafeHwnd(), CSize(0,34), CSize(0,67));
	AddAnchor(GetDlgItem(IDC_NUM_3)->GetSafeHwnd(), CSize(0,67), CSize(0,100));
	AddAnchor(GetDlgItem(IDC_ORGANO)->GetSafeHwnd(), CSize(0,0), CSize(10,1));
	AddAnchor(GetDlgItem(IDC_SUIS_00)->GetSafeHwnd(), CSize(10,0), CSize(20,1));
	AddAnchor(GetDlgItem(IDC_SUIS_01)->GetSafeHwnd(), CSize(0,0), CSize(0,1));
	AddAnchor(GetDlgItem(IDC_SUIS_02)->GetSafeHwnd(), CSize(20,0), CSize(20,1));
	AddAnchor(GetDlgItem(IDC_SUIS_03)->GetSafeHwnd(), CSize(20,0), CSize(100,1));
	AddAnchor(GetDlgItem(IDC_STAMPA_TUTTE)->GetSafeHwnd(), CSize(90,0), CSize(100,1));
	AddAnchor(GetDlgItem(IDC_TIPO_1)->GetSafeHwnd(), CSize(0,17), CSize(0,17));
	AddAnchor(GetDlgItem(IDC_ORGANO_1)->GetSafeHwnd(), CSize(0,17), CSize(10,17));
	AddAnchor(GetDlgItem(IDC_SEDE_1)->GetSafeHwnd(), CSize(10,17), CSize(20,17));
	AddAnchor(GetDlgItem(IDC_PROVETTA_1)->GetSafeHwnd(), CSize(20,17), CSize(20,17));
	AddAnchor(GetDlgItem(IDC_DIAGNOSI_1)->GetSafeHwnd(), CSize(20,1), CSize(90,34));
	AddAnchor(GetDlgItem(IDC_STAMPA_1)->GetSafeHwnd(), CSize(90,17), CSize(100,17));
	AddAnchor(GetDlgItem(IDC_TIPO_2)->GetSafeHwnd(), CSize(0,50), CSize(0,50));
	AddAnchor(GetDlgItem(IDC_ORGANO_2)->GetSafeHwnd(), CSize(0,50), CSize(10,50));
	AddAnchor(GetDlgItem(IDC_SEDE_2)->GetSafeHwnd(), CSize(10,50), CSize(20,50));
	AddAnchor(GetDlgItem(IDC_PROVETTA_2)->GetSafeHwnd(), CSize(20,50), CSize(20,50));
	AddAnchor(GetDlgItem(IDC_DIAGNOSI_2)->GetSafeHwnd(), CSize(20,34), CSize(90,67));
	AddAnchor(GetDlgItem(IDC_STAMPA_2)->GetSafeHwnd(), CSize(90,50), CSize(100,50));
	AddAnchor(GetDlgItem(IDC_TIPO_3)->GetSafeHwnd(), CSize(0,83), CSize(0,83));
	AddAnchor(GetDlgItem(IDC_ORGANO_3)->GetSafeHwnd(), CSize(0,83), CSize(10,83));
	AddAnchor(GetDlgItem(IDC_SEDE_3)->GetSafeHwnd(), CSize(10,83), CSize(20,83));
	AddAnchor(GetDlgItem(IDC_PROVETTA_3)->GetSafeHwnd(), CSize(20,83), CSize(20,83));
	AddAnchor(GetDlgItem(IDC_DIAGNOSI_3)->GetSafeHwnd(), CSize(20,67), CSize(90,100));
	AddAnchor(GetDlgItem(IDC_STAMPA_3)->GetSafeHwnd(), CSize(90,83), CSize(100,83));

	// Sandro 13/01/2014 // RAS 20130203 //

	for(int i = 0; i < m_nIndexPage; i++)
	{
		m_ctrlTipo[i].ResetContent();

		m_ctrlTipo[i].InsertString(0, "");
		m_ctrlTipo[i].SetItemData(0, 0);
	}

	CIstologiaTipiSet setIT;
	setIT.SetSortRecord("Descrizione");
	if (setIT.OpenRecordset("CIstologiaTotForm::OnInitDialog"))
	{
		int nIndex = 1;

		while(!setIT.IsEOF())
		{
			for(int i = 0; i < m_nIndexPage; i++)
			{
				m_ctrlTipo[i].InsertString(nIndex, setIT.m_sDescrizione);
				m_ctrlTipo[i].SetItemData(nIndex, setIT.m_lID);
			}

			nIndex++;
			setIT.MoveNext();
		}

		setIT.CloseRecordset("CIstologiaTotForm::OnInitDialog");
	}

	for(int i = 0; i < m_nIndexPage; i++)
		m_ctrlTipo[i].SetCurSel(0);

	//

	for(int i = 0; i < m_nIndexPage; i++)
	{
		m_ctrlTipo[i].EnableWindow(FALSE);
		m_ctrlDiagnosi[i].SetLimitText(3999);
	}

	theApp.LocalizeDialog(this, CIstologiaTotForm::IDD, "IstologiaTotForm");

	return TRUE;
}

void CIstologiaTotForm::ModificaForm()
{
	UINT uiOrgano[] = { IDC_ORGANO_1, IDC_ORGANO_2, IDC_ORGANO_3 };
	UINT uiSede[] = { IDC_SEDE_1, IDC_SEDE_2, IDC_SEDE_3 };

	for(int i = 0; i < m_nIndexPage; i++)
	{
		m_ctrlOrgano[i].SetParam(m_pEsamiView, GetDlgItem(uiOrgano[i]), GetDlgItem(uiSede[i]));
		m_ctrlSede[i].SetParam(m_pEsamiView, GetDlgItem(uiOrgano[i]), GetDlgItem(uiSede[i]));
	}
}

LRESULT CIstologiaTotForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CIstologiaTotForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CIstologiaSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CIstologiaTotForm::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setTemp, nCounter, FALSE);

				nCounter++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CIstologiaTotForm::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CIstologiaTotForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	static UINT pControlID1[] = {
		IDC_ORGANO_1,
		IDC_ORGANO_2,
		IDC_ORGANO_3,
		IDC_SEDE_1,
		IDC_SEDE_2,
		IDC_SEDE_3,
		IDC_PROVETTA_1,
		IDC_PROVETTA_2,
		IDC_PROVETTA_3,
		IDC_DIAGNOSI_1,
		IDC_DIAGNOSI_2,
		IDC_DIAGNOSI_3,
	};

	static UINT pControlID2[] = {
		IDC_TIPO_1,
		IDC_TIPO_2,
		IDC_TIPO_3,
	};

	static UINT pControlSearchID1[] = {
		IDC_ORGANO_1,
		IDC_SEDE_1,
		IDC_PROVETTA_1,
		IDC_DIAGNOSI_1
	};

	static UINT pControlSearchID2[] = {
		IDC_TIPO_1
	};

	if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI))
	{
		for(i = 0; i < (sizeof(pControlSearchID1) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlSearchID1[i], EM_SETREADONLY, wParam, lParam);

		for(i = 0; i < (sizeof(pControlSearchID2) / sizeof(UINT)); i++)
			GetDlgItem(pControlSearchID2[i])->EnableWindow(!(BOOL)wParam);

		GetDlgItem(IDC_SCROLL)->EnableWindow(FALSE);
	}
	else
	{
		for(i = 0; i < (sizeof(pControlID1) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlID1[i], EM_SETREADONLY, wParam, lParam);

		for(i = 0; i < (sizeof(pControlID2) / sizeof(UINT)); i++)
			GetDlgItem(pControlID2[i])->EnableWindow(!(BOOL)wParam);

		GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);
	}

	return 1;
}

LRESULT CIstologiaTotForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_nContatore = 0;
	}

	return 1;
}

LRESULT CIstologiaTotForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CIstologiaSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("CIstologiaTotForm::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lContatore, &setTemp.m_lEsame);
		setTemp.CloseRecordset("CIstologiaTotForm::OnFormSave");
	}

	return 1;
}

LRESULT CIstologiaTotForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	CIstologiaSet* pSet = &m_ctrLine[0].m_Set;

	if (pSet->m_lTipo > 0)
		ComponiRicercaLong(pStrWhere, pSet, &pSet->m_lTipo, "EIstologia.Tipo", 4, "AND");
	
	if (pSet->m_lOrgano != -1)
		ComponiRicercaLong(pStrWhere, pSet, &pSet->m_lOrgano, "EIstologia.Organo", 0, "AND");
	
	ComponiRicercaString(pStrWhere, pSet, &pSet->m_sSede, "EIstologia.Sede", 2);
	ComponiRicercaString(pStrWhere, pSet, &pSet->m_sProvette, "EIstologia.Provette", 2);
	ComponiRicercaString(pStrWhere, pSet, &pSet->m_sDiagnosi, "EIstologia.Diagnosi", 1);

	return 1;
}

long CIstologiaTotForm::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_nContatore;
}

BOOL CIstologiaTotForm::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

BOOL CIstologiaTotForm::IsValidSet(int nCounter)
{
	// Sandro 05/02/2014 // 
	// return (m_ctrLine[nCounter].m_Set.m_sProvette != "");

	return ((m_ctrLine[nCounter].m_Set.m_lTipo > 0) && (m_ctrLine[nCounter].m_Set.m_lOrgano > 0));
}

void CIstologiaTotForm::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void CIstologiaTotForm::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CIstologiaSet* pSet = (CIstologiaSet*)pBaseSet;
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

void CIstologiaTotForm::OnChangeTipo1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CIstologiaTotForm::OnChangeTipo2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CIstologiaTotForm::OnChangeTipo3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CIstologiaTotForm::OnChangeOrgano1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CIstologiaTotForm::OnChangeOrgano2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CIstologiaTotForm::OnChangeOrgano3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CIstologiaTotForm::OnChangeSede1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CIstologiaTotForm::OnChangeSede2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CIstologiaTotForm::OnChangeSede3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CIstologiaTotForm::OnChangeProvette1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CIstologiaTotForm::OnChangeProvette2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CIstologiaTotForm::OnChangeProvette3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CIstologiaTotForm::OnChangeDiagnosi1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CIstologiaTotForm::OnChangeDiagnosi2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CIstologiaTotForm::OnChangeDiagnosi3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

long CIstologiaTotForm::GetContenuto()
{
	return sub_istopatologia;
}

BOOL CIstologiaTotForm::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}

void CIstologiaTotForm::OnBnClickedStampaTutte()
{
	m_ctrlButtonStampaTutte.SetCheck(BST_UNCHECKED);
	for(int i=0; i<MAX_OBJ_X_FORM; i++)
	{
		if (m_ctrLine[i].m_Set.m_lTipo > 0)
		{
			m_rigaSelezionata = i;
			StampaRiga(m_pEsamiView);
		}
	}
}

void CIstologiaTotForm::OnBnClickedStampa1()
{
	m_ctrlStampa[0].SetCheck(BST_UNCHECKED);
	m_rigaSelezionata = 0;
	StampaRiga(m_pEsamiView);
}

void CIstologiaTotForm::OnBnClickedStampa2()
{
	m_ctrlStampa[1].SetCheck(BST_UNCHECKED);
	m_rigaSelezionata = 1;
	StampaRiga(m_pEsamiView);
}

void CIstologiaTotForm::OnBnClickedStampa3()
{
	m_ctrlStampa[2].SetCheck(BST_UNCHECKED);
	m_rigaSelezionata = 2;
	StampaRiga(m_pEsamiView);
}

void CIstologiaTotForm::StampaRiga(CEsamiView* pEsamiView)
{
	long lPdfId = 0;
	pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, theApp.m_sEditRep + "\\Etichette.rpa", FALSE, 1, &lPdfId,"");
}

CString CIstologiaTotForm::GetField(int nSubItem)
{
	CString strReturn = "";
	
	switch(nSubItem) 
	{
		case 0:
		{
			// Sandro 05/11/2013 // RAS 20130163 //
			if (theApp.m_bIstopatologiaMostraLettera)
			{
				long lTemp = m_nIndexLine + m_rigaSelezionata;

				if (lTemp < 26)
					strReturn.Format("%c", 'A' + lTemp);
				else
					strReturn.Format("%c%c", 'A' + (lTemp / 26) - 1, 'A' + (lTemp % 26));
			}
			else
			{
				strReturn.Format("%d", m_nIndexLine + m_rigaSelezionata + 1);
			}

			break;
		}
		case 1:
		{
			strReturn = CIstologiaTipiSet().GetDescrizione(m_ctrLine[m_nIndexLine + m_rigaSelezionata].m_Set.m_lTipo);
			break;
		}

		case 2:
		{
			strReturn = CMstOrganoSet().GetFieldText(m_ctrLine[m_nIndexLine + m_rigaSelezionata].m_Set.m_lOrgano);
			break;
		}

		case 3:
		{
			strReturn.Format("%s", m_ctrLine[m_nIndexLine+m_rigaSelezionata].m_Set.m_sSede);
			break;
		}

		case 4:
		{
			strReturn.Format("%s", m_ctrLine[m_nIndexLine+m_rigaSelezionata].m_Set.m_sProvette);
			break;
		}

		case 5:
		{
			strReturn.Format("%s", m_ctrLine[m_nIndexLine+m_rigaSelezionata].m_Set.m_sDiagnosi);
			break;
		}
	}

	return strReturn;
}

// Sandro 19/09/2013 // RAS 20130099 //
void CIstologiaTotForm::StampaTutteLeRighe()
{
	OnBnClickedStampaTutte();
}
