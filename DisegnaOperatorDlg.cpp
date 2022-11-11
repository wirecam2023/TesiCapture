#include "stdafx.h"
#include "Endox.h"
#include "DisegnaOperatorDlg.h"

#include "DLL_Imaging\h\AMLogin.h"

#include "DynCampoSet.h"
#include "DynFormSet.h"
#include "DynVersioneSet.h"
#include "EsamiView.h"
#include "LinguettaDlg.h"
#include "PasswordDlg.h"
#include "PropCampoDlg.h"
#include "TipoEsameNew.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDisegnaOperatorDlg, CDialog)

CDisegnaOperatorDlg::CDisegnaOperatorDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CDisegnaOperatorDlg::IDD, pParent), m_FrameWnd(&m_report)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_lIDVersione = -1;
}

CDisegnaOperatorDlg::~CDisegnaOperatorDlg()
{
}

BEGIN_MESSAGE_MAP(CDisegnaOperatorDlg, CDialog)

	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()

	ON_BN_CLICKED(IDC_BTN_COPY, OnBnClickedBtnCopy)

	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)

	ON_BN_CLICKED(IDC_BTN_ADD, OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_REM, OnBnClickedBtnRem)
	ON_BN_CLICKED(IDC_BTN_ADDCAMPO, OnBnClickedBtnAddCampo)

	ON_BN_CLICKED(IDC_BTN_SOLOQUESTO,	OnBnClickedBtnSoloQuesto)
	ON_BN_CLICKED(IDC_BTN_SAVEOVER,		OnBnClickedBtnSaveOver)

	ON_CBN_SELCHANGE(IDC_COMBO_ESAME, OnCbnSelchangeComboEsame)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnTcnSelchangeTab)

END_MESSAGE_MAP()

void CDisegnaOperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_FRAME, m_FrameWnd);

	DDX_Control(pDX, IDC_BTN_COPY, m_ctrlButtonCopy);

	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlButtonUndo);

	DDX_Control(pDX, IDC_BTN_ADD, m_ctrlButtonAdd);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_BTN_REM, m_ctrlButtonRem);
	DDX_Control(pDX, IDC_BTN_ADDCAMPO, m_ctrlButtonAddCampo);

	DDX_Control(pDX, IDC_BTN_SOLOQUESTO,	m_ctrlButtonSoloQuesto);
	DDX_Control(pDX, IDC_BTN_SAVEOVER,		m_ctrlButtonSaveOver);

	DDX_Control(pDX, IDCANCEL,				m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_STATIC_LABEL2, m_ctrlStaticLabel2);

	DDX_Control(pDX, IDC_COMBO_ESAME, m_ctrlCombo);
	DDX_Control(pDX, IDC_TAB, m_ctrlTab);
}

void CDisegnaOperatorDlg::OnCancel()
{
	if (GetDlgItem(IDCANCEL)->IsWindowEnabled() == TRUE)
	{
		CancellaTabs();
		CDialog::OnCancel();
	}
}

BOOL CDisegnaOperatorDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	m_ctrlStaticLabel2.SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_COMBO_ESAME)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_BTN_SAVE)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_BTN_UNDO)->SetFont(&theApp.m_fontBold);

	RiempiListaEsami();

	m_FrameWnd.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	theApp.LocalizeDialog(this, CDisegnaOperatorDlg::IDD, "DisegnaOperatorDlg");

	return bReturn;
}

void CDisegnaOperatorDlg::OnOK()
{
	// CDialog::OnCancel();
}

