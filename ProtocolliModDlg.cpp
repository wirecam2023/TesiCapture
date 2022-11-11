#include "stdafx.h"
#include "Endox.h"
#include "ProtocolliModDlg.h"

#include "EditStringCheckDlg.h"
#include "EditStringDlg.h"
#include "ProtocolloCardioSet.h"
#include "ProtocolloColonneSet.h"
#include "ProtocolloValoriDefaultSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CProtocolliModDlg, CDialog)

CProtocolliModDlg::CProtocolliModDlg(CWnd* pParent)
	: CDialog(CProtocolliModDlg::IDD, pParent),
	m_ctrlList03(TRUE, TRUE, TRUE)
{
	m_lIDProtocollo = 0;

	m_nColonnaTempo = -1;
	m_nColonnaSommaTempo = -1;
}

CProtocolliModDlg::~CProtocolliModDlg()
{
}

BEGIN_MESSAGE_MAP(CProtocolliModDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_01_NEW, OnBnClickedBtn01New)
	ON_BN_CLICKED(IDC_BTN_01_EDT, OnBnClickedBtn01Edt)
	ON_BN_CLICKED(IDC_BTN_01_DEL, OnBnClickedBtn01Del)
	ON_BN_CLICKED(IDC_BTN_02_NEW, OnBnClickedBtn02New)
	ON_BN_CLICKED(IDC_BTN_02_EDT, OnBnClickedBtn02Edt)
	ON_BN_CLICKED(IDC_BTN_02_DEL, OnBnClickedBtn02Del)
	ON_BN_CLICKED(IDC_BTN_03_NEW, OnBnClickedBtn03New)
	ON_BN_CLICKED(IDC_BTN_03_DEL, OnBnClickedBtn03Del)
	ON_BN_CLICKED(IDC_BTN_ESCI, OnBnClickedBtnEsci)

	ON_MESSAGE(WM_PROTOCOLLOCHANGED, OnList03SubitemChanged)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_01, OnLvnItemchangedList01)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_02, OnLvnItemchangedList02)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_03, OnLvnItemchangedList03)

END_MESSAGE_MAP()

void CProtocolliModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_01_NEW, m_ctrlBtn01New);
	DDX_Control(pDX, IDC_BTN_01_EDT, m_ctrlBtn01Edt);
	DDX_Control(pDX, IDC_BTN_01_DEL, m_ctrlBtn01Del);
	DDX_Control(pDX, IDC_BTN_02_NEW, m_ctrlBtn02New);
	DDX_Control(pDX, IDC_BTN_02_EDT, m_ctrlBtn02Edt);
	DDX_Control(pDX, IDC_BTN_02_DEL, m_ctrlBtn02Del);
	DDX_Control(pDX, IDC_BTN_03_NEW, m_ctrlBtn03New);
	DDX_Control(pDX, IDC_BTN_03_DEL, m_ctrlBtn03Del);
	DDX_Control(pDX, IDC_BTN_ESCI, m_ctrlBtnEsci);

	DDX_Control(pDX, IDC_LIST_01, m_ctrlList01);
	DDX_Control(pDX, IDC_LIST_02, m_ctrlList02);
	DDX_Control(pDX, IDC_LIST_03, m_ctrlList03);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
}

void CProtocolliModDlg::OnCancel()
{
}

