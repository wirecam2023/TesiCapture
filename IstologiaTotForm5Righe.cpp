#include "stdafx.h"
#include "Endox.h"
#include "IstologiaTotForm5Righe.h"

#include <io.h>

#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "GruppiPrelieviOldItemSet.h"
#include "GruppiPrelieviOldUseDlg.h"
#include "IstologiaTipiSet.h"
#include "MstOrganoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CIstologiaTotForm5Righe::CIstologiaTotForm5Righe(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CIstologiaTotForm5Righe::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 5;

	m_bStampaTutte = FALSE;
	m_rigaSelezionata = 0;
}

CIstologiaTotForm5Righe::~CIstologiaTotForm5Righe()
{
}

BEGIN_MESSAGE_MAP(CIstologiaTotForm5Righe, CSubForm)
	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_ORGANO_1, OnChangeOrgano1)
	ON_EN_CHANGE(IDC_ORGANO_2, OnChangeOrgano2)
	ON_EN_CHANGE(IDC_ORGANO_3, OnChangeOrgano3)
	ON_EN_CHANGE(IDC_ORGANO_6, OnChangeOrgano4)
	ON_EN_CHANGE(IDC_ORGANO_7, OnChangeOrgano5)
	ON_EN_CHANGE(IDC_SEDE_1, OnChangeSede1)
	ON_EN_CHANGE(IDC_SEDE_2, OnChangeSede2)
	ON_EN_CHANGE(IDC_SEDE_3, OnChangeSede3)
	ON_EN_CHANGE(IDC_SEDE_6, OnChangeSede4)
	ON_EN_CHANGE(IDC_SEDE_7, OnChangeSede5)
	ON_EN_CHANGE(IDC_PROVETTA_1, OnChangeProvette1)
	ON_EN_CHANGE(IDC_PROVETTA_2, OnChangeProvette2)
	ON_EN_CHANGE(IDC_PROVETTA_3, OnChangeProvette3)
	ON_EN_CHANGE(IDC_PROVETTA_4, OnChangeProvette4)
	ON_EN_CHANGE(IDC_PROVETTA_5, OnChangeProvette5)
	ON_CBN_SELCHANGE(IDC_TIPO_1, OnChangeTipo1)
	ON_CBN_SELCHANGE(IDC_TIPO_2, OnChangeTipo2)
	ON_CBN_SELCHANGE(IDC_TIPO_3, OnChangeTipo3)
	ON_CBN_SELCHANGE(IDC_TIPO_4, OnChangeTipo4)
	ON_CBN_SELCHANGE(IDC_TIPO_5, OnChangeTipo5)
	ON_EN_CHANGE(IDC_DIAGNOSI_1, OnChangeDiagnosi1)
	ON_EN_CHANGE(IDC_DIAGNOSI_2, OnChangeDiagnosi2)
	ON_EN_CHANGE(IDC_DIAGNOSI_3, OnChangeDiagnosi3)
	ON_EN_CHANGE(IDC_DIAGNOSI_4, OnChangeDiagnosi4)
	ON_EN_CHANGE(IDC_DIAGNOSI_5, OnChangeDiagnosi5)
	ON_BN_CLICKED(IDC_GRUPPI, OnBnClickedGruppi)
	ON_BN_CLICKED(IDC_STAMPA_TUTTE, OnBnClickedStampaTutte)
	ON_BN_CLICKED(IDC_STAMPA_1, OnBnClickedStampa1)
	ON_BN_CLICKED(IDC_STAMPA_2, OnBnClickedStampa2)
	ON_BN_CLICKED(IDC_STAMPA_3, OnBnClickedStampa3)
	ON_BN_CLICKED(IDC_STAMPA_4, OnBnClickedStampa4)
	ON_BN_CLICKED(IDC_STAMPA_5, OnBnClickedStampa5)

END_MESSAGE_MAP()