void CDisegnaOperatorDlg::CaricaInterfaccia(long lIDVersione)
{
	CString sTitle;
	sTitle.Format(IDS_DISEGNOINTERFACCIAOPERATORE, lIDVersione);
	SetWindowText(sTitle);

	//

	CString strFilter;
	CDynFormSet setDynForm;
	CDynCampoSet setDynCampo;

	TCITEM item;
	item.mask = TCIF_PARAM | TCIF_TEXT;

	BeginWaitCursor();

	CancellaTabs();
	SelezionaTab(-1);

	m_ctrlButtonEdt.EnableWindow(FALSE);
	m_ctrlButtonRem.EnableWindow(FALSE);
	m_ctrlButtonAddCampo.EnableWindow(FALSE);

	if (lIDVersione > 0)
	{
		strFilter.Format("IDVersione=%li", lIDVersione);
		setDynForm.SetOpenFilter(strFilter);
		setDynForm.SetSortRecord("Ordine, ID");

		if (setDynForm.OpenRecordset("CDisegnaOperatorDlg::CaricaInterfaccia") == TRUE)
		{
			while(setDynForm.IsEOF() == FALSE)
			{
				STRUCT_LINGUETTA* pLinguetta = new STRUCT_LINGUETTA;

				if (pLinguetta != NULL)
				{
					strFilter.Format("IDForm=%li", setDynForm.m_lID);
					setDynCampo.SetOpenFilter(strFilter);

					pLinguetta->lMostraAlbum = setDynForm.m_lAlbum;
					pLinguetta->bVisualizzaSempre = setDynForm.m_bVisualizzaSempre;

					if (setDynCampo.OpenRecordset("CDisegnaOperatorDlg::CaricaInterfaccia") == TRUE)
					{
						while(setDynCampo.IsEOF() == FALSE)
						{
							STRUCT_CAMPO campoTemp;

							campoTemp.lContenuto = setDynCampo.m_lContenuto;
							campoTemp.lX = setDynCampo.m_lX;
							campoTemp.lY = setDynCampo.m_lY;
							campoTemp.lL = setDynCampo.m_lL;
							campoTemp.lA = setDynCampo.m_lA;
							campoTemp.lColore = setDynCampo.m_lColore;
							campoTemp.lTabOrder = setDynCampo.m_lTabOrder;
							campoTemp.lIDFaseBlocco = setDynCampo.m_lIDFaseBlocco;
							campoTemp.lIDFaseBlocco = setDynCampo.m_lIDFaseBlocco;

							pLinguetta->listCampi.AddTail(campoTemp);

							setDynCampo.MoveNext();
						}

						setDynCampo.CloseRecordset("CDisegnaOperatorDlg::CaricaInterfaccia");
					}

					item.lParam = (LPARAM)pLinguetta;
					item.pszText = (LPTSTR)((LPCTSTR)setDynForm.m_sNome);

					m_ctrlTab.InsertItem(m_ctrlTab.GetItemCount(), &item);
				}

				setDynForm.MoveNext();
			}

			setDynForm.CloseRecordset("CDisegnaOperatorDlg::CaricaInterfaccia");
		}
		
		if (m_ctrlTab.GetItemCount() > 0)
		{
			SelezionaTab(0);

			m_ctrlButtonEdt.EnableWindow(TRUE);
			m_ctrlButtonRem.EnableWindow(TRUE);
			m_ctrlButtonAddCampo.EnableWindow(TRUE);
		}
	}

	EndWaitCursor();
}

