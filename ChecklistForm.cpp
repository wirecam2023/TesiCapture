#include "stdafx.h"
#include "Endox.h"
#include "ChecklistForm.h"
#include "Common.h"

#include "CheckListItemRegoleSet.h"
#include "CheckListItemSet.h"
#include "CheckListSet.h"
#include "CodiciClassificazioneDiagnosticaSet.h"
#include "EditStringDlg.h"
#include "EsamiCodiciClassDiagnostSet.h"
#include "EsamiView.h"
#include "LogFileWriter.h"
#include "MeasurementsSet.h" //Luiz - 01/07/2019 - P3 - Permitir combobox de variáveis de laudo exibir até 200 caracteres
#include "MeasurementsAliasMappingSet.h" //Luiz - 01/07/2019 - P3 - Permitir combobox de variáveis de laudo exibir até 200 caracteres
#include "MmSystem.h"
#include "VistaChecklistItemRegoleSet.h"
#include "VistaCheckListSet.h"
#include "ExtPrestazioniSet.h"
#include "DialogWithResizableCombo.h" //Luiz - 01/07/2019 - P3 - Permitir combobox de variáveis de laudo exibir até 200 caracteres
#include "SelectNumeroFichaDlg.h"
#include "ImageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_RICARICAFRASE		1001
#define TIMER_RICARICAFRASEITEM 1002

CChecklistForm::CChecklistForm(CWnd* pParentWnd, CEsamiView* pEsamiView)
	: CEndoxDynForm(CChecklistForm::IDD, pParentWnd, pEsamiView)
{
	m_lIDChecklist = 0;
	m_lIDItem = 0;
}

CChecklistForm::~CChecklistForm()
{
	while (m_listVariables.GetCount() > 0)
	{
		VARIABLES* pVar = m_listVariables.GetTail();
		m_listVariables.RemoveTail();

		if (pVar != NULL)
		{
			delete pVar;
			pVar = NULL;
		}
	}
}

BEGIN_MESSAGE_MAP(CChecklistForm, CEndoxDynForm)

	ON_BN_CLICKED(IDC_BTN_APRI, OnBnClickedBtnApri)
	ON_BN_CLICKED(IDC_BTN_CHIUDI, OnBnClickedBtnChiudi)
	ON_BN_CLICKED(IDC_BTN_IMPORT, OnBnClickedBtnImport)

	ON_CBN_SELCHANGE(IDC_COMBO_CHECKLIST, OnCbnSelchangeComboChecklist)
	ON_BN_CLICKED(IDC_CHK_MOSTRATODAS, OnBnClickedChkMostraTodas) // Luiz - 10/04/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo

	ON_MESSAGE(WM_ITEM_CHECK_CHANGED, OnItemCheckChanged)

	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnTvnSelchangedTree)

	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_BTN_IMAGENS, &CChecklistForm::OnBnClickedBtnImagens)
END_MESSAGE_MAP()

void CChecklistForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_APRI, m_ctrlButtonApri);
	DDX_Control(pDX, IDC_BTN_CHIUDI, m_ctrlButtonChiudi);
	DDX_Control(pDX, IDC_BTN_IMPORT, m_ctrlButtonImport);
	DDX_Control(pDX, IDC_BTN_IMAGENS, m_ctrlButtonImagens);

	DDX_Control(pDX, IDC_COMBO_CHECKLIST, m_ctrlComboChecklist);
	DDX_Control(pDX, IDC_CHK_MOSTRATODAS, m_ctrlChkMostraTodas); // Luiz - 10/04/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo

	DDX_Control(pDX, IDC_LIST_CODICI, m_ctrlListCodiciClassificazione);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);

	DDX_Control(pDX, IDC_TEXTCONTROL_HIDE, m_ctrlTextControlHide);
	m_ctrlTextControlHide.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //

	DDX_Control(pDX, IDC_TEXTCONTROL_ITEM, m_ctrlTextControlItem);
	m_ctrlTextControlItem.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //

	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //

	DDX_Control(pDX, IDC_TREE, m_ctrlTree);
}

void CChecklistForm::OnDestroy()
{
	for (POSITION pos = m_listRegole2.GetHeadPosition(); pos;)
		delete m_listRegole2.GetNext(pos).pListItemBind;

	CEndoxDynForm::OnDestroy();
}

BOOL CChecklistForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	//m_ctrlChkMostraTodas.SetCheck(BST_CHECKED);// Luiz - 24/04/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo
	m_ctrlTree.SetNotificationCheckMessage(WM_ITEM_CHECK_CHANGED);

	m_ctrlListCodiciClassificazione.SetExtendedStyle(m_ctrlListCodiciClassificazione.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListCodiciClassificazione.InsertColumn(0, theApp.GetMessageString(IDS_CODICE), LVCFMT_LEFT);
	m_ctrlListCodiciClassificazione.InsertColumn(1, theApp.GetMessageString(IDS_DESCRIZIONE), LVCFMT_LEFT);
	m_ctrlListCodiciClassificazione.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListCodiciClassificazione.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	AddAnchor(IDC_STATIC_00, CSize(0, 0), CSize(0, 0));

	// FIX: estes objetos estavam se sobrepondo quando redimensionado para menor o diálogo.
	// Ajustado também o posicionamento no RESOURCE IDD_SUBFORM_CHECKLIST
	AddAnchor(IDC_COMBO_CHECKLIST, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_CHK_MOSTRATODAS, CSize(0, 0), CSize(0, 0));

	// Luiz - 10/04/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo
	/*
	if (GetSystemMetrics(SM_CYSCREEN) < 800)
	{
		AddAnchor(IDC_CHK_MOSTRATODAS, CSize(100, 0), CSize(110, 0));
	}
	else
	{
		AddAnchor(IDC_CHK_MOSTRATODAS, CSize(50, 0), CSize(60, 0));
	}
	*/


	AddAnchor(IDC_BTN_APRI, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_BTN_CHIUDI, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_BTN_IMPORT, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_BTN_IMAGENS, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_TREE, CSize(0, 0), CSize(100, 100));

	AddAnchor(IDC_STATIC_01, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDC_TEXTCONTROLITEM_PLACE, CSize(0, 100), CSize(100, 100));

	AddAnchor(IDC_STATIC_02, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDC_TEXTCONTROL_PLACE, CSize(0, 100), CSize(100, 100));

	/*AddAnchor(IDC_STATIC_01, CSize(0, 50), CSize(100, 50));
	AddAnchor(IDC_TEXTCONTROLITEM_PLACE, CSize(0, 50), CSize(100, 50));

	AddAnchor(IDC_STATIC_02, CSize(0, 50), CSize(100, 50));
	AddAnchor(IDC_TEXTCONTROL_PLACE, CSize(0, 50), CSize(100, 100));*/

	// AddAnchor(IDC_LIST_CODICI, CSize(0, 100), CSize(100, 100));

	//

	OnBnClickedChkMostraTodas(); //Luiz - 02/05/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo
	//RiempiComboChecklist();

	//
	GetDlgItem(IDC_BTN_IMAGENS)->EnableWindow(TRUE);

	theApp.LocalizeDialog(this, CChecklistForm::IDD, "ChecklistForm");
	m_ctrlTree.SetFocus();

	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#1 - dual screen)
	if (theApp.m_bConfigFormRefertoBtnImgAutomated)
	{
		OnBnClickedBtnImagens();
	}

	return FALSE;
}

void CChecklistForm::OnSize(UINT nType, int cx, int cy)
{
	CEndoxDynForm::OnSize(nType, cx, cy);

	CWnd* pTextControlItemPlace = GetDlgItem(IDC_TEXTCONTROLITEM_PLACE);
	if (pTextControlItemPlace && m_ctrlTextControlItem.GetSafeHwnd())
	{
		CRect rect;
		pTextControlItemPlace->GetWindowRect(rect);
		ScreenToClient(&rect);
		m_ctrlTextControlItem.SetWindowPos(GetDlgItem(IDC_TEXTCONTROLITEM_PLACE),
			rect.left + 1,
			rect.top + 1,
			rect.Width() - 2,
			rect.Height() - 2, 0);
	}

	CWnd* pTextControlPlace = GetDlgItem(IDC_TEXTCONTROL_PLACE);
	if (pTextControlPlace && m_ctrlTextControl.GetSafeHwnd())
	{
		CRect rect;
		pTextControlPlace->GetWindowRect(rect);
		ScreenToClient(&rect);
		m_ctrlTextControl.SetWindowPos(GetDlgItem(IDC_TEXTCONTROL_PLACE),
			rect.left + 1,
			rect.top + 1,
			rect.Width() - 2,
			rect.Height() - 2, 0);
	}
}

void CChecklistForm::OnTimer(UINT nIDEvent)
{
	KillTimer(nIDEvent);

	switch (nIDEvent)
	{
		case TIMER_RICARICAFRASE:
		{
			RicaricaFrase();
			break;
		}
		case TIMER_RICARICAFRASEITEM:
		{
			RicaricaFraseTemp();
			break;
		}
	}
}

BOOL CChecklistForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, CChecklistForm** pForm)
{
	BOOL bResult = FALSE;

	if ((*pForm) == NULL)
	{
		(*pForm) = new CChecklistForm(NULL, pEsamiView);
		if ((*pForm) != NULL)
		{
			(*pForm)->m_pParentFrame = pParentFrame;
			(*pForm)->m_lColore = -1;
			(*pForm)->m_lIDFaseBlocco = 2;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			(*pForm)->CreateChildForm(CChecklistForm::IDD, pParent, rectFrame);
		}
	}

	return bResult;
}

long CChecklistForm::GetContenuto()
{
	return -1;
}

BOOL CChecklistForm::CampoObbligatorioValido()
{
	return TRUE;
}

