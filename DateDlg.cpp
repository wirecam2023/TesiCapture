#include "stdafx.h"
#include "Endox.h"
#include "DateDlg.h"

#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDateDlg::CDateDlg(CWnd* pParent)
	: CDialog(CDateDlg::IDD, pParent)
{
	m_strRicercaView = "";
	m_iRicercaOutputMode = 0;
}

void CDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBOTIPO, m_ctrlOperatore);
	DDX_Control(pDX, IDC_DATE2, m_ctrlDate2);
	DDX_Control(pDX, IDC_DATE1, m_ctrlDate1);
	DDX_Control(pDX, IDCANCEL,            m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK,                m_ctrlButtonOK);
	DDX_Control(pDX, IDC_STATIC_DA,       m_ctrlStaticFrom);
	DDX_Control(pDX, IDC_STATIC_OPERATOR, m_ctrlStaticOperator);
	DDX_Control(pDX, IDC_STATIC_A,        m_ctrlStaticTo);
}

BEGIN_MESSAGE_MAP(CDateDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBOTIPO, OnSelchangeCombotipo)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE1, OnDate1Change)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE2, OnDate2Change)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateDlg message handlers

BOOL CDateDlg::OnInitDialog() 
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

	theApp.LocalizeDialog(this, CDateDlg::IDD, "DateDlg");

	return TRUE;
}

void CDateDlg::OnSelchangeCombotipo() 
{
	SetDlgMember();
}

void CDateDlg::OnDate1Change(NMHDR* pNMHDR, LRESULT* pResult)
{
	SetDlgMember();
	
	*pResult = 0;
}

