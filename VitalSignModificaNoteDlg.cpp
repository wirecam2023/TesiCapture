#include "stdafx.h"
#include "Endox.h"
#include "VitalSignModificaNoteDlg.h"

#include "VitalSignManager.h"
#include "VitalSignMisurazioniHeaderSet.h"
#include "VitalSignPdfWaitingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVitalSignModificaNoteDlg, CEndoxResizableDlg)

CVitalSignModificaNoteDlg::CVitalSignModificaNoteDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, long lIDHeaderMisurazioni)
: CEndoxResizableDlg(CVitalSignModificaNoteDlg::IDD, pParentWnd)
{
	m_lIDHeaderMisurazioni = lIDHeaderMisurazioni;
	m_pEsamiView = pEsamiView;
}

CVitalSignModificaNoteDlg::~CVitalSignModificaNoteDlg()
{
}

BEGIN_MESSAGE_MAP(CVitalSignModificaNoteDlg, CEndoxResizableDlg)
END_MESSAGE_MAP()

void CVitalSignModificaNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlBtnSave);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDC_EDT_NOTE, m_ctrlEdtNote);
}

BOOL CVitalSignModificaNoteDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDOK, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDCANCEL, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_EDT_NOTE, CSize(0, 0), CSize(100, 100));

	CString filter;
	filter.Format("ID=%li", m_lIDHeaderMisurazioni);
	CVitalSignMisurazioniHeaderSet vitalSignMisSet;
	vitalSignMisSet.SetOpenFilter(filter);

	if (vitalSignMisSet.OpenRecordset("CVitalSignModificaNoteDlg::OnInitDialog"))
	{
		if (!vitalSignMisSet.IsEOF())
		{
			m_ctrlEdtNote.SetWindowText(vitalSignMisSet.m_sNote);
		}

		vitalSignMisSet.CloseRecordset("CVitalSignModificaNoteDlg::OnInitDialog");
	}

	//
	theApp.LocalizeDialog(this, CVitalSignModificaNoteDlg::IDD, "VitalSignModificaNoteDlg");

	//
	return TRUE;
}

void CVitalSignModificaNoteDlg::OnCancel()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ABORT), MB_YESNO) == IDNO)
		return;

	CResizableDialog::OnCancel();
}

void CVitalSignModificaNoteDlg::OnOK()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONFIRM), MB_YESNO) == IDNO)
		return;

	BeginWaitCursor();

	CString filter;
	filter.Format("ID=%li", m_lIDHeaderMisurazioni);
	CVitalSignMisurazioniHeaderSet vitalSignMisSet;
	vitalSignMisSet.SetOpenFilter(filter);
	CString oldNotes;
	long oldPdfId = 0;

	BOOL bSuccess = FALSE;

	if (vitalSignMisSet.OpenRecordset("CVitalSignModificaNoteDlg::OnOK"))
	{
		if (!vitalSignMisSet.IsEOF())
		{
			if (vitalSignMisSet.EditRecordset("CVitalSignModificaNoteDlg::OnOK"))
			{				
				oldNotes = vitalSignMisSet.m_sNote; //Mi metto via le vecchie note per ripristinarle in caso di errore
				m_ctrlEdtNote.GetWindowText(vitalSignMisSet.m_sNote);
				oldPdfId = vitalSignMisSet.m_lIDPdf; //Mi metto via il vecchio idpdf per individuarne la sostituzione da parte dell'integrazione

				if (vitalSignMisSet.UpdateRecordset("CVitalSignModificaNoteDlg::OnOK"))
				{
					//Chiamata al client					
					if (!CVitalSignManager(m_pEsamiView).ChangeNotesAndWait(vitalSignMisSet.m_sIDSessioneVitalSign, m_lIDHeaderMisurazioni, oldPdfId, oldNotes, (CList<CVitalSignManager::Measurament>*) NULL, oldNotes, (CList<CVitalSignManager::Measurament>*) NULL))
					{		
						if (vitalSignMisSet.EditRecordset("CVitalSignModificaNoteDlg::OnOK"))
						{
							vitalSignMisSet.m_sNote = oldNotes;
							m_ctrlEdtNote.SetWindowText(oldNotes);

							vitalSignMisSet.UpdateRecordset("CVitalSignModificaNoteDlg::OnOK");
						}

						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NOTEPDF_MODIFICA_ERR1));

					}
					else
					{
						bSuccess = TRUE;
					}
				}
			}
		}

		vitalSignMisSet.CloseRecordset("CVitalSignModificaNoteDlg::OnOK");
	}

	EndWaitCursor();

	CResizableDialog::OnOK();
}