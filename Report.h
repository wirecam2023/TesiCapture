#pragma once

typedef struct Campo
{
	long lContenuto;
	long lX;
	long lY;
	long lL;
	long lA;
	long lColore;
	long lTabOrder;
	long lIDFaseBlocco;
} STRUCT_CAMPO;

typedef struct Linguetta
{  
	long lMostraAlbum;
	BOOL bVisualizzaSempre;
	CList <STRUCT_CAMPO> listCampi;
} STRUCT_LINGUETTA;

class CReport : public CObject
{

public:

	CReport();
	virtual ~CReport();

	void Draw(CDC* pDC, CWnd* pWnd);

	STRUCT_LINGUETTA* GetLinguetta();
	void SetLinguetta(STRUCT_LINGUETTA* pLinguetta);

	POSITION GetCurSel();
	void SetCurSel(POSITION pos);

protected:

	CRect m_rectPage;

private:

	void DrawAlbumArea(CDC* pDC, CWnd* pWnd, int lAlbumType);

	STRUCT_LINGUETTA* m_pLinguetta;
	POSITION m_pos;
};
