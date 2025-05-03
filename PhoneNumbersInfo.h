#pragma once

#include "PhoneNumbers.h"
#include "PersonsTable.h"
#include "PhoneTypesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogPersonsInsert
/// <summary> Клас служещ за пакетиране на информацуята която трябва да се предаде на диалога</summary>
class CPhoneNumbersInfo 
{
// Constructor / Destructor
// ----------------
public:
	CPhoneNumbersInfo::CPhoneNumbersInfo();
	CPhoneNumbersInfo::~CPhoneNumbersInfo();

// Members
// ----------------
private:
	CPersonsTable m_oPersonsTable;
	CPhoneTypesTable m_oPhoneTypesTable;
public:
	PHONE_NUMBERS m_recPhoneNum;
	CSmartArray<PERSONS> m_personsArray;
	CSmartArray<PHONE_TYPES> m_phoneTypesArray;
};
