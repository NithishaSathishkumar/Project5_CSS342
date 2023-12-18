/* Nithisha Sathishkumar
* Novemeber 13, 2023
* Project 1
* Professor.Dimpsey
*/

#ifndef FUND_H_
#define FUND_H_

#include "transaction.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

class Fund {
public:
  //Constructor
  Fund(string name);

  //Destructor
  ~Fund();

  //getter
  string name() const;
  int balance() const;
  vector<Transaction> transactions();

  //Deposit funds into the account
  bool Deposit(int amount);

  //Withdraw funds from the account
  bool Withdraw(int amount);

  //Check if there's enough balance for a specific amount
  bool VerifyBalance(int amount);

  //Log a transaction in the fund's history
  bool TransactionLog(Transaction t);

  //Display the transaction history for this fund
  void FundHistory();

  // Display the overall transaction history for this fund
  void OverallHistory();

private:
  // Private data members
  string name_;
  int balance_ = 0;
  vector<Transaction> past_transactions_;
};
#endif