#include "stdafx.h"
#include "Endox.h"
#include "organisedidiagnosiusedlg.h"
#include "TipiEsamiOrganiSet.h"
#include "MstOrganoSet.h"
#include "EsamiSet.h"
#include "SedeSet.h"
#include "mstdiagnosiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COrganiSediDiagnosiUseDlg, CDialog)

COrganiSediDiagnosiUseDlg::COrganiSediDiagnosiUseDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(COrganiSediDiagnosiUseDlg::IDD, pParent)
{
	// ASSERT(pEsamiView != NULL); Sandro //

	m_pEsamiView = pEsamiView;

	m_strOrgano = "";
	m_strSede = "";
	m_strDiagnosi = "";
}

BEGIN_MESSAGE_MAP(COrganiSediDiagnosiUseDlg, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST_ORGANI, OnLbnSelchangeListOrgani)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_DESELEZIONA, OnBnClickedBtnDeseleziona)
	ON_LBN_SELCHANGE(IDC_LIST_DIAGNOSI, &COrganiSediDiagnosiUseDlg::OnLbnSelchangeListDiagnosi)
	ON_LBN_SELCHANGE(IDC_LIST_CARATT1, &COrganiSediDiagnosiUseDlg::OnLbnSelchangeListCaratt1)
	ON_LBN_SELCHANGE(IDC_LIST_CARATT2, &COrganiSediDiagnosiUseDlg::OnLbnSelchangeListCaratt2)
	ON_LBN_SELCHANGE(IDC_LIST_CARATT3, &COrganiSediDiagnosiUseDlg::OnLbnSelchangeListCaratt3)
	ON_LBN_SELCHANGE(IDC_LIST_CARATT4, &COrganiSediDiagnosiUseDlg::OnLbnSelchangeListCaratt4)
	ON_LBN_SELCHANGE(IDC_LIST_CARATT5, &COrganiSediDiagnosiUseDlg::OnLbnSelchangeListCaratt5)
	ON_LBN_SELCHANGE(IDC_LIST_CARATT6, &COrganiSediDiagnosiUseDlg::OnLbnSelchangeListCaratt6)
END_MESSAGE_MAP()

void COrganiSediDiagnosiUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_DESELEZIONA, m_ctrlButtonDelsel);
	DDX_Control(pDX, IDOK,                m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL,            m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_LIST_ORGANI, m_ctrlListOrgani);
	DDX_Control(pDX, IDC_TREE_SEDI, m_ctrlTreeSedi);
	DDX_Control(pDX, IDC_LIST_DIAGNOSI, m_ctrlListDiagnosi);
	DDX_Control(pDX, IDC_LIST_CARATT1, m_ctrlListCaratteristiche[0]);
	DDX_Control(pDX, IDC_LIST_CARATT2, m_ctrlListCaratteristiche[1]);
	DDX_Control(pDX, IDC_LIST_CARATT3, m_ctrlListCaratteristiche[2]);
	DDX_Control(pDX, IDC_LIST_CARATT4, m_ctrlListCaratteristiche[3]);
	DDX_Control(pDX, IDC_LIST_CARATT5, m_ctrlListCaratteristiche[4]);
	DDX_Control(pDX, IDC_LIST_CARATT6, m_ctrlListCaratteristiche[5]);
}

BOOL COrganiSediDiagnosiUseDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	RiempiListaOrgani();
	theApp.LocalizeDialog(this, COrganiSediDiagnosiUseDlg::IDD, "OrganiSediUseDlg");

	return bReturn;
}

void COrganiSediDiagnosiUseDlg::OnBnClickedOk()
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
		}

		int iDiagnosi = m_ctrlListDiagnosi.GetCurSel();
		if (iDiagnosi > -1)
			m_ctrlListDiagnosi.GetText(iDiagnosi, m_strDiagnosi);

		for(int index=0; index < 6; index++)
		{
			int i = m_ctrlListCaratteristiche[index].GetCurSel();
			if (i > -1)
			{
				CString temp;
				m_ctrlListCaratteristiche[index].GetText(i, temp);
				m_strDiagnosi.Append(", ");
				m_strDiagnosi.Append(temp);
			}
		}
	}

	OnOK();
}

void COrganiSediDiagnosiUseDlg::OnBnClickedBtnDeseleziona()
{
	m_ctrlListOrgani.SetCurSel(-1);
	OnLbnSelchangeListOrgani();
}

void COrganiSediDiagnosiUseDlg::OnLbnSelchangeListOrgani()
{
	int iTemp = m_ctrlListOrgani.GetCurSel();

	if (iTemp >= 0)
	{
		RiempiTreeSedi((long)m_ctrlListOrgani.GetItemData(iTemp));
		RiempiListaDiagnosi((long)m_ctrlListOrgani.GetItemData(iTemp));
	}
	else
	{
		RiempiTreeSedi(-1);
		RiempiListaDiagnosi(-1);
	}
}

