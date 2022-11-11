#include "stdafx.h"
#include "Endox.h"
#include "ImportaCasoDlg.h"

#include "DLL_Imaging\h\AmLogin.h"

#include "CodificaDiagnosiEsameSet.h"
#include "CustomDate.h"
#include "EsamiAccessoriSet.h"
#include "EsamiView.h"
#include "InsertLogImportazioneCasiSPSet.h"
#include "RegioneSet.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CImportaCasoDlg, CDialog)

CImportaCasoDlg::CImportaCasoDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CImportaCasoDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CImportaCasoDlg::~CImportaCasoDlg()
{
}

BEGIN_MESSAGE_MAP(CImportaCasoDlg, CDialog)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)

END_MESSAGE_MAP()

void CImportaCasoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

void CImportaCasoDlg::OnCancel()
{
	CDialog::OnCancel();
}

BOOL CImportaCasoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, theApp.GetMessageString(IDS_DATAESAME));
	m_ctrlList.InsertColumn(1, theApp.GetMessageString(IDS_CODICERICOVERO));
	m_ctrlList.InsertColumn(2, theApp.GetMessageString(IDS_TIPOESAME));
	m_ctrlList.InsertColumn(3, theApp.GetMessageString(IDS_CODICEESTERNOESAME));
	m_ctrlList.InsertColumn(4, "", LVCFMT_CENTER, 0);

	RiempiLista();

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);

	theApp.LocalizeDialog(this, CImportaCasoDlg::IDD, "ImportaCasoDlg");
	return TRUE;
}

void CImportaCasoDlg::OnOK()
{
	// faccio niente //
}

void CImportaCasoDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);

	CString sFilter;
	sFilter.Format("Paziente=%li AND Contatore<>%li", m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

	CEsamiSet setEsami;
	setEsami.SetOpenFilter(sFilter);
	setEsami.SetSortRecord("Data DESC");

	if (setEsami.OpenRecordset("CImportaCasoDlg::RiempiLista"))
	{
		int nItem = 0;

		while (!setEsami.IsEOF())
		{
			if (!CRegioneSet().ExamHasPrestazioniNonNormate(setEsami.m_lContatore))
			{
				m_ctrlList.InsertItem(nItem, CCustomDate(setEsami.m_lData).GetDate("%d/%m/%Y %H:%M"));
				m_ctrlList.SetItemData(nItem, setEsami.m_lContatore);

				m_ctrlList.SetItemText(nItem, 1, setEsami.m_sRicovero);
				m_ctrlList.SetItemText(nItem, 2, CTipoEsameSet().GetDescrizione(setEsami.m_lIDEsame));
				m_ctrlList.SetItemText(nItem, 3, setEsami.m_sCodEsame);

				nItem++;
			}

			setEsami.MoveNext();
		}

		setEsami.CloseRecordset("CImportaCasoDlg::RiempiLista");
	}

	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CImportaCasoDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlList.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			CString sMsg;
			sMsg.Format(theApp.GetMessageString(IDS_COMFERMA_IMPORTAZIONE), m_ctrlList.GetItemText(nCurSel, 2), m_ctrlList.GetItemText(nCurSel, 0), m_ctrlList.GetItemText(nCurSel, 1), m_ctrlList.GetItemText(nCurSel, 3));

			if (AfxMessageBox(sMsg, MB_YESNO) == IDYES)
			{
				long lIDEsame = m_ctrlList.GetItemData(nCurSel);

				CString sFilter;
				sFilter.Format("Contatore=%li", lIDEsame);

				//

				CInsertLogImportazioneCasiSPSet().Exec(m_pEsamiView->m_pPazientiSet->m_lContatore, lIDEsame, m_pEsamiView->m_pEsamiSet->m_lContatore, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer);

				//

				CEsamiSet setEsamiOrigine;
				setEsamiOrigine.SetOpenFilter(sFilter);
				if (setEsamiOrigine.OpenRecordset("CImportaCasoDlg::OnNMDblclkList"))
				{
					if (!setEsamiOrigine.IsEOF())
					{
						if (m_pEsamiView->m_pEsamiSet->EditRecordset("CImportaCasoDlg::OnNMDblclkList"))
						{
							m_pEsamiView->m_pEsamiSet->m_sAccessori = setEsamiOrigine.m_sAccessori;
							m_pEsamiView->m_pEsamiSet->m_lData = setEsamiOrigine.m_lData;
							m_pEsamiView->m_pEsamiSet->m_iAllergie = setEsamiOrigine.m_iAllergie;
							m_pEsamiView->m_pEsamiSet->m_sDescrizioneAllergie = setEsamiOrigine.m_sDescrizioneAllergie;
							m_pEsamiView->m_pEsamiSet->m_lMedico = setEsamiOrigine.m_lMedico;
							m_pEsamiView->m_pEsamiSet->m_lAssistente = setEsamiOrigine.m_lAssistente;
							m_pEsamiView->m_pEsamiSet->m_lIDSedeEsame = setEsamiOrigine.m_lIDSedeEsame;
							// m_pEsamiView->m_pEsamiSet->m_sSalaEsame = setEsamiOrigine.m_sSalaEsame; // come SALAESAME usano il campo testo080 //
							m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto080 = setEsamiOrigine.m_setEP.m_sTesto080; // SALAESAME //
							m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto040 = setEsamiOrigine.m_setEP.m_sTesto040; // TROLLEY //
							m_pEsamiView->m_pEsamiSet->m_sStrumenti = setEsamiOrigine.m_sStrumenti;
							// m_pEsamiView->m_pEsamiSet->m_sAnestesista = setEsamiOrigine.m_sAnestesista; // come ANESTESISTA usano il campo testo082 //
							m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto082 = setEsamiOrigine.m_setEP.m_sTesto082; // ANESTESISTA //
							m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra000 = setEsamiOrigine.m_setEP.m_lDataOra000; // arrivo del prossimo paziente in sala
							m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra001 = setEsamiOrigine.m_setEP.m_lDataOra001; // uscita paziente dalla sala
							m_pEsamiView->m_pEsamiSet->m_sProcTerapeutiche = setEsamiOrigine.m_sProcTerapeutiche;
							m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf000 = setEsamiOrigine.m_setEP.m_sTestoCLRtf000; // REFERTO //
							m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt000 = setEsamiOrigine.m_setEP.m_sTestoCLTxt000; // REFERTO //
							m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLRtf001 = setEsamiOrigine.m_setEP.m_sTestoCLRtf001; // REFERTOINGLESE //
							m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoCLTxt001 = setEsamiOrigine.m_setEP.m_sTestoCLTxt001; // REFERTOINGLESE //

							if (m_pEsamiView->m_pEsamiSet->UpdateRecordset("CImportaCasoDlg::OnNMDblclkList"))
							{
								CopiaAccessoriEsame(setEsamiOrigine.m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore);
								CopiaCodificaDiagnosiEsame(setEsamiOrigine.m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore);

								if (ImportaImmaginiFilmati(setEsamiOrigine.m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore))
								{
									// cancello l'esame di origine //
									setEsamiOrigine.DeleteRecordset("CImportaCasoDlg::OnNMDblclkList");

									// mi riposiziono sull'esame nuovo così aggiorno i dati //
									if (m_pEsamiView->RicercaCodicePaziente(m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore, FALSE, FALSE))
										m_pEsamiView->MovePazientiAndEsami(NULL, FALSE, TRUE);
									else
										m_pEsamiView->MovePazientiAndEsami(NULL, TRUE, TRUE);
								}
							}
						}
					}

					setEsamiOrigine.CloseRecordset("CImportaCasoDlg::OnNMDblclkList");
				}

				CDialog::OnOK();
			}
		}
	}
}

