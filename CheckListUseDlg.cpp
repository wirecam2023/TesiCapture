#include "stdafx.h"
#include "Endox.h"
#include "CheckListUseDlg.h"

#include "CheckListItemRegoleSet.h"
#include "CheckListItemSet.h"
#include "CheckListSet.h"
#include "CodiciClassificazioneDiagnosticaSet.h"
#include "CustomDate.h"
#include "EditStringDlg.h"
#include "Esamiview.h"
#include "DialogWithResizableCombo.h"

#define TIMER_CONTROLLAALBERO				 999
#define TIMER_RICARICAFRASE					1001
#define TIMER_RICARICAFRASEITEMSELEZIONATO	1002

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCheckListUseDlg, CEndoxResizableDlg)

CCheckListUseDlg::CCheckListUseDlg(CWnd* pParent, CEsamiView* pEsamiView, CTXTextControl23Ex* pTextControl, long lIDCheckList)
	: CEndoxResizableDlg(CCheckListUseDlg::IDD, pParent)
{
	m_pEsamiView = pEsamiView;
	m_pTextControl = pTextControl;
	m_lIDCheckList = lIDCheckList;
	m_pListSearchSelectedElements = NULL;

	m_lIDItem = 0;
	m_hTreeItemFirst = NULL;
}

CCheckListUseDlg::CCheckListUseDlg(CWnd* pParent, CEsamiView* pEsamiView, CTXTextControl23Ex* pTextControl, CList<long>* pListIDCheckList, CList<long>* pListSearchElements)
	: CEndoxResizableDlg(CCheckListUseDlg::IDD, pParent)
{
	m_pEsamiView = pEsamiView;
	m_pTextControl = pTextControl;
	m_lIDCheckList = -1;
	m_pListIDCheckList = pListIDCheckList;
	m_pListSearchSelectedElements = pListSearchElements;

	m_lIDItem = 0;
	m_hTreeItemFirst = NULL;
}

CCheckListUseDlg::~CCheckListUseDlg()
{
	while(m_listVariables.GetCount() > 0)
	{
		VARIABLES* pVar = m_listVariables.RemoveTail();
		if (pVar != NULL)
		{
			delete pVar;
			pVar = NULL;
		}
	}
}

BEGIN_MESSAGE_MAP(CCheckListUseDlg, CEndoxResizableDlg)

	ON_BN_CLICKED(IDC_BTN_APRI, OnBnClickedBtnApri)
	ON_BN_CLICKED(IDC_BTN_CHIUDI, OnBnClickedBtnChiudi)
	ON_BN_CLICKED(IDC_BTN_ADDANDCLEAN, OnBnClickedBtnAddAndClean)
	ON_BN_CLICKED(IDC_CHECK_DATA, OnBnClickedCheckData)

	ON_NOTIFY(NM_CLICK, IDC_TREE, OnNMClickTree)
	ON_NOTIFY(NM_TVSTATEIMAGECHANGING, IDC_TREE, OnNMTVStateImageChangingTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnTvnSelchangedTree)

	ON_WM_SIZE()
	ON_WM_TIMER()

END_MESSAGE_MAP()

void CCheckListUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_APRI, m_ctrlButtonApri);
	DDX_Control(pDX, IDC_BTN_CHIUDI, m_ctrlButtonChiudi);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_TEXTCONTROL_HIDE, m_ctrlTextControlHide);
	m_ctrlTextControlHide.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //
	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //

	DDX_Control(pDX, IDC_TREE, m_ctrlTree);

	DDX_Control(pDX, IDC_ITEMSELEZIONATO_TITLE, m_ctrlItemSelezionatoTitle);
	DDX_Control(pDX, IDC_ITEMSELEZIONATO_PLACE, m_ctrlItemSelezionatoPlace);
	DDX_Control(pDX, IDC_ITEMSELEZIONATO_TXCONTROL, m_ctrlItemSelezionatoTxControl);
	m_ctrlItemSelezionatoTxControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //

	DDX_Control(pDX, IDC_CHECK_DATA, m_ctrlCheckData);
	DDX_Control(pDX, IDC_BTN_ADDANDCLEAN, m_ctrlBtnAddAndClean);
}

