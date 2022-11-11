#ifndef _ANATOMIAPATOLOGICANEWEDTDLG_H_
	#define _ANATOMIAPATOLOGICANEWEDTDLG_H_

class CAnatomiaPatologicaNewEdtDlg : public CDialog
{
	DECLARE_DYNAMIC(CAnatomiaPatologicaNewEdtDlg)

public:

	CAnatomiaPatologicaNewEdtDlg(CWnd* pParent, CEsamiView* pEsamiView, long lRecord);
	virtual ~CAnatomiaPatologicaNewEdtDlg();

	enum { IDD = IDD_ANATOMIAPATOLOGICA_NEWEDT_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnCbnSelchangeComboTipo();

private:

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
	CStaticLocalize m_ctrlStatic05;

	CEdit m_ctrlEditCampione;
	CComboBox m_ctrlComboTipo;
	CComboBox m_ctrlComboIntervento;
	CEdit m_ctrlEditPrelievi;
	CEdit m_ctrlEditDescrizione;

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CEsamiView* m_pEsamiView;
	long m_lIDEsame;
	long m_lRecord;

};

#endif /* _ANATOMIAPATOLOGICANEWEDTDLG_H_ */