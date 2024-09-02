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

        void insertAtEnd(int val) {
            Node* newNode = new Node(val);
            if(!head) {
                head = newNode;
            } else {
                Node* curr = head;
                while(curr->next) {
                    curr = curr->next;
                }
                curr->next = newNode;
                newNode->prev = curr;
            }
        }

        void insertBeforeValue(int targetVal, int insertVal) {
            if(!head) return;

            if(head->val == targetVal) {
                insertAtFront(insertVal);
            } else {
                Node* curr = head;
                while(curr->next->val != targetVal) {
                    curr = curr->next;
                }
                curr->next = new Node(insertVal, curr->next, curr);
                curr->next->next->prev = curr->next;
            }
        }

        void insertAfterValue(int targetVal, int insertVal) {
            Node* curr = head;
            while(curr && curr->val != targetVal) {
                curr = curr->next;
            }

            if(curr) {
                curr->next = new Node(insertVal, curr->next, curr);
                if(curr->next->next) curr->next->next->prev = curr->next;
            }
        }

        void deleteAtFront() {
            if(!head) return;

            Node* temp = head;
            head = head->next;
            delete temp;

            if(head) head->prev = nullptr;
        }

        void deleteAtEnd() {
            if(!head || !head->next) {
                deleteAtFront();
            } else {
                Node* curr = head;
                while(curr->next->next) {
                    curr = curr->next;
                }

                Node* temp = curr->next;
                curr->next = nullptr;
                delete temp;
            }
        }

        void deleteParticularValue(int val) {
            if(!head) return;

            if(val == head->val) {
                deleteAtFront();
            } else {
                Node* curr = head;
                while(curr->next && curr->next->val != val) {
                    curr = curr->next;
                }

                if(curr->next) {
                    Node* temp = curr->next;
                    curr->next = curr->next->next;
                    delete temp;

                    if(curr->next) curr->next->prev = curr;
                }
            }
        }

        void printList() {
            if(!head) return;

            Node* curr = head;

            cout << "Forward Traverse" << endl;
            while(curr->next) {
                cout << curr->val << " -> ";
                curr = curr->next;
            }
            cout << curr->val << " -> " << "NULL" << endl;

            cout << endl << "Backward Traverse" << endl;
            while(curr) {
                cout << curr->val << " -> ";
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

    dll.printList();

    dll.insertAtEnd(5);
    dll.insertAtEnd(6);
    dll.insertAtEnd(7);
    dll.insertAtEnd(8);

    cout << endl << endl;
    dll.printList();

    dll.insertBeforeValue(5, 9);
    dll.insertAfterValue(2, 10);

    cout << endl << endl;
    dll.printList();

    dll.deleteAtFront();
    dll.deleteAtEnd();
    dll.deleteParticularValue(1);

    cout << endl << endl;
    dll.printList();
    
    return 0;
}
