#pragma once

#include <afx.h>

/////////////////////////////////////////////////////////////////////////////
// CGeneralHint
/// <summary> Клас служещ за съхранение на информация за hint-овете на таблиците в базата данни.</summary>
template<typename tableType>
class CGeneralHint : public CObject
{
// Constructor / Destructor
// ----------------
public:
    CGeneralHint(const tableType& recItem)
        : m_recItem(recItem)
    {
    }
    virtual ~CGeneralHint() {}

// Members
// ----------------
public:
    tableType m_recItem;
};
