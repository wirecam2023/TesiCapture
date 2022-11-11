#include "stdafx.h"
#include "Endox.h"
#include "GenomicaRicercaVarianteForm.h"
#include "afxdialogex.h"
#include "PatogenicitaSet.h"
#include "TipiAlterazioniSet.h"
#include "TipiVariantiGeneticheSet.h"
#include "GenomicaVariantiGeneticheDlg.h"
#include "VariantiGeneticheSet.h"
#include "GenomicaCorpoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGenomicaRicercaVarianteForm::CGenomicaRicercaVarianteForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(CGenomicaRicercaVarianteForm::IDD, pParent, pEsamiView)
{
	m_lBtnAdd = BTNADD_VARIANTI;
}

CGenomicaRicercaVarianteForm::~CGenomicaRicercaVarianteForm()
{
}

BEGIN_MESSAGE_MAP(CGenomicaRicercaVarianteForm, CEndoxDynForm)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_FIND, OnBnClickedBtnFind)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBnClickedBtnClear)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CGenomicaRicercaVarianteForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);
	
	
	DDX_Control(pDX, IDC_BTN_ADD, m_ctrlButtonAggiunge);
	DDX_Control(pDX, IDC_BTN_FIND, m_ctrlButtonTrova);
	DDX_Control(pDX, IDC_BTN_CLEAR, m_ctrlButtonLimpa);

	DDX_Control(pDX, IDC_PATOGENICITA, m_ctrlComboPatogenicita);
	DDX_Control(pDX, IDC_TIPOVARIANTE, m_ctrlComboTipoVariante);
	DDX_Control(pDX, IDC_TIPOALTERAZIONE, m_ctrlComboTipoAlterazione);	

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_7, m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC_8, m_ctrlStatic8);
	DDX_Control(pDX, IDC_STATIC_9, m_ctrlStatic9);
	DDX_Control(pDX, IDC_STATIC_10, m_ctrlStatic10);
	DDX_Control(pDX, IDC_STATIC_11, m_ctrlStatic11);
}

BOOL CGenomicaRicercaVarianteForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, CGenomicaRicercaVarianteForm** pForm, long lBtnAdd)
{
	BOOL bResult = FALSE;
	
	/*if ((*pForm) == NULL)
	{*/
		(*pForm) = new CGenomicaRicercaVarianteForm(NULL, pEsamiView);
		if ((*pForm) != NULL)
		{
			(*pForm)->m_lBtnAdd = lBtnAdd;

			(*pForm)->m_pParentFrame = pParentFrame;
			(*pForm)->m_lColore = -1;
			(*pForm)->m_lIDFaseBlocco = 2;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			(*pForm)->CreateChildForm(CGenomicaRicercaVarianteForm::IDD, pParent, rectFrame);
		}
	//}

	return bResult;
}

BOOL CGenomicaRicercaVarianteForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	if(m_lBtnAdd == BTNADD_DISABLE) m_ctrlButtonAggiunge.ShowWindow(SW_HIDE);

	RiempiCombos();

	theApp.LocalizeDialog(this, CGenomicaRicercaVarianteForm::IDD, "CGenomicaRicercaVarianteForm");
	return TRUE;
}

void CGenomicaRicercaVarianteForm::RiempiCombos()
{
	m_ctrlComboPatogenicita.ResetContent();
	m_ctrlComboTipoVariante.ResetContent();
	m_ctrlComboTipoAlterazione.ResetContent();

	CList<long> list;
	long nIndex = 0;

	CPatogenicitaSet().GetIDList(list);
	for (POSITION pos = list.GetHeadPosition(); pos;)
	{
		if (nIndex == 0)
		{
			m_ctrlComboPatogenicita.InsertString(nIndex, "");
			m_ctrlComboPatogenicita.SetItemData(nIndex, 0);
		}
		else
		{
			long lID = list.GetNext(pos);

			CString sCodice = CPatogenicitaSet().GetCodice(lID);
			CString sDesc = CPatogenicitaSet().GetDescrizione(lID);
			CString sValue = sDesc.IsEmpty() ? sCodice : sCodice + " - " + sDesc;

			m_ctrlComboPatogenicita.InsertString(nIndex, sValue);
			m_ctrlComboPatogenicita.SetItemData(nIndex, lID);
		}
		nIndex++;
	}

	nIndex = 0;
	list.RemoveAll();
	CTipiVariantiGeneticheSet().GetIDList(list);
	for (POSITION pos = list.GetHeadPosition(); pos;)
	{
		if (nIndex == 0)
		{
			m_ctrlComboTipoVariante.InsertString(nIndex, "");
			m_ctrlComboTipoVariante.SetItemData(nIndex, 0);
		}
		else
		{
			long lID = list.GetNext(pos);

			CString sCodice = CTipiVariantiGeneticheSet().GetCodice(lID);
			CString sDesc = CTipiVariantiGeneticheSet().GetDescrizione(lID);
			CString sValue = sDesc.IsEmpty() ? sCodice : sCodice + " - " + sDesc;

			m_ctrlComboTipoVariante.InsertString(nIndex, sValue);
			m_ctrlComboTipoVariante.SetItemData(nIndex, lID);
		}
		nIndex++;
	}

	nIndex = 0;
	list.RemoveAll();
	CTipiAlterazioniSet().GetIDList(list);
	for (POSITION pos = list.GetHeadPosition(); pos;)
	{
		if (nIndex == 0)
		{
			m_ctrlComboTipoAlterazione.InsertString(nIndex, "");
			m_ctrlComboTipoAlterazione.SetItemData(nIndex, 0);
		}
		else
		{
			long lID = list.GetNext(pos);

			CString sCodice = CTipiAlterazioniSet().GetCodice(lID);
			CString sDesc = CTipiAlterazioniSet().GetDescrizione(lID);
			CString sValue = sDesc.IsEmpty() ? sCodice : sCodice + " - " + sDesc;

			m_ctrlComboTipoAlterazione.InsertString(nIndex, sValue);
			m_ctrlComboTipoAlterazione.SetItemData(nIndex, lID);
		}
		nIndex++;
	}
}

