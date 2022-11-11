#include "stdafx.h"
#include "Endox.h"
#include "MediciCurantiInviantiDlg.h"

#include "MediciCurantiInviantiSet.h"
#include "WebDeployer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMediciCurantiInviantiDlg::CMediciCurantiInviantiDlg(CWnd* pParent, long lCurantiInvianti, BOOL bMenu)
	: CDialog(CMediciCurantiInviantiDlg::IDD, pParent)
{
	m_lCurantiInvianti = lCurantiInvianti;
	m_bMenu = bMenu;

	//

	m_lContatore = 0;
	m_sCognome = "";
	m_sNome = "";
	m_sTitolo = "";
	m_sVia = "";
	m_sCitta = "";
	m_sProvincia = "";
	m_sTelefono = "";
	m_sEmail = "";
	m_sLogin = "";
	m_sCodiceFiscale = "";
	m_sCodiceIntegrazione = "";
	m_bSpeciale = FALSE;

	m_sRicerca = "";
	m_sRicercaView = "";

	m_bAddNew = FALSE;
	m_bModify = FALSE;
	m_bOrPressed = FALSE;
	m_bRicercaAttivata = FALSE;
	m_bUserFocus = FALSE;
	m_bValidUser = TRUE;

	m_iItemCount = -1;
	m_iItemPressed = -1;
	m_iSavedPosition = -1;
}

CMediciCurantiInviantiDlg::~CMediciCurantiInviantiDlg()
{
}

BEGIN_MESSAGE_MAP(CMediciCurantiInviantiDlg, CDialog)

	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_MEDICI_NUOVO, OnMediciNew)
	ON_BN_CLICKED(IDC_MEDICI_MODIFY, OnMediciEdt)
	ON_BN_CLICKED(IDC_MEDICI_CANC, OnMediciDel)
	ON_BN_CLICKED(IDC_MEDICI_UPDATE, OnMediciSave)
	ON_BN_CLICKED(IDC_MEDICI_REFRESH, OnMediciUndo)

	ON_BN_CLICKED(IDC_BTN_OR, OnBtnOr)

	ON_LBN_DBLCLK(IDC_LISTA, OnLbnDblclkLista)
	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)
	ON_BN_CLICKED(IDC_BTN_CERCA, OnBnClickedBtnCerca)

	ON_EN_CHANGE(IDC_LOGIN, OnEnChangeLogin)
	ON_EN_SETFOCUS(IDC_LOGIN, OnEnSetfocusLogin)
	ON_EN_KILLFOCUS(IDC_LOGIN, OnEnKillfocusLogin)
	ON_BN_CLICKED(IDC_BUTTON_GENERA, OnBnClickedButtonGenera)
END_MESSAGE_MAP()

void CMediciCurantiInviantiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_COGNOME, m_sCognome);
	DDX_Text(pDX, IDC_NOME, m_sNome);
	DDX_Text(pDX, IDC_TITOLO, m_sTitolo);
	DDX_Text(pDX, IDC_INDIRIZZO, m_sVia);
	DDX_Text(pDX, IDC_CITTA, m_sCitta);
	DDX_Text(pDX, IDC_PROVINCIA, m_sProvincia);
	DDX_Text(pDX, IDC_TELEFONO, m_sTelefono);
	DDX_Text(pDX, IDC_CODICEFISCALE, m_sCodiceFiscale);
	DDX_Text(pDX, IDC_EMAIL, m_sEmail);
	DDX_Text(pDX, IDC_LOGIN, m_sLogin);
	DDX_Text(pDX, IDC_EDIT_11, m_sCodiceIntegrazione);
	DDX_Check(pDX, IDC_CHK_SPECIALE, m_bSpeciale);

	DDX_Text(pDX, IDC_RICERCA_STR, m_sRicercaView);	

	DDX_Control(pDX, IDC_LISTA, m_ctrlLista);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_7, m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC_8, m_ctrlStatic8);
	DDX_Control(pDX, IDC_STATIC_9, m_ctrlStatic9);
	DDX_Control(pDX, IDC_STATIC_10, m_ctrlStatic10);
	DDX_Control(pDX, IDC_STATIC_11, m_ctrlStatic11);
	DDX_Control(pDX, IDC_LABEL_RIC, m_ctrlStaticRic);
	DDX_Control(pDX, IDC_MEDICI_NUOVO, m_ctrlButtonNew);
	DDX_Control(pDX, IDC_MEDICI_MODIFY, m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_MEDICI_CANC, m_ctrlButtonDel);
	DDX_Control(pDX, IDC_MEDICI_UPDATE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_MEDICI_REFRESH, m_ctrlButtonUndo);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDC_CHK_SPECIALE, m_ctrlChkSpeciale);
}

BOOL CMediciCurantiInviantiDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);
	
	GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_TITOLO)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COGNOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_INDIRIZZO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CITTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_PROVINCIA)->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CODICEFISCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_11)->EnableWindow(FALSE);

	GetDlgItem(IDC_EMAIL)->EnableWindow(FALSE);
	GetDlgItem(IDC_LOGIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GENERA)->EnableWindow(FALSE);

	GetDlgItem(IDC_RICERCA_STR)->EnableWindow(FALSE);

	m_ctrlLista.SetTabStops(138);
	RiempiListaMedici();

	GetDlgItem(IDC_RICERCA_STR2)->ShowWindow(SW_HIDE);

	// Davide - 24/03/2003
	m_bRicercaAttivata = theApp.m_nProgramMode & FILTER_RECORD_ESAMI;
	
	if (m_bRicercaAttivata)
	{
		GetDlgItem(IDC_LABEL_RIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RICERCA_STR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_OR)->ShowWindow(SW_SHOW);

		// Sandro 12/09/2013 //
		m_ctrlButtonNew.ShowWindow(SW_HIDE);
		m_ctrlButtonEdt.ShowWindow(SW_HIDE);
		m_ctrlButtonDel.ShowWindow(SW_HIDE);
		m_ctrlButtonSave.ShowWindow(SW_HIDE);
		m_ctrlButtonUndo.ShowWindow(SW_HIDE);
	}
	else
	{
		// Sandro 08/06/2015 //
		if (theApp.m_bPersonalizzazioniBrasileSirio)
			m_ctrlChkSpeciale.ShowWindow(SW_SHOW);

		//
		if (!m_bMenu)
		{
			GetDlgItem(IDC_LABEL_RIC)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_RICERCA_STR2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_CERCA)->ShowWindow(SW_SHOW);
		}
	}
	
	m_iItemPressed = 0;
	m_iItemCount = m_ctrlLista.GetCount();

	// Sandro 25/09/2013 // RAS 20130148 //
	if (m_lCurantiInvianti == MEDICI_INVIANTI)
	{
		GetDlgItem(IDC_STATIC_8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LOGIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_GENERA)->ShowWindow(SW_HIDE);		
	}

	GetDlgItem(IDC_STATIC_11)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_11)->ShowWindow(SW_SHOW);

	//
	theApp.LocalizeDialog(this, CMediciCurantiInviantiDlg::IDD, "MediciCurantiInviantiDlg");

	if (m_lCurantiInvianti == MEDICI_INVIANTI)
		SetWindowText(theApp.GetMessageString(IDS_MEDICI_INVIANTI));

	if (!m_bMenu)
		PostMessage(WM_USER);

	return TRUE;
}

