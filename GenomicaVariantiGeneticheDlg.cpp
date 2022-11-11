#include "stdafx.h"
#include "Endox.h"
#include "GenomicaVariantiGeneticheDlg.h"
#include "VariantiGeneticheSet.h"
#include "PatogenicitaSet.h"
#include "TipiVariantiGeneticheSet.h"
#include "TipiAlterazioniSet.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGenomicaVariantiGeneticheDlg, CDialog)

CGenomicaVariantiGeneticheDlg::CGenomicaVariantiGeneticheDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CGenomicaVariantiGeneticheDlg::IDD, pParent)
{
	m_pEsamiView = pEsamiView;
	m_lIDSelected = 1;
	m_lIDTipoAlterazioneSelected = -1;
	m_lIDTipoVarianteSelected = -1;
	m_bMarcaObbligatori = FALSE;
}

CGenomicaVariantiGeneticheDlg::~CGenomicaVariantiGeneticheDlg()
{
}

BEGIN_MESSAGE_MAP(CGenomicaVariantiGeneticheDlg, CDialog)
	ON_MESSAGE(WM_GENOMICA_FILTROVARIANTE, ProccessVarianteFilter)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)	
	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)
	ON_CBN_SELCHANGE(IDC_PATOGENICITA, OnCbnSelchange)
	ON_CBN_SELCHANGE(IDC_TIPOVARIANTE, OnCbnSelchange)
	ON_CBN_SELCHANGE(IDC_TIPOALTERAZIONE, OnCbnSelchange)
	ON_WM_CTLCOLOR()
	
END_MESSAGE_MAP()

void CGenomicaVariantiGeneticheDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlButtonEdit);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_RICERCA_PLACE, m_ctrlStaticRicercaForm);

	DDX_Control(pDX, IDC_PATOGENICITA, m_ctrlComboPatogenicita);
	DDX_Control(pDX, IDC_TIPOVARIANTE, m_ctrlComboTipoVariante);
	DDX_Control(pDX, IDC_TIPOALTERAZIONE, m_ctrlComboTipoAlterazione);	

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_7, m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC_8, m_ctrlStatic8);
	DDX_Control(pDX, IDC_STATIC_9, m_ctrlStatic9);
	DDX_Control(pDX, IDC_STATIC_10, m_ctrlStatic10);
	DDX_Control(pDX, IDC_STATIC_11, m_ctrlStatic11);
}

BOOL CGenomicaVariantiGeneticheDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(0, "Titolo", LVCFMT_LEFT, 0);	

	//RiempiLista();
	RiempiCombos();	

	EditDialog(FALSE);

	CGenomicaRicercaVarianteForm::CreateFormEx(this, &m_ctrlStaticRicercaForm, m_pEsamiView, &m_pRicercaForm, BTNADD_DISABLE);

	theApp.LocalizeDialog(this, CGenomicaVariantiGeneticheDlg::IDD, "CGenomicaVariantiGeneticheDlg");
	return TRUE;
}

void CGenomicaVariantiGeneticheDlg::OnOK()
{
	if (GetFocus() == GetDlgItem(IDOK))
		CDialog::OnOK();

	else if (GetDlgItem(IDOK)->IsWindowEnabled())
		m_pRicercaForm->OnBnClickedBtnFind();
}

void CGenomicaVariantiGeneticheDlg::OnCancel()
{
	if (GetDlgItem(IDOK)->IsWindowEnabled())
		CDialog::OnCancel();
}

void CGenomicaVariantiGeneticheDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CList<long> listID;
	CVariantiGeneticheSet().GetIDList(listID);

	for (POSITION pos = listID.GetHeadPosition(); pos;)
	{
		long lID = listID.GetNext(pos);

		int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), CVariantiGeneticheSet().GetTitolo(lID));		
		m_ctrlList.SetItemData(nItem, (DWORD)lID);
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
	
	RedrawWindow();

	EndWaitCursor();
}

