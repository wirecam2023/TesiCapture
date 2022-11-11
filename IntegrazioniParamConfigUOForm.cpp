#include "stdafx.h"
#include "Endox.h"

#include "EsamiDoc.h"
#include "EsamiView.h"

#include "CodificaRegionaleExDlg.h"
#include "IntegrazioniParamConfigUOForm.h"
#include "IntegrazioniConfigurazioneModDlg.h"
#include "InviantiDlg.h"
#include "MediciCurantiInviantiDlg.h"
#include "OperatoriDlg.h"
#include "ProvenienzaDlg.h"
#include "RAODlg.h"
#include "SediSaleDlg.h"
#include "SorgentiStreamingConfigDlg.h"
#include "WorklistLayoutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CIntegrazioniParamConfigUOForm, CResizableDialog)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_BTN_WORKLIST, OnBnClickedBtnWorklist)
	ON_BN_CLICKED(IDC_BTN_OPERATORI, OnBnClickedBtnOperatori)
	ON_BN_CLICKED(IDC_BTN_MEDICI, OnBnClickedBtnMedici)
	ON_BN_CLICKED(IDC_BTN_MEDICI_INVIANTI, OnBnClickedBtnMediciInvianti)
	ON_BN_CLICKED(IDC_BTN_PROVENIENZA, OnBnClickedBtnProvenienza)
	ON_BN_CLICKED(IDC_BTN_PRESTAZIONI, OnBnClickedBtnPrestazioni)
	ON_BN_CLICKED(IDC_BTN_SEDI, OnBnClickedBtnSedi)
	ON_BN_CLICKED(IDC_BTN_REPARTI, OnBnClickedBtnReparti)
	ON_BN_CLICKED(IDC_CHK_ANAGRAFE_ATTIVO, OnBnClickedChkAnagrafeAttivo)
	ON_BN_CLICKED(IDC_CHK_WORKLIST, OnBnClickedChkWorklist)
	ON_BN_CLICKED(IDC_BTN_SORGENTISTREAMING, OnBnClickedBtnSorgentistreaming)
END_MESSAGE_MAP()

HBRUSH CIntegrazioniParamConfigUOForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CResizableDialog::OnCtlColor (pDC, pWnd, nCtlColor);	
	return hBrush;
}


CIntegrazioniParamConfigUOForm::CIntegrazioniParamConfigUOForm(CWnd* pParent, CIntegrazioniConfigurazioneModDlg* configDlg) : CResizableDialog(CIntegrazioniParamConfigUOForm::IDD, pParent)
{
	m_pConfigDlg = configDlg;

	CResizableDialog::Create(CIntegrazioniParamConfigUOForm::IDD, pParent->GetParent());	

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);
}

CIntegrazioniParamConfigUOForm::~CIntegrazioniParamConfigUOForm()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