void CMediciCurantiInviantiDlg::RiempiListaMedici(CString sCampoRicerca)
{
	BeginWaitCursor();
	m_ctrlLista.SetRedraw(FALSE);
	m_ctrlLista.ResetContent();

	sCampoRicerca.Trim();
	int nLen = sCampoRicerca.GetLength();
	int nIndex = 0;

	switch(m_lCurantiInvianti)
	{
		case MEDICI_CURANTI:
		{
			POSITION pos = theApp.m_listMediciCuranti.GetHeadPosition();
			while(pos != NULL)
			{
				tagMEDICICURANTIINVIANTI medcur = theApp.m_listMediciCuranti.GetNext(pos);

				if (nLen > 0) // filtro //
				{
					if ((medcur.m_sCognome.Left(nLen).CompareNoCase(sCampoRicerca) == 0) || (medcur.m_sNome.Left(nLen).CompareNoCase(sCampoRicerca) == 0))
					{
						// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
						if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
							m_ctrlLista.InsertString(nIndex, medcur.m_sTitolo + "\t" + medcur.m_sNome + "\t" + medcur.m_sCognome);
						else
							m_ctrlLista.InsertString(nIndex, medcur.m_sCognome + "\t" + medcur.m_sNome + "\t" + medcur.m_sTitolo);
						m_ctrlLista.SetItemData(nIndex, (DWORD)medcur.m_lContatore);
						nIndex++;
					}
				}
				else
				{
					// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
					if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
						m_ctrlLista.InsertString(nIndex, medcur.m_sTitolo + "\t" + medcur.m_sNome + "\t" + medcur.m_sCognome);
					else
						m_ctrlLista.InsertString(nIndex, medcur.m_sCognome + "\t" + medcur.m_sNome + "\t" + medcur.m_sTitolo);
					m_ctrlLista.SetItemData(nIndex, (DWORD)medcur.m_lContatore);
					nIndex++;
				}
			}

			break;
		}
		case MEDICI_INVIANTI:
		{
			POSITION pos = theApp.m_listMediciInvianti.GetHeadPosition();
			while(pos != NULL)
			{
				tagMEDICICURANTIINVIANTI medcur = theApp.m_listMediciInvianti.GetNext(pos);

				if (nLen > 0) // filtro //
				{
					if ((medcur.m_sCognome.Left(nLen).CompareNoCase(sCampoRicerca) == 0) || (medcur.m_sNome.Left(nLen).CompareNoCase(sCampoRicerca) == 0))
					{
						// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
						if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
							m_ctrlLista.InsertString(nIndex, medcur.m_sTitolo + "\t" + medcur.m_sNome + "\t" + medcur.m_sCognome);
						else
							m_ctrlLista.InsertString(nIndex, medcur.m_sCognome + "\t" + medcur.m_sNome + "\t" + medcur.m_sTitolo);
						m_ctrlLista.SetItemData(nIndex, (DWORD)medcur.m_lContatore);
						nIndex++;
					}
				}
				else
				{
					// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
					if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
						m_ctrlLista.InsertString(nIndex, medcur.m_sTitolo + "\t" + medcur.m_sNome + "\t" + medcur.m_sCognome);
					else
						m_ctrlLista.InsertString(nIndex, medcur.m_sCognome + "\t" + medcur.m_sNome + "\t" + medcur.m_sTitolo);
					m_ctrlLista.SetItemData(nIndex, (DWORD)medcur.m_lContatore);
					nIndex++;
				}
			}

			break;
		}
	}

	m_ctrlLista.SetRedraw(TRUE);
	EndWaitCursor();
	
	OnSelchangeLista();
}

void CMediciCurantiInviantiDlg::OnLbnDblclkLista()
{
	if (m_bMenu == FALSE)
		OnOK();
}

void CMediciCurantiInviantiDlg::OnSelchangeLista() 
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

			GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(TRUE);
			GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(TRUE);
			GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(TRUE);
			GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(FALSE);
			GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(FALSE);

			if (dwCode >= 0)
			{
				CString strFilter;
				strFilter.Format("Contatore=%li", (long)dwCode);

				CMediciCurantiInviantiSet setTemp(m_lCurantiInvianti);
				setTemp.SetOpenFilter(strFilter);

				if (setTemp.OpenRecordset("CMediciCurantiInviantiDlg::OnSelchangeLista"))
				{
					if (!setTemp.IsEOF())
					{
						m_lContatore = setTemp.m_lContatore;
						m_sCognome = setTemp.m_sCognome;
						m_sNome = setTemp.m_sNome;
						m_sTitolo = setTemp.m_sTitolo;
						m_sVia = setTemp.m_sVia;
						m_sCitta = setTemp.m_sCitta;
						m_sProvincia = setTemp.m_sProvincia;
						m_sTelefono = setTemp.m_sTelefono;
						m_sEmail = setTemp.m_sEmail;
						m_sLogin = setTemp.m_sLogin;
						m_sCodiceFiscale = setTemp.m_sCodiceFiscale;
						m_sCodiceIntegrazione = setTemp.m_sCodiceIntegrazione;
						m_bSpeciale = setTemp.m_bSpeciale;

						m_iSavedPosition = nCurPos;
						
						strDoctor = m_sTitolo + " " + m_sCognome + " " + m_sNome;
						strDoctor.TrimLeft();
						strDoctor.TrimRight();

						if (m_bRicercaAttivata)
						{
							if (m_bOrPressed)
							{
								strTmp.Format("%i", m_lContatore);

								if (CanBeInserted(m_lContatore))
								{
									m_sRicerca += strTmp;
									m_sRicercaView += strDoctor;
								
									m_bOrPressed = FALSE;
									m_iItemPressed++;

									if (m_iItemPressed < m_iItemCount)
										GetDlgItem(IDC_BTN_OR)->EnableWindow(TRUE);
								}
							}
							else
							{
								m_sRicerca.Format("%i", m_lContatore);
								m_sRicercaView = strDoctor;
								m_iItemPressed = 1;
							}
						}
						else
						{
							m_sRicerca.Format("%i", m_lContatore);
							m_sRicercaView = strDoctor;
						}
					}
		
					setTemp.CloseRecordset("CMediciCurantiInviantiDlg::OnSelchangeLista");
				}

				UpdateData(FALSE);
			}
		}
	}
}

