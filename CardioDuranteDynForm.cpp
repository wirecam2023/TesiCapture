#include "stdafx.h"
#include "Endox.h"
#include "CardioDuranteDynForm.h"

#include "EsamiSet.h"
#include "EsamiView.h"
#include "NumeroNuoviStadiDlg.h"
#include "ProtocolloCardioSet.h"
#include "ProtocolloColonneSet.h"
#include "ProtocolloEsamiSet.h"
#include "ProtocolloValoriDefaultSet.h"

#define RGB_MODIFICABILE RGB(255, 255, 191)
#define RGB_SOLALETTURA RGB(223, 223, 223)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCardioDuranteDynForm::CCardioDuranteDynForm(CWnd* pParent, CEsamiView* pEsamiView)
: CEndoxDynForm(CCardioDuranteDynForm::IDD, pParent, pEsamiView),
m_ctrlList(FALSE, TRUE, TRUE)
{
	m_bReadOnly = TRUE;

	m_lIDProtocollo = 0;
	m_lNumColonne = 0;
	m_pArrayStructColonne = NULL;

	m_nColonnaTempo = -1;
	m_nColonnaSommaTempo = -1;
	m_nColonnaMETS = -1;
	m_nColonnaTempoOriginale = -1;
}

CCardioDuranteDynForm::~CCardioDuranteDynForm(void)
{
	if (m_pArrayStructColonne != NULL)
	{
		delete m_pArrayStructColonne;
		m_pArrayStructColonne = NULL;
	}
}

BEGIN_MESSAGE_MAP(CCardioDuranteDynForm, CEndoxDynForm)

	ON_BN_CLICKED(IDC_BTN_ADD, OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)

	ON_CBN_SELCHANGE(IDC_COMBO, OnCbnSelchangeCombo)

	ON_MESSAGE(WM_PROTOCOLLOCHANGED, OnListSubitemChanged)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

void CCardioDuranteDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_cardio_durante] == NULL)
	{
		pEsamiView->m_pDynForm[sub_cardio_durante] = new CCardioDuranteDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_cardio_durante] != NULL)
		{
			pEsamiView->m_pDynForm[sub_cardio_durante]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_cardio_durante]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_cardio_durante]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_cardio_durante]->CreateChildForm(CCardioDuranteDynForm::IDD, pParent, rectFrame);
		}
	}		
}

void CCardioDuranteDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	//

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_BTN_ADD, m_ctrlBtnAdd);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);

	DDX_Control(pDX, IDC_COMBO, m_ctrlCombo);

	DDX_Control(pDX, IDC_STATIC_TITLE, m_ctrlStaticTitle);
	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);

	//

	if (pDX->m_bSaveAndValidate)
		m_pEsamiView->m_pEsamiSet->m_lIDProtocolloUsato = m_lIDProtocollo;
	else
		m_lIDProtocollo = m_pEsamiView->m_pEsamiSet->m_lIDProtocolloUsato;

	if (theApp.m_bPersonalizzazioniBrasileFleury)
		m_ctrlCardioDopoForm = (CCardioDopoDynForm*)m_pEsamiView->m_pDynForm[sub_cardio_dopo];
	else
		m_ctrlCardioDopoForm = NULL;
}

HBRUSH CCardioDuranteDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_TITLE:
		case IDC_STATIC_00:
		case IDC_COMBO:
		case IDC_BTN_ADD:
		case IDC_BTN_DEL:
		case IDC_LIST:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hReturn;
}

BOOL CCardioDuranteDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_TITLE, CSize(0, 0), CSize(100, 0));

	AddAnchor(IDC_STATIC_00, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_COMBO, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_BTN_ADD, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_DEL, CSize(100, 100), CSize(100, 100));

	m_ctrlStaticTitle.SetFont(&theApp.m_fontBold);
	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.SetNotificationChangeValueMessage(WM_PROTOCOLLOCHANGED);

	//

	RiempiCombo();

	//	

	theApp.LocalizeDialog(this, CCardioDuranteDynForm::IDD, "CardioDuranteDynForm");
	return bReturn;
}

