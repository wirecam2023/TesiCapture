#include "stdafx.h"
#include "Endox.h"
#include "Common.h"
#include "GenomicaSezioniDlg.h"
#include "TipiVariantiGeneticheSet.h"
#include "TipiRefertoSet.h"
#include "SezioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGenomicaSezioniDlg, CDialog)

CGenomicaSezioniDlg::CGenomicaSezioniDlg(CWnd* pParent)
	: CDialog(CGenomicaSezioniDlg::IDD, pParent)
{
	m_lIdTipoRefertoSelected = -1;
	m_lIdSezioniSelected = -1;
}

CGenomicaSezioniDlg::~CGenomicaSezioniDlg()
{
}

BEGIN_MESSAGE_MAP(CGenomicaSezioniDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_TIPI_REFERTO, &CGenomicaSezioniDlg::OnLvnItemchangedListTipiReferto)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SEZIONI, &CGenomicaSezioniDlg::OnLvnItemchangedListSezione)


	ON_BN_CLICKED(IDC_BTN_NEW, &CGenomicaSezioniDlg::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, &CGenomicaSezioniDlg::OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, &CGenomicaSezioniDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CGenomicaSezioniDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, &CGenomicaSezioniDlg::OnBnClickedBtnUndo)

	ON_BN_CLICKED(IDC_BTN_SU, &CGenomicaSezioniDlg::OnBnClickedBtnSu)
	ON_BN_CLICKED(IDC_BTN_GIU, &CGenomicaSezioniDlg::OnBnClickedBtnGiu)

	ON_COMMAND(IDC_RTF_TABLE, &CGenomicaSezioniDlg::OnBnClickedBtnRtfNewTable)
	ON_COMMAND(IDC_RTF_MAKEUPPER, &CGenomicaSezioniDlg::OnBnClickedBtnRtfMakeUpper)
	ON_COMMAND(IDC_RTF_MAKENORMAL, &CGenomicaSezioniDlg::OnBnClickedBtnRtfMakeNormal)
	ON_COMMAND(IDC_RTF_MAKELOWER, &CGenomicaSezioniDlg::OnBnClickedBtnRtfMakeLower)
	ON_COMMAND(IDC_RTF_FONT, &CGenomicaSezioniDlg::OnBnClickedBtnRtfFont) //Julio - BUG 4392 Edicao de texto
END_MESSAGE_MAP()

void CGenomicaSezioniDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlButtonEdit);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_LIST_TIPI_REFERTO, m_ctrlListTipiReferto);
	DDX_Control(pDX, IDC_LIST_SEZIONI, m_ctrlListSezione);

	DDX_Control(pDX, IDC_BTN_SU, m_ctrlButtonSu);
	DDX_Control(pDX, IDC_BTN_GIU, m_ctrlButtonGiu);

	DDX_Control(pDX, IDC_RISULTATO, m_ctrlButtonRisultato);
	DDX_Control(pDX, IDC_TIPOVARIANTE, m_ctrlComboTipoVariante);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	
	DDX_Control(pDX, IDC_BUTTONBAR, m_ctrlButtonBar);
	DDX_Control(pDX, IDC_BUTTONBAR2, m_ctrlButtonBar2);

	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //

	DDX_Control(pDX, IDC_TEXTCONTROL2, m_ctrlTextControl2);
	m_ctrlTextControl2.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //
}

