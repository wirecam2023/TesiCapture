#include "stdafx.h"
#include "Endox.h"
#include "TabComboDlg.h"

#include "AddDescrDlg.h"
#include "ComboBoxSet.h"
#include "CustomDate.h"
#include "EsamiView.h"
#include "ExtList.h"
#include "MyPrintDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTabComboDlg::CTabComboDlg(CWnd* pParent, BOOL bMenu)
	: CDialog(CTabComboDlg::IDD, pParent)
{
	m_bActiveIsCodeCounter = FALSE;
	m_bActiveOrderByCode = FALSE;
	m_bMenu = bMenu;

	m_nActiveMaxLenCB = 0;

	m_lActiveComboDefine = -1;
	m_lActiveExtMode = 0;
	m_lSelected = 0;
}

CTabComboDlg::~CTabComboDlg()
{
}

void CTabComboDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_TABELLE, m_ctrlListCombo);

	DDX_Control(pDX, IDC_LIST_DESCR, m_ctrlListValue);
	
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_ELIMINA, m_ctrlButtonDelete);
	DDX_Control(pDX, IDC_MODIFICA, m_ctrlButtonModify);
	DDX_Control(pDX, IDC_NUOVO, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_STAMPA, m_ctrlButtonPrint);
}

BEGIN_MESSAGE_MAP(CTabComboDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN, OnBnClickedBtn)
	ON_BN_CLICKED(IDC_BTN_AZZERA, OnBnClickedBtnAzzera)

	ON_CBN_SELENDOK(IDC_COMBO_TABELLE, OnSelectComboBox)

	ON_LBN_SELCHANGE(IDC_LIST_DESCR, OnLbnSelchangeListDescr)

	ON_BN_CLICKED(IDC_ELIMINA, OnElimina)
	ON_BN_CLICKED(IDC_MODIFICA, OnModifica)
	ON_BN_CLICKED(IDC_NUOVO, OnNuovo)
	ON_BN_CLICKED(IDC_STAMPA, OnStampa) // DA CANCELLARE //

	ON_WM_DESTROY()

END_MESSAGE_MAP()


void CTabComboDlg::InsertPointerSet(CString sTitle, long lComboDefine, int nMaxLen, BOOL bIsCodeCounter, BOOL bOrderByCode)
{
	int nPos = m_ctrlListCombo.AddString(sTitle);
	if (nPos >= 0)
	{
		DATACOMBO* pDataCombo = new DATACOMBO;
		
		pDataCombo->nMaxLen = nMaxLen;
		pDataCombo->lExtMode = 0;
		pDataCombo->lComboDefine = lComboDefine;
		pDataCombo->bIsCodeCounter = bIsCodeCounter;
		pDataCombo->bOrderByCode = bOrderByCode;
		
		m_ctrlListCombo.SetItemDataPtr(nPos, pDataCombo);
	}
}