void CGenomicaVariantiGeneticheDlg::RiempiCombos()
{
	m_ctrlComboPatogenicita.ResetContent();
	m_ctrlComboTipoVariante.ResetContent();
	m_ctrlComboTipoAlterazione.ResetContent();

	CList<long> list;
	long nIndex = 0;
	
	CPatogenicitaSet().GetIDList(list);
	for (POSITION pos = list.GetHeadPosition(); pos;)
	{
		if (nIndex == 0)
		{
			m_ctrlComboPatogenicita.InsertString(nIndex, "");
			m_ctrlComboPatogenicita.SetItemData(nIndex, 0);
		}
		else
		{
			long lID = list.GetNext(pos);

			CString sCodice = CPatogenicitaSet().GetCodice(lID);
			CString sDesc = CPatogenicitaSet().GetDescrizione(lID);
			CString sValue = sDesc.IsEmpty() ? sCodice : sCodice + " - " + sDesc;

			m_ctrlComboPatogenicita.InsertString(nIndex, sValue);
			m_ctrlComboPatogenicita.SetItemData(nIndex, lID);
		}
		nIndex++;
	}	

	nIndex = 0;
	list.RemoveAll();
	CTipiVariantiGeneticheSet().GetIDList(list);
	for (POSITION pos = list.GetHeadPosition(); pos;)
	{
		if (nIndex == 0)
		{
			m_ctrlComboTipoVariante.InsertString(nIndex, "");
			m_ctrlComboTipoVariante.SetItemData(nIndex, 0);
		}
		else
		{
			long lID = list.GetNext(pos);

			CString sCodice = CTipiVariantiGeneticheSet().GetCodice(lID);
			CString sDesc = CTipiVariantiGeneticheSet().GetDescrizione(lID);
			CString sValue = sDesc.IsEmpty() ? sCodice : sCodice + " - " + sDesc;

			m_ctrlComboTipoVariante.InsertString(nIndex, sValue);
			m_ctrlComboTipoVariante.SetItemData(nIndex, lID);
		}
		nIndex++;
	}

	nIndex = 0;
	list.RemoveAll();
	CTipiAlterazioniSet().GetIDList(list);
	for (POSITION pos = list.GetHeadPosition(); pos;)
	{
		if (nIndex == 0)
		{
			m_ctrlComboTipoAlterazione.InsertString(nIndex, "");
			m_ctrlComboTipoAlterazione.SetItemData(nIndex, 0);
		}
		else
		{
			long lID = list.GetNext(pos);

			CString sCodice = CTipiAlterazioniSet().GetCodice(lID);
			CString sDesc = CTipiAlterazioniSet().GetDescrizione(lID);
			CString sValue = sDesc.IsEmpty() ? sCodice : sCodice + " - " + sDesc;

			m_ctrlComboTipoAlterazione.InsertString(nIndex, sValue);
			m_ctrlComboTipoAlterazione.SetItemData(nIndex, lID);
		}
		nIndex++;
	}
}


