#include "stdafx.h"
#include "Endox.h"
#include "CheckListElModDlg.h"

#include "CheckListItemSet.h"
#include "Common.h"
#include "CheckListItemRegoleSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCheckListElModDlg, CDialog)

// costruttore per l'inserimento di un nuovo elemento //
CCheckListElModDlg::CCheckListElModDlg(CWnd* pParent, long lIDCheckList, long lIDPadre, const CTreeCtrl* pTreeCtrl)
	: CDialog(CCheckListElModDlg::IDD, pParent),
	  m_wndCampoSingolo(FALSE)
{
	ASSERT(pTreeCtrl != NULL);

	m_pCheckListTreeCtrl = pTreeCtrl;
	m_lIDCheckList = lIDCheckList;
	m_lIDPadre = lIDPadre;
	m_lIDEl = 0;
}

// costruttore per la modifica di un elemento esistente //
CCheckListElModDlg::CCheckListElModDlg(CWnd* pParent, long lIDEl, const CTreeCtrl* pTreeCtrl)
	: CDialog(CCheckListElModDlg::IDD, pParent),
	  m_wndCampoSingolo(FALSE)
{
	ASSERT(pTreeCtrl != NULL);

	m_pCheckListTreeCtrl = pTreeCtrl;
	m_lIDCheckList = 0;
	m_lIDPadre = 0;
	m_lIDEl = lIDEl;
}

CCheckListElModDlg::~CCheckListElModDlg()
{
}

BEGIN_MESSAGE_MAP(CCheckListElModDlg, CDialog)

	ON_COMMAND(IDC_RTF_TABLE, OnBnClickedBtnRtfNewTable)
	ON_COMMAND(IDC_RTF_MAKEUPPER, OnBnClickedBtnRtfMakeUpper)
	ON_COMMAND(IDC_RTF_MAKENORMAL, OnBnClickedBtnRtfMakeNormal)
	ON_COMMAND(IDC_RTF_MAKELOWER, OnBnClickedBtnRtfMakeLower)

END_MESSAGE_MAP()

void CCheckListElModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	// --- //

	DDX_Control(pDX, IDC_CHECK_1, m_ctrlCheck1);
	DDX_Control(pDX, IDC_CHECK_2, m_ctrlCheck2);

	DDX_Control(pDX, IDC_BUTTONBAR, m_ctrlButtonBar);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_EDIT_TITOLO, m_ctrlEditTitolo);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_17, m_ctrlStatic17);
	DDX_Control(pDX, IDC_STATIC_18, m_ctrlStatic18);
	DDX_Control(pDX, IDC_STATIC_19, m_ctrlStatic19);
	DDX_Control(pDX, IDC_STATIC_20, m_ctrlStatic20);

	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //

	UINT nTreeID[] = { IDC_TREE1, IDC_TREE2, IDC_TREE3, IDC_TREE4 };
	for (int i = 0; i < _countof(m_ctrlTree); i++)
		DDX_Control(pDX, nTreeID[i], m_ctrlTree[i]);
}

BOOL CCheckListElModDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();
	m_ctrlToolbar.Create(IDC_BUTTONBAR_PLACE, this);
	m_ctrlToolbar.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	m_ctrlStatic01.SetFont(&theApp.m_fontBold);
	m_ctrlStatic02.SetFont(&theApp.m_fontBold);
	m_ctrlStatic03.SetFont(&theApp.m_fontBold);
	m_ctrlStatic04.SetFont(&theApp.m_fontBold);
	m_ctrlStatic05.SetFont(&theApp.m_fontBold);
	m_ctrlStatic17.SetFont(&theApp.m_fontBold);
	m_ctrlStatic18.SetFont(&theApp.m_fontBold);
	m_ctrlStatic19.SetFont(&theApp.m_fontBold);
	m_ctrlStatic20.SetFont(&theApp.m_fontBold);

	// tolgo i flag WS_CLIPCHILDREN e WS_CLIPSIBLINGS dallo stile della barra //
	::SetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE, (GetWindowLong(m_ctrlButtonBar.GetSafeHwnd(), GWL_STYLE) & ~WS_CLIPCHILDREN) & ~WS_CLIPSIBLINGS);

	m_ctrlTextControl.SetButtonBarHandle((long)m_ctrlButtonBar.GetSafeHwnd());
	m_ctrlTextControl.SetFontName(g_sReportFaceName);
	m_ctrlTextControl.SetFontSize(g_nReportSize);
	m_ctrlTextControl.SetFontBold(g_bReportBold);
	m_ctrlTextControl.SetFontItalic(g_bReportItalic);
	m_ctrlTextControl.SetFontUnderline(g_bReportUnderline);

	m_wndCampoSingolo.CreateForm(IDC_PLACE_1, this, "");
	m_wndCampoSingolo.SetQuery("CodiciClassificazioneDiagnost");

	for (int i = 0; i < _countof(m_ctrlTree); i++)
		FillTree(i);

	if (m_lIDEl > 0)
		CaricaDati();

    theApp.LocalizeDialog(this, CCheckListElModDlg::IDD, "CheckListElModDlg");
	if (m_lIDEl == 0)
		SetWindowText(theApp.GetMessageString(IDS_CHECKLISTEL_MOD_TITLE1));
	else
		SetWindowText(theApp.GetMessageString(IDS_CHECKLISTEL_MOD_TITLE2));

	return bReturn;
}

