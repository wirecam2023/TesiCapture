#include "stdafx.h"
#include "Endox.h"
#include "GruppiPrestazioniModDlg.h"

#include "Endox.h"
#include "EsamiView.h"
#include "CodificaRegionaleExSet.h"
#include "GruppiPrestazioniSet.h"
#include "GruppiPrestazioniPrestazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiPrestazioniModDlg, CDialog)

CGruppiPrestazioniModDlg::CGruppiPrestazioniModDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CGruppiPrestazioniModDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_sDescrizione = "";
	m_bAddNew = FALSE;
	m_bModify = FALSE;
}

CGruppiPrestazioniModDlg::~CGruppiPrestazioniModDlg()
{
}

BEGIN_MESSAGE_MAP(CGruppiPrestazioniModDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_NEW, OnBnClickedNew)
	ON_BN_CLICKED(IDC_EDT, OnBnClickedEdt)
	ON_BN_CLICKED(IDC_DEL, OnBnClickedDel)
	ON_BN_CLICKED(IDC_SAVE, OnBnClickedSave)
	ON_BN_CLICKED(IDC_UNDO, OnBnClickedUndo)

	ON_LBN_SELCHANGE(IDC_LISTA_GRUPPI, OnLbnSelchangeListaGruppi)
END_MESSAGE_MAP()

void CGruppiPrestazioniModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LISTA_GRUPPI, m_ctrlListaGruppi);
	DDX_Control(pDX, IDC_LISTA_PRESTAZIONI, m_ctrlListaPrestazioni);


	DDX_Control(pDX, IDC_STATIC_GRUPPI,				m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_PRESTAZIONI,		m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_GRUPPOPRESTAZIONI,	m_ctrlStatic3);
	DDX_Control(pDX, IDC_NEW,   m_ctrlButtonNew);
	DDX_Control(pDX, IDC_EDT,	m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_DEL,   m_ctrlButtonDel);
	DDX_Control(pDX, IDC_SAVE,  m_ctrlButtonSave);
	DDX_Control(pDX, IDC_UNDO,	m_ctrlButtonUndo);
	DDX_Control(pDX, IDCANCEL,  m_ctrlButtonCancel);
	
	DDX_Text(pDX, IDC_DESCRIZIONE, m_sDescrizione);
}

HBRUSH CGruppiPrestazioniModDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_GRUPPI:
			pDC->SetTextColor(theApp.m_color[0]);
			break;
		case IDC_LISTA_GRUPPI:
			if (m_ctrlListaGruppi.IsWindowEnabled())
				pDC->SetTextColor(theApp.m_color[1]);
			else
				pDC->SetTextColor(RGB(192,192,192));
			break;
		case IDC_STATIC_GRUPPOPRESTAZIONI:
		case IDC_DESCRIZIONE:
			pDC->SetTextColor(theApp.m_color[0]);
			break;

		case IDC_STATIC_PRESTAZIONI:
			pDC->SetTextColor(theApp.m_color[1]);
			break;
		case IDC_LISTA_PRESTAZIONI:
			if (m_ctrlListaPrestazioni.IsWindowEnabled())
				pDC->SetTextColor(theApp.m_color[1]);
			else
				pDC->SetTextColor(RGB(192,192,192));
			break;
	}

	return hBrush;
}

BOOL CGruppiPrestazioniModDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_GRUPPI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_PRESTAZIONI)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_NEW)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_DEL)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);

	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);

	m_ctrlListaGruppi.EnableWindow(TRUE);
	m_ctrlListaPrestazioni.EnableWindow(FALSE);

	RiempiListaGruppi();
	RiempiListaPrestazioni();
	
	theApp.LocalizeDialog(this, CGruppiPrestazioniModDlg::IDD, "GruppiPrestazioniModDlg");

	RedrawWindow();

	return TRUE;
}

