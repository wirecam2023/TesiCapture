#include "stdafx.h"
#include "Endox.h"
#include "ElemReportSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CElemReportSet, CBaseSet)

CElemReportSet::CElemReportSet()
	: CBaseSet(&m_nContatore, "CONTATORE")
{
	m_nContatore  = 0;
	m_lIDHeaderFooter = 0;
	m_strType     = "";
	m_strValue    = "";
	m_nLeft       = 0;
	m_nRight      = 0;
	m_nTop        = 0;
	m_nBottom     = 0;
	m_nCheck      = 0;
	m_nColor      = 0;
	m_nParam      = 0;
	m_strFontName = "";
	m_nFontFamily = 0;
	m_nFontHeight = 0;
	m_nFontWeight = 0;
	m_nFontUnder  = 0;
	m_nFontItalic = 0;
	m_nAlignment  = 0;
	m_nRotation   = 0;
	m_bEliminato  = FALSE;

	m_nFields = 20;
	SetBaseFilter("");
}

void CElemReportSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "CONTATORE",    m_nContatore);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDHeaderFooter", m_lIDHeaderFooter);
		RFX_Text(pFX, "FIELD_TYPE",   m_strType);
		RFX_Text(pFX, "FIELD_VALUE",  m_strValue);
		RFX_Long(pFX, "DIM_LEFT",     m_nLeft);
		RFX_Long(pFX, "DIM_RIGHT",    m_nRight);
		RFX_Long(pFX, "DIM_TOP",      m_nTop);
		RFX_Long(pFX, "DIM_BOTTOM",   m_nBottom);
		RFX_Long(pFX, "OPT_CHECK",    m_nCheck);
		RFX_Long(pFX, "OPT_COLOR",    m_nColor);
		RFX_Long(pFX, "OPT_PARAM",    m_nParam);
		RFX_Text(pFX, "FONT_NAME",    m_strFontName);
		RFX_Long(pFX, "FONT_FAMILY",  m_nFontFamily);
		RFX_Long(pFX, "FONT_HEIGHT",  m_nFontHeight);
		RFX_Long(pFX, "FONT_WEIGHT",  m_nFontWeight);
		RFX_Long(pFX, "FONT_UNDER",   m_nFontUnder);
		RFX_Long(pFX, "FONT_ITALIC",  m_nFontItalic);
		RFX_Int (pFX, "Alignment",	  m_nAlignment);
		RFX_Int (pFX, "Rotation",	  m_nRotation);
		RFX_Bool(pFX, "Eliminato",    m_bEliminato);
	}
}

CString CElemReportSet::GetDefaultSQL()
{
	return "EELEMENTOREPORT";
}

void CElemReportSet::SetEmpty()
{
	m_nContatore  = 0;
	m_lIDHeaderFooter = 0;
	// m_strBelong   = "";
	m_strType     = "";
	m_strValue    = "";
	m_nLeft       = 0;
	m_nRight      = 0;
	m_nTop        = 0;
	m_nBottom     = 0;
	m_nCheck      = 0;
	m_nColor      = 0;
	m_nParam      = 0;
	m_strFontName = "";
	m_nFontFamily = 0;
	m_nFontHeight = 0;
	m_nFontWeight = 0;
	m_nFontUnder  = 0;
	m_nFontItalic = 0;
	m_nAlignment  = 0;
	m_nRotation   = 0;
	m_bEliminato  = FALSE;
}

CBaseSet* CElemReportSet::CreateNew()
{
	return (CBaseSet*)new CElemReportSet;
}

void CElemReportSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CElemReportSet* pElemReportSet = (CElemReportSet*)pOriginalSet;

	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_lIDHeaderFooter) || bCopyAll)
		m_lIDHeaderFooter   = pElemReportSet->m_lIDHeaderFooter;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_strType) || bCopyAll)
		m_strType     = pElemReportSet->m_strType;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_strValue) || bCopyAll)
		m_strValue    = pElemReportSet->m_strValue;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nLeft) || bCopyAll)
		m_nLeft       = pElemReportSet->m_nLeft;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nRight) || bCopyAll)
		m_nRight      = pElemReportSet->m_nRight;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nTop) || bCopyAll)
		m_nTop        = pElemReportSet->m_nTop;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nBottom) || bCopyAll)
		m_nBottom     = pElemReportSet->m_nBottom;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nCheck) || bCopyAll)
		m_nCheck      = pElemReportSet->m_nCheck;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nColor) || bCopyAll)
		m_nColor      = pElemReportSet->m_nColor;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nParam) || bCopyAll)
		m_nParam      = pElemReportSet->m_nParam;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_strFontName) || bCopyAll)
		m_strFontName = pElemReportSet->m_strFontName;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nFontFamily) || bCopyAll)
		m_nFontFamily = pElemReportSet->m_nFontFamily;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nFontHeight) || bCopyAll)
		m_nFontHeight = pElemReportSet->m_nFontHeight;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nFontWeight) || bCopyAll)
		m_nFontWeight = pElemReportSet->m_nFontWeight;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nFontUnder) || bCopyAll)
		m_nFontUnder  = pElemReportSet->m_nFontUnder;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nFontItalic) || bCopyAll)
		m_nFontItalic = pElemReportSet->m_nFontItalic;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nAlignment) || bCopyAll)
		m_nAlignment = pElemReportSet->m_nAlignment;
	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_nRotation) || bCopyAll)
		m_nRotation = pElemReportSet->m_nRotation;

	if (!pElemReportSet->IsOpen() || pElemReportSet->IsFieldDirty(&pElemReportSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pElemReportSet->m_bEliminato;
}

void CElemReportSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CElemReportSet* pOV = (CElemReportSet*)pOldValues;
	CElemReportSet* pNV = (CElemReportSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDHeaderFooter", pOV, &pOV->m_lIDHeaderFooter, pNV, &pNV->m_lIDHeaderFooter);
	sp.Execute("FIELD_TYPE", pOV, &pOV->m_strType, pNV, &pNV->m_strType);
	sp.Execute("FIELD_VALUE", pOV, &pOV->m_strValue, pNV, &pNV->m_strValue);
	sp.Execute("DIM_LEFT", pOV, &pOV->m_nLeft, pNV, &pNV->m_nLeft);
	sp.Execute("DIM_RIGHT", pOV, &pOV->m_nRight, pNV, &pNV->m_nRight);
	sp.Execute("DIM_TOP", pOV, &pOV->m_nTop, pNV, &pNV->m_nTop);
	sp.Execute("DIM_BOTTOM", pOV, &pOV->m_nBottom, pNV, &pNV->m_nBottom);
	sp.Execute("OPT_CHECK", pOV, &pOV->m_nCheck, pNV, &pNV->m_nCheck);
	sp.Execute("OPT_COLOR", pOV, &pOV->m_nColor, pNV, &pNV->m_nColor);
	sp.Execute("OPT_PARAM", pOV, &pOV->m_nParam, pNV, &pNV->m_nParam);
	sp.Execute("FONT_NAME", pOV, &pOV->m_strFontName, pNV, &pNV->m_strFontName);
	sp.Execute("FONT_FAMILY", pOV, &pOV->m_nFontFamily, pNV, &pNV->m_nFontFamily);
	sp.Execute("FONT_HEIGHT", pOV, &pOV->m_nFontHeight, pNV, &pNV->m_nFontHeight);
	sp.Execute("FONT_WEIGHT", pOV, &pOV->m_nFontWeight, pNV, &pNV->m_nFontWeight);
	sp.Execute("FONT_UNDER", pOV, &pOV->m_nFontUnder, pNV, &pNV->m_nFontUnder);
	sp.Execute("FONT_ITALIC", pOV, &pOV->m_nFontItalic, pNV, &pNV->m_nFontItalic);
	sp.Execute("Alignment", pOV, &pOV->m_nAlignment, pNV, &pNV->m_nAlignment);
	sp.Execute("Rotation", pOV, &pOV->m_nRotation, pNV, &pNV->m_nRotation);
	
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CElemReportSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CElemReportSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CElemReportSet::DeleteRecordset");
	}
	return bReturn;
}

CString CElemReportSet::SetBaseFilter(const CString &strFilter)
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

long CElemReportSet::AddRow(long lIDHeaderFooter, CString strType, CString strValue, long nLeft, long nRight, long nTop, long nBottom, long nCheck, long nColor, long nParam, CString strFontName, long nFontFamily, long nFontHeight, long nFontWeight, long nFontUnder, long nFontItalic, int nAlignment, int nRotation)
{
	long lReturn = 0;

	SetOpenFilter("CONTATORE=0");
	if (OpenRecordset("CElemReportSet::AddRow"))
	{
		if (AddNewRecordset("CElemReportSet::AddRow"))
		{
			m_lIDHeaderFooter = lIDHeaderFooter;
			m_strType = strType;
			m_strValue = strValue;
			m_nLeft = nLeft;
			m_nRight = nRight;
			m_nTop = nTop;
			m_nBottom = nBottom;
			m_nCheck = nCheck;
			m_nColor = nColor;
			m_nParam = nParam;
			m_strFontName = strFontName;
			m_nFontFamily = nFontFamily;
			m_nFontHeight = nFontHeight;
			m_nFontWeight = nFontWeight;
			m_nFontUnder = nFontUnder;
			m_nFontItalic = nFontItalic;
			m_nAlignment = nAlignment;
			m_nRotation = nRotation;

			if (UpdateRecordset("CElemReportSet::AddRow"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CElemReportSet::AddRow");
	}

	return lReturn;
}

void CElemReportSet::EdtRow(long lContatore, CString sValue)
{
	if (lContatore > 0)
	{
		CString sFilter;
		sFilter.Format("CONTATORE=%li", lContatore);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CElemReportSet::EdtRow"))
		{
			if (!IsEOF())
			{
				if (EditRecordset("CElemReportSet::EdtRow"))
				{
					m_strValue = sValue;
					UpdateRecordset("CElemReportSet::EdtRow");
				}
			}

			CloseRecordset("CElemReportSet::EdtRow");
		}
	}
}
