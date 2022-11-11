#include "stdafx.h"
#include "Endox.h"
#include "MosaicDlg.h"

#include <io.h>

#include "DLL_Imaging\h\AMLogin.h"

#include "Common.h"
#include "EsamiView.h"
#include "ExportDlg.h"
#include "FileBmp.h"
#include "ImmaginiPuntiSet.h"
#include "LogFileWriter.h"
#include "MmSystem.h"
#include "ModelessDlg.h"
#include "PuntiSet.h"
#include "QueryDlg.h"
#include "Riga.h"
#include "ShowEsameForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT CMosaicDlg::uiFrameEsami[NUM_ESAMI_MAX] = { IDC_ESAME1, IDC_ESAME2, IDC_ESAME3, IDC_ESAME4, IDC_ESAME5, IDC_ESAME6, IDC_ESAME7, IDC_ESAME8, IDC_ESAME9, IDC_ESAME10 };
UINT CMosaicDlg::uiFrameImmagini[NUM_ESAMI_MAX][NUM_MOSAIC_MAX] = { { IDC_FRAME_11, IDC_FRAME_12, IDC_FRAME_13, IDC_FRAME_14, IDC_FRAME_15, IDC_FRAME_16, IDC_FRAME_17, IDC_FRAME_18 }, { IDC_FRAME_21, IDC_FRAME_22, IDC_FRAME_23, IDC_FRAME_24, IDC_FRAME_25, IDC_FRAME_26, IDC_FRAME_27, IDC_FRAME_28 }, { IDC_FRAME_31, IDC_FRAME_32, IDC_FRAME_33, IDC_FRAME_34, IDC_FRAME_35, IDC_FRAME_36, IDC_FRAME_37, IDC_FRAME_38 }, { IDC_FRAME_41, IDC_FRAME_42, IDC_FRAME_43, IDC_FRAME_44, IDC_FRAME_45, IDC_FRAME_46, IDC_FRAME_47, IDC_FRAME_48 }, { IDC_FRAME_51, IDC_FRAME_52, IDC_FRAME_53, IDC_FRAME_54, IDC_FRAME_55, IDC_FRAME_56, IDC_FRAME_57, IDC_FRAME_58 }, { IDC_FRAME_61, IDC_FRAME_62, IDC_FRAME_63, IDC_FRAME_64, IDC_FRAME_65, IDC_FRAME_66, IDC_FRAME_67, IDC_FRAME_68 }, { IDC_FRAME_71, IDC_FRAME_72, IDC_FRAME_73, IDC_FRAME_74, IDC_FRAME_75, IDC_FRAME_76, IDC_FRAME_77, IDC_FRAME_78 }, { IDC_FRAME_81, IDC_FRAME_82, IDC_FRAME_83, IDC_FRAME_84, IDC_FRAME_85, IDC_FRAME_86, IDC_FRAME_87, IDC_FRAME_88 }, { IDC_FRAME_91, IDC_FRAME_92, IDC_FRAME_93, IDC_FRAME_94, IDC_FRAME_95, IDC_FRAME_96, IDC_FRAME_97, IDC_FRAME_98 }, { IDC_FRAME_101, IDC_FRAME_102, IDC_FRAME_103, IDC_FRAME_104, IDC_FRAME_105, IDC_FRAME_106, IDC_FRAME_107, IDC_FRAME_108 } };

CMosaicDlg::CMosaicDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(CMosaicDlg::IDD, pParent)
{
	m_nDiapoPerEsame = 0;
	m_nEsamiPerPage	 = 0;
	m_pEsamiView	 = pEsamiView;

	m_pQueryDlg		= NULL;
	if (pParent->IsKindOf(RUNTIME_CLASS(CQueryDlg)))
		m_pQueryDlg	= (CQueryDlg*)pParent;

	m_pWndExport	 = m_pEsamiView->m_pWndExport;
	if (m_pWndExport)
		m_pWndExport->m_pMosaicDlg = this;

	m_ArrayPosition = 0;

	if (m_pQueryDlg)
	{
		CDWordArray*	pLista				= &m_pQueryDlg->m_ArrayCode;
		int				nTotPazienti		= pLista->GetSize();
		int				nPaziente;
		MSG				msg;
		CModelessDlg	dlg(m_pEsamiView, IDS_MODELESS_TITLE_5);

		m_PazientiSet.SetSortRecord("Contatore");
		m_PazientiSet.SetOpenFilter("");
		m_PazientiSet.SetBaseFilter("");

		m_EsamiSet.SetSortRecord("Paziente, Contatore");
		m_EsamiSet.SetOpenFilter("");
		m_EsamiSet.SetBaseFilter("");

		switch(m_pQueryDlg->m_lRelazione)
		{
			case SOLO_PAZIENTI:
				dlg.CreateModeless(m_pEsamiView);

				for(nPaziente=0; nPaziente<nTotPazienti; nPaziente++)
				{
					BOOL		bError;
					CString		strFilter;

					strFilter.Format("Paziente=%li", (long)pLista->GetAt(nPaziente));
				
					if (m_EsamiSet.RecordsetReOpen(bError, strFilter, "Data", "CMosaicDlg::CMosaicDlg"))
					{
						while (!m_EsamiSet.IsEOF())
						{
							CString strInfo;

							m_ArrayCode.Add(m_EsamiSet.m_lContatore);

							strInfo.Format("Esame %li", m_EsamiSet.m_lContatore);

							dlg.SetInfo(strInfo);
						
							while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
							{
								TranslateMessage(&msg);
								DispatchMessage(&msg);
							}

							m_EsamiSet.MoveNext();
						}
					}

					if (dlg.m_bStop)
						break;
				}

				m_EsamiSet.CloseRecordset("Esami");

				dlg.DestroyWindow();
				break;

			case PAZIENTI_ESAMI:
			case SOLO_ESAMI:
				m_ArrayCode.Copy(*pLista);
				break;
		}
	}
	else
	{
		m_PazientiSet.SetSortRecord("Contatore");
		m_PazientiSet.SetOpenFilter("");
		m_PazientiSet.SetBaseFilter(m_pEsamiView->m_pPazientiSet->GetBaseFilter());

		m_EsamiSet.SetSortRecord("Paziente, Contatore");
		m_EsamiSet.SetBaseFilter("");
	}

	ResetVetDiapo(TRUE);

	//CFileBmp::DeleteListSelected(GLOBAL_IMAGES);  
}

CMosaicDlg::~CMosaicDlg()
{
	m_PazientiSet.CloseRecordset("CMosaicDlg::~CMosaicDlg");
	m_EsamiSet.CloseRecordset("CMosaicDlg::~CMosaicDlg");

	for(int i = 0; i < NUM_ESAMI_MAX; i++)
	{
		POSITION pos = m_RigaEsame[i].ImgListOrgani.GetHeadPosition();

		while(pos != NULL)
		{
			DeleteObject(m_RigaEsame[i].ImgListOrgani.GetAt(pos).img.hBmp);

			m_RigaEsame[i].ImgListOrgani.GetNext(pos);
		}

		m_RigaEsame[i].ImgListOrgani.RemoveAll();
	}
	
	if (m_pWndExport)
		m_pWndExport->m_pMosaicDlg = NULL; 
}

void CMosaicDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);
}

IMPLEMENT_DYNCREATE(CMosaicDlg, CEndoxResizableDlg)

