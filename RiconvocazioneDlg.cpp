//Gabriel BUG 6225 - Lista DO

#include "stdafx.h"
#include "Endox.h"
#include "RiconvocazioneDlg.h"
#include "ExtOrdiniSet.h"
#include "MediciSet.h"
#include "RiconvocazioneSet.h"
#include "CustomDate.h"
#include "VistaComboPrestazioni.h"
#include "DatabasesSet.h"
#include "CodificaRegionaleExSet.h"
#include "RiconvocazioneAnnullamentoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRiconvocazioneDlg, CDialog)

CRiconvocazioneDlg::CRiconvocazioneDlg(CWnd* pParent, CEsamiView* pEsamiView)
: CDialog(CRiconvocazioneDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	
	m_lIdMotivo = -1;
	m_bPassivoReferto = 0;
}

CRiconvocazioneDlg::~CRiconvocazioneDlg()
{
}

BEGIN_MESSAGE_MAP(CRiconvocazioneDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_BTN_CHIUDI, &CRiconvocazioneDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_BTN_INVIA, &CRiconvocazioneDlg::OnBnClickedInvia)
	ON_BN_CLICKED(IDC_BTN_ANNULLA, &CRiconvocazioneDlg::OnBnClickedAnnulla)

	ON_BN_CLICKED(IDC_RADIO1, OnClickedRadioMotivo)
	ON_BN_CLICKED(IDC_RADIO2, OnClickedRadioMotivo)
	ON_BN_CLICKED(IDC_RADIO3, OnClickedRadioMotivo)
	ON_BN_CLICKED(IDC_RADIO4, OnClickedRadioMotivo)
	ON_BN_CLICKED(IDC_RADIO5, OnClickedRadioMotivo)
	ON_BN_CLICKED(IDC_RADIO6, OnClickedRadioMotivo)
	ON_BN_CLICKED(IDC_RADIO7, OnClickedRadioMotivo)

	ON_BN_CLICKED(IDC_RADIO8, OnClickedRadioReferto)
	ON_BN_CLICKED(IDC_RADIO9, OnClickedRadioReferto)

	ON_EN_CHANGE(IDC_EDT_MOTIVO, &CRiconvocazioneDlg::OnEnChangeEditMotivo)
	ON_EN_CHANGE(IDC_EDT_PREPARAZIONE, &CRiconvocazioneDlg::OnEnChangeEditPreparazione)
END_MESSAGE_MAP()

void CRiconvocazioneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_7, m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC_8, m_ctrlStatic8);
	DDX_Control(pDX, IDC_STATIC_10, m_ctrlStatic10);
	DDX_Control(pDX, IDC_STATIC_11, m_ctrlStatic11);
	DDX_Control(pDX, IDC_STATIC_12, m_ctrlStatic12);
	DDX_Control(pDX, IDC_STATIC_13, m_ctrlStatic13);
	DDX_Control(pDX, IDC_STATIC_14, m_ctrlStatic14);
	DDX_Control(pDX, IDC_STATIC_15, m_ctrlStatic15);
	DDX_Control(pDX, IDC_STATIC_16, m_ctrlStatic16);
	DDX_Control(pDX, IDC_STATIC_18, m_ctrlStatic18);
	DDX_Control(pDX, IDC_STATIC_GROUP, m_ctrlStaticGroup);

	DDX_Control(pDX, IDC_BTN_CHIUDI, m_ctrlButtonChiudi);
	DDX_Control(pDX, IDC_BTN_INVIA, m_ctrlButtonInvia);
	DDX_Control(pDX, IDC_BTN_ANNULLA, m_ctrlButtonAnnulla);
	DDX_Control(pDX, IDC_COMBO, m_ctrlComboMedico);
	DDX_Control(pDX, IDC_COMBO2, m_ctrlComboUnita);
	DDX_Control(pDX, IDC_COMBO3, m_ctrlComboCodicePrestazione);
	
	DDX_Text(pDX, IDC_EDT_FICHA, m_sFicha);
	DDX_Text(pDX, IDC_EDT_PAZIENTENOME, m_sNome);
	DDX_Text(pDX, IDC_EDT_MARCA, m_sMarca);
	DDX_Text(pDX, IDC_EDT_UNITA, m_sUnita);
	DDX_Text(pDX, IDC_EDT_DATAESAME, m_sDataEsame);
	DDX_Text(pDX, IDC_EDT_SIGLA, m_sSiglaEsame);
	DDX_Text(pDX, IDC_EDT_MOTIVO, m_sDescrizioneMotivo);
	DDX_Text(pDX, IDC_EDT_PREPARAZIONE, m_sPreparazione);
	DDX_Control(pDX, IDC_EDT_DATARICONVOCAZIONE, m_sDataReconvocazione);

	DDX_Control(pDX, IDC_RADIO1, m_ctrlRadio1);
	DDX_Control(pDX, IDC_RADIO2, m_ctrlRadio2);
	DDX_Control(pDX, IDC_RADIO3, m_ctrlRadio3);
	DDX_Control(pDX, IDC_RADIO4, m_ctrlRadio4);
	DDX_Control(pDX, IDC_RADIO5, m_ctrlRadio5);
	DDX_Control(pDX, IDC_RADIO6, m_ctrlRadio6);
	DDX_Control(pDX, IDC_RADIO7, m_ctrlRadio7);
	DDX_Control(pDX, IDC_RADIO8, m_ctrlRadio8);
	DDX_Control(pDX, IDC_RADIO9, m_ctrlRadio9);
}

BOOL CRiconvocazioneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_sDataReconvocazione.SetEditMask("00/00/0000 00:00", "__/__/____ __:__");

	RiempiComboMedico();
	RiempiComboUnita();
	RiempiComboCodicePrestazione();
	CaricaDati();
	Aggiorna();
	
	theApp.LocalizeDialog(this, CRiconvocazioneDlg::IDD, "CReconvocazioneDlg");
	return TRUE;
}

void CRiconvocazioneDlg::RiempiComboMedico()
{
	int nCurSelSede = -1;

	m_ctrlComboMedico.ResetContent();

	CMediciSet setMed;
	setMed.SetBaseFilter("");
	setMed.SetSortRecord("NOME DESC, COGNOME DESC");

	int nIndex = 0;

	if (setMed.OpenRecordset("CRiconvocazioneDlg::RiempiComboMedico"))
	{
		while (!setMed.IsEOF())
		{
			CString sMedico = setMed.m_sNome + " " + setMed.m_sCognome;

			m_ctrlComboMedico.InsertString(nIndex, sMedico);
			m_ctrlComboMedico.SetItemData(nIndex, setMed.m_lContatore);

			setMed.MoveNext();
		}

		setMed.CloseRecordset("CRiconvocazioneDlg::RiempiComboMedico");
	}
}

void CRiconvocazioneDlg::RiempiComboUnita()
{
	int nCurSelSede = -1;

	m_ctrlComboUnita.ResetContent();

	CDatabasesSet setUnita;
	setUnita.SetBaseFilter("ELIMINATO = 0");
	setUnita.SetSortRecord("DESCRIZIONE DESC");

	int nIndex = 0;

	if (setUnita.OpenRecordset("CRiconvocazioneDlg::RiempiComboUnita"))
	{
		while (!setUnita.IsEOF())
		{
			m_ctrlComboUnita.InsertString(nIndex, setUnita.m_sDescrizione);
			m_ctrlComboUnita.SetItemData(nIndex, setUnita.m_lID);

			setUnita.MoveNext();
		}

		setUnita.CloseRecordset("CRiconvocazioneDlg::RiempiComboUnita");
	}
}

