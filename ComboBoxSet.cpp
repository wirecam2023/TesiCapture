#include "stdafx.h"
#include "Endox.h"
#include "ComboBoxSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboBoxSet, CBaseSet)

CComboBoxSet::CComboBoxSet(long lComboDefine)
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	ASSERT((lComboDefine >= CMB_PAZ_FAMILIARI) && (lComboDefine <= CMB_ESA_ESAMIPREGRESSI));

	m_lComboDefine = lComboDefine;

	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

void CComboBoxSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "NomeTabella", m_sNomeTabella,	255);
		RFX_Text(pFX, "Testo", m_sTesto, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CComboBoxSet::GetDefaultSQL()
{
	return "ECOMBOTABELLA";
}

void CComboBoxSet::SetEmpty()
{
	m_lContatore = 0;
	m_sNomeTabella = "";
	m_sTesto = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CString CComboBoxSet::GetFieldText(long lContatore)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CComboBoxSet::GetFieldText"))
	{
		if (!IsEOF())
			sReturn = m_sTesto;

		CloseRecordset("CComboBoxSet::GetFieldText");
	}

	return sReturn;
}

CBaseSet* CComboBoxSet::CreateNew()
{
	return (CBaseSet*)new CComboBoxSet(m_lComboDefine);
}

void CComboBoxSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CComboBoxSet* pSet = (CComboBoxSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNomeTabella) || bCopyAll)
		m_sNomeTabella = pSet->m_sNomeTabella;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTesto) || bCopyAll)
		m_sTesto = pSet->m_sTesto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CComboBoxSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CComboBoxSet* pOV = (CComboBoxSet*)pOldValues;
	CComboBoxSet* pNV = (CComboBoxSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("NomeTabella", pOV, &pOV->m_sNomeTabella, pNV, &pNV->m_sNomeTabella);
	sp.Execute("Testo", pOV, &pOV->m_sTesto, pNV, &pNV->m_sTesto);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CComboBoxSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CComboBoxSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CComboBoxSet::DeleteRecordset");
	}
	return bReturn;
}

CString CComboBoxSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO + " AND ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	strNewFilter += " AND " + GetComboTabellaBaseFilter(FALSE);

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CComboBoxSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

// aggiunge una riga e ritorna il relativo contatore //
long CComboBoxSet::AddRow(CString sTesto)
{
	long lReturn = 0;

	SetOpenFilter("Contatore=0");
	if (OpenRecordset("CComboBoxSet::AddRow"))
	{
		if (AddNewRecordset("CComboBoxSet::AddRow"))
		{
			m_sNomeTabella = GetComboTabellaBaseFilter(TRUE);
			m_sTesto = sTesto;

			if (UpdateRecordset("CComboBoxSet::AddRow"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CComboBoxSet::AddRow");
	}

	return lReturn;
}

// elimina una riga specifica //
BOOL CComboBoxSet::DelRow(long lContatore)
{
	BOOL bReturn = FALSE;

	CString sFilter;
	sFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CComboBoxSet::DelRow"))
	{
		if (!IsEOF())
			bReturn = DeleteRecordset("CComboBoxSet::DelRow");

		CloseRecordset("CComboBoxSet::DelRow");
	}

	return bReturn;
}

// modifica una riga specifica //
BOOL CComboBoxSet::EdtRow(long lContatore, CString sTesto)
{
	BOOL bReturn = FALSE;

	CString sFilter;
	sFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CComboBoxSet::EdtRow"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CComboBoxSet::EdtRow"))
			{
				m_sTesto = sTesto;
				bReturn = UpdateRecordset("CComboBoxSet::EdtRow");
			}
		}

		CloseRecordset("CComboBoxSet::EdtRow");
	}

	return bReturn;
}

// Sandro 22/12/2015 //

