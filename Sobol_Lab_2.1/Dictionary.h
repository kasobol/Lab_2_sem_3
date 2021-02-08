#pragma once

#include "IDictionary.h"

using namespace std;

template<class TKey, class TValue>
class Dictionary// : public IDictionary<TKey, TValue>
{
public:
    virtual int GetCount() = 0;
    virtual int GetCapacity() = 0;
    virtual TValue Get1(TKey key) = 0;
    virtual bool ContainsKey(TKey key) = 0;
    virtual void Add(TKey key, TValue value) = 0;
    virtual void Remove(TKey key) = 0;
    virtual void Change(TKey key, TValue value) = 0;
    virtual void Print() = 0;
//public:
//    BinaryTree<TKey, TValue>* container1;
//    BTree<TKey, TValue>* container2;
//public:
//    Dictionary(BinaryTree<TKey, TValue>* tree)
//    {
//        container1 = tree;
//        container2 = nullptr;
//    }
//    Dictionary(BTree<TKey, TValue>* tree)
//    {
//        container1 = nullptr;
//        container2 = tree;
//    }
//
//    int GetCount() override
//    {
//        if (container1 != nullptr)
//        {
//            return container1->GetCount();
//        }
//        else
//        {
//            return container2->GetCount();
//        }
//    }
//
//    int GetCapacity() override
//    {
//        if (container1 != nullptr)
//        {
//            return container1->GetCapacity();
//        }
//        else
//        {
//            return container2->GetCapacity();
//        }
//    }
//
//    TValue Get(TKey key) override
//    {
//        if (container1 != nullptr)
//        {
//            return container1->Get(key)->Value;
//        }
//        else
//        {
//            return container2->Get(key)->Value;
//        }
//    }
//
//    bool ContainsKey(TKey key) override
//    {
//        if (container1 != nullptr)
//        {
//            return container1->ContainsKey(key);
//        }
//        else
//        {
//            return container2->ContainsKey(key);
//        }
//    }
//
//    void Add(TKey key, TValue value) override
//    {
//        if (container1 != nullptr)
//        {
//            container1->Add(key, value);
//        }
//        else
//        {
//            container2->Add(key, value);
//        }
//    }
//
//    void Remove(TKey key) override
//    {
//        if (container1 != nullptr)
//        {
//            container1->Remove(key);
//        }
//        else
//        {
//            container2->Remove(key);
//        }
//    }
//
//    void Change(TKey key, TValue value)
//    {
//        if (container1 != nullptr)
//        {
//            container1->Change(key, value);
//        }
//        else
//        {
//            container2->Change(key, value);
//        }
//    }
//
//    void Print()
//    {
//        if (container1 != nullptr)
//        {
//            container1->Print();
//        }
//        else
//        {
//            container2->Print();
//        }
//    }
};