void CRiconvocazioneDlg::CaricaDati()
{
	m_sFicha = m_pEsamiView->m_pEsamiSet->m_sCodEsame;
	m_sNome = m_pEsamiView->m_pPazientiSet->m_sNome + " " + m_pEsamiView->m_pPazientiSet->m_sCognome;
	m_sMarca = theApp.m_sControlloQualitaMarca;
	m_sUnita = GetUnitName(m_sFicha);//BUG #9573 Felipe
	
	m_sDataEsame = CCustomDate(m_pEsamiView->m_pEsamiSet->m_lData).GetDate("%d/%m/%Y - %H:%M");
	m_sSiglaEsame = CVistaComboPrestazioni().GetCodicePrestazione(CExtOrdiniSet().GetOrdineId(m_pEsamiView->m_pEsamiSet->m_lContatore));
	SetDlgItemText(IDC_EDT_FICHA, m_sFicha);
	SetDlgItemText(IDC_EDT_PAZIENTENOME, m_sNome);
	SetDlgItemText(IDC_EDT_MARCA, m_sMarca);
	SetDlgItemText(IDC_EDT_UNITA, m_sUnita);
	SetDlgItemText(IDC_EDT_DATAESAME, m_sDataEsame);
	SetDlgItemText(IDC_EDT_SIGLA, m_sSiglaEsame);
	
	if (EsameRiconvocato(m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("IDESAME = %li AND ELIMINATO = 0", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CRiconvocazioneSet set;
		set.SetOpenFilter(sFilter);

		if (set.OpenRecordset("CRiconvocazioneDlg::CaricaDati"))
		{
			CString sDataEsameRiconvocazione = set.m_sDataOraRiconvocazione.Mid(6, 2) + "/" + set.m_sDataOraRiconvocazione.Mid(4, 2) + "/" + set.m_sDataOraRiconvocazione.Mid(0, 4) + " " + set.m_sDataOraRiconvocazione.Mid(8, 2) + ":" + set.m_sDataOraRiconvocazione.Mid(10, 2);
			SetDlgItemText(IDC_EDT_DATARICONVOCAZIONE, sDataEsameRiconvocazione);
			
			m_ctrlComboUnita.SetCurSel(m_ctrlComboUnita.FindString(0, set.m_sUnitaRiconvocazione));
			m_ctrlComboCodicePrestazione.SetCurSel(m_ctrlComboCodicePrestazione.FindString(0, set.m_sCodicePrestazioneRiconvocazione));
			CheckRadioMotivo(set.m_lIdMotivo);
			CheckRadioReferto(set.m_bPassivoDeReferto);

			CMediciSet mediciSet;
			m_ctrlComboMedico.SetCurSel(m_ctrlComboMedico.FindString(0, mediciSet.GetNomeCognomeFromContatore(set.m_lIdMedicoRiconvocazione)));
			
			SetDlgItemText(IDC_EDT_MOTIVO, set.m_sDescrizioneMotivo);
			SetDlgItemText(IDC_EDT_PREPARAZIONE, set.m_sPreparazione);

			set.CloseRecordset("CRiconvocazioneDlg::CaricaDati");
		}
		
		SetReadOnly(TRUE);
	}
	else
		SetReadOnly(FALSE);
}

CString CRiconvocazioneDlg::GetUnitName(CString orderNumber) //BUG #9573 Felipe
{
	CString description = "";
	int on = 0;
	CDatabasesSet unitSet;
	orderNumber = orderNumber.Mid(0, 3);

	unitSet.SetBaseFilter("ELIMINATO = 0");
	unitSet.SetBaseFilter("DESCRIZIONE LIKE '%"+ orderNumber +"%'");

	if(unitSet.OpenRecordset("CRiconvocazioneDlg"))
	{
		description = unitSet.m_sDescrizione;

		unitSet.CloseRecordset("CRiconvocazioneDlg");
	}

	return description;
}

void CRiconvocazioneDlg::OnCancel()
{
}

void CRiconvocazioneDlg::OnOK()
{
	
}

void CRiconvocazioneDlg::OnBnClickedClose()
{
	CDialog::OnOK();
}

void CRiconvocazioneDlg::OnBnClickedInvia()
{
	CString sDataOraRiconvocazione, sNuovaData, sCodicePrestazione;
	GetDlgItemText(IDC_EDT_DATARICONVOCAZIONE, sDataOraRiconvocazione);
	
	if (DataValida(sDataOraRiconvocazione) && CampiValidi())
	{
		sNuovaData = sDataOraRiconvocazione.Mid(6, 4) + sDataOraRiconvocazione.Mid(3, 2) + sDataOraRiconvocazione.Mid(0, 2) + sDataOraRiconvocazione.Mid(11, 2) + sDataOraRiconvocazione.Mid(14, 2) + "00";
		
		m_ctrlComboUnita.GetLBText(m_ctrlComboUnita.GetCurSel(), m_sUnitaRiconvocazione);
		m_ctrlComboCodicePrestazione.GetLBText(m_ctrlComboCodicePrestazione.GetCurSel(), sCodicePrestazione);

		FormataEmail();

		CRiconvocazioneSet set;
		set.SetOpenFilter("Id=0");
		if (set.OpenRecordset("CRiconvocazioneDlg::OnBnClickedInvia"))
		{
			if (set.AddNewRecordset("CRiconvocazioneDlg::OnBnClickedInvia"))
			{
				set.m_lIdEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
				set.m_sFicha = m_sFicha;
				set.m_sDataOraEsame = CCustomDate(m_pEsamiView->m_pEsamiSet->m_lData).GetDate("%Y%m%d%H%M00");
				set.m_sUtente = theApp.m_sUtenteLoggato;
				set.m_sUnita = m_sUnita;
				set.m_sMarca = m_sMarca;
				set.m_sDataOraRiconvocazione = sNuovaData;
				set.m_lIdMedicoRiconvocazione = m_ctrlComboMedico.GetItemData(m_ctrlComboMedico.GetCurSel());
				set.m_sUnitaRiconvocazione = m_sUnitaRiconvocazione;
				set.m_sCodicePrestazioneRiconvocazione = sCodicePrestazione;
				set.m_sCodicePrestazione = m_sSiglaEsame;
				GetDlgItemText(IDC_EDT_PREPARAZIONE, set.m_sPreparazione);
				set.m_lIdMotivo = m_lIdMotivo;
				GetDlgItemText(IDC_EDT_MOTIVO, set.m_sDescrizioneMotivo);
				set.m_bBloccaEsame = TRUE;
				set.m_bPassivoDeReferto = m_bPassivoReferto;
				set.m_sCorpoEmail = m_sCorpoEmail;
				set.m_sInviatoA = theApp.m_sIndirizziMailReconvocazione;

				set.UpdateRecordset("CRiconvocazioneDlg::OnBnClickedInvia");
			}
		}
			
		CaricaDati();
		Aggiorna();
	}
}

void CRiconvocazioneDlg::OnBnClickedAnnulla()
{
	CRiconvocazioneAnnullamentoDlg dlg(this, m_pEsamiView->m_pEsamiSet->m_lContatore);

	if (dlg.DoModal() == IDOK)
	{
		Aggiorna();
		CaricaDati();
	}
}
void CRiconvocazioneDlg::CheckRadioMotivo(int nNewVal)
{
	m_ctrlRadio1.SetCheck(nNewVal == 0 ? BST_CHECKED : BST_UNCHECKED);
	m_ctrlRadio2.SetCheck(nNewVal == 1 ? BST_CHECKED : BST_UNCHECKED);
	m_ctrlRadio3.SetCheck(nNewVal == 2 ? BST_CHECKED : BST_UNCHECKED);
	m_ctrlRadio4.SetCheck(nNewVal == 3 ? BST_CHECKED : BST_UNCHECKED);
	m_ctrlRadio5.SetCheck(nNewVal == 4 ? BST_CHECKED : BST_UNCHECKED);
	m_ctrlRadio6.SetCheck(nNewVal == 5 ? BST_CHECKED : BST_UNCHECKED);
	m_ctrlRadio7.SetCheck(nNewVal == 6 ? BST_CHECKED : BST_UNCHECKED);
	m_lIdMotivo = nNewVal;
}

void CRiconvocazioneDlg::OnClickedRadioMotivo()
{
	if (m_ctrlRadio1.GetCheck() == BST_CHECKED && m_lIdMotivo != 0)
		CheckRadioMotivo(0);
	else if (m_ctrlRadio2.GetCheck() == BST_CHECKED && m_lIdMotivo != 1)
		CheckRadioMotivo(1);
	else if (m_ctrlRadio3.GetCheck() == BST_CHECKED && m_lIdMotivo != 2)
		CheckRadioMotivo(2);
	else if (m_ctrlRadio4.GetCheck() == BST_CHECKED && m_lIdMotivo != 3)
		CheckRadioMotivo(3);
	else if (m_ctrlRadio5.GetCheck() == BST_CHECKED && m_lIdMotivo != 4)
		CheckRadioMotivo(4);
	else if (m_ctrlRadio6.GetCheck() == BST_CHECKED && m_lIdMotivo != 5)
		CheckRadioMotivo(5);
	else if (m_ctrlRadio7.GetCheck() == BST_CHECKED && m_lIdMotivo != 6)
		CheckRadioMotivo(6);
}

void CRiconvocazioneDlg::CheckRadioReferto(BOOL bNewVal)
{
	m_ctrlRadio8.SetCheck(bNewVal == 0 ? BST_CHECKED : BST_UNCHECKED);
	m_ctrlRadio9.SetCheck(bNewVal == 1 ? BST_CHECKED : BST_UNCHECKED);
	m_bPassivoReferto = bNewVal;
}

void CRiconvocazioneDlg::OnClickedRadioReferto()
{
	if (m_ctrlRadio8.GetCheck() == BST_CHECKED && m_bPassivoReferto != 0)
		CheckRadioReferto(0);
	else if (m_ctrlRadio9.GetCheck() == BST_CHECKED && m_bPassivoReferto != 1)
		CheckRadioReferto(1);
}

void CRiconvocazioneDlg::OnEnChangeEditMotivo()
{
	CString sMotivo;
	GetDlgItemText(IDC_EDT_MOTIVO, sMotivo);
	if (sMotivo.GetLength() > 200){
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RICONVOCAZIONE_LIMITEMASSIMO));
		pressKey(VK_BACK);
	}
}

