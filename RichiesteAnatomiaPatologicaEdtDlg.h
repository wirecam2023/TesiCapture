#ifndef _RICHIESTEANATOMIAPATOLOGICAEDTDLG_H_
	#define _RICHIESTEANATOMIAPATOLOGICAEDTDLG_H_

class CAnatomiaPatologicaRichListCtrl;
class CEsamiView;

class CRichiesteAnatomiaPatologicaEdtDlg : public CDialog
{
	DECLARE_DYNAMIC(CRichiesteAnatomiaPatologicaEdtDlg)

public:

	CRichiesteAnatomiaPatologicaEdtDlg(CWnd* pParent, CEsamiView* pEsamiView, CAnatomiaPatologicaRichListCtrl* pListCtrl);
	virtual ~CRichiesteAnatomiaPatologicaEdtDlg();

	enum { IDD = IDD_RICHIESTEANATOMIAPATOLOGICA_EDT_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedCheckSpeditoRitirato();
	afx_msg void OnBnClickedCheckVerificato();

private:

	CEsamiView* m_pEsamiView;
	CAnatomiaPatologicaRichListCtrl* m_pList;
	int m_nListItem;
	long m_lIDEsame;

	int m_nSpedireRitirare;
	BOOL m_bRefertato;
	BOOL m_bVerificato;
	int m_nVerificatoMedico;
	BOOL m_bSpeditoRitirato;
	CString m_sDataVerificato;
	CString m_sDataSpeditoRitirato;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
	CStaticLocalize m_ctrlStatic05;
	CStaticLocalize m_ctrlStatic06;
	CStaticLocalize m_ctrlStatic07;
	CStaticLocalize m_ctrlStatic08;
	CStaticLocalize m_ctrlStatic09;
	CStaticLocalize m_ctrlStatic10;

	CComboBox m_ctrlComboMedico;
};

#endif /* _RICHIESTEANATOMIAPATOLOGICAEDTDLG_H_ */