void CDisegnaOperatorDlg::SalvaInterfaccia(long lIDVersione)
{
	CString sTitle;
	sTitle.Format(IDS_DISEGNOINTERFACCIAOPERATORE, lIDVersione);
	SetWindowText(sTitle);

	//

	CString strFilter;
	CDynFormSet setDynForm;
	CDynCampoSet setDynCampo;

	char szBuffer[1024];
	ZeroMemory(szBuffer, 1024 * sizeof(char));

	TCITEM item;
	item.mask = TCIF_PARAM | TCIF_TEXT;
	item.pszText = szBuffer;
	item.cchTextMax = 1024;

	STRUCT_LINGUETTA* pLinguetta = NULL;

	BeginWaitCursor();

	setDynForm.SetSortRecord("ID");
	if (setDynForm.OpenRecordset("CDisegnaOperatorDlg::SalvaInterfaccia") == TRUE)
	{
		setDynCampo.SetSortRecord("ID");
		if (setDynCampo.OpenRecordset("CDisegnaOperatorDlg::SalvaInterfaccia") == TRUE)
		{
			for(int i = 0; i < m_ctrlTab.GetItemCount(); i++)
			{
				m_ctrlTab.GetItem(i, &item);

				pLinguetta = (STRUCT_LINGUETTA*)item.lParam;
				if (pLinguetta != NULL)
				{
					if (setDynForm.AddNewRecordset("CDisegnaOperatorDlg::SalvaInterfaccia") == TRUE)
					{
						setDynForm.m_lIDVersione = lIDVersione;
						setDynForm.m_sNome = CString(item.pszText);
						setDynForm.m_lOrdine = i + 1;
						setDynForm.m_lAlbum = pLinguetta->lMostraAlbum;
						setDynForm.m_bVisualizzaSempre = pLinguetta->bVisualizzaSempre;

						if (setDynForm.UpdateRecordset("CDisegnaOperatorDlg::SalvaInterfaccia") == TRUE)
						{
							POSITION pos = pLinguetta->listCampi.GetHeadPosition();

							while(pos != NULL)
							{
								STRUCT_CAMPO campoTemp = pLinguetta->listCampi.GetAt(pos);

								if (setDynCampo.AddNewRecordset("CDisegnaOperatorDlg::SalvaInterfaccia") == TRUE)
								{
									setDynCampo.m_lIDForm = setDynForm.GetLastAdd();
									setDynCampo.m_lContenuto = campoTemp.lContenuto;
									setDynCampo.m_lX = campoTemp.lX;
									setDynCampo.m_lY = campoTemp.lY;
									setDynCampo.m_lL = campoTemp.lL;
									setDynCampo.m_lA = campoTemp.lA;
									setDynCampo.m_lColore = campoTemp.lColore;
									setDynCampo.m_lTabOrder = campoTemp.lTabOrder;
									setDynCampo.m_lIDFaseBlocco = campoTemp.lIDFaseBlocco;
									setDynCampo.m_lIDFaseBlocco = campoTemp.lIDFaseBlocco;

									setDynCampo.UpdateRecordset("CDisegnaOperatorDlg::SalvaInterfaccia");
								}

								pLinguetta->listCampi.GetNext(pos);
							}
						}
					}
				}
			}

			m_ctrlButtonSave.EnableWindow(FALSE);
			m_ctrlButtonUndo.EnableWindow(FALSE);
			m_ctrlButtonSoloQuesto.EnableWindow(TRUE);
			m_ctrlButtonSaveOver.EnableWindow(FALSE);
			m_ctrlCombo.EnableWindow(TRUE);
			GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

			setDynCampo.CloseRecordset("CDisegnaOperatorDlg::SalvaInterfaccia");
		}

		setDynForm.CloseRecordset("CDisegnaOperatorDlg::SalvaInterfaccia");
	}
	EndWaitCursor();
}

void CDisegnaOperatorDlg::RiempiListaEsami()
{
	int nIndex = 1;
	CTipoEsameSet setTemp;

	m_ctrlCombo.InsertString(0, theApp.GetMessageString(IDS_RICERCA));
	m_ctrlCombo.SetItemData(0, (DWORD)VAL_RICERCA);

	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CDisegnaOperatorDlg::RiempiListaEsami") == TRUE)
	{
		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlCombo.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlCombo.SetItemData(nIndex, (DWORD)setTemp.m_lContatore);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CDisegnaOperatorDlg::RiempiListaEsami");
	}
}

