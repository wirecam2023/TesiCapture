#include "stdafx.h"
#include "Endox.h"
#include "EsamiView.h"
#include "DocManager.h"

#include "ButtonDynForm.h"

#include <WinReg.h>

#include "DLL_Imaging\h\AMLogin.h"

#include "CustomDate.h"
#include "EsamiFasiChiuseSet.h"
#include "EsamiRefertazioneRemotaSet.h"
#include "EsamiView.h"
#include "ExtOrdiniSet.h"
#include "ExtVideocapsuleSet.h"
#include "FasiEsameSet.h"
#include "MediciSet.h"
#include "MstCodificaDiagnosiEsame5RigheUseDlg.h"
#include "MstCodificaDiagnosiEsameUseDlg.h"
#include "MstComplicanze1UseDlg.h"
#include "MstComplicanze2UseDlg.h"
#include "MstComplicanze3UseDlg.h"
#include "MstDiagnosiUseDlg.h"
#include "MstOsservazioniUseDlg.h"
#include "MstProcedureDiagnosticheUseDlg.h"
#include "MstProcedureTerapeuticheUseDlg.h"
#include "UtentiSet.h"
#include "OperatoriDlg.h"
#include "ExtPrestazioniSet.h" //Gabriel - TCP
#include "EsamiInvioAltraUnitaSet.h" //Gabriel - TCP
#include "InviaAltraUnitaDlg.h" //Gabriel - TCP

// librerie per le chiamate http //
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include <windows.h>
#include <wininet.h>
#include "WebForm\Web.h"
#include "ExtComboPrestazioni.h"
#include "AlbumEsameDlg.h"
#include "AlbumForm.h"
#include "ExamListDlg.h"
#include "MultiPageTiffNewEdtDlg.h"
#include "PDFCreator.h"
#include "QueryDlg.h"
#include "RefertoDlg.h"

#include "NeoConnection.h"
#include "SendPneuDLG.h"

using namespace openutils;
//

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CButton CButtonDynForm::m_ctrlButtonOsservazioni;
CButton CButtonDynForm::m_ctrlButtonDiagnostiche;
CButton CButtonDynForm::m_ctrlButtonTerapeutiche;
CButton CButtonDynForm::m_ctrlButtonDiagnosi;
CButton CButtonDynForm::m_ctrlButtonCodificaDiagnosiEsame;
CButton CButtonDynForm::m_ctrlButtonConvalida;
CButton CButtonDynForm::m_ctrlButtonChiusuraEsame;
CButton CButtonDynForm::m_ctrlButtonComplicanze1;
CButton CButtonDynForm::m_ctrlButtonComplicanze2;
CButton CButtonDynForm::m_ctrlButtonComplicanze3;
CButton CButtonDynForm::m_ctrlButtonVideocapsula;
CButton CButtonDynForm::m_ctrlButtonStampa[NUM_LABEL_TASTO_STAMPA];
CButton CButtonDynForm::m_ctrlButtonBrowser[NUM_LABEL_TASTO_BROWSER];
CButton CButtonDynForm::m_ctrlButtonEseguibile[NUM_LABEL_TASTO_EXEC];
CButton CButtonDynForm::m_ctrlButtonChiusuraFase[NUM_LABEL_TASTO_CHIUSURAFASE];
CButton CButtonDynForm::m_ctrlButtonCentraleRefertazione;
CButton CButtonDynForm::m_ctrlButtonCarestream;
CButton CButtonDynForm::m_ctrlButtonInviaAltraUnita; //Gabriel - TCP

CButtonDynForm::CButtonDynForm(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
: CEndoxDynForm(CButtonDynForm::IDD, pParent, pEsamiView)
{
	m_lContenuto = lContenuto;
}

CButtonDynForm::~CButtonDynForm()
{
}

BEGIN_MESSAGE_MAP(CButtonDynForm, CEndoxDynForm)

	ON_BN_CLICKED(IDC_BUTTON, OnClickButton) 

	ON_WM_PAINT()

	ON_CBN_SELCHANGE(IDC_COMBO_USER, &CButtonDynForm::OnCbnSelchangeComboUser)
END_MESSAGE_MAP()

void CButtonDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new CButtonDynForm(NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(CButtonDynForm::IDD, pParent, rectFrame);
		}
	}
}

void CButtonDynForm::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_STATIC_SEARCH, m_ctrlStatic);
	DDX_Control(pDX, IDC_STATIC_SEARCH_1, m_ctrlStaticSearch1);
	DDX_Control(pDX, IDC_STATIC_SEARCH_2, m_ctrlStaticSearch2);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_ctrlDataOraSearch);
	DDX_Control(pDX, IDC_COMBO_USER, m_ctrlComboUtenteSearch);

	//DDX_FieldOperatoriCombo(pDX, IDC_COMBO_USER, m_pEsamiView->m_pEsamiSet->m_lMedico, m_pEsamiView->m_pEsamiSet);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		DDX_Text(pDX, IDC_EDIT_SEARCH, m_ctrlDataOraSearch.m_strRicercaView);

	switch(m_lContenuto)
	{
		case btn_osservazioni:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonOsservazioni);
			break;
		}
		case btn_diagnostiche:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonDiagnostiche);
			break;
		}
		case btn_terapeutiche:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonTerapeutiche);
			break;
		}
		case btn_diagnosi:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonDiagnosi);
			break;
		}
		case btn_codificadiagnosiesame: 
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonCodificaDiagnosiEsame);
			break;
		}
		case btn_codificadiagnosiesame5righe: 
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonCodificaDiagnosiEsame);
			break;
		}
		case btn_convalida:
		{			
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonConvalida);
			break;
		}
		case btn_chiusuraesame:
		{			
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonChiusuraEsame);
			break;
		}
		case btn_complicanze1:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonComplicanze1);
			break;
		}
		case btn_complicanze2:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonComplicanze2);
			break;
		}
		case btn_complicanze3:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonComplicanze3);
			break;
		}
		case btn_videocapsula:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonVideocapsula);
			break;
		}
		case btn_liberotastostampa000:
		case btn_liberotastostampa001:
		case btn_liberotastostampa002:
		case btn_liberotastostampa003:
		case btn_liberotastostampa004:
		case btn_liberotastostampa005:
		case btn_liberotastostampa006:
		case btn_liberotastostampa007:
		case btn_liberotastostampa008:
		case btn_liberotastostampa009:
		case btn_liberotastostampa010:
		case btn_liberotastostampa011:
		case btn_liberotastostampa012:
		case btn_liberotastostampa013:
		case btn_liberotastostampa014:
		case btn_liberotastostampa015:
		case btn_liberotastostampa016:
		case btn_liberotastostampa017:
		case btn_liberotastostampa018:
		case btn_liberotastostampa019:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonStampa[m_lContenuto - btn_liberotastostampa000]);
			break;
		}
		case btn_liberotastobrowser000:
		case btn_liberotastobrowser001:
		case btn_liberotastobrowser002:
		case btn_liberotastobrowser003:
		case btn_liberotastobrowser004:
		case btn_liberotastobrowser005:
		case btn_liberotastobrowser006:
		case btn_liberotastobrowser007:
		case btn_liberotastobrowser008:
		case btn_liberotastobrowser009:
		case btn_liberotastobrowser010:
		case btn_liberotastobrowser011:
		case btn_liberotastobrowser012:
		case btn_liberotastobrowser013:
		case btn_liberotastobrowser014:
		case btn_liberotastobrowser015:
		case btn_liberotastobrowser016:
		case btn_liberotastobrowser017:
		case btn_liberotastobrowser018:
		case btn_liberotastobrowser019:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonBrowser[m_lContenuto - btn_liberotastobrowser000]);
			break;
		}
		case btn_liberotastoeseguibile000:
		case btn_liberotastoeseguibile001:
		case btn_liberotastoeseguibile002:
		case btn_liberotastoeseguibile003:
		case btn_liberotastoeseguibile004:
		case btn_liberotastoeseguibile005:
		case btn_liberotastoeseguibile006:
		case btn_liberotastoeseguibile007:
		case btn_liberotastoeseguibile008:
		case btn_liberotastoeseguibile009:
		case btn_liberotastoeseguibile010:
		case btn_liberotastoeseguibile011:
		case btn_liberotastoeseguibile012:
		case btn_liberotastoeseguibile013:
		case btn_liberotastoeseguibile014:
		case btn_liberotastoeseguibile015:
		case btn_liberotastoeseguibile016:
		case btn_liberotastoeseguibile017:
		case btn_liberotastoeseguibile018:
		case btn_liberotastoeseguibile019:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonEseguibile[m_lContenuto - btn_liberotastoeseguibile000]);
			break;
		}
		case btn_centralerefertazione:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonCentraleRefertazione);
			break;
		}
		case btn_carestream:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonCarestream);
			break;
		}
		case btn_liberotastochiusurafase000:
		case btn_liberotastochiusurafase001:
		case btn_liberotastochiusurafase002:
		case btn_liberotastochiusurafase003:
		case btn_liberotastochiusurafase004:
		case btn_liberotastochiusurafase005:
		case btn_liberotastochiusurafase006:
		case btn_liberotastochiusurafase007:
		case btn_liberotastochiusurafase008:
		case btn_liberotastochiusurafase009:
		case btn_liberotastochiusurafase010:
		case btn_liberotastochiusurafase011:
		case btn_liberotastochiusurafase012:
		case btn_liberotastochiusurafase013:
		case btn_liberotastochiusurafase014:
		case btn_liberotastochiusurafase015:
		case btn_liberotastochiusurafase016:
		case btn_liberotastochiusurafase017:
		case btn_liberotastochiusurafase018:
		case btn_liberotastochiusurafase019:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonChiusuraFase[m_lContenuto - btn_liberotastochiusurafase000]);
			break;
		}
		//Gabriel - TCP
		case btn_invia_altra_unita:
		{
			DDX_Control(pDX, IDC_BUTTON, m_ctrlButtonInviaAltraUnita); 
			break;
		}
	}

	SetButtonText();
}

