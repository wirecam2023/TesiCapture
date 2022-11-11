#include "stdafx.h"
#include "Endox.h"
#include "TipoEsameCombo.h"

#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTipoEsameCombo::CTipoEsameCombo()
{
	m_pMainSet = NULL;
	m_pTipoEsame = NULL;
}

CTipoEsameCombo::~CTipoEsameCombo()
{
}

void CTipoEsameCombo::SetParam(CBaseSet* pMainSet, long* pTipoEsame)
{
	m_pMainSet = pMainSet;
	m_pTipoEsame = pTipoEsame;
}

BEGIN_MESSAGE_MAP(CTipoEsameCombo, CComboBox)

	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)

END_MESSAGE_MAP()

void CTipoEsameCombo::OnCloseup() 
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

void CTipoEsameCombo::OnDropdown() 
{
	CTipoEsameSet setTipoEsame;
	setTipoEsame.SetSortRecord("Descrizione, Sigla");

	if (setTipoEsame.OpenRecordset("CTipoEsameCombo::OnDropdown"))
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

			while (!setTipoEsame.IsEOF())
			{
				CString strAdd = setTipoEsame.m_sDescrizione;
				// Sandro 03/05/2012 // commento le due righe qui sotto //
				// strAdd.Replace("  ", " ");
				// strAdd.Trim();
				int posiz = AddString(strAdd);

				if (posiz >= 0)
					SetItemData(posiz, (DWORD)setTipoEsame.m_lContatore);

				setTipoEsame.MoveNext();
			}

			SelectString(-1, CurSelStr);
		}
		else	// ItemsCount == 0 => il combo é vuoto
		{		// Questa parte di codice serve se si prevede di gestire qui il fatto
			// che nel combo non vi sia nulla e quindi recuperare da disco i dati 
			// necessari alla selezione

			if (ItemsCount == 0)		// dovrebbe normalmente essere 1 ( o 0 [caso da evitare])
			{
				while (!setTipoEsame.IsEOF())
				{
					CString strAdd = setTipoEsame.m_sDescrizione;
					// Sandro 03/05/2012 // commento le due righe qui sotto //
					// strAdd.Replace("  ", " ");
					// strAdd.Trim();
					int posiz = AddString(strAdd);

					if (posiz >= 0)
						SetItemData(posiz, (DWORD)setTipoEsame.m_lContatore);

					setTipoEsame.MoveNext();
				}
			}
		}

		setTipoEsame.CloseRecordset("CTipoEsameCombo::OnDropdown");
	}
}