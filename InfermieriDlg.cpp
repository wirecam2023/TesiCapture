#include "stdafx.h"
#include "Endox.h"
#include "InfermieriDlg.h"

#include "EsamiView.h"
#include "InfermieriSet.h"
#include "SediEsameSet.h"
#include "VistaUtentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInfermieriDlg::CInfermieriDlg(CEsamiView* pEsamiView, BOOL bMenu)
	: CDialog(CInfermieriDlg::IDD, (CWnd*)pEsamiView)
{
	m_pEsamiView	= pEsamiView;
	m_bMenu			= bMenu;

	m_lID = 0;
	m_sTitolo = "";
	m_sCognome = "";
	m_sNome = "";
	m_sMatricola = "";
	m_sIndirizzo = "";
	m_sCitta = "";
	m_sProvincia = "";
	m_sTelefono = "";

	m_strRicerca = "";

	m_lSavedPosition = -1;
	m_bAddNew		= FALSE;
	m_bModify		= FALSE;

	m_bOrPressed    = FALSE;
}

CInfermieriDlg::~CInfermieriDlg()
{
}

void CInfermieriDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_TITOLO, m_sTitolo);
	DDX_Text(pDX, IDC_COGNOME, m_sCognome);
	DDX_Text(pDX, IDC_NOME, m_sNome);
	DDX_Text(pDX, IDC_MATRICOLA, m_sMatricola);
	DDX_Text(pDX, IDC_INDIRIZZO, m_sIndirizzo);
	DDX_Text(pDX, IDC_CITTA, m_sCitta);
	DDX_Text(pDX, IDC_PROVINCIA, m_sProvincia);
	DDX_Text(pDX, IDC_TELEFONO, m_sTelefono);

	DDX_Text(pDX, IDC_RICERCA_STR, m_strRicercaView);
	DDX_Control(pDX, IDC_LISTA,  m_ctrlLista);

	DDX_Control(pDX, IDC_STATIC_1,       m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2,       m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3,       m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4,       m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5,       m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6,       m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_7,       m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC_8,		 m_ctrlStatic8);

	DDX_Control(pDX, IDC_COMBO_USER, m_ctrlComboUser);

	DDX_Control(pDX, IDC_MEDICI_NUOVO,   m_ctrlButtonNew);
	DDX_Control(pDX, IDC_MEDICI_MODIFY,  m_ctrlButtonMod);
	DDX_Control(pDX, IDC_MEDICI_CANC,    m_ctrlButtonDel);
	DDX_Control(pDX, IDC_MEDICI_UPDATE,  m_ctrlButtonUpd);
	DDX_Control(pDX, IDC_MEDICI_REFRESH, m_ctrlButtonRefresh);
	DDX_Control(pDX, IDOK, m_ctrlButtonExit);
}

BEGIN_MESSAGE_MAP(CInfermieriDlg, CDialog)
	ON_BN_CLICKED(IDC_MEDICI_CANC,	 OnInfermieriDelete)
	ON_BN_CLICKED(IDC_MEDICI_MODIFY, OnInfermieriModify)
	ON_BN_CLICKED(IDC_MEDICI_NUOVO,  OnInfermieriNew)
	ON_BN_CLICKED(IDC_MEDICI_REFRESH,OnInfermieriRefresh)
	ON_BN_CLICKED(IDC_MEDICI_UPDATE, OnInfermieriUpdate)
	ON_BN_CLICKED(IDC_BTN_OR,        OnBtnOr)
	ON_LBN_DBLCLK(IDC_LISTA,         OnLbnDblclkLista)
	ON_LBN_SELCHANGE(IDC_LISTA,      OnSelchangeLista)
	ON_BN_CLICKED(IDOK, OnOK)
END_MESSAGE_MAP()