void CGenomicaVariantiGeneticheDlg::CaricaDati()
{
	GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);

	SetDlgItemText(IDC_TITOLO, "");
	SetDlgItemText(IDC_TRASCRIZIONE, "");	
	SetDlgItemText(IDC_CROMOSSOMA, "");
	SetDlgItemText(IDC_GENE, "");
	SetDlgItemText(IDC_POSIZIONE, "");
	SetDlgItemText(IDC_CODICE, "");
	SetDlgItemText(IDC_HGVSC, "");
	SetDlgItemText(IDC_HGVSP, "");
	
	m_ctrlComboPatogenicita.SetCurSel(0);
	m_ctrlComboTipoVariante.SetCurSel(0);
	m_ctrlComboTipoAlterazione.SetCurSel(0);

	//
	
	SetDlgItemText(IDC_TITOLO, CVariantiGeneticheSet().GetTitolo(m_lIDSelected));
	SetDlgItemText(IDC_TRASCRIZIONE, CVariantiGeneticheSet().GetTrascrizione(m_lIDSelected));
	SetDlgItemText(IDC_CROMOSSOMA, CVariantiGeneticheSet().GetCromossoma(m_lIDSelected));
	SetDlgItemText(IDC_GENE, CVariantiGeneticheSet().GetGene(m_lIDSelected));
	SetDlgItemText(IDC_POSIZIONE, CVariantiGeneticheSet().GetPosizioneGene(m_lIDSelected));
	SetDlgItemText(IDC_CODICE, CVariantiGeneticheSet().GetCodice(m_lIDSelected));
	SetDlgItemText(IDC_HGVSC, CVariantiGeneticheSet().GetHGVSc(m_lIDSelected));
	SetDlgItemText(IDC_HGVSP, CVariantiGeneticheSet().GetHGVSp(m_lIDSelected));	

	long lIDPatogenicita = CVariantiGeneticheSet().GetIDPatogenicita(m_lIDSelected);
	for (int i = 0; i < m_ctrlComboPatogenicita.GetCount(); i++)
	{
		if ((long)m_ctrlComboPatogenicita.GetItemData(i) == lIDPatogenicita)
		{
			m_ctrlComboPatogenicita.SetCurSel(i);
			break;
		}
	}
	long lIDTipoVariante = CVariantiGeneticheSet().GetIDTipoVariante(m_lIDSelected);	
	m_lIDTipoVarianteSelected = lIDTipoVariante;
	for (int i = 0; i < m_ctrlComboTipoVariante.GetCount(); i++)
	{
		if ((long)m_ctrlComboTipoVariante.GetItemData(i) == lIDTipoVariante)
		{
			m_ctrlComboTipoVariante.SetCurSel(i);
			break;
		}
	}
	long lIDTipoAlterazione = CVariantiGeneticheSet().GetIDTipoAlterazione(m_lIDSelected);
	m_lIDTipoAlterazioneSelected = lIDTipoAlterazione;
	for (int i = 0; i < m_ctrlComboTipoAlterazione.GetCount(); i++)
	{
		if ((long)m_ctrlComboTipoAlterazione.GetItemData(i) == lIDTipoAlterazione)
		{
			m_ctrlComboTipoAlterazione.SetCurSel(i);
			break;
		}
	}	

	//

	GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
}

void CGenomicaVariantiGeneticheDlg::UnselectAll()
{
	if (m_ctrlList.GetItemCount() > 0)
	{
		for (int i = 0; i < m_ctrlList.GetItemCount(); i++)
			m_ctrlList.SetItemState(i, 0, LVIS_SELECTED);
	}
	else
	{
		OnLvnItemchangedList(NULL, NULL);
	}
}

void CGenomicaVariantiGeneticheDlg::EditDialog(BOOL bEdit)
{
	m_ctrlList.EnableWindow(!bEdit);	
	SendDlgItemMessage(IDC_TITOLO, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_TRASCRIZIONE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_CROMOSSOMA, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_GENE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_POSIZIONE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_CODICE, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_HGVSC, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	SendDlgItemMessage(IDC_HGVSP, EM_SETREADONLY, (WPARAM)!bEdit, (LPARAM)0);
	m_ctrlComboPatogenicita.EnableWindow(bEdit);
	m_ctrlComboTipoVariante.EnableWindow(bEdit);
	m_ctrlComboTipoAlterazione.EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_NEW)->EnableWindow(!bEdit);
	GetDlgItem(IDC_BTN_EDT)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_DEL)->EnableWindow((!bEdit) && (m_ctrlList.GetFirstSelectedItemPosition() != NULL));
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEdit);
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(bEdit);
}


// CGenomicaPatogenicitaDlg message handlers
void CGenomicaVariantiGeneticheDlg::OnBnClickedBtnNew()
{
	UnselectAll();
	EditDialog(TRUE);
}

void CGenomicaVariantiGeneticheDlg::OnBnClickedBtnEdt()
{
	EditDialog(TRUE);
}

void CGenomicaVariantiGeneticheDlg::OnBnClickedBtnDel()
{
	if (AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		if (m_lIDSelected > 0)
		{
			if (!CVariantiGeneticheSet().SetEliminato(m_lIDSelected))
				AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO1));
		}
		UnselectAll();
		//RiempiLista();
	}
}

void CGenomicaVariantiGeneticheDlg::OnBnClickedBtnUndo()
{
	UnselectAll();
	//RiempiLista();
	RiempiCombos();
	EditDialog(FALSE);
}

