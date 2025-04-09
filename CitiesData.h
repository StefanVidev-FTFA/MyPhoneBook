#include "pch.h"
#include "CitiesArray.h"
#include "CitiesTable.h"



/// <summary> ���� �� ���������� �� ������ �������� �� ����������� ��������. /// </summary>
class CCitiesData
{
private:
    // Constants
    // ----------------
    CCitiesTable m_oCitiesTable;


    // Constructor / Destructor
    // ----------------
public:
    CCitiesData();
    ~CCitiesData();


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
    bool UpdateWhereID(const long lID, CITIES& recCity);
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