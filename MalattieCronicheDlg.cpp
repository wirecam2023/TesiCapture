#include "stdafx.h"
#include "Endox.h"
#include "MalattieCronicheDlg.h"

#include "ComboDynCampoDlg.h"
#include "Common.h"
#include "EditStringDlg.h"
#include "FarmaciPazientiCroniciSet.h"
#include "MalattieCronicheCampiSet.h"
#include "MalattieCronicheSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMalattieCronicheDlg, CDialog)

CMalattieCronicheDlg::CMalattieCronicheDlg(CWnd* pParent)
	: CDialog(CMalattieCronicheDlg::IDD, pParent)
{
}

CMalattieCronicheDlg::~CMalattieCronicheDlg()
{
}

BEGIN_MESSAGE_MAP(CMalattieCronicheDlg, CDialog)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MALATTIE, OnLvnItemchangedListMalattie)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CAMPI, OnLvnItemchangedListCampi)

	ON_BN_CLICKED(IDC_BTN_MAL_NEW, OnBnClickedBtnMalNew)
	ON_BN_CLICKED(IDC_BTN_MAL_EDT, OnBnClickedBtnMalEdt)
	ON_BN_CLICKED(IDC_BTN_MAL_DEL, OnBnClickedBtnMalDel)
	ON_BN_CLICKED(IDC_BTN_CAM_NEW, OnBnClickedBtnCamNew)
	ON_BN_CLICKED(IDC_BTN_CAM_EDT, OnBnClickedBtnCamEdt)
	ON_BN_CLICKED(IDC_BTN_CAM_DEL, OnBnClickedBtnCamDel)
	ON_BN_CLICKED(IDC_BTN_CAM_UP, OnBnClickedBtnCamUp)
	ON_BN_CLICKED(IDC_BTN_CAM_DN, OnBnClickedBtnCamDn)
	ON_BN_CLICKED(IDC_BTN_CHIUDI, OnBnClickedBtnChiudi)

END_MESSAGE_MAP()

void CMalattieCronicheDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_MALATTIE, m_ctrlListMalattie);
	DDX_Control(pDX, IDC_LIST_CAMPI, m_ctrlListCampi);

	DDX_Control(pDX, IDC_BTN_MAL_NEW, m_ctrlBtnMalNew);
	DDX_Control(pDX, IDC_BTN_MAL_EDT, m_ctrlBtnMalEdt);
	DDX_Control(pDX, IDC_BTN_MAL_DEL, m_ctrlBtnMalDel);
	DDX_Control(pDX, IDC_BTN_CAM_NEW, m_ctrlBtnCamNew);
	DDX_Control(pDX, IDC_BTN_CAM_EDT, m_ctrlBtnCamEdt);
	DDX_Control(pDX, IDC_BTN_CAM_DEL, m_ctrlBtnCamDel);
	DDX_Control(pDX, IDC_BTN_CAM_UP, m_ctrlBtnCamUp);
	DDX_Control(pDX, IDC_BTN_CAM_DN, m_ctrlBtnCamDn);
	DDX_Control(pDX, IDC_BTN_CHIUDI, m_ctrlBtnChiudi);
}

void CMalattieCronicheDlg::OnCancel()
{
}

