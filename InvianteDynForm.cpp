/************************************************************************

--provenienza
select * from PROVENIENZA --Il valore scelto viene salvato su EESAMI.IDPROVENIENZANEW e EESAMI.PROVENIENZA

--inviante 1 incompatibile con invianteI --
--inviante 1 con provenienza interno
select * from ECOMBOTABELLA where upper(NOMETABELLA) like 'ESAMEOSPEDALE' --Il valore scelto viene salvato su EESAMI.OSPEDALE
--inviante 1 con provenienza esterno
select * from EINVIANTIESTERNI -- Il valore scelto viene salvato in EESAMI.INVIANTE

--inviante 2 incompatibile con invianteI --
--inviante 2 con provenienza interno
select * from EINVIANTIINTERNI -- Il valore scelto viene salvato in EESAMI.INVIANTE
--inviante 2 con provenienza esterno
select * from EMEDICICURANTI -- Il valore scelto viene salvato in EESAMI.IDINVMEDICO e EESAMI.INVMEDICO

--inviante 3 con provenienza interno
select * from ECOMBOTABELLA where upper(NOMETABELLA) like 'TIPODEGENZAINTERNI' -- Il valore scelto viene salvato in EESAMI.TIPODEGENZAINTERNO
--inviante 3 con provenienza esterno
select * from ECOMBOTABELLA where upper(NOMETABELLA) like 'TIPODEGENZAESTERNI' -- Il valore scelto viene salvato in EESAMI.TIPODEGENZAESTERNO

--inviante E con provenienza interno
select * from EMEDICICURANTI -- Il valore scelto viene salvato in EESAMI.IDINVMEDICO e EESAMI.INVMEDICO
--inviante E con provenienza esterno
select * from EMEDICICURANTI -- Il valore scelto viene salvato in EESAMI.IDINVMEDICO e EESAMI.INVMEDICO

--inviante I con provenienza interno
select * from EINVIANTIINTERNI -- Il valore scelto viene salvato in EESAMI.INVIANTE
--inviante I con provenienza esterno
select * from EINVIANTIESTERNI -- Il valore scelto viene salvato in EESAMI.INVIANTE

***************************************************************************/



#include "stdafx.h"
#include "Endox.h"
#include "InvianteDynForm.h"

#include "EsamiView.h"
#include "EsamiSet.h"
#include "Common.h"
#include "PazientiSet.h"
#include "InvianteDynForm1.h"
#include "InvianteDynForm2.h"
#include "InvianteDynForm3.h"
#include "ProvenienzaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInvianteDynForm::CInvianteDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
}

CInvianteDynForm::~CInvianteDynForm()
{
}

BEGIN_MESSAGE_MAP(CInvianteDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_EN_SETFOCUS(IDC_EDIT_PROVENIENZA, OnEnSetfocusEditProvenienza)
	ON_CBN_SETFOCUS(IDC_COMBO_PROVENIENZA, OnCbnSetfocusComboProvenienza)
	
	ON_CBN_SELCHANGE(IDC_COMBO_PROVENIENZA, &CInvianteDynForm::OnCbnSelchangeComboProvenienza)
	ON_EN_CHANGE(IDC_EDIT_PROVENIENZA, &CInvianteDynForm::OnEnChangeEditProvenienza)
END_MESSAGE_MAP()

void CInvianteDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_inviante] == NULL)
	{
		pEsamiView->m_pDynForm[sub_inviante] = new CInvianteDynForm(CInvianteDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_inviante] != NULL)
		{
			pEsamiView->m_pDynForm[sub_inviante]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_inviante]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_inviante]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_inviante]->CreateChildForm(CInvianteDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CInvianteDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_LABEL:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_COMBO_PROVENIENZA:
		case IDC_EDIT_PROVENIENZA:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CInvianteDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_PROVENIENZA, m_ctrlComboProvenienza);
	DDX_Control(pDX, IDC_EDIT_PROVENIENZA, m_ctrlEditProvenienza);

	DDX_FieldProvenienzaCombo(pDX, IDC_COMBO_PROVENIENZA, m_pEsamiView->m_pEsamiSet->m_lIdProvenienzaNew, m_pEsamiView->m_pEsamiSet->m_lProvenienza, m_pEsamiView->m_pEsamiSet);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		DDX_Text(pDX, IDC_EDIT_PROVENIENZA, m_ctrlEditProvenienza.m_strRicercaView);
	}
	else
	{
		DDX_FieldProvenienzaEdit(pDX, IDC_EDIT_PROVENIENZA, m_pEsamiView->m_pEsamiSet->m_lIdProvenienzaNew, m_pEsamiView->m_pEsamiSet);
	}
}

