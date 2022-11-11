#include "stdafx.h"
#include "Endox.h"
#include "VistaMediciSedeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaMediciSedeSet, CBaseSet)

CVistaMediciSedeSet::CVistaMediciSedeSet()
	: CBaseSet(NULL, "VIEW")
{
	SetBaseFilter("");
	SetEmpty();
	SetSortRecord("Contatore");

	m_nFields = 8;
}

CString CVistaMediciSedeSet::GetDefaultSQL()
{
	return "VistaMediciSede";
}

void CVistaMediciSedeSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	RFX_Text(pFX, "Codice", m_sCodice, 50);
	RFX_Text(pFX, "Titolo", m_sTitolo, 50);
	RFX_Text(pFX, "Cognome", m_sCognome, 50);
	RFX_Text(pFX, "Nome", m_sNome, 50);
	RFX_Bool(pFX, "Libero", m_bLibero);
	RFX_Bool(pFX, "Eliminato", m_bEliminato);
	RFX_Long(pFX, "UO", m_lUO);
}

void CVistaMediciSedeSet::SetEmpty()
{
	m_lContatore = 0;
	m_sCodice = "";
	m_sTitolo = "";
	m_sCognome = "";
	m_sNome = "";
	m_bLibero = FALSE;
	m_bEliminato = FALSE;
	m_lUO = 0;
}

CString CVistaMediciSedeSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO + " AND ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

// Sandro 15/12/2015 // RAS 20150065 //

void CVistaMediciSedeSet::FillListByAll(CList<CQueryFormListDlg::tagITEM>* pListRecord)
{
	CString sFilter;
	sFilter.Format("IDSede=%li", theApp.m_lIDSedeEsameDefault);
	SetOpenFilter(sFilter);

	SetSortRecord("Codice");

	FillListByFilter(pListRecord);
}

void CVistaMediciSedeSet::FillListByCodice(CString sCodice, CList<CQueryFormListDlg::tagITEM>* pListRecord)
{
	CString sFilter;
	sFilter.Format("IDSede=%li AND UPPER(Codice)='%s'", theApp.m_lIDSedeEsameDefault, sCodice);
	SetOpenFilter(sFilter);

	SetSortRecord("Codice");

	FillListByFilter(pListRecord);
}

void CVistaMediciSedeSet::FillListByCodiceLike(CString sCodice, CList<CQueryFormListDlg::tagITEM>* pListRecord)
{
	CString sFilter;
	sFilter.Format("IDSede=%li AND UPPER(Codice) LIKE '%s%%'", theApp.m_lIDSedeEsameDefault, sCodice);
	SetOpenFilter(sFilter);

	SetSortRecord("Codice");

	FillListByFilter(pListRecord);
}

void CVistaMediciSedeSet::FillListByContatore(long lContatore, CList<CQueryFormListDlg::tagITEM>* pListRecord)
{
	CString sFilter;
	sFilter.Format("IDSede=%li AND Contatore=%li", theApp.m_lIDSedeEsameDefault, lContatore);
	SetOpenFilter(sFilter);

	SetSortRecord("Contatore");

	FillListByFilter(pListRecord);
}

void CVistaMediciSedeSet::FillListByDescrizione(CString sDescrizione, CList<CQueryFormListDlg::tagITEM>* pListRecord)
{
	CString sFilter;
	sFilter.Format("IDSede=%li AND (UPPER(Cognome)='%s' OR UPPER(Nome)='%s')", theApp.m_lIDSedeEsameDefault, sDescrizione, sDescrizione);
	SetOpenFilter(sFilter);

	SetSortRecord("Cognome, Nome");
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
		SetSortRecord("Nome, Cognome");

	FillListByFilter(pListRecord);
}

void CVistaMediciSedeSet::FillListByDescrizioneLike(CString sDescrizione, CList<CQueryFormListDlg::tagITEM>* pListRecord)
{
	CString sFilter;
	sFilter.Format("IDSede=%li AND (UPPER(Cognome) LIKE '%%%s%%' OR UPPER(Nome) LIKE '%%%s%%')", theApp.m_lIDSedeEsameDefault, sDescrizione, sDescrizione);
	SetOpenFilter(sFilter);

	SetSortRecord("Cognome, Nome");
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
		SetSortRecord("Nome, Cognome");

	FillListByFilter(pListRecord);
}

void CVistaMediciSedeSet::FillListByFilter(CList<CQueryFormListDlg::tagITEM>* pListRecord)
{
	pListRecord->RemoveAll();

	if (OpenRecordset("CVistaMediciSedeSet::FillListByFilter"))
	{
		while (!IsEOF())
		{
			CString sDescrizione = m_sTitolo + " " + m_sCognome + " " + m_sNome;
			sDescrizione.Trim();

			if (!sDescrizione.IsEmpty())
			{
				CQueryFormListDlg::tagITEM record;

				record.lContatore = m_lContatore;
				strcpy_s(record.szCodice, m_sCodice);
				strcpy_s(record.szDescrizione, sDescrizione);
				record.bLibero = m_bLibero;

				pListRecord->AddTail(record);
			}

			MoveNext();
		}

		CloseRecordset("CVistaMediciSedeSet::FillListByFilter");
	}
}
