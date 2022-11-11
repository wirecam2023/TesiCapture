#ifndef _FRASIDLG_H_
	#define _FRASIDLG_H_

#define NO_MODE		0
#define ADD_MODE	1
#define MOD_MODE	2
#define ROOT_MODE	3

class CFrasiExDlg : public CDialog
{

public:

	CFrasiExDlg(CEsamiView* pEsamiView);

	enum { IDD = IDD_FRASI_EX };

	CString GetNomeMedico(long lMedico);
	void RiempiListaFigli(HTREEITEM hPadre, long lPadre);
	void RiempiListaFrasi();
	BOOL RiempiTipoEsame();
	void ImpostaModalita(int nModalita);

	CEsamiView*	m_pEsamiView;

	int m_nModalita;
	long m_lTipoEsame;
	long m_lFamiglia;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnChangeFamiglia(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeTipoEsame();
	afx_msg void OnChangeListaFrasi(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNewCateg();
	afx_msg void OnNewFrase();
	afx_msg void OnMod();
	afx_msg void OnDel();
	afx_msg void OnSav();
	afx_msg void OnUnd();
	DECLARE_MESSAGE_MAP()

	CStaticLocalize m_ctrlStatic1, m_ctrlStatic2;
	CButtonLocalize m_ctrlButton1, m_ctrlButton2, m_ctrlButton3, m_ctrlButton4, m_ctrlButton5, m_ctrlButton6, m_ctrlButtonOK;
	CTabCtrlLocalize m_ctrlFamiglia;
	CComboBox		 m_ctrlTipoEsame;
	CTreeCtrl		 m_ctrlListaFrasi;
};

#endif /* _FRASIDLG_H_ */