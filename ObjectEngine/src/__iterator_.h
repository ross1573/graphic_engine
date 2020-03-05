#pragma once
#include "../../ObjectEngine/type"

namespace __base_ {
    class __iterator_ : protected node_t {
    public:
        virtual ~__iterator_() = default;
    };

    template <typename _kT>
    class __iterator_typed : protected __iterator_ {
    protected:
        _kT __key;
        
    public:
        __iterator_typed(_kT key) : __key(key) {};
        virtual ~__iterator_typed() = default;
    };
}
