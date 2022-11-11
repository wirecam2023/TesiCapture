#include "stdafx.h"
#include "Endox.h"

#include "ModStatoColoreDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CModStatoColoreDlg, CDialog)

CModStatoColoreDlg::CModStatoColoreDlg(CWnd* pParent)
	: CDialog(CModStatoColoreDlg::IDD, pParent)
{
	m_clColor1 = GetSysColor(COLOR_BTNFACE);
	m_clColor2 = GetSysColor(COLOR_BTNFACE);
	m_lID = -1;
}

CModStatoColoreDlg::~CModStatoColoreDlg()
{
}

void CModStatoColoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_PREVIEW, m_ctrlStaticPreview);

	DDX_Control(pDX, IDC_BTN_ESCI, m_ctrlButtonEsci);
}

BEGIN_MESSAGE_MAP(CModStatoColoreDlg, CDialog)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()

	ON_BN_CLICKED(IDC_BTN_ESCI, &CModStatoColoreDlg::OnBnClickedBtnEsci)
END_MESSAGE_MAP()

BOOL CModStatoColoreDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlStaticPreview.SetFont(&theApp.m_fontBig);

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0);

	RiempiLista();

	theApp.LocalizeDialog(this, CModStatoColoreDlg::IDD, "ModStatoColoreDlg");
	return TRUE;
}

void CModStatoColoreDlg::OnPaint()
{
	CPaintDC dc(this);
	
	CRect rect;
	GetDlgItem(IDC_STATIC_COLOR1)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	dc.FillRect(&rect, &CBrush(m_clColor1));

	GetDlgItem(IDC_STATIC_COLOR2)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	dc.FillRect(&rect, &CBrush(m_clColor2));
}

HBRUSH CModStatoColoreDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_PREVIEW:
		{
			pDC->SetTextColor(m_clColor1);
			pDC->SetBkColor(m_clColor2);
			hBrush = m_brushSfondo;
			break;
		}
	}

	return hBrush;
}

void CModStatoColoreDlg::OnCancel()
{
}

void CModStatoColoreDlg::OnOK()
{
}

void CModStatoColoreDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags, point);

	CRect rect;
	GetDlgItem(IDC_STATIC_COLOR1)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	if (rect.PtInRect(point))
	{
		CColorDialog dlg(m_clColor1);
		if (dlg.DoModal() == IDOK)
			m_clColor1 = dlg.GetColor();
	}

	GetDlgItem(IDC_STATIC_COLOR2)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	if (rect.PtInRect(point))
	{
		CColorDialog dlg(m_clColor2);
		if (dlg.DoModal() == IDOK)
			m_clColor2 = dlg.GetColor();
	}

	SaveNewColor();
	RefreshColor();
}

void CModStatoColoreDlg::CaricaDati()
{
	m_clColor1 = GetSysColor(COLOR_BTNFACE);
	m_clColor2 = GetSysColor(COLOR_BTNFACE);

	switch(m_lID)
	{
		case 0:
		{
			m_clColor1 = theApp.m_colorVisualizzazioneAperto;
			m_clColor2 = theApp.m_colorVisualizzazioneApertoSfondo;
			break;
		}
		case 1:
		{
			m_clColor1 = theApp.m_colorVisualizzazioneFirmato;
			m_clColor2 = theApp.m_colorVisualizzazioneFirmatoSfondo;
			break;
		}
		case 2:
		{
			m_clColor1 = theApp.m_colorVisualizzazioneChiuso;
			m_clColor2 = theApp.m_colorVisualizzazioneChiusoSfondo;
			break;
		}
		case 3:
		{
			m_clColor1 = theApp.m_colorAggiuntaPaziente;
			m_clColor2 = theApp.m_colorAggiuntaPazienteSfondo;
			break;
		}
		case 4:
		{
			m_clColor1 = theApp.m_colorModificaPaziente;
			m_clColor2 = theApp.m_colorModificaPazienteSfondo;
			break;
		}
		case 5:
		{
			m_clColor1 = theApp.m_colorAggiuntaEsame;
			m_clColor2 = theApp.m_colorAggiuntaEsameSfondo;
			break;
		}
		case 6:
		{
			m_clColor1 = theApp.m_colorModificaEsame;
			m_clColor2 = theApp.m_colorModificaEsameSfondo;
			break;
		}
		case 7:
		{
			m_clColor1 = theApp.m_colorRicercaPaziente;
			m_clColor2 = theApp.m_colorRicercaPazienteSfondo;
			break;
		}
		case 8:
		{
			m_clColor1 = theApp.m_colorRicercaEsame;
			m_clColor2 = theApp.m_colorRicercaEsameSfondo;
			break;
		}
		case 9:
		{
			m_clColor1 = theApp.m_colorVisualizzazioneInArchiviazione;
			m_clColor2 = theApp.m_colorVisualizzazioneInArchiviazioneSfondo;
			break;
		}
		case 10:
		{
			m_clColor1 = theApp.m_colorVisualizzazioneArchiviato;
			m_clColor2 = theApp.m_colorVisualizzazioneArchiviatoSfondo;
			break;
		}
		case 11:
		{
			m_clColor1 = theApp.m_colorStreamingAttivo;
			m_clColor2 = theApp.m_colorStreamingAttivoSfondo;
			break;
		}
		case 12:
		{
			m_clColor1 = theApp.m_colorStreamingConnesso;
			m_clColor2 = theApp.m_colorStreamingConnessoSfondo;
			break;
		}
	}

	RefreshColor();
}

