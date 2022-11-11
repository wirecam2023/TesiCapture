#include "stdafx.h"
#include "Endox.h"
#include "OrganiSediDlg.h"
#include "EsamiView.h"

#include "EditStringDlg.h"
#include "SedeSet.h"
#include "MstOrganoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COrganiSediDlg, CDialog)

COrganiSediDlg::COrganiSediDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL selectionMode)
	: CDialog(COrganiSediDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_strRicerca = "";
	m_strRicercaView = "";

	m_bSelectionMode = selectionMode;
}

COrganiSediDlg::~COrganiSediDlg()
{
}

BEGIN_MESSAGE_MAP(COrganiSediDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_LBN_SELCHANGE(IDC_LIST_ORGANI, OnLbnSelchangeListOrgani)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_SEDI, OnTvnSelchangedTreeSedi)

	ON_BN_CLICKED(IDC_BTN_ORGANI_NUOVO, OnBnClickedBtnOrganiNuovo)
	ON_BN_CLICKED(IDC_BTN_ORGANI_MODIFICA, OnBnClickedBtnOrganiModifica)
	ON_BN_CLICKED(IDC_BTN_ORGANI_ELIMINA, OnBnClickedBtnOrganiElimina)
	ON_BN_CLICKED(IDC_BTN_SEDI_NUOVO, OnBnClickedBtnSediNuovo)
	ON_BN_CLICKED(IDC_BTN_SEDI_NUOVOSUB, OnBnClickedBtnSediNuovosub)
	ON_BN_CLICKED(IDC_BTN_SEDI_MODIFICA, OnBnClickedBtnSediModifica)
	ON_BN_CLICKED(IDC_BTN_SEDI_ELIMINA, OnBnClickedBtnSediElimina)
END_MESSAGE_MAP()

void COrganiSediDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_ORGANI, m_ctrlListOrgani);
	DDX_Control(pDX, IDC_TREE_SEDI, m_ctrlTreeSedi);

	DDX_Control(pDX, IDC_STATIC_ORGANI, m_ctrlStaticOrgani);
	DDX_Control(pDX, IDC_STATIC_SEDI,   m_ctrlStaticSedi);
	DDX_Control(pDX, IDC_STATIC_CODICEINTEGRAZIONE,   m_ctrlStaticCodiceIntegrazione);

	DDX_Control(pDX, IDCANCEL,                m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_BTN_ORGANI_NUOVO,    m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_ORGANI_MODIFICA, m_ctrlButtonMod);
	DDX_Control(pDX, IDC_BTN_ORGANI_ELIMINA,  m_ctrlButtonDel);
	DDX_Control(pDX, IDC_BTN_SEDI_NUOVO,      m_ctrlButtonNew2);
	DDX_Control(pDX, IDC_BTN_SEDI_NUOVOSUB,   m_ctrlButtonNew3);
	DDX_Control(pDX, IDC_BTN_SEDI_MODIFICA,   m_ctrlButtonMod2);
	DDX_Control(pDX, IDC_BTN_SEDI_ELIMINA,    m_ctrlButtonDel2);

	DDX_Control(pDX, IDC_EDIT_CODICEINTEGRAZIONE, m_ctrlEdtCodiceIntegrazione);
	DDX_Text(pDX, IDC_EDIT_CODICEINTEGRAZIONE, m_sCodiceIntegrazione);

}

HBRUSH COrganiSediDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_ORGANI:
		case IDC_LIST_ORGANI:
			pDC->SetTextColor(theApp.m_color[0]);
			break;

		case IDC_STATIC_SEDI:
			pDC->SetTextColor(theApp.m_color[1]);
			break;
	}

	return hBrush;
}

BOOL COrganiSediDlg::OnInitDialog()
{   
	BOOL bReturn = CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_ORGANI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_SEDI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);

	m_ctrlTreeSedi.SetTextColor(theApp.m_color[1]);

	RiempiListOrgani();
	theApp.LocalizeDialog(this, COrganiSediDlg::IDD, "OrganiSediDlg");

	if (m_bSelectionMode)
	{
		GetDlgItem(IDC_BTN_ORGANI_NUOVO)->EnableWindow(FALSE);
	}

	return bReturn;
}