void CIntegrazioniParamConfigUOForm::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_11, m_ctrlStatic11);
	DDX_Control(pDX, IDC_STATIC_12, m_ctrlStatic12);
	DDX_Control(pDX, IDC_STATIC_13, m_ctrlStatic13);
	DDX_Control(pDX, IDC_STATIC_14, m_ctrlStatic14);
	DDX_Control(pDX, IDC_STATIC_15, m_ctrlStatic15);
	DDX_Control(pDX, IDC_STATIC_16, m_ctrlStatic16);
	DDX_Control(pDX, IDC_STATIC_18, m_ctrlStatic18);
	DDX_Control(pDX, IDC_STATIC_19, m_ctrlStatic19);
	DDX_Control(pDX, IDC_STATIC_22, m_ctrlStatic22);

	DDX_Control(pDX, IDC_BTN_OPERATORI,			m_ctrlBtnOperatori);
	DDX_Control(pDX, IDC_BTN_MEDICI,			m_ctrlBtnMedici);
	DDX_Control(pDX, IDC_BTN_PROVENIENZA,		m_ctrlBtnProvenienza);
	DDX_Control(pDX, IDC_BTN_SORGENTISTREAMING,	m_ctrlBtnSorgentiStreaming);
	DDX_Control(pDX, IDC_BTN_PRESTAZIONI,		m_ctrlBtnPrestazioni);
	DDX_Control(pDX, IDC_BTN_REPARTI,			m_ctrlBtnReparti);
	DDX_Control(pDX, IDC_BTN_SEDI,				m_ctrlBtnSedi);
	DDX_Control(pDX, IDC_BTN_WORKLIST,			m_ctrlBtnWorklistLayout);
	DDX_Control(pDX, IDC_BTN_MEDICI_INVIANTI,	m_ctrlBtnMediciInvianti);

	DDX_Control(pDX, IDC_CHK_ANAGRAFE_ATTIVO,			m_ctrlChkAnagrafeAttiva);
	DDX_Control(pDX, IDC_CHK_ANAGRAFE_LOCKINSERT,		m_ctrlChkAnagrafeLockInserimento);
	DDX_Control(pDX, IDC_CHK_ANAGRAFE_SOLOCENTRALE,		m_ctrlChkAnagrafeSoloCentrale);
	DDX_Control(pDX, IDC_CHK_LOCK_ATTIVO,				m_ctrlChkLockAttivo);
	DDX_Control(pDX, IDC_CHK_WORKLIST,					m_ctrlChkWorklist);
	DDX_Control(pDX, IDC_CHK_WORKLIST_IBRIDA,			m_ctrlChkWorklistIbrida);

	DDX_Control(pDX, IDC_EDT_ANAGRAFE_IP,			m_ctrlEdtAnagrafeIP);
	DDX_Control(pDX, IDC_EDT_ANAGRAFE_PORT,			m_ctrlEdtAnagrafePorta);
	DDX_Control(pDX, IDC_EDT_QUERYMAN_URL,			m_ctrlEdtQuerymanUrl);

	DDX_Control(pDX, IDC_CMB_FIRMA,					m_ctrlCmbFirma);
	DDX_Control(pDX, IDC_CMB_WORKLIST_STATODEFAULT,	m_ctrlCmbWorklistStatoDefault);
	DDX_Control(pDX, IDC_CMB_WORKLIST_FOCUS,		m_ctrlCmbWorklistFocus);
	DDX_Control(pDX, IDC_CMB_DICOM_SMODE,			m_ctrlCmbDicomStoreMode);
}

BOOL CIntegrazioniParamConfigUOForm::OnInitDialog()
{
	CResizableDialog::OnInitDialog();	
	
	LoadAnagrafeCentrale();
	LoadServer();
	LoadLock();
	LoadFirma();
	LoadQueryman();
	LoadWorklist();
	LoadDicom();

	theApp.LocalizeDialog(this, CIntegrazioniParamConfigUOForm::IDD, "IntegrazioniParamConfigUOForm");
	return TRUE;
}

void CIntegrazioniParamConfigUOForm::LoadAnagrafeCentrale()
{
	m_ctrlEdtAnagrafeIP.SetWindowText(theApp.m_sTesiAtdNetIndirizzo);
	CString temp;
	temp.Format("%li", theApp.m_nTesiAtdNetPorta);
	m_ctrlEdtAnagrafePorta.SetWindowText(temp);

	VerifyAnagrafeOptions();
}

void CIntegrazioniParamConfigUOForm::LoadServer()
{
	/*m_ctrlChkServerGestioneRicAcq.SetCheck((theApp.m_bIntegrazioneGestioneRichiesteAcquisite==TRUE?BST_CHECKED:BST_UNCHECKED));
	m_ctrlChkServerImmaginibin.SetCheck((theApp.m_bIntegrazioneInvioImmaginiBinarie==TRUE?BST_CHECKED:BST_UNCHECKED));
	m_ctrlChkServerInvioRefAnnull.SetCheck((theApp.m_bIntegrazioneInvioRefertiAnnullati==TRUE?BST_CHECKED:BST_UNCHECKED));
	m_ctrlChkServerInvioRefFiller.SetCheck((theApp.m_bIntegrazioneInvioRefertiDalFiller==TRUE?BST_CHECKED:BST_UNCHECKED));*/
}

