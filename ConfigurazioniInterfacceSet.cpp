#include "stdafx.h"
#include "Endox.h"
#include "ConfigurazioniInterfacceSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CConfigurazioniInterfacceSet, CBaseSet)

CConfigurazioniInterfacceSet::CConfigurazioniInterfacceSet()
	: CBaseSet(NULL, "NOLOG") // non lascio traccia delle modifiche //
{
	SetBaseFilter("");
	SetEmpty();
	SetSortRecord("VOCE");

	m_nFields = 3;
}

void CConfigurazioniInterfacceSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "Voce", m_sVoce, 255);
	RFX_Text(pFX, "Valore", m_sValore, 255);
	RFX_Long(pFX, "UO", m_lUO);
}

CString CConfigurazioniInterfacceSet::GetDefaultSQL()
{
	return "CONFIGURAZIONIINTERFACCE";
}

void CConfigurazioniInterfacceSet::SetEmpty()
{
	m_sVoce = "";
	m_sValore = "";
	m_lUO = 0;
}

void CConfigurazioniInterfacceSet::GetBoolValue(const CString& strVoce, BOOL& bValore)
{
	SetOpenFilter("Voce='" + strVoce + "'");
	SetSortRecord("Voce");
	if (OpenRecordset("CConfigurazioniInterfacceSet::GetBoolValue"))
	{
		if (IsEOF())
			SetBoolValue(strVoce, bValore);
		else
			bValore = (atol(m_sValore) == 1 ? TRUE : FALSE);

		CloseRecordset("CConfigurazioniInterfacceSet::GetBoolValue");
	}
}

void CConfigurazioniInterfacceSet::GetLongValue(const CString& strVoce, long& lValore)
{
	SetOpenFilter("Voce='" + strVoce + "'");
	SetSortRecord("Voce");
	if (OpenRecordset("CConfigurazioniInterfacceSet::GetLongValue"))
	{
		if (IsEOF())
			SetLongValue(strVoce, lValore);
		else
			lValore = atol(m_sValore);

		CloseRecordset("CConfigurazioniInterfacceSet::GetLongValue");
	}
}

void CConfigurazioniInterfacceSet::GetStringValue(const CString& strVoce, CString& strValore)
{
	SetOpenFilter("Voce='" + strVoce + "'");
	SetSortRecord("Voce");
	if (OpenRecordset("CConfigurazioniInterfacceSet::GetStringValue"))
	{
		if (IsEOF())
			SetStringValue(strVoce, strValore);
		else
			strValore = m_sValore;

		CloseRecordset("CConfigurazioniInterfacceSet::GetStringValue");
	}
}

void CConfigurazioniInterfacceSet::SetBoolValue(const CString& strVoce, const BOOL& bValore)
{
	SetOpenFilter("Voce='" + strVoce + "'");
	SetSortRecord("Voce");
	if (OpenRecordset("CConfigurazioniInterfacceSet::SetBoolValue"))
	{
		if (IsEOF())
		{
			if (AddNewRecordset("CConfigurazioniInterfacceSet::SetBoolValue"))
			{
				m_sVoce = strVoce;
				m_sValore = (bValore == TRUE ? "1" : "0");
				UpdateRecordset("CConfigurazioniInterfacceSet::SetBoolValue");
			}
		}
		else
		{
			if (EditRecordset("CConfigurazioniInterfacceSet::SetBoolValue"))
			{
				m_sValore = (bValore == TRUE ? "1" : "0");
				UpdateRecordset("CConfigurazioniInterfacceSet::SetBoolValue");
			}
		}

		CloseRecordset("CConfigurazioniInterfacceSet::SetBoolValue");
	}
}

void CConfigurazioniInterfacceSet::SetLongValue(const CString& strVoce, const long& lValore)
{
	SetOpenFilter("Voce='" + strVoce + "'");
	SetSortRecord("Voce");
	if (OpenRecordset("CConfigurazioniInterfacceSet::SetLongValue"))
	{
		if (IsEOF())
		{
			if (AddNewRecordset("CConfigurazioniInterfacceSet::SetLongValue"))
			{
				m_sVoce = strVoce;
				m_sValore.Format("%li", lValore);
				UpdateRecordset("CConfigurazioniInterfacceSet::SetLongValue");
			}
		}
		else
		{
			if (EditRecordset("CConfigurazioniInterfacceSet::SetLongValue"))
			{
				m_sValore.Format("%li", lValore);
				UpdateRecordset("CConfigurazioniInterfacceSet::SetLongValue");
			}
		}

		CloseRecordset("CConfigurazioniInterfacceSet::SetLongValue");
	}
}

void CConfigurazioniInterfacceSet::SetStringValue(const CString& strVoce, const CString& strValore)
{
	SetOpenFilter("Voce='" + strVoce + "'");
	SetSortRecord("Voce");
	if (OpenRecordset("CConfigurazioniInterfacceSet::SetStringValue"))
	{
		if (IsEOF())
		{
			if (AddNewRecordset("CConfigurazioniInterfacceSet::SetStringValue"))
			{
				m_sVoce = strVoce;
				m_sValore = strValore;
				UpdateRecordset("CConfigurazioniInterfacceSet::SetStringValue");
			}
		}
		else
		{
			if (EditRecordset("CConfigurazioniInterfacceSet::SetStringValue"))
			{
				m_sValore = strValore;
				UpdateRecordset("CConfigurazioniInterfacceSet::SetStringValue");
			}
		}

		CloseRecordset("CConfigurazioniInterfacceSet::SetStringValue");
	}

}

CString CConfigurazioniInterfacceSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO;
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CConfigurazioniInterfacceSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
