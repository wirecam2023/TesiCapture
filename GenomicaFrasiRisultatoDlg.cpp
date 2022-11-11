#include "stdafx.h"
#include "Endox.h"
#include "GenomicaFrasiRisultatoDlg.h"
#include "FrasiRisultatoSet.h"
#include "TipiVariantiGeneticheSet.h" //Julio BUG 3791 - Melhoria frases resultado laudo genomica
#include "PatogenicitaSet.h" //Julio BUG 3791 - Melhoria frases resultado laudo genomica

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGenomicaFrasiRisultatoDlg, CDialog)

CGenomicaFrasiRisultatoDlg::CGenomicaFrasiRisultatoDlg(CWnd* pParent)
	: CDialog(CGenomicaFrasiRisultatoDlg::IDD, pParent)
{
	m_lIDTipoVarianteSelected = 0; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
}

CGenomicaFrasiRisultatoDlg::~CGenomicaFrasiRisultatoDlg()
{
}

BEGIN_MESSAGE_MAP(CGenomicaFrasiRisultatoDlg, CDialog)		
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)	
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)	
	ON_CBN_SELCHANGE(IDC_TIPOVARIANTE, OnCbnSelchange) //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	ON_CBN_SELCHANGE(IDC_PATOGENICITA, OnCbnSelchange) //Julio BUG 3791 - Melhoria frases resultado laudo genomica
END_MESSAGE_MAP()

void CGenomicaFrasiRisultatoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlButtonEdit);

	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_STATIC1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC4, m_ctrlStatic4);	
	DDX_Control(pDX, IDC_STATIC5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC7, m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC8, m_ctrlStatic8);
	DDX_Control(pDX, IDC_STATIC9, m_ctrlStatic9);
	DDX_Control(pDX, IDC_STATIC10, m_ctrlStatic10);
	DDX_Control(pDX, IDC_STATIC11, m_ctrlStatic11);
	DDX_Control(pDX, IDC_STATIC12, m_ctrlStatic12);	//Julio BUG 3791 - Melhoria frases resultado laudo genomica

	DDX_Control(pDX, IDC_TIPOVARIANTE, m_ctrlComboTipoVariante); //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	//DDX_Control(pDX, IDC_PATOGENICITA, m_ctrlComboPatogenicita); //Julio BUG 3791 - Melhoria frases resultado laudo genomica	
}

BOOL CGenomicaFrasiRisultatoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	EditDialog(FALSE);	

	RiempiCombos(); //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	CaricaDati();
	
	theApp.LocalizeDialog(this, CGenomicaFrasiRisultatoDlg::IDD, "CGenomicaFrasiRisultatoDlg");
	return TRUE;
}


void CGenomicaFrasiRisultatoDlg::OnOK()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnOK();
}

void CGenomicaFrasiRisultatoDlg::OnCancel()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}

