#include "stdafx.h"
#include "Endox.h"

#include "CodificaRegionaleExSet.h"
#include "EsamiView.h"
#include "GruppiPrestazioniSet.h"
#include "MalattieCronicheSet.h"
#include "MstOrganoSet.h"
#include "TipoEsameDlg.h"
#include "TipoEsameSet.h"
#include "TipiEsamiOrganiSet.h"
#include "TipiEsamiPrestazioniSet.h"
#include "TipiEsamiGruppiPrestazioniSet.h"
#include "TipoEsameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTipoEsameDlg::CTipoEsameDlg(CEsamiView* pEsamiView)
	: CDialog(CTipoEsameDlg::IDD, (CWnd*)pEsamiView)
{
	m_pEsamiView = pEsamiView;

	m_sDescrizione = "";
	m_sSigla = "";
	m_iPrivato = BST_UNCHECKED;
	m_iEsameScreening = BST_UNCHECKED;
	m_iErogaSoloPP = BST_UNCHECKED;

	m_lSavedPosition = -1;
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	m_bOrPressed = FALSE;

	m_clColor = GetSysColor(COLOR_BTNFACE);
	m_clColorM1 = RGB(0, 0, 0);
	m_clColorM2 = RGB(255, 255, 255);
}

CTipoEsameDlg::~CTipoEsameDlg()
{
}

BEGIN_MESSAGE_MAP(CTipoEsameDlg, CDialog)

	ON_BN_CLICKED(IDC_TIPOESAME_CANC, OnTipoEsameDelete)
	ON_BN_CLICKED(IDC_TIPOESAME_MODIFY, OnTipoEsameModify)
	ON_BN_CLICKED(IDC_TIPOESAME_NUOVO, OnTipoEsameNew)
	ON_BN_CLICKED(IDC_TIPOESAME_REFRESH, OnTipoEsameRefresh)
	ON_BN_CLICKED(IDC_TIPOESAME_UPDATE, OnTipoEsameUpdate)
	ON_BN_CLICKED(IDC_BTN_RESETCOLOR, OnBtnResetColor)
	ON_BN_CLICKED(IDC_BTN_OR, OnBtnOr)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)

	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)

	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()

END_MESSAGE_MAP()

void CTipoEsameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_TIPI, m_ctrlStaticTipi);
	DDX_Control(pDX, IDC_STATIC_ORGANI, m_ctrlStaticOrgani);
	DDX_Control(pDX, IDC_STATIC_GRUPPI, m_ctrlStaticGruppi);
	DDX_Control(pDX, IDC_STATIC_PRESTAZIONI, m_ctrlStaticPrestazioni);
	DDX_Control(pDX, IDC_STATIC_ESAME, m_ctrlStaticEsame);
	DDX_Control(pDX, IDC_STATIC_SIGLA, m_ctrlStaticSigla);
	DDX_Control(pDX, IDC_STATIC_PRIVATO, m_ctrlStaticPrivato);
	DDX_Control(pDX, IDC_STATIC_SCREENING, m_ctrlStaticScreening);
	DDX_Control(pDX, IDC_STATIC_EROGA_SOLO_PP, m_ctrlStaticErogaSoloPP);
	DDX_Control(pDX, IDC_STATIC_SFONDO, m_ctrlStaticSfondo);
	DDX_Control(pDX, IDC_STATIC_MONITOR, m_ctrlStaticMonitor);
	DDX_Control(pDX, IDC_STATIC_CRONICITA, m_ctrlStaticCronicita);

	DDX_Control(pDX, IDC_TIPOESAME_NUOVO,   m_ctrlButtonNew);
	DDX_Control(pDX, IDC_TIPOESAME_MODIFY,  m_ctrlButtonModify);
	DDX_Control(pDX, IDC_TIPOESAME_CANC,    m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_TIPOESAME_UPDATE,  m_ctrlButtonUpdate);
	DDX_Control(pDX, IDC_TIPOESAME_REFRESH, m_ctrlButtonRefresh);
	DDX_Control(pDX, IDCANCEL,              m_ctrlButtonCancel);
	
	DDX_Control(pDX, IDC_LISTA,		m_ctrlLista);
	DDX_Control(pDX, IDC_ORGANI,	m_ctrlListOrgani);
	DDX_Control(pDX, IDC_GRUPPI,	m_ctrlListGruppi);
	DDX_Control(pDX, IDC_PRESTAZIONI, m_ctrlListPrestazioni);

	DDX_Text(pDX, IDC_DESCRIZIONE, m_sDescrizione);
	DDX_Text(pDX, IDC_SIGLA, m_sSigla);
	DDX_Check(pDX, IDC_CHECK_PRIVATO, m_iPrivato);
	DDX_Check(pDX, IDC_CHECK_SCREENING, m_iEsameScreening);
	DDX_Check(pDX, IDC_CHECK_EROGA_SOLO_PP, m_iErogaSoloPP);
	DDX_Control(pDX, IDC_COMBO_CRONICITA, m_ctrlComboCronicita);
}

