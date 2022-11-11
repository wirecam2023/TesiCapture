#pragma once

#include "Common.h"
#include "SubForm.h"
#include "afxcmn.h"

#define BTNADD_VARIANTI 1
#define BTNADD_CORPO 2
#define BTNADD_DISABLE 3

class CEsamiView;

class CGenomicaRicercaVarianteForm : public CEndoxDynForm
{	
public:
	CGenomicaRicercaVarianteForm(CWnd* pParent, CEsamiView* pEsamiView);
	
	~CGenomicaRicercaVarianteForm();

	enum { IDD = IDD_SUBFORM_GENOMICA_FILTROVARIANTE };

	static BOOL CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, CGenomicaRicercaVarianteForm** pForm, long lBtnAdd);
	long GetContenuto() { return -1; };
	BOOL CampoObbligatorioValido() { return TRUE; };
	
protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();	
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnFind();	
	afx_msg void OnBnClickedBtnClear();
	
	DECLARE_MESSAGE_MAP()

public: 
	void RiempiCombos();

	CButtonLocalize m_ctrlButtonTrova;
	CButtonLocalize m_ctrlButtonAggiunge;
	CButtonLocalize m_ctrlButtonLimpa;

	CComboBox m_ctrlComboPatogenicita;
	CComboBox m_ctrlComboTipoVariante;
	CComboBox m_ctrlComboTipoAlterazione;	

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;
	CStaticLocalize m_ctrlStatic7;
	CStaticLocalize m_ctrlStatic8;
	CStaticLocalize m_ctrlStatic9;
	CStaticLocalize m_ctrlStatic10;
	CStaticLocalize m_ctrlStatic11;

	long m_lBtnAdd;
};
