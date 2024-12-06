#include <iostream>
#include <queue>

using namespace std;

class BinaryTree {
    struct Node {
        char val;
        Node* left;
        Node* right;

        Node(char val, Node* left = nullptr, Node* right = nullptr) : val(val), left(left), right(right) {}
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

                if(curr) {
                    ans += curr->val;
                    q.push(curr->left);
                    q.push(curr->right);
                } else {
                    ans += '#';
                }
            }

            while(!ans.empty() && ans.back() == '#') {
                ans.pop_back();
            }
            return ans;
        }

        void constructFromString(const string s) {
            if(s.empty()) return;

            root = new Node(s[0]);

            queue<Node*> q;
            q.push(root);
            for(int i = 1; i < s.size(); ++i) {
                Node* curr = q.front();
                q.pop();

                if(s[i] != '#') {
                    curr->left = new Node(s[i]);
                    q.push(curr->left);
                }
                ++i;

                if(i < s.size() && s[i] != '#') {
                    curr->right = new Node(s[i]);
                    q.push(curr->right);
                }
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
    cout << stringFromTree << endl;

    BinaryTree newBt;
    newBt.constructFromString(stringFromTree);

    cout << endl << "New Constructed Binary tree : " << endl;
    newBt.dfs();

    return 0;
}