LRESULT CCardioDuranteDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CCardioDuranteDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	UpdateData(FALSE);

	int nCurSel = 0;
	if (m_lIDProtocollo > 0)
	{
		for (int i = 0; i < m_ctrlCombo.GetCount(); i++)
		{
			if (m_ctrlCombo.GetItemData(i) == m_lIDProtocollo)
			{
				nCurSel = i;
				break;
			}
		}
	}

	m_ctrlCombo.SetCurSel(nCurSel);
	OnCbnSelchangeCombo();

	return 1;
}

LRESULT CCardioDuranteDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	m_bReadOnly = (BOOL)wParam;

	m_ctrlCombo.EnableWindow(!m_bReadOnly);
	m_ctrlList.SetReadOnly(m_bReadOnly);

	BOOL bEnable = FALSE;
	if (!m_bReadOnly)
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nCurSel = m_ctrlList.GetNextSelectedItem(pos);

			if (m_ctrlList.GetItemData(nCurSel) > 0)
				bEnable = TRUE;
		}
	}
	m_ctrlBtnAdd.EnableWindow(bEnable);
	m_ctrlBtnDel.EnableWindow(bEnable);

	return 1;
}

LRESULT CCardioDuranteDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	// ListControlDeleteAll();

	return 1;
}

LRESULT CCardioDuranteDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	// CEsamiSet().SetIDProtocolloUsato(m_pEsamiView->m_pEsamiSet->m_lContatore, m_lIDProtocollo);

	if (m_lIDProtocollo > 0)
	{
		for (int iRiga = 1; iRiga < m_ctrlList.GetItemCount(); iRiga++)
			for (int iColonna = 0; iColonna < m_lNumColonne; iColonna++)
				CProtocolloEsamiSet().AddEdtRow(m_pEsamiView->m_pEsamiSet->m_lContatore, m_lIDProtocollo, m_pArrayStructColonne[iColonna].lID, iRiga, m_ctrlList.GetItemText(iRiga, iColonna));

		CProtocolloEsamiSet().DelRows(m_pEsamiView->m_pEsamiSet->m_lContatore, m_lIDProtocollo, m_ctrlList.GetItemCount());
	}

	return UpdateData(TRUE);
}

LRESULT CCardioDuranteDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	return 1;
}

long CCardioDuranteDynForm::GetContenuto()
{
	return sub_cardio_durante;
}

BOOL CCardioDuranteDynForm::CampoObbligatorioValido()
{
	return FALSE;
}

