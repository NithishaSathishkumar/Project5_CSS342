/* Nithisha Sathishkumar
* Novemeber 13, 2023
* Project 1
* Professor.Dimpsey
*/

#include "fund.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

// Constructor
Fund::Fund(string name) {
  this->name_ = name;
}

// Destructor
Fund::~Fund() {
  
}

// Getter for fund name
string Fund::name() const { 
  return this->name_; 
}

// Getter for fund balance
int Fund::balance() const { 
  return this->balance_; 
}

// Getter for past transactions
vector<Transaction> Fund::transactions() { 
  return this->past_transactions_; 
}

// Deposit funds into the fund
bool Fund::Deposit(int amount) {
  if(amount < 0){
    return false;
  }

  balance_ += amount;
  return true;
}

// Withdraw funds from the fund
bool Fund::Withdraw(int amount) {
  if (amount < 0 || amount > balance_) {
    return false;
  }
  balance_ -= amount;
  return true;
}

// Verify if the fund has enough balance for a given amount
bool Fund::VerifyBalance(int amount) {
  return balance_ >= amount;
}

// Log a transaction in the fund
bool Fund::TransactionLog(Transaction t) {
  past_transactions_.push_back(t);
  return true;
}

// Display the transaction history for the fund
void Fund::FundHistory() {
  for (const Transaction &transaction : past_transactions_) {
    cout << " " << transaction;
  }
}

// Display the overall history for the fund, including balance
void Fund::OverallHistory() {
  if (!past_transactions_.empty()) {
    cout << name() << ": $" << balance() << endl;
    for (const Transaction &transaction : past_transactions_) {
      cout << " " << transaction;
    }
  }
}