BOOL CGenomicaSezioniDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlListTipiReferto.SetExtendedStyle(m_ctrlListTipiReferto.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlListTipiReferto.InsertColumn(0, theApp.GetMessageString(IDS_GENOMICA_SEZIONE_TIPO_REFERTO), LVCFMT_LEFT, 0);	//"scegli il tipo referto"
	RiempiListaTipiReferto();

	m_ctrlListSezione.SetExtendedStyle(m_ctrlListSezione.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlListSezione.InsertColumn(0, "Codice", LVCFMT_LEFT, 0);

	RiempiListaSezioni();
	RiempiCombo();

	//
	m_ctrlToolbar.Create(IDC_BUTTONBAR_PLACE, this);
	m_ctrlToolbar.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	::SetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE, (GetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE) & ~WS_CLIPCHILDREN) & ~WS_CLIPSIBLINGS);

	m_ctrlTextControl.SetButtonBarHandle((long)m_ctrlButtonBar.GetSafeHwnd());
	m_ctrlTextControl.SetFontName(g_sReportFaceName);
	m_ctrlTextControl.SetFontSize(g_nReportSize);
	m_ctrlTextControl.SetFontBold(g_bReportBold);
	m_ctrlTextControl.SetFontItalic(g_bReportItalic);
	m_ctrlTextControl.SetFontUnderline(g_bReportUnderline);

	m_ctrlTextControl.EnableWindow(FALSE);
	m_ctrlButtonBar.EnableWindow(FALSE);
	m_ctrlToolbar.EnableWindow(FALSE);
	//

	//
	m_ctrlToolbar2.Create(IDC_BUTTONBAR_PLACE2, this);
	m_ctrlToolbar2.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	::SetWindowLong(m_ctrlButtonBar2.GetSafeHwnd(), GWL_STYLE, (GetWindowLong(m_ctrlButtonBar2.GetSafeHwnd(), GWL_STYLE) & ~WS_CLIPCHILDREN) & ~WS_CLIPSIBLINGS);

	m_ctrlTextControl2.SetButtonBarHandle((long)m_ctrlButtonBar2.GetSafeHwnd());
	m_ctrlTextControl2.SetFontName(g_sReportFaceName);
	m_ctrlTextControl2.SetFontSize(g_nReportSize);
	m_ctrlTextControl2.SetFontBold(g_bReportBold);
	m_ctrlTextControl2.SetFontItalic(g_bReportItalic);
	m_ctrlTextControl2.SetFontUnderline(g_bReportUnderline);

	m_ctrlTextControl2.EnableWindow(FALSE);
	m_ctrlButtonBar2.EnableWindow(FALSE);
	m_ctrlToolbar2.EnableWindow(FALSE);
	//

	EditDialog(FALSE);

	theApp.LocalizeDialog(this, CGenomicaSezioniDlg::IDD, "CGenomicaSezioniDlg");

	m_lIdTipoRefertoSelected = -1;

	return TRUE;
}

void CGenomicaSezioniDlg::OnOK()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnOK();
}

void CGenomicaSezioniDlg::OnCancel()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}


void CGenomicaSezioniDlg::RiempiListaTipiReferto()
{
	BeginWaitCursor();

	// 1a. LISTA - TIPI REFERTO
	{
		m_ctrlListTipiReferto.SetRedraw(FALSE);
		m_ctrlListTipiReferto.DeleteAllItems();

		CList<long> listID;
		CTipiRefertoSet().GetIDTipoRefertoList(listID);

		for (POSITION pos = listID.GetHeadPosition(); pos;)
		{
			long lID = listID.GetNext(pos);

			//int nItem = m_ctrlListTipiReferto.InsertItem(m_ctrlListTipiReferto.GetItemCount(), CTipiRefertoSet().GetCodiceByIdTipoReferto(lID));
			int nItem = m_ctrlListTipiReferto.InsertItem(m_ctrlListTipiReferto.GetItemCount(), CTipiRefertoSet().GetCodice(lID));
			m_ctrlListTipiReferto.SetItemData(nItem, (DWORD)lID);
		}

		m_ctrlListTipiReferto.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListTipiReferto.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListTipiReferto.SetRedraw(TRUE);
	}

	EndWaitCursor();
}

void CGenomicaSezioniDlg::RiempiListaSezioni()
{
	if (m_lIdTipoRefertoSelected < 0)
	{
		CaricaDati(); // em branco
		return;
	}

	BeginWaitCursor();

	// 2a LISTA - SEZIONI
	{
		m_ctrlListSezione.SetRedraw(FALSE);
		m_ctrlListSezione.DeleteAllItems();

		CList<long> listID;
		CSezioniSet().GetIDListByTipoReferto(listID, m_lIdTipoRefertoSelected);

		for (POSITION pos = listID.GetHeadPosition(); pos;)
		{
			long lID = listID.GetNext(pos);

			int nItem = m_ctrlListSezione.InsertItem(m_ctrlListSezione.GetItemCount(), CSezioniSet().GetCodice(lID));
			m_ctrlListSezione.SetItemData(nItem, (DWORD)lID);
		}

		m_ctrlListSezione.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListSezione.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListSezione.SetRedraw(TRUE);
	}

	CaricaDati(); // em branco
	EndWaitCursor();
}


