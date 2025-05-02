#pragma once
#include "pch.h"
#include "PersonsTable.h"
#include "CitiesTable.h"
#include "PhoneNumbersTable.h"
#include "PhoneTypesTable.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CPersonsData
/// <summary> Клас служещ за изпълнението на бизнес логиката на указателя /// </summary>
class CPersonsData: public CPersonsTable
{
public:
	/// <summary>Вевежда нов потребител заедно със набор от телефонни номера за него/// </summary>
	bool CommitNewPerson(PERSONS& recItem, const CSmartArray<PHONE_NUMBERS>& phoneNumbers);
};