void COrganiSediDlg::RiempiTreeSedi()
{
	HTREEITEM hPadre;
	HTREEITEM hFirst = NULL;

	CString strTemp;
	strTemp.Format("Organo=%d and Padre=0", (int)m_ctrlListOrgani.GetItemData(m_ctrlListOrgani.GetCurSel()));

	m_ctrlTreeSedi.DeleteAllItems();

	CMstSediSet setTemp1;
	setTemp1.SetSortRecord("Descrizione");

	CMstSediSet setTemp2;
	setTemp2.SetSortRecord("Descrizione");

	setTemp1.SetBaseFilter(strTemp);
	if (setTemp1.OpenRecordset("COrganiSediDlg::RiempiTreeSedi") == FALSE)
		return;

	while(setTemp1.IsEOF() == FALSE)
	{
		hPadre = m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp1.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp1.m_lContatore, TVI_ROOT, TVI_LAST);
		if (hFirst == NULL)
			hFirst = hPadre;

		strTemp.Format("Padre=%li", setTemp1.m_lContatore);
		setTemp2.SetOpenFilter(strTemp);
		if (setTemp2.OpenRecordset("COrganiSediDlg::RiempiTreeSedi") == TRUE)
		{
			while(setTemp2.IsEOF() == FALSE)
			{
				m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp2.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp2.m_lContatore, hPadre, TVI_LAST);

				setTemp2.MoveNext();
			}

			setTemp2.CloseRecordset("COrganiSediDlg::RiempiTreeSedi");
		}

		m_ctrlTreeSedi.Expand(hPadre, TVE_EXPAND);

		setTemp1.MoveNext();
	}

	setTemp1.CloseRecordset("COrganiSediDlg::RiempiTreeSedi");

	if (hFirst != NULL)
		m_ctrlTreeSedi.EnsureVisible(hFirst);

	if (!m_bSelectionMode)
	{
		GetDlgItem(IDC_BTN_SEDI_NUOVOSUB)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SEDI_MODIFICA)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SEDI_ELIMINA)->EnableWindow(FALSE);
	}
}

void COrganiSediDlg::RiempiListOrgani()
{
	int iIndex = 0;
	CMstOrganoSet setTemp;
	
	m_ctrlListOrgani.ResetContent();

	setTemp.SetSortRecord("Organo");
	if (setTemp.OpenRecordset("COrganiSediDlg::RiempiListaOrgani") == FALSE)
		return;

	while(setTemp.IsEOF() == FALSE)
	{
		m_ctrlListOrgani.InsertString(iIndex, setTemp.m_sOrgano);
		m_ctrlListOrgani.SetItemData(iIndex, setTemp.m_lContatore);

		iIndex++;
		setTemp.MoveNext();
	}

	setTemp.CloseRecordset("COrganiSediDlg::RiempiListaOrgani");
}

void COrganiSediDlg::OnLbnSelchangeListOrgani()
{
	static int iPrevSel = LB_ERR;
	int iCurrSel = m_ctrlListOrgani.GetCurSel();

	if (iCurrSel == iPrevSel)
		return;

	TRACE1("-> OnLbnSelchangeListOrgani(%d)\n", iCurrSel);

	iPrevSel = iCurrSel;

	if (!m_bSelectionMode)
	{
		GetDlgItem(IDC_BTN_ORGANI_MODIFICA)->EnableWindow(iCurrSel >= 0);
		GetDlgItem(IDC_BTN_ORGANI_ELIMINA)->EnableWindow(iCurrSel >= 0);
		GetDlgItem(IDC_BTN_SEDI_NUOVO)->EnableWindow(iCurrSel >= 0);
		GetDlgItem(IDC_BTN_SEDI_NUOVOSUB)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SEDI_MODIFICA)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SEDI_ELIMINA)->EnableWindow(FALSE);
	}

	if (iCurrSel >= 0)
	{
		RiempiTreeSedi();
		m_ctrlListOrgani.GetText(iCurrSel, m_strRicercaView);
	}
	else
	{
		m_ctrlTreeSedi.DeleteAllItems();
		m_strRicercaView = "";
	}

	m_sCodiceIntegrazione = "";
	UpdateData(FALSE);
}

void COrganiSediDlg::OnTvnSelchangedTreeSedi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hTemp = m_ctrlTreeSedi.GetSelectedItem();

	if (!m_bSelectionMode)
	{
		GetDlgItem(IDC_BTN_SEDI_NUOVOSUB)->EnableWindow(hTemp != NULL);
		GetDlgItem(IDC_BTN_SEDI_MODIFICA)->EnableWindow(hTemp != NULL);
		GetDlgItem(IDC_BTN_SEDI_ELIMINA)->EnableWindow(hTemp != NULL);
	}

	m_sCodiceIntegrazione = CMstSediSet().GetCodiceIntegrazione((int)m_ctrlTreeSedi.GetItemData(hTemp));

	CString strRicercaView;
	strRicercaView.Append(m_ctrlTreeSedi.GetItemText(hTemp));
	while((hTemp = m_ctrlTreeSedi.GetParentItem(hTemp)) != NULL)
	{
		CString strTemp;
		strTemp = m_ctrlTreeSedi.GetItemText(hTemp);
		strTemp.Append(" ");
		strTemp.Append(strRicercaView);
		strRicercaView = strTemp;
	}

	m_strRicercaView.Append(" ");
	m_strRicercaView.Append(strRicercaView);

	UpdateData(FALSE);

	*pResult = 0;
}