void CCheckListUseDlg::OnCancel()
{
	// OnCancel è quando chiudo il dialog normalmente, non è un "annulla" //

	if (m_lIDCheckList > 0)
	{
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
	}
	else
	{
		/* non so bene come fare...
		POSITION pos1 = m_pListIDCheckList->GetHeadPosition();
		while (pos1 != NULL)
		{
			long lIDCheckList = m_pListIDCheckList->GetNext(pos1);
		}
		*/
	}

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
				return;
			}
		}
	}

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		if (m_pListSearchSelectedElements != NULL)
		{
			m_pListSearchSelectedElements->RemoveAll();

			POSITION pos = m_ctrlTree.m_listSelectedItem.GetHeadPosition();

			while(pos)
			{
				long itemTemp = m_ctrlTree.m_listSelectedItem.GetNext(pos);
				m_pListSearchSelectedElements->AddTail(itemTemp);
			}
		}
	}
	else
	{
		m_ctrlTextControl.SetSelStart(0);
		m_ctrlTextControl.SetSelLength(-1);
		m_pTextControl->SetRTFSelText(m_ctrlTextControl.GetRTFSelText());
	}

	CEndoxResizableDlg::OnCancel();
}

BOOL CCheckListUseDlg::OnInitDialog()
{
	BOOL bReturn = CEndoxResizableDlg::OnInitDialog();

	// --- //

	AddAnchor(IDC_TREE, CSize(0, 0), CSize(50, 100));

	AddAnchor(IDC_ITEMSELEZIONATO_TITLE, CSize(0, 100), CSize(50, 100));
	AddAnchor(IDC_ITEMSELEZIONATO_PLACE, CSize(0, 100), CSize(50, 100));

	AddAnchor(IDCANCEL, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_TEXTCONTROL_PLACE, CSize(50, 0), CSize(100, 100));

	AddAnchor(IDC_CHECK_DATA, CSize(50, 0), CSize(50, 0));
	AddAnchor(IDC_BTN_ADDANDCLEAN, CSize(50, 100), CSize(100, 100));

	// --- //

	m_ctrlItemSelezionatoTitle.SetFont(&theApp.m_fontBold);

	// Sandro 13/06/2016 // per velocizzare caricamento butto tutta la checklist in memoria //

	m_listChecklistItem.RemoveAll();

	if (m_lIDCheckList > 0)
	{
		CString strFilter;
		strFilter.Format("IDCheckList=%li", m_lIDCheckList);

		CCheckListItemSet setCheckItemZ;
		setCheckItemZ.SetOpenFilter(strFilter);
		setCheckItemZ.SetSortRecord("IDPadre, Ordine, ID");
		if (setCheckItemZ.OpenRecordset("CCheckListUseDlg::OnInitDialog"))
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

			setCheckItemZ.CloseRecordset("CCheckListUseDlg::OnInitDialog");
		}
	}
	else
	{
		POSITION pos = m_pListIDCheckList->GetHeadPosition();
		while (pos != NULL)
		{
			long lIDCheckList = m_pListIDCheckList->GetNext(pos);

			CString strFilter;
			strFilter.Format("IDCheckList=%li", lIDCheckList);

			CCheckListItemSet setCheckItemZ;
			setCheckItemZ.SetOpenFilter(strFilter);
			setCheckItemZ.SetSortRecord("IDPadre, Ordine, ID");
			if (setCheckItemZ.OpenRecordset("CCheckListUseDlg::OnInitDialog"))
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

				setCheckItemZ.CloseRecordset("CCheckListUseDlg::OnInitDialog");
			}
		}
	}

	RiempiAlbero();

	// --- //

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	theApp.LocalizeDialog(this, CCheckListUseDlg::IDD, "CheckListUseDlg");
	return bReturn;
}

void CCheckListUseDlg::OnOK()
{
}

void CCheckListUseDlg::OnSize(UINT nType, int cx, int cy)
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);

	CRect rect;

	CWnd* pItemSelezinatoPlace = GetDlgItem(IDC_ITEMSELEZIONATO_PLACE);
	if (pItemSelezinatoPlace && m_ctrlItemSelezionatoTxControl.GetSafeHwnd())
	{
		pItemSelezinatoPlace->GetWindowRect(rect);
		ScreenToClient(&rect);
		m_ctrlItemSelezionatoTxControl.SetWindowPos(GetDlgItem(IDC_ITEMSELEZIONATO_PLACE), rect.left + 1, rect.top + 1, rect.Width() - 2, rect.Height() - 2, 0);
	}

	CWnd* pTextControlPlace = GetDlgItem(IDC_TEXTCONTROL_PLACE);
	if (pTextControlPlace && m_ctrlTextControl.GetSafeHwnd())
	{
		pTextControlPlace->GetWindowRect(rect);
		ScreenToClient(&rect);
		m_ctrlTextControl.SetWindowPos(GetDlgItem(IDC_TEXTCONTROL_PLACE), rect.left + 1, rect.top + 1, rect.Width() - 2, rect.Height() - 2, 0);
	}
}

