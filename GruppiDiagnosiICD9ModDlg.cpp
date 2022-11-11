#include "stdafx.h"
#include "Endox.h"
#include "GruppiDiagnosiICD9ModDlg.h"

#include "Endox.h"
#include "EsamiView.h"
#include "DiagnosiICD9Set.h"
#include "GruppiDiagnosiICD9Set.h"
#include "GruppiDiagnosiICD9DiagnosiICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiDiagnosiICD9ModDlg, CDialog)

CGruppiDiagnosiICD9ModDlg::CGruppiDiagnosiICD9ModDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CGruppiDiagnosiICD9ModDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_sDescrizione = "";
	m_bAddNew = FALSE;
	m_bModify = FALSE;
}

CGruppiDiagnosiICD9ModDlg::~CGruppiDiagnosiICD9ModDlg()
{
}

BEGIN_MESSAGE_MAP(CGruppiDiagnosiICD9ModDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_NEW, OnBnClickedNew)
	ON_BN_CLICKED(IDC_EDT, OnBnClickedEdt)
	ON_BN_CLICKED(IDC_DEL, OnBnClickedDel)
	ON_BN_CLICKED(IDC_SAVE, OnBnClickedSave)
	ON_BN_CLICKED(IDC_UNDO, OnBnClickedUndo)

	ON_LBN_SELCHANGE(IDC_LISTA_GRUPPI, OnLbnSelchangeListaGruppi)
END_MESSAGE_MAP()

void CGruppiDiagnosiICD9ModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LISTA_GRUPPI, m_ctrlListaGruppi);
	DDX_Control(pDX, IDC_LISTA_DIAGNOSI, m_ctrlListaDiagnosi);

	DDX_Control(pDX, IDC_STATIC_GRUPPI, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_DIAGNOSI, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_GRUPPODIAGNOSI, m_ctrlStatic3);

	DDX_Control(pDX, IDC_NEW,   m_ctrlButtonNew);
	DDX_Control(pDX, IDC_EDT,	m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_DEL,   m_ctrlButtonDel);
	DDX_Control(pDX, IDC_SAVE,  m_ctrlButtonSave);
	DDX_Control(pDX, IDC_UNDO,	m_ctrlButtonUndo);
	DDX_Control(pDX, IDCANCEL,  m_ctrlButtonCancel);
	
	DDX_Text(pDX, IDC_DESCRIZIONE, m_sDescrizione);
}

HBRUSH CGruppiDiagnosiICD9ModDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		case IDC_STATIC_GRUPPODIAGNOSI:
		case IDC_DESCRIZIONE:
			pDC->SetTextColor(theApp.m_color[0]);
			break;

		case IDC_STATIC_PRESTAZIONI:
			pDC->SetTextColor(theApp.m_color[1]);
			break;
		case IDC_LISTA_DIAGNOSI:
			if (m_ctrlListaDiagnosi.IsWindowEnabled())
				pDC->SetTextColor(theApp.m_color[1]);
			else
				pDC->SetTextColor(RGB(192,192,192));
			break;
	}

	return hBrush;
}

BOOL CGruppiDiagnosiICD9ModDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_GRUPPI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_DIAGNOSI)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_NEW)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_DEL)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);

	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);

	m_ctrlListaGruppi.EnableWindow(TRUE);
	m_ctrlListaDiagnosi.EnableWindow(FALSE);

	RiempiListaGruppi();
	RiempiListaDiagnosi();
	
	RedrawWindow();

	theApp.LocalizeDialog(this, CGruppiDiagnosiICD9ModDlg::IDD, "GruppiDiagnosiICD9ModDlg");
	return TRUE;
}

void CGruppiDiagnosiICD9ModDlg::OnBnClickedNew()
{
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	m_ctrlListaGruppi.EnableWindow(FALSE);
	m_ctrlListaDiagnosi.EnableWindow(TRUE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(TRUE);

	GetDlgItem(IDC_NEW)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_UNDO)->EnableWindow(TRUE);

	// Deseleziono tutti gli elementi dalle liste delle prestazioni //
	m_ctrlListaDiagnosi.SelItemRange(FALSE, 0, m_ctrlListaDiagnosi.GetCount() - 1);

	m_sDescrizione = "";

	m_bAddNew = TRUE;

	UpdateData(FALSE);
	RedrawWindow();
}

