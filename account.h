/* Nithisha Sathishkumar
* Novemeber 13, 2023
* Project 1
* Professor.Dimpsey
*/

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "fund.h"
#include "transaction.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Constants for fund IDs
const int kMaxFundId = 9;
const int kLongTermBond = 2;
const int kShortTermBond = 3;
const int kMoneyMarket = 0;
const int kPrimeMoneyMarket = 1;

// Constant List of fund names
const vector<string> list_{
    "Money Market",       "Prime Money Market", "Long-Term Bond",
    "Short-Term Bond",    "500 Index Fund",     "Capital Value Fund",
    "Growth Equity Fund", "Growth Index Fund",  "International Fund"};

class Account {
  friend ostream &operator<<(ostream &stream, const Account &a);

public:
  // Default constructor
  Account();

  //Copy constructor
  Account(const Account &account);

  //Destructor
  Account(unsigned int account_id, string first_name, string last_name);

  ~Account();

  //Getter
  string first_name() const;
  string last_name() const;
  int unique_account_id() const;

  // Method to get the name of a fund
  string FundNameList(int id) const;

  // Check if a fund ID is valid
  bool CheckId(int id);

  // Deposit funds into the specified fund of the account or perform a transfer between funds
  bool AccountDeposit(int fund_id, int amount, char transaction_type, int account_id, int transfer_account_id, int transfer_fund_id);

  //Deposit helper functions 
  bool ProcessDeposit(int fund_id, int amount); // Process a deposit into the specified fund of the account.
  bool ProcessTransfer(int fund_id, int transfer_account_id, int transfer_fund_id, int amount); //Process a fund transfer from the specified fund of the account to another account and fund

  // Withdraw funds from one account
  bool OneAccountWithdraw(int fund_id, int amount, char transaction_type, int account_id, int transfer_account_id, int transfer_fund_id);

  //Withdraw helper functions
  bool IsLinkedFund(int fund_id) const; // Check if a fund is linked
  int LinkedFund(int fund_id) const; // Get the linked fund ID
  int LinkedFundsTotalBalance(int fund_id) const; // Get the total balance of linked funds

  // Withdraw funds from two linked accounts
  bool TwoAccountWithdraw(int primary, int secondary, int amount);

  // Display transaction history for the entire account
  void AccountHistory();

  // Display transaction history for a specific fund
  void AccountFundHistory(int fund_id);
  
  // Assignment operator
  Account &operator=(const Account &account);

  // Equality operator
  bool operator==(const Account &a) const;

  // Inequality operator
  bool operator!=(const Account &a) const;

private:
  // Private data members
  string last_name_;
  string first_name_;
  int account_id_ = 0;
  Fund *fund_[kMaxFundId];
  vector<Transaction> past_transaction_history_;
};
#endif