BOOL CMalattieCronicheDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	m_ctrlListMalattie.SetExtendedStyle(m_ctrlListMalattie.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListMalattie.InsertColumn(0, "Malattie croniche");
	m_ctrlListMalattie.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	//

	m_ctrlListCampi.SetExtendedStyle(m_ctrlListCampi.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListCampi.InsertColumn(0, "Campo");
	m_ctrlListCampi.InsertColumn(1, "Tipo");
	m_ctrlListCampi.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListCampi.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	//

	RiempiListaMalattie(0);

	//

	theApp.LocalizeDialog(this, CMalattieCronicheDlg::IDD, "MalattieCronicheDlg");
	return TRUE;
}

void CMalattieCronicheDlg::OnOK()
{
}

void CMalattieCronicheDlg::RiempiListaMalattie(long lIDToSel)
{
	BeginWaitCursor();
	m_ctrlListMalattie.SetRedraw(FALSE);
	m_ctrlListMalattie.DeleteAllItems();

	CMalattieCronicheSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CMalattieCronicheDlg::RiempiListaMalattie"))
	{
		int nIndex = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlListMalattie.InsertItem(nIndex, setTemp.m_sDescrizione);
			m_ctrlListMalattie.SetItemData(nIndex, setTemp.m_lID);

			if (setTemp.m_lID == lIDToSel)
				m_ctrlListMalattie.SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMalattieCronicheDlg::RiempiListaMalattie");
	}

	m_ctrlListMalattie.SetRedraw(TRUE);
	EndWaitCursor();
}

void CMalattieCronicheDlg::RiempiListaCampi(long lIDToSel)
{
	BeginWaitCursor();
	m_ctrlListCampi.SetRedraw(FALSE);
	m_ctrlListCampi.DeleteAllItems();

	int nIndexToSel = -1;

	POSITION pos = m_ctrlListMalattie.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSelTemp = m_ctrlListMalattie.GetNextSelectedItem(pos);

		if (nCurSelTemp >= 0)
		{
			CString sFilter;
			sFilter.Format("IDMalattia=%li", m_ctrlListMalattie.GetItemData(nCurSelTemp));

			CMalattieCronicheCampiSet setTemp;
			setTemp.SetOpenFilter(sFilter);
			setTemp.SetSortRecord("Ordine, ID");
			if (setTemp.OpenRecordset("CMalattieCronicheDlg::RiempiListaCampi"))
			{
				int nIndex = 0;

				while(!setTemp.IsEOF())
				{
					switch(setTemp.m_lTipoCampo)
					{
						case TIPOCAMPO_LIBERO:
						{
							CString sToAdd = "";

							if (((setTemp.m_lIDCampo >= edt_libero000) && (setTemp.m_lIDCampo <= edt_libero099)) || ((setTemp.m_lIDCampo >= edt_liberodataora000) && (setTemp.m_lIDCampo <= edt_liberodataora019)))
								if (g_FormCaract[setTemp.m_lIDCampo].bEndox && !g_FormCaract[setTemp.m_lIDCampo].sDescrizione.Trim().IsEmpty())
									sToAdd = g_FormCaract[setTemp.m_lIDCampo].sDescrizione + GetStringCampoLiberoDatabase(setTemp.m_lIDCampo);

							if (!sToAdd.IsEmpty())
							{
								m_ctrlListCampi.InsertItem(nIndex, sToAdd);
								m_ctrlListCampi.SetItemData(nIndex, setTemp.m_lID);

								m_ctrlListCampi.SetItemText(nIndex, 1, theApp.GetMessageString(IDS_TIPOCAMPO_LIBERO));

								if (setTemp.m_lID == lIDToSel)
									nIndexToSel = nIndex;

								nIndex++;
							}

							break;
						}
						case TIPOCAMPO_SCORE:
						{
							switch(setTemp.m_lIDCampo)
							{
								case EDT_PAZIENTICRONICI_SCORE_HB:
								{
									m_ctrlListCampi.InsertItem(nIndex, theApp.GetMessageString(IDS_SCORE_HB));
									m_ctrlListCampi.SetItemData(nIndex, setTemp.m_lID);

									m_ctrlListCampi.SetItemText(nIndex, 1, theApp.GetMessageString(IDS_TIPOCAMPO_SCORE));

									if (setTemp.m_lID == lIDToSel)
										nIndexToSel = nIndex;

									nIndex++;

									break;
								}
								case EDT_PAZIENTICRONICI_SCORE_S:
								{
									m_ctrlListCampi.InsertItem(nIndex, theApp.GetMessageString(IDS_SCORE_S));
									m_ctrlListCampi.SetItemData(nIndex, setTemp.m_lID);

									m_ctrlListCampi.SetItemText(nIndex, 1, theApp.GetMessageString(IDS_TIPOCAMPO_SCORE));

									if (setTemp.m_lID == lIDToSel)
										nIndexToSel = nIndex;

									nIndex++;

									break;
								}
								default:
								{
									ASSERT(FALSE);
									break;
								}
							}

							break;
						}
						case TIPOCAMPO_FARMACO:
						{
							m_ctrlListCampi.InsertItem(nIndex, CFarmaciPazientiCroniciSet().GetDescrizione(setTemp.m_lIDCampo));
							m_ctrlListCampi.SetItemData(nIndex, setTemp.m_lID);

							m_ctrlListCampi.SetItemText(nIndex, 1, theApp.GetMessageString(IDS_TIPOCAMPO_FARMACO));

							if (setTemp.m_lID == lIDToSel)
								nIndexToSel = nIndex;

							nIndex++;

							break;
						}
						default:
						{
							ASSERT(FALSE);
							break;
						}
					}

					setTemp.MoveNext();
				}

				setTemp.CloseRecordset("CMalattieCronicheDlg::RiempiListaCampi");
			}
		}
	}

	m_ctrlListCampi.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListCampi.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	if (nIndexToSel >= 0)
	{
		m_ctrlListCampi.SetItemState(nIndexToSel, LVIS_SELECTED, LVIS_SELECTED);
		m_ctrlListCampi.EnsureVisible(nIndexToSel, FALSE);
	}

	m_ctrlListCampi.SetRedraw(TRUE);
	EndWaitCursor();
}

