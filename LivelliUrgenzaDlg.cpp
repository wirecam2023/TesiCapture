#include "stdafx.h"
#include "Endox.h"
#include "LivelliUrgenzaDlg.h"

#include "ExtTransUrgenzaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLivelliUrgenzaDlg::CLivelliUrgenzaDlg(CWnd* pParent)
	: CDialog(CLivelliUrgenzaDlg::IDD, pParent)
{
	m_lId = 0;
	m_sCodiceEsterno = "";
	m_lLivelloUrgenzaEndox = 0;

	m_bAddNew = FALSE;
	m_bModify = FALSE;
	//m_bOrPressed = FALSE;
	m_bRicercaAttivata = FALSE;
	m_bUserFocus = FALSE;
	m_bValidUser = TRUE;

	m_iItemCount = -1;
	m_iItemPressed = -1;
	m_iSavedPosition = -1;
}

CLivelliUrgenzaDlg::~CLivelliUrgenzaDlg()
{
}

BEGIN_MESSAGE_MAP(CLivelliUrgenzaDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_LIVELLOURGENZA_NUOVO, OnLivelloUrgenzaNew)
	ON_BN_CLICKED(IDC_LIVELLOURGENZA_MODIFY, OnLivelloUrgenzaEdt)
	ON_BN_CLICKED(IDC_LIVELLOURGENZA_CANC, OnLivelloUrgenzaDel)
	ON_BN_CLICKED(IDC_LIVELLOURGENZA_UPDATE, OnLivelloUrgenzaSave)
	ON_BN_CLICKED(IDC_LIVELLOURGENZA_REFRESH, OnLivelloUrgenzaUndo)

	//ON_BN_CLICKED(IDC_BTN_OR,        OnBtnOr)

	ON_LBN_DBLCLK(IDC_LISTA, OnLbnDblclkLista)
	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)

	// ON_MESSAGE(WM_USER, OnWMUser) // è na pazzia //

	//ON_EN_CHANGE(IDC_LOGIN, OnEnChangeLogin)
	//ON_EN_SETFOCUS(IDC_LOGIN, OnEnSetfocusLogin)
	//ON_EN_KILLFOCUS(IDC_LOGIN, OnEnKillfocusLogin)
	//ON_BN_CLICKED(IDC_BUTTON_GENERA, OnBnClickedButtonGenera)
END_MESSAGE_MAP()

void CLivelliUrgenzaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_CODICE, m_sCodiceEsterno);

	DDX_Control(pDX, IDC_CMB_LIVELLOURGENZA, m_ctrlCmbLivelloUrgenza);

	if (pDX->m_bSaveAndValidate)
		m_lLivelloUrgenzaEndox = m_ctrlCmbLivelloUrgenza.GetItemData(m_ctrlCmbLivelloUrgenza.GetCurSel());
	else
	{
		for (int i = 0; i<m_ctrlCmbLivelloUrgenza.GetCount(); i++)
		{
			if (m_ctrlCmbLivelloUrgenza.GetItemData(i) == m_lLivelloUrgenzaEndox)
			{
				m_ctrlCmbLivelloUrgenza.SetCurSel(i);
				break;
			}
		}
	}

	DDX_Control(pDX, IDC_LISTA, m_ctrlLista);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_LIVELLOURGENZA_NUOVO, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_LIVELLOURGENZA_MODIFY, m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_LIVELLOURGENZA_CANC, m_ctrlButtonDel);
	DDX_Control(pDX, IDC_LIVELLOURGENZA_UPDATE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_LIVELLOURGENZA_REFRESH, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
}

