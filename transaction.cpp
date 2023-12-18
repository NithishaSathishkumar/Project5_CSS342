/* Nithisha Sathishkumar
* Novemeber 13, 2023
* Project 1
* Professor.Dimpsey
*/


#include "transaction.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Constructor for default initialization
Transaction::Transaction() {

}

// Destructor for cleaning up resources
Transaction::~Transaction() {

}

// Constructor for a basic transaction without fund-related details
Transaction::Transaction(char transaction_type, int account_id, string last_name, string first_name, bool transaction_went_through) {
  this->transaction_type_ = transaction_type;
  this->account_id_ = account_id;
  this->last_name_ = last_name;
  this->first_name_ = first_name;
  this->transaction_went_through_ = transaction_went_through;
}

// Constructor for a transaction involving an amount and fund details
Transaction::Transaction(char transaction_type, int account_id, int fund_id, int amount, bool transaction_went_through) {
  this->transaction_type_ = transaction_type;
  this->account_id_ = account_id;
  this->fund_id_ = fund_id;
  this->amount_ = amount;
  this->transaction_went_through_ = transaction_went_through;
}

// Constructor for a transaction involving a transfer between accounts and funds
Transaction::Transaction(char transaction_type, int account_id, int fund_id, int transfer_acc_id, int transfer_fund_id, int amount, bool transaction_went_through) {
  this->transaction_type_ = transaction_type;
  this->account_id_ = account_id;
  this->fund_id_ = fund_id;
  this->transfer_account_id_ = transfer_acc_id;
  this->transfer_fund_id_ = transfer_fund_id;
  this->amount_ = amount;
  this->transaction_went_through_ = transaction_went_through;
}

// Constructor for an opening account transaction
Transaction::Transaction(char transaction_type, int account_id, bool transaction_went_through) {
  this->transaction_type_ = transaction_type;
  this->account_id_ = account_id;
  this->transaction_went_through_ = transaction_went_through;
}

// Constructor for a fund-specific transaction
Transaction::Transaction(char transaction_type, int account_id, int fund_id, bool transaction_went_through) {
  this->transaction_type_ = transaction_type;
  this->account_id_ = account_id;
  this->fund_id_ = fund_id;
  this->transaction_went_through_ = transaction_went_through;
}

// Getter methods 
char Transaction::transaction_type() const { 
    return this->transaction_type_; 
}

int Transaction::account_id() const { 
    return this->account_id_; 
}

int Transaction::fund_id() const { 
    return this->fund_id_; 
}

string Transaction::first_name() const { 
    return this->first_name_; 
}
string Transaction::last_name() const { 
    return this->last_name_; 
}

int Transaction::transfer_account_id() const { 
    return this->transfer_account_id_; 
}

int Transaction::transfer_fund_id() const { 
    return this->transfer_fund_id_; 
}

int Transaction::amount() const { 
    return this->amount_; 
}

// Check if the transaction was successful
bool Transaction::Error() const { 
    return this->transaction_went_through_; 
}

// Overloaded stream output operator for printing transactions
ostream &operator<<(ostream &stream, const Transaction &t) {

    // Check if the transaction was successful
    if (t.Error()) {
        switch (toupper(t.transaction_type())) {
            case 'D':
            case 'W':
                stream << ' ' << t.transaction_type() << ' ' << t.account_id() << ' ' << t.fund_id() << ' ' << t.amount();
                break;
            case 'T':
                stream << ' ' << t.transaction_type() << ' ' << t.account_id() << ' ' << t.fund_id() << ' '
                       << t.transfer_account_id() << ' ' << t.transfer_fund_id() << ' ' << t.amount();
                break;
            case 'O':
                stream << "Opened an account for " << t.account_id() << endl;
                break;
            default:
                stream << ' ' << t.transaction_type() << " is an invalid transaction type.";
                break;
        }
    // Handle error cases
    } else {
        if (toupper(t.transaction_type()) == 'O') {
            stream << "Account " << t.account_id() << " already exists" << endl;
        } else {
            stream << ' ' << t.transaction_type() << ' ' << t.account_id() << ' ';
            if (toupper(t.transaction_type()) == 'T') {
                stream << t.fund_id() << ' ' << t.transfer_account_id() << ' ' << t.transfer_fund_id() << ' ';
            } else {
                stream << t.fund_id() << ' ';
            }
            // Display the transaction amount and indicate failure
            stream << t.amount() << " (Failed)";
        }
    }
    return stream << endl;
}
