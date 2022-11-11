#include "stdafx.h"
#include "Endox.h"
#include "DermoxAcqSetupDlg.h"

#include <GdiPlus.h>

#include "LibCap\LibCap.h"

#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT uiEdit[10] = { IDC_EDIT_0, IDC_EDIT_1, IDC_EDIT_2, IDC_EDIT_3, IDC_EDIT_4, IDC_EDIT_5, IDC_EDIT_6, IDC_EDIT_7, IDC_EDIT_8, IDC_EDIT_9 };
static UINT uiCombo0[10] = { IDC_COMBO_00, IDC_COMBO_10, IDC_COMBO_20, IDC_COMBO_30, IDC_COMBO_40, IDC_COMBO_50, IDC_COMBO_60, IDC_COMBO_70, IDC_COMBO_80, IDC_COMBO_90 };
static UINT uiCombo1[10] = { IDC_COMBO_01, IDC_COMBO_11, IDC_COMBO_21, IDC_COMBO_31, IDC_COMBO_41, IDC_COMBO_51, IDC_COMBO_61, IDC_COMBO_71, IDC_COMBO_81, IDC_COMBO_91 };

IMPLEMENT_DYNAMIC(CDermoxAcqSetupDlg, CDialog)

CDermoxAcqSetupDlg::CDermoxAcqSetupDlg(CWnd* pParent)
	: CDialog(CDermoxAcqSetupDlg::IDD, pParent)
{
	xcapCOMStartListen = NULL;
	xcapCOMStopListen = NULL;

	m_iComPort = GetPrivateProfileInt("xcap", "ComPortPhoto", 0, theApp.m_sFileConfig);
	m_iComPort = max(0, m_iComPort);

	m_bComPortInv = (GetPrivateProfileInt("xcap", "invertpedalsphoto", 0, theApp.m_sFileConfig) == 0) ? FALSE : TRUE;

	m_bSx = FALSE;
	m_bDx = FALSE;
}

CDermoxAcqSetupDlg::~CDermoxAcqSetupDlg()
{
	xcapCOMStopListen();

	if (m_hModuleCOM)
		FreeLibrary(m_hModuleCOM);
}

BEGIN_MESSAGE_MAP(CDermoxAcqSetupDlg, CDialog)

	ON_BN_CLICKED(IDC_COM_NO, OnChangeCom)
	ON_BN_CLICKED(IDC_COM_1, OnChangeCom)
	ON_BN_CLICKED(IDC_COM_2, OnChangeCom)
	ON_BN_CLICKED(IDC_COM_3, OnChangeCom)
	ON_BN_CLICKED(IDC_COM_4, OnChangeCom)
	ON_BN_CLICKED(IDC_COM_REVERSE, OnChangeCom)

	ON_MESSAGE(WM_PRESS_PEDAL_1, OnPressPedal1)
	ON_MESSAGE(WM_PRESS_PEDAL_2, OnPressPedal2)

	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_CHECK_PHOTOACQ, &CDermoxAcqSetupDlg::OnBnClickedCheckPhotoacq)
	ON_BN_CLICKED(IDC_BTN_ACQ_NAV, &CDermoxAcqSetupDlg::OnBnClickedBtnAcqNav)
END_MESSAGE_MAP()

void CDermoxAcqSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COM_1, m_ctrlBtnCom1);
	DDX_Control(pDX, IDC_COM_2, m_ctrlBtnCom2);
	DDX_Control(pDX, IDC_COM_3, m_ctrlBtnCom3);
	DDX_Control(pDX, IDC_COM_4, m_ctrlBtnCom4);
	DDX_Control(pDX, IDC_BTN_ACQ_NAV, m_ctrlBtnPhotoAcqNav);

	DDX_Control(pDX, IDC_COM_NO, m_ctrlBtnCom0);
	DDX_Control(pDX, IDC_COM_REVERSE, m_ctrlBtnComInverti);
	DDX_Control(pDX, IDC_CHECK_PHOTOACQ, m_ctrlChkPhotoAcq);

	DDX_Control(pDX, IDC_COMBO_00, m_ctrlCombo0[0]);
	DDX_Control(pDX, IDC_COMBO_01, m_ctrlCombo1[0]);
	DDX_Control(pDX, IDC_COMBO_10, m_ctrlCombo0[1]);
	DDX_Control(pDX, IDC_COMBO_11, m_ctrlCombo1[1]);
	DDX_Control(pDX, IDC_COMBO_20, m_ctrlCombo0[2]);
	DDX_Control(pDX, IDC_COMBO_21, m_ctrlCombo1[2]);
	DDX_Control(pDX, IDC_COMBO_30, m_ctrlCombo0[3]);
	DDX_Control(pDX, IDC_COMBO_31, m_ctrlCombo1[3]);
	DDX_Control(pDX, IDC_COMBO_40, m_ctrlCombo0[4]);
	DDX_Control(pDX, IDC_COMBO_41, m_ctrlCombo1[4]);
	DDX_Control(pDX, IDC_COMBO_50, m_ctrlCombo0[5]);
	DDX_Control(pDX, IDC_COMBO_51, m_ctrlCombo1[5]);
	DDX_Control(pDX, IDC_COMBO_60, m_ctrlCombo0[6]);
	DDX_Control(pDX, IDC_COMBO_61, m_ctrlCombo1[6]);
	DDX_Control(pDX, IDC_COMBO_70, m_ctrlCombo0[7]);
	DDX_Control(pDX, IDC_COMBO_71, m_ctrlCombo1[7]);
	DDX_Control(pDX, IDC_COMBO_80, m_ctrlCombo0[8]);
	DDX_Control(pDX, IDC_COMBO_81, m_ctrlCombo1[8]);
	DDX_Control(pDX, IDC_COMBO_90, m_ctrlCombo0[9]);
	DDX_Control(pDX, IDC_COMBO_91, m_ctrlCombo1[9]);

	DDX_Control(pDX, IDC_EDIT_0, m_ctrlEdit0);
	DDX_Control(pDX, IDC_EDIT_1, m_ctrlEdit1);
	DDX_Control(pDX, IDC_EDIT_2, m_ctrlEdit2);
	DDX_Control(pDX, IDC_EDIT_3, m_ctrlEdit3);
	DDX_Control(pDX, IDC_EDIT_4, m_ctrlEdit4);
	DDX_Control(pDX, IDC_EDIT_5, m_ctrlEdit5);
	DDX_Control(pDX, IDC_EDIT_6, m_ctrlEdit6);
	DDX_Control(pDX, IDC_EDIT_7, m_ctrlEdit7);
	DDX_Control(pDX, IDC_EDIT_8, m_ctrlEdit8);
	DDX_Control(pDX, IDC_EDIT_9, m_ctrlEdit9);
	DDX_Control(pDX, IDC_EDIT_ACQDIRECTORY, m_ctrlEditPhotoAcqDir);

	DDX_Control(pDX, IDC_STATIC_0, m_ctrlStatic0);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_7, m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC_8, m_ctrlStatic8);
	DDX_Control(pDX, IDC_STATIC_9, m_ctrlStatic9);
	DDX_Control(pDX, IDC_STATIC_ACQ_DIR, m_ctrlStaticPhotoAcqDir);

	DDX_Control(pDX, IDC_STATIC_COM, m_ctrlStaticCom);

	// --- //

	DDX_Radio(pDX, IDC_COM_NO, m_iComPort);
	DDX_Check(pDX, IDC_COM_REVERSE, m_bComPortInv);

	DDX_Check(pDX, IDC_CHECK_PHOTOACQ, m_bPhotoAcq);
	DDX_Text(pDX, IDC_EDIT_ACQDIRECTORY, m_sAcqPhotoDirectory);

}

