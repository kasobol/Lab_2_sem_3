#pragma once

#include "Sequence.h"
#include "LinkedList.h"

using namespace std;

template <class T>
class LinkedListSequence : public Sequence<T>
{
private:
    LinkedList<T> *list;
public:
    LinkedListSequence<T>* Clone() override
    {
        return new LinkedListSequence<T>(*list);
    }
public:
    LinkedList<T>* Get_List()
    {
        return list;
    }
    LinkedListSequence(T* items, int count)
    {
        list = new LinkedList<T>(items, count);
    }
    LinkedListSequence()
    {
        list = new LinkedList<T>();
    }
    LinkedListSequence(const LinkedList<T> &list)
    {
        this->list = new LinkedList<T>(list);
    }
public:
    T GetFirst() override
    {
        return list->GetFirst();
    }
    T GetLast() override
    {
        return list->GetLast();
    }
    T Get(int index) override
    {
        return list->Get(index);
    }
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) override
    {
        Sequence<T> *res = new LinkedListSequence<T>(*list->GetSubList(startIndex, endIndex));
        return res;
    }
    int GetLength() override
    {
        return list->GetLength();
    }
public:
    void Append(T item) override
    {
        list->Append(item);
    }
    void Prepend(T item) override
    {
        list->Prepend(item);
    }
    void InsertAt(T item, int index) override
    {
        list->InsertAt(item, index);
    }
    Sequence<T>* Concat(Sequence<T> *list) override
    {
        Sequence<T> *res = new LinkedListSequence<T>();
        for (int i = 0; i < this->GetLength(); i++)
        {
            res->Prepend(this->Get(i));
        }
        for (int i = 0; i < list->GetLength(); i++)
        {
            res->Prepend(list->Get(i));
        }
        return res;
    }
    ~LinkedListSequence()
    {
        delete list;
    }
};
