// Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO
// Luiz - 01/07/2019 - P3 - Permitir combobox de variáveis de laudo exibir até 200 caracteres
#include "stdafx.h"
#include "Endox.h"
#include "DialogWithResizableCombo.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// TODO: REFACTORING POSSIBILITY : reavaliar necessidade de 5 FORMS / tentar a abordagem de redimensionar um único
const UINT CDialogWithResizableCombo::m_uiIDD[5] = { IDD_SELECT_COMBO_GRANDE_50,
											   	     IDD_SELECT_COMBO_GRANDE_80,
												     IDD_SELECT_COMBO_GRANDE_100,
												     IDD_SELECT_COMBO_GRANDE_150,
												     IDD_SELECT_COMBO_GRANDE_200 };

IMPLEMENT_DYNAMIC(CDialogWithResizableCombo, CDialog)

CDialogWithResizableCombo::CDialogWithResizableCombo(CWnd* pParent, const CString &sTitle, CString *sArray, long lArraySize, long lRectSize, BOOL p_bAddImgButton)
: CDialog(m_uiIDD[lRectSize], pParent)
{
	m_sTitle = sTitle;
	m_sArray = sArray;
	m_lArraySize = lArraySize;
	m_pEsamiView = NULL;
	m_bShowImgButton = p_bAddImgButton;
	m_lRectSize = lRectSize;
}

CDialogWithResizableCombo::CDialogWithResizableCombo() : CDialog(m_uiIDD[0], NULL) { }


CDialogWithResizableCombo::~CDialogWithResizableCombo()
{
}

long CDialogWithResizableCombo::GetRectSize(CString sTesto)
{
	//int iMaxWidth = GetSystemMetrics(SM_CXSCREEN);
	int iMaxHeight = GetSystemMetrics(SM_CYSCREEN);
	long lRetorno = 0;
	if (iMaxHeight <= 800)
	{
		if (sTesto.GetLength() > 100)
			lRetorno = 3;
		else if (sTesto.GetLength() > 80)
			lRetorno = 2;
		else if (sTesto.GetLength() > 50)
			lRetorno = 1;
		else
			lRetorno = 0;
	}
	else
	{
		if (sTesto.GetLength() > 150)
			lRetorno = 4;
		else if (sTesto.GetLength() > 100)
			lRetorno = 3;
		else if (sTesto.GetLength() > 80)
			lRetorno = 2;
		else if (sTesto.GetLength() > 50)
			lRetorno = 1;
		else
			lRetorno = 0;
	}
	return lRetorno;
}

void CDialogWithResizableCombo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_1, m_ctrlCombo1);
	DDX_Control(pDX, IDC_BTN_IMM, m_ctrlButtonImm); // Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOk);
}

BEGIN_MESSAGE_MAP(CDialogWithResizableCombo, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_1, &CDialogWithResizableCombo::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BTN_IMM, &CDialogWithResizableCombo::OnBnClickedBtnImm) // Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO
END_MESSAGE_MAP()

BOOL CDialogWithResizableCombo::OnInitDialog()
{

	BOOL bReturn = CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, m_uiIDD[m_lRectSize], "DialogWithResizableCombo");  // Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO

	SetDlgItemText(IDC_COMBO_1, m_sValue); // Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO

	if (!m_sTitle.IsEmpty())
		SetWindowText(m_sTitle);

	for (int i = 0; i < m_lArraySize; i++)
	{
		int nIndex = m_ctrlCombo1.AddString(m_sArray[i]);
	}

	if (m_lArraySize > 0)
	{
		m_ctrlCombo1.SetCurSel(0);
		m_ctrlBtnOk.EnableWindow(m_ctrlCombo1.GetCurSel() >= 0);
	}

	GetDlgItem(IDC_BTN_IMM)->ShowWindow(m_bShowImgButton ? SW_SHOW : SW_HIDE);
	if (m_bShowImgButton) {
		if (GetDlgItem(IDC_BTN_IMM)) {
			// Img Button depends on m_pEsamiView
			GetDlgItem(IDC_BTN_IMM)->EnableWindow(m_pEsamiView != NULL);
		}
	}

	return bReturn;
}

BOOL CDialogWithResizableCombo::SetEsamiView(CEsamiView* pEsamiView)
{
	m_pEsamiView = pEsamiView; // Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO
	return TRUE;
}

void CDialogWithResizableCombo::OnOK()
{
	GetDlgItemText(IDC_EDIT_VALUE, m_sValue);  // Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO

	int nIndex = m_ctrlCombo1.GetCurSel();

	m_ctrlCombo1.GetLBText(nIndex, m_sSelectedItem);

	m_sArray = NULL;
	delete(m_sArray);

	CDialog::OnOK();
}

void CDialogWithResizableCombo::OnCbnSelchangeCombo1()
{
	m_ctrlBtnOk.EnableWindow(m_ctrlCombo1.GetCurSel() >= 0);
}

// Marvel Carvalho - Bug 4216 botão IMG na pop-up do @COMBO
void CDialogWithResizableCombo::OnBnClickedBtnImm()
{
	CRect rect;
	GetWindowRect(&rect);
	int x = rect.TopLeft().x;
	int y = rect.TopLeft().y;

	//MoveWindow(x, 50, rect.Width(), rect.Height(), TRUE);
	//Invalidate();
	//UpdateWindow();

	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#1 - dual screen)
	// TODO: Ver se precisa colocar aqui também
	if (m_pEsamiView != NULL)
	{
		CImageSimple2Dlg* pDlgImageSimple2 = new CImageSimple2Dlg(this, m_pEsamiView, TRUE);
		if (pDlgImageSimple2->Create(IDD_IMAGE_SIMPLE2, this))
			pDlgImageSimple2->ShowWindow(SW_SHOWNORMAL);
		else
			delete pDlgImageSimple2;
	}
}
// CDialogWithResizableCombo message handlers