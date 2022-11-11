#include "stdafx.h"
#include "Endox.h"
#include "GenomicaCorpoDlg.h"
#include "VariantiGeneticheSet.h"
#include "SezioniSet.h"
#include "TipiVariantiGeneticheSet.h"
#include "PatogenicitaSet.h"
#include "TipiAlterazioniSet.h"
#include "CorpoSezioneSet.h"
#include "VistaVariantiGeneticheSet.h"
#include "TipiRefertoSet.h"
#include "VistaRefertoGenomicaSet.h"

#include "GenomicaRefertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGenomicaCorpoDlg, CDialog)

CGenomicaCorpoDlg::CGenomicaCorpoDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CGenomicaCorpoDlg::IDD, pParent)
{
	m_pEsamiView = pEsamiView;

	m_lIDSezioneSelected = -1;
	m_lIDVarianteSelected = -1;
}

CGenomicaCorpoDlg::~CGenomicaCorpoDlg()
{
}

BEGIN_MESSAGE_MAP(CGenomicaCorpoDlg, CDialog)
	ON_MESSAGE(WM_GENOMICA_FILTROVARIANTE, ProccessVarianteFilter)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_VARIANTI, OnLvnItemchangedListVarianti)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SEZIONI, OnLvnItemchangedListSezioni)

	//ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)

	ON_COMMAND(IDC_RTF_TABLE, OnBnClickedBtnRtfNewTable)
	ON_COMMAND(IDC_RTF_MAKEUPPER, OnBnClickedBtnRtfMakeUpper)
	ON_COMMAND(IDC_RTF_MAKENORMAL, OnBnClickedBtnRtfMakeNormal)
	ON_COMMAND(IDC_RTF_MAKELOWER, OnBnClickedBtnRtfMakeLower)
	ON_COMMAND(IDC_RTF_FONT, OnBnClickedBtnRtfFont) //Julio - BUG 4392 Edicao de texto

END_MESSAGE_MAP()

void CGenomicaCorpoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//DDX_Control(pDX, IDC_BTN_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlButtonEdit);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_RICERCA_PLACE, m_ctrlStaticRicercaForm);

	DDX_Control(pDX, IDC_LIST_VARIANTI, m_ctrlListVarianti);
	DDX_Control(pDX, IDC_LIST_SEZIONI, m_ctrlListSezioni);

	DDX_Control(pDX, IDC_BUTTONBAR, m_ctrlButtonBar);

	DDX_Control(pDX, IDC_TEXTCONTROL_HIDE, m_ctrlTextControlHide);
	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //	
}


BOOL CGenomicaCorpoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlListVarianti.SetExtendedStyle(m_ctrlListVarianti.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlListVarianti.InsertColumn(0, "Titolo", LVCFMT_LEFT, 0);
	m_ctrlListVarianti.InsertColumn(1, "Tipo variante", LVCFMT_LEFT, 0);
	m_ctrlListVarianti.InsertColumn(2, "Trascrizione", LVCFMT_LEFT, 0);
	m_ctrlListVarianti.InsertColumn(3, "Cromossoma", LVCFMT_LEFT, 0);
	m_ctrlListVarianti.InsertColumn(4, "Gene", LVCFMT_LEFT, 0);
	m_ctrlListVarianti.InsertColumn(5, "Posizione", LVCFMT_LEFT, 0);
	m_ctrlListVarianti.InsertColumn(6, "Codice", LVCFMT_LEFT, 0);
	m_ctrlListVarianti.InsertColumn(7, "Tipo alterazione", LVCFMT_LEFT, 0);
	m_ctrlListVarianti.InsertColumn(8, "HGVSc", LVCFMT_LEFT, 0);
	m_ctrlListVarianti.InsertColumn(9, "HGVSp", LVCFMT_LEFT, 0);
	m_ctrlListVarianti.InsertColumn(10, "Patogenicita", LVCFMT_LEFT, 0);
	
	m_ctrlListSezioni.SetExtendedStyle(m_ctrlListSezioni.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlListSezioni.InsertColumn(0, "Codice", LVCFMT_LEFT, 0);

	RiempiLista();

	m_ctrlToolbar.Create(IDC_BUTTONBAR_PLACE, this);
	m_ctrlToolbar.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	// tolgo i flag WS_CLIPCHILDREN e WS_CLIPSIBLINGS dallo stile della barra //
	::SetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE, (GetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE) & ~WS_CLIPCHILDREN) & ~WS_CLIPSIBLINGS);

	m_ctrlTextControl.SetButtonBarHandle((long)m_ctrlButtonBar.GetSafeHwnd());
	m_ctrlTextControl.SetFontName(g_sReportFaceName);
	m_ctrlTextControl.SetFontSize(g_nReportSize);
	m_ctrlTextControl.SetFontBold(g_bReportBold);
	m_ctrlTextControl.SetFontItalic(g_bReportItalic);
	m_ctrlTextControl.SetFontUnderline(g_bReportUnderline);

	m_ctrlTextControl.EnableWindow(FALSE);
	m_ctrlToolbar.EnableWindow(FALSE);
	m_ctrlButtonBar.EnableWindow(FALSE);
