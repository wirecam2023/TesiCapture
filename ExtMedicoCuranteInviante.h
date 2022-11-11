#ifndef _EXTMEDICOCURANTEINVIANTE_H_
	#define _EXTMEDICOCURANTEINVIANTE_H_

class CEsamiView;
class CMediciCurantiInviantiSet;
class CBaseSet;

class CExtMedicoCuranteInviante : public CEdit
{
	DECLARE_DYNCREATE (CExtMedicoCuranteInviante)

public:

	CExtMedicoCuranteInviante();
	~CExtMedicoCuranteInviante();

	//

	void SetParams(CWnd* pParentView, CBaseSet* pSet, CString* pStrOutput, long* pLongOutput, int nMaxLen, int nIndexMode, long lCurantiInvianti);
	void SetStrings(CString* pStrIndirizzo, CString* pStrTelefono, CString* pStrEmail);

	//

	//long m_lIDMedico;

	CString m_strRicerca;
	CString m_strRicercaView;

protected:

	DECLARE_MESSAGE_MAP()

	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

private:

	BOOL OpenComboMenu(BOOL& bIsOK, CString strValue);
	BOOL OpenDialog(BOOL bUpdate, CString strValue);

	//

	CWnd* m_pParentView;
	CBaseSet* m_pSet;
	CString* m_pStrOutput;
	long* m_pLongOutput;
	long m_nExtMode;
	long m_lCurantiInvianti;

	CString* m_pStrIndirizzo;
	CString* m_pStrTelefono;
	CString* m_pStrEmail;

};

#endif /* _EXTMEDICOCURANTEINVIANTE_H_ */