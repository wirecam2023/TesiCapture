#include "stdafx.h"
#include "Endox.h"
#include "EsamiView.h"

#include <GdiPlus.h>

#include "DLL_Imaging\h\AMBase64.h"
#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\RemoteService.h"
#include "DLL_Imaging\h\AmRemoteStruct.h"

#include "AnatomiaPatologicaForm.h"
#include "CodificaDiagnosiEsameSet.h"
#include "CodificaRegionaleExSet.h"
#include "ComboAltreAnomalieSet.h"
#include "ComboBoxSet.h"
#include "ComboCauseNonCompletamentoSet.h"
#include "ComboComplicanzeSet.h"
#include "ComboConclusioniColonSet.h"
#include "ComboConclusioniScreeningSet.h"
#include "ComboDiagnosiFinaleSet.h"
#include "ComboPuliziaSet.h"
#include "ComboTolleranzaSet.h"
#include "ComboRAOSet.h"
#include "ComuniSet.h"
#include "CupWorkListManager.h"
#include "CustomDate.h"
#include "DiagnosiSet.h"
#include "DigitalSignUtil.h"
#include "EndoGridDynForm.h"
#include "EsamiAccessoriSet.h"
#include "EtichetteSet.h"
#include "ExtOrdiniSet.h"
#include "FamiliaritaSet.h"
#include "FarmaciSet.h"
#include "FieldDlg.h"
#include "IndaginiPregresseSet.h"
#include "InfermieriSet.h"
#include "InterventiChirurgiciSet.h"
#include "InterventiEndoscopiciSet.h"
#include "InviantiSet.h"
#include "IstologiaProcedureSet.h"
#include "IstologiaSet.h"
#include "IstologiaTipiSet.h"
#include "IstologiaTotForm.h"
#include "IstologiaTotForm5righe.h"
#include "IstologiaTotForm5RighePlus.h"
#include "MalattieSet.h"
#include "MediciSet.h"
#include "MonitoraggioBaseDynForm.h"
#include "MstOrganoSet.h"
#include "OsservazioniSet.h"
#include "PdfManager.h"
#include "RegioneSet.h"
#include "SediEsameSet.h"
#include "StudiSet.h"
#include "TerapieSet.h"
#include "TipoEsameSet.h"
#include "VistaMonitoraggioFarmaciSet.h"
#include "VistaUtentiMediciSet.h"
#include "SelectMedicoSolicitanteDlg.h"

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CEsamiView::GetFieldPaziente(int nField, CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement, BOOL bOnlyIsValid)
{
	switch (nField)
	{
	case paziente_progressivo:
	{
		if (bOnlyIsValid)
			return TRUE;

		tagElement.strFieldValue.Format("%li", m_PazTempSet.m_lContatore);
		listElements.AddTail(tagElement);

		AddElementToDocument("paziente_progressivo", tagElement.strFieldValue);
		break;
	}
	case paziente_codicefiscale:
	{
		//strTagName = "paziente_codicefiscale";
		tagElement.strFieldValue = m_PazTempSet.m_sCodFisc;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_codicefiscale", tagElement.strFieldValue);
		break;
	}
	case paziente_codicefiscale_largo:
	{
		//strTagName = "paziente_codicefiscale_largo";

		CString sTemp = m_PazTempSet.m_sCodFisc;
		sTemp.Trim();

		if (!sTemp.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			CRect rectTot = tagElement.rectInMm;
			double dCellWidth = (double)rectTot.Width() / (double)16;
			for (int i = 0; i < m_PazTempSet.m_sCodFisc.GetLength(); i++)
			{
				tagElement.hAlignment = HPDF_TALIGN_CENTER;
				tagElement.lRotation = ROTATION_NONE;
				tagElement.strFieldValue = m_PazTempSet.m_sCodFisc.Mid(i, 1);
				tagElement.strFieldValue.MakeUpper();

				tagElement.rectInMm.left = rectTot.left + (LONG)(dCellWidth * (double)i);
				tagElement.rectInMm.top = rectTot.top;
				tagElement.rectInMm.right = rectTot.left + (LONG)(dCellWidth * (double)(i + 1));
				tagElement.rectInMm.bottom = rectTot.bottom;

				listElements.AddTail(tagElement);
			}
		}

		AddElementToDocument("paziente_codicefiscale_largo", tagElement.strFieldValue);
		break;
	}
	case paziente_codicesanitario:
	{
		//strTagName = "paziente_codicesanitario";

		tagElement.strFieldValue = m_PazTempSet.m_sCodSanit;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_codicesanitario", tagElement.strFieldValue);
		break;
	}
	case paziente_cognome:
	{
		//strTagName = "paziente_cognome";

		// Sandro 20/11/2013 // RAS 20130186 //
		if (theApp.m_bMostraSecondoCognome)
			tagElement.strFieldValue = m_PazTempSet.m_sCognome + " " + m_PazTempSet.m_sCognome2;
		else
			tagElement.strFieldValue = m_PazTempSet.m_sCognome;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_cognome", tagElement.strFieldValue);
		break;
	}
	case paziente_nome:
	{
		//strTagName = "paziente_nome";

		tagElement.strFieldValue = m_PazTempSet.m_sNome;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_nome", tagElement.strFieldValue);
		break;
	}
	case paziente_nominativo_cn:
	{
		//strTagName = "paziente_nominativo_cn";

		tagElement.strFieldValue = m_PazTempSet.m_sCognome;
		tagElement.strFieldValue.Trim();

		// Sandro 20/11/2013 // RAS 20130186 //
		if (theApp.m_bMostraSecondoCognome)
		{
			tagElement.strFieldValue += " " + m_PazTempSet.m_sCognome2;
			tagElement.strFieldValue.Trim();
		}

		tagElement.strFieldValue += " " + m_PazTempSet.m_sNome;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_nominativo_cn", tagElement.strFieldValue);
		break;
	}
	case paziente_nominativo_nc:
	{
		//strTagName = "paziente_nominativo_nc";

		tagElement.strFieldValue = m_PazTempSet.m_sNome;
		tagElement.strFieldValue.Trim();

		tagElement.strFieldValue += " " + m_PazTempSet.m_sCognome;
		tagElement.strFieldValue.Trim();

		// Sandro 20/11/2013 // RAS 20130186 //
		if (theApp.m_bMostraSecondoCognome)
		{
			tagElement.strFieldValue += " " + m_PazTempSet.m_sCognome2;
			tagElement.strFieldValue.Trim();
		}

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_nominativo_nc", tagElement.strFieldValue);
		break;
	}
	case paziente_sesso:
	{
		//strTagName = "paziente_sesso";

		switch (m_PazTempSet.m_lSessoPaz)
		{
		case -1:
			tagElement.strFieldValue = theApp.GetMessageString(IDS_PAZIENTIDLG_ND);
			break;
		case 0:
			tagElement.strFieldValue = theApp.GetMessageString(IDS_PAZIENTIDLG_MALE);
			break;
		case 1:
			tagElement.strFieldValue = theApp.GetMessageString(IDS_PAZIENTIDLG_FEMALE);
			break;
		case 2:
			tagElement.strFieldValue = theApp.GetMessageString(IDS_PAZIENTIDLG_AMBIGOUS);
			break;
		case 3:
			tagElement.strFieldValue = theApp.GetMessageString(IDS_PAZIENTIDLG_NOTAPPLICABLE);
			break;
		case 4:
			tagElement.strFieldValue = theApp.GetMessageString(IDS_PAZIENTIDLG_OTHER);
			break;
		default:
			break;
		}

		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_sesso", tagElement.strFieldValue);
		break;
	}
	case paziente_natoil:
	{
		//strTagName = "paziente_natoil";

		if (!m_PazTempSet.IsFieldNull(&m_PazTempSet.m_lNatoIlCustom) && m_PazTempSet.m_lNatoIlCustom > 0)
			tagElement.strFieldValue = CCustomDate(m_PazTempSet.m_lNatoIlCustom).GetDate("%d/%m/%Y");
		else
			tagElement.strFieldValue = theApp.GetMessageString(IDS_NOPATIENTDATA);
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_natoil", tagElement.strFieldValue);
		break;
	}
	case paziente_natoa:
	{
		//strTagName = "paziente_natoa";

		tagElement.strFieldValue = m_PazTempSet.m_sNatoA;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_natoa", tagElement.strFieldValue);
		break;
	}
	case paziente_professione:
	{
		//strTagName = "paziente_professione";

		tagElement.strFieldValue = m_PazTempSet.m_sProfessione;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_professione", tagElement.strFieldValue);
		break;
	}
	case paziente_via:
	{
		//strTagName = "paziente_via";

		tagElement.strFieldValue = m_PazTempSet.m_sVia;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_via", tagElement.strFieldValue);
		break;
	}
	case paziente_citta:
	{
		//strTagName = "paziente_citta";

		tagElement.strFieldValue = m_PazTempSet.m_sCitta;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_citta", tagElement.strFieldValue);
		break;
	}
	case paziente_cap:
	{
		//strTagName = "paziente_cap";

		tagElement.strFieldValue = m_PazTempSet.m_sCAP;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_cap", tagElement.strFieldValue);
		break;
	}
	case paziente_provincia:
	{
		//strTagName = "paziente_provincia";

		tagElement.strFieldValue = m_PazTempSet.m_sProvincia;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_provincia", tagElement.strFieldValue);
		break;
	}
	case paziente_recapito:
	{
		//strTagName = "paziente_recapito";

		tagElement.strFieldValue = m_PazTempSet.m_sCAP;
		tagElement.strFieldValue.Trim();
		tagElement.strFieldValue += " " + m_PazTempSet.m_sCitta;
		tagElement.strFieldValue.Trim();
		if (!m_PazTempSet.m_sProvincia.IsEmpty())
			tagElement.strFieldValue += " (" + m_PazTempSet.m_sProvincia + ")";
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_recapito", tagElement.strFieldValue);
		break;
	}
	case paziente_telefono1:
	{
		//strTagName = "paziente_telefono1";

		tagElement.strFieldValue = m_PazTempSet.m_sTelefono1;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_telefono1", tagElement.strFieldValue);
		break;
	}
	case paziente_telefono2:
	{
		//strTagName = "paziente_telefono2";

		tagElement.strFieldValue = m_PazTempSet.m_sTelefono2;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_telefono2", tagElement.strFieldValue);
		break;
	}
	case paziente_fax:
	{
		//strTagName = "paziente_fax";

		tagElement.strFieldValue = m_PazTempSet.m_sFax;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_fax", tagElement.strFieldValue);
		break;
	}
	case paziente_cellulare1:
	{
		//strTagName = "paziente_cellulare1";

		tagElement.strFieldValue = m_PazTempSet.m_sCellulare1;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_cellulare1", tagElement.strFieldValue);
		break;
	}
	case paziente_cellulare2:
	{
		//strTagName = "paziente_cellulare2";

		tagElement.strFieldValue = m_PazTempSet.m_sCellulare2;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_cellulare2", tagElement.strFieldValue);
		break;
	}
	case paziente_email:
	{
		//strTagName = "paziente_email";

		tagElement.strFieldValue = m_PazTempSet.m_sEmail;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_email", tagElement.strFieldValue);
		break;
	}
	case paziente_medicocurante:
	{
		//strTagName = "paziente_medicocurante";

		tagElement.strFieldValue = m_PazTempSet.m_sMedicoCurante;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_medicocurante", tagElement.strFieldValue);
		break;
	}
	case paziente_medicotelefono:
	{
		//strTagName = "paziente_medicotelefono";

		tagElement.strFieldValue = m_PazTempSet.m_sMedicoTel;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_medicotelefono", tagElement.strFieldValue);
		break;
	}
	case paziente_medicoindirizzo:
	{
		//strTagName = "paziente_medicoindirizzo";

		tagElement.strFieldValue = m_PazTempSet.m_sMedicoIndirizzo;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_medicoindirizzo", tagElement.strFieldValue);
		break;
	}
	case paziente_medicoemail:
	{
		//strTagName = "paziente_medicoemail";

		tagElement.strFieldValue = m_PazTempSet.m_sMedicoEmail;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_medicoemail", tagElement.strFieldValue);
		break;
	}
	case paziente_dasegnalare:
	{
		//strTagName = "paziente_dasegnalare";

		tagElement.strFieldValue = m_PazTempSet.m_sDenSegnalato;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_dasegnalare", tagElement.strFieldValue);
		break;
	}
	case paziente_codicecliente:
	{
		//strTagName = "paziente_codicecliente";

		tagElement.strFieldValue = m_PazTempSet.m_sCodiceCliente;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_codicecliente", tagElement.strFieldValue);
		break;
	}
	case paziente_cognome2:
	{
		//strTagName = "paziente_cognome2";

		tagElement.strFieldValue = m_PazTempSet.m_sCognome2;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_cognome2", tagElement.strFieldValue);
		break;
	}
	case paziente_nominativopadre:
	{
		//strTagName = "paziente_nominativopadre";

		tagElement.strFieldValue = m_PazTempSet.m_sNominativoPadre;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_nominativopadre", tagElement.strFieldValue);
		break;
	}
	case paziente_nominativomadre:
	{
		//strTagName = "paziente_nominativomadre";

		tagElement.strFieldValue = m_PazTempSet.m_sNominativoMadre;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_nominativomadre", tagElement.strFieldValue);
		break;
	}
	case paziente_eta:
	{
		//strTagName = "paziente_eta";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = GetStringEta(m_pPazientiSet->m_lNatoIlCustom, m_pEsamiSet->m_lData, FormatoEta::AnnoMeseGiornoAbbreviato); //Gabriel BUG 6225 - Lista DO
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("paziente_eta", tagElement.strFieldValue);
		break;
	}
	case paziente_eta_soloanni:
	{
		//strTagName = "paziente_eta_soloanni";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = GetStringEta(m_pPazientiSet->m_lNatoIlCustom, m_pEsamiSet->m_lData, FormatoEta::SoloAnno); //Gabriel BUG 6225 - Lista DO
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("paziente_eta_soloanni", tagElement.strFieldValue);
		break;
	}
	case paziente_indirizzoricetta:
	{
		//strTagName = "paziente_indirizzoricetta";

		tagElement.strFieldValue = m_PazTempSet.m_sVia;
		tagElement.strFieldValue.Trim();
		tagElement.strFieldValue += " " + m_PazTempSet.m_sCitta;
		tagElement.strFieldValue.Trim();
		if (!m_PazTempSet.m_sProvincia.IsEmpty())
			tagElement.strFieldValue += " (" + m_PazTempSet.m_sProvincia + ")";
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_indirizzoricetta", tagElement.strFieldValue);
		break;
	}
	case paziente_assiden:
	{
		//strTagName = "paziente_assiden";

		tagElement.strFieldValue = m_PazTempSet.m_sAssIden;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_assiden", tagElement.strFieldValue);
		break;
	}
	case paziente_codalfa:
	{
		//strTagName = "paziente_codalfa";

		tagElement.strFieldValue = m_PazTempSet.m_sCodAlfa;
		tagElement.strFieldValue.Trim();

		if (!tagElement.strFieldValue.IsEmpty())
		{
			if (bOnlyIsValid)
				return TRUE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("paziente_codalfa", tagElement.strFieldValue);
		break;
	}
	default:
		break;
	}

	return FALSE;
}

BOOL CEsamiView::GetFieldAnamnesi(int nField, CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement, BOOL bOnlyIsValid)
{
	switch (nField)
	{
	case anamnesi_fumo:
	{
		//strTagName = "anamnesi_fumo";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CComboBoxSet(CMB_ANA_FUMO).GetFieldText(m_pEsamiSet->m_lFumo);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("anamnesi_fumo", tagElement.strFieldValue);
		break;
	}
	case anamnesi_sigarette:
	{
		//strTagName = "anamnesi_sigarette";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CComboBoxSet(CMB_ANA_SIGA).GetFieldText(m_pEsamiSet->m_lSigarette);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("anamnesi_sigarette", tagElement.strFieldValue);
		break;
	}
	case anamnesi_alcol:
	{
		//strTagName = "anamnesi_alcol";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CComboBoxSet(CMB_ANA_ALCO).GetFieldText(m_pEsamiSet->m_lAlcool);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("anamnesi_alcol", tagElement.strFieldValue);
		break;
	}
	case anamnesi_superalcolici:
	{
		//strTagName = "anamnesi_superalcolici";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CComboBoxSet(CMB_ANA_SUPE).GetFieldText(m_pEsamiSet->m_lSuperAlcolici);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("anamnesi_superalcolici", tagElement.strFieldValue);
		break;
	}
	case anamnesi_caffe:
	{
		//strTagName = "anamnesi_caffe";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CComboBoxSet(CMB_ANA_CAFF).GetFieldText(m_pEsamiSet->m_lCaffe);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("anamnesi_caffe", tagElement.strFieldValue);
		break;
	}
	case anamnesi_farmaci:
	{
		//strTagName = "anamnesi_farmaci";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_sDenFarmaci;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("anamnesi_farmaci", tagElement.strFieldValue);
		break;
	}
	case anamnesi_assunzione:
	{
		//strTagName = "anamnesi_assunzione";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CComboBoxSet(CMB_ANA_ASSU).GetFieldText(m_pEsamiSet->m_lAssunzione);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("anamnesi_assunzione", tagElement.strFieldValue);
		break;
	}
	case anamnesi_peso:
	{
		//strTagName = "anamnesi_peso";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fPeso))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue.Format("%.2f", m_pEsamiSet->m_fPeso);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("anamnesi_peso", tagElement.strFieldValue);
		break;
	}
	case anamnesi_altezza:
	{
		//strTagName = "anamnesi_altezza";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fAltezza))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue.Format("%.2f", m_pEsamiSet->m_fAltezza);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("anamnesi_altezza", tagElement.strFieldValue);
		break;
	}
	case anamnesi_bmi:
	{
		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if ((!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fPeso)) && (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fAltezza)))
			{
				if ((m_pEsamiSet->m_fPeso > 0) && (m_pEsamiSet->m_fAltezza > 0))
				{
					if (bOnlyIsValid)
						return TRUE;

					tagElement.strFieldValue.Format("%.2f", (m_pEsamiSet->m_fPeso * 10000.0f) / (m_pEsamiSet->m_fAltezza * m_pEsamiSet->m_fAltezza));
					listElements.AddTail(tagElement);
				}
			}
		}
		AddElementToDocument("anamnesi_bmi", tagElement.strFieldValue);
		break;
	}
	case anamnesi_bsa:
	{
		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if ((!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fPeso)) && (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fAltezza)))
			{
				if ((m_pEsamiSet->m_fPeso > 0) && (m_pEsamiSet->m_fAltezza > 0))
				{
					if (bOnlyIsValid)
						return TRUE;

					tagElement.strFieldValue.Format("%.2f", m_pEsamiSet->m_fBSA);
					listElements.AddTail(tagElement);
				}
			}
		}
		AddElementToDocument("anamnesi_bsa", tagElement.strFieldValue);
		break;
	}

	default:
		break;
	}

	return FALSE;
}

BOOL CEsamiView::GetFieldPreliminari(int nField, CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement, BOOL bOnlyIsValid)
{
	switch (nField)
	{
	case preliminari_progressivo:
	{
		//strTagName = "preliminari_progressivo";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (bOnlyIsValid)
				return TRUE;

			tagElement.strFieldValue.Format("%li", m_pEsamiSet->m_lContatore);
			listElements.AddTail(tagElement);
		}
		AddElementToDocument("preliminari_progressivo", tagElement.strFieldValue);
		break;
	}
	case preliminari_data:
	{
		//strTagName = "preliminari_data";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_lData).GetDate("%d/%m/%Y");
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_data", tagElement.strFieldValue);
		break;
	}
	case preliminari_data_eng:
	{
		//strTagName = "preliminari_data_eng";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_lData).GetDate("%m/%d/%Y");
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_data_eng", tagElement.strFieldValue);
		break;
	}
	case preliminari_ora:
	{
		//strTagName = "preliminari_ora";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_lData).GetDate("%H:%M");
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_ora", tagElement.strFieldValue);
		break;
	}
	case preliminari_tipoesame:
	{
		//strTagName = "preliminari_tipoesame";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CTipoEsameSet().GetDescrizione(m_pEsamiSet->m_lIDEsame);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_tipoesame", tagElement.strFieldValue);
		break;
	}
	case preliminari_tipoesame_codice:
	{
		//strTagName = "preliminari_tipoesame_codice";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue.Format("%li", m_pEsamiSet->m_lIDEsame);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_tipoesame_codice", tagElement.strFieldValue);
		break;
	}
	case preliminari_tipoesame_colore:
	{
		//strTagName = "preliminari_tipoesame_colore";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (bOnlyIsValid)
				return TRUE;

			tagElement.rgbColor = CTipoEsameSet().GetSfondo(m_pEsamiSet->m_lIDEsame);

			if (tagElement.rgbColor == GetSysColor(COLOR_BTNFACE))
				tagElement.rgbColor = RGB_WHITE;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("preliminari_tipoesame_colore", tagElement.strFieldValue);
		break;
	}
	case preliminari_sedeesame:
	{
		//strTagName = "preliminari_sedeesame";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CSediEsameSet().GetDescrizione(m_pEsamiSet->m_lIDSedeEsame, FALSE);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_sedeesame", tagElement.strFieldValue);
		break;
	}
	case preliminari_salaesame:
	{
		//strTagName = "preliminari_salaesame";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_sSalaEsame;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_salaesame", tagElement.strFieldValue);
		break;
	}
	case preliminari_progressivoannuale:
	{
		//strTagName = "preliminari_progressivoannuale";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_sProgressivoAnno;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_progressivoannuale", tagElement.strFieldValue);
		break;
	}
	case preliminari_codiceprenotazione:
	{
		//strTagName = "preliminari_codiceprenotazione";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_sCodicePrenotazione;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_codiceprenotazione", tagElement.strFieldValue);
		break;
	}
	case preliminari_internoesterno:
	{
		//strTagName = "preliminari_internoesterno";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = (m_pEsamiSet->m_lProvenienza == 0 ? theApp.GetMessageString(IDS_INVIANTE_INTERNO) : theApp.GetMessageString(IDS_INVIANTE_ESTERNO));
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_internoesterno", tagElement.strFieldValue);
		break;
	}
	case preliminari_inviante1:
	{
		//strTagName = "preliminari_inviante1";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = "";
			switch (m_pEsamiSet->m_lProvenienza)
			{
			case INTERNO:
			{
				tagElement.strFieldValue = CComboBoxSet(CMB_ESA_OSPEDALE).GetFieldText(m_pEsamiSet->m_lOspedale);
				break;
			}
			case ESTERNO:
			{
				tagElement.strFieldValue = CInviantiSet("EInviantiEsterni").GetFieldText(m_pEsamiSet->m_lInviante);
				break;
			}
			}
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_inviante1", tagElement.strFieldValue);
		break;
	}
	case preliminari_inviante2:
	{
		//strTagName = "preliminari_inviante2";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = "";
			switch (m_pEsamiSet->m_lProvenienza)
			{
			case INTERNO:
			{
				tagElement.strFieldValue = CInviantiSet("EInviantiInterni").GetFieldText(m_pEsamiSet->m_lInviante);
				break;
			}
			case ESTERNO:
			{
				tagElement.strFieldValue = m_pEsamiSet->m_sInvMedico;
				break;
			}
			}
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_inviante2", tagElement.strFieldValue);
		break;
	}
	case preliminari_inviante3:
	{
		//strTagName = "preliminari_inviante3";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = "";
			switch (m_pEsamiSet->m_lProvenienza)
			{
			case INTERNO:
			{
				tagElement.strFieldValue = CComboBoxSet(CMB_ESA_TIPODEGENZAINT).GetFieldText(m_pEsamiSet->m_lTipoDegenzaInterno);
				break;
			}
			case ESTERNO:
			{
				tagElement.strFieldValue = CComboBoxSet(CMB_ESA_TIPODEGENZAEST).GetFieldText(m_pEsamiSet->m_lTipoDegenzaEsterno);
				break;
			}
			}
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_inviante3", tagElement.strFieldValue);
		break;
	}
	case preliminari_inviante_codice:
	{
		//strTagName = "preliminari_inviante_codice";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lInviante) && (m_pEsamiSet->m_lInviante > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue.Format("%li", m_pEsamiSet->m_lInviante);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_inviante_codice", tagElement.strFieldValue);
		break;
	}
	case preliminari_medico1:
	{
		//strTagName = "preliminari_medico1";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (CMediciSet().IsLiberoFromContatore(m_pEsamiSet->m_lMedico))
				tagElement.strFieldValue = m_pEsamiSet->m_sMedicoLibero;
			else
				tagElement.strFieldValue = CMediciSet().GetFieldTextFromContatore(m_pEsamiSet->m_lMedico);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_medico1", tagElement.strFieldValue);
		break;
	}
	case preliminari_medico1_firma0:
	case preliminari_medico1_firma1:
	case preliminari_medico1_firma2:
	case preliminari_medico1_firma3:
	case preliminari_medico1_firma4:
	case preliminari_medico1_firma5:
	case preliminari_medico1_firma6:
	case preliminari_medico1_firma7:
	case preliminari_medico1_firma8:
	case preliminari_medico1_firma9:
	{
		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			int nIndexTemp = nField - preliminari_medico1_firma0;
			ASSERT((nIndexTemp >= 0) && (nIndexTemp <= 9));

			tagElement.strFieldValue = CMediciSet().GetFieldFirmaFromContatore(m_pEsamiSet->m_lMedico, nIndexTemp);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		if (nField == preliminari_medico1_firma0)
			AddElementToDocument("preliminari_medico1_firma0", tagElement.strFieldValue);
		if (nField == preliminari_medico1_firma1)
			AddElementToDocument("preliminari_medico1_firma1", tagElement.strFieldValue);
		if (nField == preliminari_medico1_firma2)
			AddElementToDocument("preliminari_medico1_firma2", tagElement.strFieldValue);
		if (nField == preliminari_medico1_firma3)
			AddElementToDocument("preliminari_medico1_firma3", tagElement.strFieldValue);
		if (nField == preliminari_medico1_firma4)
			AddElementToDocument("preliminari_medico1_firma4", tagElement.strFieldValue);
		if (nField == preliminari_medico1_firma5)
			AddElementToDocument("preliminari_medico1_firma5", tagElement.strFieldValue);
		if (nField == preliminari_medico1_firma6)
			AddElementToDocument("preliminari_medico1_firma6", tagElement.strFieldValue);
		if (nField == preliminari_medico1_firma7)
			AddElementToDocument("preliminari_medico1_firma7", tagElement.strFieldValue);
		if (nField == preliminari_medico1_firma8)
			AddElementToDocument("preliminari_medico1_firma8", tagElement.strFieldValue);
		if (nField == preliminari_medico1_firma9)
			AddElementToDocument("preliminari_medico1_firma9", tagElement.strFieldValue);
		break;
	}
	case preliminari_medico2:
	{
		//strTagName = "preliminari_medico2";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (CMediciSet().IsLiberoFromContatore(m_pEsamiSet->m_lAssistente))
				tagElement.strFieldValue = m_pEsamiSet->m_sAssistenteLibero;
			else
				tagElement.strFieldValue = CMediciSet().GetFieldTextFromContatore(m_pEsamiSet->m_lAssistente);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_medico2", tagElement.strFieldValue);
		break;
	}
	case preliminari_medico2_firma0:
	case preliminari_medico2_firma1:
	case preliminari_medico2_firma2:
	case preliminari_medico2_firma3:
	case preliminari_medico2_firma4:
	case preliminari_medico2_firma5:
	case preliminari_medico2_firma6:
	case preliminari_medico2_firma7:
	case preliminari_medico2_firma8:
	case preliminari_medico2_firma9:
	{
		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			int nIndexTemp = nField - preliminari_medico2_firma0;
			ASSERT((nIndexTemp >= 0) && (nIndexTemp <= 9));

			tagElement.strFieldValue = CMediciSet().GetFieldFirmaFromContatore(m_pEsamiSet->m_lAssistente, nIndexTemp);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}

		if (nField == preliminari_medico2_firma0)
			AddElementToDocument("preliminari_medico2_firma0", tagElement.strFieldValue);
		if (nField == preliminari_medico2_firma1)
			AddElementToDocument("preliminari_medico2_firma1", tagElement.strFieldValue);
		if (nField == preliminari_medico2_firma2)
			AddElementToDocument("preliminari_medico2_firma2", tagElement.strFieldValue);
		if (nField == preliminari_medico2_firma3)
			AddElementToDocument("preliminari_medico2_firma3", tagElement.strFieldValue);
		if (nField == preliminari_medico2_firma4)
			AddElementToDocument("preliminari_medico2_firma4", tagElement.strFieldValue);
		if (nField == preliminari_medico2_firma5)
			AddElementToDocument("preliminari_medico2_firma5", tagElement.strFieldValue);
		if (nField == preliminari_medico2_firma6)
			AddElementToDocument("preliminari_medico2_firma6", tagElement.strFieldValue);
		if (nField == preliminari_medico2_firma7)
			AddElementToDocument("preliminari_medico2_firma7", tagElement.strFieldValue);
		if (nField == preliminari_medico2_firma8)
			AddElementToDocument("preliminari_medico2_firma8", tagElement.strFieldValue);
		if (nField == preliminari_medico2_firma9)
			AddElementToDocument("preliminari_medico2_firma9", tagElement.strFieldValue);

		break;
	}
	case preliminari_infermiere1:
	{
		//strTagName = "preliminari_infermiere1";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CInfermieriSet().GetFieldText(m_pEsamiSet->m_lInfermiere1);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_infermiere1", tagElement.strFieldValue);
		break;
	}
	case preliminari_infermiere1_matricola:
	{
		//strTagName = "preliminari_infermiere1_matricola";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CInfermieriSet().GetMatricola(m_pEsamiSet->m_lInfermiere1);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_infermiere1_matricola", tagElement.strFieldValue);
		break;
	}
	case preliminari_infermiere2:
	{
		//strTagName = "preliminari_infermiere2";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CInfermieriSet().GetFieldText(m_pEsamiSet->m_lInfermiere2);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_infermiere2", tagElement.strFieldValue);
		break;
	}
	case preliminari_infermiere2_matricola:
	{
		//strTagName = "preliminari_infermiere2_matricola";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = CInfermieriSet().GetMatricola(m_pEsamiSet->m_lInfermiere2);
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_infermiere2_matricola", tagElement.strFieldValue);
		break;
	}
	case preliminari_anestesista:
	{
		//strTagName = "preliminari_anestesista";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_sAnestesista;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_anestesista", tagElement.strFieldValue);
		break;
	}
	case preliminari_camera:
	{
		//strTagName = "preliminari_camera";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lCamera) && (m_pEsamiSet->m_lCamera > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue.Format("%li", m_pEsamiSet->m_lCamera);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_camera", tagElement.strFieldValue);
		break;
	}
	case preliminari_indicazioni:
	{
		//strTagName = "preliminari_indicazioni";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_sIndicazioni;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_indicazioni", tagElement.strFieldValue);
		break;
	}
	case preliminari_indicazioni_grande:
	{
		//strTagName = "preliminari_indicazioni_grande";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_sIndicazioni;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.bCanExpand = TRUE;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_indicazioni_grande", tagElement.strFieldValue);
		break;
	}
	case preliminari_farmacotrial:
	{
		//strTagName = "preliminari_farmacotrial";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_sFarmacoTrial;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_farmacotrial", tagElement.strFieldValue);
		break;
	}
	case preliminari_premedicazioni:
	{
		//strTagName = "preliminari_premedicazioni";

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_sPremedicazioni;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument("preliminari_premedicazioni", tagElement.strFieldValue);
		break;
	}
	default:
		break;
	}

	return FALSE;
}

