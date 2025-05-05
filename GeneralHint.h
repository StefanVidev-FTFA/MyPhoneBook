#pragma once

#include <afx.h>

/////////////////////////////////////////////////////////////////////////////
// CGeneralHint
/// <summary> ���� ������ �� ���������� �� ���������� �� hint-����� �� ��������� � ������ �����.</summary>
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
