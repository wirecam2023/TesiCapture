#include "stdafx.h"
#include "Endox.h"
#include "ConsensoInformatoDynForm.h"

#include "AlbumForm.h"
#include "CustomDate.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "LockManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CConsensoInformatoDynForm::CConsensoInformatoDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView),
	  m_ctrlRadio1(IDC_EDIT_MOTIVO),
	  m_ctrlRadio2(IDC_EDIT_MOTIVO)
{
	m_wReadOnly = -1;
}

CConsensoInformatoDynForm::~CConsensoInformatoDynForm()
{
}

BEGIN_MESSAGE_MAP(CConsensoInformatoDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_RADIO1, OnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO2, OnClickedRadio)
	ON_BN_CLICKED(IDC_BTN_STAMPA, OnClickedBtnStampa)
	ON_BN_CLICKED(IDC_BTN_STAMPA_BAT, OnClickedBtnStampaBat)
	ON_BN_CLICKED(IDC_BTN_ACQUISISCI, OnClickedBtnAcquisisci)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CConsensoInformatoDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_consensoinformato] == NULL)
	{
		pEsamiView->m_pDynForm[sub_consensoinformato] = new CConsensoInformatoDynForm(CConsensoInformatoDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_consensoinformato] != NULL)
		{
			pEsamiView->m_pDynForm[sub_consensoinformato]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_consensoinformato]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_consensoinformato]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_consensoinformato]->CreateChildForm(CConsensoInformatoDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CConsensoInformatoDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_CONSENSO:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_STATIC1:
		case IDC_STATIC2:
		case IDC_STATIC_NOTE:
		case IDC_EDIT_MOTIVO:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CConsensoInformatoDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_FieldRadio(pDX, IDC_RADIO1, m_pEsamiView->m_pEsamiSet->m_iConsensoInformato, m_pEsamiView->m_pEsamiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_MOTIVO, m_pEsamiView->m_pEsamiSet->m_sNoteConsensoInformato, m_pEsamiView->m_pEsamiSet->GetRecordset());

	DDX_Control(pDX, IDC_STATIC_CONSENSO, m_ctrlStaticConsenso);
	DDX_Control(pDX, IDC_STATIC1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_NOTE, m_ctrlStaticNote);

	DDX_Control(pDX, IDC_RADIO1, m_ctrlRadio1);
	DDX_Control(pDX, IDC_RADIO2, m_ctrlRadio2);

	DDX_Control(pDX, IDC_EDIT_MOTIVO, m_ctrlMotivo);
	DDX_Control(pDX, IDC_BTN_STAMPA, m_ctrlButtonStampa);
	DDX_Control(pDX, IDC_BTN_STAMPA_BAT, m_ctrlButtonStampaBat);
	DDX_Control(pDX, IDC_BTN_ACQUISISCI, m_ctrlButtonAcquisisci);
}

BOOL CConsensoInformatoDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_CONSENSO, CSize(0,0), CSize(100,0));
	AddAnchor(IDC_RADIO1, CSize(0,0), CSize(0,0));
	AddAnchor(IDC_STATIC1, CSize(0,0), CSize(50,0));
	AddAnchor(IDC_RADIO2, CSize(50,0), CSize(50,0));
	AddAnchor(IDC_STATIC2, CSize(50,0), CSize(100,0));
	AddAnchor(IDC_STATIC_NOTE, CSize(0,0), CSize(100,0));
	AddAnchor(IDC_EDIT_MOTIVO, CSize(0,0), CSize(100,100));
	AddAnchor(IDC_BTN_STAMPA, CSize(0,100), CSize(100,100));
	AddAnchor(IDC_BTN_STAMPA_BAT, CSize(0,100), CSize(50,100));
	AddAnchor(IDC_BTN_ACQUISISCI, CSize(50,100), CSize(100,100));
	AddAnchor(IDC_STATIC_NUM, CSize(100,100), CSize(100,100));

	m_ctrlMotivo.SetParam(this, CMB_ESA_MOTIVOCONSENSO, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_sNoteConsensoInformato, 3999);
	m_ctrlMotivo.SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);

	theApp.LocalizeDialog(this, CConsensoInformatoDynForm::IDD, "ConsensoInformatoDynForm");

	return bReturn;
}

void CConsensoInformatoDynForm::OnClickedRadio()
{
	m_pEsamiView->UpdateData(TRUE);

	OnFormReadOnly(m_wReadOnly, (LPARAM)0);
}

LRESULT CConsensoInformatoDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CConsensoInformatoDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	CRect rectTemp;
	GetDlgItem(IDC_STATIC_NUM)->GetWindowRect(rectTemp);
	ScreenToClient(rectTemp);
	InvalidateRect(rectTemp);

	return UpdateData(FALSE);
}

LRESULT CConsensoInformatoDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_wReadOnly = wParam;

	SendDlgItemMessage(IDC_EDIT_MOTIVO, EM_SETREADONLY, wParam, lParam);

	m_ctrlRadio1.EnableWindow(!(BOOL)wParam);
	m_ctrlRadio2.EnableWindow(!(BOOL)wParam);

	m_ctrlButtonStampa.EnableWindow((BOOL)wParam);
	m_ctrlButtonStampaBat.EnableWindow(FALSE);
	m_ctrlButtonAcquisisci.EnableWindow((BOOL)wParam);

	if (m_pEsamiView->m_pEsamiSet->m_iConsensoInformato == 1)
	{
		GetDlgItem(IDC_STATIC_NOTE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MOTIVO)->ShowWindow(SW_SHOW);

		if ((theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI) || (theApp.m_nProgramMode & FILTER_RECORD_ESAMI))
		{
			m_ctrlButtonStampa.ShowWindow(SW_HIDE);
			m_ctrlButtonStampaBat.ShowWindow(SW_HIDE);
			m_ctrlButtonAcquisisci.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_NUM)->ShowWindow(SW_HIDE);
		}
		else
		{
			m_ctrlButtonStampa.ShowWindow(SW_SHOW);
			m_ctrlButtonStampaBat.ShowWindow(SW_HIDE);
			m_ctrlButtonAcquisisci.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_NUM)->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		GetDlgItem(IDC_STATIC_NOTE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MOTIVO)->ShowWindow(SW_HIDE);
		m_ctrlButtonStampa.ShowWindow(SW_HIDE);
		m_ctrlButtonStampaBat.ShowWindow(SW_HIDE);
		m_ctrlButtonAcquisisci.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_NUM)->ShowWindow(SW_HIDE);
	}

	return 1;
}

