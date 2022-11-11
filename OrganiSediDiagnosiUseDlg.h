#ifndef _ORGANISEDIDIAGNOSIUSEDLG_H_
	#define _ORGANISEDIDIAGNOSIUSEDLG_H_

class CEsamiView;

class COrganiSediDiagnosiUseDlg : public CDialog
{
	DECLARE_DYNAMIC(COrganiSediDiagnosiUseDlg)

public:

	COrganiSediDiagnosiUseDlg(CWnd* pParent, CEsamiView* pEsamiView);

	enum { IDD = IDD_ORGANISEDIDIAGNOSI_USE_DLG };

	CString GetOrgano();
	CString GetSede();
	CString GetDiagnosi();
	void SetOrgano(CString strOrgano);
	void SetSede(CString strSede);
	void SetDiagnosi(CString strDiagnosi);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnDeseleziona();
	afx_msg void OnLbnSelchangeListOrgani();
	DECLARE_MESSAGE_MAP()

private:
	void RiempiListaOrgani();
	void RiempiTreeSedi(long lOrgano);
	void RiempiListaDiagnosi(long lOrgano);
	void RiempiListaCaratteristiche(long lOrgano, long lDiagnosi);

	CListBox m_ctrlListOrgani;
	CTreeCtrl m_ctrlTreeSedi;
	CListBox m_ctrlListDiagnosi;
	CListBox m_ctrlListCaratteristiche[6];
	int m_selPrecCaratt[6];

	CEsamiView* m_pEsamiView;

	CString m_strOrgano;
	CString m_strSede;
	CString m_strDiagnosi;

	CButtonLocalize m_ctrlButtonDelsel, m_ctrlButtonOK, m_ctrlButtonCancel;
public:
	afx_msg void OnLbnSelchangeListDiagnosi();
	afx_msg void OnLbnSelchangeListCaratt1();
	afx_msg void OnLbnSelchangeListCaratt2();
	afx_msg void OnLbnSelchangeListCaratt3();
	afx_msg void OnLbnSelchangeListCaratt4();
	afx_msg void OnLbnSelchangeListCaratt5();
	afx_msg void OnLbnSelchangeListCaratt6();
};

#endif /* _ORGANISEDIDIAGNOSIUSEDLG_H_ */