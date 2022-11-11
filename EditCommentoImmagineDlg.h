#ifndef _EDITCOMMENTOIMMAGINEDLG_H_
	#define _EDITCOMMENTOIMMAGINEDLG_H_

#include "EndoxResizableDlg.h"

class CEditCommentoImmagineDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CEditCommentoImmagineDlg)

public:

	CEditCommentoImmagineDlg(CWnd* pParent, UINT idTitle, const CString &sValue, long lIDTipoEsame, CRect rectLocation);
	~CEditCommentoImmagineDlg();

	enum { IDD = IDD_EDITCOMMENTOIMMAGINE_DLG };

	CString GetValue();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditValue();
	afx_msg void OnNMDblclkListCommenti(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiListaCommenti(long lIDTipoEsame);

	//

	long m_lIDTipoEsame;
	CRect m_rectLocation;

	CString m_sTitle;
	CString m_sValue;

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;

	CListCtrl m_ctrlListCommenti;
	CEdit m_ctrlEditCommento;

};

#endif /* _EDITCOMMENTOIMMAGINEDLG_H_ */