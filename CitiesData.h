#ifndef CITIESDATA_H
#define CITIESDATA_H

#include "pch.h"
#include "CitiesArray.h"
#include "CitiesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary> ���� ������ �� ������������ �� ������ �������� �� ��������� /// </summary>
class CCitiesData
{
private:
    // Constants
    // ----------------
    CCitiesTable m_oCitiesTable;


    // Methods
    // ----------------
public:
    /// <summary> ���� ����� ���� �� ��������� ������� � sql � �� ������� ��� ����� �� ������. </summary>
    
    template <typename tableType>
    bool SelectAll(CSmartArray<tableType>& oTableItemsArray)
    {
        return m_oCitiesTable.SelectAll(oTableItemsArray);
    }
    /// <summary> ������ ���� ��������� �� ���������������� ����� </summary>
    bool SelectWhereID(const long lID, CITIES& recCity);
    /// <summary>���������� ���� ����� �������� �� ��������� ���������������� �����</summary>
    bool UpdateWhereID(const long lID,const CITIES& recCity);
    /// <summary> ������� ��� ���� </summary>
    bool Insert(const CITIES& recCity);
    /// <summary> ������� ����� �� ���� �� ���������������� ����� </summary>
    bool DeleteWhereID(const long lID);
};
#endif // !CITIESDATA_H