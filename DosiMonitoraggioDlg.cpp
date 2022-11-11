#include "stdafx.h"
#include "Endox.h"
#include "DosiMonitoraggioDlg.h"

#include "EsamiView.h"
#include "DosiMonitoraggioSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDosiMonitoraggioDlg::CDosiMonitoraggioDlg(CEsamiView* pEsamiView, BOOL bMenu)
	: CDialog(CDosiMonitoraggioDlg::IDD, (CWnd*)pEsamiView)
{
	m_pEsamiView	= pEsamiView;
	m_bMenu			= bMenu;

	m_strDescrizione = "";

	m_lSavedPosition = -1;
	m_bAddNew		= FALSE;
	m_bModify		= FALSE;

}

CDosiMonitoraggioDlg::~CDosiMonitoraggioDlg()
{
}

void CDosiMonitoraggioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DESCRIZIONE,	   m_strDescrizione);
	DDX_Control(pDX, IDC_LISTA,    m_ctrlLista);

	DDX_Control(pDX, IDC_STATIC_1,  m_ctrlStatic1);
	DDX_Control(pDX, IDC_NUOVO,   m_ctrlButtonNew);
	DDX_Control(pDX, IDC_MODIFY,  m_ctrlButtonMod);
	DDX_Control(pDX, IDC_CANC,    m_ctrlButtonDel);
	DDX_Control(pDX, IDC_UPDATE,  m_ctrlButtonUpd);
	DDX_Control(pDX, IDC_REFRESH, m_ctrlButtonRefresh);
	DDX_Control(pDX, IDOK,               m_ctrlButtonOK);
}

BEGIN_MESSAGE_MAP(CDosiMonitoraggioDlg, CDialog)
	ON_BN_CLICKED(IDC_CANC,	 OnDelete)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_NUOVO,  OnNew)
	ON_BN_CLICKED(IDC_REFRESH,OnRefresh)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)

	ON_LBN_DBLCLK(IDC_LISTA, OnLbnDblclkLista)
	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COperatoriDlg message handlers

BOOL CDosiMonitoraggioDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);
	
	GetDlgItem(IDC_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);

	RiempiLista();
	
	m_nItemPressed = 0;
	m_nItemCount = m_ctrlLista.GetCount();
	theApp.LocalizeDialog(this, CDosiMonitoraggioDlg::IDD, "DosiMonitoraggioDlg");

	return TRUE;
}

void CDosiMonitoraggioDlg::RiempiLista()
{
	m_ctrlLista.ResetContent();
	m_ctrlLista.SetTabStops(100);
	
	CDosiMonitoraggioSet setDosiMonitoraggio;
	setDosiMonitoraggio.SetSortRecord("Descrizione");
	if (setDosiMonitoraggio.OpenRecordset("CDosiMonitoraggioDlg::RiempiLista"))
	{
		while (!setDosiMonitoraggio.IsEOF())
		{
			int posiz = m_ctrlLista.AddString(setDosiMonitoraggio.m_sNome);

			if (posiz >= 0)
				m_ctrlLista.SetItemData(posiz, (DWORD)setDosiMonitoraggio.m_lID);

			setDosiMonitoraggio.MoveNext();
		}

		setDosiMonitoraggio.CloseRecordset("CDosiMonitoraggioDlg::RiempiLista");
	}
	
	OnSelchangeLista();
}

void CDosiMonitoraggioDlg::OnLbnDblclkLista()
{
	if (m_bMenu == FALSE)
		OnOK();
}

void CDosiMonitoraggioDlg::OnSelchangeLista() 
{
	CString strDoctor, strTmp;

	if (m_bAddNew || m_bModify)
		return;

	int nCount = m_ctrlLista.GetCount();

	if (nCount > 0)
	{
		int nCurPos = m_ctrlLista.GetCurSel();

		if (nCurPos >= 0)
		{
			// recupera il codice del medico appena selezionato	
			DWORD dwCode = m_ctrlLista.GetItemData(nCurPos);

			GetDlgItem(IDC_NUOVO)->EnableWindow(TRUE);
			GetDlgItem(IDC_MODIFY)->EnableWindow(TRUE);
			GetDlgItem(IDC_CANC)->EnableWindow(TRUE);
			GetDlgItem(IDC_UPDATE)->EnableWindow(FALSE);
			GetDlgItem(IDC_REFRESH)->EnableWindow(FALSE);

			if (dwCode >= 0)
			{
				CString sFilter;
				sFilter.Format("Id=%li", (long)dwCode);

				CDosiMonitoraggioSet setDosiMonitoraggio;
				setDosiMonitoraggio.SetOpenFilter(sFilter);
				if (setDosiMonitoraggio.OpenRecordset("CDosiMonitoraggioDlg::OnSelchangeLista"))
				{
					if (!setDosiMonitoraggio.IsEOF())
					{
						m_strDescrizione = setDosiMonitoraggio.m_sNome;
						m_lID = (long)dwCode;

						m_lSavedPosition = nCurPos;
					}

					setDosiMonitoraggio.CloseRecordset("CDosiMonitoraggioDlg::OnSelchangeLista");
				}

				UpdateData(FALSE);
			}
		}
	}
}

