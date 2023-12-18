/* Nithisha Sathishkumar
* Novemeber 13, 2023
* Project 1
* Professor.Dimpsey
*/

#include "bank.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Default constructor
Bank::Bank() {

}

// Destructor
Bank::~Bank(){ 

}

// Read transactions from a file
bool Bank::ReadTransactions(const string& file) {
  ifstream file_name(file);

  // Check if the file is open
  if (!file_name.is_open()) {
    cerr << "Cannot open " << file << endl;
    return false;
  }

  string command;

  // Read each line from the file and process transactions
  while (getline(file_name, command)) {
    if (command.empty()) {
      break;  // Break if an empty line is encountered
    }

    istringstream read_line(command);

    char transaction_type;
    read_line >> transaction_type;

    try {
      ReadProcessTransaction(transaction_type, read_line);
    } catch (const exception& e) {
      cerr << "Error processing transaction: " << e.what() << std::endl;
    }
  }
  return true;
}

// Process a transaction based on its type and Extract relevant information and push a transaction object to the queue
void Bank::ReadProcessTransaction(char transaction_type, std::istringstream& read_line) {

  // Switch statement to handle different transaction types
  switch (transaction_type) {

    // Process an account open transaction
    case 'O': {
      int account_id;
      string last_name, first_name;

      read_line >> account_id >> last_name >> first_name;
      Transaction t(transaction_type, account_id, last_name, first_name, true);
      transactions_.push(t);
      break;
    }

    // Process deposit or withdrawal transaction
    case 'D':
    case 'W': {
      int account_id, fund_id, amount;

      read_line >> account_id >> fund_id >> amount;
      Transaction t(transaction_type, account_id, fund_id, amount, true);
      transactions_.push(t);
      break;
    }

    // Process transfer transaction
    case 'T': {
      int account_id, fund_id, transfer_acc_id, transfer_fund_id, amount;

      read_line >> account_id >> fund_id >> transfer_acc_id >> transfer_fund_id >> amount;
      Transaction t(transaction_type, account_id, fund_id, transfer_acc_id, transfer_fund_id,
                    amount, true);
      transactions_.push(t);
      break;
    }

    // Process account history transaction
    case 'H': {
      int account_id;
      read_line >> account_id;
      Transaction t(transaction_type, account_id, true);
      transactions_.push(t);
      break;
    }

    // Process fund history transaction
    case 'F': {
      int account_id, fund_id;
      read_line >> account_id >> fund_id;
      Transaction t(transaction_type, account_id, fund_id, true);
      transactions_.push(t);
      break;
    }

    default:
      cerr << "Invalid transaction type: " << transaction_type << std::endl;
  
  }    
}

// Process all transactions in the queue
bool Bank::ProcessTransactions() {
  while (!transactions_.empty()) {
    Transaction process = transactions_.front();
    transactions_.pop();

    int account_id = process.account_id();
    Account *account;

    switch (process.transaction_type()) {
      case 'W':
        ProcessWithdrawal(process, account_id); // Process withdrawal
        break;

      case 'D':
        ProcessDeposit(process, account_id); // Process deposit
        break;

      case 'T':
        ProcessTransfer(process, account_id); // Process transfer
        break;

      case 'O':
        ProcessAccountOpen(process, account_id); // Process account open
        break;

      case 'H':
        ProcessAccountHistory(process, account_id); // Process account history
        break;

      case 'F':
        ProcessFundHistory(process, account_id); // Process fund history
        break;

      default:
        cerr << "ERROR: Invalid transaction type: " << process.transaction_type() << endl;
    }
  }
  return true;
}

// Process withdrawal transaction and Extract relevant information and call corresponding methods
void Bank::ProcessWithdrawal(const Transaction& process, int account_id) {
  int fund_id = process.fund_id();
  int amount = process.amount();

  Account *account;

  if (accounts_.Retrieve(account_id, account)) {
    account->OneAccountWithdraw(fund_id, amount, process.transaction_type(), account_id, 0, 0);
  } else {
    cerr << "ERROR: Account " << account_id << " not found. Withdraw refused." << endl;
  }
}

// Process deposit transaction and Extract relevant information and call corresponding methods
void Bank::ProcessDeposit(const Transaction& process, int account_id) {
  int fund_id = process.fund_id();
  int amount = process.amount();

  Account *account;

  if (accounts_.Retrieve(account_id, account)) {
    account->AccountDeposit(fund_id, amount, process.transaction_type(), account_id, 0, 0);
  } else {
    cerr << "ERROR: Account " << account_id << " not found. Deposit refused." << endl;
  }
}

// Process transfer transaction and Extract relevant information and call corresponding methods
void Bank::ProcessTransfer(const Transaction& process, int account_id) {
  if (process.Error()) {
    int fund_id = process.fund_id();
    int transfer_acc_id = process.transfer_account_id();
    int transfer_fund_id = process.transfer_fund_id();
    int amount = process.amount();

    Account *transfer_from, *transfer_to;

    if ((accounts_.Retrieve(account_id, transfer_from)) && (accounts_.Retrieve(transfer_acc_id, transfer_to))) {

      if (transfer_from->OneAccountWithdraw(fund_id, amount, process.transaction_type(), account_id, transfer_acc_id, transfer_fund_id)) {
        transfer_to->AccountDeposit(transfer_fund_id, amount, process.transaction_type(), transfer_acc_id, account_id, fund_id);

      }

    } else {
      cerr << "ERROR: Account " << (accounts_.Retrieve(account_id, transfer_from) ? transfer_acc_id : account_id) << " not found. Transfer refused." << endl;

    }
  }
}

// Process account open transaction and Extract relevant information and call corresponding methods
void Bank::ProcessAccountOpen(const Transaction& process, int account_id) {
  Account *account;
  if (accounts_.Retrieve(account_id, account)) {
    cerr << "ERROR: Account " << account_id << " is already open. Transaction refused." << endl;
  } else {
    Account *ins_account = new Account(process.account_id(), process.first_name(), process.last_name());
    accounts_.Insert(ins_account);
  }
}

// Process account history transaction and Extract relevant information and call corresponding methods
void Bank::ProcessAccountHistory(const Transaction& process, int account_id) {
  Account *account;

  if (accounts_.Retrieve(account_id, account)) {
    account->AccountHistory();
  } else {
    if (process.account_id() <= 0) {
      cerr << "ERROR: Invalid Account ID: " << process.account_id() << endl;
    } else {
      cerr << "ERROR: Account " << process.account_id() << " not found. Account History cannot be printed." << endl;
    }
  }
}

// Process fund history transaction and Extract relevant information and call corresponding methods
void Bank::ProcessFundHistory(const Transaction& process, int account_id) {
  int fund_id = process.fund_id();
  Account *account;

  if (accounts_.Retrieve(account_id, account)) {
    account->AccountFundHistory(fund_id);
  } else {
    cerr << "ERROR: Invalid Account ID " << process.account_id() << ". History by fund cannot be printed." << endl;
  }
}

// Print account balances
void Bank::PrintTransactions() {
  cout << endl << "Account Balances:" << endl;
  accounts_.Display();
}