void COrganiSediDiagnosiUseDlg::RiempiListaOrgani()
{
	CMstOrganoSet setOrgano;
	int iTemp;

	if (m_pEsamiView != NULL)
	{
		CString strTemp;

		CTipiEsamiOrganiSet setJoin;

		strTemp.Format("TipoEsame=%li", m_pEsamiView->m_pEsamiSet->m_lIDEsame);
		setJoin.SetOpenFilter(strTemp);

		if (setJoin.OpenRecordset("COrganiSediDiagnosiUseDlg::RiempiListaOrgani") == TRUE)
		{
			while(setJoin.IsEOF() == FALSE)
			{
				strTemp.Format("Contatore=%li", setJoin.m_lOrgano);
				setOrgano.SetOpenFilter(strTemp);

				if (setOrgano.OpenRecordset("COrganiSediDiagnosiUseDlg::RiempiListaOrgani") == TRUE)
				{
					if (setOrgano.IsEOF() == FALSE)
					{
						iTemp = m_ctrlListOrgani.AddString(setOrgano.m_sOrgano);
						m_ctrlListOrgani.SetItemData(iTemp, (DWORD)setOrgano.m_lContatore);
					}
				}

				setJoin.MoveNext();
			}

			setOrgano.CloseRecordset("COrganiSediDiagnosiUseDlg::RiempiListaOrgani");
			setJoin.CloseRecordset("COrganiSediDiagnosiUseDlg::RiempiListaOrgani");
		}
	}

	if (m_ctrlListOrgani.GetCount() == 0)
	{
		if (setOrgano.OpenRecordset("COrganiSediDiagnosiUseDlg::RiempiListaOrgani") == TRUE)
		{
			while(setOrgano.IsEOF() == FALSE)
			{
				iTemp = m_ctrlListOrgani.AddString(setOrgano.m_sOrgano);
				m_ctrlListOrgani.SetItemData(iTemp, (DWORD)setOrgano.m_lContatore);

				setOrgano.MoveNext();
			}

			setOrgano.CloseRecordset("COrganiSediDiagnosiUseDlg::RiempiListaOrgani");
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

void COrganiSediDiagnosiUseDlg::RiempiTreeSedi(long lOrgano)
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
	if (setTemp1.OpenRecordset("COrganiSediDiagnosiUseDlg::RiempiTreeSedi") == TRUE)
	{
		while(setTemp1.IsEOF() == FALSE)
		{
			hPadre = m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp1.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp1.m_lContatore, TVI_ROOT, TVI_LAST);

			if (m_strSede == setTemp1.m_sDescrizione)
				hFind = hPadre;

			strTemp.Format("Padre=%li", setTemp1.m_lContatore);
			setTemp2.SetOpenFilter(strTemp);
			if (setTemp2.OpenRecordset("COrganiSediDiagnosiUseDlg::RiempiTreeSedi") == TRUE)
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

		setTemp2.CloseRecordset("COrganiSediDiagnosiUseDlg::RiempiTreeSedi");
		setTemp1.CloseRecordset("COrganiSediDiagnosiUseDlg::RiempiTreeSedi");
	}

	// mi serve per fare lo scroll e riportare la lista sopra, all'inizio //
	hPadre = m_ctrlTreeSedi.GetRootItem();
	if (hPadre != NULL)
	{
		m_ctrlTreeSedi.SelectItem(hPadre);
		//m_ctrlTreeSedi.SelectItem(hFind);
	}

	m_strSede = "";
}

void COrganiSediDiagnosiUseDlg::RiempiListaDiagnosi(long lOrgano)
{
	CString strTemp;
	strTemp.Format("Organo=%li and Padre=0", lOrgano);

	m_ctrlListDiagnosi.ResetContent();

	CMstDiagnosiSet setTemp1;
	setTemp1.SetSortRecord("Descrizione");

	setTemp1.SetBaseFilter(strTemp);
	if (setTemp1.OpenRecordset("COrganiSediDiagnosiUseDlg::RiempiListaDiagnosi") == TRUE)
	{
		int index = 0;
		while(setTemp1.IsEOF() == FALSE)
		{
			//hPadre = m_ctrlListDiagnosi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp1.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp1.m_lContatore, TVI_ROOT, TVI_LAST);
			int i = m_ctrlListDiagnosi.InsertString(index, setTemp1.m_sDescrizione);
			m_ctrlListDiagnosi.SetItemData(i, setTemp1.m_lContatore);
			index++;
			setTemp1.MoveNext();
		}

		setTemp1.CloseRecordset("COrganiSediDiagnosiUseDlg::RiempiListaDiagnosi");
	}

	// mi serve per fare lo scroll e riportare la lista sopra, all'inizio //
	m_ctrlListDiagnosi.SetCurSel(-1);
	m_strDiagnosi = "";

	RiempiListaCaratteristiche(-1,-1);
}


CString COrganiSediDiagnosiUseDlg::GetOrgano()
{
	return m_strOrgano;
}

CString COrganiSediDiagnosiUseDlg::GetSede()
{
	return m_strSede;
}

CString COrganiSediDiagnosiUseDlg::GetDiagnosi()
{
	return m_strDiagnosi;
}

void COrganiSediDiagnosiUseDlg::SetOrgano(CString strOrgano)
{
	m_strOrgano = strOrgano;
}

void COrganiSediDiagnosiUseDlg::SetSede(CString strSede)
{
	m_strSede = strSede;
}

void COrganiSediDiagnosiUseDlg::SetDiagnosi(CString strDiagnosi)
{
	m_strDiagnosi = strDiagnosi;
}

void COrganiSediDiagnosiUseDlg::OnLbnSelchangeListDiagnosi()
{
	int organoSel = m_ctrlListOrgani.GetItemData(m_ctrlListOrgani.GetCurSel());
	int diagnosiSel = m_ctrlListDiagnosi.GetItemData(m_ctrlListDiagnosi.GetCurSel());
	RiempiListaCaratteristiche(organoSel, diagnosiSel);
}

void COrganiSediDiagnosiUseDlg::RiempiListaCaratteristiche(long lOrgano, long lDiagnosi)
{
	for(int lLivello=1; lLivello<=6; lLivello++)
	{
		m_ctrlListCaratteristiche[lLivello-1].ResetContent();
		m_selPrecCaratt[lLivello-1] = -1;

		if (lOrgano > -1 && lDiagnosi > -1)
		{
			CString strTemp;
			strTemp.Format("Organo=%li and Padre=%li and Livello = %li", lOrgano, lDiagnosi, lLivello);

			CMstDiagnosiSet setTemp1;
			setTemp1.SetSortRecord("Descrizione");

			setTemp1.SetBaseFilter(strTemp);
			if (setTemp1.OpenRecordset("COrganiSediDiagnosiUseDlg::RiempiListaCaratteristiche") == TRUE)
			{
				int index = 0;
				while(setTemp1.IsEOF() == FALSE)
				{
					//hPadre = m_ctrlListDiagnosi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp1.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp1.m_lContatore, TVI_ROOT, TVI_LAST);
					m_ctrlListCaratteristiche[lLivello-1].InsertString(index, setTemp1.m_sDescrizione);
					index++;
					setTemp1.MoveNext();
				}

				setTemp1.CloseRecordset("COrganiSediDiagnosiUseDlg::RiempiListaCaratteristiche");
			}
		}
	}
}
void COrganiSediDiagnosiUseDlg::OnLbnSelchangeListCaratt1()
{
	if (m_ctrlListCaratteristiche[0].GetCurSel() == m_selPrecCaratt[0])
	{
		m_ctrlListCaratteristiche[0].SetCurSel(-1);
		m_selPrecCaratt[0] = -1;
	}
	else
		m_selPrecCaratt[0] = m_ctrlListCaratteristiche[0].GetCurSel();
	
}

void COrganiSediDiagnosiUseDlg::OnLbnSelchangeListCaratt2()
{
	if (m_ctrlListCaratteristiche[1].GetCurSel() == m_selPrecCaratt[1])
	{
		m_ctrlListCaratteristiche[1].SetCurSel(-1);
		m_selPrecCaratt[1] = -1;
	}
	else
		m_selPrecCaratt[1] = m_ctrlListCaratteristiche[1].GetCurSel();
}

void COrganiSediDiagnosiUseDlg::OnLbnSelchangeListCaratt3()
{
	if (m_ctrlListCaratteristiche[2].GetCurSel() == m_selPrecCaratt[2])
	{
		m_ctrlListCaratteristiche[2].SetCurSel(-1);
		m_selPrecCaratt[2] = -1;
	}
	else
		m_selPrecCaratt[2] = m_ctrlListCaratteristiche[2].GetCurSel();
}

void COrganiSediDiagnosiUseDlg::OnLbnSelchangeListCaratt4()
{
	if (m_ctrlListCaratteristiche[3].GetCurSel() == m_selPrecCaratt[3])
	{
		m_ctrlListCaratteristiche[3].SetCurSel(-1);
		m_selPrecCaratt[3] = -1;
	}
	else
		m_selPrecCaratt[3] = m_ctrlListCaratteristiche[3].GetCurSel();
}

void COrganiSediDiagnosiUseDlg::OnLbnSelchangeListCaratt5()
{
	if (m_ctrlListCaratteristiche[4].GetCurSel() == m_selPrecCaratt[4])
	{
		m_ctrlListCaratteristiche[4].SetCurSel(-1);
		m_selPrecCaratt[4] = -1;
	}
	else
		m_selPrecCaratt[4] = m_ctrlListCaratteristiche[4].GetCurSel();
}

void COrganiSediDiagnosiUseDlg::OnLbnSelchangeListCaratt6()
{
	if (m_ctrlListCaratteristiche[5].GetCurSel() == m_selPrecCaratt[5])
	{
		m_ctrlListCaratteristiche[5].SetCurSel(-1);
		m_selPrecCaratt[5] = -1;
	}
	else
		m_selPrecCaratt[5] = m_ctrlListCaratteristiche[5].GetCurSel();
}