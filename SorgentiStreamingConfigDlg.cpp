#include "stdafx.h"
#include "Endox.h"
#include "SorgentiStreamingConfigDlg.h"

#include "SorgentiStreamingSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSorgentiStreamingConfigDlg::CSorgentiStreamingConfigDlg(CWnd* pParentWnd)
	: CDialog(CSorgentiStreamingConfigDlg::IDD, pParentWnd)
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;
}

CSorgentiStreamingConfigDlg::~CSorgentiStreamingConfigDlg()
{
}

BEGIN_MESSAGE_MAP(CSorgentiStreamingConfigDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBtnUndo)

	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)
END_MESSAGE_MAP()

void CSorgentiStreamingConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW,		m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT,		m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_BTN_DEL,		m_ctrlButtonDel);
	DDX_Control(pDX, IDC_BTN_SAVE,		m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO,		m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK,				m_ctrlButtonOK);

	DDX_Control(pDX, IDC_DESCRIZIONE,	m_ctrlEditDescrizione);
	DDX_Control(pDX, IDC_INDIRIZZO_STREAMING,	m_ctrlEditIndirizzoStreaming);
	DDX_Control(pDX, IDC_NOMECOMPUTERSORGENTE,	m_ctrlEditNomeComputerSorgente);

	DDX_Control(pDX, IDC_LISTA,			m_ctrlLista);

	DDX_Control(pDX, IDC_STATIC_1,		m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2,		m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3,		m_ctrlStatic3);
}

void CSorgentiStreamingConfigDlg::OnCancel()
{
}

BOOL CSorgentiStreamingConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ctrlButtonOK.SetFont(&theApp.m_fontBold);
	
	RiempiListaSorgenti();
	
	theApp.LocalizeDialog(this, CSorgentiStreamingConfigDlg::IDD, "SorgentiStreamingConfigDlg");
	return TRUE;
}

void CSorgentiStreamingConfigDlg::OnOK()
{
	if (m_ctrlButtonOK.IsWindowEnabled())
		CDialog::OnOK();
}

void CSorgentiStreamingConfigDlg::RiempiListaSorgenti()
{
	m_ctrlLista.ResetContent();

	CSorgentiStreamingSet set;
	set.SetSortRecord("descrizione");
	if (set.OpenRecordset("CSorgentiStreamingConfigDlg::RiempiListaSorgenti"))
	{
		while(!set.IsEOF())
		{
			int nItem = m_ctrlLista.AddString(set.m_sDescrizione);

			if (nItem >= 0)
				m_ctrlLista.SetItemData(nItem, (DWORD)set.m_lID);

			set.MoveNext();
		}

		set.CloseRecordset("CSorgentiStreamingConfigDlg::RiempiListaSorgenti");
	}
	
	OnSelchangeLista();
}

void CSorgentiStreamingConfigDlg::OnSelchangeLista() 
{
	int nCurPos = m_ctrlLista.GetCurSel();

	m_ctrlButtonEdt.EnableWindow(nCurPos >= 0);
	m_ctrlButtonDel.EnableWindow(nCurPos >= 0);

	if (nCurPos >= 0)
	{
		/*CString sDesc;
		m_ctrlLista.GetText(nCurPos, sDesc);
		m_ctrlEditDescrizione.SetWindowText(sDesc);*/

		DWORD dwCode = m_ctrlLista.GetItemData(nCurPos);

		if (dwCode >= 0)
		{
			CString strFilter;
			strFilter.Format("Id=%li", (long)dwCode);

			CSorgentiStreamingSet setTemp;
			setTemp.SetOpenFilter(strFilter);

			if (setTemp.OpenRecordset("CSorgentiStreamingConfigDlg::OnSelchangeLista"))
			{				
				if (!setTemp.IsEOF())
				{					
					m_ctrlEditDescrizione.SetWindowText(setTemp.m_sDescrizione);
					m_ctrlEditIndirizzoStreaming.SetWindowText(setTemp.m_sIndirizzoCompleto);
					m_ctrlEditNomeComputerSorgente.SetWindowText(setTemp.m_sNomeComputerSala);
				}
		
				setTemp.CloseRecordset("CSorgentiStreamingConfigDlg::OnSelchangeLista");				
			}

			UpdateData(FALSE);
		}	
	}
	else
	{
		m_ctrlEditDescrizione.SetWindowText("");
		m_ctrlEditIndirizzoStreaming.SetWindowText("");
		m_ctrlEditNomeComputerSorgente.SetWindowText("");
	}
}

