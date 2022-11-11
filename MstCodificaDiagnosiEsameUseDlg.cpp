#include "stdafx.h"
#include "Endox.h"
#include "MstCodificaDiagnosiEsameUseDlg.h"

#include "CodificaDiagnosiEsameForm.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "MstCodificaDiagnosiEsameSet.h"
#include "MstOrganoSet.h"
#include "RicercaCodificaDiagnosiEsameSet.h"
#include "SedeSet.h"
#include "TipiEsamiOrganiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstCodificaDiagnosiEsameUseDlg, CDialog)

CMstCodificaDiagnosiEsameUseDlg::CMstCodificaDiagnosiEsameUseDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CMstCodificaDiagnosiEsameUseDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	ASSERT(pEsamiView->m_pDynForm[sub_codificadiagnosiesame] != NULL);

	m_pEsamiView = pEsamiView;
	m_pFormCodificaDiagnosiEsame = NULL;
	m_pFormParent = (CCodificaDiagnosiEsameForm*)pEsamiView->m_pDynForm[sub_codificadiagnosiesame];

	m_lTipoEsame = m_pEsamiView->m_pEsamiSet->m_lIDEsame;

	m_setCodificaDiagnosiEsame.SetEmpty();
}

CMstCodificaDiagnosiEsameUseDlg::~CMstCodificaDiagnosiEsameUseDlg()
{
	if (m_pFormCodificaDiagnosiEsame != NULL)
		delete m_pFormCodificaDiagnosiEsame;
}

BEGIN_MESSAGE_MAP(CMstCodificaDiagnosiEsameUseDlg, CDialog)
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
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL7, OnLbnSelchangeListLevel7)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL8, OnLbnSelchangeListLevel8)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL9, OnLbnSelchangeListLevel9)
	ON_LBN_SELCHANGE(IDC_LIST_LEVEL10, OnLbnSelchangeListLevel10)

	ON_BN_CLICKED(IDC_AGGIUNGI, OnBnClickedAggiungi)
	ON_BN_CLICKED(IDC_RESETTA, OnBnClickedResetta)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_SEDI, &CMstCodificaDiagnosiEsameUseDlg::OnTvnSelchangedTreeSedi)
END_MESSAGE_MAP()

void CMstCodificaDiagnosiEsameUseDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_LIST_LEVEL7, m_ctrlListLevel7);
	DDX_Control(pDX, IDC_LIST_LEVEL8, m_ctrlListLevel8);
	DDX_Control(pDX, IDC_LIST_LEVEL9, m_ctrlListLevel9);
	DDX_Control(pDX, IDC_LIST_LEVEL10, m_ctrlListLevel10);

	DDX_Control(pDX, IDC_FRAME_CODIFICADIAGNOSIESAME, m_ctrlStaticCodificaDiagnosiEsame);
	DDX_Control(pDX, IDC_FRAME_CODIFICADIAGNOSIESAME2, m_ctrlStaticCodificaDiagnosiEsame2);
}

HBRUSH CMstCodificaDiagnosiEsameUseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		case IDC_LIST_LEVEL7:
		case IDC_LIST_LEVEL8:
		case IDC_LIST_LEVEL9:
		case IDC_LIST_LEVEL10:
		case IDC_EDIT_FRASE:
			pDC->SetTextColor(theApp.m_color[2]);
			break;
	}

	return hBrush;
}

