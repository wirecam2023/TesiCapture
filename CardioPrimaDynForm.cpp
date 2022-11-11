#include "stdafx.h"
#include "Endox.h"
#include "CardioPrimaDynForm.h"

#include "EsamiSet.h"
#include "EsamiView.h"
#include "ProtocolloCardioSet.h"
#include "ProtocolloColonneSet.h"
#include "ProtocolloEsamiSet.h"
#include "ProtocolloValoriDefaultSet.h"

#define RGB_MODIFICABILE RGB(255, 255, 191)
#define RGB_SOLALETTURA RGB(223, 223, 223)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCardioPrimaDynForm::CCardioPrimaDynForm(CWnd* pParent, CEsamiView* pEsamiView)
: CEndoxDynForm(CCardioPrimaDynForm::IDD, pParent, pEsamiView),
m_ctrlList(FALSE, TRUE, TRUE)
{
	m_lIDProtocollo = 0;
	m_lNumColonne = 0;
	m_pArrayStructColonne = NULL;
}

CCardioPrimaDynForm::~CCardioPrimaDynForm(void)
{
	if (m_pArrayStructColonne != NULL)
	{
		delete m_pArrayStructColonne;
		m_pArrayStructColonne = NULL;
	}
}

BEGIN_MESSAGE_MAP(CCardioPrimaDynForm, CEndoxDynForm)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

void CCardioPrimaDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_cardio_prima] == NULL)
	{
		pEsamiView->m_pDynForm[sub_cardio_prima] = new CCardioPrimaDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_cardio_prima] != NULL)
		{
			pEsamiView->m_pDynForm[sub_cardio_prima]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_cardio_prima]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_cardio_prima]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_cardio_prima]->CreateChildForm(CCardioPrimaDynForm::IDD, pParent, rectFrame);
		}
	}
}

void CCardioPrimaDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	//

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_EDIT_MASSIMA, m_ctrlEditMassima);
	DDX_Control(pDX, IDC_EDIT_SUBMASSIMA, m_ctrlEditSubmassima);

	DDX_Control(pDX, IDC_STATIC_TITLE, m_ctrlStaticTitle);
	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);

	//

	DDX_FieldText(pDX, IDC_EDIT_MASSIMA, m_pEsamiView->m_pEsamiSet->m_sFCMassima, m_pEsamiView->m_pEsamiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_SUBMASSIMA, m_pEsamiView->m_pEsamiSet->m_sFCSubmassima, m_pEsamiView->m_pEsamiSet->GetRecordset());
}

HBRUSH CCardioPrimaDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_TITLE:
		case IDC_STATIC_00:
		case IDC_EDIT_MASSIMA:
		case IDC_STATIC_01:
		case IDC_EDIT_SUBMASSIMA:
		case IDC_LIST:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hReturn;
}

BOOL CCardioPrimaDynForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_TITLE, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_00, CSize(0, 0), CSize(0, 0)); // CSize(0, 0), CSize(50, 0));
	AddAnchor(IDC_EDIT_MASSIMA, CSize(0, 0), CSize(0, 0)); // CSize(50, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_01, CSize(0, 0), CSize(0, 0)); // CSize(0, 0), CSize(50, 0));
	AddAnchor(IDC_EDIT_SUBMASSIMA, CSize(0, 0), CSize(0, 0)); // CSize(50, 0), CSize(100, 0));
	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));

	m_ctrlStaticTitle.SetFont(&theApp.m_fontBold);
	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);

	//

	m_lIDProtocollo = CProtocolloCardioSet().GetIDFromFase(PROTOCOLLO_FASE_PRIMA);
	if (m_lIDProtocollo > 0)
		ListControlPrepara();

	//

	theApp.LocalizeDialog(this, CCardioPrimaDynForm::IDD, "CardioPrimaDynForm");
	return TRUE;
}

LRESULT CCardioPrimaDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CCardioPrimaDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	m_ctrlList.SetRedraw(FALSE);

	ListControlDeleteAll();
	if (CProtocolloEsamiSet().HasRows(m_pEsamiView->m_pEsamiSet->m_lContatore, m_lIDProtocollo))
	{
		// carico i dati già inseriti //
		ListControlCaricaDatiEsame();
	}
	else
	{
		// carico i valori di default //
		ListControlCaricaDefault();
	}

	m_ctrlList.SetRedraw(TRUE);
	return UpdateData(FALSE);
}

LRESULT CCardioPrimaDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	m_ctrlEditMassima.SetReadOnly((BOOL)wParam);
	m_ctrlEditSubmassima.SetReadOnly((BOOL)wParam);

	m_ctrlList.SetReadOnly((BOOL)wParam);

	return 1;
}