void CIntegrazioniParamConfigUOForm::LoadLock()
{
	m_ctrlChkLockAttivo.SetCheck((theApp.m_bLockServerAttivo==TRUE?BST_CHECKED:BST_UNCHECKED));
	
}

void CIntegrazioniParamConfigUOForm::LoadFirma()
{
	int disabled = m_ctrlCmbFirma.InsertString(0, theApp.GetMessageString(IDS_FIRMA_DISABLED));
	m_ctrlCmbFirma.SetItemData(disabled, CEndoxApp::sign_disabled);
	int comped = m_ctrlCmbFirma.InsertString(1, theApp.GetMessageString(IDS_FIRMA_COMPED));
	m_ctrlCmbFirma.SetItemData(comped, CEndoxApp::sign_comped);

	switch(theApp.m_enumFirmaDigitale)
	{
		case CEndoxApp::sign_disabled:
		{
			m_ctrlCmbFirma.SetCurSel(disabled);
			break;
		}
		case CEndoxApp::sign_comped:
		{
			m_ctrlCmbFirma.SetCurSel(comped);
			break;
		}
	}
}

void CIntegrazioniParamConfigUOForm::LoadQueryman()
{	
	m_ctrlEdtQuerymanUrl.SetWindowText(theApp.m_sQueryMan);
}

void CIntegrazioniParamConfigUOForm::LoadWorklist()
{
	// Sandro 20/04/2015
	RiempiComboStatiWorklist(&m_ctrlCmbWorklistStatoDefault, theApp.m_lWorklistStatoDaSelezionare, FALSE);

	// 0 normale, 1 utente windows, 2 con richiesta della password //
	int codric = m_ctrlCmbWorklistFocus.InsertString(0, theApp.GetMessageString(IDS_WL_FOCUS_CODICERICHIESTA));
	m_ctrlCmbWorklistFocus.SetItemData(codric, 0);
	int codpaz = m_ctrlCmbWorklistFocus.InsertString(1, theApp.GetMessageString(IDS_WL_FOCUS_CODICEPAZIENTE));
	m_ctrlCmbWorklistFocus.SetItemData(codpaz, 1);
	int cognome = m_ctrlCmbWorklistFocus.InsertString(2, theApp.GetMessageString(IDS_WL_FOCUS_CODICECOGNOME));
	m_ctrlCmbWorklistFocus.SetItemData(cognome, 2);
	int nome = m_ctrlCmbWorklistFocus.InsertString(3, theApp.GetMessageString(IDS_WL_FOCUS_CODICENOME));
	m_ctrlCmbWorklistFocus.SetItemData(nome, 3);	

	switch (theApp.m_lPrenotazioniCupFocus)
	{
		case 0:
		{
			m_ctrlCmbWorklistFocus.SetCurSel(codric);
			break;
		}
		case 1:
		{
			m_ctrlCmbWorklistFocus.SetCurSel(codpaz);
			break;
		}
		case 2:
		{
			m_ctrlCmbWorklistFocus.SetCurSel(cognome);
			break;
		}
		case 3:
		{
			m_ctrlCmbWorklistFocus.SetCurSel(nome);
			break;
		}
	}

	m_ctrlChkWorklist.SetCheck(theApp.m_bPrenotazioniCup == TRUE ? BST_CHECKED : BST_UNCHECKED);
	// m_ctrlChkWorklistIbrida.SetCheck(theApp.m_bWLModalitaIbrida == TRUE ? BST_CHECKED : BST_UNCHECKED);
	// m_ctrlChkWorklistDicom.SetCheck(theApp.m_bPrenotazioniDicom == TRUE ? BST_CHECKED : BST_UNCHECKED);

	VerifyWLOptions();
}

void CIntegrazioniParamConfigUOForm::LoadDicom()
{
	m_ctrlCmbDicomStoreMode.InsertString(0, theApp.GetMessageString(IDS_DICOM_NESSUNA));
	m_ctrlCmbDicomStoreMode.SetItemData(0, 0);
	m_ctrlCmbDicomStoreMode.InsertString(1, theApp.GetMessageString(IDS_DICOM_CONTRASSEGNATE));
	m_ctrlCmbDicomStoreMode.SetItemData(1, 1);	
	m_ctrlCmbDicomStoreMode.InsertString(2, theApp.GetMessageString(IDS_DICOM_TUTTE));
	m_ctrlCmbDicomStoreMode.SetItemData(2, 2);

	m_ctrlCmbDicomStoreMode.SetCurSel(theApp.m_lDcmStoreMode);
}

