#pragma once

class CWriteLogLineSet : protected CAMBaseSet
{
	DECLARE_DYNAMIC(CWriteLogLineSet)

public:
	CWriteLogLineSet(LPCTSTR szTabella, LPCTSTR szNomeChiave, const long lValoreChiave, const CString &sCommento);
	~CWriteLogLineSet();

	void Execute(const CString &sCampo, CRecordset* pSetOld, double* pValoreOld, CRecordset* pSetNew, double* pValoreNew);
	void Execute(const CString &sCampo, CRecordset* pSetOld, float* pValoreOld, CRecordset* pSetNew, float* pValoreNew);
	void Execute(const CString &sCampo, CRecordset* pSetOld, int* pValoreOld, CRecordset* pSetNew, int* pValoreNew);
	void Execute(const CString &sCampo, CRecordset* pSetOld, long* pValoreOld, CRecordset* pSetNew, long* pValoreNew);
	void Execute(const CString &sCampo, CRecordset* pSetOld, CString* pValoreOld, CRecordset* pSetNew, CString* pValoreNew);

	void Execute();

protected:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	enum Operations
	{
		op_addnew = 1,
		op_edit = 2
	};

	long    m_lID;
	long	m_lIDPaziente;
	long	m_lIDEsame;
	CString m_sData;
	CString m_sUtente;
	CString m_sStazione;
	CString m_sImpianto;
	CString m_sTabella;
	long    m_lOperazione;
	CString m_sNomeChiave;
	long	m_lValoreChiave;
	CString m_sCampo;
	CString m_sValoreOld;
	CString m_sValoreNew;
	CString m_sCommento;

private:

	void Execute(const long lOperazione, const CString &sCampo, const CString &sValoreOld, const CString &sValoreNew);

	CString m_sSavedTabella;
	CString m_sSavedNomeChiave;
	long m_lSavedValoreChiave;
	CString m_sSavedCommento;
	CString m_strDataSaved;

	CString m_sDataSaved;

};