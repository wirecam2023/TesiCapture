#include "stdafx.h"
#include "Endox.h"
#include "EditDynFormCodiceDescrizione.h"

#include "EsamiView.h"
#include "MediciSet.h"
#include "QueryFormListDlg.h"
#include "VistaMediciSedeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEditDynFormCodiceDescrizione::CEditDynFormCodiceDescrizione(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
: CEndoxDynForm(CEditDynFormCodiceDescrizione::IDD, pParent, pEsamiView)
{
	m_lContenuto = lContenuto;

	m_bResetting1 = FALSE;
	m_bResetting2 = FALSE;
	m_bLibero = FALSE;
	m_bOK = FALSE;

	m_lID = 0;
}

CEditDynFormCodiceDescrizione::~CEditDynFormCodiceDescrizione()
{
}

BEGIN_MESSAGE_MAP(CEditDynFormCodiceDescrizione, CEndoxDynForm)

	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_SETFOCUS(IDC_BUTTON1, OnBnSetfocusButton1)
	ON_BN_SETFOCUS(IDC_BUTTON2, OnBnSetfocusButton2)

	ON_EN_CHANGE(IDC_EDIT1, OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnEnChangeEdit2)

	ON_MESSAGE(EPM_CHECKVALUE, OnCheckValue)

END_MESSAGE_MAP()

void CEditDynFormCodiceDescrizione::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new CEditDynFormCodiceDescrizione(NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(CEditDynFormCodiceDescrizione::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CEditDynFormCodiceDescrizione::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		case IDC_EDIT1:
		case IDC_EDIT2:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CEditDynFormCodiceDescrizione::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, m_ctrlEdit1);
	DDX_Control(pDX, IDC_EDIT2, m_ctrlEdit2);
	DDX_Control(pDX, IDC_BUTTON1, m_ctrlButton1);
	DDX_Control(pDX, IDC_BUTTON2, m_ctrlButton2);

	if (pDX->m_bSaveAndValidate)
	{
		switch (m_lContenuto)
		{
			case cmb_medico1:
			{
				m_pEsamiView->m_pEsamiSet->m_lMedico = m_lID;
				if (m_lID > 0)
					m_pEsamiView->m_pEsamiSet->SetFieldNull(&m_pEsamiView->m_pEsamiSet->m_lMedico, FALSE);

				if (m_bLibero)
				{
					CString sTemp;
					GetDlgItemText(IDC_EDIT2, sTemp);
					m_pEsamiView->m_pEsamiSet->m_sMedicoLibero = sTemp.Left(255);
				}
				else
				{
					m_pEsamiView->m_pEsamiSet->SetFieldNull(&m_pEsamiView->m_pEsamiSet->m_sMedicoLibero);
				}

				break;
			}
			case cmb_medico2:
			{
				m_pEsamiView->m_pEsamiSet->m_lAssistente = m_lID;
				if (m_lID > 0)
					m_pEsamiView->m_pEsamiSet->SetFieldNull(&m_pEsamiView->m_pEsamiSet->m_lAssistente, FALSE);

				if (m_bLibero)
				{
					CString sTemp;
					GetDlgItemText(IDC_EDIT2, sTemp);
					m_pEsamiView->m_pEsamiSet->m_sAssistenteLibero = sTemp.Left(255);
				}
				else
				{
					m_pEsamiView->m_pEsamiSet->SetFieldNull(&m_pEsamiView->m_pEsamiSet->m_sAssistenteLibero);
				}

				break;
			}
		}
	}
	else
	{
		m_lID = 0;
		SetDlgItemText(IDC_EDIT1, "");
		SetDlgItemText(IDC_EDIT2, "");

		switch (m_lContenuto)
		{
			case cmb_medico1:
			{
				if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lMedico) && (&m_pEsamiView->m_pEsamiSet->m_lMedico > 0))
				{
					CString strFilter;
					strFilter.Format("Contatore=%li", m_pEsamiView->m_pEsamiSet->m_lMedico);

					CMediciSet setMedici;
					setMedici.SetOpenFilter(strFilter);
					if (setMedici.OpenRecordset("CEditDynFormCodiceDescrizione::DoDataExchange"))
					{
						if (!setMedici.IsEOF())
						{
							m_lID = setMedici.m_lContatore;
							m_bLibero = setMedici.m_bLibero;
							SetDlgItemText(IDC_EDIT1, setMedici.m_sCodice);

							if (m_bLibero)
								SetDlgItemText(IDC_EDIT2, m_pEsamiView->m_pEsamiSet->m_sMedicoLibero);
							else
								SetDlgItemText(IDC_EDIT2, CString(setMedici.m_sTitolo + " " + setMedici.m_sNome + " " + setMedici.m_sCognome).Trim());
						}

						setMedici.CloseRecordset("CEditDynFormCodiceDescrizione::DoDataExchange");
					}
				}
				else
				{
					m_lID = 0;
					m_bLibero = FALSE;
					SetDlgItemText(IDC_EDIT1, "");
					SetDlgItemText(IDC_EDIT2, "");
				}

				break;
			}
			case cmb_medico2:
			{
				if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lAssistente) && (&m_pEsamiView->m_pEsamiSet->m_lAssistente > 0))
				{
					CString strFilter;
					strFilter.Format("Contatore=%li", m_pEsamiView->m_pEsamiSet->m_lAssistente);

					CMediciSet setMedici;
					setMedici.SetOpenFilter(strFilter);
					if (setMedici.OpenRecordset("CEditDynFormCodiceDescrizione::DoDataExchange"))
					{
						if (!setMedici.IsEOF())
						{
							m_lID = setMedici.m_lContatore;
							m_bLibero = setMedici.m_bLibero;
							SetDlgItemText(IDC_EDIT1, setMedici.m_sCodice);

							if (m_bLibero)
								SetDlgItemText(IDC_EDIT2, m_pEsamiView->m_pEsamiSet->m_sAssistenteLibero);
							else
								SetDlgItemText(IDC_EDIT2, CString(setMedici.m_sTitolo + " " + setMedici.m_sNome + " " + setMedici.m_sCognome).Trim());
						}

						setMedici.CloseRecordset("CEditDynFormCodiceDescrizione::DoDataExchange");
					}
				}
				else
				{
					m_lID = 0;
					m_bLibero = FALSE;
					SetDlgItemText(IDC_EDIT1, "");
					SetDlgItemText(IDC_EDIT2, "");
				}

				break;
			}
		}
	}
}