void CCheckListElModDlg::OnOK()
{
	if (SalvaDati())
		CDialog::OnOK();
}

void CCheckListElModDlg::CaricaDati()
{
	if (m_lIDEl > 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", m_lIDEl);

		CCheckListItemSet setItem;
		setItem.SetOpenFilter(strFilter);
		if (setItem.OpenRecordset("CCheckListElModDlg::CaricaDati"))
		{
			if (!setItem.IsEOF())
			{
				m_ctrlEditTitolo.SetWindowText(setItem.m_sTitolo);

				m_ctrlTextControl.ResetContents();
				m_ctrlTextControl.SetRTFSelText(setItem.m_sTestoRTF);

				m_ctrlCheck1.SetCheck(setItem.m_bItemAlmenoUno ? BST_CHECKED : BST_UNCHECKED);
				m_ctrlCheck2.SetCheck(setItem.m_bItemPiuDiUno ? BST_CHECKED : BST_UNCHECKED);

				if (!setItem.IsFieldNull(&setItem.m_lClassificazioneDiagnosi) && setItem.m_lClassificazioneDiagnosi > 0)
					m_wndCampoSingolo.SetItemSelectedID(setItem.m_lClassificazioneDiagnosi);
			}

			setItem.CloseRecordset("CCheckListElModDlg::CaricaDati");
		}

		///

		strFilter.Format("IDCHECKLISTITEM = %li", m_lIDEl);

		CCheckListItemRegoleSet setRegole;
		setRegole.SetOpenFilter(strFilter);
		if (setRegole.OpenRecordset("CCheckListElModDlg::CaricaDati"))
		{
			CList<long>** ppListSelected = new CList<long>*[_countof(m_ctrlTree)];
			for (int i = 0; i < _countof(m_ctrlTree); i++)
				ppListSelected[i] = new CList<long>();

			while (!setRegole.IsEOF())
			{
				if (!setRegole.IsFieldNull(&setRegole.m_lTipoRegola) && setRegole.m_lTipoRegola >= 0 && setRegole.m_lTipoRegola < _countof(m_ctrlTree))
					ppListSelected[setRegole.m_lTipoRegola]->AddTail(setRegole.m_lIDCheckListItemBind);
				setRegole.MoveNext();
			}

			for (int i = 0; i < _countof(m_ctrlTree); i++)
				SetCheckTreeItem(i, ppListSelected[i]);

			setRegole.CloseRecordset("CCheckListElModDlg::CaricaDati");

			for (int i = 0; i < _countof(m_ctrlTree); i++)
				delete ppListSelected[i];
			delete ppListSelected;
		}
	}
}

