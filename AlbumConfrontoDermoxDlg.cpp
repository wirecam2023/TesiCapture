#include "stdafx.h"
#include "Endox.h"
#include "AlbumConfrontoDermoxDlg.h"

#include <io.h>
#include <math.h>

#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\ImgArchive.h"
#include "DLL_Imaging\h\ImgManager.h"

#include "Common.h"
#include "CustomDate.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "EspelliDlg.h"
#include "FileBmp.h"
#include "ImageCompareDlg.h"
#include "ObSelect.h"
#include "PazientiSet.h"
#include "PuntiPazienteSet.h"
#include "PuntiSediSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RAGGIO_PUNTO_1 3
#define RAGGIO_PUNTO_2 6

CAlbumConfrontoDermoxDlg::CAlbumConfrontoDermoxDlg(CWnd* pParent, CEsamiView* pEsamiView, CPoint ptSelPoint)
	: CEndoxResizableDlg(CAlbumConfrontoDermoxDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	m_pEsamiView = pEsamiView;
	m_ptSelPoint = ptSelPoint;

	m_pFileBmp[0] = NULL;
	m_pFileBmp[1] = NULL;

	m_rectFrameSagoma = CRect(0, 0, 0, 0);
	m_rectPaintSagoma = CRect(0, 0, 0, 0);
	m_rectFrameZoom = CRect(0, 0, 0, 0);

	m_iCurSelPointIndex = -1;
	m_iCurSelPointX = -1;
	m_iCurSelPointY = -1;

	m_lIDSede = 0;
}

CAlbumConfrontoDermoxDlg::~CAlbumConfrontoDermoxDlg()
{
	CFileBmp::DeleteListSelected(GLOBAL_IMAGES);
	
	for(int i = 0; i < 2; i++)
	{
		if (m_pFileBmp[i] != NULL)
		{
			::DestroyWindow(m_pFileBmp[i]->GetSafeHwnd());
			delete m_pFileBmp[i];
			m_pFileBmp[i] = NULL;
		}
	}

	POSITION pos;

	pos = m_ImgListOrgani[0].GetHeadPosition();
	while(pos != NULL)
	{
		DeleteObject(m_ImgListOrgani[0].GetAt(pos).img.hBmp);
		
		m_ImgListOrgani[0].GetNext(pos);
	}
	m_ImgListOrgani[0].RemoveAll();

	pos = m_ImgListOrgani[1].GetHeadPosition();
	while(pos != NULL)
	{
		DeleteObject(m_ImgListOrgani[1].GetAt(pos).img.hBmp);
		
		m_ImgListOrgani[1].GetNext(pos);
	}
	m_ImgListOrgani[1].RemoveAll();

	m_listImg.RemoveAll();
}


