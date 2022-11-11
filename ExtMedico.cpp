#include "stdafx.h"
#include "Endox.h"
#include "ExtMedico.h"

#include "OperatoriDlg.h"
#include "BaseSet.h"
#include "Define.h"
#include "VistaUtentiSet.h"
#include "MediciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CExtMedico, CEdit)

CExtMedico::CExtMedico()
	:CEdit()
{
	m_pParentView	= NULL;
	m_pEsamiView	= NULL;
	m_pSet			= NULL;
	m_pStrOutput	= NULL;
	m_pStrOther[0]  = NULL;
	m_pStrOther[1]  = NULL;
	m_nMaxLen		= 0;
	m_nExtMode 		= 0;
	m_strTitle		= "";	
	m_bUpdateRecord = TRUE;	
}

CExtMedico::~CExtMedico()
{
}

BEGIN_MESSAGE_MAP(CExtMedico, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

CString CExtMedico::GetCurrentUtentiMedici()
{
	CString sReturn = "";

	CString sFilter;
	long lIDUtenti = 0;

	CVistaUtentiSet set;
	set.SetSortRecord("USERNAME");
	sFilter.Format("USERNAME = '%s'", theApp.m_sUtenteLoggato);
	set.SetOpenFilter(sFilter);

	if (set.OpenRecordset("COperatoriDlg::GetCurrentUtentiMedici"))
	{
		if (!set.IsEOF())
		{
			lIDUtenti = set.m_lId;
		}
		set.CloseRecordset("COperatoriDlg::RiempiComboUsers");
	}

	if (lIDUtenti > 0)
	{
		CMediciSet setMed;		
		sFilter.Format("idutenteendox = %li", lIDUtenti);
		setMed.SetOpenFilter(sFilter);


		setMed.SetSortRecord("Cognome, Nome");
		if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
			setMed.SetSortRecord("Nome, Cognome");
		
		if (setMed.OpenRecordset("COperatoriDlg::RiempiListaMedici"))
		{
			if (!setMed.IsEOF())
			{	
				// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
				if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
					sReturn = setMed.m_sTitolo + " " + setMed.m_sNome + " " + setMed.m_sCognome;
				else
					sReturn = setMed.m_sTitolo + " " + setMed.m_sCognome + " " + setMed.m_sNome;
				m_strRicercaView = sReturn;

				CString sID;
				sID.Format("%i", setMed.m_lContatore);
				m_strRicerca = sID;
			}
			setMed.CloseRecordset("COperatoriDlg::RiempiListaMedici");
		}
	}
	return sReturn;
}

void CExtMedico::SetParam(CWnd* pParentForm, CBaseSet* pSet, CString* pStrParent, int nMaxLen, CString strTitle)
{	
	m_pParentView = pParentForm;
	m_pSet		  = pSet;
	m_pStrOutput  = pStrParent;
	m_nMaxLen	  = nMaxLen;
	m_strTitle	  = strTitle;

	LimitText(m_nMaxLen);
}

void CExtMedico::SetParam(CEsamiView* pEsamiView, CString* strSede, CString* strTelefono)
{	
	m_pEsamiView	= pEsamiView;
	m_pStrOther[0]  = strSede;
	m_pStrOther[1]  = strTelefono;
}

void CExtMedico::SetParam(CWnd* pParentForm, CBaseSet* pSet)
{
	m_pParentView = pParentForm;
	m_pSet		  = pSet;
	m_bUpdateRecord = FALSE;
}

void CExtMedico::SetParam(int nIndexMode)
{	
	switch (nIndexMode)
	{
		case 0: 
			m_nExtMode = ES_LOWERCASE;
			break;
		case 1: 
			m_nExtMode = ES_UPPERCASE;
			break;
		case 2: 
		default:
			m_nExtMode = 0L;
			break;
	}

	long nVal = ::GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	nVal &= (~ES_LOWERCASE);
	nVal &= (~ES_UPPERCASE);
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, nVal|m_nExtMode);

	LimitText(m_nMaxLen);
}

BOOL CExtMedico::OpenDialog(BOOL bUpdate, CString strValue)
{	
	BOOL	bOpened;
	BOOL	bIsOK;

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
			WPARAM wParam = MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE);
			
			m_pParentView->UpdateData(FALSE);
			m_pParentView->PostMessage(WM_COMMAND, (WPARAM)wParam, (LPARAM)GetSafeHwnd());
		}
	}

	SetFocus();

	return bOpened;
}

BOOL CExtMedico::OpenComboMenu(BOOL& bIsOK, CString strValue)
{
	BOOL bResult;
	UINT nResult;

	
	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	CBaseSet* auxBaseSet = this->m_pSet;
	CEsamiSet* auxEsamiSet = (CEsamiSet*)auxBaseSet->GetRecordset();
	

	COperatoriDlg dlg(m_pEsamiView, BOOL_NOTMENU, auxEsamiSet->m_lMedico);	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
		
	nResult = dlg.DoModal();

	switch(nResult)
	{
		case IDOK:
		{
			bIsOK	= TRUE;
			bResult = TRUE;

			m_strRicerca = dlg.m_strRicerca;
			m_strRicercaView = dlg.m_strRicercaView;

			if (dlg.m_bCleanContent)
			{
				m_strRicerca = "-1";
				m_strRicercaView = "#NULL#";
				break;
			}

			if (m_pStrOutput)
			{
				// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
				CString strText;
				if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
					strText = dlg.m_sTitolo + " " + dlg.m_sNome + " " + dlg.m_sCognome;
				else
					strText = dlg.m_sTitolo + " " + dlg.m_sCognome + " " + dlg.m_sNome;

				strText.TrimLeft();
				strText.TrimRight();

				*m_pStrOutput = strText;
			
				if (m_pSet->IsOpen())
					m_pSet->SetFieldNull(m_pStrOutput, FALSE);
			}

			if (m_pStrOther[0])
			{
				CString strText = dlg.m_sVia + "\r\n"+ dlg.m_sCitta + " ("+ dlg.m_sProvincia + ")";

				strText.TrimLeft();
				strText.TrimRight();

				if (strText.GetLength() >= 48)
					strText = strText.Left(48);
				
				*m_pStrOther[0] = strText;
			
				if (m_pSet->IsOpen())
					m_pSet->SetFieldNull(m_pStrOther[0], FALSE);
			}

			if (m_pStrOther[1])
			{
				CString strText = dlg.m_sTelefono;

				strText.TrimLeft();
				strText.TrimRight();
				
				*m_pStrOther[1] = strText;
			
				if (m_pSet->IsOpen())
					m_pSet->SetFieldNull(m_pStrOther[1], FALSE);
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

/////////////////////////////////////////////////////////////////////////////
// CExtMedico message handlers

void CExtMedico::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, "")))
		CEdit::OnLButtonDown(nFlags, point);
}

void CExtMedico::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void CExtMedico::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
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