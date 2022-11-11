#include "stdafx.h"
#include "Endox.h"
#include "MstDiagnosiUseDlg.h"

#include "EsamiView.h"
#include "MstDiagnosiSet.h"
#include "DiagnosiForm.h"
#include "EsamiSet.h"
#include "MstOrganoSet.h"
#include "TipiEsamiOrganiSet.h"
#include "SedeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstDiagnosiUseDlg, CDialog)

CMstDiagnosiUseDlg::CMstDiagnosiUseDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CMstDiagnosiUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	ASSERT(pEsamiView->m_pDynForm[sub_diagnosi] != NULL);

	m_pEsamiView = pEsamiView;
	m_pFormDiagnosi = NULL;
	m_pFormParent = (CDiagnosiForm*)pEsamiView->m_pDynForm[sub_diagnosi];

	m_lTipoEsame = m_pEsamiView->m_pEsamiSet->m_lIDEsame;

	m_setDiagnosi.SetEmpty();
}

CMstDiagnosiUseDlg::~CMstDiagnosiUseDlg()
{
	if (m_pFormDiagnosi != NULL)
		delete m_pFormDiagnosi;
}

BEGIN_MESSAGE_MAP(CMstDiagnosiUseDlg, CDialog)
	ON_WM_CTLCOLOR()

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
	ON_BN_CLICKED(IDC_RESETTA, OnBnClickedResetta)
END_MESSAGE_MAP()

void CMstDiagnosiUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LABEL_ORGANO,   m_ctrlStaticOrgano);
	DDX_Control(pDX, IDC_STATIC_SEDE,    m_ctrlStaticSede);
	DDX_Control(pDX, IDC_STATIC_TERMINI, m_ctrlStaticTerm);
	DDX_Control(pDX, IDC_AGGIUNGI,       m_ctrlButtonAdd);
	DDX_Control(pDX, IDC_RESETTA,        m_ctrlButtonReset);
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

	DDX_Control(pDX, IDC_FRAME_DIAGNOSI, m_ctrlStaticDiagnosi);
}

HBRUSH CMstDiagnosiUseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

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

BOOL CMstDiagnosiUseDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_LABEL_ORGANO)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_SEDE)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_TERMINI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_AGGIUNGI)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_RESETTA)->SetFont(&theApp.m_fontBold);

	m_ctrlTreeSedi.SetTextColor(theApp.m_color[1]);

	CDiagnosiForm::CreateFormEx(this, &m_ctrlStaticDiagnosi, m_pEsamiView, &m_pFormDiagnosi);

	theApp.LocalizeDialog(this, CMstDiagnosiUseDlg::IDD, "MstDiagnosiUseDlg");

	// In modalità ricerca abilito solo la prima "riga" della form
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		m_pFormDiagnosi->SendMessage(MSG_FORM_READONLY, (WPARAM)TRUE);
		m_pFormDiagnosi->SendMessage(MSG_FORM_READONLY, (WPARAM)FALSE);

		SetDlgItemText(IDC_AGGIUNGI, theApp.GetMessageString(IDS_MSTDIAGNOSIUSE_ADD));
		SetDlgItemText(IDC_RESETTA,  theApp.GetMessageString(IDS_MSTDIAGNOSIUSE_RESET));
		SetDlgItemText(IDOK,         theApp.GetMessageString(IDS_MSTDIAGNOSIUSE_OK));
	}

	LoadForm();
	UpdateData(FALSE);

	RiempiListOrgani();

	return bReturn;
}

void CMstDiagnosiUseDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	SaveForm();

	OnOK();
}

void CMstDiagnosiUseDlg::CreaFrase()
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

void CMstDiagnosiUseDlg::RiempiListOrgani()
{
	int iTemp;

	m_ctrlListOrgani.ResetContent();

	CMstOrganoSet setOrgano;
	
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		if (setOrgano.OpenRecordset("CMstDiagnosiUseDlg::RiempiListOrgani") == TRUE)
		{
			while(!setOrgano.IsEOF())
			{
				iTemp = m_ctrlListOrgani.AddString(setOrgano.m_sOrgano);
				m_ctrlListOrgani.SetItemData(iTemp, (long)setOrgano.m_lContatore);
				setOrgano.MoveNext();
			}
		}
	}
	else
	{
		CString strTemp;
		CTipiEsamiOrganiSet setJoin;
		
		strTemp.Format("TipoEsame=%li", m_lTipoEsame);
		setJoin.SetOpenFilter(strTemp);

		if (setJoin.OpenRecordset("CMstDiagnosiUseDlg::RiempiListOrgani") == TRUE)
		{
			while(setJoin.IsEOF() == FALSE)
			{
				strTemp.Format("Contatore=%li", setJoin.m_lOrgano);
				setOrgano.SetOpenFilter(strTemp);

				if (setOrgano.OpenRecordset("CMstDiagnosiUseDlg::RiempiListOrgani") == TRUE)
				{
					if (setOrgano.IsEOF() == FALSE)
					{
						iTemp = m_ctrlListOrgani.AddString(setOrgano.m_sOrgano);
						m_ctrlListOrgani.SetItemData(iTemp, (long)setOrgano.m_lContatore);
					}
				}

				setJoin.MoveNext();
			}

			setJoin.CloseRecordset("CMstDiagnosiUseDlg::RiempiListOrgani");
		}
	}

	setOrgano.CloseRecordset("CMstDiagnosiUseDlg::RiempiListOrgani");
}

