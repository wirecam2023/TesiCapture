#include "stdafx.h"
#include "Endox.h"
#include "ImmToPathoxDlg.h"

#include "AnatomiaPatologicaImmSet.h"
#include "EsamiView.h"
#include "LogFileWriter.h"
#include "MmSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CImmToPathoxDlg, CResizableDialog)

CImmToPathoxDlg::CImmToPathoxDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CResizableDialog(CImmToPathoxDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	m_pEsamiView = pEsamiView;
}

CImmToPathoxDlg::~CImmToPathoxDlg()
{
	SvuotaImgList(&m_imglistNo);
	SvuotaImgList(&m_imglistSi);
}

BEGIN_MESSAGE_MAP(CImmToPathoxDlg, CResizableDialog)

	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_BTN_NO, OnBnClickedBtnNo)
	ON_BN_CLICKED(IDC_BTN_NOTUTTI, OnBnClickedBtnNoTutti)
	ON_BN_CLICKED(IDC_BTN_SI, OnBnClickedBtnSi)
	ON_BN_CLICKED(IDC_BTN_SITUTTI, OnBnClickedBtnSiTutti)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_NO, OnLvnItemchangedListNo)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SI, OnLvnItemchangedListSi)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NO, OnNMDblclkListNo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SI, OnNMDblclkListSi)

END_MESSAGE_MAP()

void CImmToPathoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_NO, m_ctrlStaticNo);
	DDX_Control(pDX, IDC_LIST_NO, m_ctrlListNo);
	DDX_Control(pDX, IDC_BTN_SITUTTI, m_ctrlBtnSiTutti);
	DDX_Control(pDX, IDC_BTN_SI, m_ctrlBtnSi);
	DDX_Control(pDX, IDC_BTN_NO, m_ctrlBtnNo);
	DDX_Control(pDX, IDC_BTN_NOTUTTI, m_ctrlBtnNoTutti);
	DDX_Control(pDX, IDC_STATIC_SI, m_ctrlStaticSi);
	DDX_Control(pDX, IDC_LIST_SI, m_ctrlListSi);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
}

void CImmToPathoxDlg::OnCancel()
{
	CResizableDialog::OnCancel();
}

BOOL CImmToPathoxDlg::OnInitDialog()
{
	CResizableDialog::OnInitDialog();

	// ancoro i controlli //
	AddAnchor(IDC_STATIC_NO, CSize(0, 0), CSize(50, 0));
	AddAnchor(IDC_LIST_NO, CSize(0, 0), CSize(50, 100));
	AddAnchor(IDC_BTN_SITUTTI, CSize(50, 50), CSize(50, 50));
	AddAnchor(IDC_BTN_SI, CSize(50, 50), CSize(50, 50));
	AddAnchor(IDC_BTN_NO, CSize(50, 50), CSize(50, 50));
	AddAnchor(IDC_BTN_NOTUTTI, CSize(50, 50), CSize(50, 50));
	AddAnchor(IDC_STATIC_SI, CSize(50, 0), CSize(100, 0));
	AddAnchor(IDC_LIST_SI, CSize(50, 0), CSize(100, 100));
	AddAnchor(IDCANCEL, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDOK, CSize(50, 100), CSize(50, 100));

	// apro la finestra a tutto schermo //
	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	// preparo le CImageList //
	m_imagelistNo.Create(HSIZE_PAL_4, VSIZE_PAL_4, ILC_COLOR32, 0, 1);
	m_imagelistSi.Create(HSIZE_PAL_4, VSIZE_PAL_4, ILC_COLOR32, 0, 1);

	// preparo i controlli che conterranno le immagini //
	m_ctrlListNo.SetExtendedStyle(m_ctrlListNo.GetExtendedStyle() | LVS_EX_BORDERSELECT);
	m_ctrlListNo.SetImageList(&m_imagelistNo, LVSIL_NORMAL);
	m_ctrlListSi.SetExtendedStyle(m_ctrlListSi.GetExtendedStyle() | LVS_EX_BORDERSELECT);
	m_ctrlListSi.SetImageList(&m_imagelistSi, LVSIL_NORMAL);

	// carico le immagini //
	CaricaTutteLeImmagini();

	// localizzo la finestra //
	theApp.LocalizeDialog(this, CImmToPathoxDlg::IDD, "ImmToPathoxDlg");

	//
	return TRUE;
}

