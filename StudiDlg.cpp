#include "stdafx.h"
#include "Endox.h"
#include "StudiDlg.h"

#include "EsamiView.h"
#include "StudiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CStudiDlg::CStudiDlg(CWnd* pParentWnd)
	: CDialog(CStudiDlg::IDD, pParentWnd)
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;
}

CStudiDlg::~CStudiDlg()
{
}

BEGIN_MESSAGE_MAP(CStudiDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBtnUndo)

	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)

END_MESSAGE_MAP()

void CStudiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlButtonDel);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);

	DDX_Control(pDX, IDC_DESCRIZIONE, m_ctrlEditDescrizione);

	DDX_Control(pDX, IDC_LISTA, m_ctrlLista);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
}

void CStudiDlg::OnCancel()
{
}

BOOL CStudiDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ctrlButtonOK.SetFont(&theApp.m_fontBold);
	
	RiempiListaStudi();
	
	theApp.LocalizeDialog(this, CStudiDlg::IDD, "StudiDlg");
	return TRUE;
}

void CStudiDlg::OnOK()
{
	if (m_ctrlButtonOK.IsWindowEnabled())
		CDialog::OnOK();
}

void CStudiDlg::RiempiListaStudi()
{
	m_ctrlLista.ResetContent();

	CStudiSet setStudi;
	setStudi.SetSortRecord("Descrizione");
	if (setStudi.OpenRecordset("CStudiDlg::RiempiListaStudi"))
	{
		while(!setStudi.IsEOF())
		{
			int nItem = m_ctrlLista.AddString(setStudi.m_sDescrizione);

			if (nItem >= 0)
				m_ctrlLista.SetItemData(nItem, (DWORD)setStudi.m_lID);

			setStudi.MoveNext();
		}

		setStudi.CloseRecordset("CStudiDlg::RiempiListaStudi");
	}
	
	OnSelchangeLista();
}

void CStudiDlg::OnSelchangeLista() 
{
	int nCurPos = m_ctrlLista.GetCurSel();

	m_ctrlButtonEdt.EnableWindow(nCurPos >= 0);
	m_ctrlButtonDel.EnableWindow(nCurPos >= 0);

	if (nCurPos >= 0)
	{
		CString sDesc;
		m_ctrlLista.GetText(nCurPos, sDesc);
		m_ctrlEditDescrizione.SetWindowText(sDesc);
	}
	else
	{
		m_ctrlEditDescrizione.SetWindowText("");
	}
}

void CStudiDlg::OnBtnNew() 
{
	m_ctrlLista.EnableWindow(FALSE);
	m_ctrlEditDescrizione.EnableWindow(TRUE);
	
	m_ctrlButtonNew.EnableWindow(FALSE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(TRUE);
	m_ctrlButtonUndo.EnableWindow(TRUE);
	m_ctrlButtonOK.EnableWindow(FALSE);

	m_ctrlEditDescrizione.SetWindowText("");
	m_ctrlEditDescrizione.SetFocus();

	m_bAddNew = TRUE;
}

void CStudiDlg::OnBtnEdt() 
{
	int nCurSel = m_ctrlLista.GetCurSel();

	if (nCurSel >= 0)
	{
		m_ctrlLista.EnableWindow(FALSE);
		m_ctrlEditDescrizione.EnableWindow(TRUE);
		
		m_ctrlButtonNew.EnableWindow(FALSE);
		m_ctrlButtonEdt.EnableWindow(FALSE);
		m_ctrlButtonDel.EnableWindow(FALSE);
		m_ctrlButtonSave.EnableWindow(TRUE);
		m_ctrlButtonUndo.EnableWindow(TRUE);
		m_ctrlButtonOK.EnableWindow(FALSE);

		m_ctrlEditDescrizione.SetFocus();

		m_bModify = TRUE;
	}			
}


void CStudiDlg::OnBtnDel() 
{
	int nCurSel = m_ctrlLista.GetCurSel();
		
	if (nCurSel >= 0)
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STUDIDLG_DELETE_CONFIRM), MB_YESNO) == IDYES)
		{
			long lID = (long)m_ctrlLista.GetItemData(nCurSel);
		
			if (CStudiSet().DelStudio(lID))
				RiempiListaStudi();
		}
	}
}

void CStudiDlg::OnBtnSave() 
{
	CString sDesc;
	m_ctrlEditDescrizione.GetWindowText(sDesc);

	sDesc.Trim();
	if (sDesc.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STUDIDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		CStudiSet().AddStudio(sDesc);
	}
	else if (m_bModify)		
	{
		int nCurSel = m_ctrlLista.GetCurSel();

		if (nCurSel >= 0)
			CStudiSet().EdtStudio((long)m_ctrlLista.GetItemData(nCurSel), sDesc);
	}

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlEditDescrizione.EnableWindow(FALSE);
	
	m_ctrlButtonNew.EnableWindow(TRUE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(FALSE);
	m_ctrlButtonUndo.EnableWindow(FALSE);
	m_ctrlButtonOK.EnableWindow(TRUE);

	RiempiListaStudi();
	
	m_bModify = FALSE;
	m_bAddNew = FALSE;
}

void CStudiDlg::OnBtnUndo() 
{
	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlEditDescrizione.EnableWindow(FALSE);
	
	m_ctrlButtonNew.EnableWindow(TRUE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(FALSE);
	m_ctrlButtonUndo.EnableWindow(FALSE);
	m_ctrlButtonOK.EnableWindow(TRUE);

	RiempiListaStudi();

	m_bAddNew = FALSE;
	m_bModify = FALSE;
}