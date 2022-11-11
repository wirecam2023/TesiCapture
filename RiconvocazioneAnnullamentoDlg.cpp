//Gabriel BUG 6225 - Lista DO

#include "stdafx.h"
#include "Endox.h"
#include "RiconvocazioneAnnullamentoDlg.h"
#include "RiconvocazioneSet.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRiconvocazioneAnnullamentoDlg, CDialog)

CRiconvocazioneAnnullamentoDlg::CRiconvocazioneAnnullamentoDlg(CWnd* pParent, long lIdEsame)
: CDialog(CRiconvocazioneAnnullamentoDlg::IDD, pParent)
{
	m_lIdEsame = lIdEsame;
}

CRiconvocazioneAnnullamentoDlg::~CRiconvocazioneAnnullamentoDlg()
{
}

void CRiconvocazioneAnnullamentoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
}


BEGIN_MESSAGE_MAP(CRiconvocazioneAnnullamentoDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CRiconvocazioneAnnullamentoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRiconvocazioneAnnullamentoDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

void CRiconvocazioneAnnullamentoDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDT_MOTIVO, m_sMotivoAnnullamento);

	CString sFilter;
	sFilter.Format("IDESAME=%li AND ELIMINATO = 0", m_lIdEsame);

	CRiconvocazioneSet set;
	set.SetOpenFilter(sFilter);

	if (set.OpenRecordset("CRiconvocazioneAnnullamentoDlg::OnBnClickedOk"))
	{
		if (!set.IsEOF())
		{
			if (set.EditRecordset("CRiconvocazioneAnnullamentoDlg::OnBnClickedOk"))
			{
				set.SetMotivoAnnullamento(set.m_lId, m_sMotivoAnnullamento);
				set.SetEliminato(set.m_lId);
				
				if(set.UpdateRecordset("CRiconvocazioneAnnullamentoDlg::OnBnClickedOk"))
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RICONVOCAZIONE_ANNULLAMENTO_OK));
			}
		}
		set.CloseRecordset("CRiconvocazioneAnnullamentoDlg::OnBnClickedOk");
	}
	CDialog::OnOK();
}

void CRiconvocazioneAnnullamentoDlg::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

void CRiconvocazioneAnnullamentoDlg::OnCancel()
{
}

void CRiconvocazioneAnnullamentoDlg::OnOK()
{

}