void CModStatoColoreDlg::RiempiLista()
{
	m_ctrlList.DeleteAllItems();

	int nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_STATO_ESAMEAPERTO));
	m_ctrlList.SetItemData(nItem, 0);
	nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_STATO_ESAMEFIRMATO));
	m_ctrlList.SetItemData(nItem, 1);
	nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_STATO_ESAMECHIUSO));
	m_ctrlList.SetItemData(nItem, 2);
	nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_STATO_AGGIUNTAPAZIENTE));
	m_ctrlList.SetItemData(nItem, 3);
	nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_STATO_AGGIUNTAESAME));
	m_ctrlList.SetItemData(nItem, 5);
	nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_STATO_MODIFICAPAZIENTE));
	m_ctrlList.SetItemData(nItem, 4);
	nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_STATO_MODIFICAESAME));
	m_ctrlList.SetItemData(nItem, 6);
	nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_STATO_RICERCAPAZIENTE));
	m_ctrlList.SetItemData(nItem, 7);
	nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_STATO_RICERCAESAME));
	m_ctrlList.SetItemData(nItem, 8);
	nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_ESAMIVIEW_STATE_13));
	m_ctrlList.SetItemData(nItem, 9);
	nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_ESAMIVIEW_STATE_12));
	m_ctrlList.SetItemData(nItem, 10);
	nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_ESAMIVIEW_STATE_14));
	m_ctrlList.SetItemData(nItem, 11);
	nItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), theApp.GetMessageString(IDS_ESAMIVIEW_STATE_15));
	m_ctrlList.SetItemData(nItem, 12);

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}

void CModStatoColoreDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lID = -1;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_lID = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));

	CaricaDati();
}

void CModStatoColoreDlg::SaveNewColor()
{
	switch(m_lID)
	{
		case 0:
		{
			theApp.m_colorVisualizzazioneAperto = m_clColor1;
			theApp.m_colorVisualizzazioneApertoSfondo = m_clColor2;
			break;
		}
		case 1:
		{
			theApp.m_colorVisualizzazioneFirmato = m_clColor1;
			theApp.m_colorVisualizzazioneFirmatoSfondo = m_clColor2;
			break;
		}
		case 2:
		{
			theApp.m_colorVisualizzazioneChiuso = m_clColor1;
			theApp.m_colorVisualizzazioneChiusoSfondo = m_clColor2;
			break;
		}
		case 3:
		{
			theApp.m_colorAggiuntaPaziente = m_clColor1;
			theApp.m_colorAggiuntaPazienteSfondo = m_clColor2;
			break;
		}
		case 4:
		{
			theApp.m_colorModificaPaziente = m_clColor1;
			theApp.m_colorModificaPazienteSfondo = m_clColor2;
			break;
		}
		case 5:
		{
			theApp.m_colorAggiuntaEsame = m_clColor1;
			theApp.m_colorAggiuntaEsameSfondo = m_clColor2;
			break;
		}
		case 6:
		{
			theApp.m_colorModificaEsame = m_clColor1;
			theApp.m_colorModificaEsameSfondo = m_clColor2;
			break;
		}
		case 7:
		{
			theApp.m_colorRicercaPaziente = m_clColor1;
			theApp.m_colorRicercaPazienteSfondo = m_clColor2;
			break;
		}
		case 8:
		{
			theApp.m_colorRicercaEsame = m_clColor1;
			theApp.m_colorRicercaEsameSfondo = m_clColor2;
			break;
		}
		case 9:
		{
			theApp.m_colorVisualizzazioneInArchiviazione = m_clColor1;
			theApp.m_colorVisualizzazioneInArchiviazioneSfondo = m_clColor2;
			break;
		}
		case 10:
		{
			theApp.m_colorVisualizzazioneArchiviato = m_clColor1;
			theApp.m_colorVisualizzazioneArchiviatoSfondo = m_clColor2;
			break;
		}
		case 11:
		{
			theApp.m_colorStreamingAttivo = m_clColor1;
			theApp.m_colorStreamingAttivoSfondo = m_clColor2;
			break;
		}
		case 12:
		{
			theApp.m_colorStreamingConnesso = m_clColor1;
			theApp.m_colorStreamingConnessoSfondo = m_clColor2;
			break;
		}

	}
}

void CModStatoColoreDlg::RefreshColor()
{
	m_brushSfondo.DeleteObject();
	m_brushSfondo.CreateSolidBrush(m_clColor2);

	CRect rect;
	GetDlgItem(IDC_STATIC_COLOR1)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);

	GetDlgItem(IDC_STATIC_COLOR2)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);

	GetDlgItem(IDC_STATIC_PREVIEW)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);
}

void CModStatoColoreDlg::OnBnClickedBtnEsci()
{
	CDialog::OnOK();
}
