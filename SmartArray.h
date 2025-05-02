#pragma once
#include "pch.h"
#include <afx.h>
#include "Cities.h"
#include "afxcoll.h"
#include "afxtempl.h"

/////////////////////////////////////////////////////////////////////////////
// CSmartArray

/// <summary> Клас който дефинира масив от записи на някои от таблиците. /// </summary>
template <typename Ttable>
class CSmartArray: public CTypedPtrArray<CPtrArray,Ttable*>
{
    // Constructor / Destructor
    // ----------------     
public:
    CSmartArray() {};
    virtual ~CSmartArray()
    {
        if (!IsEmpty())
        {
            for (INT_PTR nIndex = 0; nIndex < GetSize(); nIndex++)
            {
                const Ttable* pItem = GetAt(nIndex);
                if (!pItem)
                    continue;

                delete GetAt(nIndex);
            }
        }
    }
};
