#include "stdafx.h"
#include "Endox.h"
#include "NomenclatoreRisDlg.h"

#include "MediciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNomenclatoreRisDlg::CNomenclatoreRisDlg(CWnd* pParentWnd, CEsamiView* pEsamiView)
	: CDialog(CNomenclatoreRisDlg::IDD, pParentWnd),
	m_ctrlListResult(pEsamiView)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

BEGIN_MESSAGE_MAP(CNomenclatoreRisDlg, CDialog)
	// ON_WM_GETMINMAXINFO()
	// ON_WM_PAINT()
	// ON_WM_SIZE()

	ON_BN_CLICKED(IDC_STAMPA, OnStampa) // DA CANCELLARE //
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	ON_NOTIFY(LVN_ENDSCROLL, IDC_LIST_RESULT, OnLvnEndScrollListResult)
END_MESSAGE_MAP()

void CNomenclatoreRisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_RESULT, m_ctrlListResult);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
}

BOOL CNomenclatoreRisDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlListResult.SetExtendedStyle(m_ctrlListResult.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	
	//Caricamento icone bottoni..
	m_BtnStampa.AutoLoad(IDC_STAMPA, this);
	m_BtnExport.AutoLoad(IDC_EXPORT, this);

	theApp.LocalizeDialog(this, CNomenclatoreRisDlg::IDD, "NomenclatoreRisDlg");

	if (m_sDataIniz.Find('_') < 0)
	{
		// data inizio apparentemente valida //
		m_sDataIniz = theApp.GetMessageString(IDS_A_PARTIRE_DAL) + " " + m_sDataIniz;
	}
	else
	{
		// data inizio apparentemente NON valida //
		m_sDataIniz.Empty();
	}

	if (m_sDataFine.Find('_') < 0)
	{
		// data fine apparentemente valida //
		m_sDataFine = theApp.GetMessageString(IDS_FINO_AL) + " " + m_sDataFine;
	}
	else
	{
		// data fine apparentemente NON valida //
		m_sDataFine.Empty();
	}

	CMediciSet setMedico;
	CString strMedico = setMedico.GetFieldTextFromContatore(m_lMedico);

	CString strTemp;
	strTemp.Format(theApp.GetMessageString(IDS_NOMENCLATORE_TITLE), 
		           m_sDataIniz, 
				   m_sDataFine, 
				   (m_nProvenienza == 0 ? theApp.GetMessageString(IDS_NOMENCLATORE_PROV_I) : (m_nProvenienza == 1 ? theApp.GetMessageString(IDS_NOMENCLATORE_PROV_E) : theApp.GetMessageString(IDS_NOMENCLATORE_PROV_ALL))),
				   (m_sSedeEsame.IsEmpty() ? "" : " " + theApp.GetMessageString(IDS_NELLA_SEDE_DI) + " " + m_sSedeEsame),
				   (strMedico.IsEmpty() ? "" : " " + theApp.GetMessageString(IDS_DA) + " " + strMedico));
	
	strTemp.Replace("  ", " ");
	strTemp.Replace("  ", " ");

	SetWindowText(strTemp);

	return TRUE;
}

void CNomenclatoreRisDlg::OnStampa() 
{
	CString strTemp;

	// Sandro Gallina - 31/05/2004 //
	// strTemp.Format("Prestazioni eseguite dal %s al %s su pazienti %s%s - ", m_dtInizio.Format("%d/%m/%Y"), m_dtFine.Format("%d/%m/%Y"), (m_nProvenienza == 0 ? "interni" : (m_nProvenienza == 1 ? "esterni" : "interni ed esterni")), m_sSedeEsame.IsEmpty() ? "" : " nella sede di " + m_sSedeEsame);
	GetWindowText(strTemp);

	m_ctrlListResult.SetNotePiePagina(strTemp + " - ");
	m_ctrlListResult.Print();
}

void CNomenclatoreRisDlg::OnExport() 
{
	CString strTemp;

	// Sandro Gallina - 31/05/2004 //
	GetWindowText(strTemp);

	m_ctrlListResult.Export(strTemp);
}

void CNomenclatoreRisDlg::OnLvnEndScrollListResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);

	m_ctrlListResult.Invalidate();

	*pResult = 0;
}
