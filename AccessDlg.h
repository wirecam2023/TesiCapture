#ifndef _CACCESSDLG_H_
	#define _CACCESSDLG_H_

class CAccessDlg : public CDialog
{
public:

    CAccessDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_ACCESS };

protected:

    virtual void DoDataExchange(CDataExchange *pDX);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
};

#endif  /* _CACCESSDLG_H_ */
