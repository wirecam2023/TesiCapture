#include "stdafx.h"
#include "Endox.h"
#include "FrasiRisultatoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFrasiRisultatoSet, CBaseSet)


CFrasiRisultatoSet::CFrasiRisultatoSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 14; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
}

CString CFrasiRisultatoSet::GetDefaultSQL()
{
	return "FrasiRisultato";
}

void CFrasiRisultatoSet::SetEmpty()
{
	m_lID = 0;
	m_lIDTipoVariante = 0; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	//m_lIDPatogenicita = 0; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	m_sTitoloRisultato = ""; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	m_sTitoloComplemento = ""; //Julio BUG 3791 - Melhoria frases resultado laudo genomica	
	m_sPositivoSingolare = "";
	m_sPositivoPlurale = "";
	m_sPositivoVariante = "";
	m_sNegativoSingolare = "";
	m_sComplementoSingolare = "";
	m_sComplementoPlurale = "";
	m_sComplementoNegativo = "";
	m_sComplementoVariante = "";
	m_sNegativoNegativo = "";
	m_bEliminato = FALSE;
}

void CFrasiRisultatoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDTipoVariante", m_lIDTipoVariante); //Julio BUG 3791 - Melhoria frases resultado laudo genomica
		//RFX_Long(pFX, "IDPatogenicita", m_lIDPatogenicita); //Julio BUG 3791 - Melhoria frases resultado laudo genomica
		RFX_Text(pFX, "TitoloRisultato", m_sTitoloRisultato, 512); //Julio BUG 3791 - Melhoria frases resultado laudo genomica
		RFX_Text(pFX, "TitoloComplemento", m_sTitoloComplemento, 512); //Julio BUG 3791 - Melhoria frases resultado laudo genomica
		RFX_Text(pFX, "PositivoSingolare", m_sPositivoSingolare, 512);
		RFX_Text(pFX, "PositivoPlurale", m_sPositivoPlurale, 512);
		RFX_Text(pFX, "PositivoVariante", m_sPositivoVariante, 512);
		RFX_Text(pFX, "NegativoSingolare", m_sNegativoSingolare, 512);
		RFX_Text(pFX, "ComplementoSingolare", m_sComplementoSingolare, 512);
		RFX_Text(pFX, "ComplementoPlurale", m_sComplementoPlurale, 512);
		RFX_Text(pFX, "ComplementoNegativo", m_sComplementoNegativo, 512);
		RFX_Text(pFX, "ComplementoVariante", m_sComplementoVariante, 512);
		RFX_Text(pFX, "NegativoNegativo", m_sNegativoNegativo, 512);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CFrasiRisultatoSet::CreateNew()
{
	return (CBaseSet*)new CFrasiRisultatoSet;
}

void CFrasiRisultatoSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CFrasiRisultatoSet* pSet = (CFrasiRisultatoSet*)pOriginalSet;

	//Julio BUG 3791 - Melhoria frases resultado laudo genomica
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoVariante) || bCopyAll)
		m_lIDTipoVariante = pSet->m_lIDTipoVariante;
	/*if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDPatogenicita) || bCopyAll)
		m_lIDPatogenicita = pSet->m_lIDPatogenicita;*/
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTitoloRisultato) || bCopyAll)
		m_sTitoloRisultato = pSet->m_sTitoloRisultato;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTitoloComplemento) || bCopyAll)
		m_sTitoloComplemento = pSet->m_sTitoloComplemento;
	//
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPositivoSingolare) || bCopyAll)
		m_sPositivoSingolare = pSet->m_sPositivoSingolare;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPositivoPlurale) || bCopyAll)
		m_sPositivoPlurale = pSet->m_sPositivoPlurale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPositivoVariante) || bCopyAll)
		m_sPositivoVariante = pSet->m_sPositivoVariante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNegativoSingolare) || bCopyAll)
		m_sNegativoSingolare = pSet->m_sNegativoSingolare;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sComplementoSingolare) || bCopyAll)
		m_sComplementoSingolare = pSet->m_sComplementoSingolare;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sComplementoPlurale) || bCopyAll)
		m_sComplementoPlurale = pSet->m_sComplementoPlurale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sComplementoNegativo) || bCopyAll)
		m_sComplementoNegativo = pSet->m_sComplementoNegativo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sComplementoVariante) || bCopyAll)
		m_sComplementoVariante = pSet->m_sComplementoVariante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNegativoNegativo) || bCopyAll)
		m_sNegativoNegativo = pSet->m_sNegativoNegativo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}
void CFrasiRisultatoSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CFrasiRisultatoSet* pOV = (CFrasiRisultatoSet*)pOldValues;
	CFrasiRisultatoSet* pNV = (CFrasiRisultatoSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);
	
	//Julio BUG 3791 - Melhoria frases resultado laudo genomica
	sp.Execute("IDTipoVariante", pOV, &pOV->m_lIDTipoVariante, pNV, &pNV->m_lIDTipoVariante);
	//sp.Execute("IDPatogenicita", pOV, &pOV->m_lIDPatogenicita, pNV, &pNV->m_lIDPatogenicita);
	sp.Execute("TitoloRisultato", pOV, &pOV->m_sTitoloRisultato, pNV, &pNV->m_sTitoloRisultato);
	sp.Execute("TitoloComplemento", pOV, &pOV->m_sTitoloComplemento, pNV, &pNV->m_sTitoloComplemento);
	//
	sp.Execute("PositivoSingolare", pOV, &pOV->m_sPositivoSingolare, pNV, &pNV->m_sPositivoSingolare);
	sp.Execute("PositivoPlurale", pOV, &pOV->m_sPositivoPlurale, pNV, &pNV->m_sPositivoPlurale);
	sp.Execute("PositivoVariante", pOV, &pOV->m_sPositivoVariante, pNV, &pNV->m_sPositivoVariante);
	sp.Execute("NegativoSingolare", pOV, &pOV->m_sNegativoSingolare, pNV, &pNV->m_sNegativoSingolare);	
	sp.Execute("ComplementoSingolare", pOV, &pOV->m_sComplementoSingolare, pNV, &pNV->m_sComplementoSingolare);
	sp.Execute("ComplementoPlurale", pOV, &pOV->m_sComplementoPlurale, pNV, &pNV->m_sComplementoPlurale);
	sp.Execute("ComplementoNegativo", pOV, &pOV->m_sComplementoNegativo, pNV, &pNV->m_sComplementoNegativo);
	sp.Execute("ComplementoVariante", pOV, &pOV->m_sComplementoVariante, pNV, &pNV->m_sComplementoVariante);
	sp.Execute("NegativoNegativo", pOV, &pOV->m_sNegativoNegativo, pNV, &pNV->m_sNegativoNegativo);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CFrasiRisultatoSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("::DeleteRecordset");
	}
	return bReturn;
}

CString CFrasiRisultatoSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty() == TRUE)
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO") == -1)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CFrasiRisultatoSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

//
CString CFrasiRisultatoSet::GetTitoloRisultato()
{
	CString sResult = "";

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);
	//

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::GetTitoloRisultato"))
	{
		if (!IsEOF())
			sResult = m_sTitoloRisultato;

		CloseRecordset("CFrasiRisultatoSet::GetTitoloRisultato");
	}

	return sResult;
}
BOOL CFrasiRisultatoSet::SetTitoloRisultato(CString sTitolo)
{
	BOOL bResult = FALSE;

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::SetTitoloRisultato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFrasiRisultatoSet::SetTitoloRisultato"))
			{
				m_sTitoloRisultato = sTitolo;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetTitoloRisultato");
			}
		}
		else
		{
			if (AddNewRecordset("CFrasiRisultatoSet::SetTitoloRisultato"))
			{
				m_sTitoloRisultato = sTitolo;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetTitoloRisultato");
			}
		}
		CloseRecordset("CFrasiRisultatoSet::SetTitoloRisultato");
	}

	return bResult;
}