void CImmToPathoxDlg::OnOK()
{
	CString strFilter;
	strFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	CAnatomiaPatologicaImmSet setTemp;
	setTemp.SetOpenFilter(strFilter);
	if (setTemp.OpenRecordset("CImmToPathoxDlg::OnOK"))
	{
		// prima cancello tutti i vecchi //
		while(!setTemp.IsEOF())
		{
			setTemp.DeleteRecordset("CImmToPathoxDlg::OnOK");
			setTemp.MoveNext();
		}

		// poi aggiungo tutti i nuovi //

		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

		while(m_listIDSi.GetCount() > 0)
		{
			if (setTemp.AddNewRecordset("CImmToPathoxDlg::OnOK"))
			{
				setTemp.m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
				setTemp.m_sPercorso = m_pEsamiView->m_pImgManager->GetFullPath(m_listIDSi.GetHead());

				setTemp.UpdateRecordset("CImmToPathoxDlg::OnOK");
			}

			m_listIDSi.RemoveHead();
		}

		//
		setTemp.CloseRecordset("CImmToPathoxDlg::OnOK");
	}

	CResizableDialog::OnOK();
}

void CImmToPathoxDlg::OnSize(UINT nType, int cx, int cy)
{
	CResizableDialog::OnSize(nType, cx, cy);

	//

	if (::IsWindow(m_ctrlListNo.GetSafeHwnd()))
	{
		CRect rectTempNo;
		m_ctrlListNo.GetClientRect(&rectTempNo);

		long lHNumImmNo = rectTempNo.Width() / HSIZE_PAL_4;

		long lHSpaceNo = rectTempNo.Width() / lHNumImmNo;
		long lVSpaceNo = VSIZE_PAL_4 + 32;

		m_ctrlListNo.SetIconSpacing(lHSpaceNo, lVSpaceNo);
		m_ctrlListNo.RedrawWindow();
	}

	//

	if (::IsWindow(m_ctrlListSi.GetSafeHwnd()))
	{
		CRect rectTempSi;
		m_ctrlListSi.GetClientRect(&rectTempSi);

		long lHNumImmSi = rectTempSi.Width() / HSIZE_PAL_4;

		long lHSpaceSi = rectTempSi.Width() / lHNumImmSi;
		long lVSpaceSi = VSIZE_PAL_4 + 32;

		m_ctrlListSi.SetIconSpacing(lHSpaceSi, lVSpaceSi);
		m_ctrlListSi.RedrawWindow();
	}
}

void CImmToPathoxDlg::AggiornaListCtrl()
{
	// svuoto le due CListCtrl //
	int nItem;
	m_ctrlListNo.DeleteAllItems();
	m_ctrlListSi.DeleteAllItems();
	OnLvnItemchangedListNo(NULL, NULL);
	OnLvnItemchangedListSi(NULL, NULL);

	// riempio la m_ctrlListNo in base agli ID contenuti in m_listIDNo //
	nItem = 0;
	for(int i = 0; i < m_imglistNo.GetCount(); i++)
	{
		POSITION pos = m_imglistNo.FindIndex(i);

		if (pos != NULL)
		{
			IMG img = m_imglistNo.GetAt(pos);

			if (m_listIDNo.Find(img.lID) != NULL)
			{
				m_ctrlListNo.InsertItem(nItem, img.szDescription, i);
				m_ctrlListNo.SetItemData(nItem, img.lID);
				nItem++;
			}
		}
	}

	// riempio la m_ctrlListSi in base agli ID contenuti in m_listIDSi //
	nItem = 0;
	for(int i = 0; i < m_imglistSi.GetCount(); i++)
	{
		POSITION pos = m_imglistSi.FindIndex(i);

		if (pos != NULL)
		{
			IMG img = m_imglistSi.GetAt(pos);

			if (m_listIDSi.Find(img.lID) != NULL)
			{
				m_ctrlListSi.InsertItem(nItem, img.szDescription, i);
				m_ctrlListSi.SetItemData(nItem, img.lID);
				nItem++;
			}
		}
	}
}

void CImmToPathoxDlg::CaricaTutteLeImmagini()
{
	BeginWaitCursor();

	CImgList* pImgList = NULL;
	CList<long>* pListID = NULL;

	switch(theApp.m_lInterfacciaPathox)
	{
		case 1:
		{
			pImgList = &m_imglistNo;
			pListID = &m_listIDNo;
			break;
		}
		case 2:
		{
			pImgList = &m_imglistSi;
			pListID = &m_listIDSi;
			break;
		}
	}

	if ((pImgList != NULL) && (pListID != NULL))
	{
		CImgList imgListTemp;

		// carico tutte le hBit nelle due CImgList //
		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

		DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
		int iNumImages = m_pEsamiView->m_pImgManager->GetImgList(&imgListTemp);
		if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
			CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore, iNumImages, "CImmToPathoxDlg::CaricaTutteLeImmagini");

		CopiaImgList(&imgListTemp, &m_imglistNo);
		CopiaImgList(&imgListTemp, &m_imglistSi);

		// carico le immagini nelle due CImageList //
		RiempiImageList(&m_imglistNo, &m_imagelistNo);
		RiempiImageList(&m_imglistSi, &m_imagelistSi);

		// riempio la CList<long> //
		pListID->RemoveAll();
		for(int i = 0; i < iNumImages; i++)
		{
			POSITION pos = pImgList->FindIndex(i);

			if (pos != NULL)
				pListID->AddTail(pImgList->GetAt(pos).lID);
		}
	}

	AggiornaListCtrl();

	EndWaitCursor();
}