void CRiconvocazioneDlg::OnEnChangeEditPreparazione()
{
	CString sPreparazione;
	GetDlgItemText(IDC_EDT_PREPARAZIONE, sPreparazione);
	if (sPreparazione.GetLength() > 200)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RICONVOCAZIONE_LIMITEMASSIMO));
		pressKey(VK_BACK);
	}
}

void CRiconvocazioneDlg::FormataEmail()
{
	CString sMedico, sAzione, sPreparazione, sMotivo, sCodicePrestazione, sDescrizioneMotivo;
	m_ctrlComboMedico.GetLBText(m_ctrlComboMedico.GetCurSel(), sMedico);
	m_ctrlComboCodicePrestazione.GetLBText(m_ctrlComboCodicePrestazione.GetCurSel(), sCodicePrestazione);
	
	GetDlgItemText(IDC_EDT_MOTIVO, sDescrizioneMotivo);
	GetDlgItemText(IDC_EDT_PREPARAZIONE, sPreparazione);
	sMotivo = MotivoTesto(m_lIdMotivo);

	CString sHtmlTitoloInizio = "<div style =\"text-align:center\"><span style =\"font-size:11pt;font-family:Arial;text-align:center\">";
	CString sHtmlFine = "</span></div>";
	CString sHtmlTestoInizio = "<div style=\"text-align:left\"><span style=\"font-size:11pt;font-family:Arial;text-align:left\">";

	m_sCorpoEmail = sHtmlTitoloInizio + "RECONVOCAÇÃO DE CLIENTES<br><br>DADOS DO CLIENTE<br><br>" + sHtmlFine;
	m_sCorpoEmail += sHtmlTestoInizio + "Nº da Ficha :	" + m_pEsamiView->m_pEsamiSet->m_sCodEsame + "<br>";
	m_sCorpoEmail += "Nome do cliente:	" + m_pEsamiView->m_pPazientiSet->m_sNome + " " + m_pEsamiView->m_pPazientiSet->m_sCognome +"<br><br>";
	m_sCorpoEmail += "Marca:	" + m_sMarca + "<br><br>";
	m_sCorpoEmail += "Unidade de realização do exame:	" + m_sUnita + "<br><br>" + sHtmlFine;
	m_sCorpoEmail += sHtmlTitoloInizio + "DADOS DO EXAME<br>" + sHtmlFine;
	m_sCorpoEmail += sHtmlTestoInizio + "Data do exame:	" + CCustomDate(m_pEsamiView->m_pEsamiSet->m_lData).GetDate("%d/%m/%Y - %H:%M") + "<br>";
	m_sCorpoEmail += "Sigla:	" + CVistaComboPrestazioni().GetCodicePrestazione(CExtOrdiniSet().GetOrdineId(m_pEsamiView->m_pEsamiSet->m_lContatore)) + "<br><br>" + sHtmlFine;
	m_sCorpoEmail += sHtmlTitoloInizio + "DADOS PARA RECONVOCAÇÃO<br><br>" + sHtmlFine;
	m_sCorpoEmail += sHtmlTestoInizio + "Médico solicitante da reconvocação:	" + sMedico + "<br><br>";
	m_sCorpoEmail += "Agendar na unidade:	" + m_sUnitaRiconvocazione + "<br><br>";
	m_sCorpoEmail += "Agendar sigla:	" + sCodicePrestazione + "<br><br>";
	m_sCorpoEmail += "Preparo:	" + sPreparazione + "<br><br>";
	m_sCorpoEmail += "Motivo:	" + sMotivo + "<br>		" + sDescrizioneMotivo + sHtmlFine;
}

