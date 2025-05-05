#include "pch.h"
#include "PersonsData.h"

// Methods
// ----------------
bool CPersonsData::AddPerson(PERSONS& recPerson, const CSmartArray<PHONE_NUMBERS>& phoneNumbers)
{
	CDatabaseConnection::GetInstance().OpenSession();
	CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

	CPhoneNumbersTable oPhoneNumbersTable;

	CDatabaseConnection::GetInstance().BeginTransaction();


	if (!Insert(recPerson))
	{
		CDatabaseConnection::GetInstance().RollbackTransaction();
		return false;
	}
	int nTargetPersonId = recPerson.nId;


	for (INT_PTR i = 0; i < phoneNumbers.GetCount(); i++)
	{
		if (phoneNumbers.GetAt(i)->nId == 0)
		{
			PHONE_NUMBERS* pRecPhoneNumber = phoneNumbers.GetAt(i);
			if (pRecPhoneNumber == NULL)
				continue;

			pRecPhoneNumber->nPersonId = nTargetPersonId;
			if (!oPhoneNumbersTable.Insert(*phoneNumbers.GetAt(i)))
			{
				CDatabaseConnection::GetInstance().RollbackTransaction();
				return false;
			}
		}
	}

	CDatabaseConnection::GetInstance().CommitTransaction();
	return true;
}

bool CPersonsData::UpdatePerson(const PERSONS& recPerson,CSmartArray<PHONE_NUMBERS>& newPhoneNumbers)
{
	CDatabaseConnection::GetInstance().OpenSession();
	CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();

	CPhoneNumbersTable oPhoneNumbersTable;
	CSmartArray<PHONE_NUMBERS> dataBasePhoneNumbers;
	if (!oPhoneNumbersTable.GetPersonsPhoneNumbers(dataBasePhoneNumbers, recPerson.nId))
		return false;

	CDatabaseConnection::GetInstance().BeginTransaction();

	if (!UpdateById(recPerson.nId,recPerson))
	{
		CDatabaseConnection::GetInstance().RollbackTransaction();
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
				CDatabaseConnection::GetInstance().RollbackTransaction();
				return false;
			}
		}
	}

	for (INT_PTR index = 0; index < dataBasePhoneNumbers.GetCount(); index++)
	{
		PHONE_NUMBERS* pRecDbNumber = dataBasePhoneNumbers.GetAt(index);
		if (pRecDbNumber == NULL)
			continue;

		int nIndexHolder = -1;
		if (CUtils::CheckIfItCointains(newPhoneNumbers, *pRecDbNumber, nIndexHolder))
		{
			if (nIndexHolder != -1)
			{
				PHONE_NUMBERS* pNewRecNumber = newPhoneNumbers.GetAt(nIndexHolder);
				if (pNewRecNumber == NULL)
					continue;

				if (!oPhoneNumbersTable.UpdateById(pNewRecNumber->nId, *pNewRecNumber))
				{
					CDatabaseConnection::GetInstance().RollbackTransaction();
					return false;
				}
			}
		}
		else 
		{

			if (!oPhoneNumbersTable.DeleteWhereId(pRecDbNumber->nId))
			{
				CDatabaseConnection::GetInstance().RollbackTransaction();
				return false;
			}
		}
	}

	CDatabaseConnection::GetInstance().CommitTransaction();
	return true;
}

bool CPersonsData::DeletePerson(const long lPersonId)
{
	CDatabaseConnection::GetInstance().OpenSession();
	CSession& oSession = CDatabaseConnection::GetInstance().GetCurrentSession();


	CPhoneNumbersTable oPhoneNumbersTable;
	CSmartArray<PHONE_NUMBERS> dataBasePhoneNumbers;
	if (!oPhoneNumbersTable.GetPersonsPhoneNumbers(dataBasePhoneNumbers, lPersonId))
		return false;

	CDatabaseConnection::GetInstance().BeginTransaction();

	for (INT_PTR index = 0; index < dataBasePhoneNumbers.GetCount(); index++)
	{
		PHONE_NUMBERS* pRecDbNumber = dataBasePhoneNumbers.GetAt(index);
		if (pRecDbNumber == NULL)
			continue;

		if (!oPhoneNumbersTable.DeleteWhereId(pRecDbNumber->nId))
		{
			CDatabaseConnection::GetInstance().RollbackTransaction();
			return false;
		}
	}

	if (!DeleteWhereId(lPersonId))
	{
		CDatabaseConnection::GetInstance().RollbackTransaction();
		return false;
	}

	CDatabaseConnection::GetInstance().CommitTransaction();
	return true;
}