BOOL CCheckListElModDlg::SalvaDati()
{
	BOOL bReturn = FALSE;

	// cerco e conto le chiocciole //
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);
	CString strTXT = m_ctrlTextControl.GetSelText();

	BOOL bError = FALSE;

	long lVariables = 0;
	int iTemp = strTXT.Find('@');
	int iTempCombo = strTXT.Find("@COMBO");
	int iTempPrev = iTemp; 
	while(iTemp >= 0)
	{
		if (lVariables % 2 != 0)
		{
			// sono su una chiocciola che dovrebbe chiudere una variabile -> verifico lunghezza descrizione //
			if (iTempCombo == -1)
				if (iTemp - iTempPrev > 51)
					bError = TRUE;
		}

		iTempPrev = iTemp;

		lVariables++;
		iTemp = strTXT.Find('@', iTemp + 1);
	}

	// controllo che le chiocciole siano in numero pari altrimenti segnalo l'errore //
	if (lVariables % 2 != 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CHECKLISTITEM_ERROR1));
		return FALSE;
	}

	// le chiocciole sono pari, ma ci sono variabili con una descrizione più lunga di 50 caratteri //
	if (bError)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CHECKLISTITEM_ERROR3));
		return FALSE;
	}
	//

	if (m_lIDEl == 0)
	{
		// inserimento di un nuovo elemento //

		CCheckListItemSet setItem;
		if (setItem.OpenRecordset("CCheckListElModDlg::SalvaDati"))
		{
			if (setItem.AddNewRecordset("CCheckListElModDlg::SalvaDati"))
			{
				setItem.m_lIDCheckList = m_lIDCheckList;
				setItem.m_lIDPadre = m_lIDPadre;

				m_ctrlEditTitolo.GetWindowText(setItem.m_sTitolo);

				setItem.m_sTestoRTF = m_ctrlTextControl.GetRTFSelText();
				setItem.m_sTestoTXT = strTXT;

				setItem.m_lTestoNumeroVariabili = lVariables / 2;

				setItem.m_bItemAlmenoUno = (m_ctrlCheck1.GetCheck() == BST_CHECKED);
				setItem.m_bItemPiuDiUno = (m_ctrlCheck2.GetCheck() == BST_CHECKED);

				setItem.m_lClassificazioneDiagnosi = m_wndCampoSingolo.GetItemSelectedID();

				if (setItem.UpdateRecordset("CCheckListElModDlg::SalvaDati"))
				{
					m_lIDEl = setItem.GetLastAdd();
					bReturn = TRUE;
				}
			}

			setItem.CloseRecordset("CCheckListElModDlg::SalvaDati");
		}
	}
	else
	{
		// modifica di un elemento esistente //

		CString strFilter;
		strFilter.Format("ID=%li", m_lIDEl);

		CCheckListItemSet setItem;
		setItem.SetOpenFilter(strFilter);
		if (setItem.OpenRecordset("CCheckListElModDlg::SalvaDati"))
		{
			if (!setItem.IsEOF())
			{
				if (setItem.EditRecordset("CCheckListElModDlg::SalvaDati"))
				{
					m_ctrlEditTitolo.GetWindowText(setItem.m_sTitolo);

					setItem.m_sTestoRTF = m_ctrlTextControl.GetRTFSelText();
					setItem.m_sTestoTXT = strTXT;

					setItem.m_lTestoNumeroVariabili = lVariables / 2;

					setItem.m_bItemAlmenoUno = (m_ctrlCheck1.GetCheck() == BST_CHECKED);
					setItem.m_bItemPiuDiUno = (m_ctrlCheck2.GetCheck() == BST_CHECKED);

					setItem.m_lClassificazioneDiagnosi = m_wndCampoSingolo.GetItemSelectedID();

					bReturn = setItem.UpdateRecordset("CCheckListElModDlg::SalvaDati");
				}
			}

			setItem.CloseRecordset("CCheckListElModDlg::SalvaDati");
		}
	}

	if (bReturn && m_lIDEl > 0)
	{
		for (int i = 0; i < _countof(m_ctrlTree); i++)
		{
			CList<long> listSelected;
			GetCheckTreeItem(i, &listSelected);

			if (POSITION pos = listSelected.Find(m_lIDEl))
				listSelected.RemoveAt(pos);

			CString strFilter;
			strFilter.Format("IDCheckListItem = %li AND TipoRegola = %li", m_lIDEl, i);

			CCheckListItemRegoleSet setRegole;
			setRegole.SetOpenFilter(strFilter);
			if (setRegole.OpenRecordset("CCheckListElModDlg::SalvaDati"))
			{
				while (!setRegole.IsEOF())
				{
					if (POSITION pos = listSelected.Find(setRegole.m_lIDCheckListItemBind))
						listSelected.RemoveAt(pos);
					else
						setRegole.DeleteRecordset("CCheckListElModDlg::SalvaDati");

					setRegole.MoveNext();
				}

				for (POSITION pos = listSelected.GetHeadPosition(); pos;)
				{
					if (setRegole.AddNewRecordset("CCheckListElModDlg::SalvaDati"))
					{
						setRegole.m_lIDCheckListItem = m_lIDEl;
						setRegole.m_lIDCheckListItemBind = listSelected.GetNext(pos);
						setRegole.m_lTipoRegola = i;
						setRegole.UpdateRecordset("CCheckListElModDlg::SalvaDati");
					}
				}

				setRegole.CloseRecordset("CCheckListElModDlg::SalvaDati");
			}
		}
	}

	return bReturn;
}

