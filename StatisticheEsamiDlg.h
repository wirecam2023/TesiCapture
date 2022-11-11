#ifndef _STATISTICHEESAMIDLG_H_
	#define _STATISTICHEESAMIDLG_H_

#include "DLL_Imaging\h\AMListCtrl.h"

#include "EndoxResizableDlg.h"

#include "msxml6.tlh"

class CStatisticheEsamiDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CStatisticheEsamiDlg)

public:

	CStatisticheEsamiDlg(CWnd* pParent, long lAnno);
	virtual ~CStatisticheEsamiDlg();

	enum { IDD = IDD_STATISTICHE_ESAMI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void AggiungiEsame(long lData, long lIDEsame, long lIDMedico);
	long GetValoreCella(long lMese, long lEsame, long lMedico);
	BOOL CreateExcel(CString message, CString &ret);	
	void AddCell(MSXML2::IXMLDOMDocument3Ptr pxmlDocument, MSXML2::IXMLDOMElementPtr pParent, long rowIndex, long colIndex, CString value, BOOL bold=FALSE);

	CAMEditComboListCtrl m_ctrlList;
	CButtonLocalize m_ctrlBtnOK, m_ctrlBtnExport;
	CTabCtrl m_ctrlTab;

	BOOL m_bStatisticaEsamiChiusi;

	long m_lNumeroEsami;
	long* m_pArrayEsami;

	long m_lNumeroMedici;
	long* m_pArrayMedici;

	long* m_pNumeriTridimensionale;

	long m_lAnno;

	MSXML2::IXMLDOMDocument3Ptr m_pxmlDocument;

public:
	afx_msg void OnBnClickedExport();
};

#endif /* _STATISTICHEESAMIDLG_H_ */