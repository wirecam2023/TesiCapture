#include "stdafx.h"
#include "Endox.h"
#include "EtichetteNewRTFForm.h"

#include "EtichetteSet.h"
#include "EtichetteCondConfigDlg.h"
#include "EtichetteCondizionateConfigSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT uiTestoVecchioRtfEx[NUM_LABEL_TESTO_PAGE] = { IDC_OLD_TESTO00, IDC_OLD_TESTO01, IDC_OLD_TESTO02, IDC_OLD_TESTO03, IDC_OLD_TESTO04, IDC_OLD_TESTO05, IDC_OLD_TESTO06, IDC_OLD_TESTO07, IDC_OLD_TESTO08, IDC_OLD_TESTO09, IDC_OLD_TESTO10, IDC_OLD_TESTO11, IDC_OLD_TESTO12, IDC_OLD_TESTO13, IDC_OLD_TESTO14, IDC_OLD_TESTO15, IDC_OLD_TESTO16, IDC_OLD_TESTO17, IDC_OLD_TESTO18, IDC_OLD_TESTO19 };
UINT uiTestoNuovoRtfEx[NUM_LABEL_TESTO_PAGE] = { IDC_NEW_TESTO00, IDC_NEW_TESTO01, IDC_NEW_TESTO02, IDC_NEW_TESTO03, IDC_NEW_TESTO04, IDC_NEW_TESTO05, IDC_NEW_TESTO06, IDC_NEW_TESTO07, IDC_NEW_TESTO08, IDC_NEW_TESTO09, IDC_NEW_TESTO10, IDC_NEW_TESTO11, IDC_NEW_TESTO12, IDC_NEW_TESTO13, IDC_NEW_TESTO14, IDC_NEW_TESTO15, IDC_NEW_TESTO16, IDC_NEW_TESTO17, IDC_NEW_TESTO18, IDC_NEW_TESTO19 };

UINT uiCopiaRtfEx[NUM_LABEL_TESTO_PAGE] = { IDC_COPIA_00, IDC_COPIA_01, IDC_COPIA_02, IDC_COPIA_03, IDC_COPIA_04, IDC_COPIA_05, IDC_COPIA_06, IDC_COPIA_07, IDC_COPIA_08, IDC_COPIA_09, IDC_COPIA_10, IDC_COPIA_11, IDC_COPIA_12, IDC_COPIA_13, IDC_COPIA_14, IDC_COPIA_15, IDC_COPIA_16, IDC_COPIA_17, IDC_COPIA_18, IDC_COPIA_19 };
UINT uiCmbCondRtfEx[NUM_LABEL_TESTO_PAGE] = { IDC_CMB_COND_00, IDC_CMB_COND_01, IDC_CMB_COND_02, IDC_CMB_COND_03, IDC_CMB_COND_04, IDC_CMB_COND_05, IDC_CMB_COND_06, IDC_CMB_COND_07, IDC_CMB_COND_08, IDC_CMB_COND_09, IDC_CMB_COND_10, IDC_CMB_COND_11, IDC_CMB_COND_12, IDC_CMB_COND_13, IDC_CMB_COND_14, IDC_CMB_COND_15, IDC_CMB_COND_16, IDC_CMB_COND_17, IDC_CMB_COND_18, IDC_CMB_COND_19 };
UINT uiBtnCondConfRtfEx[NUM_LABEL_TESTO_PAGE] = { IDC_BTN_COND_CONF_00, IDC_BTN_COND_CONF_01, IDC_BTN_COND_CONF_02, IDC_BTN_COND_CONF_03, IDC_BTN_COND_CONF_04, IDC_BTN_COND_CONF_05, IDC_BTN_COND_CONF_06, IDC_BTN_COND_CONF_07, IDC_BTN_COND_CONF_08, IDC_BTN_COND_CONF_09, IDC_BTN_COND_CONF_10, IDC_BTN_COND_CONF_11, IDC_BTN_COND_CONF_12, IDC_BTN_COND_CONF_13, IDC_BTN_COND_CONF_14, IDC_BTN_COND_CONF_15, IDC_BTN_COND_CONF_16, IDC_BTN_COND_CONF_17, IDC_BTN_COND_CONF_18, IDC_BTN_COND_CONF_19 };



