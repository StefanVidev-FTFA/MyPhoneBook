#include "pch.h"
#include "CitiesArray.h"
#include "CitiesTable.h"



/// <summary> Клас за поддържане на бизнес логиката за телефонният указател. /// </summary>
class CCitiesData
{
private:
    // Constants
    // ----------------
    CCitiesTable m_oCitiesTable;


    // Constructor / Destructor
    // ----------------
public:
    CCitiesData();
    ~CCitiesData();


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
    bool UpdateWhereID(const long lID, CITIES& recCity);
    /// <summary>
    /// Въвежда нов град.
    /// </summary>
    bool Insert(const CITIES& recCity);
    /// <summary>
    /// ИЗтрива запис за град по идентификационен номер.
    /// </summary>
    bool DeleteWhereID(const long lID);
};
// Overrides
// ----------------


// Members
// ----------------