#include "stdafx.h"
#include "Endox.h"
#include "PropCampoDlg.h"
#include "EsamiView.h"

#include "FasiEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPropCampoDlg, CDialog)

CPropCampoDlg::CPropCampoDlg(CWnd* pParent, CReport* pReport)
	: CDialog(CPropCampoDlg::IDD, pParent)
{
	ASSERT(pReport != NULL);

	m_pReport = pReport;

	STRUCT_LINGUETTA* pLinguetta = m_pReport->GetLinguetta();
	m_OriginalCampo = pLinguetta->listCampi.GetAt(m_pReport->GetCurSel());
	m_iColore = m_OriginalCampo.lColore + 1;

	for(int i = 0; i < form_list_total; i++)
	{
		if (g_FormCaract[i].lID == m_OriginalCampo.lContenuto)
		{
			m_iContenuto = i;
			break;
		}
	}
}

CPropCampoDlg::~CPropCampoDlg()
{
	m_pReport->SetCurSel(NULL);
	m_pParentWnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE);
}

BEGIN_MESSAGE_MAP(CPropCampoDlg, CDialog)

	ON_WM_PAINT()

	ON_CBN_SELCHANGE(IDC_COMBO, OnCbnSelchangeCombo)

	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_X, OnDeltaposSpinX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_Y, OnDeltaposSpinY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_L, OnDeltaposSpinL)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_A, OnDeltaposSpinA)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TAB, OnDeltaposSpinTab)

	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO4, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO5, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO6, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO7, OnBnClickedRadio)

	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)

	ON_CBN_SELCHANGE(IDC_COMBO_FASE, &CPropCampoDlg::OnCbnSelchangeComboFase)
END_MESSAGE_MAP()

void CPropCampoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_LAB1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_LAB2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_LAB3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_LAB4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_LAB5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_BTN_DEL,     m_ctrlButton1);
	DDX_Control(pDX, IDCANCEL,        m_ctrlButton2);
	DDX_Control(pDX, IDOK,            m_ctrlButton3);

	DDX_Control(pDX, IDC_COMBO, m_ctrlCombo);

	DDX_Control(pDX, IDC_SPIN_X, m_ctrlSpinX);
	DDX_Control(pDX, IDC_SPIN_Y, m_ctrlSpinY);
	DDX_Control(pDX, IDC_SPIN_L, m_ctrlSpinL);
	DDX_Control(pDX, IDC_SPIN_A, m_ctrlSpinA);
	DDX_Control(pDX, IDC_SPIN_TAB, m_ctrlSpinTab);

	DDX_Control(pDX, IDC_COMBO_FASE, m_ctrlComboFase);

	DDX_Radio(pDX, IDC_RADIO1, m_iColore);	
}

void CPropCampoDlg::OnCancel()
{
	// riordino i tab dei campi come erano impostati precedentemente //
	STRUCT_CAMPO campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(m_pReport->GetCurSel());
	int nTabAttuale = campoTemp.lTabOrder;
	int nTabPrecedente = m_OriginalCampo.lTabOrder;
	if (nTabAttuale != nTabPrecedente)
	{
		if (nTabAttuale < nTabPrecedente)
		{
			for(int i = nTabAttuale + 1; i <= nTabPrecedente; i++)
			{
				// ora ricerco il campo con il nuovo tab per scambiarli //
				POSITION pos = m_pReport->GetLinguetta()->listCampi.GetHeadPosition();
				while(pos != NULL)
				{
					if ((pos != m_pReport->GetCurSel()) && (m_pReport->GetLinguetta()->listCampi.GetAt(pos).lTabOrder == i))
					{
						campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(pos);
						campoTemp.lTabOrder = i - 1;
						m_pReport->GetLinguetta()->listCampi.SetAt(pos, campoTemp);

						break;
					}

					m_pReport->GetLinguetta()->listCampi.GetNext(pos);
				}
			}
		}
		else
		{
			for(int i = nTabAttuale - 1; i >= nTabPrecedente; i--)
			{
				// ora ricerco il campo con il nuovo tab per scambiarli //
				POSITION pos = m_pReport->GetLinguetta()->listCampi.GetHeadPosition();
				while(pos != NULL)
				{
					if ((pos != m_pReport->GetCurSel()) && (m_pReport->GetLinguetta()->listCampi.GetAt(pos).lTabOrder == i))
					{
						campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(pos);
						campoTemp.lTabOrder = i + 1;
						m_pReport->GetLinguetta()->listCampi.SetAt(pos, campoTemp);

						break;
					}

					m_pReport->GetLinguetta()->listCampi.GetNext(pos);
				}
			}
		}
	}

	// if (theApp.AfxMessageBoxEndo(Uscire annullando le modifiche effettuate?, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
	{
		m_pReport->GetLinguetta()->listCampi.SetAt(m_pReport->GetCurSel(), m_OriginalCampo);
	
		CDialog::OnCancel();
	}
}

