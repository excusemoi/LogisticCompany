#pragma once
#include <algorithm>
#include <memory>
#include <map>
#include <deque>
using namespace std;
template< template< typename T, class _allocator = allocator<T> >
        class Container , typename T >
class Interface {
public:
    Container<T>* decoratedContainer;
    Interface(Container<T>* container):decoratedContainer(container)
    {
    }
    ~Interface() {}
    size_t size() { return this->decoratedContainer->size(); }
    bool empty() { return (this->decoratedContainer->empty()); }
    void insert_back(const T& value) { this->decoratedContainer->insert_back(value); }
    void insert_back(T&& value) { this->decoratedContainer->insert_back(value); }
    void remove_back() { this->decoratedContainer->remove_back(); }
    void remove(const T& value) { this->decoratedContainer->remove_back(); }
    bool find(const T& value) { return (this->decoratedContainer->find(value)); }
};
template <typename T, class _allocator = allocator<T>>
class dequeInterface : public deque<T>{
private:
    deque<T>* deq;
public:
    dequeInterface(deque<T>* d) : deq(d) {}
    ~dequeInterface() {}
    size_t size() { return deq->size(); }
    using typename std::deque<T>::iterator;
    bool empty() { return deq->empty(); }
    void insert_back(const T& value) { deq->push_back(value); };
    void insert_back(T&& value) { deq->push_back(value); };
    void remove_back() { deq->pop_back(); };
    void remove(const T& value) { deq->erase(find(value)); };
    typename deque<T>::iterator find(const T& value) {
        for (typename deque<T>::iterator it = deq->begin(); it !=deq->end(); it++)
            if (*(*it) == *value)
                return it;
        return deq->end();
    }
};
template <typename T, class _allocator = allocator<T>>
class vectorInterface : public vector<T> {
public:
    vector<T>* vec;
    vectorInterface(vector<T>* d) : vec(d) {}
    ~vectorInterface() {}
    size_t size() { return vec->size(); }
    using typename std::vector<T>::iterator;
    bool empty() { return vec->empty(); }
    void insert_back(const T& value) { vec->push_back(value); };
    void insert_back(T&& value) { vec->push_back(value); };
    void remove_back() { vec->pop_back(); };
    void remove(const T& value) { vec->erase(find(value)); };
    typename vector<T>::iterator find(const T& value) {
        for (typename vector<T>::iterator it = vec->begin(); it !=
                                                             vec->end(); it++)
            if (*(*it) == *value)
                return it;
        return vec->end();
    }
};