#include "stdafx.h"
#include "Endox.h"

#include "EndoxMenu.h"
#include "EsamiDoc.h"
#include "EsamiView.h"

#include "IntegrazioniVitalSignConfigForm.h"
#include "IntegrazioniConfigurazioneModDlg.h"
#include "VitalSignDispositiviSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CIntegrazioniVitalSignConfigForm, CResizableDialog)
	ON_WM_CTLCOLOR()
	
	ON_BN_CLICKED(IDC_CHK_ATTIVA, &CIntegrazioniVitalSignConfigForm::OnBnClickedChkAttiva)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DISPOSITIVI, &CIntegrazioniVitalSignConfigForm::OnNMRClickListDispositivi)

	ON_COMMAND(ID_VS_NUOVO, OnNuovoDispositivo)
	ON_COMMAND(ID_VS_ELIMINA, OnEliminaDispositivo)

END_MESSAGE_MAP()

HBRUSH CIntegrazioniVitalSignConfigForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CResizableDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	//pDC->SetBkColor(theApp.m_color[0]);	

	return hBrush;
}


CIntegrazioniVitalSignConfigForm::CIntegrazioniVitalSignConfigForm(CWnd* pParent, CIntegrazioniConfigurazioneModDlg* configDlg)
	: CResizableDialog(CIntegrazioniVitalSignConfigForm::IDD, pParent), m_ctrlListDispositivi(TRUE, FALSE, FALSE)
{
	m_pConfigDlg = configDlg;

	CResizableDialog::Create(CIntegrazioniVitalSignConfigForm::IDD, pParent->GetParent());

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);
}

CIntegrazioniVitalSignConfigForm::~CIntegrazioniVitalSignConfigForm()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

void CIntegrazioniVitalSignConfigForm::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);

	DDX_Control(pDX, IDC_CHK_ATTIVA, m_ctrlBtnAttiva);
	DDX_Control(pDX, IDC_EDIT_WEBSERVICE, m_ctrlEdtWebservice);
	DDX_Control(pDX, IDC_LIST_DISPOSITIVI, m_ctrlListDispositivi);
	
}

BOOL CIntegrazioniVitalSignConfigForm::OnInitDialog()
{
	CResizableDialog::OnInitDialog();	

	AddAnchor(IDC_CHK_ATTIVA, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_1, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_EDIT_WEBSERVICE, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_2, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_LIST_DISPOSITIVI, CSize(0, 0), CSize(100, 100));

	theApp.LocalizeDialog(this, CIntegrazioniVitalSignConfigForm::IDD, "IntegrazioniVitalSignConfigForm");	

	m_ctrlListDispositivi.SetExtendedStyle(m_ctrlListDispositivi.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlListDispositivi.InsertColumn(0, "Descrizione", LVCFMT_LEFT, 200);
	m_ctrlListDispositivi.InsertColumn(1, "Codice identificativo", LVCFMT_LEFT, 200);	
	m_ctrlListDispositivi.InsertColumn(2, "Default", LVCFMT_LEFT, 200);

	Load();

	return TRUE;
}

void CIntegrazioniVitalSignConfigForm::Load()
{	
	m_ctrlBtnAttiva.SetCheck(theApp.m_bVitalSignIntegrazioneAttiva);
	m_ctrlEdtWebservice.SetWindowText(theApp.m_sVitalSignWebServiceEndpoint);

	VerifyActive();

	RiempiListaDispositivi();
}

void CIntegrazioniVitalSignConfigForm::Save()
{	
	theApp.m_bVitalSignIntegrazioneAttiva = m_ctrlBtnAttiva.GetCheck();
	m_ctrlEdtWebservice.GetWindowText(theApp.m_sVitalSignWebServiceEndpoint);

	//Salva dispositivi
	//Primo giro, elimino dal db i dispositivi che non ho nella lista
	CVitalSignDispositiviSet set;
	if (set.OpenRecordset("CIntegrazioniVitalSignConfigForm::Save"))
	{
		while (!set.IsEOF())
		{
			BOOL bFound = false;
			for (int i = 0; i < m_ctrlListDispositivi.GetItemCount(); i++)
			{
				if (m_ctrlListDispositivi.GetItemText(i, 1) == set.m_sCodiceIdentificativo)
				{
					bFound = true;
					break;
				}
			}

			if (!bFound)
				set.DeleteRecordset("CIntegrazioniVitalSignConfigForm::Save");

			set.MoveNext();
		}

		set.CloseRecordset("CIntegrazioniVitalSignConfigForm::Save");
	}

	//Secondo giro, aggiungo quelli che ho sulla lista ma non sul db
	for (int i = 0; i < m_ctrlListDispositivi.GetItemCount(); i++)
	{
		CString filter = "codiceIdentificativo = '" + m_ctrlListDispositivi.GetItemText(i, 1) + "'";
		set.SetOpenFilter(filter);

		if (set.OpenRecordset("CIntegrazioniVitalSignConfigForm::Save"))
		{
			if (set.IsEOF())
			{
				set.AddNewRecordset("CIntegrazioniVitalSignConfigForm::Save");
				set.m_sDescrizione = m_ctrlListDispositivi.GetItemText(i, 0);
				set.m_sCodiceIdentificativo = m_ctrlListDispositivi.GetItemText(i, 1);
				set.UpdateRecordset("CIntegrazioniVitalSignConfigForm::Save");
			}
			else
			{
				set.EditRecordset("CIntegrazioniVitalSignConfigForm::Save");
				set.m_sDescrizione = m_ctrlListDispositivi.GetItemText(i, 0);
				set.UpdateRecordset("CIntegrazioniVitalSignConfigForm::Save");
			}

			set.CloseRecordset("CIntegrazioniVitalSignConfigForm::Save");
		}	

		if (m_ctrlListDispositivi.GetSubItemData(i, 2) == 1)
			theApp.m_sCodiceDispositivoDefault = m_ctrlListDispositivi.GetItemText(i, 1);
	}

	//salvataggio
	CEsamiDoc *doc = (CEsamiDoc*)m_pConfigDlg->m_pEsamiView->GetDocument();
	doc->OnSalvaConfigurazioneIntegrazioneVitalSign();
}

void CIntegrazioniVitalSignConfigForm::OnBnClickedChkAttiva()
{
	VerifyActive();
}

BOOL CIntegrazioniVitalSignConfigForm::VerifyActive()
{
	BOOL bActive = FALSE;

	if (m_ctrlBtnAttiva.GetCheck() == BST_CHECKED)
		bActive = TRUE;

	SetActive(bActive);

	return bActive;
}

void CIntegrazioniVitalSignConfigForm::SetActive(BOOL bActive)
{
	m_ctrlStatic1.EnableWindow(bActive);
	m_ctrlEdtWebservice.EnableWindow(bActive);
	m_ctrlStatic2.EnableWindow(bActive);
	m_ctrlListDispositivi.EnableWindow(bActive);
}

void CIntegrazioniVitalSignConfigForm::OnNMRClickListDispositivi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		
	CPoint point;
	GetCursorPos(&point);

	CEndoxMenu menu;
	menu.LoadMenu(IDR_MENU_VS_DISPOSITIVI);

	if (m_ctrlListDispositivi.GetSelectedCount() == 0)
		menu.DeleteMenu(ID_VS_ELIMINA, MF_BYCOMMAND);

	CEndoxMenu* pMenu = (CEndoxMenu*)menu.GetSubMenu(0);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	

	*pResult = 0;
}

