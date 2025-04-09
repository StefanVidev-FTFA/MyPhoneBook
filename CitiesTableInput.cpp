#pragma once
#include "pch.h"
#include "Cities.h"
#include <atldbcli.h>
#include "CitiesAccessor.h"

class CCitiesTableInput : public CTable<CCitiesAccessor>
{
public:
    CCitiesTableInput() = default; // Or just omit this entirely

    // You can add convenience methods here if needed
};