void CCheckListElModDlg::OnBnClickedBtnRtfNewTable()
{
	m_ctrlTextControl.RtfInsertNewTable(this);
}

void CCheckListElModDlg::OnBnClickedBtnRtfMakeUpper()
{
	m_ctrlTextControl.RtfSelectedTextMakeUpper();
}

void CCheckListElModDlg::OnBnClickedBtnRtfMakeNormal()
{
	m_ctrlTextControl.RtfSelectedTextMakeNormal();
}

void CCheckListElModDlg::OnBnClickedBtnRtfMakeLower()
{
	m_ctrlTextControl.RtfSelectedTextMakeLower();
}

/*
void CCheckListElModDlg::OnLvnItemchangedListInterniDiagnosi(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListInterniDiagnosi.GetFirstSelectedItemPosition();
	m_ctrlBtnDelInterniDiagnosi.EnableWindow(pos != NULL);
}

void CCheckListElModDlg::OnBtnNewInterniDiagnosi()
{
	// ButtonNew(&m_ctrlListInterniDiagnosi, "CodiciInterniDiagnosi", &m_listInterniDiagnosiAdded, &m_listInterniDiagnosiRemoved);
}

void CCheckListElModDlg::OnBtnDelInterniDiagnosi()
{
	// ButtonDel(&m_ctrlListInterniDiagnosi, &m_listInterniDiagnosiAdded, &m_listInterniDiagnosiRemoved);
}
*/

void CCheckListElModDlg::FillTree(int iIndex, HTREEITEM hItemParentSource, HTREEITEM hItemParent)
{
	if (hItemParentSource == NULL)
	{
		m_ctrlTree[iIndex].ModifyStyle(TVS_CHECKBOXES, 0);
		m_ctrlTree[iIndex].ModifyStyle(0, TVS_CHECKBOXES);
	}

	HTREEITEM hItem = (hItemParentSource == NULL) ? m_pCheckListTreeCtrl->GetRootItem() : hItemParentSource;

	while (hItem)
	{
		HTREEITEM hNewItem = m_ctrlTree[iIndex].InsertItem(m_pCheckListTreeCtrl->GetItemText(hItem), hItemParent);
		m_ctrlTree[iIndex].SetItemData(hNewItem, m_pCheckListTreeCtrl->GetItemData(hItem));

		if (HTREEITEM hItemChild = m_pCheckListTreeCtrl->GetChildItem(hItem))
			FillTree(iIndex, hItemChild, hNewItem);

		m_ctrlTree[iIndex].Expand(hNewItem, TVE_EXPAND);

		hItem = m_pCheckListTreeCtrl->GetNextSiblingItem(hItem);
	}

	if (hItemParentSource == NULL && m_ctrlTree[iIndex].GetCount())
		m_ctrlTree[iIndex].EnsureVisible(m_ctrlTree[iIndex].GetRootItem());
}

void CCheckListElModDlg::SetCheckTreeItem(int iIndex, const CList<long>* pItemSelected, HTREEITEM hItemParent)
{
	HTREEITEM hItem = (hItemParent == NULL) ? m_ctrlTree[iIndex].GetRootItem() : hItemParent;

	while (hItem)
	{
		if (pItemSelected->Find(m_ctrlTree[iIndex].GetItemData(hItem)))
			m_ctrlTree[iIndex].SetCheck(hItem, TRUE);

		if (HTREEITEM hItemChild = m_ctrlTree[iIndex].GetChildItem(hItem))
			SetCheckTreeItem(iIndex, pItemSelected, hItemChild);

		hItem = m_ctrlTree[iIndex].GetNextSiblingItem(hItem);
	}
}

void CCheckListElModDlg::GetCheckTreeItem(int iIndex, CList<long>* pItemSelected, HTREEITEM hItemParent)
{
	if (hItemParent == NULL)
		pItemSelected->RemoveAll();

	HTREEITEM hItem = (hItemParent == NULL) ? m_ctrlTree[iIndex].GetRootItem() : hItemParent;

	while (hItem)
	{
		if (m_ctrlTree[iIndex].GetCheck(hItem))
			pItemSelected->AddTail(m_ctrlTree[iIndex].GetItemData(hItem));

		if (HTREEITEM hItemChild = m_ctrlTree[iIndex].GetChildItem(hItem))
			GetCheckTreeItem(iIndex, pItemSelected, hItemChild);

		hItem = m_ctrlTree[iIndex].GetNextSiblingItem(hItem);
	}
}