#include "stdafx.h"
#include "Endox.h"
#include "TabellaEbusDynForm.h"

#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTabellaEbusDynForm::CTabellaEbusDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView),
	  m_ctrlList(TRUE, TRUE, FALSE)
{
	m_bReadOnly = FALSE;

	AssociaRecordset();
}

CTabellaEbusDynForm::~CTabellaEbusDynForm()
{
}

BEGIN_MESSAGE_MAP(CTabellaEbusDynForm, CEndoxDynForm)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

void CTabellaEbusDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_tabellaebus] == NULL)
	{
		pEsamiView->m_pDynForm[sub_tabellaebus] = new CTabellaEbusDynForm(CTabellaEbusDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_tabellaebus] != NULL)
		{
			pEsamiView->m_pDynForm[sub_tabellaebus]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_tabellaebus]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_tabellaebus]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_tabellaebus]->CreateChildForm(CTabellaEbusDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CTabellaEbusDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_TITOLO:
		case IDC_LIST:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CTabellaEbusDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_TITOLO, m_ctrlStaticTitolo);
	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

BOOL CTabellaEbusDynForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	//

	AddAnchor(IDC_STATIC_TITOLO, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));

	m_ctrlStaticTitolo.SetFont(&theApp.m_fontBold);

	//

	RiempiLista();

	//

	theApp.LocalizeDialog(this, CTabellaEbusDynForm::IDD, "TabellaEbusDynForm");
	return TRUE;
}

LRESULT CTabellaEbusDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CTabellaEbusDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(NULL, NULL);

	//

	CString sFilter;
	sFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	m_setEBUS.SetOpenFilter(sFilter);
	if (m_setEBUS.OpenRecordset("CTabellaEbusDynForm::OnFormLoad"))
	{
		if (!m_setEBUS.IsEOF())
		{
			for(int x = 0; x < 8; x++)
				for(int y = 0; y < 11; y++)
					m_ctrlList.SetItemText(y + 1, x + 1, *m_pRecordFields[x][y]);
		}

		m_setEBUS.CloseRecordset("CTabellaEbusDynForm::OnFormLoad");
	}

	//

	return 1;
}

LRESULT CTabellaEbusDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_bReadOnly = (BOOL)wParam;

	//

	m_ctrlList.EnableWindow(!m_bReadOnly);

	//

	return 1;
}

LRESULT CTabellaEbusDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int x = 0; x < 8; x++)
		for(int y = 0; y < 11; y++)
			m_ctrlList.SetItemText(y + 1, x + 1, "");

	return 1;
}

LRESULT CTabellaEbusDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CString sFilter;
	sFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	m_setEBUS.SetOpenFilter(sFilter);
	if (m_setEBUS.OpenRecordset("CTabellaEbusDynForm::OnFormSave"))
	{
		if (!m_setEBUS.IsEOF())
		{
			if (m_setEBUS.EditRecordset("CTabellaEbusDynForm::OnFormSave"))
			{
				for(int x = 0; x < 8; x++)
					for(int y = 0; y < 11; y++)
						*m_pRecordFields[x][y] = m_ctrlList.GetItemText(y + 1, x + 1);

				m_setEBUS.UpdateRecordset("CTabellaEbusDynForm::OnFormSave");
			}
		}
		else
		{
			if (m_setEBUS.AddNewRecordset("CTabellaEbusDynForm::OnFormSave"))
			{
				m_setEBUS.m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;

				for(int x = 0; x < 8; x++)
					for(int y = 0; y < 11; y++)
						*m_pRecordFields[x][y] = m_ctrlList.GetItemText(y + 1, x + 1);

				m_setEBUS.UpdateRecordset("CTabellaEbusDynForm::OnFormSave");
			}
		}

		m_setEBUS.CloseRecordset("CTabellaEbusDynForm::OnFormSave");
	}

	//

	return 1;
}

LRESULT CTabellaEbusDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	/*
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (m_pEsamiView->m_pEsamiSet->m_iAllergie >= 0)
	{
		ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, (long*)&m_pEsamiView->m_pEsamiSet->m_iAllergie, "EEsami.Allergie", 0, "AND");

		if (m_pEsamiView->m_pEsamiSet->m_sDescrizioneAllergie.Compare("") != 0)
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sDescrizioneAllergie, "EEsami.DescrizioneAllergie", 0);
	}
	*/

	return 1;
}