BOOL CButtonDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_BUTTON)->GetSafeHwnd(), CSize(0,50), CSize(100,100));

	AddAnchor(IDC_STATIC_SEARCH_1, CSize(0, 50), CSize(50, 50));
	AddAnchor(IDC_COMBO_USER, CSize(0, 50), CSize(50, 50));

	AddAnchor(IDC_STATIC_SEARCH_2, CSize(50, 50), CSize(100, 50));
	AddAnchor(IDC_EDIT_SEARCH, CSize(50, 50), CSize(100, 50));

	m_ctrlDataOraSearch.ShowWindow(SW_HIDE);
	m_ctrlComboUtenteSearch.ShowWindow(SW_HIDE);
	m_ctrlStaticSearch1.ShowWindow(SW_HIDE);
	m_ctrlStaticSearch2.ShowWindow(SW_HIDE);
	m_ctrlStatic.ShowWindow(SW_HIDE);	
	

	switch(m_lContenuto)
	{
		case btn_osservazioni:
		{
			GetDlgItem(IDC_BUTTON)->SetFont(&theApp.m_fontBold);
			SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_OSSERVAZIONI));
			break;
		}
		case btn_diagnostiche:
		{
			GetDlgItem(IDC_BUTTON)->SetFont(&theApp.m_fontBold);
			SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_DIAGNOSTICHE));
			break;
		}
		case btn_terapeutiche:
		{
			GetDlgItem(IDC_BUTTON)->SetFont(&theApp.m_fontBold);
			SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_TERAPEUTICHE));
			break;
		}
		case btn_diagnosi:
		{
			GetDlgItem(IDC_BUTTON)->SetFont(&theApp.m_fontBold);
			SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_DIAGNOSI));
			break;
		}
		case btn_codificadiagnosiesame: 
		{
			GetDlgItem(IDC_BUTTON)->SetFont(&theApp.m_fontBold);
			SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_CODIFICADIAGNOSIESAME));
			break;
		}
		case btn_codificadiagnosiesame5righe: 
		{
			GetDlgItem(IDC_BUTTON)->SetFont(&theApp.m_fontBold);
			SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_CODIFICADIAGNOSIESAME));
			break;
		}
		case btn_convalida:
		{		
			SetDlgItemText(IDC_STATIC_SEARCH, theApp.GetMessageString(IDS_BTN_CONVALIDA));
			m_ctrlDataOraSearch.SetParam(this, m_pEsamiView, theApp.GetMessageString(IDS_BTN_CONVALIDA), DATA_ORA_FULL);
			
			m_ctrlComboUtenteSearch.SelectCurrent(this);
			m_ctrlComboUtenteSearch.SetCurSel(0);

			if (theApp.m_bUsaMedicoLogadoNaPesquisaSalvar)
				m_ctrlComboUtenteSearch.SelectCurrent(this);
			
			SetButtonText();
			break;
		}
		case btn_chiusuraesame:
		{			
			SetDlgItemText(IDC_STATIC_SEARCH, theApp.GetMessageString(IDS_BTN_CHIUSURAESAME));
			m_ctrlDataOraSearch.SetParam(this, m_pEsamiView, theApp.GetMessageString(IDS_BTN_CHIUSURAESAME), DATA_ORA_FULL);
			
			m_ctrlComboUtenteSearch.SelectCurrent(this);
			m_ctrlComboUtenteSearch.SetCurSel(0);

			if (theApp.m_bUsaMedicoLogadoNaPesquisaAssinar)
				m_ctrlComboUtenteSearch.SelectCurrent(this);
			
			SetButtonText();
			break;
		}
		// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo 
		case btn_libera_laudo:
		{
			SetDlgItemText(IDC_STATIC_SEARCH, theApp.GetMessageString(IDS_LIBERA_LAUDO));
			m_ctrlDataOraSearch.SetParam(this, m_pEsamiView, theApp.GetMessageString(IDS_LIBERA_LAUDO), DATA_ORA_FULL);

			if (theApp.m_bUsaMedicoLogadoNaPesquisaSalvar)
				m_ctrlComboUtenteSearch.SelectCurrent(this);

			SetButtonText();
			break;
		}
		case btn_complicanze1:
		{
			GetDlgItem(IDC_BUTTON)->SetFont(&theApp.m_fontBold);
			SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_COMPLICANZE1));
			break;
		}
		case btn_complicanze2:
		{
			GetDlgItem(IDC_BUTTON)->SetFont(&theApp.m_fontBold);
			SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_COMPLICANZE2));
			break;
		}
		case btn_complicanze3:
		{
			GetDlgItem(IDC_BUTTON)->SetFont(&theApp.m_fontBold);
			SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_COMPLICANZE3));
			break;
		}
		case btn_videocapsula:
		{
			SetButtonText();
			break;
		}
		case btn_liberotastostampa000:
		case btn_liberotastostampa001:
		case btn_liberotastostampa002:
		case btn_liberotastostampa003:
		case btn_liberotastostampa004:
		case btn_liberotastostampa005:
		case btn_liberotastostampa006:
		case btn_liberotastostampa007:
		case btn_liberotastostampa008:
		case btn_liberotastostampa009:
		case btn_liberotastostampa010:
		case btn_liberotastostampa011:
		case btn_liberotastostampa012:
		case btn_liberotastostampa013:
		case btn_liberotastostampa014:
		case btn_liberotastostampa015:
		case btn_liberotastostampa016:
		case btn_liberotastostampa017:
		case btn_liberotastostampa018:
		case btn_liberotastostampa019:
		{
			SetDlgItemText(IDC_BUTTON, theApp.m_sLabelTastoStampa[m_lContenuto - btn_liberotastostampa000]);
			break;
		}
		case btn_liberotastobrowser000:
		case btn_liberotastobrowser001:
		case btn_liberotastobrowser002:
		case btn_liberotastobrowser003:
		case btn_liberotastobrowser004:
		case btn_liberotastobrowser005:
		case btn_liberotastobrowser006:
		case btn_liberotastobrowser007:
		case btn_liberotastobrowser008:
		case btn_liberotastobrowser009:
		case btn_liberotastobrowser010:
		case btn_liberotastobrowser011:
		case btn_liberotastobrowser012:
		case btn_liberotastobrowser013:
		case btn_liberotastobrowser014:
		case btn_liberotastobrowser015:
		case btn_liberotastobrowser016:
		case btn_liberotastobrowser017:
		case btn_liberotastobrowser018:
		case btn_liberotastobrowser019:
		{
			SetDlgItemText(IDC_BUTTON, theApp.m_sLabelTastoBrowser[m_lContenuto - btn_liberotastobrowser000]);
			break;
		}
		case btn_liberotastoeseguibile000:
		case btn_liberotastoeseguibile001:
		case btn_liberotastoeseguibile002:
		case btn_liberotastoeseguibile003:
		case btn_liberotastoeseguibile004:
		case btn_liberotastoeseguibile005:
		case btn_liberotastoeseguibile006:
		case btn_liberotastoeseguibile007:
		case btn_liberotastoeseguibile008:
		case btn_liberotastoeseguibile009:
		case btn_liberotastoeseguibile010:
		case btn_liberotastoeseguibile011:
		case btn_liberotastoeseguibile012:
		case btn_liberotastoeseguibile013:
		case btn_liberotastoeseguibile014:
		case btn_liberotastoeseguibile015:
		case btn_liberotastoeseguibile016:
		case btn_liberotastoeseguibile017:
		case btn_liberotastoeseguibile018:
		case btn_liberotastoeseguibile019:
		{
			SetDlgItemText(IDC_BUTTON, theApp.m_sLabelTastoEseguibile[m_lContenuto - btn_liberotastoeseguibile000]);
			break;
		}
		case btn_centralerefertazione:
		{
			SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_CENTRALEREFERTAZIONE));
			break;
		}
		case btn_carestream:
		{
			SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_CARESTREAM));
			break;
		}
		case btn_liberotastochiusurafase000:
		case btn_liberotastochiusurafase001:
		case btn_liberotastochiusurafase002:
		case btn_liberotastochiusurafase003:
		case btn_liberotastochiusurafase004:
		case btn_liberotastochiusurafase005:
		case btn_liberotastochiusurafase006:
		case btn_liberotastochiusurafase007:
		case btn_liberotastochiusurafase008:
		case btn_liberotastochiusurafase009:
		case btn_liberotastochiusurafase010:
		case btn_liberotastochiusurafase011:
		case btn_liberotastochiusurafase012:
		case btn_liberotastochiusurafase013:
		case btn_liberotastochiusurafase014:
		case btn_liberotastochiusurafase015:
		case btn_liberotastochiusurafase016:
		case btn_liberotastochiusurafase017:
		case btn_liberotastochiusurafase018:
		case btn_liberotastochiusurafase019:
		{
			SetDlgItemText(IDC_BUTTON, theApp.m_sLabelTastoChiusuraFase[m_lContenuto - btn_liberotastochiusurafase000]);
			break;
		}
		//Gabriel - TCP
		case btn_invia_altra_unita:
		{
			if (theApp.m_bAtivaTCP)
				SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_INVIAALTRAUNITA));
			break;
		}
	}
	GetDlgItem(IDC_BUTTON)->SetWindowPos(&CWnd::wndTop/*Most*/, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	return bReturn;
}

