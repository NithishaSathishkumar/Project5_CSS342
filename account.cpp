/* Nithisha Sathishkumar
* Novemeber 13, 2023
* Project 1
* Professor.Dimpsey
*/

#include "account.h"
#include "transaction.h"

#include <string>
#include <vector>

using namespace std;

// Default constructor
Account::Account() {

}

// Copy constructor
Account::Account(const Account &account) {

}

// Parameterized constructor for creating an account
Account::Account(unsigned int account_id, string first_name, string last_name) {
  
  // Set account details
  this->account_id_ = account_id;
  this->first_name_ = first_name;
  this->last_name_ = last_name;

  // Create an opening transaction and add it to the transaction history
  Transaction open_account('O', account_id, last_name, first_name, true);
  past_transaction_history_.push_back(open_account);

  // Initialize funds associated with the account
  for (int i = 0; i < kMaxFundId; i++) {
    fund_[i] = new Fund(list_[i]);
  }

  // Deposit an initial amount of $200 into the first fund
  fund_[0]->Deposit(200);
  Transaction deposit_transaction('D', account_id, 0, 200, true);
} 

// Destructor
Account::~Account() {

}

// Getter for first name
string Account::first_name() const { 
  return this->first_name_; 
}

// Getter for last name
string Account::last_name() const { 
  return this->last_name_; 
}

// Getter for account ID
int Account::unique_account_id() const { 
  return this->account_id_; 
}

// Getter for the list of fund names
string Account::FundNameList(int id) const { 
  return list_[id]; 
} 

// Check if fund ID is valid
bool Account::CheckId(int id) {
  int num_id = id;

  if (num_id >= kMaxFundId || num_id < 0) {
    return true;

  } else {
    return false;

  }
}

// Deposit or transfer funds into the account
bool Account::AccountDeposit(int fund_id, int amount, char transaction_type, int account_id, int transfer_account_id, int transfer_fund_id) {
  
  // Check if the provided fund ID is valid
  if (CheckId(fund_id)) {
    cerr << "ERROR: Invalid Fund ID " << fund_id << " for Account " << account_id << ". Deposit/Transfer failed." << endl;
    return false;
  }

  // Choose the appropriate action based on the transaction type
  switch (transaction_type) {

    // Process a deposit transaction  
    case 'D': 
      return ProcessDeposit(fund_id, amount);

    // Process a transfer transaction
    case 'T': 
      return ProcessTransfer(fund_id, transfer_account_id, transfer_fund_id, amount);

    // Handle invalid transaction type
    default:
      cerr << "ERROR: Invaild transaction type '" << transaction_type << "'. Deposit/Transfer failed." << endl;
      return false;
  }
} 

// Process deposit transaction for a specific fund
bool Account::ProcessDeposit(int fund_id, int amount) {

  // Check if the deposit amount is negative
  if (amount < 0) {
    cerr << "ERROR: Cannot deposit a negative amount to " << FundNameList(fund_id) << " for Account " << first_name_ << " " << last_name_ << endl;
    return false;
  }

  // Deposit the amount into the specified fund
  fund_[fund_id]->Deposit(amount);

  // Create a transaction object for the deposit
  Transaction deposit_transaction('D', account_id_, fund_id, amount, true);

  // Log the transaction in the fund's transaction history
  fund_[fund_id]->TransactionLog(deposit_transaction);

  // Log the transaction in the account's overall transaction history
  past_transaction_history_.push_back(deposit_transaction);

  // Return true to indicate a successful deposit
  return true;
} 

// Process transfer transaction between funds
bool Account::ProcessTransfer(int fund_id, int transfer_account_id, int transfer_fund_id,int amount) {
  
  // Check if the transfer fund ID is invalid
  if (CheckId(transfer_fund_id)) {
    cerr << "ERROR: Invalid transfer Fund ID " << transfer_fund_id << " for Account " << transfer_account_id << ". Transfer failed." << endl;
    return false;
  }

  // Check if the transfer amount is negative
  if (amount < 0) {
    cerr << "ERROR: Cannot transfer a negative amount from "  << FundNameList(fund_id)[fund_id] << " to " << FundNameList(transfer_fund_id)[transfer_fund_id]
    << " for Account " << account_id_ << "." << endl;
    return false;
  }

  // Deposit the specified amount into the source fund
  fund_[fund_id]->Deposit(amount);

  // Create a transaction object for the transfer
  Transaction transfer_transaction('T', transfer_account_id, transfer_fund_id, account_id_, fund_id, amount, true);

  // Log the transfer transaction in the source fund's transaction history
  fund_[fund_id]->TransactionLog(transfer_transaction);

  // Log the transfer transaction in the overall transaction history of the account
  past_transaction_history_.push_back(transfer_transaction);

  // Return true to indicate a successful transfer
  return true;
} 