void CTabComboDlg::FillLabelList(long lComboDefine, BOOL bIsCodeCounter, BOOL bOrderByCode)
{
	m_ctrlListValue.ResetContent();

	if (lComboDefine < 0)
	{
		GetDlgItem(IDC_STAMPA)->EnableWindow(FALSE);
		GetDlgItem(IDC_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_MODIFICA)->EnableWindow(FALSE);
		GetDlgItem(IDC_ELIMINA)->EnableWindow(FALSE);

		return;
	}

	GetDlgItem(IDC_STAMPA)->EnableWindow(TRUE);
	GetDlgItem(IDC_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MODIFICA)->EnableWindow(TRUE);
	GetDlgItem(IDC_ELIMINA)->EnableWindow(TRUE);

	BeginWaitCursor();
	if (bOrderByCode)
	{
		m_ctrlListValue.SetRedraw(FALSE);

		CComboBoxSet setComboBox(lComboDefine);
		setComboBox.SetSortRecord("Contatore");
		if (setComboBox.OpenRecordset("CTabComboDlg::FillLabelList"))
		{
			long i = 0;
			while (!setComboBox.IsEOF())
			{
				setComboBox.m_sTesto.Trim();

				if (!setComboBox.m_sTesto.IsEmpty())
				{
					CString strValue;
					strValue.Format("%li) %s", i + 1, setComboBox.m_sTesto);
					
					m_ctrlListValue.InsertString(i, strValue);
					m_ctrlListValue.SetItemData(i, setComboBox.m_lContatore);

					i++;
				}
				
				setComboBox.MoveNext();
			}
			setComboBox.CloseRecordset("CTabComboDlg::FillLabelList");
		}

		m_ctrlListValue.SetRedraw(TRUE);
	}
	else
	{
		m_ctrlListValue.SetRedraw(FALSE);

		CComboBoxSet setComboBox(lComboDefine);
		setComboBox.SetSortRecord("Testo");
		if (setComboBox.OpenRecordset("CTabComboDlg::FillLabelList"))
		{
			long i = 0;
			while (!setComboBox.IsEOF())
			{
				setComboBox.m_sTesto.Trim();

				if (!setComboBox.m_sTesto.IsEmpty())
				{
					m_ctrlListValue.InsertString(i, setComboBox.m_sTesto);
					m_ctrlListValue.SetItemData(i, setComboBox.m_lContatore);

					i++;
				}
				
				setComboBox.MoveNext();
			}
			setComboBox.CloseRecordset("CTabComboDlg::FillLabelList");
		}

		m_ctrlListValue.SetRedraw(TRUE);
	}
	EndWaitCursor();

	UpdateData(FALSE);
}

void CTabComboDlg::FillLabelList(long lComboDefine, BOOL bIsCodeCounter, BOOL bOrderByCode, CString strRicerca)
{
	strRicerca.Trim();
	if (strRicerca.IsEmpty())
	{
		FillLabelList(lComboDefine, bIsCodeCounter, bOrderByCode);
		return;
	}

	m_ctrlListValue.ResetContent();

	if (lComboDefine < 0)
	{
		GetDlgItem(IDC_STAMPA)->EnableWindow(FALSE);
		GetDlgItem(IDC_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_MODIFICA)->EnableWindow(FALSE);
		GetDlgItem(IDC_ELIMINA)->EnableWindow(FALSE);

		return;
	}

	GetDlgItem(IDC_STAMPA)->EnableWindow(TRUE);
	GetDlgItem(IDC_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MODIFICA)->EnableWindow(TRUE);
	GetDlgItem(IDC_ELIMINA)->EnableWindow(TRUE);

	BeginWaitCursor();

	CString sFilter;
	sFilter.Format("Testo LIKE '%s%%'", strRicerca);

	CComboBoxSet setComboBox(lComboDefine);
	setComboBox.SetOpenFilter(sFilter);
	if (bOrderByCode)
	{
		m_ctrlListValue.SetRedraw(FALSE);

		setComboBox.SetSortRecord("Contatore");
		if (setComboBox.OpenRecordset("CTabComboDlg::FillLabelList"))
		{
			long i = 0;
			while (!setComboBox.IsEOF())
			{
				setComboBox.m_sTesto.Trim();
				if (!setComboBox.m_sTesto.IsEmpty())
				{
					CString strValue;
					strValue.Format("%li) %s", i + 1, setComboBox.m_sTesto);
					
					m_ctrlListValue.InsertString(i, strValue);
					m_ctrlListValue.SetItemData(i, setComboBox.m_lContatore);

					i++;
				}
				
				setComboBox.MoveNext();
			}
			setComboBox.CloseRecordset("CTabComboDlg::FillLabelList");
		}

		m_ctrlListValue.SetRedraw(TRUE);
	}
	else
	{
		m_ctrlListValue.SetRedraw(FALSE);

		setComboBox.SetSortRecord("Testo");
		if (setComboBox.OpenRecordset("CTabComboDlg::FillLabelList"))
		{
			long i = 0;
			while (!setComboBox.IsEOF())
			{
				setComboBox.m_sTesto.Trim();
				if (!setComboBox.m_sTesto.IsEmpty())
				{
					m_ctrlListValue.InsertString(i, setComboBox.m_sTesto);
					m_ctrlListValue.SetItemData(i, setComboBox.m_lContatore);

					i++;
				}
				
				setComboBox.MoveNext();
			}
			setComboBox.CloseRecordset("CTabComboDlg::FillLabelList");
		}

		m_ctrlListValue.SetRedraw(TRUE);
	}
	EndWaitCursor();

	UpdateData(FALSE);
}

