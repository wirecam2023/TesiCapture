#include "stdafx.h"
#include "Endox.h"
#include "FrasiPostEsameDlg.h"

#include "FrasiNewSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NONE 0
#define SEL_CAT 1
#define SEL_FRA 2
#define NEW_CAT 3
#define NEW_FRA 4
#define EDT_CAT 5
#define EDT_FRA 6

IMPLEMENT_DYNAMIC(CFrasiPostEsameDlg, CDialog)

CFrasiPostEsameDlg::CFrasiPostEsameDlg(CWnd* pParent)
	: CDialog(CFrasiPostEsameDlg::IDD, pParent)
{
	m_nRadioPrePost = 0;

	m_nState = NONE;
	htiPrevSel = NULL;
}

CFrasiPostEsameDlg::~CFrasiPostEsameDlg()
{
}

BEGIN_MESSAGE_MAP(CFrasiPostEsameDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_NEWCAT, OnBnClickedBtnNewCat)
	ON_BN_CLICKED(IDC_BTN_NEWFRA, OnBnClickedBtnNewFra)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)
	ON_BN_CLICKED(IDC_RADIO_01, OnBnClickedRadio01)
	ON_BN_CLICKED(IDC_RADIO_02, OnBnClickedRadio02)

	ON_STN_CLICKED(IDC_STATIC_03, OnStnClickedStatic03)
	ON_STN_CLICKED(IDC_STATIC_04, OnStnClickedStatic04)

	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnTvnSelchangedTree)
END_MESSAGE_MAP()

void CFrasiPostEsameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TREE, m_ctrlTree);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);

	DDX_Control(pDX, IDC_BTN_NEWCAT, m_ctrlBtnNewCat);
	DDX_Control(pDX, IDC_BTN_NEWFRA, m_ctrlBtnNewFra);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlBtnSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlBtnUndo);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Radio(pDX, IDC_RADIO_01, m_nRadioPrePost);
}

void CFrasiPostEsameDlg::OnCancel()
{
}

BOOL CFrasiPostEsameDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CFrasiPostEsameDlg::IDD, "FrasiPostEsameDlg");

	RiempiListaFrasi();

	return bReturn;
}

void CFrasiPostEsameDlg::OnOK()
{
	if (m_ctrlBtnOK.IsWindowEnabled())
		CDialog::OnOK();
}

void CFrasiPostEsameDlg::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	GetDlgItem(IDC_EDIT_TITOLO)->SetWindowText("");
	GetDlgItem(IDC_EDIT_FRASE)->SetWindowText("");

	if (pNMTreeView != NULL)
	{
		if ((long)pNMTreeView->itemNew.lParam > 0)
		{
			CString strTemp;
			strTemp.Format("ID=%li", (long)pNMTreeView->itemNew.lParam);

			CFrasiNewSet setFrasi;
			setFrasi.SetOpenFilter(strTemp);
			setFrasi.SetSortRecord("ID");
			if (setFrasi.OpenRecordset("CFrasiPostEsameDlg::OnTvnSelchangedTree"))
			{
				if (!setFrasi.IsEOF())
				{
					GetDlgItem(IDC_EDIT_TITOLO)->SetWindowText(setFrasi.m_sTitolo);
					GetDlgItem(IDC_EDIT_FRASE)->SetWindowText(setFrasi.m_sDescrizione);
				}

				setFrasi.CloseRecordset("CFrasiPostEsameDlg::OnTvnSelchangedTree");
			}
		}

		if (m_ctrlTree.GetParentItem(pNMTreeView->itemNew.hItem) == NULL)
			SetState(SEL_CAT);
		else
			SetState(SEL_FRA);
	}

	*pResult = 0;
}

void CFrasiPostEsameDlg::RiempiListaFrasi()
{
	m_ctrlTree.DeleteAllItems();
	SetState(NONE);

	HTREEITEM hFirst = NULL;

	CString strTemp;
	strTemp.Format("PrePost=%d AND Padre=0", m_nRadioPrePost);

	CFrasiNewSet setPadre;
	setPadre.SetBaseFilter(strTemp);
	setPadre.SetSortRecord("ID");
	if (setPadre.OpenRecordset("CFrasiPostEsameDlg::RiempiListaFrasi"))
	{
		while(!setPadre.IsEOF())
		{
			HTREEITEM hTemp = m_ctrlTree.InsertItem(TVIF_TEXT | TVIF_PARAM, setPadre.m_sTitolo, 0, 0, 0, 0, (LPARAM)setPadre.m_lID, TVI_ROOT, TVI_LAST);

			if (hFirst == NULL)
				hFirst = hTemp;

			RiempiListaFigli(hTemp, setPadre.m_lID);
			m_ctrlTree.Expand(hTemp, TVE_EXPAND);

			setPadre.MoveNext();
		}

		setPadre.CloseRecordset("CFrasiPostEsameDlg::RiempiListaFrasi");
	}

	if (hFirst != NULL)
		m_ctrlTree.EnsureVisible(hFirst);
}

