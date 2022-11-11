#include "stdafx.h"
#include "Endox.h"
#include "GenomicaRefertoDlg.h"
#include "GenomicaCorpoDlg.h"
#include "VariantiGeneticheSet.h"
#include "SezioniSet.h"
#include "TipiVariantiGeneticheSet.h"
#include "PatogenicitaSet.h"
#include "TipiAlterazioniSet.h"
#include "CorpoSezioneSet.h"
#include "TipiRefertoSet.h"
#include "VistaRefertoGenomicaSet.h"
#include "VistaVariantiGeneticheSet.h"
#include "TipiMaterialiSet.h"
#include "TipiRefertoSet.h"
#include "FrasiRisultatoSet.h"
#include "EsamiRefertoSezionatoSet.h"
#include "EsamiVariantiSelezionateSet.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "EditStringDlg.h"
#include "KeyboardMonitor.h" //Julio BUG 3457 - Texter
#include "FrasiRtfSet.h" //Julio BUG 3457 - Texter
#include "DialogWithResizableCombo.h" //Luiz - 01/07/2019 - P3 - Permitir combobox de variáveis de laudo exibir até 200 caracteres

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGenomicaRefertoDlg, CDialog)

CGenomicaRefertoDlg::CGenomicaRefertoDlg(CWnd* pParent, CEsamiView* pEsamiView)
: CDialog(CGenomicaRefertoDlg::IDD, pParent)
{
	m_pEsamiView = pEsamiView;
	m_lIDEsame = pEsamiView->m_pEsamiSet->m_lContatore;
}

CGenomicaRefertoDlg::~CGenomicaRefertoDlg()
{
}

BEGIN_MESSAGE_MAP(CGenomicaRefertoDlg, CDialog)
	ON_MESSAGE(WM_GENOMICA_FILTROVARIANTE, ProccessVarianteFilter)

	ON_BN_CLICKED(IDC_BTN_GENERA, OnBnClickedBtnGenera)
	ON_BN_CLICKED(IDC_BTN_ANNULLA, OnBnClickedBtnAnnulla)
	ON_BN_CLICKED(IDC_BTN_SALVA, OnBnClickedBtnSalva)
	ON_BN_CLICKED(IDC_BTN_SU, OnBnClickedBtnSu)
	ON_BN_CLICKED(IDC_BTN_GIU, OnBnClickedBtnGiu)
	ON_BN_CLICKED(IDC_BTN_RIMUOVE, OnBnClickedBtnRimuove)

	ON_COMMAND(IDC_RTF_TABLE, OnBnClickedBtnRtfNewTable)
	ON_COMMAND(IDC_RTF_MAKEUPPER, OnBnClickedBtnRtfMakeUpper)
	ON_COMMAND(IDC_RTF_MAKENORMAL, OnBnClickedBtnRtfMakeNormal)
	ON_COMMAND(IDC_RTF_MAKELOWER, OnBnClickedBtnRtfMakeLower)
	ON_COMMAND(IDC_RTF_FONT, OnBnClickedBtnRtfFont) //Julio - BUG 4392 Edicao de texto
	ON_COMMAND(IDC_RTF_IMAGE, OnBnClickedBtnRtfImage) //Julio - BUG 4392 Edicao de texto
	ON_MESSAGE(EPM_KEYBOARD_PRESS, OnKeyboardPress) //Julio BUG 3457 - Texter

	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VARIANTI, OnNMDblclkListVarianti)

END_MESSAGE_MAP()

void CGenomicaRefertoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_GENERA, m_ctrlButtonGenera);
	DDX_Control(pDX, IDC_BTN_ANNULLA, m_ctrlButtonAnnulla);
	DDX_Control(pDX, IDC_BTN_SALVA, m_ctrlButtonSalva);
	DDX_Control(pDX, IDC_BTN_SU, m_ctrlButtonSu);
	DDX_Control(pDX, IDC_BTN_GIU, m_ctrlButtonGiu);
	DDX_Control(pDX, IDC_BTN_RIMUOVE, m_ctrlButtonRimuove);

	DDX_Control(pDX, IDC_RICERCA_PLACE, m_ctrlStaticRicercaForm);

	DDX_Control(pDX, IDC_LIST_VARIANTI, m_ctrlListVarianti);
	DDX_Control(pDX, IDC_LIST_VARIANTISELEZIONATE, m_ctrlListVariantiSelezionate);

	DDX_Control(pDX, IDC_STATIC1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC6, m_ctrlStatic6);

	DDX_Control(pDX, IDC_COMBO_TIPOESAME, m_ctrlComboTipoEsame);
	DDX_Control(pDX, IDC_COMBO_MATERIALE, m_ctrlComboMateriale);

	DDX_Control(pDX, IDC_BUTTONBAR, m_ctrlButtonBar);

	DDX_Control(pDX, IDC_TEXTCONTROL_HIDE, m_ctrlTextControlHide);
	DDX_Control(pDX, IDC_TEXTCONTROL_HIDE2, m_ctrlTextControlHide2);
	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //	
}


BOOL CGenomicaRefertoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CKeyboardMonitor::Get()->Start(this->GetSafeHwnd(), EPM_KEYBOARD_PRESS); //Julio BUG 3457 - Texter

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

	m_ctrlListVariantiSelezionate.SetExtendedStyle(m_ctrlListVariantiSelezionate.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlListVariantiSelezionate.InsertColumn(0, "Titolo", LVCFMT_LEFT, 0);

	//RiempiLista();
	RiempiCombo();

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

	m_ctrlTextControl.SetImageSaveMode(1);


	m_ctrlTextControl.EnableWindow(TRUE);
	m_ctrlToolbar.EnableWindow(TRUE);
	m_ctrlButtonBar.EnableWindow(TRUE);
	m_ctrlTextControlHide.EnableWindow(FALSE);
	m_ctrlTextControlHide2.EnableWindow(FALSE);

	CGenomicaRicercaVarianteForm::CreateFormEx(this, &m_ctrlStaticRicercaForm, m_pEsamiView, &m_pRicercaForm, BTNADD_CORPO);

	LoadLastReport();

	theApp.LocalizeDialog(this, CGenomicaRefertoDlg::IDD, "CGenomicaRefertoDlg");

	// Marvel BUG 4092 - concorrência na edição de laudos
	if (!m_pEsamiView->m_sMsgGotRefertoRefreshWithUpdate.IsEmpty()){
		theApp.AfxMessageBoxEndo(m_pEsamiView->m_sMsgGotRefertoRefreshWithUpdate);
		m_pEsamiView->m_sMsgGotRefertoRefreshWithUpdate = "";
	}

	return TRUE;
}

void CGenomicaRefertoDlg::OnOK()
{
	if (GetFocus() == GetDlgItem(IDC_BTN_SALVA))
	CDialog::OnOK();
	else
		m_pRicercaForm->OnBnClickedBtnFind();
}

void CGenomicaRefertoDlg::OnCancel()
{
	CDialog::OnCancel();
}

void CGenomicaRefertoDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlListVariantiSelezionate.DeleteAllItems();

	m_ctrlListVarianti.SetRedraw(FALSE);
	m_ctrlListVarianti.DeleteAllItems();

	CList<long> listID;
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
	m_ctrlListVarianti.SetRedraw(TRUE);
	EndWaitCursor();
}

void CGenomicaRefertoDlg::RiempiCombo()
{
	m_ctrlComboMateriale.ResetContent();
	m_ctrlComboTipoEsame.ResetContent();

	CList<long> list;
	long nIndex = 0;

	CTipiMaterialiSet().GetIDList(list);
	for (POSITION pos = list.GetHeadPosition(); pos;)
	{
		if (nIndex == 0)
		{
			m_ctrlComboMateriale.InsertString(nIndex, "");
			m_ctrlComboMateriale.SetItemData(nIndex, 0);
		}
		else
		{
			long lID = list.GetNext(pos);

			CString sCodice = CTipiMaterialiSet().GetCodice(lID);
			CString sDesc = CTipiMaterialiSet().GetDescrizione(lID);
			CString sValue = sDesc.IsEmpty() ? sCodice : sCodice + " - " + sDesc;

			m_ctrlComboMateriale.InsertString(nIndex, sValue);
			m_ctrlComboMateriale.SetItemData(nIndex, lID);
		}
		nIndex++;
	}

	nIndex = 0;
	list.RemoveAll();
	CTipiRefertoSet().GetIDList(list);
	for (POSITION pos = list.GetHeadPosition(); pos;)
	{
		if (nIndex == 0)
		{
			m_ctrlComboTipoEsame.InsertString(nIndex, "");
			m_ctrlComboTipoEsame.SetItemData(nIndex, 0);
		}
		else
		{
			long lID = list.GetNext(pos);

			CString sCodice = CTipiRefertoSet().GetCodice(lID);
			CString sValue = sCodice;

			m_ctrlComboTipoEsame.InsertString(nIndex, sValue);
			m_ctrlComboTipoEsame.SetItemData(nIndex, lID);
		}
		nIndex++;
	}
}

void CGenomicaRefertoDlg::UnselectAll()
{
	if (m_ctrlListVarianti.GetItemCount() > 0)
	{
		for (int i = 0; i < m_ctrlListVarianti.GetItemCount(); i++)
			m_ctrlListVarianti.SetItemState(i, 0, LVIS_SELECTED);
	}
}

