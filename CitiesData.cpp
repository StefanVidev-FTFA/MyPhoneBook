#include "pch.h"
#include "CitiesData.h"


bool CCitiesData::SelectAll(CCitiesArray& oCitiesArray)
{
	return m_oCitiesTable.SelectAll(oCitiesArray);
}
bool CCitiesData::SelectWhereID(const long lID, CITIES& recCity)
{
	return m_oCitiesTable.SelectWhereID(lID, recCity);
}
bool CCitiesData::UpdateWhereID(const long lID, CITIES& recCity)
{
	return m_oCitiesTable.UpdateWhereID(lID, recCity);
}
bool CCitiesData::Insert(const CITIES& recCity)
{
	return m_oCitiesTable.Insert(recCity);
}
bool CCitiesData::DeleteWhereID(const long lID)
{
	return m_oCitiesTable.DeleteWhereID(lID);
}