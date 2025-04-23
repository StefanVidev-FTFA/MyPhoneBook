template <typename RecordType>
class CBaseAccessor {
public:
    virtual RecordType GetRecord() const=0;
    virtual ~CBaseAccessor() = default;
};