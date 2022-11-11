#include "stdafx.h"
#include "Endox.h"
#include "EtichetteNewTastiChiusuraFaseForm.h"

#include "EtichetteSet.h"
#include "FasiEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT uiTestoVecchioTastiChiusuraFaseEx[NUM_LABEL_TESTO_PAGE] = { IDC_OLD_TESTO00, IDC_OLD_TESTO01, IDC_OLD_TESTO02, IDC_OLD_TESTO03, IDC_OLD_TESTO04, IDC_OLD_TESTO05, IDC_OLD_TESTO06, IDC_OLD_TESTO07, IDC_OLD_TESTO08, IDC_OLD_TESTO09, IDC_OLD_TESTO10, IDC_OLD_TESTO11, IDC_OLD_TESTO12, IDC_OLD_TESTO13, IDC_OLD_TESTO14, IDC_OLD_TESTO15, IDC_OLD_TESTO16, IDC_OLD_TESTO17, IDC_OLD_TESTO18, IDC_OLD_TESTO19 };
UINT uiTestoNuovoTastiChiusuraFaseEx[NUM_LABEL_TESTO_PAGE] = { IDC_NEW_TESTO00, IDC_NEW_TESTO01, IDC_NEW_TESTO02, IDC_NEW_TESTO03, IDC_NEW_TESTO04, IDC_NEW_TESTO05, IDC_NEW_TESTO06, IDC_NEW_TESTO07, IDC_NEW_TESTO08, IDC_NEW_TESTO09, IDC_NEW_TESTO10, IDC_NEW_TESTO11, IDC_NEW_TESTO12, IDC_NEW_TESTO13, IDC_NEW_TESTO14, IDC_NEW_TESTO15, IDC_NEW_TESTO16, IDC_NEW_TESTO17, IDC_NEW_TESTO18, IDC_NEW_TESTO19 };

UINT uiCmbFaseEx[NUM_LABEL_TESTO_PAGE] = { IDC_CMB_00, IDC_CMB_01, IDC_CMB_02, IDC_CMB_03, IDC_CMB_04, IDC_CMB_05, IDC_CMB_06, IDC_CMB_07, IDC_CMB_08, IDC_CMB_09, IDC_CMB_10, IDC_CMB_11, IDC_CMB_12, IDC_CMB_13, IDC_CMB_14, IDC_CMB_15, IDC_CMB_16, IDC_CMB_17, IDC_CMB_18, IDC_CMB_19 };



CEtichetteNewTastiChiusuraFaseForm::CEtichetteNewTastiChiusuraFaseForm(CWnd* pParent)
	: CMyResizableDialog(CEtichetteNewTastiChiusuraFaseForm::IDD, pParent)
{
	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		m_sTesto[i] = theApp.m_sLabelTastoChiusuraFase[i];
	}

	Create(CEtichetteNewTastiChiusuraFaseForm::IDD, pParent->GetParent());

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);

}


CEtichetteNewTastiChiusuraFaseForm::~CEtichetteNewTastiChiusuraFaseForm()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

BEGIN_MESSAGE_MAP(CEtichetteNewTastiChiusuraFaseForm, CMyResizableDialog)	
END_MESSAGE_MAP()

void CEtichetteNewTastiChiusuraFaseForm::DoDataExchange(CDataExchange* pDX)
{
	CMyResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);

	//

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		if (!pDX->m_bSaveAndValidate)
		{
			DDX_Text(pDX, uiTestoVecchioTastiChiusuraFaseEx[i], theApp.m_sLabelTastoChiusuraFase[i]);
		}

		DDX_Text(pDX, uiTestoNuovoTastiChiusuraFaseEx[i], m_sTesto[i]);		
	}
}

BOOL CEtichetteNewTastiChiusuraFaseForm::OnInitDialog()
{
	CMyResizableDialog::OnInitDialog();

	//Riempio le combo con le fasi
	for (int h = 0; h < NUM_LABEL_TESTO_PAGE; h++) //Per ogni combo di questa pagina
	{
		((CComboBox*)GetDlgItem(uiCmbFaseEx[h]))->Clear(); //pulisco...
		int index = ((CComboBox*)GetDlgItem(uiCmbFaseEx[h]))->AddString(""); //Inserisco l'elemento vuoto...
		((CComboBox*)GetDlgItem(uiCmbFaseEx[h]))->SetItemData(index, 0);

		CString sFilter;
		sFilter.Format("ID > 2");
		CFasiEsameSet set;
		set.SetOpenFilter(sFilter);

		if (set.OpenRecordset("CEtichetteNewTastiChiusuraFaseForm::OnInitDialog"))
		{
			while (!set.IsEOF())
			{
				int index = ((CComboBox*)GetDlgItem(uiCmbFaseEx[h]))->AddString(set.m_sDescrizione); //Inserisco l'elemento...						
				((CComboBox*)GetDlgItem(uiCmbFaseEx[h]))->SetItemData(index, set.m_lID); //e come itemData metto il CONTATORE della fase

				if (theApp.m_lIdFaseTastoChiusuraFase[h] == set.m_lID)
				{
					((CComboBox*)GetDlgItem(uiCmbFaseEx[h]))->SetCurSel(index);
				}

				set.MoveNext();
			}

			set.CloseRecordset("CEtichetteNewTastiChiusuraFaseForm::OnInitDialog");
		}

	}

	UpdateData(FALSE);

	return TRUE;
}


void CEtichetteNewTastiChiusuraFaseForm::Savee()
{
	UpdateData(TRUE);

	///////////
	// TESTI //
	///////////

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		theApp.m_sLabelTastoChiusuraFase[i] = m_sTesto[i];

		int curSel = ((CComboBox*)GetDlgItem(uiCmbFaseEx[i]))->GetCurSel();
		theApp.m_lIdFaseTastoChiusuraFase[i] = ((CComboBox*)GetDlgItem(uiCmbFaseEx[i]))->GetItemData(curSel);
	}
}
