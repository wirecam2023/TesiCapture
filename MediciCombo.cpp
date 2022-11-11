#include "stdafx.h"
#include "Endox.h"
#include "MediciCombo.h"
#include "VistaUtentiSet.h"
#include "MediciSet.h"

#include "VistaMediciSedeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMediciCombo::CMediciCombo()
{
}

CMediciCombo::~CMediciCombo()
{
}

BEGIN_MESSAGE_MAP(CMediciCombo, CComboBox)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
END_MESSAGE_MAP()

void CMediciCombo::OnCloseup() 
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

void CMediciCombo::OnDropdown() 
{
	BOOL bError = FALSE;

	// Sandro 26/11/2015 // RAS 20150015 //
	CString sFilter;
	sFilter.Format("IDSede=%li", theApp.m_lIDSedeEsameDefault);

	//
	CString sSort = "Cognome, Nome";
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
		sSort = "Nome, Cognome";

	//
	CVistaMediciSedeSet setTemp;
	setTemp.SetOpenFilter(sFilter);
	setTemp.SetSortRecord(sSort);
	if (setTemp.OpenRecordset("CMediciCombo::OnDropdown"))
	{
		switch (GetCount())
		{
			case 0:
			{
				while (!setTemp.IsEOF())
				{
					CString strAdd = setTemp.m_sTitolo + " " + setTemp.m_sNome + " " + setTemp.m_sCognome;
					strAdd.Replace("  ", " ");
					strAdd.Trim();

					int nPosiz = AddString(strAdd);
					if (nPosiz >= 0)
						SetItemData(nPosiz, (DWORD)setTemp.m_lContatore);

					setTemp.MoveNext();
				}

				break;
			}
			case 1:
			{
				int nCurSel = GetCurSel();
				CString sCurSelStr = "";

				if (nCurSel >= 0)
					GetLBText(nCurSel, sCurSelStr);

				// svuoto ed inserisco solo la stringa selezionata //

				ResetContent();

				// stringa vuota iniziale //

				int nPosiz = AddString("");
				if (nPosiz >= 0)
					SetItemData(nPosiz, 0);

				//

				while (!setTemp.IsEOF())
				{
					CString strAdd = setTemp.m_sTitolo + " " + setTemp.m_sNome + " " + setTemp.m_sCognome;
					strAdd.Replace("  ", " ");
					strAdd.Trim();

					nPosiz = AddString(strAdd);
					if (nPosiz >= 0)
						SetItemData(nPosiz, (DWORD)setTemp.m_lContatore);

					setTemp.MoveNext();
				}

				//

				SelectString(-1, sCurSelStr);

				//

				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
			}
		}
		
		setTemp.CloseRecordset("CMediciCombo::OnDropdown");
	}
}

void CMediciCombo::SelectCurrent(CWnd* pParentView)
{
	m_pParentView = pParentView;

	CString sFilter;
	long lIDUtenti = 0;
	long lContatore = 0;

	CVistaUtentiSet set;
	set.SetSortRecord("USERNAME");
	sFilter.Format("USERNAME = '%s'", theApp.m_sUtenteLoggato);
	set.SetOpenFilter(sFilter);

	if (set.OpenRecordset("CMediciCombo::SelectCurrent"))
	{
		if (!set.IsEOF())
		{
			lIDUtenti = set.m_lId;
		}
		set.CloseRecordset("CMediciCombo::SelectCurrent");
	}

	if (lIDUtenti > 0)
	{
		CMediciSet setMed;
		sFilter.Format("idutenteendox = %li and uo = %li", lIDUtenti, theApp.m_lUO);
		setMed.SetOpenFilter(sFilter);

		if (setMed.OpenRecordset("CMediciCombo::SelectCurrent"))
		{
			if (!setMed.IsEOF())
			{
				lContatore = setMed.m_lContatore;
			}
			setMed.CloseRecordset("CMediciCombo::SelectCurrent");
		}
	}

	//////////////////////

	BOOL bError = FALSE;
	
	sFilter.Format("Contatore=%li", lContatore);

	CString sSort = "Cognome, Nome";
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
		sSort = "Nome, Cognome";

	CVistaMediciSedeSet setTemp;
	setTemp.SetOpenFilter(sFilter);
	setTemp.SetSortRecord(sSort);
	if (setTemp.OpenRecordset("CMediciCombo::SelectCurrent"))
	{
		switch (GetCount())
		{
		case 0:
		{
			while (!setTemp.IsEOF())
			{
				CString strAdd = setTemp.m_sTitolo + " " + setTemp.m_sNome + " " + setTemp.m_sCognome;
				strAdd.Replace("  ", " ");
				strAdd.Trim();

				int nPosiz = AddString(strAdd);
				if (nPosiz >= 0)
					SetItemData(nPosiz, (DWORD)setTemp.m_lContatore);

				setTemp.MoveNext();
			}

			break;
		}
		case 1:
		{
			int nCurSel = GetCurSel();
			CString sCurSelStr = "";

			if (nCurSel >= 0)
				GetLBText(nCurSel, sCurSelStr);

			// svuoto ed inserisco solo la stringa selezionata //

			ResetContent();

			// stringa vuota iniziale //

			int nPosiz = AddString("");
			if (nPosiz >= 0)
				SetItemData(nPosiz, 0);

			//

			while (!setTemp.IsEOF())
			{
				CString strAdd = setTemp.m_sTitolo + " " + setTemp.m_sNome + " " + setTemp.m_sCognome;
				strAdd.Replace("  ", " ");
				strAdd.Trim();

				nPosiz = AddString(strAdd);
				if (nPosiz >= 0)
					SetItemData(nPosiz, (DWORD)setTemp.m_lContatore);

				setTemp.MoveNext();
			}

			//

			SelectString(-1, sCurSelStr);
			
			//

			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
		}

		setTemp.CloseRecordset("CMediciCombo::SelectCurrent");
	}
	SetCurSel(0);
}
