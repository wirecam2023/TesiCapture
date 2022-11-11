#include "stdafx.h"
#include "Endox.h"
#include "ComboDynCampoDlg.h"

#include "Common.h"
#include "FarmaciPazientiCroniciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboDynCampoDlg, CDialog)

CComboDynCampoDlg::CComboDynCampoDlg(CWnd* pParent, UINT idTitle, const CString &sValue)
	: CDialog(CComboDynCampoDlg::IDD, pParent)
{
	m_lIDCampo = 0;
	m_lTipoCampo = 0;

	m_sTitle = theApp.GetMessageString(idTitle);
	m_sValue = sValue;

	m_nIndexScores = -1;
	m_nIndexFarmaci = -1;
}

CComboDynCampoDlg::~CComboDynCampoDlg()
{
}

void CComboDynCampoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_COMBO_CAMPI, m_ctrlComboCampi);
}

BEGIN_MESSAGE_MAP(CComboDynCampoDlg, CDialog)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_CBN_SELCHANGE(IDC_COMBO_CAMPI, OnCbnSelchangeComboCampi)

END_MESSAGE_MAP()

BOOL CComboDynCampoDlg::OnInitDialog()
{   
	CDialog::OnInitDialog();

	//

	RiempiComboCampi();

	//

	theApp.LocalizeDialog(this, CComboDynCampoDlg::IDD, "ComboDynCampoDlg");
	SetWindowText(m_sTitle);

	//

	m_ctrlComboCampi.ShowDropDown();
	return TRUE;
}

void CComboDynCampoDlg::OnBnClickedOk()
{
	int nIndex = m_ctrlComboCampi.GetCurSel();
	if (nIndex >= 0)
	{
		m_lIDCampo = m_ctrlComboCampi.GetItemData(nIndex);

		if (nIndex < m_nIndexScores)
			m_lTipoCampo = TIPOCAMPO_LIBERO;
		else if (nIndex > m_nIndexFarmaci)
			m_lTipoCampo = TIPOCAMPO_FARMACO;
		else
			m_lTipoCampo = TIPOCAMPO_SCORE;
	}

	OnOK();
}

long CComboDynCampoDlg::GetIDCampo()
{
	return m_lIDCampo;
}

long CComboDynCampoDlg::GetTipoCampo()
{
	return m_lTipoCampo;
}

void CComboDynCampoDlg::OnCbnSelchangeComboCampi()
{
	BOOL bEnable = FALSE;

	int nCurSel = m_ctrlComboCampi.GetCurSel();
	if (nCurSel >= 0)
		bEnable = (m_ctrlComboCampi.GetItemData(nCurSel) > 0);

	m_ctrlButtonOK.EnableWindow(bEnable);
}

void CComboDynCampoDlg::RiempiComboCampi()
{
	m_ctrlComboCampi.SetRedraw(FALSE);
	m_ctrlComboCampi.ResetContent();

	int nIndex = 0;
	int nIndexToSel = -1;

	//

	m_ctrlComboCampi.InsertString(nIndex, theApp.GetMessageString(IDS_TIPOCAMPO_LIBERI));
	m_ctrlComboCampi.SetItemData(nIndex, (DWORD)0);
	nIndex++;

	for(int i = edt_libero000; i <= edt_libero099; i++)
	{
		if (g_FormCaract[i].bEndox && !g_FormCaract[i].sDescrizione.Trim().IsEmpty())
		{
			CString sTemp = g_FormCaract[i].sDescrizione + GetStringCampoLiberoDatabase(i);

			m_ctrlComboCampi.InsertString(nIndex, sTemp);
			m_ctrlComboCampi.SetItemData(nIndex, (DWORD)i);
			if (sTemp == m_sValue)
				nIndexToSel = nIndex;
			nIndex++;
		}
	}
	for(int i = edt_liberodataora000; i <= edt_liberodataora019; i++)
	{
		if (g_FormCaract[i].bEndox && !g_FormCaract[i].sDescrizione.Trim().IsEmpty())
		{
			CString sTemp = g_FormCaract[i].sDescrizione + GetStringCampoLiberoDatabase(i);

			m_ctrlComboCampi.InsertString(nIndex, sTemp);
			m_ctrlComboCampi.SetItemData(nIndex, (DWORD)i);
			if (sTemp == m_sValue)
				nIndexToSel = nIndex;
			nIndex++;
		}
	}

	//

	m_nIndexScores = m_ctrlComboCampi.InsertString(nIndex, theApp.GetMessageString(IDS_TIPOCAMPO_SCORES));
	m_ctrlComboCampi.SetItemData(nIndex, (DWORD)0);
	nIndex++;

	m_ctrlComboCampi.InsertString(nIndex, theApp.GetMessageString(IDS_SCORE_HB));
	m_ctrlComboCampi.SetItemData(nIndex, (DWORD)EDT_PAZIENTICRONICI_SCORE_HB);
	if (theApp.GetMessageString(IDS_SCORE_HB) == m_sValue)
		nIndexToSel = nIndex;
	nIndex++;

	m_ctrlComboCampi.InsertString(nIndex, theApp.GetMessageString(IDS_SCORE_S));
	m_ctrlComboCampi.SetItemData(nIndex, (DWORD)EDT_PAZIENTICRONICI_SCORE_S);
	if (theApp.GetMessageString(IDS_SCORE_S) == m_sValue)
		nIndexToSel = nIndex;
	nIndex++;

	//

	m_nIndexFarmaci = m_ctrlComboCampi.InsertString(nIndex, theApp.GetMessageString(IDS_TIPOCAMPO_FARMACI));
	m_ctrlComboCampi.SetItemData(nIndex, (DWORD)0);
	nIndex++;

	CFarmaciPazientiCroniciSet setFPC;
	setFPC.SetSortRecord("Descrizione");
	if (setFPC.OpenRecordset("CComboDynCampoDlg::RiempiComboCampi"))
	{
		while(!setFPC.IsEOF())
		{
			m_ctrlComboCampi.InsertString(nIndex, setFPC.m_sDescrizione);
			m_ctrlComboCampi.SetItemData(nIndex, (DWORD)setFPC.m_lID);
			if (setFPC.m_sDescrizione == m_sValue)
				nIndexToSel = nIndex;
			nIndex++;

			setFPC.MoveNext();
		}

		setFPC.CloseRecordset("CComboDynCampoDlg::RiempiComboCampi");
	}

	//

	if (nIndexToSel >= 0)
		m_ctrlComboCampi.SetCurSel(nIndexToSel);

	m_ctrlComboCampi.SetRedraw(TRUE);
}
