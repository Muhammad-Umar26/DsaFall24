#include <iostream>
#include <vector>

using namespace std;

class BankingSystem {
    vector<int> arr;
    int tableSize;

    int hash_function(int num) {
        return num % tableSize;
    }

    int hash_function2(int num) {
        return 7 - (num % 7); 
    }
    
public:
    BankingSystem() : tableSize(11), arr(11, -1) {}

    void insert(int bookId) {
        int hash1 = hash_function(bookId);
        int hash2 = hash_function2(bookId);

        for(int i=0;i < tableSize ;  i++) {
            int index = (hash1 + i * hash2) % tableSize;
            if (arr[index] == -1) {
                arr[index] = bookId;
                cout << "Inserted " << bookId << " at index " << index << endl;
                return;
            }
        }

        cout << "Hash table is full. Cannot insert " << bookId << endl;
    }

    void search(int searchKey) {
        int hash1 = hash_function(searchKey);
        int hash2 = hash_function2(searchKey);
        for(int i=0;i < tableSize ;  i++) {
            int index = (hash1 + i * hash2) % tableSize;
            if (arr[index] == searchKey) {
                cout << "ID " << searchKey << " found at index " << index << endl;
                return;
            }
        }

        cout << "ID " << searchKey << " not found" << endl;
    }

    void deleteVal(int deleteKey) {
        int hash1 = hash_function(deleteKey);
        int hash2 = hash_function2(deleteKey);

        for(int i=0;i < tableSize ;  i++) {
            int index = (hash1 + i * hash2) % tableSize;
            if (arr[index] == deleteKey) {
                arr[index] = -1;
                cout << "ID " << deleteKey << " deleted successfully" << endl;
                return;
            }
        }

        cout << "ID " << deleteKey << " not found" << endl;
    }

    void print() {
        for (int i = 0; i < tableSize; i++) {
            if (arr[i] == -1)
                cout << "EMPTY ";
            else
                cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    BankingSystem bs;

    bs.insert(101);
    bs.insert(111);
    bs.insert(121);
    bs.insert(131);
    bs.insert(141);
    bs.insert(151);
    bs.print();

    bs.search(111);
    bs.search(141);
    bs.search(161);

    bs.deleteVal(111);
    bs.print();
    bs.deleteVal(131);
    bs.print();

    cout << "Inserting 161" << endl;
    bs.insert(161);
    bs.print();
    cout << "Inserting 171" << endl;
    bs.insert(171);
    bs.print();

    return 0;
}
