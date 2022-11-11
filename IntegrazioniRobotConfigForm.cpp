#include "stdafx.h"
#include "Endox.h"

#include "EndoxMenu.h"
#include "EsamiDoc.h"
#include "EsamiView.h"

#include "IntegrazioniRobotConfigForm.h"
#include "IntegrazioniConfigurazioneModDlg.h"
#include "RobotSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CIntegrazioniRobotConfigForm, CResizableDialog)
	ON_WM_CTLCOLOR()	

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTA, OnLvnItemchangedList)
	ON_BN_CLICKED(IDC_NUOVO, OnBnClickedButtonNuovo)
	ON_BN_CLICKED(IDC_CANC, OnBnClickedButtonCanc)
END_MESSAGE_MAP()

HBRUSH CIntegrazioniRobotConfigForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CResizableDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	//pDC->SetBkColor(theApp.m_color[0]);	

	return hBrush;
}


CIntegrazioniRobotConfigForm::CIntegrazioniRobotConfigForm(CWnd* pParent, CIntegrazioniConfigurazioneModDlg* configDlg)
	: CResizableDialog(CIntegrazioniRobotConfigForm::IDD, pParent), m_ctrlListLista(TRUE, FALSE, FALSE)
{
	m_pConfigDlg = configDlg;

	CResizableDialog::Create(CIntegrazioniRobotConfigForm::IDD, pParent->GetParent());

	CRect rect;
	m_pParentWnd->GetWindowRect(&rect);
	m_pParentWnd->GetParent()->ScreenToClient(&rect);
	SetWindowPos(pParent, rect.left, rect.top, rect.Width(), rect.Height(), 0);

	m_listDeletedItem.RemoveAll();
}

CIntegrazioniRobotConfigForm::~CIntegrazioniRobotConfigForm()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

void CIntegrazioniRobotConfigForm::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_LISTA, m_ctrlListLista);
	DDX_Control(pDX, IDC_NUOVO, m_ctrlBtnAdd);
	DDX_Control(pDX, IDC_CANC, m_ctrlBtnDel);
	
}

BOOL CIntegrazioniRobotConfigForm::OnInitDialog()
{
	CResizableDialog::OnInitDialog();
	
	AddAnchor(IDC_STATIC_1, CSize(0, 0), CSize(100, 100));	
	AddAnchor(IDC_LISTA, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_NUOVO, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_CANC, CSize(0, 100), CSize(0, 100));

	theApp.LocalizeDialog(this, CIntegrazioniRobotConfigForm::IDD, "IntegrazioniRobotConfigForm");

	Load();

	m_ctrlListLista.SetExtendedStyle(m_ctrlListLista.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);

	return TRUE;
}

