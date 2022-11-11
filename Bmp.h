#ifndef _BMP_H_
#define _BMP_H_

#include "Dib.h"

#define BMP_L_NORMALMODE	1000
#define BMP_L_NODOUBLECLICK	1100

#define BMP_R_NORMALMODE	2000
#define BMP_R_SENDTOPARENT	2100

#define RGB_BLACK RGB(0, 0, 0)
#define RGB_BLUE RGB(47, 47, 255)
#define RGB_GRAY_DARK RGB(95, 95, 95)
#define RGB_GRAY_LIGHT RGB(223, 223, 223)
#define RGB_GREEN RGB(0, 255, 0)
#define RGB_RED RGB(255, 0, 0)
#define RGB_WHITE RGB(255, 255, 255)

typedef struct PUNTI
{
	long lIdPunto;
	long lIdOrgano;
	long lX;
	long lY;
} tagPunti;

typedef struct PUNTI_DERMOX
{
	long lIDPunto;
	CPoint ptPunto;
	long lNumeroDermox;
	char szSede[256];
	char szPattern[256];
	BOOL bAsportazione;
} tagPuntiDermox;

class CEditBmp;
class CCheckList;
class CEsamiView;

class CBmp : public CWnd
{

public:

	CBmp();
	virtual ~CBmp();

	// statici --> //
	static BOOL CreateBmp(CEsamiView* pActiveView, CWnd* pParentWnd, CWnd* pctrFrame, CBmp* pBmp);

	static CEsamiView*	m_pEsamiView;
	static CWnd*		m_pParentWnd;
	static COLORREF		m_rgbPointColors[6];
	// <-- statici //

	// non statici --> //
	void	AssignEdit(CEditBmp* pEdit);
	void	AutoRedraw(CRect* pRect = NULL);
	void	SetMouseMode(int nLeft, int nRight);
	void	DeSelectBmp();
	BOOL	IsSelect();
	BOOL	IsValidBmp();
	BOOL	SelectBmp();
	BOOL	SelectBmp(BOOL bSelect);
	void	SendBmpMessage(UINT nMsg);

	BOOL		m_bAutoRedraw;
	long		m_lID;

	int			m_nBtnMouseModeLeft;
	int			m_nBtnMouseModeRight;

	CEsamiView* m_pActiveView;
	CDib*		m_pDib;
	CEditBmp*	m_pEditWnd;
	BOOL		m_bIsSelect;
	CWnd*		m_pParentAlbum;
	CWnd*		m_pParentFrame;
	CString		m_strComment;
	CString		m_strSede;

	int GetPointNumber();
	void SetPoint(int iPointNumber, COLORREF colorCircle, COLORREF colorNumber, BOOL bRedraw);
	void SetPointAutoColor(int iPointNumber, BOOL bRedraw);
	void SetPointColor(COLORREF colorCircle, COLORREF colorNumber, BOOL bRedraw);
	void SetPointNumber(int iPointNumber, BOOL bRedraw);

	int GetPositionNumber();
	void SetPositionNumber(int iPositionNumber, int iTotalImageNumber, BOOL bRedraw);

	int m_iPointNumber;
	COLORREF m_colorCircle;
	COLORREF m_colorNumber;

	int m_iPositionNumber;
	int m_iTotalImageNumber;
	// <-- non statici //

protected:

	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd);

	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual afx_msg LRESULT OnResizeForm(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

};

#endif  /* _BMP_H_ */