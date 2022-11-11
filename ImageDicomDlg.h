#ifndef _IMAGEDICOMDLG_H_
	#define _IMAGEDICOMDLG_H_

#include "EndoxResizableDlg.h"

class CImageDicomDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CImageDicomDlg)

public:

	CImageDicomDlg(CWnd* pParent, CString strDicomFileName);
	virtual ~CImageDicomDlg();

	enum { IDD = IDD_IMAGE_DICOM };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:

	CString m_sDicomFileName;
	UINT m_iDicomViewerID;

	CStatic m_ctrlStaticFrame;
	CButtonLocalize m_ctrlBtnOK;

};

#endif /* _IMAGEDICOMDLG_H_ */