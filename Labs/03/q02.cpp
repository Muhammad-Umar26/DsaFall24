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

        Node* reverseHelper(Node* node) {
            if(!node || !node->next) return node;

            Node* reversed = reverseHelper(node->next);
            node->next->next = node;
            node->next = nullptr;

            return reversed;
        }

        void reverse() {
            head = reverseHelper(head);
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
    sll.insertAtFront(5);
    sll.insertAtFront(6);
    sll.insertAtFront(7);
    sll.insertAtFront(8);

    cout << "Before reversing" << endl;
    sll.printList();
    
    sll.reverse();
    
    cout << endl << "After reversing" << endl;
    sll.printList();

    return 0;
}