void COrganiSediDlg::OnBnClickedBtnOrganiNuovo()
{
	CEditStringDlg dlg(this, IDS_ORGANISEDI_TITLE_1, "");

	if (dlg.DoModal() == IDOK)
	{
		CMstOrganoSet setTemp;

		if (setTemp.OpenRecordset("COrganiSediDlg::OnBnClickedBtnOrganiNuovo") == TRUE)
		{
			if (setTemp.AddNewRecordset("COrganiSediDlg::OnBnClickedBtnOrganiNuovo") == TRUE)
			{
				setTemp.m_sOrgano = dlg.GetValue();

				setTemp.UpdateRecordset("COrganiSediDlg::OnBnClickedBtnOrganiNuovo");
			}

			setTemp.CloseRecordset("COrganiSediDlg::OnBnClickedBtnOrganiNuovo");
		}

		RiempiListOrgani();
	}
}

void COrganiSediDlg::OnBnClickedBtnOrganiModifica()
{
	CString strTemp;
	m_ctrlListOrgani.GetText(m_ctrlListOrgani.GetCurSel(), strTemp);

	CEditStringDlg dlg(this, IDS_ORGANISEDI_TITLE_2, strTemp);

	if (dlg.DoModal() == IDOK)
	{
		CMstOrganoSet setTemp;

		strTemp.Format("Contatore=%d", (int)m_ctrlListOrgani.GetItemData(m_ctrlListOrgani.GetCurSel()));
		setTemp.SetOpenFilter(strTemp);

		if (setTemp.OpenRecordset("COrganiSediDlg::OnBnClickedBtnOrganiModifica") == TRUE)
		{
			if (setTemp.IsEOF() == FALSE)
			{
				if (setTemp.EditRecordset("COrganiSediDlg::OnBnClickedBtnOrganiModifica") == TRUE)
				{
					setTemp.m_sOrgano = dlg.GetValue();

					setTemp.UpdateRecordset("COrganiSediDlg::OnBnClickedBtnOrganiModifica");
				}
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ORGANISEDIDLG_ERR_1));
			}

			setTemp.CloseRecordset("COrganiSediDlg::OnBnClickedBtnOrganiModifica");
		}

		RiempiListOrgani();
	}
}

void COrganiSediDlg::OnBnClickedBtnOrganiElimina()
{
	CString strTemp, strTmp;
	m_ctrlListOrgani.GetText(m_ctrlListOrgani.GetCurSel(), strTemp);

	strTmp.Format(theApp.GetMessageString(IDS_ORGANISEDIDLG_CONFIRM_DEL),
		          strTemp);
	if (theApp.AfxMessageBoxEndo(strTmp, MB_YESNO) == IDNO)
		return;

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ORGANISEDIDLG_CONFIRM_DEL_2), MB_YESNO | MB_ICONSTOP) == IDYES)
		return;

	CMstOrganoSet setTemp;

	strTemp.Format("Contatore = %d", (int)m_ctrlListOrgani.GetItemData(m_ctrlListOrgani.GetCurSel()));
	setTemp.SetOpenFilter(strTemp);

	if (setTemp.OpenRecordset("COrganiSediDlg::OnBnClickedBtnOrganiElimina") == TRUE)
	{
		if (setTemp.IsEOF() == FALSE)
		{
			if (setTemp.DeleteRecordset("COrganiSediDlg::OnBnClickedBtnOrganiElimina") == FALSE)
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ORGANISEDIDLG_CANNOT_DELETE));
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ORGANISEDIDLG_CANNOT_DELETE_2));
		}

		setTemp.CloseRecordset("COrganiSediDlg::OnBnClickedBtnOrganiElimina");
	}

	RiempiListOrgani();
}

void COrganiSediDlg::OnBnClickedBtnSediNuovo()
{
	CEditStringDlg dlg(this, IDS_ORGANISEDI_TITLE_3, "");

	if (dlg.DoModal() == IDOK)
	{
		CMstSediSet setTemp;

		if (setTemp.OpenRecordset("COrganiSediDlg::OnBnClickedBtnSediNuovo") == TRUE)
		{
			if (setTemp.AddNewRecordset("COrganiSediDlg::OnBnClickedBtnSediNuovo") == TRUE)
			{
				setTemp.m_lOrgano = (long)m_ctrlListOrgani.GetItemData(m_ctrlListOrgani.GetCurSel());
				setTemp.m_lPadre = 0;
				setTemp.m_sDescrizione = dlg.GetValue();

				setTemp.UpdateRecordset("COrganiSediDlg::OnBnClickedBtnSediNuovo");
			}

			setTemp.CloseRecordset("COrganiSediDlg::OnBnClickedBtnSediNuovo");
		}

		RiempiTreeSedi();
	}
}