BOOL CRiconvocazioneDlg::DataValida(CString sData)
{
	int iAnno = atoi(sData.Mid(6, 4));
	int iMese = atoi(sData.Mid(3, 2));
	int iGiorno = atoi(sData.Mid(0, 2));
	int iOra = atoi(sData.Mid(11, 2));
	int iMinuto = atoi(sData.Mid(14, 2));
	
	COleDateTime data(iAnno, iMese, iGiorno, iOra, iMinuto, 0);

	if (data.GetStatus() == COleDateTime::valid)
		return TRUE;
	else
	{
		AfxMessageBox(theApp.GetMessageString(IDS_DATA_NON_VALIDA));
		return FALSE;
	}
		
}

BOOL CRiconvocazioneDlg::CampiValidi()
{
	CString sPreparazione, sMotivo;
	GetDlgItemText(IDC_EDT_PREPARAZIONE, sPreparazione);
	GetDlgItemText(IDC_EDT_MOTIVO, sMotivo);
	if (m_ctrlComboMedico.GetCurSel() != -1 && m_ctrlComboUnita.GetCurSel() != -1 && m_ctrlComboCodicePrestazione.GetCurSel() != -1 && sPreparazione.GetLength() == 0 && sMotivo.GetLength() == 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_INSERIRETUTTIVALORI));
		return FALSE;
	}
	
	return TRUE;
}