void CSorgentiStreamingConfigDlg::OnBtnNew() 
{
	m_ctrlLista.EnableWindow(FALSE);
	m_ctrlEditDescrizione.EnableWindow(TRUE);
	m_ctrlEditIndirizzoStreaming.EnableWindow(TRUE);
	m_ctrlEditNomeComputerSorgente.EnableWindow(TRUE);
	
	m_ctrlButtonNew.EnableWindow(FALSE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(TRUE);
	m_ctrlButtonUndo.EnableWindow(TRUE);
	m_ctrlButtonOK.EnableWindow(FALSE);

	m_ctrlEditDescrizione.SetWindowText("");
	m_ctrlEditDescrizione.SetFocus();
	m_ctrlEditIndirizzoStreaming.SetWindowText("");
	m_ctrlEditIndirizzoStreaming.SetFocus();
	m_ctrlEditNomeComputerSorgente.SetWindowText("");
	m_ctrlEditNomeComputerSorgente.SetFocus();

	m_bAddNew = TRUE;
}

void CSorgentiStreamingConfigDlg::OnBtnEdt() 
{
	int nCurSel = m_ctrlLista.GetCurSel();

	if (nCurSel >= 0)
	{
		m_ctrlLista.EnableWindow(FALSE);
		m_ctrlEditDescrizione.EnableWindow(TRUE);
		m_ctrlEditIndirizzoStreaming.EnableWindow(TRUE);
		m_ctrlEditNomeComputerSorgente.EnableWindow(TRUE);
		
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


void CSorgentiStreamingConfigDlg::OnBtnDel() 
{
	int nCurSel = m_ctrlLista.GetCurSel();
		
	if (nCurSel >= 0)
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_DELETE_CONFIRM), MB_YESNO) == IDYES)
		{
			long lID = (long)m_ctrlLista.GetItemData(nCurSel);
		
			if (CSorgentiStreamingSet().Del(lID))
				RiempiListaSorgenti();
		}
	}
}

void CSorgentiStreamingConfigDlg::OnBtnSave() 
{
	CString sDesc;
	m_ctrlEditDescrizione.GetWindowText(sDesc);

	sDesc.Trim();
	if (sDesc.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	CString sIndirizzo, sComputer;
	m_ctrlEditIndirizzoStreaming.GetWindowText(sIndirizzo);
	m_ctrlEditNomeComputerSorgente.GetWindowText(sComputer);

	if (m_bAddNew)
	{
		CSorgentiStreamingSet().Add(sDesc, sIndirizzo, sComputer);
	}
	else if (m_bModify)		
	{
		int nCurSel = m_ctrlLista.GetCurSel();

		if (nCurSel >= 0)
			CSorgentiStreamingSet().Edt((long)m_ctrlLista.GetItemData(nCurSel), sDesc, sIndirizzo, sComputer);
	}

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlEditDescrizione.EnableWindow(FALSE);
	m_ctrlEditIndirizzoStreaming.EnableWindow(FALSE);
	m_ctrlEditNomeComputerSorgente.EnableWindow(FALSE);
	
	m_ctrlButtonNew.EnableWindow(TRUE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(FALSE);
	m_ctrlButtonUndo.EnableWindow(FALSE);
	m_ctrlButtonOK.EnableWindow(TRUE);

	RiempiListaSorgenti();
	
	m_bModify = FALSE;
	m_bAddNew = FALSE;
}

void CSorgentiStreamingConfigDlg::OnBtnUndo() 
{
	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlEditDescrizione.EnableWindow(FALSE);
	m_ctrlEditIndirizzoStreaming.EnableWindow(FALSE);
	m_ctrlEditNomeComputerSorgente.EnableWindow(FALSE);
	
	m_ctrlButtonNew.EnableWindow(TRUE);
	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonDel.EnableWindow(FALSE);
	m_ctrlButtonSave.EnableWindow(FALSE);
	m_ctrlButtonUndo.EnableWindow(FALSE);
	m_ctrlButtonOK.EnableWindow(TRUE);

	RiempiListaSorgenti();

	m_bAddNew = FALSE;
	m_bModify = FALSE;
}