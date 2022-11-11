#include "stdafx.h"
#include "Endox.h"
#include "ModifyGridCLConfigDlg.h"

#include "ChangeCheckDlg.h"
#include "ChangeDescriptionDlg.h"
#include "EndoGridCLOptionDlg.h"
#include "EndoGridCLParameterSet.h"
#include "EndoGridCLVersionSet.h"

#include "EtichetteSet.h"
//#include "UserFieldsParameterSet.h"
//#include "UserFieldsVersionSet.h"
//#include "UserFieldOptionDlg.h"
//#include "InsertUserFieldParameter.h"
//
//#include "ConfigSet.h"
//#include "UserFieldsExamSet.h"
//#include "UserFieldsParameterExamTypeSet.h"

// CModifyFieldAnamnesisDlg dialog

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CModifyGridCLConfigDlg, CXTResizeDialog)

CModifyGridCLConfigDlg::CModifyGridCLConfigDlg(CWnd* pParent, int iIndex)
: CXTResizeDialog(CModifyGridCLConfigDlg::IDD, pParent)
{
	m_bAddNewVersion = FALSE;
	m_lIDEtichetta = CEtichetteSet().GetId("GRIDCL", iIndex);
}

CModifyGridCLConfigDlg::~CModifyGridCLConfigDlg()
{
}

void CModifyGridCLConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_ctrlTree);
	DDX_Control(pDX, IDOK, m_ctrlOK);

	DDX_Control(pDX, IDC_ADD_CAT, m_ctrlButton1);
	DDX_Control(pDX, IDC_ADD_FIELD, m_ctrlButton2);
	DDX_Control(pDX, IDC_REMOVE_FIELD, m_ctrlButton3);
}

BEGIN_MESSAGE_MAP(CModifyGridCLConfigDlg, CXTResizeDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, OnNMDblclkTreeFields)

	ON_BN_CLICKED(IDC_ADD_CAT, OnAddCategory)
	ON_BN_CLICKED(IDC_ADD_FIELD, OnAddField)
	ON_BN_CLICKED(IDC_RENAME_FIELD, OnRenameField)
	ON_BN_CLICKED(IDC_REMOVE_FIELD, OnRemoveField)

	ON_BN_CLICKED(IDC_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_DOWN, OnButtonDown)

END_MESSAGE_MAP()

// CModifyFieldAnamnesisDlg message handlers

BOOL CModifyGridCLConfigDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	SetResize(IDC_TREE, 0.0f, 0.0f, 1.0f, 1.0f);
	SetResize(IDC_ADD_CAT, 0.0f, 1.0f, 0.0f, 1.0f);
	SetResize(IDC_ADD_FIELD, 0.0f, 1.0f, 0.0f, 1.0f);
	SetResize(IDC_RENAME_FIELD, 0.0f, 1.0f, 0.0f, 1.0f);
	SetResize(IDC_REMOVE_FIELD, 0.0f, 1.0f, 0.0f, 1.0f);
	SetResize(IDC_DOWN, 1.0f, 0.5f, 1.0f, 0.5f);
	SetResize(IDC_UP, 1.0f, 0.5f, 1.0f, 0.5f);
	SetResize(IDC_LINE, 0.0f, 1.0f, 1.0f, 1.0f);
	SetResize(IDOK, 1, 1, 1, 1);

	//FillExamTypeTree();
	RefreshGridCLFields();

	GetDlgItem(IDOK)->SetFocus();

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	theApp.LocalizeDialog(this, CModifyGridCLConfigDlg::IDD, "ModifyGridCLConfigDlg");
	return FALSE;
}

void CModifyGridCLConfigDlg::OnOK()
{
	CDialog::OnOK();
}

