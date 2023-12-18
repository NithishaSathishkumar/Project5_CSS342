/* Nithisha Sathishkumar
* Novemeber 13, 2023
* Project 1
* Professor.Dimpsey
*/

#include "bst.h"
#include<iostream>
using namespace std;

// Constructor
BSTree::BSTree(){
    this->root_ = nullptr;
    this->size_ = 0;
}

//Copy Constructor
BSTree::BSTree(const BSTree& tree){

}

// Destructor 
BSTree::~BSTree(){
    DeleteList();
}

// Get the size of the tree (number of nodes)
int BSTree::size() const {
    return this->size_;
}

// Insert an account into the tree based on its unique account ID
bool BSTree::Insert(Account* p_account) {
    if (p_account->unique_account_id() < 0) {
        cerr << "ERROR: Invaild Account ID is has to be positive: " << p_account->unique_account_id() << endl;
        return false;
    }

    return RecursivelyInsert(p_account, root_);
}

// Recursive function to insert an account
bool BSTree::RecursivelyInsert(Account* p_account, Node*& root) {
    if (root == nullptr) {
        root = new Node{p_account, nullptr, nullptr};
        size_++;
        return true; 
    }

    int current_acct_id = root->p_acct->unique_account_id();
    int new_acct_id = p_account->unique_account_id();

    if (new_acct_id < current_acct_id) {
        return RecursivelyInsert(p_account, root->left);
        
    } else if (new_acct_id > current_acct_id) {
        return RecursivelyInsert(p_account, root->right);
    }

    cerr << "ERROR: Account ID " << new_acct_id << " already exists." << endl;
    return false; 
}

// Retrieve an account based on its account number
bool BSTree::Retrieve(int acct_num, Account*& p_account) const {
    return RecursivelyRetrieve(acct_num, p_account, root_);
}

// Recursive function to retrieve an account
bool BSTree::RecursivelyRetrieve(int acct_num, Account*& p_account, Node* root) const {
    if (root == nullptr) {
        return false; 
    }

    int root_acct_num = root->p_acct->unique_account_id();

    if (acct_num == root_acct_num) {
        p_account = root->p_acct;
        return true;
    }

    if (acct_num < root_acct_num) {
        return RecursivelyRetrieve(acct_num, p_account, root->left);
    } else {
        return RecursivelyRetrieve(acct_num, p_account, root->right);
    }
}

// Display the accounts in the tree
void BSTree::Display() const {
    if (isEmpty()) {
        cerr << "ERROR: BST Tree is empty!" << endl;
    } else {
        RecursivelyDisplay(root_);
    }
    cout << endl;
}

// Recursive function to display accounts in sorted order
void BSTree::RecursivelyDisplay(Node* root) const {
    if (root != nullptr) {
        RecursivelyDisplay(root->left);
        cout << *(root->p_acct) << endl;
        RecursivelyDisplay(root->right);
    }
}

// Delete all nodes in the tree
void BSTree::DeleteList() {
    RecursivelyDeleteList(root_);
    size_ = 0;
    root_ = nullptr;
}

// Recursive function to delete nodes in the tree
void BSTree::RecursivelyDeleteList(Node* root) {
    if (root == nullptr) {
        return;
    }

    RecursivelyDeleteList(root->left);
    RecursivelyDeleteList(root->right);

    delete root;
}

// Check if the tree is empty
bool BSTree::isEmpty() const{
    return (root_ == nullptr);
}

// Operator overloading to display the tree
ostream& operator<<(ostream& cout, const BSTree& BSTree){
    BSTree.Display();
    return cout;
}

