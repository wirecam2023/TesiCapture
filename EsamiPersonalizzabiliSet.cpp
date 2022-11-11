#include "stdafx.h"
#include "Endox.h"
#include "EsamiPersonalizzabiliSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiPersonalizzabiliSet, CBaseSet)

CEsamiPersonalizzabiliSet::CEsamiPersonalizzabiliSet(BOOL bDefaultFieldSet)
	: CBaseSet(&m_lIDEsame, "IDESAME") // è legato al contatore dell'esame //
{
	SetBaseFilter("");
	SetEmpty();

	m_bDefaultFieldSet = bDefaultFieldSet;

	m_nFields = 201; 
}

void CEsamiPersonalizzabiliSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDEsame", m_lIDEsame);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Testo000", m_sTesto000, 4000);
		RFX_Text(pFX, "Testo001", m_sTesto001, 4000);
		RFX_Text(pFX, "Testo002", m_sTesto002, 4000);
		RFX_Text(pFX, "Testo003", m_sTesto003, 4000);
		RFX_Text(pFX, "Testo004", m_sTesto004, 4000);
		RFX_Text(pFX, "Testo005", m_sTesto005, 4000);
		RFX_Text(pFX, "Testo006", m_sTesto006, 4000);
		RFX_Text(pFX, "Testo007", m_sTesto007, 4000);
		RFX_Text(pFX, "Testo008", m_sTesto008, 4000);
		RFX_Text(pFX, "Testo009", m_sTesto009, 4000);
		RFX_Text(pFX, "Testo010", m_sTesto010, 4000);
		RFX_Text(pFX, "Testo011", m_sTesto011, 4000);
		RFX_Text(pFX, "Testo012", m_sTesto012, 4000);
		RFX_Text(pFX, "Testo013", m_sTesto013, 4000);
		RFX_Text(pFX, "Testo014", m_sTesto014, 4000);
		RFX_Text(pFX, "Testo015", m_sTesto015, 4000);
		RFX_Text(pFX, "Testo016", m_sTesto016, 4000);
		RFX_Text(pFX, "Testo017", m_sTesto017, 4000);
		RFX_Text(pFX, "Testo018", m_sTesto018, 4000);
		RFX_Text(pFX, "Testo019", m_sTesto019, 4000);
		RFX_Text(pFX, "Testo020", m_sTesto020, 4000);
		RFX_Text(pFX, "Testo021", m_sTesto021, 4000);
		RFX_Text(pFX, "Testo022", m_sTesto022, 4000);
		RFX_Text(pFX, "Testo023", m_sTesto023, 4000);
		RFX_Text(pFX, "Testo024", m_sTesto024, 4000);
		RFX_Text(pFX, "Testo025", m_sTesto025, 4000);
		RFX_Text(pFX, "Testo026", m_sTesto026, 4000);
		RFX_Text(pFX, "Testo027", m_sTesto027, 4000);
		RFX_Text(pFX, "Testo028", m_sTesto028, 4000);
		RFX_Text(pFX, "Testo029", m_sTesto029, 4000);
		RFX_Text(pFX, "Testo030", m_sTesto030, 4000);
		RFX_Text(pFX, "Testo031", m_sTesto031, 4000);
		RFX_Text(pFX, "Testo032", m_sTesto032, 4000);
		RFX_Text(pFX, "Testo033", m_sTesto033, 4000);
		RFX_Text(pFX, "Testo034", m_sTesto034, 4000);
		RFX_Text(pFX, "Testo035", m_sTesto035, 4000);
		RFX_Text(pFX, "Testo036", m_sTesto036, 4000);
		RFX_Text(pFX, "Testo037", m_sTesto037, 4000);
		RFX_Text(pFX, "Testo038", m_sTesto038, 4000);
		RFX_Text(pFX, "Testo039", m_sTesto039, 4000);
		RFX_Text(pFX, "Testo040", m_sTesto040, 4000);
		RFX_Text(pFX, "Testo041", m_sTesto041, 4000);
		RFX_Text(pFX, "Testo042", m_sTesto042, 4000);
		RFX_Text(pFX, "Testo043", m_sTesto043, 4000);
		RFX_Text(pFX, "Testo044", m_sTesto044, 4000);
		RFX_Text(pFX, "Testo045", m_sTesto045, 4000);
		RFX_Text(pFX, "Testo046", m_sTesto046, 4000);
		RFX_Text(pFX, "Testo047", m_sTesto047, 4000);
		RFX_Text(pFX, "Testo048", m_sTesto048, 4000);
		RFX_Text(pFX, "Testo049", m_sTesto049, 4000);
		RFX_Text(pFX, "Testo050", m_sTesto050, 4000);
		RFX_Text(pFX, "Testo051", m_sTesto051, 4000);
		RFX_Text(pFX, "Testo052", m_sTesto052, 4000);
		RFX_Text(pFX, "Testo053", m_sTesto053, 4000);
		RFX_Text(pFX, "Testo054", m_sTesto054, 4000);
		RFX_Text(pFX, "Testo055", m_sTesto055, 4000);
		RFX_Text(pFX, "Testo056", m_sTesto056, 4000);
		RFX_Text(pFX, "Testo057", m_sTesto057, 4000);
		RFX_Text(pFX, "Testo058", m_sTesto058, 4000);
		RFX_Text(pFX, "Testo059", m_sTesto059, 4000);
		RFX_Text(pFX, "Testo060", m_sTesto060, 4000);
		RFX_Text(pFX, "Testo061", m_sTesto061, 4000);
		RFX_Text(pFX, "Testo062", m_sTesto062, 4000);
		RFX_Text(pFX, "Testo063", m_sTesto063, 4000);
		RFX_Text(pFX, "Testo064", m_sTesto064, 4000);
		RFX_Text(pFX, "Testo065", m_sTesto065, 4000);
		RFX_Text(pFX, "Testo066", m_sTesto066, 4000);
		RFX_Text(pFX, "Testo067", m_sTesto067, 4000);
		RFX_Text(pFX, "Testo068", m_sTesto068, 4000);
		RFX_Text(pFX, "Testo069", m_sTesto069, 4000);
		RFX_Text(pFX, "Testo070", m_sTesto070, 4000);
		RFX_Text(pFX, "Testo071", m_sTesto071, 4000);
		RFX_Text(pFX, "Testo072", m_sTesto072, 4000);
		RFX_Text(pFX, "Testo073", m_sTesto073, 4000);
		RFX_Text(pFX, "Testo074", m_sTesto074, 4000);
		RFX_Text(pFX, "Testo075", m_sTesto075, 4000);
		RFX_Text(pFX, "Testo076", m_sTesto076, 4000);
		RFX_Text(pFX, "Testo077", m_sTesto077, 4000);
		RFX_Text(pFX, "Testo078", m_sTesto078, 4000);
		RFX_Text(pFX, "Testo079", m_sTesto079, 4000);
		RFX_Text(pFX, "Testo080", m_sTesto080, 4000);
		RFX_Text(pFX, "Testo081", m_sTesto081, 4000);
		RFX_Text(pFX, "Testo082", m_sTesto082, 4000);
		RFX_Text(pFX, "Testo083", m_sTesto083, 4000);
		RFX_Text(pFX, "Testo084", m_sTesto084, 4000);
		RFX_Text(pFX, "Testo085", m_sTesto085, 4000);
		RFX_Text(pFX, "Testo086", m_sTesto086, 4000);
		RFX_Text(pFX, "Testo087", m_sTesto087, 4000);
		RFX_Text(pFX, "Testo088", m_sTesto088, 4000);
		RFX_Text(pFX, "Testo089", m_sTesto089, 4000);
		RFX_Text(pFX, "Testo090", m_sTesto090, 4000);
		RFX_Text(pFX, "Testo091", m_sTesto091, 4000);
		RFX_Text(pFX, "Testo092", m_sTesto092, 4000);
		RFX_Text(pFX, "Testo093", m_sTesto093, 4000);
		RFX_Text(pFX, "Testo094", m_sTesto094, 4000);
		RFX_Text(pFX, "Testo095", m_sTesto095, 4000);
		RFX_Text(pFX, "Testo096", m_sTesto096, 4000);
		RFX_Text(pFX, "Testo097", m_sTesto097, 4000);
		RFX_Text(pFX, "Testo098", m_sTesto098, 4000);
		RFX_Text(pFX, "Testo099", m_sTesto099, 4000);

		RFX_Text(pFX, "TestoRtf000", m_sTestoRtf000, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt000", m_sTestoTxt000, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf001", m_sTestoRtf001, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt001", m_sTestoTxt001, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf002", m_sTestoRtf002, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt002", m_sTestoTxt002, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf003", m_sTestoRtf003, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt003", m_sTestoTxt003, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf004", m_sTestoRtf004, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt004", m_sTestoTxt004, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf005", m_sTestoRtf005, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt005", m_sTestoTxt005, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf006", m_sTestoRtf006, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt006", m_sTestoTxt006, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf007", m_sTestoRtf007, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt007", m_sTestoTxt007, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf008", m_sTestoRtf008, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt008", m_sTestoTxt008, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf009", m_sTestoRtf009, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt009", m_sTestoTxt009, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf010", m_sTestoRtf010, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt010", m_sTestoTxt010, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf011", m_sTestoRtf011, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt011", m_sTestoTxt011, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf012", m_sTestoRtf012, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt012", m_sTestoTxt012, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf013", m_sTestoRtf013, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt013", m_sTestoTxt013, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf014", m_sTestoRtf014, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt014", m_sTestoTxt014, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf015", m_sTestoRtf015, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt015", m_sTestoTxt015, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf016", m_sTestoRtf016, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt016", m_sTestoTxt016, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf017", m_sTestoRtf017, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt017", m_sTestoTxt017, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf018", m_sTestoRtf018, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt018", m_sTestoTxt018, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf019", m_sTestoRtf019, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTxt019", m_sTestoTxt019, _TEXT_CONTROL_FIELD_LIMIT);

		RFX_Text(pFX, "TestoCLRtf000", m_sTestoCLRtf000, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt000", m_sTestoCLTxt000, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf001", m_sTestoCLRtf001, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt001", m_sTestoCLTxt001, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf002", m_sTestoCLRtf002, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt002", m_sTestoCLTxt002, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf003", m_sTestoCLRtf003, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt003", m_sTestoCLTxt003, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf004", m_sTestoCLRtf004, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt004", m_sTestoCLTxt004, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf005", m_sTestoCLRtf005, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt005", m_sTestoCLTxt005, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf006", m_sTestoCLRtf006, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt006", m_sTestoCLTxt006, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf007", m_sTestoCLRtf007, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt007", m_sTestoCLTxt007, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf008", m_sTestoCLRtf008, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt008", m_sTestoCLTxt008, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf009", m_sTestoCLRtf009, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt009", m_sTestoCLTxt009, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf010", m_sTestoCLRtf010, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt010", m_sTestoCLTxt010, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf011", m_sTestoCLRtf011, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt011", m_sTestoCLTxt011, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf012", m_sTestoCLRtf012, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt012", m_sTestoCLTxt012, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf013", m_sTestoCLRtf013, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt013", m_sTestoCLTxt013, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf014", m_sTestoCLRtf014, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt014", m_sTestoCLTxt014, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf015", m_sTestoCLRtf015, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt015", m_sTestoCLTxt015, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf016", m_sTestoCLRtf016, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt016", m_sTestoCLTxt016, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf017", m_sTestoCLRtf017, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt017", m_sTestoCLTxt017, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf018", m_sTestoCLRtf018, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt018", m_sTestoCLTxt018, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLRtf019", m_sTestoCLRtf019, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoCLTxt019", m_sTestoCLTxt019, _TEXT_CONTROL_FIELD_LIMIT);

		RFX_Long(pFX, "DataOra000", m_lDataOra000);
		RFX_Long(pFX, "DataOra001", m_lDataOra001);
		RFX_Long(pFX, "DataOra002", m_lDataOra002);
		RFX_Long(pFX, "DataOra003", m_lDataOra003);
		RFX_Long(pFX, "DataOra004", m_lDataOra004);
		RFX_Long(pFX, "DataOra005", m_lDataOra005);
		RFX_Long(pFX, "DataOra006", m_lDataOra006);
		RFX_Long(pFX, "DataOra007", m_lDataOra007);
		RFX_Long(pFX, "DataOra008", m_lDataOra008);
		RFX_Long(pFX, "DataOra009", m_lDataOra009);
		RFX_Long(pFX, "DataOra010", m_lDataOra010);
		RFX_Long(pFX, "DataOra011", m_lDataOra011);
		RFX_Long(pFX, "DataOra012", m_lDataOra012);
		RFX_Long(pFX, "DataOra013", m_lDataOra013);
		RFX_Long(pFX, "DataOra014", m_lDataOra014);
		RFX_Long(pFX, "DataOra015", m_lDataOra015);
		RFX_Long(pFX, "DataOra016", m_lDataOra016);
		RFX_Long(pFX, "DataOra017", m_lDataOra017);
		RFX_Long(pFX, "DataOra018", m_lDataOra018);
		RFX_Long(pFX, "DataOra019", m_lDataOra019);
	}
}