BEGIN_MESSAGE_MAP(CMosaicDlg, CEndoxResizableDlg)
	ON_WM_DESTROY()
	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_ESA_FIRST,	OnEsamiFirst)
	ON_BN_CLICKED(IDC_ESA_PREV_PAG,	OnEsamiPrevPage)
	ON_BN_CLICKED(IDC_ESA_PREV,		OnEsamiPrev)
	ON_BN_CLICKED(IDC_ESA_NEXT,		OnEsamiNext)
	ON_BN_CLICKED(IDC_ESA_NEXT_PAG,	OnEsamiNextPage)
	ON_BN_CLICKED(IDC_ESA_LAST,		OnEsamiLast)
	ON_BN_CLICKED(IDC_EXPORT,		OnExport)
	ON_BN_CLICKED(IDC_VISTA,		OnCambiaVista)

	ON_MESSAGE(MSG_AFTER_ELABIMAGE, AfterElabImage)
	ON_REGISTERED_MESSAGE (MSG_SELECT_BMP,		OnSelectBmp)
END_MESSAGE_MAP()

BOOL CMosaicDlg::OnInitDialog() 
{
	int i;
	int j;

	CEndoxResizableDlg::OnInitDialog();

	for(i = 0; i < NUM_ESAMI_MAX; i++)
	{
		AddAnchor(GetDlgItem(uiFrameEsami[i])->GetSafeHwnd(), CSize(1,i*10), CSize(1,(i+1)*10));

		for(j = 0; j < NUM_MOSAIC_MAX; j++)
			AddAnchor(GetDlgItem(uiFrameImmagini[i][j])->GetSafeHwnd(), CSize(2+(j*12),i*10), CSize(2+((j+1)*12),(i+1)*10));
	}
	AddAnchor(IDC_STATIC_FRAME, CSize(100, 0), CSize(100, 100));
	AddAnchor(IDC_ESA_FIRST, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_ESA_PREV_PAG, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_ESA_PREV, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_ESA_NEXT, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_ESA_NEXT_PAG, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_ESA_LAST, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_LINE1, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_VISTA, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_LINE2, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_EXPORT, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_LINE3, CSize(100, 0), CSize(100, 0));
	// Luiz 18/02/2019 - P3 - Ajuste do Form para monitores de baixa resolução
	//AddAnchor(IDC_STATIC_LINE4, CSize(100, 100), CSize(100, 100));
	//AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDOK, CSize(100, 0), CSize(100, 0));

	m_BtnEsaFirst.AutoLoad(IDC_ESA_FIRST, this);
	m_BtnEsaPrevP.AutoLoad(IDC_ESA_PREV_PAG, this);
	m_BtnEsaPrev.AutoLoad(IDC_ESA_PREV, this);
	m_BtnEsaNext.AutoLoad(IDC_ESA_NEXT, this);
	m_BtnEsaNextP.AutoLoad(IDC_ESA_NEXT_PAG, this);
	m_BtnEsaLast.AutoLoad(IDC_ESA_LAST, this);

	m_BtnVista.AutoLoad(IDC_VISTA, this);
	m_btnExp.AutoLoad(IDC_EXPORT, this);

	m_btnEsci.AutoLoad(IDOK, this);

	CreateFormEsami();

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	SetDiapoPerPage(NUM_MOSAIC_MAX);

	m_PazientiSet.OpenRecordset("CMosaicDlg::OnInitDialog");
	m_EsamiSet.OpenRecordset("Archivio " + theApp.m_sNomeProgramma);

	m_btnExp.EnableWindow(theApp.m_dwPrivileges & AMLogin_Permissions::exportout ? TRUE : FALSE);

	OnEsamiFirst();
	theApp.LocalizeDialog(this, CMosaicDlg::IDD, "MosaicDlg");

	m_bInizializzato = TRUE;

	return TRUE;
}

void CMosaicDlg::OnEsamiFirst()  
{ 
	RegisterPages();

	if (m_pQueryDlg)
	{
		BOOL	bOK				= FALSE;
		int		nMaxArraySize	= m_ArrayCode.GetSize();

		m_ArrayPosition = 0;

		if (nMaxArraySize)
		{
			CString strFilter;
			BOOL	bError;
			
			do
			{
				strFilter.Format("Contatore=%li", (long)m_ArrayCode.GetAt(m_ArrayPosition));

				bOK = m_EsamiSet.RecordsetReOpen(bError, strFilter, "", "CMosaicDlg::OnEsamiFirst");

				if (!bOK)
					m_ArrayPosition++;
			
			} while (!bOK && (m_ArrayPosition<nMaxArraySize));

			m_ArrayPosition = min (nMaxArraySize-1, m_ArrayPosition);
		}

		AfterMoveEsame(bOK);
	}
	else
	{
		BOOL bOK = FALSE;
		
		if ((m_EsamiSet.IsBOF() == FALSE) || (m_EsamiSet.IsEOF() == FALSE))
		{
			m_EsamiSet.MoveFirst();
			bOK = TRUE;
		}

		AfterMoveEsame(bOK);
	}

	//abilitazione tasti...
	m_BtnEsaFirst. EnableWindow(FALSE);
	m_BtnEsaPrevP. EnableWindow(FALSE);
	m_BtnEsaPrev.  EnableWindow(FALSE);
	m_BtnEsaNext.  EnableWindow(TRUE);
	m_BtnEsaNextP. EnableWindow(TRUE);
	m_BtnEsaLast.  EnableWindow(TRUE);
}

void CMosaicDlg::OnEsamiPrevPage()  
{ 
	int nRecord		  = 5 * m_nEsamiPerPage;
	
	RegisterPages();

	if (m_pQueryDlg)
	{
		BOOL	bOK				= FALSE;
		int		nMaxArraySize	= m_ArrayCode.GetSize();

		m_ArrayPosition = max (0, m_ArrayPosition - nRecord);

		if (nMaxArraySize)
		{
			CString strFilter;
			BOOL	bError;
			
			do
			{
				strFilter.Format("Contatore=%li", (long)m_ArrayCode.GetAt(m_ArrayPosition));

				bOK = m_EsamiSet.RecordsetReOpen(bError, strFilter, "", "CMosaicDlg::OnEsamiPrevPage");

				if (!bOK)
					m_ArrayPosition--;
			
			} while (!bOK && (m_ArrayPosition>=0));

			m_ArrayPosition = max (0, m_ArrayPosition);
		}

		AfterMoveEsame(bOK);
	}
	else
	{
		for(int i = 0; i < m_nEsamiPerPage * 5; i++)
		{
			m_EsamiSet.MovePrev();
			if (m_EsamiSet.IsBOF() == TRUE)
			{
				OnEsamiFirst();
				return;
			}
		}
		AfterMoveEsame(TRUE);
	}

	//abilitazione tasti...
	m_BtnEsaFirst. EnableWindow(TRUE);
	m_BtnEsaPrevP. EnableWindow(TRUE);
	m_BtnEsaPrev.  EnableWindow(TRUE);
	m_BtnEsaNext.  EnableWindow(TRUE);
	m_BtnEsaNextP. EnableWindow(TRUE);
	m_BtnEsaLast.  EnableWindow(TRUE);
}

