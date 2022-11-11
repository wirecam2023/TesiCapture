#ifndef _OCCUPAZIONEGIORNALIERADLG_H_
	#define _OCCUPAZIONEGIORNALIERADLG_H_

#include <afxdtctl.h>

#include "CustomDate.h"

class COccupazioneGiornalieraDlg : public CDialog
{
	DECLARE_DYNAMIC(COccupazioneGiornalieraDlg)

public:

	COccupazioneGiornalieraDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~COccupazioneGiornalieraDlg();

	enum { IDD = IDD_OCCUPAZIONE_GIORNALIERA };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnDtnDateTimeChangeDateTimePicker(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void SetDate(CCustomDate dateFrom, CCustomDate dateTo);

	//

	CButtonLocalize m_ctrlBtnChiudi;

	CDateTimeCtrl m_ctrlDate;

	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic06;
	CStaticLocalize m_ctrlStatic09;
	CStaticLocalize m_ctrlStatic12;

	//

	CEsamiView* m_pEsamiView;

};

#endif /* _OCCUPAZIONEGIORNALIERADLG_H_ */