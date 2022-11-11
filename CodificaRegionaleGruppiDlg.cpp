#include "stdafx.h"
#include "Endox.h"
#include "CodificaRegionaleGruppiDlg.h"

#include "CodificaRegionaleGruppiItemsSet.h"
#include "CodificaRegionaleGruppiSet.h"
#include "EditCodificaRegionaleDlg.h"
#include "EditStringDlg.h"
#include "VistaCodificaRegionaleGruppiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCodificaRegionaleGruppiDlg, CDialog)

CCodificaRegionaleGruppiDlg::CCodificaRegionaleGruppiDlg(CWnd* pParent)
	: CDialog(CCodificaRegionaleGruppiDlg::IDD, pParent)
{
}

CCodificaRegionaleGruppiDlg::~CCodificaRegionaleGruppiDlg()
{
}

BEGIN_MESSAGE_MAP(CCodificaRegionaleGruppiDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_NEW_SX, OnBnClickedBtnNewSx)
	ON_BN_CLICKED(IDC_BTN_EDT_SX, OnBnClickedBtnEdtSx)
	ON_BN_CLICKED(IDC_BTN_DEL_SX, OnBnClickedBtnDelSx)
	ON_BN_CLICKED(IDC_BTN_NEW_DX, OnBnClickedBtnNewDx)
	ON_BN_CLICKED(IDC_BTN_EDT_DX, OnBnClickedBtnEdtDx)
	ON_BN_CLICKED(IDC_BTN_DEL_DX, OnBnClickedBtnDelDx)
	ON_BN_CLICKED(IDC_BTN_ESCI, OnBnClickedBtnEsci)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SX, OnLvnItemchangedListSx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DX, OnLvnItemchangedListDx)
END_MESSAGE_MAP()

void CCodificaRegionaleGruppiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW_SX, m_ctrlBtnNewSx);
	DDX_Control(pDX, IDC_BTN_EDT_SX, m_ctrlBtnEdtSx);
	DDX_Control(pDX, IDC_BTN_DEL_SX, m_ctrlBtnDelSx);
	DDX_Control(pDX, IDC_BTN_NEW_DX, m_ctrlBtnNewDx);
	DDX_Control(pDX, IDC_BTN_EDT_DX, m_ctrlBtnEdtDx);
	DDX_Control(pDX, IDC_BTN_DEL_DX, m_ctrlBtnDelDx);

	DDX_Control(pDX, IDC_LIST_SX, m_ctrlListSx);
	DDX_Control(pDX, IDC_LIST_DX, m_ctrlListDx);
}

void CCodificaRegionaleGruppiDlg::OnCancel()
{
}

BOOL CCodificaRegionaleGruppiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlListSx.SetExtendedStyle(m_ctrlListSx.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListSx.InsertColumn(0, "Gruppo");
	m_ctrlListSx.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListDx.SetExtendedStyle(m_ctrlListDx.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListDx.InsertColumn(0, "Prestazione");
	m_ctrlListDx.InsertColumn(1, "Quantita", LVCFMT_RIGHT);
	m_ctrlListDx.InsertColumn(2, "Testo libero");
	m_ctrlListDx.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListDx.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListDx.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

	RiempiListaSx();

	theApp.LocalizeDialog(this, CCodificaRegionaleGruppiDlg::IDD, "CodificaRegionaleGruppiDlg");
	return TRUE;
}

void CCodificaRegionaleGruppiDlg::OnOK()
{
}

void CCodificaRegionaleGruppiDlg::OnLvnItemchangedListSx(NMHDR *pNMHDR, LRESULT *pResult)
{
	long lID = 0;

	POSITION pos = m_ctrlListSx.GetFirstSelectedItemPosition();

	m_ctrlBtnEdtSx.EnableWindow(pos != NULL);
	m_ctrlBtnDelSx.EnableWindow(pos != NULL);
	m_ctrlBtnNewDx.EnableWindow(pos != NULL);

	if (pos != NULL)
	{
		int nIndex = m_ctrlListSx.GetNextSelectedItem(pos);
		if (nIndex >= 0)
			lID = (long)m_ctrlListSx.GetItemData(nIndex);
	}

	RiempiListaDx(lID);
	OnLvnItemchangedListDx(NULL, NULL);
}

void CCodificaRegionaleGruppiDlg::OnLvnItemchangedListDx(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListDx.GetFirstSelectedItemPosition();

	m_ctrlBtnEdtDx.EnableWindow(pos != NULL);
	m_ctrlBtnDelDx.EnableWindow(pos != NULL);
}

void CCodificaRegionaleGruppiDlg::OnBnClickedBtnNewSx()
{
	CEditStringDlg dlg(this, IDS_CODIFICAREGIONALEGRUPPIRICDLG_TITLE1, "");
	if ((dlg.DoModal() == IDOK) && (!dlg.GetValue().Trim().IsEmpty()))
	{
		CCodificaRegionaleGruppiSet setTemp;
		setTemp.SetOpenFilter("ID=0");
		if (setTemp.OpenRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnNewSx"))
		{
			if (setTemp.AddNewRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnNewSx"))
			{
				setTemp.m_sDescrizione = dlg.GetValue();
				if (setTemp.UpdateRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnNewSx"))
				{
					BOOL bInserted = FALSE;

					tagRicettaElement tagToAdd;
					tagToAdd.m_lID = setTemp.GetLastAdd();
					tagToAdd.m_sDescrizione = dlg.GetValue();
					tagToAdd.m_sDescrizione.MakeUpper();

					POSITION pos = theApp.m_listGruppiPrestazioni.GetHeadPosition();
					while(pos != NULL)
					{
						if (tagToAdd.m_sDescrizione.CompareNoCase(theApp.m_listGruppiPrestazioni.GetAt(pos).m_sDescrizione) < 0)
						{
							theApp.m_listGruppiPrestazioni.InsertBefore(pos, tagToAdd);
							bInserted = TRUE;

							break;
						}
						theApp.m_listGruppiPrestazioni.GetNext(pos);
					} 

					if (!bInserted)
						theApp.m_listGruppiPrestazioni.AddTail(tagToAdd);
				}
			}

			setTemp.CloseRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnNewSx");
		}

		RiempiListaSx();

		for(int i = 0; i < m_ctrlListSx.GetItemCount(); i++)
		{
			if ((long)m_ctrlListSx.GetItemData(i) == setTemp.GetLastAdd())
				m_ctrlListSx.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			else
				m_ctrlListSx.SetItemState(i, 0, LVIS_SELECTED);
		}
	}
}

void CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtSx()
{
	POSITION pos = m_ctrlListSx.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListSx.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			long lID = (long)m_ctrlListSx.GetItemData(nIndex);
			CString sDescrizione = m_ctrlListSx.GetItemText(nIndex, 0);

			CEditStringDlg dlg(this, IDS_CODIFICAREGIONALEGRUPPIRICDLG_TITLE2, sDescrizione);
			if ((dlg.DoModal() == IDOK) && (!dlg.GetValue().Trim().IsEmpty()))
			{
				CString strFilter;
				strFilter.Format("ID=%li", lID);

				CCodificaRegionaleGruppiSet setTemp;
				setTemp.SetOpenFilter(strFilter);
				if (setTemp.OpenRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtSx"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtSx"))
						{
							setTemp.m_sDescrizione = dlg.GetValue();
							if (setTemp.UpdateRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtSx"))
							{
								POSITION pos = theApp.m_listGruppiPrestazioni.GetHeadPosition();
								while(pos != NULL)
								{
									if (theApp.m_listGruppiPrestazioni.GetAt(pos).m_lID == lID)
									{
										theApp.m_listGruppiPrestazioni.RemoveAt(pos);
										break;
									}
									theApp.m_listGruppiPrestazioni.GetNext(pos);
								} 

								// --- //

								BOOL bInserted = FALSE;

								tagRicettaElement tagToAdd;
								tagToAdd.m_lID = lID;
								tagToAdd.m_sDescrizione = dlg.GetValue();
								tagToAdd.m_sDescrizione.MakeUpper();

								pos = theApp.m_listGruppiPrestazioni.GetHeadPosition();
								while(pos != NULL)
								{
									if (tagToAdd.m_sDescrizione.CompareNoCase(theApp.m_listGruppiPrestazioni.GetAt(pos).m_sDescrizione) < 0)
									{
										theApp.m_listGruppiPrestazioni.InsertBefore(pos, tagToAdd);
										bInserted = TRUE;

										break;
									}
									theApp.m_listGruppiPrestazioni.GetNext(pos);
								} 

								if (!bInserted)
									theApp.m_listGruppiPrestazioni.AddTail(tagToAdd);
							}
						}
					}

					setTemp.CloseRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtSx");
				}

				RiempiListaSx();

				for(int i = 0; i < m_ctrlListSx.GetItemCount(); i++)
				{
					if ((long)m_ctrlListSx.GetItemData(i) == lID)
						m_ctrlListSx.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
					else
						m_ctrlListSx.SetItemState(i, 0, LVIS_SELECTED);
				}
			}
		}
	}
}

