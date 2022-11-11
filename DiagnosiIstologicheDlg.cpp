#include "stdafx.h"
#include "Endox.h"
#include "DiagnosiIstologicheDlg.h"

#include "DiagnosiIstologicheSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDiagnosiIstologicheDlg::CDiagnosiIstologicheDlg(CWnd* pParent)
	: CDialog(CDiagnosiIstologicheDlg::IDD, pParent)
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;
}

CDiagnosiIstologicheDlg::~CDiagnosiIstologicheDlg()
{
}

BEGIN_MESSAGE_MAP(CDiagnosiIstologicheDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBtnUndo)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)

	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)

END_MESSAGE_MAP()

void CDiagnosiIstologicheDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LISTA, m_ctrlLista);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_DESCRIZIONE, m_ctrlEditDescrizione);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlBtnNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlBtnSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlBtnUndo);
	DDX_Control(pDX, IDC_BTN_EXIT, m_ctrlBtnExit);
}

void CDiagnosiIstologicheDlg::OnCancel()
{
}

BOOL CDiagnosiIstologicheDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ctrlBtnExit.SetFont(&theApp.m_fontBold);
	
	m_ctrlBtnNew.EnableWindow(TRUE);
	m_ctrlBtnEdt.EnableWindow(FALSE);
	m_ctrlBtnDel.EnableWindow(FALSE);
	m_ctrlBtnSave.EnableWindow(FALSE);
	m_ctrlBtnUndo.EnableWindow(FALSE);

	m_ctrlEditDescrizione.SetReadOnly(TRUE);

	RiempiLista();

	theApp.LocalizeDialog(this, CDiagnosiIstologicheDlg::IDD, "DiagnosiIstologicheDlg");
	return TRUE;
}

void CDiagnosiIstologicheDlg::OnOK()
{
}

void CDiagnosiIstologicheDlg::OnBtnNew() 
{
	m_ctrlLista.EnableWindow(FALSE);
	m_ctrlEditDescrizione.SetReadOnly(FALSE);
	
	m_ctrlBtnNew.EnableWindow(FALSE);
	m_ctrlBtnEdt.EnableWindow(FALSE);
	m_ctrlBtnDel.EnableWindow(FALSE);
	m_ctrlBtnSave.EnableWindow(TRUE);
	m_ctrlBtnUndo.EnableWindow(TRUE);

	m_ctrlBtnExit.EnableWindow(FALSE);

	//

	m_ctrlEditDescrizione.SetWindowText("");
	m_ctrlEditDescrizione.SetFocus();
	m_bAddNew = TRUE;
}

void CDiagnosiIstologicheDlg::OnBtnEdt() 
{
	m_ctrlLista.EnableWindow(FALSE);
	m_ctrlEditDescrizione.SetReadOnly(FALSE);

	m_ctrlBtnNew.EnableWindow(FALSE);
	m_ctrlBtnEdt.EnableWindow(FALSE);
	m_ctrlBtnDel.EnableWindow(FALSE);
	m_ctrlBtnSave.EnableWindow(TRUE);
	m_ctrlBtnUndo.EnableWindow(TRUE);

	m_ctrlBtnExit.EnableWindow(FALSE);

	if (m_ctrlLista.GetCurSel() >= 0)
	{
		m_ctrlEditDescrizione.SetFocus();
		m_bModify = TRUE;
	}			
}

void CDiagnosiIstologicheDlg::OnBtnDel() 
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIAGNOSIISTOLOGICHE_DELETE_CONFIRM), MB_YESNO) == IDYES)
	{
		int nIndex = m_ctrlLista.GetCurSel();
		if (nIndex >= 0)
		{
			long lID = m_ctrlLista.GetItemData(nIndex);
		
			if (lID >= 0)
			{
				CDiagnosiIstologicheSet().Del(lID);

				m_ctrlEditDescrizione.SetWindowText("");
				RiempiLista();
			}
		}
	}

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlEditDescrizione.SetReadOnly(TRUE);

	m_ctrlBtnNew.EnableWindow(TRUE);
	m_ctrlBtnEdt.EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	m_ctrlBtnDel.EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	m_ctrlBtnSave.EnableWindow(FALSE);
	m_ctrlBtnUndo.EnableWindow(FALSE);

	m_ctrlBtnExit.EnableWindow(TRUE);
}

