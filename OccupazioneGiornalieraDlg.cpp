#include "stdafx.h"
#include "Endox.h"
#include "OccupazioneGiornalieraDlg.h"

#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COccupazioneGiornalieraDlg, CDialog)

COccupazioneGiornalieraDlg::COccupazioneGiornalieraDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(COccupazioneGiornalieraDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	m_pEsamiView = pEsamiView;
}

COccupazioneGiornalieraDlg::~COccupazioneGiornalieraDlg()
{
}

BEGIN_MESSAGE_MAP(COccupazioneGiornalieraDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER, OnDtnDateTimeChangeDateTimePicker)
END_MESSAGE_MAP()

void COccupazioneGiornalieraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlBtnChiudi);

	DDX_Control(pDX, IDC_DATETIMEPICKER, m_ctrlDate);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_06, m_ctrlStatic06);
	DDX_Control(pDX, IDC_STATIC_09, m_ctrlStatic09);
	DDX_Control(pDX, IDC_STATIC_12, m_ctrlStatic12);
}

HBRUSH COccupazioneGiornalieraDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_12:
		case IDC_DATETIMEPICKER:
		{
			pDC->SetTextColor(theApp.m_color[1]);
			break;
		}
		case IDC_STATIC_00:
		case IDC_STATIC_01:
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
		case IDC_STATIC_03:
		case IDC_STATIC_04:
		case IDC_STATIC_05:
		{
			pDC->SetTextColor(theApp.m_color[3]);
			break;
		}
		case IDC_STATIC_06:
		case IDC_STATIC_07:
		case IDC_STATIC_08:
		{
			pDC->SetTextColor(theApp.m_color[4]);
			break;
		}
		case IDC_STATIC_09:
		case IDC_STATIC_10:
		case IDC_STATIC_11:
		{
			pDC->SetTextColor(theApp.m_color[5]);
			break;
		}
	}

	return hBrush;
}

BOOL COccupazioneGiornalieraDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	CCustomDate dateToday1(TRUE, FALSE);
	CCustomDate dateToday2(TRUE, FALSE);
	dateToday1.SetTime("00:00");
	dateToday2.SetTime("23:59");

	SetDate(dateToday1, dateToday2);

	theApp.LocalizeDialog(this, COccupazioneGiornalieraDlg::IDD, "OccupazioneGiornalieraDlg");
	return bReturn;
}
void COccupazioneGiornalieraDlg::OnDtnDateTimeChangeDateTimePicker(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	
	CString temp;
	m_ctrlDate.GetWindowText(temp);
	
	CCustomDate dateFrom(atoi(temp.Right(4)), atoi(temp.Mid(3,2)), atoi(temp.Left(2)), 0, 0, 0);
	CCustomDate dateTo(atoi(temp.Right(4)), atoi(temp.Mid(3,2)), atoi(temp.Left(2)), 0, 23, 59);

	SetDate(dateFrom, dateTo);

	*pResult = 0;
}

void COccupazioneGiornalieraDlg::SetDate(CCustomDate dateFrom, CCustomDate dateTo)
{
	SetDlgItemText(IDC_STATIC_01, "0");
	SetDlgItemText(IDC_STATIC_04, "0");
	SetDlgItemText(IDC_STATIC_05, "");
	SetDlgItemText(IDC_STATIC_07, "0");
	SetDlgItemText(IDC_STATIC_08, "");
	SetDlgItemText(IDC_STATIC_10, "0");
	SetDlgItemText(IDC_STATIC_11, "");

	BeginWaitCursor();

	try
	{
		long lEsami = 0;
		long lTemp;

		CString strQuery;
		CRecordset setCount(&theApp.m_dbEndox);
		// carico il numero di esami della giornata //
		strQuery.Format("SELECT COUNT(*) AS CONTEGGIO FROM EESAMI WHERE DATA BETWEEN %li AND %li", dateFrom.GetDate(), dateTo.GetDate());
		setCount.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);
		if (!setCount.IsEOF())
		{
			setCount.GetFieldValue("CONTEGGIO", strQuery);
			SetDlgItemText(IDC_STATIC_01, strQuery);

			lEsami = atol(strQuery);
		}
		if (setCount.IsOpen())
			setCount.Close();

		if (lEsami > 0)
		{
			// carico il numero di immagini della giornata //
			strQuery.Format("SELECT COUNT(*) AS CONTEGGIO FROM EESAMI INNER JOIN IMMAGINI ON EESAMI.CONTATORE=IMMAGINI.IDESAME WHERE DATA BETWEEN %li AND %li AND TIPO=0", dateFrom.GetDate(), dateTo.GetDate());
			setCount.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);
			if (!setCount.IsEOF())
			{
				setCount.GetFieldValue("CONTEGGIO", strQuery);
				SetDlgItemText(IDC_STATIC_04, strQuery);

				lTemp = atol(strQuery);
				strQuery.Format("(%0.1f %s)", (float)lTemp / (float)lEsami, theApp.GetMessageString(IDS_PERESAME));
				SetDlgItemText(IDC_STATIC_05, strQuery);
			}
			if (setCount.IsOpen())
				setCount.Close();

			// carico il numero di filmati della giornata //
			strQuery.Format("SELECT COUNT(*) AS CONTEGGIO FROM EESAMI INNER JOIN IMMAGINI ON EESAMI.CONTATORE=IMMAGINI.IDESAME WHERE DATA BETWEEN %li AND %li AND TIPO=1", dateFrom.GetDate(), dateTo.GetDate());
			setCount.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);
			if (!setCount.IsEOF())
			{
				setCount.GetFieldValue("CONTEGGIO", strQuery);
				SetDlgItemText(IDC_STATIC_07, strQuery);

				lTemp = atol(strQuery);
				strQuery.Format("(%0.1f %s)", (float)lTemp / (float)lEsami, theApp.GetMessageString(IDS_PERESAME));
				SetDlgItemText(IDC_STATIC_08, strQuery);
			}
			if (setCount.IsOpen())
				setCount.Close();

			// carico le dimensioni dei documenti //
			strQuery.Format("Data BETWEEN %li AND %li", dateFrom.GetDate(), dateTo.GetDate());

			CImgManager imgTemp(theApp.m_sPathImageOD, &theApp.m_dbEndox);
			imgTemp.SetImageExt(CString(EXT_IMG).Right(3));
			imgTemp.SetThumbExt(CString(EXT_WIN).Right(3));

			CEsamiSet setTemp;
			setTemp.SetOpenFilter(strQuery);
			setTemp.SetSortRecord("Contatore");

			PAT_EXAM peTemp;
			CExamIDList listTemp;

			if (setTemp.OpenRecordset("COccupazioneGiornalieraDlg::OnInitDialog"))
			{
				while(!setTemp.IsEOF())
				{
					peTemp.lPatientID = setTemp.m_lPaziente;
					peTemp.lExamID = setTemp.m_lContatore;
					listTemp.AddTail(peTemp);

					setTemp.MoveNext();
				}

				setTemp.CloseRecordset("COccupazioneGiornalieraDlg::OnInitDialog");
			}

			LONGLONG llDimension;
			imgTemp.GetImageDimension(&listTemp, llDimension);

			double lfDimension = (double)llDimension / 1024.0f / 1024.0f;

			strQuery.Format("%0.0lf", lfDimension);
			SetDlgItemText(IDC_STATIC_10, strQuery);
			strQuery.Format("(%0.1lf %s)", lfDimension / (double)lEsami, theApp.GetMessageString(IDS_PERESAME));
			SetDlgItemText(IDC_STATIC_11, strQuery);
		}
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}

	EndWaitCursor();
}