void CCheckListUseDlg::OnTimer(UINT nIDEvent)
{
	KillTimer(nIDEvent);

	switch(nIDEvent)
	{
		case TIMER_CONTROLLAALBERO:
		{
			ControllaAlbero();
			break;
		}
		case TIMER_RICARICAFRASE:
		{
			RicaricaFrase();
			break;
		}
		case TIMER_RICARICAFRASEITEMSELEZIONATO:
		{
			RicaricaFraseItemSelezionato();
			break;
		}
	}
}

void CCheckListUseDlg::OnBnClickedBtnApri()
{
	HTREEITEM hItem = m_hTreeItemFirst;

	while(hItem != NULL)
	{
		ApriRamo(hItem);
		hItem = m_ctrlTree.GetNextSiblingItem(hItem);
	}
}

void CCheckListUseDlg::OnBnClickedBtnChiudi()
{
	HTREEITEM hItem = m_hTreeItemFirst;

	while(hItem != NULL)
	{
		ChiudiRamo(hItem);
		hItem = m_ctrlTree.GetNextSiblingItem(hItem);
	}
}

void CCheckListUseDlg::OnBnClickedCheckData()
{
	RicaricaFrase();
}

void CCheckListUseDlg::OnNMTVStateImageChangingTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMTVSTATEIMAGECHANGING *lpnmtsic = (NMTVSTATEIMAGECHANGING*)pNMHDR;

	if (lpnmtsic->hti != NULL)
	{
		if ((lpnmtsic->iOldStateImageIndex == 1) && (lpnmtsic->iNewStateImageIndex == 2))
		{
			//////////////////////////////////////////////
			// l'item sta passando da NON-CHECK a CHECK //
			//////////////////////////////////////////////

			HTREEITEM hTreePadre = NULL;

			// seleziono l'elemento //
			m_ctrlTree.SelectItem(lpnmtsic->hti);

			// espando l'elemento //
			m_ctrlTree.Expand(lpnmtsic->hti, TVE_EXPAND);

			// eventualmente, se a scelta singola, tolgo i check dai fratelli //
			UncheckFratelli(lpnmtsic->hti);

			// metto il check anche su tutti gli elementi superiori in cascata //
			CheckPadre(lpnmtsic->hti);

			// Sandro 15/03/2010 - aggiungo la gestione delle @variabili@ //
			long lIDItem = (long)m_ctrlTree.GetItemData(lpnmtsic->hti);
			if (lIDItem > 0)
			{
				CString sText = GetTestoVariabili(lIDItem);
				if (!sText.IsEmpty())
				{
					ChiediValoriCombo(lIDItem, sText);
					ChiediValori(lIDItem, sText);
				}
			}

			// aggiorno il testo sotto //
			SetTimer(TIMER_RICARICAFRASEITEMSELEZIONATO, 100, NULL);

			// aggiorno il testo a destra - uso il timer per far passare un po' di tempo altrimenti l'item che sto checkando non risulta checkato //
			SetTimer(TIMER_RICARICAFRASE, 100, NULL);
		}
		else if ((lpnmtsic->iOldStateImageIndex == 2) && (lpnmtsic->iNewStateImageIndex == 1))
		{
			//////////////////////////////////////////////
			// l'item sta passando da CHECK a NON-CHECK //
			//////////////////////////////////////////////

			// seleziono l'elemento //
			m_ctrlTree.SelectItem(lpnmtsic->hti);

			// tolgo il check anche su tutti gli elementi inferiori //
			UncheckRamo(lpnmtsic->hti);

			// Sandro 15/03/2010 - aggiungo la gestione delle @variabili@ //
			long lIDItem = (long)m_ctrlTree.GetItemData(lpnmtsic->hti);
			if (lIDItem > 0)
			{
				POSITION pos = m_listVariables.GetHeadPosition();
				while(pos != NULL)
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
			SetTimer(TIMER_RICARICAFRASEITEMSELEZIONATO, 100, NULL);

			// aggiorno il testo a destra - uso il timer per far passare un po' di tempo altrimenti l'item che sto decheckando non risulta decheckato //
			SetTimer(TIMER_RICARICAFRASE, 100, NULL);
		}
	}
}