void CModifyGridCLConfigDlg::OnAddCategory()
{
	CChangeDescriptionDlg dlg(theApp.GetMessageString(IDS_ADD_CATEGORY),
		theApp.GetMessageString(IDS_CATEGORY_NAME),
		theApp.GetMessageString(IDS_DESCRIZIONE),
		theApp.GetMessageString(IDS_NOTE),
		"",
		"",
		"",
		10,
		FALSE,
		this);
	if (dlg.DoModal() != IDOK || dlg.m_strDescription1.IsEmpty())
		return;

	CEndoGridCLVersionSet setVersion;

	if (!m_bAddNewVersion)
	{
		//m_lLastUserGridVersion contiene la versione attuale per questa UO
		long tempVersion = theApp.m_lLastGridCLVersion;
		long newVersion = CEndoGridCLVersionSet().GetLastGridVersion() + 1;
		CEndoGridCLVersionSet().DuplicateVersion(tempVersion, newVersion); //Prendo l'ultimo assoluto e lo incremento di 1
		theApp.m_lLastGridCLVersion = newVersion;
		m_bAddNewVersion = TRUE;
	}

	long lParameterID = CEndoGridCLParameterSet().Insert(dlg.m_strDescription1.Left(255),
		dlg.m_strDescription2.Left(255),
		dlg.m_strDescription3.Left(255),
		m_lIDEtichetta,
		CEndoGridCLParameterSet::FIELD_TYPE::type_combo,
		m_ctrlTree.GetCount() + 1,
		-1,
		dlg.m_bCheckBold, 
		atoi(dlg.m_strFontSize));

	if (lParameterID == -1)
		return;

	CString strDescription;
	if (!dlg.m_strDescription3.IsEmpty())
		strDescription = dlg.m_strDescription1.Left(255) + " - " + dlg.m_strDescription3.Left(255);
	else
		strDescription = dlg.m_strDescription1.Left(255);

	HTREEITEM hItem = m_ctrlTree.InsertItem(strDescription);
	m_ctrlTree.SetItemData(hItem, lParameterID);
	m_ctrlTree.EnsureVisible(hItem);

	if (setVersion.OpenRecordset("CModifyGridCLConfigDlg::OnAddCategory"))
	{
		if (setVersion.AddNewRecordset("CModifyGridCLConfigDlg::OnAddCategory"))
		{
			setVersion.m_lParameterID = lParameterID;
			setVersion.m_lVersionID = theApp.m_lLastGridCLVersion;
			setVersion.UpdateRecordset("CModifyGridCLConfigDlg::OnAddCategory");
		}

		setVersion.CloseRecordset("CModifyGridCLConfigDlg::OnAddCategory");
	}
}

