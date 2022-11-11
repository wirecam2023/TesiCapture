#include "stdafx.h"
#include "Endox.h"
#include "ExtMedicoCuranteInviante.h"

#include "MediciCurantiInviantiDlg.h"
#include "BaseSet.h"
#include "Define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CExtMedicoCuranteInviante, CEdit)

CExtMedicoCuranteInviante::CExtMedicoCuranteInviante()
	: CEdit()
{
	m_pParentView = NULL;
	m_pSet = NULL;
	m_pStrOutput = NULL;
	m_pLongOutput = NULL;
	m_nExtMode = 0;
	m_lCurantiInvianti = 0;

	m_pStrIndirizzo = NULL;
	m_pStrTelefono = NULL;
	m_pStrEmail = NULL;

	//

	//m_lIDMedico = 0;

	m_strRicerca = "";
	m_strRicercaView = "";
}

CExtMedicoCuranteInviante::~CExtMedicoCuranteInviante()
{
}

BEGIN_MESSAGE_MAP(CExtMedicoCuranteInviante, CEdit)

	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()

END_MESSAGE_MAP()

void CExtMedicoCuranteInviante::SetParams(CWnd* pParentView, CBaseSet* pSet, CString* pStrOutput, long* pLongOutput, int nMaxLen, int nIndexMode, long lCurantiInvianti)
{
	m_pParentView = pParentView;
	m_pSet = pSet;
	m_pStrOutput = pStrOutput;
	m_pLongOutput = pLongOutput;

	//
	LimitText(nMaxLen);

	//
	switch(nIndexMode)
	{
		case 0:
		{
			m_nExtMode = ES_LOWERCASE;
			break;
		}
		case 1:
		{
			m_nExtMode = ES_UPPERCASE;
			break;
		}
		default:
		{
			m_nExtMode = 0L;
			break;
		}
	}

	long nVal = ::GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	nVal &= (~ES_LOWERCASE);
	nVal &= (~ES_UPPERCASE);
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, nVal | m_nExtMode);

	// Sandro 25/09/2013 // RAS 20130148 //
	ASSERT((lCurantiInvianti == MEDICI_CURANTI) || (lCurantiInvianti == MEDICI_INVIANTI));
	m_lCurantiInvianti = lCurantiInvianti;
}

void CExtMedicoCuranteInviante::SetStrings(CString* pStrIndirizzo, CString* pStrTelefono, CString* pStrEmail)
{
	m_pStrIndirizzo = pStrIndirizzo;
	m_pStrTelefono = pStrTelefono;
	m_pStrEmail = pStrEmail;
}

void CExtMedicoCuranteInviante::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != 9) //TAB
	{
		CString strValue = "";
		DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

		if (nChar >= 32 && nChar <= 255)
			strValue = CString((char)nChar, nRepCnt);

		if (m_nExtMode == ES_LOWERCASE)
			strValue.MakeLower();
		
		if (m_nExtMode == ES_UPPERCASE)
			strValue.MakeUpper();

		if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, strValue)))
			CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}

void CExtMedicoCuranteInviante::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, "")))
		CEdit::OnLButtonDown(nFlags, point);
}

void CExtMedicoCuranteInviante::OnRButtonDown(UINT nFlags, CPoint point)
{
}

BOOL CExtMedicoCuranteInviante::OpenComboMenu(BOOL& bIsOK, CString strValue)
{
	BOOL bResult;
	UINT nResult;

	CMediciCurantiInviantiDlg dlg(m_pParentView, m_lCurantiInvianti, BOOL_NOTMENU);
		
	nResult = dlg.DoModal();

	switch (nResult)
	{
		case IDOK:
		{
			bIsOK = TRUE;
			bResult = TRUE;

			m_strRicerca = dlg.m_sRicerca;
			m_strRicercaView = dlg.m_sRicercaView;

			if (m_pStrOutput)
			{
				CString strText = dlg.m_sTitolo;
				strText.Trim();
				// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
				if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
				{
					strText += " " + dlg.m_sNome;
					strText.Trim();
					strText += " " + dlg.m_sCognome;
					strText.Trim();
				}
				else
				{
					strText += " " + dlg.m_sCognome;
					strText.Trim();
					strText += " " + dlg.m_sNome;
					strText.Trim();
				}
				*m_pStrOutput = strText;
				//Mi salvo anche il contatore del medico per gli interfacciamenti, Sandro non cancellare!
				*m_pLongOutput = dlg.m_lContatore;
				//m_lIDMedico = dlg.m_lContatore;
			
				if (m_pSet->IsOpen())
				{
					m_pSet->SetFieldNull(m_pStrOutput, FALSE);
					m_pSet->SetFieldNull(m_pLongOutput, FALSE);
				}
			}

			if (m_pStrIndirizzo)
			{
				CString strText = dlg.m_sVia;
				strText.Trim();
				if ((!strText.IsEmpty()) && ((!dlg.m_sCitta.IsEmpty()) || (!dlg.m_sProvincia.IsEmpty())))
				{
					strText += " - " + dlg.m_sCitta;
					strText.Trim();
					if (!dlg.m_sProvincia.IsEmpty())
						strText += " ("+ dlg.m_sProvincia + ")";
				}

				if (strText.GetLength() >= 48)
					strText = strText.Left(48);

				*m_pStrIndirizzo = strText;
			
				if (m_pSet->IsOpen())
					m_pSet->SetFieldNull(m_pStrIndirizzo, FALSE);
			}

			if (m_pStrTelefono)
			{
				CString strText = dlg.m_sTelefono;
				strText.Trim();
				
				*m_pStrTelefono = strText;
			
				if (m_pSet->IsOpen())
					m_pSet->SetFieldNull(m_pStrTelefono, FALSE);
			}

			if (m_pStrEmail)
			{
				CString strText = dlg.m_sEmail;
				strText.Trim();
				
				*m_pStrEmail = strText;
			
				if (m_pSet->IsOpen())
					m_pSet->SetFieldNull(m_pStrEmail, FALSE);
			}

			break;
		}
		case IDCANCEL:
		{
			bIsOK	= FALSE;
			bResult = TRUE;
			break;
		}
		case IDC_EXIT:
		{
			bIsOK	= FALSE;
			bResult = FALSE;
			break;
		}
	}

	return bResult;
}

BOOL CExtMedicoCuranteInviante::OpenDialog(BOOL bUpdate, CString strValue)
{
	BOOL bOpened = FALSE;
	BOOL bIsOK = FALSE;

	if (bUpdate)
		if (m_pParentView)
			m_pParentView->UpdateData(TRUE);
	
	if (strValue.IsEmpty())
		GetWindowText(strValue);

	bOpened = OpenComboMenu(bIsOK, strValue);

	if (bOpened && bIsOK)
	{
		if (m_pParentView)
		{
			m_pParentView->UpdateData(FALSE);
			m_pParentView->PostMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE), (LPARAM)GetSafeHwnd());
		}
	}

	SetFocus();

	return bOpened;
}
