#pragma once
#include "pch.h"
#include "CitiesAccessor.h"
#include <atlbase.h>
#include <atlcom.h>
#include "CitiesArray.h"
#include "SmartArray.h"
#include "CitiesTable.h"
#include <iostream>
#include <atldbcli.h>
#include <afxwin.h>
#include "DatabaseConnection.h"
#include "Macros.h"
#include "CommonMethods.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary> Клас за работа с таблицата CITIES. </summary>
class CCitiesTable : public CCommand<CAccessor<CCitiesAccessor>>
{
// Methods
// ----------------

};