LRESULT CButtonDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlComboUtenteSearch.SetCurSel(0);
	return 1;
}

LRESULT CButtonDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)

{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	switch (m_lContenuto)
	{	
	case btn_chiusuraesame:
	{
		CString strIDUtente;
		if (m_ctrlComboUtenteSearch.GetCurSel() >= 0)
			strIDUtente.Format("= %li", COperatoriDlg(m_pEsamiView, FALSE).GetIDUtenteEndoxFromMediciID(m_ctrlComboUtenteSearch.GetItemData(m_ctrlComboUtenteSearch.GetCurSel())));

		ComponiRicercaEx(pStrWhere, m_ctrlDataOraSearch.m_strRicerca, "EEsami.DataOraSuperLock", FALSE, TRUE);
		// Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
		if (strIDUtente == "= 0" || strIDUtente == "")
		{
		}
		else
		{
			ComponiRicercaEx(pStrWhere, strIDUtente, "EEsami.IdUtenteSuperLock", FALSE, TRUE);
		}
		break;
	}
	case btn_convalida:
	{
		CString strIDUtente;
		if (m_ctrlComboUtenteSearch.GetCurSel() >= 0)
			strIDUtente.Format("= %li", COperatoriDlg(m_pEsamiView, FALSE).GetIDUtenteEndoxFromMediciID(m_ctrlComboUtenteSearch.GetItemData(m_ctrlComboUtenteSearch.GetCurSel())));

		ComponiRicercaEx(pStrWhere, m_ctrlDataOraSearch.m_strRicerca, "EEsami.DataOraLock", FALSE, TRUE);
		// Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
		if (strIDUtente == "= 0" || strIDUtente == "")
		{
		}
		else
		{
			ComponiRicercaEx(pStrWhere, strIDUtente, "EEsami.IdUtenteLock", FALSE, TRUE);
		}
		break;
	}
	}

	return 1;
}


LRESULT CButtonDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == TRUE)
	{
		if (!m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
			wParam = FALSE;
	}
	else
	{
		if (!(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
			wParam = TRUE;
	}

	if (!((BOOL)wParam)) // sto entrando il modalità "editing"
	{
		switch (m_lContenuto)
		{
		case btn_convalida:
		case btn_chiusuraesame:
		{
			if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0) //modifica esame
			{
				m_ctrlDataOraSearch.EnableWindow(FALSE);
				m_ctrlDataOraSearch.SetReadOnly(TRUE);
				m_ctrlDataOraSearch.ShowWindow(SW_HIDE);

				m_ctrlComboUtenteSearch.EnableWindow(FALSE);
				m_ctrlComboUtenteSearch.ShowWindow(SW_HIDE);

				m_ctrlStaticSearch1.ShowWindow(SW_HIDE);
				m_ctrlStaticSearch2.ShowWindow(SW_HIDE);

				GetDlgItem(IDC_BUTTON)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_EDIT_SEARCH)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO_USER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_HIDE);
			}
			else // ricerca
			{
				m_ctrlDataOraSearch.EnableWindow(TRUE);
				m_ctrlDataOraSearch.SetReadOnly(FALSE);
				m_ctrlDataOraSearch.ShowWindow(SW_SHOW);

				m_ctrlComboUtenteSearch.EnableWindow(TRUE);
				m_ctrlComboUtenteSearch.ShowWindow(SW_SHOW);

				m_ctrlStaticSearch1.ShowWindow(SW_SHOW);
				m_ctrlStaticSearch2.ShowWindow(SW_SHOW);

				GetDlgItem(IDC_BUTTON)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT_SEARCH)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_COMBO_USER)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_SHOW);
			}
		}		
		}
	}

	switch(m_lContenuto)
	{
		case btn_convalida:
		{
			//if (!m_pEsamiView->m_pEsamiSet->m_bLocked)
			GetDlgItem(IDC_BUTTON)->EnableWindow(!wParam && !m_pEsamiView->m_pEsamiSet->m_bLocked && m_pEsamiView->m_bEsamiValid && !m_pEsamiView->m_bEsamiBusy && !m_pEsamiView->m_bPazientiBusy && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto);
			//else
				//GetDlgItem(IDC_BUTTON)->EnableWindow(FALSE);
			break;
		}
		case btn_chiusuraesame:
		{
			//if (!m_pEsamiView->m_pEsamiSet->m_bSuperLocked)
			GetDlgItem(IDC_BUTTON)->EnableWindow(!wParam && !m_pEsamiView->m_pEsamiSet->m_bSuperLocked && m_pEsamiView->m_bEsamiValid && !m_pEsamiView->m_bEsamiBusy && !m_pEsamiView->m_bPazientiBusy && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto);
			//else
				//GetDlgItem(IDC_BUTTON)->EnableWindow(FALSE);
			break;
		}
		case btn_libera_laudo: // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
		{
			GetDlgItem(IDC_BUTTON)->EnableWindow(!wParam && m_pEsamiView->m_bEsamiValid && !m_pEsamiView->m_bEsamiBusy && !m_pEsamiView->m_bPazientiBusy && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto);
			break;
		}
		case btn_videocapsula:
		{
			//long idVideocapsula = CEsamiSet().GetIDVideocapsula(m_pEsamiView->m_pEsamiSet->m_lContatore);
			GetDlgItem(IDC_BUTTON)->EnableWindow(!wParam && m_pEsamiView->m_bEsamiValid && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto); //&& !CExtEsamiVideocapsulaSet().IsInviata(idVideocapsula));
			break;
		}
		case btn_liberotastostampa000:
		case btn_liberotastostampa001:
		case btn_liberotastostampa002:
		case btn_liberotastostampa003:
		case btn_liberotastostampa004:
		case btn_liberotastostampa005:
		case btn_liberotastostampa006:
		case btn_liberotastostampa007:
		case btn_liberotastostampa008:
		case btn_liberotastostampa009:
		case btn_liberotastostampa010:
		case btn_liberotastostampa011:
		case btn_liberotastostampa012:
		case btn_liberotastostampa013:
		case btn_liberotastostampa014:
		case btn_liberotastostampa015:
		case btn_liberotastostampa016:
		case btn_liberotastostampa017:
		case btn_liberotastostampa018:
		case btn_liberotastostampa019:
		{
			// Sandro 15/05/2015 // l'eventuale blocco per convalida o chiusura viene esaminato dopo (vedi sotto) per evitare di modificare la "logica" di funzionamento del tasto //
			GetDlgItem(IDC_BUTTON)->EnableWindow((theApp.m_dwPrivileges & AMLogin_Permissions::printout) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto && m_pEsamiView->m_bEsamiValid && !m_pEsamiView->m_bEsamiBusy && !m_pEsamiView->m_bPazientiBusy);
			break;
		}
		case btn_liberotastobrowser000:
		case btn_liberotastobrowser001:
		case btn_liberotastobrowser002:
		case btn_liberotastobrowser003:
		case btn_liberotastobrowser004:
		case btn_liberotastobrowser005:
		case btn_liberotastobrowser006:
		case btn_liberotastobrowser007:
		case btn_liberotastobrowser008:
		case btn_liberotastobrowser009:
		case btn_liberotastobrowser010:
		case btn_liberotastobrowser011:
		case btn_liberotastobrowser012:
		case btn_liberotastobrowser013:
		case btn_liberotastobrowser014:
		case btn_liberotastobrowser015:
		case btn_liberotastobrowser016:
		case btn_liberotastobrowser017:
		case btn_liberotastobrowser018:
		case btn_liberotastobrowser019:
		{
			// Sandro 15/05/2015 // l'eventuale blocco per convalida o chiusura viene esaminato dopo (vedi sotto) per evitare di modificare la "logica" di funzionamento del tasto //
			break;
		}
		case btn_liberotastoeseguibile000:
		case btn_liberotastoeseguibile001:
		case btn_liberotastoeseguibile002:
		case btn_liberotastoeseguibile003:
		case btn_liberotastoeseguibile004:
		case btn_liberotastoeseguibile005:
		case btn_liberotastoeseguibile006:
		case btn_liberotastoeseguibile007:
		case btn_liberotastoeseguibile008:
		case btn_liberotastoeseguibile009:
		case btn_liberotastoeseguibile010:
		case btn_liberotastoeseguibile011:
		case btn_liberotastoeseguibile012:
		case btn_liberotastoeseguibile013:
		case btn_liberotastoeseguibile014:
		case btn_liberotastoeseguibile015:
		case btn_liberotastoeseguibile016:
		case btn_liberotastoeseguibile017:
		case btn_liberotastoeseguibile018:
		case btn_liberotastoeseguibile019:
		{
			// Sandro 15/05/2015 // l'eventuale blocco per convalida o chiusura viene esaminato dopo (vedi sotto) per evitare di modificare la "logica" di funzionamento del tasto //
			break;
		}
		case btn_centralerefertazione:
		{
			if (m_pEsamiView->m_pEsamiSet->m_lStatoInvioCentraleRefertaz == StatoInvioCentraleRefertazione::crNonInviare)
				m_ctrlButtonCentraleRefertazione.EnableWindow(m_pEsamiView->m_bEsamiValid && !m_pEsamiView->m_bEsamiBusy && !m_pEsamiView->m_bPazientiBusy && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto && m_pEsamiView->m_pEsamiSet->m_lStatoInvioAltraUnita == 0); //Gabriel - TCP
			else
				m_ctrlButtonCentraleRefertazione.EnableWindow(FALSE);
			break;
		}
		case btn_carestream:
		{
			m_ctrlButtonCarestream.EnableWindow(TRUE);
			break;
		}
		case btn_liberotastochiusurafase000:
		case btn_liberotastochiusurafase001:
		case btn_liberotastochiusurafase002:
		case btn_liberotastochiusurafase003:
		case btn_liberotastochiusurafase004:
		case btn_liberotastochiusurafase005:
		case btn_liberotastochiusurafase006:
		case btn_liberotastochiusurafase007:
		case btn_liberotastochiusurafase008:
		case btn_liberotastochiusurafase009:
		case btn_liberotastochiusurafase010:
		case btn_liberotastochiusurafase011:
		case btn_liberotastochiusurafase012:
		case btn_liberotastochiusurafase013:
		case btn_liberotastochiusurafase014:
		case btn_liberotastochiusurafase015:
		case btn_liberotastochiusurafase016:
		case btn_liberotastochiusurafase017:
		case btn_liberotastochiusurafase018:
		case btn_liberotastochiusurafase019:
		{	
			long idFaseAppartenenza = theApp.m_lIdFaseTastoChiusuraFase[m_lContenuto - btn_liberotastochiusurafase000];
			GetDlgItem(IDC_BUTTON)->EnableWindow(!wParam && !m_pEsamiView->IsFaseChiusa(idFaseAppartenenza) && m_pEsamiView->m_bEsamiValid && !m_pEsamiView->m_bEsamiBusy && !m_pEsamiView->m_bPazientiBusy && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto);
			break;
		}
		//Gabriel - TCP
		case btn_invia_altra_unita:
		{
			if (theApp.m_bAtivaTCP)
			{
				if (m_pEsamiView->IsTCP())
				{
					m_ctrlButtonInviaAltraUnita.ShowWindow(TRUE);
					if (m_pEsamiView->m_pEsamiSet->m_lStatoInvioAltraUnita == StatoInvioAltraUnita::auNonInviare)
						m_ctrlButtonInviaAltraUnita.EnableWindow(TRUE);
					else
						m_ctrlButtonInviaAltraUnita.EnableWindow(FALSE);
				}
				else
					m_ctrlButtonInviaAltraUnita.ShowWindow(FALSE);
			}
			else
				m_ctrlButtonInviaAltraUnita.ShowWindow(FALSE);
			break;
		}
		default:
		{
			GetDlgItem(IDC_BUTTON)->EnableWindow(!(BOOL)wParam);
			break;
		}
	}

	//Devo controllare se disabilitare il tasto verificando le fasi gestibili dall'utente
	switch (m_lContenuto)
	{
		case btn_convalida:
		{
#ifndef _DEBUG
			if (theApp.m_listUserPhases.Find(CO_FASE_CONVALIDA) == NULL)
				GetDlgItem(IDC_BUTTON)->EnableWindow(FALSE);
#endif
			break;
		}
		case btn_chiusuraesame:
		{
#ifndef _DEBUG
			if (theApp.m_listUserPhases.Find(CO_FASE_CHIUSURA_STAMPA) == NULL)
				GetDlgItem(IDC_BUTTON)->EnableWindow(FALSE);
#endif
			break;
		}
		// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
		case btn_libera_laudo:
		{
#ifndef _DEBUG
			if (theApp.m_listUserPhases.Find(CO_FASE_LIBERA_LAUDO) == NULL)
				GetDlgItem(IDC_BUTTON)->EnableWindow(FALSE);
#endif
			break;
		}
		case btn_liberotastochiusurafase000:
		case btn_liberotastochiusurafase001:
		case btn_liberotastochiusurafase002:
		case btn_liberotastochiusurafase003:
		case btn_liberotastochiusurafase004:
		case btn_liberotastochiusurafase005:
		case btn_liberotastochiusurafase006:
		case btn_liberotastochiusurafase007:
		case btn_liberotastochiusurafase008:
		case btn_liberotastochiusurafase009:
		case btn_liberotastochiusurafase010:
		case btn_liberotastochiusurafase011:
		case btn_liberotastochiusurafase012:
		case btn_liberotastochiusurafase013:
		case btn_liberotastochiusurafase014:
		case btn_liberotastochiusurafase015:
		case btn_liberotastochiusurafase016:
		case btn_liberotastochiusurafase017:
		case btn_liberotastochiusurafase018:
		case btn_liberotastochiusurafase019:
		{
			long idFaseAppartenenza = theApp.m_lIdFaseTastoChiusuraFase[m_lContenuto - btn_liberotastochiusurafase000];
			if (theApp.m_listUserPhases.Find(idFaseAppartenenza) == NULL)
				GetDlgItem(IDC_BUTTON)->EnableWindow(FALSE);

			break;
		}
	}

	/*if ((m_lContenuto != btn_convalida) && (m_lContenuto != btn_chiusuraesame) && (m_lContenuto != btn_priamo) && (m_lContenuto != btn_centralerefertazione))
	{
		if ((m_pEsamiView->m_pEsamiSet->m_bLocked == TRUE) && (m_lIDFaseBlocco <= 0)) // Davide - in ricerca m_bLocked è uguale a 2
			GetDlgItem(IDC_BUTTON)->EnableWindow(FALSE);

		if ((m_pEsamiView->m_pEsamiSet->m_bSuperLocked == TRUE) && (m_lIDFaseBlocco <= 1)) // Sandro // in ricerca m_bSuperLocked è uguale a 2 //
			GetDlgItem(IDC_BUTTON)->EnableWindow(FALSE);
	}*/

	//

	return 1;
}

