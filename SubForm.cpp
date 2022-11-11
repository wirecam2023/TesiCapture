#include "stdafx.h"
#include "Endox.h"
#include "SubForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSubForm::CSubForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 0;
}

void CSubForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SCROLL, m_ctrlScroll);
}

BOOL CSubForm::CreateChildForm(UINT nID, CWnd* pParentWnd, CRect rectFrame)
{
	BOOL result = CEndoxDynForm::Create(nID, pParentWnd);

	m_pParentWnd = pParentWnd;

	if (result != FALSE)
	{	
		SetWindowPos(NULL, rectFrame.left, rectFrame.top, rectFrame.Width(), rectFrame.Height(), SWP_NOZORDER | SWP_NOOWNERZORDER);
		ShowWindow(SW_SHOW);
	}

	return result;
}

BEGIN_MESSAGE_MAP(CSubForm, CEndoxDynForm)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()

BOOL CSubForm::OnInitDialog() 
{
	CEndoxDynForm::OnInitDialog();

	m_nIndexLine = 0;
	m_ctrlScroll.SetScrollRange(0, (MAX_OBJ_X_FORM-m_nIndexPage));
	m_ctrlScroll.SetScrollPos  (m_nIndexLine);

	UpgradeForm();

	return TRUE;
}

void CSubForm::SaveForm(long* pParamOfFilter, CBaseSet* pSet, long* pCounterSet, long* pParamSet, CString sKeyFieldName)
{
	BOOL bError;
	CString strFilter;

	for(int nCounter = 0; nCounter < MAX_OBJ_X_FORM; nCounter++)
	{
		BOOL bSave = FALSE;
		long nContatore = 0;
		
		if (IsLineDirty(nCounter))
		{
			if (IsValidSet(nCounter))
			{
				nContatore = GetCounterSetOfLine(nCounter);
				
				if (nContatore)
				{
					strFilter.Format(sKeyFieldName + "=%li", nContatore);
		
					if (pSet->RecordsetReOpen(bError, strFilter, sKeyFieldName, "CSubForm::SaveForm"))
						bSave = pSet->EditRecordset("CSubForm::SaveForm");
				}
				else
				{
					bSave = pSet->AddNewRecordset("CSubForm::SaveForm");
				}
			}
			else
			{
				nContatore = GetCounterSetOfLine(nCounter);
				
				if (nContatore)
				{
					strFilter.Format(sKeyFieldName + "=%li", nContatore);
		
					if (pSet->RecordsetReOpen(bError, strFilter, sKeyFieldName, "CSubForm::SaveForm"))
						pSet->DeleteRecordset("CSubForm::SaveForm");
				}
			}
		}

		if (bSave)
		{
			UpdateDataLine(pSet, nCounter, TRUE);

			if (nContatore)
			{
				//sono in Edit...
				*pParamSet = *pParamOfFilter;

				pSet->SetFieldDirty(pCounterSet, FALSE);
			}
			else
			{
				//sono in AddNew...
				*pParamSet = *pParamOfFilter;
				
				pSet->SetFieldDirty(pCounterSet, FALSE);
				pSet->SetFieldNull (pCounterSet, TRUE);
			}

			if (pSet->UpdateRecordset("CSubForm::SaveForm"))
			{
				SetLineDirty(nCounter, FALSE);
			}
			else
			{
				pSet->NoEditRecordset("CSubForm::SaveForm");
				
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_SUBFORM_DONT_SAVE), "CSubForm::SaveForm", nCounter);
				theApp.AfxMessageBoxEndo(strError);
			}
		}
	}
}

void CSubForm::UpgradeForm()
{
	UpdateData(TRUE);

	m_nIndexLine = m_ctrlScroll.GetScrollPos();

	ModificaForm();

	UpdateData(FALSE);
}

void CSubForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CEndoxDynForm::OnVScroll(nSBCode, nPos, pScrollBar);

	int Min, Max, OldPos, NewPos;

	pScrollBar->GetScrollRange(&Min, &Max);
    OldPos = pScrollBar->GetScrollPos();

	switch(nSBCode)
	{
		case SB_LEFT :
		case SB_LINELEFT :
			NewPos = max(Min, OldPos - 1);
			break;

		case SB_PAGELEFT :
			NewPos = max(Min, OldPos - m_nIndexPage);
			break;

		case SB_RIGHT :
		case SB_LINERIGHT :
			NewPos = min(Max, OldPos + 1);
			break;

		case SB_PAGERIGHT :
			NewPos = min(Max, OldPos + m_nIndexPage);
			break;

		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			NewPos = nPos;
			break;
		
		default:
			NewPos = OldPos;
	}
	
	pScrollBar->SetScrollPos(NewPos);

	if (nSBCode == SB_ENDSCROLL)
		UpgradeForm();
}

void CSubForm::GoToFirst()
{
	m_ctrlScroll.SetScrollPos(0);

	m_nIndexLine = 0;

	ModificaForm();

	UpdateData(FALSE);
}