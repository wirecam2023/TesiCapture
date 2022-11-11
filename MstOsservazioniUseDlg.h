#ifndef _MSTOSSERVAZIONIUSEDLG_H_
	#define _MSTOSSERVAZIONIUSEDLG_H_

#include "EndoxResizableDlg.h"
#include "OsservazioniSet.h"
#include "SediTreeCtrl.h"

class COsservazioniForm;
class CEsamiView;

class CMstOsservazioniUseDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CMstOsservazioniUseDlg)

public:

	CMstOsservazioniUseDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CMstOsservazioniUseDlg();

	enum { IDD = IDD_MST_OSSERVAZIONI_USE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedAggiungi();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeListOrgani();
	afx_msg void OnLbnSelchangeListLevel0();
	afx_msg void OnLbnSelchangeListLevel1();
	afx_msg void OnLbnSelchangeListLevel2();
	afx_msg void OnLbnSelchangeListLevel3();
	afx_msg void OnLbnSelchangeListLevel4();
	afx_msg void OnLbnSelchangeListLevel5();
	afx_msg void OnLbnSelchangeListLevel6();
	afx_msg void OnSize(UINT nType, int cx, int cy);

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
	COsservazioniForm* m_pFormOsservazioni;
	COsservazioniForm* m_pFormParent;

	COsservazioniSet m_setOsservazioni;

	CListBox m_ctrlListOrgani;
	CSediTreeCtrl m_ctrlTreeSedi;

	CListBox m_ctrlListLevel0;
	CListBox m_ctrlListLevel1;
	CListBox m_ctrlListLevel2;
	CListBox m_ctrlListLevel3;
	CListBox m_ctrlListLevel4;
	CListBox m_ctrlListLevel5;
	CListBox m_ctrlListLevel6;

	CStatic m_ctrlStaticOsservazioni;

	CStaticLocalize m_ctrlStaticOrgano, m_ctrlStaticSede, m_ctrlStaticTerm;
	CButtonLocalize m_ctrlButtonAdd, m_ctrlButtonCancel, m_ctrlButtonOK;

	long m_lTipoEsame;
};

#endif /* _MSTOSSERVAZIONIUSEDLG_H_ */