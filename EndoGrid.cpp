#include "stdafx.h"
#include "Endox.h"
#include "EndoGrid.h"

#include "EndoGridTheme.h"
#include "EndoGridCLOptionsSet.h"
#include "EndoGridCLParameterSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGrid, CXTPPropertyGrid)

CEndoGrid::CEndoGrid(CString sGridID)
{
	m_bReadOnly = FALSE;
	m_bShowAllItem = FALSE;
	m_bEvidenceObbligaroryField = TRUE;
	m_sGridID = sGridID;
}


CEndoGrid::~CEndoGrid()
{
}

void CEndoGrid::DoDataExchange(CDataExchange* pDX)
{
	CXTPPropertyGrid::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEndoGrid, CXTPPropertyGrid)
	ON_MESSAGE(EPM_CHECK_OBBLIGATORY_FIELD, OnCheckObbligatoryField)
	ON_MESSAGE(EPM_FOCUS_OBBLIGATORY_FIELD, OnFocusObbligatoryField)
	ON_MESSAGE(EPM_APP_STATECHANGED, OnAppStateChanged)
	ON_MESSAGE(EPM_PATIENTCHANGED, OnPatientChanged)
	ON_MESSAGE(EPM_EXAMCHANGED, OnExamChanged)
	ON_MESSAGE(EPM_EXAM_EDIT, OnExamEdit)
	ON_MESSAGE(EPM_EXAM_UPDATE, OnExamUpdate)
	ON_MESSAGE(EPM_EXAM_UNDO, OnExamUndo)
	ON_MESSAGE(EPM_ITEMDIRTY, OnItemDirty)
	ON_MESSAGE(EPM_PROPERTYGRID_NOTIFY, OnGridNotify)
	ON_MESSAGE(EPM_ANALYZE_GRID_RULES, OnAnalyzeGridRules)

	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CEndoGrid::Create(CWnd* pParentWnd, UINT nID)
{
	ASSERT(pParentWnd);

	CRect rc;
	pParentWnd->GetDlgItem(nID)->GetWindowRect(&rc);
	pParentWnd->ScreenToClient(&rc);

	SetVariableItemsHeight(TRUE);
	NavigateItems(TRUE, FALSE);

	if (!CXTPPropertyGrid::Create(rc, pParentWnd, nID))
		return FALSE;

	SetCustomTheme(new CEndoGridTheme(this));

	SetFont(pParentWnd->GetFont());
	LoadDividerPos();
	BringWindowToTop();
	ShowHelp(FALSE);

	Init();

	LoadRules();
	
	return TRUE;
}

void CEndoGrid::OnDestroy()
{
	CXTPPropertyGrid::OnDestroy();
}

LRESULT CEndoGrid::OnGridNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case XTP_PGN_INPLACEBUTTONDOWN:
		case XTP_PGN_SORTORDER_CHANGED:
		case XTP_PGN_SELECTION_CHANGED:
			break;

		case XTP_PGN_ITEMVALUE_CHANGED:
		{
			ItemValueChanged((CXTPPropertyGridItem*)lParam);
			break;
		}

		case XTP_PGN_ITEMEXPANDCHANGED:
		case XTP_PGN_SCROLL:
			//ReposButtons();
			break;

		case XTP_TAB_ON_LAST_ITEM:
			break;

		case XTP_PGN_EDIT_CHANGED:
		{
			if (CXTPPropertyGridInplaceEdit* pInplaceEdit = DYNAMIC_DOWNCAST(CXTPPropertyGridInplaceEdit, (CWnd*)lParam))
			{
				if (CEndoGridItemEdit* pItem = DYNAMIC_DOWNCAST(CEndoGridItemEdit, pInplaceEdit->GetItem()))
				{
					int nMax = pItem->GetLimitText();
					if (nMax > 0)
					{
						CString str;
						pInplaceEdit->CEdit::GetWindowText(str);

						if (nMax > 0 && str.GetLength() > nMax)
						{
							MessageBeep((UINT)-1);
							pInplaceEdit->SetSel(0, -1);
							pInplaceEdit->ReplaceSel(str.Left(nMax));
						}
					}
				}
			}
			break;
		}

		case XTP_DIVIDER_POS_CHANGED:
		{
			SaveDividerPos();
			break;
		}
	}

	return 0;
}