BOOL CTipoEsameDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Sandro 04/06/2013 // RIMA 13070 //

	if (theApp.m_lOpzionalePazientiCronici != OPZIONALE_PAZIENTI_CRONICI)
	{
		GetDlgItem(IDC_STATIC_CRONICITA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_CRONICITA)->ShowWindow(SW_HIDE);
	}
	else
	{
		RiempiComboCronicita();
	}

	// Sandro 15/04/2014 //

	// if (theApp.m_bPersonalizzazioniAcireale)
	{
		m_ctrlStaticMonitor.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_COLOR_M1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_COLOR_M2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PREVIEW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PREVIEW_BORDER)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_PREVIEW)->SetFont(&theApp.m_fontBig);
	}

	//
	
	m_ctrlListOrgani.EnableWindow(FALSE);
	m_ctrlListGruppi.EnableWindow(FALSE);
	m_ctrlListPrestazioni.EnableWindow(FALSE);

	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_TIPI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_ORGANI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_GRUPPI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_PRESTAZIONI)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	
	GetDlgItem(IDC_TIPOESAME_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIPOESAME_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_BTN_RESETCOLOR)->EnableWindow(FALSE);

	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIGLA)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_PRIVATO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_SCREENING)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_EROGA_SOLO_PP)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_CRONICITA)->EnableWindow(FALSE);

	RiempiListaTipoEsame();

	// 10/02/2003
	m_bRicercaAttivata = theApp.m_nProgramMode & FILTER_RECORD_ESAMI;
	
	if (m_bRicercaAttivata)
	{
		// se sono in ricerca attivo pulsante or e ridimensiono testo descrizione //
		CRect rectText, rectBtn;
		GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_DESCRIZIONE)->GetWindowRect(&rectText);
		GetDlgItem(IDC_BTN_OR)->GetWindowRect(&rectBtn);
		
		GetDlgItem(IDC_DESCRIZIONE)->SetWindowPos(&wndTop, 0, 0, rectText.Width() - rectBtn.Width() - 5, rectText.Height(), SWP_NOMOVE);
	}
	else
	{
		GetDlgItem(IDC_BTN_OR)->ShowWindow(SW_HIDE);

		RiempiListaOrgani();
		RiempiListaGruppi();
		RiempiListaPrestazioni();
	}
	
	GetDlgItem(IDC_BTN_OR)->EnableWindow(FALSE);
	m_nItemCount = m_ctrlLista.GetCount();

	theApp.LocalizeDialog(this, CTipoEsameDlg::IDD, "TipoEsameDlg");
	return TRUE;
}

HBRUSH CTipoEsameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_TIPI:
		case IDC_STATIC_ESAME:
		case IDC_DESCRIZIONE:
		case IDC_STATIC_SIGLA:
		case IDC_SIGLA:
		case IDC_STATIC_PRIVATO:
		case IDC_STATIC_SCREENING:
		case IDC_STATIC_EROGA_SOLO_PP:
		case IDC_CHECK_PRIVATO:
		case IDC_STATIC_SFONDO:
		case IDC_STATIC_MONITOR:
		case IDC_STATIC_CRONICITA:
		case IDC_COMBO_CRONICITA:
		{
			pDC->SetTextColor(theApp.m_color[0]);
			break;
		}
		case IDC_LISTA:
		{
			if (m_ctrlLista.IsWindowEnabled())
				pDC->SetTextColor(theApp.m_color[0]);
			else
				pDC->SetTextColor(RGB(95, 95, 95));
			break;
		}
		case IDC_STATIC_ORGANI:
		{
			pDC->SetTextColor(theApp.m_color[1]);
			break;
		}
		case IDC_ORGANI:
		{
			if (m_ctrlListOrgani.IsWindowEnabled())
				pDC->SetTextColor(theApp.m_color[1]);
			else
				pDC->SetTextColor(RGB(95, 95, 95));
			break;
		}
		case IDC_STATIC_GRUPPI:
		case IDC_STATIC_PRESTAZIONI:
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
		case IDC_GRUPPI:
		{
			if (m_ctrlListGruppi.IsWindowEnabled())
				pDC->SetTextColor(theApp.m_color[2]);
			else
				pDC->SetTextColor(RGB(95, 95, 95));
			break;
		}
		case IDC_PRESTAZIONI:
		{
			if (m_ctrlListPrestazioni.IsWindowEnabled())
				pDC->SetTextColor(theApp.m_color[2]);
			else
				pDC->SetTextColor(RGB(95, 95, 95));
			break;
		}
		case IDC_STATIC_PREVIEW:
		{
			// if (theApp.m_bPersonalizzazioniAcireale)
			{
				m_brushSfondo.DeleteObject();
				m_brushSfondo.CreateSolidBrush(m_clColorM1);

				pDC->SetTextColor(m_clColorM2);
				pDC->SetBkColor(m_clColorM1);
				hBrush = m_brushSfondo;
			}
			break;
		}
	}

	return hBrush;
}

void CTipoEsameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags, point);

	if (m_bAddNew || m_bModify)
	{
		CRect rect;

		GetDlgItem(IDC_STATIC_COLOR)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		if (rect.PtInRect(point))
		{
			CColorDialog dlg(m_clColor);
			if (dlg.DoModal() == IDOK)
				m_clColor = dlg.GetColor();
		}
		InvalidateRect(&rect);

		// if (theApp.m_bPersonalizzazioniAcireale)
		{
			GetDlgItem(IDC_STATIC_COLOR_M1)->GetWindowRect(&rect);
			ScreenToClient(&rect);
			if (rect.PtInRect(point))
			{
				CColorDialog dlg(m_clColorM1);
				if (dlg.DoModal() == IDOK)
					m_clColorM1 = dlg.GetColor();
			}
			InvalidateRect(&rect);

			GetDlgItem(IDC_STATIC_COLOR_M2)->GetWindowRect(&rect);
			ScreenToClient(&rect);
			if (rect.PtInRect(point))
			{
				CColorDialog dlg(m_clColorM2);
				if (dlg.DoModal() == IDOK)
					m_clColorM2 = dlg.GetColor();
			}
			InvalidateRect(&rect);

			GetDlgItem(IDC_STATIC_PREVIEW_BORDER)->GetWindowRect(&rect);
			ScreenToClient(&rect);
			InvalidateRect(&rect);
		}
	}
}

