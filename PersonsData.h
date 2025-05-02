#pragma once
#include "pch.h"
#include "PersonsTable.h"
#include "CitiesTable.h"
#include "PhoneNumbersTable.h"
#include "PhoneTypesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData
/// <summary> ���� ������ �� ������������ �� ������ �������� �� ��������� </summary>
class CPersonsData: public CPersonsTable
{
public:
	/// <summary>������� ��� ���������� ������ ��� ����� �� ��������� ������ �� ���� </summary>
	bool AddPerson(PERSONS& recItem, const CSmartArray<PHONE_NUMBERS>& phoneNumbers);

	/// <summary>��������� ������� �� ���������� ������ ��� �������� ��������� ������</summary>
	bool UpdatePerson(const PERSONS& recPerson,CSmartArray<PHONE_NUMBERS>& newPhoneNumbers);
};