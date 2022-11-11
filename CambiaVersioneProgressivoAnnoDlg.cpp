#include "stdafx.h"
#include "Endox.h"
#include "CambiaVersioneProgressivoAnnoDlg.h"

#include "Common.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCambiaVersioneProgressivoAnnoDlg, CDialog)

CCambiaVersioneProgressivoAnnoDlg::CCambiaVersioneProgressivoAnnoDlg(CWnd* pParent, long lIDEsameOLD, long lIDEsameNEW, long lIDVersioneOLD, CString sProgressivoAnnoOLD)
	: CDialog(CCambiaVersioneProgressivoAnnoDlg::IDD, pParent)
{
	m_lIDEsameOLD = lIDEsameOLD;
	m_lIDEsameNEW = lIDEsameNEW;

	m_lIDVersioneOLD = lIDVersioneOLD;
	m_lIDVersioneNEW = GetIDVersione(m_lIDEsameNEW);

	m_sProgressivoAnnoOLD = sProgressivoAnnoOLD;
	m_sProgressivoAnnoNEW = GetContatoreAnnualeNoIncrement(m_lIDEsameNEW);

	m_lCountdown = theApp.m_lCountdownPartenza - 1;

	// --- //

	m_bFlagIDVersione = FALSE;
	m_bFlagProgressivoAnno = FALSE;
}

CCambiaVersioneProgressivoAnnoDlg::~CCambiaVersioneProgressivoAnnoDlg()
{
}

BEGIN_MESSAGE_MAP(CCambiaVersioneProgressivoAnnoDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_CONFERMA, OnBnClickedBtnConferma)

	ON_WM_TIMER()

END_MESSAGE_MAP()

void CCambiaVersioneProgressivoAnnoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_CONFERMA, m_ctrlButtonConferma);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlCheck1);
	DDX_Control(pDX, IDC_CHECK2, m_ctrlCheck2);
	DDX_Control(pDX, IDC_STATIC_LABEL1, m_ctrlStaticLabel1);
	DDX_Control(pDX, IDC_STATIC_LABEL2, m_ctrlStaticLabel2);
}

void CCambiaVersioneProgressivoAnnoDlg::OnCancel()
{
}

BOOL CCambiaVersioneProgressivoAnnoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlStaticLabel1.SetFont(&theApp.m_fontBold);
	m_ctrlButtonConferma.SetFont(&theApp.m_fontBold);

	//

	CString strTeeemp;
	int nVisibles = 0;

	// TITOLO DELLA FINESTRA //

	strTeeemp.Format(theApp.GetMessageString(IDS_CAMBIATO_TIPO_ESAME), CTipoEsameSet().GetDescrizione(m_lIDEsameOLD).Trim(), CTipoEsameSet().GetDescrizione(m_lIDEsameNEW).Trim());
	m_ctrlStaticLabel1.SetWindowText(strTeeemp);

	// PRIMO FLAG // PROGRESSIVOANNO //

	if (ProgressiviDifferenti(m_sProgressivoAnnoOLD, m_sProgressivoAnnoNEW))
	{
		strTeeemp.Format(theApp.GetMessageString(IDS_CAMBIATO_PROGRESSIVO_ANNO), m_sProgressivoAnnoOLD, m_sProgressivoAnnoNEW);
		m_ctrlCheck1.SetCheck(BST_CHECKED);
		m_ctrlCheck1.SetWindowText(strTeeemp);
		nVisibles++;
	}
	else
	{
		m_ctrlCheck1.ShowWindow(SW_HIDE);
	}

	// SECONDO FLAG // IDVERSIONE //

	if (m_lIDVersioneOLD != m_lIDVersioneNEW)
	{
		strTeeemp.Format(theApp.GetMessageString(IDS_CAMBIATO_VERSIONE), CTipoEsameSet().GetDescrizione(m_lIDEsameNEW).Trim());
		m_ctrlCheck2.SetCheck(BST_CHECKED);
		m_ctrlCheck2.SetWindowText(strTeeemp);
		nVisibles++;
	}
	else
	{
		m_ctrlCheck2.ShowWindow(SW_HIDE);
	}

	// --- //

	if (nVisibles == 0)
		CDialog::OnOK();
	else
		SetTimer(ATTIVA_TASTO_TIMER, 1000, NULL);

	// --- //

	theApp.LocalizeDialog(this, CCambiaVersioneProgressivoAnnoDlg::IDD, "CambiaVersioneProgressivoAnnoDlg");
	return TRUE;
}

void CCambiaVersioneProgressivoAnnoDlg::OnOK()
{
}

void CCambiaVersioneProgressivoAnnoDlg::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == ATTIVA_TASTO_TIMER)
	{
		if (m_lCountdown > 0)
		{
			CString strTempCountdown;
			strTempCountdown.Format("%li", m_lCountdown);
			m_ctrlButtonConferma.SetWindowText(strTempCountdown);

			m_lCountdown--;
		}
		else
		{
			KillTimer(ATTIVA_TASTO_TIMER);

			m_ctrlButtonConferma.SetWindowText(theApp.GetMessageString(IDS_CONFERMA));
			m_ctrlButtonConferma.EnableWindow(TRUE);
		}
	}
}

void CCambiaVersioneProgressivoAnnoDlg::OnBnClickedBtnConferma()
{
	if (m_ctrlButtonConferma.IsWindowEnabled())
	{
		m_bFlagIDVersione = (m_ctrlCheck2.GetCheck() == BST_CHECKED);
		m_bFlagProgressivoAnno = (m_ctrlCheck1.GetCheck() == BST_CHECKED);

		CDialog::OnOK();
	}
}

long CCambiaVersioneProgressivoAnnoDlg::GetNewIDVersione()
{
	long lReturn = m_lIDVersioneOLD;

	if (m_bFlagIDVersione)
		lReturn = m_lIDVersioneNEW;

	return lReturn;
}

CString CCambiaVersioneProgressivoAnnoDlg::GetNewProgressivoAnno()
{
	CString strReturn = m_sProgressivoAnnoOLD;

	if (m_bFlagProgressivoAnno)
		strReturn = GetContatoreAnnuale(m_lIDEsameNEW);

	return strReturn;
}

BOOL CCambiaVersioneProgressivoAnnoDlg::ProgressiviDifferenti(CString sProgressivo1, CString sProgressivo2)
{
	BOOL bReturn = TRUE;

	int nFindInizP1 = sProgressivo1.Find(" / ") + 3;
	int nFindFineP1 = sProgressivo1.Find(" / ", nFindInizP1);

	int nFindInizP2 = sProgressivo2.Find(" / ") + 3;
	int nFindFineP2 = sProgressivo2.Find(" / ", nFindInizP2);

	if ((nFindFineP1 > nFindInizP1) && (nFindFineP2 > nFindInizP2))
	{
		CString s1 = sProgressivo1.Mid(nFindInizP1, nFindFineP1 - nFindInizP1);
		CString s2 = sProgressivo2.Mid(nFindInizP2, nFindFineP2 - nFindInizP2);

		if (s1.CompareNoCase(s2) == 0)
			bReturn = FALSE;
	}

	return bReturn;
}