void CFrasiPostEsameDlg::RiempiListaFigli(HTREEITEM hPadre, long lPadre)
{
	CString strTemp;
	strTemp.Format("Padre=%li", lPadre);

	CFrasiNewSet setFiglio;
	setFiglio.SetBaseFilter(strTemp);
	setFiglio.SetSortRecord("ID");
	if (setFiglio.OpenRecordset("CFrasiPostEsameDlg::RiempiListaFigli"))
	{
		while(!setFiglio.IsEOF())
		{
			m_ctrlTree.InsertItem(TVIF_TEXT | TVIF_PARAM, setFiglio.m_sTitolo, 0, 0, 0, 0, (LPARAM)setFiglio.m_lID, hPadre, TVI_LAST);

			setFiglio.MoveNext();
		}
		setFiglio.CloseRecordset("CFrasiPostEsameDlg::RiempiListaFigli");
	}
}

BOOL CFrasiPostEsameDlg::SaveEdt(long lID, const CString &sTitolo, const CString &sDescrizione)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	CFrasiNewSet setFrasi;
	setFrasi.SetOpenFilter(strFilter);

	if (setFrasi.OpenRecordset("CFrasiPostEsameDlg::SaveEdt"))
	{
		if (!setFrasi.IsEOF())
		{
			if (setFrasi.EditRecordset("CFrasiPostEsameDlg::SaveEdt"))
			{
				setFrasi.m_sTitolo = sTitolo;
				setFrasi.m_sDescrizione = sDescrizione;

				bReturn = setFrasi.UpdateRecordset("CFrasiPostEsameDlg::SaveEdt");
			}
		}

		setFrasi.CloseRecordset("CFrasiPostEsameDlg::SaveEdt");
	}

	return bReturn;
}

BOOL CFrasiPostEsameDlg::SaveNew(long lPadre, const CString &sTitolo, const CString &sDescrizione)
{
	BOOL bReturn = FALSE;

	CFrasiNewSet setFrasi;

	if (setFrasi.OpenRecordset("CFrasiPostEsameDlg::SaveNew"))
	{
		if (setFrasi.AddNewRecordset("CFrasiPostEsameDlg::SaveNew"))
		{
			setFrasi.m_lPrePost = m_nRadioPrePost;
			setFrasi.m_lPadre = lPadre;
			setFrasi.m_sTitolo = sTitolo;
			setFrasi.m_sDescrizione = sDescrizione;

			bReturn = setFrasi.UpdateRecordset("CFrasiPostEsameDlg::SaveNew");
		}

		setFrasi.CloseRecordset("CFrasiPostEsameDlg::SaveNew");
	}

	return bReturn;
}