void CModifyGridCLConfigDlg::OnAddField()
{
	HTREEITEM hItemSelected = m_ctrlTree.GetSelectedItem();
	if (hItemSelected == NULL)
		return;

	CChangeDescriptionDlg dlg(theApp.GetMessageString(IDS_ADD_FIELD),
		theApp.GetMessageString(IDS_FIELD_NAME),
		theApp.GetMessageString(IDS_DESCRIZIONE),
		theApp.GetMessageString(IDS_NOTE),
		"",
		"",
		"",
		10,
		FALSE,
		this);
	if (dlg.DoModal() != IDOK || dlg.m_strDescription1.IsEmpty())
		return;

	CEndoGridCLVersionSet setVersion;

	if (!m_bAddNewVersion)
	{
		//m_lLastUserGridVersion contiene la versione attuale per questa UO
		long tempVersion = theApp.m_lLastGridCLVersion;
		long newVersion = CEndoGridCLVersionSet().GetLastGridVersion() + 1;
		CEndoGridCLVersionSet().DuplicateVersion(tempVersion, newVersion); //Prendo l'ultimo assoluto e lo incremento di 1
		theApp.m_lLastGridCLVersion = newVersion;
		m_bAddNewVersion = TRUE;
	}

	long lParameterID = CEndoGridCLParameterSet().Insert(dlg.m_strDescription1.Left(255),
		dlg.m_strDescription2.Left(255),
		dlg.m_strDescription3.Left(255),
		m_lIDEtichetta,
		CEndoGridCLParameterSet::FIELD_TYPE::type_combo,
		m_ctrlTree.GetCount() + 1,
		(long)m_ctrlTree.GetItemData(hItemSelected),
		dlg.m_bCheckBold, 
		atoi(dlg.m_strFontSize));

	if (lParameterID == -1)
		return;

	CString strDescription;
	if (!dlg.m_strDescription3.IsEmpty())
		strDescription = dlg.m_strDescription1.Left(255) + " - " + dlg.m_strDescription3.Left(255);
	else
		strDescription = dlg.m_strDescription1.Left(255);

	HTREEITEM hItem = m_ctrlTree.InsertItem(strDescription, hItemSelected);
	m_ctrlTree.SetItemData(hItem, lParameterID);
	m_ctrlTree.Expand(hItemSelected, TVE_EXPAND);
	m_ctrlTree.EnsureVisible(hItem);

	if (setVersion.OpenRecordset("CModifyGridCLConfigDlg::OnAddField"))
	{
		if (setVersion.AddNewRecordset("CModifyGridCLConfigDlg::OnAddField"))
		{
			setVersion.m_lParameterID = lParameterID;
			setVersion.m_lVersionID = theApp.m_lLastGridCLVersion;
			setVersion.UpdateRecordset("CModifyGridCLConfigDlg::OnAddField");
		}

		setVersion.CloseRecordset("CModifyGridCLConfigDlg::OnAddField");
	}
}

void CModifyGridCLConfigDlg::OnRenameField()
{
	HTREEITEM hItemSelected = m_ctrlTree.GetSelectedItem();
	if (hItemSelected == NULL || theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_USER_FIELD_RENAME_FIELD), MB_YESNO | MB_ICONQUESTION) != IDYES)
		return;

	CEndoGridCLParameterSet set;
	CString strFilter;
	strFilter.Format("id = %li", m_ctrlTree.GetItemData(hItemSelected));
	set.SetOpenFilter(strFilter);

	if (set.OpenRecordset("CModifyGridCLConfigDlg::OnRenameField"))
	{
		if (!set.IsEOF())
		{
			CChangeDescriptionDlg dlg(theApp.GetMessageString(IDS_ADD_FIELD),
				theApp.GetMessageString(IDS_FIELD_NAME),
				theApp.GetMessageString(IDS_DESCRIZIONE),
				theApp.GetMessageString(IDS_NOTE),
				set.m_sParameterName,
				set.m_sDescription,
				set.m_sNotes,
				set.m_lFontSize,
				set.m_bBold,
				this);
			if (dlg.DoModal() == IDOK && !dlg.m_strDescription1.IsEmpty())
			{
				if (set.EditRecordset("CModifyGridCLConfigDlg::OnRenameField"))
				{
					set.m_sParameterName = dlg.m_strDescription1.Left(255);
					set.m_sDescription = dlg.m_strDescription2.Left(255);
					set.m_sNotes = dlg.m_strDescription3.Left(255);
					set.m_lFontSize = atoi(dlg.m_strFontSize);
					set.m_bBold = dlg.m_bCheckBold;
					set.UpdateRecordset("CModifyGridCLConfigDlg::OnRenameField");
				}

				CString strDescription;
				if (!dlg.m_strDescription3.IsEmpty())
					strDescription = dlg.m_strDescription1.Left(255) + " - " + dlg.m_strDescription3.Left(255);
				else
					strDescription = dlg.m_strDescription1.Left(255);

				m_ctrlTree.SetItemText(hItemSelected, strDescription);
				m_ctrlTree.RedrawWindow();
			}
		}

		set.CloseRecordset("CModifyGridCLConfigDlg::OnRenameField");
	}
}

