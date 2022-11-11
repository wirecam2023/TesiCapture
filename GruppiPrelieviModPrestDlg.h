#ifndef _GRUPPIPRELIEVIMODPRESTDLG_H_
	#define _GRUPPIPRELIEVIMODPRESTDLG_H_

class CGruppiPrelieviModPrestDlg : public CDialog
{
	DECLARE_DYNAMIC(CGruppiPrelieviModPrestDlg)

public:

	CGruppiPrelieviModPrestDlg(CWnd* pParent, long lIDGruppo, long lRecord);
	virtual ~CGruppiPrelieviModPrestDlg();

	enum { IDD = IDD_GRUPPIPRELIEVI_MOD_PREST };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnCbnSelchangeComboTipo();

private:

	CComboBox m_ctrlComboTipo;
	CComboBox m_ctrlComboIntervento;
	CEdit m_ctrlEditPrelievi;
	CEdit m_ctrlEditDescrizione;

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;

	//

	CEsamiView* m_pEsamiView;
	long m_lIDGruppo;
	long m_lRecord;

};

#endif /* _GRUPPIPRELIEVIMODPRESTDLG_H_ */