BOOL CProtocolliModDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	m_ctrlStatic01.SetFont(&theApp.m_fontBold);
	m_ctrlStatic02.SetFont(&theApp.m_fontBold);
	m_ctrlStatic03.SetFont(&theApp.m_fontBold);
	m_ctrlBtnEsci.SetFont(&theApp.m_fontBold);

	//

	m_ctrlList01.SetExtendedStyle(m_ctrlList01.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList01.InsertColumn(0, theApp.GetMessageString(IDS_PROTOCOLLI_LIST01_COL00)); // descrizione //
	m_ctrlList01.InsertColumn(1, theApp.GetMessageString(IDS_PROTOCOLLI_LIST01_COL01)); // fase //
	m_ctrlList01.InsertColumn(2, "", LVCFMT_LEFT, 0);

	m_ctrlList02.SetExtendedStyle(m_ctrlList02.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList02.InsertColumn(0, theApp.GetMessageString(IDS_PROTOCOLLI_LIST02_COL00)); // descrizione //
	m_ctrlList02.InsertColumn(1, theApp.GetMessageString(IDS_PROTOCOLLI_LIST02_COL02)); // tipo //
	m_ctrlList02.InsertColumn(2, theApp.GetMessageString(IDS_PROTOCOLLI_LIST02_COL01)); // valore modificabile //
	m_ctrlList02.InsertColumn(3, "", LVCFMT_LEFT, 0);

	m_ctrlList03.SetExtendedStyle(m_ctrlList03.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList03.SetNotificationChangeValueMessage(WM_PROTOCOLLOCHANGED);

	//

	RiempiList01(0);

	//

	theApp.LocalizeDialog(this, CProtocolliModDlg::IDD, "ProtocolliModDlg");
	return TRUE;
}

void CProtocolliModDlg::OnOK()
{
}

void CProtocolliModDlg::OnBnClickedBtn01New()
{
	CEditStringDlg dlg(this, IDS_PROTOCOLLO_NUOVO, "");
	if (dlg.DoModal() == IDOK)
	{
		long lIDNew = CProtocolloCardioSet().AddRow(dlg.GetValue(), PROTOCOLLO_FASE_DURANTE);
		RiempiList01(lIDNew);
	}
}

void CProtocolliModDlg::OnBnClickedBtn01Edt()
{
	POSITION pos = m_ctrlList01.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlList01.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			long lIDMod = m_ctrlList01.GetItemData(nIndex);
			if (lIDMod > 0)
			{
				CEditStringDlg dlg(this, IDS_PROTOCOLLO_MODIFICA, m_ctrlList01.GetItemText(nIndex, 0));
				if (dlg.DoModal() == IDOK)
				{
					CProtocolloCardioSet().EdtRow(lIDMod, dlg.GetValue());
					RiempiList01(lIDMod);
				}
			}
		}
	}
}

void CProtocolliModDlg::OnBnClickedBtn01Del()
{
	POSITION pos = m_ctrlList01.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlList01.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			long lIDDel = m_ctrlList01.GetItemData(nIndex);
			if (lIDDel > 0)
			{
				if (theApp.AfxMessageBoxEndo(IDS_PROTOCOLLO_ELIMINA, MB_YESNO) == IDYES)
				{
					CProtocolloCardioSet().DelRow(lIDDel);
					RiempiList01(0);
				}
			}
		}
	}
}

void CProtocolliModDlg::OnBnClickedBtn02New()
{
	POSITION pos = m_ctrlList01.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_ctrlList01.GetNextSelectedItem(pos);
		if (nItem >= 0)
		{
			long lIDProtocollo = m_ctrlList01.GetItemData(nItem);

			CEditStringCheckDlg dlg(this, IDS_PROTOCOLLO_COLONNA_NUOVA, "", 0, FALSE);
			if (dlg.DoModal() == IDOK)
			{
				CString sDescrizione;
				long lTipo;
				BOOL bValoriModificabili;
				dlg.GetColonnaSetting(sDescrizione, lTipo, bValoriModificabili);

				long lIDNew = CProtocolloColonneSet().AddRow(lIDProtocollo, sDescrizione, lTipo, bValoriModificabili);
				RiempiList02(lIDNew);
			}
		}
	}
}