CString CComboBoxSet::GetComboTabellaBaseFilter(BOOL bSoloNomeTabella)
{
	CString sReturn = "";

	CString sNomeTabella = "";
		switch (m_lComboDefine)
		{
		case CMB_PAZ_FAMILIARI:
		{
			sNomeTabella = "PAZIENTEFAMILIARITA";
			break;
		}
		case CMB_PAZ_PARENTELA:
		{
			sNomeTabella = "PAZIENTEPARENTELA";
			break;
		}
		case CMB_PAZ_PROFESSIO:
		{
			sNomeTabella = "PAZIENTEPROFESSIONE";
			break;
		}
		case CMB_PAZ_NAZIONALI:
		{
			sNomeTabella = "PAZIENTENAZIONALITA";
			break;
		}
		case CMB_ANA_FUMO:
		{
			sNomeTabella = "ANAMNESIFUMO";
			break;
		}
		case CMB_ANA_SIGA:
		{
			sNomeTabella = "ANAMNESISIGARETTE";
			break;
		}
		case CMB_ANA_CAFF:
		{
			sNomeTabella = "ANAMNESICAFFE";
			break;
		}
		case CMB_ANA_ALCO:
		{
			sNomeTabella = "ANAMNESIALCOOL";
			break;
		}
		case CMB_ANA_SUPE:
		{
			sNomeTabella = "ANAMNESISUPERALCOLICI";
			break;
		}
		case CMB_ANA_FARM:
		{
			sNomeTabella = "ANAMNESIFARMACI";
			break;
		}
		case CMB_ANA_ASSU:
		{
			sNomeTabella = "ANAMNESIASSUNZIONE";
			break;
		}
		case CMB_ANA_INDAGINE:
		{
			sNomeTabella = "ANAMNESIINDAGINE";
			break;
		}
		case CMB_ANA_ICHIRURG:
		{
			sNomeTabella = "ANAMNESIICHIRURGICO";
			break;
		}
		case CMB_ANA_IENDOSCO:
		{
			sNomeTabella = "ANAMNESIIENDOSCOPICO";
			break;
		}
		case CMB_ANA_MALATTIE:
		{
			sNomeTabella = "ANAMNESIMALATTIE";
			break;
		}
		case CMB_ESA_ESTENS:
		{
			sNomeTabella = "TABELLA01";
			break;
		}
		case CMB_ESA_FARMAC:
		{
			sNomeTabella = "TABELLA02";
			break;
		}
		case CMB_ESA_STUDIO:
		{
			sNomeTabella = "TABELLA03";
			break;
		}
		case CMB_ESA_CONTRO:
		{
			sNomeTabella = "TABELLA04";
			break;
		}
		case CMB_ESA_PREMED:
		{
			sNomeTabella = "TABELLA06";
			break;
		}
		case CMB_ESA_ACCESS:
		{
			sNomeTabella = "TABELLA08";
			break;
		}
		case CMB_ESA_VALUTA:
		{
			sNomeTabella = "TABELLA11";
			break;
		}
		case CMB_ESA_COMPLICANZE:
		{
			sNomeTabella = "TABELLA12";
			break;
		}
		case CMB_ESA_COMPLICANZEPROVV:
		{
			sNomeTabella = "TABELLA41";
			break;
		}
		case CMB_ESA_COMPLICANZETERAP:
		{
			sNomeTabella = "TABELLA42";
			break;
		}
		case CMB_ESA_COMPLICANZEESITO:
		{
			sNomeTabella = "TABELLA43";
			break;
		}
		case CMB_ESA_GUARIG:
		{
			sNomeTabella = "TABELLA13";
			break;
		}
		case CMB_ESA_QUADRO:
		{
			sNomeTabella = "TABELLA14";
			break;
		}
		case CMB_ESA_TERAPIACONSIGLIATA:
		{
			sNomeTabella = "TABELLA15";
			break;
		}
		case CMB_ESA_TERAPIACONSIGLIATADOSAGG:
		{
			sNomeTabella = "TABELLA21";
			break;
		}
		case CMB_ESA_TERAPIACONSIGLIATADURATA:
		{
			sNomeTabella = "TABELLA22";
			break;
		}
		case CMB_ESA_TERAPIAINATTO:
		{
			sNomeTabella = "ESAMETERAPIA";
			break;
		}
		case CMB_ESA_TERAPIAINATTODOSAGG:
		{
			sNomeTabella = "ESAMEDOSE";
			break;
		}
		case CMB_ESA_TERAPIAINATTODURATA:
		{
			sNomeTabella = "ESAMEDURATA";
			break;
		}
		case CMB_ESA_OSPEDALE:
		{
			sNomeTabella = "ESAMEOSPEDALE";
			break;
		}
		case CMB_ESA_LIBERO000:
		{
			sNomeTabella = "TABELLA000";
			break;
		}
		case CMB_ESA_LIBERO001:
		{
			sNomeTabella = "TABELLA001";
			break;
		}
		case CMB_ESA_LIBERO002:
		{
			sNomeTabella = "TABELLA002";
			break;
		}
		case CMB_ESA_LIBERO003:
		{
			sNomeTabella = "TABELLA003";
			break;
		}
		case CMB_ESA_LIBERO004:
		{
			sNomeTabella = "TABELLA004";
			break;
		}
		case CMB_ESA_LIBERO005:
		{
			sNomeTabella = "TABELLA005";
			break;
		}
		case CMB_ESA_LIBERO006:
		{
			sNomeTabella = "TABELLA006";
			break;
		}
		case CMB_ESA_LIBERO007:
		{
			sNomeTabella = "TABELLA007";
			break;
		}
		case CMB_ESA_LIBERO008:
		{
			sNomeTabella = "TABELLA008";
			break;
		}
		case CMB_ESA_LIBERO009:
		{
			sNomeTabella = "TABELLA009";
			break;
		}
		case CMB_ESA_LIBERO010:
		{
			sNomeTabella = "TABELLA010";
			break;
		}
		case CMB_ESA_LIBERO011:
		{
			sNomeTabella = "TABELLA011";
			break;
		}
		case CMB_ESA_LIBERO012:
		{
			sNomeTabella = "TABELLA012";
			break;
		}
		case CMB_ESA_LIBERO013:
		{
			sNomeTabella = "TABELLA013";
			break;
		}
		case CMB_ESA_LIBERO014:
		{
			sNomeTabella = "TABELLA014";
			break;
		}
		case CMB_ESA_LIBERO015:
		{
			sNomeTabella = "TABELLA015";
			break;
		}
		case CMB_ESA_LIBERO016:
		{
			sNomeTabella = "TABELLA016";
			break;
		}
		case CMB_ESA_LIBERO017:
		{
			sNomeTabella = "TABELLA017";
			break;
		}
		case CMB_ESA_LIBERO018:
		{
			sNomeTabella = "TABELLA018";
			break;
		}
		case CMB_ESA_LIBERO019:
		{
			sNomeTabella = "TABELLA019";
			break;
		}
		case CMB_ESA_LIBERO020:
		{
			sNomeTabella = "TABELLA020";
			break;
		}
		case CMB_ESA_LIBERO021:
		{
			sNomeTabella = "TABELLA021";
			break;
		}
		case CMB_ESA_LIBERO022:
		{
			sNomeTabella = "TABELLA022";
			break;
		}
		case CMB_ESA_LIBERO023:
		{
			sNomeTabella = "TABELLA023";
			break;
		}
		case CMB_ESA_LIBERO024:
		{
			sNomeTabella = "TABELLA024";
			break;
		}
		case CMB_ESA_LIBERO025:
		{
			sNomeTabella = "TABELLA025";
			break;
		}
		case CMB_ESA_LIBERO026:
		{
			sNomeTabella = "TABELLA026";
			break;
		}
		case CMB_ESA_LIBERO027:
		{
			sNomeTabella = "TABELLA027";
			break;
		}
		case CMB_ESA_LIBERO028:
		{
			sNomeTabella = "TABELLA028";
			break;
		}
		case CMB_ESA_LIBERO029:
		{
			sNomeTabella = "TABELLA029";
			break;
		}
		case CMB_ESA_LIBERO030:
		{
			sNomeTabella = "TABELLA030";
			break;
		}
		case CMB_ESA_LIBERO031:
		{
			sNomeTabella = "TABELLA031";
			break;
		}
		case CMB_ESA_LIBERO032:
		{
			sNomeTabella = "TABELLA032";
			break;
		}
		case CMB_ESA_LIBERO033:
		{
			sNomeTabella = "TABELLA033";
			break;
		}
		case CMB_ESA_LIBERO034:
		{
			sNomeTabella = "TABELLA034";
			break;
		}
		case CMB_ESA_LIBERO035:
		{
			sNomeTabella = "TABELLA035";
			break;
		}
		case CMB_ESA_LIBERO036:
		{
			sNomeTabella = "TABELLA036";
			break;
		}
		case CMB_ESA_LIBERO037:
		{
			sNomeTabella = "TABELLA037";
			break;
		}
		case CMB_ESA_LIBERO038:
		{
			sNomeTabella = "TABELLA038";
			break;
		}
		case CMB_ESA_LIBERO039:
		{
			sNomeTabella = "TABELLA039";
			break;
		}
		case CMB_ESA_LIBERO040:
		{
			sNomeTabella = "TABELLA040";
			break;
		}
		case CMB_ESA_LIBERO041:
		{
			sNomeTabella = "TABELLA041";
			break;
		}
		case CMB_ESA_LIBERO042:
		{
			sNomeTabella = "TABELLA042";
			break;
		}
		case CMB_ESA_LIBERO043:
		{
			sNomeTabella = "TABELLA043";
			break;
		}
		case CMB_ESA_LIBERO044:
		{
			sNomeTabella = "TABELLA044";
			break;
		}
		case CMB_ESA_LIBERO045:
		{
			sNomeTabella = "TABELLA045";
			break;
		}
		case CMB_ESA_LIBERO046:
		{
			sNomeTabella = "TABELLA046";
			break;
		}
		case CMB_ESA_LIBERO047:
		{
			sNomeTabella = "TABELLA047";
			break;
		}
		case CMB_ESA_LIBERO048:
		{
			sNomeTabella = "TABELLA048";
			break;
		}
		case CMB_ESA_LIBERO049:
		{
			sNomeTabella = "TABELLA049";
			break;
		}
		case CMB_ESA_LIBERO050:
		{
			sNomeTabella = "TABELLA050";
			break;
		}
		case CMB_ESA_LIBERO051:
		{
			sNomeTabella = "TABELLA051";
			break;
		}
		case CMB_ESA_LIBERO052:
		{
			sNomeTabella = "TABELLA052";
			break;
		}
		case CMB_ESA_LIBERO053:
		{
			sNomeTabella = "TABELLA053";
			break;
		}
		case CMB_ESA_LIBERO054:
		{
			sNomeTabella = "TABELLA054";
			break;
		}
		case CMB_ESA_LIBERO055:
		{
			sNomeTabella = "TABELLA055";
			break;
		}
		case CMB_ESA_LIBERO056:
		{
			sNomeTabella = "TABELLA056";
			break;
		}
		case CMB_ESA_LIBERO057:
		{
			sNomeTabella = "TABELLA057";
			break;
		}
		case CMB_ESA_LIBERO058:
		{
			sNomeTabella = "TABELLA058";
			break;
		}
		case CMB_ESA_LIBERO059:
		{
			sNomeTabella = "TABELLA059";
			break;
		}
		case CMB_ESA_LIBERO060:
		{
			sNomeTabella = "TABELLA060";
			break;
		}
		case CMB_ESA_LIBERO061:
		{
			sNomeTabella = "TABELLA061";
			break;
		}
		case CMB_ESA_LIBERO062:
		{
			sNomeTabella = "TABELLA062";
			break;
		}
		case CMB_ESA_LIBERO063:
		{
			sNomeTabella = "TABELLA063";
			break;
		}
		case CMB_ESA_LIBERO064:
		{
			sNomeTabella = "TABELLA064";
			break;
		}
		case CMB_ESA_LIBERO065:
		{
			sNomeTabella = "TABELLA065";
			break;
		}
		case CMB_ESA_LIBERO066:
		{
			sNomeTabella = "TABELLA066";
			break;
		}
		case CMB_ESA_LIBERO067:
		{
			sNomeTabella = "TABELLA067";
			break;
		}
		case CMB_ESA_LIBERO068:
		{
			sNomeTabella = "TABELLA068";
			break;
		}
		case CMB_ESA_LIBERO069:
		{
			sNomeTabella = "TABELLA069";
			break;
		}
		case CMB_ESA_LIBERO070:
		{
			sNomeTabella = "TABELLA070";
			break;
		}
		case CMB_ESA_LIBERO071:
		{
			sNomeTabella = "TABELLA071";
			break;
		}
		case CMB_ESA_LIBERO072:
		{
			sNomeTabella = "TABELLA072";
			break;
		}
		case CMB_ESA_LIBERO073:
		{
			sNomeTabella = "TABELLA073";
			break;
		}
		case CMB_ESA_LIBERO074:
		{
			sNomeTabella = "TABELLA074";
			break;
		}
		case CMB_ESA_LIBERO075:
		{
			sNomeTabella = "TABELLA075";
			break;
		}
		case CMB_ESA_LIBERO076:
		{
			sNomeTabella = "TABELLA076";
			break;
		}
		case CMB_ESA_LIBERO077:
		{
			sNomeTabella = "TABELLA077";
			break;
		}
		case CMB_ESA_LIBERO078:
		{
			sNomeTabella = "TABELLA078";
			break;
		}
		case CMB_ESA_LIBERO079:
		{
			sNomeTabella = "TABELLA079";
			break;
		}
		case CMB_ESA_LIBERO080:
		{
			sNomeTabella = "TABELLA080";
			break;
		}
		case CMB_ESA_LIBERO081:
		{
			sNomeTabella = "TABELLA081";
			break;
		}
		case CMB_ESA_LIBERO082:
		{
			sNomeTabella = "TABELLA082";
			break;
		}
		case CMB_ESA_LIBERO083:
		{
			sNomeTabella = "TABELLA083";
			break;
		}
		case CMB_ESA_LIBERO084:
		{
			sNomeTabella = "TABELLA084";
			break;
		}
		case CMB_ESA_LIBERO085:
		{
			sNomeTabella = "TABELLA085";
			break;
		}
		case CMB_ESA_LIBERO086:
		{
			sNomeTabella = "TABELLA086";
			break;
		}
		case CMB_ESA_LIBERO087:
		{
			sNomeTabella = "TABELLA087";
			break;
		}
		case CMB_ESA_LIBERO088:
		{
			sNomeTabella = "TABELLA088";
			break;
		}
		case CMB_ESA_LIBERO089:
		{
			sNomeTabella = "TABELLA089";
			break;
		}
		case CMB_ESA_LIBERO090:
		{
			sNomeTabella = "TABELLA090";
			break;
		}
		case CMB_ESA_LIBERO091:
		{
			sNomeTabella = "TABELLA091";
			break;
		}
		case CMB_ESA_LIBERO092:
		{
			sNomeTabella = "TABELLA092";
			break;
		}
		case CMB_ESA_LIBERO093:
		{
			sNomeTabella = "TABELLA093";
			break;
		}
		case CMB_ESA_LIBERO094:
		{
			sNomeTabella = "TABELLA094";
			break;
		}
		case CMB_ESA_LIBERO095:
		{
			sNomeTabella = "TABELLA095";
			break;
		}
		case CMB_ESA_LIBERO096:
		{
			sNomeTabella = "TABELLA096";
			break;
		}
		case CMB_ESA_LIBERO097:
		{
			sNomeTabella = "TABELLA097";
			break;
		}
		case CMB_ESA_LIBERO098:
		{
			sNomeTabella = "TABELLA098";
			break;
		}
		case CMB_ESA_LIBERO099:
		{
			sNomeTabella = "TABELLA099";
			break;
		}
		case CMB_ESA_MOTIVOCONSENSO:
		{
			sNomeTabella = "MOTIVOCONSENSOINFORMATO";
			break;
		}
		case CMB_ESA_TIPODEGENZAINT:
		{
			sNomeTabella = "TIPODEGENZAINTERNI";
			break;
		}
		case CMB_ESA_TIPODEGENZAEST:
		{
			sNomeTabella = "TIPODEGENZAESTERNI";
			break;
		}
		case CMB_ESA_ESAMIPREGRESSI:
		{
			sNomeTabella = "ESAMIPREGRESSI";
			break;
		}
		case CMB_ESA_MOTIVOCANCEL: // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
		{
			sNomeTabella = "MOTIVOCANCEL";
			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}

	sNomeTabella.MakeUpper();
	sNomeTabella.Trim();

	if (!sNomeTabella.IsEmpty())
	{
		if (!bSoloNomeTabella)
			sReturn.Format("NomeTabella='%s'", sNomeTabella);
		else
			sReturn = sNomeTabella;
	}

	return sReturn;
}
