#ifndef _ENDOXSTATIC_H_
	#define _ENDOXSTATIC_H_

class CBaseForm;

class CEndoxStatic : public CStatic
{
	DECLARE_DYNAMIC(CEndoxStatic)

public:

	CEndoxStatic(CBaseForm* pBaseForm, CEsamiView* pEsamiView);
	virtual ~CEndoxStatic();

	BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID, long lColore, BOOL bOnAlbumZone, long lIDFaseBlocco);

	long m_lID;
	BOOL m_bOnAlbumZone;

protected:

	DECLARE_MESSAGE_MAP()

private:

	CBaseForm* m_pBaseForm;
	CEsamiView* m_pEsamiView;

};

#endif /* _ENDOXSTATIC_H_ */