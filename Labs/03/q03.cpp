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

        void segregateEvenOdd() {
            Node* evenHead = nullptr;
            Node* oddHead = nullptr;
            Node* evenCurr = nullptr;
            Node* oddCurr = nullptr;

            for(Node* curr = head; curr; curr = curr->next) {
                if(curr->val & 1) {
                    if(!oddHead) {
                        oddHead = curr;
                        oddCurr = curr;
                    } else {
                        oddCurr->next = curr;
                        oddCurr = oddCurr->next;
                    }
                } else {
                    if(!evenHead) {
                        evenHead = curr;
                        evenCurr = curr;
                    } else {
                        evenCurr->next = curr;
                        evenCurr = evenCurr->next;
                    }
                }
            }

            if(evenCurr) evenCurr->next = oddHead;
            if(oddCurr) oddCurr->next = nullptr;

            head = evenHead ? evenHead : oddHead;
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

int main () {
    SinglyLinkedList sll;
    sll.insertAtFront(6);
    sll.insertAtFront(7);
    sll.insertAtFront(1);
    sll.insertAtFront(4);
    sll.insertAtFront(5);
    sll.insertAtFront(10);
    sll.insertAtFront(12);
    sll.insertAtFront(8);
    sll.insertAtFront(15);
    sll.insertAtFront(17);

    cout << "Original List" << endl;
    sll.printList();

    sll.segregateEvenOdd();

    cout << endl << "Segregated List" << endl;
    sll.printList();
    
    return 0;
}