void CTipoEsameDlg::OnPaint()
{
	CPaintDC dc(this);
	
	CRect rect;

	GetDlgItem(IDC_STATIC_COLOR)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	dc.FillRect(&rect, &CBrush(m_clColor));

	// if (theApp.m_bPersonalizzazioniAcireale)
	{
		GetDlgItem(IDC_STATIC_COLOR_M1)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		dc.FillRect(&rect, &CBrush(m_clColorM1));

		GetDlgItem(IDC_STATIC_COLOR_M2)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		dc.FillRect(&rect, &CBrush(m_clColorM2));
	}
}

void CTipoEsameDlg::OnOK() 
{
	if (m_ctrlButtonCancel.IsWindowEnabled())
		CDialog::OnOK();
}

void CTipoEsameDlg::OnBnClickedCancel()
{
	if (GetDlgItem(IDCANCEL)->IsWindowEnabled())
	{
		m_strRicercaView = m_sDescrizione;
		
		if (m_strRicerca.Right(4) == " OR ")
		{
			m_strRicerca = m_strRicerca.Left(m_strRicerca.GetLength() - 4);
			m_strRicercaView = m_strRicercaView.Left(m_strRicercaView.GetLength() - 4);
		}
		
		UpdateData(FALSE);

		OnOK();
	}
}

void CTipoEsameDlg::OnBtnOr()
{
	m_bOrPressed = TRUE;
	
	m_sDescrizione += " OR ";
	m_strRicerca += " OR ";

	GetDlgItem(IDC_BTN_OR)->EnableWindow(FALSE);
	
	UpdateData(FALSE);
}

void CTipoEsameDlg::OnSelchangeLista() 
{
	if (m_bAddNew || m_bModify)
		return;

	m_clColor = GetSysColor(COLOR_BTNFACE);
	m_clColorM1 = RGB(0, 0, 0);
	m_clColorM2 = RGB(255, 255, 255);

	int nCount = m_ctrlLista.GetCount();
	if (nCount > 0)
	{
		int nCurPos = m_ctrlLista.GetCurSel();

		BOOL bRicerca = theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI || theApp.m_nProgramMode & FILTER_RECORD_ESAMI;
		GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(m_ctrlLista.GetCurSel() >= 0 && !bRicerca);
		GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(m_ctrlLista.GetCurSel() >= 0 && !bRicerca);

		if (nCurPos >= 0)
		{
			DWORD dwCode = m_ctrlLista.GetItemData(nCurPos);
			if (dwCode >= 0)
			{
				CString sFilter;
				sFilter.Format("Contatore=%li", (long)dwCode);

				CTipoEsameSet setTipoEsame;
				setTipoEsame.SetOpenFilter(sFilter);
				if (setTipoEsame.OpenRecordset("CTipoEsameDlg::OnSelchangeLista"))
				{
					if (!setTipoEsame.IsEOF())
					{
						if (m_bRicercaAttivata)
						{
							if (m_bOrPressed)
							{
								CString strTmp;
								strTmp.Format("%i ", setTipoEsame.m_lContatore);

								if (CanBeInserted(setTipoEsame.m_lContatore))
								{
									m_sDescrizione += setTipoEsame.m_sDescrizione;
									strTmp.Format("%i", setTipoEsame.m_lContatore);
									m_strRicerca += strTmp;

									m_bOrPressed = FALSE;
									m_nItemPressed++;

									if (m_nItemPressed < m_nItemCount)
										GetDlgItem(IDC_BTN_OR)->EnableWindow(TRUE);
								}
							}
							else
							{
								GetDlgItem(IDC_BTN_OR)->EnableWindow(TRUE);
								m_strRicerca.Format("%i", setTipoEsame.m_lContatore);
								m_sDescrizione = setTipoEsame.m_sDescrizione;
								m_nItemPressed = 1;
							}
						}
						else
						{
							m_sDescrizione = setTipoEsame.m_sDescrizione;
							m_sSigla = setTipoEsame.m_sSigla;
							m_iPrivato = (setTipoEsame.m_bPrivato ? BST_CHECKED : BST_UNCHECKED);
							m_iEsameScreening = (setTipoEsame.m_bEsameScreening ? BST_CHECKED : BST_UNCHECKED);
							m_iErogaSoloPP = (setTipoEsame.m_bErogaSoloPrestazioniPrincipali ? BST_CHECKED : BST_UNCHECKED);

							if (setTipoEsame.m_lSfondo >= 0)
								m_clColor = setTipoEsame.m_lSfondo;

							m_clColorM1 = setTipoEsame.m_lEliminaCodeBack;
							m_clColorM2 = setTipoEsame.m_lEliminaCodeFore;

							BeginWaitCursor();

							SelezionaComboCronicita(setTipoEsame.m_lIDCronicita);
							SelezionaOrgani(setTipoEsame.m_lContatore);
							SelezionaGruppi(setTipoEsame.m_lContatore);
							SelezionaPrestazioni(setTipoEsame.m_lContatore);

							EndWaitCursor();
						}

						m_lSavedPosition = nCurPos;
					}

					setTipoEsame.CloseRecordset("CTipoEsameDlg::OnSelchangeLista");
				}

				UpdateData(FALSE);
			}
		}
	}

	CRect rect;

	GetDlgItem(IDC_STATIC_COLOR)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);

	// if (theApp.m_bPersonalizzazioniAcireale)
	{
		GetDlgItem(IDC_STATIC_COLOR_M1)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		InvalidateRect(&rect);

		GetDlgItem(IDC_STATIC_COLOR_M2)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		InvalidateRect(&rect);

		GetDlgItem(IDC_STATIC_PREVIEW_BORDER)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		InvalidateRect(&rect);
	}
}