void CDateDlg::OnDate2Change(NMHDR* pNMHDR, LRESULT* pResult)
{
	SetDlgMember();	

	*pResult = 0;
}
void CDateDlg::SetRicercaOutputMode(int nModalita)
{
	m_iRicercaOutputMode = nModalita;
}
void CDateDlg::SetDlgMember()
{
	COleDateTime time1, time2;
	CString strData1, strData2;
	LONG nData1, nData2;
	int nSel;

	m_ctrlDate1.GetTime(time1);
	m_ctrlDate2.GetTime(time2);
	
	strData1.Format("%02d/%02d/%04d", time1.GetDay(), time1.GetMonth(), time1.GetYear());
	strData2.Format("%02d/%02d/%04d", time2.GetDay(), time2.GetMonth(), time2.GetYear());
	
	nSel = m_ctrlOperatore.GetCurSel();

	switch (nSel)
	{
		case 0: // =
		{
			CCustomDate cData1(time1.GetYear(), time1.GetMonth(), time1.GetDay(), 0, 0, 0);
			CCustomDate cData2(time1.GetYear(), time1.GetMonth(), time1.GetDay(), 0, 23, 59);

			if (m_iRicercaOutputMode == DATA_ORA_FULL)
				m_strRicerca.Format(">='%s' AND <='%s'", cData1.GetDate("%Y%m%d%H%M%S"), cData2.GetDate("%Y%m%d%H%M%S"));
			else
				m_strRicerca.Format(">=%i AND <=%i", cData1.GetDate(), cData2.GetDate());

			m_strRicercaView.Format("=%s", strData1);
			m_ctrlDate2.EnableWindow(FALSE);
			break;
		}
		
		case 1: // <
		{
			CCustomDate cData1(time1.GetYear(), time1.GetMonth(), time1.GetDay(), 0, 23, 59);
			nData1 = cData1.GetDate();
	
			if (m_iRicercaOutputMode == DATA_ORA_FULL)
				m_strRicerca.Format("> '1900010100000' AND < '%s'", cData1.GetDate("%Y%m%d%H%M%S"));
			else
				m_strRicercaView.Format("< %s", strData1);
			
			m_ctrlDate2.EnableWindow(FALSE);
			break;
		}

		case 2: // >
		{
			CCustomDate cData1(time1.GetYear(), time1.GetMonth(), time1.GetDay(), 0, 0, 0);
			nData1 = cData1.GetDate();
	
			if (m_iRicercaOutputMode == DATA_ORA_FULL)
				m_strRicerca.Format("> '%s'", cData1.GetDate("%Y%m%d%H%M%S"));
			else
				m_strRicerca.Format("> %i", nData1);

			m_strRicercaView.Format("> %s", strData1);
			m_ctrlDate2.EnableWindow(FALSE);
			break;
		}
		
		case 3: // diverso
		{
			CCustomDate cData1(time1.GetYear(), time1.GetMonth(), time1.GetDay(), 0, 0, 0);
			CCustomDate cData2(time1.GetYear(), time1.GetMonth(), time1.GetDay(), 0, 23, 59);
			nData1 = cData1.GetDate();
			nData2 = cData2.GetDate();
	
//			m_strRicerca.Format("<> %i", nData1); // Sandro 16/07/2003
			if (m_iRicercaOutputMode == DATA_ORA_FULL)
				m_strRicerca.Format("< '%s' AND > '%s'", cData1.GetDate("%Y%m%d%H%M%S"), cData2.GetDate("%Y%m%d%H%M%S"));
			else
				m_strRicerca.Format("< %i AND > %i", nData1, nData2);

			m_strRicercaView.Format(theApp.GetMessageString(IDS_DIVERSO_DA) + " %s", strData1);
			m_ctrlDate2.EnableWindow(FALSE);
			break;
		}

		case 4: // interno
		{
			CCustomDate cData1(time1.GetYear(), time1.GetMonth(), time1.GetDay(), 0, 0, 0);
			CCustomDate cData2(time2.GetYear(), time2.GetMonth(), time2.GetDay(), 0, 23, 59);
			nData1 = min(cData1.GetDate(), cData2.GetDate());
			nData2 = max(cData1.GetDate(), cData2.GetDate());
	
			if (m_iRicercaOutputMode == DATA_ORA_FULL)
				m_strRicerca.Format(">='%s' AND <='%s'", cData1.GetDate("%Y%m%d%H%M%S"), cData2.GetDate("%Y%m%d%H%M%S"));
			else
				m_strRicerca.Format(">=%i AND <=%i", nData1, nData2);

			m_strRicercaView.Format("> %s AND < %s", strData1, strData2);
			m_ctrlDate2.EnableWindow(TRUE);
			break;
		}
		
		case 5: // esterno
		{
			CCustomDate cData1(time1.GetYear(), time1.GetMonth(), time1.GetDay(), 0, 0, 0);
			CCustomDate cData2(time2.GetYear(), time2.GetMonth(), time2.GetDay(), 0, 23, 59);
			nData1 = min(cData1.GetDate(), cData2.GetDate());
			nData2 = max(cData1.GetDate(), cData2.GetDate());
	
			if (m_iRicercaOutputMode == DATA_ORA_FULL)
				m_strRicerca.Format("< '%s' AND > '%s'", cData1.GetDate("%Y%m%d%H%M%S"), cData2.GetDate("%Y%m%d%H%M%S"));
			else
				m_strRicerca.Format("< %i AND > %i", nData1, nData2);

			m_strRicercaView.Format("< %s AND > %s", strData1, strData2);
			m_ctrlDate2.EnableWindow(TRUE);
			break;
		}
	}

	UpdateData(FALSE);
}

void CDateDlg::OnOK() 
{
	BOOL bError = FALSE;
	int nSel = m_ctrlOperatore.GetCurSel();
	COleDateTime time1, time2;

	m_ctrlDate1.GetTime(time1);
	m_ctrlDate2.GetTime(time2);
	
	switch (nSel)
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
		TRACE("Uscita CDateDlg: m_strRicerca=\"" + m_strRicerca + "\" m_strRicercaView=\"" + m_strRicercaView + "\"\n");
		CDialog::OnOK();
	}
}