void CMosaicDlg::OnEsamiPrev()  
{ 
	int nRecord		  = m_nEsamiPerPage;
	int	nMaxArraySize = m_ArrayCode.GetSize();
	
	RegisterPages();

	if (m_pQueryDlg)
	{
		BOOL	bOK				= FALSE;
		int		nMaxArraySize	= m_ArrayCode.GetSize();

		m_ArrayPosition = max (0, m_ArrayPosition - nRecord);

		if (nMaxArraySize)
		{
			CString strFilter;
			BOOL	bError;
			
			do
			{
				strFilter.Format("Contatore=%li", (long)m_ArrayCode.GetAt(m_ArrayPosition));

				bOK = m_EsamiSet.RecordsetReOpen(bError, strFilter, "", "CMosaicDlg::OnEsamiPrev");

				if (!bOK)
					m_ArrayPosition--;
			
			} while (!bOK && (m_ArrayPosition>=0));

			m_ArrayPosition = max (0, m_ArrayPosition);
		}

		AfterMoveEsame(bOK);
	}
	else
	{
		for(int i = 0; i < m_nEsamiPerPage; i++)
		{
			m_EsamiSet.MovePrev();
			if (m_EsamiSet.IsBOF() == TRUE)
			{
				OnEsamiFirst();
				return;
			}
		}
		AfterMoveEsame(TRUE);
	}

	//abilitazione tasti...
	m_BtnEsaFirst. EnableWindow(TRUE);
	m_BtnEsaPrevP. EnableWindow(TRUE);
	m_BtnEsaPrev.  EnableWindow(TRUE);
	m_BtnEsaNext.  EnableWindow(TRUE);
	m_BtnEsaNextP. EnableWindow(TRUE);
	m_BtnEsaLast.  EnableWindow(TRUE);
}

void CMosaicDlg::OnEsamiNext()  
{ 
	int nRecord = m_nEsamiPerPage;

	RegisterPages();

	if (m_pQueryDlg)
	{
		BOOL	bOK				= FALSE;
		int		nMaxArraySize	= m_ArrayCode.GetSize();

		m_ArrayPosition = min (nMaxArraySize - 1, m_ArrayPosition + nRecord);

		if (nMaxArraySize)
		{
			CString strFilter;
			BOOL	bError;
			
			do
			{
				strFilter.Format("Contatore=%li", (long)m_ArrayCode.GetAt(m_ArrayPosition));

				bOK = m_EsamiSet.RecordsetReOpen(bError, strFilter, "", "CMosaicDlg::OnEsamiNext");

				if (!bOK)
					m_ArrayPosition++;
			
			} while (!bOK && (m_ArrayPosition<nMaxArraySize));

			m_ArrayPosition = min (nMaxArraySize-1, m_ArrayPosition);
		}

		AfterMoveEsame(bOK);
	}
	else
	{
		for(int i = 0; i < m_nEsamiPerPage; i++)
		{
			m_EsamiSet.MoveNext();
			if (m_EsamiSet.IsEOF() == TRUE)
			{
				OnEsamiLast();
				return;
			}
		}
		AfterMoveEsame(TRUE);
	}

	//abilitazione tasti...
	m_BtnEsaFirst. EnableWindow(TRUE);
	m_BtnEsaPrevP. EnableWindow(TRUE);
	m_BtnEsaPrev.  EnableWindow(TRUE);
	m_BtnEsaNext.  EnableWindow(TRUE);
	m_BtnEsaNextP. EnableWindow(TRUE);
	m_BtnEsaLast.  EnableWindow(TRUE);
}


void CMosaicDlg::OnEsamiNextPage()  
{ 
	int nRecord		  = 5 * m_nEsamiPerPage;
	int	nMaxArraySize = m_ArrayCode.GetSize();

	RegisterPages();

	if (m_pQueryDlg)
	{
		BOOL	bOK				= FALSE;
		int		nMaxArraySize	= m_ArrayCode.GetSize();

		m_ArrayPosition = min (nMaxArraySize-1, m_ArrayPosition + nRecord);

		if (nMaxArraySize)
		{
			CString strFilter;
			BOOL	bError;
			
			do
			{
				strFilter.Format("Contatore=%li", (long)m_ArrayCode.GetAt(m_ArrayPosition));

				bOK = m_EsamiSet.RecordsetReOpen(bError, strFilter, "", "CMosaicDlg::OnEsamiNextPage");

				if (!bOK)
					m_ArrayPosition++;
			
			} while (!bOK && (m_ArrayPosition<nMaxArraySize));

			m_ArrayPosition = min (nMaxArraySize-1, m_ArrayPosition);
		}

		AfterMoveEsame(bOK);
	}
	else
	{
		for(int i = 0; i < m_nEsamiPerPage * 5; i++)
		{
			m_EsamiSet.MoveNext();
			if (m_EsamiSet.IsEOF() == TRUE)
			{
				OnEsamiLast();
				return;
			}
		}
		AfterMoveEsame(TRUE);
	}

	//abilitazione tasti...
	m_BtnEsaFirst. EnableWindow(TRUE);
	m_BtnEsaPrevP. EnableWindow(TRUE);
	m_BtnEsaPrev.  EnableWindow(TRUE);
	m_BtnEsaNext.  EnableWindow(TRUE);
	m_BtnEsaNextP. EnableWindow(TRUE);
	m_BtnEsaLast.  EnableWindow(TRUE);
}

void CMosaicDlg::OnEsamiLast()  
{ 
	RegisterPages();

	if (m_pQueryDlg)
	{
		BOOL	bOK				= FALSE;
		int		nMaxArraySize	= m_ArrayCode.GetSize();
		
		m_ArrayPosition = max (0, ((nMaxArraySize-1) / m_nEsamiPerPage)  * m_nEsamiPerPage);

		if (nMaxArraySize)
		{
			CString strFilter;
			BOOL	bError;
			
			do
			{
				strFilter.Format("Contatore=%li", (long)m_ArrayCode.GetAt(m_ArrayPosition));

				bOK = m_EsamiSet.RecordsetReOpen(bError, strFilter, "", "CMosaicDlg::OnEsamiLast");

				if (!bOK)
					m_ArrayPosition--;
			
			} while (!bOK && (m_ArrayPosition>=0));

			m_ArrayPosition = max (0, m_ArrayPosition);
		}

		AfterMoveEsame(bOK);
	}
	else
	{
		m_EsamiSet.MoveLast();

		AfterMoveEsame(TRUE);
	}

	//abilitazione tasti...
	m_BtnEsaFirst. EnableWindow(TRUE);
	m_BtnEsaPrevP. EnableWindow(TRUE);
	m_BtnEsaPrev.  EnableWindow(TRUE);
	m_BtnEsaNext.  EnableWindow(FALSE);
	m_BtnEsaNextP. EnableWindow(FALSE);
	m_BtnEsaLast.  EnableWindow(FALSE);
}


void CMosaicDlg::CreateFormEsami()  
{ 
	CWnd* pEsameFrame[NUM_ESAMI_MAX];

	pEsameFrame[0] = GetDlgItem(IDC_ESAME1); //valida anche grande
	pEsameFrame[1] = GetDlgItem(IDC_ESAME2);
	pEsameFrame[2] = GetDlgItem(IDC_ESAME3); //valida anche grande
	pEsameFrame[3] = GetDlgItem(IDC_ESAME4);
	pEsameFrame[4] = GetDlgItem(IDC_ESAME5); //valida anche grande
	pEsameFrame[5] = GetDlgItem(IDC_ESAME6);
	pEsameFrame[6] = GetDlgItem(IDC_ESAME7); //valida anche grande
	pEsameFrame[7] = GetDlgItem(IDC_ESAME8);
	pEsameFrame[8] = GetDlgItem(IDC_ESAME9); //valida anche grande
	pEsameFrame[9] = GetDlgItem(IDC_ESAME10);

	for(int nEsame=0; nEsame<NUM_ESAMI_MAX; nEsame++)
	{
		CShowEsameForm::CreateFormEx(this, pEsameFrame[nEsame], &m_pShowEsame[nEsame]);
		
		if (m_pShowEsame[nEsame])
			m_pShowEsame[nEsame]->SetParentDialog(this);

	}
}