void CDisegnaOperatorDlg::OnCbnSelchangeComboEsame()
{
	int nCurSel = m_ctrlCombo.GetCurSel();

	m_lIDVersione = -1;

	if (nCurSel >= 0)
	{
		long lTipoEsame = (long)m_ctrlCombo.GetItemData(nCurSel);

		if (lTipoEsame == VAL_RICERCA)
		{
			m_lIDVersione = 1;

			m_ctrlButtonCopy.EnableWindow(TRUE);
			m_ctrlButtonAdd.EnableWindow(TRUE);
			m_ctrlButtonSoloQuesto.EnableWindow(TRUE);
		}
		else
		{
			CString strFilter;
			strFilter.Format("IDTipoEsame=%li OR IDTipoEsame=0", lTipoEsame);

			CDynVersioneSet setDynVersione;
			setDynVersione.SetOpenFilter(strFilter);
			setDynVersione.SetSortRecord("DataOra DESC, ID DESC");
			if (setDynVersione.OpenRecordset("CDisegnaOperatorDlg::OnCbnSelchangeComboEsame") == TRUE)
			{
				if (setDynVersione.IsEOF() == FALSE)
					m_lIDVersione = setDynVersione.m_lID;

				setDynVersione.CloseRecordset("CDisegnaOperatorDlg::OnCbnSelchangeComboEsame");
			}

			m_ctrlButtonCopy.EnableWindow(TRUE);
			m_ctrlButtonAdd.EnableWindow(TRUE);
			m_ctrlButtonSoloQuesto.EnableWindow(TRUE);
		}
	}
	else
	{
		m_ctrlButtonCopy.EnableWindow(FALSE);
		m_ctrlButtonAdd.EnableWindow(FALSE);
		m_ctrlButtonSoloQuesto.EnableWindow(FALSE);
	}

	CaricaInterfaccia(m_lIDVersione);
}

void CDisegnaOperatorDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = m_ctrlTab.GetCurSel();
	SelezionaTab(nTab);

	*pResult = 0;
}

void CDisegnaOperatorDlg::OnBnClickedBtnAdd()
{
	TCITEM item;
	item.mask = TCIF_PARAM | TCIF_TEXT;

	STRUCT_LINGUETTA* pLinguetta = new STRUCT_LINGUETTA;
	if (pLinguetta != NULL)
	{
		pLinguetta->lMostraAlbum = 1;
		pLinguetta->bVisualizzaSempre = TRUE;

		item.lParam = (LPARAM)pLinguetta;
		item.pszText = "";

		SelezionaTab(m_ctrlTab.InsertItem(m_ctrlTab.GetItemCount(), &item));

		CLinguettaDlg dlg(this, TRUE, &m_ctrlTab);
		if (dlg.DoModal() == IDCANCEL)
		{
			CancellaTab(m_ctrlTab.GetCurSel());

			if (m_ctrlTab.GetItemCount() > 0)
			{
				SelezionaTab(0);
			}
			else
			{
				SelezionaTab(-1);

				m_ctrlButtonEdt.EnableWindow(FALSE);
				m_ctrlButtonRem.EnableWindow(FALSE);
				m_ctrlButtonAddCampo.EnableWindow(FALSE);
			}
		}
		else
		{
			m_ctrlButtonEdt.EnableWindow(TRUE);
			m_ctrlButtonRem.EnableWindow(TRUE);
			m_ctrlButtonAddCampo.EnableWindow(TRUE);

			m_ctrlButtonSave.EnableWindow((long)m_ctrlCombo.GetItemData(m_ctrlCombo.GetCurSel()) == VAL_RICERCA ? FALSE : TRUE);
			m_ctrlButtonUndo.EnableWindow(TRUE);
			m_ctrlButtonSoloQuesto.EnableWindow(FALSE);
			m_ctrlButtonSaveOver.EnableWindow(TRUE);
			m_ctrlCombo.EnableWindow(FALSE);
			GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
		}
	}
}

