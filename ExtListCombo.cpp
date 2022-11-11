#include "stdafx.h"
#include "Endox.h"
#include "ExtListCombo.h"

#include "ComboBoxSet.h"
#include "Common.h"
#include "SediEsameSet.h"
#include "StrumentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CExtListCombo, CExtList)

CExtListCombo::CExtListCombo()
	:CExtList()
{
}

CExtListCombo::~CExtListCombo()
{
}

BEGIN_MESSAGE_MAP(CExtListCombo, CExtList)
END_MESSAGE_MAP()

BOOL CExtListCombo::SetParamSet(long lComboDefine, BOOL bOrderByString)
{
	BOOL bError = TRUE;
	
	if (lComboDefine >= 0)
	{
		ResetContent();

		CComboBoxSet setCombo(lComboDefine);

		if (bOrderByString)
			setCombo.SetSortRecord("Testo");
		else
			setCombo.SetSortRecord("Contatore");

		if (setCombo.OpenRecordset("CExtListCombo::SetParamSet"))
		{
			bError = FALSE;

			while (!setCombo.IsEOF())
			{
				if (!setCombo.IsFieldNull(&setCombo.m_sTesto) && !setCombo.m_sTesto.IsEmpty())
				{
					int nPos = AddString(setCombo.m_sTesto);
					if (nPos >= 0)
						SetItemData(nPos, (DWORD)setCombo.m_lContatore);
				}

				setCombo.MoveNext();
			}

			setCombo.CloseRecordset("CExtListCombo::SetParamSet");
		}
	}
	else
	{
		// STRUMENTI //

		ResetContent();

		CStrumentiSet setStrumenti;
		setStrumenti.SetOpenFilter("ELIMINATO=0 AND Sede='" + CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, TRUE) + "'");

		if (bOrderByString)
			setStrumenti.SetSortRecord("Testo");
		else
			setStrumenti.SetSortRecord("Contatore");

		if (setStrumenti.OpenRecordset("CExtListCombo::SetParamSet"))
		{
			bError = FALSE;

			while (!setStrumenti.IsEOF())
			{
				if (!setStrumenti.IsFieldNull(&setStrumenti.m_sTesto) && !setStrumenti.m_sTesto.IsEmpty())
				{
					int nPos = AddString(setStrumenti.m_sTesto);
					if (nPos >= 0)
						SetItemData(nPos, (DWORD)setStrumenti.m_lContatore);
				}

				setStrumenti.MoveNext();
			}

			setStrumenti.CloseRecordset("CExtListCombo::SetParamSet");
		}
	}

	return !bError;
}
