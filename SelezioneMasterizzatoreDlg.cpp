#include "stdafx.h"
#include "Endox.h"
#include "SelezioneMasterizzatoreDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSelezioneMasterizzatoreDlg, CDialog)

CSelezioneMasterizzatoreDlg::CSelezioneMasterizzatoreDlg(CWnd* pParent, int iTipoMasterizzatore)
	: CDialog(CSelezioneMasterizzatoreDlg::IDD, pParent)
{
	m_iTipoMasterizzatore = iTipoMasterizzatore;
	m_lDeviceID = -1;
}

CSelezioneMasterizzatoreDlg::~CSelezioneMasterizzatoreDlg()
{
}

void CSelezioneMasterizzatoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO1, m_ctrlComboMast);
}

BEGIN_MESSAGE_MAP(CSelezioneMasterizzatoreDlg, CDialog)
END_MESSAGE_MAP()

BOOL CSelezioneMasterizzatoreDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	int nIndex = 0;
	CString strTemp;
	POSITION pos = theApp.m_listTransferDevice.GetHeadPosition();
	while(pos != NULL)
	{
		switch(m_iTipoMasterizzatore)
		{
			case DISC_CD:
			{
				if (theApp.m_listTransferDevice.GetAt(pos).bCD == TRUE)
				{
					strTemp.Format("%s (%c:)", theApp.m_listTransferDevice.GetAt(pos).szName, theApp.m_listTransferDevice.GetAt(pos).szLetter);
					m_ctrlComboMast.InsertString(nIndex, strTemp);
					m_ctrlComboMast.SetItemData(nIndex, (DWORD)theApp.m_listTransferDevice.GetAt(pos).lID);
					nIndex++;
				}
				break;
			}
			case DISC_DVD:
			{
				if (theApp.m_listTransferDevice.GetAt(pos).bDVD == TRUE)
				{
					strTemp.Format("%s (%c:)", theApp.m_listTransferDevice.GetAt(pos).szName, theApp.m_listTransferDevice.GetAt(pos).szLetter);
					m_ctrlComboMast.InsertString(nIndex, strTemp);
					m_ctrlComboMast.SetItemData(nIndex, (DWORD)theApp.m_listTransferDevice.GetAt(pos).lID);
					nIndex++;
				}
				break;
			}
		}

		theApp.m_listTransferDevice.GetNext(pos);
	}

	m_ctrlComboMast.SetCurSel(0);

	return bReturn;
}

long CSelezioneMasterizzatoreDlg::GetDeviceID()
{
	return m_lDeviceID;
}

void CSelezioneMasterizzatoreDlg::OnCancel() 
{
	// CDialog::OnCancel();
}

void CSelezioneMasterizzatoreDlg::OnOK() 
{
	if (m_ctrlComboMast.GetCount() > 0)
	{
		int nIndex = m_ctrlComboMast.GetCurSel();

		if (nIndex >= 0)
			m_lDeviceID = (long)m_ctrlComboMast.GetItemData(nIndex);
	}

	CDialog::OnOK();
}

INT_PTR CSelezioneMasterizzatoreDlg::DoModal()
{
	int nIndex = 0;
	long lDevice = -1;
	POSITION pos = theApp.m_listTransferDevice.GetHeadPosition();
	while(pos != NULL)
	{
		switch(m_iTipoMasterizzatore)
		{
			case DISC_CD:
			{
				if (theApp.m_listTransferDevice.GetAt(pos).bCD == TRUE)
				{
					nIndex++;
					lDevice = theApp.m_listTransferDevice.GetAt(pos).lID;
				}
				break;
			}
			case DISC_DVD:
			{
				if (theApp.m_listTransferDevice.GetAt(pos).bDVD == TRUE)
				{
					nIndex++;
					lDevice = theApp.m_listTransferDevice.GetAt(pos).lID;
				}
				break;
			}
		}

		theApp.m_listTransferDevice.GetNext(pos);
	}

	if (nIndex <= 1)
	{
		m_lDeviceID = lDevice;
		return IDOK;
	}

	return CDialog::DoModal();
}