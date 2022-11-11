#include "stdafx.h"
#include "Endox.h"
#include "MstOsservazioniUseDlg.h"

#include "EsamiView.h"
#include "MstOsservazioniSet.h"
#include "OsservazioniForm.h"
#include "EsamiSet.h"
#include "TipiEsamiOrganiSet.h"
#include "MstOrganoSet.h"
#include "SedeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstOsservazioniUseDlg, CEndoxResizableDlg)

CMstOsservazioniUseDlg::CMstOsservazioniUseDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(CMstOsservazioniUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	ASSERT(pEsamiView->m_pDynForm[sub_osservazioni] != NULL);

	m_pEsamiView = pEsamiView;
	m_pFormOsservazioni = NULL;
	m_pFormParent = (COsservazioniForm*)pEsamiView->m_pDynForm[sub_osservazioni];

	m_lTipoEsame = m_pEsamiView->m_pEsamiSet->m_lIDEsame;

	m_setOsservazioni.SetEmpty();
}

CMstOsservazioniUseDlg::~CMstOsservazioniUseDlg()
{
	if (m_pFormOsservazioni != NULL)
		delete m_pFormOsservazioni;
}

BEGIN_MESSAGE_MAP(CMstOsservazioniUseDlg, CEndoxResizableDlg)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()

	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_LBN_SELCHANGE(IDC_LIST_ORGANI, OnLbnSelchangeListOrgani)

	ON_LBN_SELCHANGE(IDC_LIST_LEVEL0, OnLbnSelchangeListLevel0)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL1, OnLbnSelchangeListLevel1)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL2, OnLbnSelchangeListLevel2)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL3, OnLbnSelchangeListLevel3)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL4, OnLbnSelchangeListLevel4)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL5, OnLbnSelchangeListLevel5)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL6, OnLbnSelchangeListLevel6)

	ON_BN_CLICKED(IDC_AGGIUNGI, OnBnClickedAggiungi)
END_MESSAGE_MAP()

void CMstOsservazioniUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LABEL_ORGANO,   m_ctrlStaticOrgano);
	DDX_Control(pDX, IDC_STATIC_SEDE,    m_ctrlStaticSede);
	DDX_Control(pDX, IDC_STATIC_TERMINI, m_ctrlStaticTerm);
	DDX_Control(pDX, IDC_AGGIUNGI,       m_ctrlButtonAdd);
	DDX_Control(pDX, IDCANCEL,           m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK,               m_ctrlButtonOK);

	DDX_Control(pDX, IDC_LIST_ORGANI, m_ctrlListOrgani);
	DDX_Control(pDX, IDC_TREE_SEDI, m_ctrlTreeSedi);

	DDX_Control(pDX, IDC_LIST_LEVEL0, m_ctrlListLevel0);
	DDX_Control(pDX, IDC_LIST_LEVEL1, m_ctrlListLevel1);
	DDX_Control(pDX, IDC_LIST_LEVEL2, m_ctrlListLevel2);
	DDX_Control(pDX, IDC_LIST_LEVEL3, m_ctrlListLevel3);
	DDX_Control(pDX, IDC_LIST_LEVEL4, m_ctrlListLevel4);
	DDX_Control(pDX, IDC_LIST_LEVEL5, m_ctrlListLevel5);
	DDX_Control(pDX, IDC_LIST_LEVEL6, m_ctrlListLevel6);

	DDX_Control(pDX, IDC_FRAME_OSSERVAZIONI, m_ctrlStaticOsservazioni);
}

HBRUSH CMstOsservazioniUseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxResizableDlg::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_LABEL_ORGANO:
		case IDC_LIST_ORGANI:
			pDC->SetTextColor(theApp.m_color[0]);
			break;

		case IDC_STATIC_SEDE:
		case IDC_TREE_SEDI:
			pDC->SetTextColor(theApp.m_color[1]);
			break;

		case IDC_STATIC_TERMINI:
		case IDC_LIST_LEVEL0:
		case IDC_LIST_LEVEL1:
		case IDC_LIST_LEVEL2:
		case IDC_LIST_LEVEL3:
		case IDC_LIST_LEVEL4:
		case IDC_LIST_LEVEL5:
		case IDC_LIST_LEVEL6:
		case IDC_EDIT_FRASE:
			pDC->SetTextColor(theApp.m_color[2]);
			break;
	}

	return hBrush;
}