void CButtonDynForm::OnClickButton() 
{
	if (theApp.m_nProgramMode & ADD_RECORD_ESAMI || theApp.m_nProgramMode & MODIFY_RECORD_ESAMI || theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		switch(m_lContenuto)
		{
			case btn_osservazioni:
			{
				m_ctrlButtonOsservazioni.SetCheck(BST_UNCHECKED);

				m_pEsamiView->UpdateData(TRUE);

				CMstOsservazioniUseDlg dlg(this, m_pEsamiView);
				if (dlg.DoModal() == IDOK)
					m_pEsamiView->UpdateData(FALSE);
				
				break;
			}
			case btn_diagnostiche:
			{
				m_ctrlButtonDiagnostiche.SetCheck(BST_UNCHECKED);

				m_pEsamiView->UpdateData(TRUE);

				CMstProcedureDiagnosticheUseDlg dlg(this, m_pEsamiView);
				dlg.SetValue(m_pEsamiView->m_pEsamiSet->m_sProcDiagnostiche);

				if (dlg.DoModal() == IDOK)
				{
					m_pEsamiView->m_pEsamiSet->m_sProcDiagnostiche = dlg.GetValue();
					m_pEsamiView->UpdateData(FALSE);
				}

				break;
			}
			case btn_terapeutiche:
			{
				m_ctrlButtonTerapeutiche.SetCheck(BST_UNCHECKED);

				m_pEsamiView->UpdateData(TRUE);

				CMstProcedureTerapeuticheUseDlg dlg(this, m_pEsamiView);
				dlg.SetValue(m_pEsamiView->m_pEsamiSet->m_sProcTerapeutiche);

				if (dlg.DoModal() == IDOK)
				{
					m_pEsamiView->m_pEsamiSet->m_sProcTerapeutiche = dlg.GetValue();
					m_pEsamiView->UpdateData(FALSE);
				}

				break;
			}
			case btn_diagnosi:
			{
				m_ctrlButtonDiagnosi.SetCheck(BST_UNCHECKED);

				m_pEsamiView->UpdateData(TRUE);

				CMstDiagnosiUseDlg dlg(this, m_pEsamiView);
				if (dlg.DoModal() == IDOK)
					m_pEsamiView->UpdateData(FALSE);

				break;
			}
			case btn_codificadiagnosiesame:
			{
				m_ctrlButtonCodificaDiagnosiEsame.SetCheck(BST_UNCHECKED);

				m_pEsamiView->UpdateData(TRUE);

				CMstCodificaDiagnosiEsameUseDlg dlg(this, m_pEsamiView);

				if (dlg.DoModal() == IDOK)
					m_pEsamiView->UpdateData(FALSE);

				break;
			}
			case btn_codificadiagnosiesame5righe:
			{
				m_ctrlButtonCodificaDiagnosiEsame.SetCheck(BST_UNCHECKED);

				m_pEsamiView->UpdateData(TRUE);

				CMstCodificaDiagnosiEsame5RigheUseDlg dlg(this, m_pEsamiView);

				if (dlg.DoModal() == IDOK)
					m_pEsamiView->UpdateData(FALSE);

				break;
			}

			case btn_complicanze1:
			{
				m_ctrlButtonComplicanze1.SetCheck(BST_UNCHECKED);

				m_pEsamiView->UpdateData(TRUE);

				CMstComplicanze1UseDlg dlg(this, m_pEsamiView);
				dlg.SetValue(m_pEsamiView->m_pEsamiSet->m_sMstComplicanze1);

				if (dlg.DoModal() == IDOK)
				{
					m_pEsamiView->m_pEsamiSet->m_sMstComplicanze1 = dlg.GetValue();
					m_pEsamiView->UpdateData(FALSE);
				}

				break;
			}
			case btn_complicanze2:
			{
				m_ctrlButtonComplicanze2.SetCheck(BST_UNCHECKED);

				m_pEsamiView->UpdateData(TRUE);

				CMstComplicanze2UseDlg dlg(this, m_pEsamiView);
				dlg.SetValue(m_pEsamiView->m_pEsamiSet->m_sMstComplicanze2);

				if (dlg.DoModal() == IDOK)
				{
					m_pEsamiView->m_pEsamiSet->m_sMstComplicanze2 = dlg.GetValue();
					m_pEsamiView->UpdateData(FALSE);
				}

				break;
			}
			case btn_complicanze3:
			{
				m_ctrlButtonComplicanze3.SetCheck(BST_UNCHECKED);

				m_pEsamiView->UpdateData(TRUE);

				CMstComplicanze3UseDlg dlg(this, m_pEsamiView);
				dlg.SetValue(m_pEsamiView->m_pEsamiSet->m_sMstComplicanze3);

				if (dlg.DoModal() == IDOK)
				{
					m_pEsamiView->m_pEsamiSet->m_sMstComplicanze3 = dlg.GetValue();
					m_pEsamiView->UpdateData(FALSE);
				}

				break;
			}
			
		}
	}

	switch(m_lContenuto)
	{
		case btn_convalida:	// BOTAO SALVAR LAUDO
		{
			m_ctrlButtonConvalida.SetCheck(BST_UNCHECKED);

			// Sandro 23/06/2017 //
			if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (!m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() && m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito != "1"))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito + ".");
				return;
			}

			// Invio alle checklist l'input di salvarsi
			for (int i = sub_gridcl000; i <= sub_gridcl039; i++)
				if (m_pEsamiView->m_pDynForm[i] != NULL)
					m_pEsamiView->m_pDynForm[i]->SendMessage(MSG_FORM_SAVE);

			//
			m_pEsamiView->ChiudiFase(CO_FASE_CONVALIDA);

			// Marvel Carvalho - BUG 4621 Pop up central de laudos
			if (theApp.m_bPopupCentralDeLaudos)
			{
				DoCentraleRefertazione();
			}

			break;
		}
		case btn_chiusuraesame:	// BOTAO ASSINAR LAUDO
		{			
			m_ctrlButtonChiusuraEsame.SetCheck(BST_UNCHECKED);

			//Felipe - 01/09/2022
			if (theApp.m_bConfermareGliEsamiSenzaAttaccamentoOImmagini && theApp.m_bPersonalizzazioniBrasileFleury)
			{
				// não verificar pasta amarela - documentos não serão exportados
				// int iTotalAnexos = m_pDocManager->GetAttachedDocNumberExam(m_pEsamiSet->m_lContatore, DOCUMENTS_NOT_EXPORT); 
				int iTotalAnexos = m_pEsamiView->m_pDocManager->GetAttachedDocNumberExam(m_pEsamiView->m_pEsamiSet->m_lContatore, DOCUMENTS_ONLY_EXPORT);

				CImgList listImg;
				if (m_pEsamiView->m_pImgManager->GetImgList(&listImg) == 0 && iTotalAnexos == 0)
				{
					if (theApp.AfxMessageBoxEndo("Nenhum PDF ou IMAGEM encontrado anexado ao exame. Deseja assinar mesmo assim?", MB_YESNO) == IDNO)
					{
						return;
					}
					/*if (theApp.MessageBoxEndo(theApp.GetMessageString(IDS_FLEURY_CONFERMA_ESAMI_SENZA_ATTACCA_IMMAGI), theApp.GetMessageString(IDS_ACHTUNG), MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
						return;*/
				}
			}

			//BEGIN - BUG 9527 - Felipe (NewTCP)
			CString sigla;
			NeoConnection nc = NeoConnection();
			nc.ConnectionDatabase();
			CRecordset rs;
			nc.Select("select * from EXT_PRESTAZIONI where IDPRESTAZIONE = '" + m_pEsamiView->m_pEsamiSet->m_sCodEsame + "'", rs);

			if (rs.GetRecordCount() != 0) {
				rs.GetFieldValue("CODICEPRESTAZIONE", sigla);
			}

			if (theApp.m_lUO == 7 && theApp.m_bAtivaTCP == 1 && (sigla == "TCP" || sigla == "TCPCICLO" || sigla == "TCPMIB"))
			{
				CSendPneuDLG open;
				open.DoModal();
				if (open.IsCancel)
					return;

				//Caso escolha com Pneu, enviar para outra unidade
				if (open.IsWithPneu)
				{
					InviaAltraUnita();
					AfxMessageBox("Exame enviado para Pneumologia.");
					return;
				}

			}
			//END - BUG 9527 - Felipe (NewTCP)

			


			// Sandro 23/06/2017 //
			if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (!m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() && m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito != "-1"))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito + ".");
				return;
			}

			// Invio alle checklist l'input di salvarsi
			for (int i = sub_gridcl000; i <= sub_gridcl039; i++)
				if (m_pEsamiView->m_pDynForm[i] != NULL)
					m_pEsamiView->m_pDynForm[i]->SendMessage(MSG_FORM_SAVE);

			//
			m_pEsamiView->ChiudiFase(CO_FASE_CHIUSURA_STAMPA);			

			break;
		}
		// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
		case btn_libera_laudo:
		{
			if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (!m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() && m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito != "1"))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito + ".");
				return;
			}

			for (int i = sub_gridcl000; i <= sub_gridcl039; i++)
				if (m_pEsamiView->m_pDynForm[i] != NULL)
					m_pEsamiView->m_pDynForm[i]->SendMessage(MSG_FORM_SAVE);

			m_pEsamiView->ChiudiFase(CO_FASE_LIBERA_LAUDO);

			break;
		}
		case btn_videocapsula:
		{
			m_ctrlButtonVideocapsula.SetCheck(BST_UNCHECKED);

			if (theApp.AfxMessageBoxEndo(IDS_INVIAAVIDEOCAPSULA, MB_YESNO) == IDYES)
			{
				long userId;
				AMLogin_GetUserID(&userId);

				CExtEsamiVideocapsulaSet().InserisciRecord(m_pEsamiView->m_pEsamiSet->m_lContatore, userId);
			}
			
			break;
		}
		case btn_liberotastostampa000:
		case btn_liberotastostampa001:
		case btn_liberotastostampa002:
		case btn_liberotastostampa003:
		case btn_liberotastostampa004:
		case btn_liberotastostampa005:
		case btn_liberotastostampa006:
		case btn_liberotastostampa007:
		case btn_liberotastostampa008:
		case btn_liberotastostampa009:
		case btn_liberotastostampa010:
		case btn_liberotastostampa011:
		case btn_liberotastostampa012:
		case btn_liberotastostampa013:
		case btn_liberotastostampa014:
		case btn_liberotastostampa015:
		case btn_liberotastostampa016:
		case btn_liberotastostampa017:
		case btn_liberotastostampa018:
		case btn_liberotastostampa019:
		{
			m_ctrlButtonStampa[m_lContenuto - btn_liberotastostampa000].SetCheck(BST_UNCHECKED);

			CString sReport = theApp.m_sTastoStampaFile[m_lContenuto - btn_liberotastostampa000];
			if (sReport.GetLength() > 4)
			{
				long lPdfId = 0;
				if ((sReport.Right(3).CompareNoCase("RPT") == 0) || (sReport.Right(3).CompareNoCase("RPA") == 0))
					m_pEsamiView->AnteprimaStampaReport(STAMPA, theApp.m_bTastoStampaCheck[m_lContenuto - btn_liberotastostampa000], sReport, FALSE, 0, &lPdfId,""); // <-- PetrOne inserirà RAS per fare parametrizzabile anche il numero di copie da stampare //
				else
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REPORTESTENSIONEERRATA));
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REPORTNONASSOCIATO));
			}

			break;
		}
		case btn_liberotastobrowser000:
		case btn_liberotastobrowser001:
		case btn_liberotastobrowser002:
		case btn_liberotastobrowser003:
		case btn_liberotastobrowser004:
		case btn_liberotastobrowser005:
		case btn_liberotastobrowser006:
		case btn_liberotastobrowser007:
		case btn_liberotastobrowser008:
		case btn_liberotastobrowser009:
		case btn_liberotastobrowser010:
		case btn_liberotastobrowser011:
		case btn_liberotastobrowser012:
		case btn_liberotastobrowser013:
		case btn_liberotastobrowser014:
		case btn_liberotastobrowser015:
		case btn_liberotastobrowser016:
		case btn_liberotastobrowser017:
		case btn_liberotastobrowser018:
		case btn_liberotastobrowser019:
		{
			m_ctrlButtonBrowser[m_lContenuto - btn_liberotastobrowser000].SetCheck(BST_UNCHECKED);

			CString sURL = theApp.m_sTastoBrowserIndirizzo[m_lContenuto - btn_liberotastobrowser000];
			if (!sURL.IsEmpty())
			{
				USES_CONVERSION;
				if (IsValidURL(NULL, T2W(sURL), 0) == S_OK)
				{
					int iReturn = (int)ShellExecute(NULL, "open", sURL, NULL, NULL, SW_SHOWMAXIMIZED);
				}
				else
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_URLNONVALIDA));
				}
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_URLNONASSOCIATA));
			}

			break;
		}
		case btn_liberotastoeseguibile000:
		case btn_liberotastoeseguibile001:
		case btn_liberotastoeseguibile002:
		case btn_liberotastoeseguibile003:
		case btn_liberotastoeseguibile004:
		case btn_liberotastoeseguibile005:
		case btn_liberotastoeseguibile006:
		case btn_liberotastoeseguibile007:
		case btn_liberotastoeseguibile008:
		case btn_liberotastoeseguibile009:
		case btn_liberotastoeseguibile010:
		case btn_liberotastoeseguibile011:
		case btn_liberotastoeseguibile012:
		case btn_liberotastoeseguibile013:
		case btn_liberotastoeseguibile014:
		case btn_liberotastoeseguibile015:
		case btn_liberotastoeseguibile016:
		case btn_liberotastoeseguibile017:
		case btn_liberotastoeseguibile018:
		case btn_liberotastoeseguibile019:
		{
			m_ctrlButtonEseguibile[m_lContenuto - btn_liberotastoeseguibile000].SetCheck(BST_UNCHECKED);

			CString sEseguibile = theApp.m_sTastoEseguibileFile[m_lContenuto - btn_liberotastoeseguibile000];
			if (sEseguibile.GetLength() > 4)
			{
				STARTUPINFO si;
				PROCESS_INFORMATION pi;

				ZeroMemory(&si, sizeof(si));
				si.cb = sizeof(si);
				ZeroMemory(&pi, sizeof(pi));

				if (!CreateProcess(NULL, sEseguibile.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
				{
					LPVOID lpMsgBuf;
					if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
						theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
					else
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
					LocalFree(lpMsgBuf);
				}
				sEseguibile.ReleaseBuffer();

				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESEGUIBILENONASSOCIATO));
			}

			break;
		}
		case btn_centralerefertazione:
		{
			m_ctrlButtonCentraleRefertazione.SetCheck(BST_UNCHECKED);

			// Sandro 23/06/2017 //
			if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (!m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() && m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito != "-1"))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito + ".");
				return;
			}

			// Marvel Carvalho - BUG 4621 Pop up central de laudos
			DoCentraleRefertazione();
			break;
		}
		case btn_carestream:
		{
			m_ctrlButtonCarestream.SetCheck(BST_UNCHECKED);

			CString sAccessionNumber = "";
			switch (m_pEsamiView->m_pEsamiSet->m_sCodEsame.GetLength())
			{
				case 14:
				{
					sAccessionNumber = m_pEsamiView->m_pEsamiSet->m_sCodEsame.Left(10) + "000" + m_pEsamiView->m_pEsamiSet->m_sCodEsame.Mid(11, 1) + "00";
					break;
				}
				case 15:
				{
					sAccessionNumber = m_pEsamiView->m_pEsamiSet->m_sCodEsame.Left(10) + "00" + m_pEsamiView->m_pEsamiSet->m_sCodEsame.Mid(11, 2) + "00";
					break;
				}
				default:
				{
					ASSERT(FALSE);

					sAccessionNumber = m_pEsamiView->m_pEsamiSet->m_sCodEsame;
					break;
				}
			}

			// chiamata a carestream //
			CString sURL;
			// sURL.Format("http://192.168.220.12?user_name=Tesi&password=t&s!@2016&patient_id=%s&accession_number=%s", m_pEsamiView->m_pPazientiSet->m_sAssIden, sAccessionNumber); // Sandro 24/11/2016 //
			sURL.Format("https://pacs.fleury.com.br/?user_name=tesi&password=t$s!2016&accession_number=%s&signout=false&key_images=true", sAccessionNumber);
			if (!sURL.IsEmpty())
			{
				USES_CONVERSION;
				if (IsValidURL(NULL, T2W(sURL), 0) == S_OK)
				{
					CString sChromeExe = RegistryGetStringValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\chrome.exe", "");

					if (sChromeExe.IsEmpty())
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CHROMENONTROVATO));

						ShellExecute(NULL, "open", sURL, NULL, NULL, SW_SHOWMAXIMIZED);
					}
					else
					{
						char szProcess[4096];
						sprintf_s(szProcess, "%s --app=\"%s\"", sChromeExe, sURL);

						STARTUPINFO si;
						PROCESS_INFORMATION pi;

						ZeroMemory(&si, sizeof(si));
						si.cb = sizeof(si);
						ZeroMemory(&pi, sizeof(pi));

						if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
						{
							LPVOID lpMsgBuf;
							if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
								theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
							else
								theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
							LocalFree(lpMsgBuf);
						}
						else
						{
							CloseHandle(pi.hProcess);
							CloseHandle(pi.hThread);
						}
					}
				}
				else
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_URLNONVALIDA));
				}
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_URLNONASSOCIATA));
			}

			break;
		}
		case btn_liberotastochiusurafase000:
		case btn_liberotastochiusurafase001:
		case btn_liberotastochiusurafase002:
		case btn_liberotastochiusurafase003:
		case btn_liberotastochiusurafase004:
		case btn_liberotastochiusurafase005:
		case btn_liberotastochiusurafase006:
		case btn_liberotastochiusurafase007:
		case btn_liberotastochiusurafase008:
		case btn_liberotastochiusurafase009:
		case btn_liberotastochiusurafase010:
		case btn_liberotastochiusurafase011:
		case btn_liberotastochiusurafase012:
		case btn_liberotastochiusurafase013:
		case btn_liberotastochiusurafase014:
		case btn_liberotastochiusurafase015:
		case btn_liberotastochiusurafase016:
		case btn_liberotastochiusurafase017:
		case btn_liberotastochiusurafase018:
		case btn_liberotastochiusurafase019:
		{
			m_ctrlButtonChiusuraFase[m_lContenuto - btn_liberotastochiusurafase000].SetCheck(BST_UNCHECKED);

			// Sandro 23/06/2017 //
			if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (!m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() && m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito != "-1"))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito + ".");
				return;
			}

			// Invio alle checklist l'input di salvarsi
			for (int i = sub_gridcl000; i <= sub_gridcl039; i++)
				if (m_pEsamiView->m_pDynForm[i] != NULL)
					m_pEsamiView->m_pDynForm[i]->SendMessage(MSG_FORM_SAVE);
			//

			long idFaseAppartenenza = theApp.m_lIdFaseTastoChiusuraFase[m_lContenuto - btn_liberotastochiusurafase000];
			m_pEsamiView->ChiudiFase(idFaseAppartenenza);
			SetButtonText();
			break;
		}

		//Gabriel - TCP
		case btn_invia_altra_unita:
		{
			if (theApp.m_bAtivaTCP)
			{
				m_ctrlButtonInviaAltraUnita.SetCheck(BST_UNCHECKED);

				// Sandro 23/06/2017 //
				if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (!m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() && m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito != "-1"))
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito + ".");
					return;
				}

				InviaAltraUnita();
				//m_ctrlButtonInviaAltraUnita.SetCheck(BST_CHECKED);
			}
			break;
		}
	}
}


