#ifndef _SELEZIONEANNODLG_H_
	#define _SELEZIONEANNODLG_H_

class CSelezioneAnnoDlg : public CDialog
{

	DECLARE_DYNAMIC(CSelezioneAnnoDlg)

public:

	CSelezioneAnnoDlg(CWnd* pParent);
	virtual ~CSelezioneAnnoDlg();

	enum { IDD = IDD_SELEZIONE_ANNO };

	long GetAnno();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CSpinButtonCtrl m_ctrlSpin;

	long m_lAnno;

};

#endif /* _SELEZIONEANNODLG_H_ */