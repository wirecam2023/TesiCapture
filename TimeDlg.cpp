#include "stdafx.h"
#include "Endox.h"
#include "TimeDlg.h"

#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTimeDlg::CTimeDlg(CWnd* pParent)
	: CDialog(CTimeDlg::IDD, pParent)
{
	m_strRicercaView = "";
}

void CTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBOTIPO,			m_ctrlOperatore);
	DDX_Control(pDX, IDC_TIME_1,			m_ctrlTime1);
	DDX_Control(pDX, IDC_TIME_2,			m_ctrlTime2);
	DDX_Control(pDX, IDCANCEL,				m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK,					m_ctrlButtonOK);
	DDX_Control(pDX, IDC_STATIC_DA,			m_ctrlStaticFrom);
	DDX_Control(pDX, IDC_STATIC_OPERATOR,	m_ctrlStaticOperator);
	DDX_Control(pDX, IDC_STATIC_A,			m_ctrlStaticTo);
}

BEGIN_MESSAGE_MAP(CTimeDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBOTIPO, OnSelchangeComboTipo)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIME_1, OnTime1Change)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIME_2, OnTime2Change)
END_MESSAGE_MAP()

BOOL CTimeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlOperatore.InsertString(0, "=");
	m_ctrlOperatore.InsertString(1, "<");
	m_ctrlOperatore.InsertString(2, ">");
	m_ctrlOperatore.InsertString(3, theApp.GetMessageString(IDS_DIVERSO));
	m_ctrlOperatore.InsertString(4, theApp.GetMessageString(IDS_INTERNO));
	m_ctrlOperatore.InsertString(5, theApp.GetMessageString(IDS_ESTERNO));
	m_ctrlOperatore.SetCurSel(0);
	SetDlgMember();

	theApp.LocalizeDialog(this, CTimeDlg::IDD, "TimeDlg");

	return TRUE;
}

void CTimeDlg::OnSelchangeComboTipo() 
{
	SetDlgMember();
}

void CTimeDlg::OnTime1Change(NMHDR* pNMHDR, LRESULT* pResult)
{
	SetDlgMember();
	
	*pResult = 0;
}

void CTimeDlg::OnTime2Change(NMHDR* pNMHDR, LRESULT* pResult)
{
	SetDlgMember();	

	*pResult = 0;
}

void CTimeDlg::SetDlgMember()
{
	COleDateTime time1;
	COleDateTime time2;
	m_ctrlTime1.GetTime(time1);
	m_ctrlTime2.GetTime(time2);

	CString strTime1;
	CString strTime2;
	strTime1.Format("%02d:%02d", time1.GetHour(), time1.GetMinute());
	strTime2.Format("%02d:%02d", time2.GetHour(), time2.GetMinute());
	
	CCustomDate cTime1(0);
	cTime1.SetHour(time1.GetHour());
	cTime1.SetMinute(time1.GetMinute());

	CCustomDate cTime2(0);
	cTime2.SetHour(time2.GetHour());
	cTime2.SetMinute(time2.GetMinute());

	switch(m_ctrlOperatore.GetCurSel())
	{
		case 0: // =
		{
			m_strRicerca.Format("=%i", cTime1.GetDate());
			m_strRicercaView.Format("=%s", strTime1);
			m_ctrlTime2.EnableWindow(FALSE);

			break;
		}
		case 1: // <
		{
			m_strRicerca.Format("> 0 AND < %i", cTime1.GetDate());
			m_strRicercaView.Format("< %s", strTime1);
			m_ctrlTime2.EnableWindow(FALSE);

			break;
		}
		case 2: // >
		{
			m_strRicerca.Format("> %i", cTime1.GetDate());
			m_strRicercaView.Format("> %s", strTime1);
			m_ctrlTime2.EnableWindow(FALSE);

			break;
		}
		case 3: // diverso
		{
			m_strRicerca.Format("<> %i", cTime1.GetDate());
			m_strRicercaView.Format(theApp.GetMessageString(IDS_DIVERSO_DA) + " %s", strTime1);
			m_ctrlTime2.EnableWindow(FALSE);

			break;
		}
		case 4: // interno
		{
			m_strRicerca.Format(">=%i AND <=%i", cTime1.GetDate(), cTime2.GetDate());
			m_strRicercaView.Format("> %s AND < %s", strTime1, strTime2);
			m_ctrlTime2.EnableWindow(TRUE);

			break;
		}
		case 5: // esterno
		{
			m_strRicerca.Format("< %i AND > %i", cTime1.GetDate(), cTime2.GetDate());
			m_strRicercaView.Format("< %s AND > %s", strTime1, strTime2);
			m_ctrlTime2.EnableWindow(TRUE);

			break;
		}
	}

	UpdateData(FALSE);
}

void CTimeDlg::OnOK() 
{
	BOOL bError = FALSE;
	int nSel = m_ctrlOperatore.GetCurSel();
	COleDateTime time1, time2;

	m_ctrlTime1.GetTime(time1);
	m_ctrlTime2.GetTime(time2);
	
	switch(nSel)
	{
		case -1:
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DATEDLG_SELECT_OPERATOR));
			bError = TRUE;
			break;
		}

		case 4:
		{
			if (time1 == time2)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DATEDLG_ERR_OPERATOR));
				bError = TRUE;
			}
			break;
		}

		case 5:
		{
			if (time1 == time2)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DATEDLG_ERR_OPERATOR));
				bError = TRUE;
			}
			break;
		}
	}	

	if (!bError)
	{
		TRACE("Uscita CTimeDlg: m_strRicerca=\"" + m_strRicerca + "\" m_strRicercaView=\"" + m_strRicercaView + "\"\n");
		CDialog::OnOK();
	}
}