CEtichetteNewRTFForm::CEtichetteNewRTFForm(CWnd* pParent)
	: CMyResizableDialog(CEtichetteNewRTFForm::IDD, pParent)
{
	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		m_sTesto[i] = theApp.m_sLabelTextRtf[i];
		m_bCopia[i] = theApp.m_bCopyRtf[i];
		m_lSelectedCondIndex[i] = 0;
	}	
	
	Create(CEtichetteNewRTFForm::IDD, pParent->GetParent());

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);

}


CEtichetteNewRTFForm::~CEtichetteNewRTFForm()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

BEGIN_MESSAGE_MAP(CEtichetteNewRTFForm, CMyResizableDialog)
	ON_CBN_SELCHANGE(IDC_CMB_COND_00, OnCbnSelchangeCmbCond00)
	ON_CBN_SELCHANGE(IDC_CMB_COND_01, OnCbnSelchangeCmbCond01)
	ON_CBN_SELCHANGE(IDC_CMB_COND_02, OnCbnSelchangeCmbCond02)
	ON_CBN_SELCHANGE(IDC_CMB_COND_03, OnCbnSelchangeCmbCond03)
	ON_CBN_SELCHANGE(IDC_CMB_COND_04, OnCbnSelchangeCmbCond04)
	ON_CBN_SELCHANGE(IDC_CMB_COND_05, OnCbnSelchangeCmbCond05)
	ON_CBN_SELCHANGE(IDC_CMB_COND_06, OnCbnSelchangeCmbCond06)
	ON_CBN_SELCHANGE(IDC_CMB_COND_07, OnCbnSelchangeCmbCond07)
	ON_CBN_SELCHANGE(IDC_CMB_COND_08, OnCbnSelchangeCmbCond08)
	ON_CBN_SELCHANGE(IDC_CMB_COND_09, OnCbnSelchangeCmbCond09)
	ON_CBN_SELCHANGE(IDC_CMB_COND_10, OnCbnSelchangeCmbCond10)
	ON_CBN_SELCHANGE(IDC_CMB_COND_11, OnCbnSelchangeCmbCond11)
	ON_CBN_SELCHANGE(IDC_CMB_COND_12, OnCbnSelchangeCmbCond12)
	ON_CBN_SELCHANGE(IDC_CMB_COND_13, OnCbnSelchangeCmbCond13)
	ON_CBN_SELCHANGE(IDC_CMB_COND_14, OnCbnSelchangeCmbCond14)
	ON_CBN_SELCHANGE(IDC_CMB_COND_15, OnCbnSelchangeCmbCond15)
	ON_CBN_SELCHANGE(IDC_CMB_COND_16, OnCbnSelchangeCmbCond16)
	ON_CBN_SELCHANGE(IDC_CMB_COND_17, OnCbnSelchangeCmbCond17)
	ON_CBN_SELCHANGE(IDC_CMB_COND_18, OnCbnSelchangeCmbCond18)
	ON_CBN_SELCHANGE(IDC_CMB_COND_19, OnCbnSelchangeCmbCond19)

	ON_BN_CLICKED(IDC_BTN_COND_CONF_00, OnBnClickedBtnCondConf00)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_01, OnBnClickedBtnCondConf01)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_02, OnBnClickedBtnCondConf02)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_03, OnBnClickedBtnCondConf03)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_04, OnBnClickedBtnCondConf04)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_05, OnBnClickedBtnCondConf05)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_06, OnBnClickedBtnCondConf06)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_07, OnBnClickedBtnCondConf07)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_08, OnBnClickedBtnCondConf08)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_09, OnBnClickedBtnCondConf09)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_10, OnBnClickedBtnCondConf10)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_11, OnBnClickedBtnCondConf11)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_12, OnBnClickedBtnCondConf12)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_13, OnBnClickedBtnCondConf13)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_14, OnBnClickedBtnCondConf14)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_15, OnBnClickedBtnCondConf15)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_16, OnBnClickedBtnCondConf16)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_17, OnBnClickedBtnCondConf17)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_18, OnBnClickedBtnCondConf18)
	ON_BN_CLICKED(IDC_BTN_COND_CONF_19, OnBnClickedBtnCondConf19)
