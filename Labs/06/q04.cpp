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

class Queue {
    Stack st;

    public :
        bool isEmpty() {
            return st.isEmpty();
        }

        void enqueue(int val) {
            Stack temp;

            while(!st.isEmpty()) {
                temp.push(st.pop());
            }

            st.push(val);

            while(!temp.isEmpty()) {
                st.push(temp.pop());
            }
        }

        int dequeue() {
            if(isEmpty()) {
                cout << "Queue is already empty" << endl;
                return -1;
            }

            return st.pop();
        }

        int front() {
            if(isEmpty()) {
                cout << "No element in queue" << endl;
                return -1;
            }

            return st.peek();
        }
};

#include <iostream>

int main() {
    Queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Front element is: " << q.front() << endl << endl;

    cout << "Dequeue element: " << q.dequeue() << endl;
    cout << "Dequeue element: " << q.dequeue() << endl << endl;

    cout << "Front element is: " << q.front() << endl << endl;

    cout << "Dequeue element: " << q.dequeue() << endl << endl;

    cout << "Dequeue element: " << q.dequeue() << endl;

    return 0;
}
