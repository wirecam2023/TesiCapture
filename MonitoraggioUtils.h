#pragma once

class CMonitoraggioUtils
{
public:
	CMonitoraggioUtils();
	~CMonitoraggioUtils();

	static CString DecodeFase(long value);
	static CString DecodePolso(long value);
	static CString DecodeIntubazione(long value);
	static CString DecodeVentilazione(long value);
	static CString DecodeDoloreScala(long value);
	static CString DecodeDoloreVAS(long value);
	static CString DecodeDoloreNRS(long value);
	static CString DecodeDoloreWB(long value);
	static CString DecodeDoloreCCPO1(long value);
	static CString DecodeDoloreCCPO2(long value);
	static CString DecodeDoloreCCPO3(long value);
	static CString DecodeDoloreCCPO4(long value);
	static CString DecodeDoloreCCPO5(long value);
	static CString DecodeDoloreLocalizzazione(long value);
	static CString DecodeDoloreCaratteristiche(long value);
	static CString DecodeDoloreFrequenza(long value);
	static CString DecodeDoloreDurata(long value);
	static CString DecodeRamsay(long value);
};