//	GetDlgItem(IDC_BTN_NEW)->EnableWindow(FALSE);

	m_ctrlTextControlHide.EnableWindow(FALSE);	

	EditDialog(FALSE);
	
	CGenomicaRicercaVarianteForm::CreateFormEx(this, &m_ctrlStaticRicercaForm, m_pEsamiView, &m_pRicercaForm, BTNADD_VARIANTI);

	theApp.LocalizeDialog(this, CGenomicaCorpoDlg::IDD, "CGenomicaCorpoDlg");
	return TRUE;
}

void CGenomicaCorpoDlg::OnOK()
{		
	if (GetFocus() == GetDlgItem(IDOK))
		CDialog::OnOK();
	
	else if (GetDlgItem(IDOK)->IsWindowEnabled())	
		m_pRicercaForm->OnBnClickedBtnFind();		
}

void CGenomicaCorpoDlg::OnCancel()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}

void CGenomicaCorpoDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlListSezioni.SetRedraw(FALSE);
	m_ctrlListSezioni.DeleteAllItems();

	CList<long> listID;
	CSezioniSet().GetIDList(listID);

	for (POSITION pos = listID.GetHeadPosition(); pos;)
	{
		long lID = listID.GetNext(pos);

		int nItem = m_ctrlListSezioni.InsertItem(m_ctrlListSezioni.GetItemCount(), CSezioniSet().GetCodice(lID));
		m_ctrlListSezioni.SetItemData(nItem, (DWORD)lID);
	}

	m_ctrlListSezioni.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);	
	m_ctrlListSezioni.SetRedraw(TRUE);

	/*m_ctrlListVarianti.SetRedraw(FALSE);
	m_ctrlListVarianti.DeleteAllItems();

	listID.RemoveAll();
	CVariantiGeneticheSet().GetIDList(listID);
	
	for (POSITION pos = listID.GetHeadPosition(); pos;)
	{
		long lID = listID.GetNext(pos);
		
		int nItem = m_ctrlListVarianti.InsertItem(m_ctrlListVarianti.GetItemCount(), CVariantiGeneticheSet().GetTitolo(lID));
		m_ctrlListVarianti.SetItemText(nItem, 1, CTipiVariantiGeneticheSet().GetCodice(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
		m_ctrlListVarianti.SetItemText(nItem, 2, CVariantiGeneticheSet().GetTrascrizione(lID));
		m_ctrlListVarianti.SetItemText(nItem, 3, CVariantiGeneticheSet().GetCromossoma(lID));
		m_ctrlListVarianti.SetItemText(nItem, 4, CVariantiGeneticheSet().GetGene(lID));
		m_ctrlListVarianti.SetItemText(nItem, 5, CVariantiGeneticheSet().GetPosizioneGene(lID));
		m_ctrlListVarianti.SetItemText(nItem, 6, CVariantiGeneticheSet().GetCodice(lID));
		m_ctrlListVarianti.SetItemText(nItem, 7, CTipiAlterazioniSet().GetCodice(CVariantiGeneticheSet().GetIDTipoAlterazione(lID)));
		m_ctrlListVarianti.SetItemText(nItem, 8, CVariantiGeneticheSet().GetHGVSc(lID));
		m_ctrlListVarianti.SetItemText(nItem, 9, CVariantiGeneticheSet().GetHGVSp(lID));
		m_ctrlListVarianti.SetItemText(nItem, 10, CPatogenicitaSet().GetCodice(CVariantiGeneticheSet().GetIDPatogenicita(lID)));
		m_ctrlListVarianti.SetItemData(nItem, (DWORD)lID);
	}

	m_ctrlListVarianti.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListVarianti.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListVarianti.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListVarianti.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListVarianti.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListVarianti.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListVarianti.SetColumnWidth(6, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListVarianti.SetColumnWidth(7, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListVarianti.SetColumnWidth(8, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListVarianti.SetColumnWidth(9, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListVarianti.SetColumnWidth(10, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListVarianti.SetRedraw(TRUE);*/
	EndWaitCursor();
}