// Marvel Carvalho - BUG 4621 Pop up central de laudos
BOOL CButtonDynForm::DoCentraleRefertazione()
{
	BOOL bResultDone = FALSE;

	if (m_pEsamiView->VerificaCampiObbligatoriFase(CO_FASE_CHIUSURA_STAMPA))
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_INVIOACENTRALE_CONFERMA), MB_YESNO) == IDYES)
		{
			bResultDone = TRUE;
			//
			BeginWaitCursor();

			// Invio alle checklist l'input di salvarsi
			for (int i = sub_gridcl000; i <= sub_gridcl039; i++)
				if (m_pEsamiView->m_pDynForm[i] != NULL)
					m_pEsamiView->m_pDynForm[i]->SendMessage(MSG_FORM_SAVE);

			// inserisco una riga nella tabella EXT_ESAMI_REFERTAZIONEREMOTA //
			long userId;
			AMLogin_GetUserID(&userId);

			//Gabriel BUG 6225 - Lista DO
			if (m_pEsamiView->m_lNumDocumentsExam == 0 && theApp.m_bImportazioneAutomaticaRicetta)
			{
				m_pEsamiView->OnEsameAllegatiCentralizzazione();
			}
			if (CEsamiRefertazioneRemotaSet().InserisciRecord(m_pEsamiView->m_pEsamiSet->m_lContatore, userId))
			{				
				// flaggo l'esame //
				m_pEsamiView->m_pEsamiSet->FlaggaEsameInviareCentraleRefertazione();

				// aggiorno l'interfaccia //
				m_pEsamiView->UpdateData(FALSE);

				// Sandro 17/10/2016 // RIMA 16037 RN43 // esame coniugato //
				if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
				{
					if (CEsamiSet().IsConiugatoSecondario(m_pEsamiView->m_pEsamiSet->m_lContatore))
					{
						CString sFilter;
						sFilter.Format("CODESAME='%s'", m_pEsamiView->m_pEsamiSet->m_sRefertoConiugatoPrincipale);

						CEsamiSet setTeeeeemp;
						setTeeeeemp.SetBaseFilter("(UO=0 OR UO>0)");
						setTeeeeemp.SetOpenFilter(sFilter);

						if (setTeeeeemp.OpenRecordset("CButtonDynForm::OnClickButton"))
						{
							if (!setTeeeeemp.IsEOF())
							{
								// flaggo l'esame //
								if (setTeeeeemp.EditRecordset("CButtonDynForm::OnClickButton"))
								{
									setTeeeeemp.m_bSuperLocked = TRUE;
									setTeeeeemp.m_lIdUtenteSuperLock = userId;
									setTeeeeemp.m_sDataOraSuperLock = CTime::GetCurrentTime().Format("%Y%m%d%H%M%S");

									if (setTeeeeemp.m_sDataOraSuperLockPrimo.IsEmpty())
										setTeeeeemp.m_sDataOraSuperLockPrimo = setTeeeeemp.m_sDataOraSuperLock;

									CCustomDate customStart = CCustomDate(setTeeeeemp.m_lData);
									COleDateTime start = COleDateTime(customStart.GetYear(), customStart.GetMonth(), customStart.GetDay(), customStart.GetHour(), customStart.GetMinute(), 0);
									COleDateTime stop = COleDateTime(atoi(setTeeeeemp.m_sDataOraSuperLock.Left(4)),
										atoi(setTeeeeemp.m_sDataOraSuperLock.Mid(4, 2)),
										atoi(setTeeeeemp.m_sDataOraSuperLock.Mid(6, 2)),
										atoi(setTeeeeemp.m_sDataOraSuperLock.Mid(8, 2)),
										atoi(setTeeeeemp.m_sDataOraSuperLock.Mid(10, 2)),
										0); // non serve gestire i secondi perchè dataesame non li gestisce
									COleDateTimeSpan timeDiff = stop - start;

									CString result;
									result.Format("%02li:%02li:%02li", timeDiff.GetDays(), timeDiff.GetHours(), timeDiff.GetMinutes());
									setTeeeeemp.m_sTempoChiusura = result;

									setTeeeeemp.m_lStatoInvioCentraleRefertaz = StatoInvioCentraleRefertazione::crDaInviare;

									if (setTeeeeemp.UpdateRecordset("CButtonDynForm::OnClickButton"))
									{
										// flaggo la richiesta come refertata sulla worklist se esiste //
										CExtOrdiniSet().SetStatoRichiesta(setTeeeeemp.m_lContatore, LPC_STATO_REFERTATA);

										// inserisco una riga nella tabella EXT_ESAMI_REFERTAZIONEREMOTA //
										CEsamiRefertazioneRemotaSet().InserisciRecord(setTeeeeemp.m_lContatore, userId);
									}
								}
							}

							setTeeeeemp.CloseRecordset("CButtonDynForm::OnClickButton");
						}
					}
				}
			}

			//
			EndWaitCursor();
		}
	}
	return bResultDone;
}

