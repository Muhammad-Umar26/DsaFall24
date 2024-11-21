#include <iostream>

using namespace std;

class Record {
    struct Node {
        int score;
        string name;
        Node* next;
        Node* prev;

        Node(string name = "", int score = 0, Node* next = nullptr, Node* prev = nullptr) : name(name), score(score), next(next), prev(prev) {};
    };

    Node *head, *tail;

    int getMax(){
        int maxi;
        Node* curr = head;
        if(curr) {
            maxi = curr->score;
            curr = curr->next;
            while(curr){
                if(maxi < curr->score){
                    maxi = curr->score;
                }
                    
                curr = curr->next;
            }
        }
        return maxi;
    }

    void countSort(int exp){
        Node* sortedHead = nullptr;
        Node* sortedTail = nullptr;
        int count[10] = {0};
        Node* curr = head;

        while(curr) {
            ++count[(curr->score / exp) % 10];
            curr = curr->next;
        }

        for(int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        int n = 0;
        curr = head;
        while(curr) {
            ++n;
            curr = curr->next;
        }

        Node* output[n];

        curr = tail;
        while(curr) {
            int index = (curr->score / exp) % 10;
            output[--count[index]] = curr;
            curr = curr->prev;
        }

        sortedHead = output[0];
        sortedTail = output[n - 1];
        for(int i = 0; i < n - 1; i++) {
            output[i]->next = output[i + 1];
            output[i + 1]->prev = output[i];
        }
        
        sortedHead->prev = nullptr;
        sortedTail->next = nullptr;

        head = sortedHead;
        tail = sortedTail;
    }

    public:
        Record() : head(nullptr), tail(nullptr) {};

        void insert(string name, int score) {
            tail = new Node(name, score, nullptr, tail);
            if(tail->prev) {
                tail->prev->next = tail;
            } else {
                head = tail;
            }
        }

        void printList() {
            for(Node* curr = head; curr; curr = curr->next) {
                cout << curr->name << " " << curr->score << endl;
            }
        }

        void radixsort() {
            int m = getMax();
            for(int exp = 1; m / exp > 0; exp *= 10) {
                countSort(exp);
            }
        }

        ~Record() {
            while(head) {
                Node *curr = head;
                head = head->next;
                delete curr;
            }
        }
};

int main() {
    Record record;
    record.insert("Jeena", 40);
    record.insert("Zara", 50);
    record.insert("Sara", 70);
    record.insert("Ali", 60);
    record.insert("Ayan", 90);

    record.radixsort();

    cout << "Sorted list of student records:" << endl;
    record.printList();

    return 0;
}
