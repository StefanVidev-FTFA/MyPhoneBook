#ifndef CITIESDATA_H
#define CITIESDATA_H

// Your existing CCitiesData class definition goes here:
#include "pch.h"
#include "CitiesArray.h"
#include "CitiesTable.h"

class CCitiesData
{
private:
    // Constants
    // ----------------
    CCitiesTable m_oCitiesTable;


    // Methods
    // ----------------
public:

    /// <summary>������������ ����� �� ����� </summary>
    bool Initialize();
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
// Overrides
// ----------------


// Members
// ----------------

#endif // !CITIESDATA_H