void CGruppiPrestazioniModDlg::OnBnClickedNew()
{
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	m_ctrlListaGruppi.EnableWindow(FALSE);
	m_ctrlListaPrestazioni.EnableWindow(TRUE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(TRUE);

	GetDlgItem(IDC_NEW)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_UNDO)->EnableWindow(TRUE);

	// Deseleziono tutti gli elementi dalle liste delle prestazioni //
	m_ctrlListaPrestazioni.SelItemRange(FALSE, 0, m_ctrlListaPrestazioni.GetCount() - 1);

	m_sDescrizione = "";

	m_bAddNew = TRUE;

	UpdateData(FALSE);
	RedrawWindow();
}

void CGruppiPrestazioniModDlg::OnBnClickedEdt()
{
	int nSelect = m_ctrlListaGruppi.GetCurSel();
		
	if (nSelect >= 0)
	{
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

		m_ctrlListaGruppi.EnableWindow(FALSE);
		m_ctrlListaPrestazioni.EnableWindow(TRUE);
		GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(TRUE);

		GetDlgItem(IDC_NEW)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT)->EnableWindow(FALSE);
		GetDlgItem(IDC_DEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_UNDO)->EnableWindow(TRUE);

		m_bModify = TRUE;

		UpdateData(FALSE);
		RedrawWindow();
	}			
}

void CGruppiPrestazioniModDlg::OnBnClickedDel()
{
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlListaGruppi.EnableWindow(TRUE);
	m_ctrlListaPrestazioni.EnableWindow(FALSE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);

	GetDlgItem(IDC_NEW)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_DEL)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DELETE_GRUPPOPRESTAZIONI), MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		return;

	/*
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_GRUPPIPRESTAZIONI_DELETE_CONFIRM_2), MB_YESNO | MB_ICONSTOP) == IDYES)
		return;
	*/

	int posiz = m_ctrlListaGruppi.GetCurSel();
	if (posiz >= 0)
	{
		long lID = (long)m_ctrlListaGruppi.GetItemData(posiz);
	
		if (lID >= 0)
		{
			CString strFilter;
			strFilter.Format("ID=%li", (long)lID);

			CGruppiPrestazioniSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CGruppiPrestazioniModDlg::OnBnClickedDel"))
			{
				if (!setTemp.IsEOF())
					setTemp.DeleteRecordset("CGruppiPrestazioniModDlg::OnBnClickedDel");
		
				setTemp.CloseRecordset("CGruppiPrestazioniModDlg::OnBnClickedDel");
				RiempiListaGruppi();
			}
		}
	}
	
	UpdateData(FALSE);
	RedrawWindow();
}

void CGruppiPrestazioniModDlg::OnBnClickedSave()
{
	UpdateData(TRUE);

	if (m_sDescrizione.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TIPOESAMEDLG_EMPTY_DESC), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		CGruppiPrestazioniSet setTemp;

        if (setTemp.OpenRecordset("CGruppiPrestazioniModDlg::OnBnClickedSave"))
		{
			if (setTemp.AddNewRecordset("CGruppiPrestazioniModDlg::OnBnClickedSave"))
			{
				setTemp.m_sDescrizione = m_sDescrizione;

				if (setTemp.UpdateRecordset("CGruppiPrestazioniModDlg::OnBnClickedSave"))
					SalvaPrestazioni(setTemp.GetLastAdd());

				setTemp.CloseRecordset("CGruppiPrestazioniModDlg::OnBnClickedSave");
			}

			setTemp.CloseRecordset("CGruppiPrestazioniModDlg::OnBnClickedSave");
		}

		RiempiListaGruppi();
		OnLbnSelchangeListaGruppi();
	}
	else		
	{
		if (m_bModify)
		{
			int nIndex = m_ctrlListaGruppi.GetCurSel();

			if (nIndex >= 0)
			{
				CString strFilter;
				strFilter.Format("ID=%li", (long)m_ctrlListaGruppi.GetItemData(nIndex));

				CGruppiPrestazioniSet setTemp;
				setTemp.SetOpenFilter(strFilter);
		        
				if (setTemp.OpenRecordset("CGruppiPrestazioniModDlg::OnBnClickedSave"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CGruppiPrestazioniModDlg::OnBnClickedSave"))
						{
							setTemp.m_sDescrizione = m_sDescrizione;

							if (setTemp.UpdateRecordset("CGruppiPrestazioniModDlg::OnBnClickedSave"))
								SalvaPrestazioni(setTemp.m_lID);
						}
					}

					setTemp.CloseRecordset("CGruppiPrestazioniModDlg::OnBnClickedSave");
				}
			}
		}
	}

	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlListaGruppi.EnableWindow(TRUE);
	m_ctrlListaPrestazioni.EnableWindow(FALSE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);

	GetDlgItem(IDC_NEW)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_DEL)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);

	m_bModify = FALSE;
	m_bAddNew = FALSE;

	RedrawWindow();
}