void CMalattieCronicheDlg::OnLvnItemchangedListMalattie(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListMalattie.GetFirstSelectedItemPosition();

	m_ctrlBtnMalEdt.EnableWindow(pos != NULL);
	m_ctrlBtnMalDel.EnableWindow(pos != NULL);
	m_ctrlBtnCamNew.EnableWindow(pos != NULL);

	RiempiListaCampi(0);
	OnLvnItemchangedListCampi(NULL, NULL);
}

void CMalattieCronicheDlg::OnLvnItemchangedListCampi(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListCampi.GetFirstSelectedItemPosition();

	m_ctrlBtnCamEdt.EnableWindow(pos != NULL);
	m_ctrlBtnCamDel.EnableWindow(pos != NULL);

	BOOL bEnableUp = FALSE;
	BOOL bEnableDn = FALSE;

	if (pos != NULL)
	{
		int nIndex = m_ctrlListCampi.GetNextSelectedItem(pos);

		bEnableUp = (nIndex > 0);
		bEnableDn = (nIndex < m_ctrlListCampi.GetItemCount() - 1);
	}

	m_ctrlBtnCamUp.EnableWindow(bEnableUp);
	m_ctrlBtnCamDn.EnableWindow(bEnableDn);
}

void CMalattieCronicheDlg::OnBnClickedBtnMalNew()
{
	CEditStringDlg dlg(this, IDS_MALATTIECRONICHE_TITLE_1, "");
	if (dlg.DoModal() == IDOK)
	{
		CMalattieCronicheSet setTemp;
		setTemp.SetOpenFilter("ID=0");
		if (setTemp.OpenRecordset("CMalattieCronicheDlg::OnBnClickedBtnMalNew"))
		{
			if (setTemp.AddNewRecordset("CMalattieCronicheDlg::OnBnClickedBtnMalNew"))
			{
				setTemp.m_sDescrizione = dlg.GetValue();

				if (setTemp.UpdateRecordset("CMalattieCronicheDlg::OnBnClickedBtnMalNew"))
					RiempiListaMalattie(setTemp.GetLastAdd());
			}

			setTemp.CloseRecordset("CMalattieCronicheDlg::OnBnClickedBtnMalNew");
		}
	}
}

