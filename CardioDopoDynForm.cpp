#include "stdafx.h"
#include "Endox.h"
#include "CardioDopoDynForm.h"

#include "EsamiSet.h"
#include "EsamiView.h"
#include "ProtocolloCardioSet.h"
#include "ProtocolloColonneSet.h"
#include "ProtocolloEsamiSet.h"
#include "ProtocolloValoriDefaultSet.h"

#define RGB_MODIFICABILE RGB(255, 255, 191)
#define RGB_SOLALETTURA RGB(223, 223, 223)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCardioDopoDynForm::CCardioDopoDynForm(CWnd* pParent, CEsamiView* pEsamiView)
: CEndoxDynForm(CCardioDopoDynForm::IDD, pParent, pEsamiView),
m_ctrlList(FALSE, TRUE, TRUE)
{
	m_bReadOnly = TRUE;
	m_lIDProtocollo = 0;
	m_lNumColonne = 0;
	m_pArrayStructColonne = NULL;
}

CCardioDopoDynForm::~CCardioDopoDynForm(void)
{
	if (m_pArrayStructColonne != NULL)
	{
		delete m_pArrayStructColonne;
		m_pArrayStructColonne = NULL;
	}
}

BEGIN_MESSAGE_MAP(CCardioDopoDynForm, CEndoxDynForm)

	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

END_MESSAGE_MAP()

void CCardioDopoDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_cardio_dopo] == NULL)
	{
		pEsamiView->m_pDynForm[sub_cardio_dopo] = new CCardioDopoDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_cardio_dopo] != NULL)
		{
			pEsamiView->m_pDynForm[sub_cardio_dopo]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_cardio_dopo]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_cardio_dopo]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_cardio_dopo]->CreateChildForm(CCardioDopoDynForm::IDD, pParent, rectFrame);
		}
	}
}

void CCardioDopoDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	//

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_STATIC_TITLE, m_ctrlStaticTitle);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);
}

HBRUSH CCardioDopoDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_TITLE:
		case IDC_BTN_DEL:
		case IDC_LIST:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hReturn;
}

BOOL CCardioDopoDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_TITLE, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_BTN_DEL, CSize(100, 100), CSize(100, 100));

	m_ctrlStaticTitle.SetFont(&theApp.m_fontBold);
	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);

	//

	m_lIDProtocollo = CProtocolloCardioSet().GetIDFromFase(PROTOCOLLO_FASE_DOPO);
	if (m_lIDProtocollo > 0)
		ListControlPrepara();

	//

	theApp.LocalizeDialog(this, CCardioDopoDynForm::IDD, "CardioDopoDynForm");
	return bReturn;
}

LRESULT CCardioDopoDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CCardioDopoDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	m_ctrlList.SetRedraw(FALSE);

	ListControlDeleteAll();
	if (CProtocolloEsamiSet().HasRows(m_pEsamiView->m_pEsamiSet->m_lContatore, m_lIDProtocollo))
	{
		// carico i dati già inseriti //
		ListControlCaricaDatiEsame();
	}
	else
	{
		// carico i valori di default //
		ListControlCaricaDefault();
	}

	m_ctrlList.SetRedraw(TRUE);
	return UpdateData(FALSE);
}

LRESULT CCardioDopoDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	m_bReadOnly = (BOOL)wParam;
	
	m_ctrlList.SetReadOnly(m_bReadOnly);
	
	BOOL bEnable = FALSE;
	if (!m_bReadOnly)
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nCurSel = m_ctrlList.GetNextSelectedItem(pos);

			if (m_ctrlList.GetItemData(nCurSel) > 0)
				bEnable = TRUE;
		}
	}
	
	m_ctrlBtnDel.EnableWindow(bEnable);
	return 1;
}

LRESULT CCardioDopoDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	ListControlDeleteAll();

	return 1;
}

LRESULT CCardioDopoDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	for (int iRiga = 1; iRiga < m_ctrlList.GetItemCount(); iRiga++)
		for (int iColonna = 0; iColonna < m_lNumColonne; iColonna++)
			CProtocolloEsamiSet().AddEdtRow(m_pEsamiView->m_pEsamiSet->m_lContatore, m_lIDProtocollo, m_pArrayStructColonne[iColonna].lID, iRiga, m_ctrlList.GetItemText(iRiga, iColonna));

	CProtocolloEsamiSet().DelRows(m_pEsamiView->m_pEsamiSet->m_lContatore, m_lIDProtocollo, m_ctrlList.GetItemCount());

	return UpdateData(TRUE);
}

