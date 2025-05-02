#include "pch.h"
#include "PersonsData.h"




bool CPersonsData::AddPerson(PERSONS& recPerson, const CSmartArray<PHONE_NUMBERS>& phoneNumbers)
{
	CDatabaseConnection::GetInstance().OpenSession();
	CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

	CPhoneNumbersTable oPhoneNumbersTable;

	CDatabaseConnection::GetInstance().BeginTrans();


	if (!Insert(recPerson))
	{
		CDatabaseConnection::GetInstance().RollbackTrans();
		return false;
	}
	int nTargetPersonId = recPerson.nId;

	for (INT_PTR i = 0; i < phoneNumbers.GetCount(); i++)
	{
		if (phoneNumbers.GetAt(i)->nId == -1)
		{
			PHONE_NUMBERS* pRecPhoneNumber = phoneNumbers.GetAt(i);
			if (pRecPhoneNumber == NULL)
				continue;

			pRecPhoneNumber->nPersonId = nTargetPersonId;
			if (!oPhoneNumbersTable.Insert(*phoneNumbers.GetAt(i)))
			{
				CDatabaseConnection::GetInstance().RollbackTrans();
				return false;
			}
		}
	}

	CDatabaseConnection::GetInstance().CommitTrans();
	return true;
}

bool CPersonsData::UpdatePerson(const PERSONS& recPerson,CSmartArray<PHONE_NUMBERS>& newPhoneNumbers)
{
	CDatabaseConnection::GetInstance().OpenSession();
	CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

	CPhoneNumbersTable oPhoneNumbersTable;
	CSmartArray<PHONE_NUMBERS> dataBasePhoneNumbers;
	oPhoneNumbersTable.GetPersonsPhoneNumbers(dataBasePhoneNumbers,recPerson.nId);

	CDatabaseConnection::GetInstance().BeginTrans();

	if (!UpdateById(recPerson.nId,recPerson))
	{
		CDatabaseConnection::GetInstance().RollbackTrans();
		return false;
	}

	for (INT_PTR index = 0; index < newPhoneNumbers.GetCount(); index++)
	{
		PHONE_NUMBERS* pRecPhoneNumber = newPhoneNumbers.GetAt(index);
		if (pRecPhoneNumber == NULL)
			continue;

		if (pRecPhoneNumber->nId == 0) 
		{

			if (!oPhoneNumbersTable.Insert(*pRecPhoneNumber))
			{
				CDatabaseConnection::GetInstance().RollbackTrans();
				return false;
			}
			delete pRecPhoneNumber;
			newPhoneNumbers.RemoveAt(index);
		}
	}

	for (INT_PTR index = 0; index < dataBasePhoneNumbers.GetCount(); index++)
	{
		PHONE_NUMBERS* pRecDbNumber = dataBasePhoneNumbers.GetAt(index);
		if (pRecDbNumber == NULL)
			continue;

		if (Utils::CheckIfItCointains(newPhoneNumbers, *pRecDbNumber))
		{
			if (!oPhoneNumbersTable.UpdateById(pRecDbNumber->nId,*pRecDbNumber))
			{
				CDatabaseConnection::GetInstance().RollbackTrans();
				return false;
			}
		}
		else 
		{

			if (!oPhoneNumbersTable.DeleteWhereId(pRecDbNumber->nId))
			{
				CDatabaseConnection::GetInstance().RollbackTrans();
				return false;
			}
		}
	}



	CDatabaseConnection::GetInstance().CommitTrans();
	return true;
}