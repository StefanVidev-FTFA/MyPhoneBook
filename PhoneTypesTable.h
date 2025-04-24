#pragma once

#include "pch.h"
#include <atlbase.h>
#include <atlcom.h>
#include <iostream>
#include <atldbcli.h>
#include <afxwin.h>
#include "PhoneTypesAccessor.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsTable


class CPhoneTypesTable : public CBaseTable<PHONE_TYPES, CPhoneTypesAccessor>
{

};