#ifndef _NOMENCLATOREDLG_H_
	#define _NOMENCLATOREDLG_H_

#include "MaskEdit.h"
#include "QueryUtility.h"

class CNomenclatoreDlg : public CDialog, public CQueryUtility
{

public:

	CNomenclatoreDlg(CWnd* pParent, CEsamiView* pEsamiView);

	enum { IDD = IDD_NOMENCLATORE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBtnEsami();
	afx_msg void OnBtnEsamiReparto();
	afx_msg void OnBtnPrestaz();
	afx_msg void OnBtnPrestazReparto();
	afx_msg void OnCbnSelchangeComboData();

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlRadio1;
	CButtonLocalize m_ctrlRadio2; 
	CButtonLocalize m_ctrlRadio3;
	CButtonLocalize m_ctrlBtnEsami;
	CButtonLocalize m_ctrlBtnEsamiReparto;
	CButtonLocalize m_ctrlBtnPrestaz;
	CButtonLocalize m_ctrlBtnPrestazReparto;
	CButtonLocalize m_ctrlButtonOK;
	CComboBox		m_ctrlComboData;
	CComboBox		m_ctrlComboMedico;
	CComboBox		m_ctrlComboSede;
	CMaskEdit		m_ctrlDataFine;
	CMaskEdit		m_ctrlDataIniz;
	CStaticLocalize m_ctrlStatic00; 
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;

private:

	void RiempiComboMedici();
	void RiempiComboSedi();

	CEsamiView* m_pEsamiView;

	CString m_sSedeEsame;
	int m_nMedicoIndex;
	int m_nProvenienza;

};

#endif /* _NOMENCLATOREDLG_H_ */