LRESULT CCardioPrimaDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	ListControlDeleteAll();
	return 1;
}

LRESULT CCardioPrimaDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	for (int iRiga = 1; iRiga < m_ctrlList.GetItemCount(); iRiga++)
		for (int iColonna = 0; iColonna < m_lNumColonne; iColonna++)
			CProtocolloEsamiSet().AddEdtRow(m_pEsamiView->m_pEsamiSet->m_lContatore, m_lIDProtocollo, m_pArrayStructColonne[iColonna].lID, iRiga, m_ctrlList.GetItemText(iRiga, iColonna));

	return UpdateData(TRUE);
}

LRESULT CCardioPrimaDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	return 1;
}

long CCardioPrimaDynForm::GetContenuto()
{
	return sub_cardio_prima;
}

BOOL CCardioPrimaDynForm::CampoObbligatorioValido()
{
	return FALSE;
}

void CCardioPrimaDynForm::ListControlPrepara()
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li", m_lIDProtocollo);

	CProtocolloColonneSet setPC;
	setPC.SetOpenFilter(sFilter);
	setPC.SetSortRecord("ORDINE");
	if (setPC.OpenRecordset("CCardioPrimaDynForm::OnInitDialog"))
	{
		while (!setPC.IsEOF())
		{
			m_lNumColonne++;
			setPC.MoveNext();
		}

		if (m_lNumColonne > 0)
		{
			setPC.MoveFirst();

			m_pArrayStructColonne = new STRUCT_COLONNE[m_lNumColonne];

			int nIndex = 0;
			while (!setPC.IsEOF())
			{
				m_ctrlList.InsertColumn(nIndex, setPC.m_sDescrizione, LVCFMT_LEFT, 0);

				m_pArrayStructColonne[nIndex].lID = setPC.m_lID;
				strcpy_s(m_pArrayStructColonne[nIndex].szDescrizione, setPC.m_sDescrizione);
				m_pArrayStructColonne[nIndex].bValoreModificabile = setPC.m_bValoriModificabili;

				nIndex++;
				setPC.MoveNext();
			}
			m_ctrlList.InsertColumn(nIndex, "", LVCFMT_LEFT, 0);

			for (int i = 0; i < m_lNumColonne; i++)
				m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
		}

		setPC.CloseRecordset("CCardioPrimaDynForm::OnInitDialog");
	}
}

void CCardioPrimaDynForm::ListControlCaricaDatiEsame()
{
	CString sFilter;
	sFilter.Format("IDESAME=%li AND IDPROTOCOLLO=%li", m_pEsamiView->m_pEsamiSet->m_lContatore, m_lIDProtocollo);

	CProtocolloEsamiSet setPE;
	setPE.SetOpenFilter(sFilter);
	setPE.SetSortRecord("ORDINE, IDCOLONNA");
	if (setPE.OpenRecordset("CCardioPrimaDynForm::ListControlCaricaDatiEsame"))
	{
		int nIndex = 0;
		long lLastOrder = -1;

		while (!setPE.IsEOF())
		{
			// se serve aggiungo una riga //

			if (setPE.m_lOrdine != lLastOrder)
			{
				nIndex++;

				m_ctrlList.InsertItem(nIndex, "");
				m_ctrlList.SetItemData(nIndex, setPE.m_lOrdine);

				for (int i = 0; i < m_lNumColonne; i++)
					if (m_pArrayStructColonne[i].bValoreModificabile)
						m_ctrlList.SetSubItemEdit(nIndex, i, FALSE, 250);

				lLastOrder = setPE.m_lOrdine;
			}

			//

			for (int i = 0; i < m_lNumColonne; i++)
			{
				if (m_pArrayStructColonne[i].lID == setPE.m_lIDColonna)
				{
					m_ctrlList.SetItemText(nIndex, i, setPE.m_sValore);
					break;
				}
			}

			//

			setPE.MoveNext();
		}

		setPE.CloseRecordset("CCardioPrimaDynForm::ListControlCaricaDatiEsame");
	}

	//

	for (int i = 0; i < m_lNumColonne; i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE);

	//

	for (int iSubItem = 0; iSubItem < m_lNumColonne; iSubItem++)
	{
		if (!m_pArrayStructColonne[iSubItem].bValoreModificabile)
		{
			for (int iItem = 1; iItem < m_ctrlList.GetItemCount(); iItem++)
				m_ctrlList.SetSubItemBkColor(iItem, iSubItem, RGB_SOLALETTURA);
		}
		else
		{
			for (int iItem = 1; iItem < m_ctrlList.GetItemCount(); iItem++)
				m_ctrlList.SetSubItemBkColor(iItem, iSubItem, RGB_MODIFICABILE);
		}
	}
}