void CDosiMonitoraggioDlg::OnOK()
{
	UpdateData(FALSE);
	CDialog::OnOK();
}

void CDosiMonitoraggioDlg::OnDelete() 
{
	BOOL	bDeleted = FALSE;

	GetDlgItem(IDC_LISTA)->EnableWindow(TRUE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);

	GetDlgItem(IDC_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_REFRESH)->EnableWindow(FALSE);

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_DELETE_CONFIRM), MB_YESNO) == IDYES)
	{
		int posiz = m_ctrlLista.GetCurSel();
		if (posiz >= 0)
		{
			DWORD dwCode = m_ctrlLista.GetItemData(posiz);
			if (dwCode >= 0)
				CDosiMonitoraggioSet().Del(dwCode);
		}
	}
	
	UpdateData(FALSE);

	RiempiLista();
}

void CDosiMonitoraggioDlg::OnModify() 
{
	int nSelect = m_ctrlLista.GetCurSel();
		
	if (nSelect >= 0)
	{
		GetDlgItem(IDC_LISTA)	->EnableWindow(FALSE);
		GetDlgItem(IDC_DESCRIZIONE)	->EnableWindow(TRUE);

		GetDlgItem(IDC_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CANC)->EnableWindow(FALSE);
		GetDlgItem(IDC_UPDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_REFRESH)->EnableWindow(TRUE);

		GetDlgItem(IDOK)->EnableWindow(FALSE);

		m_bModify = TRUE;

		GetDlgItem(IDC_DESCRIZIONE)->SetFocus();

		UpdateData(FALSE);
	}			
}

void CDosiMonitoraggioDlg::OnNew() 
{
	GetDlgItem(IDC_LISTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_NUOVO)->EnableWindow(FALSE);
	GetDlgItem(IDC_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_REFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_strDescrizione.Empty();

	m_bAddNew = TRUE;

	GetDlgItem(IDC_DESCRIZIONE)->SetFocus();

	UpdateData(FALSE);
}

void CDosiMonitoraggioDlg::OnRefresh() 
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	GetDlgItem(IDC_LISTA)	->EnableWindow(TRUE);
	GetDlgItem(IDC_DESCRIZIONE)	->EnableWindow(FALSE);

	GetDlgItem(IDC_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(TRUE);

	if (m_lSavedPosition <= m_ctrlLista.GetCount())
	{
		int nPos = m_lSavedPosition;

		if (nPos < 0 && m_ctrlLista.GetCount())
			nPos = 0;
	
		m_lSavedPosition = -1;

		m_ctrlLista.SetCurSel(nPos);

		OnSelchangeLista();
	}
}

void CDosiMonitoraggioDlg::OnUpdate() 
{
	BOOL bSaved = FALSE;
	
	UpdateData(TRUE);

	if (m_strDescrizione.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	long lTemp = 0;

	if (m_bAddNew)
		lTemp = CDosiMonitoraggioSet().Add(m_strDescrizione);
	else		
		CDosiMonitoraggioSet().Edt(m_lID, m_strDescrizione);
	
	int posiz;
	if (m_bAddNew)
	{
		posiz = m_ctrlLista.AddString(m_strDescrizione);

		if (posiz >= 0)
		{
			m_ctrlLista.SetItemData(posiz, (DWORD)lTemp);
			m_ctrlLista.SetCurSel(posiz);
		}
	}
	else
	{
		posiz = m_ctrlLista.GetCurSel();

		if (posiz >= 0)
		{
			m_ctrlLista.DeleteString(posiz);

			posiz = m_ctrlLista.InsertString(posiz, m_strDescrizione);

			if (posiz >= 0)
			{
				m_ctrlLista.SetItemData(posiz, (DWORD)m_lID);
				m_ctrlLista.SetCurSel(posiz);
			}
		}
	}

	GetDlgItem(IDC_LISTA)	->EnableWindow(TRUE);
	GetDlgItem(IDC_DESCRIZIONE)	->EnableWindow(FALSE);

	GetDlgItem(IDC_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(TRUE);

	m_bModify = FALSE;
	m_bAddNew = FALSE;

	OnSelchangeLista();
}