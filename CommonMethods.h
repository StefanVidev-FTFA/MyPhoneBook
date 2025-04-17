#pragma once


namespace Utils {
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
}
