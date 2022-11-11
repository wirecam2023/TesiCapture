#include "stdafx.h"
#include "Endox.h"
#include "UnificazioneAnagraficheDlg.h"

#include "Common.h"
#include "CustomDate.h"
#include "DocManager.h"
#include "EsamiView.h"
#include "PdfManager.h"

#include "ExtPatientEventSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CUnificazioneAnagraficheDlg, CDialog)

CUnificazioneAnagraficheDlg::CUnificazioneAnagraficheDlg(CWnd* pParent, CEsamiView* pEsamiView, CList<STRUCT_PAZIENTE>* pListPazienti)
	: CDialog(CUnificazioneAnagraficheDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	ASSERT(pListPazienti != NULL);
	ASSERT(pListPazienti->GetCount() > 1);

	m_pEsamiView = pEsamiView;
	m_pListPazienti = pListPazienti;
}

CUnificazioneAnagraficheDlg::~CUnificazioneAnagraficheDlg()
{
}

BEGIN_MESSAGE_MAP(CUnificazioneAnagraficheDlg, CDialog)

	ON_WM_CTLCOLOR()

	ON_LBN_SELCHANGE(IDC_LISTBOX_PAZIENTI, OnLbnSelchangeListboxPazienti)

END_MESSAGE_MAP()

void CUnificazioneAnagraficheDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_NOTA, m_ctrlStaticNota);	

	DDX_Control(pDX, IDC_LISTBOX_PAZIENTI, m_ctrlListboxPazienti);
	DDX_Control(pDX, IDC_LIST_TITOLI, m_ctrlListTitoli);
	DDX_Control(pDX, IDC_LIST_SELEZIONATI, m_ctrlListSelezionati);
	DDX_Control(pDX, IDC_LIST_RISULTATO, m_ctrlListRiepilogo);
}

BOOL CUnificazioneAnagraficheDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	m_ctrlStatic01.SetFont(&theApp.m_fontBig);
	m_ctrlStatic02.SetFont(&theApp.m_fontBig);
	m_ctrlStatic03.SetFont(&theApp.m_fontBig);
	m_ctrlListTitoli.SetFont(&theApp.m_fontBold);
	m_ctrlListRiepilogo.SetFont(&theApp.m_fontBold);

	//

	if (theApp.m_bDisabilitaEsamiPazientiSenzaAssiden)
		m_ctrlStaticNota.ShowWindow(TRUE);

	int iIndex = 0;
	POSITION pos = m_pListPazienti->GetHeadPosition();
	while(pos != NULL)
	{
		STRUCT_PAZIENTE structTemp = m_pListPazienti->GetAt(pos);

		if (theApp.m_bDisabilitaEsamiPazientiSenzaAssiden && !HasAssiden(structTemp.lID))
			m_ctrlListboxPazienti.InsertString(iIndex, structTemp.sNominativo, RGB(255,0,0), RGB(255,255,255));
		else
			m_ctrlListboxPazienti.InsertString(iIndex, structTemp.sNominativo);
		
		m_ctrlListboxPazienti.SetItemData(iIndex, structTemp.lID);

		m_pListPazienti->GetNext(pos);
	}

	//

	m_ctrlListTitoli.SetExtendedStyle(m_ctrlListTitoli.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListTitoli.SetTextColor(theApp.m_color[0]);
	m_ctrlListTitoli.InsertColumn(0, "", LVCFMT_LEFT, 0); // empty //
	m_ctrlListTitoli.InsertColumn(1, "", LVCFMT_LEFT, 107); // titolo //

	//

	m_ctrlListSelezionati.SetExtendedStyle(m_ctrlListSelezionati.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListSelezionati.SetTextColor(theApp.m_color[1]);
	m_ctrlListSelezionati.InsertColumn(0, "", LVCFMT_LEFT, 0); // empty //
	m_ctrlListSelezionati.InsertColumn(1, "", LVCFMT_LEFT, 211); // primo paziente //
	m_ctrlListSelezionati.InsertColumn(2, "", LVCFMT_LEFT, 211); // secondo paziente //

	//

	m_ctrlListRiepilogo.SetExtendedStyle(m_ctrlListRiepilogo.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListRiepilogo.SetTextColor(theApp.m_color[2]);
	m_ctrlListRiepilogo.InsertColumn(0, "", LVCFMT_LEFT, 0); // empty //
	m_ctrlListRiepilogo.InsertColumn(1, "", LVCFMT_LEFT, 211); // risultato della fusione //

	//

	int nItem = 0;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_PROGRESSIVO));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_ASSIDEN));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_CODALFA));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_COGNOME));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_NOME));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_SESSO));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_NATOIL));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_NATOA));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_CODICEFISCALE));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_CODICESANITARIO));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_CODICECLIENTE));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_NAZIONALITA));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_PROFESSIONE));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_NOMINATIVOPADRE));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_NOMINATIVOMADRE));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_ULSSRESIDENZA));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_VIA));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_CITTA));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_TELEFONO1));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_TELEFONO2));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_FAX));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_CELLULARE1));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_CELLULARE2));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_EMAIL));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_MEDICOCURANTE));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_NOSOLOGICO));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_DATARICOVERO));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	m_ctrlListTitoli.InsertItem(nItem, "");
	m_ctrlListTitoli.SetItemText(nItem, 1, theApp.GetMessageString(IDS_DASEGNALARE));
	m_ctrlListSelezionati.InsertItem(nItem, "");
	m_ctrlListRiepilogo.InsertItem(nItem, "");
	nItem++;

	//

	return TRUE;
}

