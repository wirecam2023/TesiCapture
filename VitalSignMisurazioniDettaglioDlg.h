#pragma once

#include "EndoxResizableDlg.h"
#include "DLL_Imaging\h\AMListCtrl.h"

class CVitalSignMisurazioniDettaglioDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CVitalSignMisurazioniDettaglioDlg)

public:

	CVitalSignMisurazioniDettaglioDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, long idHeader);
	virtual ~CVitalSignMisurazioniDettaglioDlg();

	enum { IDD = IDD_VITALSIGN_MISURAZIONI_DETTAGLIO };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CButtonLocalize m_ctrlBtnConferma;
	CButtonLocalize m_ctrlBtnAnnulla;
	CButtonLocalize m_ctrlBtnVediPdf;

	CAMEditComboListCtrl m_ctrlList;

	CEsamiView* m_pEsamiView;

	long m_lIDHeader;
	CList<long> m_changedList;
	CString m_sIdSessioneVitalSign;

	void RiempiLista();

	LRESULT OnMisurazioni_VitalSign_ListEv(WPARAM wParam, LPARAM lParam);

	//

public:
	afx_msg void OnBnClickedVedipdf();
};
