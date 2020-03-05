#pragma once
#include <functional>
#include <map>
#include <queue>
#include <tuple>
#include <thread>
#include <future>
#include <stdexcept>

#include "../../ObjectEngine/type"
#include "../../ObjectEngine/iterator"
#include "command.h"


template <typename _cT, typename _rT, typename... _pT>
class command_queue<_cT, _rT(_pT...)> : __base_::__command_ {
public:
    typedef iterator_map<unsigned> id;
    typedef long tick_t;
    typedef std::function<_rT(_cT&, _pT...)> work_t;
    
private:
    std::queue<std::pair<id, std::tuple<_cT*, _pT...>>> __queue;
    std::map<id, work_t> __list;
    std::queue<_rT> __result;
    
    std::thread __exec;
    std::atomic<bool> __active;
    std::future<void> __future[2];
    std::promise<void> __promise[2];
    
    tick_t __sleep_tick = 0;
    bool __sleep = false;
    
public:
    command_queue();
    ~command_queue();
    
    inline void insert(id&, work_t&);
    inline void insert(const id&, const work_t&);
    inline void insert(id&, _cT*, _pT...);
    inline void insert(const id&, const _cT*, const _pT...);
    inline void erase(id&);
    inline void erase(const id&);
    
    inline void execute();
    inline void synchronize();
    inline void sleep(tick_t = -1);
    inline void wake();
    inline bool is_sleeping();
    
    inline std::queue<_rT>& get_result();
    
private:
    void __execute_();
};

    
template <typename _cT, typename _rT>
class command_queue<_cT, _rT()> : __base_::__command_ {
public:
    typedef iterator_map<unsigned> id;
    typedef long tick_t;
    typedef std::function<_rT(_cT&)> work_t;
    
private:
    std::queue<std::pair<id, _cT*>> __queue;
    std::map<id, work_t> __list;
    std::queue<_rT> __result;
    
    std::thread __exec;
    std::atomic<bool> __active;
    std::future<void> __future[2];
    std::promise<void> __promise[2];
    
    tick_t __sleep_tick = 0;
    bool __sleep = false;
    
public:
    command_queue();
    ~command_queue();
    
    inline void insert(id&, work_t&);
    inline void insert(const id&, const work_t&);
    inline void insert(id&, _cT*);
    inline void insert(const id&, const _cT*);
    inline void erase(id&);
    inline void erase(const id&);
    
    inline void execute();
    inline void synchronize();
    inline void sleep(tick_t = -1);
    inline void wake();
    inline bool is_sleeping();
    
    inline std::queue<_rT>& get_result();
    
private:
    void __execute_();
};

    
template <typename _cT, typename... _pT>
class command_queue<_cT, void(_pT...)> : __base_::__command_ {
public:
    typedef iterator_map<unsigned> id;
    typedef long tick_t;
    typedef std::function<void(_cT&, _pT...)> work_t;
    
private:
    std::queue<std::pair<id, std::tuple<_cT*, _pT...>>> __queue;
    std::map<id, work_t> __list;
    
    std::thread __exec;
    std::atomic<bool> __active;
    std::future<void> __future[2];
    std::promise<void> __promise[2];
    
    tick_t __sleep_tick = 0;
    bool __sleep = false;
    
public:
    command_queue();
    ~command_queue();
    
    inline void insert(id&, work_t&);
    inline void insert(const id&, const work_t&);
    inline void insert(id&, _cT*, _pT...);
    inline void insert(const id&, const _cT*, const _pT...);
    inline void erase(id&);
    inline void erase(const id&);
    
    inline void execute();
    inline void synchronize();
    inline void sleep(tick_t = -1);
    inline void wake();
    inline bool is_sleeping();
    
private:
    void __execute_();
};


template <typename _cT>
class command_queue<_cT, void()> : __base_::__command_ {
public:
    typedef iterator_map<unsigned> id;
    typedef long tick_t;
    typedef std::function<void(_cT&)> work_t;
    
private:
    std::queue<std::pair<id, _cT*>> __queue;
    std::map<id, work_t> __list;
    
    std::thread __exec;
    std::atomic<bool> __active;
    std::future<void> __future[2];
    std::promise<void> __promise[2];
    
    tick_t __sleep_tick = 0;
    bool __sleep = false;
    
public:
    command_queue();
    ~command_queue();
    
