#include "stdafx.h"
#include "SendPneuDLG.h"


void CSendPneuDLG::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	IsCancel = true;
	OnCancel();
}


void CSendPneuDLG::OnBnClickedOnlyCard()
{
	// TODO: Add your control notification handler code here
	IsOnlyCard = true;
	OnCancel();
}


void CSendPneuDLG::OnBnClickedWithPneu()
{
	// TODO: Add your control notification handler code here
	IsWithPneu = true;
	OnCancel();
}