BOOL CDermoxAcqSetupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlStatic0.SetFont(&theApp.m_fontBold);
	m_ctrlStatic1.SetFont(&theApp.m_fontBold);
	m_ctrlStatic2.SetFont(&theApp.m_fontBold);
	m_ctrlStatic3.SetFont(&theApp.m_fontBold);
	m_ctrlStatic4.SetFont(&theApp.m_fontBold);
	m_ctrlStatic5.SetFont(&theApp.m_fontBold);
	m_ctrlStatic6.SetFont(&theApp.m_fontBold);
	m_ctrlStatic7.SetFont(&theApp.m_fontBold);
	m_ctrlStatic8.SetFont(&theApp.m_fontBold);
	m_ctrlStatic9.SetFont(&theApp.m_fontBold);
	m_ctrlStaticCom.SetFont(&theApp.m_fontBold);

	m_bPhotoAcq = GetPrivateProfileInt("xcap", "AcquisizioneDaFotocamera", 0, theApp.m_sFileConfig);
	m_sAcqPhotoDirectory = GetPrivateProfileString("xcap", "AcquisizioneDaFotocameraDirectory", "", theApp.m_sFileConfig);

	//Riporto i dati letti sull'interfaccia
	UpdateData(FALSE);
	
	if (!m_bPhotoAcq)
	{
		for (int i = 0; i < 10; i++)
		{
			CString sSezione;
			sSezione.Format("SorgenteDermox%02d", i);

			// --- //

			CString strTemp;
			strTemp.Format("Preset %02d", i + 1);
			strTemp = GetPrivateProfileString(sSezione, "Nome", strTemp, theApp.m_sFileConfig);
			WritePrivateProfileString(sSezione, "Nome", strTemp, theApp.m_sFileConfig);

			SetDlgItemText(uiEdit[i], strTemp);

			// --- //

			m_ctrlCombo0[i].InsertString(0, "");
			m_ctrlCombo0[i].SetItemData(0, DeviceUnknown);
			m_ctrlCombo0[i].InsertString(1, "Vio");
			m_ctrlCombo0[i].SetItemData(1, Vio);
			m_ctrlCombo0[i].InsertString(2, "UsbVideoDevice");
			m_ctrlCombo0[i].SetItemData(2, UsbVideoDevice);

			int iCombo0 = GetPrivateProfileInt(sSezione, "Device", DeviceUnknown, theApp.m_sFileConfig);
			WritePrivateProfileInt(sSezione, "Device", iCombo0, theApp.m_sFileConfig);
			m_ctrlCombo0[i].SetCurSel(0);
			for (int j = 1; j < m_ctrlCombo0[i].GetCount(); j++)
			{
				if (m_ctrlCombo0[i].GetItemData(j) == iCombo0)
				{
					m_ctrlCombo0[i].SetCurSel(j);
					break;
				}
			}

			// --- //

			m_ctrlCombo1[i].InsertString(0, "");
			m_ctrlCombo1[i].SetItemData(0, FormatUnknown);
			m_ctrlCombo1[i].InsertString(1, "Composite_PAL");
			m_ctrlCombo1[i].SetItemData(1, Composite_PAL);
			m_ctrlCombo1[i].InsertString(2, "RGB_PAL");
			m_ctrlCombo1[i].SetItemData(2, RGB_PAL);

			int iCombo1 = GetPrivateProfileInt(sSezione, "Format", FormatUnknown, theApp.m_sFileConfig);
			WritePrivateProfileInt(sSezione, "Format", iCombo1, theApp.m_sFileConfig);
			m_ctrlCombo1[i].SetCurSel(0);
			for (int j = 1; j < m_ctrlCombo1[i].GetCount(); j++)
			{
				if (m_ctrlCombo1[i].GetItemData(j) == iCombo1)
				{
					m_ctrlCombo1[i].SetCurSel(j);
					break;
				}
			}
		}
	}

	CString strPortCom = "xcapCOMInterface.dll";
	m_hModuleCOM = LoadLibrary(strPortCom);
	if (m_hModuleCOM == NULL)
	{
		CString strError;
		strError.Format(theApp.GetMessageString(IDS_LIBCAP_LOAD_ERROR1), strPortCom);
		theApp.AfxMessageBoxEndo(strError);
	}
	else
	{
		xcapCOMStartListen = (xcapCOMStartListen_PTR)GetProcAddress(m_hModuleCOM, _XCAP_COM_START_FUNCTION);
		xcapCOMStopListen = (xcapCOMStopListen_PTR)GetProcAddress(m_hModuleCOM, _XCAP_COM_STOP_FUNCTION);

		if ((xcapCOMStartListen == NULL) || (xcapCOMStopListen == NULL))
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_LIBCAP_LOAD_ERROR2), strPortCom);
			theApp.AfxMessageBoxEndo(strError);
		}

		InitComPort();
	}	

	CheckFieldsToEnable();

	return TRUE;
}

