#include "stdafx.h"
#include "Endox.h"
#include "VitalSignMisurazioniDettaglioDlg.h"

#include "ArchivioStampeDlg.h"
#include "EsamiView.h"
#include "MonitoraggioSet.h"
#include "PdfManager.h"
#include "VitalSignManager.h"
#include "VitalSignMisurazioniDetailSet.h"
#include "VitalSignMisurazioniHeaderSet.h"
#include "VitalSignPdfWaitingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVitalSignMisurazioniDettaglioDlg, CEndoxResizableDlg)

CVitalSignMisurazioniDettaglioDlg::CVitalSignMisurazioniDettaglioDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, long idHeader)
: CEndoxResizableDlg(CVitalSignMisurazioniDettaglioDlg::IDD, pParentWnd), m_ctrlList(TRUE, TRUE, FALSE)
{
	m_pEsamiView = pEsamiView;
	m_lIDHeader = idHeader;
	m_sIdSessioneVitalSign = "";
}

CVitalSignMisurazioniDettaglioDlg::~CVitalSignMisurazioniDettaglioDlg()
{
}

BEGIN_MESSAGE_MAP(CVitalSignMisurazioniDettaglioDlg, CEndoxResizableDlg)

	ON_MESSAGE(WM_MISURAZIONI_VITALSIGN_LISTEV, OnMisurazioni_VitalSign_ListEv)

	ON_BN_CLICKED(IDC_BTN_VEDIPDF, &CVitalSignMisurazioniDettaglioDlg::OnBnClickedVedipdf)
END_MESSAGE_MAP()

void CVitalSignMisurazioniDettaglioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlBtnConferma);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnAnnulla);
	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_BTN_VEDIPDF, m_ctrlBtnVediPdf);
}

BOOL CVitalSignMisurazioniDettaglioDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDOK, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDCANCEL, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));	
	AddAnchor(IDC_BTN_VEDIPDF, CSize(0, 0), CSize(100, 0));

	//
	theApp.LocalizeDialog(this, CVitalSignMisurazioniDettaglioDlg::IDD, "MisurazioniVitalSignDettaglioDlg");

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	CVitalSignMisurazioniHeaderSet tempSet;
	CString filter;
	filter.Format("ID=%li", m_lIDHeader);
	tempSet.SetOpenFilter(filter);

	if (tempSet.OpenRecordset("CMonitoraggioVertDynForm::OnMonitoraggioListEv"))
	{
		if (!tempSet.IsEOF())
		{
			m_sIdSessioneVitalSign = tempSet.m_sIDSessioneVitalSign;
		}

		tempSet.CloseRecordset("CMonitoraggioVertDynForm::OnMonitoraggioListEv");
	}

	RiempiLista();

	m_changedList.RemoveAll();

	m_ctrlList.SetNotificationChangeValueMessage(WM_MISURAZIONI_VITALSIGN_LISTEV);

	//
	return TRUE;
}

void CVitalSignMisurazioniDettaglioDlg::OnCancel()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ABORT), MB_YESNO) == IDNO)
		return;

	CResizableDialog::OnCancel();
}