CString CRiconvocazioneDlg::MotivoTesto(long lId)
{
	CString sMotivo;
	switch (lId)
	{
		case 0:
			GetDlgItemText(IDC_RADIO1, sMotivo);
			return sMotivo;
		case 1:
			GetDlgItemText(IDC_RADIO2, sMotivo);
			return sMotivo;
		case 2:
			GetDlgItemText(IDC_RADIO3, sMotivo);
			return sMotivo;
		case 3:
			GetDlgItemText(IDC_RADIO4, sMotivo);
			return sMotivo;
		case 4:
			GetDlgItemText(IDC_RADIO5, sMotivo);
			return sMotivo;
		case 5:
			GetDlgItemText(IDC_RADIO6, sMotivo);
			return sMotivo;
		case 6:
			GetDlgItemText(IDC_RADIO7, sMotivo);
			return sMotivo;
	}

	return "";
		
}

void CRiconvocazioneDlg::RiempiComboCodicePrestazione()
{
	int nCurSelSede = -1;

	m_ctrlComboCodicePrestazione.ResetContent();

	CCodificaRegionaleExSet setCodicePrestazione;

	CString sFilter;
	sFilter.Format("CODICEINTEGRAZIONE IS NOT NULL");

	setCodicePrestazione.SetSortRecord("CODICEINTEGRAZIONE");
	if (setCodicePrestazione.OpenRecordset("CRiconvocazioneDlg::RiempiComboCodicePrestazione"))
	{
		int nIndex = 0;

		while (!setCodicePrestazione.IsEOF())
		{
			m_ctrlComboCodicePrestazione.InsertString(nIndex, setCodicePrestazione.m_sCodiceIntegrazione);
			m_ctrlComboCodicePrestazione.SetItemData(nIndex, setCodicePrestazione.m_lContatore);

			nIndex++;
			setCodicePrestazione.MoveNext();
		}

		setCodicePrestazione.CloseRecordset("CRiconvocazioneDlg::RiempiComboCodicePrestazione");
	}

	if (nCurSelSede >= 0)
		m_ctrlComboCodicePrestazione.SetCurSel(nCurSelSede);
}

