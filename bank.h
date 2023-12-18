/* Nithisha Sathishkumar
* Novemeber 13, 2023
* Project 1
* Professor.Dimpsey
*/

#ifndef BANK_H_
#define BANK_H_

#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "account.h"
#include "bst.h"
#include "transaction.h"
using namespace std;

class Bank {
public:
  // Constructors
  Bank();

  // Destructor
  ~Bank();

  // Read transactions from a file
  bool ReadTransactions(const string& file_name);

  // Process a transaction line from the file
  void ReadProcessTransaction(char transaction_type, istringstream& parseLine);

  // Process all transactions in the queue
  bool ProcessTransactions();

  // Process a withdrawal transaction
  void ProcessWithdrawal(const Transaction& process, int account_id);

  // Process a deposit transaction
  void ProcessDeposit(const Transaction& process, int account_id);

  // Process a transfer transaction
  void ProcessTransfer(const Transaction& process, int account_id);

  // Process an account opening transaction
  void ProcessAccountOpen(const Transaction& process, int account_id);

  // Process an account history transaction
  void ProcessAccountHistory(const Transaction& process, int account_id);

  // Process a fund history transaction
  void ProcessFundHistory(const Transaction& process, int account_id);

  // Print all processed transactions 
  void PrintTransactions();

private:
  // Private data members
  BSTree accounts_;
  queue<Transaction> transactions_;
};
#endif