void CDermoxAcqSetupDlg::OnOK()
{
	UpdateData(TRUE);

	//Salvo la parte inerente all'acq da fotocamera
	if (m_bPhotoAcq)
	{
		if (m_sAcqPhotoDirectory.Right(1) != "\\")
			m_sAcqPhotoDirectory += "\\";

		WritePrivateProfileInt("xcap", "AcquisizioneDaFotocamera", 1, theApp.m_sFileConfig);
		WritePrivateProfileString("xcap", "AcquisizioneDaFotocameraDirectory", m_sAcqPhotoDirectory, theApp.m_sFileConfig);
	}
	else
	{
		//
		for (int i = 0; i < 10; i++)
		{
			CString sSezione;
			sSezione.Format("SorgenteDermox%02d", i);

			// --- //

			CString strTemp;
			GetDlgItemText(uiEdit[i], strTemp);
			WritePrivateProfileString(sSezione, "Nome", strTemp, theApp.m_sFileConfig);

			// --- //

			int iCombo0 = m_ctrlCombo0[i].GetCurSel();
			if (iCombo0 >= 0)
				WritePrivateProfileInt(sSezione, "Device", m_ctrlCombo0[i].GetItemData(iCombo0), theApp.m_sFileConfig);

			// --- //

			int iCombo1 = m_ctrlCombo1[i].GetCurSel();
			if (iCombo1 >= 0)
				WritePrivateProfileInt(sSezione, "Format", m_ctrlCombo1[i].GetItemData(iCombo1), theApp.m_sFileConfig);
		}

		//
		WritePrivateProfileInt("xcap", "ComPortPhoto", m_iComPort, theApp.m_sFileConfig);
		WritePrivateProfileInt("xcap", "invertpedalsphoto", m_bComPortInv ? 1 : 0, theApp.m_sFileConfig);

		WritePrivateProfileInt("xcap", "AcquisizioneDaFotocamera", 0, theApp.m_sFileConfig);
		WritePrivateProfileString("xcap", "AcquisizioneDaFotocamera", "", theApp.m_sFileConfig);
	}

	//
	CDialog::OnOK();
}

void CDermoxAcqSetupDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	Gdiplus::Graphics g(dc.GetSafeHdc());
	g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	g.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
	g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);

	CRect rc1;
	GetDlgItem(IDC_SX)->GetWindowRect(&rc1);
	ScreenToClient(&rc1);

	CRect rc2;
	GetDlgItem(IDC_DX)->GetWindowRect(&rc2);
	ScreenToClient(&rc2);

	Gdiplus::Rect rect1(rc1.left, rc1.top, rc1.Width(), rc1.Height());
	Gdiplus::Rect rect2a(rc2.left, rc2.top, rc2.Width() * 2 / 5, rc2.Height());
	Gdiplus::Rect rect2b(rc2.right - (rc2.Width() * 2 / 5), rc2.top, rc2.Width() * 2 / 5, rc2.Height());

	Gdiplus::Pen penRed  (Gdiplus::Color(255, 0, 0), 2);
	Gdiplus::Pen penBlue (Gdiplus::Color(0, 0, 255), 2);

	Gdiplus::SolidBrush brushRed  (Gdiplus::Color(255, 0, 0));
	Gdiplus::SolidBrush brushBlue (Gdiplus::Color(0, 0, 255));

	if (m_bSx)
		g.FillEllipse(&brushRed, rect1);
	g.DrawEllipse(&penRed, rect1);

	if (m_bDx)
	{
		g.FillRectangle(&brushBlue, rect2a);
		g.FillRectangle(&brushBlue, rect2b);
	}
	g.DrawRectangle(&penBlue, rect2a);
	g.DrawRectangle(&penBlue, rect2b);
		
	/*
	Gdiplus::Point pointTriangle[3];
	pointTriangle[0].X = rect3.X;
	pointTriangle[0].Y = rect3.Y + rect3.Height;
	pointTriangle[1].X = rect3.X + rect3.Width;
	pointTriangle[1].Y = rect3.Y + rect3.Height;
	pointTriangle[2].X = rect3.X + rect3.Width / 2;
	pointTriangle[2].Y = rect3.Y;

	if (m_bSwitch)
		g.FillPolygon(&brushBlue, pointTriangle, 3);
	g.DrawPolygon(&penBlue, pointTriangle, 3);
	*/
}