void CModifyGridCLConfigDlg::OnRemoveField()
{
	HTREEITEM hItemSelected = m_ctrlTree.GetSelectedItem();
	if (hItemSelected == NULL || theApp.AfxMessageBoxEndo("Rimuovere il campo selezionato?", MB_YESNO | MB_ICONQUESTION) != IDYES)
		return;

	CEndoGridCLVersionSet setVersion;
	CString strFilter;

	if (!m_bAddNewVersion)
	{
		long tempVersion = theApp.m_lLastGridCLVersion;
		long newVersion = CEndoGridCLVersionSet().GetLastGridVersion() + 1;
		CEndoGridCLVersionSet().DuplicateVersion(tempVersion, newVersion); //Prendo l'ultimo assoluto e lo incremento di 1
		theApp.m_lLastGridCLVersion = newVersion;
		m_bAddNewVersion = TRUE;
	}

	//Cancello dalla versione
	strFilter.Format("idparametro = %li AND idversione = %li",
		(long)m_ctrlTree.GetItemData(hItemSelected),
		theApp.m_lLastGridCLVersion);

	CEndoGridCLVersionSet versionSet;
	versionSet.SetOpenFilter(strFilter);

	if (versionSet.OpenRecordset("CModifyGridCLConfigDlg::OnRemoveField"))
	{
		if (!versionSet.IsEOF())
			versionSet.DeleteRecordset("CModifyGridCLConfigDlg::OnRemoveField");

		versionSet.CloseRecordset("CModifyGridCLConfigDlg::OnRemoveField");
	}

	//Cancello il parametro
	strFilter.Format("id = %li",
		(long)m_ctrlTree.GetItemData(hItemSelected));

	CEndoGridCLParameterSet paramSet;
	paramSet.SetOpenFilter(strFilter);

	if (paramSet.OpenRecordset("CModifyGridCLConfigDlg::OnRemoveField"))
	{
		if (!paramSet.IsEOF())
			paramSet.DeleteRecordset("CModifyGridCLConfigDlg::OnRemoveField");

		paramSet.CloseRecordset("CModifyGridCLConfigDlg::OnRemoveField");
	}

	m_ctrlTree.DeleteItem(hItemSelected);
}

void CModifyGridCLConfigDlg::OnButtonUp()
{
	if (!m_ctrlTree.MoveSelectedUp())
		return;

	UpdateTreeOrder(&m_ctrlTree);
}

void CModifyGridCLConfigDlg::OnButtonDown()
{
	if (!m_ctrlTree.MoveSelectedDown())
		return;

	UpdateTreeOrder(&m_ctrlTree);
}

void CModifyGridCLConfigDlg::OnNMDblclkTreeFields(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	HTREEITEM hItemSelected = m_ctrlTree.GetSelectedItem();
	if (!hItemSelected)
		return;

	CEndoGridCLParameterSet set;
	CString strFilter;
	strFilter.Format("id = %li", m_ctrlTree.GetItemData(hItemSelected));
	set.SetOpenFilter(strFilter);

	if (set.OpenRecordset("CModifyGridCLConfigDlg::OnNMDblclkTreeFields"))
	{
		if (!set.IsEOF() && !set.IsBOF())
		{
			if (m_ctrlTree.GetParentItem(hItemSelected) == NULL) // Categoria
			{
				CChangeCheckDlg dlg(theApp.GetMessageString(IDS_EXPANDED_ITEM_CHECK), this);
				dlg.SetCheckValue1(set.m_bExpanded);
				if (dlg.DoModal() == IDOK)
				{
					if (set.EditRecordset("CModifyGridCLConfigDlg::OnNMDblclkTreeFields"))
					{
						set.m_bExpanded = dlg.GetCheckValue1();
						set.UpdateRecordset("CModifyGridCLConfigDlg::OnNMDblclkTreeFields");
					}
				}
			}
			else
			{
				if (set.EditRecordset("CModifyGridCLConfigDlg::OnNMDblclkTreeFields"))
				{
					CEndoGridCLOptionDlg dlg(&set, this);
					if (dlg.DoModal() == IDOK)
						set.UpdateRecordset("CModifyGridCLConfigDlg::OnNMDblclkTreeFields");
					else
						set.CancelUpdateRecordset("CModifyGridCLConfigDlg::OnNMDblclkTreeFields");
				}
			}
		}

		set.CloseRecordset("CModifyGridCLConfigDlg::OnNMDblclkTreeFields");
	}
}