BOOL CMediciCurantiInviantiDlg::CanBeInserted(long lContatore)
{
	CString strContatore, strTmp;

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
		return FALSE;

	return TRUE;
}

void CMediciCurantiInviantiDlg::OnBtnOr()
{
	m_sRicerca += " OR ";
	m_sRicercaView += " OR ";

	m_bOrPressed = TRUE;
	GetDlgItem(IDC_BTN_OR)->EnableWindow(FALSE);
	
	UpdateData(FALSE);
}

void CMediciCurantiInviantiDlg::OnOK()
{
	if (m_sRicerca.Right(4) == " OR ")
	{
		m_sRicerca = m_sRicerca.Left(m_sRicerca.GetLength() - 4);
		m_sRicercaView = m_sRicercaView.Left(m_sRicercaView.GetLength() - 4);
	}

	UpdateData(FALSE);

	if (GetFocus() == GetDlgItem(IDC_RICERCA_STR2))
		OnBnClickedBtnCerca();
	else
		CDialog::OnOK();
}

void CMediciCurantiInviantiDlg::OnMediciNew() 
{
	GetDlgItem(IDC_LISTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_COGNOME)->EnableWindow(TRUE);
	GetDlgItem(IDC_NOME)->EnableWindow(TRUE);
	GetDlgItem(IDC_TITOLO)->EnableWindow(TRUE);
	GetDlgItem(IDC_INDIRIZZO)->EnableWindow(TRUE);
	GetDlgItem(IDC_CITTA)->EnableWindow(TRUE);
	GetDlgItem(IDC_PROVINCIA)->EnableWindow(TRUE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(TRUE);
	GetDlgItem(IDC_CODICEFISCALE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EMAIL)->EnableWindow(TRUE);
	GetDlgItem(IDC_LOGIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_11)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GENERA)->EnableWindow(TRUE);

	m_ctrlChkSpeciale.EnableWindow(TRUE);

	GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_lContatore = 0;
	m_sCognome.Empty();
	m_sNome.Empty();
	m_sTitolo.Empty();
	m_sVia.Empty();
	m_sCitta.Empty();
	m_sProvincia.Empty();
	m_sTelefono.Empty();
	m_sEmail.Empty();
	m_sLogin.Empty();
	m_sCodiceFiscale.Empty();
	m_sCodiceIntegrazione.Empty();
	m_bSpeciale = FALSE;

	m_bAddNew = TRUE;

	GetDlgItem(IDC_COGNOME)->SetFocus();

	UpdateData(FALSE);
}

