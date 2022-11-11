#include "stdafx.h"
#include "Endox.h"
#include "OperatoriDlg.h"

#include <GdiPlus.h>

#include "DLL_Imaging\h\AMBase64.h"

#include "ComboDynForm.h" // Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
#include "CustomDate.h"
#include "EsamiView.h"
#include "MediciSet.h"
#include "MediciSediEsameSet.h"
#include "SediEsameSet.h"
#include "VistaUtentiSet.h"

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COperatoriDlg::COperatoriDlg(CEsamiView* pEsamiView, BOOL bMenu, long p_lLastValue)
	: CDialog(COperatoriDlg::IDD, (CWnd*)pEsamiView)
{
	m_pEsamiView = pEsamiView;
	m_bMenu = bMenu;
	m_lLastMedico1 = p_lLastValue; // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	m_iStatusMode = _NONE_MODE_;   // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

	m_lID = 0;
	m_sTitolo = "";
	m_sCodice = "";
	m_sCognome = "";
	m_sNome = "";
	m_iLibero = BST_UNCHECKED;
	m_sCodiceFiscale = "";
	m_sVia = "";
	m_sCitta = "";
	m_sProvincia = "";
	m_sTelefono = "";
	m_sFirma0 = "";
	m_sFirma1 = "";
	m_sFirma2 = "";
	m_sFirma3 = "";
	m_sFirma4 = "";
	m_sFirma5 = "";
	m_sFirma6 = "";
	m_sFirma7 = "";
	m_sFirma8 = "";
	m_sFirma9 = "";

	m_lSavedPosition = -1;
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	m_bOrPressed = FALSE;
	m_bCleanContent = FALSE; // Luiz - 19/06/2019 - P3 - Melhoria do processo de busca

	m_pBitmapBuffer = NULL;
	m_dwBitmapBufferLength = 0;
}

COperatoriDlg::~COperatoriDlg()
{
}

BEGIN_MESSAGE_MAP(COperatoriDlg, CDialog)

	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	ON_BN_CLICKED(IDC_MEDICI_NUOVO, OnMediciNew)               // BOTÃO NUOVO
	ON_BN_CLICKED(IDC_MEDICI_MODIFY, OnMediciModify)           // BOTÃO MODIFICA
	ON_BN_CLICKED(IDC_MEDICI_CANC, OnMediciDelete)             // BOTÃO ELIMINA
	ON_BN_CLICKED(IDC_MEDICI_UPDATE, OnMediciUpdate)           // BOTÃO SALVA - ATUALIZA CADASTRO MÉDICO
	ON_BN_CLICKED(IDC_MEDICI_REFRESH, OnMediciRefresh)         // BOTÃO RICARICA (REFRESH)
	ON_BN_CLICKED(IDC_MEDICI_CLEAR, OnMediciClean)             // BOTÃO RESET (LIMPA)           // Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
	ON_BN_CLICKED(IDCANCEL, &COperatoriDlg::OnBnClickedCancel) // BOTÃO ESCI (CANCEL) // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	ON_BN_CLICKED(IDOK, &COperatoriDlg::OnBnClickedOK)         // BOTÃO OK (SALVA/CONFIRMA)     // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	//ON_BN_CLICKED(IDC_CHK_LIBERO, OnBnClickedChkLibero)        // DESCONTINUADO ???
	ON_BN_CLICKED(IDC_BTN_OR, OnBtnOr)                         // BOTÃO [OR] (OU)
	ON_BN_CLICKED(IDC_CLEAN_SEARCHMEDICI, &COperatoriDlg::OnBnClickedCleanSearchmedici)
	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

	ON_LBN_DBLCLK(IDC_LISTA, OnLbnDblclkLista)
	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)

	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()

	ON_EN_CHANGE(IDC_EDIT_SEARCHMEDICI, &COperatoriDlg::OnEnChangeEditSearchmedici)

END_MESSAGE_MAP()

void COperatoriDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_TITOLO, m_sTitolo);
	DDX_Text(pDX, IDC_CODICE, m_sCodice);
	DDX_Text(pDX, IDC_COGNOME, m_sCognome);
	DDX_Text(pDX, IDC_NOME, m_sNome);
	DDX_Check(pDX, IDC_CHK_LIBERO, m_iLibero);
	DDX_Text(pDX, IDC_CODICEFISCALE, m_sCodiceFiscale);
	DDX_Text(pDX, IDC_INDIRIZZO, m_sVia);
	DDX_Text(pDX, IDC_CITTA, m_sCitta);
	DDX_Text(pDX, IDC_PROVINCIA, m_sProvincia);
	DDX_Text(pDX, IDC_TELEFONO, m_sTelefono);
	DDX_Text(pDX, IDC_EDIT_FIRMA0, m_sFirma0);
	DDX_Text(pDX, IDC_EDIT_FIRMA1, m_sFirma1);
	DDX_Text(pDX, IDC_EDIT_FIRMA2, m_sFirma2);
	DDX_Text(pDX, IDC_EDIT_FIRMA3, m_sFirma3);
	DDX_Text(pDX, IDC_EDIT_FIRMA4, m_sFirma4);
	DDX_Text(pDX, IDC_EDIT_FIRMA5, m_sFirma5);
	DDX_Text(pDX, IDC_EDIT_FIRMA6, m_sFirma6);
	DDX_Text(pDX, IDC_EDIT_FIRMA7, m_sFirma7);
	DDX_Text(pDX, IDC_EDIT_FIRMA8, m_sFirma8);
	DDX_Text(pDX, IDC_EDIT_FIRMA9, m_sFirma9);

	DDV_MaxChars(pDX, m_sCodiceFiscale, 16);

	DDX_Control(pDX, IDC_CHK_LIBERO, m_ctrlChkLibero);
	DDX_Control(pDX, IDC_COMBO_USER, m_ctrlComboUser);

	DDX_Text(pDX, IDC_RICERCA_STR, m_strRicercaView);
	DDX_Control(pDX, IDC_LISTA, m_ctrlLista);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_7, m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC_8, m_ctrlStatic8);
	DDX_Control(pDX, IDC_STATIC_10, m_ctrlStatic10);
	DDX_Control(pDX, IDC_STATIC_11, m_ctrlStatic11);
	DDX_Control(pDX, IDC_LABEL_RIC, m_ctrlStaticRic);

	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	DDX_Control(pDX, IDC_MEDICI_NUOVO,   m_ctrlButtonNew);	 // BOTÃO NUOVO (INCLUSÃO DE MÉDICO)
	DDX_Control(pDX, IDC_MEDICI_MODIFY,  m_ctrlButtonEdt);	 // BOTÃO MODIFICA (ALTERAÇÃO DE MÉDICO)
	DDX_Control(pDX, IDC_MEDICI_CANC,    m_ctrlButtonDel);   // BOTÃO ELIMINA (DELETA REGISTRO DE MÉDICO)
	DDX_Control(pDX, IDC_MEDICI_UPDATE,  m_ctrlButtonSave);  // BOTÃO SALVA (INCLUSÃO / ALTERAÇÃO DE MÉDICO)
	DDX_Control(pDX, IDC_MEDICI_REFRESH, m_ctrlButtonUndo);  // BOTÃO ANULA (UNDO DA AÇÃO MODIFICA)
	DDX_Control(pDX, IDC_MEDICI_CLEAR,   m_ctrlButtonClean); // BOTÃO RESET (LIMPA)       // Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
	DDX_Control(pDX, IDCANCEL,           m_ctrlButtonEsc);   // BOTÃO ESCI (CANCEL)     // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	DDX_Control(pDX, IDOK,               m_ctrlButtonOK);	 // BOTÃO OK (SALVA/CONFIRMA) // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

	DDX_Control(pDX, IDC_LIST_SEDI, m_ctrlListSedi);

	DDX_Text(pDX, IDC_EDIT_SEARCHMEDICI, m_sMediciSearch);
}

