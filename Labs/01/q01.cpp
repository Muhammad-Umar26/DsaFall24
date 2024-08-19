#include <iostream>

using namespace std;

class BankAccount {
    double* balance;

    public:
        BankAccount() : balance(new double(0)) {}

        BankAccount(double balance) : balance(new double(balance)) {}

        BankAccount(const BankAccount& obj) : balance(new double(*obj.balance)) {}

        void deductBalance(int amount) {
            *balance -= amount;
        }

        int getBalanace() {
            return *balance;
        }

        ~BankAccount() {
            delete balance;
        }
};

int main () {
    BankAccount account1;

    cout << "Balance in account 1 : $" << account1.getBalanace() << endl;

    BankAccount account2(1000);

    cout << "Balance in account 2 : $" << account2.getBalanace() << endl;

    BankAccount account3(account2);
    account3.deductBalance(200);

    cout << "Balance in account 3 : $" << account3.getBalanace() << endl;
    cout << "Balance in account 2 : $" << account2.getBalanace() << endl;

    return 0;
}
