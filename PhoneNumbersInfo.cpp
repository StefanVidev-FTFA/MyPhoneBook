#include "pch.h"
#include "PhoneNumbersInfo.h"

CPhoneNumbersInfo::CPhoneNumbersInfo()
{
	m_oPersonsTable.AssignItemsIds(m_personsIdsList);
	m_oPhoneTypesTable.AssignItemsIds(m_phoneTypesIdsList);
}