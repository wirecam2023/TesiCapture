#ifndef _NUMERONUOVISTADIDLG_H_
	#define _NUMERONUOVISTADIDLG_H_

class CNumeroNuoviStadiDlg : public CDialog
{
	DECLARE_DYNAMIC(CNumeroNuoviStadiDlg)

public:

	CNumeroNuoviStadiDlg(CWnd* pParent);
	virtual ~CNumeroNuoviStadiDlg();

	enum { IDD = IDD_NUMERO_NUOVI_STADI };

	long GetNumero();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CSpinButtonCtrl m_ctrlSpin;

	CStaticLocalize m_ctrlStaticLabel;

	//

	long m_lNumero;

};

#endif /* _NUMERONUOVISTADIDLG_H_ */