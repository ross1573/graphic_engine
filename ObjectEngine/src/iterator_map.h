#pragma once
#include "__iterator_.h"


template <typename _kT>
class iterator_map : protected __base_::__iterator_typed<_kT> {
public:
    iterator_map(__base_::__iterator_typed<_kT>& i) : __base_::__iterator_typed<_kT>(       i) {}
    iterator_map()                                  : __base_::__iterator_typed<_kT>((_kT)  0) {}
    iterator_map(bool key)                          : __base_::__iterator_typed<_kT>((_kT)key) {}
    iterator_map(char key)                          : __base_::__iterator_typed<_kT>((_kT)key) {}
    iterator_map(short key)                         : __base_::__iterator_typed<_kT>((_kT)key) {}
    iterator_map(unsigned short key)                : __base_::__iterator_typed<_kT>((_kT)key) {}
    iterator_map(int key)                           : __base_::__iterator_typed<_kT>((_kT)key) {}
    iterator_map(unsigned key)                      : __base_::__iterator_typed<_kT>((_kT)key) {}
    iterator_map(long key)                          : __base_::__iterator_typed<_kT>((_kT)key) {}
    iterator_map(unsigned long key)                 : __base_::__iterator_typed<_kT>((_kT)key) {}
    iterator_map(long long key)                     : __base_::__iterator_typed<_kT>((_kT)key) {}
    iterator_map(unsigned long long key)            : __base_::__iterator_typed<_kT>((_kT)key) {}
    iterator_map(float key)                         : __base_::__iterator_typed<_kT>((_kT)key) {}
    iterator_map(double key)                        : __base_::__iterator_typed<_kT>((_kT)key) {}
    iterator_map(long double key)                   : __base_::__iterator_typed<_kT>((_kT)key) {}
    virtual ~iterator_map() = default;
    
    template <typename _pT> bool operator== (_pT key) { return this->__key == (_kT)key; }
    template <typename _pT> bool operator<  (_pT key) { return this->__key <  (_kT)key; }
    template <typename _pT> bool operator>  (_pT key) { return this->__key >  (_kT)key; }
                            void operator++ () { this->__key += 1; }
                            void operator-- () { this->__key -= 1; }
    template <typename _pT> void operator() (_pT key) { this->__key  = key; }
    template <typename _pT> void operator=  (_pT key) { this->__key  = key; }
    template <typename _pT> void operator+= (_pT key) { this->__key += key; }
    template <typename _pT> iterator_map& operator+  (_pT key) { this->__key += key; return *this; }
    
    friend bool operator>  (      iterator_map& k1,       iterator_map& k2) { return k1.__key > k2.__key; }
    friend bool operator>  (const iterator_map& k1, const iterator_map& k2) { return k1.__key > k2.__key; }
    friend bool operator<  (      iterator_map& k1,       iterator_map& k2) { return k1.__key < k2.__key; }
    friend bool operator<  (const iterator_map& k1, const iterator_map& k2) { return k1.__key < k2.__key; }
    friend bool operator== (      iterator_map& k1,       iterator_map& k2) { return k1.__key == k2.__key; }
    friend bool operator== (const iterator_map& k1, const iterator_map& k2) { return k1.__key == k2.__key; }
    friend bool operator!= (      iterator_map& k1,       iterator_map& k2) { return k1.__key != k2.__key; }
    friend bool operator!= (const iterator_map& k1, const iterator_map& k2) { return k1.__key != k2.__key; }
};