BOOL CEditDynFormCodiceDescrizione::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_TEXT, CSize(0, 50), CSize(100, 50));
	AddAnchor(IDC_EDIT1, CSize(0, 50), CSize(10, 50));
	AddAnchor(IDC_BUTTON1, CSize(10, 50), CSize(10, 50));
	AddAnchor(IDC_EDIT2, CSize(10, 50), CSize(100, 50));
	AddAnchor(IDC_BUTTON2, CSize(100, 50), CSize(100, 50));

	switch(m_lContenuto)
	{
		case cmb_medico1:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_MEDICO));
			break;
		}
		case cmb_medico2:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_ASSISTENTE));
			break;
		}
	}

	return TRUE;
}

LRESULT CEditDynFormCodiceDescrizione::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CEditDynFormCodiceDescrizione::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CEditDynFormCodiceDescrizione::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	BOOL bReadOnly = (BOOL)wParam;

	SendDlgItemMessage(IDC_EDIT1, EM_SETREADONLY, wParam, lParam);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(bReadOnly ? SW_HIDE : SW_SHOW);
	SendDlgItemMessage(IDC_EDIT2, EM_SETREADONLY, wParam, lParam);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(bReadOnly ? SW_HIDE : SW_SHOW);

	return 1;
}

LRESULT CEditDynFormCodiceDescrizione::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_lID = 0;
	m_bLibero = FALSE;
	SetDlgItemText(IDC_EDIT1, "");
	SetDlgItemText(IDC_EDIT2, "");

	return 1;
}

