#include "stdafx.h"
#include "Endox.h"
#include "EtichetteCondConfigDlg.h"

#include "EtichetteSet.h"
#include "ComboBoxSet.h"
#include "EtichetteCondizionateConfigSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEtichetteCondConfigDlg, CDialog)

CEtichetteCondConfigDlg::CEtichetteCondConfigDlg(CWnd* pParent, long idCondizionato, long idRelazionato, conditionalType tipoCondizionato)
: CDialog(CEtichetteCondConfigDlg::IDD, pParent), m_ctrlList(TRUE, FALSE, FALSE)
{
	CString sFilter;
	sFilter.Format("CONTATORE=%li", idRelazionato);
	CEtichetteSet set;
	set.SetOpenFilter(sFilter);
	if (set.OpenRecordset("CEtichetteCondConfigDlg::CEtichetteCondConfigDlg"))
	{
		if (!set.IsEOF())
		{
			m_iIndexRelazionato = set.m_lIndice;
			m_sDescrizioneRelazionato = set.m_sLabel;
		}

		set.CloseRecordset("CEtichetteCondConfigDlg::CEtichetteCondConfigDlg");
	}
	
	sFilter.Format("CONTATORE=%li", idCondizionato);
	set.SetOpenFilter(sFilter);
	if (set.OpenRecordset("CEtichetteCondConfigDlg::CEtichetteCondConfigDlg"))
	{
		if (!set.IsEOF())
		{
			m_iIndexCondizionato = set.m_lIndice;
			m_sDescrizioneCondizionato = set.m_sLabel;
		}

		set.CloseRecordset("CEtichetteCondConfigDlg::CEtichetteCondConfigDlg");
	}			

	m_lIdCondizionato = idCondizionato;
	m_lIdRelazionato = idRelazionato;
	m_tipoCondizionato = tipoCondizionato;
}


CEtichetteCondConfigDlg::~CEtichetteCondConfigDlg()
{
}

BEGIN_MESSAGE_MAP(CEtichetteCondConfigDlg, CDialog)
	ON_WM_DESTROY()

	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_ADD, &CEtichetteCondConfigDlg::OnBnClickedAdd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CEtichetteCondConfigDlg::OnLvnItemchangedList)
	ON_BN_CLICKED(IDC_DEL, &CEtichetteCondConfigDlg::OnBnClickedDel)
END_MESSAGE_MAP()


void CEtichetteCondConfigDlg::OnDestroy()
{
	CDialog::OnDestroy();
}

void CEtichetteCondConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_ADD, m_ctrlBtnAggiungi);
	DDX_Control(pDX, IDC_DEL, m_ctrlBtnRimuovi);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
}

BOOL CEtichetteCondConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.InsertColumn(0, m_sDescrizioneRelazionato);
	m_ctrlList.InsertColumn(1, m_sDescrizioneCondizionato);
	
	CComboBoxSet set(CMB_ESA_LIBERO000 + m_iIndexRelazionato);
	if (set.OpenRecordset("CEtichetteCondConfigDlg::OnInitDialog"))
	{
		while (!set.IsEOF())
		{
			tagLISTCOMBO tempTag;
			tempTag.lID = set.m_lContatore;
			tempTag.strName = set.m_sTesto;

			m_strIdList.AddTail(tempTag);

			set.MoveNext();
		}

		set.CloseRecordset("CEtichetteCondConfigDlg::OnInitDialog");
	}

	if (m_tipoCondizionato == conditionalType::combo)
	{
		CComboBoxSet set2(CMB_ESA_LIBERO000 + m_iIndexCondizionato);
		if (set2.OpenRecordset("CEtichetteCondConfigDlg::OnInitDialog"))
		{
			while (!set2.IsEOF())
			{
				tagLISTCOMBO tempTag;
				tempTag.lID = set2.m_lContatore;
				tempTag.strName = set2.m_sTesto;

				m_strIdListCondizionato.AddTail(tempTag);

				set2.MoveNext();
			}

			set2.CloseRecordset("CEtichetteCondConfigDlg::OnInitDialog");
		}
	}

	//Carico gli eventuali valori
	CString sFilter;
	sFilter.Format("IDCAMPOCONDIZIONATO=%li", m_lIdCondizionato);
	CEtichetteCondizionateConfigSet set3;
	set3.SetOpenFilter(sFilter);
	if (set3.OpenRecordset("CEtichetteCondConfigDlg::OnInitDialog"))
	{
		while (!set3.IsEOF())
		{
			int index = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), "");
			m_ctrlList.SetSubItemCombo(index, 0, m_strIdList);			
			m_ctrlList.SetSubItemData(index, 0, set3.m_lIDScelta);

			if (m_tipoCondizionato == conditionalType::combo)
			{
				m_ctrlList.SetSubItemCombo(index, 1, m_strIdListCondizionato);
				m_ctrlList.SetSubItemData(index, 1, set3.m_lIDRisultato);
			}
			else
			{
				m_ctrlList.SetSubItemEdit(index, 1);
				m_ctrlList.SetItemText(index, 1, set3.m_sRisultatoTxt);
			}			

			set3.MoveNext();
		}

		set3.CloseRecordset("CEtichetteCondConfigDlg::OnInitDialog");
	}

	//

	for (int i = 0; i < 2; i++)
		m_ctrlList.SetColumnWidth(i, 400);

	return TRUE;
}

