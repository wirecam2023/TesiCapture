#include "stdafx.h"
#include "Endox.h"
#include "CronicitaPazienteDlg.h"

#include "Common.h"
#include "CronicitaPazienteRecordDlg.h"
#include "CustomDate.h"
#include "EsamiFarmaciCroniciSet.h"
#include "EsamiView.h"
#include "FarmaciPazientiCroniciSet.h"
#include "MalattieCronicheCampiSet.h"
#include "MalattieCronicheSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RGB_ATTIVITA RGB(255, 127, 127)
#define RGB_REMISSIONE RGB(127, 255, 127)

IMPLEMENT_DYNAMIC(CCronicitaPazienteDlg, CResizableDialog)

CCronicitaPazienteDlg::CCronicitaPazienteDlg(CWnd* pParent, CEsamiView* pEsamiView, CPazientiSet* pPazientiSet)
	: CResizableDialog(CCronicitaPazienteDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	ASSERT(pPazientiSet != NULL);

	m_pEsamiView = pEsamiView;
	m_pPazientiSet = pPazientiSet;

	//

	m_ctrlListSn.SetBindedListCtrl(&m_ctrlListDx);
	m_ctrlListDx.SetBindedListCtrl(&m_ctrlListSn);

	//

	m_lNumeroColonne = 0;
	m_pColonne = NULL;

	m_lNumeroRighe = 0;
	m_pRighe = NULL;

	//

	CString sFilter;
	sFilter.Format("Paziente=%li AND IDMalattiaCronica<>0", m_pPazientiSet->m_lContatore);
	m_setEsami.SetBaseFilter("(RecordSenzaAccesso=0 OR RecordSenzaAccesso=1)");
	m_setEsami.SetOpenFilter(sFilter);
	m_setEsami.SetSortRecord("Data, Contatore");

	//

	m_brushSfondoEdit.CreateSolidBrush(theApp.m_colorSfondo[1]);
}

CCronicitaPazienteDlg::~CCronicitaPazienteDlg()
{
	if (m_pColonne != NULL)
	{
		delete m_pColonne;
		m_pColonne = NULL;
	}

	if (m_pRighe != NULL)
	{
		delete m_pRighe;
		m_pRighe = NULL;
	}

	m_brushSfondoEdit.DeleteObject();
}

BEGIN_MESSAGE_MAP(CCronicitaPazienteDlg, CResizableDialog)

	ON_WM_CTLCOLOR()
	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_BTN_CHIUDI, OnBnClickedBtnChiudi)
	ON_BN_CLICKED(IDC_BTN_NEWRECORD, OnBnClickedBtnNewRecord)

	ON_NOTIFY(NM_CLICK, IDC_LIST_01, OnNMClickListSn)
	ON_NOTIFY(NM_CLICK, IDC_LIST_02, OnNMClickListDx)

END_MESSAGE_MAP()

void CCronicitaPazienteDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEWRECORD, m_ctrlBtnNewRecord);
	DDX_Control(pDX, IDC_BTN_CHIUDI, m_ctrlBtnChiudi);

	DDX_Control(pDX, IDC_EDIT_01, m_ctrlEdit01);

	DDX_Control(pDX, IDC_LIST_01, m_ctrlListSn);
	DDX_Control(pDX, IDC_LIST_02, m_ctrlListDx);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
}

void CCronicitaPazienteDlg::OnCancel()
{
}

