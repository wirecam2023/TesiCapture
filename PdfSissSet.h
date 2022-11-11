#pragma once

class CPdfSissSet : public CAMBaseSet
{

	DECLARE_DYNAMIC(CPdfSissSet)

public:

	CPdfSissSet(CDatabase* pDatabase);

	long m_lIDPdf;
	CString m_sCognomeMedico;
	CString m_sNomeMedico;
	CString m_sCodiceFiscaleMedico;
	CString m_sAutorizzazione;
	CString m_sAutorizzazioneFormato;
	CString m_sAutorizzazioneFirmato;
	CString m_sAutorizzazioneVersione;
	CString m_sDocumento;
	CString m_sDocumentoFormato;
	CString m_sDocumentoFirmato;
	CString m_sDocumentoMarcato;
	CString m_sHashDocumento;
	CString m_sAlgoritmoHash;
	CString m_sDataOraDocumento;
	BOOL m_bAnnullativo;
	long m_lSizeDocumento;
	long m_lTentativi;
	CString m_sErrore;
	BOOL m_bProcessato;

protected:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

};