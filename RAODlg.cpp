#include "stdafx.h"
#include "Endox.h"
#include "RAODlg.h"

#include "ComboRAOSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRAODlg::CRAODlg(CWnd* pParentWnd)
	: CDialog(CRAODlg::IDD, pParentWnd)
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;
}

CRAODlg::~CRAODlg()
{
}

BEGIN_MESSAGE_MAP(CRAODlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBtnUndo)

	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)
END_MESSAGE_MAP()

void CRAODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW,		m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT,		m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_BTN_DEL,		m_ctrlButtonDel);
	DDX_Control(pDX, IDC_BTN_SAVE,		m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO,		m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK,				m_ctrlButtonOK);

	DDX_Control(pDX, IDC_DESCRIZIONE,	m_ctrlEditDescrizione);
	DDX_Control(pDX, IDC_CODICE_INTEGRAZIONE,	m_ctrlEditCodiceIntegrazione);

	DDX_Control(pDX, IDC_LISTA,			m_ctrlLista);

	DDX_Control(pDX, IDC_STATIC_1,		m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2,		m_ctrlStatic2);
}

void CRAODlg::OnCancel()
{
}

BOOL CRAODlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ctrlButtonOK.SetFont(&theApp.m_fontBold);
	
	RiempiListaRAO();
	
	theApp.LocalizeDialog(this, CRAODlg::IDD, "RAODlg");
	return TRUE;
}

void CRAODlg::OnOK()
{
	if (m_ctrlButtonOK.IsWindowEnabled())
		CDialog::OnOK();
}

void CRAODlg::RiempiListaRAO()
{
	m_ctrlLista.ResetContent();

	CComboRAOSet setRao;
	setRao.SetSortRecord("DescrizioneRAO");
	if (setRao.OpenRecordset("CRAODlg::RiempiListaRAO"))
	{
		while(!setRao.IsEOF())
		{
			int nItem = m_ctrlLista.AddString(setRao.m_sDescrizione);

			if (nItem >= 0)
				m_ctrlLista.SetItemData(nItem, (DWORD)setRao.m_lID);

			setRao.MoveNext();
		}

		setRao.CloseRecordset("CRAODlg::RiempiListaRAO");
	}
	
	OnSelchangeLista();
}

void CRAODlg::OnSelchangeLista() 
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

void CRAODlg::OnBtnNew() 
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
	m_ctrlEditCodiceIntegrazione.SetWindowText("");
	m_ctrlEditCodiceIntegrazione.SetFocus();

	m_bAddNew = TRUE;
}

void CRAODlg::OnBtnEdt() 
{
	int nCurSel = m_ctrlLista.GetCurSel();

	if (nCurSel >= 0)
	{
		m_ctrlLista.EnableWindow(FALSE);
		m_ctrlEditDescrizione.EnableWindow(TRUE);
		m_ctrlEditCodiceIntegrazione.EnableWindow(TRUE);
		
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


void CRAODlg::OnBtnDel() 
{
	int nCurSel = m_ctrlLista.GetCurSel();
		
	if (nCurSel >= 0)
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_DELETE_CONFIRM), MB_YESNO) == IDYES)
		{
			long lID = (long)m_ctrlLista.GetItemData(nCurSel);
		
			if (CComboRAOSet().DelRAO(lID))
				RiempiListaRAO();
		}
	}
}

void CRAODlg::OnBtnSave() 
{
	CString sDesc;
	m_ctrlEditDescrizione.GetWindowText(sDesc);

	sDesc.Trim();
	if (sDesc.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	CString sCodice;
	m_ctrlEditCodiceIntegrazione.GetWindowText(sCodice);

	if (m_bAddNew)
	{
		CComboRAOSet().AddRAO(sDesc);
	}
	else if (m_bModify)		
	{
		int nCurSel = m_ctrlLista.GetCurSel();

		if (nCurSel >= 0)
			CComboRAOSet().EdtRAO((long)m_ctrlLista.GetItemData(nCurSel), sDesc);
	}

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlEditDescrizione.EnableWindow(FALSE);
	m_ctrlEditCodiceIntegrazione.EnableWindow(FALSE);
	
	m_ctrlButtonNew.EnableWindow(TRUE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(FALSE);
	m_ctrlButtonUndo.EnableWindow(FALSE);
	m_ctrlButtonOK.EnableWindow(TRUE);

	RiempiListaRAO();
	
	m_bModify = FALSE;
	m_bAddNew = FALSE;
}

void CRAODlg::OnBtnUndo() 
{
	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlEditDescrizione.EnableWindow(FALSE);
	m_ctrlEditCodiceIntegrazione.EnableWindow(FALSE);
	
	m_ctrlButtonNew.EnableWindow(TRUE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(FALSE);
	m_ctrlButtonUndo.EnableWindow(FALSE);
	m_ctrlButtonOK.EnableWindow(TRUE);

	RiempiListaRAO();

	m_bAddNew = FALSE;
	m_bModify = FALSE;
}