void CMalattieCronicheDlg::OnBnClickedBtnMalEdt()
{
	POSITION pos = m_ctrlListMalattie.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListMalattie.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			CEditStringDlg dlg(this, IDS_MALATTIECRONICHE_TITLE_2, m_ctrlListMalattie.GetItemText(nIndex, 0));
			if (dlg.DoModal() == IDOK)
			{
				CString sFilter;
				sFilter.Format("ID=%li", m_ctrlListMalattie.GetItemData(nIndex));

				CMalattieCronicheSet setTemp;
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CMalattieCronicheDlg::OnBnClickedBtnMalEdt"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CMalattieCronicheDlg::OnBnClickedBtnMalEdt"))
						{
							setTemp.m_sDescrizione = dlg.GetValue();

							if (setTemp.UpdateRecordset("CMalattieCronicheDlg::OnBnClickedBtnMalEdt"))
								RiempiListaMalattie(m_ctrlListMalattie.GetItemData(nIndex));
						}
					}

					setTemp.CloseRecordset("CMalattieCronicheDlg::OnBnClickedBtnMalEdt");
				}
			}
		}
	}
}

void CMalattieCronicheDlg::OnBnClickedBtnMalDel()
{
	POSITION pos = m_ctrlListMalattie.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListMalattie.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			CString sMessage;
			sMessage.Format(theApp.GetMessageString(IDS_MALATTIECRONICHE_DELETE1), m_ctrlListMalattie.GetItemText(nIndex, 0).MakeUpper());

			if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO | MB_ICONSTOP) == IDYES)
			{
				CString sFilter;
				sFilter.Format("ID=%li", m_ctrlListMalattie.GetItemData(nIndex));

				CMalattieCronicheSet setTemp;
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CMalattieCronicheDlg::OnBnClickedBtnMalDel"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.DeleteRecordset("CMalattieCronicheDlg::OnBnClickedBtnMalDel"))
							RiempiListaMalattie(0);
					}

					setTemp.CloseRecordset("CMalattieCronicheDlg::OnBnClickedBtnMalDel");
				}
			}
		}
	}
}

void CMalattieCronicheDlg::OnBnClickedBtnCamNew()
{
	POSITION pos = m_ctrlListMalattie.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListMalattie.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			CComboDynCampoDlg dlg(this, IDS_MALATTIECRONICHE_TITLE_3, "");
			if (dlg.DoModal() == IDOK)
			{
				CMalattieCronicheCampiSet setTemp;
				setTemp.SetOpenFilter("ID=0");
				if (setTemp.OpenRecordset("CMalattieCronicheDlg::OnBnClickedBtnCamNew"))
				{
					if (setTemp.AddNewRecordset("CMalattieCronicheDlg::OnBnClickedBtnCamNew"))
					{
						setTemp.m_lIDMalattia = m_ctrlListMalattie.GetItemData(nIndex);
						setTemp.m_lIDCampo = dlg.GetIDCampo();
						setTemp.m_lTipoCampo = dlg.GetTipoCampo();
						setTemp.m_lOrdine = CMalattieCronicheCampiSet().GetNextOrdine(m_ctrlListMalattie.GetItemData(nIndex));

						if (setTemp.UpdateRecordset("CMalattieCronicheDlg::OnBnClickedBtnCamNew"))
							RiempiListaCampi(setTemp.GetLastAdd());
					}

					setTemp.CloseRecordset("CMalattieCronicheDlg::OnBnClickedBtnCamNew");
				}
			}
		}
	}
}

void CMalattieCronicheDlg::OnBnClickedBtnCamEdt()
{
	POSITION pos = m_ctrlListCampi.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListCampi.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			CComboDynCampoDlg dlg(this, IDS_MALATTIECRONICHE_TITLE_4, m_ctrlListCampi.GetItemText(nIndex, 0));
			if (dlg.DoModal() == IDOK)
			{
				CString sFilter;
				sFilter.Format("ID=%li", m_ctrlListCampi.GetItemData(nIndex));

				CMalattieCronicheCampiSet setTemp;
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CMalattieCronicheDlg::OnBnClickedBtnCamEdt"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CMalattieCronicheDlg::OnBnClickedBtnCamEdt"))
						{
							setTemp.m_lIDCampo = dlg.GetIDCampo();
							setTemp.m_lTipoCampo = dlg.GetTipoCampo();

							if (setTemp.UpdateRecordset("CMalattieCronicheDlg::OnBnClickedBtnCamEdt"))
								RiempiListaCampi(m_ctrlListCampi.GetItemData(nIndex));
						}
					}

					setTemp.CloseRecordset("CMalattieCronicheDlg::OnBnClickedBtnCamEdt");
				}
			}
		}
	}
}

