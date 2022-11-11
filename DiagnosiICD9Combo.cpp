#include "stdafx.h"
#include "Endox.h"
#include "DiagnosiICD9Combo.h"

#include "DiagnosiICD9Set.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "VistaDiagnosiICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDiagnosiICD9Combo::CDiagnosiICD9Combo()
{
	m_pEsamiView = NULL;
	m_pDiagnosi = NULL;
}

CDiagnosiICD9Combo::~CDiagnosiICD9Combo()
{
}

BEGIN_MESSAGE_MAP(CDiagnosiICD9Combo, CComboBox)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
END_MESSAGE_MAP()

void CDiagnosiICD9Combo::SetParam(CEsamiView* pEsamiView, long* pDiagnosi)
{
	m_pEsamiView = pEsamiView;
	m_pDiagnosi	= pDiagnosi;
}

void CDiagnosiICD9Combo::OnCloseup() 
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

void CDiagnosiICD9Combo::OnDropdown() 
{
	BeginWaitCursor();

	if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI))
	{
		// siamo in ricerca //

		CString sCurSelStr = "";
		int nCurSel = GetCurSel();
		if (nCurSel >= 0)
			GetLBText(nCurSel, sCurSelStr);

		ResetContent();

		InsertString(0, "");
		SetItemData(0, 0);

		int nIndex = 1;
		CDiagnosiICD9Set setD;
		setD.SetSortRecord("Descrizione");
		if (setD.OpenRecordset("CDiagnosiICD9Combo::OnDropdown"))
		{
			while(!setD.IsEOF())
			{
				if (m_pEsamiView->m_pEsamiSet->m_lProvenienza == ESTERNO)
					InsertString(nIndex, setD.m_sDescrizione + " - " + setD.m_sCodificaICD9Esterni + " - " + setD.m_sCodificaInterna);
				else
					InsertString(nIndex, setD.m_sDescrizione + " - " + setD.m_sCodificaICD9Interni + " - " + setD.m_sCodificaInterna);
				SetItemData(nIndex, (DWORD)setD.m_lID);

				nIndex++;
				setD.MoveNext();
			}
		}

		SelectString(-1, sCurSelStr);
	}
	else
	{
		// NON siamo in ricerca //

		CString sCurSelStr = "";
		int nCurSel = GetCurSel();
		if (nCurSel >= 0)
			GetLBText(nCurSel, sCurSelStr);

		ResetContent();

		CString strFilter;
		strFilter.Format("IDTipoEsame=%li", m_pEsamiView->m_pEsamiSet->m_lIDEsame);

		InsertString(0, "");
		SetItemData(0, 0);

		int nIndex = 1;
		CVistaDiagnosiICD9Set setVD;
		setVD.SetOpenFilter(strFilter);
		if (setVD.OpenRecordset("CDiagnosiICD9Combo::OnDropdown"))
		{
			while(!setVD.IsEOF())
			{
				if (m_pEsamiView->m_pEsamiSet->m_lProvenienza == ESTERNO)
					InsertString(nIndex, setVD.m_sDescrizione + " - " + setVD.m_sCodificaICD9Esterni + " - " + setVD.m_sCodificaInterna);
				else
					InsertString(nIndex, setVD.m_sDescrizione + " - " + setVD.m_sCodificaICD9Interni + " - " + setVD.m_sCodificaInterna);
				SetItemData(nIndex, (DWORD)setVD.m_lID);

				nIndex++;
				setVD.MoveNext();
			}
		}

		SelectString(-1, sCurSelStr);
	}

	EndWaitCursor();
}