void CCheckListUseDlg::OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	/*OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);*/
	/*
	Windows Server 2008 6.0 
	Windows Vista 6.0 
	Windows Server 2003 5.2 
	Windows XP 5.1 
	Windows 2000 5.0 
	*/

	// il NM_TVSTATEIMAGECHANGING funziona solo da Vista in poi //
	//if (osvi.dwMajorVersion < 6)
	//	SetTimer(TIMER_CONTROLLAALBERO, 100, NULL);
}

void CCheckListUseDlg::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hTree = m_ctrlTree.GetSelectedItem();

	if (hTree == NULL)
		CaricaDati(0);
	else
		CaricaDati((long)m_ctrlTree.GetItemData(hTree));
}

void CCheckListUseDlg::ApriRamo(HTREEITEM hItemPadre)
{
	m_ctrlTree.Expand(hItemPadre, TVE_EXPAND);

	HTREEITEM hItemAll = m_ctrlTree.GetNextItem(hItemPadre, TVGN_CHILD);
	while(hItemAll != NULL)
	{
		ApriRamo(hItemAll);
		hItemAll = m_ctrlTree.GetNextSiblingItem(hItemAll);
	}
}

void CCheckListUseDlg::CaricaDati(long lIDItem)
{
	BOOL bAzzera = TRUE;

	m_lIDItem = lIDItem;

	if (m_lIDItem > 0)
	{
		POSITION pos = m_listChecklistItem.GetHeadPosition();
		while (pos != NULL)
		{
			STRUCT_CHECKLISTITEM itemTemp = m_listChecklistItem.GetAt(pos);

			if (itemTemp.lID == m_lIDItem)
			{
				m_ctrlItemSelezionatoTitle.SetWindowText(itemTemp.sTitolo);

				m_ctrlItemSelezionatoTxControl.ResetContents();

				// aggiorno il testo della frase sotto - uso il timer perchè altrimenti l'albero va inspiegabilmente in palla (sbaglia a visualizzare gli elementi selezionati) //
				SetTimer(TIMER_RICARICAFRASEITEMSELEZIONATO, 100, NULL);

				bAzzera = FALSE;

				break;
			}

			m_listChecklistItem.GetNext(pos);
		}
	}

	if (bAzzera)
	{
		m_ctrlItemSelezionatoTitle.SetWindowText("");

		m_ctrlItemSelezionatoTxControl.ResetContents();
	}
}

BOOL CCheckListUseDlg::CercaCheckNoSi(HTREEITEM hItem)
{
	BOOL bReturn = FALSE;

	HTREEITEM hItemFigli = m_ctrlTree.GetNextItem(hItem, TVGN_CHILD);
	while(hItemFigli != NULL)
	{
		if (m_ctrlTree.GetCheck(hItemFigli))
		{
			if (m_listIDCheckListItems.Find((long)m_ctrlTree.GetItemData(hItemFigli)) == NULL)
			{
				NMTVSTATEIMAGECHANGING nmtsic;
				nmtsic.hti = hItemFigli;
				nmtsic.iOldStateImageIndex = 1;
				nmtsic.iNewStateImageIndex = 2;

				OnNMTVStateImageChangingTree((NMHDR*)&nmtsic, NULL);

				return TRUE;
			}
		}

		bReturn = CercaCheckNoSi(hItemFigli);
		if (bReturn)
			return TRUE;

		hItemFigli = m_ctrlTree.GetNextSiblingItem(hItemFigli);
	}

	return bReturn;
}

BOOL CCheckListUseDlg::CercaCheckSiNo(HTREEITEM hItem)
{
	BOOL bReturn = FALSE;

	HTREEITEM hItemFigli = m_ctrlTree.GetNextItem(hItem, TVGN_CHILD);
	while(hItemFigli != NULL)
	{
		if (!m_ctrlTree.GetCheck(hItemFigli))
		{
			if (m_listIDCheckListItems.Find((long)m_ctrlTree.GetItemData(hItemFigli)) != NULL)
			{
				NMTVSTATEIMAGECHANGING nmtsic;
				nmtsic.hti = hItemFigli;
				nmtsic.iOldStateImageIndex = 2;
				nmtsic.iNewStateImageIndex = 1;

				OnNMTVStateImageChangingTree((NMHDR*)&nmtsic, NULL);

				return TRUE;
			}
		}

		bReturn = CercaCheckSiNo(hItemFigli);
		if (bReturn)
			return TRUE;

		hItemFigli = m_ctrlTree.GetNextSiblingItem(hItemFigli);
	}

	return bReturn;
}