BOOL CCronicitaPazienteDlg::OnInitDialog()
{
	CResizableDialog::OnInitDialog();

	//

	AddAnchor(IDC_STATIC_01, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_STATIC_02, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_STATIC_03, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_EDIT_01, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_BTN_NEWRECORD, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_LIST_01, CSize(0, 0), CSize(0, 100));
	AddAnchor(IDC_LIST_02, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_BTN_CHIUDI, CSize(100, 100), CSize(100, 100));

	//

	m_ctrlStatic01.SetFont(&theApp.m_fontBold);
	m_ctrlStatic02.SetFont(&theApp.m_fontBold);
	m_ctrlStatic03.SetFont(&theApp.m_fontBold);
	m_ctrlEdit01.SetFont(&theApp.m_fontBold);
	m_ctrlListSn.SetFont(&theApp.m_fontBold);
	m_ctrlBtnNewRecord.SetFont(&theApp.m_fontBold);

	// aggiorno i dati di intestazione relativi al paziente //

	CString sStatic;

	sStatic = m_pPazientiSet->m_sCognome + " " + m_pPazientiSet->m_sNome;
	sStatic.MakeUpper();
	sStatic.Trim();
	m_ctrlStatic01.SetWindowText(sStatic);

	if ((!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lNatoIlCustom)) && (m_pPazientiSet->m_lNatoIlCustom > 0))
	{
		if (theApp.m_bAtivaListaDO)
			sStatic = CCustomDate(m_pPazientiSet->m_lNatoIlCustom).GetDate("%d/%m/%Y") + " (" + GetStringEta(m_pPazientiSet->m_lNatoIlCustom, CCustomDate(TRUE, TRUE).GetDate(), FormatoEta::SoloAnno) + ")"; //Gabriel BUG 6225 - Lista DO
		else
			sStatic = CCustomDate(m_pPazientiSet->m_lNatoIlCustom).GetDate("%d/%m/%Y") + " (" + GetStringEta(m_pPazientiSet->m_lNatoIlCustom, CCustomDate(TRUE, TRUE).GetDate(), TRUE) + ")";
		sStatic.Trim();
		m_ctrlStatic02.SetWindowText(sStatic);
	}

	sStatic = CMalattieCronicheSet().GetDescrizione(m_pPazientiSet->m_lIDMalattiaCronica);
	sStatic.MakeUpper();
	sStatic.Trim();
	m_ctrlStatic03.SetWindowText(sStatic);

	m_ctrlEdit01.SetWindowText(m_pPazientiSet->m_sDescrizioneMalattiaCronica);

	//

	m_ctrlImageList.Create(150, 19, ILC_COLOR32, 2, 0);
	m_ctrlImageList.Add(AfxGetApp()->LoadIcon(IDI_BTN_VAIALLESAME));
	m_ctrlImageList.Add(AfxGetApp()->LoadIcon(IDI_BTN_MODIFICA));

	m_ctrlListSn.SetExtendedStyle(m_ctrlListSn.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP); // senza LVS_EX_FULLROWSELECT non mi restituisce il click sulla riga giusta !!! //

	m_ctrlListDx.SetExtendedStyle(m_ctrlListDx.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP | LVS_EX_SUBITEMIMAGES); // senza LVS_EX_FULLROWSELECT non mi restituisce il click sulla riga giusta !!! //
	m_ctrlListDx.SetImageList(&m_ctrlImageList, LVSIL_SMALL);

	//

	RiempiLista();

	//

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	//

	theApp.LocalizeDialog(this, CCronicitaPazienteDlg::IDD, "CronicitaPazienteDlg");
	return TRUE;
}

void CCronicitaPazienteDlg::OnOK()
{
}

HBRUSH CCronicitaPazienteDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CResizableDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_01:
		case IDC_STATIC_02:
		{
			pDC->SetTextColor(theApp.m_color[0]);
			break;
		}
		case IDC_STATIC_03:
		{
			pDC->SetTextColor(theApp.m_color[5]);
			break;
		}
		case IDC_EDIT_01:
		{
			pDC->SetTextColor(theApp.m_color[4]);
			pDC->SetBkColor(theApp.m_colorSfondo[1]);
			return m_brushSfondoEdit;
			break;
		}
	}

	return hBrush;
}

void CCronicitaPazienteDlg::OnSize(UINT nType, int cx, int cy) 
{
	CResizableDialog::OnSize(nType, cx, cy);

	if (m_ctrlListSn.GetSafeHwnd() && m_ctrlListDx.GetSafeHwnd())
	{
		SCROLLINFO si;
		CRect rect;

		// imposto l'altezza della lista di sinistra (dipende se a destra c'è la scrollbar orizzontale visualizzata o meno)

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
		if (m_ctrlListDx.GetScrollInfo(SB_HORZ, &si, SIF_ALL))
		{
			m_ctrlListDx.GetClientRect(&rect);
			if (rect.Width() < si.nMax) // Barra orizzontale visibile...
			{
				m_ctrlListSn.GetWindowRect(&rect);
				ScreenToClient(&rect);

				m_ctrlListSn.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height() - GetSystemMetrics(SM_CYHSCROLL), SWP_NOZORDER | SWP_NOMOVE);
			}
		}

		// imposto la larghezza della colonna nella lista di sinistra (dipende se c'è la scrollbar verticale) //

		m_ctrlListSn.GetWindowRect(&rect);
		ScreenToClient(&rect);

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
		if (m_ctrlListDx.GetScrollInfo(SB_VERT, &si) && ((int)si.nPage) <= si.nMax)
			rect.right -= GetSystemMetrics(SM_CXVSCROLL);

		m_ctrlListSn.SetColumnWidth(1, rect.Width() - 4);
	}
}

