#include "stdafx.h"
#include "Endox.h"
#include "DermoxPuntiPazienteSimpleDlg.h"

#include <io.h>
#include <math.h>

#include "DLL_Imaging\h\ImgArchive.h"

#include "AlbumConfrontoDermoxDlg.h"
#include "DiagnosiIstologicheSet.h"
#include "EsamiView.h"
#include "MaximizeDlg.h"
#include "PuntiPazienteSet.h"
#include "PuntiSediSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RAGGIO_PUNTO_1 3
#define RAGGIO_PUNTO_2 6

IMPLEMENT_DYNAMIC(CDermoxPuntiPazienteSimpleDlg, CEndoxResizableDlg)

CDermoxPuntiPazienteSimpleDlg::CDermoxPuntiPazienteSimpleDlg(CWnd* pParent, CEsamiView* pEsamiView, int iCurSelPointIndex)
	: CEndoxResizableDlg(CDermoxPuntiPazienteSimpleDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

	m_rectFrameSagoma = CRect(0, 0, 0, 0);
	m_rectPaintSagoma = CRect(0, 0, 0, 0);
	m_rectFrameZoom = CRect(0, 0, 0, 0);

	m_iCurSelPointIndex = iCurSelPointIndex;
	m_iCurSelPointX = -1;
	m_iCurSelPointY = -1;

	m_lIDSede = 0;

	// --- //

	m_nOperazione = 0;

	// --- //

	m_bFillingList = TRUE;
	m_bLoadingData = FALSE;
	m_bModified = FALSE;

	// --- //

	GetClipCursor(&m_rectOriginalClip); 
}

CDermoxPuntiPazienteSimpleDlg::~CDermoxPuntiPazienteSimpleDlg()
{
}

BEGIN_MESSAGE_MAP(CDermoxPuntiPazienteSimpleDlg, CEndoxResizableDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBnClickedBtnExit)
	// ON_BN_CLICKED(IDC_RADIO_SEL, OnBnClickedRadioSel)
	ON_BN_CLICKED(IDC_RADIO_MOV, OnBnClickedRadioMov)
	ON_BN_CLICKED(IDC_RADIO_DEL, OnBnClickedRadioDel)
	ON_BN_CLICKED(IDC_BTN_CONFRONTO, OnBnClickedBtnConfronto)
	ON_BN_CLICKED(IDC_CHECK_00, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_01, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_02, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_03, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_04, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_05, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_06, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_07, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_08, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_09, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_10, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_11, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_12, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_13, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_14, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_15, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_16, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_17, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_18, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_19, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_20, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_21, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_22, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_23, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_RADIO_00, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_01, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_02, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_03, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_04, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_05, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_06, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_07, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_08, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_09, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_10, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_11, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_12, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_13, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_14, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_15, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_16, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_17, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_18, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_19, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_20, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_21, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_22, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_23, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_24, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_25, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_26, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_27, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_28, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_29, OnBnClickedRadio)

	ON_CBN_SELCHANGE(IDC_COMBO_00, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_01, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_02, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_03, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_04, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_05, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_06, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_07, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_08, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_09, OnCbnSelchangeCombo)

	ON_EN_CHANGE(IDC_EDIT_00, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_01, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_02, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_03, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_04, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_05, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_06, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_07, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_08, OnEnChangeEdit)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_POINTS, OnLvnItemchangedListPoints)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_POINTS, OnLvnItemchangingListPoints)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_IMAGES, OnNMDblClkListImages)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

void CDermoxPuntiPazienteSimpleDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	// --- //

	DDX_Control(pDX, IDC_BTN_EXIT, m_ctrlBtnExit);

	DDX_Control(pDX, IDC_LIST_POINTS, m_ctrlListPoints);
	DDX_Control(pDX, IDC_LIST_IMAGES, m_ctrlListImages);

	DDX_Control(pDX, IDC_STATIC_SAGOMA, m_ctrlFrameSagoma);
	DDX_Control(pDX, IDC_STATIC_ZOOM, m_ctrlFrameZoom);
	DDX_Control(pDX, IDC_STATIC_SEDE1, m_ctrlFrameSede);
	DDX_Control(pDX, IDC_STATIC_SEDE2, m_ctrlStaticSede);

	DDX_Control(pDX, IDC_STATIC_56, m_ctrlStatic56);
	DDX_Control(pDX, IDC_STATIC_57, m_ctrlStatic57);
	DDX_Control(pDX, IDC_STATIC_58, m_ctrlStatic58);
	DDX_Control(pDX, IDC_RADIO_SEL, m_ctrlRadioSel);
	DDX_Control(pDX, IDC_RADIO_MOV, m_ctrlRadioMov);
	DDX_Control(pDX, IDC_RADIO_DEL, m_ctrlRadioDel);
	DDX_Control(pDX, IDC_BTN_CONFRONTO, m_ctrlBtnConfronto);

	DDX_Control(pDX, IDC_STATIC_59, m_ctrlStatic59);
	DDX_Control(pDX, IDC_CHECK_23, m_ctrlCheck23);
	DDX_Control(pDX, IDC_STATIC_60, m_ctrlStatic60);
	DDX_Control(pDX, IDC_COMBO_09, m_ctrlCombo09);
	DDX_Control(pDX, IDC_STATIC_61, m_ctrlStatic61);
	DDX_Control(pDX, IDC_EDIT_08, m_ctrlEdit08);

	// --- //

	DDX_Radio(pDX, IDC_RADIO_SEL, m_nOperazione);

	m_ctrlStatic59.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck23.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);	

	CString sSi = theApp.GetMessageString(IDS_YES);
	CString sNo = theApp.GetMessageString(IDS_NO);
	sSi.MakeUpper();
	sNo.MakeUpper();
	m_ctrlCheck23.SetWindowText(m_ctrlCheck23.GetCheck() == BST_CHECKED ? sSi : sNo);
	m_ctrlStatic60.ShowWindow(m_ctrlCheck23.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlCombo09.ShowWindow(m_ctrlCheck23.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlStatic61.ShowWindow(m_ctrlCheck23.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlEdit08.ShowWindow(m_ctrlCheck23.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);

}

void CDermoxPuntiPazienteSimpleDlg::OnCancel()
{
	if (m_nOperazione == 1)
	{
		//
		m_nOperazione = 0;
		UpdateData(FALSE);

		// sblocco il cursore //
		ClipCursor(&m_rectOriginalClip);

		// mostro la lista dei punti //
		m_ctrlListPoints.ShowWindow(SW_SHOW);

		// nascondo le etichette con le istruzioni //
		m_ctrlStatic58.ShowWindow(SW_HIDE);
	}
}

BOOL CDermoxPuntiPazienteSimpleDlg::OnInitDialog()
{
	//Julio: Scrollbar, under developtment
	GetWindowRect(m_rect);
	m_nScrollPos = 0;
	
	int nScrollMax;
	if (m_nCurHeight < m_rect.Height())
	{
		nScrollMax = m_rect.Height() - m_nCurHeight;
	}
	else
		nScrollMax = 0;

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL; // SIF_ALL = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nScrollMax;
	si.nPage = si.nMax / 10;
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si, TRUE);

	CEndoxResizableDlg::OnInitDialog();

	BOOL bOk = FALSE;

	char szPathImm[MAX_PATH];
	char szPathMin[MAX_PATH];
	if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
	{
		CString fileSagomeName = "sagome.reg";

		CString sFileSagome;
		sFileSagome.Format("%s\\Organ\\sagome.org", szPathImm);

		CString sFileSedi;
		sFileSedi.Format("%s\\Organ\\%s", szPathImm, fileSagomeName);

		if (_access(sFileSagome, 00) == 0)
		{
			if (_access(sFileSedi, 00) == 0)
			{
				HBITMAP hBit;

				if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(sFileSagome, &hBit) > 0)
					if (hBit != INVALID_HANDLE_VALUE)
						bOk = m_dibSagome.Attach(CDib::BitmapToDIB(hBit, NULL), TRUE);
				DeleteObject(hBit);

				if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(sFileSedi, &hBit) > 0)
					if (hBit != INVALID_HANDLE_VALUE)
						bOk = m_dibSedi.Attach(CDib::BitmapToDIB(hBit, NULL), TRUE);
				DeleteObject(hBit);
			}
			else
			{
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_FILE_SAGOME_NON_TROVATO), sFileSedi);
				theApp.AfxMessageBoxEndo(strError);
			}
		}
		else
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_FILE_SAGOME_NON_TROVATO), sFileSagome);
			theApp.AfxMessageBoxEndo(strError);
		}
	}
	else
	{
		ASSERT(FALSE);
	}

	if (bOk)
	{
		AddAnchor(IDC_BTN_EXIT, CSize(100, 0), CSize(100, 0));

		AddAnchor(IDC_LIST_POINTS, CSize(0, 0), CSize(100, 0));
		AddAnchor(IDC_LIST_IMAGES, CSize(100, 0), CSize(100, 0));

		AddAnchor(IDC_STATIC_SAGOMA, CSize(0, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_ZOOM, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_SEDE1, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_SEDE2, CSize(100, 0), CSize(100, 0));

		AddAnchor(IDC_STATIC_56, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_57, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_58, CSize(0, 0), CSize(50, 0));
		AddAnchor(IDC_RADIO_SEL, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_RADIO_MOV, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_RADIO_DEL, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_BTN_CONFRONTO, CSize(100, 0), CSize(100, 0));

		AddAnchor(IDC_STATIC_59, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_CHECK_23, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_60, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_COMBO_09, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_61, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_EDIT_08, CSize(100, 0), CSize(100, 0));

		//

		m_ctrlStaticSede.SetFont(&theApp.m_fontBold);
		m_ctrlBtnExit.SetFont(&theApp.m_fontBold);
		m_ctrlStaticSede.SetFont(&theApp.m_fontBold);
		m_ctrlBtnExit.SetFont(&theApp.m_fontBold);


		m_ctrlStatic57.SetFont(&theApp.m_fontBold);
		m_ctrlStatic58.SetFont(&theApp.m_fontBold);
		m_ctrlStatic59.SetFont(&theApp.m_fontBold);

		//

		//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
		SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

		//

		m_ctrlListPoints.SetExtendedStyle(m_ctrlListPoints.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
		m_ctrlListPoints.InsertColumn(0, "", LVCFMT_LEFT, 0); // empty //
		m_ctrlListPoints.InsertColumn(1, "", LVCFMT_CENTER, 30); // numero //
		m_ctrlListPoints.InsertColumn(2, "Sede", LVCFMT_LEFT, 0); // sede //
		m_ctrlListPoints.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

		//

		m_listImages.Create(HSIZE_PAL_4, VSIZE_PAL_4, ILC_COLOR32, 0, 1);
		m_ctrlListImages.SetExtendedStyle(m_ctrlListImages.GetExtendedStyle() | LVS_EX_BORDERSELECT);
		m_ctrlListImages.SetImageList(&m_listImages, LVSIL_NORMAL);
		m_ctrlListImages.SetIconSpacing(HSIZE_PAL_4 + 5, VSIZE_PAL_4 + 5);

		//
		CString strFilter;
		strFilter.Format("IDPaziente=%li", m_pEsamiView->m_pPazientiSet->m_lContatore);

		CPuntiPazienteSet setPunti;
		setPunti.SetOpenFilter(strFilter);
		if (setPunti.OpenRecordset("CDermoxPuntiPazienteSimpleDlg::OnInitDialog"))
		{
			while(!setPunti.IsEOF())
			{
				tagPuntiDermox tagTemp;
				tagTemp.lIDPunto = setPunti.m_lID;
				tagTemp.ptPunto.x = setPunti.m_lX;
				tagTemp.ptPunto.y = setPunti.m_lY;
				tagTemp.lNumeroDermox = setPunti.m_lNumeroDermox;
				sprintf_s(tagTemp.szSede, 255, "%s", setPunti.m_sSede);
				sprintf_s(tagTemp.szPattern, 255, "%s", GetTextPattern(setPunti.m_lPattern));
				tagTemp.bAsportazione = setPunti.m_bAsportazione;

				m_listPunti.AddTail(tagTemp);

				setPunti.MoveNext();
			}

			setPunti.CloseRecordset("CDermoxPuntiPazienteSimpleDlg::OnInitDialog");
		}

		//
		CPuntiSediSet setSedi;
		if (setSedi.OpenRecordset("CDermoxPuntiPazienteSimpleDlg::OnInitDialog"))
		{
			while(!setSedi.IsEOF())
			{
				tagSede tagTemp;

				tagTemp.m_lID = setSedi.m_lID;
				tagTemp.m_sSede = setSedi.m_sSede;
				tagTemp.m_sSede.MakeUpper();

				m_listSedi.AddTail(tagTemp);

				setSedi.MoveNext();
			}

			setSedi.CloseRecordset("CDermoxPuntiPazienteSimpleDlg::OnInitDialog");
		}

		RiempiCombo09();

		//

		m_ctrlListPoints.SetRedraw(FALSE);
		m_ctrlListPoints.DeleteAllItems();

		int nItem = 0;
		POSITION pos = m_listPunti.GetHeadPosition();
		while(pos != NULL)
		{
			CString strTemp;
			tagPuntiDermox tagTemp = m_listPunti.GetAt(pos);

			m_ctrlListPoints.InsertItem(nItem, "");
			m_ctrlListPoints.SetItemData(nItem, (DWORD)tagTemp.lIDPunto);

			strTemp.Format("%li", tagTemp.lNumeroDermox);
			m_ctrlListPoints.SetItemText(nItem, 1, strTemp);

			m_ctrlListPoints.SetItemText(nItem, 2, tagTemp.szSede);

			nItem++;
			m_listPunti.GetNext(pos);
		}

		m_ctrlListPoints.SetRedraw(TRUE);

		m_bFillingList = FALSE;

		if (m_iCurSelPointIndex >= 0)
		{
			m_ctrlListPoints.SetItemState(m_iCurSelPointIndex, LVIS_SELECTED, LVIS_SELECTED);
			m_ctrlListPoints.EnsureVisible(m_iCurSelPointIndex, FALSE);
		}

		//
		theApp.LocalizeDialog(this, CDermoxPuntiPazienteSimpleDlg::IDD, "DermoxPuntiPazienteSimpleDlg");
	}
	else
	{
		m_dibSagome.ReleaseContents();
		m_dibSagome.Detach();

		m_dibSedi.ReleaseContents();
		m_dibSedi.Detach();

		EndDialog(IDCANCEL);
	}

	return TRUE;
}

void CDermoxPuntiPazienteSimpleDlg::OnOK()
{
}

void CDermoxPuntiPazienteSimpleDlg::OnBnClickedBtnExit()
{
	if (m_bModified)
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SALVARE_NEVO), MB_YESNO | MB_ICONQUESTION) == IDYES)
			SalvaDatiPunto();

		m_bModified = FALSE;
	}

	CResizableDialog::OnOK();
}