void CCheckListUseDlg::CheckPadre(HTREEITEM hItem)
{
	// prendo l'HTREEITEM del padre (che è l'elemento da checkare) //
	HTREEITEM hTreePadre = m_ctrlTree.GetParentItem(hItem);

	if (hTreePadre != NULL)
	{
		///////////////////////////////////
		// se il padre esiste ed è buono //
		///////////////////////////////////

		// prima checko suo padre così mi chiede prima le sue eventuali @varibili@ //
		CheckPadre(hTreePadre);

		// eventualmente, se a scelta singola, tolgo i check dai fratelli //
		UncheckFratelli(hTreePadre);

		// ora checko questo item //
		SetCheck(hTreePadre, TRUE);
	}
	else
	{
		/////////////////////////////////////////////
		// se questo è un item radice, senza padre //
		/////////////////////////////////////////////

		// se la root non è ancora nella lista che contiene l'ordine di selezione ce la aggiungo //
		if (m_listIDCheckListRootsOrder.Find((long)m_ctrlTree.GetItemData(hItem)) == NULL)
			m_listIDCheckListRootsOrder.AddTail((long)m_ctrlTree.GetItemData(hItem));
	}
}

void CCheckListUseDlg::ChiediValori(long lIDItem, CString& sText)
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
				CString sMeasurementValue = "";
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

BOOL CCheckListUseDlg::ChiediValoriCombo(long lIDItem, CString& sText)
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
			if (resToken != _T(""))
			{
				if (lArrayPos < lArrayCount)
				{
					sArray[lArrayPos] = resToken;
					lArrayPos++;
				}
			}
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
				CDialogWithResizableCombo dlg(this, sTitolo, sArrayNEW, lArrayCountNEW, lRect);

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


void CCheckListUseDlg::ChiudiRamo(HTREEITEM hItemPadre)
{
	if (m_ctrlTree.GetCheck(hItemPadre))
		m_ctrlTree.Expand(hItemPadre, TVE_EXPAND);
	else
		m_ctrlTree.Expand(hItemPadre, TVE_COLLAPSE);

	HTREEITEM hItemAll = m_ctrlTree.GetNextItem(hItemPadre, TVGN_CHILD);
	while(hItemAll != NULL)
	{
		ChiudiRamo(hItemAll);
		hItemAll = m_ctrlTree.GetNextSiblingItem(hItemAll);
	}
}

void CCheckListUseDlg::ContaCheck(HTREEITEM hItem, long& lChecks)
{
	HTREEITEM hItemFigli = m_ctrlTree.GetNextItem(hItem, TVGN_CHILD);
	while(hItemFigli != NULL)
	{
		if (m_ctrlTree.GetCheck(hItemFigli))
			lChecks++;

		ContaCheck(hItemFigli, lChecks);

		hItemFigli = m_ctrlTree.GetNextSiblingItem(hItemFigli);
	}
}

void CCheckListUseDlg::ControllaAlbero()
{
	long lChecks = 0;

	HTREEITEM hTreeConta = m_hTreeItemFirst;
	while(hTreeConta != NULL)
	{
		if (m_ctrlTree.GetCheck(hTreeConta))
			lChecks++;

		ContaCheck(hTreeConta, lChecks);
		hTreeConta = m_ctrlTree.GetNextSiblingItem(hTreeConta);
	}

	if (lChecks != m_listIDCheckListItems.GetCount())
	{
		if (lChecks > m_listIDCheckListItems.GetCount())
		{
			//////////////////////////////////////////////
			// l'item sta passando da NON-CHECK a CHECK //
			//////////////////////////////////////////////

			HTREEITEM hTreeCerca = m_hTreeItemFirst;
			while(hTreeCerca != NULL)
			{
				if (m_ctrlTree.GetCheck(hTreeCerca))
				{
					if (m_listIDCheckListItems.Find((long)m_ctrlTree.GetItemData(hTreeCerca)) == NULL)
					{
						NMTVSTATEIMAGECHANGING nmtsic;
						nmtsic.hti = hTreeCerca;
						nmtsic.iOldStateImageIndex = 1;
						nmtsic.iNewStateImageIndex = 2;

						OnNMTVStateImageChangingTree((NMHDR*)&nmtsic, NULL);

						return;
					}
				}

				if (CercaCheckNoSi(hTreeCerca))
					return;

				hTreeCerca = m_ctrlTree.GetNextSiblingItem(hTreeCerca);
			}
		}
		else
		{
			//////////////////////////////////////////////
			// l'item sta passando da CHECK a NON-CHECK //
			//////////////////////////////////////////////

			HTREEITEM hTreeCerca = m_hTreeItemFirst;
			while(hTreeCerca != NULL)
			{
				if (!m_ctrlTree.GetCheck(hTreeCerca))
				{
					if (m_listIDCheckListItems.Find((long)m_ctrlTree.GetItemData(hTreeCerca)) != NULL)
					{
						NMTVSTATEIMAGECHANGING nmtsic;
						nmtsic.hti = hTreeCerca;
						nmtsic.iOldStateImageIndex = 2;
						nmtsic.iNewStateImageIndex = 1;

						OnNMTVStateImageChangingTree((NMHDR*)&nmtsic, NULL);

						return;
					}
				}

				if (CercaCheckSiNo(hTreeCerca))
					return;

				hTreeCerca = m_ctrlTree.GetNextSiblingItem(hTreeCerca);
			}
		}
	}
}

