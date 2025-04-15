#pragma once
#include <afxtempl.h>


#define MAX_CITY_NAME 41
#define MAX_REGION_NAME 41

/// <summary> ��������� �� ���������� �� ���������� �� ��������� /// </summary>
struct CITIES {
    /// <summary> �������� ������������� �� ���/// </summary>
    int nId;
    /// <summary> Versioning /// </summary>
    int nUpdateCounter;
    /// <summary>������������ �� ������</summary>
    char szCityName[MAX_CITY_NAME];
    /// <summary>������������ �� �������</summary>
    char szRegion[MAX_REGION_NAME];

    CITIES()
    {
        SecureZeroMemory(this, sizeof(*this));
    }
};