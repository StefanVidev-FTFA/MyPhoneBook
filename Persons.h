#pragma once
#include <afxtempl.h>
#include "SmartArray.h"

#define MAX_ANY_NAME 41
#define MAX_EGN 11
#define MAX_ADRESS 256

/// <summary> </summary>
struct PERSONS 
{
    /// <summary> </summary>
    int nId;
    /// <summary> </summary>
    int nUpdateCounter;
    /// <summary> </summary>
    TCHAR szFirstName[MAX_ANY_NAME];
    /// <summary> </summary>
    TCHAR szMiddleName[MAX_ANY_NAME];
    /// <summary> </summary>
    TCHAR szLastName[MAX_ANY_NAME];
    /// <summary> </summary>
    TCHAR szEgn[MAX_EGN];
    /// <summary> </summary>
    int nCityId;
    /// <summary> </summary>
    TCHAR szAddress[MAX_ADRESS];

    PERSONS()
    {
        SecureZeroMemory(this, sizeof(*this));
    }
};