void CMediciCurantiInviantiDlg::OnMediciEdt() 
{
	int nSelect = m_ctrlLista.GetCurSel();
		
	if (nSelect >= 0)
	{
		GetDlgItem(IDC_LISTA)->EnableWindow(FALSE);
		GetDlgItem(IDC_TITOLO)->EnableWindow(TRUE);
		GetDlgItem(IDC_NOME)->EnableWindow(TRUE);
		GetDlgItem(IDC_COGNOME)->EnableWindow(TRUE);
		GetDlgItem(IDC_INDIRIZZO)->EnableWindow(TRUE);
		GetDlgItem(IDC_CITTA)->EnableWindow(TRUE);
		GetDlgItem(IDC_PROVINCIA)->EnableWindow(TRUE);
		GetDlgItem(IDC_TELEFONO)->EnableWindow(TRUE);
		GetDlgItem(IDC_CODICEFISCALE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EMAIL)->EnableWindow(TRUE);
		GetDlgItem(IDC_LOGIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_11)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_GENERA)->EnableWindow(TRUE);

		m_ctrlChkSpeciale.EnableWindow(TRUE);

		GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(FALSE);
		GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(TRUE);

		GetDlgItem(IDOK)->EnableWindow(FALSE);

		m_bModify = TRUE;

		GetDlgItem(IDC_COGNOME)->SetFocus();

		UpdateData(FALSE);
	}			
}

void CMediciCurantiInviantiDlg::OnMediciDel() 
{
	BOOL bDeleted = FALSE;

	GetDlgItem(IDC_LISTA)->EnableWindow(TRUE);
	GetDlgItem(IDC_TITOLO)->EnableWindow(FALSE);
	GetDlgItem(IDC_NOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COGNOME)->EnableWindow(FALSE);
	GetDlgItem(IDC_INDIRIZZO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CITTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_PROVINCIA)->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CODICEFISCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EMAIL)->EnableWindow(FALSE);
	GetDlgItem(IDC_LOGIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_11)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GENERA)->EnableWindow(FALSE);

	m_ctrlChkSpeciale.EnableWindow(FALSE);

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
				CString strFilter;
				strFilter.Format("Contatore=%li", (long) dwCode);
			
				CMediciCurantiInviantiSet setTemp(m_lCurantiInvianti);
				setTemp.SetOpenFilter(strFilter);
			
				if (setTemp.OpenRecordset("CMediciCurantiInviantiDlg::OnMediciDelete"))
				{
					if (!setTemp.IsEOF())
					{
						if (setTemp.DeleteRecordset("CMediciCurantiInviantiDlg::OnMediciDelete"))
						{
							int nRemained = m_ctrlLista.DeleteString(posiz);
							int nNewPos   = min (posiz, nRemained-1);

							m_ctrlLista.SetCurSel(nNewPos);

							OnSelchangeLista();
						}
					}

					setTemp.CloseRecordset("CMediciCurantiInviantiDlg::OnMediciDelete");
				}
			}
		}
	}
	
	UpdateData(FALSE);
}

