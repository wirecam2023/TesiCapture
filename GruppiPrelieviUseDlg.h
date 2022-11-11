#ifndef _GRUPPIPRELIEVIUSEDLG_H_
	#define _GRUPPIPRELIEVIUSEDLG_H_

class CGruppiPrelieviUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CGruppiPrelieviUseDlg)

public:

	CGruppiPrelieviUseDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CGruppiPrelieviUseDlg();

	enum { IDD = IDD_GRUPPIPRELIEVI_USE };

	long m_lReturn;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLbnDblclkListaGruppi();

private:

	CEsamiView* m_pEsamiView;

	long m_lTipoEsame;

	//

	CListBox m_ctrlListaGruppi;

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

};

#endif /* _GRUPPIPRELIEVIUSEDLG_H_ */