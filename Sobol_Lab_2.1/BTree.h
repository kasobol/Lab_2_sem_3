#pragma once

#include <exception>

#include "BPrint.h"

#include "Dictionary.h"

using namespace std;

template<class TKey, class TValue>
class BTree : public Dictionary<TKey, TValue>
{
private:
    struct SuperNode;
    struct Node;
    struct List
    {
        List(SuperNode* data, List* next)
        {
            this->data = data;
            this->next = next;
        }
        SuperNode* data;
        List* next;
    };
public:

    struct Node
    {
        Node(TKey Key, TValue Value, SuperNode* LeftSuperNode, SuperNode* RightSuperNode)
        {
            this->Key = Key;
            this->Value = Value;
            this->LeftSuperNode = LeftSuperNode;
            this->RightSuperNode = RightSuperNode;
        }
        TKey Key;
        TValue Value;
        SuperNode* LeftSuperNode;
        SuperNode* RightSuperNode;
    };

    struct SuperNode
    {
        SuperNode(int full_size)
        {
            real_size = 0;
            this->full_size = full_size;
            Nodes = new Node*[full_size];
        }
        SuperNode(SuperNode* CopySuperNode, int start, int end)
        {
            real_size = end - start + 1;
            full_size = CopySuperNode->full_size;
            Nodes = new Node*[full_size];
            for (int i = start, k = 0; i <= end; i++, k++)
            {
                Nodes[k] = CopySuperNode->Nodes[i];
            }
        }

        void For_All_OutNodes_Change_Prev()
        {
            if (Nodes[0]->LeftSuperNode != nullptr)
            {
                Nodes[0]->LeftSuperNode->PrevSuperNode = this;
                Nodes[0]->LeftSuperNode->prev_number_node = 0;
                for (int i = 0; i < real_size; i++)
                {
                    Nodes[i]->RightSuperNode->PrevSuperNode = this;
                    Nodes[i]->RightSuperNode->prev_number_node = i + 1;
                }
            }
        }

        void Displacement(int start, int end)
        {
            for (int i = end; i >= start; i--)
            {
                Nodes[i + 1] = Nodes[i];
            }
        }

        int GetPlace(TKey key)
        {
            int start_binary_search = 0;
            int end_binary_search = real_size - 1;
            int tmp;
            while (end_binary_search - start_binary_search != -1)
            {
                tmp = (start_binary_search + end_binary_search) / 2;
                if (key < Nodes[tmp]->Key)
                {
                    end_binary_search = tmp - 1;
                }
                else
                {
                    start_binary_search = tmp + 1;
                }
            }
            return start_binary_search;
        }

        void Add(Node* add_node)
        {
            int insert_place = GetPlace(add_node->Key);
            Displacement(insert_place, real_size - 1);
            Nodes[insert_place] = add_node;
            real_size++;
        }
        void Add(Node* add_node, int insert_place)
        {
            if (real_size != 0)
            {
                if (insert_place == 0)
                {
                    Nodes[0]->LeftSuperNode = add_node->RightSuperNode;
                }
                else if (insert_place == real_size)
                {
                    Nodes[real_size - 1]->RightSuperNode = add_node->LeftSuperNode;
                }
                else
                {
                    Nodes[insert_place - 1]->RightSuperNode = add_node->LeftSuperNode;
                    Nodes[insert_place]->LeftSuperNode = add_node->RightSuperNode;
                }
            }
            Displacement(insert_place, real_size - 1);
            Nodes[insert_place] = add_node;
            real_size++;
            if (add_node->LeftSuperNode != nullptr)
            {
                Nodes[insert_place]->LeftSuperNode->prev_number_node = insert_place;
                for (int i = insert_place; i < real_size; i++)
                {
                    Nodes[i]->RightSuperNode->prev_number_node = i + 1;
                }
            }
        }

        string ShowStr()
        {
            string str = "";
            for (int i = 0; i <= real_size - 1; i++)
            {
                str += to_string(Nodes[i]->Key) + "|";
            }
            str += "#";
            return str;
        }

        int full_size;
        int real_size;
        Node** Nodes;
        SuperNode* PrevSuperNode;
        int prev_number_node;