/*
void CDermoxPuntiPazienteSimpleDlg::OnBnClickedRadioSel()
{
	UpdateData(TRUE);

	ClipCursor(&m_rectOriginalClip);

	m_ctrlListPoints.EnableWindow(TRUE);
}
*/

void CDermoxPuntiPazienteSimpleDlg::OnBnClickedRadioMov()
{
	UpdateData(TRUE);

	// sposto il cursore sopra al punto attualmente selezionato //
	CPoint ptTemp = ImageToScreen(CPoint(m_iCurSelPointX, m_iCurSelPointY));
	ClientToScreen(&ptTemp);
	SetCursorPos(ptTemp.x, ptTemp.y);

	// blocco il cursore nella finestra della sagoma //
	CRect rectTemp = m_rectPaintSagoma;
	ClientToScreen(&rectTemp);
	rectTemp.right--;
	rectTemp.bottom--;
	ClipCursor(&rectTemp);

	// nascondo la lista dei punti //
	m_ctrlListPoints.ShowWindow(SW_HIDE);

	// mostro le etichette con le istruzioni //
	m_ctrlStatic58.ShowWindow(SW_SHOW);

	// salvo la "vecchia" sede del punto //
	m_ctrlStaticSede.GetWindowText(m_sSedeOld);
	m_sSedeOld.Trim();
}

void CDermoxPuntiPazienteSimpleDlg::OnBnClickedRadioDel()
{
	UpdateData(TRUE);

	CString strMessage;

	CString strRegione = m_ctrlListPoints.GetItemText(m_iCurSelPointIndex, 2);
	if (strRegione.IsEmpty())
		strMessage = theApp.GetMessageString(IDS_ELIMINAPUNTO_1);
	else
		strMessage.Format(theApp.GetMessageString(IDS_ELIMINAPUNTO_2), strRegione);

	if (theApp.MessageBoxEndo(strMessage, theApp.GetMessageString(IDS_ACHTUNG), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		//
		EliminaPunto();

		// ridisegno le due dib //
		InvalidateRect(m_rectFrameSagoma, FALSE);
		InvalidateRect(m_rectFrameZoom, FALSE);

		// riaggiorno l'interfaccia //
		OnLvnItemchangedListPoints(NULL, NULL);
	}

	// rimetto in modalità "selezione" //
	UpdateData(TRUE);
	m_nOperazione = 0;
	UpdateData(FALSE);
}

void CDermoxPuntiPazienteSimpleDlg::OnBnClickedBtnConfronto()
{
	CAlbumConfrontoDermoxDlg dlg(this, m_pEsamiView, CPoint(m_iCurSelPointX, m_iCurSelPointY));
	dlg.DoModal();
}

void CDermoxPuntiPazienteSimpleDlg::OnBnClickedCheck()
{
	TRACE0("OnBnClickedCheck\n");

	if (!m_bLoadingData)
	{
		m_bModified = TRUE;
		UpdateData(TRUE);
	}
}

void CDermoxPuntiPazienteSimpleDlg::OnBnClickedRadio()
{
	TRACE0("OnBnClickedRadio\n");

	if (!m_bLoadingData)
		m_bModified = TRUE;
}

void CDermoxPuntiPazienteSimpleDlg::OnCbnSelchangeCombo()
{
	TRACE0("OnCbnSelchangeCombo\n");

	if (!m_bLoadingData)
		m_bModified = TRUE;
}

void CDermoxPuntiPazienteSimpleDlg::OnEnChangeEdit()
{
	TRACE0("OnEnChangeEdit\n");

	if (!m_bLoadingData)
		m_bModified = TRUE;
}

void CDermoxPuntiPazienteSimpleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	point.x++;
	point.y++;
	if (m_rectPaintSagoma.PtInRect(point))
	{
		point = ScreenToImage(point);

		switch(m_nOperazione)
		{
			case 1:
			{
				SpostaPunto(point);
				break;
			}
			case 2:
			{
				// eliminazione //
				break;
			}
			default:
			{
				SelezionaPunto(point);
				break;
			}
		}
	}
}

void CDermoxPuntiPazienteSimpleDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CEndoxResizableDlg::OnMouseMove(nFlags, point);

	// calcolo l'area del rect di zoom //
	InvalidateRect(m_rectFrameZoom, FALSE);
}

void CDermoxPuntiPazienteSimpleDlg::OnLvnItemchangedListPoints(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (!m_bFillingList)
	{
		BeginWaitCursor();

		POSITION pos1 = m_ctrlListPoints.GetFirstSelectedItemPosition();
		if (pos1 != NULL)
		{
			m_iCurSelPointIndex = m_ctrlListPoints.GetNextSelectedItem(pos1);

			POSITION pos2 = m_listPunti.FindIndex(m_iCurSelPointIndex);
			m_iCurSelPointX = m_listPunti.GetAt(pos2).ptPunto.x;
			m_iCurSelPointY = m_listPunti.GetAt(pos2).ptPunto.y;

			InvalidateRect(m_rectFrameSagoma, FALSE);
			InvalidateRect(m_rectFrameZoom, FALSE);

			m_ctrlRadioMov.EnableWindow(TRUE);
			m_ctrlRadioDel.EnableWindow(TRUE);
		}
		else
		{
			m_iCurSelPointIndex = -1;

			m_iCurSelPointX = -1;
			m_iCurSelPointY = -1;

			InvalidateRect(m_rectFrameSagoma, FALSE);
			InvalidateRect(m_rectFrameZoom, FALSE);

			m_ctrlRadioMov.EnableWindow(FALSE);
			m_ctrlRadioDel.EnableWindow(FALSE);
		}

		CaricaDatiPunto();
		CaricaImmaginiPunto();

		EndWaitCursor();
	}
}

void CDermoxPuntiPazienteSimpleDlg::OnLvnItemchangingListPoints(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if ((m_iCurSelPointIndex >= 0) && m_bModified)
	{
		if (((pNMLV->uOldState == LVIS_FOCUSED || pNMLV->uOldState == LVIS_SELECTED)) && (pNMLV->uNewState != pNMLV->uOldState))
		{
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SALVARE_NEVO), MB_YESNO | MB_ICONQUESTION) == IDYES)
				SalvaDatiPunto();
		}
	}
	m_bModified = FALSE;

	*pResult = 0;
}

void CDermoxPuntiPazienteSimpleDlg::OnNMDblClkListImages(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListImages.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlListImages.GetNextSelectedItem(pos);
		long lIDImmagine = (long)m_ctrlListImages.GetItemData(iCurSel);

		if (lIDImmagine > 0)
		{
			BeginWaitCursor();
			HBITMAP hTemp = m_pEsamiView->m_pImgManager->GetImg(lIDImmagine, FALSE, FALSE, FALSE);
			EndWaitCursor();

			if (hTemp != NULL)
			{
				CDib dibTemp;
				dibTemp.Attach(CDib::BitmapToDIB(hTemp, NULL), TRUE);

				CMaximizeDlg dlgTemp(this, &dibTemp);
				dlgTemp.DoModal();

				DeleteObject(hTemp);
			}
		}
	}
}

