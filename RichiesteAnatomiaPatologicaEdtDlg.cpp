#include "stdafx.h"
#include "Endox.h"
#include "Endox.h"
#include "RichiesteAnatomiaPatologicaEdtDlg.h"

#include "AnatomiaPatologicaRichListCtrl.h"
#include "EsamiView.h"
#include "MediciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRichiesteAnatomiaPatologicaEdtDlg, CDialog)

CRichiesteAnatomiaPatologicaEdtDlg::CRichiesteAnatomiaPatologicaEdtDlg(CWnd* pParent, CEsamiView* pEsamiView, CAnatomiaPatologicaRichListCtrl* pListCtrl)
	: CDialog(CRichiesteAnatomiaPatologicaEdtDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	ASSERT(pListCtrl != NULL);

	m_pEsamiView = pEsamiView;
	m_pList = pListCtrl;

	m_nListItem = -1;
	m_lIDEsame = 0;
	POSITION pos = m_pList->GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		m_nListItem = m_pList->GetNextSelectedItem(pos);
		if (m_nListItem >= 0)
			m_lIDEsame = (long)m_pList->GetItemData(m_nListItem);
	}

	m_nSpedireRitirare = 0;
	m_bRefertato = FALSE;
	m_bVerificato = FALSE;
	m_bSpeditoRitirato = FALSE;
	m_sDataVerificato = "";
	m_sDataSpeditoRitirato = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", m_lIDEsame);

	CEsamiSet setEsami;
	setEsami.SetOpenFilter(strFilter);
	if (setEsami.OpenRecordset("CRichiesteAnatomiaPatologicaEdtDlg::CRichiesteAnatomiaPatologicaEdtDlg"))
	{
		if (!setEsami.IsEOF())
		{
			m_nSpedireRitirare = (setEsami.m_nAPSpedireRitirare % 3);
			m_bRefertato = setEsami.m_bAPRefertato;
			m_bVerificato = setEsami.m_bAPVerificato;
			m_nVerificatoMedico = setEsami.m_nAPVerificatoMedico;
			m_bSpeditoRitirato = setEsami.m_bAPSpeditoRitirato;

			if (!setEsami.IsFieldNull(&setEsami.m_sAPDataVerificato))
				m_sDataVerificato = setEsami.m_sAPDataVerificato;

			if (!setEsami.IsFieldNull(&setEsami.m_sAPDataSpeditoRitirato))
				m_sDataSpeditoRitirato = setEsami.m_sAPDataSpeditoRitirato;

			// Sandro 09/11/2010 // Imposto come default che il medico che verifica l'esame è il medico che esegue l'esame //
			if (m_nVerificatoMedico <= 0)
				m_nVerificatoMedico = setEsami.m_lMedico;
		}

		setEsami.CloseRecordset("CRichiesteAnatomiaPatologicaEdtDlg::CRichiesteAnatomiaPatologicaEdtDlg");
	}
}

CRichiesteAnatomiaPatologicaEdtDlg::~CRichiesteAnatomiaPatologicaEdtDlg()
{
}

BEGIN_MESSAGE_MAP(CRichiesteAnatomiaPatologicaEdtDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_SPEDITORITIRATO, OnBnClickedCheckSpeditoRitirato)
	ON_BN_CLICKED(IDC_CHECK_VERIFICATO, OnBnClickedCheckVerificato)
END_MESSAGE_MAP()

void CRichiesteAnatomiaPatologicaEdtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO_SPEDIRE, m_nSpedireRitirare);
	DDX_Check(pDX, IDC_CHECK_REFERTATO, m_bRefertato);
	DDX_Check(pDX, IDC_CHECK_VERIFICATO, m_bVerificato);
	DDX_Check(pDX, IDC_CHECK_SPEDITORITIRATO, m_bSpeditoRitirato);
	DDX_Text(pDX, IDC_CHECK_VERIFICATO, m_sDataVerificato);
	DDX_Text(pDX, IDC_CHECK_SPEDITORITIRATO, m_sDataSpeditoRitirato);

	DDX_Control(pDX, IDC_COMBO_MEDICO, m_ctrlComboMedico);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_06, m_ctrlStatic06);
	DDX_Control(pDX, IDC_STATIC_07, m_ctrlStatic07);
	DDX_Control(pDX, IDC_STATIC_08, m_ctrlStatic08);
	DDX_Control(pDX, IDC_STATIC_09, m_ctrlStatic09);
	DDX_Control(pDX, IDC_STATIC_10, m_ctrlStatic10);
}