// Julio BUG 3791 - Melhoria frases resultado laudo genomica
CString CGenomicaRefertoDlg::GetResultText()
{
	CString sTestoResultado = CFrasiRisultatoSet().GetTitoloRisultato();

	//Se nenhuma variante foi selecionada o resultado é NegativoNegativo
	if (m_ctrlListVariantiSelezionate.GetItemCount() == 0)
		return sTestoResultado + CFrasiRisultatoSet().GetNegativoNegativo();
	
	//Verifica quais das frases serao usadas
	CList<VARIANTE*> listaPositivos;
	BOOL bPositivo = FALSE;
	BOOL bPlural = FALSE;
	
	for (int i = 0; i < m_ctrlListVariantiSelezionate.GetItemCount(); i++)
	{
		VARIANTE* pVariante = (VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i);
		if (pVariante->bPositivita)
		{
			bPlural = bPositivo; //Se ja foi encontrado um positivo, entao e um plural			
			bPositivo = TRUE;

			listaPositivos.AddTail(pVariante);
		}
	}
		//	

	//Busca o texto da frase escolhida
	if (bPositivo)
	{
		if (bPlural)
			sTestoResultado += CFrasiRisultatoSet().GetPositivoPlurale();
		else //Singular
			sTestoResultado += CFrasiRisultatoSet().GetPositivoSingolare();
	}
	else //Negativo
	{
		return sTestoResultado + CFrasiRisultatoSet().GetNegativoSingolare();
	}
	//

	//Substitui os placeholders pelas variantes selecionadas
	CString sVarComplete;
	int nCur = 1;
	int nTotal = listaPositivos.GetCount();
			
	for (POSITION pos = listaPositivos.GetHeadPosition(); pos;)
	{
		VARIANTE* pVariante = (VARIANTE*)listaPositivos.GetNext(pos);
		long lID = pVariante->lID;

		CString sVar = CFrasiRisultatoSet().GetPositivoVariante();
		sVar.Replace("<@Titolo@>", CVariantiGeneticheSet().GetTitolo(lID));
		sVar.Replace("<@Codice@>", CVariantiGeneticheSet().GetCodice(lID));
		sVar.Replace("<@Trascrizione@>", CVariantiGeneticheSet().GetTrascrizione(lID));
		sVar.Replace("<@Cromossoma@>", CVariantiGeneticheSet().GetCromossoma(lID));
		sVar.Replace("<@Gene@>", CVariantiGeneticheSet().GetGene(lID));
		sVar.Replace("<@Posizione@>", CVariantiGeneticheSet().GetPosizioneGene(lID));
		sVar.Replace("<@HGVSc@>", CVariantiGeneticheSet().GetHGVSc(lID));
		sVar.Replace("<@HGVSp@>", CVariantiGeneticheSet().GetHGVSp(lID));				
		sVar.Replace("<@TipoVarianteDescrizione@>", CTipiVariantiGeneticheSet().GetDescrizione(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
		sVar.Replace("<@PatogenicitaDescrizione@>", CPatogenicitaSet().GetDescrizione(CVariantiGeneticheSet().GetIDPatogenicita(lID)));
				
		sVarComplete += sVar;

		if (nCur < nTotal)
		{
			if (nCur + 1 == nTotal)
				sVarComplete += " e ";
			else
				sVarComplete += ", ";
		}

		nCur++;
	}
	sTestoResultado.Replace("<@#VAR#@>", sVarComplete);
	//

	return sTestoResultado;
}

CString CGenomicaRefertoDlg::GetComplementText()
{
	CString sTestoComplemento = CFrasiRisultatoSet().GetTitoloComplemento();

	//Se nenhuma variante foi selecionada o resultado é NegativoNegativo
	if (m_ctrlListVariantiSelezionate.GetItemCount() == 0)
		return "";

	//loop por todos os tipos de variantes, o complemento precisa agrupar as variantes selecionadas por tipo
	CList<long> listaTipoVariante;
	CTipiVariantiGeneticheSet().GetIDList(listaTipoVariante);

	long lLastIDTipo = listaTipoVariante.GetTail();
	for (POSITION pos = listaTipoVariante.GetHeadPosition(); pos;)
	{
		long lIDTipo = listaTipoVariante.GetNext(pos);

		//Verifica quais das frases serao usadas para este tipo de variante
		CList<VARIANTE*> listaVUS;
		BOOL bNegativo = TRUE;
		BOOL bPlural = FALSE;
		BOOL bHasPositiveSameType = FALSE;

		for (int i = 0; i < m_ctrlListVariantiSelezionate.GetItemCount(); i++)
		{
			VARIANTE* pVariante = (VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i);
			if (!pVariante->bPositivita && pVariante->lIDTipo == lIDTipo)
			{
				bPlural = !bNegativo; //Se ja foi encontrado um, entao e um plural
				bNegativo = FALSE;

				listaVUS.AddTail(pVariante);
			}

			if (pVariante->bPositivita && pVariante->lIDTipo == lIDTipo) bHasPositiveSameType = TRUE; //Indica se uma variante do mesmo tipo foi selecionada no resultado

		}

		//Busca o texto da frase escolhida
		if (bNegativo) //nenhum complemento para este tipo 
		{
			if (bHasPositiveSameType && CTipiVariantiGeneticheSet().GetFraseRemovibile(lIDTipo))
			{
				sTestoComplemento += ((lIDTipo == lLastIDTipo) ? "" : "&#13;");
			}
			else
			{
				if (!CFrasiRisultatoSet().GetComplementoNegativo(lIDTipo).IsEmpty())
				{
				sTestoComplemento +=
					CFrasiRisultatoSet().GetComplementoNegativo(lIDTipo)
					+ ((lIDTipo == lLastIDTipo) ? "" : "&#13;");
			}
		}
		}
		else //Ao menos um complemento
		{
			if (bPlural)
			{
				if (!CFrasiRisultatoSet().GetComplementoPlurale(lIDTipo).IsEmpty())
				{
				sTestoComplemento += CFrasiRisultatoSet().GetComplementoPlurale(lIDTipo)
					+ ((lIDTipo == lLastIDTipo) ? "" : "&#13;");
			}
			}
			else //Singular
			{
				if (!CFrasiRisultatoSet().GetComplementoSingolare(lIDTipo).IsEmpty())
				{
				sTestoComplemento += CFrasiRisultatoSet().GetComplementoSingolare(lIDTipo)
					+ ((lIDTipo == lLastIDTipo) ? "" : "&#13;");
			}
		}
		}
		//

		//Substitui os placeholders pelas variantes selecionadas
		CString sVarComplete;
		int nCur = 1;
		int nTotal = listaVUS.GetCount();

		for (POSITION pos = listaVUS.GetHeadPosition(); pos;)
		{
			VARIANTE* pVariante = (VARIANTE*)listaVUS.GetNext(pos);
			long lID = pVariante->lID;

			CString sVar = CFrasiRisultatoSet().GetComplementoVariante(pVariante->lIDTipo);
			sVar.Replace("<@Titolo@>", CVariantiGeneticheSet().GetTitolo(lID));
			sVar.Replace("<@Codice@>", CVariantiGeneticheSet().GetCodice(lID));
			sVar.Replace("<@Trascrizione@>", CVariantiGeneticheSet().GetTrascrizione(lID));
			sVar.Replace("<@Cromossoma@>", CVariantiGeneticheSet().GetCromossoma(lID));
			sVar.Replace("<@Gene@>", CVariantiGeneticheSet().GetGene(lID));
			sVar.Replace("<@Posizione@>", CVariantiGeneticheSet().GetPosizioneGene(lID));
			sVar.Replace("<@HGVSc@>", CVariantiGeneticheSet().GetHGVSc(lID));
			sVar.Replace("<@HGVSp@>", CVariantiGeneticheSet().GetHGVSp(lID));
			sVar.Replace("<@TipoVarianteDescrizione@>", CTipiVariantiGeneticheSet().GetDescrizione(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
			sVar.Replace("<@PatogenicitaDescrizione@>", CPatogenicitaSet().GetDescrizione(CVariantiGeneticheSet().GetIDPatogenicita(lID)));
			
			sVarComplete += sVar;

			if (nCur < nTotal)
			{
				if (nCur + 1 == nTotal)
					sVarComplete += " e ";
				else
					sVarComplete += ", ";
			}

			nCur++;
		}
		sTestoComplemento.Replace("<@#VAR#@>", sVarComplete);
	}

	return sTestoComplemento;
}

void CGenomicaRefertoDlg::GetComplementTextInParts()
{
	//CString sTestoComplemento = CFrasiRisultatoSet().GetTitoloComplemento();
	CString sTestoComplementoParcial = "";

	//Se nenhuma variante foi selecionada o resultado é NegativoNegativo
	//if (m_ctrlListVariantiSelezionate.GetItemCount() == 0)
	//	return "";

	//loop por todos os tipos de variantes, o complemento precisa agrupar as variantes selecionadas por tipo
	CList<long> listaTipoVariante;
	CTipiVariantiGeneticheSet().GetIDList(listaTipoVariante);

	int nVariablePos = 0;
	long lLastIDTipo = listaTipoVariante.GetTail();
	for (POSITION pos = listaTipoVariante.GetHeadPosition(); pos;)
	{
		long lIDTipo = listaTipoVariante.GetNext(pos);

		//Verifica quais das frases serao usadas para este tipo de variante
		CList<VARIANTE*> listaVUS;
		BOOL bNegativo = TRUE;
		BOOL bPlural = FALSE;
		BOOL bHasPositiveSameType = FALSE;

		for (int i = 0; i < m_ctrlListVariantiSelezionate.GetItemCount(); i++)
		{
			VARIANTE* pVariante = (VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i);
			if (!pVariante->bPositivita && pVariante->lIDTipo == lIDTipo)
			{
				bPlural = !bNegativo; //Se ja foi encontrado um, entao e um plural
				bNegativo = FALSE;

				listaVUS.AddTail(pVariante);
			}

			if (pVariante->bPositivita && pVariante->lIDTipo == lIDTipo) bHasPositiveSameType = TRUE; //Indica se uma variante do mesmo tipo foi selecionada no resultado
		}

		//Busca o texto da frase escolhida
		if (bNegativo) //nenhum complemento para este tipo 
		{
			sTestoComplementoParcial = CFrasiRisultatoSet().GetComplementoNegativo(lIDTipo);
		}
		else //Ao menos um complemento
		{
			if (bPlural)
			{
				sTestoComplementoParcial = CFrasiRisultatoSet().GetComplementoPlurale(lIDTipo);

			}
			else //Singular
			{
				sTestoComplementoParcial = CFrasiRisultatoSet().GetComplementoSingolare(lIDTipo);
			}
		}
		//

		//Substitui os placeholders pelas variantes selecionadas
		CString sVarComplete;
		int nCur = 1;
		int nTotal = listaVUS.GetCount();

		for (POSITION pos = listaVUS.GetHeadPosition(); pos;)
		{
			VARIANTE* pVariante = (VARIANTE*)listaVUS.GetNext(pos);
			long lID = pVariante->lID;

			CString sVar = CFrasiRisultatoSet().GetComplementoVariante(pVariante->lIDTipo);
			sVar.Replace("<@Titolo@>", CVariantiGeneticheSet().GetTitolo(lID));
			sVar.Replace("<@Codice@>", CVariantiGeneticheSet().GetCodice(lID));
			sVar.Replace("<@Trascrizione@>", CVariantiGeneticheSet().GetTrascrizione(lID));
			sVar.Replace("<@Cromossoma@>", CVariantiGeneticheSet().GetCromossoma(lID));
			sVar.Replace("<@Gene@>", CVariantiGeneticheSet().GetGene(lID));
			sVar.Replace("<@Posizione@>", CVariantiGeneticheSet().GetPosizioneGene(lID));
			sVar.Replace("<@HGVSc@>", CVariantiGeneticheSet().GetHGVSc(lID));
			sVar.Replace("<@HGVSp@>", CVariantiGeneticheSet().GetHGVSp(lID));
			sVar.Replace("<@TipoVarianteDescrizione@>", CTipiVariantiGeneticheSet().GetDescrizione(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
			sVar.Replace("<@PatogenicitaDescrizione@>", CPatogenicitaSet().GetDescrizione(CVariantiGeneticheSet().GetIDPatogenicita(lID)));

			sVarComplete += sVar;

			/*if (nCur < nTotal)
			{
				if (nCur + 1 == nTotal)
					sVarComplete += " e ";
				else
					sVarComplete += ", ";
			}*/

			nCur++;
		}
		sTestoComplementoParcial.Replace("<@#VAR#@>", sVarComplete);
		
		CString sTitolo;
		sTitolo.Format("<@#COMPLEMENTO%li#@>", nVariablePos++);

		VARIABLES* pVarComplemento = new VARIABLES;
		if (pVarComplemento != NULL)
		{
			pVarComplemento->lIDItem = 0;
			pVarComplemento->sVariable = sTitolo;
			pVarComplemento->sValue = sTestoComplementoParcial;
			m_listVariables.AddTail(pVarComplemento);
		}
	}
}

void CGenomicaRefertoDlg::GetOtherTexts()
{
	CList<VARIANTE*> listaALL;		

	for (int i = 0; i < m_ctrlListVariantiSelezionate.GetItemCount(); i++)
	{
		VARIANTE* pVariante = (VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i);
		listaALL.AddTail(pVariante);
	}
	
	int nTotal = listaALL.GetCount();
	
	//lista de todos os genes separados por virgula
	CString sVarComplete = "";
	int nCur = 1;		
	for (POSITION pos = listaALL.GetHeadPosition(); pos;)
	{
		VARIANTE* pVariante = (VARIANTE*)listaALL.GetNext(pos);
		long lID = pVariante->lID;

		CString sVar = "<@Gene@>";
		sVar.Replace("<@Titolo@>", CVariantiGeneticheSet().GetTitolo(lID));
		sVar.Replace("<@Codice@>", CVariantiGeneticheSet().GetCodice(lID));
		sVar.Replace("<@Trascrizione@>", CVariantiGeneticheSet().GetTrascrizione(lID));
		sVar.Replace("<@Cromossoma@>", CVariantiGeneticheSet().GetCromossoma(lID));
		sVar.Replace("<@Gene@>", CVariantiGeneticheSet().GetGene(lID));
		sVar.Replace("<@Posizione@>", CVariantiGeneticheSet().GetPosizioneGene(lID));
		sVar.Replace("<@HGVSc@>", CVariantiGeneticheSet().GetHGVSc(lID));
		sVar.Replace("<@HGVSp@>", CVariantiGeneticheSet().GetHGVSp(lID));
		sVar.Replace("<@TipoVarianteDescrizione@>", CTipiVariantiGeneticheSet().GetDescrizione(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
		sVar.Replace("<@PatogenicitaDescrizione@>", CPatogenicitaSet().GetDescrizione(CVariantiGeneticheSet().GetIDPatogenicita(lID)));
		sVar.Replace("<@PatogenicitaCodice@>", CPatogenicitaSet().GetCodice(CVariantiGeneticheSet().GetIDPatogenicita(lID)));

		sVarComplete += sVar;

		if (nCur < nTotal)
		{
			if (nCur + 1 == nTotal)
				sVarComplete += " e ";
			else
				sVarComplete += ", ";
		}

		nCur++;
	}
	VARIABLES* pVarLista1 = new VARIABLES;
	if (pVarLista1 != NULL)
	{
		pVarLista1->lIDItem = 0;
		pVarLista1->sVariable = "<@#LISTA1#@>";
		pVarLista1->sValue = sVarComplete;
		m_listVariables.AddTail(pVarLista1);
	}
	//

	//lista de todos os genes e transcritos positivos separados por enter
	sVarComplete = "";
	nCur = 1;
	for (POSITION pos = listaALL.GetHeadPosition(); pos;)
	{
		VARIANTE* pVariante = (VARIANTE*)listaALL.GetNext(pos);
		if (pVariante->bPositivita)
		{
			long lID = pVariante->lID;

			CString sVar = "<@Gene@>, <@HGVSp@>&#13;";
			sVar.Replace("<@Titolo@>", CVariantiGeneticheSet().GetTitolo(lID));
			sVar.Replace("<@Codice@>", CVariantiGeneticheSet().GetCodice(lID));
			sVar.Replace("<@Trascrizione@>", CVariantiGeneticheSet().GetTrascrizione(lID));
			sVar.Replace("<@Cromossoma@>", CVariantiGeneticheSet().GetCromossoma(lID));
			sVar.Replace("<@Gene@>", CVariantiGeneticheSet().GetGene(lID));
			sVar.Replace("<@Posizione@>", CVariantiGeneticheSet().GetPosizioneGene(lID));
			sVar.Replace("<@HGVSc@>", CVariantiGeneticheSet().GetHGVSc(lID));
			sVar.Replace("<@HGVSp@>", CVariantiGeneticheSet().GetHGVSp(lID));
			sVar.Replace("<@TipoVarianteDescrizione@>", CTipiVariantiGeneticheSet().GetDescrizione(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
			sVar.Replace("<@PatogenicitaDescrizione@>", CPatogenicitaSet().GetDescrizione(CVariantiGeneticheSet().GetIDPatogenicita(lID)));
			sVar.Replace("<@PatogenicitaCodice@>", CPatogenicitaSet().GetCodice(CVariantiGeneticheSet().GetIDPatogenicita(lID)));

			sVarComplete += sVar;

			/*if (nCur < nTotal)
			{
			if (nCur + 1 == nTotal)
			sVarComplete += " e ";
			else
			sVarComplete += ", ";
			}*/
		}
		nCur++;
	}
	VARIABLES* pVarLista2 = new VARIABLES;
	if (pVarLista2 != NULL)
	{
		pVarLista2->lIDItem = 0;
		pVarLista2->sVariable = "<@#LISTA2#@>";
		pVarLista2->sValue = sVarComplete;
		m_listVariables.AddTail(pVarLista2);
	}
	//

	//todas as variantes selecionadas
	sVarComplete = "";
	nCur = 1;
	for (POSITION pos = listaALL.GetHeadPosition(); pos;)
	{
		VARIANTE* pVariante = (VARIANTE*)listaALL.GetNext(pos);
		
		long lID = pVariante->lID;

		CString sVar = theApp.m_sGenomicaModeloTabela1; //"1;8;<@Gene@>\\line(<@Trascrizione@>);<@HGVSp@>;;<@PatogenicitaDescrizione@>;;;;;";
		sVar.Replace("<@Titolo@>", CVariantiGeneticheSet().GetTitolo(lID));
		sVar.Replace("<@Codice@>", CVariantiGeneticheSet().GetCodice(lID));
		sVar.Replace("<@Trascrizione@>", CVariantiGeneticheSet().GetTrascrizione(lID));
		sVar.Replace("<@Cromossoma@>", CVariantiGeneticheSet().GetCromossoma(lID));
		sVar.Replace("<@Gene@>", CVariantiGeneticheSet().GetGene(lID));
		sVar.Replace("<@Posizione@>", CVariantiGeneticheSet().GetPosizioneGene(lID));
		sVar.Replace("<@HGVSc@>", CVariantiGeneticheSet().GetHGVSc(lID));
		sVar.Replace("<@HGVSp@>", CVariantiGeneticheSet().GetHGVSp(lID));
		sVar.Replace("<@TipoVarianteDescrizione@>", CTipiVariantiGeneticheSet().GetDescrizione(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
		sVar.Replace("<@PatogenicitaDescrizione@>", CPatogenicitaSet().GetDescrizione(CVariantiGeneticheSet().GetIDPatogenicita(lID)));
		sVar.Replace("<@PatogenicitaCodice@>", CPatogenicitaSet().GetCodice(CVariantiGeneticheSet().GetIDPatogenicita(lID)));

		CString sLine;
		sLine.Format("@TABLE_%s;%s_TABLE@", CVariantiGeneticheSet().GetHGVSp(lID), sVar);

		sVarComplete += sLine;			
		
		nCur++;
	}
	VARIABLES* pVarTable1 = new VARIABLES;
	if (pVarTable1 != NULL)
	{
		pVarTable1->lIDItem = 0;
		pVarTable1->sVariable = "<@#TABLE1#@>";
		pVarTable1->sValue = sVarComplete;
		m_listVariables.AddTail(pVarTable1);
	}
	//

	//todas as variantes positivas selecionadas
	sVarComplete = "";
	nCur = 1;
	for (POSITION pos = listaALL.GetHeadPosition(); pos;)
	{
		VARIANTE* pVariante = (VARIANTE*)listaALL.GetNext(pos);
		if (pVariante->bPositivita)
		{
			long lID = pVariante->lID;

			CString sVar = theApp.m_sGenomicaModeloTabela2; //"1;8;<@Gene@>\\line(<@Trascrizione@>);<@HGVSp@>;;<@PatogenicitaDescrizione@>;;;;;";
			sVar.Replace("<@Titolo@>", CVariantiGeneticheSet().GetTitolo(lID));
			sVar.Replace("<@Codice@>", CVariantiGeneticheSet().GetCodice(lID));
			sVar.Replace("<@Trascrizione@>", CVariantiGeneticheSet().GetTrascrizione(lID));
			sVar.Replace("<@Cromossoma@>", CVariantiGeneticheSet().GetCromossoma(lID));
			sVar.Replace("<@Gene@>", CVariantiGeneticheSet().GetGene(lID));
			sVar.Replace("<@Posizione@>", CVariantiGeneticheSet().GetPosizioneGene(lID));
			sVar.Replace("<@HGVSc@>", CVariantiGeneticheSet().GetHGVSc(lID));
			sVar.Replace("<@HGVSp@>", CVariantiGeneticheSet().GetHGVSp(lID));
			sVar.Replace("<@TipoVarianteDescrizione@>", CTipiVariantiGeneticheSet().GetDescrizione(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
			sVar.Replace("<@PatogenicitaDescrizione@>", CPatogenicitaSet().GetDescrizione(CVariantiGeneticheSet().GetIDPatogenicita(lID)));
			sVar.Replace("<@PatogenicitaCodice@>", CPatogenicitaSet().GetCodice(CVariantiGeneticheSet().GetIDPatogenicita(lID)));

			CString sLine;
			sLine.Format("@TABLE_%s;%s_TABLE@", CVariantiGeneticheSet().GetHGVSp(lID), sVar);

			sVarComplete += sLine;
		}
		nCur++;
	}
	VARIABLES* pVarTable2 = new VARIABLES;
	if (pVarTable2 != NULL)
	{
		pVarTable2->lIDItem = 0;
		pVarTable2->sVariable = "<@#TABLE2#@>";
		pVarTable2->sValue = sVarComplete;
		m_listVariables.AddTail(pVarTable2);
	}
	//

	//lista de todos os genes e transcritos negativos tabelados
	sVarComplete = "";
	nCur = 1;
	for (POSITION pos = listaALL.GetHeadPosition(); pos;)
	{
		VARIANTE* pVariante = (VARIANTE*)listaALL.GetNext(pos);
		if (!pVariante->bPositivita)
		{
			long lID = pVariante->lID;

			CString sVar = theApp.m_sGenomicaModeloTabela3; //"1;8;<@Gene@>\\line(<@Trascrizione@>);<@HGVSp@>;;<@PatogenicitaDescrizione@>;;;;;";
			sVar.Replace("<@Titolo@>", CVariantiGeneticheSet().GetTitolo(lID));
			sVar.Replace("<@Codice@>", CVariantiGeneticheSet().GetCodice(lID));
			sVar.Replace("<@Trascrizione@>", CVariantiGeneticheSet().GetTrascrizione(lID));
			sVar.Replace("<@Cromossoma@>", CVariantiGeneticheSet().GetCromossoma(lID));
			sVar.Replace("<@Gene@>", CVariantiGeneticheSet().GetGene(lID));
			sVar.Replace("<@Posizione@>", CVariantiGeneticheSet().GetPosizioneGene(lID));
			sVar.Replace("<@HGVSc@>", CVariantiGeneticheSet().GetHGVSc(lID));
			sVar.Replace("<@HGVSp@>", CVariantiGeneticheSet().GetHGVSp(lID));
			sVar.Replace("<@TipoVarianteDescrizione@>", CTipiVariantiGeneticheSet().GetDescrizione(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
			sVar.Replace("<@PatogenicitaDescrizione@>", CPatogenicitaSet().GetDescrizione(CVariantiGeneticheSet().GetIDPatogenicita(lID)));
			sVar.Replace("<@PatogenicitaCodice@>", CPatogenicitaSet().GetCodice(CVariantiGeneticheSet().GetIDPatogenicita(lID)));

			CString sLine;
			sLine.Format("@TABLE_%s;%s_TABLE@", CVariantiGeneticheSet().GetHGVSp(lID), sVar);

			sVarComplete += sLine;
		}
		nCur++;
	}
	VARIABLES* pVarTable3 = new VARIABLES;
	if (pVarTable3 != NULL)
	{
		pVarTable3->lIDItem = 0;
		pVarTable3->sVariable = "<@#TABLE3#@>";
		pVarTable3->sValue = sVarComplete;
		m_listVariables.AddTail(pVarTable3);
	}
	//

	//lista de todos os genes e transcritos negativos tabelados
	sVarComplete = "";
	nCur = 1;
	for (POSITION pos = listaALL.GetHeadPosition(); pos;)
	{
		VARIANTE* pVariante = (VARIANTE*)listaALL.GetNext(pos);
		if (pVariante->bPositivita)
		{
			long lID = pVariante->lID;

			CString sVar = theApp.m_sGenomicaModeloTabela4; //"1;8;<@Gene@>\\line(<@Trascrizione@>);<@HGVSp@>;;<@PatogenicitaDescrizione@>;;;;;";
			sVar.Replace("<@Titolo@>", CVariantiGeneticheSet().GetTitolo(lID));
			sVar.Replace("<@Codice@>", CVariantiGeneticheSet().GetCodice(lID));
			sVar.Replace("<@Trascrizione@>", CVariantiGeneticheSet().GetTrascrizione(lID));
			sVar.Replace("<@Cromossoma@>", CVariantiGeneticheSet().GetCromossoma(lID));
			sVar.Replace("<@Gene@>", CVariantiGeneticheSet().GetGene(lID));
			sVar.Replace("<@Posizione@>", CVariantiGeneticheSet().GetPosizioneGene(lID));
			sVar.Replace("<@HGVSc@>", CVariantiGeneticheSet().GetHGVSc(lID));
			sVar.Replace("<@HGVSp@>", CVariantiGeneticheSet().GetHGVSp(lID));
			sVar.Replace("<@TipoVarianteDescrizione@>", CTipiVariantiGeneticheSet().GetDescrizione(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
			sVar.Replace("<@PatogenicitaDescrizione@>", CPatogenicitaSet().GetDescrizione(CVariantiGeneticheSet().GetIDPatogenicita(lID)));
			sVar.Replace("<@PatogenicitaCodice@>", CPatogenicitaSet().GetCodice(CVariantiGeneticheSet().GetIDPatogenicita(lID)));

			CString sLine;
			sLine.Format("@TABLE_%s;%s_TABLE@", CVariantiGeneticheSet().GetHGVSp(lID), sVar);

			sVarComplete += sLine;
		}
		nCur++;
	}
	VARIABLES* pVarTable4 = new VARIABLES;
	if (pVarTable4 != NULL)
	{
		pVarTable4->lIDItem = 0;
		pVarTable4->sVariable = "<@#TABLE4#@>";
		pVarTable4->sValue = sVarComplete;
		m_listVariables.AddTail(pVarTable4);
	}
	//

	//lista de todos os genes e transcritos negativos tabelados
	sVarComplete = "";
	nCur = 1;
	for (POSITION pos = listaALL.GetHeadPosition(); pos;)
	{
		VARIANTE* pVariante = (VARIANTE*)listaALL.GetNext(pos);
		if (!pVariante->bPositivita)
		{
			long lID = pVariante->lID;

			CString sVar = theApp.m_sGenomicaModeloTabela5; //"1;8;<@Gene@>\\line(<@Trascrizione@>);<@HGVSp@>;;<@PatogenicitaDescrizione@>;;;;;";
			sVar.Replace("<@Titolo@>", CVariantiGeneticheSet().GetTitolo(lID));
			sVar.Replace("<@Codice@>", CVariantiGeneticheSet().GetCodice(lID));
			sVar.Replace("<@Trascrizione@>", CVariantiGeneticheSet().GetTrascrizione(lID));
			sVar.Replace("<@Cromossoma@>", CVariantiGeneticheSet().GetCromossoma(lID));
			sVar.Replace("<@Gene@>", CVariantiGeneticheSet().GetGene(lID));
			sVar.Replace("<@Posizione@>", CVariantiGeneticheSet().GetPosizioneGene(lID));
			sVar.Replace("<@HGVSc@>", CVariantiGeneticheSet().GetHGVSc(lID));
			sVar.Replace("<@HGVSp@>", CVariantiGeneticheSet().GetHGVSp(lID));
			sVar.Replace("<@TipoVarianteDescrizione@>", CTipiVariantiGeneticheSet().GetDescrizione(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
			sVar.Replace("<@PatogenicitaDescrizione@>", CPatogenicitaSet().GetDescrizione(CVariantiGeneticheSet().GetIDPatogenicita(lID)));
			sVar.Replace("<@PatogenicitaCodice@>", CPatogenicitaSet().GetCodice(CVariantiGeneticheSet().GetIDPatogenicita(lID)));

			CString sLine;
			sLine.Format("@TABLE_%s;%s_TABLE@", CVariantiGeneticheSet().GetHGVSp(lID), sVar);

			sVarComplete += sLine;
		}
		nCur++;
	}
	VARIABLES* pVarTable5 = new VARIABLES;
	if (pVarTable5 != NULL)
	{
		pVarTable5->lIDItem = 0;
		pVarTable5->sVariable = "<@#TABLE5#@>";
		pVarTable5->sValue = sVarComplete;
		m_listVariables.AddTail(pVarTable5);
	}
	//
}

CString CGenomicaRefertoDlg::CalculateResult(long lIDSezioni)
{
	m_listVariables.RemoveAll();
	
	CString sTestoResultado = GetResultText();
	CString sTestoComplemento = GetComplementText();
	GetComplementTextInParts();
	GetOtherTexts();

	BOOL bPositivo =
		(sTestoResultado == CFrasiRisultatoSet().GetTitoloRisultato() + CFrasiRisultatoSet().GetNegativoNegativo()
		|| sTestoResultado == CFrasiRisultatoSet().GetTitoloRisultato() + CFrasiRisultatoSet().GetNegativoSingolare())
		? FALSE
		: TRUE;

	//Elaboracao do RTF

	
	VARIABLES* pVarResultadoP = new VARIABLES;
	if (pVarResultadoP != NULL)
	{
		pVarResultadoP->lIDItem = 0;
		pVarResultadoP->sVariable = "<@#RESULTADOP#@>";
		pVarResultadoP->sValue = bPositivo ? sTestoResultado : "";
		m_listVariables.AddTail(pVarResultadoP);
	}
	VARIABLES* pVarResultadoN = new VARIABLES;
	if (pVarResultadoN != NULL)
	{
		pVarResultadoN->lIDItem = 0;
		pVarResultadoN->sVariable = "<@#RESULTADON#@>";
		pVarResultadoN->sValue = bPositivo ? "" : sTestoResultado; 
		m_listVariables.AddTail(pVarResultadoN);
	}
	VARIABLES* pVarComplemento = new VARIABLES;
	if (pVarComplemento != NULL)
	{
		pVarComplemento->lIDItem = 0;
		pVarComplemento->sVariable = "<@#COMPLEMENTO#@>";
		pVarComplemento->sValue = sTestoComplemento;
		m_listVariables.AddTail(pVarComplemento);
	}

	m_ctrlTextControlHide2.ResetContents();
	m_ctrlTextControlHide2.SetRTFSelText(CSezioniSet().GetTitolo(lIDSezioni));
	m_ctrlTextControlHide2.SetSelStart(0);
	m_ctrlTextControlHide2.SetSelLength(-1);

	CString sRTF, sTXT;
	sRTF = m_ctrlTextControlHide2.GetRTFSelText();
	sTXT = m_ctrlTextControlHide2.GetSelText();
	SostituisciVariabili(sRTF, sTXT);

	m_listVariables.RemoveAll();
	m_ctrlTextControlHide2.ResetContents();
	
	return sRTF;
}

// Julio BUG 3791 - Melhoria frases resultado laudo genomica
void CGenomicaRefertoDlg::OrdenaVariantiPerPositivita()
{
	CList<VARIANTE*> listaVarianti;

	//orderna todas as variantes positivas
	for (int i = 0; i < m_ctrlListVariantiSelezionate.GetItemCount(); i++)
	{
		VARIANTE* pVariante = (VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i);
		if (pVariante->bPositivita)
			listaVarianti.AddTail(pVariante);
	}

	//ordena todas as variantes nao positivas
	for (int i = 0; i < m_ctrlListVariantiSelezionate.GetItemCount(); i++)
	{
		VARIANTE* pVariante = (VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i);
		if (!pVariante->bPositivita)
			listaVarianti.AddTail(pVariante);
	}
	

#ifdef _DEBUG
	CString sPrint;
#endif

	m_ctrlListVariantiSelezionate.DeleteAllItems();
	for (POSITION pos = listaVarianti.GetHeadPosition(); pos;)
	{
		VARIANTE* pData = (VARIANTE*)listaVarianti.GetNext(pos);
		long lID = pData->lID;

		int nItem = m_ctrlListVariantiSelezionate.InsertItem(m_ctrlListVariantiSelezionate.GetItemCount(), CVariantiGeneticheSet().GetTitolo(lID));
		m_ctrlListVariantiSelezionate.SetItemData(nItem, (DWORD_PTR)pData);

#ifdef _DEBUG
		sPrint += CVariantiGeneticheSet().GetTitolo(lID) + "\n";
#endif
	}

#ifdef _DEBUG
	AfxMessageBox(sPrint);
#endif

	listaVarianti.RemoveAll();
}

// Julio BUG 3791 - Melhoria frases resultado laudo genomica
void CGenomicaRefertoDlg::OrdenaVariantiPerTipo()
{
	CList<VARIANTE*> listaVarianti;
	
	CList<long> listaTipiVarianti;
	CTipiVariantiGeneticheSet().GetIDList(listaTipiVarianti);

	for (POSITION pos = listaTipiVarianti.GetHeadPosition(); pos;)
	{
		long lIDTipo = listaTipiVarianti.GetNext(pos);
		
		//orderna todas as variantes positivas por tipo
		for (int i = 0; i < m_ctrlListVariantiSelezionate.GetItemCount(); i++)
		{
			VARIANTE* pVariante = (VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i);
			if (pVariante->bPositivita && pVariante->lIDTipo == lIDTipo)
				listaVarianti.AddTail(pVariante);
	}

		//ordena todas as variantes nao positivas por tipo
		for (int i = 0; i < m_ctrlListVariantiSelezionate.GetItemCount(); i++)
	{
			VARIANTE* pVariante = (VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i);
			if (!pVariante->bPositivita && pVariante->lIDTipo == lIDTipo)
				listaVarianti.AddTail(pVariante);
		}
	}

#ifdef _DEBUG
	CString sPrint;
#endif

	m_ctrlListVariantiSelezionate.DeleteAllItems();
	for (POSITION pos = listaVarianti.GetHeadPosition(); pos;)
	{
		VARIANTE* pData = (VARIANTE*)listaVarianti.GetNext(pos);
		long lID = pData->lID;

		int nItem = m_ctrlListVariantiSelezionate.InsertItem(m_ctrlListVariantiSelezionate.GetItemCount(), CVariantiGeneticheSet().GetTitolo(lID));
		m_ctrlListVariantiSelezionate.SetItemData(nItem, (DWORD_PTR)pData);

#ifdef _DEBUG
		sPrint += CVariantiGeneticheSet().GetTitolo(lID) + "\n";
#endif
	}
	
#ifdef _DEBUG
	AfxMessageBox(sPrint);
#endif

	listaVarianti.RemoveAll();
}

// Julio BUG 3791 - Melhoria frases resultado laudo genomica
void CGenomicaRefertoDlg::OrdernaVarianti()
{
	//OrdenaVariantiPerTipo();
	OrdenaVariantiPerPositivita();

	// Save to database
	for (int i = 0; i < m_ctrlListVariantiSelezionate.GetItemCount(); i++)
	{
		long lIDVariante = ((VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i))->lID;
		CEsamiVariantiSelezionateSet().SetNewSelection(m_lIDEsame, lIDVariante, i, i == 0);
	}
	if (m_ctrlListVariantiSelezionate.GetItemCount() == 0)
	{
		CEsamiVariantiSelezionateSet().SetNewSelection(m_lIDEsame, 0, 0, TRUE);
	}
}

void CGenomicaRefertoDlg::LoadLastReport()
{
	CList<long> listIDVariante;
	CEsamiVariantiSelezionateSet().GetSelectionList(m_lIDEsame, listIDVariante);

	if (listIDVariante.GetCount() > 0)
	{
		m_ctrlListVariantiSelezionate.DeleteAllItems();
		
		for (POSITION pos = listIDVariante.GetHeadPosition(); pos;)
		{
			long lIDVariante = listIDVariante.GetNext(pos);
			if (lIDVariante > 0)
			{
				int nItem = m_ctrlListVariantiSelezionate.InsertItem(m_ctrlListVariantiSelezionate.GetItemCount(), CVariantiGeneticheSet().GetTitolo(lIDVariante));

				//Julio BUG 3791 - Melhoria frases resultado laudo genomica
				VARIANTE* pData = new VARIANTE;
				pData->lID = lIDVariante;
				pData->lIDTipo = CVariantiGeneticheSet().GetIDTipoVariante(lIDVariante);
				pData->lIDPatogenicita = CVariantiGeneticheSet().GetIDPatogenicita(lIDVariante);
				pData->bPositivita = CPatogenicitaSet().GetPositivita(CVariantiGeneticheSet().GetIDPatogenicita(lIDVariante));
				m_ctrlListVariantiSelezionate.SetItemData(nItem, (DWORD_PTR)pData);
				//
			}
		}		
		m_ctrlListVariantiSelezionate.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	}

	//
	long lIDTipoReferto, lIDTipoMateriale;
	CString sBasiTotali, sCoperturaMedia, sCoperturaPercentuale;
	
	CEsamiRefertoSezionatoSet().GetLastReferto(m_lIDEsame, lIDTipoReferto, lIDTipoMateriale, sBasiTotali, sCoperturaMedia, sCoperturaPercentuale);

	int nPos;
	nPos = m_ctrlComboTipoEsame.FindString(-1, CTipiRefertoSet().GetCodice(lIDTipoReferto));
	if (nPos >= 0)
		m_ctrlComboTipoEsame.SetCurSel(nPos);
	else
		m_ctrlComboTipoEsame.SetCurSel(0);

	nPos = m_ctrlComboMateriale.FindString(-1, CTipiMaterialiSet().GetCodice(lIDTipoMateriale));
	if (nPos >= 0)
		m_ctrlComboMateriale.SetCurSel(nPos);
	else
		m_ctrlComboMateriale.SetCurSel(0);

	SetDlgItemText(IDC_COPERTURAMEDIA, sCoperturaMedia);
	SetDlgItemText(IDC_PERCENTUALE, sCoperturaPercentuale);
	SetDlgItemText(IDC_TOTALIBASI, sBasiTotali);
	//

	m_ctrlTextControl.ResetContents();
	m_ctrlTextControl.SetRTFSelText(m_pEsamiView->m_pEsamiSet->m_sRefertoTestoRtf);
}

void CGenomicaRefertoDlg::OnBnClickedBtnRtfNewTable()
{
	m_ctrlTextControl.RtfInsertNewTable(this);
}

void CGenomicaRefertoDlg::OnBnClickedBtnRtfMakeUpper()
{
	m_ctrlTextControl.RtfSelectedTextMakeUpper();
}

void CGenomicaRefertoDlg::OnBnClickedBtnRtfMakeNormal()
{
	m_ctrlTextControl.RtfSelectedTextMakeNormal();
}

void CGenomicaRefertoDlg::OnBnClickedBtnRtfMakeLower()
{
	m_ctrlTextControl.RtfSelectedTextMakeLower();
}

void CGenomicaRefertoDlg::OnBnClickedBtnRtfFont() //Julio - BUG 4392 Edicao de texto
{
	m_ctrlTextControl.RtfSetFontProperties();
}

void CGenomicaRefertoDlg::OnBnClickedBtnRtfImage() //Julio - BUG 4392 Edicao de texto
{
	m_ctrlTextControl.SetImageSaveMode(1);//The image is saved with its complete binary data
	if (!m_ctrlTextControl.RtfSetImageProperties() && m_pEsamiView != NULL)
	{
		// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#1 - dual screen)
		// TODO: Ver se precisa colocar aqui também
		CImageSimple2Dlg pDlgImageSimple2(this, m_pEsamiView, FALSE);
		if (pDlgImageSimple2.DoModal() == IDOK && !pDlgImageSimple2.m_sCurImgPath.IsEmpty())
			m_ctrlTextControl.ImageInsertAsChar(pDlgImageSimple2.m_sCurImgPath, -1, 100, 100);
		  //m_ctrlTextControl.ImageInsert      (pDlgImageSimple2.m_sCurImgPath, -1, 1, 0, 0, 100, 100, 3, 100, 100, 100, 100);		
	}
}

LRESULT CGenomicaRefertoDlg::ProccessVarianteFilter(WPARAM wParam, LPARAM lParam)
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

void CGenomicaRefertoDlg::ChiediVariabiliCombo(CString& sTXT)
{
	m_listVariables.RemoveAll();

	long lVariable = 0;

	int iHasSpecialVariables = sTXT.Find("@COMBO_");
	int iLastEndPos = 0;
	while (iHasSpecialVariables >= 0)
	{
		int iPosStart = sTXT.Find("@COMBO_", iLastEndPos) + 7; //removing @COMBO_
		int iPosEnd = sTXT.Find("_COMBO@", iPosStart);

		CString sOpizioni = sTXT.Mid(iPosStart, (iPosEnd - iPosStart));

		long lArrayPos = 0;
		long lArrayCount = 15;
		CString *sArray = new CString[lArrayCount];

		int pos = 0;
		CString resToken;		
		
		resToken = sOpizioni.Tokenize(";", pos);
		CString sTitolo = resToken;

		while (resToken != _T(""))
		{
			resToken = sOpizioni.Tokenize(";", pos);			
			if (lArrayPos < lArrayCount)
			{
				sArray[lArrayPos] = resToken;
				lArrayPos++;
			}			
		}		

		CDialogWithResizableCombo dlg(this, sTitolo, sArray, lArrayCount, 1, FALSE);
		dlg.SetEsamiView(m_pEsamiView);


		if (dlg.DoModal() == IDOK)
		{
			VARIABLES* pVar = new VARIABLES;
			if (pVar != NULL)
			{
				pVar->lIDItem = 0;
				pVar->sVariable = "@COMBO_" + sOpizioni + "_COMBO@";
				pVar->sValue = dlg.m_sSelectedItem;
				m_listVariables.AddTail(pVar);
			}
		}
		else
		{
			VARIABLES* pVar = new VARIABLES;
			if (pVar != NULL)
			{
				pVar->lIDItem = 0;
				pVar->sVariable = "@COMBO_" + sOpizioni + "_COMBO@";
				pVar->sValue = "@COMBO_" + sOpizioni + "_COMBO@";
				m_listVariables.AddTail(pVar);
			}
		}

		lVariable++;
		iHasSpecialVariables = sTXT.Find("@COMBO_", iPosEnd + 1);
		iLastEndPos = iPosEnd + 1;
	}
}

void CGenomicaRefertoDlg::ChiediVariabili(CString& sTXT)
{
	m_listVariables.RemoveAll();

	long lVariable = 0;

	int iHasSpecialVariables = sTXT.Find("@");
	int iLastEndPos = 0;
	while (iHasSpecialVariables >= 0)
	{
		int iPosStart = sTXT.Find("@", iLastEndPos) + 1; //removing @
		int iPosEnd = sTXT.Find("@", iPosStart);

		if (sTXT.Find("@COMBO_", iLastEndPos) == sTXT.Find("@", iLastEndPos)) 
		{
			//this is a combo variable, it was handled in other method
		}
		else
		{
			CString sVariable = sTXT.Mid(iPosStart, (iPosEnd - iPosStart));

			CEditStringDlg dlg(this, sVariable, "");
			dlg.SetEsamiView(m_pEsamiView);
			if (dlg.DoModal() == IDOK)
			{
				VARIABLES* pVar = new VARIABLES;
				if (pVar != NULL)
				{
					pVar->lIDItem = 0;
					pVar->sVariable = "@" + sVariable + "@";
					pVar->sValue = dlg.GetValue();
					m_listVariables.AddTail(pVar);
				}
			}
			else
			{
				VARIABLES* pVar = new VARIABLES;
				if (pVar != NULL)
				{
					pVar->lIDItem = 0;
					pVar->sVariable = "@" + sVariable + "@";
					pVar->sValue = "@" + sVariable + "@";
					m_listVariables.AddTail(pVar);
				}
			}
		}

		lVariable++;
		iHasSpecialVariables = sTXT.Find("@", iPosEnd + 1);
		iLastEndPos = iPosEnd + 1;
	}
}

void CGenomicaRefertoDlg::ChiediVariabiliSpeciale(CString& sTXT)
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

CString CGenomicaRefertoDlg::ChiediValoriSpeciale(CString sVariabili)
{
	CString sResult = CVistaRefertoGenomicaSet().TryGetVaule(m_lIDEsame, sVariabili);

	if (sResult == sVariabili)
	{
		sResult = "<@" + sResult + "@>";
	}

	return sResult;
}

void CGenomicaRefertoDlg::ChiediVariabiliTabelle(CString& sTXT)
{
	m_listVariables.RemoveAll();

	long lVariable = 0;

	int iHasSpecialVariables = sTXT.Find("@TABLE_");
	int iLastEndPos = 0;
	while (iHasSpecialVariables >= 0)
	{
		int iPosStart = sTXT.Find("@TABLE_", iLastEndPos) + 7; //removing @TABLE_
		int iPosEnd = sTXT.Find("_TABLE@", iPosStart);

		CString sOpizioni = sTXT.Mid(iPosStart, (iPosEnd - iPosStart));

		long lArrayPos = 0;
		long lArrayCount = 15;
		CString *sArray = new CString[lArrayCount];

		int pos = 0;
		CString resToken;

		resToken = sOpizioni.Tokenize(";", pos);
		CString sTitolo = resToken;

		while (resToken != _T(""))
		{
			resToken = sOpizioni.Tokenize(";", pos);
			if (lArrayPos < lArrayCount)
			{
				sArray[lArrayPos] = resToken;
				lArrayPos++;
			}
		}
			
		VARIABLES* pVar = new VARIABLES;
		if (pVar != NULL)
		{
			pVar->lIDItem = 0;
			pVar->sVariable = "@TABLE_" + sOpizioni + "_TABLE@";
			pVar->sValue = CreateRTFTable(sTitolo, atol(sArray[0]), atol(sArray[1]), sArray);
			m_listVariables.AddTail(pVar);
		}
		
		lVariable++;
		iHasSpecialVariables = sTXT.Find("@TABLE_", iPosEnd + 1);
		iLastEndPos = iPosEnd + 1;
	}
}

void CGenomicaRefertoDlg::SostituisciVariabili(CString& sRTF, CString& sTXT)
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

				if (pVal->sValue.Find("{") == 0) //if the value is RTF add as RTF
					m_ctrlTextControlHide.SetRTFSelText(pVal->sValue);
				else //add as non formatted text
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

void CGenomicaRefertoDlg::InputSectionWithGroupedValues(long lIDSezione)
{
	long lIDTipoVariante = CSezioniSet().GetTipoVariante(lIDSezione);

	BOOL bFound = FALSE; //Check if the user selected at least one variant with the section's tipovariante
	for (int i = 0; i < m_ctrlListVariantiSelezionate.GetItemCount(); i++)
	{
		long lIDVariante = ((VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i))->lID;

		if (lIDTipoVariante == CVariantiGeneticheSet().GetIDTipoVariante(lIDVariante))
			bFound = TRUE;
	}
	
	if (bFound)
	{
		CString sRTF = CSezioniSet().GetTitolo(lIDSezione);
		m_ctrlTextControlHide.SetRTFSelText(sRTF);

		for (int i = 0; i < m_ctrlListVariantiSelezionate.GetItemCount(); i++)
		{
			long lIDVariante = ((VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i))->lID;

			if (lIDTipoVariante == CVariantiGeneticheSet().GetIDTipoVariante(lIDVariante))
			{
				sRTF = CCorpoSezioneSet().GetCorpoRtf(lIDSezione, lIDVariante);
				m_ctrlTextControlHide.SetRTFSelText(sRTF);
			}
		}
	}
}

void CGenomicaRefertoDlg::OnBnClickedBtnGenera()
{
	m_ctrlTextControl.EnableWindow(FALSE);
	OrdernaVarianti();
	
	long lIDTipoReferto = m_ctrlComboTipoEsame.GetItemData(m_ctrlComboTipoEsame.GetCurSel());
	long lIDTipoMateriale = m_ctrlComboMateriale.GetItemData(m_ctrlComboMateriale.GetCurSel());

	CString sCoperturaMedia, sCoperturaPercentuale, sTotaliBasi;
	GetDlgItemText(IDC_COPERTURAMEDIA, sCoperturaMedia);
	GetDlgItemText(IDC_PERCENTUALE, sCoperturaPercentuale);
	GetDlgItemText(IDC_TOTALIBASI, sTotaliBasi);

	if (CEsamiRefertoSezionatoSet().SetNewReferto(m_lIDEsame, lIDTipoReferto, lIDTipoMateriale,
		sTotaliBasi, sCoperturaMedia, sCoperturaPercentuale))
	{
		m_ctrlTextControlHide.ResetContents();

		CString sRTF, sRTFRisultato;
		long lRefertoLen = 0;

		sRTF = CTipiRefertoSet().GetTitolo(lIDTipoReferto);

		long lResultID = CSezioniSet().GetRisultatoID(lIDTipoReferto);
		if (lResultID > 0)
			sRTFRisultato = CalculateResult(lResultID);
		
		m_ctrlTextControlHide.SetRTFSelText(sRTF);

		CList<long> listSezioni;
		CSezioniSet().GetIDListByTipoReferto(listSezioni, lIDTipoReferto);

		for (POSITION pos = listSezioni.GetHeadPosition(); pos;)
		{
			long lIDSezioni = listSezioni.GetNext(pos);

			if (CSezioniSet().GetRisultato(lIDSezioni, lIDTipoReferto)) //Current section is a calculated result seciton
			{
				m_ctrlTextControlHide.SetRTFSelText(sRTFRisultato);
				sRTFRisultato = ""; //just in case someone register more than one section as a result section							
			}
			else if (CSezioniSet().GetTipoVariante(lIDSezioni) > 0) //Current section is dependent on tipovariante
			{
				InputSectionWithGroupedValues(lIDSezioni);
			}
			else //Current section is a normal section
			{
				sRTF = CSezioniSet().GetTitolo(lIDSezioni);
				m_ctrlTextControlHide.SetRTFSelText(sRTF);

				for (int i = 0; i < m_ctrlListVariantiSelezionate.GetItemCount(); i++)
				{
					long lIDVariante = ((VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i))->lID;
					sRTF = CCorpoSezioneSet().GetCorpoRtf(lIDSezioni, lIDVariante);
					m_ctrlTextControlHide.SetRTFSelText(sRTF);
				}
			}
		}

		m_ctrlTextControlHide.SetSelStart(0);
		m_ctrlTextControlHide.SetSelLength(-1);
		sRTF = m_ctrlTextControlHide.GetRTFSelText();

		m_ctrlTextControl.ResetContents();
		m_ctrlTextControl.SetRTFSelText(sRTF);
	}

	CString sRTF, sTXT;
	//Special variables 
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);
	sRTF = m_ctrlTextControl.GetRTFSelText();
	sTXT = m_ctrlTextControl.GetSelText();

	ChiediVariabiliSpeciale(sTXT);
	SostituisciVariabili(sRTF, sTXT);

	m_ctrlTextControl.ResetContents();
	m_ctrlTextControl.SetRTFSelText(sRTF);
	//

	//Table variables @TABLE@
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);
	sRTF = m_ctrlTextControl.GetRTFSelText();
	sTXT = m_ctrlTextControl.GetSelText();

	ChiediVariabiliTabelle(sTXT);
	SostituisciVariabili(sRTF, sTXT);

	m_ctrlTextControl.ResetContents();
	m_ctrlTextControl.SetRTFSelText(sRTF);
	//


	//Combo variables @COMBO@
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);
	sRTF = m_ctrlTextControl.GetRTFSelText();
	sTXT = m_ctrlTextControl.GetSelText();

	ChiediVariabiliCombo(sTXT);
	SostituisciVariabili(sRTF, sTXT);

	m_ctrlTextControl.ResetContents();
	m_ctrlTextControl.SetRTFSelText(sRTF);
	//
	
	//Normal variables @@
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);
	sRTF = m_ctrlTextControl.GetRTFSelText();
	sTXT = m_ctrlTextControl.GetSelText();

	ChiediVariabili(sTXT);
	SostituisciVariabili(sRTF, sTXT);

	m_ctrlTextControl.ResetContents();
	m_ctrlTextControl.SetRTFSelText(sRTF);
	//

	//Manage the @ symbol
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);
	
	sRTF = m_ctrlTextControl.GetRTFSelText();		
	sRTF.Replace("&#64;", "@");	
	sRTF.Replace("&#13;", "\\line ");
	
	m_ctrlTextControl.ResetContents();
	m_ctrlTextControl.SetRTFSelText(sRTF);
	//

	m_ctrlTextControl.EnableWindow(TRUE);
}

void CGenomicaRefertoDlg::OnBnClickedBtnAnnulla()
{
	OnCancel();
}

void CGenomicaRefertoDlg::OnBnClickedBtnSalva()
{
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);

	CString sRefertoRtf = m_ctrlTextControl.GetRTFSelText();
	CString sRefertoTxt = m_ctrlTextControl.GetText();

	//removing tables fixed width for genomica reports
	CString sRefertoHtml = m_ctrlTextControl.GetHTMLSelText();
	
	int nPos = 0;
	while (nPos < sRefertoHtml.GetLength())
	{
		int nTablePos = sRefertoHtml.Find("<table", nPos);//find table tag
		if (nTablePos < 0)
			break;

		int nWidthPos = sRefertoHtml.Find("width:", nTablePos); //find width property inside table tag
		int nSemiCPos = sRefertoHtml.Find(";", nWidthPos) + 1; //find the ; after the width property
		int nTablePosEnd = sRefertoHtml.Find(">", nTablePos);//find table tag

		CString sTableTag = sRefertoHtml.Mid(nTablePos, (nTablePosEnd - nTablePos) + 1);
		CString sTableTagRep = sRefertoHtml.Mid(nTablePos, (nTablePosEnd - nTablePos) + 1);
		CString sWidthVal = sRefertoHtml.Mid(nWidthPos + 6, ((nSemiCPos - 1) - (nWidthPos + 6))).Trim();

	
		sTableTagRep.Replace(sWidthVal, "100%");
		sRefertoHtml.Replace(sTableTag, sTableTagRep);
		
		nPos = nTablePos + 1;
	}
	//


	if (m_pEsamiView->m_pEsamiSet != NULL)
		m_pEsamiView->m_pEsamiSet->SetReferto(sRefertoRtf, sRefertoTxt, sRefertoHtml);

	OnOK();
}

void CGenomicaRefertoDlg::OnBnClickedBtnSu()
{
	int sel = m_ctrlListVariantiSelezionate.GetNextItem(-1, LVNI_SELECTED);
	// Move up or down
	int next = sel - 1;
	if (next < 0 || next >= m_ctrlListVariantiSelezionate.GetItemCount())
		return;

	CString sSel, sNext;
	long lSel, lNext;
	for (int i = 0; i < m_ctrlListVariantiSelezionate.GetHeaderCtrl()->GetItemCount(); i++)
	{
		sSel = m_ctrlListVariantiSelezionate.GetItemText(sel, i);
		lSel = m_ctrlListVariantiSelezionate.GetItemData(sel);

		sNext = m_ctrlListVariantiSelezionate.GetItemText(next, i);
		lNext = m_ctrlListVariantiSelezionate.GetItemData(next);

		m_ctrlListVariantiSelezionate.SetItemText(sel, i, sNext);
		m_ctrlListVariantiSelezionate.SetItemData(sel, lNext);

		m_ctrlListVariantiSelezionate.SetItemText(next, i, sSel);
		m_ctrlListVariantiSelezionate.SetItemData(next, lSel);
	}
	// Move selection
	m_ctrlListVariantiSelezionate.SetItemState(sel, ~LVNI_SELECTED, LVIS_SELECTED);
	m_ctrlListVariantiSelezionate.SetItemState(next, LVNI_SELECTED, LVIS_SELECTED);
	m_ctrlListVariantiSelezionate.SetSelectionMark(next);
}

void CGenomicaRefertoDlg::OnBnClickedBtnGiu()
{
	int sel = m_ctrlListVariantiSelezionate.GetNextItem(-1, LVNI_SELECTED);
	// Move up or down
	int next = sel + 1;
	if (next < 0 || next >= m_ctrlListVariantiSelezionate.GetItemCount())
		return;

	CString strSel, strNext;
	for (int i = 0; i < m_ctrlListVariantiSelezionate.GetHeaderCtrl()->GetItemCount(); i++)
	{
		strSel = m_ctrlListVariantiSelezionate.GetItemText(sel, i);
		strNext = m_ctrlListVariantiSelezionate.GetItemText(next, i);

		m_ctrlListVariantiSelezionate.SetItemText(sel, i, strNext);
		m_ctrlListVariantiSelezionate.SetItemText(next, i, strSel);
	}
	// Move selection
	m_ctrlListVariantiSelezionate.SetItemState(sel, ~LVNI_SELECTED, LVIS_SELECTED);
	m_ctrlListVariantiSelezionate.SetItemState(next, LVNI_SELECTED, LVIS_SELECTED);
	m_ctrlListVariantiSelezionate.SetSelectionMark(next);
}

void CGenomicaRefertoDlg::OnBnClickedBtnRimuove()
{
	POSITION pos = m_ctrlListVariantiSelezionate.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlListVariantiSelezionate.GetNextSelectedItem(pos);
		m_ctrlListVariantiSelezionate.DeleteItem(iCurSel);
	}
}

void CGenomicaRefertoDlg::OnNMDblclkListVarianti(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	POSITION pos = m_ctrlListVarianti.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlListVarianti.GetNextSelectedItem(pos);
		long lID = (long)m_ctrlListVarianti.GetItemData(iCurSel);

		if (lID > 0)
		{
			BOOL bCanInsert = TRUE;
			int nLast = m_ctrlListVariantiSelezionate.GetItemCount();

			for (int i = 0; i < nLast; i++)
			{
				if (((VARIANTE*)m_ctrlListVariantiSelezionate.GetItemData(i))->lID == lID)
				{
					AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO3));
					bCanInsert = FALSE;
					break;
				}
			}
			if (bCanInsert)
			{
				m_ctrlListVariantiSelezionate.SetRedraw(FALSE);

				int nItem = m_ctrlListVariantiSelezionate.InsertItem(m_ctrlListVariantiSelezionate.GetItemCount(), CVariantiGeneticheSet().GetTitolo(lID));

				//Julio BUG 3791 - Melhoria frases resultado laudo genomica
				VARIANTE* pData = new VARIANTE;
				pData->lID = lID;
				pData->lIDTipo = CVariantiGeneticheSet().GetIDTipoVariante(lID);
				pData->lIDPatogenicita = CVariantiGeneticheSet().GetIDPatogenicita(lID);
				pData->bPositivita = CPatogenicitaSet().GetPositivita(CVariantiGeneticheSet().GetIDPatogenicita(lID));
				m_ctrlListVariantiSelezionate.SetItemData(nItem, (DWORD_PTR)pData);
				//

				m_ctrlListVariantiSelezionate.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
				m_ctrlListVariantiSelezionate.SetRedraw(TRUE);
			}
		}
	}

	*pResult = 0;
}

//Julio BUG 3457 - Texter
LRESULT CGenomicaRefertoDlg::OnKeyboardPress(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_F3:
	case VK_TAB:
	{
		CWnd* pFocusWnd = GetFocus();
		if (pFocusWnd && pFocusWnd->IsKindOf(RUNTIME_CLASS(CTXTextControl23Ex)))
			if (pFocusWnd->GetDlgCtrlID() == IDC_TEXTCONTROL)
			{
				int iSelStart = m_ctrlTextControl.GetSelStart();
				int iSelLength = m_ctrlTextControl.GetSelLength();

				int iStartSearch = iSelStart + iSelLength;
				if (iStartSearch <= 0)
					return 0;

				m_ctrlTextControl.SetRedraw(FALSE);

				CString strWord;
				while (--iStartSearch >= 0 && (strWord.GetLength() == 0 || (strWord.GetAt(0) != ' ' && strWord.GetAt(0) != '\n')))
				{
					m_ctrlTextControl.SetSelStart(iStartSearch);
					m_ctrlTextControl.SetSelLength(1);
					strWord = m_ctrlTextControl.GetSelText() + strWord;
				}

				if (strWord.GetAt(0) == ' ' || strWord.GetAt(0) == '\n')
					strWord = strWord.Right(strWord.GetLength() - 1);

				if (strWord.GetLength() >= 2)
				{
					m_ctrlTextControl.SetSelStart(iSelStart - iSelLength - strWord.GetLength());
					m_ctrlTextControl.SetSelLength(strWord.GetLength());

					SearchAndReplaceTexterPhrase(strWord.Trim());	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
				}

				m_ctrlTextControl.SetRedraw(TRUE);
				m_ctrlTextControl.RedrawWindow();

				return 0;
			}
		break;
	}
	}
	return 0;

}


// Marvel Carvalho - Bug 3457 (FIX) TEXTER
void CGenomicaRefertoDlg::ApplyTexterPhrase(long p_lIDFrase)
{
	CString sFraseRtf = CFrasiRtfSet().GetTestoRtf(p_lIDFrase);
	CString sFraseTxt = CFrasiRtfSet().GetTestoTxt(p_lIDFrase);

	if (!sFraseRtf.IsEmpty())
	{
		try
		{
			if (theApp.m_bUsaTexterAsRTF)
			{				
				//Normal variables @@
				ChiediVariabili(sFraseTxt);
				SostituisciVariabili(sFraseRtf, sFraseTxt);
				//
				CString sFraseRtfCleaned = cleanFinalDoubleParInRTF(sFraseRtf);

				m_ctrlTextControl.SetRTFSelText(sFraseRtfCleaned); //quando insiro o texto como rtf o TX Text Control sempre coloca um enter no final do texto
				// remove um ENTER extra que a função SetRTFSelText adiciona indevidamente
				pressKey(VK_BACK);  // BACKSPACE key
			}
			else
			{
				m_ctrlTextControl.SetSelText(sFraseTxt);
			}			
		}
		catch (CException* e)
		{
			TCHAR szError[255];
			e->GetErrorMessage(szError, 255);
			e->Delete();
		}
	}
}

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
void CGenomicaRefertoDlg::SearchAndReplaceTexterPhrase(CString sFrase)
{
	BeginWaitCursor();

	long lIDFrase = CFrasiRtfSet().GetIDByCodice(sFrase);
	if (lIDFrase > 0)
	{
		ApplyTexterPhrase(lIDFrase);
	}
	else
	{
		m_ctrlTextControl.SetSelStart(m_ctrlTextControl.GetSelStart() + m_ctrlTextControl.GetSelLength());
		m_ctrlTextControl.SetSelLength(0);
	}

	EndWaitCursor();
}

CString CGenomicaRefertoDlg::CreateRTFTable(CString sTitle, long lRows, long lCols, CString* sValArray)
{
	CString sTable = "";
	for (int r = 0; r < lRows; r++)
	{
		CString sRow = "\\trowd";
		for (int c = 0; c < lCols; c++)
		{
			CString sColID;
			sColID.Format("%s col:%li", sTitle, c + 1);

			CString sCellx;
			sCellx.Format("%li", (c + 1) * 1500);

			CString sCol;
			if (!sValArray[(c+1)*(r+1)+1].IsEmpty())
			{
				sCol = "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx" + sCellx + " " + sValArray[(c+1)*(r+1)+1] + "\\intbl\\cell";
			}
			else
			{
				sCol = "\\clbrdrt\\brdrs\\clbrdrl\\brdrs\\clbrdrb\\brdrs\\clbrdrr\\brdrs\\cellx" + sCellx + "\\\'40" + sColID + "\\'40\\intbl\\cell";
			}
			
			sRow += sCol;
		}
		sRow += "\\row";
		sTable += sRow;
	}
	CString sRTF = "{\\rtf1\\ansi\\deff" + sTable + "}";

	return sRTF;
}