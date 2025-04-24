#pragma once

#include "pch.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atldbcli.h>
#include <afxwin.h>
#include "Macros.h"
#include "PhoneNumbersAccessor.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsTable


class CPhoneNumbersTable : public CBaseTable<PHONE_NUMBERS, CPhoneNumbersAccessor>
{

};