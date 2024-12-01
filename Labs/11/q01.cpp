#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Library {
    int size;
    vector<vector<int>> table;

    int getIndex(int key) {
        return key / 100;
    }

    public:
        Library(int size = 10) : size(size) {
            table.resize(size);
        }

        void insertBook(int key) {
            int index = getIndex(key);
            table[index].push_back(key);
        }

        bool searchBook(int key) {
            int index = getIndex(key);
            return find(table[index].begin(), table[index].end(), key) != table[index].end();
        }

        void deleteBook(int key) {
            int index = getIndex(key);

            auto it = find(table[index].begin(), table[index].end(), key);
            if(it != table[index].end()) {
                table[index].erase(it);
            }
        }

        void displayTable() {
            for(int i = 0; i < table.size(); ++i) {
                cout << i << ": ";
                for(int j = 0; j < table[i].size(); ++j) {
                    cout << table[i][j] << ", ";
                }
                cout << endl;
            }
        }
};

int main() {
    Library library;

    cout << "Inserting books..." << endl;

    library.insertBook(101);
    library.insertBook(102);
    library.insertBook(103);

    library.insertBook(201);
    library.insertBook(202);

    library.insertBook(301);
    library.insertBook(302);
    library.insertBook(303);
    library.insertBook(304);

    cout << "Hash Table after inserting books:" << endl;
    library.displayTable();
    cout << endl;

    cout << "Searching for books..." << endl;
    cout << "Search for book 101: " << (library.searchBook(101) ? "Found" : "Not Found") << endl;
    cout << "Search for book 202: " << (library.searchBook(202) ? "Found" : "Not Found") << endl;
    cout << "Search for book 404: " << (library.searchBook(404) ? "Found" : "Not Found") << endl;
    cout << endl;

    cout << "Deleting books 101 and 202..." << endl;
    library.deleteBook(101);
    library.deleteBook(202);

    cout << "Hash Table after deleting books:" << endl;
    library.displayTable();

    return 0;
}
