#ifndef _GRUPPIPRELIEVIOLDUSEDLG_H_
	#define _GRUPPIPRELIEVIOLDUSEDLG_H_

class CGruppiPrelieviOldUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CGruppiPrelieviOldUseDlg)

public:

	CGruppiPrelieviOldUseDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CGruppiPrelieviOldUseDlg();

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

#endif /* _GRUPPIPRELIEVIOLDUSEDLG_H_ */