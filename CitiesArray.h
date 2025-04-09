#pragma once

#include <afx.h>
#include "Cities.h"
#include "afxcoll.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesArray


/// <summary>
/// Клас който дефинира масив от записи на таблицата CITIES.
/// </summary>
class CCitiesArray : public CPtrArray
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------     
public:
    CCitiesArray() {}
    virtual ~CCitiesArray() 
    {
        if(!IsEmpty())
        {
            AfxMessageBox(_T("CCitiesArray destructor has been called to clear out the heap memory"));

            for (int i = 0; i < GetSize(); i++)
            {
                delete GetAt(i);
            }
        }
    }

// Methods
// ----------------


// Overrides
// ----------------


// Members
// ----------------
};
