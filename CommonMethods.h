#pragma once

#include "PhoneTypes.h"
#include "Persons.h"
#include "Macros.h"

class  CUtils
{
public:
    static bool IsEven(int x)
    {
        return x % 2 == 0;
    }
    static void MessageWithLong(CString message, long lnumber)
    {
        CString strNotify;
        strNotify.Format(message, lnumber);
        MESSAGE_INFO(strNotify);
    }
    static void MessageWithInt(CString message, int nNumber)
    {
        CString strNotify;
        strNotify.Format(message, nNumber);
        MESSAGE_INFO(strNotify);
    }
    static void MessageWithStr(CString message, CString str)
    {
        CString strNotify;
        strNotify.Format(message, str);
        MESSAGE_INFO(strNotify);
    }
    static CString QueryWithStr(CString message, CString str) {
        CString strQuery;
        strQuery.Format(message, str);
        return strQuery;
    }

    template <typename TableType>
    static CString GetFinalQuery(CString strQuery)
    {
		CString finalQuery;

        CString strTableName = CString(typeid(TableType).name());
        strTableName.Replace(_T("struct "), _T(""));
        strTableName.Trim();

        finalQuery.Format(strQuery, strTableName);
        return finalQuery;
    }

    template <typename TableType>
    static CString GetFinalQuery(CString strQuery,long lId)
    {
        CString finalQuery;

        CString strTableName = CString(typeid(TableType).name());
        strTableName.Replace(_T("struct "), _T(""));
        strTableName.Trim();

        finalQuery.Format(strQuery, strTableName, lId);
        return finalQuery;
    }

    template <typename TableType>
    static bool CheckIfItCointains(const CSmartArray<TableType>& phoneNumbers, const TableType& recNumber, int& index)
    {
        bool itsContained = false;
        for (INT_PTR newNumbersIndex = 0; newNumbersIndex < phoneNumbers.GetCount(); newNumbersIndex++)
        {
            int newIndex = phoneNumbers.GetAt(newNumbersIndex)->nId;
            int dbIndex = recNumber.nId;

            if (dbIndex == newIndex)
            {
                index = newNumbersIndex;
                itsContained = true;
                break;
            }
        }
        return itsContained;
    }

    static int CALLBACK CompareByName(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
    {
        CListCtrl* pList = reinterpret_cast<CListCtrl*>(lParamSort);
        CString strItem1 = pList->GetItemText((int)lParam1, 1); // Column 1 = Name
        CString strItem2 = pList->GetItemText((int)lParam2, 1);
        return strItem1.CompareNoCase(strItem2); // Ascending A–Z
    }
};