LRESULT CEditDynFormCodiceDescrizione::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CEditDynFormCodiceDescrizione::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	switch(m_lContenuto)
	{
		case cmb_medico1:
		{
			if (m_bLibero)
			{
				ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lMedico, "EEsami.Medico", 4, "AND");
				ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sMedicoLibero, "EEsami.MedicoLibero", 1);
			}
			else
			{
				ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lMedico, "EEsami.Medico", 4, "AND");
			}

			break;
		}
		case cmb_medico2:
		{
			if (m_bLibero)
			{
				ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lAssistente, "EEsami.Assistente", 4, "AND");
				ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sAssistenteLibero, "EEsami.AssistenteLibero", 1);
			}
			else
			{
				ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lAssistente, "EEsami.Assistente", 4, "AND");
			}

			break;
		}
	}

	return 1;
}

BOOL CEditDynFormCodiceDescrizione::CampoObbligatorioValido()
{
	CString strEdit1;
	GetDlgItemText(IDC_EDIT1, strEdit1);

	CString strEdit2;
	GetDlgItemText(IDC_EDIT2, strEdit2);

	if (!strEdit1.IsEmpty() || !strEdit2.IsEmpty())
		return TRUE;

	return FALSE;
}

long CEditDynFormCodiceDescrizione::GetContenuto()
{
	return m_lContenuto;
}

LRESULT CEditDynFormCodiceDescrizione::OnCheckValue(WPARAM wParam, LPARAM lParam)
{
	if ((m_lID > 0 && m_bLibero) || (m_lID > 0 && lParam == VK_TAB))
		return 0;

	CString str1, str2;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1);
	GetDlgItem(IDC_EDIT2)->GetWindowText(str2);

	switch ((UINT)wParam)
	{
	case IDC_EDIT1:
	{
		if (lParam != VK_TAB || str1.GetLength() > 0)
			OnOK1(-1);

		if ((lParam == VK_TAB && m_lID > 0) && (!m_bLibero))
			::keybd_event(VK_TAB, MapVirtualKey(VK_TAB, 0), 0, 0);

		break;
	}
	case IDC_EDIT2:
	{
		if (lParam != VK_TAB || str2.GetLength() > 0)
			OnOK2(-1);

		break;
	}
	}

	return 1;
}

void CEditDynFormCodiceDescrizione::OnBnClickedButton1()
{
	m_ctrlButton1.SetCheck(BST_UNCHECKED);

	OnOK1(m_lID > 0 ? m_lID : -1);
}

void CEditDynFormCodiceDescrizione::OnBnClickedButton2()
{
	m_ctrlButton2.SetCheck(BST_UNCHECKED);

	OnOK2(m_lID > 0 ? m_lID : -1);
}

void CEditDynFormCodiceDescrizione::OnBnSetfocusButton1()
{
	if (GetDlgItem(IDC_BUTTON1)->IsWindowVisible() == FALSE)
		GetDlgItem(IDC_EDIT1)->SetFocus();
}

void CEditDynFormCodiceDescrizione::OnBnSetfocusButton2()
{
	if (GetDlgItem(IDC_BUTTON2)->IsWindowVisible() == FALSE)
		GetDlgItem(IDC_EDIT2)->SetFocus();
}

void CEditDynFormCodiceDescrizione::OnEnChangeEdit1()
{
	if (!m_bResetting1)
	{
		m_bResetting2 = TRUE;
		SetDlgItemText(IDC_EDIT2, "");
		m_lID = 0;
		m_bResetting2 = FALSE;
	}
}

void CEditDynFormCodiceDescrizione::OnEnChangeEdit2()
{
	if (!m_bResetting2 && !m_bLibero)
	{
		m_bResetting1 = TRUE;
		SetDlgItemText(IDC_EDIT1, "");
		m_lID = 0;
		m_bResetting1 = FALSE;
	}
}