void CMediciCurantiInviantiDlg::OnMediciSave() 
{
	if (m_bValidUser == FALSE)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_LOGIN_ALREADY_USED));
		return;
	}

	BOOL bSaved = FALSE;
	
	UpdateData(TRUE);

	if (m_sCognome.IsEmpty() && 
		m_sNome.IsEmpty() &&
		m_sTitolo.IsEmpty() && 
		m_sVia.IsEmpty() &&	
		m_sCitta.IsEmpty() &&	
		m_sProvincia.IsEmpty() &&	
		m_sTelefono.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	if (m_bAddNew)
	{
		CMediciCurantiInviantiSet setTemp(m_lCurantiInvianti);
        if (setTemp.OpenRecordset("CMediciCurantiInviantiDlg::OnMediciUpdate"))
		{
			if (setTemp.AddNewRecordset("CMediciCurantiInviantiDlg::OnMediciUpdate"))
			{
				setTemp.m_sCognome = m_sCognome;
				setTemp.m_sNome = m_sNome;
				setTemp.m_sTitolo = m_sTitolo;
				setTemp.m_sVia = m_sVia;
				setTemp.m_sCitta = m_sCitta;
				setTemp.m_sProvincia = m_sProvincia;
				setTemp.m_sTelefono = m_sTelefono;
				setTemp.m_sEmail = m_sEmail;
				setTemp.m_sLogin = m_sLogin;
				setTemp.m_sCodiceFiscale = m_sCodiceFiscale;
				setTemp.m_sCodiceIntegrazione = m_sCodiceIntegrazione;
				setTemp.m_bSpeciale = m_bSpeciale;

				bSaved = setTemp.UpdateRecordset("CMediciCurantiInviantiDlg::OnMediciUpdate");
				if (bSaved)
				{
					m_lContatore = setTemp.GetLastAdd();

					tagMEDICICURANTIINVIANTI tagNewMed;
					tagNewMed.m_lContatore = setTemp.GetLastAdd();
					tagNewMed.m_sTitolo = m_sTitolo;
					tagNewMed.m_sCognome = m_sCognome;
					tagNewMed.m_sNome = m_sNome;

					switch(m_lCurantiInvianti)
					{
						case MEDICI_CURANTI:
						{
							theApp.m_listMediciCuranti.AddTail(tagNewMed);

							// WebDeployer //
							if (theApp.m_bConsultazioneWEB && setTemp.m_sLogin != "")
							{
								CWebDeployer webCreator(&theApp.m_dbEndox);
								webCreator.DeployDoctor(&theApp.m_sPercorsoTemporaneoWEB, &theApp.m_sInterfacciaWebTo, &theApp.m_sInterfacciaWebFrom, &setTemp, WD_OPERAZIONE_NEW);
								webCreator.DeployPasswordDoctor(&theApp.m_sPercorsoTemporaneoWEB, &theApp.m_sInterfacciaWebTo, &theApp.m_sInterfacciaWebFrom, setTemp.m_lContatore, setTemp.m_sLogin);
							}

							break;
						}
						case MEDICI_INVIANTI:
						{
							theApp.m_listMediciInvianti.AddTail(tagNewMed);

							break;
						}
					}
				}
			}

			setTemp.CloseRecordset("CMediciCurantiInviantiDlg::OnMediciUpdate");
		}
	}
	else		
	{
		CString strFilter;
		strFilter.Format("Contatore=%li", m_lContatore);

		CMediciCurantiInviantiSet setTemp(m_lCurantiInvianti);
		setTemp.SetOpenFilter(strFilter);
        
		if (setTemp.OpenRecordset("CMediciCurantiInviantiDlg::OnMediciUpdate"))
		{
			if (setTemp.IsBOF() && setTemp.IsEOF())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_ALREADY_DELETED), MB_ICONINFORMATION);
			}
			else
			{
				if (setTemp.EditRecordset("CMediciCurantiInviantiDlg::OnMediciUpdate"))
				{
					setTemp.SetFieldDirty(NULL, TRUE);
					setTemp.SetFieldDirty(&setTemp.m_lContatore, FALSE);

					setTemp.m_sCognome = m_sCognome;
					setTemp.m_sNome = m_sNome;
					setTemp.m_sTitolo = m_sTitolo;
					setTemp.m_sVia = m_sVia;
					setTemp.m_sCitta = m_sCitta;
					setTemp.m_sProvincia = m_sProvincia;
					setTemp.m_sTelefono = m_sTelefono;
					setTemp.m_sEmail = m_sEmail;
					setTemp.m_sLogin = m_sLogin;
					setTemp.m_sCodiceFiscale = m_sCodiceFiscale;
					setTemp.m_sCodiceIntegrazione = m_sCodiceIntegrazione;
					setTemp.m_bSpeciale = m_bSpeciale;

					// WebDeployer
					if (theApp.m_bConsultazioneWEB && setTemp.m_sLogin != "")
					{
						CWebDeployer webCreator(&theApp.m_dbEndox);
						webCreator.DeployDoctor(&theApp.m_sPercorsoTemporaneoWEB, &theApp.m_sInterfacciaWebTo, &theApp.m_sInterfacciaWebFrom, &setTemp, WD_OPERAZIONE_MODIFY);
					}

					bSaved = setTemp.UpdateRecordset("CMediciCurantiInviantiDlg::OnMediciUpdate");
					if (bSaved)
					{
						switch(m_lCurantiInvianti)
						{
							case MEDICI_CURANTI:
							{
								POSITION pos = theApp.m_listMediciCuranti.GetHeadPosition();
								while(pos != NULL)
								{
									tagMEDICICURANTIINVIANTI tagEdtMed = theApp.m_listMediciCuranti.GetAt(pos);

									if (tagEdtMed.m_lContatore == m_lContatore)
									{
										tagEdtMed.m_sTitolo = m_sTitolo;
										tagEdtMed.m_sCognome = m_sCognome;
										tagEdtMed.m_sNome = m_sNome;
										theApp.m_listMediciCuranti.SetAt(pos, tagEdtMed);

										break;
									}

									theApp.m_listMediciCuranti.GetNext(pos);
								}

								break;
							}
							case MEDICI_INVIANTI:
							{
								POSITION pos = theApp.m_listMediciInvianti.GetHeadPosition();
								while(pos != NULL)
								{
									tagMEDICICURANTIINVIANTI tagEdtMed = theApp.m_listMediciInvianti.GetAt(pos);

									if (tagEdtMed.m_lContatore == m_lContatore)
									{
										tagEdtMed.m_sTitolo = m_sTitolo;
										tagEdtMed.m_sCognome = m_sCognome;
										tagEdtMed.m_sNome = m_sNome;
										theApp.m_listMediciInvianti.SetAt(pos, tagEdtMed);

										break;
									}

									theApp.m_listMediciInvianti.GetNext(pos);
								}

								break;
							}
						}
					}
				}
			}

			setTemp.CloseRecordset("CMediciCurantiInviantiDlg::OnMediciUpdate");
		}
	}

	if (bSaved)	
	{
		int posiz;

		if (m_bAddNew)
		{
			posiz = m_ctrlLista.AddString(m_sCognome + "\t" + m_sNome + "\t" + m_sTitolo);

			if (posiz >= 0)
			{
				m_iSavedPosition = posiz;

				m_ctrlLista.SetItemData(posiz, (DWORD)m_lContatore);
				m_ctrlLista.SetCurSel(posiz);
			}
		}
		else
		{
			posiz = m_ctrlLista.GetCurSel();

			if (posiz >= 0)
			{
				m_ctrlLista.DeleteString(posiz);

				posiz = m_ctrlLista.InsertString(posiz, m_sCognome + "\t" + m_sNome + "\t" + m_sTitolo);

				if (posiz >= 0)
				{
					m_ctrlLista.SetItemData(posiz, (DWORD)m_lContatore);
					m_ctrlLista.SetCurSel(posiz);
				}
			}
		}

		GetDlgItem(IDC_LISTA)	->EnableWindow(TRUE);
		GetDlgItem(IDC_COGNOME)	->EnableWindow(FALSE);
		GetDlgItem(IDC_NOME)	->EnableWindow(FALSE);
		GetDlgItem(IDC_TITOLO)	->EnableWindow(FALSE);
		GetDlgItem(IDC_INDIRIZZO)->EnableWindow(FALSE);
		GetDlgItem(IDC_CITTA)	->EnableWindow(FALSE);
		GetDlgItem(IDC_PROVINCIA)->EnableWindow(FALSE);
		GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
		GetDlgItem(IDC_CODICEFISCALE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EMAIL)->EnableWindow(FALSE);
		GetDlgItem(IDC_LOGIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_11)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_GENERA)->EnableWindow(FALSE);

		m_ctrlChkSpeciale.EnableWindow(FALSE);

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