void CCardioPrimaDynForm::ListControlCaricaDefault()
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li", m_lIDProtocollo);

	CProtocolloValoriDefaultSet setPVD;
	setPVD.SetOpenFilter(sFilter);
	setPVD.SetSortRecord("ORDINE, IDCOLONNA");
	if (setPVD.OpenRecordset("CCardioPrimaDynForm::ListControlCaricaDefault"))
	{
		int nIndex = 0;
		long lLastOrder = -1;

		while (!setPVD.IsEOF())
		{
			// se serve aggiungo una riga //

			if (setPVD.m_lOrdine != lLastOrder)
			{
				nIndex++;

				m_ctrlList.InsertItem(nIndex, "");
				m_ctrlList.SetItemData(nIndex, setPVD.m_lOrdine);

				for (int i = 0; i < m_lNumColonne; i++)
					if (m_pArrayStructColonne[i].bValoreModificabile)
						m_ctrlList.SetSubItemEdit(nIndex, i, FALSE, 250);

				lLastOrder = setPVD.m_lOrdine;
			}

			//

			for (int i = 0; i < m_lNumColonne; i++)
			{
				if (m_pArrayStructColonne[i].lID == setPVD.m_lIDColonna)
				{
					m_ctrlList.SetItemText(nIndex, i, setPVD.m_sValore);
					break;
				}
			}

			//

			setPVD.MoveNext();
		}

		setPVD.CloseRecordset("CCardioPrimaDynForm::ListControlCaricaDefault");
	}

	//

	for (int i = 0; i < m_lNumColonne; i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE);

	//

	for (int iSubItem = 0; iSubItem < m_lNumColonne; iSubItem++)
	{
		if (!m_pArrayStructColonne[iSubItem].bValoreModificabile)
		{
			for (int iItem = 1; iItem < m_ctrlList.GetItemCount(); iItem++)
				m_ctrlList.SetSubItemBkColor(iItem, iSubItem, RGB_SOLALETTURA);
		}
		else
		{
			for (int iItem = 1; iItem < m_ctrlList.GetItemCount(); iItem++)
				m_ctrlList.SetSubItemBkColor(iItem, iSubItem, RGB_MODIFICABILE);
		}
	}
}

void CCardioPrimaDynForm::ListControlDeleteAll()
{
	m_ctrlList.DeleteAllItems();

	m_ctrlList.InsertItem(0, "");
	m_ctrlList.SetItemData(0, 0);

	for (int i = 0; i < m_lNumColonne; i++)
	{
		m_ctrlList.SetItemText(0, i, m_pArrayStructColonne[i].szDescrizione);
		m_ctrlList.SetSubItemBkColor(0, i, RGB_SOLALETTURA);

		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}

short CCardioPrimaDynForm::GetColNumber()
{
	return (short)m_lNumColonne;
}

short CCardioPrimaDynForm::GetRowNumber()
{
	return (short)m_ctrlList.GetItemCount();
}

CString CCardioPrimaDynForm::GetMassimaBpm()
{
	CString sReturn = "";

	m_ctrlEditMassima.GetWindowText(sReturn);
	sReturn += " bpm";

	return sReturn;
}

CString CCardioPrimaDynForm::GetMassimaTitle()
{
	CString sReturn = "";

	m_ctrlStatic00.GetWindowText(sReturn);
	sReturn += ":";

	return sReturn;
}

CString CCardioPrimaDynForm::GetSubmassimaBpm()
{
	CString sReturn = "";

	m_ctrlEditSubmassima.GetWindowText(sReturn);
	sReturn += " bpm";

	return sReturn;
}

CString CCardioPrimaDynForm::GetSubmassimaTitle()
{
	CString sReturn = "";

	m_ctrlStatic01.GetWindowText(sReturn);
	sReturn += ":";

	return sReturn;
}

CString CCardioPrimaDynForm::GetTableCellText(short shCol, short shRow)
{
	CString sReturn = "";

	if ((shCol < GetColNumber()) && (shRow < GetRowNumber()))
		sReturn = m_ctrlList.GetItemText(shRow, shCol);

	return sReturn;
}

CString CCardioPrimaDynForm::GetTitle()
{
	CString sReturn = "";

	m_ctrlStaticTitle.GetWindowTextA(sReturn);
	sReturn.Trim();
	if (!sReturn.IsEmpty())
		sReturn = "\r\n" + sReturn + "\r\n";

	return sReturn;
}
