#include "stdafx.h"
#include "Endox.h"
#include "EndoGridDynForm.h"

#include "EndoGridChecklist.h"
#include "EsamiView.h"
#include "GruppiSet.h"

#include "DLL_Imaging\h\AmLogin.h"

#include "LockManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEndoGridDynForm::CEndoGridDynForm(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
	: CEndoxDynForm(CEndoGridDynForm::IDD, pParent, pEsamiView)
{
	m_lContenuto = lContenuto;
	m_pEndoGrid = NULL;
	m_bUserCanUseCL = FALSE;
}


CEndoGridDynForm::~CEndoGridDynForm()
{
	if (m_pEndoGrid)
	{
		delete m_pEndoGrid;
		m_pEndoGrid = NULL;
	}
}

BEGIN_MESSAGE_MAP(CEndoGridDynForm, CEndoxDynForm)
	ON_MESSAGE(XTPWM_PROPERTYGRID_NOTIFY, OnGridNotify)

	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_EDIT_1, OnBnClickedBtnEdit1)
	ON_BN_CLICKED(IDC_BTN_END_1, OnBnClickedBtnEnd1)
END_MESSAGE_MAP()

void CEndoGridDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new CEndoGridDynForm(NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(CEndoGridDynForm::IDD, pParent, rectFrame);
		}
	}

}

HBRUSH CEndoGridDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hReturn = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_1:
	{
		if (m_lColore >= 0)
			pDC->SetTextColor(theApp.m_color[m_lColore]);

		if (m_crCampoObbligatorio > 0)
		{
			pDC->SetBkColor(m_crCampoObbligatorio);
			if (m_pEndoGrid)
				m_pEndoGrid->SetRequiredFieldColor(m_crCampoObbligatorio);
		}

		break;
	}
	}

	return hReturn;
}

void CEndoGridDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_EDIT_1, m_ctrlBtnEdit);
	DDX_Control(pDX, IDC_BTN_END_1, m_ctrlBtnEnd);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);

	if (m_pEndoGrid)
		m_pEndoGrid->DoDataExchange(pDX);
}

BOOL CEndoGridDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	GetDlgItem(IDC_STATIC_1)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_2)->SetFont(&theApp.m_fontBold);

	AddAnchor(GetDlgItem(IDC_PLACE)->GetSafeHwnd(), CSize(0, 0), CSize(100, 100));

	m_pEndoGrid = new CEndoGridChecklist(m_pEsamiView, m_lContenuto - sub_gridcl000);
	m_pEndoGrid->Create(this, IDC_PLACE);

	AddAnchor(IDC_STATIC_1, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_2, CSize(0, 0), CSize(100, 0));

	AddAnchor(IDC_BTN_EDIT_1, CSize(0, 0), CSize(50, 0));
	AddAnchor(IDC_BTN_END_1, CSize(50, 0), CSize(100, 0));
	AddAnchor(m_pEndoGrid->GetDlgCtrlID(), CSize(0, 0), CSize(100, 100));

	m_ctrlStatic1.SetWindowText(theApp.m_sLabelTextGridCL[m_lContenuto - sub_gridcl000]);

	theApp.LocalizeDialog(this, CEndoGridDynForm::IDD, "EndoGridDynForm");

	return bReturn;
}

LRESULT CEndoGridDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == TRUE)
	{
		//Caso nothing_mode

		m_ctrlBtnEdit.ShowWindow(SW_SHOW);
		m_ctrlBtnEnd.ShowWindow(SW_SHOW);

		if (!m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		{
			m_ctrlBtnEdit.EnableWindow(TRUE);
			m_ctrlBtnEnd.EnableWindow(FALSE);

			//verifica utente
			if (!m_bUserCanUseCL)
			{
				m_ctrlBtnEdit.ShowWindow(SW_HIDE);
				m_ctrlBtnEnd.ShowWindow(SW_HIDE);
				m_ctrlStatic2.ShowWindow(SW_SHOW);
			}
		}
		else
		{
			m_ctrlBtnEdit.EnableWindow(FALSE);
			m_ctrlBtnEnd.EnableWindow(FALSE);
		}
	}
	else
	{
		//caso new, edit e query

		if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		{
			m_ctrlBtnEdit.ShowWindow(SW_SHOW);
			m_ctrlBtnEnd.ShowWindow(SW_SHOW);
			m_ctrlStatic2.ShowWindow(SW_HIDE);
			m_ctrlBtnEdit.EnableWindow(FALSE);
			m_ctrlBtnEnd.EnableWindow(FALSE);
			m_pEndoGrid->SetReadOnly(TRUE);
		}
		else
		{

			if (m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
			{
				m_ctrlBtnEdit.ShowWindow(SW_SHOW);
				m_ctrlBtnEnd.ShowWindow(SW_SHOW);
				m_ctrlBtnEdit.EnableWindow(FALSE);
				m_ctrlBtnEnd.EnableWindow(FALSE);
			}
			else
			{
				m_ctrlBtnEdit.ShowWindow(SW_HIDE);
				m_ctrlBtnEnd.ShowWindow(SW_HIDE);

				//verifica utente
				if (!m_bUserCanUseCL)
				{
					m_ctrlStatic2.ShowWindow(SW_SHOW);
					m_pEndoGrid->SetReadOnly(TRUE);
				}
				else
				{
					m_ctrlStatic2.ShowWindow(SW_HIDE);
					m_pEndoGrid->SetReadOnly(FALSE);
				}
			}
		}
	}

	return 1;
}

long CEndoGridDynForm::GetContenuto()
{
	return m_lContenuto;
}

BOOL CEndoGridDynForm::CampoObbligatorioValido()
{
	CObbligatoryFieldErrorList list;
	if (m_pEndoGrid->SendMessage(EPM_CHECK_OBBLIGATORY_FIELD, (WPARAM)&list))
	{
		theApp.AfxMessageBoxEndo(list.GetDescription());
		return FALSE;
	}

	return TRUE;
}

LRESULT CEndoGridDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	//Recupero la lista dei gruppi dell'utente collegato
	//	Devo utilizzare le descrizioni per gestire anche il caso LDAP, dove un utente può appartenere a più gruppi
	m_bUserCanUseCL = FALSE;

	POSITION pos = theApp.m_listUserGroups.GetHeadPosition();
	while (pos)
	{
		CString sNomeGruppo = theApp.m_listUserGroups.GetNext(pos);
		long idGruppo = CGruppiSet().GetIDFromNome(sNomeGruppo);

		//Verifico se il gruppo può modificare la checklist
		if (theApp.m_listGridCLGruppiAssociati[m_lContenuto - sub_gridcl000].Find(idGruppo) != NULL)
		{
			m_bUserCanUseCL = TRUE;
			break;
		}

	}

	m_pEndoGrid->SendMessage(EPM_EXAMCHANGED);

	return 1;
}

