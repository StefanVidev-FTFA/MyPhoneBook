#pragma once

#include "SmartArray.h"
#include "PersonsData.h"
#include "GeneralHint.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData
/// <summary> ���� �� extend-���� �� �������� �� CDocument, � ��� ������ � ��������� �� ������ ����� </summary>
class CCommonDocument : public CDocument
{
// Constructor / Destructor
// ----------------
protected:
    CCommonDocument() noexcept = default;
public:
    virtual ~CCommonDocument() = default;
};