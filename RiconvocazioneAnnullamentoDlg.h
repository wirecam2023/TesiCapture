//Gabriel BUG 6225 - Lista DO
#pragma once

#include "EndoxResizableDlg.h"

#ifndef _RICONVOCAZIONEANNULLAMENTODLG_H_
#define _RICONVOCAZIONEANNULLAMENTODLG_H_

class CRiconvocazioneAnnullamentoDlg : public CDialog
{
	DECLARE_DYNAMIC(CRiconvocazioneAnnullamentoDlg)

public:
	CRiconvocazioneAnnullamentoDlg(CWnd* pParent, long lId);   // standard constructor
	virtual ~CRiconvocazioneAnnullamentoDlg();

	CString m_sMotivoAnnullamento;
	long m_lIdEsame;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

// Dialog Data
	enum { IDD = IDD_RICONVOCAZIONE_ANNULLAMENTO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnCancel();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;
};

#endif /* _RICONVOCAZIONEANNULLAMENTODLG_H_ */