void CDermoxAcqSetupDlg::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);

	KillTimer(nIDEvent);

	m_bSx = FALSE;
	m_bDx = FALSE;

	InvalidateComRegion();
}

void CDermoxAcqSetupDlg::InitComPort()
{
	if ((xcapCOMStartListen != NULL) && (xcapCOMStopListen != NULL))
	{
		xcapCOMStopListen();

		if (m_iComPort > 0)
			if (!xcapCOMStartListen(m_iComPort, 0, 0, GetSafeHwnd(), WM_PRESS_PEDAL_1, WM_PRESS_PEDAL_2, WM_PRESS_PEDAL_3, WM_PRESS_PEDAL_4, 200, 1000))
				theApp.MessageBoxEndo(theApp.GetMessageString(IDS_ERROR_OPENING_COM), theApp.GetMessageString(IDS_ACHTUNG));

		m_bSx = FALSE;
		m_bDx = FALSE;
		InvalidateComRegion();
	}
}

void CDermoxAcqSetupDlg::InvalidateComRegion()
{
	CRect rect;

	GetDlgItem(IDC_SX)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);

	GetDlgItem(IDC_DX)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);
}

void CDermoxAcqSetupDlg::OnChangeCom()
{
	UpdateData(TRUE);

	m_bSx = FALSE;
	m_bDx = FALSE;

	InvalidateComRegion();

	InitComPort();
}

LRESULT CDermoxAcqSetupDlg::OnPressPedal1(WPARAM wParam, LPARAM lParam)
{
	// theApp.AfxMessageBoxEndo("Pedale1");

	if (m_bComPortInv)
		m_bDx = TRUE;
	else
		m_bSx = TRUE;

	SetTimer(1, 500, NULL);
	InvalidateComRegion();

	return 0;
}

LRESULT CDermoxAcqSetupDlg::OnPressPedal2(WPARAM wParam, LPARAM lParam)
{
	// theApp.AfxMessageBoxEndo("Pedale2");

	if (m_bComPortInv)
		m_bSx = TRUE;
	else
		m_bDx = TRUE;

	SetTimer(1, 500, NULL);
	InvalidateComRegion();

	return 0;
}

void CDermoxAcqSetupDlg::OnBnClickedCheckPhotoacq()
{
	CheckFieldsToEnable();
}

void CDermoxAcqSetupDlg::CheckFieldsToEnable()
{
	UpdateData(TRUE);

	//disabilito o abilito tutti i controlli
	CWnd* pwndChild = GetWindow(GW_CHILD);
	while (pwndChild)
	{
		if ((pwndChild->GetDlgCtrlID() != IDOK) && (pwndChild->GetDlgCtrlID() != IDCANCEL))
			pwndChild->EnableWindow(!m_bPhotoAcq);

		pwndChild = pwndChild->GetNextWindow();
	}

	//disabilito o abilito i controlli interessati, in modo opposto a quello appena fatto
	m_ctrlStaticPhotoAcqDir.EnableWindow(m_bPhotoAcq);
	m_ctrlEditPhotoAcqDir.EnableWindow(m_bPhotoAcq);
	m_ctrlBtnPhotoAcqNav.EnableWindow(m_bPhotoAcq);

	//check sempre abilitata se no mi blocco
	m_ctrlChkPhotoAcq.EnableWindow(TRUE);
}

void CDermoxAcqSetupDlg::OnBnClickedBtnAcqNav()
{
	CFolderDialog dlg("", m_sAcqPhotoDirectory, 64, this);
	if (dlg.DoModal() == IDOK)
		m_sAcqPhotoDirectory = dlg.GetSelectedFolder();

	UpdateData(FALSE);
}
