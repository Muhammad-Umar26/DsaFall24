#include <iostream>

using namespace std;

class Stack {
    struct Node {
        int val;
        Node* next;

        Node(int val, Node* next = nullptr) : val(val), next(next) {}
    };

    Node* head;
    
    public :
        Stack() : head(nullptr) {}

        bool isEmpty() {
            return !head;
        }

        void push(int val) {
            head = new Node(val, head);
        }

        int pop() {
            if(isEmpty()) {
                cout << "Stack Underflow" << endl;
                return -1;
            }

            int val = head->val;

            Node* temp = head;
            head = head->next;
            delete temp;

            return val;
        }

        int peek() {
            if(isEmpty()) {
                cout << "No element in stack" << endl;
                return -1;
            }
            return head->val;
        }

        ~Stack() {
            while(head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
};

void printStack(Stack& s) {
    while(!s.isEmpty()) {
        cout << s.peek() << " ";
        s.pop();
    }
    cout << endl;
}

int main() {
    Stack s;
    int n = 7;

    for(int i = 0; i < n; ++i) {
        s.push(i + 1);
    }

    Stack odd, even;

    while(!s.isEmpty()) {
        if(s.peek() & 1) {
            odd.push(s.pop());
        } else {
            even.push(s.pop());
        }
    }

    cout << endl << "Even Stack : ";
    printStack(even);

    cout << endl << "Odd Stack : ";
    printStack(odd);

    return 0;
}