void CIstologiaTotForm5Righe::DoDataExchange(CDataExchange* pDX)
{
	static UINT nID_Numero  [5] = { IDC_NUM_1,      IDC_NUM_2,      IDC_NUM_3,		IDC_NUM_6,		IDC_NUM_7};
	static UINT nID_Organo  [5] = { IDC_ORGANO_1,   IDC_ORGANO_2,   IDC_ORGANO_3,	IDC_ORGANO_6,	IDC_ORGANO_7 };
	static UINT nID_Sede    [5] = { IDC_SEDE_1,     IDC_SEDE_2,     IDC_SEDE_3,		IDC_SEDE_6,		IDC_SEDE_7 };
	static UINT nID_Provette[5] = { IDC_PROVETTA_1, IDC_PROVETTA_2, IDC_PROVETTA_3,	IDC_PROVETTA_4,	IDC_PROVETTA_5 };
	static UINT nID_Tipo    [5] = { IDC_TIPO_1,     IDC_TIPO_2,     IDC_TIPO_3,		IDC_TIPO_4,		IDC_TIPO_5 };
	static UINT nID_Diagnosi[5] = { IDC_DIAGNOSI_1, IDC_DIAGNOSI_2, IDC_DIAGNOSI_3,	IDC_DIAGNOSI_4,	IDC_DIAGNOSI_5 };
	static UINT nID_Stampa  [5] = { IDC_STAMPA_1,	IDC_STAMPA_2,	IDC_STAMPA_3,	IDC_STAMPA_4,	IDC_STAMPA_5 };

	CSubForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ORGANO, m_ctrlStatic[0]);
	DDX_Control(pDX, IDC_SUIS_00, m_ctrlStatic[1]);
	DDX_Control(pDX, IDC_SUIS_01, m_ctrlStatic[2]);
	DDX_Control(pDX, IDC_SUIS_02, m_ctrlStatic[3]);
	DDX_Control(pDX, IDC_SUIS_03, m_ctrlStatic[4]);

	DDX_Control(pDX, IDC_GRUPPI, m_ctrlBtnGruppi);
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

				if (m_ctrLine[m_nIndexLine+i].m_Set.m_lTipo > 0)
				{
					for(int j = 1; j < m_ctrlTipo[i].GetCount(); j++)
					{
						if (m_ctrlTipo[i].GetItemData(j) == m_ctrLine[m_nIndexLine+i].m_Set.m_lTipo)
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
			
			// Sandro 11/11/2015 // modifico tutta la roba sotto perché così com'era non si riuscivano a cancellare righe //

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

void CIstologiaTotForm5Righe::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_istopatologia5righe] == NULL)
	{
		pEsamiView->m_pDynForm[sub_istopatologia5righe] = new CIstologiaTotForm5Righe(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_istopatologia5righe] != NULL)
		{
			pEsamiView->m_pDynForm[sub_istopatologia5righe]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_istopatologia5righe]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_istopatologia5righe]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_istopatologia5righe]->CreateChildForm(CIstologiaTotForm5Righe::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CIstologiaTotForm5Righe::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		case IDC_NUM_6:
		case IDC_NUM_7:
		case IDC_ORGANO_1:
		case IDC_ORGANO_2:
		case IDC_ORGANO_3:
		case IDC_ORGANO_6:
		case IDC_ORGANO_7:
		case IDC_SEDE_1:
		case IDC_SEDE_2:
		case IDC_SEDE_3:
		case IDC_SEDE_6:
		case IDC_SEDE_7:
		case IDC_TIPO_1:
		case IDC_TIPO_2:
		case IDC_TIPO_3:
		case IDC_TIPO_4:
		case IDC_TIPO_5:
		case IDC_PROVETTA_1:
		case IDC_PROVETTA_2:
		case IDC_PROVETTA_3:
		case IDC_PROVETTA_4:
		case IDC_PROVETTA_5:
		case IDC_DIAGNOSI_1:
		case IDC_DIAGNOSI_2:
		case IDC_DIAGNOSI_3:
		case IDC_DIAGNOSI_4:
		case IDC_DIAGNOSI_5:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CIstologiaTotForm5Righe::OnInitDialog() 
{
	CSubForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_SCROLL)->GetSafeHwnd(), CSize(100,0), CSize(100,100));

	AddAnchor(GetDlgItem(IDC_SUIS_01)->GetSafeHwnd(), CSize(0,0), CSize(0,0));
	AddAnchor(GetDlgItem(IDC_ORGANO)->GetSafeHwnd(), CSize(0,0), CSize(10,0));
	AddAnchor(GetDlgItem(IDC_SUIS_00)->GetSafeHwnd(), CSize(10,0), CSize(40,0));
	AddAnchor(GetDlgItem(IDC_SUIS_02)->GetSafeHwnd(), CSize(40,0), CSize(40,0));
	AddAnchor(GetDlgItem(IDC_SUIS_03)->GetSafeHwnd(), CSize(40,0), CSize(100,0));
	AddAnchor(GetDlgItem(IDC_GRUPPI)->GetSafeHwnd(), CSize(100,0), CSize(100,0));
	AddAnchor(GetDlgItem(IDC_STAMPA_TUTTE)->GetSafeHwnd(), CSize(100,0), CSize(100,0));

	AddAnchor(GetDlgItem(IDC_NUM_1)->GetSafeHwnd(), CSize(0,20), CSize(0,20));
	AddAnchor(GetDlgItem(IDC_TIPO_1)->GetSafeHwnd(), CSize(0,20), CSize(0,20));
	AddAnchor(GetDlgItem(IDC_ORGANO_1)->GetSafeHwnd(), CSize(0,20), CSize(10,20));
	AddAnchor(GetDlgItem(IDC_SEDE_1)->GetSafeHwnd(), CSize(10,20), CSize(40,20));
	AddAnchor(GetDlgItem(IDC_PROVETTA_1)->GetSafeHwnd(), CSize(40,20), CSize(40,20));
	AddAnchor(GetDlgItem(IDC_DIAGNOSI_1)->GetSafeHwnd(), CSize(40,20), CSize(100,20));
	AddAnchor(GetDlgItem(IDC_STAMPA_1)->GetSafeHwnd(), CSize(100,20), CSize(100,20));

	AddAnchor(GetDlgItem(IDC_NUM_2)->GetSafeHwnd(), CSize(0,40), CSize(0,40));
	AddAnchor(GetDlgItem(IDC_TIPO_2)->GetSafeHwnd(), CSize(0,40), CSize(0,40));
	AddAnchor(GetDlgItem(IDC_ORGANO_2)->GetSafeHwnd(), CSize(0,40), CSize(10,40));
	AddAnchor(GetDlgItem(IDC_SEDE_2)->GetSafeHwnd(), CSize(10,40), CSize(40,40));
	AddAnchor(GetDlgItem(IDC_PROVETTA_2)->GetSafeHwnd(), CSize(40,40), CSize(40,40));
	AddAnchor(GetDlgItem(IDC_DIAGNOSI_2)->GetSafeHwnd(), CSize(40,40), CSize(100,40));
	AddAnchor(GetDlgItem(IDC_STAMPA_2)->GetSafeHwnd(), CSize(100,40), CSize(100,40));

	AddAnchor(GetDlgItem(IDC_NUM_3)->GetSafeHwnd(), CSize(0,60), CSize(0,60));
	AddAnchor(GetDlgItem(IDC_TIPO_3)->GetSafeHwnd(), CSize(0,60), CSize(0,60));
	AddAnchor(GetDlgItem(IDC_ORGANO_3)->GetSafeHwnd(), CSize(0,60), CSize(10,60));
	AddAnchor(GetDlgItem(IDC_SEDE_3)->GetSafeHwnd(), CSize(10,60), CSize(40,60));
	AddAnchor(GetDlgItem(IDC_PROVETTA_3)->GetSafeHwnd(), CSize(40,60), CSize(40,60));
	AddAnchor(GetDlgItem(IDC_DIAGNOSI_3)->GetSafeHwnd(), CSize(40,60), CSize(100,60));
	AddAnchor(GetDlgItem(IDC_STAMPA_3)->GetSafeHwnd(), CSize(100,60), CSize(100,60));

	AddAnchor(GetDlgItem(IDC_NUM_6)->GetSafeHwnd(), CSize(0,80), CSize(0,80));
	AddAnchor(GetDlgItem(IDC_TIPO_4)->GetSafeHwnd(), CSize(0,80), CSize(0,80));
	AddAnchor(GetDlgItem(IDC_ORGANO_6)->GetSafeHwnd(), CSize(0,80), CSize(10,80));
	AddAnchor(GetDlgItem(IDC_SEDE_6)->GetSafeHwnd(), CSize(10,80), CSize(40,80));
	AddAnchor(GetDlgItem(IDC_PROVETTA_4)->GetSafeHwnd(), CSize(40,80), CSize(40,80));
	AddAnchor(GetDlgItem(IDC_DIAGNOSI_4)->GetSafeHwnd(), CSize(40,80), CSize(100,80));
	AddAnchor(GetDlgItem(IDC_STAMPA_4)->GetSafeHwnd(), CSize(100,80), CSize(100,80));

	AddAnchor(GetDlgItem(IDC_NUM_7)->GetSafeHwnd(), CSize(0,100), CSize(0,100));
	AddAnchor(GetDlgItem(IDC_TIPO_5)->GetSafeHwnd(), CSize(0,100), CSize(0,100));
	AddAnchor(GetDlgItem(IDC_ORGANO_7)->GetSafeHwnd(), CSize(0,100), CSize(10,100));
	AddAnchor(GetDlgItem(IDC_SEDE_7)->GetSafeHwnd(), CSize(10,100), CSize(40,100));
	AddAnchor(GetDlgItem(IDC_PROVETTA_5)->GetSafeHwnd(), CSize(40,100), CSize(40,100));
	AddAnchor(GetDlgItem(IDC_DIAGNOSI_5)->GetSafeHwnd(), CSize(40,100), CSize(100,100));
	AddAnchor(GetDlgItem(IDC_STAMPA_5)->GetSafeHwnd(), CSize(100,100), CSize(100,100));

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

	theApp.LocalizeDialog(this, CIstologiaTotForm5Righe::IDD, "IstologiaTotForm5Righe");
	return TRUE;
}