BOOL CTabComboDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();

	/* Sandro 11/08/2010 - ricommentato su disposizione di Gottardo */
	// Sandro 05/05/2010 - RIMA 10-028.5 //
	// if (theApp.m_bPavia)
	// 	GetDlgItem(IDC_RICERCA_STR)->ModifyStyle(0, ES_UPPERCASE);

	m_ctrlListCombo.ResetContent();

	switch(theApp.m_nApplication)
	{
		case PRG_IMAGENT:
		{
			FillListImageNT();
			break;
		}
		default:
		{
			FillListEndox();
			break;
		}
	}

	GetDlgItem(IDC_COMBO_TABELLE)->SetFont(&theApp.m_fontBold, TRUE);
	GetDlgItem(IDCANCEL)->SetFont(&theApp.m_fontBold, TRUE);

	UpdateData(FALSE);
	theApp.LocalizeDialog(this, CTabComboDlg::IDD, "TabComboDlg");

	if (!m_bMenu)
	{
		int nPos = m_ctrlListCombo.FindStringExact(-1, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_104));
		m_ctrlListCombo.SetCurSel(nPos);
		OnSelectComboBox();
		m_ctrlListValue.SetCurSel(0);
		OnLbnSelchangeListDescr();
		m_ctrlListCombo.ShowWindow(SW_HIDE);
		SetWindowText(theApp.GetMessageString(IDS_CMB_INVIANTE_INTERNO));
		GetDlgItem(IDC_BTN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RICERCA_STR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LABEL_RIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDCANCEL)->SetWindowText(theApp.GetMessageString(IDS_BTN_SELEZIONA));
		GetDlgItem(IDC_BTN_AZZERA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RICERCA_STR)->SetFocus();
	}

	m_lSelected = -1;
	
	return TRUE;
}