void CImportaCasoDlg::CopiaAccessoriEsame(long lIDEsameOrigine, long lIDEsameDestinazione)
{
	CString sFilterOrigine;
	sFilterOrigine.Format("Esame=%li", lIDEsameOrigine);

	CString sFilterDestinazione;
	sFilterDestinazione.Format("Esame=%li", lIDEsameDestinazione);

	CEsamiAccessoriSet setOrigine;
	setOrigine.SetOpenFilter(sFilterOrigine);

	CEsamiAccessoriSet setDestinazione;
	setDestinazione.SetOpenFilter(sFilterDestinazione);

	if (setOrigine.OpenRecordset("CImportaCasoDlg::CopiaAccessoriEsame"))
	{
		if (setDestinazione.OpenRecordset("CImportaCasoDlg::CopiaAccessoriEsame"))
		{
			while (!setDestinazione.IsEOF())
			{
				setDestinazione.DeleteRecordset("CImportaCasoDlg::CopiaAccessoriEsame");
				setDestinazione.MoveNext();
			}

			while (!setOrigine.IsEOF())
			{
				if (setDestinazione.AddNewRecordset("CImportaCasoDlg::CopiaAccessoriEsame"))
				{
					setDestinazione.m_lEsame = lIDEsameDestinazione;
					setDestinazione.m_lCodice = setOrigine.m_lCodice;
					setDestinazione.m_lQuantita = setOrigine.m_lQuantita;

					setDestinazione.UpdateRecordset("CImportaCasoDlg::CopiaAccessoriEsame");
				}

				setOrigine.MoveNext();
			}

			setDestinazione.CloseRecordset("CImportaCasoDlg::CopiaAccessoriEsame");
		}

		setOrigine.CloseRecordset("CImportaCasoDlg::CopiaAccessoriEsame");
	}
}

void CImportaCasoDlg::CopiaCodificaDiagnosiEsame(long lIDEsameOrigine, long lIDEsameDestinazione)
{
	CString sFilterOrigine;
	sFilterOrigine.Format("Esame=%li", lIDEsameOrigine);

	CString sFilterDestinazione;
	sFilterDestinazione.Format("Esame=%li", lIDEsameDestinazione);

	CCodificaDiagnosiEsameSet setOrigine;
	setOrigine.SetOpenFilter(sFilterOrigine);

	CCodificaDiagnosiEsameSet setDestinazione;
	setDestinazione.SetOpenFilter(sFilterDestinazione);

	if (setOrigine.OpenRecordset("CImportaCasoDlg::CopiaCodificaDiagnosiEsame"))
	{
		if (setDestinazione.OpenRecordset("CImportaCasoDlg::CopiaCodificaDiagnosiEsame"))
		{
			while (!setDestinazione.IsEOF())
			{
				setDestinazione.DeleteRecordset("CImportaCasoDlg::CopiaCodificaDiagnosiEsame");
				setDestinazione.MoveNext();
			}

			while (!setOrigine.IsEOF())
			{
				if (setDestinazione.AddNewRecordset("CImportaCasoDlg::CopiaCodificaDiagnosiEsame"))
				{
					setDestinazione.m_lEsame = lIDEsameDestinazione;
					setDestinazione.m_lOrgano = setOrigine.m_lOrgano;
					setDestinazione.m_sSede = setOrigine.m_sSede;
					setDestinazione.m_sDiagnosiEsame = setOrigine.m_sDiagnosiEsame;

					setDestinazione.UpdateRecordset("CImportaCasoDlg::CopiaCodificaDiagnosiEsame");
				}

				setOrigine.MoveNext();
			}

			setDestinazione.CloseRecordset("CImportaCasoDlg::CopiaCodificaDiagnosiEsame");
		}

		setOrigine.CloseRecordset("CImportaCasoDlg::CopiaCodificaDiagnosiEsame");
	}
}

BOOL CImportaCasoDlg::ImportaImmaginiFilmati(long lIDEsameOrigine, long lIDEsameDestinazione)
{
	BOOL bReturn = FALSE;

	CImgIDList listIDs;
	CStringList listStrings;

	//

	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pPazientiSet->m_lContatore, lIDEsameOrigine);
	m_pEsamiView->m_pImgManager->GetImgIDList(&listIDs);

	POSITION pos = listIDs.GetHeadPosition();
	while (pos != NULL)
	{
		long lIDTemp = listIDs.GetNext(pos);

		CString sStringTemp = m_pEsamiView->m_pImgManager->GetFullPath(lIDTemp);
		listStrings.AddTail(sStringTemp);
	}

	//

	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pPazientiSet->m_lContatore, lIDEsameDestinazione);

	CImgIDList listIDImageImported;

	if (m_pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &listStrings, FORM_IMM, FORM_MINI, &listIDImageImported, theApp.m_lDcmStoreMode == 2, FALSE, FALSE) != listStrings.GetCount())
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMPORTERROR));
	else
		bReturn = TRUE;

	return bReturn;
}