BOOL CEsamiView::GetFieldTestiLiberi(int nField, CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement, BOOL bOnlyIsValid)
{
	switch (nField)
	{
	case libero_000:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 0);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto000;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 0), tagElement.strFieldValue);
		break;
	}
	case libero_001:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 1);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto001;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 1), tagElement.strFieldValue);
		break;
	}
	case libero_002:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 2);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto002;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 2), tagElement.strFieldValue);
		break;
	}
	case libero_003:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 3);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto003;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 3), tagElement.strFieldValue);
		break;
	}
	case libero_004:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 4);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto004;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 4), tagElement.strFieldValue);
		break;
	}
	case libero_005:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 5);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto005;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 5), tagElement.strFieldValue);
		break;
	}
	case libero_006:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 6);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto006;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 6), tagElement.strFieldValue);
		break;
	}
	case libero_007:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 7);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto007;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 7), tagElement.strFieldValue);
		break;
	}
	case libero_008:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 8);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto008;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 8), tagElement.strFieldValue);
		break;
	}
	case libero_009:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 9);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto009;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 9), tagElement.strFieldValue);
		break;
	}
	case libero_010:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 10);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto010;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 10), tagElement.strFieldValue);
		break;
	}
	case libero_011:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 11);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto011;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 11), tagElement.strFieldValue);
		break;
	}
	case libero_012:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 12);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto012;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 12), tagElement.strFieldValue);
		break;
	}
	case libero_013:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 13);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto013;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 13), tagElement.strFieldValue);
		break;
	}
	case libero_014:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 14);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto014;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 14), tagElement.strFieldValue);
		break;
	}
	case libero_015:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 15);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto015;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 15), tagElement.strFieldValue);
		break;
	}
	case libero_016:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 16);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto016;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 16), tagElement.strFieldValue);
		break;
	}
	case libero_017:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 17);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto017;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 17), tagElement.strFieldValue);
		break;
	}
	case libero_018:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 18);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto018;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 18), tagElement.strFieldValue);
		break;
	}
	case libero_019:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 19);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto019;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 19), tagElement.strFieldValue);
		break;
	}
	case libero_020:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 20);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto020;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 20), tagElement.strFieldValue);
		break;
	}
	case libero_021:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 21);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto021;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 21), tagElement.strFieldValue);
		break;
	}
	case libero_022:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 22);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto022;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 22), tagElement.strFieldValue);
		break;
	}
	case libero_023:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 23);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto023;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 23), tagElement.strFieldValue);
		break;
	}
	case libero_024:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 24);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto024;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 24), tagElement.strFieldValue);
		break;
	}
	case libero_025:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 25);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto025;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 25), tagElement.strFieldValue);
		break;
	}
	case libero_026:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 26);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto026;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 26), tagElement.strFieldValue);
		break;
	}
	case libero_027:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 27);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto027;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 27), tagElement.strFieldValue);
		break;
	}
	case libero_028:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 28);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto028;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 28), tagElement.strFieldValue);
		break;
	}
	case libero_029:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 29);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto029;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 29), tagElement.strFieldValue);
		break;
	}
	case libero_030:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 30);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto030;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 30), tagElement.strFieldValue);
		break;
	}
	case libero_031:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 31);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto031;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 31), tagElement.strFieldValue);
		break;
	}
	case libero_032:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 32);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto032;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 32), tagElement.strFieldValue);
		break;
	}
	case libero_033:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 33);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto033;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 33), tagElement.strFieldValue);
		break;
	}
	case libero_034:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 34);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto034;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 34), tagElement.strFieldValue);
		break;
	}
	case libero_035:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 35);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto035;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 35), tagElement.strFieldValue);
		break;
	}
	case libero_036:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 36);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto036;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 36), tagElement.strFieldValue);
		break;
	}
	case libero_037:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 37);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto037;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 37), tagElement.strFieldValue);
		break;
	}
	case libero_038:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 38);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto038;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 38), tagElement.strFieldValue);
		break;
	}
	case libero_039:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 39);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto039;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 39), tagElement.strFieldValue);
		break;
	}
	case libero_040:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 40);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto040;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 40), tagElement.strFieldValue);
		break;
	}
	case libero_041:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 41);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto041;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 41), tagElement.strFieldValue);
		break;
	}
	case libero_042:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 42);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto042;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 42), tagElement.strFieldValue);
		break;
	}
	case libero_043:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 43);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto043;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 43), tagElement.strFieldValue);
		break;
	}
	case libero_044:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 44);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto044;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 44), tagElement.strFieldValue);
		break;
	}
	case libero_045:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 45);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto045;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 45), tagElement.strFieldValue);
		break;
	}
	case libero_046:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 46);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto046;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 46), tagElement.strFieldValue);
		break;
	}
	case libero_047:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 47);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto047;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 47), tagElement.strFieldValue);
		break;
	}
	case libero_048:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 48);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto048;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 48), tagElement.strFieldValue);
		break;
	}
	case libero_049:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 49);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto049;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 49), tagElement.strFieldValue);
		break;
	}
	case libero_050:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 50);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto050;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 50), tagElement.strFieldValue);
		break;
	}
	case libero_051:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 51);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto051;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 51), tagElement.strFieldValue);
		break;
	}
	case libero_052:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 52);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto052;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 52), tagElement.strFieldValue);
		break;
	}
	case libero_053:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 53);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto053;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 53), tagElement.strFieldValue);
		break;
	}
	case libero_054:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 54);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto054;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 54), tagElement.strFieldValue);
		break;
	}
	case libero_055:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 55);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto055;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 55), tagElement.strFieldValue);
		break;
	}
	case libero_056:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 56);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto056;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 56), tagElement.strFieldValue);
		break;
	}
	case libero_057:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 57);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto057;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 57), tagElement.strFieldValue);
		break;
	}
	case libero_058:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 58);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto058;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 58), tagElement.strFieldValue);
		break;
	}
	case libero_059:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 59);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto059;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 59), tagElement.strFieldValue);
		break;
	}
	case libero_060:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 60);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto060;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 60), tagElement.strFieldValue);
		break;
	}
	case libero_061:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 61);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto061;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 61), tagElement.strFieldValue);
		break;
	}
	case libero_062:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 62);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto062;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 62), tagElement.strFieldValue);
		break;
	}
	case libero_063:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 63);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto063;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 63), tagElement.strFieldValue);
		break;
	}
	case libero_064:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 64);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto064;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 64), tagElement.strFieldValue);
		break;
	}
	case libero_065:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 65);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto065;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 65), tagElement.strFieldValue);
		break;
	}
	case libero_066:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 66);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto066;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 66), tagElement.strFieldValue);
		break;
	}
	case libero_067:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 67);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto067;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 67), tagElement.strFieldValue);
		break;
	}
	case libero_068:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 68);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto068;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 68), tagElement.strFieldValue);
		break;
	}
	case libero_069:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 69);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto069;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 69), tagElement.strFieldValue);
		break;
	}
	case libero_070:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 70);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto070;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 70), tagElement.strFieldValue);
		break;
	}
	case libero_071:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 71);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto071;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 71), tagElement.strFieldValue);
		break;
	}
	case libero_072:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 72);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto072;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 72), tagElement.strFieldValue);
		break;
	}
	case libero_073:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 73);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto073;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 73), tagElement.strFieldValue);
		break;
	}
	case libero_074:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 74);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto074;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 74), tagElement.strFieldValue);
		break;
	}
	case libero_075:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 75);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto075;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 75), tagElement.strFieldValue);
		break;
	}
	case libero_076:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 76);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto076;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 76), tagElement.strFieldValue);
		break;
	}
	case libero_077:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 77);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto077;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 77), tagElement.strFieldValue);
		break;
	}
	case libero_078:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 78);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto078;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 78), tagElement.strFieldValue);
		break;
	}
	case libero_079:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 79);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto079;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 79), tagElement.strFieldValue);
		break;
	}
	case libero_080:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 80);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto080;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 80), tagElement.strFieldValue);
		break;
	}
	case libero_081:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 81);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto081;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 81), tagElement.strFieldValue);
		break;
	}
	case libero_082:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 82);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto082;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 82), tagElement.strFieldValue);
		break;
	}
	case libero_083:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 83);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto083;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 83), tagElement.strFieldValue);
		break;
	}
	case libero_084:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 84);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto084;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 84), tagElement.strFieldValue);
		break;
	}
	case libero_085:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 85);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto085;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 85), tagElement.strFieldValue);
		break;
	}
	case libero_086:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 86);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto086;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 86), tagElement.strFieldValue);
		break;
	}
	case libero_087:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 87);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto087;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 87), tagElement.strFieldValue);
		break;
	}
	case libero_088:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 88);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto088;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 88), tagElement.strFieldValue);
		break;
	}
	case libero_089:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 89);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto089;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 89), tagElement.strFieldValue);
		break;
	}
	case libero_090:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 90);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto090;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 90), tagElement.strFieldValue);
		break;
	}
	case libero_091:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 91);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto091;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 91), tagElement.strFieldValue);
		break;
	}
	case libero_092:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 92);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto092;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 92), tagElement.strFieldValue);
		break;
	}
	case libero_093:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 93);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto093;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 93), tagElement.strFieldValue);
		break;
	}
	case libero_094:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 94);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto094;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 94), tagElement.strFieldValue);
		break;
	}
	case libero_095:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 95);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto095;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 95), tagElement.strFieldValue);
		break;
	}
	case libero_096:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 96);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto096;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 96), tagElement.strFieldValue);
		break;
	}
	case libero_097:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 97);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto097;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 97), tagElement.strFieldValue);
		break;
	}
	case libero_098:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 98);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto098;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 98), tagElement.strFieldValue);
		break;
	}
	case libero_099:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO", 99);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTesto099;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO", 99), tagElement.strFieldValue);
		break;
	}

	case libero_rtf_000_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 0);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt000;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf000;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 0), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_000_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 0);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt000;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf000;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 0), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_001_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 1);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt001;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf001;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 1), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_001_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 1);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt001;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf001;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 1), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_002_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 2);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt002;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf002;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 2), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_002_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 2);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt002;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf002;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 2), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_003_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 3);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt003;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf003;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 3), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_003_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 3);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt003;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf003;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 3), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_004_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 4);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt004;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf004;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 4), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_004_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 4);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt004;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf004;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 4), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_005_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 5);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt005;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf005;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 5), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_005_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 5);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt005;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf005;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 5), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_006_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 6);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt006;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf006;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 6), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_006_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 6);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt006;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf006;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 6), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_007_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 7);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt007;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf007;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 7), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_007_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 7);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt007;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf007;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 7), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_008_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 8);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt008;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf008;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 8), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_008_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 8);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt008;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf008;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 8), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_009_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 9);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt009;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf009;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 9), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_009_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 9);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt009;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf009;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 9), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_010_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 10);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt010;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf010;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 10), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_010_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 10);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt010;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf010;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 10), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_011_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 11);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt011;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf011;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 11), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_011_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 11);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt011;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf011;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 11), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_012_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 12);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt012;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf012;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 12), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_012_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 12);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt012;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf012;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 12), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_013_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 13);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt013;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf013;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 13), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_013_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 13);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt013;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf013;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 13), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_014_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 14);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt014;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf014;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 14), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_014_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 14);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt014;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf014;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 14), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_015_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 15);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt015;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf015;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 15), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_015_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 15);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt015;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf015;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 15), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_016_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 16);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt016;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf016;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 16), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_016_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 16);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt016;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf016;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 16), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_017_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 17);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt017;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf017;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 17), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_017_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 17);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt017;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf017;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 17), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_018_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 18);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt018;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf018;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 18), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_018_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 18);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt018;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf018;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 18), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_019_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 19);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt019;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf019;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 19), tagElement.strFieldValue);
		break;
	}
	case libero_rtf_019_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_RTF", 19);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoTxt019;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoRtf019;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_RTF", 19), tagElement.strFieldValue);
		break;
	}
	case libero_cl_000_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 0);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt000;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf000;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 0), tagElement.strFieldValue);
		break;
	}
	case libero_cl_000_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 0);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt000;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf000;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 0), tagElement.strFieldValue);
		break;
	}
	case libero_cl_001_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 1);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt001;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf001;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 1), tagElement.strFieldValue);
		break;
	}
	case libero_cl_001_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 1);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt001;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf001;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 1), tagElement.strFieldValue);
		break;
	}
	case libero_cl_002_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 2);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt002;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf002;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 2), tagElement.strFieldValue);
		break;
	}
	case libero_cl_002_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 2);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt002;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf002;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 2), tagElement.strFieldValue);
		break;
	}
	case libero_cl_003_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 3);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt003;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf003;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 3), tagElement.strFieldValue);
		break;
	}
	case libero_cl_003_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 3);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt003;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf003;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 3), tagElement.strFieldValue);
		break;
	}
	case libero_cl_004_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 4);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt004;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf004;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 4), tagElement.strFieldValue);
		break;
	}
	case libero_cl_004_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 4);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt004;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf004;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 4), tagElement.strFieldValue);
		break;
	}
	case libero_cl_005_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 5);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt005;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf005;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 5), tagElement.strFieldValue);
		break;
	}
	case libero_cl_005_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 5);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt005;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf005;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 5), tagElement.strFieldValue);
		break;
	}
	case libero_cl_006_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 6);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt006;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf006;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 6), tagElement.strFieldValue);
		break;
	}
	case libero_cl_006_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 6);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt006;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf006;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 6), tagElement.strFieldValue);
		break;
	}
	case libero_cl_007_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 7);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt007;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf007;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 7), tagElement.strFieldValue);
		break;
	}
	case libero_cl_007_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 7);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt007;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf007;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 7), tagElement.strFieldValue);
		break;
	}
	case libero_cl_008_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 8);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt008;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf008;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 8), tagElement.strFieldValue);
		break;
	}
	case libero_cl_008_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 8);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt008;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf008;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 8), tagElement.strFieldValue);
		break;
	}
	case libero_cl_009_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 9);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt009;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf009;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 9), tagElement.strFieldValue);
		break;
	}
	case libero_cl_009_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 9);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt009;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf009;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 9), tagElement.strFieldValue);
		break;
	}
	case libero_cl_010_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 10);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt010;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf010;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 10), tagElement.strFieldValue);
		break;
	}
	case libero_cl_010_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 10);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt010;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf010;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 10), tagElement.strFieldValue);
		break;
	}
	case libero_cl_011_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 11);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt011;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf011;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 11), tagElement.strFieldValue);
		break;
	}
	case libero_cl_011_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 11);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt011;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf011;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 11), tagElement.strFieldValue);
		break;
	}
	case libero_cl_012_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 12);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt012;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf012;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 12), tagElement.strFieldValue);
		break;
	}
	case libero_cl_012_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 12);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt012;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf012;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 12), tagElement.strFieldValue);
		break;
	}
	case libero_cl_013_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 13);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt013;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf013;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 13), tagElement.strFieldValue);
		break;
	}
	case libero_cl_013_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 13);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt013;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf013;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 13), tagElement.strFieldValue);
		break;
	}
	case libero_cl_014_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 14);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt014;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf014;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 14), tagElement.strFieldValue);
		break;
	}
	case libero_cl_014_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 14);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt014;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf014;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 14), tagElement.strFieldValue);
		break;
	}
	case libero_cl_015_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 15);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt015;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf015;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 15), tagElement.strFieldValue);
		break;
	}
	case libero_cl_015_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 15);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt015;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf015;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 15), tagElement.strFieldValue);
		break;
	}
	case libero_cl_016_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 16);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt016;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf016;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 16), tagElement.strFieldValue);
		break;
	}
	case libero_cl_016_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 16);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt016;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf016;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 16), tagElement.strFieldValue);
		break;
	}
	case libero_cl_017_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 17);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt017;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf017;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 17), tagElement.strFieldValue);
		break;
	}
	case libero_cl_017_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 17);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt017;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf017;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 17), tagElement.strFieldValue);
		break;
	}
	case libero_cl_018_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 18);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt018;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf018;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 18), tagElement.strFieldValue);
		break;
	}
	case libero_cl_018_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 18);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt018;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf018;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 18), tagElement.strFieldValue);
		break;
	}
	case libero_cl_019_fisso:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 19);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt019;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf019;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 19), tagElement.strFieldValue);
		break;
	}
	case libero_cl_019_grande:
	{
		//strTagName = CEtichetteSet().GetLabel("TESTO_CL", 19);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLTxt019;
			tagElement.strFieldValue.Trim();

			if (!tagElement.strFieldValue.IsEmpty())
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = m_pEsamiSet->m_setEP.m_sTestoCLRtf019;
				tagElement.bCanExpand = TRUE;
				tagElement.lFieldType = TYPE_RTF;
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("TESTO_CL", 19), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_000:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 0);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra000) && (m_pEsamiSet->m_setEP.m_lDataOra000 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra000).GetDateForPrint(theApp.m_iRadioDate[0]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 0), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_001:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 1);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra001) && (m_pEsamiSet->m_setEP.m_lDataOra001 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra001).GetDateForPrint(theApp.m_iRadioDate[1]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 1), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_002:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 2);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra002) && (m_pEsamiSet->m_setEP.m_lDataOra002 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra002).GetDateForPrint(theApp.m_iRadioDate[2]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 2), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_003:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 3);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra003) && (m_pEsamiSet->m_setEP.m_lDataOra003 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra003).GetDateForPrint(theApp.m_iRadioDate[3]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 3), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_004:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 4);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra004) && (m_pEsamiSet->m_setEP.m_lDataOra004 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra004).GetDateForPrint(theApp.m_iRadioDate[4]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 4), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_005:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 5);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra005) && (m_pEsamiSet->m_setEP.m_lDataOra005 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra005).GetDateForPrint(theApp.m_iRadioDate[5]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 5), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_006:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 6);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra006) && (m_pEsamiSet->m_setEP.m_lDataOra006 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra006).GetDateForPrint(theApp.m_iRadioDate[6]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 6), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_007:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 7);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra007) && (m_pEsamiSet->m_setEP.m_lDataOra007 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra007).GetDateForPrint(theApp.m_iRadioDate[7]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 7), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_008:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 8);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra008) && (m_pEsamiSet->m_setEP.m_lDataOra008 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra008).GetDateForPrint(theApp.m_iRadioDate[8]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 8), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_009:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 9);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra009) && (m_pEsamiSet->m_setEP.m_lDataOra009 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra009).GetDateForPrint(theApp.m_iRadioDate[9]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 9), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_010:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 10);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra010) && (m_pEsamiSet->m_setEP.m_lDataOra010 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra010).GetDateForPrint(theApp.m_iRadioDate[10]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 10), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_011:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 11);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra011) && (m_pEsamiSet->m_setEP.m_lDataOra011 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra011).GetDateForPrint(theApp.m_iRadioDate[11]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 11), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_012:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 12);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra012) && (m_pEsamiSet->m_setEP.m_lDataOra012 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra012).GetDateForPrint(theApp.m_iRadioDate[12]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 12), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_013:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 13);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra013) && (m_pEsamiSet->m_setEP.m_lDataOra013 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra013).GetDateForPrint(theApp.m_iRadioDate[13]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 13), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_014:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 14);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra014) && (m_pEsamiSet->m_setEP.m_lDataOra014 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra014).GetDateForPrint(theApp.m_iRadioDate[14]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 14), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_015:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 15);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra015) && (m_pEsamiSet->m_setEP.m_lDataOra015 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra015).GetDateForPrint(theApp.m_iRadioDate[15]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 15), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_016:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 16);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra016) && (m_pEsamiSet->m_setEP.m_lDataOra016 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra016).GetDateForPrint(theApp.m_iRadioDate[16]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 16), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_017:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 17);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra017) && (m_pEsamiSet->m_setEP.m_lDataOra017 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra017).GetDateForPrint(theApp.m_iRadioDate[17]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 17), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_018:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 18);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra018) && (m_pEsamiSet->m_setEP.m_lDataOra018 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra018).GetDateForPrint(theApp.m_iRadioDate[18]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 18), tagElement.strFieldValue);
		break;
	}
	case libero_dataora_019:
	{
		//strTagName = CEtichetteSet().GetLabel("DATAORA_TESTO", 19);

		if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			if (!m_pEsamiSet->m_setEP.IsFieldNull(&m_pEsamiSet->m_setEP.m_lDataOra019) && (m_pEsamiSet->m_setEP.m_lDataOra019 > 0))
			{
				if (bOnlyIsValid)
					return TRUE;

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_setEP.m_lDataOra019).GetDateForPrint(theApp.m_iRadioDate[19]);
				listElements.AddTail(tagElement);
			}
		}
		AddElementToDocument(CEtichetteSet().GetLabel("DATAORA_TESTO", 19), tagElement.strFieldValue);
		break;
	}
	default:
		break;
	}

	return FALSE;
}

BOOL CEsamiView::GetFieldGridCL(int nField, CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement, BOOL bOnlyIsValid)
{
	switch (nField)
	{
	case esame_gridcl000:
	case esame_gridcl001:
	case esame_gridcl002:
	case esame_gridcl003:
	case esame_gridcl004:
	case esame_gridcl005:
	case esame_gridcl006:
	case esame_gridcl007:
	case esame_gridcl008:
	case esame_gridcl009:
	case esame_gridcl010:
	case esame_gridcl011:
	case esame_gridcl012:
	case esame_gridcl013:
	case esame_gridcl014:
	case esame_gridcl015:
	case esame_gridcl016:
	case esame_gridcl017:
	case esame_gridcl018:
	case esame_gridcl019:
	case esame_gridcl020:
	case esame_gridcl021:
	case esame_gridcl022:
	case esame_gridcl023:
	case esame_gridcl024:
	case esame_gridcl025:
	case esame_gridcl026:
	case esame_gridcl027:
	case esame_gridcl028:
	case esame_gridcl029:
	case esame_gridcl030:
	case esame_gridcl031:
	case esame_gridcl032:
	case esame_gridcl033:
	case esame_gridcl034:
	case esame_gridcl035:
	case esame_gridcl036:
	case esame_gridcl037:
	case esame_gridcl038:
	case esame_gridcl039:
	{
		int index = nField - esame_gridcl000;
		CEndoGridDynForm* pGrid = (CEndoGridDynForm*)m_pDynForm[sub_gridcl000 + index];

		if (pGrid != NULL)
		{
			if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
			{
				CString sElement;
				sElement.Format("gridcl%03d", index);
				CList<reportElement*> *root = AddElementToDocument(sElement, "");

				pGrid->ExpandAll();

				long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

				CRect rectTot = tagElement.rectInMm;

				int numRows = pGrid->GetLines();
				int columnWidth = rectTot.Width() / 2;

				CRect rectRow = rectTot;
				rectRow.bottom = rectRow.top + lRowHeight;

				BOOL bItalic = tagElement.lfFont.lfItalic;
				long lfWeight = tagElement.lfFont.lfWeight;

				for (int r = 0; r < numRows; r++)
				{
					if (pGrid->IsCategory(r)) //Se è una categoria lascio il 100% dello spazio per il caption
					{
						tagElement.lfFont.lfItalic = TRUE;
						tagElement.lfFont.lfWeight = FW_BOLD;

						CRect rectTemp = rectRow; //Contiene la riga che sto stampando							

						tagElement.strFieldValue = pGrid->GetItemText(r, 0);
						tagElement.rectInMm = rectTemp;

						tagElement.hAlignment = HPDF_TALIGN_LEFT;
						tagElement.bPaintBorder = FALSE;
						tagElement.bCanExpand = TRUE;

						listElements.AddTail(tagElement);
						AddElementToDocument(tagElement.strFieldValue, "", root);
					}
					else //altrimenti chiedo al controllo la posizione del divider
					{
						//colonna titolo
						CRect rectCol1 = rectRow;
						tagElement.lfFont.lfItalic = TRUE;
						tagElement.lfFont.lfWeight = FW_BOLD;

						int width = rectRow.Width();

						float dim = ((float)width) * ((float)pGrid->GetViewDivider());
						rectCol1.right = rectRow.left + (long)dim;

						tagElement.strFieldValue = pGrid->GetItemText(r, 0);
						tagElement.hAlignment = HPDF_TALIGN_LEFT;
						tagElement.bPaintBorder = FALSE;
						tagElement.rectInMm = rectCol1;
						tagElement.bCanExpand = TRUE;

						listElements.AddTail(tagElement);
						CString sTitolo;

						//colonna valore
						CRect rectCol2 = rectRow;
						tagElement.lfFont.lfItalic = bItalic;
						tagElement.lfFont.lfWeight = lfWeight;

						rectCol2.left = rectCol1.right;

						tagElement.strFieldValue = pGrid->GetItemText(r, 1);
						tagElement.rectInMm = rectCol2;

						tagElement.hAlignment = HPDF_TALIGN_LEFT;
						tagElement.bPaintBorder = FALSE;
						tagElement.bCanExpand = TRUE;

						listElements.AddTail(tagElement);

						AddElementToDocument(sTitolo, tagElement.strFieldValue, root);
					}

					rectRow.OffsetRect(0, lRowHeight + 2);
				}

			}
		}

		break;
	}

	default:
		break;
	}

	return FALSE;
}