LRESULT CEndoGridDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	if (m_pEndoGrid->GetReadOnly())
		return 1;

	m_pEndoGrid->SetReadOnly(TRUE); //Se non la setto a read-only prima, alcuni dati tipo i double non vengono salvati
	m_pEndoGrid->SendMessage(EPM_EXAM_UPDATE);

	return 1;
}

void CEndoGridDynForm::EvidenziaCampoObbligatorioEx(COLORREF crColor)
{
	CEndoxDynForm::EvidenziaCampoObbligatorioEx(crColor);

	//Ricarico i dati per evidenziare immediatamente i campi obbligatori
	m_pEndoGrid->SendMessage(EPM_EXAMCHANGED);
}

LRESULT CEndoGridDynForm::OnGridNotify(WPARAM wParam, LPARAM lParam)
{
	//Qui ricevo i messaggi di quando la griglia viene variata. Li giro direttamente alla griglia stessa che sa come gestirli
	m_pEndoGrid->SendMessage(EPM_PROPERTYGRID_NOTIFY, wParam, lParam);
	return 0;
}

int CEndoGridDynForm::GetLines()
{
	int count = m_pEndoGrid->GetCount();
	return count;
}

CString CEndoGridDynForm::GetItemText(int row, int col)
{
	CXTPPropertyGridItem* temp = m_pEndoGrid->GetItem(row);

	if (col == 0)
	{
		CXTPMarkupUIElement* markupCaption = temp->GetMarkupCaption();
		if (markupCaption == NULL)
			return temp->GetCaption();
		else
		{
			//DA RIFARE			
			CString temps = temp->GetCaption();
			CString tempsTemp = temps;
			int occMaggiore = tempsTemp.Replace('>', '.');

			int posStart = 0;
			for (int i = 0; i < occMaggiore / 2; i++)
				posStart = temps.Find('>', posStart + 1);

			int posEnd = temps.Find('<', posStart);

			temps = temps.Mid(posStart + 1, (posEnd - posStart) - 1);
			return temps;
		}
	}
	else
		return temp->GetValue();
}

void CEndoGridDynForm::ExpandAll()
{
	m_pEndoGrid->ExpandAll();
}

BOOL CEndoGridDynForm::IsCategory(int index)
{
	return (m_pEndoGrid->GetCategories()->Find(m_pEndoGrid->GetItem(index)) >= 0);
}

double CEndoGridDynForm::GetViewDivider()
{
	return m_pEndoGrid->GetViewDivider();
}

void CEndoGridDynForm::OnBnClickedBtnEdit1()
{
	m_ctrlBtnEdit.SetCheck(BST_UNCHECKED);

	// Davide - risoluzione bug Humanitas caricamento griglie
	m_pEndoGrid->SendMessage(EPM_EXAMCHANGED);
	if (!CLockManager::Get()->LockExam(m_pEsamiView->m_pEsamiSet->m_lContatore))
		return;
	//

	m_ctrlBtnEdit.EnableWindow(FALSE);
	m_ctrlBtnEnd.EnableWindow(TRUE);
	m_pEndoGrid->SetReadOnly(FALSE);
}

void CEndoGridDynForm::OnBnClickedBtnEnd1()
{
	m_ctrlBtnEnd.SetCheck(BST_UNCHECKED);

	m_ctrlBtnEdit.EnableWindow(TRUE);
	m_ctrlBtnEnd.EnableWindow(FALSE);
	m_pEndoGrid->SetReadOnly(TRUE); //Se non la setto a read-only prima, alcuni dati tipo i double non vengono salvati

	m_pEndoGrid->SendMessage(EPM_EXAM_UPDATE);

	//Davide - risoluzione bug Humanitas caricamento griglie
	CLockManager::Get()->UnlockExam(m_pEsamiView->m_pEsamiSet->m_lContatore);
	//
}
