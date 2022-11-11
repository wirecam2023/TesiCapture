#include "stdafx.h"
#include "Endox.h"
#include "VisualizzatoreLogDlg.h"

#include "EsamiView.h"
#include "TbLogCompletoSet.h"
#include "ViewLogImportazioneCasiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COL_DATA 0
#define COL_UTENTE1 1
#define COL_STAZIONE1 2
#define COL_OPERAZIONE 3
#define COL_TABELLA 4
#define COL_CAMPO 5
#define COL_VALOREOLD 6
#define COL_VALORENEW 7

#define COL_PAZIENTE 0
#define COL_ESAMEORIG 1
#define COL_ESAMEDEST 2
#define COL_DATAORA 3
#define COL_UTENTE2 4
#define COL_STAZIONE2 5

IMPLEMENT_DYNAMIC(CVisualizzatoreLogDlg, CEndoxResizableDlg)

CVisualizzatoreLogDlg::CVisualizzatoreLogDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL bLogImportCasi)
	: CEndoxResizableDlg(CVisualizzatoreLogDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_bLogImportCasi = bLogImportCasi;
}

CVisualizzatoreLogDlg::~CVisualizzatoreLogDlg()
{
}

BEGIN_MESSAGE_MAP(CVisualizzatoreLogDlg, CEndoxResizableDlg)
END_MESSAGE_MAP()

void CVisualizzatoreLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

BOOL CVisualizzatoreLogDlg::OnInitDialog()
{   
	BOOL bReturn = CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	if (!m_bLogImportCasi)
	{
		m_ctrlList.InsertColumn(COL_DATA, theApp.GetMessageString(IDS_DATA), LVCFMT_LEFT, 50); // "Data"
		m_ctrlList.InsertColumn(COL_UTENTE1, theApp.GetMessageString(IDS_UTENTE), LVCFMT_LEFT, 50); // "Utente"
		m_ctrlList.InsertColumn(COL_STAZIONE1, theApp.GetMessageString(IDS_STAZIONE), LVCFMT_LEFT, 50); // "Stazione"
		m_ctrlList.InsertColumn(COL_OPERAZIONE, theApp.GetMessageString(IDS_OPERAZIONE), LVCFMT_LEFT, 50); // "Operazione"
		m_ctrlList.InsertColumn(COL_TABELLA, theApp.GetMessageString(IDS_TABELLA), LVCFMT_LEFT, 50); // "Tabella"
		m_ctrlList.InsertColumn(COL_CAMPO, theApp.GetMessageString(IDS_CAMPO), LVCFMT_LEFT, 50); // "Campo"
		m_ctrlList.InsertColumn(COL_VALOREOLD, theApp.GetMessageString(IDS_VALOREPRECEDENTE), LVCFMT_LEFT, 50); // "Valore precedente"
		m_ctrlList.InsertColumn(COL_VALORENEW, theApp.GetMessageString(IDS_VALORENUOVO), LVCFMT_LEFT, 50); // "Valore nuovo"

		RiempiLista();
	}
	else
	{
		m_ctrlList.InsertColumn(COL_PAZIENTE, theApp.GetMessageString(IDS_PAZIENTE), LVCFMT_LEFT, 50);
		m_ctrlList.InsertColumn(COL_ESAMEORIG, theApp.GetMessageString(IDS_ESAMEORIG), LVCFMT_LEFT, 50);
		m_ctrlList.InsertColumn(COL_ESAMEDEST, theApp.GetMessageString(IDS_ESAMEDEST), LVCFMT_LEFT, 50);
		m_ctrlList.InsertColumn(COL_DATAORA, theApp.GetMessageString(IDS_DATA), LVCFMT_LEFT, 50);
		m_ctrlList.InsertColumn(COL_UTENTE2, theApp.GetMessageString(IDS_UTENTE), LVCFMT_LEFT, 50);
		m_ctrlList.InsertColumn(COL_STAZIONE2, theApp.GetMessageString(IDS_STAZIONE), LVCFMT_LEFT, 50);

		RiempiListaImportCasi();
	}

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	theApp.LocalizeDialog(this, CVisualizzatoreLogDlg::IDD, "LogEsameDlg");
	return bReturn;
}

