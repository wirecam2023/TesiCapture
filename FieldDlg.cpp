#include "stdafx.h"
#include "Endox.h"
#include "FieldDlg.h"

#include "Common.h"
#include "DrawTool.h"
#include "RectPreviewObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

endox_report_field CFieldDlg::m_strFieldEndox[endox_report_field_num_total];

CFieldDlg::CFieldDlg(CWnd* pParent, CRect rectPage, CDrawTool* pObj, CSize szPage)
	: CDialog(CFieldDlg::IDD, pParent)
{
	m_nLeft		= 0;
	m_nTop		= 0;
	m_nWidth	= 0;
	m_nHeight	= 0;
	m_strTesto	= "";
	m_bCheck	= FALSE;
	m_nParam	= 0;
	m_nAlignment = 0;
	m_nRotation = 0;

	m_rectPage	= rectPage;
	m_pObj		= pObj;
	m_szPage    = szPage;

	if (m_pObj)
	{
		CRect  rect = m_pObj->GetRectInMM();

		m_nLeft	= rect.left; 
		m_nTop	= rect.top;

		m_nWidth  = rect.Width ();
		m_nHeight = rect.Height();
		
		m_strTesto	= m_pObj->m_strValue;
		m_bCheck	= m_pObj->m_bCheck;
		m_nParam	= m_pObj->m_nParam;
		m_nAlignment = m_pObj->m_nAlignment;
		m_nRotation = m_pObj->m_nRotation;
	}
}

void CFieldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Control	(pDX, IDC_STATIC_DIM,   m_ctrlStaticDim);
	DDX_Control	(pDX, IDC_STATIC_POS,   m_ctrlStaticPos);
	DDX_Control	(pDX, IDC_STATIC_X,     m_ctrlStaticX);
	DDX_Control	(pDX, IDC_STATIC_Y,     m_ctrlStaticY);
	DDX_Control	(pDX, IDC_STATIC_WIDTH, m_ctrlStaticWidth);
	DDX_Control	(pDX, IDC_HEIGHT,       m_ctrlStaticHeight);
	DDX_Control	(pDX, IDCANCEL,         m_ctrlButtonCancel);
	DDX_Control	(pDX, IDOK,             m_ctrlButtonOK);
	DDX_Control	(pDX, IDC_RADIO_ORIZ,	m_ctrlRadioOriz);
	DDX_Control	(pDX, IDC_RADIO_90_O,	m_ctrlRadio90O);
	DDX_Control	(pDX, IDC_RADIO_90_A,	m_ctrlRadio90A);
	
	DDX_Control	(pDX, IDC_BTN,		 m_ctrlFontButton);
	DDX_Control	(pDX, IDC_CHECK,	 m_ctrlCheck);
	DDX_Control	(pDX, IDC_EDIT,		 m_ctrlTesto);
	DDX_Control	(pDX, IDC_COMBO,	 m_ctrlCombo);
	DDX_Control	(pDX, IDC_ETICHETTA, m_ctrlTipo);
	DDX_Text	(pDX, IDC_LEFT,		 m_nLeft);
	DDX_Text	(pDX, IDC_TOP,		 m_nTop);
	DDX_Text	(pDX, IDC_CX,		 m_nWidth);
	DDX_Text	(pDX, IDC_CY,		 m_nHeight);

	DDX_Control	(pDX, IDC_PARAM_LABEL,	 m_ctrlParam[0]);
	DDX_Control	(pDX, IDC_PARAM_EDIT,	 m_ctrlParam[1]);

	DDX_Check	(pDX, IDC_CHECK,		m_bCheck);
	DDX_Text	(pDX, IDC_EDIT,			m_strTesto);
	DDX_Text	(pDX, IDC_PARAM_EDIT,	m_nParam);
	//DDX_CBIndex	(pDX, IDC_COMBO,	m_strCombo);
	DDX_Radio	(pDX, IDC_RADIO_L,		m_nAlignment);
	DDX_Radio	(pDX, IDC_RADIO_ORIZ,	m_nRotation);
}

