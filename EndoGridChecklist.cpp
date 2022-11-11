#include "stdafx.h"
#include "Endox.h"
#include "EndoGridChecklist.h"

#include "EndoGridCLDatiEsameSet.h"
#include "EndoGridCLParameterSet.h"
#include "EsamiView.h"
#include "EsamiSet.h"
#include "EtichetteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridChecklist, CEndoGrid)

CEndoGridChecklist::CEndoGridChecklist(CEsamiView *pEsamiView, long lIndex)
: CEndoGrid(CEndoGridChecklist::GetIdentifier("GRIDCL", lIndex))
{
	m_lIdEtichetta = CEtichetteSet().GetId("GRIDCL", lIndex);
	m_pEsamiView = pEsamiView;
	m_crCampoObbligatorio = RGB(255, 255, 255);
}


CEndoGridChecklist::~CEndoGridChecklist()
{
}

BEGIN_MESSAGE_MAP(CEndoGridChecklist, CEndoGrid)
END_MESSAGE_MAP()

void CEndoGridChecklist::DoDataExchange(CDataExchange* pDX)
{
	CEndoGrid::DoDataExchange(pDX);
}

BOOL CEndoGridChecklist::Create(CWnd* pParentWnd, UINT nID)
{
	return CEndoGrid::Create(pParentWnd, nID);
}

void CEndoGridChecklist::InitializeItems()
{
	// Rimozione elementi in griglia...
	m_GeneralItemList.Truncate(); //Non usare RemoveAll!
	//m_SpecificItemList.RemoveAll();
	//m_FormulaItemList.RemoveAll();
	//m_listColorItemID.Reset();
	m_listRequiredField.Reset();
}

void CEndoGridChecklist::Init()
{
	ResetContent();
	InitializeItems();

	EnableMarkup(TRUE);
}

void CEndoGridChecklist::InsertGeneralField(long lVersionID, long lParentID, CXTPPropertyGridItem* pParentItem)
{
	if (lParentID == 0 && pParentItem == NULL)
	{
		if (lVersionID == 0)
			return;

		CEndoGridCLParameterSet setCategory(TRUE);
		CString strFilter;
		strFilter.Format("IDETICHETTA_GRIDCL = %li AND (idpadre IS NULL or idpadre=-1) AND idversione = %li",
			m_lIdEtichetta,
			lVersionID);
		setCategory.SetOpenFilter(strFilter);
		setCategory.SetSortRecord("ordine");

		try
		{
			setCategory.OpenRecordset("CEndoGridChecklist::InsertGeneralField");

			while (!setCategory.IsEOF())
			{
				CString strCategory = setCategory.m_sParameterName;
#ifdef _DEBUG
				strCategory.Format("%s %li", setCategory.m_sParameterName, setCategory.m_lId);
#endif

				//
				//Anche per le categorie devo settare il carattere impostato
				int lines = strCategory.Replace("\\n", "<LineBreak/>");
				CString start;
				start.Format("<TextBlock VerticalAlignment='Center' FontSize='%lipt'>", setCategory.m_lFontSize);
				CString end = "</TextBlock>";

				if (setCategory.m_bBold)
				{
					start += "<Bold>";
					end = "</Bold>" + end;
				}

				strCategory = start + strCategory + end;
				//

				CXTPPropertyGridItem* pCategory = AddCategory(strCategory);
				pCategory->Expand();
				pCategory->SetID(setCategory.m_lId);

				pCategory->SetMultiLinesCount(lines + 1);
				pCategory->SetHeight(setCategory.m_lFontSize * (lines + (setCategory.m_lFontSize / 4)));

				if (setCategory.m_bExpanded)
					pCategory->Expand();
				else
					pCategory->Collapse();

				m_GeneralItemList.AddTail(pCategory);

				InsertGeneralField(lVersionID, setCategory.m_lId, pCategory);
				setCategory.MoveNext();
			}
		}
		catch (CDBException* pEx)
		{
			pEx->ReportError();
			pEx->Delete();
		}
		catch (CMemoryException* pEx)
		{
			pEx->ReportError();
			pEx->Delete();
		}

		if (setCategory.IsOpen())
			setCategory.CloseRecordset("CEndoGridChecklist::InsertGeneralField");
	}
	else
	{
		CEndoGridCLParameterSet setItems(TRUE);
		CString strFilter;
		strFilter.Format("IDETICHETTA_GRIDCL = %li AND idpadre = %li AND idversione = %li",
			m_lIdEtichetta,
			lParentID,
			lVersionID);
		setItems.SetOpenFilter(strFilter);
		setItems.SetSortRecord("ordine");
		setItems.IsOpen() ? setItems.RequeryRecordset() : setItems.OpenRecordset("CEndoGridChecklist::InsertGeneralField");
		while (!setItems.IsEOF())
		{
			if (CXTPPropertyGridItem* pItem = setItems.CreateItem())
			{
				pParentItem->AddChildItem(pItem);
				pItem->SetID(setItems.m_lId);

				if (setItems.m_bExpanded)
					pItem->Expand();
				else
					pItem->Collapse();

				m_GeneralItemList.AddTail(pItem);
				InsertGeneralField(lVersionID, setItems.m_lId, pItem);

				/*if (setItems.m_bChangeColor)
				m_listColorItemID.Add(setItems.m_lId);*/
				if (setItems.m_bRequired)
					m_listRequiredField.Add(setItems.m_lId);

			}

			setItems.MoveNext();
		}
	}
}

