#ifndef _ORGANISEDIDLG_H_
	#define _ORGANISEDIDLG_H_

#include "SediTreeCtrl.h"

class COrganiSediDlg : public CDialog
{
	DECLARE_DYNAMIC(COrganiSediDlg)

public:

	COrganiSediDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL selectionMode = FALSE);
	virtual ~COrganiSediDlg();

	CString			m_strRicerca;
	CString         m_strRicercaView;

	enum { IDD = IDD_ORGANISEDI_MOD_DLG };

protected:

	virtual void	DoDataExchange(CDataExchange* pDX);
	virtual BOOL	OnInitDialog();

	afx_msg HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void	OnLbnSelchangeListOrgani();
	afx_msg void	OnTvnSelchangedTreeSedi(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void	OnBnClickedBtnOrganiElimina();
	afx_msg void	OnBnClickedBtnOrganiModifica();
	afx_msg void	OnBnClickedBtnOrganiNuovo();
	afx_msg void	OnBnClickedBtnSediElimina();
	afx_msg void	OnBnClickedBtnSediModifica();
	afx_msg void	OnBnClickedBtnSediNuovo();
	afx_msg void	OnBnClickedBtnSediNuovosub();

	DECLARE_MESSAGE_MAP()

private:

	void RiempiTreeSedi();
	void RiempiListOrgani();


	CEsamiView*		m_pEsamiView;

	CListBox		m_ctrlListOrgani;
	CSediTreeCtrl	m_ctrlTreeSedi;

	CStaticLocalize m_ctrlStaticOrgani, m_ctrlStaticSedi, m_ctrlStaticCodiceIntegrazione;
	CButtonLocalize m_ctrlButtonCancel, m_ctrlButtonNew, m_ctrlButtonMod, m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonNew2, m_ctrlButtonNew3, m_ctrlButtonMod2, m_ctrlButtonDel2;
	CEdit m_ctrlEdtCodiceIntegrazione;

	CString m_sCodiceIntegrazione;

	BOOL m_bSelectionMode;
};

#endif /* _ORGANISEDIDLG_H_ */