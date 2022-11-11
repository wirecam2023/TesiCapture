#include "stdafx.h"
#include "Endox.h"
#include "FrasiNewUseDlg.h"

#include "FrasiNewSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFrasiNewUseDlg, CDialog)

CFrasiNewUseDlg::CFrasiNewUseDlg(CWnd* pParent, CString sTitolo, long lPrePost, CString strValue)
	: CDialog(CFrasiNewUseDlg::IDD, pParent)
{
	m_sTitolo = sTitolo;
	m_lPrePost = lPrePost;
	m_strValue = strValue;
}

CFrasiNewUseDlg::~CFrasiNewUseDlg()
{
}

BEGIN_MESSAGE_MAP(CFrasiNewUseDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnTvnSelchangedTree)
	ON_BN_CLICKED(IDC_BTN_INSERISCI, OnBnClickedBtnInserisci)
END_MESSAGE_MAP()

void CFrasiNewUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TREE, m_ctrlTree);

	DDX_Control(pDX, IDC_EDIT_TEXT, m_ctrlText);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDC_BTN_INSERISCI, m_ctrlBtnInserisci);
	DDX_Control(pDX, IDOK, m_ctrlBtnOk);
}

BOOL CFrasiNewUseDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	m_ctrlText.SetWindowText(m_strValue);

	theApp.LocalizeDialog(this, CFrasiNewUseDlg::IDD, "FrasiNewUseDlg");

	SetWindowText(m_sTitolo);
	RiempiListaFrasi();

	return bReturn;
}

void CFrasiNewUseDlg::OnOK()
{
	m_ctrlText.GetWindowText(m_strValue);

	CDialog::OnOK();
}

void CFrasiNewUseDlg::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	GetDlgItem(IDC_EDIT_FRASE)->SetWindowText("");
	m_ctrlBtnInserisci.EnableWindow(FALSE);

	if (pNMTreeView != NULL)
	{
		if (m_ctrlTree.GetParentItem(pNMTreeView->itemNew.hItem) != NULL)
		{
			if ((long)pNMTreeView->itemNew.lParam > 0)
			{
				CString strTemp;
				strTemp.Format("ID=%li", (long)pNMTreeView->itemNew.lParam);

				CFrasiNewSet setFrasi;
				setFrasi.SetOpenFilter(strTemp);
				setFrasi.SetSortRecord("ID");
				if (setFrasi.OpenRecordset("CFrasiNewUseDlg::OnTvnSelchangedTree"))
				{
					if (!setFrasi.IsEOF())
					{
						setFrasi.m_sDescrizione.Trim();

						GetDlgItem(IDC_EDIT_FRASE)->SetWindowText(setFrasi.m_sDescrizione);
						m_ctrlBtnInserisci.EnableWindow(!setFrasi.m_sDescrizione.IsEmpty());
					}

					setFrasi.CloseRecordset("CFrasiNewUseDlg::OnTvnSelchangedTree");
				}
			}
		}
	}

	*pResult = 0;
}

CString CFrasiNewUseDlg::GetValue()
{
	return m_strValue;
}

void CFrasiNewUseDlg::RiempiListaFrasi()
{
	m_ctrlTree.DeleteAllItems();

	HTREEITEM hFirst = NULL;

	CString strTemp;
	strTemp.Format("PrePost=%li AND Padre=0", m_lPrePost);

	CFrasiNewSet setPadre;
	setPadre.SetBaseFilter(strTemp);
	setPadre.SetSortRecord("ID");
	if (setPadre.OpenRecordset("CFrasiNewUseDlg::RiempiListaFrasi"))
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

		setPadre.CloseRecordset("CFrasiNewUseDlg::RiempiListaFrasi");
	}

	if (hFirst != NULL)
		m_ctrlTree.EnsureVisible(hFirst);
}

void CFrasiNewUseDlg::RiempiListaFigli(HTREEITEM hPadre, long lPadre)
{
	CString strTemp;
	strTemp.Format("Padre=%li", lPadre);

	CFrasiNewSet setFiglio;
	setFiglio.SetBaseFilter(strTemp);
	setFiglio.SetSortRecord("ID");
	if (setFiglio.OpenRecordset("CFrasiNewUseDlg::RiempiListaFigli"))
	{
		while(!setFiglio.IsEOF())
		{
			m_ctrlTree.InsertItem(TVIF_TEXT | TVIF_PARAM, setFiglio.m_sTitolo, 0, 0, 0, 0, (LPARAM)setFiglio.m_lID, hPadre, TVI_LAST);

			setFiglio.MoveNext();
		}
		setFiglio.CloseRecordset("CFrasiNewUseDlg::RiempiListaFigli");
	}
}

void CFrasiNewUseDlg::OnBnClickedBtnInserisci()
{
	CString strFrase;
	GetDlgItemText(IDC_EDIT_FRASE, strFrase);

	m_ctrlText.ReplaceSel(strFrase, TRUE);
}