CString CFrasiRisultatoSet::GetTitoloComplemento()
{
	CString sResult = "";

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);
	//

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::GetTitoloComplemento"))
	{
		if (!IsEOF())
			sResult = m_sTitoloComplemento;

		CloseRecordset("CFrasiRisultatoSet::GetTitoloComplemento");
	}

	return sResult;
}
BOOL CFrasiRisultatoSet::SetTitoloComplemento(CString sTitolo)
{
	BOOL bResult = FALSE;

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::SetTitoloComplemento"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFrasiRisultatoSet::SetTitoloComplemento"))
			{
				m_sTitoloComplemento = sTitolo;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetTitoloComplemento");
			}
		}
		else
		{
			if (AddNewRecordset("CFrasiRisultatoSet::SetTitoloComplemento"))
			{
				m_sTitoloComplemento = sTitolo;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetTitoloComplemento");
			}
		}
		CloseRecordset("CFrasiRisultatoSet::SetTitoloComplemento");
	}

	return bResult;
}

CString CFrasiRisultatoSet::GetPositivoSingolare()
{
	CString sResult = "";

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);
	//

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::GetPositivoSingolare"))
	{
		if (!IsEOF())
			sResult = m_sPositivoSingolare;

		CloseRecordset("CFrasiRisultatoSet::GetPositivoSingolare");
	}

	return sResult;
}
BOOL CFrasiRisultatoSet::SetPositivoSingolare(CString sPosSing)
{
	BOOL bResult = FALSE;

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::SetPositivoSingolare"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFrasiRisultatoSet::SetPositivoSingolare"))
			{
				m_sPositivoSingolare = sPosSing;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetPositivoSingolare");
			}
		}
		else
		{
			if (AddNewRecordset("CFrasiRisultatoSet::SetPositivoSingolare"))
			{
				m_sPositivoSingolare = sPosSing;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetPositivoSingolare");
			}
		}
		CloseRecordset("CFrasiRisultatoSet::SetPositivoSingolare");
	}

	return bResult;
}

CString CFrasiRisultatoSet::GetPositivoPlurale()
{
	CString sResult = "";

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);
	//

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::GetPositivoPlurale"))
	{
		if (!IsEOF())
			sResult = m_sPositivoPlurale;

		CloseRecordset("CFrasiRisultatoSet::GetPositivoPlurale");
	}

	return sResult;
}
BOOL CFrasiRisultatoSet::SetPositivoPlurale(CString sPosPlur)
{
	BOOL bResult = FALSE;

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::SetPositivoPlurale"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFrasiRisultatoSet::SetPositivoPlurale"))
			{
				m_sPositivoPlurale = sPosPlur;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetPositivoPlurale");
			}
		}
		else
		{
			if (AddNewRecordset("CFrasiRisultatoSet::SetPositivoPlurale"))
			{
				m_sPositivoPlurale = sPosPlur;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetPositivoPlurale");
			}
		}
		CloseRecordset("CFrasiRisultatoSet::SetPositivoPlurale");
	}

	return bResult;
}

CString CFrasiRisultatoSet::GetPositivoVariante()
{
	CString sResult = "";

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);
	//

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::GetPositivoVariante"))
	{
		if (!IsEOF())
			sResult = m_sPositivoVariante;

		CloseRecordset("CFrasiRisultatoSet::GetPositivoVariante");
	}

	return sResult;
}
BOOL CFrasiRisultatoSet::SetPositivoVariante(CString sPosVari)
{
	BOOL bResult = FALSE;

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::SetPositivoVariante"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFrasiRisultatoSet::SetPositivoVariante"))
			{
				m_sPositivoVariante = sPosVari;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetPositivoVariante");
			}
		}
		else
		{
			if (AddNewRecordset("CFrasiRisultatoSet::SetPositivoVariante"))
			{
				m_sPositivoVariante = sPosVari;
				//m_lIDPatogenicita = lIDPatogenicita;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetPositivoVariante");
			}
		}
		CloseRecordset("CFrasiRisultatoSet::SetPositivoVariante");
	}

	return bResult;
}