void CTabComboDlg::FillListEndox()
{
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_52), CMB_PAZ_PROFESSIO, 3999, FALSE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_102), CMB_PAZ_NAZIONALI, 3999, FALSE, FALSE);

	if (theApp.m_bAnamVisi[0] && !theApp.m_sAnamText[0].Trim().IsEmpty())
		InsertPointerSet(theApp.m_sAnamText[0], CMB_ANA_FUMO, 3999, FALSE, TRUE);
	if (theApp.m_bAnamVisi[1] && !theApp.m_sAnamText[1].Trim().IsEmpty())
		InsertPointerSet(theApp.m_sAnamText[1], CMB_ANA_SIGA, 3999, FALSE, TRUE);
	if (theApp.m_bAnamVisi[2] && !theApp.m_sAnamText[2].Trim().IsEmpty())
		InsertPointerSet(theApp.m_sAnamText[2], CMB_ANA_CAFF, 3999, FALSE, TRUE);
	if (theApp.m_bAnamVisi[3] && !theApp.m_sAnamText[3].Trim().IsEmpty())
		InsertPointerSet(theApp.m_sAnamText[3], CMB_ANA_ALCO, 3999, FALSE, TRUE);
	if (theApp.m_bAnamVisi[4] && !theApp.m_sAnamText[4].Trim().IsEmpty())
		InsertPointerSet(theApp.m_sAnamText[4], CMB_ANA_SUPE, 3999, FALSE, TRUE);
	if (theApp.m_bAnamVisi[5] && !theApp.m_sAnamText[5].Trim().IsEmpty())
		InsertPointerSet(theApp.m_sAnamText[5], CMB_ANA_FARM, 3999, FALSE, TRUE);
	if (theApp.m_bAnamVisi[6] && !theApp.m_sAnamText[6].Trim().IsEmpty())
		InsertPointerSet(theApp.m_sAnamText[6], CMB_ANA_ASSU, 3999, FALSE, TRUE);

	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_82), CMB_PAZ_FAMILIARI, 3999, FALSE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_103), CMB_PAZ_PARENTELA, 3999, FALSE, TRUE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_80), CMB_ANA_ICHIRURG, 3999, FALSE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_81), CMB_ANA_IENDOSCO, 3999, FALSE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_83), CMB_ANA_INDAGINE, 3999, FALSE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_84), CMB_ANA_MALATTIE, 3999, FALSE, FALSE);

	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_33), CMB_ESA_FARMAC, 3999, TRUE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_86), CMB_ESA_TERAPIAINATTO, 3999, FALSE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_105), CMB_ESA_TERAPIAINATTODOSAGG, 3999, FALSE, TRUE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_111), CMB_ESA_TERAPIAINATTODURATA, 3999, FALSE, TRUE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_104), CMB_ESA_OSPEDALE, 3999, FALSE, FALSE);

	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_30), CMB_ESA_ESTENS, 3999, TRUE, TRUE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_37), CMB_ESA_PREMED, 3999, TRUE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_42), CMB_ESA_VALUTA, 3999, TRUE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_20), CMB_ESA_TERAPIACONSIGLIATA, 3999, TRUE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_106), CMB_ESA_TERAPIACONSIGLIATADOSAGG, 3999, TRUE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_107), CMB_ESA_TERAPIACONSIGLIATADURATA, 3999, TRUE, FALSE);

	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_43), CMB_ESA_COMPLICANZE, 3999, TRUE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_74), CMB_ESA_COMPLICANZEPROVV, 3999, TRUE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_73), CMB_ESA_COMPLICANZETERAP, 3999, TRUE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_75), CMB_ESA_COMPLICANZEESITO, 3999, TRUE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_45), CMB_ESA_QUADRO, 3999, TRUE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_44), CMB_ESA_GUARIG, 3999, TRUE, TRUE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_34), CMB_ESA_STUDIO, 3999, TRUE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_36), CMB_ESA_CONTRO, 3999, TRUE, TRUE);

	static int nTabelle[NUM_LABEL_TESTO] = { CMB_ESA_LIBERO000, CMB_ESA_LIBERO001, CMB_ESA_LIBERO002, CMB_ESA_LIBERO003, CMB_ESA_LIBERO004, CMB_ESA_LIBERO005, CMB_ESA_LIBERO006, CMB_ESA_LIBERO007, CMB_ESA_LIBERO008, CMB_ESA_LIBERO009, CMB_ESA_LIBERO010, CMB_ESA_LIBERO011, CMB_ESA_LIBERO012, CMB_ESA_LIBERO013, CMB_ESA_LIBERO014, CMB_ESA_LIBERO015, CMB_ESA_LIBERO016, CMB_ESA_LIBERO017, CMB_ESA_LIBERO018, CMB_ESA_LIBERO019, CMB_ESA_LIBERO020, CMB_ESA_LIBERO021, CMB_ESA_LIBERO022, CMB_ESA_LIBERO023, CMB_ESA_LIBERO024, CMB_ESA_LIBERO025, CMB_ESA_LIBERO026, CMB_ESA_LIBERO027, CMB_ESA_LIBERO028, CMB_ESA_LIBERO029, CMB_ESA_LIBERO030, CMB_ESA_LIBERO031, CMB_ESA_LIBERO032, CMB_ESA_LIBERO033, CMB_ESA_LIBERO034, CMB_ESA_LIBERO035, CMB_ESA_LIBERO036, CMB_ESA_LIBERO037, CMB_ESA_LIBERO038, CMB_ESA_LIBERO039, CMB_ESA_LIBERO040, CMB_ESA_LIBERO041, CMB_ESA_LIBERO042, CMB_ESA_LIBERO043, CMB_ESA_LIBERO044, CMB_ESA_LIBERO045, CMB_ESA_LIBERO046, CMB_ESA_LIBERO047, CMB_ESA_LIBERO048, CMB_ESA_LIBERO049, CMB_ESA_LIBERO050, CMB_ESA_LIBERO051, CMB_ESA_LIBERO052, CMB_ESA_LIBERO053, CMB_ESA_LIBERO054, CMB_ESA_LIBERO055, CMB_ESA_LIBERO056, CMB_ESA_LIBERO057, CMB_ESA_LIBERO058, CMB_ESA_LIBERO059, CMB_ESA_LIBERO060, CMB_ESA_LIBERO061, CMB_ESA_LIBERO062, CMB_ESA_LIBERO063, CMB_ESA_LIBERO064, CMB_ESA_LIBERO065, CMB_ESA_LIBERO066, CMB_ESA_LIBERO067, CMB_ESA_LIBERO068, CMB_ESA_LIBERO069, CMB_ESA_LIBERO070, CMB_ESA_LIBERO071, CMB_ESA_LIBERO072, CMB_ESA_LIBERO073, CMB_ESA_LIBERO074, CMB_ESA_LIBERO075, CMB_ESA_LIBERO076, CMB_ESA_LIBERO077, CMB_ESA_LIBERO078, CMB_ESA_LIBERO079, CMB_ESA_LIBERO080, CMB_ESA_LIBERO081, CMB_ESA_LIBERO082, CMB_ESA_LIBERO083, CMB_ESA_LIBERO084, CMB_ESA_LIBERO085, CMB_ESA_LIBERO086, CMB_ESA_LIBERO087, CMB_ESA_LIBERO088, CMB_ESA_LIBERO089, CMB_ESA_LIBERO090, CMB_ESA_LIBERO091, CMB_ESA_LIBERO092, CMB_ESA_LIBERO093, CMB_ESA_LIBERO094, CMB_ESA_LIBERO095, CMB_ESA_LIBERO096, CMB_ESA_LIBERO097, CMB_ESA_LIBERO098, CMB_ESA_LIBERO099 };
	for(int xyz = 0; xyz < NUM_LABEL_TESTO; xyz++)
	{
		if (theApp.m_bComboActive[xyz] && !theApp.m_sLabelText[xyz].Trim().IsEmpty())
			InsertPointerSet(theApp.m_sLabelText[xyz], nTabelle[xyz], 3999, TRUE, FALSE);
	}

	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_108), CMB_ESA_MOTIVOCONSENSO, 3999, TRUE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_109), CMB_ESA_TIPODEGENZAINT, 3999, FALSE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_110), CMB_ESA_TIPODEGENZAEST, 3999, FALSE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_101), CMB_ESA_ESAMIPREGRESSI, 3999, FALSE, FALSE);

	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_591), CMB_ESA_MOTIVOCANCEL, 3999, FALSE, FALSE);
}