//Luiz - 10/04/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo
CString CChecklistForm::GetPrestazione()
{
	CString sReturn = "";

	CString sIdPrestazione = m_pEsamiView->m_pEsamiSet->m_sCodEsame;

	CExtPrestazioniSet setPrest;
	CString sFilter;
	sFilter.Format("IDPRESTAZIONE LIKE '%s'", sIdPrestazione);
	setPrest.SetOpenFilter(sFilter);

	if (setPrest.OpenRecordset("CChecklistForm::GetPrestazione") && !setPrest.IsEOF())
	{
		sReturn = setPrest.m_sCodicePrestazione;
		setPrest.CloseRecordset("CChecklistForm::GetPrestazione");
	}

	return sReturn;
}

void CChecklistForm::RiempiComboChecklist()
{	
	CString strFilter;
	//Luiz - 10/04/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo
	BOOL bMostrarTodas = m_ctrlChkMostraTodas.GetCheck() == BST_CHECKED;
	m_ctrlComboChecklist.ResetContent();
	m_listChecklist.RemoveAll();

	if (!bMostrarTodas)
	{
		CString sCodicePrestazione = GetPrestazione();
		//Julio 03/08/2018
		if (sCodicePrestazione.IsEmpty())
			strFilter.Format("IDTipoEsame=%li AND CampoCL=999", m_pEsamiView->m_pEsamiSet->m_lIDEsame);
		else
			strFilter.Format("IDTipoEsame=%li AND CampoCL=999 AND Descrizione='%s'", m_pEsamiView->m_pEsamiSet->m_lIDEsame, sCodicePrestazione);

		CVistaCheckListSet viewCL;
		viewCL.SetOpenFilter(strFilter);
		
		// Marvel BUG 4094 - Combo Checklists filtradas deve ser vazio por default (ORDEM ALFABÉTICA DO CODICE SEMPRE)
		//Julio - BUG 3736 - Ordenar Combo
		//if (sCodicePrestazione.IsEmpty())
			viewCL.SetSortRecord("Codice");
		//else
		//	viewCL.SetSortRecord("Descrizione");
		//
		
		if (viewCL.OpenRecordset("CChecklistForm::RiempiComboChecklist"))
		{
			while (!viewCL.IsEOF())
			{
				STRUCT_CHECKLIST tagTemp;
				tagTemp.m_lID = viewCL.m_lID;
				tagTemp.m_sCodice = viewCL.m_sCodice;
				tagTemp.m_sDescrizione = viewCL.m_sDescrizione;
				tagTemp.m_lIDTipoEsame = viewCL.m_lIDTipoEsame;
				tagTemp.m_lCampoCL = viewCL.m_lCampoCL;
				tagTemp.m_lOrdine = viewCL.m_lOrdine;
				m_listChecklist.AddTail(tagTemp);

				viewCL.MoveNext();
			}

			viewCL.CloseRecordset("CChecklistForm::RiempiComboChecklist");
		}
	}

	if (m_listChecklist.GetCount() == 0)
	{
		strFilter.Format("IDTipoEsame=%li AND CampoCL=999", m_pEsamiView->m_pEsamiSet->m_lIDEsame);
		
		CVistaCheckListSet viewCL;
		viewCL.SetOpenFilter(strFilter);
		
		//Julio - BUG 3736 - Ordenar Combo
		//viewCL.SetSortRecord("Descrizione");
		viewCL.SetSortRecord("Codice");
		//
		
		if (viewCL.OpenRecordset("CChecklistForm::RiempiComboChecklist"))
		{
			while (!viewCL.IsEOF())
			{
				STRUCT_CHECKLIST tagTemp;
				tagTemp.m_lID = viewCL.m_lID;
				tagTemp.m_sCodice = viewCL.m_sCodice;
				tagTemp.m_sDescrizione = viewCL.m_sDescrizione;
				tagTemp.m_lIDTipoEsame = viewCL.m_lIDTipoEsame;
				tagTemp.m_lCampoCL = viewCL.m_lCampoCL;
				tagTemp.m_lOrdine = viewCL.m_lOrdine;
				m_listChecklist.AddTail(tagTemp);

				viewCL.MoveNext();
			}

			viewCL.CloseRecordset("CChecklistForm::RiempiComboChecklist");
		}
	}
}

void CChecklistForm::ProcessItemCheckChanged(HTREEITEM hItem)
{	
	BOOL bChecked = m_ctrlTree.GetCheck(hItem);
		
	if (bChecked)
	{
		//////////////////////////////////////////////
		// l'item sta passando da NON-CHECK a CHECK //
		//////////////////////////////////////////////

		if (m_listIDCheckListItems.Find(m_ctrlTree.GetItemData(hItem)) == NULL)
		{
			m_listIDCheckListItems.AddTail(m_ctrlTree.GetItemData(hItem));

			HTREEITEM hTreePadre = NULL;

			// seleziono l'elemento //
			m_ctrlTree.SelectItem(hItem);

			// espando l'elemento //
			m_ctrlTree.Expand(hItem, TVE_EXPAND);

			// eventualmente, se a scelta singola, tolgo i check dai fratelli //
			UncheckFratelli(hItem);

			// metto il check anche su tutti gli elementi superiori in cascata //
			CheckPadre(hItem);

			// Sandro 15/03/2010 - aggiungo la gestione delle @variabili@ //
			long lIDItem = (long)m_ctrlTree.GetItemData(hItem);
			if (lIDItem > 0)
			{
				CString sText = GetTestoVariabili(lIDItem);
				if (!sText.IsEmpty())
				{
					ChiediValoriCombo(lIDItem, sText);
					ChiediValori(lIDItem, sText);
				}
			}

			// Verifica regola di check automatico...
			CList<long> listItemToCheck;
			for (POSITION pos = m_listRegole.GetHeadPosition(); pos;)
			{
				tagREGOLA tr = m_listRegole.GetNext(pos);
				if (tr.lTipoRegola != 3)
					continue;

				if (tr.lIDItem == m_ctrlTree.GetItemData(hItem))
					listItemToCheck.AddTail(tr.lIDItemBind);
			}

			if (listItemToCheck.GetCount() > 0)
			{
				for (POSITION pos = listItemToCheck.GetHeadPosition(); pos;)
				{
					HTREEITEM hItemNew = GetItemFromID(listItemToCheck.GetNext(pos));
					m_ctrlTree.SetCheck(hItemNew, TRUE);
					
					ProcessItemCheckChanged(hItemNew);			
				}
			}
			//

			// aggiorno il testo sotto //
			SetTimer(TIMER_RICARICAFRASEITEM, 100, NULL);

			// aggiorno il testo a destra - uso il timer per far passare un po' di tempo altrimenti l'item che sto checkando non risulta checkato //
			SetTimer(TIMER_RICARICAFRASE, 100, NULL);

		}
	}
	else
	{
		//////////////////////////////////////////////
		// l'item sta passando da CHECK a NON-CHECK //
		//////////////////////////////////////////////

		if (POSITION pos = m_listIDCheckListItems.Find(m_ctrlTree.GetItemData(hItem)))
		{
			m_listIDCheckListItems.RemoveAt(pos);

			// seleziono l'elemento //
			m_ctrlTree.SelectItem(hItem);

			// tolgo il check anche su tutti gli elementi inferiori //
			UncheckRamo(hItem);

			// Sandro 15/03/2010 - aggiungo la gestione delle @variabili@ //
			long lIDItem = (long)m_ctrlTree.GetItemData(hItem);
			if (lIDItem > 0)
			{
				POSITION pos = m_listVariables.GetHeadPosition();
				while (pos != NULL)
				{
					VARIABLES* pVal = m_listVariables.GetAt(pos);

					POSITION posDel = NULL;
					if (pVal->lIDItem == lIDItem)
						posDel = pos;

					m_listVariables.GetNext(pos);

					if (posDel != NULL)
					{
						delete pVal;
						m_listVariables.RemoveAt(posDel);
					}
				}
			}

			// aggiorno il testo sotto //
			SetTimer(TIMER_RICARICAFRASEITEM, 100, NULL);

			// aggiorno il testo a destra - uso il timer per far passare un po' di tempo altrimenti l'item che sto decheckando non risulta decheckato //
			SetTimer(TIMER_RICARICAFRASE, 100, NULL);
		}
	}
	
	ASSERT(m_ctrlTree.GetCheckedItemCount() == m_listIDCheckListItems.GetCount());		
}

LRESULT CChecklistForm::OnItemCheckChanged(WPARAM wParam, LPARAM lParam)
{
	BeginWaitCursor();
	m_ctrlTree.EnableWindow(FALSE);
	m_ctrlTree.SetNotificationCheckMessage(0);
	HTREEITEM hItem = (HTREEITEM)wParam;
	
	//
	TraceAndLog("CChecklistForm::OnItemCheckChanged --> ProcessItemCheckChanged inizio");	
	DWORD timeProcess = timeGetTime();
	ProcessItemCheckChanged(hItem);
	timeProcess = timeGetTime() - timeProcess;	
	TraceAndLog("CChecklistForm::OnItemCheckChanged --> ProcessItemCheckChanged fine", (long)timeProcess);
	//

	//
	TraceAndLog("CChecklistForm::OnItemCheckChanged --> AnalyzeAllRules inizio");	
	DWORD timeRules = timeGetTime();
	AnalyzeAllRules();
	timeRules = timeGetTime() - timeRules;
	TraceAndLog("CChecklistForm::OnItemCheckChanged --> AnalyzeAllRules fine", (long)timeRules);
	//

	m_ctrlTree.SetNotificationCheckMessage(WM_ITEM_CHECK_CHANGED);
	m_ctrlTree.EnableWindow(TRUE);
	EndWaitCursor();

	m_ctrlTree.SetFocus();
	return 0;
}

