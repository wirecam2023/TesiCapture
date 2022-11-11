#include "stdafx.h"
#include "Endox.h"
#include "StrumentiDlg.h"

#include "AddDescrDlg.h"
#include "EsamiView.h"
#include "SediEsameSet.h"
#include "StrumentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CStrumentiDlg::CStrumentiDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CStrumentiDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CStrumentiDlg::~CStrumentiDlg()
{
}

void CStrumentiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_STRUMENTI, m_ctrlListStrumenti);
	
	DDX_Control(pDX, IDCANCEL,     m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_NUOVO,    m_ctrlButtonNew);
	DDX_Control(pDX, IDC_MODIFICA, m_ctrlButtonModify);
	DDX_Control(pDX, IDC_ELIMINA,  m_ctrlButtonDelete);
}

BEGIN_MESSAGE_MAP(CStrumentiDlg, CDialog)
	ON_BN_CLICKED(IDC_ELIMINA, OnElimina)
	ON_BN_CLICKED(IDC_MODIFICA, OnModifica)
	ON_BN_CLICKED(IDC_NUOVO, OnNuovo)
END_MESSAGE_MAP()

BOOL CStrumentiDlg::OnInitDialog ()
{
	CDialog::OnInitDialog();

	CenterWindow();

	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold, TRUE);
	GetDlgItem(IDC_STATIC_1)->SetFont(&theApp.m_fontBold, TRUE);
	GetDlgItem(IDC_STATIC_2)->SetFont(&theApp.m_fontBold, TRUE);

	CString strSede = CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, FALSE);
	SetDlgItemText(IDC_STATIC_2, strSede);

	RiempiLista();

	theApp.LocalizeDialog(this, CStrumentiDlg::IDD, "StrumentiDlg");

	return TRUE;
}

void CStrumentiDlg::OnElimina()
{
	int nIndex = m_ctrlListStrumenti.GetCurSel();
	if (nIndex >= 0)
	{
		CString strTemp;
		m_ctrlListStrumenti.GetText(nIndex, strTemp);

		CString strString;
		strString.Format(theApp.GetMessageString(IDS_TABCOMBODLG_DELETE_CONFIRM), strTemp, "Strumenti");
		if (theApp.AfxMessageBoxEndo(strString, MB_YESNO) == IDYES)
		{
			CStrumentiSet setTemp;
			BOOL bOK = FALSE;

			CString strFilter;
			strFilter.Format("Contatore=%li", (long)m_ctrlListStrumenti.GetItemData(nIndex));

			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CStrumentiDlg::OnModifica"))
			{
				if (setTemp.DeleteRecordset("CStrumentiDlg::OnModifica"))
					bOK = TRUE;

				setTemp.CloseRecordset("CStrumentiDlg::OnModifica");
			}

			if (bOK)
				RiempiLista();
		}
	}
}

void CStrumentiDlg::OnModifica()
{
	int nIndex = m_ctrlListStrumenti.GetCurSel();
	if (nIndex >= 0)
	{
		CString strTemp;
		m_ctrlListStrumenti.GetText(nIndex, strTemp);

		CAddDescrDlg dlg(this, "Modifica strumento", 255, strTemp, 0);
		if (dlg.DoModal() == IDOK)
		{
			CStrumentiSet setTemp;
			BOOL bOK = FALSE;

			CString strFilter;
			strFilter.Format("Contatore=%li", (long)m_ctrlListStrumenti.GetItemData(nIndex));

			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CStrumentiDlg::OnModifica"))
			{
				if (setTemp.EditRecordset("CStrumentiDlg::OnModifica"))
				{
					setTemp.m_sTesto = dlg.m_strDescription;

					if (setTemp.UpdateRecordset("CStrumentiDlg::OnModifica"))
						bOK = TRUE;
				}

				setTemp.CloseRecordset("CStrumentiDlg::OnModifica");
			}

			if (bOK)
				RiempiLista();
		}
	}
}

void CStrumentiDlg::OnNuovo()
{
	CAddDescrDlg dlg(this, "Inserimento nuovo strumento", 255, "", 0);

	if (dlg.DoModal() == IDOK)
	{
		CStrumentiSet setTemp;
		BOOL bOK = FALSE;

		if (setTemp.OpenRecordset("CStrumentiDlg::OnNuovo"))
		{
			if (setTemp.AddNewRecordset("CStrumentiDlg::OnNuovo"))
			{
				setTemp.m_sTesto = dlg.m_strDescription;
				setTemp.m_sSede = CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, FALSE);

				if (setTemp.UpdateRecordset("CStrumentiDlg::OnNuovo"))
					bOK = TRUE;
			}

			setTemp.CloseRecordset("CStrumentiDlg::OnNuovo");
		}

		if (bOK)
			RiempiLista();
	}
}

void CStrumentiDlg::RiempiLista()
{
	CStrumentiSet setTemp;

	m_ctrlListStrumenti.ResetContent();

	setTemp.SetOpenFilter("Sede LIKE '" + CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, TRUE) + "' AND ELIMINATO=0");
	setTemp.SetSortRecord("Testo");
	if (setTemp.OpenRecordset("CStrumentiDlg::RiempiLista"))
	{
		int nIndex;

		while(!setTemp.IsEOF())
		{
			nIndex = m_ctrlListStrumenti.AddString(setTemp.m_sTesto);
			m_ctrlListStrumenti.SetItemData(nIndex, (DWORD)setTemp.m_lContatore);

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CStrumentiDlg::RiempiLista");
	}
}