void CGenomicaSezioniDlg::RiempiCombo()
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
	m_ctrlComboTipoVariante.SetCurSel(0);
}

void CGenomicaSezioniDlg::RiempiComboUnselectAll()
{
	m_ctrlComboTipoVariante.SetCurSel(0);
}

void CGenomicaSezioniDlg::CaricaDati()
{
	SetDlgItemText(IDC_CODICE, "");
	SetDlgItemText(IDC_ORDINE, "");
	m_ctrlTextControl.ResetContents();
	m_ctrlTextControl2.ResetContents();

	RiempiComboUnselectAll();

	if (m_lIdSezioniSelected > 0)
	{
		SetDlgItemText(IDC_CODICE, CSezioniSet().GetCodice(m_lIdSezioniSelected));

		CString sOrdine;
		sOrdine.Format("%li", CSezioniSet().GetOrdine(m_lIdSezioniSelected));
		if (sOrdine == "0")
		{
			sOrdine.Format("%li", CSezioniSet().GetNextMaxOrdine(m_lIdTipoRefertoSelected));
		}
		SetDlgItemText(IDC_ORDINE, sOrdine);

		m_ctrlTextControl.SetRTFSelText(CSezioniSet().GetTitolo(m_lIdSezioniSelected));
		m_ctrlTextControl2.SetRTFSelText(CSezioniSet().GetTestoRtf(m_lIdSezioniSelected, 1));

		m_ctrlButtonRisultato.SetCheck(CSezioniSet().GetRisultato(m_lIdSezioniSelected, m_lIdTipoRefertoSelected) ? BST_CHECKED : BST_UNCHECKED);

		int nPos;
		nPos = m_ctrlComboTipoVariante.FindString(-1, CTipiVariantiGeneticheSet().GetCodice(CSezioniSet().GetTipoVariante(m_lIdSezioniSelected)));
		if (nPos >= 0)
			m_ctrlComboTipoVariante.SetCurSel(nPos);
		else
			m_ctrlComboTipoVariante.SetCurSel(0);
	}
	//
	GetDlgItem(IDC_BTN_EDT)->EnableWindow(m_lIdSezioniSelected > 0);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(m_lIdSezioniSelected > 0);
	GetDlgItem(IDC_BTN_SU)->EnableWindow(m_lIdSezioniSelected > 0);
	GetDlgItem(IDC_BTN_GIU)->EnableWindow(m_lIdSezioniSelected > 0);
}

void CGenomicaSezioniDlg::UnselectAll()
{
	if (m_ctrlListTipiReferto.GetItemCount() > 0)
	{
		for (int i = 0; i < m_ctrlListTipiReferto.GetItemCount(); i++)
			m_ctrlListTipiReferto.SetItemState(i, 0, LVIS_SELECTED);
	}
	else
	{
		OnLvnItemchangedListTipiReferto(NULL, NULL);
	}

	if (m_ctrlListSezione.GetItemCount() > 0)
	{
		for (int i = 0; i < m_ctrlListSezione.GetItemCount(); i++)
			m_ctrlListSezione.SetItemState(i, 0, LVIS_SELECTED);
	}
	else
	{
		OnLvnItemchangedListSezione(NULL, NULL);
	}
}

void CGenomicaSezioniDlg::EditDialog(BOOL bEdit)
{
	m_ctrlListTipiReferto.EnableWindow(!bEdit);
	m_ctrlListSezione.EnableWindow(!bEdit);
	SendDlgItemMessage(IDC_CODICE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_ORDINE, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);

	m_ctrlTextControl.EnableWindow(bEdit);
	m_ctrlToolbar.EnableWindow(bEdit);
	m_ctrlButtonBar.EnableWindow(bEdit);

	m_ctrlTextControl2.EnableWindow(bEdit);
	m_ctrlToolbar2.EnableWindow(bEdit);
	m_ctrlButtonBar2.EnableWindow(bEdit);

	m_ctrlComboTipoVariante.EnableWindow(bEdit);
	GetDlgItem(IDC_RISULTATO)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_NEW)->EnableWindow(!bEdit);		// not available NEW for tipo referto, only available NEW for sezione
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit) && m_lIdSezioniSelected > 0);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!bEdit) && m_lIdSezioniSelected > 0);
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_SU)->EnableWindow(m_lIdSezioniSelected > 0);
	GetDlgItem(IDC_BTN_GIU)->EnableWindow(m_lIdSezioniSelected > 0);
}


