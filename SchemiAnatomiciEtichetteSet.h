// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury

#ifndef _SchemiAnatomiciEtichetteSet_H_

#define _SchemiAnatomiciEtichetteSet_H_

#include "BaseSet.h"
#include "SchemiAnatomiciEtichette.h"

/*
	USE[TESICAPTURE]
	GO
	SET ANSI_NULLS ON
	GO
	SET QUOTED_IDENTIFIER ON
	GO
	CREATE TABLE[dbo].[SCHEMI_ANATOMICI_ETICHETTE](
	[ID][int] NOT NULL,
	[ID_SCHEMI_ANATOMICI][int] NULL,
	[DESCRIZIONE][varchar](5) NULL,
	[PUNTO_ALTO_SINISTRA_X][int] NULL,
	[PUNTO_ALTO_SINISTRA_Y][int] NULL,
	[PUNTO_BASSO_DESTRA_X][int] NULL,
	[PUNTO_BASSO_DESTRA_Y][int] NULL,
	[ZOOM_FACTOR][float] NULL,
	[ELIMINATO][bit] NULL,
	CONSTRAINT[PK_SCHEMI_ANATOMICI_ETICHETTE] PRIMARY KEY CLUSTERED
	(
	[ID] ASC
	)WITH(PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON[PRIMARY]
	) ON[PRIMARY]
	GO
	ALTER TABLE[dbo].[SCHEMI_ANATOMICI_ETICHETTE] ADD  CONSTRAINT[DF_SCHEMI_ANATOMICI_ETICHETTE_ELIMINATO]  DEFAULT((0)) FOR[ELIMINATO]
	GO
	EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'da label', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI_ETICHETTE', @level2type = N'COLUMN', @level2name = N'ID'
	GO
	EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'id do pai', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI_ETICHETTE', @level2type = N'COLUMN', @level2name = N'ID_SCHEMI_ANATOMICI'
	GO
	EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'descrição suscinta da label', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI_ETICHETTE', @level2type = N'COLUMN', @level2name = N'DESCRIZIONE'
	GO
	EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'x do ponto do canto superior esquerdo', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI_ETICHETTE', @level2type = N'COLUMN', @level2name = N'PUNTO_ALTO_SINISTRA_X'
	GO
	EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'y do ponto do canto superior esquerdo', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI_ETICHETTE', @level2type = N'COLUMN', @level2name = N'PUNTO_ALTO_SINISTRA_Y'
	GO
	EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'x do ponto do canto inferior direito', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI_ETICHETTE', @level2type = N'COLUMN', @level2name = N'PUNTO_BASSO_DESTRA_X'
	GO
	EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'y do ponto do canto inferior direito', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI_ETICHETTE', @level2type = N'COLUMN', @level2name = N'PUNTO_BASSO_DESTRA_Y'
	GO
	EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'proporção de zoom usada no cadastramento. necessário para os pontos dos labels (ver na table schemi_anatomici) veja também no projeto em CDib::PaintDIB(CDC* dcp, CRect rectDest) ', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI_ETICHETTE', @level2type = N'COLUMN', @level2name = N'ZOOM_FACTOR'
	GO
	EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'bool deleted or not', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI_ETICHETTE', @level2type = N'COLUMN', @level2name = N'ELIMINATO'
	GO
*/
class CSchemiAnatomiciEtichetteSet : public CBaseSet
{
	DECLARE_DYNAMIC(CSchemiAnatomiciEtichetteSet)

public:

	CSchemiAnatomiciEtichetteSet();

	long m_lID; // da label - PK da tabela schemi_anatomici_etichette
	long m_lID_Schemi_Anatomici; // FK: ID na tabela Schemi_Anatomici
	CString	m_sDescrizione; // descrição suscinta da label
	long m_lPunto_Alto_Sinistra_X; // x do ponto superior esquerdo do retangulo
	long m_lPunto_Alto_Sinistra_Y; // y do ponto superior esquerdo do retangulo
	long m_lPunto_Basso_Destra_X; // x do ponto inferior direito do retangulo
	long m_lPunto_Basso_Destra_Y; // y do ponto inferior direito do retangulo
	long m_lColore;
	double m_dZoom_Factor;
	BOOL m_bEliminato; // bool deleted or not na tabela schemi_anatomici_etichette
	
	CSchemiAnatomiciEtichette m_pSchemiAnatomiciEtichette;

	//CSchemiAnatomiciEtichette getObjSchemiAnatomiciEtichette(long	p_lID);

	BOOL Find(long lID);
	BOOL FindByFatherID(long p_lID_Schemi_Anatomici);

	BOOL SoftRefreshData(CSchemiAnatomiciEtichette* p_pSchemiAnatomiciEtichette);

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

#endif /* _SchemiAnatomiciEtichetteSet_H_ */