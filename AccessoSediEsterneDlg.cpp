#include "stdafx.h"
#include "Endox.h"
#include "AccessoSediEsterneDlg.h"

#include "DLL_Imaging\h\AmLogin.h"

#include "Common.h"
#include "DatabasesSet.h"
#include "UOSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAccessoSediEsterneDlg, CDialog)

CAccessoSediEsterneDlg::CAccessoSediEsterneDlg(CWnd* pParent)
	: CDialog(CAccessoSediEsterneDlg::IDD, pParent)
{
	CString sConnect = theApp.m_dbEndox.GetDecryptedConnectionString();
	sConnect.MakeUpper();
	m_bIsOracle = sConnect.Find("ORACLE") > 0;
}

CAccessoSediEsterneDlg::~CAccessoSediEsterneDlg()
{
}

BEGIN_MESSAGE_MAP(CAccessoSediEsterneDlg, CDialog)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)

END_MESSAGE_MAP()

void CAccessoSediEsterneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

void CAccessoSediEsterneDlg::OnCancel()
{
	CDialog::OnCancel();
}

BOOL CAccessoSediEsterneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, theApp.GetMessageString(IDS_DESCRIZIONE));

	//

	RiempiLista();

	//

	theApp.LocalizeDialog(this, CAccessoSediEsterneDlg::IDD, "AccessoSediEsterneDlg");
	return TRUE;
}

void CAccessoSediEsterneDlg::OnOK()
{
	if (m_ctrlBtnOK.IsWindowEnabled())
	{
		BeginWaitCursor();

		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nCurSel = m_ctrlList.GetNextSelectedItem(pos);
			if (nCurSel >= 0)
			{
				long lIDDatabase = m_ctrlList.GetItemData(nCurSel);

				CString sFilter;
				sFilter.Format("ID=%li", lIDDatabase);

				CDatabasesSet setTemp;
				setTemp.SetOpenFilter(sFilter);
				if (setTemp.OpenRecordset("CAccessoSediEsterneDlg::OnOK"))
				{
					if (!setTemp.IsEOF())
					{
						CAMBaseDB dbTemp;
						try
						{
							CString sStringaConnessione = ComponiStringaConnessione(m_bIsOracle, setTemp.m_sOracleDriver, setTemp.m_sServerDBQ, setTemp.m_sUsername, setTemp.m_sPassword);
							dbTemp.OpenEx(sStringaConnessione, CDatabase::noOdbcDialog);
							if (dbTemp.IsOpen())
								dbTemp.Close();

							EndWaitCursor();

							// ok...

							CString sMessage;
							sMessage.Format(theApp.GetMessageString(IDS_CONNETTI_SEDE_ESTERNA), setTemp.m_sDescrizione);
							theApp.AfxMessageBoxEndo(sMessage);

							CString sUser = "";
							CString sPass = "";
							AMLogin_GetUserAndPass(&sUser, &sPass);

							CString sEseguibile;
							sEseguibile.Format("%s\\%s.exe -c:\"%s\" -d:\"%s\" -u:\"%s\" -p:\"%s\" -o:\"%s\"", theApp.m_sDirProg, CString(theApp.m_pszExeName), sStringaConnessione, setTemp.m_sDescrizione, sUser, sPass, CUOSet().GetDescrizione(theApp.m_lUO));

							STARTUPINFO si;
							PROCESS_INFORMATION pi;

							ZeroMemory(&si, sizeof(si));
							si.cb = sizeof(si);
							ZeroMemory(&pi, sizeof(pi));

							if (!CreateProcess(NULL, sEseguibile.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
							{
								LPVOID lpMsgBuf;
								if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
									theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
								else
									theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
								LocalFree(lpMsgBuf);
							}
							else
							{
								AfxGetMainWnd()->PostMessage(WM_CLOSE);
							}
							sEseguibile.ReleaseBuffer();

							CloseHandle(pi.hProcess);
							CloseHandle(pi.hThread);
						}
						catch (CDBException* pEx)
						{
							EndWaitCursor();
							theApp.MessageBoxEndo(pEx->m_strError, theApp.GetMessageString(IDS_DATABASE_KO));

							pEx->Delete();
						}
						if (dbTemp.IsOpen())
							dbTemp.Close();
					}
					setTemp.CloseRecordset("CAccessoSediEsterneDlg::OnOK");
				}
			}
		}

		EndWaitCursor();
	}
}

void CAccessoSediEsterneDlg::RiempiLista()
{
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CDatabasesSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CAccessoSediEsterneDlg::RiempiLista"))
	{
		int nIndex = 0;
		while (!setTemp.IsEOF())
		{
			m_ctrlList.InsertItem(nIndex, setTemp.m_sDescrizione);
			m_ctrlList.SetItemData(nIndex, setTemp.m_lID);

			// m_ctrlList.SetItemText(nIndex, 1, ComponiStringaConnessione(m_bIsOracle, setTemp.m_sOracleDriver, setTemp.m_sServerDBQ, setTemp.m_sUsername, setTemp.m_sPassword));

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CAccessoSediEsterneDlg::RiempiLista");
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
}

void CAccessoSediEsterneDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_ctrlBtnOK.EnableWindow(m_ctrlList.GetFirstSelectedItemPosition() != NULL);

	*pResult = 0;
}

void CAccessoSediEsterneDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	OnOK();

	*pResult = 0;
}
