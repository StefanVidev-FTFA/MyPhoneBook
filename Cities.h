#pragma once
#include <afxtempl.h>

#define MAX_CITY_NAME 41
#define MAX_REGION_NAME 41

/// <summary> Структура за съхранение на информация за градовете /// </summary>
struct CITIES {
    /// <summary> Уникален идентификатор за ред/// </summary>
    int nId;
    /// <summary> Versioning /// </summary>
    int nUpdateCounter;
    /// <summary>Наименование на градът</summary>
    TCHAR szCityName[MAX_CITY_NAME];
    /// <summary>Наименование на региона</summary>
    TCHAR szRegion[MAX_REGION_NAME];

    CITIES()
    {
        SecureZeroMemory(this, sizeof(*this));
    }
};