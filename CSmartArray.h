#pragma once
#include "pch.h"
#include <afx.h>
#include "Cities.h"
#include "afxcoll.h"
#include "afxtempl.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesArray

/// <summary> Клас който дефинира масив от записи на таблицата CITIES. /// </summary>
template <typename Ttable>
class CSmartArray: public CTypedPtrArray<CPtrArray,Ttable*>
{
    // Constructor / Destructor
    // ----------------     
public:
    CSmartArray() {}
    virtual ~CSmartArray()
    {
        if (!IsEmpty())
        {
            for (int i = 0; i < this->GetSize(); i++)
            {
                delete this->(GetAt(i));
            }
        }
    }
};
