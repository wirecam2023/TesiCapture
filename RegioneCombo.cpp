#include "stdafx.h"
#include "Endox.h"
#include "RegioneCombo.h"

#include "CodificaRegionaleExSet.h"
#include "TipiEsamiPrestazioniSet.h"
#include "EsamiView.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRegioneCombo::CRegioneCombo()
{
	m_pEsamiView = NULL;
	m_pRegione = NULL;
}

CRegioneCombo::~CRegioneCombo()
{
}

void CRegioneCombo::SetParam(long* pRegione, CEsamiView* pEsamiView)
{
	m_pEsamiView = pEsamiView;
	m_pRegione = pRegione;
}

BEGIN_MESSAGE_MAP(CRegioneCombo, CComboBox)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
END_MESSAGE_MAP()

void CRegioneCombo::OnCloseup() 
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

void CRegioneCombo::OnDropdown() 
{

	BOOL bError = FALSE;

	if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI))
	{
		// siamo in ricerca //

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

		CCodificaRegionaleExSet setTemp;
		if (setTemp.OpenRecordset("CRegioneCombo::OnDropdown"))
		{
			while (!setTemp.IsEOF())
			{
				posiz = AddString(setTemp.m_sDescrizione);
				if (posiz >= 0)
					SetItemData(posiz, (DWORD)setTemp.m_lContatore);

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CRegioneCombo::OnDropdown");
		}

		SelectString(-1, sCurSelStr);

		EndWaitCursor();
	}
	else
	{
		// NON siamo in ricerca //

		CString sFilter;
		sFilter.Format("TipoEsame=%li", m_pEsamiView->m_pEsamiSet->m_lIDEsame);

		CTipiEsamiPrestazioniSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CRegioneCombo::OnDropdown"))
		{
			int		nCurSel = GetCurSel();
			CString sCurSelStr = "";
			long	lCurSelData = 0;
			if (nCurSel >= 0)
			{
				GetLBText(nCurSel, sCurSelStr);
				lCurSelData = GetItemData(nCurSel);
			}

			ResetContent();
			int posiz = AddString("");
			if (posiz >= 0)
				SetItemData(posiz, 0);

			while(!setTemp.IsEOF())
			{
				sFilter.Format("Contatore=%li", setTemp.m_lPrestazione);

				CCodificaRegionaleExSet setTeeemp;
				setTeeemp.SetOpenFilter(sFilter);
				if (setTeeemp.OpenRecordset("CRegioneCombo::OnDropdown"))
				{
					if (!setTeeemp.IsEOF())
					{
						CString sVoice = setTeeemp.m_sDescrizione;

						switch(theApp.m_lCodificaRegionaleMostraCodice)
						{
							case 1:
							{
								// codice NAZIONALE in fondo, tra parentesi //

								if (!setTeeemp.m_sCodiceNazionale.IsEmpty())
									sVoice += " (" + setTeeemp.m_sCodiceNazionale + ")";

								break;
							}
							case 2:
							{
								// codice NAZIONALE all'inizio //

								if (!setTeeemp.m_sCodiceNazionale.IsEmpty())
									sVoice = setTeeemp.m_sCodiceNazionale + " - " + setTeeemp.m_sDescrizione;

								break;
							}
							case 3:
							{
								// codice REGIONALE in fondo, tra parentesi //

								if (!setTeeemp.m_sCodiceRegionale.IsEmpty())
									sVoice += " (" + setTeeemp.m_sCodiceRegionale + ")";

								break;
							}
							case 4:
							{
								// codice REGIONALE all'inizio //

								if (!setTeeemp.m_sCodiceRegionale.IsEmpty())
									sVoice = setTeeemp.m_sCodiceRegionale + " - " + setTeeemp.m_sDescrizione;

								break;
							}
						}

						posiz = AddString(sVoice);
						if (posiz >= 0)
							SetItemData(posiz, (DWORD)setTeeemp.m_lContatore);
					}

					setTeeemp.CloseRecordset("CRegioneCombo::OnDropdown");
				}

				setTemp.MoveNext();
			}

			SelectString(-1, sCurSelStr);

			setTemp.CloseRecordset("CRegioneCombo::OnDropdown");
		}
	}
}