END_MESSAGE_MAP()

void CEtichetteNewRTFForm::DoDataExchange(CDataExchange* pDX)
{
	CMyResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);

	//

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		if (!pDX->m_bSaveAndValidate)
		{
			DDX_Text(pDX, uiTestoVecchioRtfEx[i], theApp.m_sLabelTextRtf[i]);
		}

		DDX_Text(pDX, uiTestoNuovoRtfEx[i], m_sTesto[i]);
		DDX_Check(pDX, uiCopiaRtfEx[i], m_bCopia[i]);

		//I cambi condizionati vengono disabilitati in selezione multipla		
		int curSel = ((CComboBox*)GetDlgItem(uiCmbCondRtfEx[i]))->GetCurSel();
		int itemData = ((CComboBox*)GetDlgItem(uiCmbCondRtfEx[i]))->GetItemData(curSel);
		GetDlgItem(uiBtnCondConfRtfEx[i])->EnableWindow(itemData > 0); //Abilito il tasto di config solo se ho selezionato un elemento relazionato valido
	}
}

BOOL CEtichetteNewRTFForm::OnInitDialog()
{
	CMyResizableDialog::OnInitDialog();

	//Carico gli id per non fare la query 1000 volte
	long idCampoArray[NUM_LABEL_TESTO];
	for (int i = 0; i < NUM_LABEL_TESTO; i++)
		idCampoArray[i] = CEtichetteSet().GetId("TESTO", i);

	//Riempio le combo con i testi che sono combo a scelta singola
	for (int h = 0; h < NUM_LABEL_TESTO_PAGE; h++) //Per ogni combo di questa pagina
	{
		((CComboBox*)GetDlgItem(uiCmbCondRtfEx[h]))->Clear(); //pulisco...
		int index = ((CComboBox*)GetDlgItem(uiCmbCondRtfEx[h]))->AddString(""); //Inserisco l'elemento vuoto...
		((CComboBox*)GetDlgItem(uiCmbCondRtfEx[h]))->SetItemData(index, -1);

		for (int i = 0; i < NUM_LABEL_TESTO; i++) //mi passo tutti i campi personalizzabili testo
		{
			if (theApp.m_bComboActive[i] && !theApp.m_bComboMultipleSel[i] && !theApp.m_sLabelText[i].IsEmpty()) //se sono di tipo combo a scelta singola e gli si è dato un nome...
			{
				int index = ((CComboBox*)GetDlgItem(uiCmbCondRtfEx[h]))->AddString(theApp.m_sLabelText[i]); //Inserisco l'elemento...						
				((CComboBox*)GetDlgItem(uiCmbCondRtfEx[h]))->SetItemData(index, idCampoArray[i]); //e come itemData metto il CONTATORE del relativo elemento di EETICHETTE				

				if (theApp.m_lIdCampoRelazionatoRtf[h] == idCampoArray[i])
				{
					((CComboBox*)GetDlgItem(uiCmbCondRtfEx[h]))->SetCurSel(index);
					m_lSelectedCondIndex[h] = index;
				}
			}			
		}
	}

	UpdateData(FALSE);

	return TRUE;
}