BOOL CRichiesteAnatomiaPatologicaEdtDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	if (m_nListItem >= 0)
	{
		SetDlgItemText(IDC_EDIT_PAZIENTE, m_pList->GetItemText(m_nListItem, 2));
		SetDlgItemText(IDC_EDIT_ESAME, m_pList->GetItemText(m_nListItem, 3));
		SetDlgItemText(IDC_EDIT_MEDICO, m_pList->GetItemText(m_nListItem, 4));
		SetDlgItemText(IDC_EDIT_STATO, m_pList->GetItemText(m_nListItem, 6));
	}

	m_ctrlComboMedico.ShowWindow(m_bVerificato ? SW_SHOW : SW_HIDE);

	// riempio la combo dei medici //
	m_ctrlComboMedico.InsertString(0, "");
	m_ctrlComboMedico.SetItemData(0, 0);

	int nToSel = 0;
	CMediciSet setMedici;
	if (theApp.m_bPersonalizzazioniBrasileEinstein)
		setMedici.SetSortRecord("Nome, Cognome");
	else
		setMedici.SetSortRecord("Cognome, Nome");
	if (setMedici.OpenRecordset("CRichiesteAnatomiaPatologicaEdtDlg::OnInitDialog"))
	{
		int nIndex = 1;
		while(!setMedici.IsEOF())
		{
			// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
			CString strTemp;
			if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
				strTemp = setMedici.m_sNome + " " + setMedici.m_sCognome;
			else
				strTemp = setMedici.m_sCognome + " " + setMedici.m_sNome;
			strTemp.Trim();

			m_ctrlComboMedico.InsertString(nIndex, strTemp);
			m_ctrlComboMedico.SetItemData(nIndex, setMedici.m_lContatore);

			if (setMedici.m_lContatore == m_nVerificatoMedico)
				nToSel = nIndex;

			nIndex++;
			setMedici.MoveNext();
		}

		setMedici.CloseRecordset("CRichiesteAnatomiaPatologicaEdtDlg::OnInitDialog");
	}
	m_ctrlComboMedico.SetCurSel(nToSel);

	theApp.LocalizeDialog(this, CRichiesteAnatomiaPatologicaEdtDlg::IDD, "RichiesteAnatomiaPatologicaEdtDlg");

	return bReturn;
}

void CRichiesteAnatomiaPatologicaEdtDlg::OnOK()
{
	CString strFilter;
	strFilter.Format("Contatore=%li", m_lIDEsame);

	CEsamiSet setEsami;

	setEsami.SetOpenFilter(strFilter);
	if (setEsami.OpenRecordset("CRichiesteAnatomiaPatologicaEdtDlg::OnOK"))
	{
		if (!setEsami.IsEOF())
		{
			if (setEsami.EditRecordset("CRichiesteAnatomiaPatologicaEdtDlg::OnOK"))
			{
				UpdateData(TRUE);

				int nIndex = m_ctrlComboMedico.GetCurSel();

				setEsami.m_nAPSpedireRitirare = (m_nSpedireRitirare % 3);
				setEsami.m_bAPVerificato = m_bVerificato;
				setEsami.m_nAPVerificatoMedico = (nIndex >= 0 ? m_ctrlComboMedico.GetItemData(nIndex) : 0);
				setEsami.m_bAPSpeditoRitirato = m_bSpeditoRitirato;
				setEsami.m_sAPDataVerificato = m_sDataVerificato;
				setEsami.m_sAPDataSpeditoRitirato = m_sDataSpeditoRitirato;

				if (setEsami.UpdateRecordset("CRichiesteAnatomiaPatologicaEdtDlg::OnOK"))
				{
					// aggiorno i dati visualizzati nella lista //

					POSITION pos = m_pList->GetFirstSelectedItemPosition();
					if (pos != NULL)
					{
						int nItem = m_pList->GetNextSelectedItem(pos);

						UINT uiSpedireRitirare[3] = { IDS_ANATOMIA_SPEDIRE, IDS_ANATOMIA_SPEDIREALTRO, IDS_ANATOMIA_RITIRO};
						m_pList->SetItemText(nItem, 7, theApp.GetMessageString(uiSpedireRitirare[m_nSpedireRitirare % 3]));

						if (m_bVerificato)
						{
							CString strTemp = theApp.GetMessageString(IDS_YES);

							if (m_sDataVerificato.GetLength() > 0)
								strTemp += " (" + m_sDataVerificato + ")";

							m_pList->SetItemText(nItem, 8, strTemp);
						}
						else
						{
							m_pList->SetItemText(nItem, 8, theApp.GetMessageString(IDS_NO));
						}

						if (m_bSpeditoRitirato)
						{
							CString strTemp = theApp.GetMessageString(IDS_YES);

							if (m_sDataSpeditoRitirato.GetLength() > 0)
								strTemp += " (" + m_sDataSpeditoRitirato + ")";

							m_pList->SetItemText(nItem, 9, strTemp);
						}
						else
						{
							m_pList->SetItemText(nItem, 9, theApp.GetMessageString(IDS_NO));
						}

						if ((m_nSpedireRitirare % 3 == 0) || (m_nSpedireRitirare % 3 == 1))
							m_pList->SetItem(nItem, 10, LVIF_IMAGE, NULL, 0, 0, 0, 0);
						else
							m_pList->SetItem(nItem, 10, LVIF_IMAGE, NULL, -1, -1, 0, 0);
					}
				}
			}
		}

		setEsami.CloseRecordset("CRichiesteAnatomiaPatologicaEdtDlg::OnOK");
	}

	CDialog::OnOK();
}

void CRichiesteAnatomiaPatologicaEdtDlg::OnBnClickedCheckSpeditoRitirato()
{
	UpdateData(TRUE);

	if (m_bSpeditoRitirato)
	{
		CTime timeNow = CTime::GetCurrentTime();
		m_sDataSpeditoRitirato = timeNow.Format("%d/%m/%Y");
	}
	else
	{
		m_sDataSpeditoRitirato = "";
	}

	UpdateData(FALSE);
}

void CRichiesteAnatomiaPatologicaEdtDlg::OnBnClickedCheckVerificato()
{
	// Sandro 09/11/2010 // Aggiungo anche la data di verifica //

	UpdateData(TRUE);

	if (m_bVerificato)
	{
		CTime timeNow = CTime::GetCurrentTime();
		m_sDataVerificato = timeNow.Format("%d/%m/%Y");
	}
	else
	{
		m_sDataVerificato = "";
	}

	UpdateData(FALSE);

	//
	m_ctrlComboMedico.ShowWindow(m_bVerificato ? SW_SHOW : SW_HIDE);
}