void CTabComboDlg::FillListImageNT()
{
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_52), CMB_PAZ_PROFESSIO, 3999, FALSE, FALSE);
	InsertPointerSet(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_102), CMB_PAZ_NAZIONALI, 3999, FALSE, FALSE);

	static int nTabelle[20] = { CMB_ESA_LIBERO000, CMB_ESA_LIBERO001, CMB_ESA_LIBERO002, CMB_ESA_LIBERO003, CMB_ESA_LIBERO004, CMB_ESA_LIBERO005, CMB_ESA_LIBERO006, CMB_ESA_LIBERO007, CMB_ESA_LIBERO008, CMB_ESA_LIBERO009, CMB_ESA_LIBERO010, CMB_ESA_LIBERO011, CMB_ESA_LIBERO012, CMB_ESA_LIBERO013, CMB_ESA_LIBERO014, CMB_ESA_LIBERO015, CMB_ESA_LIBERO016, CMB_ESA_LIBERO017, CMB_ESA_LIBERO018, CMB_ESA_LIBERO019 };
	for(int xyz = 0; xyz < 20; xyz++)
	{
		if (theApp.m_bComboActive[xyz] && !theApp.m_sLabelText[xyz].Trim().IsEmpty())
			InsertPointerSet(theApp.m_sLabelText[xyz], nTabelle[xyz], 3999, TRUE, FALSE);
	}
}

void CTabComboDlg::OnDestroy() 
{
	int nCounter = m_ctrlListCombo.GetCount();
	
	while (nCounter >  0)
	{
		DATACOMBO* pData;
		
		pData		= (DATACOMBO*)m_ctrlListCombo.GetItemDataPtr(nCounter - 1);
		nCounter	= m_ctrlListCombo.DeleteString(nCounter - 1);

		if (pData)
			delete pData;
	}

	CDialog::OnDestroy();
}

