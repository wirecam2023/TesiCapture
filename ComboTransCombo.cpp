#include "stdafx.h"
#include "Endox.h"
#include "ComboTransCombo.h"

#include "ComboTransSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComboTransCombo::CComboTransCombo()
{
	m_pSetComboTrans = NULL;
	m_pMainSet = NULL;
	m_pValore = NULL;
}

CComboTransCombo::~CComboTransCombo()
{
}

void CComboTransCombo::SetParam(CBaseSet* pMainSet, long* pValore, CComboTransSet* pSet)
{
	m_pSetComboTrans = pSet;
	m_pMainSet = pMainSet;
	m_pValore = pValore;
}

BEGIN_MESSAGE_MAP(CComboTransCombo, CComboBox)

	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)

END_MESSAGE_MAP()

void CComboTransCombo::OnCloseup() 
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

void CComboTransCombo::OnDropdown() 
{
	m_pSetComboTrans->SetOpenFilter("");
	m_pSetComboTrans->SetSortRecord("Descrizione");

	if (m_pSetComboTrans->OpenRecordset("CComboTransCombo::OnDropdown"))
	{
		int ItemsCount = GetCount();
		if (ItemsCount == 1)		// dovrebbe normalmente essere 1 ( o 0 [caso da evitare])
		{
			int		CurSel = GetCurSel();	// CurSel == 1
			CString CurSelStr = "";
			long	CurSelData = 0;

			if (CurSel >= 0)
			{
				GetLBText(CurSel, CurSelStr);
				CurSelData = GetItemData(CurSel);
			}

			//svuoto ed inserisco solo la stringa selezionata
			ResetContent();

			// niente stringa vuota iniziale....
			// int posiz = AddString("");

			// if (posiz >= 0)
			// 	SetItemData(posiz, 0);
			////////////////////////////

			while (!m_pSetComboTrans->IsEOF())
			{
				CString strAdd = m_pSetComboTrans->m_sDescrizione;
				strAdd.Replace("  ", " ");
				strAdd.Trim();
				int posiz = AddString(strAdd);

				if (posiz >= 0)
					SetItemData(posiz, (DWORD)m_pSetComboTrans->m_lID);

				m_pSetComboTrans->MoveNext();
			}

			SelectString(-1, CurSelStr);
		}
		else	// ItemsCount == 0 => il combo é vuoto
		{		// Questa parte di codice serve se si prevede di gestire qui il fatto
			// che nel combo non vi sia nulla e quindi recuperare da disco i dati 
			// necessari alla selezione

			if (ItemsCount == 0)		// dovrebbe normalmente essere 1 ( o 0 [caso da evitare])
			{
				while (!m_pSetComboTrans->IsEOF())
				{
					CString strAdd = m_pSetComboTrans->m_sDescrizione;
					strAdd.Replace("  ", " ");
					strAdd.Trim();
					int posiz = AddString(strAdd);

					if (posiz >= 0)
						SetItemData(posiz, (DWORD)m_pSetComboTrans->m_lID);

					m_pSetComboTrans->MoveNext();
				}
			}
		}

		m_pSetComboTrans->CloseRecordset("CComboTransCombo::OnDropdown");
	}
}