BOOL COperatoriDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_bRicercaAttivata = theApp.m_nProgramMode & FILTER_RECORD_ESAMI;

	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
	{
		m_ctrlStatic10.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CODICE)->ShowWindow(SW_HIDE);
	}

	m_ctrlStatic00.SetFont(&theApp.m_fontBold);
	m_ctrlStatic01.SetFont(&theApp.m_fontBold);
	m_ctrlStaticRic.SetFont(&theApp.m_fontBold);
	m_ctrlButtonOK.SetFont(&theApp.m_fontBold);

	RiempiComboUsers();	

	CString sMedici;

	sMedici = GetCurrentUtentiMedici();
	
	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	BOOLEAN bLastSearchRecovered = false;
	if (sMedici.IsEmpty())
	{
		sMedici = theApp.m_sLastSearchMedico1;
		bLastSearchRecovered = true;
	}

	RiempiListaMedici(sMedici);
	GetDlgItem(IDC_EDIT_SEARCHMEDICI)->SetWindowText(m_strRicercaView);
	m_strRicercaView = sMedici;

	m_ctrlListSedi.EnableWindow(FALSE);

	if (m_bRicercaAttivata)
	{
		m_ctrlStaticRic.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RICERCA_STR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_OR)->ShowWindow(SW_SHOW);

		SetButtonsShowOrHide(_RICERCA_MODE_); // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	}
	else
	{
		SetButtonsShowOrHide(_EDIT_MODE_); // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

		// Sandro 15/12/2015 // RAS 20150065 //
		if (theApp.m_bMediciDescrizioneLibera)
		{
			m_ctrlChkLibero.ShowWindow(SW_SHOW);
		}
	}
	
	m_nItemPressed = 0;
	m_nItemCount = m_ctrlLista.GetCount();

	theApp.LocalizeDialog(this, COperatoriDlg::IDD, "OperatoriDlg");

	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	if (bLastSearchRecovered)
	{
		CEdit * pAuxEdit;
		pAuxEdit = (CEdit*)GetDlgItem(IDC_EDIT_SEARCHMEDICI);
		if (pAuxEdit != NULL){
			pAuxEdit->SetFocus();    // Set  focus to the component
			pAuxEdit->SetSel(0, -1); // Select all text of the component
			GetDlgItem(IDC_EDIT_SEARCHMEDICI)->SetWindowText(sMedici);
			pAuxEdit->UpdateWindow();// force it update
		}
	}
	return TRUE;
}

// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
void COperatoriDlg::SetButtonsShowOrHide(const int p_iContext){

	m_iStatusMode = p_iContext;

	// m_bMenu indica que o diálogo foi iniciado pelo Menu | Arquivo | Pessoal | Cadastro de Médicos...

	BOOL bEditingMode = (m_iStatusMode == _NEW_MODE_ || m_iStatusMode == _MODIFICA_MODE_);
	BOOL bHasRecordSelected = (!m_bCleanContent && m_ctrlLista.GetCount() > 0 && m_ctrlLista.GetCurSel() >= 0);

	switch (m_iStatusMode){
	case _RICERCA_MODE_:
		/* OFF */
		m_ctrlButtonNew.EnableWindow(FALSE);	// BOTÃO NUOVO (INCLUSÃO DE MÉDICO)
		m_ctrlButtonEdt.EnableWindow(FALSE);	// BOTÃO MODIFICA (ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonDel.EnableWindow(FALSE);	// BOTÃO ELIMINA (DELETA REGISTRO DE MÉDICO)
		m_ctrlButtonSave.EnableWindow(FALSE);	// BOTÃO SALVA (INCLUSÃO / ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonUndo.EnableWindow(FALSE);	// BOTÃO ANULA (UNDO DA AÇÃO MODIFICA)

		/* ON */
		m_ctrlButtonClean.EnableWindow(TRUE);	// BOTÃO RESET (LIMPA)  
		m_ctrlButtonEsc.EnableWindow(TRUE);		// BOTÃO ESCI (CANCEL) 
		m_ctrlButtonOK.EnableWindow(TRUE);		// BOTÃO OK (SALVA/CONFIRMA)

		break;
	case _EDIT_MODE_:
		/* ON */
		m_ctrlButtonNew.EnableWindow(TRUE);		// BOTÃO NUOVO (INCLUSÃO DE MÉDICO)
		/* ON se selecionado */
		m_ctrlButtonEdt.EnableWindow(bHasRecordSelected);		// BOTÃO MODIFICA (ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonDel.EnableWindow(bHasRecordSelected);		// BOTÃO ELIMINA (DELETA REGISTRO DE MÉDICO)
		/* OFF */
		m_ctrlButtonSave.EnableWindow(FALSE);	// BOTÃO SALVA (INCLUSÃO / ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonUndo.EnableWindow(FALSE);	// BOTÃO ANULA (UNDO DA AÇÃO MODIFICA)
		/* ON */
		m_ctrlButtonClean.EnableWindow(TRUE);	// BOTÃO RESET (LIMPA)  
		m_ctrlButtonEsc.EnableWindow(TRUE);		// BOTÃO ESCI (CANCEL) 
		m_ctrlButtonOK.EnableWindow(TRUE);		// BOTÃO OK (SALVA/CONFIRMA)

		break;

	case _MODIFICA_MODE_:
		/* OFF */
		m_ctrlButtonNew.EnableWindow(FALSE);	// BOTÃO NUOVO (INCLUSÃO DE MÉDICO)
		m_ctrlButtonEdt.EnableWindow(FALSE);	// BOTÃO MODIFICA (ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonDel.EnableWindow(FALSE);	// BOTÃO ELIMINA (DELETA REGISTRO DE MÉDICO)
		/* ON se editando */
		m_ctrlButtonSave.EnableWindow(bEditingMode);	// BOTÃO SALVA (INCLUSÃO / ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonUndo.EnableWindow(bEditingMode);	// BOTÃO ANULA (UNDO DA AÇÃO MODIFICA)
		/* OFF */
		m_ctrlButtonOK.EnableWindow(FALSE);    // BOTÃO OK (SALVA/CONFIRMA) E SAI
		m_ctrlButtonClean.EnableWindow(FALSE); // BOTÃO RESET (LIMPA)   // Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
		m_ctrlButtonEsc.EnableWindow(FALSE);   // BOTÃO ESCI (CANCEL) // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

		break;

	case _NEW_MODE_:
		/* OFF */
		m_ctrlButtonNew.EnableWindow(FALSE);	// BOTÃO NUOVO (INCLUSÃO DE MÉDICO)
		m_ctrlButtonEdt.EnableWindow(FALSE);	// BOTÃO MODIFICA (ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonDel.EnableWindow(FALSE);	// BOTÃO ELIMINA (DELETA REGISTRO DE MÉDICO)
		/* ON se editando */
		m_ctrlButtonSave.EnableWindow(bEditingMode);	// BOTÃO SALVA (INCLUSÃO / ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonUndo.EnableWindow(bEditingMode);	// BOTÃO ANULA (UNDO DA AÇÃO MODIFICA)
		/* OFF */
		m_ctrlButtonOK.EnableWindow(FALSE);
		m_ctrlButtonClean.EnableWindow(FALSE); // Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
		m_ctrlButtonEsc.EnableWindow(FALSE);   // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

		break;

	case _RICARICA_MODE_:
		m_ctrlButtonNew.EnableWindow(TRUE);		// BOTÃO NUOVO (INCLUSÃO DE MÉDICO)
		/* ON se selecionado */
		m_ctrlButtonEdt.EnableWindow(bHasRecordSelected);		// BOTÃO MODIFICA (ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonDel.EnableWindow(bHasRecordSelected);		// BOTÃO ELIMINA (DELETA REGISTRO DE MÉDICO)

		m_ctrlButtonSave.EnableWindow(FALSE);	// BOTÃO SALVA (INCLUSÃO / ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonUndo.EnableWindow(FALSE);	// BOTÃO ANULA (UNDO DA AÇÃO MODIFICA)

		m_ctrlButtonOK.EnableWindow(TRUE);
		m_ctrlButtonClean.EnableWindow(TRUE);
		//m_ctrlButtonClean.EnableWindow(FALSE); // Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
		m_ctrlButtonEsc.EnableWindow(TRUE);    // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

		break;

	case _UPDATE_MODE_:
		m_ctrlButtonNew.EnableWindow(TRUE);		// BOTÃO NUOVO (INCLUSÃO DE MÉDICO)
		/* ON se selecionado */
		m_ctrlButtonEdt.EnableWindow(bHasRecordSelected);		// BOTÃO MODIFICA (ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonDel.EnableWindow(bHasRecordSelected);		// BOTÃO ELIMINA (DELETA REGISTRO DE MÉDICO)
		m_ctrlButtonSave.EnableWindow(FALSE);	// BOTÃO SALVA (INCLUSÃO / ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonUndo.EnableWindow(FALSE);	// BOTÃO ANULA (UNDO DA AÇÃO MODIFICA)
		//m_ctrlButtonOK.EnableWindow(TRUE);
		m_ctrlButtonClean.EnableWindow(FALSE); // Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
		m_ctrlButtonEsc.EnableWindow(TRUE);    // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

		break;

	case _SELECTED_MODE_:
	case _NOT_SELECTED_MODE_:
		/* OFF m_bRicercaAttivata | ON caso contrário */
		m_ctrlButtonNew.EnableWindow(m_bRicercaAttivata ? FALSE : TRUE);	// BOTÃO NUOVO (INCLUSÃO DE MÉDICO)
		/* OFF para DLG | ON se selecionado*/
		m_ctrlButtonEdt.EnableWindow(bHasRecordSelected ? TRUE : FALSE);	// BOTÃO MODIFICA (ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonDel.EnableWindow(bHasRecordSelected ? TRUE : FALSE);	// BOTÃO ELIMINA (DELETA REGISTRO DE MÉDICO)
		/* ON se editando */
		m_ctrlButtonSave.EnableWindow(bEditingMode);	// BOTÃO SALVA (INCLUSÃO / ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonUndo.EnableWindow(bEditingMode);	// BOTÃO ANULA (UNDO DA AÇÃO MODIFICA)
		/* ON */
		m_ctrlButtonClean.EnableWindow(TRUE);	// BOTÃO RESET (LIMPA)  
		m_ctrlButtonEsc.EnableWindow(TRUE);		// BOTÃO ESCI (CANCEL) 
		m_ctrlButtonOK.EnableWindow(TRUE);		// BOTÃO OK (SALVA/CONFIRMA)

		break;

	case _ELIMINA_MODE_:
		/* ON */
		m_ctrlButtonNew.EnableWindow(TRUE);	// BOTÃO NUOVO (INCLUSÃO DE MÉDICO)
		/* ON se selecionado */
		m_ctrlButtonEdt.EnableWindow(bHasRecordSelected);	// BOTÃO MODIFICA (ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonDel.EnableWindow(bHasRecordSelected);	// BOTÃO ELIMINA (DELETA REGISTRO DE MÉDICO)

		/* OFF */
		m_ctrlButtonSave.EnableWindow(FALSE);	// BOTÃO SALVA (INCLUSÃO / ALTERAÇÃO DE MÉDICO)
		m_ctrlButtonUndo.EnableWindow(FALSE);	// BOTÃO ANULA (UNDO DA AÇÃO MODIFICA)
		m_ctrlButtonClean.EnableWindow(FALSE);  // Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
		m_ctrlButtonClean.EnableWindow(FALSE); // BOTÃO RESET(LIMPA)
		m_ctrlButtonEsc.EnableWindow(FALSE); // BOTÃO ESCI (CANCEL) 
		m_ctrlButtonOK.EnableWindow(FALSE); // BOTÃO OK (SALVA/CONFIRMA)
		break;

	}
	// HIDE X SHOW COMPONENTS

	// BOTÃO NUOVO (INCLUSÃO DE MÉDICO)
	if (m_ctrlButtonNew.IsWindowEnabled()){ m_ctrlButtonNew.ShowWindow(SW_SHOW); }
	else { m_ctrlButtonNew.ShowWindow(SW_HIDE); }

	// BOTÃO MODIFICA (ALTERAÇÃO DE MÉDICO)
	if (m_ctrlButtonEdt.IsWindowEnabled()){ m_ctrlButtonEdt.ShowWindow(SW_SHOW); }
	else { m_ctrlButtonEdt.ShowWindow(SW_HIDE); }

	// BOTÃO ELIMINA (DELETA REGISTRO DE MÉDICO)
	if (m_ctrlButtonDel.IsWindowEnabled()){ m_ctrlButtonDel.ShowWindow(SW_SHOW); }
	else { m_ctrlButtonDel.ShowWindow(SW_HIDE); }
	
	// BOTÃO SALVA (INCLUSÃO / ALTERAÇÃO DE MÉDICO)
	if (m_ctrlButtonSave.IsWindowEnabled()){ m_ctrlButtonSave.ShowWindow(SW_SHOW); }
	else { m_ctrlButtonSave.ShowWindow(SW_HIDE); }
	
	// BOTÃO ANULA (UNDO DA AÇÃO MODIFICA)
	if (m_ctrlButtonUndo.IsWindowEnabled()){ m_ctrlButtonUndo.ShowWindow(SW_SHOW); }
	else { m_ctrlButtonUndo.ShowWindow(SW_HIDE); }

	// BOTÃO RESET (LIMPA) 
	if (m_ctrlButtonClean.IsWindowEnabled()){ m_ctrlButtonClean.ShowWindow(SW_SHOW); }
	else { m_ctrlButtonClean.ShowWindow(SW_HIDE); }

	// BOTÃO ESCI (CANCEL) 
	if (m_ctrlButtonEsc.IsWindowEnabled()){ m_ctrlButtonEsc.ShowWindow(SW_SHOW); }
	else { m_ctrlButtonEsc.ShowWindow(SW_HIDE); }

	// BOTÃO OK (SALVA/CONFIRMA)
	if (m_ctrlButtonOK.IsWindowEnabled()){ m_ctrlButtonOK.ShowWindow(SW_SHOW); }
	else { m_ctrlButtonOK.ShowWindow(SW_HIDE); }
}