BOOL CEndoGrid::GetEvidenceObbligaroryField()
{
	return m_bEvidenceObbligaroryField;
}

void CEndoGrid::SetEvidenceObbligaroryField(BOOL bEnable)
{
	m_bEvidenceObbligaroryField = bEnable;
}

BOOL CEndoGrid::IsObbligaroryField(CXTPPropertyGridItem* pItem)
{
	long lFieldID = pItem->GetID();

	return m_listObbligatoryField.IsPresent(lFieldID);
}

void CEndoGrid::LoadObbligatoryField()
{
	m_listObbligatoryField.Reset();
}

BOOL CEndoGrid::CheckObbligatoryField(CObbligatoryFieldErrorList* pList, CXTPPropertyGridItem* pItemParent)
{
	BOOL bReturn = TRUE;

	if (pItemParent == NULL)
	{
		for (int i = 0; i < GetCategories()->GetCount(); i++)
		{
			CXTPPropertyGridItem* pCategory = GetCategories()->GetAt(i);
			bReturn &= (!pCategory->IsHidden()) ? CEndoGrid::CheckObbligatoryField(pList, pCategory) : TRUE;
		}
	}
	else
	{
		for (int j = 0; j < pItemParent->GetChilds()->GetCount(); j++)
		{
			CXTPPropertyGridItem* pItem = pItemParent->GetChilds()->GetAt(j);

			if (m_listObbligatoryField.IsPresent(pItem->GetID()))
			{
				BOOL bItemVisible = !pItem->IsHidden();
				CXTPPropertyGridItem* pItemParent = pItem->GetParentItem();
				while (pItemParent)
				{
					bItemVisible &= !pItemParent->IsHidden();
					pItemParent = pItemParent->GetParentItem();
				}

				if (bItemVisible && !pItem->IsValorized())
				{
					pList->Add(pItem->GetID(), pItem->GetCaption());
					bReturn = FALSE;
				}
			}

			bReturn &= CEndoGrid::CheckObbligatoryField(pList, pItem);
		}
	}

	return bReturn;
}

BOOL CEndoGrid::FocusObbligatoryField(long lFieldID, CXTPPropertyGridItem* pItemParent)
{
	BOOL bReturn = FALSE;

	if (pItemParent == NULL)
	{
		for (int i = 0; i < GetCategories()->GetCount(); i++)
		{
			CXTPPropertyGridItem* pCategory = GetCategories()->GetAt(i);
			if (CEndoGrid::FocusObbligatoryField(lFieldID, pCategory))
			{
				bReturn = TRUE;
				break;
			}
		}
	}
	else
	{
		for (int j = 0; j < pItemParent->GetChilds()->GetCount(); j++)
		{
			CXTPPropertyGridItem* pItem = pItemParent->GetChilds()->GetAt(j);

			if (m_listObbligatoryField.IsPresent(pItem->GetID()) && lFieldID == pItem->GetID())
			{
				pItem->Select();
				bReturn = TRUE;
				break;
			}

			CEndoGrid::FocusObbligatoryField(lFieldID, pItem);
		}
	}

	return bReturn;
}

void CEndoGrid::LoadDividerPos()
{
	//Ogni volta che viene richiesto, viene caricata la posizione del divider dal db
	CString sFilter;
	sFilter.Format("GRIDIDENTIFIER='%s'", m_sGridID);
	CEndoGridCLOptionsSet optionSet;
	optionSet.SetOpenFilter(sFilter);

	if (optionSet.OpenRecordset("CEndoGrid::LoadDividerPos"))
	{
		if (!optionSet.IsEOF())
			SetViewDivider(optionSet.m_fDividerPos);

		optionSet.CloseRecordset("CEndoGrid::LoadDividerPos");
	}
}

