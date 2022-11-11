#include "stdafx.h"
#include "Endox.h"
#include "EndoGridModifyRulesDlg.h"
#include "EndoGridModifyFieldRulesChildDlg.h"
//#include "EcoGridItemSelectColorDlg.h"
//#include "PrintListCtrl.h"
#include "EndoGridCLParameterSet.h"
#include "EtichetteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT CEndoGridModifyRulesDlg::m_iListChange1 = WM_USER + 0xFB;
UINT CEndoGridModifyRulesDlg::m_iListChange2 = WM_USER + 0xFC;
UINT CEndoGridModifyRulesDlg::m_iListChange3 = WM_USER + 0xFD;
UINT CEndoGridModifyRulesDlg::m_iListChange4 = WM_USER + 0xFE;

IMPLEMENT_DYNAMIC(CEndoGridModifyRulesDlg, CDialog)

CEndoGridModifyRulesDlg::CEndoGridModifyRulesDlg(CWnd* pParentWnd, int iGridIndex)
: CDialog(CEndoGridModifyRulesDlg::IDD, pParentWnd), m_ctrlList1(5), m_ctrlList2(5), m_ctrlList3(-1), m_ctrlList4(-1)
{
	//Recupero l'id dell'etichetta
	m_lIDEtichetta = CEtichetteSet().GetId("GRIDCL", iGridIndex);
	//Mi salvo la lista dei parametri appartenenti a questa grid
	m_listIDParam.RemoveAll();
	CString sFilter;
	sFilter.Format("IDETICHETTA_GRIDCL=%li", m_lIDEtichetta);
	CEndoGridCLParameterSet tempSet;	
	tempSet.SetOpenFilter(sFilter);
	if (tempSet.OpenRecordset("CEndoGridModifyRulesDlg::CEndoGridModifyRulesDlg"))
	{
		while (!tempSet.IsEOF())
		{
			m_listIDParam.AddTail(tempSet.m_lId);

			tempSet.MoveNext();
		}

		tempSet.CloseRecordset("CEndoGridModifyRulesDlg::CEndoGridModifyRulesDlg");
	}
}

CEndoGridModifyRulesDlg::~CEndoGridModifyRulesDlg(void)
{
}

void CEndoGridModifyRulesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIRM, m_ctrlButton1);
	DDX_Control(pDX, IDCANCEL, m_ctrlButton2);
	DDX_Control(pDX, IDC_ADD, m_ctrlButton3);
	DDX_Control(pDX, IDC_REMOVE, m_ctrlButton4);
	DDX_Control(pDX, IDC_BUTTON_UP, m_ctrlButton5);
	DDX_Control(pDX, IDC_BUTTON_DOWN, m_ctrlButton6);
	//DDX_Control(pDX, IDC_PRINTLIST, m_ctrlButton7);

	DDX_Control(pDX, IDC_LIST1, m_ctrlList1);
	DDX_Control(pDX, IDC_LIST_2, m_ctrlList2);
	DDX_Control(pDX, IDC_LIST_3, m_ctrlList3);
	DDX_Control(pDX, IDC_LIST_4, m_ctrlList4);

	DDX_Control(pDX, IDC_TAB, m_ctrlTab);
}

BEGIN_MESSAGE_MAP(CEndoGridModifyRulesDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnTcnSelchangeTab)

	ON_MESSAGE(m_iListChange1, OnListChanged1)
	ON_MESSAGE(m_iListChange2, OnListChanged2)
	ON_MESSAGE(m_iListChange3, OnListChanged3)
	ON_MESSAGE(m_iListChange4, OnListChanged4)

	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_2, OnNMClickList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_3, OnNMClickList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_4, OnNMClickList)

	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_BN_CLICKED(IDC_CONFIRM, OnButtonConfirm)
	ON_BN_CLICKED(IDC_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_ADD, OnButtonAdd)
	//ON_BN_CLICKED(IDC_PRINTLIST, OnButtonPrintList)