BOOL CTipoEsameDlg::CanBeInserted(long lContatore)
{
	CString strContatore, strTmp;

	//Controllo inizio stringa
	strContatore.Format("%i ", lContatore);
	strTmp = m_strRicerca.Left(strContatore.GetLength());

	if (strTmp == strContatore)
		return FALSE;

	//Controllo in mezzo alla stringa
	strContatore.Format(" %i ", lContatore);

	if (m_strRicerca.Find(strContatore) > 0)
		return FALSE;

	//Controllo alla fine
	strContatore.Format(" %i", lContatore);
	strTmp = m_strRicerca.Right(strContatore.GetLength());

	if (strTmp == strContatore)
		return FALSE;

	return TRUE;
}

void CTipoEsameDlg::OnTipoEsameDelete() 
{
	BOOL bDeleted = FALSE;

	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlListOrgani.EnableWindow(FALSE);
	m_ctrlListGruppi.EnableWindow(FALSE);
	m_ctrlListPrestazioni.EnableWindow(FALSE);

	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIGLA)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_PRIVATO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_SCREENING)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_EROGA_SOLO_PP)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_CRONICITA)->EnableWindow(FALSE);

	GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	GetDlgItem(IDC_TIPOESAME_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIPOESAME_REFRESH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_RESETCOLOR)->EnableWindow(FALSE);

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TIPOESAMEDLG_DELETE_CONFIRM), MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		return;

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TIPOESAMEDLG_DELETE_CONFIRM_2), MB_YESNO | MB_ICONSTOP) == IDYES)
		return;

	int posiz = m_ctrlLista.GetCurSel();
	if (posiz >= 0)
	{
		DWORD dwCode = m_ctrlLista.GetItemData(posiz);
	
		if (dwCode >= 0)
		{
			CString sFilter;
			sFilter.Format("Contatore=%li", (long) dwCode);
		
			CTipoEsameSet setTipoEsame;
			setTipoEsame.SetOpenFilter(sFilter);
		
			if (setTipoEsame.OpenRecordset("CTipoEsameDlg::OnTipoEsameDelete"))
			{
				if (!setTipoEsame.IsEOF())
				{
					if (setTipoEsame.DeleteRecordset("CTipoEsameDlg::OnTipoEsameDelete"))
					{
						int nRemained = m_ctrlLista.DeleteString(posiz);
						int nNewPos = min(posiz, nRemained - 1);

						m_ctrlLista.SetCurSel(nNewPos);

						OnSelchangeLista();
					}
				}

				setTipoEsame.CloseRecordset("CTipoEsameDlg::OnTipoEsameDelete");
			}
		}
	}
	
	UpdateData(FALSE);
	RedrawWindow();
}

void CTipoEsameDlg::OnTipoEsameModify() 
{
	int nSelect = m_ctrlLista.GetCurSel();
		
	if (nSelect >= 0)
	{
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

		m_ctrlLista.EnableWindow(FALSE);
		m_ctrlListOrgani.EnableWindow(TRUE);
		m_ctrlListGruppi.EnableWindow(TRUE);
		m_ctrlListPrestazioni.EnableWindow(TRUE);

		GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(TRUE);
		GetDlgItem(IDC_SIGLA)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_PRIVATO)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_SCREENING)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_EROGA_SOLO_PP)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_CRONICITA)->EnableWindow(TRUE);

		GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(FALSE);
		GetDlgItem(IDC_TIPOESAME_UPDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_TIPOESAME_REFRESH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_RESETCOLOR)->EnableWindow(TRUE);

		m_bModify = TRUE;

		UpdateData(FALSE);
		RedrawWindow();
	}
}

void CTipoEsameDlg::OnTipoEsameNew() 
{
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	m_ctrlLista.EnableWindow(FALSE);
	m_ctrlListOrgani.EnableWindow(TRUE);
	m_ctrlListGruppi.EnableWindow(TRUE);
	m_ctrlListPrestazioni.EnableWindow(TRUE);

	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(TRUE);
	GetDlgItem(IDC_SIGLA)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_PRIVATO)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_SCREENING)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_EROGA_SOLO_PP)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_CRONICITA)->EnableWindow(TRUE);

	GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIPOESAME_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_TIPOESAME_REFRESH)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_RESETCOLOR)->EnableWindow(TRUE);

	// Deseleziono tutti gli elementi dalle liste degli organi e delle prestazioni //
	m_ctrlListOrgani.SelItemRange(FALSE, 0, m_ctrlListOrgani.GetCount() - 1);
	m_ctrlListGruppi.SelItemRange(FALSE, 0, m_ctrlListGruppi.GetCount() - 1);
	m_ctrlListPrestazioni.SelItemRange(FALSE, 0, m_ctrlListPrestazioni.GetCount() - 1);

	m_sDescrizione = "";
	m_sSigla = "";
	m_iPrivato = BST_UNCHECKED;
	m_iEsameScreening = BST_UNCHECKED;
	m_iErogaSoloPP = BST_UNCHECKED;
	m_clColor = GetSysColor(COLOR_BTNFACE);
	m_clColorM1 = RGB(0, 0, 0);
	m_clColorM2 = RGB(255, 255, 255);
	m_ctrlComboCronicita.SetCurSel(0);

	m_bAddNew = TRUE;

	UpdateData(FALSE);
	RedrawWindow();
}

void CTipoEsameDlg::OnTipoEsameRefresh() 
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlListOrgani.EnableWindow(FALSE);
	m_ctrlListGruppi.EnableWindow(FALSE);
	m_ctrlListPrestazioni.EnableWindow(FALSE);

	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIGLA)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_PRIVATO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_SCREENING)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_EROGA_SOLO_PP)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_CRONICITA)->EnableWindow(FALSE);

	GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	GetDlgItem(IDC_TIPOESAME_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIPOESAME_REFRESH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_RESETCOLOR)->EnableWindow(FALSE);

	if (m_lSavedPosition <= m_ctrlLista.GetCount())
	{
		int nPos = m_lSavedPosition;

		if (nPos < 0 && m_ctrlLista.GetCount())
			nPos = 0;
	
		m_lSavedPosition = -1;

		m_ctrlLista.SetCurSel(nPos);

		OnSelchangeLista();
	}
	RedrawWindow();
}

