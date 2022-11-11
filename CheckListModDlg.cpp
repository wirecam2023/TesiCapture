#include "stdafx.h"
#include "Endox.h"
#include "CheckListModDlg.h"

#include "CheckListElModDlg.h"
#include "CheckListEsamiSet.h"
#include "CheckListItemRegoleSet.h"
#include "CheckListItemSet.h"
#include "CheckListSet.h"
#include "CodiciClassificazioneDiagnosticaSet.h"
#include "EditCodiceDescrizioneDlg.h"
#include "EsamiView.h"
#include "TipoEsameNew.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COL_COD 0
#define COL_DESC 1

IMPLEMENT_DYNAMIC(CCheckListModDlg, CDialog)

CCheckListModDlg::CCheckListModDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CCheckListModDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	m_pEsamiView = pEsamiView;

	m_bCloning = FALSE;
	m_lCloningID = 0;

	m_lIDCheckList = 0;
	m_lIDCheckListItem = 0;
	m_lIDCheckListItemPadre = 0;
	m_lIDCheckListItemSiblingPrev = 0;
	m_lIDCheckListItemSiblingNext = 0;

	m_lIDItemCopiato = 0;
}

CCheckListModDlg::~CCheckListModDlg()
{
}

BEGIN_MESSAGE_MAP(CCheckListModDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_CLONE, OnBnClickedBtnClone)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)
	ON_BN_CLICKED(IDC_BTN_NEW_EXAM, OnBnClickedBtnNewExam)
	ON_BN_CLICKED(IDC_BTN_DEL_EXAM, OnBnClickedBtnDelExam)
	ON_BN_CLICKED(IDC_BTN_NEW_EL1, OnBnClickedBtnNewEl1)
	ON_BN_CLICKED(IDC_BTN_NEW_EL2, OnBnClickedBtnNewEl2)
	ON_BN_CLICKED(IDC_BTN_NEW_EL3, OnBnClickedBtnNewEl3)
	ON_BN_CLICKED(IDC_BTN_EDT_EL, OnBnClickedBtnEdtEl)
	ON_BN_CLICKED(IDC_BTN_DEL_EL, OnBnClickedBtnDelEl)
	ON_BN_CLICKED(IDC_BTN_UP, OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DN, OnBnClickedBtnDn)
	ON_BN_CLICKED(IDC_BTN_COPY, OnBnClickedBtnCopy)
	ON_BN_CLICKED(IDC_BTN_PASTE, OnBnClickedBtnPaste)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EXAM, OnLvnItemchangedListExam)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnTvnSelchangedTree)

END_MESSAGE_MAP()

void CCheckListModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK_1, m_ctrlCheck1);
	DDX_Control(pDX, IDC_CHECK_2, m_ctrlCheck2);

	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlBtnNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);
	DDX_Control(pDX, IDC_BTN_CLONE, m_ctrlBtnClone);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlBtnSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlBtnUndo);
	DDX_Control(pDX, IDC_BTN_NEW_EXAM, m_ctrlBtnNewExam);
	DDX_Control(pDX, IDC_BTN_DEL_EXAM, m_ctrlBtnDelExam);
	DDX_Control(pDX, IDC_BTN_NEW_EL1, m_ctrlBtnNewEl1);
	DDX_Control(pDX, IDC_BTN_NEW_EL2, m_ctrlBtnNewEl2);
	DDX_Control(pDX, IDC_BTN_NEW_EL3, m_ctrlBtnNewEl3);
	DDX_Control(pDX, IDC_BTN_EDT_EL, m_ctrlBtnEdtEl);
	DDX_Control(pDX, IDC_BTN_DEL_EL, m_ctrlBtnDelEl);
	DDX_Control(pDX, IDC_BTN_UP, m_ctrlBtnUp);
	DDX_Control(pDX, IDC_BTN_DN, m_ctrlBtnDn);
	DDX_Control(pDX, IDC_BTN_COPY, m_ctrlBtnCopy);
	DDX_Control(pDX, IDC_BTN_PASTE, m_ctrlBtnPaste);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_COMBO, m_ctrlCombo);
	DDX_Control(pDX, IDC_COMBO_CAMPO, m_ctrlComboCampo);
	DDX_Control(pDX, IDC_COMBO_ORDINE, m_ctrlComboOrdine);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_LIST_EXAM, m_ctrlListExam);

	DDX_Control(pDX, IDC_EDIT_COD, m_ctrlEditCod);
	DDX_Control(pDX, IDC_EDIT_DESC, m_ctrlEditDesc);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_06, m_ctrlStatic06);
	DDX_Control(pDX, IDC_STATIC_07, m_ctrlStatic07);
	DDX_Control(pDX, IDC_STATIC_08, m_ctrlStatic08);

	DDX_Control(pDX, IDC_TREE, m_ctrlTree);
}

void CCheckListModDlg::OnCancel()
{
}

BOOL CCheckListModDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	m_ctrlStatic01.SetFont(&theApp.m_fontBold);
	m_ctrlStatic02.SetFont(&theApp.m_fontBold);
	m_ctrlStatic03.SetFont(&theApp.m_fontBold);
	m_ctrlStatic04.SetFont(&theApp.m_fontBold);
	m_ctrlStatic05.SetFont(&theApp.m_fontBold);
	m_ctrlStatic06.SetFont(&theApp.m_fontBold);
	m_ctrlStatic07.SetFont(&theApp.m_fontBold);
	m_ctrlStatic08.SetFont(&theApp.m_fontBold);

	SetReadOnly(TRUE);

	m_ctrlCombo.InsertString(0, theApp.GetMessageString(IDS_CHECKLIST_ESPANSA));
	m_ctrlCombo.InsertString(1, theApp.GetMessageString(IDS_CHECKLIST_COMPRESSA));
	m_ctrlCombo.SetCurSel(0);

	int nIndex = 1;
	m_ctrlComboCampo.InsertString(0, "");
	m_ctrlComboCampo.SetItemData(0, -1);
	for(int i = 0; i < NUM_LABEL_TESTO_CL; i++)
	{
		if (!theApp.m_sLabelTextCL[i].IsEmpty())
		{
			m_ctrlComboCampo.InsertString(nIndex, theApp.m_sLabelTextCL[i]);
			m_ctrlComboCampo.SetItemData(nIndex, i);
			nIndex++;
		}
	}
	if (theApp.m_bRefertazioneUsaChecklist)
	{
		m_ctrlComboCampo.InsertString(nIndex, theApp.GetMessageString(IDS_REFERTO));
		m_ctrlComboCampo.SetItemData(nIndex, 999);
		nIndex++;
	}
	m_ctrlComboCampo.SetCurSel(0);
	m_ctrlComboOrdine.SetCurSel(0);

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(COL_COD, "Codice");
	m_ctrlList.InsertColumn(COL_DESC, "Descrizione");
	RiempiLista();

	m_ctrlListExam.SetExtendedStyle(m_ctrlListExam.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListExam.InsertColumn(COL_COD, "Codice");
	m_ctrlListExam.InsertColumn(COL_DESC, "Descrizione");
	m_ctrlListExam.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListExam.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	theApp.LocalizeDialog(this, CCheckListModDlg::IDD, "CheckListModDlg");
	return bReturn;
}