void CDermoxPuntiPazienteSimpleDlg::OnPaint() 
{
	CPaintDC dc(this);

	///////////////////
	// SAGOMA GRANDE //
	///////////////////

	// disegno la dib //

	if (m_nScrollPos != 0)
		return;
	m_rectPaintSagoma = m_dibSagome.PaintDIBSagome(&dc, m_rectFrameSagoma);
	// TRACE("   SAGOME IN L%04li R%04li T%04li B%04li\n", m_rectSagoma.left, m_rectSagoma.right, m_rectSagoma.top, m_rectSagoma.bottom);

	/////////////////////////
	// PUNTI SAGOMA GRANDE //
	/////////////////////////

	CPen penSel(PS_SOLID, 1, RGB_RED);
	CBrush brushSel(RGB_RED);
	CPen penNormal(PS_SOLID, 1, RGB_BLUE);
	CBrush brushNormal(RGB_BLUE);
	CPen penAsportaz(PS_SOLID, 1, RGB_BLACK);
	CBrush brushAsportaz(RGB_BLACK);
	COLORREF crOldColor;

	dc.SetBkMode(TRANSPARENT);

	int i = 0;
	POSITION pos = m_listPunti.GetHeadPosition();
	while(pos != NULL)
	{
		CPen* pOldPen;
		CBrush* pOldBrush;
		if (i == m_iCurSelPointIndex)
		{
			pOldPen = dc.SelectObject(&penSel);
			pOldBrush = dc.SelectObject(&brushSel);
			crOldColor = dc.SetTextColor(RGB_RED);
		}
		else
		{
			if (m_listPunti.GetAt(pos).bAsportazione)
			{
				pOldPen = dc.SelectObject(&penAsportaz);
				pOldBrush = dc.SelectObject(&brushAsportaz);
				crOldColor = dc.SetTextColor(RGB_BLACK);
			}
			else
			{
				pOldPen = dc.SelectObject(&penNormal);
				pOldBrush = dc.SelectObject(&brushNormal);
				crOldColor = dc.SetTextColor(RGB_BLUE);
			}
		}

		CPoint ptToPaint = m_listPunti.GetAt(pos).ptPunto;
		ptToPaint = ImageToScreen(ptToPaint);

		CRect rectTemp(ptToPaint.x - RAGGIO_PUNTO_1, ptToPaint.y - RAGGIO_PUNTO_1, ptToPaint.x + RAGGIO_PUNTO_1, ptToPaint.y + RAGGIO_PUNTO_1);

		dc.Ellipse(rectTemp);

		if (theApp.m_bNumeriSuImmagineSagoma)
		{
			CString sTemp;
			sTemp.Format("%li", m_listPunti.GetAt(pos).lNumeroDermox);

			CFont* pOldFont = dc.SelectObject(&theApp.m_fontBold);
			int nOldBkMode = dc.SetBkMode(OPAQUE);
			dc.TextOut(ptToPaint.x + 4, ptToPaint.y - 9, sTemp);
			dc.SetBkMode(nOldBkMode);
			dc.SelectObject(pOldFont);
		}

		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);
		dc.SetTextColor(crOldColor);

		m_listPunti.GetNext(pos);
		i++;
	}

	/////////////////////////
	// FINESTRELLA DI ZOOM //
	/////////////////////////

	// disegno	nella finestra di zoom //
	RECT rectPaintZoom = { 0, 0, 0, 0 };
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(&ptMouse);
	ptMouse.x++;
	ptMouse.y++;
	if (m_rectPaintSagoma.PtInRect(ptMouse) && m_nScrollPos == 0)
	{
		// se sono sulla sagoma faccio lo zoom intorno al cursore //

		// TRACE2("   CURSOR IN    X%04li       Y%04li\n", ptMouse.x, ptMouse.y);
		POINT ptToZoom;
		ptToZoom.x = ptMouse.x - m_rectPaintSagoma.left;
		ptToZoom.x = ptToZoom.x * m_dibSagome.Width() / m_rectPaintSagoma.Width();
		ptToZoom.y = ptMouse.y - m_rectPaintSagoma.top;
		ptToZoom.y = ptToZoom.y * m_dibSagome.Height() / m_rectPaintSagoma.Height();
		ptToZoom.y = m_dibSagome.Height() - ptToZoom.y;
		// TRACE2("   CURSOR IN   (X%04li)     (Y%04li)\n", ptToZoom.x, ptToZoom.y);

		rectPaintZoom = m_dibSagome.PaintDIBSagomeZoom(&dc, m_rectFrameZoom, ptToZoom);
		LONG lTeeemp = rectPaintZoom.top;
		rectPaintZoom.top = m_dibSagome.Height() - rectPaintZoom.bottom;
		rectPaintZoom.bottom = m_dibSagome.Height() - lTeeemp;
		// TRACE("    ZOOM  IN L%04li R%04li T%04li B%04li\n\n", rectPaintZoom.left, rectPaintZoom.right, rectPaintZoom.top, rectPaintZoom.bottom);

		///////////////////
		// TESTO REGIONE //
		///////////////////

		BYTE bytePixel;
		m_dibSedi.GetPixel(ptToZoom.x, ptToZoom.y, &bytePixel);

		if ((long)bytePixel != m_lIDSede)
		{
			CString strSede = "";
			m_lIDSede = (long)bytePixel;

			if ((m_lIDSede > 0) && (m_lIDSede < 255))
			{
				POSITION pos = m_listSedi.GetHeadPosition();

				while(pos != NULL)
				{
					tagSede tagTemp = m_listSedi.GetNext(pos);

					if (tagTemp.m_lID == m_lIDSede)
					{
						strSede = tagTemp.m_sSede;
						break;
					}
				}
			}

			m_ctrlStaticSede.SetWindowText(strSede);
		}
	}
	else
	{
		if ((m_iCurSelPointIndex >= 0) && (m_iCurSelPointX >= 0) && (m_iCurSelPointY >= 0))
		{
			// se sono fuori dalla sagoma ma c'è un punto selezionato ci faccio lo zoom attorno //

			POINT ptToZoom;
			ptToZoom.x = m_iCurSelPointX;
			ptToZoom.y = m_iCurSelPointY;
			ptToZoom.y = m_dibSagome.Height() - ptToZoom.y;

			rectPaintZoom = m_dibSagome.PaintDIBSagomeZoom(&dc, m_rectFrameZoom, ptToZoom);
			LONG lTeeemp = rectPaintZoom.top;
			rectPaintZoom.top = m_dibSagome.Height() - rectPaintZoom.bottom;
			rectPaintZoom.bottom = m_dibSagome.Height() - lTeeemp;
			// TRACE("    ZOOM  IN L%04li R%04li T%04li B%04li\n\n", rectPaintZoom.left, rectPaintZoom.right, rectPaintZoom.top, rectPaintZoom.bottom);

			///////////////////
			// TESTO REGIONE //
			///////////////////

			BYTE bytePixel;
			m_dibSedi.GetPixel(ptToZoom.x, ptToZoom.y, &bytePixel);
			// TRACE3("   GETPIX IN X%04li %04li) --> \n", ptToZoom.x, ptToZoom.y);

			if ((long)bytePixel != m_lIDSede)
			{
				CString strSede = "";
				m_lIDSede = (long)bytePixel;

				if ((m_lIDSede > 0) && (m_lIDSede < 255))
				{
					POSITION pos = m_listSedi.GetHeadPosition();

					while(pos != NULL)
					{
						tagSede tagTemp = m_listSedi.GetNext(pos);

						if (tagTemp.m_lID == m_lIDSede)
						{
							strSede = tagTemp.m_sSede;
							break;
						}
					}
				}

				m_ctrlStaticSede.SetWindowText(strSede);
			}
		}
		else
		{
			// se sono fuori dalla sagoma e non c'è un punto selezionato svuoto la finestra di zoom //

			CBrush brushNull;
			brushNull.CreateSolidBrush(RGB_BLACK);
			dc.FillRect(m_rectFrameZoom, &brushNull);
			brushNull.DeleteObject();

			///////////////////
			// TESTO REGIONE //
			///////////////////

			m_lIDSede = 0;
			m_ctrlStaticSede.SetWindowText("");
		}
	}

	///////////////////////////////
	// PUNTI FINESTRELLA DI ZOOM //
	///////////////////////////////

	dc.SetBkMode(TRANSPARENT);

	i = 0;
	pos = m_listPunti.GetHeadPosition();
	while(pos != NULL)
	{
		CPoint ptToPaint = m_listPunti.GetAt(pos).ptPunto;
		if (CRect(rectPaintZoom).PtInRect(ptToPaint))
		{
			CPen* pOldPen;
			CBrush* pOldBrush;
			if (i == m_iCurSelPointIndex)
			{
				pOldPen = dc.SelectObject(&penSel);
				pOldBrush = dc.SelectObject(&brushSel);
				crOldColor = dc.SetTextColor(RGB_RED);
			}
			else
			{
				if (m_listPunti.GetAt(pos).bAsportazione)
				{
					pOldPen = dc.SelectObject(&penAsportaz);
					pOldBrush = dc.SelectObject(&brushAsportaz);
					crOldColor = dc.SetTextColor(RGB_BLACK);
				}
				else
				{
					pOldPen = dc.SelectObject(&penNormal);
					pOldBrush = dc.SelectObject(&brushNormal);
					crOldColor = dc.SetTextColor(RGB_BLUE);
				}
			}

			ptToPaint = ImageToScreenZoom(ptToPaint, rectPaintZoom);

			CRect rectTemp(ptToPaint.x - RAGGIO_PUNTO_2, ptToPaint.y - RAGGIO_PUNTO_2, ptToPaint.x + RAGGIO_PUNTO_2, ptToPaint.y + RAGGIO_PUNTO_2);

			dc.Ellipse(rectTemp);

			if (theApp.m_bNumeriSuImmagineSagoma)
			{
				CString sTemp;
				sTemp.Format("%li", m_listPunti.GetAt(pos).lNumeroDermox);

				CFont* pOldFont = dc.SelectObject(&theApp.m_fontBigBig);
				int nOldBkMode = dc.SetBkMode(TRANSPARENT);
				dc.TextOut(ptToPaint.x + 6, ptToPaint.y - 13, sTemp);
				dc.SetBkMode(nOldBkMode);
				dc.SelectObject(pOldFont);
			}

			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBrush);
			dc.SetTextColor(crOldColor);
		}

		m_listPunti.GetNext(pos);
		i++;
	}
	penSel.DeleteObject();
	brushSel.DeleteObject();
	penNormal.DeleteObject();
	brushNormal.DeleteObject();
}

