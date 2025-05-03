#pragma once

#include "SmartArray.h"
#include "PersonsData.h"
#include "GeneralHint.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData
/// <summary> Клас за extend-ване на логиката на CDocument, с цел работа с градовете от базата данни </summary>
class CCommonDocument : public CDocument
{
// Constructor / Destructor
// ----------------
protected:
    CCommonDocument() noexcept = default;
public:
    virtual ~CCommonDocument() = default;
};