LRESULT CEndoGridChecklist::OnExamChanged(WPARAM wParam, LPARAM lParam)
{
	CEndoGrid::OnExamChanged(wParam, lParam);

	if (m_pEsamiView == NULL)
		return 0;

	Init();

	InsertGeneralField(m_pEsamiView->m_pEsamiSet->m_lVersioneGridCL);

	LoadGeneralData();

	CList<tagAPPLYRULE> listApplyRule;
	AnalyzeRules(&m_GeneralItemList, &listApplyRule);
	ApplyRules(&m_GeneralItemList, &listApplyRule);

	SetReadOnly(theApp.m_nProgramMode == NOTHING_MODE);

	UpdateData(FALSE);
	return 0;
}

LRESULT CEndoGridChecklist::OnExamUpdate(WPARAM wParam, LPARAM lParam)
{
	CEndoGrid::OnExamUpdate(wParam, lParam);

	SaveGeneralData();

	return 0;
}

LRESULT CEndoGridChecklist::OnExamUndo(WPARAM wParam, LPARAM lParam)
{
	CEndoGrid::OnExamUndo(wParam, lParam);

	SetReadOnly(TRUE);

	LoadGeneralData();

	return 0;
}

void CEndoGridChecklist::SetReadOnly(BOOL bEnable)
{
	CEndoGrid::SetReadOnly(bEnable);
}

BOOL CEndoGridChecklist::IsObbligaroryField(CXTPPropertyGridItem* pItem)
{
	if (m_GeneralItemList.Find(pItem))
		return m_listRequiredField.IsPresent(pItem->GetID());

	return CEndoGrid::IsObbligaroryField(pItem);
}

LRESULT CEndoGridChecklist::OnGridNotify(WPARAM wParam, LPARAM lParam)
{
	CEndoGrid::OnGridNotify(wParam, lParam);

	switch (wParam)
	{
	case XTP_PGN_ITEMVALUE_CHANGED:
	{
		if (m_pEsamiView == NULL)
			return 0;

		CList<tagAPPLYRULE> listApplyRule;
		AnalyzeRules(&m_GeneralItemList, &listApplyRule);
		ApplyRules(&m_GeneralItemList, &listApplyRule);
		break;
	}
	}

	return 0;
}