void CCheckListModDlg::OnOK()
{
	if (m_ctrlBtnOK.IsWindowEnabled())
		CDialog::OnOK();
}

void CCheckListModDlg::OnBnClickedBtnNew()
{
	// Sandro 12/07/2016 // questo dà problemi quando più utenti creano nuove checklist in contemporanea! //
	// DeselezionaTutti();
	// SetReadOnly(FALSE);

	// chiedo codice e descrizione della nuova checklist //
	CEditCodiceDescrizioneDlg dlg(this, IDS_NUOVA_CHECKLIST, "", "");
	if (dlg.DoModal() == IDOK)
	{
		CCheckListSet setCheck;
		if (setCheck.OpenRecordset("CCheckListModDlg::OnBnClickedBtnNew"))
		{
			// salvo nel db la nuova checklist //
			if (setCheck.AddNewRecordset("CCheckListModDlg::OnBnClickedBtnNew"))
			{
				setCheck.m_sCodice = dlg.GetCodice();
				setCheck.m_sDescrizione = dlg.GetDescrizione();
				if (setCheck.UpdateRecordset("CCheckListModDlg::OnBnClickedBtnNew"))
				{
					// aggiorno la lista //

					SetReadOnly(TRUE);
					RiempiLista();
					m_lIDCheckList = setCheck.GetLastAdd();

					// seleziono la nuova checklist appena inserita //
					if (m_lIDCheckList > 0)
					{
						for (int i = 0; i < m_ctrlList.GetItemCount(); i++)
						{
							if ((long)m_ctrlList.GetItemData(i) == m_lIDCheckList)
							{
								m_ctrlList.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);

								// rimetto in "edit" il dialog //
								SetReadOnly(FALSE);

								break;
							}
						}
					}
				}
			}

			setCheck.CloseRecordset("CCheckListModDlg::OnBnClickedBtnNew");
		}
	}
}

void CCheckListModDlg::OnBnClickedBtnEdt()
{
	SetReadOnly(FALSE);
}

void CCheckListModDlg::OnBnClickedBtnDel()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CHECKLIST_MOD_DEL1), MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		if (m_ctrlTree.GetCount() > 0)
			if (theApp.MessageBoxEndo(theApp.GetMessageString(IDS_CHECKLIST_MOD_DEL2), theApp.GetMessageString(IDS_ACHTUNG), MB_ICONSTOP| MB_YESNO) == IDNO)
				return;

		CString strFilter;
		strFilter.Format("ID=%li", m_lIDCheckList);
		
		CCheckListSet setDel;
		setDel.SetOpenFilter(strFilter);
		if (setDel.OpenRecordset("CCheckListModDlg::OnBnClickedBtnDel"))
		{
			if (!setDel.IsEOF())
			{
				if (setDel.DeleteRecordset("CCheckListModDlg::OnBnClickedBtnDel"))
					RiempiLista();
			}

			setDel.CloseRecordset("CCheckListModDlg::OnBnClickedBtnDel");
		}
	}
}

void CCheckListModDlg::OnBnClickedBtnClone()
{
	m_bCloning = TRUE;
	m_lCloningID = m_lIDCheckList;

	// faccio finta che sia un nuovo inserimento ma senza resettare tutto //
	m_lIDCheckList = 0;
	m_ctrlEditCod.SetWindowText("");
	m_ctrlEditDesc.SetWindowText("");

	SetReadOnly(FALSE);
}

void CCheckListModDlg::OnBnClickedBtnSave()
{
	// controllo il codice //
	CString strCod;
	m_ctrlEditCod.GetWindowText(strCod);
	strCod.Trim();
	if (strCod.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CHECKLIST_ERR_COD));
		return;
	}

	// controllo la descrizione //
	CString strDesc;
	m_ctrlEditDesc.GetWindowText(strDesc);
	strDesc.Trim();
	if (strDesc.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CHECKLIST_ERR_DESC));
		return;
	}

	// se codice e descrizione sono apposto procedo //
	if (m_lIDCheckList == 0)
	{
		CCheckListSet setCheck;
		if (setCheck.OpenRecordset("CCheckListModDlg::OnBnClickedBtnSave"))
		{
			if (setCheck.AddNewRecordset("CCheckListModDlg::OnBnClickedBtnSave"))
			{
				setCheck.m_sCodice = strCod;
				setCheck.m_sDescrizione = strDesc;
				setCheck.m_lPresentazione = m_ctrlCombo.GetCurSel();
				setCheck.m_bItemAlmenoUno = (m_ctrlCheck1.GetCheck() == BST_CHECKED);
				setCheck.m_bItemPiuDiUno = (m_ctrlCheck2.GetCheck() == BST_CHECKED);
				setCheck.m_lCampoCL = m_ctrlComboCampo.GetItemData(m_ctrlComboCampo.GetCurSel());
				setCheck.m_lOrdine = m_ctrlComboOrdine.GetCurSel();

				if (setCheck.UpdateRecordset("CCheckListModDlg::OnBnClickedBtnSave"))
				{
					m_lIDCheckList = setCheck.GetLastAdd();
					SalvaEsami();
					SalvaAlbero();
				}
			}

			setCheck.CloseRecordset("CCheckListModDlg::OnBnClickedBtnSave");
		}
	}
	else
	{
		CString strFilter;
		strFilter.Format("ID=%li", m_lIDCheckList);

		CCheckListSet setCheck;
		setCheck.SetOpenFilter(strFilter);
		if (setCheck.OpenRecordset("CCheckListModDlg::OnBnClickedBtnSave"))
		{
			if (!setCheck.IsEOF())
			{
				if (setCheck.EditRecordset("CCheckListModDlg::OnBnClickedBtnSave"))
				{
					setCheck.m_sCodice = strCod;
					setCheck.m_sDescrizione = strDesc;
					setCheck.m_lPresentazione = m_ctrlCombo.GetCurSel();
					setCheck.m_bItemAlmenoUno = (m_ctrlCheck1.GetCheck() == BST_CHECKED);
					setCheck.m_bItemPiuDiUno = (m_ctrlCheck2.GetCheck() == BST_CHECKED);
					setCheck.m_lCampoCL = m_ctrlComboCampo.GetItemData(m_ctrlComboCampo.GetCurSel());
					setCheck.m_lOrdine = m_ctrlComboOrdine.GetCurSel();

					if (setCheck.UpdateRecordset("CCheckListModDlg::OnBnClickedBtnSave"))
					{
						SalvaEsami();
						SalvaAlbero();
					}
				}
			}

			setCheck.CloseRecordset("CCheckListModDlg::OnBnClickedBtnSave");
		}
	}

	//
	m_bCloning = FALSE;
	m_lCloningID = 0;

	//
	long lID = m_lIDCheckList;
	SetReadOnly(TRUE);
	RiempiLista();
	m_lIDCheckList = lID;

	if (m_lIDCheckList > 0)
	{
		for(int i = 0; i < m_ctrlList.GetItemCount(); i++)
		{
			if ((long)m_ctrlList.GetItemData(i) == m_lIDCheckList)
			{
				m_ctrlList.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
				break;
			}
		}
	}
}