long CTabellaEbusDynForm::GetContenuto()
{
	return sub_tabellaebus;
}

BOOL CTabellaEbusDynForm::CampoObbligatorioValido()
{
	return TRUE;
}

void CTabellaEbusDynForm::AssociaRecordset()
{
	m_pRecordFields[0][0] = &m_setEBUS.m_sDimensione_12R;
	m_pRecordFields[0][1] = &m_setEBUS.m_sDimensione_11R;
	m_pRecordFields[0][2] = &m_setEBUS.m_sDimensione_10R;
	m_pRecordFields[0][3] = &m_setEBUS.m_sDimensione_4R;
	m_pRecordFields[0][4] = &m_setEBUS.m_sDimensione_2R;
	m_pRecordFields[0][5] = &m_setEBUS.m_sDimensione_7;
	m_pRecordFields[0][6] = &m_setEBUS.m_sDimensione_2L;
	m_pRecordFields[0][7] = &m_setEBUS.m_sDimensione_4L;
	m_pRecordFields[0][8] = &m_setEBUS.m_sDimensione_10L;
	m_pRecordFields[0][9] = &m_setEBUS.m_sDimensione_11L;
	m_pRecordFields[0][10] = &m_setEBUS.m_sDimensione_12L;

	m_pRecordFields[1][0] = &m_setEBUS.m_sPuntura_12R;
	m_pRecordFields[1][1] = &m_setEBUS.m_sPuntura_11R;
	m_pRecordFields[1][2] = &m_setEBUS.m_sPuntura_10R;
	m_pRecordFields[1][3] = &m_setEBUS.m_sPuntura_4R;
	m_pRecordFields[1][4] = &m_setEBUS.m_sPuntura_2R;
	m_pRecordFields[1][5] = &m_setEBUS.m_sPuntura_7;
	m_pRecordFields[1][6] = &m_setEBUS.m_sPuntura_2L;
	m_pRecordFields[1][7] = &m_setEBUS.m_sPuntura_4L;
	m_pRecordFields[1][8] = &m_setEBUS.m_sPuntura_10L;
	m_pRecordFields[1][9] = &m_setEBUS.m_sPuntura_11L;
	m_pRecordFields[1][10] = &m_setEBUS.m_sPuntura_12L;

	m_pRecordFields[2][0] = &m_setEBUS.m_sNumeroPunture_12R;
	m_pRecordFields[2][1] = &m_setEBUS.m_sNumeroPunture_11R;
	m_pRecordFields[2][2] = &m_setEBUS.m_sNumeroPunture_10R;
	m_pRecordFields[2][3] = &m_setEBUS.m_sNumeroPunture_4R;
	m_pRecordFields[2][4] = &m_setEBUS.m_sNumeroPunture_2R;
	m_pRecordFields[2][5] = &m_setEBUS.m_sNumeroPunture_7;
	m_pRecordFields[2][6] = &m_setEBUS.m_sNumeroPunture_2L;
	m_pRecordFields[2][7] = &m_setEBUS.m_sNumeroPunture_4L;
	m_pRecordFields[2][8] = &m_setEBUS.m_sNumeroPunture_10L;
	m_pRecordFields[2][9] = &m_setEBUS.m_sNumeroPunture_11L;
	m_pRecordFields[2][10] = &m_setEBUS.m_sNumeroPunture_12L;

	m_pRecordFields[3][0] = &m_setEBUS.m_sForma_12R;
	m_pRecordFields[3][1] = &m_setEBUS.m_sForma_11R;
	m_pRecordFields[3][2] = &m_setEBUS.m_sForma_10R;
	m_pRecordFields[3][3] = &m_setEBUS.m_sForma_4R;
	m_pRecordFields[3][4] = &m_setEBUS.m_sForma_2R;
	m_pRecordFields[3][5] = &m_setEBUS.m_sForma_7;
	m_pRecordFields[3][6] = &m_setEBUS.m_sForma_2L;
	m_pRecordFields[3][7] = &m_setEBUS.m_sForma_4L;
	m_pRecordFields[3][8] = &m_setEBUS.m_sForma_10L;
	m_pRecordFields[3][9] = &m_setEBUS.m_sForma_11L;
	m_pRecordFields[3][10] = &m_setEBUS.m_sForma_12L;

	m_pRecordFields[4][0] = &m_setEBUS.m_sMargine_12R;
	m_pRecordFields[4][1] = &m_setEBUS.m_sMargine_11R;
	m_pRecordFields[4][2] = &m_setEBUS.m_sMargine_10R;
	m_pRecordFields[4][3] = &m_setEBUS.m_sMargine_4R;
	m_pRecordFields[4][4] = &m_setEBUS.m_sMargine_2R;
	m_pRecordFields[4][5] = &m_setEBUS.m_sMargine_7;
	m_pRecordFields[4][6] = &m_setEBUS.m_sMargine_2L;
	m_pRecordFields[4][7] = &m_setEBUS.m_sMargine_4L;
	m_pRecordFields[4][8] = &m_setEBUS.m_sMargine_10L;
	m_pRecordFields[4][9] = &m_setEBUS.m_sMargine_11L;
	m_pRecordFields[4][10] = &m_setEBUS.m_sMargine_12L;

	m_pRecordFields[5][0] = &m_setEBUS.m_sEcogenicita_12R;
	m_pRecordFields[5][1] = &m_setEBUS.m_sEcogenicita_11R;
	m_pRecordFields[5][2] = &m_setEBUS.m_sEcogenicita_10R;
	m_pRecordFields[5][3] = &m_setEBUS.m_sEcogenicita_4R;
	m_pRecordFields[5][4] = &m_setEBUS.m_sEcogenicita_2R;
	m_pRecordFields[5][5] = &m_setEBUS.m_sEcogenicita_7;
	m_pRecordFields[5][6] = &m_setEBUS.m_sEcogenicita_2L;
	m_pRecordFields[5][7] = &m_setEBUS.m_sEcogenicita_4L;
	m_pRecordFields[5][8] = &m_setEBUS.m_sEcogenicita_10L;
	m_pRecordFields[5][9] = &m_setEBUS.m_sEcogenicita_11L;
	m_pRecordFields[5][10] = &m_setEBUS.m_sEcogenicita_12L;

	m_pRecordFields[6][0] = &m_setEBUS.m_sFilo_12R;
	m_pRecordFields[6][1] = &m_setEBUS.m_sFilo_11R;
	m_pRecordFields[6][2] = &m_setEBUS.m_sFilo_10R;
	m_pRecordFields[6][3] = &m_setEBUS.m_sFilo_4R;
	m_pRecordFields[6][4] = &m_setEBUS.m_sFilo_2R;
	m_pRecordFields[6][5] = &m_setEBUS.m_sFilo_7;
	m_pRecordFields[6][6] = &m_setEBUS.m_sFilo_2L;
	m_pRecordFields[6][7] = &m_setEBUS.m_sFilo_4L;
	m_pRecordFields[6][8] = &m_setEBUS.m_sFilo_10L;
	m_pRecordFields[6][9] = &m_setEBUS.m_sFilo_11L;
	m_pRecordFields[6][10] = &m_setEBUS.m_sFilo_12L;

	m_pRecordFields[7][0] = &m_setEBUS.m_sNecrosi_12R;
	m_pRecordFields[7][1] = &m_setEBUS.m_sNecrosi_11R;
	m_pRecordFields[7][2] = &m_setEBUS.m_sNecrosi_10R;
	m_pRecordFields[7][3] = &m_setEBUS.m_sNecrosi_4R;
	m_pRecordFields[7][4] = &m_setEBUS.m_sNecrosi_2R;
	m_pRecordFields[7][5] = &m_setEBUS.m_sNecrosi_7;
	m_pRecordFields[7][6] = &m_setEBUS.m_sNecrosi_2L;
	m_pRecordFields[7][7] = &m_setEBUS.m_sNecrosi_4L;
	m_pRecordFields[7][8] = &m_setEBUS.m_sNecrosi_10L;
	m_pRecordFields[7][9] = &m_setEBUS.m_sNecrosi_11L;
	m_pRecordFields[7][10] = &m_setEBUS.m_sNecrosi_12L;
}

