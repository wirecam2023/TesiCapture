#ifndef _VISUALIZZATORELOGDLG_H_
	#define _VISUALIZZATORELOGDLG_H_

#include "EndoxResizableDlg.h"

class CVisualizzatoreLogDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CVisualizzatoreLogDlg)

public:

	CVisualizzatoreLogDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL bLogImportCasi);
	virtual ~CVisualizzatoreLogDlg();

	enum { IDD = IDD_LOG_ESAME };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:

	void RiempiLista();
	void RiempiListaImportCasi();

	//

	CEsamiView* m_pEsamiView;

	CButtonLocalize m_ctrlBtnOK;
	CListCtrl m_ctrlList;

	BOOL m_bLogImportCasi;

};

#endif /* _VISUALIZZATORELOGDLG_H_ */