void CCheckListModDlg::OnBnClickedBtnUndo()
{
	m_bCloning = FALSE;
	m_lCloningID = 0;

	SetReadOnly(TRUE);
	OnLvnItemchangedList(NULL, NULL);
}

void CCheckListModDlg::OnBnClickedBtnNewExam()
{
	CTipoEsameNewDlg dlg(this, m_pEsamiView, FALSE, TRUE, 0);
	if (dlg.DoModal() == IDOK)
	{
		long lTipoEsame = dlg.GetTipoEsame();

		BOOL bFound = FALSE;
		for(int i = 0; i < m_ctrlListExam.GetItemCount(); i++)
		{
			if (m_ctrlListExam.GetItemData(i) == lTipoEsame)
			{
				bFound = TRUE;
				break;
			}
		}

		if (!bFound)
		{
			int nItem = m_ctrlListExam.GetItemCount();

			m_ctrlListExam.InsertItem(nItem, CTipoEsameSet().GetSigla(lTipoEsame));
			m_ctrlListExam.SetItemData(nItem, (DWORD)lTipoEsame);

			m_ctrlListExam.SetItemText(nItem, COL_DESC, CTipoEsameSet().GetDescrizione(lTipoEsame));
		}
	}
}

void CCheckListModDlg::OnBnClickedBtnDelExam()
{
	POSITION pos = m_ctrlListExam.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nItem = m_ctrlListExam.GetNextSelectedItem(pos);
		long lIDExamToDelete = m_ctrlListExam.GetItemData(nItem);

		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CHECKLIST_MOD_DEL5), MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			m_ctrlListExam.DeleteItem(nItem);
			m_listExamToDelete.AddTail(lIDExamToDelete);
		}
	}
}

void CCheckListModDlg::OnBnClickedBtnNewEl1()
{
	CCheckListElModDlg dlg(this, m_lIDCheckList, 0, &m_ctrlTree);
	if (dlg.DoModal() == IDOK)
		RiempiAlbero(0);
}

void CCheckListModDlg::OnBnClickedBtnNewEl2()
{
	CCheckListElModDlg dlg(this, m_lIDCheckList, m_lIDCheckListItemPadre, &m_ctrlTree);
	if (dlg.DoModal() == IDOK)
		RiempiAlbero(0);
}

void CCheckListModDlg::OnBnClickedBtnNewEl3()
{
	CCheckListElModDlg dlg(this, m_lIDCheckList, m_lIDCheckListItem, &m_ctrlTree);
	if (dlg.DoModal() == IDOK)
		RiempiAlbero(0);
}

void CCheckListModDlg::OnBnClickedBtnEdtEl()
{
	CCheckListElModDlg dlg(this, m_lIDCheckListItem, &m_ctrlTree);
	if (dlg.DoModal() == IDOK)
		RiempiAlbero(m_lIDCheckListItem);
}

void CCheckListModDlg::OnBnClickedBtnDelEl()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CHECKLIST_MOD_DEL3), MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		HTREEITEM hTree = m_ctrlTree.GetSelectedItem();

		if (hTree != NULL)
		{
			HTREEITEM hTreeFiglio = m_ctrlTree.GetChildItem(hTree);
			if (hTreeFiglio != NULL)
			{
				if (theApp.MessageBoxEndo(theApp.GetMessageString(IDS_CHECKLIST_MOD_DEL4), theApp.GetMessageString(IDS_ACHTUNG), MB_ICONSTOP| MB_YESNO) == IDNO)
					return;
			}
		}

		CString strFilter;
		strFilter.Format("ID=%li", m_lIDCheckListItem);
		
		CCheckListItemSet setDel;
		setDel.SetOpenFilter(strFilter);
		if (setDel.OpenRecordset("CCheckListModDlg::OnBnClickedBtnDelEl"))
		{
			if (!setDel.IsEOF())
			{
				if (setDel.DeleteRecordset("CCheckListModDlg::OnBnClickedBtnDelEl"))
					RiempiAlbero(0);
			}

			setDel.CloseRecordset("CCheckListModDlg::OnBnClickedBtnDelEl");
		}
	}
}

