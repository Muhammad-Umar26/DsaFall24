#include <iostream>

using namespace std;

class Node {
    int val;
    Node* next;
    Node* prev;

    public:
        Node(int val = 0, Node* next = nullptr, Node* prev = nullptr) : val(val), next(next), prev(prev) {}

        friend class DoublyLinkedList;
};

class DoublyLinkedList {
    Node* head;

    public:
        DoublyLinkedList() : head(nullptr) {}

        void insertAtFront(int val) {
            head = new Node(val, head);
            if(head->next) head->next->prev = head;
        }

        void sort() {
            Node* sortedHead = nullptr;
            Node* currSorted = nullptr;
            while(head) {
                Node* mini = head;
                for(Node* curr = head->next; curr; curr = curr->next) {
                    if(curr->val < mini->val) {
                        mini = curr;
                    }
                }

                if(mini != head) {
                    mini->prev->next = mini->next;
                } else {
                    head = head->next;
                }

                if(mini->next) mini->next->prev = mini->prev;

                if(!sortedHead) {
                    sortedHead = mini;
                    mini->prev = nullptr;
                } else {
                    currSorted->next = mini;
                    mini->prev = currSorted;
                }
                
                currSorted = mini;
                mini->next = nullptr;
            }
            head = sortedHead;
        }

        void removeDuplicates() {
            Node* curr = head;
            while(curr->next) {
                if(curr->val == curr->next->val) {
                    Node* temp = curr->next;
                    curr->next = curr->next->next;
                    if(curr->next) curr->next->prev = curr;
                    delete temp;
                } else {
                    curr = curr->next;
                }
            }
        }

        void printListForward() {
            Node* curr = head;

            while(curr) {
                cout << curr->val << " <-> ";
                curr = curr->next;
            }
            cout << "NULL" << endl;
        }

        void printListBackward() {
            Node* curr = head;
            while(curr && curr->next) {
                curr = curr->next;
            }

            while(curr) {
                cout << curr->val << " <-> ";
                curr = curr->prev;
            }
            cout << "NULL" << endl;
        }

        ~DoublyLinkedList() {
            while(head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
};

int main () {
    DoublyLinkedList dll;
    dll.insertAtFront(1);
    dll.insertAtFront(2);
    dll.insertAtFront(3);
    dll.insertAtFront(4);
    dll.insertAtFront(7);
    dll.insertAtFront(6);
    dll.insertAtFront(4);
    dll.insertAtFront(3);
    dll.insertAtFront(7);
    dll.insertAtFront(1);

    cout << "Initial list" << endl;
    dll.printListForward();

    dll.sort();

    cout << endl << "After sorting" << endl;
    dll.printListForward();

    dll.removeDuplicates();

    cout << endl << "After removing duplicates" << endl;
    dll.printListForward();
    
    return 0;
}
