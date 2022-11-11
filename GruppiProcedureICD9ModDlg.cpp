#include "stdafx.h"
#include "Endox.h"
#include "GruppiProcedureICD9ModDlg.h"

#include "Endox.h"
#include "EsamiView.h"
#include "ProcedureICD9Set.h"
#include "GruppiProcedureICD9Set.h"
#include "GruppiProcedureICD9ProcedureICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiProcedureICD9ModDlg, CDialog)

CGruppiProcedureICD9ModDlg::CGruppiProcedureICD9ModDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CGruppiProcedureICD9ModDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_sDescrizione = "";
	m_bAddNew = FALSE;
	m_bModify = FALSE;
}

CGruppiProcedureICD9ModDlg::~CGruppiProcedureICD9ModDlg()
{
}

BEGIN_MESSAGE_MAP(CGruppiProcedureICD9ModDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_NEW, OnBnClickedNew)
	ON_BN_CLICKED(IDC_EDT, OnBnClickedEdt)
	ON_BN_CLICKED(IDC_DEL, OnBnClickedDel)
	ON_BN_CLICKED(IDC_SAVE, OnBnClickedSave)
	ON_BN_CLICKED(IDC_UNDO, OnBnClickedUndo)

	ON_LBN_SELCHANGE(IDC_LISTA_GRUPPI, OnLbnSelchangeListaGruppi)
END_MESSAGE_MAP()

void CGruppiProcedureICD9ModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LISTA_GRUPPI, m_ctrlListaGruppi);
	DDX_Control(pDX, IDC_LISTA_PROCEDURE, m_ctrlListaProcedure);


	DDX_Control(pDX, IDC_STATIC_GRUPPI, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_PROCEDURE, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_GRUPPOPROCEDURE, m_ctrlStatic3);

	DDX_Control(pDX, IDC_NEW,   m_ctrlButtonNew);
	DDX_Control(pDX, IDC_EDT,	m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_DEL,   m_ctrlButtonDel);
	DDX_Control(pDX, IDC_SAVE,  m_ctrlButtonSave);
	DDX_Control(pDX, IDC_UNDO,	m_ctrlButtonUndo);
	DDX_Control(pDX, IDCANCEL,  m_ctrlButtonCancel);
	
	DDX_Text(pDX, IDC_DESCRIZIONE, m_sDescrizione);
}

HBRUSH CGruppiProcedureICD9ModDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		case IDC_STATIC_GRUPPOPROCEDURE:
		case IDC_DESCRIZIONE:
			pDC->SetTextColor(theApp.m_color[0]);
			break;

		case IDC_STATIC_PRESTAZIONI:
			pDC->SetTextColor(theApp.m_color[1]);
			break;
		case IDC_LISTA_PROCEDURE:
			if (m_ctrlListaProcedure.IsWindowEnabled())
				pDC->SetTextColor(theApp.m_color[1]);
			else
				pDC->SetTextColor(RGB(192,192,192));
			break;
	}

	return hBrush;
}

BOOL CGruppiProcedureICD9ModDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_GRUPPI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_PROCEDURE)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_NEW)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_DEL)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);

	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);

	m_ctrlListaGruppi.EnableWindow(TRUE);
	m_ctrlListaProcedure.EnableWindow(FALSE);

	RiempiListaGruppi();
	RiempiListaProcedure();
	
	RedrawWindow();

	theApp.LocalizeDialog(this, CGruppiProcedureICD9ModDlg::IDD, "GruppiProcedureICD9ModDlg");
	return TRUE;
}

void CGruppiProcedureICD9ModDlg::OnBnClickedNew()
{
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	m_ctrlListaGruppi.EnableWindow(FALSE);
	m_ctrlListaProcedure.EnableWindow(TRUE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(TRUE);

	GetDlgItem(IDC_NEW)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_UNDO)->EnableWindow(TRUE);

	// Deseleziono tutti gli elementi dalle liste delle prestazioni //
	m_ctrlListaProcedure.SelItemRange(FALSE, 0, m_ctrlListaProcedure.GetCount() - 1);

	m_sDescrizione = "";

	m_bAddNew = TRUE;

	UpdateData(FALSE);
	RedrawWindow();
}