void CModifyGridCLConfigDlg::UpdateTreeOrder(CSortableTreeCtrl* pTreeCtrl, HTREEITEM hItemParent)
{
	HTREEITEM hItemFirstLevel = pTreeCtrl->GetRootItem();
	if (hItemParent != NULL)
		hItemFirstLevel = hItemParent;

	try
	{
		UINT iCounter = 1;
		while (hItemFirstLevel)
		{
			CString sFilter;
			sFilter.Format("ID=%li", pTreeCtrl->GetItemData(hItemFirstLevel));
			CEndoGridCLParameterSet tempSet;
			tempSet.SetOpenFilter(sFilter);

			if (tempSet.OpenRecordset("CModifyGridCLConfigDlg::UpdateTreeOrder"))
			{
				if (!tempSet.IsEOF())
				{
					if (tempSet.EditRecordset("CModifyGridCLConfigDlg::UpdateTreeOrder"))
					{
						tempSet.m_lOrder = iCounter++;

						tempSet.UpdateRecordset("CModifyGridCLConfigDlg::UpdateTreeOrder");
					}
				}

				tempSet.CloseRecordset("CModifyGridCLConfigDlg::UpdateTreeOrder");
			}

			if (HTREEITEM hItemChild = pTreeCtrl->GetChildItem(hItemFirstLevel))
				UpdateTreeOrder(pTreeCtrl, hItemChild);

			hItemFirstLevel = pTreeCtrl->GetNextSiblingItem(hItemFirstLevel);
		}
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
}

void CModifyGridCLConfigDlg::RefreshGridCLFields(HTREEITEM hItemParent)
{
	if (hItemParent == NULL)
		m_ctrlTree.DeleteAllItems();

	CString strFilter;
	if (hItemParent == NULL)
		strFilter.Format("IDETICHETTA_GRIDCL = %li AND (idpadre IS NULL or idpadre=-1) AND idversione = %li",
		m_lIDEtichetta,
		theApp.m_lLastGridCLVersion);
	else
		strFilter.Format("IDETICHETTA_GRIDCL = %li AND idpadre = %li AND idversione = %li",
		m_lIDEtichetta,
		m_ctrlTree.GetItemData(hItemParent),
		theApp.m_lLastGridCLVersion);

	CEndoGridCLParameterSet setItems(TRUE);
	setItems.SetOpenFilter(strFilter);
	setItems.SetSortRecord("ordine");

	if (setItems.OpenRecordset("CModifyGridCLConfigDlg::RefreshGridCLFields"))
	{
		while (!setItems.IsEOF())
		{
			CString strDescription;
			if (!setItems.m_sNotes.IsEmpty())
				strDescription = setItems.m_sParameterName + " - " + setItems.m_sNotes;
			else
				strDescription = setItems.m_sParameterName;

			HTREEITEM hItem = m_ctrlTree.InsertItem(strDescription, hItemParent);
			m_ctrlTree.SetItemData(hItem, setItems.m_lId);

			RefreshGridCLFields(hItem);

			m_ctrlTree.Expand(hItem, TVE_EXPAND);
			setItems.MoveNext();
		}

		setItems.CloseRecordset("CModifyGridCLConfigDlg::RefreshGridCLFields");
	}

	if (hItemParent == NULL)
		m_ctrlTree.EnsureVisible(m_ctrlTree.GetRootItem());
}