void CIntegrazioniParamConfigUOForm::SaveAnagrafeCentrale()
{
	m_ctrlEdtAnagrafeIP.GetWindowText(theApp.m_sTesiAtdNetIndirizzo);
	CString temp;
	m_ctrlEdtAnagrafePorta.GetWindowText(temp);
	theApp.m_nTesiAtdNetPorta = atoi(temp);
}

void CIntegrazioniParamConfigUOForm::SaveServer()
{
	/*theApp.m_bIntegrazioneGestioneRichiesteAcquisite = (m_ctrlChkServerGestioneRicAcq.GetCheck()==BST_CHECKED?TRUE:FALSE);
	theApp.m_bIntegrazioneInvioImmaginiBinarie = (m_ctrlChkServerImmaginibin.GetCheck()==BST_CHECKED?TRUE:FALSE);
	theApp.m_bIntegrazioneInvioRefertiAnnullati = (m_ctrlChkServerInvioRefAnnull.GetCheck()==BST_CHECKED?TRUE:FALSE);
	theApp.m_bIntegrazioneInvioRefertiDalFiller = (m_ctrlChkServerInvioRefFiller.GetCheck()==BST_CHECKED?TRUE:FALSE);*/
}

void CIntegrazioniParamConfigUOForm::SaveLock()
{	
	theApp.m_bLockServerAttivo = (m_ctrlChkLockAttivo.GetCheck()==BST_CHECKED?TRUE:FALSE);
}

void CIntegrazioniParamConfigUOForm::SaveFirma()
{
	int i = m_ctrlCmbFirma.GetCurSel();
	theApp.m_enumFirmaDigitale = (CEndoxApp::FirmaDigitaleType) m_ctrlCmbFirma.GetItemData(i);
}

void CIntegrazioniParamConfigUOForm::SaveQueryman()
{	
	m_ctrlEdtQuerymanUrl.GetWindowText(theApp.m_sQueryMan);
}

void CIntegrazioniParamConfigUOForm::SaveWorklist()
{
	// Sandro 20/04/2015 //
	int nCurSel = m_ctrlCmbWorklistStatoDefault.GetCurSel();
	theApp.m_lWorklistStatoDaSelezionare = m_ctrlCmbWorklistStatoDefault.GetItemData(nCurSel);

	//
	nCurSel = m_ctrlCmbWorklistFocus.GetCurSel();
	theApp.m_lPrenotazioniCupFocus = m_ctrlCmbWorklistFocus.GetItemData(nCurSel);

	theApp.m_bPrenotazioniCup = (m_ctrlChkWorklist.GetCheck() == BST_CHECKED ? TRUE : FALSE);
	// theApp.m_bWLModalitaIbrida = (m_ctrlChkWorklistIbrida.GetCheck() == BST_CHECKED ? TRUE : FALSE);
	// theApp.m_bPrenotazioniDicom = (m_ctrlChkWorklistDicom.GetCheck() == BST_CHECKED ? TRUE : FALSE);
}

void CIntegrazioniParamConfigUOForm::SaveDicom()
{
	int i = m_ctrlCmbDicomStoreMode.GetCurSel();
	theApp.m_lDcmStoreMode = m_ctrlCmbDicomStoreMode.GetItemData(i);	
}

void CIntegrazioniParamConfigUOForm::Save()
{
	SaveAnagrafeCentrale();
	SaveServer();
	SaveLock();
	SaveFirma();
	SaveQueryman();
	SaveWorklist();
	SaveDicom();

	//salvataggio
	CEsamiDoc *doc = (CEsamiDoc*) m_pConfigDlg->m_pEsamiView->GetDocument();
	//doc->OnSalvaConfigurazione();
	doc->OnSalvaConfigurazioneIntegrazioniUO();
}