BOOL CLivelliUrgenzaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_LIVELLOURGENZA_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIVELLOURGENZA_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIVELLOURGENZA_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIVELLOURGENZA_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIVELLOURGENZA_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_CODICE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CMB_LIVELLOURGENZA)->EnableWindow(FALSE);

	m_ctrlLista.SetTabStops(138);
	RiempiListaUrgenze();

	m_iItemPressed = 0;
	m_iItemCount = m_ctrlLista.GetCount();

	/*m_ctrlCmbLivelloUrgenza.InsertString(0, "");
	m_ctrlCmbLivelloUrgenza.SetItemData(0, -1);*/
	m_ctrlCmbLivelloUrgenza.InsertString(0, "NON URGENTE");
	m_ctrlCmbLivelloUrgenza.SetItemData(0, 0);
	m_ctrlCmbLivelloUrgenza.InsertString(1, "URGENTE");
	m_ctrlCmbLivelloUrgenza.SetItemData(1, 1);

	//
	theApp.LocalizeDialog(this, CLivelliUrgenzaDlg::IDD, "LivelliUrgenzaDlg");

	if (!m_bMenu)
		PostMessage(WM_USER);

	return TRUE;
}

/* è na pazzia
LRESULT CMediciCurantiInviantiDlg::OnWMUser(WPARAM wParam, LPARAM lParam)
{
GetDlgItem(IDC_RICERCA_STR2)->SetFocus();
return 0;
}
*/

void CLivelliUrgenzaDlg::RiempiListaUrgenze()
{
	BeginWaitCursor();
	m_ctrlLista.SetRedraw(FALSE);
	m_ctrlLista.ResetContent();

	int nIndex = 0;

	CExtTransUrgenzaSet setTemp;

	if (setTemp.OpenRecordset("CLivelliUrgenzaDlg::RiempiListaUrgenze"))
	{
		while (!setTemp.IsEOF())
		{
			int index = m_ctrlLista.InsertString(m_ctrlLista.GetCount(), setTemp.m_sCodiceIntegrazione);
			m_ctrlLista.SetItemData(index, setTemp.m_lId);

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CLivelliUrgenzaDlg::RiempiListaUrgenze");
	}

	m_ctrlLista.SetRedraw(TRUE);
	EndWaitCursor();

	OnSelchangeLista();
}

void CLivelliUrgenzaDlg::OnLbnDblclkLista()
{
	OnOK();
}

void CLivelliUrgenzaDlg::OnSelchangeLista()
{
	CString strDoctor, strTmp;

	if (m_bAddNew || m_bModify)
		return;

	int nCount = m_ctrlLista.GetCount();

	if (nCount > 0)
	{
		int nCurPos = m_ctrlLista.GetCurSel();

		if (nCurPos >= 0)
		{
			// recupera il codice del medico appena selezionato	
			DWORD dwCode = m_ctrlLista.GetItemData(nCurPos);

			GetDlgItem(IDC_LIVELLOURGENZA_NUOVO)->EnableWindow(TRUE);
			GetDlgItem(IDC_LIVELLOURGENZA_MODIFY)->EnableWindow(TRUE);
			GetDlgItem(IDC_LIVELLOURGENZA_CANC)->EnableWindow(TRUE);
			GetDlgItem(IDC_LIVELLOURGENZA_UPDATE)->EnableWindow(FALSE);
			GetDlgItem(IDC_LIVELLOURGENZA_REFRESH)->EnableWindow(FALSE);

			if (dwCode >= 0)
			{
				CString strFilter;
				strFilter.Format("Id=%li", (long)dwCode);

				CExtTransUrgenzaSet setTemp;
				setTemp.SetOpenFilter(strFilter);

				if (setTemp.OpenRecordset("CLivelliUrgenzaDlg::OnSelchangeLista"))
				{
					if (!setTemp.IsEOF())
					{
						m_lId = setTemp.m_lId;
						m_sCodiceEsterno = setTemp.m_sCodiceIntegrazione;
						m_lLivelloUrgenzaEndox = setTemp.m_lLivelloUrgenza;
					}

					setTemp.CloseRecordset("CLivelliUrgenzaDlg::OnSelchangeLista");
				}

				UpdateData(FALSE);
			}
		}
	}
}

BOOL CLivelliUrgenzaDlg::CanBeInserted(long lContatore)
{
	/*CString strContatore, strTmp;

	//Controllo inizio stringa
	strContatore.Format("%i ", lContatore);
	strTmp = m_sRicerca.Left(strContatore.GetLength());

	if (strTmp == strContatore)
	return FALSE;

	//Controllo in mezzo alla stringa
	strContatore.Format(" %i ", lContatore);

	if (m_sRicerca.Find(strContatore) > 0)
	return FALSE;

	//Controllo alla fine
	strContatore.Format(" %i", lContatore);
	strTmp = m_sRicerca.Right(strContatore.GetLength());

	if (strTmp == strContatore)
	return FALSE;*/

	return TRUE;
}

void CLivelliUrgenzaDlg::OnOK()
{
	UpdateData(FALSE);

	CDialog::OnOK();
}

void CLivelliUrgenzaDlg::OnLivelloUrgenzaNew()
{
	GetDlgItem(IDC_CODICE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CMB_LIVELLOURGENZA)->EnableWindow(TRUE);

	GetDlgItem(IDC_LIVELLOURGENZA_NUOVO)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIVELLOURGENZA_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIVELLOURGENZA_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIVELLOURGENZA_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIVELLOURGENZA_REFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_lId = 0;
	m_sCodiceEsterno.Empty();
	m_lLivelloUrgenzaEndox = -1;

	m_bAddNew = TRUE;

	GetDlgItem(IDC_CODICE)->SetFocus();

	UpdateData(FALSE);
}

void CLivelliUrgenzaDlg::OnLivelloUrgenzaEdt()
{
	int nSelect = m_ctrlLista.GetCurSel();

	if (nSelect >= 0)
	{
		GetDlgItem(IDC_LISTA)->EnableWindow(FALSE);
		GetDlgItem(IDC_CODICE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_LIVELLOURGENZA)->EnableWindow(TRUE);

		GetDlgItem(IDC_LIVELLOURGENZA_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIVELLOURGENZA_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIVELLOURGENZA_CANC)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIVELLOURGENZA_UPDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIVELLOURGENZA_REFRESH)->EnableWindow(TRUE);

		GetDlgItem(IDOK)->EnableWindow(FALSE);

		m_bModify = TRUE;

		GetDlgItem(IDC_CODICE)->SetFocus();

		UpdateData(FALSE);
	}
}