// CGenomicaTipiVariantiDlg message handlers
void CGenomicaSezioniDlg::OnBnClickedBtnNew()
{
	UnselectAll();
	EditDialog(TRUE);
}

void CGenomicaSezioniDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}

void CGenomicaSezioniDlg::OnBnClickedBtnDel()
{
	if (AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		if (m_lIdSezioniSelected > 0)
		{
			if (!CSezioniSet().SetEliminato(m_lIdSezioniSelected))
				AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO1));
		}
		UnselectAll();
		RiempiListaSezioni();
	}
}

void CGenomicaSezioniDlg::OnBnClickedBtnUndo()
{
	UnselectAll();
	RiempiListaSezioni();
	EditDialog(FALSE);
}

void CGenomicaSezioniDlg::OnBnClickedBtnSave()
{
	if (m_lIdTipoRefertoSelected <= 0)
	{
		AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO4), MB_ICONSTOP);	// Não foi possivel salvar as informações
		OnBnClickedBtnUndo();
		return;
	}

	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);

	m_ctrlTextControl2.SetSelStart(0);
	m_ctrlTextControl2.SetSelLength(-1);

	if (!UpdateData(TRUE))
		return;

	CString strTemp;

	GetDlgItemText(IDC_CODICE, strTemp);
	strTemp.Trim();

	if (!strTemp.IsEmpty() && 
		((m_ctrlButtonRisultato.GetCheck() == BST_UNCHECKED) || !CSezioniSet().VerifyRisultadoField(m_lIdSezioniSelected, m_lIdTipoRefertoSelected))) //Verificando se ja existe um campo de resultado salvo
	{
		if (m_lIdSezioniSelected <= 0)
		{
			// addnew //
			CSezioniSet setTemp;
			setTemp.SetOpenFilter((LPCTSTR)"");
			if (setTemp.OpenRecordset("CGenomicaSezioniDlg::OnBnClickedBtnSave"))
			{
				if (setTemp.AddNewRecordset("CGenomicaSezioniDlg::OnBnClickedBtnSave"))
				{					
					setTemp.m_lIDTipoReferto = m_lIdTipoRefertoSelected;

					GetDlgItemText(IDC_CODICE, setTemp.m_sCodice);

					CString sOrdine;
					GetDlgItemText(IDC_ORDINE, sOrdine);

					setTemp.m_lOrdine = atol(sOrdine);
					if (setTemp.m_lOrdine <= 0)
						setTemp.m_lOrdine = CSezioniSet().GetNextMaxOrdine(m_lIdTipoRefertoSelected);

					setTemp.m_lIDTipoVariante = m_ctrlComboTipoVariante.GetItemData(m_ctrlComboTipoVariante.GetCurSel());
					setTemp.m_sTitoloRtf = m_ctrlTextControl.GetRTFSelText();
					setTemp.m_sTestoRtf001 = m_ctrlTextControl2.GetRTFSelText();
					setTemp.m_bRisultato = (m_ctrlButtonRisultato.GetCheck() == BST_CHECKED);					
					setTemp.m_bEliminato = FALSE;

					setTemp.UpdateRecordset("CGenomicaSezioniDlg::OnBnClickedBtnSave");
				}
				setTemp.CloseRecordset("CGenomicaSezioniDlg::OnBnClickedBtnSave");
			}
		}
		else
		{
			CSezioniSet().SetTipoReferto(m_lIdSezioniSelected, m_lIdTipoRefertoSelected);

			CString sCodice;
			GetDlgItemText(IDC_CODICE, sCodice);
			CSezioniSet().SetCodice(m_lIdSezioniSelected, sCodice);

			CString sOrdine;
			GetDlgItemText(IDC_ORDINE, sOrdine);
			CSezioniSet().SetOrdine(m_lIdSezioniSelected, atol(sOrdine));

			CSezioniSet().SetTipoVariante(m_lIdSezioniSelected, m_ctrlComboTipoVariante.GetItemData(m_ctrlComboTipoVariante.GetCurSel()));
			
			CSezioniSet().SetTitolo(m_lIdSezioniSelected, m_ctrlTextControl.GetRTFSelText());

			CSezioniSet().SetTestoRtf(m_lIdSezioniSelected, 1, m_ctrlTextControl2.GetRTFSelText());

			CSezioniSet().SetRisultato(m_lIdSezioniSelected, (m_ctrlButtonRisultato.GetCheck() == BST_CHECKED));
		}

		UnselectAll();
		RiempiListaSezioni();
		EditDialog(FALSE);
	}
	else
	{
		AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO4), MB_ICONSTOP);
	}
}

