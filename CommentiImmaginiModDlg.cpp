#include "stdafx.h"
#include "Endox.h"
#include "CommentiImmaginiModDlg.h"

#include "CommentiImmaginiSet.h"
#include "EditStringDlg.h"
#include "EsamiDoc.h"
#include "EsamiView.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCommentiImmaginiModDlg, CDialog)

CCommentiImmaginiModDlg::CCommentiImmaginiModDlg(CEsamiView* pParent)
	: CDialog(CCommentiImmaginiModDlg::IDD, pParent)
{
	m_lIDTipoEsame = 0;
	m_pEsamiView = pParent;
}

CCommentiImmaginiModDlg::~CCommentiImmaginiModDlg()
{
}

BEGIN_MESSAGE_MAP(CCommentiImmaginiModDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBnClickedBtnExit)

	ON_CBN_SELCHANGE(IDC_COMBO_TIPOESAME, OnCbnSelchangeComboTipoEsame)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_COMMENTI, OnLvnItemchangedListCommenti)

	ON_BN_CLICKED(IDC_CHK_ATTIVA, &CCommentiImmaginiModDlg::OnBnClickedChkAttiva)
	ON_BN_CLICKED(IDC_CHK_NOEDITABLE, &CCommentiImmaginiModDlg::OnBnClickedChkNoeditable)
END_MESSAGE_MAP()

void CCommentiImmaginiModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlBtnNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);
	DDX_Control(pDX, IDC_BTN_EXIT, m_ctrlBtnExit);
	DDX_Control(pDX, IDC_CHK_ATTIVA, m_ctrlChkAttiva);
	DDX_Control(pDX, IDC_CHK_NOEDITABLE, m_ctrlChkNoEdit);

	DDX_Control(pDX, IDC_COMBO_TIPOESAME, m_ctrlCmbTipoEsame);

	DDX_Control(pDX, IDC_LIST_COMMENTI, m_ctrlListCommenti);

	DDX_Control(pDX, IDC_STATIC_TIPOESAME, m_ctrlStaticTipoEsame);

	DDX_Check(pDX, IDC_CHK_ATTIVA, theApp.m_bAlbumImmaginiUsaListaCommenti);
	DDX_Check(pDX, IDC_CHK_NOEDITABLE, theApp.m_bAlbumImmaginiCommentoNonEditabile);

}

void CCommentiImmaginiModDlg::OnCancel()
{
}

BOOL CCommentiImmaginiModDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	m_ctrlListCommenti.SetExtendedStyle(m_ctrlListCommenti.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListCommenti.InsertColumn(0, theApp.GetMessageString(IDS_COMMENTI));
	m_ctrlListCommenti.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	//

	RiempiComboTipoEsame();

	//

	CheckFieldsToEnable();

	UpdateData(FALSE);

	theApp.LocalizeDialog(this, CCommentiImmaginiModDlg::IDD, "CommentiImmaginiModDlg");
	return TRUE;
}

void CCommentiImmaginiModDlg::OnOK()
{
}

void CCommentiImmaginiModDlg::OnBnClickedBtnNew()
{
	CEditStringDlg dlg(this, IDS_COMMENTOIMMAGINE_NEW, "");
	if (dlg.DoModal() == IDOK)
	{
		BeginWaitCursor();

		long lNewRowID = CCommentiImmaginiSet().AddRow(m_lIDTipoEsame, dlg.GetValue());
		if (lNewRowID > 0)
			RiempiListaCommenti(m_lIDTipoEsame, lNewRowID);

		EndWaitCursor();
	}
}

void CCommentiImmaginiModDlg::OnBnClickedBtnEdt()
{
	POSITION pos = m_ctrlListCommenti.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListCommenti.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			long lID = m_ctrlListCommenti.GetItemData(nCurSel);
			if (lID > 0)
			{
				CEditStringDlg dlg(this, IDS_COMMENTOIMMAGINE_EDT, m_ctrlListCommenti.GetItemText(nCurSel, 0));
				if (dlg.DoModal() == IDOK)
				{
					BeginWaitCursor();

					if(CCommentiImmaginiSet().EdtRow(lID, dlg.GetValue()))
						RiempiListaCommenti(m_lIDTipoEsame, lID);

					EndWaitCursor();
				}
			}
		}
	}
}

void CCommentiImmaginiModDlg::OnBnClickedBtnDel()
{
	POSITION pos = m_ctrlListCommenti.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlListCommenti.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			long lID = m_ctrlListCommenti.GetItemData(nCurSel);
			if (lID > 0)
			{
				if (theApp.AfxMessageBoxEndo(IDS_COMMENTOIMMAGINE_DEL, MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					BeginWaitCursor();

					if (CCommentiImmaginiSet().DelRow(lID))
						RiempiListaCommenti(m_lIDTipoEsame, 0);

					EndWaitCursor();
				}
			}
		}
	}
}

void CCommentiImmaginiModDlg::OnBnClickedBtnExit()
{
	m_pEsamiView->GetDocument()->SetBoolValue("Album immagini - Usa lista commenti", theApp.m_bAlbumImmaginiUsaListaCommenti);
	m_pEsamiView->GetDocument()->SetBoolValue("Album immagini - Commento non editabile", theApp.m_bAlbumImmaginiCommentoNonEditabile);

	CDialog::OnOK();
}