BOOL CCheckListUseDlg::GetSceltaMultipla(long lIDItem)
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

void CCheckListUseDlg::GetTesti(long lIDItem, CString& strRTF, CString& strTXT, long& lNumeroVariabili, long& lIDDiagnosi, CString& sDiagnosiCodice, CString& sDiagnosiDescrizione)
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

CString CCheckListUseDlg::GetTestoVariabili(long lIDItem)
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

void CCheckListUseDlg::RicaricaFrase()
{
	BeginWaitCursor();

	long lRefertoLen = 0;

	m_ctrlTextControl.ResetContents();
	m_listIDCheckListItems.RemoveAll();

	if (m_ctrlCheckData.GetCheck() == BST_CHECKED)
	{
		CString strData = CCustomDate(TRUE, TRUE).GetDate("%d/%m/%Y") + "\r\n\r\n\r\n";
		m_ctrlTextControl.SetText(strData);
		lRefertoLen += strData.GetLength();
	}

	// RIMA 11-005.16 // inserisco le frasi in ordine di selezione //
	POSITION pos = m_listIDCheckListRootsOrder.GetHeadPosition();
	while(pos != NULL)
	{
		long lIDItem = m_listIDCheckListRootsOrder.GetNext(pos);

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
		}

		// --- //

		HTREEITEM hTreeRoot = m_hTreeItemFirst;

		while(hTreeRoot != NULL)
		{
			if ((long)m_ctrlTree.GetItemData(hTreeRoot) == lIDItem)
				break;

			hTreeRoot = m_ctrlTree.GetNextSiblingItem(hTreeRoot);
		}

		if (hTreeRoot != NULL)
			RicaricaFraseSub(hTreeRoot, lRefertoLen);
	}

	EndWaitCursor();
}

void CCheckListUseDlg::RicaricaFraseItemSelezionato()
{
	if (m_lIDItem > 0)
	{
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

		m_ctrlItemSelezionatoTxControl.ResetContents();
		m_ctrlItemSelezionatoTxControl.SetRTFSelText(strRTF);
	}
}

void CCheckListUseDlg::RicaricaFraseSub(HTREEITEM hItemPadre, long& lRefertoLen)
{
	HTREEITEM hItemFigli = m_ctrlTree.GetNextItem(hItemPadre, TVGN_CHILD);

	while(hItemFigli != NULL)
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
			}

			// --- //

			RicaricaFraseSub(hItemFigli, lRefertoLen);
		}

		hItemFigli = m_ctrlTree.GetNextSiblingItem(hItemFigli);
	}
}

