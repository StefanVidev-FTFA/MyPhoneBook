#include "pch.h"
#include "PhoneNumbersInfo.h"

CPhoneNumbersInfo::CPhoneNumbersInfo()
{
	m_oPersonsTable.SelectAll(m_personsArray);
	m_oPhoneTypesTable.SelectAll(m_phoneTypesArray);
}
CPhoneNumbersInfo::~CPhoneNumbersInfo()
{

}