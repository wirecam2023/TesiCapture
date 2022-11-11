#include "stdafx.h"
#include "Endox.h"
#include "TerapiaDlg.h"

#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTerapiaDlg::CTerapiaDlg(CWnd* pParent, CBaseSet* pSet, CString* pStrParent, CString strInit)
	: CDialog(CTerapiaDlg::IDD, pParent)
{
	m_pSet		 = pSet;
	m_pStrOutput = pStrParent;

	m_bOrPressed = FALSE;
}

CTerapiaDlg::~CTerapiaDlg()
{
}

void CTerapiaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//DDX_Control(pDX, IDC_RICERCA,	m_ctrlRicerca);
	//DDX_Text(pDX, IDC_RICERCA,		m_strRicerca);
	//DDX_Text(pDX, IDC_OUTPUT,	m_strOut);

	DDX_Control(pDX, IDC_LISTA1,	m_ctrLista[0]);
	DDX_Control(pDX, IDC_LISTA2,	m_ctrLista[1]);
	DDX_Control(pDX, IDC_LISTA3,	m_ctrLista[2]);

	if (m_pStrOutput)
		DDX_Text(pDX, IDC_OUTPUT,	*m_pStrOutput);
}

BEGIN_MESSAGE_MAP(CTerapiaDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD,	   OnAdd)
	ON_BN_CLICKED(IDC_RESET,   OnReset)
	ON_BN_CLICKED(IDC_BTN_OR,  OnBtnOr)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////
BOOL CTerapiaDlg::SelectLista()
{
	int		nPos;
	CString strSelect[3], strTerapia;
	BOOL	bSelect  [3];
	BOOL	bResult = FALSE;
	
	for(int i = 0; i < 3; i++)
	{
		nPos		= m_ctrLista[i].GetCurSel();
		bSelect[i]	= (nPos != LB_ERR);

		strSelect[i] = "";

		if (bSelect[i])
		{
			m_ctrLista[i].GetText(nPos, strSelect[i]);
		}
	}

	bResult = bSelect[0];

	if (bResult && m_pStrOutput)
	{
		strTerapia = strSelect[0] + " " + strSelect[1] + " " + strSelect[2];

		if (m_bRicercaAttivata)
		{
			if (m_pStrOutput->Find(strTerapia) < 0)
			{				
				if (m_bOrPressed)
				{
					*m_pStrOutput += strTerapia;
					GetDlgItem(IDC_BTN_OR)->EnableWindow(TRUE);
					m_bOrPressed = FALSE;
				}
				else
				{
					if ((*m_pStrOutput).Find(" OR ") > 0)
						*m_pStrOutput = "(" + *m_pStrOutput + ")";

					if (!m_pStrOutput->IsEmpty())
						*m_pStrOutput += " AND ";

					*m_pStrOutput += strTerapia;
					GetDlgItem(IDC_BTN_OR)->EnableWindow(TRUE);
				}
			}
		}
		else
		{
			if (!m_pStrOutput->IsEmpty())
			{
				if (m_pStrOutput->Find(strTerapia) < 0)
				{
					*m_pStrOutput += theApp.m_sTestiConcatenatiSeparatore;
					*m_pStrOutput += strTerapia;
				}
			}
			else
			{
				*m_pStrOutput = strTerapia;
			}
		}
		
		if (m_pSet->IsOpen())
			m_pSet->SetFieldNull(m_pStrOutput, FALSE);
	}

	return bResult;
}

void CTerapiaDlg::OnBtnOr()
{
	if (m_pStrOutput->Find(" AND ") > 0)
		*m_pStrOutput = "(" + *m_pStrOutput + ")";

	*m_pStrOutput += " OR ";
	m_bOrPressed = TRUE;

	GetDlgItem(IDC_BTN_OR)->EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CTerapiaDlg::OnOK()
{
	UpdateData(TRUE);

	if (m_bOrPressed)
	{
		*m_pStrOutput = m_pStrOutput->Left(m_pStrOutput->GetLength() - 3);
		m_pStrOutput->TrimRight();
		
		if (m_pStrOutput->Right(1) == ")")
			*m_pStrOutput = m_pStrOutput->Mid(1, m_pStrOutput->GetLength() - 2);
	}
	
	UpdateData(FALSE);

	CDialog::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CTerapiaDlg message handlers

/////////////////////////////////////////////////////////
BOOL CTerapiaDlg::OnInitDialog ()
{   
	CDialog::OnInitDialog ();
	
	m_ctrLista[0].SetParam(this);
	m_ctrLista[0].SetParamSet(CMB_ESA_TERAPIACONSIGLIATA, TRUE);
	m_ctrLista[0].SetCurSel(0);

	m_ctrLista[1].SetParam(this);
	m_ctrLista[1].SetParamSet(CMB_ESA_TERAPIACONSIGLIATADOSAGG, TRUE);
	m_ctrLista[1].SetCurSel(0);

	m_ctrLista[2].SetParam(this);
	m_ctrLista[2].SetParamSet(CMB_ESA_TERAPIACONSIGLIATADURATA, TRUE);
	m_ctrLista[2].SetCurSel(0);

	m_bRicercaAttivata = theApp.m_nProgramMode & FILTER_RECORD_ESAMI;

	if (m_pStrOutput->IsEmpty())
		GetDlgItem(IDC_BTN_OR)->EnableWindow(FALSE);

	if (!m_bRicercaAttivata)
		GetDlgItem(IDC_BTN_OR)->ShowWindow(SW_HIDE);

	return TRUE;
}

/////////////////////////////////////////////////////////
void CTerapiaDlg::OnAdd()
{
	UpdateData(TRUE);
	
	SelectLista();

	UpdateData(FALSE);
}

/////////////////////////////////////////////////////////
void CTerapiaDlg::OnReset()
{
	UpdateData(TRUE);
	
	*m_pStrOutput = "";
	//m_strOut = *m_pStrOutput;
	
	if (m_pSet->IsOpen())
		m_pSet->SetFieldNull(m_pStrOutput, FALSE);

	UpdateData(FALSE);
}

/////////////////////////////////////////////////////////
/*
void CTerapiaDlg::OnChangeRicerca()
{
	int nNewPos = -1; 

	UpdateData(TRUE);
	
	nNewPos = m_ctrLista[0].FindString(-1, m_strRicerca);

	m_ctrLista[0].SetCurSel(nNewPos);
		
	UpdateData(FALSE);
}
*/

/////////////////////////////////////////////////////////
void CTerapiaDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	/*
	if (bShow)
	{
		int nStart, nEnd;
		m_ctrlRicerca.GetSel(nStart, nEnd);
		m_ctrlRicerca.SetSel(nEnd+1, nEnd+1);
	}
	*/
}