#include <iostream>
#include <vector>

using namespace std;

class BankingSystem {
    int size;
    vector<int> table;

    int primaryHash(int id) {
        return id % size;
    }

    int secondaryHash(int id) {
        return 7 - (id % 7);
    }

    public:
        BankingSystem(int size = 10) : size(size) {
            table.resize(size, -1);
        }

        void insertAccountNo(int id) {
            int idx = primaryHash(id);
            int index = idx;

            int i = 1;
            while(table[index] != -1) {
                index = (idx + i * secondaryHash(id)) % size;
                ++i;
            }
            table[index] = id;
        }

        bool searchAccountNo(int id) {
            int idx = primaryHash(id);
            int index = idx;
            int originalIndex = index;

            int i = 1;
            while(table[index] != id) {
                index = (idx + i * secondaryHash(id)) % size;
                ++i;
                if(index == originalIndex) return false;
            }
            return true;
        }

        void deleteAccountNo(int id) {
            int idx = primaryHash(id);
            int index = idx;
            int originalIndex = index;

            int i = 1;
            while(table[index] != id) {
                index = (idx + i * secondaryHash(id)) % size;
                ++i;
                if(index == originalIndex) return;
            }
            table[index] = -1;
        }

        void displayTable() {
            for(int i = 0; i < size; ++i) {
                cout << i << ": ";
                if(table[i] != -1) {
                    cout << table[i];
                }
                cout << endl;
            }
        }
};

int main() {
    BankingSystem bankingSystem(11);

    cout << "Inserting account numbers: 101, 111, 121, 131, 141, 151" << endl;
    bankingSystem.insertAccountNo(101);
    bankingSystem.insertAccountNo(111);
    bankingSystem.insertAccountNo(121);
    bankingSystem.insertAccountNo(131);
    bankingSystem.insertAccountNo(141);
    bankingSystem.insertAccountNo(151);

    cout << "Hash Table after inserting account numbers:" << endl;
    bankingSystem.displayTable();

    cout << endl << "Searching for account numbers:" << endl;
    cout << "111: " << (bankingSystem.searchAccountNo(111) ? "Found" : "Not Found") << endl;
    cout << "141: " << (bankingSystem.searchAccountNo(141) ? "Found" : "Not Found") << endl;
    cout << "161: " << (bankingSystem.searchAccountNo(161) ? "Found" : "Not Found") << endl;

    cout << endl << "Deleting account numbers 111, 131:" << endl;
    bankingSystem.deleteAccountNo(111);
    bankingSystem.deleteAccountNo(131);

    cout << "Hash Table after deleting 111, 131:" << endl;
    bankingSystem.displayTable();

    cout << endl << "Inserting account numbers 161, 171 to demonstrate how secondary formula resolves collisions:" << endl;
    bankingSystem.insertAccountNo(161);
    bankingSystem.insertAccountNo(171);

    cout << "Hash Table after inserting 161, 171:" << endl;
    bankingSystem.displayTable();

    return 0;
}
