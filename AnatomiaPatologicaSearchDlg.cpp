#include "stdafx.h"
#include "Endox.h"
#include "AnatomiaPatologicaSearchDlg.h"

#include "VistaSnomedSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAnatomiaPatologicaSearchDlg, CDialog)

CAnatomiaPatologicaSearchDlg::CAnatomiaPatologicaSearchDlg(CWnd* pParent, CListCtrl* pListCtrl)
	: CDialog(CAnatomiaPatologicaSearchDlg::IDD, pParent)
{
	ASSERT(pListCtrl != NULL);

	m_pListCtrl = pListCtrl;
}

CAnatomiaPatologicaSearchDlg::~CAnatomiaPatologicaSearchDlg()
{
}

BEGIN_MESSAGE_MAP(CAnatomiaPatologicaSearchDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_CODICE, OnCbnSelchangeComboCodice)
	ON_CBN_SELCHANGE(IDC_COMBO_DESCRIZIONE, OnCbnSelchangeComboDescrizione)

	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CAnatomiaPatologicaSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_CODICE, m_ctrlComboCodice);
	DDX_Control(pDX, IDC_COMBO_DESCRIZIONE, m_ctrlComboDescrizione);
}

BOOL CAnatomiaPatologicaSearchDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	RiempiComboCodice();
	RiempiComboDescrizione();

	return bReturn;
}

void CAnatomiaPatologicaSearchDlg::OnOK()
{
	int nIndex;
	char* szCodice = NULL;
	char* szDescrizione = NULL;
	
	nIndex = m_ctrlComboCodice.GetCurSel();
	if (nIndex >= 0)
		szCodice = (char*)m_ctrlComboCodice.GetItemData(nIndex);

	nIndex = m_ctrlComboDescrizione.GetCurSel();
	if (nIndex >= 0)
		szDescrizione = (char*)m_ctrlComboDescrizione.GetItemData(nIndex);

	if (strcmp(szCodice, szDescrizione) == 0)
	{
		CString strFilter;
		strFilter.Format("Codice='%s'", szCodice);

		CVistaSnomedSet setSnomed;
		setSnomed.SetOpenFilter(strFilter);
		if (setSnomed.OpenRecordset("CAnatomiaPatologicaSearchDlg::OnOK"))
		{
			if (!setSnomed.IsEOF())
			{
				int nNewItem = m_pListCtrl->GetItemCount();
				m_pListCtrl->InsertItem(nNewItem, setSnomed.m_sCodice);
				m_pListCtrl->SetItemText(nNewItem, 1, setSnomed.m_sDescrizione);
			}

			setSnomed.CloseRecordset("CAnatomiaPatologicaSearchDlg::OnOK");
		}
	}

	CDialog::OnOK();
}

void CAnatomiaPatologicaSearchDlg::OnCbnSelchangeComboCodice()
{
	int nIndexToSelect = -1;

	int nIndex = m_ctrlComboCodice.GetCurSel();
	if (nIndex >= 0)
	{
		char* szCodice = (char*)m_ctrlComboCodice.GetItemData(nIndex);

		for(int i = 0; i < m_ctrlComboDescrizione.GetCount(); i++)
		{
			char* szDescrizione = (char*)m_ctrlComboDescrizione.GetItemData(i);

			if (strcmp(szCodice, szDescrizione) == 0)
			{
				nIndexToSelect = i;
				break;
			}
		}
	}

	m_ctrlComboDescrizione.SetCurSel(nIndexToSelect);
}

void CAnatomiaPatologicaSearchDlg::OnCbnSelchangeComboDescrizione()
{
	int nIndexToSelect = -1;

	int nIndex = m_ctrlComboDescrizione.GetCurSel();
	if (nIndex >= 0)
	{
		char* szDescrizione = (char*)m_ctrlComboDescrizione.GetItemData(nIndex);

		for(int i = 0; i < m_ctrlComboCodice.GetCount(); i++)
		{
			char* szCodice = (char*)m_ctrlComboCodice.GetItemData(i);

			if (strcmp(szDescrizione, szCodice) == 0)
			{
				nIndexToSelect = i;
				break;
			}
		}
	}

	m_ctrlComboCodice.SetCurSel(nIndexToSelect);
}

void CAnatomiaPatologicaSearchDlg::OnDestroy()
{
	ResetContentCodice();
	ResetContentDescrizione();

	CDialog::OnDestroy();
}

void CAnatomiaPatologicaSearchDlg::ResetContentCodice()
{
	for(int i = 0; i < m_ctrlComboCodice.GetCount(); i++)
	{
		char* szTemp = (char*)m_ctrlComboCodice.GetItemData(i);
		delete szTemp;
	}

	m_ctrlComboCodice.ResetContent();
}

void CAnatomiaPatologicaSearchDlg::ResetContentDescrizione()
{
	for(int i = 0; i < m_ctrlComboDescrizione.GetCount(); i++)
	{
		char* szTemp = (char*)m_ctrlComboDescrizione.GetItemData(i);
		delete szTemp;
	}

	m_ctrlComboDescrizione.ResetContent();
}

void CAnatomiaPatologicaSearchDlg::RiempiComboCodice()
{
	CVistaSnomedSet setTemp;

	ResetContentCodice();

	setTemp.SetSortRecord("Codice");
	if (setTemp.OpenRecordset("CAnatomiaPatologicaSearchDlg::RiempiComboCodice"))
	{
		int nIndex = 0;
		while(!setTemp.IsEOF())
		{
			CString strTemp = setTemp.m_sCodice + " " + setTemp.m_sDescrizione;
			strTemp.Trim();

			char* szTemp = new char[11];
			ZeroMemory(szTemp, sizeof(char) * 11);
			memcpy(szTemp, setTemp.m_sCodice.GetBuffer(), 10);

			m_ctrlComboCodice.InsertString(nIndex, strTemp);
			m_ctrlComboCodice.SetItemData(nIndex, (DWORD)szTemp);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAnatomiaPatologicaSearchDlg::RiempiComboCodice");
	}
}

void CAnatomiaPatologicaSearchDlg::RiempiComboDescrizione()
{
	CVistaSnomedSet setTemp;

	ResetContentDescrizione();

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CAnatomiaPatologicaSearchDlg::RiempiComboDescrizione"))
	{
		int nIndex = 0;
		while(!setTemp.IsEOF())
		{
			CString strTemp = setTemp.m_sDescrizione + " (" + setTemp.m_sCodice + ")";
			strTemp.Trim();

			char* szTemp = new char[11];
			ZeroMemory(szTemp, sizeof(char) * 11);
			memcpy(szTemp, setTemp.m_sCodice.GetBuffer(), 10);

			m_ctrlComboDescrizione.InsertString(nIndex, strTemp);
			m_ctrlComboDescrizione.SetItemData(nIndex, (DWORD)szTemp);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAnatomiaPatologicaSearchDlg::RiempiComboDescrizione");
	}
}