CString CEsamiPersonalizzabiliSet::GetDefaultSQL()
{
	return m_bDefaultFieldSet ? "EEsamiPersonalizzabiliVD" : "EEsamiPersonalizzabili";
}

void CEsamiPersonalizzabiliSet::SetEmpty()
{
	m_lIDEsame = 0;

	m_sTesto000 = "";
	m_sTesto001 = "";
	m_sTesto002 = "";
	m_sTesto003 = "";
	m_sTesto004 = "";
	m_sTesto005 = "";
	m_sTesto006 = "";
	m_sTesto007 = "";
	m_sTesto008 = "";
	m_sTesto009 = "";
	m_sTesto010 = "";
	m_sTesto011 = "";
	m_sTesto012 = "";
	m_sTesto013 = "";
	m_sTesto014 = "";
	m_sTesto015 = "";
	m_sTesto016 = "";
	m_sTesto017 = "";
	m_sTesto018 = "";
	m_sTesto019 = "";
	m_sTesto020 = "";
	m_sTesto021 = "";
	m_sTesto022 = "";
	m_sTesto023 = "";
	m_sTesto024 = "";
	m_sTesto025 = "";
	m_sTesto026 = "";
	m_sTesto027 = "";
	m_sTesto028 = "";
	m_sTesto029 = "";
	m_sTesto030 = "";
	m_sTesto031 = "";
	m_sTesto032 = "";
	m_sTesto033 = "";
	m_sTesto034 = "";
	m_sTesto035 = "";
	m_sTesto036 = "";
	m_sTesto037 = "";
	m_sTesto038 = "";
	m_sTesto039 = "";
	m_sTesto040 = "";
	m_sTesto041 = "";
	m_sTesto042 = "";
	m_sTesto043 = "";
	m_sTesto044 = "";
	m_sTesto045 = "";
	m_sTesto046 = "";
	m_sTesto047 = "";
	m_sTesto048 = "";
	m_sTesto049 = "";
	m_sTesto050 = "";
	m_sTesto051 = "";
	m_sTesto052 = "";
	m_sTesto053 = "";
	m_sTesto054 = "";
	m_sTesto055 = "";
	m_sTesto056 = "";
	m_sTesto057 = "";
	m_sTesto058 = "";
	m_sTesto059 = "";
	m_sTesto060 = "";
	m_sTesto061 = "";
	m_sTesto062 = "";
	m_sTesto063 = "";
	m_sTesto064 = "";
	m_sTesto065 = "";
	m_sTesto066 = "";
	m_sTesto067 = "";
	m_sTesto068 = "";
	m_sTesto069 = "";
	m_sTesto070 = "";
	m_sTesto071 = "";
	m_sTesto072 = "";
	m_sTesto073 = "";
	m_sTesto074 = "";
	m_sTesto075 = "";
	m_sTesto076 = "";
	m_sTesto077 = "";
	m_sTesto078 = "";
	m_sTesto079 = "";
	m_sTesto080 = "";
	m_sTesto081 = "";
	m_sTesto082 = "";
	m_sTesto083 = "";
	m_sTesto084 = "";
	m_sTesto085 = "";
	m_sTesto086 = "";
	m_sTesto087 = "";
	m_sTesto088 = "";
	m_sTesto089 = "";
	m_sTesto090 = "";
	m_sTesto091 = "";
	m_sTesto092 = "";
	m_sTesto093 = "";
	m_sTesto094 = "";
	m_sTesto095 = "";
	m_sTesto096 = "";
	m_sTesto097 = "";
	m_sTesto098 = "";
	m_sTesto099 = "";

	m_sTestoRtf000 = "";
	m_sTestoTxt000 = "";
	m_sTestoRtf001 = "";
	m_sTestoTxt001 = "";
	m_sTestoRtf002 = "";
	m_sTestoTxt002 = "";
	m_sTestoRtf003 = "";
	m_sTestoTxt003 = "";
	m_sTestoRtf004 = "";
	m_sTestoTxt004 = "";
	m_sTestoRtf005 = "";
	m_sTestoTxt005 = "";
	m_sTestoRtf006 = "";
	m_sTestoTxt006 = "";
	m_sTestoRtf007 = "";
	m_sTestoTxt007 = "";
	m_sTestoRtf008 = "";
	m_sTestoTxt008 = "";
	m_sTestoRtf009 = "";
	m_sTestoTxt009 = "";
	m_sTestoRtf010 = "";
	m_sTestoTxt010 = "";
	m_sTestoRtf011 = "";
	m_sTestoTxt011 = "";
	m_sTestoRtf012 = "";
	m_sTestoTxt012 = "";
	m_sTestoRtf013 = "";
	m_sTestoTxt013 = "";
	m_sTestoRtf014 = "";
	m_sTestoTxt014 = "";
	m_sTestoRtf015 = "";
	m_sTestoTxt015 = "";
	m_sTestoRtf016 = "";
	m_sTestoTxt016 = "";
	m_sTestoRtf017 = "";
	m_sTestoTxt017 = "";
	m_sTestoRtf018 = "";
	m_sTestoTxt018 = "";
	m_sTestoRtf019 = "";
	m_sTestoTxt019 = "";

	m_sTestoCLRtf000 = "";
	m_sTestoCLTxt000 = "";
	m_sTestoCLRtf001 = "";
	m_sTestoCLTxt001 = "";
	m_sTestoCLRtf002 = "";
	m_sTestoCLTxt002 = "";
	m_sTestoCLRtf003 = "";
	m_sTestoCLTxt003 = "";
	m_sTestoCLRtf004 = "";
	m_sTestoCLTxt004 = "";
	m_sTestoCLRtf005 = "";
	m_sTestoCLTxt005 = "";
	m_sTestoCLRtf006 = "";
	m_sTestoCLTxt006 = "";
	m_sTestoCLRtf007 = "";
	m_sTestoCLTxt007 = "";
	m_sTestoCLRtf008 = "";
	m_sTestoCLTxt008 = "";
	m_sTestoCLRtf009 = "";
	m_sTestoCLTxt009 = "";
	m_sTestoCLRtf010 = "";
	m_sTestoCLTxt010 = "";
	m_sTestoCLRtf011 = "";
	m_sTestoCLTxt011 = "";
	m_sTestoCLRtf012 = "";
	m_sTestoCLTxt012 = "";
	m_sTestoCLRtf013 = "";
	m_sTestoCLTxt013 = "";
	m_sTestoCLRtf014 = "";
	m_sTestoCLTxt014 = "";
	m_sTestoCLRtf015 = "";
	m_sTestoCLTxt015 = "";
	m_sTestoCLRtf016 = "";
	m_sTestoCLTxt016 = "";
	m_sTestoCLRtf017 = "";
	m_sTestoCLTxt017 = "";
	m_sTestoCLRtf018 = "";
	m_sTestoCLTxt018 = "";
	m_sTestoCLRtf019 = "";
	m_sTestoCLTxt019 = "";

	m_lDataOra000 = 0;
	m_lDataOra001 = 0;
	m_lDataOra002 = 0;
	m_lDataOra003 = 0;
	m_lDataOra004 = 0;
	m_lDataOra005 = 0;
	m_lDataOra006 = 0;
	m_lDataOra007 = 0;
	m_lDataOra008 = 0;
	m_lDataOra009 = 0;
	m_lDataOra010 = 0;
	m_lDataOra011 = 0;
	m_lDataOra012 = 0;
	m_lDataOra013 = 0;
	m_lDataOra014 = 0;
	m_lDataOra015 = 0;
	m_lDataOra016 = 0;
	m_lDataOra017 = 0;
	m_lDataOra018 = 0;
	m_lDataOra019 = 0;
}