long CButtonDynForm::GetContenuto()
{
	return m_lContenuto;
}

BOOL CButtonDynForm::CampoObbligatorioValido()
{
	switch(m_lContenuto)
	{
		case btn_convalida:
		{
			//return ((m_ctrlButtonConvalida.GetCheck() == BST_CHECKED) || m_bTastoConvalidaPremuto);
			return m_pEsamiView->m_pEsamiSet->m_bLocked;
			break;
		}
		case btn_chiusuraesame:
		{
			//return ((m_ctrlButtonChiusuraEsame.GetCheck() == BST_CHECKED) || m_bTastoChiusuraPremuto);
			return m_pEsamiView->m_pEsamiSet->m_bSuperLocked;
			break;
		}
		case btn_libera_laudo: // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
		{
			return TRUE;
			break;
		}
		case btn_liberotastochiusurafase000:
		case btn_liberotastochiusurafase001:
		case btn_liberotastochiusurafase002:
		case btn_liberotastochiusurafase003:
		case btn_liberotastochiusurafase004:
		case btn_liberotastochiusurafase005:
		case btn_liberotastochiusurafase006:
		case btn_liberotastochiusurafase007:
		case btn_liberotastochiusurafase008:
		case btn_liberotastochiusurafase009:
		case btn_liberotastochiusurafase010:
		case btn_liberotastochiusurafase011:
		case btn_liberotastochiusurafase012:
		case btn_liberotastochiusurafase013:
		case btn_liberotastochiusurafase014:
		case btn_liberotastochiusurafase015:
		case btn_liberotastochiusurafase016:
		case btn_liberotastochiusurafase017:
		case btn_liberotastochiusurafase018:
		case btn_liberotastochiusurafase019:
		{
			long idFaseAppartenenza = theApp.m_lIdFaseTastoChiusuraFase[m_lContenuto - btn_liberotastochiusurafase000];
			return m_pEsamiView->IsFaseChiusa(idFaseAppartenenza);
			break;
		}
	}

	return TRUE;
}