void CGenomicaFrasiRisultatoDlg::CaricaDati()
{
	GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
	
	SetDlgItemText(IDC_RISULTATO, "");
	SetDlgItemText(IDC_COMPLEMENTO, "");
	SetDlgItemText(IDC_POSITIVO_SINGOLARE, "");
	SetDlgItemText(IDC_POSITIVO_PLURALE, "");
	SetDlgItemText(IDC_POSITIVO_VARIANTI, "");
	SetDlgItemText(IDC_NEGATIVO_SINGOLARE, "");	
	SetDlgItemText(IDC_COMPLEMENTO_SINGOLARE, "");
	SetDlgItemText(IDC_COMPLEMENTO_PLURALE, "");
	SetDlgItemText(IDC_COMPLEMENTO_NEGATIVO, "");
	SetDlgItemText(IDC_COMPLEMENTO_VARIANTI, "");
	SetDlgItemText(IDC_NEGATIVO_NEGATIVO, "");
	
	//Julio BUG 3791 - Melhoria frases resultado laudo genomica
	CString sRisultato = CFrasiRisultatoSet().GetTitoloRisultato();
	CString sComplmento = CFrasiRisultatoSet().GetTitoloComplemento();

	CString sPosSing = CFrasiRisultatoSet().GetPositivoSingolare();
	CString sPosPlur = CFrasiRisultatoSet().GetPositivoPlurale();
	CString sPosVari = CFrasiRisultatoSet().GetPositivoVariante(/*m_lIDPatogenicita*/);
	CString sNegSing = CFrasiRisultatoSet().GetNegativoSingolare();
	CString sNegNeg = CFrasiRisultatoSet().GetNegativoNegativo();
	
	CString sComSing = CFrasiRisultatoSet().GetComplementoSingolare(m_lIDTipoVarianteSelected);
	CString sComPlur = CFrasiRisultatoSet().GetComplementoPlurale(m_lIDTipoVarianteSelected);
	CString sComVari = CFrasiRisultatoSet().GetComplementoVariante(m_lIDTipoVarianteSelected);
	CString sComNeg = CFrasiRisultatoSet().GetComplementoNegativo(m_lIDTipoVarianteSelected);
	//

	SetDlgItemText(IDC_RISULTATO, sRisultato);
	SetDlgItemText(IDC_COMPLEMENTO, sComplmento);
	SetDlgItemText(IDC_POSITIVO_SINGOLARE, sPosSing);
	SetDlgItemText(IDC_POSITIVO_PLURALE, sPosPlur);
	SetDlgItemText(IDC_POSITIVO_VARIANTI, sPosVari);
	SetDlgItemText(IDC_NEGATIVO_SINGOLARE, sNegSing);	
	SetDlgItemText(IDC_COMPLEMENTO_SINGOLARE, sComSing);
	SetDlgItemText(IDC_COMPLEMENTO_PLURALE, sComPlur);
	SetDlgItemText(IDC_COMPLEMENTO_NEGATIVO, sComNeg);
	SetDlgItemText(IDC_COMPLEMENTO_VARIANTI, sComVari);
	SetDlgItemText(IDC_NEGATIVO_NEGATIVO, sNegNeg);

	//

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);	
}

//Julio BUG 3791 - Melhoria frases resultado laudo genomica
void CGenomicaFrasiRisultatoDlg::RiempiCombos()
{	
	m_ctrlComboTipoVariante.ResetContent();
	
	CList<long> list;
	long nIndex = 0;

	CTipiVariantiGeneticheSet().GetIDList(list);
	for (POSITION pos = list.GetHeadPosition(); pos;)
	{
		long lID = list.GetNext(pos);

		CString sCodice = CTipiVariantiGeneticheSet().GetCodice(lID);
		CString sDesc = CTipiVariantiGeneticheSet().GetDescrizione(lID);
		CString sValue = sDesc.IsEmpty() ? sCodice : sCodice + " - " + sDesc;

		m_ctrlComboTipoVariante.InsertString(nIndex, sValue);
		m_ctrlComboTipoVariante.SetItemData(nIndex, lID);		
		nIndex++;
	}
	
	if (nIndex > 0)
		m_ctrlComboTipoVariante.SetCurSel(0);

	m_lIDTipoVarianteSelected = (long)m_ctrlComboTipoVariante.GetItemData(m_ctrlComboTipoVariante.GetCurSel());	

	//

	/*m_ctrlComboPatogenicita.ResetContent();

	list.RemoveAll();
	nIndex = 0;

	CPatogenicitaSet().GetIDList(list);
	for (POSITION pos = list.GetHeadPosition(); pos;)
	{
		long lID = list.GetNext(pos);

		if (CPatogenicitaSet().GetPositivita(lID))
		{
			CString sCodice = CPatogenicitaSet().GetCodice(lID);
			CString sDesc = CPatogenicitaSet().GetDescrizione(lID);
			CString sValue = sDesc.IsEmpty() ? sCodice : sCodice + " - " + sDesc;

			m_ctrlComboPatogenicita.InsertString(nIndex, sValue);
			m_ctrlComboPatogenicita.SetItemData(nIndex, lID);
			nIndex++;
		}
	}

	if (nIndex > 0)
		m_ctrlComboPatogenicita.SetCurSel(0);

	m_lIDPatogenicita = (long)m_ctrlComboPatogenicita.GetItemData(m_ctrlComboPatogenicita.GetCurSel());*/
}