BOOL CMstOsservazioniUseDlg::OnInitDialog()
{
	BOOL bReturn = CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_LABEL_ORGANO, CSize(0, 0), CSize(25, 0));
	AddAnchor(IDC_LIST_ORGANI, CSize(0, 0), CSize(25, 50));
	AddAnchor(IDC_STATIC_SEDE, CSize(25, 0), CSize(50, 0));
	AddAnchor(IDC_TREE_SEDI, CSize(25, 0), CSize(50, 50));
	AddAnchor(IDC_STATIC_LINE1, CSize(0, 50), CSize(50, 50));
	AddAnchor(IDC_AGGIUNGI, CSize(0, 50), CSize(50, 50));
	AddAnchor(IDC_STATIC_LINE2, CSize(0, 50), CSize(50, 50));
	AddAnchor(IDC_FRAME_OSSERVAZIONI, CSize(0, 50), CSize(50, 100));
	AddAnchor(IDC_STATIC_LINE4, CSize(50, 0), CSize(50, 100));
	AddAnchor(IDC_STATIC_TERMINI, CSize(50, 0), CSize(100, 0));
	AddAnchor(IDC_LIST_LEVEL0, CSize(50, 0), CSize(75, 96));
	AddAnchor(IDC_LIST_LEVEL1, CSize(75, 0), CSize(100, 16));
	AddAnchor(IDC_LIST_LEVEL2, CSize(75, 16), CSize(100, 32));
	AddAnchor(IDC_LIST_LEVEL3, CSize(75, 32), CSize(100, 48));
	AddAnchor(IDC_LIST_LEVEL4, CSize(75, 48), CSize(100, 64));
	AddAnchor(IDC_LIST_LEVEL5, CSize(75, 64), CSize(100, 80));
	AddAnchor(IDC_LIST_LEVEL6, CSize(75, 80), CSize(100, 96));
	AddAnchor(IDC_EDIT_FRASE, CSize(50, 96), CSize(100, 100));
	AddAnchor(IDC_STATIC_LINE5, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDCANCEL, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));

	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_LABEL_ORGANO)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_SEDE)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_TERMINI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_AGGIUNGI)->SetFont(&theApp.m_fontBold);

	m_ctrlTreeSedi.SetTextColor(theApp.m_color[1]);

	COsservazioniForm::CreateFormEx(this, &m_ctrlStaticOsservazioni, m_pEsamiView, &m_pFormOsservazioni);

	theApp.LocalizeDialog(this, CMstOsservazioniUseDlg::IDD, "MstOsservazioniUseDlg");

	// In modalità ricerca abilito solo la prima "riga" della form
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		m_pFormOsservazioni->SendMessage(MSG_FORM_READONLY, (WPARAM)TRUE);
		m_pFormOsservazioni->SendMessage(MSG_FORM_READONLY, (WPARAM)FALSE);

		SetDlgItemText(IDC_AGGIUNGI, theApp.GetMessageString(IDS_MSTOSSERVAZIONIUSE_BUTTON_1));
		SetDlgItemText(IDOK,         theApp.GetMessageString(IDS_MSTOSSERVAZIONIUSE_BUTTON_3));
	}

	LoadForm();
	UpdateData(FALSE);

	RiempiListOrgani();

	//
	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	//
	return bReturn;
}

void CMstOsservazioniUseDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	SaveForm();

	OnOK();
}

void CMstOsservazioniUseDlg::CreaFrase()
{
	int iTemp;
	CString strTemp;
	CString strValue = "";

	iTemp = m_ctrlListLevel0.GetCurSel();
	if (iTemp >= 0)
	{
		m_ctrlListLevel0.GetText(iTemp, strValue);

		iTemp = m_ctrlListLevel1.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel1.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}

		iTemp = m_ctrlListLevel2.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel2.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}

		iTemp = m_ctrlListLevel3.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel3.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}

		iTemp = m_ctrlListLevel4.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel4.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}

		iTemp = m_ctrlListLevel5.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel5.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}

		iTemp = m_ctrlListLevel6.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel6.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}
	}

	SetDlgItemText(IDC_EDIT_FRASE, strValue);
}

void CMstOsservazioniUseDlg::RiempiListOrgani()
{
	int iTemp;

	m_ctrlListOrgani.ResetContent();

	CString strTemp;
	CTipiEsamiOrganiSet setJoin;
	CMstOrganoSet setOrgano;
	
	strTemp.Format("TipoEsame=%li", m_lTipoEsame);
	setJoin.SetOpenFilter(strTemp);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		CMstOrganoSet setTemp;

		if (setTemp.OpenRecordset("CMstOsservazioniUseDlg::RiempiListOrgani") == TRUE)
		{
			while (!setTemp.IsEOF())
			{
				iTemp = m_ctrlListOrgani.AddString(setTemp.m_sOrgano);
				m_ctrlListOrgani.SetItemData(iTemp, (long)setTemp.m_lContatore);
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMstOsservazioniUseDlg::RiempiListOrgani");
		}
	}
	else if (setJoin.OpenRecordset("CMstOsservazioniUseDlg::RiempiListOrgani") == TRUE)
	{
		while(setJoin.IsEOF() == FALSE)
		{
			strTemp.Format("Contatore=%li", setJoin.m_lOrgano);
			setOrgano.SetOpenFilter(strTemp);

			if (setOrgano.OpenRecordset("CMstOsservazioniUseDlg::RiempiListOrgani") == TRUE)
			{
				if (setOrgano.IsEOF() == FALSE)
				{
					iTemp = m_ctrlListOrgani.AddString(setOrgano.m_sOrgano);
					m_ctrlListOrgani.SetItemData(iTemp, (long)setOrgano.m_lContatore);
				}
			}

			setJoin.MoveNext();
		}

		setOrgano.CloseRecordset("CMstOsservazioniUseDlg::RiempiListOrgani");
		setJoin.CloseRecordset("CMstOsservazioniUseDlg::RiempiListOrgani");
	}
}

