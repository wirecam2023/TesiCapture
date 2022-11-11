#include "stdafx.h"
#include "Endox.h"
#include "Endox.h"

#include "AnatomiaPatologicaPrestNewEdtDlg.h"
#include "AnatomiaPatologicaPrestSet.h"
#include "EsamiView.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAnatomiaPatologicaPrestNewEdtDlg, CDialog)

CAnatomiaPatologicaPrestNewEdtDlg::CAnatomiaPatologicaPrestNewEdtDlg(CWnd* pParent, CEsamiView* pEsamiView, long lRecord)
	: CDialog(CAnatomiaPatologicaPrestNewEdtDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_lRecord = lRecord;
}

CAnatomiaPatologicaPrestNewEdtDlg::~CAnatomiaPatologicaPrestNewEdtDlg()
{
	m_setRecord.CloseRecordset("CAnatomiaPatologicaPrestNewEdtDlg::~CAnatomiaPatologicaPrestNewEdtDlg");
}

BEGIN_MESSAGE_MAP(CAnatomiaPatologicaPrestNewEdtDlg, CDialog)
END_MESSAGE_MAP()

void CAnatomiaPatologicaPrestNewEdtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);

	DDX_Control(pDX, IDC_COMBO_PRESTAZIONE, m_ctrlComboPrestazione);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
}

BOOL CAnatomiaPatologicaPrestNewEdtDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	CAnatomiaPatologicaPrestSet setTemp;
	setTemp.SetSortRecord("TipoEsame, Descrizione");
	if (setTemp.OpenRecordset("CAnatomiaPatologicaPrestNewEdtDlg::OnInitDialog"))
	{
		int nTemp;
		while(!setTemp.IsEOF())
		{
			nTemp = m_ctrlComboPrestazione.AddString(setTemp.m_sTipoEsame + " - " + setTemp.m_sDescrizione);
			m_ctrlComboPrestazione.SetItemData(nTemp, (DWORD)setTemp.m_lID);

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAnatomiaPatologicaPrestNewEdtDlg::OnInitDialog");
	}

	if (m_lRecord <= 0)
	{
		m_setRecord.OpenRecordset("CAnatomiaPatologicaPrestNewEdtDlg::OnInitDialog");
	}
	else
	{
		CString strFilter;
		strFilter.Format("ID=%li", m_lRecord);

		m_setRecord.SetOpenFilter(strFilter);
		if (m_setRecord.OpenRecordset("CAnatomiaPatologicaPrestNewEdtDlg::OnInitDialog"))
		{
			if (!m_setRecord.IsEOF())
			{
				int nIndexFound;

				CAnatomiaPatologicaPrestSet setPrest;
				nIndexFound = m_ctrlComboPrestazione.FindStringExact(-1, setPrest.GetFieldTextComplete(m_setRecord.m_lIDPrestazione));
				if (nIndexFound >= 0)
					m_ctrlComboPrestazione.SetCurSel(nIndexFound);
			}
		}
	}

	theApp.LocalizeDialog(this, CAnatomiaPatologicaPrestNewEdtDlg::IDD, "AnatomiaPatologicaPrestNewEdtDlg");

	if (m_lRecord <= 0)
		SetWindowText(theApp.GetMessageString(IDS_INSERIMENTO_NUOVA_PRESTAZIONE));
	else
		SetWindowText(theApp.GetMessageString(IDS_MODIFICA_PRESTAZIONE));

	return bReturn;
}

void CAnatomiaPatologicaPrestNewEdtDlg::OnOK()
{
	CString sPrestazione = "";
	m_ctrlComboPrestazione.GetWindowText(sPrestazione);
	if (sPrestazione.GetLength() <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPAT_ERROR3));
		return;
	}
	long lPrestazione = m_ctrlComboPrestazione.GetItemData(m_ctrlComboPrestazione.GetCurSel());

	if (m_lRecord <= 0) // addnew //
	{
		if (m_setRecord.AddNewRecordset("CAnatomiaPatologicaPrestNewEdtDlg::OnOK"))
		{
			m_setRecord.m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
			m_setRecord.m_lIDPrestazione = lPrestazione;

			m_setRecord.UpdateRecordset("CAnatomiaPatologicaPrestNewEdtDlg::OnOK");
		}
	}
	else // edit //
	{
		if (m_setRecord.EditRecordset("CAnatomiaPatologicaPrestNewEdtDlg::OnOK"))
		{
			m_setRecord.m_lIDPrestazione = lPrestazione;

			m_setRecord.UpdateRecordset("CAnatomiaPatologicaPrestNewEdtDlg::OnOK");
		}
	}

	CDialog::OnOK();
}