void CFrasiPostEsameDlg::SetState(int nState)
{
	m_nState = nState;
	switch(nState)
	{
		case NONE: // selezionato niente //
		{
			// visible //
			GetDlgItem(IDC_STATIC_01)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_TITOLO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_02)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_FRASE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_BTN_NEWCAT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_NEWFRA)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_EDT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_DEL)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_UNDO)->ShowWindow(SW_HIDE);

			// enable //
			GetDlgItem(IDC_RADIO_01)->EnableWindow(TRUE);
			GetDlgItem(IDC_RADIO_02)->EnableWindow(TRUE);
			m_ctrlTree.EnableWindow(TRUE);

			SendDlgItemMessage(IDC_EDIT_TITOLO, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_FRASE, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);

			GetDlgItem(IDC_BTN_NEWCAT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_NEWFRA)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_UNDO)->EnableWindow(FALSE);
			GetDlgItem(IDOK)->EnableWindow(TRUE);

			break;
		}
		case SEL_CAT: // selezionata una categoria //
		{
			// visible //
			GetDlgItem(IDC_STATIC_01)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_TITOLO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_02)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_FRASE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_BTN_NEWCAT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_NEWFRA)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_EDT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_DEL)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_UNDO)->ShowWindow(SW_HIDE);

			// enable //
			GetDlgItem(IDC_RADIO_01)->EnableWindow(TRUE);
			GetDlgItem(IDC_RADIO_02)->EnableWindow(TRUE);
			m_ctrlTree.EnableWindow(TRUE);

			SendDlgItemMessage(IDC_EDIT_TITOLO, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_FRASE, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);

			GetDlgItem(IDC_BTN_NEWCAT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_NEWFRA)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_UNDO)->EnableWindow(FALSE);
			GetDlgItem(IDOK)->EnableWindow(TRUE);

			break;
		}
		case SEL_FRA: // selezionata una frase //
		{
			// visible //
			GetDlgItem(IDC_STATIC_01)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_TITOLO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_02)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_FRASE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_BTN_NEWCAT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_NEWFRA)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_EDT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_DEL)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_UNDO)->ShowWindow(SW_HIDE);

			// enable //
			GetDlgItem(IDC_RADIO_01)->EnableWindow(TRUE);
			GetDlgItem(IDC_RADIO_02)->EnableWindow(TRUE);
			m_ctrlTree.EnableWindow(TRUE);

			SendDlgItemMessage(IDC_EDIT_TITOLO, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_FRASE, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);

			GetDlgItem(IDC_BTN_NEWCAT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_NEWFRA)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_UNDO)->EnableWindow(FALSE);
			GetDlgItem(IDOK)->EnableWindow(TRUE);

			break;
		}
		case NEW_CAT: // inserendo una nuova categoria //
		case EDT_CAT: // modificando una categoria //
		{
			// visible //
			GetDlgItem(IDC_STATIC_01)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_TITOLO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_02)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_FRASE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_BTN_NEWCAT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEWFRA)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_EDT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_DEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_UNDO)->ShowWindow(SW_SHOW);

			// enable //
			GetDlgItem(IDC_RADIO_01)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_02)->EnableWindow(FALSE);
			m_ctrlTree.EnableWindow(FALSE);

			SendDlgItemMessage(IDC_EDIT_TITOLO, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_FRASE, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);

			GetDlgItem(IDC_BTN_NEWCAT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_NEWFRA)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_UNDO)->EnableWindow(TRUE);
			GetDlgItem(IDOK)->EnableWindow(FALSE);

			// others //
			GetDlgItem(IDC_EDIT_TITOLO)->SetFocus();

			break;
		}
		case NEW_FRA: // inserendo una nuova frase //
		case EDT_FRA: // modificando una frase //
		{
			// visible //
			GetDlgItem(IDC_STATIC_01)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_TITOLO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_02)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_FRASE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_BTN_NEWCAT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEWFRA)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_EDT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_DEL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_UNDO)->ShowWindow(SW_SHOW);

			// enable //
			GetDlgItem(IDC_RADIO_01)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_02)->EnableWindow(FALSE);
			m_ctrlTree.EnableWindow(FALSE);

			SendDlgItemMessage(IDC_EDIT_TITOLO, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_FRASE, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			GetDlgItem(IDC_BTN_NEWCAT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_NEWFRA)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_UNDO)->EnableWindow(TRUE);
			GetDlgItem(IDOK)->EnableWindow(FALSE);

			// others //
			GetDlgItem(IDC_EDIT_TITOLO)->SetFocus();

			break;
		}
	}
}

void CFrasiPostEsameDlg::OnBnClickedBtnNewCat()
{
	htiPrevSel = m_ctrlTree.GetSelectedItem();

	m_ctrlTree.SelectItem(NULL);

	SetDlgItemText(IDC_EDIT_TITOLO, "");
	SetDlgItemText(IDC_EDIT_FRASE, "");

	SetState(NEW_CAT);
}

void CFrasiPostEsameDlg::OnBnClickedBtnNewFra()
{
	htiPrevSel = m_ctrlTree.GetSelectedItem();

	if (m_ctrlTree.GetParentItem(htiPrevSel) == NULL)
		m_ctrlTree.SelectItem(htiPrevSel);
	else
		m_ctrlTree.SelectItem(m_ctrlTree.GetParentItem(htiPrevSel));

	SetDlgItemText(IDC_EDIT_TITOLO, "");
	SetDlgItemText(IDC_EDIT_FRASE, "");

	SetState(NEW_FRA);
}

void CFrasiPostEsameDlg::OnBnClickedBtnEdt()
{
	htiPrevSel = m_ctrlTree.GetSelectedItem();

	if (m_ctrlTree.GetParentItem(htiPrevSel) == NULL)
		SetState(EDT_CAT);
	else
		SetState(EDT_FRA);
}

