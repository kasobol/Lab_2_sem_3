#pragma once

#include <exception>

using namespace std;

template<class T>
class LinkedList
{
private:
    struct List
    {
        T info;
        List* next;
    };
    List *head, *tail;
    int size;
public:
    LinkedList(T* items, int count)
    {
        head = new List();
        head->info = items[0];
        head->next = nullptr;
        tail = head;
        for (int i = 1; i < count; i++)
        {
            tail->next = new List();
            tail->next->info = items[i];
            tail->next->next = nullptr;
            tail = tail->next;
        }
        size = count;
    }
    LinkedList()
    {
        size = 0;
        head = nullptr;
        tail = head;
    }
    LinkedList(const LinkedList<T> &list)
    {
        List *tmp = list.head;
        while (tmp != nullptr)
        {
            Prepend(tmp->info);
            tmp = tmp->next;
        }
    }
public:
    T GetFirst()
    {
        if (size == 0)
        {
            throw exception("The list is empty");
        }
        return head->info;
    }
    T GetLast()
    {
        if (size == 0)
        {
            throw exception("The list is empty");
        }
        return tail->info;
    }
    T Get(int index)
    {
        if (index < 0)
        {
            throw exception("Negative index");
        }
        if (index >= size)
        {
            throw exception("Index out of range");
        }
        List *tmp = head;
        for (int i = 0; i != index; i++)
        {
            tmp = tmp->next;
        }
        return tmp->info;
    }
    LinkedList<T>* GetSubList(int startIndex, int endIndex)
    {
        if (startIndex < 0 || endIndex < 0)
        {
            throw exception("Negative index");
        }
        if (startIndex >= size || endIndex >= size)
        {
            throw exception("Index out of range");
        }
        if (startIndex > endIndex)
        {
            throw exception("startIndex > endIndex");
        }

        int resSize = endIndex - startIndex + 1;
        T *mas = new T[resSize];
        for (int i = startIndex, j = 0; i <= endIndex; i++, j++)
        {
            mas[j] = Get(i);
        }

        LinkedList<T> *res = new LinkedList(mas, resSize);
        return res;
    }
    int GetLength()
    {
        return size;
    }
public:
    void Append(T item)
    {
        size++;
        List *tmp = new List();
        tmp->info = item;
        tmp->next = head;
        head = tmp;
    }
    void Prepend(T item)
    {
        size++;
        List *tmp = new List();
        tmp->info = item;
        tmp->next = nullptr;
        if (head == nullptr)
        {
            head = tmp;
            tail = head;
        }
        tail->next = tmp;
        tail = tmp;
    }
    void InsertAt(T item, int index)
    {
        if (index < 0)
        {
            throw exception("Negative index");
        }
        if (index >= size)
        {
            throw exception("Index out of range");
        }
        List *tmp = head;
        for (int i = 0; i != index; i++)
        {
            tmp = tmp->next;
        }
        tmp->info = item;
    }
    LinkedList<T>* Concat(LinkedList<T> *list)
    {
        LinkedList<T> *res = new LinkedList();
        res->size = size + list->size;
        res->head = head;
        res->tail = tail;
        res->tail->next = list->head;
        res->tail = list->tail;

        return res;
    }

    ~LinkedList()
    {
        List *tmp = head;
        List *next = head;
        while (tmp != nullptr)
        {
            next = tmp->next;
            delete tmp;
            tmp = next;
        }
    }
};