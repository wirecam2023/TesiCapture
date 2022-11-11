#include "stdafx.h"
#include "Endox.h"
#include "EtichetteNewTestiForm.h"

#include "EtichetteSet.h"
#include "EtichetteCondConfigDlg.h"
#include "EtichetteCondizionateConfigSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


UINT uiTestoVecchioEx[NUM_LABEL_TESTO_PAGE] = { IDC_OLD_TESTO00, IDC_OLD_TESTO01, IDC_OLD_TESTO02, IDC_OLD_TESTO03, IDC_OLD_TESTO04, IDC_OLD_TESTO05, IDC_OLD_TESTO06, IDC_OLD_TESTO07, IDC_OLD_TESTO08, IDC_OLD_TESTO09, IDC_OLD_TESTO10, IDC_OLD_TESTO11, IDC_OLD_TESTO12, IDC_OLD_TESTO13, IDC_OLD_TESTO14, IDC_OLD_TESTO15, IDC_OLD_TESTO16, IDC_OLD_TESTO17, IDC_OLD_TESTO18, IDC_OLD_TESTO19 };
UINT uiTestoNuovoEx[NUM_LABEL_TESTO_PAGE] = { IDC_NEW_TESTO00, IDC_NEW_TESTO01, IDC_NEW_TESTO02, IDC_NEW_TESTO03, IDC_NEW_TESTO04, IDC_NEW_TESTO05, IDC_NEW_TESTO06, IDC_NEW_TESTO07, IDC_NEW_TESTO08, IDC_NEW_TESTO09, IDC_NEW_TESTO10, IDC_NEW_TESTO11, IDC_NEW_TESTO12, IDC_NEW_TESTO13, IDC_NEW_TESTO14, IDC_NEW_TESTO15, IDC_NEW_TESTO16, IDC_NEW_TESTO17, IDC_NEW_TESTO18, IDC_NEW_TESTO19 };