    inline void insert(id&, work_t&);
    inline void insert(const id&, const work_t&);
    inline void insert(id&, _cT*);
    inline void insert(const id&, const _cT*);
    inline void erase(id&);
    inline void erase(const id&);
    
    inline void execute();
    inline void synchronize();
    inline void sleep(tick_t = -1);
    inline void wake();
    inline bool is_sleeping();
    
private:
    void __execute_();
};


template <typename _cT, typename _rT, typename... _pT>
command_queue<_cT, _rT(_pT...)>::command_queue() {
    __active = false;
    __future[0] = __promise[0].get_future();
    __future[1] = __promise[1].get_future();
    __promise[1].set_value();
    __exec = std::thread(&command_queue::__execute_, this);
}

template <typename _cT, typename _rT, typename... _pT>
command_queue<_cT, _rT(_pT...)>::~command_queue() {
    __active = false;
    __promise[0].set_value();
    __exec.join();
}

template <typename _cT, typename _rT, typename... _pT>
void command_queue<_cT, _rT(_pT...)>::insert(id &work_id, work_t &work) {
    __list.insert(std::make_pair(work_id, work));
}

template <typename _cT, typename _rT, typename... _pT>
void command_queue<_cT, _rT(_pT...)>::insert(const id &work_id, const work_t &work) {
    __list.insert(std::make_pair(work_id, work));
}

template <typename _cT, typename _rT, typename... _pT>
void command_queue<_cT, _rT(_pT...)>::insert(id &work_id, _cT* object, _pT... args) {
    __queue.push(std::make_pair(work_id, std::make_tuple(object, args...)));
}

template <typename _cT, typename _rT, typename... _pT>
void command_queue<_cT, _rT(_pT...)>::insert(const id &work_id, const _cT* object, const _pT... args) {
    __queue.push(std::make_pair(work_id, std::make_tuple(object, args...)));
}

template <typename _cT, typename _rT, typename... _pT>
void command_queue<_cT, _rT(_pT...)>::erase(id &work_id) {
    __list.erase(__list.find(work_id));
}

template <typename _cT, typename _rT, typename... _pT>
void command_queue<_cT, _rT(_pT...)>::erase(const id &work_id) {
    __list.erase(__list.find(work_id));
}

template <typename _cT, typename _rT, typename... _pT>
void command_queue<_cT, _rT(_pT...)>::execute() {
    __promise[0].set_value();
}

template <typename _cT, typename _rT, typename... _pT>
void command_queue<_cT, _rT(_pT...)>::synchronize() {
    __future[1].get();
}

template <typename _cT, typename _rT, typename... _pT>
void command_queue<_cT, _rT(_pT...)>::sleep(tick_t tick) {
    if (__sleep_tick == 0) __sleep_tick = tick;
}

template <typename _cT, typename _rT, typename... _pT>
void command_queue<_cT, _rT(_pT...)>::wake() {
    __sleep_tick = 0;
}

template <typename _cT, typename _rT, typename... _pT>
bool command_queue<_cT, _rT(_pT...)>::is_sleeping() {
    return __sleep_tick;
}

template <typename _cT, typename _rT, typename... _pT>
std::queue<_rT>& command_queue<_cT, _rT(_pT...)>::get_result() {
    return __result;
}

template <typename _cT, typename _rT, typename... _pT>
void command_queue<_cT, _rT(_pT...)>::__execute_() {
    __future[0].wait();
    __active = true;
    while (__active) {
        __future[0].get();
        __promise[0] = std::promise<void>();
        __future[0] = __promise[0].get_future();
        __promise[1] = std::promise<void>();
        __future[1] = __promise[1].get_future();
        while (!__result.empty()) __result.pop();
        
        if (__sleep_tick) {
            if (__sleep_tick != -1) __sleep_tick -= 1;
            __promise[1].set_value();
                continue;
            }
            
            while (!__queue.empty()) {
                std::pair<id, std::tuple<_cT*, _pT...>> __work = __queue.front();
                work_t __func = __list.find(__work.first)->second;
                __result.push(__func(*std::get<0>(__work.second),
                                     std::get<_pT>(__work.second)...));
                __queue.pop();
            }
        __promise[1].set_value();
    }
}

template <typename _cT, typename _rT>
command_queue<_cT, _rT()>::command_queue() {
    __active = false;
    __future[0] = __promise[0].get_future();
    __future[1] = __promise[1].get_future();
    __promise[1].set_value();
    __exec = std::thread(&command_queue::__execute_, this);
}