BOOL CInvianteDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_LABEL, CSize(0, 50), CSize(100, 50));
	AddAnchor(IDC_COMBO_PROVENIENZA, CSize(0, 50), CSize(100, 50));
	AddAnchor(IDC_EDIT_PROVENIENZA, CSize(0, 50), CSize(100, 50));

	m_ctrlComboProvenienza.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIdProvenienzaNew);
	m_ctrlEditProvenienza.SetParam(this, m_pEsamiView->m_pEsamiSet);

	return bReturn;
}

LRESULT CInvianteDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CInvianteDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	if (theApp.m_nProgramMode & ADD_RECORD_ESAMI)
	{
		m_pEsamiView->m_pEsamiSet->m_lIdProvenienzaNew = CProvenienzaSet().GetFirst(INTERNO);
		m_pEsamiView->m_pEsamiSet->m_lProvenienza = CProvenienzaSet().GetInternoEsterno(m_pEsamiView->m_pEsamiSet->m_lIdProvenienzaNew);

		if (m_pEsamiView->m_pDynForm[edt_inviante1] != NULL)
		{
			CInvianteDynForm1* pDynForm1 = (CInvianteDynForm1*)m_pEsamiView->m_pDynForm[edt_inviante1];
			pDynForm1->UpdateData(FALSE);
		}
		if (m_pEsamiView->m_pDynForm[edt_inviante2] != NULL)
		{
			CInvianteDynForm2* pDynForm2 = (CInvianteDynForm2*)m_pEsamiView->m_pDynForm[edt_inviante2];
			pDynForm2->UpdateData(FALSE);
		}
		if (m_pEsamiView->m_pDynForm[edt_inviante3] != NULL)
		{
			CInvianteDynForm3* pDynForm3 = (CInvianteDynForm3*)m_pEsamiView->m_pDynForm[edt_inviante3];
			pDynForm3->UpdateData(FALSE);
		}
	}

	return UpdateData(FALSE);
}

LRESULT CInvianteDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	if (((BOOL)wParam == FALSE) && ((theApp.m_nProgramMode & ADD_RECORD_ESAMI) || (theApp.m_nProgramMode & MODIFY_RECORD_ESAMI)))
	{
		GetDlgItem(IDC_COMBO_PROVENIENZA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PROVENIENZA)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_PROVENIENZA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_PROVENIENZA)->ShowWindow(SW_HIDE);		
	}

	// cambio l'etichetta //
	SetDlgItemText(IDC_LABEL, theApp.GetMessageString(IDS_PROVENIENZA));

	GetDlgItem(IDC_COMBO_PROVENIENZA)->EnableWindow(!(BOOL)wParam);
	SendDlgItemMessage(IDC_EDIT_PROVENIENZA, EM_SETREADONLY, wParam, lParam);

	return 1;
}

LRESULT CInvianteDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlEditProvenienza.m_strRicerca = "";
	m_ctrlEditProvenienza.m_strRicercaView = "";

	return 1;
}

LRESULT CInvianteDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CInvianteDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;	

	ComponiRicercaEx(pStrWhere, m_ctrlEditProvenienza.m_strRicerca, "EEsami.IdProvenienzaNew", TRUE, TRUE);

	return 1;
}

long CInvianteDynForm::GetContenuto()
{
	return sub_inviante;
}

BOOL CInvianteDynForm::CampoObbligatorioValido()
{
	if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lIdProvenienzaNew) && m_pEsamiView->m_pEsamiSet->m_lIdProvenienzaNew > 0)
		return TRUE;

	return FALSE;
}

void CInvianteDynForm::OnEnSetfocusEditProvenienza()
{
	if (!GetDlgItem(IDC_EDIT_PROVENIENZA)->IsWindowVisible())
		GetDlgItem(IDC_COMBO_PROVENIENZA)->SetFocus();
}

void CInvianteDynForm::OnCbnSetfocusComboProvenienza()
{
	if (!GetDlgItem(IDC_EDIT_PROVENIENZA)->IsWindowVisible())
		GetDlgItem(IDC_COMBO_PROVENIENZA)->SetFocus();
}

void CInvianteDynForm::OnCbnSelchangeComboProvenienza()
{
	OnChangeProvenienza();
}

