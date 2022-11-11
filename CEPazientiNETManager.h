#pragma once

class CPazientiSet;

class CNETPatientManager
{
public:
	CNETPatientManager();
	~CNETPatientManager();

	BOOL AddPatient(CPazientiSet *pPazientiSet);

};