void CCardioDuranteDynForm::ListControlRiempi()
{
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	m_nColonnaTempo = -1;
	m_nColonnaSommaTempo = -1;
	m_nColonnaMETS = -1;
	m_nColonnaTempoOriginale = -1;

	//

	while (m_lNumColonne > 0)
	{
		m_lNumColonne--;
		m_ctrlList.DeleteColumn(m_lNumColonne);
	}

	if (m_pArrayStructColonne != NULL)
	{
		delete m_pArrayStructColonne;
		m_pArrayStructColonne = NULL;
	}

	//

	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li", m_lIDProtocollo);

	CProtocolloColonneSet setPC;
	setPC.SetOpenFilter(sFilter);
	setPC.SetSortRecord("ORDINE");
	if (setPC.OpenRecordset("CCardioDuranteDynForm::ListControlPrepara"))
	{
		BOOL bColonnaTempoTrovata = FALSE;

		while (!setPC.IsEOF())
		{
			m_lNumColonne++;

			if (setPC.m_lTipo == 1)
				bColonnaTempoTrovata = TRUE;

			setPC.MoveNext();
		}

		if (m_lNumColonne > 0)
		{
			setPC.MoveFirst();

			if (bColonnaTempoTrovata)
				m_nColonnaTempoOriginale = m_lNumColonne;

			m_lNumColonne++;
			m_pArrayStructColonne = new STRUCT_COLONNE[m_lNumColonne];

			int nIndex = 0;
			while (!setPC.IsEOF())
			{
				m_ctrlList.InsertColumn(nIndex, setPC.m_sDescrizione, LVCFMT_LEFT, 0);

				m_pArrayStructColonne[nIndex].lID = setPC.m_lID;
				strcpy_s(m_pArrayStructColonne[nIndex].szDescrizione, setPC.m_sDescrizione);
				m_pArrayStructColonne[nIndex].lTipo = setPC.m_lTipo;
				m_pArrayStructColonne[nIndex].bValoreModificabile = setPC.m_bValoriModificabili;

				switch (setPC.m_lTipo)
				{
					case 1: // TEMPO //
					{
						if (m_nColonnaTempo < 0)
							m_nColonnaTempo = nIndex;

						break;
					}
					case 2: // SOMMATEMPO //
					{
						if (m_nColonnaSommaTempo < 0)
							m_nColonnaSommaTempo = nIndex;

						break;
					}
					case 3: // METS //
					{
						if (m_nColonnaMETS < 0)
							m_nColonnaMETS = nIndex;

						break;
					}
				}

				nIndex++;
				setPC.MoveNext();
			}

			m_ctrlList.InsertColumn(nIndex, "", LVCFMT_LEFT, 0);
			m_pArrayStructColonne[nIndex].lID = 0;
			strcpy_s(m_pArrayStructColonne[nIndex].szDescrizione, "");
			m_pArrayStructColonne[nIndex].lTipo = 0;
			m_pArrayStructColonne[nIndex].bValoreModificabile = FALSE;
		}

		for (int i = 0; i < m_lNumColonne - 1; i++)
			m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

		setPC.CloseRecordset("CCardioDuranteDynForm::ListControlPrepara");
	}

	//

	m_ctrlList.InsertItem(0, "");
	m_ctrlList.SetItemData(0, 0);

	for (int i = 0; i < m_lNumColonne - 1; i++)
	{
		m_ctrlList.SetItemText(0, i, m_pArrayStructColonne[i].szDescrizione);
		m_ctrlList.SetSubItemBkColor(0, i, RGB_SOLALETTURA);

		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}

	//

	if (CProtocolloEsamiSet().HasRows(m_pEsamiView->m_pEsamiSet->m_lContatore, m_lIDProtocollo))
	{
		// carico i dati già inseriti //
		ListControlCaricaDatiEsame();
	}
	else
	{
		// carico i valori di default //
		ListControlCaricaDefault();
	}

	//

	m_ctrlList.SetRedraw(TRUE);
}

void CCardioDuranteDynForm::ListControlCaricaDatiEsame()
{
	CString sFilter;
	sFilter.Format("IDESAME=%li AND IDPROTOCOLLO=%li", m_pEsamiView->m_pEsamiSet->m_lContatore, m_lIDProtocollo);

	CProtocolloEsamiSet setPE;
	setPE.SetOpenFilter(sFilter);
	setPE.SetSortRecord("ORDINE, IDCOLONNA");
	if (setPE.OpenRecordset("CCardioPrimaDynForm::ListControlCaricaDatiEsame"))
	{
		int nIndex = 0;
		long lLastOrder = -1;

		while (!setPE.IsEOF())
		{
			// se serve aggiungo una riga //

			if (setPE.m_lOrdine != lLastOrder)
			{
				nIndex++;

				m_ctrlList.InsertItem(nIndex, "");
				m_ctrlList.SetItemData(nIndex, setPE.m_lOrdine);

				for (int i = 0; i < m_lNumColonne; i++)
				{
					if (m_pArrayStructColonne[i].bValoreModificabile)
					{
						switch (m_pArrayStructColonne[i].lTipo)
						{
							case 1: // TEMPO //
							{
								m_ctrlList.SetSubItemEditTimeSec(nIndex, i);
								break;
							}
							case 2: // SOMMATEMPO //
							{
								break;
							}
							default:
							{
								m_ctrlList.SetSubItemEdit(nIndex, i, FALSE, 250);
								break;
							}
						}
					}
				}

				lLastOrder = setPE.m_lOrdine;
			}

			//

			for (int i = 0; i < m_lNumColonne; i++)
			{
				if (m_pArrayStructColonne[i].lID == setPE.m_lIDColonna)
				{
					m_ctrlList.SetItemText(nIndex, i, setPE.m_sValore);
					break;
				}
			}

			//

			setPE.MoveNext();
		}

		setPE.CloseRecordset("CCardioPrimaDynForm::ListControlCaricaDatiEsame");
	}

	//

	for (int i = 0; i < m_lNumColonne - 1; i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE);

	//

	for (int iSubItem = 0; iSubItem < m_lNumColonne; iSubItem++)
	{
		if (!m_pArrayStructColonne[iSubItem].bValoreModificabile || (m_pArrayStructColonne[iSubItem].lTipo == 2)) // 2 è SOMMATEMPO //
		{
			for (int iItem = 1; iItem < m_ctrlList.GetItemCount(); iItem++)
				m_ctrlList.SetSubItemBkColor(iItem, iSubItem, RGB_SOLALETTURA);
		}
		else
		{
			for (int iItem = 1; iItem < m_ctrlList.GetItemCount(); iItem++)
				m_ctrlList.SetSubItemBkColor(iItem, iSubItem, RGB_MODIFICABILE);
		}
	}
}