void CCheckListModDlg::OnBnClickedBtnUp()
{
	if ((m_lIDCheckListItem > 0) && (m_lIDCheckListItemSiblingPrev > 0))
	{
		// scambio l'item con il suo sibling precedente //

		CString strFilter;
		CCheckListItemSet setTemp;

		// punto il materiale corrente e gli decremento l'ordine //
		strFilter.Format("ID=%li", m_lIDCheckListItem);
		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CCheckListModDlg::OnBnClickedBtnUp"))
		{
			if (!setTemp.IsEOF())
			{
				if (setTemp.EditRecordset("CCheckListModDlg::OnBnClickedBtnUp"))
				{
					setTemp.m_lOrdine--;
					setTemp.UpdateRecordset("CCheckListModDlg::OnBnClickedBtnUp");
				}
			}
			setTemp.CloseRecordset("CCheckListModDlg::OnBnClickedBtnUp");
		}

		// punto il materiale precedente e gli incremento l'ordine //
		strFilter.Format("ID=%li", m_lIDCheckListItemSiblingPrev);
		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CCheckListModDlg::OnBnClickedBtnUp"))
		{
			if (!setTemp.IsEOF())
			{
				if (setTemp.EditRecordset("CCheckListModDlg::OnBnClickedBtnUp"))
				{
					setTemp.m_lOrdine++;
					setTemp.UpdateRecordset("CCheckListModDlg::OnBnClickedBtnUp");
				}
			}
			setTemp.CloseRecordset("CCheckListModDlg::OnBnClickedBtnUp");
		}

		//
		RiempiAlbero(m_lIDCheckListItem);
	}
}

void CCheckListModDlg::OnBnClickedBtnDn()
{
	if ((m_lIDCheckListItem > 0) && (m_lIDCheckListItemSiblingNext > 0))
	{
		// scambio l'item con il suo sibling successivo //

		CString strFilter;
		CCheckListItemSet setTemp;

		// punto il materiale corrente e gli incremento l'ordine //
		strFilter.Format("ID=%li", m_lIDCheckListItem);
		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CCheckListModDlg::OnBnClickedBtnDn"))
		{
			if (!setTemp.IsEOF())
			{
				if (setTemp.EditRecordset("CCheckListModDlg::OnBnClickedBtnDn"))
				{
					setTemp.m_lOrdine++;
					setTemp.UpdateRecordset("CCheckListModDlg::OnBnClickedBtnDn");
				}
			}
			setTemp.CloseRecordset("CCheckListModDlg::OnBnClickedBtnDn");
		}

		// punto il materiale precedente e gli decremento l'ordine //
		strFilter.Format("ID=%li", m_lIDCheckListItemSiblingNext);
		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CCheckListModDlg::OnBnClickedBtnDn"))
		{
			if (!setTemp.IsEOF())
			{
				if (setTemp.EditRecordset("CCheckListModDlg::OnBnClickedBtnDn"))
				{
					setTemp.m_lOrdine--;
					setTemp.UpdateRecordset("CCheckListModDlg::OnBnClickedBtnDn");
				}
			}
			setTemp.CloseRecordset("CCheckListModDlg::OnBnClickedBtnDn");
		}

		//
		RiempiAlbero(m_lIDCheckListItem);
	}
}

void CCheckListModDlg::OnBnClickedBtnCopy()
{
	m_lIDItemCopiato = m_lIDCheckListItem;
	m_ctrlBtnPaste.EnableWindow(FALSE);
}

void CCheckListModDlg::OnBnClickedBtnPaste()
{
	BeginWaitCursor();

	if ((m_lIDCheckListItem > 0) && (m_lIDItemCopiato > 0))
	{
		CList<STRUCT_COPPIA_LONG> listIDs;

		CString sFilter;
		sFilter.Format("ID=%li", m_lIDItemCopiato);

		CCheckListItemSet setOrig;
		setOrig.SetOpenFilter(sFilter);
		if (setOrig.OpenRecordset("CCheckListModDlg::OnBnClickedBtnPaste"))
		{
			if (!setOrig.IsEOF())
			{
				CCheckListItemSet setDest;
				setDest.SetOpenFilter("ID=0");
				if (setDest.OpenRecordset("CCheckListModDlg::OnBnClickedBtnPaste"))
				{
					if (setDest.AddNewRecordset("CCheckListModDlg::OnBnClickedBtnPaste"))
					{
						setDest.m_lIDCheckList = m_lIDCheckList;
						setDest.m_lIDPadre = m_lIDCheckListItem;
						// setDest.m_lOrdine = ;
						setDest.m_sTitolo = setOrig.m_sTitolo;
						setDest.m_sTestoRTF = setOrig.m_sTestoRTF;
						setDest.m_sTestoTXT = setOrig.m_sTestoTXT;
						setDest.m_lTestoNumeroVariabili = setOrig.m_lTestoNumeroVariabili;
						setDest.m_bItemAlmenoUno = setOrig.m_bItemAlmenoUno;
						setDest.m_bItemPiuDiUno = setOrig.m_bItemPiuDiUno;
						setDest.m_lClassificazioneDiagnosi = setOrig.m_lClassificazioneDiagnosi;

						if (setDest.UpdateRecordset("CCheckListModDlg::OnBnClickedBtnPaste"))
						{
							STRUCT_COPPIA_LONG structTemp;
							structTemp.lIDOrig = setOrig.m_lID;
							structTemp.lIDDest = setDest.GetLastAdd();
							listIDs.AddTail(structTemp);

							SalvaAlberoSub(m_lIDItemCopiato, setDest.GetLastAdd(), &listIDs);
						}
					}

					setDest.CloseRecordset("CCheckListModDlg::OnBnClickedBtnPaste");
				}
			}

			setOrig.CloseRecordset("CCheckListModDlg::OnBnClickedBtnPaste");
		}

		// Sandro 05/10/2016 // copio anche le regole //

		POSITION posOrig = listIDs.GetHeadPosition();
		while (posOrig != NULL)
		{
			STRUCT_COPPIA_LONG structTempOrig = listIDs.GetAt(posOrig);

			sFilter.Format("IDCHECKLISTITEM=%li", structTempOrig.lIDOrig);

			CCheckListItemRegoleSet setRegOrig;
			setRegOrig.SetOpenFilter(sFilter);
			if (setRegOrig.OpenRecordset("CCheckListModDlg::SalvaAlbero"))
			{
				while (!setRegOrig.IsEOF())
				{
					long lIDDestBind = 0;

					POSITION posOrigBind = listIDs.GetHeadPosition();
					while (posOrigBind != NULL)
					{
						STRUCT_COPPIA_LONG structTempBind = listIDs.GetAt(posOrigBind);

						if (structTempBind.lIDOrig == setRegOrig.m_lIDCheckListItemBind)
						{
							lIDDestBind = structTempBind.lIDDest;
							break;
						}

						listIDs.GetNext(posOrigBind);
					}

					if (lIDDestBind > 0)
						CCheckListItemRegoleSet().AddRow(structTempOrig.lIDDest, lIDDestBind, setRegOrig.m_lTipoRegola);

					setRegOrig.MoveNext();
				}

				setRegOrig.CloseRecordset("CCheckListModDlg::SalvaAlbero");
			}

			listIDs.GetNext(posOrig);
		}

		//

		RiempiAlbero(m_lIDCheckListItem);
	}

	EndWaitCursor();
}

void CCheckListModDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();

	if (pos == NULL)
	{
		m_ctrlBtnEdt.EnableWindow(FALSE);
		m_ctrlBtnDel.EnableWindow(FALSE);
		m_ctrlBtnClone.EnableWindow(FALSE);

		m_lIDCheckList = 0;
	}
	else
	{
		int nCurSel = m_ctrlList.GetNextSelectedItem(pos);

		m_ctrlBtnEdt.EnableWindow(TRUE);
		m_ctrlBtnDel.EnableWindow(TRUE);
		m_ctrlBtnClone.EnableWindow(TRUE);

		m_lIDCheckList = (long)m_ctrlList.GetItemData(nCurSel);
	}

	CaricaDati();
}

void CCheckListModDlg::OnLvnItemchangedListExam(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_ctrlBtnDelExam.EnableWindow(m_ctrlListExam.GetFirstSelectedItemPosition() != NULL);
}

void CCheckListModDlg::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hTree = m_ctrlTree.GetSelectedItem();

	if (hTree == NULL)
	{
		m_ctrlBtnNewEl2.EnableWindow(FALSE);
		m_ctrlBtnNewEl3.EnableWindow(FALSE);
		m_ctrlBtnEdtEl.EnableWindow(FALSE);
		m_ctrlBtnDelEl.EnableWindow(FALSE);
		m_ctrlBtnUp.EnableWindow(FALSE);
		m_ctrlBtnDn.EnableWindow(FALSE);
		m_ctrlBtnCopy.EnableWindow(FALSE);
		m_ctrlBtnPaste.EnableWindow(FALSE);

		// --- //

		m_lIDCheckListItem = 0;
		m_lIDCheckListItemPadre = 0;
		m_lIDCheckListItemSiblingPrev = 0;
		m_lIDCheckListItemSiblingNext = 0;
	}
	else
	{
		HTREEITEM hTreeSiblingPrev = m_ctrlTree.GetPrevSiblingItem(hTree);
		HTREEITEM hTreeSiblingNext = m_ctrlTree.GetNextSiblingItem(hTree);

		m_ctrlBtnNewEl2.EnableWindow(TRUE);
		m_ctrlBtnNewEl3.EnableWindow(TRUE);
		m_ctrlBtnEdtEl.EnableWindow(TRUE);
		m_ctrlBtnDelEl.EnableWindow(TRUE);
		m_ctrlBtnUp.EnableWindow(hTreeSiblingPrev != NULL);
		m_ctrlBtnDn.EnableWindow(hTreeSiblingNext != NULL);
		m_ctrlBtnCopy.EnableWindow(TRUE);

		// non posso incollare un elemento in un suo proprio figlio altrimenti mi si inlooppa tutto //

		BOOL bEnablePaste = (m_lIDItemCopiato > 0);

		if (bEnablePaste)
		{
			HTREEITEM hTemp = hTree;

			do
			{
				if ((long)m_ctrlTree.GetItemData(hTemp) == m_lIDItemCopiato)
				{
					bEnablePaste = FALSE;
					break;
				}
				hTemp = m_ctrlTree.GetParentItem(hTemp);
			} while(hTemp != NULL);
		}

		m_ctrlBtnPaste.EnableWindow(bEnablePaste);

		// --- //

		m_lIDCheckListItem = (long)m_ctrlTree.GetItemData(hTree);
		m_lIDCheckListItemPadre = 0;
		m_lIDCheckListItemSiblingPrev = 0;
		m_lIDCheckListItemSiblingNext = 0;

		HTREEITEM hTreePadre = m_ctrlTree.GetParentItem(hTree);
		if (hTreePadre != NULL)
			m_lIDCheckListItemPadre = (long)m_ctrlTree.GetItemData(hTreePadre);

		if (hTreeSiblingPrev != NULL)
			m_lIDCheckListItemSiblingPrev = (long)m_ctrlTree.GetItemData(hTreeSiblingPrev);
		if (hTreeSiblingNext != NULL)
			m_lIDCheckListItemSiblingNext = (long)m_ctrlTree.GetItemData(hTreeSiblingNext);
	}
}

void CCheckListModDlg::CaricaDati()
{
	if (m_lIDCheckList == 0)
	{
		m_ctrlEditCod.SetWindowText("");
		m_ctrlEditDesc.SetWindowText("");
		m_ctrlCombo.SetCurSel(0);
		m_ctrlCheck1.SetCheck(BST_UNCHECKED);
		m_ctrlCheck2.SetCheck(BST_UNCHECKED);
		m_ctrlComboCampo.SetCurSel(0);
		m_ctrlComboOrdine.SetCurSel(0);
		m_ctrlListExam.DeleteAllItems();
		m_ctrlListExam.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListExam.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		m_listExamToDelete.RemoveAll();

		m_ctrlTree.DeleteAllItems();
		OnTvnSelchangedTree(NULL, NULL);
	}
	else
	{
		CString strFilter;
		strFilter.Format("ID=%li", m_lIDCheckList);

		CCheckListSet setCheck;
		setCheck.SetOpenFilter(strFilter);
		if (setCheck.OpenRecordset("CCheckListModDlg::CaricaDati"))
		{
			if (!setCheck.IsEOF())
			{
				m_ctrlEditCod.SetWindowText(setCheck.m_sCodice);
				m_ctrlEditDesc.SetWindowText(setCheck.m_sDescrizione);
				m_ctrlCombo.SetCurSel(setCheck.m_lPresentazione);
				m_ctrlCheck1.SetCheck(setCheck.m_bItemAlmenoUno ? BST_CHECKED : BST_UNCHECKED);
				m_ctrlCheck2.SetCheck(setCheck.m_bItemPiuDiUno ? BST_CHECKED : BST_UNCHECKED);

				int nSelect = 0;
				for(int i = 0; i < m_ctrlComboCampo.GetCount(); i++)
				{
					if (m_ctrlComboCampo.GetItemData(i) == setCheck.m_lCampoCL)
					{
						nSelect = i;
						break;
					}
				}
				m_ctrlComboCampo.SetCurSel(nSelect);

				m_ctrlComboOrdine.SetCurSel(setCheck.m_lOrdine);
			}

			setCheck.CloseRecordset("CCheckListModDlg::CaricaDati");
		}

		RiempiListaExam();

		RiempiAlbero(0);
	}
}