void CMstOsservazioniUseDlg::RiempiTreeSedi()
{
	HTREEITEM hPadre;

	CString strTemp;
	strTemp.Format("Organo=%d and Padre=0", (int)m_ctrlListOrgani.GetItemData(m_ctrlListOrgani.GetCurSel()));

	m_ctrlTreeSedi.DeleteAllItems();

	CMstSediSet setTemp1;
	setTemp1.SetSortRecord("Descrizione");

	CMstSediSet setTemp2;
	setTemp2.SetSortRecord("Descrizione");

	setTemp1.SetBaseFilter(strTemp);
	if (setTemp1.OpenRecordset("CMstOsservazioniUseDlg::RiempiTreeSedi") == TRUE)
	{
		while(setTemp1.IsEOF() == FALSE)
		{
			hPadre = m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp1.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp1.m_lContatore, TVI_ROOT, TVI_LAST);

			strTemp.Format("Padre=%li", setTemp1.m_lContatore);
			setTemp2.SetOpenFilter(strTemp);
			if (setTemp2.OpenRecordset("CMstOsservazioniUseDlg::RiempiTreeSedi") == TRUE)
			{
				while(setTemp2.IsEOF() == FALSE)
				{
					m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp2.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp2.m_lContatore, hPadre, TVI_LAST);

					setTemp2.MoveNext();
				}

				setTemp2.CloseRecordset("CMstOsservazioniUseDlg::RiempiTreeSedi");
			}

			m_ctrlTreeSedi.Expand(hPadre, TVE_EXPAND);

			setTemp1.MoveNext();
		}

		setTemp1.CloseRecordset("CMstProcedureTerapeuticheUseDlg::RiempiTreeSedi");
	}
}

void CMstOsservazioniUseDlg::RiempiListLevel0()
{
	int iTemp = 0;
	CString strTemp;
	long lOrgano = m_ctrlListOrgani.GetCurSel();
	CMstOsservazioniSet setTemp;

	if (lOrgano >= 0)
		lOrgano = (long)m_ctrlListOrgani.GetItemData(lOrgano);

	strTemp.Format("Organo=%li", lOrgano);
	setTemp.SetBaseFilter(strTemp);
	setTemp.SetOpenFilter("Padre=0 AND Livello=0");
	setTemp.SetSortRecord("Descrizione");

	m_ctrlListLevel0.ResetContent();

	if (setTemp.OpenRecordset("CMstOsservazioniUseDlg::RiempiListLevel0") == TRUE)
	{
		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListLevel0.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListLevel0.SetItemData(iTemp, (DWORD)setTemp.m_lContatore);
			
			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMstOsservazioniUseDlg::RiempiListLevel0");
	}
}

void CMstOsservazioniUseDlg::RiempiListSubLevels()
{
	CListBox* pListLevel[] = { &m_ctrlListLevel1, &m_ctrlListLevel2, &m_ctrlListLevel3, &m_ctrlListLevel4, &m_ctrlListLevel5, &m_ctrlListLevel6 };

	int iTemp;
	int nTemp;
	long lPadre = m_ctrlListLevel0.GetCurSel();
	CString strTemp;
	CMstOsservazioniSet setTemp;

	setTemp.SetSortRecord("Descrizione");

	if (lPadre >= 0)
		lPadre = (long)m_ctrlListLevel0.GetItemData(lPadre);

	for(nTemp = 0; nTemp < 6; nTemp++)
	{
		iTemp = 0;

		pListLevel[nTemp]->ResetContent();

		strTemp.Format("Padre=%li AND Livello=%d", lPadre, nTemp + 1);
		setTemp.SetOpenFilter(strTemp);

		if (setTemp.OpenRecordset("CMstOsservazioniUseDlg::RiempiListSubLevels") == TRUE)
		{
			while(setTemp.IsEOF() == FALSE)
			{
				pListLevel[nTemp]->InsertString(iTemp, setTemp.m_sDescrizione);
				pListLevel[nTemp]->SetItemData(iTemp, (DWORD)setTemp.m_lContatore);

				iTemp++;
				setTemp.MoveNext();
			}
		}
	}

	setTemp.CloseRecordset("CMstOsservazioniUseDlg::RiempiListSubLevels");
}