void CIntegrazioniVitalSignConfigForm::RiempiListaDispositivi()
{
	m_ctrlListDispositivi.SetRedraw(FALSE);
	m_ctrlListDispositivi.DeleteAllItems();

	int i = 3;

	CVitalSignDispositiviSet set;
	if (set.OpenRecordset("CIntegrazioniVitalSignConfigForm::RiempiListaDispositivi"))
	{
		while (!set.IsEOF())
		{
			int item = m_ctrlListDispositivi.InsertItem(m_ctrlListDispositivi.GetItemCount(), set.m_sDescrizione);
			m_ctrlListDispositivi.SetItemText(item, 1, set.m_sCodiceIdentificativo);

			m_ctrlListDispositivi.SetSubItemEdit(item, 0);
			m_ctrlListDispositivi.SetSubItemEdit(item, 1);
			m_ctrlListDispositivi.SetSubItemCheck(item, 2);

			if (set.m_sCodiceIdentificativo == theApp.m_sCodiceDispositivoDefault)
				m_ctrlListDispositivi.SetSubItemData(item, 2, 1);
			else
				m_ctrlListDispositivi.SetSubItemData(item, 2, 0);

			set.MoveNext();
		}

		set.CloseRecordset("CIntegrazioniVitalSignConfigForm::RiempiListaDispositivi");
	}

	for (int h = 0; h < i; h++)
		m_ctrlListDispositivi.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListDispositivi.SetRedraw(TRUE);
	
}

void CIntegrazioniVitalSignConfigForm::OnNuovoDispositivo()
{
	int item = m_ctrlListDispositivi.InsertItem(m_ctrlListDispositivi.GetItemCount(), "Nuovo dispositivo");
	m_ctrlListDispositivi.SetSubItemEdit(item, 0);
	m_ctrlListDispositivi.SetSubItemEdit(item, 1);
	m_ctrlListDispositivi.SetSubItemCheck(item, 2);
}

void CIntegrazioniVitalSignConfigForm::OnEliminaDispositivo()
{	
	int deleted = 0;
	POSITION pos = m_ctrlListDispositivi.GetFirstSelectedItemPosition();
	while (pos)
	{
		int item = m_ctrlListDispositivi.GetNextSelectedItem(pos);		
		m_ctrlListDispositivi.DeleteItem(item-deleted);

		deleted++;
	}	

}