UINT uiCopiaEx[NUM_LABEL_TESTO_PAGE] = { IDC_COPIA_00, IDC_COPIA_01, IDC_COPIA_02, IDC_COPIA_03, IDC_COPIA_04, IDC_COPIA_05, IDC_COPIA_06, IDC_COPIA_07, IDC_COPIA_08, IDC_COPIA_09, IDC_COPIA_10, IDC_COPIA_11, IDC_COPIA_12, IDC_COPIA_13, IDC_COPIA_14, IDC_COPIA_15, IDC_COPIA_16, IDC_COPIA_17, IDC_COPIA_18, IDC_COPIA_19 };
UINT uiRadioNumEx[NUM_LABEL_TESTO_PAGE] = { IDC_RADIO_NUM00, IDC_RADIO_NUM01, IDC_RADIO_NUM02, IDC_RADIO_NUM03, IDC_RADIO_NUM04, IDC_RADIO_NUM05, IDC_RADIO_NUM06, IDC_RADIO_NUM07, IDC_RADIO_NUM08, IDC_RADIO_NUM09, IDC_RADIO_NUM10, IDC_RADIO_NUM11, IDC_RADIO_NUM12, IDC_RADIO_NUM13, IDC_RADIO_NUM14, IDC_RADIO_NUM15, IDC_RADIO_NUM16, IDC_RADIO_NUM17, IDC_RADIO_NUM18, IDC_RADIO_NUM19 };
UINT uiRadioTestoEx[NUM_LABEL_TESTO_PAGE] = { IDC_RADIO_TESTO00, IDC_RADIO_TESTO01, IDC_RADIO_TESTO02, IDC_RADIO_TESTO03, IDC_RADIO_TESTO04, IDC_RADIO_TESTO05, IDC_RADIO_TESTO06, IDC_RADIO_TESTO07, IDC_RADIO_TESTO08, IDC_RADIO_TESTO09, IDC_RADIO_TESTO10, IDC_RADIO_TESTO11, IDC_RADIO_TESTO12, IDC_RADIO_TESTO13, IDC_RADIO_TESTO14, IDC_RADIO_TESTO15, IDC_RADIO_TESTO16, IDC_RADIO_TESTO17, IDC_RADIO_TESTO18, IDC_RADIO_TESTO19 };
UINT uiRadioListaEx[NUM_LABEL_TESTO_PAGE] = { IDC_RADIO_LISTA00, IDC_RADIO_LISTA01, IDC_RADIO_LISTA02, IDC_RADIO_LISTA03, IDC_RADIO_LISTA04, IDC_RADIO_LISTA05, IDC_RADIO_LISTA06, IDC_RADIO_LISTA07, IDC_RADIO_LISTA08, IDC_RADIO_LISTA09, IDC_RADIO_LISTA10, IDC_RADIO_LISTA11, IDC_RADIO_LISTA12, IDC_RADIO_LISTA13, IDC_RADIO_LISTA14, IDC_RADIO_LISTA15, IDC_RADIO_LISTA16, IDC_RADIO_LISTA17, IDC_RADIO_LISTA18, IDC_RADIO_LISTA19 };
UINT uiSelezioneMultiplaEx[NUM_LABEL_TESTO_PAGE] = { IDC_MULTIPLESEL00, IDC_MULTIPLESEL01, IDC_MULTIPLESEL02, IDC_MULTIPLESEL03, IDC_MULTIPLESEL04, IDC_MULTIPLESEL05, IDC_MULTIPLESEL06, IDC_MULTIPLESEL07, IDC_MULTIPLESEL08, IDC_MULTIPLESEL09, IDC_MULTIPLESEL10, IDC_MULTIPLESEL11, IDC_MULTIPLESEL12, IDC_MULTIPLESEL13, IDC_MULTIPLESEL14, IDC_MULTIPLESEL15, IDC_MULTIPLESEL16, IDC_MULTIPLESEL17, IDC_MULTIPLESEL18, IDC_MULTIPLESEL19 };
UINT uiMaiuscoloEx[NUM_LABEL_TESTO_PAGE] = { IDC_UPPERCASE00, IDC_UPPERCASE01, IDC_UPPERCASE02, IDC_UPPERCASE03, IDC_UPPERCASE04, IDC_UPPERCASE05, IDC_UPPERCASE06, IDC_UPPERCASE07, IDC_UPPERCASE08, IDC_UPPERCASE09, IDC_UPPERCASE10, IDC_UPPERCASE11, IDC_UPPERCASE12, IDC_UPPERCASE13, IDC_UPPERCASE14, IDC_UPPERCASE15, IDC_UPPERCASE16, IDC_UPPERCASE17, IDC_UPPERCASE18, IDC_UPPERCASE19 };
UINT uiLineaSingolaEx[NUM_LABEL_TESTO_PAGE] = { IDC_SINGLELINE00, IDC_SINGLELINE01, IDC_SINGLELINE02, IDC_SINGLELINE03, IDC_SINGLELINE04, IDC_SINGLELINE05, IDC_SINGLELINE06, IDC_SINGLELINE07, IDC_SINGLELINE08, IDC_SINGLELINE09, IDC_SINGLELINE10, IDC_SINGLELINE11, IDC_SINGLELINE12, IDC_SINGLELINE13, IDC_SINGLELINE14, IDC_SINGLELINE15, IDC_SINGLELINE16, IDC_SINGLELINE17, IDC_SINGLELINE18, IDC_SINGLELINE19 };
UINT uiCmbCondEx[NUM_LABEL_TESTO_PAGE] = { IDC_CMB_COND_00, IDC_CMB_COND_01, IDC_CMB_COND_02, IDC_CMB_COND_03, IDC_CMB_COND_04, IDC_CMB_COND_05, IDC_CMB_COND_06, IDC_CMB_COND_07, IDC_CMB_COND_08, IDC_CMB_COND_09, IDC_CMB_COND_10, IDC_CMB_COND_11, IDC_CMB_COND_12, IDC_CMB_COND_13, IDC_CMB_COND_14, IDC_CMB_COND_15, IDC_CMB_COND_16, IDC_CMB_COND_17, IDC_CMB_COND_18, IDC_CMB_COND_19 };
UINT uiBtnCondConfEx[NUM_LABEL_TESTO_PAGE] = { IDC_BTN_COND_CONF_00, IDC_BTN_COND_CONF_01, IDC_BTN_COND_CONF_02, IDC_BTN_COND_CONF_03, IDC_BTN_COND_CONF_04, IDC_BTN_COND_CONF_05, IDC_BTN_COND_CONF_06, IDC_BTN_COND_CONF_07, IDC_BTN_COND_CONF_08, IDC_BTN_COND_CONF_09, IDC_BTN_COND_CONF_10, IDC_BTN_COND_CONF_11, IDC_BTN_COND_CONF_12, IDC_BTN_COND_CONF_13, IDC_BTN_COND_CONF_14, IDC_BTN_COND_CONF_15, IDC_BTN_COND_CONF_16, IDC_BTN_COND_CONF_17, IDC_BTN_COND_CONF_18, IDC_BTN_COND_CONF_19 };

