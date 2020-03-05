#pragma once
#include <climits>
#include <memory>
#include <cassert>

#include "type_traits.h"
#include "math.h"


class node_t {
public:
    virtual ~node_t() = default;
};


template <int _tN>
struct make_class {
    enum {
        value = _tN | 0x80000000
    };
};

template <typename _T>
struct type_value {
    enum {
        value = 0xFFFFFFFF
    };
};

template <int _tN>
struct type {
    typedef std::nullptr_t ptype;
    typedef std::nullptr_t rtype;
};


template <typename _T>
std::unique_ptr<node_t> make_node(_T value) {
    return std::unique_ptr<node_t>((node_t*)new _T(value));
}

template <int _tN>
std::unique_ptr<node_t> make_node() {
    return std::unique_ptr<node_t>((node_t*)new typename type<make_class<_tN>::value>::rtype);
}


template <typename _rT>
_rT* get(std::unique_ptr<node_t>&& ptr) {
    assert(ptr.get() != nullptr);
    return (_rT*)(ptr.get());
}

template <typename _rT>
_rT* get(std::unique_ptr<node_t>& ptr) {
    assert(ptr.get() != nullptr);
    return (_rT*)(ptr.get());
}


template <int _tN>
typename type<_tN>::rtype get(typename type<_tN>::ptype&& value) {
    return static_cast<typename type<_tN>::rtype>(value);
}

template <int _tN>
typename type<_tN>::rtype get(typename type<_tN>::ptype& value) {
    return static_cast<typename type<_tN>::rtype>(value);
}

template <int _tN>
typename type<_tN>::rtype* get(std::unique_ptr<typename type<_tN>::ptype>&& ptr) {
    assert(ptr.get() != nullptr);
    return (typename type<_tN>::rtype*)(ptr.get());
}

template <int _tN>
typename type<_tN>::rtype* get(std::unique_ptr<typename type<_tN>::ptype>& ptr) {
    assert(ptr.get() != nullptr);
    return (typename type<_tN>::rtype*)(ptr.get());
}
