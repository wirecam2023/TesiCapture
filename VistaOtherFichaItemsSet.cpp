#include "stdafx.h"
#include "Endox.h"
#include "UOSet.h"
#include "VistaOtherFichaItemsSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaOtherFichaItemsSet, CBaseSet)

CVistaOtherFichaItemsSet::CVistaOtherFichaItemsSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetEmpty();
	SetSortRecord("FICHAITEM");

	m_nFields = 7;
}

CString CVistaOtherFichaItemsSet::GetDefaultSQL()
{
	return "VISTAOTHERFICHAITEMS";
}

void CVistaOtherFichaItemsSet::SetEmpty()
{
	m_sFichaItem = "";
	m_sCodice = "";
	m_sDescrizione = "";
	m_lIDEsameIns = 0;
	m_bSuperlocked = FALSE;
	m_sRefertoConiugatoPrincipale = "";
	m_sRefertoConiugatoSecondario = "";
}

void CVistaOtherFichaItemsSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "FICHAITEM", m_sFichaItem, 50);
	RFX_Text(pFX, "CODICE", m_sCodice, 50);
	RFX_Text(pFX, "DESCRIZIONE", m_sDescrizione, 4000);
	RFX_Long(pFX, "IDESAMEINS", m_lIDEsameIns);
	RFX_Bool(pFX, "SUPERLOCKED", m_bSuperlocked);
	RFX_Text(pFX, "REFERTOCONIUGATOPRINCIPALE", m_sRefertoConiugatoPrincipale, 50);
	RFX_Text(pFX, "REFERTOCONIUGATOSECONDARIO", m_sRefertoConiugatoSecondario, 50);
}

CString CVistaOtherFichaItemsSet::GetFleuryListOtherFichaItems(CString sFichaItem, CList<STRUCT_FICHA_ITEM> *pListFichaItem)
{
	CString sCurUOReturn = "";

	pListFichaItem->RemoveAll();

	sFichaItem.Trim();
	if (!sFichaItem.IsEmpty())
	{
		int nFindUnderscore = sFichaItem.Find('_');
		if (nFindUnderscore > 0)
		{
			CString sFichaItemFilter = sFichaItem.Left(nFindUnderscore + 1);

			CString sFilter;
			// Luiz - 11/02/2019 - P3 - Dependendo da Configuração (Ricerca UO limitata), impedir que itens de outra especialidade na conjugacao
			//sFilter.Format("FICHAITEM LIKE '%s%%' AND ((SUPERLOCKED IS NULL) OR (SUPERLOCKED=0)) AND ((REFERTOCONIUGATOPRINCIPALE IS NULL) OR (REFERTOCONIUGATOPRINCIPALE LIKE '')) AND ((REFERTOCONIUGATOSECONDARIO IS NULL) OR (REFERTOCONIUGATOSECONDARIO LIKE ''))", sFichaItemFilter);
			if (theApp.m_bRicercaUOLimitata){
				CString sCodiceFichaItem = CUOSet().GetCodiceIntegrazione(theApp.m_lUO, FALSE);
				sFilter.Format("FICHAITEM LIKE '%s%%' AND ((SUPERLOCKED IS NULL) OR (SUPERLOCKED=0)) AND ((REFERTOCONIUGATOPRINCIPALE IS NULL) OR (REFERTOCONIUGATOPRINCIPALE LIKE '')) AND ((REFERTOCONIUGATOSECONDARIO IS NULL) OR (REFERTOCONIUGATOSECONDARIO LIKE '')) AND CODICE =  '%s'", sFichaItemFilter, sCodiceFichaItem);
			}
			else{
				sFilter.Format("FICHAITEM LIKE '%s%%' AND ((SUPERLOCKED IS NULL) OR (SUPERLOCKED=0)) AND ((REFERTOCONIUGATOPRINCIPALE IS NULL) OR (REFERTOCONIUGATOPRINCIPALE LIKE '')) AND ((REFERTOCONIUGATOSECONDARIO IS NULL) OR (REFERTOCONIUGATOSECONDARIO LIKE ''))", sFichaItemFilter);
			}
			SetOpenFilter(sFilter);
			SetSortRecord("FICHAITEM");
			if (OpenRecordset("CVistaOtherFichaItemsSet::GetFleuryListOtherFichaItems"))
			{
				long lCount = 0;

				while (!IsEOF())
				{
					if (sFichaItem.CompareNoCase(m_sFichaItem) == 0)
						sCurUOReturn = m_sCodice;
					else
						lCount++;

					MoveNext();
				}

				if (lCount > 0)
				{
					MoveFirst();
					while (!IsEOF())
					{
						if (sFichaItem.CompareNoCase(m_sFichaItem) != 0)
						{
							// if (m_sRefertoConiugatoPrincipale.IsEmpty() && m_sRefertoConiugatoSecondario.IsEmpty())
							{
								STRUCT_FICHA_ITEM structFichaItemTemp;
								strcpy_s(structFichaItemTemp.szFichaItem, m_sFichaItem.Left(50));
								strcpy_s(structFichaItemTemp.szCodice, m_sCodice.Left(50));
								strcpy_s(structFichaItemTemp.szDescrizione, m_sDescrizione.Left(255));
								structFichaItemTemp.bStessaUO = (sCurUOReturn.CompareNoCase(m_sCodice) == 0);

								pListFichaItem->AddTail(structFichaItemTemp);
							}
						}

						MoveNext();
					}
				}

				CloseRecordset("CVistaOtherFichaItemsSet::GetFleuryListOtherFichaItems");
			}
		}
	}

	return sCurUOReturn;
}
