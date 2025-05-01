#pragma once
#include "PhoneNumbers.h"
#include "PersonsTable.h"
#include "PhoneTypesTable.h"


class CPhoneNumbersInfo 
{
public:
	CPhoneNumbersInfo::CPhoneNumbersInfo();
	CPhoneNumbersInfo::~CPhoneNumbersInfo();

private:
	CPersonsTable m_oPersonsTable;
	CPhoneTypesTable m_oPhoneTypesTable;

public:
	PHONE_NUMBERS m_recPhoneNum;

	CSmartArray<PERSONS> m_personsArray;
	CSmartArray<PHONE_TYPES> m_phoneTypesArray;
};