void CGruppiDiagnosiICD9ModDlg::OnBnClickedEdt()
{
	int nSelect = m_ctrlListaGruppi.GetCurSel();
		
	if (nSelect >= 0)
	{
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

		m_ctrlListaGruppi.EnableWindow(FALSE);
		m_ctrlListaDiagnosi.EnableWindow(TRUE);
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

void CGruppiDiagnosiICD9ModDlg::OnBnClickedDel()
{
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlListaGruppi.EnableWindow(TRUE);
	m_ctrlListaDiagnosi.EnableWindow(FALSE);
	GetDlgItem(IDC_DESCRIZIONE)->EnableWindow(FALSE);

	GetDlgItem(IDC_NEW)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_DEL)->EnableWindow(m_ctrlListaGruppi.GetCurSel() >= 0);
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_UNDO)->EnableWindow(FALSE);

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DELETE_GRUPPODIAGNOSI), MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
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

			CGruppiDiagnosiICD9Set setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedDel"))
			{
				if (!setTemp.IsEOF())
					setTemp.DeleteRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedDel");
		
				setTemp.CloseRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedDel");
				RiempiListaGruppi();
			}
		}
	}
	
	UpdateData(FALSE);
	RedrawWindow();
}

void CGruppiDiagnosiICD9ModDlg::OnBnClickedSave()
{
	UpdateData(TRUE);

	if (m_sDescrizione.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TIPOESAMEDLG_EMPTY_DESC), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		CGruppiDiagnosiICD9Set setTemp;

        if (setTemp.OpenRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedSave"))
		{
			if (setTemp.AddNewRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedSave"))
			{
				setTemp.m_sDescrizione = m_sDescrizione;

				setTemp.UpdateRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedSave");
				setTemp.CloseRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedSave");

				setTemp.SetSortRecord("ID");
				if (setTemp.OpenRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedSave"))
				{
					setTemp.MoveLast();

					SalvaDiagnosiICD9(setTemp.m_lID);

					setTemp.CloseRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedSave");
				}
			}

			setTemp.CloseRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedSave");
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

				CGruppiDiagnosiICD9Set setTemp;
				setTemp.SetOpenFilter(strFilter);
		        
				if (setTemp.OpenRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedSave"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.EditRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedSave"))
						{
							setTemp.m_sDescrizione = m_sDescrizione;

							setTemp.UpdateRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedSave");

							SalvaDiagnosiICD9(setTemp.m_lID);
						}
					}

					setTemp.CloseRecordset("CGruppiDiagnosiICD9ModDlg::OnBnClickedSave");
				}
			}
		}
	}

	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlListaGruppi.EnableWindow(TRUE);
	m_ctrlListaDiagnosi.EnableWindow(FALSE);
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

void CGruppiDiagnosiICD9ModDlg::OnBnClickedUndo()
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	m_ctrlListaGruppi.EnableWindow(TRUE);
	m_ctrlListaDiagnosi.EnableWindow(FALSE);
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

void CGruppiDiagnosiICD9ModDlg::OnLbnSelchangeListaGruppi()
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

			CGruppiDiagnosiICD9Set setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CGruppiDiagnosiICD9ModDlg::OnLbnSelchangeListaGruppi"))
			{
				if (!setTemp.IsEOF())
				{
					m_sDescrizione = setTemp.m_sDescrizione;

					SelezionaDiagnosiICD9(setTemp.m_lID);
				}

				setTemp.CloseRecordset("CGruppiDiagnosiICD9ModDlg::OnLbnSelchangeListaGruppi");
			}

			UpdateData(FALSE);
		}
	}
	else
	{
		m_ctrlListaDiagnosi.SelItemRange(FALSE, 0, m_ctrlListaDiagnosi.GetCount() - 1);
	}
}

void CGruppiDiagnosiICD9ModDlg::RiempiListaGruppi()
{
	CGruppiDiagnosiICD9Set setTemp;

	m_ctrlListaGruppi.ResetContent();

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CGruppiDiagnosiICD9ModDlg::RiempiListaGruppi") == TRUE)
	{
		int iTemp = 0;

		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListaGruppi.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListaGruppi.SetItemData(iTemp, (DWORD)setTemp.m_lID);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGruppiDiagnosiICD9ModDlg::RiempiListaGruppi");
	}

	m_ctrlListaGruppi.SetCurSel(-1);
}

void CGruppiDiagnosiICD9ModDlg::RiempiListaDiagnosi()
{
	CDiagnosiICD9Set setTemp;

	m_ctrlListaDiagnosi.ResetContent();

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CGruppiDiagnosiICD9ModDlg::RiempiListaPrestazioni") == TRUE)
	{
		int iTemp = 0;

		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListaDiagnosi.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListaDiagnosi.SetItemData(iTemp, (DWORD)setTemp.m_lID);

			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGruppiDiagnosiICD9ModDlg::RiempiListaPrestazioni");
	}
}