void CChecklistForm::ChiediValori(long lIDItem, CString& sText)
{
	/* NON devo cancellarle altrimenti me le chiede tutte le volte! //
	// cancello tutte le variabili memorizzate relative all'item interessato //
	POSITION pos = m_listVariables.GetHeadPosition();
	while(pos != NULL)
	{
		VARIABLES* pVal = m_listVariables.GetAt(pos);

		POSITION posDel = NULL;
		if(pVal->lIDItem == lIDItem)
			posDel = pos;

		m_listVariables.GetNext(pos);

		if(posDel != NULL)
		{
			delete pVal;
			m_listVariables.RemoveAt(posDel);
		}
	}
	*/

	// ora cerco le variabili contenute nel testo dell'item interessato e chiedo il valore di ciascuna //
	long lVariable = 0;
	int iTemp = sText.Find('@');
	int iTempCombo = sText.Find("@COMBO");
	int iTempPrev = iTemp;
	while (iTemp >= 0)
	{
		if (lVariable % 2 != 0 && iTemp != iTempCombo && iTempPrev != iTempCombo)
		{
			// sono su una chiocciola che dovrebbe chiudere una variabile //

			CString sTitle = sText.Mid(iTempPrev + 1, (iTemp - iTempPrev) - 1);

			// prima di chiedere il valore cerco in memoria se ho già il valore della @variabile@ //
			BOOL bFound = FALSE;
			POSITION pos = m_listVariables.GetHeadPosition();
			while (pos != NULL)
			{
				VARIABLES* pVal = m_listVariables.GetNext(pos);
				if (pVal != NULL)
				{
					if ((pVal->lIDItem == lIDItem) && (pVal->sVariable == "@" + sTitle + "@"))
					{
						bFound = TRUE;
						break;
					}
				}
			}

			// se non l'ho trovato chiedo di inserirlo //
			if (!bFound)
			{				
				/*CEditStringDlg dlg(this, sTitle, "");
				dlg.SetEsamiView(m_pEsamiView);
				if (dlg.DoModal() == IDOK)
				{
					VARIABLES* pVar = new VARIABLES;
					if (pVar != NULL)
					{
						pVar->lIDItem = lIDItem;
						pVar->sVariable = "@" + sTitle + "@";
						pVar->sValue = dlg.GetValue();
						m_listVariables.AddTail(pVar);
					}
				}
				else
				{
					VARIABLES* pVar = new VARIABLES;
					if (pVar != NULL)
					{
						pVar->lIDItem = lIDItem;
						pVar->sVariable = "@" + sTitle + "@";
						pVar->sValue = "@" + sTitle + "@";
						m_listVariables.AddTail(pVar);
					}
				}*/
				CString sMeasurementValue = FindVariableValue(m_pEsamiView->m_pEsamiSet->m_lContatore, "@" + sTitle + "@");
				if (sMeasurementValue.GetLength() > 0)
				{
					VARIABLES* pVar = new VARIABLES;
					if (pVar != NULL)
					{
						pVar->lIDItem = lIDItem;
						pVar->sVariable = "@" + sTitle + "@";
						pVar->sValue = sMeasurementValue;
						m_listVariables.AddTail(pVar);
					}
				}
				else
				{
					CEditStringDlg dlg(this, sTitle, "");
					dlg.SetEsamiView(m_pEsamiView);
					if (dlg.DoModal() == IDOK)
					{
						VARIABLES* pVar = new VARIABLES;
						if (pVar != NULL)
						{
							pVar->lIDItem = lIDItem;
							pVar->sVariable = "@" + sTitle + "@";
							pVar->sValue = dlg.GetValue();
							m_listVariables.AddTail(pVar);
						}
					}
					else
					{
						VARIABLES* pVar = new VARIABLES;
						if (pVar != NULL)
						{
							pVar->lIDItem = lIDItem;
							pVar->sVariable = "@" + sTitle + "@";
							pVar->sValue = "@" + sTitle + "@";
							m_listVariables.AddTail(pVar);
						}
					}
				}
			}
		}

		iTempPrev = iTemp;

		lVariable++;
		iTemp = sText.Find('@', iTemp + 1);
	}
}

CString CChecklistForm::FindVariableValue(long lIDEsame, CString sVariableName)
{
	CString sValue = "";
	CString sAlias = "";
	CMeasurementsAliasMappingSet mappingSet;

	CString sFilter;
	sFilter.Format("VARIABLENAME='%s'", sVariableName);

	mappingSet.SetOpenFilter(sFilter);
	if (mappingSet.OpenRecordset("CChecklistForm::FindVariableValue"))
	{
		while (!mappingSet.IsEOF())
		{
			sAlias = mappingSet.m_sAlias;
			sValue = "#";

			if (sAlias.GetLength() > 0)
			{
				CMeasurementsSet measurementSet;
				sFilter.Format("IDESAME=%li AND ALIAS='%s'", lIDEsame, sAlias);

				measurementSet.SetOpenFilter(sFilter);
				if (measurementSet.OpenRecordset("CChecklistForm::FindVariableValue"))
				{
					if (!measurementSet.IsEOF())

					{
						if (theApp.m_bMedidasBiometricasUsaCodeValue && measurementSet.m_sCodeValue.GetLength() > 0)
							sValue = measurementSet.m_sNumericValue + " " + measurementSet.m_sCodeValue.MakeLower();
						else
							sValue = measurementSet.m_sNumericValue;						

						break;
					}
					measurementSet.CloseRecordset("CChecklistForm::FindVariableValue");
				}
			}
			mappingSet.MoveNext();
		}
		mappingSet.CloseRecordset("CChecklistForm::FindVariableValue");
	}
	return sValue;
}

BOOL CChecklistForm::ChiediValoriCombo(long lIDItem, CString& sText)
{	
	long lVariable = 0;
	
	int iHasComboVariables = sText.Find("@COMBO_");
	int iLastComboEndPos = 0;
	while (iHasComboVariables >= 0)
	{
		int iComboPosStart = sText.Find("@COMBO_", iLastComboEndPos) + 7; //removing @combo_
		int iComboPosEnd = sText.Find("_COMBO@", iLastComboEndPos);

		CString sVariable = sText.Mid(iComboPosStart, (iComboPosEnd - iComboPosStart));
		CString sTitolo = "";
	
		long lArrayPos = 0;
		long lArrayCount = 15;
		CString *sArray = new CString[lArrayCount];

		int pos = 0;
		CString resToken;

		resToken = sVariable.Tokenize(";", pos);
		sTitolo = resToken;

		while (resToken != _T(""))
		{
			resToken = sVariable.Tokenize(";", pos);
			//if (resToken != _T(""))					// Marvel BUG 3837 @COMBO com opção vazia 
			//{
				if (lArrayPos < lArrayCount)
				{
					sArray[lArrayPos] = resToken;
					lArrayPos++;
				}
			//}
		}
		if (lArrayCount > 0)
		{
			// prima di chiedere il valore cerco in memoria se ho già il valore della @variabile@ //
			BOOL bFound = FALSE;
			POSITION pos = m_listVariables.GetHeadPosition();
			while (pos != NULL)
			{
				VARIABLES* pVal = m_listVariables.GetNext(pos);
				if (pVal != NULL)
				{
					if ((pVal->lIDItem == lIDItem) && (pVal->sVariable == "@COMBO_" + sVariable + "_COMBO@"))
					{
						bFound = TRUE;
						break;
					}
				}
			}
			if (!bFound)
			{
				// TODO: REFACTORING POSSIBILITY : reavaliar necessidade de 5 FORMS / tentar a abordagem de redimensionar um único
				long lArrayCountNEW = lArrayPos;
				//Luiz - 01/07/2019 - P3 - Permitir combobox de variáveis de laudo exibir até 200 caracteres
				int iMaxLen = 0;
				CString sMaxTxt = "";
				CString *sArrayNEW = new CString[lArrayCountNEW];
				for (int i = 0; i < lArrayCountNEW; i++)
				{
					sArrayNEW[i] = sArray[i];
					if (sArray[i].GetLength() > iMaxLen)
					{
						iMaxLen = sArray[i].GetLength();
						sMaxTxt = sArray[i];
					}
				}
				
				long lRect = CDialogWithResizableCombo().GetRectSize(sMaxTxt);
				CDialogWithResizableCombo dlg(this, sTitolo, sArrayNEW, lArrayCountNEW, lRect, TRUE);

				dlg.SetEsamiView(m_pEsamiView);
				if (dlg.DoModal() == IDOK)
				{
					VARIABLES* pVar = new VARIABLES;
					if (pVar != NULL)
					{
						pVar->lIDItem = lIDItem;
						pVar->sVariable = "@COMBO_" + sVariable + "_COMBO@";
						//pVar->sValue = dlg.m_sSelectedFicha;
						pVar->sValue = dlg.m_sSelectedItem;
						m_listVariables.AddTail(pVar);
					}
				}
				else
				{
					VARIABLES* pVar = new VARIABLES;
					if (pVar != NULL)
					{
						pVar->lIDItem = lIDItem;
						pVar->sVariable = "@COMBO_" + sVariable + "_COMBO@";
						pVar->sValue = "@COMBO_" + sVariable + "_COMBO@";
						m_listVariables.AddTail(pVar);
					}
				}
			}
		}								
		
		lVariable++;
		iHasComboVariables = sText.Find("@COMBO_", iComboPosEnd + 1);
		iLastComboEndPos = iComboPosEnd + 1;
	}

	return lVariable > 0;
}

