#include "stdafx.h"
#include "Endox.h"
#include "ExamListDlg.h"

#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExamListDlg::CExamListDlg(CWnd* pParent, CVistaEsamiPerWLSet* esamiSet, long* contatore)
	: CEndoxResizableDlg(CExamListDlg::IDD, pParent)
{
	m_pEsamiView = (CEsamiView*) pParent;
	m_pEsamiSet = esamiSet;
	m_pContatore = contatore;
}

CExamListDlg::~CExamListDlg()
{
}

BEGIN_MESSAGE_MAP(CExamListDlg, CEndoxResizableDlg)
	
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_EXAM_LIST, &CExamListDlg::OnLvnItemchangedExamList)
	ON_BN_CLICKED(IDC_NUOVO, &CExamListDlg::OnBnClickedNuovo)
	ON_NOTIFY(NM_DBLCLK, IDC_EXAM_LIST, &CExamListDlg::OnNMDblclkExamList)
END_MESSAGE_MAP()

void CExamListDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXAM_LIST,		m_ctrlList);
	DDX_Control(pDX, IDCANCEL,			m_ctrlButtonAnnulla);	
	DDX_Control(pDX, IDOK,				m_ctrlButtonOK);
}

BOOL CExamListDlg::OnInitDialog() 
{
	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_EXAM_LIST, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDCANCEL, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_NUOVO, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	m_ctrlList.InsertColumn(0, theApp.GetMessageString(IDS_CMB_TIPOESAME), LVCFMT_CENTER, 250);
	m_ctrlList.InsertColumn(1, theApp.GetMessageString(IDS_DATA), LVCFMT_CENTER, 250);
	m_ctrlList.InsertColumn(2, theApp.GetMessageString(IDS_RICETTEFORM_MEDICO), LVCFMT_CENTER, 200);
	m_ctrlList.InsertColumn(3, theApp.GetMessageString(IDS_EDT_SALAESAME), LVCFMT_CENTER, 200);
	m_ctrlList.InsertColumn(4, theApp.GetMessageString(IDS_BTN_CONVALIDATO), LVCFMT_CENTER, 100);

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	RiempiLista();

	m_ctrlButtonOK.EnableWindow(FALSE);

	theApp.LocalizeDialog(this, CExamListDlg::IDD, "ExamListDlg");
	return TRUE;
}

void CExamListDlg::OnOK() 
{
	if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
		*m_pContatore = m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

	m_iOperation = 2;

	CEndoxResizableDlg::OnOK();
}

void CExamListDlg::OnCancel() 
{
	*m_pContatore = -1;
	CEndoxResizableDlg::OnCancel();
}

void CExamListDlg::RiempiLista()
{
	while(!m_pEsamiSet->IsEOF())
	{
		//TODO: vanno mostrati in neretto i casi che non possono essere filtrati perché già erogati
		//strFilter.Format("select idesame from ext_esami_chiusi where eseguito = 1"); //not in

		int iItemInserted = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), "", 0);
		m_ctrlList.SetItemData(iItemInserted, m_pEsamiSet->m_lContatore);
		CString temp;
		m_ctrlList.SetItemText(iItemInserted, 0, m_pEsamiSet->m_sDescrizione);
		temp.Format("%s/%s/%s", m_pEsamiSet->m_sDataEsame.Right(2), m_pEsamiSet->m_sDataEsame.Mid(4,2), m_pEsamiSet->m_sDataEsame.Left(4));
		m_ctrlList.SetItemText(iItemInserted, 1, temp);
		m_ctrlList.SetItemText(iItemInserted, 2, m_pEsamiSet->m_sMedico);
		m_ctrlList.SetItemText(iItemInserted, 3, m_pEsamiSet->m_sSalaEsame);
		if (m_pEsamiSet->m_bSuperLocked)
			m_ctrlList.SetItemText(iItemInserted, 4, "SI");
		else
			m_ctrlList.SetItemText(iItemInserted, 4, "NO");

		m_pEsamiSet->MoveNext();
	}

	m_ctrlList.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}

void CExamListDlg::OnLvnItemchangedExamList(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
		m_ctrlButtonOK.EnableWindow(TRUE);
	else
		m_ctrlButtonOK.EnableWindow(FALSE);
}

void CExamListDlg::OnBnClickedNuovo()
{
	m_iOperation = 1;

	CEndoxResizableDlg::OnOK();
}


void CExamListDlg::OnNMDblclkExamList(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
		OnOK();
}
