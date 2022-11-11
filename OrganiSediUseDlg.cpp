#include "stdafx.h"
#include "Endox.h"
#include "OrganiSediUseDlg.h"
#include "TipiEsamiOrganiSet.h"
#include "MstOrganoSet.h"
#include "EsamiSet.h"
#include "SedeSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COrganiSediUseDlg, CDialog)

COrganiSediUseDlg::COrganiSediUseDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(COrganiSediUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_strOrgano = "";
	m_strSede = "";
}

BEGIN_MESSAGE_MAP(COrganiSediUseDlg, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST_ORGANI, OnLbnSelchangeListOrgani)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_DESELEZIONA, OnBnClickedBtnDeseleziona)
END_MESSAGE_MAP()

void COrganiSediUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_DESELEZIONA, m_ctrlButtonDelsel);
	DDX_Control(pDX, IDOK,                m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL,            m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_LIST_ORGANI, m_ctrlListOrgani);
	DDX_Control(pDX, IDC_TREE_SEDI, m_ctrlTreeSedi);
}

BOOL COrganiSediUseDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	RiempiListaOrgani();
	theApp.LocalizeDialog(this, COrganiSediUseDlg::IDD, "OrganiSediUseDlg");

	return bReturn;
}

void COrganiSediUseDlg::OnBnClickedOk()
{
	int iTemp = m_ctrlListOrgani.GetCurSel();

	m_strSede = "";

	if (iTemp >= 0)
	{
		HTREEITEM hSelez = m_ctrlTreeSedi.GetSelectedItem();

		m_ctrlListOrgani.GetText(iTemp, m_strOrgano);

		if (hSelez != NULL)
		{
			HTREEITEM hPadre = m_ctrlTreeSedi.GetParentItem(hSelez);

			if ((hPadre != NULL) && (hPadre != hSelez))
				m_strSede = m_ctrlTreeSedi.GetItemText(hPadre) + " " + m_ctrlTreeSedi.GetItemText(hSelez);
			else
				m_strSede = m_ctrlTreeSedi.GetItemText(hSelez);

			m_lIDSede = m_ctrlTreeSedi.GetItemData(hSelez);
		}
		else
			m_lIDSede = 0;
	}

	OnOK();
}

void COrganiSediUseDlg::OnBnClickedBtnDeseleziona()
{
	m_ctrlListOrgani.SetCurSel(-1);
	OnLbnSelchangeListOrgani();
}

void COrganiSediUseDlg::OnLbnSelchangeListOrgani()
{
	int iTemp = m_ctrlListOrgani.GetCurSel();

	if (iTemp >= 0)
		RiempiTreeSedi((long)m_ctrlListOrgani.GetItemData(iTemp));
	else
		RiempiTreeSedi(-1);
}

void COrganiSediUseDlg::RiempiListaOrgani()
{
	int iTemp;
	CString strTemp;
	CTipiEsamiOrganiSet setJoin;
	CMstOrganoSet setOrgano;
	
	strTemp.Format("TipoEsame=%li", m_pEsamiView->m_pEsamiSet->m_lIDEsame);
	setJoin.SetOpenFilter(strTemp);

	if (setJoin.OpenRecordset("COrganiSediUseDlg::RiempiListaOrgani") == TRUE)
	{
		while(setJoin.IsEOF() == FALSE)
		{
			strTemp.Format("Contatore=%li", setJoin.m_lOrgano);
			setOrgano.SetOpenFilter(strTemp);

			if (setOrgano.OpenRecordset("COrganiSediUseDlg::RiempiListaOrgani") == TRUE)
			{
				if (setOrgano.IsEOF() == FALSE)
				{
					iTemp = m_ctrlListOrgani.AddString(setOrgano.m_sOrgano);
					m_ctrlListOrgani.SetItemData(iTemp, (DWORD)setOrgano.m_lContatore);
				}
			}

			setJoin.MoveNext();
		}

		setOrgano.CloseRecordset("COrganiSediUseDlg::RiempiListaOrgani");
		setJoin.CloseRecordset("COrganiSediUseDlg::RiempiListaOrgani");
	}

	if (m_ctrlListOrgani.GetCount() == 0)
	{
		if (setOrgano.OpenRecordset("COrganiSediUseDlg::RiempiListaOrgani") == TRUE)
		{
			while(setOrgano.IsEOF() == FALSE)
			{
				iTemp = m_ctrlListOrgani.AddString(setOrgano.m_sOrgano);
				m_ctrlListOrgani.SetItemData(iTemp, (DWORD)setOrgano.m_lContatore);

				setOrgano.MoveNext();
			}

			setOrgano.CloseRecordset("COrganiSediUseDlg::RiempiListaOrgani");
		}
	}

	if (m_strOrgano.IsEmpty() == FALSE)
	{
		iTemp = m_ctrlListOrgani.FindStringExact(-1, m_strOrgano);

		if (iTemp >= 0)
			m_ctrlListOrgani.SetCurSel(iTemp);

		m_strOrgano = "";
	}
	else
	{
		m_ctrlListOrgani.SetCurSel(-1);
	}

	OnLbnSelchangeListOrgani();
}

