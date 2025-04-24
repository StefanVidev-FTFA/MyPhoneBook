#pragma once

#include "PhoneTypes.h"
#include <atldbcli.h>
#include "BaseAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesAccessor

class CPhoneTypesAccessor : CBaseAccessor<PHONE_TYPES> 
{
protected:

		BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor,2)
			BEGIN_ACCESSOR(0,true)
				COLUMN_ENTRY(1,m_recItem.nId)
			END_ACCESSOR()

			BEGIN_ACCESSOR(1, true)
				COLUMN_ENTRY(2, m_recItem.nUpdateCounter)
				COLUMN_ENTRY(3, m_recItem.szPhoneType)
			END_ACCESSOR()
		END_ACCESSOR_MAP()
};