void COrganiSediDlg::OnBnClickedBtnSediNuovosub()
{
	CEditStringDlg dlg(this, IDS_ORGANISEDI_TITLE_4, "");

	if (dlg.DoModal() == IDOK)
	{
		CMstSediSet setTemp;

		HTREEITEM hTemp	= m_ctrlTreeSedi.GetParentItem(m_ctrlTreeSedi.GetSelectedItem());
		if (hTemp == NULL)
			hTemp = m_ctrlTreeSedi.GetSelectedItem();

		if (setTemp.OpenRecordset("COrganiSediDlg::OnBnClickedBtnSediNuovosub") == TRUE)
		{
			if (setTemp.AddNewRecordset("COrganiSediDlg::OnBnClickedBtnSediNuovosub") == TRUE)
			{
				setTemp.m_lOrgano = (long)m_ctrlListOrgani.GetItemData(m_ctrlListOrgani.GetCurSel());
				setTemp.m_lPadre = (long)m_ctrlTreeSedi.GetItemData(hTemp);
				setTemp.m_sDescrizione = dlg.GetValue();

				setTemp.UpdateRecordset("COrganiSediDlg::OnBnClickedBtnSediNuovosub");
			}

			setTemp.CloseRecordset("COrganiSediDlg::OnBnClickedBtnSediNuovosub");
		}

		RiempiTreeSedi();
	}
}

void COrganiSediDlg::OnBnClickedBtnSediModifica()
{
	CString strTemp = m_ctrlTreeSedi.GetItemText(m_ctrlTreeSedi.GetSelectedItem());

	CEditStringDlg dlg(this, IDS_ORGANISEDI_TITLE_5, strTemp);

	if (dlg.DoModal() == IDOK)
	{
		CMstSediSet setTemp;

		strTemp.Format("Contatore=%d", (int)m_ctrlTreeSedi.GetItemData(m_ctrlTreeSedi.GetSelectedItem()));
		setTemp.SetOpenFilter(strTemp);

		if (setTemp.OpenRecordset("COrganiSediDlg::OnBnClickedBtnSediModifica") == TRUE)
		{
			if (setTemp.IsEOF() == FALSE)
			{
				if (setTemp.EditRecordset("COrganiSediDlg::OnBnClickedBtnSediModifica") == TRUE)
				{
					setTemp.m_sDescrizione = dlg.GetValue();

					setTemp.UpdateRecordset("COrganiSediDlg::OnBnClickedBtnSediModifica");
				}
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ORGANISEDIDLG_ERR_2));
			}

			setTemp.CloseRecordset("COrganiSediDlg::OnBnClickedBtnSediModifica");
		}

		RiempiTreeSedi();
	}
}

void COrganiSediDlg::OnBnClickedBtnSediElimina()
{
	HTREEITEM hTemp = m_ctrlTreeSedi.GetSelectedItem();
	CString strTemp = m_ctrlTreeSedi.GetItemText(hTemp);

	CString strMessage;
	strMessage.Format(theApp.GetMessageString(IDS_ORGANISEDIDLG_CONFIRM_DEL_3),
				      strTemp);
	if (theApp.AfxMessageBoxEndo(strMessage, MB_YESNO) == IDNO)
		return;

	if ((m_ctrlTreeSedi.ItemHasChildren(hTemp) == TRUE) && 
		(theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ORGANISEDIDLG_CONFIRM_DEL_4), MB_YESNO | MB_ICONSTOP) == IDYES))
		return;

	CMstSediSet setTemp;

	strTemp.Format("Contatore=%d", (int)m_ctrlTreeSedi.GetItemData(hTemp));
	setTemp.SetOpenFilter(strTemp);

	if (setTemp.OpenRecordset("COrganiSediDlg::OnBnClickedBtnSediElimina") == TRUE)
	{
		if (setTemp.IsEOF() == FALSE)
		{
			if (setTemp.DeleteRecordset("COrganiSediDlg::OnBnClickedBtnSediElimina") == FALSE)
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ORGANISEDIDLG_CANNOT_DELETE_3));
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ORGANISEDIDLG_ERR_3));
		}

		setTemp.CloseRecordset("COrganiSediDlg::OnBnClickedBtnSediElimina");
	}

	RiempiTreeSedi();
}