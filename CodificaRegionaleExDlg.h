#ifndef _CODIFICAREGIONALEEXDLG_H_
	#define _CODIFICAREGIONALEEXDLG_H_

#include "CodificaRegionaleExSet.h"

#define CORE_VISUA 0
#define CORE_NUOVO 1
#define CORE_MODIF 2

class CCodificaRegionaleExDlg : public CDialog
{
	DECLARE_DYNAMIC(CCodificaRegionaleExDlg)

public:

	CCodificaRegionaleExDlg(CWnd* pParent);
	virtual ~CCodificaRegionaleExDlg();

	enum { IDD = IDD_CODIFICA_REGIONALE_EX };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnPri();
	afx_msg void OnBnClickedBtnSav();
	afx_msg void OnBnClickedBtnUnd();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnEnChangeEdit06();
	afx_msg void OnEnChangeEdit07();
	afx_msg void OnEnChangeEdit08();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit14();
	afx_msg void OnEnChangeEdit17();
	afx_msg void OnEnChangeEdit20();
	afx_msg void OnEnChangeEdit23();
	afx_msg void OnEnChangeEdit26();
	afx_msg void OnEnChangeEdit36();

	afx_msg void OnLbnSelchangeList00();

	DECLARE_MESSAGE_MAP()

private:

	void CambiaModalita(int iNuovaModalita);
	void Calcola05();
	void Calcola09();
	void Calcola12();
	void Calcola29();
	void SvuotaDialog();
	void VisualizzaDati();

	CListBox m_ctrlList00;
	CCodificaRegionaleExSet m_setCodificaRegionaleEx;

	int m_iModalita;

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
	CStaticLocalize m_ctrlStatic40;
	CStaticLocalize m_ctrlStatic41;
	CStaticLocalize m_ctrlStatic43;
	CStaticLocalize m_ctrlStatic44;
	//CStaticLocalize m_ctrlStatic45;

	CComboBox m_ctrlComboTipoEsame;

	CButtonLocalize m_ctrlCheckPrestazionePrincipale;
	CButtonLocalize m_ctrlCheckPrestazioneNormata;
	CButtonLocalize m_ctrlCheckPrestazionePNGLA;

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonSav;
	CButtonLocalize m_ctrlButtonUnd;
	CButtonLocalize m_ctrlButtonPri;
	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonDel;

};

#endif /* _CODIFICAREGIONALEEXDLG_H_ */