void CCronicitaPazienteDlg::OnBnClickedBtnChiudi()
{
	// salvo il testo relativo al "post-it" //

	if (m_pPazientiSet->EditRecordset("CCronicitaPazienteDlg::OnBnClickedBtnChiudi"))
	{
		m_ctrlEdit01.GetWindowText(m_pPazientiSet->m_sDescrizioneMalattiaCronica);

		m_pPazientiSet->UpdateRecordset("CCronicitaPazienteDlg::OnBnClickedBtnChiudi");
	}

	//

	CResizableDialog::OnOK();
}

void CCronicitaPazienteDlg::OnBnClickedBtnNewRecord()
{
	CCronicitaPazienteRecordDlg dlg(this, m_pEsamiView, m_pPazientiSet->m_lIDMalattiaCronica, 0);
	if (dlg.DoModal() == IDOK)
		RiempiLista();
}

void CCronicitaPazienteDlg::OnNMClickListSn(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// Sandro 17/06/2013 // i primi 150 pixel sono ERRONEAMENTE assegnati alla colonna 0 anche se questa ha larghezza nulla //
	// if (pNMItemActivate->iSubItem == 0)
	//	pNMItemActivate->iSubItem = 2;

	TRACE2("--> CCronicitaPazienteDlg::OnNMClickListSn --> %d %d\n", pNMItemActivate->iItem, pNMItemActivate->iSubItem);

	BOOL bFound = FALSE;

	for(int i = m_ctrlListDx.GetHeaderCtrl()->GetItemCount() - 1; i > 1; i--)
	{
		CString sTemp = m_ctrlListDx.GetItemText(pNMItemActivate->iItem, i);
		sTemp.Trim();

		if (!sTemp.IsEmpty())
		{
			// evidenzio cella //
			m_ctrlListDx.HighlightCell(pNMItemActivate->iItem, i);

			// mi sposto tutto a destra //
			m_ctrlListDx.EnsureColumnVisible(m_ctrlListDx.GetHeaderCtrl()->GetItemCount() - 1, FALSE);

			// se necessario mi risposto verso sinistra per mostrare il campo evidenziato //
			m_ctrlListDx.EnsureColumnVisible(i, FALSE);

			//
			m_ctrlListDx.RedrawWindow();

			//
			bFound = TRUE;
			break;
		}
	}

	if (!bFound)
	{
		m_ctrlListDx.HighlightCell(-1, -1);
		m_ctrlListDx.RedrawWindow();
	}

	*pResult = 0;
}

void CCronicitaPazienteDlg::OnNMClickListDx(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// Sandro 17/06/2013 // i primi 150 pixel sono ERRONEAMENTE assegnati alla colonna 0 anche se questa ha larghezza nulla //
	if (pNMItemActivate->iSubItem == 0)
		pNMItemActivate->iSubItem = 2;

	TRACE2("--> CCronicitaPazienteDlg::OnNMClickListDx --> %d %d\n", pNMItemActivate->iItem, pNMItemActivate->iSubItem);

	if ((pNMItemActivate->iItem == m_ctrlListDx.GetItemCount() - 1) && (pNMItemActivate->iSubItem > 1))
	{
		if (m_pColonne[pNMItemActivate->iSubItem - 2].bRecordSenzaAccesso)
		{
			CCronicitaPazienteRecordDlg dlg(this, m_pEsamiView, m_pPazientiSet->m_lIDMalattiaCronica, m_pColonne[pNMItemActivate->iSubItem - 2].lIDEsame);
			if (dlg.DoModal() == IDOK)
				RiempiLista();
		}
		else
		{
			BeginWaitCursor();
			if (m_pEsamiView->RicercaCodicePaziente(m_pPazientiSet->m_lContatore, m_pColonne[pNMItemActivate->iSubItem - 2].lIDEsame, FALSE, FALSE))
				m_pEsamiView->MovePazientiAndEsami(NULL, FALSE, TRUE);
			else
				m_pEsamiView->MovePazientiAndEsami(NULL, TRUE, TRUE);
			EndWaitCursor();

			CDialog::OnOK();
		}
	}

	*pResult = 0;
}

