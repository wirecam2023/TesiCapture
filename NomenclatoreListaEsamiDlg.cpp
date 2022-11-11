#include "stdafx.h"
#include "Endox.h"
#include "NomenclatoreListaEsamiDlg.h"

#include "CustomDate.h"
#include "EsamiView.h"
#include "PrestazioneSet.h"

#define COL_PRES 0
#define COL_CODI 1
#define COL_QUAN 2

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNomenclatoreListaEsamiDlg::CNomenclatoreListaEsamiDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, CString &sFiltroData, CString &sDataIniz, CString &sDataFine, CString &sSedeEsame, long lMedico, int nProvenienza)
	: CNomenclatoreRisDlg(pParentWnd, pEsamiView)
{
	m_sFiltroData = sFiltroData;
	m_sDataIniz = sDataIniz;
	m_sDataFine = sDataFine;
	m_sSedeEsame = sSedeEsame;
	m_lMedico = lMedico;
	m_nProvenienza = nProvenienza;
}

BOOL CNomenclatoreListaEsamiDlg::OnInitDialog()
{
	BOOL bReturn = CNomenclatoreRisDlg::OnInitDialog();

	m_ctrlListResult.InsertColumn(COL_PRES, theApp.GetMessageString(IDS_PRESTAZIONE), LVCFMT_LEFT);
	m_ctrlListResult.InsertColumn(COL_CODI, theApp.GetMessageString(IDS_CODICE), LVCFMT_CENTER);
	m_ctrlListResult.InsertColumn(COL_QUAN, theApp.GetMessageString(IDS_QTA), LVCFMT_RIGHT);

	m_ctrlListResult.SetColumnWidth(COL_PRES, 500);
	m_ctrlListResult.SetColumnWidth(COL_CODI, 100);
	m_ctrlListResult.SetColumnWidth(COL_QUAN,  50);

	m_ctrlListResult.SetColumnWidthForPrint(COL_PRES, 80);
	m_ctrlListResult.SetColumnWidthForPrint(COL_CODI, 10);
	m_ctrlListResult.SetColumnWidthForPrint(COL_QUAN, 10);

	m_ctrlListResult.SetIntestazioneData(0, COL_PRES, 1, 1, theApp.GetMessageString(IDS_PRESTAZIONE));
	m_ctrlListResult.SetIntestazioneData(0, COL_CODI, 1, 1, theApp.GetMessageString(IDS_CODICE));
	m_ctrlListResult.SetIntestazioneData(0, COL_QUAN, 1, 1, theApp.GetMessageString(IDS_QTA));

	UINT uiMessage = RiempiLista();
	if (uiMessage > 0)
	{	
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(uiMessage));
		EndDialog(IDCANCEL);
	}

	return bReturn;
}

UINT CNomenclatoreListaEsamiDlg::RiempiLista()
{
	BeginWaitCursor();

	// INIZIO costruzione filtro //

	CString strFilter = m_sFiltroData;
	strFilter.Trim();

	m_sSedeEsame.Trim();
	if (!m_sSedeEsame.IsEmpty())
	{
		CString sSedeTemp = m_sSedeEsame;
		sSedeTemp.Replace("'", "''");

		if (!strFilter.IsEmpty())
			strFilter += " AND ";

		strFilter += "SedeEsame='" + sSedeTemp + "'";
		strFilter.Trim();
	}

	if (m_lMedico > 0)
	{
		CString strMed;
		strMed.Format("Medico=%li", m_lMedico);

		if (!strFilter.IsEmpty())
			strFilter += " AND ";

		strFilter += strMed;
		strFilter.Trim();
	}

	if ((m_nProvenienza == 0) || (m_nProvenienza == 1))
	{
		CString strPro;
		strPro.Format("Provenienza=%d", m_nProvenienza);

		if (!strFilter.IsEmpty())
			strFilter += " AND ";

		strFilter += strPro;
		strFilter.Trim();
	}

	if (theApp.m_lUO > 0)
	{
		CString strUo;
		strUo.Format("Uo=%d", theApp.m_lUO);

		if (!strFilter.IsEmpty())
			strFilter += " AND ";

		strFilter += strUo;
		strFilter.Trim();
	}

	if (strFilter.IsEmpty())
	{
		EndWaitCursor();
		return IDS_NOMENCLATOR_EMPTY_FILTER;
	}

	CString strQuery = "SELECT CodiceNazionale, Descrizione, SUM(Quantita) AS SumQuantita ";
	strQuery		+= "FROM VISTAESAMI ";
	strQuery		+= "WHERE " + strFilter + " ";
	strQuery		+= "GROUP BY Descrizione, CodiceNazionale ";
	strQuery		+= "ORDER BY Descrizione, CodiceNazionale";

	// FINE costruzione filtro //

#ifdef _DEBUG
	theApp.AfxMessageBoxEndo(strQuery);
#endif

	long lTotale = 0;
	int nIndex = 0;
	CString strTmp = "";

	CPrestazioneSet setPrestazioni;
	setPrestazioni.SetSortRecord("");
	setPrestazioni.GetRecordset()->Open(CRecordset::snapshot, strQuery, CRecordset::skipDeletedRecords);
	if (setPrestazioni.IsOpen())
	{
		while(!setPrestazioni.IsEOF())
		{
			m_ctrlListResult.InsertItem(nIndex, setPrestazioni.m_sDescrizione);

			m_ctrlListResult.SetItemText(nIndex, COL_CODI, setPrestazioni.m_sCodice);

			strTmp.Format("%li", setPrestazioni.m_lSumQuantita);
			m_ctrlListResult.SetItemText(nIndex, COL_QUAN, strTmp);

			lTotale += setPrestazioni.m_lSumQuantita;

			nIndex++;
			setPrestazioni.MoveNext();
		}

		setPrestazioni.CloseRecordset("CNomenclatoreListaEsamiDlg::RiempiLista");
	}
	
	if (lTotale > 0)
	{
		m_ctrlListResult.InsertItem(nIndex, theApp.GetMessageString(IDS_TOTALE));
		strTmp.Format("%li", lTotale);
		m_ctrlListResult.SetItemText(nIndex, COL_QUAN, strTmp);
	}
	
	if (lTotale == 0)
	{
		EndWaitCursor();
		return IDS_NOMENCLATOR_EMPTY_RESULT;
	}

	EndWaitCursor();
	return 0; // tutto OK //
}