void CGenomicaVariantiGeneticheDlg::OnBnClickedBtnSave()
{
	if (!UpdateData(TRUE))
		return;
	
	if (VerificaCampiObbligatori())
	{		
		if (m_lIDSelected <= 0)
		{
			CString sTitolo;
			GetDlgItemText(IDC_TITOLO, sTitolo);
			if (CVariantiGeneticheSet().CheckTitolo(sTitolo))
			{
				AfxMessageBox(theApp.GetMessageString(IDS_GENOMICA_ERRO5), MB_ICONSTOP);
				return;
			}

			// addnew //
			CVariantiGeneticheSet setTemp;
			setTemp.SetOpenFilter("");
			if (setTemp.OpenRecordset("CGenomicaVariantiGeneticheDlg::OnBnClickedBtnSave"))
			{
				if (setTemp.AddNewRecordset("CGenomicaVariantiGeneticheDlg::OnBnClickedBtnSave"))
				{
					GetDlgItemText(IDC_TITOLO, setTemp.m_sTitolo);
					GetDlgItemText(IDC_TRASCRIZIONE, setTemp.m_sTrascrizione);
					GetDlgItemText(IDC_CROMOSSOMA, setTemp.m_sCromossoma);
					GetDlgItemText(IDC_GENE, setTemp.m_sGene);
					GetDlgItemText(IDC_POSIZIONE, setTemp.m_sPosizioneGene);
					GetDlgItemText(IDC_CODICE, setTemp.m_sCodice);
					GetDlgItemText(IDC_HGVSC, setTemp.m_sHGVSc);
					GetDlgItemText(IDC_HGVSP, setTemp.m_sHGVSp);
					setTemp.m_lIDPatogenicita = (long)m_ctrlComboPatogenicita.GetItemData(m_ctrlComboPatogenicita.GetCurSel());
					setTemp.m_lIDTipoVariante = (long)m_ctrlComboTipoVariante.GetItemData(m_ctrlComboTipoVariante.GetCurSel());
					setTemp.m_lIDTipoAlterazione = (long)m_ctrlComboTipoAlterazione.GetItemData(m_ctrlComboTipoAlterazione.GetCurSel());
					setTemp.m_bEliminato = FALSE;

					setTemp.UpdateRecordset("CGenomicaVariantiGeneticheDlg::OnBnClickedBtnSave");
				}
				setTemp.CloseRecordset("CGenomicaVariantiGeneticheDlg::OnBnClickedBtnSave");
			}
		}
		else
		{
			CString sTemp;
			
			GetDlgItemText(IDC_TITOLO, sTemp);
			CVariantiGeneticheSet().SetTitolo(m_lIDSelected, sTemp);
			
			GetDlgItemText(IDC_TRASCRIZIONE, sTemp);
			CVariantiGeneticheSet().SetTrascrizione(m_lIDSelected, sTemp);
			
			GetDlgItemText(IDC_CROMOSSOMA, sTemp);
			CVariantiGeneticheSet().SetCromossoma(m_lIDSelected, sTemp);
			
			GetDlgItemText(IDC_GENE, sTemp);
			CVariantiGeneticheSet().SetGene(m_lIDSelected, sTemp);
			
			GetDlgItemText(IDC_POSIZIONE, sTemp);
			CVariantiGeneticheSet().SetPosizioneGene(m_lIDSelected, sTemp);
			
			GetDlgItemText(IDC_CODICE, sTemp);
			CVariantiGeneticheSet().SetCodice(m_lIDSelected, sTemp);
			
			GetDlgItemText(IDC_HGVSC, sTemp);
			CVariantiGeneticheSet().SetHGVSc(m_lIDSelected, sTemp);
			
			GetDlgItemText(IDC_HGVSP, sTemp);
			CVariantiGeneticheSet().SetHGVSp(m_lIDSelected, sTemp);
			
			CVariantiGeneticheSet().SetIDPatogenicita(m_lIDSelected, (long)m_ctrlComboPatogenicita.GetItemData(m_ctrlComboPatogenicita.GetCurSel()));
			CVariantiGeneticheSet().SetIDTipoVariante(m_lIDSelected, (long)m_ctrlComboTipoVariante.GetItemData(m_ctrlComboTipoVariante.GetCurSel()));
			CVariantiGeneticheSet().SetIDTipoAlterazione(m_lIDSelected, (long)m_ctrlComboTipoAlterazione.GetItemData(m_ctrlComboTipoAlterazione.GetCurSel()));
		}

		UnselectAll();
		//RiempiLista();
		EditDialog(FALSE);
	}
	else
	{
		AfxMessageBox(theApp.GetMessageString(IDS_ESAMIVIEW_FIELD_OBBLIGATORY), MB_ICONSTOP);
	}	
}

void CGenomicaVariantiGeneticheDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lIDSelected = -1;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_lIDSelected = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

	CaricaDati();
}

HBRUSH CGenomicaVariantiGeneticheDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{		 
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (m_bMarcaObbligatori)
	{
		BOOL bCodice, bTipo, bTrascrizione, bHGVSc, bHGVSp = FALSE;
		if (m_lIDTipoVarianteSelected > 0)
			CTipiVariantiGeneticheSet().GetObbligatori(m_lIDTipoVarianteSelected, bCodice, bTipo, bTrascrizione);

		if (m_lIDTipoAlterazioneSelected > 0)
			CTipiAlterazioniSet().GetObbligatori(m_lIDTipoAlterazioneSelected, bHGVSc, bHGVSp);


		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_STATIC_1: //Titolo		
		case IDC_STATIC_3: //Cromossoma
		case IDC_STATIC_4: //Gene
		case IDC_STATIC_5: //Posizione
		case IDC_STATIC_9: //Patogenicita
		case IDC_STATIC_11: //Tipo variante
			pDC->SetTextColor(RGB(255, 0, 0));
			pDC->SetBkColor(RGB(255, 255, 0));
			break;
		case IDC_STATIC_6: //Codice
			if (bCodice == TRUE)
			{
				pDC->SetTextColor(RGB(255, 0, 0));
				pDC->SetBkColor(RGB(255, 255, 0));
			}
			break;
		case IDC_STATIC_7: //HGVSc
			if (bHGVSc == TRUE)
			{
				pDC->SetTextColor(RGB(255, 0, 0));
				pDC->SetBkColor(RGB(255, 255, 0));
			}
			break;
		case IDC_STATIC_8: //HGVSp
			if (bHGVSp == TRUE)
			{
				pDC->SetTextColor(RGB(255, 0, 0));
				pDC->SetBkColor(RGB(255, 255, 0));
			}
			break;
		case IDC_STATIC_10: //Tipo alterazione
			if (bTipo == TRUE)
			{
				pDC->SetTextColor(RGB(255, 0, 0));
				pDC->SetBkColor(RGB(255, 255, 0));
			}
			break;
		case IDC_STATIC_2: //Trascrizione
			if (bTrascrizione == TRUE)
			{
				pDC->SetTextColor(RGB(255, 0, 0));
				pDC->SetBkColor(RGB(255, 255, 0));
			}
			break;
		}
	}
	return hBrush;
}

void CGenomicaVariantiGeneticheDlg::OnCbnSelchange()
{
	long lOldVar = m_lIDTipoVarianteSelected;
	long lOldTipo = m_lIDTipoAlterazioneSelected;
	
	m_lIDTipoVarianteSelected = (long)m_ctrlComboTipoVariante.GetItemData(m_ctrlComboTipoVariante.GetCurSel());
	m_lIDTipoAlterazioneSelected = (long)m_ctrlComboTipoAlterazione.GetItemData(m_ctrlComboTipoAlterazione.GetCurSel());

	if (lOldVar != m_lIDTipoVarianteSelected || lOldTipo != m_lIDTipoAlterazioneSelected)
		RedrawWindow();
}

