#pragma once

using namespace std;

template<class TKey, class TValue>
class IDictionary
{
public:
    virtual int GetCount() = 0;
    virtual int GetCapacity() = 0;
public:
    virtual TValue Get(TKey key) = 0;
    virtual bool ContainsKey(TKey key) = 0;
    virtual void Add(TKey key, TValue value) = 0;
    virtual void Remove(TKey key) = 0;
};