void CGenomicaCorpoDlg::CaricaDati()
{
	GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
	
	m_ctrlTextControl.ResetContents();
	m_ctrlTextControlHide.ResetContents();

	//

	m_ctrlTextControl.SetRTFSelText(CCorpoSezioneSet().GetCorpoRtf(m_lIDSezioneSelected, m_lIDVarianteSelected));
	m_ctrlTextControlHide.SetRTFSelText(CCorpoSezioneSet().GetCorpoRtf(m_lIDSezioneSelected, m_lIDVarianteSelected));

	//

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
}

void CGenomicaCorpoDlg::UnselectAll()
{
	if (m_ctrlListSezioni.GetItemCount() > 0)
	{
		for (int i = 0; i < m_ctrlListSezioni.GetItemCount(); i++)
			m_ctrlListSezioni.SetItemState(i, 0, LVIS_SELECTED);
	}
	else
	{
		OnLvnItemchangedListSezioni(NULL, NULL);
	}
	
	if (m_ctrlListVarianti.GetItemCount() > 0)
	{
		for (int i = 0; i < m_ctrlListVarianti.GetItemCount(); i++)
			m_ctrlListVarianti.SetItemState(i, 0, LVIS_SELECTED);
	}
	else
	{
		OnLvnItemchangedListVarianti(NULL, NULL);
	}

}

void CGenomicaCorpoDlg::EditDialog(BOOL bEdit)
{
	m_ctrlListVarianti.EnableWindow(!bEdit);
	m_ctrlListSezioni.EnableWindow(!bEdit);	
	m_ctrlTextControl.EnableWindow(bEdit);
	m_ctrlToolbar.EnableWindow(bEdit);
	m_ctrlButtonBar.EnableWindow(bEdit);
	//GetDlgItem(IDC_BTN_NEW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit) && (m_lIDSezioneSelected > 0 && m_lIDVarianteSelected > 0) /*(m_ctrlListSezioni.GetFirstSelectedItemPosition() != NULL && m_ctrlListVarianti.GetFirstSelectedItemPosition() != NULL)*/);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!bEdit) && (m_lIDSezioneSelected > 0 && m_lIDVarianteSelected > 0) /*(m_ctrlListSezioni.GetFirstSelectedItemPosition() != NULL && m_ctrlListVarianti.GetFirstSelectedItemPosition() != NULL)*/);
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);
}


// CGenomicaCorpoDlg message handlers
/*void CGenomicaCorpoDlg::OnBnClickedBtnNew()
{
	UnselectAll();
	EditDialog(TRUE);
}*/

void CGenomicaCorpoDlg::OnBnClickedBtnEdt()
{
	if (m_lIDSezioneSelected > 0 && m_lIDVarianteSelected > 0)
	{
		EditDialog(TRUE);
		CaricaSuggerimenti();
	}
}

void CGenomicaCorpoDlg::OnBnClickedBtnDel()
{
	if (AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		if (m_lIDSezioneSelected > 0 && m_lIDVarianteSelected > 0)
		{
			if (!CCorpoSezioneSet().SetEliminato(m_lIDSezioneSelected, m_lIDVarianteSelected))
				AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO1));
		}
		UnselectAll();
		RiempiLista();
	}
}

void CGenomicaCorpoDlg::OnBnClickedBtnUndo()
{
	UnselectAll();
	RiempiLista();
	EditDialog(FALSE);
}

void CGenomicaCorpoDlg::OnBnClickedBtnSave()
{
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);

	if (!UpdateData(TRUE))
		return;

	if (m_lIDSezioneSelected > 0 && m_lIDVarianteSelected > 0)
	{
		// addnew //
		CString sFilter;
		CCorpoSezioneSet setTemp;
		
		sFilter.Format("IDSezione=%li AND IDVariante=%li", m_lIDSezioneSelected, m_lIDVarianteSelected);
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CGenomicaCorpoDlg::OnBnClickedBtnSave"))
		{
			if (setTemp.IsEOF())
			{
				if (setTemp.AddNewRecordset("CGenomicaCorpoDlg::OnBnClickedBtnSave"))
				{
					setTemp.m_lIDSezione = m_lIDSezioneSelected;
					setTemp.m_lIDVariante = m_lIDVarianteSelected;
					setTemp.m_sCorpoRtf = m_ctrlTextControl.GetRTFSelText();
					setTemp.m_bEliminato = FALSE;

					setTemp.UpdateRecordset("CGenomicaCorpoDlg::OnBnClickedBtnSave");
				}			
			}
			setTemp.CloseRecordset("CGenomicaCorpoDlg::OnBnClickedBtnSave");
		}
		
		CCorpoSezioneSet().SetCorpoRtf(m_lIDSezioneSelected, m_lIDVarianteSelected, m_ctrlTextControl.GetRTFSelText());
	}
	else
		AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO2));
		
	
	//UnselectAll();
	//RiempiLista();
	EditDialog(FALSE);
	
}

