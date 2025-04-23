#pragma once

template <typename TRecord>
class IAccessorBase {
public:
    virtual TRecord& GetRecord() = 0;
};