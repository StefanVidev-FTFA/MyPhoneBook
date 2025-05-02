#pragma once
#include "pch.h"
#include <atlbase.h>
#include <atlcom.h>
#include <iostream>
#include <atldbcli.h>
#include <afxwin.h>
#include "Macros.h"
#include "CitiesAccessor.h"
#include "CommonMethods.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable
class CCitiesTable : public CBaseTable<CITIES, CCitiesAccessor>
{
};