void CProtocolliModDlg::OnBnClickedBtn02Edt()
{
	POSITION pos = m_ctrlList02.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlList02.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			long lIDMod = m_ctrlList02.GetItemData(nIndex);
			if (lIDMod > 0)
			{
				CString sTipo = m_ctrlList02.GetItemText(nIndex, 1);
				long lTipo = 0;
				if (sTipo.CompareNoCase(theApp.GetMessageString(IDS_TEMPO)) == 0)
					lTipo = 1;
				else if (sTipo.CompareNoCase(theApp.GetMessageString(IDS_SOMMATEMPO)) == 0)
					lTipo = 2;
				else if (sTipo.CompareNoCase(theApp.GetMessageString(IDS_METS)) == 0)
					lTipo = 3;

				CEditStringCheckDlg dlg(this, IDS_PROTOCOLLO_COLONNA_MODIFICA, m_ctrlList02.GetItemText(nIndex, 0), lTipo, m_ctrlList02.GetItemText(nIndex, 2).CompareNoCase(theApp.GetMessageString(IDS_YES)) == 0);
				if (dlg.DoModal() == IDOK)
				{
					CString sDescrizione;
					long lTipo;
					BOOL bValoriModificabili;
					dlg.GetColonnaSetting(sDescrizione, lTipo, bValoriModificabili);

					CProtocolloColonneSet().EdtRow(lIDMod, sDescrizione, lTipo, bValoriModificabili);
					RiempiList02(lIDMod);
				}
			}
		}
	}
}

void CProtocolliModDlg::OnBnClickedBtn02Del()
{
	POSITION pos = m_ctrlList02.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlList02.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			long lIDDel = m_ctrlList02.GetItemData(nIndex);
			if (lIDDel > 0)
			{
				if (theApp.AfxMessageBoxEndo(IDS_PROTOCOLLO_COLONNA_ELIMINA, MB_YESNO) == IDYES)
				{
					CProtocolloColonneSet().DelRow(lIDDel);
					RiempiList02(0);
				}
			}
		}
	}
}

void CProtocolliModDlg::OnBnClickedBtn03New()
{
	CProtocolloValoriDefaultSet().AddEdtRow(m_lIDProtocollo, m_ctrlList02.GetItemData(0), CProtocolloValoriDefaultSet().GetNextOrdine(m_lIDProtocollo), "");
	RiempiList03();
	m_ctrlList03.SetItemState(m_ctrlList03.GetItemCount() - 1, LVIS_SELECTED, LVIS_SELECTED);
}

void CProtocolliModDlg::OnBnClickedBtn03Del()
{
	POSITION pos = m_ctrlList03.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlList03.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			long lIDDel = m_ctrlList03.GetItemData(nIndex);
			if (lIDDel > 0)
			{
				if (theApp.AfxMessageBoxEndo(IDS_PROTOCOLLO_RIGA_ELIMINA, MB_YESNO) == IDYES)
				{
					CProtocolloValoriDefaultSet().DelAllOrdi(m_lIDProtocollo, lIDDel);
					RiempiList03();
				}
			}
		}
	}
}

void CProtocolliModDlg::OnBnClickedBtnEsci()
{
	CDialog::OnOK();
}

