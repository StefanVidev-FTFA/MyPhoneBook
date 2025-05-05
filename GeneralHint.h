#pragma once

#include <afx.h>

/////////////////////////////////////////////////////////////////////////////
// CGeneralHint
/// <summary> Клас служещ за съхранение на информация за hint-овете на таблиците в базата данни.</summary>
template<typename TableType>
class CGeneralHint : public CObject
{
// Constructor / Destructor
// ----------------
public:
    CGeneralHint(const TableType& recItem)
        : m_recItem(recItem)
    {
    }
    virtual ~CGeneralHint() {}

// Members
// ----------------
public:
    TableType m_recItem;
};