void CDisegnaOperatorDlg::OnBnClickedBtnEdt()
{
	CLinguettaDlg dlg(this, FALSE, &m_ctrlTab);

	if (dlg.DoModal() == IDCANCEL)
	{
		m_FrameWnd.RedrawWindow(NULL, NULL, RDW_INVALIDATE);
	}
	else
	{
		m_ctrlButtonSave.EnableWindow((long)m_ctrlCombo.GetItemData(m_ctrlCombo.GetCurSel()) == VAL_RICERCA ? FALSE : TRUE);
		m_ctrlButtonUndo.EnableWindow(TRUE);
		m_ctrlButtonSoloQuesto.EnableWindow(FALSE);
		m_ctrlButtonSaveOver.EnableWindow(TRUE);
		m_ctrlCombo.EnableWindow(FALSE);
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	}
}

void CDisegnaOperatorDlg::OnBnClickedBtnRem()
{
	int nIndex = m_ctrlTab.GetCurSel();
	if (nIndex >= 0)
	{
		char szBuffer[1024];
		ZeroMemory(szBuffer, 1024 * sizeof(char));

		TCITEM item;
		item.mask = TCIF_TEXT;
		item.pszText = szBuffer;
		item.cchTextMax = 1024;

		m_ctrlTab.GetItem(nIndex, &item);

		CString strMessage;
		strMessage.Format(theApp.GetMessageString(IDS_ELIMINARE_LINGUETTA), szBuffer);

		if (theApp.AfxMessageBoxEndo(strMessage, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
		{
			if (theApp.MessageBoxEndo(theApp.GetMessageString(IDS_ELIMINA_LINGUETTA_CONFIRM), theApp.GetMessageString(IDS_ACHTUNG), MB_YESNO | MB_ICONSTOP) == IDNO)
			{
				CancellaTab(nIndex);

				if (m_ctrlTab.GetItemCount() > 0)
				{
					SelezionaTab(0);
				}
				else
				{
					SelezionaTab(-1);

					m_ctrlButtonEdt.EnableWindow(FALSE);
					m_ctrlButtonRem.EnableWindow(FALSE);
					m_ctrlButtonAddCampo.EnableWindow(FALSE);
				}

				m_ctrlButtonSave.EnableWindow((long)m_ctrlCombo.GetItemData(m_ctrlCombo.GetCurSel()) == VAL_RICERCA ? FALSE : TRUE);
				m_ctrlButtonUndo.EnableWindow(TRUE);
				m_ctrlButtonSoloQuesto.EnableWindow(FALSE);
				m_ctrlButtonSaveOver.EnableWindow(TRUE);
				m_ctrlCombo.EnableWindow(FALSE);
				GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
			}
		}
	}
}

void CDisegnaOperatorDlg::OnBnClickedBtnAddCampo()
{
	STRUCT_CAMPO campoTemp;

	campoTemp.lContenuto = 10007;
	campoTemp.lX = 0;
	campoTemp.lY = 0;
	campoTemp.lL = 1;
	campoTemp.lA = 2;
	campoTemp.lColore = -1;
	campoTemp.lIDFaseBlocco = 0;
	campoTemp.lIDFaseBlocco = 0;

	// imposto il tab order --> //
	campoTemp.lTabOrder = 0;
	POSITION pos = m_report.GetLinguetta()->listCampi.GetHeadPosition();
	while(pos != NULL)
	{
		if (m_report.GetLinguetta()->listCampi.GetAt(pos).lTabOrder > campoTemp.lTabOrder)
			campoTemp.lTabOrder = m_report.GetLinguetta()->listCampi.GetAt(pos).lTabOrder;

		m_report.GetLinguetta()->listCampi.GetNext(pos);
	}
	campoTemp.lTabOrder++;
	// <-- //

	m_report.GetLinguetta()->listCampi.AddTail(campoTemp);
	m_report.SetCurSel(m_report.GetLinguetta()->listCampi.GetTailPosition());

	CPropCampoDlg dlg(this, &m_report);
	if (dlg.DoModal() == IDCANCEL)
	{
		m_report.GetLinguetta()->listCampi.RemoveTail();
	}
	else
	{
		m_ctrlButtonSave.EnableWindow((long)m_ctrlCombo.GetItemData(m_ctrlCombo.GetCurSel()) == VAL_RICERCA ? FALSE : TRUE);
		m_ctrlButtonUndo.EnableWindow(TRUE);
		m_ctrlButtonSoloQuesto.EnableWindow(FALSE);
		m_ctrlButtonSaveOver.EnableWindow(TRUE);
		m_ctrlCombo.EnableWindow(FALSE);
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	}
}

void CDisegnaOperatorDlg::CancellaTab(int nTab)
{
	TCITEM tabItem;
	tabItem.mask = TCIF_PARAM;

	if (m_ctrlTab.GetItem(nTab, &tabItem) == TRUE)
	{
		STRUCT_LINGUETTA* pLinguetta = (STRUCT_LINGUETTA*)tabItem.lParam;

		if (pLinguetta != NULL)
		{
			pLinguetta->listCampi.RemoveAll();
			delete pLinguetta;
		}

		m_ctrlTab.DeleteItem(nTab);
	}
}

void CDisegnaOperatorDlg::CancellaTabs()
{
	while(m_ctrlTab.GetItemCount() > 0)
		CancellaTab(0);
}

void CDisegnaOperatorDlg::SelezionaTab(int nTab)
{
	STRUCT_LINGUETTA* pLinguetta = NULL;

	if (nTab >= 0)
	{
		TCITEM tabItem;
		tabItem.mask = TCIF_PARAM;

		if (m_ctrlTab.GetItem(nTab, &tabItem) == TRUE)
			pLinguetta = (STRUCT_LINGUETTA*)tabItem.lParam;

		m_ctrlTab.SetCurSel(nTab);
	}

	m_report.SetLinguetta(pLinguetta);
	m_FrameWnd.RedrawWindow(NULL, NULL, RDW_INVALIDATE);
}

void CDisegnaOperatorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	OpenDialog(point);

	CDialog::OnLButtonDown(nFlags, point);
}

void CDisegnaOperatorDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	OpenDialog(point);

	CDialog::OnRButtonDown(nFlags, point);
}

