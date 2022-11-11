#include "stdafx.h"
#include "Endox.h"
#include "EndoGridCLParameterSet.h"
#include "EndoGridItems.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridCLParameterSet, CBaseSet)

CEndoGridCLParameterSet::CEndoGridCLParameterSet(BOOL bVersionJoin, CDatabase* pDatabase)
: CBaseSet((bVersionJoin ? NULL : &m_lId), (bVersionJoin ? "VIEW" : "ID"))
{
	SetBaseFilter("");
	SetEmpty();
	
	m_nFields = 18;

	m_bVersionJoin = bVersionJoin;
}

void CEndoGridCLParameterSet::SetEmpty()
{
	m_lId = 0;
	m_lIdEtichetta = 0;
	m_sParameterName = "";
	m_sDescription = "";
	m_lType = 0;
	m_lOrder = 0;
	m_bDefaultBool = FALSE;
	m_lDefaultInt = 0;
	m_fDefaultFloat = 0.0;
	m_sDefaultString = "";
	m_lParentID = 0;
	m_bExpanded = FALSE;
	m_bRequired = FALSE;
	m_bChangeColor = FALSE;
	m_sNotes = "";
	m_bBold = FALSE;
	m_lFontSize = 10;
	m_bEliminato = FALSE;
}

void CEndoGridCLParameterSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, _T("ID"), m_lId);

	if (m_nFields > 1)
	{
		RFX_Long(pFX, _T("IDETICHETTA_GRIDCL"), m_lIdEtichetta);
		RFX_Text(pFX, _T("NOMEPARAMETRO"), m_sParameterName);
		RFX_Text(pFX, _T("DESCRIZIONE"), m_sDescription);
		RFX_Long(pFX, _T("TIPO"), m_lType);
		RFX_Long(pFX, _T("ORDINE"), m_lOrder);
		RFX_Bool(pFX, _T("DEFAULT_BOOL"), m_bDefaultBool);
		RFX_Long(pFX, _T("DEFAULT_INT"), m_lDefaultInt);
		RFX_Single(pFX, _T("DEFAULT_FLOAT"), m_fDefaultFloat);
		RFX_Text(pFX, _T("DEFAULT_STRINGA"), m_sDefaultString, 255);
		RFX_Long(pFX, _T("IDPADRE"), m_lParentID);
		RFX_Bool(pFX, _T("ESPANSO"), m_bExpanded);
		RFX_Bool(pFX, _T("OBBLIGATORIO"), m_bRequired);
		RFX_Bool(pFX, _T("COLORE"), m_bChangeColor);
		RFX_Text(pFX, _T("NOTE"), m_sNotes);
		RFX_Bool(pFX, _T("BOLD"), m_bBold);
		RFX_Long(pFX, _T("FONTSIZE"), m_lFontSize);
		RFX_Bool(pFX, _T("ELIMINATO"), m_bEliminato);
	}
}

CString CEndoGridCLParameterSet::GetDefaultSQL()
{
	if (m_bVersionJoin)
	{
		CString strReturn;
		strReturn += "SELECT GRIDCL_PARAM.ID,IDETICHETTA_GRIDCL,NOMEPARAMETRO,DESCRIZIONE,TIPO,ORDINE,DEFAULT_BOOL,DEFAULT_INT,DEFAULT_FLOAT,DEFAULT_STRINGA,IDPADRE,ESPANSO,OBBLIGATORIO,COLORE,NOTE,BOLD,FONTSIZE,GRIDCL_PARAM.ELIMINATO";
		strReturn += "	FROM GRIDCL_PARAM ";
		strReturn += "	 INNER JOIN GRIDCL_PARAM_VERS ON GRIDCL_PARAM.ID = GRIDCL_PARAM_VERS.IDPARAMETRO";
		
		return strReturn;
	}
	else
		return _T("GRIDCL_PARAM");
}

CEndoGridCLParameterSet::FIELD_TYPE CEndoGridCLParameterSet::GetFieldType()
{
	FIELD_TYPE type = type_double;

	switch (m_lType)
	{
	case 0:
		type = type_double;
		break;

	case 1:
		type = type_bool;
		break;

	case 2:
		type = type_integer;
		break;

	case 3:
		type = type_combo;
		break;

	case 4:
		type = type_date;
		break;

	case 5:
		type = type_string;
		break;

	case 6:
		type = type_combo_multi;
		break;

	case 7:
		type = type_notes;
		break;

	case 8:
		type = type_combo_fixed;
		break;

	case 9:
		type = type_date_free;
		break;	

	case 10:
		type = type_check;
		break;

	default:
		ASSERT(FALSE);
		break;
	}

	return type;
}