void CCommentiImmaginiModDlg::OnCbnSelchangeComboTipoEsame()
{
	m_lIDTipoEsame = 0;

	int nCurSel = m_ctrlCmbTipoEsame.GetCurSel();
	if (nCurSel >= 0)
		m_lIDTipoEsame = m_ctrlCmbTipoEsame.GetItemData(nCurSel);

	m_ctrlBtnNew.EnableWindow(m_lIDTipoEsame > 0);
	RiempiListaCommenti(m_lIDTipoEsame, 0);
}

void CCommentiImmaginiModDlg::OnLvnItemchangedListCommenti(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	POSITION pos = m_ctrlListCommenti.GetFirstSelectedItemPosition();
	m_ctrlBtnEdt.EnableWindow(pos != NULL);
	m_ctrlBtnDel.EnableWindow(pos != NULL);

	*pResult = 0;
}

void CCommentiImmaginiModDlg::RiempiComboTipoEsame()
{
	m_ctrlCmbTipoEsame.SetRedraw(FALSE);
	m_ctrlCmbTipoEsame.ResetContent();

	m_ctrlCmbTipoEsame.InsertString(0, "");
	m_ctrlCmbTipoEsame.SetItemData(0, 0);

	CTipoEsameSet setTemp;
	setTemp.SetSortRecord("Descrizione, Contatore");
	if (setTemp.OpenRecordset("CCommentiImmaginiModDlg::RiempiComboTipoEsame"))
	{
		int nIndex = 1;
		while (!setTemp.IsEOF())
		{
			m_ctrlCmbTipoEsame.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlCmbTipoEsame.SetItemData(nIndex, setTemp.m_lContatore);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CCommentiImmaginiModDlg::RiempiComboTipoEsame");
	}

	m_ctrlCmbTipoEsame.SetCurSel(0);

	m_ctrlCmbTipoEsame.SetRedraw(TRUE);
}

void CCommentiImmaginiModDlg::RiempiListaCommenti(long lIDTipoEsame, long lIDCommentoDaSelezionare)
{
	int nIndexToSel = -1;

	CString sFilter;
	sFilter.Format("IDTipoEsame=%li", lIDTipoEsame);

	m_ctrlListCommenti.SetRedraw(FALSE);
	m_ctrlListCommenti.DeleteAllItems();

	CCommentiImmaginiSet setTemp;
	setTemp.SetOpenFilter(sFilter);
	setTemp.SetSortRecord("Commento");
	if (setTemp.OpenRecordset("CCommentiImmaginiModDlg::RiempiListaCommenti"))
	{
		int nIndex = 0;
		while (!setTemp.IsEOF())
		{
			m_ctrlListCommenti.InsertItem(nIndex, setTemp.m_sCommento);
			m_ctrlListCommenti.SetItemData(nIndex, setTemp.m_lID);

			if (setTemp.m_lID == lIDCommentoDaSelezionare)
				nIndexToSel = nIndex;

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CCommentiImmaginiModDlg::RiempiListaCommenti");
	}

	if (nIndexToSel >= 0)
		m_ctrlListCommenti.SetItemState(nIndexToSel, LVIS_SELECTED, LVIS_SELECTED);

	m_ctrlListCommenti.SetRedraw(TRUE);
}


void CCommentiImmaginiModDlg::CheckFieldsToEnable()
{
	//disabilito o abilito tutti i controlli
	CWnd* pwndChild = GetWindow(GW_CHILD);
	while (pwndChild)
	{
		if ((pwndChild->GetDlgCtrlID() != IDOK) && (pwndChild->GetDlgCtrlID() != IDCANCEL) && (pwndChild->GetDlgCtrlID() != IDC_BTN_EXIT))
			pwndChild->EnableWindow(theApp.m_bAlbumImmaginiUsaListaCommenti);

		pwndChild = pwndChild->GetNextWindow();
	}

	//disabilito o abilito i controlli interessati, in modo opposto a quello appena fatto
	m_ctrlChkNoEdit.EnableWindow(theApp.m_bAlbumImmaginiUsaListaCommenti);

	//check sempre abilitata se no mi blocco
	m_ctrlChkAttiva.EnableWindow(TRUE);
}

void CCommentiImmaginiModDlg::OnBnClickedChkAttiva()
{
	if (m_ctrlChkAttiva.GetCheck() == BST_CHECKED)
		theApp.m_bAlbumImmaginiUsaListaCommenti = TRUE;
	else
		theApp.m_bAlbumImmaginiUsaListaCommenti = FALSE;

	CheckFieldsToEnable();

	UpdateData(TRUE);
}


void CCommentiImmaginiModDlg::OnBnClickedChkNoeditable()
{
	if (m_ctrlChkAttiva.GetCheck() == BST_CHECKED)
		theApp.m_bAlbumImmaginiCommentoNonEditabile = TRUE;
	else
		theApp.m_bAlbumImmaginiCommentoNonEditabile = FALSE;

	UpdateData(TRUE);
}
