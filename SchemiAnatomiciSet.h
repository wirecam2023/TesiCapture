// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury

#ifndef _SchemiAnatomiciSet_H_

#define _SchemiAnatomiciSet_H_

#include "BaseSet.h"
#include "SchemiAnatomici.h"

class CSchemiAnatomiciSet : public CBaseSet
{
	DECLARE_DYNAMIC(CSchemiAnatomiciSet)

public:

	CSchemiAnatomiciSet();

	//USE[TESICAPTURE]
	//GO
	//SET ANSI_NULLS ON
	//GO
	//SET QUOTED_IDENTIFIER ON
	//GO
	//CREATE TABLE[dbo].[SCHEMI_ANATOMICI](
	//[ID][int] NOT NULL,
	//[DESCRIZIONE][varchar](50) NULL,
	//[UO][int] NULL,
	//[CODICEPRESTAZIONEPREVISTA][varchar](50) NULL,
	//[IMMAGINE_FULLPATH][varchar](255) NULL,
	//[IMMAGINE_LARGHEZZA][int] NULL,
	//[IMMAGINE_ALTEZZA][int] NULL,
	//[ZOOM_FACTOR][float] NULL,
	//[ELIMINATO][bit] NULL,
	//CONSTRAINT[PK_SCHEMI_ANATOMICI] PRIMARY KEY CLUSTERED
	//(
	//[ID] ASC
	//)WITH(PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON[PRIMARY]
	//) ON[PRIMARY]
	//GO
	//ALTER TABLE[dbo].[SCHEMI_ANATOMICI] ADD  CONSTRAINT[DF_SCHEMI_ANATOMICI_ELIMINATO]  DEFAULT((0)) FOR[ELIMINATO]
	//GO
	//EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'(do esquema)', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI', @level2type = N'COLUMN', @level2name = N'ID'
	//GO
	//EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'(do esquema)', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI', @level2type = N'COLUMN', @level2name = N'DESCRIZIONE'
	//GO
	//EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'(id da UO)', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI', @level2type = N'COLUMN', @level2name = N'UO'
	//GO
	//EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'(CODICEPRESTAZIONEPREVISTA da VISTA_EXT_PRESTAZIONI)', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI', @level2type = N'COLUMN', @level2name = N'CODICEPRESTAZIONEPREVISTA'
	//GO
	//EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'(pasta e nome do arquivo da imagem)', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI', @level2type = N'COLUMN', @level2name = N'IMMAGINE_FULLPATH'
	//GO
	//EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'(px)', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI', @level2type = N'COLUMN', @level2name = N'IMMAGINE_LARGHEZZA'
	//GO
	//EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'(px)', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI', @level2type = N'COLUMN', @level2name = N'IMMAGINE_ALTEZZA'
	//GO
	//EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'proporção de zoom usada no cadastramento. necessário para os pontos dos labels (ver na table schemi_anatomici_etichette) veja também no projeto em CDib::PaintDIB(CDC* dcp, CRect rectDest) ', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI', @level2type = N'COLUMN', @level2name = N'ZOOM_FACTOR'
	//GO
	//EXEC sys.sp_addextendedproperty @name = N'MS_Description', @value = N'bool deleted or not', @level0type = N'SCHEMA', @level0name = N'dbo', @level1type = N'TABLE', @level1name = N'SCHEMI_ANATOMICI', @level2type = N'COLUMN', @level2name = N'ELIMINATO'
	//GO

	long	m_lID;
	CString	m_sDescrizione;
	long	m_lUO;							// Código da Especialidade - onde o esquema anatômico poderá ser usado
	CString	m_sCodicePrestazionePrevista;	// Código do Exame - onde o esquema anatômico poderá ser usado
	CString m_sImmagine_FullPath;
	long	m_lImmagine_Larghezza;
	long	m_lImmagine_Altezza;
	double	m_dZoom_Factor;
	BOOL	m_bEliminato;
	
	CSchemiAnatomici m_pSchemiAnatomici;

	//CSchemiAnatomici getObjSchemiAnatomici(long	p_lID);

	BOOL Find(long lID);

	//BOOL SoftRefreshData(CSchemiAnatomici* p_pSchemiAnatomici);

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

#endif /* _SchemiAnatomiciSet_H_ */