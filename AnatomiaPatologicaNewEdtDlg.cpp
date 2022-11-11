#include "stdafx.h"
#include "Endox.h"
#include "AnatomiaPatologicaNewEdtDlg.h"

#include "AnatomiaPatologicaEsamiPrestSet.h"
#include "AnatomiaPatologicaIntervSet.h"
#include "AnatomiaPatologicaSet.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "SediEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAnatomiaPatologicaNewEdtDlg, CDialog)

CAnatomiaPatologicaNewEdtDlg::CAnatomiaPatologicaNewEdtDlg(CWnd* pParent, CEsamiView* pEsamiView, long lRecord)
	: CDialog(CAnatomiaPatologicaNewEdtDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
	m_lRecord = lRecord;
}

CAnatomiaPatologicaNewEdtDlg::~CAnatomiaPatologicaNewEdtDlg()
{
}

BEGIN_MESSAGE_MAP(CAnatomiaPatologicaNewEdtDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_TIPO, OnCbnSelchangeComboTipo)
END_MESSAGE_MAP()

void CAnatomiaPatologicaNewEdtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);

	DDX_Control(pDX, IDC_EDIT_CAMPIONE, m_ctrlEditCampione);
	DDX_Control(pDX, IDC_COMBO_TIPO, m_ctrlComboTipo);
	DDX_Control(pDX, IDC_COMBO_INTERVENTO, m_ctrlComboIntervento);
	DDX_Control(pDX, IDC_EDIT_PRELIEVI, m_ctrlEditPrelievi);
	DDX_Control(pDX, IDC_EDIT_DESCRIZIONE, m_ctrlEditDescrizione);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
}

BOOL CAnatomiaPatologicaNewEdtDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	// EDT CAMPIONE //

	// CMB TIPO //
	m_ctrlComboTipo.AddString(theApp.GetMessageString(IDS_CITOLOGICO));
	m_ctrlComboTipo.AddString(theApp.GetMessageString(IDS_ISTOLOGICO));

	// CMB INTERVENTO //

	// EDT PRELIEVI //

	// EDT DESCRIZIONE //
	m_ctrlEditDescrizione.SetLimitText(255);

	if (m_lRecord <= 0)
	{
		// NEW //

		// CMB TIPO //
		m_ctrlComboTipo.SetCurSel(1);
		OnCbnSelchangeComboTipo();

		// CMB INTERVENTO //
		m_ctrlComboIntervento.SetFocus();
		m_ctrlComboIntervento.ShowDropDown(TRUE);
	}
	else
	{
		// EDIT //

		CString strFilter;
		strFilter.Format("ID=%li", m_lRecord);

		CAnatomiaPatologicaSet setAP;
		setAP.SetOpenFilter(strFilter);
		if (setAP.OpenRecordset("CAnatomiaPatologicaNewEdtDlg::OnInitDialog"))
		{
			if (!setAP.IsEOF())
			{
				int nIndexFound;
				CString strTemp;

				// EDT CAMPIONE //
				m_ctrlEditCampione.SetWindowText(setAP.m_sIDCampione);

				// CMB TIPO //
				nIndexFound = m_ctrlComboTipo.FindString(-1, setAP.m_sTipo);
				if (nIndexFound >= 0)
				{
					m_ctrlComboTipo.SetCurSel(nIndexFound);
					OnCbnSelchangeComboTipo();
				}

				// CMB INTERVENTO //
				nIndexFound = m_ctrlComboIntervento.FindStringExact(-1, setAP.m_sIntervProcedura);
				if (nIndexFound >= 0)
					m_ctrlComboIntervento.SetCurSel(nIndexFound);

				// EDT PRELIEVI //
				if (!setAP.IsFieldNull(&setAP.m_lPrelievi) && setAP.m_lPrelievi > 0)
				{
					strTemp.Format("%li", setAP.m_lPrelievi);
					m_ctrlEditPrelievi.SetWindowText(strTemp);
				}

				// EDT DESCRIZIONE //
				m_ctrlEditDescrizione.SetWindowText(setAP.m_sDescrizione);

			}
			setAP.CloseRecordset("CAnatomiaPatologicaNewEdtDlg::OnInitDialog");
		}
	}

	theApp.LocalizeDialog(this, CAnatomiaPatologicaNewEdtDlg::IDD, "AnatomiaPatologicaNewEdtDlg");

	if (m_lRecord <= 0)
		SetWindowText(theApp.GetMessageString(IDS_INSERIMENTO_NUOVA_PROVETTA));	// NEW //
	else
		SetWindowText(theApp.GetMessageString(IDS_MODIFICA_PROVETTA));			// EDIT //

	return bReturn;
}

