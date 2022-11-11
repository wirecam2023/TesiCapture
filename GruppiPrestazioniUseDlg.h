#ifndef _GRUPPIPRESTAZIONIUSEDLG_H_
	#define _GRUPPIPRESTAZIONIUSEDLG_H_

#include "afxwin.h"

class CGruppiPrestazioniUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CGruppiPrestazioniUseDlg)

public:

	CGruppiPrestazioniUseDlg(CWnd* pParent, CEsamiView* pEsamiView, long lTipoEsame);
	virtual ~CGruppiPrestazioniUseDlg();

	enum { IDD = IDD_GRUPPIPRESTAZIONI_USE_DLG };

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

#endif /* _GRUPPIPRESTAZIONIUSEDLG_H_ */