void CUnificazioneAnagraficheDlg::OnCancel()
{
	if (m_ctrlBtnCancel.IsWindowEnabled())
		CDialog::OnCancel();
}

void CUnificazioneAnagraficheDlg::OnOK()
{
	if (m_ctrlBtnOK.IsWindowEnabled())
	{
		if (TimerMessageBox(theApp.GetMessageString(IDS_CONFERMA_UNIFICAZIONE)) == IDOK)
		{
			m_ctrlBtnCancel.EnableWindow(FALSE);
			m_ctrlBtnOK.EnableWindow(FALSE);

			BeginWaitCursor();

			int nSelItems[2];
			m_ctrlListboxPazienti.GetSelItems(2, nSelItems);

			//

			long lContatore1 = min(m_ctrlListboxPazienti.GetItemData(nSelItems[0]), m_ctrlListboxPazienti.GetItemData(nSelItems[1]));
			long lContatore2 = max(m_ctrlListboxPazienti.GetItemData(nSelItems[0]), m_ctrlListboxPazienti.GetItemData(nSelItems[1]));

			CString sFilter1;
			CString sFilter2;

			sFilter1.Format("Contatore=%li", lContatore1);
			sFilter2.Format("Contatore=%li", lContatore2);

			CPazientiSet setTemp1;
			CPazientiSet setTemp2;

			setTemp1.SetOpenFilter(sFilter1);
			setTemp2.SetOpenFilter(sFilter2);

			if (setTemp1.OpenRecordset("CUnificazioneAnagraficheDlg::OnOK") && setTemp2.OpenRecordset("CUnificazioneAnagraficheDlg::OnOK"))
			{
				if (!setTemp1.IsEOF() && !setTemp2.IsEOF())
				{
					if (setTemp1.EditRecordset("CUnificazioneAnagraficheDlg::OnOK") && setTemp2.EditRecordset("CUnificazioneAnagraficheDlg::OnOK"))
					{
						CString sTemp1;
						CString sTemp2;

						//

						setTemp1.m_sAssIden.Trim();
						setTemp2.m_sAssIden.Trim();

						BOOL bPreferOld = FALSE;
						if (!setTemp1.m_sAssIden.IsEmpty() && setTemp2.m_sAssIden.IsEmpty())
							bPreferOld = TRUE;

						//

						// setTemp1.m_lContatore = GetFieldValue(&setTemp1.m_lContatore, setTemp1.GetRecordset(), &setTemp2.m_lContatore, setTemp2.GetRecordset(), FALSE, TRUE);

						setTemp1.m_sAssIden = GetFieldValue(setTemp1.m_sAssIden, setTemp2.m_sAssIden, bPreferOld);

						setTemp1.m_sCodAlfa = GetFieldValue(setTemp1.m_sCodAlfa, setTemp2.m_sCodAlfa, bPreferOld);

						setTemp1.m_sCognome = GetFieldValue(setTemp1.m_sCognome, setTemp2.m_sCognome, bPreferOld);
						setTemp1.m_sCognome2 = GetFieldValue(setTemp1.m_sCognome2, setTemp2.m_sCognome2, bPreferOld);

						setTemp1.m_sNome = GetFieldValue(setTemp1.m_sNome, setTemp2.m_sNome, bPreferOld);

						setTemp1.m_lSessoPaz = GetFieldValue(&setTemp1.m_lSessoPaz, setTemp1.GetRecordset(), &setTemp2.m_lSessoPaz, setTemp2.GetRecordset(), TRUE, bPreferOld);

						setTemp1.m_lNatoIlCustom = GetFieldValue(&setTemp1.m_lNatoIlCustom, setTemp1.GetRecordset(), &setTemp2.m_lNatoIlCustom, setTemp2.GetRecordset(), FALSE, bPreferOld);

						setTemp1.m_sNatoA = GetFieldValue(setTemp1.m_sNatoA, setTemp2.m_sNatoA, bPreferOld);
						setTemp1.m_lIDComuneNascita = GetFieldValue(&setTemp1.m_lIDComuneNascita, setTemp1.GetRecordset(), &setTemp2.m_lIDComuneNascita, setTemp2.GetRecordset(), FALSE, bPreferOld);

						setTemp1.m_sCodFisc = GetFieldValue(setTemp1.m_sCodFisc, setTemp2.m_sCodFisc, bPreferOld);

						setTemp1.m_sCodSanit = GetFieldValue(setTemp1.m_sCodSanit, setTemp2.m_sCodSanit, bPreferOld);

						setTemp1.m_sCodiceCliente = GetFieldValue(setTemp1.m_sCodiceCliente, setTemp2.m_sCodiceCliente, bPreferOld);

						setTemp1.m_sNazionalita = GetFieldValue(setTemp1.m_sNazionalita, setTemp2.m_sNazionalita, bPreferOld);

						setTemp1.m_sProfessione = GetFieldValue(setTemp1.m_sProfessione, setTemp2.m_sProfessione, bPreferOld);

						setTemp1.m_sNominativoPadre = GetFieldValue(setTemp1.m_sNominativoPadre, setTemp2.m_sNominativoPadre, bPreferOld);

						setTemp1.m_sNominativoMadre = GetFieldValue(setTemp1.m_sNominativoMadre, setTemp2.m_sNominativoMadre, bPreferOld);

						setTemp1.m_sUlssResidenza = GetFieldValue(setTemp1.m_sUlssResidenza, setTemp2.m_sUlssResidenza, bPreferOld);

						setTemp1.m_sVia = GetFieldValue(setTemp1.m_sVia, setTemp2.m_sVia, bPreferOld);

						setTemp1.m_sCAP = GetFieldValue(setTemp1.m_sCAP, setTemp2.m_sCAP, bPreferOld);
						setTemp1.m_sCitta = GetFieldValue(setTemp1.m_sCitta, setTemp2.m_sCitta, bPreferOld);
						setTemp1.m_sProvincia = GetFieldValue(setTemp1.m_sProvincia, setTemp2.m_sProvincia, bPreferOld);
						setTemp1.m_lIDComune = GetFieldValue(&setTemp1.m_lIDComune, setTemp1.GetRecordset(), &setTemp2.m_lIDComune, setTemp2.GetRecordset(), FALSE, bPreferOld);

						setTemp1.m_sTelefono1 = GetFieldValue(setTemp1.m_sTelefono1, setTemp2.m_sTelefono1, bPreferOld);

						setTemp1.m_sTelefono2 = GetFieldValue(setTemp1.m_sTelefono2, setTemp2.m_sTelefono2, bPreferOld);

						setTemp1.m_sFax = GetFieldValue(setTemp1.m_sFax, setTemp2.m_sFax, bPreferOld);

						setTemp1.m_sCellulare1 = GetFieldValue(setTemp1.m_sCellulare1, setTemp2.m_sCellulare1, bPreferOld);

						setTemp1.m_sCellulare2 = GetFieldValue(setTemp1.m_sCellulare2, setTemp2.m_sCellulare2, bPreferOld);

						setTemp1.m_sEmail = GetFieldValue(setTemp1.m_sEmail, setTemp2.m_sEmail, bPreferOld);

						setTemp1.m_sMedicoCurante = GetFieldValue(setTemp1.m_sMedicoCurante, setTemp2.m_sMedicoCurante, bPreferOld);
						setTemp1.m_lMedicoCurante = GetFieldValue(&setTemp1.m_lMedicoCurante, setTemp1.GetRecordset(), &setTemp2.m_lMedicoCurante, setTemp2.GetRecordset(), FALSE, bPreferOld);
						setTemp1.m_sMedicoTel = GetFieldValue(setTemp1.m_sMedicoTel, setTemp2.m_sMedicoTel, bPreferOld);
						setTemp1.m_sMedicoIndirizzo = GetFieldValue(setTemp1.m_sMedicoIndirizzo, setTemp2.m_sMedicoIndirizzo, bPreferOld);
						setTemp1.m_sMedicoEmail = GetFieldValue(setTemp1.m_sMedicoEmail, setTemp2.m_sMedicoEmail, bPreferOld);

						setTemp1.m_sCodiceRicovero = GetFieldValue(setTemp1.m_sCodiceRicovero, setTemp2.m_sCodiceRicovero, bPreferOld);
						setTemp1.m_sIdEpisodioRicovero = GetFieldValue(setTemp1.m_sIdEpisodioRicovero, setTemp2.m_sIdEpisodioRicovero, bPreferOld);
						setTemp1.m_lIdRepartoDegenza = GetFieldValue(&setTemp1.m_lIdRepartoDegenza, setTemp1.GetRecordset(), &setTemp2.m_lIdRepartoDegenza, setTemp2.GetRecordset(), FALSE, bPreferOld);

						setTemp1.m_lDataRicoveroCustom = GetFieldValue(&setTemp1.m_lDataRicoveroCustom, setTemp1.GetRecordset(), &setTemp2.m_lDataRicoveroCustom, setTemp2.GetRecordset(), FALSE, bPreferOld);

						setTemp1.m_sDenSegnalato = GetFieldValue(setTemp1.m_sDenSegnalato, setTemp2.m_sDenSegnalato, bPreferOld);

						//

						if (!setTemp1.IsFieldNull(&setTemp1.m_lDataUltimoEsame) && !setTemp2.IsFieldNull(&setTemp2.m_lDataUltimoEsame))
						{
							setTemp1.m_lDataUltimoEsame = max(setTemp1.m_lDataUltimoEsame, setTemp2.m_lDataUltimoEsame);
						}
						else
						{
							if (!setTemp2.IsFieldNull(&setTemp2.m_lDataUltimoEsame))
								setTemp1.m_lDataUltimoEsame = setTemp2.m_lDataUltimoEsame;
						}

						if (setTemp1.m_lStatoAPC != 1)
							setTemp1.m_lStatoAPC = 2;

						setTemp1.m_sLogin = GetFieldValue(setTemp1.m_sLogin, setTemp2.m_sLogin, bPreferOld);

						if (setTemp2.m_bSendEmail)
							setTemp1.m_bSendEmail = TRUE;

						if (setTemp2.m_bSendSms)
							setTemp1.m_bSendSms = TRUE;

						if (setTemp2.m_bPazienteDelDirettore)
							setTemp1.m_bPazienteDelDirettore = TRUE;

						setTemp1.m_lIDMalattiaCronica = GetFieldValue(&setTemp1.m_lIDMalattiaCronica, setTemp1.GetRecordset(), &setTemp2.m_lIDMalattiaCronica, setTemp2.GetRecordset(), FALSE, bPreferOld);
						setTemp1.m_sDescrizioneMalattiaCronica = GetFieldValue(setTemp1.m_sDescrizioneMalattiaCronica, setTemp2.m_sDescrizioneMalattiaCronica, bPreferOld);

						if (setTemp2.m_bCertificazioneMEF)
							setTemp1.m_bCertificazioneMEF = TRUE;

						if (setTemp2.m_bCertificazioneSISS)
							setTemp1.m_bCertificazioneSISS = TRUE;

						//

						setTemp2.m_lIDPazienteUnificato = lContatore1;
						setTemp2.m_bEliminato = TRUE;

						//

						if (setTemp1.UpdateRecordset("CUnificazioneAnagraficheDlg::OnOK") && setTemp2.UpdateRecordset("CUnificazioneAnagraficheDlg::OnOK"))
						{
							// Sandro 04/01/2014 // sposto anche i documenti allegati al paziente //
							AmDocManager_MoveDocPatient(theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, lContatore2, lContatore1);

							// riempio la lista di ID degli esami da spostare //

							CList<long> listIDEsamiDaSpostare;

							CString sFilterEsami;
							sFilterEsami.Format("Paziente=%li", lContatore2);

							CEsamiSet setEsamiTemp;
							setEsamiTemp.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
							setEsamiTemp.SetOpenFilter(sFilterEsami);

							if (setEsamiTemp.OpenRecordset("CUnificazioneAnagraficheDlg::OnOK"))
							{
								while(!setEsamiTemp.IsEOF())
								{
									listIDEsamiDaSpostare.AddTail(setEsamiTemp.m_lContatore);
									setEsamiTemp.MoveNext();
								}

								setEsamiTemp.CloseRecordset("CUnificazioneAnagraficheDlg::OnOK");
							}

							POSITION pos = listIDEsamiDaSpostare.GetHeadPosition();
							while(pos != NULL)
							{
								long lIDEsame = listIDEsamiDaSpostare.GetAt(pos);

								// sposto i documenti allegati all'esame //
								AmDocManager_MoveDocExam(theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, lContatore2, lContatore1, lIDEsame);

								// sposto i PDF allegati //
								CPdfManager pdfManager;
								pdfManager.MovePdfEx(lContatore2, lContatore1, lIDEsame);

								// sposto immagini e filmati //
								m_pEsamiView->m_pImgManager->MoveImg(lContatore2, lIDEsame, lContatore1);

								// sposto i record degli esami //
								sFilterEsami.Format("Contatore=%li", lIDEsame);
								setEsamiTemp.SetOpenFilter(sFilterEsami);
								if (setEsamiTemp.OpenRecordset("CUnificazioneAnagraficheDlg::OnOK"))
								{
									if (!setEsamiTemp.IsEOF())
									{
										if (setEsamiTemp.EditRecordset("CUnificazioneAnagraficheDlg::OnOK"))
										{
											setEsamiTemp.m_lPaziente = lContatore1;
											setEsamiTemp.UpdateRecordset("CUnificazioneAnagraficheDlg::OnOK");
										}
									}

									setEsamiTemp.CloseRecordset("CEsamiView::OnCommandFileSpostaEsame");
								}

								//
								listIDEsamiDaSpostare.GetNext(pos);
							}

							//

							m_pEsamiView->RicercaCodicePaziente(lContatore1, 0, FALSE, TRUE);
							m_pEsamiView->MovePazientiAndEsami(NULL, TRUE, TRUE);

							CExtPatientEventSet().AddEvent(lContatore1, updatePatient);
						}
					}
				}
			}
			setTemp1.CloseRecordset("CUnificazioneAnagraficheDlg::OnOK");
			setTemp2.CloseRecordset("CUnificazioneAnagraficheDlg::OnOK");

			EndWaitCursor();

			CDialog::OnOK();
		}
	}
}

HBRUSH CUnificazioneAnagraficheDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hReturn = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_01:
		//case IDC_LISTBOX_PAZIENTI:
		{
			pDC->SetTextColor(theApp.m_color[0]);
			break;
		}
		case IDC_STATIC_02:
		case IDC_LIST_TITOLI:
		case IDC_LIST_SELEZIONATI:
		{
			pDC->SetTextColor(theApp.m_color[1]);
			break;
		}
		case IDC_STATIC_03:
		case IDC_LIST_RISULTATO:
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
	}

	return hReturn;
}

BOOL CUnificazioneAnagraficheDlg::HasAssiden(int contatore)
{
	CString sFilter1;
	sFilter1.Format("Contatore=%li", contatore);

	CPazientiSet setTemp1;
	setTemp1.SetOpenFilter(sFilter1);

	BOOL result = FALSE;

	if (setTemp1.OpenRecordset("CUnificazioneAnagraficheDlg::HasAssiden"))
	{
		if (!setTemp1.IsEOF())
		{
			if (!setTemp1.IsFieldNull(&setTemp1.m_sAssIden) && setTemp1.m_sAssIden.GetLength() > 0)
				result = TRUE;			
		}

		setTemp1.CloseRecordset("CUnificazioneAnagraficheDlg::OnLbnSelchangeListboxPazienti");
	}	

	return result;
}