void CMalattieCronicheDlg::OnBnClickedBtnCamDel()
{
	POSITION pos = m_ctrlListCampi.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListCampi.GetNextSelectedItem(pos);
		if (nIndex >= 0)
		{
			CString sMessage;
			sMessage.Format(theApp.GetMessageString(IDS_MALATTIECRONICHE_DELETE2), m_ctrlListCampi.GetItemText(nIndex, 0).MakeUpper());

			if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO | MB_ICONSTOP) == IDYES)
			{
				CString sFilter;
				sFilter.Format("ID=%li", m_ctrlListCampi.GetItemData(nIndex));

				CMalattieCronicheCampiSet setTemp;
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CMalattieCronicheDlg::OnBnClickedBtnCamDel"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.DeleteRecordset("CMalattieCronicheDlg::OnBnClickedBtnCamDel"))
							RiempiListaCampi(0);
					}

					setTemp.CloseRecordset("CMalattieCronicheDlg::OnBnClickedBtnCamDel");
				}
			}
		}
	}
}

void CMalattieCronicheDlg::OnBnClickedBtnCamUp()
{
	POSITION pos = m_ctrlListCampi.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListCampi.GetNextSelectedItem(pos);
		if (nIndex > 0)
		{
			//
			BeginWaitCursor();

			// metto da parte l'ID della riga da selezionare //
			long lIDUp = m_ctrlListCampi.GetItemData(nIndex);

			// scambio l'ID delle due righe adiacenti //
			long lTemp = (long)m_ctrlListCampi.GetItemData(nIndex - 1);
			m_ctrlListCampi.SetItemData(nIndex - 1, m_ctrlListCampi.GetItemData(nIndex));
			m_ctrlListCampi.SetItemData(nIndex, (DWORD)lTemp);

			// ri-salvo l'ordine per tutte le righe //
			for(int i = 0; i < m_ctrlListCampi.GetItemCount(); i++)
				CMalattieCronicheCampiSet().SetOrdine(m_ctrlListCampi.GetItemData(i), i);

			// ri-riempio la lista //
			RiempiListaCampi(lIDUp);

			//
			EndWaitCursor();
		}
	}
}

void CMalattieCronicheDlg::OnBnClickedBtnCamDn()
{
	POSITION pos = m_ctrlListCampi.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_ctrlListCampi.GetNextSelectedItem(pos);
		if ((nIndex > 0) && (nIndex < m_ctrlListCampi.GetItemCount() - 1))
		{
			//
			BeginWaitCursor();

			// metto da parte l'ID della riga da selezionare //
			long lIDDn = m_ctrlListCampi.GetItemData(nIndex);

			// scambio l'ID delle due righe adiacenti //
			long lTemp = (long)m_ctrlListCampi.GetItemData(nIndex + 1);
			m_ctrlListCampi.SetItemData(nIndex + 1, m_ctrlListCampi.GetItemData(nIndex));
			m_ctrlListCampi.SetItemData(nIndex, (DWORD)lTemp);

			// ri-salvo l'ordine per tutte le righe //
			for(int i = 0; i < m_ctrlListCampi.GetItemCount(); i++)
				CMalattieCronicheCampiSet().SetOrdine(m_ctrlListCampi.GetItemData(i), i);

			// ri-riempio la lista //
			RiempiListaCampi(lIDDn);

			//
			EndWaitCursor();
		}
	}
}

void CMalattieCronicheDlg::OnBnClickedBtnChiudi()
{
	CDialog::OnOK();
}