void CMosaicDlg::SetDiapoPerPage(int nDiapoPerPage)  
{ 
	int nOldDiapoPerPage = m_nDiapoPerEsame;

	if (nDiapoPerPage != m_nDiapoPerEsame)
	{
		CWnd* pEsameFrame[NUM_ESAMI_MAX];
		CWnd* pBmpFrame[NUM_ESAMI_MAX][NUM_MOSAIC_MAX];

		for(int i = 0; i < NUM_ESAMI_MAX; i++)
		{
			pEsameFrame[i] = GetDlgItem(uiFrameEsami[i]);

			for(int j = 0; j < NUM_MOSAIC_MAX; j++)
				pBmpFrame[i][j] = GetDlgItem(uiFrameImmagini[i][j]);
		}

		for(int nEsame = 0; nEsame < NUM_ESAMI_MAX; nEsame++)
		{
			if (m_pShowEsame[nEsame])
			{
				m_pShowEsame[nEsame]->ShowWindow(SW_HIDE);
				pEsameFrame[nEsame]->ShowWindow(SW_HIDE);
			}

			for(int j = 0; j < NUM_MOSAIC_MAX; j++)
			{
				if (pBmpFrame[nEsame][j])
				{
//					pBmpFrame[nEsame][j]->SetWindowPos(NULL, 0, 0, (768+4)/8, (576+4)/8, SWP_NOMOVE|SWP_NOZORDER|SWP_HIDEWINDOW);
					pBmpFrame[nEsame][j]->ShowWindow(SW_HIDE);
				}

				if (m_RigaEsame[nEsame].pFileBmp[j])
				{
					::DestroyWindow(m_RigaEsame[nEsame].pFileBmp[j]->GetSafeHwnd());
					delete m_RigaEsame[nEsame].pFileBmp[j];
					m_RigaEsame[nEsame].pFileBmp[j] = NULL;
				}
			}
		}

		CRect rectTemp1;
		CRect rectTemp2;
		if (nDiapoPerPage == NUM_MOSAIC_MAX)
		{
			m_nEsamiPerPage		= NUM_ESAMI_MAX;
			m_nDiapoPerEsame	= NUM_MOSAIC_MAX;

			for(int nEsame=0; nEsame<NUM_ESAMI_MAX; nEsame++)
			{
				if (m_pShowEsame[nEsame])
				{
					m_pShowEsame[nEsame]->SetParameter(nEsame, &m_RigaEsame[nEsame]);
					//m_pShowEsame[nEsame]->SetDimension((int)((float)114 * 1.75), (int)((float)35 * 2.00));
					if (nEsame % 2 == 0)
						pEsameFrame[nEsame+1]->GetWindowRect(rectTemp1);
					else
						pEsameFrame[nEsame]->GetWindowRect(rectTemp1);
					pEsameFrame[nEsame]->SetWindowPos(NULL, 0, 0, rectTemp1.Width(), rectTemp1.Height(), SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);
					m_pShowEsame[nEsame]->ShowWindow(SW_SHOW);
				}

				for(int j=0; j<NUM_MOSAIC_MAX; j++)
				{
					if (pBmpFrame[nEsame][j])
					{
//						pBmpFrame[nEsame][j]->SetWindowPos(NULL, 0, 0, (int)((float)53 * 1.75), (int)((float)35 * 2.00), SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);

						if (j % 2 == 0)
						{
							pBmpFrame[nEsame][j+1]->GetWindowRect(rectTemp1);
							pBmpFrame[nEsame][j]->SetWindowPos(NULL, 0, 0, rectTemp1.Width(), rectTemp1.Height(), SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);
						}
						else
						{
							pBmpFrame[nEsame][j]->GetWindowRect(rectTemp1);
							pBmpFrame[nEsame][j]->SetWindowPos(NULL, 0, 0, rectTemp1.Width(), rectTemp1.Height(), SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);
						}
					}

					if (CFileBmp::CreateBmp(m_pEsamiView, this, pBmpFrame[nEsame][j], &(m_RigaEsame[nEsame].pFileBmp[j])))
					{
						m_RigaEsame[nEsame].pFileBmp[j]->SetMouseMode(BMP_L_NORMALMODE, BMP_R_SENDTOPARENT);
						m_RigaEsame[nEsame].pFileBmp[j]->SetAlbumType(TRUE); 
						m_RigaEsame[nEsame].pFileBmp[j]->ShowWindow(TRUE);
					}
				}

				m_RigaEsame[nEsame].nDiapoPage = (m_RigaEsame[nEsame].nDiapoPage * nOldDiapoPerPage) / m_nDiapoPerEsame;
				m_pShowEsame[nEsame]->SendMessage(EPM_RESIZE_FORM);
			}
		}
		else
		{
			m_nEsamiPerPage		= NUM_ESAMI_MIN;
			m_nDiapoPerEsame	= NUM_MOSAIC_MIN;

			for(int nEsame=0; nEsame<NUM_ESAMI_MIN; nEsame++)
			{
				if (m_pShowEsame[nEsame*2])
				{
					m_pShowEsame[nEsame*2]->SetParameter(nEsame, &m_RigaEsame[nEsame]);
//					m_pShowEsame[nEsame*2]->SetDimension((int)((float)114 * 1.75), (int)((float)71 * 2.00));
					pEsameFrame[nEsame*2]->GetWindowRect(rectTemp1);
					pEsameFrame[(nEsame*2)+1]->GetWindowRect(rectTemp2);
					pEsameFrame[nEsame*2]->SetWindowPos(NULL, 0, 0, rectTemp1.Width(), rectTemp2.bottom - rectTemp1.top, SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);
					m_pShowEsame[nEsame*2]->ShowWindow(SW_SHOW);
				}

				for(int j=0; j<NUM_MOSAIC_MIN; j++)
				{
					if (pBmpFrame[nEsame*2][j*2])
					{
//						pBmpFrame[nEsame*2][j*2]->SetWindowPos(NULL, 0, 0, (int)((float)107 * 1.75), (int)((float)71 * 2.00), SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);

						pBmpFrame[nEsame*2][j*2]->GetWindowRect(rectTemp1);
						pBmpFrame[(nEsame*2)+1][(j*2)+1]->GetWindowRect(rectTemp2);
						pBmpFrame[nEsame*2][j*2]->SetWindowPos(NULL, 0, 0, rectTemp2.right - rectTemp1.left, rectTemp2.bottom - rectTemp1.top, SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);
					}

					if (CFileBmp::CreateBmp(m_pEsamiView, this, pBmpFrame[nEsame*2][j*2], &(m_RigaEsame[nEsame].pFileBmp[j])))
					{
						m_RigaEsame[nEsame].pFileBmp[j]->SetMouseMode(BMP_L_NORMALMODE, BMP_R_SENDTOPARENT);
						m_RigaEsame[nEsame].pFileBmp[j]->SetAlbumType(TRUE); 
						m_RigaEsame[nEsame].pFileBmp[j]->ShowWindow(TRUE);
					}
				}

				m_RigaEsame[nEsame].nDiapoPage = (m_RigaEsame[nEsame].nDiapoPage * nOldDiapoPerPage) / m_nDiapoPerEsame;
				m_pShowEsame[nEsame*2]->SendMessage(EPM_RESIZE_FORM);
			}
		}
	}
}