CString CFrasiRisultatoSet::GetNegativoSingolare()
{	
	CString sResult = "";

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);
	//

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::GetNegativoSingolare"))
	{
		if (!IsEOF())
			sResult = m_sNegativoSingolare;

		CloseRecordset("CFrasiRisultatoSet::GetNegativoSingolare");
	}

	return sResult;
}
BOOL CFrasiRisultatoSet::SetNegativoSingolare(CString sNegSing)
{
	BOOL bResult = FALSE;
	
	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::SetNegativoSingolare"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFrasiRisultatoSet::SetNegativoSingolare"))
			{
				m_sNegativoSingolare = sNegSing;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetNegativoSingolare");
			}
		}
		else
		{
			if (AddNewRecordset("CFrasiRisultatoSet::SetNegativoSingolare"))
			{
				m_sNegativoSingolare = sNegSing;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetNegativoSingolare");
			}
		}
		CloseRecordset("CFrasiRisultatoSet::SetNegativoSingolare");
	}

	return bResult;
}

CString CFrasiRisultatoSet::GetNegativoNegativo()
{
	CString sResult = "";

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);
	//

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::GetNegativoNegativo"))
	{
		if (!IsEOF())
			sResult = m_sNegativoNegativo;

		CloseRecordset("CFrasiRisultatoSet::GetNegativoNegativo");
	}

	return sResult;
}
BOOL CFrasiRisultatoSet::SetNegativoNegativo(CString sNegNeg)
{
	BOOL bResult = FALSE;

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = 0");
	SetOpenFilter(sFilter);

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::SetNegativoNegativo"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFrasiRisultatoSet::SetNegativoNegativo"))
			{
				m_sNegativoNegativo = sNegNeg;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetNegativoNegativo");
			}
		}
		else
		{
			if (AddNewRecordset("CFrasiRisultatoSet::SetNegativoNegativo"))
			{
				m_sNegativoNegativo = sNegNeg;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetNegativoNegativo");
			}
		}
		CloseRecordset("CFrasiRisultatoSet::SetNegativoNegativo");
	}

	return bResult;
}

CString CFrasiRisultatoSet::GetComplementoSingolare(long lIDTipoVariante)
{
	CString sResult = "";

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = %li", lIDTipoVariante);
	SetOpenFilter(sFilter);
	//

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::GetComplementoSingolare"))
	{
		if (!IsEOF())
			sResult = m_sComplementoSingolare;

		CloseRecordset("CFrasiRisultatoSet::GetComplementoSingolare");
	}

	return sResult;
}
BOOL CFrasiRisultatoSet::SetComplementoSingolare(long lIDTipoVariante, CString sComSing)
{
	BOOL bResult = FALSE;

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = %li", lIDTipoVariante);
	SetOpenFilter(sFilter);

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::SetComplementoSingolare"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFrasiRisultatoSet::SetComplementoSingolare"))
			{
				m_sComplementoSingolare = sComSing;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetComplementoSingolare");
			}
		}
		else
		{
			if (AddNewRecordset("CFrasiRisultatoSet::SetComplementoSingolare"))
			{
				m_sComplementoSingolare = sComSing;
				m_lIDTipoVariante = lIDTipoVariante;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetComplementoSingolare");
			}
		}
		CloseRecordset("CFrasiRisultatoSet::SetComplementoSingolare");
	}

	return bResult;
}