void CInvianteDynForm::OnChangeProvenienza()
{
	m_pEsamiView->UpdateData(TRUE);
	m_pEsamiView->m_pEsamiSet->m_sInvMedico = "";
	m_pEsamiView->m_pEsamiSet->m_lInviante = 0;
	m_pEsamiView->m_pEsamiSet->m_lOspedale = 0;
	m_pEsamiView->UpdateData(FALSE);

	if (m_pEsamiView->m_pDynForm[edt_inviante1] != NULL)
	{
		CInvianteDynForm1* pDynForm1 = (CInvianteDynForm1*)m_pEsamiView->m_pDynForm[edt_inviante1];
		pDynForm1->UpdateData(FALSE);
	}
	if (m_pEsamiView->m_pDynForm[edt_inviante2] != NULL)
	{
		CInvianteDynForm2* pDynForm2 = (CInvianteDynForm2*)m_pEsamiView->m_pDynForm[edt_inviante2];
		pDynForm2->UpdateData(FALSE);
	}
	if (m_pEsamiView->m_pDynForm[edt_inviante3] != NULL)
	{
		CInvianteDynForm3* pDynForm3 = (CInvianteDynForm3*)m_pEsamiView->m_pDynForm[edt_inviante3];
		pDynForm3->UpdateData(FALSE);
	}
}

BOOL CInvianteDynForm::HasValue()
{
	if ((theApp.m_nProgramMode & ADD_RECORD_ESAMI) || (theApp.m_nProgramMode & MODIFY_RECORD_ESAMI))
	{
		int selVal = m_ctrlComboProvenienza.GetItemData(m_ctrlComboProvenienza.GetCurSel());
		if (selVal < 0)
			return FALSE;
		else
			return TRUE;
	}
	else
	{
		CString txt;
		m_ctrlEditProvenienza.GetWindowText(txt);
		if (txt == "")
			return FALSE;
		else
			return TRUE;
	}
}