HBRUSH COperatoriDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
		case IDC_LIST_SEDI:
		{
			if (m_ctrlListSedi.IsWindowEnabled())
				pDC->SetTextColor(RGB_BLACK);
			else
				pDC->SetTextColor(RGB(95, 95, 95));
			break;
		}
	}

	return hBrush;
}


void COperatoriDlg::OnOK()
{
	if (m_strRicerca.Right(4) == " OR ")
	{
		m_strRicerca = m_strRicerca.Left(m_strRicerca.GetLength() - 4);
		m_strRicercaView = m_strRicercaView.Left(m_strRicercaView.GetLength() - 4);
	}

	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	theApp.m_sLastSearchMedico1 = m_strRicercaView;

	UpdateData(FALSE);

	CDialog::OnOK();
}

// DESCONTINUADO ???
//void COperatoriDlg::OnBnClickedChkLibero()
//{
	/*
	if (m_ctrlChkLibero.GetCheck() == BST_CHECKED)
	{
		GetDlgItem(IDC_COGNOME)->EnableWindow(FALSE);
		GetDlgItem(IDC_NOME)->EnableWindow(FALSE);

		GetDlgItem(IDC_COGNOME)->SetWindowText(theApp.GetMessageString(IDS_LIBERO));
		GetDlgItem(IDC_NOME)->SetWindowText(theApp.GetMessageString(IDS_LIBERO));
	}
	else
	{
		GetDlgItem(IDC_COGNOME)->EnableWindow(TRUE);
		GetDlgItem(IDC_NOME)->EnableWindow(TRUE);

		GetDlgItem(IDC_COGNOME)->SetWindowText("");
		GetDlgItem(IDC_NOME)->SetWindowText("");
	}

	UpdateData(TRUE);
	*/
//}

/// BOTÃO [OR] - CONCATENA CRITÉRIO DE PESQUISA DO CADASTRO MÉDICO
void COperatoriDlg::OnBtnOr()
{
	m_strRicerca += " OR ";
	m_strRicercaView += " OR ";

	m_bOrPressed = TRUE;
	GetDlgItem(IDC_BTN_OR)->EnableWindow(FALSE);

	UpdateData(FALSE);
}

// Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
/// BOTÃO [RESET] (CLEAR) - IGNORA O MÉDICO SELECIONADO - LIMPA O CAMPO (DEIXA VAZIO) - SAI COMO OK
void COperatoriDlg::OnMediciClean()
{
	if (m_bRicercaAttivata)
	{
		m_bCleanContent = TRUE;
		m_strRicerca = "-1";
		m_strRicercaView = "#NULL#";
	}
	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	else
	{
		m_bCleanContent = TRUE;
	}

	UpdateData(FALSE);

	CDialog::OnOK();
}

void COperatoriDlg::OnDestroy()
{
	CDialog::OnDestroy();

	if (m_pBitmapBuffer)
	{
		delete m_pBitmapBuffer;
		m_pBitmapBuffer = NULL;

		m_dwBitmapBufferLength = 0;
	}
}

/// DUPLO CLIQUE NA LISTA DE SELEÇÃO - SELECIONA O MÉDICO - E SAI COM OK
void COperatoriDlg::OnLbnDblclkLista()
{
	if (m_bMenu == FALSE)
		OnOK();
}

void COperatoriDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDblClk(nFlags, point);

	if (!m_bAddNew && !m_bModify)
		return;

	CRect rect;
	GetDlgItem(IDC_PLACE_IMMAGINEFIRMA)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	if (!rect.PtInRect(point))
		return;

	CFileDialog dlg(TRUE, "*.BMP", "", OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, "Windows Bitmap BMP|*.BMP|Graphics Interchange GIF|*GIF|Tagged Image TIF|*.TIF|Tagged Image TIFF|*.TIFF|", NULL);
	if (dlg.DoModal() == IDOK)
	{
		if (m_pBitmapBuffer)
		{
			delete m_pBitmapBuffer;
			m_pBitmapBuffer = NULL;

			m_dwBitmapBufferLength = 0;
		}

		//

		USES_CONVERSION;

		Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)Gdiplus::Bitmap::FromFile(A2W(dlg.GetPathName()));
		if (pBitmap->GetLastStatus() == Gdiplus::Ok)
		{
			CLSID idClass;
			if (GetEncoderClsid(L"image/bmp", &idClass))
			{
				// Gdiplus::Bitmap *dest = new Gdiplus::Bitmap(pBitmap->

				CString strFileTemp = theApp.m_sDirTemp + "\\" + CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M%S") + ".bmp";
				if (pBitmap->Save(T2W(strFileTemp), &idClass, NULL) == Gdiplus::Ok)
				{
					HANDLE hFile = CreateFile(strFileTemp, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
					if (hFile != INVALID_HANDLE_VALUE)
					{
						DWORD dwFileSize = GetFileSize(hFile, NULL);

						DWORD dwEncodeBufferLength = AmBase64_CalculateRequiredEncodeOutputBufferSize(dwFileSize);
						if (dwEncodeBufferLength < _FIRMA_BMP_MAX_LENGTH)
						{
							BYTE* pBufferFile = new BYTE[dwFileSize];
							DWORD dwBytesRead;
							if (ReadFile(hFile, (LPVOID)pBufferFile, dwFileSize, &dwBytesRead, NULL))
							{
								m_pBitmapBuffer = pBufferFile;
								m_dwBitmapBufferLength = dwFileSize;

								InvalidateRect(&rect);
							}
							else
							{
								delete pBufferFile;
							}
						}
						else
						{
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMMAGINEFIRMA_TROPPOGRANDE), MB_ICONSTOP);
						}

						CloseHandle(hFile);
					}
				}
				DeleteFile(strFileTemp);
			}
		}
		delete pBitmap;
	}
}

/// BOTÃO [ELIMINA] - EXECUTA A FUNÇÃO DELETE DO CADASTRO DO MÉDICO
void COperatoriDlg::OnMediciDelete()
{
	BOOL bDeleted = FALSE;

	m_ctrlLista.EnableWindow(TRUE);
	GetDlgItem(IDC_TITOLO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CODICE)->EnableWindow(FALSE);
	m_ctrlChkLibero.EnableWindow(FALSE);
	GetDlgItem(IDC_COGNOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_INDIRIZZO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CITTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_PROVINCIA)->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CODICEFISCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA0)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA7)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA8)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA9)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_USER)->EnableWindow(FALSE);

	m_ctrlListSedi.EnableWindow(FALSE);

	SetButtonsShowOrHide(_ELIMINA_MODE_); // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_DELETE_CONFIRM), MB_YESNO) == IDYES)
	{
		int nCurSel = m_ctrlLista.GetCurSel();
		if (nCurSel >= 0)
		{
			long lID = m_ctrlLista.GetItemData(nCurSel);
			if (lID > 0)
			{
				CString strFilter;
				strFilter.Format("Contatore=%li", lID);

				CMediciSet setMed;
				setMed.SetOpenFilter(strFilter);
				if (setMed.OpenRecordset("COperatoriDlg::OnMediciDelete"))
				{
					if (!setMed.IsEOF())
					{
						if (setMed.DeleteRecordset("COperatoriDlg::OnMediciDelete"))
						{
							int nRemained = m_ctrlLista.DeleteString(nCurSel);
							int nNewPos = min(nCurSel, nRemained - 1);

							m_ctrlLista.SetCurSel(nNewPos);

							OnSelchangeLista();
						}
					}

					setMed.CloseRecordset("COperatoriDlg::OnMediciDelete");
				}
			}
		}
	}

	UpdateData(FALSE);
	RedrawWindow();
}

/// BOTÃO [MODIFICA] - ENTRA NA EDIÇÃO DO CADASTRO DO MÉDICO
void COperatoriDlg::OnMediciModify()
{
	int nCurSel = m_ctrlLista.GetCurSel();
	if (nCurSel >= 0)
	{
		long lIDUserTemp = 0;

		int nCurSelTemp = m_ctrlComboUser.GetCurSel();
		if (nCurSelTemp >= 0)
			lIDUserTemp = m_ctrlComboUser.GetItemData(nCurSelTemp);

		// Ricarico la lista che potrebbe essere cambiata
		RiempiComboUsers();
		m_ctrlComboUser.SetCurSel(-1);
		for (int i = 0; i < m_ctrlComboUser.GetCount(); i++)
		{
			if (m_ctrlComboUser.GetItemData(i) == lIDUserTemp)
			{
				m_ctrlComboUser.SetCurSel(i);
				break;
			}
		}

		m_ctrlLista.EnableWindow(FALSE);

		GetDlgItem(IDC_TITOLO)->EnableWindow(TRUE);
		GetDlgItem(IDC_CODICE)->EnableWindow(TRUE);
		m_ctrlChkLibero.EnableWindow(TRUE);
		GetDlgItem(IDC_COGNOME)->EnableWindow(m_iLibero != BST_CHECKED);
		GetDlgItem(IDC_NOME)->EnableWindow(m_iLibero != BST_CHECKED);
		GetDlgItem(IDC_INDIRIZZO)->EnableWindow(TRUE);
		GetDlgItem(IDC_CITTA)->EnableWindow(TRUE);
		GetDlgItem(IDC_PROVINCIA)->EnableWindow(TRUE);
		GetDlgItem(IDC_TELEFONO)->EnableWindow(TRUE);
		GetDlgItem(IDC_CODICEFISCALE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FIRMA0)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FIRMA1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FIRMA2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FIRMA3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FIRMA4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FIRMA5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FIRMA6)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FIRMA7)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FIRMA8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FIRMA9)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_USER)->EnableWindow(TRUE);

		m_ctrlListSedi.EnableWindow(TRUE);

		SetButtonsShowOrHide(_MODIFICA_MODE_); // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

		m_bModify = TRUE;

		GetDlgItem(IDC_TITOLO)->SetFocus();

		UpdateData(FALSE);
	}
	RedrawWindow();
}

