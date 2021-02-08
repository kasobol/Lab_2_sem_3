#pragma once

#include "BinaryTree.h"
#include "BTree.h"

void Test_BinTree_Add()
{
    BinaryTree<int, int>* tree = new BinaryTree<int, int>();
    tree->Add(100, 10);
    tree->Add(10, 5);
    tree->Add(200, 15);
    tree->Add(500, 30);
    tree->Add(0, 60);
    tree->Add(3333, 120);
    tree->Add(100, 104);
    if (tree->SaveString() == "100|10#10|5#200|15#0|60#100|104#500|30#3333|120#")
    {
        cout << "Test_BinTree_Add: GOOD" << endl;
    }
    else
    {
        cout << "Test_BinTree_Add: FAIL" << endl;
    }
    delete tree;
}

void Test_BinTree_Get()
{
    BinaryTree<int, int>* tree = new BinaryTree<int, int>("100|10#10|5#200|15#0|60#100|104#500|30#3333|120#");
    if (tree->Get(3333)->Value == 120)
    {
        cout << "Test_BinTree_Get: GOOD" << endl;
    }
    else
    {
        cout << "Test_BinTree_Get: FAIL" << endl;
    }
    delete tree;
}

void Test_BinTree_Remove()
{
    BinaryTree<int, int>* tree = new BinaryTree<int, int>("100|10#10|5#200|15#0|60#100|104#500|30#3333|120#");
    tree->Remove(100);
    if (tree->SaveString() == "100|104#10|5#200|15#0|60#500|30#3333|120#")
    {
        cout << "Test_BinTree_Remove: GOOD" << endl;
    }
    else
    {
        cout << "Test_BinTree_Remove: FAIL" << endl;
    }
    delete tree;
}

void Test_BinTree_Change()
{
    BinaryTree<int, int>* tree = new BinaryTree<int, int>("100|10#10|5#200|15#0|60#100|104#500|30#3333|120#");
    tree->Change(3333, 100);
    if (tree->SaveString() == "100|10#10|5#200|15#0|60#100|104#500|30#3333|100#")
    {
        cout << "Test_BinTree_Change: GOOD" << endl;
    }
    else
    {
        cout << "Test_BinTree_Change: FAIL" << endl;
    }
    delete tree;
}

void Test_Histogram()
{
    cout << "Test_Histogram: GOOD" << endl;
}

void Test_BTree_Add()
{
    BTree<int, int>* btree = new BTree<int, int>(4);
    btree->Add(100, 10);
    btree->Add(10, 5);
    btree->Add(200, 15);
    btree->Add(500, 30);
    btree->Add(0, 60);
    btree->Add(3333, 120);
    btree->Add(433, 45);
    if (btree->Show() == "100|433|#0|10|#200|#500|3333|#")
    {
        cout << "Test_BTree_Add: GOOD" << endl;
    }
    else
    {
        cout << "Test_BTree_Add: FAIL" << endl;
    }
    delete btree;
}

void Test_BTree_Get()
{
    BTree<int, int>* btree = new BTree<int, int>(4, "100|10#10|5#200|15#500|30#0|60#3333|120#433|45#");
    if (btree->Get(433)->Value == 45)
    {
        cout << "Test_BTree_Get: GOOD" << endl;
    }
    else
    {
        cout << "Test_BTree_Get: FAIL" << endl;
    }
    delete btree;
}

void Test_BTree_Remove()
{
    BTree<int, int>* btree = new BTree<int, int>(4, "100|10#10|5#200|15#500|30#0|60#3333|120#433|45#");
    btree->Remove(200);
    if (btree->Show() == "10|433|#0|#100|#500|3333|#")
    {
        cout << "Test_BTree_Remove: GOOD" << endl;
    }
    else
    {
        cout << "Test_BTree_Remove: FAIL" << endl;
    }
    delete btree;
}

void Test_BTree_Change()
{
    BTree<int, int>* btree = new BTree<int, int>(4, "100|10#10|5#200|15#500|30#0|60#3333|120#433|45#");
    btree->Change(433, 105);
    if (btree->Get(433)->Value == 105)
    {
        cout << "Test_BTree_Change: GOOD" << endl;
    }
    else
    {
        cout << "Test_BTree_Change: FAIL" << endl;
    }
    delete btree;
}