void CCronicitaPazienteDlg::FillDatiCampoLibero(long lIDCampo, STRUCT_RIGA* pRiga)
{
	ASSERT(((lIDCampo >= edt_libero000) && (lIDCampo <= edt_libero099)) || ((lIDCampo >= edt_liberodataora000) && (lIDCampo <= edt_liberodataora019)));

	CString sTemp = g_FormCaract[lIDCampo].sDescrizione.Left(1023);
	memcpy(pRiga->szTitoloRiga, sTemp.GetBuffer(), sTemp.GetLength() + 1);
	sTemp.ReleaseBuffer();

	//

	pRiga->lIDCampo = lIDCampo;

	//

	pRiga->lTipoCampo = FT_BOH;

	if ((lIDCampo >= edt_libero000) && (lIDCampo <= edt_libero099))
	{
		if (theApp.m_bComboNumerico[lIDCampo - edt_libero000])
			pRiga->lTipoCampo = FT_NUMERICO;
		else if (theApp.m_bComboActive[lIDCampo - edt_libero000])
			pRiga->lTipoCampo = FT_LISTAVELOCE;
		else
			pRiga->lTipoCampo = FT_TESTOLIBERO;

	}
	else if ((lIDCampo >= edt_liberodataora000) && (lIDCampo <= edt_liberodataora019))
	{
		switch(theApp.m_iRadioDate[lIDCampo - edt_liberodataora000])
		{
			case DATA_ORA:
			{
				pRiga->lTipoCampo = FT_CUSTOM_DATAORA;
				break;
			}
			case SOLO_DATA:
			{
				pRiga->lTipoCampo = FT_CUSTOM_SOLODATA;
				break;
			}
			case SOLO_ORA:
			{
				pRiga->lTipoCampo = FT_CUSTOM_SOLOORA;
				break;
			}
		}
	}

	//

	switch(lIDCampo)
	{
		case edt_libero000:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto000;
			break;
		}
		case edt_libero001:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto001;
			break;
		}
		case edt_libero002:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto002;
			break;
		}
		case edt_libero003:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto003;
			break;
		}
		case edt_libero004:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto004;
			break;
		}
		case edt_libero005:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto005;
			break;
		}
		case edt_libero006:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto006;
			break;
		}
		case edt_libero007:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto007;
			break;
		}
		case edt_libero008:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto008;
			break;
		}
		case edt_libero009:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto009;
			break;
		}
		case edt_libero010:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto010;
			break;
		}
		case edt_libero011:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto011;
			break;
		}
		case edt_libero012:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto012;
			break;
		}
		case edt_libero013:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto013;
			break;
		}
		case edt_libero014:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto014;
			break;
		}
		case edt_libero015:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto015;
			break;
		}
		case edt_libero016:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto016;
			break;
		}
		case edt_libero017:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto017;
			break;
		}
		case edt_libero018:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto018;
			break;
		}
		case edt_libero019:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto019;
			break;
		}
		case edt_libero020:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto020;
			break;
		}
		case edt_libero021:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto021;
			break;
		}
		case edt_libero022:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto022;
			break;
		}
		case edt_libero023:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto023;
			break;
		}
		case edt_libero024:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto024;
			break;
		}
		case edt_libero025:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto025;
			break;
		}
		case edt_libero026:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto026;
			break;
		}
		case edt_libero027:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto027;
			break;
		}
		case edt_libero028:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto028;
			break;
		}
		case edt_libero029:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto029;
			break;
		}
		case edt_libero030:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto030;
			break;
		}
		case edt_libero031:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto031;
			break;
		}
		case edt_libero032:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto032;
			break;
		}
		case edt_libero033:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto033;
			break;
		}
		case edt_libero034:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto034;
			break;
		}
		case edt_libero035:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto035;
			break;
		}
		case edt_libero036:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto036;
			break;
		}
		case edt_libero037:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto037;
			break;
		}
		case edt_libero038:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto038;
			break;
		}
		case edt_libero039:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto039;
			break;
		}
		case edt_libero040:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto040;
			break;
		}
		case edt_libero041:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto041;
			break;
		}
		case edt_libero042:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto042;
			break;
		}
		case edt_libero043:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto043;
			break;
		}
		case edt_libero044:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto044;
			break;
		}
		case edt_libero045:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto045;
			break;
		}
		case edt_libero046:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto046;
			break;
		}
		case edt_libero047:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto047;
			break;
		}
		case edt_libero048:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto048;
			break;
		}
		case edt_libero049:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto049;
			break;
		}
		case edt_libero050:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto050;
			break;
		}
		case edt_libero051:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto051;
			break;
		}
		case edt_libero052:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto052;
			break;
		}
		case edt_libero053:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto053;
			break;
		}
		case edt_libero054:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto054;
			break;
		}
		case edt_libero055:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto055;
			break;
		}
		case edt_libero056:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto056;
			break;
		}
		case edt_libero057:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto057;
			break;
		}
		case edt_libero058:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto058;
			break;
		}
		case edt_libero059:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto059;
			break;
		}
		case edt_libero060:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto060;
			break;
		}
		case edt_libero061:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto061;
			break;
		}
		case edt_libero062:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto062;
			break;
		}
		case edt_libero063:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto063;
			break;
		}
		case edt_libero064:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto064;
			break;
		}
		case edt_libero065:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto065;
			break;
		}
		case edt_libero066:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto066;
			break;
		}
		case edt_libero067:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto067;
			break;
		}
		case edt_libero068:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto068;
			break;
		}
		case edt_libero069:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto069;
			break;
		}
		case edt_libero070:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto070;
			break;
		}
		case edt_libero071:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto071;
			break;
		}
		case edt_libero072:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto072;
			break;
		}
		case edt_libero073:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto073;
			break;
		}
		case edt_libero074:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto074;
			break;
		}
		case edt_libero075:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto075;
			break;
		}
		case edt_libero076:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto076;
			break;
		}
		case edt_libero077:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto077;
			break;
		}
		case edt_libero078:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto078;
			break;
		}
		case edt_libero079:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto079;
			break;
		}
		case edt_libero080:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto080;
			break;
		}
		case edt_libero081:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto081;
			break;
		}
		case edt_libero082:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto082;
			break;
		}
		case edt_libero083:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto083;
			break;
		}
		case edt_libero084:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto084;
			break;
		}
		case edt_libero085:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto085;
			break;
		}
		case edt_libero086:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto086;
			break;
		}
		case edt_libero087:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto087;
			break;
		}
		case edt_libero088:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto088;
			break;
		}
		case edt_libero089:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto089;
			break;
		}
		case edt_libero090:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto090;
			break;
		}
		case edt_libero091:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto091;
			break;
		}
		case edt_libero092:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto092;
			break;
		}
		case edt_libero093:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto093;
			break;
		}
		case edt_libero094:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto094;
			break;
		}
		case edt_libero095:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto095;
			break;
		}
		case edt_libero096:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto096;
			break;
		}
		case edt_libero097:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto097;
			break;
		}
		case edt_libero098:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto098;
			break;
		}
		case edt_libero099:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_sTesto099;
			break;
		}
		case edt_liberodataora000:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra000;
			break;
		}
		case edt_liberodataora001:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra001;
			break;
		}
		case edt_liberodataora002:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra002;
			break;
		}
		case edt_liberodataora003:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra003;
			break;
		}
		case edt_liberodataora004:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra004;
			break;
		}
		case edt_liberodataora005:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra005;
			break;
		}
		case edt_liberodataora006:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra006;
			break;
		}
		case edt_liberodataora007:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra007;
			break;
		}
		case edt_liberodataora008:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra008;
			break;
		}
		case edt_liberodataora009:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra009;
			break;
		}
		case edt_liberodataora010:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra010;
			break;
		}
		case edt_liberodataora011:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra011;
			break;
		}
		case edt_liberodataora012:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra012;
			break;
		}
		case edt_liberodataora013:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra013;
			break;
		}
		case edt_liberodataora014:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra014;
			break;
		}
		case edt_liberodataora015:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra015;
			break;
		}
		case edt_liberodataora016:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra016;
			break;
		}
		case edt_liberodataora017:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra017;
			break;
		}
		case edt_liberodataora018:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra018;
			break;
		}
		case edt_liberodataora019:
		{
			pRiga->pCampo = &m_setEsami.m_setEP.m_lDataOra019;
			break;
		}
		default:
		{
			pRiga->pCampo = NULL;
			break;
		}
	}
}