void CAlbumConfrontoDermoxDlg::DoDataExchange(CDataExchange* pDX)
{
	int nFlag = 0;

	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LABEL_PAZIENTE_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_08, m_ctrlStatic08);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);

	if (m_pEsamiView->m_pPazientiSet->IsOpen())
	{
		DDX_FieldText (pDX, IDC_PAZIENTE_FISC,		m_pEsamiView->m_pPazientiSet->m_sCodFisc,	m_pEsamiView->m_pPazientiSet->GetRecordset());
		DDX_FieldText (pDX, IDC_PAZIENTE_SANIT,		m_pEsamiView->m_pPazientiSet->m_sCodSanit,	m_pEsamiView->m_pPazientiSet->GetRecordset());
		DDX_FieldText (pDX, IDC_PAZIENTE_COGNOME,	m_pEsamiView->m_pPazientiSet->m_sCognome,	m_pEsamiView->m_pPazientiSet->GetRecordset());
		DDX_FieldText (pDX, IDC_PAZIENTE_NOME,		m_pEsamiView->m_pPazientiSet->m_sNome,		m_pEsamiView->m_pPazientiSet->GetRecordset());
		DDX_FieldDate (pDX, IDC_PAZIENTE_NATOIL,	m_pEsamiView->m_pPazientiSet->m_lNatoIlCustom, m_pEsamiView->m_pPazientiSet);

		if ((m_pEsamiView->m_pPazientiSet->IsFieldNull(&m_pEsamiView->m_pPazientiSet->m_lSessoPaz) == FALSE))
		{
			switch (m_pEsamiView->m_pPazientiSet->m_lSessoPaz)
			{
				case -1:
					SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_ND));
					break;
				case 0:
					SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_MALE));
					break;
				case 1:
					SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_FEMALE));
					break;
				case 2:
					SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_AMBIGOUS));
					break;
				case 3:
					SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_NOTAPPLICABLE));
					break;
				case 4:
					SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_OTHER));
					break;
				default:
					SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_ND));
					break;
			}
		}			
		else
			SetDlgItemText(IDC_PAZIENTE_SESSO, "");
	}

	DDX_Control(pDX, IDC_COMBO1, m_ctrlCombo[0]);
	DDX_Control(pDX, IDC_COMBO2, m_ctrlCombo[1]);
	DDX_Control(pDX, IDC_STATIC_SAGOMA, m_ctrlFrameSagoma);
	DDX_Control(pDX, IDC_STATIC_SEDE2, m_ctrlStaticSede);
	DDX_Control(pDX, IDC_STATIC_ZOOM, m_ctrlFrameZoom);
}

BEGIN_MESSAGE_MAP(CAlbumConfrontoDermoxDlg, CEndoxResizableDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_IMM_FIRST_1, OnImmFirst1)
	ON_BN_CLICKED(IDC_IMM_FIRST_2, OnImmFirst2)
	ON_BN_CLICKED(IDC_IMM_LAST_1, OnImmLast1)
	ON_BN_CLICKED(IDC_IMM_LAST_2, OnImmLast2)
	ON_BN_CLICKED(IDC_IMM_NEXT_1, OnImmNext1)
	ON_BN_CLICKED(IDC_IMM_NEXT_2, OnImmNext2)
	ON_BN_CLICKED(IDC_IMM_PREV_1, OnImmPrev1)
	ON_BN_CLICKED(IDC_IMM_PREV_2, OnImmPrev2)
	ON_BN_CLICKED(IDC_FULLSCREEN, OnBnClickedFullScreen)
	ON_BN_CLICKED(IDC_PRINT_IMAGES, OnPrintImages)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnCbnSelchangeCombo2)
END_MESSAGE_MAP()