BOOL CInfermieriDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC1)->SetFont(&theApp.m_fontBold, TRUE);
	GetDlgItem(IDC_STATIC2)->SetFont(&theApp.m_fontBold, TRUE);

	GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_TITOLO)->EnableWindow(FALSE);
	GetDlgItem(IDC_COGNOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MATRICOLA)->EnableWindow(FALSE);
	GetDlgItem(IDC_INDIRIZZO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CITTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_PROVINCIA)->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);

	GetDlgItem(IDC_RICERCA_STR)->EnableWindow(FALSE);

	CString strSede = CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, FALSE);
	SetDlgItemText(IDC_STATIC2, strSede);

	m_bRicercaAttivata = theApp.m_nProgramMode & FILTER_RECORD_ESAMI;

	RiempiComboUsers();

	RiempiListaInfermieri();

	GetDlgItem(IDC_RICERCA_STR)->EnableWindow(FALSE);
	
	if (m_bRicercaAttivata)
	{
		GetDlgItem(IDC_LABEL_RIC)  ->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RICERCA_STR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_OR)     ->ShowWindow(SW_SHOW);
	}

	m_nItemSelected = 0;
	m_nItemCount = m_ctrlLista.GetCount();
	
	theApp.LocalizeDialog(this, CInfermieriDlg::IDD, "InfermieriDlg");

	return TRUE;
}

void CInfermieriDlg::RiempiListaInfermieri()
{
	m_ctrlLista.SetTabStops(100);
	
	CInfermieriSet setInf;

	// Sandro 18/11/2014 // RAS 20140046 //
	if (m_bRicercaAttivata)
	{
		setInf.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
		setInf.SetOpenFilter("");
		setInf.SetSortRecord("Cognome, Nome");
	}
	else
	{
		setInf.SetOpenFilter("Sede LIKE '" + CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, TRUE) + "'");
		setInf.SetSortRecord("Contatore");
	}

	if (setInf.OpenRecordset("CInfermieriDlg::RiempiListaInfermieri"))
	{
		while (!setInf.IsEOF())
		{
			// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
			int posiz;
			if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
				posiz = m_ctrlLista.AddString(setInf.m_sNome + "\t" + setInf.m_sCognome);
			else
				posiz = m_ctrlLista.AddString(setInf.m_sCognome + "\t" + setInf.m_sNome);

			if (posiz >= 0)
				m_ctrlLista.SetItemData(posiz, (DWORD)setInf.m_lContatore);

			setInf.MoveNext();
		}

		setInf.CloseRecordset("CInfermieriDlg::RiempiListaInfermieri");
	}
	
	OnSelchangeLista();
}

void CInfermieriDlg::OnSelchangeLista() 
{
	CString strInfermiere, strTmp;

	if (m_bAddNew || m_bModify)
		return;

	int nCount = m_ctrlLista.GetCount();

	if (nCount > 0)
	{
		int nCurPos = m_ctrlLista.GetCurSel();

		if (nCurPos >= 0)
		{
			// recupera il codice dell'infermiere appena selezionato	
			DWORD dwCode = m_ctrlLista.GetItemData(nCurPos);

			GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(TRUE);
			GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(TRUE);
			GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(TRUE);
			GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(FALSE);
			GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(FALSE);

			if (dwCode >= 0)
			{
				CString sFilter;
				sFilter.Format("Contatore=%li", (long)dwCode);

				CInfermieriSet setInf;
				setInf.SetOpenFilter(sFilter);

				if (setInf.OpenRecordset("CInfermieriDlg::OnSelchangeLista"))
				{
					if (!setInf.IsEOF())
					{
						m_lID = setInf.m_lContatore;
						m_sTitolo = setInf.m_sTitolo;
						m_sCognome = setInf.m_sCognome;
						m_sNome = setInf.m_sNome;
						m_sMatricola = setInf.m_sMatricola;
						m_sIndirizzo = setInf.m_sVia;
						m_sCitta = setInf.m_sCitta;
						m_sProvincia = setInf.m_sProvincia;
						m_sTelefono = setInf.m_sTelefono;
						// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
						if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
							strInfermiere = m_sTitolo + " " + m_sNome + " " + m_sCognome;
						else
							strInfermiere = m_sTitolo + " " + m_sCognome + " " + m_sNome;
						strInfermiere.TrimLeft();
						strInfermiere.TrimRight();

						int m_iUserCurSel = -1;
						for (int i = 0; i < m_ctrlComboUser.GetCount(); i++)
						{
							if (m_ctrlComboUser.GetItemData(i) == setInf.m_lIDUserEndox)
							{
								m_iUserCurSel = i;
								break;
							}
						}
						m_ctrlComboUser.SetCurSel(m_iUserCurSel);

						if (m_bRicercaAttivata)
						{
							if (m_bOrPressed)
							{
								if (CanBeInserted(m_lID))
								{
									strTmp.Format("%i", m_lID);
									m_strRicerca += strTmp;
									m_strRicercaView += strInfermiere;

									m_nItemSelected++;
									m_bOrPressed = FALSE;

									if (m_nItemSelected < m_nItemCount)
										GetDlgItem(IDC_BTN_OR)->EnableWindow(TRUE);
								}
							}
							else
							{
								m_nItemSelected = 1;
								m_strRicerca.Format("%i", m_lID);
								m_strRicercaView = strInfermiere;
							}
						}
						else
						{
							m_strRicerca.Format("%i", m_lID);
							m_strRicercaView = strInfermiere;
						}

						m_lSavedPosition = nCurPos;
					}

					setInf.CloseRecordset("CInfermieriDlg::OnSelchangeLista");
				}

				UpdateData(FALSE);
			}
		}
	}
}