void CTabComboDlg::OnElimina()
{
	if (m_lActiveComboDefine < 0)
		return;

	CString strTabella = "";
	int nSelTab = m_ctrlListCombo.GetCurSel();
	CString strValue = "";
	long nValue = 0;
	BOOL bUpdated = FALSE;
	int nSel = m_ctrlListValue.GetCurSel();
	int nTotSel = m_ctrlListValue.GetCount();

	if (m_bActiveOrderByCode)
	{
		if (nSel < nTotSel - 1)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TABCOMBODLG_ERR_ORDER));
			return;
		}
	}

	if (nSelTab != LB_ERR)
		m_ctrlListCombo.GetLBText(nSelTab, strTabella);

	if (nSel != LB_ERR)
	{
		m_ctrlListValue.GetText(nSel, strValue);
		nValue = (long)m_ctrlListValue.GetItemData(nSel);
	}

	if (nValue != LB_ERR)
	{
		CString strString;
		strString.Format(theApp.GetMessageString(IDS_TABCOMBODLG_DELETE_CONFIRM), strValue, strTabella);
		if (theApp.AfxMessageBoxEndo(strString, MB_YESNO) == IDYES)
		{
			CString sFilter;
			sFilter.Format("Contatore=%li", nValue);

			CComboBoxSet setComboBox(m_lActiveComboDefine);
			setComboBox.SetOpenFilter(sFilter);
			if (setComboBox.OpenRecordset("CTabComboDlg::OnElimina"))
			{	
				if (!setComboBox.IsEOF())
					if (setComboBox.CanUpdate())
						bUpdated = setComboBox.DeleteRecordset("CTabComboDlg::OnElimina");
		
				setComboBox.CloseRecordset("CTabComboDlg::OnElimina");
			}
		}
	}

	if (bUpdated)
		FillLabelList(m_lActiveComboDefine, m_bActiveIsCodeCounter, m_bActiveOrderByCode);
}

void CTabComboDlg::OnModifica()
{
	if (m_lActiveComboDefine < 0)
		return;
		
	CString strValue	= "";
	long	nValue		= 0;
	BOOL	bUpdated	= FALSE;
	int 	nSel		= m_ctrlListValue.GetCurSel();

	if (nSel != LB_ERR)
		nValue = (long)m_ctrlListValue.GetItemData(nSel);

	if (nValue != LB_ERR)
	{
		CString sFilter;
		sFilter.Format("Contatore=%li", nValue);

		CComboBoxSet setComboBox(m_lActiveComboDefine);
		setComboBox.SetOpenFilter(sFilter);
		if (setComboBox.OpenRecordset("CTabComboDlg::OnModifica"))
		{
			if (!setComboBox.IsEOF())
			{
				CString strTitle = "";
				int nCombo = m_ctrlListCombo.GetCurSel();
				
				if (nCombo != LB_ERR)
					m_ctrlListCombo.GetLBText(nCombo, strTitle);
				
				CAddDescrDlg dlg(this, strTitle, m_nActiveMaxLenCB, setComboBox.m_sTesto, m_lActiveExtMode, FALSE);
				if (dlg.DoModal() == IDOK)
				{
					if (setComboBox.EditRecordset("CTabComboDlg::OnModifica"))
					{
						setComboBox.m_sTesto = dlg.m_strDescription.Left(m_nActiveMaxLenCB).TrimRight();
						bUpdated = setComboBox.UpdateRecordset("CTabComboDlg::OnModifica");
					}
				}
			}

			setComboBox.CloseRecordset("CTabComboDlg::OnModifica");
		}
	}

	if (bUpdated)
		FillLabelList(m_lActiveComboDefine, m_bActiveIsCodeCounter, m_bActiveOrderByCode);
}