void CCodificaRegionaleGruppiDlg::OnBnClickedBtnDelSx()
{
	POSITION pos = m_ctrlListSx.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListSx.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			long lID = (long)m_ctrlListSx.GetItemData(nIndex);
			CString sDescrizione = m_ctrlListSx.GetItemText(nIndex, 0);

			CString strMB;
			strMB.Format(theApp.GetMessageString(IDS_CODIFICAREGIONALEGRUPPIRICDLG_MB1), sDescrizione);
			if (theApp.AfxMessageBoxEndo(strMB, MB_YESNO | MB_ICONSTOP) == IDYES)
			{
				CString strFilter;
				strFilter.Format("ID=%li", lID);

				CCodificaRegionaleGruppiSet setTemp;
				setTemp.SetOpenFilter(strFilter);
				if (setTemp.OpenRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtSx"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.DeleteRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtSx"))
						{
							POSITION pos = theApp.m_listGruppiPrestazioni.GetHeadPosition();
							while(pos != NULL)
							{
								if (theApp.m_listGruppiPrestazioni.GetAt(pos).m_lID == lID)
								{
									theApp.m_listGruppiPrestazioni.RemoveAt(pos);
									break;
								}

								theApp.m_listGruppiPrestazioni.GetNext(pos);
							} 
						}
					}

					setTemp.CloseRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtSx");
				}

				RiempiListaSx();
			}
		}
	}
}

void CCodificaRegionaleGruppiDlg::OnBnClickedBtnNewDx()
{
	if (m_ctrlListDx.GetItemCount() >= theApp.m_lRicettaMaxItems)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RICETTA_TROPPEVOCI));
		return;
	}

	POSITION pos = m_ctrlListSx.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListSx.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			long lIDGruppo = (long)m_ctrlListSx.GetItemData(nIndex);

			if (lIDGruppo > 0)
			{
				CEditCodificaRegionaleDlg dlg(this, 0, 1, "");
				if ((dlg.DoModal() == IDOK) && (dlg.GetIDProcedura() > 0))
				{
					CCodificaRegionaleGruppiItemsSet setTemp;
					setTemp.SetOpenFilter("ID=0");
					if (setTemp.OpenRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnNewDx"))
					{
						if (setTemp.AddNewRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnNewDx"))
						{
							setTemp.m_lIDGruppo = lIDGruppo;
							setTemp.m_lIDProcedura = dlg.GetIDProcedura();
							setTemp.m_lQuantita = dlg.GetQuantita();
							setTemp.m_sTestoLibero = dlg.GetTestoLibero();
							setTemp.UpdateRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnNewDx");
						}

						setTemp.CloseRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnNewDx");
					}

					RiempiListaDx(lIDGruppo);

					for(int i = 0; i < m_ctrlListDx.GetItemCount(); i++)
					{
						if ((long)m_ctrlListDx.GetItemData(i) == setTemp.GetLastAdd())
							m_ctrlListDx.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
						else
							m_ctrlListDx.SetItemState(i, 0, LVIS_SELECTED);
					}
				}
			}
		}
	}
}

void CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtDx()
{
	POSITION pos = m_ctrlListSx.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListSx.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			long lIDGruppo = (long)m_ctrlListSx.GetItemData(nIndex);

			if (lIDGruppo > 0)
			{
				pos = m_ctrlListDx.GetFirstSelectedItemPosition();
				if (pos != NULL)
				{
					nIndex = m_ctrlListDx.GetNextSelectedItem(pos);
					if (nIndex >= 0)
					{
						long lID = (long)m_ctrlListDx.GetItemData(nIndex);
						long lQuantita = atol(m_ctrlListDx.GetItemText(nIndex, 1));
						CString sTestoLibero = m_ctrlListDx.GetItemText(nIndex, 2);

						CEditCodificaRegionaleDlg dlg(this, CCodificaRegionaleGruppiItemsSet().GetIDProcedura(lID), lQuantita, sTestoLibero);
						if ((dlg.DoModal() == IDOK) && (dlg.GetIDProcedura() > 0))
						{
							CString strFilter;
							strFilter.Format("ID=%li", lID);

							CCodificaRegionaleGruppiItemsSet setTemp;
							setTemp.SetOpenFilter(strFilter);
							if (setTemp.OpenRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtDx"))
							{
								if (!setTemp.IsEOF())
								{
									if (setTemp.EditRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtDx"))
									{
										setTemp.m_lIDGruppo = lIDGruppo;
										setTemp.m_lIDProcedura = dlg.GetIDProcedura();
										setTemp.m_lQuantita = dlg.GetQuantita();
										setTemp.m_sTestoLibero = dlg.GetTestoLibero();
										setTemp.UpdateRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtDx");
									}
								}

								setTemp.CloseRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtDx");
							}

							RiempiListaDx(lIDGruppo);

							for(int i = 0; i < m_ctrlListDx.GetItemCount(); i++)
							{
								if ((long)m_ctrlListDx.GetItemData(i) == lID)
									m_ctrlListDx.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
								else
									m_ctrlListDx.SetItemState(i, 0, LVIS_SELECTED);
							}
						}
					}
				}
			}
		}
	}
}

