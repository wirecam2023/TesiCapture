#ifndef _PATH_H_
	#define _PATH_H_

class CPath: public CObject
{      

public:

	CPath();

	void SetParameter(long lPaziente, long lEsame, long lID, CImgListOrgani *pImgList, long lIndex, BOOL bConfirmed, CString strDvdLabel, CString strPaziente, long lDataEsame);

	long m_lPaziente;
	long m_lEsame;
	long m_lID;
	CImgListOrgani* m_pImgListOrgani;
	long m_lIndex;
	BOOL m_bConfirmed;
	CString m_strDvdLabel;
	char m_szDesc[1024];
};

#endif /* _PATH_H_ */