//////////////////////////////////////////////////////
BOOL CMosaicDlg::FiltraPazienti()
{
	BOOL	bError = FALSE;
	CString strFilter;

	strFilter.Format("Contatore=%li", m_EsamiSet.m_lPaziente);

	return m_PazientiSet.RecordsetReOpen(bError, strFilter, "", "CMosaicDlg::FiltraPazienti");
}

//////////////////////////////////////////////////////
void CMosaicDlg::ResetVetDiapo(BOOL bBmp)
{   
	for(int nEsame=0; nEsame<NUM_ESAMI_MAX; nEsame++)
	{
		m_RigaEsame[nEsame].lEsame			= 0;
//		m_RigaEsame[nEsame].IdEsame			= -1;
		m_RigaEsame[nEsame].nDataEsame		= 0;
//		m_RigaEsame[nEsame].strCodice		= "";
//		m_RigaEsame[nEsame].strTesto1		= "";
//		m_RigaEsame[nEsame].strTesto2		= "";
//		m_RigaEsame[nEsame].strTesto3		= "";
   		m_RigaEsame[nEsame].strPaziente		= "";
//		m_RigaEsame[nEsame].strPathBmp		= "";
//		m_RigaEsame[nEsame].strPathTga		= "";
//		m_RigaEsame[nEsame].strDisco		= "";
//		m_RigaEsame[nEsame].strVolume		= "";
//		m_RigaEsame[nEsame].strPathVolume   = "";
//		m_RigaEsame[nEsame].strNomeFile		= "";
//		m_RigaEsame[nEsame].nLastImage		= 0;
		m_RigaEsame[nEsame].nDiapoPage		= 0;
		m_RigaEsame[nEsame].nMaxDiapo		= 0;
		POSITION pos = m_RigaEsame[nEsame].ImgListOrgani.GetHeadPosition();
		while(pos != NULL)
		{
			DeleteObject(m_RigaEsame[nEsame].ImgListOrgani.GetAt(pos).img.hBmp);
			m_RigaEsame[nEsame].ImgListOrgani.GetNext(pos);
		}
		m_RigaEsame[nEsame].ImgListOrgani.RemoveAll();
		m_RigaEsame[nEsame].lPaziente = 0;
		m_RigaEsame[nEsame].lEsame = 0;
		m_RigaEsame[nEsame].bConfirmed = FALSE;
		m_RigaEsame[nEsame].strDvdLabel = "";
		
		if (bBmp)
		{
			m_pShowEsame[nEsame] = NULL;

			for(int j=0; j<NUM_MOSAIC_MAX; j++)
				m_RigaEsame[nEsame].pFileBmp[j] = NULL;
		}
	}
}  	

//////////////////////////////////////////////////////
LRESULT CMosaicDlg::AfterElabImage(WPARAM wParam, LPARAM lParam)
{   
	//reset della lista degli indici...
	for(int nEsame=0; nEsame<NUM_ESAMI_MAX; nEsame++)
	{
		POSITION pos = m_RigaEsame[nEsame].ImgListOrgani.GetHeadPosition();
		while(pos != NULL)
		{
			DeleteObject(m_RigaEsame[nEsame].ImgListOrgani.GetAt(pos).img.hBmp);
			m_RigaEsame[nEsame].ImgListOrgani.GetNext(pos);
		}
		m_RigaEsame[nEsame].ImgListOrgani.RemoveAll();

		/*
		for(int j=0; j<100; j++)
			m_RigaEsame[nEsame].nVetFound[j] = 0xff;
		*/
	
		m_RigaEsame[nEsame].nMaxDiapo = FillDiapoIndex(nEsame);
	}

	RepositionPages();

	return 1;
}


//////////////////////////////////////////////////////
void CMosaicDlg::AfterMoveEsame(BOOL bFound)
{   
	BOOL		bEscape	  = FALSE;
	int			nOrgArrayPosition;
	int			nInseriti = 0;

	if (m_pQueryDlg)
	{
		nOrgArrayPosition = m_ArrayPosition;
	}

	ResetVetDiapo(FALSE);

	if (bFound)
	{
		for(int nEsame = 0; nEsame < m_nEsamiPerPage; nEsame++)
		{
			if (!m_EsamiSet.IsBOF() && !m_EsamiSet.IsEOF())
			{
				if (FiltraPazienti())
				{
					nInseriti++;

					m_RigaEsame[nEsame].strPaziente = m_PazientiSet.m_sCognome + " " + m_PazientiSet.m_sNome;

//					m_RigaEsame[nEsame].IdEsame		= m_EsamiSet.m_IdEsame;
//					m_RigaEsame[nEsame].nEsame		= m_EsamiSet.m_Contatore;

					m_RigaEsame[nEsame].nDataEsame	= m_EsamiSet.m_lData;

//					m_RigaEsame[nEsame].strCodice	= m_EsamiSet.m_CodEsame;
//					m_RigaEsame[nEsame].strTesto1	= m_EsamiSet.m_InvMedico;	//medico inviante
//					m_RigaEsame[nEsame].strTesto2	= m_EsamiSet.m_Testo1;		//indicazioni
//					m_RigaEsame[nEsame].strTesto3	= m_EsamiSet.m_Testo5;		//tipoesame
//					m_RigaEsame[nEsame].strNomeFile = CEsamiView::GetNameOfFile(&m_EsamiSet);
//					m_RigaEsame[nEsame].strPathBmp	= CEsamiView::GetPathDiapo(&m_EsamiSet);
//					m_RigaEsame[nEsame].strPathTga	= "";
//					m_RigaEsame[nEsame].strDisco	= m_EsamiSet.m_Disco;
//					m_RigaEsame[nEsame].strVolume	= m_EsamiSet.m_Label;
//					m_RigaEsame[nEsame].nLastImage  = m_EsamiSet.m_LastImage;
					m_RigaEsame[nEsame].lPaziente	= m_EsamiSet.m_lPaziente;
					m_RigaEsame[nEsame].lEsame		= m_EsamiSet.m_lContatore;
					m_RigaEsame[nEsame].nMaxDiapo	= FillDiapoIndex(nEsame);

					/*
					if (m_EsamiSet.m_Disco == "O")
					{
						m_RigaEsame[nEsame].strPathTga		= CEsamiView::GetPathOD(&m_EsamiSet);
//						m_RigaEsame[nEsame].strPathVolume	= CEsamiView::GetPrePathOD(&m_EsamiSet);
					}
					else
					{
						m_RigaEsame[nEsame].strPathTga		= CEsamiView::GetPathHD(&m_EsamiSet);
//						m_RigaEsame[nEsame].strPathVolume	= CEsamiView::GetPrePathHD(&m_EsamiSet);
					}
					*/
				}
				
			}

			//esami sucessivi.......
			//fino a riempire la pagina....
			if (m_pQueryDlg)
			{
				BOOL	bOK				= FALSE;
				int		nMaxArraySize	= m_ArrayCode.GetSize();

				bOK		= ((m_ArrayPosition+1) < nMaxArraySize);

				m_ArrayPosition = min (nMaxArraySize-1, m_ArrayPosition+1);

				if (nMaxArraySize && bOK)
				{
					CString strFilter;
					BOOL	bOK;
					BOOL	bError;
					
					do
					{
						strFilter.Format("Contatore=%li", (long)m_ArrayCode.GetAt(m_ArrayPosition));

						bOK = m_EsamiSet.RecordsetReOpen(bError, strFilter, "", "CMosaicDlg::AfterMoveEsame");

						if (!bOK)
							m_ArrayPosition++;
					
					} while (!bOK && (m_ArrayPosition<nMaxArraySize));

					m_ArrayPosition = min (nMaxArraySize-1, m_ArrayPosition);
				}

				if (!bOK)
					bEscape = TRUE;
			}
			else
			{
				if (!m_EsamiSet.IsEOF())
					m_EsamiSet.MoveNext();
			}

			if (bEscape)
				break;
		}
	}

	for(int i = 0; i < nInseriti; i++)
	{
		m_EsamiSet.MovePrev();
		if (m_EsamiSet.IsBOF() == TRUE)
		{
			m_EsamiSet.MoveFirst();
			break;
		}
	}
	
	RepositionPages();

	if (m_pQueryDlg)
	{
		int	 nMaxArraySize	= m_ArrayCode.GetSize();

		m_ArrayPosition = nOrgArrayPosition;
		
		if (nMaxArraySize)
		{
			CString strFilter;
			BOOL	bOK;
			BOOL	bError;
			
			do
			{
				strFilter.Format("Contatore=%li", (long)m_ArrayCode.GetAt(m_ArrayPosition));

				bOK = m_EsamiSet.RecordsetReOpen(bError, strFilter, "", "CMosaicDlg::AfterMoveEsame");

				if (!bOK)
					m_ArrayPosition++;
			
			} while (!bOK && (m_ArrayPosition<nMaxArraySize));

			m_ArrayPosition = min (nMaxArraySize-1, m_ArrayPosition);
		}
	}
}

