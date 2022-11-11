#include "stdafx.h"
#include "Endox.h"

#include "AssociazioniICD9Dlg.h"
#include "DiagnosiICD9Set.h"
#include "EsamiView.h"
#include "GruppiDiagnosiICD9DiagnosiICD9Set.h"
#include "GruppiDiagnosiICD9Set.h"
#include "GruppiProcedureICD9ProcedureICD9Set.h"
#include "GruppiProcedureICD9Set.h"
#include "ProcedureICD9Set.h"
#include "TipiEsamiDiagnosiICD9Set.h"
#include "TipiEsameGruppiDiagnosiICD9Set.h"
#include "TipiEsameGruppiProcedureICD9Set.h"
#include "TipiEsamiProcedureICD9Set.h"
#include "TipoEsameDlg.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAssociazioniICD9Dlg::CAssociazioniICD9Dlg(CEsamiView* pEsamiView)
	: CDialog(CAssociazioniICD9Dlg::IDD, (CWnd*)pEsamiView)
{
	m_pEsamiView = pEsamiView;

	m_sDescrizione = "";
	m_sSigla = "";

	m_bVisibile = FALSE;
	m_lSavedPosition = -1;
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	m_bOrPressed = FALSE;
}

CAssociazioniICD9Dlg::~CAssociazioniICD9Dlg()
{
}

BEGIN_MESSAGE_MAP(CAssociazioniICD9Dlg, CDialog)
	ON_LBN_SELCHANGE(IDC_LISTA,			OnSelchangeLista)
	ON_BN_CLICKED(IDC_TIPOESAME_CANC,	OnTipoEsameDelete)
	ON_BN_CLICKED(IDC_TIPOESAME_MODIFY, OnTipoEsameModify)
	ON_BN_CLICKED(IDC_TIPOESAME_NUOVO,	OnTipoEsameNew)
	ON_BN_CLICKED(IDC_TIPOESAME_REFRESH,OnTipoEsameRefresh)
	ON_BN_CLICKED(IDC_TIPOESAME_UPDATE, OnTipoEsameUpdate)
	ON_BN_CLICKED(IDC_BTN_OR,           OnBtnOr)
	ON_BN_CLICKED(IDCANCEL,				OnBnClickedCancel)
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_GRUPPI_DIAGNOSI, &CAssociazioniICD9Dlg::OnLbnSelchangeGruppiDiagnosi)
	ON_LBN_SELCHANGE(IDC_GRUPPI_PROCEDURE, &CAssociazioniICD9Dlg::OnLbnSelchangeGruppiProcedure)
END_MESSAGE_MAP()

void CAssociazioniICD9Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_TIPI, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_GRUPPI_PROCEDURE, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_GRUPPI_DIAGNOSI, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_ESAME, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_SIGLA, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_PROCEDUREICD9, m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC_DIAGNOSIICD9, m_ctrlStatic8);

	DDX_Control(pDX, IDC_TIPOESAME_NUOVO, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_TIPOESAME_MODIFY, m_ctrlButtonModify);
	DDX_Control(pDX, IDC_TIPOESAME_CANC, m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_TIPOESAME_UPDATE, m_ctrlButtonUpdate);
	DDX_Control(pDX, IDC_TIPOESAME_REFRESH, m_ctrlButtonRefresh);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	
	DDX_Control(pDX, IDC_LISTA, m_ctrlLista);
	DDX_Control(pDX, IDC_GRUPPI_PROCEDURE, m_ctrlListGruppiProcedure);
	DDX_Control(pDX, IDC_PROCEDUREICD9, m_ctrlListProcedure);
	DDX_Control(pDX, IDC_GRUPPI_DIAGNOSI, m_ctrlListGruppiDiagnosi);
	DDX_Control(pDX, IDC_DIAGNOSIICD9_2, m_ctrlListDiagnosi);

	DDX_Text(pDX, IDC_DESCRIZIONE, m_sDescrizione);
	DDX_Text(pDX, IDC_SIGLA, m_sSigla);
}

HBRUSH CAssociazioniICD9Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_TIPI:
		case IDC_STATIC_ESAME:
		case IDC_DESCRIZIONE:
		case IDC_STATIC_SIGLA:
		case IDC_SIGLA:
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
		case IDC_STATIC_PROCEDUREICD9:
		case IDC_STATIC_GRUPPI_PROCEDURE:
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
		case IDC_STATIC_DIAGNOSIICD9:
		case IDC_STATIC_GRUPPI_DIAGNOSI:
		{
			pDC->SetTextColor(theApp.m_color[3]);
			break;
		}
		case IDC_GRUPPI_DIAGNOSI:
		case IDC_DIAGNOSIICD9_2:
		{
			if (m_ctrlListProcedure.IsWindowEnabled())
				pDC->SetTextColor(theApp.m_color[3]);
			else
				pDC->SetTextColor(RGB(95, 95, 95));
			break;
		}
		case IDC_GRUPPI_PROCEDURE:
		case IDC_PROCEDUREICD9:
		{
			if (m_ctrlListProcedure.IsWindowEnabled())
				pDC->SetTextColor(theApp.m_color[2]);
			else
				pDC->SetTextColor(RGB(95, 95, 95));
			break;
		}
	}

	return hBrush;
}

