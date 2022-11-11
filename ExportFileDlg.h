#ifndef _EXPORTFILEDLG_H_
	#define _EXPORTFILEDLG_H_

class CExportFileDlg : public CDialog
{

public:

	CExportFileDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_EXPORT_FILE };

	int		m_nTipoExport;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK();
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonOK, m_ctrlButtonCancel, m_ctrlButton1, m_ctrlButton2, m_ctrlButton3;
	CStaticLocalize m_ctrlStaticGroup;

};

#endif /* _EXPORTFILEDLG_H_ */