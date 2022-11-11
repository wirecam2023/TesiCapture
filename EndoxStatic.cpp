#include "stdafx.h"
#include "Endox.h"
#include "EndoxStatic.h"

#include "AbitudiniDynForm.h"
#include "AccessoriForm5Righe.h"
#include "AllergieDynForm.h"
#include "AnatomiaPatologicaForm.h"
#include "AnatomiaPatologicaPrestForm.h"
#include "AnatomiaPatologicaTastiForm.h"
#include "AntiaggregantiDynForm.h"
#include "AnticoagulantiDynForm.h"
#include "BMIDynForm.h"
#include "BostonScoreDynForm.h"
#include "BreathTestHPDynForm.h"
#include "ButtonDynForm.h"
#include "CentraleDiStampaDynForm.h"
#include "CheckDynForm.h"
#include "ChirurgiciDynForm.h"
#include "CodificaDiagnosiEsameForm.h"
#include "CodificaDiagnosiEsame5RigheForm.h"
#include "ComboDynForm.h"
#include "ConsensoInformatoDynForm.h"
#include "DiagnosiForm.h"
#include "DiagnosiICD9Form.h"
#include "DiagnosiICD9FormEx.h"
#include "DiagnosiFinaliICD9FormEx.h"
#include "EditDynFormFullRtf.h"
#include "EditDynFormRtf.h"
#include "EditDynForm1.h"
#include "EditDynForm2.h"
#include "EditDynForm3.h"
#include "EditDynFormCodiceDescrizione.h"
#include "EditDynFormConsigli.h"
#include "EditDynFormDataOra.h"
#include "EndoGridDynForm.h"
#include "EndoscopiciDynForm.h"
#include "EsamiPregressiForm.h"
#include "EsamiView.h"
#include "FamiliaritaForm.h"
#include "FarmaciPazientiCroniciDynForm.h"
#include "FluoroscopiaDynForm.h"
#include "IndaginiForm.h"
#include "InvianteDynForm.h"
#include "InvianteDynFormE.h"
#include "InvianteDynFormI.h"
#include "InvianteDynForm1.h"
#include "InvianteDynForm2.h"
#include "InvianteDynForm3.h"
#include "IstologiaTotForm.h"
#include "IstologiaTotForm5Righe.h"
#include "IstologiaTotForm5RighePlus.h"
#include "LegendaDynForm.h"
#include "MalattieForm.h"
#include "MonitoraggioOrizDynForm.h"
#include "MonitoraggioVertDynForm.h"
#include "OrganoSedeDynForm.h"
#include "OsservazioniForm.h"
#include "PacemakerDynForm.h"
#include "PortPacemakerDynForm.h"
#include "ProcedureICD9Form.h"
#include "PuntiPazienteDynForm.h"
#include "PressioneDynForm.h"
#include "RaoDynForm.h"
#include "RefertoForm.h"
#include "RegioneForm.h"
#include "RegioneForm5Righe.h"
#include "SospensioneDynForm.h"
#include "StudioDynForm.h"
#include "TabellaEbusDynForm.h"
#include "TerapieForm.h"
#include "TerapieTestoForm.h"
#include "CodiciClassificazioneDiagnosticaDynForm.h"
#include "VolumeDynForm.h"
#include "CardioPrimaDynForm.h"
#include "CardioDuranteDynForm.h"
#include "CardioDopoDynForm.h"
#include "MielogrammaDynForm.h"
#include "SchemiAnatomiciAggiuntoDynForm.h"  // Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoxStatic, CStatic)

CEndoxStatic::CEndoxStatic(CBaseForm* pBaseForm, CEsamiView* pEsamiView)
{
	ASSERT(pBaseForm != NULL);
	ASSERT(pEsamiView != NULL);

	m_pBaseForm = pBaseForm;
	m_pEsamiView = pEsamiView;

	m_lID = -1;
}

CEndoxStatic::~CEndoxStatic()
{
}

BEGIN_MESSAGE_MAP(CEndoxStatic, CStatic)
END_MESSAGE_MAP()

