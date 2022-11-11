#ifndef _IMAGEORDERDLG_H_
	#define _IMAGEORDERDLG_H_

class CImageOrderDlg : public CDialog
{
	DECLARE_DYNAMIC(CImageOrderDlg)

public:

	CImageOrderDlg(CWnd* pParent);
	virtual ~CImageOrderDlg();

	enum { IDD = IDD_IMAGE_ORDER };

	int GetNewPos();
	void SetParam(int nPosition, int nMax);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CSpinButtonCtrl m_ctrlSpin;

	int m_nPosition;
	int m_nMax;

};

#endif /* _IMAGEORDERDLG_H_ */