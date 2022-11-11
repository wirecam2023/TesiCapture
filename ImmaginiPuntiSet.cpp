#include "stdafx.h"
#include "Endox.h"
#include "ImmaginiPuntiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CImmaginiPuntiSet, CBaseSet)

CImmaginiPuntiSet::CImmaginiPuntiSet()
	: CBaseSet(&m_lID, "ID")
{
	m_lID = 0;
	m_lIDImmagine = 0;
	m_lIDPunto = 0;
	m_bEliminato = FALSE;

	m_nFields = 4;
	SetBaseFilter("");
}

CString CImmaginiPuntiSet::GetDefaultSQL()
{
	return "ImmaginiPunti";
}

void CImmaginiPuntiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDImmagine", m_lIDImmagine);
		RFX_Long(pFX, "IDPunto", m_lIDPunto);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CImmaginiPuntiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDImmagine = 0;
	m_lIDPunto = 0;
	m_bEliminato = FALSE;
}

long CImmaginiPuntiSet::GetIDPunto(long lIDImmagine)
{
	long lReturn = 0;

	if (lIDImmagine > 0)
	{
		CString strFilter;
		strFilter.Format("IDImmagine=%li", lIDImmagine);

		SetOpenFilter(strFilter);
		if (OpenRecordset("CImmaginiPuntiSet::GetIDPunto") == TRUE)
		{
			if ((IsBOF() == FALSE) && (IsEOF() == FALSE))
				lReturn = m_lIDPunto;

			CloseRecordset("CImmaginiPuntiSet::GetIDPunto");
		}
	}

	return lReturn;
}

void CImmaginiPuntiSet::SetIDPunto(long lIDImmagine, long lIDPunto)
{
	if (lIDImmagine > 0)
	{
		if (lIDPunto > 0) // l'ID del punto è valido e quindi lo salvo //
		{
			CString strFilter;
			strFilter.Format("IDImmagine=%li", lIDImmagine);

			SetOpenFilter(strFilter);
			if (OpenRecordset("CImmaginiPuntiSet::SetIDPunto") == TRUE)
			{
				if ((IsBOF() == FALSE) && (IsEOF() == FALSE))
				{
					if (EditRecordset("CImmaginiPuntiSet::SetIDPunto") == TRUE)
					{
						m_lIDPunto = lIDPunto;

						UpdateRecordset("CImmaginiPuntiSet::SetIDPunto");
					}
				}
				else
				{
					if (AddNewRecordset("CImmaginiPuntiSet::SetIDPunto") == TRUE)
					{
						m_lIDImmagine = lIDImmagine;
						m_lIDPunto = lIDPunto;

						UpdateRecordset("CImmaginiPuntiSet::SetIDPunto");
					}
				}

				CloseRecordset("CImmaginiPuntiSet::SetIDPunto");
			}
		}
		else // l'ID del punto non è valido e quindi se trovo quell'immagine nella tabella la cancello //
		{
			CString strFilter;
			strFilter.Format("IDImmagine=%li", lIDImmagine);

			SetOpenFilter(strFilter);
			if (OpenRecordset("CImmaginiPuntiSet::SetIDPunto") == TRUE)
			{
				if ((IsBOF() == FALSE) && (IsEOF() == FALSE))
					DeleteRecordset("CImmaginiPuntiSet::SetIDPunto");

				CloseRecordset("CImmaginiPuntiSet::SetIDPunto");
			}
		}
	}
}

CBaseSet* CImmaginiPuntiSet::CreateNew()
{
	return (CBaseSet*)new CImmaginiPuntiSet;
}

void CImmaginiPuntiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CImmaginiPuntiSet* pImmaginiPuntiSet = (CImmaginiPuntiSet*)pOriginalSet;

	if (!pImmaginiPuntiSet->IsOpen() || pImmaginiPuntiSet->IsFieldDirty(&pImmaginiPuntiSet->m_lIDImmagine) || bCopyAll)
		m_lIDImmagine = pImmaginiPuntiSet->m_lIDImmagine;
	if (!pImmaginiPuntiSet->IsOpen() || pImmaginiPuntiSet->IsFieldDirty(&pImmaginiPuntiSet->m_lIDPunto) || bCopyAll)
		m_lIDPunto = pImmaginiPuntiSet->m_lIDPunto;
	if (!pImmaginiPuntiSet->IsOpen() || pImmaginiPuntiSet->IsFieldDirty(&pImmaginiPuntiSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pImmaginiPuntiSet->m_bEliminato;
}

void CImmaginiPuntiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CImmaginiPuntiSet* pOV = (CImmaginiPuntiSet*)pOldValues;
	CImmaginiPuntiSet* pNV = (CImmaginiPuntiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDImmagine", pOV, &pOV->m_lIDImmagine, pNV, &pNV->m_lIDImmagine);
	sp.Execute("IDPunto", pOV, &pOV->m_lIDPunto, pNV, &pNV->m_lIDPunto);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CImmaginiPuntiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CImmaginiPuntiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CImmaginiPuntiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CImmaginiPuntiSet::SetBaseFilter(const CString &strFilter)
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