void CEditDynFormCodiceDescrizione::OnOK1(long lSel)
{
	if (lSel < 0)
	{
		CString strCodice;
		GetDlgItemText(IDC_EDIT1, strCodice);
		strCodice.MakeUpper();
		strCodice.Replace("'", "''");

		CList<CQueryFormListDlg::tagITEM> listRecord;

		CVistaMediciSedeSet setTemp;
		setTemp.FillListByCodice(strCodice, &listRecord);

		if (listRecord.GetCount() > 0)
		{
			CQueryFormListDlg::tagITEM record = listRecord.GetHead();

			// trovato un codice che corrisponde al 100% //

			m_bResetting1 = TRUE;
			m_bResetting2 = TRUE;

			m_lID = record.lContatore;
			m_bLibero = record.bLibero;

			SetDlgItemText(IDC_EDIT1, record.szCodice);

			if (!m_bLibero)
				SetDlgItemText(IDC_EDIT2, record.szDescrizione);
			else
				SetDlgItemText(IDC_EDIT2, "");

			m_bResetting1 = FALSE;
			m_bResetting2 = FALSE;
		}
		else
		{
			setTemp.FillListByCodiceLike(strCodice, &listRecord);

			if (listRecord.GetCount() == 0)
			{
				// nessun codice trovato //

				theApp.AfxMessageBoxEndo(IDS_COMBO_DYNFORM2_STRING_6);

				m_lID = 0;
				m_bLibero = FALSE;
				SetDlgItemText(IDC_EDIT1, "");
				SetDlgItemText(IDC_EDIT2, "");
				GetDlgItem(IDC_EDIT1)->SetFocus();
			}
			else
			{
				// trovati alcuni codici che potrebbero corrispondere //

				CRect rectTemp;
				GetDlgItem(IDC_EDIT1)->GetWindowRect(rectTemp);

				CPoint ptLocation;
				ptLocation.x = rectTemp.left;
				ptLocation.y = rectTemp.bottom;

				CQueryFormListDlg dlg(this, ptLocation, &listRecord, -1, FALSE);
				if (dlg.DoModal() == IDOK)
				{
					setTemp.FillListByContatore(dlg.GetItemSelected().lContatore, &listRecord);

					if (listRecord.GetCount() > 0)
					{
						CQueryFormListDlg::tagITEM record = listRecord.GetHead();

						// trovato un codice che corrisponde al 100% //

						m_bResetting1 = TRUE;
						m_bResetting2 = TRUE;

						m_lID = record.lContatore;
						m_bLibero = record.bLibero;

						SetDlgItemText(IDC_EDIT1, record.szCodice);

						if (!m_bLibero)
							SetDlgItemText(IDC_EDIT2, record.szDescrizione);
						else
							SetDlgItemText(IDC_EDIT2, "");

						m_bResetting1 = FALSE;
						m_bResetting2 = FALSE;
					}
				}
			}
		}
	}
	else
	{
		CList<CQueryFormListDlg::tagITEM> listRecord;

		CVistaMediciSedeSet setTemp;
		setTemp.FillListByAll(&listRecord);

		CRect rectTemp;
		GetDlgItem(IDC_EDIT1)->GetWindowRect(rectTemp);

		CPoint ptLocation;
		ptLocation.x = rectTemp.left;
		ptLocation.y = rectTemp.bottom;

		CQueryFormListDlg dlg(this, ptLocation, &listRecord, m_lID, FALSE);
		if (dlg.DoModal() == IDOK)
		{
			setTemp.FillListByContatore(dlg.GetItemSelected().lContatore, &listRecord);

			if (listRecord.GetCount() > 0)
			{
				CQueryFormListDlg::tagITEM record = listRecord.GetHead();

				// trovato un codice che corrisponde al 100% //

				m_bResetting1 = TRUE;
				m_bResetting2 = TRUE;

				m_lID = record.lContatore;
				m_bLibero = record.bLibero;

				SetDlgItemText(IDC_EDIT1, record.szCodice);

				if (!m_bLibero)
					SetDlgItemText(IDC_EDIT2, record.szDescrizione);
				else
					SetDlgItemText(IDC_EDIT2, "");

				m_bResetting1 = FALSE;
				m_bResetting2 = FALSE;
			}
		}
	}
}