//////////////////////////////////////////////////////
void CMosaicDlg::RepositionPages()
{
	for(int nEsame=0; nEsame<m_nEsamiPerPage; nEsame++)
	{
		int		nPage = 0;
		CRiga*	pRiga = m_ListRighe.SearchObj(m_RigaEsame[nEsame].lEsame);

		if (pRiga)
			nPage = (pRiga->m_nPage * pRiga->m_nDiapoPerEsame) / m_nDiapoPerEsame;

		GoToPage(nEsame, nPage);
	
		if (m_nEsamiPerPage == NUM_ESAMI_MAX)
			m_pShowEsame[nEsame]->UpdateData(FALSE);
		else
			m_pShowEsame[nEsame*2]->UpdateData(FALSE);
	}
}

//////////////////////////////////////////////////////
void CMosaicDlg::RegisterPages()
{
	for(int nEsame=0; nEsame<m_nEsamiPerPage; nEsame++)
	{
		if (m_RigaEsame[nEsame].lEsame > 0)
		{
			int		nPage = 0;
			CRiga*	pRiga = m_ListRighe.SearchObj(m_RigaEsame[nEsame].lEsame);

			if (pRiga)
			{
				pRiga->m_nPage			= m_RigaEsame[nEsame].nDiapoPage;
				pRiga->m_nDiapoPerEsame	= m_nDiapoPerEsame;
			}
			else
			{
				pRiga = new CRiga;

				if (pRiga)
				{
					pRiga->m_nEsame			= m_RigaEsame[nEsame].lEsame;
					pRiga->m_nPage			= m_RigaEsame[nEsame].nDiapoPage;
					pRiga->m_nDiapoPerEsame	= m_nDiapoPerEsame;

					m_ListRighe.InsertObjInList(pRiga);
				}
			}
		}
	}
}

//////////////////////////////////////////////////////
int CMosaicDlg::FillDiapoIndex(int nEsame)
{
	TRACE1("-> CMosaicDlg::FillDiapoIndex(%d)\n", nEsame);

	int nReturn;
	CImgList listImg;

	BeginWaitCursor();
	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_RigaEsame[nEsame].lPaziente, m_RigaEsame[nEsame].lEsame);

	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	nReturn = m_pEsamiView->m_pImgManager->GetImgList(&listImg) - 1;
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_RigaEsame[nEsame].lPaziente, m_RigaEsame[nEsame].lEsame, nReturn + 1, "CMosaicDlg::FillDiapoIndex");

	m_RigaEsame[nEsame].ImgListOrgani = listImg;
	m_RigaEsame[nEsame].bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(m_RigaEsame[nEsame].strDvdLabel);
	CaricaPunti(nEsame);
	EndWaitCursor();

	return nReturn;
}

void CMosaicDlg::GoToPage(int nEsame, int nPage) 
{
    if (nPage < 0)
		nPage = 0;
	else
		if (nPage >= (m_RigaEsame[nEsame].nMaxDiapo / m_nDiapoPerEsame))
			nPage = m_RigaEsame[nEsame].nMaxDiapo / m_nDiapoPerEsame;

	m_RigaEsame[nEsame].nDiapoPage = nPage;
	MoveImage(nEsame);
}

void CMosaicDlg::GoPageFirst(int nEsame) 
{
    if (m_RigaEsame[nEsame].nDiapoPage == 0)
    	return;

    m_RigaEsame[nEsame].nDiapoPage = 0;
	MoveImage(nEsame);
}

void CMosaicDlg::GoPagePrev(int nEsame)
{
    if (m_RigaEsame[nEsame].nDiapoPage == 0)
    	return;

    m_RigaEsame[nEsame].nDiapoPage--;
	MoveImage(nEsame);
}

void CMosaicDlg::GoPageNext(int nEsame)
{
	if (m_RigaEsame[nEsame].nDiapoPage == (m_RigaEsame[nEsame].nMaxDiapo / m_nDiapoPerEsame))
		return;

	m_RigaEsame[nEsame].nDiapoPage++;
	MoveImage(nEsame);
}

void CMosaicDlg::GoPageLast(int nEsame)
{
	if (m_RigaEsame[nEsame].nDiapoPage == (m_RigaEsame[nEsame].nMaxDiapo / m_nDiapoPerEsame))
		return;

	m_RigaEsame[nEsame].nDiapoPage = m_RigaEsame[nEsame].nMaxDiapo / m_nDiapoPerEsame;
	MoveImage(nEsame);
}

void CMosaicDlg::SelectAllImages(int nEsame)
{
	long lPaz = m_RigaEsame[nEsame].lPaziente;
	long lEsa = m_RigaEsame[nEsame].lEsame;
	BOOL bConf = m_RigaEsame[nEsame].bConfirmed;
	CString sDvd = m_RigaEsame[nEsame].strDvdLabel;

	POSITION pos = m_RigaEsame[nEsame].ImgListOrgani.GetHeadPosition();
	while(pos != NULL)
	{
		long lID = m_RigaEsame[nEsame].ImgListOrgani.GetAt(pos).img.lID;
		CString strDesc = CString(m_RigaEsame[nEsame].ImgListOrgani.GetAt(pos).img.szDescription);
		int nType = m_RigaEsame[nEsame].ImgListOrgani.GetAt(pos).img.type;
		HBITMAP hBit = m_RigaEsame[nEsame].ImgListOrgani.GetAt(pos).img.hBmp;
		BOOL bCI = m_RigaEsame[nEsame].ImgListOrgani.GetAt(pos).img.bCI;

		if (CFileBmp::NewSelected(lID, TRUE, nType, strDesc, lPaz, lEsa, bConf, sDvd, bCI) != NULL)
			m_pWndExport->AddImage(&m_RigaEsame[nEsame], lID, nType, bConf, sDvd, hBit, bCI);

		m_RigaEsame[nEsame].ImgListOrgani.GetNext(pos);
	}

	for(int i = 0; i < NUM_MOSAIC_MAX; i++)
	{
		if (m_RigaEsame[nEsame].pFileBmp[i] != NULL)
			m_RigaEsame[nEsame].pFileBmp[i]->SelectBmp(TRUE); // AutoRedraw();
	}
}