BOOL CAssociazioniICD9Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlListGruppiDiagnosi.EnableWindow(FALSE);
	m_ctrlListDiagnosi.EnableWindow(FALSE);
	m_ctrlListGruppiProcedure.EnableWindow(FALSE);
	m_ctrlListProcedure.EnableWindow(FALSE);

	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_TIPI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_GRUPPI_PROCEDURE)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_PROCEDUREICD9)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_GRUPPI_DIAGNOSI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_DIAGNOSIICD9)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	
	GetDlgItem(IDC_TIPOESAME_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIPOESAME_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIGLA)->EnableWindow(FALSE);

	RiempiListaTipoEsame();

	// 10/02/2003
	m_bRicercaAttivata = theApp.m_nProgramMode & FILTER_RECORD_ESAMI;
	
	if (m_bRicercaAttivata)
	{
		//Se sono in ricerca attivo pulsante or e ridimensiono testo descrizione
		CRect rectText, rectBtn;
		GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_DESCRIZIONE)->GetWindowRect(&rectText);
		GetDlgItem(IDC_BTN_OR)     ->GetWindowRect(&rectBtn);
		
		GetDlgItem(IDC_DESCRIZIONE)->SetWindowPos(&wndTop, 0, 0, rectText.Width() - rectBtn.Width() - 5, rectText.Height(), SWP_NOMOVE);
	}
	else
	{
		GetDlgItem(IDC_BTN_OR)->ShowWindow(SW_HIDE);

		RiempiListaGruppiProcedure();
		RiempiListaProcedure();
		RiempiListaGruppiDiagnosi();
		RiempiListaDiagnosi();
	}
	
	GetDlgItem(IDC_BTN_OR)->EnableWindow(FALSE);
	m_nItemCount = m_ctrlLista.GetCount();

	theApp.LocalizeDialog(this, CAssociazioniICD9Dlg::IDD, "AssociazioniICD9Dlg");
	return TRUE;
}

void CAssociazioniICD9Dlg::OnOK() 
{
	if (m_ctrlButtonCancel.IsWindowEnabled())
		CDialog::OnOK();
}

void CAssociazioniICD9Dlg::OnBnClickedCancel()
{
	if (GetDlgItem(IDCANCEL)->IsWindowEnabled() == TRUE)
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

void CAssociazioniICD9Dlg::OnBtnOr()
{
	m_bOrPressed = TRUE;
	
	m_sDescrizione += " OR ";
	m_strRicerca += " OR ";

	GetDlgItem(IDC_BTN_OR)->EnableWindow(FALSE);
	
	UpdateData(FALSE);
}

void CAssociazioniICD9Dlg::OnSelchangeLista() 
{
	if (m_bAddNew || m_bModify)
		return;

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

				if (setTipoEsame.OpenRecordset("CAssociazioniICD9Dlg::OnSelchangeLista"))
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

							BeginWaitCursor();

							SelezionaGruppiProcedure(setTipoEsame.m_lContatore);
							SelezionaProcedure(setTipoEsame.m_lContatore);
							SelezionaGruppiDiagnosi(setTipoEsame.m_lContatore);
							SelezionaDiagnosi(setTipoEsame.m_lContatore);

							EndWaitCursor();
						}

						m_lSavedPosition = nCurPos;
					}

					setTipoEsame.CloseRecordset("CAssociazioniICD9Dlg::OnSelchangeLista");
				}

				UpdateData(FALSE);
			}
		}
	}
}

BOOL CAssociazioniICD9Dlg::CanBeInserted(long lContatore)
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

void CAssociazioniICD9Dlg::OnTipoEsameDelete() 
{
	BOOL bDeleted = FALSE;

	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlListGruppiProcedure.EnableWindow(FALSE);
	m_ctrlListProcedure.EnableWindow(FALSE);
	m_ctrlListGruppiDiagnosi.EnableWindow(FALSE);
	m_ctrlListDiagnosi.EnableWindow(FALSE);

	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIGLA)->EnableWindow(FALSE);

	GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	GetDlgItem(IDC_TIPOESAME_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIPOESAME_REFRESH)->EnableWindow(FALSE);

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
			sFilter.Format("Contatore=%li", (long)dwCode);
		
			CTipoEsameSet setTipoEsame;
			setTipoEsame.SetOpenFilter(sFilter);
			if (setTipoEsame.OpenRecordset("CAssociazioniICD9Dlg::OnTipoEsameDelete"))
			{
				if (!setTipoEsame.IsEOF())
				{
					if (setTipoEsame.DeleteRecordset("Tipo Esame"))
					{
						int nRemained = m_ctrlLista.DeleteString(posiz);
						int nNewPos = min(posiz, nRemained - 1);

						m_ctrlLista.SetCurSel(nNewPos);

						OnSelchangeLista();
					}
				}

				setTipoEsame.CloseRecordset("CAssociazioniICD9Dlg::OnTipoEsameDelete");
			}
		}
	}
	
	UpdateData(FALSE);
	RedrawWindow();
}

void CAssociazioniICD9Dlg::OnTipoEsameModify() 
{
	int nSelect = m_ctrlLista.GetCurSel();
		
	if (nSelect >= 0)
	{
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

		m_ctrlLista.EnableWindow(FALSE);
		m_ctrlListGruppiProcedure.EnableWindow(TRUE);
		m_ctrlListProcedure.EnableWindow(TRUE);
		m_ctrlListGruppiDiagnosi.EnableWindow(TRUE);
		m_ctrlListDiagnosi.EnableWindow(TRUE);
		GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(TRUE);
		GetDlgItem(IDC_SIGLA)->EnableWindow(TRUE);

		GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(FALSE);
		GetDlgItem(IDC_TIPOESAME_UPDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_TIPOESAME_REFRESH)->EnableWindow(TRUE);

		m_bModify = TRUE;

		UpdateData(FALSE);
		RedrawWindow();
	}			
}

