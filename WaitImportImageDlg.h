#ifndef _WAITIMPORTIMAGEDLG_H_
	#define _WAITIMPORTIMAGEDLG_H_

class CWaitImportImageDlg : public CDialog
{

	DECLARE_DYNAMIC(CWaitImportImageDlg)

public:

	CWaitImportImageDlg(CWnd* pParent, CImgManager* pImgManager, CStringList* pImgList);
	virtual ~CWaitImportImageDlg();

	enum { IDD = IDD_WAITING };

	static BOOL m_sbError;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	LRESULT OnDestroyWaitImportImageDlg(WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateProgress(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	struct tagTHREAD
	{
		CStringList* pImgList;
		CImgManager* pImageManager;
		HWND hWndParent;
	};

	//

	void SetProgress(UINT idString, UINT iMax);
	static UINT Thread(LPVOID pParam);

	//

	CAnimateCtrl m_ctrlAnim;
	CProgressCtrl m_ctrlProgress;

	//

	tagTHREAD m_ThreadParam;

	UINT m_idString;
	UINT m_iMax;

};

#endif /* _WAITIMPORTIMAGEDLG_H_ */