BOOL CEndoxStatic::Create(const RECT& rect, CWnd* pParentWnd, UINT nID, long lColore, BOOL bOnAlbumZone, long lIDFaseBlocco)
{
/* #ifdef _DEBUG
	BOOL bReturn = CStatic::Create("", WS_CHILD | WS_VISIBLE | SS_SUNKEN | SS_BLACKRECT, rect, pParentWnd, nID);
#else */
	BOOL bReturn = CStatic::Create("", WS_CHILD | WS_VISIBLE | SS_BLACKFRAME, rect, pParentWnd, nID);
// #endif

	m_lID = nID;
	m_bOnAlbumZone = bOnAlbumZone;

	switch(nID)
	{
		case SUB_ABITUDINI:
		{
			if (m_pEsamiView->m_pDynForm[sub_abitudini] == NULL)
				CAbitudiniDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_CHIRURGICI:
		{
			if (m_pEsamiView->m_pDynForm[sub_chirurgici] == NULL)
				CChirurgiciDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case SUB_ENDOSCOPICI:
		{
			if (m_pEsamiView->m_pDynForm[sub_endoscopici] == NULL)
				CEndoscopiciDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case SUB_FAMILIARITA:
		{
			if (m_pEsamiView->m_pDynForm[sub_familiarita] == NULL)
				CFamiliaritaForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_INDAGINI:
		{
			if (m_pEsamiView->m_pDynForm[sub_indagini] == NULL)
				CIndaginiForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_MALATTIE:
		{
			if (m_pEsamiView->m_pDynForm[sub_malattie] == NULL)
				CMalattieForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_PROGRESSIVO:
		{
			if (m_pEsamiView->m_pDynForm[edt_progressivo] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_progressivo, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_DATAESAME:
		{
			if (m_pEsamiView->m_pDynForm[edt_dataesame] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_dataesame, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_TIPOESAME:
		{
			if (m_pEsamiView->m_pDynForm[cmb_tipoesame] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_tipoesame, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_PROGRESSIVOANNO:
		{
			if (m_pEsamiView->m_pDynForm[edt_progressivoanno] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_progressivoanno, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_CODICEPRENOTAZIONE:
		{
			if (m_pEsamiView->m_pDynForm[edt_codiceprenotazione] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_codiceprenotazione, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_MEDICO1:
		{
			if (m_pEsamiView->m_pDynForm[cmb_medico1] == NULL)
			{
				if(theApp.m_bMediciDescrizioneLibera)
					CEditDynFormCodiceDescrizione::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_medico1, lColore, lIDFaseBlocco);
				else
					CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_medico1, lColore, lIDFaseBlocco);
			}

			break;
		}
		case CMB_MEDICO2:
		{
			if (m_pEsamiView->m_pDynForm[cmb_medico2] == NULL)
			{
				if (theApp.m_bMediciDescrizioneLibera)
					CEditDynFormCodiceDescrizione::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_medico2, lColore, lIDFaseBlocco);
				else
					CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_medico2, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_MEDICO_RICERCA:
		{
			if (m_pEsamiView->m_pDynForm[edt_medico_ricerca] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_medico_ricerca, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_ANESTESISTA:
		{
			if (m_pEsamiView->m_pDynForm[edt_anestesista] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_anestesista, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_INFERMIERE1:
		{
			if (m_pEsamiView->m_pDynForm[cmb_infermiere1] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_infermiere1, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_INFERMIERE2:
		{
			if (m_pEsamiView->m_pDynForm[cmb_infermiere2] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_infermiere2, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_INVIANTE:
		{
			if (m_pEsamiView->m_pDynForm[sub_inviante] == NULL)
				CInvianteDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case EDT_CAMERA:
		{
			if (m_pEsamiView->m_pDynForm[edt_camera] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_camera, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_INDICAZIONI:
		{
			if (m_pEsamiView->m_pDynForm[edt_indicazioni] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_indicazioni, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_FARMACOTRIAL:
		{
			if (m_pEsamiView->m_pDynForm[edt_farmacotrial] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_farmacotrial, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_PREMEDICAZIONI:
		{
			if (m_pEsamiView->m_pDynForm[edt_premedicazioni] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_premedicazioni, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_TERAPIAINATTO:
		{
			if (m_pEsamiView->m_pDynForm[sub_terapiainatto] == NULL)
				CTerapieForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_TERAPIAINATTO_TESTO:
		{
			if (m_pEsamiView->m_pDynForm[sub_terapiainatto_testo] == NULL)
				CTerapieTestoForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_OSSERVAZIONI:
		{
			if (m_pEsamiView->m_pDynForm[sub_osservazioni] == NULL)
				COsservazioniForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_DIAGNOSTICHE:
		{
			if (m_pEsamiView->m_pDynForm[edt_diagnostiche] == NULL)
				CEditDynForm3::CreateFormEx(GetParent(), this, m_pEsamiView, edt_diagnostiche, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_TERAPEUTICHE:
		{
			if (m_pEsamiView->m_pDynForm[edt_terapeutiche] == NULL)
				CEditDynForm3::CreateFormEx(GetParent(), this, m_pEsamiView, edt_terapeutiche, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_DIAGNOSI:
		{
			if (m_pEsamiView->m_pDynForm[sub_diagnosi] == NULL)
				CDiagnosiForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_CONDOTTOFINO:
		{
			if (m_pEsamiView->m_pDynForm[edt_condottofino] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_condottofino, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_VALUTAZIONE:
		{
			if (m_pEsamiView->m_pDynForm[edt_valutazione] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_valutazione, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_COMPLICANZE:
		{
			if (m_pEsamiView->m_pDynForm[edt_complicanze] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_complicanze, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_COMPLICANZEPROVVEDIMENTI:
		{
			if (m_pEsamiView->m_pDynForm[edt_complicanzeprovvedimenti] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_complicanzeprovvedimenti, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_COMPLICANZETERAPIA:
		{
			if (m_pEsamiView->m_pDynForm[edt_complicanzeterapia] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_complicanzeterapia, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_COMPLICANZEESITO:
		{
			if (m_pEsamiView->m_pDynForm[edt_complicanzeesito] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_complicanzeesito, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_TIPOVISITA:
		{
			if (m_pEsamiView->m_pDynForm[edt_tipovisita] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_tipovisita, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_QUADRO:
		{
			if (m_pEsamiView->m_pDynForm[edt_quadro] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_quadro, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_DURATA:
		{
			if (m_pEsamiView->m_pDynForm[edt_durata] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_durata, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_PROSSIMO:
		{
			if (m_pEsamiView->m_pDynForm[edt_prossimo] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_prossimo, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_STUDIO:
		{
			if (m_pEsamiView->m_pDynForm[edt_studio] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_studio, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_GUARIGIONE:
		{
			if (m_pEsamiView->m_pDynForm[edt_guarigione] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_guarigione, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_DIFFICOLTA:
		{
			if (m_pEsamiView->m_pDynForm[edt_difficolta] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_difficolta, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_REGIONE:
		{
			if (m_pEsamiView->m_pDynForm[sub_regione] == NULL)
				CRegioneForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_TERAPIACONSIGLIATA:
		{
			if (m_pEsamiView->m_pDynForm[edt_terapiaconsigliata] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_terapiaconsigliata, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_STRUMENTI:
		{
			if (m_pEsamiView->m_pDynForm[edt_strumenti] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_strumenti, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_ACCESSORI:
		{
			if (m_pEsamiView->m_pDynForm[edt_accessori] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_accessori, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_NOTE:
		{
			if (m_pEsamiView->m_pDynForm[edt_note] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_note, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_ISTOPATOLOGIA:
		{
			if (m_pEsamiView->m_pDynForm[sub_istopatologia] == NULL)
				CIstologiaTotForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_ISTOPATOLOGIA5RIGHE:
		{
			if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe] == NULL)
				CIstologiaTotForm5Righe::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case SUB_ISTOPATOLOGIA5RIGHE_PLUS:
		{
			if (m_pEsamiView->m_pDynForm[sub_istopatologia5righe_plus] == NULL)
				CIstologiaTotForm5RighePlus::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_REFERTO:
		{
			if (m_pEsamiView->m_pDynForm[sub_referto] == NULL)
				CRefertoForm::CreateFormEx(GetParent(), this, m_pEsamiView, lIDFaseBlocco);

			break;
		}
		case EDT_RIFERIMENTO:
		{
			if (m_pEsamiView->m_pDynForm[edt_riferimento] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_riferimento, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERO000:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero000] == NULL)
			{
				if (theApp.m_bComboSingleLine[0])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero000, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero000, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO001:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero001] == NULL)
			{
				if (theApp.m_bComboSingleLine[1])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero001, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero001, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO002:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero002] == NULL)
			{
				if (theApp.m_bComboSingleLine[2])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero002, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero002, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO003:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero003] == NULL)
			{
				if (theApp.m_bComboSingleLine[3])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero003, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero003, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO004:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero004] == NULL)
			{
				if (theApp.m_bComboSingleLine[4])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero004, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero004, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO005:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero005] == NULL)
			{
				if (theApp.m_bComboSingleLine[5])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero005, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero005, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO006:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero006] == NULL)
			{
				if (theApp.m_bComboSingleLine[6])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero006, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero006, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO007:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero007] == NULL)
			{
				if (theApp.m_bComboSingleLine[7])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero007, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero007, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO008:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero008] == NULL)
			{
				if (theApp.m_bComboSingleLine[8])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero008, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero008, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO009:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero009] == NULL)
			{
				if (theApp.m_bComboSingleLine[9])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero009, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero009, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO010:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero010] == NULL)
			{
				if (theApp.m_bComboSingleLine[10])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero010, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero010, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO011:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero011] == NULL)
			{
				if (theApp.m_bComboSingleLine[11])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero011, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero011, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO012:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero012] == NULL)
			{
				if (theApp.m_bComboSingleLine[12])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero012, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero012, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO013:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero013] == NULL)
			{
				if (theApp.m_bComboSingleLine[13])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero013, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero013, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO014:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero014] == NULL)
			{
				if (theApp.m_bComboSingleLine[14])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero014, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero014, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO015:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero015] == NULL)
			{
				if (theApp.m_bComboSingleLine[15])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero015, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero015, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO016:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero016] == NULL)
			{
				if (theApp.m_bComboSingleLine[16])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero016, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero016, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO017:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero017] == NULL)
			{
				if (theApp.m_bComboSingleLine[17])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero017, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero017, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO018:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero018] == NULL)
			{
				if (theApp.m_bComboSingleLine[18])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero018, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero018, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO019:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero019] == NULL)
			{
				if (theApp.m_bComboSingleLine[19])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero019, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero019, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO020:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero020] == NULL)
			{
				if (theApp.m_bComboSingleLine[20])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero020, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero020, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO021:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero021] == NULL)
			{
				if (theApp.m_bComboSingleLine[21])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero021, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero021, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO022:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero022] == NULL)
			{
				if (theApp.m_bComboSingleLine[22])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero022, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero022, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO023:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero023] == NULL)
			{
				if (theApp.m_bComboSingleLine[23])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero023, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero023, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO024:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero024] == NULL)
			{
				if (theApp.m_bComboSingleLine[24])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero024, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero024, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO025:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero025] == NULL)
			{
				if (theApp.m_bComboSingleLine[25])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero025, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero025, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO026:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero026] == NULL)
			{
				if (theApp.m_bComboSingleLine[26])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero026, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero026, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO027:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero027] == NULL)
			{
				if (theApp.m_bComboSingleLine[27])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero027, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero027, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO028:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero028] == NULL)
			{
				if (theApp.m_bComboSingleLine[28])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero028, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero028, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO029:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero029] == NULL)
			{
				if (theApp.m_bComboSingleLine[29])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero029, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero029, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO030:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero030] == NULL)
			{
				if (theApp.m_bComboSingleLine[30])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero030, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero030, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO031:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero031] == NULL)
			{
				if (theApp.m_bComboSingleLine[31])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero031, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero031, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO032:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero032] == NULL)
			{
				if (theApp.m_bComboSingleLine[32])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero032, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero032, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO033:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero033] == NULL)
			{
				if (theApp.m_bComboSingleLine[33])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero033, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero033, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO034:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero034] == NULL)
			{
				if (theApp.m_bComboSingleLine[34])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero034, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero034, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO035:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero035] == NULL)
			{
				if (theApp.m_bComboSingleLine[35])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero035, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero035, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO036:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero036] == NULL)
			{
				if (theApp.m_bComboSingleLine[36])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero036, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero036, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO037:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero037] == NULL)
			{
				if (theApp.m_bComboSingleLine[37])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero037, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero037, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO038:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero038] == NULL)
			{
				if (theApp.m_bComboSingleLine[38])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero038, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero038, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO039:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero039] == NULL)
			{
				if (theApp.m_bComboSingleLine[39])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero039, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero039, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO040:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero040] == NULL)
			{
				if (theApp.m_bComboSingleLine[40])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero040, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero040, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO041:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero041] == NULL)
			{
				if (theApp.m_bComboSingleLine[41])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero041, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero041, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO042:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero042] == NULL)
			{
				if (theApp.m_bComboSingleLine[42])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero042, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero042, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO043:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero043] == NULL)
			{
				if (theApp.m_bComboSingleLine[43])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero043, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero043, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO044:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero044] == NULL)
			{
				if (theApp.m_bComboSingleLine[44])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero044, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero044, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO045:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero045] == NULL)
			{
				if (theApp.m_bComboSingleLine[45])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero045, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero045, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO046:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero046] == NULL)
			{
				if (theApp.m_bComboSingleLine[46])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero046, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero046, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO047:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero047] == NULL)
			{
				if (theApp.m_bComboSingleLine[47])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero047, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero047, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO048:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero048] == NULL)
			{
				if (theApp.m_bComboSingleLine[48])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero048, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero048, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO049:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero049] == NULL)
			{
				if (theApp.m_bComboSingleLine[49])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero049, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero049, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO050:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero050] == NULL)
			{
				if (theApp.m_bComboSingleLine[50])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero050, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero050, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO051:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero051] == NULL)
			{
				if (theApp.m_bComboSingleLine[51])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero051, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero051, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO052:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero052] == NULL)
			{
				if (theApp.m_bComboSingleLine[52])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero052, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero052, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO053:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero053] == NULL)
			{
				if (theApp.m_bComboSingleLine[53])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero053, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero053, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO054:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero054] == NULL)
			{
				if (theApp.m_bComboSingleLine[54])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero054, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero054, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO055:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero055] == NULL)
			{
				if (theApp.m_bComboSingleLine[55])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero055, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero055, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO056:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero056] == NULL)
			{
				if (theApp.m_bComboSingleLine[56])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero056, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero056, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO057:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero057] == NULL)
			{
				if (theApp.m_bComboSingleLine[57])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero057, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero057, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO058:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero058] == NULL)
			{
				if (theApp.m_bComboSingleLine[58])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero058, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero058, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO059:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero059] == NULL)
			{
				if (theApp.m_bComboSingleLine[59])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero059, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero059, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO060:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero060] == NULL)
			{
				if (theApp.m_bComboSingleLine[60])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero060, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero060, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO061:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero061] == NULL)
			{
				if (theApp.m_bComboSingleLine[61])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero061, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero061, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO062:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero062] == NULL)
			{
				if (theApp.m_bComboSingleLine[62])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero062, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero062, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO063:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero063] == NULL)
			{
				if (theApp.m_bComboSingleLine[63])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero063, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero063, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO064:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero064] == NULL)
			{
				if (theApp.m_bComboSingleLine[64])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero064, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero064, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO065:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero065] == NULL)
			{
				if (theApp.m_bComboSingleLine[65])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero065, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero065, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO066:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero066] == NULL)
			{
				if (theApp.m_bComboSingleLine[66])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero066, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero066, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO067:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero067] == NULL)
			{
				if (theApp.m_bComboSingleLine[67])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero067, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero067, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO068:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero068] == NULL)
			{
				if (theApp.m_bComboSingleLine[68])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero068, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero068, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO069:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero069] == NULL)
			{
				if (theApp.m_bComboSingleLine[69])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero069, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero069, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO070:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero070] == NULL)
			{
				if (theApp.m_bComboSingleLine[70])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero070, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero070, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO071:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero071] == NULL)
			{
				if (theApp.m_bComboSingleLine[71])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero071, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero071, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO072:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero072] == NULL)
			{
				if (theApp.m_bComboSingleLine[72])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero072, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero072, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO073:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero073] == NULL)
			{
				if (theApp.m_bComboSingleLine[73])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero073, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero073, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO074:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero074] == NULL)
			{
				if (theApp.m_bComboSingleLine[74])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero074, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero074, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO075:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero075] == NULL)
			{
				if (theApp.m_bComboSingleLine[75])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero075, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero075, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO076:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero076] == NULL)
			{
				if (theApp.m_bComboSingleLine[76])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero076, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero076, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO077:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero077] == NULL)
			{
				if (theApp.m_bComboSingleLine[77])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero077, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero077, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO078:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero078] == NULL)
			{
				if (theApp.m_bComboSingleLine[78])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero078, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero078, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO079:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero079] == NULL)
			{
				if (theApp.m_bComboSingleLine[79])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero079, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero079, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO080:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero080] == NULL)
			{
				if (theApp.m_bComboSingleLine[80])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero080, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero080, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO081:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero081] == NULL)
			{
				if (theApp.m_bComboSingleLine[81])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero081, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero081, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO082:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero082] == NULL)
			{
				if (theApp.m_bComboSingleLine[82])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero082, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero082, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO083:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero083] == NULL)
			{
				if (theApp.m_bComboSingleLine[83])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero083, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero083, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO084:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero084] == NULL)
			{
				if (theApp.m_bComboSingleLine[84])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero084, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero084, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO085:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero085] == NULL)
			{
				if (theApp.m_bComboSingleLine[85])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero085, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero085, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO086:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero086] == NULL)
			{
				if (theApp.m_bComboSingleLine[86])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero086, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero086, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO087:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero087] == NULL)
			{
				if (theApp.m_bComboSingleLine[87])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero087, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero087, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO088:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero088] == NULL)
			{
				if (theApp.m_bComboSingleLine[88])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero088, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero088, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO089:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero089] == NULL)
			{
				if (theApp.m_bComboSingleLine[89])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero089, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero089, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO090:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero090] == NULL)
			{
				if (theApp.m_bComboSingleLine[90])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero090, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero090, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO091:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero091] == NULL)
			{
				if (theApp.m_bComboSingleLine[91])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero091, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero091, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO092:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero092] == NULL)
			{
				if (theApp.m_bComboSingleLine[92])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero092, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero092, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO093:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero093] == NULL)
			{
				if (theApp.m_bComboSingleLine[93])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero093, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero093, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO094:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero094] == NULL)
			{
				if (theApp.m_bComboSingleLine[94])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero094, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero094, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO095:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero095] == NULL)
			{
				if (theApp.m_bComboSingleLine[95])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero095, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero095, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO096:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero096] == NULL)
			{
				if (theApp.m_bComboSingleLine[96])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero096, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero096, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO097:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero097] == NULL)
			{
				if (theApp.m_bComboSingleLine[97])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero097, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero097, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO098:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero098] == NULL)
			{
				if (theApp.m_bComboSingleLine[98])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero098, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero098, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERO099:
		{
			if (m_pEsamiView->m_pDynForm[edt_libero099] == NULL)
			{
				if (theApp.m_bComboSingleLine[99])
					CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero099, lColore, lIDFaseBlocco);
				else
					CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_libero099, lColore, lIDFaseBlocco);
			}

			break;
		}
		case EDT_LIBERORTF000:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf000] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf000, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF001:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf001] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf001, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF002:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf002] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf002, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF003:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf003] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf003, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF004:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf004] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf004, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF005:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf005] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf005, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF006:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf006] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf006, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF007:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf007] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf007, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF008:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf008] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf008, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF009:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf009] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf009, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF010:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf010] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf010, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF011:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf011] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf011, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF012:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf012] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf012, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF013:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf013] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf013, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF014:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf014] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf014, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF015:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf015] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf015, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF016:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf016] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf016, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF017:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf017] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf017, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF018:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf018] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf018, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERORTF019:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberortf019] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberortf019, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL000:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl000] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl000, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL001:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl001] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl001, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL002:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl002] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl002, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL003:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl003] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl003, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL004:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl004] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl004, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL005:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl005] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl005, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL006:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl006] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl006, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL007:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl007] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl007, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL008:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl008] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl008, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL009:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl009] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl009, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL010:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl010] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl010, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL011:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl011] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl011, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL012:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl012] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl012, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL013:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl013] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl013, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL014:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl014] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl014, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL015:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl015] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl015, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL016:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl016] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl016, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL017:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl017] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl017, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL018:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl018] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl018, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBEROCL019:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberocl019] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberocl019, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA000:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora000] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora000, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA001:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora001] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora001, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA002:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora002] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora002, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA003:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora003] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora003, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA004:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora004] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora004, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA005:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora005] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora005, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA006:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora006] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora006, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA007:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora007] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora007, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA008:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora008] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora008, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA009:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora009] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora009, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA010:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora010] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora010, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA011:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora011] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora011, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA012:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora012] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora012, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA013:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora013] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora013, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA014:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora014] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora014, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA015:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora015] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora015, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA016:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora016] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora016, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA017:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora017] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora017, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA018:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora018] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora018, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_LIBERODATAORA019:
		{
			if (m_pEsamiView->m_pDynForm[edt_liberodataora019] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_liberodataora019, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA000:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa000] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa000, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA001:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa001] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa001, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA002:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa002] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa002, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA003:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa003] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa003, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA004:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa004] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa004, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA005:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa005] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa005, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA006:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa006] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa006, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA007:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa007] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa007, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA008:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa008] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa008, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA009:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa009] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa009, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA010:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa010] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa010, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA011:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa011] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa011, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA012:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa012] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa012, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA013:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa013] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa013, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA014:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa014] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa014, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA015:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa015] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa015, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA016:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa016] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa016, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA017:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa017] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa017, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA018:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa018] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa018, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOSTAMPA019:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastostampa019] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastostampa019, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER000:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser000] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser000, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER001:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser001] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser001, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER002:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser002] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser002, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER003:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser003] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser003, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER004:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser004] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser004, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER005:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser005] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser005, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER006:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser006] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser006, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER007:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser007] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser007, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER008:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser008] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser008, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER009:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser009] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser009, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER010:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser010] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser010, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER011:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser011] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser011, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER012:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser012] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser012, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER013:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser013] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser013, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER014:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser014] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser014, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER015:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser015] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser015, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER016:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser016] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser016, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER017:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser017] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser017, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER018:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser018] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser018, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOBROWSER019:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastobrowser019] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastobrowser019, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE000:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile000] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile000, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE001:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile001] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile001, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE002:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile002] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile002, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE003:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile003] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile003, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE004:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile004] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile004, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE005:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile005] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile005, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE006:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile006] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile006, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE007:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile007] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile007, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE008:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile008] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile008, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE009:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile009] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile009, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE010:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile010] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile010, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE011:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile011] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile011, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE012:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile012] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile012, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE013:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile013] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile013, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE014:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile014] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile014, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE015:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile015] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile015, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE016:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile016] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile016, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE017:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile017] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile017, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE018:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile018] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile018, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_LIBEROTASTOESEGUIBILE019:
		{
			if (m_pEsamiView->m_pDynForm[btn_liberotastoeseguibile019] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastoeseguibile019, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_INTEGRAZIONI:
		{
			if (m_pEsamiView->m_pDynForm[edt_integrazioni] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_integrazioni, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_OSSERVAZIONI:
		{
			if (m_pEsamiView->m_pDynForm[btn_osservazioni] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_osservazioni, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_DIAGNOSTICHE:
		{
			if (m_pEsamiView->m_pDynForm[btn_diagnostiche] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_diagnostiche, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_TERAPEUTICHE:
		{
			if (m_pEsamiView->m_pDynForm[btn_terapeutiche] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_terapeutiche, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_DIAGNOSI:
		{
			if (m_pEsamiView->m_pDynForm[btn_diagnosi] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_diagnosi, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_MONITORAGGIO_ORIZ:
		{
			if (m_pEsamiView->m_pDynForm[sub_monitoraggio_oriz] == NULL)
				CMonitoraggioOrizDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_MONITORAGGIO_VERT:
		{
			if (m_pEsamiView->m_pDynForm[sub_monitoraggio_vert] == NULL)
				CMonitoraggioVertDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case SUB_RAO:
		{
			if (m_pEsamiView->m_pDynForm[sub_rao] == NULL)
				CRaoDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_CONSENSOINFORMATO:
		{
			if (m_pEsamiView->m_pDynForm[sub_consensoinformato] == NULL)
				CConsensoInformatoDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_LEGENDA1:
		{
			if (m_pEsamiView->m_pDynForm[sub_legenda1] == NULL)
				CLegendaDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, sub_legenda1, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_LEGENDA2:
		{
			if (m_pEsamiView->m_pDynForm[sub_legenda2] == NULL)
				CLegendaDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, sub_legenda2, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_SEDEESAME:
		{
			if (m_pEsamiView->m_pDynForm[edt_sedeesame] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_sedeesame, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_SALAESAME:
		{
			if (m_pEsamiView->m_pDynForm[edt_salaesame] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_salaesame, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_CODIFICADIAGNOSIESAME:
		{
			if (m_pEsamiView->m_pDynForm[sub_codificadiagnosiesame] == NULL)
				CCodificaDiagnosiEsameForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_CODIFICADIAGNOSIESAME:
		{
			if (m_pEsamiView->m_pDynForm[btn_codificadiagnosiesame] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_codificadiagnosiesame, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_LEGENDA3:
		{
			if (m_pEsamiView->m_pDynForm[sub_legenda3] == NULL)
				CLegendaDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, sub_legenda3, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_ESAMIPREGRESSI:
		{
			if (m_pEsamiView->m_pDynForm[sub_esamipregressi] == NULL)
				CEsamiPregressiForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_INVIANTE1:
		{
			if (m_pEsamiView->m_pDynForm[edt_inviante1] == NULL)
				CInvianteDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_INVIANTE2:
		{
			if (m_pEsamiView->m_pDynForm[edt_inviante2] == NULL)
				CInvianteDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_INVIANTE3:
		{
			if (m_pEsamiView->m_pDynForm[edt_inviante3] == NULL)
				CInvianteDynForm3::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_ANATOMIAPATOLOGICA:
		{
			if (m_pEsamiView->m_pDynForm[sub_anatomiapatologica] == NULL)
				CAnatomiaPatologicaForm::CreateFormEx(IDD_SUBFORM_ANATOMIAPATOLOGICA, GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case EDT_ANATOMIAPATOLOGICANOTE:
		{
			if (m_pEsamiView->m_pDynForm[edt_anatomiapatologicanote] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_anatomiapatologicanote, lColore, lIDFaseBlocco);
			
			break;
		}
		case SUB_ANATOMIAPATOLOGICAPREST:
		{
			if (m_pEsamiView->m_pDynForm[sub_anatomiapatologicaprest] == NULL)
				CAnatomiaPatologicaPrestForm::CreateFormEx(IDD_SUBFORM_ANATOMIAPATOLOGICA_PREST, GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case EDT_ANATOMIAPATOLOGICAREFER:
		{
			if (m_pEsamiView->m_pDynForm[edt_anatomiapatologicarefer] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_anatomiapatologicarefer, lColore, lIDFaseBlocco);
			
			break;
		}
		case EDT_ANATOMIAPATOLOGICAREFER_RTF:
		{
			if (m_pEsamiView->m_pDynForm[edt_anatomiapatologicarefer_rtf] == NULL)
				CEditDynFormRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_anatomiapatologicarefer_rtf, lColore, lIDFaseBlocco);
			
			break;
		}
		case SUB_ANATOMIAPATOLOGICATASTI:
		{
			if (m_pEsamiView->m_pDynForm[sub_anatomiapatologicatasti] == NULL)
				CAnatomiaPatologicaTastiForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case EDT_ANATOMIAPATOLOGICASUGGER1:
		{
			if (m_pEsamiView->m_pDynForm[edt_anatomiapatologicasugger1] == NULL)
				CEditDynFormConsigli::CreateFormEx(GetParent(), this, m_pEsamiView, edt_anatomiapatologicasugger1, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_ANATOMIAPATOLOGICASUGGER2:
		{
			if (m_pEsamiView->m_pDynForm[edt_anatomiapatologicasugger2] == NULL)
				CEditDynFormConsigli::CreateFormEx(GetParent(), this, m_pEsamiView, edt_anatomiapatologicasugger2, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_ORGANOSEDEPREVISTA:
		{
			if (m_pEsamiView->m_pDynForm[edt_organosedeprevista] == NULL)
				COrganoSedeDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, edt_organosedeprevista, lColore, lIDFaseBlocco);
			
			break;
		}
		case EDT_ORGANOSEDERAGGIUNTA:
		{
			if (m_pEsamiView->m_pDynForm[edt_organosederaggiunta] == NULL)
				COrganoSedeDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, edt_organosederaggiunta, lColore, lIDFaseBlocco);
			
			break;
		}
		case SUB_ALLERGIE:
		{
			if (m_pEsamiView->m_pDynForm[sub_allergie] == NULL)
				CAllergieDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case SUB_PACEMAKER:
		{
			if (m_pEsamiView->m_pDynForm[sub_pacemaker] == NULL)
				CPacemakerDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}

		case SUB_PORTATOREPACEMAKER:
		{
			if (m_pEsamiView->m_pDynForm[sub_portatorepacemaker] == NULL)
				CPortPacemakerDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}

		case SUB_ANTICOAGULANTI:
		{
			if (m_pEsamiView->m_pDynForm[sub_anticoagulanti] == NULL)
				CAnticoagulantiDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}

		case SUB_ANTIAGGREGANTI:
		{
			if (m_pEsamiView->m_pDynForm[sub_antiaggreganti] == NULL)
				CAntiaggregantiDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}

		case SUB_REGIONE5RIGHE:
		{
			if (m_pEsamiView->m_pDynForm[sub_regione5righe] == NULL)
				CRegioneForm5Righe::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}

		case SUB_CODIFICADIAGNOSIESAME5RIGHE:
		{
			if (m_pEsamiView->m_pDynForm[sub_codificadiagnosiesame5righe] == NULL)
				CCodificaDiagnosiEsame5RigheForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}

		case BTN_CODIFICADIAGNOSIESAME5RIGHE:
		{
			if (m_pEsamiView->m_pDynForm[btn_codificadiagnosiesame5righe] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_codificadiagnosiesame5righe, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_FUMO:
		{
			if (m_pEsamiView->m_pDynForm[edt_fumo] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_fumo, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_CAFFE:
		{
			if (m_pEsamiView->m_pDynForm[edt_caffe] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_caffe, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_SIGARETTE:
		{
			if (m_pEsamiView->m_pDynForm[edt_sigarette] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_sigarette, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_FARMACI:
		{
			if (m_pEsamiView->m_pDynForm[edt_farmaci] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_farmaci, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_ALCOOL:
		{
			if (m_pEsamiView->m_pDynForm[edt_alcool] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_alcool, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_ASSUNZIONE:
		{
			if (m_pEsamiView->m_pDynForm[edt_assunzione] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_assunzione, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_SUPERALCOLICI:
		{
			if (m_pEsamiView->m_pDynForm[edt_superalcolici] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_superalcolici, lColore, lIDFaseBlocco);

			break;
		}

		case SUB_BMI:
		{
			if (m_pEsamiView->m_pDynForm[sub_bmi] == NULL)
				CBMIDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_VOLUME:
		{
			if (m_pEsamiView->m_pDynForm[sub_volume] == NULL)
				CVolumeDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_FLUOROSCOPIA:
		{
			if (m_pEsamiView->m_pDynForm[sub_fluoroscopia] == NULL)
				CFluoroscopiaDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		
		case SUB_ACCESSORI5RIGHE:
		{
			if (m_pEsamiView->m_pDynForm[sub_accessori5righe] == NULL)
				CAccessoriForm5Righe::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}

		case BTN_CONVALIDA:
		{
			if (m_pEsamiView->m_pDynForm[btn_convalida] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_convalida, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_INVIANTE_I:
		{
			if (m_pEsamiView->m_pDynForm[edt_inviante_i] == NULL)
				CInvianteDynFormI::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_INVIANTE_E:
		{
			if (m_pEsamiView->m_pDynForm[edt_inviante_e] == NULL)
				CInvianteDynFormE::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
		case EDT_MEDICO2:
		{
			if (m_pEsamiView->m_pDynForm[edt_medico2] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_medico2, lColore, lIDFaseBlocco);
			break;
		}
		case EDT_MEDICO3:
		{
			if (m_pEsamiView->m_pDynForm[edt_medico3] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_medico3, lColore, lIDFaseBlocco);
			break;
		}
		case EDT_MEDICO4:
		{
			if (m_pEsamiView->m_pDynForm[edt_medico4] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_medico4, lColore, lIDFaseBlocco);
			break;
		}
		case EDT_PAZIENTE_PASSAPORTO: //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			if (m_pEsamiView->m_pDynForm[edt_paziente_passaporto] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_paziente_passaporto, lColore, lIDFaseBlocco);
			break;
		}
		case EDT_PAZIENTE_DOC1: //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			if (m_pEsamiView->m_pDynForm[edt_paziente_doc1] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_paziente_doc1, lColore, lIDFaseBlocco);
			break;
		}
		case EDT_PAZIENTE_DOC2: //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			if (m_pEsamiView->m_pDynForm[edt_paziente_doc2] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_paziente_doc2, lColore, lIDFaseBlocco);
			break;
		}
		case EDT_REFERTOINTEGRATO_MACRO: //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		{
			if (m_pEsamiView->m_pDynForm[edt_refertointegrato_macro] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_refertointegrato_macro, lColore, lIDFaseBlocco);
			break;
		}
		case EDT_REFERTOINTEGRATO_DIAG: //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		{
			if (m_pEsamiView->m_pDynForm[edt_refertointegrato_diag] == NULL)
				CEditDynFormFullRtf::CreateFormEx(GetParent(), this, m_pEsamiView, edt_refertointegrato_diag, lColore, lIDFaseBlocco);
			break;
		}
		case EDT_REFERTOINTEGRATO_FIRMA: //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		{
			if (m_pEsamiView->m_pDynForm[edt_refertointegrato_firma] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_refertointegrato_firma, lColore, lIDFaseBlocco);
			break;
		}

		case EDT_PAZIENTE_MEDICOCURANTE:
		{
			if (m_pEsamiView->m_pDynForm[edt_paziente_medicocurante] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_paziente_medicocurante, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_COMPLICANZEIMMEDIATE:
		{
			if (m_pEsamiView->m_pDynForm[cmb_complicanzeimmediate] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_complicanzeimmediate, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_COMPLICANZETARDIVE:
		{
			if (m_pEsamiView->m_pDynForm[cmb_complicanzetardive] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_complicanzetardive, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_PULIZIA:
		{
			if (m_pEsamiView->m_pDynForm[cmb_pulizia] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_pulizia, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_CAUSENONCOMPLETAMENTO:
		{
			if (m_pEsamiView->m_pDynForm[cmb_causenoncompletamento] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_causenoncompletamento, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_TOLLERANZA:
		{
			if (m_pEsamiView->m_pDynForm[cmb_tolleranza] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_tolleranza, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_CONCLUSIONISCREENING:
		{
			if (m_pEsamiView->m_pDynForm[cmb_conclusioniscreening] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_conclusioniscreening, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_CONCLUSIONICOLON:
		{
			if (m_pEsamiView->m_pDynForm[cmb_conclusionicolon] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_conclusionicolon, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_DIAGNOSIFINALE:
		{
			if (m_pEsamiView->m_pDynForm[cmb_diagnosifinale] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_diagnosifinale, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_NECASSOSPEDALIERA:
		{
			if (m_pEsamiView->m_pDynForm[sub_necassospedaliera] == NULL)
				CCheckDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, sub_necassospedaliera, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_PREMEDPOSOLOGIA:
		{
			if (m_pEsamiView->m_pDynForm[edt_premedposologia] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_premedposologia, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_ALTREANOMALIE:
		{
			if (m_pEsamiView->m_pDynForm[cmb_altreanomalie] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_altreanomalie, lColore, lIDFaseBlocco);

			break;
		}

		case BTN_CHIUSURAESAME:
		{
			if (m_pEsamiView->m_pDynForm[btn_chiusuraesame] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_chiusuraesame, lColore, lIDFaseBlocco);

			break;
		}

		// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
		case BTN_LIBERA_LAUDO:
		{
			if (m_pEsamiView->m_pDynForm[btn_libera_laudo] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_libera_laudo, lColore, lIDFaseBlocco);
			break;
		}

		case BTN_COMPLICANZE1:
		{
			if (m_pEsamiView->m_pDynForm[btn_complicanze1] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_complicanze1, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_COMPLICANZE2:
		{
			if (m_pEsamiView->m_pDynForm[btn_complicanze2] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_complicanze2, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_COMPLICANZE3:
		{
			if (m_pEsamiView->m_pDynForm[btn_complicanze3] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_complicanze3, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_MST_COMPLICANZE1:
		{
			if (m_pEsamiView->m_pDynForm[edt_mst_complicanze1] == NULL)
				CEditDynForm3::CreateFormEx(GetParent(), this, m_pEsamiView, edt_mst_complicanze1, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_MST_COMPLICANZE2:
		{
			if (m_pEsamiView->m_pDynForm[edt_mst_complicanze2] == NULL)
				CEditDynForm3::CreateFormEx(GetParent(), this, m_pEsamiView, edt_mst_complicanze2, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_MST_COMPLICANZE3:
		{
			if (m_pEsamiView->m_pDynForm[edt_mst_complicanze3] == NULL)
				CEditDynForm3::CreateFormEx(GetParent(), this, m_pEsamiView, edt_mst_complicanze3, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_BREATHTEST_HP:
		{
			if (m_pEsamiView->m_pDynForm[sub_breathtest_hp] == NULL)
				CBreathTestHPDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case SUB_SOSPENSIONE:
		{
			if (m_pEsamiView->m_pDynForm[sub_sospensione] == NULL)
				CSospensioneDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case SUB_PROCEDUREICD9:
		{
			if (m_pEsamiView->m_pDynForm[sub_procedureicd9] == NULL)
				CProcedureICD9Form::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case SUB_DIAGNOSIICD9:
		{
			if (m_pEsamiView->m_pDynForm[sub_diagnosiicd9] == NULL)
				CDiagnosiICD9Form::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);
			
			break;
		}
		case EDT_CODESAME:
		{
			if (m_pEsamiView->m_pDynForm[edt_codesame] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_codesame, lColore, lIDFaseBlocco);
			
			break;
		}

		case SUB_PUNTIPAZIENTE:
		{
			if (m_pEsamiView->m_pDynForm[sub_puntipaziente] == NULL)
				CPuntiPazienteDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_TEMPOCHIUSURA:
		{
			if (m_pEsamiView->m_pDynForm[edt_tempochiusura] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_tempochiusura, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_TEMPOCONVALIDA:
		{
			if (m_pEsamiView->m_pDynForm[edt_tempoconvalida] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_tempoconvalida, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_CODICERICOVERO:
		{
			if (m_pEsamiView->m_pDynForm[edt_codicericovero] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_codicericovero, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_BARCODERICOVERO:
		{
			if (m_pEsamiView->m_pDynForm[edt_barcodericovero] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_barcodericovero, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_ASSIDEN:
		{
			if (m_pEsamiView->m_pDynForm[edt_assiden] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_assiden, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_CODALFA:
		{
			if (m_pEsamiView->m_pDynForm[edt_codalfa] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_codalfa, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_PRESSIONE:
		{
			if (m_pEsamiView->m_pDynForm[edt_pressione] == NULL)
				CPressioneDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}

		case BTN_VIDEOCAPSULA:
		{
			if (m_pEsamiView->m_pDynForm[btn_videocapsula] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_videocapsula, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_ESAMESTRUMENTALE_ORAINIZIO:
		{
			if (m_pEsamiView->m_pDynForm[edt_esamestrumentale_orainizio] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_esamestrumentale_orainizio, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_ESAMESTRUMENTALE_ORAFINE:
		{
			if (m_pEsamiView->m_pDynForm[edt_esamestrumentale_orafine] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_esamestrumentale_orafine, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_ESAMESTRUMENTALE_DURATAOREMINUTI:
		{
			if (m_pEsamiView->m_pDynForm[edt_esamestrumentale_durataoreminuti] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_esamestrumentale_durataoreminuti, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_ESAMESTRUMENTALE_DURATASOLOMINUTI:
		{
			if (m_pEsamiView->m_pDynForm[edt_esamestrumentale_duratasolominuti] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_esamestrumentale_duratasolominuti, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_PAZIENTICRONICI_TERAPIA:
		{
			if (m_pEsamiView->m_pDynForm[sub_pazienticronici_terapia] == NULL)
				CFarmaciPazientiCroniciDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
		case SUB_SCHEMI_ANATOMICHI:
		{
			if (m_pEsamiView->m_pDynForm[sub_schemi_anatomichi] == NULL)
				CSchemiAnatomiciAggiuntoDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_PAZIENTICRONICI_SCORE_HB:
		{
			if (m_pEsamiView->m_pDynForm[edt_pazienticronici_score_hb] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_pazienticronici_score_hb, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_PAZIENTICRONICI_SCORE_S:
		{
			if (m_pEsamiView->m_pDynForm[edt_pazienticronici_score_s] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_pazienticronici_score_s, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_TABELLAEBUS:
		{
			if (m_pEsamiView->m_pDynForm[sub_tabellaebus] == NULL)
				CTabellaEbusDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_STUDIO:
		{
			if (m_pEsamiView->m_pDynForm[sub_studio] == NULL)
				CStudioDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_UTENTE_INSERIMENTOESAME:
		{
			if (m_pEsamiView->m_pDynForm[edt_utente_inserimentoesame] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_utente_inserimentoesame, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_DATAREFERTOISTOLOGICO:
		{
			if (m_pEsamiView->m_pDynForm[edt_data_referto_istologico] == NULL)
				CEditDynFormDataOra::CreateFormEx(GetParent(), this, m_pEsamiView, edt_data_referto_istologico, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_PRESENZALESIONECCR:
		{
			if (m_pEsamiView->m_pDynForm[sub_presenzalesioneCCR] == NULL)
				CCheckDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, sub_presenzalesioneCCR, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_NUMEROTOTALEPOLIPI:
		{
			if (m_pEsamiView->m_pDynForm[edt_numerototalepolipi] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_numerototalepolipi, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_BOSTONSCORE:
		{
			if (m_pEsamiView->m_pDynForm[sub_bostonscore] == NULL)
				CBostonScoreDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_TEMPORETRAZIONE:
		{
			if (m_pEsamiView->m_pDynForm[edt_temporetrazione] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_temporetrazione, lColore, lIDFaseBlocco);

			break;
		}

		case EDT_INTEGRAZIONECODICEURGENZA:
		{
			if (m_pEsamiView->m_pDynForm[edt_integrazioneCodiceUrgenza] == NULL)
				CEditDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, edt_integrazioneCodiceUrgenza, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_CENTRALEREFERTAZIONE:
		{

			if (m_pEsamiView->m_pDynForm[btn_centralerefertazione] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_centralerefertazione, lColore, lIDFaseBlocco);

			break;
		}
		case BTN_CARESTREAM:
		{

			if (m_pEsamiView->m_pDynForm[btn_carestream] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_carestream, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_DIAGNOSIICD9EX:
		{
			if (m_pEsamiView->m_pDynForm[sub_diagnosiicd9ex] == NULL)
				CDiagnosiICD9FormEx::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_DIAGNOSIFINALEICD9EX:
		{
			if (m_pEsamiView->m_pDynForm[sub_diagnosifinaliicd9ex] == NULL)
				CDiagnosiFinaliICD9FormEx::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_ETICHETTA000:
		case SUB_ETICHETTA001:
		case SUB_ETICHETTA002:
		case SUB_ETICHETTA003:
		case SUB_ETICHETTA004:
		case SUB_ETICHETTA005:
		case SUB_ETICHETTA006:
		case SUB_ETICHETTA007:
		case SUB_ETICHETTA008:
		case SUB_ETICHETTA009:
		case SUB_ETICHETTA010:
		case SUB_ETICHETTA011:
		case SUB_ETICHETTA012:
		case SUB_ETICHETTA013:
		case SUB_ETICHETTA014:
		case SUB_ETICHETTA015:
		case SUB_ETICHETTA016:
		case SUB_ETICHETTA017:
		case SUB_ETICHETTA018:
		case SUB_ETICHETTA019:
		case SUB_ETICHETTA020:
		case SUB_ETICHETTA021:
		case SUB_ETICHETTA022:
		case SUB_ETICHETTA023:
		case SUB_ETICHETTA024:
		case SUB_ETICHETTA025:
		case SUB_ETICHETTA026:
		case SUB_ETICHETTA027:
		case SUB_ETICHETTA028:
		case SUB_ETICHETTA029:
		case SUB_ETICHETTA030:
		case SUB_ETICHETTA031:
		case SUB_ETICHETTA032:
		case SUB_ETICHETTA033:
		case SUB_ETICHETTA034:
		case SUB_ETICHETTA035:
		case SUB_ETICHETTA036:
		case SUB_ETICHETTA037:
		case SUB_ETICHETTA038:
		case SUB_ETICHETTA039:
		{
			int index = nID - SUB_ETICHETTA000;

			if (m_pEsamiView->m_pDynForm[sub_etichetta000 + index] == NULL)			
				CLegendaDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, sub_etichetta000 + index, lColore, lIDFaseBlocco);			

			break;
		}

		case BTN_LIBEROTASTOCHIUSURAFASE000:
		case BTN_LIBEROTASTOCHIUSURAFASE001:
		case BTN_LIBEROTASTOCHIUSURAFASE002:
		case BTN_LIBEROTASTOCHIUSURAFASE003:
		case BTN_LIBEROTASTOCHIUSURAFASE004:
		case BTN_LIBEROTASTOCHIUSURAFASE005:
		case BTN_LIBEROTASTOCHIUSURAFASE006:
		case BTN_LIBEROTASTOCHIUSURAFASE007:
		case BTN_LIBEROTASTOCHIUSURAFASE008:
		case BTN_LIBEROTASTOCHIUSURAFASE009:
		case BTN_LIBEROTASTOCHIUSURAFASE010:
		case BTN_LIBEROTASTOCHIUSURAFASE011:
		case BTN_LIBEROTASTOCHIUSURAFASE012:
		case BTN_LIBEROTASTOCHIUSURAFASE013:
		case BTN_LIBEROTASTOCHIUSURAFASE014:
		case BTN_LIBEROTASTOCHIUSURAFASE015:
		case BTN_LIBEROTASTOCHIUSURAFASE016:
		case BTN_LIBEROTASTOCHIUSURAFASE017:
		case BTN_LIBEROTASTOCHIUSURAFASE018:
		case BTN_LIBEROTASTOCHIUSURAFASE019:
		{
			int index = nID - BTN_LIBEROTASTOCHIUSURAFASE000;

			if (m_pEsamiView->m_pDynForm[btn_liberotastochiusurafase000 + index] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_liberotastochiusurafase000 + index, lColore, lIDFaseBlocco);

			break;
		}

		case SUB_GRIDCL000:
		case SUB_GRIDCL001:
		case SUB_GRIDCL002:
		case SUB_GRIDCL003:
		case SUB_GRIDCL004:
		case SUB_GRIDCL005:
		case SUB_GRIDCL006:
		case SUB_GRIDCL007:
		case SUB_GRIDCL008:
		case SUB_GRIDCL009:
		case SUB_GRIDCL010:
		case SUB_GRIDCL011:
		case SUB_GRIDCL012:
		case SUB_GRIDCL013:
		case SUB_GRIDCL014:
		case SUB_GRIDCL015:
		case SUB_GRIDCL016:
		case SUB_GRIDCL017:
		case SUB_GRIDCL018:
		case SUB_GRIDCL019:
		case SUB_GRIDCL020:
		case SUB_GRIDCL021:
		case SUB_GRIDCL022:
		case SUB_GRIDCL023:
		case SUB_GRIDCL024:
		case SUB_GRIDCL025:
		case SUB_GRIDCL026:
		case SUB_GRIDCL027:
		case SUB_GRIDCL028:
		case SUB_GRIDCL029:
		case SUB_GRIDCL030:
		case SUB_GRIDCL031:
		case SUB_GRIDCL032:
		case SUB_GRIDCL033:
		case SUB_GRIDCL034:
		case SUB_GRIDCL035:
		case SUB_GRIDCL036:
		case SUB_GRIDCL037:
		case SUB_GRIDCL038:
		case SUB_GRIDCL039:
		{
			int index = nID - SUB_GRIDCL000;

			if (m_pEsamiView->m_pDynForm[sub_gridcl000 + index] == NULL)
				CEndoGridDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, sub_gridcl000 + index, lColore, lIDFaseBlocco);

			break;
		}
		case CMB_ESAMEURGENTE:
		{
			if (m_pEsamiView->m_pDynForm[cmb_esameurgente] == NULL)
				CComboDynForm1::CreateFormEx(GetParent(), this, m_pEsamiView, cmb_esameurgente, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_CODICICLASSIFICAZIONEDIAGNOSTICA:
		{
			if (m_pEsamiView->m_pDynForm[sub_codiciclassificazionediagnostica] == NULL)
				CCodiciClassificazioneDiagnosticaDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_CARDIO_PRIMA:
		{
			if (m_pEsamiView->m_pDynForm[sub_cardio_prima] == NULL)
				CCardioPrimaDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_CARDIO_DURANTE:
		{
			if (m_pEsamiView->m_pDynForm[sub_cardio_durante] == NULL)
				CCardioDuranteDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case SUB_CARDIO_DOPO:
		{
			if (m_pEsamiView->m_pDynForm[sub_cardio_dopo] == NULL)
				CCardioDopoDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}
		case EDT_ESAME_CONIUGATO:
		{
			if (m_pEsamiView->m_pDynForm[edt_esame_coniugato] == NULL)
				CEditDynForm2::CreateFormEx(GetParent(), this, m_pEsamiView, edt_esame_coniugato, lColore, lIDFaseBlocco);
			
			break;
		}
		case SUB_CENTRALEDISTAMPA:
		{
			if (m_pEsamiView->m_pDynForm[sub_centraledistampa] == NULL)
				CCentraleDiStampaDynForm::CreateFormEx(GetParent(), this, m_pEsamiView);

			break;
		}
		case SUB_MIELOGRAMMA:
		{
			if (m_pEsamiView->m_pDynForm[sub_mielogramma] == NULL)
				CMielogrammaDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, lColore, lIDFaseBlocco);

			break;
		}

		//Gabriel - TCP
		case BTN_INVIAALTRAUNITA:
		{
			if (m_pEsamiView->m_pDynForm[btn_invia_altra_unita] == NULL)
				CButtonDynForm::CreateFormEx(GetParent(), this, m_pEsamiView, btn_invia_altra_unita, lColore, lIDFaseBlocco);

			break;
		}
	}

	return bReturn;
}