BOOL CInfermieriDlg::CanBeInserted(long lContatore)
{
	CString strContatore, strTmp;

	//Controllo inizio stringa
	strContatore.Format("%i ", lContatore);
	strTmp = m_strRicerca.Left(strContatore.GetLength());

	if (strTmp == strContatore)
		return FALSE;

	//Controllo in mezzo alla stringa
	strContatore.Format(" %i ", lContatore);

	if (m_strRicerca.Find(strContatore) > 0)
		return FALSE;

	//Controllo alla fine
	strContatore.Format(" %i", lContatore);
	strTmp = m_strRicerca.Right(strContatore.GetLength());

	if (strTmp == strContatore)
		return FALSE;

	return TRUE;
}

void CInfermieriDlg::OnBtnOr()
{
	m_strRicerca += " OR ";
	m_strRicercaView += " OR ";
	
	m_bOrPressed = TRUE;
	GetDlgItem(IDC_BTN_OR)->EnableWindow(FALSE);
	
	UpdateData(FALSE);
}

void CInfermieriDlg::OnLbnDblclkLista()
{
	if (m_bMenu == FALSE)
		OnOK();
}

void CInfermieriDlg::OnInfermieriDelete() 
{
	BOOL bDeleted = FALSE;

	GetDlgItem(IDC_LISTA)->EnableWindow(TRUE);
	GetDlgItem(IDC_TITOLO)->EnableWindow(FALSE);
	GetDlgItem(IDC_COGNOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MATRICOLA)->EnableWindow(FALSE);
	GetDlgItem(IDC_INDIRIZZO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CITTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_PROVINCIA)->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_USER)->EnableWindow(FALSE);

	GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(FALSE);

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_DELETE_CONFIRM), MB_YESNO) == IDYES)
	{
		// recupera il codice del medico appena selezionato	
		int posiz = m_ctrlLista.GetCurSel();
			
		if (posiz >= 0)
		{
			DWORD dwCode = m_ctrlLista.GetItemData(posiz);
		
			if (dwCode >= 0)
			{
				CString sFilter;
				sFilter.Format("Contatore=%li", (long) dwCode);
			
				CInfermieriSet setInf;
				setInf.SetOpenFilter(sFilter);
			
				if (setInf.OpenRecordset("CInfermieriDlg::OnInfermieriDelete"))
				{
					if (!setInf.IsEOF())
					{
						if (setInf.DeleteRecordset("CInfermieriDlg::OnInfermieriDelete"))
						{
							int nRemained = m_ctrlLista.DeleteString(posiz);
							int nNewPos = min(posiz, nRemained - 1);

							m_ctrlLista.SetCurSel(nNewPos);

							OnSelchangeLista();
						}
					}

					setInf.CloseRecordset("CInfermieriDlg::OnInfermieriDelete");
				}
			}
		}
	}
	
	UpdateData(FALSE);
}