void CGruppiDiagnosiICD9ModDlg::SalvaDiagnosiICD9(long lContatoreEsame)
{
	int nCount = m_ctrlListaDiagnosi.GetSelCount();
	CArray<int, int> listSel;
	listSel.SetSize(nCount);
	m_ctrlListaDiagnosi.GetSelItems(nCount, listSel.GetData());

	int iTemp;
	CString strTemp;
	CGruppiDiagnosiICD9DiagnosiICD9Set setTemp;

	//Cancello quelli esistenti
	strTemp.Format("IDGruppo=%li", lContatoreEsame);
	setTemp.SetBaseFilter(strTemp);
	if (setTemp.OpenRecordset("CGruppiDiagnosiICD9ModDlg::SalvaDiagnosiICD9") == TRUE)
	{
		while(!setTemp.IsEOF())
		{
			setTemp.DeleteRecordset("CGruppiDiagnosiICD9ModDlg::SalvaDiagnosiICD9");
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGruppiDiagnosiICD9ModDlg::SalvaDiagnosiICD9");
	}
	
	// per ogni Prestazione in lista controllo se è selezionato o meno //
	for(iTemp = 0; iTemp < listSel.GetCount(); iTemp++)
	{
		int ind = listSel.GetAt(iTemp);
		if (m_ctrlListaDiagnosi.GetSel(ind) > 0)
		{
			// l'elemento è selezionato e quindi se non lo trovo nel db lo aggiungo //

			strTemp.Format("IDDiagnosi=%li", (long)m_ctrlListaDiagnosi.GetItemData(listSel.GetAt(iTemp)));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CGruppiDiagnosiICD9ModDlg::SalvaDiagnosiICD9") == TRUE)
			{
				if (setTemp.IsEOF() == TRUE)
				{
					// non c'è e quindi lo aggiungo //

					if (setTemp.AddNewRecordset("CGruppiDiagnosiICD9ModDlg::SalvaDiagnosiICD9") == TRUE)
					{
						setTemp.m_lIDGruppo = lContatoreEsame;
						setTemp.m_lIDDiagnosi = (long)m_ctrlListaDiagnosi.GetItemData(listSel.GetAt(iTemp));

						setTemp.UpdateRecordset("CGruppiDiagnosiICD9ModDlg::SalvaDiagnosiICD9");
					}
				}

				setTemp.CloseRecordset("CGruppiDiagnosiICD9ModDlg::SalvaDiagnosiICD9");
			}
		}
		else
		{
			// l'elemento NON è selezionato e quindi se lo trovo nel db lo cancello //

			strTemp.Format("IDDiagnosi=%li", (long)m_ctrlListaDiagnosi.GetItemData(listSel.GetAt(iTemp)));
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CGruppiDiagnosiICD9ModDlg::SalvaDiagnosiICD9") == TRUE)
			{
				if (setTemp.IsEOF() == FALSE)
				{
					// c'è e quindi lo elimino //

					setTemp.DeleteRecordset("CGruppiDiagnosiICD9ModDlg::SalvaDiagnosiICD9");
				}
			}
		}
	}
}

void CGruppiDiagnosiICD9ModDlg::SelezionaDiagnosiICD9(long lContatoreEsame)
{
	CString strTemp;
	CGruppiDiagnosiICD9DiagnosiICD9Set setJoin;
	CDiagnosiICD9Set setDiagnosi;

	// Deseleziono tutti gli elementi //
	m_ctrlListaDiagnosi.SelItemRange(FALSE, 0, m_ctrlListaDiagnosi.GetCount() - 1);

	// Cerco nella tabella 'GruppiPrestazioniPrestazioni' tutti i record che hanno il 'IDGruppo' correntemente selezionato //
	strTemp.Format("IDGruppo=%li", lContatoreEsame);
	setJoin.SetOpenFilter(strTemp);

	if (setJoin.OpenRecordset("CGruppiDiagnosiICD9ModDlg::SelezionaPrestazioni") == TRUE)
	{
		while(setJoin.IsEOF() == FALSE)
		{
			// Prendo dalla tabella 'ECodificaRegionaleEx' la descrizione per esteso della prestazione trovata nella tabella 'GruppiPrestazioniPrestazioni' //
			strTemp.Format("ID=%li", setJoin.m_lIDDiagnosi);
			setDiagnosi.SetOpenFilter(strTemp);

			if (setDiagnosi.OpenRecordset("CGruppiDiagnosiICD9ModDlg::SelezionaPrestazioni") == TRUE)
			{
				if (setDiagnosi.IsEOF() == FALSE)
				{
					// Se trovo l'organo nella lista (e dovrei trovarlo, se sono arrivato qui) lo seleziono //
					int iFind = m_ctrlListaDiagnosi.FindStringExact(-1, setDiagnosi.m_sDescrizione);

					if (iFind != LB_ERR)
						m_ctrlListaDiagnosi.SetSel(iFind, TRUE);
				}

				setDiagnosi.CloseRecordset("CGruppiDiagnosiICD9ModDlg::SelezionaPrestazioni");
			}

			setJoin.MoveNext();
		}

		setJoin.CloseRecordset("CGruppiDiagnosiICD9ModDlg::SelezionaPrestazioni");
	}
}