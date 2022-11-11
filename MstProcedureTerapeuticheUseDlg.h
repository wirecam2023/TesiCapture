#ifndef _MSTPROCEDURETERAPEUTICHEUSEDLG_H_
	#define _MSTPROCEDURETERAPEUTICHEUSEDLG_H_

#include "SediTreeCtrl.h"

class CMstProcedureTerapeuticheUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CMstProcedureTerapeuticheUseDlg)

public:

	CMstProcedureTerapeuticheUseDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CMstProcedureTerapeuticheUseDlg();

	enum { IDD = IDD_MST_PROCEDURETERAPEUTICHE_USE };

	CString GetValue();
	void SetValue(CString sValue);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedAggiungi();
	afx_msg void OnBnClickedDeselect();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeListOrgani();
	afx_msg void OnLbnSelchangeListLevel0();
	afx_msg void OnLbnSelchangeListLevel1();
	afx_msg void OnLbnSelchangeListLevel2();
	afx_msg void OnLbnSelchangeListLevel3();
	afx_msg void OnLbnSelchangeListLevel4();
	afx_msg void OnLbnSelchangeListLevel5();
	afx_msg void OnLbnSelchangeListLevel6();
	afx_msg void OnTvnSelchangedTreeSedi(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:

	void CreaFrase();
	void RiempiListOrgani();
	void RiempiTreeSedi();
	void RiempiListLevel0();
	void RiempiListSubLevels();


	CEsamiView* m_pEsamiView;

	CString m_strValue;

	CListBox m_ctrlListOrgani;
	CSediTreeCtrl m_ctrlTreeSedi;

	CListBox m_ctrlListLevel0;
	CListBox m_ctrlListLevel1;
	CListBox m_ctrlListLevel2;
	CListBox m_ctrlListLevel3;
	CListBox m_ctrlListLevel4;
	CListBox m_ctrlListLevel5;
	CListBox m_ctrlListLevel6;

	long* m_pTipoEsame;

	CStaticLocalize m_ctrlStaticOrgano, m_ctrlStaticSede, m_ctrlStaticTerm;
	CButtonLocalize m_ctrlButtonDeselect, m_ctrlButtonAdd, m_ctrlButtonCancel, m_ctrlButtonOK;
};

#endif /* _MSTPROCEDURETERAPEUTICHEUSEDLG_H_ */