void CGruppiPrestazioniModDlg::OnBnClickedUndo()
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlListaGruppi.EnableWindow(TRUE);
	m_ctrlListaPrestazioni.EnableWindow(FALSE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);

	GetDlgItem(IDC_NEW)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_DEL)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);

	RiempiListaGruppi();
	OnLbnSelchangeListaGruppi();
	RedrawWindow();
}

void CGruppiPrestazioniModDlg::OnLbnSelchangeListaGruppi()
{
	int nCurPos = m_ctrlListaGruppi.GetCurSel();

	GetDlgItem(IDC_EDT)->EnableWindow(nCurPos >= 0);
	GetDlgItem(IDC_DEL)->EnableWindow(nCurPos >= 0);

	if (nCurPos >= 0)
	{
		long lID = (long)m_ctrlListaGruppi.GetItemData(nCurPos);

		if (lID >= 0)
		{
			CString strFilter;
			strFilter.Format("ID=%li", lID);

			CGruppiPrestazioniSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CGruppiPrestazioniModDlg::OnLbnSelchangeListaGruppi"))
			{
				if (!setTemp.IsEOF())
				{
					m_sDescrizione = setTemp.m_sDescrizione;

					SelezionaPrestazioni(setTemp.m_lID);
				}

				setTemp.CloseRecordset("CGruppiPrestazioniModDlg::OnLbnSelchangeListaGruppi");
			}

			UpdateData(FALSE);
		}
	}
	else
	{
		m_ctrlListaPrestazioni.SelItemRange(FALSE, 0, m_ctrlListaPrestazioni.GetCount() - 1);
	}
}

void CGruppiPrestazioniModDlg::RiempiListaGruppi()
{
	CGruppiPrestazioniSet setTemp;

	m_ctrlListaGruppi.ResetContent();

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CGruppiPrestazioniModDlg::RiempiListaGruppi") == TRUE)
	{
		int iTemp = 0;

		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListaGruppi.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListaGruppi.SetItemData(iTemp, (DWORD)setTemp.m_lID);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGruppiPrestazioniModDlg::RiempiListaGruppi");
	}

	m_ctrlListaGruppi.SetCurSel(-1);
}

void CGruppiPrestazioniModDlg::RiempiListaPrestazioni()
{
	CCodificaRegionaleExSet setTemp;

	m_ctrlListaPrestazioni.ResetContent();

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CGruppiPrestazioniModDlg::RiempiListaPrestazioni") == TRUE)
	{
		int iTemp = 0;

		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListaPrestazioni.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListaPrestazioni.SetItemData(iTemp, (DWORD)setTemp.m_lContatore);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGruppiPrestazioniModDlg::RiempiListaPrestazioni");
	}
}

