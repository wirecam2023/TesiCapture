#include "stdafx.h"
#include "Endox.h"
#include "SpellCheckerDlg.h"

#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSpellCheckerDlg, CDialog)

CSpellCheckerDlg::CSpellCheckerDlg()
	: CDialog(CSpellCheckerDlg::IDD, NULL)
{
	m_pTextControl = NULL;
	m_bAlreadyCreated = FALSE;
}

CSpellCheckerDlg::~CSpellCheckerDlg()
{
}

void CSpellCheckerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WSPELLCTRL, m_ctrl);
}

BEGIN_EVENTSINK_MAP(CSpellCheckerDlg, CDialog)
	// ON_EVENT(CSpellCheckerDlg, IDC_WSPELLCTRL, 1 /* MisspelledWord */, OnMisspelledWordWspell, VTS_NONE)
	// ON_EVENT(CSpellCheckerDlg, IDC_WSPELLCTRL, 2 /* WordWithDigits */, OnWordWithDigitsWspell, VTS_NONE)
	// ON_EVENT(CSpellCheckerDlg, IDC_WSPELLCTRL, 3 /* MixedCaseWord */, OnMixedCaseWordWspell, VTS_NONE)
	ON_EVENT(CSpellCheckerDlg, IDC_WSPELLCTRL, 4 /* DoubledWord */, OnDoubledWordWspell, VTS_NONE)
	// ON_EVENT(CSpellCheckerDlg, IDC_WSPELLCTRL, 5 /* Capitalization */, OnCapitalizationWspell, VTS_NONE)
	// ON_EVENT(CSpellCheckerDlg, IDC_WSPELLCTRL, 6 /* ConditionallyChangeWord */, OnConditionallyChangeWordWspell, VTS_NONE)
	// ON_EVENT(CSpellCheckerDlg, IDC_WSPELLCTRL, 7 /* EndOfText */, OnEndOfTextWspell, VTS_NONE)
END_EVENTSINK_MAP()

BEGIN_MESSAGE_MAP(CSpellCheckerDlg, CDialog)
END_MESSAGE_MAP()

BOOL CSpellCheckerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!theApp.m_sControlloOrtograficoPathDizionarioUtente.IsEmpty())
	{
		if (_access(theApp.m_sControlloOrtograficoPathDizionarioUtente, 00) == 0)
		{
			CString strFiles;
			strFiles.Format("%s\\userdic.tlx,%s\\correct.tlx", 
				            theApp.m_sControlloOrtograficoPathDizionarioUtente, 
							theApp.m_sControlloOrtograficoPathDizionarioUtente);

			if (_access(theApp.m_sControlloOrtograficoPathDizionarioUtente + "\\userdic.tlx", 00) == 0 && _access(theApp.m_sControlloOrtograficoPathDizionarioUtente + "\\correct.tlx", 00) == 0)
			{
				m_ctrl.SetUserDictionaryFiles(strFiles);
			}
			else
			{
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_ERROR_FILE_NOT_FOUND), strFiles);
				theApp.AfxMessageBoxEndo(strError);
			}
		}
		else
		{

			// ignora o erro de dicionário se estiver em modo _DEBUG
#ifndef _DEBUG
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_WSPELL_DICTIONARY_PATH_WRONG), MB_ICONSTOP);
#endif

		}
	}

	switch(theApp.m_nLanguage)
	{
		case loc_eng: // inglese //
		{
			m_ctrl.SetMainDictionaryFiles("sscebr.tlx,sscebr2.clx");
			break;
		}
		case loc_esp: // spagnolo //
		{
			m_ctrl.SetMainDictionaryFiles("sscesp.tlx,sscesp2.clx");
			break;
		}
		case loc_por: // portoghese //
		{
			m_ctrl.SetMainDictionaryFiles("sscepb.tlx,sscepb2.clx");
			break;
		}
		default: // italiano //
		{
			m_ctrl.SetMainDictionaryFiles("ssceit.tlx,ssceit2.clx");
			break;
		}
	}

	m_ctrl.SetCatchDoubledWords(TRUE);

	if (m_pTextControl)
		m_ctrl.SetTextControlHWnd((long)m_pTextControl->GetSafeHwnd());

	return TRUE;
}

void CSpellCheckerDlg::OnDoubledWordWspell()
{
}

