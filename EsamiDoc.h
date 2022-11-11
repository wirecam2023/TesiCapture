#ifndef _ESAMIDOC_H_
	#define _ESAMIDOC_H_

#include "ComboBoxSet.h"
#include "EsamiSet.h"
#include "PazientiSet.h"

class CEsamiDoc : public CDocument
{
protected:

	CEsamiDoc();
	virtual ~CEsamiDoc();

	DECLARE_DYNCREATE(CEsamiDoc)

public:

	CPazientiSet m_PazientiSet;
	CEsamiSet m_EsamiSet;

	virtual BOOL OnNewDocument();
	virtual void OnCloseDocument();

	void SetBoolValue(CString sVoce, BOOL& bValore);
	void SetIntValue(CString sVoce, int& iValore);
	void SetStringValue(CString sVoce, CString& sValore);
	void SetLongValue(CString sVoce, long& iValore);

	void OnSalvaConfigurazioneIntegrazioniGenerale();
	void OnSalvaConfigurazioneIntegrazioneVitalSign();
	void OnSalvaConfigurazioneIntegrazioniUO();
	void OnSalvaConfigurazioneFasi();

	BOOL LeggiConfigurazioniEImpostaSoftware();	

	void LoadUserGroups();
	void LoadEnabledPhaseForUser();

protected:

	void LeggiConfigurazioneStep1();
	void LeggiConfigurazioneStep2();
	void LeggiConfigurazioneStep3();

	DECLARE_MESSAGE_MAP()

private:

	void GetBoolValue(CString sVoce, BOOL& bValore);
	void GetFloatValue(CString sVoce, float& fValore);
	void GetIntValue(CString sVoce, int& iValore);
	void GetLongValue(CString sVoce, long& lValore);
	void GetStringValue(CString sVoce, CString& sValore);
	void GetStringValueServizi(CString sVoce, CString& sValore);
	void GetLongValueServizi(CString sVoce, long& lValore);	

};

#endif /* _ESAMIDOC_H_ */