#include "stdafx.h"
#include "Endox.h"
#include "NomenclatoreListaPrestazRepartoDlg.h"

#include "CustomDate.h"
#include "EsamiView.h"
#include "InviantiSet.h"
#include "PrestazioneSet.h"

#define COL_PROV 0
#define COL_INV1 1
#define COL_INV2 2
#define COL_PRES 3
#define COL_CODI 4
#define COL_QUAN 5

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNomenclatoreListaPrestazRepartoDlg::CNomenclatoreListaPrestazRepartoDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, CString &sFiltroData, CString &sDataIniz, CString &sDataFine, CString &sSedeEsame, long lMedico, int nProvenienza)
	: CNomenclatoreRisDlg(pParentWnd, pEsamiView)
{
	m_sFiltroData = sFiltroData;
	m_sDataIniz = sDataIniz;
	m_sDataFine = sDataFine;
	m_sSedeEsame = sSedeEsame;
	m_lMedico = lMedico;
	m_nProvenienza = nProvenienza;
}

BOOL CNomenclatoreListaPrestazRepartoDlg::OnInitDialog()
{
	BOOL bReturn = CNomenclatoreRisDlg::OnInitDialog();

	m_ctrlListResult.InsertColumn(COL_PROV, theApp.GetMessageString(IDS_PROV), LVCFMT_LEFT);
	m_ctrlListResult.InsertColumn(COL_INV1, theApp.GetMessageString(IDS_INVIANTE1), LVCFMT_LEFT);
	m_ctrlListResult.InsertColumn(COL_INV2, theApp.GetMessageString(IDS_INVIANTE2), LVCFMT_LEFT);
	m_ctrlListResult.InsertColumn(COL_PRES, theApp.GetMessageString(IDS_PRESTAZIONE), LVCFMT_LEFT);
	m_ctrlListResult.InsertColumn(COL_CODI, theApp.GetMessageString(IDS_CODICE), LVCFMT_CENTER);
	m_ctrlListResult.InsertColumn(COL_QUAN, theApp.GetMessageString(IDS_QTA), LVCFMT_RIGHT);

	m_ctrlListResult.SetColumnWidth(COL_PROV,  78 + 5);
	m_ctrlListResult.SetColumnWidth(COL_INV1, 156);
	m_ctrlListResult.SetColumnWidth(COL_INV2, 156);
	m_ctrlListResult.SetColumnWidth(COL_PRES, 468);
	m_ctrlListResult.SetColumnWidth(COL_CODI,  78);
	m_ctrlListResult.SetColumnWidth(COL_QUAN,  39);

	m_ctrlListResult.SetColumnWidthForPrint(COL_PROV,  8);
	m_ctrlListResult.SetColumnWidthForPrint(COL_INV1, 16);
	m_ctrlListResult.SetColumnWidthForPrint(COL_INV2, 16);
	m_ctrlListResult.SetColumnWidthForPrint(COL_PRES, 44);
	m_ctrlListResult.SetColumnWidthForPrint(COL_CODI,  8);
	m_ctrlListResult.SetColumnWidthForPrint(COL_QUAN,  8);

	m_ctrlListResult.SetIntestazioneData(0, COL_PROV, 1, 1, theApp.GetMessageString(IDS_PROV));
	m_ctrlListResult.SetIntestazioneData(0, COL_INV1, 1, 1, theApp.GetMessageString(IDS_INVIANTE1));
	m_ctrlListResult.SetIntestazioneData(0, COL_INV2, 1, 1, theApp.GetMessageString(IDS_INVIANTE2));
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

BOOL CNomenclatoreListaPrestazRepartoDlg::RiempiLista()
{
	BeginWaitCursor();

	// prima di tutto controllo la provenienza perchè poi tutto il resto dipende da questo //
	int iProvMin = 0;
	int iProvMax = 1;
	switch(m_nProvenienza)
	{
		case 0: // solo interni //
		{
			iProvMax = 0;
			break;
		}
		case 1: // solo esterni //
		{
			iProvMin = 1;
			break;
		}
	}
	
	// inizio a riempire la lista //

	BOOL bFirst = TRUE;
	long lTotaleGenerale = 0;
	long lTotaleParzialeInviante1 = 0;
	long lTotaleParzialeInviante2 = 0;
	int nIndex = 0;
	CString strTmp = "";
	CString strPrevInv1;
	CString strPrevInv2;
	int iLastProv = iProvMin;

	CString strProv[2] = { theApp.GetMessageString(IDS_INVIANTE_INTERNO), theApp.GetMessageString(IDS_INVIANTE_ESTERNO) };
	strProv[0].MakeUpper();
	strProv[1].MakeUpper();

	CString strView[2] = { "VistaPrestazioniInterni ", "VistaPrestazioniEsterni " };
	for(int iProv = iProvMin; iProv <= iProvMax; iProv++)
	{
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

		CString strQuery = "SELECT CodiceNazionale, Descrizione, SUM(Quantita) AS SumQuantita, Inviante1, Inviante2 ";
		strQuery		+= "FROM " + strView[iProv];
		strQuery		+= "WHERE " + strFilter + " ";
		strQuery		+= "GROUP BY Inviante1, Inviante2, Descrizione, CodiceNazionale ";
		strQuery		+= "ORDER BY Inviante1, Inviante2, Descrizione, CodiceNazionale";

		// FINE costruzione filtro //

#ifdef _DEBUG
		theApp.AfxMessageBoxEndo(strQuery);
#endif

		CPrestazioneSet setPrestazioni;
		setPrestazioni.SetSortRecord("");
		setPrestazioni.GetRecordset()->Open(CRecordset::snapshot, strQuery, CRecordset::skipDeletedRecords);
		if (setPrestazioni.IsOpen())
		{
			while(!setPrestazioni.IsEOF())
			{
				if (bFirst)
				{
					bFirst = FALSE;
					strPrevInv1 = setPrestazioni.m_sInviante1;
					strPrevInv2 = setPrestazioni.m_sInviante2;

					m_ctrlListResult.InsertItem(nIndex, strProv[iProv]);
					m_ctrlListResult.SetItemText(nIndex, COL_INV1, setPrestazioni.m_sInviante1);
					m_ctrlListResult.SetItemText(nIndex, COL_INV2, setPrestazioni.m_sInviante2);
				}
				else
				{
					if ((iLastProv != iProv) || (strPrevInv1.Compare(setPrestazioni.m_sInviante1) != 0) || (strPrevInv2.Compare(setPrestazioni.m_sInviante2) != 0))
					{
						// nuovo inviante rispetto alla riga precedente quindi aggiungo il totale //
						m_ctrlListResult.InsertItem(nIndex, theApp.GetMessageString(IDS_PARZIALE));
						m_ctrlListResult.SetItemText(nIndex, COL_INV1, strProv[iLastProv] + " " + strPrevInv1);
						m_ctrlListResult.SetItemText(nIndex, COL_INV2, strPrevInv2);
						strTmp.Format("%li", lTotaleParzialeInviante2);
						m_ctrlListResult.SetItemText(nIndex, COL_QUAN, strTmp);
						lTotaleParzialeInviante2 = 0;
						nIndex++;

						// riga vuota per staccare //
						m_ctrlListResult.InsertItem(nIndex, "");
						nIndex++;

						// Sandro 16/12/2014 // SUBTOTALE suddiviso per Inviante 1 //
						if ((iLastProv != iProv) || (strPrevInv1.Compare(setPrestazioni.m_sInviante1) != 0))
						{
							// nuovo inviante rispetto alla riga precedente quindi aggiungo il subtotale //
							m_ctrlListResult.InsertItem(nIndex, theApp.GetMessageString(IDS_SUBTOTALE));
							m_ctrlListResult.SetItemText(nIndex, COL_INV1, strProv[iLastProv] + " " + strPrevInv1);
							strTmp.Format("%li", lTotaleParzialeInviante1);
							m_ctrlListResult.SetItemText(nIndex, COL_QUAN, strTmp);
							lTotaleParzialeInviante1 = 0;
							nIndex++;

							// riga vuota per staccare //
							m_ctrlListResult.InsertItem(nIndex, "");
							nIndex++;
						}

						// poi valorizzo le prime tre colonne //
						m_ctrlListResult.InsertItem(nIndex, strProv[iProv]);
						m_ctrlListResult.SetItemText(nIndex, COL_INV1, setPrestazioni.m_sInviante1);
						m_ctrlListResult.SetItemText(nIndex, COL_INV2, setPrestazioni.m_sInviante2);

						// salvo il nuovo inviante //
						strPrevInv1 = setPrestazioni.m_sInviante1;
						strPrevInv2 = setPrestazioni.m_sInviante2;

						//
						iLastProv = iProv;
					}
					else
					{
						// stesso inviante quindi non valorizzo le prime tre colonne //
						m_ctrlListResult.InsertItem(nIndex, "");
					}
				}

				m_ctrlListResult.SetItemText(nIndex, COL_PRES, setPrestazioni.m_sDescrizione);

				m_ctrlListResult.SetItemText(nIndex, COL_CODI, setPrestazioni.m_sCodice);

				strTmp.Format("%li", setPrestazioni.m_lSumQuantita);
				m_ctrlListResult.SetItemText(nIndex, COL_QUAN, strTmp);

				lTotaleGenerale += setPrestazioni.m_lSumQuantita;
				lTotaleParzialeInviante1 += setPrestazioni.m_lSumQuantita;
				lTotaleParzialeInviante2 += setPrestazioni.m_lSumQuantita;

				nIndex++;
				setPrestazioni.MoveNext();
			}

			setPrestazioni.CloseRecordset("CNomenclatoreListaPrestDlg::RiempiLista");
		}
	}

	if (lTotaleGenerale > 0)
	{
		// prima stampo l'ultimo parziale //
		m_ctrlListResult.InsertItem(nIndex, theApp.GetMessageString(IDS_PARZIALE));
		m_ctrlListResult.SetItemText(nIndex, COL_INV1, strProv[iLastProv] + " " + strPrevInv1);
		m_ctrlListResult.SetItemText(nIndex, COL_INV2, strPrevInv2);
		strTmp.Format("%li", lTotaleParzialeInviante2);
		m_ctrlListResult.SetItemText(nIndex, COL_QUAN, strTmp);
		lTotaleParzialeInviante2 = 0;
		nIndex++;

		// riga vuota per spaziare un po' //
		m_ctrlListResult.InsertItem(nIndex, "");
		nIndex++;

		// Sandro 16/12/2014 // SUBTOTALE suddiviso per Inviante 1 //
		m_ctrlListResult.InsertItem(nIndex, theApp.GetMessageString(IDS_SUBTOTALE));
		m_ctrlListResult.SetItemText(nIndex, COL_INV1, strProv[iLastProv] + " " + strPrevInv1);
		strTmp.Format("%li", lTotaleParzialeInviante1);
		m_ctrlListResult.SetItemText(nIndex, COL_QUAN, strTmp);
		lTotaleParzialeInviante1 = 0;
		nIndex++;

		// riga vuota per spaziare un po' //
		m_ctrlListResult.InsertItem(nIndex, "");
		nIndex++;

		// totale generale //
		m_ctrlListResult.InsertItem(nIndex, theApp.GetMessageString(IDS_TOTALE));
		strTmp.Format("%li", lTotaleGenerale);
		m_ctrlListResult.SetItemText(nIndex, COL_QUAN, strTmp);
	}
	
	if (lTotaleGenerale == 0)
	{
		EndWaitCursor();
		return IDS_NOMENCLATOR_EMPTY_RESULT;
	}

	EndWaitCursor();
	return 0; // tutto OK //
}