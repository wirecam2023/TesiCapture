#ifndef _MSTINDICAZIONIUSEDLG_H_
	#define _MSTINDICAZIONIUSEDLG_H_

/*
#include "afxwin.h"
class CEsamiView;
*/

class CMstIndicazioniUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CMstIndicazioniUseDlg)

public:

	CMstIndicazioniUseDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CMstIndicazioniUseDlg();

	enum { IDD = IDD_MST_INDICAZIONI_USE };

	CString GetValue();
	void SetValue(CString sValue);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeListLevel0();
	afx_msg void OnBnClickedAdd();
	DECLARE_MESSAGE_MAP()

private:
	void RiempiLevel0(long lTipoEsame);
	void RiempiLevel1(long lPadre);

	CEsamiView* m_pEsamiView;
	CListBox m_ctrlListLevel0;
	CListBox m_ctrlListLevel1;
	CString m_strValue;

	CButtonLocalize m_ctrlButtonAdd, m_ctrlButtonCancel, m_ctrlButtonOK;
};

#endif /* _MSTINDICAZIONIUSEDLG_H_ */