void CDermoxPuntiPazienteSimpleDlg::OnSize(UINT nType, int cx, int cy) 
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);

	m_nCurHeight = cy;

	if (IsWindow(m_ctrlFrameSagoma))
	{
		m_ctrlFrameSagoma.GetWindowRect(&m_rectFrameSagoma);
		ScreenToClient(&m_rectFrameSagoma);
	}

	if (IsWindow(m_ctrlFrameZoom))
	{
		m_ctrlFrameZoom.GetWindowRect(&m_rectFrameZoom);
		ScreenToClient(&m_rectFrameZoom);
	}
}

CPoint CDermoxPuntiPazienteSimpleDlg::ImageToScreen(CPoint ptPoint)
{
	CPoint ptReturn;

	ptReturn.x = ptPoint.x * m_rectPaintSagoma.Width() / m_dibSagome.Width();
	ptReturn.x = ptReturn.x + m_rectPaintSagoma.left;
	ptReturn.y = ptPoint.y * m_rectPaintSagoma.Height() / m_dibSagome.Height();
	ptReturn.y = ptReturn.y + m_rectPaintSagoma.top;

	return ptReturn;
}

CPoint CDermoxPuntiPazienteSimpleDlg::ImageToScreenZoom(CPoint ptPoint, CRect rectImageZoom)
{
	CPoint ptReturn;

	ptReturn.x = ((ptPoint.x - rectImageZoom.left) * m_rectFrameZoom.Width() / rectImageZoom.Width()) + m_rectFrameZoom.left;
	ptReturn.y = ((ptPoint.y - rectImageZoom.top) * m_rectFrameZoom.Height() / rectImageZoom.Height()) + m_rectFrameZoom.top;

	return ptReturn;
}

CPoint CDermoxPuntiPazienteSimpleDlg::ScreenToImage(CPoint ptPoint)
{
	CPoint ptReturn;

	ptReturn.x = ptPoint.x - m_rectPaintSagoma.left;
	ptReturn.x = ptReturn.x * m_dibSagome.Width() / m_rectPaintSagoma.Width();
	ptReturn.y = ptPoint.y - m_rectPaintSagoma.top;
	ptReturn.y = ptReturn.y * m_dibSagome.Height() / m_rectPaintSagoma.Height();

	return ptReturn;
}

void CDermoxPuntiPazienteSimpleDlg::CaricaDatiPunto()
{
	// ID del punto //
	long lIDPunto = 0;
	if (m_iCurSelPointIndex >= 0)
		lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

	BOOL bResetData = TRUE;
	if (lIDPunto > 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", lIDPunto);

		CPuntiPazienteSet setPP;
		setPP.SetOpenFilter(strFilter);
		if (setPP.OpenRecordset("CDermoxPuntiPazienteSimpleDlg::CaricaDatiPunto"))
		{
			if (!setPP.IsEOF())
			{
				m_bLoadingData = TRUE;
				
				m_ctrlCheck23.SetCheck(setPP.m_bAsportazione ? BST_CHECKED : BST_UNCHECKED);
				m_ctrlCombo09.SetCurSel(0);
				if (setPP.m_lDiagnosiIstologica > 0)
				{
					for (int i = 1; i < m_ctrlCombo09.GetCount(); i++)
					{
						if (m_ctrlCombo09.GetItemData(i) == setPP.m_lDiagnosiIstologica)
						{
							m_ctrlCombo09.SetCurSel(i);
							break;
						}
					}
				}
				m_ctrlEdit08.SetWindowText(setPP.m_sNotizieAccessorie);
				
				bResetData = FALSE;
				m_bLoadingData = FALSE;
			}

			setPP.CloseRecordset("CDermoxPuntiPazienteSimpleDlg::CaricaDatiPunto");
		}
	}

	if (bResetData)
	{
		m_bLoadingData = TRUE;

		m_ctrlCheck23.SetCheck(BST_UNCHECKED);
		m_ctrlCombo09.SetCurSel(0);
		m_ctrlEdit08.SetWindowText("");

		m_bLoadingData = FALSE;
	}

	UpdateData(FALSE);
}

void CDermoxPuntiPazienteSimpleDlg::CaricaImmaginiPunto()
{
	// ID del punto //
	long lIDPunto = 0;
	if (m_iCurSelPointIndex >= 0)
		lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

	if (lIDPunto > 0)
	{
		// lista delle immagini di quel punto //
		CImgList listImg;
		int nImageCount = m_pEsamiView->m_pImgManager->GetImgListByPoint(m_pEsamiView->m_pEsamiSet->m_lPaziente, lIDPunto, &listImg);

		// reimposto la lista di immagini ed il relativo controllo //
		m_listImages.SetImageCount(nImageCount);
		m_ctrlListImages.DeleteAllItems();

		// riempio di nuovo tutto //
		for(int i = 0; i < nImageCount; i++)
		{
			IMG img = listImg.GetAt(listImg.FindIndex(i));

			m_listImages.Replace(i, CBitmap::FromHandle(img.hBmp), RGB(0, 0, 0));
			m_ctrlListImages.InsertItem(i, CEsamiSet().GetDataEsame(img.lIDEsame), i);
			m_ctrlListImages.SetItemData(i, (DWORD)img.lID);

			DeleteObject(img.hBmp);
			DeleteObject(img.hBmpSelected);
		}
	}
	else
	{
		m_listImages.SetImageCount(0);
		m_ctrlListImages.DeleteAllItems();
	}

	m_ctrlBtnConfronto.EnableWindow(m_ctrlListImages.GetItemCount() > 1);
}

