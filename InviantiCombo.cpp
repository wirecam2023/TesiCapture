#include "stdafx.h"
#include "Endox.h"
#include "InviantiCombo.h"

#include "Define.h"
#include "InviantiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInviantiCombo::CInviantiCombo()
{
	m_pMainSet = NULL;
	m_pInviante = NULL;
	m_pProvenienza = NULL;
}

CInviantiCombo::~CInviantiCombo()
{
}

void CInviantiCombo::SetParam(CBaseSet* pMainSet, long* pInviante, long* pProvenienza)
{
	m_pMainSet = pMainSet;
	m_pInviante = pInviante;
	m_pProvenienza = pProvenienza;
}

BEGIN_MESSAGE_MAP(CInviantiCombo, CComboBox)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
END_MESSAGE_MAP()

void CInviantiCombo::OnCloseup() 
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

void CInviantiCombo::OnDropdown() 
{
	if (!m_pProvenienza || *m_pProvenienza < INTERNO || *m_pProvenienza > ESTERNO)
		return;

	CInviantiSet setInvianti;

	switch (*m_pProvenienza)
	{
		case INTERNO:
		{
			setInvianti.SetSortRecord("Descrizione");
			setInvianti.SetTableName("EInviantiInterni");
			break;
		}
		case ESTERNO:
		{
			setInvianti.SetSortRecord("Contatore");
			setInvianti.SetTableName("EInviantiEsterni");
			break;
		}
	}

	if (setInvianti.OpenRecordset("CInviantiCombo::OnDropdown"))
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

			//stringa vuota iniziale....
			int posiz = AddString("");

			if (posiz >= 0)
				SetItemData(posiz, 0);
			////////////////////////////

			while (!setInvianti.IsEOF())
			{
				int posiz = AddString(setInvianti.m_sDescrizione);

				if (posiz >= 0)
					SetItemData(posiz, (DWORD)setInvianti.m_lContatore);

				setInvianti.MoveNext();
			}

			SelectString(-1, CurSelStr);
		}
		else	// ItemsCount == 0 => il combo é vuoto
		{		// Questa parte di codice serve se si prevede di gestire qui il fatto
			// che nel combo non vi sia nulla e quindi recuperare da disco i dati 
			// necessari alla selezione

			if (ItemsCount == 0)		// dovrebbe normalmente essere 1 ( o 0 [caso da evitare])
			{
				while (!setInvianti.IsEOF())
				{
					int posiz = AddString(setInvianti.m_sDescrizione);

					if (posiz >= 0)
						SetItemData(posiz, (DWORD)setInvianti.m_lContatore);

					setInvianti.MoveNext();
				}
			}
		}

		setInvianti.CloseRecordset("CInviantiCombo::OnDropdown");
	}

}