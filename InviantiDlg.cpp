#include "stdafx.h"
#include "Endox.h"
#include "InviantiDlg.h"

#include "InviantiSet.h"
#include "EsamiView.h"
#include "CentriDiCostoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInviantiDlg::CInviantiDlg(CEsamiView* pEsamiView, BOOL bInterni, BOOL bMenu) 
	: CDialog(CInviantiDlg::IDD, (CWnd*)pEsamiView)
{
	m_pEsamiView = pEsamiView;
	m_bInterni = bInterni;
	m_bMenu = bMenu;

	m_lCode		 = 0;
	m_strDescr	 = "";
	m_strPhone	 = "";
	m_strFax	 = "";
	m_strCodiceIntegrazione = "";
	m_strRicercaView = "";

	m_lSavedPosition = -1;
	m_bAddNew		= FALSE;
	m_bModify		= FALSE;

	m_bOrPressed = FALSE;
}

CInviantiDlg::~CInviantiDlg()
{
}

void CInviantiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_1,  m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2,  m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3,  m_ctrlStatic3);
	DDX_Control(pDX, IDC_LABEL_RIC, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5,  m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6,  m_ctrlStatic6);
	DDX_Control(pDX, IDC_MEDICI_NUOVO,   m_ctrlButtonNew);
	DDX_Control(pDX, IDC_MEDICI_MODIFY,  m_ctrlButtonMod);
	DDX_Control(pDX, IDC_MEDICI_CANC,    m_ctrlButtonCanc);
	DDX_Control(pDX, IDC_MEDICI_UPDATE,  m_ctrlButtonUpd);
	DDX_Control(pDX, IDC_MEDICI_REFRESH, m_ctrlButtonRefresh);
	DDX_Control(pDX, IDOK,               m_ctrlButtonOK);
	DDX_Control(pDX, IDC_COMBO_CENTRODICOSTO, m_ctrlCentriDiCosto);

	DDX_Text(pDX, IDC_INVIANTE,	 m_strDescr);
	DDX_Text(pDX, IDC_TELEFONO,  m_strPhone);
	DDX_Text(pDX, IDC_FAX,		 m_strFax);
	DDX_Text(pDX, IDC_CODICE,	 m_strCodiceIntegrazione);	
	DDX_Control(pDX, IDC_LISTA,  m_ctrlLista);
	DDX_Text(pDX, IDC_RICERCA_STR, m_strRicercaView);
}

BEGIN_MESSAGE_MAP(CInviantiDlg, CDialog)
	ON_BN_CLICKED(IDC_MEDICI_CANC,	 OnDelete)
	ON_BN_CLICKED(IDC_MEDICI_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_MEDICI_NUOVO,  OnNew)
	ON_BN_CLICKED(IDC_MEDICI_REFRESH,OnRefresh)
	ON_BN_CLICKED(IDC_MEDICI_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_BTN_OR,        OnBtnOr)
	ON_LBN_DBLCLK(IDC_LISTA, OnLbnDblclkLista)
	ON_LBN_SELCHANGE(IDC_LISTA, OnSelchangeLista)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInviantiDlg message handlers

BOOL CInviantiDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CInviantiDlg::IDD, "InviantiDlg");
	
	SetWindowText(theApp.GetMessageString(m_bInterni == TRUE ? IDS_INVIANTIDLG_TITLE_1 : IDS_INVIANTIDLG_TITLE_2));

	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);
	
	GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_INVIANTE) ->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEFONO) ->EnableWindow(FALSE);
	GetDlgItem(IDC_FAX)      ->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_CENTRODICOSTO)     ->EnableWindow(FALSE);
	GetDlgItem(IDC_CODICE)      ->EnableWindow(FALSE);

	if (!m_bInterni)
		GetDlgItem(IDC_CODICE)->ShowWindow(SW_HIDE);

	RiempiListaCentriDiCosto();

	RiempiListaMedici();

	//Davide : 24/03/2003
	GetDlgItem(IDC_RICERCA_STR)->EnableWindow(FALSE);
	
	m_bRicercaAttivata = theApp.m_nProgramMode & FILTER_RECORD_ESAMI;
	
	if (m_bRicercaAttivata)
	{
		GetDlgItem(IDC_LABEL_RIC)  ->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RICERCA_STR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_OR)     ->ShowWindow(SW_SHOW);
	}
	
	GetDlgItem(IDC_BTN_OR)->EnableWindow(FALSE);
	m_nItemCount = m_ctrlLista.GetCount();

	return TRUE;
}