CXTPPropertyGridItem* CEndoGridCLParameterSet::CreateItem()
{
	CString strName;
#ifdef _DEBUG
	strName.Format("%s %li", m_sParameterName, m_lId);	
#else
	strName = m_sParameterName;
#endif

	int lines = strName.Replace("\\n","<LineBreak/>");
	CString start;
	start.Format("<TextBlock VerticalAlignment='Center' FontSize='%lipt'>", m_lFontSize);
	CString end = "</TextBlock>";

	if (m_bBold)
	{
		start += "<Bold>";
		end = "</Bold>" + end;
	}

	strName = start + strName + end;

	CXTPPropertyGridItem* pItem = NULL;
	switch (GetFieldType())
	{
	case CEndoGridCLParameterSet::type_double:
		pItem = new CEndoGridItemDouble(strName, 0, 0, "%.02f");
		break;

	case CEndoGridCLParameterSet::type_check:
		pItem = new CEndoGridItemCheck(strName);
		break;

	case CEndoGridCLParameterSet::type_bool:
		pItem = new CEndoGridItemBool(strName);
		break;

	case CEndoGridCLParameterSet::type_integer:
		pItem = new CEndoGridItemNumber(strName);
		break;

	case CEndoGridCLParameterSet::type_combo:
		pItem = new CEndoGridItemEdit(m_lId, strName, FALSE, FALSE);
		break;

	case CEndoGridCLParameterSet::type_date:
		pItem = new CEndoGridItemDate(strName);
		pItem->SetValue(((CEndoGridItemDate*)pItem)->GetLiteral());
		break;

	case CEndoGridCLParameterSet::type_string:
		pItem = new CEndoGridItemEdit(strName);
		break;

	case CEndoGridCLParameterSet::type_combo_multi:
		pItem = new CEndoGridItemEdit(m_lId, strName, TRUE, FALSE);
		break;

	case CEndoGridCLParameterSet::type_notes:
		pItem = new CEndoGridItemNotes(strName);
		break;

	case CEndoGridCLParameterSet::type_combo_fixed:
		pItem = new CEndoGridItemEdit(m_lId, strName, FALSE, TRUE);
		break;

	case CEndoGridCLParameterSet::type_date_free:
		pItem = new CEndoGridItemEditDate(strName);
		break;

	default:
		ASSERT(FALSE);
		break;
	}

	pItem->SetDescription(m_sDescription);
	pItem->SetMultiLinesCount(lines + 1);
	pItem->SetHeight(m_lFontSize * (lines + (m_lFontSize/4)));

	return pItem;
}

BOOL CEndoGridCLParameterSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEndoGridCLParameterSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEndoGridCLParameterSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEndoGridCLParameterSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{	
		strNewFilter = "GRIDCL_PARAM.ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND GRIDCL_PARAM.ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CEndoGridCLParameterSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);	
}

void CEndoGridCLParameterSet::CancelUpdateRecordset(const CString &strCommento)
{
	CBaseSet::CancelUpdate();
}

CBaseSet* CEndoGridCLParameterSet::CreateNew()
{
	return (CBaseSet*)new CEndoGridCLParameterSet;
}

void CEndoGridCLParameterSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEndoGridCLParameterSet* pSet = (CEndoGridCLParameterSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdEtichetta) || bCopyAll)
		m_lIdEtichetta = pSet->m_lIdEtichetta;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sParameterName) || bCopyAll)
		m_sParameterName = pSet->m_sParameterName;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescription) || bCopyAll)
		m_sDescription = pSet->m_sDescription;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lType) || bCopyAll)
		m_lType = pSet->m_lType;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOrder) || bCopyAll)
		m_lOrder = pSet->m_lOrder;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bDefaultBool) || bCopyAll)
		m_bDefaultBool = pSet->m_bDefaultBool;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lDefaultInt) || bCopyAll)
		m_lDefaultInt = pSet->m_lDefaultInt;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fDefaultFloat) || bCopyAll)
		m_fDefaultFloat = pSet->m_fDefaultFloat;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDefaultString) || bCopyAll)
		m_sDefaultString = pSet->m_sDefaultString;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lParentID) || bCopyAll)
		m_lParentID = pSet->m_lParentID;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bExpanded) || bCopyAll)
		m_bExpanded = pSet->m_bExpanded;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bRequired) || bCopyAll)
		m_bRequired = pSet->m_bRequired;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bChangeColor) || bCopyAll)
		m_bChangeColor = pSet->m_bChangeColor;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNotes) || bCopyAll)
		m_sNotes = pSet->m_sNotes;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bBold) || bCopyAll)
		m_bBold = pSet->m_bBold;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lFontSize) || bCopyAll)
		m_lFontSize = pSet->m_lFontSize;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEndoGridCLParameterSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEndoGridCLParameterSet* pOV = (CEndoGridCLParameterSet*)pOldValues;
	CEndoGridCLParameterSet* pNV = (CEndoGridCLParameterSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDETICHETTA_GRIDCL", pOV, &pOV->m_lIdEtichetta, pNV, &pNV->m_lIdEtichetta);
	sp.Execute("NOMEPARAMETRO", pOV, &pOV->m_sParameterName, pNV, &pNV->m_sParameterName);
	sp.Execute("DESCRIZIONE", pOV, &pOV->m_sDescription, pNV, &pNV->m_sDescription);
	sp.Execute("TIPO", pOV, &pOV->m_lType, pNV, &pNV->m_lType);
	sp.Execute("ORDINE", pOV, &pOV->m_lOrder, pNV, &pNV->m_lOrder);
	sp.Execute("DEFAULT_BOOL", pOV, &pOV->m_bDefaultBool, pNV, &pNV->m_bDefaultBool);
	sp.Execute("DEFAULT_INT", pOV, &pOV->m_lDefaultInt, pNV, &pNV->m_lDefaultInt);
	sp.Execute("DEFAULT_FLOAT", pOV, &pOV->m_fDefaultFloat, pNV, &pNV->m_fDefaultFloat);
	sp.Execute("DEFAULT_STRINGA", pOV, &pOV->m_sDefaultString, pNV, &pNV->m_sDefaultString);
	sp.Execute("IDPADRE", pOV, &pOV->m_lParentID, pNV, &pNV->m_lParentID);
	sp.Execute("ESPANSO", pOV, &pOV->m_bExpanded, pNV, &pNV->m_bExpanded);
	sp.Execute("OBBLIGATORIO", pOV, &pOV->m_bRequired, pNV, &pNV->m_bRequired);
	sp.Execute("COLORE", pOV, &pOV->m_bChangeColor, pNV, &pNV->m_bChangeColor);
	sp.Execute("NOTE", pOV, &pOV->m_bChangeColor, pNV, &pNV->m_bChangeColor);
	sp.Execute("BOLD", pOV, &pOV->m_bBold, pNV, &pNV->m_bBold);
	sp.Execute("FONTSIZE", pOV, &pOV->m_lFontSize, pNV, &pNV->m_lFontSize);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

long CEndoGridCLParameterSet::Insert(CString strParameterName, CString strDescription, CString strNotes, long lIdEtichetta, int iFieldType, long lSort, long lParentID, BOOL bBold, long lFontSize)
{
	long lReturn = 0;

	if (OpenRecordset("CEndoGridCLParameterSet::Insert"))
	{

		if (AddNewRecordset("CEndoGridCLParameterSet::Insert"))
		{
			m_lIdEtichetta = lIdEtichetta;
			m_sParameterName = strParameterName;
			m_sDescription = strDescription;
			m_sNotes = strNotes;
			m_lType = iFieldType;
			m_lOrder = lSort;
			m_lParentID = lParentID;
			m_bBold = bBold;
			m_lFontSize = lFontSize;

			if (UpdateRecordset("CEndoGridCLParameterSet::Insert"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CEndoGridCLParameterSet::Insert");
	}

	return lReturn;
}

float CEndoGridCLParameterSet::GetDefaultFloatValue(long id)
{
	float fResult = 0.0;

	CString filter;
	filter.Format("ID=%li", id);
	SetOpenFilter(filter);
	if (OpenRecordset("CEndoGridCLParameterSet::GetDefaultFloatValue"))
	{

		if (!IsEOF())
			fResult = m_fDefaultFloat;

		CloseRecordset("CEndoGridCLParameterSet::GetDefaultFloatValue");
	}

	return fResult;
}

BOOL CEndoGridCLParameterSet::GetDefaultBoolValue(long id)
{
	BOOL bResult = FALSE;

	CString filter;
	filter.Format("ID=%li", id);
	SetOpenFilter(filter);
	if (OpenRecordset("CEndoGridCLParameterSet::GetDefaultBoolValue"))
	{

		if (!IsEOF())
			bResult = m_bDefaultBool;

		CloseRecordset("CEndoGridCLParameterSet::GetDefaultBoolValue");
	}

	return bResult;
}

long CEndoGridCLParameterSet::GetDefaultLongValue(long id)
{
	long lResult = 0;

	CString filter;
	filter.Format("ID=%li", id);
	SetOpenFilter(filter);
	if (OpenRecordset("CEndoGridCLParameterSet::GetDefaultLongValue"))
	{

		if (!IsEOF())
			lResult = m_lDefaultInt;

		CloseRecordset("CEndoGridCLParameterSet::GetDefaultLongValue");
	}

	return lResult;
}

CString CEndoGridCLParameterSet::GetDefaultValue(long id)
{
	CString sResult = "";

	CString filter;
	filter.Format("ID=%li", id);
	SetOpenFilter(filter);
	if (OpenRecordset("CEndoGridCLParameterSet::GetDefaultValue"))
	{

		if (!IsEOF())
			sResult = m_sDefaultString;

		CloseRecordset("CEndoGridCLParameterSet::GetDefaultValue");
	}

	return sResult;
}