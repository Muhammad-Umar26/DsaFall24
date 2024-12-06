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

        void dfs() {
            dfsHelper(root);
            cout << endl;
        }

        bool isSameTree(Node* node1, Node* node2) {
            if(!node1 && !node2) return true;
            if(!node1 || !node2 || node1->val != node2->val) return false;

            return isSameTree(node1->left, node2->left) && isSameTree(node1->right, node2->right);
        }

        bool isSubtree(BinaryTree T2) {
            if(!T2.root) return true;
            if(!root) return false;

            queue<Node*> q;
            q.push(root);

            while(!q.empty()) {
                Node* curr = q.front();
                q.pop();

                if(curr->val == T2.root->val && isSameTree(curr, T2.root)) return true;

                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);
            }
            return false;
        }

        ~BinaryTree() {
            destroyTree(root);
        }
};

int main() {
    BinaryTree T1;
    T1.insertNode(2);
    T1.insertNode(8);
    T1.insertNode(7);
    T1.insertNode(10);
    T1.insertNode(9);
    T1.insertNode(7);
    T1.insertNode(3);

    BinaryTree T2;
    T2.insertNode(7);
    T2.insertNode(7);
    T2.insertNode(3);

    cout << "T1 : ";
    T1.dfs();

    cout << "T2 : ";
    T2.dfs();

    if(T1.isSubtree(T2)) {
        cout << endl << "T2 is subtree of T1" << endl;
    } else {
        cout << endl << "T2 is not a subtree of T1" << endl;
    }

    return 0;
}
