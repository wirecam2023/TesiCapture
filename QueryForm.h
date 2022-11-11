#pragma once

#include "EndoxListBox.h"
#include "EndoxResizableDlg.h"
#include "QueryUtility.h"

#define WM_QUERY_FORM_CHANGED	WM_USER + 0x2000
#define WM_QUERY_FORM_RESET		WM_USER + 0x2001
#define WM_QUERY_FORM_OK		WM_USER + 0x2002

class CQueryFormRemember
{

public:

	CQueryFormRemember()
	{
		m_bEscludi = FALSE;
	}

	void Reset()
	{
		m_listSelected.RemoveAll();
	}

	void WriteToFile(LPCTSTR szSection, LPCTSTR szKeyname, LPCTSTR szFile)
	{
		CString strNumbers, strTmp;
		for (POSITION pos = m_listSelected.GetHeadPosition(); pos;)
		{
			strTmp.Format("%li;", m_listSelected.GetNext(pos));
			strNumbers += strTmp;
		}

		CString strKeyname;
		strKeyname.Format("%s_Selected", szKeyname);
		WritePrivateProfileString(szSection, strKeyname, strNumbers, szFile);

		strTmp.Format("%li", m_bEscludi);
		strKeyname.Format("%s_Escludi", szKeyname);
		WritePrivateProfileString(szSection, strKeyname, strTmp, szFile);
	}

	void ReadFromFile(LPCTSTR szSection, LPCTSTR szKeyname, LPCTSTR szFile)
	{
		m_listSelected.RemoveAll();

		CString strKeyname, strTemp;
		strKeyname.Format("%s_Selected", szKeyname);
		GetPrivateProfileString(szSection, strKeyname, "", strTemp.GetBuffer(1024), 1024, szFile);
		strTemp.ReleaseBuffer();

		int nLastPos = 0, nPos = 0;
		while (nPos != -1)
		{
			nPos = strTemp.Find(";", nLastPos);
			if (nPos != -1)
			{
				m_listSelected.AddTail(atol(strTemp.Mid(nLastPos, nPos - nLastPos)));
				nLastPos = nPos + 1;
			}
		}

		strTemp.Empty();
		strKeyname.Format("%s_Escludi", szKeyname);
		GetPrivateProfileString(szSection, strKeyname, "", strTemp.GetBuffer(1024), 1024, szFile);
		strTemp.ReleaseBuffer();

		m_bEscludi = atol(strTemp);
	}

protected:
	CList<long> m_listSelected;
	BOOL m_bEscludi;

	friend class CQueryForm;
};

class CQueryForm : protected CEndoxResizableDlg, public CQueryUtility
{
	DECLARE_DYNAMIC(CQueryForm)

public:

	CQueryForm(BOOL bMultiSelect = TRUE, BOOL bFreeFieldAccepted = FALSE);

    enum { IDD = IDD_QUERY_FORM };
	enum { IDD_SINGLE = IDD_QUERY_FORM_SINGLE };

	void SetMultiSelect(BOOL bMultiSelect, BOOL bFreeFieldAccepted = FALSE);
	BOOL CreateForm(UINT iPlace, CWnd* pParentWnd, CString strTitle);

	void SetFiltro(long lFiltro1ID, long lFiltro2ID, CString strName);
	void SetQuery(CString strQuery);
	void GetFilterString(CString* pFilter, CString strDatabaseField);
	void GetFilterStringText(CString* pFilter, CString strDatabaseField);

	void Enable(BOOL bEnable);
	void Empty();

	HWND GetSafeHwnd();
	CWnd* GetCWnd();

	BOOL ShowWindow(int nCmdShow);

	BOOL GetItemSelectedFree();
	long GetItemSelectedID();
	void SetItemSelectedID(long lID);

	void SetItemSelected(const CList<long>* pList);
	void GetItemSelected(CList<long>* pList);

	CString GetItemSelectedCode();
	CString GetItemSelectedDesc();
	CString GetItemSelectedDesc2();
	void SetItemSelectedDesc(CString str);

	void GetDescriptionForPrint(CString* pDescription);

	void StoreData(CQueryFormRemember* pObj);
	void LoadData(CQueryFormRemember* pObj);

	void SetNotifyParentWnd(BOOL bNotify) { m_bNotifyParentWnd = bNotify; }
	
	void SetFocusOnCode() { GetDlgItem(IDC_EDIT_CODICE)->SetFocus(); }

	CString GetTitle() { return m_strTitle; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	LRESULT OnNotifyDeleteStringListBox(WPARAM wParam, LPARAM lParam);
	LRESULT OnNotifyEmptyListBox(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnChangeDescription();
	afx_msg void OnEnChangeCode();
	afx_msg void OnCheckButtonEscludi();
	afx_msg void OnCheckButtonTutti();
	afx_msg void OnButtonDescrizione();
	afx_msg void OnButtonCodice();
	virtual BOOL OnInitDialog();
	virtual void OnCancel() {}
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlCheckTutti, m_ctrlCheckEscludi;
	CButton m_ctrlButtonCodice, m_ctrlButtonDescrizione;
	CEndoxListBox m_ctrlList;
	CString m_strQuery, m_strTitle;
	BOOL m_bMultiSelect, m_bFreeFieldAccepted;

	BOOL m_bChangingCode, m_bChangingDescription;

	long m_lItemSelected;
	CString m_strItemSelected;
	BOOL m_bItemSelectedFree;

	BOOL m_bNotifyParentWnd;

	long m_lFiltro1ID, m_lFiltro2ID;
	CString m_strName;

private:
	BOOL ExecuteSearch(CString strQueryEqual, CString strQueryLike);

	BOOL SearchByDescription();
	BOOL SearchByCode();

	BOOL IsItemPresent(long lID);

	class CTableSet : public CAMBaseSet
	{
	public:
		CTableSet(BOOL bAddFilter1, BOOL bAddFilter2);

		long GetID(DWORD dwIndex);
		CString GetCodice(DWORD dwIndex);
		CString GetDescrizione(DWORD dwIndex);
		BOOL GetLibero(DWORD dwIndex);
		long GetFiltro1(DWORD dwIndex);
		long GetFiltro2(DWORD dwIndex);

	private:
		virtual void DoBulkFieldExchange(CFieldExchange* pFX);

		long* m_pID;
		LPTSTR m_pCodice;
		LPTSTR m_pDescrizione;
		BOOL* m_pLibero;
		long* m_pFilter1ID;
		long* m_pFilter2ID;

		long* m_pIDLength;
		long* m_pCodiceLength;
		long* m_pDescrizioneLength;
		long* m_pLiberoLength;
		long* m_pFilter1IDLength;
		long* m_pFilter2IDLength;

		BOOL m_bAddFilter1, m_bAddFilter2;
	};

	friend class CQueryFormRemember;
};