void CGruppiProcedureICD9ModDlg::OnBnClickedEdt()
{
	int nSelect = m_ctrlListaGruppi.GetCurSel();
		
	if (nSelect >= 0)
	{
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

		m_ctrlListaGruppi.EnableWindow(FALSE);
		m_ctrlListaProcedure.EnableWindow(TRUE);
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

void CGruppiProcedureICD9ModDlg::OnBnClickedDel()
{
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlListaGruppi.EnableWindow(TRUE);
	m_ctrlListaProcedure.EnableWindow(FALSE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);

	GetDlgItem(IDC_NEW)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_DEL)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DELETE_GRUPPOPROCEDURE), MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
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

			CGruppiProcedureICD9Set setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedDel"))
			{
				if (!setTemp.IsEOF())
					setTemp.DeleteRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedDel");
		
				setTemp.CloseRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedDel");
				RiempiListaGruppi();
			}
		}
	}
	
	UpdateData(FALSE);
	RedrawWindow();
}

void CGruppiProcedureICD9ModDlg::OnBnClickedSave()
{
	UpdateData(TRUE);

	if (m_sDescrizione.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TIPOESAMEDLG_EMPTY_DESC), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		CGruppiProcedureICD9Set setTemp;

        if (setTemp.OpenRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedSave"))
		{
			if (setTemp.AddNewRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedSave"))
			{
				setTemp.m_sDescrizione = m_sDescrizione;

				setTemp.UpdateRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedSave");
				setTemp.CloseRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedSave");

				setTemp.SetSortRecord("ID");
				if (setTemp.OpenRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedSave"))
				{
					setTemp.MoveLast();

					SalvaProcedureICD9(setTemp.m_lID);

					setTemp.CloseRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedSave");
				}
			}

			setTemp.CloseRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedSave");
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

				CGruppiProcedureICD9Set setTemp;
				setTemp.SetOpenFilter(strFilter);
		        
				if (setTemp.OpenRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedSave"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedSave"))
						{
							setTemp.m_sDescrizione = m_sDescrizione;

							setTemp.UpdateRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedSave");

							SalvaProcedureICD9(setTemp.m_lID);
						}
					}

					setTemp.CloseRecordset("CGruppiProcedureICD9ModDlg::OnBnClickedSave");
				}
			}
		}
	}

	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlListaGruppi.EnableWindow(TRUE);
	m_ctrlListaProcedure.EnableWindow(FALSE);
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

void CGruppiProcedureICD9ModDlg::OnBnClickedUndo()
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlListaGruppi.EnableWindow(TRUE);
	m_ctrlListaProcedure.EnableWindow(FALSE);
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

void CGruppiProcedureICD9ModDlg::OnLbnSelchangeListaGruppi()
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

			CGruppiProcedureICD9Set setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CGruppiProcedureICD9ModDlg::OnLbnSelchangeListaGruppi"))
			{
				if (!setTemp.IsEOF())
				{
					m_sDescrizione = setTemp.m_sDescrizione;

					SelezionaProcedureICD9(setTemp.m_lID);
				}

				setTemp.CloseRecordset("CGruppiProcedureICD9ModDlg::OnLbnSelchangeListaGruppi");
			}

			UpdateData(FALSE);
		}
	}
	else
	{
		m_ctrlListaProcedure.SelItemRange(FALSE, 0, m_ctrlListaProcedure.GetCount() - 1);
	}
}

void CGruppiProcedureICD9ModDlg::RiempiListaGruppi()
{
	CGruppiProcedureICD9Set setTemp;

	m_ctrlListaGruppi.ResetContent();

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CGruppiProcedureICD9ModDlg::RiempiListaGruppi") == TRUE)
	{
		int iTemp = 0;

		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListaGruppi.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListaGruppi.SetItemData(iTemp, (DWORD)setTemp.m_lID);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGruppiProcedureICD9ModDlg::RiempiListaGruppi");
	}

	m_ctrlListaGruppi.SetCurSel(-1);
}

void CGruppiProcedureICD9ModDlg::RiempiListaProcedure()
{
	CProcedureICD9Set setTemp;

	m_ctrlListaProcedure.ResetContent();

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CGruppiProcedureICD9ModDlg::RiempiListaPrestazioni") == TRUE)
	{
		int iTemp = 0;

		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListaProcedure.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListaProcedure.SetItemData(iTemp, (DWORD)setTemp.m_lID);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGruppiProcedureICD9ModDlg::RiempiListaPrestazioni");
	}
}