void CCronicitaPazienteDlg::FillDatiCampoScore(long lIDCampo, STRUCT_RIGA* pRiga)
{
	ASSERT((lIDCampo == EDT_PAZIENTICRONICI_SCORE_HB) || (lIDCampo == EDT_PAZIENTICRONICI_SCORE_S));

	//

	switch(lIDCampo)
	{
		case EDT_PAZIENTICRONICI_SCORE_HB:
		{
			CString sTemp = theApp.GetMessageString(IDS_SCORE_HB);
			memcpy(pRiga->szTitoloRiga, sTemp.GetBuffer(), sTemp.GetLength() + 1);
			sTemp.ReleaseBuffer();

			break;
		}
		case EDT_PAZIENTICRONICI_SCORE_S:
		{
			CString sTemp = theApp.GetMessageString(IDS_SCORE_S);
			memcpy(pRiga->szTitoloRiga, sTemp.GetBuffer(), sTemp.GetLength() + 1);
			sTemp.ReleaseBuffer();

			break;
		}
		default:
		{
			memcpy(pRiga->szTitoloRiga, "", 1);
			break;
		}
	}

	//

	pRiga->lIDCampo = lIDCampo;

	//

	pRiga->lTipoCampo = FT_SCORE;

	//

	switch(lIDCampo)
	{
		case EDT_PAZIENTICRONICI_SCORE_HB:
		{
			pRiga->pCampo = &m_setEsami.m_sPazientiCroniciScoreHB;
			break;
		}
		case EDT_PAZIENTICRONICI_SCORE_S:
		{
			pRiga->pCampo = &m_setEsami.m_sPazientiCroniciScoreS;
			break;
		}
		default:
		{
			pRiga->pCampo = NULL;
			break;
		}
	}
}

