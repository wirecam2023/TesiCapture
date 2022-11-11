#ifndef _FLEURYSCELTARIAPERTURADLG_H_
	#define _FLEURYSCELTARIAPERTURADLG_H_

class CFleurySceltaRiaperturaDlg : public CDialog
{
	DECLARE_DYNAMIC(CFleurySceltaRiaperturaDlg)

public:

	CFleurySceltaRiaperturaDlg(CWnd* pParent, CString p_sFichaItem);
	virtual ~CFleurySceltaRiaperturaDlg();

	enum { IDD = IDD_FLEURY_SCELTARIAPERTURA };
	
	CString m_sFicha;
	CString m_sItem;
	BOOL m_bImprimirLaudo = FALSE;
	BOOL m_bImprimirImagens = FALSE;
	BOOL m_bImportarExame = FALSE;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CButtonLocalize m_ctrlBtnAlterarExame;
	CButtonLocalize m_ctrlBtImprimirLaudo;
	CButtonLocalize m_ctrlBtImprimirImagens;
	CButtonLocalize m_ctrlBtnCancel;

	CStaticLocalize m_ctrlStatic00;

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnImprimir();
	afx_msg void OnBnClickedBtnImagens();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnImprimirTodos();
};

#endif /* _FLEURYSCELTARIAPERTURADLG_H_ */