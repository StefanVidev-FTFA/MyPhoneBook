#pragma once
#include <afxtempl.h>
#include "SmartArray.h"

#define MAX_ANY_NAME 41
#define MAX_EGN 11
#define MAX_ADRESS 256
struct PERSONS {

    int nId;
    int nUpdateCounter;
    TCHAR szFirstName[MAX_ANY_NAME];
    TCHAR szMiddleName[MAX_ANY_NAME];
    TCHAR szLastName[MAX_ANY_NAME];
    TCHAR szEgn[MAX_EGN];
    int nCityId;
    TCHAR szAddress[MAX_ADRESS];

    PERSONS()
    {
        SecureZeroMemory(this, sizeof(*this));
    }
};