BOOL CAlbumConfrontoDermoxDlg::OnInitDialog() 
{
	CEndoxResizableDlg::OnInitDialog();

	m_BtnImmFirst[0].AutoLoad(IDC_IMM_FIRST_1,	this);
	m_BtnImmPrev[0].AutoLoad(IDC_IMM_PREV_1,	this);
	m_BtnImmNext[0].AutoLoad(IDC_IMM_NEXT_1,	this);
	m_BtnImmLast[0].AutoLoad(IDC_IMM_LAST_1,	this);
	m_BtnImmFirst[1].AutoLoad(IDC_IMM_FIRST_2,	this);
	m_BtnImmPrev[1].AutoLoad(IDC_IMM_PREV_2,	this);
	m_BtnImmNext[1].AutoLoad(IDC_IMM_NEXT_2,	this);
	m_BtnImmLast[1].AutoLoad(IDC_IMM_LAST_2,	this);
	m_BtnFullScreen.AutoLoad(IDC_FULLSCREEN,	this);
	m_BtnPrintImages.AutoLoad(IDC_PRINT_IMAGES, this);

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
		CFileBmp::DeleteListSelected(GLOBAL_IMAGES);

		/*
		CEsamiSet setTemp;
		setTemp.SetOpenFilter(m_pEsamiView->m_pEsamiSet->GetBaseFilter(TRUE));
		setTemp.SetSortRecord("Data, Contatore");
		if (setTemp.OpenRecordset("CAlbumConfrontoDermoxDlg::OnInitDialog"))
		{
			int nIndex = 0;

			while(!setTemp.IsEOF())
			{
				CString strTemp;
				strTemp.Format("%d° %s %s", nIndex + 1, theApp.GetMessageString(IDS_ESAME_DEL), CCustomDate(setTemp.m_lData).GetDate("%d/%m/%Y"));

				m_ctrlCombo[0].InsertString(nIndex, strTemp);
				m_ctrlCombo[0].SetItemData(nIndex, (DWORD)setTemp.m_lContatore);

				m_ctrlCombo[1].InsertString(nIndex, strTemp);
				m_ctrlCombo[1].SetItemData(nIndex, (DWORD)setTemp.m_lContatore);

				nIndex++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CAlbumConfrontoDermoxDlg::OnInitDialog");
		}
		*/

		AddAnchor(IDC_LABEL_PAZIENTE_01, CSize(0, 0), CSize(11, 0));
		AddAnchor(IDC_LABEL_PAZIENTE_02, CSize(0, 0), CSize(11, 0));
		AddAnchor(IDC_PAZIENTE_FISC, CSize(11, 0), CSize(33, 0));
		AddAnchor(IDC_PAZIENTE_SANIT, CSize(11, 0), CSize(33, 0));

		AddAnchor(IDC_LABEL_PAZIENTE_03, CSize(33, 0), CSize(44, 0));
		AddAnchor(IDC_LABEL_PAZIENTE_04, CSize(33, 0), CSize(44, 0));
		AddAnchor(IDC_PAZIENTE_COGNOME, CSize(44, 0), CSize(66, 0));
		AddAnchor(IDC_PAZIENTE_NOME, CSize(44, 0), CSize(66, 0));

		AddAnchor(IDC_LABEL_PAZIENTE_05, CSize(66, 0), CSize(77, 0));
		AddAnchor(IDC_LABEL_PAZIENTE_08, CSize(66, 0), CSize(77, 0));
		AddAnchor(IDC_PAZIENTE_SESSO, CSize(77, 0), CSize(100, 0));
		AddAnchor(IDC_PAZIENTE_NATOIL, CSize(77, 0), CSize(100, 0));

		AddAnchor(IDC_STATIC_LINE1, CSize(0, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_LINE2, CSize(0, 100), CSize(100, 100));
		AddAnchor(IDC_STATIC_LINE3, CSize(50, 0), CSize(50, 100));
		AddAnchor(IDC_STATIC_LINE4, CSize(50, 50), CSize(100, 50));

		AddAnchor(IDC_COMBO1, CSize(50, 0), CSize(50, 0));
		AddAnchor(IDC_IMM_FIRST_1, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_IMM_PREV_1, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_IMM_NEXT_1, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_IMM_LAST_1, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_FRAME_LARGE_1, CSize(50, 0), CSize(100, 50));

		AddAnchor(IDC_COMBO2, CSize(50, 50), CSize(50, 50));
		AddAnchor(IDC_IMM_FIRST_2, CSize(100, 50), CSize(100, 50));
		AddAnchor(IDC_IMM_PREV_2, CSize(100, 50), CSize(100, 50));
		AddAnchor(IDC_IMM_NEXT_2, CSize(100, 50), CSize(100, 50));
		AddAnchor(IDC_IMM_LAST_2, CSize(100, 50), CSize(100, 50));
		AddAnchor(IDC_FRAME_LARGE_2, CSize(50, 50), CSize(100, 100));

		AddAnchor(IDC_FULLSCREEN, CSize(0, 100), CSize(0, 100));
		AddAnchor(IDC_PRINT_IMAGES, CSize(0, 100), CSize(0, 100));
		AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));

		AddAnchor(IDC_STATIC_SAGOMA, CSize(0, 0), CSize(50, 100));
		AddAnchor(IDC_STATIC_ZOOM, CSize(0, 100), CSize(0, 100));
		AddAnchor(IDC_STATIC_SEDE1, CSize(0, 100), CSize(0, 100));
		AddAnchor(IDC_STATIC_SEDE2, CSize(0, 100), CSize(0, 100));

		m_ctrlStaticSede.SetFont(&theApp.m_fontBold);

		GetDlgItem(IDC_PAZIENTE_FISC)->SetFont(&theApp.m_fontBold);
		GetDlgItem(IDC_PAZIENTE_SANIT)->SetFont(&theApp.m_fontBold);
		GetDlgItem(IDC_PAZIENTE_COGNOME)->SetFont(&theApp.m_fontBold);
		GetDlgItem(IDC_PAZIENTE_NOME)->SetFont(&theApp.m_fontBold);
		GetDlgItem(IDC_PAZIENTE_NATOIL)->SetFont(&theApp.m_fontBold);
		GetDlgItem(IDC_PAZIENTE_SESSO)->SetFont(&theApp.m_fontBold, TRUE);

		m_BtnPrintImages.EnableWindow(theApp.m_dwPrivileges & AMLogin_Permissions::printout ? TRUE : FALSE);

		//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
		SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

		//////////////////////
		// OnChangeView --> //
		//////////////////////

		CWnd* pBmpFrame[2];
		pBmpFrame[0] = (CWnd*)GetDlgItem(IDC_FRAME_LARGE_1);
		pBmpFrame[1] = (CWnd*)GetDlgItem(IDC_FRAME_LARGE_2);

		for(int i = 0; i < 2; i++)
		{
			if (pBmpFrame[i])
			{
				if (CFileBmp::CreateBmp(m_pEsamiView, this, pBmpFrame[i], &m_pFileBmp[i]))
				{
					m_pFileBmp[i]->SetMouseMode(BMP_L_NODOUBLECLICK, BMP_R_NORMALMODE);
					m_pFileBmp[i]->SetAlbumType(TRUE); 
					m_pFileBmp[i]->ShowWindow(TRUE);
				}
			}
		}

		for(int i = 0; i < 2; i++)
		{
			m_nMaxDiapo[i] = 0;
			m_nDiapoPage[i] = 0;
			m_pFileBmp[i]->ResetImage();
		}

		//////////////////////
		// <-- OnChangeView //
		//////////////////////

		//
		CString strFilter;
		strFilter.Format("IDPaziente=%li", m_pEsamiView->m_pPazientiSet->m_lContatore);

		CPuntiPazienteSet setPunti;
		setPunti.SetOpenFilter(strFilter);
		if (setPunti.OpenRecordset("CAcqFromTeleDermoxDlg::OnInitDialog"))
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

			setPunti.CloseRecordset("CAcqFromTeleDermoxDlg::OnInitDialog");
		}

		//
		CPuntiSediSet setSedi;
		if (setSedi.OpenRecordset("CAcqFromTeleDermoxDlg::OnInitDialog"))
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

			setSedi.CloseRecordset("CAcqFromTeleDermoxDlg::OnInitDialog");
		}

		//
		theApp.LocalizeDialog(this, CAlbumConfrontoDermoxDlg::IDD, "CAlbumConfrontoDermoxDlg");

		/*
		int nTemp;

		nTemp = m_ctrlCombo[0].GetCount();
		if (nTemp > 0)
			m_ctrlCombo[0].SetCurSel(max(nTemp - 1, 0));
		EsamiMove(0);

		nTemp = m_ctrlCombo[1].GetCount();
		if (nTemp > 0)
			m_ctrlCombo[1].SetCurSel(max(nTemp - 2, 0));
		EsamiMove(1);
		*/

		SelezionaPunto(m_ptSelPoint);
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

void CAlbumConfrontoDermoxDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	point.x++;
	point.y++;
	if (m_rectPaintSagoma.PtInRect(point))
	{
		point = ScreenToImage(point);
		SelezionaPunto(point);
	}
}

void CAlbumConfrontoDermoxDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CEndoxResizableDlg::OnMouseMove(nFlags, point);

	// calcolo l'area del rect di zoom //
	InvalidateRect(m_rectFrameZoom, FALSE);
}

void CAlbumConfrontoDermoxDlg::ResetVetDiapo(BOOL bReposition , int nEsame)
{   
	POSITION pos = m_ImgListOrgani[nEsame].GetHeadPosition();
	while(pos != NULL)
	{
		DeleteObject(m_ImgListOrgani[nEsame].GetAt(pos).img.hBmp);
		
		m_ImgListOrgani[nEsame].GetNext(pos);
	}
	m_ImgListOrgani[nEsame].RemoveAll();

	if (bReposition)
	{
		m_nMaxDiapo[nEsame] = 0;
		m_nDiapoPage[nEsame] = -1;
	}
}  	

int CAlbumConfrontoDermoxDlg::FillDiapoIndex(int nEsame) 
{
	BeginWaitCursor();

	//
	m_ImgListOrgani[nEsame].RemoveAll();

	//
	int nIndex = m_ctrlCombo[nEsame].GetCurSel();
	long lContatore = (long)m_ctrlCombo[nEsame].GetItemData(nIndex);

	//
	POSITION pos = m_listImg.GetHeadPosition();
	while(pos != NULL)
	{
		IMG_ORGANI ImgOrgani;

		ImgOrgani.img = m_listImg.GetNext(pos);
		ImgOrgani.iPunto = -1;
		ImgOrgani.sSedeDermox = "";
		ImgOrgani.lNumeroDermox = -1;

		if (ImgOrgani.img.lIDEsame == lContatore)
		{
			if (ImgOrgani.img.lIDPunto > 0)
				CPuntiPazienteSet().GetSedeNumero(ImgOrgani.img.lIDPunto, ImgOrgani.sSedeDermox, ImgOrgani.lNumeroDermox);

			m_ImgListOrgani[nEsame].AddTail(ImgOrgani);
		}
	}

	//
	EndWaitCursor();

	//
	return m_ImgListOrgani[nEsame].GetCount();
}

