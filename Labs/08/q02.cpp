#include <iostream>
#include <queue>

using namespace std;

class BinaryTree {
    struct Node {
        int val;
        Node* left;
        Node* right;

        Node(int val, Node* left = nullptr, Node* right = nullptr) : val(val), left(left), right(right) {}
    };

    Node *root;

    void dfsHelper(Node* node) {
        if(!node) return;

        cout << node->val << " ";
        dfsHelper(node->left);
        dfsHelper(node->right);
    }

    void destroyTree(Node* node) {
        if(!node) return;
        
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    public:
        BinaryTree() : root(nullptr) {}

        void insertNode(int data) {
            Node* newNode = new Node(data);

            if(!root) {
                root = newNode;
                return;
            }

            queue<Node*> q;
            q.push(root);

            while(!q.empty()) {
                Node* curr = q.front();
                q.pop();

                if(curr->left) {
                    q.push(curr->left);
                } else {
                    curr->left = newNode;
                    return;
                }

                if(curr->right) {
                    q.push(curr->right);
                } else {
                    curr->right = newNode;
                    return;
                }
            }
        }
        
        void zigZagOrder() {
            queue<Node*> q;
            if(root) q.push(root);

            int level = 1;
            while(!q.empty()) {
                deque<int> temp;
                for(int size = q.size(); size; --size) {
                    Node* curr = q.front();
                    q.pop();

                    if(level & 1) {
                        temp.push_back(curr->val);
                    } else {
                        temp.push_front(curr->val);
                    }

                    if(curr->left) {
                        q.push(curr->left);
                    }

                    if(curr->right) {
                        q.push(curr->right);
                    }
                }
                
                cout << "Level " << level++ << " : ";
                for(int& num : temp) {
                    cout << num << " ";
                }
                cout << endl;
            }
        }

        void dfs() {
            dfsHelper(root);
            cout << endl;
        }

        ~BinaryTree() {
            destroyTree(root);
        }
};

int main() {
    BinaryTree bt;
    bt.insertNode(2);
    bt.insertNode(8);
    bt.insertNode(7);
    bt.insertNode(10);
    bt.insertNode(9);
    bt.insertNode(7);
    bt.insertNode(3);

    cout << "Original Binary tree : " << endl;
    bt.dfs();

    cout << endl << "Zigzag Binary tree : " << endl;
    bt.zigZagOrder();

    return 0;
}