BOOL CMstCodificaDiagnosiEsameUseDlg::OnInitDialog()
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

	CCodificaDiagnosiEsameForm::CreateFormEx(this, &m_ctrlStaticCodificaDiagnosiEsame, m_pEsamiView, &m_pFormCodificaDiagnosiEsame);

	theApp.LocalizeDialog(this, CMstCodificaDiagnosiEsameUseDlg::IDD, "MstDiagnosiUseDlg");

	// In modalità ricerca abilito solo la prima "riga" della form
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		m_pFormCodificaDiagnosiEsame->SendMessage(MSG_FORM_READONLY, (WPARAM)TRUE);
		m_pFormCodificaDiagnosiEsame->SendMessage(MSG_FORM_READONLY, (WPARAM)FALSE);

		SetDlgItemText(IDC_AGGIUNGI, theApp.GetMessageString(IDS_MSTDIAGNOSIUSE_ADD));
		SetDlgItemText(IDC_RESETTA,  theApp.GetMessageString(IDS_MSTDIAGNOSIUSE_RESET));
		SetDlgItemText(IDOK,         theApp.GetMessageString(IDS_MSTDIAGNOSIUSE_OK));
	}

	LoadForm();
	UpdateData(FALSE);

	RiempiListOrgani();
	RiempiListLevel0();

	return bReturn;
}

void CMstCodificaDiagnosiEsameUseDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	SaveForm();

	OnOK();
}

void CMstCodificaDiagnosiEsameUseDlg::CreaFrase()
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

		iTemp = m_ctrlListLevel7.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel7.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}

		iTemp = m_ctrlListLevel8.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel8.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}
	
		iTemp = m_ctrlListLevel9.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel9.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}

		iTemp = m_ctrlListLevel10.GetCurSel();
		if (iTemp >= 0)
		{
			m_ctrlListLevel10.GetText(iTemp, strTemp);

			strValue = strValue + ", " + strTemp;
		}
	}

	SetDlgItemText(IDC_EDIT_FRASE, strValue);
}

