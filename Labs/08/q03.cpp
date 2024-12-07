#include <iostream>
#include <vector>
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

    int findMaxProfitPath(Node* node, vector<int>& currPath, vector<int>& maxPath, int& maxProfit) {
        if(!node) return 0;

        vector<int> leftPath, rightPath;

        int profit1 = findMaxProfitPath(node->left, leftPath, maxPath, maxProfit);
        int profit2 = findMaxProfitPath(node->right, rightPath, maxPath, maxProfit);

        if(profit1 + profit2 + node->val > maxProfit) {
            maxProfit = profit1 + profit2 + node->val;
            maxPath = leftPath;
            maxPath.push_back(node->val);
            maxPath.insert(maxPath.end(), rightPath.rbegin(), rightPath.rend());
        }

        int currProfit = 0;
        if(profit1 >= profit2 && profit1 > 0) {
            currProfit = profit1;
            currPath = leftPath;
        } else if(profit2 > 0) {
            currProfit = profit2;
            currPath = rightPath;
        } else {
            currPath.clear();
        }
        currProfit += node->val;
        currPath.push_back(node->val);

        return currProfit;
    }

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

        pair<vector<int>, int> findMaxProfitPath() {
            if(!root) return {{}, 0};

            vector<int> currPath, maxPath;
            int maxProfit = INT_MIN;
            findMaxProfitPath(root, currPath, maxPath, maxProfit);
            return {maxPath, maxProfit};
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
    bt.insertNode(10);
    bt.insertNode(2);
    bt.insertNode(10);
    bt.insertNode(-25);
    bt.insertNode(20);
    bt.insertNode(3);
    bt.insertNode(1);
    bt.insertNode(4);

    cout << "Binary Tree : ";
    bt.dfs();

    pair<vector<int>, int> ans = bt.findMaxProfitPath();

    cout << "Maximum Profit Path : ";
    for(int& num : ans.first) {
        cout << num << " ";
    }

    cout << endl << "Maximum Profit : " << ans.second << endl;

    return 0;
}