void CAlbumConfrontoDermoxDlg::MoveImage(int nEsame)
{
	m_BtnImmFirst[nEsame].EnableWindow(m_nDiapoPage[nEsame] > 0);
	m_BtnImmPrev[nEsame].EnableWindow(m_nDiapoPage[nEsame] > 0);
	m_BtnImmNext[nEsame].EnableWindow(m_nDiapoPage[nEsame] < (m_nMaxDiapo[nEsame] - 1));
	m_BtnImmLast[nEsame].EnableWindow(m_nDiapoPage[nEsame] < (m_nMaxDiapo[nEsame] - 1));

	m_pFileBmp[nEsame]->ResetImage();

	long lIDEsame = (long)m_ctrlCombo[nEsame].GetItemData(m_ctrlCombo[nEsame].GetCurSel());
	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pPazientiSet->m_lContatore, lIDEsame);
	
	CString strDvdLabel;
	BOOL bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(strDvdLabel);
	if (m_nDiapoPage[nEsame] < m_nMaxDiapo[nEsame])
	{
		if (!bConfirmed)
		{
			if (!m_pFileBmp[nEsame]->LoadImage(m_pEsamiView->m_pPazientiSet->m_lContatore, lIDEsame, &m_ImgListOrgani[nEsame], m_nDiapoPage[nEsame], bConfirmed, strDvdLabel, CARICA_IMM))
				m_pFileBmp[nEsame]->LoadImage(m_pEsamiView->m_pPazientiSet->m_lContatore, lIDEsame, &m_ImgListOrgani[nEsame], m_nDiapoPage[nEsame], bConfirmed, strDvdLabel, CARICA_MINI);
		}
		else
		{
			BOOL bDvd = TRUE;

			while(GetVolumeName() != strDvdLabel)
			{
				CEspelliDlg	dlg(this, strDvdLabel);

				if (dlg.DoModal() == IDCANCEL)
				{
					m_pFileBmp[nEsame]->LoadImage(m_pEsamiView->m_pPazientiSet->m_lContatore, lIDEsame, &m_ImgListOrgani[nEsame], m_nDiapoPage[nEsame], bConfirmed, strDvdLabel, CARICA_MINI);
					bDvd = FALSE;
					break;
				}
			}

			if (bDvd)
				m_pFileBmp[nEsame]->LoadImage(m_pEsamiView->m_pPazientiSet->m_lContatore, lIDEsame, &m_ImgListOrgani[nEsame], m_nDiapoPage[nEsame], bConfirmed, strDvdLabel, CARICA_IMM);
		}

		CFileBmp::ReselectBmp(m_pFileBmp[nEsame], FALSE);
	}
	else
	{
		m_pFileBmp[nEsame]->ResetImage();
	}

	m_BtnFullScreen.EnableWindow(m_pFileBmp[0]->IsValidBmp() && m_pFileBmp[1]->IsValidBmp());
}

