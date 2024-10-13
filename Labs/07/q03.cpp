#include <iostream>
using namespace std;

struct Node {
    Node *next,*prev;
    int score;
    string name;

    Node(string name = "", int sc = 0, Node *next = nullptr, Node *prev = nullptr) : next(next), score(sc), name(name), prev(prev) {};
};

class Record {
    Node *head, *tail;
    
    public:
        Record() : head(nullptr), tail(NULL) {};

        void insertAtEnd(string name, int score) {
            tail = new Node(name, score, nullptr, tail);
            if(tail->prev) {
                tail->prev->next = tail;
            } else {
                head = tail;
            }
        }

        void PrintList() {
            for (Node *curr = head; curr; curr = curr->next) {
                cout << curr->name << " " << curr->score << endl;
            }
        }

        ~Record() {
            while (head) {
                Node *curr = head;
                head = head->next;
                delete curr;
            }
        }

        int getMax(){
            int maxi;
            Node *curr = head;
            if(curr) {
                maxi = curr->score;
                curr = curr->next;
                while(curr) {
                    if (maxi < curr->score) {
                        maxi = curr->score;
                    }
                    curr = curr->next;
                }
            }
            return maxi;
        }

        void countSort(int exp){
            Node *sortedHead = nullptr, *sortedTail = nullptr;
            int count[10] = {0};
            Node* curr = head;

            while(curr) {
                ++count[(curr->score / exp) % 10];
                curr = curr->next;
            }

            for (int i = 1; i < 10; i++) {
                count[i] += count[i - 1];
            }

            int n = 0;
            curr = head;
            while(curr) {
                n++;
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

        void radixsort() {
            int m = getMax();
            for(int exp = 1; m / exp > 0; exp *= 10) {
                countSort(exp);
            }
        }
};

int main() {
    Record rec;
    rec.insertAtEnd("Ayan", 90);
    rec.insertAtEnd("Ali", 60);
    rec.insertAtEnd("Sara", 70);
    rec.insertAtEnd("Zara", 50);
    rec.insertAtEnd("Jeena", 40);

    rec.radixsort();

    cout << "Sorted list of student records:" << endl;
    rec.PrintList();

    return 0;
}
