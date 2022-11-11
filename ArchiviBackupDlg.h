#ifndef _ARCHIVIBACKUPDLG_H_
	#define _ARCHIVIBACKUPDLG_H_

#include "ExtListBox.h"
#include "DLL_Imaging\h\AmLocalize.h"

class CComboRAOSet;
class CEsamiDoc;

struct ArchiveElement
{
	long lIDArchivio;
	CString sDescrizione;
	CString sPathImage;
	CString sPathThumb;
	CString sPathImageWeb;
	CString sPathThumbWeb;
	BOOL bPrimario;
};

class CArchiviBackupDlg : public CDialog
{

public:

	CArchiviBackupDlg(CWnd* pParent, CEsamiDoc* pEsamiDoc);
	virtual ~CArchiviBackupDlg();

	enum { IDD = IDD_ARCHIVIBACKUP };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnArchiveDelete();
	afx_msg void OnArchiveModify();
	afx_msg void OnArchiveNew();
	afx_msg void OnArchiveRefresh();
	afx_msg void OnArchiveUpdate();
	afx_msg void OnLbnDblclkLista();
	afx_msg void OnSelchangeLista();
	afx_msg void OnBnClickedBtnPathImm();
	afx_msg void OnBnClickedBtnPathMin();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnPathPdf();
	afx_msg void OnBnClickedBtnPathAllegatiPaz();
	afx_msg void OnBnClickedBtnPathAllegatiEsa();
	afx_msg void OnBnClickedChkPacsAttivo();

private:

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlPrimario;

	CEsamiDoc* m_pEsamiDoc;

	CExtListBox m_ctrlLista;

	CStaticLocalize m_ctrlStatic00;
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

	CButtonLocalize m_ctrlChkPacsAttivo;
	CButtonLocalize m_ctrlChkPacsSincronizza;
	CEdit m_ctrlEdtPacsRetrieveURL;

	//

	CList<ArchiveElement*> m_listArchivi;
	ArchiveElement* getArchiveInfo();

	//

	long m_lID;
	CString m_sDescrizioneArchivio;
	CString m_sImagePath;
	CString m_sThumbPath;
	CString m_sImagePathWeb;
	CString m_sThumbPathWeb;

	int m_lSavedPosition;
	BOOL m_bAddNew;
	BOOL m_bModify;

	int m_nItemPressed;
	int m_nItemCount;

	void RiempiListaArchivi();

};

#endif /* _ARCHIVIBACKUPDLG_H_ */