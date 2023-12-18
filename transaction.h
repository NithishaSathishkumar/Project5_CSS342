/* Nithisha Sathishkumar
* Novemeber 13, 2023
* Project 1
* Professor.Dimpsey
*/


#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction{
friend ostream& operator<<(ostream& stream, const Transaction& t);

public:
    // Default constructor
    Transaction();

    // Destructor
    ~Transaction();

    // Constructor for account opening
    Transaction(char transaction_type, int account_id, string last_name, string first_name, bool transaction_went_through);

    // Constructor for deposit/withdrawal transactions
    Transaction(char transaction_type, int account_id, int fund_id, int amount, bool transaction_went_through);

    // Constructor for fund transfer transactions
    Transaction(char transaction_type, int account_id, int fund_id, int transfer_acc_id, int transfer_fund_id, int amount, bool transaction_went_through);

    // Constructor for printing transactions by account
    Transaction(char transaction_type, int account_id, bool transaction_went_through);

    // Constructor for printing transactions by fund for a client account
    Transaction(char transaction_type, int account_id, int fund_id, bool transaction_went_through);

    //getters
    char transaction_type() const;
    int account_id() const;
    int fund_id() const;
    string first_name() const;
    string last_name() const;
    int transfer_account_id() const;
    int transfer_fund_id() const;
    int amount() const;

    // Check if the transaction had an error
    bool Error() const;

private:
    // Private data members
    char transaction_type_;
    string last_name_;
    string first_name_;
    int account_id_;
    int fund_id_;
    int transfer_account_id_;
    int transfer_fund_id_;
    int amount_;
    bool transaction_went_through_;
};
#endif