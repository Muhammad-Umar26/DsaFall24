#include<iostream>
using namespace std;

class Node {
    Node* next;
    Node* prev;
    int val;
public:
    friend class DoublyLinkedList;
    Node() : next(nullptr), prev(nullptr), val(0) {};
    Node(Node* next, Node* prev, int v) : next(next), prev(prev), val(v) {};
};

class DoublyLinkedList {
    Node* head;
public:
    DoublyLinkedList() : head(nullptr) {};

    void End(int v) {
        Node* newnode = new Node(nullptr, nullptr, v);
        if (!head) {
            head = newnode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newnode;
            newnode->prev = temp;
        }
    }

    void PrintList() {
        Node* temp = head;
        while (temp) {
            cout << " <-> " << temp->val;
            temp = temp->next;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* del = head;
            head = head->next;
            delete del;
        }
    }

    void swapNodes(Node* node1, Node* node2) {
        if (node1 == node2) return;

        // Swap the next pointers
        Node* tempNext = node1->next;
        node1->next = node2->next;
        node2->next = tempNext;

        // Swap the previous pointers
        Node* tempPrev = node1->prev;
        node1->prev = node2->prev;
        node2->prev = tempPrev;

        // Adjust next pointers of adjacent nodes
        if (node1->next != nullptr) node1->next->prev = node1;
        if (node2->next != nullptr) node2->next->prev = node2;

        // Adjust previous pointers of adjacent nodes
        if (node1->prev != nullptr) node1->prev->next = node1;
        if (node2->prev != nullptr) node2->prev->next = node2;

        // If one of them is the head
        if (head == node1) head = node2;
        else if (head == node2) head = node1;
    }

    Node* Partition(Node* L, Node* R) {
        Node* pivot = L;
        Node* i = L->next;
        Node* j = R;

        while (i != j->next) {
            while (i != R && i->val <= pivot->val) {
                i = i->next;
            }
            while (j != L && j->val > pivot->val) {
                j = j->prev;
            }

            if (i != j && i != j->next) {
                swapNodes(i, j);
            }
        }
        swapNodes(pivot, j);
        return j; 
    }

    void QuickSortHelper(Node* L, Node* R) {
        if (L == nullptr || R == nullptr || L == R || L == R->next) return;

        Node* pivot = Partition(L, R);
        QuickSortHelper(L, pivot->prev);    
        QuickSortHelper(pivot->next, R);  
    }

    void QuickSort() {
        if (!head || !head->next) return;
        Node* tail = head;
        while (tail->next) {
            tail = tail->next;
        }

        QuickSortHelper(head, tail);
    }
};

int main() {
    DoublyLinkedList L1;

    L1.End(5);
    L1.End(4);
    L1.End(35);
    L1.End(2);
    L1.End(11);
    L1.End(77);
    L1.End(30);
    L1.End(24);
    L1.End(10);
    L1.End(7);

    cout << "Before Sorting: ";
    L1.PrintList();

    L1.QuickSort();

    cout << "After Sorting: ";
    L1.PrintList();
    return 0;
}
