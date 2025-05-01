#include "pch.h"
#include "Persons.h"
#include "PhoneNumbers.h"
#include "PersonsTable.h"
#include "PhoneNumbersTable.h"

bool CPersonsTable::CommitNewPerson(PERSONS& recItem, const CSmartArray<PHONE_NUMBERS>& phoneNumbers)
{
	CDatabaseConnection::GetInstance().OpenSession();
	CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

	CPhoneNumbersTable oPhoneNumbersTable;

	CDatabaseConnection::GetInstance().BeginTrans();

	for (INT_PTR i = 0; i < phoneNumbers.GetCount(); i++)
	{
		if(phoneNumbers.GetAt(i)->nId==-1)
		{
			if (!oPhoneNumbersTable.Insert(*phoneNumbers.GetAt(i))) 
			{
				CDatabaseConnection::GetInstance().RollbackTrans();
				return false;
			}
		}
	}

	if (Insert(recItem))
	{
		CDatabaseConnection::GetInstance().CommitTrans();
		return true;
	}
	else {
		CDatabaseConnection::GetInstance().RollbackTrans();
		return false;
	}
}