void CCardioDuranteDynForm::ListControlCaricaDefault()
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li", m_lIDProtocollo);

	CProtocolloValoriDefaultSet setPVD;
	setPVD.SetOpenFilter(sFilter);
	setPVD.SetSortRecord("ORDINE, IDCOLONNA");
	if (setPVD.OpenRecordset("CCardioPrimaDynForm::ListControlCaricaDefault"))
	{
		int nIndex = 0;
		long lLastOrder = -1;

		while (!setPVD.IsEOF())
		{
			// se serve aggiungo una riga //

			if (setPVD.m_lOrdine != lLastOrder)
			{
				nIndex++;

				m_ctrlList.InsertItem(nIndex, "");
				m_ctrlList.SetItemData(nIndex, setPVD.m_lOrdine);

				for (int i = 0; i < m_lNumColonne; i++)
				{
					if (m_pArrayStructColonne[i].bValoreModificabile)
					{
						switch (m_pArrayStructColonne[i].lTipo)
						{
							case 1: // TEMPO //
							{
								m_ctrlList.SetSubItemEditTimeSec(nIndex, i);
								break;
							}
							case 2: // SOMMATEMPO //
							{
								break;
							}
							default:
							{
								m_ctrlList.SetSubItemEdit(nIndex, i, FALSE, 250);
								break;
							}
						}
					}
				}

				lLastOrder = setPVD.m_lOrdine;
			}

			//

			for (int i = 0; i < m_lNumColonne; i++)
			{
				if (m_pArrayStructColonne[i].lID == setPVD.m_lIDColonna)
				{
					if (m_pArrayStructColonne[i].lTipo != 2) // SOMMATEMPO //
						m_ctrlList.SetItemText(nIndex, i, setPVD.m_sValore);
					break;
				}
			}

			//

			setPVD.MoveNext();
		}

		setPVD.CloseRecordset("CCardioPrimaDynForm::ListControlCaricaDefault");
	}

	//

	for (int i = 0; i < m_lNumColonne - 1; i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE);

	//

	for (int iSubItem = 0; iSubItem < m_lNumColonne; iSubItem++)
	{
		if (!m_pArrayStructColonne[iSubItem].bValoreModificabile || (m_pArrayStructColonne[iSubItem].lTipo == 2)) // 2 è SOMMATEMPO //
		{
			for (int iItem = 1; iItem < m_ctrlList.GetItemCount(); iItem++)
				m_ctrlList.SetSubItemBkColor(iItem, iSubItem, RGB_SOLALETTURA);
		}
		else
		{
			for (int iItem = 1; iItem < m_ctrlList.GetItemCount(); iItem++)
				m_ctrlList.SetSubItemBkColor(iItem, iSubItem, RGB_MODIFICABILE);
		}
	}

	//

	CalcolaTempi();

	//

	if (m_nColonnaTempoOriginale >= 0)
	{
		if (m_nColonnaTempo >= 0)
		{
			for (int i = 1; i < m_ctrlList.GetItemCount(); i++)
				m_ctrlList.SetItemText(i, m_nColonnaTempoOriginale, m_ctrlList.GetItemText(i, m_nColonnaTempo));
		}
	}
}

