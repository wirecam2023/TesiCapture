#ifndef _UNIFICAZIONEANAGRAFICHEDLG_H_
	#define _UNIFICAZIONEANAGRAFICHEDLG_H_
#include "afxwin.h"
#include "afxcmn.h"

#include "PatientListbox.h"

typedef struct Paziente
{  
	long lID;
	CString sNominativo;
} STRUCT_PAZIENTE;

class CUnificazioneAnagraficheDlg : public CDialog
{

	DECLARE_DYNAMIC(CUnificazioneAnagraficheDlg)

public:

	CUnificazioneAnagraficheDlg(CWnd* pParent, CEsamiView* pEsamiView, CList<STRUCT_PAZIENTE>* pListPazienti);
	virtual ~CUnificazioneAnagraficheDlg();

	enum { IDD = IDD_UNIFICAZIONEANAGRAFICHE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLbnSelchangeListboxPazienti();

private:

	long GetFieldValue(long* pLongOld, CRecordset* pRecordsetOld, long* pLongNew, CRecordset* pRecordsetNew, BOOL bZeroIsValidValue, BOOL bPreferOld);
	CString GetFieldValue(CString sOld, CString sNew, BOOL bPreferOld);

	void SetListsItemText(int nItem, CString sOld, CString sNew, BOOL bPreferOld);

	BOOL HasAssiden(int contatore);

	//

	CEsamiView* m_pEsamiView;
	CList<STRUCT_PAZIENTE>* m_pListPazienti;

	//

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStaticNota;

	CPatientListBox m_ctrlListboxPazienti;
	CListCtrl m_ctrlListTitoli;
	CListCtrl m_ctrlListSelezionati;
	CListCtrl m_ctrlListRiepilogo;

};

#endif /* _UNIFICAZIONEANAGRAFICHEDLG_H_ */