BOOL CGenomicaVariantiGeneticheDlg::VerificaCampiObbligatori()
{
	BOOL bResult = TRUE;
	CString strTemp;
	
	GetDlgItemText(IDC_TITOLO, strTemp);
	strTemp.Trim();
	bResult = bResult && !strTemp.IsEmpty();

	bResult = bResult && (int)m_ctrlComboPatogenicita.GetCurSel() > 0;
	bResult = bResult && (int)m_ctrlComboTipoVariante.GetCurSel() > 0;

	GetDlgItemText(IDC_CROMOSSOMA, strTemp);
	strTemp.Trim();
	bResult = bResult && !strTemp.IsEmpty();

	GetDlgItemText(IDC_GENE, strTemp);
	strTemp.Trim();
	bResult = bResult && !strTemp.IsEmpty();

	GetDlgItemText(IDC_POSIZIONE, strTemp);
	strTemp.Trim();
	bResult = bResult && !strTemp.IsEmpty();	

	BOOL bCodice, bTipo, bTrascrizione, bHGVSc, bHGVSp = FALSE;
	if (m_lIDTipoVarianteSelected > 0)
		CTipiVariantiGeneticheSet().GetObbligatori(m_lIDTipoVarianteSelected, bCodice, bTipo, bTrascrizione);

	if (m_lIDTipoAlterazioneSelected > 0)
		CTipiAlterazioniSet().GetObbligatori(m_lIDTipoAlterazioneSelected, bHGVSc, bHGVSp);

	if (bCodice == TRUE)
	{
		GetDlgItemText(IDC_CODICE, strTemp);
		strTemp.Trim();
		bResult = bResult && !strTemp.IsEmpty();
	}

	if (bHGVSc == TRUE)
	{
		GetDlgItemText(IDC_HGVSC, strTemp);
		strTemp.Trim();
		bResult = bResult && !strTemp.IsEmpty();
	}
	if (bHGVSp == TRUE)
	{
		GetDlgItemText(IDC_HGVSP, strTemp);
		strTemp.Trim();
		bResult = bResult && !strTemp.IsEmpty();
	}
	if (bTipo == TRUE)
	{
		bResult = bResult && (int)m_ctrlComboTipoAlterazione.GetCurSel() > 0;
	}	
	if (bTrascrizione == TRUE)
	{
		GetDlgItemText(IDC_TRASCRIZIONE, strTemp);
		strTemp.Trim();
		bResult = bResult && !strTemp.IsEmpty();
	}

	return bResult;
}

LRESULT CGenomicaVariantiGeneticheDlg::ProccessVarianteFilter(WPARAM wParam, LPARAM lParam)
{
	BeginWaitCursor();

	try
	{
		CList<long>* pList = (CList<long>*)wParam;

		long lCount = pList->GetCount();
		UnselectAll();

		//

		m_ctrlList.SetRedraw(FALSE);
		m_ctrlList.DeleteAllItems();

		for (POSITION pos = pList->GetHeadPosition(); pos;)
		{
			long lID = pList->GetNext(pos);

			int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), CVariantiGeneticheSet().GetTitolo(lID));
			m_ctrlList.SetItemText(nItem, 1, CTipiVariantiGeneticheSet().GetCodice(CVariantiGeneticheSet().GetIDTipoVariante(lID)));
			m_ctrlList.SetItemText(nItem, 2, CVariantiGeneticheSet().GetTrascrizione(lID));
			m_ctrlList.SetItemText(nItem, 3, CVariantiGeneticheSet().GetCromossoma(lID));
			m_ctrlList.SetItemText(nItem, 4, CVariantiGeneticheSet().GetGene(lID));
			m_ctrlList.SetItemText(nItem, 5, CVariantiGeneticheSet().GetPosizioneGene(lID));
			m_ctrlList.SetItemText(nItem, 6, CVariantiGeneticheSet().GetCodice(lID));
			m_ctrlList.SetItemText(nItem, 7, CTipiAlterazioniSet().GetCodice(CVariantiGeneticheSet().GetIDTipoAlterazione(lID)));
			m_ctrlList.SetItemText(nItem, 8, CVariantiGeneticheSet().GetHGVSc(lID));
			m_ctrlList.SetItemText(nItem, 9, CVariantiGeneticheSet().GetHGVSp(lID));
			m_ctrlList.SetItemText(nItem, 10, CPatogenicitaSet().GetCodice(CVariantiGeneticheSet().GetIDPatogenicita(lID)));
			m_ctrlList.SetItemData(nItem, (DWORD)lID);
		}

		m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(6, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(7, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(8, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(9, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(10, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetRedraw(TRUE);
	}
	catch (...)
	{
		//
	}

	EndWaitCursor();

	return 1;
}