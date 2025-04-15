#pragma once
#include "CitiesAccessor.h"
#include <atlbase.h>
#include <atlcom.h>
#include "CitiesArray.h"
/////////////////////////////////////////////////////////////////////////////
// CCitiesTable


/// <summary>
/// ���� �� ������ � ��������� CITIES.
/// </summary>
class CCitiesTable : public CCommand<CAccessor<CCitiesAccessor>>
{
// Methods
// ----------------
public:

    /// <summary>
	/// ���� ����� ���� �� ��������� ������� � sql � �� ������� ��� ����� �� ������.
    /// </summary>
    bool SelectAll(CCitiesArray& oCitiesArray);
    /// <summary>
    /// ������ ���� ��������� �� ���������������� �����.
    /// </summary>
    bool SelectWhereID(const long lID, CITIES& recCity);
    /// <summary>
    /// ���������� ���� ����� �������� �� ��������� ���������������� �����.
    /// </summary>
    bool UpdateWhereID(const long lID,const CITIES& recCity);
    /// <summary>
	/// ������� ��� ����.
    /// </summary>
    bool Insert(const CITIES& recCity);
    /// <summary>
	/// ������� ����� �� ���� �� ���������������� �����.
    /// </summary>
    bool DeleteWhereID(const long lID);
};