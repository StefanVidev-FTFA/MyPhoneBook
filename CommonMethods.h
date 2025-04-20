#pragma once

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
}