void CInviantiDlg::RiempiListaMedici()
{
	m_ctrlLista.SetTabStops(100);

	CInviantiSet setInvianti;

	if (m_bInterni)
	{
		setInvianti.SetSortRecord("Descrizione"); // Sandro Gallina - 01/03/2004 //
		setInvianti.SetTableName("EInviantiInterni");
	}
	else
	{
		setInvianti.SetSortRecord("Contatore"); // Sandro Gallina - 01/03/2004 //
		setInvianti.SetTableName("EInviantiEsterni");
	}

	if (setInvianti.OpenRecordset("CInviantiDlg::RiempiListaMedici"))
	{
		while (!setInvianti.IsEOF())
		{
			int posiz = m_ctrlLista.AddString(setInvianti.m_sDescrizione);

			if (posiz >= 0)
				m_ctrlLista.SetItemData(posiz, (DWORD)setInvianti.m_lContatore);

			setInvianti.MoveNext();
		}

		setInvianti.CloseRecordset("CInviantiDlg::RiempiListaMedici");
	}
	
	OnSelchangeLista();
}

void CInviantiDlg::RiempiListaCentriDiCosto()
{
	m_ctrlCentriDiCosto.ResetContent();
	
	if (m_bInterni)
	{
		m_ctrlCentriDiCosto.ShowWindow(SW_SHOW);
		m_ctrlStatic5.ShowWindow(SW_SHOW);
	}
	else
	{
		m_ctrlCentriDiCosto.ShowWindow(SW_HIDE);
		m_ctrlStatic5.ShowWindow(SW_HIDE);
	}

	int posiz = m_ctrlCentriDiCosto.AddString("");

	if (posiz >= 0)
		m_ctrlCentriDiCosto.SetItemData(posiz, 0);

	CCentriDiCostoSet centriDiCostoSet;
	centriDiCostoSet.SetOpenFilter("");
	centriDiCostoSet.SetSortRecord("Descrizione");
	if (centriDiCostoSet.OpenRecordset("CInviantiDlg::RiempiListaCentriDiCosto"))
	{
		while(!centriDiCostoSet.IsEOF())
		{
			int posiz = m_ctrlCentriDiCosto.AddString(centriDiCostoSet.m_sDescrizione);

			if (posiz >= 0)
				m_ctrlCentriDiCosto.SetItemData(posiz, (DWORD)centriDiCostoSet.m_lContatore);

			centriDiCostoSet.MoveNext();
		}

		centriDiCostoSet.CloseRecordset("CInviantiDlg::RiempiListaCentriDiCosto");
	}
}


void CInviantiDlg::OnLbnDblclkLista()
{
	if (m_bMenu == FALSE)
		OnOK();
}

void CInviantiDlg::OnSelchangeLista() 
{
	if (m_bAddNew || m_bModify)
		return;

	int nCount = m_ctrlLista.GetCount();

	if (nCount > 0)
	{
		int nCurPos = m_ctrlLista.GetCurSel();

		if (nCurPos >= 0)
		{
			// recupera il codice dell'inviante appena selezionato	
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

				CInviantiSet setInvianti;

				if (m_bInterni)
					setInvianti.SetTableName("EInviantiInterni");
				else
					setInvianti.SetTableName("EInviantiEsterni");

				setInvianti.SetOpenFilter(sFilter);
				if (setInvianti.OpenRecordset("CInviantiDlg::OnSelchangeLista"))
				{
					if (!setInvianti.IsEOF())
					{
						// 10/02/2003
						if (m_bRicercaAttivata)
						{
							if (m_bOrPressed)
							{
								CString strTmp;
								strTmp.Format("%i ", setInvianti.m_lContatore);

								if (m_strRicerca.Find(strTmp) == -1)
								{
									m_lCode = setInvianti.m_lContatore;
									m_strDescr = setInvianti.m_sDescrizione;
									m_strRicercaView += setInvianti.m_sDescrizione;
									strTmp.Format("%i", m_lCode);
									m_strRicerca += strTmp;

									m_bOrPressed = FALSE;
									m_nItemPressed++;

									if (m_nItemPressed < m_nItemCount)
										GetDlgItem(IDC_BTN_OR)->EnableWindow(TRUE);
								}
							}
							else
							{
								GetDlgItem(IDC_BTN_OR)->EnableWindow(TRUE);
								m_lCode = setInvianti.m_lContatore;
								m_strRicerca.Format("%i", m_lCode);
								m_strRicercaView = setInvianti.m_sDescrizione;
								m_strDescr = setInvianti.m_sDescrizione;
								m_nItemPressed = 1;
							}
						}
						else
						{
							m_lCode = setInvianti.m_lContatore;
							m_strDescr = setInvianti.m_sDescrizione;
							m_strPhone = setInvianti.m_sTelefono;
							m_strFax = setInvianti.m_sFax;

							if (m_bInterni)
								m_strCodiceIntegrazione = setInvianti.m_sCodiceIntegrazione;

							m_ctrlCentriDiCosto.SetCurSel(0);

							for (int i = 0; i < m_ctrlCentriDiCosto.GetCount(); i++)
							{
								if (m_ctrlCentriDiCosto.GetItemData(i) == setInvianti.m_lIdCentroDiCosto)
								{
									m_ctrlCentriDiCosto.SetCurSel(i);
									break;
								}
							}

							m_strRicerca.Format("%i", m_lCode);
							m_strRicercaView = m_strDescr;
						}

						m_lSavedPosition = nCurPos;
					}

					setInvianti.CloseRecordset("CInviantiDlg::OnSelchangeLista");
				}

				UpdateData(FALSE);
			}
		}
	}
}

