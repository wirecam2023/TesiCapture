#include "stdafx.h"
#include "Endox.h"
#include "AccessoriCombo.h"

#include "ComboBoxSet.h"
#include "EsamiView.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAccessoriCombo::CAccessoriCombo()
{
}

CAccessoriCombo::~CAccessoriCombo()
{
}

BEGIN_MESSAGE_MAP(CAccessoriCombo, CComboBox)

	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)

END_MESSAGE_MAP()

void CAccessoriCombo::OnCloseup() 
{
	// quando il Combo perde il Focus tutta la memoria occupata dalle sue
	// stringhe viene liberata, meno la stringa correntemente selezionata
	int nCount = GetCount();

	if (nCount > 0)
	{
		CString survivorStr  = "";
		long	survivorData = -1;
		int		CurSel = GetCurSel();
		
		if (CurSel >= 0)
		{
			GetLBText(CurSel, survivorStr);
			survivorData = GetItemData(CurSel);
		}
	
		//svuoto ed inserisco solo la stringa selezionata
		ResetContent();
		
		if (survivorData >= 0)
		{
			CurSel =  AddString((LPCSTR) survivorStr);
		
			if (CurSel >= 0)
			{
				SetItemData(CurSel, (DWORD) survivorData);
	
				SetCurSel(CurSel);
			}
		}
	}
}

void CAccessoriCombo::OnDropdown() 
{
	BeginWaitCursor();

	int nCurSel = GetCurSel();
	long lCurSelData = 0;
	CString sCurSelStr = "";
	if (nCurSel >= 0)
	{
		GetLBText(nCurSel, sCurSelStr);
		lCurSelData = GetItemData(nCurSel);
	}

	ResetContent();
	int posiz = AddString("");
	if (posiz >= 0)
		SetItemData(posiz, 0);

	CComboBoxSet setAccessori(CMB_ESA_ACCESS);
	setAccessori.SetSortRecord("Testo");
	if (setAccessori.OpenRecordset("CAccessoriCombo::OnDropdown"))
	{
		while (!setAccessori.IsEOF())
		{
			posiz = AddString(setAccessori.m_sTesto);
			if (posiz >= 0)
				SetItemData(posiz, (DWORD)setAccessori.m_lContatore);

			setAccessori.MoveNext();
		}

		setAccessori.CloseRecordset("CAccessoriCombo::OnDropdown");
	}

	SelectString(-1, sCurSelStr);

	EndWaitCursor();
}