void COrganiSediUseDlg::RiempiTreeSedi(long lOrgano)
{
	HTREEITEM hFind = NULL;
	HTREEITEM hFiglio;
	HTREEITEM hPadre;

	CString strTemp;
	strTemp.Format("Organo=%li and Padre=0", lOrgano);

	m_ctrlTreeSedi.DeleteAllItems();

	CMstSediSet setTemp1;
	setTemp1.SetSortRecord("Descrizione");

	CMstSediSet setTemp2;
	setTemp2.SetSortRecord("Descrizione");

	setTemp1.SetBaseFilter(strTemp);
	if (setTemp1.OpenRecordset("COrganiSediUseDlg::RiempiTreeSedi") == TRUE)
	{
		while(setTemp1.IsEOF() == FALSE)
		{
			hPadre = m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp1.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp1.m_lContatore, TVI_ROOT, TVI_LAST);

			if (m_strSede == setTemp1.m_sDescrizione)
				hFind = hPadre;

			strTemp.Format("Padre=%li", setTemp1.m_lContatore);
			setTemp2.SetOpenFilter(strTemp);
			if (setTemp2.OpenRecordset("COrganiSediUseDlg::RiempiTreeSedi") == TRUE)
			{
				while(setTemp2.IsEOF() == FALSE)
				{
					hFiglio = m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp2.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp2.m_lContatore, hPadre, TVI_LAST);

					if (m_strSede == setTemp1.m_sDescrizione + " " + setTemp2.m_sDescrizione)
						hFind = hFiglio;

					setTemp2.MoveNext();
				}
			}

			m_ctrlTreeSedi.Expand(hPadre, TVE_EXPAND);

			setTemp1.MoveNext();
		}

		setTemp2.CloseRecordset("COrganiSediUseDlg::RiempiTreeSedi");
		setTemp1.CloseRecordset("COrganiSediUseDlg::RiempiTreeSedi");
	}

	// mi serve per fare lo scroll e riportare la lista sopra, all'inizio //
	hPadre = m_ctrlTreeSedi.GetRootItem();
	if (hPadre != NULL)
	{
		m_ctrlTreeSedi.SelectItem(hPadre);
		m_ctrlTreeSedi.SelectItem(hFind);
	}

	m_strSede = "";
}

CString COrganiSediUseDlg::GetOrgano()
{
	return m_strOrgano;
}

CString COrganiSediUseDlg::GetSede()
{
	return m_strSede;
}

long COrganiSediUseDlg::GetIdSede()
{
	return m_lIDSede;
}

void COrganiSediUseDlg::SetOrgano(CString strOrgano)
{
	m_strOrgano = strOrgano;
}

void COrganiSediUseDlg::SetSede(CString strSede)
{
	m_strSede = strSede;
}