void CAlbumConfrontoDermoxDlg::EsamiMove(int nEsame) 
{
	long lContatore = (long)m_ctrlCombo[nEsame].GetItemData(m_ctrlCombo[nEsame].GetCurSel());

	ResetVetDiapo(TRUE, nEsame);

	m_nMaxDiapo[nEsame] = FillDiapoIndex(nEsame);

	m_nDiapoPage[nEsame] = 0;

	MoveImage(nEsame);

	UpdateData(FALSE);
}

void CAlbumConfrontoDermoxDlg::OnImmFirst1() 
{
    if (m_nDiapoPage[0] == 0)
    	return;

    m_nDiapoPage[0] = 0;
	MoveImage(0);
}

void CAlbumConfrontoDermoxDlg::OnImmLast1() 
{
	if (m_nDiapoPage[0] == m_nMaxDiapo[0] - 1)
		return;

	m_nDiapoPage[0] = m_nMaxDiapo[0] - 1;
	MoveImage(0);
}

void CAlbumConfrontoDermoxDlg::OnImmNext1() 
{
	if (m_nDiapoPage[0] == m_nMaxDiapo[0])
		return;

	m_nDiapoPage[0]++;
	MoveImage(0);
}

void CAlbumConfrontoDermoxDlg::OnImmPrev1() 
{
    if (m_nDiapoPage[0] == 0)
    	return;

    m_nDiapoPage[0]--;
	MoveImage(0);
}

void CAlbumConfrontoDermoxDlg::OnImmFirst2() 
{
    if (m_nDiapoPage[1] == 0)
    	return;

    m_nDiapoPage[1] = 0;
	MoveImage(1);
}

void CAlbumConfrontoDermoxDlg::OnImmLast2() 
{
	if (m_nDiapoPage[1] == m_nMaxDiapo[1] - 1)
		return;

	m_nDiapoPage[1] = m_nMaxDiapo[1] - 1;
	MoveImage(1);
}

void CAlbumConfrontoDermoxDlg::OnImmNext2() 
{
	if (m_nDiapoPage[1] == m_nMaxDiapo[1])
		return;

	m_nDiapoPage[1]++;
	MoveImage(1);
}

void CAlbumConfrontoDermoxDlg::OnImmPrev2() 
{
    if (m_nDiapoPage[1] == 0)
    	return;

    m_nDiapoPage[1]--;
	MoveImage(1);
}