LRESULT CCardioDopoDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	return 1;
}

long CCardioDopoDynForm::GetContenuto()
{
	return sub_cardio_dopo;
}

BOOL CCardioDopoDynForm::CampoObbligatorioValido()
{
	return FALSE;
}

void CCardioDopoDynForm::ListControlPrepara()
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li", m_lIDProtocollo);

	CProtocolloColonneSet setPC;
	setPC.SetOpenFilter(sFilter);
	setPC.SetSortRecord("ORDINE");
	if (setPC.OpenRecordset("CCardioPrimaDynForm::OnInitDialog"))
	{
		while (!setPC.IsEOF())
		{
			m_lNumColonne++;
			setPC.MoveNext();
		}

		if (m_lNumColonne > 0)
		{
			setPC.MoveFirst();

			m_pArrayStructColonne = new STRUCT_COLONNE[m_lNumColonne];

			int nIndex = 0;
			while (!setPC.IsEOF())
			{
				m_ctrlList.InsertColumn(nIndex, setPC.m_sDescrizione, LVCFMT_LEFT, 0);

				m_pArrayStructColonne[nIndex].lID = setPC.m_lID;
				strcpy_s(m_pArrayStructColonne[nIndex].szDescrizione, setPC.m_sDescrizione);
				m_pArrayStructColonne[nIndex].bValoreModificabile = setPC.m_bValoriModificabili;

				nIndex++;
				setPC.MoveNext();
			}
			m_ctrlList.InsertColumn(nIndex, "", LVCFMT_LEFT, 0);

			for (int i = 0; i < m_lNumColonne; i++)
				m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
		}

		setPC.CloseRecordset("CCardioPrimaDynForm::OnInitDialog");
	}
}

void CCardioDopoDynForm::ListControlCaricaDatiEsame()
{
	CString sFilter;
	sFilter.Format("IDESAME=%li AND IDPROTOCOLLO=%li", m_pEsamiView->m_pEsamiSet->m_lContatore, m_lIDProtocollo);

	CProtocolloEsamiSet setPE;
	setPE.SetOpenFilter(sFilter);
	setPE.SetSortRecord("ORDINE, IDCOLONNA");
	if (setPE.OpenRecordset("CCardioPrimaDynForm::ListControlCaricaDatiEsame"))
	{
		int nIndex = 0;
		long lLastOrder = -1;

		while (!setPE.IsEOF())
		{
			// se serve aggiungo una riga //

			if (setPE.m_lOrdine != lLastOrder)
			{
				nIndex++;

				m_ctrlList.InsertItem(nIndex, "");
				m_ctrlList.SetItemData(nIndex, setPE.m_lOrdine);

				for (int i = 0; i < m_lNumColonne; i++)
					if (m_pArrayStructColonne[i].bValoreModificabile)
						m_ctrlList.SetSubItemEdit(nIndex, i, FALSE, 250);

				lLastOrder = setPE.m_lOrdine;
			}

			//

			for (int i = 0; i < m_lNumColonne; i++)
			{
				if (m_pArrayStructColonne[i].lID == setPE.m_lIDColonna)
				{
					m_ctrlList.SetItemText(nIndex, i, setPE.m_sValore);
					break;
				}
			}

			//

			setPE.MoveNext();
		}

		setPE.CloseRecordset("CCardioPrimaDynForm::ListControlCaricaDatiEsame");
	}

	//

	for (int i = 0; i < m_lNumColonne; i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE);

	//

	for (int iSubItem = 0; iSubItem < m_lNumColonne; iSubItem++)
	{
		if (!m_pArrayStructColonne[iSubItem].bValoreModificabile)
		{
			for (int iItem = 1; iItem < m_ctrlList.GetItemCount(); iItem++)
				m_ctrlList.SetSubItemBkColor(iItem, iSubItem, RGB_SOLALETTURA);
		}
		else
		{
			for (int iItem = 1; iItem < m_ctrlList.GetItemCount(); iItem++)
				m_ctrlList.SetSubItemBkColor(iItem, iSubItem, RGB_MODIFICABILE);
		}
	}
}

