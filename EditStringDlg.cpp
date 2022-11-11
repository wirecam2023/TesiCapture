#include "stdafx.h"
#include "Endox.h"
#include "EditStringDlg.h"

#include <cctype>

#define CONTROLLO_NESSUNO 0
#define CONTROLLO_NUMEROINTERO 1
#define CONTROLLO_NUMEROVIRGOL 2

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEditStringDlg, CDialog)

CEditStringDlg::CEditStringDlg(CWnd* pParent, const CString &strTitle, const CString &sValue)
	: CDialog(CEditStringDlg::IDD, pParent)
{
	m_bRangeMin = FALSE;
	m_bRangeMax = FALSE;

	m_lRangeValMin = 0;
	m_lRangeValMax = 0;

	m_lfRangeValMin = 0;
	m_lfRangeValMax = 0;

	m_pEsamiView = NULL;

	if (strTitle.Left(4).CompareNoCase("numi") == 0)
	{
		m_iTipoInput = CONTROLLO_NUMEROINTERO;

		int iUnderscore1 = strTitle.Find('_');
		int iUnderscore2 = strTitle.Find('_', iUnderscore1 + 1);
		int iDuepunti = strTitle.Find(':');

		if ((iUnderscore1 > 0) && (iUnderscore2 > 0) && (iUnderscore1 < iDuepunti) && (iUnderscore2 < iDuepunti))
		{
			if (iUnderscore2 - iUnderscore1 > 1)
			{
				// valore minimo //

				m_bRangeMin = TRUE;

				CString sTemp = strTitle.Mid(iUnderscore1 + 1, iUnderscore2 - (iUnderscore1 + 1));
				m_lRangeValMin = atol(sTemp);
			}

			if (iDuepunti - iUnderscore2 > 1)
			{
				// valore massimo //

				m_bRangeMax = TRUE;

				CString sTemp = strTitle.Mid(iUnderscore2 + 1, iDuepunti - (iUnderscore2 + 1));
				m_lRangeValMax = atol(sTemp);
			}

			if (m_bRangeMin && m_bRangeMax && (m_lRangeValMin > m_lRangeValMax))
			{
				// controllo il range minimo-massimo //

				long lTemp = m_lRangeValMin;
				m_lRangeValMin = m_lRangeValMax;
				m_lRangeValMax = lTemp;
			}
		}

		m_sTitle = strTitle.Mid(max(4, iDuepunti + 2));

		if (m_bRangeMin && m_bRangeMax)
			m_sTitle.AppendFormat(" " + theApp.GetMessageString(IDS_RANGEL_MIN_MAX), m_lRangeValMin, m_lRangeValMax);
		else if (m_bRangeMin)
			m_sTitle.AppendFormat(" " + theApp.GetMessageString(IDS_RANGEL_MIN), m_lRangeValMin);
		else if (m_bRangeMax)
			m_sTitle.AppendFormat(" " + theApp.GetMessageString(IDS_RANGEL_MAX), m_lRangeValMax);
	}
	else if (strTitle.Left(4).CompareNoCase("numv") == 0)
	{
		m_iTipoInput = CONTROLLO_NUMEROVIRGOL;

		int iUnderscore1 = strTitle.Find('_');
		int iUnderscore2 = strTitle.Find('_', iUnderscore1 + 1);
		int iDuepunti = strTitle.Find(':');

		if ((iUnderscore1 > 0) && (iUnderscore2 > 0) && (iUnderscore1 < iDuepunti) && (iUnderscore2 < iDuepunti))
		{
			if (iUnderscore2 - iUnderscore1 > 1)
			{
				// valore minimo //

				m_bRangeMin = TRUE;

				CString sTemp = strTitle.Mid(iUnderscore1 + 1, iUnderscore2 - (iUnderscore1 + 1));
				sTemp.Replace(',', '.');
				m_lfRangeValMin = atof(sTemp);
			}

			if (iDuepunti - iUnderscore2 > 1)
			{
				// valore massimo //

				m_bRangeMax = TRUE;

				CString sTemp = strTitle.Mid(iUnderscore2 + 1, iDuepunti - (iUnderscore2 + 1));
				sTemp.Replace(',', '.');
				m_lfRangeValMax = atof(sTemp);
			}

			if (m_bRangeMin && m_bRangeMax && (m_lfRangeValMin > m_lfRangeValMax))
			{
				// controllo il range minimo-massimo //

				double lfTemp = m_lfRangeValMin;
				m_lfRangeValMin = m_lfRangeValMax;
				m_lfRangeValMax = lfTemp;
			}
		}

		m_sTitle = strTitle.Mid(max(4, iDuepunti + 2));

		if (m_bRangeMin && m_bRangeMax)
			m_sTitle.AppendFormat(" " + theApp.GetMessageString(IDS_RANGEF_MIN_MAX), m_lfRangeValMin, m_lfRangeValMax);
		else if (m_bRangeMin)
			m_sTitle.AppendFormat(" " + theApp.GetMessageString(IDS_RANGEF_MIN), m_lfRangeValMin);
		else if (m_bRangeMax)
			m_sTitle.AppendFormat(" " + theApp.GetMessageString(IDS_RANGEF_MAX), m_lfRangeValMax);
	}
	else
	{
		m_iTipoInput = CONTROLLO_NESSUNO;
		m_sTitle = strTitle;
	}

	m_sValue = sValue;
}

