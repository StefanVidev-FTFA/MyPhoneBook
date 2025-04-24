#pragma once
#include <afxtempl.h>
#include <afxstr.h> 
#include "SmartArray.h"

#define MAX_PHONE_TYPE 31
struct PHONE_TYPES {

    int nId;
    int nUpdateCounter;
    TCHAR szPhoneType[MAX_PHONE_TYPE];

    PHONE_TYPES()
    {
        SecureZeroMemory(this, sizeof(*this));
    }

};