void CDiagnosiIstologicheDlg::OnBtnSave() 
{
	CString sDescrizione;
	m_ctrlEditDescrizione.GetWindowText(sDescrizione);

	sDescrizione.Trim();
	if (sDescrizione.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIAGNOSIISTOLOGICHE_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		CDiagnosiIstologicheSet().Add(sDescrizione);
	}
	else if (m_bModify)
	{
		int nIndex = m_ctrlLista.GetCurSel();
		if (nIndex >= 0)
		{
			long lID = m_ctrlLista.GetItemData(nIndex);
		
			if (lID >= 0)
				CDiagnosiIstologicheSet().Edt(lID, sDescrizione);
		}
	}
	
	m_ctrlEditDescrizione.SetWindowText("");
	RiempiLista();

	//

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlEditDescrizione.SetReadOnly(TRUE);

	m_ctrlBtnNew.EnableWindow(TRUE);
	m_ctrlBtnEdt.EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	m_ctrlBtnDel.EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	m_ctrlBtnSave.EnableWindow(FALSE);
	m_ctrlBtnUndo.EnableWindow(FALSE);

	m_ctrlBtnExit.EnableWindow(TRUE);

	//

	m_bAddNew = FALSE;
	m_bModify = FALSE;
}

void CDiagnosiIstologicheDlg::OnBtnUndo() 
{
	m_ctrlEditDescrizione.SetWindowText("");
	RiempiLista();

	//

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlEditDescrizione.SetReadOnly(TRUE);

	m_ctrlBtnNew.EnableWindow(TRUE);
	m_ctrlBtnEdt.EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	m_ctrlBtnDel.EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	m_ctrlBtnSave.EnableWindow(FALSE);
	m_ctrlBtnUndo.EnableWindow(FALSE);

	m_ctrlBtnExit.EnableWindow(TRUE);

	//

	m_bAddNew = FALSE;
	m_bModify = FALSE;
}

void CDiagnosiIstologicheDlg::OnBtnExit()
{
	if (m_ctrlBtnExit.IsWindowEnabled())
		CDialog::OnOK();
}

void CDiagnosiIstologicheDlg::OnSelchangeLista() 
{
	if (m_bAddNew || m_bModify)
		return;

	int nCurSel = m_ctrlLista.GetCurSel();
	if (nCurSel >= 0)
	{
		long lID = m_ctrlLista.GetItemData(nCurSel);
		m_ctrlEditDescrizione.SetWindowText(CDiagnosiIstologicheSet().GetDescrizione(lID));

		m_ctrlBtnNew.EnableWindow(TRUE);
		m_ctrlBtnEdt.EnableWindow(TRUE);
		m_ctrlBtnDel.EnableWindow(TRUE);
		m_ctrlBtnSave.EnableWindow(FALSE);
		m_ctrlBtnUndo.EnableWindow(FALSE);
	}
	else
	{
		m_ctrlBtnNew.EnableWindow(TRUE);
		m_ctrlBtnEdt.EnableWindow(FALSE);
		m_ctrlBtnDel.EnableWindow(FALSE);
		m_ctrlBtnSave.EnableWindow(FALSE);
		m_ctrlBtnUndo.EnableWindow(FALSE);
	}
}

void CDiagnosiIstologicheDlg::RiempiLista()
{
	m_ctrlLista.SetRedraw(FALSE);
	m_ctrlLista.ResetContent();
	m_ctrlLista.SetTabStops(100);
	
	CDiagnosiIstologicheSet setTemp;
	setTemp.SetSortRecord("Descrizione");

	if (setTemp.OpenRecordset("CDiagnosiIstologicheDlg::RiempiLista"))
	{
		int nIndex = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlLista.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlLista.SetItemData(nIndex, setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CDiagnosiIstologicheDlg::RiempiLista");
	}
	
	m_ctrlLista.SetRedraw(TRUE);
}