void CInfermieriDlg::OnInfermieriModify() 
{
	int nSelect = m_ctrlLista.GetCurSel();
		
	if (nSelect >= 0)
	{
		long lIDUserTemp = 0;

		int nCurSelTemp = m_ctrlComboUser.GetCurSel();
		if (nCurSelTemp >= 0)
			lIDUserTemp = m_ctrlComboUser.GetItemData(nCurSelTemp);

		// Ricarico la lista che potrebbe essere cambiata
		RiempiComboUsers();
		m_ctrlComboUser.SetCurSel(-1);
		for (int i = 0; i < m_ctrlComboUser.GetCount(); i++)
		{
			if (m_ctrlComboUser.GetItemData(i) == lIDUserTemp)
			{
				m_ctrlComboUser.SetCurSel(i);
				break;
			}
		}

		GetDlgItem(IDC_LISTA)->EnableWindow(FALSE);
		GetDlgItem(IDC_TITOLO)->EnableWindow(TRUE);
		GetDlgItem(IDC_COGNOME)->EnableWindow(TRUE);
		GetDlgItem(IDC_NOME)->EnableWindow(TRUE);
		GetDlgItem(IDC_MATRICOLA)->EnableWindow(TRUE);
		GetDlgItem(IDC_INDIRIZZO)->EnableWindow(TRUE);
		GetDlgItem(IDC_CITTA)->EnableWindow(TRUE);
		GetDlgItem(IDC_PROVINCIA)->EnableWindow(TRUE);
		GetDlgItem(IDC_TELEFONO)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_USER)->EnableWindow(TRUE);

		GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(FALSE);
		GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(TRUE);

		GetDlgItem(IDOK)->EnableWindow(FALSE);

		m_bModify = TRUE;

		GetDlgItem(IDC_TITOLO)->SetFocus();

		UpdateData(FALSE);
	}			
}

void CInfermieriDlg::OnInfermieriNew() 
{
	GetDlgItem(IDC_LISTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_TITOLO)->EnableWindow(TRUE);
	GetDlgItem(IDC_COGNOME)->EnableWindow(TRUE);
	GetDlgItem(IDC_NOME)->EnableWindow(TRUE);
	GetDlgItem(IDC_MATRICOLA)->EnableWindow(TRUE);
	GetDlgItem(IDC_INDIRIZZO)->EnableWindow(TRUE);
	GetDlgItem(IDC_CITTA)->EnableWindow(TRUE);
	GetDlgItem(IDC_PROVINCIA)->EnableWindow(TRUE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_USER)->EnableWindow(TRUE);

	GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_lID = 0;
	m_sTitolo.Empty();
	m_sCognome.Empty();
	m_sNome.Empty();
	m_sMatricola.Empty();
	m_sIndirizzo.Empty();
	m_sCitta.Empty();
	m_sProvincia.Empty();
	m_sTelefono.Empty();
	m_ctrlComboUser.SetCurSel(-1);

	m_bAddNew = TRUE;

	GetDlgItem(IDC_TITOLO)->SetFocus();

	UpdateData(FALSE);
}

void CInfermieriDlg::OnInfermieriRefresh() 
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	GetDlgItem(IDC_LISTA)->EnableWindow(TRUE);
	GetDlgItem(IDC_TITOLO)->EnableWindow(FALSE);
	GetDlgItem(IDC_COGNOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MATRICOLA)->EnableWindow(FALSE);
	GetDlgItem(IDC_INDIRIZZO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CITTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_PROVINCIA)->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_USER)->EnableWindow(FALSE);

	GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(TRUE);

	if (m_lSavedPosition <= m_ctrlLista.GetCount())
	{
		int nPos = m_lSavedPosition;

		if (nPos < 0 && m_ctrlLista.GetCount())
			nPos = 0;
	
		m_lSavedPosition = -1;

		m_ctrlLista.SetCurSel(nPos);

		OnSelchangeLista();
	}
}