void CTabComboDlg::OnNuovo()
{
	if (m_lActiveComboDefine < 0)
		return;

	CString strTitle = "";
	int nCombo = m_ctrlListCombo.GetCurSel();
			
	if (nCombo != LB_ERR)
		m_ctrlListCombo.GetLBText(nCombo, strTitle);

	CAddDescrDlg dlg(this, strTitle, m_nActiveMaxLenCB, "", m_lActiveExtMode, FALSE);
	if (dlg.DoModal() == IDOK)
	{
		if (CComboBoxSet(m_lActiveComboDefine).AddRow(dlg.m_strDescription.Left(m_nActiveMaxLenCB).TrimRight()) > 0)
			FillLabelList(m_lActiveComboDefine, m_bActiveIsCodeCounter, m_bActiveOrderByCode);
	}
}

void CTabComboDlg::OnStampa()
{
	//Font grafico di default
	LOGFONT lfPrinterFont;
	
	memset(&lfPrinterFont, 0, sizeof(lfPrinterFont));
	lfPrinterFont.lfHeight 			= -10;
	lfPrinterFont.lfWeight 			= 400;
	lfPrinterFont.lfEscapement		= 0;   // orizzontale
	lfPrinterFont.lfOrientation		= 0;
	lfPrinterFont.lfWidth			= 0;
	lfPrinterFont.lfStrikeOut		= 0;
	lfPrinterFont.lfCharSet			= 0;
	lfPrinterFont.lfItalic			= 0;
	lfPrinterFont.lfUnderline		= 0;
	lfPrinterFont.lfOutPrecision	= 1;
	lfPrinterFont.lfClipPrecision	= 2;
	lfPrinterFont.lfQuality			= 1;
	lfPrinterFont.lfPitchAndFamily 	= 34;
	strcpy_s(lfPrinterFont.lfFaceName, "Arial");

	if (m_lActiveComboDefine < 0)
		return;
		
	CString strTitle = "";
	int 	nCombo = m_ctrlListCombo.GetCurSel();
	int 	nCounter = m_ctrlListValue.GetCount();
			
	if (nCombo == LB_ERR || nCounter == LB_ERR)
		return;

	CMyPrintDialog printdlg (FALSE, PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS |
								  PD_HIDEPRINTTOFILE | PD_NOSELECTION, this);

	if (printdlg.DoModal()==IDOK)
	{
		CDC 		prnDC ;   
		DOCINFO 	docInfo;
		CRect 		rectPage;
		TEXTMETRIC 	tm;
		CFont*		pFontOld;
		CFont		PrinterFont;
		CString		strTitle;
		CString		strValue;
		
		CCustomDate date(TRUE, TRUE);
		
		docInfo.cbSize			= sizeof (DOCINFO);
		docInfo.lpszDocName		= "Tabelle";
		docInfo.lpszOutput		= NULL;                       
		docInfo.lpszDatatype	= NULL;
		docInfo.fwType			= 0;
			
		prnDC.Attach(printdlg.GetPrinterDC());
        prnDC.StartDoc(&docInfo);
	        
		rectPage.SetRect(150, 0, prnDC.GetDeviceCaps(HORZRES), prnDC.GetDeviceCaps(VERTRES));
		prnDC.DPtoLP(&rectPage);
			    
		// create new font.
		int 	rapXP = prnDC.GetDeviceCaps(LOGPIXELSX);
		int 	rapYP = prnDC.GetDeviceCaps(LOGPIXELSY);
	
		//CClientDC	dcForm(this);
    	int 	rapXV = 72; //dcForm.GetDeviceCaps(LOGPIXELSX);
		int		rapYV = 72; //dcForm.GetDeviceCaps(LOGPIXELSY);

		// calcola il font per la stampante
		lfPrinterFont.lfHeight = ::MulDiv(lfPrinterFont.lfHeight, rapYP, rapYV);
		lfPrinterFont.lfWidth  = ::MulDiv(lfPrinterFont.lfWidth,  rapXP, rapXV);

		PrinterFont.CreateFontIndirect(&lfPrinterFont);

		pFontOld = prnDC.SelectObject(&PrinterFont);
	
		prnDC.GetTextMetrics(&tm);

		int nCYChar			= tm.tmHeight + tm.tmExternalLeading;
		int nLinesPerPage	= (prnDC.GetDeviceCaps(VERTRES) / nCYChar) - 2;
		int nPage			= (nCounter-1) / nLinesPerPage + 1;
		int	nL				= 0;
		
		m_ctrlListCombo.GetLBText(nCombo, strTitle);
		
		while (nL<nCounter)
		{
			for(int nP=1; nP<=nPage; nP++)
			{
				int		nLine = 0;
				CRect	rect  = CRect(rectPage.left, nLine * nCYChar, rectPage.right, (nLine+1) * nCYChar);

				prnDC.StartPage();
		
				prnDC.SetTextAlign(TA_LEFT);
				prnDC.TextOut (rect.left, rect.top, date.GetDate("%d/%m/%Y %H:%M"));
				prnDC.SetTextAlign(TA_CENTER);
				prnDC.TextOut ((rect.left + rectPage.right)/2, rect.top, strTitle);
					
				nLine++;
				prnDC.MoveTo(rectPage.left, nLine * nCYChar + (nCYChar / 2));
				prnDC.LineTo(rectPage.right, nLine * nCYChar + (nCYChar / 2));
			
				while (nL<nCounter && nL<(nP*nLinesPerPage))
				{
					m_ctrlListValue.GetText(nL, strValue);
					nL++;
				
					if (strValue != "")
					{
						nLine++;
			
						rect = CRect(rectPage.left, nLine * nCYChar, rectPage.right, (nLine+1) * nCYChar);
					
						prnDC.SetTextAlign(TA_LEFT);
						prnDC.TextOut (rect.left, rect.top, strValue);
					}
					
				}
			
				prnDC.EndPage();
			}
		}
	    
		prnDC.EndDoc();  
		        
		prnDC.SelectObject(pFontOld);
	    prnDC.DeleteDC();
		        
		::GlobalFree (printdlg.m_pd.hDevMode);
		::GlobalFree (printdlg.m_pd.hDevNames);
	}
}