void CMediciCurantiInviantiDlg::OnMediciUndo() 
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	GetDlgItem(IDC_LISTA)	->EnableWindow(TRUE);
	GetDlgItem(IDC_COGNOME)	->EnableWindow(FALSE);
	GetDlgItem(IDC_NOME)	->EnableWindow(FALSE);
	GetDlgItem(IDC_TITOLO)	->EnableWindow(FALSE);
	GetDlgItem(IDC_INDIRIZZO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CITTA)	->EnableWindow(FALSE);
	GetDlgItem(IDC_PROVINCIA)->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CODICEFISCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EMAIL)->EnableWindow(FALSE);
	GetDlgItem(IDC_LOGIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_11)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GENERA)->EnableWindow(FALSE);

	m_ctrlChkSpeciale.EnableWindow(FALSE);

	GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(FALSE);

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

void CMediciCurantiInviantiDlg::OnBnClickedBtnCerca()
{
	CString contenuto;
	GetDlgItem(IDC_RICERCA_STR2)->GetWindowText(contenuto);
	//theApp.AfxMessageBoxEndo(contenuto);
	m_ctrlLista.ResetContent();
	RiempiListaMedici(contenuto);
}

void CMediciCurantiInviantiDlg::OnEnChangeLogin()
{
	CString strTemp;
	GetDlgItem(IDC_LOGIN)->GetWindowText(strTemp);
	strTemp.Trim();
	if (strTemp != "")
	{
		CString query;
		if (m_bAddNew)
			query = "SELECT COUNT(*) as OCC FROM EMEDICICURANTI WHERE ELIMINATO = 0 AND LOGIN LIKE '" + strTemp  + "'";
		else
			query.Format("SELECT COUNT(*) as OCC FROM EMEDICICURANTI WHERE ELIMINATO = 0 AND LOGIN LIKE '%s' AND CONTATORE = %li", strTemp, m_lContatore);

		CRecordset setCount(&theApp.m_dbEndox); // non mi interessa tanto è per il conteggio //
		setCount.Open(CRecordset::snapshot, query, CRecordset::readOnly);
		if (!setCount.IsEOF())
		{
			CDBVariant dbVariant;
			setCount.GetFieldValue("OCC", dbVariant, SQL_C_SLONG);

			setCount.Close();

			if (dbVariant.m_lVal == 0)
				m_bValidUser = TRUE;
			else
				m_bValidUser = FALSE;
		}
	}
	else
		m_bValidUser = TRUE;

	GetDlgItem(IDC_LOGIN)->Invalidate();
}

