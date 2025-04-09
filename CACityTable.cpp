#include "pch.h"
#include "CACityTable.h"




void CACityTable::SetCityData() {
    m_recCity.nUpdateCounter = 0;
    strncpy_s(m_recCity.szCityName, "trying here 1", MAX_CITY_NAME - 1);
    strncpy_s(m_recCity.szRegion, "trying here 2", MAX_CITY_NAME - 1);
}