template <typename _cT, typename _rT>
command_queue<_cT, _rT()>::~command_queue() {
    __active = false;
    __promise[0].set_value();
    __exec.join();
}

template <typename _cT, typename _rT>
void command_queue<_cT, _rT()>::insert(id &work_id, work_t &work) {
    __list.insert(std::make_pair(work_id, work));
}

template <typename _cT, typename _rT>
void command_queue<_cT, _rT()>::insert(const id &work_id, const work_t &work) {
    __list.insert(std::make_pair(work_id, work));
}

template <typename _cT, typename _rT>
void command_queue<_cT,_rT()>::insert(id &work_id, _cT* object) {
    __queue.push(std::make_pair(work_id, object));
}

template <typename _cT, typename _rT>
void command_queue<_cT,_rT()>::insert(const id &work_id, const _cT* object) {
    __queue.push(std::make_pair(work_id, object));
}

template <typename _cT, typename _rT>
void command_queue<_cT,_rT()>::erase(id &work_id) {
    __list.erase(__list.find(work_id));
}

template <typename _cT, typename _rT>
void command_queue<_cT,_rT()>::erase(const id &work_id) {
    __list.erase(__list.find(work_id));
}

template <typename _cT, typename _rT>
void command_queue<_cT,_rT()>::execute() {
    __promise[0].set_value();
}

template <typename _cT, typename _rT>
void command_queue<_cT,_rT()>::synchronize() {
    __future[1].get();
}

template <typename _cT, typename _rT>
void command_queue<_cT, _rT()>::sleep(tick_t tick) {
    if (__sleep_tick == 0) __sleep_tick = tick;
}

template <typename _cT, typename _rT>
void command_queue<_cT, _rT()>::wake() {
    __sleep_tick = 0;
}

template <typename _cT, typename _rT>
bool command_queue<_cT, _rT()>::is_sleeping() {
    return __sleep_tick;
}

template <typename _cT, typename _rT>
std::queue<_rT>& command_queue<_cT, _rT()>::get_result() {
    return __result;
}

template <typename _cT, typename _rT>
void command_queue<_cT, _rT()>::__execute_() {
    __future[0].wait();
    __active = true;
    while (__active) {
        __future[0].get();
        __promise[0] = std::promise<void>();
        __future[0] = __promise[0].get_future();
        __promise[1] = std::promise<void>();
        __future[1] = __promise[1].get_future();
        while (!__result.empty()) __result.pop();
        
        if (__sleep_tick) {
            if (__sleep_tick != -1) __sleep_tick -= 1;
            __promise[1].set_value();
            continue;
        }
        
        while (!__queue.empty()) {
            std::pair<id, _cT*> __work = __queue.front();
            work_t __func = __list.find(__work.first)->second;
            __result.push(__func(*__work.second));
            __queue.pop();
        }
        __promise[1].set_value();
    }
}

template <typename _cT, typename... _pT>
command_queue<_cT, void(_pT...)>::command_queue() {
    __active = false;
    __future[0] = __promise[0].get_future();
    __future[1] = __promise[1].get_future();
    __promise[1].set_value();
    __exec = std::thread(&command_queue::__execute_, this);
}

template <typename _cT, typename... _pT>
command_queue<_cT, void(_pT...)>::~command_queue() {
    __active = false;
    __promise[0].set_value();
    __exec.join();
}
    
template <typename _cT, typename... _pT>
void command_queue<_cT, void(_pT...)>::insert(id &work_id, work_t &work) {
    __list.insert(std::make_pair(work_id, work));
}
    
template <typename _cT, typename... _pT>
void command_queue<_cT, void(_pT...)>::insert(const id &work_id, const work_t&work) {
        __list.insert(std::make_pair(work_id, work));
}
    
template <typename _cT, typename... _pT>
void command_queue<_cT, void(_pT...)>::insert(id &work_id, _cT* object, _pT...args) {
        __queue.push(std::make_pair(work_id, std::make_tuple(object, args...)));
}
    
template <typename _cT, typename... _pT>
void command_queue<_cT, void(_pT...)>::insert(const id &work_id, const _cT*object, const _pT... args) {
        __queue.push(std::make_pair(work_id, std::make_tuple(object, args...)));
}
    
template <typename _cT, typename... _pT>
void command_queue<_cT, void(_pT...)>::erase(id &work_id) {
    __list.erase(__list.find(work_id));
}
    