BEGIN_MESSAGE_MAP(CFieldDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN, OnButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFieldDlg message handlers

BOOL CFieldDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_ETICHETTA)->SetFont(&theApp.m_fontBig);

	theApp.LocalizeDialog(this, CFieldDlg::IDD, "FieldDlg");

	if (!m_pObj)
	{
		UpdateData(FALSE);
		return TRUE;
	}

	if (m_pObj->m_strType == "Field" || m_pObj->m_strType == "Label")
	{
		m_ctrlCombo.ShowWindow(SW_SHOW);

		CString strToFind = "";
		switch(theApp.m_nApplication)
		{
			case PRG_ENDOX:
			case PRG_DERMOX:
			{
				for(int i = 0; i < endox_report_field_num_total; i++)
				{
					if (CFieldDlg::m_strFieldEndox[i].bEndox && (!CFieldDlg::m_strFieldEndox[i].sCombo.IsEmpty()) && (!CFieldDlg::m_strFieldEndox[i].sReport.IsEmpty()))
					{
						BOOL bAddField = TRUE;

						switch(i)
						{
							case pazientecronico_score_hb:
							case pazientecronico_score_s:
							{
								if (theApp.m_lOpzionalePazientiCronici != OPZIONALE_PAZIENTI_CRONICI)
									bAddField = FALSE;

								break;
							}
						}

						if (bAddField)
						{
							int iContenuto = -1;
							if (CFieldDlg::m_strFieldEndox[i].lID >= 0)
							{
								for(int j = 0; j < form_list_total; j++)
								{
									if (g_FormCaract[j].lID == CFieldDlg::m_strFieldEndox[i].lID)
									{
										iContenuto = j;
										break;
									}
								}
							}

							m_ctrlCombo.AddString(CFieldDlg::m_strFieldEndox[i].sCombo + GetStringCampoLiberoDatabase(iContenuto));

							if (m_pObj->m_strValue == CFieldDlg::m_strFieldEndox[i].sReport)
				 				strToFind = CFieldDlg::m_strFieldEndox[i].sCombo + GetStringCampoLiberoDatabase(iContenuto);
						}
					}
				}
				break;
			}
			case PRG_IMAGENT:
			{
				for(int i = 0; i < endox_report_field_num_total; i++)
				{
					if (CFieldDlg::m_strFieldEndox[i].bImageNT && (!CFieldDlg::m_strFieldEndox[i].sCombo.IsEmpty()) && (!CFieldDlg::m_strFieldEndox[i].sReport.IsEmpty()))
					{
						m_ctrlCombo.AddString(CFieldDlg::m_strFieldEndox[i].sCombo);

						if (m_pObj->m_strValue == CFieldDlg::m_strFieldEndox[i].sReport)
				 			strToFind = CFieldDlg::m_strFieldEndox[i].sCombo;
					}
				}
				break;
			}
		}

		int nIndex = m_ctrlCombo.FindStringExact(-1, strToFind);
		m_ctrlCombo.SetCurSel(nIndex);

		if (m_pObj->m_strType == "Field")
			m_ctrlTipo.SetWindowText(theApp.GetMessageString(IDS_FIELD_DLG_TYPE_1));
		else
			m_ctrlTipo.SetWindowText(theApp.GetMessageString(IDS_FIELD_DLG_TYPE_2));

		m_ctrlFontButton.SetWindowText(theApp.GetMessageString(IDS_FIELDDLG_BUTTON_1));

		m_ctrlParam[1].ShowWindow(SW_HIDE);
		m_ctrlParam[0].ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RADIO_L)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_C)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_R)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_RADIO_ORIZ)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_90_O)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_90_A)->ShowWindow(SW_SHOW);
	}
	else if (m_pObj->m_strType == "Param")
	{
		m_ctrlCombo.ShowWindow(SW_SHOW);
	
		m_ctrlCombo.AddString(szParamData);
		m_ctrlCombo.AddString(szParamDataLarga);
		m_ctrlCombo.AddString(szParamOra);

		m_ctrlCombo.SetCurSel(m_ctrlCombo.FindStringExact(-1, m_pObj->m_strValue));
		m_ctrlTipo.SetWindowText(theApp.GetMessageString(IDS_FIELD_DLG_TYPE_3));

		m_ctrlFontButton.SetWindowText(theApp.GetMessageString(IDS_FIELDDLG_BUTTON_1));

		m_ctrlParam[0].ShowWindow(SW_HIDE);
		m_ctrlParam[1].ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RADIO_L)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_C)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_R)->ShowWindow(SW_SHOW);
	}
	else if (m_pObj->m_strType == "Text")
	{
		m_ctrlTesto.ShowWindow(SW_SHOW);
		
		m_strTesto	= m_pObj->m_strValue;
		m_ctrlTesto.SetWindowText(m_strTesto);
		m_ctrlTipo.SetWindowText(theApp.GetMessageString(IDS_FIELD_DLG_TYPE_4));

		m_ctrlFontButton.SetWindowText(theApp.GetMessageString(IDS_FIELDDLG_BUTTON_1));

		m_ctrlParam[0].ShowWindow(SW_HIDE);
		m_ctrlParam[1].ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RADIO_L)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_C)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_R)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_RADIO_ORIZ)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_90_O)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_90_A)->ShowWindow(SW_SHOW);
	}
	else if (m_pObj->m_strType == "Image")
	{
		m_ctrlCheck.ShowWindow(SW_SHOW);
		m_ctrlCheck.SetWindowText(theApp.GetMessageString(IDS_FIELDDLG_CHECK_1));
		m_ctrlTipo. SetWindowText(theApp.GetMessageString(IDS_FIELD_DLG_TYPE_5));
		m_ctrlTesto.SetWindowText(m_strTesto);

		m_ctrlFontButton.ShowWindow(SW_HIDE);
		// m_ctrlFontButton.SetWindowText(theApp.GetMessageString(IDS_FIELDDLG_BUTTON_1));
	
		m_ctrlParam[0].ShowWindow(SW_HIDE);
		m_ctrlParam[1].ShowWindow(SW_HIDE);
	}
	else if (m_pObj->m_strType == "Icon")
	{
		m_ctrlTesto.ShowWindow(SW_SHOW);

		m_ctrlTesto.SetWindowText(m_strTesto);
		m_ctrlTipo. SetWindowText(theApp.GetMessageString(IDS_FIELD_DLG_TYPE_6));

		m_ctrlFontButton.SetWindowText(theApp.GetMessageString(IDS_FIELDDLG_BUTTON_2));

		m_ctrlParam[0].ShowWindow(SW_HIDE);
		m_ctrlParam[1].ShowWindow(SW_HIDE);
	}
	else if (m_pObj->m_strType == "Line")
	{
		m_ctrlCheck.ShowWindow(SW_HIDE);

		m_ctrlTipo. SetWindowText(theApp.GetMessageString(IDS_FIELD_DLG_TYPE_9));
		
		m_ctrlTesto.ShowWindow(SW_HIDE);

		m_ctrlFontButton.ShowWindow(SW_HIDE);
	
		m_ctrlParam[0].ShowWindow(SW_SHOW);
		m_ctrlParam[1].ShowWindow(SW_SHOW);
		m_ctrlParam[0].SetWindowText(theApp.GetMessageString(IDS_FIELDDLG_PARAM));
	}
	else if (m_pObj->m_strType == "Organ")
	{
		m_ctrlCheck.ShowWindow(SW_HIDE);

		m_ctrlTipo. SetWindowText(theApp.GetMessageString(IDS_FIELD_DLG_TYPE_10));

		m_ctrlTesto.SetWindowText(m_strTesto);

		m_ctrlFontButton.ShowWindow(SW_HIDE);
	
		m_ctrlParam[0].ShowWindow(SW_HIDE);
		m_ctrlParam[1].ShowWindow(SW_HIDE);
	}
	else if (m_pObj->m_strType == "PageNum")
	{
		m_ctrlTipo.SetWindowText(theApp.GetMessageString(IDS_FIELD_DLG_TYPE_11));

		m_ctrlFontButton.SetWindowText(theApp.GetMessageString(IDS_FIELDDLG_BUTTON_1));

		m_ctrlParam[0].ShowWindow(SW_HIDE);
		m_ctrlParam[1].ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RADIO_L)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_C)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_R)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_RADIO_ORIZ)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_90_O)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_90_A)->ShowWindow(SW_SHOW);
	}
	else if (m_pObj->m_strType == "PageTot")
	{
		m_ctrlTipo.SetWindowText(theApp.GetMessageString(IDS_FIELD_DLG_TYPE_12));

		m_ctrlFontButton.SetWindowText(theApp.GetMessageString(IDS_FIELDDLG_BUTTON_1));

		m_ctrlParam[0].ShowWindow(SW_HIDE);
		m_ctrlParam[1].ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RADIO_L)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_C)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_R)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_RADIO_ORIZ)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_90_O)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_90_A)->ShowWindow(SW_SHOW);
	}

	UpdateData(FALSE);
	
	return TRUE;
}