void CImmToPathoxDlg::CopiaImgList(CImgList* pOrig, CImgList* pDest)
{
	SvuotaImgList(pDest);

	POSITION pos = pOrig->GetHeadPosition();
	while(pos != NULL)
		pDest->AddTail(pOrig->GetNext(pos));
}

void CImmToPathoxDlg::RiempiImageList(CImgList* pOrig, CImageList* pDest)
{
	int nCount = pOrig->GetCount();
	pDest->SetImageCount(nCount);

	for(int i = 0; i < nCount; i++)
	{
		POSITION pos = pOrig->FindIndex(i);

		if (pos != NULL)
		{
			IMG img = pOrig->GetAt(pos);

			CBitmap* bmp = CBitmap::FromHandle(img.hBmp);
			pDest->Replace(i, bmp, RGB(0, 0, 0));
		}
	}
}

void CImmToPathoxDlg::SvuotaImgList(CImgList* pImgList)
{
	POSITION pos = pImgList->GetHeadPosition();
	while(pos != NULL)
	{
		IMG img = pImgList->GetAt(pos);

		if (img.hBmp != NULL)
			DeleteObject(img.hBmp);

		if (img.hBmpSelected != NULL)
			DeleteObject(img.hBmpSelected);

		pImgList->GetNext(pos);
	}
	pImgList->RemoveAll();
}

void CImmToPathoxDlg::OnLvnItemchangedListNo(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListNo.GetFirstSelectedItemPosition();

	m_ctrlBtnSiTutti.EnableWindow(m_ctrlListNo.GetItemCount() > 0);
	m_ctrlBtnSi.EnableWindow(pos != NULL);
}

void CImmToPathoxDlg::OnLvnItemchangedListSi(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListSi.GetFirstSelectedItemPosition();

	m_ctrlBtnNoTutti.EnableWindow(m_ctrlListSi.GetItemCount() > 0);
	m_ctrlBtnNo.EnableWindow(pos != NULL);
}

void CImmToPathoxDlg::OnNMDblclkListNo(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedBtnSi();
}

void CImmToPathoxDlg::OnNMDblclkListSi(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedBtnNo();
}

void CImmToPathoxDlg::OnBnClickedBtnNo()
{
	POSITION pos = NULL;

	// aggiungo a SX le immagini selezionate eliminandole da DX //

	pos = m_ctrlListSi.GetFirstSelectedItemPosition();
	while(pos != NULL)
	{
		int nItem = m_ctrlListSi.GetNextSelectedItem(pos);
		if (nItem >= 0)
		{
			long lID = m_ctrlListSi.GetItemData(nItem);
			if (lID > 0)
			{
				m_listIDNo.AddTail(lID);

				POSITION posTemp = m_listIDSi.Find(lID);
				if (posTemp != NULL)
					m_listIDSi.RemoveAt(posTemp);
			}
		}
	}

	// ricarico le immagini nei due controlli //

	AggiornaListCtrl();
}

void CImmToPathoxDlg::OnBnClickedBtnNoTutti()
{
	// aggiungo a SX tutte le immagini eliminandole da DX //

	while(m_listIDSi.GetCount() > 0)
		m_listIDNo.AddTail(m_listIDSi.RemoveHead());

	// ricarico le immagini nei due controlli //

	AggiornaListCtrl();
}

void CImmToPathoxDlg::OnBnClickedBtnSi()
{
	POSITION pos = NULL;

	// aggiungo a DX le immagini selezionate eliminandole da SX //

	pos = m_ctrlListNo.GetFirstSelectedItemPosition();
	while(pos != NULL)
	{
		int nItem = m_ctrlListNo.GetNextSelectedItem(pos);
		if (nItem >= 0)
		{
			long lID = m_ctrlListNo.GetItemData(nItem);
			if (lID > 0)
			{
				m_listIDSi.AddTail(lID);

				POSITION posTemp = m_listIDNo.Find(lID);
				if (posTemp != NULL)
					m_listIDNo.RemoveAt(posTemp);
			}
		}
	}

	// ricarico le immagini nei due controlli //

	AggiornaListCtrl();
}

void CImmToPathoxDlg::OnBnClickedBtnSiTutti()
{
	// aggiungo a DX tutte le immagini eliminandole da SX //

	while(m_listIDNo.GetCount() > 0)
		m_listIDSi.AddTail(m_listIDNo.RemoveHead());

	// ricarico le immagini nei due controlli //

	AggiornaListCtrl();
}