void CEtichetteNewRTFForm::Savee()
{
	UpdateData(TRUE);

	///////////
	// TESTI //
	///////////

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		theApp.m_sLabelTextRtf[i] = m_sTesto[i];
		theApp.m_bCopyRtf[i] = m_bCopia[i];

		int curSel = ((CComboBox*)GetDlgItem(uiCmbCondRtfEx[i]))->GetCurSel();
		theApp.m_lIdCampoRelazionatoRtf[i] = ((CComboBox*)GetDlgItem(uiCmbCondRtfEx[i]))->GetItemData(curSel);
	}
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond00()
{
	ManageCombo(0);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond01()
{
	ManageCombo(1);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond02()
{
	ManageCombo(2);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond03()
{
	ManageCombo(3);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond04()
{
	ManageCombo(4);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond05()
{
	ManageCombo(5);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond06()
{
	ManageCombo(6);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond07()
{
	ManageCombo(7);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond08()
{
	ManageCombo(8);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond09()
{
	ManageCombo(9);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond10()
{
	ManageCombo(10);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond11()
{
	ManageCombo(11);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond12()
{
	ManageCombo(12);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond13()
{
	ManageCombo(13);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond14()
{
	ManageCombo(14);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond15()
{
	ManageCombo(15);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond16()
{
	ManageCombo(16);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond17()
{
	ManageCombo(17);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond18()
{
	ManageCombo(18);
}

void CEtichetteNewRTFForm::OnCbnSelchangeCmbCond19()
{
	ManageCombo(19);
}

void CEtichetteNewRTFForm::OnBnClickedBtnCondConf00()
{
	ApriConfigurazioneCampoCondizionato(0);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf01()
{
	ApriConfigurazioneCampoCondizionato(1);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf02()
{
	ApriConfigurazioneCampoCondizionato(2);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf03()
{
	ApriConfigurazioneCampoCondizionato(3);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf04()
{
	ApriConfigurazioneCampoCondizionato(4);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf05()
{
	ApriConfigurazioneCampoCondizionato(5);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf06()
{
	ApriConfigurazioneCampoCondizionato(6);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf07()
{
	ApriConfigurazioneCampoCondizionato(7);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf08()
{
	ApriConfigurazioneCampoCondizionato(8);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf09()
{
	ApriConfigurazioneCampoCondizionato(9);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf10()
{
	ApriConfigurazioneCampoCondizionato(10);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf11()
{
	ApriConfigurazioneCampoCondizionato(11);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf12()
{
	ApriConfigurazioneCampoCondizionato(12);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf13()
{
	ApriConfigurazioneCampoCondizionato(13);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf14()
{
	ApriConfigurazioneCampoCondizionato(14);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf15()
{
	ApriConfigurazioneCampoCondizionato(15);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf16()
{
	ApriConfigurazioneCampoCondizionato(16);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf17()
{
	ApriConfigurazioneCampoCondizionato(17);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf18()
{
	ApriConfigurazioneCampoCondizionato(18);
}


void CEtichetteNewRTFForm::OnBnClickedBtnCondConf19()
{
	ApriConfigurazioneCampoCondizionato(19);
}

void CEtichetteNewRTFForm::ApriConfigurazioneCampoCondizionato(int index)
{
	//get id del record
	long idCondizionato = CEtichetteSet().GetId("TESTO_RTF", index);

	//get id del record relazionato
	int curSel = ((CComboBox*)GetDlgItem(uiCmbCondRtfEx[index]))->GetCurSel();
	long idRelazionato = ((CComboBox*)GetDlgItem(uiCmbCondRtfEx[index]))->GetItemData(curSel);

	CEtichetteCondConfigDlg dlg(this, idCondizionato, idRelazionato, CEtichetteCondConfigDlg::conditionalType::text);
	dlg.DoModal();
}

void CEtichetteNewRTFForm::ManageCombo(int index)
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ETICHETTE_MESSAGE1), MB_YESNO) == IDNO)
	{
		((CComboBox*)GetDlgItem(uiCmbCondRtfEx[index]))->SetCurSel(m_lSelectedCondIndex[index]);
		return;
	}

	//Cancello i record esistenti
	CString sFilter;
	sFilter.Format("IDCAMPOCONDIZIONATO=%li", CEtichetteSet().GetId("TESTO_RTF", index));
	CEtichetteCondizionateConfigSet set;
	set.SetOpenFilter(sFilter);
	if (set.OpenRecordset("CEtichetteNewRTFForm::ManageCombo"))
	{
		while (!set.IsEOF())
		{
			set.DeleteRecordset("CEtichetteNewRTFForm::ManageCombo");

			set.MoveNext();
		}

		set.CloseRecordset("CEtichetteNewRTFForm::ManageCombo");
	}

	m_lSelectedCondIndex[index] = ((CComboBox*)GetDlgItem(uiCmbCondRtfEx[index]))->GetCurSel();

	UpdateData(TRUE);
	UpdateData(FALSE);
}