template <typename _cT, typename... _pT>
void command_queue<_cT, void(_pT...)>::erase(const id &work_id) {
    __list.erase(__list.find(work_id));
}

template <typename _cT, typename... _pT>
void command_queue<_cT, void(_pT...)>::execute() {
    __promise[0].set_value();
}

template <typename _cT, typename... _pT>
void command_queue<_cT, void(_pT...)>::synchronize() {
    __future[1].get();
}

template <typename _cT, typename... _pT>
void command_queue<_cT, void(_pT...)>::sleep(tick_t tick) {
    if (__sleep_tick == 0) __sleep_tick = tick;
}

template <typename _cT, typename... _pT>
void command_queue<_cT, void(_pT...)>::wake() {
    __sleep_tick = 0;
}

template <typename _cT, typename... _pT>
bool command_queue<_cT, void(_pT...)>::is_sleeping() {
    return __sleep_tick;
}

template <typename _cT, typename... _pT>
void command_queue<_cT, void(_pT...)>::__execute_() {
    __future[0].wait();
    __active = true;
    while (__active) {
        __future[0].get();
        __promise[0] = std::promise<void>();
        __future[0] = __promise[0].get_future();
        __promise[1] = std::promise<void>();
        __future[1] = __promise[1].get_future();
        
        if (__sleep_tick) {
            if (__sleep_tick != -1) __sleep_tick -= 1;
            __promise[1].set_value();
            continue;
        }
        
        while (!__queue.empty()) {
            std::pair<id, std::tuple<_cT*, _pT...>> __work = __queue.front();
            work_t __func = __list.find(__work.first)->second;
            __func(*std::get<0>(__work.second),
                    std::get<_pT>(__work.second)...);
            __queue.pop();
        }
        __promise[1].set_value();
    }
}

template <typename _cT>
command_queue<_cT, void()>::command_queue() {
    __active = false;
    __future[0] = __promise[0].get_future();
    __future[1] = __promise[1].get_future();
    __promise[1].set_value();
    __exec = std::thread(&command_queue::__execute_, this);
}

template <typename _cT>
command_queue<_cT, void()>::~command_queue() {
    __active = false;
    __promise[0].set_value();
    __exec.join();
}

template <typename _cT>
void command_queue<_cT, void()>::insert(id &work_id, work_t &work) {
    __list.insert(std::make_pair(work_id, work));
}

template <typename _cT>
void command_queue<_cT, void()>::insert(const id &work_id, const work_t &work) {
    __list.insert(std::make_pair(work_id, work));
}

template <typename _cT>
void command_queue<_cT, void()>::insert(id &work_id, _cT* object) {
    __queue.push(std::make_pair(work_id, object));
}

template <typename _cT>
void command_queue<_cT, void()>::insert(const id &work_id, const _cT* object) {
    __queue.push(std::make_pair(work_id, object));
}

template <typename _cT>
void command_queue<_cT, void()>::erase(id &work_id) {
    __list.erase(__list.find(work_id));
}

template <typename _cT>
void command_queue<_cT, void()>::erase(const id &work_id) {
    __list.erase(__list.find(work_id));
}

template <typename _cT>
void command_queue<_cT, void()>::execute() {
    __promise[0].set_value();
}

template <typename _cT>
void command_queue<_cT, void()>::synchronize() {
    __future[1].get();
}

template <typename _cT>
void command_queue<_cT, void()>::sleep(tick_t tick) {
    if (__sleep_tick == 0) __sleep_tick = tick;
}

template <typename _cT>
void command_queue<_cT, void()>::wake() {
    __sleep_tick = 0;
}

template <typename _cT>
bool command_queue<_cT, void()>::is_sleeping() {
    return __sleep_tick;
}

template <typename _cT>
void command_queue<_cT, void()>::__execute_() {
    __future[0].wait();
    __active = true;
    while (__active) {
        __future[0].get();
        __promise[0] = std::promise<void>();
        __future[0] = __promise[0].get_future();
        __promise[1] = std::promise<void>();
        __future[1] = __promise[1].get_future();
        
        if (__sleep_tick) {
            if (__sleep_tick != -1) __sleep_tick -= 1;
            __promise[1].set_value();
            continue;
        }
        
        while (!__queue.empty()) {
            std::pair<id, _cT*> __work = __queue.front();
            work_t __func = __list.find(__work.first)->second;
            __func(*__work.second);
            __queue.pop();
        }
        __promise[1].set_value();
    }
}