void CDisegnaOperatorDlg::OpenDialog(CPoint p)
{
	if (ClientToLogical(p)) 
	{	
		STRUCT_LINGUETTA* pLinguetta = m_report.GetLinguetta();

		if (pLinguetta != NULL)
		{
			POSITION pos = pLinguetta->listCampi.GetHeadPosition();

			while(pos != NULL)
			{
				STRUCT_CAMPO campoTemp = pLinguetta->listCampi.GetAt(pos);

				if ((p.x >= campoTemp.lX) && (p.x < campoTemp.lX + campoTemp.lL) && (p.y >= campoTemp.lY) && (p.y < campoTemp.lY + campoTemp.lA))
				{
					pLinguetta->listCampi.RemoveAt(pos);
					pLinguetta->listCampi.AddTail(campoTemp);
					m_report.SetCurSel(pLinguetta->listCampi.GetTailPosition());

					CPropCampoDlg dlg(this, &m_report);
					if (dlg.DoModal() != IDCANCEL)
					{
						m_ctrlButtonSave.EnableWindow((long)m_ctrlCombo.GetItemData(m_ctrlCombo.GetCurSel()) == VAL_RICERCA ? FALSE : TRUE);
						m_ctrlButtonUndo.EnableWindow(TRUE);
						m_ctrlButtonSoloQuesto.EnableWindow(FALSE);
						m_ctrlButtonSaveOver.EnableWindow(TRUE);
						m_ctrlCombo.EnableWindow(FALSE);
						GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
					}

					break;
				}

				pLinguetta->listCampi.GetNext(pos);
			}
		}
	}
}

