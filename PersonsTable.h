#pragma once

#include "pch.h"
#include <atlbase.h>
#include <atlcom.h>
#include <iostream>
#include <atldbcli.h>
#include <afxwin.h>
#include "PersonsAccessor.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsTable


class CPersonsTable : public CBaseTable<PERSONS, CPersonsAccessor>
{

};