void CAssociazioniICD9Dlg::OnTipoEsameNew() 
{
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	m_ctrlLista.EnableWindow(FALSE);
	m_ctrlListGruppiProcedure.EnableWindow(TRUE);
	m_ctrlListProcedure.EnableWindow(TRUE);
	m_ctrlListGruppiDiagnosi.EnableWindow(TRUE);
	m_ctrlListDiagnosi.EnableWindow(TRUE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(TRUE);
	GetDlgItem(IDC_SIGLA)->EnableWindow(TRUE);

	GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIPOESAME_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_TIPOESAME_REFRESH)->EnableWindow(TRUE);

	// Deseleziono tutti gli elementi dalle liste degli organi e delle prestazioni //
	m_ctrlListGruppiProcedure.SelItemRange(FALSE, 0, m_ctrlListGruppiProcedure.GetCount() - 1);
	m_ctrlListGruppiDiagnosi.SelItemRange(FALSE, 0, m_ctrlListGruppiDiagnosi.GetCount() - 1);

	m_sDescrizione = "";
	m_sSigla = "";
	m_bVisibile = TRUE;

	m_bAddNew = TRUE;

	UpdateData(FALSE);
	RedrawWindow();
}

void CAssociazioniICD9Dlg::OnTipoEsameRefresh() 
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlLista.EnableWindow(TRUE);
	m_ctrlListGruppiProcedure.EnableWindow(FALSE);
	m_ctrlListProcedure.EnableWindow(FALSE);
	m_ctrlListGruppiDiagnosi.EnableWindow(FALSE);
	m_ctrlListDiagnosi.EnableWindow(FALSE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIGLA)->EnableWindow(FALSE);

	GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
	GetDlgItem(IDC_TIPOESAME_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIPOESAME_REFRESH)->EnableWindow(FALSE);

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

void CAssociazioniICD9Dlg::OnTipoEsameUpdate() 
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

	if (m_bAddNew)
	{
		CTipoEsameSet setTipoEsame;
		setTipoEsame.SetOpenFilter("Contatore=0");
		if (setTipoEsame.OpenRecordset("CAssociazioniICD9Dlg::OnTipoEsameUpdate"))
		{
			if (setTipoEsame.AddNewRecordset("CAssociazioniICD9Dlg::OnTipoEsameUpdate"))
			{
				setTipoEsame.m_sDescrizione = m_sDescrizione;
				setTipoEsame.m_sSigla = m_sSigla;

				setTipoEsame.m_lContatoreAnnuale = 0;
				setTipoEsame.m_lAnno = 0;

				bSaved = setTipoEsame.UpdateRecordset("CAssociazioniICD9Dlg::OnTipoEsameUpdate");
				if (bSaved)
				{
					lAdded = setTipoEsame.GetLastAdd();

					if (lAdded > 0)
					{
						SalvaGruppiProcedure(lAdded);
						SalvaProcedure(lAdded);
						SalvaGruppiDiagnosi(lAdded);
						SalvaDiagnosi(lAdded);
					}
				}
			}

			setTipoEsame.CloseRecordset("CAssociazioniICD9Dlg::OnTipoEsameUpdate");
		}
	}
	else		
	{
		int nCurPos = m_ctrlLista.GetCurSel();
		if (nCurPos >= 0)
		{
			dwCode = m_ctrlLista.GetItemData(nCurPos);
			if (dwCode > 0)
			{
				CString sFilter;
				sFilter.Format("Contatore=%li", (long)dwCode);

				CTipoEsameSet setTipoEsame;
				setTipoEsame.SetOpenFilter(sFilter);
				if (setTipoEsame.OpenRecordset("CAssociazioniICD9Dlg::OnTipoEsameUpdate"))
				{
					if (setTipoEsame.IsEOF())
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TIPOESAMEDLG_ALREADY_DEL), MB_ICONINFORMATION);
					}
					else
					{
						if (setTipoEsame.EditRecordset("CAssociazioniICD9Dlg::OnTipoEsameUpdate"))
						{
							setTipoEsame.m_sDescrizione = m_sDescrizione;
							setTipoEsame.m_sSigla = m_sSigla;

							bSaved = setTipoEsame.UpdateRecordset("CAssociazioniICD9Dlg::OnTipoEsameUpdate");

							SalvaGruppiProcedure(dwCode);
							SalvaProcedure(dwCode);
							SalvaGruppiDiagnosi(dwCode);
							SalvaDiagnosi(dwCode);
						}
					}
					setTipoEsame.CloseRecordset("CAssociazioniICD9Dlg::OnTipoEsameUpdate");
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
		m_ctrlListGruppiProcedure.EnableWindow(FALSE);
		m_ctrlListProcedure.EnableWindow(FALSE);
		m_ctrlListGruppiDiagnosi.EnableWindow(FALSE);
		m_ctrlListDiagnosi.EnableWindow(FALSE);
		GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIGLA)->EnableWindow(FALSE);

		GetDlgItem(IDC_TIPOESAME_NUOVO)->EnableWindow(TRUE);
		GetDlgItem(IDC_TIPOESAME_MODIFY)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
		GetDlgItem(IDC_TIPOESAME_CANC)->EnableWindow(m_ctrlLista.GetCurSel() >= 0);
		GetDlgItem(IDC_TIPOESAME_UPDATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_TIPOESAME_REFRESH)->EnableWindow(FALSE);

		m_bModify = FALSE;
		m_bAddNew = FALSE;

		OnSelchangeLista();
	}
	RedrawWindow();
}

