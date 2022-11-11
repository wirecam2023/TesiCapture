#ifndef _BASEFORM_H_
	#define _BASEFORM_H_

#include "EndoxResizableDlg.h"
#include "EndoxStatic.h"

#define DEF_X1 8
#define DEF_X2 16
#define DEF_Y 26
#define DEF_BOR_X 5
#define DEF_BOR_Y 6

class CEsamiView;

class CBaseForm : public CEndoxResizableDlg
{

public:

	CBaseForm(CWnd* pParent, CEsamiView* pEsamiView, long lShowAlbum);
	virtual ~CBaseForm();

	enum { IDD = IDD_SUBFORM_EMPTY };

	BOOL CreateChildForm(CRect rectFrame, long lIDForm);
	BOOL GetInvertedState();
	long GetShowAlbum();
	void InvertShowAlbumState();
	void LoadControls();
	// void SetFocusOnFirst();

	CList <CEndoxStatic*> m_listControls;

	BOOL m_bLockResize;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:

	CStatic m_ctrlStaticFrame;

	CEsamiView* m_pEsamiView;
	long m_lShowAlbum;

	long m_lIDForm;

	BOOL m_bShowAlbumInverted;

};

#endif /* _BASEFORM_H_ */