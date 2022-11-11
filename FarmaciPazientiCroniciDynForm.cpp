#include "stdafx.h"
#include "Endox.h"
#include "FarmaciPazientiCroniciDynForm.h"

#include "CronicitaPazienteDlg.h"
#include "EsamiFarmaciCroniciSet.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "FarmaciPazientiCroniciSet.h"
#include "MalattieCronicheCampiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFarmaciPazientiCroniciDynForm::CFarmaciPazientiCroniciDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView),
	m_ctrlListFarmaci(FALSE, TRUE, FALSE)
{
	m_bReadOnly = FALSE;
}

CFarmaciPazientiCroniciDynForm::~CFarmaciPazientiCroniciDynForm()
{
}

BEGIN_MESSAGE_MAP(CFarmaciPazientiCroniciDynForm, CEndoxDynForm)

	ON_WM_CTLCOLOR()
	ON_WM_SIZE()

END_MESSAGE_MAP()

void CFarmaciPazientiCroniciDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_pazienticronici_terapia] == NULL)
	{
		pEsamiView->m_pDynForm[sub_pazienticronici_terapia] = new CFarmaciPazientiCroniciDynForm(CFarmaciPazientiCroniciDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_pazienticronici_terapia] != NULL)
		{
			pEsamiView->m_pDynForm[sub_pazienticronici_terapia]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_pazienticronici_terapia]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_pazienticronici_terapia]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_pazienticronici_terapia]->CreateChildForm(CFarmaciPazientiCroniciDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CFarmaciPazientiCroniciDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_TITOLO:
		case IDC_LIST_FARMACI:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CFarmaciPazientiCroniciDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_TITOLO, m_ctrlStaticTitolo);
	DDX_Control(pDX, IDC_LIST_FARMACI, m_ctrlListFarmaci);
}

BOOL CFarmaciPazientiCroniciDynForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_TITOLO, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_LIST_FARMACI, CSize(0, 0), CSize(100, 100));

	//

	tagLISTCOMBO tagTemp;
	
	m_slTerapia.RemoveAll();

	tagTemp.lID = 0;
	tagTemp.strName = "";
	m_slTerapia.AddTail(tagTemp);

	tagTemp.lID = 1;
	tagTemp.strName = theApp.GetMessageString(IDS_FARMACO_INIZIO);
	m_slTerapia.AddTail(tagTemp);

	tagTemp.lID = 2;
	tagTemp.strName = theApp.GetMessageString(IDS_FARMACO_CONTINUA);
	m_slTerapia.AddTail(tagTemp);

	tagTemp.lID = 3;
	tagTemp.strName = theApp.GetMessageString(IDS_FARMACO_FINE);
	m_slTerapia.AddTail(tagTemp);

	//

	m_ctrlListFarmaci.SetExtendedStyle(m_ctrlListFarmaci.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListFarmaci.InsertColumn(0, "");
	m_ctrlListFarmaci.InsertColumn(1, "");
	m_ctrlListFarmaci.InsertColumn(2, "");

	//

	theApp.LocalizeDialog(this, CFarmaciPazientiCroniciDynForm::IDD, "FarmaciPazientiCroniciDynForm");
	return TRUE;
}

void CFarmaciPazientiCroniciDynForm::OnSize(UINT nType, int cx, int cy)
{
	CEndoxDynForm::OnSize(nType, cx, cy);

	if (IsWindow(m_ctrlListFarmaci))
	{
		m_ctrlListFarmaci.SetRedraw(FALSE);
		m_ctrlListFarmaci.SetColumnWidth(0, 0);
		m_ctrlListFarmaci.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListFarmaci.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListFarmaci.SetRedraw(TRUE);
	}
}

LRESULT CFarmaciPazientiCroniciDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CFarmaciPazientiCroniciDynForm::OnFormClone(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(NULL, NULL);

	//

	long lIDEsameDaClonare = CEsamiSet().GetLastPatientExam(m_pEsamiView->m_pPazientiSet->m_lContatore);

	//

	CString strFilter;
	strFilter.Format("IDEsame=%li", lIDEsameDaClonare);

	CEsamiFarmaciCroniciSet setTemp;
	setTemp.SetOpenFilter(strFilter);

	if (setTemp.OpenRecordset("CFarmaciPazientiCroniciDynForm::OnFormLoad"))
	{
		while(!setTemp.IsEOF())
		{
			for(int i = 0; i < m_ctrlListFarmaci.GetItemCount(); i++)
			{
				if (m_ctrlListFarmaci.GetItemData(i) == setTemp.m_lIDFarmaco)
				{
					switch(setTemp.m_lFase)
					{
						case FARMACO_NIENTE:
						{
							break;
						}
						case FARMACO_INIZIO:
						{
							m_ctrlListFarmaci.SetItemText(i, 2, theApp.GetMessageString(IDS_FARMACO_CONTINUA));
							break;
						}
						case FARMACO_CONTINUA:
						{
							m_ctrlListFarmaci.SetItemText(i, 2, theApp.GetMessageString(IDS_FARMACO_CONTINUA));
							break;
						}
						case FARMACO_FINE:
						{
							break;
						}
						default:
						{
							ASSERT(FALSE);
							break;
						}
					}
				}
			}

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CFarmaciPazientiCroniciDynForm::OnFormLoad");
	}

	return 1;
}

LRESULT CFarmaciPazientiCroniciDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(NULL, NULL);

	CString strFilter;
	strFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	CEsamiFarmaciCroniciSet setTemp;
	setTemp.SetOpenFilter(strFilter);

	if (setTemp.OpenRecordset("CFarmaciPazientiCroniciDynForm::OnFormLoad"))
	{
		while(!setTemp.IsEOF())
		{
			for(int i = 0; i < m_ctrlListFarmaci.GetItemCount(); i++)
			{
				if (m_ctrlListFarmaci.GetItemData(i) == setTemp.m_lIDFarmaco)
				{
					switch(setTemp.m_lFase)
					{
						case FARMACO_NIENTE:
						{
							break;
						}
						case FARMACO_INIZIO:
						{
							m_ctrlListFarmaci.SetItemText(i, 2, theApp.GetMessageString(IDS_FARMACO_INIZIO));
							break;
						}
						case FARMACO_CONTINUA:
						{
							m_ctrlListFarmaci.SetItemText(i, 2, theApp.GetMessageString(IDS_FARMACO_CONTINUA));
							break;
						}
						case FARMACO_FINE:
						{
							m_ctrlListFarmaci.SetItemText(i, 2, theApp.GetMessageString(IDS_FARMACO_FINE));
							break;
						}
						default:
						{
							ASSERT(FALSE);
							break;
						}
					}
				}
			}

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CFarmaciPazientiCroniciDynForm::OnFormLoad");
	}

	return 1;
}

LRESULT CFarmaciPazientiCroniciDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_bReadOnly = (BOOL)wParam;

	//

	m_ctrlListFarmaci.EnableWindow(!m_bReadOnly);

	//

	return 1;
}

LRESULT CFarmaciPazientiCroniciDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	/*
	for(int i = 0; i < m_ctrlListFarmaci.GetItemCount(); i++)
		m_ctrlListFarmaci.SetItemText(i, 2, "");
	*/

	m_ctrlListFarmaci.SetRedraw(FALSE);
	m_ctrlListFarmaci.DeleteAllItems();

	CString sFilter = "";
	if (!m_pEsamiView->m_pPazientiSet->IsFieldNull(&m_pEsamiView->m_pPazientiSet->m_lIDMalattiaCronica) && (m_pEsamiView->m_pPazientiSet->m_lIDMalattiaCronica > 0))
	{
		sFilter.Format("IDMalattia=%li", m_pEsamiView->m_pPazientiSet->m_lIDMalattiaCronica);
	}
	else
	{
		if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lIDMalattiaCronica) && (m_pEsamiView->m_pEsamiSet->m_lIDMalattiaCronica > 0))
			sFilter.Format("IDMalattia=%li", m_pEsamiView->m_pEsamiSet->m_lIDMalattiaCronica);
	}
	sFilter.Trim();

	if (!sFilter.IsEmpty())
	{
		CMalattieCronicheCampiSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		setTemp.SetSortRecord("Ordine, ID");

		if (setTemp.OpenRecordset("CFarmaciPazientiCroniciDynForm::OnInitDialog"))
		{
			int nIndex = 0;

			while(!setTemp.IsEOF())
			{
				if (setTemp.m_lTipoCampo == TIPOCAMPO_FARMACO)
				{
					m_ctrlListFarmaci.InsertItem(nIndex, "");
					m_ctrlListFarmaci.SetItemData(nIndex, setTemp.m_lIDCampo);

					m_ctrlListFarmaci.SetItemText(nIndex, 1, CFarmaciPazientiCroniciSet().GetDescrizione(setTemp.m_lIDCampo));

					m_ctrlListFarmaci.SetSubItemCombo(nIndex, 2, m_slTerapia);

					nIndex++;
				}

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CFarmaciPazientiCroniciDynForm::OnInitDialog");
		}
	}

	m_ctrlListFarmaci.SetColumnWidth(0, 0);
	m_ctrlListFarmaci.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListFarmaci.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListFarmaci.SetRedraw(TRUE);

	return 1;
}

LRESULT CFarmaciPazientiCroniciDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CEsamiFarmaciCroniciSet().DelAllRows(m_pEsamiView->m_pEsamiSet->m_lContatore);

	for(int i = 0; i < m_ctrlListFarmaci.GetItemCount(); i++)
	{
		CString sTemp = m_ctrlListFarmaci.GetItemText(i, 2);

		if (sTemp == theApp.GetMessageString(IDS_FARMACO_INIZIO))
		{
			CEsamiFarmaciCroniciSet().AddRow(m_pEsamiView->m_pEsamiSet->m_lContatore, m_ctrlListFarmaci.GetItemData(i), FARMACO_INIZIO);
		}
		else if (sTemp == theApp.GetMessageString(IDS_FARMACO_CONTINUA))
		{
			CEsamiFarmaciCroniciSet().AddRow(m_pEsamiView->m_pEsamiSet->m_lContatore, m_ctrlListFarmaci.GetItemData(i), FARMACO_CONTINUA);
		}
		else if (sTemp == theApp.GetMessageString(IDS_FARMACO_FINE))
		{
			CEsamiFarmaciCroniciSet().AddRow(m_pEsamiView->m_pEsamiSet->m_lContatore, m_ctrlListFarmaci.GetItemData(i), FARMACO_FINE);
		}
	}

	return 1;
}

LRESULT CFarmaciPazientiCroniciDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
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

long CFarmaciPazientiCroniciDynForm::GetContenuto()
{
	return sub_pazienticronici_terapia;
}

BOOL CFarmaciPazientiCroniciDynForm::CampoObbligatorioValido()
{
	return TRUE;
}
