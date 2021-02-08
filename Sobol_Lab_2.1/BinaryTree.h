#pragma once

#include <exception>

#include "BinPrint.h"

#include "Dictionary.h"

using namespace std;

bool operator < (Person p1, Person p2)
{
    bool k = p1.GetAge(2020) < p2.GetAge(2020);
    return k;
}
bool operator > (Person p1, Person p2)
{
    bool k = p1.GetAge(2020) > p2.GetAge(2020);
    return k;
}

template<class TKey, class TValue>
class BinaryTree : public Dictionary<TKey, TValue>
{
private:
    template<typename Node>
    struct List
    {
        List(Node* Data, List* Next)
        {
            this->Data = Data;
            this->Next = Next;
        }
        Node* Data;
        List* Next;
        ~List()
        {
            delete Next;
        }
    };
    struct Node
    {
        Node(TKey Key, TValue Value, Node* LeftNode, Node* RightNode, Node* PrevNode)
        {
            this->Key = Key;
            this->Value = Value;
            this->LeftNode = LeftNode;
            this->RightNode = RightNode;
            this->PrevNode = PrevNode;
        }
        TKey Key;
        TValue Value;
        Node* LeftNode;
        Node* RightNode;
        Node* PrevNode;
    };

    Node* head;
    int length;
    int(*fcompare)(TKey, TKey);
    bool(*Fcompare_all)(TKey, TKey);

public:
    BinaryTree()
    {
        length = 0;
        head = nullptr;
    }

    BinaryTree(string str)
    {
        length = 0;
        head = nullptr;
        TKey add_key;
        for (int i = 0, j = 0; i < (int)str.length(); i++)
        {
            if (str[i] == '|')
            {
                TKey add_key_1;
                string key = str.substr(j, i - j);
                stringstream ss(key);
                ss >> add_key_1;
                add_key = add_key_1;
                j = i + 1;
            }
            else if (str[i] == '#')
            {
                TValue add_value;
                string value = str.substr(j, i - j);
                stringstream ss(value);
                ss >> add_value;
                j = i + 1;
                Add(add_key, add_value);
            }
        }
    }

    void Print()  override
    {
        if (head == nullptr)
        {
            return;
        }

        cout << head->Key << endl;
        printSubtree(head, "");
        cout << endl;
    }

    //void Print()
    //{
    //    BinTree<TKey, TValue> *tree_print = new BinTree<TKey, TValue>(SaveString());
    //    tree_print->Dump();
    //    delete tree_print;
    //}

    int GetCount() override
    {
        return length;
    }

    int GetCapacity() override
    {
        return 999999999;
    }

    bool ContainsKey(TKey key)  override
    {
        try
        {
            Get(key);
        }
        catch (exception) 
        {
            return false;
        }
        return true;
    }

    void Add(TKey key, TValue value)  override
    {
        if (head == nullptr)
        {
            head = new Node(key, value, nullptr, nullptr, nullptr);
        }
        else
        {
            Node* tmp = head;
            while (true)
            {
                if (key < tmp->Key)
                {
                    if (tmp->LeftNode == nullptr)
                    {
                        tmp->LeftNode = new Node(key, value, nullptr, nullptr, tmp);
                        break;
                    }
                    tmp = tmp->LeftNode;
                }
                else
                {
                    if (tmp->RightNode == nullptr)
                    {
                        tmp->RightNode = new Node(key, value, nullptr, nullptr, tmp);
                        break;
                    }
                    tmp = tmp->RightNode;
                }
            }
        }
        length++;
    }

    TValue Get1(TKey key) override
    {
        auto k = Get(key);
        return k->Value;
    }

    Node* Get(TKey key)
    {
        if (head == nullptr)
        {
            throw exception("The BinaryTree is empty");
        }
        else
        {
            Node* tmp = head;
            while (tmp->Key != key)
            {
                if (key < tmp->Key)
                {
                    tmp = tmp->LeftNode;
                }
                else
                {
                    tmp = tmp->RightNode;
                }

                if (tmp == nullptr)
                {
                    throw exception("Key is not exist");
                }
            }
            return tmp;
        }
    }

