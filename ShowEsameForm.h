#ifndef _SHOWESAMEFORM_H_
	#define _SHOWESAMEFORM_H_

#include "EndoxResizableDlg.h"

class CMosaicDlg;

class CShowEsameForm : public CEndoxResizableDlg
{

public:

	CShowEsameForm(CWnd* pParent = NULL);

	enum { IDD = IDD_ALBUM_TOTALE_SUBESAME };

	CMosaicDlg*		m_pMosaicDlg;
	structEsame*	m_pRigaEsame;
	int				m_nEsame;

	CBitmapButtonEx	m_BtnImmFirst,
					m_BtnImmPrev,
					m_BtnImmNext,
					m_BtnImmLast;

	static	BOOL	CreateFormEx(CWnd* pParent, CWnd* pFrame, CShowEsameForm** pDlg);
	BOOL			CreateChildForm(CWnd* pParent, CRect rectFrame);

	void SetParentDialog(CMosaicDlg* pDlg)	{ m_pMosaicDlg = pDlg; }
	void SetParameter(int nEsame, structEsame* pRiga);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnSelectall();
	afx_msg void OnPageFirst();
	afx_msg void OnPagePrev();
	afx_msg void OnPageNext();
	afx_msg void OnPageLast();
	afx_msg void OnCancel() {};
	afx_msg void OnOK() {};

	DECLARE_MESSAGE_MAP()

	CStaticLocalize m_ctrlLabel1,
		            m_ctrlLabel2,
		            m_ctrlLabel3,
		            m_ctrlLabel4,
		            m_ctrlLabel5;
};

#endif /* _SHOWESAMEFORM_H_ */