void CGruppiPrestazioniModDlg::SalvaPrestazioni(long lContatoreEsame)
{
	int iTemp;
	CString strTemp;
	CGruppiPrestazioniPrestazioniSet setTemp;

	strTemp.Format("IDGruppo=%li", lContatoreEsame);
	setTemp.SetBaseFilter(strTemp);
	
	// per ogni Prestazione in lista controllo se è selezionato o meno //
	for(iTemp = 0; iTemp < m_ctrlListaPrestazioni.GetCount(); iTemp++)
	{
		if (m_ctrlListaPrestazioni.GetSel(iTemp) > 0)
		{
			// l'elemento è selezionato e quindi se non lo trovo nel db lo aggiungo //

			strTemp.Format("IDPrestazione=%li", (long)m_ctrlListaPrestazioni.GetItemData(iTemp));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CGruppiPrestazioniModDlg::SalvaPrestazioni") == TRUE)
			{
				if (setTemp.IsEOF() == TRUE)
				{
					// non c'è e quindi lo aggiungo //

					if (setTemp.AddNewRecordset("CGruppiPrestazioniModDlg::SalvaPrestazioni") == TRUE)
					{
						setTemp.m_lIDGruppo = lContatoreEsame;
						setTemp.m_lIDPrestazione = (long)m_ctrlListaPrestazioni.GetItemData(iTemp);

						setTemp.UpdateRecordset("CGruppiPrestazioniModDlg::SalvaPrestazioni");
					}
				}

				setTemp.CloseRecordset("CGruppiPrestazioniModDlg::SalvaPrestazioni");
			}
		}
		else
		{
			// l'elemento NON è selezionato e quindi se lo trovo nel db lo cancello //

			strTemp.Format("IDPrestazione=%li", (long)m_ctrlListaPrestazioni.GetItemData(iTemp));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CGruppiPrestazioniModDlg::SalvaPrestazioni") == TRUE)
			{
				if (setTemp.IsEOF() == FALSE)
				{
					// c'è e quindi lo elimino //

					setTemp.DeleteRecordset("CGruppiPrestazioniModDlg::SalvaPrestazioni");
				}
			}
		}
	}
}

void CGruppiPrestazioniModDlg::SelezionaPrestazioni(long lContatoreEsame)
{
	CString strTemp;
	CGruppiPrestazioniPrestazioniSet setJoin;
	CCodificaRegionaleExSet setPrestazione;

	// Deseleziono tutti gli elementi //
	m_ctrlListaPrestazioni.SelItemRange(FALSE, 0, m_ctrlListaPrestazioni.GetCount() - 1);

	// Cerco nella tabella 'GruppiPrestazioniPrestazioni' tutti i record che hanno il 'IDGruppo' correntemente selezionato //
	strTemp.Format("IDGruppo=%li", lContatoreEsame);
	setJoin.SetOpenFilter(strTemp);

	if (setJoin.OpenRecordset("CGruppiPrestazioniModDlg::SelezionaPrestazioni") == TRUE)
	{
		while(setJoin.IsEOF() == FALSE)
		{
			// Prendo dalla tabella 'ECodificaRegionaleEx' la descrizione per esteso della prestazione trovata nella tabella 'GruppiPrestazioniPrestazioni' //
			strTemp.Format("Contatore=%li", setJoin.m_lIDPrestazione);
			setPrestazione.SetOpenFilter(strTemp);

			if (setPrestazione.OpenRecordset("CGruppiPrestazioniModDlg::SelezionaPrestazioni") == TRUE)
			{
				if (setPrestazione.IsEOF() == FALSE)
				{
					// Se trovo l'organo nella lista (e dovrei trovarlo, se sono arrivato qui) lo seleziono //
					int iFind = m_ctrlListaPrestazioni.FindStringExact(-1, setPrestazione.m_sDescrizione);

					if (iFind != LB_ERR)
						m_ctrlListaPrestazioni.SetSel(iFind, TRUE);
				}

				setPrestazione.CloseRecordset("CGruppiPrestazioniModDlg::SelezionaPrestazioni");
			}

			setJoin.MoveNext();
		}

		setJoin.CloseRecordset("CGruppiPrestazioniModDlg::SelezionaPrestazioni");
	}
}