#pragma once

class CPdfDatiAggiuntiviSet : public CAMBaseSet
{

	DECLARE_DYNAMIC(CPdfDatiAggiuntiviSet)

public:

	CPdfDatiAggiuntiviSet(CDatabase* pDatabase);

	long m_lIDPdf;	
	CString m_sRappresentazioneXml;	
	CString m_sB64MimeFirmato;

protected:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

};