void CInfermieriDlg::OnInfermieriUpdate() 
{
	if (m_ctrlComboUser.GetItemData(m_ctrlComboUser.GetCurSel()) <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_INFMED_ALERT1));
		return;
	}

	BOOL bSaved = FALSE;
	long lLastAdd = 0;
	
	UpdateData(TRUE);

	if (m_sTitolo.IsEmpty() && 
		m_sCognome.IsEmpty() &&
		m_sNome.IsEmpty() && 
		m_sMatricola.IsEmpty() &&	
		m_sIndirizzo.IsEmpty() &&	
		m_sCitta.IsEmpty() &&	
		m_sProvincia.IsEmpty() &&
		m_sTelefono.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		CInfermieriSet setInf;
		setInf.SetOpenFilter("Contatore=0");
		if (setInf.OpenRecordset("CInfermieriDlg::OnInfermieriUpdate"))
		{
			if (setInf.AddNewRecordset("CInfermieriDlg::OnInfermieriUpdate"))
			{
				setInf.m_sTitolo = m_sTitolo;
				setInf.m_sCognome = m_sCognome;
				setInf.m_sNome = m_sNome;
				setInf.m_sMatricola = m_sMatricola;
				setInf.m_sVia = m_sIndirizzo;
				setInf.m_sCitta = m_sCitta;
				setInf.m_sProvincia = m_sProvincia;
				setInf.m_sTelefono = m_sTelefono;
				setInf.m_sSede = CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, FALSE);
				setInf.m_lIDUserEndox = m_ctrlComboUser.GetItemData(m_ctrlComboUser.GetCurSel());

				bSaved = setInf.UpdateRecordset("CInfermieriDlg::OnInfermieriUpdate");

				if (bSaved)
					lLastAdd = setInf.GetLastAdd();
			}
			setInf.CloseRecordset("CInfermieriDlg::OnInfermieriUpdate");
		}
	}
	else		
	{
		CString sFilter;
		sFilter.Format("Contatore=%li", m_lID);

		CInfermieriSet setInf;
		setInf.SetOpenFilter(sFilter);
 
		if (setInf.OpenRecordset("CInfermieriDlg::OnInfermieriUpdate"))
		{
			if (!setInf.IsEOF())
			{
				if (setInf.EditRecordset("CInfermieriDlg::OnInfermieriUpdate"))
				{
					setInf.m_sTitolo = m_sTitolo;
					setInf.m_sCognome = m_sCognome;
					setInf.m_sNome = m_sNome;
					setInf.m_sMatricola = m_sMatricola;
					setInf.m_sVia = m_sIndirizzo;
					setInf.m_sCitta = m_sCitta;
					setInf.m_sProvincia = m_sProvincia;
					setInf.m_sTelefono = m_sTelefono;
					setInf.m_lIDUserEndox = m_ctrlComboUser.GetItemData(m_ctrlComboUser.GetCurSel());

					bSaved = setInf.UpdateRecordset("CInfermieriDlg::OnInfermieriUpdate");
				}
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_INFERMIERIDLG_ALREADY_DELETED), MB_ICONINFORMATION);
			}
			setInf.CloseRecordset("CInfermieriDlg::OnInfermieriUpdate");
		}
	}
	
	if (bSaved)	
	{
		int posiz;

		if (m_bAddNew)
		{
			posiz = m_ctrlLista.AddString(m_sCognome + "\t" + m_sNome);

			if (posiz >= 0)
			{
				m_ctrlLista.SetItemData(posiz, (DWORD)lLastAdd);
				m_ctrlLista.SetCurSel(posiz);
			}
		}
		else
		{
			posiz = m_ctrlLista.GetCurSel();

			if (posiz >= 0)
			{
				m_ctrlLista.DeleteString(posiz);

				posiz = m_ctrlLista.InsertString(posiz, m_sCognome + "\t" + m_sNome);

				if (posiz >= 0)
				{
					m_ctrlLista.SetItemData(posiz, (DWORD)m_lID);
				
					m_ctrlLista.SetCurSel(posiz);
				}
			}
		}

		GetDlgItem(IDC_LISTA)->EnableWindow(TRUE);
		GetDlgItem(IDC_TITOLO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COGNOME)->EnableWindow(FALSE);
		GetDlgItem(IDC_NOME)->EnableWindow(FALSE);
		GetDlgItem(IDC_MATRICOLA)->EnableWindow(FALSE);
		GetDlgItem(IDC_INDIRIZZO)->EnableWindow(FALSE);
		GetDlgItem(IDC_CITTA)->EnableWindow(FALSE);
		GetDlgItem(IDC_PROVINCIA)->EnableWindow(FALSE);
		GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_USER)->EnableWindow(FALSE);

		GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(TRUE);
		GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(TRUE);
		GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(FALSE);

		GetDlgItem(IDOK)->EnableWindow(TRUE);

		m_bModify = FALSE;
		m_bAddNew = FALSE;

		OnSelchangeLista();
	}
}

void CInfermieriDlg::RiempiComboUsers()
{
	m_ctrlComboUser.ResetContent();

	CVistaUtentiSet set;
	set.SetSortRecord("USERNAME");
	if (set.OpenRecordset("CInfermieriDlg::RiempiComboUsers"))
	{
		int index = m_ctrlComboUser.AddString("");
		m_ctrlComboUser.SetItemData(index, 0);

		while (!set.IsEOF())
		{
			index = m_ctrlComboUser.AddString(set.m_sUsername);
			m_ctrlComboUser.SetItemData(index, set.m_lId);
			set.MoveNext();
		}
		set.CloseRecordset("CInfermieriDlg::RiempiComboUsers");
	}
}