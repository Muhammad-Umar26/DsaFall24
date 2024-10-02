#include <iostream>

#define size 10

using namespace std;

// USING LINEAR QUEUE
// class TicketQueue {
//     string names[size];
//     int start, rear;

//     public :
//         TicketQueue() : start(-1), rear(-1) {}

//         bool isEmpty() {
//             return start == -1;
//         }

//         bool isFull() {
//             return rear == size - 1;
//         }

//         void enqueue(string val) {
//             if(isFull()) {
//                 cout << "Cant enqueue as queue is already full" << endl;
//                 return;
//             }
//             names[++rear] = val;
            
//             if(start == -1) ++start;
//         }

//         string dequeue() {
//             if(isEmpty()) {
//                 cout << "Queue is already empty" << endl;
//                 return "";
//             }

//             return names[start++];
//         }

//         string front() {
//             if(isEmpty()) {
//                 cout << "No element in queue" << endl;
//                 return "";
//             }

//             return names[start];
//         }
// };

// USING CIRCULAR QUEUE
// We should use circulr queue instead of linear queue so that it can handle space efficiently
// class TicketQueue {
//     string names[size];
//     int start, rear;

//     public :
//         TicketQueue() : start(-1), rear(-1) {}

//         bool isEmpty() {
//             return start == -1 && rear == -1;
//         }

//         bool isFull() {
//             return (rear + 1) % size == start;
//         }

//         void enqueue(string val) {
//             if(isFull()) {
//                 cout << "Cant enqueue as queue is already full" << endl;
//                 return;
//             }
//             rear = (rear + 1) % size;
//             names[rear] = val;
            
//             if(start == -1) ++start;
//         }

//         string dequeue() {
//             if(isEmpty()) {
//                 cout << "Queue is already empty" << endl;
//                 return "";
//             }

//             string val = names[start];

//             if(start == rear) {
//                 start = rear = -1;
//             } else {
//                 start = (start + 1) % size;
//             }

//             return val;
//         }

//         string front() {
//             if(isEmpty()) {
//                 cout << "No element in queue" << endl;
//                 return "";
//             }

//             return names[start];
//         }
// };

// USING LINKED LIST
class TicketQueue {
    struct Node {
        string val;
        Node* next;

        Node(string val = 0, Node* next = nullptr) : val(val), next(next) {}
    };

    Node* start;
    Node* rear;
    int count;

    public :
        TicketQueue() : start(nullptr), rear(nullptr), count(0) {}

        bool isEmpty() {
            return start == nullptr;
        }

        bool isFull() {
            return count == size;
        }

        void enqueue(string val) {
            if(isFull()) {
                cout << "Cant enqueue as queue is already full" << endl;
                return;
            }

            ++count;
            
            if(!start) {
                start = rear = new Node(val);
            } else {
                rear->next = new Node(val);
                rear = rear->next;
            }
        }

        string dequeue() {
            if(isEmpty()) {
                cout << "Queue is already empty" << endl;
                return "";
            }

            --count;
            
            string val = start->val;

            Node* temp = start;

            if(start == rear) {
                start = rear = nullptr;
            } else {
                start = start->next;
            }

            delete temp;

            return val;
        }

        string front() {
            if(isEmpty()) {
                cout << "No element in queue" << endl;
                return "";
            }

            return start->val;
        }

        ~TicketQueue() {
            while(start) {
                Node* temp = start;
                start = start->next;
                delete temp;
            }
        }
};

int main() {
    TicketQueue q;

    q.enqueue("Passenger1");
    q.enqueue("Passenger2");
    q.enqueue("Passenger3");
    q.enqueue("Passenger4");
    q.enqueue("Passenger5");
    q.enqueue("Passenger6");
    q.enqueue("Passenger7");
    q.enqueue("Passenger8");
    q.enqueue("Passenger9");
    q.enqueue("Passenger10");

    cout << "Front element is: " << q.front() << endl << endl;

    cout << "Dequeue element: " << q.dequeue() << endl;
    cout << "Dequeue element: " << q.dequeue() << endl;
    cout << "Dequeue element: " << q.dequeue() << endl;
    cout << "Dequeue element: " << q.dequeue() << endl;
    cout << "Dequeue element: " << q.dequeue() << endl << endl;

    cout << "Front element is: " << q.front() << endl << endl;

    q.enqueue("Passenger11");
    q.enqueue("Passenger12");
    q.enqueue("Passenger13");
    q.enqueue("Passenger14");
    q.enqueue("Passenger15");

    for (int i = 0; i < 10; i++) {
        cout << "Dequeue element: " << q.dequeue() << endl;
    }

    return 0;
}