void CAlbumConfrontoDermoxDlg::OnPaint() 
{
	CPaintDC dc(this);

	///////////////////
	// SAGOMA GRANDE //
	///////////////////

	// disegno la dib //
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
	if (m_rectPaintSagoma.PtInRect(ptMouse))
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

void CAlbumConfrontoDermoxDlg::OnBnClickedFullScreen()
{
	CImageCompareDlg dlg(this, m_pEsamiView, m_pEsamiView->m_pPazientiSet->m_lContatore, (long)m_ctrlCombo[0].GetItemData(m_ctrlCombo[0].GetCurSel()), (long)m_ctrlCombo[1].GetItemData(m_ctrlCombo[1].GetCurSel()), &m_ImgListOrgani[0], m_nDiapoPage[0], &m_ImgListOrgani[1], m_nDiapoPage[1]);
	dlg.DoModal();
}

void CAlbumConfrontoDermoxDlg::OnPrintImages() 
{
	// cancello la selezione di tutte le immagini globali //
	CFileBmp::DeleteListSelected(GLOBAL_IMAGES);

	// seleziono solo le due immagini che sto guardando //
	CFileBmp::NewSelected(m_pFileBmp[0]);
	CFileBmp::NewSelected(m_pFileBmp[1]);

	// cambio il numero di immagini per pagina, impostandolo a 2 //
	int nOldTypePrintImage = theApp.m_nStampaImmaginiTipoDiStampa;
	theApp.m_nStampaImmaginiTipoDiStampa = 1; // <-- due immagini per pagina //

	// lancio la stampa //
	m_pEsamiView->AnteprimaStampaImmagini(STAMPA, GLOBAL_IMAGES, 1);

	// ripristino il numero di immagini per pagina //
	theApp.m_nStampaImmaginiTipoDiStampa = nOldTypePrintImage;

	// cancello nuovamente la selezione di tutte le immagini globali //
	CFileBmp::DeleteListSelected(GLOBAL_IMAGES);

	//
	EsamiMove(0);
	EsamiMove(1);
}

void CAlbumConfrontoDermoxDlg::OnSize(UINT nType, int cx, int cy) 
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);

	if (m_pFileBmp[0] != NULL)
		m_pFileBmp[0]->SendMessage(EPM_RESIZE_FORM);
	if (m_pFileBmp[1] != NULL)
		m_pFileBmp[1]->SendMessage(EPM_RESIZE_FORM);

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

void CAlbumConfrontoDermoxDlg::OnCbnSelchangeCombo1()
{
	EsamiMove(0);
}

void CAlbumConfrontoDermoxDlg::OnCbnSelchangeCombo2()
{
	EsamiMove(1);
}

CPoint CAlbumConfrontoDermoxDlg::ImageToScreen(CPoint ptPoint)
{
	CPoint ptReturn;

	ptReturn.x = ptPoint.x * m_rectPaintSagoma.Width() / m_dibSagome.Width();
	ptReturn.x = ptReturn.x + m_rectPaintSagoma.left;
	ptReturn.y = ptPoint.y * m_rectPaintSagoma.Height() / m_dibSagome.Height();
	ptReturn.y = ptReturn.y + m_rectPaintSagoma.top;

	return ptReturn;
}

CPoint CAlbumConfrontoDermoxDlg::ImageToScreenZoom(CPoint ptPoint, CRect rectImageZoom)
{
	CPoint ptReturn;

	ptReturn.x = ((ptPoint.x - rectImageZoom.left) * m_rectFrameZoom.Width() / rectImageZoom.Width()) + m_rectFrameZoom.left;
	ptReturn.y = ((ptPoint.y - rectImageZoom.top) * m_rectFrameZoom.Height() / rectImageZoom.Height()) + m_rectFrameZoom.top;

	return ptReturn;
}