void CCardioDuranteDynForm::RiempiCombo()
{
	m_ctrlCombo.ResetContent();

	m_ctrlCombo.InsertString(0, "");
	m_ctrlCombo.SetItemData(0, 0);

	CString sFilter;
	sFilter.Format("FASE=%li", PROTOCOLLO_FASE_DURANTE);

	CProtocolloCardioSet setPC;
	setPC.SetOpenFilter(sFilter);
	if (setPC.OpenRecordset("CCardioDuranteDynForm::RiempiCombo"))
	{
		int nIndex = 1;
		while (!setPC.IsEOF())
		{
			m_ctrlCombo.InsertString(nIndex, setPC.m_sDescrizione);
			m_ctrlCombo.SetItemData(nIndex, setPC.m_lID);

			nIndex++;
			setPC.MoveNext();
		}

		setPC.CloseRecordset("CCardioDuranteDynForm::RiempiCombo");
	}
}

void CCardioDuranteDynForm::OnBnClickedBtnAdd()
{
	CNumeroNuoviStadiDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nItemToClone = m_ctrlList.GetNextSelectedItem(pos);

			for (int i = 0; i < dlg.GetNumero(); i++)
			{
				m_ctrlList.InsertItem(nItemToClone + 1, "");

				for (int j = 0; j < m_lNumColonne; j++)
				{
					if (!m_pArrayStructColonne[j].bValoreModificabile || (m_pArrayStructColonne[j].lTipo == 2)) // 2 è SOMMATEMPO //
					{
						m_ctrlList.SetSubItemBkColor(nItemToClone + 1, j, RGB_SOLALETTURA);
					}
					else
					{
						switch (m_pArrayStructColonne[i].lTipo)
						{
							case 1: // TEMPO //
							{
								m_ctrlList.SetSubItemEditTimeSec(nItemToClone + 1, j);
								break;
							}
							default:
							{
								m_ctrlList.SetSubItemEdit(nItemToClone + 1, j, FALSE, 250);
								break;
							}
						}
						m_ctrlList.SetSubItemBkColor(nItemToClone + 1, j, RGB_MODIFICABILE);
					}

					m_ctrlList.SetItemText(nItemToClone + 1, j, m_ctrlList.GetItemText(nItemToClone, j));
				}
				m_ctrlList.SetItemText(nItemToClone + 1, m_lNumColonne, m_ctrlList.GetItemText(nItemToClone, m_lNumColonne)); // copio anche ultima colonna nascosta (tempo originale) //
			}

			long lOrdine = m_ctrlList.GetItemData(nItemToClone);
			for (int k = nItemToClone + 1; k < m_ctrlList.GetItemCount(); k++)
			{
				m_ctrlList.SetItemData(k, lOrdine);
				lOrdine++;
			}
		}

		CalcolaTempi();
	}
}

void CCardioDuranteDynForm::OnBnClickedBtnDel()
{
	if (theApp.AfxMessageBoxEndo(IDS_ELIMINARIGAETUTTESUCCESSIVE, MB_YESNO) == IDYES)
	{
		POSITION posFirst = m_ctrlList.GetFirstSelectedItemPosition();
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nCurSel = m_ctrlList.GetNextSelectedItem(pos);
			while (m_ctrlList.GetItemCount() > nCurSel)
				m_ctrlList.DeleteItem(m_ctrlList.GetItemCount() - 1);
		}
	}
}

void CCardioDuranteDynForm::OnCbnSelchangeCombo()
{
	m_lIDProtocollo = 0;

	int nCurSel = m_ctrlCombo.GetCurSel();
	if (nCurSel > 0)
	{		
		m_ctrlCombo.GetLBText(nCurSel, m_sNomeProtocollo);
		m_lIDProtocollo = m_ctrlCombo.GetItemData(nCurSel);
	}
	//Julio 13/08/2018
	if (theApp.m_bPersonalizzazioniBrasileFleury)
	{
		if (m_sNomeProtocollo == "DIPI" || m_sNomeProtocollo == "CINTADENO" || m_sNomeProtocollo == "DOBUTA")
		{
			m_ctrlStaticTitle.SetWindowTextA("Fase de Infusão");
			if (m_ctrlCardioDopoForm != NULL)
				m_ctrlCardioDopoForm->SetTitle("Fase de Pós-Infusão");
		}
		else
		{
			m_ctrlStaticTitle.SetWindowTextA("Fase de Exercício");
			if (m_ctrlCardioDopoForm != NULL)
				m_ctrlCardioDopoForm->SetTitle("Fase de Recuperação");
		}
	}	
	//
	ListControlRiempi();
}