void CCodificaRegionaleGruppiDlg::OnBnClickedBtnDelDx()
{
	POSITION pos = m_ctrlListSx.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListSx.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			long lIDGruppo = (long)m_ctrlListSx.GetItemData(nIndex);

			if (lIDGruppo > 0)
			{
				pos = m_ctrlListDx.GetFirstSelectedItemPosition();
				if (pos != NULL)
				{
					nIndex = m_ctrlListDx.GetNextSelectedItem(pos);
					if (nIndex >= 0)
					{
						long lID = (long)m_ctrlListDx.GetItemData(nIndex);
						CString sDescrizione = m_ctrlListDx.GetItemText(nIndex, 0);

						CString strMB;
						strMB.Format(theApp.GetMessageString(IDS_CODIFICAREGIONALEGRUPPIRICDLG_MB2), sDescrizione);
						if (theApp.AfxMessageBoxEndo(strMB, MB_YESNO | MB_ICONSTOP) == IDYES)
						{
							CString strFilter;
							strFilter.Format("ID=%li", lID);

							CCodificaRegionaleGruppiItemsSet setTemp;
							setTemp.SetOpenFilter(strFilter);
							if (setTemp.OpenRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtDx"))
							{
								if (!setTemp.IsEOF())
									setTemp.DeleteRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtDx");

								setTemp.CloseRecordset("CCodificaRegionaleGruppiDlg::OnBnClickedBtnEdtDx");
							}

							RiempiListaDx(lIDGruppo);
						}
					}
				}
			}
		}
	}
}

void CCodificaRegionaleGruppiDlg::OnBnClickedBtnEsci()
{
	CDialog::OnOK();
}

void CCodificaRegionaleGruppiDlg::RiempiListaSx()
{
	BeginWaitCursor();
	m_ctrlListSx.SetRedraw(FALSE);
	m_ctrlListSx.DeleteAllItems();

	int nIndex = 0;

	POSITION pos = theApp.m_listGruppiPrestazioni.GetHeadPosition();
	while(pos != NULL)
	{
		tagRicettaElement tagTemp = theApp.m_listGruppiPrestazioni.GetAt(pos);

		m_ctrlListSx.InsertItem(nIndex, tagTemp.m_sDescrizione);
		m_ctrlListSx.SetItemData(nIndex, tagTemp.m_lID);

		nIndex++;
		theApp.m_listGruppiPrestazioni.GetNext(pos);
	} 

	m_ctrlListSx.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListSx.SetRedraw(TRUE);
	EndWaitCursor();
}

void CCodificaRegionaleGruppiDlg::RiempiListaDx(long lIDGruppo)
{
	BeginWaitCursor();
	m_ctrlListDx.SetRedraw(FALSE);
	m_ctrlListDx.DeleteAllItems();

	CString strFilter;
	strFilter.Format("IDGruppo=%li", lIDGruppo);

	CVistaCodificaRegionaleGruppiSet setTemp;
	setTemp.SetOpenFilter(strFilter);
	if (setTemp.OpenRecordset("CCodificaRegionaleGruppiDlg::RiempiListaDx"))
	{
		int nIndex = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlListDx.InsertItem(nIndex, setTemp.m_sDescrizione);
			m_ctrlListDx.SetItemData(nIndex, setTemp.m_lID);

			CString sQ;
			sQ.Format("%li", setTemp.m_lQuantita);
			m_ctrlListDx.SetItemText(nIndex, 1, sQ);

			m_ctrlListDx.SetItemText(nIndex, 2, setTemp.m_sTestoLibero);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CCodificaRegionaleGruppiDlg::RiempiListaDx");
	}

	m_ctrlListDx.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListDx.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListDx.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListDx.SetRedraw(TRUE);
	EndWaitCursor();
}