#pragma once

#include "PhoneTypes.h"
#include "Persons.h"
#include "Macros.h"

namespace Utils
{
    inline bool IsEven(int x)
    {
        return x % 2 == 0;
    }
    inline void MessageWithLong(CString message,long lnumber)
    {
        CString strNotify;
        strNotify.Format(message, lnumber);
        MESSAGE_INFO(strNotify);
    }
    inline void MessageWithInt(CString message, int nNumber)
    {
        CString strNotify;
        strNotify.Format(message, nNumber);
        MESSAGE_INFO(strNotify);
    }
    inline void MessageWithStr(CString message, CString str)
    {
        CString strNotify;
        strNotify.Format(message, str);
        MESSAGE_INFO(strNotify);
    }
    inline CString QueryWithStr(CString message, CString str) {
        CString strQuery;
        strQuery.Format(message, str);
        return strQuery;
    }
    template <typename tableType>
    inline CString GetTableName()
    {
        CString type;
        if (typeid(tableType) == typeid(PHONE_NUMBERS))
        {
            type = _T("PHONE_NUMBERS");
        }
        else if (typeid(tableType) == typeid(CITIES))
        {
            type = _T("CITIES");
        }
        else if (typeid(tableType) == typeid(PERSONS))
        {
            type = _T("PERSONS");
        }
        else if (typeid(tableType) == typeid(PHONE_TYPES))
        {
            type = _T("PHONE_TYPES");
        }
        return type;
    }
}
