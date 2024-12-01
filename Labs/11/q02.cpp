#include <iostream>
#include <vector>

using namespace std;

class FitnessClub {
    int size, capacity;
    vector<int> table;

    int getIndex(int key) {
        return key % capacity;
    }

    float getLoadFactor() {
        return (float)size / capacity;
    }

public:
    FitnessClub(int capacity = 10) : size(0), capacity(capacity) {
        table.resize(capacity, -1);
    }

    void insertMember(int key) {
        if(size == capacity) {
            cout << "Sorry! Can't insert " << key << " as hash map is full." << endl;
            return;
        }
        
        int index = getIndex(key);

        while(table[index] != -1) {
            index = (index + 1) % capacity;
        }
        table[index] = key;
        ++size;
    }

    bool searchMember(int key) {
        int index = getIndex(key);
        int originalIndex = index;

        while(table[index] != -1) {
            if(table[index] == key) return true;
            index = (index + 1) % capacity;
            if(index == originalIndex) return false;
        }
        return false;
    }

    void removeMember(int key) {
        int index = getIndex(key);
        int originalIndex = index;

        while(table[index] != -1) {
            if(table[index] == key) {
                table[index] = -1;
                --size;
                return;
            }
            index = (index + 1) % capacity;
            if(index == originalIndex) return;
        }
    }

    void displayMemberIds() {
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
    FitnessClub club(7);

    cout << "Inserting member IDs 10 to 60:\n";
    for(int i = 10; i <= 60; i += 10) {
        club.insertMember(i);
    }
    club.displayMemberIds();
    cout << endl;

    cout << "Searching for member IDs 30, 50, 70:\n";
    cout << "Search for 30: " << (club.searchMember(30) ? "Found" : "Not Found") << endl;
    cout << "Search for 50: " << (club.searchMember(50) ? "Found" : "Not Found") << endl;
    cout << "Search for 70: " << (club.searchMember(70) ? "Found" : "Not Found") << endl;
    cout << endl;

    cout << "Deleting member IDs 20 and 40...\n";
    club.removeMember(20);
    club.removeMember(40);
    club.displayMemberIds();
    cout << endl;

    cout << "Inserting member IDs 70 and 80:\n";
    club.insertMember(70);
    club.insertMember(80);
    club.displayMemberIds();
    
    return 0;
}
