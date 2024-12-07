#include <iostream>

using namespace std;

class BinarySearchTree {
    struct Node {
        int val;
        Node* left;
        Node* right;

        Node(int val = 0, Node* left = nullptr, Node* right = nullptr) : val(val), left(left), right(right) {}
    };

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

    Node* constructBalancedBST(int arr[], int low, int high) {
        if(low > high) return nullptr;

        int mid = low + (high - low) / 2;

        Node* node = new Node(arr[mid]);

        node->left = constructBalancedBST(arr, low, mid - 1);
        node->right = constructBalancedBST(arr, mid + 1, high);

        return node;
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

        void constructBalancedBST(int arr[], int size) {
            root = constructBalancedBST(arr, 0, size - 1);
        }

        Node* search(int val) {
            return search(root, val);
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
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int size = sizeof(arr) / sizeof(arr[0]);

    BinarySearchTree bst;
    bst.constructBalancedBST(arr, size);
    bst.print();

    return 0;
}