CEtichetteNewTestiForm::CEtichetteNewTestiForm(CWnd* pParent, int index)
	: CMyResizableDialog(CEtichetteNewTestiForm::IDD, pParent)
{
	m_iIndex = index;	

	///////////
	// TESTI //
	///////////

	int iPage = m_iIndex * NUM_LABEL_TESTO_PAGE;

	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		m_sTesto[i] = theApp.m_sLabelText[i + iPage];
		m_bCopia[i] = theApp.m_bCopy[i + iPage];

		if (theApp.m_bComboActive[i + iPage])
			m_iRadio[i] = 2; // lista //
		else if (theApp.m_bComboNumerico[i + iPage])
			m_iRadio[i] = 0; // numerico //
		else
			m_iRadio[i] = 1; // scrittura libera //

		m_bSelezioneMultipla[i] = theApp.m_bComboMultipleSel[i + iPage];
		m_bMaiuscolo[i] = theApp.m_bComboUppercase[i + iPage];
		m_bLineaSingola[i] = theApp.m_bComboSingleLine[i + iPage];
		m_lSelectedCondIndex[i] = 0;
	}	

	Create(CEtichetteNewTestiForm::IDD, pParent->GetParent());

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);		

}


CEtichetteNewTestiForm::~CEtichetteNewTestiForm()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

BEGIN_MESSAGE_MAP(CEtichetteNewTestiForm, CMyResizableDialog)

	ON_BN_CLICKED(IDC_RADIO_NUM00, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM01, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM02, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM03, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM04, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM05, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM06, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM07, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM08, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM09, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM10, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM11, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM12, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM13, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM14, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM15, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM16, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM17, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM18, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_NUM19, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO00, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO01, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO02, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO03, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO04, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO05, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO06, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO07, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO08, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO09, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO10, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO11, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO12, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO13, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO14, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO15, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO16, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO17, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO18, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_TESTO19, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA00, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA01, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA02, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA03, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA04, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA05, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA06, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA07, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA08, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA09, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA10, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA11, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA12, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA13, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA14, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA15, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA16, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA17, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA18, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_LISTA19, OnBnClickedRadio)

	ON_BN_CLICKED(IDC_MULTIPLESEL00, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL01, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL02, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL03, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL04, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL05, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL06, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL07, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL08, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL09, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL10, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL11, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL12, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL13, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL14, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL15, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL16, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL17, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL18, OnBnClickedMultiplesel)
	ON_BN_CLICKED(IDC_MULTIPLESEL19, OnBnClickedMultiplesel)

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

