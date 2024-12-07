#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int val = 0, Node* left = nullptr, Node* right = nullptr) : val(val), left(left), right(right) {}
};

class BinarySearchTree {
    Node* root;

    Node* insert(Node* node, int val) {
        if(!node) {
            return new Node(val);
        }

        if(val == node->val) return node;

        if(val < node->val) {
            node->left = insert(node->left, val);
        } else {
            node->right = insert(node->right, val);
        }

        return node;
    }

    Node* search(Node* node, int val) {
        if(!node || val == node->val) {
            return node;
        }

        if(val < node->val) {
            return search(node->left, val);
        }

        return search(node->right, val);
    }

    Node* searchWrongNodes(Node* node, int val) {
        if(!node || val == node->val) {
            return node;
        }
        
        Node* n = searchWrongNodes(node->left, val);

        return n ? n : searchWrongNodes(node->right, val);
    }

    void inorder(Node* node) {
        if(!node) return;

        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }

    Node* minValueNode(Node* node) {
        Node* curr = node;
        while(curr->left) {
            curr = curr->left;
        }
        return curr;
    }

    Node* deleteNode(Node* node, int val) {
        if(!node) return node;

        if(val < node->val) {
            node->left = deleteNode(node, val);
        } else if(val > node->val) {
            node->right = deleteNode(node->right, val);
        } else {
            if(!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else if(!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->val = temp->val;
            node->right = deleteNode(node->right, temp->val);
        }
        return node;
    }

    void storeInArray(Node* node, vector<int>& arr) {
        if(!node) return;

        storeInArray(node->left, arr);
        arr.push_back(node->val);
        storeInArray(node->right, arr);
    }

    void destroyTree(Node* node) {
        if(!node) return;
        
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    public:
        BinarySearchTree() : root(nullptr) {}

        void insert(int val) {
            root = insert(root, val);
        }

        Node* search(int val) {
            return search(root, val);
        }

        void recoverBST() {
            vector<int> bstInArray;
            storeInArray(root, bstInArray);

            vector<int> temp(bstInArray);
            sort(temp.begin(), temp.end());

            for(int i = 0; i < bstInArray.size(); ++i) {
                if(bstInArray[i] != temp[i]) {
                    Node* node1 = searchWrongNodes(root, bstInArray[i]);
                    Node* node2 = searchWrongNodes(root, temp[i]);
                    swap(node1->val, node2->val);
                    return;
                }
            }
        }

        void print() {
            inorder(root);
            cout << endl;
        }

        void deleteNode(int val) {
            root = deleteNode(root, val);
        }

        ~BinarySearchTree() {
            destroyTree(root);
        }
};

int main() {
    BinarySearchTree bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    Node* node1 = bst.search(20);
    Node* node2 = bst.search(60);

    swap(node1->val, node2->val);

    cout << "BST with swapped nodes : ";
    bst.print();

    cout << "Recovering BST..." << endl;
    bst.recoverBST();

    cout << "Recovered BST : ";
    bst.print();

    return 0;
}
