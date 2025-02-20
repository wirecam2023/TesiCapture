#include "stdafx.h"
#include "Endox.h"
#include "ProvenienzeCombo.h"

#include "Define.h"
#include "ProvenienzaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CProvenienzeCombo::CProvenienzeCombo()
{
	m_pMainSet = NULL;
	m_pIdProvenienza = NULL;
}

CProvenienzeCombo::~CProvenienzeCombo()
{
}

void CProvenienzeCombo::SetParam(CBaseSet* pMainSet, long* pIdProvenienza)
{
	m_pMainSet = pMainSet;
	m_pIdProvenienza = pIdProvenienza;
}

BEGIN_MESSAGE_MAP(CProvenienzeCombo, CComboBox)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
END_MESSAGE_MAP()

void CProvenienzeCombo::OnCloseup()
{
	// quando il Combo perde il Focus tutta la memoria occupata dalle sue
	// stringhe viene liberata, meno la stringa correntemente selezionata
	int nCount = GetCount();

	if (nCount > 0)
	{
		CString survivorStr = "";
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
			CurSel = AddString((LPCSTR)survivorStr);

			if (CurSel >= 0)
			{
				SetItemData(CurSel, (DWORD)survivorData);

				SetCurSel(CurSel);
			}
		}
	}
}

void CProvenienzeCombo::OnDropdown()
{
	CProvenienzaSet setProvenienza;

	setProvenienza.SetSortRecord("Descrizione");	

	if (setProvenienza.OpenRecordset("CProvenienzeCombo::OnDropdown"))
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
			/*int posiz = AddString("");

			if (posiz >= 0)
				SetItemData(posiz, 0);*/
			////////////////////////////

			while (!setProvenienza.IsEOF())
			{
				CString descrizione = setProvenienza.m_sDescrizione;

				if (setProvenienza.m_lIdProvenienzaEndox == INTERNO)
					descrizione += " (" + theApp.GetMessageString(IDS_INTERNO).MakeUpper() + ")";
				else
					descrizione += " (" + theApp.GetMessageString(IDS_ESTERNO).MakeUpper() + ")";

				int posiz = AddString(descrizione);

				if (posiz >= 0)
					SetItemData(posiz, (DWORD)setProvenienza.m_lId);

				setProvenienza.MoveNext();
			}

			SelectString(-1, CurSelStr);
		}
		else	// ItemsCount == 0 => il combo � vuoto
		{		// Questa parte di codice serve se si prevede di gestire qui il fatto
			// che nel combo non vi sia nulla e quindi recuperare da disco i dati 
			// necessari alla selezione

			if (ItemsCount == 0)		// dovrebbe normalmente essere 1 ( o 0 [caso da evitare])
			{
				while (!setProvenienza.IsEOF())
				{
					CString descrizione = setProvenienza.m_sDescrizione;

					if (setProvenienza.m_lIdProvenienzaEndox == INTERNO)
						descrizione += " (" + theApp.GetMessageString(IDS_INTERNO).MakeUpper() + ")";
					else
						descrizione += " (" + theApp.GetMessageString(IDS_ESTERNO).MakeUpper() + ")";

					int posiz = AddString(descrizione);

					if (posiz >= 0)
						SetItemData(posiz, (DWORD)setProvenienza.m_lId);

					setProvenienza.MoveNext();
				}
			}
		}

		setProvenienza.CloseRecordset("CProvenienzeCombo::OnDropdown");
	}

}