BOOL CChecklistForm::SetCheck(HTREEITEM hItem, BOOL bCheck)
{
	BOOL bReturn = TRUE;

	// Sandro 19/10/2016 //
	if (m_ctrlTree.GetCheck(hItem) != bCheck)
	{
		if (bCheck)
		{
			// Sandro 16/03/2010 - controllo ed eventualmente chiedo le @variabili@ //
			long lIDItem = (long)m_ctrlTree.GetItemData(hItem);
			if (lIDItem > 0)
			{
				CString sText = GetTestoVariabili(lIDItem);
				if (!sText.IsEmpty())
				{
					ChiediValoriCombo(lIDItem, sText);
					ChiediValori(lIDItem, sText);
				}
			}
		}
		else
		{
			// cancello le @variabili@ memorizzate relative a questo item //
			long lIDItem = (long)m_ctrlTree.GetItemData(hItem);
			if (lIDItem > 0)
			{
				POSITION pos = m_listVariables.GetHeadPosition();
				while (pos != NULL)
				{
					VARIABLES* pVal = m_listVariables.GetAt(pos);

					POSITION posDel = NULL;
					if (pVal->lIDItem == lIDItem)
						posDel = pos;

					m_listVariables.GetNext(pos);

					if (posDel != NULL)
					{
						delete pVal;
						m_listVariables.RemoveAt(posDel);
					}
				}
			}
		}

		bReturn = m_ctrlTree.SetCheck(hItem, bCheck);
		if (bReturn)
		{
			if (bCheck)
			{
				if (m_listIDCheckListItems.Find(m_ctrlTree.GetItemData(hItem)) == NULL)
					m_listIDCheckListItems.AddTail(m_ctrlTree.GetItemData(hItem));
			}
			else
			{
				if (POSITION pos = m_listIDCheckListItems.Find(m_ctrlTree.GetItemData(hItem)))
					m_listIDCheckListItems.RemoveAt(pos);
			}

			//
			/*TRACE0("    CChecklistForm::SetCheck --> AnalyzeAllRules inizio\n");
			CLogFileWriter::Get()->WriteLogLine0("CChecklistForm::SetCheck --> AnalyzeAllRules inizio");

			DWORD timeDurata = timeGetTime();
			AnalyzeAllRules();
			timeDurata = timeGetTime() - timeDurata;

			CString sLog;
			sLog.Format("CChecklistForm::SetCheck --> AnalyzeAllRules fine (%li msec)", (long)timeDurata);
			CLogFileWriter::Get()->WriteLogLine0(sLog);
			TRACE0("    " + sLog + "\n");*/
		}
	}

	ASSERT(m_ctrlTree.GetCheckedItemCount() == m_listIDCheckListItems.GetCount());
	return bReturn;
}

void CChecklistForm::SostituisciVariabili(long lIDItem, CString& strRTF, CString& strTXT)
{
	// metto temporaneamente il testo RTF in un controllo rich //
	m_ctrlTextControlHide.ResetContents();
	m_ctrlTextControlHide.SetRTFSelText(strRTF);

	// ora sostituisco (direttamente nel controllo) il testo di ogni variabile con il suo valore //
	POSITION pos = m_listVariables.GetHeadPosition();
	while (pos != NULL)
	{
		VARIABLES* pVal = m_listVariables.GetNext(pos);
		if (pVal->lIDItem == lIDItem)
		{
			long lFind = strTXT.Find(pVal->sVariable);
			int iLen = pVal->sVariable.GetLength();
						
			while (lFind >= 0)
			{
				m_ctrlTextControlHide.ResetContents();
				m_ctrlTextControlHide.SetRTFSelText(strRTF);

				m_ctrlTextControlHide.SetSelStart(lFind);
				m_ctrlTextControlHide.SetSelLength(iLen);
				
				CString aa = m_ctrlTextControlHide.GetSelText();
				
				m_ctrlTextControlHide.SetSelText(pVal->sValue);				
				
				m_ctrlTextControlHide.SetSelStart(0);
				m_ctrlTextControlHide.SetSelLength(-1);
				strRTF = m_ctrlTextControlHide.GetRTFSelText();
				strTXT = m_ctrlTextControlHide.GetSelText();

				lFind = strTXT.Find(pVal->sVariable, lFind + 1);
			}
		}
	}

	// riprendo il testo modificato //
	m_ctrlTextControlHide.SetSelStart(0);
	m_ctrlTextControlHide.SetSelLength(-1);
	strRTF = m_ctrlTextControlHide.GetRTFSelText();
	strTXT = m_ctrlTextControlHide.GetSelText();

	m_ctrlTextControlHide.ResetContents();

	if (theApp.m_bRefertoMarcaVariabiliAnnullati)
		SostituisciVariabiliAnnullati(lIDItem, strRTF, strTXT);
}

void CChecklistForm::SostituisciVariabiliAnnullati(long lIDItem, CString& strRTF, CString& strTXT)
{
	// metto temporaneamente il testo RTF in un controllo rich //
	m_ctrlTextControlHide.ResetContents();

	m_ctrlTextControlHide.SetFontBold(FALSE); //Set font to normal
	m_ctrlTextControlHide.SetForeColor(RGB(0, 0, 0));

	m_ctrlTextControlHide.SetRTFSelText(strRTF);

	// ora sostituisco (direttamente nel controllo) il testo di ogni variabile con il suo valore //
	POSITION pos = m_listVariables.GetHeadPosition();
	while (pos != NULL)
	{
		VARIABLES* pVal = m_listVariables.GetNext(pos);
		if (pVal->lIDItem == lIDItem)
		{
			long lFind = strTXT.Find(pVal->sVariable);
			int iLen = pVal->sVariable.GetLength();

			while (lFind >= 0)
			{
				m_ctrlTextControlHide.SetSelStart(lFind);
				m_ctrlTextControlHide.SetSelLength(iLen);

				CString aa = m_ctrlTextControlHide.GetSelText();
				BOOL bFound = FALSE;
				if (aa.Find('@') == 0 && aa.ReverseFind('@') == aa.GetLength() - 1) //confirms its a variable
				{
					m_ctrlTextControlHide.SetFormatSelection(TRUE); //Sets the format type to be cast only for the selection (not the entire control)

					m_ctrlTextControlHide.SetForeColor(RGB(255, 0, 0)); //Set font to bold and red
					m_ctrlTextControlHide.SetFontBold(TRUE);

					lFind = strTXT.Find(pVal->sVariable, lFind + 1);
					bFound = TRUE;
				}

				m_ctrlTextControlHide.SetSelStart(0);
				m_ctrlTextControlHide.SetSelLength(-1);

				if (!bFound)
					lFind = strTXT.Find(pVal->sVariable, lFind + 1);
			}
		}
	}

	// riprendo il testo modificato //
	m_ctrlTextControlHide.SetSelStart(0);
	m_ctrlTextControlHide.SetSelLength(-1);
	strRTF = m_ctrlTextControlHide.GetRTFSelText();
	strTXT = m_ctrlTextControlHide.GetSelText();

	m_ctrlTextControlHide.ResetContents();		
}

void CChecklistForm::OnBnClickedBtnApri()
{
	HTREEITEM hItem = m_ctrlTree.GetRootItem();

	while (hItem != NULL)
	{
		ApriRamo(hItem);
		hItem = m_ctrlTree.GetNextSiblingItem(hItem);
	}
}

void CChecklistForm::OnBnClickedBtnChiudi()
{
	HTREEITEM hItem = m_ctrlTree.GetRootItem();

	while (hItem != NULL)
	{
		ChiudiRamo(hItem);
		hItem = m_ctrlTree.GetNextSiblingItem(hItem);
	}
}