void CMstOsservazioniUseDlg::OnLbnSelchangeListOrgani()
{
	RiempiTreeSedi();
	RiempiListLevel0();
	RiempiListSubLevels();

	CreaFrase();
}

void CMstOsservazioniUseDlg::OnLbnSelchangeListLevel0()
{
	RiempiListSubLevels();

	CreaFrase();
}

void CMstOsservazioniUseDlg::OnLbnSelchangeListLevel1()
{
	CreaFrase();
}

void CMstOsservazioniUseDlg::OnLbnSelchangeListLevel2()
{
	CreaFrase();
}

void CMstOsservazioniUseDlg::OnLbnSelchangeListLevel3()
{
	CreaFrase();
}

void CMstOsservazioniUseDlg::OnLbnSelchangeListLevel4()
{
	CreaFrase();
}

void CMstOsservazioniUseDlg::OnLbnSelchangeListLevel5()
{
	CreaFrase();
}

void CMstOsservazioniUseDlg::OnLbnSelchangeListLevel6()
{
	CreaFrase();
}

void CMstOsservazioniUseDlg::OnSize(UINT nType, int cx, int cy)
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);

	if (m_pFormOsservazioni != NULL)
		m_pFormOsservazioni->SendMessage(EPM_RESIZE_FORM);
}

void CMstOsservazioniUseDlg::OnBnClickedAggiungi()
{
	int iOrgano;
	HTREEITEM hSedePadre;
	HTREEITEM hSedeSelez;

	m_setOsservazioni.m_lEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;

	iOrgano = m_ctrlListOrgani.GetCurSel();
	m_setOsservazioni.m_lOrgano = (iOrgano >= 0 ? (long)m_ctrlListOrgani.GetItemData(iOrgano) : 0);

	hSedeSelez = m_ctrlTreeSedi.GetSelectedItem();
	if (hSedeSelez != NULL)
	{
		hSedePadre = m_ctrlTreeSedi.GetParentItem(hSedeSelez);

		if ((hSedePadre != NULL) && (hSedePadre != hSedeSelez))
			m_setOsservazioni.m_sSede = m_ctrlTreeSedi.GetItemText(hSedePadre) + " " + m_ctrlTreeSedi.GetItemText(hSedeSelez);
		else
			m_setOsservazioni.m_sSede = m_ctrlTreeSedi.GetItemText(hSedeSelez);
	}
	else
	{
		m_setOsservazioni.m_sSede = "";
	}

	GetDlgItemText(IDC_EDIT_FRASE, m_setOsservazioni.m_sOsservazioni);

	UpdateData(TRUE);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		m_pFormOsservazioni->m_ctrLine[0].m_Set.CopyFieldFrom(&m_setOsservazioni);
		m_pFormOsservazioni->UpdateData(FALSE);
	}
	else
	{
		if (m_setOsservazioni.m_sOsservazioni.IsEmpty() == FALSE)
		{
			if ((m_pFormOsservazioni != NULL) && (m_pFormOsservazioni->UpdateNewDataLine(&m_setOsservazioni) == TRUE))
				UpdateData(FALSE);
		}
	}
}

void CMstOsservazioniUseDlg::ClearForm()
{
	CString sFilter;
	sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	COsservazioniSet setTemp;
	setTemp.SetOpenFilter(sFilter);
	setTemp.SetSortRecord("Contatore");
	if (setTemp.OpenRecordset("CMstOsservazioniUseDlg::ClearForm") == TRUE)
	{
		while (setTemp.IsEOF() == FALSE)
		{
			setTemp.DeleteRecordset("CMstOsservazioniUseDlg::ClearForm");

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMstOsservazioniUseDlg::ClearForm");
	}

	m_pFormOsservazioni->SendMessage(MSG_FORM_RESET);
}

void CMstOsservazioniUseDlg::LoadForm()
{
	if ((m_pFormOsservazioni != NULL) && (m_pFormParent != NULL))
		m_pFormOsservazioni->SendMessage(MSG_FORM_LOAD, (WPARAM)m_pFormParent);
}

void CMstOsservazioniUseDlg::SaveForm()
{
	if ((m_pFormOsservazioni != NULL) && (m_pFormParent != NULL))
		m_pFormParent->SendMessage(MSG_FORM_LOAD, (WPARAM)m_pFormOsservazioni);
}

BOOL CMstOsservazioniUseDlg::UpdateData(BOOL bSaveAndValidate)
{
	BOOL bResult = CEndoxResizableDlg::UpdateData(bSaveAndValidate);

	if (m_pFormOsservazioni != NULL)
		m_pFormOsservazioni->UpdateData(bSaveAndValidate);

	return bResult;
}