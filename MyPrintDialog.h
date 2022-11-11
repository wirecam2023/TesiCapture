#ifndef _MYPRINTDIALOG_H_
	#define _MYPRINTDIALOG_H_

class CMyPrintDialog : public CPrintDialog
{

	DECLARE_DYNAMIC(CMyPrintDialog)

public:

	CMyPrintDialog(BOOL bPrintSetupOnly, DWORD dwFlags = PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS | PD_HIDEPRINTTOFILE | PD_NOSELECTION, CWnd* pParentWnd = NULL);

	virtual ~CMyPrintDialog();

	virtual BOOL OnInitDialog();

protected:

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);
};

#endif /* _MYPRINTDIALOG_H_ */