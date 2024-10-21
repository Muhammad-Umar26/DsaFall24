#include <iostream>
#include <queue>

using namespace std;

struct Node {
    char val;
    Node* left;
    Node* right;

    Node(char val, Node* left = nullptr, Node* right = nullptr) : val(val), left(left), right(right) {}
};

class BinaryTree {
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

        void insertNode(char data) {
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
        
        string readTreeLevelOrder() {
            if(!root) return "";
            
            string ans = "";

            queue<Node*> q;
            q.push(root);

            while(!q.empty()) {
                Node* curr = q.front();
                q.pop();

                ans += curr->val;

                if(curr->left) {
                    q.push(curr->left);
                }

                if(curr->right) {
                    q.push(curr->right);
                }
            }
            return ans;
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
    bt.insertNode('a');
    bt.insertNode('b');
    bt.insertNode('c');
    bt.insertNode('d');
    bt.insertNode('e');
    bt.insertNode('a');
    bt.insertNode('f');

    cout << "Original Binary tree : " << endl;
    bt.dfs();

    string stringFromTree = bt.readTreeLevelOrder();

    BinaryTree newBt;
    for(char& c : stringFromTree) {
        newBt.insertNode(c);
    }

    cout << endl << "New Constructed Binary tree : " << endl;
    newBt.dfs();

    return 0;
}