BOOL CEsamiView::GetField(CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement, BOOL bOnlyIsValid)
{
	int nField = -1;
	for (int i = 0; i < endox_report_field_num_total; i++)
	{
		if (CFieldDlg::m_strFieldEndox[i].sReport.CompareNoCase(tagElement.strFieldValue) == 0)
		{
			nField = i;
			break;
		}
	}

	tagElement.strFieldValue = "";

	BOOL bReturn = FALSE;
	bReturn = GetFieldPaziente(nField, listElements, tagElement, bOnlyIsValid);

	if (!bOnlyIsValid || bReturn == FALSE) //entro solo se non bOnlyIsValid, oppure se bOnlyIsValid ma bReturn è ancora FALSE
		bReturn = GetFieldAnamnesi(nField, listElements, tagElement, bOnlyIsValid);

	if (!bOnlyIsValid || bReturn == FALSE) //entro solo se non bOnlyIsValid, oppure se bOnlyIsValid ma bReturn è ancora FALSE
		bReturn = GetFieldPreliminari(nField, listElements, tagElement, bOnlyIsValid);

	if (!bOnlyIsValid || bReturn == FALSE) //entro solo se non bOnlyIsValid, oppure se bOnlyIsValid ma bReturn è ancora FALSE
		bReturn = GetFieldTestiLiberi(nField, listElements, tagElement, bOnlyIsValid);

	if (!bOnlyIsValid || bReturn == FALSE) //entro solo se non bOnlyIsValid, oppure se bOnlyIsValid ma bReturn è ancora FALSE
		bReturn = GetFieldGridCL(nField, listElements, tagElement, bOnlyIsValid);

	if (!bOnlyIsValid || bReturn == FALSE)
	{
		switch (nField)
		{
			case esame_procdiag_fisso:
			{
				//strTagName = "esame_procdiag_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sProcDiagnostiche;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("esame_procdiag_fisso", tagElement.strFieldValue);
				break;
			}
			case esame_procdiag_grande:
			{
				//strTagName = "esame_procdiag_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sProcDiagnostiche;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("esame_procdiag_grande", tagElement.strFieldValue);
				break;
			}
			case esame_proctera_fisso:
			{
				//strTagName = "esame_proctera_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sProcTerapeutiche;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("esame_proctera_fisso", tagElement.strFieldValue);
				break;
			}
			case esame_proctera_grande:
			{
				//strTagName = "esame_proctera_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sProcTerapeutiche;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("esame_proctera_grande", tagElement.strFieldValue);
				break;
			}
			case esame_condottofino:
			{
				//strTagName = "esame_condottofino";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sEstensione;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("esame_condottofino", tagElement.strFieldValue);
				break;
			}

			case esame_firma_smartcard_utente:
			{
				//strTagName = "esame_firma_smartcard_utente";

				if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
				{
					CString sSmartCardUtente;
					if (CDigitalSignUtil::GetSmartCardUtente(&sSmartCardUtente))
					{
						tagElement.strFieldValue = sSmartCardUtente;
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}

				AddElementToDocument("esame_firma_smartcard_utente", tagElement.strFieldValue);
				break;
			}
			case esami_firma_smartcard_numero:
			{
				//strTagName = "esami_firma_smartcard_numero";

				if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
				{
					CString sSmartCardNumero;
					if (CDigitalSignUtil::GetSmartCardNumero(&sSmartCardNumero))
					{
						tagElement.strFieldValue = sSmartCardNumero;
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}

				AddElementToDocument("esami_firma_smartcard_numero", tagElement.strFieldValue);
				break;
			}
			case esami_firma_smartcard_entecertificato:
			{
				//strTagName = "esami_firma_smartcard_entecertificato";

				if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
				{
					CString sSmartCardEnteCertificato;
					if (CDigitalSignUtil::GetSmartCardEnteCertificato(&sSmartCardEnteCertificato))
					{
						tagElement.strFieldValue = sSmartCardEnteCertificato;
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}

				AddElementToDocument("esami_firma_smartcard_entecertificato", tagElement.strFieldValue);
				break;
			}
			case esame_firma_sostituzione_motivo:
			{
				//strTagName = "esame_firma_sostituzione_motivo";

				if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
				{
					if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
					{
						long lIDPrecedente;
						CString sDataPrecedente;
						CString sMotivoPrecedente;

						if (CPdfManager().GetDatiUltimoPdfFirmato(m_pEsamiSet->m_lContatore, lIDPrecedente, sDataPrecedente, sMotivoPrecedente))
						{
							if (bOnlyIsValid)
								return TRUE;

							CString sIDPrecedente;
							sIDPrecedente.Format("%li", lIDPrecedente);

							tagElement.strFieldValue.Format(theApp.GetMessageString(IDS_FIRMA_ANNULLAMENTO), sIDPrecedente, sDataPrecedente, sMotivoPrecedente);

							listElements.AddTail(tagElement);
						}
					}
				}

				AddElementToDocument("esame_firma_sostituzione_motivo", tagElement.strFieldValue);
				break;
			}
			case esame_firma_annullamento_idprecedente:
			{
				//strTagName = "esame_firma_annullamento_idprecedente";

				if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
				{
					if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
					{
						long lIDPrecedente = 0;
						long lVersioneReferto = 0;
						if (CPdfManager().GetDatiUltimoPdfFirmatoIDVersioneReferto(m_pEsamiSet->m_lContatore, lIDPrecedente, lVersioneReferto))
						{
							if (bOnlyIsValid)
								return TRUE;

							tagElement.strFieldValue.Format("%li", lIDPrecedente);
							listElements.AddTail(tagElement);
						}
					}
				}

				AddElementToDocument("esame_firma_annullamento_idprecedente", tagElement.strFieldValue);
				break;
			}
			case esame_firma_annullamento_dataprecedente:
			{
				//strTagName = "esame_firma_annullamento_dataprecedente";

				if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
				{
					if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
					{
						CString sDataPrecedente;
						if (CPdfManager().GetDatiUltimoPdfFirmatoData(m_pEsamiSet->m_lContatore, sDataPrecedente))
						{
							if (bOnlyIsValid)
								return TRUE;

							tagElement.strFieldValue = sDataPrecedente;
							listElements.AddTail(tagElement);
						}
					}
				}

				AddElementToDocument("esame_firma_annullamento_dataprecedente", tagElement.strFieldValue);
				break;
			}
			case esame_firma_annullamento_motivo:
			{
				//strTagName = "esame_firma_annullamento_motivo";

				if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
				{
					if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
					{
						CString sMotivoPrecedente;
						if (CPdfManager().GetDatiUltimoPdfFirmatoMotivo(m_pEsamiSet->m_lContatore, sMotivoPrecedente))
						{
							if (bOnlyIsValid)
								return TRUE;

							tagElement.strFieldValue = sMotivoPrecedente;
							listElements.AddTail(tagElement);
						}
					}
				}

				AddElementToDocument("esame_firma_annullamento_motivo", tagElement.strFieldValue);
				break;
			}
			/*
			case esame_firma_versione_referto:
			{
			if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
			{
			if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
			{
			long lIDPrecedente = 0;
			long lVersioneReferto = 0;

			// nessuna delle due funziona davvero bene :-( bisogna pensare a qualcos'altro //
			// if (CPdfManager().GetDatiUltimoPdfFirmatoIDVersioneReferto(m_pEsamiSet->m_lContatore, lIDPrecedente, lVersioneReferto))
			// if (CPdfManager().GetDatiUltimoPdf(m_pEsamiSet->m_lContatore, lIDPrecedente, lVersioneReferto))
			{
			if (bOnlyIsValid)
			return TRUE;

			lVersioneReferto++;
			tagElement.strFieldValue.Format("%li", lVersioneReferto);
			listElements.AddTail(tagElement);
			}
			}
			}

			AddElementToDocument("paziente_progressivo", tagElement.strFieldValue);
			break;
			}
			*/

			case altridati_valutazione:
			{
				//strTagName = "altridati_valutazione";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sValutazione;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_valutazione", tagElement.strFieldValue);
				break;
			}
			case altridati_prossimocontrollo:
			{
				//strTagName = "altridati_prossimocontrollo";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_lDataControllo).GetDate("%d/%m/%Y");
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_prossimocontrollo", tagElement.strFieldValue);
				break;
			}
			case altridati_complicanze:
			{
				//strTagName = "altridati_complicanze";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sComplicanzeOld;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_complicanze", tagElement.strFieldValue);
				break;
			}
			case altridati_terapia:
			{
				//strTagName = "altridati_terapia";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sComplicanze1;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_terapia", tagElement.strFieldValue);
				break;
			}
			case altridati_provvedimenti:
			{
				//strTagName = "altridati_provvedimenti";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sComplicanze2;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_provvedimenti", tagElement.strFieldValue);
				break;
			}
			case altridati_esito:
			{
				//strTagName = "altridati_esito";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sComplicanze3;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_esito", tagElement.strFieldValue);
				break;
			}
			case altridati_tipovisita:
			{
				//strTagName = "altridati_tipovisita";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sTipoVisita;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_tipovisita", tagElement.strFieldValue);
				break;
			}
			case altridati_studio:
			{
				//strTagName = "altridati_studio";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sStudio;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_studio", tagElement.strFieldValue);
				break;
			}
			case altridati_quadro:
			{
				//strTagName = "altridati_quadro";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sQuadro;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_quadro", tagElement.strFieldValue);
				break;
			}
			case altridati_guarigione:
			{
				//strTagName = "altridati_guarigione";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sGuarigione;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_guarigione", tagElement.strFieldValue);
				break;
			}
			case altridati_durata:
			{
				//strTagName = "altridati_durata";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lDurata) && (m_pEsamiSet->m_lDurata > 0))
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.strFieldValue.Format("%li", m_pEsamiSet->m_lDurata);
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_durata", tagElement.strFieldValue);
				break;
			}
			case altridati_difficolta:
			{
				//strTagName = "altridati_difficolta";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lDifficolta) && (m_pEsamiSet->m_lDifficolta > 0))
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.strFieldValue.Format("%li", m_pEsamiSet->m_lDifficolta);
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_difficolta", tagElement.strFieldValue);
				break;
			}
			case altridati_terapiaconsigliata:
			{
				//strTagName = "altridati_terapiaconsigliata";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sTerapia;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_terapiaconsigliata", tagElement.strFieldValue);
				break;
			}
			case altridati_strumenti:
			{
				//strTagName = "altridati_strumenti";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sStrumenti;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_strumenti", tagElement.strFieldValue);
				break;
			}
			case altridati_accessori:
			{
				//strTagName = "altridati_accessori";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sAccessori;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_accessori", tagElement.strFieldValue);
				break;
			}
			case altridati_note:
			{
				//strTagName = "altridati_note";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sAppunti;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_note", tagElement.strFieldValue);
				break;
			}
			case altridati_biopsie:
			{
				//strTagName = "altridati_biopsie";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = CIstologiaSet().GetEseguitoPrelievo(m_pEsamiSet->m_lContatore);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("altridati_biopsie", tagElement.strFieldValue);
				break;
			}

			case referto_referto_fisso:
			{
				//strTagName = "referto_referto_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sRefertoTestoRtf; // CRefertoSet().GetRefertoRtf(m_pEsamiSet->m_lContatore); // Sandro 09/01/2015 // GetRefertoTxt //
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.lFieldType = TYPE_RTF;
						listElements.AddTail(tagElement);
					}
					else
					{
						tagElement.strFieldValue = m_pEsamiSet->m_sConclusioni;
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("referto_referto_fisso", tagElement.strFieldValue);
				break;
			}
			case referto_referto_grande:
			{
				//strTagName = "referto_referto_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sRefertoTestoRtf; // CRefertoSet().GetRefertoRtf(m_pEsamiSet->m_lContatore); // Sandro 09/01/2015 // GetRefertoTxt //
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						tagElement.lFieldType = TYPE_RTF;
						listElements.AddTail(tagElement);
					}
					else
					{
						tagElement.strFieldValue = m_pEsamiSet->m_sConclusioni;
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							tagElement.bCanExpand = TRUE;
							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("referto_referto_grande", tagElement.strFieldValue);
				break;
			}

			case libero_riferimento:
			{
				//strTagName = "libero_riferimento";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sCodEsame;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("libero_riferimento", tagElement.strFieldValue);
				break;
			}
			case libero_integrazioni:
			{
				//strTagName = "libero_integrazioni";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sIntegrazioni;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("libero_integrazioni", tagElement.strFieldValue);
				break;
			}

			case form_codificadiagnosi_fisso:
			{
				//strTagName = "form_codificadiagnosi_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CCodificaDiagnosiEsameSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_codificadiagnosi_fisso", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectOrgano;
							rectOrgano.left = rectTot.left + ((rectTot.Width() * 0) / 7);
							rectOrgano.top = rectTot.top;
							rectOrgano.right = rectTot.left + ((rectTot.Width() * 1) / 7);
							rectOrgano.bottom = rectTot.top + lRowHeight;

							CRect rectSede;
							rectSede.left = rectTot.left + ((rectTot.Width() * 1) / 7);
							rectSede.top = rectTot.top;
							rectSede.right = rectTot.left + ((rectTot.Width() * 3) / 7);
							rectSede.bottom = rectTot.top + lRowHeight;

							CRect rectDiagnosi;
							rectDiagnosi.left = rectTot.left + ((rectTot.Width() * 3) / 7);
							rectDiagnosi.top = rectTot.top;
							rectDiagnosi.right = rectTot.left + ((rectTot.Width() * 7) / 7);
							rectDiagnosi.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectOrgano.bottom < rectTot.bottom)
							{
								// organo //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_ORGANO);
								tagElement.rectInMm = rectOrgano;
								listElements.AddTail(tagElement);
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_SEDEANATOMICA);
								tagElement.rectInMm = rectSede;
								listElements.AddTail(tagElement);
								rectSede.OffsetRect(0, lRowHeight);

								// diagnosi //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DIAGNOSI);
								tagElement.rectInMm = rectDiagnosi;
								listElements.AddTail(tagElement);
								rectDiagnosi.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//

							while (!setTemp.IsEOF())
							{
								if (rectOrgano.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								// organo //
								CString strTemp = CMstOrganoSet().GetFieldText(setTemp.m_lOrgano);
								strTemp.Trim();
								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectOrgano;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("organo", tagElement.strFieldValue, parent);
								}
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								strTemp = setTemp.m_sSede;
								strTemp.Trim();
								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectSede;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("sede", tagElement.strFieldValue, parent);
								}
								rectSede.OffsetRect(0, lRowHeight);

								// diagnosi //
								strTemp = setTemp.m_sDiagnosiEsame;
								strTemp.Trim();
								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectDiagnosi;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("diagnosi", tagElement.strFieldValue, parent);
								}
								rectDiagnosi.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}

						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_codificadiagnosi_grande:
			{
				//strTagName = "form_codificadiagnosi_grande";			

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CCodificaDiagnosiEsameSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_codificadiagnosi_grande", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectNumero;
							rectNumero.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectNumero.top = rectTot.top;
							rectNumero.right = rectTot.left + ((rectTot.Width() * 4) / 100);
							rectNumero.bottom = rectTot.top + lRowHeight;

							CRect rectOrgano;
							rectOrgano.left = rectTot.left + ((rectTot.Width() * 4) / 100);
							rectOrgano.top = rectTot.top;
							rectOrgano.right = rectTot.left + ((rectTot.Width() * 15) / 100);
							rectOrgano.bottom = rectTot.top + lRowHeight;

							CRect rectSede;
							rectSede.left = rectTot.left + ((rectTot.Width() * 15) / 100);
							rectSede.top = rectTot.top;
							rectSede.right = rectTot.left + ((rectTot.Width() * 40) / 100);
							rectSede.bottom = rectTot.top + lRowHeight;

							CRect rectDiagnosi;
							rectDiagnosi.left = rectTot.left + ((rectTot.Width() * 40) / 100);
							rectDiagnosi.top = rectTot.top;
							rectDiagnosi.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectDiagnosi.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							// numero //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_RIGA);
							tagElement.rectInMm = rectNumero;
							listElements.AddTail(tagElement);
							rectNumero.OffsetRect(0, lRowHeight);

							// organo //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_ORGANO);
							tagElement.rectInMm = rectOrgano;
							listElements.AddTail(tagElement);
							rectOrgano.OffsetRect(0, lRowHeight);

							// sede //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_SEDEANATOMICA);
							tagElement.rectInMm = rectSede;
							listElements.AddTail(tagElement);
							rectSede.OffsetRect(0, lRowHeight);

							// diagnosi //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DIAGNOSI);
							tagElement.rectInMm = rectDiagnosi;
							listElements.AddTail(tagElement);
							rectDiagnosi.OffsetRect(0, lRowHeight);

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//		



							int iRow = 1;
							while (!setTemp.IsEOF())
							{
								parent = AddElementToDocument("record", "", parent);

								// numero //
								tagElement.strFieldValue.Format("%d", iRow);
								tagElement.rectInMm = rectNumero;
								listElements.AddTail(tagElement);
								rectNumero.OffsetRect(0, lRowHeight);
								AddElementToDocument("numero", tagElement.strFieldValue);

								// organo //
								CString strTemp = CMstOrganoSet().GetFieldText(setTemp.m_lOrgano);
								strTemp.Trim();
								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectOrgano;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("organo", tagElement.strFieldValue, parent);
								}
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								strTemp = setTemp.m_sSede;
								strTemp.Trim();
								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectSede;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("sede", tagElement.strFieldValue, parent);
								}
								rectSede.OffsetRect(0, lRowHeight);

								// diagnosi //
								strTemp = setTemp.m_sDiagnosiEsame;
								strTemp.Trim();
								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectDiagnosi;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("diagnosi", tagElement.strFieldValue, parent);
								}
								rectDiagnosi.OffsetRect(0, lRowHeight);

								//strComplexTagValue += "</record>";

								//
								iRow++;
								setTemp.MoveNext();
							}

						}

						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_codificaregionale_fisso:
			{
				//strTagName = "form_codificaregionale_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CRegioneSet setReg;
					setReg.SetOpenFilter(strFilter);
					if (setReg.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setReg.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setReg.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_codificaregionale_fisso", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectCodNaz;
							rectCodNaz.left = rectTot.left + ((rectTot.Width() * 0) / 8);
							rectCodNaz.top = rectTot.top;
							rectCodNaz.right = rectTot.left + ((rectTot.Width() * 1) / 8);
							rectCodNaz.bottom = rectTot.top + lRowHeight;

							CRect rectCodReg;
							rectCodReg.left = rectTot.left + ((rectTot.Width() * 1) / 8);
							rectCodReg.top = rectTot.top;
							rectCodReg.right = rectTot.left + ((rectTot.Width() * 2) / 8);
							rectCodReg.bottom = rectTot.top + lRowHeight;

							CRect rectDescrizione;
							rectDescrizione.left = rectTot.left + ((rectTot.Width() * 2) / 8);
							rectDescrizione.top = rectTot.top;
							rectDescrizione.right = rectTot.left + ((rectTot.Width() * 7) / 8);
							rectDescrizione.bottom = rectTot.top + lRowHeight;

							CRect rectQuantita;
							rectQuantita.left = rectTot.left + ((rectTot.Width() * 7) / 8);
							rectQuantita.top = rectTot.top;
							rectQuantita.right = rectTot.left + ((rectTot.Width() * 8) / 8);
							rectQuantita.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectCodNaz.bottom < rectTot.bottom)
							{
								// codice nazionale //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_CODREG);
								tagElement.rectInMm = rectCodNaz;
								listElements.AddTail(tagElement);
								rectCodNaz.OffsetRect(0, lRowHeight);

								// codice regionale //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_CODLOC);
								tagElement.rectInMm = rectCodReg;
								listElements.AddTail(tagElement);
								rectCodReg.OffsetRect(0, lRowHeight);

								// descrizione //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DESCRIZIONE);
								tagElement.rectInMm = rectDescrizione;
								listElements.AddTail(tagElement);
								rectDescrizione.OffsetRect(0, lRowHeight);

								// quantità //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_QUANTITA);
								tagElement.rectInMm = rectQuantita;
								listElements.AddTail(tagElement);
								rectQuantita.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//



							while (!setReg.IsEOF())
							{
								if (rectCodNaz.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								strFilter.Format("Contatore=%li", setReg.m_lCodice);

								CCodificaRegionaleExSet setTemp;
								setTemp.SetOpenFilter(strFilter);

								if (setTemp.OpenRecordset("CEsamiView::AddField"))
								{
									if (!setTemp.IsEOF())
									{
										// codice nazionale //
										tagElement.strFieldValue = setTemp.m_sCodiceNazionale;
										tagElement.rectInMm = rectCodNaz;
										listElements.AddTail(tagElement);
										rectCodNaz.OffsetRect(0, lRowHeight);
										AddElementToDocument("codice_nazionale", tagElement.strFieldValue, parent);

										// codice regionale //
										CString strTemp = setTemp.m_sCodiceRegionale;
										strTemp.Trim();
										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectCodReg;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("codice_regionale", tagElement.strFieldValue, parent);
										}
										rectCodReg.OffsetRect(0, lRowHeight);

										// descrizione //
										strTemp = setTemp.m_sDescrizione;
										strTemp.Trim();
										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectDescrizione;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("descrizione", tagElement.strFieldValue, parent);
										}
										rectDescrizione.OffsetRect(0, lRowHeight);

										// quantità //
										strTemp.Format("%li", setReg.m_lQuantita);
										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectQuantita;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("quantita", tagElement.strFieldValue, parent);
										}
										rectQuantita.OffsetRect(0, lRowHeight);
									}

									setTemp.CloseRecordset("CEsamiView::AddField");
								}

								//
								setReg.MoveNext();
							}
						}
						setReg.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_codificaregionale_grande:
			{
				//strTagName = "form_codificaregionale_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CRegioneSet setReg;
					setReg.SetOpenFilter(strFilter);
					if (setReg.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setReg.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setReg.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_codificaregionale_grande", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectCodReg;
							rectCodReg.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectCodReg.top = rectTot.top;
							rectCodReg.right = rectTot.left + ((rectTot.Width() * 15) / 100);
							rectCodReg.bottom = rectTot.top + lRowHeight;

							CRect rectDescrizione;
							rectDescrizione.left = rectTot.left + ((rectTot.Width() * 15) / 100);
							rectDescrizione.top = rectTot.top;
							rectDescrizione.right = rectTot.left + ((rectTot.Width() * 85) / 100);
							rectDescrizione.bottom = rectTot.top + lRowHeight;

							CRect rectQuantita;
							rectQuantita.left = rectTot.left + ((rectTot.Width() * 85) / 100);
							rectQuantita.top = rectTot.top;
							rectQuantita.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectQuantita.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							// codice regionale //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_CODREG);
							tagElement.rectInMm = rectCodReg;
							listElements.AddTail(tagElement);
							rectCodReg.OffsetRect(0, lRowHeight);

							// descrizione //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DESCRIZIONE);
							tagElement.rectInMm = rectDescrizione;
							listElements.AddTail(tagElement);
							rectDescrizione.OffsetRect(0, lRowHeight);

							// quantità //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_QUANTITA);
							tagElement.rectInMm = rectQuantita;
							listElements.AddTail(tagElement);
							rectQuantita.OffsetRect(0, lRowHeight);

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setReg.IsEOF())
							{
								parent = AddElementToDocument("form_codificaregionale_grande", "", parent);

								strFilter.Format("Contatore=%li", setReg.m_lCodice);

								CCodificaRegionaleExSet setTemp;
								setTemp.SetOpenFilter(strFilter);

								if (setTemp.OpenRecordset("CEsamiView::AddField"))
								{
									if (!setTemp.IsEOF())
									{
										// codice regionale //
										CString strTemp = setTemp.m_sCodiceRegionale;
										strTemp.Trim();
										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectCodReg;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("codice_regionale", tagElement.strFieldValue, parent);
										}
										rectCodReg.OffsetRect(0, lRowHeight);

										// descrizione //
										strTemp = setTemp.m_sDescrizione;
										strTemp.Trim();
										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectDescrizione;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("descrizione", tagElement.strFieldValue, parent);
										}
										rectDescrizione.OffsetRect(0, lRowHeight);

										// quantità //
										strTemp.Format("%li", setReg.m_lQuantita);
										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectQuantita;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("quantita", tagElement.strFieldValue, parent);
										}
										rectQuantita.OffsetRect(0, lRowHeight);
									}

									setTemp.CloseRecordset("CEsamiView::AddField");
								}

								//
								setReg.MoveNext();
							}
						}
						setReg.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_codificaregionale_desc_fisso:
			{
				//strTagName = "form_codificaregionale_desc_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = CRegioneSet().GetStringDescrizioni(m_pEsamiSet->m_lContatore);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_codificaregionale_desc_fisso", tagElement.strFieldValue);

				break;
			}
			case form_codificaregionale_desc_grande:
			{
				//strTagName = "form_codificaregionale_desc_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					//Simone 16/06/2016 - Non so chi avesse questo campo di stampa, ma non è corretto che ciò che viene stampato sia diverso da form_codificaregionale_desc_fisso
					//		Nel caso sorga questo problema in futuro, creare un altro campo di stampa
					//tagElement.strFieldValue = CRegioneSet().GetStringDescrizioniGrande(m_pEsamiSet->m_lContatore);
					tagElement.strFieldValue = CRegioneSet().GetStringDescrizioni(m_pEsamiSet->m_lContatore);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_codificaregionale_desc_grande", tagElement.strFieldValue);

				break;
			}
			case form_diagnosi_fisso:
			{
				//strTagName = "form_diagnosi_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CDiagnosiSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_diagnosi_fisso", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectOrgano;
							rectOrgano.left = rectTot.left + ((rectTot.Width() * 0) / 7);
							rectOrgano.top = rectTot.top;
							rectOrgano.right = rectTot.left + ((rectTot.Width() * 1) / 7);
							rectOrgano.bottom = rectTot.top + lRowHeight;

							CRect rectSede;
							rectSede.left = rectTot.left + ((rectTot.Width() * 1) / 7);
							rectSede.top = rectTot.top;
							rectSede.right = rectTot.left + ((rectTot.Width() * 3) / 7);
							rectSede.bottom = rectTot.top + lRowHeight;

							CRect rectDiagnosi;
							rectDiagnosi.left = rectTot.left + ((rectTot.Width() * 3) / 7);
							rectDiagnosi.top = rectTot.top;
							rectDiagnosi.right = rectTot.left + ((rectTot.Width() * 7) / 7);
							rectDiagnosi.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectOrgano.bottom < rectTot.bottom)
							{
								// organo //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_ORGANO);
								tagElement.rectInMm = rectOrgano;
								listElements.AddTail(tagElement);
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_SEDEANATOMICA);
								tagElement.rectInMm = rectSede;
								listElements.AddTail(tagElement);
								rectSede.OffsetRect(0, lRowHeight);

								// diagnosi //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DIAGNOSI);
								tagElement.rectInMm = rectDiagnosi;
								listElements.AddTail(tagElement);
								rectDiagnosi.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//



							while (!setTemp.IsEOF())
							{
								if (rectOrgano.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								// organo //
								CString strTemp = CMstOrganoSet().GetFieldText(setTemp.m_lOrgano);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectOrgano;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("organo", tagElement.strFieldValue, parent);
								}
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								strTemp = setTemp.m_sSede;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectSede;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("sede", tagElement.strFieldValue, parent);
								}
								rectSede.OffsetRect(0, lRowHeight);

								// diagnosi //
								strTemp = setTemp.m_sDiagnosi;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectDiagnosi;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("diagnosi", tagElement.strFieldValue, parent);
								}
								rectDiagnosi.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_diagnosi_grande:
			{
				//strTagName = "form_diagnosi_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CDiagnosiSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_diagnosi_grande", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectOrgano;
							rectOrgano.left = rectTot.left + ((rectTot.Width() * 0) / 7);
							rectOrgano.top = rectTot.top;
							rectOrgano.right = rectTot.left + ((rectTot.Width() * 1) / 7);
							rectOrgano.bottom = rectTot.top + lRowHeight;

							CRect rectSede;
							rectSede.left = rectTot.left + ((rectTot.Width() * 1) / 7);
							rectSede.top = rectTot.top;
							rectSede.right = rectTot.left + ((rectTot.Width() * 3) / 7);
							rectSede.bottom = rectTot.top + lRowHeight;

							CRect rectDiagnosi;
							rectDiagnosi.left = rectTot.left + ((rectTot.Width() * 3) / 7);
							rectDiagnosi.top = rectTot.top;
							rectDiagnosi.right = rectTot.left + ((rectTot.Width() * 7) / 7);
							rectDiagnosi.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							// organo //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_ORGANO);
							tagElement.rectInMm = rectOrgano;
							listElements.AddTail(tagElement);
							rectOrgano.OffsetRect(0, lRowHeight);

							// sede //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_SEDEANATOMICA);
							tagElement.rectInMm = rectSede;
							listElements.AddTail(tagElement);
							rectSede.OffsetRect(0, lRowHeight);

							// diagnosi //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DIAGNOSI);
							tagElement.rectInMm = rectDiagnosi;
							listElements.AddTail(tagElement);
							rectDiagnosi.OffsetRect(0, lRowHeight);

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setTemp.IsEOF())
							{
								parent = AddElementToDocument("record", "", parent);

								// organo //
								CString strTemp = CMstOrganoSet().GetFieldText(setTemp.m_lOrgano);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectOrgano;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("organo", tagElement.strFieldValue, parent);
								}
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								strTemp = setTemp.m_sSede;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectSede;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("sede", tagElement.strFieldValue, parent);
								}
								rectSede.OffsetRect(0, lRowHeight);

								// diagnosi //
								strTemp = setTemp.m_sDiagnosi;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectDiagnosi;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("diagnosi", tagElement.strFieldValue, parent);
								}
								rectDiagnosi.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_indaginipregresse:
			{
				//strTagName = "form_indaginipregresse";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CIndaginiPregresseSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_indaginipregresse", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectIndagine;
							rectIndagine.left = rectTot.left + ((rectTot.Width() * 0) / 10);
							rectIndagine.top = rectTot.top;
							rectIndagine.right = rectTot.left + ((rectTot.Width() * 7) / 10);
							rectIndagine.bottom = rectTot.top + lRowHeight;

							CRect rectPatologico;
							rectPatologico.left = rectTot.left + ((rectTot.Width() * 7) / 10);
							rectPatologico.top = rectTot.top;
							rectPatologico.right = rectTot.left + ((rectTot.Width() * 10) / 10);
							rectPatologico.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectIndagine.bottom < rectTot.bottom)
							{
								// indagine //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_INDAGINE);
								tagElement.rectInMm = rectIndagine;
								listElements.AddTail(tagElement);
								rectIndagine.OffsetRect(0, lRowHeight);

								// patologico //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_PATOLOGICO);
								tagElement.rectInMm = rectPatologico;
								listElements.AddTail(tagElement);
								rectPatologico.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setTemp.IsEOF())
							{
								if (rectIndagine.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								// indagine //
								CString strTemp = setTemp.m_sIndagine;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectIndagine;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("indagine", tagElement.strFieldValue, parent);
								}
								rectIndagine.OffsetRect(0, lRowHeight);

								// patologico //
								strTemp = (setTemp.m_lPatologico == 1 ? theApp.GetMessageString(IDS_YES) : theApp.GetMessageString(IDS_NO));
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectPatologico;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("patologico", tagElement.strFieldValue, parent);
								}
								rectPatologico.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_pregressiesamistrumentali:
			{
				//strTagName = "form_pregressiesamistrumentali";

				// ??? prima non era implementato ??? //
				AddElementToDocument("form_pregressiesamistrumentali", tagElement.strFieldValue);

				break;
			}
			case form_interventichirurgici:
			{
				//strTagName = "form_interventichirurgici";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CInterventiChirurgiciSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_interventichirurgici", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectIntervento;
							rectIntervento.left = rectTot.left + ((rectTot.Width() * 0) / 10);
							rectIntervento.top = rectTot.top;
							rectIntervento.right = rectTot.left + ((rectTot.Width() * 7) / 10);
							rectIntervento.bottom = rectTot.top + lRowHeight;

							CRect rectData;
							rectData.left = rectTot.left + ((rectTot.Width() * 7) / 10);
							rectData.top = rectTot.top;
							rectData.right = rectTot.left + ((rectTot.Width() * 10) / 10);
							rectData.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectIntervento.bottom < rectTot.bottom)
							{
								// intervento //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_INTERVENTOC);
								tagElement.rectInMm = rectIntervento;
								listElements.AddTail(tagElement);
								rectIntervento.OffsetRect(0, lRowHeight);

								// data //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DATA);
								tagElement.rectInMm = rectData;
								listElements.AddTail(tagElement);
								rectData.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setTemp.IsEOF())
							{
								if (rectIntervento.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								// intervento //
								CString strTemp = setTemp.m_sIntervento;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectIntervento;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("intervento", tagElement.strFieldValue, parent);
								}
								rectIntervento.OffsetRect(0, lRowHeight);

								// data //
								strTemp = CCustomDate(setTemp.m_lClasse).GetDate("%d/%m/%Y");
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectData;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("data", tagElement.strFieldValue, parent);
								}
								rectData.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}

						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_interventiendoscopici:
			{
				//strTagName = "form_interventiendoscopici";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CInterventiEndoscopiciSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_interventiendoscopici", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectIntervento;
							rectIntervento.left = rectTot.left + ((rectTot.Width() * 0) / 10);
							rectIntervento.top = rectTot.top;
							rectIntervento.right = rectTot.left + ((rectTot.Width() * 7) / 10);
							rectIntervento.bottom = rectTot.top + lRowHeight;

							CRect rectData;
							rectData.left = rectTot.left + ((rectTot.Width() * 7) / 10);
							rectData.top = rectTot.top;
							rectData.right = rectTot.left + ((rectTot.Width() * 10) / 10);
							rectData.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectIntervento.bottom < rectTot.bottom)
							{
								// intervento //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_INTERVENTOE);
								tagElement.rectInMm = rectIntervento;
								listElements.AddTail(tagElement);
								rectIntervento.OffsetRect(0, lRowHeight);

								// data //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DATA);
								tagElement.rectInMm = rectData;
								listElements.AddTail(tagElement);
								rectData.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setTemp.IsEOF())
							{
								if (rectIntervento.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								// intervento //
								CString strTemp = setTemp.m_sIntervento;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectIntervento;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("intervento", tagElement.strFieldValue, parent);
								}
								rectIntervento.OffsetRect(0, lRowHeight);

								// data //
								strTemp = CCustomDate(setTemp.m_lClasse).GetDate("%d/%m/%Y");
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectData;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("data", tagElement.strFieldValue, parent);
								}
								rectData.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_istologia_fisso:
			{
				//strTagName = "form_istologia_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CIstologiaSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_istologia_fisso", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont) + 2;

							CRect rectTot = tagElement.rectInMm;

							CRect rectTipo;
							rectTipo.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectTipo.top = rectTot.top;
							rectTipo.right = rectTot.left + ((rectTot.Width() * 20) / 100);
							rectTipo.bottom = rectTot.top + lRowHeight;

							CRect rectOrgano;
							rectOrgano.left = rectTot.left + ((rectTot.Width() * 20) / 100);
							rectOrgano.top = rectTot.top;
							rectOrgano.right = rectTot.left + ((rectTot.Width() * 40) / 100);
							rectOrgano.bottom = rectTot.top + lRowHeight;

							CRect rectSede;
							rectSede.left = rectTot.left + ((rectTot.Width() * 40) / 100);
							rectSede.top = rectTot.top;
							rectSede.right = rectTot.left + ((rectTot.Width() * 60) / 100);
							rectSede.bottom = rectTot.top + lRowHeight;

							CRect rectProvette;
							rectProvette.left = rectTot.left + ((rectTot.Width() * 60) / 100);
							rectProvette.top = rectTot.top;
							rectProvette.right = rectTot.left + ((rectTot.Width() * 70) / 100);
							rectProvette.bottom = rectTot.top + lRowHeight;

							CRect rectDiagnosi;
							rectDiagnosi.left = rectTot.left + ((rectTot.Width() * 70) / 100);
							rectDiagnosi.top = rectTot.top;
							rectDiagnosi.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectDiagnosi.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectOrgano.bottom < rectTot.bottom)
							{
								// tipo //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_TIPO);
								tagElement.rectInMm = rectTipo;
								listElements.AddTail(tagElement);
								rectTipo.OffsetRect(0, lRowHeight);

								// organo //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_ORGANO);
								tagElement.rectInMm = rectOrgano;
								listElements.AddTail(tagElement);
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_SEDEANATOMICA);
								tagElement.rectInMm = rectSede;
								listElements.AddTail(tagElement);
								rectSede.OffsetRect(0, lRowHeight);

								// provette //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_PROVETTE);
								tagElement.rectInMm = rectProvette;
								listElements.AddTail(tagElement);
								rectProvette.OffsetRect(0, lRowHeight);

								// diagnosi //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DIAGNOSI);
								tagElement.rectInMm = rectDiagnosi;
								listElements.AddTail(tagElement);
								rectDiagnosi.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setTemp.IsEOF())
							{
								if (rectOrgano.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								// tipo //
								CString strTemp = CIstologiaTipiSet().GetDescrizione(setTemp.m_lTipo);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectTipo;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("tipo", tagElement.strFieldValue, parent);
								}
								rectTipo.OffsetRect(0, lRowHeight);

								// organo //
								strTemp = CMstOrganoSet().GetFieldText(setTemp.m_lOrgano);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectOrgano;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("organo", tagElement.strFieldValue, parent);
								}
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								strTemp = setTemp.m_sSede;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectSede;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("sede", tagElement.strFieldValue, parent);
								}
								rectSede.OffsetRect(0, lRowHeight);

								// provette //
								strTemp = setTemp.m_sProvette;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectProvette;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("provette", tagElement.strFieldValue, parent);
								}
								rectProvette.OffsetRect(0, lRowHeight);

								// diagnosi //
								strTemp = setTemp.m_sDiagnosi;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectDiagnosi;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("diagnosi", tagElement.strFieldValue, parent);
								}
								rectDiagnosi.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_istologia_fisso_plus:
			{
				//strTagName = "form_istologia_fisso_plus";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CIstologiaSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_istologia_fisso_plus", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont) + 2;

							CRect rectTot = tagElement.rectInMm;

							CRect rectTipo;
							rectTipo.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectTipo.top = rectTot.top;
							rectTipo.right = rectTot.left + ((rectTot.Width() * 15) / 100);
							rectTipo.bottom = rectTot.top + lRowHeight;

							CRect rectOrgano;
							rectOrgano.left = rectTot.left + ((rectTot.Width() * 15) / 100);
							rectOrgano.top = rectTot.top;
							rectOrgano.right = rectTot.left + ((rectTot.Width() * 30) / 100);
							rectOrgano.bottom = rectTot.top + lRowHeight;

							CRect rectSede;
							rectSede.left = rectTot.left + ((rectTot.Width() * 30) / 100);
							rectSede.top = rectTot.top;
							rectSede.right = rectTot.left + ((rectTot.Width() * 45) / 100);
							rectSede.bottom = rectTot.top + lRowHeight;

							CRect rectProvette;
							rectProvette.left = rectTot.left + ((rectTot.Width() * 45) / 100);
							rectProvette.top = rectTot.top;
							rectProvette.right = rectTot.left + ((rectTot.Width() * 50) / 100);
							rectProvette.bottom = rectTot.top + lRowHeight;

							CRect rectProcedura;
							rectProcedura.left = rectTot.left + ((rectTot.Width() * 50) / 100);
							rectProcedura.top = rectTot.top;
							rectProcedura.right = rectTot.left + ((rectTot.Width() * 70) / 100);
							rectProcedura.bottom = rectTot.top + lRowHeight;

							CRect rectDiagnosi;
							rectDiagnosi.left = rectTot.left + ((rectTot.Width() * 70) / 100);
							rectDiagnosi.top = rectTot.top;
							rectDiagnosi.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectDiagnosi.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectOrgano.bottom < rectTot.bottom)
							{
								// tipo //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_TIPO);
								tagElement.rectInMm = rectTipo;
								listElements.AddTail(tagElement);
								rectTipo.OffsetRect(0, lRowHeight);

								// organo //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_ORGANO);
								tagElement.rectInMm = rectOrgano;
								listElements.AddTail(tagElement);
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_SEDEANATOMICA);
								tagElement.rectInMm = rectSede;
								listElements.AddTail(tagElement);
								rectSede.OffsetRect(0, lRowHeight);

								// provette //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_PROVETTE);
								tagElement.rectInMm = rectProvette;
								listElements.AddTail(tagElement);
								rectProvette.OffsetRect(0, lRowHeight);

								// procedura //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_PROCEDURA);
								tagElement.rectInMm = rectProcedura;
								listElements.AddTail(tagElement);
								rectProcedura.OffsetRect(0, lRowHeight);

								// diagnosi //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DIAGNOSI);
								tagElement.rectInMm = rectDiagnosi;
								listElements.AddTail(tagElement);
								rectDiagnosi.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setTemp.IsEOF())
							{
								if (rectOrgano.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								// tipo //
								CString strTemp = CIstologiaTipiSet().GetDescrizione(setTemp.m_lTipo);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectTipo;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("tipo", tagElement.strFieldValue, parent);
								}
								rectTipo.OffsetRect(0, lRowHeight);

								// organo //
								strTemp = CMstOrganoSet().GetFieldText(setTemp.m_lOrgano);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectOrgano;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("organo", tagElement.strFieldValue, parent);
								}
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								strTemp = setTemp.m_sSede;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectSede;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("sede", tagElement.strFieldValue, parent);
								}
								rectSede.OffsetRect(0, lRowHeight);

								// provette //
								strTemp = setTemp.m_sProvette;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectProvette;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("provette", tagElement.strFieldValue, parent);
								}
								rectProvette.OffsetRect(0, lRowHeight);

								// procedura //
								strTemp = CIstologiaProcedureSet().GetDescrizione(setTemp.m_lProcedura);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectProcedura;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("procedura", tagElement.strFieldValue, parent);
								}
								rectProcedura.OffsetRect(0, lRowHeight);

								// diagnosi //
								strTemp = setTemp.m_sDiagnosi;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectDiagnosi;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("diagnosi", tagElement.strFieldValue, parent);
								}
								rectDiagnosi.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_istologia_grande:
			{
				//strTagName = "form_istologia_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CIstologiaSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_istologia_grande", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont) + 2;

							CRect rectTot = tagElement.rectInMm;

							CRect rectRiga;
							rectRiga.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectRiga.top = rectTot.top;
							rectRiga.right = rectTot.left + ((rectTot.Width() * 5) / 100);
							rectRiga.bottom = rectTot.top + lRowHeight;

							CRect rectTipo;
							rectTipo.left = rectTot.left + ((rectTot.Width() * 5) / 100);
							rectTipo.top = rectTot.top;
							rectTipo.right = rectTot.left + ((rectTot.Width() * 20) / 100);
							rectTipo.bottom = rectTot.top + lRowHeight;

							CRect rectOrgano;
							rectOrgano.left = rectTot.left + ((rectTot.Width() * 20) / 100);
							rectOrgano.top = rectTot.top;
							rectOrgano.right = rectTot.left + ((rectTot.Width() * 40) / 100);
							rectOrgano.bottom = rectTot.top + lRowHeight;

							CRect rectSede;
							rectSede.left = rectTot.left + ((rectTot.Width() * 40) / 100);
							rectSede.top = rectTot.top;
							rectSede.right = rectTot.left + ((rectTot.Width() * 60) / 100);
							rectSede.bottom = rectTot.top + lRowHeight;

							CRect rectProvette;
							rectProvette.left = rectTot.left + ((rectTot.Width() * 60) / 100);
							rectProvette.top = rectTot.top;
							rectProvette.right = rectTot.left + ((rectTot.Width() * 65) / 100);
							rectProvette.bottom = rectTot.top + lRowHeight;

							CRect rectDiagnosi;
							rectDiagnosi.left = rectTot.left + ((rectTot.Width() * 65) / 100);
							rectDiagnosi.top = rectTot.top;
							rectDiagnosi.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectDiagnosi.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							// riga //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_RIGA);
							tagElement.rectInMm = rectRiga;
							listElements.AddTail(tagElement);
							rectRiga.OffsetRect(0, lRowHeight);

							// tipo //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_TIPO);
							tagElement.rectInMm = rectTipo;
							listElements.AddTail(tagElement);
							rectTipo.OffsetRect(0, lRowHeight);

							// organo //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_ORGANO);
							tagElement.rectInMm = rectOrgano;
							listElements.AddTail(tagElement);
							rectOrgano.OffsetRect(0, lRowHeight);

							// sede //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_SEDEANATOMICA);
							tagElement.rectInMm = rectSede;
							listElements.AddTail(tagElement);
							rectSede.OffsetRect(0, lRowHeight);

							// provette //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_PROVETTE);
							tagElement.rectInMm = rectProvette;
							listElements.AddTail(tagElement);
							rectProvette.OffsetRect(0, lRowHeight);

							// diagnosi //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DIAGNOSI);
							tagElement.rectInMm = rectDiagnosi;
							listElements.AddTail(tagElement);
							rectDiagnosi.OffsetRect(0, lRowHeight);

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							int iRow = 1;
							while (!setTemp.IsEOF())
							{
								parent = AddElementToDocument("record", "", parent);

								// riga //
								CString strTemp = "";

								// Sandro 05/11/2013 // RAS 20130163 //
								if (theApp.m_bIstopatologiaMostraLettera)
								{
									long lTemp = iRow - 1;

									if (lTemp < 26)
										strTemp.Format("%c", 'A' + lTemp);
									else
										strTemp.Format("%c%c", 'A' + (lTemp / 26) - 1, 'A' + (lTemp % 26));
								}
								else
								{
									strTemp.Format("%d", iRow);
								}

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectRiga;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("riga", tagElement.strFieldValue, parent);
								}
								rectRiga.OffsetRect(0, lRowHeight);

								// tipo //
								strTemp = CIstologiaTipiSet().GetDescrizione(setTemp.m_lTipo);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectTipo;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("tipo", tagElement.strFieldValue, parent);
								}
								rectTipo.OffsetRect(0, lRowHeight);

								// organo //
								strTemp = CMstOrganoSet().GetFieldText(setTemp.m_lOrgano);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectOrgano;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("organo", tagElement.strFieldValue, parent);
								}
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								strTemp = setTemp.m_sSede;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectSede;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("sede", tagElement.strFieldValue, parent);
								}
								rectSede.OffsetRect(0, lRowHeight);

								// provette //
								strTemp = setTemp.m_sProvette;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectProvette;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("provette", tagElement.strFieldValue, parent);
								}
								rectProvette.OffsetRect(0, lRowHeight);

								// diagnosi //
								strTemp = setTemp.m_sDiagnosi;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectDiagnosi;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("diagnosi", tagElement.strFieldValue, parent);
								}
								rectDiagnosi.OffsetRect(0, lRowHeight);

								//
								iRow++;
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_istologia_grande_plus:
			{
				//strTagName = "form_istologia_grande_plus";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CIstologiaSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_istologia_grande_plus", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont) + 2;

							CRect rectTot = tagElement.rectInMm;

							CRect rectRiga;
							rectRiga.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectRiga.top = rectTot.top;
							rectRiga.right = rectTot.left + ((rectTot.Width() * 5) / 100);
							rectRiga.bottom = rectTot.top + lRowHeight;

							CRect rectTipo;
							rectTipo.left = rectTot.left + ((rectTot.Width() * 5) / 100);
							rectTipo.top = rectTot.top;
							rectTipo.right = rectTot.left + ((rectTot.Width() * 20) / 100);
							rectTipo.bottom = rectTot.top + lRowHeight;

							CRect rectOrgano;
							rectOrgano.left = rectTot.left + ((rectTot.Width() * 20) / 100);
							rectOrgano.top = rectTot.top;
							rectOrgano.right = rectTot.left + ((rectTot.Width() * 35) / 100);
							rectOrgano.bottom = rectTot.top + lRowHeight;

							CRect rectSede;
							rectSede.left = rectTot.left + ((rectTot.Width() * 35) / 100);
							rectSede.top = rectTot.top;
							rectSede.right = rectTot.left + ((rectTot.Width() * 50) / 100);
							rectSede.bottom = rectTot.top + lRowHeight;

							CRect rectProvette;
							rectProvette.left = rectTot.left + ((rectTot.Width() * 50) / 100);
							rectProvette.top = rectTot.top;
							rectProvette.right = rectTot.left + ((rectTot.Width() * 55) / 100);
							rectProvette.bottom = rectTot.top + lRowHeight;

							CRect rectProcedura;
							rectProcedura.left = rectTot.left + ((rectTot.Width() * 55) / 100);
							rectProcedura.top = rectTot.top;
							rectProcedura.right = rectTot.left + ((rectTot.Width() * 70) / 100);
							rectProcedura.bottom = rectTot.top + lRowHeight;

							CRect rectDiagnosi;
							rectDiagnosi.left = rectTot.left + ((rectTot.Width() * 70) / 100);
							rectDiagnosi.top = rectTot.top;
							rectDiagnosi.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectDiagnosi.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							// riga //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_RIGA);
							tagElement.rectInMm = rectRiga;
							listElements.AddTail(tagElement);
							rectRiga.OffsetRect(0, lRowHeight);

							// tipo //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_TIPO);
							tagElement.rectInMm = rectTipo;
							listElements.AddTail(tagElement);
							rectTipo.OffsetRect(0, lRowHeight);

							// organo //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_ORGANO);
							tagElement.rectInMm = rectOrgano;
							listElements.AddTail(tagElement);
							rectOrgano.OffsetRect(0, lRowHeight);

							// sede //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_SEDEANATOMICA);
							tagElement.rectInMm = rectSede;
							listElements.AddTail(tagElement);
							rectSede.OffsetRect(0, lRowHeight);

							// provette //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_PROVETTE);
							tagElement.rectInMm = rectProvette;
							listElements.AddTail(tagElement);
							rectProvette.OffsetRect(0, lRowHeight);

							// procedura //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_PROCEDURA);
							tagElement.rectInMm = rectProcedura;
							listElements.AddTail(tagElement);
							rectProcedura.OffsetRect(0, lRowHeight);

							// diagnosi //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DIAGNOSI);
							tagElement.rectInMm = rectDiagnosi;
							listElements.AddTail(tagElement);
							rectDiagnosi.OffsetRect(0, lRowHeight);

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							int iRow = 1;
							while (!setTemp.IsEOF())
							{
								parent = AddElementToDocument("form_istologia_grande_plus", "", parent);

								// riga //
								CString strTemp = "";

								// Sandro 05/11/2013 // RAS 20130163 //
								if (theApp.m_bIstopatologiaMostraLettera)
								{
									long lTemp = iRow - 1;

									if (lTemp < 26)
										strTemp.Format("%c", 'A' + lTemp);
									else
										strTemp.Format("%c%c", 'A' + (lTemp / 26) - 1, 'A' + (lTemp % 26));
								}
								else
								{
									strTemp.Format("%d", iRow);
								}

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectRiga;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("riga", tagElement.strFieldValue, parent);
								}
								rectRiga.OffsetRect(0, lRowHeight);

								// tipo //
								strTemp = CIstologiaTipiSet().GetDescrizione(setTemp.m_lTipo);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectTipo;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("tipo", tagElement.strFieldValue, parent);
								}
								rectTipo.OffsetRect(0, lRowHeight);

								// organo //
								strTemp = CMstOrganoSet().GetFieldText(setTemp.m_lOrgano);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectOrgano;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("organo", tagElement.strFieldValue, parent);
								}
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								strTemp = setTemp.m_sSede;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectSede;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("sede", tagElement.strFieldValue, parent);
								}
								rectSede.OffsetRect(0, lRowHeight);

								// provette //
								strTemp = setTemp.m_sProvette;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectProvette;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("provette", tagElement.strFieldValue, parent);
								}
								rectProvette.OffsetRect(0, lRowHeight);

								// procedura //
								strTemp = CIstologiaProcedureSet().GetDescrizione(setTemp.m_lProcedura);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectProcedura;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("procedura", tagElement.strFieldValue, parent);
								}
								rectProcedura.OffsetRect(0, lRowHeight);

								// diagnosi //
								strTemp = setTemp.m_sDiagnosi;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectDiagnosi;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("diagnosi", tagElement.strFieldValue, parent);
								}
								rectDiagnosi.OffsetRect(0, lRowHeight);

								//
								iRow++;
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_familiarita:
			{
				//strTagName = "form_familiarita";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Paziente=%li", m_pEsamiSet->m_lPaziente);

					CFamiliaritaSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_familiarita", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectFamiliarita;
							rectFamiliarita.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectFamiliarita.top = rectTot.top;
							rectFamiliarita.right = rectTot.left + ((rectTot.Width() * 60) / 100);
							rectFamiliarita.bottom = rectTot.top + lRowHeight;

							CRect rectParentela;
							rectParentela.left = rectTot.left + ((rectTot.Width() * 60) / 100);
							rectParentela.top = rectTot.top;
							rectParentela.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectParentela.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectFamiliarita.bottom < rectTot.bottom)
							{
								// familiarità //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_FAMILIARITA);
								tagElement.rectInMm = rectFamiliarita;
								listElements.AddTail(tagElement);
								rectFamiliarita.OffsetRect(0, lRowHeight);

								// parentela //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_PARENTELA);
								tagElement.rectInMm = rectParentela;
								listElements.AddTail(tagElement);
								rectParentela.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setTemp.IsEOF())
							{
								if (rectFamiliarita.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								// familiarità //
								CString strTemp = setTemp.m_sFamiliarita;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectFamiliarita;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("familiarita", tagElement.strFieldValue, parent);
								}
								rectFamiliarita.OffsetRect(0, lRowHeight);

								// parentela //
								strTemp = CComboBoxSet(CMB_PAZ_PARENTELA).GetFieldText(setTemp.m_lParentela);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectParentela;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("parentela", tagElement.strFieldValue, parent);
								}
								rectParentela.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_osservazioni_fisso:
			{
				//strTagName = "form_osservazioni_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					COsservazioniSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_osservazioni_fisso", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectOrgano;
							rectOrgano.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectOrgano.top = rectTot.top;
							rectOrgano.right = rectTot.left + ((rectTot.Width() * 15) / 100);
							rectOrgano.bottom = rectTot.top + lRowHeight;

							CRect rectSede;
							rectSede.left = rectTot.left + ((rectTot.Width() * 15) / 100);
							rectSede.top = rectTot.top;
							rectSede.right = rectTot.left + ((rectTot.Width() * 45) / 100);
							rectSede.bottom = rectTot.top + lRowHeight;

							CRect rectOsservazioni;
							rectOsservazioni.left = rectTot.left + ((rectTot.Width() * 45) / 100);
							rectOsservazioni.top = rectTot.top;
							rectOsservazioni.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectOsservazioni.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectOrgano.bottom < rectTot.bottom)
							{
								// organo //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_ORGANO);
								tagElement.rectInMm = rectOrgano;
								listElements.AddTail(tagElement);
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_SEDEANATOMICA);
								tagElement.rectInMm = rectSede;
								listElements.AddTail(tagElement);
								rectSede.OffsetRect(0, lRowHeight);

								// osservazioni //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_OSSERVAZIONI);
								tagElement.rectInMm = rectOsservazioni;
								listElements.AddTail(tagElement);
								rectOsservazioni.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setTemp.IsEOF())
							{
								if (rectOrgano.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("form_osservazioni_fisso", "", parent);

								// organo //
								CString strTemp = CMstOrganoSet().GetFieldText(setTemp.m_lOrgano);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectOrgano;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("organo", tagElement.strFieldValue, parent);
								}
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								strTemp = setTemp.m_sSede;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectSede;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("sede", tagElement.strFieldValue, parent);
								}
								rectSede.OffsetRect(0, lRowHeight);

								// osservazioni //
								strTemp = setTemp.m_sOsservazioni;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectOsservazioni;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("osservazioni", tagElement.strFieldValue, parent);
								}
								rectOsservazioni.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_osservazioni_grande:
			{
				//strTagName = "form_osservazioni_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					COsservazioniSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_osservazioni_grande", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectOrgano;
							rectOrgano.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectOrgano.top = rectTot.top;
							rectOrgano.right = rectTot.left + ((rectTot.Width() * 15) / 100);
							rectOrgano.bottom = rectTot.top + lRowHeight;

							CRect rectSede;
							rectSede.left = rectTot.left + ((rectTot.Width() * 15) / 100);
							rectSede.top = rectTot.top;
							rectSede.right = rectTot.left + ((rectTot.Width() * 45) / 100);
							rectSede.bottom = rectTot.top + lRowHeight;

							CRect rectOsservazioni;
							rectOsservazioni.left = rectTot.left + ((rectTot.Width() * 45) / 100);
							rectOsservazioni.top = rectTot.top;
							rectOsservazioni.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectOsservazioni.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							// organo //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_ORGANO);
							tagElement.rectInMm = rectOrgano;
							listElements.AddTail(tagElement);
							rectOrgano.OffsetRect(0, lRowHeight);

							// sede //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_SEDEANATOMICA);
							tagElement.rectInMm = rectSede;
							listElements.AddTail(tagElement);
							rectSede.OffsetRect(0, lRowHeight);

							// osservazioni //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_OSSERVAZIONI);
							tagElement.rectInMm = rectOsservazioni;
							listElements.AddTail(tagElement);
							rectOsservazioni.OffsetRect(0, lRowHeight);

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setTemp.IsEOF())
							{
								parent = AddElementToDocument("record", "", parent);

								// organo //
								CString strTemp = CMstOrganoSet().GetFieldText(setTemp.m_lOrgano);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectOrgano;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("organo", tagElement.strFieldValue, parent);
								}
								rectOrgano.OffsetRect(0, lRowHeight);

								// sede //
								strTemp = setTemp.m_sSede;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectSede;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("sede", tagElement.strFieldValue, parent);
								}
								rectSede.OffsetRect(0, lRowHeight);

								// osservazioni //
								strTemp = setTemp.m_sOsservazioni;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectOsservazioni;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("osservazioni", tagElement.strFieldValue, parent);
								}
								rectOsservazioni.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_malattieprecedenti:
			{
				//strTagName = "form_malattieprecedenti";			

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CMalattieSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_malattieprecedenti", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectMalattia;
							rectMalattia.left = rectTot.left + ((rectTot.Width() * 0) / 7);
							rectMalattia.top = rectTot.top;
							rectMalattia.right = rectTot.left + ((rectTot.Width() * 1) / 7);
							rectMalattia.bottom = rectTot.top + lRowHeight;

							CRect rectEpisodi;
							rectEpisodi.left = rectTot.left + ((rectTot.Width() * 1) / 7);
							rectEpisodi.top = rectTot.top;
							rectEpisodi.right = rectTot.left + ((rectTot.Width() * 3) / 7);
							rectEpisodi.bottom = rectTot.top + lRowHeight;

							CRect rectData;
							rectData.left = rectTot.left + ((rectTot.Width() * 3) / 7);
							rectData.top = rectTot.top;
							rectData.right = rectTot.left + ((rectTot.Width() * 7) / 7);
							rectData.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectMalattia.bottom < rectTot.bottom)
							{
								// malattia //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_MALATTIA);
								tagElement.rectInMm = rectMalattia;
								listElements.AddTail(tagElement);
								rectMalattia.OffsetRect(0, lRowHeight);

								// episodi //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_EPISODI);
								tagElement.rectInMm = rectEpisodi;
								listElements.AddTail(tagElement);
								rectEpisodi.OffsetRect(0, lRowHeight);

								// data //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DATA);
								tagElement.rectInMm = rectData;
								listElements.AddTail(tagElement);
								rectData.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setTemp.IsEOF())
							{
								if (rectMalattia.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								// malattia //
								CString strTemp = setTemp.m_sMalattia;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectMalattia;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("malattia", tagElement.strFieldValue, parent);
								}
								rectMalattia.OffsetRect(0, lRowHeight);

								// episodi //
								strTemp.Format("%li", setTemp.m_lEpisodi);

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectEpisodi;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("episodi", tagElement.strFieldValue, parent);
								}
								rectEpisodi.OffsetRect(0, lRowHeight);

								// data //
								strTemp = CCustomDate(setTemp.m_lClasse).GetDate("%d/%m/%Y");
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectData;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("data", tagElement.strFieldValue, parent);
								}
								rectData.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_monitoraggio_verticale:
			{
				//strTagName = "form_monitoraggio_verticale";

				CMonitoraggioBaseDynForm* pMon = (CMonitoraggioBaseDynForm*)m_pDynForm[sub_monitoraggio_vert];

				if (pMon != NULL)
				{
					if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
					{
	#define NUM_COLUMNS 10

						long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

						CRect rectTot = tagElement.rectInMm;

						CRect rectColumns[NUM_COLUMNS];

						for (int i = 0; i < NUM_COLUMNS; i++)
						{
							switch (i)
							{
							case 0:	//Fase 5%
							{
								long dimensione = (lRowHeight * 7); // (long)(((double)rectTot.Width() / 100) * 5);
								rectColumns[i].left = rectTot.left;
								rectColumns[i].top = rectTot.top;
								rectColumns[i].right = rectTot.left + dimensione;
								rectColumns[i].bottom = rectTot.top + lRowHeight;
								tagElement.strFieldValue = theApp.GetMessageString(IDS_FASE);
								tagElement.hAlignment = HPDF_TALIGN_LEFT;
								break;
							}
							case 1:	//Ora 5%
							{
								long dimensione = (lRowHeight * 5); // (long)(((double)rectTot.Width() / 100) * 5);
								rectColumns[i].left = rectColumns[i - 1].right;
								rectColumns[i].top = rectTot.top;
								rectColumns[i].right = rectColumns[i].left + dimensione;
								rectColumns[i].bottom = rectTot.top + lRowHeight;
								tagElement.strFieldValue = theApp.GetMessageString(IDS_ORE);
								tagElement.hAlignment = HPDF_TALIGN_LEFT;
								break;
							}
							case 2:	//Infermiere 10%
							{
								long dimensione = (lRowHeight * 7); // (long)(((double)rectTot.Width() / 100) * 10);
								rectColumns[i].left = rectColumns[i - 1].right;
								rectColumns[i].top = rectTot.top;
								rectColumns[i].right = rectColumns[i].left + dimensione;
								rectColumns[i].bottom = rectTot.top + lRowHeight;
								tagElement.strFieldValue = theApp.GetMessageString(IDS_INFERMIERE);
								tagElement.hAlignment = HPDF_TALIGN_LEFT;
								break;
							}
							case 3:	//FC 5%
							{
								long dimensione = (lRowHeight * 3); // (long)(((double)rectTot.Width() / 100) * 5);
								rectColumns[i].left = rectColumns[i - 1].right;
								rectColumns[i].top = rectTot.top;
								rectColumns[i].right = rectColumns[i].left + dimensione;
								rectColumns[i].bottom = rectTot.top + lRowHeight;
								tagElement.strFieldValue = theApp.GetMessageString(IDS_FC) + " ";
								tagElement.hAlignment = HPDF_TALIGN_CENTER;
								break;
							}
							case 4:	//PA 6%
							{
								long dimensione = (lRowHeight * 4); // (long)(((double)rectTot.Width() / 100) * 6);
								rectColumns[i].left = rectColumns[i - 1].right;
								rectColumns[i].top = rectTot.top;
								rectColumns[i].right = rectColumns[i].left + dimensione;
								rectColumns[i].bottom = rectTot.top + lRowHeight;
								tagElement.strFieldValue = theApp.GetMessageString(IDS_PA) + " ";
								tagElement.hAlignment = HPDF_TALIGN_CENTER;
								break;
							}
							case 5:	//SatO2 5%
							{
								long dimensione = (lRowHeight * 3); // (long)(((double)rectTot.Width() / 100) * 5);
								rectColumns[i].left = rectColumns[i - 1].right;
								rectColumns[i].top = rectTot.top;
								rectColumns[i].right = rectColumns[i].left + dimensione;
								rectColumns[i].bottom = rectTot.top + lRowHeight;
								tagElement.strFieldValue = theApp.GetMessageString(IDS_SAT) + " ";
								tagElement.hAlignment = HPDF_TALIGN_CENTER;
								break;
							}
							case 6:	//O2 5%
							{
								long dimensione = (lRowHeight * 3); // (long)(((double)rectTot.Width() / 100) * 5);
								rectColumns[i].left = rectColumns[i - 1].right;
								rectColumns[i].top = rectTot.top;
								rectColumns[i].right = rectColumns[i].left + dimensione;
								rectColumns[i].bottom = rectTot.top + lRowHeight;
								tagElement.strFieldValue = theApp.GetMessageString(IDS_O2) + " ";
								tagElement.hAlignment = HPDF_TALIGN_CENTER;
								break;
							}
							case 7:	//Dolore 5%
							{
								long dimensione = (lRowHeight * 3); // (long)(((double)rectTot.Width() / 100) * 5);
								rectColumns[i].left = rectColumns[i - 1].right;
								rectColumns[i].top = rectTot.top;
								rectColumns[i].right = rectColumns[i].left + dimensione;
								rectColumns[i].bottom = rectTot.top + lRowHeight;
								tagElement.strFieldValue = theApp.GetMessageString(IDS_DOLORE) + " ";
								tagElement.hAlignment = HPDF_TALIGN_CENTER;
								break;
							}
							case 8:	//Score 5%
							{
								long dimensione = (lRowHeight * 3); // (long)(((double)rectTot.Width() / 100) * 5);
								rectColumns[i].left = rectColumns[i - 1].right;
								rectColumns[i].top = rectTot.top;
								rectColumns[i].right = rectColumns[i].left + dimensione;
								rectColumns[i].bottom = rectTot.top + lRowHeight;
								tagElement.strFieldValue = theApp.GetMessageString(IDS_CHERNIK) + " ";
								tagElement.hAlignment = HPDF_TALIGN_CENTER;
								break;
							}
							case 9:	//Farmaci 49%
							{
								//long dimensione = rectTot.Width() - 170; // (long)(((double)rectTot.Width() / 100) * 49);
								rectColumns[i].left = rectColumns[i - 1].right;
								rectColumns[i].top = rectTot.top;
								rectColumns[i].right = rectTot.right;
								rectColumns[i].bottom = rectTot.top + lRowHeight;
								tagElement.strFieldValue = theApp.GetMessageString(IDS_FARMACI_E_DOSI);
								tagElement.hAlignment = HPDF_TALIGN_LEFT;
								break;
							}
							}

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							tagElement.rectInMm = rectColumns[i];
							tagElement.bPaintBorder = FALSE;
							listElements.AddTail(tagElement);
							rectColumns[i].OffsetRect(0, lRowHeight + 2);
							//rectColumns[i].bottom = rectColumns[i].bottom + lRowHeight;

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;
						}

						//

						for (int i = 1; i < pMon->GetListItemCount(); i++)
						{
							if (rectColumns[0].bottom > rectTot.bottom)
								break;

							for (int j = 0; j < NUM_COLUMNS; j++)
							{
								switch (j)
								{
								case 0:
								{
									tagElement.hAlignment = HPDF_TALIGN_LEFT;
									break;
								}
								case 1:
								{
									tagElement.hAlignment = HPDF_TALIGN_LEFT;
									break;
								}
								case 2:
								{
									tagElement.hAlignment = HPDF_TALIGN_LEFT;
									break;
								}
								case 3:
								{
									tagElement.hAlignment = HPDF_TALIGN_CENTER;
									break;
								}
								case 4:
								{
									tagElement.hAlignment = HPDF_TALIGN_CENTER;
									break;
								}
								case 5:
								{
									tagElement.hAlignment = HPDF_TALIGN_CENTER;
									break;
								}
								case 6:
								{
									tagElement.hAlignment = HPDF_TALIGN_CENTER;
									break;
								}
								case 7:
								{
									tagElement.hAlignment = HPDF_TALIGN_CENTER;
									break;
								}
								case 8:
								{
									tagElement.hAlignment = HPDF_TALIGN_CENTER;
									break;
								}
								case 9:
								{
									tagElement.hAlignment = HPDF_TALIGN_JUSTIFY;
									break;
								}
								}

								switch (j)
								{
								case 0:
								case 1:
								case 2:
								case 3:
								case 4:
								case 5:
								case 6:
								case 7:
								case 8:
								{
									CString strTemp = pMon->GetListItemText(j, i);
									strTemp.Trim();

									if (!strTemp.IsEmpty())
									{
										tagElement.strFieldValue = strTemp;
										tagElement.rectInMm = rectColumns[j];
										tagElement.bCanExpand = TRUE;
										tagElement.bPaintBorder = FALSE;
										listElements.AddTail(tagElement);
									}
									rectColumns[j].OffsetRect(0, lRowHeight);
									break;
								}
								case 9:	//Farmaci 30%
								{
									CString strTemp = pMon->GetFarmaciList(i);
									strTemp.Trim();

									if (!strTemp.IsEmpty())
									{
										tagElement.strFieldValue = strTemp;
										tagElement.rectInMm = rectColumns[j];
										tagElement.bCanExpand = TRUE;
										tagElement.bPaintBorder = FALSE;
										listElements.AddTail(tagElement);
									}
									rectColumns[j].OffsetRect(0, lRowHeight);
									break;
								}
								}
							}
						}

	#undef NUM_COLUMNS
					}
				}

				AddElementToDocument("form_monitoraggio_verticale", tagElement.strFieldValue);

				break;
			}
			case form_monitoraggio_verticale_new:
			{
				//strTagName = "form_monitoraggio_verticale_new";

				CMonitoraggioBaseDynForm* pMon = (CMonitoraggioBaseDynForm*)m_pDynForm[sub_monitoraggio_vert];

				if (pMon != NULL)
				{
					if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
					{
						long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

						CRect rectTot = tagElement.rectInMm;

						int numColumns = pMon->GetListNumCol();
						int numRows = pMon->GetListNumRig();
						int columnWidth = ((rectTot.Width() / 100) * 85) / numColumns;

						CRect* rectColumns = new CRect[numColumns];

						BOOL bItalic = tagElement.lfFont.lfItalic;
						long lfWeight = tagElement.lfFont.lfWeight;

						for (int r = 0; r < numRows; r++)
						{
							for (int c = 0; c < numColumns; c++)
							{
								if (c == 0)
								{
									tagElement.lfFont.lfItalic = TRUE;
									tagElement.lfFont.lfWeight = FW_BOLD;

									if (r == 0)
									{
										rectColumns[c].left = rectTot.left;
										rectColumns[c].top = rectTot.top;
										rectColumns[c].right = rectColumns[c].left + (rectTot.Width() / 100) * 15;
										rectColumns[c].bottom = rectColumns[c].top + lRowHeight;
									}
									else
									{
										rectColumns[c].left = rectTot.left;
										//rectColumns[c].top = rectColumns[c - 1].top;
										rectColumns[c].right = rectColumns[c].left + (rectTot.Width() / 100) * 15;
										rectColumns[c].bottom = rectColumns[c].top + lRowHeight;
									}

								}
								else
								{
									if (r == 0)
									{
										rectColumns[c].left = rectColumns[c - 1].right;
										rectColumns[c].top = rectTot.top;
										rectColumns[c].right = rectColumns[c].left + columnWidth;
										rectColumns[c].bottom = rectColumns[c].top + lRowHeight;
									}
									else
									{
										rectColumns[c].left = rectColumns[c - 1].right;
										//rectColumns[c].top = rectColumns[c - 1].top;
										rectColumns[c].right = rectColumns[c].left + columnWidth;
										rectColumns[c].bottom = rectColumns[c].top + lRowHeight;
									}
								}

								tagElement.strFieldValue = pMon->GetListItemText(r, c);
								tagElement.hAlignment = HPDF_TALIGN_LEFT;
								tagElement.bPaintBorder = FALSE;
								tagElement.rectInMm = rectColumns[c];
								tagElement.bCanExpand = TRUE;

								listElements.AddTail(tagElement);

								rectColumns[c].OffsetRect(0, lRowHeight + 2);

								tagElement.lfFont.lfItalic = bItalic;
								tagElement.lfFont.lfWeight = lfWeight;

							}
						}

						delete(rectColumns);

					}
				}

				AddElementToDocument("form_monitoraggio_verticale_new", tagElement.strFieldValue);

				break;
			}
			case form_monitoraggio_farmaci:
			{
				//strTagName = "form_monitoraggio_farmaci";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{

					CMonitoraggioBaseDynForm* pMon = (CMonitoraggioBaseDynForm*)m_pDynForm[sub_monitoraggio_vert];

					if (pMon != NULL)
					{
						tagElement.strFieldValue = pMon->GetTotaleFarmaciList();
						tagElement.strFieldValue.Trim();
					}
					else
					{
						tagElement.strFieldValue = CVistaMonitoraggioFarmaciSet().GetFarmaci(m_pEsamiSet->m_lContatore);
						tagElement.strFieldValue.Trim();
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}

				AddElementToDocument("form_monitoraggio_farmaci", tagElement.strFieldValue);

				break;
			}
			case form_monitoraggio_infermiere:
			{
				//strTagName = "form_monitoraggio_infermiere";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lInfermiereMonitoraggio) && (m_pEsamiSet->m_lInfermiereMonitoraggio > 0))
					{
						tagElement.strFieldValue = CInfermieriSet().GetFieldText(m_pEsamiSet->m_lInfermiereMonitoraggio);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("form_monitoraggio_infermiere", tagElement.strFieldValue);

				break;
			}
			case form_monitoraggio_note:
			{
				//strTagName = "form_monitoraggio_note";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sNoteMonitoraggio;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_monitoraggio_note", tagElement.strFieldValue);

				break;
			}
			case form_terapiainatto:
			{
				//strTagName = "form_terapiainatto";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CTerapieSet setTemp;
					setTemp.SetOpenFilter(strFilter);
					if (setTemp.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setTemp.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setTemp.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_terapiainatto", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectTerapia;
							rectTerapia.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectTerapia.top = rectTot.top;
							rectTerapia.right = rectTot.left + ((rectTot.Width() * 50) / 100);
							rectTerapia.bottom = rectTot.top + lRowHeight;

							CRect rectDurata;
							rectDurata.left = rectTot.left + ((rectTot.Width() * 50) / 100);
							rectDurata.top = rectTot.top;
							rectDurata.right = rectTot.left + ((rectTot.Width() * 75) / 100);
							rectDurata.bottom = rectTot.top + lRowHeight;

							CRect rectDose;
							rectDose.left = rectTot.left + ((rectTot.Width() * 75) / 100);
							rectDose.top = rectTot.top;
							rectDose.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectDose.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectTerapia.bottom < rectTot.bottom)
							{
								// terapia //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_TERAPIA);
								tagElement.rectInMm = rectTerapia;
								listElements.AddTail(tagElement);
								rectTerapia.OffsetRect(0, lRowHeight);

								// durata //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DURATA);
								tagElement.rectInMm = rectDurata;
								listElements.AddTail(tagElement);
								rectDurata.OffsetRect(0, lRowHeight);

								// dose //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DOSE);
								tagElement.rectInMm = rectDose;
								listElements.AddTail(tagElement);
								rectDose.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setTemp.IsEOF())
							{
								if (rectTerapia.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								// terapia //
								CString strTemp = setTemp.m_sTerapia;
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectTerapia;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("terapia", tagElement.strFieldValue, parent);
								}
								rectTerapia.OffsetRect(0, lRowHeight);

								// durata //
								strTemp = CComboBoxSet(CMB_ESA_TERAPIAINATTODURATA).GetFieldText(setTemp.m_lDurata);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectDurata;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("durata", tagElement.strFieldValue, parent);
								}
								rectDurata.OffsetRect(0, lRowHeight);

								// dose //
								strTemp = CComboBoxSet(CMB_ESA_TERAPIAINATTODOSAGG).GetFieldText(setTemp.m_lDose);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectDose;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("dose", tagElement.strFieldValue, parent);
								}
								rectDose.OffsetRect(0, lRowHeight);

								//
								setTemp.MoveNext();
							}
						}
						setTemp.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_codificaregionale_5righe:
			{
				//strTagName = "form_codificaregionale_5righe";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CRegioneSet setReg;
					setReg.SetOpenFilter(strFilter);
					if (setReg.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setReg.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setReg.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_codificaregionale_5righe", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectCodNaz;
							rectCodNaz.left = rectTot.left + ((rectTot.Width() * 0) / 8);
							rectCodNaz.top = rectTot.top;
							rectCodNaz.right = rectTot.left + ((rectTot.Width() * 1) / 8);
							rectCodNaz.bottom = rectTot.top + lRowHeight;

							CRect rectCodReg;
							rectCodReg.left = rectTot.left + ((rectTot.Width() * 1) / 8);
							rectCodReg.top = rectTot.top;
							rectCodReg.right = rectTot.left + ((rectTot.Width() * 2) / 8);
							rectCodReg.bottom = rectTot.top + lRowHeight;

							CRect rectDescrizione;
							rectDescrizione.left = rectTot.left + ((rectTot.Width() * 2) / 8);
							rectDescrizione.top = rectTot.top;
							rectDescrizione.right = rectTot.left + ((rectTot.Width() * 7) / 8);
							rectDescrizione.bottom = rectTot.top + lRowHeight;

							CRect rectQuantita;
							rectQuantita.left = rectTot.left + ((rectTot.Width() * 7) / 8);
							rectQuantita.top = rectTot.top;
							rectQuantita.right = rectTot.left + ((rectTot.Width() * 8) / 8);
							rectQuantita.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							// codice nazionale //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_CODREG);
							tagElement.rectInMm = rectCodNaz;
							listElements.AddTail(tagElement);
							rectCodNaz.OffsetRect(0, lRowHeight);

							// codice regionale //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_CODLOC);
							tagElement.rectInMm = rectCodReg;
							listElements.AddTail(tagElement);
							rectCodReg.OffsetRect(0, lRowHeight);

							// descrizione //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DESCRIZIONE);
							tagElement.rectInMm = rectDescrizione;
							listElements.AddTail(tagElement);
							rectDescrizione.OffsetRect(0, lRowHeight);

							// quantità //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_QUANTITA);
							tagElement.rectInMm = rectQuantita;
							listElements.AddTail(tagElement);
							rectQuantita.OffsetRect(0, lRowHeight);

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setReg.IsEOF())
							{
								parent = AddElementToDocument("record", "", parent);

								strFilter.Format("Contatore=%li", setReg.m_lCodice);

								CCodificaRegionaleExSet setTemp;
								setTemp.SetOpenFilter(strFilter);

								if (setTemp.OpenRecordset("CEsamiView::AddField"))
								{
									if (!setTemp.IsEOF())
									{
										// codice nazionale //
										CString strTemp = setTemp.m_sCodiceNazionale;
										strTemp.Trim();

										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectCodNaz;
											listElements.AddTail(tagElement);
											AddElementToDocument("codice_nazionale", tagElement.strFieldValue, parent);
										}
										rectCodNaz.OffsetRect(0, lRowHeight);

										// codice regionale //
										strTemp = setTemp.m_sCodiceRegionale;
										strTemp.Trim();

										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectCodReg;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("codice_regionale", tagElement.strFieldValue, parent);
										}
										rectCodReg.OffsetRect(0, lRowHeight);

										// descrizione //
										strTemp = setTemp.m_sDescrizione;
										strTemp.Trim();

										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectDescrizione;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("descrizione", tagElement.strFieldValue, parent);
										}
										rectDescrizione.OffsetRect(0, lRowHeight);

										// quantità //
										strTemp.Format("%li", setReg.m_lQuantita);

										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectQuantita;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("quantita", tagElement.strFieldValue, parent);
										}
										rectQuantita.OffsetRect(0, lRowHeight);
									}

									setTemp.CloseRecordset("CEsamiView::AddField");
								}

								//
								setReg.MoveNext();
							}
						}
						setReg.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_fluoroscopia:
			{
				//strTagName = "form_fluoroscopia";

				// Sandro 18/11/2014 // RAS 20140047 //

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lFluoroscopiaMinuti) && !m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lFluoroscopiaSecondi) && !m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fFluoroscopiaDose))
					{
						tagElement.strFieldValue.Format(theApp.GetMessageString(IDS_FLUOROSCOPIA_STAMPA), m_pEsamiSet->m_lFluoroscopiaMinuti, m_pEsamiSet->m_lFluoroscopiaSecondi, m_pEsamiSet->m_fFluoroscopiaDose);
						tagElement.strFieldValue.Trim();
					}
				}

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("form_fluoroscopia", tagElement.strFieldValue);

				break;
			}
			case form_accessori:
			{
				//strTagName = "form_accessori_5righe";

				break;
			}

			case subanatomia_campioni:
			{
				//strTagName = "subanatomia_campioni";

				if (m_pDynForm[sub_anatomiapatologica] != NULL)
				{
					CAnatomiaPatologicaForm* pForm = (CAnatomiaPatologicaForm*)m_pDynForm[sub_anatomiapatologica];
					if (pForm != NULL)
					{
						if (pForm->m_ctrlList.GetItemCount() > 0)
						{
							if (bOnlyIsValid)
								return TRUE;

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectIDCampione;
							rectIDCampione.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectIDCampione.top = rectTot.top;
							rectIDCampione.right = rectTot.left + ((rectTot.Width() * 20) / 100);
							rectIDCampione.bottom = rectTot.top + lRowHeight;

							CRect rectTipo;
							rectTipo.left = rectTot.left + ((rectTot.Width() * 20) / 100);
							rectTipo.top = rectTot.top;
							rectTipo.right = rectTot.left + ((rectTot.Width() * 30) / 100);
							rectTipo.bottom = rectTot.top + lRowHeight;

							CRect rectSede;
							rectSede.left = rectTot.left + ((rectTot.Width() * 30) / 100);
							rectSede.top = rectTot.top;
							rectSede.right = rectTot.left + ((rectTot.Width() * 60) / 100);
							rectSede.bottom = rectTot.top + lRowHeight;

							CRect rectPrelievi;
							rectPrelievi.left = rectTot.left + ((rectTot.Width() * 60) / 100);
							rectPrelievi.top = rectTot.top;
							rectPrelievi.right = rectTot.left + ((rectTot.Width() * 70) / 100);
							rectPrelievi.bottom = rectTot.top + lRowHeight;

							CRect rectCommento;
							rectCommento.left = rectTot.left + ((rectTot.Width() * 70) / 100);
							rectCommento.top = rectTot.top;
							rectCommento.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectCommento.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectIDCampione.bottom < rectTot.bottom)
							{
								// ID campione //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_ANATOMIAFORM_COL01);
								tagElement.rectInMm = rectIDCampione;
								listElements.AddTail(tagElement);
								rectIDCampione.OffsetRect(0, lRowHeight);

								// tipo //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_ANATOMIAFORM_COL02);
								tagElement.rectInMm = rectTipo;
								listElements.AddTail(tagElement);
								rectTipo.OffsetRect(0, lRowHeight);

								// sede anatomica //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_ANATOMIAFORM_COL04);
								tagElement.rectInMm = rectSede;
								listElements.AddTail(tagElement);
								rectSede.OffsetRect(0, lRowHeight);

								// numero prelievi //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_ANATOMIAFORM_COL05);
								tagElement.rectInMm = rectPrelievi;
								listElements.AddTail(tagElement);
								rectPrelievi.OffsetRect(0, lRowHeight);

								// commento //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_ANATOMIAFORM_COL06);
								tagElement.rectInMm = rectCommento;
								listElements.AddTail(tagElement);
								rectCommento.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							CList<reportElement*> *parent = AddElementToDocument("subanatomia_campioni", "");

							//

							for (int i = 0; i < pForm->m_ctrlList.GetItemCount(); i++)
							{
								if (rectIDCampione.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								// ID campione //
								CString strTemp = pForm->m_ctrlList.GetItemText(i, 2);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectIDCampione;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("id_campione", tagElement.strFieldValue, parent);
								}
								rectIDCampione.OffsetRect(0, lRowHeight);

								// tipo //
								strTemp = pForm->m_ctrlList.GetItemText(i, 3);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectTipo;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("tipo", tagElement.strFieldValue, parent);
								}
								rectTipo.OffsetRect(0, lRowHeight);

								// sede anatomica //
								strTemp = pForm->m_ctrlList.GetItemText(i, 4);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectSede;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("sede_anatomica", tagElement.strFieldValue, parent);
								}
								rectSede.OffsetRect(0, lRowHeight);

								// numero prelievi //
								strTemp = pForm->m_ctrlList.GetItemText(i, 5);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectPrelievi;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("numero_prelievi", tagElement.strFieldValue, parent);
								}
								rectPrelievi.OffsetRect(0, lRowHeight);

								// commento //
								strTemp = pForm->m_ctrlList.GetItemText(i, 6);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectCommento;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("commento", tagElement.strFieldValue, parent);
								}
								rectCommento.OffsetRect(0, lRowHeight);
							}
						}
					}
				}

				break;
			}
			case subanatomia_inviorichiesta:
			{
				//strTagName = "subanatomia_inviorichiesta";

				// non stampo niente, è solo per i campi obbligatori //
				AddElementToDocument("subanatomia_inviorichiesta", tagElement.strFieldValue);

				break;
			}
			case subanatomia_idcampione:
			{
				//strTagName = "subanatomia_idcampione";

				CAnatomiaPatologicaForm* pForm = (CAnatomiaPatologicaForm*)m_pDynForm[sub_anatomiapatologica];
				if (pForm != NULL)
				{
					tagElement.strFieldValue = pForm->GetField(2);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subanatomia_idcampione", tagElement.strFieldValue);

				break;
			}
			case subanatomia_tipo:
			{
				//strTagName = "subanatomia_tipo";

				CAnatomiaPatologicaForm* pForm = (CAnatomiaPatologicaForm*)m_pDynForm[sub_anatomiapatologica];
				if (pForm != NULL)
				{
					tagElement.strFieldValue = pForm->GetField(3);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subanatomia_tipo", tagElement.strFieldValue);

				break;
			}
			case subanatomia_intervento:
			{
				//strTagName = "subanatomia_intervento";

				CAnatomiaPatologicaForm* pForm = (CAnatomiaPatologicaForm*)m_pDynForm[sub_anatomiapatologica];
				if (pForm != NULL)
				{
					tagElement.strFieldValue = pForm->GetField(4);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subanatomia_intervento", tagElement.strFieldValue);

				break;
			}
			case subanatomia_nrcampione:
			{
				//strTagName = "subanatomia_nrcampione";

				CAnatomiaPatologicaForm* pForm = (CAnatomiaPatologicaForm*)m_pDynForm[sub_anatomiapatologica];
				if (pForm != NULL)
				{
					tagElement.strFieldValue = pForm->GetField(1);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subanatomia_nrcampione", tagElement.strFieldValue);

				break;
			}
			case subanatomia_notecampione:
			{
				//strTagName = "subanatomia_notecampione";

				CAnatomiaPatologicaForm* pForm = (CAnatomiaPatologicaForm*)m_pDynForm[sub_anatomiapatologica];
				if (pForm != NULL)
				{
					tagElement.strFieldValue = pForm->GetField(6);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subanatomia_notecampione", tagElement.strFieldValue);

				break;
			}
			case subanatomia_suggerimenti1_fisso:
			{
				//strTagName = "subanatomia_suggerimenti1_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sAPSuggerimenti1;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subanatomia_suggerimenti1_fisso", tagElement.strFieldValue);

				break;
			}
			case subanatomia_suggerimenti1_grande:
			{
				//strTagName = "subanatomia_suggerimenti1_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sAPSuggerimenti1;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subanatomia_suggerimenti1_grande", tagElement.strFieldValue);

				break;
			}
			case subanatomia_suggerimenti2:
			{
				//strTagName = "subanatomia_suggerimenti2";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sAPSuggerimenti2;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subanatomia_suggerimenti2", tagElement.strFieldValue);

				break;
			}
			case subanatomia_spedireritirare:
			{
				//strTagName = "subanatomia_spedireritirare";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_nAPSpedireRitirare) && (m_pEsamiSet->m_nAPSpedireRitirare >= 0) && (m_pEsamiSet->m_nAPSpedireRitirare < 3))
					{
						switch (m_pEsamiSet->m_nAPSpedireRitirare)
						{
						case 0:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_ANATOMIA_SPEDIRE);
							break;
						}
						case 1:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_ANATOMIA_SPEDIREALTRO);
							break;
						}
						case 2:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_ANATOMIA_RITIRO);
							break;
						}
						}
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("subanatomia_spedireritirare", tagElement.strFieldValue);

				break;
			}
			case subanatomia_indirizzoalternativo:
			{
				//strTagName = "subanatomia_indirizzoalternativo";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sAPIndirizzo;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subanatomia_indirizzoalternativo", tagElement.strFieldValue);

				break;
			}
			case subanatomia_note:
			{
				//strTagName = "subanatomia_note";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sAPDescrizioneRichiesta;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subanatomia_note", tagElement.strFieldValue);

				break;
			}

			case subistologia_riga:
			{
				//strTagName = "subistologia_riga";

				if (m_pDynForm[sub_istopatologia] != NULL)
				{
					CIstologiaTotForm* pForm = (CIstologiaTotForm*)m_pDynForm[sub_istopatologia];
					tagElement.strFieldValue = pForm->GetField(0);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				else if (m_pDynForm[sub_istopatologia5righe] != NULL)
				{
					CIstologiaTotForm5Righe* pForm = (CIstologiaTotForm5Righe*)m_pDynForm[sub_istopatologia5righe];
					tagElement.strFieldValue = pForm->GetField(0);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				else if (m_pDynForm[sub_istopatologia5righe_plus] != NULL)
				{
					CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pDynForm[sub_istopatologia5righe_plus];
					tagElement.strFieldValue = pForm->GetField(0);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subistologia_riga", tagElement.strFieldValue);

				break;
			}
			case subistologia_tipo:
			{
				//strTagName = "subistologia_tipo";

				if (m_pDynForm[sub_istopatologia] != NULL)
				{
					CIstologiaTotForm* pForm = (CIstologiaTotForm*)m_pDynForm[sub_istopatologia];
					tagElement.strFieldValue = pForm->GetField(1);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				else if (m_pDynForm[sub_istopatologia5righe] != NULL)
				{
					CIstologiaTotForm5Righe* pForm = (CIstologiaTotForm5Righe*)m_pDynForm[sub_istopatologia5righe];
					tagElement.strFieldValue = pForm->GetField(1);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				else if (m_pDynForm[sub_istopatologia5righe_plus] != NULL)
				{
					CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pDynForm[sub_istopatologia5righe_plus];
					tagElement.strFieldValue = pForm->GetField(1);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subistologia_tipo", tagElement.strFieldValue);

				break;
			}
			case subistologia_organo:
			{
				//strTagName = "subistologia_organo";

				if (m_pDynForm[sub_istopatologia] != NULL)
				{
					CIstologiaTotForm* pForm = (CIstologiaTotForm*)m_pDynForm[sub_istopatologia];
					tagElement.strFieldValue = pForm->GetField(2);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				else if (m_pDynForm[sub_istopatologia5righe] != NULL)
				{
					CIstologiaTotForm5Righe* pForm = (CIstologiaTotForm5Righe*)m_pDynForm[sub_istopatologia5righe];
					tagElement.strFieldValue = pForm->GetField(2);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				else if (m_pDynForm[sub_istopatologia5righe_plus] != NULL)
				{
					CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pDynForm[sub_istopatologia5righe_plus];
					tagElement.strFieldValue = pForm->GetField(2);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subistologia_organo", tagElement.strFieldValue);

				break;
			}
			case subistologia_sede:
			{
				//strTagName = "subistologia_sede";

				if (m_pDynForm[sub_istopatologia] != NULL)
				{
					CIstologiaTotForm* pForm = (CIstologiaTotForm*)m_pDynForm[sub_istopatologia];
					tagElement.strFieldValue = pForm->GetField(3);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				else if (m_pDynForm[sub_istopatologia5righe] != NULL)
				{
					CIstologiaTotForm5Righe* pForm = (CIstologiaTotForm5Righe*)m_pDynForm[sub_istopatologia5righe];
					tagElement.strFieldValue = pForm->GetField(3);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				else if (m_pDynForm[sub_istopatologia5righe_plus] != NULL)
				{
					CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pDynForm[sub_istopatologia5righe_plus];
					tagElement.strFieldValue = pForm->GetField(3);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subistologia_sede", tagElement.strFieldValue);

				break;
			}
			case subistologia_numero:
			{
				//strTagName = "subistologia_numero";

				if (m_pDynForm[sub_istopatologia] != NULL)
				{
					CIstologiaTotForm* pForm = (CIstologiaTotForm*)m_pDynForm[sub_istopatologia];
					tagElement.strFieldValue = pForm->GetField(4);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				else if (m_pDynForm[sub_istopatologia5righe] != NULL)
				{
					CIstologiaTotForm5Righe* pForm = (CIstologiaTotForm5Righe*)m_pDynForm[sub_istopatologia5righe];
					tagElement.strFieldValue = pForm->GetField(4);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				else if (m_pDynForm[sub_istopatologia5righe_plus] != NULL)
				{
					CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pDynForm[sub_istopatologia5righe_plus];
					tagElement.strFieldValue = pForm->GetField(4);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subistologia_numero", tagElement.strFieldValue);

				break;
			}
			case subistologia_procedura:
			{
				//strTagName = "subistologia_procedura";

				if (m_pDynForm[sub_istopatologia] != NULL)
				{
				}
				else if (m_pDynForm[sub_istopatologia5righe] != NULL)
				{
				}
				else if (m_pDynForm[sub_istopatologia5righe_plus] != NULL)
				{
					CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pDynForm[sub_istopatologia5righe_plus];
					tagElement.strFieldValue = pForm->GetField(5);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subistologia_procedura", tagElement.strFieldValue);

				break;
			}
			case subistologia_diagnosi:
			{
				//strTagName = "subistologia_diagnosi";

				if (m_pDynForm[sub_istopatologia] != NULL)
				{
					CIstologiaTotForm* pForm = (CIstologiaTotForm*)m_pDynForm[sub_istopatologia];
					tagElement.strFieldValue = pForm->GetField(5);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				else if (m_pDynForm[sub_istopatologia5righe] != NULL)
				{
					CIstologiaTotForm5Righe* pForm = (CIstologiaTotForm5Righe*)m_pDynForm[sub_istopatologia5righe];
					tagElement.strFieldValue = pForm->GetField(5);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				else if (m_pDynForm[sub_istopatologia5righe_plus] != NULL)
				{
					CIstologiaTotForm5RighePlus* pForm = (CIstologiaTotForm5RighePlus*)m_pDynForm[sub_istopatologia5righe_plus];
					tagElement.strFieldValue = pForm->GetField(6);
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("subistologia_diagnosi", tagElement.strFieldValue);

				break;
			}

			case form_allergie:
			{
				//strTagName = "form_allergie";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_iAllergie))
					{
						switch (m_pEsamiSet->m_iAllergie)
						{
						case 0:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_NO);
							break;
						}
						case 1:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_YES);

							m_pEsamiSet->m_sDescrizioneAllergie.Trim();
							if (!m_pEsamiSet->m_sDescrizioneAllergie.IsEmpty())
								tagElement.strFieldValue += ", " + m_pEsamiSet->m_sDescrizioneAllergie;

							break;
						}
						default:
						{
							// ASSERT(FALSE);

							tagElement.strFieldValue = "";
							break;
						}
						}

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("form_allergie", tagElement.strFieldValue);

				break;
			}
			case form_pacemaker:
			{
				//strTagName = "form_pacemaker";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (bOnlyIsValid)
						return TRUE;

					long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

					CRect rectTot = tagElement.rectInMm;

					CRect rectLeft;
					rectLeft.left = rectTot.left + ((rectTot.Width() * 0) / 100);
					rectLeft.top = rectTot.top;
					rectLeft.right = rectTot.left + ((rectTot.Width() * 80) / 100);
					rectLeft.bottom = rectTot.top + lRowHeight;

					CRect rectRight;
					rectRight.left = rectTot.left + ((rectTot.Width() * 80) / 100);
					rectRight.top = rectTot.top;
					rectRight.right = rectTot.left + ((rectTot.Width() * 100) / 100);
					rectRight.bottom = rectTot.top + lRowHeight;

					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_iPacemaker))
					{
						tagElement.strFieldValue = theApp.GetMessageString(IDS_PORTATOREPACEMAKER);
						tagElement.rectInMm = rectLeft;
						listElements.AddTail(tagElement);

						//

						switch (m_pEsamiSet->m_iPacemaker)
						{
						case 0:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_NO);
							break;
						}
						case 1:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_YES);
							break;
						}
						default:
						{
							// ASSERT(FALSE);

							tagElement.strFieldValue = "";
							break;
						}
						}
						tagElement.rectInMm = rectRight;
						listElements.AddTail(tagElement);

						//

						rectLeft.OffsetRect(0, lRowHeight);
						rectRight.OffsetRect(0, lRowHeight);
					}

					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_iAnticoagulanti))
					{
						tagElement.strFieldValue = theApp.GetMessageString(IDS_TERAPIAANTICOAGULANTE);
						tagElement.rectInMm = rectLeft;
						listElements.AddTail(tagElement);

						//

						switch (m_pEsamiSet->m_iAnticoagulanti)
						{
						case 0:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_NO);
							break;
						}
						case 1:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_YES);
							break;
						}
						default:
						{
							// ASSERT(FALSE);

							tagElement.strFieldValue = "";
							break;
						}
						}
						tagElement.rectInMm = rectRight;
						listElements.AddTail(tagElement);

						//

						rectLeft.OffsetRect(0, lRowHeight);
						rectRight.OffsetRect(0, lRowHeight);
					}

					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_iAntiaggreganti))
					{
						tagElement.strFieldValue = theApp.GetMessageString(IDS_TERAPIAANTIAGGREGANTE);
						tagElement.rectInMm = rectLeft;
						listElements.AddTail(tagElement);

						//

						switch (m_pEsamiSet->m_iAntiaggreganti)
						{
						case 0:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_NO);
							break;
						}
						case 1:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_SINGOLO);
							break;
						}
						case 2:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_DOPPIO);
							break;
						}
						default:
						{
							// ASSERT(FALSE);

							tagElement.strFieldValue = "";
							break;
						}
						}
						tagElement.rectInMm = rectRight;
						listElements.AddTail(tagElement);

						//

						rectLeft.OffsetRect(0, lRowHeight);
						rectRight.OffsetRect(0, lRowHeight);
					}
				}

				AddElementToDocument("form_pacemaker", tagElement.strFieldValue);

				break;
			}
			case form_portatorepacemaker:
			{
				//strTagName = "form_portatorepacemaker";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_iPacemaker))
					{
						switch (m_pEsamiSet->m_iPacemaker)
						{
						case 0:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_NO);
							break;
						}
						case 1:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_YES);

							m_pEsamiSet->m_sDescrizionePacemaker.Trim();
							if (!m_pEsamiSet->m_sDescrizionePacemaker.IsEmpty())
								tagElement.strFieldValue += ", " + m_pEsamiSet->m_sDescrizionePacemaker;

							break;
						}
						default:
						{
							// ASSERT(FALSE);

							tagElement.strFieldValue = "";
							break;
						}
						}

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("form_portatorepacemaker", tagElement.strFieldValue);

				break;
			}
			case form_anticoagulanti:
			{
				//strTagName = "form_anticoagulanti";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_iAnticoagulanti))
					{
						switch (m_pEsamiSet->m_iAnticoagulanti)
						{
						case 0:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_NO);
							break;
						}
						case 1:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_YES);

							m_pEsamiSet->m_sDescrizioneAnticoagulanti.Trim();
							if (!m_pEsamiSet->m_sDescrizioneAnticoagulanti.IsEmpty())
								tagElement.strFieldValue += ", " + m_pEsamiSet->m_sDescrizioneAnticoagulanti;

							break;
						}
						default:
						{
							// ASSERT(FALSE);

							tagElement.strFieldValue = "";
							break;
						}
						}

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("form_anticoagulanti", tagElement.strFieldValue);

				break;
			}
			case form_antiaggreganti:
			{
				//strTagName = "form_antiaggreganti";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_iAntiaggreganti))
					{
						switch (m_pEsamiSet->m_iAntiaggreganti)
						{
						case 0:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_NO);
							break;
						}
						case 1:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_SINGOLO);

							m_pEsamiSet->m_sDescrizioneAntiaggreganti.Trim();
							if (!m_pEsamiSet->m_sDescrizioneAntiaggreganti.IsEmpty())
								tagElement.strFieldValue += ", " + m_pEsamiSet->m_sDescrizioneAntiaggreganti;

							break;
						}
						case 2:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_DOPPIO);

							m_pEsamiSet->m_sDescrizioneAntiaggreganti.Trim();
							if (!m_pEsamiSet->m_sDescrizioneAntiaggreganti.IsEmpty())
								tagElement.strFieldValue += ", " + m_pEsamiSet->m_sDescrizioneAntiaggreganti;

							break;
						}
						default:
						{
							// ASSERT(FALSE);

							tagElement.strFieldValue = "";
							break;
						}
						}

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("form_antiaggreganti", tagElement.strFieldValue);

				break;
			}

			case form_anatomiapatologicatasti:
			{
				//strTagName = "form_anatomiapatologicatasti";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sAPIndirizzo;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_anatomiapatologicatasti", tagElement.strFieldValue);

				break;
			}

			case form_rao:
			{
				//strTagName = "form_rao";

				// non stampo niente, è solo per i campi obbligatori //
				AddElementToDocument("form_rao", tagElement.strFieldValue);

				break;
			}
			case form_consensoinformato:
			{
				//strTagName = "form_consensoinformato";

				// non stampo niente, è solo per i campi obbligatori //
				AddElementToDocument("form_consensoinformato", tagElement.strFieldValue);

				break;
			}

			case preliminari_inviante_i:
			{
				//strTagName = "preliminari_inviante_i";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					switch (m_pEsamiSet->m_lProvenienza)
					{
					case INTERNO:
					{
						tagElement.strFieldValue = CInviantiSet("EInviantiInterni").GetFieldText(m_pEsamiSet->m_lInviante);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
						break;
					}
					case ESTERNO:
					{
						tagElement.strFieldValue = CInviantiSet("EInviantiEsterni").GetFieldText(m_pEsamiSet->m_lInviante);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
						break;
					}
					}
				}
				AddElementToDocument("preliminari_inviante_i", tagElement.strFieldValue);

				break;
			}
			case preliminari_inviante_e:
			{
				//strTagName = "preliminari_inviante_e";
				long lArrayCount;
				CString sListaMedico;
				m_pEsamiSet->GetMediciRichiedente(sListaMedico, lArrayCount);
				
				if (theApp.m_bSelezionaMedicoRichiedente && lArrayCount > 1)
				{
					CString sMedicoSolicitante;
					
					if (!sListaMedico.IsEmpty())
						sListaMedico = sListaMedico.Mid(0, sListaMedico.GetLength() - 1);
					
					long lArrayPos = 0;
					CString *sArray = new CString[lArrayCount];

					int pos = 0;
					CString resToken;

					resToken = sListaMedico.Tokenize("|", pos);
					sArray[lArrayPos] = resToken;
					lArrayPos++;

					while (resToken != _T(""))
					{
						resToken = sListaMedico.Tokenize("|", pos);
						if (resToken != _T(""))
						{
							sArray[lArrayPos] = resToken;
							lArrayPos++;
						}
					}
						
					CSelectMedicoSolicitanteDlg selectDlg(this, sArray, lArrayCount);
					if (selectDlg.DoModal() == IDOK)
						sMedicoSolicitante = selectDlg.m_sSelectedMedico;

					tagElement.strFieldValue = sMedicoSolicitante;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
						
					sArray = NULL;
					delete(sArray);
				}

				else if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sInvMedico;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("preliminari_inviante_e", tagElement.strFieldValue);

				break;
			}

			case form_sedeprevista:
			{
				//strTagName = "form_sedeprevista";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sSedePrevista;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_sedeprevista", tagElement.strFieldValue);

				break;
			}
			case form_sederaggiunta:
			{
				//strTagName = "form_sederaggiunta";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sSedeRaggiunta;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_sederaggiunta", tagElement.strFieldValue);

				break;
			}

			case screening_complicanzeimmediate:
			{
				//strTagName = "screening_complicanzeimmediate";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lIDComplicanzeImmediate) && (m_pEsamiSet->m_lIDComplicanzeImmediate > 0))
					{
						tagElement.strFieldValue = CComboComplicanzeSet(FALSE).GetDescrizione(m_pEsamiSet->m_lIDComplicanzeImmediate);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("screening_complicanzeimmediate", tagElement.strFieldValue);

				break;
			}
			case screening_complicanzetardive:
			{
				//strTagName = "screening_complicanzetardive";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lIDComplicanzeTardive) && (m_pEsamiSet->m_lIDComplicanzeTardive > 0))
					{
						tagElement.strFieldValue = CComboComplicanzeSet(TRUE).GetDescrizione(m_pEsamiSet->m_lIDComplicanzeTardive);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("screening_complicanzetardive", tagElement.strFieldValue);

				break;
			}
			case screening_pulizia:
			{
				//strTagName = "screening_pulizia";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lIDPulizia) && (m_pEsamiSet->m_lIDPulizia > 0))
					{
						tagElement.strFieldValue = CComboPuliziaSet().GetDescrizione(m_pEsamiSet->m_lIDPulizia);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("screening_pulizia", tagElement.strFieldValue);

				break;
			}
			case screening_causenoncompletamento:
			{
				//strTagName = "screening_causenoncompletamento";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lIDCausaNonCompleto) && (m_pEsamiSet->m_lIDCausaNonCompleto > 0))
					{
						tagElement.strFieldValue = CComboCauseNonCompletamentoSet().GetDescrizione(m_pEsamiSet->m_lIDCausaNonCompleto);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("screening_causenoncompletamento", tagElement.strFieldValue);

				break;
			}
			case screening_tolleranza:
			{
				//strTagName = "screening_tolleranza";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lIDTolleranza) && (m_pEsamiSet->m_lIDTolleranza > 0))
					{
						tagElement.strFieldValue = CComboTolleranzaSet().GetDescrizione(m_pEsamiSet->m_lIDTolleranza);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("screening_tolleranza", tagElement.strFieldValue);

				break;
			}
			case screening_conclusioniscreening:
			{
				//strTagName = "screening_conclusioniscreening";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lIDConclusioniScreening) && (m_pEsamiSet->m_lIDConclusioniScreening > 0))
					{
						tagElement.strFieldValue = CComboConclusioniScreeningSet().GetDescrizione(m_pEsamiSet->m_lIDConclusioniScreening);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("screening_conclusioniscreening", tagElement.strFieldValue);

				break;
			}
			case screening_conclusionicolon:
			{
				//strTagName = "screening_conclusionicolon";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lIDConclusioniColon) && (m_pEsamiSet->m_lIDConclusioniColon > 0))
					{
						tagElement.strFieldValue = CComboConclusioniColonSet().GetDescrizione(m_pEsamiSet->m_lIDConclusioniColon);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("screening_conclusionicolon", tagElement.strFieldValue);

				break;
			}
			case screening_diagnosifinale:
			{
				//strTagName = "screening_diagnosifinale";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lIDDiagnosiFinale) && (m_pEsamiSet->m_lIDDiagnosiFinale > 0))
					{
						tagElement.strFieldValue = CComboDiagnosiFinaleSet().GetDescrizione(m_pEsamiSet->m_lIDDiagnosiFinale);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("screening_diagnosifinale", tagElement.strFieldValue);

				break;
			}
			case screening_altreanomalie:
			{
				//strTagName = "screening_altreanomalie";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lIDAltreAnomalie) && (m_pEsamiSet->m_lIDAltreAnomalie > 0))
					{
						tagElement.strFieldValue = CComboAltreAnomalieSet().GetDescrizione(m_pEsamiSet->m_lIDAltreAnomalie);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("screening_altreanomalie", tagElement.strFieldValue);

				break;
			}

			case preliminari_premedposologia:
			{
				//strTagName = "preliminari_premedposologia";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sPremedicazioni;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("preliminari_premedposologia", tagElement.strFieldValue);

				break;
			}

			case esame_mst_complicanze1_fisso:
			{
				//strTagName = "esame_mst_complicanze1_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sMstComplicanze1;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("esame_mst_complicanze1_fisso", tagElement.strFieldValue);

				break;
			}
			case esame_mst_complicanze1_grande:
			{
				//strTagName = "esame_mst_complicanze1_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sMstComplicanze1;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("esame_mst_complicanze1_grande", tagElement.strFieldValue);

				break;
			}
			case esame_mst_complicanze2_fisso:
			{
				//strTagName = "esame_mst_complicanze2_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sMstComplicanze2;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("esame_mst_complicanze2_fisso", tagElement.strFieldValue);

				break;
			}
			case esame_mst_complicanze2_grande:
			{
				//strTagName = "esame_mst_complicanze2_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sMstComplicanze2;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("esame_mst_complicanze2_grande", tagElement.strFieldValue);

				break;
			}
			case esame_mst_complicanze3_fisso:
			{
				//strTagName = "esame_mst_complicanze3_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sMstComplicanze3;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("esame_mst_complicanze3_fisso", tagElement.strFieldValue);

				break;
			}
			case esame_mst_complicanze3_grande:
			{
				//strTagName = "esame_mst_complicanze3_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sMstComplicanze3;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("esame_mst_complicanze3_grande", tagElement.strFieldValue);

				break;
			}

			case form_breathtest_hp_risultato:
			{
				//strTagName = "form_breathtest_hp_risultato";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = theApp.GetMessageString(IDS_DUBBIO);
					if (m_pEsamiSet->m_iBreathTestHP == 0)
					{
						if ((m_pEsamiSet->m_fBreathTestHPDiff >= 0.0f) && (m_pEsamiSet->m_fBreathTestHPDiff < theApp.m_fSogliaBreathTestHP))
							tagElement.strFieldValue = theApp.GetMessageString(IDS_NEGATIVO);
						else if (m_pEsamiSet->m_fBreathTestHPDiff >= theApp.m_fSogliaBreathTestHP)
							tagElement.strFieldValue = theApp.GetMessageString(IDS_POSITIVO);
					}
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_breathtest_hp_risultato", tagElement.strFieldValue);

				break;
			}
			case form_breathtest_hp_valore1:
			{
				//strTagName = "form_breathtest_hp_valore1";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = "-";
					if (m_pEsamiSet->m_iBreathTestHP == 0)
					{
						if (m_pEsamiSet->m_fBreathTestHPVal1 > -99.0f)
							tagElement.strFieldValue.Format("%.1f", m_pEsamiSet->m_fBreathTestHPVal1);
					}
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_breathtest_hp_valore1", tagElement.strFieldValue);

				break;
			}
			case form_breathtest_hp_valore2:
			{
				//strTagName = "form_breathtest_hp_valore2";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = "-";
					if (m_pEsamiSet->m_iBreathTestHP == 0)
					{
						if (m_pEsamiSet->m_fBreathTestHPVal2 > -99.0f)
							tagElement.strFieldValue.Format("%.1f", m_pEsamiSet->m_fBreathTestHPVal2);
					}
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_breathtest_hp_valore2", tagElement.strFieldValue);

				break;
			}
			case form_breathtest_hp_differenza:
			{
				//strTagName = "form_breathtest_hp_differenza";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = "-";
					if (m_pEsamiSet->m_iBreathTestHP == 0)
					{
						if (m_pEsamiSet->m_fBreathTestHPDiff >= 0.0f)
							tagElement.strFieldValue.Format("%.1f", m_pEsamiSet->m_fBreathTestHPDiff);
					}
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_breathtest_hp_differenza", tagElement.strFieldValue);

				break;
			}

			case form_sospensione_si_no:
			{
				//strTagName = "form_sospensione_si_no";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					switch (m_pEsamiSet->m_iSospeso)
					{
					case 0:
					{
						tagElement.strFieldValue = theApp.GetMessageString(IDS_NO);
						break;
					}
					case 1:
					{
						tagElement.strFieldValue = theApp.GetMessageString(IDS_YES);
						break;
					}
					default:
					{
						tagElement.strFieldValue = "";
						break;
					}
					}
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_sospensione_si_no", tagElement.strFieldValue);

				break;
			}
			case form_sospensione_data:
			{
				//strTagName = "form_sospensione_data";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_lDataScadenzaSospensione).GetDate("%d/%m/%Y");
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_sospensione_data", tagElement.strFieldValue);

				break;
			}
			case form_sospensione_motivo:
			{
				//strTagName = "form_sospensione_motivo";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sMotivoSospensione;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("form_sospensione_motivo", tagElement.strFieldValue);

				break;
			}

			case form_procedure_icd9:
			{
				//strTagName = "form_procedure_icd9";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("IDEsame=%li", m_pEsamiSet->m_lContatore);

					CProcedureEsamiSet setProcedure;
					setProcedure.SetOpenFilter(strFilter);
					if (setProcedure.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setProcedure.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setProcedure.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_procedure_icd9", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectCodInt;
							rectCodInt.left = rectTot.left + ((rectTot.Width() * 0) / 8);
							rectCodInt.top = rectTot.top;
							rectCodInt.right = rectTot.left + ((rectTot.Width() * 1) / 8);
							rectCodInt.bottom = rectTot.top + lRowHeight;

							CRect rectCodICD9;
							rectCodICD9.left = rectTot.left + ((rectTot.Width() * 1) / 8);
							rectCodICD9.top = rectTot.top;
							rectCodICD9.right = rectTot.left + ((rectTot.Width() * 2) / 8);
							rectCodICD9.bottom = rectTot.top + lRowHeight;

							CRect rectDescrizione;
							rectDescrizione.left = rectTot.left + ((rectTot.Width() * 2) / 8);
							rectDescrizione.top = rectTot.top;
							rectDescrizione.right = rectTot.left + ((rectTot.Width() * 7) / 8);
							rectDescrizione.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							// codifica interna //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_CODIFICAINTERNA);
							tagElement.rectInMm = rectCodInt;
							listElements.AddTail(tagElement);
							rectCodInt.OffsetRect(0, lRowHeight);

							// codifica ICD9 //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_CODIFICAICD9);
							tagElement.rectInMm = rectCodICD9;
							listElements.AddTail(tagElement);
							rectCodICD9.OffsetRect(0, lRowHeight);

							// descrizione //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DESCRIZIONE);
							tagElement.rectInMm = rectDescrizione;
							listElements.AddTail(tagElement);
							rectDescrizione.OffsetRect(0, lRowHeight);

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setProcedure.IsEOF())
							{
								parent = AddElementToDocument("record", "", parent);

								strFilter.Format("ID=%li", setProcedure.m_lIDProcedura);

								CProcedureICD9Set setTemp;
								setTemp.SetOpenFilter(strFilter);

								if (setTemp.OpenRecordset("CEsamiView::AddField"))
								{
									if (!setTemp.IsEOF())
									{
										// codice nazionale //
										CString strTemp = setTemp.m_sCodificaInterna;
										strTemp.Trim();

										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectCodInt;
											listElements.AddTail(tagElement);
											AddElementToDocument("codice_nazionale", tagElement.strFieldValue, parent);
										}
										rectCodInt.OffsetRect(0, lRowHeight);

										// codifica regionale //
										strTemp = "";
										if (m_pEsamiSet->m_lProvenienza == ESTERNO)
											strTemp = setTemp.m_sCodificaICD9Esterni;
										else
											strTemp = setTemp.m_sCodificaICD9Interni;
										strTemp.Trim();

										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectCodICD9;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("codice_regionale", tagElement.strFieldValue, parent);
										}
										rectCodICD9.OffsetRect(0, lRowHeight);

										// descrizione //
										strTemp = setTemp.m_sDescrizione;
										strTemp.Trim();

										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectDescrizione;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("descrizione", tagElement.strFieldValue, parent);
										}
										rectDescrizione.OffsetRect(0, lRowHeight);
									}

									setTemp.CloseRecordset("CEsamiView::AddField");
								}

								//
								setProcedure.MoveNext();
							}
						}
						setProcedure.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_diagnosi_icd9:
			{
				//strTagName = "form_diagnosi_icd9";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("IDEsame=%li", m_pEsamiSet->m_lContatore);

					CDiagnosiEsamiSet set;
					set.SetOpenFilter(strFilter);
					if (set.OpenRecordset("CEsamiView::AddField"))
					{
						if (!set.IsEOF())
						{
							if (bOnlyIsValid)
							{
								set.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_diagnosi_icd9", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectCodInt;
							rectCodInt.left = rectTot.left + ((rectTot.Width() * 0) / 8);
							rectCodInt.top = rectTot.top;
							rectCodInt.right = rectTot.left + ((rectTot.Width() * 1) / 8);
							rectCodInt.bottom = rectTot.top + lRowHeight;

							CRect rectCodICD9;
							rectCodICD9.left = rectTot.left + ((rectTot.Width() * 1) / 8);
							rectCodICD9.top = rectTot.top;
							rectCodICD9.right = rectTot.left + ((rectTot.Width() * 2) / 8);
							rectCodICD9.bottom = rectTot.top + lRowHeight;

							CRect rectDescrizione;
							rectDescrizione.left = rectTot.left + ((rectTot.Width() * 2) / 8);
							rectDescrizione.top = rectTot.top;
							rectDescrizione.right = rectTot.left + ((rectTot.Width() * 8) / 8);
							rectDescrizione.bottom = rectTot.top + lRowHeight;

							/*CRect rectQuantita;
							rectQuantita.left = rectTot.left + ((rectTot.Width() * 7) / 8);
							rectQuantita.top = rectTot.top;
							rectQuantita.right = rectTot.left + ((rectTot.Width() * 8) / 8);
							rectQuantita.bottom = rectTot.top + lRowHeight;*/

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							// codifica interna //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_CODIFICAINTERNA);
							tagElement.rectInMm = rectCodInt;
							listElements.AddTail(tagElement);
							rectCodInt.OffsetRect(0, lRowHeight);

							// codifica ICD9 //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_CODIFICAICD9);
							tagElement.rectInMm = rectCodICD9;
							listElements.AddTail(tagElement);
							rectCodICD9.OffsetRect(0, lRowHeight);

							// descrizione //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DESCRIZIONE);
							tagElement.rectInMm = rectDescrizione;
							listElements.AddTail(tagElement);
							rectDescrizione.OffsetRect(0, lRowHeight);

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!set.IsEOF())
							{
								parent = AddElementToDocument("record", "", parent);

								strFilter.Format("ID=%li", set.m_lIDDiagnosi);

								CDiagnosiICD9Set setTemp;
								setTemp.SetOpenFilter(strFilter);

								if (setTemp.OpenRecordset("CEsamiView::AddField"))
								{
									if (!setTemp.IsEOF())
									{
										// codice nazionale //
										CString strTemp = setTemp.m_sCodificaInterna;
										strTemp.Trim();

										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectCodInt;
											listElements.AddTail(tagElement);
											AddElementToDocument("codice_nazionale", tagElement.strFieldValue, parent);
										}
										rectCodInt.OffsetRect(0, lRowHeight);

										// codice regionale //
										strTemp = "";
										if (m_pEsamiSet->m_lProvenienza == ESTERNO)
											strTemp = setTemp.m_sCodificaICD9Esterni;
										else
											strTemp = setTemp.m_sCodificaICD9Interni;
										strTemp.Trim();

										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectCodICD9;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("codice_regionale", tagElement.strFieldValue, parent);
										}
										rectCodICD9.OffsetRect(0, lRowHeight);

										// descrizione //
										strTemp = setTemp.m_sDescrizione;
										strTemp.Trim();

										if (!strTemp.IsEmpty())
										{
											tagElement.strFieldValue = strTemp;
											tagElement.rectInMm = rectDescrizione;
											tagElement.bCanExpand = TRUE;
											listElements.AddTail(tagElement);
											AddElementToDocument("descrizione", tagElement.strFieldValue, parent);
										}
										rectDescrizione.OffsetRect(0, lRowHeight);
									}

									setTemp.CloseRecordset("CEsamiView::AddField");
								}

								//
								set.MoveNext();
							}
						}
						set.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}

			case form_newaccessori_fisso:
			{
				//strTagName = "form_newaccessori_fisso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CEsamiAccessoriSet setEsamiAccessori;
					setEsamiAccessori.SetOpenFilter(strFilter);
					if (setEsamiAccessori.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setEsamiAccessori.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setEsamiAccessori.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_newaccessori_fisso", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectDescrizione;
							rectDescrizione.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectDescrizione.top = rectTot.top;
							rectDescrizione.right = rectTot.left + ((rectTot.Width() * 90) / 100);
							rectDescrizione.bottom = rectTot.top + lRowHeight;

							CRect rectQuantita;
							rectQuantita.left = rectTot.left + ((rectTot.Width() * 90) / 100);
							rectQuantita.top = rectTot.top;
							rectQuantita.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectQuantita.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							if (rectDescrizione.bottom < rectTot.bottom)
							{
								// descrizione //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DESCRIZIONE);
								tagElement.rectInMm = rectDescrizione;
								listElements.AddTail(tagElement);
								rectDescrizione.OffsetRect(0, lRowHeight);

								// quantità //
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_QUANTITA);
								tagElement.rectInMm = rectQuantita;
								listElements.AddTail(tagElement);
								rectQuantita.OffsetRect(0, lRowHeight);
							}

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setEsamiAccessori.IsEOF())
							{
								if (rectDescrizione.bottom > rectTot.bottom)
									break;

								parent = AddElementToDocument("record", "", parent);

								// descrizione //
								CString strTemp = CComboBoxSet(CMB_ESA_ACCESS).GetFieldText(setEsamiAccessori.m_lCodice);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectDescrizione;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("descrizione", tagElement.strFieldValue, parent);
								}
								rectDescrizione.OffsetRect(0, lRowHeight);

								// quantità //
								strTemp.Format("%li", setEsamiAccessori.m_lQuantita);

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectQuantita;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("quantita", tagElement.strFieldValue, parent);
								}
								rectQuantita.OffsetRect(0, lRowHeight);

								//
								setEsamiAccessori.MoveNext();
							}
						}
						setEsamiAccessori.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}
			case form_newaccessori_grande:
			{
				//strTagName = "form_newaccessori_grande";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					CString strFilter;
					strFilter.Format("Esame=%li", m_pEsamiSet->m_lContatore);

					CEsamiAccessoriSet setEsamiAccessori;
					setEsamiAccessori.SetOpenFilter(strFilter);
					if (setEsamiAccessori.OpenRecordset("CEsamiView::AddField"))
					{
						if (!setEsamiAccessori.IsEOF())
						{
							if (bOnlyIsValid)
							{
								setEsamiAccessori.CloseRecordset("CEsamiView::AddField");
								return TRUE;
							}

							CList<reportElement*> *parent = AddElementToDocument("form_newaccessori_grande", "");

							long lRowHeight = AmPdfCreator_TextHeight(&tagElement.lfFont);

							CRect rectTot = tagElement.rectInMm;

							CRect rectDescrizione;
							rectDescrizione.left = rectTot.left + ((rectTot.Width() * 0) / 100);
							rectDescrizione.top = rectTot.top;
							rectDescrizione.right = rectTot.left + ((rectTot.Width() * 90) / 100);
							rectDescrizione.bottom = rectTot.top + lRowHeight;

							CRect rectQuantita;
							rectQuantita.left = rectTot.left + ((rectTot.Width() * 90) / 100);
							rectQuantita.top = rectTot.top;
							rectQuantita.right = rectTot.left + ((rectTot.Width() * 100) / 100);
							rectQuantita.bottom = rectTot.top + lRowHeight;

							//

							BOOL bItalic = tagElement.lfFont.lfItalic;
							long lfWeight = tagElement.lfFont.lfWeight;

							tagElement.lfFont.lfItalic = TRUE;
							tagElement.lfFont.lfWeight = FW_BOLD;

							// descrizione //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_DESCRIZIONE);
							tagElement.rectInMm = rectDescrizione;
							listElements.AddTail(tagElement);
							rectDescrizione.OffsetRect(0, lRowHeight);

							// quantità //
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REPORTFORM_QUANTITA);
							tagElement.rectInMm = rectQuantita;
							listElements.AddTail(tagElement);
							rectQuantita.OffsetRect(0, lRowHeight);

							//

							tagElement.lfFont.lfItalic = bItalic;
							tagElement.lfFont.lfWeight = lfWeight;

							//


							while (!setEsamiAccessori.IsEOF())
							{
								parent = AddElementToDocument("record", "", parent);

								// descrizione //
								CString strTemp = CComboBoxSet(CMB_ESA_ACCESS).GetFieldText(setEsamiAccessori.m_lCodice);
								strTemp.Trim();

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectDescrizione;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("descrizione", tagElement.strFieldValue, parent);
								}
								rectDescrizione.OffsetRect(0, lRowHeight);

								// quantità //
								strTemp.Format("%li", setEsamiAccessori.m_lQuantita);

								if (!strTemp.IsEmpty())
								{
									tagElement.strFieldValue = strTemp;
									tagElement.rectInMm = rectQuantita;
									tagElement.bCanExpand = TRUE;
									listElements.AddTail(tagElement);
									AddElementToDocument("quantita", tagElement.strFieldValue, parent);
								}
								rectQuantita.OffsetRect(0, lRowHeight);

								//
								setEsamiAccessori.MoveNext();
							}
						}
						setEsamiAccessori.CloseRecordset("CEsamiView::AddField");
					}
				}

				break;
			}

			case esame_codesame:
			{
				//strTagName = "esame_codesame";

				//Gestione stampa codesame senza riferimento al tipo esame generato
				int nTokenPos = m_pEsamiSet->m_sCodEsame.Find("#");
				if (nTokenPos >= 0)
					tagElement.strFieldValue = m_pEsamiSet->m_sCodEsame.Left(nTokenPos);
				else
					tagElement.strFieldValue = m_pEsamiSet->m_sCodEsame;

				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("esame_codesame", tagElement.strFieldValue);

				break;
			}
			case esame_tempochiusura:
			{
				//strTagName = "esame_tempochiusura";

				if (m_sDataOraChiusura.IsEmpty() && (m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_sDataOraSuperLock) || m_pEsamiSet->m_sDataOraSuperLock.IsEmpty()))
				{
					tagElement.strFieldValue = theApp.GetMessageString(IDS_ESAMEINCORSO);
				}
				else
				{
					if (m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_sDataOraSuperLock) || m_pEsamiSet->m_sDataOraSuperLock.IsEmpty())
						m_pEsamiSet->m_sDataOraSuperLock = m_sDataOraChiusura;

					CCustomDate customStart = CCustomDate(m_pEsamiSet->m_lData);
					COleDateTime oledtStart = COleDateTime(customStart.GetYear(), customStart.GetMonth(), customStart.GetDay(), customStart.GetHour(), customStart.GetMinute(), 0);
					COleDateTime oledtStop = COleDateTime(atoi(m_pEsamiSet->m_sDataOraSuperLock.Left(4)), atoi(m_pEsamiSet->m_sDataOraSuperLock.Mid(4, 2)), atoi(m_pEsamiSet->m_sDataOraSuperLock.Mid(6, 2)), atoi(m_pEsamiSet->m_sDataOraSuperLock.Mid(8, 2)), atoi(m_pEsamiSet->m_sDataOraSuperLock.Mid(10, 2)), 0);
					COleDateTimeSpan timeDiff = oledtStop - oledtStart;

					tagElement.strFieldValue.Format("%li %s %li %s %li %s", timeDiff.GetDays(), theApp.GetMessageString(IDS_GIORNI), timeDiff.GetHours(), theApp.GetMessageString(IDS_ORE), timeDiff.GetMinutes(), theApp.GetMessageString(IDS_MINUTI));
				}

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("esame_tempochiusura", tagElement.strFieldValue);

				break;
			}
			case esame_tempoconvalida:
			{
				//strTagName = "esame_tempoconvalida";

				if (m_sDataOraConvalida.IsEmpty() && (m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_sDataOraLock) || m_pEsamiSet->m_sDataOraLock.IsEmpty()))
				{
					tagElement.strFieldValue = theApp.GetMessageString(IDS_ESAMEINCORSO);
				}
				else
				{
					if (m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_sDataOraLock) || m_pEsamiSet->m_sDataOraLock.IsEmpty())
						m_pEsamiSet->m_sDataOraLock = m_sDataOraConvalida;

					CCustomDate customStart = CCustomDate(m_pEsamiSet->m_lData);
					COleDateTime oledtStart = COleDateTime(customStart.GetYear(), customStart.GetMonth(), customStart.GetDay(), customStart.GetHour(), customStart.GetMinute(), 0);
					COleDateTime oledtStop = COleDateTime(atoi(m_pEsamiSet->m_sDataOraLock.Left(4)), atoi(m_pEsamiSet->m_sDataOraLock.Mid(4, 2)), atoi(m_pEsamiSet->m_sDataOraLock.Mid(6, 2)), atoi(m_pEsamiSet->m_sDataOraLock.Mid(8, 2)), atoi(m_pEsamiSet->m_sDataOraLock.Mid(10, 2)), 0);
					COleDateTimeSpan timeDiff = oledtStop - oledtStart;

					tagElement.strFieldValue.Format("%li %s %li %s %li %s", timeDiff.GetDays(), theApp.GetMessageString(IDS_GIORNI), timeDiff.GetHours(), theApp.GetMessageString(IDS_ORE), timeDiff.GetMinutes(), theApp.GetMessageString(IDS_MINUTI));
				}

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("esame_tempoconvalida", tagElement.strFieldValue);

				break;
			}
			case esame_codicericovero:
			{
				//strTagName = "esame_codicericovero";

				tagElement.strFieldValue = m_pEsamiSet->m_sRicovero;
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("esame_codicericovero", tagElement.strFieldValue);

				break;
			}
			case esame_barcodericovero:
			{
				//strTagName = "esame_barcodericovero";

				tagElement.strFieldValue = m_pEsamiSet->m_sIdEpisodioRicovero;
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("esame_barcodericovero", tagElement.strFieldValue);

				break;
			}
			case esame_dataoralock:
			{
				//strTagName = "esame_dataoralock";

				if (m_pEsamiSet->m_sDataOraLock.GetLength() == 14)
				{
					tagElement.strFieldValue.Format("%s/%s/%s %s:%s:%s", m_pEsamiSet->m_sDataOraLock.Mid(6, 2), m_pEsamiSet->m_sDataOraLock.Mid(4, 2), m_pEsamiSet->m_sDataOraLock.Left(4), m_pEsamiSet->m_sDataOraLock.Mid(8, 2), m_pEsamiSet->m_sDataOraLock.Mid(10, 2), m_pEsamiSet->m_sDataOraLock.Mid(12, 2));
				}
				else
				{
					CTime now = CTime::GetCurrentTime();
					tagElement.strFieldValue = now.Format("%d/%m/%Y %H:%M:%S");
				}
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("esame_dataoralock", tagElement.strFieldValue);

				break;
			}
			case esame_dataorasuperlock:
			{
				//strTagName = "esame_dataorasuperlock";

				if (m_pEsamiSet->m_sDataOraSuperLock.GetLength() == 14)
				{
					tagElement.strFieldValue.Format("%s/%s/%s %s:%s:%s", m_pEsamiSet->m_sDataOraSuperLock.Mid(6, 2), m_pEsamiSet->m_sDataOraSuperLock.Mid(4, 2), m_pEsamiSet->m_sDataOraSuperLock.Left(4), m_pEsamiSet->m_sDataOraSuperLock.Mid(8, 2), m_pEsamiSet->m_sDataOraSuperLock.Mid(10, 2), m_pEsamiSet->m_sDataOraSuperLock.Mid(12, 2));
				}
				else
				{
					CTime now = CTime::GetCurrentTime();
					tagElement.strFieldValue = now.Format("%d/%m/%Y %H:%M:%S");
				}
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("esame_dataorasuperlock", tagElement.strFieldValue);

				break;
			}

			case inps_medico_codicefiscale:
			{
				//strTagName = "inps_medico_codicefiscale";

				long lUserID;
				AMLogin_GetUserID(&lUserID);

				tagElement.strFieldValue = CMediciSet().GetCodiceFiscaleFromUserID(lUserID);
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("inps_medico_codicefiscale", tagElement.strFieldValue);

				break;
			}
			case inps_reperibilita_cognome:
			{
				//strTagName = "inps_reperibilita_cognome";

				tagElement.strFieldValue = m_pEsamiSet->m_sInpsCognome;
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("inps_reperibilita_cognome", tagElement.strFieldValue);

				break;
			}
			case inps_reperibilita_via:
			{
				//strTagName = "inps_reperibilita_via";

				tagElement.strFieldValue = m_pEsamiSet->m_sInpsVia;
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("inps_reperibilita_via", tagElement.strFieldValue);

				break;
			}
			case inps_reperibilita_cap:
			{
				//strTagName = "inps_reperibilita_cap";

				tagElement.strFieldValue = m_pEsamiSet->m_sInpsCap;
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("inps_reperibilita_cap", tagElement.strFieldValue);

				break;
			}
			case inps_reperibilita_comune:
			{
				//strTagName = "inps_reperibilita_comune";

				tagElement.strFieldValue = m_pEsamiSet->m_sInpsComune;
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("inps_reperibilita_comune", tagElement.strFieldValue);

				break;
			}
			case inps_reperibilita_provincia:
			{
				//strTagName = "inps_reperibilita_provincia";

				tagElement.strFieldValue = m_pEsamiSet->m_sInpsProvincia;
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("inps_reperibilita_provincia", tagElement.strFieldValue);

				break;
			}
			case inps_datainizio:
			{
				//strTagName = "inps_datainizio";

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_lInpsDataInizio).GetDate("%d/%m/%Y");
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("inps_datainizio", tagElement.strFieldValue);

				break;
			}
			case inps_datafine:
			{
				//strTagName = "inps_datafine";

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_lInpsDataFine).GetDate("%d/%m/%Y");
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("inps_datafine", tagElement.strFieldValue);

				break;
			}
			case inps_tipocertificato:
			{
				//strTagName = "inps_tipocertificato";

				switch (m_pEsamiSet->m_iInpsTipo)
				{
				case 1:
				{
					tagElement.strFieldValue = theApp.GetMessageString(IDS_CONTINUAZIONE);
					break;
				}
				case 2:
				{
					tagElement.strFieldValue = theApp.GetMessageString(IDS_RICADUTA);
					break;
				}
				default:
				{
					tagElement.strFieldValue = theApp.GetMessageString(IDS_INIZIO);
					break;
				}
				}
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("inps_tipocertificato", tagElement.strFieldValue);

				break;
			}
			case inps_diagnosinote:
			{
				//strTagName = "inps_diagnosinote";

				tagElement.strFieldValue = m_pEsamiSet->m_sInpsNote;
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("inps_diagnosinote", tagElement.strFieldValue);

				break;
			}
			case inps_numeroprotocollo:
			{
				//strTagName = "inps_numeroprotocollo";

				tagElement.strFieldValue = CEsamiSet().GetNumeroProtocolloINPS(m_pEsamiSet->m_lContatore);
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("inps_numeroprotocollo", tagElement.strFieldValue);

				break;
			}

			case esamestrumentale_orainizio:
			{
				//strTagName = "esamestrumentale_orainizio";

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_lCustomDataOraInizioAcq).GetDate("%H:%M");
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("esamestrumentale_orainizio", tagElement.strFieldValue);

				break;
			}
			case esamestrumentale_orafine:
			{
				//strTagName = "esamestrumentale_orafine";

				tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_lCustomDataOraFineAcq).GetDate("%H:%M");
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("esamestrumentale_orafine", tagElement.strFieldValue);

				break;
			}
			case esamestrumentale_durata_oreminuti:
			{
				//strTagName = "esamestrumentale_durata_oreminuti";

				tagElement.strFieldValue = GetStringOreDifferenza(m_pEsamiSet->m_lCustomDataOraInizioAcq, m_pEsamiSet->m_lCustomDataOraFineAcq, FALSE);
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("esamestrumentale_durata_oreminuti", tagElement.strFieldValue);

				break;
			}
			case esamestrumentale_durata_solominuti:
			{
				//strTagName = "esamestrumentale_durata_solominuti";

				tagElement.strFieldValue = GetStringOreDifferenza(m_pEsamiSet->m_lCustomDataOraInizioAcq, m_pEsamiSet->m_lCustomDataOraFineAcq, TRUE);
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("esamestrumentale_durata_solominuti", tagElement.strFieldValue);

				break;
			}

			case pazientecronico_score_hb:
			{
				//strTagName = "pazientecronico_score_hb";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sPazientiCroniciScoreHB;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("pazientecronico_score_hb", tagElement.strFieldValue);

				break;
			}
			case pazientecronico_score_s:
			{
				//strTagName = "pazientecronico_score_s";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sPazientiCroniciScoreS;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("pazientecronico_score_s", tagElement.strFieldValue);

				break;
			}

			case studio_descrizione:
			{
				//strTagName = "studio_descrizione";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lIDStudio) && (m_pEsamiSet->m_lIDStudio > 0))
					{
						tagElement.strFieldValue = CStudiSet().GetDescrizione(m_pEsamiSet->m_lIDStudio);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("studio_descrizione", tagElement.strFieldValue);

				break;
			}
			case studio_data:
			{
				//strTagName = "studio_data";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lDataStudio) && (m_pEsamiSet->m_lDataStudio > 0))
					{
						tagElement.strFieldValue = CCustomDate(m_pEsamiSet->m_lDataStudio).GetDate("%d/%m/%Y");
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("studio_data", tagElement.strFieldValue);

				break;
			}
			case studio_tempotrascorso:
			{
				//strTagName = "studio_tempotrascorso";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lDataStudio) && (m_pEsamiSet->m_lDataStudio > 0))
					{
						tagElement.strFieldValue = GetStringEta(m_pEsamiSet->m_lDataStudio, m_pEsamiSet->m_lData, FormatoEta::AnnoMeseGiornoAbbreviato); //Gabriel BUG 6225 - Lista DO
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}
				AddElementToDocument("studio_tempotrascorso", tagElement.strFieldValue);

				break;
			}

			case utente_inserimentoesame:
			{
				//strTagName = "utente_inserimentoesame";

				tagElement.strFieldValue = CVistaUtentiMediciSet().GetDescrizione(m_pEsamiSet->m_lIDUtenteInserimentoEsame);
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}

				AddElementToDocument("utente_inserimentoesame", tagElement.strFieldValue);

				break;
			}
			case bostonscore_score_dx:
			{
				//strTagName = "bostonscore_score_dx";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreDx) && (m_pEsamiSet->m_lBostonScoreDx >= 0))
					{
						if (bOnlyIsValid)
							return TRUE;

						switch (m_pEsamiSet->m_lBostonScoreDx)
						{
						case 0:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_BOSTONSCORE_0);
							break;
						}
						case 1:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_BOSTONSCORE_1);
							break;
						}
						case 2:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_BOSTONSCORE_2);
							break;
						}
						case 3:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_BOSTONSCORE_3);
							break;
						}
						}

						if (!tagElement.strFieldValue.IsEmpty())
							listElements.AddTail(tagElement);
					}
				}

				AddElementToDocument("bostonscore_score_dx", tagElement.strFieldValue);

				break;
			}
			case bostonscore_score_mid:
			{
				//strTagName = "bostonscore_score_mid";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreMid) && (m_pEsamiSet->m_lBostonScoreMid >= 0))
					{
						if (bOnlyIsValid)
							return TRUE;

						switch (m_pEsamiSet->m_lBostonScoreMid)
						{
						case 0:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_BOSTONSCORE_0);
							break;
						}
						case 1:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_BOSTONSCORE_1);
							break;
						}
						case 2:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_BOSTONSCORE_2);
							break;
						}
						case 3:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_BOSTONSCORE_3);
							break;
						}
						}

						if (!tagElement.strFieldValue.IsEmpty())
							listElements.AddTail(tagElement);
					}
				}

				AddElementToDocument("bostonscore_score_mid", tagElement.strFieldValue);

				break;
			}
			case bostonscore_score_sx:
			{
				//strTagName = "bostonscore_score_sx";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreSx) && (m_pEsamiSet->m_lBostonScoreSx >= 0))
					{
						if (bOnlyIsValid)
							return TRUE;

						switch (m_pEsamiSet->m_lBostonScoreSx)
						{
						case 0:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_BOSTONSCORE_0);
							break;
						}
						case 1:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_BOSTONSCORE_1);
							break;
						}
						case 2:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_BOSTONSCORE_2);
							break;
						}
						case 3:
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_BOSTONSCORE_3);
							break;
						}
						}

						if (!tagElement.strFieldValue.IsEmpty())
							listElements.AddTail(tagElement);
					}
				}

				AddElementToDocument("bostonscore_score_sx", tagElement.strFieldValue);

				break;
			}
			case bostonscore_score_totale:
			{
				//strTagName = "bostonscore_score_totale";

				long lScoreTot = 0;

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreDx) && (m_pEsamiSet->m_lBostonScoreDx >= 0))
						lScoreTot += m_pEsamiSet->m_lBostonScoreDx;

					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreMid) && (m_pEsamiSet->m_lBostonScoreMid >= 0))
						lScoreTot += m_pEsamiSet->m_lBostonScoreMid;

					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreSx) && (m_pEsamiSet->m_lBostonScoreSx >= 0))
						lScoreTot += m_pEsamiSet->m_lBostonScoreSx;
				}

				if ((lScoreTot >= 0) && (lScoreTot <= 9))
				{
					if (bOnlyIsValid)
						return TRUE;

					tagElement.strFieldValue.Format("%li", lScoreTot);
					listElements.AddTail(tagElement);
				}

				AddElementToDocument("bostonscore_score_totale", tagElement.strFieldValue);

				break;
			}
			case bostonscore_descrizione_totale:
			{
				//strTagName = "bostonscore_descrizione_totale";

				long lScoreTot = 0;

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreDx) && (m_pEsamiSet->m_lBostonScoreDx >= 0))
						lScoreTot += m_pEsamiSet->m_lBostonScoreDx;

					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreMid) && (m_pEsamiSet->m_lBostonScoreMid >= 0))
						lScoreTot += m_pEsamiSet->m_lBostonScoreMid;

					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lBostonScoreSx) && (m_pEsamiSet->m_lBostonScoreSx >= 0))
						lScoreTot += m_pEsamiSet->m_lBostonScoreSx;
				}

				if ((lScoreTot >= 0) && (lScoreTot <= 9))
				{
					tagElement.strFieldValue = theApp.m_sBostonScore[lScoreTot];
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}

				AddElementToDocument("bostonscore_descrizione_totale", tagElement.strFieldValue);

				break;
			}
			case esame_temporetrazione:
			{
				//strTagName = "esame_temporetrazione";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lTempoRetrazione) && (m_pEsamiSet->m_lTempoRetrazione > 0))
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.strFieldValue.Format("%li:%02li", m_pEsamiSet->m_lTempoRetrazione / 60, m_pEsamiSet->m_lTempoRetrazione % 60);
						listElements.AddTail(tagElement);
					}
				}

				AddElementToDocument("esame_temporetrazione", tagElement.strFieldValue);

				break;
			}
			case worklist_note:
			{
				//strTagName = "worklist_note";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sNote;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_note", tagElement.strFieldValue);

				break;
			}
			case worklist_assiden:
			{
				//strTagName = "worklist_assiden";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sAssIden;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_assiden", tagElement.strFieldValue);

				break;
			}
			case worklist_cognome:
			{
				//strTagName = "worklist_cognome";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sCognome;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_cognome", tagElement.strFieldValue);

				break;
			}
			case worklist_cognome2:
			{
				//strTagName = "worklist_cognome2";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sCognome2;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_cognome2", tagElement.strFieldValue);

				break;
			}
			case worklist_nome:
			{
				//strTagName = "worklist_nome";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sNome;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_nome", tagElement.strFieldValue);

				break;
			}
			case worklist_datanascita:
			{
				//strTagName = "worklist_datanascita";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					tagElement.strFieldValue = "";

					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							BOOL bOK = FALSE;

							if (!setWorklist.IsFieldNull(&setWorklist.m_lDataNascitaCustom))
							{
								if (setWorklist.m_lDataNascitaCustom > 0)
								{
									tagElement.strFieldValue = CCustomDate(setWorklist.m_lDataNascitaCustom).GetDate("%d/%m/%Y");
									bOK = !tagElement.strFieldValue.IsEmpty();
								}
							}

							if (!bOK)
							{
								if (setWorklist.m_sDataNascita.GetLength() == 8)
									tagElement.strFieldValue = setWorklist.m_sDataNascita.Right(2) + "/" + setWorklist.m_sDataNascita.Mid(4, 2) + "/" + setWorklist.m_sDataNascita.Left(4);
							}
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_datanascita", tagElement.strFieldValue);

				break;
			}
			case worklist_comunenascita:
			{
				//strTagName = "worklist_comunenascita";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sComuneNascita;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_comunenascita", tagElement.strFieldValue);

				break;
			}
			case worklist_indirizzoresidenza:
			{
				//strTagName = "worklist_indirizzoresidenza";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sIndirizzoResidenza;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_indirizzoresidenza", tagElement.strFieldValue);

				break;
			}
			case worklist_comuneresidenza:
			{
				//strTagName = "worklist_comuneresidenza";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sComuneResidenza;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_comuneresidenza", tagElement.strFieldValue);

				break;
			}
			case worklist_capresidenza:
			{
				//strTagName = "worklist_capresidenza";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sCapResidenza;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_capresidenza", tagElement.strFieldValue);

				break;
			}
			case worklist_telefono1:
			{
				//strTagName = "worklist_telefono1";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sTelefono1;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_telefono1", tagElement.strFieldValue);

				break;
			}
			case worklist_telefono2:
			{
				//strTagName = "worklist_telefono2";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sTelefono2;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_telefono2", tagElement.strFieldValue);

				break;
			}
			case worklist_cellulare1:
			{
				//strTagName = "worklist_cellulare1";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sCellulare1;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_cellulare1", tagElement.strFieldValue);

				break;
			}
			case worklist_cellulare2:
			{
				//strTagName = "worklist_cellulare2";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sCellulare2;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_cellulare2", tagElement.strFieldValue);

				break;
			}
			case worklist_codicefiscale:
			{
				//strTagName = "worklist_codicefiscale";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sCodiceFiscale;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_codicefiscale", tagElement.strFieldValue);

				break;
			}
			case worklist_codicesanitario:
			{
				//strTagName = "worklist_codicesanitario";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sCodiceSanitario;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_codicesanitario", tagElement.strFieldValue);

				break;
			}
			case worklist_codicestp:
			{
				//strTagName = "worklist_codicestp";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sCodiceSTP;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_codicestp", tagElement.strFieldValue);

				break;
			}
			case worklist_codiceteam:
			{
				//strTagName = "worklist_codiceteam";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sCodiceTEAM;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_codiceteam", tagElement.strFieldValue);

				break;
			}
			case worklist_sesso:
			{
				//strTagName = "worklist_sesso";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							switch (setWorklist.m_lSesso)
							{
							case -1:
								tagElement.strFieldValue = theApp.GetMessageString(IDS_PAZIENTIDLG_ND);
								break;
							case 0:
								tagElement.strFieldValue = theApp.GetMessageString(IDS_PAZIENTIDLG_MALE);
								break;
							case 1:
								tagElement.strFieldValue = theApp.GetMessageString(IDS_PAZIENTIDLG_FEMALE);
								break;
							case 2:
								tagElement.strFieldValue = theApp.GetMessageString(IDS_PAZIENTIDLG_AMBIGOUS);
								break;
							case 3:
								tagElement.strFieldValue = theApp.GetMessageString(IDS_PAZIENTIDLG_NOTAPPLICABLE);
								break;
							case 4:
								tagElement.strFieldValue = theApp.GetMessageString(IDS_PAZIENTIDLG_OTHER);
								break;
							default:
								break;
							}

							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_sesso", tagElement.strFieldValue);

				break;
			}
			case worklist_medicocurante:
			{
				//strTagName = "worklist_medicocurante";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sMedicoCurante;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_medicocurante", tagElement.strFieldValue);

				break;
			}
			case worklist_cittadinanza:
			{
				//strTagName = "worklist_cittadinanza";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sCittadinanza;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_cittadinanza", tagElement.strFieldValue);

				break;
			}
			case worklist_provincia:
			{
				//strTagName = "worklist_provincia";

				if (theApp.m_lIDPrintingWorklist > 0)
				{
					CString sWorklistFilter;
					sWorklistFilter.Format("ID=%li", theApp.m_lIDPrintingWorklist);

					CExtOrdiniSet setWorklist;
					setWorklist.SetOpenFilter(sWorklistFilter);
					if (setWorklist.OpenRecordset("CEsamiView::GetField"))
					{
						if (!setWorklist.IsEOF())
						{
							tagElement.strFieldValue = setWorklist.m_sProvincia;
							tagElement.strFieldValue.Trim();
						}
						setWorklist.CloseRecordset("CEsamiView::GetField");
					}

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("worklist_provincia", tagElement.strFieldValue);

				break;
			}

			case utenteconvalida_anagrafica:
			{
				//strTagName = "utenteconvalida_anagrafica";

				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					long lIDUtenteConvalida = 0;
					if (m_pEsamiSet->m_bLocked)
						lIDUtenteConvalida = m_pEsamiSet->m_lIdUtenteLock;
					else
						lIDUtenteConvalida = GetUserIDForLockSuperlock();

					long lIDUtenteChiusura = 0;
					if (m_pEsamiSet->m_bSuperLocked)
						lIDUtenteChiusura = m_pEsamiSet->m_lIdUtenteSuperLock;
					else
						lIDUtenteChiusura = GetUserIDForLockSuperlock();

					if (lIDUtenteConvalida > 0)
					{
						BOOL bPrint = TRUE;

						if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
							if (lIDUtenteConvalida == lIDUtenteChiusura)
								bPrint = FALSE;

						if (bPrint)
						{
							CString sCognome;
							CString sNome;
							CString sCodFisc;
							CMediciSet().GetUserDataFromUserID(lIDUtenteConvalida, &sCognome, &sNome, &sCodFisc);

							tagElement.strFieldValue = sCognome + " " + sNome;
							tagElement.strFieldValue.Trim();

							if (!tagElement.strFieldValue.IsEmpty())
							{
								if (bOnlyIsValid)
									return TRUE;

								listElements.AddTail(tagElement);
							}
						}
					}
				}
				AddElementToDocument("utenteconvalida_anagrafica", tagElement.strFieldValue);

				break;
			}
			case utenteconvalida_firma0:
			case utenteconvalida_firma1:
			case utenteconvalida_firma2:
			case utenteconvalida_firma3:
			case utenteconvalida_firma4:
			case utenteconvalida_firma5:
			case utenteconvalida_firma6:
			case utenteconvalida_firma7:
			case utenteconvalida_firma8:
			case utenteconvalida_firma9:
			{
				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					long lIDUtenteConvalida = 0;
					if (m_pEsamiSet->m_bLocked)
						lIDUtenteConvalida = m_pEsamiSet->m_lIdUtenteLock;
					else
						lIDUtenteConvalida = GetUserIDForLockSuperlock();

					long lIDUtenteChiusura = 0;
					if (m_pEsamiSet->m_bSuperLocked)
						lIDUtenteChiusura = m_pEsamiSet->m_lIdUtenteSuperLock;
					else
						lIDUtenteChiusura = GetUserIDForLockSuperlock();

					if (lIDUtenteConvalida > 0)
					{
						BOOL bPrint = TRUE;

						if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
							if (lIDUtenteConvalida == lIDUtenteChiusura)
								bPrint = FALSE;

						if (bPrint)
						{
							int nIndexTemp = nField - utenteconvalida_firma0;
							ASSERT((nIndexTemp >= 0) && (nIndexTemp <= 9));

							tagElement.strFieldValue = CMediciSet().GetFieldFirmaFromUserID(lIDUtenteConvalida, nIndexTemp);
							tagElement.strFieldValue.Trim();

							if (!tagElement.strFieldValue.IsEmpty())
							{
								if (bOnlyIsValid)
									return TRUE;

								listElements.AddTail(tagElement);
							}
						}
					}
				}

				if (nField == utenteconvalida_firma0)
					AddElementToDocument("utenteconvalida_firma0", tagElement.strFieldValue);
				if (nField == utenteconvalida_firma1)
					AddElementToDocument("utenteconvalida_firma1", tagElement.strFieldValue);
				if (nField == utenteconvalida_firma2)
					AddElementToDocument("utenteconvalida_firma2", tagElement.strFieldValue);
				if (nField == utenteconvalida_firma3)
					AddElementToDocument("utenteconvalida_firma3", tagElement.strFieldValue);
				if (nField == utenteconvalida_firma4)
					AddElementToDocument("utenteconvalida_firma4", tagElement.strFieldValue);
				if (nField == utenteconvalida_firma5)
					AddElementToDocument("utenteconvalida_firma5", tagElement.strFieldValue);
				if (nField == utenteconvalida_firma6)
					AddElementToDocument("utenteconvalida_firma6", tagElement.strFieldValue);
				if (nField == utenteconvalida_firma7)
					AddElementToDocument("utenteconvalida_firma7", tagElement.strFieldValue);
				if (nField == utenteconvalida_firma8)
					AddElementToDocument("utenteconvalida_firma8", tagElement.strFieldValue);
				if (nField == utenteconvalida_firma9)
					AddElementToDocument("utenteconvalida_firma9", tagElement.strFieldValue);

				break;
			}

			case utentechiusura_anagrafica:
			{
				//strTagName = "utentechiusura_anagrafica";

				long lUserID = 0;
				if (m_pEsamiSet->m_bSuperLocked)
					lUserID = m_pEsamiSet->m_lIdUtenteSuperLock;
				else
					lUserID = GetUserIDForLockSuperlock();

				if (lUserID > 0)
				{
					CString sCognome;
					CString sNome;
					CString sCodFisc;
					CMediciSet().GetUserDataFromUserID(lUserID, &sCognome, &sNome, &sCodFisc);

					tagElement.strFieldValue = sCognome + " " + sNome;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("utentechiusura_anagrafica", tagElement.strFieldValue);

				break;
			}
			case utentechiusura_firma0:
			case utentechiusura_firma1:
			case utentechiusura_firma2:
			case utentechiusura_firma3:
			case utentechiusura_firma4:
			case utentechiusura_firma5:
			case utentechiusura_firma6:
			case utentechiusura_firma7:
			case utentechiusura_firma8:
			case utentechiusura_firma9:
			{
				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					long lUserID = 0;
					if (m_pEsamiSet->m_bSuperLocked)
						lUserID = m_pEsamiSet->m_lIdUtenteSuperLock;
					else
						lUserID = GetUserIDForLockSuperlock();

					if (lUserID > 0)
					{
						int nIndexTemp = nField - utentechiusura_firma0;
						ASSERT((nIndexTemp >= 0) && (nIndexTemp <= 9));

						tagElement.strFieldValue = CMediciSet().GetFieldFirmaFromUserID(lUserID, nIndexTemp);
						tagElement.strFieldValue.Trim();

						if (!tagElement.strFieldValue.IsEmpty())
						{
							if (bOnlyIsValid)
								return TRUE;

							listElements.AddTail(tagElement);
						}
					}
				}

				if (nField == utentechiusura_firma0)
					AddElementToDocument("utentechiusura_firma0", tagElement.strFieldValue);
				if (nField == utentechiusura_firma1)
					AddElementToDocument("utentechiusura_firma1", tagElement.strFieldValue);
				if (nField == utentechiusura_firma2)
					AddElementToDocument("utentechiusura_firma2", tagElement.strFieldValue);
				if (nField == utentechiusura_firma3)
					AddElementToDocument("utentechiusura_firma3", tagElement.strFieldValue);
				if (nField == utentechiusura_firma4)
					AddElementToDocument("utentechiusura_firma4", tagElement.strFieldValue);
				if (nField == utentechiusura_firma5)
					AddElementToDocument("utentechiusura_firma5", tagElement.strFieldValue);
				if (nField == utentechiusura_firma6)
					AddElementToDocument("utentechiusura_firma6", tagElement.strFieldValue);
				if (nField == utentechiusura_firma7)
					AddElementToDocument("utentechiusura_firma7", tagElement.strFieldValue);
				if (nField == utentechiusura_firma8)
					AddElementToDocument("utentechiusura_firma8", tagElement.strFieldValue);
				if (nField == utentechiusura_firma9)
					AddElementToDocument("utentechiusura_firma9", tagElement.strFieldValue);

				break;
			}

			case preliminari_medico1_immaginefirma:
			case preliminari_medico2_immaginefirma:
			case utenteconvalida_immaginefirma:
			case utentechiusura_immaginefirma:
			{
				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					long lIDMedico = 0;
					long lIDUtente = 0;

					if (nField == preliminari_medico1_immaginefirma)
					{
						if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lMedico) && (m_pEsamiSet->m_lMedico > 0))
							lIDMedico = m_pEsamiSet->m_lMedico;
					}
					else if (nField == preliminari_medico2_immaginefirma)
					{
						if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lAssistente) && (m_pEsamiSet->m_lAssistente > 0))
							lIDMedico = m_pEsamiSet->m_lAssistente;
					}
					else if (nField == utenteconvalida_immaginefirma)
					{
						if (m_pEsamiSet->m_bLocked)
						{
							lIDUtente = m_pEsamiSet->m_lIdUtenteLock;
						}
						else
						{
							// Sandro 01/09/2017 //
							if(!m_pEsamiSet->m_bSuperLocked)
								lIDUtente = GetUserIDForLockSuperlock();
						}

						if (lIDUtente > 0)
						{
							long lIDUtenteChiusura = 0;
							if (m_pEsamiSet->m_bSuperLocked)
								lIDUtenteChiusura = m_pEsamiSet->m_lIdUtenteSuperLock;
							else
								lIDUtenteChiusura = GetUserIDForLockSuperlock();

							if (lIDUtente == lIDUtenteChiusura)
								lIDUtente = 0;
						}
					}
					else if (nField == utentechiusura_immaginefirma)
					{
						if (m_pEsamiSet->m_bSuperLocked)
							lIDUtente = m_pEsamiSet->m_lIdUtenteSuperLock;
						else
							lIDUtente = GetUserIDForLockSuperlock();
					}

					CString sFilter = "";
					if (lIDMedico > 0)
						sFilter.Format("Contatore=%li", lIDMedico);
					else if (lIDUtente > 0)
						sFilter.Format("IDUtenteEndox=%li", lIDUtente);

					if (!sFilter.IsEmpty())
					{
						CMediciSet setTemp;
						setTemp.SetOpenFilter(sFilter);
						if (setTemp.OpenRecordset("CEsamiView::GetField"))
						{
							if (!setTemp.IsEOF() && !setTemp.m_sImmagineFirma.IsEmpty())
							{
								if (bOnlyIsValid)
								{
									setTemp.CloseRecordset("CEsamiView::GetField");
									return TRUE;
								}

								LPTSTR pImmagineFirma = setTemp.m_sImmagineFirma.GetBuffer(setTemp.m_sImmagineFirma.GetLength());
								UINT iBitmapSize = AmBase64_CalculateRequiredDecodeOutputBufferSize(pImmagineFirma);
								BYTE* pBitmapBuffer = new BYTE[iBitmapSize];
								AmBase64_DecodeBuffer(pImmagineFirma, setTemp.m_sImmagineFirma.GetLength(), (TCHAR*)pBitmapBuffer);
								setTemp.m_sImmagineFirma.ReleaseBuffer();

								//

								tagElement.strFieldValue.Format("IMM%05d", nField);

								CString strFileXXX;
								strFileXXX.Format("%s\\%s_%s.xxx", theApp.m_sDirTemp, tagElement.strFieldValue, CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M%S"));
								HANDLE hFileXXX = CreateFile(strFileXXX, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
								if (hFileXXX != INVALID_HANDLE_VALUE)
								{
									DWORD dwBytesWrite;
									WriteFile(hFileXXX, pBitmapBuffer, iBitmapSize, &dwBytesWrite, NULL);
								}
								CloseHandle(hFileXXX);

								//

								CString strFileFinal = "";

								USES_CONVERSION;
								Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)Gdiplus::Bitmap::FromFile(A2W(strFileXXX));
								if (pBitmap->GetLastStatus() == Gdiplus::Ok)
								{
									if (theApp.m_bPDFImmaginiNonCompresse)
									{
										USES_CONVERSION;
										CLSID idClass;
										if (GetEncoderClsid(L"image/png", &idClass))
										{
											strFileFinal.Format("%s\\%s_%s.png", theApp.m_sDirTemp, tagElement.strFieldValue, CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M%S"));

											if (pBitmap->Save(T2W(strFileFinal), &idClass, NULL) == Gdiplus::Ok)
												AmPdfCreator_AddImageFromFilePng(tagElement.strFieldValue, strFileFinal);
										}
									}
									else
									{
										USES_CONVERSION;
										CLSID idClass;
										if (GetEncoderClsid(L"image/jpeg", &idClass))
										{
											strFileFinal.Format("%s\\%s_%s.jpg", theApp.m_sDirTemp, tagElement.strFieldValue, CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M%S"));

											EncoderParameters encoderParameters;
											encoderParameters.Count = 1;
											encoderParameters.Parameter[0].Guid = EncoderQuality;
											encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
											encoderParameters.Parameter[0].NumberOfValues = 1;
											ULONG quality = theApp.m_lPDFQualitaImmaginiCompresse; // Sandro 20/09/2013 // RAS 20130112 //
											encoderParameters.Parameter[0].Value = &quality;

											if (pBitmap->Save(T2W(strFileFinal), &idClass, &encoderParameters) == Gdiplus::Ok)
												AmPdfCreator_AddImageFromFileJpg(tagElement.strFieldValue, strFileFinal);
										}
									}
								}
								delete pBitmap;

								//

								// Sandro 31/08/2017 //
								// AmPdfCreator_PrintIcon(tagElement); // Sandro 11/05/2015 // con PrintIcon non mi stampa i bordi neri //

								tagElement.lFieldType = TYPE_ICON;
								tagElement.lMyParam = -1;
								listElements.AddTail(tagElement); // aggiungo l'elemento in coda //

								//

								// DeleteFile(strFileFinal);
								DeleteFile(strFileXXX);
							}

							setTemp.CloseRecordset("CEsamiView::GetField");
						}
					}
				}

				if (nField == preliminari_medico1_immaginefirma)
					AddElementToDocument("preliminari_medico1_immaginefirma", tagElement.strFieldValue);
				if (nField == preliminari_medico2_immaginefirma)
					AddElementToDocument("preliminari_medico2_immaginefirma", tagElement.strFieldValue);
				if (nField == utenteconvalida_immaginefirma)
					AddElementToDocument("utenteconvalida_immaginefirma", tagElement.strFieldValue);
				if (nField == utentechiusura_immaginefirma)
					AddElementToDocument("utentechiusura_immaginefirma", tagElement.strFieldValue);

				break;
			}
			case esame_urgente:
			{
				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					switch (m_pEsamiSet->m_lLivelloUrgenza)
					{
					case 0:
					{
						tagElement.strFieldValue = theApp.GetMessageString(IDS_ESAME_NONURGENTE);
						break;
					}
					case 1:
					{
						tagElement.strFieldValue = theApp.GetMessageString(IDS_ESAME_URGENTE);
						break;
					}
					default:
					{
						tagElement.strFieldValue = "";
						break;
					}
					}

					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("esame_urgente", tagElement.strFieldValue);

				break;
			}
			case utenteloggato:
			{
				tagElement.strFieldValue = theApp.m_sUtenteLoggato;
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}
				AddElementToDocument("utenteloggato", tagElement.strFieldValue);

				break;
			}
			case fleury_ficha:
			{
				tagElement.strFieldValue = m_pEsamiSet->m_sCodEsame;
				tagElement.strFieldValue.Trim();

				switch (tagElement.strFieldValue.GetLength())
				{
					case 14:
					{
						tagElement.strFieldValue = tagElement.strFieldValue.Left(10) + "000" + tagElement.strFieldValue.Mid(11, 1) + "00";
						break;
					}
					case 15:
					{
						tagElement.strFieldValue = tagElement.strFieldValue.Left(10) + "00" + tagElement.strFieldValue.Mid(11, 2) + "00";
						break;
					}
				}

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}
				AddElementToDocument("fleuryficha", tagElement.strFieldValue);

				break;
			}
			//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
			case medico_inviante2:
			{
				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sInvMedico2;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("medico_inviante2", tagElement.strFieldValue);

			break;
			}
			case medico_inviante3:
			{
				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_sInvMedico3;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("medico_inviante3", tagElement.strFieldValue);

			break;
			}
			case medico_inviante4:
			{
			if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
			{
				tagElement.strFieldValue = m_pEsamiSet->m_sInvMedico4;
				tagElement.strFieldValue.Trim();

				if (!tagElement.strFieldValue.IsEmpty())
				{
					if (bOnlyIsValid)
						return TRUE;

					listElements.AddTail(tagElement);
				}
				}
				AddElementToDocument("medico_inviante4", tagElement.strFieldValue);

			break;
			}
			
			case paziente_identificazionepassaporto: //Julio - BUG 3285 - Adequação de laudos
			{
				if (m_pPazientiSet->IsOpen() && !m_pPazientiSet->IsBOF() && !m_pPazientiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pPazientiSet->m_sIdentificazionePassaporto;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("paziente_identificazionepassaporto", tagElement.strFieldValue);

				break;
			}
			
			case paziente_identificazionedoc1: //Julio - BUG 3285 - Adequação de laudos
			{
				if (m_pPazientiSet->IsOpen() && !m_pPazientiSet->IsBOF() && !m_pPazientiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pPazientiSet->m_sIdentificazioneDoc1;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("paziente_identificazionedoc1", tagElement.strFieldValue);

				break;
			}

			case paziente_identificazionedoc2: //Julio - BUG 3285 - Adequação de laudos
			{
				if (m_pPazientiSet->IsOpen() && !m_pPazientiSet->IsBOF() && !m_pPazientiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pPazientiSet->m_sIdentificazioneDoc2;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("paziente_identificazionedoc2", tagElement.strFieldValue);

				break;
			}
			case referto_integrato_macro: //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
			{
				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_setRI.m_sRTFMacro;
					tagElement.strFieldValue.Trim();					

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.lFieldType = TYPE_RTF;
						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("referto_integrato_macro", tagElement.strFieldValue);

				break;
			}
			case referto_integrato_diag:  //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
			{
				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_setRI.m_sRTFDiag;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;

						tagElement.lFieldType = TYPE_RTF;
						tagElement.bCanExpand = TRUE;
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("referto_integrato_diag", tagElement.strFieldValue);

				break;
			}
			case referto_integrato_firma: //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
			{
				if (m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
				{
					tagElement.strFieldValue = m_pEsamiSet->m_setRI.m_sSignature;
					tagElement.strFieldValue.Trim();

					if (!tagElement.strFieldValue.IsEmpty())
					{
						if (bOnlyIsValid)
							return TRUE;
						
						listElements.AddTail(tagElement);
					}
				}
				AddElementToDocument("referto_integrato_firma", tagElement.strFieldValue);

				break;
			}

		}
	}

	return bReturn;
}
