#include "stdafx.h"
#include "Endox.h"
#include "EsamiMielogrammaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiMielogrammaSet, CBaseSet)

CEsamiMielogrammaSet::CEsamiMielogrammaSet()
	: CBaseSet(&m_lIDESAME, "IDESAME") // è legato al contatore dell'esame //
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 26; 
}

void CEsamiMielogrammaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDESAME", m_lIDESAME);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "CELULASACONTAR", m_lCELULASACONTAR);
		RFX_Long(pFX, "HISTIOCITOS", m_lHISTIOCITOS);
		RFX_Long(pFX, "MACROFAGOS", m_lMACROFAGOS);
		RFX_Long(pFX, "MASTOCITOS", m_lMASTOCITOS);
		RFX_Long(pFX, "NPROM", m_lNPROM);
		RFX_Long(pFX, "NMIEL", m_lNMIEL);
		RFX_Long(pFX, "NMETAM", m_lNMETAM);
		RFX_Long(pFX, "NBAST", m_lNBAST);
		RFX_Long(pFX, "NSEGM", m_lNSEGM);
		RFX_Long(pFX, "PROERITRO", m_lPROERITRO);
		RFX_Long(pFX, "ERITROBASO", m_lERITROBASO);
		RFX_Long(pFX, "ERITPOLICRO", m_lERITPOLICRO);
		RFX_Long(pFX, "ERITROORTO", m_lERITROORTO);
		RFX_Long(pFX, "BLASTOS", m_lBLASTOS);
		RFX_Long(pFX, "OUTROS", m_lOUTROS);
		RFX_Long(pFX, "EPROM", m_lEPROM);
		RFX_Long(pFX, "EMIEL", m_lEMIEL);
		RFX_Long(pFX, "EMETAM", m_lEMETAM);
		RFX_Long(pFX, "EBAST", m_lEBAST);
		RFX_Long(pFX, "ESEGM", m_lESEGM);
		RFX_Long(pFX, "LINFOCITO", m_lLINFOCITO);
		RFX_Long(pFX, "MONOCITO", m_lMONOCITO);
		RFX_Long(pFX, "PLASMOCITO", m_lPLASMOCITO);
		RFX_Long(pFX, "BSEGM", m_lBSEGM);
		RFX_Text(pFX, "MGC", m_sMGC, 50);
	}
}

CString CEsamiMielogrammaSet::GetDefaultSQL()
{
	return "EEsamiMielogramma";
}

void CEsamiMielogrammaSet::SetEmpty()
{
	m_lIDESAME = 0;
	m_lCELULASACONTAR = 0;
	m_lHISTIOCITOS = 0;
	m_lMACROFAGOS = 0;
	m_lMASTOCITOS = 0;
	m_lNPROM = 0;
	m_lNMIEL = 0;
	m_lNMETAM = 0;
	m_lNBAST = 0;
	m_lNSEGM = 0;
	m_lPROERITRO = 0;
	m_lERITROBASO = 0;
	m_lERITPOLICRO = 0;
	m_lERITROORTO = 0;
	m_lBLASTOS = 0;
	m_lOUTROS = 0;
	m_lEPROM = 0;
	m_lEMIEL = 0;
	m_lEMETAM = 0;
	m_lEBAST = 0;
	m_lESEGM = 0;
	m_lLINFOCITO = 0;
	m_lMONOCITO = 0;
	m_lPLASMOCITO = 0;
	m_lBSEGM = 0;
	m_sMGC = "";
}