void CGenomicaCorpoDlg::OnLvnItemchangedListVarianti(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lIDVarianteSelected = -1;
	POSITION pos = m_ctrlListVarianti.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_lIDVarianteSelected = (long)m_ctrlListVarianti.GetItemData(m_ctrlListVarianti.GetNextSelectedItem(pos));

	CaricaDati();
}

void CGenomicaCorpoDlg::OnLvnItemchangedListSezioni(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lIDSezioneSelected = -1;
	POSITION pos = m_ctrlListSezioni.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_lIDSezioneSelected = (long)m_ctrlListSezioni.GetItemData(m_ctrlListSezioni.GetNextSelectedItem(pos));

	CaricaDati();
}

void CGenomicaCorpoDlg::OnBnClickedBtnRtfNewTable()
{
	m_ctrlTextControl.RtfInsertNewTable(this);
}

void CGenomicaCorpoDlg::OnBnClickedBtnRtfMakeUpper()
{
	m_ctrlTextControl.RtfSelectedTextMakeUpper();
}

void CGenomicaCorpoDlg::OnBnClickedBtnRtfMakeNormal()
{
	m_ctrlTextControl.RtfSelectedTextMakeNormal();
}

void CGenomicaCorpoDlg::OnBnClickedBtnRtfMakeLower()
{
	m_ctrlTextControl.RtfSelectedTextMakeLower();
}

void CGenomicaCorpoDlg::OnBnClickedBtnRtfFont() //Julio - BUG 4392 Edicao de texto
{
	m_ctrlTextControl.RtfSetFontProperties();
}

