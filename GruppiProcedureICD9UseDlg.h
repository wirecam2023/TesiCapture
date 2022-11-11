#ifndef _GRUPPIPROCEDUREICD9USEDLG_H_
	#define _GRUPPIPROCEDUREICD9USEDLG_H_

#include "afxwin.h"

class CGruppiProcedureICD9UseDlg : public CDialog
{
	DECLARE_DYNAMIC(CGruppiProcedureICD9UseDlg)

public:

	CGruppiProcedureICD9UseDlg(CWnd* pParent, CEsamiView* pEsamiView, long lTipoEsame);
	virtual ~CGruppiProcedureICD9UseDlg();

	enum { IDD = IDD_GRUPPIPROCEDUREICD9_USE_DLG };

	long m_lReturn;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CListBox m_ctrlListaGruppi;
	long m_lTipoEsame;
	CEsamiView* m_pEsamiView;

};

#endif /* _GRUPPIPROCEDUREICD9USEDLG_H_ */