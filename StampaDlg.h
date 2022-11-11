#ifndef _STAMPADLG_H_
	#define _STAMPADLG_H_

#include "afxwin.h"

class CStampaDlg : public CDialog
{

public:

	CStampaDlg(CWnd* pParent, CEsamiView* pEsamiView);

	enum { IDD = IDD_STAMPA };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnChangeStampa();
	afx_msg void OnChangeDistanza();

private:

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStaticStampante;
	CButtonLocalize m_ctrlButton06;
	CButtonLocalize m_ctrlButton07;
	CButtonLocalize m_ctrlButton08;
	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlRadioStampa1;
	CButtonLocalize m_ctrlRadioStampa2;
	CButtonLocalize m_ctrlRadioStampa3;
	CButtonLocalize m_ctrlRadioStampa4;
	CButtonLocalize m_ctrlRadioStampa5;
	CComboBox m_ctrlComboHeader;
	CComboBox m_ctrlComboFooter;
	CComboBox m_ctrlComboStampante;

	//

	CEsamiView* m_pEsamiView;

	int	 m_nTypePrintImage;
	long m_lIDHeader;
	long m_lIDFooter;
	long m_lIDStampante;
	BOOL m_bPrintComment;
	BOOL m_bPrintPazData;
	BOOL m_bStampaNumero;

	CSpinButtonCtrl m_ctrlSpin;
	int m_nDistImmagini;

};

#endif /* _STAMPADLG_H_ */