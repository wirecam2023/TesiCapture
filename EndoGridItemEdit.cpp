#include "stdafx.h"
#include "Endox.h"
#include "EndoGridItemEdit.h"
//#include "EndoGridComboDlg.h"

#include "EndoGridComboDlg.h"
#include "EndoGridCLComboSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CEndoGridItemEdit::m_bCheckReadOnly = TRUE;

IMPLEMENT_DYNAMIC(CEndoGridItemEdit, CXTPPropertyGridItem)

CEndoGridItemEdit::CEndoGridItemEdit(UINT nID, LPCTSTR strValue, CString* pBindString, CAMBaseSet* pSet, long lComboTable/*, BOOL bCheckReadOnly*/)
: CXTPPropertyGridItem(nID, strValue, pBindString)
{
	m_lComboTable = lComboTable;
	m_pSet = pSet;
	m_bCheckReadOnly = TRUE;
	InitItemEdit();
}

CEndoGridItemEdit::CEndoGridItemEdit(CString strCaption, LPCTSTR strValue, CString* pBindString, CAMBaseSet* pSet, long lComboTable/*, BOOL bCheckReadOnly*/)
	: CXTPPropertyGridItem(strCaption, strValue, pBindString)
{
	m_lComboTable = lComboTable;
	m_pSet = pSet;
	m_bCheckReadOnly = TRUE;
	InitItemEdit();
}

CEndoGridItemEdit::CEndoGridItemEdit(long lParameterID, CString strCaption, BOOL bAllowMultiSelect, BOOL bFixedCombo)
	: CXTPPropertyGridItem(strCaption, NULL, NULL)
{
	m_lComboTable = lParameterID;
	m_pSet = NULL;
	m_bCheckReadOnly = TRUE;
	InitItemEdit();

	m_bAllowMultiSelect = bAllowMultiSelect;
	if (bFixedCombo)
		PrepareAsFixedCombo();
}

CEndoGridItemEdit::~CEndoGridItemEdit(void)
{
}

void CEndoGridItemEdit::InitItemEdit()
{
	if (m_lComboTable != -1)
		SetFlags(GetFlags() | xtpGridItemHasComboButton);

	SetLimitText(m_pBindString, m_pSet);
}

void CEndoGridItemEdit::OnAddChildItem()
{
	CXTPPropertyGridItem::OnAddChildItem();
}

void CEndoGridItemEdit::SetLimitText(CString* pBindString, CAMBaseSet* pSet)
{
	//int nIndex, nIndexEnd;
	m_nMax = 0;

	/*if (pSet && pBindString)
	{
		if (!pSet->IsOpen())
			pSet->OpenRecordset("CEndoGridItemEdit::SetLimitText");

		// GetBoundFieldIndex returns 1-based index
		nIndex = pSet->GetBoundFieldIndex(pBindString) - 1;

		if (nIndex < 0)
		{
			// pv must be address of field member
			ASSERT(FALSE);
			return;
		}
		else
		{
			nIndexEnd = nIndex;
		}

		CODBCFieldInfo info;
		if (nIndex > 0 && nIndex <= nIndexEnd)
		{
			pSet->GetODBCFieldInfo(nIndex, info);
			m_nMax = info.m_nPrecision;
		}
	}*/

	m_nMax = MAX_PATH;
}

int CEndoGridItemEdit::GetLimitText()
{
	return m_nMax;
}

//!Descrizione:	invia messaggio di notifica del cambiamento alla finestra padre
//! strValue: il valore che viene selezionato 
void CEndoGridItemEdit::OnValueChanged(CString strValue)
{
	/*CString strPrecValue = GetValue();*/

	CXTPPropertyGridItem::OnValueChanged(strValue);

	/*if ((theApp.m_nProgramMode == NOTHING_MODE) && m_bCheckReadOnly)
		SetValue(strPrecValue);*/

}

void CEndoGridItemEdit::OnInplaceButtonDown(CXTPPropertyGridInplaceButton* pButton)
{
	if (m_lComboTable > 0 && GetFlags() & xtpGridItemHasComboButton)
	{
		CEndoGridComboDlg dlg(m_lComboTable, GetValue(), m_bAllowMultiSelect, FALSE);
		if (dlg.DoModal() == IDOK)
			SetValue(dlg.m_strEdit);

		OnSelect();
		SetFocusToInplaceControl();
	}
	else
		CXTPPropertyGridItem::OnInplaceButtonDown(pButton);	
}

BOOL CEndoGridItemEdit::OnChar(UINT nChar)
{
	NotifyDirty();
	return CXTPPropertyGridItem::OnChar(nChar);
}

void CEndoGridItemEdit::NotifyDirty()
{
	if (m_pGrid)
		m_pGrid->GetParent()->PostMessage(EPM_ITEMDIRTY);
}

void CEndoGridItemEdit::PrepareAsFixedCombo()
{
	m_nFlags = xtpGridItemHasComboButton /*| pgiHasEdit*/;
	SetConstraintEdit(TRUE);

	CEndoGridCLComboSet set;
	CString strFilter;
	strFilter.Format("idparametro = %li", m_lComboTable);

	set.SetOpenFilter(strFilter);
	set.SetSortRecord("descrizione");

	GetConstraints()->AddConstraint("");

	try
	{
		if (set.OpenRecordset("CEndoGridItemEdit::PrepareAsFixedCombo"))
		{
			while (!set.IsEOF())
			{
				GetConstraints()->AddConstraint(set.m_sDescrizione);
				set.MoveNext();
			}

			set.CloseRecordset("CEndoGridItemEdit::PrepareAsFixedCombo");
		}
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}

	m_lComboTable = -1;
}

void CEndoGridItemEdit::OnDrawItemConstraint(CDC* pDC, CXTPPropertyGridItemConstraint* pConstraint, CRect rc, BOOL bSelected)
{
	GetGrid()->GetPaintManager()->DrawInplaceListItem(pDC, pConstraint, rc, bSelected, RGB(255, 255, 255));
}