void CAssociazioniICD9Dlg::RiempiListaGruppiProcedure()
{
	CGruppiProcedureICD9Set setTemp;

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::RiempiListaGruppi") == TRUE)
	{
		int iTemp = 0;

		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListGruppiProcedure.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListGruppiProcedure.SetItemData(iTemp, (DWORD)setTemp.m_lID);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAssociazioniICD9Dlg::RiempiListaGruppi");
	}
}

void CAssociazioniICD9Dlg::RiempiListaGruppiDiagnosi()
{
	CGruppiDiagnosiICD9Set setTemp;

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::RiempiListaGruppiDiagnosi") == TRUE)
	{
		int iTemp = 0;

		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListGruppiDiagnosi.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListGruppiDiagnosi.SetItemData(iTemp, (DWORD)setTemp.m_lID);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAssociazioniICD9Dlg::RiempiListaGruppiDiagnosi");
	}
}

void CAssociazioniICD9Dlg::RiempiListaProcedure()
{
	CProcedureICD9Set setTemp;

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::RiempiListaProcedure") == TRUE)
	{
		int iTemp = 0;

		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListProcedure.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListProcedure.SetItemData(iTemp, (DWORD)setTemp.m_lID);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAssociazioniICD9Dlg::RiempiListaProcedure");
	}
}

void CAssociazioniICD9Dlg::RiempiListaDiagnosi()
{
	CDiagnosiICD9Set setTemp;

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::RiempiListaDiagnosi") == TRUE)
	{
		int iTemp = 0;

		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListDiagnosi.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListDiagnosi.SetItemData(iTemp, (DWORD)setTemp.m_lID);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAssociazioniICD9Dlg::RiempiListaDiagnosi");
	}
}

void CAssociazioniICD9Dlg::RiempiListaTipoEsame()
{
	m_ctrlLista.SetTabStops(100);
	
	CTipoEsameSet setTipoEsame;
	setTipoEsame.SetSortRecord("Descrizione");
	if (setTipoEsame.OpenRecordset("CAssociazioniICD9Dlg::RiempiListaTipoEsame"))
	{
		while (!setTipoEsame.IsEOF())
		{
			int posiz = m_ctrlLista.AddString(setTipoEsame.m_sDescrizione);

			if (posiz >= 0)
				m_ctrlLista.SetItemData(posiz, (DWORD)setTipoEsame.m_lContatore);

			setTipoEsame.MoveNext();
		}

		setTipoEsame.CloseRecordset("CAssociazioniICD9Dlg::RiempiListaTipoEsame");
	}
	
	OnSelchangeLista();
}

