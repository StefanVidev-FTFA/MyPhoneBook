#pragma once
#include "CitiesAccessor.h"
#include <atlbase.h>
#include <atlcom.h>
#include "CitiesArray.h"
/////////////////////////////////////////////////////////////////////////////
// CCitiesTable


/// <summary>
/// Клас за работа с таблицата CITIES.
/// </summary>
class CCitiesTable : public CCommand<CAccessor<CCitiesAccessor>>
{
// Methods
// ----------------
public:

    /// <summary>
	/// Чете всеки град от таблицата градове в sql и ги въвежда във масив от записи.
    /// </summary>
    bool SelectAll(CCitiesArray& oCitiesArray);
    /// <summary>
    /// Избира град възоснова на идентификационен номер.
    /// </summary>
    bool SelectWhereID(const long lID, CITIES& recCity);
    /// <summary>
    /// Модифицира град който отговарч на конкретен идентификационен номер.
    /// </summary>
    bool UpdateWhereID(const long lID,const CITIES& recCity);
    /// <summary>
	/// Въвежда нов град.
    /// </summary>
    bool Insert(const CITIES& recCity);
    /// <summary>
	/// ИЗтрива запис за град по идентификационен номер.
    /// </summary>
    bool DeleteWhereID(const long lID);
};