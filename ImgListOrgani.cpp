#include "stdafx.h"
#include "Endox.h"
#include "ImgListOrgani.h"

#include "PuntiPazienteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CImgListOrgani::CImgListOrgani(INT_PTR nBlockSize)
	: CList<IMG_ORGANI, IMG_ORGANI&>(nBlockSize)
{
}

CImgListOrgani::~CImgListOrgani()
{
	RemoveAll();
}

void CImgListOrgani::RemoveAll()
{
	/*POSITION pos = GetHeadPosition();
	while(pos != NULL)
	{
		HBITMAP hBit = GetNext(pos).img.hBmp;
		if (hBit != NULL)
			DeleteObject(hBit);
	}
	CList<IMG_ORGANI, IMG_ORGANI&>::RemoveAll();*/
	
	POSITION pos = GetHeadPosition();
	while (pos != NULL)
	{
		IMG img = GetNext(pos).img;
		if (img.hBmp != NULL)
			DeleteObject(img.hBmp);
		if (img.hBmpSelected != NULL)
			DeleteObject(img.hBmpSelected);
	}
	CList<IMG_ORGANI, IMG_ORGANI&>::RemoveAll();
}

CImgListOrgani& CImgListOrgani::operator = (CImgList& list)
{
	RemoveAll();
	IMG_ORGANI ImgOrgani;

	POSITION pos = list.GetHeadPosition();
	while(pos != NULL)
	{
		ImgOrgani.img = list.GetNext(pos);
		ImgOrgani.iPunto = -1;
		ImgOrgani.sSedeDermox = "";
		ImgOrgani.lNumeroDermox = -1;

		if ((theApp.m_nApplication == PRG_DERMOX) && (ImgOrgani.img.lIDPunto > 0))
			CPuntiPazienteSet().GetSedeNumero(ImgOrgani.img.lIDPunto, ImgOrgani.sSedeDermox, ImgOrgani.lNumeroDermox);

		AddTail(ImgOrgani);
	}

	return *this;
}