void CEditDynFormCodiceDescrizione::OnOK2(long lSel)
{
	if (lSel < 0)
	{
		CString strDescrizione;
		GetDlgItemText(IDC_EDIT2, strDescrizione);
		strDescrizione.MakeUpper();
		strDescrizione.Replace("'", "''");

		CList<CQueryFormListDlg::tagITEM> listRecord;

		CVistaMediciSedeSet setTemp;
		setTemp.FillListByDescrizione(strDescrizione, &listRecord);

		if (listRecord.GetCount() > 0)
		{
			CQueryFormListDlg::tagITEM record = listRecord.GetHead();

			// trovata una descrizione che corrisponde al 100% //

			m_bResetting1 = TRUE;
			m_bResetting2 = TRUE;

			m_lID = record.lContatore;
			m_bLibero = record.bLibero;

			SetDlgItemText(IDC_EDIT1, record.szCodice);

			if (!m_bLibero)
				SetDlgItemText(IDC_EDIT2, record.szDescrizione);
			else
				SetDlgItemText(IDC_EDIT2, "");

			m_bResetting1 = FALSE;
			m_bResetting2 = FALSE;
		}
		else
		{
			setTemp.FillListByDescrizioneLike(strDescrizione, &listRecord);

			if (listRecord.GetCount() == 0)
			{
				// nessuna descrizione trovata //

				theApp.AfxMessageBoxEndo(IDS_COMBO_DYNFORM2_STRING_7);

				m_lID = 0;
				m_bLibero = FALSE;
				SetDlgItemText(IDC_EDIT1, "");
				SetDlgItemText(IDC_EDIT2, "");
				GetDlgItem(IDC_EDIT2)->SetFocus();
			}
			else
			{
				// trovate alcune descrizioni che potrebbero corrispondere //

				CRect rectTemp;
				GetDlgItem(IDC_EDIT1)->GetWindowRect(rectTemp);

				CPoint ptLocation;
				ptLocation.x = rectTemp.left;
				ptLocation.y = rectTemp.bottom;

				CQueryFormListDlg dlg(this, ptLocation, &listRecord, -1, FALSE);
				if (dlg.DoModal() == IDOK)
				{
					setTemp.FillListByContatore(dlg.GetItemSelected().lContatore, &listRecord);

					if (listRecord.GetCount() > 0)
					{
						CQueryFormListDlg::tagITEM record = listRecord.GetHead();

						// trovata una descrizione che corrisponde al 100% //

						m_bResetting1 = TRUE;
						m_bResetting2 = TRUE;

						m_lID = record.lContatore;
						m_bLibero = record.bLibero;

						SetDlgItemText(IDC_EDIT1, record.szCodice);

						if (!m_bLibero)
							SetDlgItemText(IDC_EDIT2, record.szDescrizione);
						else
							SetDlgItemText(IDC_EDIT2, "");

						m_bResetting1 = FALSE;
						m_bResetting2 = FALSE;
					}
				}
			}
		}
	}
	else
	{
		CList<CQueryFormListDlg::tagITEM> listRecord;

		CVistaMediciSedeSet setTemp;
		setTemp.FillListByAll(&listRecord);

		CRect rectTemp;
		GetDlgItem(IDC_EDIT2)->GetWindowRect(rectTemp);

		CPoint ptLocation;
		ptLocation.x = rectTemp.left;
		ptLocation.y = rectTemp.bottom;

		CQueryFormListDlg dlg(this, ptLocation, &listRecord, m_lID, FALSE);
		if (dlg.DoModal() == IDOK)
		{
			setTemp.FillListByContatore(dlg.GetItemSelected().lContatore, &listRecord);

			if (listRecord.GetCount() > 0)
			{
				CQueryFormListDlg::tagITEM record = listRecord.GetHead();

				// trovata una descrizione che corrisponde al 100% //

				m_bResetting1 = TRUE;
				m_bResetting2 = TRUE;

				m_lID = record.lContatore;
				m_bLibero = record.bLibero;

				SetDlgItemText(IDC_EDIT1, record.szCodice);

				if (!m_bLibero)
					SetDlgItemText(IDC_EDIT2, record.szDescrizione);
				else
					SetDlgItemText(IDC_EDIT2, "");

				m_bResetting1 = FALSE;
				m_bResetting2 = FALSE;
			}
		}
	}
}
