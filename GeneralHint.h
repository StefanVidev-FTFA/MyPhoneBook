#pragma once

#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// CGeneralHint

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
