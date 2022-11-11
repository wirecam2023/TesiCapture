#ifndef _MALATTIECRONICHEDLG_H_
	#define _MALATTIECRONICHEDLG_H_
#include "afxcmn.h"
#include "afxwin.h"

class CMalattieCronicheDlg : public CDialog
{

	DECLARE_DYNAMIC(CMalattieCronicheDlg)

public:

	CMalattieCronicheDlg(CWnd* pParent);
	virtual ~CMalattieCronicheDlg();

	enum { IDD = IDD_MALATTIECRONICHE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLvnItemchangedListMalattie(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListCampi(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnMalNew();
	afx_msg void OnBnClickedBtnMalEdt();
	afx_msg void OnBnClickedBtnMalDel();
	afx_msg void OnBnClickedBtnCamNew();
	afx_msg void OnBnClickedBtnCamEdt();
	afx_msg void OnBnClickedBtnCamDel();
	afx_msg void OnBnClickedBtnCamUp();
	afx_msg void OnBnClickedBtnCamDn();
	afx_msg void OnBnClickedBtnChiudi();

private:

	void RiempiListaMalattie(long lIDToSel);
	void RiempiListaCampi(long lIDToSel);

	//

	CListCtrlLocalize m_ctrlListMalattie;
	CListCtrlLocalize m_ctrlListCampi;

	CButtonLocalize m_ctrlBtnMalNew;
	CButtonLocalize m_ctrlBtnMalEdt;
	CButtonLocalize m_ctrlBtnMalDel;
	CButtonLocalize m_ctrlBtnCamNew;
	CButtonLocalize m_ctrlBtnCamEdt;
	CButtonLocalize m_ctrlBtnCamDel;
	CButtonLocalize m_ctrlBtnCamUp;
	CButtonLocalize m_ctrlBtnCamDn;
	CButtonLocalize m_ctrlBtnChiudi;

};

#endif /* _MALATTIECRONICHEDLG_H_ */