void CIstologiaTotForm5Righe::ModificaForm()
{
	UINT uiOrgano[] = { IDC_ORGANO_1, IDC_ORGANO_2, IDC_ORGANO_3, IDC_ORGANO_6, IDC_ORGANO_7 };
	UINT uiSede[] = { IDC_SEDE_1, IDC_SEDE_2, IDC_SEDE_3, IDC_SEDE_6, IDC_SEDE_7 };
	UINT uiDiagnosi[] = { IDC_DIAGNOSI_1, IDC_DIAGNOSI_2, IDC_DIAGNOSI_3, IDC_DIAGNOSI_4, IDC_DIAGNOSI_5 };

	for(int i = 0; i < m_nIndexPage; i++)
	{
		m_ctrlOrgano[i].SetParam(m_pEsamiView, GetDlgItem(uiOrgano[i]), GetDlgItem(uiSede[i]), GetDlgItem(uiDiagnosi[i]));
		m_ctrlSede[i].SetParam(m_pEsamiView, GetDlgItem(uiOrgano[i]), GetDlgItem(uiSede[i]), GetDlgItem(uiDiagnosi[i]));
		m_ctrlDiagnosi[i].SetParam(m_pEsamiView, GetDlgItem(uiOrgano[i]), GetDlgItem(uiSede[i]), GetDlgItem(uiDiagnosi[i]));
	}
}