void CLivelliUrgenzaDlg::OnLivelloUrgenzaDel()
{
	BOOL	bDeleted = FALSE;

	GetDlgItem(IDC_LISTA)->EnableWindow(TRUE);
	GetDlgItem(IDC_CODICE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CMB_LIVELLOURGENZA)->EnableWindow(FALSE);

	GetDlgItem(IDC_PROVENIENZA_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_PROVENIENZA_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_PROVENIENZA_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_PROVENIENZA_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_PROVENIENZA_REFRESH)->EnableWindow(FALSE);

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_DELETE_CONFIRM), MB_YESNO) == IDYES)
	{
		// recupera il codice del medico appena selezionato	
		int posiz = m_ctrlLista.GetCurSel();

		if (posiz >= 0)
		{
			DWORD dwCode = m_ctrlLista.GetItemData(posiz);

			if (dwCode >= 0)
			{
				CString strFilter;
				strFilter.Format("Id=%li", (long)dwCode);

				CExtTransUrgenzaSet setTemp;
				setTemp.SetOpenFilter(strFilter);

				if (setTemp.OpenRecordset("CLivelliUrgenzaDlg::OnLivelloUrgenzaDel"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.DeleteRecordset("CLivelliUrgenzaDlg::OnLivelloUrgenzaDel"))
						{
							int nRemained = m_ctrlLista.DeleteString(posiz);
							int nNewPos = min(posiz, nRemained - 1);

							m_ctrlLista.SetCurSel(nNewPos);

							OnSelchangeLista();
						}
					}


					setTemp.CloseRecordset("CLivelliUrgenzaDlg::OnLivelloUrgenzaDel");
				}
			}
		}
	}

	UpdateData(FALSE);
}