void CCheckListUseDlg::RiempiAlbero()
{
	BeginWaitCursor();

	m_hTreeItemFirst = NULL;
	m_ctrlTree.DeleteAllItems();
	m_listIDCheckListRootsOrder.RemoveAll();
	m_listCheckListItemObbligatory.RemoveAll();

	if (m_lIDCheckList > 0)
	{
		BOOL bEspansa = FALSE;
		if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
			bEspansa = FALSE;
		else
			bEspansa = CCheckListSet().GetEspansa(m_lIDCheckList);

		POSITION pos = m_listChecklistItem.GetHeadPosition();
		while (pos != NULL)
		{
			STRUCT_CHECKLISTITEM cliTemp = m_listChecklistItem.GetAt(pos);

			if ((cliTemp.lIDChecklist == m_lIDCheckList) && (cliTemp.lIDPadre == 0))
			{
				HTREEITEM hRoot = NULL;
				if (bEspansa)
					hRoot = m_ctrlTree.InsertItem(TVIF_HANDLE | TVIF_PARAM | TVIF_STATE | TVIF_TEXT, cliTemp.sTitolo, 0, 0, TVIS_EXPANDED, TVIS_EXPANDED, (LPARAM)cliTemp.lID, TVI_ROOT, TVI_LAST);
				else
					hRoot = m_ctrlTree.InsertItem(TVIF_HANDLE | TVIF_PARAM | TVIF_TEXT, cliTemp.sTitolo, 0, 0, 0, 0, (LPARAM)cliTemp.lID, TVI_ROOT, TVI_LAST);

				if (cliTemp.bItemAlmenoUno)
					m_listCheckListItemObbligatory.AddTail(cliTemp.lID);

				if (m_hTreeItemFirst == NULL)
					m_hTreeItemFirst = hRoot;

				if (hRoot != NULL)
					RiempiAlberoSub(bEspansa, hRoot, cliTemp.lID);
			}

			m_listChecklistItem.GetNext(pos);
		}
	}
	else
	{
		POSITION pos1 = m_pListIDCheckList->GetHeadPosition();
		while(pos1 != NULL)
		{
			long lIDCheckList = m_pListIDCheckList->GetNext(pos1);

			BOOL bEspansa = FALSE;
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				bEspansa = FALSE;
			else
				bEspansa = CCheckListSet().GetEspansa(lIDCheckList);

			POSITION pos2 = m_listChecklistItem.GetHeadPosition();
			while (pos2 != NULL)
			{
				STRUCT_CHECKLISTITEM cliTemp = m_listChecklistItem.GetAt(pos2);

				if ((cliTemp.lIDChecklist == lIDCheckList) && (cliTemp.lIDPadre == 0))
				{
					HTREEITEM hRoot = NULL;
					if (bEspansa)
						hRoot = m_ctrlTree.InsertItem(TVIF_HANDLE | TVIF_PARAM | TVIF_STATE | TVIF_TEXT, cliTemp.sTitolo, 0, 0, TVIS_EXPANDED, TVIS_EXPANDED, (LPARAM)cliTemp.lID, TVI_ROOT, TVI_LAST);
					else
						hRoot = m_ctrlTree.InsertItem(TVIF_HANDLE | TVIF_PARAM | TVIF_TEXT, cliTemp.sTitolo, 0, 0, 0, 0, (LPARAM)cliTemp.lID, TVI_ROOT, TVI_LAST);

					if (cliTemp.bItemAlmenoUno)
						m_listCheckListItemObbligatory.AddTail(cliTemp.lID);

					if (m_hTreeItemFirst == NULL)
						m_hTreeItemFirst = hRoot;

					if (hRoot != NULL)
						RiempiAlberoSub(bEspansa, hRoot, cliTemp.lID);
				}

				m_listChecklistItem.GetNext(pos2);
			}
		}
	}

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		if (m_pListSearchSelectedElements != NULL)
		{
			POSITION pos = m_pListSearchSelectedElements->GetHeadPosition();

			while(pos)
			{
				long itemTemp = m_pListSearchSelectedElements->GetNext(pos);
				m_ctrlTree.m_listSelectedItem.AddTail(itemTemp);
			}
			m_ctrlTree.Invalidate();
		}
	}
	else
	{
		m_ctrlTree.LoadSelectedItems(m_pEsamiView->m_pEsamiSet->m_lContatore);
	}

	EndWaitCursor();
}

void CCheckListUseDlg::RiempiAlberoSub(BOOL bEspansa, HTREEITEM hRoot, long lIDPadre)
{
	POSITION pos = m_listChecklistItem.GetHeadPosition();
	while (pos != NULL)
	{
		STRUCT_CHECKLISTITEM cliTemp = m_listChecklistItem.GetAt(pos);

		if (cliTemp.lIDPadre == lIDPadre)
		{
			HTREEITEM hItem = NULL;
			if (bEspansa)
				hItem = m_ctrlTree.InsertItem(TVIF_HANDLE | TVIF_PARAM | TVIF_STATE | TVIF_TEXT, cliTemp.sTitolo, 0, 0, TVIS_EXPANDED, TVIS_EXPANDED, (LPARAM)cliTemp.lID, hRoot, TVI_LAST);
			else
				hItem = m_ctrlTree.InsertItem(TVIF_HANDLE | TVIF_PARAM | TVIF_TEXT, cliTemp.sTitolo, 0, 0, 0, 0, (LPARAM)cliTemp.lID, hRoot, TVI_LAST);

			if (cliTemp.bItemAlmenoUno)
				m_listCheckListItemObbligatory.AddTail(cliTemp.lID);

			if (hItem != NULL)
				RiempiAlberoSub(bEspansa, hItem, cliTemp.lID);
		}

		m_listChecklistItem.GetNext(pos);
	}
}