void CUnificazioneAnagraficheDlg::OnLbnSelchangeListboxPazienti()
{
	if (m_ctrlListboxPazienti.GetSelCount() == 2)
	{
		int nSelItems[2];
		m_ctrlListboxPazienti.GetSelItems(2, nSelItems);

		//

		long lContatore1 = min(m_ctrlListboxPazienti.GetItemData(nSelItems[0]), m_ctrlListboxPazienti.GetItemData(nSelItems[1]));
		long lContatore2 = max(m_ctrlListboxPazienti.GetItemData(nSelItems[0]), m_ctrlListboxPazienti.GetItemData(nSelItems[1]));

		CString sFilter1;
		CString sFilter2;

		sFilter1.Format("Contatore=%li", lContatore1);
		sFilter2.Format("Contatore=%li", lContatore2);

		CPazientiSet setTemp1;
		CPazientiSet setTemp2;

		setTemp1.SetOpenFilter(sFilter1);
		setTemp2.SetOpenFilter(sFilter2);

		if (setTemp1.OpenRecordset("CUnificazioneAnagraficheDlg::OnLbnSelchangeListboxPazienti") && setTemp2.OpenRecordset("CUnificazioneAnagraficheDlg::OnLbnSelchangeListboxPazienti"))
		{
			if (!setTemp1.IsEOF() && !setTemp2.IsEOF())
			{
				CString sTemp1;
				CString sTemp2;

				//

				setTemp1.m_sAssIden.Trim();
				setTemp2.m_sAssIden.Trim();

				BOOL bPreferOld = FALSE;
				if (!setTemp1.m_sAssIden.IsEmpty() && setTemp2.m_sAssIden.IsEmpty())
					bPreferOld = TRUE;

				//

				int nItem = 0;

				sTemp1.Format("%li", setTemp1.m_lContatore);
				sTemp2.Format("%li", setTemp2.m_lContatore);
				SetListsItemText(nItem, sTemp1, sTemp2, TRUE);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sAssIden, setTemp2.m_sAssIden, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sCodAlfa, setTemp2.m_sCodAlfa, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sCognome + " " + setTemp1.m_sCognome2, setTemp2.m_sCognome + " " + setTemp2.m_sCognome2, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sNome, setTemp2.m_sNome, bPreferOld);
				nItem++;

				SetListsItemText(nItem, DecodeSesso(setTemp1.m_lSessoPaz), DecodeSesso(setTemp2.m_lSessoPaz), bPreferOld);
				nItem++;

				SetListsItemText(nItem, CCustomDate(setTemp1.m_lNatoIlCustom).GetDate("%d/%m/%Y"), CCustomDate(setTemp2.m_lNatoIlCustom).GetDate("%d/%m/%Y"), bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sNatoA, setTemp2.m_sNatoA, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sCodFisc, setTemp2.m_sCodFisc, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sCodSanit, setTemp2.m_sCodSanit, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sCodiceCliente, setTemp2.m_sCodiceCliente, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sNazionalita, setTemp2.m_sNazionalita, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sProfessione, setTemp2.m_sProfessione, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sNominativoPadre, setTemp2.m_sNominativoPadre, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sNominativoMadre, setTemp2.m_sNominativoMadre, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sUlssResidenza, setTemp2.m_sUlssResidenza, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sVia, setTemp2.m_sVia, bPreferOld);
				nItem++;

				SetListsItemText(nItem, DecodeCitta(setTemp1.m_sCAP, setTemp1.m_sCitta, setTemp1.m_sProvincia), DecodeCitta(setTemp2.m_sCAP, setTemp2.m_sCitta, setTemp2.m_sProvincia), bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sTelefono1, setTemp2.m_sTelefono1, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sTelefono2, setTemp2.m_sTelefono2, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sFax, setTemp2.m_sFax, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sCellulare1, setTemp2.m_sCellulare1, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sCellulare2, setTemp2.m_sCellulare2, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sEmail, setTemp2.m_sEmail, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sMedicoCurante, setTemp2.m_sMedicoCurante, bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sCodiceRicovero, setTemp2.m_sCodiceRicovero, bPreferOld);
				nItem++;

				SetListsItemText(nItem, CCustomDate(setTemp1.m_lDataRicoveroCustom).GetDate("%d/%m/%Y"), CCustomDate(setTemp2.m_lDataRicoveroCustom).GetDate("%d/%m/%Y"), bPreferOld);
				nItem++;

				SetListsItemText(nItem, setTemp1.m_sDenSegnalato, setTemp2.m_sDenSegnalato, bPreferOld);
				nItem++;
			}
		}
		setTemp1.CloseRecordset("CUnificazioneAnagraficheDlg::OnLbnSelchangeListboxPazienti");
		setTemp2.CloseRecordset("CUnificazioneAnagraficheDlg::OnLbnSelchangeListboxPazienti");

		//

		if (theApp.m_bDisabilitaEsamiPazientiSenzaAssiden && HasAssiden(lContatore1) && HasAssiden(lContatore2))
			m_ctrlBtnOK.EnableWindow(FALSE);
		else
			m_ctrlBtnOK.EnableWindow(TRUE);
	}
	else
	{
		for(int i = 0; i <= 25; i++)
		{
			m_ctrlListSelezionati.SetItemText(i, 1, "");
			m_ctrlListSelezionati.SetItemText(i, 2, "");

			m_ctrlListRiepilogo.SetItemText(i, 1, "");
		}

		m_ctrlBtnOK.EnableWindow(FALSE);
	}
}

