#include "pch.h"
#include "PersonsData.h"

bool CPersonsData::CommitNewPerson(PERSONS& recPerson, const CSmartArray<PHONE_NUMBERS>& phoneNumbers)
{
	CDatabaseConnection::GetInstance().OpenSession();
	CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

	CPhoneNumbersTable oPhoneNumbersTable;

	CDatabaseConnection::GetInstance().BeginTrans();

	for (INT_PTR i = 0; i < phoneNumbers.GetCount(); i++)
	{
		if (phoneNumbers.GetAt(i)->nId == -1)
		{
			PHONE_NUMBERS& oke = *phoneNumbers.GetAt(i);
			oke.nId = 0;
			if (!oPhoneNumbersTable.Insert(*phoneNumbers.GetAt(i)))
			{
				CDatabaseConnection::GetInstance().RollbackTrans();
				return false;
			}
		}
	}

	if (Insert(recPerson))
	{
		CDatabaseConnection::GetInstance().CommitTrans();
		return true;
	}
	else {
		CDatabaseConnection::GetInstance().RollbackTrans();
		return false;
	}
}