void CEndoGridChecklist::SaveGeneralData()
{
	CEndoGridCLDatiEsameSet set;
	CString strFilter;

	try
	{
		for (POSITION pos = m_GeneralItemList.GetHeadPosition(); pos;)
		{
			CXTPPropertyGridItem* pItem = m_GeneralItemList.GetNext(pos);
			if (pItem->IsCategory())
				continue;

			strFilter.Format("idesame = %li AND idparametro = %li", m_pEsamiView->m_pEsamiSet->m_lContatore, pItem->GetID());
			set.SetOpenFilter(strFilter);
			if (set.OpenRecordset("CEndoGridChecklist::SaveGeneralData"))
			{
				if (set.IsEOF() || set.IsBOF())
				{
					if (!set.AddNewRecordset("CEndoGridChecklist::SaveGeneralData")) //Davide - Replica OK
						return;

					set.m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
					set.m_lIDParametro = pItem->GetID();
				}
				else
				{
					if (!set.EditRecordset("CEndoGridChecklist::SaveGeneralData"))
						return;
				}

				// Davide - risoluzione bug Humanitas caricamento griglie
				set.m_bDatoBool = FALSE;
				set.m_lDatoInt = 0;
				set.m_fDatoFloat = 0.0;
				set.m_sDatoStringa = "";
				set.m_lColore = -1;
				//

				CDataExchange de(this, TRUE);

				if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemDouble)))
				{
					DDX_GridItem(&de, (CEndoGridItemDouble*)pItem, set.m_fDatoFloat, (CAMBaseSet*)&set);
					// Davide - risoluzione bug Humanitas caricamento griglie
					/*set.SetFieldNull(&set.m_bDatoBool);
					set.SetFieldNull(&set.m_lDatoInt);
					set.SetFieldNull(&set.m_sDatoStringa);*/
				}
				else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemBool)))
				{
					DDX_GridItem(&de, (CEndoGridItemBool*)pItem, set.m_bDatoBool, (CAMBaseSet*)&set);
					// Davide - risoluzione bug Humanitas caricamento griglie
					/*set.SetFieldNull(&set.m_lDatoInt);
					set.SetFieldNull(&set.m_fDatoFloat);
					set.SetFieldNull(&set.m_sDatoStringa);*/
				}
				else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemCheck)))
				{
					DDX_GridItem(&de, (CEndoGridItemCheck*)pItem, set.m_bDatoBool, (CAMBaseSet*)&set);
					// Davide - risoluzione bug Humanitas caricamento griglie
					/*set.SetFieldNull(&set.m_lDatoInt);
					set.SetFieldNull(&set.m_fDatoFloat);
					set.SetFieldNull(&set.m_sDatoStringa);*/
				}
				else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemNumber)))
				{
					DDX_GridItem(&de, (CEndoGridItemNumber*)pItem, set.m_lDatoInt, (CAMBaseSet*)&set);
					// Davide - risoluzione bug Humanitas caricamento griglie
					/*set.SetFieldNull(&set.m_bDatoBool);
					set.SetFieldNull(&set.m_fDatoFloat);
					set.SetFieldNull(&set.m_sDatoStringa);*/
				}
				else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemEdit)) ||
					pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemNotes)))
				{
					DDX_GridItem(&de, (CEndoGridItemEdit*)pItem, set.m_sDatoStringa, (CAMBaseSet*)&set);
					// Davide - risoluzione bug Humanitas caricamento griglie
					/*set.SetFieldNull(&set.m_bDatoBool);
					set.SetFieldNull(&set.m_lDatoInt);
					set.SetFieldNull(&set.m_fDatoFloat);*/
				}
				else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemDate)))
				{
					DDX_GridItem(&de, (CEndoGridItemDate*)pItem, set.m_sDatoStringa, (CAMBaseSet*)&set);
					// Davide - risoluzione bug Humanitas caricamento griglie
					/*set.SetFieldNull(&set.m_bDatoBool);
					set.SetFieldNull(&set.m_lDatoInt);
					set.SetFieldNull(&set.m_fDatoFloat);*/
				}

				if (pItem->GetValueMetrics()->m_clrBack.IsCustomValue())
					set.m_lColore = (COLORREF)pItem->GetValueMetrics()->m_clrBack;
				// Davide - risoluzione bug Humanitas caricamento griglie
				//else 
				//	set.SetFieldNull(&set.m_lColore);

				BOOL bHidden = FALSE;
				CXTPPropertyGridItem* pCurrentItem = pItem;
				while (pCurrentItem)
				{
					if (pCurrentItem->IsHidden())
					{
						bHidden = TRUE;
						break;
					}

					if (pCurrentItem->IsCategory())
						break;

					pCurrentItem = pCurrentItem->GetParentItem();
				}

				if (bHidden)
				{
					// Davide - risoluzione bug Humanitas caricamento griglie
					/*
					set.SetFieldNull(&set.m_bDatoBool);
					set.SetFieldNull(&set.m_lDatoInt);
					set.SetFieldNull(&set.m_fDatoFloat);
					set.SetFieldNull(&set.m_sDatoStringa);*/
				}

				set.UpdateRecordset("CEndoGridChecklist::SaveGeneralData");

				set.CloseRecordset("CEndoGridChecklist::SaveGeneralData");
			}
		}
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}

}

