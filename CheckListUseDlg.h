#ifndef _CHECKLISTUSEDLG_H_
	#define _CHECKLISTUSEDLG_H_

#include "CheckListTreeCtrl.h"
#include "EndoxResizableDlg.h"
#include "TXTextControl23.h"
#include "Common.h"
#include "QueryForm.h"

class CCheckListUseDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CCheckListUseDlg)

public:

	CCheckListUseDlg(CWnd* pParent, CEsamiView* pEsamiView, CTXTextControl23Ex* pTextControl, long lIDCheckList);
	CCheckListUseDlg(CWnd* pParent, CEsamiView* pEsamiView, CTXTextControl23Ex* pTextControl, CList<long>* pListIDCheckList, CList<long>* pListSearchElements = NULL);
	virtual ~CCheckListUseDlg();

	enum { IDD = IDD_CHECKLIST_USE_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);

	afx_msg void OnBnClickedBtnApri();
	afx_msg void OnBnClickedBtnChiudi();
	afx_msg void OnBnClickedCheckData();
	afx_msg void OnBnClickedBtnAddAndClean();
	afx_msg void OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMTVStateImageChangingTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void ApriRamo(HTREEITEM hItemPadre);
	void CaricaDati(long lIDItem);
	BOOL CercaCheckNoSi(HTREEITEM hItem);
	BOOL CercaCheckSiNo(HTREEITEM hItem);
	void CheckPadre(HTREEITEM hItem);
	void ChiediValori(long lIDItem, CString& sText);
	BOOL ChiediValoriCombo(long lIDItem, CString& sText);
	void ChiudiRamo(HTREEITEM hItemPadre);
	void ContaCheck(HTREEITEM hItem, long& lChecks);
	void ControllaAlbero();
	BOOL GetSceltaMultipla(long lIDItem);
	void GetTesti(long lIDItem, CString& strRTF, CString& strTXT, long& lNumeroVariabili, long& lIDDiagnosi, CString& sDiagnosiCodice, CString& sDiagnosiDescrizione);
	CString GetTestoVariabili(long lIDItem);
	void RicaricaFrase();
	void RicaricaFraseItemSelezionato();
	void RicaricaFraseSub(HTREEITEM hItemPadre, long& lRefertoLen);
	void RiempiAlbero();
	void RiempiAlberoSub(BOOL bEspansa, HTREEITEM hRoot, long lIDPadre);
	BOOL SetCheck(HTREEITEM hItem, BOOL bCheck);
	void SostituisciVariabili(long lIDItem, CString& strRTF, CString& strTXT);
	void UncheckFratelli(HTREEITEM hItem);
	void UncheckRamo(HTREEITEM hItemPadre);

	// --- //

	CButtonLocalize m_ctrlButtonApri;
	CButtonLocalize m_ctrlButtonChiudi;
	CButtonLocalize m_ctrlButtonCancel;

	CTXTextControl23Ex m_ctrlTextControlHide;
	CTXTextControl23Ex m_ctrlTextControl;

	CCheckListTreeCtrl m_ctrlTree;

	CStatic m_ctrlItemSelezionatoTitle;
	CStatic m_ctrlItemSelezionatoPlace;
	CTXTextControl23Ex m_ctrlItemSelezionatoTxControl;

	CButtonLocalize m_ctrlCheckData;
	CButtonLocalize m_ctrlBtnAddAndClean;

	// --- //

	CEsamiView* m_pEsamiView;
	CTXTextControl23Ex* m_pTextControl;
	long m_lIDItem;

	HTREEITEM m_hTreeItemFirst;

	CList<VARIABLES*> m_listVariables;

	long m_lIDCheckList;
	CList<long>* m_pListIDCheckList;

	// --- //

	CList<long> m_listIDCheckListRootsOrder; // RIMA 11-005.16 // inserisco le frasi in ordine di selezione //
	CList<long> m_listIDCheckListItems;

	CList<long>* m_pListSearchSelectedElements;
	CList<long> m_listCheckListItemObbligatory;

	HTREEITEM GetItemFromID(long lID, HTREEITEM hItemParent = NULL);
	CList<STRUCT_CHECKLISTITEM> m_listChecklistItem;

};

#endif /* _CHECKLISTUSEDLG_H_ */