#ifndef _IMGLISTORGANI_H_
	#define _IMGLISTORGANI_H_

typedef struct _IMG_ORGANI_
{
   IMG img;
   int iPunto;
   CString sSedeDermox;
   long lNumeroDermox;
} IMG_ORGANI;

class CImgListOrgani : public CList<IMG_ORGANI, IMG_ORGANI&>
{

public:

	CImgListOrgani(INT_PTR nBlockSize = 10);
	~CImgListOrgani();

	void RemoveAll();

	CImgListOrgani& operator = (CImgList& list);
};

#endif /* _IMGLISTORGANI_H_ */