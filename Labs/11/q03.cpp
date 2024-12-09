#include <iostream>
#include <vector>

using namespace std;

class University {
    int size, capacity;
    float loadFactor;
    vector<int> table;

    int getIndex(int key) {
        return key % capacity;
    }

    float getLoadFactor() {
        return (float)size / capacity;
    }

    void rehash() {
        int oldCap = capacity;
        capacity *= 2;
        vector<int> newTable(capacity, -1);
        
        for(int& num : table) {
            if(num != -1) {
                int idx = getIndex(num);
                int index = idx;

                int i = 1;
                while(newTable[index] != -1) {
                    index = (idx + i * i) % capacity;
                    ++i;
                }
                newTable[index] = num;
            }
        }
        table = newTable;
    }

    public:
        University(int capacity = 10, float loadFactor = 0.75) : size(0), capacity(capacity), loadFactor(loadFactor) {
            table.resize(capacity, -1);
        }

        void insertStudent(int key) {
            int idx = getIndex(key);
            int index = idx;

            int i = 1;
            while(table[index] != -1) {
                index = (idx + i * i) % capacity;
                ++i;
            }
            table[index] = key;
            ++size;

            if (getLoadFactor() >= loadFactor) {
                rehash();
            }
        }

        bool searchStudent(int key) {
            int idx = getIndex(key);
            int index = idx;
            int originalIndex = index;

            int i = 1;
            while(table[index] != key) {
                index = (idx + i * i) % capacity;
                ++i;
                if(index == originalIndex) return false;
            }
            return true;
        }

        void removeStudent(int key) {
            int idx = getIndex(key);
            int index = idx;
            int originalIndex = index;

            int i = 1;
            while(table[index] != key) {
                index = (idx + i * i) % capacity;
                ++i;
                if(index == originalIndex) return;
            }
            table[index] = -1;
        }

        void displayStudentIds() {
            for(int i = 0; i < capacity; ++i) {
                cout << i << ": ";
                if(table[i] != -1) {
                    cout << table[i];
                }
                cout << endl;
            }
        }
};

int main() {
    University university(7);

    cout << "Inserting student IDs: 12, 22, 32, 42, 52, 62" << endl;
    university.insertStudent(12);
    university.insertStudent(22);
    university.insertStudent(32);
    university.insertStudent(42);
    university.insertStudent(52);
    university.insertStudent(62);

    cout << "Hash Table after inserting student IDs:" << endl;
    university.displayStudentIds();

    cout << endl << "Searching for student IDs:" << endl;
    cout << "22: " << (university.searchStudent(22) ? "Found" : "Not Found") << endl;
    cout << "42: " << (university.searchStudent(42) ? "Found" : "Not Found") << endl;
    cout << "72: " << (university.searchStudent(72) ? "Found" : "Not Found") << endl;

    cout << endl << "Inserting student IDs 72, 82 to exceed load factor:" << endl;
    university.insertStudent(72);
    university.insertStudent(82);

    cout << "Hash Table after inserting 72, 82:" << endl;
    university.displayStudentIds();

    return 0;
}