void CInvianteDynForm::OnEnChangeEditProvenienza()
{
	//Se siamo in ricerca devo verificare i valori per gestire i campi correlati
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		m_pEsamiView->UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_sInvMedico = "";
		m_pEsamiView->m_pEsamiSet->m_lInviante = 0;
		m_pEsamiView->m_pEsamiSet->m_lOspedale = 0;
		m_pEsamiView->UpdateData(FALSE);

		if (m_ctrlEditProvenienza.m_strRicerca != "" && m_ctrlEditProvenienza.m_strRicerca.Find("OR") < 0)
		{
			int provenienza = atoi(m_ctrlEditProvenienza.m_strRicerca);
			m_pEsamiView->m_pEsamiSet->m_lProvenienza = CProvenienzaSet().GetInternoEsterno(provenienza);

			//Se è contenuto solo un numero significa che ho fatto una sola scelta, quindi abilito nel modo corretto gli altri campi
			if (m_pEsamiView->m_pDynForm[edt_inviante1] != NULL)
			{
				CInvianteDynForm1* pDynForm1 = (CInvianteDynForm1*)m_pEsamiView->m_pDynForm[edt_inviante1];
				pDynForm1->UpdateData(FALSE);
				pDynForm1->SendMessage(MSG_FORM_READONLY, FALSE, (LPARAM)0);
			}
			if (m_pEsamiView->m_pDynForm[edt_inviante2] != NULL)
			{
				CInvianteDynForm2* pDynForm2 = (CInvianteDynForm2*)m_pEsamiView->m_pDynForm[edt_inviante2];
				pDynForm2->UpdateData(FALSE);
				pDynForm2->SendMessage(MSG_FORM_READONLY, FALSE, (LPARAM)0);
			}
			if (m_pEsamiView->m_pDynForm[edt_inviante3] != NULL)
			{
				CInvianteDynForm3* pDynForm3 = (CInvianteDynForm3*)m_pEsamiView->m_pDynForm[edt_inviante3];
				pDynForm3->UpdateData(FALSE);
				pDynForm3->SendMessage(MSG_FORM_READONLY, FALSE, (LPARAM)0);
			}
		}
		else
		{
			//altrimenti, se le scelte sono di provenienze diverse(interno/esterno), li disabilito
			if (m_ctrlEditProvenienza.m_strRicerca == "")
			{
				if (m_pEsamiView->m_pDynForm[edt_inviante1] != NULL)
				{
					CInvianteDynForm1* pDynForm1 = (CInvianteDynForm1*)m_pEsamiView->m_pDynForm[edt_inviante1];
					pDynForm1->UpdateData(FALSE);
					pDynForm1->SendMessage(MSG_FORM_READONLY, TRUE, (LPARAM)0);
				}
				if (m_pEsamiView->m_pDynForm[edt_inviante2] != NULL)
				{
					CInvianteDynForm2* pDynForm2 = (CInvianteDynForm2*)m_pEsamiView->m_pDynForm[edt_inviante2];
					pDynForm2->UpdateData(FALSE);
					pDynForm2->SendMessage(MSG_FORM_READONLY, TRUE, (LPARAM)0);
				}
				if (m_pEsamiView->m_pDynForm[edt_inviante3] != NULL)
				{
					CInvianteDynForm3* pDynForm3 = (CInvianteDynForm3*)m_pEsamiView->m_pDynForm[edt_inviante3];
					pDynForm3->UpdateData(FALSE);
					pDynForm3->SendMessage(MSG_FORM_READONLY, TRUE, (LPARAM)0);
				}
			}
			else
			{
				//Qui devo verificare le provenienze di ogni scelta per capire se sono tutte uguali
				int nTokenPos = 0;
				CString strToken = m_ctrlEditProvenienza.m_strRicerca.Tokenize("OR", nTokenPos);
				CList<int> idList;

				while (!strToken.IsEmpty())
				{
					idList.AddTail(atoi(strToken));
					strToken = m_ctrlEditProvenienza.m_strRicerca.Tokenize("OR", nTokenPos);
				}

				int countInt = 0;
				int countEst = 0;
				POSITION pos = idList.GetHeadPosition();
				while (pos)
				{
					int id = idList.GetNext(pos);

					if (CProvenienzaSet().GetInternoEsterno(id) == INTERNO)
						countInt++;
					else
						countEst++;
				}

				if (countInt > 0 && countEst > 0)
				{
					if (m_pEsamiView->m_pDynForm[edt_inviante1] != NULL)
					{
						CInvianteDynForm1* pDynForm1 = (CInvianteDynForm1*)m_pEsamiView->m_pDynForm[edt_inviante1];
						pDynForm1->SendMessage(MSG_FORM_READONLY, TRUE, (LPARAM)0);
					}
					if (m_pEsamiView->m_pDynForm[edt_inviante2] != NULL)
					{
						CInvianteDynForm2* pDynForm2 = (CInvianteDynForm2*)m_pEsamiView->m_pDynForm[edt_inviante2];
						pDynForm2->SendMessage(MSG_FORM_READONLY, TRUE, (LPARAM)0);
					}
					if (m_pEsamiView->m_pDynForm[edt_inviante3] != NULL)
					{
						CInvianteDynForm3* pDynForm3 = (CInvianteDynForm3*)m_pEsamiView->m_pDynForm[edt_inviante3];
						pDynForm3->SendMessage(MSG_FORM_READONLY, TRUE, (LPARAM)0);
					}
				}
				else
				{
					if (countInt > 0)
						m_pEsamiView->m_pEsamiSet->m_lProvenienza = INTERNO;
					else
						m_pEsamiView->m_pEsamiSet->m_lProvenienza = ESTERNO;

					if (m_pEsamiView->m_pDynForm[edt_inviante1] != NULL)
					{
						CInvianteDynForm1* pDynForm1 = (CInvianteDynForm1*)m_pEsamiView->m_pDynForm[edt_inviante1];
						pDynForm1->UpdateData(FALSE);
						pDynForm1->SendMessage(MSG_FORM_READONLY, FALSE, (LPARAM)0);
					}
					if (m_pEsamiView->m_pDynForm[edt_inviante2] != NULL)
					{
						CInvianteDynForm2* pDynForm2 = (CInvianteDynForm2*)m_pEsamiView->m_pDynForm[edt_inviante2];
						pDynForm2->UpdateData(FALSE);
						pDynForm2->SendMessage(MSG_FORM_READONLY, FALSE, (LPARAM)0);
					}
					if (m_pEsamiView->m_pDynForm[edt_inviante3] != NULL)
					{
						CInvianteDynForm3* pDynForm3 = (CInvianteDynForm3*)m_pEsamiView->m_pDynForm[edt_inviante3];
						pDynForm3->UpdateData(FALSE);
						pDynForm3->SendMessage(MSG_FORM_READONLY, FALSE, (LPARAM)0);
					}
				}
			}
		}
	}
}