LRESULT CIstologiaTotForm5Righe::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CIstologiaTotForm5Righe::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CIstologiaSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CIstologiaTotForm5Righe::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setTemp, nCounter, FALSE);

				nCounter++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CIstologiaTotForm5Righe::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CIstologiaTotForm5Righe::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	static UINT pControlID1[] = {
		IDC_ORGANO_1,
		IDC_ORGANO_2,
		IDC_ORGANO_3,
		IDC_ORGANO_6,
		IDC_ORGANO_7,
		IDC_SEDE_1,
		IDC_SEDE_2,
		IDC_SEDE_3,
		IDC_SEDE_6,
		IDC_SEDE_7,
		IDC_PROVETTA_1,
		IDC_PROVETTA_2,
		IDC_PROVETTA_3,
		IDC_PROVETTA_4,
		IDC_PROVETTA_5,
		IDC_DIAGNOSI_1,
		IDC_DIAGNOSI_2,
		IDC_DIAGNOSI_3,
		IDC_DIAGNOSI_4,
		IDC_DIAGNOSI_5
	};

	static UINT pControlID2[] = {
		IDC_TIPO_1,
		IDC_TIPO_2,
		IDC_TIPO_3,
		IDC_TIPO_4,
		IDC_TIPO_5
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

		m_ctrlBtnGruppi.EnableWindow(FALSE);
		GetDlgItem(IDC_SCROLL)->EnableWindow(FALSE);
	}
	else
	{
		for(i = 0; i < (sizeof(pControlID1) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlID1[i], EM_SETREADONLY, wParam, lParam);

		for(i = 0; i < (sizeof(pControlID2) / sizeof(UINT)); i++)
			GetDlgItem(pControlID2[i])->EnableWindow(!(BOOL)wParam);

		m_ctrlBtnGruppi.EnableWindow(!(BOOL)wParam);
		GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);
	}

	return 1;
}

