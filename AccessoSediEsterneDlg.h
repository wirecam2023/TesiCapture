#ifndef _ACCESSOSEDIESTERNEDLG_H_
	#define _ACCESSOSEDIESTERNEDLG_H_

class CAccessoSediEsterneDlg : public CDialog
{
	DECLARE_DYNAMIC(CAccessoSediEsterneDlg)

public:

	CAccessoSediEsterneDlg(CWnd* pParent);
	virtual ~CAccessoSediEsterneDlg();

	enum { IDD = IDD_ACCESSO_SEDI_ESTERNE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiLista();

	//

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CListCtrl m_ctrlList;

	//

	BOOL m_bIsOracle;

};

#endif /* _ACCESSOSEDIESTERNEDLG_H_ */