#pragma once

#include "CheckBoxTreeCtrl.h"
#include "ComboBoxExt.h"
#include "Common.h"
#include "QueryForm.h"
#include "SubForm.h"
#include "TXTextControl23.h"
#include "afxcmn.h"

class CEsamiView;

#define WM_ADD_RTFTEXT_TO_REPORT WM_USER + 0x6990

class CChecklistForm : public CEndoxDynForm
{

public:

	CChecklistForm(CWnd* pParentWnd, CEsamiView* pEsamiView);
	~CChecklistForm();

	enum { IDD = IDD_SUBFORM_CHECKLIST };

	static BOOL CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, CChecklistForm** pForm);

	long GetContenuto();

	BOOL CampoObbligatorioValido();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnApri();
	afx_msg void OnBnClickedBtnChiudi();
	afx_msg void OnBnClickedBtnImport();
	afx_msg void OnCbnSelchangeComboChecklist();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedChkMostraTodas(); // Luiz - 10/04/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo

	LRESULT OnItemCheckChanged(WPARAM wParam, LPARAM lParam);
	void ProcessItemCheckChanged(HTREEITEM hItem); //Julio Melhoria de performance checklist	

private:

	struct tagREGOLA
	{
		long lIDItem;
		long lIDItemBind;
		long lTipoRegola;
	};

	struct tagREGOLA2
	{
		long lIDItem;
		CList<long>* pListItemBind;
		long lTipoRegola;
	};

	struct VARIABLES
	{
		long lIDItem;
		CString sVariable;
		CString sValue;
	};

	//

	void AnalyzeAllRules(HTREEITEM hItemParent = NULL);
	void AnalyzeRules(HTREEITEM hItem);
	void AnalyzeRulesType2();
	void ApriRamo(HTREEITEM hItemPadre);
	void CaricaDati(long lIDItem);
	void CaricaRegole();
	BOOL CercaCheckNoSi(HTREEITEM hItem);
	BOOL CercaCheckSiNo(HTREEITEM hItem);
	void CheckPadre(HTREEITEM hItem);
	void ChiediValori(long lIDItem, CString& sText);
	BOOL ChiediValoriCombo(long lIDItem, CString& sText); //Julio 06/08/2018
	CString FindVariableValue(long lIDEsame, CString sVariableName); //Julio 01/02/2019
	CString GetPrestazione();// Luiz - 10/04/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo
	void ChiudiRamo(HTREEITEM hItemPadre);
	void EnableAllItems(HTREEITEM hItemParent = NULL);
	void EnableItems(const CList<long>* pList, BOOL bEnable, HTREEITEM hItemParent = NULL);
	HTREEITEM GetItemFromID(long lID, HTREEITEM hItemParent = NULL);
	BOOL GetSceltaMultipla(long lIDItem);
	void GetTesti(long lIDItem, CString& strRTF, CString& strTXT, long& lNumeroVariabili, long& lIDDiagnosi, CString& sDiagnosiCodice, CString& sDiagnosiDescrizione);
	CString GetTestoVariabili(long lIDItem);
	void RicaricaFrase(long lParentItemID = 0, long* pRefertoLen = NULL);
	void RicaricaFraseSub(HTREEITEM hItemPadre, long& lRefertoLen);
	void RicaricaFraseTemp();
	void RiempiAlbero();
	void RiempiAlberoSub(BOOL bEspansa, HTREEITEM hRoot, long lIDPadre);
	void RiempiComboChecklist();
	BOOL SetCheck(HTREEITEM hItem, BOOL bCheck);
	void SostituisciVariabili(long lIDItem, CString& strRTF, CString& strTXT);
	void SostituisciVariabiliAnnullati(long lIDItem, CString& strRTF, CString& strTXT);
	void UncheckAllItems(HTREEITEM hItemParent = NULL);
	void UncheckFratelli(HTREEITEM hItem);
	void UncheckRamo(HTREEITEM hItemPadre);

	//

	CButtonLocalize m_ctrlButtonApri;
	CButtonLocalize m_ctrlButtonChiudi;
	CButtonLocalize m_ctrlButtonImport;
	CButtonLocalize m_ctrlButtonImagens;

	CCheckBoxTreeCtrl m_ctrlTree;

	//CComboBox m_ctrlComboChecklist;
	CComboBoxExt m_ctrlComboChecklist;	// Marvel BUG 4094 - Combo Checklists filtradas deve ser vazio por default

	CButtonLocalize m_ctrlChkMostraTodas;
	CListCtrl m_ctrlListCodiciClassificazione;

	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;

	CTXTextControl23Ex m_ctrlTextControl;
	CTXTextControl23Ex m_ctrlTextControlHide;
	CTXTextControl23Ex m_ctrlTextControlItem;

	//
	CList<STRUCT_CHECKLIST> m_listChecklist; // Luiz - 10/04/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo
	CList<long> m_listCheckListItemObbligatory;
	CList<STRUCT_CHECKLISTITEM> m_listChecklistItem;
	CList<long> m_listIDCheckListItems;
	CList<tagREGOLA> m_listRegole;
	CList<tagREGOLA2> m_listRegole2;
	CList<VARIABLES*> m_listVariables;

	long m_lIDChecklist;
	long m_lIDItem;

public:
	afx_msg void OnBnClickedBtnImagens();
};
