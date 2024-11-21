#include <iostream>

using namespace std;

class SinglyLinkedList {
    struct Node {
        int val;
        Node* next;

        Node(int val = 0, Node* next = nullptr) : val(val), next(next) {}
    };

    Node* head;

    void swap(Node* node1, Node* node2) {
        if(!node1 || !node2 || node1 == node2) return;
        
        Node* prevNode1 = nullptr;
        for(Node* curr = head; curr != node1; curr = curr->next) {
            prevNode1 = curr;
        }
        
        Node* prevNode2 = nullptr;
        for(Node* curr = head; curr != node2; curr = curr->next) {
            prevNode2 = curr;
        }
        
        if(node1->next == node2) {
            node1->next = node2->next;
            node2->next = node1;
        } else {
            Node* temp = node2->next;
            node2->next = node1->next;
            node1->next = temp;
            
            prevNode2->next = node1;
        }
        
        if(prevNode1) {
            prevNode1->next = node2;
        } else {
            head = node2;
        }
    }

    Node* getTail(Node* curr){
        while(curr && curr->next) {
            curr = curr->next;
        }
        return curr;
    }
    
    Node* partition(Node* head, Node* end, Node*& newHead, Node*& newEnd){
        Node* pivot = end;
        Node* prev = nullptr;
        Node* curr = head;
        Node* tail = pivot;

        while(curr != pivot){
            if (curr->val < pivot->val) {
                if(!newHead) {
                    newHead = curr;
                }

                prev = curr;
                curr = curr->next;
            } else {
                if(prev) prev->next = curr->next;
                Node* temp = curr->next;
                curr->next = nullptr;
                tail->next = curr;
                tail = curr;
                curr = temp;
            }
        }

        if(!newHead) newHead = pivot;

        newEnd = tail;

        return pivot;
    }

    Node* quickSort(Node* head, Node* end) {
        if(!head || head == end) return head;

        Node* newHead = nullptr, *newEnd = nullptr;
        Node* pivot = partition(head, end, newHead, newEnd);

        if(newHead != pivot) {
            Node* temp = newHead;
            while(temp->next != pivot) {
                temp = temp->next;
            }
            temp->next = nullptr;

            newHead = quickSort(newHead, temp);

            temp = getTail(newHead);
            temp->next = pivot;
        }

        pivot->next = quickSort(pivot->next, newEnd);

        return newHead;
    }

    public:
        SinglyLinkedList() : head(nullptr) {}

        void insertAtFront(int val) {
            head = new Node(val, head);
        }

        void quickSort() {
            head = quickSort(head, getTail(head));
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
    sll.insertAtFront(3);
    sll.insertAtFront(5);
    sll.insertAtFront(1);
    sll.insertAtFront(9);
    sll.insertAtFront(8);
    sll.insertAtFront(7);
    sll.insertAtFront(10);

    cout << "Initial list:" << endl;
    sll.printList();

    sll.quickSort();

    cout << endl << "After sorting" << endl;
    sll.printList();
    
    return 0;
}