CEditStringDlg::CEditStringDlg(CWnd* pParent, UINT idTitle, const CString &sValue)
	: CDialog(CEditStringDlg::IDD, pParent)
{
	m_sTitle = theApp.GetMessageString(idTitle);
	m_sValue = sValue;

	m_iTipoInput = CONTROLLO_NESSUNO;

	m_bRangeMin = FALSE;
	m_bRangeMax = FALSE;

	m_lRangeValMin = 0;
	m_lRangeValMax = 0;

	m_lfRangeValMin = 0;
	m_lfRangeValMax = 0;
}

CEditStringDlg::~CEditStringDlg()
{
}

void CEditStringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_BTN_IMM, m_ctrlButtonImm);

}

BEGIN_MESSAGE_MAP(CEditStringDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CEditStringDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_VALUE, &CEditStringDlg::OnEnChangeEditValue)
	ON_BN_CLICKED(IDC_BTN_IMM, &CEditStringDlg::OnBnClickedBtnImm)
END_MESSAGE_MAP()

BOOL CEditStringDlg::OnInitDialog()
{   
	BOOL bReturn = CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CEditStringDlg::IDD, "EditStringDlg");

	SetWindowText(m_sTitle);
	SetDlgItemText(IDC_EDIT_VALUE, m_sValue);

	// Sandro 03/06/2013 // Attivo il tasto "Conferma" solo se c'è qualcosa di scritto //
	m_ctrlButtonOK.EnableWindow(!m_sValue.IsEmpty());
	GetDlgItem(IDC_BTN_IMM)->EnableWindow(m_pEsamiView != NULL);
	//
	return bReturn;
}

void CEditStringDlg::OnBnClickedOk()
{
	BOOL bError = FALSE;

	GetDlgItemText(IDC_EDIT_VALUE, m_sValue);

	switch (m_iTipoInput)
	{
		case CONTROLLO_NUMEROINTERO:
		{
			for (int i = 0; i < m_sValue.GetLength(); i++)
			{
				if (!std::isdigit(m_sValue[i]))
				{
					bError = TRUE;
					theApp.AfxMessageBoxEndo(IDS_STRINGA_NONNUMINT);
					break;
				}
			}

			if (!bError)
			{
				long lTemp = atol(m_sValue);

				if (m_bRangeMin && (lTemp < m_lRangeValMin))
					bError = (theApp.AfxMessageBoxEndo(IDS_STRINGA_VALORETROPPOBASSO, MB_YESNO | MB_ICONEXCLAMATION) != IDYES);
			}

			if (!bError)
			{
				long lTemp = atol(m_sValue);

				if (m_bRangeMax && (lTemp > m_lRangeValMax))
					bError = (theApp.AfxMessageBoxEndo(IDS_STRINGA_VALORETROPPOALTO, MB_YESNO | MB_ICONEXCLAMATION) != IDYES);
			}

			break;
		}
		case CONTROLLO_NUMEROVIRGOL:
		{
			for (int i = 0; i < m_sValue.GetLength(); i++)
			{
				if (!std::isdigit(m_sValue[i]) && (m_sValue[i] != '.') && (m_sValue[i] != ','))
				{
					bError = TRUE;
					theApp.AfxMessageBoxEndo(IDS_STRINGA_NONNUMVIR);
					break;
				}
			}

			if (!bError)
			{
				CString sTemp = m_sValue;
				sTemp.Replace(',', '.');
				double lfTemp = atof(sTemp);

				if (m_bRangeMin && (lfTemp < m_lfRangeValMin))
					bError = (theApp.AfxMessageBoxEndo(IDS_STRINGA_VALORETROPPOBASSO, MB_YESNO | MB_ICONEXCLAMATION) != IDYES);
			}

			if (!bError)
			{
				CString sTemp = m_sValue;
				sTemp.Replace(',', '.');
				double lfTemp = atof(sTemp);

				if (m_bRangeMax && (lfTemp > m_lfRangeValMax))
					bError = (theApp.AfxMessageBoxEndo(IDS_STRINGA_VALORETROPPOALTO, MB_YESNO | MB_ICONEXCLAMATION) != IDYES);
			}

			break;
		}
		default:
		{
			break;
		}
	}

	if (!bError)
		OnOK();
}

CString CEditStringDlg::GetValue()
{
	return m_sValue;
}

void CEditStringDlg::OnEnChangeEditValue()
{
	// Sandro 03/06/2013 // Attivo il tasto "Conferma" solo se c'è qualcosa di scritto //

	CString sTemp;
	GetDlgItemText(IDC_EDIT_VALUE, sTemp);
	sTemp.Trim();

	m_ctrlButtonOK.EnableWindow(!sTemp.IsEmpty());
}
//Julio 15/08/2018 used for CImgSimpleDlg2
BOOL CEditStringDlg::SetEsamiView(CEsamiView* pEsamiView)
{	
	m_pEsamiView = pEsamiView;
	return TRUE;
}

void CEditStringDlg::OnBnClickedBtnImm()
{
	CRect rect;
	GetWindowRect(&rect);
	int x = rect.TopLeft().x;
	int y = rect.TopLeft().y;

	//MoveWindow(x, 50, rect.Width(), rect.Height(), TRUE);
	//Invalidate();
	//UpdateWindow();

	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#1 - dual screen)
	// TODO: Ver se precisa colocar aqui também
	if (m_pEsamiView != NULL)
	{
		CImageSimple2Dlg* pDlgImageSimple2 = new CImageSimple2Dlg(this, m_pEsamiView, TRUE);
		if (pDlgImageSimple2->Create(IDD_IMAGE_SIMPLE2, this))
			pDlgImageSimple2->ShowWindow(SW_SHOWNORMAL);
		else
			delete pDlgImageSimple2;
	}	
}