LRESULT CConsensoInformatoDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CConsensoInformatoDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CConsensoInformatoDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (m_pEsamiView->m_pEsamiSet->m_iConsensoInformato >= 0)
		ComponiRicercaShort(*pStrWhere, m_pEsamiView->m_pEsamiSet, (short*)&m_pEsamiView->m_pEsamiSet->m_iConsensoInformato, "EEsami.ConsensoInformato", 0, TRUE);

	return 1;
}

long CConsensoInformatoDynForm::GetContenuto()
{
	return sub_consensoinformato;
}

BOOL CConsensoInformatoDynForm::CampoObbligatorioValido()
{
	switch(m_pEsamiView->m_pEsamiSet->m_iConsensoInformato)
	{
		case 0:
		{
			return TRUE;

			break;
		}
		case 1:
		{
			if (m_pEsamiView->m_pEsamiSet->m_sNoteConsensoInformato.GetLength() > 0)
				return TRUE;

			break;
		}
	}

	return FALSE;
}

void CConsensoInformatoDynForm::OnClickedBtnAcquisisci()
{
	m_ctrlButtonAcquisisci.SetCheck(BST_UNCHECKED);

    if (!m_pEsamiView->m_pEsamiSet->IsOpen() || m_pEsamiView->m_pEsamiSet->IsBOF() || m_pEsamiView->m_pEsamiSet->IsEOF())
        return;

	if (m_pEsamiView->m_pFormImmagini == NULL)
		return;
 
	if (m_pEsamiView->m_pFormImmagini->CheckTempFolder())
	{
		// creo la stringa con la data di oggi //
		SYSTEMTIME SystemTime;
		GetLocalTime(&SystemTime);	
		CString strDataOggi;
		strDataOggi.Format("%04d%02d%02d", SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay);

		// creo la stringa con la data dell'esame //
		CCustomDate ExamTime(m_pEsamiView->m_pEsamiSet->m_lData);
		CString strDataEsame = ExamTime.GetDate("%Y%m%d");

		// confronto le due date e se diverse do un alert che forse si è su un esame sbagliato //
		if (strDataOggi != strDataEsame)
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_LAUNCHACQUISITION), MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
				return;

		// long lLockedPatient = m_pEsamiView->m_pEsamiSet->m_lPaziente;
		long lLockedExam = m_pEsamiView->m_pEsamiSet->m_lContatore;
		if (CLockManager::Get()->LockExam(lLockedExam))
		{
			m_pEsamiView->m_pFormImmagini->AcqFromScanner(TRUE);
			CLockManager::Get()->UnlockExam(lLockedExam);
		}
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_IMPORT_PREVIMAGE));
	}

	UpdateData(TRUE);
}

void CConsensoInformatoDynForm::OnClickedBtnStampa()
{
	m_ctrlButtonStampa.SetCheck(BST_UNCHECKED);

	long lPdfId = 0;
	m_pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, "", FALSE, 0, &lPdfId,""); // <-- chiede il report //

	if (m_pEsamiView->m_bEsamiModify)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iConsensoInformato = -1;
		UpdateData(FALSE);
	}
	else
	{
		UpdateData(TRUE);
		if (m_pEsamiView->m_pEsamiSet->EditRecordset("CConsensoInformatoDynForm::OnClickedBtnStampa"))
		{
			m_pEsamiView->m_pEsamiSet->m_iConsensoInformato = -1;
			m_pEsamiView->m_pEsamiSet->UpdateRecordset("CConsensoInformatoDynForm::OnClickedBtnStampa");
		}
		UpdateData(FALSE);
	}

	OnFormReadOnly(m_wReadOnly, (LPARAM)0);
}

void CConsensoInformatoDynForm::OnClickedBtnStampaBat()
{
	//
	m_ctrlButtonStampaBat.SetCheck(BST_UNCHECKED);

	// Sandro 01/10/2012 // RAS 20120138 //
	if (!theApp.m_sPercorsoReportsConsensoInformato.IsEmpty())
	{
		CFileDialog FileDlg(TRUE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "Report (*.rpt)|*.rpt|Tutti i file|*.*|", this, 0, FALSE);
		FileDlg.GetOFN().lpstrInitialDir = theApp.m_sPercorsoReportsConsensoInformato;
		long lPdfId = 0;
		if (FileDlg.DoModal() == IDOK)
			m_pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, FileDlg.GetPathName(), FALSE, 0, &lPdfId,""); // <-- NON chiede il report //
	}
	else
	{
		long lPdfId = 0;
		m_pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, "", FALSE, 0, &lPdfId,""); // <-- chiede il report //
	}
}

void CConsensoInformatoDynForm::OnPaint()
{
	CPaintDC dc(this);

	CRect rectTemp;
	GetDlgItem(IDC_STATIC_NUM)->GetWindowRect(rectTemp);
	ScreenToClient(rectTemp);
}
