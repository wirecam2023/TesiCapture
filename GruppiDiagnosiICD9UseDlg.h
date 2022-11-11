#ifndef _GRUPPIDIAGNOSIICD9USEDLG_H_
	#define _GRUPPIDIAGNOSIICD9USEDLG_H_

#include "afxwin.h"

class CGruppiDiagnosiICD9UseDlg : public CDialog
{
	DECLARE_DYNAMIC(CGruppiDiagnosiICD9UseDlg)

public:

	CGruppiDiagnosiICD9UseDlg(CWnd* pParent, CEsamiView* pEsamiView, long lTipoEsame);
	virtual ~CGruppiDiagnosiICD9UseDlg();

	enum { IDD = IDD_GRUPPIDIAGNOSIICD9_USE_DLG };

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

#endif /* _GRUPPIDIAGNOSIICD9USEDLG_H_ */