void CCheckListModDlg::DeselezionaTutti()
{
	for(int i = 0; i < m_ctrlList.GetItemCount(); i++)
		m_ctrlList.SetItemState(i, 0, LVIS_SELECTED);

	m_lIDCheckList = 0;
}

void CCheckListModDlg::RiempiAlbero(long lIDItemToSelect)
{
	HTREEITEM hTreeItemToSelect = NULL;

	BeginWaitCursor();
	m_ctrlTree.SetRedraw(FALSE);

	m_ctrlTree.DeleteAllItems();
	m_listChecklistItem.RemoveAll();
	OnTvnSelchangedTree(NULL, NULL);

	// Sandro 13/06/2016 // per velocizzare caricamento butto tutta la checklist in memoria //

	CString strFilter;
	strFilter.Format("IDCheckList=%li AND IDPadre IS NOT NULL", m_lIDCheckList);

	CCheckListItemSet setCheckItemZ;
	setCheckItemZ.SetOpenFilter(strFilter);
	setCheckItemZ.SetSortRecord("IDPadre, Ordine, ID");
	if (setCheckItemZ.OpenRecordset("CCheckListModDlg::RiempiAlbero"))
	{
		long lIDPadrePrev = -1;
		long lOrdine = 1;

		while (!setCheckItemZ.IsEOF())
		{
			if (setCheckItemZ.m_lIDPadre != lIDPadrePrev)
			{
				lIDPadrePrev = setCheckItemZ.m_lIDPadre;
				lOrdine = 1;
			}

			// controllo se l'ordine è corretto, altrimenti lo reimposto //
			if (setCheckItemZ.m_lOrdine != lOrdine)
			{
				if (setCheckItemZ.EditRecordset("CCheckListModDlg::RiempiAlbero"))
				{
					setCheckItemZ.m_lOrdine = lOrdine;
					setCheckItemZ.UpdateRecordset("CCheckListModDlg::RiempiAlbero");
				}
			}

			STRUCT_CHECKLISTITEM cliTemp;
			cliTemp.lID = setCheckItemZ.m_lID;
			cliTemp.lIDChecklist = setCheckItemZ.m_lIDCheckList;
			cliTemp.lIDPadre = setCheckItemZ.m_lIDPadre;
			cliTemp.sTitolo = setCheckItemZ.m_sTitolo;
			cliTemp.sTestoRtf = setCheckItemZ.m_sTestoRTF;
			cliTemp.sTestoTxt = setCheckItemZ.m_sTestoTXT;
			cliTemp.lNumeroVariabili = setCheckItemZ.m_lTestoNumeroVariabili;
			cliTemp.lIDDiagnosi = setCheckItemZ.m_lClassificazioneDiagnosi;
			CCodiciClassificazioneDiagnostSet().GetStringCodiceDescrizione(cliTemp.lIDDiagnosi, cliTemp.sDiagnosiCodice, cliTemp.sDiagnosiDescrizione);
			cliTemp.bItemAlmenoUno = setCheckItemZ.m_bItemAlmenoUno;
			cliTemp.bItemPiuDiUno = setCheckItemZ.m_bItemPiuDiUno;

			m_listChecklistItem.AddTail(cliTemp);

			lOrdine++;
			setCheckItemZ.MoveNext();
		}

		setCheckItemZ.CloseRecordset("CCheckListModDlg::RiempiAlbero");
	}

	// Sandro 16/06/2016 // ora dalla memoria riempio tutto l'albero //

	POSITION pos = m_listChecklistItem.GetHeadPosition();
	while (pos != NULL)
	{
		STRUCT_CHECKLISTITEM cliTemp = m_listChecklistItem.GetAt(pos);

		if (cliTemp.lIDPadre > 0)
			break;

		HTREEITEM hRoot = m_ctrlTree.InsertItem(TVIF_HANDLE | TVIF_PARAM | TVIF_STATE | TVIF_TEXT, cliTemp.sTitolo, 0, 0, TVIS_EXPANDED, TVIS_EXPANDED, (LPARAM)cliTemp.lID, TVI_ROOT, TVI_LAST);

		if (cliTemp.lID == lIDItemToSelect)
			hTreeItemToSelect = hRoot;

		if (hRoot != NULL)
		{
			HTREEITEM hTreeItemTemp = RiempiAlberoSub(hRoot, cliTemp.lID, lIDItemToSelect);
			if (hTreeItemTemp != NULL)
				hTreeItemToSelect = hTreeItemTemp;
		}

		m_listChecklistItem.GetNext(pos);
	}

	//

	if (hTreeItemToSelect != NULL)
		m_ctrlTree.SelectItem(hTreeItemToSelect);

	m_ctrlTree.SetRedraw(TRUE);
	EndWaitCursor();
}

HTREEITEM CCheckListModDlg::RiempiAlberoSub(HTREEITEM hRoot, long lIDPadre, long lIDItemToSelect)
{
	// Sandro 16/06/2016 // ora dalla memoria riempio tutto l'albero //

	HTREEITEM hTreeItemToSelect = NULL;

	POSITION pos = m_listChecklistItem.GetHeadPosition();
	while (pos != NULL)
	{
		STRUCT_CHECKLISTITEM cliTemp = m_listChecklistItem.GetAt(pos);

		if (cliTemp.lIDPadre > lIDPadre)
			break;

		if (cliTemp.lIDPadre == lIDPadre)
		{
			HTREEITEM hItem = m_ctrlTree.InsertItem(TVIF_HANDLE | TVIF_PARAM | TVIF_STATE | TVIF_TEXT, cliTemp.sTitolo, 0, 0, TVIS_EXPANDED, TVIS_EXPANDED, (LPARAM)cliTemp.lID, hRoot, TVI_LAST);

			if (cliTemp.lID == lIDItemToSelect)
				hTreeItemToSelect = hItem;

			if (hItem != NULL)
			{
				HTREEITEM hTreeItemTemp = RiempiAlberoSub(hItem, cliTemp.lID, lIDItemToSelect);
				if (hTreeItemTemp != NULL)
					hTreeItemToSelect = hTreeItemTemp;
			}
		}

		m_listChecklistItem.GetNext(pos);
	}

	return hTreeItemToSelect;
}

void CCheckListModDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);

	m_ctrlList.DeleteAllItems();

	CCheckListSet setCheck;
	setCheck.SetSortRecord("Codice, Descrizione");
	if (setCheck.OpenRecordset("CCheckListModDlg::RiempiLista"))
	{
		int nItem = 0;

		while(!setCheck.IsEOF())
		{
			m_ctrlList.InsertItem(nItem, setCheck.m_sCodice);
			m_ctrlList.SetItemData(nItem, (DWORD)setCheck.m_lID);

			m_ctrlList.SetItemText(nItem, COL_DESC, setCheck.m_sDescrizione);

			nItem++;
			setCheck.MoveNext();
		}

		setCheck.CloseRecordset("CCheckListModDlg::RiempiLista");
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CCheckListModDlg::RiempiListaExam()
{
	BeginWaitCursor();
	m_ctrlListExam.SetRedraw(FALSE);

	m_ctrlListExam.DeleteAllItems();
	m_listExamToDelete.RemoveAll();

	CString strFilter;
	strFilter.Format("IDCheckList=%li", m_lIDCheckList);

	CCheckListEsamiSet setCheckExam;
	setCheckExam.SetOpenFilter(strFilter);
	if (setCheckExam.OpenRecordset("CCheckListModDlg::RiempiListaExam"))
	{
		int nItem = 0;

		while(!setCheckExam.IsEOF())
		{
			m_ctrlListExam.InsertItem(nItem, CTipoEsameSet().GetSigla(setCheckExam.m_lIDTipoEsame));
			m_ctrlListExam.SetItemData(nItem, (DWORD)setCheckExam.m_lIDTipoEsame);

			m_ctrlListExam.SetItemText(nItem, COL_DESC, CTipoEsameSet().GetDescrizione(setCheckExam.m_lIDTipoEsame));

			nItem++;
			setCheckExam.MoveNext();
		}

		setCheckExam.CloseRecordset("CCheckListModDlg::RiempiListaExam");
	}

	m_ctrlListExam.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListExam.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListExam.SetRedraw(TRUE);
	EndWaitCursor();
}

void CCheckListModDlg::SalvaAlbero()
{
	if (m_bCloning && (m_lCloningID > 0))
	{
		// copio tutto l'albero che ci sta sotto //

		CList<STRUCT_COPPIA_LONG> listIDs;

		CCheckListItemSet setOrig;
		CCheckListItemSet setDest;

		CString sFilter;
		sFilter.Format("IDCheckList=%li AND IDPadre=0", m_lCloningID);

		setOrig.SetOpenFilter(sFilter);
		setOrig.SetSortRecord("Ordine, ID");
		if (setOrig.OpenRecordset("CCheckListModDlg::SalvaAlbero"))
		{
			if (setDest.OpenRecordset("CCheckListModDlg::SalvaAlbero"))
			{
				while(!setOrig.IsEOF())
				{
					if (setDest.AddNewRecordset("CCheckListModDlg::SalvaAlbero"))
					{
						setDest.m_lIDCheckList = m_lIDCheckList;
						setDest.m_lIDPadre = 0;
						setDest.m_lOrdine = setOrig.m_lOrdine;
						setDest.m_sTitolo = setOrig.m_sTitolo;
						setDest.m_sTestoRTF = setOrig.m_sTestoRTF;
						setDest.m_sTestoTXT = setOrig.m_sTestoTXT;
						setDest.m_lTestoNumeroVariabili = setOrig.m_lTestoNumeroVariabili;
						setDest.m_bItemAlmenoUno = setOrig.m_bItemAlmenoUno;
						setDest.m_bItemPiuDiUno = setOrig.m_bItemPiuDiUno;
						setDest.m_lClassificazioneDiagnosi = setOrig.m_lClassificazioneDiagnosi;

						if (setDest.UpdateRecordset("CCheckListModDlg::SalvaAlbero"))
						{
							STRUCT_COPPIA_LONG structTemp;
							structTemp.lIDOrig = setOrig.m_lID;
							structTemp.lIDDest = setDest.GetLastAdd();
							listIDs.AddTail(structTemp);

							SalvaAlberoSub(setOrig.m_lID, setDest.GetLastAdd(), &listIDs);
						}
					}

					setOrig.MoveNext();
				}

				setDest.CloseRecordset("CCheckListModDlg::SalvaAlbero");
			}

			setOrig.CloseRecordset("CCheckListModDlg::SalvaAlbero");
		}

		// Sandro 05/10/2016 // copio anche le regole //

		POSITION posOrig = listIDs.GetHeadPosition();
		while (posOrig != NULL)
		{
			STRUCT_COPPIA_LONG structTempOrig = listIDs.GetAt(posOrig);

			sFilter.Format("IDCHECKLISTITEM=%li", structTempOrig.lIDOrig);

			CCheckListItemRegoleSet setRegOrig;
			setRegOrig.SetOpenFilter(sFilter);
			if (setRegOrig.OpenRecordset("CCheckListModDlg::SalvaAlbero"))
			{
				while (!setRegOrig.IsEOF())
				{
					long lIDDestBind = 0;

					POSITION posOrigBind = listIDs.GetHeadPosition();
					while (posOrigBind != NULL)
					{
						STRUCT_COPPIA_LONG structTempBind = listIDs.GetAt(posOrigBind);

						if (structTempBind.lIDOrig == setRegOrig.m_lIDCheckListItemBind)
						{
							lIDDestBind = structTempBind.lIDDest;
							break;
						}

						listIDs.GetNext(posOrigBind);
					}

					if (lIDDestBind > 0)
						CCheckListItemRegoleSet().AddRow(structTempOrig.lIDDest, lIDDestBind, setRegOrig.m_lTipoRegola);

					setRegOrig.MoveNext();
				}

				setRegOrig.CloseRecordset("CCheckListModDlg::SalvaAlbero");
			}

			listIDs.GetNext(posOrig);
		}
	}
	else
	{
		// sposto tutti gli item dalla checklist con ID 0 a quella attualmente selezionata //

		CCheckListItemSet setTemp;
		setTemp.SetOpenFilter("IDCheckList=0");
		if (setTemp.OpenRecordset("CCheckListModDlg::SalvaAlbero"))
		{
			while(!setTemp.IsEOF())
			{
				if (setTemp.EditRecordset("CCheckListModDlg::SalvaAlbero"))
				{
					setTemp.m_lIDCheckList = m_lIDCheckList;
					setTemp.UpdateRecordset("CCheckListModDlg::SalvaAlbero");
				}

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CCheckListModDlg::SalvaAlbero");
		}
	}
}

void CCheckListModDlg::SalvaEsami()
{
	CString strFilter;
	CCheckListEsamiSet setTemp;

	// prima cancello tutti gli esami nella lista di quelli da eliminare //
	while(m_listExamToDelete.GetCount() > 0)
	{
		long lIDToDelete = m_listExamToDelete.RemoveHead();
		strFilter.Format("IDCheckList=%li AND IDTipoEsame=%li", m_lIDCheckList, lIDToDelete);

		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CCheckListModDlg::SalvaEsami"))
		{
			while(!setTemp.IsEOF())
			{
				setTemp.DeleteRecordset("CCheckListModDlg::SalvaEsami");
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CCheckListModDlg::SalvaEsami");
		}
	}

	// dopo salvo quelli nuovi //
	for(int i = 0; i < m_ctrlListExam.GetItemCount(); i++)
	{
		long lIDToSave = m_ctrlListExam.GetItemData(i);
		strFilter.Format("IDCheckList=%li AND IDTipoEsame=%li", m_lIDCheckList, lIDToSave);

		setTemp.SetOpenFilter(strFilter);
		if (setTemp.OpenRecordset("CCheckListModDlg::SalvaEsami"))
		{
			if (setTemp.IsEOF())
			{
				if (setTemp.AddNewRecordset("CCheckListModDlg::SalvaEsami"))
				{
					setTemp.m_lIDCheckList = m_lIDCheckList;
					setTemp.m_lIDTipoEsame = lIDToSave;

					setTemp.UpdateRecordset("CCheckListModDlg::SalvaEsami");
				}
			}

			setTemp.CloseRecordset("CCheckListModDlg::SalvaEsami");
		}
	}
}

void CCheckListModDlg::SalvaAlberoSub(long lIDPadreOrig, long lIDPadreDest, CList<STRUCT_COPPIA_LONG>* pIDsList)
{
	CCheckListItemSet setOrig;
	CCheckListItemSet setDest;

	CString strFilter;
	strFilter.Format("IDPadre=%li", lIDPadreOrig);

	setOrig.SetOpenFilter(strFilter);
	setOrig.SetSortRecord("Ordine, ID");
	if (setOrig.OpenRecordset("CCheckListModDlg::SalvaAlberoSub"))
	{
		if (setDest.OpenRecordset("CCheckListModDlg::SalvaAlberoSub"))
		{
			while(!setOrig.IsEOF())
			{
				if (setDest.AddNewRecordset("CCheckListModDlg::SalvaAlberoSub"))
				{
					setDest.m_lIDCheckList = m_lIDCheckList;
					setDest.m_lIDPadre = lIDPadreDest;
					setDest.m_lOrdine = setOrig.m_lOrdine;
					setDest.m_sTitolo = setOrig.m_sTitolo;
					setDest.m_sTestoRTF = setOrig.m_sTestoRTF;
					setDest.m_sTestoTXT = setOrig.m_sTestoTXT;
					setDest.m_lTestoNumeroVariabili = setOrig.m_lTestoNumeroVariabili;
					setDest.m_bItemAlmenoUno = setOrig.m_bItemAlmenoUno;
					setDest.m_bItemPiuDiUno = setOrig.m_bItemPiuDiUno;
					setDest.m_lClassificazioneDiagnosi = setOrig.m_lClassificazioneDiagnosi;

					if (setDest.UpdateRecordset("CCheckListModDlg::SalvaAlberoSub"))
					{
						STRUCT_COPPIA_LONG structTemp;
						structTemp.lIDOrig = setOrig.m_lID;
						structTemp.lIDDest = setDest.GetLastAdd();
						pIDsList->AddTail(structTemp);

						SalvaAlberoSub(setOrig.m_lID, setDest.GetLastAdd(), pIDsList);
					}
				}

				setOrig.MoveNext();
			}

			setDest.CloseRecordset("CCheckListModDlg::SalvaAlberoSub");
		}

		setOrig.CloseRecordset("CCheckListModDlg::SalvaAlberoSub");
	}
}

void CCheckListModDlg::SetReadOnly(BOOL bReadOnly)
{
	m_ctrlBtnNew.ShowWindow(bReadOnly);
	m_ctrlBtnEdt.ShowWindow(bReadOnly);
	m_ctrlBtnDel.ShowWindow(bReadOnly);
	m_ctrlBtnClone.ShowWindow(bReadOnly);
	m_ctrlBtnSave.ShowWindow(!bReadOnly);
	m_ctrlBtnUndo.ShowWindow(!bReadOnly);
	m_ctrlBtnNewEl1.ShowWindow(!bReadOnly && !m_bCloning);
	m_ctrlBtnNewEl2.ShowWindow(!bReadOnly && !m_bCloning);
	m_ctrlBtnNewEl3.ShowWindow(!bReadOnly && !m_bCloning);
	m_ctrlBtnEdtEl.ShowWindow(!bReadOnly && !m_bCloning);
	m_ctrlBtnDelEl.ShowWindow(!bReadOnly && !m_bCloning);
	m_ctrlBtnUp.ShowWindow(!bReadOnly && !m_bCloning);
	m_ctrlBtnDn.ShowWindow(!bReadOnly && !m_bCloning);
	m_ctrlBtnCopy.ShowWindow(!bReadOnly && !m_bCloning);
	m_ctrlBtnPaste.ShowWindow(!bReadOnly && !m_bCloning);
	m_ctrlBtnOK.EnableWindow(bReadOnly);

	m_ctrlList.EnableWindow(bReadOnly);
	// m_ctrlListExam.EnableWindow(bReadOnly); // sempre attivo //
	// m_ctrlTree.EnableWindow(bReadOnly); // sempre attivo //

	m_ctrlEditCod.SetReadOnly(bReadOnly);
	m_ctrlEditDesc.SetReadOnly(bReadOnly);
	m_ctrlCombo.EnableWindow(!bReadOnly);
	m_ctrlCheck1.EnableWindow(!bReadOnly);
	m_ctrlCheck2.EnableWindow(!bReadOnly);

	m_ctrlComboCampo.EnableWindow(!bReadOnly);
	m_ctrlComboOrdine.EnableWindow(!bReadOnly);

	m_ctrlBtnNewExam.ShowWindow(!bReadOnly);
	m_ctrlBtnDelExam.ShowWindow(!bReadOnly);
}