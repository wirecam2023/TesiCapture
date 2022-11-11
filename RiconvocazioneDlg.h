//Gabriel BUG 6225 - Lista DO
#pragma once

#ifndef _RICONVOCAZIONEDLG_H_
#define _RICONVOCAZIONEDLG_H_

#include "ListSortableCtrl.h"
#include "EsamiView.h"
#include "MaskEdit.h"

class CRiconvocazioneDlg : public CDialog
{
	DECLARE_DYNAMIC(CRiconvocazioneDlg)

public:

	CRiconvocazioneDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CRiconvocazioneDlg();

	enum { IDD = IDD_RICONVOCAZIONE };

	CString m_sFicha;
	CString m_sNome;
	CString m_sMarca;
	CString m_sUnita;
	CString m_sDataEsame;
	CString m_sSiglaEsame;
	CMaskEdit m_sDataReconvocazione;
	CString m_sUnitaRiconvocazione;
	CString m_sDescrizioneMotivo;
	CString m_sPreparazione;
	long m_lIdMotivo;
	BOOL m_bPassivoReferto;
	CString m_sCorpoEmail;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	
	afx_msg void OnClickedRadioMotivo();
	afx_msg void OnClickedRadioReferto();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()

private:

	void CheckRadioMotivo(int nNewVal);
	void CheckRadioReferto(BOOL bNewVal);

	void RiempiComboMedico();
	void RiempiComboUnita();
	void RiempiComboCodicePrestazione();
	void CaricaDati();
	void FormataEmail();
	BOOL DataValida(CString sData);
	CString MotivoTesto(long lId);
	BOOL EsameRiconvocato(long lIdEsame);
	void Aggiorna();
	void SetReadOnly(BOOL bReadOnly);
	BOOL CampiValidi();
	CString GetUnitName(CString orderNumber); //BUG #9573 Felipe

	CEsamiView* m_pEsamiView;

	CStaticLocalize m_ctrlStatic1, m_ctrlStatic2, m_ctrlStatic3, m_ctrlStatic4, m_ctrlStatic5, m_ctrlStatic6, m_ctrlStatic7, m_ctrlStatic8, m_ctrlStatic10, m_ctrlStatic11, m_ctrlStatic12, m_ctrlStatic13, m_ctrlStatic14, m_ctrlStatic15, m_ctrlStatic16, m_ctrlStatic18, m_ctrlStaticGroup;
	CButtonLocalize m_ctrlButtonChiudi;
	CButtonLocalize m_ctrlButtonInvia;
	CButtonLocalize m_ctrlButtonAnnulla;

	CComboBox m_ctrlComboMedico;
	CComboBox m_ctrlComboUnita;
	CComboBox m_ctrlComboCodicePrestazione;

	CButtonLocalize m_ctrlRadio1;
	CButtonLocalize m_ctrlRadio2;
	CButtonLocalize m_ctrlRadio3;
	CButtonLocalize m_ctrlRadio4;
	CButtonLocalize m_ctrlRadio5;
	CButtonLocalize m_ctrlRadio6;
	CButtonLocalize m_ctrlRadio7;
	CButtonLocalize m_ctrlRadio8;
	CButtonLocalize m_ctrlRadio9;

public:
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedInvia();
	afx_msg void OnBnClickedAnnulla();
	afx_msg void OnEnChangeEditMotivo();
	afx_msg void OnEnChangeEditPreparazione();
};

#endif /* _RICONVOCAZIONEDLG_H_ */