void CEtichetteCondConfigDlg::OnBnClickedCancel()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANNULLA_MODIFICHE), MB_YESNO) == IDNO)
		return;

	CDialog::OnCancel();
}


void CEtichetteCondConfigDlg::OnBnClickedOk()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONFIRM), MB_YESNO) == IDNO)
		return;

	//Cancello i record esistenti
	CString sFilter;
	sFilter.Format("IDCAMPOCONDIZIONATO=%li", m_lIdCondizionato);
	CEtichetteCondizionateConfigSet set;
	set.SetOpenFilter(sFilter);
	if (set.OpenRecordset("CEtichetteCondConfigDlg::OnBnClickedOk"))
	{
		while (!set.IsEOF())
		{
			set.DeleteRecordset("CEtichetteCondConfigDlg::OnBnClickedOk");

			set.MoveNext();
		}

		set.CloseRecordset("CEtichetteCondConfigDlg::OnBnClickedOk");
	}

	//Inserisco quelli nuovi
	CEtichetteCondizionateConfigSet set2;	
	if (set2.OpenRecordset("CEtichetteCondConfigDlg::OnBnClickedOk"))
	{
		for (int i = 0; i < m_ctrlList.GetItemCount(); i++)
		{
			if (set2.AddNewRecordset("CEtichetteCondConfigDlg::OnBnClickedOk"))
			{
				set2.m_lIDCampoCondizionato = m_lIdCondizionato;
				set2.m_lIDScelta = m_ctrlList.GetSubItemData(i, 0);
				
				if (m_tipoCondizionato == conditionalType::combo)
					set2.m_lIDRisultato = m_ctrlList.GetSubItemData(i, 1);
				else
					set2.m_sRisultatoTxt = m_ctrlList.GetItemText(i, 1);

				set2.UpdateRecordset("CEtichetteCondConfigDlg::OnBnClickedOk");
			}
		}

		set2.CloseRecordset("CEtichetteCondConfigDlg::OnBnClickedOk");
	}

	CDialog::OnOK();
}


void CEtichetteCondConfigDlg::OnBnClickedAdd()
{
	int index = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), "");
	m_ctrlList.SetSubItemCombo(index, 0, m_strIdList);

	switch (m_tipoCondizionato)
	{
		case conditionalType::combo:
			m_ctrlList.SetSubItemCombo(index, 1, m_strIdListCondizionato);
			break;
		case conditionalType::text:
			m_ctrlList.SetSubItemEdit(index, 1);
			break;
		case conditionalType::numeric:
			m_ctrlList.SetSubItemEdit(index, 1, TRUE);
			break;
	}

	//Apro la combo appena inserita altrimenti l'utente non ha alcun riscontro sulla nuova riga
	CRect rect;
	m_ctrlList.GetSubItemRect(index, 1, LVIR_LABEL, rect);
	m_ctrlList.PostMessage(WM_LBUTTONDOWN, 0, MAKELPARAM((rect.right + rect.left) / 2, (rect.bottom + rect.top) / 2));

}


void CEtichetteCondConfigDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos)
		m_ctrlBtnRimuovi.EnableWindow(TRUE);
	else
		m_ctrlBtnRimuovi.EnableWindow(FALSE);

	*pResult = 0;
}


void CEtichetteCondConfigDlg::OnBnClickedDel()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = m_ctrlList.GetNextSelectedItem(pos);
		m_ctrlList.DeleteItem(index);
		m_ctrlBtnRimuovi.EnableWindow(FALSE);
	}
}
