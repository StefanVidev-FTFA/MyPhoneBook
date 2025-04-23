#pragma once
#include "pch.h"
#include <atlbase.h>
#include <atlcom.h>
#include "SmartArray.h"
#include <iostream>
#include <atldbcli.h>
#include <afxwin.h>
#include "DatabaseConnection.h"
#include "Macros.h"
#include "CommonMethods.h"
#include "PhoneNumbersAccessor.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsTable


class CPersonsTable : public CBaseTable<PHONE_NUMBERS,CPhoneNumbersAccessor>
{

};