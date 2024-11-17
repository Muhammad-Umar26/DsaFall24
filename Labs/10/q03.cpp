#include <iostream>
#include <vector>

using namespace std;

class Heap { // Min Heap
    vector<int> arr;

    public:
        void insert(int val) {
            arr.push_back(val);

            for(int i = arr.size() - 1, parent; i; i = parent) {
                parent = (i - 1) / 2;

                if(arr[i] < arr[parent]) {
                    swap(arr[i], arr[parent]);
                } else {
                    return;
                }
            }
        }

        void deleteVal() {
            if(arr.empty()) return;

            arr.front() = arr.back();
            arr.pop_back();

            for(int i = 0, smallest; i < arr.size(); i = smallest) {
                int left = 2 * i + 1, right = 2 * i + 2;
                smallest = i;

                if(left < arr.size() && arr[left] < arr[smallest]) {
                    smallest = left;
                }

                if(right < arr.size() && arr[right] < arr[smallest]) {
                    smallest = right;
                }

                if(smallest != i) {
                    swap(arr[i], arr[smallest]);
                } else {
                    return;
                }
            }
        }

        int size() {
            return arr.size();
        }

        bool empty() {
            return arr.empty();
        }

        int top() {
            return arr.empty() ? -1 : arr[0];
        }

        void print() {
            for(int& a : arr) {
                cout << a << " ";
            }
            cout << endl;
        }
};

struct Node {
    int val;
    Node* next;

    Node(int val = 0, Node* next = nullptr) : val(val), next(next) {}
};

class SinglyLinkedList {
    public:
        Node* head;

        SinglyLinkedList() : head(nullptr) {}

        void insertAtFront(int val) {
            head = new Node(val, head);
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

SinglyLinkedList mergeKSortedLists(vector<SinglyLinkedList>& lists) {
    SinglyLinkedList merged;
    int i = 0;
    while(i < lists.size() && !lists[i].head) {
        ++i;
    }

    if(i == lists.size()) return merged;

    merged.head = lists[i].head;
    lists[i].head = nullptr;

    Node* curr = merged.head;
    Heap heap;

    for( ; curr; curr = curr->next) {
        heap.insert(curr->val);
        if(!curr->next) {
            while(i < lists.size() - 1) {
                ++i;
                if(lists[i].head) {
                    curr->next = lists[i].head;
                    lists[i].head = nullptr;
                    break;
                }
            }
        }
    }
    
    for(curr = merged.head; !heap.empty(); curr = curr->next) {
        curr->val = heap.top();
        heap.deleteVal();
    }

    return merged;
}

int main() {
    vector<SinglyLinkedList> lists(5);

    lists[0].insertAtFront(7);
    lists[0].insertAtFront(5);
    lists[0].insertAtFront(3);
    lists[0].insertAtFront(1);

    lists[2].insertAtFront(15);
    lists[2].insertAtFront(12);
    lists[2].insertAtFront(9);

    lists[4].insertAtFront(8);
    lists[4].insertAtFront(6);
    lists[4].insertAtFront(4);
    lists[4].insertAtFront(2);

    cout << "Input Lists:" << endl;
    for (int i = 0; i < lists.size(); ++i) {
        cout << "List " << i + 1 << ": ";
        lists[i].printList();
    }

    SinglyLinkedList merged = mergeKSortedLists(lists);

    cout << endl << "Merged List:" << endl;
    merged.printList();

    return 0;
}