void CButtonDynForm::OnPaint()
{
	CPaintDC dc(this);

	if (m_crCampoObbligatorio > 0)
	{
		CRect rect;
		GetDlgItem(IDC_BUTTON)->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.InflateRect(2, 2);

		dc.FillSolidRect(rect.left, rect.top, rect.Width(), rect.Height(), m_crCampoObbligatorio);
	}
}

void CButtonDynForm::SetButtonText()
{
	switch(m_lContenuto)
	{
		case btn_convalida:
		{
			GetDlgItem(IDC_BUTTON)->SetFont(&theApp.m_fontBold);		
			if (m_pEsamiView->m_pEsamiSet->m_bLocked)
			{
				if (m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lIdUtenteLock) || m_pEsamiView->m_pEsamiSet->m_lIdUtenteLock == 0)
				{
					CString strButton;
					CString dataOraTemp = m_pEsamiView->m_pEsamiSet->m_sDataOraLock;
					CString dataOraConvalida;
					dataOraConvalida.Format(theApp.GetMessageString(IDS_DATAORA), dataOraTemp.Mid(6,2), dataOraTemp.Mid(4,2), dataOraTemp.Mid(0,4), dataOraTemp.Mid(8,2), dataOraTemp.Mid(10,2));
					strButton.Format("%s (%s) %s", theApp.GetMessageString(IDS_BTN_CONVALIDATO), theApp.GetMessageString(IDS_SCONOSCIUTO), dataOraConvalida);
					SetDlgItemText(IDC_BUTTON, strButton);					
				}
				else
				{
					CUtentiSet utentiSet;
					CString filter;
					filter.Format("ID = %li", m_pEsamiView->m_pEsamiSet->m_lIdUtenteLock);
					utentiSet.SetOpenFilter(filter);
					if (utentiSet.OpenRecordset("CButtonDynForm::OnInitDialog"))
					{
						CString strButton;
						CString dataOraTemp = m_pEsamiView->m_pEsamiSet->m_sDataOraLock;
						CString dataOraConvalida;

						// Sandro 14/11/2016 // richiesta telefonica di Pilotto //
						CString sUsername = utentiSet.m_sUsername;
						sUsername.Replace("FLEURY.COM.BR\\", "");

						//
						dataOraConvalida.Format(theApp.GetMessageString(IDS_DATAORA), dataOraTemp.Mid(6,2), dataOraTemp.Mid(4,2), dataOraTemp.Mid(0,4), dataOraTemp.Mid(8,2), dataOraTemp.Mid(10,2));
						strButton.Format("%s (%s) %s", theApp.GetMessageString(IDS_BTN_CONVALIDATO), sUsername, dataOraConvalida);
						SetDlgItemText(IDC_BUTTON, strButton);						
						utentiSet.CloseRecordset("CButtonDynForm::OnInitDialog");
					}
				}
			}
			else
			{
				SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_CONVALIDA));
			}
			break;
		}
		case btn_chiusuraesame:
		{
			GetDlgItem(IDC_BUTTON)->SetFont(&theApp.m_fontBold);			
			if (m_pEsamiView->m_pEsamiSet->m_bSuperLocked == TRUE) // Sandro // in ricerca m_bSuperLocked è uguale a 2 //
			{
				if (m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lIdUtenteSuperLock) || m_pEsamiView->m_pEsamiSet->m_lIdUtenteSuperLock == 0)
				{
					CString strButton;
					CString dataOraTemp = m_pEsamiView->m_pEsamiSet->m_sDataOraSuperLock;
					CString dataOraChiusuraEsame;
					dataOraChiusuraEsame.Format(theApp.GetMessageString(IDS_DATAORA), dataOraTemp.Mid(6,2), dataOraTemp.Mid(4,2), dataOraTemp.Mid(0,4), dataOraTemp.Mid(8,2), dataOraTemp.Mid(10,2));
					strButton.Format("%s (%s) %s", theApp.GetMessageString(IDS_BTN_CHIUSOESAME), theApp.GetMessageString(IDS_SCONOSCIUTO), dataOraChiusuraEsame);
					SetDlgItemText(IDC_BUTTON, strButton);					
				}
				else
				{
					CUtentiSet utentiSet;
					CString filter;
					filter.Format("ID = %li", m_pEsamiView->m_pEsamiSet->m_lIdUtenteSuperLock);
					utentiSet.SetOpenFilter(filter);
					if (utentiSet.OpenRecordset("CButtonDynForm::OnInitDialog"))
					{
						CString strButton;
						CString dataOraTemp = m_pEsamiView->m_pEsamiSet->m_sDataOraSuperLock;
						CString dataOraChiusuraEsame;
						dataOraChiusuraEsame.Format(theApp.GetMessageString(IDS_DATAORA), dataOraTemp.Mid(6,2), dataOraTemp.Mid(4,2), dataOraTemp.Mid(0,4), dataOraTemp.Mid(8,2), dataOraTemp.Mid(10,2));

						// Sandro 14/11/2016 // richiesta telefonica di Pilotto //
						CString sUsername = utentiSet.m_sUsername;
						sUsername.Replace("FLEURY.COM.BR\\", "");

						//
						if (m_pEsamiView->m_pEsamiSet->m_lStatoInvioCentraleRefertaz > 0)
							strButton.Format("%s %s (%s) %s", theApp.GetMessageString(IDS_HOST), theApp.GetMessageString(IDS_BTN_CHIUSOESAME), sUsername, dataOraChiusuraEsame);
						else
							strButton.Format("%s (%s) %s", theApp.GetMessageString(IDS_BTN_CHIUSOESAME), sUsername, dataOraChiusuraEsame);

						SetDlgItemText(IDC_BUTTON, strButton);
						utentiSet.CloseRecordset("CButtonDynForm::OnInitDialog");
					}
				}
			}
			else
			{
				SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_CHIUSURAESAME));
			}
			break;
		}
		case btn_videocapsula:
		{
			//if (m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lIDVideocapsulaRegistrata) || m_pEsamiView->m_pEsamiSet->m_lIDVideocapsulaRegistrata == 0)
			//{
				SetDlgItemText(IDC_BUTTON, theApp.GetMessageString(IDS_BTN_VIDEOCAPSULA));
			//}
			/*else
			{
				long idVideocapsula = CEsamiSet().GetIDVideocapsula(m_pEsamiView->m_pEsamiSet->m_lContatore);
				if (CExtEsamiVideocapsulaSet().IsInviata(idVideocapsula))
				{
					CString output;
					output.Format(theApp.GetMessageString(IDS_BTN_VIDEOCAPSULA_INVIATA), CExtEsamiVideocapsulaSet().GetSerialSensore(idVideocapsula));
					SetDlgItemText(IDC_BUTTON, output);
				}
				else
				{
					CString output;
					output.Format(theApp.GetMessageString(IDS_BTN_VIDEOCAPSULA_ANNULLA), CExtEsamiVideocapsulaSet().GetSerialSensore(idVideocapsula));
					SetDlgItemText(IDC_BUTTON, output);
				}
			}*/
			break;
		}
		case btn_liberotastochiusurafase000:
		case btn_liberotastochiusurafase001:
		case btn_liberotastochiusurafase002:
		case btn_liberotastochiusurafase003:
		case btn_liberotastochiusurafase004:
		case btn_liberotastochiusurafase005:
		case btn_liberotastochiusurafase006:
		case btn_liberotastochiusurafase007:
		case btn_liberotastochiusurafase008:
		case btn_liberotastochiusurafase009:
		case btn_liberotastochiusurafase010:
		case btn_liberotastochiusurafase011:
		case btn_liberotastochiusurafase012:
		case btn_liberotastochiusurafase013:
		case btn_liberotastochiusurafase014:
		case btn_liberotastochiusurafase015:
		case btn_liberotastochiusurafase016:
		case btn_liberotastochiusurafase017:
		case btn_liberotastochiusurafase018:
		case btn_liberotastochiusurafase019:
		{
			long idFaseAppartenenza = theApp.m_lIdFaseTastoChiusuraFase[m_lContenuto - btn_liberotastochiusurafase000];

			GetDlgItem(IDC_BUTTON)->SetFont(&theApp.m_fontBold);
			if (m_pEsamiView->IsFaseChiusa(idFaseAppartenenza)) // Sandro // in ricerca m_bSuperLocked è uguale a 2 //
			{
				CString sFilter;
				sFilter.Format("IDESAME=%li and IDFASE=%li", m_pEsamiView->m_pEsamiSet->m_lContatore, idFaseAppartenenza);
				CEsamiFasiChiuseSet set;
				set.SetOpenFilter(sFilter);
				set.SetSortRecord("ID DESC");

				if (set.OpenRecordset("CButtonDynForm::SetButtonText"))
				{
					if (!set.IsEOF())
					{
						long lIdUtente = set.m_lIDUtente;
						CString sDataOraTemp = set.m_sDataOra;

						if (lIdUtente > 0)
						{
							CUtentiSet utentiSet;
							CString filter;
							filter.Format("ID = %li", lIdUtente);
							utentiSet.SetOpenFilter(filter);
							if (utentiSet.OpenRecordset("CButtonDynForm::SetButtonText"))
							{
								CUtentiSet utentiSet;
								CString filter;
								filter.Format("ID = %li", lIdUtente);
								utentiSet.SetOpenFilter(filter);
								if (utentiSet.OpenRecordset("CButtonDynForm::SetButtonText"))
								{
									CString strButton;
									CString dataOraTemp = sDataOraTemp;
									CString dataOraChiusuraEsame;
									dataOraChiusuraEsame.Format(theApp.GetMessageString(IDS_DATAORA), dataOraTemp.Mid(6, 2), dataOraTemp.Mid(4, 2), dataOraTemp.Mid(0, 4), dataOraTemp.Mid(8, 2), dataOraTemp.Mid(10, 2));
									strButton.Format("%s (%s) %s", CFasiEsameSet().GetDescrizione(idFaseAppartenenza) + " " + theApp.GetMessageString(IDS_CHIUSO).MakeUpper(), utentiSet.m_sUsername, dataOraChiusuraEsame);
									SetDlgItemText(IDC_BUTTON, strButton);
									utentiSet.CloseRecordset("CButtonDynForm::SetButtonText");
								}

								utentiSet.CloseRecordset("CButtonDynForm::SetButtonText");
							}
						}
						else
						{
							CString strButton;
							CString dataOraTemp = sDataOraTemp;
							CString dataOraChiusuraEsame;
							dataOraChiusuraEsame.Format(theApp.GetMessageString(IDS_DATAORA), dataOraTemp.Mid(6, 2), dataOraTemp.Mid(4, 2), dataOraTemp.Mid(0, 4), dataOraTemp.Mid(8, 2), dataOraTemp.Mid(10, 2));
							strButton.Format("%s (%s) %s", CFasiEsameSet().GetDescrizione(idFaseAppartenenza) + " " + theApp.GetMessageString(IDS_CHIUSO).MakeUpper(), theApp.GetMessageString(IDS_SCONOSCIUTO), dataOraChiusuraEsame);
							SetDlgItemText(IDC_BUTTON, strButton);
						}
					}

					set.CloseRecordset("CButtonDynForm::SetButtonText");
				}
				
			}
			else
			{
				SetDlgItemText(IDC_BUTTON, theApp.m_sLabelTastoChiusuraFase[m_lContenuto - btn_liberotastochiusurafase000]);
			}
			break;
		}
	}	
}

