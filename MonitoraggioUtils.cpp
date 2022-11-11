#include "stdafx.h"
#include "Endox.h"
#include "MonitoraggioUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CMonitoraggioUtils::CMonitoraggioUtils()
{
}


CMonitoraggioUtils::~CMonitoraggioUtils()
{
}

CString CMonitoraggioUtils::DecodeFase(long value)
{
	switch (value)
	{
	case MonitoringPhase::pre:
		return theApp.GetMessageString(IDS_PRE);
	case MonitoringPhase::intra:
		return theApp.GetMessageString(IDS_INTRA);
	case MonitoringPhase::post:
		return theApp.GetMessageString(IDS_POST);
	case MonitoringPhase::recoveryRoom:
		return theApp.GetMessageString(IDS_SALA_RISVEGLIO);
	case MonitoringPhase::discharge:
		return theApp.GetMessageString(IDS_DIMISSIONE);
	}

	return "";
}

CString CMonitoraggioUtils::DecodePolso(long value)
{
	switch (value)
	{
	case 1:
		return theApp.GetMessageString(IDS_RITMICO);
	case 2:
		return theApp.GetMessageString(IDS_ARITMICO);
	}

	return "";
}

CString CMonitoraggioUtils::DecodeIntubazione(long value)
{
	switch (value)
	{
	case 0:
		return theApp.GetMessageString(IDS_INTUBAZIONE_NA);
	case 1:
		return theApp.GetMessageString(IDS_INTUBAZIONE_IN);
	case 2:
		return theApp.GetMessageString(IDS_INTUBAZIONE_OUT);
	}

	return "";
}

CString CMonitoraggioUtils::DecodeVentilazione(long value)
{
	switch (value)
	{
	case 1:
		return theApp.GetMessageString(IDS_SPONTANEA);
	case 2:
		return theApp.GetMessageString(IDS_ASSISTITA);
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreScala(long value)
{
	switch (value)
	{
	case 1:
		return theApp.GetMessageString(IDS_VAS);
	case 2:
		return theApp.GetMessageString(IDS_NRS);
	case 3:
		return theApp.GetMessageString(IDS_WB);
	case 4:
		return theApp.GetMessageString(IDS_CCPO);
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreVAS(long value)
{
	switch (value)
	{
	case 0:
		return "0";
	case 1:
		return "1";
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";
	case 10:
		return "10";
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreNRS(long value)
{
	switch (value)
	{
	case 0:
		return "0";
	case 1:
		return "1";
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";
	case 10:
		return "10";
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreWB(long value)
{
	switch (value)
	{
	case 0:
		return "Non fa male";
	case 1:
		return "Fa poco male";
	case 2:
		return "Fa abbastanza male";
	case 3:
		return "Fa male";
	case 4:
		return "Fa molto male";
	case 5:
		return "Fa malissimo";	
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreCCPO1(long value)
{
	switch (value)
	{
	case -1:
		return "";
	case 0:
		return "0 - Rilassata o neutra";
	case 1:
		return "1 - Tensione";
	case 2:
		return "2 - Smorfie dolorose";	
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreCCPO2(long value)
{
	switch (value)
	{
	case -1:
		return "";
	case 0:
		return "0 - Assenti";
	case 1:
		return "1 - Di protezione";
	case 2:
		return "2 - Agitazione";
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreCCPO3(long value)
{
	switch (value)
	{
	case -1:
		return "";
	case 0:
		return "0 - Rilassato";
	case 1:
		return "1 - Tensione/ridigità";
	case 2:
		return "2 - Forte tensione/ridigità";
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreCCPO4(long value)
{
	switch (value)
	{
	case -1:
		return "N/A";
	case 0:
		return "0 - Normale, o non suoni";
	case 1:
		return "1 - Sospiri o gemiti";
	case 2:
		return "2 - Pianto o singhiozzo";
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreCCPO5(long value)
{
	switch (value)
	{
	case -1:
		return "N/A";
	case 0:
		return "0 - Tollerante alla ventilazione";
	case 1:
		return "1 - Tosse ma tolleranza";
	case 2:
		return "2 - Contrasto alla ventilazione";
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreLocalizzazione(long value)
{
	switch (value)
	{
	case 0:
		return "";
	case 1:
		return "Testa anteriore";
	case 2:
		return "Testa posteriore";
	case 3:
		return "Collo";
	case 4:
		return "Torace";
	case 5:
		return "Arti superiori";
	case 6:
		return "Addome";
	case 7:
		return "Parte lombare";
	case 8:
		return "Zona pelvica/glutei";
	case 9:
		return "Arti inferiori";
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreCaratteristiche(long value)
{
	switch (value)
	{
	case 1:
		return theApp.GetMessageString(IDS_SORDO);
	case 2:
		return theApp.GetMessageString(IDS_PUNTORIO);
	case 3:
		return theApp.GetMessageString(IDS_COSTRITTIVO);
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreFrequenza(long value)
{
	switch (value)
	{
	case 1:
		return theApp.GetMessageString(IDS_DINAMICO);
	case 2:
		return theApp.GetMessageString(IDS_INTERMITTENTE);
	case 3:
		return theApp.GetMessageString(IDS_CONTINUO);
	}

	return "";
}

CString CMonitoraggioUtils::DecodeDoloreDurata(long value)
{
	switch (value)
	{
	case 1:
		return theApp.GetMessageString(IDS_ACUTO);
	case 2:
		return theApp.GetMessageString(IDS_PERSISTENTE);
	case 3:
		return theApp.GetMessageString(IDS_CRONICO);
	}

	return "";
}

CString CMonitoraggioUtils::DecodeRamsay(long value)
{
	switch (value)
	{
	case 1:
		return theApp.GetMessageString(IDS_PAZIENTE_SVEGLIO);
	case 2:
		return theApp.GetMessageString(IDS_RISV_STIMOLI_VERBALI);
	case 3:
		return theApp.GetMessageString(IDS_RISV_STIMOLI_FISICI);
	case 4:
		return theApp.GetMessageString(IDS_SOPOROSO);
	case 5:
		return theApp.GetMessageString(IDS_DIFFICILMENTE_RISV);
	case 6:
		return theApp.GetMessageString(IDS_INTUBATO);
	}

	return "";
}
