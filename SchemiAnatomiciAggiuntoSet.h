// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury

#ifndef _SCHEMIANATOMICIAGGIUNTOSET_H_

#define _SCHEMIANATOMICIAGGIUNTOSET_H_

#include "BaseSet.h"

/*
	USE[TESICAPTURE]
	GO
	SET ANSI_NULLS ON
	GO
	SET QUOTED_IDENTIFIER ON
	GO
	CREATE TABLE[dbo].[SCHEMI_ANATOMICI_AGGIUNTO](

	[CONTATORE][int] NOT NULL,
	[CONTATORE_EESAMI][int] NULL,
	[ID_SCHEMI_ANATOMICI][int] NULL,
	[DESCRIZIONE][varchar](50) NULL,
	[STATO][int] NULL,
	[ELIMINATO][bit] NULL,

	CONSTRAINT[PK_SCHEMI_ANATOMICI_AGGIUNTO] PRIMARY KEY CLUSTERED
	(
	[CONTATORE] ASC
	)WITH(PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON[PRIMARY]
	) ON[PRIMARY]
	GO
	ALTER TABLE[dbo].[SCHEMI_ANATOMICI_AGGIUNTO] ADD  CONSTRAINT[DF_SCHEMI_ANATOMICI_AGGIUNTO_ELIMINATO]  DEFAULT((0)) FOR[ELIMINATO]
	GO
*/
class CSchemiAnatomiciAggiuntoSet : public CBaseSet
{
	DECLARE_DYNAMIC(CSchemiAnatomiciAggiuntoSet)

public:

	CSchemiAnatomiciAggiuntoSet();

	long	m_lCONTATORE;
	long	m_lCONTATORE_EESAMI;
	long	m_lID_SCHEMI_ANATOMICI;
	CString	m_sDESCRIZIONE;
	long	m_lSTATO;
	BOOL	m_bEliminato;

	BOOL Find(long p_lCONTATORE);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);
	virtual void SetEmpty();

private:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _SCHEMIANATOMICIAGGIUNTOSET_H_ */