void CEndoGrid::SaveDividerPos()
{
	//Ogni volta che viene richiesto, viene salvata la posizione del divider sul db
	CString sFilter;
	sFilter.Format("GRIDIDENTIFIER='%s'", m_sGridID);
	CEndoGridCLOptionsSet optionSet;
	optionSet.SetOpenFilter(sFilter);

	if (optionSet.OpenRecordset("CEndoGrid::SaveDividerPos"))
	{
		if (!optionSet.IsEOF())
		{
			if (optionSet.EditRecordset("CEndoGrid::SaveDividerPos"))
			{
				optionSet.m_fDividerPos = (float) GetViewDivider();

				optionSet.UpdateRecordset("CEndoGrid::SaveDividerPos");
			}			
		}
		else
		{
			if (optionSet.AddNewRecordset("CEndoGrid::SaveDividerPos"))
			{
				optionSet.m_sGridIdentifier = m_sGridID;
				optionSet.m_fDividerPos = (float)GetViewDivider();

				optionSet.UpdateRecordset("CEndoGrid::SaveDividerPos");
			}
		}

		optionSet.CloseRecordset("CEndoGrid::SaveDividerPos");
	}
}

BOOL CEndoGrid::PreTranslateMessage(MSG* pMsg)
{
	UpdateDialogControls(this, TRUE);
	return CXTPPropertyGrid::PreTranslateMessage(pMsg);
}

void CEndoGrid::OnCollapse()
{
	CXTPPropertyGridItems* pItems = GetCategories();
	for (int i = 0; i < pItems->GetCount(); i++)
		pItems->GetAt(i)->Expand();
}

