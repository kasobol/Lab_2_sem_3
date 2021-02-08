
#include <iostream>
#include <ctime>

#include "Person.h"

#include "Dictionary.h"

#include "Sequence.h"
#include "LinkedListSequence.h"
#include "ArraySequence.h"

#include "Tests.h"

using namespace std;

int GetPlace(int* mas,int key, int size)
{
    int start_binary_search = 0;
    int end_binary_search = size - 1;
    int tmp;
    while (end_binary_search - start_binary_search != -1)
    {
        tmp = (start_binary_search + end_binary_search) / 2;
        if (key < mas[tmp])
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

void Little_Change(int* mas, int m, int size)
{
    int place = GetPlace(mas, m, size);
    for (int i = size; i > place; i--)
    {
        mas[i] = mas[i - 1];
    }
    mas[place] = m;
}

void Show_Histogram(Dictionary<int, int>* dict, int* splitting, int size)
{
    cout << "Histogram: " << endl;
    for (int i = 0; i < size - 1; i++)
    {
        cout << "[" << splitting[i] << ", " << splitting[i + 1] << ") --- " << dict->Get1(splitting[i]) << endl;
    }
    cout << endl;
}

Dictionary<int, int>* Histogram_BinaryTree(Sequence<Person>* seq, int* splitting, int size)
{
    Dictionary<int, int>* res = new BinaryTree<int, int>();
    int* values = new int[size];
    for (int i = 0; i < size; i++)
    {
        values[i] = 0;
    }

    for (int i = 0; i < seq->GetLength(); i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (seq->Get(i).GetAge(2020) < splitting[j + 1] && seq->Get(i).GetAge(2020) >= splitting[j])
            {
                values[j] = values[j] + 1;
            }
        }
    }
    
    int* mas = new int[size] { 0, (size - 1) / 2, size - 1 };
    int size_mas = 3;
    res->Add(splitting[mas[1]], values[mas[1]]);
    while (size_mas != size)
    {
        for (int i = 1; i < size_mas; i++)
        {
            if (mas[i] - mas[i - 1] > 1)
            {
                int m = (mas[i] + mas[i - 1]) / 2;
                res->Add(splitting[m], values[m]);
                Little_Change(mas, m, size_mas);
                size_mas++;
                i++;
            }
        }
    }
    res->Add(splitting[0], values[0]);
    res->Add(splitting[size - 1], values[size - 1]);
    return res;
}

Dictionary<int, int>* Histogram_BTree(Sequence<Person>* seq, int* splitting, int size, int number_tree)
{
    Dictionary<int, int>* res = new BTree<int, int>(number_tree);
    int* values = new int[size];
    for (int i = 0; i < size; i++)
    {
        values[i] = 0;
    }

    for (int i = 0; i < seq->GetLength(); i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (seq->Get(i).GetAge(2020) < splitting[j + 1] && seq->Get(i).GetAge(2020) >= splitting[j])
            {
                values[j] = values[j] + 1;
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        res->Add(splitting[i], values[i]);
    }
    return res;
}

int main()
{
    Test_BinTree_Add();
    Test_BinTree_Get();
    Test_BinTree_Remove();
    Test_BinTree_Change();
    Test_BTree_Add();
    Test_BTree_Get();
    Test_BTree_Remove();
    Test_BTree_Change();
    Test_Histogram();

    string str;
    cout << "\nIf you want to use - press \"e\", else - press \"p\"\n";
    cin >> str;
    if (str != "e")
    {
        cout << "\nGOODbye";
        return 0;
    }

    char fun;

    do
    {
        system("color 7");
        try
        {
            cout << "\nEnter: 0 - Check BinaryTree, 1 - Check BTree, 2 - Check Histogram";
            cin >> fun;

            Dictionary<int, int>* dict;

            int size;
            cout << "Enter size: ";
            cin >> size;

            switch (fun)
            {
            case '0':
            {
                dict = new BinaryTree<int, int>();
                for (int i = 0; i < size; i++)
                {
                    dict->Add(rand() % 1000, rand() % 1000);
                }
                dict->Print();
                do
                {
                    cout << "\nEnter: 0 - Add(key, value), 1 - Get(key), 2 - Remove(key)";
                    cin >> fun;
                    switch (fun)
                    {
                    case '0':
                    {
                        int key, value;
                        cin >> key >> value;
                        dict->Add(key, value);
                        cout << "\nAdd(" << key << ", " << value << ")" << endl;
                        dict->Print();
                    }
                    break;
                    case '1':
                    {
                        int key;
                        cin >> key;
                        cout << "\nGet(" << key << ") = " << dict->Get1(key) << endl;
                    }
                    break;
                    case '2':
                    {
                        int key;
                        cin >> key;
                        dict->Remove(key);
                        cout << "\nRemove(" << key << ")" << endl;
                        dict->Print();
                    }
                    break;
                    }
                    cout << "\nIf you want to exit from this - press \"e\", else - press \"p\"";
                    cin >> str;
                } while (str != "e");
                delete dict;
            }
            break;
            case '1':
            {
                int number_tree;
                cout << "\nBTree_Level: ";
                cin >> number_tree;
                dict = new BTree<int, int>(number_tree);
                for (int i = 0; i < size; i++)
                {
                    dict->Add(rand() % 1000, rand() % 1000);
                }
                dict->Print();
                do
                {
                    cout << "\nEnter: 0 - Add(key, value), 1 - Get(key), 2 - Remove(key)";
                    cin >> fun;
                    switch (fun)
                    {
                    case '0':
                    {
                        int key, value;
                        cin >> key >> value;
                        dict->Add(key, value);
                        cout << "\nAdd(" << key << ", " << value << ")" << endl;
                        dict->Print();
                    }
                    break;
                    case '1':
                    {
                        int key;
                        cin >> key;
                        cout << "\nGet(" << key << ") = " << dict->Get1(key) << endl;
                    }
                    break;
                    case '2':
                    {
                        int key;
                        cin >> key;
                        dict->Remove(key);
                        cout << "\nRemove(" << key << ")" << endl;
                        dict->Print();
                    }
                    break;
                    }
                    cout << "\nIf you want to exit from this - press \"e\", else - press \"p\"";
                    cin >> str;
                } while (str != "e");
                delete dict;
            }
            break;
            case '2':
            {
                Sequence<Person>* seq = new ArraySequence<Person>(size);

                do
                {
                    dict = nullptr;
                    cout << "\nWhat do you want to use?: Enter: 0 - BinaryTree, 1 - BTree";
                    cin >> fun;
                    cout << "Inputed Age of Person: ";
                    for (int i = 0; i < size; i++)
                    {
                        seq->InsertAt(Person("", "", "", rand() % 2020), i);
                        cout << seq->Get(i).GetAge(2020) << " ";
                    }
                    cout << "\n\n";
                    int leng = 20;
                    int* splitting = new int[leng] { 0, 50, 70, 200, 240, 270, 500, 700, 900, 1150, 1350, 1500, 1600, 1700, 1750, 1800, 1900, 1950, 2000, 2020 };
                    cout << "Splitting: ";
                    for (int i = 0; i < leng; i++)
                    {
                        cout << splitting[i] << " ";
                    }
                    cout << "\n\n";
                    switch (fun)
                    {
                    case '0':
                    {
                        dict = Histogram_BinaryTree(seq, splitting, leng);
                    }
                    break;
                    case '1':
                    {
                        int number_tree;
                        cout << "\nBTree_Level: ";
                        cin >> number_tree;
                        dict = Histogram_BTree(seq, splitting, leng, number_tree);
                    }
                    break;
                    }
                    dict->Print();
                    Show_Histogram(dict, splitting, leng);
                    cout << "If you want to Get(key) value, press - \"e\", else - \"p\"" << endl;
                    cin >> str;
                    while (str != "p")
                    {
                        int key;
                        cin >> key;
                        cout << "\nGet(" << key << ") = " << dict->Get1(key) << endl;
                        cout << "If you want to Get(key) value, press - \"e\", else - \"p\"" << endl;
                        cin >> str;
                    }

                    cout << "\nIf you want to exit from this - press \"e\", else - press \"p\"";
                    cin >> str;
                } while (str != "e");
                delete dict;
            }
            break;
            }
        }
        catch (exception ex)
        {
            system("color 4");
            cout << "\n" << "ERROR !!!";
            cout << "\n" << ex.what() << endl;
        }

        cout << "\nIf you want to exit - press \"e\", else - press \"p\"" << endl;

        cin >> str;

    } while (str != "e");

    cout << "\nGOODbye\n" << endl;

    //srand(time(0));
    /*Sequence<Person>* seq = new ArraySequence<Person>(30);
    for (int i = 0; i < seq->GetLength(); i++)
    {
        seq->InsertAt(Person("", "", "", rand() % 2020), i);
    }
    for (int i = 0; i < seq->GetLength(); i++)
    {
        cout << seq->Get(i).GetAge(2020) << endl;
    }
    int* splitting = new int[10]{ 0, 20, 50, 70, 500, 1000, 1500, 2000, 2010, 2020 };
    auto res = Histogram_BinaryTree(seq, splitting, 10);
    res->Print();
    auto tres = Histogram_BTree(seq, splitting, 10, 4);
    tres->Print();*/
}
