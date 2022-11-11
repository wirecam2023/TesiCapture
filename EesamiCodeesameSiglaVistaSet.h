// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury

#ifndef _CEESAMICODEESAMESIGLAVISTASET_H_

#define _CEESAMICODEESAMESIGLAVISTASET_H_

#include "BaseSet.h"
/*
	USE[TESICAPTURE]
	GO
	SET ANSI_NULLS ON
	GO
	SET QUOTED_IDENTIFIER ON
	GO

	*** OLD ***
	create view[dbo].[VISTA_SCHEMI_ANATOMICI_PERTIPIESAMI] as
	SELECT
	ETipoEsame.UO AS ID_UO,
	ETipoEsame.CONTATORE AS ID_TIPO_ESAMI,
	UO.DESCRIZIONE + ': ' + ETipoEsame.DESCRIZIONE + ' (' + ETipoEsame.SIGLA + ')' AS DESC_TIPO_ESAMI
	FROM
	ETipoEsame INNER JOIN UO ON ETipoEsame.UO = UO.ID
	WHERE(ETipoEsame.Eliminato = 0) AND(UO.Eliminato = 0)
	GO

	-- ID_UO			int	
	-- ID_TIPO_ESAMI	int	
	-- DESC_TIPO_ESAMI	varchar(565)


	*** NOVO ***
	create view[dbo].[VISTA_SCHEMI_ANATOMICI_PERTIPIESAMI] as
	select DISTINCT
	A.CODICEPRESTAZIONEPREVISTA AS SIGLA_EXAME,
	A.UO,
	B.ID,
	B.DESCRIZIONE,
	--B.UO,
	--B.CODICEPRESTAZIONEPREVISTA,
	B.IMMAGINE_FULLPATH,
	B.IMMAGINE_LARGHEZZA,
	B.IMMAGINE_ALTEZZA,
	B.ZOOM_FACTOR,
	B.ELIMINATO
	from VISTA_EXT_PRESTAZIONI A INNER JOIN SCHEMI_ANATOMICI B
	ON A.UO = B.UO AND A.CODICEPRESTAZIONEPREVISTA = B.CODICEPRESTAZIONEPREVISTA
	WHERE A.ELIMINATO = 0 AND B.ELIMINATO = 0
	order by A.UO

	-----
	Julio DiPolito	,	18 de mar., 11:50	,	select IDPRESTAZIONE as [IDPRESTAZIONE = CODESAME na tabela EESAMI], CODICEPRESTAZIONE as SIGLA from EXT_PRESTAZIONI
	Julio DiPolito	,	18 de mar., 11:58	,	select distinct(CODICEPRESTAZIONEPREVISTA), uo from VISTA_EXT_PRESTAZIONI order by uo

	** NOVO **

	CREATE VIEW [dbo].[VISTA_EESAMI_CODESAME_SIGLA]
	AS
	select
	A.CONTATORE,
	A.UO,
	B.IDPRESTAZIONE as CODESAME, -- [IDPRESTAZIONE = CODESAME na tabela EESAMI]
	B.CODICEPRESTAZIONE as SIGLA
	from
	EESAMI A FULL OUTER JOIN EXT_PRESTAZIONI B on A.CODESAME = B.IDPRESTAZIONE
	GO

	Column_name	Type	Computed	Length	Prec	Scale	Nullable	TrimTrailingBlanks	FixedLenNullInSource	Collation
	CONTATORE	int		no			4		10   	0    	yes			(n/a)				(n/a)					NULL
	UO			int		no			4		10   	0    	yes			(n/a)				(n/a)					NULL
	CODESAME	varchar	no			50	     	     		yes			no					yes						Latin1_General_CI_AS
	SIGLA		varchar	no			50	     	     		yes			no					yes						Latin1_General_CI_AS

*/
class CEesamiCodeesameSiglaVistaSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEesamiCodeesameSiglaVistaSet)

public:

	CEesamiCodeesameSiglaVistaSet();

	long	m_lCONTATORE;
	long	m_lUO;
	CString	m_sCODESAME;
	CString	m_sSIGLA;
 	
	BOOL Find(long lID);

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

#endif /* _CEESAMICODEESAMESIGLAVISTASET_H_ */