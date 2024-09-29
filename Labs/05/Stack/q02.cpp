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
            cout << "Pushing " << val << endl;
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

int main() {
    Stack s;

    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);

    cout << endl << "Top element is: " << s.peek() << endl << endl;

    cout << s.isEmpty() << endl << endl;

    cout << "Popped element: " << s.pop() << endl;
    cout << "Popped element: " << s.pop() << endl;
    cout << "Popped element: " << s.pop() << endl;

    cout << endl << "Top element is: " << s.peek() << endl << endl;

    cout << "Popped element: " << s.pop() << endl;
    cout << "Popped element: " << s.pop() << endl;
    cout << "Popped element: " << s.pop() << endl;

    cout << endl << s.isEmpty() << endl;

    return 0;
}
