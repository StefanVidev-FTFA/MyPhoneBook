#pragma once
#include "pch.h"
#include "PersonsTable.h"
#include "CitiesTable.h"
#include "PhoneNumbersTable.h"
#include "PhoneTypesTable.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CPersonsData

/// <summary> ���� ������ �� ������������ �� ������ �������� �� ��������� /// </summary>
class CPersonsData: public CPersonsTable
{
public:
	bool CommitNewPerson(PERSONS& recItem, const CSmartArray<PHONE_NUMBERS>& phoneNumbers);
};