void CEsamiPersonalizzabiliSet::CopyFieldFrom(CEsamiPersonalizzabiliSet* pSet, BOOL bEmpty)
{
	if (bEmpty)
		SetEmpty();
	
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDEsame))
		m_lIDEsame = pSet->m_lIDEsame;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto000))
		m_sTesto000 = pSet->m_sTesto000;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto001))
		m_sTesto001 = pSet->m_sTesto001;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto002))
		m_sTesto002 = pSet->m_sTesto002;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto003))
		m_sTesto003 = pSet->m_sTesto003;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto004))
		m_sTesto004 = pSet->m_sTesto004;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto005))
		m_sTesto005 = pSet->m_sTesto005;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto006))
		m_sTesto006 = pSet->m_sTesto006;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto007))
		m_sTesto007 = pSet->m_sTesto007;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto008))
		m_sTesto008 = pSet->m_sTesto008;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto009))
		m_sTesto009 = pSet->m_sTesto009;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto010))
		m_sTesto010 = pSet->m_sTesto010;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto011))
		m_sTesto011 = pSet->m_sTesto011;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto012))
		m_sTesto012 = pSet->m_sTesto012;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto013))
		m_sTesto013 = pSet->m_sTesto013;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto014))
		m_sTesto014 = pSet->m_sTesto014;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto015))
		m_sTesto015 = pSet->m_sTesto015;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto016))
		m_sTesto016 = pSet->m_sTesto016;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto017))
		m_sTesto017 = pSet->m_sTesto017;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto018))
		m_sTesto018 = pSet->m_sTesto018;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto019))
		m_sTesto019 = pSet->m_sTesto019;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto020))
		m_sTesto020 = pSet->m_sTesto020;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto021))
		m_sTesto021 = pSet->m_sTesto021;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto022))
		m_sTesto022 = pSet->m_sTesto022;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto023))
		m_sTesto023 = pSet->m_sTesto023;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto024))
		m_sTesto024 = pSet->m_sTesto024;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto025))
		m_sTesto025 = pSet->m_sTesto025;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto026))
		m_sTesto026 = pSet->m_sTesto026;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto027))
		m_sTesto027 = pSet->m_sTesto027;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto028))
		m_sTesto028 = pSet->m_sTesto028;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto029))
		m_sTesto029 = pSet->m_sTesto029;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto030))
		m_sTesto030 = pSet->m_sTesto030;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto031))
		m_sTesto031 = pSet->m_sTesto031;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto032))
		m_sTesto032 = pSet->m_sTesto032;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto033))
		m_sTesto033 = pSet->m_sTesto033;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto034))
		m_sTesto034 = pSet->m_sTesto034;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto035))
		m_sTesto035 = pSet->m_sTesto035;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto036))
		m_sTesto036 = pSet->m_sTesto036;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto037))
		m_sTesto037 = pSet->m_sTesto037;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto038))
		m_sTesto038 = pSet->m_sTesto038;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto039))
		m_sTesto039 = pSet->m_sTesto039;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto040))
		m_sTesto040 = pSet->m_sTesto040;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto041))
		m_sTesto041 = pSet->m_sTesto041;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto042))
		m_sTesto042 = pSet->m_sTesto042;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto043))
		m_sTesto043 = pSet->m_sTesto043;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto044))
		m_sTesto044 = pSet->m_sTesto044;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto045))
		m_sTesto045 = pSet->m_sTesto045;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto046))
		m_sTesto046 = pSet->m_sTesto046;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto047))
		m_sTesto047 = pSet->m_sTesto047;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto048))
		m_sTesto048 = pSet->m_sTesto048;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto049))
		m_sTesto049 = pSet->m_sTesto049;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto050))
		m_sTesto050 = pSet->m_sTesto050;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto051))
		m_sTesto051 = pSet->m_sTesto051;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto052))
		m_sTesto052 = pSet->m_sTesto052;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto053))
		m_sTesto053 = pSet->m_sTesto053;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto054))
		m_sTesto054 = pSet->m_sTesto054;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto055))
		m_sTesto055 = pSet->m_sTesto055;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto056))
		m_sTesto056 = pSet->m_sTesto056;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto057))
		m_sTesto057 = pSet->m_sTesto057;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto058))
		m_sTesto058 = pSet->m_sTesto058;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto059))
		m_sTesto059 = pSet->m_sTesto059;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto060))
		m_sTesto060 = pSet->m_sTesto060;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto061))
		m_sTesto061 = pSet->m_sTesto061;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto062))
		m_sTesto062 = pSet->m_sTesto062;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto063))
		m_sTesto063 = pSet->m_sTesto063;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto064))
		m_sTesto064 = pSet->m_sTesto064;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto065))
		m_sTesto065 = pSet->m_sTesto065;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto066))
		m_sTesto066 = pSet->m_sTesto066;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto067))
		m_sTesto067 = pSet->m_sTesto067;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto068))
		m_sTesto068 = pSet->m_sTesto068;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto069))
		m_sTesto069 = pSet->m_sTesto069;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto070))
		m_sTesto070 = pSet->m_sTesto070;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto071))
		m_sTesto071 = pSet->m_sTesto071;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto072))
		m_sTesto072 = pSet->m_sTesto072;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto073))
		m_sTesto073 = pSet->m_sTesto073;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto074))
		m_sTesto074 = pSet->m_sTesto074;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto075))
		m_sTesto075 = pSet->m_sTesto075;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto076))
		m_sTesto076 = pSet->m_sTesto076;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto077))
		m_sTesto077 = pSet->m_sTesto077;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto078))
		m_sTesto078 = pSet->m_sTesto078;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto079))
		m_sTesto079 = pSet->m_sTesto079;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto080))
		m_sTesto080 = pSet->m_sTesto080;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto081))
		m_sTesto081 = pSet->m_sTesto081;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto082))
		m_sTesto082 = pSet->m_sTesto082;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto083))
		m_sTesto083 = pSet->m_sTesto083;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto084))
		m_sTesto084 = pSet->m_sTesto084;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto085))
		m_sTesto085 = pSet->m_sTesto085;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto086))
		m_sTesto086 = pSet->m_sTesto086;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto087))
		m_sTesto087 = pSet->m_sTesto087;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto088))
		m_sTesto088 = pSet->m_sTesto088;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto089))
		m_sTesto089 = pSet->m_sTesto089;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto090))
		m_sTesto090 = pSet->m_sTesto090;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto091))
		m_sTesto091 = pSet->m_sTesto091;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto092))
		m_sTesto092 = pSet->m_sTesto092;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto093))
		m_sTesto093 = pSet->m_sTesto093;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto094))
		m_sTesto094 = pSet->m_sTesto094;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto095))
		m_sTesto095 = pSet->m_sTesto095;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto096))
		m_sTesto096 = pSet->m_sTesto096;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto097))
		m_sTesto097 = pSet->m_sTesto097;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto098))
		m_sTesto098 = pSet->m_sTesto098;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTesto099))
		m_sTesto099 = pSet->m_sTesto099;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf000))
		m_sTestoRtf000 = pSet->m_sTestoRtf000;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt000))
		m_sTestoTxt000 = pSet->m_sTestoTxt000;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf001))
		m_sTestoRtf001 = pSet->m_sTestoRtf001;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt001))
		m_sTestoTxt001 = pSet->m_sTestoTxt001;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf002))
		m_sTestoRtf002 = pSet->m_sTestoRtf002;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt002))
		m_sTestoTxt002 = pSet->m_sTestoTxt002;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf003))
		m_sTestoRtf003 = pSet->m_sTestoRtf003;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt003))
		m_sTestoTxt003 = pSet->m_sTestoTxt003;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf004))
		m_sTestoRtf004 = pSet->m_sTestoRtf004;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt004))
		m_sTestoTxt004 = pSet->m_sTestoTxt004;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf005))
		m_sTestoRtf005 = pSet->m_sTestoRtf005;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt005))
		m_sTestoTxt005 = pSet->m_sTestoTxt005;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf006))
		m_sTestoRtf006 = pSet->m_sTestoRtf006;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt006))
		m_sTestoTxt006 = pSet->m_sTestoTxt006;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf007))
		m_sTestoRtf007 = pSet->m_sTestoRtf007;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt007))
		m_sTestoTxt007 = pSet->m_sTestoTxt007;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf008))
		m_sTestoRtf008 = pSet->m_sTestoRtf008;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt008))
		m_sTestoTxt008 = pSet->m_sTestoTxt008;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf009))
		m_sTestoRtf009 = pSet->m_sTestoRtf009;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt009))
		m_sTestoTxt009 = pSet->m_sTestoTxt009;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf010))
		m_sTestoRtf010 = pSet->m_sTestoRtf010;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt010))
		m_sTestoTxt010 = pSet->m_sTestoTxt010;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf011))
		m_sTestoRtf011 = pSet->m_sTestoRtf011;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt011))
		m_sTestoTxt011 = pSet->m_sTestoTxt011;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf012))
		m_sTestoRtf012 = pSet->m_sTestoRtf012;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt012))
		m_sTestoTxt012 = pSet->m_sTestoTxt012;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf013))
		m_sTestoRtf013 = pSet->m_sTestoRtf013;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt013))
		m_sTestoTxt013 = pSet->m_sTestoTxt013;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf014))
		m_sTestoRtf014 = pSet->m_sTestoRtf014;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt014))
		m_sTestoTxt014 = pSet->m_sTestoTxt014;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf015))
		m_sTestoRtf015 = pSet->m_sTestoRtf015;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt015))
		m_sTestoTxt015 = pSet->m_sTestoTxt015;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf016))
		m_sTestoRtf016 = pSet->m_sTestoRtf016;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt016))
		m_sTestoTxt016 = pSet->m_sTestoTxt016;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf017))
		m_sTestoRtf017 = pSet->m_sTestoRtf017;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt017))
		m_sTestoTxt017 = pSet->m_sTestoTxt017;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf018))
		m_sTestoRtf018 = pSet->m_sTestoRtf018;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt018))
		m_sTestoTxt018 = pSet->m_sTestoTxt018;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoRtf019))
		m_sTestoRtf019 = pSet->m_sTestoRtf019;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoTxt019))
		m_sTestoTxt019 = pSet->m_sTestoTxt019;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf000))
		m_sTestoCLRtf000 = pSet->m_sTestoCLRtf000;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt000))
		m_sTestoCLTxt000 = pSet->m_sTestoCLTxt000;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf001))
		m_sTestoCLRtf001 = pSet->m_sTestoCLRtf001;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt001))
		m_sTestoCLTxt001 = pSet->m_sTestoCLTxt001;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf002))
		m_sTestoCLRtf002 = pSet->m_sTestoCLRtf002;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt002))
		m_sTestoCLTxt002 = pSet->m_sTestoCLTxt002;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf003))
		m_sTestoCLRtf003 = pSet->m_sTestoCLRtf003;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt003))
		m_sTestoCLTxt003 = pSet->m_sTestoCLTxt003;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf004))
		m_sTestoCLRtf004 = pSet->m_sTestoCLRtf004;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt004))
		m_sTestoCLTxt004 = pSet->m_sTestoCLTxt004;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf005))
		m_sTestoCLRtf005 = pSet->m_sTestoCLRtf005;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt005))
		m_sTestoCLTxt005 = pSet->m_sTestoCLTxt005;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf006))
		m_sTestoCLRtf006 = pSet->m_sTestoCLRtf006;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt006))
		m_sTestoCLTxt006 = pSet->m_sTestoCLTxt006;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf007))
		m_sTestoCLRtf007 = pSet->m_sTestoCLRtf007;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt007))
		m_sTestoCLTxt007 = pSet->m_sTestoCLTxt007;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf008))
		m_sTestoCLRtf008 = pSet->m_sTestoCLRtf008;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt008))
		m_sTestoCLTxt008 = pSet->m_sTestoCLTxt008;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf009))
		m_sTestoCLRtf009 = pSet->m_sTestoCLRtf009;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt009))
		m_sTestoCLTxt009 = pSet->m_sTestoCLTxt009;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf010))
		m_sTestoCLRtf010 = pSet->m_sTestoCLRtf010;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt010))
		m_sTestoCLTxt010 = pSet->m_sTestoCLTxt010;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf011))
		m_sTestoCLRtf011 = pSet->m_sTestoCLRtf011;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt011))
		m_sTestoCLTxt011 = pSet->m_sTestoCLTxt011;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf012))
		m_sTestoCLRtf012 = pSet->m_sTestoCLRtf012;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt012))
		m_sTestoCLTxt012 = pSet->m_sTestoCLTxt012;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf013))
		m_sTestoCLRtf013 = pSet->m_sTestoCLRtf013;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt013))
		m_sTestoCLTxt013 = pSet->m_sTestoCLTxt013;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf014))
		m_sTestoCLRtf014 = pSet->m_sTestoCLRtf014;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt014))
		m_sTestoCLTxt014 = pSet->m_sTestoCLTxt014;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf015))
		m_sTestoCLRtf015 = pSet->m_sTestoCLRtf015;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt015))
		m_sTestoCLTxt015 = pSet->m_sTestoCLTxt015;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf016))
		m_sTestoCLRtf016 = pSet->m_sTestoCLRtf016;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt016))
		m_sTestoCLTxt016 = pSet->m_sTestoCLTxt016;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf017))
		m_sTestoCLRtf017 = pSet->m_sTestoCLRtf017;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt017))
		m_sTestoCLTxt017 = pSet->m_sTestoCLTxt017;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf018))
		m_sTestoCLRtf018 = pSet->m_sTestoCLRtf018;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt018))
		m_sTestoCLTxt018 = pSet->m_sTestoCLTxt018;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLRtf019))
		m_sTestoCLRtf019 = pSet->m_sTestoCLRtf019;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTestoCLTxt019))
		m_sTestoCLTxt019 = pSet->m_sTestoCLTxt019;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra000))
		m_lDataOra000 = pSet->m_lDataOra000;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra001))
		m_lDataOra001 = pSet->m_lDataOra001;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra002))
		m_lDataOra002 = pSet->m_lDataOra002;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra003))
		m_lDataOra003 = pSet->m_lDataOra003;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra004))
		m_lDataOra004 = pSet->m_lDataOra004;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra005))
		m_lDataOra005 = pSet->m_lDataOra005;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra006))
		m_lDataOra006 = pSet->m_lDataOra006;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra007))
		m_lDataOra007 = pSet->m_lDataOra007;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra008))
		m_lDataOra008 = pSet->m_lDataOra008;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra009))
		m_lDataOra009 = pSet->m_lDataOra009;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra010))
		m_lDataOra010 = pSet->m_lDataOra010;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra011))
		m_lDataOra011 = pSet->m_lDataOra011;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra012))
		m_lDataOra012 = pSet->m_lDataOra012;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra013))
		m_lDataOra013 = pSet->m_lDataOra013;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra014))
		m_lDataOra014 = pSet->m_lDataOra014;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra015))
		m_lDataOra015 = pSet->m_lDataOra015;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra016))
		m_lDataOra016 = pSet->m_lDataOra016;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra017))
		m_lDataOra017 = pSet->m_lDataOra017;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra018))
		m_lDataOra018 = pSet->m_lDataOra018;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataOra019))
		m_lDataOra019 = pSet->m_lDataOra019;

	if (bEmpty && IsOpen())
	{
		SetFieldNull(NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

CBaseSet* CEsamiPersonalizzabiliSet::CreateNew()
{
	return (CBaseSet*)new CEsamiPersonalizzabiliSet;
}

int CEsamiPersonalizzabiliSet::GetEditMode()
{
	return m_nEditMode;
}

void CEsamiPersonalizzabiliSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiPersonalizzabiliSet* pEEsamiRtfSet = (CEsamiPersonalizzabiliSet*)pOriginalSet;

	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto000) || bCopyAll)
		m_sTesto000 = pEEsamiRtfSet->m_sTesto000;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto001) || bCopyAll)
		m_sTesto001 = pEEsamiRtfSet->m_sTesto001;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto002) || bCopyAll)
		m_sTesto002 = pEEsamiRtfSet->m_sTesto002;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto003) || bCopyAll)
		m_sTesto003 = pEEsamiRtfSet->m_sTesto003;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto004) || bCopyAll)
		m_sTesto004 = pEEsamiRtfSet->m_sTesto004;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto005) || bCopyAll)
		m_sTesto005 = pEEsamiRtfSet->m_sTesto005;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto006) || bCopyAll)
		m_sTesto006 = pEEsamiRtfSet->m_sTesto006;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto007) || bCopyAll)
		m_sTesto007 = pEEsamiRtfSet->m_sTesto007;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto008) || bCopyAll)
		m_sTesto008 = pEEsamiRtfSet->m_sTesto008;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto009) || bCopyAll)
		m_sTesto009 = pEEsamiRtfSet->m_sTesto009;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto010) || bCopyAll)
		m_sTesto010 = pEEsamiRtfSet->m_sTesto010;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto011) || bCopyAll)
		m_sTesto011 = pEEsamiRtfSet->m_sTesto011;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto012) || bCopyAll)
		m_sTesto012 = pEEsamiRtfSet->m_sTesto012;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto013) || bCopyAll)
		m_sTesto013 = pEEsamiRtfSet->m_sTesto013;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto014) || bCopyAll)
		m_sTesto014 = pEEsamiRtfSet->m_sTesto014;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto015) || bCopyAll)
		m_sTesto015 = pEEsamiRtfSet->m_sTesto015;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto016) || bCopyAll)
		m_sTesto016 = pEEsamiRtfSet->m_sTesto016;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto017) || bCopyAll)
		m_sTesto017 = pEEsamiRtfSet->m_sTesto017;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto018) || bCopyAll)
		m_sTesto018 = pEEsamiRtfSet->m_sTesto018;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto019) || bCopyAll)
		m_sTesto019 = pEEsamiRtfSet->m_sTesto019;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto020) || bCopyAll)
		m_sTesto020 = pEEsamiRtfSet->m_sTesto020;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto021) || bCopyAll)
		m_sTesto021 = pEEsamiRtfSet->m_sTesto021;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto022) || bCopyAll)
		m_sTesto022 = pEEsamiRtfSet->m_sTesto022;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto023) || bCopyAll)
		m_sTesto023 = pEEsamiRtfSet->m_sTesto023;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto024) || bCopyAll)
		m_sTesto024 = pEEsamiRtfSet->m_sTesto024;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto025) || bCopyAll)
		m_sTesto025 = pEEsamiRtfSet->m_sTesto025;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto026) || bCopyAll)
		m_sTesto026 = pEEsamiRtfSet->m_sTesto026;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto027) || bCopyAll)
		m_sTesto027 = pEEsamiRtfSet->m_sTesto027;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto028) || bCopyAll)
		m_sTesto028 = pEEsamiRtfSet->m_sTesto028;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto029) || bCopyAll)
		m_sTesto029 = pEEsamiRtfSet->m_sTesto029;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto030) || bCopyAll)
		m_sTesto030 = pEEsamiRtfSet->m_sTesto030;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto031) || bCopyAll)
		m_sTesto031 = pEEsamiRtfSet->m_sTesto031;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto032) || bCopyAll)
		m_sTesto032 = pEEsamiRtfSet->m_sTesto032;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto033) || bCopyAll)
		m_sTesto033 = pEEsamiRtfSet->m_sTesto033;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto034) || bCopyAll)
		m_sTesto034 = pEEsamiRtfSet->m_sTesto034;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto035) || bCopyAll)
		m_sTesto035 = pEEsamiRtfSet->m_sTesto035;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto036) || bCopyAll)
		m_sTesto036 = pEEsamiRtfSet->m_sTesto036;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto037) || bCopyAll)
		m_sTesto037 = pEEsamiRtfSet->m_sTesto037;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto038) || bCopyAll)
		m_sTesto038 = pEEsamiRtfSet->m_sTesto038;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto039) || bCopyAll)
		m_sTesto039 = pEEsamiRtfSet->m_sTesto039;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto040) || bCopyAll)
		m_sTesto040 = pEEsamiRtfSet->m_sTesto040;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto041) || bCopyAll)
		m_sTesto041 = pEEsamiRtfSet->m_sTesto041;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto042) || bCopyAll)
		m_sTesto042 = pEEsamiRtfSet->m_sTesto042;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto043) || bCopyAll)
		m_sTesto043 = pEEsamiRtfSet->m_sTesto043;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto044) || bCopyAll)
		m_sTesto044 = pEEsamiRtfSet->m_sTesto044;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto045) || bCopyAll)
		m_sTesto045 = pEEsamiRtfSet->m_sTesto045;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto046) || bCopyAll)
		m_sTesto046 = pEEsamiRtfSet->m_sTesto046;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto047) || bCopyAll)
		m_sTesto047 = pEEsamiRtfSet->m_sTesto047;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto048) || bCopyAll)
		m_sTesto048 = pEEsamiRtfSet->m_sTesto048;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto049) || bCopyAll)
		m_sTesto049 = pEEsamiRtfSet->m_sTesto049;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto050) || bCopyAll)
		m_sTesto050 = pEEsamiRtfSet->m_sTesto050;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto051) || bCopyAll)
		m_sTesto051 = pEEsamiRtfSet->m_sTesto051;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto052) || bCopyAll)
		m_sTesto052 = pEEsamiRtfSet->m_sTesto052;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto053) || bCopyAll)
		m_sTesto053 = pEEsamiRtfSet->m_sTesto053;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto054) || bCopyAll)
		m_sTesto054 = pEEsamiRtfSet->m_sTesto054;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto055) || bCopyAll)
		m_sTesto055 = pEEsamiRtfSet->m_sTesto055;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto056) || bCopyAll)
		m_sTesto056 = pEEsamiRtfSet->m_sTesto056;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto057) || bCopyAll)
		m_sTesto057 = pEEsamiRtfSet->m_sTesto057;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto058) || bCopyAll)
		m_sTesto058 = pEEsamiRtfSet->m_sTesto058;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto059) || bCopyAll)
		m_sTesto059 = pEEsamiRtfSet->m_sTesto059;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto060) || bCopyAll)
		m_sTesto060 = pEEsamiRtfSet->m_sTesto060;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto061) || bCopyAll)
		m_sTesto061 = pEEsamiRtfSet->m_sTesto061;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto062) || bCopyAll)
		m_sTesto062 = pEEsamiRtfSet->m_sTesto062;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto063) || bCopyAll)
		m_sTesto063 = pEEsamiRtfSet->m_sTesto063;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto064) || bCopyAll)
		m_sTesto064 = pEEsamiRtfSet->m_sTesto064;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto065) || bCopyAll)
		m_sTesto065 = pEEsamiRtfSet->m_sTesto065;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto066) || bCopyAll)
		m_sTesto066 = pEEsamiRtfSet->m_sTesto066;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto067) || bCopyAll)
		m_sTesto067 = pEEsamiRtfSet->m_sTesto067;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto068) || bCopyAll)
		m_sTesto068 = pEEsamiRtfSet->m_sTesto068;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto069) || bCopyAll)
		m_sTesto069 = pEEsamiRtfSet->m_sTesto069;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto070) || bCopyAll)
		m_sTesto070 = pEEsamiRtfSet->m_sTesto070;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto071) || bCopyAll)
		m_sTesto071 = pEEsamiRtfSet->m_sTesto071;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto072) || bCopyAll)
		m_sTesto072 = pEEsamiRtfSet->m_sTesto072;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto073) || bCopyAll)
		m_sTesto073 = pEEsamiRtfSet->m_sTesto073;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto074) || bCopyAll)
		m_sTesto074 = pEEsamiRtfSet->m_sTesto074;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto075) || bCopyAll)
		m_sTesto075 = pEEsamiRtfSet->m_sTesto075;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto076) || bCopyAll)
		m_sTesto076 = pEEsamiRtfSet->m_sTesto076;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto077) || bCopyAll)
		m_sTesto077 = pEEsamiRtfSet->m_sTesto077;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto078) || bCopyAll)
		m_sTesto078 = pEEsamiRtfSet->m_sTesto078;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto079) || bCopyAll)
		m_sTesto079 = pEEsamiRtfSet->m_sTesto079;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto080) || bCopyAll)
		m_sTesto080 = pEEsamiRtfSet->m_sTesto080;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto081) || bCopyAll)
		m_sTesto081 = pEEsamiRtfSet->m_sTesto081;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto082) || bCopyAll)
		m_sTesto082 = pEEsamiRtfSet->m_sTesto082;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto083) || bCopyAll)
		m_sTesto083 = pEEsamiRtfSet->m_sTesto083;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto084) || bCopyAll)
		m_sTesto084 = pEEsamiRtfSet->m_sTesto084;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto085) || bCopyAll)
		m_sTesto085 = pEEsamiRtfSet->m_sTesto085;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto086) || bCopyAll)
		m_sTesto086 = pEEsamiRtfSet->m_sTesto086;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto087) || bCopyAll)
		m_sTesto087 = pEEsamiRtfSet->m_sTesto087;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto088) || bCopyAll)
		m_sTesto088 = pEEsamiRtfSet->m_sTesto088;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto089) || bCopyAll)
		m_sTesto089 = pEEsamiRtfSet->m_sTesto089;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto090) || bCopyAll)
		m_sTesto090 = pEEsamiRtfSet->m_sTesto090;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto091) || bCopyAll)
		m_sTesto091 = pEEsamiRtfSet->m_sTesto091;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto092) || bCopyAll)
		m_sTesto092 = pEEsamiRtfSet->m_sTesto092;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto093) || bCopyAll)
		m_sTesto093 = pEEsamiRtfSet->m_sTesto093;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto094) || bCopyAll)
		m_sTesto094 = pEEsamiRtfSet->m_sTesto094;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto095) || bCopyAll)
		m_sTesto095 = pEEsamiRtfSet->m_sTesto095;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto096) || bCopyAll)
		m_sTesto096 = pEEsamiRtfSet->m_sTesto096;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto097) || bCopyAll)
		m_sTesto097 = pEEsamiRtfSet->m_sTesto097;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto098) || bCopyAll)
		m_sTesto098 = pEEsamiRtfSet->m_sTesto098;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTesto099) || bCopyAll)
		m_sTesto099 = pEEsamiRtfSet->m_sTesto099;

	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf000) || bCopyAll)
		m_sTestoRtf000 = pEEsamiRtfSet->m_sTestoRtf000;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt000) || bCopyAll)
		m_sTestoTxt000 = pEEsamiRtfSet->m_sTestoTxt000;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf001) || bCopyAll)
		m_sTestoRtf001 = pEEsamiRtfSet->m_sTestoRtf001;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt001) || bCopyAll)
		m_sTestoTxt001 = pEEsamiRtfSet->m_sTestoTxt001;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf002) || bCopyAll)
		m_sTestoRtf002 = pEEsamiRtfSet->m_sTestoRtf002;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt002) || bCopyAll)
		m_sTestoTxt002 = pEEsamiRtfSet->m_sTestoTxt002;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf003) || bCopyAll)
		m_sTestoRtf003 = pEEsamiRtfSet->m_sTestoRtf003;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt003) || bCopyAll)
		m_sTestoTxt003 = pEEsamiRtfSet->m_sTestoTxt003;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf004) || bCopyAll)
		m_sTestoRtf004 = pEEsamiRtfSet->m_sTestoRtf004;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt004) || bCopyAll)
		m_sTestoTxt004 = pEEsamiRtfSet->m_sTestoTxt004;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf005) || bCopyAll)
		m_sTestoRtf005 = pEEsamiRtfSet->m_sTestoRtf005;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt005) || bCopyAll)
		m_sTestoTxt005 = pEEsamiRtfSet->m_sTestoTxt005;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf006) || bCopyAll)
		m_sTestoRtf006 = pEEsamiRtfSet->m_sTestoRtf006;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt006) || bCopyAll)
		m_sTestoTxt006 = pEEsamiRtfSet->m_sTestoTxt006;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf007) || bCopyAll)
		m_sTestoRtf007 = pEEsamiRtfSet->m_sTestoRtf007;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt007) || bCopyAll)
		m_sTestoTxt007 = pEEsamiRtfSet->m_sTestoTxt007;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf008) || bCopyAll)
		m_sTestoRtf008 = pEEsamiRtfSet->m_sTestoRtf008;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt008) || bCopyAll)
		m_sTestoTxt008 = pEEsamiRtfSet->m_sTestoTxt008;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf009) || bCopyAll)
		m_sTestoRtf009 = pEEsamiRtfSet->m_sTestoRtf009;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt009) || bCopyAll)
		m_sTestoTxt009 = pEEsamiRtfSet->m_sTestoTxt009;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf010) || bCopyAll)
		m_sTestoRtf010 = pEEsamiRtfSet->m_sTestoRtf010;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt010) || bCopyAll)
		m_sTestoTxt010 = pEEsamiRtfSet->m_sTestoTxt010;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf011) || bCopyAll)
		m_sTestoRtf011 = pEEsamiRtfSet->m_sTestoRtf011;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt011) || bCopyAll)
		m_sTestoTxt011 = pEEsamiRtfSet->m_sTestoTxt011;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf012) || bCopyAll)
		m_sTestoRtf012 = pEEsamiRtfSet->m_sTestoRtf012;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt012) || bCopyAll)
		m_sTestoTxt012 = pEEsamiRtfSet->m_sTestoTxt012;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf013) || bCopyAll)
		m_sTestoRtf013 = pEEsamiRtfSet->m_sTestoRtf013;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt013) || bCopyAll)
		m_sTestoTxt013 = pEEsamiRtfSet->m_sTestoTxt013;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf014) || bCopyAll)
		m_sTestoRtf014 = pEEsamiRtfSet->m_sTestoRtf014;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt014) || bCopyAll)
		m_sTestoTxt014 = pEEsamiRtfSet->m_sTestoTxt014;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf015) || bCopyAll)
		m_sTestoRtf015 = pEEsamiRtfSet->m_sTestoRtf015;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt015) || bCopyAll)
		m_sTestoTxt015 = pEEsamiRtfSet->m_sTestoTxt015;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf016) || bCopyAll)
		m_sTestoRtf016 = pEEsamiRtfSet->m_sTestoRtf016;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt016) || bCopyAll)
		m_sTestoTxt016 = pEEsamiRtfSet->m_sTestoTxt016;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf017) || bCopyAll)
		m_sTestoRtf017 = pEEsamiRtfSet->m_sTestoRtf017;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt017) || bCopyAll)
		m_sTestoTxt017 = pEEsamiRtfSet->m_sTestoTxt017;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf018) || bCopyAll)
		m_sTestoRtf018 = pEEsamiRtfSet->m_sTestoRtf018;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt018) || bCopyAll)
		m_sTestoTxt018 = pEEsamiRtfSet->m_sTestoTxt018;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoRtf019) || bCopyAll)
		m_sTestoRtf019 = pEEsamiRtfSet->m_sTestoRtf019;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoTxt019) || bCopyAll)
		m_sTestoTxt019 = pEEsamiRtfSet->m_sTestoTxt019;

	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf000) || bCopyAll)
		m_sTestoCLRtf000 = pEEsamiRtfSet->m_sTestoCLRtf000;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt000) || bCopyAll)
		m_sTestoCLTxt000 = pEEsamiRtfSet->m_sTestoCLTxt000;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf001) || bCopyAll)
		m_sTestoCLRtf001 = pEEsamiRtfSet->m_sTestoCLRtf001;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt001) || bCopyAll)
		m_sTestoCLTxt001 = pEEsamiRtfSet->m_sTestoCLTxt001;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf002) || bCopyAll)
		m_sTestoCLRtf002 = pEEsamiRtfSet->m_sTestoCLRtf002;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt002) || bCopyAll)
		m_sTestoCLTxt002 = pEEsamiRtfSet->m_sTestoCLTxt002;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf003) || bCopyAll)
		m_sTestoCLRtf003 = pEEsamiRtfSet->m_sTestoCLRtf003;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt003) || bCopyAll)
		m_sTestoCLTxt003 = pEEsamiRtfSet->m_sTestoCLTxt003;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf004) || bCopyAll)
		m_sTestoCLRtf004 = pEEsamiRtfSet->m_sTestoCLRtf004;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt004) || bCopyAll)
		m_sTestoCLTxt004 = pEEsamiRtfSet->m_sTestoCLTxt004;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf005) || bCopyAll)
		m_sTestoCLRtf005 = pEEsamiRtfSet->m_sTestoCLRtf005;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt005) || bCopyAll)
		m_sTestoCLTxt005 = pEEsamiRtfSet->m_sTestoCLTxt005;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf006) || bCopyAll)
		m_sTestoCLRtf006 = pEEsamiRtfSet->m_sTestoCLRtf006;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt006) || bCopyAll)
		m_sTestoCLTxt006 = pEEsamiRtfSet->m_sTestoCLTxt006;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf007) || bCopyAll)
		m_sTestoCLRtf007 = pEEsamiRtfSet->m_sTestoCLRtf007;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt007) || bCopyAll)
		m_sTestoCLTxt007 = pEEsamiRtfSet->m_sTestoCLTxt007;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf008) || bCopyAll)
		m_sTestoCLRtf008 = pEEsamiRtfSet->m_sTestoCLRtf008;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt008) || bCopyAll)
		m_sTestoCLTxt008 = pEEsamiRtfSet->m_sTestoCLTxt008;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf009) || bCopyAll)
		m_sTestoCLRtf009 = pEEsamiRtfSet->m_sTestoCLRtf009;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt009) || bCopyAll)
		m_sTestoCLTxt009 = pEEsamiRtfSet->m_sTestoCLTxt009;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf010) || bCopyAll)
		m_sTestoCLRtf010 = pEEsamiRtfSet->m_sTestoCLRtf010;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt010) || bCopyAll)
		m_sTestoCLTxt010 = pEEsamiRtfSet->m_sTestoCLTxt010;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf011) || bCopyAll)
		m_sTestoCLRtf011 = pEEsamiRtfSet->m_sTestoCLRtf011;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt011) || bCopyAll)
		m_sTestoCLTxt011 = pEEsamiRtfSet->m_sTestoCLTxt011;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf012) || bCopyAll)
		m_sTestoCLRtf012 = pEEsamiRtfSet->m_sTestoCLRtf012;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt012) || bCopyAll)
		m_sTestoCLTxt012 = pEEsamiRtfSet->m_sTestoCLTxt012;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf013) || bCopyAll)
		m_sTestoCLRtf013 = pEEsamiRtfSet->m_sTestoCLRtf013;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt013) || bCopyAll)
		m_sTestoCLTxt013 = pEEsamiRtfSet->m_sTestoCLTxt013;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf014) || bCopyAll)
		m_sTestoCLRtf014 = pEEsamiRtfSet->m_sTestoCLRtf014;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt014) || bCopyAll)
		m_sTestoCLTxt014 = pEEsamiRtfSet->m_sTestoCLTxt014;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf015) || bCopyAll)
		m_sTestoCLRtf015 = pEEsamiRtfSet->m_sTestoCLRtf015;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt015) || bCopyAll)
		m_sTestoCLTxt015 = pEEsamiRtfSet->m_sTestoCLTxt015;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf016) || bCopyAll)
		m_sTestoCLRtf016 = pEEsamiRtfSet->m_sTestoCLRtf016;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt016) || bCopyAll)
		m_sTestoCLTxt016 = pEEsamiRtfSet->m_sTestoCLTxt016;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf017) || bCopyAll)
		m_sTestoCLRtf017 = pEEsamiRtfSet->m_sTestoCLRtf017;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt017) || bCopyAll)
		m_sTestoCLTxt017 = pEEsamiRtfSet->m_sTestoCLTxt017;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf018) || bCopyAll)
		m_sTestoCLRtf018 = pEEsamiRtfSet->m_sTestoCLRtf018;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt018) || bCopyAll)
		m_sTestoCLTxt018 = pEEsamiRtfSet->m_sTestoCLTxt018;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLRtf019) || bCopyAll)
		m_sTestoCLRtf019 = pEEsamiRtfSet->m_sTestoCLRtf019;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_sTestoCLTxt019) || bCopyAll)
		m_sTestoCLTxt019 = pEEsamiRtfSet->m_sTestoCLTxt019;

	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra000) || bCopyAll)
		m_lDataOra000 = pEEsamiRtfSet->m_lDataOra000;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra001) || bCopyAll)
		m_lDataOra001 = pEEsamiRtfSet->m_lDataOra001;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra002) || bCopyAll)
		m_lDataOra002 = pEEsamiRtfSet->m_lDataOra002;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra003) || bCopyAll)
		m_lDataOra003 = pEEsamiRtfSet->m_lDataOra003;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra004) || bCopyAll)
		m_lDataOra004 = pEEsamiRtfSet->m_lDataOra004;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra005) || bCopyAll)
		m_lDataOra005 = pEEsamiRtfSet->m_lDataOra005;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra006) || bCopyAll)
		m_lDataOra006 = pEEsamiRtfSet->m_lDataOra006;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra007) || bCopyAll)
		m_lDataOra007 = pEEsamiRtfSet->m_lDataOra007;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra008) || bCopyAll)
		m_lDataOra008 = pEEsamiRtfSet->m_lDataOra008;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra009) || bCopyAll)
		m_lDataOra009 = pEEsamiRtfSet->m_lDataOra009;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra010) || bCopyAll)
		m_lDataOra010 = pEEsamiRtfSet->m_lDataOra010;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra011) || bCopyAll)
		m_lDataOra011 = pEEsamiRtfSet->m_lDataOra011;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra012) || bCopyAll)
		m_lDataOra012 = pEEsamiRtfSet->m_lDataOra012;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra013) || bCopyAll)
		m_lDataOra013 = pEEsamiRtfSet->m_lDataOra013;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra014) || bCopyAll)
		m_lDataOra014 = pEEsamiRtfSet->m_lDataOra014;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra015) || bCopyAll)
		m_lDataOra015 = pEEsamiRtfSet->m_lDataOra015;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra016) || bCopyAll)
		m_lDataOra016 = pEEsamiRtfSet->m_lDataOra016;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra017) || bCopyAll)
		m_lDataOra017 = pEEsamiRtfSet->m_lDataOra017;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra018) || bCopyAll)
		m_lDataOra018 = pEEsamiRtfSet->m_lDataOra018;
	if (!pEEsamiRtfSet->IsOpen() || pEEsamiRtfSet->IsFieldDirty(&pEEsamiRtfSet->m_lDataOra019) || bCopyAll)
		m_lDataOra019 = pEEsamiRtfSet->m_lDataOra019;
}

void CEsamiPersonalizzabiliSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiPersonalizzabiliSet* pOV = (CEsamiPersonalizzabiliSet*)pOldValues;
	CEsamiPersonalizzabiliSet* pNV = (CEsamiPersonalizzabiliSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Testo000", pOV, &pOV->m_sTesto000, pNV, &pNV->m_sTesto000);
	sp.Execute("Testo001", pOV, &pOV->m_sTesto001, pNV, &pNV->m_sTesto001);
	sp.Execute("Testo002", pOV, &pOV->m_sTesto002, pNV, &pNV->m_sTesto002);
	sp.Execute("Testo003", pOV, &pOV->m_sTesto003, pNV, &pNV->m_sTesto003);
	sp.Execute("Testo004", pOV, &pOV->m_sTesto004, pNV, &pNV->m_sTesto004);
	sp.Execute("Testo005", pOV, &pOV->m_sTesto005, pNV, &pNV->m_sTesto005);
	sp.Execute("Testo006", pOV, &pOV->m_sTesto006, pNV, &pNV->m_sTesto006);
	sp.Execute("Testo007", pOV, &pOV->m_sTesto007, pNV, &pNV->m_sTesto007);
	sp.Execute("Testo008", pOV, &pOV->m_sTesto008, pNV, &pNV->m_sTesto008);
	sp.Execute("Testo009", pOV, &pOV->m_sTesto009, pNV, &pNV->m_sTesto009);
	sp.Execute("Testo010", pOV, &pOV->m_sTesto010, pNV, &pNV->m_sTesto010);
	sp.Execute("Testo011", pOV, &pOV->m_sTesto011, pNV, &pNV->m_sTesto011);
	sp.Execute("Testo012", pOV, &pOV->m_sTesto012, pNV, &pNV->m_sTesto012);
	sp.Execute("Testo013", pOV, &pOV->m_sTesto013, pNV, &pNV->m_sTesto013);
	sp.Execute("Testo014", pOV, &pOV->m_sTesto014, pNV, &pNV->m_sTesto014);
	sp.Execute("Testo015", pOV, &pOV->m_sTesto015, pNV, &pNV->m_sTesto015);
	sp.Execute("Testo016", pOV, &pOV->m_sTesto016, pNV, &pNV->m_sTesto016);
	sp.Execute("Testo017", pOV, &pOV->m_sTesto017, pNV, &pNV->m_sTesto017);
	sp.Execute("Testo018", pOV, &pOV->m_sTesto018, pNV, &pNV->m_sTesto018);
	sp.Execute("Testo019", pOV, &pOV->m_sTesto019, pNV, &pNV->m_sTesto019);
	sp.Execute("Testo020", pOV, &pOV->m_sTesto020, pNV, &pNV->m_sTesto020);
	sp.Execute("Testo021", pOV, &pOV->m_sTesto021, pNV, &pNV->m_sTesto021);
	sp.Execute("Testo022", pOV, &pOV->m_sTesto022, pNV, &pNV->m_sTesto022);
	sp.Execute("Testo023", pOV, &pOV->m_sTesto023, pNV, &pNV->m_sTesto023);
	sp.Execute("Testo024", pOV, &pOV->m_sTesto024, pNV, &pNV->m_sTesto024);
	sp.Execute("Testo025", pOV, &pOV->m_sTesto025, pNV, &pNV->m_sTesto025);
	sp.Execute("Testo026", pOV, &pOV->m_sTesto026, pNV, &pNV->m_sTesto026);
	sp.Execute("Testo027", pOV, &pOV->m_sTesto027, pNV, &pNV->m_sTesto027);
	sp.Execute("Testo028", pOV, &pOV->m_sTesto028, pNV, &pNV->m_sTesto028);
	sp.Execute("Testo029", pOV, &pOV->m_sTesto029, pNV, &pNV->m_sTesto029);
	sp.Execute("Testo030", pOV, &pOV->m_sTesto030, pNV, &pNV->m_sTesto030);
	sp.Execute("Testo031", pOV, &pOV->m_sTesto031, pNV, &pNV->m_sTesto031);
	sp.Execute("Testo032", pOV, &pOV->m_sTesto032, pNV, &pNV->m_sTesto032);
	sp.Execute("Testo033", pOV, &pOV->m_sTesto033, pNV, &pNV->m_sTesto033);
	sp.Execute("Testo034", pOV, &pOV->m_sTesto034, pNV, &pNV->m_sTesto034);
	sp.Execute("Testo035", pOV, &pOV->m_sTesto035, pNV, &pNV->m_sTesto035);
	sp.Execute("Testo036", pOV, &pOV->m_sTesto036, pNV, &pNV->m_sTesto036);
	sp.Execute("Testo037", pOV, &pOV->m_sTesto037, pNV, &pNV->m_sTesto037);
	sp.Execute("Testo038", pOV, &pOV->m_sTesto038, pNV, &pNV->m_sTesto038);
	sp.Execute("Testo039", pOV, &pOV->m_sTesto039, pNV, &pNV->m_sTesto039);
	sp.Execute("Testo040", pOV, &pOV->m_sTesto040, pNV, &pNV->m_sTesto040);
	sp.Execute("Testo041", pOV, &pOV->m_sTesto041, pNV, &pNV->m_sTesto041);
	sp.Execute("Testo042", pOV, &pOV->m_sTesto042, pNV, &pNV->m_sTesto042);
	sp.Execute("Testo043", pOV, &pOV->m_sTesto043, pNV, &pNV->m_sTesto043);
	sp.Execute("Testo044", pOV, &pOV->m_sTesto044, pNV, &pNV->m_sTesto044);
	sp.Execute("Testo045", pOV, &pOV->m_sTesto045, pNV, &pNV->m_sTesto045);
	sp.Execute("Testo046", pOV, &pOV->m_sTesto046, pNV, &pNV->m_sTesto046);
	sp.Execute("Testo047", pOV, &pOV->m_sTesto047, pNV, &pNV->m_sTesto047);
	sp.Execute("Testo048", pOV, &pOV->m_sTesto048, pNV, &pNV->m_sTesto048);
	sp.Execute("Testo049", pOV, &pOV->m_sTesto049, pNV, &pNV->m_sTesto049);
	sp.Execute("Testo050", pOV, &pOV->m_sTesto050, pNV, &pNV->m_sTesto050);
	sp.Execute("Testo051", pOV, &pOV->m_sTesto051, pNV, &pNV->m_sTesto051);
	sp.Execute("Testo052", pOV, &pOV->m_sTesto052, pNV, &pNV->m_sTesto052);
	sp.Execute("Testo053", pOV, &pOV->m_sTesto053, pNV, &pNV->m_sTesto053);
	sp.Execute("Testo054", pOV, &pOV->m_sTesto054, pNV, &pNV->m_sTesto054);
	sp.Execute("Testo055", pOV, &pOV->m_sTesto055, pNV, &pNV->m_sTesto055);
	sp.Execute("Testo056", pOV, &pOV->m_sTesto056, pNV, &pNV->m_sTesto056);
	sp.Execute("Testo057", pOV, &pOV->m_sTesto057, pNV, &pNV->m_sTesto057);
	sp.Execute("Testo058", pOV, &pOV->m_sTesto058, pNV, &pNV->m_sTesto058);
	sp.Execute("Testo059", pOV, &pOV->m_sTesto059, pNV, &pNV->m_sTesto059);
	sp.Execute("Testo060", pOV, &pOV->m_sTesto060, pNV, &pNV->m_sTesto060);
	sp.Execute("Testo061", pOV, &pOV->m_sTesto061, pNV, &pNV->m_sTesto061);
	sp.Execute("Testo062", pOV, &pOV->m_sTesto062, pNV, &pNV->m_sTesto062);
	sp.Execute("Testo063", pOV, &pOV->m_sTesto063, pNV, &pNV->m_sTesto063);
	sp.Execute("Testo064", pOV, &pOV->m_sTesto064, pNV, &pNV->m_sTesto064);
	sp.Execute("Testo065", pOV, &pOV->m_sTesto065, pNV, &pNV->m_sTesto065);
	sp.Execute("Testo066", pOV, &pOV->m_sTesto066, pNV, &pNV->m_sTesto066);
	sp.Execute("Testo067", pOV, &pOV->m_sTesto067, pNV, &pNV->m_sTesto067);
	sp.Execute("Testo068", pOV, &pOV->m_sTesto068, pNV, &pNV->m_sTesto068);
	sp.Execute("Testo069", pOV, &pOV->m_sTesto069, pNV, &pNV->m_sTesto069);
	sp.Execute("Testo070", pOV, &pOV->m_sTesto070, pNV, &pNV->m_sTesto070);
	sp.Execute("Testo071", pOV, &pOV->m_sTesto071, pNV, &pNV->m_sTesto071);
	sp.Execute("Testo072", pOV, &pOV->m_sTesto072, pNV, &pNV->m_sTesto072);
	sp.Execute("Testo073", pOV, &pOV->m_sTesto073, pNV, &pNV->m_sTesto073);
	sp.Execute("Testo074", pOV, &pOV->m_sTesto074, pNV, &pNV->m_sTesto074);
	sp.Execute("Testo075", pOV, &pOV->m_sTesto075, pNV, &pNV->m_sTesto075);
	sp.Execute("Testo076", pOV, &pOV->m_sTesto076, pNV, &pNV->m_sTesto076);
	sp.Execute("Testo077", pOV, &pOV->m_sTesto077, pNV, &pNV->m_sTesto077);
	sp.Execute("Testo078", pOV, &pOV->m_sTesto078, pNV, &pNV->m_sTesto078);
	sp.Execute("Testo079", pOV, &pOV->m_sTesto079, pNV, &pNV->m_sTesto079);
	sp.Execute("Testo080", pOV, &pOV->m_sTesto080, pNV, &pNV->m_sTesto080);
	sp.Execute("Testo081", pOV, &pOV->m_sTesto081, pNV, &pNV->m_sTesto081);
	sp.Execute("Testo082", pOV, &pOV->m_sTesto082, pNV, &pNV->m_sTesto082);
	sp.Execute("Testo083", pOV, &pOV->m_sTesto083, pNV, &pNV->m_sTesto083);
	sp.Execute("Testo084", pOV, &pOV->m_sTesto084, pNV, &pNV->m_sTesto084);
	sp.Execute("Testo085", pOV, &pOV->m_sTesto085, pNV, &pNV->m_sTesto085);
	sp.Execute("Testo086", pOV, &pOV->m_sTesto086, pNV, &pNV->m_sTesto086);
	sp.Execute("Testo087", pOV, &pOV->m_sTesto087, pNV, &pNV->m_sTesto087);
	sp.Execute("Testo088", pOV, &pOV->m_sTesto088, pNV, &pNV->m_sTesto088);
	sp.Execute("Testo089", pOV, &pOV->m_sTesto089, pNV, &pNV->m_sTesto089);
	sp.Execute("Testo090", pOV, &pOV->m_sTesto090, pNV, &pNV->m_sTesto090);
	sp.Execute("Testo091", pOV, &pOV->m_sTesto091, pNV, &pNV->m_sTesto091);
	sp.Execute("Testo092", pOV, &pOV->m_sTesto092, pNV, &pNV->m_sTesto092);
	sp.Execute("Testo093", pOV, &pOV->m_sTesto093, pNV, &pNV->m_sTesto093);
	sp.Execute("Testo094", pOV, &pOV->m_sTesto094, pNV, &pNV->m_sTesto094);
	sp.Execute("Testo095", pOV, &pOV->m_sTesto095, pNV, &pNV->m_sTesto095);
	sp.Execute("Testo096", pOV, &pOV->m_sTesto096, pNV, &pNV->m_sTesto096);
	sp.Execute("Testo097", pOV, &pOV->m_sTesto097, pNV, &pNV->m_sTesto097);
	sp.Execute("Testo098", pOV, &pOV->m_sTesto098, pNV, &pNV->m_sTesto098);
	sp.Execute("Testo099", pOV, &pOV->m_sTesto099, pNV, &pNV->m_sTesto099);

	sp.Execute("TestoRtf000", pOV, &pOV->m_sTestoRtf000, pNV, &pNV->m_sTestoRtf000);
	sp.Execute("TestoTxt000", pOV, &pOV->m_sTestoTxt000, pNV, &pNV->m_sTestoTxt000);
	sp.Execute("TestoRtf001", pOV, &pOV->m_sTestoRtf001, pNV, &pNV->m_sTestoRtf001);
	sp.Execute("TestoTxt001", pOV, &pOV->m_sTestoTxt001, pNV, &pNV->m_sTestoTxt001);
	sp.Execute("TestoRtf002", pOV, &pOV->m_sTestoRtf002, pNV, &pNV->m_sTestoRtf002);
	sp.Execute("TestoTxt002", pOV, &pOV->m_sTestoTxt002, pNV, &pNV->m_sTestoTxt002);
	sp.Execute("TestoRtf003", pOV, &pOV->m_sTestoRtf003, pNV, &pNV->m_sTestoRtf003);
	sp.Execute("TestoTxt003", pOV, &pOV->m_sTestoTxt003, pNV, &pNV->m_sTestoTxt003);
	sp.Execute("TestoRtf004", pOV, &pOV->m_sTestoRtf004, pNV, &pNV->m_sTestoRtf004);
	sp.Execute("TestoTxt004", pOV, &pOV->m_sTestoTxt004, pNV, &pNV->m_sTestoTxt004);
	sp.Execute("TestoRtf005", pOV, &pOV->m_sTestoRtf005, pNV, &pNV->m_sTestoRtf005);
	sp.Execute("TestoTxt005", pOV, &pOV->m_sTestoTxt005, pNV, &pNV->m_sTestoTxt005);
	sp.Execute("TestoRtf006", pOV, &pOV->m_sTestoRtf006, pNV, &pNV->m_sTestoRtf006);
	sp.Execute("TestoTxt006", pOV, &pOV->m_sTestoTxt006, pNV, &pNV->m_sTestoTxt006);
	sp.Execute("TestoRtf007", pOV, &pOV->m_sTestoRtf007, pNV, &pNV->m_sTestoRtf007);
	sp.Execute("TestoTxt007", pOV, &pOV->m_sTestoTxt007, pNV, &pNV->m_sTestoTxt007);
	sp.Execute("TestoRtf008", pOV, &pOV->m_sTestoRtf008, pNV, &pNV->m_sTestoRtf008);
	sp.Execute("TestoTxt008", pOV, &pOV->m_sTestoTxt008, pNV, &pNV->m_sTestoTxt008);
	sp.Execute("TestoRtf009", pOV, &pOV->m_sTestoRtf009, pNV, &pNV->m_sTestoRtf009);
	sp.Execute("TestoTxt009", pOV, &pOV->m_sTestoTxt009, pNV, &pNV->m_sTestoTxt009);
	sp.Execute("TestoRtf010", pOV, &pOV->m_sTestoRtf010, pNV, &pNV->m_sTestoRtf010);
	sp.Execute("TestoTxt010", pOV, &pOV->m_sTestoTxt010, pNV, &pNV->m_sTestoTxt010);
	sp.Execute("TestoRtf011", pOV, &pOV->m_sTestoRtf011, pNV, &pNV->m_sTestoRtf011);
	sp.Execute("TestoTxt011", pOV, &pOV->m_sTestoTxt011, pNV, &pNV->m_sTestoTxt011);
	sp.Execute("TestoRtf012", pOV, &pOV->m_sTestoRtf012, pNV, &pNV->m_sTestoRtf012);
	sp.Execute("TestoTxt012", pOV, &pOV->m_sTestoTxt012, pNV, &pNV->m_sTestoTxt012);
	sp.Execute("TestoRtf013", pOV, &pOV->m_sTestoRtf013, pNV, &pNV->m_sTestoRtf013);
	sp.Execute("TestoTxt013", pOV, &pOV->m_sTestoTxt013, pNV, &pNV->m_sTestoTxt013);
	sp.Execute("TestoRtf014", pOV, &pOV->m_sTestoRtf014, pNV, &pNV->m_sTestoRtf014);
	sp.Execute("TestoTxt014", pOV, &pOV->m_sTestoTxt014, pNV, &pNV->m_sTestoTxt014);
	sp.Execute("TestoRtf015", pOV, &pOV->m_sTestoRtf015, pNV, &pNV->m_sTestoRtf015);
	sp.Execute("TestoTxt015", pOV, &pOV->m_sTestoTxt015, pNV, &pNV->m_sTestoTxt015);
	sp.Execute("TestoRtf016", pOV, &pOV->m_sTestoRtf016, pNV, &pNV->m_sTestoRtf016);
	sp.Execute("TestoTxt016", pOV, &pOV->m_sTestoTxt016, pNV, &pNV->m_sTestoTxt016);
	sp.Execute("TestoRtf017", pOV, &pOV->m_sTestoRtf017, pNV, &pNV->m_sTestoRtf017);
	sp.Execute("TestoTxt017", pOV, &pOV->m_sTestoTxt017, pNV, &pNV->m_sTestoTxt017);
	sp.Execute("TestoRtf018", pOV, &pOV->m_sTestoRtf018, pNV, &pNV->m_sTestoRtf018);
	sp.Execute("TestoTxt018", pOV, &pOV->m_sTestoTxt018, pNV, &pNV->m_sTestoTxt018);
	sp.Execute("TestoRtf019", pOV, &pOV->m_sTestoRtf019, pNV, &pNV->m_sTestoRtf019);
	sp.Execute("TestoTxt019", pOV, &pOV->m_sTestoTxt019, pNV, &pNV->m_sTestoTxt019);

	sp.Execute("TestoCLRtf000", pOV, &pOV->m_sTestoCLRtf000, pNV, &pNV->m_sTestoCLRtf000);
	sp.Execute("TestoCLTxt000", pOV, &pOV->m_sTestoCLTxt000, pNV, &pNV->m_sTestoCLTxt000);
	sp.Execute("TestoCLRtf001", pOV, &pOV->m_sTestoCLRtf001, pNV, &pNV->m_sTestoCLRtf001);
	sp.Execute("TestoCLTxt001", pOV, &pOV->m_sTestoCLTxt001, pNV, &pNV->m_sTestoCLTxt001);
	sp.Execute("TestoCLRtf002", pOV, &pOV->m_sTestoCLRtf002, pNV, &pNV->m_sTestoCLRtf002);
	sp.Execute("TestoCLTxt002", pOV, &pOV->m_sTestoCLTxt002, pNV, &pNV->m_sTestoCLTxt002);
	sp.Execute("TestoCLRtf003", pOV, &pOV->m_sTestoCLRtf003, pNV, &pNV->m_sTestoCLRtf003);
	sp.Execute("TestoCLTxt003", pOV, &pOV->m_sTestoCLTxt003, pNV, &pNV->m_sTestoCLTxt003);
	sp.Execute("TestoCLRtf004", pOV, &pOV->m_sTestoCLRtf004, pNV, &pNV->m_sTestoCLRtf004);
	sp.Execute("TestoCLTxt004", pOV, &pOV->m_sTestoCLTxt004, pNV, &pNV->m_sTestoCLTxt004);
	sp.Execute("TestoCLRtf005", pOV, &pOV->m_sTestoCLRtf005, pNV, &pNV->m_sTestoCLRtf005);
	sp.Execute("TestoCLTxt005", pOV, &pOV->m_sTestoCLTxt005, pNV, &pNV->m_sTestoCLTxt005);
	sp.Execute("TestoCLRtf006", pOV, &pOV->m_sTestoCLRtf006, pNV, &pNV->m_sTestoCLRtf006);
	sp.Execute("TestoCLTxt006", pOV, &pOV->m_sTestoCLTxt006, pNV, &pNV->m_sTestoCLTxt006);
	sp.Execute("TestoCLRtf007", pOV, &pOV->m_sTestoCLRtf007, pNV, &pNV->m_sTestoCLRtf007);
	sp.Execute("TestoCLTxt007", pOV, &pOV->m_sTestoCLTxt007, pNV, &pNV->m_sTestoCLTxt007);
	sp.Execute("TestoCLRtf008", pOV, &pOV->m_sTestoCLRtf008, pNV, &pNV->m_sTestoCLRtf008);
	sp.Execute("TestoCLTxt008", pOV, &pOV->m_sTestoCLTxt008, pNV, &pNV->m_sTestoCLTxt008);
	sp.Execute("TestoCLRtf009", pOV, &pOV->m_sTestoCLRtf009, pNV, &pNV->m_sTestoCLRtf009);
	sp.Execute("TestoCLTxt009", pOV, &pOV->m_sTestoCLTxt009, pNV, &pNV->m_sTestoCLTxt009);
	sp.Execute("TestoCLRtf010", pOV, &pOV->m_sTestoCLRtf010, pNV, &pNV->m_sTestoCLRtf010);
	sp.Execute("TestoCLTxt010", pOV, &pOV->m_sTestoCLTxt010, pNV, &pNV->m_sTestoCLTxt010);
	sp.Execute("TestoCLRtf011", pOV, &pOV->m_sTestoCLRtf011, pNV, &pNV->m_sTestoCLRtf011);
	sp.Execute("TestoCLTxt011", pOV, &pOV->m_sTestoCLTxt011, pNV, &pNV->m_sTestoCLTxt011);
	sp.Execute("TestoCLRtf012", pOV, &pOV->m_sTestoCLRtf012, pNV, &pNV->m_sTestoCLRtf012);
	sp.Execute("TestoCLTxt012", pOV, &pOV->m_sTestoCLTxt012, pNV, &pNV->m_sTestoCLTxt012);
	sp.Execute("TestoCLRtf013", pOV, &pOV->m_sTestoCLRtf013, pNV, &pNV->m_sTestoCLRtf013);
	sp.Execute("TestoCLTxt013", pOV, &pOV->m_sTestoCLTxt013, pNV, &pNV->m_sTestoCLTxt013);
	sp.Execute("TestoCLRtf014", pOV, &pOV->m_sTestoCLRtf014, pNV, &pNV->m_sTestoCLRtf014);
	sp.Execute("TestoCLTxt014", pOV, &pOV->m_sTestoCLTxt014, pNV, &pNV->m_sTestoCLTxt014);
	sp.Execute("TestoCLRtf015", pOV, &pOV->m_sTestoCLRtf015, pNV, &pNV->m_sTestoCLRtf015);
	sp.Execute("TestoCLTxt015", pOV, &pOV->m_sTestoCLTxt015, pNV, &pNV->m_sTestoCLTxt015);
	sp.Execute("TestoCLRtf016", pOV, &pOV->m_sTestoCLRtf016, pNV, &pNV->m_sTestoCLRtf016);
	sp.Execute("TestoCLTxt016", pOV, &pOV->m_sTestoCLTxt016, pNV, &pNV->m_sTestoCLTxt016);
	sp.Execute("TestoCLRtf017", pOV, &pOV->m_sTestoCLRtf017, pNV, &pNV->m_sTestoCLRtf017);
	sp.Execute("TestoCLTxt017", pOV, &pOV->m_sTestoCLTxt017, pNV, &pNV->m_sTestoCLTxt017);
	sp.Execute("TestoCLRtf018", pOV, &pOV->m_sTestoCLRtf018, pNV, &pNV->m_sTestoCLRtf018);
	sp.Execute("TestoCLTxt018", pOV, &pOV->m_sTestoCLTxt018, pNV, &pNV->m_sTestoCLTxt018);
	sp.Execute("TestoCLRtf019", pOV, &pOV->m_sTestoCLRtf019, pNV, &pNV->m_sTestoCLRtf019);
	sp.Execute("TestoCLTxt019", pOV, &pOV->m_sTestoCLTxt019, pNV, &pNV->m_sTestoCLTxt019);

	sp.Execute("DataOra000", pOV, &pOV->m_lDataOra000, pNV, &pNV->m_lDataOra000);
	sp.Execute("DataOra001", pOV, &pOV->m_lDataOra001, pNV, &pNV->m_lDataOra001);
	sp.Execute("DataOra002", pOV, &pOV->m_lDataOra002, pNV, &pNV->m_lDataOra002);
	sp.Execute("DataOra003", pOV, &pOV->m_lDataOra003, pNV, &pNV->m_lDataOra003);
	sp.Execute("DataOra004", pOV, &pOV->m_lDataOra004, pNV, &pNV->m_lDataOra004);
	sp.Execute("DataOra005", pOV, &pOV->m_lDataOra005, pNV, &pNV->m_lDataOra005);
	sp.Execute("DataOra006", pOV, &pOV->m_lDataOra006, pNV, &pNV->m_lDataOra006);
	sp.Execute("DataOra007", pOV, &pOV->m_lDataOra007, pNV, &pNV->m_lDataOra007);
	sp.Execute("DataOra008", pOV, &pOV->m_lDataOra008, pNV, &pNV->m_lDataOra008);
	sp.Execute("DataOra009", pOV, &pOV->m_lDataOra009, pNV, &pNV->m_lDataOra009);
	sp.Execute("DataOra010", pOV, &pOV->m_lDataOra010, pNV, &pNV->m_lDataOra010);
	sp.Execute("DataOra011", pOV, &pOV->m_lDataOra011, pNV, &pNV->m_lDataOra011);
	sp.Execute("DataOra012", pOV, &pOV->m_lDataOra012, pNV, &pNV->m_lDataOra012);
	sp.Execute("DataOra013", pOV, &pOV->m_lDataOra013, pNV, &pNV->m_lDataOra013);
	sp.Execute("DataOra014", pOV, &pOV->m_lDataOra014, pNV, &pNV->m_lDataOra014);
	sp.Execute("DataOra015", pOV, &pOV->m_lDataOra015, pNV, &pNV->m_lDataOra015);
	sp.Execute("DataOra016", pOV, &pOV->m_lDataOra016, pNV, &pNV->m_lDataOra016);
	sp.Execute("DataOra017", pOV, &pOV->m_lDataOra017, pNV, &pNV->m_lDataOra017);
	sp.Execute("DataOra018", pOV, &pOV->m_lDataOra018, pNV, &pNV->m_lDataOra018);
	sp.Execute("DataOra019", pOV, &pOV->m_lDataOra019, pNV, &pNV->m_lDataOra019);
}