void CChecklistForm::OnBnClickedBtnImport()
{
	// controllo i check obbligatori tra gli item della root //

	BOOL bChecked = FALSE;
	HTREEITEM hItemChild = m_ctrlTree.GetRootItem();
	while (hItemChild)
	{
		TRACE("\tCheck %li %s\n", m_ctrlTree.GetItemData(hItemChild), m_ctrlTree.GetItemText(hItemChild));
		if (m_ctrlTree.GetCheck(hItemChild))
		{
			bChecked = TRUE;
			break;
		}

		hItemChild = m_ctrlTree.GetNextSiblingItem(hItemChild);
	}

	if (!bChecked)
	{
		AfxMessageBox(theApp.GetMessageString(IDS_CHECKLIST_USE_OBBLIGATORYROOT), MB_ICONSTOP);
		return;
	}

	// controllo i check obbligatori tra i subitem selezionati //

	for (POSITION pos = m_listCheckListItemObbligatory.GetHeadPosition(); pos;)
	{
		if (HTREEITEM hItem = GetItemFromID(m_listCheckListItemObbligatory.GetNext(pos)))
		{
			if (!m_ctrlTree.GetCheck(hItem))
				continue;

			TRACE("Controllo check obbligatoria; %li %s\n", m_ctrlTree.GetItemData(hItem), m_ctrlTree.GetItemText(hItem));

			BOOL bChecked = FALSE;
			HTREEITEM hItemChild = m_ctrlTree.GetChildItem(hItem);
			while (hItemChild)
			{
				TRACE("\tCheck %li %s\n", m_ctrlTree.GetItemData(hItemChild), m_ctrlTree.GetItemText(hItemChild));
				if (m_ctrlTree.GetCheck(hItemChild))
				{
					bChecked = TRUE;
					break;
				}

				hItemChild = m_ctrlTree.GetNextSiblingItem(hItemChild);
			}

			if (!bChecked)
			{
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_CHECKLIST_USE_OBBLIGATORY), m_ctrlTree.GetItemText(hItem));
				AfxMessageBox(strError, MB_ICONSTOP);

				m_ctrlTree.SelectItem(hItem);

				return;
			}
		}
	}
	
	// Luiz - 29/04/2019 - P3 - Email no Laudo - Substitui &#64; por @
	CString strRTF = m_ctrlTextControl.GetRTFSelText();
	if (strRTF.Find("&#64;") != -1)
	{
		strRTF.Replace("&#64;", "@");
	}
	m_ctrlTextControl.ResetContents();
	m_ctrlTextControl.SetRTFSelText(strRTF);
	//

	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);
	GetParent()->SendMessage(WM_ADD_RTFTEXT_TO_REPORT, (WPARAM)&m_ctrlTextControl.GetRTFSelText(), (LPARAM)&theApp.m_sTabellaEcocardioTabs);
	m_ctrlTextControl.SetSelLength(0);

	/* if (theApp.m_bCheckListSalvaSelezione)
	{
		// salvo nell'esame l'ID dell'ultima checklist utilizzata //

		BOOL bEsamiModify = theApp.m_nProgramMode & ADD_RECORD_ESAMI || theApp.m_nProgramMode & MODIFY_RECORD_ESAMI;

		BOOL bDoUpdate = FALSE;
		if (!bEsamiModify)
			bDoUpdate = m_pEsamiView->m_pEsamiSet->EditRecordset("CChecklistForm::OnBnClickedBtnImport");

		m_pEsamiView->m_pEsamiSet->m_lIDUltimaChecklistUsata = m_lIDChecklist;

		if (bDoUpdate)
			m_pEsamiView->m_pEsamiSet->UpdateRecordset("CChecklistForm::OnBnClickedBtnImport");

		// salvo nel DB gli item selezionati //

		CList<long> listChecked;
		CList<HTREEITEM> listItems;
		listItems.AddTail(m_ctrlTree.GetRootItem());

		while (listItems.GetCount() > 0)
		{
			HTREEITEM hItem = listItems.RemoveHead();
			if (m_ctrlTree.GetCheck(hItem))
				listChecked.AddTail(m_ctrlTree.GetItemData(hItem));

			if (HTREEITEM hItemSibling = m_ctrlTree.GetNextSiblingItem(hItem))
				listItems.AddTail(hItemSibling);

			if (HTREEITEM hItemChild = m_ctrlTree.GetChildItem(hItem))
				listItems.AddTail(hItemChild);
		}

		ASSERT(listChecked.GetCount() == m_ctrlTree.GetCheckedItemCount());

		CString strFilter;
		strFilter.Format("IDEsame = %li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CEsamiChecklistSet EsamiChecklistSet;
		EsamiChecklistSet.SetOpenFilter(strFilter);
		if (EsamiChecklistSet.OpenRecordset("CCheckListUseDlg::OnCancel"))
		{
			while (!EsamiChecklistSet.IsEOF())
			{
				if (POSITION pos = listChecked.Find(EsamiChecklistSet.m_lIDCheck))
					listChecked.RemoveAt(pos);
				else
					EsamiChecklistSet.DeleteRecordset("CCheckListUseDlg::OnCancel");

				EsamiChecklistSet.MoveNext();
			}

			EsamiChecklistSet.CloseRecordset("CCheckListUseDlg::OnCancel");

			EsamiChecklistSet.SetOpenFilter("ID = 0");
			if (EsamiChecklistSet.OpenRecordset("CCheckListUseDlg::OnCancel"))
			{
				for (POSITION pos = listChecked.GetHeadPosition(); pos;)
				{
					if (EsamiChecklistSet.AddNewRecordset("CCheckListUseDlg::OnCancel"))
					{
						EsamiChecklistSet.m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
						EsamiChecklistSet.m_lIDCheck = listChecked.GetNext(pos);
						EsamiChecklistSet.UpdateRecordset("CCheckListUseDlg::OnCancel");
					}
				}

				EsamiChecklistSet.CloseRecordset("CCheckListUseDlg::OnCancel");
			}
		}
	}
	*/

	// salvo su DB i codici di classificazione diagnostica //

	for (int i = 0; i < m_ctrlListCodiciClassificazione.GetItemCount(); i++)
		CEsamiCodiciClassDiagnostSet().AddRecord(m_pEsamiView->m_pEsamiSet->m_lContatore, m_ctrlListCodiciClassificazione.GetItemData(i));

	// Sandro 10/08/2016 // su indicazione di Pilotto...

	m_lIDItem = 0;

	m_ctrlListCodiciClassificazione.DeleteAllItems();
	m_ctrlTextControl.ResetContents();
	m_ctrlTextControlItem.ResetContents();

	m_listIDCheckListItems.RemoveAll();

	RiempiAlbero();
}

void CChecklistForm::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (HTREEITEM hItemSelected = m_ctrlTree.GetSelectedItem())
		CaricaDati((long)m_ctrlTree.GetItemData(hItemSelected));
	else
		CaricaDati(0);
}

void CChecklistForm::CaricaDati(long lIDItem)
{
	BOOL bAzzera = TRUE;

	m_lIDItem = lIDItem;

	m_ctrlTextControlItem.ResetContents();

	// aggiorno il testo della frase sotto - uso il timer perchè altrimenti l'albero va inspiegabilmente in palla (sbaglia a visualizzare gli elementi selezionati) //
	if (m_lIDItem > 0)
		SetTimer(TIMER_RICARICAFRASEITEM, 100, NULL);
}

void CChecklistForm::RicaricaFraseTemp()
{
	if (m_lIDItem <= 0)
		return;

	CString strRTF;
	CString strTXT;
	long lNumeroVariabili;
	long lIDDiagnosi;
	CString sDiagnosiCodice;
	CString sDiagnosiDescrizione;
	GetTesti(m_lIDItem, strRTF, strTXT, lNumeroVariabili, lIDDiagnosi, sDiagnosiCodice, sDiagnosiDescrizione);

	// Sandro 15/03/2010 - gestione @variabili@ //
	if (lNumeroVariabili > 0)
		SostituisciVariabili(m_lIDItem, strRTF, strTXT);

	m_ctrlTextControlItem.ResetContents();
	m_ctrlTextControlItem.SetRTFSelText(strRTF); 
}

void CChecklistForm::RicaricaFrase(long lParentItemID, long* pRefertoLen)
{
	BeginWaitCursor();

	if (theApp.m_bCheckListComponiSequenzialmente)
	{
		long lRefertoLen = 0;

		m_ctrlTextControl.ResetContents();
		m_listIDCheckListItems.RemoveAll();
		m_ctrlListCodiciClassificazione.DeleteAllItems();

		HTREEITEM hTreeAll = m_ctrlTree.GetRootItem();
		while (hTreeAll != NULL)
		{
			if (m_ctrlTree.GetCheck(hTreeAll))
			{
				long lIDItem = (long)m_ctrlTree.GetItemData(hTreeAll);

				m_listIDCheckListItems.AddTail(lIDItem);

				// --- //

				CString strRTF;
				CString strTXT;
				long lNumeroVariabili;
				long lIDDiagnosi;
				CString sDiagnosiCodice;
				CString sDiagnosiDescrizione;
				GetTesti(lIDItem, strRTF, strTXT, lNumeroVariabili, lIDDiagnosi, sDiagnosiCodice, sDiagnosiDescrizione);
				if (!strTXT.IsEmpty())
				{
					// Sandro 15/03/2010 - gestione @variabili@ //
					if (lNumeroVariabili > 0)
						SostituisciVariabili(lIDItem, strRTF, strTXT);

					m_ctrlTextControl.SetSelStart(lRefertoLen + 1);
					m_ctrlTextControl.SetSelLength(-1);
					m_ctrlTextControl.SetRTFSelText(strRTF);

					lRefertoLen += strTXT.GetLength();

					if (lIDDiagnosi > 0)
					{
						int nItem = m_ctrlListCodiciClassificazione.GetItemCount();

						m_ctrlListCodiciClassificazione.InsertItem(nItem, sDiagnosiCodice);
						m_ctrlListCodiciClassificazione.SetItemData(nItem, lIDDiagnosi);

						m_ctrlListCodiciClassificazione.SetItemText(nItem, 1, sDiagnosiDescrizione);
					}
				}

				// --- //

				RicaricaFraseSub(hTreeAll, lRefertoLen);
			}

			hTreeAll = m_ctrlTree.GetNextSiblingItem(hTreeAll);
		}

		m_ctrlListCodiciClassificazione.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListCodiciClassificazione.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	}
	else
	{
		HTREEITEM hItem = NULL;
		long lRefertoLen = 0;

		if (lParentItemID == 0)
		{
			m_ctrlTextControl.ResetContents();
			m_ctrlListCodiciClassificazione.DeleteAllItems();

			pRefertoLen = &lRefertoLen;
			hItem = m_ctrlTree.GetRootItem();
		}
		else
		{
			HTREEITEM hItemPadre = m_ctrlTree.GetItemFromData(lParentItemID);
			if (hItemPadre == NULL)
				return;

			hItem = m_ctrlTree.GetChildItem(hItemPadre);
		}

		// Metto in una lista gli elementi di questo livello...
		CList<long> listSiblings;
		while (hItem)
		{
			listSiblings.AddTail((long)m_ctrlTree.GetItemData(hItem));
			hItem = m_ctrlTree.GetNextSiblingItem(hItem);
		}

		// Rimuovo dalla lista degli elementi selezionati quelli che non sono di questo livello...
		CList<long> listCheckListLong; // Luiz - 10/04/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo
		listCheckListLong.AddTail(&m_listIDCheckListItems);
		for (INT_PTR i = 0; i < listCheckListLong.GetCount(); i++)
		{
			POSITION pos = listCheckListLong.FindIndex(i);
			if (listSiblings.Find(listCheckListLong.GetAt(pos)) == NULL)
			{
				listCheckListLong.RemoveAt(pos);
				i--;
			}
		}

		// Compongo il testo...
		for (POSITION pos = listCheckListLong.GetHeadPosition(); pos;)
		{
			long lIDItem = listCheckListLong.GetNext(pos);

			CString strRTF;
			CString strTXT;
			long lNumeroVariabili;
			long lIDDiagnosi;
			CString sDiagnosiCodice;
			CString sDiagnosiDescrizione;
			GetTesti(lIDItem, strRTF, strTXT, lNumeroVariabili, lIDDiagnosi, sDiagnosiCodice, sDiagnosiDescrizione);
			if (!strTXT.IsEmpty())
			{
				// Sandro 15/03/2010 - gestione @variabili@ //
				if (lNumeroVariabili > 0)
					SostituisciVariabili(lIDItem, strRTF, strTXT);

				m_ctrlTextControl.SetSelStart((*pRefertoLen) + 1);
				m_ctrlTextControl.SetSelLength(-1);
				m_ctrlTextControl.SetRTFSelText(strRTF);

				(*pRefertoLen) += strTXT.GetLength();

				if (lIDDiagnosi > 0)
				{
					int nItem = m_ctrlListCodiciClassificazione.GetItemCount();

					m_ctrlListCodiciClassificazione.InsertItem(nItem, sDiagnosiCodice);
					m_ctrlListCodiciClassificazione.SetItemData(nItem, lIDDiagnosi);

					m_ctrlListCodiciClassificazione.SetItemText(nItem, 1, sDiagnosiDescrizione);
				}
			}

			// --- //
			RicaricaFrase(lIDItem, pRefertoLen);
		}

		m_ctrlListCodiciClassificazione.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListCodiciClassificazione.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	}

	EndWaitCursor();
}