void CAnatomiaPatologicaNewEdtDlg::OnOK()
{
	// EDT CAMPIONE //

	// CMB TIPO //
	CString sTipo = "";
	m_ctrlComboTipo.GetWindowText(sTipo);
	if (sTipo.GetLength() <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPAT_ERROR1));
		return;
	}
	sTipo = sTipo.Left(1);

	// CMB INTERVENTO //
	CString sCodice = "";
	CString sDescrizioneNew = "";
	long lIDPrestazione = 0;
	CString sDescrizioneAnatomia = "";
	int nIndexFound = m_ctrlComboIntervento.GetCurSel();
	if (nIndexFound >= 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", (long)m_ctrlComboIntervento.GetItemData(nIndexFound));

		CAnatomiaPatologicaIntervSet setInterv;
		setInterv.SetOpenFilter(strFilter);
		if (setInterv.OpenRecordset("CAnatomiaPatologicaNewEdtDlg::OnOK"))
		{
			if (!setInterv.IsEOF())
			{
				sCodice = setInterv.m_sCodice;
				sDescrizioneNew = setInterv.m_sDescrizione;
				lIDPrestazione = setInterv.m_lIDPrestazione;
				sDescrizioneAnatomia = setInterv.m_sDescrizioneAnatomia;
			}

			setInterv.CloseRecordset("CAnatomiaPatologicaNewEdtDlg::OnOK");
		}
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPAT_ERROR2));
		return;
	}

	// EDT PRELIEVI //
	CString sPrelieviTemp;
	m_ctrlEditPrelievi.GetWindowText(sPrelieviTemp);
	long lPrelievi = atol(sPrelieviTemp);
	if (lPrelievi <= 0)
	{
		// Sandro 01/03/2010 - RAS 20100009 //
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPAT_ERROR4));
		return;
	}

	// EDT DESCRIZIONE //
	CString sDescrizione;
	m_ctrlEditDescrizione.GetWindowText(sDescrizione);

	if (m_lRecord <= 0)
	{
		// NEW //

		CString strFilter;
		strFilter.Format("IDEsame=%li", m_lIDEsame);

		CAnatomiaPatologicaSet setAP;
		setAP.SetOpenFilter(strFilter);
		if (setAP.OpenRecordset("CAnatomiaPatologicaNewEdtDlg::OnOK"))
		{
			long lIDCampione = 1;

			if (!setAP.IsEOF())
			{
				CString strQuery;
				strQuery.Format("SELECT MAX(IDCampione) AS CONTEGGIO FROM AnatomiaPatologica WHERE IDEsame=%li AND Eliminato=0", m_lIDEsame);

				CRecordset setCount(&theApp.m_dbEndox); // è solo per il conteggio //
				setCount.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);
				if (!setCount.IsEOF())
				{
					// con i driver Oracle 9.2 si pianta tutto //
					// CDBVariant dbVariant;
					// setCount.GetFieldValue((short)0 oppure "CONTEGGIO", dbVariant, SQL_C_SLONG);
					// lIDCampione = (dbVariant.m_lVal % 100) + 1;

					// così sembra funzionare invece //
					CString sValue;
					setCount.GetFieldValue("CONTEGGIO", sValue);
					if (sValue.GetLength() > 2)
						sValue = sValue.Right(2);
					lIDCampione = (atol(sValue) % 100) + 1;
				}
				setCount.Close();
			}

			if (setAP.AddNewRecordset("CAnatomiaPatologicaNewEdtDlg::OnOK"))
			{
				CAnatomiaPatologicaEsamiPrestSet setPrestEsame;

				setAP.m_lIDEsame = m_lIDEsame;
				setAP.m_sIDCampione.Format("%08li%02li", m_lIDEsame, lIDCampione);
				setAP.m_sTipo = sTipo;
				setAP.m_sIntervCodice = sCodice;
				setAP.m_sIntervProcedura = sDescrizioneNew;
				setAP.m_lPrelievi = lPrelievi;
				setAP.m_sDescrizione = sDescrizione;
				setAP.m_lIDPrestazioneAssociata = setPrestEsame.AddPrestazione(m_lIDEsame, lIDPrestazione);
				setAP.m_sDescrizioneAnatomia = sDescrizioneAnatomia;

				setAP.UpdateRecordset("CAnatomiaPatologicaNewEdtDlg::OnOK");
			}
			setAP.CloseRecordset("CAnatomiaPatologicaNewEdtDlg::OnOK");
		}
	}
	else
	{
		// EDIT //

		CString strFilter;
		strFilter.Format("ID=%li", m_lRecord);

		CAnatomiaPatologicaSet setAP;
		setAP.SetOpenFilter(strFilter);
		if (setAP.OpenRecordset("CAnatomiaPatologicaNewEdtDlg::OnOK"))
		{
			if (!setAP.IsEOF())
			{
				if (setAP.EditRecordset("CAnatomiaPatologicaNewEdtDlg::OnOK"))
				{
					CAnatomiaPatologicaEsamiPrestSet setPrestEsame;

					setAP.m_sTipo = sTipo;
					setAP.m_sIntervCodice = sCodice;
					setAP.m_sIntervProcedura = sDescrizioneNew;
					setAP.m_lPrelievi = lPrelievi;
					setAP.m_sDescrizione = sDescrizione;
					setPrestEsame.EdtPrestazione(setAP.m_lIDPrestazioneAssociata, lIDPrestazione);
					setAP.m_sDescrizioneAnatomia = sDescrizioneAnatomia;

					setAP.UpdateRecordset("CAnatomiaPatologicaNewEdtDlg::OnOK");
				}
			}
			setAP.CloseRecordset("CAnatomiaPatologicaNewEdtDlg::OnOK");
		}
	}

	CDialog::OnOK();
}

void CAnatomiaPatologicaNewEdtDlg::OnCbnSelchangeComboTipo()
{
	CString strComboTipo;
	m_ctrlComboTipo.GetWindowText(strComboTipo);

	m_ctrlComboIntervento.ResetContent();

	if (strComboTipo.GetLength() > 0)
	{
		strComboTipo = strComboTipo.Left(1);

		CString strFilter;
		strFilter.Format("Tipo='%s' AND APSede='%s'", strComboTipo, CSediEsameSet().GetAPSede(m_pEsamiView->m_pEsamiSet->m_lIDSedeEsame));

		CAnatomiaPatologicaIntervSet setTemp;
		setTemp.SetOpenFilter(strFilter);
		setTemp.SetSortRecord("ID");
		if (setTemp.OpenRecordset("CAnatomiaPatologicaNewEdtDlg::OnCbnSelchangeComboTipo"))
		{
			int nTemp;
			while(!setTemp.IsEOF())
			{
				nTemp = m_ctrlComboIntervento.AddString(setTemp.m_sDescrizione);
				m_ctrlComboIntervento.SetItemData(nTemp, (DWORD)setTemp.m_lID);

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CAnatomiaPatologicaNewEdtDlg::OnCbnSelchangeComboTipo");
		}
	}
}