#include "stdafx.h"
#include "Endox.h"
#include "EditDynFormDataOra.h"

#include "Common.h"
#include "CustomDate.h"
#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra000;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra001;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra002;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra003;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra004;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra005;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra006;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra007;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra008;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra009;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra010;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra011;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra012;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra013;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra014;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra015;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra016;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra017;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra018;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataOra019;
CExtDateEdit CEditDynFormDataOra::m_ctrlDataRefertoIstologico;

CEditDynFormDataOra::CEditDynFormDataOra(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
: CEndoxDynForm(CEditDynFormDataOra::IDD, pParent, pEsamiView)
{
	m_lContenuto = lContenuto;
}

CEditDynFormDataOra::~CEditDynFormDataOra()
{
}

BEGIN_MESSAGE_MAP(CEditDynFormDataOra, CEndoxDynForm)

	ON_BN_CLICKED(IDC_BUTTON, OnBnClickedButton)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

void CEditDynFormDataOra::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new CEditDynFormDataOra(NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(CEditDynFormDataOra::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CEditDynFormDataOra::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_TEXT:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_EDIT:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CEditDynFormDataOra::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON, m_ctrlBtnButton);

	switch(m_lContenuto)
	{
		case edt_liberodataora000:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra000);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra000.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[0], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra000, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora001:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra001);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra001.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[1], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra001, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora002:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra002);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra002.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[2], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra002, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora003:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra003);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra003.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[3], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra003, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora004:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra004);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra004.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[4], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra004, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora005:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra005);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra005.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[5], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra005, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora006:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra006);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra006.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[6], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra006, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora007:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra007);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra007.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[7], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra007, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora008:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra008);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra008.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[8], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra008, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora009:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra009);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra009.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[9], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra009, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora010:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra010);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra010.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[10], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra010, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora011:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra011);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra011.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[11], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra011, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora012:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra012);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra012.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[12], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra012, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora013:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra013);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra013.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[13], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra013, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora014:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra014);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra014.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[14], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra014, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora015:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra015);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra015.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[15], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra015, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora016:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra016);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra016.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[16], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra016, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora017:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra017);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra017.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[17], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra017, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora018:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra018);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra018.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[18], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra018, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_liberodataora019:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataOra019);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataOra019.m_strRicercaView);
			else
				DDX_DateTimePersMask(pDX, IDC_EDIT, theApp.m_iRadioDate[19], m_pEsamiView->m_pEsamiSet->m_setEP.m_lDataOra019, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_data_referto_istologico:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataRefertoIstologico);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataRefertoIstologico.m_strRicercaView);
			else
				DDX_DateMask(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lDataRefertoIstologico, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
	}
}

BOOL CEditDynFormDataOra::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_TEXT)->GetSafeHwnd(), CSize(0, 50), CSize(100, 50));
	AddAnchor(GetDlgItem(IDC_EDIT)->GetSafeHwnd(), CSize(0, 50), CSize(100, 50));
	AddAnchor(GetDlgItem(IDC_BUTTON)->GetSafeHwnd(), CSize(100, 50), CSize(100, 50));

	switch(m_lContenuto)
	{
		case edt_liberodataora000:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[0]);
			m_ctrlDataOra000.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[0], theApp.m_iRadioDate[0]);
			break;
		}
		case edt_liberodataora001:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[1]);
			m_ctrlDataOra001.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[1], theApp.m_iRadioDate[1]);
			break;
		}
		case edt_liberodataora002:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[2]);
			m_ctrlDataOra002.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[2], theApp.m_iRadioDate[2]);
			break;
		}
		case edt_liberodataora003:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[3]);
			m_ctrlDataOra003.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[3], theApp.m_iRadioDate[3]);
			break;
		}
		case edt_liberodataora004:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[4]);
			m_ctrlDataOra004.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[4], theApp.m_iRadioDate[4]);
			break;
		}
		case edt_liberodataora005:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[5]);
			m_ctrlDataOra005.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[5], theApp.m_iRadioDate[5]);
			break;
		}
		case edt_liberodataora006:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[6]);
			m_ctrlDataOra006.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[6], theApp.m_iRadioDate[6]);
			break;
		}
		case edt_liberodataora007:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[7]);
			m_ctrlDataOra007.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[7], theApp.m_iRadioDate[7]);
			break;
		}
		case edt_liberodataora008:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[8]);
			m_ctrlDataOra008.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[8], theApp.m_iRadioDate[8]);
			break;
		}
		case edt_liberodataora009:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[9]);
			m_ctrlDataOra009.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[9], theApp.m_iRadioDate[9]);
			break;
		}
		case edt_liberodataora010:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[10]);
			m_ctrlDataOra010.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[10], theApp.m_iRadioDate[10]);
			break;
		}
		case edt_liberodataora011:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[11]);
			m_ctrlDataOra011.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[11], theApp.m_iRadioDate[11]);
			break;
		}
		case edt_liberodataora012:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[12]);
			m_ctrlDataOra012.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[12], theApp.m_iRadioDate[12]);
			break;
		}
		case edt_liberodataora013:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[13]);
			m_ctrlDataOra013.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[13], theApp.m_iRadioDate[13]);
			break;
		}
		case edt_liberodataora014:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[14]);
			m_ctrlDataOra014.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[14], theApp.m_iRadioDate[14]);
			break;
		}
		case edt_liberodataora015:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[15]);
			m_ctrlDataOra015.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[15], theApp.m_iRadioDate[15]);
			break;
		}
		case edt_liberodataora016:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[16]);
			m_ctrlDataOra016.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[16], theApp.m_iRadioDate[16]);
			break;
		}
		case edt_liberodataora017:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[17]);
			m_ctrlDataOra017.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[17], theApp.m_iRadioDate[17]);
			break;
		}
		case edt_liberodataora018:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[18]);
			m_ctrlDataOra018.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[18], theApp.m_iRadioDate[18]);
			break;
		}
		case edt_liberodataora019:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelDate[19]);
			m_ctrlDataOra019.SetParam(this, m_pEsamiView, theApp.m_sLabelDate[19], theApp.m_iRadioDate[19]);
			break;
		}
		case edt_data_referto_istologico:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_502));
			m_ctrlDataRefertoIstologico.SetParam(this, m_pEsamiView, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_502), SOLO_DATA);
			break;
		}
	}

	return bReturn;
}