void CMediciCurantiInviantiDlg::OnEnSetfocusLogin()
{
	m_bUserFocus = TRUE;
}

void CMediciCurantiInviantiDlg::OnEnKillfocusLogin()
{
	m_bUserFocus = FALSE;
}

HBRUSH CMediciCurantiInviantiDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_11:
		case IDC_EDIT_11:
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
		case IDC_LOGIN:
		{
			if (m_bValidUser)
				pDC->SetBkColor(RGB(0,255,0));
			else
				pDC->SetBkColor(RGB(255,0,0));

			if (m_bUserFocus)
				pDC->SetTextColor(RGB(255,255,255));
			else
				pDC->SetTextColor(RGB(0,0,0));

			break;
		}
	}

	return hBrush;
}

void CMediciCurantiInviantiDlg::OnBnClickedButtonGenera()
{
	//Generazione automatica Password
	CString strCognome, strNome, strUser;
	GetDlgItem(IDC_COGNOME)->GetWindowText(strCognome);
	GetDlgItem(IDC_NOME)->GetWindowText(strNome);

	if (strCognome == "" || strNome == "")
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FILL_MEDIC_FIELDS));
		return;
	}

	strUser = strCognome + strNome.Left(1);
	if (strUser.GetLength() < 4)
		while(strUser.GetLength() < 4)
			strUser += "_";

	strUser.Remove('\'');

	CString query = "SELECT COUNT(*) as OCC FROM EMEDICICURANTI WHERE ELIMINATO = 0 AND LOGIN LIKE '" + strUser  + "'";
	CRecordset setCount(&theApp.m_dbEndox); // non mi interessa tanto è per il conteggio //
	setCount.Open(CRecordset::snapshot, query, CRecordset::readOnly);
	if (!setCount.IsEOF())
	{
		CDBVariant dbVariant;
		setCount.GetFieldValue("OCC", dbVariant, SQL_C_SLONG);
		setCount.Close();

		//Se lo user non è usato lo propongo, altrimenti genero un successivo
		if (dbVariant.m_lVal > 0)
		{
			for(int i=1; i<10000; i++)
			{
				CString strUserTemp;
				strUserTemp.Format("%s%li", strUser, i);
				query = "SELECT COUNT(*) as OCC FROM EMEDICICURANTI WHERE ELIMINATO = 0 AND LOGIN LIKE '" + strUserTemp  + "'";
				setCount.Open(CRecordset::snapshot, query, CRecordset::readOnly);
				if (!setCount.IsEOF())
				{
					CDBVariant dbVariant;
					setCount.GetFieldValue("OCC", dbVariant, SQL_C_SLONG);
					setCount.Close();
					if (dbVariant.m_lVal == 0)
					{
						strUser = strUserTemp;
						break;
					}
				}
			}
		}
	}

	GetDlgItem(IDC_LOGIN)->SetWindowText(strUser);
}