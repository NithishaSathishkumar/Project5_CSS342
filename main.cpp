/* Nithisha Sathishkumar
* Novemeber 13, 2023
* Project 1
* Professor.Dimpsey
*/

#include "bank.h"
#include <iostream>

int main(int argc, char *argv[]) {
  if(argc != 2){
    cout << "Only 1 argument.";
    return -1;
  }

  Bank jolly_banker;
  jolly_banker.ReadTransactions(argv[1]);
  jolly_banker.ProcessTransactions();
  jolly_banker.PrintTransactions();
  return 0;
}

// int main() {
//   Bank jolly_banker;
//   jolly_banker.ReadTransactions("bank_trans_in.txt");
//   jolly_banker.ProcessTransactions();
//   jolly_banker.PrintTransactions();
// }