void CLivelliUrgenzaDlg::OnLivelloUrgenzaSave()
{
	BOOL bSaved = FALSE;

	UpdateData(TRUE);

	if (m_sCodiceEsterno.IsEmpty() || m_lLivelloUrgenzaEndox < 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		CExtTransUrgenzaSet setTemp;
		if (setTemp.OpenRecordset("CLivelliUrgenzaDlg::OnLivelloUrgenzaSave"))
		{
			setTemp.AddNewRecordset("CLivelliUrgenzaDlg::OnLivelloUrgenzaSave");

			setTemp.m_sCodiceIntegrazione = m_sCodiceEsterno;
			setTemp.m_lLivelloUrgenza = m_lLivelloUrgenzaEndox;

			bSaved = setTemp.UpdateRecordset("CLivelliUrgenzaDlg::OnLivelloUrgenzaSave");

			m_lId = setTemp.GetLastAdd();

			setTemp.CloseRecordset("CLivelliUrgenzaDlg::OnLivelloUrgenzaSave");
		}
	}
	else
	{
		CString strFilter;
		strFilter.Format("id=%li", m_lId);

		CExtTransUrgenzaSet setTemp;
		setTemp.SetOpenFilter(strFilter);

		if (setTemp.OpenRecordset("CLivelliUrgenzaDlg::OnLivelloUrgenzaSave"))
		{
			if (setTemp.IsBOF() && setTemp.IsEOF())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_ALREADY_DELETED), MB_ICONINFORMATION);
			}
			else
			{
				if (setTemp.EditRecordset("CLivelliUrgenzaDlg::OnLivelloUrgenzaSave"))
				{
					setTemp.SetFieldDirty(NULL, TRUE);
					setTemp.SetFieldDirty(&setTemp.m_lId, FALSE);

					setTemp.m_sCodiceIntegrazione = m_sCodiceEsterno;
					setTemp.m_lLivelloUrgenza = m_lLivelloUrgenzaEndox;

					bSaved = setTemp.UpdateRecordset("CLivelliUrgenzaDlg::OnLivelloUrgenzaSave");
				}
			}

			setTemp.CloseRecordset("CLivelliUrgenzaDlg::OnLivelloUrgenzaSave");
		}
	}

	if (bSaved)
	{
		int posiz;

		if (m_bAddNew)
		{
			posiz = m_ctrlLista.AddString(m_sCodiceEsterno);

			if (posiz >= 0)
			{
				m_iSavedPosition = posiz;

				m_ctrlLista.SetItemData(posiz, (DWORD)m_lId);
				m_ctrlLista.SetCurSel(posiz);
			}
		}
		else
		{
			posiz = m_ctrlLista.GetCurSel();

			if (posiz >= 0)
			{
				m_ctrlLista.DeleteString(posiz);

				posiz = m_ctrlLista.InsertString(posiz, m_sCodiceEsterno);

				if (posiz >= 0)
				{
					m_ctrlLista.SetItemData(posiz, (DWORD)m_lId);
					m_ctrlLista.SetCurSel(posiz);
				}
			}
		}

		GetDlgItem(IDC_LISTA)->EnableWindow(TRUE);
		GetDlgItem(IDC_CODICE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_LIVELLOURGENZA)->EnableWindow(FALSE);

		GetDlgItem(IDC_LIVELLOURGENZA_NUOVO)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIVELLOURGENZA_MODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIVELLOURGENZA_CANC)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIVELLOURGENZA_UPDATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIVELLOURGENZA_REFRESH)->EnableWindow(FALSE);

		GetDlgItem(IDOK)->EnableWindow(TRUE);

		m_bModify = FALSE;
		m_bAddNew = FALSE;

		OnSelchangeLista();
	}
}

void CLivelliUrgenzaDlg::OnLivelloUrgenzaUndo()
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	GetDlgItem(IDC_LISTA)->EnableWindow(TRUE);
	GetDlgItem(IDC_CODICE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CMB_LIVELLOURGENZA)->EnableWindow(FALSE);

	GetDlgItem(IDC_LIVELLOURGENZA_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIVELLOURGENZA_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIVELLOURGENZA_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIVELLOURGENZA_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIVELLOURGENZA_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(TRUE);

	if (m_iSavedPosition <= m_ctrlLista.GetCount())
	{
		int nPos = m_iSavedPosition;

		if (nPos < 0 && m_ctrlLista.GetCount())
			nPos = 0;

		m_iSavedPosition = -1;

		m_ctrlLista.SetCurSel(nPos);

		OnSelchangeLista();
	}
}