void CEsamiMielogrammaSet::CopyFieldFrom(CEsamiMielogrammaSet* pSet, BOOL bEmpty)
{
	if (bEmpty)
		SetEmpty();
	
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDESAME))
		m_lIDESAME = pSet->m_lIDESAME;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lCELULASACONTAR))
		m_lCELULASACONTAR = pSet->m_lCELULASACONTAR;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lHISTIOCITOS))
		m_lHISTIOCITOS = pSet->m_lHISTIOCITOS;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lMACROFAGOS))
		m_lMACROFAGOS = pSet->m_lMACROFAGOS;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lMASTOCITOS))
		m_lMASTOCITOS = pSet->m_lMASTOCITOS;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lNPROM))
		m_lNPROM = pSet->m_lNPROM;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lNMIEL))
		m_lNMIEL = pSet->m_lNMIEL;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lNMETAM))
		m_lNMETAM = pSet->m_lNMETAM;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lNBAST))
		m_lNBAST = pSet->m_lNBAST;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lNSEGM))
		m_lNSEGM = pSet->m_lNSEGM;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lPROERITRO))
		m_lPROERITRO = pSet->m_lPROERITRO;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lERITROBASO))
		m_lERITROBASO = pSet->m_lERITROBASO;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lERITPOLICRO))
		m_lERITPOLICRO = pSet->m_lERITPOLICRO;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lERITROORTO))
		m_lERITROORTO = pSet->m_lERITROORTO;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lBLASTOS))
		m_lBLASTOS = pSet->m_lBLASTOS;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lOUTROS))
		m_lOUTROS = pSet->m_lOUTROS;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEPROM))
		m_lEPROM = pSet->m_lEPROM;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEMIEL))
		m_lEMIEL = pSet->m_lEMIEL;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEMETAM))
		m_lEMETAM = pSet->m_lEMETAM;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEBAST))
		m_lEBAST = pSet->m_lEBAST;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lESEGM))
		m_lESEGM = pSet->m_lESEGM;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lLINFOCITO))
		m_lLINFOCITO = pSet->m_lLINFOCITO;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lMONOCITO))
		m_lMONOCITO = pSet->m_lMONOCITO;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lPLASMOCITO))
		m_lPLASMOCITO = pSet->m_lPLASMOCITO;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lBSEGM))
		m_lBSEGM = pSet->m_lBSEGM;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sMGC))
		m_sMGC = pSet->m_sMGC;

	if (bEmpty && IsOpen())
	{
		SetFieldNull(NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

CBaseSet* CEsamiMielogrammaSet::CreateNew()
{
	return (CBaseSet*)new CEsamiMielogrammaSet;
}

int CEsamiMielogrammaSet::GetEditMode()
{
	return m_nEditMode;
}

void CEsamiMielogrammaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiMielogrammaSet* pSet = (CEsamiMielogrammaSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDESAME) || bCopyAll)
		m_lIDESAME = pSet->m_lIDESAME;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lCELULASACONTAR) || bCopyAll)
		m_lCELULASACONTAR = pSet->m_lCELULASACONTAR;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lHISTIOCITOS) || bCopyAll)
		m_lHISTIOCITOS = pSet->m_lHISTIOCITOS;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lMACROFAGOS) || bCopyAll)
		m_lMACROFAGOS = pSet->m_lMACROFAGOS;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lMASTOCITOS) || bCopyAll)
		m_lMASTOCITOS = pSet->m_lMASTOCITOS;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lNPROM) || bCopyAll)
		m_lNPROM = pSet->m_lNPROM;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lNMIEL) || bCopyAll)
		m_lNMIEL = pSet->m_lNMIEL;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lNMETAM) || bCopyAll)
		m_lNMETAM = pSet->m_lNMETAM;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lNBAST) || bCopyAll)
		m_lNBAST = pSet->m_lNBAST;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lNSEGM) || bCopyAll)
		m_lNSEGM = pSet->m_lNSEGM;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPROERITRO) || bCopyAll)
		m_lPROERITRO = pSet->m_lPROERITRO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lERITROBASO) || bCopyAll)
		m_lERITROBASO = pSet->m_lERITROBASO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lERITPOLICRO) || bCopyAll)
		m_lERITPOLICRO = pSet->m_lERITPOLICRO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lERITROORTO) || bCopyAll)
		m_lERITROORTO = pSet->m_lERITROORTO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lBLASTOS) || bCopyAll)
		m_lBLASTOS = pSet->m_lBLASTOS;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOUTROS) || bCopyAll)
		m_lOUTROS = pSet->m_lOUTROS;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEPROM) || bCopyAll)
		m_lEPROM = pSet->m_lEPROM;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEMIEL) || bCopyAll)
		m_lEMIEL = pSet->m_lEMIEL;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEMETAM) || bCopyAll)
		m_lEMETAM = pSet->m_lEMETAM;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEBAST) || bCopyAll)
		m_lEBAST = pSet->m_lEBAST;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lESEGM) || bCopyAll)
		m_lESEGM = pSet->m_lESEGM;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lLINFOCITO) || bCopyAll)
		m_lLINFOCITO = pSet->m_lLINFOCITO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lMONOCITO) || bCopyAll)
		m_lMONOCITO = pSet->m_lMONOCITO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPLASMOCITO) || bCopyAll)
		m_lPLASMOCITO = pSet->m_lPLASMOCITO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lBSEGM) || bCopyAll)
		m_lBSEGM = pSet->m_lBSEGM;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMGC) || bCopyAll)
		m_sMGC = pSet->m_sMGC;
}

void CEsamiMielogrammaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiMielogrammaSet* pOV = (CEsamiMielogrammaSet*)pOldValues;
	CEsamiMielogrammaSet* pNV = (CEsamiMielogrammaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("CELULASACONTAR", pOV, &pOV->m_lCELULASACONTAR, pNV, &pNV->m_lCELULASACONTAR);
	sp.Execute("HISTIOCITOS", pOV, &pOV->m_lHISTIOCITOS, pNV, &pNV->m_lHISTIOCITOS);
	sp.Execute("MACROFAGOS", pOV, &pOV->m_lMACROFAGOS, pNV, &pNV->m_lMACROFAGOS);
	sp.Execute("MASTOCITOS", pOV, &pOV->m_lMASTOCITOS, pNV, &pNV->m_lMASTOCITOS);
	sp.Execute("NPROM", pOV, &pOV->m_lNPROM, pNV, &pNV->m_lNPROM);
	sp.Execute("NMIEL", pOV, &pOV->m_lNMIEL, pNV, &pNV->m_lNMIEL);
	sp.Execute("NMETAM", pOV, &pOV->m_lNMETAM, pNV, &pNV->m_lNMETAM);
	sp.Execute("NBAST", pOV, &pOV->m_lNBAST, pNV, &pNV->m_lNBAST);
	sp.Execute("NSEGM", pOV, &pOV->m_lNSEGM, pNV, &pNV->m_lNSEGM);
	sp.Execute("PROERITRO", pOV, &pOV->m_lPROERITRO, pNV, &pNV->m_lPROERITRO);
	sp.Execute("ERITROBASO", pOV, &pOV->m_lERITROBASO, pNV, &pNV->m_lERITROBASO);
	sp.Execute("ERITPOLICRO", pOV, &pOV->m_lERITPOLICRO, pNV, &pNV->m_lERITPOLICRO);
	sp.Execute("ERITROORTO", pOV, &pOV->m_lERITROORTO, pNV, &pNV->m_lERITROORTO);
	sp.Execute("BLASTOS", pOV, &pOV->m_lBLASTOS, pNV, &pNV->m_lBLASTOS);
	sp.Execute("OUTROS", pOV, &pOV->m_lOUTROS, pNV, &pNV->m_lOUTROS);
	sp.Execute("EPROM", pOV, &pOV->m_lEPROM, pNV, &pNV->m_lEPROM);
	sp.Execute("EMIEL", pOV, &pOV->m_lEMIEL, pNV, &pNV->m_lEMIEL);
	sp.Execute("EMETAM", pOV, &pOV->m_lEMETAM, pNV, &pNV->m_lEMETAM);
	sp.Execute("EBAST", pOV, &pOV->m_lEBAST, pNV, &pNV->m_lEBAST);
	sp.Execute("ESEGM", pOV, &pOV->m_lESEGM, pNV, &pNV->m_lESEGM);
	sp.Execute("LINFOCITO", pOV, &pOV->m_lLINFOCITO, pNV, &pNV->m_lLINFOCITO);
	sp.Execute("MONOCITO", pOV, &pOV->m_lMONOCITO, pNV, &pNV->m_lMONOCITO);
	sp.Execute("PLASMOCITO", pOV, &pOV->m_lPLASMOCITO, pNV, &pNV->m_lPLASMOCITO);
	sp.Execute("BSEGM", pOV, &pOV->m_lBSEGM, pNV, &pNV->m_lBSEGM);
	sp.Execute("MGC", pOV, &pOV->m_sMGC, pNV, &pNV->m_sMGC);
}