void CMosaicDlg::MoveImage(int nEsame)
{
	TRACE1("-> CMosaicDlg::MoveImage(%d)\n", nEsame);

	int nBase = m_RigaEsame[nEsame].nDiapoPage * m_nDiapoPerEsame;

	for(int i = 0; i < m_nDiapoPerEsame; i++)
	{
		if (nBase + i <= m_RigaEsame[nEsame].nMaxDiapo)
		{
			m_RigaEsame[nEsame].pFileBmp[i]->LoadImage(m_RigaEsame[nEsame].lPaziente, m_RigaEsame[nEsame].lEsame, &m_RigaEsame[nEsame].ImgListOrgani, nBase + i, m_RigaEsame[nEsame].bConfirmed, m_RigaEsame[nEsame].strDvdLabel, CARICA_MINI);

			CFileBmp::ReselectBmp(m_RigaEsame[nEsame].pFileBmp[i], FALSE);
		}
		else
		{
			m_RigaEsame[nEsame].pFileBmp[i]->ResetImage();
		}
	}
}

void CMosaicDlg::DeleteSelection()
{
	CFileBmp::DeleteListSelected(GLOBAL_IMAGES);  

	for(int nEsame=0; nEsame<NUM_ESAMI_MAX; nEsame++)
	{
		for(int j=0; j<NUM_MOSAIC_MAX; j++)
		{
			CFileBmp* pBmp = m_RigaEsame[nEsame].pFileBmp[j];

			if (pBmp && pBmp->IsSelect())
			{
				pBmp->DeSelectBmp(); //deselezione
			}
		}
	}
}

void CMosaicDlg::DeleteSelection(long nCodEsame, long lID)
{
	for(int nEsame = 0; nEsame < NUM_ESAMI_MAX; nEsame++)
	{
		if (m_RigaEsame[nEsame].lEsame == nCodEsame)
		{
			for(int j=0; j<NUM_MOSAIC_MAX; j++)
			{
				CFileBmp* pBmp = m_RigaEsame[nEsame].pFileBmp[j];

				if (pBmp && pBmp->m_lID == lID)
				{
					if (pBmp->IsSelect())
						pBmp->SelectBmp(); //deselezione
					
					CFileBmp::RemoveSelected(pBmp);

					break;
				}
			}
		}
	}
}

LONG CMosaicDlg::OnSelectBmp(WPARAM wParam, LPARAM lParam)
{
	if (lParam)
	{
		CFileBmp* pBmp = (CFileBmp*)lParam;
		
		if (m_pWndExport /*&& m_pWndExport->m_bIsActive*/)
		{
			for(int nEsame = 0; nEsame < NUM_ESAMI_MAX; nEsame++)
			{
				if (m_RigaEsame[nEsame].lEsame > 0)
				{
					for(int j = 0; j < NUM_MOSAIC_MAX; j++)
					{
						if (m_RigaEsame[nEsame].pFileBmp[j] == pBmp)
						{
							if (m_pWndExport->FindImage(m_RigaEsame[nEsame].lEsame, -1, 0, -1))
							{
								theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MOSAICDLG_MULTIPLE_SELECT));
							}
							else
							{
								pBmp->SelectBmp();
								
								if (pBmp->IsSelect())
								{
									CFileBmp::NewSelected(pBmp);
									m_pWndExport->AddImage(&m_RigaEsame[nEsame], pBmp->m_lID, pBmp->m_iType, pBmp->m_bConfirmed, pBmp->m_strDvdLabel, pBmp->m_hMiniBmp, pBmp->m_bCI);
								}
								else
								{
									CFileBmp::RemoveSelected(pBmp);
									m_pWndExport->RemoveImage(pBmp->m_lID);
								}
							}

							break;
						}
					}
				}
			}
		}
	}

	return 0;
}

LONG CMosaicDlg::OnSelectAllBmp(WPARAM wParam, LPARAM lParam)
{
	if (lParam)
	{
		CFileBmp* pBmp = (CFileBmp*)lParam;
		
		if (m_pWndExport)
		{
			for(int nEsame = 0; nEsame < NUM_ESAMI_MAX; nEsame++)
			{
				if (m_RigaEsame[nEsame].lEsame > 0)
				{
					for(int j = 0; j < NUM_MOSAIC_MAX; j++)
					{
						if (m_RigaEsame[nEsame].pFileBmp[j] == pBmp)
						{
							if (m_pWndExport->FindImage(m_RigaEsame[nEsame].lEsame, -1, 0, -1))
							{
								theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MOSAICDLG_MULTIPLE_SELECT));
							}
							else
							{
								if (!pBmp->IsSelect())
								{
									pBmp->SelectBmp();
									
									CFileBmp::NewSelected(pBmp);
									m_pWndExport->AddImage(&m_RigaEsame[nEsame], pBmp->m_lID, pBmp->m_iType, pBmp->m_bConfirmed, pBmp->m_strDvdLabel, pBmp->m_hMiniBmp, pBmp->m_bCI);
								}
							}

							break;
						}
					}
				}
			}
		}
	}

	return 0;
}

void CMosaicDlg::OnExport() 
{
	if (m_pWndExport)
	{
		// Sandro 18/12/2015 // Segnalazione PetrOne //
		m_pWndExport->m_btnCanc.EnableWindow(theApp.m_dwPrivileges & AMLogin_Permissions::modify_image);

		//
		m_pWndExport->ShowDialog(TRUE);
	}
}

void CMosaicDlg::OnDestroy() 
{
	for(int nEsame=0; nEsame<NUM_ESAMI_MAX; nEsame++)
	{
		if (m_pShowEsame[nEsame])
		{
			::DestroyWindow(m_pShowEsame[nEsame]->GetSafeHwnd());
			delete m_pShowEsame[nEsame];
			m_pShowEsame[nEsame] = NULL;
		}

		for(int j=0; j<NUM_MOSAIC_MAX; j++)
		{
			if (m_RigaEsame[nEsame].pFileBmp[j])
			{
				::DestroyWindow(m_RigaEsame[nEsame].pFileBmp[j]->GetSafeHwnd());
				delete m_RigaEsame[nEsame].pFileBmp[j];
				m_RigaEsame[nEsame].pFileBmp[j] = NULL;
			}
		}
	}

	if (m_pWndExport)
		m_pWndExport->ShowDialog(FALSE);

	CEndoxResizableDlg::OnDestroy();
}