void CChecklistForm::RicaricaFraseSub(HTREEITEM hItemPadre, long& lRefertoLen)
{
	HTREEITEM hItemFigli = m_ctrlTree.GetNextItem(hItemPadre, TVGN_CHILD);

	while (hItemFigli != NULL)
	{
		if (m_ctrlTree.GetCheck(hItemFigli))
		{
			long lIDItem = (long)m_ctrlTree.GetItemData(hItemFigli);

			m_listIDCheckListItems.AddTail(lIDItem);

			// --- //

			CString strRTF;
			CString strTXT;
			long lNumeroVariabili;
			long lIDDiagnosi;
			CString sDiagnosiCodice;
			CString sDiagnosiDescrizione;
			GetTesti(lIDItem, strRTF, strTXT, lNumeroVariabili, lIDDiagnosi, sDiagnosiCodice, sDiagnosiDescrizione);
			if (!strTXT.IsEmpty())
			{
				// Sandro 15/03/2010 - gestione @variabili@ //
				if (lNumeroVariabili > 0)
					SostituisciVariabili(lIDItem, strRTF, strTXT);

				m_ctrlTextControl.SetSelStart(lRefertoLen + 1);
				m_ctrlTextControl.SetSelLength(-1);
				m_ctrlTextControl.SetRTFSelText(strRTF);

				lRefertoLen += strTXT.GetLength();

				if (lIDDiagnosi > 0)
				{
					int nItem = m_ctrlListCodiciClassificazione.GetItemCount();

					m_ctrlListCodiciClassificazione.InsertItem(nItem, sDiagnosiCodice);
					m_ctrlListCodiciClassificazione.SetItemData(nItem, lIDDiagnosi);

					m_ctrlListCodiciClassificazione.SetItemText(nItem, 1, sDiagnosiDescrizione);
				}
			}

			// --- //

			RicaricaFraseSub(hItemFigli, lRefertoLen);
		}

		hItemFigli = m_ctrlTree.GetNextSiblingItem(hItemFigli);
	}
}

BOOL CChecklistForm::CercaCheckNoSi(HTREEITEM hItem)
{
	BOOL bReturn = FALSE;

	HTREEITEM hItemFigli = m_ctrlTree.GetNextItem(hItem, TVGN_CHILD);
	while (hItemFigli != NULL)
	{
		if (m_ctrlTree.GetCheck(hItemFigli))
		{
			if (m_listIDCheckListItems.Find((long)m_ctrlTree.GetItemData(hItemFigli)) == NULL)
				return TRUE;
		}

		bReturn = CercaCheckNoSi(hItemFigli);
		if (bReturn)
			return TRUE;

		hItemFigli = m_ctrlTree.GetNextSiblingItem(hItemFigli);
	}

	return bReturn;
}

BOOL CChecklistForm::CercaCheckSiNo(HTREEITEM hItem)
{
	BOOL bReturn = FALSE;

	HTREEITEM hItemFigli = m_ctrlTree.GetNextItem(hItem, TVGN_CHILD);
	while (hItemFigli != NULL)
	{
		if (!m_ctrlTree.GetCheck(hItemFigli))
		{
			if (m_listIDCheckListItems.Find((long)m_ctrlTree.GetItemData(hItemFigli)) != NULL)
				return TRUE;
		}

		bReturn = CercaCheckSiNo(hItemFigli);
		if (bReturn)
			return TRUE;

		hItemFigli = m_ctrlTree.GetNextSiblingItem(hItemFigli);
	}

	return bReturn;
}

void CChecklistForm::EnableItems(const CList<long>* pList, BOOL bEnable, HTREEITEM hItemParent)
{
	HTREEITEM hItem = (hItemParent == NULL) ? m_ctrlTree.GetRootItem() : hItemParent;

	while (hItem)
	{
		if (pList->Find(m_ctrlTree.GetItemData(hItem)))
		{
			// TRACE("%s item %li...\n", bEnable ? "Enable" : "Disable", m_ctrlTree.GetItemData(hItem));
			m_ctrlTree.SetCheckEnabled(hItem, bEnable);

			if (!bEnable)
			{
				if (POSITION pos = m_listIDCheckListItems.Find(m_ctrlTree.GetItemData(hItem)))
					m_listIDCheckListItems.RemoveAt(pos);
			}
		}

		if (HTREEITEM hItemChild = m_ctrlTree.GetChildItem(hItem))
			EnableItems(pList, bEnable, hItemChild);

		hItem = m_ctrlTree.GetNextSiblingItem(hItem);
	}

	/* Sandro 19/10/2016
	POSITION pos1 = pList->GetHeadPosition();
	while (pos1 != NULL)
	{
		long lTempID = pList->GetAt(pos1);

		HTREEITEM hItem = (hItemParent == NULL) ? m_ctrlTree.GetRootItem() : hItemParent;
		while (hItem)
		{
			if (m_ctrlTree.GetItemData(hItem) == lTempID)
			{
				TRACE("%s item %li...\n", bEnable ? "Enable" : "Disable", m_ctrlTree.GetItemData(hItem));
				m_ctrlTree.SetCheckEnabled(hItem, bEnable);

				if (!bEnable)
				{
					if (POSITION pos = m_listIDCheckListItems.Find(m_ctrlTree.GetItemData(hItem)))
						m_listIDCheckListItems.RemoveAt(pos);
				}
			}

			if (HTREEITEM hItemChild = m_ctrlTree.GetChildItem(hItem))
				EnableItems(pList, bEnable, hItemChild);

			hItem = m_ctrlTree.GetNextSiblingItem(hItem);
		}

		pList->GetNext(pos1);
	}
	*/
}

void CChecklistForm::CheckPadre(HTREEITEM hItem)
{
	// prendo l'HTREEITEM del padre (che è l'elemento da checkare) //
	HTREEITEM hTreePadre = m_ctrlTree.GetParentItem(hItem);

	// se il padre esiste ed è buono //
	if (hTreePadre != NULL)
	{
		// prima checko suo padre così mi chiede prima le sue eventuali @varibili@ //
		CheckPadre(hTreePadre);

		// eventualmente, se a scelta singola, tolgo i check dai fratelli //
		UncheckFratelli(hTreePadre);

		// ora checko questo item //
		SetCheck(hTreePadre, TRUE);
	}
}

void CChecklistForm::UncheckFratelli(HTREEITEM hItem)
{
	// controllo se gli item sono a scelta singola perchè eventualmente deseleziono tutti gli altri //
	HTREEITEM hTreePadre = m_ctrlTree.GetParentItem(hItem);
	if (hTreePadre == NULL)
	{
		// l'item è nella root //
		if (!GetSceltaMultipla(m_lIDChecklist))
		{
			HTREEITEM hTreeAll = m_ctrlTree.GetRootItem();
			while (hTreeAll != NULL)
			{
				if (hTreeAll != hItem)
				{
					SetCheck(hTreeAll, FALSE);
					UncheckRamo(hTreeAll);
				}

				hTreeAll = m_ctrlTree.GetNextSiblingItem(hTreeAll);
			}
		}
	}
	else
	{
		// l'item è figlio //
		if (!GetSceltaMultipla((long)m_ctrlTree.GetItemData(hTreePadre)))
		{
			HTREEITEM hTreeAll = m_ctrlTree.GetNextItem(hTreePadre, TVGN_CHILD);
			while (hTreeAll != NULL)
			{
				if (hTreeAll != hItem)
				{
					SetCheck(hTreeAll, FALSE);
					UncheckRamo(hTreeAll);
				}

				hTreeAll = m_ctrlTree.GetNextSiblingItem(hTreeAll);
			}
		}
	}
}

void CChecklistForm::CaricaRegole()
{
	CString sFilter;
	sFilter.Format("IDCHECKLIST=%li", m_lIDChecklist);

	CVistaChecklistItemRegoleSet set;
	set.SetOpenFilter(sFilter);
	if (set.OpenRecordset("CCheckListUseDlg::CaricaRegole"))
	{
		while (!set.IsEOF())
		{
			if (set.m_lTipoRegola != 2)
			{
				tagREGOLA tr;
				tr.lIDItem = set.m_lIDChecklistItem;
				tr.lIDItemBind = set.m_lIDChecklistItemBind;
				tr.lTipoRegola = set.m_lTipoRegola;
				m_listRegole.AddTail(tr);
			}
			else
			{
				BOOL bFound = FALSE;
				for (POSITION pos = m_listRegole2.GetHeadPosition(); pos;)
				{
					tagREGOLA2 tr = m_listRegole2.GetNext(pos);
					if (tr.lIDItem == set.m_lIDChecklistItem && tr.lTipoRegola == set.m_lTipoRegola)
					{
						tr.pListItemBind->AddTail(set.m_lIDChecklistItemBind);
						bFound = TRUE;
					}
				}

				if (!bFound)
				{
					tagREGOLA2 tr;
					tr.lTipoRegola = set.m_lTipoRegola;
					tr.lIDItem = set.m_lIDChecklistItem;
					tr.pListItemBind = new CList<long>();
					tr.pListItemBind->AddTail(set.m_lIDChecklistItemBind);
					m_listRegole2.AddTail(tr);
				}
			}

			set.MoveNext();
		}

		set.CloseRecordset("CCheckListUseDlg::CaricaRegole");
	}
}

