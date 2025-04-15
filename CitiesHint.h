#pragma once

#include <afx.h>
#include "Cities.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesHint


class CCitiesHint : public CObject
{
    // Constructor / Destructor
    // ----------------
public:
    CCitiesHint(int nId, const CITIES& recCity)
        : m_nTargetId(nId), m_recCity(recCity)
    {
    }
    CCitiesHint(CCitiesArray* pArray)
    {
        if (pArray != nullptr)
            m_oCitiesArray.Append(*pArray);
    }
    virtual ~CCitiesHint() {}


    // Members
    // ----------------
public:
    int m_nTargetId;
    CITIES m_recCity;
    CCitiesArray m_oCitiesArray;
};