void CIntegrazioniParamConfigUOForm::OnBnClickedBtnWorklist()
{
	CWorklistLayoutDlg layoutDlg(this, m_pConfigDlg->m_pEsamiView);
	layoutDlg.DoModal();
}


void CIntegrazioniParamConfigUOForm::OnBnClickedBtnOperatori()
{
	COperatoriDlg dlg(m_pConfigDlg->m_pEsamiView, BOOL_FROMMENU);
	dlg.DoModal();
}


void CIntegrazioniParamConfigUOForm::OnBnClickedBtnMedici()
{
	CMediciCurantiInviantiDlg dlg(this, MEDICI_CURANTI, BOOL_FROMMENU);
	dlg.DoModal();
}

void CIntegrazioniParamConfigUOForm::OnBnClickedBtnMediciInvianti()
{
	CMediciCurantiInviantiDlg dlg(this, MEDICI_INVIANTI, BOOL_FROMMENU);
	dlg.DoModal();
}


void CIntegrazioniParamConfigUOForm::OnBnClickedBtnProvenienza()
{
	CProvenienzaDlg dlg(this);
	dlg.DoModal();
}


void CIntegrazioniParamConfigUOForm::OnBnClickedBtnPrestazioni()
{
	CCodificaRegionaleExDlg dlg(this);
	dlg.DoModal();
}

void CIntegrazioniParamConfigUOForm::OnBnClickedBtnSedi()
{
	CSediSaleDlg dlg(this);
	dlg.DoModal();
}


void CIntegrazioniParamConfigUOForm::OnBnClickedBtnReparti()
{
	CInviantiDlg dlg(m_pConfigDlg->m_pEsamiView, BOOL_INTERNI, BOOL_FROMMENU);
	dlg.DoModal();
}


/*void CIntegrazioniParamConfigUOForm::OnBnClickedBtnUrgenza()
{
	CRAODlg dlg(this);
	dlg.DoModal();
	theApp.AfxMessageBoxEndo("Disabled");
}*/


void CIntegrazioniParamConfigUOForm::OnBnClickedChkAnagrafeAttivo()
{
	VerifyAnagrafeOptions();
}

void CIntegrazioniParamConfigUOForm::OnBnClickedChkWorklist()
{
	VerifyWLOptions();
}

void CIntegrazioniParamConfigUOForm::OnBnClickedChkCostoprestazioniAttivo()
{
}

void CIntegrazioniParamConfigUOForm::VerifyAnagrafeOptions()
{
	if (m_ctrlChkAnagrafeAttiva.GetCheck() == BST_CHECKED)
	{
		m_ctrlChkAnagrafeLockInserimento.EnableWindow(TRUE);
		m_ctrlChkAnagrafeSoloCentrale.EnableWindow(TRUE);
		m_ctrlEdtAnagrafeIP.EnableWindow(TRUE);
		m_ctrlEdtAnagrafePorta.EnableWindow(TRUE);
	}
	else
	{
		m_ctrlChkAnagrafeLockInserimento.EnableWindow(FALSE);
		m_ctrlChkAnagrafeSoloCentrale.EnableWindow(FALSE);
		m_ctrlEdtAnagrafeIP.EnableWindow(FALSE);
		m_ctrlEdtAnagrafePorta.EnableWindow(FALSE);
	}
}

void CIntegrazioniParamConfigUOForm::VerifyWLOptions()
{
	m_ctrlChkWorklistIbrida.EnableWindow(m_ctrlChkWorklist.GetCheck() == BST_CHECKED);
	m_ctrlCmbWorklistStatoDefault.EnableWindow(m_ctrlChkWorklist.GetCheck() == BST_CHECKED);
	m_ctrlCmbWorklistFocus.EnableWindow(m_ctrlChkWorklist.GetCheck() == BST_CHECKED);
	m_ctrlBtnWorklistLayout.EnableWindow(m_ctrlChkWorklist.GetCheck() == BST_CHECKED);
}

void CIntegrazioniParamConfigUOForm::OnBnClickedBtnSorgentistreaming()
{
	CSorgentiStreamingConfigDlg dlg(this);
	dlg.DoModal();
}