BOOL CSpellCheckerDlg::Create(CWnd* pParentWnd)
{
	if (m_bAlreadyCreated)
		return GetSafeHwnd() ? TRUE : FALSE;

	m_pParentWnd = pParentWnd;
	m_bAlreadyCreated = TRUE;

	CLSID clsid;
	HRESULT hr = ::CLSIDFromProgID(L"WSPELL.WSpellCtrl.3", &clsid);
	if (hr != S_OK)
		return FALSE;

	return CDialog::Create(CSpellCheckerDlg::IDD, m_pParentWnd);
}

void CSpellCheckerDlg::SetTextControl(CWnd* pTextControl)
{
	if (m_pTextControl && pTextControl)
		return;

	m_ctrl.SetTextControlHWnd((long)pTextControl->GetSafeHwnd());
	m_pTextControl = pTextControl;
}

BOOL CSpellCheckerDlg::Destroy()
{
	m_bAlreadyCreated = FALSE;
	return GetSafeHwnd() ? DestroyWindow() : FALSE;
}

void CSpellCheckerDlg::Check()
{
	if (!m_pTextControl || !m_pTextControl->GetSafeHwnd() || !m_ctrl.GetSafeHwnd())
		return;

	m_ctrl.CheckBackgroundNotify((long)m_pTextControl->GetSafeHwnd(),
							     FALSE, 
							     FALSE, 
							     FALSE, 
							     TRUE,
							     RGB(255,0,0));
}

void CSpellCheckerDlg::Recheck()
{
	if (!m_pTextControl || !m_pTextControl->GetSafeHwnd() || !m_ctrl.GetSafeHwnd())
		return;

	m_ctrl.CheckBackgroundRecheck((long)m_pTextControl->GetSafeHwnd(),
							      FALSE, 
							      FALSE, 
							      FALSE, 
							      TRUE,
							      RGB(255,0,0));
}

void CSpellCheckerDlg::Menu(CPoint point)
{
	if (!m_pTextControl || !m_pTextControl->GetSafeHwnd() || !m_ctrl.GetSafeHwnd())
		return;

	m_ctrl.CheckBackgroundMenu((long)m_pTextControl->GetSafeHwnd(),
							   point.x, 
							   point.y, 
							   0, 
							   FALSE, 
							   FALSE, 
							   FALSE, 
							   TRUE,
							   RGB(255,0,0));
}

void CSpellCheckerDlg::DeleteUnderline()
{
	if (!m_pTextControl || !m_pTextControl->GetSafeHwnd())
		return;

	m_pTextControl->SendMessage(WM_USER+130, /*TX_SETFONTATTR*/ 0x00020000 /*FA_UL_NOREDZIGZAG*/);
}

void CSpellCheckerDlg::ImportWordsFromExcel(CString strFile)
{
	if (GetSafeHwnd() == NULL)
		return;

	CDatabase db;
	CRecordset set(&db);

	CString strConnect;
	strConnect.Format("DRIVER={Microsoft Excel Driver (*.xls)};DBQ=%s", strFile);

	UINT iWordsInserted = 0;

	try
	{
		db.OpenEx(strConnect, CDatabase::noOdbcDialog);

		SQLCHAR szTableName[255];
		SQLHANDLE handle;
		if (SQLAllocHandle(SQL_HANDLE_STMT, db.m_hdbc, &handle) == SQL_SUCCESS)
		{
			SQLRETURN rc = SQLTables(handle,
									 NULL,
									 0,
									 NULL,
									 0,
									 NULL, //(SQLCHAR*)strTable.GetBuffer(strTable.GetLength()),
									 0, //strTable.GetLength(),
									 NULL,
									 0);

			if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) 
			{
				SQLINTEGER cbName;
				SQLBindCol(handle, 3, SQL_C_CHAR, szTableName, 255, &cbName);
				if (SQLFetch(handle) != SQL_NO_DATA_FOUND)
					_strupr_s((LPTSTR)szTableName, 255);
			}
		}

		if (handle != NULL)
			SQLFreeHandle(SQL_HANDLE_STMT, handle);

		CString strQuery;
		strQuery.Format("SELECT * FROM [%s]", szTableName);
		set.Open(CRecordset::snapshot, strQuery);
		while (!set.IsEOF())
		{
			CString strWord;
			set.GetFieldValue((short)0, strWord);
			m_ctrl.AddToUserDictionary("userdic.tlx", strWord, 105, "");
			iWordsInserted++;
			set.MoveNext();
		}
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}

	if (set.IsOpen())
		set.Close();
	if (db.IsOpen())
		db.Close();

	CString str;
	str.Format(theApp.GetMessageString(IDS_WSPELL_ADD_WORDS), iWordsInserted);
	theApp.AfxMessageBoxEndo(str, MB_ICONINFORMATION);
}