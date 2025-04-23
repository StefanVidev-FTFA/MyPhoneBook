#pragma once

template <typename RecordType>
class CBaseAccessor {
public:
    RecordType& GetRecord() const;
    virtual ~CBaseAccessor() = default;
protected:
    RecordType m_recItem;
};

template<typename RecordType>
inline RecordType& CBaseAccessor<RecordType>::GetRecord() const
{
    return m_recItem;
}
