#include "stdafx.h"
#include "Endox.h"
#include "ProcedureICD9Combo.h"

#include "EsamiSet.h"
#include "EsamiView.h"
#include "ProcedureICD9Set.h"
#include "VistaProcedureICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CProcedureICD9Combo::CProcedureICD9Combo()
{
	m_pEsamiView = NULL;
	m_pProcedura = NULL;
}

CProcedureICD9Combo::~CProcedureICD9Combo()
{
}

BEGIN_MESSAGE_MAP(CProcedureICD9Combo, CComboBox)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
END_MESSAGE_MAP()

void CProcedureICD9Combo::SetParam(CEsamiView* pEsamiView, long* pProcedura)
{
	m_pEsamiView = pEsamiView;
	m_pProcedura = pProcedura;
}

void CProcedureICD9Combo::OnCloseup() 
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

void CProcedureICD9Combo::OnDropdown() 
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
		CProcedureICD9Set setP;
		setP.SetSortRecord("Descrizione");
		if (setP.OpenRecordset("CDiagnosiICD9Combo::OnDropdown"))
		{
			while(!setP.IsEOF())
			{
				if (m_pEsamiView->m_pEsamiSet->m_lProvenienza == ESTERNO)
					InsertString(nIndex, setP.m_sDescrizione + " - " + setP.m_sCodificaICD9Esterni + " - " + setP.m_sCodificaInterna);
				else
					InsertString(nIndex, setP.m_sDescrizione + " - " + setP.m_sCodificaICD9Interni + " - " + setP.m_sCodificaInterna);
				SetItemData(nIndex, (DWORD)setP.m_lID);

				nIndex++;
				setP.MoveNext();
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
		CVistaProcedureICD9Set setVP;
		setVP.SetOpenFilter(strFilter);
		if (setVP.OpenRecordset("CDiagnosiICD9Combo::OnDropdown"))
		{
			while(!setVP.IsEOF())
			{
				if (m_pEsamiView->m_pEsamiSet->m_lProvenienza == ESTERNO)
					InsertString(nIndex, setVP.m_sDescrizione + " - " + setVP.m_sCodificaICD9Esterni + " - " + setVP.m_sCodificaInterna);
				else
					InsertString(nIndex, setVP.m_sDescrizione + " - " + setVP.m_sCodificaICD9Interni + " - " + setVP.m_sCodificaInterna);
				SetItemData(nIndex, (DWORD)setVP.m_lID);

				nIndex++;
				setVP.MoveNext();
			}
		}

		SelectString(-1, sCurSelStr);
	}

	EndWaitCursor();
}