void CFrasiPostEsameDlg::OnBnClickedBtnDel()
{
	HTREEITEM htiSel = m_ctrlTree.GetSelectedItem();

	if (htiSel != NULL)
	{
		if (m_ctrlTree.GetParentItem(htiSel) == NULL)
		{
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DELETE_CATEGORIA), MB_YESNO) == IDNO)
				return;
		}
		else
		{
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DELETE_FRASE), MB_YESNO) == IDNO)
				return;
		}

		long lID = m_ctrlTree.GetItemData(htiSel);

		CString strFilter;
		strFilter.Format("ID=%li", lID);

		CFrasiNewSet setFrasi;
		setFrasi.SetOpenFilter(strFilter);
		if (setFrasi.OpenRecordset("CFrasiPostEsameDlg::OnBnClickedBtnDel"))
		{
			if (!setFrasi.IsEOF())
			{
				if (setFrasi.DeleteRecordset("CFrasiPostEsameDlg::OnBnClickedBtnDel"))
				{
					setFrasi.CloseRecordset("CFrasiPostEsameDlg::OnBnClickedBtnDel");

					strFilter.Format("Padre=%li", lID);
					setFrasi.SetOpenFilter(strFilter);
					if (setFrasi.OpenRecordset("CFrasiPostEsameDlg::OnBnClickedBtnDel"))
					{
						while (!setFrasi.IsEOF())
						{
							setFrasi.DeleteRecordset("CFrasiPostEsameDlg::OnBnClickedBtnDel");
							setFrasi.MoveNext();
						}

						setFrasi.CloseRecordset("CFrasiPostEsameDlg::OnBnClickedBtnDel");
					}
				}
			}
			
			if (setFrasi.IsOpen())
				setFrasi.CloseRecordset("CFrasiPostEsameDlg::OnBnClickedBtnDel");
		}

		RiempiListaFrasi();
	}
}

void CFrasiPostEsameDlg::OnBnClickedBtnSave()
{
	CString strTitolo;
	CString strFrase;

	GetDlgItemText(IDC_EDIT_TITOLO, strTitolo);
	GetDlgItemText(IDC_EDIT_FRASE, strFrase);

	strTitolo.Trim();
	strFrase.Trim();

	if (strTitolo.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_EMPTY_TITOLO));
		return;
	}

	BOOL bOk = FALSE;
	switch(m_nState)
	{
		case NEW_CAT: // inserendo una nuova categoria //
		{
			bOk = SaveNew(0, strTitolo, "");
			break;
		}
		case NEW_FRA: // inserendo una nuova frase //
		{
			if (strFrase.IsEmpty())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_EMPTY_FRASE));
				return;
			}

			bOk = SaveNew(m_ctrlTree.GetItemData(m_ctrlTree.GetSelectedItem()), strTitolo, strFrase);
			break;
		}
		case EDT_CAT: // modificando una categoria //
		{
			bOk = SaveEdt(m_ctrlTree.GetItemData(htiPrevSel), strTitolo, "");
			break;
		}
		case EDT_FRA: // modificando una frase //
		{
			if (strFrase.IsEmpty())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_EMPTY_FRASE));
				return;
			}

			bOk = SaveEdt(m_ctrlTree.GetItemData(htiPrevSel), strTitolo, strFrase);
			break;
		}
	}

	if (!bOk)
	{
		OnBnClickedBtnUndo();
		return;
	}

	RiempiListaFrasi();
}

void CFrasiPostEsameDlg::OnBnClickedBtnUndo()
{
	m_ctrlTree.SelectItem(NULL);
	m_ctrlTree.SelectItem(htiPrevSel);

	if (m_ctrlTree.GetParentItem(htiPrevSel) == NULL)
		SetState(SEL_CAT);
	else
		SetState(SEL_FRA);
}

void CFrasiPostEsameDlg::OnBnClickedRadio01()
{
	int nTemp = m_nRadioPrePost;
	UpdateData(TRUE);
	if (nTemp != m_nRadioPrePost)
		RiempiListaFrasi();
}

void CFrasiPostEsameDlg::OnBnClickedRadio02()
{
	int nTemp = m_nRadioPrePost;
	UpdateData(TRUE);
	if (nTemp != m_nRadioPrePost)
		RiempiListaFrasi();
}

void CFrasiPostEsameDlg::OnStnClickedStatic03()
{
	UpdateData(TRUE);
	m_nRadioPrePost = 0;
	UpdateData(FALSE);

	// aggiorno interfaccia //
	// OnClickedRadio1();
}

void CFrasiPostEsameDlg::OnStnClickedStatic04()
{
	UpdateData(TRUE);
	m_nRadioPrePost = 1;
	UpdateData(FALSE);

	// aggiorno interfaccia //
	// OnClickedRadio1();
}