// Withdraw funds from the account
bool Account::OneAccountWithdraw(int fund_id, int amount, char transaction_type, int account_id, int transfer_account_id, int transfer_fund_id) {

  // Check if the fund ID is invalid
  if (CheckId(fund_id)) {
    cerr << "ERROR: Cannot Withdraw/Transfer " << amount << " from account: " << account_id << " fund: " << fund_id << ". " << "Fund ID is invalid." << endl;
    return false;
  }

  // Process withdrawal or transfer based on the transaction type
  if (transaction_type != 'T') {
    if ((amount >= 0) && (amount <= fund_[fund_id]->balance())) {
      Transaction withdraw_transaction('W', account_id_, fund_id, amount, true);
      fund_[fund_id]->Withdraw(amount);
      fund_[fund_id]->TransactionLog(withdraw_transaction);
      past_transaction_history_.push_back(withdraw_transaction);
      return true;
    }

    // Withdraw from linked funds if necessary
    else if (IsLinkedFund(fund_id) && (amount >= 0) && (amount <= LinkedFundsTotalBalance(fund_id))) {
      return TwoAccountWithdraw(fund_id, LinkedFund(fund_id), amount);
    }

    // Handle insufficient funds or negative amount
    else {
      if(amount < 0){
        cerr << "ERROR: Cannot Withdraw negative amount of $ " << amount << " from " << first_name_ << " " << last_name_ << " " << FundNameList(fund_id) << endl;
        
      }else{
        cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << first_name_ << " " << last_name_ << " " << FundNameList(fund_id) << endl;
      }

      Transaction withdraw_transaction('W', account_id_, fund_id, amount, false);
      fund_[fund_id]->TransactionLog(withdraw_transaction);
      past_transaction_history_.push_back(withdraw_transaction);
      return false;
    }
  }

  // Transfer funds between accounts and funds
  else {
    if (CheckId(transfer_fund_id)) {
      cerr << "ERROR: Account " << transfer_account_id << " Fund ID " << transfer_fund_id << " is invalid. Transferal failed." << endl;
      return false;
    }

    // Standard transfer
    if ((amount >= 0) && (amount <= fund_[fund_id]->balance())) {
      Transaction transfer_transaction('T', account_id_, fund_id, transfer_account_id, transfer_fund_id, amount, true);
      fund_[fund_id]->Withdraw(amount);
      fund_[fund_id]->TransactionLog(transfer_transaction);
      past_transaction_history_.push_back(transfer_transaction);
      return true;
    }

    // Transfer from linked funds if necessary
    else if (IsLinkedFund(fund_id) && (amount >= 0) && (amount <= LinkedFundsTotalBalance(fund_id))) {
      return TwoAccountWithdraw(fund_id, LinkedFund(fund_id), amount);
    }

    // Handle insufficient funds or negative amount for transfer
    else {
      cerr << "ERROR: Unable to transfer " << amount << " from Account: " << account_id_ << " " << FundNameList(fund_id) << " to Account: " << transfer_account_id << " " << FundNameList(transfer_fund_id) << endl;
      Transaction transfer_transaction('T', account_id_, fund_id, transfer_account_id, transfer_fund_id, amount, false);
      fund_[fund_id]->TransactionLog(transfer_transaction);
      past_transaction_history_.push_back(transfer_transaction);
      return false;
    }
  }
}

// Check if a fund is linked with another
bool Account::IsLinkedFund(int fund_id) const {
  return (fund_id == kMoneyMarket && LinkedFund(fund_id) == kPrimeMoneyMarket) || (fund_id == kPrimeMoneyMarket && LinkedFund(fund_id) == kMoneyMarket) ||
         (fund_id == kLongTermBond && LinkedFund(fund_id) == kShortTermBond) || (fund_id == kShortTermBond && LinkedFund(fund_id) == kLongTermBond);
}

