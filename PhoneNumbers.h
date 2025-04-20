#pragma once
#include <afxtempl.h>
#include "CSmartArray.h"


#define MAX_PHONE_NUMBER 11
struct PHONE_NUMBERS {

    int nId;
    int nUpdateCounter;
    int nPersonId;
    int nPhoneTypeId;
    TCHAR szPhoneNumber[MAX_PHONE_NUMBER];

    PHONE_NUMBERS()
    {
        SecureZeroMemory(this, sizeof(*this));
    }

};
typedef CSmartArray<PHONE_NUMBERS> CSmartPhoneNumbersArray;