BOOL CDisegnaOperatorDlg::ClientToLogical(CPoint &point)
{		
	CRect rectPage;
	GetDlgItem(IDC_STATIC_FRAME)->GetWindowRect(rectPage);
	ScreenToClient(rectPage);

	if (!rectPage.PtInRect(point))
		return FALSE;

	float dimX = (float)rectPage.Width() / (float)DEF_X2;
	float dimY = (float)rectPage.Height() / (float)DEF_Y;

	point.Offset(-rectPage.left, -rectPage.top);

	point.x = (long)((float)point.x / dimX);
	point.y = (long)((float)point.y / dimY);

	TRACE2("-> X=%li - Y=%li\n", point.x, point.y);

	return TRUE;
}

void CDisegnaOperatorDlg::OnBnClickedBtnSave()
{
	CDynVersioneSet setDynVersione;

	int nCurSel = m_ctrlCombo.GetCurSel();
	if (nCurSel >= 0)
	{
		m_lIDVersione = 0;
		long lTipoEsame = (long)m_ctrlCombo.GetItemData(nCurSel);

		setDynVersione.SetSortRecord("DataOra DESC, ID DESC");
		if (setDynVersione.OpenRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSave"))
		{
			if (setDynVersione.AddNewRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSave"))
			{
				setDynVersione.m_lIDTipoEsame = lTipoEsame;

				if (setDynVersione.UpdateRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSave"))
					m_lIDVersione = setDynVersione.GetLastAdd();
			}

			setDynVersione.CloseRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSave");
		}

		if (m_lIDVersione > 0)
			SalvaInterfaccia(m_lIDVersione);
	}
}

void CDisegnaOperatorDlg::OnBnClickedBtnUndo()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DISEGNA_INTERFACCIA_UNDO), MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
	{
		OnCbnSelchangeComboEsame();

		m_ctrlButtonSave.EnableWindow(FALSE);
		m_ctrlButtonUndo.EnableWindow(FALSE);
		m_ctrlButtonSoloQuesto.EnableWindow(TRUE);
		m_ctrlButtonSaveOver.EnableWindow(FALSE);
		m_ctrlCombo.EnableWindow(TRUE);
		GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
	}
}

void CDisegnaOperatorDlg::OnBnClickedBtnCopy()
{
	CTipoEsameNewDlg dlg(this, m_pEsamiView, TRUE, TRUE, 0);
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.GetTipoEsame() == VAL_RICERCA)
		{
			CaricaInterfaccia(1);
		}
		else
		{
			long lIDVersione = -1;

			CString strBaseFilter;
			strBaseFilter.Format("UO=%li", dlg.GetUO());

			CString strOpenFilter;
			strOpenFilter.Format("IDTipoEsame=%li OR IDTipoEsame=0", dlg.GetTipoEsame());

			CDynVersioneSet setDynVersione;
			setDynVersione.SetBaseFilter(strBaseFilter);
			setDynVersione.SetOpenFilter(strOpenFilter);
			setDynVersione.SetSortRecord("DataOra DESC, ID DESC");
			if (setDynVersione.OpenRecordset("CEsamiView::OnEsameNew") == TRUE)
			{
				if (!setDynVersione.IsEOF())
					lIDVersione = setDynVersione.m_lID;

				setDynVersione.CloseRecordset("CEsamiView::OnEsameNew");
			}

			CaricaInterfaccia(lIDVersione);
		}

		m_ctrlButtonSave.EnableWindow((long)m_ctrlCombo.GetItemData(m_ctrlCombo.GetCurSel()) == VAL_RICERCA ? FALSE : TRUE);
		m_ctrlButtonUndo.EnableWindow(TRUE);
		m_ctrlButtonSoloQuesto.EnableWindow(FALSE);
		m_ctrlButtonSaveOver.EnableWindow(TRUE);
		m_ctrlCombo.EnableWindow(FALSE);
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	}
}

