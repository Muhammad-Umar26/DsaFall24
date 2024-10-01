#include <iostream>
#include <algorithm>
#include <ctype.h>

using namespace std;

class Stack {
    struct Node {
        char val;
        Node* next;

        Node(char val, Node* next = nullptr) : val(val), next(next) {}
    };

    Node* head;

    public :
        Stack() : head(nullptr) {}

        bool isEmpty() {
            return !head;
        }

        void push(char val) {
            head = new Node(val, head);
        }

        char pop() {
            if(isEmpty()) {
                cout << "Stack Underflow" << endl;
                return '\0';
            }

            char val = head->val;

            Node* temp = head;
            head = head->next;
            delete temp;

            return val;
        }

        char peek() {
            if(isEmpty()) {
                cout << "No element in stack" << endl;
                return '\0';
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

int precedence(char op) {
    return op == '+' || op == '-' ? 1 : (op == '*' || op == '/' ? 2 : (op == '^' ? 3 : -1));
}

string infixToPostfix(string& s) {
    string postfix;
    Stack st;

    for(char& c : s) {
        if(isalnum(c)) {
            postfix += c;
        } else if(c == '(') {
            st.push(c);
        } else if(c == ')'){
            while(!st.isEmpty() && st.peek() != '(') {
                postfix += st.pop();
            }
            st.pop();
        } else {
            while(!st.isEmpty() && precedence(c) <= precedence(st.peek())) {
                postfix += st.pop();
            }
            st.push(c);
        }
    }

    while(!st.isEmpty()) {
        postfix += st.pop();
    }

    return postfix;
}

string infixToPrefix(string s) {
    // Reverse the infix expression
    reverse(s.begin(), s.end());

    // Swap '(' with ')' and vice versa to adjust for reversed expression
    for(char& c: s) {
        if(c == '(') {
            c = ')';
        } else if(c == ')') {
            c = '(';
        }
    }

    string prefix = "";
    Stack st;

    for(char& c : s) {
        if(isalnum(c)) {
            prefix += c;
        } else if(c == '(') {
            st.push(c);
        } else if(c == ')'){
            while(!st.isEmpty() && st.peek() != '(') {
                prefix += st.pop();
            }
            st.pop();
        } else { 
            // Modified operator handling for prefix
            // Step 4: Handle operators with precedence and associativity
            while(!st.isEmpty() && (precedence(c) < precedence(st.peek()) || (c == '^' && st.peek() == '^'))) {
                prefix += st.pop();
            }
            st.push(c);
        }
    }

    while(!st.isEmpty()) {
        prefix += st.pop();
    }

    // Reverse the result to get the correct prefix expression
    reverse(prefix.begin(), prefix.end());

    return prefix;
}

int main() {
    string s = "K+L-M*N+(O^P)*W/U/V*T+Q";

    cout << "Infix : " << s << endl << "Postfix : " << infixToPostfix(s) << endl << "Prefix : " << infixToPrefix(s) << endl;

    return 0;
}