void CTipoEsameDlg::OnTipoEsameUpdate() 
{
	BOOL bSaved = FALSE;
	long lAdded = -1;
	
	UpdateData(TRUE);

	if (m_sDescrizione.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TIPOESAMEDLG_EMPTY_DESC), MB_ICONINFORMATION);
		return;
	}

	if (m_sSigla.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TIPOESAMEDLG_EMPTY_SIGLA), MB_ICONINFORMATION);
		return;
	}

	DWORD dwCode = 0;

	int nCurPos = m_ctrlLista.GetCurSel();
	if (nCurPos >= 0)
		dwCode = m_ctrlLista.GetItemData(nCurPos);

	if (m_bAddNew)
	{
		CTipoEsameSet setTipoEsame;
		if (setTipoEsame.OpenRecordset("CTipoEsameDlg::OnTipoEsameUpdate"))
		{
			if (setTipoEsame.AddNewRecordset("CTipoEsameDlg::OnTipoEsameUpdate"))
			{
				setTipoEsame.m_sDescrizione = m_sDescrizione;
				setTipoEsame.m_sSigla = m_sSigla;
				setTipoEsame.m_bPrivato = (m_iPrivato == BST_UNCHECKED ? FALSE : TRUE);
				setTipoEsame.m_bEsameScreening = (m_iEsameScreening == BST_UNCHECKED ? FALSE : TRUE);
				setTipoEsame.m_bErogaSoloPrestazioniPrincipali = (m_iErogaSoloPP == BST_UNCHECKED ? FALSE : TRUE);

				if (m_clColor == GetSysColor(COLOR_BTNFACE))
					setTipoEsame.m_lSfondo = -1;
				else
					setTipoEsame.m_lSfondo = m_clColor;

				setTipoEsame.m_lEliminaCodeBack = m_clColorM1;
				setTipoEsame.m_lEliminaCodeFore = m_clColorM2;

				int nComboCurSel = m_ctrlComboCronicita.GetCurSel();
				if (nComboCurSel > 0)
					setTipoEsame.m_lIDCronicita = m_ctrlComboCronicita.GetItemData(nComboCurSel);
				else
					setTipoEsame.m_lIDCronicita = 0;

				setTipoEsame.m_lContatoreAnnuale = 0;
				setTipoEsame.m_lAnno = 0;

				bSaved = setTipoEsame.UpdateRecordset("CTipoEsameDlg::OnTipoEsameUpdate");
				if (bSaved)
				{
					lAdded = setTipoEsame.GetLastAdd();
					if (lAdded > 0)
					{
						SalvaOrgani(lAdded);
						SalvaGruppi(lAdded);
						SalvaPrestazioni(lAdded);
					}
				}
			}

			setTipoEsame.CloseRecordset("CTipoEsameDlg::OnTipoEsameUpdate");
		}
	}
	else
	{
		if (dwCode >= 0)
		{
			CString sFilter;
			sFilter.Format("Contatore=%li", (long)dwCode);

			CTipoEsameSet setTipoEsame;
			setTipoEsame.SetOpenFilter(sFilter);
			if (setTipoEsame.OpenRecordset("CTipoEsameDlg::OnTipoEsameUpdate"))
			{
				if (setTipoEsame.IsEOF())
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TIPOESAMEDLG_ALREADY_DEL), MB_ICONINFORMATION);
				}
				else
				{
					if (setTipoEsame.EditRecordset("CTipoEsameDlg::OnTipoEsameUpdate"))
					{
						setTipoEsame.m_sDescrizione = m_sDescrizione;
						setTipoEsame.m_sSigla = m_sSigla;
						setTipoEsame.m_bPrivato = (m_iPrivato == BST_UNCHECKED ? FALSE : TRUE);
						setTipoEsame.m_bEsameScreening = (m_iEsameScreening == BST_UNCHECKED ? FALSE : TRUE);
						setTipoEsame.m_bErogaSoloPrestazioniPrincipali = (m_iErogaSoloPP == BST_UNCHECKED ? FALSE : TRUE);

						if (m_clColor == GetSysColor(COLOR_BTNFACE))
							setTipoEsame.m_lSfondo = -1;
						else
							setTipoEsame.m_lSfondo = m_clColor;

						setTipoEsame.m_lEliminaCodeBack = m_clColorM1;
						setTipoEsame.m_lEliminaCodeFore = m_clColorM2;

						int nComboCurSel = m_ctrlComboCronicita.GetCurSel();
						if (nComboCurSel > 0)
							setTipoEsame.m_lIDCronicita = m_ctrlComboCronicita.GetItemData(nComboCurSel);
						else
							setTipoEsame.m_lIDCronicita = 0;

						bSaved = setTipoEsame.UpdateRecordset("CTipoEsameDlg::OnTipoEsameUpdate");

						SalvaOrgani(dwCode);
						SalvaGruppi(dwCode);
						SalvaPrestazioni(dwCode);
					}
				}
			}
		}
	}
	
	if (bSaved)	
	{
		int posiz;
		if (m_bAddNew)
		{
			posiz = m_ctrlLista.AddString(m_sDescrizione);
			m_ctrlLista.SetItemData(posiz, (DWORD)lAdded);
			m_ctrlLista.SetCurSel(posiz);
		}
		else
		{
			posiz = m_ctrlLista.GetCurSel();
			if (posiz >= 0)
			{
				m_ctrlLista.DeleteString(posiz);

				posiz = m_ctrlLista.InsertString(posiz, m_sDescrizione);
				if (posiz >= 0)
				{
					m_ctrlLista.SetItemData(posiz, (DWORD)dwCode);
					m_ctrlLista.SetCurSel(posiz);
				}
			}
		}

		GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

		m_ctrlLista.EnableWindow(TRUE);
		m_ctrlListOrgani.EnableWindow(FALSE);
		m_ctrlListGruppi.EnableWindow(FALSE);
		m_ctrlListPrestazioni.EnableWindow(FALSE);

		GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIGLA)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_PRIVATO)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_SCREENING)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_EROGA_SOLO_PP)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_CRONICITA)->EnableWindow(FALSE);

		GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(TRUE);
		GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
		GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
		GetDlgItem(IDC_TIPOESAME_UPDATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_TIPOESAME_REFRESH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_RESETCOLOR)->EnableWindow(FALSE);

		m_bModify = FALSE;
		m_bAddNew = FALSE;

		OnSelchangeLista();
	}
	RedrawWindow();
}

