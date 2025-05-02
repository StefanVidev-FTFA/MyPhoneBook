#pragma once
#include <afxtempl.h>
#include "SmartArray.h"

#define MAX_ANY_NAME 41
#define MAX_EGN 11
#define MAX_ADRESS 256

/// <summary> Структура за съхранение на информация за потребители </summary>
struct PERSONS 
{
    /// <summary> Уникален идентификатор за ред </summary>
    int nId;
    /// <summary> Versioning </summary>
    int nUpdateCounter;
    /// <summary> Име на потребител </summary>
    TCHAR szFirstName[MAX_ANY_NAME];
    /// <summary> Бащино Име на потребител </summary>
    TCHAR szMiddleName[MAX_ANY_NAME];
    /// <summary> Фамилно Име на потребител </summary>
    TCHAR szLastName[MAX_ANY_NAME];
    /// <summary> Уникално ЕГН на потребител</summary>
    TCHAR szEgn[MAX_EGN];
    /// <summary> Идентификатор на град </summary>
    int nCityId;
    /// <summary> Адрес на потребител </summary>
    TCHAR szAddress[MAX_ADRESS];

    PERSONS()
    {
        SecureZeroMemory(this, sizeof(*this));
    }
};
