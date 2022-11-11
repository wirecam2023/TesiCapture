#ifndef _IMPORTACASODLG_H_
	#define _IMPORTACASODLG_H_
#include "afxcmn.h"

class CImportaCasoDlg : public CDialog
{
	DECLARE_DYNAMIC(CImportaCasoDlg)

public:

	CImportaCasoDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CImportaCasoDlg();

	enum { IDD = IDD_IMPORTACASO };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void CopiaAccessoriEsame(long lIDEsameOrigine, long lIDEsameDestinazione);
	void CopiaCodificaDiagnosiEsame(long lIDEsameOrigine, long lIDEsameDestinazione);
	BOOL ImportaImmaginiFilmati(long lIDEsameOrigine, long lIDEsameDestinazione);

	void RiempiLista();

	//

	CButtonLocalize m_ctrlBtnCancel;

	CListCtrl m_ctrlList;

	//

	CEsamiView* m_pEsamiView;

};

#endif /* _IMPORTACASODLG_H_ */