#ifndef _MSTDIAGNOSIUSEDLG_H_
	#define _MSTDIAGNOSIUSEDLG_H_

#include "DiagnosiSet.h"
#include "SediTreeCtrl.h"

class CEsamiView;
class CDiagnosiForm;

class CMstDiagnosiUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CMstDiagnosiUseDlg)

public:

	CMstDiagnosiUseDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CMstDiagnosiUseDlg();

	enum { IDD = IDD_MST_DIAGNOSI_USE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedAggiungi();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedResetta();
	afx_msg void OnLbnSelchangeListOrgani();
	afx_msg void OnLbnSelchangeListLevel0();
	afx_msg void OnLbnSelchangeListLevel1();
	afx_msg void OnLbnSelchangeListLevel2();
	afx_msg void OnLbnSelchangeListLevel3();
	afx_msg void OnLbnSelchangeListLevel4();
	afx_msg void OnLbnSelchangeListLevel5();
	afx_msg void OnLbnSelchangeListLevel6();
	DECLARE_MESSAGE_MAP()

private:

	void CreaFrase();
	void RiempiListOrgani();
	void RiempiTreeSedi();
	void RiempiListLevel0();
	void RiempiListSubLevels();

	void ClearForm();
	void LoadForm();
	void SaveForm();
	BOOL UpdateData(BOOL bSaveAndValidate);

	CEsamiView* m_pEsamiView;
	CDiagnosiForm* m_pFormDiagnosi;
	CDiagnosiForm* m_pFormParent;

	CDiagnosiSet m_setDiagnosi;

	CListBox m_ctrlListOrgani;
	CSediTreeCtrl m_ctrlTreeSedi;

	CListBox m_ctrlListLevel0;
	CListBox m_ctrlListLevel1;
	CListBox m_ctrlListLevel2;
	CListBox m_ctrlListLevel3;
	CListBox m_ctrlListLevel4;
	CListBox m_ctrlListLevel5;
	CListBox m_ctrlListLevel6;

	CStatic m_ctrlStaticDiagnosi;

	long m_lTipoEsame;

	CButtonLocalize m_ctrlButtonAdd;
	CButtonLocalize m_ctrlButtonReset;
	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonOK;

	CStaticLocalize m_ctrlStaticOrgano;
	CStaticLocalize m_ctrlStaticSede;
	CStaticLocalize m_ctrlStaticTerm;
};

#endif /* _MSTDIAGNOSIUSEDLG_H_ */