void CTabellaEbusDynForm::RiempiLista()
{
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);

	//

	tagLISTCOMBO tagTemp;

	// lista sì/no //

	CStringIDList listSiNo;

	tagTemp.lID = 0;
	tagTemp.strName = "";
	listSiNo.AddTail(tagTemp);

	tagTemp.lID = 1;
	tagTemp.strName = theApp.GetMessageString(IDS_YES);
	listSiNo.AddTail(tagTemp);

	tagTemp.lID = 2;
	tagTemp.strName = theApp.GetMessageString(IDS_NO);
	listSiNo.AddTail(tagTemp);

	// lista ovale/rotondo //

	CStringIDList listOvaleRotondo;

	tagTemp.lID = 0;
	tagTemp.strName = "";
	listOvaleRotondo.AddTail(tagTemp);

	tagTemp.lID = 1;
	tagTemp.strName = theApp.GetMessageString(IDS_OVALE);
	listOvaleRotondo.AddTail(tagTemp);

	tagTemp.lID = 2;
	tagTemp.strName = theApp.GetMessageString(IDS_ROTONDO);
	listOvaleRotondo.AddTail(tagTemp);

	// lista definito/indefinito //

	CStringIDList listDefinitoIndefinito;

	tagTemp.lID = 0;
	tagTemp.strName = "";
	listDefinitoIndefinito.AddTail(tagTemp);

	tagTemp.lID = 1;
	tagTemp.strName = theApp.GetMessageString(IDS_DEFINITO);
	listDefinitoIndefinito.AddTail(tagTemp);

	tagTemp.lID = 2;
	tagTemp.strName = theApp.GetMessageString(IDS_INDEFINITO);
	listDefinitoIndefinito.AddTail(tagTemp);

	// lista omogeneo/eterogeneo //

	CStringIDList listOmogeneoEterogeneo;

	tagTemp.lID = 0;
	tagTemp.strName = "";
	listOmogeneoEterogeneo.AddTail(tagTemp);

	tagTemp.lID = 1;
	tagTemp.strName = theApp.GetMessageString(IDS_OMOGENEO);
	listOmogeneoEterogeneo.AddTail(tagTemp);

	tagTemp.lID = 2;
	tagTemp.strName = theApp.GetMessageString(IDS_ETEROGENEO);
	listOmogeneoEterogeneo.AddTail(tagTemp);

	// inserisco tutte le colonne //

	m_ctrlList.InsertColumn(0, "");
	m_ctrlList.InsertColumn(1, "");
	m_ctrlList.InsertColumn(2, "");
	m_ctrlList.InsertColumn(3, "");
	m_ctrlList.InsertColumn(4, "");
	m_ctrlList.InsertColumn(5, "");
	m_ctrlList.InsertColumn(6, "");
	m_ctrlList.InsertColumn(7, "");
	m_ctrlList.InsertColumn(8, "");

	// inserisco la prima riga con tutti i titoli sopra //

	m_ctrlList.InsertItem(0, theApp.GetMessageString(IDS_SERIE));
	m_ctrlList.SetSubItemBkColor(0, 0, RGB_GRAY_LIGHT);
	m_ctrlList.SetItemText(0, 1, theApp.GetMessageString(IDS_DIMENSIONE));
	m_ctrlList.SetSubItemBkColor(0, 1, RGB_GRAY_LIGHT);
	m_ctrlList.SetItemText(0, 2, theApp.GetMessageString(IDS_PUNTURA));
	m_ctrlList.SetSubItemBkColor(0, 2, RGB_GRAY_LIGHT);
	m_ctrlList.SetItemText(0, 3, theApp.GetMessageString(IDS_NUMEROPUNTURE));
	m_ctrlList.SetSubItemBkColor(0, 3, RGB_GRAY_LIGHT);
	m_ctrlList.SetItemText(0, 4, theApp.GetMessageString(IDS_FORMA));
	m_ctrlList.SetSubItemBkColor(0, 4, RGB_GRAY_LIGHT);
	m_ctrlList.SetItemText(0, 5, theApp.GetMessageString(IDS_MARGINE));
	m_ctrlList.SetSubItemBkColor(0, 5, RGB_GRAY_LIGHT);
	m_ctrlList.SetItemText(0, 6, theApp.GetMessageString(IDS_ECOGENICITA));
	m_ctrlList.SetSubItemBkColor(0, 6, RGB_GRAY_LIGHT);
	m_ctrlList.SetItemText(0, 7, theApp.GetMessageString(IDS_FILO));
	m_ctrlList.SetSubItemBkColor(0, 7, RGB_GRAY_LIGHT);
	m_ctrlList.SetItemText(0, 8, theApp.GetMessageString(IDS_NECROSI));
	m_ctrlList.SetSubItemBkColor(0, 8, RGB_GRAY_LIGHT);

	// inserisco tutte le righe con i titoli a sinistra //

	m_ctrlList.InsertItem(1, theApp.GetMessageString(IDS_12R));
	m_ctrlList.SetSubItemBkColor(1, 0, RGB_GRAY_LIGHT);
	m_ctrlList.InsertItem(2, theApp.GetMessageString(IDS_11R));
	m_ctrlList.SetSubItemBkColor(2, 0, RGB_GRAY_LIGHT);
	m_ctrlList.InsertItem(3, theApp.GetMessageString(IDS_10R));
	m_ctrlList.SetSubItemBkColor(3, 0, RGB_GRAY_LIGHT);
	m_ctrlList.InsertItem(4, theApp.GetMessageString(IDS_4R));
	m_ctrlList.SetSubItemBkColor(4, 0, RGB_GRAY_LIGHT);
	m_ctrlList.InsertItem(5, theApp.GetMessageString(IDS_2R));
	m_ctrlList.SetSubItemBkColor(5, 0, RGB_GRAY_LIGHT);
	m_ctrlList.InsertItem(6, theApp.GetMessageString(IDS_7));
	m_ctrlList.SetSubItemBkColor(6, 0, RGB_GRAY_LIGHT);
	m_ctrlList.InsertItem(7, theApp.GetMessageString(IDS_2L));
	m_ctrlList.SetSubItemBkColor(7, 0, RGB_GRAY_LIGHT);
	m_ctrlList.InsertItem(8, theApp.GetMessageString(IDS_4L));
	m_ctrlList.SetSubItemBkColor(8, 0, RGB_GRAY_LIGHT);
	m_ctrlList.InsertItem(9, theApp.GetMessageString(IDS_10L));
	m_ctrlList.SetSubItemBkColor(9, 0, RGB_GRAY_LIGHT);
	m_ctrlList.InsertItem(10, theApp.GetMessageString(IDS_11L));
	m_ctrlList.SetSubItemBkColor(10, 0, RGB_GRAY_LIGHT);
	m_ctrlList.InsertItem(11, theApp.GetMessageString(IDS_12L));
	m_ctrlList.SetSubItemBkColor(11, 0, RGB_GRAY_LIGHT);

	// imposto la colonna "dimensione" //

	for(int i = 1; i < m_ctrlList.GetItemCount(); i++)
		m_ctrlList.SetSubItemEdit(i, 1);

	// imposto la colonna "puntura" //

	for(int i = 1; i < m_ctrlList.GetItemCount(); i++)
		m_ctrlList.SetSubItemCombo(i, 2, listSiNo);

	// imposto la colonna "numero punture" //

	for(int i = 1; i < m_ctrlList.GetItemCount(); i++)
		m_ctrlList.SetSubItemEdit(i, 3, TRUE);

	// imposto la colonna "forma" //

	for(int i = 1; i < m_ctrlList.GetItemCount(); i++)
		m_ctrlList.SetSubItemCombo(i, 4, listOvaleRotondo);

	// imposto la colonna "margine" //

	for(int i = 1; i < m_ctrlList.GetItemCount(); i++)
		m_ctrlList.SetSubItemCombo(i, 5, listDefinitoIndefinito);

	// imposto la colonna "ecogenicità" //

	for(int i = 1; i < m_ctrlList.GetItemCount(); i++)
		m_ctrlList.SetSubItemCombo(i, 6, listOmogeneoEterogeneo);

	// imposto la colonna "filo" //

	for(int i = 1; i < m_ctrlList.GetItemCount(); i++)
		m_ctrlList.SetSubItemCombo(i, 7, listSiNo);

	// imposto la colonna "necrosi" //

	for(int i = 1; i < m_ctrlList.GetItemCount(); i++)
		m_ctrlList.SetSubItemCombo(i, 8, listSiNo);

	//

	m_ctrlList.SetRedraw(TRUE);
}