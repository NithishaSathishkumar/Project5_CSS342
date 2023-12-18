/* Nithisha Sathishkumar
* Novemeber 13, 2023
* Project 1
* Professor.Dimpsey
*/

#ifndef BSTree_h
#define BSTree_h
#include "account.h"
#include <stdio.h>
#include <iostream>
using namespace std;

class BSTree {
friend ostream& operator<<(ostream &out, const BSTree& tree);

public:
    // Constructor
    BSTree();

    // Copy Constructor
    BSTree(const BSTree& tree);

    // Destructor
    ~BSTree();

    // Public member functions
    bool Insert(Account* p_account);
    void DeleteList();
    bool Retrieve(int acct_ID, Account*& p_account) const;
    void Display() const;
    bool isEmpty() const;
    int size() const;

private:
    // Node structure for the binary search tree
    struct Node{
        Account* p_acct;
        Node* right;
        Node* left;
    };

    // Root of the binary search tree
    Node* root_ = nullptr;

    // Number of elements in the binary search tree
    int size_;

    // Private helper functions    
    bool RecursivelyRetrieve(int acct_ID, Account*& p_account, Node* root) const;
    bool RecursivelyInsert(Account* p_account, Node* &root);
    void RecursivelyDisplay(Node* root) const;
    void RecursivelyDeleteList(Node* root);
};
#endif