LRESULT CGenomicaCorpoDlg::ProccessVarianteFilter(WPARAM wParam, LPARAM lParam)
{
	BeginWaitCursor();
	
	try
	{
		CList<long>* pList = (CList<long>*)wParam;
		
		long lCount = pList->GetCount();
		UnselectAll();

		//

		m_ctrlListVarianti.SetRedraw(FALSE);
		m_ctrlListVarianti.DeleteAllItems();

		for (POSITION pos = pList->GetHeadPosition(); pos;)
		{
			long lID = pList->GetNext(pos);

			int nItem = m_ctrlListVarianti.InsertItem(m_ctrlListVarianti.GetItemCount(), CVariantiGeneticheSet().GetTitolo(lID));
			m_ctrlListVarianti.SetItemText(nItem, 1, CTipiVariantiGeneticheSet().GetCodice(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
			m_ctrlListVarianti.SetItemText(nItem, 2, CVariantiGeneticheSet().GetTrascrizione(lID));
			m_ctrlListVarianti.SetItemText(nItem, 3, CVariantiGeneticheSet().GetCromossoma(lID));
			m_ctrlListVarianti.SetItemText(nItem, 4, CVariantiGeneticheSet().GetGene(lID));
			m_ctrlListVarianti.SetItemText(nItem, 5, CVariantiGeneticheSet().GetPosizioneGene(lID));
			m_ctrlListVarianti.SetItemText(nItem, 6, CVariantiGeneticheSet().GetCodice(lID));
			m_ctrlListVarianti.SetItemText(nItem, 7, CTipiAlterazioniSet().GetCodice(CVariantiGeneticheSet().GetIDTipoAlterazione(lID)));
			m_ctrlListVarianti.SetItemText(nItem, 8, CVariantiGeneticheSet().GetHGVSc(lID));
			m_ctrlListVarianti.SetItemText(nItem, 9, CVariantiGeneticheSet().GetHGVSp(lID));
			m_ctrlListVarianti.SetItemText(nItem, 10, CPatogenicitaSet().GetCodice(CVariantiGeneticheSet().GetIDPatogenicita(lID)));
			m_ctrlListVarianti.SetItemData(nItem, (DWORD)lID);
		}

		m_ctrlListVarianti.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListVarianti.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListVarianti.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListVarianti.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListVarianti.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListVarianti.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListVarianti.SetColumnWidth(6, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListVarianti.SetColumnWidth(7, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListVarianti.SetColumnWidth(8, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListVarianti.SetColumnWidth(9, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListVarianti.SetColumnWidth(10, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListVarianti.SetRedraw(TRUE);
	}
	catch (...)
	{
		//
	}
	
	EndWaitCursor();
	
	return 1;
}

void CGenomicaCorpoDlg::CaricaSuggerimenti()
{
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);

	CString sTesto = m_ctrlTextControl.GetSelText();

	if (sTesto.IsEmpty())
	{
		CString sSuggestedRtf = CSezioniSet().GetTestoRtf(m_lIDSezioneSelected, 1);
		m_ctrlTextControlHide.SetRTFSelText(sSuggestedRtf);

		m_ctrlTextControlHide.SetSelStart(0);
		m_ctrlTextControlHide.SetSelLength(-1);
		CString sSuggestedTxt = m_ctrlTextControlHide.GetSelText();

		ChiediVariabiliSpeciale(sSuggestedTxt);
		SostituisciVariabili(sSuggestedRtf, sSuggestedTxt);

		//After replacing all the variables
		m_ctrlTextControl.ResetContents();
		m_ctrlTextControl.SetRTFSelText(sSuggestedRtf); 
		
	}
}

void CGenomicaCorpoDlg::ChiediVariabiliSpeciale(CString& sTXT)
{
	m_listVariables.RemoveAll();

	long lVariable = 0;

	int iHasSpecialVariables = sTXT.Find("<@");
	int iLastEndPos = 0;
	while (iHasSpecialVariables >= 0)
	{
		int iPosStart = sTXT.Find("<@", iLastEndPos) + 2; //removing <@
		int iPosEnd = sTXT.Find("@>", iLastEndPos);

		CString sVariable = sTXT.Mid(iPosStart, (iPosEnd - iPosStart));
		CString sTitolo = "";

		VARIABLES* pVar = new VARIABLES;
		if (pVar != NULL)
		{
			pVar->lIDItem = 0;
			pVar->sVariable = "<@" + sVariable + "@>";
			pVar->sValue = ChiediValoriSpeciale(sVariable);
			m_listVariables.AddTail(pVar);
		}

		lVariable++;
		iHasSpecialVariables = sTXT.Find("<@", iPosEnd + 1);
		iLastEndPos = iPosEnd + 1;
	}
}

CString CGenomicaCorpoDlg::ChiediValoriSpeciale(CString sVariabili)
{
	CString sResult = CVistaVariantiGeneticheSet().TryGetVaule(m_lIDVarianteSelected, sVariabili);	

	if (sResult == sVariabili)
		sResult = "<@" + sResult + "@>";

	return sResult;
}

void CGenomicaCorpoDlg::SostituisciVariabili(CString& sRTF, CString& sTXT)
{

	// metto temporaneamente il testo RTF in un controllo rich //
	m_ctrlTextControlHide.ResetContents();
	m_ctrlTextControlHide.SetRTFSelText(sRTF);

	// ora sostituisco (direttamente nel controllo) il testo di ogni variabile con il suo valore //
	POSITION pos = m_listVariables.GetHeadPosition();
	while (pos != NULL)
	{
		VARIABLES* pVal = m_listVariables.GetNext(pos);
		if (pVal->lIDItem == 0)
		{
			long lFind = sTXT.Find(pVal->sVariable);
			int iLen = pVal->sVariable.GetLength();

			while (lFind >= 0)
			{
				m_ctrlTextControlHide.ResetContents();
				m_ctrlTextControlHide.SetRTFSelText(sRTF);

				m_ctrlTextControlHide.SetSelStart(lFind);
				m_ctrlTextControlHide.SetSelLength(iLen);

				CString aa = m_ctrlTextControlHide.GetSelText();

				m_ctrlTextControlHide.SetSelText(pVal->sValue);

				m_ctrlTextControlHide.SetSelStart(0);
				m_ctrlTextControlHide.SetSelLength(-1);
				sRTF = m_ctrlTextControlHide.GetRTFSelText();
				sTXT = m_ctrlTextControlHide.GetSelText();

				lFind = sTXT.Find(pVal->sVariable, lFind + 1);
			}
		}
	}

	// riprendo il testo modificato //
	m_ctrlTextControlHide.SetSelStart(0);
	m_ctrlTextControlHide.SetSelLength(-1);
	sRTF = m_ctrlTextControlHide.GetRTFSelText();
	sTXT = m_ctrlTextControlHide.GetSelText();

	m_ctrlTextControlHide.ResetContents();
}