void CMosaicDlg::OnCambiaVista() 
{
	CString strTitle;
	BOOL	bOK	= FALSE;

	RegisterPages();

	if (m_pQueryDlg)
	{
		int		nMaxArraySize	= m_ArrayCode.GetSize();

		bOK = ((m_ArrayPosition>=0) && (m_ArrayPosition<nMaxArraySize));
	}
	else
	{
		bOK = (!m_EsamiSet.IsBOF() && !m_EsamiSet.IsEOF());
	}

	if (m_nDiapoPerEsame == NUM_MOSAIC_MAX)
	{
		SetDiapoPerPage(NUM_MOSAIC_MIN);
		strTitle	= "Alb10_";
	}
	else
	{
		SetDiapoPerPage(NUM_MOSAIC_MAX);
		strTitle	= "Album_";
	}

	m_BtnVista.SetWindowText(strTitle);
	m_BtnVista.LoadBitmaps(strTitle + "U", strTitle + "D", strTitle + "F", strTitle + "X");
	m_BtnVista.SizeToContent();
	m_BtnVista.Invalidate();

	AfterMoveEsame(bOK);
}

void CMosaicDlg::OnSize(UINT nType, int cx, int cy) 
{
	int i, j;

	CEndoxResizableDlg::OnSize(nType, cx, cy);

	if (m_bInizializzato == TRUE)
		UpdateFramesPos();

	for(i = 0; i < NUM_ESAMI_MAX; i++)
	{
		if (m_pShowEsame[i] != NULL)
			m_pShowEsame[i]->SendMessage(EPM_RESIZE_FORM);

		for(j = 0; j < NUM_MOSAIC_MAX; j++)
			if (m_RigaEsame[i].pFileBmp[j] != NULL)
				m_RigaEsame[i].pFileBmp[j]->SendMessage(EPM_RESIZE_FORM);
	}
}

void CMosaicDlg::UpdateFramesPos()
{
	CRect rectTemp1, rectTemp2;

	CWnd* pEsameFrame[NUM_ESAMI_MAX];
	CWnd* pBmpFrame[NUM_ESAMI_MAX][NUM_MOSAIC_MAX];

	for(int i = 0; i < NUM_ESAMI_MAX; i++)
	{
		pEsameFrame[i] = GetDlgItem(uiFrameEsami[i]);

		for(int j = 0; j < NUM_MOSAIC_MAX; j++)
			pBmpFrame[i][j] = GetDlgItem(uiFrameImmagini[i][j]);
	}

	if (m_nDiapoPerEsame == NUM_MOSAIC_MAX)
	{
		for(int nEsame=0; nEsame<NUM_ESAMI_MAX; nEsame++)
		{
			if (m_pShowEsame[nEsame])
			{
				if (nEsame % 2 == 0)
					pEsameFrame[nEsame+1]->GetWindowRect(rectTemp1);
				else
					pEsameFrame[nEsame]->GetWindowRect(rectTemp1);
				pEsameFrame[nEsame]->SetWindowPos(NULL, 0, 0, rectTemp1.Width(), rectTemp1.Height(), SWP_NOMOVE|SWP_NOZORDER);
			}

			for(int j=0; j<NUM_MOSAIC_MAX; j++)
			{
				if (pBmpFrame[nEsame][j])
				{
					if (j % 2 == 0)
					{
						pBmpFrame[nEsame][j+1]->GetWindowRect(rectTemp1);
						pBmpFrame[nEsame][j]->SetWindowPos(NULL, 0, 0, rectTemp1.Width(), rectTemp1.Height(), SWP_NOMOVE|SWP_NOZORDER);
					}
					else
					{
						pBmpFrame[nEsame][j]->GetWindowRect(rectTemp1);
						pBmpFrame[nEsame][j]->SetWindowPos(NULL, 0, 0, rectTemp1.Width(), rectTemp1.Height(), SWP_NOMOVE|SWP_NOZORDER);
					}
				}
			}

			m_pShowEsame[nEsame]->SendMessage(EPM_RESIZE_FORM);
		}
	}
	else
	{
		for(int nEsame=0; nEsame<NUM_ESAMI_MIN; nEsame++)
		{
			if (m_pShowEsame[nEsame*2])
			{
				pEsameFrame[nEsame*2]->GetWindowRect(rectTemp1);
				pEsameFrame[(nEsame*2)+1]->GetWindowRect(rectTemp2);
				pEsameFrame[nEsame*2]->SetWindowPos(NULL, 0, 0, rectTemp1.Width(), rectTemp2.bottom - rectTemp1.top, SWP_NOMOVE|SWP_NOZORDER);
			}

			for(int j=0; j<NUM_MOSAIC_MIN; j++)
			{
				if (pBmpFrame[nEsame*2][j*2])
				{
					pBmpFrame[nEsame*2][j*2]->GetWindowRect(rectTemp1);
					pBmpFrame[(nEsame*2)+1][(j*2)+1]->GetWindowRect(rectTemp2);
					pBmpFrame[nEsame*2][j*2]->SetWindowPos(NULL, 0, 0, rectTemp2.right - rectTemp1.left, rectTemp2.bottom - rectTemp1.top, SWP_NOMOVE|SWP_NOZORDER);
				}
			}

			if (m_pShowEsame[nEsame*2] != NULL)
				m_pShowEsame[nEsame*2]->SendMessage(EPM_RESIZE_FORM);
		}
	}
}
//m_RigaEsame[nEsame]
void CMosaicDlg::CaricaPunti(int nEsame)
{
	long lIdPunto;
	long lIdOrgano;
	long lX;
	long lY;
	IMG_ORGANI img_organi;

	BOOL bFindIndex;

	POSITION pos1 = m_RigaEsame[nEsame].ImgListOrgani.GetHeadPosition();
	POSITION pos2;

	m_RigaEsame[nEsame].listPunti.RemoveAll();
	while(pos1 != NULL)
	{
		lIdPunto = CImmaginiPuntiSet().GetIDPunto(m_RigaEsame[nEsame].ImgListOrgani.GetAt(pos1).img.lID);
		if (lIdPunto > 0)
		{
			if (CPuntiSet().GetDatiPunto(lIdPunto, lIdOrgano, lX, lY) == TRUE)
			{
				img_organi = m_RigaEsame[nEsame].ImgListOrgani.GetAt(pos1);
				img_organi.iPunto = 0;

				bFindIndex = FALSE;
				pos2 = m_RigaEsame[nEsame].listPunti.GetHeadPosition();
				while(pos2 != NULL)
				{
					if (m_RigaEsame[nEsame].listPunti.GetAt(pos2).lIdOrgano == lIdOrgano)
					{
						if ((lX == m_RigaEsame[nEsame].listPunti.GetAt(pos2).lX) && (lY == m_RigaEsame[nEsame].listPunti.GetAt(pos2).lY))
						{
							bFindIndex = TRUE;
							break;
						}
					}

					m_RigaEsame[nEsame].listPunti.GetNext(pos2);
					img_organi.iPunto++;
				}

				if (bFindIndex == FALSE)
				{
					tagPunti puntoTemp;

					puntoTemp.lIdPunto = lIdPunto;
					puntoTemp.lIdOrgano = lIdOrgano;
					puntoTemp.lX = lX;
					puntoTemp.lY = lY;

					m_RigaEsame[nEsame].listPunti.AddTail(puntoTemp);

					img_organi.iPunto = m_RigaEsame[nEsame].listPunti.GetCount() - 1;
				}

				m_RigaEsame[nEsame].ImgListOrgani.SetAt(pos1, img_organi);
			}
		}
		m_RigaEsame[nEsame].ImgListOrgani.GetNext(pos1);
	}
}