LRESULT CEndoGrid::OnPatientChanged(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CEndoGrid::OnExamChanged(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CEndoGrid::OnExamEdit(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CEndoGrid::OnExamUpdate(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CEndoGrid::OnExamUndo(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CEndoGrid::OnItemDirty(WPARAM wParam, LPARAM lParam)
{
	GetParent()->PostMessage(EPM_GRIDDIRTY);
	return 0;
}

LRESULT CEndoGrid::OnAppStateChanged(WPARAM wParam, LPARAM lParam)
{
	SetReadOnly(wParam);
	//UpdateButtonState();
	return 0;
}

void CEndoGrid::OnSize(UINT nType, int cx, int cy)
{
	CXTPPropertyGrid::OnSize(nType, cx, cy);
	//ReposButtons();
}

LRESULT CEndoGrid::OnCheckObbligatoryField(WPARAM wParam, LPARAM lParam)
{
	return CheckObbligatoryField((CObbligatoryFieldErrorList*)wParam) ? 0 : 1;
}

LRESULT CEndoGrid::OnFocusObbligatoryField(WPARAM wParam, LPARAM lParam)
{
	FocusObbligatoryField((long)wParam);
	return 0;
}

LRESULT CEndoGrid::OnAnalyzeGridRules(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

/*LRESULT CEndoGrid::OnLoadGridRules(WPARAM wParam, LPARAM lParam)
{
	LoadRules();
	return 0;
}*/

void CEndoGrid::SetReadOnly(BOOL bEnable)
{
#define _RO_HELP_BACKGROUND RGB(242, 241, 238)
#define _RO_HELP_FOREGROUND RGB(0, 0, 0)
#define _RO_HELP_VIEWLINE   RGB(0, 0, 0)
#define _RO_HELP_VIEWBACK   RGB(242, 241, 238)
#define _RO_HELP_VIEWFORE   RGB(0, 0, 0)
#define _RW_HELP_BACKGROUND RGB(255, 255, 255) 
#define _RW_HELP_FOREGROUND RGB(0, 0, 0)
#define _RW_HELP_VIEWLINE   RGB(0, 0, 0)
#define _RW_HELP_VIEWBACK   RGB(255, 255, 255)
#define _RW_HELP_VIEWFORE   RGB(0, 0, 0)

	m_bReadOnly = bEnable;

	CXTPPropertyGridItemMetrics* pMetrics = m_pPaintManager->GetItemMetrics();

	if (bEnable)
	{
		//pMetrics->m_clrHelpBack.SetCustomValue(_RO_HELP_BACKGROUND);
		//pMetrics->m_clrHelpFore.SetCustomValue(_RO_HELP_FOREGROUND);
		//pMetrics->m_clrLine.SetCustomValue(_RO_HELP_VIEWLINE);
		//pMetrics->m_clrBack.SetCustomValue(_RO_HELP_VIEWBACK);
		//pMetrics->m_clrFore.SetCustomValue(_RO_HELP_VIEWFORE);
		pMetrics->m_clrReadOnlyFore.SetCustomValue(0);
		pMetrics->m_clrCategoryFore.SetCustomValue(0);
		pMetrics->m_clrBack.SetCustomValue(_RO_HELP_VIEWBACK);

		//pMetrics->m_clrCategoryFore.m_clrFace
	}
	else
	{
		//pMetrics->m_clrHelpBack.SetCustomValue(_RW_HELP_BACKGROUND);
		//pMetrics->m_clrHelpFore.SetCustomValue(_RW_HELP_FOREGROUND);
		//pMetrics->m_clrLine.SetCustomValue(_RW_HELP_VIEWLINE);
		//pMetrics->m_clrBack.SetCustomValue(_RW_HELP_VIEWBACK);
		//pMetrics->m_clrFore.SetCustomValue(_RW_HELP_VIEWFORE);
		pMetrics->m_clrReadOnlyFore.SetCustomValue(0);
		pMetrics->m_clrCategoryFore.SetCustomValue(0);
		pMetrics->m_clrBack.SetCustomValue(RGB(255, 255, 255));

		//pMetrics->m_clrCategoryFore.m_clrFace
	}

	/*
	if (bEnable)
	SetCustomColors(_RO_HELP_BACKGROUND,
	_RO_HELP_FOREGROUND,
	_RO_HELP_VIEWLINE,
	_RO_HELP_VIEWBACK,
	_RO_HELP_VIEWFORE);
	else
	SetCustomColors(_RW_HELP_BACKGROUND,
	_RW_HELP_FOREGROUND,
	_RW_HELP_VIEWLINE,
	_RW_HELP_VIEWBACK,
	_RW_HELP_VIEWFORE);*/

	if (CXTPPropertyGridItems* pCategoryList = GetCategories())
	{
		for (int i = 0; i < pCategoryList->GetCount(); i++)
			pCategoryList->GetAt(i)->SetReadOnly(bEnable);
	}
}

void CEndoGrid::SetFocusFirstItem()
{
	CXTPPropertyGridItems* pCategoryList = GetCategories();

	if (!pCategoryList)
		return;

	BOOL bFoundNotes = FALSE;
	/*if (theApp.m_CurrentUserSettings.bFocusOnGridItemNotes)
	{
		for (int i = 0; i < pCategoryList->GetCount(); i++)
		{
			CXTPPropertyGridItem* pCategoryItem = pCategoryList->GetAt(i);
			if (!pCategoryItem || !pCategoryItem->GetChilds())
				continue;

			for (int j = 0; j < pCategoryItem->GetChilds()->GetCount(); j++)
			{
				CXTPPropertyGridItem* pItem = pCategoryItem->GetChilds()->GetAt(j);
				if (pItem->IsKindOf(RUNTIME_CLASS(CEcoGridItemNotes)))
				{
					SetFocus();
					pItem->Select();
					bFoundNotes = TRUE;
					break;
				}
			}

			if (bFoundNotes)
				break;
		}
	}

	if (!bFoundNotes)
	{
		CXTPPropertyGridItem* pCategoryItem = pCategoryList->GetAt(0);
		if (pCategoryItem && pCategoryItem->GetChilds())
		{
			SetFocus();
			pCategoryItem->Select();

			GetGridView().SendMessage(WM_CHAR, VK_TAB);
		}
	}*/
}

void CEndoGrid::LoadRules()
{
	m_listRules.RemoveAll();

	CEndoGridParameterRulesSet set(TRUE);

	if (set.OpenRecordset("CEndoGrid::LoadRules"))
	{
		while (!set.IsEOF())
		{
			tagFIELDRULE rule;
			rule.lID = set.m_id;
			rule.RuleType = (CEndoGridParameterRulesSet::RuleType)set.m_tiporegola;
			rule.lFieldID = set.m_idparametro1;
			rule.bNumeric = (set.m_fbisd1 == CEndoGridCLParameterSet::type_double ||
				set.m_fbisd1 == CEndoGridCLParameterSet::type_integer);
			rule.Operator = (CEndoGridParameterRulesSet::OperatorType)set.m_operatore;
			strcpy_s(rule.szValue, set.m_valore);
			rule.lFieldToHide = set.m_idparametro2;
			rule.clColor = (!set.IsFieldNull(&set.m_colore)) ? set.m_colore : 0;
			strcpy_s(rule.szNewValue, set.m_valore2);
			m_listRules.AddTail(rule);
			set.MoveNext();
		}

		set.CloseRecordset("CEndoGrid::LoadRules");
	}
	
}

void CEndoGrid::ItemValueChanged(CXTPPropertyGridItem* pItem)
{
	//if (!AreActivatedRules())
		//return;

	TRACE("%s ItemValueChanged %s %li %s\n", pItem->GetGrid()->GetPropertyGrid()->GetRuntimeClass()->m_lpszClassName, pItem->GetCaption(), pItem->GetID(), pItem->GetValueEx());

	//OnAnalyzeGridRules(NULL,NULL);

	/*
	CEcoUserGridItems list;
	list.AddTail(pItem);
	AnalyzeRules(&list);
	*/
}

void CEndoGrid::AnalyzeRules(const CEndoGridCLItems* pItems, CList<tagAPPLYRULE>* pListApplyRule)
{
	TRACE("Analizzo %li campi griglia %s!\n", pItems->GetCount(), GetRuntimeClass()->m_lpszClassName);

	int iCounter = 0;
	for (int i = 0; i < pItems->GetCount(); i++)
	{
		CXTPPropertyGridItem* pItem = pItems->GetAt(pItems->FindIndex(i));
		for (POSITION pos = m_listRules.GetHeadPosition(); pos;)
		{
			tagFIELDRULE rule = m_listRules.GetNext(pos);
			if (rule.lFieldID == pItem->GetID())
			{
				tagAPPLYRULE ApplyRule;
				ZeroMemory(&ApplyRule, sizeof(tagAPPLYRULE));

				ApplyRule.lID = rule.lID;
				ApplyRule.RuleType = rule.RuleType;
				ApplyRule.lFieldID = rule.lFieldToHide;
				ApplyRule.clColor = rule.clColor;
				strcpy_s(ApplyRule.szNewValue, rule.szNewValue);

				if (strcmp(rule.szValue, "DATA ODIERNA") == 0)
				{
					CString strNow = theApp.GetServerDate();
					strcpy_s(rule.szValue, strNow.Mid(6, 2) + "/" + strNow.Mid(4, 2) + "/" + strNow.Mid(0, 4));
				}

				switch (rule.Operator)
				{
				case CEndoGridParameterRulesSet::equal: // Uguale a
					ApplyRule.bRuleValid = (pItem->GetValueEx() == rule.szValue);
					break;

				case CEndoGridParameterRulesSet::valid: // Valorizzato
					ApplyRule.bRuleValid = !pItem->GetValueEx().IsEmpty();
					break;

				case CEndoGridParameterRulesSet::startwith: // Comincia con
					ApplyRule.bRuleValid = pItem->GetValueEx().Left(strlen(rule.szValue)) == rule.szValue;
					break;

				case CEndoGridParameterRulesSet::major: // Maggiore
					if (rule.bNumeric || pItem->IsValueExNumeric())
						ApplyRule.bRuleValid = atof(pItem->GetValueEx()) > atof(rule.szValue);
					else
						ApplyRule.bRuleValid = strcmp(pItem->GetValueEx(), rule.szValue) > 0;
					break;

				case CEndoGridParameterRulesSet::minor: // Minore
					if (rule.bNumeric || pItem->IsValueExNumeric())
						ApplyRule.bRuleValid = atof(pItem->GetValueEx()) < atof(rule.szValue);
					else
						ApplyRule.bRuleValid = strcmp(pItem->GetValueEx(), rule.szValue) < 0;
					break;

				case CEndoGridParameterRulesSet::minor_major: // Minore maggiore
					if (rule.bNumeric || pItem->IsValueExNumeric())
					{
						CNumberList listNumber;
						listNumber.SetString(rule.szValue);
						if (listNumber.GetCount() == 2)
						{
							ApplyRule.bRuleValid = atof(pItem->GetValueEx()) < listNumber.GetAt(0) &&
								atof(pItem->GetValueEx()) > listNumber.GetAt(1);
						}
					}
					break;

				case CEndoGridParameterRulesSet::different: // Diverso
					ApplyRule.bRuleValid = (pItem->GetValueEx() != rule.szValue);
					break;

				case CEndoGridParameterRulesSet::contains: // Contiene
					ApplyRule.bRuleValid = pItem->GetValueEx().Find(rule.szValue) >= 0;
					break;

				default:
					ApplyRule.bRuleValid = FALSE;
					ASSERT(FALSE);
					break;
				}

				TRACE("%li. Regola ID %li di tipo %li (\"%s\") su campo %s con valore \"%s\" da applicare %li su campo %li!\n",
					++iCounter,
					rule.lID,
					rule.RuleType,
					rule.szValue,
					pItem->GetCaption(),
					pItem->GetValueEx(),
					ApplyRule.bRuleValid,
					ApplyRule.lFieldID);
				pListApplyRule->AddTail(ApplyRule);
			}
		}
	}

	for (int i = 0; i < GetCategories()->GetCount(); i++)
	{
		CXTPPropertyGridItem* pCategory = GetCategories()->GetAt(i);
		for (int j = 0; j < pCategory->GetChilds()->GetCount(); j++)
		{
			CXTPPropertyGridItem* pItem = pCategory->GetChilds()->GetAt(j);
			if (pItems->Find(pItem))
				continue;

			for (POSITION pos = m_listRules.GetHeadPosition(); pos;)
			{
				tagFIELDRULE rule = m_listRules.GetNext(pos);
				if (((rule.lFieldID << 2) >> 2) == pItem->GetID())
				{
					tagAPPLYRULE ApplyRule;
					ApplyRule.lID = rule.lID;
					ApplyRule.RuleType = rule.RuleType;
					ApplyRule.lFieldID = rule.lFieldToHide;
					ApplyRule.clColor = rule.clColor;

					if (strcmp(rule.szValue, "DATA ODIERNA") == 0)
					{
						CString strNow = theApp.GetServerDate();
						strcpy_s(rule.szValue, strNow.Mid(6, 2) + "/" + strNow.Mid(4, 2) + "/" + strNow.Mid(0, 4));
					}

					switch (rule.Operator)
					{
					case CEndoGridParameterRulesSet::equal: // Uguale a
						ApplyRule.bRuleValid = (pItem->GetValueEx() == rule.szValue);
						break;

					case CEndoGridParameterRulesSet::valid: // Valorizzato
						ApplyRule.bRuleValid = !pItem->GetValueEx().IsEmpty();
						break;

					case CEndoGridParameterRulesSet::startwith: // Comincia con
						ApplyRule.bRuleValid = pItem->GetValueEx().Left(strlen(rule.szValue)) == rule.szValue;
						break;

					case CEndoGridParameterRulesSet::major: // Maggiore
						if (rule.bNumeric || pItem->IsValueExNumeric())
							ApplyRule.bRuleValid = atof(pItem->GetValueEx()) > atof(rule.szValue);
						else
							ApplyRule.bRuleValid = strcmp(pItem->GetValueEx(), rule.szValue) > 0;
						break;

					case CEndoGridParameterRulesSet::minor: // Minore
						if (rule.bNumeric || pItem->IsValueExNumeric())
							ApplyRule.bRuleValid = atof(pItem->GetValueEx()) < atof(rule.szValue);
						else
							ApplyRule.bRuleValid = strcmp(pItem->GetValueEx(), rule.szValue) < 0;
						break;

					case CEndoGridParameterRulesSet::minor_major: // Minore maggiore
						if (rule.bNumeric || pItem->IsValueExNumeric())
						{
							CNumberList listNumber;
							listNumber.SetString(rule.szValue);
							if (listNumber.GetCount() == 2)
							{
								ApplyRule.bRuleValid = atof(pItem->GetValueEx()) < listNumber.GetAt(0) &&
									atof(pItem->GetValueEx()) > listNumber.GetAt(1);
							}
						}
						break;

					case CEndoGridParameterRulesSet::different: // Diverso
						ApplyRule.bRuleValid = (pItem->GetValueEx() != rule.szValue);
						break;

					case CEndoGridParameterRulesSet::contains: // Contiene
						ApplyRule.bRuleValid = pItem->GetValueEx().Find(rule.szValue) >= 0;
						break;

					default:
						ApplyRule.bRuleValid = FALSE;
						ASSERT(FALSE);
						break;
					}

					TRACE("%li. Regola ID %li di tipo %li (\"%s\") su campo %s con valore \"%s\" da applicare %li su campo %li!\n",
						++iCounter,
						rule.lID,
						rule.RuleType,
						rule.szValue,
						pItem->GetCaption(),
						pItem->GetValueEx(),
						ApplyRule.bRuleValid,
						ApplyRule.lFieldID);
					pListApplyRule->AddTail(ApplyRule);
				}
			}
		}
	}

	for (POSITION pos = m_listRules.GetHeadPosition(); pos;)
	{
		tagFIELDRULE rule = m_listRules.GetNext(pos);
		long lFieldID = (rule.lFieldID << 2) >> 2;

		tagAPPLYRULE ApplyRule;
		ApplyRule.lID = rule.lID;
		ApplyRule.RuleType = rule.RuleType;
		ApplyRule.lFieldID = rule.lFieldToHide;
		ApplyRule.clColor = rule.clColor;
		ApplyRule.bRuleValid = FALSE;

		if (strcmp(rule.szValue, "DATA ODIERNA") == 0)
		{
			CString strNow = theApp.GetServerDate();
			strcpy_s(rule.szValue, strNow.Mid(6, 2) + "/" + strNow.Mid(4, 2) + "/" + strNow.Mid(0, 4));
		}

		pListApplyRule->AddTail(ApplyRule);
	}
}

void CEndoGrid::ApplyRules(const CEndoGridCLItems* pItems, CList<tagAPPLYRULE>* pListRule)
{
	//Applico per ciascun campo una volta sola il suo aspetto di default
	//Se la regola è hidefield di default è visualizzato
	//Se la regola è showfield di default è nascosto
	CList<tagRULEPROCESSED> listFieldProcessed;
	for (INT_PTR i = 0; i < pListRule->GetCount(); i++)
	{
		tagAPPLYRULE rule = pListRule->GetAt(pListRule->FindIndex(i));
		if (rule.RuleType == CEndoGridParameterRulesSet::valorizefield)
			continue;

		BOOL bContinue = TRUE;
		for (POSITION pos = listFieldProcessed.GetHeadPosition(); pos;)
		{
			tagRULEPROCESSED rp = listFieldProcessed.GetNext(pos);
			if (rp.lFieldID == rule.lFieldID)
			{
				if ((rp.RuleType == CEndoGridParameterRulesSet::hidefield && rule.RuleType == CEndoGridParameterRulesSet::hidefield) ||
					(rp.RuleType == CEndoGridParameterRulesSet::showfield && rule.RuleType == CEndoGridParameterRulesSet::showfield) ||
					(rp.RuleType == CEndoGridParameterRulesSet::hidefield && rule.RuleType == CEndoGridParameterRulesSet::showfield) ||
					(rp.RuleType == CEndoGridParameterRulesSet::showfield && rule.RuleType == CEndoGridParameterRulesSet::hidefield))
				{
					bContinue = FALSE;
					break;
				}
			}
		}

		if (!bContinue)
			continue;

		BOOL bHiddenDefault = FALSE;
		if (rule.RuleType == CEndoGridParameterRulesSet::showfield)
			bHiddenDefault = TRUE;

		for (POSITION pos = pItems->GetHeadPosition(); pos;)
		{
			CXTPPropertyGridItem* pItem = pItems->GetNext(pos);
			if (pItem->GetID() == rule.lFieldID)
			{
				if (rule.RuleType == CEndoGridParameterRulesSet::colorfield)
					pItem->GetValueMetrics()->m_clrBack.SetDefaultValue();
				else
					pItem->SetHidden(bHiddenDefault);
				break;
			}
		}

		tagRULEPROCESSED rp;
		rp.lFieldID = rule.lFieldID;
		rp.RuleType = rule.RuleType;
		listFieldProcessed.AddTail(rp);
	}

	// Se la regola è valida allora la applico...
	for (INT_PTR i = 0; i < pListRule->GetCount(); i++)
	{
		tagAPPLYRULE rule = pListRule->GetAt(pListRule->FindIndex(i));

		for (POSITION pos = pItems->GetHeadPosition(); pos;)
		{
			CXTPPropertyGridItem* pItem = pItems->GetNext(pos);
			if (pItem->GetID() == rule.lFieldID)
			{
				switch (rule.RuleType)
				{
				case CEndoGridParameterRulesSet::hidefield:
					if (rule.bRuleValid)
					{
						TRACE("Regola %li hidefield su campo %li - %s applicata!\n", rule.lID, rule.lFieldID, pItem->GetCaption());
						pItem->SetValue("");
						pItem->SetHidden(TRUE);
					}
					break;

				case CEndoGridParameterRulesSet::showfield:
					if (rule.bRuleValid)
						pItem->SetHidden(FALSE);
					break;

				case CEndoGridParameterRulesSet::colorfield:
					if (rule.bRuleValid)
						pItem->GetValueMetrics()->m_clrBack.SetCustomValue(rule.clColor);
					break;

				case CEndoGridParameterRulesSet::valorizefield:
					if (rule.bRuleValid && pItem->GetValueEx().IsEmpty())
						pItem->SetValue(rule.szNewValue);
					break;

				default:
					ASSERT(FALSE);
					break;
				}
				break;
			}
		}
	}
}

void CEndoGrid::ExpandAll()
{
	CXTPPropertyGridItems* pItems = GetCategories();
	for (int i = 0; i < pItems->GetCount(); i++)
		pItems->GetAt(i)->Expand();
}