BOOL CCheckListUseDlg::SetCheck(HTREEITEM hItem, BOOL bCheck)
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
			while(pos != NULL)
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

	return m_ctrlTree.SetMyCheck(hItem, bCheck);
}

void CCheckListUseDlg::SostituisciVariabili(long lIDItem, CString& strRTF, CString& strTXT)
{
	// metto temporaneamente il testo RTF in un controllo rich //
	m_ctrlTextControlHide.ResetContents();
	m_ctrlTextControlHide.SetRTFSelText(strRTF);

	// ora sostituisco (direttamente nel controllo) il testo di ogni variabile con il suo valore //
	POSITION pos = m_listVariables.GetHeadPosition();
	while(pos != NULL)
	{
		VARIABLES* pVal = m_listVariables.GetNext(pos);
		if (pVal->lIDItem == lIDItem)
		{
			long lFind = strTXT.Find(pVal->sVariable);
			while(lFind >= 0)
			{
				m_ctrlTextControlHide.SetSelStart(lFind);
				m_ctrlTextControlHide.SetSelLength(pVal->sVariable.GetLength());
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
}

void CCheckListUseDlg::UncheckFratelli(HTREEITEM hItem)
{
	// controllo se gli item sono a scelta singola perchè eventualmente deseleziono tutti gli altri //
	HTREEITEM hTreePadre = m_ctrlTree.GetParentItem(hItem);
	if (hTreePadre == NULL)
	{
		// l'item è nella root //

		if (m_lIDCheckList > 0)
		{
			if (!GetSceltaMultipla(m_lIDCheckList))
			{
				HTREEITEM hTreeAll = m_hTreeItemFirst;
				while(hTreeAll != NULL)
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
	else
	{
		// l'item è figlio //

		if (!GetSceltaMultipla((long)m_ctrlTree.GetItemData(hTreePadre)))
		{
			HTREEITEM hTreeAll = m_ctrlTree.GetNextItem(hTreePadre, TVGN_CHILD);
			while(hTreeAll != NULL)
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

void CCheckListUseDlg::UncheckRamo(HTREEITEM hItemPadre)
{
	// se trovo l'item padre nella lista dei root lo rimuovo //
	POSITION pos = m_listIDCheckListRootsOrder.Find((long)m_ctrlTree.GetItemData(hItemPadre));
	if (pos != NULL)
		m_listIDCheckListRootsOrder.RemoveAt(pos);

	//
	HTREEITEM hItemFiglio = m_ctrlTree.GetChildItem(hItemPadre);
	while(hItemFiglio != NULL)
	{
		SetCheck(hItemFiglio, FALSE);
		UncheckRamo(hItemFiglio);

		hItemFiglio = m_ctrlTree.GetNextSiblingItem(hItemFiglio);
	}
}

void CCheckListUseDlg::OnBnClickedBtnAddAndClean()
{
	// copio tutto dentro al controllo nell'interfaccia principale //
	m_ctrlTextControl.SetSelStart(0);
	m_ctrlTextControl.SetSelLength(-1);
	m_pTextControl->SetRTFSelText(m_ctrlTextControl.GetRTFSelText());

	// unchecko il tasto data //
	m_ctrlCheckData.SetCheck(BST_UNCHECKED);

	// pulisco il text control locale //
	m_ctrlTextControl.ResetContents();

	// pulisco la lista delle variabili //
	while(m_listVariables.GetCount() > 0)
	{
		VARIABLES* pVar = m_listVariables.RemoveTail();
		if (pVar != NULL)
		{
			delete pVar;
			pVar = NULL;
		}
	}

	// pulisco la checklist //
	RiempiAlbero();
}

HTREEITEM CCheckListUseDlg::GetItemFromID(long lID, HTREEITEM hItemParent)
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
