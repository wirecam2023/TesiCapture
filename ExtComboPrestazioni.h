#include "BaseSet.h"

// Luiz - 12/08/2019 - P4 - Permite envio de exames MAMOGUS de acordo com opção do usuário
class CExtComboPrestazioni : public CBaseSet
{
	DECLARE_DYNAMIC(CExtComboPrestazioni)

public:
	enum Tipo {		
		StatusChange = 0,
		Report = 1
	};

	CExtComboPrestazioni();

	long m_lID;
	long m_lIDEsame;
	long m_lIDEsameChiuso;
	CString m_sTipo; //Julio - BUG 3365 - MAMOGUS
	CString m_sDataOra;
	long m_lIDUtente;
	long m_lEseguito;
	CString m_sEsito;

	long Insert(long lIDEsame, Tipo eTipo, long lIDEsameChiuso = 0); //Julio - BUG 3365 - MAMOGUS
	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter); 
	
private:

	CString GetTipoAsString(Tipo eTipo);  //Julio - BUG 3365 - MAMOGUS

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();
	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};