#ifndef _SUBFORM_H_
	#define _SUBFORM_H_

#include "CodificaDiagnosiEsameSet.h"
#include "DiagnosiEsamiSet.h"
#include "DiagnosiFinaliEsamiSet.h"
#include "DiagnosiICD9Set.h"
#include "DiagnosiSet.h"
#include "EndoxDynForm.h"
#include "EsamiAccessoriSet.h"
#include "EsamiPregressiSet.h"
#include "FamiliaritaSet.h"
#include "IndaginiPregresseSet.h"
#include "InterventiChirurgiciSet.h"
#include "InterventiEndoscopiciSet.h"
#include "IstologiaSet.h"
#include "MalattieSet.h"
#include "OsservazioniSet.h"
#include "ProcedureEsamiSet.h"
#include "ProcedureICD9Set.h"
#include "RegioneSet.h"
#include "TerapieSet.h"

typedef struct Terapia
{  
	int				m_nStato;
	long			m_nContatore;
	CTerapieSet		m_Set;
} STRUCT_TERAPIA;

typedef struct Diagnosi
{  
	int				m_nStato;
	long			m_nContatore;
	CDiagnosiSet m_Set;
} STRUCT_DIAGNOSI;

typedef struct Osservazioni
{  
	int m_nStato;
	long m_nContatore;
	COsservazioniSet m_Set;
} STRUCT_OSSERVAZIONI;

typedef struct Istologia
{  
	int				m_nStato;
	long			m_nContatore;
	CIstologiaSet	m_Set;
} STRUCT_ISTOLOGIA;

typedef struct IChirurgico
{  
	int							m_nStato;
	long						m_nContatore;
	CInterventiChirurgiciSet	m_Set;

} STRUCT_ICHIRURGICO;

typedef struct IEndoscopico
{  
	int							m_nStato;
	long						m_nContatore;
	CInterventiEndoscopiciSet	m_Set;
} STRUCT_IENDOSCOPICO;

typedef struct Indagini
{  
	int							m_nStato;
	long						m_nContatore;
	CIndaginiPregresseSet		m_Set;
} STRUCT_INDAGINI;

typedef struct Malattie
{  
	int				m_nStato;
	long			m_nContatore;
	CMalattieSet	m_Set;
} STRUCT_MALATTIE;

typedef struct Familiarita
{  
	int				m_nStato;
	long			m_nContatore;
	CFamiliaritaSet	m_Set;
} STRUCT_FAMILIARITA;

typedef struct Regione
{  
	int				m_nStato;
	long			m_nContatore;
	CRegioneSet	m_Set;
} STRUCT_REGIONE;

typedef struct ProcedureICD9
{  
	int m_nStato;
	long m_lID;
	CProcedureEsamiSet m_Set;
} STRUCT_PROCEDUREICD9;

typedef struct DiagnosiICD9
{  
	int m_nStato;
	long m_lID;
	CDiagnosiEsamiSet m_Set;
} STRUCT_DIAGNOSIICD9;

typedef struct DiagnosiFinaliICD9
{
	int m_nStato;
	long m_lID;
	CDiagnosiFinaliEsamiSet m_Set;
} STRUCT_DIAGNOSIFINALIICD9;

typedef struct CodificaDiagnosiEsame
{  
	int				m_nStato;
	long			m_nContatore;
	CCodificaDiagnosiEsameSet m_Set;
} STRUCT_CODIFICADIAGNOSIESAME;

typedef struct EsamiPregressi
{  
	int					m_nStato;
	long				m_lContatore;
	CEsamiPregressiSet	m_Set;
} STRUCT_ESAMIPREGRESSI;

typedef struct EsitiEsami
{  
	int					m_nStato;
	long				m_lContatore;

	CString				m_sCodice;
	CString				m_sDescrizione;
	CString 			m_sEsito;
} STRUCT_ESITIESAMI;

typedef struct Accessori
{  
	int				m_nStato;
	long			m_nContatore;
	CEsamiAccessoriSet	m_Set;
} STRUCT_ACCESSORI;

#define MAX_OBJ_X_FORM	50

#define RECORD_EMPTY	0
#define RECORD_FULL		1
#define RECORD_DIRTY	2

class CEsamiView;

class CSubForm : public CEndoxDynForm
{

public:

	CSubForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);

	CScrollBar m_ctrlScroll;

	BOOL CreateChildForm(UINT nID, CWnd* pParent, CRect rectFrame);

	virtual void SaveForm(long* pParamOfFilter, CBaseSet* pSet, long* pCounterSet, long* pParamSet, CString sKeyFieldName="CONTATORE");

	virtual long GetCounterSetOfLine(int nCounter) = 0;
	virtual BOOL IsLineDirty(int nCounter) = 0;
	virtual BOOL IsValidSet(int nCounter) = 0;
	virtual void ModificaForm() = 0;
	virtual void SetLineDirty(int nCounter, BOOL bSetDirty) = 0;
	virtual void UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet) = 0;

	void GoToFirst();

protected:

	void DoDataExchange(CDataExchange* pDX);
	BOOL OnInitDialog();

	virtual void UpgradeForm();

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	int				m_nIndexLine;
	int				m_nIndexPage;

	DECLARE_MESSAGE_MAP()

};

#endif /* _SUBFORM_H_ */