//CString CGenomicaSezioniDlg::m_ctrlListBoxTipoVariante_GetStringVari()
//{
//	// Works with multiple selection
//	int count = m_ctrlListBoxTipoVariante.GetSelCount();
//	int* lp = new int[256];
//	int count2 = m_ctrlListBoxTipoVariante.GetSelItems(255, lp);
//	for (int i = 0; i < count2; i++)
//	{
//		CString str;
//		m_ctrlListBoxTipoVariante.GetText(lp[i], str);
//		//MessageBox(str);
//	}
//	delete[] lp;
//
//	CString strAuxConcat = "";
//	int numberSelected = m_ctrlListBoxTipoVariante.GetSelCount();
//	if (numberSelected > 0)
//	{
//		int* selIndex = new int[numberSelected];
//		m_ctrlListBoxTipoVariante.GetSelItems(numberSelected, selIndex);
//		for (int i = 0; i < numberSelected; i++)
//		{
//			//CString str;
//			//m_ctrlListBoxTipoVariante.GetText(selIndex[i], str);
//			long lAuxID = m_ctrlListBoxTipoVariante.GetItemData(selIndex[i]);
//			CString sAuxID;
//			sAuxID.Format("%ld", lAuxID);
//
//			if (!sAuxID.IsEmpty())
//			{
//				if (!strAuxConcat.IsEmpty())
//				{
//					strAuxConcat += ",";
//				}
//				strAuxConcat += sAuxID;
//			}
//		}
//		delete[] selIndex;
//	}
//	return strAuxConcat;
//}