LRESULT CIstologiaTotForm5Righe::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_nContatore = 0;
	}

	return 1;
}

LRESULT CIstologiaTotForm5Righe::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CIstologiaSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("CIstologiaTotForm5Righe::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lContatore, &setTemp.m_lEsame);
		setTemp.CloseRecordset("CIstologiaTotForm5Righe::OnFormSave");
	}

	return 1;
}

LRESULT CIstologiaTotForm5Righe::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
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

long CIstologiaTotForm5Righe::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_nContatore;
}

BOOL CIstologiaTotForm5Righe::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

BOOL CIstologiaTotForm5Righe::IsValidSet(int nCounter)
{
	return ((m_ctrLine[nCounter].m_Set.m_lTipo > 0) && (m_ctrLine[nCounter].m_Set.m_lOrgano > 0));
}

void CIstologiaTotForm5Righe::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void CIstologiaTotForm5Righe::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
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

void CIstologiaTotForm5Righe::OnChangeTipo1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeTipo2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeTipo3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeTipo4()
{
	SetLineDirty(m_nIndexLine+3, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeTipo5()
{
	SetLineDirty(m_nIndexLine+4, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeOrgano1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeOrgano2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeOrgano3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeOrgano4()
{
	SetLineDirty(m_nIndexLine+3, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeOrgano5()
{
	SetLineDirty(m_nIndexLine+4, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeSede1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeSede2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeSede3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeSede4()
{
	SetLineDirty(m_nIndexLine+3, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeSede5()
{
	SetLineDirty(m_nIndexLine+4, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeProvette1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeProvette2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeProvette3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeProvette4()
{
	SetLineDirty(m_nIndexLine+3, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeProvette5()
{
	SetLineDirty(m_nIndexLine+4, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeDiagnosi1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeDiagnosi2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeDiagnosi3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeDiagnosi4()
{
	SetLineDirty(m_nIndexLine+3, TRUE);
}

void CIstologiaTotForm5Righe::OnChangeDiagnosi5()
{
	SetLineDirty(m_nIndexLine+4, TRUE);
}

long CIstologiaTotForm5Righe::GetContenuto()
{
	return sub_istopatologia5righe;
}

BOOL CIstologiaTotForm5Righe::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}

void CIstologiaTotForm5Righe::OnBnClickedGruppi()
{
	m_ctrlBtnGruppi.SetCheck(BST_UNCHECKED);

	// UpdateData(TRUE);

	CGruppiPrelieviOldUseDlg dlg(this, m_pEsamiView);
	if (dlg.DoModal() == IDOK)
	{
		CString strFilter;
		strFilter.Format("IDGruppoOld=%li", dlg.m_lReturn);

		CGruppiPrelieviOldItemSet setTemp;
		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CIstologiaTotForm5Righe::OnBnClickedGruppi"))
		{
			while(!setTemp.IsEOF())
			{
				for(int i = 0; i < MAX_OBJ_X_FORM; i++)
				{
					if (m_ctrLine[i].m_nStato == RECORD_EMPTY)
					{
						m_ctrLine[i].m_Set.m_lTipo = setTemp.m_lTipo;
						m_ctrLine[i].m_Set.m_lOrgano = setTemp.m_lOrgano;
						m_ctrLine[i].m_Set.m_sSede = setTemp.m_sSede;
						m_ctrLine[i].m_Set.m_sProvette = setTemp.m_sProvette;
						m_ctrLine[i].m_Set.m_lProcedura = setTemp.m_lProcedura;
						m_ctrLine[i].m_Set.m_sDiagnosi = setTemp.m_sDiagnosi;

						m_ctrLine[i].m_nStato = RECORD_FULL | RECORD_DIRTY;
						m_ctrLine[i].m_nContatore = 0;

						break;
					}
				}

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CIstologiaTotForm5Righe::OnBnClickedGruppi");
		}
	}

	UpdateData(FALSE);
}

void CIstologiaTotForm5Righe::OnBnClickedStampaTutte()
{
	m_ctrlButtonStampaTutte.SetCheck(BST_UNCHECKED);
	
	m_bStampaTutte = TRUE;

	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		if (m_ctrLine[i].m_Set.m_lTipo > 0)
		{
			m_rigaSelezionata = i;
			StampaRiga(m_pEsamiView);
		}
	}

	m_bStampaTutte = FALSE;
}

void CIstologiaTotForm5Righe::OnBnClickedStampa1()
{
	m_ctrlStampa[0].SetCheck(BST_UNCHECKED);
	m_rigaSelezionata = 0;
	StampaRiga(m_pEsamiView);
}

void CIstologiaTotForm5Righe::OnBnClickedStampa2()
{
	m_ctrlStampa[1].SetCheck(BST_UNCHECKED);
	m_rigaSelezionata = 1;
	StampaRiga(m_pEsamiView);
}

void CIstologiaTotForm5Righe::OnBnClickedStampa3()
{
	m_ctrlStampa[2].SetCheck(BST_UNCHECKED);
	m_rigaSelezionata = 2;
	StampaRiga(m_pEsamiView);
}

void CIstologiaTotForm5Righe::OnBnClickedStampa4()
{
	m_ctrlStampa[3].SetCheck(BST_UNCHECKED);
	m_rigaSelezionata = 3;
	StampaRiga(m_pEsamiView);
}

void CIstologiaTotForm5Righe::OnBnClickedStampa5()
{
	m_ctrlStampa[4].SetCheck(BST_UNCHECKED);
	m_rigaSelezionata = 4;
	StampaRiga(m_pEsamiView);
}

void CIstologiaTotForm5Righe::StampaRiga(CEsamiView* pEsamiView)
{
	long lPdfId = 0;
	pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, theApp.m_sEditRep + "\\Etichette.rpa", FALSE, 1, &lPdfId,"");
}

CString CIstologiaTotForm5Righe::GetField(int nSubItem)
{
	CString strReturn = "";
	
	switch(nSubItem)
	{
		case 0:
		{
			if (m_bStampaTutte)
			{
				// Sandro 05/11/2013 // RAS 20130163 //
				if (theApp.m_bIstopatologiaMostraLettera)
				{
					long lTemp = m_rigaSelezionata;

					if (lTemp < 26)
						strReturn.Format("%c", 'A' + lTemp);
					else
						strReturn.Format("%c%c", 'A' + (lTemp / 26) - 1, 'A' + (lTemp % 26));
				}
				else
				{
					strReturn.Format("%d", m_rigaSelezionata + 1);
				}
			}
			else
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
			}

			break;
		}
		case 1:
		{
			if (m_bStampaTutte)
				strReturn = CIstologiaTipiSet().GetDescrizione(m_ctrLine[m_rigaSelezionata].m_Set.m_lTipo);
			else
				strReturn = CIstologiaTipiSet().GetDescrizione(m_ctrLine[m_nIndexLine + m_rigaSelezionata].m_Set.m_lTipo);
			break;
		}

		case 2:
		{
			if (m_bStampaTutte)
				strReturn = CMstOrganoSet().GetFieldText(m_ctrLine[m_rigaSelezionata].m_Set.m_lOrgano);
			else
				strReturn = CMstOrganoSet().GetFieldText(m_ctrLine[m_nIndexLine + m_rigaSelezionata].m_Set.m_lOrgano);
			break;
		}

		case 3:
		{
			if (m_bStampaTutte)
				strReturn.Format("%s", m_ctrLine[m_rigaSelezionata].m_Set.m_sSede);
			else
				strReturn.Format("%s", m_ctrLine[m_nIndexLine + m_rigaSelezionata].m_Set.m_sSede);
			break;
		}

		case 4:
		{
			if (m_bStampaTutte)
				strReturn.Format("%s", m_ctrLine[m_rigaSelezionata].m_Set.m_sProvette);
			else
				strReturn.Format("%s", m_ctrLine[m_nIndexLine + m_rigaSelezionata].m_Set.m_sProvette);
			break;
		}

		case 5:
		{
			if (m_bStampaTutte)
				strReturn.Format("%s", m_ctrLine[m_rigaSelezionata].m_Set.m_sDiagnosi);
			else
				strReturn.Format("%s", m_ctrLine[m_nIndexLine + m_rigaSelezionata].m_Set.m_sDiagnosi);
			break;
		}
	}

	return strReturn;
}

// Sandro 19/09/2013 // RAS 20130099 //
void CIstologiaTotForm5Righe::StampaTutteLeRighe()
{
	OnBnClickedStampaTutte();
}