END_MESSAGE_MAP()

// CModifyFieldRulesDlg message handlers

BOOL CEndoGridModifyRulesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlTab.InsertItem(0, theApp.GetMessageString(IDS_GRID_RULES_HIDE));
	m_ctrlTab.InsertItem(1, theApp.GetMessageString(IDS_GRID_RULES_SHOW));
	m_ctrlTab.InsertItem(2, theApp.GetMessageString(IDS_GRID_RULES_SIGN));
	m_ctrlTab.InsertItem(3, theApp.GetMessageString(IDS_GRID_RULES_FILL));

	InitializeListCtrl(&m_ctrlList1);
	InitializeListCtrl(&m_ctrlList2);
	InitializeListCtrl(&m_ctrlList3);
	InitializeListCtrl(&m_ctrlList4);

	Load(&m_ctrlList1, CEndoGridParameterRulesSet::hidefield);
	Load(&m_ctrlList2, CEndoGridParameterRulesSet::showfield);
	Load(&m_ctrlList3, CEndoGridParameterRulesSet::colorfield);
	Load(&m_ctrlList4, CEndoGridParameterRulesSet::valorizefield);

	ChangeTab();

	theApp.LocalizeDialog(this, CEndoGridModifyRulesDlg::IDD, "EndoGridModifyRulesDlg");
	return TRUE;
}

void CEndoGridModifyRulesDlg::OnButtonConfirm()
{
	Save(&m_ctrlList1, CEndoGridParameterRulesSet::hidefield);
	Save(&m_ctrlList2, CEndoGridParameterRulesSet::showfield);
	Save(&m_ctrlList3, CEndoGridParameterRulesSet::colorfield);
	Save(&m_ctrlList4, CEndoGridParameterRulesSet::valorizefield);
	CDialog::OnOK();
}

void CEndoGridModifyRulesDlg::OnButtonDown()
{
	switch (m_ctrlTab.GetCurSel())
	{
	case 0:
		MoveDown(&m_ctrlList1);
		break;

	case 1:
		MoveDown(&m_ctrlList2);
		break;

	case 2:
		MoveDown(&m_ctrlList3);
		break;

	case 3:
		MoveDown(&m_ctrlList4);
		break;

	default:
		ASSERT(FALSE);
		break;
	}
}

void CEndoGridModifyRulesDlg::OnButtonUp()
{
	switch (m_ctrlTab.GetCurSel())
	{
	case 0:
		MoveUp(&m_ctrlList1);
		break;

	case 1:
		MoveUp(&m_ctrlList2);
		break;

	case 2:
		MoveUp(&m_ctrlList3);
		break;

	case 3:
		MoveUp(&m_ctrlList4);
		break;

	default:
		ASSERT(FALSE);
		break;
	}
}

void CEndoGridModifyRulesDlg::OnButtonAdd()
{
	switch (m_ctrlTab.GetCurSel())
	{
	case 0:
		AddNew(&m_ctrlList1);
		break;

	case 1:
		AddNew(&m_ctrlList2);
		break;

	case 2:
		AddNew(&m_ctrlList3);
		break;

	case 3:
		AddNew(&m_ctrlList4);
		break;

	default:
		ASSERT(FALSE);
		break;
	}
}

void CEndoGridModifyRulesDlg::OnButtonRemove()
{
	switch (m_ctrlTab.GetCurSel())
	{
	case 0:
		Remove(&m_ctrlList1);
		break;

	case 1:
		Remove(&m_ctrlList2);
		break;

	case 2:
		Remove(&m_ctrlList3);
		break;

	case 3:
		Remove(&m_ctrlList4);
		break;

	default:
		ASSERT(FALSE);
		break;
	}
}

void CEndoGridModifyRulesDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	if (pNMItem->iSubItem != 1 && pNMItem->iSubItem != 4 && pNMItem->iSubItem != 5)
		return;

	CAMEditComboListCtrl* pListCtrl = NULL;
	if (pNMHDR->hwndFrom == m_ctrlList1.GetSafeHwnd())
		pListCtrl = &m_ctrlList1;
	else if (pNMHDR->hwndFrom == m_ctrlList2.GetSafeHwnd())
		pListCtrl = &m_ctrlList2;
	else if (pNMHDR->hwndFrom == m_ctrlList3.GetSafeHwnd())
		pListCtrl = &m_ctrlList3;
	else if (pNMHDR->hwndFrom == m_ctrlList4.GetSafeHwnd())
		pListCtrl = &m_ctrlList4;
	else
		ASSERT(FALSE);

	if (pNMItem->iSubItem == 5 && pListCtrl == &m_ctrlList4)
		return;

	CPoint point(pNMItem->ptAction.x, pNMItem->ptAction.y);
	CRect rectDlg;
	for (int i = 0; i < pListCtrl->GetItemCount(); i++)
	{
		CRect rect;
		if (pListCtrl->GetSubItemRect(i, pNMItem->iSubItem, LVIR_BOUNDS, rect))
		{
			if (rect.PtInRect(point))
			{
				rectDlg = rect;
				pNMItem->iItem = i;
				break;
			}
		}
	}

	if (pNMItem->iItem == -1)
		return;

	if (pListCtrl->GetItemState(pNMItem->iItem, LVIS_SELECTED) == 0)
		return;

	pListCtrl->ClientToScreen(&rectDlg);

	if (pNMItem->iSubItem == 5)
	{
		CColorDialog dlg;
		if (dlg.DoModal() == IDCANCEL)
			return;

		pListCtrl->SetSubItemBkColor(pNMItem->iItem, pNMItem->iSubItem, dlg.GetColor());
		pListCtrl->SetSubItemData(pNMItem->iItem, pNMItem->iSubItem, dlg.GetColor());
	}
	else
	{
		CEndoGridModifyFieldRulesChildDlg dlg(-1, m_lIDEtichetta, (pNMItem->iSubItem == 4), CPoint(rectDlg.left, rectDlg.bottom), this);
		if (dlg.DoModal() == IDCANCEL)
			return;

		CString strDescription;
		if (((dlg.GetItemSelectedID() << 2) >> 2) == dlg.GetItemSelectedID())
		{
			CString strFilter;
			strFilter.Format("ID = %li", dlg.GetItemSelectedID());

			CEndoGridCLParameterSet set;			
			set.SetOpenFilter(strFilter);
			if (set.OpenRecordset("CEndoGridModifyRulesDlg::OnNMClickList"))
			{
				if (!set.IsEOF())
				{
					strDescription = set.m_sParameterName;					

					if (!set.m_sNotes.IsEmpty())
						strDescription += " (" + set.m_sNotes + ")";
				}

				set.CloseRecordset("CEndoGridModifyRulesDlg::OnNMClickList");
			}			
		}
		else
		{
			strDescription = theApp.GetMessageString((dlg.GetItemSelectedID() << 2) >> 2);

			int iFind = strDescription.Find("\n");
			if (iFind > 0)
				strDescription = strDescription.Left(iFind);
		}

		pListCtrl->SetItemText(pNMItem->iItem, pNMItem->iSubItem, strDescription);
		pListCtrl->SetSubItemData(pNMItem->iItem, pNMItem->iSubItem, dlg.GetItemSelectedID());
	}
}

LRESULT CEndoGridModifyRulesDlg::OnListChanged1(WPARAM wParam, LPARAM lParam)
{
	if (lParam == 2)
		SetListSubItems(&m_ctrlList1);
	return 0;
}

LRESULT CEndoGridModifyRulesDlg::OnListChanged2(WPARAM wParam, LPARAM lParam)
{
	if (lParam == 2)
		SetListSubItems(&m_ctrlList2);
	return 0;
}