/// BOTÃO [NOVO] - ENTRA NA INCLUSÃO DO CADASTRO DO MÉDICO
void COperatoriDlg::OnMediciNew()
{
	RiempiComboUsers();
	m_ctrlComboUser.SetCurSel(-1);
	m_ctrlListSedi.SelItemRange(FALSE, 0, m_ctrlListSedi.GetCount() - 1);
	m_ctrlLista.EnableWindow(FALSE);
	GetDlgItem(IDC_TITOLO)->EnableWindow(TRUE);
	GetDlgItem(IDC_CODICE)->EnableWindow(TRUE);
	m_ctrlChkLibero.EnableWindow(TRUE);
	GetDlgItem(IDC_COGNOME)->EnableWindow(TRUE);
	GetDlgItem(IDC_NOME)->EnableWindow(TRUE);
	GetDlgItem(IDC_INDIRIZZO)->EnableWindow(TRUE);
	GetDlgItem(IDC_CITTA)->EnableWindow(TRUE);
	GetDlgItem(IDC_PROVINCIA)->EnableWindow(TRUE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(TRUE);
	GetDlgItem(IDC_CODICEFISCALE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_FIRMA0)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_FIRMA1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_FIRMA2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_FIRMA3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_FIRMA4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_FIRMA5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_FIRMA6)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_FIRMA7)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_FIRMA8)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_FIRMA9)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_USER)->EnableWindow(TRUE);

	m_ctrlListSedi.EnableWindow(TRUE);

	SetButtonsShowOrHide(_NEW_MODE_); // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

	m_lID = 0;
	m_sTitolo.Empty();
	m_sCodice.Empty();
	m_sCognome.Empty();
	m_sNome.Empty();
	m_iLibero = BST_UNCHECKED;
	m_sCodiceFiscale.Empty();
	m_sVia.Empty();
	m_sCitta.Empty();
	m_sProvincia.Empty();
	m_sTelefono.Empty();
	m_sFirma0.Empty();
	m_sFirma1.Empty();
	m_sFirma2.Empty();
	m_sFirma3.Empty();
	m_sFirma4.Empty();
	m_sFirma5.Empty();
	m_sFirma6.Empty();
	m_sFirma7.Empty();
	m_sFirma8.Empty();
	m_sFirma9.Empty();

	m_bAddNew = TRUE;

	GetDlgItem(IDC_TITOLO)->SetFocus();

	UpdateData(FALSE);
	RedrawWindow();
}

/// BOTÃO [RICARICA] (REFRESH) - REAPRESENTA A TELA DO CADASTRO DO MÉDICO - PERMANECE NO DIALOGO
void COperatoriDlg::OnMediciRefresh()
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	m_ctrlLista.EnableWindow(TRUE);
	GetDlgItem(IDC_CODICE)->EnableWindow(FALSE);
	m_ctrlChkLibero.EnableWindow(FALSE);
	GetDlgItem(IDC_COGNOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TITOLO)->EnableWindow(FALSE);
	GetDlgItem(IDC_INDIRIZZO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CITTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_PROVINCIA)->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CODICEFISCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA0)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA7)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA8)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FIRMA9)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_USER)->EnableWindow(FALSE);

	m_ctrlListSedi.EnableWindow(FALSE);
	
	SetButtonsShowOrHide(_RICARICA_MODE_); // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

	if (m_lSavedPosition <= m_ctrlLista.GetCount())
	{
		int nPos = m_lSavedPosition;
		if (nPos < 0 && m_ctrlLista.GetCount())
			nPos = 0;

		m_lSavedPosition = -1;

		m_ctrlLista.SetCurSel(nPos);

		OnSelchangeLista();
	}

	//

	/*
	CRect rectImmagineFirma;
	GetDlgItem(IDC_PLACE_IMMAGINEFIRMA)->GetWindowRect(&rectImmagineFirma);
	ScreenToClient(&rectImmagineFirma);
	InvalidateRect(&rectImmagineFirma);
	*/

	RedrawWindow();
}

/// BOTÃO [SALVA] - EXECUTA A FUNÇÃO SALVAR DO CADASTRO DO MÉDICO
void COperatoriDlg::OnMediciUpdate()
{
	if (m_ctrlComboUser.GetItemData(m_ctrlComboUser.GetCurSel()) <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_INFMED_ALERT1));
		return;
	}

	BOOL bSaved = FALSE;
	long lLastAdd = 0;

	UpdateData(TRUE);

	if (m_sTitolo.IsEmpty() && m_sCognome.IsEmpty() && m_sNome.IsEmpty() && m_sVia.IsEmpty() && m_sCitta.IsEmpty() && m_sProvincia.IsEmpty() && m_sTelefono.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		CMediciSet setMed;
		setMed.SetOpenFilter("Contatore=0");
		if (setMed.OpenRecordset("COperatoriDlg::OnMediciUpdate"))
		{
			if (setMed.AddNewRecordset("COperatoriDlg::OnMediciUpdate"))
			{
				setMed.m_sTitolo = m_sTitolo;
				setMed.m_sCodice = m_sCodice;
				setMed.m_sCognome = m_sCognome;
				setMed.m_sNome = m_sNome;
				setMed.m_bLibero = (m_iLibero != BST_UNCHECKED);
				setMed.m_sVia = m_sVia;
				setMed.m_sCitta = m_sCitta;
				setMed.m_sProvincia = m_sProvincia;
				setMed.m_sTelefono = m_sTelefono;
				setMed.m_sCodiceFiscale = m_sCodiceFiscale;
				setMed.m_sFirma0 = m_sFirma0;
				setMed.m_sFirma1 = m_sFirma1;
				setMed.m_sFirma2 = m_sFirma2;
				setMed.m_sFirma3 = m_sFirma3;
				setMed.m_sFirma4 = m_sFirma4;
				setMed.m_sFirma5 = m_sFirma5;
				setMed.m_sFirma6 = m_sFirma6;
				setMed.m_sFirma7 = m_sFirma7;
				setMed.m_sFirma8 = m_sFirma8;
				setMed.m_sFirma9 = m_sFirma9;
				setMed.m_lIDUserEndox = m_ctrlComboUser.GetItemData(m_ctrlComboUser.GetCurSel());

				//

				DWORD dwEncodeBufferLength = AmBase64_CalculateRequiredEncodeOutputBufferSize(m_dwBitmapBufferLength);
				TCHAR* pBufferB64 = new TCHAR[dwEncodeBufferLength];
				ZeroMemory(pBufferB64, dwEncodeBufferLength * sizeof(TCHAR));
				AmBase64_EncodeBuffer((CHAR*)m_pBitmapBuffer, m_dwBitmapBufferLength, pBufferB64);
				setMed.m_sImmagineFirma = CString(pBufferB64);
				delete pBufferB64;

				//

				bSaved = setMed.UpdateRecordset("COperatoriDlg::OnMediciUpdate");

				if (bSaved)
					lLastAdd = setMed.GetLastAdd();
			}
			setMed.CloseRecordset("COperatoriDlg::OnMediciUpdate");
		}
	}
	else
	{
		CString sFilter;
		sFilter.Format("Contatore=%li", m_lID);

		CMediciSet setMed;
		setMed.SetOpenFilter(sFilter);
		if (setMed.OpenRecordset("COperatoriDlg::OnMediciUpdate"))
		{
			if (!setMed.IsEOF())
			{
				if (setMed.EditRecordset("COperatoriDlg::OnMediciUpdate"))
				{
					setMed.m_sTitolo = m_sTitolo;
					setMed.m_sCodice = m_sCodice;
					setMed.m_sCognome = m_sCognome;
					setMed.m_sNome = m_sNome;
					setMed.m_bLibero = (m_iLibero != BST_UNCHECKED);
					setMed.m_sVia = m_sVia;
					setMed.m_sCitta = m_sCitta;
					setMed.m_sProvincia = m_sProvincia;
					setMed.m_sTelefono = m_sTelefono;
					setMed.m_sCodiceFiscale = m_sCodiceFiscale;
					setMed.m_sFirma0 = m_sFirma0;
					setMed.m_sFirma1 = m_sFirma1;
					setMed.m_sFirma2 = m_sFirma2;
					setMed.m_sFirma3 = m_sFirma3;
					setMed.m_sFirma4 = m_sFirma4;
					setMed.m_sFirma5 = m_sFirma5;
					setMed.m_sFirma6 = m_sFirma6;
					setMed.m_sFirma7 = m_sFirma7;
					setMed.m_sFirma8 = m_sFirma8;
					setMed.m_sFirma9 = m_sFirma9;
					setMed.m_lIDUserEndox = m_ctrlComboUser.GetItemData(m_ctrlComboUser.GetCurSel());

					//

					DWORD dwEncodeBufferLength = AmBase64_CalculateRequiredEncodeOutputBufferSize(m_dwBitmapBufferLength);
					TCHAR* pBufferB64 = new TCHAR[dwEncodeBufferLength];
					ZeroMemory(pBufferB64, dwEncodeBufferLength * sizeof(TCHAR));
					AmBase64_EncodeBuffer((CHAR*)m_pBitmapBuffer, m_dwBitmapBufferLength, pBufferB64);
					setMed.m_sImmagineFirma = CString(pBufferB64);
					delete pBufferB64;

					//

					bSaved = setMed.UpdateRecordset("COperatoriDlg::OnMediciUpdate");
				}
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_ALREADY_DELETED), MB_ICONINFORMATION);
			}
			setMed.CloseRecordset("COperatoriDlg::OnMediciUpdate");
		}
	}

	if (bSaved)
	{
		if (m_bAddNew)
		{
			int nCurSel = m_ctrlLista.AddString(m_sCognome + "\t" + m_sNome);
			if (nCurSel >= 0)
			{
				m_ctrlLista.SetItemData(nCurSel, (DWORD)lLastAdd);

				for (int i = 0; i < m_ctrlListSedi.GetCount(); i++)
				{
					if (m_ctrlListSedi.GetSel(i) > 0)
						CMediciSediEsameSet().AddRow(lLastAdd, m_ctrlListSedi.GetItemData(i));
					else
						CMediciSediEsameSet().DelRow(lLastAdd, m_ctrlListSedi.GetItemData(i));
				}

				m_ctrlLista.SetCurSel(nCurSel);
			}
		}
		else
		{
			int nCurSel = m_ctrlLista.GetCurSel();
			if (nCurSel >= 0)
			{
				m_ctrlLista.DeleteString(nCurSel);

				nCurSel = m_ctrlLista.InsertString(nCurSel, m_sCognome + "\t" + m_sNome);
				if (nCurSel >= 0)
				{
					m_ctrlLista.SetItemData(nCurSel, (DWORD)m_lID);

					for (int i = 0; i < m_ctrlListSedi.GetCount(); i++)
					{
						if (m_ctrlListSedi.GetSel(i) > 0)
							CMediciSediEsameSet().AddRow(m_lID, m_ctrlListSedi.GetItemData(i));
						else
							CMediciSediEsameSet().DelRow(m_lID, m_ctrlListSedi.GetItemData(i));
					}

					m_ctrlLista.SetCurSel(nCurSel);
				}
			}
		}

		m_ctrlLista.EnableWindow(TRUE);
		GetDlgItem(IDC_CODICE)->EnableWindow(FALSE);
		m_ctrlChkLibero.EnableWindow(FALSE);
		GetDlgItem(IDC_COGNOME)->EnableWindow(FALSE);
		GetDlgItem(IDC_NOME)->EnableWindow(FALSE);
		GetDlgItem(IDC_TITOLO)->EnableWindow(FALSE);
		GetDlgItem(IDC_INDIRIZZO)->EnableWindow(FALSE);
		GetDlgItem(IDC_CITTA)->EnableWindow(FALSE);
		GetDlgItem(IDC_PROVINCIA)->EnableWindow(FALSE);
		GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
		GetDlgItem(IDC_CODICEFISCALE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FIRMA0)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FIRMA1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FIRMA2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FIRMA3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FIRMA4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FIRMA5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FIRMA6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FIRMA7)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FIRMA8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FIRMA9)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_USER)->EnableWindow(FALSE);

		m_ctrlListSedi.EnableWindow(FALSE);

		SetButtonsShowOrHide(_UPDATE_MODE_); // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

		m_bModify = FALSE;
		m_bAddNew = FALSE;

		OnSelchangeLista();
	}
	RedrawWindow();
}

