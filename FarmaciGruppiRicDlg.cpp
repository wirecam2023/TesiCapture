#include "stdafx.h"
#include "Endox.h"
#include "FarmaciGruppiRicDlg.h"

#include "EditFarmacoDlg.h"
#include "EditStringDlg.h"
#include "FarmaciGruppiRicItemsSet.h"
#include "FarmaciGruppiRicSet.h"
#include "VistaFarmaciGruppiRicSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFarmaciGruppiRicDlg, CDialog)

CFarmaciGruppiRicDlg::CFarmaciGruppiRicDlg(CWnd* pParent)
	: CDialog(CFarmaciGruppiRicDlg::IDD, pParent)
{
}

CFarmaciGruppiRicDlg::~CFarmaciGruppiRicDlg()
{
}

BEGIN_MESSAGE_MAP(CFarmaciGruppiRicDlg, CDialog)
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

void CFarmaciGruppiRicDlg::DoDataExchange(CDataExchange* pDX)
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

void CFarmaciGruppiRicDlg::OnCancel()
{
}

BOOL CFarmaciGruppiRicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlListSx.SetExtendedStyle(m_ctrlListSx.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListSx.InsertColumn(0, "Gruppi");
	m_ctrlListSx.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListDx.SetExtendedStyle(m_ctrlListDx.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListDx.InsertColumn(0, "Nome", LVCFMT_LEFT);
	m_ctrlListDx.InsertColumn(1, "Principio attivo", LVCFMT_LEFT);
	m_ctrlListDx.InsertColumn(2, "Descrizione", LVCFMT_LEFT);
	m_ctrlListDx.InsertColumn(3, "Quantita", LVCFMT_RIGHT);
	m_ctrlListDx.InsertColumn(4, "Testo libero");

	m_ctrlListDx.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListDx.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListDx.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListDx.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListDx.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);

	RiempiListaSx();

	theApp.LocalizeDialog(this, CFarmaciGruppiRicDlg::IDD, "FarmaciGruppiRicDlg");
	return TRUE;
}

void CFarmaciGruppiRicDlg::OnOK()
{
}

void CFarmaciGruppiRicDlg::OnLvnItemchangedListSx(NMHDR *pNMHDR, LRESULT *pResult)
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

void CFarmaciGruppiRicDlg::OnLvnItemchangedListDx(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListDx.GetFirstSelectedItemPosition();

	m_ctrlBtnEdtDx.EnableWindow(pos != NULL);
	m_ctrlBtnDelDx.EnableWindow(pos != NULL);
}