void CVitalSignMisurazioniDettaglioDlg::OnOK()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONFIRM), MB_YESNO) == IDNO)
		return;

	int iTempFase = 0;
	int iTempIdDispositivo = 0;
	CString sTempNomeStazione = "";
	CString sTempIdSessioneVitalSign = "";

	CList<CVitalSignManager::Measurament>* measuraments = new CList<CVitalSignManager::Measurament>();
	CList<CVitalSignManager::Measurament>* oldMeasurament = new CList<CVitalSignManager::Measurament>();

	POSITION pos = m_changedList.GetHeadPosition();
	while (pos)
	{
		int index = m_changedList.GetNext(pos);

		if (index >= 0)
		{
			long lIDdetail = m_ctrlList.GetItemData(index);
			CString sNota = m_ctrlList.GetItemText(index, 4);

			CVitalSignMisurazioniDetailSet detailSet;
			CString sFilter;
			sFilter.Format("ID=%li", lIDdetail);
			detailSet.SetOpenFilter(sFilter);

			if (detailSet.OpenRecordset("CVitalSignMisurazioniDettaglioDlg::OnOK"))
			{
				if (!detailSet.IsEOF())
				{

					//Lista che contiene i vecchi commenti delle misurazioni modificate
					CVitalSignManager::Measurament tmpMes1;
					tmpMes1.lId = detailSet.m_lID;
					strcpy_s(tmpMes1.sNotes, detailSet.m_sNote);
					oldMeasurament->AddTail(tmpMes1);
					//

					if (detailSet.EditRecordset("CVitalSignMisurazioniDettaglioDlg::OnOK"))
					{
						detailSet.m_sNote = sNota;

						CVitalSignManager::Measurament tmpMes;
						strcpy_s(tmpMes.sId, detailSet.m_sVitalSignId);
						strcpy_s(tmpMes.sNotes, sNota);
						measuraments->AddTail(tmpMes);

						detailSet.UpdateRecordset("CVitalSignMisurazioniDettaglioDlg::OnOK");
					}
				}

				detailSet.CloseRecordset("CVitalSignMisurazioniDettaglioDlg::OnOK");
			}								
		}
	}

	//Recupero note dell'header e di ogni dettaglio. Mi serve perché in caso di errore le riprisitino
	CString filter;
	filter.Format("ID=%li", m_lIDHeader);
	CVitalSignMisurazioniHeaderSet vitalSignMisSet;
	vitalSignMisSet.SetOpenFilter(filter);
	CString oldNotes;
	long oldPdfId = 0;

	if (vitalSignMisSet.OpenRecordset("CVitalSignMisurazioniDettaglioDlg::OnOK"))
	{
		if (!vitalSignMisSet.IsEOF())
		{
			oldNotes = vitalSignMisSet.m_sNote; //Mi metto via le vecchie note per ripristinarle in caso di errore
			oldPdfId = vitalSignMisSet.m_lIDPdf; //Mi metto via il vecchio idpdf per individuarne la sostituzione da parte dell'integrazione						

			//Mi salvo anche la parte dell'header da riportare nel monitoraggio
			iTempFase = vitalSignMisSet.m_lFase;
			iTempIdDispositivo = vitalSignMisSet.m_lIDDispositivo;
			sTempNomeStazione = vitalSignMisSet.m_sNomeStazione;
			sTempIdSessioneVitalSign = vitalSignMisSet.m_sIDSessioneVitalSign;
		}

		vitalSignMisSet.CloseRecordset("CVitalSignModificaNoteDlg::OnOK");
	}

	if (!CVitalSignManager(m_pEsamiView).ChangeNotesAndWait(m_sIdSessioneVitalSign, m_lIDHeader, oldPdfId, oldNotes, oldMeasurament, oldNotes, measuraments))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MISURAZIONIDETTAGLIO_MODIFICA_ERR1));
	}
	else
	{
		//Se è tutto ok, le righe commentate diventano MONITORAGGI di Endox
		POSITION pos = m_changedList.GetHeadPosition();
		while (pos)
		{
			int index = m_changedList.GetNext(pos);

			if (index >= 0)
			{
				long lIDdetail = m_ctrlList.GetItemData(index);
				CString sNota = m_ctrlList.GetItemText(index, 4);

				CVitalSignMisurazioniDetailSet detailSet;
				CString sFilter;
				sFilter.Format("ID=%li", lIDdetail);
				detailSet.SetOpenFilter(sFilter);

				if (detailSet.OpenRecordset("CVitalSignMisurazioniDettaglioDlg::OnOK"))
				{
					if (!detailSet.IsEOF())
					{

						//Inserisco un monitoraggio per ogni record
						CString sFilter;
						sFilter.Format("IDESTERNO = '%s'", detailSet.m_sVitalSignId);
						CMonitoraggioSet monitoraggioSet;
						monitoraggioSet.SetOpenFilter(sFilter);
						if (monitoraggioSet.OpenRecordset(""))
						{
							if (monitoraggioSet.IsEOF())
							{
								if (!monitoraggioSet.AddNewRecordset("CVitalSignMisurazioniDettaglioDlg::OnOK"))
								{
									theApp.AfxMessageBoxEndo("CVitalSignMisurazioniDettaglioDlg::OnOK");
									return;
								}
							}
							else
							{
								if (!monitoraggioSet.EditRecordset("CVitalSignMisurazioniDettaglioDlg::OnOK"))
								{
									theApp.AfxMessageBoxEndo("CVitalSignMisurazioniDettaglioDlg::OnOK");
									return;
								}
							}

							monitoraggioSet.m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
							monitoraggioSet.m_lQuando = iTempFase;
							monitoraggioSet.m_lIdDispositivo = iTempIdDispositivo;
							monitoraggioSet.m_sNomeStazione = sTempNomeStazione;
							monitoraggioSet.m_sIdSessione = sTempIdSessioneVitalSign;
							monitoraggioSet.m_sIdEsterno = detailSet.m_sVitalSignId;
							monitoraggioSet.m_strOra = detailSet.m_sOra;
							monitoraggioSet.m_strFC = detailSet.m_sFC;
							monitoraggioSet.m_strPA = detailSet.m_sPA;
							monitoraggioSet.m_strSat = detailSet.m_sSat;

							monitoraggioSet.UpdateRecordset("CVitalSignMisurazioniDettaglioDlg::OnOK");

							monitoraggioSet.CloseRecordset("CVitalSignMisurazioniDettaglioDlg::OnOK");
						}
					}

					detailSet.CloseRecordset("CVitalSignMisurazioniDettaglioDlg::OnOK");
				}
			}
		}
	}

	delete(measuraments);
	delete(oldMeasurament);
		
	CResizableDialog::OnOK();
}