void CCardioDuranteDynForm::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	BOOL bEnable = FALSE;
	if (!m_bReadOnly)
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nCurSel = m_ctrlList.GetNextSelectedItem(pos);

			if (m_ctrlList.GetItemData(nCurSel) > 0)
				bEnable = TRUE;
		}
	}
	m_ctrlBtnAdd.EnableWindow(bEnable);
	m_ctrlBtnDel.EnableWindow(bEnable);

	*pResult = 0;
}

short CCardioDuranteDynForm::GetColNumber()
{
	return (short)m_lNumColonne - 1;
}

short CCardioDuranteDynForm::GetRowNumber()
{
	return (short)m_ctrlList.GetItemCount();
}

CString CCardioDuranteDynForm::GetTableCellText(short shCol, short shRow)
{
	CString sReturn = "";

	if ((shCol < GetColNumber()) && (shRow < GetRowNumber()))
		sReturn = m_ctrlList.GetItemText(shRow, shCol);

	return sReturn;
}

CString CCardioDuranteDynForm::GetTitle()
{
	CString sReturn = "";

	m_ctrlStaticTitle.GetWindowTextA(sReturn);
	sReturn.Trim();
	if (!sReturn.IsEmpty())
		sReturn = "\r\n" + sReturn + "\r\n";

	return sReturn;
}
CString CCardioDuranteDynForm::GetNomeProtocollo()
{
	return m_sNomeProtocollo;
}

LRESULT CCardioDuranteDynForm::OnListSubitemChanged(WPARAM wParam, LPARAM lParam)
{
	if ((wParam >= 0) && (lParam >= 0))
	{
		if (lParam == m_nColonnaTempo)
		{
			CalcolaTempi();

			if ((m_nColonnaMETS >= 0) && (m_nColonnaTempoOriginale >= 0))
			{
				if (m_ctrlList.GetItemText(wParam, m_nColonnaTempo) < m_ctrlList.GetItemText(wParam, m_nColonnaTempoOriginale))
					m_ctrlList.SetItemText(wParam, m_nColonnaMETS, "");
			}
		}
	}

	return 0;
}

void CCardioDuranteDynForm::CalcolaTempi()
{
	if ((m_nColonnaTempo >= 0) && (m_nColonnaSommaTempo >= 0))
	{
		long lSommaSecondi = 0;

		for (int i = 1; i < m_ctrlList.GetItemCount(); i++)
		{
			CString sTemp = m_ctrlList.GetItemText(i, m_nColonnaTempo);

			if (isdigit(sTemp[0]) &&
				isdigit(sTemp[1]) &&
				(sTemp[2] == ' ' || sTemp[2] == '.' || sTemp[2] == ':') &&
				isdigit(sTemp[3]) &&
				isdigit(sTemp[4]) &&
				(sTemp[5] == ' ' || sTemp[5] == '.' || sTemp[5] == ':') &&
				isdigit(sTemp[6]) &&
				isdigit(sTemp[7]))
			{
				CString sH = sTemp.Mid(0, 2);
				CString sM = sTemp.Mid(3, 2);
				CString sS = sTemp.Mid(6, 2);

				long lSeconds = (atol(sH) * 60 * 60) + (atol(sM) * 60) + atol(sS);
				lSommaSecondi += lSeconds;

				long lSH = (lSommaSecondi / 60) / 60;
				long lSM = (lSommaSecondi / 60) % 60;
				long lSS = lSommaSecondi % 60;

				CString sTeeemp;
				sTeeemp.Format("%02li:%02li:%02li", lSH, lSM, lSS);
				m_ctrlList.SetItemText(i, m_nColonnaSommaTempo, sTeeemp);
			}
			else
			{
				m_ctrlList.SetItemText(i, m_nColonnaTempo, "00:00:00");
			}
		}
	}
}