void CTipoEsameDlg::OnBtnResetColor()
{
	m_clColor = GetSysColor(COLOR_BTNFACE);

	CRect rect;
	GetDlgItem(IDC_STATIC_COLOR)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);
}

void CTipoEsameDlg::RiempiListaOrgani()
{
	CMstOrganoSet setTemp;

	setTemp.SetSortRecord("Organo");
	if (setTemp.OpenRecordset("CTipoEsameDlg::RiempiListaOrgani"))
	{
		int iTemp = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlListOrgani.InsertString(iTemp, setTemp.m_sOrgano);
			m_ctrlListOrgani.SetItemData(iTemp, (DWORD)setTemp.m_lContatore);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CTipoEsameDlg::RiempiListaOrgani");
	}
}

void CTipoEsameDlg::RiempiListaGruppi()
{
	CGruppiPrestazioniSet setTemp;

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CTipoEsameDlg::RiempiListaGruppi"))
	{
		int iTemp = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlListGruppi.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListGruppi.SetItemData(iTemp, (DWORD)setTemp.m_lID);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CTipoEsameDlg::RiempiListaGruppi");
	}
}

void CTipoEsameDlg::RiempiListaPrestazioni()
{
	CCodificaRegionaleExSet setTemp;

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CTipoEsameDlg::RiempiListaPrestazioni"))
	{
		int iTemp = 0;

		while(!setTemp.IsEOF())
		{
			m_ctrlListPrestazioni.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListPrestazioni.SetItemData(iTemp, (DWORD)setTemp.m_lContatore);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CTipoEsameDlg::RiempiListaPrestazioni");
	}
}

void CTipoEsameDlg::RiempiListaTipoEsame()
{
	m_ctrlLista.SetTabStops(100);
	
	CTipoEsameSet setTipoEsame;
	setTipoEsame.SetSortRecord("Descrizione");
	if (setTipoEsame.OpenRecordset("CTipoEsameDlg::RiempiListaTipoEsame"))
	{
		while (!setTipoEsame.IsEOF())
		{
			int posiz = m_ctrlLista.AddString(setTipoEsame.m_sDescrizione);

			if (posiz >= 0)
				m_ctrlLista.SetItemData(posiz, (DWORD)setTipoEsame.m_lContatore);

			setTipoEsame.MoveNext();
		}

		setTipoEsame.CloseRecordset("CTipoEsameDlg::RiempiListaTipoEsame");
	}
	
	OnSelchangeLista();
}

void CTipoEsameDlg::SalvaOrgani(long lContatoreEsame)
{
	int iTemp;
	CString strTemp;
	CTipiEsamiOrganiSet setTemp;

	strTemp.Format("TipoEsame=%li", lContatoreEsame);
	setTemp.SetBaseFilter(strTemp);
	
	// per ogni organo in lista controllo se è selezionato o meno //
	for(iTemp = 0; iTemp < m_ctrlListOrgani.GetCount(); iTemp++)
	{
		if (m_ctrlListOrgani.GetSel(iTemp) > 0)
		{
			// l'elemento è selezionato e quindi se non lo trovo nel db lo aggiungo //

			strTemp.Format("Organo=%li", (long)m_ctrlListOrgani.GetItemData(iTemp));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CTipoEsameDlg::SalvaOrgani"))
			{
				if (setTemp.IsEOF())
				{
					// non c'è e quindi lo aggiungo //

					if (setTemp.AddNewRecordset("CTipoEsameDlg::SalvaOrgani"))
					{
						setTemp.m_lTipoEsame = lContatoreEsame;
						setTemp.m_lOrgano = (long)m_ctrlListOrgani.GetItemData(iTemp);

						setTemp.UpdateRecordset("CTipoEsameDlg::SalvaOrgani");
					}
				}

				setTemp.CloseRecordset("CTipoEsameDlg::SalvaOrgani");
			}
		}
		else
		{
			// l'elemento NON è selezionato e quindi se lo trovo nel db lo cancello //

			strTemp.Format("Organo=%li", (long)m_ctrlListOrgani.GetItemData(iTemp));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CTipoEsameDlg::SalvaOrgani"))
			{
				if (!setTemp.IsEOF())
				{
					// c'è e quindi lo elimino //

					setTemp.DeleteRecordset("CTipoEsameDlg::SalvaOrgani");
				}
			}
		}
	}
}

void CTipoEsameDlg::SalvaGruppi(long lContatoreEsame)
{
	int iTemp;
	CString strTemp;
	CTipiEsamiGruppiPrestazioniSet setTemp;

	strTemp.Format("TipoEsame=%li", lContatoreEsame);
	setTemp.SetBaseFilter(strTemp);
	
	// per ogni Prestazione in lista controllo se è selezionato o meno //
	for(iTemp = 0; iTemp < m_ctrlListGruppi.GetCount(); iTemp++)
	{
		if (m_ctrlListGruppi.GetSel(iTemp) > 0)
		{
			// l'elemento è selezionato e quindi se non lo trovo nel db lo aggiungo //

			strTemp.Format("Gruppo=%li", (long)m_ctrlListGruppi.GetItemData(iTemp));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CTipoEsameDlg::SalvaGruppi"))
			{
				if (setTemp.IsEOF())
				{
					// non c'è e quindi lo aggiungo //

					if (setTemp.AddNewRecordset("CTipoEsameDlg::SalvaGruppi"))
					{
						setTemp.m_lTipoEsame = lContatoreEsame;
						setTemp.m_lGruppo = (long)m_ctrlListGruppi.GetItemData(iTemp);

						setTemp.UpdateRecordset("CTipoEsameDlg::SalvaGruppi");
					}
				}

				setTemp.CloseRecordset("CTipoEsameDlg::SalvaGruppi");
			}
		}
		else
		{
			// l'elemento NON è selezionato e quindi se lo trovo nel db lo cancello //

			strTemp.Format("Gruppo=%li", (long)m_ctrlListGruppi.GetItemData(iTemp));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CTipoEsameDlg::SalvaGruppi"))
			{
				if (!setTemp.IsEOF())
				{
					// c'è e quindi lo elimino //

					setTemp.DeleteRecordset("CTipoEsameDlg::SalvaGruppi");
				}
			}
		}
	}
}

void CTipoEsameDlg::SalvaPrestazioni(long lContatoreEsame)
{
	int iTemp;
	CString strTemp;
	CTipiEsamiPrestazioniSet setTemp;

	strTemp.Format("TipoEsame=%li", lContatoreEsame);
	setTemp.SetBaseFilter(strTemp);
	
	// per ogni Prestazione in lista controllo se è selezionato o meno //
	for(iTemp = 0; iTemp < m_ctrlListPrestazioni.GetCount(); iTemp++)
	{
		if (m_ctrlListPrestazioni.GetSel(iTemp) > 0)
		{
			// l'elemento è selezionato e quindi se non lo trovo nel db lo aggiungo //

			strTemp.Format("Prestazione=%li", (long)m_ctrlListPrestazioni.GetItemData(iTemp));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CTipoEsameDlg::SalvaPrestazioni"))
			{
				if (setTemp.IsEOF())
				{
					// non c'è e quindi lo aggiungo //

					if (setTemp.AddNewRecordset("CTipoEsameDlg::SalvaPrestazioni"))
					{
						setTemp.m_lTipoEsame = lContatoreEsame;
						setTemp.m_lPrestazione = (long)m_ctrlListPrestazioni.GetItemData(iTemp);

						setTemp.UpdateRecordset("CTipoEsameDlg::SalvaPrestazioni");
					}
				}

				setTemp.CloseRecordset("CTipoEsameDlg::SalvaPrestazioni");
			}
		}
		else
		{
			// l'elemento NON è selezionato e quindi se lo trovo nel db lo cancello //

			strTemp.Format("Prestazione=%li", (long)m_ctrlListPrestazioni.GetItemData(iTemp));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CTipoEsameDlg::SalvaPrestazioni"))
			{
				if (!setTemp.IsEOF())
				{
					// c'è e quindi lo elimino //

					setTemp.DeleteRecordset("CTipoEsameDlg::SalvaPrestazioni");
				}
			}
		}
	}
}

void CTipoEsameDlg::SelezionaComboCronicita(long lIDCronicita)
{
	int nCurSel = 0;

	if (lIDCronicita > 0)
	{
		for(int i = 1; i < m_ctrlComboCronicita.GetCount(); i++)
		{
			if (m_ctrlComboCronicita.GetItemData(i) == lIDCronicita)
			{
				nCurSel = i;
				break;
			}
		}
	}

	m_ctrlComboCronicita.SetCurSel(nCurSel);
}

void CTipoEsameDlg::SelezionaOrgani(long lContatoreEsame)
{
	CString strTemp;
	CTipiEsamiOrganiSet setJoin;
	CMstOrganoSet setOrgano;

	// nascondo il controllo //
	m_ctrlListOrgani.ShowWindow(SW_HIDE);

	// Deseleziono tutti gli elementi //
	m_ctrlListOrgani.SelItemRange(FALSE, 0, m_ctrlListOrgani.GetCount() - 1);

	// Cerco nella tabella 'ETipiEsamiOrgani' tutti i record che hanno il 'TipoEsame' correntemente selezionato //
	strTemp.Format("TipoEsame=%li", lContatoreEsame);
	setJoin.SetOpenFilter(strTemp);

	if (setJoin.OpenRecordset("CTipoEsameDlg::SelezionaOrgani"))
	{
		while(!setJoin.IsEOF())
		{
			// Prendo dalla tabella 'EMSTOrgano' la descrizione per esteso dell'organo trovato nella tabella 'ETipiEsamiOrgani' //
			strTemp.Format("Contatore=%li", setJoin.m_lOrgano);
			setOrgano.SetOpenFilter(strTemp);

			if (setOrgano.OpenRecordset("CTipoEsameDlg::SelezionaOrgani"))
			{
				if (!setOrgano.IsEOF())
				{
					// Se trovo l'organo nella lista (e dovrei trovarlo, se sono arrivato qui) lo seleziono //
					int iFind = m_ctrlListOrgani.FindStringExact(-1, setOrgano.m_sOrgano);

					if (iFind != LB_ERR)
						m_ctrlListOrgani.SetSel(iFind, TRUE);
				}

				setOrgano.CloseRecordset("CTipoEsameDlg::SelezionaOrgani");
			}

			setJoin.MoveNext();
		}

		setJoin.CloseRecordset("CTipoEsameDlg::SelezionaOrgani");
	}

	// mi riposiziono all'inizio //
	m_ctrlListOrgani.SendMessage(WM_VSCROLL, SB_TOP, NULL);

	// mostro il controllo //
	m_ctrlListOrgani.ShowWindow(SW_SHOW);
}

void CTipoEsameDlg::SelezionaGruppi(long lContatoreEsame)
{
	CString strTemp;
	CTipiEsamiGruppiPrestazioniSet setJoin;
	CGruppiPrestazioniSet setGruppo;

	// nascondo il controllo //
	m_ctrlListGruppi.ShowWindow(SW_HIDE);

	// Deseleziono tutti gli elementi //
	m_ctrlListGruppi.SelItemRange(FALSE, 0, m_ctrlListGruppi.GetCount() - 1);

	// Cerco nella tabella 'ETipiEsamiGruppi' tutti i record che hanno il 'TipoEsame' correntemente selezionato //
	strTemp.Format("TipoEsame=%li", lContatoreEsame);
	setJoin.SetOpenFilter(strTemp);

	if (setJoin.OpenRecordset("CTipoEsameDlg::SelezionaGruppi"))
	{
		while(!setJoin.IsEOF())
		{
			// Prendo dalla tabella 'GruppiPrestazioni' la descrizione per esteso del Gruppo trovata nella tabella 'TipiEsamiGruppiPrestazioni' //
			strTemp.Format("ID=%li", setJoin.m_lGruppo);
			setGruppo.SetOpenFilter(strTemp);

			if (setGruppo.OpenRecordset("CTipoEsameDlg::SelezionaGruppi"))
			{
				if (!setGruppo.IsEOF())
				{
					// Se trovo l'organo nella lista (e dovrei trovarlo, se sono arrivato qui) lo seleziono //
					int iFind = m_ctrlListGruppi.FindStringExact(-1, setGruppo.m_sDescrizione);

					if (iFind != LB_ERR)
						m_ctrlListGruppi.SetSel(iFind, TRUE);
				}

				setGruppo.CloseRecordset("CTipoEsameDlg::SelezionaGruppi");
			}

			setJoin.MoveNext();
		}

		setJoin.CloseRecordset("CTipoEsameDlg::SelezionaGruppi");
	}

	// mi riposiziono all'inizio //
	m_ctrlListGruppi.SendMessage(WM_VSCROLL, SB_TOP, NULL);

	// mostro il controllo //
	m_ctrlListGruppi.ShowWindow(SW_SHOW);
}

void CTipoEsameDlg::SelezionaPrestazioni(long lContatoreEsame)
{
	CString strTemp;
	CTipiEsamiPrestazioniSet setJoin;
	CCodificaRegionaleExSet setPrestazione;

	// nascondo il controllo //
	m_ctrlListPrestazioni.ShowWindow(SW_HIDE);

	// Deseleziono tutti gli elementi //
	m_ctrlListPrestazioni.SelItemRange(FALSE, 0, m_ctrlListPrestazioni.GetCount() - 1);

	// Cerco nella tabella 'ETipiEsamiPrestazioni' tutti i record che hanno il 'TipoEsame' correntemente selezionato //
	strTemp.Format("TipoEsame=%li", lContatoreEsame);
	setJoin.SetOpenFilter(strTemp);

	if (setJoin.OpenRecordset("CTipoEsameDlg::SelezionaPrestazioni"))
	{
		while(!setJoin.IsEOF())
		{
			// Prendo dalla tabella 'ECodificaRegionaleEx' la descrizione per esteso della prestazione trovata nella tabella 'ETipiEsamiPrestazioni' //
			strTemp.Format("Contatore=%li", setJoin.m_lPrestazione);
			setPrestazione.SetOpenFilter(strTemp);

			if (setPrestazione.OpenRecordset("CTipoEsameDlg::SelezionaPrestazioni"))
			{
				if (!setPrestazione.IsEOF())
				{
					// Se trovo l'organo nella lista (e dovrei trovarlo, se sono arrivato qui) lo seleziono //
					int iFind = m_ctrlListPrestazioni.FindStringExact(-1, setPrestazione.m_sDescrizione);

					if (iFind != LB_ERR)
						m_ctrlListPrestazioni.SetSel(iFind, TRUE);
				}

				setPrestazione.CloseRecordset("CTipoEsameDlg::SelezionaPrestazioni");
			}

			setJoin.MoveNext();
		}

		setJoin.CloseRecordset("CTipoEsameDlg::SelezionaPrestazioni");
	}

	// mi riposiziono all'inizio //
	m_ctrlListPrestazioni.SendMessage(WM_VSCROLL, SB_TOP, NULL);

	// mostro il controllo //
	m_ctrlListPrestazioni.ShowWindow(SW_SHOW);
}

void CTipoEsameDlg::RiempiComboCronicita()
{
	m_ctrlComboCronicita.SetRedraw(FALSE);
	m_ctrlComboCronicita.ResetContent();

	m_ctrlComboCronicita.InsertString(0, "");
	m_ctrlComboCronicita.SetItemData(0, 0);

	CMalattieCronicheSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CTipoEsameDlg::RiempiComboCronicita"))
	{
		int nIndex = 1;

		while(!setTemp.IsEOF())
		{
			m_ctrlComboCronicita.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlComboCronicita.SetItemData(nIndex, setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CTipoEsameDlg::RiempiComboCronicita");
	}

	m_ctrlComboCronicita.SetRedraw(TRUE);
}