LRESULT CEditDynFormDataOra::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CEditDynFormDataOra::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CEditDynFormDataOra::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	switch(m_lContenuto)
	{
		case edt_liberodataora000:
		case edt_liberodataora001:
		case edt_liberodataora002:
		case edt_liberodataora003:
		case edt_liberodataora004:
		case edt_liberodataora005:
		case edt_liberodataora006:
		case edt_liberodataora007:
		case edt_liberodataora008:
		case edt_liberodataora009:
		case edt_liberodataora010:
		case edt_liberodataora011:
		case edt_liberodataora012:
		case edt_liberodataora013:
		case edt_liberodataora014:
		case edt_liberodataora015:
		case edt_liberodataora016:
		case edt_liberodataora017:
		case edt_liberodataora018:
		case edt_liberodataora019:
		case edt_data_referto_istologico:
		{
			SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, wParam, lParam);
			m_ctrlBtnButton.ShowWindow((BOOL)wParam ? SW_HIDE : SW_SHOW);
			break;
		}
	}

	return 1;
}

LRESULT CEditDynFormDataOra::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	switch(m_lContenuto)
	{
		case edt_liberodataora000:
		{
			m_ctrlDataOra000.m_strRicerca = "";
			m_ctrlDataOra000.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora001:
		{
			m_ctrlDataOra001.m_strRicerca = "";
			m_ctrlDataOra001.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora002:
		{
			m_ctrlDataOra002.m_strRicerca = "";
			m_ctrlDataOra002.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora003:
		{
			m_ctrlDataOra003.m_strRicerca = "";
			m_ctrlDataOra003.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora004:
		{
			m_ctrlDataOra004.m_strRicerca = "";
			m_ctrlDataOra004.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora005:
		{
			m_ctrlDataOra005.m_strRicerca = "";
			m_ctrlDataOra005.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora006:
		{
			m_ctrlDataOra006.m_strRicerca = "";
			m_ctrlDataOra006.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora007:
		{
			m_ctrlDataOra007.m_strRicerca = "";
			m_ctrlDataOra007.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora008:
		{
			m_ctrlDataOra008.m_strRicerca = "";
			m_ctrlDataOra008.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora009:
		{
			m_ctrlDataOra009.m_strRicerca = "";
			m_ctrlDataOra009.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora010:
		{
			m_ctrlDataOra010.m_strRicerca = "";
			m_ctrlDataOra010.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora011:
		{
			m_ctrlDataOra011.m_strRicerca = "";
			m_ctrlDataOra011.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora012:
		{
			m_ctrlDataOra012.m_strRicerca = "";
			m_ctrlDataOra012.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora013:
		{
			m_ctrlDataOra013.m_strRicerca = "";
			m_ctrlDataOra013.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora014:
		{
			m_ctrlDataOra014.m_strRicerca = "";
			m_ctrlDataOra014.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora015:
		{
			m_ctrlDataOra015.m_strRicerca = "";
			m_ctrlDataOra015.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora016:
		{
			m_ctrlDataOra016.m_strRicerca = "";
			m_ctrlDataOra016.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora017:
		{
			m_ctrlDataOra017.m_strRicerca = "";
			m_ctrlDataOra017.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora018:
		{
			m_ctrlDataOra018.m_strRicerca = "";
			m_ctrlDataOra018.m_strRicercaView = "";
			break;
		}
		case edt_liberodataora019:
		{
			m_ctrlDataOra019.m_strRicerca = "";
			m_ctrlDataOra019.m_strRicercaView = "";
			break;
		}
		case edt_data_referto_istologico:
		{
			m_ctrlDataRefertoIstologico.m_strRicerca = "";
			m_ctrlDataRefertoIstologico.m_strRicercaView = "";
			break;
		}
	}

	return 1;
}

LRESULT CEditDynFormDataOra::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	switch(m_lContenuto)
	{
		case edt_liberodataora000:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra000.m_strRicerca, "EEsamiPersonalizzabili.DataOra000", FALSE, TRUE);
			break;
		}
		case edt_liberodataora001:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra001.m_strRicerca, "EEsamiPersonalizzabili.DataOra001", FALSE, TRUE);
			break;
		}
		case edt_liberodataora002:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra002.m_strRicerca, "EEsamiPersonalizzabili.DataOra002", FALSE, TRUE);
			break;
		}
		case edt_liberodataora003:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra003.m_strRicerca, "EEsamiPersonalizzabili.DataOra003", FALSE, TRUE);
			break;
		}
		case edt_liberodataora004:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra004.m_strRicerca, "EEsamiPersonalizzabili.DataOra004", FALSE, TRUE);
			break;
		}
		case edt_liberodataora005:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra005.m_strRicerca, "EEsamiPersonalizzabili.DataOra005", FALSE, TRUE);
			break;
		}
		case edt_liberodataora006:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra006.m_strRicerca, "EEsamiPersonalizzabili.DataOra006", FALSE, TRUE);
			break;
		}
		case edt_liberodataora007:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra007.m_strRicerca, "EEsamiPersonalizzabili.DataOra007", FALSE, TRUE);
			break;
		}
		case edt_liberodataora008:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra008.m_strRicerca, "EEsamiPersonalizzabili.DataOra008", FALSE, TRUE);
			break;
		}
		case edt_liberodataora009:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra009.m_strRicerca, "EEsamiPersonalizzabili.DataOra009", FALSE, TRUE);
			break;
		}
		case edt_liberodataora010:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra010.m_strRicerca, "EEsamiPersonalizzabili.DataOra010", FALSE, TRUE);
			break;
		}
		case edt_liberodataora011:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra011.m_strRicerca, "EEsamiPersonalizzabili.DataOra011", FALSE, TRUE);
			break;
		}
		case edt_liberodataora012:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra012.m_strRicerca, "EEsamiPersonalizzabili.DataOra012", FALSE, TRUE);
			break;
		}
		case edt_liberodataora013:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra013.m_strRicerca, "EEsamiPersonalizzabili.DataOra013", FALSE, TRUE);
			break;
		}
		case edt_liberodataora014:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra014.m_strRicerca, "EEsamiPersonalizzabili.DataOra014", FALSE, TRUE);
			break;
		}
		case edt_liberodataora015:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra015.m_strRicerca, "EEsamiPersonalizzabili.DataOra015", FALSE, TRUE);
			break;
		}
		case edt_liberodataora016:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra016.m_strRicerca, "EEsamiPersonalizzabili.DataOra016", FALSE, TRUE);
			break;
		}
		case edt_liberodataora017:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra017.m_strRicerca, "EEsamiPersonalizzabili.DataOra017", FALSE, TRUE);
			break;
		}
		case edt_liberodataora018:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra018.m_strRicerca, "EEsamiPersonalizzabili.DataOra018", FALSE, TRUE);
			break;
		}
		case edt_liberodataora019:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataOra019.m_strRicerca, "EEsamiPersonalizzabili.DataOra019", FALSE, TRUE);
			break;
		}
		case edt_data_referto_istologico:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataRefertoIstologico.m_strRicerca, "EEsami.DataRefertoIstologico", FALSE, TRUE);
			break;
		}
	}

	return 1;
}

long CEditDynFormDataOra::GetContenuto()
{
	return m_lContenuto;
}

BOOL CEditDynFormDataOra::CampoObbligatorioValido()
{
	CString strEdit;
	GetDlgItemText(IDC_EDIT, strEdit);

	if (!strEdit.IsEmpty())
		return TRUE;

	return FALSE;
}

void CEditDynFormDataOra::OnBnClickedButton()
{
	m_ctrlBtnButton.SetCheck(BST_UNCHECKED);

	switch (m_lContenuto)
	{
		case edt_data_referto_istologico:
		{
			SetDlgItemText(IDC_EDIT, CCustomDate(TRUE, TRUE).GetDateForEdit(SOLO_DATA));
			break;
		}
		default:
		{
			int iIndex = m_lContenuto - edt_liberodataora000;
			ASSERT((iIndex >= 0) && (iIndex < NUM_LABEL_DATAORA));

			SetDlgItemText(IDC_EDIT, CCustomDate(TRUE, TRUE).GetDateForEdit(theApp.m_iRadioDate[iIndex]));
			break;
		}
	}
	
	
}
