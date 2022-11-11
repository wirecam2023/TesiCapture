#ifndef _MSTCODIFICADIAGNOSIESAMEUSEDLG_H_
	#define _MSTCODIFICADIAGNOSIESAMEUSEDLG_H_

#include "CodificaDiagnosiEsameSet.h"
#include "SediTreeCtrl.h"

class CEsamiView;
class CCodificaDiagnosiEsameForm;

class CMstCodificaDiagnosiEsameUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CMstCodificaDiagnosiEsameUseDlg)

public:

	CMstCodificaDiagnosiEsameUseDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CMstCodificaDiagnosiEsameUseDlg();

	enum { IDD = IDD_MST_CODIFICADIAGNOSIESAME_USE };

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
	afx_msg void OnLbnSelchangeListLevel7();
	afx_msg void OnLbnSelchangeListLevel8();
	afx_msg void OnLbnSelchangeListLevel9();
	afx_msg void OnLbnSelchangeListLevel10();

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
	CCodificaDiagnosiEsameForm* m_pFormCodificaDiagnosiEsame;
	CCodificaDiagnosiEsameForm* m_pFormParent;

	CCodificaDiagnosiEsameSet m_setCodificaDiagnosiEsame;

	CListBox m_ctrlListOrgani;
	CSediTreeCtrl m_ctrlTreeSedi;

	CListBox m_ctrlListLevel0;
	CListBox m_ctrlListLevel1;
	CListBox m_ctrlListLevel2;
	CListBox m_ctrlListLevel3;
	CListBox m_ctrlListLevel4;
	CListBox m_ctrlListLevel5;
	CListBox m_ctrlListLevel6;
	CListBox m_ctrlListLevel7;
	CListBox m_ctrlListLevel8;
	CListBox m_ctrlListLevel9;
	CListBox m_ctrlListLevel10;

	CStatic m_ctrlStaticCodificaDiagnosiEsame;
	CStatic m_ctrlStaticCodificaDiagnosiEsame2;

	long m_lTipoEsame;

	CStaticLocalize m_ctrlStaticOrgano, m_ctrlStaticSede, m_ctrlStaticTerm;
	CButtonLocalize m_ctrlButtonAdd, m_ctrlButtonReset, m_ctrlButtonCancel, m_ctrlButtonOK;
public:
	afx_msg void OnTvnSelchangedTreeSedi(NMHDR *pNMHDR, LRESULT *pResult);
};

#endif /* _MSTCODIFICADIAGNOSIESAMEUSEDLG_H_ */