void CInviantiDlg::OnBtnOr()
{
	m_bOrPressed = TRUE;
	
	m_strRicerca += " OR ";
	m_strRicercaView += " OR ";

	GetDlgItem(IDC_BTN_OR)->EnableWindow(FALSE);
	
	UpdateData(FALSE);
}

void CInviantiDlg::OnOK()
{
	if (m_strRicerca.Right(4) == " OR ")
	{
		m_strRicerca = m_strRicerca.Left(m_strRicerca.GetLength() - 4);
		m_strRicercaView = m_strRicercaView.Left(m_strRicercaView.GetLength() - 4);
	}

	UpdateData(FALSE);

	CDialog::OnOK();
}

void CInviantiDlg::OnDelete() 
{
	BOOL	bDeleted = FALSE;

	GetDlgItem(IDC_LISTA)	->EnableWindow(TRUE);
	GetDlgItem(IDC_INVIANTE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
	GetDlgItem(IDC_FAX)     ->EnableWindow(FALSE);
	GetDlgItem(IDC_CODICE)     ->EnableWindow(FALSE);

	GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(FALSE);

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_INVIANTIDLG_DELETE_CONFIRM), MB_YESNO) == IDYES)
	{
		// recupera il codice dell'inviante appena selezionato	
		int posiz = m_ctrlLista.GetCurSel();
			
		if (posiz >= 0)
		{
			DWORD dwCode = m_ctrlLista.GetItemData(posiz);
		
			if (dwCode >= 0)
			{
				CString sFilter;
				sFilter.Format("Contatore=%li", (long)dwCode);
			
				CInviantiSet setInvianti;

				if (m_bInterni)
					setInvianti.SetTableName("EInviantiInterni");
				else
					setInvianti.SetTableName("EInviantiEsterni");

				setInvianti.SetOpenFilter(sFilter);
				if (setInvianti.OpenRecordset("CInviantiDlg::OnDelete"))
				{
					if (!setInvianti.IsEOF())
					{
						if (setInvianti.DeleteRecordset("CInviantiDlg::OnDelete"))
						{
							int nRemained = m_ctrlLista.DeleteString(posiz);
							int nNewPos = min(posiz, nRemained - 1);

							m_ctrlLista.SetCurSel(nNewPos);

							OnSelchangeLista();
						}
					}

					setInvianti.CloseRecordset("CInviantiDlg::OnDelete");
				}
			}
		}
	}
	
	UpdateData(FALSE);
}

void CInviantiDlg::OnModify() 
{
	int nSelect = m_ctrlLista.GetCurSel();
		
	if (nSelect >= 0)
	{
		GetDlgItem(IDC_LISTA)	->EnableWindow(FALSE);
		GetDlgItem(IDC_INVIANTE)->EnableWindow(TRUE);
		GetDlgItem(IDC_TELEFONO)->EnableWindow(TRUE);
		GetDlgItem(IDC_FAX)     ->EnableWindow(TRUE);
		GetDlgItem(IDC_CODICE)     ->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_CENTRODICOSTO)     ->EnableWindow(TRUE);

		GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(FALSE);
		GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(FALSE);
		GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(TRUE);

		GetDlgItem(IDOK)->EnableWindow(FALSE);

		m_bModify = TRUE;

		GetDlgItem(IDC_INVIANTE)->SetFocus();

		UpdateData(FALSE);
	}			
}

void CInviantiDlg::OnNew() 
{
	GetDlgItem(IDC_LISTA)	->EnableWindow(FALSE);
	GetDlgItem(IDC_INVIANTE)->EnableWindow(TRUE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(TRUE);
	GetDlgItem(IDC_FAX)     ->EnableWindow(TRUE);
	GetDlgItem(IDC_CODICE)     ->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_CENTRODICOSTO)     ->EnableWindow(TRUE);

	GetDlgItem(IDC_MEDICI_NUOVO)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_CANC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDICI_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDICI_REFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_lCode		= 0;
	m_strDescr. Empty();
	m_strPhone. Empty();
	m_strFax.	Empty();
	m_strCodiceIntegrazione.Empty();

	m_bAddNew = TRUE;

	GetDlgItem(IDC_INVIANTE)->SetFocus();

	UpdateData(FALSE);
}

