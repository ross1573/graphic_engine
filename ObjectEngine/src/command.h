#pragma once
#include <functional>
#include <queue>
#include <tuple>
#include <thread>
#include <future>
#include <string>
#include <stdexcept>

#include "../../ObjectEngine/type"

    
namespace __base_ {
    class __command_ : private node_t {
    public:
        virtual ~__command_() = default;
    };
}


template <typename _cT, typename _T>
class command_queue : __base_::__command_ {
public:
    virtual ~command_queue() = default;
};