// Get the linked fund ID
int Account::LinkedFund(int fund_id) const {
  switch (fund_id) {
    case kMoneyMarket:
      return kPrimeMoneyMarket;

    case kPrimeMoneyMarket:
      return kMoneyMarket;

    case kLongTermBond:
      return kShortTermBond;

    case kShortTermBond:
      return kLongTermBond;
      
    default:
      return -1;
  }
} 

// Get the total balance of linked funds
int Account::LinkedFundsTotalBalance(int fund_id) const {
  int linked_fund = LinkedFund(fund_id);
  return fund_[fund_id]->balance() + fund_[linked_fund]->balance();
} 

// Withdraw funds from two linked accounts
bool Account::TwoAccountWithdraw(int primary, int secondary, int amount) {

  // Check if there are sufficient funds in the primary fund
  int primary_balance = fund_[primary]->balance();

  // Withdraw from the primary fund
  if (primary_balance >= amount) {
    fund_[primary]->Withdraw(amount);
    Transaction withdraw_transaction('W', account_id_, primary, amount, true);
    past_transaction_history_.push_back(withdraw_transaction);
    fund_[primary]->TransactionLog(withdraw_transaction);

  // Withdraw the entire balance from the primary fund
  } else {
    fund_[primary]->Withdraw(primary_balance);
    Transaction withdraw_transaction('W', account_id_, primary, primary_balance, true);
    past_transaction_history_.push_back(withdraw_transaction);
    fund_[primary]->TransactionLog(withdraw_transaction);

    // Calculate the remaining amount after withdrawing from the primary fund
    int remaining_amount = amount - primary_balance;

    // Withdraw the remaining amount from the secondary fund
    fund_[secondary]->Withdraw(remaining_amount);
    Transaction withdraw_transaction2('W', account_id_, secondary, remaining_amount, true);
    past_transaction_history_.push_back(withdraw_transaction2);
    fund_[secondary]->TransactionLog(withdraw_transaction2);
  }

  return true;
} 

// Display account transaction history
void Account::AccountHistory() {
cout << "\nTransaction History for Account: " << account_id_  << ", Holder " << first_name_ << " " << last_name_  <<  " by fund." << endl;

  for (int i = 0; i < kMaxFundId; i++) {
    fund_[i]->OverallHistory();
  }

}
// Display transaction history for a specific fund
void Account::AccountFundHistory(int fund_id) {

  // Check if the provided fund_id is valid
  if (CheckId(fund_id)) {
    cerr << "ERROR: Cannot Print Transactions by fund. Fund ID cannot be " << fund_id << endl;

  } else {

    // Print the header with account holder name, fund name, and balance
    cout << "\nTransaction History for " << first_name_ << " " << last_name_ << " " << fund_[fund_id]->name() << ": $" << fund_[fund_id]->balance() << endl;

    // Iterate through transactions of the specified fund and print each transaction
    for (Transaction transaction : fund_[fund_id]->transactions()) {
      cout << " " << transaction;
    }
  }
}

// Overloaded stream insertion operator to print account information
ostream &operator<<(ostream &cout, const Account &other_account) {
  cout << other_account.first_name() << " " << other_account.last_name() << " Account ID: " << other_account.unique_account_id() << endl;

  for (int i = 0; i < kMaxFundId; i++) {
    cout << "    " << other_account.fund_[i]->name() << ": " << "$" << other_account.fund_[i]->balance() << endl;
  }
  
  return cout;
}

// Overloaded assignment operator
Account &Account::operator=(const Account &account) {
  if (this == &account) {
    return *this;
  }

  return *this;
}

// Overloaded equality operator
bool Account::operator==(const Account &other_account) const { 
  if(account_id_ == other_account.unique_account_id()){
    return true;

  }else{
    return false;

  }
}

// Overloaded inequality operator
bool Account::operator!=(const Account &other_account) const {
  if(account_id_ != other_account.unique_account_id()){
    return true;

  }else{
    return false;

  }
}