    void Remove(TKey key)  override
    {
        Node* remove_node = Get(key);
        Node* tmp;
        if (remove_node->LeftNode == nullptr && remove_node->RightNode == nullptr)
        {
            if (remove_node != head)
            {
                if (remove_node == remove_node->PrevNode->LeftNode)
                {
                    remove_node->PrevNode->LeftNode = nullptr;

                }
                else
                {
                    remove_node->PrevNode->RightNode = nullptr;
                }
            }
            tmp = nullptr;
        }
        else if (remove_node->LeftNode != nullptr && remove_node->RightNode == nullptr)
        {
            if (remove_node != head)
            {
                if (remove_node == remove_node->PrevNode->LeftNode)
                {
                    remove_node->PrevNode->LeftNode = remove_node->LeftNode;
                }
                else
                {
                    remove_node->PrevNode->RightNode = remove_node->LeftNode;
                }
            }
            remove_node->LeftNode->PrevNode = remove_node->PrevNode;
            tmp = remove_node->LeftNode;
        }
        else if (remove_node->LeftNode == nullptr && remove_node->RightNode != nullptr)
        {
            if (remove_node != head)
            {
                if (remove_node == remove_node->PrevNode->LeftNode)
                {
                    remove_node->PrevNode->LeftNode = remove_node->RightNode;
                }
                else
                {
                    remove_node->PrevNode->RightNode = remove_node->RightNode;
                }
            }
            remove_node->RightNode->PrevNode = remove_node->PrevNode;
            tmp = remove_node->RightNode;
        }
        else
        {
            tmp = remove_node->RightNode;
            while (tmp->LeftNode != nullptr)
            {
                tmp = tmp->LeftNode;
            }

            if (remove_node != head)
            {
                if (remove_node == remove_node->PrevNode->LeftNode)
                {
                    remove_node->PrevNode->LeftNode = tmp;
                }
                else
                {
                    remove_node->PrevNode->RightNode = tmp;
                }
            }

            if (tmp != remove_node->RightNode)
            {
                tmp->PrevNode->LeftNode = tmp->RightNode;
                if (tmp->RightNode != nullptr)
                {
                    tmp->RightNode->PrevNode = tmp->PrevNode;
                }
                tmp->RightNode = remove_node->RightNode;
                remove_node->RightNode->PrevNode = tmp;
            }
            tmp->PrevNode = remove_node->PrevNode;

            tmp->LeftNode = remove_node->LeftNode;
            remove_node->LeftNode->PrevNode = tmp;
        }
        if (remove_node == head)
        {
            head = tmp;
        }
        delete remove_node;
        length--;
    }

    void Change(TKey key, TValue value) override
    {
        Node* node = Get(key);
        node->Value = value;
    }

    void printSubtree(Node* head, const string& prefix)
    {
        if (head == nullptr)
        {
            return;
        }

        bool hasLeft = (head->LeftNode != nullptr);
        bool hasRight = (head->RightNode != nullptr);

        if (!hasLeft && !hasRight)
        {
            return;
        }

        string k = "    ";
        k[0] = (char)(192);
        k[1] = (char)(196);
        k[2] = (char)(196);
        k[3] = (char)(196);
        string m = " ";
        m[0] = (char)(195);
        m += k.substr(1, 3);

        cout << prefix;
        cout << ((hasLeft  && hasRight) ? m : "");
        cout << ((!hasLeft && hasRight) ? k : "");

        if (hasRight)
        {
            bool printStrand = (hasLeft && hasRight && (head->RightNode->RightNode != nullptr || head->RightNode->LeftNode != nullptr));
            string newPrefix = prefix + (printStrand ? "|   " : "    ");
            cout << head->RightNode->Key << endl;
            printSubtree(head->RightNode, newPrefix);
        }

        if (hasLeft)
        {
            cout << (hasRight ? prefix : "") << k << head->LeftNode->Key << endl;
            printSubtree(head->LeftNode, prefix + "    ");
        }
    }

    string SaveString()
    {
        List<Node> *head;
        Node* pointer = this->head;
        head = new List<Node>(pointer, nullptr);
        List<Node>* tmp = head;
        List<Node>* tmp_2 = head;
        while (true)
        {
            if (pointer->LeftNode != nullptr)
            {
                tmp->Next = new List<Node>(pointer->LeftNode, nullptr);
                tmp = tmp->Next;
            }
            if (pointer->RightNode != nullptr)
            {
                tmp->Next = new List<Node>(pointer->RightNode, nullptr);
                tmp = tmp->Next;
            }
            tmp_2 = tmp_2->Next;
            if (tmp_2 == nullptr)
            {
                break;
            }
            pointer = tmp_2->Data;
        }
        tmp = head;
        string str = "";
        while (tmp != nullptr)
        {
            str = str + to_string(tmp->Data->Key) + "|" + to_string(tmp->Data->Value) + "#";
            tmp = tmp->Next;
        }
        delete head;
        return str;
    }
};