void CMstDiagnosiUseDlg::RiempiTreeSedi()
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
	if (setTemp1.OpenRecordset("CMstDiagnosiUseDlg::RiempiTreeSedi") == TRUE)
	{
		while(setTemp1.IsEOF() == FALSE)
		{
			hPadre = m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp1.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp1.m_lContatore, TVI_ROOT, TVI_LAST);

			strTemp.Format("Padre=%li", setTemp1.m_lContatore);
			setTemp2.SetOpenFilter(strTemp);
			if (setTemp2.OpenRecordset("CMstDiagnosiUseDlg::RiempiTreeSedi") == TRUE)
			{
				while(setTemp2.IsEOF() == FALSE)
				{
					m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp2.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp2.m_lContatore, hPadre, TVI_LAST);

					setTemp2.MoveNext();
				}

				setTemp2.CloseRecordset("CMstDiagnosiUseDlg::RiempiTreeSedi");
			}

			m_ctrlTreeSedi.Expand(hPadre, TVE_EXPAND);

			setTemp1.MoveNext();
		}

		setTemp1.CloseRecordset("CMstProcedureTerapeuticheUseDlg::RiempiTreeSedi");
	}
}

void CMstDiagnosiUseDlg::RiempiListLevel0()
{
	int iTemp = 0;
	CString strTemp;
	long lOrgano = m_ctrlListOrgani.GetCurSel();
	CMstDiagnosiSet setTemp;

	if (lOrgano >= 0)
		lOrgano = (long)m_ctrlListOrgani.GetItemData(lOrgano);

	strTemp.Format("Organo=%li", lOrgano);
	setTemp.SetBaseFilter(strTemp);
	setTemp.SetOpenFilter("Padre=0 AND Livello=0");
	setTemp.SetSortRecord("Descrizione");

	m_ctrlListLevel0.ResetContent();

	if (setTemp.OpenRecordset("CMstDiagnosiUseDlg::RiempiListLevel0") == TRUE)
	{
		while(setTemp.IsEOF() == FALSE)
		{
			m_ctrlListLevel0.InsertString(iTemp, setTemp.m_sDescrizione);
			m_ctrlListLevel0.SetItemData(iTemp, (DWORD)setTemp.m_lContatore);
			
			iTemp++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CMstDiagnosiUseDlg::RiempiListLevel0");
	}
}

void CMstDiagnosiUseDlg::RiempiListSubLevels()
{
	CListBox* pListLevel[] = { &m_ctrlListLevel1, &m_ctrlListLevel2, &m_ctrlListLevel3, &m_ctrlListLevel4, &m_ctrlListLevel5, &m_ctrlListLevel6 };

	int iTemp;
	int nTemp;
	long lPadre = m_ctrlListLevel0.GetCurSel();
	CString strTemp;
	CMstDiagnosiSet setTemp;

	setTemp.SetSortRecord("Descrizione");

	if (lPadre >= 0)
		lPadre = (long)m_ctrlListLevel0.GetItemData(lPadre);

	for(nTemp = 0; nTemp < 6; nTemp++)
	{
		iTemp = 0;

		pListLevel[nTemp]->ResetContent();

		strTemp.Format("Padre=%li AND Livello=%d", lPadre, nTemp + 1);
		setTemp.SetOpenFilter(strTemp);

		if (setTemp.OpenRecordset("CMstDiagnosiUseDlg::RiempiListSubLevels") == TRUE)
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

	setTemp.CloseRecordset("CMstDiagnosiUseDlg::RiempiListSubLevels");
}

void CMstDiagnosiUseDlg::OnLbnSelchangeListOrgani()
{
	RiempiTreeSedi();
	RiempiListLevel0();
	RiempiListSubLevels();

	CreaFrase();
}

void CMstDiagnosiUseDlg::OnLbnSelchangeListLevel0()
{
	RiempiListSubLevels();

	CreaFrase();
}

void CMstDiagnosiUseDlg::OnLbnSelchangeListLevel1()
{
	CreaFrase();
}

void CMstDiagnosiUseDlg::OnLbnSelchangeListLevel2()
{
	CreaFrase();
}

void CMstDiagnosiUseDlg::OnLbnSelchangeListLevel3()
{
	CreaFrase();
}

void CMstDiagnosiUseDlg::OnLbnSelchangeListLevel4()
{
	CreaFrase();
}

void CMstDiagnosiUseDlg::OnLbnSelchangeListLevel5()
{
	CreaFrase();
}

void CMstDiagnosiUseDlg::OnLbnSelchangeListLevel6()
{
	CreaFrase();
}

void CMstDiagnosiUseDlg::OnBnClickedAggiungi()
{
	int iOrgano;
	HTREEITEM hSedePadre;
	HTREEITEM hSedeSelez;

	m_setDiagnosi.m_lEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;

	iOrgano = m_ctrlListOrgani.GetCurSel();
	m_setDiagnosi.m_lOrgano = (iOrgano >= 0 ? (long)m_ctrlListOrgani.GetItemData(iOrgano) : 0);

	hSedeSelez = m_ctrlTreeSedi.GetSelectedItem();
	if (hSedeSelez != NULL)
	{
		hSedePadre = m_ctrlTreeSedi.GetParentItem(hSedeSelez);

		if ((hSedePadre != NULL) && (hSedePadre != hSedeSelez))
			m_setDiagnosi.m_sSede = m_ctrlTreeSedi.GetItemText(hSedePadre) + " " + m_ctrlTreeSedi.GetItemText(hSedeSelez);
		else
			m_setDiagnosi.m_sSede = m_ctrlTreeSedi.GetItemText(hSedeSelez);
	}
	else
	{
		m_setDiagnosi.m_sSede = "";
	}

	GetDlgItemText(IDC_EDIT_FRASE, m_setDiagnosi.m_sDiagnosi);

	UpdateData(TRUE);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		m_pFormDiagnosi->m_ctrLine[0].m_Set.CopyFieldFrom(&m_setDiagnosi);
		m_pFormDiagnosi->UpdateData(FALSE);
	}
	else
	{
		if (!m_setDiagnosi.m_sDiagnosi.IsEmpty())
			if ((m_pFormDiagnosi != NULL) && (m_pFormDiagnosi->UpdateNewDataLine(&m_setDiagnosi) == TRUE))
				UpdateData(FALSE);
	}
}

void CMstDiagnosiUseDlg::OnBnClickedResetta()
{
	CString strTemp;

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		strTemp = theApp.GetMessageString(IDS_MSTDIAGNOSI_CONFIRM_DEL_3);
	else
		strTemp = theApp.GetMessageString(IDS_MSTDIAGNOSI_CONFIRM_DEL_4);

	if (theApp.AfxMessageBoxEndo(strTemp, MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		ClearForm();
		UpdateData(FALSE);
	}
}

void CMstDiagnosiUseDlg::ClearForm()
{
	CString sFilter;
	sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	CDiagnosiSet setTemp;
	setTemp.SetOpenFilter(sFilter);
	setTemp.SetSortRecord("Contatore");
	if (setTemp.OpenRecordset("CMstDiagnosiUseDlg::ClearForm") == TRUE)
	{
		while (!setTemp.IsEOF())
		{
			setTemp.DeleteRecordset("CMstDiagnosiUseDlg::ClearForm");
			setTemp.MoveNext();
		}
		setTemp.CloseRecordset("CMstDiagnosiUseDlg::ClearForm");
	}

	m_pFormDiagnosi->SendMessage(MSG_FORM_RESET);
}

void CMstDiagnosiUseDlg::LoadForm()
{
	if (m_pFormDiagnosi != NULL && m_pFormParent != NULL)
		m_pFormDiagnosi->SendMessage(MSG_FORM_LOAD, (WPARAM)m_pFormParent);
}

void CMstDiagnosiUseDlg::SaveForm()
{
	if (m_pFormDiagnosi != NULL && m_pFormParent != NULL)
		m_pFormParent->SendMessage(MSG_FORM_LOAD, (WPARAM)m_pFormDiagnosi);
}

BOOL CMstDiagnosiUseDlg::UpdateData(BOOL bSaveAndValidate)
{
	BOOL bResult = CDialog::UpdateData(bSaveAndValidate);

	if (m_pFormDiagnosi != NULL)
		m_pFormDiagnosi->UpdateData(bSaveAndValidate);

	return bResult;
}