//Gabriel - TCP
BOOL CButtonDynForm::InviaAltraUnita()
{
	BOOL bResultDone = FALSE;
	
	if (m_pEsamiView->m_pEsamiSet->m_bLocked)
	{
		long lUnitaId = 0;
		CInviaAltraUnitaDlg dlg(m_pEsamiView);

		/*if (dlg.DoModal() == IDOK)
			lUnitaId = dlg.GetSelectedUnita();*/

		lUnitaId = 460;//criar flag na na tabela configuracione

		if (lUnitaId > 0)
		{
			bResultDone = TRUE;
			//
			BeginWaitCursor();

			// Invio alle checklist l'input di salvarsi
			for (int i = sub_gridcl000; i <= sub_gridcl039; i++)
				if (m_pEsamiView->m_pDynForm[i] != NULL)
					m_pEsamiView->m_pDynForm[i]->SendMessage(MSG_FORM_SAVE);

			// inserisco una riga nella tabella EXT_ESAMI_INVIOALTRAUNITA //
			long userId;
			AMLogin_GetUserID(&userId);

			if (CEsamiInvioAltraUnitaSet().InserisciRecord(m_pEsamiView->m_pEsamiSet->m_lContatore, userId, lUnitaId))
			{
				CEsamiInvioAltraUnitaSet().SetIdPdf(m_pEsamiView->OnGeneraRefertoEsamePrincipale(), m_pEsamiView->m_pEsamiSet->m_lContatore);

				// flaggo l'esame //
				m_pEsamiView->m_pEsamiSet->FlaggaEsameInviaAltraUnita();

				// aggiorno l'interfaccia //
				m_pEsamiView->UpdateData(FALSE);
			}

			EndWaitCursor();
		}
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SAVE_BEFORE_SEND));
		return bResultDone;
	}

	return bResultDone;
}

void CButtonDynForm::OnCbnSelchangeComboUser()
{
	// TODO: Add your control notification handler code here
}