void CFieldDlg::OnButton() 
{
	UpdateData(TRUE);

	if (m_pObj)
	{
		if (m_pObj->m_strType == "Icon")
		{
			CFileDialog FileDlg(TRUE, NULL, NULL, OFN_READONLY |OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, "Tutti i file|*.*|", this, 0, FALSE);
			
			if (FileDlg.DoModal() == IDOK)
				m_strTesto = FileDlg.GetPathName();
		}
		else
		{
			CFontDialog	dlg(&m_pObj->m_lfFont);
			dlg.m_cf.rgbColors = m_pObj->m_rgbColor;

			if (dlg.DoModal() == IDOK)
			{
				dlg.GetCurrentFont(&m_pObj->m_lfFont);
				m_pObj->m_rgbColor = dlg.GetColor();
			}
		}
	}

	UpdateData(FALSE);
}

void CFieldDlg::OnOK() 
{
	UpdateData(TRUE);
	
	if (m_pObj)
	{
		CRect rect;

		rect.left	= m_nLeft;
		rect.top	= m_nTop;
		rect.right	= m_nLeft + m_nWidth;
		rect.bottom	= m_nTop  + m_nHeight;
		
		if (((m_nLeft + m_nWidth > m_szPage.cx) || (m_nTop + m_nHeight > m_szPage.cy)) && (m_szPage != CSize(0, 0)))
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FIELDDLG_ERR_DIM));
			return;
		}

		// Sandro 17/05/2012 // quello sopra non funziona sempre anzi quasi mai, quindi aggiungo ulteriore controllo //
		if ((m_nLeft + m_nWidth > m_pObj->m_pObj->m_PosObj.m_PageInMM.right) || (m_nTop + m_nHeight > m_pObj->m_pObj->m_PosObj.m_PageInMM.bottom))
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FIELDDLG_ERR_DIM));
			return;
		}

		//
		if (m_pObj->m_strType == "Field" || m_pObj->m_strType == "Label")
		{
			CString strSelString;
			
			m_pObj->SetRectInMM(m_pParentWnd, rect);
			m_pObj->m_bCheck	= m_bCheck;
			m_pObj->m_nParam	= m_nParam;
			m_pObj->m_nAlignment = m_nAlignment;
			m_pObj->m_nRotation = m_nRotation;
			//m_pObj->m_strValue	= ....;

			m_ctrlCombo.GetLBText(m_ctrlCombo.GetCurSel(), strSelString);

			for(int i = 0; i < endox_report_field_num_total; i++)
			{
				int iContenuto = -1;
				if (CFieldDlg::m_strFieldEndox[i].lID >= 0)
				{
					for(int j = 0; j < form_list_total; j++)
					{
						if (g_FormCaract[j].lID == CFieldDlg::m_strFieldEndox[i].lID)
						{
							iContenuto = j;
							break;
						}
					}
				}

				if (CFieldDlg::m_strFieldEndox[i].sCombo + GetStringCampoLiberoDatabase(iContenuto) == strSelString)
				{
					m_pObj->m_strValue = CFieldDlg::m_strFieldEndox[i].sReport;
					break;
				}
			}
		}
		else
		{
			if (m_pObj->m_strType == "Form")
			{
				CString strSelString;
				
				m_ctrlCombo.GetLBText(m_ctrlCombo.GetCurSel(), strSelString);

				m_pObj->SetRectInMM(m_pParentWnd, rect);
				m_pObj->m_bCheck	= m_bCheck;
				m_pObj->m_nParam	= m_nParam;
				m_pObj->m_nAlignment = m_nAlignment;
				m_pObj->m_nRotation = m_nRotation;

				if (strSelString == theApp.GetMessageString(IDS_FIELDDLG_FORM_1))
					m_pObj->m_strValue = "Terapie";
				else if (strSelString == theApp.GetMessageString(IDS_FIELDDLG_FORM_2))
					m_pObj->m_strValue = "Osservazioni";
				else if (strSelString == theApp.GetMessageString(IDS_FIELDDLG_FORM_3))
					m_pObj->m_strValue = "Patologia";
				else if (strSelString == theApp.GetMessageString(IDS_FIELDDLG_FORM_4))
					m_pObj->m_strValue = "Diagnosi";
				else if (strSelString == theApp.GetMessageString(IDS_FIELDDLG_FORM_5))
					m_pObj->m_strValue = "Codifica regionale";
				else if (strSelString == theApp.GetMessageString(IDS_FIELDDLG_FORM_6))
					m_pObj->m_strValue = "Monitoraggio";
			}
			else
			{
				if (m_pObj->m_strType == "Param")
				{
					m_pObj->SetRectInMM(m_pParentWnd, rect);
					m_pObj->m_bCheck	= m_bCheck;
					m_pObj->m_nParam	= m_nParam;
					m_pObj->m_nAlignment = m_nAlignment;
					m_pObj->m_nRotation = m_nRotation;

					m_ctrlCombo.GetLBText(m_ctrlCombo.GetCurSel(), m_pObj->m_strValue);
				}
				else
				{
					m_pObj->SetRectInMM(m_pParentWnd, rect);
					m_pObj->m_bCheck	= m_bCheck;
					m_pObj->m_nParam	= m_nParam;
					m_pObj->m_nAlignment = m_nAlignment;
					m_pObj->m_nRotation = m_nRotation;
					m_pObj->m_strValue	= m_strTesto;
				}
			}
		}	
	}
	
	CDialog::OnOK();
}