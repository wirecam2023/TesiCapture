#include "stdafx.h"
#include "Endox.h"
#include "StudioDynForm.h"

#include "CustomDate.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "StudiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CStudioDynForm::CStudioDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
	m_bReadOnly = FALSE;
}

CStudioDynForm::~CStudioDynForm()
{
}

BEGIN_MESSAGE_MAP(CStudioDynForm, CEndoxDynForm)

	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_EDIT_DATA, OnEnChangeEditData)

END_MESSAGE_MAP()

void CStudioDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_studio] == NULL)
	{
		pEsamiView->m_pDynForm[sub_studio] = new CStudioDynForm(CStudioDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_studio] != NULL)
		{
			pEsamiView->m_pDynForm[sub_studio]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_studio]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_studio]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_studio]->CreateChildForm(CStudioDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CStudioDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_01:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_COMBO_STUDIO:
		case IDC_EDIT_STUDIO:
		case IDC_EDIT_DATA:
		case IDC_EDIT_DIFF:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CStudioDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	//

	DDX_Control(pDX, IDC_COMBO_STUDIO, m_ctrlComboStudio);

	DDX_Control(pDX, IDC_EDIT_STUDIO, m_ctrlEditStudio);

	DDX_Control(pDX, IDC_EDIT_DATA, m_ctrlEditData);
	DDX_Control(pDX, IDC_EDIT_DIFF, m_ctrlEditDiff);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);

	//

	m_ctrlEditStudio.SetWindowText("");
	m_ctrlEditDiff.SetWindowText("");

	if (m_bReadOnly)
	{
		if (!pDX->m_bSaveAndValidate)
		{
			// m_ctrlEditStudio //

			if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lIDStudio) && (m_pEsamiView->m_pEsamiSet->m_lIDStudio > 0))
				m_ctrlEditStudio.SetWindowText(CStudiSet().GetDescrizione(m_pEsamiView->m_pEsamiSet->m_lIDStudio));

			// Sandro 18/11/2013 //
			// m_ctrlStaticDiff //

			// if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lDataStudio) && (m_pEsamiView->m_pEsamiSet->m_lDataStudio > 0))
			//	m_ctrlEditDiff.SetWindowText(GetStringEta(m_pEsamiView->m_pEsamiSet->m_lDataStudio, m_pEsamiView->m_pEsamiSet->m_lData, FALSE));
		}
	}
	else
	{
		// m_ctrlComboStudio //
		
		DDX_Studi(pDX, IDC_COMBO_STUDIO, m_pEsamiView->m_pEsamiSet->m_lIDStudio, m_pEsamiView->m_pEsamiSet->GetRecordset());
	}

	DDX_DateMask(pDX, IDC_EDIT_DATA, m_pEsamiView->m_pEsamiSet->m_lDataStudio, m_pEsamiView->m_pEsamiSet->GetRecordset());

	// Sandro 18/11/2013//
	OnEnChangeEditData();
}

BOOL CStudioDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_01, CSize(0, 50), CSize(100, 50));
	AddAnchor(IDC_COMBO_STUDIO, CSize(0, 50), CSize(100, 50));
	AddAnchor(IDC_EDIT_STUDIO, CSize(0, 50), CSize(100, 50));
	AddAnchor(IDC_EDIT_DATA, CSize(0, 50), CSize(50, 50));
	AddAnchor(IDC_EDIT_DIFF, CSize(50, 50), CSize(100, 50));

	GetDlgItem(IDC_STATIC_01)->SetFont(&theApp.m_fontBold);

	RiempiComboStudio();
	m_ctrlEditData.SetEditMask("00/00/0000", "__/__/____");

	theApp.LocalizeDialog(this, CStudioDynForm::IDD, "StudioDynForm");
	return bReturn;
}

LRESULT CStudioDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CStudioDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CStudioDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_bReadOnly = (BOOL)wParam;

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		m_ctrlComboStudio.ShowWindow(SW_SHOW);
		m_ctrlEditStudio.ShowWindow(SW_HIDE);

		m_ctrlEditData.ShowWindow(SW_HIDE);

		m_ctrlEditDiff.ShowWindow(SW_HIDE);
	}
	else
	{
		m_ctrlComboStudio.ShowWindow(m_bReadOnly ? SW_HIDE : SW_SHOW);
		m_ctrlEditStudio.ShowWindow(m_bReadOnly ? SW_SHOW : SW_HIDE);

		m_ctrlEditData.ShowWindow(SW_SHOW);
		m_ctrlEditData.SetReadOnly(m_bReadOnly);

		// m_ctrlEditDiff.ShowWindow(m_bReadOnly ? SW_/SHOW : SW_HIDE);	// Sandro 18/11/2013 //
		m_ctrlEditDiff.ShowWindow(SW_SHOW);								// Sandro 18/11/2013 //
	}

	return 1;
}

LRESULT CStudioDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CStudioDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CStudioDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (m_pEsamiView->m_pEsamiSet->m_lIDStudio >= 0)
		ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, (long*)&m_pEsamiView->m_pEsamiSet->m_lIDStudio, "EEsami.IDStudio", 0, "AND");

	return 1;
}

long CStudioDynForm::GetContenuto()
{
	return sub_studio;
}

BOOL CStudioDynForm::CampoObbligatorioValido()
{
	/*
	switch(m_pEsamiView->m_pEsamiSet->m_iAllergie)
	{
		case 0:
		{
			return TRUE;
			break;
		}
		case 1:
		{
			if (m_pEsamiView->m_pEsamiSet->m_sDescrizioneAllergie.GetLength() > 0)
				return TRUE;
			break;
		}
	}
	*/

	return FALSE;
}

void CStudioDynForm::RiempiComboStudio()
{
	m_ctrlComboStudio.SetRedraw(FALSE);
	m_ctrlComboStudio.ResetContent();

	int nIndex = 1;

	m_ctrlComboStudio.InsertString(0, "");
	m_ctrlComboStudio.SetItemData(0, 0);

	CStudiSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CStudioDynForm::RiempiComboStudio"))
	{
		while(!setTemp.IsEOF())
		{
			m_ctrlComboStudio.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlComboStudio.SetItemData(nIndex, setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CStudioDynForm::RiempiComboStudio");
	}

	m_ctrlComboStudio.SetRedraw(TRUE);
}

void CStudioDynForm::OnEnChangeEditData()
{
	CString sTemp;
	m_ctrlEditData.GetWindowText(sTemp);

	long lTemp = CCustomDate().SetDate(sTemp); 
	
	if (lTemp > 0)
		m_ctrlEditDiff.SetWindowText(GetStringEta(lTemp, m_pEsamiView->m_pEsamiSet->m_lData, FormatoEta::AnnoMeseGiornoAbbreviato)); //Gabriel BUG 6225 - Lista DO
	else
		m_ctrlEditDiff.SetWindowText("");
}
