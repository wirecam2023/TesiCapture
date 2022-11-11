#include "stdafx.h"
#include "Endox.h"
#include "FleurySceltaRiaperturaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFleurySceltaRiaperturaDlg, CDialog)

CFleurySceltaRiaperturaDlg::CFleurySceltaRiaperturaDlg(CWnd* pParent, CString p_sFichaItem)
	: CDialog(CFleurySceltaRiaperturaDlg::IDD, pParent)
{
	m_sFicha = p_sFichaItem.Left(10);
	
	p_sFichaItem.Replace(p_sFichaItem.Left(10) + "_", "");
	p_sFichaItem.Replace("_", "0");

	m_sItem = p_sFichaItem;

}

CFleurySceltaRiaperturaDlg::~CFleurySceltaRiaperturaDlg()
{
}

BEGIN_MESSAGE_MAP(CFleurySceltaRiaperturaDlg, CDialog)	
	ON_BN_CLICKED(IDC_BTN_IMPRIMIR, &CFleurySceltaRiaperturaDlg::OnBnClickedBtnImprimir)
	ON_BN_CLICKED(IDC_BTN_IMAGENS, &CFleurySceltaRiaperturaDlg::OnBnClickedBtnImagens)
	ON_BN_CLICKED(IDOK, &CFleurySceltaRiaperturaDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFleurySceltaRiaperturaDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_IMPRIMIR_TODOS, &CFleurySceltaRiaperturaDlg::OnBnClickedBtnImprimirTodos)
END_MESSAGE_MAP()

void CFleurySceltaRiaperturaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_IMPRIMIR, m_ctrlBtImprimirLaudo);
	DDX_Control(pDX, IDC_BTN_IMAGENS, m_ctrlBtImprimirImagens);
	DDX_Control(pDX, IDOK, m_ctrlBtnAlterarExame);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
}

BOOL CFleurySceltaRiaperturaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CFleurySceltaRiaperturaDlg::IDD, "FleurySceltaRiaperturaDlg");

	CString title;
	title.Format(theApp.GetMessageString(IDS_FLEURY_SCELTA_001), m_sFicha, m_sItem);
	m_ctrlStatic00.SetWindowTextA(title);
	
	m_ctrlBtImprimirLaudo.SetFont(&theApp.m_fontNormal);
	m_ctrlBtImprimirImagens.SetFont(&theApp.m_fontNormal);
	m_ctrlBtnAlterarExame.SetFont(&theApp.m_fontNormal);

	m_ctrlStatic00.SetFont(&theApp.m_fontNormal);


	
	return TRUE;
}

void CFleurySceltaRiaperturaDlg::OnBnClickedBtnImprimir()
{
	m_bImprimirLaudo = TRUE;
	m_bImprimirImagens = FALSE;
	m_bImportarExame = FALSE;
	
	CDialog::OnOK();
}


void CFleurySceltaRiaperturaDlg::OnBnClickedBtnImagens()
{
	m_bImprimirLaudo = FALSE;
	m_bImprimirImagens = TRUE;
	m_bImportarExame = FALSE;

	CDialog::OnOK();
}


void CFleurySceltaRiaperturaDlg::OnBnClickedOk()
{	
	m_bImprimirLaudo = FALSE;
	m_bImprimirImagens = FALSE;
	m_bImportarExame = TRUE;

	CDialog::OnOK();
}
void CFleurySceltaRiaperturaDlg::OnBnClickedCancel()
{
	m_bImprimirLaudo = FALSE;
	m_bImprimirImagens = FALSE;
	m_bImportarExame = FALSE;

	CDialog::OnCancel();
}

void CFleurySceltaRiaperturaDlg::OnBnClickedBtnImprimirTodos()
{
	m_bImprimirLaudo = TRUE;
	m_bImprimirImagens = TRUE;
	m_bImportarExame = FALSE;
	CDialog::OnOK();
}