void CAssociazioniICD9Dlg::SalvaGruppiProcedure(long lContatoreEsame)
{
	int nCount = m_ctrlListGruppiProcedure.GetSelCount();
	CArray<int, int> listSel;
	listSel.SetSize(nCount);
	m_ctrlListGruppiProcedure.GetSelItems(nCount, listSel.GetData());
	
	int iTemp;
	CString strTemp;
	CTipiEsameGruppiProcedureICD9Set setTemp;

	//Cancello quelli presenti prima di rivalutarli
	strTemp.Format("IDTipoEsame=%li", lContatoreEsame);
	setTemp.SetBaseFilter(strTemp);
	if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::SalvaGruppiProcedure") == TRUE)
	{
		while(!setTemp.IsEOF())
		{
			setTemp.DeleteRecordset("CAssociazioniICD9Dlg::SalvaGruppiProcedure");
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAssociazioniICD9Dlg::SalvaGruppiProcedure");
	}
	
	// per ogni Prestazione in lista controllo se è selezionato o meno //
	for(iTemp = 0; iTemp < listSel.GetCount(); iTemp++)
	{
		int ind = listSel.GetAt(iTemp);
		if (m_ctrlListGruppiProcedure.GetSel(ind) > 0)
		{
			// l'elemento è selezionato e quindi se non lo trovo nel db lo aggiungo //

			strTemp.Format("IDGruppo=%li", (long)m_ctrlListGruppiProcedure.GetItemData(listSel.GetAt(iTemp)));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::SalvaGruppiProcedure") == TRUE)
			{
				if (setTemp.IsEOF() == TRUE)
				{
					// non c'è e quindi lo aggiungo //

					if (setTemp.AddNewRecordset("CAssociazioniICD9Dlg::SalvaGruppiProcedure") == TRUE)
					{
						setTemp.m_lIDTipoEsame = lContatoreEsame;
						setTemp.m_lIDGruppo = (long)m_ctrlListGruppiProcedure.GetItemData(listSel.GetAt(iTemp));

						setTemp.UpdateRecordset("CAssociazioniICD9Dlg::SalvaGruppiProcedure");
					}
				}

				setTemp.CloseRecordset("CAssociazioniICD9Dlg::SalvaGruppiProcedure");
			}
		}
		else
		{
			// l'elemento NON è selezionato e quindi se lo trovo nel db lo cancello //

			strTemp.Format("IDGruppo=%li", (long)m_ctrlListGruppiProcedure.GetItemData(listSel.GetAt(iTemp)));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::SalvaGruppiProcedure") == TRUE)
			{
				if (setTemp.IsEOF() == FALSE)
				{
					// c'è e quindi lo elimino //

					setTemp.DeleteRecordset("CAssociazioniICD9Dlg::SalvaGruppiProcedure");
				}
			}
		}
	}
}

void CAssociazioniICD9Dlg::SalvaGruppiDiagnosi(long lContatoreEsame)
{
	int nCount = m_ctrlListGruppiDiagnosi.GetSelCount();
	CArray<int, int> listSel;
	listSel.SetSize(nCount);
	m_ctrlListGruppiDiagnosi.GetSelItems(nCount, listSel.GetData());
	
	int iTemp;
	CString strTemp;
	CTipiEsameGruppiDiagnosiICD9Set setTemp;

	//Cancello quelli presenti prima di rivalutarli
	strTemp.Format("IDTipoEsame=%li", lContatoreEsame);
	setTemp.SetBaseFilter(strTemp);
	if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::SalvaGruppiDiagnosi") == TRUE)
	{
		while(!setTemp.IsEOF())
		{
			setTemp.DeleteRecordset("CAssociazioniICD9Dlg::SalvaGruppiDiagnosi");
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAssociazioniICD9Dlg::SalvaGruppiDiagnosi");
	}
	
	// per ogni Prestazione in lista controllo se è selezionato o meno //
	for(iTemp = 0; iTemp < listSel.GetCount(); iTemp++)
	{
		int ind = listSel.GetAt(iTemp);
		if (m_ctrlListGruppiDiagnosi.GetSel(ind) > 0)
		{
			// l'elemento è selezionato e quindi se non lo trovo nel db lo aggiungo //

			strTemp.Format("IDGruppo=%li", (long)m_ctrlListGruppiDiagnosi.GetItemData(listSel.GetAt(iTemp)));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::SalvaGruppiDiagnosi") == TRUE)
			{
				if (setTemp.IsEOF() == TRUE)
				{
					// non c'è e quindi lo aggiungo //

					if (setTemp.AddNewRecordset("CAssociazioniICD9Dlg::SalvaGruppiDiagnosi") == TRUE)
					{
						setTemp.m_lIDTipoEsame = lContatoreEsame;
						setTemp.m_lIDGruppo = (long)m_ctrlListGruppiDiagnosi.GetItemData(listSel.GetAt(iTemp));

						setTemp.UpdateRecordset("CAssociazioniICD9Dlg::SalvaGruppiDiagnosi");
					}
				}

				setTemp.CloseRecordset("CAssociazioniICD9Dlg::SalvaGruppiDiagnosi");
			}
		}
		else
		{
			// l'elemento NON è selezionato e quindi se lo trovo nel db lo cancello //

			strTemp.Format("IDGruppo=%li", (long)m_ctrlListGruppiDiagnosi.GetItemData(listSel.GetAt(iTemp)));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::SalvaGruppiDiagnosi") == TRUE)
			{
				if (setTemp.IsEOF() == FALSE)
				{
					// c'è e quindi lo elimino //

					setTemp.DeleteRecordset("CAssociazioniICD9Dlg::SalvaGruppiDiagnosi");
				}
			}
		}
	}
}

void CAssociazioniICD9Dlg::SalvaProcedure(long lContatoreEsame)
{
	int nCount = m_ctrlListProcedure.GetSelCount();
	CArray<int, int> listSel;
	listSel.SetSize(nCount);
	m_ctrlListProcedure.GetSelItems(nCount, listSel.GetData());
	
	int iTemp;
	CString strTemp;
	CTipiEsamiProcedureICD9Set setTemp;

	//Cancello quelli presenti prima di rivalutarli
	strTemp.Format("IDTipoEsame=%li", lContatoreEsame);
	setTemp.SetBaseFilter(strTemp);
	if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::SalvaProcedure") == TRUE)
	{
		while(!setTemp.IsEOF())
		{
			setTemp.DeleteRecordset("CAssociazioniICD9Dlg::SalvaProcedure");
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAssociazioniICD9Dlg::SalvaProcedure");
	}
	
	// per ogni Prestazione in lista controllo se è selezionato o meno //
	for(iTemp = 0; iTemp < listSel.GetCount(); iTemp++)
	{
		int ind = listSel.GetAt(iTemp);
		if (m_ctrlListProcedure.GetSel(ind) > 0)
		{
			// l'elemento è selezionato e quindi se non lo trovo nel db lo aggiungo //

			strTemp.Format("IDProcedura=%li", (long)m_ctrlListProcedure.GetItemData(listSel.GetAt(iTemp)));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::SalvaProcedure") == TRUE)
			{
				if (setTemp.IsEOF() == TRUE)
				{
					// non c'è e quindi lo aggiungo //

					if (setTemp.AddNewRecordset("CAssociazioniICD9Dlg::SalvaProcedure") == TRUE)
					{
						setTemp.m_lIDTipoEsame = lContatoreEsame;
						setTemp.m_lIDProcedura = (long)m_ctrlListProcedure.GetItemData(listSel.GetAt(iTemp));

						setTemp.UpdateRecordset("CAssociazioniICD9Dlg::SalvaProcedure");
					}
				}

				setTemp.CloseRecordset("CAssociazioniICD9Dlg::SalvaProcedure");
			}
		}
		else
		{
			// l'elemento NON è selezionato e quindi se lo trovo nel db lo cancello //

			strTemp.Format("IDProcedura=%li", (long)m_ctrlListProcedure.GetItemData(listSel.GetAt(iTemp)));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::SalvaProcedure") == TRUE)
			{
				if (setTemp.IsEOF() == FALSE)
				{
					// c'è e quindi lo elimino //

					setTemp.DeleteRecordset("CAssociazioniICD9Dlg::SalvaProcedure");
				}
			}
		}
	}
}

void CAssociazioniICD9Dlg::SalvaDiagnosi(long lContatoreEsame)
{
	int nCount = m_ctrlListDiagnosi.GetSelCount();
	CArray<int, int> listSel;
	listSel.SetSize(nCount);
	m_ctrlListDiagnosi.GetSelItems(nCount, listSel.GetData());
	
	int iTemp;
	CString strTemp;
	CTipiEsamiDiagnosiICD9Set setTemp;

	//Cancello quelli presenti prima di rivalutarli
	strTemp.Format("IDTipoEsame=%li", lContatoreEsame);
	setTemp.SetBaseFilter(strTemp);
	if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::SalvaDiagnosi") == TRUE)
	{
		while(!setTemp.IsEOF())
		{
			setTemp.DeleteRecordset("CAssociazioniICD9Dlg::SalvaDiagnosi");
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAssociazioniICD9Dlg::SalvaDiagnosi");
	}
	
	// per ogni Prestazione in lista controllo se è selezionato o meno //
	for(iTemp = 0; iTemp < listSel.GetCount(); iTemp++)
	{
		int ind = listSel.GetAt(iTemp);
		if (m_ctrlListDiagnosi.GetSel(ind) > 0)
		{
			// l'elemento è selezionato e quindi se non lo trovo nel db lo aggiungo //

			strTemp.Format("IDDiagnosi=%li", (long)m_ctrlListDiagnosi.GetItemData(listSel.GetAt(iTemp)));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::SalvaDiagnosi") == TRUE)
			{
				if (setTemp.IsEOF() == TRUE)
				{
					// non c'è e quindi lo aggiungo //

					if (setTemp.AddNewRecordset("CAssociazioniICD9Dlg::SalvaDiagnosi") == TRUE)
					{
						setTemp.m_lIDTipoEsame = lContatoreEsame;
						setTemp.m_lIDDiagnosi = (long)m_ctrlListDiagnosi.GetItemData(listSel.GetAt(iTemp));

						setTemp.UpdateRecordset("CAssociazioniICD9Dlg::SalvaDiagnosi");
					}
				}

				setTemp.CloseRecordset("CAssociazioniICD9Dlg::SalvaProcedure");
			}
		}
		else
		{
			// l'elemento NON è selezionato e quindi se lo trovo nel db lo cancello //

			strTemp.Format("IDDiagnosi=%li", (long)m_ctrlListProcedure.GetItemData(listSel.GetAt(iTemp)));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CAssociazioniICD9Dlg::SalvaDiagnosi") == TRUE)
			{
				if (setTemp.IsEOF() == FALSE)
				{
					// c'è e quindi lo elimino //

					setTemp.DeleteRecordset("CAssociazioniICD9Dlg::SalvaDiagnosi");
				}
			}
		}
	}
}

void CAssociazioniICD9Dlg::SelezionaGruppiProcedure(long lContatoreEsame)
{
	CString strTemp;
	CTipiEsameGruppiProcedureICD9Set setJoin;
	CGruppiProcedureICD9Set setGruppi;

	// nascondo il controllo //
	m_ctrlListGruppiProcedure.ShowWindow(SW_HIDE);

	// Deseleziono tutti gli elementi //
	m_ctrlListGruppiProcedure.SelItemRange(FALSE, 0, m_ctrlListGruppiProcedure.GetCount() - 1);

	// Cerco nella tabella 'ETipiEsamiPrestazioni' tutti i record che hanno il 'TipoEsame' correntemente selezionato //
	strTemp.Format("IDTipoEsame=%li", lContatoreEsame);
	setJoin.SetOpenFilter(strTemp);

	if (setJoin.OpenRecordset("CAssociazioniICD9Dlg::SelezionaGruppiProcedure") == TRUE)
	{
		while(setJoin.IsEOF() == FALSE)
		{
			// Prendo dalla tabella 'ECodificaRegionaleEx' la descrizione per esteso della prestazione trovata nella tabella 'ETipiEsamiPrestazioni' //
			strTemp.Format("ID=%li", setJoin.m_lIDGruppo);
			setGruppi.SetOpenFilter(strTemp);

			if (setGruppi.OpenRecordset("CAssociazioniICD9Dlg::SelezionaGruppiProcedure") == TRUE)
			{
				if (setGruppi.IsEOF() == FALSE)
				{
					// Se trovo l'organo nella lista (e dovrei trovarlo, se sono arrivato qui) lo seleziono //
					int iFind = m_ctrlListGruppiProcedure.FindStringExact(-1, setGruppi.m_sDescrizione);

					if (iFind != LB_ERR)
						m_ctrlListGruppiProcedure.SetSel(iFind, TRUE);
				}

				setGruppi.CloseRecordset("CAssociazioniICD9Dlg::SelezionaGruppiProcedure");
			}

			setJoin.MoveNext();
		}

		setJoin.CloseRecordset("CAssociazioniICD9Dlg::SelezionaDiagnosi");
	}

	// mi riposiziono all'inizio //
	m_ctrlListGruppiProcedure.SendMessage(WM_VSCROLL, SB_TOP, NULL);

	// mostro il controllo //
	m_ctrlListGruppiProcedure.ShowWindow(SW_SHOW);
}

void CAssociazioniICD9Dlg::SelezionaGruppiDiagnosi(long lContatoreEsame)
{
	CString strTemp;
	CTipiEsameGruppiDiagnosiICD9Set setJoin;
	CGruppiDiagnosiICD9Set setGruppi;

	// nascondo il controllo //
	m_ctrlListGruppiDiagnosi.ShowWindow(SW_HIDE);

	// Deseleziono tutti gli elementi //
	m_ctrlListGruppiDiagnosi.SelItemRange(FALSE, 0, m_ctrlListGruppiDiagnosi.GetCount() - 1);

	// Cerco nella tabella 'ETipiEsamiPrestazioni' tutti i record che hanno il 'TipoEsame' correntemente selezionato //
	strTemp.Format("IDTipoEsame=%li", lContatoreEsame);
	setJoin.SetOpenFilter(strTemp);

	if (setJoin.OpenRecordset("CAssociazioniICD9Dlg::SelezionaDiagnosi") == TRUE)
	{
		while(setJoin.IsEOF() == FALSE)
		{
			// Prendo dalla tabella 'ECodificaRegionaleEx' la descrizione per esteso della prestazione trovata nella tabella 'ETipiEsamiPrestazioni' //
			strTemp.Format("ID=%li", setJoin.m_lIDGruppo);
			setGruppi.SetOpenFilter(strTemp);

			if (setGruppi.OpenRecordset("CAssociazioniICD9Dlg::SelezionaDiagnosi") == TRUE)
			{
				if (setGruppi.IsEOF() == FALSE)
				{
					// Se trovo l'organo nella lista (e dovrei trovarlo, se sono arrivato qui) lo seleziono //
					int iFind = m_ctrlListGruppiDiagnosi.FindStringExact(-1, setGruppi.m_sDescrizione);

					if (iFind != LB_ERR)
						m_ctrlListGruppiDiagnosi.SetSel(iFind, TRUE);
				}

				setGruppi.CloseRecordset("CAssociazioniICD9Dlg::SelezionaDiagnosi");
			}

			setJoin.MoveNext();
		}

		setJoin.CloseRecordset("CAssociazioniICD9Dlg::SelezionaDiagnosi");
	}

	// mi riposiziono all'inizio //
	m_ctrlListGruppiDiagnosi.SendMessage(WM_VSCROLL, SB_TOP, NULL);

	// mostro il controllo //
	m_ctrlListGruppiDiagnosi.ShowWindow(SW_SHOW);
}

void CAssociazioniICD9Dlg::SelezionaProcedure(long lContatoreEsame)
{
	CString strTemp;
	CTipiEsamiProcedureICD9Set setJoin;
	CProcedureICD9Set setProcedure;

	// nascondo il controllo //
	m_ctrlListProcedure.ShowWindow(SW_HIDE);

	// Deseleziono tutti gli elementi //
	m_ctrlListProcedure.SelItemRange(FALSE, 0, m_ctrlListProcedure.GetCount() - 1);

	// Cerco nella tabella 'ETipiEsamiPrestazioni' tutti i record che hanno il 'TipoEsame' correntemente selezionato //
	strTemp.Format("IDTipoEsame=%li", lContatoreEsame);
	setJoin.SetOpenFilter(strTemp);

	if (setJoin.OpenRecordset("CAssociazioniICD9Dlg::SelezionaProcedure") == TRUE)
	{
		while(setJoin.IsEOF() == FALSE)
		{
			// Prendo dalla tabella 'ECodificaRegionaleEx' la descrizione per esteso della prestazione trovata nella tabella 'ETipiEsamiPrestazioni' //
			strTemp.Format("ID=%li", setJoin.m_lIDProcedura);
			setProcedure.SetOpenFilter(strTemp);

			if (setProcedure.OpenRecordset("CAssociazioniICD9Dlg::SelezionaProcedure") == TRUE)
			{
				if (setProcedure.IsEOF() == FALSE)
				{
					// Se trovo l'organo nella lista (e dovrei trovarlo, se sono arrivato qui) lo seleziono //
					int iFind = m_ctrlListProcedure.FindStringExact(-1, setProcedure.m_sDescrizione);

					if (iFind != LB_ERR)
						m_ctrlListProcedure.SetSel(iFind, TRUE);
				}

				setProcedure.CloseRecordset("CAssociazioniICD9Dlg::SelezionaProcedure");
			}

			setJoin.MoveNext();
		}

		setJoin.CloseRecordset("CAssociazioniICD9Dlg::SelezionaProcedure");
	}

	// mi riposiziono all'inizio //
	m_ctrlListProcedure.SendMessage(WM_VSCROLL, SB_TOP, NULL);

	// mostro il controllo //
	m_ctrlListProcedure.ShowWindow(SW_SHOW);
}

void CAssociazioniICD9Dlg::SelezionaDiagnosi(long lContatoreEsame)
{
	CString strTemp;
	CTipiEsamiDiagnosiICD9Set setJoin;
	CDiagnosiICD9Set setDiagnosi;

	// nascondo il controllo //
	m_ctrlListDiagnosi.ShowWindow(SW_HIDE);

	// Deseleziono tutti gli elementi //
	m_ctrlListDiagnosi.SelItemRange(FALSE, 0, m_ctrlListDiagnosi.GetCount() - 1);

	// Cerco nella tabella 'ETipiEsamiPrestazioni' tutti i record che hanno il 'TipoEsame' correntemente selezionato //
	strTemp.Format("IDTipoEsame=%li", lContatoreEsame);
	setJoin.SetOpenFilter(strTemp);

	if (setJoin.OpenRecordset("CAssociazioniICD9Dlg::SelezionaDiagnosi") == TRUE)
	{
		while(setJoin.IsEOF() == FALSE)
		{
			// Prendo dalla tabella 'ECodificaRegionaleEx' la descrizione per esteso della prestazione trovata nella tabella 'ETipiEsamiPrestazioni' //
			strTemp.Format("ID=%li", setJoin.m_lIDDiagnosi);
			setDiagnosi.SetOpenFilter(strTemp);

			if (setDiagnosi.OpenRecordset("CAssociazioniICD9Dlg::SelezionaDiagnosi") == TRUE)
			{
				if (setDiagnosi.IsEOF() == FALSE)
				{
					// Se trovo l'organo nella lista (e dovrei trovarlo, se sono arrivato qui) lo seleziono //
					int iFind = m_ctrlListDiagnosi.FindStringExact(-1, setDiagnosi.m_sDescrizione);

					if (iFind != LB_ERR)
						m_ctrlListDiagnosi.SetSel(iFind, TRUE);
				}

				setDiagnosi.CloseRecordset("CAssociazioniICD9Dlg::SelezionaDiagnosi");
			}

			setJoin.MoveNext();
		}

		setJoin.CloseRecordset("CAssociazioniICD9Dlg::SelezionaDiagnosi");
	}

	// mi riposiziono all'inizio //
	m_ctrlListDiagnosi.SendMessage(WM_VSCROLL, SB_TOP, NULL);

	// mostro il controllo //
	m_ctrlListDiagnosi.ShowWindow(SW_SHOW);
}


void CAssociazioniICD9Dlg::OnLbnSelchangeGruppiDiagnosi()
{
	int sel = m_ctrlListGruppiDiagnosi.GetCurSel();
	if (m_ctrlListGruppiDiagnosi.GetSel(sel) > 0)
		SelezionaDiagnosiDaGruppo(m_ctrlListGruppiDiagnosi.GetItemData(sel));
}

void CAssociazioniICD9Dlg::SelezionaDiagnosiDaGruppo(long lIdGruppo)
{
	CGruppiDiagnosiICD9DiagnosiICD9Set tempSet;
	CString filter;
	filter.Format("IDGruppo=%li and eliminato=0", lIdGruppo);
	tempSet.SetOpenFilter(filter);
	if (tempSet.OpenRecordset("CAssociazioniICD9Dlg::SelezionaDiagnosiDaGruppo"))
	{
		while(!tempSet.IsEOF())
		{
			SelectDiagnosi(tempSet.m_lIDDiagnosi);
			tempSet.MoveNext();
		}
		tempSet.CloseRecordset("CAssociazioniICD9Dlg::SelezionaDiagnosiDaGruppo");
	}
}

void CAssociazioniICD9Dlg::SelectDiagnosi(long lIdDiagnosi)
{
	for(int i=0; i<m_ctrlListDiagnosi.GetCount(); i++)
	{
		if (m_ctrlListDiagnosi.GetItemData(i) == lIdDiagnosi)
		{
			m_ctrlListDiagnosi.SetSel(i);
			return;
		}
	}
}

void CAssociazioniICD9Dlg::OnLbnSelchangeGruppiProcedure()
{
	int sel = m_ctrlListGruppiProcedure.GetCurSel();
	if (m_ctrlListGruppiProcedure.GetSel(sel) > 0)
		SelezionaProceduraDaGruppo(m_ctrlListGruppiProcedure.GetItemData(sel));
}

void CAssociazioniICD9Dlg::SelezionaProceduraDaGruppo(long lIdGruppo)
{
	CGruppiProcedureICD9ProcedureICD9Set tempSet;
	CString filter;
	filter.Format("IDGruppo=%li and eliminato=0", lIdGruppo);
	tempSet.SetOpenFilter(filter);
	if (tempSet.OpenRecordset("CAssociazioniICD9Dlg::OnLbnSelchangeGruppiProcedure"))
	{
		while(!tempSet.IsEOF())
		{
			SelectProcedura(tempSet.m_lIDProcedura);
			tempSet.MoveNext();
		}
		tempSet.CloseRecordset("CAssociazioniICD9Dlg::OnLbnSelchangeGruppiProcedure");
	}
}

void CAssociazioniICD9Dlg::SelectProcedura(long lIdProcedura)
{
	for(int i=0; i<m_ctrlListProcedure.GetCount(); i++)
	{
		if (m_ctrlListProcedure.GetItemData(i) == lIdProcedura)
		{
			m_ctrlListProcedure.SetSel(i);
			return;
		}
	}
}