void CDisegnaOperatorDlg::OnBnClickedBtnSoloQuesto()
{
	if (CPasswordDlg(NULL, theApp.GetMessageString(IDS_PASSWORD_DISEGNAOPERATORSOLOQUESTO), "nautilus").DoModal() != IDOK)
		return;
	
	if (theApp.MessageBoxEndo(theApp.GetMessageString(IDS_DISEGNAOPERATOR_ALERT1), theApp.GetMessageString(IDS_ACHTUNG), MB_YESNO | MB_ICONSTOP) != IDYES)
		return;
	
	BeginWaitCursor();
	CDynCampoSet DynCampoSet; //theApp.m_dbEndox.ExecuteSQL("DELETE FROM DynCampo");
	if (DynCampoSet.OpenRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSoloQuesto"))
	{
		while(!DynCampoSet.IsEOF())
		{
			DynCampoSet.DeleteRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSoloQuesto");
			DynCampoSet.MoveNext();
		}
		DynCampoSet.CloseRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSoloQuesto");
	}

	CDynFormSet DynFormSet; //theApp.m_dbEndox.ExecuteSQL("DELETE FROM DynForm");
	if (DynFormSet.OpenRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSoloQuesto"))
	{
		while(!DynFormSet.IsEOF())
		{
			DynFormSet.DeleteRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSoloQuesto");
			DynFormSet.MoveNext();
		}
		DynFormSet.CloseRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSoloQuesto");
	}

	CDynVersioneSet DynVersioneSet;
	if (DynVersioneSet.OpenRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSoloQuesto"))
	{
		while(!DynVersioneSet.IsEOF())
		{
			if (DynVersioneSet.m_lID == 1)
			{
				DynVersioneSet.EditRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSoloQuesto");
				DynVersioneSet.m_lIDTipoEsame = 0;
				if (DynVersioneSet.UpdateRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSoloQuesto"))
					SalvaInterfaccia(1);
			}
			else
			{
				DynVersioneSet.DeleteRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSoloQuesto");
			}

			DynVersioneSet.MoveNext();
		}
		DynVersioneSet.CloseRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSoloQuesto");
	}

	CEsamiSet().ResetVersionID(); //theApp.m_dbEndox.ExecuteSQL("UPDATE EEsami SET IDVersione=1 WHERE IDVersione<>1");
	EndWaitCursor();
}

void CDisegnaOperatorDlg::OnBnClickedBtnSaveOver()
{
	if (CPasswordDlg(NULL, theApp.GetMessageString(IDS_PASSWORD_DISEGNAOPERATORSAVEOVER), "nautilus").DoModal() != IDOK)
		return;
	
	if (theApp.MessageBoxEndo(theApp.GetMessageString(IDS_DISEGNAOPERATOR_ALERT2), theApp.GetMessageString(IDS_ACHTUNG), MB_YESNO | MB_ICONSTOP) != IDYES)
		return;
	
	//
 	if (m_lIDVersione <= 0)
	{
		OnBnClickedBtnSave();
		return;
	}

	//
	CDynFormSet DynFormSet;
	CString strFilter;
	strFilter.Format("IDVersione=%li", m_lIDVersione);
	DynFormSet.SetOpenFilter(strFilter);
	if (DynFormSet.OpenRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSaveOver"))
	{
		while (!DynFormSet.IsEOF())
		{
			DynFormSet.DeleteRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSaveOver");

			CDynCampoSet DynCampoSet;
			strFilter.Format("IDForm = %li", DynFormSet.m_lID);
			DynCampoSet.SetOpenFilter(strFilter);
			if (DynCampoSet.OpenRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSaveOver"))
			{
				while (!DynCampoSet.IsEOF())
				{
					DynCampoSet.DeleteRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSaveOver");
					DynCampoSet.MoveNext();
				}
				DynCampoSet.CloseRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSaveOver");
			}

			DynFormSet.MoveNext();
		}
		DynFormSet.CloseRecordset("CDisegnaOperatorDlg::OnBnClickedBtnSaveOver");
	}

	SalvaInterfaccia(m_lIDVersione);
}