void CGenomicaFrasiRisultatoDlg::EditDialog(BOOL bEdit)
{	
	SendDlgItemMessage(IDC_COMPLEMENTO, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_RISULTATO, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_POSITIVO_SINGOLARE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_POSITIVO_PLURALE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_POSITIVO_VARIANTI, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_NEGATIVO_SINGOLARE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);		
	SendDlgItemMessage(IDC_COMPLEMENTO_SINGOLARE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_COMPLEMENTO_PLURALE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_COMPLEMENTO_NEGATIVO, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);	
	SendDlgItemMessage(IDC_COMPLEMENTO_VARIANTI, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_NEGATIVO_NEGATIVO, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	
	m_ctrlComboTipoVariante.EnableWindow(TRUE); //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	//m_ctrlComboPatogenicita.EnableWindow(TRUE); //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit));	
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);	
}

void CGenomicaFrasiRisultatoDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}
void CGenomicaFrasiRisultatoDlg::OnBnClickedBtnUndo()
{	
	EditDialog(FALSE);
}
void CGenomicaFrasiRisultatoDlg::OnBnClickedBtnSave()
{
	if (!UpdateData(TRUE))
		return;

	CString sRisultato, sComplemento,
		sPosSing, sPosPlur, sPosVari,
		sComSing, sComPlur, sComVari,
		sNegSing, sNegNeg, sComNeg;

	GetDlgItemText(IDC_RISULTATO, sRisultato);
	GetDlgItemText(IDC_COMPLEMENTO, sComplemento);
	GetDlgItemText(IDC_POSITIVO_SINGOLARE, sPosSing);
	GetDlgItemText(IDC_POSITIVO_PLURALE, sPosPlur);
	GetDlgItemText(IDC_POSITIVO_VARIANTI, sPosVari);
	GetDlgItemText(IDC_NEGATIVO_SINGOLARE, sNegSing);	
	GetDlgItemText(IDC_COMPLEMENTO_SINGOLARE, sComSing);
	GetDlgItemText(IDC_COMPLEMENTO_PLURALE, sComPlur);
	GetDlgItemText(IDC_COMPLEMENTO_NEGATIVO, sComNeg);
	GetDlgItemText(IDC_COMPLEMENTO_VARIANTI, sComVari);
	GetDlgItemText(IDC_NEGATIVO_NEGATIVO, sNegNeg);

	
	//Julio BUG 3791 - Melhoria frases resultado laudo genomica
	CFrasiRisultatoSet().SetTitoloRisultato(sRisultato);
	CFrasiRisultatoSet().SetTitoloComplemento(sComplemento);

	CFrasiRisultatoSet().SetPositivoSingolare(sPosSing);
	CFrasiRisultatoSet().SetPositivoPlurale(sPosPlur);
	CFrasiRisultatoSet().SetPositivoVariante(/*m_lIDPatogenicita,*/ sPosVari);
	CFrasiRisultatoSet().SetNegativoSingolare(sNegSing);
	CFrasiRisultatoSet().SetNegativoNegativo(sNegNeg);
						 
	CFrasiRisultatoSet().SetComplementoSingolare(m_lIDTipoVarianteSelected, sComSing);
	CFrasiRisultatoSet().SetComplementoPlurale(m_lIDTipoVarianteSelected, sComPlur);
	CFrasiRisultatoSet().SetComplementoVariante(m_lIDTipoVarianteSelected, sComVari);
	CFrasiRisultatoSet().SetComplementoNegativo(m_lIDTipoVarianteSelected, sComNeg);
	//	

	EditDialog(FALSE);	

	CaricaDati();
}

//Julio BUG 3791 - Melhoria frases resultado laudo genomica
void CGenomicaFrasiRisultatoDlg::OnCbnSelchange()
{	
	m_lIDTipoVarianteSelected = (long)m_ctrlComboTipoVariante.GetItemData(m_ctrlComboTipoVariante.GetCurSel());
	//m_lIDPatogenicita = (long)m_ctrlComboPatogenicita.GetItemData(m_ctrlComboPatogenicita.GetCurSel());

	CaricaDati();
}