void CIntegrazioniRobotConfigForm::Load()
{	
	m_ctrlListLista.InsertColumn(m_ctrlListLista.GetHeaderCtrl()->GetItemCount(), "Descrizione");
	m_ctrlListLista.InsertColumn(m_ctrlListLista.GetHeaderCtrl()->GetItemCount(), "Tipo");
	m_ctrlListLista.InsertColumn(m_ctrlListLista.GetHeaderCtrl()->GetItemCount(), "Host");
	m_ctrlListLista.InsertColumn(m_ctrlListLista.GetHeaderCtrl()->GetItemCount(), "Porta");
	m_ctrlListLista.InsertColumn(m_ctrlListLista.GetHeaderCtrl()->GetItemCount(), "Path label backup");
	m_ctrlListLista.InsertColumn(m_ctrlListLista.GetHeaderCtrl()->GetItemCount(), "Path label paziente");
	m_ctrlListLista.InsertColumn(m_ctrlListLista.GetHeaderCtrl()->GetItemCount(), "Directory merge");
	m_ctrlListLista.InsertColumn(m_ctrlListLista.GetHeaderCtrl()->GetItemCount(), "Directory temporanea");
	m_ctrlListLista.InsertColumn(m_ctrlListLista.GetHeaderCtrl()->GetItemCount(), "Simula");
	m_ctrlListLista.InsertColumn(m_ctrlListLista.GetHeaderCtrl()->GetItemCount(), "Default");

	m_ctrlListLista.SetSubItemEdit(-1, 0);
	//m_ctrlListLista.SetSubItemEdit(-1, 1);
	m_ctrlListLista.SetSubItemEdit(-1, 2);
	m_ctrlListLista.SetSubItemEdit(-1, 3, TRUE);
	m_ctrlListLista.SetSubItemEdit(-1, 4);
	m_ctrlListLista.SetSubItemEdit(-1, 5);
	m_ctrlListLista.SetSubItemEdit(-1, 6);
	m_ctrlListLista.SetSubItemEdit(-1, 7);
	m_ctrlListLista.SetSubItemCheck(-1, 8);
	m_ctrlListLista.SetSubItemCheck(-1, 9);

	CRobotSet robotSet;
	if (robotSet.OpenRecordset("CIntegrazioniRobotConfigForm::Load"))
	{
		while (!robotSet.IsEOF())
		{
			int iItem = m_ctrlListLista.InsertItem(m_ctrlListLista.GetItemCount(), robotSet.m_sDescription);
			m_ctrlListLista.SetItemData(iItem, robotSet.m_lID);
			m_ctrlListLista.SetItemText(iItem, 1, (robotSet.m_lType == CRobotSet::Type::Rimage ? "Rimage" : "Altro"));
			m_ctrlListLista.SetItemText(iItem, 2, robotSet.m_sHost);
			CString sPort;
			sPort.Format("%li", robotSet.m_lPort);
			m_ctrlListLista.SetItemText(iItem, 3, sPort);
			m_ctrlListLista.SetItemText(iItem, 4, robotSet.m_sBackupLabelPath);
			m_ctrlListLista.SetItemText(iItem, 5, robotSet.m_sPatientLabelPath);
			m_ctrlListLista.SetItemText(iItem, 6, robotSet.m_sMergeDirectoryPath);
			m_ctrlListLista.SetItemText(iItem, 7, robotSet.m_sTempDirectoryPath);
			m_ctrlListLista.SetSubItemData(iItem, 8, robotSet.m_bSimulationMode);

			if (robotSet.m_lID == theApp.m_lIdRobotDefault)
				m_ctrlListLista.SetSubItemData(iItem, 9, TRUE);
			else
				m_ctrlListLista.SetSubItemData(iItem, 9, FALSE);

			robotSet.MoveNext();
		}

		robotSet.CloseRecordset("CIntegrazioniRobotConfigForm::Load");
	}
}