void CGenomicaSezioniDlg::OnBnClickedBtnSu() // SWAP UP
{
	long lIDPrevious = -1, lIDSelected = -1, lIDNext = -1;
	int iOrdinePrevious = -1, iOrdineSelected = -1, iOrdineNext = -1;

	int iNewIndexPosition = GetOrdineFromSelectedListSezione(
		&lIDPrevious, &lIDSelected, &lIDNext,
		&iOrdinePrevious, &iOrdineSelected, &iOrdineNext,
		-1 // means one posicion back
		);

	if (lIDPrevious > 0)
	{
		CSezioniSet().SetOrdine(lIDPrevious, iOrdineSelected);
		CSezioniSet().SetOrdine(lIDSelected, iOrdinePrevious);
		OnBnClickedBtnUndo();
		m_ctrlListSezione.SetItemState(-1, 0, LVIS_SELECTED);
		m_ctrlListSezione.SetItemState(iNewIndexPosition, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CGenomicaSezioniDlg::OnBnClickedBtnGiu() // SWAP DOWN
{
	long lIDPrevious = -1, lIDSelected = -1, lIDNext = -1;
	int iOrdinePrevious = -1, iOrdineSelected = -1, iOrdineNext = -1;

	int iNewIndexPosition = GetOrdineFromSelectedListSezione(
		&lIDPrevious, &lIDSelected, &lIDNext,
		&iOrdinePrevious, &iOrdineSelected, &iOrdineNext,
		1 // means one posicion forward
		);

	if (lIDNext > 0)
	{
		CSezioniSet().SetOrdine(lIDNext, iOrdineSelected);
		CSezioniSet().SetOrdine(lIDSelected, iOrdineNext);

		OnBnClickedBtnUndo();

		m_ctrlListSezione.SetItemState(-1, 0, LVIS_SELECTED);
		m_ctrlListSezione.SetItemState(iNewIndexPosition, LVIS_SELECTED, LVIS_SELECTED);
	}
}

int CGenomicaSezioniDlg::GetOrdineFromSelectedListSezione(
	long* p_lIDPrevious, long* p_lIDSelected, long* p_lIDNext,
	int* p_iOrdinePrevious, int* p_iOrdineSelected, int* p_iOrdineNext,
	int p_iMovement)
{
	*p_lIDPrevious = -1;
	*p_lIDSelected = -1;
	*p_lIDNext = -1;
	*p_iOrdinePrevious = -1;
	*p_iOrdineSelected = -1;
	*p_iOrdineNext = -1;

	int iIndexSelected = -1;
	long lIDSelected = -1;
	int iMaxPos = m_ctrlListSezione.GetItemCount();

	POSITION pos = m_ctrlListSezione.GetFirstSelectedItemPosition();
	if (pos != NULL)

	{
		iIndexSelected = m_ctrlListSezione.GetNextSelectedItem(pos);

		if (iIndexSelected - 1 >= 0)
		{
			lIDSelected = (long)m_ctrlListSezione.GetItemData(iIndexSelected - 1);
			*p_lIDPrevious = lIDSelected;
			*p_iOrdinePrevious = CSezioniSet().GetOrdine(lIDSelected);
		}

		lIDSelected = (long)m_ctrlListSezione.GetItemData(iIndexSelected);
		*p_lIDSelected = lIDSelected;
		*p_iOrdineSelected = CSezioniSet().GetOrdine(lIDSelected);

		if (iIndexSelected + 1 < iMaxPos)
		{

			lIDSelected = (long)m_ctrlListSezione.GetItemData(iIndexSelected + 1);
			*p_lIDNext = lIDSelected;
			*p_iOrdineNext = CSezioniSet().GetOrdine(lIDSelected);
		}
	}

	iIndexSelected += p_iMovement;

	if (iIndexSelected > iMaxPos - 1)
		iIndexSelected = iMaxPos - 1;

	if (iIndexSelected < 0)
		iIndexSelected = 0;

	return iIndexSelected; // return new SelectedIndexPosition
}

void CGenomicaSezioniDlg::OnLvnItemchangedListTipiReferto(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListTipiReferto.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int index = m_ctrlListTipiReferto.GetNextSelectedItem(pos);
		if ((long)m_ctrlListTipiReferto.GetItemData(index) > 0 && m_lIdTipoRefertoSelected != (long)m_ctrlListTipiReferto.GetItemData(index))
		{
			m_lIdTipoRefertoSelected = (long)m_ctrlListTipiReferto.GetItemData(index);
			m_lIdSezioniSelected = -1;
		}

		CString strNewColumnName = theApp.GetMessageString(IDS_GENOMICA_SEZIONE_ORDINE_1); // "ordine delle sezioni";

		int i = m_ctrlListTipiReferto.GetSelectionMark();
		// Check if selection is found
		if (i != -1)
		{
			// Get sub item of first row at the second column
			CString strSubItem = m_ctrlListTipiReferto.GetItemText(index, 0);

			strNewColumnName.Format(theApp.GetMessageString(IDS_GENOMICA_SEZIONE_ORDINE_2), (LPCTSTR)strSubItem);	//"%s: ordine delle sezioni"
		}
		m_ctrlListSezione.DeleteColumn(0);
		m_ctrlListSezione.SetExtendedStyle(m_ctrlListTipiReferto.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		m_ctrlListSezione.InsertColumn(0, strNewColumnName, LVCFMT_LEFT, 0);

		RiempiListaSezioni();

		GetDlgItem(IDC_BTN_NEW)->EnableWindow(m_lIdTipoRefertoSelected > 0);
	}
}

void CGenomicaSezioniDlg::OnLvnItemchangedListSezione(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lIdSezioniSelected = -1;
	POSITION pos = m_ctrlListSezione.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		m_lIdSezioniSelected = (long)m_ctrlListSezione.GetItemData(m_ctrlListSezione.GetNextSelectedItem(pos));
	}
	CaricaDati();
}

void CGenomicaSezioniDlg::OnBnClickedBtnRtfNewTable()
{
	m_ctrlTextControl2.RtfInsertNewTable(this);
}

void CGenomicaSezioniDlg::OnBnClickedBtnRtfMakeUpper()
{
	m_ctrlTextControl2.RtfSelectedTextMakeUpper();
}

void CGenomicaSezioniDlg::OnBnClickedBtnRtfMakeNormal()
{
	m_ctrlTextControl2.RtfSelectedTextMakeNormal();
}

void CGenomicaSezioniDlg::OnBnClickedBtnRtfMakeLower()
{
	m_ctrlTextControl2.RtfSelectedTextMakeLower();
}

void CGenomicaSezioniDlg::OnBnClickedBtnRtfFont() //Julio - BUG 4392 Edicao de texto
{
	m_ctrlTextControl.RtfSetFontProperties();
}