long CUnificazioneAnagraficheDlg::GetFieldValue(long* pLongOld, CRecordset* pRecordsetOld, long* pLongNew, CRecordset* pRecordsetNew, BOOL bZeroIsValidValue, BOOL bPreferOld)
{
	long lReturn = 0;

	//

	if (bZeroIsValidValue)
	{
		if (bPreferOld)
		{
			if (!pRecordsetOld->IsFieldNull(pLongOld))
			{
				lReturn = *pLongOld;
			}
			else
			{
				if (!pRecordsetNew->IsFieldNull(pLongNew))
					lReturn = *pLongNew;
			}
		}
		else
		{
			if (!pRecordsetNew->IsFieldNull(pLongNew))
			{
				lReturn = *pLongNew;
			}
			else
			{
				if (!pRecordsetOld->IsFieldNull(pLongOld))
					lReturn = *pLongOld;
			}
		}
	}
	else
	{
		if (bPreferOld)
		{
			if (!pRecordsetOld->IsFieldNull(pLongOld) && (*pLongOld > 0))
			{
				lReturn = *pLongOld;
			}
			else
			{
				if (!pRecordsetNew->IsFieldNull(pLongNew) && (*pLongNew > 0))
					lReturn = *pLongNew;
			}
		}
		else
		{
			if (!pRecordsetNew->IsFieldNull(pLongNew) && (*pLongNew > 0))
			{
				lReturn = *pLongNew;
			}
			else
			{
				if (!pRecordsetOld->IsFieldNull(pLongOld) && (*pLongOld > 0))
					lReturn = *pLongOld;
			}
		}
	}

	//

	return lReturn;
}

CString CUnificazioneAnagraficheDlg::GetFieldValue(CString sOld, CString sNew, BOOL bPreferOld)
{
	CString sReturn = "";

	//

	sOld.Trim();
	sNew.Trim();

	while(sOld.Find("  ") >= 0)
		sOld.Replace("  ", " ");

	while(sNew.Find("  ") >= 0)
		sNew.Replace("  ", " ");

	//

	if (bPreferOld)
	{
		if (!sOld.IsEmpty())
			sReturn = sOld;
		else
			sReturn = sNew;
	}
	else
	{
		if (!sNew.IsEmpty())
			sReturn = sNew;
		else
			sReturn = sOld;
	}

	//

	return sReturn;
}

void CUnificazioneAnagraficheDlg::SetListsItemText(int nItem, CString sOld, CString sNew, BOOL bPreferOld)
{
	m_ctrlListSelezionati.SetItemText(nItem, 1, sOld);
	m_ctrlListSelezionati.SetItemText(nItem, 2, sNew);

	//

	m_ctrlListRiepilogo.SetItemText(nItem, 1, GetFieldValue(sOld, sNew, bPreferOld));
}