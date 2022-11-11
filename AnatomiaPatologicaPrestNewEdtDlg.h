#ifndef _ANATOMIAPATOLOGICAPRESTNEWEDTDLG_H_
	#define _ANATOMIAPATOLOGICAPRESTNEWEDTDLG_H_

#include "afxwin.h"

#include "AnatomiaPatologicaEsamiPrestSet.h"

class CAnatomiaPatologicaPrestNewEdtDlg : public CDialog
{
	DECLARE_DYNAMIC(CAnatomiaPatologicaPrestNewEdtDlg)

public:

	CAnatomiaPatologicaPrestNewEdtDlg(CWnd* pParent, CEsamiView* pEsamiView, long lRecord);
	virtual ~CAnatomiaPatologicaPrestNewEdtDlg();

	enum { IDD = IDD_ANATOMIAPATOLOGICAPREST_NEWEDT_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CAnatomiaPatologicaEsamiPrestSet m_setRecord;

	CStaticLocalize m_ctrlStatic01;

	CComboBox m_ctrlComboPrestazione;

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CEsamiView* m_pEsamiView;
	long m_lRecord;
};

#endif /* _ANATOMIAPATOLOGICAPRESTNEWEDTDLG_H_ */