void CProtocolliModDlg::RiempiList01(long lIDToSel)
{
	BeginWaitCursor();
	m_ctrlList01.SetRedraw(FALSE);
	m_ctrlList01.DeleteAllItems();

	int nIndex = 0;
	int nIndexToSel = -1;

	CProtocolloCardioSet setTemp;
	CString sFilter;

	// prima //

	sFilter.Format("FASE=%li", PROTOCOLLO_FASE_PRIMA);
	setTemp.SetOpenFilter(sFilter);
	if (setTemp.OpenRecordset("CProtocolliModDlg::RiempiList01"))
	{
		if (setTemp.IsEOF())
			CProtocolloCardioSet().AddRow(theApp.GetMessageString(IDS_PROTOCOLLO_FASE_0), PROTOCOLLO_FASE_PRIMA);

		setTemp.CloseRecordset("CProtocolliModDlg::RiempiList01");
	}

	// dopo //

	sFilter.Format("FASE=%li", PROTOCOLLO_FASE_DOPO);
	setTemp.SetOpenFilter(sFilter);
	if (setTemp.OpenRecordset("CProtocolliModDlg::RiempiList01"))
	{
		if (setTemp.IsEOF())
			CProtocolloCardioSet().AddRow(theApp.GetMessageString(IDS_PROTOCOLLO_FASE_2), PROTOCOLLO_FASE_DOPO);

		setTemp.CloseRecordset("CProtocolliModDlg::RiempiList01");
	}

	// riempio lista //

	setTemp.SetOpenFilter("");
	setTemp.SetSortRecord("FASE, DESCRIZIONE");
	if (setTemp.OpenRecordset("CProtocolliModDlg::RiempiList01"))
	{
		BOOL bFoundPre = FALSE;
		BOOL bFoundPost = FALSE;

		while (!setTemp.IsEOF())
		{
			m_ctrlList01.InsertItem(nIndex, setTemp.m_sDescrizione);
			m_ctrlList01.SetItemData(nIndex, setTemp.m_lID);

			switch (setTemp.m_lFase)
			{
				case PROTOCOLLO_FASE_PRIMA:
				{
					m_ctrlList01.SetItemText(nIndex, 1, theApp.GetMessageString(IDS_PROTOCOLLO_FASE_0));
					break;
				}
				case PROTOCOLLO_FASE_DOPO:
				{
					m_ctrlList01.SetItemText(nIndex, 1, theApp.GetMessageString(IDS_PROTOCOLLO_FASE_2));
					break;
				}
				default:
				{
					m_ctrlList01.SetItemText(nIndex, 1, theApp.GetMessageString(IDS_PROTOCOLLO_FASE_1));
					break;
				}
			}

			if (setTemp.m_lID == lIDToSel)
				nIndexToSel = nIndex;

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CProtocolliModDlg::RiempiList01");
	}

	//

	if (nIndexToSel >= 0)
		m_ctrlList01.SetItemState(nIndexToSel, LVIS_SELECTED, LVIS_SELECTED);

	//

	m_ctrlList01.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList01.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	//

	m_ctrlList01.SetRedraw(TRUE);
	EndWaitCursor();
}

void CProtocolliModDlg::RiempiList02(long lIDToSel)
{
	BeginWaitCursor();
	m_ctrlList02.SetRedraw(FALSE);
	m_ctrlList02.DeleteAllItems();

	int nIndexToSel = -1;

	m_nColonnaTempo = -1;
	m_nColonnaSommaTempo = -1;

	//

	if (m_lIDProtocollo > 0)
	{
		CString sFilter;
		sFilter.Format("IDPROTOCOLLO=%li", m_lIDProtocollo);

		CProtocolloColonneSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		setTemp.SetSortRecord("ORDINE");
		if (setTemp.OpenRecordset("CProtocolliModDlg::RiempiList02"))
		{
			int nIndex = 0;
			while (!setTemp.IsEOF())
			{
				m_ctrlList02.InsertItem(nIndex, setTemp.m_sDescrizione);
				m_ctrlList02.SetItemData(nIndex, setTemp.m_lID);

				CString sTipo = theApp.GetMessageString(IDS_TESTO);
				if (setTemp.m_lTipo == 1)
				{
					sTipo = theApp.GetMessageString(IDS_TEMPO);

					if (m_nColonnaTempo < 0)
						m_nColonnaTempo = nIndex;
				}
				else if (setTemp.m_lTipo == 2)
				{
					sTipo = theApp.GetMessageString(IDS_SOMMATEMPO);

					if (m_nColonnaSommaTempo < 0)
						m_nColonnaSommaTempo = nIndex;
				}
				else if (setTemp.m_lTipo == 3)
				{
					sTipo = theApp.GetMessageString(IDS_METS);
				}
				m_ctrlList02.SetItemText(nIndex, 1, sTipo);

				m_ctrlList02.SetItemText(nIndex, 2, theApp.GetMessageString(setTemp.m_bValoriModificabili ? IDS_YES : IDS_NO));

				if (setTemp.m_lID == lIDToSel)
					nIndexToSel = nIndex;

				nIndex++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CProtocolliModDlg::RiempiList02");
		}
	}

	//

	if (nIndexToSel >= 0)
		m_ctrlList02.SetItemState(nIndexToSel, LVIS_SELECTED, LVIS_SELECTED);

	//

	m_ctrlList02.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList02.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList02.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

	//

	m_ctrlList02.SetRedraw(TRUE);
	EndWaitCursor();

	//

	RiempiList03();
}

void CProtocolliModDlg::RiempiList03()
{
	BeginWaitCursor();
	m_ctrlList03.SetRedraw(FALSE);
	m_ctrlList03.DeleteAllItems();

	while (m_ctrlList03.GetHeaderCtrl()->GetItemCount() > 0)
		m_ctrlList03.DeleteColumn(0);

	//

	for (int i = 0; i < m_ctrlList02.GetItemCount(); i++)
		m_ctrlList03.InsertColumn(i, m_ctrlList02.GetItemText(i, 0));
	m_ctrlList03.InsertColumn(m_ctrlList02.GetItemCount(), "", LVCFMT_LEFT, 0);

	//

	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li", m_lIDProtocollo);

	CProtocolloValoriDefaultSet setTemp;
	setTemp.SetOpenFilter(sFilter);
	setTemp.SetSortRecord("ORDINE, IDCOLONNA");
	if (setTemp.OpenRecordset("CProtocolliModDlg::RiempiList03"))
	{
		int nIndex = -1;
		long lLastOrder = -1;

		while (!setTemp.IsEOF())
		{
			// se serve aggiungo una riga //

			if (setTemp.m_lOrdine != lLastOrder)
			{
				nIndex++;

				m_ctrlList03.InsertItem(nIndex, "");
				m_ctrlList03.SetItemData(nIndex, setTemp.m_lOrdine);

				for (int i = 0; i < m_ctrlList02.GetItemCount(); i++)
				{
					if ((m_ctrlList02.GetItemText(i, 1).CompareNoCase(theApp.GetMessageString(IDS_TESTO)) == 0) || (m_ctrlList02.GetItemText(i, 1).CompareNoCase(theApp.GetMessageString(IDS_METS)) == 0))
						m_ctrlList03.SetSubItemEdit(nIndex, i, FALSE, 250);
					else if (m_ctrlList02.GetItemText(i, 1).CompareNoCase(theApp.GetMessageString(IDS_TEMPO)) == 0)
						m_ctrlList03.SetSubItemEditTimeSec(nIndex, i);
				}

				lLastOrder = setTemp.m_lOrdine;
			}

			//

			for (int i = 0; i < m_ctrlList02.GetItemCount(); i++)
			{
				if (m_ctrlList02.GetItemData(i) == setTemp.m_lIDColonna)
				{
					if(m_ctrlList02.GetItemText(i, 0).CompareNoCase(theApp.GetMessageString(IDS_SOMMATEMPO)) != 0)
						m_ctrlList03.SetItemText(nIndex, i, setTemp.m_sValore);
					break;
				}
			}

			//

			setTemp.MoveNext();
		}
		setTemp.CloseRecordset("CProtocolliModDlg::RiempiList03");
	}

	//

	for (int i = 0; i < m_ctrlList02.GetItemCount(); i++)
		m_ctrlList03.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	//

	for (int iSubItem = 0; iSubItem < m_ctrlList02.GetItemCount(); iSubItem++)
	{
		if (m_ctrlList02.GetItemText(iSubItem, 2).CompareNoCase(theApp.GetMessageString(IDS_YES)) != 0)
		{
			for (int iItem = 0; iItem < m_ctrlList03.GetItemCount(); iItem++)
				m_ctrlList03.SetSubItemBkColor(iItem, iSubItem, RGB(191, 191, 191));
		}
		else
		{
			for (int iItem = 0; iItem < m_ctrlList03.GetItemCount(); iItem++)
				m_ctrlList03.SetSubItemBkColor(iItem, iSubItem, RGB(255, 255, 191));
		}
	}

	//

	CalcolaTempi();

	//

	m_ctrlList03.SetRedraw(TRUE);
	EndWaitCursor();
}

void CProtocolliModDlg::CalcolaTempi()
{
	if ((m_nColonnaTempo >= 0) && (m_nColonnaSommaTempo >= 0))
	{
		long lSommaSecondi = 0;

		for (int i = 0; i < m_ctrlList03.GetItemCount(); i++)
		{
			CString sTemp = m_ctrlList03.GetItemText(i, m_nColonnaTempo);

			if (isdigit(sTemp[0]) &&
				isdigit(sTemp[1]) &&
				(sTemp[2] == ' ' || sTemp[2] == '.' || sTemp[2] == ':') &&
				isdigit(sTemp[3]) &&
				isdigit(sTemp[4]) &&
				(sTemp[5] == ' ' || sTemp[5] == '.' || sTemp[5] == ':') &&
				isdigit(sTemp[6]) &&
				isdigit(sTemp[7]))
			{
				CString sH = sTemp.Mid(0, 2);
				CString sM = sTemp.Mid(3, 2);
				CString sS = sTemp.Mid(6, 2);

				long lSeconds = (atol(sH) * 60 * 60) + (atol(sM) * 60) + atol(sS);
				lSommaSecondi += lSeconds;

				long lSH = (lSommaSecondi / 60) / 60;
				long lSM = (lSommaSecondi / 60) % 60;
				long lSS = lSommaSecondi % 60;

				CString sTeeemp;
				sTeeemp.Format("%02li:%02li:%02li", lSH, lSM, lSS);
				m_ctrlList03.SetItemText(i, m_nColonnaSommaTempo, sTeeemp);
			}
			else
			{
				m_ctrlList03.SetItemText(i, m_nColonnaTempo, "00:00:00");
			}
		}
	}
}

void CProtocolliModDlg::OnLvnItemchangedList01(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	//

	m_ctrlBtn01Edt.EnableWindow(m_ctrlList01.GetFirstSelectedItemPosition() != NULL);
	m_ctrlBtn01Del.EnableWindow(m_ctrlList01.GetFirstSelectedItemPosition() != NULL);

	m_ctrlBtn02New.EnableWindow(m_ctrlList01.GetFirstSelectedItemPosition() != NULL);
	m_ctrlBtn02Edt.EnableWindow(FALSE);
	m_ctrlBtn02Del.EnableWindow(FALSE);

	m_ctrlBtn03New.EnableWindow((m_ctrlList01.GetFirstSelectedItemPosition() != NULL) && (m_ctrlList02.GetItemCount() > 0));
	m_ctrlBtn03Del.EnableWindow(FALSE);

	//

	m_lIDProtocollo = 0;

	POSITION pos = m_ctrlList01.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_ctrlList01.GetNextSelectedItem(pos);
		if (nItem >= 0)
			m_lIDProtocollo = m_ctrlList01.GetItemData(nItem);
	}

	//

	RiempiList02(0);

	//

	*pResult = 0;
}

void CProtocolliModDlg::OnLvnItemchangedList02(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_ctrlBtn02Edt.EnableWindow(m_ctrlList02.GetFirstSelectedItemPosition() != NULL);
	m_ctrlBtn02Del.EnableWindow(m_ctrlList02.GetFirstSelectedItemPosition() != NULL);

	m_ctrlBtn03New.EnableWindow((m_ctrlList01.GetFirstSelectedItemPosition() != NULL) && (m_ctrlList02.GetItemCount() > 0));
	m_ctrlBtn03Del.EnableWindow(FALSE);

	*pResult = 0;
}

void CProtocolliModDlg::OnLvnItemchangedList03(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_ctrlBtn03Del.EnableWindow(m_ctrlList03.GetFirstSelectedItemPosition() != NULL);

	*pResult = 0;
}

LRESULT CProtocolliModDlg::OnList03SubitemChanged(WPARAM wParam, LPARAM lParam)
{
	if ((wParam >= 0) && (lParam >= 0))
	{
		long lIDColonna = m_ctrlList02.GetItemData(lParam);
		long lOrdine = m_ctrlList03.GetItemData(wParam);

		if ((lIDColonna > 0) && (lOrdine > 0))
		{
			CProtocolloValoriDefaultSet().AddEdtRow(m_lIDProtocollo, lIDColonna, lOrdine, m_ctrlList03.GetItemText(wParam, lParam));
			m_ctrlList03.SetColumnWidth(lParam, LVSCW_AUTOSIZE_USEHEADER);
		}
	}

	CalcolaTempi();

	return 0;
}
