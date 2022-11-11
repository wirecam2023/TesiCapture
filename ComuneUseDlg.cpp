#include "stdafx.h"
#include "Endox.h"
#include "ComuneUseDlg.h"

#include "ComuniSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComuneUseDlg, CDialog)

CComuneUseDlg::CComuneUseDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CComuneUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_lIDComune = 0;
	m_strComune = "";
	m_strCAP = "";
	m_strProvincia = "";
}

BEGIN_MESSAGE_MAP(CComuneUseDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_DESELEZIONA, OnBnClickedBtnDeseleziona)
END_MESSAGE_MAP()

void CComuneUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_COMUNI, m_ctrlComboComuni);

	DDX_Control(pDX, IDC_BTN_DESELEZIONA, m_ctrlBtnDeseleziona);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
}

BOOL CComuneUseDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	CaricaComuni();

	theApp.LocalizeDialog(this, CComuneUseDlg::IDD, "ComuneUseDlg");
	return bReturn;
}

void CComuneUseDlg::OnBnClickedOk()
{
	m_lIDComune = 0;
	m_strComune = "";
	m_strCAP = "";
	m_strProvincia = "";

	int nItem = m_ctrlComboComuni.GetCurSel();
	if (nItem >= 0)
	{
		m_lIDComune = (long)m_ctrlComboComuni.GetItemData(nItem);

		CComuniSet setComuni;
		setComuni.GetFieldText(m_lIDComune, m_strComune, m_strCAP, m_strProvincia);
	}

	OnOK();
}

void CComuneUseDlg::CaricaComuni()
{
	int nIndex = 0;
	int nFind = -1;

	m_ctrlComboComuni.ShowWindow(SW_HIDE);
	m_ctrlComboComuni.ResetContent();

	POSITION pos = theApp.m_listComuni.GetHeadPosition();

	BeginWaitCursor();
	while(pos != NULL)
	{
		tagCOMUNI comune = theApp.m_listComuni.GetNext(pos);

		if (comune.m_sProvincia.GetLength() > 0)
			m_ctrlComboComuni.InsertString(nIndex, comune.m_sComune + " (" + comune.m_sProvincia + ")");
		else
			m_ctrlComboComuni.InsertString(nIndex, comune.m_sComune);
		m_ctrlComboComuni.SetItemData(nIndex, (DWORD)comune.m_lID);

		if ((nFind < 0) && (!m_strComune.IsEmpty()) && (strcmp(m_strComune, comune.m_sComune) == 0))
			nFind = nIndex;

		nIndex++;
	}
	EndWaitCursor();

	m_ctrlComboComuni.SetCurSel(nFind);
	m_ctrlComboComuni.ShowWindow(SW_SHOW);
}

long CComuneUseDlg::GetIDComune()
{
	return m_lIDComune;
}

CString CComuneUseDlg::GetComune()
{
	return m_strComune;
}

CString CComuneUseDlg::GetCAP()
{
	return m_strCAP;
}

CString CComuneUseDlg::GetProvincia()
{
	return m_strProvincia;
}

void CComuneUseDlg::SetIDComune(long lIDComune)
{
	m_lIDComune = lIDComune;

	if (m_lIDComune > 0)
	{
		CComuniSet setComuni;

		CString strFilter;
		strFilter.Format("ID=%li", lIDComune);

		setComuni.SetOpenFilter(strFilter);
		setComuni.SetSortRecord("ID");
		if (setComuni.OpenRecordset("CComuneUseDlg::SetIDComune"))
		{
			if (!setComuni.IsEOF())
			{
				m_strComune = setComuni.m_sComune;
				m_strCAP = setComuni.m_sCAP;
				m_strProvincia = setComuni.m_sProvincia;
			}

			setComuni.CloseRecordset("CComuneUseDlg::SetIDComune");
		}
	}
}
void CComuneUseDlg::OnBnClickedBtnDeseleziona()
{
	m_ctrlComboComuni.SetCurSel(-1);
}