void CChecklistForm::AnalyzeRules(HTREEITEM hItem)
{
	BOOL bChecked = m_ctrlTree.GetCheck(hItem);
	long lIDItem = m_ctrlTree.GetItemData(hItem);

	CList<long> listItemToDisable;
	for (POSITION pos = m_listRegole.GetHeadPosition(); pos;)
	{
		tagREGOLA tr = m_listRegole.GetNext(pos);
		if (tr.lTipoRegola == 3)
			continue;

		if (tr.lIDItem == lIDItem)
		{
			if (bChecked)
			{
				if (tr.lTipoRegola == 1) // Elementi da disabilitare se check
					listItemToDisable.AddTail(tr.lIDItemBind);
			}
			else
			{
				if (tr.lTipoRegola == 0) // Elementi da disabilitare se non check
					listItemToDisable.AddTail(tr.lIDItemBind);
			}
		}
	}

	if (listItemToDisable.GetCount() > 0)
	{
		// TRACE("Disable %li items...\n", listItemToDisable.GetCount());
		EnableItems(&listItemToDisable, FALSE);
	}
}

void CChecklistForm::AnalyzeRulesType2()
{
	CList<long> listItemToDisable;
	for (POSITION pos = m_listRegole2.GetHeadPosition(); pos;)
	{
		tagREGOLA2 tr = m_listRegole2.GetNext(pos);

		BOOL bChecked = FALSE;
		for (POSITION pos2 = tr.pListItemBind->GetHeadPosition(); pos2;)
		{
			long lIDItemBind = tr.pListItemBind->GetNext(pos2);
			if (HTREEITEM hItemBind = GetItemFromID(lIDItemBind))
				bChecked = m_ctrlTree.GetCheck(hItemBind);

			if (bChecked)
				break;
		}

		if (!bChecked)
			listItemToDisable.AddTail(tr.lIDItem);
	}

	if (listItemToDisable.GetCount() > 0)
	{
		// TRACE("Disable %li items...\n", listItemToDisable.GetCount());
		EnableItems(&listItemToDisable, FALSE);
	}
}

void CChecklistForm::AnalyzeAllRules(HTREEITEM hItemParent)
{
	if ((m_listRegole.GetCount() > 0) || (m_listRegole2.GetCount() > 0))
	{
		UINT iMessage = 0;
		HTREEITEM hItem = NULL;
		if (hItemParent == NULL)
		{
			hItem = m_ctrlTree.GetRootItem();

			iMessage = m_ctrlTree.GetNotificationCheckMessage();
			m_ctrlTree.SetNotificationCheckMessage(0);

			EnableAllItems();
		}
		else
		{
			hItem = hItemParent;
		}

		while (hItem)
		{
			AnalyzeRules(hItem);

			if (HTREEITEM hItemChild = m_ctrlTree.GetChildItem(hItem))
				AnalyzeAllRules(hItemChild);

			hItem = m_ctrlTree.GetNextSiblingItem(hItem);
		}

		if (hItemParent == NULL)
		{
			AnalyzeRulesType2();

			m_ctrlTree.SetNotificationCheckMessage(iMessage);
		}
	}
}

HTREEITEM CChecklistForm::GetItemFromID(long lID, HTREEITEM hItemParent)
{
	HTREEITEM hItem = (hItemParent == NULL) ? m_ctrlTree.GetRootItem() : hItemParent;
	HTREEITEM hReturn = NULL;

	while (hItem)
	{
		if (m_ctrlTree.GetItemData(hItem) == lID)
		{
			hReturn = hItem;
			break;
		}

		if (HTREEITEM hItemChild = m_ctrlTree.GetChildItem(hItem))
			hReturn = GetItemFromID(lID, hItemChild);

		if (hReturn != NULL)
			break;

		hItem = m_ctrlTree.GetNextSiblingItem(hItem);
	}

	return hReturn;
}

BOOL CChecklistForm::GetSceltaMultipla(long lIDItem)
{
	BOOL bReturn = TRUE;

	POSITION pos = m_listChecklistItem.GetHeadPosition();
	while (pos != NULL)
	{
		STRUCT_CHECKLISTITEM itemTemp = m_listChecklistItem.GetAt(pos);

		if (itemTemp.lID == lIDItem)
		{
			bReturn = itemTemp.bItemPiuDiUno;
			break;
		}

		m_listChecklistItem.GetNext(pos);
	}

	return bReturn;
}

void CChecklistForm::GetTesti(long lIDItem, CString& strRTF, CString& strTXT, long& lNumeroVariabili, long& lIDDiagnosi, CString& sDiagnosiCodice, CString& sDiagnosiDescrizione)
{
	strRTF.Empty();
	strTXT.Empty();
	lNumeroVariabili = 0;
	lIDDiagnosi = 0;
	sDiagnosiCodice.Empty();
	sDiagnosiDescrizione.Empty();

	POSITION pos = m_listChecklistItem.GetHeadPosition();
	while (pos != NULL)
	{
		STRUCT_CHECKLISTITEM itemTemp = m_listChecklistItem.GetAt(pos);

		if (itemTemp.lID == lIDItem)
		{
			strRTF = itemTemp.sTestoRtf;
			strTXT = itemTemp.sTestoTxt;
			lNumeroVariabili = itemTemp.lNumeroVariabili;
			lIDDiagnosi = itemTemp.lIDDiagnosi;
			sDiagnosiCodice = itemTemp.sDiagnosiCodice;
			sDiagnosiDescrizione = itemTemp.sDiagnosiDescrizione;

			break;
		}

		m_listChecklistItem.GetNext(pos);
	}
}

CString CChecklistForm::GetTestoVariabili(long lIDItem)
{
	CString sReturn = "";

	POSITION pos = m_listChecklistItem.GetHeadPosition();
	while (pos != NULL)
	{
		STRUCT_CHECKLISTITEM itemTemp = m_listChecklistItem.GetAt(pos);

		if (itemTemp.lID == lIDItem)
		{
			sReturn = itemTemp.sTestoTxt;
			break;
		}

		m_listChecklistItem.GetNext(pos);
	}

	return sReturn;
}

void CChecklistForm::UncheckRamo(HTREEITEM hItemPadre)
{
	HTREEITEM hItemFiglio = m_ctrlTree.GetChildItem(hItemPadre);
	while (hItemFiglio != NULL)
	{
		SetCheck(hItemFiglio, FALSE);
		UncheckRamo(hItemFiglio);

		hItemFiglio = m_ctrlTree.GetNextSiblingItem(hItemFiglio);
	}
}

void CChecklistForm::RiempiAlbero()
{
	BeginWaitCursor();

	CaricaRegole();

	// Sandro 13/06/2016 // per velocizzare caricamento butto tutta la checklist in memoria //

	m_listChecklistItem.RemoveAll();

	if (m_lIDChecklist > 0)
	{
		CString strFilter;
		strFilter.Format("IDCheckList=%li AND IDPadre IS NOT NULL", m_lIDChecklist);

		CCheckListItemSet setCheckItemZ;
		setCheckItemZ.SetOpenFilter(strFilter);
		setCheckItemZ.SetSortRecord("IDPadre, Ordine, ID");
		if (setCheckItemZ.OpenRecordset("CChecklistForm::RiempiAlbero"))
		{
			while (!setCheckItemZ.IsEOF())
			{
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

				setCheckItemZ.MoveNext();
			}

			setCheckItemZ.CloseRecordset("CChecklistForm::RiempiAlbero");
		}
	}

	//

	BOOL bEspansa = CCheckListSet().GetEspansa(m_lIDChecklist);

	m_listCheckListItemObbligatory.RemoveAll();
	m_ctrlTree.DeleteAllItems();

	POSITION pos = m_listChecklistItem.GetHeadPosition();
	while (pos != NULL)
	{
		STRUCT_CHECKLISTITEM clTemp = m_listChecklistItem.GetAt(pos);

		if (clTemp.lIDPadre == 0)
		{
			HTREEITEM hItem = m_ctrlTree.InsertItem(TVIF_HANDLE | TVIF_PARAM | TVIF_TEXT,
				clTemp.sTitolo,
				0, 0, 0, 0,
				(LPARAM)clTemp.lID,
				TVI_ROOT,
				TVI_LAST);

			if (clTemp.bItemAlmenoUno)
				m_listCheckListItemObbligatory.AddTail(clTemp.lID);

			/* if (m_listCheckEsame.Find(clTemp.lID))
				m_ctrlTree.SetCheck(hItem, TRUE); */

			RiempiAlberoSub(bEspansa, hItem, clTemp.lID);

			if (bEspansa)
				m_ctrlTree.Expand(hItem, TVE_EXPAND);
		}

		m_listChecklistItem.GetNext(pos);
	}

	if (m_ctrlTree.GetCount() > 0)
		m_ctrlTree.EnsureVisible(m_ctrlTree.GetRootItem());

	//

	TRACE0("    CChecklistForm::RiempiAlbero --> AnalyzeAllRules inizio\n");
	CLogFileWriter::Get()->WriteLogLine0("CChecklistForm::RiempiAlbero --> AnalyzeAllRules inizio");

	DWORD timeDurata = timeGetTime();
	AnalyzeAllRules();
	timeDurata = timeGetTime() - timeDurata;

	CString sLog;
	sLog.Format("CChecklistForm::RiempiAlbero --> AnalyzeAllRules fine (%li msec)", (long)timeDurata);
	CLogFileWriter::Get()->WriteLogLine0(sLog);
	TRACE0("    " + sLog + "\n");

	//

	m_ctrlTree.SelectItem(NULL);

	// m_listCheckEsame.RemoveAll();
	EndWaitCursor();
}