LRESULT CEndoGridModifyRulesDlg::OnListChanged3(WPARAM wParam, LPARAM lParam)
{
	if (lParam == 2)
		SetListSubItems(&m_ctrlList3);
	return 0;
}

LRESULT CEndoGridModifyRulesDlg::OnListChanged4(WPARAM wParam, LPARAM lParam)
{
	if (lParam == 2)
		SetListSubItems(&m_ctrlList4);
	return 0;
}

void CEndoGridModifyRulesDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	ChangeTab();
	*pResult = 0;
}

void CEndoGridModifyRulesDlg::InitializeListCtrl(CAMEditComboListCtrl* pList)
{
	CRect rect;
	GetDlgItem(IDC_PLACE)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	pList->SetWindowPos(NULL,
		rect.left,
		rect.top,
		rect.Width(),
		rect.Height(),
		SWP_NOZORDER);

	pList->SetExtendedStyle(pList->GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	pList->SetFont(GetFont());

	pList->InsertColumn(0, "#");
	pList->InsertColumn(1, theApp.GetMessageString(IDS_GRID_RULES_FIELD_SOURCE));
	pList->InsertColumn(2, theApp.GetMessageString(IDS_GRID_RULES_FIELD_OPERATOR));
	pList->InsertColumn(3, theApp.GetMessageString(IDS_GRID_RULES_FIELD_VALUE));

	if (pList == &m_ctrlList1)
		pList->InsertColumn(4, theApp.GetMessageString(IDS_GRID_RULES_FIELD_TO_HIDE)); //
	else if (pList == &m_ctrlList2)
		pList->InsertColumn(4, theApp.GetMessageString(IDS_GRID_RULES_FIELD_TO_SHOW));
	else if (pList == &m_ctrlList3)
		pList->InsertColumn(4, theApp.GetMessageString(IDS_GRID_RULES_FIELD_TO_SIGN));
	else if (pList == &m_ctrlList4)
		pList->InsertColumn(4, theApp.GetMessageString(IDS_GRID_RULES_FIELD_TO_FILL));
	else
		ASSERT(FALSE);

	if (pList == &m_ctrlList4)
		pList->InsertColumn(5, theApp.GetMessageString(IDS_GRID_RULES_FIELD_VALUE));
	else
		pList->InsertColumn(5, theApp.GetMessageString(IDS_COLORE));

	pList->InsertColumn(6, theApp.GetMessageString(IDS_NOTE));

	int iColumnWidthColor = 0;
	if (pList == &m_ctrlList1 || pList == &m_ctrlList2)
		iColumnWidthColor = 0;
	else if (pList == &m_ctrlList3)
		iColumnWidthColor = 50;
	else if (pList == &m_ctrlList4)
		iColumnWidthColor = 150;
	else
		ASSERT(FALSE);

	pList->GetClientRect(&rect);
	int iColumnWidth = (rect.Width() - 120 - iColumnWidthColor - GetSystemMetrics(SM_CXVSCROLL)) / 4;

	pList->SetColumnWidth(0, 20);
	pList->SetColumnWidth(1, iColumnWidth);
	pList->SetColumnWidth(2, 100);
	pList->SetColumnWidth(3, iColumnWidth);
	pList->SetColumnWidth(4, iColumnWidth);
	pList->SetColumnWidth(5, iColumnWidthColor);
	pList->SetColumnWidth(6, iColumnWidth);

	if (pList == &m_ctrlList1)
		pList->SetNotificationChangeValueMessage(m_iListChange1);
	else if (pList == &m_ctrlList2)
		pList->SetNotificationChangeValueMessage(m_iListChange2);
	else if (pList == &m_ctrlList3)
		pList->SetNotificationChangeValueMessage(m_iListChange3);
	else if (pList == &m_ctrlList4)
		pList->SetNotificationChangeValueMessage(m_iListChange4);
	else
		ASSERT(FALSE);
}

void CEndoGridModifyRulesDlg::Load(CAMEditComboListCtrl* pList, CEndoGridParameterRulesSet::RuleType type)
{
	CEndoGridParameterRulesSet set(TRUE);
	CString strFilter;
	strFilter.Format("tiporegola = %li", type);

	set.SetOpenFilter(strFilter);

	pList->DeleteAllItems();

	if (set.OpenRecordset("CEndoGridModifyRulesDlg::Load"))
	{
		while (!set.IsEOF())
		{
			if (m_listIDParam.Find(set.m_idparametro1) == NULL)
			{
				set.MoveNext();
				continue;
			}

			CString str;
#ifdef _DEBUG
			str.Format("%li", set.m_id);
#endif
			int iInserted = pList->InsertItem(pList->GetItemCount(), str);

			if (!set.m_note1.IsEmpty())
				set.m_nomeparametro1 += " (" + set.m_note1 + ")";

			pList->SetItemText(iInserted, 1, set.m_nomeparametro1);			
			pList->SetSubItemData(iInserted, 1, set.m_idparametro1);

			pList->SetSubItemData(iInserted, 2, set.m_operatore);
			switch (set.m_operatore)
			{
			case CEndoGridParameterRulesSet::equal:
			case CEndoGridParameterRulesSet::startwith:
			case CEndoGridParameterRulesSet::major:
			case CEndoGridParameterRulesSet::minor:
			case CEndoGridParameterRulesSet::different:
			case CEndoGridParameterRulesSet::contains:
			case CEndoGridParameterRulesSet::minor_major:
				pList->SetItemText(iInserted, 3, set.m_valore);
				break;

			case CEndoGridParameterRulesSet::valid:
				break;

			default:
				ASSERT(FALSE);
				break;
			}

			if (!set.m_note2.IsEmpty())
				set.m_nomeparametro2 += " (" + set.m_note2 + ")";

			pList->SetItemText(iInserted, 4, set.m_nomeparametro2);
			pList->SetSubItemData(iInserted, 4, set.m_idparametro2);

			if (pList == &m_ctrlList3)
			{
				if (!set.IsFieldNull(&set.m_colore))
				{
					pList->SetSubItemBkColor(iInserted, 5, set.m_colore);
					pList->SetSubItemData(iInserted, 5, set.m_colore);
				}
			}
			else if (pList == &m_ctrlList4)
				pList->SetItemText(iInserted, 5, set.m_valore2);

			pList->SetItemText(iInserted, 6, set.m_nota);
			pList->SetItemData(iInserted, set.m_id);

			set.MoveNext();
		}

		set.CloseRecordset("CEndoGridModifyRulesDlg::Load");
	}	

	SetListSubItems(pList);
}

void CEndoGridModifyRulesDlg::Save(CAMEditComboListCtrl* pList, CEndoGridParameterRulesSet::RuleType type)
{
	CEndoGridParameterRulesSet set(FALSE);
	CString strFilter;

	for (int i = 0; i < pList->GetItemCount(); i++)
	{
		long lOperator = pList->GetSubItemData(i, 2);
		if (lOperator != CEndoGridParameterRulesSet::equal &&
			lOperator != CEndoGridParameterRulesSet::valid &&
			lOperator != CEndoGridParameterRulesSet::startwith &&
			lOperator != CEndoGridParameterRulesSet::major &&
			lOperator != CEndoGridParameterRulesSet::minor &&
			lOperator != CEndoGridParameterRulesSet::different &&
			lOperator != CEndoGridParameterRulesSet::contains &&
			lOperator != CEndoGridParameterRulesSet::minor_major)
		{
			ASSERT(FALSE);
			continue;
		}

		if (pList->GetItemData(i) > 0)
		{
			strFilter.Format("id = %li", pList->GetItemData(i));
			set.SetOpenFilter(strFilter);
			if (!set.OpenRecordset("CEndoGridModifyRulesDlg::Save"))
				return;

			if (!set.EditRecordset("CEndoGridModifyRulesDlg::Save"))
				return;
		}
		else
		{
			set.SetOpenFilter("id = 0");
			if (!set.OpenRecordset("CEndoGridModifyRulesDlg::Save"))
				return;

			if (!set.AddNewRecordset("CEndoGridModifyRulesDlg::Save"))
				return;

			set.m_tiporegola = type;
		}

		set.m_idparametro1 = pList->GetSubItemData(i, 1);
		set.m_operatore = lOperator;
		set.m_valore = pList->GetItemText(i, 3);
		set.m_idparametro2 = pList->GetSubItemData(i, 4);
		if (pList->GetSubItemData(i, 5) >= 0)
			set.m_colore = pList->GetSubItemData(i, 5);
		else
			set.SetFieldNull(&set.m_colore);

		if (pList == &m_ctrlList4)
			set.m_valore2 = pList->GetItemText(i, 5);

		set.m_nota = pList->GetItemText(i, 6);
		set.m_ordine = i + 1;
		
		if (!set.UpdateRecordset("CEndoGridModifyRulesDlg::Save"))
			return;

		set.CloseRecordset("");
	}
}

void CEndoGridModifyRulesDlg::SetListSubItems(CAMEditComboListCtrl* pList)
{
	pList->ResetSubItemsType();

	CStringIDList list;
	tagLISTCOMBO lc;

	lc.lID = CEndoGridParameterRulesSet::equal;
	lc.strName = theApp.GetMessageString(IDS_UGUALE_A);
	list.AddTail(lc);

	lc.lID = CEndoGridParameterRulesSet::valid;
	lc.strName = theApp.GetMessageString(IDS_VALORIZZATO);
	list.AddTail(lc);

	lc.lID = CEndoGridParameterRulesSet::startwith;
	lc.strName = theApp.GetMessageString(IDS_COMINCIA_CON);
	list.AddTail(lc);

	lc.lID = CEndoGridParameterRulesSet::major;
	lc.strName = theApp.GetMessageString(IDS_MAGGIORE);
	list.AddTail(lc);

	lc.lID = CEndoGridParameterRulesSet::minor;
	lc.strName = theApp.GetMessageString(IDS_MINORE);
	list.AddTail(lc);

	lc.lID = CEndoGridParameterRulesSet::minor_major;
	lc.strName = theApp.GetMessageString(IDS_MINORE_DI_MAGGIORE_DI);
	list.AddTail(lc);

	lc.lID = CEndoGridParameterRulesSet::different;
	lc.strName = theApp.GetMessageString(IDS_DIVERSO);
	list.AddTail(lc);

	lc.lID = CEndoGridParameterRulesSet::contains;
	lc.strName = theApp.GetMessageString(IDS_CONTIENE);
	list.AddTail(lc);

	pList->SetSubItemCombo(-1, 2, list);

	if (pList == &m_ctrlList4)
		pList->SetSubItemEdit(-1, 5, FALSE, 255);

	pList->SetSubItemEdit(-1, 6, FALSE, 255);

	for (int i = 0; i < pList->GetItemCount(); i++)
	{
		long lOperator = pList->GetSubItemData(i, 2);
		switch (lOperator)
		{
		case CEndoGridParameterRulesSet::equal:
			pList->SetItemText(i, 2, theApp.GetMessageString(IDS_UGUALE_A));
			pList->SetSubItemEdit(i, 3, FALSE, 255);
			break;

		case CEndoGridParameterRulesSet::valid:
			pList->SetItemText(i, 2, theApp.GetMessageString(IDS_VALORIZZATO));
			pList->SetItemText(i, 3, "");
			break;

		case CEndoGridParameterRulesSet::startwith:
			pList->SetItemText(i, 2, theApp.GetMessageString(IDS_COMINCIA_CON));
			pList->SetSubItemEdit(i, 3, FALSE, 255);
			break;

		case CEndoGridParameterRulesSet::major:
			pList->SetItemText(i, 2, theApp.GetMessageString(IDS_MAGGIORE));
			pList->SetSubItemEdit(i, 3, FALSE, 255);
			break;

		case CEndoGridParameterRulesSet::minor:
			pList->SetItemText(i, 2, theApp.GetMessageString(IDS_MINORE));
			pList->SetSubItemEdit(i, 3, FALSE, 255);
			break;

		case CEndoGridParameterRulesSet::minor_major:
			pList->SetItemText(i, 2, theApp.GetMessageString(IDS_MINORE_DI_MAGGIORE_DI));
			pList->SetSubItemEdit(i, 3, FALSE, 255);
			break;

		case CEndoGridParameterRulesSet::different:
			pList->SetItemText(i, 2, theApp.GetMessageString(IDS_DIVERSO));
			pList->SetSubItemEdit(i, 3, FALSE, 255);
			break;

		case CEndoGridParameterRulesSet::contains:
			pList->SetItemText(i, 2, theApp.GetMessageString(IDS_CONTIENE));
			pList->SetSubItemEdit(i, 3, FALSE, 255);
			break;

		default:
			ASSERT(FALSE);
			break;
		}
	}
}

void CEndoGridModifyRulesDlg::MoveDown(CAMEditComboListCtrl* pList)
{
	int iItemSelected = -1;
	for (int i = 0; i < pList->GetItemCount(); i++)
	{
		if (pList->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			iItemSelected = i;
			break;
		}
	}

	if (iItemSelected == -1)
		return;

	if (iItemSelected == pList->GetItemCount() - 1)
		return;

	int iInserted = pList->InsertItem(iItemSelected + 2, "");

	pList->SetItemText(iInserted, 1, pList->GetItemText(iItemSelected, 1));
	pList->SetSubItemData(iInserted, 1, pList->GetSubItemData(iItemSelected, 1));

	pList->SetSubItemData(iInserted, 2, pList->GetSubItemData(iItemSelected, 2));
	pList->SetItemText(iInserted, 3, pList->GetItemText(iItemSelected, 3));

	pList->SetItemText(iInserted, 4, pList->GetItemText(iItemSelected, 4));
	pList->SetSubItemData(iInserted, 4, pList->GetSubItemData(iItemSelected, 4));

	COLORREF clColor;
	pList->GetSubItemBkColor(iItemSelected, 5, clColor);
	pList->SetSubItemBkColor(iInserted, 5, clColor);
	pList->SetSubItemData(iInserted, 5, pList->GetSubItemData(iItemSelected, 5));
	pList->SetItemText(iInserted, 5, pList->GetItemText(iItemSelected, 5));

	pList->SetItemText(iInserted, 6, pList->GetItemText(iItemSelected, 6));
	pList->SetItemData(iInserted, pList->GetItemData(iItemSelected));

	pList->SetItemState(iInserted, LVIS_SELECTED, LVIS_SELECTED);
	pList->DeleteItem(iItemSelected);
}

void CEndoGridModifyRulesDlg::MoveUp(CAMEditComboListCtrl* pList)
{
	int iItemSelected = -1;
	for (int i = 0; i < pList->GetItemCount(); i++)
	{
		if (pList->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			iItemSelected = i;
			break;
		}
	}

	if (iItemSelected == -1)
		return;

	if (iItemSelected == 0)
		return;

	int iInserted = pList->InsertItem(iItemSelected - 1, "");
	iItemSelected = iItemSelected + 1; // ho inserito un elemento prima

	pList->SetItemText(iInserted, 1, pList->GetItemText(iItemSelected, 1));
	pList->SetSubItemData(iInserted, 1, pList->GetSubItemData(iItemSelected, 1));

	pList->SetSubItemData(iInserted, 2, pList->GetSubItemData(iItemSelected, 2));
	pList->SetItemText(iInserted, 3, pList->GetItemText(iItemSelected, 3));

	pList->SetItemText(iInserted, 4, pList->GetItemText(iItemSelected, 4));
	pList->SetSubItemData(iInserted, 4, pList->GetSubItemData(iItemSelected, 4));

	COLORREF clColor;
	pList->GetSubItemBkColor(iItemSelected, 5, clColor);
	pList->SetSubItemBkColor(iInserted, 5, clColor);
	pList->SetSubItemData(iInserted, 5, pList->GetSubItemData(iItemSelected, 5));
	pList->SetItemText(iInserted, 5, pList->GetItemText(iItemSelected, 5));

	pList->SetItemText(iInserted, 6, pList->GetItemText(iItemSelected, 6));
	pList->SetItemData(iInserted, pList->GetItemData(iItemSelected));

	pList->SetItemState(iInserted, LVIS_SELECTED, LVIS_SELECTED);
	pList->DeleteItem(iItemSelected);
}

void CEndoGridModifyRulesDlg::AddNew(CAMEditComboListCtrl* pList)
{
	int iInserted = pList->InsertItem(pList->GetItemCount(), "");
	pList->SetItemState(iInserted, LVIS_SELECTED, LVIS_SELECTED);
	pList->SetFocus();

	CRect rect;
	pList->GetSubItemRect(iInserted, 0, LVIR_LABEL, rect);
	pList->PostMessage(WM_LBUTTONDOWN, 0, MAKELPARAM((rect.right + rect.left) / 2, (rect.bottom + rect.top) / 2));
}

void CEndoGridModifyRulesDlg::Remove(CAMEditComboListCtrl* pList)
{
	if (POSITION pos = pList->GetFirstSelectedItemPosition())
	{
		int iItem = pList->GetNextSelectedItem(pos);

		if (pList->GetItemData(iItem) > 0)
		{
			CEndoGridParameterRulesSet set(FALSE);
			CString strFilter;
			strFilter.Format("id = %li", pList->GetItemData(iItem));

			set.SetOpenFilter(strFilter);
			if (set.OpenRecordset("CEndoGridModifyRulesDlg::Remove"))
			{
				if (!set.IsEOF())
					set.DeleteRecordset("CEndoGridModifyRulesDlg::Remove");

				set.CloseRecordset("CEndoGridModifyRulesDlg::Remove");
			}			
		}

		pList->DeleteItem(iItem);
	}
}

void CEndoGridModifyRulesDlg::ChangeTab()
{
	switch (m_ctrlTab.GetCurSel())
	{
	case 0:
		m_ctrlList1.ShowWindow(SW_SHOW);
		m_ctrlList2.ShowWindow(SW_HIDE);
		m_ctrlList3.ShowWindow(SW_HIDE);
		m_ctrlList4.ShowWindow(SW_HIDE);
		break;

	case 1:
		m_ctrlList1.ShowWindow(SW_HIDE);
		m_ctrlList2.ShowWindow(SW_SHOW);
		m_ctrlList3.ShowWindow(SW_HIDE);
		m_ctrlList4.ShowWindow(SW_HIDE);
		break;

	case 2:
		m_ctrlList1.ShowWindow(SW_HIDE);
		m_ctrlList2.ShowWindow(SW_HIDE);
		m_ctrlList3.ShowWindow(SW_SHOW);
		m_ctrlList4.ShowWindow(SW_HIDE);
		break;

	case 3:
		m_ctrlList1.ShowWindow(SW_HIDE);
		m_ctrlList2.ShowWindow(SW_HIDE);
		m_ctrlList3.ShowWindow(SW_HIDE);
		m_ctrlList4.ShowWindow(SW_SHOW);
		break;

	default:
		ASSERT(FALSE);
		break;
	}
}