#include "stdafx.h"
#include "Endox.h"
#include "SelezioneDispositivoVSDlg.h"

#include "EsamiView.h"
#include "VitalSignDispositiviSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSelezioneDispositivoVSDlg::CSelezioneDispositivoVSDlg(CWnd* pParent)
	: CDialog(CSelezioneDispositivoVSDlg::IDD, pParent)
{
	m_sCodiceDispositivoSelezionato = "";
	m_sNomeDispositivoMonitoraggio = "";
	m_lIdDispositivo = -1;
}

BEGIN_MESSAGE_MAP(CSelezioneDispositivoVSDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CONTINUA, &CSelezioneDispositivoVSDlg::OnBnClickedContinua)
	ON_BN_CLICKED(IDC_BTN_ANNULLA, &CSelezioneDispositivoVSDlg::OnBnClickedBtnAnnulla)
END_MESSAGE_MAP()

void CSelezioneDispositivoVSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_CMB_DISPOSITIVO, m_ctrlCmbDispositivo);
	DDX_Control(pDX, IDC_BTN_CONTINUA, m_ctrlBtnContinua);

}

BOOL CSelezioneDispositivoVSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();	

	GetDlgItem(IDC_STATIC_1)->SetFont(&theApp.m_fontBig, TRUE);

	CVitalSignDispositiviSet set;

	if (set.OpenRecordset("CSelezioneDispositivoVSDlg::OnInitDialog"))
	{
		while (!set.IsEOF())
		{
			int index = m_ctrlCmbDispositivo.AddString(set.m_sDescrizione);
			m_ctrlCmbDispositivo.SetItemData(index, set.m_lID);

			if (set.m_sCodiceIdentificativo == theApp.m_sCodiceDispositivoDefault)
				m_ctrlCmbDispositivo.SetCurSel(index);

			set.MoveNext();
		}

		set.CloseRecordset("CSelezioneDispositivoVSDlg::OnInitDialog");
	}

	theApp.LocalizeDialog(this, CSelezioneDispositivoVSDlg::IDD, "SelezioneDispositivoVSDlg");

	return TRUE;
}


void CSelezioneDispositivoVSDlg::OnBnClickedContinua()
{
	int index = m_ctrlCmbDispositivo.GetCurSel();
	int id = m_ctrlCmbDispositivo.GetItemData(index);

	CVitalSignDispositiviSet set;
	CString filter;
	filter.Format("id=%li", id);
	set.SetOpenFilter(filter);

	if (set.OpenRecordset("CSelezioneDispositivoVSDlg::OnInitDialog"))
	{
		if (!set.IsEOF())
		{
			m_sCodiceDispositivoSelezionato = set.m_sCodiceIdentificativo;
			m_sNomeDispositivoMonitoraggio = set.m_sDescrizione;
			m_lIdDispositivo = set.m_lID;

			set.MoveNext();
		}

		set.CloseRecordset("CSelezioneDispositivoVSDlg::OnInitDialog");
	}

	CDialog::OnOK();
}

void CSelezioneDispositivoVSDlg::OnCancel()
{

}

void CSelezioneDispositivoVSDlg::OnOK()
{	
}

void CSelezioneDispositivoVSDlg::OnBnClickedBtnAnnulla()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SELEZIONE_DISPOSITIVO_VS_ANNULLA), MB_YESNO) == IDYES)
		CDialog::OnCancel();
}