void CGruppiProcedureICD9ModDlg::SalvaProcedureICD9(long lContatoreEsame)
{
	int nCount = m_ctrlListaProcedure.GetSelCount();
	CArray<int, int> listSel;
	listSel.SetSize(nCount);
	m_ctrlListaProcedure.GetSelItems(nCount, listSel.GetData());

	int iTemp;
	CString strTemp;
	CGruppiProcedureICD9ProcedureICD9Set setTemp;

	//cancellazione
	strTemp.Format("IDGruppo=%li", lContatoreEsame);
	setTemp.SetBaseFilter(strTemp);
	if (setTemp.OpenRecordset("CGruppiProcedureICD9ModDlg::SalvaProcedureICD9") == TRUE)
	{
		while(!setTemp.IsEOF())
		{
			setTemp.DeleteRecordset("CGruppiProcedureICD9ModDlg::SalvaProcedureICD9");
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGruppiProcedureICD9ModDlg::SalvaProcedureICD9");
	}
	
	// per ogni Prestazione in lista controllo se è selezionato o meno //
	for(iTemp = 0; iTemp < listSel.GetCount(); iTemp++)
	{
		int ind = listSel.GetAt(iTemp);
		if (m_ctrlListaProcedure.GetSel(ind) > 0)
		{
			// l'elemento è selezionato e quindi se non lo trovo nel db lo aggiungo //

			strTemp.Format("IDProcedura=%li", (long)m_ctrlListaProcedure.GetItemData(listSel.GetAt(iTemp)));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CGruppiProcedureICD9ModDlg::SalvaProcedureICD9") == TRUE)
			{
				if (setTemp.IsEOF() == TRUE)
				{
					// non c'è e quindi lo aggiungo //

					if (setTemp.AddNewRecordset("CGruppiProcedureICD9ModDlg::SalvaProcedureICD9") == TRUE)
					{
						setTemp.m_lIDGruppo = lContatoreEsame;
						setTemp.m_lIDProcedura = (long)m_ctrlListaProcedure.GetItemData(listSel.GetAt(iTemp));

						setTemp.UpdateRecordset("CGruppiProcedureICD9ModDlg::SalvaProcedureICD9");
					}
				}

				setTemp.CloseRecordset("CGruppiProcedureICD9ModDlg::SalvaProcedureICD9");
			}
		}
		else
		{
			// l'elemento NON è selezionato e quindi se lo trovo nel db lo cancello //

			strTemp.Format("IDProcedura=%li", (long)m_ctrlListaProcedure.GetItemData(listSel.GetAt(iTemp)));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CGruppiProcedureICD9ModDlg::SalvaProcedureICD9") == TRUE)
			{
				if (setTemp.IsEOF() == FALSE)
				{
					// c'è e quindi lo elimino //

					setTemp.DeleteRecordset("CGruppiProcedureICD9ModDlg::SalvaProcedureICD9");
				}
			}
		}
	}
}

void CGruppiProcedureICD9ModDlg::SelezionaProcedureICD9(long lContatoreEsame)
{
	CString strTemp;
	CGruppiProcedureICD9ProcedureICD9Set setJoin;
	CProcedureICD9Set setProcedure;

	// Deseleziono tutti gli elementi //
	m_ctrlListaProcedure.SelItemRange(FALSE, 0, m_ctrlListaProcedure.GetCount() - 1);

	// Cerco nella tabella 'GruppiPrestazioniPrestazioni' tutti i record che hanno il 'IDGruppo' correntemente selezionato //
	strTemp.Format("IDGruppo=%li", lContatoreEsame);
	setJoin.SetOpenFilter(strTemp);

	if (setJoin.OpenRecordset("CGruppiProcedureICD9ModDlg::SelezionaPrestazioni") == TRUE)
	{
		while(setJoin.IsEOF() == FALSE)
		{
			// Prendo dalla tabella 'ECodificaRegionaleEx' la descrizione per esteso della prestazione trovata nella tabella 'GruppiPrestazioniPrestazioni' //
			strTemp.Format("ID=%li", setJoin.m_lIDProcedura);
			setProcedure.SetOpenFilter(strTemp);

			if (setProcedure.OpenRecordset("CGruppiProcedureICD9ModDlg::SelezionaPrestazioni") == TRUE)
			{
				if (setProcedure.IsEOF() == FALSE)
				{
					// Se trovo l'organo nella lista (e dovrei trovarlo, se sono arrivato qui) lo seleziono //
					int iFind = m_ctrlListaProcedure.FindStringExact(-1, setProcedure.m_sDescrizione);

					if (iFind != LB_ERR)
						m_ctrlListaProcedure.SetSel(iFind, TRUE);
				}

				setProcedure.CloseRecordset("CGruppiProcedureICD9ModDlg::SelezionaPrestazioni");
			}

			setJoin.MoveNext();
		}

		setJoin.CloseRecordset("CGruppiProcedureICD9ModDlg::SelezionaPrestazioni");
	}
}