void CDermoxPuntiPazienteSimpleDlg::EliminaPunto()
{
	// ID del punto //
	long lIDPunto = 0;
	if (m_iCurSelPointIndex >= 0)
		lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

	if (lIDPunto > 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", lIDPunto);

		CPuntiPazienteSet setPP;
		setPP.SetOpenFilter(strFilter);
		if (setPP.OpenRecordset("CDermoxPuntiPazienteSimpleDlg::EliminaPunto"))
		{
			if (!setPP.IsEOF())
			{
				if (setPP.DeleteRecordset("CDermoxPuntiPazienteSimpleDlg::EliminaPunto"))
				{
					int iTempCSPI = m_iCurSelPointIndex;

					// deseleziono tutti i punti //
					m_iCurSelPointIndex = -1;

					// rimuovo il punto dalla lista //
					m_listPunti.RemoveAt(m_listPunti.FindIndex(iTempCSPI));

					// rimuovo l'item dal controllo //
					m_ctrlListPoints.DeleteItem(iTempCSPI);
				}
			}

			setPP.CloseRecordset("CDermoxPuntiPazienteSimpleDlg::EliminaPunto");
		}
	}
}

void CDermoxPuntiPazienteSimpleDlg::RiempiCombo09()
{
	m_ctrlCombo09.ResetContent();

	m_ctrlCombo09.InsertString(0, "");
	m_ctrlCombo09.SetItemData(0, 0);

	int nIndex = 1;

	CDiagnosiIstologicheSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CDermoxPuntiPazienteDlg::RiempiCombo09"))
	{
		while (!setTemp.IsEOF())
		{
			m_ctrlCombo09.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlCombo09.SetItemData(nIndex, setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CDermoxPuntiPazienteDlg::RiempiCombo09");
	}

	m_ctrlCombo09.SetCurSel(0);
}

void CDermoxPuntiPazienteSimpleDlg::SalvaDatiPunto()
{
	// ID del punto //
	long lIDPunto = 0;
	if (m_iCurSelPointIndex >= 0)
		lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

	BOOL bResetData = TRUE;
	if (lIDPunto > 0)
	{
		UpdateData(TRUE);

		CString strFilter;
		strFilter.Format("ID=%li", lIDPunto);

		CPuntiPazienteSet setPP;
		setPP.SetOpenFilter(strFilter);
		if (setPP.OpenRecordset("CDermoxPuntiPazienteSimpleDlg::CaricaDatiPunto"))
		{
			if (!setPP.IsEOF())
			{
				if (setPP.EditRecordset("CDermoxPuntiPazienteSimpleDlg::CaricaDatiPunto"))
				{
					
					setPP.m_bAsportazione = (m_ctrlCheck23.GetCheck() == BST_CHECKED);
					if (m_ctrlCombo09.GetCurSel() > 0)
						setPP.m_lDiagnosiIstologica = m_ctrlCombo09.GetItemData(m_ctrlCombo09.GetCurSel());
					else
						setPP.m_lDiagnosiIstologica = 0;
					m_ctrlEdit08.GetWindowText(setPP.m_sNotizieAccessorie);

					
					if (setPP.UpdateRecordset("CDermoxPuntiPazienteSimpleDlg::CaricaDatiPunto"))
					{
						CString strTemp;
						
						//
						tagPuntiDermox tagTemp = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex));
						sprintf_s(tagTemp.szPattern, 255, "%s", strTemp);
						tagTemp.bAsportazione = (m_ctrlCheck23.GetCheck() == BST_CHECKED);
						m_listPunti.SetAt(m_listPunti.FindIndex(m_iCurSelPointIndex), tagTemp);

						//
						m_ctrlListPoints.SetItemText(m_iCurSelPointIndex, 3, strTemp);
						m_ctrlListPoints.SetItemText(m_iCurSelPointIndex, 4, tagTemp.bAsportazione ? theApp.GetMessageString(IDS_YES) : theApp.GetMessageString(IDS_NO));
					}
				}
			}

			setPP.CloseRecordset("CDermoxPuntiPazienteSimpleDlg::CaricaDatiPunto");
		}
	}
}

void CDermoxPuntiPazienteSimpleDlg::SelezionaPunto(CPoint ptPoint)
{
	BeginWaitCursor();

	int nIndex = TrovaPunto(ptPoint);
	if (nIndex >= 0)
	{
		if (nIndex != m_iCurSelPointIndex)
		{
			m_iCurSelPointIndex = nIndex; // il punto esiste già, mi basta soltanto selezionarlo //
			m_iCurSelPointX = ptPoint.x;
			m_iCurSelPointY = ptPoint.y;

			InvalidateRect(m_rectFrameSagoma, FALSE);
			InvalidateRect(m_rectFrameZoom, FALSE);

			//
			for(int i = 0; i < m_ctrlListPoints.GetItemCount(); i++)
			{
				if (i == nIndex)
				{
					m_ctrlListPoints.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
					m_ctrlListPoints.EnsureVisible(i, FALSE);
				}
				else
				{
					m_ctrlListPoints.SetItemState(i, 0, LVIS_SELECTED);
				}
			}
			// OnLvnItemchangedListPoints(NULL, NULL);
		}
	}

	EndWaitCursor();
}

