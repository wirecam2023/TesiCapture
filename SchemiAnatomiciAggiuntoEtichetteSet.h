// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury

#ifndef _SCHEMIANATOMICIAGGIUNTOETICHETTESET_H_

#define _SCHEMIANATOMICIAGGIUNTOETICHETTESET_H_

#include "BaseSet.h"

/*
	USE [TESICAPTURE]
	GO
	SET ANSI_NULLS ON
	GO
	SET QUOTED_IDENTIFIER ON
	GO

	CREATE TABLE[dbo].[SCHEMI_ANATOMICI_AGGIUNTO_ETICHETTE](
	[CONTATORE][int] NOT NULL,
	[ID_SCHEMI_ANATOMICI][int] NULL,
	[ID_SCHEMI_ANATOMICI_ETICHETTE][int] NULL,
	[DESCRIZIONE] [varchar](5) NULL,
	[PUNTO_ALTO_SINISTRA_X] [int] NULL,
	[PUNTO_ALTO_SINISTRA_Y] [int] NULL,
	[PUNTO_BASSO_DESTRA_X] [int] NULL,
	[PUNTO_BASSO_DESTRA_Y] [int] NULL,
	[ELIMINATO] [bit] NULL,
	CONSTRAINT[PK_SCHEMI_ANATOMICI_AGGIUNTO_ETICHETTE] PRIMARY KEY CLUSTERED
	(
	[CONTATORE] ASC
	)WITH(PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON[PRIMARY]
	) ON[PRIMARY]
	GO

	ALTER TABLE[dbo].[SCHEMI_ANATOMICI_AGGIUNTO_ETICHETTE] ADD  CONSTRAINT[DF_SCHEMI_ANATOMICI_AGGIUNTO_ETICHETTE_ELIMINATO]  DEFAULT((0)) FOR[ELIMINATO]
	GO
*/
class CSchemiAnatomiciAggiuntoEtichetteSet : public CBaseSet
{
	DECLARE_DYNAMIC(CSchemiAnatomiciAggiuntoEtichetteSet)

public:

	CSchemiAnatomiciAggiuntoEtichetteSet();

	long m_lCONTATORE;
	long m_lID_SCHEMI_ANATOMICI_AGGIUNTO;
	long m_lID_SCHEMI_ANATOMICI_ETICHETTE;
	CString m_sDESCRIZIONE;
	long m_lPUNTO_ALTO_SINISTRA_X; // x do ponto superior esquerdo do retangulo
	long m_lPUNTO_ALTO_SINISTRA_Y; // y do ponto superior esquerdo do retangulo
	long m_lPUNTO_BASSO_DESTRA_X; // x do ponto inferior direito do retangulo
	long m_lPUNTO_BASSO_DESTRA_Y; // y do ponto inferior direito do retangulo
	long m_lCOLORE;
	BOOL m_bELIMINATO;

	BOOL Find(long lID);
	BOOL FindByFatherID(long p_lID_Schemi_Anatomici);

	//BOOL SoftRefreshData(CSchemiAnatomiciEtichette* p_pSchemiAnatomiciEtichette);

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

#endif /* _SCHEMIANATOMICIAGGIUNTOETICHETTESET_H_ */