#pragma once

#include <afxtempl.h>
#include <afxstr.h> 
#include "SmartArray.h"

#define MAX_PHONE_TYPE 31

/// <summary> ��������� �� ���������� �� ���������� �� ��������� ������ </summary>
struct PHONE_TYPES {

    /// <summary> �������� ������������� �� ��� </summary>
    int nId;
    /// <summary> Versioning </summary>
    int nUpdateCounter;
    /// <summary> ����� �� �������� </summary>
    TCHAR szPhoneType[MAX_PHONE_TYPE];

    PHONE_TYPES()
    {
        SecureZeroMemory(this, sizeof(*this));
    }

};