void CIntegrazioniRobotConfigForm::Save()
{	
	//Prima elimino da db tutti gli elementi della lista m_listDeletedItem
	if (POSITION pos = m_listDeletedItem.GetHeadPosition())
	{
		while (pos)
		{
			long idToDelete = m_listDeletedItem.GetNext(pos);

			CString sFilter;
			sFilter.Format("ID=%li", idToDelete);

			CRobotSet set;
			set.SetOpenFilter(sFilter);
			if (set.OpenRecordset("CIntegrazioniRobotConfigForm::Save"))
			{
				while (!set.IsEOF())
				{
					set.DeleteRecordset("CIntegrazioniRobotConfigForm::Save");

					set.MoveNext();
				}

				set.CloseRecordset("CIntegrazioniRobotConfigForm::Save");
			}
		}
	}

	//Poi aggiungo o aggiorno i record ancora presenti
	for (int i = 0; i < m_ctrlListLista.GetItemCount(); i++)
	{
		long idToAdd = m_ctrlListLista.GetItemData(i);

		if (idToAdd == -1)
		{
			CRobotSet set;
			if (set.OpenRecordset("CIntegrazioniRobotConfigForm::Save"))
			{
				if (set.AddNewRecordset("CIntegrazioniRobotConfigForm::Save"))
				{
					set.m_sDescription = m_ctrlListLista.GetItemText(i, 0);
					set.m_lType = CRobotSet::Type::Rimage;
					set.m_sHost = m_ctrlListLista.GetItemText(i, 2);
					set.m_lPort = atoi(m_ctrlListLista.GetItemText(i, 3));
					set.m_sBackupLabelPath = m_ctrlListLista.GetItemText(i, 4);
					set.m_sPatientLabelPath = m_ctrlListLista.GetItemText(i, 5);
					set.m_sMergeDirectoryPath = m_ctrlListLista.GetItemText(i, 6);
					set.m_sTempDirectoryPath = m_ctrlListLista.GetItemText(i, 7);
					set.m_bSimulationMode = m_ctrlListLista.GetSubItemData(i, 8);

					if (set.UpdateRecordset("CIntegrazioniRobotConfigForm::Save"))
						idToAdd = set.GetLastAdd();
				}

				set.CloseRecordset("CIntegrazioniRobotConfigForm::Save");
			}
		}
		else
		{
			CString sFilter;
			sFilter.Format("ID=%li", idToAdd);
			CRobotSet set;
			set.SetOpenFilter(sFilter);
			if (set.OpenRecordset("CIntegrazioniRobotConfigForm::Save"))
			{
				if (set.EditRecordset("CIntegrazioniRobotConfigForm::Save"))
				{
					set.m_sDescription = m_ctrlListLista.GetItemText(i, 0);
					set.m_lType = CRobotSet::Type::Rimage;
					set.m_sHost = m_ctrlListLista.GetItemText(i, 2);
					set.m_lPort = atoi(m_ctrlListLista.GetItemText(i, 3));
					set.m_sBackupLabelPath = m_ctrlListLista.GetItemText(i, 4);
					set.m_sPatientLabelPath = m_ctrlListLista.GetItemText(i, 5);
					set.m_sMergeDirectoryPath = m_ctrlListLista.GetItemText(i, 6);
					set.m_sTempDirectoryPath = m_ctrlListLista.GetItemText(i, 7);
					set.m_bSimulationMode = m_ctrlListLista.GetSubItemData(i, 8);

					set.UpdateRecordset("CIntegrazioniRobotConfigForm::Save");
				}

				set.CloseRecordset("CIntegrazioniRobotConfigForm::Save");
			}
		}

		if (idToAdd > 0 && m_ctrlListLista.GetSubItemData(i, 9) == TRUE)
			theApp.m_lIdRobotDefault = idToAdd;
	}

	//Aggiorno la variabile globale che mi interessa
	theApp.m_bRobotAttivo = (m_ctrlListLista.GetItemCount() > 0);

}

void CIntegrazioniRobotConfigForm::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_ctrlBtnDel.EnableWindow(m_ctrlListLista.GetFirstSelectedItemPosition() != NULL);

	*pResult = 0;
}

void CIntegrazioniRobotConfigForm::OnBnClickedButtonNuovo()
{
	int iInserted = m_ctrlListLista.InsertItem(m_ctrlListLista.GetItemCount(), theApp.GetMessageString(IDS_NUOVO_DISPOSITIVO));
	m_ctrlListLista.SetItemText(iInserted, 1, "Rimage");
	m_ctrlListLista.SetItemData(iInserted, -1);
	m_ctrlListLista.SetItemState(iInserted, LVIS_SELECTED, LVIS_SELECTED);
	m_ctrlListLista.SetFocus();

	CRect rect;
	m_ctrlListLista.GetSubItemRect(iInserted, 0, LVIR_LABEL, rect);
	m_ctrlListLista.PostMessage(WM_LBUTTONDOWN, 0, MAKELPARAM((rect.right + rect.left) / 2, (rect.bottom + rect.top) / 2));
}

void CIntegrazioniRobotConfigForm::OnBnClickedButtonCanc()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ELIMINARERIGA), MB_YESNO) == IDNO)
		return;

	if (POSITION pos = m_ctrlListLista.GetFirstSelectedItemPosition())
	{
		int deletedItem = m_ctrlListLista.GetNextSelectedItem(pos);
		long deletedId = m_ctrlListLista.GetItemData(deletedItem);
		m_listDeletedItem.AddTail(deletedId);

		m_ctrlListLista.DeleteItem(deletedItem);
	}
}