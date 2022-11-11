#ifndef _BRIGHTNESS_H_
	#define _BRIGHTNESS_H_

class CDib;

class CBrightnessDlg : public CDialog
{

public:

	CBrightnessDlg(CWnd* pParent, CDib** pDib, CDib** pDibUndo);
	virtual ~CBrightnessDlg(void);

	enum { IDD = IDD_BRIGHTNESS };
	CScrollBar		m_ctrlBright;

	int				m_nBrightnessLev;

	LPLOGPALETTE	m_pLogPal;
	LPLOGPALETTE	m_pOldPal;
	CDib**			m_pDib;
	CDib**			m_pDibUndo;
	CDib*			m_pDibReal;
	CWnd*			m_pView;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	DECLARE_MESSAGE_MAP()

	CStaticLocalize m_ctrlStaticLabel;
	CButtonLocalize m_ctrlButtonOK, m_ctrlButtonCancel;
};

#endif /* _BRIGHTNESS_H_ */