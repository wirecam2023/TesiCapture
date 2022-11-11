#ifndef _MONITORAGGIOVERTDLG_H_
	#define _MONITORAGGIOVERTDLG_H_

#include "afxwin.h"

#include "MonitoraggioSet.h"
#include "FarmaciMonitoraggioSet.h"
#include "DosiMonitoraggioSet.h"
#include "MonitoraggioFarmaciDosiSet.h"
#include "DLL_Imaging\h\AMListCtrl.h"
#include "InfermieriCombo.h"

class CMonitoraggioVertDlg : public CDialog
{
	DECLARE_DYNAMIC(CMonitoraggioVertDlg)

public:

	CMonitoraggioVertDlg(CWnd* pParent, CEsamiView* pEsamiView, long lRecord);
	virtual ~CMonitoraggioVertDlg();

	enum { IDD = IDD_MONITORAGGIO_VERT };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedInsert();
	afx_msg void OnBnClickedRemove();

	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();

	afx_msg void OnCbnSelchangeCombo1Glasgow();
	afx_msg void OnCbnSelchangeCombo2Glasgow();
	afx_msg void OnCbnSelchangeCombo3Glasgow();
	void RecalculateGlasgow();

	afx_msg void OnCbnEditChangeComboFarmaci();
	afx_msg void OnCbnSelChangeComboFarmaci();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnLvnItemchangedListaFarmaci(NMHDR *pNMHDR, LRESULT *pResult);

	void CheckVentilazione();

private:

	void RiempiComboFase();
	void RiempiCombo1();
	void RiempiCombo2();
	void RiempiCombo3();
	void RiempiCombo4();
	void RiempiComboInfermieri();
	void RiempiComboPolso();
	void RiempiComboIntubazione();
	void RiempiComboVentilazione();
	void RiempiComboDoloreScala();
	void RiempiComboDoloreVAS();
	void RiempiComboDoloreNRS();
	void RiempiComboDoloreWB();
	void RiempiComboDoloreCCPO1();
	void RiempiComboDoloreCCPO2();
	void RiempiComboDoloreCCPO3();
	void RiempiComboDoloreCCPO4();
	void RiempiComboDoloreCCPO5();
	void RiempiComboDoloreLocalizzazione();
	void RiempiComboDoloreCaratteristiche();
	void RiempiComboDoloreFrequenza();
	void RiempiComboDoloreDurata();
	void RiempiComboRamsey();
	void RiempiComboGlasgow();
	void RiempiListaFarmaci();

	void UpdateDB();
	void UpdateCCPO();

	void DoloreScalaSelChange();

	CMonitoraggioSet m_setRecord;
	CMonitoraggioFarmaciDosiSet m_monitoraggioFarmaciDosiSet;

	CComboBox m_ctrlFase;
	CComboBox m_ctrlCmbDispositivo;
	CEdit m_ctrlEditOra;
	CEdit m_ctrlEditFC;
	CEdit m_ctrlEditPAMin, m_ctrlEditPAMax;
	CEdit m_ctrlEditSat;
	CEdit m_ctrlEditO2;
	//
	CComboBox m_ctrlCombo1;
	CComboBox m_ctrlCombo2;
	CComboBox m_ctrlCombo3;
	CComboBox m_ctrlCombo4;	
	CStatic m_ctrlStaticScore;
	CEdit m_ctrlEditETCO2;
	CComboBox m_ctrlComboPolso;
	CComboBox m_ctrlComboIntubazione;
	CComboBox m_ctrlComboVentilazione;
	CEdit m_ctrlEditVentilazioneVt;
	CEdit m_ctrlEditVentilazioneFr;

	CComboBox m_ctrlCombo1Glasgow;
	CComboBox m_ctrlCombo2Glasgow;
	CComboBox m_ctrlCombo3Glasgow;
	CStatic m_ctrlStaticScoreGlasgow;

	CComboBox m_ctrlFarmaci;
	CEdit m_ctrlDosi;
	CAMEditComboListCtrl m_listaFarmaciDosi;
	CButtonLocalize m_btnInserisci;
	CButtonLocalize m_btnRimuovi;
	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;
	int m_rigaSelezionata;
	CComboBox m_ctrlComboInfermiere;

	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
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
	CStaticLocalize m_ctrlStatic23;
	CStaticLocalize m_ctrlStatic24;
	CStaticLocalize m_ctrlStatic25;
	CStaticLocalize m_ctrlStatic26;
	CStaticLocalize m_ctrlStatic27;
	CStaticLocalize m_ctrlStatic28;
	CStaticLocalize m_ctrlStatic29;
	CStaticLocalize m_ctrlStatic30;
	CStaticLocalize m_ctrlStatic31;
	CStaticLocalize m_ctrlStatic32;
	CStaticLocalize m_ctrlStatic33;
	CStaticLocalize m_ctrlStatic34;
	CStaticLocalize m_ctrlStatic35;
	CStaticLocalize m_ctrlStatic36;
	CStaticLocalize m_ctrlStatic37;
	CStaticLocalize m_ctrlStatic38;
	CStaticLocalize m_ctrlStatic39;

	CStaticLocalize m_ctrlStaticFarmaci;
	CStaticLocalize m_ctrlStaticLabel3;
	CStaticLocalize m_ctrlStaticLabel6;
	CStaticLocalize m_ctrlStaticLabel7;
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

	CComboBox m_ctrlComboDoloreScala;
	CComboBox m_ctrlComboDoloreVAS;
	CComboBox m_ctrlComboDoloreNRS;
	CComboBox m_ctrlComboDoloreWB;
	CComboBox m_ctrlComboDoloreCCPO1;
	CComboBox m_ctrlComboDoloreCCPO2;
	CComboBox m_ctrlComboDoloreCCPO3;
	CComboBox m_ctrlComboDoloreCCPO4;
	CComboBox m_ctrlComboDoloreCCPO5;
	CComboBox m_ctrlComboDoloreLocalizzazione;
	CEdit m_ctrlEditDoloreLocalizzazioneDettaglio;
	CComboBox m_ctrlComboDoloreCaratteristiche;
	CComboBox m_ctrlComboDoloreFrequenza;
	CComboBox m_ctrlComboDoloreDurata;
	CComboBox m_ctrlComboRamsey;

	CEsamiView* m_pEsamiView;

public:
	long m_lRecord;


	afx_msg void OnCbnSelchangeComboVentilazione();
	afx_msg void OnCbnSelchangeComboDoloreScala();
	afx_msg void OnCbnSelchangeComboDoloreLocalizzazione();
	afx_msg void OnCbnSelchangeComboCcpo1();
	afx_msg void OnCbnSelchangeComboCcpo2();
	afx_msg void OnCbnSelchangeComboCcpo3();
	afx_msg void OnCbnSelchangeComboCcpo4();
	afx_msg void OnCbnSelchangeComboCcpo5();
};

#endif /* _MONITORAGGIOVERTDLG_H_ */