void CVitalSignMisurazioniDettaglioDlg::RiempiLista()
{
	m_ctrlList.SetRedraw(FALSE);

	m_ctrlList.DeleteAllItems();

	//colonne
	m_ctrlList.InsertColumn(0, theApp.GetMessageString(IDS_ORE));
	m_ctrlList.InsertColumn(1, theApp.GetMessageString(IDS_FC));
	m_ctrlList.InsertColumn(2, theApp.GetMessageString(IDS_PA));
	m_ctrlList.InsertColumn(3, theApp.GetMessageString(IDS_SAT));
	m_ctrlList.InsertColumn(4, theApp.GetMessageString(IDS_NOTE));
	m_ctrlList.InsertColumn(5, theApp.GetMessageString(IDS_FRASE_PREDEFINITA));

	//Frasi predefinite
	CStringIDList frasiPredefiniteList;
	tagLISTCOMBO temp1;
	
	temp1.lID = 1;
	temp1.strName = "Artefatto";	
	frasiPredefiniteList.AddTail(temp1);

	//righe
	CVitalSignMisurazioniDetailSet detailSet;
	CString sFilter;
	sFilter.Format("IDHEADER=%li", m_lIDHeader);
	detailSet.SetOpenFilter(sFilter);

	if (detailSet.OpenRecordset("CVitalSignMisurazioniDettaglioDlg::RiempiLista"))
	{
		while (!detailSet.IsEOF())
		{
			int index = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), detailSet.m_sOra);
			m_ctrlList.SetItemText(index, 1, detailSet.m_sFC);
			m_ctrlList.SetItemText(index, 2, detailSet.m_sPA);
			m_ctrlList.SetItemText(index, 3, detailSet.m_sSat);			
			m_ctrlList.SetSubItemEdit(index, 4);
			m_ctrlList.SetItemText(index, 4, detailSet.m_sNote);
			m_ctrlList.SetSubItemCombo(index, 5, frasiPredefiniteList);

			m_ctrlList.SetItemData(index, detailSet.m_lID);

			detailSet.MoveNext();
		}

		detailSet.CloseRecordset("CVitalSignMisurazioniDettaglioDlg::RiempiLista");
	}

	/*for (int i = 0; i < m_ctrlList.GetHeaderCtrl()->GetItemCount(); i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);*/

	m_ctrlList.SetFont(&theApp.m_fontBig);

	m_ctrlList.SetRedraw(TRUE);
}

LRESULT CVitalSignMisurazioniDettaglioDlg::OnMisurazioni_VitalSign_ListEv(WPARAM wParam, LPARAM lParam)
{
	//Se è stato cliccato il flag per visualizzare il dettaglio, apro la dialog
	if ((int)lParam == 5)
	{
		CString temp = m_ctrlList.GetItemText(wParam, lParam);
		m_ctrlList.SetItemText(wParam, lParam - 1, temp);
		m_ctrlList.SetItemText(wParam, lParam, "");

		if(m_changedList.Find(wParam) == NULL)
			m_changedList.AddTail(wParam);
	}
	if ((int)lParam == 4)
	{
		if (m_changedList.Find(wParam) == NULL)
			m_changedList.AddTail(wParam);
	}

	return 1;
}

void CVitalSignMisurazioniDettaglioDlg::OnBnClickedVedipdf()
{
	CVitalSignMisurazioniHeaderSet tempSet;
	CString filter;
	filter.Format("ID=%li", m_lIDHeader);
	tempSet.SetOpenFilter(filter);

	if (tempSet.OpenRecordset("CMonitoraggioVertDynForm::OnMonitoraggioListEv"))
	{
		if (!tempSet.IsEOF())
		{
			if (tempSet.m_lIDPdf > 0)
			{
				CPdfManager pdfManager;
				CString pdfPath = pdfManager.GetPdfPath(tempSet.m_lIDPdf);

				CArchivioStampeDlg::tagPDFVIEW pdfView;
				pdfView.lID = tempSet.m_lIDPdf;
				strcpy_s(pdfView.szNote, "");
				strcpy_s(pdfView.szData, "");
				strcpy_s(pdfView.szFile, pdfPath);
				pdfView.bFitToPage = FALSE;
				pdfView.bFirmato = FALSE;
				pdfView.bSospeso = FALSE;
				pdfView.bAnnullato = FALSE;
				pdfView.bCriptato = FALSE;
				strcpy_s(pdfView.szDisco, "H");
				strcpy_s(pdfView.szPercorsoFileRemoto, "");

				CList<CArchivioStampeDlg::tagPDFVIEW> listViewPdf;
				listViewPdf.AddTail(pdfView);

				CString sTitle = "";

				CArchivioStampeDlg dlg(this, m_pEsamiView, &listViewPdf, sTitle, FALSE);
				dlg.DoModal();
			}
		}

		tempSet.CloseRecordset("CMonitoraggioVertDynForm::OnMonitoraggioListEv");
	}
}