void CEtichetteNewTestiForm::DoDataExchange(CDataExchange* pDX)
{
	CMyResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_06, m_ctrlStatic06);
	DDX_Control(pDX, IDC_STATIC_07, m_ctrlStatic07);

	//

	int iPage = m_iIndex * NUM_LABEL_TESTO_PAGE;
	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		if (!pDX->m_bSaveAndValidate)
		{
			switch (m_iRadio[i])
			{
			case 0: // numerico //
			{
				m_bSelezioneMultipla[i] = FALSE;
				m_bMaiuscolo[i] = FALSE;
				m_bLineaSingola[i] = TRUE;

				GetDlgItem(uiSelezioneMultiplaEx[i])->EnableWindow(FALSE);
				GetDlgItem(uiMaiuscoloEx[i])->EnableWindow(FALSE);
				GetDlgItem(uiLineaSingolaEx[i])->EnableWindow(FALSE);

				break;
			}
			case 1: // scrittura libera //
			{
				m_bSelezioneMultipla[i] = FALSE;

				GetDlgItem(uiSelezioneMultiplaEx[i])->EnableWindow(FALSE);
				GetDlgItem(uiMaiuscoloEx[i])->EnableWindow(TRUE);
				GetDlgItem(uiLineaSingolaEx[i])->EnableWindow(TRUE);

				GetDlgItem(uiCmbCondEx[i])->EnableWindow(TRUE);
				GetDlgItem(uiBtnCondConfEx[i])->EnableWindow(TRUE);

				break;
			}
			case 2: // lista //
			{
				GetDlgItem(uiSelezioneMultiplaEx[i])->EnableWindow(TRUE);
				GetDlgItem(uiMaiuscoloEx[i])->EnableWindow(TRUE);
				GetDlgItem(uiLineaSingolaEx[i])->EnableWindow(TRUE);

				break;
			}
			}

			DDX_Text(pDX, uiTestoVecchioEx[i], theApp.m_sLabelText[i + iPage]);
		}

		DDX_Text(pDX, uiTestoNuovoEx[i], m_sTesto[i]);
		DDX_Check(pDX, uiCopiaEx[i], m_bCopia[i]);
		DDX_Radio(pDX, uiRadioNumEx[i], m_iRadio[i]);
		DDX_Check(pDX, uiSelezioneMultiplaEx[i], m_bSelezioneMultipla[i]);
		DDX_Check(pDX, uiMaiuscoloEx[i], m_bMaiuscolo[i]);
		DDX_Check(pDX, uiLineaSingolaEx[i], m_bLineaSingola[i]);		

		//I cambi condizionati vengono disabilitati in selezione multipla
		GetDlgItem(uiCmbCondEx[i])->EnableWindow(m_iRadio[i] != 2 || (m_iRadio[i] == 2 && !m_bSelezioneMultipla[i]));		
		int curSel = ((CComboBox*)GetDlgItem(uiCmbCondEx[i]))->GetCurSel();
		int itemData = ((CComboBox*)GetDlgItem(uiCmbCondEx[i]))->GetItemData(curSel);
		GetDlgItem(uiBtnCondConfEx[i])->EnableWindow(itemData > 0); //Abilito il tasto di config solo se ho selezionato un elemento relazionato valido
	}
}

BOOL CEtichetteNewTestiForm::OnInitDialog()
{
	CMyResizableDialog::OnInitDialog();	

	long idCampoArray[NUM_LABEL_TESTO];
	for (int i = 0; i < NUM_LABEL_TESTO; i++)
		idCampoArray[i] = CEtichetteSet().GetId("TESTO", i);

	//Riempio le combo con i testi che sono combo a scelta singola
	int iPage = m_iIndex * NUM_LABEL_TESTO_PAGE;
	for (int h = 0; h < NUM_LABEL_TESTO_PAGE; h++) //Per ogni combo di questa pagina
	{
		((CComboBox*)GetDlgItem(uiCmbCondEx[h]))->Clear(); //pulisco...
		int index = ((CComboBox*)GetDlgItem(uiCmbCondEx[h]))->AddString(""); //Inserisco l'elemento vuoto...
		((CComboBox*)GetDlgItem(uiCmbCondEx[h]))->SetItemData(index, -1);

		if (m_iRadio[h] != 2 || (m_iRadio[h] == 2 && !m_bSelezioneMultipla[h])) //se il campo di destinazione può accettare un condizionamento...
		{
			for (int i = 0; i < NUM_LABEL_TESTO; i++) //mi passo tutti i campi personalizzabili testo
			{
				if (theApp.m_bComboActive[i] && !theApp.m_bComboMultipleSel[i] && !theApp.m_sLabelText[i].IsEmpty() && (h + iPage) != i) //se sono di tipo combo a scelta singola e gli si è dato un nome (e non è lo stesso testo libero) ...
				{
					int index = ((CComboBox*)GetDlgItem(uiCmbCondEx[h]))->AddString(theApp.m_sLabelText[i]); //Inserisco l'elemento...							
					((CComboBox*)GetDlgItem(uiCmbCondEx[h]))->SetItemData(index, idCampoArray[i]); //e come itemData metto il CONTATORE del relativo elemento di EETICHETTE										

					if (theApp.m_lIdCampoRelazionato[h] == idCampoArray[i])
					{
						((CComboBox*)GetDlgItem(uiCmbCondEx[h]))->SetCurSel(index);
						m_lSelectedCondIndex[h] = index;
					}
				}				
			}
		}		
	}

	UpdateData(FALSE);

	return TRUE;
}