        ~SuperNode()
        {

        }
    };

    SuperNode* superhead;
    int number_tree;
    int length;

    btree* tree;

public:
    BTree(int number_tree)
    {
        this->number_tree = number_tree;
        length = 0;
        superhead = nullptr;

        tree = new btree(number_tree);
    }

    BTree(int number_tree, string str)
    {
        this->number_tree = number_tree;
        length = 0;
        superhead = nullptr;
        tree = new btree(number_tree);
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

    int GetCount() override
    {
        return length;
    }
    int GetCapacity()
    {
        return 999999999;
    }

    bool ContainsKey(TKey key) override
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

    void Print() override
    {
        tree->show();
    }

    TValue Get1(TKey key) override
    {
        auto k = Get(key);
        return k->Value;
    }

    Node* Get(TKey key)
    {
        if (superhead == nullptr)
        {
            throw exception("The Dictionary is empty");
        }
        SuperNode* super_tmp = superhead;
        Node* tmp;
        int place_tmp;
        do
        {
            place_tmp = super_tmp->GetPlace(key);
            if (place_tmp == 0)
            {
                tmp = super_tmp->Nodes[place_tmp];
            }
            else
            {
                tmp = super_tmp->Nodes[place_tmp - 1];
            }
            if (tmp->Key == key)
            {
                return tmp;
            }
            if (place_tmp <= 2 && super_tmp->real_size == place_tmp)
            {
                super_tmp = super_tmp->Nodes[place_tmp - 1]->RightSuperNode;
            }
            else if (place_tmp <= 2)
            {
                super_tmp = super_tmp->Nodes[place_tmp]->LeftSuperNode;
            }
            else if (super_tmp->Nodes[place_tmp - 1]->Key == super_tmp->Nodes[place_tmp - 2]->Key)
            {
                super_tmp = super_tmp->Nodes[place_tmp - 1]->LeftSuperNode;
            }
            else
            {
                super_tmp = super_tmp->Nodes[place_tmp - 1]->RightSuperNode;
            }
        } while (super_tmp != nullptr);
        throw exception("Key is not exist");
    }
public:

    void Add(TKey key, TValue value) override
    {
        if (check)
        {
            tree->insert(key);
        }
        Node* add_node = new Node(key, value, nullptr, nullptr);
        if (superhead == nullptr)
        {
            superhead = new SuperNode(number_tree - 1);
            superhead->Add(add_node);
            superhead->PrevSuperNode = nullptr;
            length++;
        }
        else
        {
            SuperNode* super_tmp = superhead;
            int place_tmp;
            while (super_tmp->Nodes[0]->LeftSuperNode != nullptr)
            {
                place_tmp = super_tmp->GetPlace(key);
                if (place_tmp == super_tmp->real_size)
                {
                    super_tmp = super_tmp->Nodes[place_tmp - 1]->RightSuperNode;
                }
                else
                {
                    super_tmp = super_tmp->Nodes[place_tmp]->LeftSuperNode;
                }
            }
            place_tmp = super_tmp->GetPlace(key);
            if (super_tmp->real_size != super_tmp->full_size)
            {
                super_tmp->Add(add_node);
                length++;
            }
            else
            {
                int mean;
                Node* tmp;
                Node* help_tmp = add_node;
                SuperNode* left_super;
                SuperNode* right_super;
                while (true)
                {
                    mean = super_tmp->full_size / 2;
                    if (place_tmp < mean)
                    {
                        tmp = super_tmp->Nodes[mean - 1];
                        left_super = new SuperNode(super_tmp, 0, mean - 2);
                        right_super = new SuperNode(super_tmp, mean, super_tmp->full_size - 1);
                        left_super->Add(help_tmp, place_tmp);
                    }
                    else if (place_tmp > mean)
                    {
                        tmp = super_tmp->Nodes[mean];
                        left_super = new SuperNode(super_tmp, 0, mean - 1);
                        right_super = new SuperNode(super_tmp, mean + 1, super_tmp->full_size - 1);
                        right_super->Add(help_tmp, place_tmp - mean - 1);
                    }
                    else
                    {
                        tmp = help_tmp;
                        left_super = new SuperNode(super_tmp, 0, mean - 1);
                        right_super = new SuperNode(super_tmp, mean, super_tmp->full_size - 1);
                        if (tmp->LeftSuperNode != nullptr)
                        {
                            tmp->LeftSuperNode->prev_number_node = mean;
                            tmp->RightSuperNode->prev_number_node = 0;
                            for (int i = 0; i < right_super->real_size; i++)
                            {
                                right_super->Nodes[i]->RightSuperNode->prev_number_node = i + 1;
                            }
                            left_super->Nodes[mean - 1]->RightSuperNode = tmp->LeftSuperNode;
                            right_super->Nodes[0]->LeftSuperNode = tmp->RightSuperNode;
                        }
                    }
                    help_tmp = tmp;

                    tmp->LeftSuperNode = left_super;
                    tmp->RightSuperNode = right_super;

                    left_super->For_All_OutNodes_Change_Prev();
                    right_super->For_All_OutNodes_Change_Prev();

                    if (super_tmp->PrevSuperNode == nullptr)
                    {
                        delete superhead;
                        superhead = new SuperNode(number_tree - 1);
                        superhead->Add(help_tmp);
                        superhead->PrevSuperNode = nullptr;
                        left_super->PrevSuperNode = superhead;
                        right_super->PrevSuperNode = superhead;
                        left_super->prev_number_node = 0;
                        right_super->prev_number_node = 1;
                        length++;
                        return;

                    }

                    left_super->PrevSuperNode = super_tmp->PrevSuperNode;
                    right_super->PrevSuperNode = super_tmp->PrevSuperNode;

                    place_tmp = super_tmp->prev_number_node;
                    auto help = super_tmp;
                    super_tmp = super_tmp->PrevSuperNode;
                    delete help;

                    if (super_tmp->real_size != super_tmp->full_size)
                    {
                        super_tmp->Add(help_tmp, place_tmp);
                        length++;
                        return;
                    }
                }
            }
        }
    }

    bool check = true;
    void Remove(TKey key) override
    {
        check = false;
        Node* remove_node = Get(key);
        List* head = new List(superhead, nullptr);
        List* res_head = head;
        auto end_tmp = head->data;
        int leng = 1;
        while (true)
        {
            if (head == nullptr)
            {
                break;
            }
            if (head->data->Nodes[0]->LeftSuperNode == nullptr)
            {
                head = head->next;
                continue;
            }
            Add1(head, head->data->Nodes[0]->LeftSuperNode);
            for (int i = 0; i <= head->data->real_size - 1; i++)
            {
                Add1(head, head->data->Nodes[i]->RightSuperNode);
                leng++;
            }
            head = head->next;
        }
        Node** Nodes = new Node*[length - 1];
        auto tmp = res_head;
        int i = 0;
        while (tmp != nullptr)
        {
            for (int j = 0; j < tmp->data->real_size; j++)
            {
                if (tmp->data->Nodes[j] != remove_node)
                {
                    Nodes[i] = tmp->data->Nodes[j];
                    i++;
                }
            }
            tmp = tmp->next;
        }

        superhead = nullptr;
        leng = length;
        length = 0;
        for (int i = 0; i < leng - 1; i++)
        {
            Add(Nodes[i]->Key, Nodes[i]->Value);
        }
        tmp = res_head;
        while (tmp->next != nullptr)
        {
            auto help = tmp->next;
            delete tmp;
            tmp = help;
        }
        for (int i = 0; i < leng - 1; i++)
        {
            delete Nodes[i];
        }
        check = false;

        tree->del(key);
    }

    void Change(TKey key, TValue value) override
    {
        Node* node = Get(key);
        node->Value = value;
    }

    string Show()
    {
        string str = "";
        List* head = new List(superhead, nullptr);
        List* res_head = head;
        auto end_tmp = head->data;
        while (true)
        {
            str += head->data->ShowStr();
            if (head->data == end_tmp)
            {
                /*cout << str << endl;
                str = "";*/
                end_tmp = head->data->Nodes[head->data->real_size - 1]->RightSuperNode;
                if (end_tmp == nullptr)
                {
                    break;
                }
            }
            Add1(head, head->data->Nodes[0]->LeftSuperNode);
            for (int i = 0; i <= head->data->real_size - 1; i++)
            {
                Add1(head, head->data->Nodes[i]->RightSuperNode);
            }
            head = head->next;
        }
        return str;
    }
    void Add1(List* head, SuperNode* str)
    {
        List* tmp = head;
        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        tmp->next = new List(str, nullptr);
    }
};

//template<class TKey, class TValue>
//class BTree
//{
//public:
//    struct SuperNode;
//    struct List
//    {
//        List(SuperNode* data, List* next)
//        {
//            this->data = data;
//            this->next = next;
//        }
//        SuperNode* data;
//        List* next;
//    };
//    struct Node
//    {
//        Node(TKey Key, TValue Value, SuperNode* ActualSuperNode, SuperNode* LeftSuperNode, SuperNode* RightSuperNode)
//        {
//            this->Key = Key;
//            this->Value = Value;
//            this->ActualSuperNode = ActualSuperNode;
//            this->LeftSuperNode = LeftSuperNode;
//            this->RightSuperNode = RightSuperNode;
//        }
//        TKey Key;
//        TValue Value;
//        SuperNode* ActualSuperNode;
//        SuperNode* LeftSuperNode;
//        SuperNode* RightSuperNode;
//    };
//    struct SuperNode
//    {
//        SuperNode(int full_size, SuperNode* PrevSuperNode, int prev_number_node)
//        {
//            this->full_size = full_size;
//            real_size = 0;
//            Nodes = new Node*[full_size];
//            this->PrevSuperNode = PrevSuperNode;
//            this->prev_number_node = prev_number_node;
//        }
//        SuperNode(SuperNode* copysupernode, int start, int end)
//        {
//            full_size = copysupernode->full_size;
//            real_size = end - start + 1;
//            Nodes = new Node*[full_size];
//            if (copysupernode->Nodes[0]->LeftSuperNode == nullptr)
//            {
//                for (int i = 0, k = start; i < real_size; i++, k++)
//                {
//                    Nodes[i] = copysupernode->Nodes[k];
//                }
//            }
//            else
//            {
//                for (int i = 0, k = start; i < real_size; i++, k++)
//                {
//                    Nodes[i] = copysupernode->Nodes[k];
//                    Nodes[i]->LeftSuperNode->PrevSuperNode = this;
//                    Nodes[i]->LeftSuperNode->prev_number_node = i;
//                }
//                Nodes[real_size - 1]->RightSuperNode->PrevSuperNode = this;
//                Nodes[real_size - 1]->RightSuperNode->prev_number_node = real_size;
//            }
//            PrevSuperNode = copysupernode->PrevSuperNode;
//            prev_number_node = copysupernode->prev_number_node;
//        }
//        SuperNode(SuperNode* copysupernode, int start, int end, Node* add_node, int place_insert)
//        {
//            full_size = copysupernode->full_size;
//            real_size = end - start + 2;
//            Nodes = new Node*[full_size];
//
//            int i = 0;
//            int k = start;
//
//            if (copysupernode->Nodes[0]->LeftSuperNode == nullptr)
//            {
//                for (; i < place_insert; i++, k++)
//                {
//                    Nodes[i] = copysupernode->Nodes[k];
//                }
//                Nodes[place_insert] = add_node;
//                i++;
//                for (; i < real_size; i++, k++)
//                {
//                    Nodes[i] = copysupernode->Nodes[k];
//                }
//            }
//            else
//            {
//                for (; i < place_insert; i++, k++)
//                {
//                    Nodes[i] = copysupernode->Nodes[k];
//                    Nodes[i]->LeftSuperNode->PrevSuperNode = this;
//                    Nodes[i]->LeftSuperNode->prev_number_node = i;
//                }
//                Nodes[place_insert] = add_node;
//                add_node->LeftSuperNode->PrevSuperNode = this;
//                add_node->LeftSuperNode->prev_number_node = place_insert;
//                add_node->RightSuperNode->PrevSuperNode = this;
//                add_node->RightSuperNode->prev_number_node = place_insert + 1;
//                i++;
//                for (; i < real_size; i++, k++)
//                {
//                    Nodes[i] = copysupernode->Nodes[k];
//                    Nodes[i]->LeftSuperNode->PrevSuperNode = this;
//                    Nodes[i]->LeftSuperNode->prev_number_node = i;
//                }
//                Nodes[i - 1]->RightSuperNode->PrevSuperNode = this;
//                Nodes[i - 1]->RightSuperNode->prev_number_node = i;
//                if (place_insert != 0)
//                {
//                    Nodes[place_insert - 1]->RightSuperNode = add_node->LeftSuperNode;
//                }
//                if (place_insert != real_size - 1)
//                {
//                    Nodes[place_insert + 1]->LeftSuperNode = add_node->RightSuperNode;
//                }
//            }
//            PrevSuperNode = copysupernode->PrevSuperNode;
//            prev_number_node = copysupernode->prev_number_node;
//        }
//
//        int GetPlace(TKey key)
//        {
//            int start_binary_search = 0;
//            int end_binary_search = real_size - 1;
//            int tmp;
//            while (end_binary_search - start_binary_search != -1)
//            {
//                tmp = (start_binary_search + end_binary_search) / 2;
//                if (key < Nodes[tmp]->Key)
//                {
//                    end_binary_search = tmp - 1;
//                }
//                else
//                {
//                    start_binary_search = tmp + 1;
//                }
//            }
//            return start_binary_search;
//        }
//
//        void Add_Place(Node* add_node, int place_insert)
//        {
//            if (real_size != 0)
//            {
//                if (Nodes[0]->LeftSuperNode != nullptr)
//                {
//                    for (int i = real_size; i > place_insert; i--)
//                    {
//                        Nodes[i] = Nodes[i - 1];
//                        Nodes[i]->LeftSuperNode->prev_number_node = i;
//                    }
//                    Nodes[place_insert] = add_node;
//                    add_node->LeftSuperNode->prev_number_node = place_insert;
//                    add_node->RightSuperNode->prev_number_node = place_insert + 1;
//
//                    add_node->LeftSuperNode->PrevSuperNode = this;
//                    add_node->RightSuperNode->PrevSuperNode = this;
//
//                    Nodes[real_size]->RightSuperNode->prev_number_node = real_size + 1;
//                    if (place_insert != 0)
//                    {
//                        Nodes[place_insert - 1]->RightSuperNode = add_node->LeftSuperNode;
//                    }
//                    if (place_insert != real_size)
//                    {
//                        Nodes[place_insert + 1]->LeftSuperNode = add_node->RightSuperNode;
//                    }
//                }
//                else
//                {
//                    for (int i = real_size; i > place_insert; i--)
//                    {
//                        Nodes[i] = Nodes[i - 1];
//                    }
//                    Nodes[place_insert] = add_node;
//                }
//            }
//            else
//            {
//                Nodes[place_insert] = add_node;
//            }
//            real_size++;
//        }
//
//        string ShowStr()
//        {
//            string str = "";
//            for (int i = 0; i <= real_size - 1; i++)
//            {
//                str += to_string(Nodes[i]->Key) + "|";
//            }
//            str += "#";
//            return str;
//        }
//
//        int full_size;
//        int real_size;
//        Node** Nodes;
//        SuperNode* PrevSuperNode;
//        int prev_number_node;
//    };
//
//    SuperNode* superhead;
//    int number_tree;
//    int length;
//
//    btree* tree;
//
//public:
//    BTree(int number_tree)
//    {
//        this->number_tree = number_tree;
//        length = 0;
//        superhead = nullptr;
//        tree = new btree(number_tree);
//    }
//
//    int GetCount()
//    {
//        return length;
//    }
//
//    int GetCapacity()
//    {
//        return 999999999;
//    }
//
//    void Print()
//    {
//        tree->show();
//    }
//
//    void Add(TKey key, TValue value)
//    {
//        tree->insert(key);
//
//        if (superhead == nullptr)
//        {
//            superhead = new SuperNode(number_tree - 1, nullptr, -1);
//            Node* add_node = new Node(key, value, nullptr, nullptr, nullptr);
//            superhead->Add_Place(add_node, superhead->GetPlace(key));
//        }
//        else
//        {
//            SuperNode* super_tmp = superhead;
//            int place_tmp = super_tmp->GetPlace(key);
//            while (super_tmp->Nodes[0]->LeftSuperNode != nullptr)
//            {
//                if (place_tmp != super_tmp->real_size)
//                {
//                    super_tmp = super_tmp->Nodes[place_tmp]->LeftSuperNode;
//                }
//                else
//                {
//                    super_tmp = super_tmp->Nodes[place_tmp - 1]->RightSuperNode;
//                }
//                place_tmp = super_tmp->GetPlace(key);
//            }
//            int mean;
//            Node* tmp = new Node(key, value, super_tmp, nullptr, nullptr);
//            SuperNode* left_super;
//            SuperNode* right_super;
//            SuperNode* help_super;
//            while (super_tmp->real_size == super_tmp->full_size)
//            {
//                mean = super_tmp->full_size / 2;
//                if (place_tmp < mean)
//                {
//                    left_super = new SuperNode(super_tmp, 0, mean - 2, tmp, place_tmp);
//                    right_super = new SuperNode(super_tmp, mean, super_tmp->full_size - 1);
//                    tmp = super_tmp->Nodes[mean - 1];
//                }
//                else if (place_tmp > mean)
//                {
//                    left_super = new SuperNode(super_tmp, 0, mean - 1);
//                    right_super = new SuperNode(super_tmp, mean + 1, super_tmp->full_size - 1, tmp, place_tmp - mean - 1);
//                    tmp = super_tmp->Nodes[mean];
//                }
//                else
//                {
//                    left_super = new SuperNode(super_tmp, 0, mean - 1);
//                    right_super = new SuperNode(super_tmp, mean, super_tmp->full_size - 1);
//                    left_super->Nodes[left_super->real_size - 1]->RightSuperNode = tmp->LeftSuperNode;
//                    right_super->Nodes[0]->LeftSuperNode = tmp->RightSuperNode;
//                }
//                tmp->LeftSuperNode = left_super;
//                tmp->RightSuperNode = right_super;
//
//                help_super = super_tmp;
//
//                if (super_tmp != superhead)
//                {
//                    place_tmp = super_tmp->prev_number_node;
//                    super_tmp = super_tmp->PrevSuperNode;
//                }
//                else
//                {
//                    SuperNode* new_superhead = new SuperNode(superhead->full_size, nullptr, -1);
//                    left_super->PrevSuperNode = new_superhead;
//                    right_super->PrevSuperNode = new_superhead;
//                    left_super->prev_number_node = 0;
//                    right_super->prev_number_node = 1;
//                    place_tmp = 0;
//
//                    super_tmp = new_superhead;
//                    superhead = new_superhead;
//                }
//                delete help_super;
//            }
//            super_tmp->Add_Place(tmp, place_tmp);
//        }
//        length++;
//    }
//    void Show()
//    {
//        string str = "";
//        List* head = new List(superhead, nullptr);
//        List* res_head = head;
//        auto end_tmp = head->data;
//        while (true)
//        {
//            str += head->data->ShowStr();
//            if (head->data == end_tmp)
//            {
//                cout << str << endl;
//                str = "";
//                end_tmp = head->data->Nodes[head->data->real_size - 1]->RightSuperNode;
//                if (end_tmp == nullptr)
//                {
//                    break;
//                }
//            }
//            Add1(head, head->data->Nodes[0]->LeftSuperNode);
//            for (int i = 0; i <= head->data->real_size - 1; i++)
//            {
//                Add1(head, head->data->Nodes[i]->RightSuperNode);
//            }
//            head = head->next;
//        }
//    }
//};
//void Add1(BTree<int, int>::List* head, BTree<int, int>::SuperNode* str)
//{
//    BTree<int, int>::List* tmp = head;
//    while (tmp->next != nullptr)
//    {
//        tmp = tmp->next;
//    }
//    tmp->next = new BTree<int, int>::List(str, nullptr);
//}