BOOL CRiconvocazioneDlg::EsameRiconvocato(long lIdEsame)
{
	CString strFilter;
	strFilter.Format("IDESAME=%li", lIdEsame);

	CRiconvocazioneSet setRiconvocazione;
	setRiconvocazione.SetOpenFilter(strFilter);

	if (setRiconvocazione.OpenRecordset("CRiconvocazioneDlg::EsameRiconvocato"))
	{
		while (!setRiconvocazione.IsEOF())
		{
			return TRUE;
		}

		setRiconvocazione.CloseRecordset("CRiconvocazioneDlg::RiempiComboUnita");
	}
	return FALSE;
}

void CRiconvocazioneDlg::Aggiorna()
{
	if (EsameRiconvocato(m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		GetDlgItem(IDC_STATIC_18)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_ANNULLA)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_INVIA)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_18)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_ANNULLA)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_INVIA)->EnableWindow(TRUE);
	}

}

HBRUSH CRiconvocazioneDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_18:
		{
			pDC->SetTextColor(RGB(255, 0, 0));

			break;
		}
	}
	return hBrush;
}

void CRiconvocazioneDlg::SetReadOnly(BOOL bReadOnly)
{
	SendDlgItemMessage(IDC_EDT_MOTIVO, EM_SETREADONLY, (WPARAM)bReadOnly, (LPARAM)0);
	SendDlgItemMessage(IDC_EDT_PREPARAZIONE, EM_SETREADONLY, (WPARAM)bReadOnly, (LPARAM)0);
	SendDlgItemMessage(IDC_EDT_DATARICONVOCAZIONE, EM_SETREADONLY, (WPARAM)bReadOnly, (LPARAM)0);
	GetDlgItem(IDC_COMBO)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_COMBO2)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_COMBO3)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_RADIO1)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_RADIO2)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_RADIO3)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_RADIO4)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_RADIO5)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_RADIO6)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_RADIO7)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_RADIO8)->EnableWindow(!bReadOnly);
	GetDlgItem(IDC_RADIO9)->EnableWindow(!bReadOnly);
}