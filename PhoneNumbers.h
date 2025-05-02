#pragma once

#include <afxtempl.h>
#include "SmartArray.h"

#define MAX_PHONE_NUMBER 11
/// <summary> Структура за съхранение на информация за телефонните номера /// </summary>
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