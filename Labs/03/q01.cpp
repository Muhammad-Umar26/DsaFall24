#include <iostream>

using namespace std;

class Node {
    int val;
    Node* next;

    public:
        Node(int val = 0, Node* next = nullptr) : val(val), next(next) {}

        friend class SinglyLinkedList;
};

class SinglyLinkedList {
    Node* head;

    public:
        SinglyLinkedList() : head(nullptr) {}

        void insertAtFront(int val) {
            head = new Node(val, head);
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
            }
        }

        void insertBeforeValue(int targetVal, int insertVal) {
            if(head->val == targetVal) {
                head = new Node(insertVal, head);
            } else {
                Node* curr = head;
                while(curr->next->val != targetVal) {
                    curr = curr->next;
                }
                curr->next = new Node(insertVal, curr->next);
            }
        }

        void insertAfterValue(int targetVal, int insertVal) {
            Node* curr = head;
            while(curr->val != targetVal) {
                curr = curr->next;
            }
            curr->next = new Node(insertVal, curr->next);
        }

        void deleteAtFront() {
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        void deleteAtEnd() {
            Node* curr = head;
            while(curr->next->next) {
                curr = curr->next;
            }

            Node* temp = curr->next;
            curr->next = nullptr;
            delete temp;
        }

        void deleteParticularValue(int val) {
            if(val == head->val) {
                deleteAtFront();
            } else {
                Node* curr = head;
                while(curr->next->val != val) {
                    curr = curr->next;
                }

                Node* temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
            }
        }

        int countNodes() {
            int count = 0;
            for(Node* curr = head; curr; curr = curr->next) {
                ++count;
            }
            return count;
        }

        void printList() {
            for(Node* curr = head; curr; curr = curr->next) {
                cout << curr->val << " -> ";
            }
            cout << "NULL" << endl;
        }

        ~SinglyLinkedList() {
            while(head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
};

int main() {
    SinglyLinkedList sll;
    sll.insertAtFront(1);
    sll.insertAtFront(2);
    sll.insertAtFront(3);
    sll.insertAtFront(4);

    sll.printList();

    sll.insertAtEnd(5);
    sll.insertAtEnd(6);
    sll.insertAtEnd(7);
    sll.insertAtEnd(8);

    sll.printList();

    sll.insertBeforeValue(5, 9);
    sll.insertAfterValue(2, 10);

    sll.printList();

    sll.deleteAtFront();
    sll.deleteAtEnd();
    sll.deleteParticularValue(1);

    sll.printList();

    cout << endl << "Number of nodes in list : " << sll.countNodes() << endl;

    return 0;
}