void CFarmaciGruppiRicDlg::OnBnClickedBtnNewSx()
{
	CEditStringDlg dlg(this, IDS_FARMACIGRUPPIRICDLG_TITLE1, "");
	if ((dlg.DoModal() == IDOK) && (!dlg.GetValue().Trim().IsEmpty()))
	{
		CFarmaciGruppiRicSet setTemp;
		setTemp.SetOpenFilter("ID=0");
		if (setTemp.OpenRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnNewSx"))
		{
			if (setTemp.AddNewRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnNewSx"))
			{
				setTemp.m_sDescrizione = dlg.GetValue();
				if (setTemp.UpdateRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnNewSx"))
				{
					BOOL bInserted = FALSE;

					tagRicettaElement tagToAdd;
					tagToAdd.m_lID = setTemp.GetLastAdd();
					tagToAdd.m_sDescrizione = dlg.GetValue();
					tagToAdd.m_sDescrizione.MakeUpper();

					POSITION pos = theApp.m_listGruppiFarmaci.GetHeadPosition();
					while(pos != NULL)
					{
						if (tagToAdd.m_sDescrizione.CompareNoCase(theApp.m_listGruppiFarmaci.GetAt(pos).m_sDescrizione) < 0)
						{
							theApp.m_listGruppiFarmaci.InsertBefore(pos, tagToAdd);
							bInserted = TRUE;

							break;
						}
						theApp.m_listGruppiFarmaci.GetNext(pos);
					} 

					if (!bInserted)
						theApp.m_listGruppiFarmaci.AddTail(tagToAdd);
				}
			}

			setTemp.CloseRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnNewSx");
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

void CFarmaciGruppiRicDlg::OnBnClickedBtnEdtSx()
{
	POSITION pos = m_ctrlListSx.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListSx.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			long lID = (long)m_ctrlListSx.GetItemData(nIndex);
			CString sDescrizione = m_ctrlListSx.GetItemText(nIndex, 0);

			CEditStringDlg dlg(this, IDS_FARMACIGRUPPIRICDLG_TITLE2, sDescrizione);
			if ((dlg.DoModal() == IDOK) && (!dlg.GetValue().Trim().IsEmpty()))
			{
				CString strFilter;
				strFilter.Format("ID=%li", lID);

				CFarmaciGruppiRicSet setTemp;
				setTemp.SetOpenFilter(strFilter);
				if (setTemp.OpenRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtSx"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtSx"))
						{
							setTemp.m_sDescrizione = dlg.GetValue();
							if (setTemp.UpdateRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtSx"))
							{
								POSITION pos = theApp.m_listGruppiFarmaci.GetHeadPosition();
								while(pos != NULL)
								{
									if (theApp.m_listGruppiFarmaci.GetAt(pos).m_lID == lID)
									{
										theApp.m_listGruppiFarmaci.RemoveAt(pos);
										break;
									}
									theApp.m_listGruppiFarmaci.GetNext(pos);
								} 

								// --- //

								BOOL bInserted = FALSE;

								tagRicettaElement tagToAdd;
								tagToAdd.m_lID = lID;
								tagToAdd.m_sDescrizione = dlg.GetValue();
								tagToAdd.m_sDescrizione.MakeUpper();

								pos = theApp.m_listGruppiFarmaci.GetHeadPosition();
								while(pos != NULL)
								{
									if (tagToAdd.m_sDescrizione.CompareNoCase(theApp.m_listGruppiFarmaci.GetAt(pos).m_sDescrizione) < 0)
									{
										theApp.m_listGruppiFarmaci.InsertBefore(pos, tagToAdd);
										bInserted = TRUE;

										break;
									}
									theApp.m_listGruppiFarmaci.GetNext(pos);
								} 

								if (!bInserted)
									theApp.m_listGruppiFarmaci.AddTail(tagToAdd);
							}
						}
					}

					setTemp.CloseRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtSx");
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

void CFarmaciGruppiRicDlg::OnBnClickedBtnDelSx()
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
			strMB.Format(theApp.GetMessageString(IDS_FARMACIGRUPPIRICDLG_MB1), sDescrizione);
			if (theApp.AfxMessageBoxEndo(strMB, MB_YESNO | MB_ICONSTOP) == IDYES)
			{
				CString strFilter;
				strFilter.Format("ID=%li", lID);

				CFarmaciGruppiRicSet setTemp;
				setTemp.SetOpenFilter(strFilter);
				if (setTemp.OpenRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtSx"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.DeleteRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtSx"))
						{
							POSITION pos = theApp.m_listGruppiFarmaci.GetHeadPosition();
							while(pos != NULL)
							{
								if (theApp.m_listGruppiFarmaci.GetAt(pos).m_lID == lID)
								{
									theApp.m_listGruppiFarmaci.RemoveAt(pos);
									break;
								}

								theApp.m_listGruppiFarmaci.GetNext(pos);
							} 
						}
					}

					setTemp.CloseRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtSx");
				}

				RiempiListaSx();
			}
		}
	}
}

void CFarmaciGruppiRicDlg::OnBnClickedBtnNewDx()
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
				CEditFarmacoDlg dlg(this, 0, 1, "");
				if ((dlg.DoModal() == IDOK) && (dlg.GetIDFarmaco() > 0))
				{
					CFarmaciGruppiRicItemsSet setTemp;
					setTemp.SetOpenFilter("ID=0");
					if (setTemp.OpenRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnNewDx"))
					{
						if (setTemp.AddNewRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnNewDx"))
						{
							setTemp.m_lIDGruppo = lIDGruppo;
							setTemp.m_lIDFarmaco = dlg.GetIDFarmaco();
							setTemp.m_lQuantita = dlg.GetQuantita();
							setTemp.m_sTestoLibero = dlg.GetTestoLibero();
							setTemp.UpdateRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnNewDx");
						}

						setTemp.CloseRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnNewDx");
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

void CFarmaciGruppiRicDlg::OnBnClickedBtnEdtDx()
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
						long lQuantita = atol(m_ctrlListDx.GetItemText(nIndex, 3));
						CString sTestoLibero = m_ctrlListDx.GetItemText(nIndex, 4);

						CEditFarmacoDlg dlg(this, CFarmaciGruppiRicItemsSet().GetIDFarmaco(lID), lQuantita, sTestoLibero);
						if ((dlg.DoModal() == IDOK) && (dlg.GetIDFarmaco() > 0))
						{
							CString strFilter;
							strFilter.Format("ID=%li", lID);

							CFarmaciGruppiRicItemsSet setTemp;
							setTemp.SetOpenFilter(strFilter);
							if (setTemp.OpenRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtDx"))
							{
								if (!setTemp.IsEOF())
								{
									if (setTemp.EditRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtDx"))
									{
										setTemp.m_lIDGruppo = lIDGruppo;
										setTemp.m_lIDFarmaco = dlg.GetIDFarmaco();
										setTemp.m_lQuantita = dlg.GetQuantita();
										setTemp.m_sTestoLibero = dlg.GetTestoLibero();
										setTemp.UpdateRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtDx");
									}
								}

								setTemp.CloseRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtDx");
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

void CFarmaciGruppiRicDlg::OnBnClickedBtnDelDx()
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
						strMB.Format(theApp.GetMessageString(IDS_FARMACIGRUPPIRICDLG_MB2), sDescrizione);
						if (theApp.AfxMessageBoxEndo(strMB, MB_YESNO | MB_ICONSTOP) == IDYES)
						{
							CString strFilter;
							strFilter.Format("ID=%li", lID);

							CFarmaciGruppiRicItemsSet setTemp;
							setTemp.SetOpenFilter(strFilter);
							if (setTemp.OpenRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtDx"))
							{
								if (!setTemp.IsEOF())
									setTemp.DeleteRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtDx");

								setTemp.CloseRecordset("CFarmaciGruppiRicDlg::OnBnClickedBtnEdtDx");
							}

							RiempiListaDx(lIDGruppo);
						}
					}
				}
			}
		}
	}
}

void CFarmaciGruppiRicDlg::OnBnClickedBtnEsci()
{
	CDialog::OnOK();
}

void CFarmaciGruppiRicDlg::RiempiListaSx()
{
	BeginWaitCursor();
	m_ctrlListSx.SetRedraw(FALSE);
	m_ctrlListSx.DeleteAllItems();

	int nIndex = 0;

	POSITION pos = theApp.m_listGruppiFarmaci.GetHeadPosition();
	while(pos != NULL)
	{
		tagRicettaElement tagTemp = theApp.m_listGruppiFarmaci.GetAt(pos);

		m_ctrlListSx.InsertItem(nIndex, tagTemp.m_sDescrizione);
		m_ctrlListSx.SetItemData(nIndex, tagTemp.m_lID);

		nIndex++;
		theApp.m_listGruppiFarmaci.GetNext(pos);
	} 

	m_ctrlListSx.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListSx.SetRedraw(TRUE);
	EndWaitCursor();
}

void CFarmaciGruppiRicDlg::RiempiListaDx(long lIDGruppo)
{
	BeginWaitCursor();
	m_ctrlListDx.SetRedraw(FALSE);
	m_ctrlListDx.DeleteAllItems();

	CString strFilter;
	strFilter.Format("IDGruppo=%li", lIDGruppo);

	CVistaFarmaciGruppiRicSet setTemp;
	setTemp.SetOpenFilter(strFilter);
	if (setTemp.OpenRecordset("CFarmaciGruppiRicDlg::RiempiListaDx"))
	{
		int nIndex = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlListDx.InsertItem(nIndex, setTemp.m_sNome);
			m_ctrlListDx.SetItemData(nIndex, setTemp.m_lID);

			m_ctrlListDx.SetItemText(nIndex, 1, setTemp.m_sPrincipioAttivo);

			m_ctrlListDx.SetItemText(nIndex, 2, setTemp.m_sDescrizione);

			CString sQ;
			sQ.Format("%li", setTemp.m_lQuantita);
			m_ctrlListDx.SetItemText(nIndex, 3, sQ);

			m_ctrlListDx.SetItemText(nIndex, 4, setTemp.m_sTestoLibero);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CFarmaciGruppiRicDlg::RiempiListaDx");
	}

	m_ctrlListDx.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListDx.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListDx.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListDx.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListDx.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListDx.SetRedraw(TRUE);
	EndWaitCursor();
}