CString CFrasiRisultatoSet::GetComplementoPlurale(long lIDTipoVariante)
{
	CString sResult = "";

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = %li", lIDTipoVariante);
	SetOpenFilter(sFilter);
	//

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::GetComplementoPlurale"))
	{
		if (!IsEOF())
			sResult = m_sComplementoPlurale;

		CloseRecordset("CFrasiRisultatoSet::GetComplementoPlurale");
	}

	return sResult;
}
BOOL CFrasiRisultatoSet::SetComplementoPlurale(long lIDTipoVariante, CString sComPlur)
{
	BOOL bResult = FALSE;

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = %li", lIDTipoVariante);
	SetOpenFilter(sFilter);

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::SetComplementoPlurale"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFrasiRisultatoSet::SetComplementoPlurale"))
			{
				m_sComplementoPlurale = sComPlur;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetComplementoPlurale");
			}
		}
		else
		{
			if (AddNewRecordset("CFrasiRisultatoSet::SetComplementoPlurale"))
			{
				m_sComplementoPlurale = sComPlur;
				m_lIDTipoVariante = lIDTipoVariante;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetComplementoPlurale");
			}
		}
		CloseRecordset("CFrasiRisultatoSet::SetComplementoPlurale");
	}

	return bResult;
}

CString CFrasiRisultatoSet::GetComplementoVariante(long lIDTipoVariante)
{
	CString sResult = "";

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = %li", lIDTipoVariante);
	SetOpenFilter(sFilter);
	//

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::GetComplementoVariante"))
	{
		if (!IsEOF())
			sResult = m_sComplementoVariante;

		CloseRecordset("CFrasiRisultatoSet::GetComplementoVariante");
	}

	return sResult;
}
BOOL CFrasiRisultatoSet::SetComplementoVariante(long lIDTipoVariante, CString sComVari)
{
	BOOL bResult = FALSE;

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = %li", lIDTipoVariante);
	SetOpenFilter(sFilter);

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::SetComplementoVariante"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFrasiRisultatoSet::SetComplementoVariante"))
			{
				m_sComplementoVariante = sComVari;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetComplementoVariante");
			}
		}
		else
		{
			if (AddNewRecordset("CFrasiRisultatoSet::SetComplementoVariante"))
			{
				m_sComplementoVariante = sComVari;
				m_lIDTipoVariante = lIDTipoVariante;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetComplementoVariante");
			}
		}
		CloseRecordset("CFrasiRisultatoSet::SetComplementoVariante");
	}

	return bResult;
}

CString CFrasiRisultatoSet::GetComplementoNegativo(long lIDTipoVariante)
{
	CString sResult = "";

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = %li", lIDTipoVariante);
	SetOpenFilter(sFilter);
	//

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::GetComplementoNegativo"))
	{
		if (!IsEOF())
			sResult = m_sComplementoNegativo;

		CloseRecordset("CFrasiRisultatoSet::GetComplementoNegativo");
	}

	return sResult;
}
BOOL CFrasiRisultatoSet::SetComplementoNegativo(long lIDTipoVariante, CString sComNeg)
{
	BOOL bResult = FALSE;

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND IDTipoVariante = %li", lIDTipoVariante);
	SetOpenFilter(sFilter);

	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::SetComplementoNegativo"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFrasiRisultatoSet::SetComplementoNegativo"))
			{
				m_sComplementoNegativo = sComNeg;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetComplementoNegativo");
			}
		}
		else
		{
			if (AddNewRecordset("CFrasiRisultatoSet::SetComplementoNegativo"))
			{
				m_sComplementoNegativo = sComNeg;
				m_lIDTipoVariante = lIDTipoVariante;
				m_bEliminato = FALSE;

				bResult = UpdateRecordset("CFrasiRisultatoSet::SetComplementoNegativo");
			}
		}
		CloseRecordset("CFrasiRisultatoSet::SetComplementoNegativo");
	}

	return bResult;
}

BOOL CFrasiRisultatoSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFrasiRisultatoSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CFrasiRisultatoSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CFrasiRisultatoSet::SetEliminato");
	}

	return bReturn;
}
void CFrasiRisultatoSet::GetIDList(CList<long>& listID)
{
	SetSortRecord("ID");
	if (OpenRecordset("CFrasiRisultatoSet::GetEliminato"))
	{
		while (!IsEOF())
		{
			listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CFrasiRisultatoSet::GetEliminato");
	}
}