void CEtichetteNewTestiForm::Savee()
{
	UpdateData(TRUE);

	///////////
	// TESTI //
	///////////

	int iPage = m_iIndex * NUM_LABEL_TESTO_PAGE;
	for (int i = 0; i < NUM_LABEL_TESTO_PAGE; i++)
	{
		theApp.m_sLabelText[i + iPage] = m_sTesto[i];
		theApp.m_bCopy[i + iPage] = m_bCopia[i];
		int curSel = ((CComboBox*)GetDlgItem(uiCmbCondEx[i]))->GetCurSel();
		theApp.m_lIdCampoRelazionato[i + iPage] = ((CComboBox*)GetDlgItem(uiCmbCondEx[i]))->GetItemData(curSel);

		switch (m_iRadio[i])
		{
		case 0: // numerico //
		{
			theApp.m_bComboNumerico[i + iPage] = TRUE;
			theApp.m_bComboActive[i + iPage] = FALSE;
			theApp.m_bComboMultipleSel[i + iPage] = FALSE;
			theApp.m_bComboUppercase[i + iPage] = FALSE;
			theApp.m_bComboSingleLine[i + iPage] = TRUE;

			break;
		}
		case 1: // scrittura libera //
		{
			theApp.m_bComboNumerico[i + iPage] = FALSE;
			theApp.m_bComboActive[i + iPage] = FALSE;
			theApp.m_bComboMultipleSel[i + iPage] = FALSE;
			theApp.m_bComboUppercase[i + iPage] = m_bMaiuscolo[i];
			theApp.m_bComboSingleLine[i + iPage] = m_bLineaSingola[i];

			break;
		}
		case 2: // lista //
		{
			theApp.m_bComboNumerico[i + iPage] = FALSE;
			theApp.m_bComboActive[i + iPage] = TRUE;
			theApp.m_bComboMultipleSel[i + iPage] = m_bSelezioneMultipla[i];
			theApp.m_bComboUppercase[i + iPage] = m_bMaiuscolo[i];
			theApp.m_bComboSingleLine[i + iPage] = m_bLineaSingola[i];

			break;
		}
		}
	}
}

void CEtichetteNewTestiForm::OnBnClickedRadio()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}