void CCardioDopoDynForm::ListControlCaricaDefault()
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li", m_lIDProtocollo);

	CProtocolloValoriDefaultSet setPVD;
	setPVD.SetOpenFilter(sFilter);
	setPVD.SetSortRecord("ORDINE, IDCOLONNA");
	if (setPVD.OpenRecordset("CCardioPrimaDynForm::ListControlCaricaDefault"))
	{
		int nIndex = 0;
		long lLastOrder = -1;

		while (!setPVD.IsEOF())
		{
			// se serve aggiungo una riga //

			if (setPVD.m_lOrdine != lLastOrder)
			{
				nIndex++;

				m_ctrlList.InsertItem(nIndex, "");
				m_ctrlList.SetItemData(nIndex, setPVD.m_lOrdine);

				for (int i = 0; i < m_lNumColonne; i++)
					if (m_pArrayStructColonne[i].bValoreModificabile)
						m_ctrlList.SetSubItemEdit(nIndex, i, FALSE, 250);

				lLastOrder = setPVD.m_lOrdine;
			}

			//

			for (int i = 0; i < m_lNumColonne; i++)
			{
				if (m_pArrayStructColonne[i].lID == setPVD.m_lIDColonna)
				{
					m_ctrlList.SetItemText(nIndex, i, setPVD.m_sValore);
					break;
				}
			}

			//

			setPVD.MoveNext();
		}

		setPVD.CloseRecordset("CCardioPrimaDynForm::ListControlCaricaDefault");
	}

	//

	for (int i = 0; i < m_lNumColonne; i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE);

	//

	for (int iSubItem = 0; iSubItem < m_lNumColonne; iSubItem++)
	{
		if (!m_pArrayStructColonne[iSubItem].bValoreModificabile)
		{
			for (int iItem = 1; iItem < m_ctrlList.GetItemCount(); iItem++)
				m_ctrlList.SetSubItemBkColor(iItem, iSubItem, RGB_SOLALETTURA);
		}
		else
		{
			for (int iItem = 1; iItem < m_ctrlList.GetItemCount(); iItem++)
				m_ctrlList.SetSubItemBkColor(iItem, iSubItem, RGB_MODIFICABILE);
		}
	}
}

void CCardioDopoDynForm::ListControlDeleteAll()
{
	m_ctrlList.DeleteAllItems();

	m_ctrlList.InsertItem(0, "");
	m_ctrlList.SetItemData(0, 0);

	for (int i = 0; i < m_lNumColonne; i++)
	{
		m_ctrlList.SetItemText(0, i, m_pArrayStructColonne[i].szDescrizione);
		m_ctrlList.SetSubItemBkColor(0, i, RGB_SOLALETTURA);

		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}

short CCardioDopoDynForm::GetColNumber()
{
	return (short)m_lNumColonne;
}

short CCardioDopoDynForm::GetRowNumber()
{
	return (short)m_ctrlList.GetItemCount();
}

CString CCardioDopoDynForm::GetTableCellText(short shCol, short shRow)
{
	CString sReturn = "";

	if ((shCol < GetColNumber()) && (shRow < GetRowNumber()))
		sReturn = m_ctrlList.GetItemText(shRow, shCol);

	return sReturn;
}

CString CCardioDopoDynForm::GetTitle()
{
	CString sReturn = "";

	m_ctrlStaticTitle.GetWindowTextA(sReturn);
	sReturn.Trim();
	if (!sReturn.IsEmpty())
		sReturn = "\r\n" + sReturn + "\r\n";

	return sReturn;
}
void CCardioDopoDynForm::SetTitle(CString sTitle)
{
	m_ctrlStaticTitle.SetWindowTextA(sTitle);
}

void CCardioDopoDynForm::OnBnClickedBtnDel()
{
	if (theApp.AfxMessageBoxEndo(IDS_ELIMINARIGAETUTTESUCCESSIVE, MB_YESNO) == IDYES)
	{
		POSITION posFirst = m_ctrlList.GetFirstSelectedItemPosition();
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nCurSel = m_ctrlList.GetNextSelectedItem(pos);
			while (m_ctrlList.GetItemCount() > nCurSel)
				m_ctrlList.DeleteItem(m_ctrlList.GetItemCount() - 1);
		}
	}
}
void CCardioDopoDynForm::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	BOOL bEnable = FALSE;
	if (!m_bReadOnly)
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nCurSel = m_ctrlList.GetNextSelectedItem(pos);

			if (m_ctrlList.GetItemData(nCurSel) > 0)
				bEnable = TRUE;
		}
		m_ctrlBtnDel.EnableWindow(bEnable);
	}
	*pResult = 0;
}