void CMstCodificaDiagnosiEsameUseDlg::RiempiListOrgani()
{
	int iTemp;

	m_ctrlListOrgani.ResetContent();

	CMstOrganoSet setOrgano;
	
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		if (setOrgano.OpenRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiListOrgani") == TRUE)
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

		if (setJoin.OpenRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiListOrgani") == TRUE)
		{
			while(setJoin.IsEOF() == FALSE)
			{
				strTemp.Format("Contatore=%li", setJoin.m_lOrgano);
				setOrgano.SetOpenFilter(strTemp);

				if (setOrgano.OpenRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiListOrgani") == TRUE)
				{
					if (setOrgano.IsEOF() == FALSE)
					{
						iTemp = m_ctrlListOrgani.AddString(setOrgano.m_sOrgano);
						m_ctrlListOrgani.SetItemData(iTemp, (long)setOrgano.m_lContatore);
					}
				}

				setJoin.MoveNext();
			}

			setJoin.CloseRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiListOrgani");
		}
	}

	setOrgano.CloseRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiListOrgani");
}

void CMstCodificaDiagnosiEsameUseDlg::RiempiTreeSedi()
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
	if (setTemp1.OpenRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiTreeSedi") == TRUE)
	{
		while(setTemp1.IsEOF() == FALSE)
		{
			hPadre = m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp1.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp1.m_lContatore, TVI_ROOT, TVI_LAST);

			strTemp.Format("Padre=%li", setTemp1.m_lContatore);
			setTemp2.SetOpenFilter(strTemp);
			if (setTemp2.OpenRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiTreeSedi") == TRUE)
			{
				while(setTemp2.IsEOF() == FALSE)
				{
					m_ctrlTreeSedi.InsertItem(TVIF_PARAM | TVIF_TEXT, setTemp2.m_sDescrizione, 0, 0, 0, 0, (LPARAM)setTemp2.m_lContatore, hPadre, TVI_LAST);

					setTemp2.MoveNext();
				}

				setTemp2.CloseRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiTreeSedi");
			}

			m_ctrlTreeSedi.Expand(hPadre, TVE_EXPAND);

			setTemp1.MoveNext();
		}

		setTemp1.CloseRecordset("CMstProcedureTerapeuticheUseDlg::RiempiTreeSedi");
	}
}

void CMstCodificaDiagnosiEsameUseDlg::RiempiListLevel0()
{
	if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0)
	{
		// modalità normale //

		int iTemp = 0;
		CString strTemp;
		CMstCodificaDiagnosiEsameSet setTemp;

		strTemp.Format("TipoEsame=%li", m_lTipoEsame);
		setTemp.SetBaseFilter(strTemp);
		setTemp.SetOpenFilter("Padre=0 AND Livello=0");
		setTemp.SetSortRecord("Descrizione");

		m_ctrlListLevel0.ResetContent();

		if (setTemp.OpenRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiListLevel0") == TRUE)
		{
			while(setTemp.IsEOF() == FALSE)
			{
				m_ctrlListLevel0.InsertString(iTemp, setTemp.m_sDescrizione);
				m_ctrlListLevel0.SetItemData(iTemp, (DWORD)setTemp.m_lContatore);
				
				iTemp++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiListLevel0");
		}
	}
	else
	{
		// modalità ricerca //

		CRicercaCodificaDiagnosiEsameSet setTemp;

		m_ctrlListLevel0.ResetContent();

		if (setTemp.OpenRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiListLevel0"))
		{
			CString strPrev = "";

			while(!setTemp.IsEOF())
			{
				if (strPrev != setTemp.m_sDescr1)
				{
					strPrev = setTemp.m_sDescr1;

					m_ctrlListLevel0.AddString(setTemp.m_sDescr1);
				}

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiListLevel0");
		}
	}
}

void CMstCodificaDiagnosiEsameUseDlg::RiempiListSubLevels()
{
	CListBox* pListLevel[] = { &m_ctrlListLevel1, &m_ctrlListLevel2, &m_ctrlListLevel3, &m_ctrlListLevel4, &m_ctrlListLevel5, &m_ctrlListLevel6, &m_ctrlListLevel7, &m_ctrlListLevel8, &m_ctrlListLevel9, &m_ctrlListLevel10 };

	if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0)
	{
		// modalità normale //

		int iTemp;
		int nTemp;
		long lPadre = m_ctrlListLevel0.GetCurSel();
		CString strTemp;
		CMstCodificaDiagnosiEsameSet setTemp;

		setTemp.SetSortRecord("Descrizione");

		if (lPadre >= 0)
			lPadre = (long)m_ctrlListLevel0.GetItemData(lPadre);

		for(nTemp = 0; nTemp < 10; nTemp++)
		{
			iTemp = 0;

			pListLevel[nTemp]->ResetContent();

			strTemp.Format("Padre=%li AND Livello=%d", lPadre, nTemp + 1);
			setTemp.SetOpenFilter(strTemp);

			if (setTemp.OpenRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiListSubLevels") == TRUE)
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

		setTemp.CloseRecordset("CMstCodificaDiagnosiEsameUseDlg::RiempiListSubLevels");
	}
	else
	{
		// modalità ricerca //

		int nCurSel = m_ctrlListLevel0.GetCurSel();

		for(int i = 0; i < 10; i++)
			pListLevel[i]->ResetContent();

		if (nCurSel >= 0)
		{
			CRicercaCodificaDiagnosiEsameSet setTemp;

			CString strTemp;
			m_ctrlListLevel0.GetText(nCurSel, strTemp);
			strTemp.Replace("'", "''");

			setTemp.SetOpenFilter("DESCR1='" + strTemp + "'");
			if (setTemp.OpenRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListSubLevels"))
			{
				while(!setTemp.IsEOF())
				{
					if (!setTemp.IsFieldNull(&setTemp.m_lLevel2))
						if ((setTemp.m_lLevel2 > 0) && (setTemp.m_lLevel2 <= 10))
							pListLevel[setTemp.m_lLevel2 - 1]->AddString(setTemp.m_sDescr2);

					setTemp.MoveNext();
				}

				setTemp.CloseRecordset("CMstProcedureTerapeuticheUseDlg::RiempiListSubLevels");
			}
		}
	}
}

void CMstCodificaDiagnosiEsameUseDlg::OnLbnSelchangeListOrgani()
{
	RiempiTreeSedi();

	m_ctrlListLevel1.ResetContent();
	m_ctrlListLevel2.ResetContent();
	m_ctrlListLevel3.ResetContent();
	m_ctrlListLevel4.ResetContent();
	m_ctrlListLevel5.ResetContent();
	m_ctrlListLevel6.ResetContent();
	m_ctrlListLevel7.ResetContent();
	m_ctrlListLevel8.ResetContent();
	m_ctrlListLevel9.ResetContent();
	m_ctrlListLevel10.ResetContent();

	m_ctrlListLevel0.SetCurSel(-1);

	GetDlgItem(IDC_EDIT_FRASE)->SetWindowText("");

	CreaFrase();
}

void CMstCodificaDiagnosiEsameUseDlg::OnLbnSelchangeListLevel0()
{
	RiempiListSubLevels();

	CreaFrase();
}

void CMstCodificaDiagnosiEsameUseDlg::OnLbnSelchangeListLevel1()
{
	CreaFrase();
}

void CMstCodificaDiagnosiEsameUseDlg::OnLbnSelchangeListLevel2()
{
	CreaFrase();
}

void CMstCodificaDiagnosiEsameUseDlg::OnLbnSelchangeListLevel3()
{
	CreaFrase();
}

void CMstCodificaDiagnosiEsameUseDlg::OnLbnSelchangeListLevel4()
{
	CreaFrase();
}

void CMstCodificaDiagnosiEsameUseDlg::OnLbnSelchangeListLevel5()
{
	CreaFrase();
}

void CMstCodificaDiagnosiEsameUseDlg::OnLbnSelchangeListLevel6()
{
	CreaFrase();
}

void CMstCodificaDiagnosiEsameUseDlg::OnLbnSelchangeListLevel7()
{
	CreaFrase();
}

void CMstCodificaDiagnosiEsameUseDlg::OnLbnSelchangeListLevel8()
{
	CreaFrase();
}

void CMstCodificaDiagnosiEsameUseDlg::OnLbnSelchangeListLevel9()
{
	CreaFrase();
}

void CMstCodificaDiagnosiEsameUseDlg::OnLbnSelchangeListLevel10()
{
	CreaFrase();
}

void CMstCodificaDiagnosiEsameUseDlg::OnBnClickedAggiungi()
{
	int iOrgano;
	HTREEITEM hSedePadre;
	HTREEITEM hSedeSelez;

	m_setCodificaDiagnosiEsame.m_lEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;

	iOrgano = m_ctrlListOrgani.GetCurSel();
	m_setCodificaDiagnosiEsame.m_lOrgano = (iOrgano >= 0 ? (long)m_ctrlListOrgani.GetItemData(iOrgano) : 0);

	hSedeSelez = m_ctrlTreeSedi.GetSelectedItem();
	if (hSedeSelez != NULL)
	{
		hSedePadre = m_ctrlTreeSedi.GetParentItem(hSedeSelez);

		if ((hSedePadre != NULL) && (hSedePadre != hSedeSelez))
			m_setCodificaDiagnosiEsame.m_sSede = m_ctrlTreeSedi.GetItemText(hSedePadre) + " " + m_ctrlTreeSedi.GetItemText(hSedeSelez);
		else
			m_setCodificaDiagnosiEsame.m_sSede = m_ctrlTreeSedi.GetItemText(hSedeSelez);
	}
	else
	{
		m_setCodificaDiagnosiEsame.m_sSede = "";
	}

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		GetDlgItemText(IDC_EDIT_FRASE, m_setCodificaDiagnosiEsame.m_sDiagnosiEsame);
		m_setCodificaDiagnosiEsame.m_sDiagnosiEsame.Replace(", ", "%");

		UpdateData(TRUE);

		if (!m_setCodificaDiagnosiEsame.m_sDiagnosiEsame.IsEmpty())
			if ((m_pFormCodificaDiagnosiEsame != NULL) && (m_pFormCodificaDiagnosiEsame->UpdateNewDataLine(&m_setCodificaDiagnosiEsame)))
				UpdateData(FALSE);

		// m_pFormCodificaDiagnosiEsame->m_ctrLine[0].m_Set.CopyFieldFrom(&m_setCodificaDiagnosiEsame);
		// m_pFormCodificaDiagnosiEsame->UpdateData(FALSE);
	}
	else
	{
		GetDlgItemText(IDC_EDIT_FRASE, m_setCodificaDiagnosiEsame.m_sDiagnosiEsame);

		UpdateData(TRUE);

		if (!m_setCodificaDiagnosiEsame.m_sDiagnosiEsame.IsEmpty())
			if ((m_pFormCodificaDiagnosiEsame != NULL) && (m_pFormCodificaDiagnosiEsame->UpdateNewDataLine(&m_setCodificaDiagnosiEsame)))
				UpdateData(FALSE);
	}
}

void CMstCodificaDiagnosiEsameUseDlg::OnBnClickedResetta()
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

	// m_pFormCodificaDiagnosiEsame->ResetByUser();
	// UpdateData(FALSE);
}

void CMstCodificaDiagnosiEsameUseDlg::ClearForm()
{
	CString sFilter;
	sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	CCodificaDiagnosiEsameSet setTemp;
	setTemp.SetOpenFilter(sFilter);
	if (setTemp.OpenRecordset("CMstCodificaDiagnosiEsameUseDlg::ClearForm"))
	{
		while (!setTemp.IsEOF())
		{
			setTemp.DeleteRecordset("CMstCodificaDiagnosiEsameUseDlg::ClearForm");
			setTemp.MoveNext();
		}
		setTemp.CloseRecordset("CMstCodificaDiagnosiEsameUseDlg::ClearForm");
	}

	m_pFormCodificaDiagnosiEsame->SendMessage(MSG_FORM_RESET);
}

void CMstCodificaDiagnosiEsameUseDlg::LoadForm()
{
	if (m_pFormCodificaDiagnosiEsame != NULL && m_pFormParent != NULL)
		m_pFormCodificaDiagnosiEsame->SendMessage(MSG_FORM_LOAD, (WPARAM)m_pFormParent);
}

void CMstCodificaDiagnosiEsameUseDlg::SaveForm()
{
	if (m_pFormCodificaDiagnosiEsame != NULL && m_pFormParent != NULL)
		m_pFormParent->SendMessage(MSG_FORM_LOAD, (WPARAM)m_pFormCodificaDiagnosiEsame);
}

BOOL CMstCodificaDiagnosiEsameUseDlg::UpdateData(BOOL bSaveAndValidate)
{
	BOOL bResult = CDialog::UpdateData(bSaveAndValidate);

	if (m_pFormCodificaDiagnosiEsame != NULL)
		m_pFormCodificaDiagnosiEsame->UpdateData(bSaveAndValidate);

	return bResult;
}
void CMstCodificaDiagnosiEsameUseDlg::OnTvnSelchangedTreeSedi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	m_ctrlListLevel1.ResetContent();
	m_ctrlListLevel2.ResetContent();
	m_ctrlListLevel3.ResetContent();
	m_ctrlListLevel4.ResetContent();
	m_ctrlListLevel5.ResetContent();
	m_ctrlListLevel6.ResetContent();
	m_ctrlListLevel7.ResetContent();
	m_ctrlListLevel8.ResetContent();
	m_ctrlListLevel9.ResetContent();
	m_ctrlListLevel10.ResetContent();

	m_ctrlListLevel0.SetCurSel(-1);

	GetDlgItem(IDC_EDIT_FRASE)->SetWindowText("");

	*pResult = 0;
}