CPoint CAlbumConfrontoDermoxDlg::ScreenToImage(CPoint ptPoint)
{
	CPoint ptReturn;

	ptReturn.x = ptPoint.x - m_rectPaintSagoma.left;
	ptReturn.x = ptReturn.x * m_dibSagome.Width() / m_rectPaintSagoma.Width();
	ptReturn.y = ptPoint.y - m_rectPaintSagoma.top;
	ptReturn.y = ptReturn.y * m_dibSagome.Height() / m_rectPaintSagoma.Height();

	return ptReturn;
}

void CAlbumConfrontoDermoxDlg::SelezionaPunto(CPoint ptPoint)
{
	BeginWaitCursor();

	int nIndex = TrovaPunto(ptPoint);

	if (nIndex >= 0)
	{
		m_iCurSelPointIndex = nIndex; // il punto esiste già, mi basta soltanto selezionarlo //
		m_iCurSelPointX = ptPoint.x;
		m_iCurSelPointY = ptPoint.y;

		CaricaImmaginiPunto();

		InvalidateRect(m_rectFrameSagoma, FALSE);
		InvalidateRect(m_rectFrameZoom, FALSE);

		// --- //

		CEsamiSet setTemp;
		setTemp.SetOpenFilter(m_pEsamiView->m_pEsamiSet->GetBaseFilter(TRUE));
		setTemp.SetSortRecord("Data, Contatore");
		if (setTemp.OpenRecordset("CAlbumConfrontoDermoxDlg::OnInitDialog"))
		{
			int nIndex = 0;

			while(!setTemp.IsEOF())
			{
				POSITION pos = m_listImg.GetHeadPosition();
				while(pos != NULL)
				{
					if (m_listImg.GetAt(pos).lIDEsame == setTemp.m_lContatore)
					{
						CString strTemp;
						strTemp.Format("%d° %s %s", nIndex + 1, theApp.GetMessageString(IDS_ESAME_DEL), CCustomDate(setTemp.m_lData).GetDate("%d/%m/%Y"));

						int nItem = m_ctrlCombo[0].GetCount();
						m_ctrlCombo[0].InsertString(nItem, strTemp);
						m_ctrlCombo[0].SetItemData(nItem, (DWORD)setTemp.m_lContatore);

						nItem = m_ctrlCombo[1].GetCount();
						m_ctrlCombo[1].InsertString(nItem, strTemp);
						m_ctrlCombo[1].SetItemData(nItem, (DWORD)setTemp.m_lContatore);

						break;
					}

					m_listImg.GetNext(pos);
				}

				nIndex++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CAlbumConfrontoDermoxDlg::OnInitDialog");
		}

		// --- //

		int nTemp;

		nTemp = m_ctrlCombo[0].GetCount();
		if (nTemp > 0)
		{
			m_ctrlCombo[0].EnableWindow(TRUE);
			m_ctrlCombo[0].SetCurSel(max(nTemp - 1, 0));
		}
		else
		{
			m_ctrlCombo[0].EnableWindow(FALSE);
		}
		EsamiMove(0);

		nTemp = m_ctrlCombo[1].GetCount();
		if (nTemp > 0)
		{
			m_ctrlCombo[1].EnableWindow(TRUE);
			m_ctrlCombo[1].SetCurSel(max(nTemp - 2, 0));
		}
		else
		{
			m_ctrlCombo[1].EnableWindow(FALSE);
		}
		EsamiMove(1);
	}

	EndWaitCursor();
}

int CAlbumConfrontoDermoxDlg::TrovaPunto(CPoint& ptPoint)
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

void CAlbumConfrontoDermoxDlg::CaricaImmaginiPunto()
{
	// ID del punto //
	long lIDPunto = 0;
	if (m_iCurSelPointIndex >= 0)
		lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

	if (lIDPunto > 0)
	{
		m_listImg.RemoveAll();

		// lista delle immagini di quel punto //
		m_pEsamiView->m_pImgManager->GetImgListByPoint(m_pEsamiView->m_pPazientiSet->m_lContatore, lIDPunto, &m_listImg);
	}
	else
	{
		m_listImg.RemoveAll();
	}
}
