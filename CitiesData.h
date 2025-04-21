#ifndef CITIESDATA_H
#define CITIESDATA_H

#include "pch.h"
#include "CitiesArray.h"
#include "CitiesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary> Клас служещ за изпълнението на бизнес логиката на указателя /// </summary>
class CCitiesData
{
private:
    // Constants
    // ----------------
    CCitiesTable m_oCitiesTable;


    // Methods
    // ----------------
public:
    /// <summary> Чете всеки град от таблицата градове в sql и ги въвежда във масив от записи. </summary>
    
    template <typename tableType>
    bool SelectAll(CSmartArray<tableType>& oTableItemsArray)
    {
        return m_oCitiesTable.SelectAll(oTableItemsArray);
    }
    /// <summary> Избира град възоснова на идентификационен номер </summary>
    bool SelectWhereID(const long lID, CITIES& recCity);
    /// <summary>Модифицира град който отговарч на конкретен идентификационен номер</summary>
    bool UpdateWhereID(const long lID,const CITIES& recCity);
    /// <summary> Въвежда нов град </summary>
    bool Insert(const CITIES& recCity);
    /// <summary> Изтрива запис за град по идентификационен номер </summary>
    bool DeleteWhereID(const long lID);
};
#endif // !CITIESDATA_H