#ifndef _LISTAOSSERVEZIONIDLG_H_
	#define _LISTAOSSERVEZIONIDLG_H_

#include "EndoxResizableDlg.h"
#include "OsservazioniListCtrl.h"

#define COL_DATAES 0
#define COL_TIPOES 1
#define COL_ORGANO 2
#define COL_OSSERV 3
#define COL_SNOCOD 4
#define COL_SNODES 5
#define COL_LASTEM 6

class CEsamiView;
class CListaCodificaDiagnosiEsameSet;
class CListaSnomedSet;

typedef struct Singolo_Esame
{
	long lID;
	long lData;
	CString sDescrizione;
} SINGOLO_ESAME;

class CListaOsservazioniDlg : public CEndoxResizableDlg
{

public:

	CListaOsservazioniDlg(CWnd* pParent, CEsamiView* pEsamiView, long lIDPaziente, CString sPaziente, BOOL bLanciatoDaReferto);
	~CListaOsservazioniDlg();

	enum { IDD = IDD_LISTA_CONCLUSIONI };

	long GetIDEsame();

protected:

	void DoDataExchange(CDataExchange* pDX);
	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedExport();
	afx_msg void OnBnClickedStampa();
	afx_msg void OnDblclkListEsami(NMHDR* pNMHDR, LRESULT* pResult);

private:

	CEsamiView* m_pEsamiView;
	long m_lIDPaziente;
	long m_lIDEsame;
	CString m_sPaziente;
	BOOL m_bReferto;

	//

	void RiempiLista();
	void RiempiListaReferto();
	void RiempiListaOsservazioni();
	void RiempiListaDiagnosiSnomed();

	void InsertDiagnosiSnomed(long lIDEsame, CListaCodificaDiagnosiEsameSet* pDia, CListaSnomedSet* pSno, int& nItem);

	//

	COsservazioniListCtrl m_ctrlListEsami;
	CButtonLocalize m_ctrlButtonOK;

	CBitmapButton m_BtnStampa;
	CBitmapButton m_BtnExport;

};

#endif /* _LISTAOSSERVEZIONIDLG_H_ */