void CGenomicaRicercaVarianteForm::OnBnClickedBtnAdd()
{
	CGenomicaVariantiGeneticheDlg dlgVar(m_pParentFrame, m_pEsamiView);
	CGenomicaCorpoDlg dlgCor(m_pParentFrame, m_pEsamiView);
	
	switch (m_lBtnAdd)
	{
	case BTNADD_VARIANTI:		
		dlgVar.DoModal();
		break;
	case BTNADD_CORPO:		
		dlgCor.DoModal();
		break;
	default:		
		dlgCor.DoModal();
		break;
	}	
}

void CGenomicaRicercaVarianteForm::OnBnClickedBtnClear()
{
	SetDlgItemText(IDC_TITOLO, "");
	SetDlgItemText(IDC_TRASCRIZIONE, "");
	SetDlgItemText(IDC_CROMOSSOMA, "");
	SetDlgItemText(IDC_GENE, "");
	SetDlgItemText(IDC_POSIZIONE, "");
	SetDlgItemText(IDC_CODICE, "");
	SetDlgItemText(IDC_HGVSC, "");
	SetDlgItemText(IDC_HGVSP, "");

	m_ctrlComboPatogenicita.SetCurSel(0);
	m_ctrlComboTipoVariante.SetCurSel(0);
	m_ctrlComboTipoAlterazione.SetCurSel(0);

	//OnBnClickedBtnFind();
}

void CGenomicaRicercaVarianteForm::OnBnClickedBtnFind()
{
	CString sTitolo;
	GetDlgItemText(IDC_TITOLO, sTitolo);

	CString sTrascrizione;
	GetDlgItemText(IDC_TRASCRIZIONE, sTrascrizione);

	CString sCromossoma;
	GetDlgItemText(IDC_CROMOSSOMA, sCromossoma);

	CString sGene;
	GetDlgItemText(IDC_GENE, sGene);

	CString sPosizione;
	GetDlgItemText(IDC_POSIZIONE, sPosizione);

	CString sCodice;
	GetDlgItemText(IDC_CODICE, sCodice);

	CString sHGVSc;
	GetDlgItemText(IDC_HGVSC, sHGVSc);

	CString sHGVSp;
	GetDlgItemText(IDC_HGVSP, sHGVSp);

	long lIDPatogenicita = (long)m_ctrlComboPatogenicita.GetItemData(m_ctrlComboPatogenicita.GetCurSel());
	long lIDTipoVariante = (long)m_ctrlComboTipoVariante.GetItemData(m_ctrlComboTipoVariante.GetCurSel());
	long lIDTipoAlterazione = (long)m_ctrlComboTipoAlterazione.GetItemData(m_ctrlComboTipoAlterazione.GetCurSel());

	CList<long> listID;
	CVariantiGeneticheSet().Filter(
		listID,
		sTitolo,
		lIDTipoVariante,
		sCodice,
		sTrascrizione,
		lIDPatogenicita,
		sCromossoma,
		sGene,
		sPosizione,
		lIDTipoAlterazione,
		sHGVSc,
		sHGVSp
		);
	
	if (listID.GetCount() == FILTER_MAX_COUNT)
	{
		CString sMessage;
		sMessage.Format(theApp.GetMessageString(IDS_GENOMICA_ERRO6), FILTER_MAX_COUNT);
		AfxMessageBox(sMessage);
	}

	GetParent()->SendMessage(WM_GENOMICA_FILTROVARIANTE, (WPARAM)&listID, (LPARAM)0);
}