void CEtichetteNewTestiForm::OnBnClickedMultiplesel()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond00()
{
	ManageCombo(0);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond01()
{
	ManageCombo(1);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond02()
{
	ManageCombo(2);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond03()
{
	ManageCombo(3);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond04()
{
	ManageCombo(4);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond05()
{
	ManageCombo(5);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond06()
{
	ManageCombo(6);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond07()
{
	ManageCombo(7);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond08()
{
	ManageCombo(8);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond09()
{
	ManageCombo(9);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond10()
{
	ManageCombo(10);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond11()
{
	ManageCombo(11);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond12()
{
	ManageCombo(12);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond13()
{
	ManageCombo(13);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond14()
{
	ManageCombo(14);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond15()
{
	ManageCombo(15);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond16()
{
	ManageCombo(16);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond17()
{
	ManageCombo(17);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond18()
{
	ManageCombo(18);
}

void CEtichetteNewTestiForm::OnCbnSelchangeCmbCond19()
{
	ManageCombo(19);
}

void CEtichetteNewTestiForm::OnBnClickedBtnCondConf00()
{	
	ApriConfigurazioneCampoCondizionato(0);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf01()
{
	ApriConfigurazioneCampoCondizionato(1);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf02()
{
	ApriConfigurazioneCampoCondizionato(2);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf03()
{
	ApriConfigurazioneCampoCondizionato(3);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf04()
{
	ApriConfigurazioneCampoCondizionato(4);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf05()
{
	ApriConfigurazioneCampoCondizionato(5);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf06()
{
	ApriConfigurazioneCampoCondizionato(6);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf07()
{
	ApriConfigurazioneCampoCondizionato(7);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf08()
{
	ApriConfigurazioneCampoCondizionato(8);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf09()
{
	ApriConfigurazioneCampoCondizionato(9);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf10()
{
	ApriConfigurazioneCampoCondizionato(10);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf11()
{
	ApriConfigurazioneCampoCondizionato(11);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf12()
{
	ApriConfigurazioneCampoCondizionato(12);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf13()
{
	ApriConfigurazioneCampoCondizionato(13);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf14()
{
	ApriConfigurazioneCampoCondizionato(14);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf15()
{
	ApriConfigurazioneCampoCondizionato(15);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf16()
{
	ApriConfigurazioneCampoCondizionato(16);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf17()
{
	ApriConfigurazioneCampoCondizionato(17);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf18()
{
	ApriConfigurazioneCampoCondizionato(18);
}


void CEtichetteNewTestiForm::OnBnClickedBtnCondConf19()
{
	ApriConfigurazioneCampoCondizionato(19);
}

void CEtichetteNewTestiForm::ApriConfigurazioneCampoCondizionato(int index)
{
	int iPage = m_iIndex * NUM_LABEL_TESTO_PAGE;

	//get id del record
	long idCondizionato = CEtichetteSet().GetId("TESTO", index + iPage);

	//get tipo del record
	CEtichetteCondConfigDlg::conditionalType tipoCondizionato;
	if (m_iRadio[index] == 0)
		tipoCondizionato = CEtichetteCondConfigDlg::conditionalType::numeric;
	else if (m_iRadio[index] == 1)
		tipoCondizionato = CEtichetteCondConfigDlg::conditionalType::text;
	else if (m_iRadio[index] == 2 && !m_bSelezioneMultipla[index])
		tipoCondizionato = CEtichetteCondConfigDlg::conditionalType::combo;

	//get id del record relazionato
	int curSel = ((CComboBox*)GetDlgItem(uiCmbCondEx[index]))->GetCurSel();
	long idRelazionato = ((CComboBox*)GetDlgItem(uiCmbCondEx[index]))->GetItemData(curSel);

	CEtichetteCondConfigDlg dlg(this, idCondizionato, idRelazionato, tipoCondizionato);
	dlg.DoModal();
}

void CEtichetteNewTestiForm::ManageCombo(int index)
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ETICHETTE_MESSAGE1), MB_YESNO) == IDNO)
	{
		((CComboBox*)GetDlgItem(uiCmbCondEx[index]))->SetCurSel(m_lSelectedCondIndex[index]);
		return;
	}

	//Cancello i record esistenti
	CString sFilter;
	sFilter.Format("IDCAMPOCONDIZIONATO=%li", CEtichetteSet().GetId("TESTO", index));
	CEtichetteCondizionateConfigSet set;
	set.SetOpenFilter(sFilter);
	if (set.OpenRecordset("CEtichetteNewTestiForm::ManageCombo"))
	{
		while (!set.IsEOF())
		{
			set.DeleteRecordset("CEtichetteNewTestiForm::ManageCombo");

			set.MoveNext();
		}

		set.CloseRecordset("CEtichetteNewTestiForm::ManageCombo");
	}

	m_lSelectedCondIndex[index] = ((CComboBox*)GetDlgItem(uiCmbCondEx[index]))->GetCurSel();

	UpdateData(TRUE);
	UpdateData(FALSE);
}