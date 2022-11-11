#ifndef _MONITORAGGIOORIZDLG_H_
	#define _MONITORAGGIOORIZDLG_H_

#include "afxwin.h"

#include "MonitoraggioSet.h"

class CMonitoraggioOrizDlg : public CDialog
{
	DECLARE_DYNAMIC(CMonitoraggioOrizDlg)

public:

	CMonitoraggioOrizDlg(CWnd* pParent, CEsamiView* pEsamiView, long lRecord);
	virtual ~CMonitoraggioOrizDlg();

	enum { IDD = IDD_MONITORAGGIO_ORIZ };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();

	afx_msg void OnCbnSelchangeCombo1Glasgow();
	afx_msg void OnCbnSelchangeCombo2Glasgow();
	afx_msg void OnCbnSelchangeCombo3Glasgow();
	void RecalculateGlasgow();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()

private:

	CMonitoraggioSet m_setRecord;

	CComboBox m_ctrlFase;
	CComboBox m_ctrlCmbDispositivo;
	CEdit m_ctrlEditOra;
	CEdit m_ctrlEditFC;
	CEdit m_ctrlEditPA;
	CEdit m_ctrlEditSat;
	CEdit m_ctrlEditO2;
	CEdit m_ctrlEditMida;
	CEdit m_ctrlEditPeti;
	CEdit m_ctrlEditAtro;
	CEdit m_ctrlEditNalo;
	CEdit m_ctrlEditFlum;
	CEdit m_ctrlEditScop;
	CEdit m_ctrlEditGluc;
	CEdit m_ctrlEditAltri;
	CComboBox m_ctrlDolore;
	CComboBox m_ctrlCombo1;
	CComboBox m_ctrlCombo2;
	CComboBox m_ctrlCombo3;
	CComboBox m_ctrlCombo4;
	CStatic m_ctrlStaticScore;
	CComboBox m_ctrlCombo1Glasgow;
	CComboBox m_ctrlCombo2Glasgow;
	CComboBox m_ctrlCombo3Glasgow;
	CStatic m_ctrlStaticScoreGlasgow;

	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
	CStaticLocalize m_ctrlStatic05;
	CStaticLocalize m_ctrlStatic06;
	CStaticLocalize m_ctrlStatic07;
	CStaticLocalize m_ctrlStatic08;
	CStaticLocalize m_ctrlStatic09;
	CStaticLocalize m_ctrlStatic10;
	CStaticLocalize m_ctrlStatic11;
	CStaticLocalize m_ctrlStatic12;
	CStaticLocalize m_ctrlStatic13;
	CStaticLocalize m_ctrlStatic14;
	CStaticLocalize m_ctrlStatic15;
	CStaticLocalize m_ctrlStatic16;
	CStaticLocalize m_ctrlStatic17;
	CStaticLocalize m_ctrlStatic18;
	CStaticLocalize m_ctrlStatic19;
	CStaticLocalize m_ctrlStatic20;
	CStaticLocalize m_ctrlStatic21;
	CStaticLocalize m_ctrlStatic22;
	CStaticLocalize m_ctrlStatic1Glasgow;
	CStaticLocalize m_ctrlStatic2Glasgow;
	CStaticLocalize m_ctrlStatic3Glasgow;
	CStaticLocalize m_ctrlStatic4Glasgow;

	int m_nPuntiScore1;
	int m_nPuntiScore2;
	int m_nPuntiScore3;
	int m_nPuntiScore4;
	int m_nTotalScore;
	COLORREF m_colorScore;

	int m_nPuntiScore1Glasgow;
	int m_nPuntiScore2Glasgow;
	int m_nPuntiScore3Glasgow;
	int m_nTotalScoreGlasgow;
	COLORREF m_colorScoreGlasgow;

	CEsamiView* m_pEsamiView;

public:
	long m_lRecord;

};

#endif /* _MONITORAGGIOORIZDLG_H_ */