#pragma once

#include <afxtempl.h>
#include <afxstr.h> 
#include "SmartArray.h"

#define MAX_PHONE_TYPE 31

/// <summary> Структура за съхранение на информация за телефонни типове </summary>
struct PHONE_TYPES {

    /// <summary> Уникален идентификатор за ред </summary>
    int nId;
    /// <summary> Versioning </summary>
    int nUpdateCounter;
    /// <summary> Типът на телефона </summary>
    TCHAR szPhoneType[MAX_PHONE_TYPE];

    PHONE_TYPES()
    {
        SecureZeroMemory(this, sizeof(*this));
    }

};