void COperatoriDlg::OnPaint()
{
	CPaintDC dc(this);

	if (!m_pBitmapBuffer)
		return;

	CRect rect;
	GetDlgItem(IDC_PLACE_IMMAGINEFIRMA)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	BYTE* pCurrentPos = m_pBitmapBuffer;
	BITMAPFILEHEADER* pBitmapHeader = (BITMAPFILEHEADER*)pCurrentPos;

	pCurrentPos += sizeof(BITMAPFILEHEADER);
	BITMAPINFO* pBitmapInfo = (BITMAPINFO*)pCurrentPos;

	pCurrentPos = m_pBitmapBuffer;
	pCurrentPos += pBitmapHeader->bfOffBits;

	CRect srcRect(0, 0, pBitmapInfo->bmiHeader.biWidth - 1, pBitmapInfo->bmiHeader.biHeight - 1);
	CRect dstRect(rect);

	double dFactorX = (double)rect.Width() / (double)pBitmapInfo->bmiHeader.biWidth;
	double dFactorY = (double)rect.Height() / (double)pBitmapInfo->bmiHeader.biHeight;

	dstRect.right = (LONG)(dstRect.left + min(dFactorX, dFactorY) * pBitmapInfo->bmiHeader.biWidth);
	dstRect.bottom = (LONG)(dstRect.top + min(dFactorX, dFactorY) * pBitmapInfo->bmiHeader.biHeight);

	CRect rectTmp(dstRect);
	rectTmp.left += abs(dstRect.Width() - rect.Width()) / 2;
	rectTmp.right += abs(dstRect.Width() - rect.Width()) / 2;
	rectTmp.top += abs(dstRect.Height() - rect.Height()) / 2;
	rectTmp.bottom += abs(dstRect.Height() - rect.Height()) / 2;
	dstRect = rectTmp;

	int iOldBltMode = dc.SetStretchBltMode(HALFTONE);

	int iScannedLines = ::StretchDIBits(dc.m_hDC,
		dstRect.left,
		dstRect.top,
		dstRect.Width(),
		dstRect.Height(),
		srcRect.left,
		srcRect.top,
		srcRect.Width(),
		srcRect.Height(),
		pCurrentPos,
		pBitmapInfo,
		DIB_RGB_COLORS,
		SRCCOPY);
	dc.SetStretchBltMode(iOldBltMode);
}

/// CLIQUE NA LISTA DE MÉDICO - BUSCA AS INFORMAÇÕES DO REGISTRO E REAPRESENTA NO FORM
void COperatoriDlg::OnSelchangeLista()
{
	if (m_bAddNew || m_bModify)
	{
		return;
	}

	// Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
	//-------------------------------------------------------
	if (m_bRicercaAttivata && m_bCleanContent)
	{
		m_ctrlComboUser.SetCurSel(-1);
		m_pBitmapBuffer = NULL;
		m_lID = 0;
		m_strRicercaView = "";
		m_strRicerca = "0";
		m_nItemPressed = 1;
		m_iLibero = BST_UNCHECKED;
		m_lSavedPosition = -1;
		return;
	}
	//-------------------------------------------------------
	// Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
	if (!m_bCleanContent) {
		if (m_ctrlLista.GetCount() > 0)
		{
			// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
			// se houver apenas um médico na lista, seleciona ele automaticamente
			if (m_ctrlLista.GetCount() == 1)
			{
				m_ctrlLista.SetCurSel(0);
			}

			if (m_ctrlLista.GetCurSel() >= 0)
			{
				SetMedicoSelected();
			}
		}
	}
}





// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
void COperatoriDlg::SetMedicoSelected()
{
	long lIDMedico = 0;
	CRect rectImmagineFirma;
	GetDlgItem(IDC_PLACE_IMMAGINEFIRMA)->GetWindowRect(&rectImmagineFirma);
	ScreenToClient(&rectImmagineFirma);

	if (m_ctrlLista.GetCount() > 0)
	{
		if (m_pBitmapBuffer)
		{
			delete m_pBitmapBuffer;
			m_pBitmapBuffer = NULL;

			m_dwBitmapBufferLength = 0;
		}

		int nCurSel = m_ctrlLista.GetCurSel();
		if (nCurSel >= 0)
		{
			SetButtonsShowOrHide(_SELECTED_MODE_);

			lIDMedico = (long)m_ctrlLista.GetItemData(nCurSel);
			if (lIDMedico > 0)
			{
				CString sFilter;
				sFilter.Format("Contatore=%li", lIDMedico);

				CMediciSet setMed;
				setMed.SetOpenFilter(sFilter);
				if (setMed.OpenRecordset("COperatoriDlg::SetMedicoSelected"))
				{
					if (!setMed.IsEOF())
					{
						m_lID = setMed.m_lContatore;
						m_sTitolo = setMed.m_sTitolo;
						m_sCodice = setMed.m_sCodice;

						/* if (setMed.m_bLibero)
						{
						m_sCognome = theApp.GetMessageString(IDS_LIBERO);
						m_sNome = theApp.GetMessageString(IDS_LIBERO);
						}
						else */
						{
							m_sCognome = setMed.m_sCognome;
							m_sNome = setMed.m_sNome;
						}

						m_iLibero = setMed.m_bLibero ? BST_CHECKED : BST_UNCHECKED;
						m_sCodiceFiscale = setMed.m_sCodiceFiscale;
						m_sVia = setMed.m_sVia;
						m_sCitta = setMed.m_sCitta;
						m_sProvincia = setMed.m_sProvincia;
						m_sTelefono = setMed.m_sTelefono;

						int m_iUserCurSel = -1;
						for (int i = 0; i < m_ctrlComboUser.GetCount(); i++)
						{
							if (m_ctrlComboUser.GetItemData(i) == setMed.m_lIDUserEndox)
							{
								m_iUserCurSel = i;
								break;
							}
						}
						m_ctrlComboUser.SetCurSel(m_iUserCurSel);

						m_sFirma0 = setMed.m_sFirma0;
						m_sFirma1 = setMed.m_sFirma1;
						m_sFirma2 = setMed.m_sFirma2;
						m_sFirma3 = setMed.m_sFirma3;
						m_sFirma4 = setMed.m_sFirma4;
						m_sFirma5 = setMed.m_sFirma5;
						m_sFirma6 = setMed.m_sFirma6;
						m_sFirma7 = setMed.m_sFirma7;
						m_sFirma8 = setMed.m_sFirma8;
						m_sFirma9 = setMed.m_sFirma9;

						if (!setMed.m_sImmagineFirma.IsEmpty())
						{
							LPTSTR pImmagineFirma = setMed.m_sImmagineFirma.GetBuffer(setMed.m_sImmagineFirma.GetLength());
							UINT iBitmapSize = AmBase64_CalculateRequiredDecodeOutputBufferSize(pImmagineFirma);
							m_pBitmapBuffer = new BYTE[iBitmapSize];
							m_dwBitmapBufferLength = iBitmapSize;
							AmBase64_DecodeBuffer(pImmagineFirma, setMed.m_sImmagineFirma.GetLength(), (TCHAR*)m_pBitmapBuffer);
							setMed.m_sImmagineFirma.ReleaseBuffer();
						}

						m_lSavedPosition = nCurSel;

						// sDoctor = m_sTitolo + " " + m_sCognome + " " + m_sNome; // ORIGINAL

						// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
						//----------------------------------------------------------------------------------------
						CString sDoctor;
						if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
							sDoctor = m_sTitolo + " " + m_sNome + " " + m_sCognome;
						else
							sDoctor = m_sTitolo + " " + m_sCognome + " " + m_sNome;
						//----------------------------------------------------------------------------------------
						// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante


						sDoctor.Trim();

						if (m_bRicercaAttivata)
						{
							if (m_bOrPressed)
							{
								CString sTemp;
								sTemp.Format("%i", m_lID);

								if (CanBeInserted(m_lID))
								{
									m_strRicerca += sTemp;
									m_strRicercaView += sDoctor;

									m_bOrPressed = FALSE;
									m_nItemPressed++;

									if (m_nItemPressed < m_nItemCount)
										GetDlgItem(IDC_BTN_OR)->EnableWindow(TRUE);
								}
							}
							else
							{
								m_strRicerca.Format("%i", m_lID);
								m_strRicercaView = sDoctor;
								m_nItemPressed = 1;
							}
						}
						else
						{
							m_strRicerca.Format("%i", m_lID);
							m_strRicercaView = sDoctor;
						}
					}

					setMed.CloseRecordset("COperatoriDlg::SetMedicoSelected");
				}

				UpdateData(FALSE);
			}
		}
		else
		{
			SetButtonsShowOrHide(_NOT_SELECTED_MODE_);
		}
	}

	SelezionaSedi(lIDMedico);
	InvalidateRect(&rectImmagineFirma);
}

// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
void COperatoriDlg::SetLastMedico()
{
	long lIDMedico = m_lLastMedico1;
	if (lIDMedico > 0)
	{
		CString sFilter;
		sFilter.Format("Contatore=%li", lIDMedico);

		CMediciSet setMed;
		setMed.SetOpenFilter(sFilter);
		if (setMed.OpenRecordset("COperatoriDlg::SetLastMedico"))
		{
			if (!setMed.IsEOF())
			{
				m_lID = setMed.m_lContatore;
				m_sTitolo = setMed.m_sTitolo;
				m_sCodice = setMed.m_sCodice;
				m_sCognome = setMed.m_sCognome;
				m_sNome = setMed.m_sNome;
				m_iLibero = setMed.m_bLibero ? BST_CHECKED : BST_UNCHECKED;
				m_sCodiceFiscale = setMed.m_sCodiceFiscale;
				m_sVia = setMed.m_sVia;
				m_sCitta = setMed.m_sCitta;
				m_sProvincia = setMed.m_sProvincia;
				m_sTelefono = setMed.m_sTelefono;

				m_sFirma0 = setMed.m_sFirma0;
				m_sFirma1 = setMed.m_sFirma1;
				m_sFirma2 = setMed.m_sFirma2;
				m_sFirma3 = setMed.m_sFirma3;
				m_sFirma4 = setMed.m_sFirma4;
				m_sFirma5 = setMed.m_sFirma5;
				m_sFirma6 = setMed.m_sFirma6;
				m_sFirma7 = setMed.m_sFirma7;
				m_sFirma8 = setMed.m_sFirma8;
				m_sFirma9 = setMed.m_sFirma9;

				CString sDoctor;
				if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
				{
					sDoctor = m_sTitolo + " " + m_sNome + " " + m_sCognome;
				}
				else
				{
					sDoctor = m_sTitolo + " " + m_sCognome + " " + m_sNome;
				}
				sDoctor.Trim();
				m_strRicerca.Format("%i", m_lID);
				m_strRicercaView = sDoctor;
			}

			setMed.CloseRecordset("COperatoriDlg::SetLastMedico");
		}

		UpdateData(FALSE);
	}

	SelezionaSedi(lIDMedico);
}

BOOL COperatoriDlg::CanBeInserted(long lContatore)
{
	CString strContatore, strTmp;

	//Controllo inizio stringa
	strContatore.Format("%i ", lContatore);
	strTmp = m_strRicerca.Left(strContatore.GetLength());

	if (strTmp == strContatore)
		return FALSE;

	//Controllo in mezzo alla stringa
	strContatore.Format(" %i ", lContatore);

	if (m_strRicerca.Find(strContatore) > 0)
		return FALSE;

	//Controllo alla fine
	strContatore.Format(" %i", lContatore);
	strTmp = m_strRicerca.Right(strContatore.GetLength());

	if (strTmp == strContatore)
		return FALSE;

	return TRUE;
}

void COperatoriDlg::RiempiComboUsers()
{
	m_ctrlComboUser.ResetContent();

	CVistaUtentiSet set;
	set.SetSortRecord("USERNAME");
	if (set.OpenRecordset("COperatoriDlg::RiempiComboUsers"))
	{
		int index = m_ctrlComboUser.AddString("");
		m_ctrlComboUser.SetItemData(index, 0);

		while (!set.IsEOF())
		{
			index = m_ctrlComboUser.AddString(set.m_sUsername);
			m_ctrlComboUser.SetItemData(index, set.m_lId);
			set.MoveNext();
		}
		set.CloseRecordset("COperatoriDlg::RiempiComboUsers");
	}
}

