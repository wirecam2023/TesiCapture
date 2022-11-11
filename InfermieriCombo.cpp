#include "stdafx.h"
#include "Endox.h"
#include "InfermieriCombo.h"

#include "InfermieriSet.h"
#include "SediEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInfermieriCombo::CInfermieriCombo()
{
}

CInfermieriCombo::~CInfermieriCombo()
{
}

BEGIN_MESSAGE_MAP(CInfermieriCombo, CComboBox)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
END_MESSAGE_MAP()

void CInfermieriCombo::OnCloseup() 
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

void CInfermieriCombo::OnDropdown() 
{
	CString sSort = "Cognome, Nome";
	if (theApp.m_bPersonalizzazioniBrasileEinstein)
		sSort = "Nome, Cognome";

	CInfermieriSet setInf;
	setInf.SetOpenFilter("ELIMINATO=0 AND Sede='" + CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, TRUE) + "'");
	setInf.SetSortRecord(sSort);
	if (setInf.OpenRecordset("CInfermieriCombo::OnDropdown"))
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

			while (!setInf.IsEOF())
			{
				CString strAdd = setInf.m_sTitolo + " " + setInf.m_sNome + " " + setInf.m_sCognome;
				strAdd.Replace("  ", " ");
				strAdd.Trim();
				int posiz = AddString(strAdd);

				if (posiz >= 0)
					SetItemData(posiz, (DWORD)setInf.m_lContatore);

				setInf.MoveNext();
			}

			SelectString(-1, CurSelStr);
		}
		else	// ItemsCount == 0 => il combo é vuoto
		{		// Questa parte di codice serve se si prevede di gestire qui il fatto
			// che nel combo non vi sia nulla e quindi recuperare da disco i dati 
			// necessari alla selezione

			if (ItemsCount == 0)		// dovrebbe normalmente essere 1 ( o 0 [caso da evitare])
			{
				while (!setInf.IsEOF())
				{
					CString strAdd = setInf.m_sTitolo + " " + setInf.m_sNome + " " + setInf.m_sCognome;
					strAdd.Replace("  ", " ");
					strAdd.Trim();
					int posiz = AddString(strAdd);

					if (posiz >= 0)
						SetItemData(posiz, (DWORD)setInf.m_lContatore);

					setInf.MoveNext();
				}
			}
		}

		setInf.CloseRecordset("CInfermieriCombo::OnDropdown");
	}
}