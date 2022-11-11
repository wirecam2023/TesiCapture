#ifndef _POSTACQUISIZONEDLG_H_
	#define _POSTACQUISIZONEDLG_H_

#include "EndoxResizableDlg.h"
#include "ThumbCtrl.h"

class CEsamiView;
class CModelessDlg;

class CPostAcquisizioneDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CPostAcquisizioneDlg)

public:

	CPostAcquisizioneDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CPostAcquisizioneDlg();

	enum { IDD = IDD_POSTACQUISIZIONE };

protected:

	afx_msg void OnBnClickedBtnElimina();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);

	LRESULT OnImageSel(WPARAM wParam, LPARAM lParam);

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	void AggiornaSpazioLibero();
	void CalcolaDimensioni(CModelessDlg* pDlg);

	COLORREF m_color1;
	COLORREF m_color2;

	CThumbCtrl m_ctrlListImage;
	CImgList m_ImgList;

	CEsamiView* m_pEsamiView;

	double m_dTotFileSize;

	CButtonLocalize m_ctrlBtnElimina;
	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic05;
	CStaticLocalize m_ctrlStatic07;

};

#endif /* _POSTACQUISIZONEDLG_H_ */