void CCronicitaPazienteDlg::FillDatiCampoFarmaco(long lIDCampo, STRUCT_RIGA* pRiga)
{
	// ASSERT();

	CString sTemp = CFarmaciPazientiCroniciSet().GetDescrizione(lIDCampo);
	memcpy(pRiga->szTitoloRiga, sTemp.GetBuffer(), sTemp.GetLength() + 1);
	sTemp.ReleaseBuffer();

	//

	pRiga->lIDCampo = lIDCampo;

	//

	pRiga->lTipoCampo = FT_FARMACO;

	//

	pRiga->pCampo = NULL;

	//

	/*
	if (m_lIDEsame <= 0)
	{
		// prendo i dati dell'esame precedente //

		long lFaseTemp = CEsamiFarmaciCroniciSet().GetFase(CEsamiSet().GetLastPatientExam(m_pEsamiView->m_pPazientiSet->m_lContatore), lIDCampo);
		if ((lFaseTemp == FARMACO_INIZIO) || (lFaseTemp == FARMACO_CONTINUA))
			pRiga->lFaseFarmaco = FARMACO_CONTINUA;
		else
			pRiga->lFaseFarmaco = FARMACO_NIENTE;
	}
	else
	{
		// prendo i dati dell'esame attuale //

		pRiga->lFaseFarmaco = CEsamiFarmaciCroniciSet().GetFase(m_lIDEsame, lIDCampo);
	}
	*/
}

void CCronicitaPazienteDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlListSn.SetRedraw(FALSE);
	m_ctrlListDx.SetRedraw(FALSE);

	// svuoto tutto e cancello tutto //

	m_lNumeroColonne = 0;
	if (m_pColonne != NULL)
	{
		delete m_pColonne;
		m_pColonne = NULL;
	}

	m_lNumeroRighe = 0;
	if (m_pRighe != NULL)
	{
		delete m_pRighe;
		m_pRighe = NULL;
	}

	m_ctrlListDx.RemoveAllCellColor();
	m_ctrlListDx.DeleteAllItems();
	while(m_ctrlListDx.GetHeaderCtrl()->GetItemCount() > 0)
		m_ctrlListDx.DeleteColumn(0);

	m_ctrlListSn.DeleteAllItems();
	while(m_ctrlListSn.GetHeaderCtrl()->GetItemCount() > 0)
		m_ctrlListSn.DeleteColumn(0);

	// conto il numero di righe e popolo l'array della struttura che conterrà i dati utili //

	CString sFilter;
	sFilter.Format("IDMalattia=%li", m_pPazientiSet->m_lIDMalattiaCronica);

	CMalattieCronicheCampiSet setMCC;
	setMCC.SetOpenFilter(sFilter);
	setMCC.SetSortRecord("Ordine, ID");
	if (setMCC.OpenRecordset("CCronicitaPazienteDlg::OnInitDialog"))
	{
		if (!setMCC.IsEOF())
		{
			while(!setMCC.IsEOF())
			{
				m_lNumeroRighe++;
				setMCC.MoveNext();
			}
			setMCC.MoveFirst();

			m_pRighe = new STRUCT_RIGA[m_lNumeroRighe];
			if (m_pRighe != NULL)
			{
				int nIndex = 0;

				while(!setMCC.IsEOF())
				{
					switch(setMCC.m_lTipoCampo)
					{
						case TIPOCAMPO_LIBERO:
						{
							FillDatiCampoLibero(setMCC.m_lIDCampo, &m_pRighe[nIndex]);
							break;
						}
						case TIPOCAMPO_SCORE:
						{
							FillDatiCampoScore(setMCC.m_lIDCampo, &m_pRighe[nIndex]);
							break;
						}
						case TIPOCAMPO_FARMACO:
						{
							FillDatiCampoFarmaco(setMCC.m_lIDCampo, &m_pRighe[nIndex]);
							break;
						}
						default:
						{
							ASSERT(FALSE);
							break;
						}
					}

					nIndex++;
					setMCC.MoveNext();
				}
			}
		}

		setMCC.CloseRecordset("CCronicitaPazienteDlg::OnInitDialog");
	}

	// riempio la lista di sinistra (quella che contiene solo i titoli delle righe) //

	m_ctrlListSn.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_ctrlListSn.InsertColumn(1, "", LVCFMT_LEFT, 0);

	// riempio la lista di destra //

	m_ctrlListDx.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_ctrlListDx.InsertColumn(1, "", LVCFMT_LEFT, 0);

	if (m_setEsami.OpenRecordset("CCronicitaPazienteDlg::OnInitDialog"))
	{
		if (!m_setEsami.IsEOF())
		{
			while(!m_setEsami.IsEOF())
			{
				m_ctrlListDx.InsertColumn(m_lNumeroColonne + 2, "", LVCFMT_LEFT, 150);
				m_lNumeroColonne++;
				m_setEsami.MoveNext();
			}

			//

			m_ctrlListDx.InsertItem(0, "");
			m_ctrlListDx.SetItemText(0, 1, theApp.GetMessageString(IDS_DATA));
			for(int i = 0; i < m_lNumeroRighe; i++)
			{
				m_ctrlListDx.InsertItem(i + 1, "");
				m_ctrlListDx.SetItemText(i + 1, 1, m_pRighe[i].szTitoloRiga);
			}
			m_ctrlListDx.InsertItem(m_ctrlListDx.GetItemCount(), ""); // immagine tasto //

			//

			if (m_pColonne != NULL)
			{
				delete m_pColonne;
				m_pColonne = NULL;
			}

			m_pColonne = new STRUCT_COLONNA[m_lNumeroColonne];

			if (m_pColonne != NULL)
			{
				m_setEsami.MoveFirst();

				int nCol = 0;

				while(!m_setEsami.IsEOF())
				{
					m_pColonne[nCol].lIDEsame = m_setEsami.m_lContatore;
					m_pColonne[nCol].bRecordSenzaAccesso = m_setEsami.m_bRecordSenzaAccesso;

					CString sTemp = CCustomDate(m_setEsami.m_lData).GetDate("%d/%m/%Y - %H:%M");
					m_ctrlListDx.SetItemText(0, nCol + 2, sTemp);

					for(int i = 0; i < m_lNumeroRighe; i++)
					{
						switch(m_pRighe[i].lTipoCampo)
						{
							case FT_NUMERICO:
							case FT_TESTOLIBERO:
							case FT_LISTAVELOCE:
							{
								sTemp = (*(CString*)m_pRighe[i].pCampo);
								m_ctrlListDx.SetItemText(i + 1, nCol + 2, sTemp);

								break;
							}
							case FT_CUSTOM_DATAORA:
							{
								sTemp = CCustomDate(*(long*)m_pRighe[i].pCampo).GetDate("%d/%m/%Y - %H:%M");
								m_ctrlListDx.SetItemText(i + 1, nCol + 2, sTemp);

								break;
							}
							case FT_CUSTOM_SOLODATA:
							{
								sTemp = CCustomDate(*(long*)m_pRighe[i].pCampo).GetDate("%d/%m/%Y");
								m_ctrlListDx.SetItemText(i + 1, nCol + 2, sTemp);

								break;
							}
							case FT_CUSTOM_SOLOORA:
							{
								sTemp = CCustomDate(*(long*)m_pRighe[i].pCampo).GetDate("%H:%M");
								m_ctrlListDx.SetItemText(i + 1, nCol + 2, sTemp);

								break;
							}
							case FT_SCORE:
							{
								sTemp = (*(CString*)m_pRighe[i].pCampo);
								sTemp.Trim();

								if (!sTemp.IsEmpty())
								{
									BOOL bNumerico = TRUE;

									for(int j = 0; j < sTemp.GetLength(); j++)
									{
										CString tempChar = sTemp.Mid(j, 1);
										if ((tempChar.Compare(".") != 0) && (tempChar.Compare(",") != 0) && (tempChar.Compare("0") != 0))
										{
											float fTemp = (float)atof(tempChar);
											if (fTemp == 0)
											{
												bNumerico = FALSE;
												break;
											}
										}
									}

									if (bNumerico)
									{
										sTemp.Replace(',','.');
										if (sTemp.Right(1).Compare(".") == 0)
											sTemp = sTemp.Left(sTemp.GetLength() - 1);

										switch(m_pRighe[i].lIDCampo)
										{
											case EDT_PAZIENTICRONICI_SCORE_HB:
											{
												double fTemp = atof(sTemp);
												if (fTemp > 4.0)
													m_ctrlListDx.AddCellColor(i + 1, nCol + 2, RGB_ATTIVITA);
												else
													m_ctrlListDx.AddCellColor(i + 1, nCol + 2, RGB_REMISSIONE);

												break;
											}
											case EDT_PAZIENTICRONICI_SCORE_S:
											{
												double fTemp = atof(sTemp);
												if (fTemp > 0.0)
													m_ctrlListDx.AddCellColor(i + 1, nCol + 2, RGB_ATTIVITA);
												else
													m_ctrlListDx.AddCellColor(i + 1, nCol + 2, RGB_REMISSIONE);

												break;
											}
											default:
											{
												ASSERT(FALSE);
												break;
											}
										}
									}

									m_ctrlListDx.SetItemText(i + 1, nCol + 2, sTemp);
								}

								break;
							}
							case FT_FARMACO:
							{
								switch(CEsamiFarmaciCroniciSet().GetFase(m_setEsami.m_lContatore, m_pRighe[i].lIDCampo))
								{
									case FARMACO_NIENTE:
									{
										m_ctrlListDx.SetItemText(i + 1, nCol + 2, "");
										break;
									}
									case FARMACO_INIZIO:
									{
										m_ctrlListDx.SetItemText(i + 1, nCol + 2, theApp.GetMessageString(IDS_FARMACO_INIZIO_ARROW));
										break;
									}
									case FARMACO_CONTINUA:
									{
										m_ctrlListDx.SetItemText(i + 1, nCol + 2, theApp.GetMessageString(IDS_FARMACO_CONTINUA_ARROW));
										break;
									}
									case FARMACO_FINE:
									{
										m_ctrlListDx.SetItemText(i + 1, nCol + 2, theApp.GetMessageString(IDS_FARMACO_FINE_ARROW));
										break;
									}
									default:
									{
										ASSERT(FALSE);
										break;
									}
								}
								break;
							}
							default:
							{
								ASSERT(FALSE);
								break;
							}
						}
					}

					m_ctrlListDx.SetItem(m_lNumeroRighe + 1, nCol + 2, LVIF_IMAGE, NULL, m_setEsami.m_bRecordSenzaAccesso ? 1 : 0, 0, 0, 0);

					nCol++;
					m_setEsami.MoveNext();
				}
			}
		}

		m_setEsami.CloseRecordset("CCronicitaPazienteDlg::OnInitDialog");
	}

	//

	m_ctrlListDx.SetItemHeight(m_ctrlListSn.GetItemHeight());

	// imposto la larghezza della colonna nella lista di sinistra (dipende se c'è la scrollbar verticale) //

	CRect rect;
	m_ctrlListSn.GetWindowRect(&rect);
	ScreenToClient(&rect);

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
	if (m_ctrlListDx.GetScrollInfo(SB_VERT, &si) && ((int)si.nPage) <= si.nMax)
		rect.right -= GetSystemMetrics(SM_CXVSCROLL);

	m_ctrlListSn.SetColumnWidth(1, rect.Width() - 4);

	//

	m_ctrlListSn.SetRedraw(TRUE);
	m_ctrlListDx.SetRedraw(TRUE);

	//

	m_ctrlListDx.EnsureColumnVisible(m_ctrlListDx.GetHeaderCtrl()->GetItemCount() - 1, FALSE);

	//

	EndWaitCursor();
}