BOOL CPropCampoDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();
	int nCol = m_pReport->GetLinguetta()->lMostraAlbum == 1 ? DEF_X1 : DEF_X2;

	GetDlgItem(IDC_STATIC_LAB1)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_STATIC_LAB2)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_STATIC_LAB3)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_STATIC_LAB4)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_STATIC_LAB5)->SetFont(&theApp.m_fontBig);

	RiempiCombo();

	UDACCEL pAccel[1];
	pAccel[0].nSec = 0;
	pAccel[0].nInc = 1;

	m_ctrlSpinX.SetAccel(1, pAccel);
	m_ctrlSpinX.SetRange32(0, nCol - m_OriginalCampo.lL);
	m_ctrlSpinX.SetPos32(m_OriginalCampo.lX);

	m_ctrlSpinY.SetAccel(1, pAccel);
	m_ctrlSpinY.SetRange32(DEF_Y - m_OriginalCampo.lA, 0);
	m_ctrlSpinY.SetPos32(m_OriginalCampo.lY);

	m_ctrlSpinL.SetAccel(1, pAccel);
	m_ctrlSpinL.SetRange32(g_FormCaract[m_iContenuto].lMinL, min(nCol - m_OriginalCampo.lX, g_FormCaract[m_iContenuto].lMaxL));
	m_ctrlSpinL.SetPos32(m_OriginalCampo.lL);

	m_ctrlSpinA.SetAccel(1, pAccel);
	m_ctrlSpinA.SetRange32(min(DEF_Y - m_OriginalCampo.lY, g_FormCaract[m_iContenuto].lMaxA), g_FormCaract[m_iContenuto].lMinA);
	m_ctrlSpinA.SetPos32(m_OriginalCampo.lA);

	m_ctrlSpinTab.SetAccel(1, pAccel);
	m_ctrlSpinTab.SetRange32(1, m_pReport->GetLinguetta()->listCampi.GetCount()); // da sistemare //
	m_ctrlSpinTab.SetPos32(m_OriginalCampo.lTabOrder);

	// inizio prova //
	STRUCT_CAMPO campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(m_pReport->GetCurSel());
	campoTemp.lL = m_ctrlSpinL.GetPos32();
	campoTemp.lA = m_ctrlSpinA.GetPos32();
	m_pReport->GetLinguetta()->listCampi.SetAt(m_pReport->GetCurSel(), campoTemp);
	// fine prova //

    //Popolo la combo delle fasi
	m_ctrlComboFase.Clear();
	int index = m_ctrlComboFase.AddString(theApp.GetMessageString(IDS_MAI));
	m_ctrlComboFase.SetItemData(index, 0);
	m_ctrlComboFase.SetCurSel(index);

	CFasiEsameSet fasiEsameSet;
	if (fasiEsameSet.OpenRecordset("CPropCampoDlg::OnInitDialog"))
	{
		while (!fasiEsameSet.IsEOF())
		{
			index = m_ctrlComboFase.AddString(fasiEsameSet.m_sDescrizione);
			m_ctrlComboFase.SetItemData(index, fasiEsameSet.m_lID);

			if (fasiEsameSet.m_lID == m_OriginalCampo.lIDFaseBlocco)
				m_ctrlComboFase.SetCurSel(index);

			fasiEsameSet.MoveNext();
		}

		fasiEsameSet.CloseRecordset("CPropCampoDlg::OnInitDialog");
	}

    //

	m_pParentWnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE);

	theApp.LocalizeDialog(this, CPropCampoDlg::IDD, "PropCampoDlg");
	return bReturn;
}

void CPropCampoDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;

	UINT nID[] = { IDC_STATIC2, IDC_STATIC3, IDC_STATIC4, IDC_STATIC5, IDC_STATIC6, IDC_STATIC7 };

	// NERO --> //
	CBrush brushNero;
	CPen penNero;

	GetDlgItem(IDC_STATIC1)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	brushNero.CreateSolidBrush(RGB(0, 0, 0));
	dc.SelectObject(&brushNero);

	penNero.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SelectObject(&penNero);

	dc.Rectangle(&rect);
	// <-- NERO //

	// COLORI --> //
	for(int i = 0; i < 6; i++)
	{
		CBrush brushColori;

		GetDlgItem(nID[i])->GetWindowRect(&rect);
		ScreenToClient(&rect);

		brushColori.CreateSolidBrush(theApp.m_color[i]);
		dc.SelectObject(&brushColori);

		dc.Rectangle(&rect);
	}
	// <-- COLORI //
}

void CPropCampoDlg::OnCbnSelchangeCombo()
{
	STRUCT_LINGUETTA* pLinguetta = m_pReport->GetLinguetta();

	if (pLinguetta != NULL)
	{
		STRUCT_CAMPO campoTemp = pLinguetta->listCampi.GetAt(m_pReport->GetCurSel());
		int nCol = pLinguetta->lMostraAlbum == 1 ? DEF_X1 : DEF_X2;

		m_iContenuto = m_ctrlCombo.GetItemData(m_ctrlCombo.GetCurSel());
		campoTemp.lContenuto = g_FormCaract[m_iContenuto].lID;

		campoTemp.lL = max(campoTemp.lL, g_FormCaract[m_iContenuto].lMinL);
		campoTemp.lL = min(campoTemp.lL, g_FormCaract[m_iContenuto].lMaxL);
		campoTemp.lX = min(campoTemp.lX, nCol - campoTemp.lL);

		campoTemp.lA = max(campoTemp.lA, g_FormCaract[m_iContenuto].lMinA);
		campoTemp.lA = min(campoTemp.lA, g_FormCaract[m_iContenuto].lMaxA);
		campoTemp.lY = min(campoTemp.lY, DEF_Y - campoTemp.lA);

		m_ctrlSpinX.SetRange32(0, nCol - campoTemp.lL);
		m_ctrlSpinX.SetPos32(campoTemp.lX);
		m_ctrlSpinL.SetRange32(g_FormCaract[m_iContenuto].lMinL, min(nCol - campoTemp.lX, g_FormCaract[m_iContenuto].lMaxL));
		m_ctrlSpinL.SetPos32(campoTemp.lL);

		m_ctrlSpinY.SetRange32(DEF_Y - campoTemp.lA, 0);
		m_ctrlSpinY.SetPos32(campoTemp.lY);
		m_ctrlSpinA.SetRange32(min(DEF_Y - campoTemp.lY, g_FormCaract[m_iContenuto].lMaxA), g_FormCaract[m_iContenuto].lMinA);
		m_ctrlSpinA.SetPos32(campoTemp.lA);

		pLinguetta->listCampi.SetAt(m_pReport->GetCurSel(), campoTemp);

		UpdateData(FALSE);
		m_pParentWnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE);
	}
}

void CPropCampoDlg::OnDeltaposSpinX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	int nCol = m_pReport->GetLinguetta()->lMostraAlbum == 1 ? DEF_X1 : DEF_X2;

	STRUCT_CAMPO campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(m_pReport->GetCurSel());

	int lower;
	int upper;
	m_ctrlSpinX.GetRange32(lower, upper);

	if (pNMUpDown->iDelta < 0)
		campoTemp.lX = max(lower, pNMUpDown->iPos + pNMUpDown->iDelta);
	else
		campoTemp.lX = min(upper, pNMUpDown->iPos + pNMUpDown->iDelta);
	m_pReport->GetLinguetta()->listCampi.SetAt(m_pReport->GetCurSel(), campoTemp);

	m_pParentWnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE);

	m_ctrlSpinL.SetRange32(g_FormCaract[m_iContenuto].lMinL, min(nCol - campoTemp.lX, g_FormCaract[m_iContenuto].lMaxL));

	*pResult = 0;
}