void CDermoxPuntiPazienteSimpleDlg::SpostaPunto(CPoint ptPoint)
{
	BeginWaitCursor();

	int nIndex = TrovaPunto(ptPoint);
	if (nIndex < 0)
	{
		// significa che NON ho cliccato sopra ad un altro punto, altrimenti poi i due punti si confonderebbero //

		// salvo la "nuova" sede del punto //
		m_ctrlStaticSede.GetWindowText(m_sSedeNew);
		m_sSedeNew.Trim();

		// chiedo conferma prima di spostare per davvero //
		CString strMessage;
		strMessage = theApp.GetMessageString(IDS_SPOSTARE_LA_NEOFORMAZIONE);
		if (!m_sSedeOld.IsEmpty())
		{
			strMessage += " " + theApp.GetMessageString(IDS_DALLA_REGIONE) + " " + m_sSedeOld;

			if (!m_sSedeNew.IsEmpty())
				strMessage += " " + theApp.GetMessageString(IDS_ALLA_REGIONE) + " " + m_sSedeNew;
			else
				strMessage += " " + theApp.GetMessageString(IDS_ALLA_NUOVA_POSIZIONE);
		}
		else
		{
			if (!m_sSedeNew.IsEmpty())
				strMessage += " " + theApp.GetMessageString(IDS_NELLA_REGIONE) + " " + m_sSedeNew;
		}
		strMessage += "?";

		// sblocco il cursore //
		ClipCursor(&m_rectOriginalClip);

		//
		if (theApp.AfxMessageBoxEndo(strMessage, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			// ID del punto //
			long lIDPunto = 0;
			if (m_iCurSelPointIndex >= 0)
				lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

			if (lIDPunto > 0)
			{
				CString strFilter;
				strFilter.Format("ID=%li", lIDPunto);

				CPuntiPazienteSet setPP;
				setPP.SetOpenFilter(strFilter);
				if (setPP.OpenRecordset("CDermoxPuntiPazienteSimpleDlg::SpostaPunto"))
				{
					if (!setPP.IsEOF())
					{
						if (setPP.EditRecordset("CDermoxPuntiPazienteSimpleDlg::SpostaPunto"))
						{
							setPP.m_lX = ptPoint.x;
							setPP.m_lY = ptPoint.y;
							setPP.m_sSede = m_sSedeNew;
							
							if (setPP.UpdateRecordset("CDermoxPuntiPazienteSimpleDlg::SpostaPunto"))
							{
								// modifico il punto nella lista //
								POSITION posTemp = m_listPunti.FindIndex(m_iCurSelPointIndex);
								if (posTemp != NULL)
								{
									tagPuntiDermox tagTemp = m_listPunti.GetAt(posTemp);

									tagTemp.ptPunto = ptPoint;
									sprintf_s(tagTemp.szSede, 255, "%s", m_sSedeNew);

									m_listPunti.SetAt(posTemp, tagTemp);
								}

								// modifico l'item nel controllo //
								m_ctrlListPoints.SetItemText(m_iCurSelPointIndex, 2, m_sSedeNew);

								//
								m_iCurSelPointX = ptPoint.x;
								m_iCurSelPointY = ptPoint.y;

								//
								InvalidateRect(m_rectFrameSagoma, FALSE);
								InvalidateRect(m_rectFrameZoom, FALSE);

								//
								OnCancel();
							}
						}

					}

					setPP.CloseRecordset("CDermoxPuntiPazienteSimpleDlg::SpostaPunto");
				}
			}
		}
		else
		{
			// blocco il cursore nella finestra della sagoma //
			CRect rectTemp = m_rectPaintSagoma;
			ClientToScreen(&rectTemp);
			rectTemp.right--;
			rectTemp.bottom--;
			ClipCursor(&rectTemp);
		}
	}
	else
	{
		// sblocco il cursore //
		ClipCursor(&m_rectOriginalClip);

		//
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PUNTO_SOPRA_PUNTO));

		// blocco il cursore nella finestra della sagoma //
		CRect rectTemp = m_rectPaintSagoma;
		ClientToScreen(&rectTemp);
		rectTemp.right--;
		rectTemp.bottom--;
		ClipCursor(&rectTemp);
	}

	EndWaitCursor();
}

int CDermoxPuntiPazienteSimpleDlg::TrovaPunto(CPoint& ptPoint)
{
	int nIndex = 0;

	POSITION pos = m_listPunti.GetHeadPosition();
	while(pos != NULL)
	{
		CPoint ptTemp = m_listPunti.GetAt(pos).ptPunto;

		if (sqrt(pow((double)(ptPoint.x - ptTemp.x), 2) + pow((double)(ptPoint.y - ptTemp.y), 2)) <= RAGGIO_PUNTO_1)
		{
			ptPoint = ptTemp;
			return nIndex;
		}

		m_listPunti.GetNext(pos);
		nIndex++;
	}

	return -1;
}

void CDermoxPuntiPazienteSimpleDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//Add screen resolution condition
	return;

	int nDelta;
	int nMaxPos = m_rect.Height() - m_nCurHeight;
	switch (nSBCode)
	{
		case SB_LINEDOWN: case SB_PAGEDOWN:
			if (m_nScrollPos >= nMaxPos)
				nDelta = min(nMaxPos / 5, nMaxPos - m_nScrollPos) + 150;
			else
				nDelta = min(nMaxPos / 5, nMaxPos - m_nScrollPos);
			break;

		case SB_LINEUP: case SB_PAGEUP:
			if (m_nScrollPos >= nMaxPos)
				nDelta = -min(nMaxPos / 5, m_nScrollPos) - 150;
			else
				nDelta = -min(nMaxPos / 5, m_nScrollPos);
			break;

		case SB_THUMBPOSITION:
			nDelta = (int)nPos - m_nScrollPos;
			break;
		
		default:
			return;
	}
	m_nScrollPos += nDelta;
	SetScrollPos(SB_VERT, m_nScrollPos, TRUE);

	ScrollWindow(0, -nDelta);

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	//CEndoxResizableDlg::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL CDermoxPuntiPazienteSimpleDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if (zDelta == -120)
	{
		CDermoxPuntiPazienteSimpleDlg::OnVScroll(SB_PAGEDOWN, 0, NULL);
		return TRUE;
	}
	else if (zDelta == 120)
	{
		CDermoxPuntiPazienteSimpleDlg::OnVScroll(SB_PAGEUP, 0, NULL);
		return TRUE;
	}
	else
		return TRUE;

	CDialog::OnMouseWheel(nFlags, zDelta, pt);

	return CEndoxResizableDlg::OnMouseWheel(nFlags, zDelta, pt);
}