void COperatoriDlg::RiempiListaMedici(CString sFilter)
{
	m_ctrlLista.SetTabStops(100);
	
	// Sandro 18/11/2014 // RAS 20140046 //

	CMediciSet setMed;

	if (m_bRicercaAttivata)
		setMed.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
	else
		setMed.SetBaseFilter("");
	
	if (!sFilter.IsEmpty())
	{
		CString sFilt = "(nome like '%" + sFilter + "%' or cognome like '%" + sFilter + "%'" + "or nome + ' ' + cognome like '%" + sFilter + "%')";
		setMed.SetOpenFilter(sFilt);
	}

	setMed.SetSortRecord("Cognome, Nome");
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
		setMed.SetSortRecord("Nome, Cognome");

	m_ctrlLista.ResetContent();
	if (setMed.OpenRecordset("COperatoriDlg::RiempiListaMedici"))
	{
		while (!setMed.IsEOF())
		{
			CString sMedico = setMed.m_sCognome + "\t" + setMed.m_sNome;

			if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
				sMedico = setMed.m_sNome + "\t" + setMed.m_sCognome;

			int posiz = m_ctrlLista.AddString(sMedico);

			if (posiz >= 0)
				m_ctrlLista.SetItemData(posiz, (DWORD)setMed.m_lContatore);

			setMed.MoveNext();
		}

		setMed.CloseRecordset("COperatoriDlg::RiempiListaMedici");
	}
	
	OnSelchangeLista();
}

void COperatoriDlg::RiempiListaSedi()
{
	m_ctrlListSedi.SetRedraw(FALSE);
	m_ctrlListSedi.ResetContent();

	CSediEsameSet setSedi;
	setSedi.SetSortRecord("Descrizione");
	if (setSedi.OpenRecordset("COperatoriDlg::RiempiListaSedi"))
	{
		int nIndex = 0;

		while (!setSedi.IsEOF())
		{
			m_ctrlListSedi.InsertString(nIndex, setSedi.m_sDescrizione);
			m_ctrlListSedi.SetItemData(nIndex, setSedi.m_lID);

			nIndex++;
			setSedi.MoveNext();
		}

		setSedi.CloseRecordset("COperatoriDlg::RiempiListaSedi");
	}

	m_ctrlListSedi.SetRedraw(TRUE);
}

long COperatoriDlg::GetIDUtenteEndoxFromMediciID(long lID)
{
	long lIDUtenteEndox = 0;
	CMediciSet set;

	CString sFilter;
	sFilter.Format("CONTATORE = %li", lID);
	set.SetOpenFilter(sFilter);

	if (set.OpenRecordset("COperatoriDlg::GetIDUtenteEndoxFromMediciID"))
	{
		if (!set.IsEOF())
		{
			lIDUtenteEndox = set.m_lIDUserEndox;
		}
		set.CloseRecordset("COperatoriDlg::GetIDUtenteEndoxFromMediciID");
	}	
	return lIDUtenteEndox;
}

CString COperatoriDlg::GetCurrentUtentiMedici()
{
	CString sReturn = "";

	CString sFilter;
	long lIDUtenti = 0;

	CVistaUtentiSet set;
	set.SetSortRecord("USERNAME");
	sFilter.Format("USERNAME = '%s'", theApp.m_sUtenteLoggato);
	set.SetOpenFilter(sFilter);

	if (set.OpenRecordset("COperatoriDlg::GetCurrentUtentiMedici"))
	{
		if(!set.IsEOF())
		{
			lIDUtenti = set.m_lId;
		}
		set.CloseRecordset("COperatoriDlg::RiempiComboUsers");
	}

	if (lIDUtenti > 0)
	{
		CMediciSet setMed;
		if (m_bRicercaAttivata)
			setMed.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
		else
			setMed.SetBaseFilter("");


		sFilter.Format("idutenteendox = %li", lIDUtenti);
		setMed.SetOpenFilter(sFilter);


		setMed.SetSortRecord("Cognome, Nome");
		if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
			setMed.SetSortRecord("Nome, Cognome");

		m_ctrlLista.ResetContent();
		if (setMed.OpenRecordset("COperatoriDlg::RiempiListaMedici"))
		{
			if(!setMed.IsEOF())
			{							
				sReturn = setMed.m_sNome + " " + setMed.m_sCognome;				
				
				//CString sDoctor = setMed.m_sTitolo + " " + setMed.m_sCognome + " " + setMed.m_sNome; //ORIGINAL

				// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
				//----------------------------------------------------------------------------------------
				CString sDoctor;
				if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
					sDoctor = setMed.m_sTitolo + " " + setMed.m_sNome + " " + setMed.m_sCognome;
				else
					sDoctor = setMed.m_sTitolo + " " + setMed.m_sCognome + " " + setMed.m_sNome;
				//----------------------------------------------------------------------------------------
				// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante


				m_strRicercaView = sDoctor;

				CString sID;
				sID.Format("%i", setMed.m_lContatore);
				m_strRicerca = sID;
			}
			setMed.CloseRecordset("COperatoriDlg::RiempiListaMedici");
		}
	}
	
	
	return sReturn;
}

void COperatoriDlg::SelezionaSedi(long lContatoreMedico)
{
	//
	m_ctrlListSedi.SetRedraw(FALSE);
	m_ctrlListSedi.SelItemRange(FALSE, 0, m_ctrlListSedi.GetCount() - 1);

	if (lContatoreMedico > 0)
	{
		//
		CString sFilter;
		sFilter.Format("IDMedico=%li", lContatoreMedico);

		//
		CMediciSediEsameSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("COperatoriDlg::SelezionaSedi"))
		{
			while (!setTemp.IsEOF())
			{
				for (int i = 0; i < m_ctrlListSedi.GetCount(); i++)
				{
					if (m_ctrlListSedi.GetItemData(i) == setTemp.m_lIDSede)
					{
						m_ctrlListSedi.SetSel(i, TRUE);
						break;
					}
				}

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("COperatoriDlg::SelezionaSedi");
		}
	}

	// mi riposiziono all'inizio //
	m_ctrlListSedi.SendMessage(WM_VSCROLL, SB_TOP, NULL);

	//
	m_ctrlListSedi.SetRedraw(TRUE);
}


void COperatoriDlg::OnEnChangeEditSearchmedici()
{
	GetDlgItem(IDC_EDIT_SEARCHMEDICI)->GetWindowText(m_sMediciSearch);

	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	if (m_bAlowListUpdate)
		RiempiListaMedici(m_sMediciSearch);

	SetButtonsShowOrHide(_SELECTED_MODE_);
}

// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
/// USADO PARA O BOTÃO [OK] - CONFIRMA A SELEÇÃO E SAI COM RESULT OK
void COperatoriDlg::OnBnClickedOK() // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
{
	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	theApp.m_sLastSearchMedico1 = m_strRicercaView;
	CDialog::OnOK();
}


// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
/// BOTÃO [ANULLA] (CANCEL) - IGNORA O MÉDICO SELECIONADO / RESTAURA O MÉDICO ANTERIOR / SAI COM CANCEL
void COperatoriDlg::OnBnClickedCancel()
{
	//m_bCleanContent = true;
	//CDialog::OnCancel();

	// DEIXAR ELE SAIR COM OK PARA FORÇAR O REFRESH DO MÉDICO ANTERIOR NO FORM CHAMADOR
	SetLastMedico();
	CDialog::OnOK();
}

// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
void COperatoriDlg::OnBnClickedCleanSearchmedici()
{
	m_bAlowListUpdate = FALSE;
	CEdit * pAuxEdit;
	pAuxEdit = (CEdit*)GetDlgItem(IDC_EDIT_SEARCHMEDICI);
	if (pAuxEdit != NULL){
		GetDlgItem(IDC_EDIT_SEARCHMEDICI)->SetWindowText(" ");
		pAuxEdit->UpdateWindow();// force it update
		pAuxEdit->SetFocus();    // Set  focus to the component
	}
	m_bAlowListUpdate = TRUE;
	GetDlgItem(IDC_EDIT_SEARCHMEDICI)->SetWindowText("");
}