void CPropCampoDlg::OnDeltaposSpinY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	STRUCT_CAMPO campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(m_pReport->GetCurSel());

	int lower;
	int upper;
	m_ctrlSpinY.GetRange32(upper, lower);

	if (pNMUpDown->iDelta < 0)
		campoTemp.lY = max(lower, pNMUpDown->iPos + pNMUpDown->iDelta);
	else
		campoTemp.lY = min(upper, pNMUpDown->iPos + pNMUpDown->iDelta);
	m_pReport->GetLinguetta()->listCampi.SetAt(m_pReport->GetCurSel(), campoTemp);

	m_pParentWnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE);

	m_ctrlSpinA.SetRange32(min(DEF_Y - campoTemp.lY, g_FormCaract[m_iContenuto].lMaxA), g_FormCaract[m_iContenuto].lMinA);

	*pResult = 0;
}

void CPropCampoDlg::OnDeltaposSpinL(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	int nCol = m_pReport->GetLinguetta()->lMostraAlbum == 1 ? DEF_X1 : DEF_X2;

	STRUCT_CAMPO campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(m_pReport->GetCurSel());

	int lower;
	int upper;
	m_ctrlSpinL.GetRange32(lower, upper);

	if (pNMUpDown->iDelta < 0)
		campoTemp.lL = max(lower, pNMUpDown->iPos + pNMUpDown->iDelta);
	else
		campoTemp.lL = min(upper, pNMUpDown->iPos + pNMUpDown->iDelta);
	m_pReport->GetLinguetta()->listCampi.SetAt(m_pReport->GetCurSel(), campoTemp);

	m_pParentWnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE);

	m_ctrlSpinX.SetRange32(0, nCol - campoTemp.lL);

	*pResult = 0;
}

void CPropCampoDlg::OnDeltaposSpinA(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	STRUCT_CAMPO campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(m_pReport->GetCurSel());

	int lower;
	int upper;
	m_ctrlSpinA.GetRange32(upper, lower);

	if (pNMUpDown->iDelta < 0)
		campoTemp.lA = max(lower, pNMUpDown->iPos + pNMUpDown->iDelta);
	else
		campoTemp.lA = min(upper, pNMUpDown->iPos + pNMUpDown->iDelta);
	m_pReport->GetLinguetta()->listCampi.SetAt(m_pReport->GetCurSel(), campoTemp);

	m_pParentWnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE);

	m_ctrlSpinY.SetRange32(DEF_Y - campoTemp.lA, 0);

	*pResult = 0;
}

void CPropCampoDlg::OnDeltaposSpinTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	STRUCT_CAMPO campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(m_pReport->GetCurSel());

	int lower;
	int upper;
	m_ctrlSpinTab.GetRange32(lower, upper);

	if (pNMUpDown->iDelta < 0)
		campoTemp.lTabOrder = max(lower, pNMUpDown->iPos + pNMUpDown->iDelta);
	else
		campoTemp.lTabOrder = min(upper, pNMUpDown->iPos + pNMUpDown->iDelta);
	m_pReport->GetLinguetta()->listCampi.SetAt(m_pReport->GetCurSel(), campoTemp);

	// ora ricerco il campo con il nuovo tab per scambiarli //
	POSITION pos = m_pReport->GetLinguetta()->listCampi.GetHeadPosition();
	while(pos != NULL)
	{
		if ((pos != m_pReport->GetCurSel()) && (m_pReport->GetLinguetta()->listCampi.GetAt(pos).lTabOrder == campoTemp.lTabOrder))
		{
			campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(pos);
			campoTemp.lTabOrder = pNMUpDown->iPos;
			m_pReport->GetLinguetta()->listCampi.SetAt(pos, campoTemp);

			break;
		}

		m_pReport->GetLinguetta()->listCampi.GetNext(pos);
	}

	m_pParentWnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE);

	*pResult = 0;
}

