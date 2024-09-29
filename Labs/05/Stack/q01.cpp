#include <iostream>

using namespace std;

class Stack {
    int* arr;
    int size, top;
    
    public :
        Stack(int size = 10) : size(size), top(-1), arr(new int[size]) {}

        bool isEmpty() {
            return top == -1;
        }

        bool isFull() {
            return top == size - 1;
        }

        void push(int val) {
            if(isFull()) {
                cout << "Stack Overflow" << endl;
            } else {
                cout << "Pushing " << val << endl;
                arr[++top] = val;
            }
        }

        int pop() {
            if(isEmpty()) {
                cout << "Stack Underflow" << endl;
                return -1;
            }
            return arr[top--];
        }

        int peek() {
            if(isEmpty()) {
                cout << "No element in stack" << endl;
                return -1;
            }
            return arr[top];
        }
};

int main() {
    Stack s(5);

    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);
    s.push(60);

    cout << endl << "Top element is: " << s.peek() << endl << endl;

    cout << s.isEmpty() << endl;
    cout << s.isFull() << endl << endl;

    cout << "Popped element: " << s.pop() << endl;
    cout << "Popped element: " << s.pop() << endl;
    cout << "Popped element: " << s.pop() << endl;

    cout << endl << "Top element is: " << s.peek() << endl << endl;

    cout << "Popped element: " << s.pop() << endl;
    cout << "Popped element: " << s.pop() << endl;
    cout << "Popped element: " << s.pop() << endl;

    cout << endl << s.isEmpty() << endl;
    cout << s.isFull() << endl << endl;

    return 0;
}
