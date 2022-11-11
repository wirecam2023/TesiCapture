#pragma once

class CVitalSignPdfWaitingDlg : public CDialog
{
	DECLARE_DYNAMIC(CVitalSignPdfWaitingDlg)

public:
	CVitalSignPdfWaitingDlg(CWnd* pParentWnd, long lIDHeaderMisurazione, long oldIdPdf);
	virtual ~CVitalSignPdfWaitingDlg();

	enum { IDD = IDD_VS_PDFWAITING };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()

private:
	
	long m_lIDHeaderMisurazione;
	long m_lOldIdPdf;

	BOOL PdfChanged();

};