void CPropCampoDlg::OnBnClickedRadio()
{
	STRUCT_CAMPO campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(m_pReport->GetCurSel());

	UpdateData(TRUE);
	campoTemp.lColore = m_iColore - 1;
	m_pReport->GetLinguetta()->listCampi.SetAt(m_pReport->GetCurSel(), campoTemp);

	m_pParentWnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE);
}

void CPropCampoDlg::RiempiCombo()
{
	m_ctrlCombo.ResetContent();

	switch(theApp.m_nApplication)
	{
		case PRG_ENDOX:
		case PRG_DERMOX:
		{
			for(int i = 0; i < form_list_total - 9; i++)
			{
				BOOL bShowField = TRUE;

				switch(i)
				{
					case sub_pazienticronici_terapia:
					case edt_pazienticronici_score_hb:
					case edt_pazienticronici_score_s:
					{
						if (theApp.m_lOpzionalePazientiCronici != OPZIONALE_PAZIENTI_CRONICI)
							bShowField = FALSE;

						break;
					}
					case edt_medico_ricerca:
					{
						bShowField = FALSE;
						break;
					}
				}

				if (bShowField)
				{
					if (g_FormCaract[i].bEndox && !g_FormCaract[i].sDescrizione.Trim().IsEmpty())
					{
						int nIndex = m_ctrlCombo.AddString(g_FormCaract[i].sDescrizione + GetStringCampoLiberoDatabase(i));
						m_ctrlCombo.SetItemData(nIndex, (DWORD)i);
					}
				}
			}
			break;
		}
		case PRG_IMAGENT:
		{
			for(int i = 0; i < form_list_total - 12; i++)
			{
				if (g_FormCaract[i].bImageNT && !g_FormCaract[i].sDescrizione.Trim().IsEmpty())
				{
					int nIndex = m_ctrlCombo.AddString(g_FormCaract[i].sDescrizione + GetStringCampoLiberoDatabase(i));
					m_ctrlCombo.SetItemData(nIndex, (DWORD)i);
				}
			}
			break;
		}
	}

	// SANDRO 02/10/2009 //

	if ((m_iContenuto < 0) || (m_iContenuto >= form_list_total))
		m_iContenuto = 0;

	if (g_FormCaract[m_iContenuto].sDescrizione.IsEmpty())
		m_iContenuto = 0;

	// Sandro 24/04/2012 // modificato il metodo per trovare l'elemento e selezionarlo... //
	for(int i = 0; i < m_ctrlCombo.GetCount(); i++)
	{
		if ((long)m_ctrlCombo.GetItemData(i) == m_iContenuto)
		{
			m_ctrlCombo.SetCurSel(i);
			break;
		}
	}
}

void CPropCampoDlg::OnBnClickedBtnDel()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DELETE_FOGLIO), MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
	{
		STRUCT_CAMPO campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(m_pReport->GetCurSel());
		int nTabAttuale = campoTemp.lTabOrder;

		POSITION pos = m_pReport->GetLinguetta()->listCampi.GetHeadPosition();
		while(pos != NULL)
		{
			if (m_pReport->GetLinguetta()->listCampi.GetAt(pos).lTabOrder > nTabAttuale)
			{
				campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(pos);
				campoTemp.lTabOrder--;
				m_pReport->GetLinguetta()->listCampi.SetAt(pos, campoTemp);
			}

			m_pReport->GetLinguetta()->listCampi.GetNext(pos);
		}

		m_pReport->GetLinguetta()->listCampi.RemoveAt(m_pReport->GetCurSel());
		CDialog::OnOK();
	}
}


void CPropCampoDlg::OnCbnSelchangeComboFase()
{
	STRUCT_CAMPO campoTemp = m_pReport->GetLinguetta()->listCampi.GetAt(m_pReport->GetCurSel());
	
	campoTemp.lIDFaseBlocco = m_ctrlComboFase.GetItemData(m_ctrlComboFase.GetCurSel());
	m_pReport->GetLinguetta()->listCampi.SetAt(m_pReport->GetCurSel(), campoTemp);

	m_pParentWnd->RedrawWindow(NULL, NULL, RDW_INVALIDATE);
}