void CTabComboDlg::OnSelectComboBox()
{
	int nSel = m_ctrlListCombo.GetCurSel();
	
	m_nActiveMaxLenCB = 0;
	m_lActiveExtMode = 0;
	m_bActiveIsCodeCounter = FALSE;
	m_bActiveOrderByCode = FALSE;
	m_lActiveComboDefine = -1;

	if (nSel != LB_ERR)
	{
		DATACOMBO* pDataCombo = (DATACOMBO*)m_ctrlListCombo.GetItemDataPtr(nSel);

		m_nActiveMaxLenCB = pDataCombo->nMaxLen;
		m_lActiveExtMode = pDataCombo->lExtMode;
		m_bActiveIsCodeCounter = pDataCombo->bIsCodeCounter;
		m_bActiveOrderByCode = pDataCombo->bOrderByCode;
		m_lActiveComboDefine = pDataCombo->lComboDefine;
	}
	
	FillLabelList(m_lActiveComboDefine, m_bActiveIsCodeCounter, m_bActiveOrderByCode);
}
void CTabComboDlg::OnLbnSelchangeListDescr()
{
	m_lSelected = m_ctrlListValue.GetItemData(m_ctrlListValue.GetCurSel());
}

void CTabComboDlg::OnOK()
{
	if (GetFocus() == GetDlgItem(IDC_RICERCA_STR))
			OnBnClickedBtn();
		else
			CDialog::OnOK();
}
void CTabComboDlg::OnBnClickedBtn()
{
	CString sRicerca;
	GetDlgItem(IDC_RICERCA_STR)->GetWindowText(sRicerca);
	FillLabelList(m_lActiveComboDefine, m_bActiveIsCodeCounter, m_bActiveOrderByCode, sRicerca.MakeUpper());
	m_lSelected = -1;
}

void CTabComboDlg::OnBnClickedBtnAzzera()
{
	m_lSelected = -1;
	GetDlgItem(IDC_RICERCA_STR)->SetWindowText("");
	FillLabelList(m_lActiveComboDefine, m_bActiveIsCodeCounter, m_bActiveOrderByCode);
	m_ctrlListValue.SetCurSel(-1);
}