void CVisualizzatoreLogDlg::RiempiLista()
{
	BeginWaitCursor();

	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CString sOperazione[] = { "Inserimento", "Modifica" };

	CString strFilter;
	strFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	CTbLogCompletoSet setLog;
	setLog.SetOpenFilter(strFilter);
	setLog.SetSortRecord("ID");
	if (setLog.OpenRecordset("CVisualizzatoreLogDlg::RiempiLista")) // , TRUE, CRecordset::forwardOnly))
	{
		int nItem = 0;
		CString strTemp;

		while(!setLog.IsEOF())
		{
			strTemp.Empty();
			if (setLog.m_sDataOra.GetLength() == 14)
				strTemp.Format("%s/%s/%s %s:%s", setLog.m_sDataOra.Mid(6, 2), setLog.m_sDataOra.Mid(4, 2), setLog.m_sDataOra.Left(4), setLog.m_sDataOra.Mid(8, 2), setLog.m_sDataOra.Mid(10, 2));

			m_ctrlList.InsertItem(nItem, strTemp);

			m_ctrlList.SetItemText(nItem, COL_UTENTE1, setLog.m_sUtente);

			m_ctrlList.SetItemText(nItem, COL_STAZIONE1, setLog.m_sStazione);

			switch(setLog.m_lOperazione)
			{
				case 1:
				{
					strTemp = sOperazione[0];
					break;
				}
				case 2:
				{
					strTemp = sOperazione[1];
					break;
				}
				default:
				{
					strTemp.Empty();
					break;
				}
			}
			m_ctrlList.SetItemText(nItem, COL_OPERAZIONE, strTemp);

			m_ctrlList.SetItemText(nItem, COL_TABELLA, setLog.m_sTabella);

			m_ctrlList.SetItemText(nItem, COL_CAMPO, setLog.m_sCampo);

			m_ctrlList.SetItemText(nItem, COL_VALOREOLD, setLog.m_sValoreOld);

			m_ctrlList.SetItemText(nItem, COL_VALORENEW, setLog.m_sValoreNew);

			nItem++;
			setLog.MoveNext();
		}

		setLog.CloseRecordset("CVisualizzatoreLogDlg::RiempiLista");
	}

	m_ctrlList.SetColumnWidth(COL_DATA, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(COL_UTENTE1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(COL_STAZIONE1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(COL_OPERAZIONE, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(COL_TABELLA, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(COL_CAMPO, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(COL_VALOREOLD, 200);
	m_ctrlList.SetColumnWidth(COL_VALORENEW, 200);

	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CVisualizzatoreLogDlg::RiempiListaImportCasi()
{
	BeginWaitCursor();

	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CViewLogImportazioneCasiSet setLog;
	setLog.SetSortRecord("ID DESC");
	if (setLog.OpenRecordset("CVisualizzatoreLogDlg::RiempiListaImportCasi"))
	{
		int nItem = 0;
		while (!setLog.IsEOF())
		{
			CString sPaziente;
			sPaziente.Format("%s %s (%li)", setLog.m_sCognome, setLog.m_sNome, setLog.m_lIDPaziente);
			sPaziente.Trim();
			m_ctrlList.InsertItem(nItem, sPaziente);

			CString sEsameOrig;
			sEsameOrig.Format("%s %s", setLog.m_sCodiceEsternoEsameOrigine, setLog.m_sTipoEsameOrigine);
			sEsameOrig.Trim();
			m_ctrlList.SetItemText(nItem, COL_ESAMEORIG, sEsameOrig);

			CString sEsameDest;
			sEsameDest.Format("%s %s", setLog.m_sCodiceEsternoEsameDestinazione, setLog.m_sTipoEsameDestinazione);
			sEsameDest.Trim();
			m_ctrlList.SetItemText(nItem, COL_ESAMEDEST, sEsameDest);

			CString sDataOra = "";
			if (setLog.m_sDataOra.GetLength() == 14)
				sDataOra.Format("%s/%s/%s %s:%s", setLog.m_sDataOra.Mid(6, 2), setLog.m_sDataOra.Mid(4, 2), setLog.m_sDataOra.Left(4), setLog.m_sDataOra.Mid(8, 2), setLog.m_sDataOra.Mid(10, 2));
			m_ctrlList.SetItemText(nItem, COL_DATAORA, sDataOra);

			m_ctrlList.SetItemText(nItem, COL_UTENTE2, setLog.m_sUtente);

			m_ctrlList.SetItemText(nItem, COL_STAZIONE2, setLog.m_sStazione);

			nItem++;
			setLog.MoveNext();
		}

		setLog.CloseRecordset("CVisualizzatoreLogDlg::RiempiListaImportCasi");
	}

	m_ctrlList.SetColumnWidth(COL_PAZIENTE, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(COL_ESAMEORIG, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(COL_ESAMEDEST, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(COL_DATAORA, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(COL_UTENTE2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(COL_STAZIONE2, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}