void CEndoGridChecklist::LoadGeneralData()
{
	CEndoGridCLDatiEsameSet set;
	CString strFilter;

	try
	{
		for (POSITION pos = m_GeneralItemList.GetHeadPosition(); pos;)
		{
			CXTPPropertyGridItem* pItem = m_GeneralItemList.GetNext(pos);
			if (pItem->IsCategory())
				continue;

			strFilter.Format("idesame = %li AND idparametro = %li", m_pEsamiView->m_pEsamiSet->m_lContatore, pItem->GetID());
			set.SetOpenFilter(strFilter);
			if (set.OpenRecordset("CEndoGridChecklist::LoadGeneralData"))
			{
				if (!set.IsEOF() && !set.IsBOF())
				{
					CDataExchange de(this, FALSE);
					if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemDouble)))
					{
						DDX_GridItem(&de, (CEndoGridItemDouble*)pItem, set.m_fDatoFloat, (CAMBaseSet*)&set);
					}
					else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemBool)))
					{
						DDX_GridItem(&de, (CEndoGridItemBool*)pItem, set.m_bDatoBool, (CAMBaseSet*)&set);
					}
					else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemCheck)))
					{
						DDX_GridItem(&de, (CEndoGridItemCheck*)pItem, set.m_bDatoBool, (CAMBaseSet*)&set);
					}
					else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemNumber)))
					{
						DDX_GridItem(&de, (CEndoGridItemNumber*)pItem, set.m_lDatoInt, (CAMBaseSet*)&set);
					}
					else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemEdit)) ||
						pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemNotes)))
					{
						DDX_GridItem(&de, (CEndoGridItemEdit*)pItem, set.m_sDatoStringa, (CAMBaseSet*)&set);
					}
					else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemDate)))
					{
						DDX_GridItem(&de, (CEndoGridItemDate*)pItem, set.m_sDatoStringa, (CAMBaseSet*)&set);
					}

					if (!set.IsFieldNull(&set.m_lColore) && set.m_lColore >= 0)
						pItem->GetValueMetrics()->m_clrBack.SetCustomValue(set.m_lColore);
				}
				else
				{
					//Se non ho record, procedo con i valori di default
					if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemDouble)))
					{
						((CEndoGridItemDouble*)pItem)->SetDouble(CEndoGridCLParameterSet().GetDefaultFloatValue(pItem->GetID()));
					}
					else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemBool)))
					{
						((CEndoGridItemBool*)pItem)->SetBool(CEndoGridCLParameterSet().GetDefaultBoolValue(pItem->GetID()));
					}
					else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemCheck)))
					{
						((CEndoGridItemCheck*)pItem)->SetBool(CEndoGridCLParameterSet().GetDefaultBoolValue(pItem->GetID()));
					}
					else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemNumber)))
					{
						((CEndoGridItemNumber*)pItem)->SetNumber(CEndoGridCLParameterSet().GetDefaultLongValue(pItem->GetID()));
					}
					else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemEdit)) ||
						pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemNotes)))
					{
						((CEndoGridItemEdit*)pItem)->SetValue(CEndoGridCLParameterSet().GetDefaultValue(pItem->GetID()));
					}
					else if (pItem->IsKindOf(RUNTIME_CLASS(CEndoGridItemDate)))
					{
						((CEndoGridItemDate*)pItem)->SetDate(CEndoGridCLParameterSet().GetDefaultValue(pItem->GetID()));
					}
				}

				set.CloseRecordset("CEndoGridChecklist::LoadGeneralData");
			}
		}
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
}

BOOL CEndoGridChecklist::CheckObbligatoryField(CObbligatoryFieldErrorList* pList, CXTPPropertyGridItem* pItemParent)
{
	BOOL bReturn = TRUE;

	for (POSITION pos = m_GeneralItemList.GetHeadPosition(); pos;)
	{
		CXTPPropertyGridItem* pItem = m_GeneralItemList.GetNext(pos);

		if (m_listRequiredField.IsPresent(pItem->GetID()))
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
	}

	return bReturn;
}

BOOL CEndoGridChecklist::FocusObbligatoryField(long lFieldID, CXTPPropertyGridItem* pItemParent)
{
	BOOL bReturn = FALSE;
	for (POSITION pos = m_GeneralItemList.GetHeadPosition(); pos;)
	{
		CXTPPropertyGridItem* pItem = m_GeneralItemList.GetNext(pos);

		if (m_listRequiredField.IsPresent(pItem->GetID()) && pItem->GetID() == lFieldID)
		{
			pItem->Select();
			bReturn = TRUE;
			break;
		}
	}

	return bReturn;
}

COLORREF CEndoGridChecklist::GetRequiredFieldColor()
{
	return m_crCampoObbligatorio;
}

void  CEndoGridChecklist::SetRequiredFieldColor(COLORREF color)
{
	m_crCampoObbligatorio = color;
}

CString CEndoGridChecklist::GetIdentifier(CString name, long id)
{
	CString temp;
	temp.Format("%s_%li", name, id);
	return temp;
}