void CChecklistForm::RiempiAlberoSub(BOOL bEspansa, HTREEITEM hRoot, long lIDPadre)
{
	POSITION pos = m_listChecklistItem.GetHeadPosition();
	while (pos != NULL)
	{
		STRUCT_CHECKLISTITEM cliTemp = m_listChecklistItem.GetAt(pos);

		if (cliTemp.lIDPadre == lIDPadre)
		{
			HTREEITEM hItem = m_ctrlTree.InsertItem(TVIF_HANDLE | TVIF_PARAM | TVIF_TEXT,
				cliTemp.sTitolo,
				0, 0, 0, 0,
				(LPARAM)cliTemp.lID,
				hRoot,
				TVI_LAST);

			if (cliTemp.bItemAlmenoUno)
				m_listCheckListItemObbligatory.AddTail(cliTemp.lID);

			/* if (m_listCheckEsame.Find(cliTemp.lID))
				m_ctrlTree.SetCheck(hItem, TRUE); */

			if (hItem != NULL)
				RiempiAlberoSub(bEspansa, hItem, cliTemp.lID);

			if (bEspansa)
				m_ctrlTree.Expand(hItem, TVE_EXPAND);
		}

		m_listChecklistItem.GetNext(pos);
	}
}

void CChecklistForm::UncheckAllItems(HTREEITEM hItemParent)
{
	HTREEITEM hItem = (hItemParent == NULL) ? m_ctrlTree.GetRootItem() : hItemParent;

	while (hItem)
	{
		if (!m_ctrlTree.GetCheckEnabled(hItem))
			m_ctrlTree.SetCheckEnabled(hItem, TRUE);
		else
			m_ctrlTree.SetCheck(hItem, FALSE);

		if (HTREEITEM hItemChild = m_ctrlTree.GetChildItem(hItem))
			UncheckAllItems(hItemChild);

		hItem = m_ctrlTree.GetNextSiblingItem(hItem);
	}
}

void CChecklistForm::ApriRamo(HTREEITEM hItemPadre)
{
	m_ctrlTree.Expand(hItemPadre, TVE_EXPAND);

	HTREEITEM hItemAll = m_ctrlTree.GetNextItem(hItemPadre, TVGN_CHILD);
	while (hItemAll != NULL)
	{
		ApriRamo(hItemAll);
		hItemAll = m_ctrlTree.GetNextSiblingItem(hItemAll);
	}
}

void CChecklistForm::ChiudiRamo(HTREEITEM hItemPadre)
{
	if (m_ctrlTree.GetCheck(hItemPadre))
		m_ctrlTree.Expand(hItemPadre, TVE_EXPAND);
	else
		m_ctrlTree.Expand(hItemPadre, TVE_COLLAPSE);

	HTREEITEM hItemAll = m_ctrlTree.GetNextItem(hItemPadre, TVGN_CHILD);
	while (hItemAll != NULL)
	{
		ChiudiRamo(hItemAll);
		hItemAll = m_ctrlTree.GetNextSiblingItem(hItemAll);
	}
}

void CChecklistForm::EnableAllItems(HTREEITEM hItemParent)
{
	HTREEITEM hItem = (hItemParent == NULL) ? m_ctrlTree.GetRootItem() : hItemParent;

#ifdef _DEBUG
	DWORD timeDurata = timeGetTime();

	if (hItemParent == NULL)
		TRACE0("    CChecklistForm::EnableAllItems inizio\n");
#endif

	while (hItem)
	{
		if (!m_ctrlTree.GetCheckEnabled(hItem))
			m_ctrlTree.SetCheckEnabled(hItem, TRUE);

		if (HTREEITEM hItemChild = m_ctrlTree.GetChildItem(hItem))
			EnableAllItems(hItemChild);

		hItem = m_ctrlTree.GetNextSiblingItem(hItem);
	}

#ifdef _DEBUG
	if (hItemParent == NULL)
		TRACE1("    CChecklistForm::EnableAllItems fine (%li msec)\n", (long)(timeGetTime() - timeDurata));
#endif
}

void CChecklistForm::OnCbnSelchangeComboChecklist()
{
	m_lIDChecklist = m_ctrlComboChecklist.GetItemData(m_ctrlComboChecklist.GetCurSel());
	RiempiAlbero();

	// salvo nell'esame l'ID dell'ultima checklist utilizzata //

	BOOL bEsamiModify = theApp.m_nProgramMode & ADD_RECORD_ESAMI || theApp.m_nProgramMode & MODIFY_RECORD_ESAMI;
	// Luiz - 10/04/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo
	if (m_ctrlChkMostraTodas.GetCheck() == BST_CHECKED)
	{
		BOOL bDoUpdate = FALSE;
		if (!bEsamiModify)
			bDoUpdate = m_pEsamiView->m_pEsamiSet->EditRecordset("CChecklistForm::OnBnClickedBtnImport");

		m_pEsamiView->m_pEsamiSet->m_lIDUltimaChecklistUsata = m_lIDChecklist;

		if (bDoUpdate)
			m_pEsamiView->m_pEsamiSet->UpdateRecordset("CChecklistForm::OnBnClickedBtnImport");
	}
}

void CChecklistForm::OnBnClickedBtnImagens()
{
	if (m_pEsamiView != NULL)
	{
		if (!theApp.m_sConfigFormRefertoBtnImgOpenWhat.IsEmpty() && !theApp.m_sConfigFormRefertoBtnImgOpenWhere.IsEmpty())
		{
			//Gabriel BUG 6225 - Lista DO
			if (theApp.m_lInstanceCountCImageDlg == 0 && theApp.m_lInstanceCountCImageSimple2Dlg == 0)
			{
				CImgList listImg;
				int nImages = m_pEsamiView->m_pImgManager->GetImgList(&listImg);
				listImg.RemoveAll();

				if (nImages > 0)
				{
					if (theApp.m_sConfigFormRefertoBtnImgOpenWhat == "CImageSimple2Dlg")
					{
						CImageSimple2Dlg* pDlg = NULL;
						pDlg = new CImageSimple2Dlg(this, m_pEsamiView, FALSE);
						pDlg->Create(IDD_IMAGE_SIMPLE2, this);
						if (pDlg != NULL)
							pDlg->ShowWindow(SW_SHOWNORMAL);
						else
							delete pDlg;
					}
					if (theApp.m_sConfigFormRefertoBtnImgOpenWhat == "CImageDlg")
					{
						CImageDlg* pDlgImage = NULL;
						pDlgImage = new CImageDlg(this, FALSE, m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore, 0, 0, TRUE);
						pDlgImage->m_bIsAlbumGlobal = FALSE;
						pDlgImage->m_pEsamiView = m_pEsamiView;
						
						/*if (m_pEsamiView->m_pImageDlg != NULL)
							m_pEsamiView->m_pImageDlg->SendMessage(EPM_EXAMCHANGED);*/

						m_pEsamiView->m_pImageDlg = pDlgImage;

						if (pDlgImage->Create(IDD_IMAGE, this))
						{
							pDlgImage->ShowWindow(SW_SHOWMAXIMIZED);
						}
						else
							delete pDlgImage;
					}
				}
			}
		}
		else
		{
			// Se não houver configuração, faz o original (como antigamente)
			CImageSimple2Dlg* pDlg = new CImageSimple2Dlg(this, m_pEsamiView, FALSE);
			if (pDlg->Create(IDD_IMAGE_SIMPLE2, this))
				pDlg->ShowWindow(SW_SHOWNORMAL);
			else
				delete pDlg;
		}
	}
}

// Luiz - 10/04/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo
void CChecklistForm::OnBnClickedChkMostraTodas()
{
	RiempiComboChecklist();

	long lCount = m_listChecklist.GetCount();
	switch (lCount)
	{
		case 0:  // NO ITEMS FOUND IN THE COMBO
		{
			m_ctrlStatic00.ShowWindow(SW_HIDE);
			m_ctrlComboChecklist.ShowWindow(SW_HIDE);
			m_ctrlChkMostraTodas.SetCheck(BST_CHECKED);
			m_ctrlChkMostraTodas.EnableWindow(FALSE);
			m_lIDChecklist = 0;
			break;
		}
		case 1: // ONLY ONE ITEM FOUND IN THE COMBO
		{
			m_ctrlStatic00.EnableWindow(FALSE);
			m_ctrlComboChecklist.ShowWindow(SW_SHOW);
			m_ctrlComboChecklist.EnableWindow(FALSE);
			//			m_ctrlChkMostraTodas.SetCheck(BST_UNCHECKED);
			m_ctrlChkMostraTodas.EnableWindow(TRUE);
			m_lIDChecklist = m_listChecklist.GetHead().m_lID;
			RiempiAlbero();
			break;
		}
		default: // TWO OR MORE ITEMS FOUND IN THE COMBO
		{
			CString sCodicePrestazione = GetPrestazione();

			m_ctrlStatic00.ShowWindow(SW_SHOW);
			m_ctrlComboChecklist.ShowWindow(SW_SHOW);
			m_ctrlComboChecklist.EnableWindow(TRUE);
			m_ctrlChkMostraTodas.EnableWindow(TRUE);


			m_ctrlComboChecklist.InsertString(0, "");
			m_ctrlComboChecklist.SetItemData(0, 0);
			int nIndex = 1;
			int nItemToSel = 0; // Marvel BUG 4094 - Combo Checklists filtradas deve ser vazio por default
			
			POSITION pos = m_listChecklist.GetHeadPosition();
			STRUCT_CHECKLIST tagTemp;

			while (pos != NULL)
			{
				tagTemp = m_listChecklist.GetAt(pos);

				//m_ctrlComboChecklist.InsertString(nIndex, tagTemp.m_sDescrizione);				
				m_ctrlComboChecklist.InsertString(nIndex, tagTemp.m_sCodice);
				m_ctrlComboChecklist.SetItemData(nIndex, tagTemp.m_lID);

				if (m_ctrlChkMostraTodas.GetCheck() == BST_CHECKED && tagTemp.m_lID == m_pEsamiView->m_pEsamiSet->m_lIDUltimaChecklistUsata)
					nItemToSel = nIndex;

				nIndex++;
				m_listChecklist.GetNext(pos);
			}

			m_ctrlComboChecklist.SetCurSel(nItemToSel);

			OnCbnSelchangeComboChecklist();
			break;
		}
	}
}