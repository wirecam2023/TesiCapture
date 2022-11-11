#ifndef _ENDOXDYNFORM_H_
	#define _ENDOXDYNFORM_H_

#include "EndoxResizableDlg.h"

#define RGB_OBBLIG_GIALLO RGB(255, 255, 127)
#define RGB_OBBLIG_VERDE RGB(127, 255, 127)

class CEndoxDynForm : public CEndoxResizableDlg
{

public:

	CEndoxDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CEndoxDynForm();

	BOOL CreateChildForm(UINT nID, CWnd* pParent, CRect rectFrame);
	virtual long GetContenuto() = 0;
	virtual BOOL CampoObbligatorioValido() = 0;
	void EvidenziaCampoObbligatorioEx(COLORREF crColor);

	CEsamiView* m_pEsamiView;
	long m_lColore;
	long m_lIDFaseBlocco;

protected:

	virtual void OnCancel();
	virtual void OnOK();
    
	DECLARE_MESSAGE_MAP()

	virtual afx_msg LRESULT OnFormAnnullaEsame(WPARAM wParam = 0, LPARAM lParam = 0);
	virtual afx_msg LRESULT OnFormAnnullaPaziente(WPARAM wParam = 0, LPARAM lParam = 0);
	virtual afx_msg LRESULT OnFormClone(WPARAM wParam = 0, LPARAM lParam = 0 /* passare il contatore dell'esame da ricopiare */);
	virtual afx_msg LRESULT OnFormLoad(WPARAM wParam = 0, LPARAM lParam = 0);
	virtual afx_msg LRESULT OnFormReadOnly(WPARAM wParam = 0 /* passare TRUE o FALSE */, LPARAM lParam = 0);
	virtual afx_msg LRESULT OnFormReset(WPARAM wParam = 0, LPARAM lParam = 0);
	virtual afx_msg LRESULT OnFormSave(WPARAM wParam = 0, LPARAM lParam = 0);
	virtual afx_msg LRESULT OnFormSearchNew(WPARAM wParam = 0 /* passare l'indirizzo della stringa WHERE */, LPARAM lParam = 0 /* passare l'indirizzo della stringa FROM */);

	COLORREF m_crCampoObbligatorio;
};

#endif /* _ENDOXDYNFORM_H_ */