void CInviantiDlg::OnRefresh() 
{
	m_bAddNew = FALSE;
	m_bModify = FALSE;

	GetDlgItem(IDC_LISTA)	->EnableWindow(TRUE);
	GetDlgItem(IDC_INVIANTE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
	GetDlgItem(IDC_FAX)     ->EnableWindow(FALSE);
	GetDlgItem(IDC_CODICE)     ->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_CENTRODICOSTO)     ->EnableWindow(FALSE);

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

void CInviantiDlg::OnUpdate() 
{
	long lLastAdd = 0;
	BOOL bSaved = FALSE;
	
	UpdateData(TRUE);

	if (m_strDescr.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_INVIANTIDLG_EMPTY_FIELD), MB_ICONINFORMATION);
		return;
	}

	CInviantiSet setInvianti;

	if (m_bInterni)
		setInvianti.SetTableName("EInviantiInterni");
	else
		setInvianti.SetTableName("EInviantiEsterni");

	if (m_bAddNew)
	{
		if (setInvianti.OpenRecordset("CInviantiDlg::OnUpdate"))
		{
			if (setInvianti.AddNewRecordset("CInviantiDlg::OnUpdate"))
			{
				setInvianti.m_sDescrizione = m_strDescr;
				setInvianti.m_sTelefono = m_strPhone;
				setInvianti.m_sFax = m_strFax;
				if (m_bInterni)
					setInvianti.m_sCodiceIntegrazione = m_strCodiceIntegrazione;
				setInvianti.m_lIdCentroDiCosto = m_ctrlCentriDiCosto.GetItemData(m_ctrlCentriDiCosto.GetCurSel());

				bSaved = setInvianti.UpdateRecordset("CInviantiDlg::OnUpdate");

				if (bSaved)
					lLastAdd = setInvianti.GetLastAdd();
			}
			setInvianti.CloseRecordset("CInviantiDlg::OnUpdate");
		}
	}
	else		
	{
		CString sFilter;
		sFilter.Format("Contatore=%li", m_lCode);

		setInvianti.SetOpenFilter(sFilter);
		if (setInvianti.OpenRecordset("CInviantiDlg::OnUpdate"))
		{
			if (setInvianti.IsEOF())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_ALREADY_DELETED), MB_ICONINFORMATION);
			}
			else
			{
				if (setInvianti.EditRecordset("CInviantiDlg::OnUpdate"))
				{
					setInvianti.SetFieldDirty(NULL, TRUE);
					setInvianti.SetFieldDirty(&setInvianti.m_lContatore, FALSE);

					setInvianti.m_sDescrizione = m_strDescr;
					setInvianti.m_sTelefono = m_strPhone;
					setInvianti.m_sFax = m_strFax;
					if (m_bInterni)
						setInvianti.m_sCodiceIntegrazione = m_strCodiceIntegrazione;
					setInvianti.m_lIdCentroDiCosto = m_ctrlCentriDiCosto.GetItemData(m_ctrlCentriDiCosto.GetCurSel());

					bSaved = setInvianti.UpdateRecordset("CInviantiDlg::OnUpdate");
				}
			}

			setInvianti.CloseRecordset("CInviantiDlg::OnUpdate");
		}
	}
	
	if (bSaved)	
	{
		if (m_bAddNew)
		{
			int posiz = m_ctrlLista.AddString(m_strDescr);
			if (posiz >= 0)
			{
				m_lCode = lLastAdd;
				m_lSavedPosition = posiz;

				m_ctrlLista.SetItemData(posiz, (DWORD)m_lCode);
				m_ctrlLista.SetCurSel(posiz);
			}
		}
		else
		{
			int posiz = m_ctrlLista.GetCurSel();
			if (posiz >= 0)
			{
				m_ctrlLista.DeleteString(posiz);

				posiz = m_ctrlLista.InsertString(posiz, m_strDescr);
				if (posiz >= 0)
				{
					m_ctrlLista.SetItemData(posiz, (DWORD)m_lCode);
					m_ctrlLista.SetCurSel(posiz);
				}
			}
		}

		GetDlgItem(IDC_LISTA)->EnableWindow(TRUE);
		GetDlgItem(IDC_INVIANTE)->EnableWindow(FALSE);
		GetDlgItem(IDC_TELEFONO)->EnableWindow(FALSE);
		GetDlgItem(IDC_FAX)->EnableWindow(FALSE);
		GetDlgItem(IDC_CODICE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_CENTRODICOSTO)->EnableWindow(FALSE);

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