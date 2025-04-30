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

	CStringList m_personsIdsList;
	CStringList m_phoneTypesIdsList;
};