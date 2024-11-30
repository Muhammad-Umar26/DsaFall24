#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

struct Record {
    int id, age;
    string name;

    Record() {}
    Record(int id, string name, int age) : id(id), name(name), age(age) {}

    void printDetails() {
        cout << "Id : " << id << endl << "Name : " << name << endl << "Age : " << age << endl;
    }
};

class BinarySearchTree {
    struct Node {
        Record record;
        Node* left;
        Node* right;

        Node(Record record, Node* left = nullptr, Node* right = nullptr) : record(record), left(left), right(right) {}
    };

    Node* table;

    Node* insert(Node* node, Record& record) {
        if(!node) {
            return new Node(record);
        }

        if(record.id == node->record.id) return node;

        if(record.id < node->record.id) {
            node->left = insert(node->left, record);
        } else {
            node->right = insert(node->right, record);
        }

        return node;
    }

    Node* search(Node* node, int id) {
        if(!node || id == node->record.id) {
            return node;
        }

        if(id < node->record.id) {
            return search(node->left, id);
        }

        return search(node->right, id);
    }

    Node* findMinNode(Node* node) {
        Node* curr = node;
        while(curr->left) {
            curr = curr->left;
        }
        return curr;
    }

    Node* deleteNode(Node* node, int id) {
        if(!node) return node;

        if(id < node->record.id) {
            node->left = deleteNode(node, id);
        } else if(id > node->record.id) {
            node->right = deleteNode(node->right, id);
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

            Node* temp = findMinNode(node->right);
            node->record = temp->record;
            node->right = deleteNode(node->right, temp->record.id);
        }
        return node;
    }

    void inorder(Node* node) {
        if(!node) return;

        inorder(node->left);
        node->record.printDetails();
        inorder(node->right);
    }

    void destroyTree(Node* node) {
        if (!node) return;

        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    public:
        BinarySearchTree() : table(nullptr) {}

        void insert(Record& record) {
            table = insert(table, record);
        }

        string search(int id) {
            return search(table, id)->record.name;
        }

        void traverse() {
            inorder(table);
        }

        void deleteNode(int id) {
            table = deleteNode(table, id);
        }

        ~BinarySearchTree() {
            destroyTree(table);
        }
};

class AVLTree {
    struct Node {
        Record record;
        int height;
        Node* left;
        Node* right;

        Node(Record record, Node* left = nullptr, Node* right = nullptr, int height = 1) : record(record), left(left), right(right), height(height) {}
    };

    Node* table;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* LL_Rotation(Node* node) {
        Node* child = node->left;
        node->left = child->right;
        child->right = node;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        child->height = max(getHeight(child->left), getHeight(child->right)) + 1;

        return child;
    }

    Node* RR_Rotation(Node* node) {
        Node* child = node->right;
        node->right = child->left;
        child->left = node;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        child->height = max(getHeight(child->left), getHeight(child->right)) + 1;

        return child;
    }

    Node* insert(Node* node, Record& record) {
        if(!node) {
            return new Node(record);
        }

        if(record.id < node->record.id) {
            node->left = insert(node->left, record);
        } else if(record.id > node->record.id) {
            node->right = insert(node->right, record);
        } else {
            return node;
        }

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = getBalance(node);

        if(balance > 1) {
            if(record.id > node->left->record.id) {
                node->left = RR_Rotation(node->left);
            }
            return LL_Rotation(node);
        }

        if(balance < -1) {
            if(record.id < node->right->record.id) {
                node->right = LL_Rotation(node->right);
            }
            return RR_Rotation(node);
        }

        return node;
    }

    Node* search(Node* node, int id) {
        if(!node || id == node->record.id) {
            return node;
        }

        if(id < node->record.id) {
            return search(node->left, id);
        }

        return search(node->right, id);
    }

    Node* findMinNode(Node* node) {
        Node* curr = node;
        while(curr && curr->left) {
            curr = curr->left;
        }
        return curr;
    }

    Node* deleteNode(Node* node, int id) {
        if(!node) return nullptr;

        if(id < node->record.id) {
            node->left = deleteNode(node->left, id);
        } else if(id > node->record.id) {
            node->right = deleteNode(node->right, id); 
        } else {
            if(!node->left) {
                Node* temp = node->right;
                delete node;
                return node->right;
            }

            if(!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMinNode(node->right);
            node->record = temp->record;
            node->right = deleteNode(node->right, temp->record.id);
        }

        if(!node) return nullptr;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = getBalance(node);

        if(balance > 1) {
            if(getBalance(node->left) < 0) {
                node->left = RR_Rotation(node->left);
            }
            return LL_Rotation(node);
        }

        if(balance < -1) {
            if(getBalance(node->right) > 0) {
                node->right = LL_Rotation(node->right);
            }
            return RR_Rotation(node);
        }

        return node;
    }

    void inorder(Node* node) {
        if(!node) return;

        inorder(node->left);
        node->record.printDetails();
        inorder(node->right);
    }

    void destroyTree(Node* node) {
        if (!node) return;

        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    public:
        AVLTree() : table(nullptr) {}

        void insert(Record& record) {
            table = insert(table, record);
        }

        string search(int id) {
            return search(table, id)->record.name;
        }

        void deleteNode(int val) {
            table = deleteNode(table, val);
        }

        void traverse() {
            inorder(table);
            cout << endl;
        }

        ~AVLTree() {
            destroyTree(table);
        }
};

class BTree {
    struct Node {
        bool isLeaf;
        vector<Record> records;
        vector<Node*> children;

        Node(bool isLeaf) : isLeaf(isLeaf) {}
    };

    Node* table;
    int minChild;

    void splitChild(Node* parent, int i, Node* child) {
        Node* newChild = new Node(child->isLeaf);
        for(int j = 0; j < minChild - 1; ++j) {
            newChild->records.push_back(child->records[minChild + j]);
        }

        if(!child->isLeaf) {
            for(int j = 0; j < minChild; ++j) {
                newChild->children.push_back(child->children[minChild + j]);
            }
        }

        child->records.resize(minChild - 1);
        child->children.resize(minChild);

        parent->children.insert(parent->children.begin() + i + 1, newChild);
        parent->records.insert(parent->records.begin() + i, child->records[minChild - 1]);
    }

    void insertNonFull(Node* node, const Record& record) {
        int i = node->records.size() - 1;
        if(node->isLeaf) {
            node->records.push_back(record);
            while(i >= 0 && node->records[i].id > record.id) {
                node->records[i + 1] = node->records[i];
                --i;
            }
            node->records[i + 1] = record;
        } else {
            while(i >= 0 && node->records[i].id > record.id) {
                --i;
            }

            if(node->children[i + 1]->records.size() == 2 * minChild - 1) {
                splitChild(node, i + 1, node->children[i + 1]);
                if(node->records[i + 1].id < record.id) {
                    ++i;
                }
            }
            insertNonFull(node->children[i + 1], record);
        }
    }

    string search(Node* node, int id) {
        if(!node) return "";
        int i = 0;
        while(i < node->records.size() && id > node->records[i].id) {
            ++i;
        }

        if(i < node->records.size() && id == node->records[i].id) return node->records[i].name;
    
        return search(node->children[i], id);
    }

    int findKey(Node* node, int id) {
        int idx = 0;
        while(idx < node->records.size() && node->records[idx].id < id) {
            ++idx;
        }
        return idx;
    }

    void removeNode(Node* node, int id) {
        int idx = findKey(node, id);

        if(idx < node->records.size() && node->records[idx].id == id) {
            if(node->isLeaf) {
                removeFromLeaf(node, idx);
            } else {
                removeFromNonLeaf(node, idx);
            }
        } else {
            if(node->isLeaf) return;

            bool flag = idx == node->records.size();

            if(node->children[idx]->records.size() < minChild) {
                fill(node, idx);
            }

            if(flag && idx > node->records.size()) {
                removeNode(node->children[idx - 1], id);
            } else {
                removeNode(node->children[idx], id);
            }
        }
    }

    void removeFromLeaf(Node* node, int idx) {
        node->records.erase(node->records.begin() + idx);
    }

    void removeFromNonLeaf(Node* node, int idx) {
        int id = node->records[idx].id;

        if(node->children[idx]->records.size() >= minChild) {
            Record pred = getPredecessor(node, idx);
            node->records[idx] = pred;
            removeNode(node->children[idx], pred.id);
        } else if(node->children[idx + 1]->records.size() >= minChild) {
            Record succ = getSuccessor(node, idx);
            node->records[idx] = succ;
            removeNode(node->children[idx + 1], succ.id);
        } else {
            merge(node, idx);
            removeNode(node->children[idx], id);
        }
    }

    Record getPredecessor(Node* node, int idx) {
        Node* curr = node->children[idx];
        while(!curr->isLeaf) {
            curr = curr->children.back();
        }
        return curr->records.back();
    }

    Record getSuccessor(Node* node, int idx) {
        Node* curr = node->children[idx + 1];
        while(!curr->isLeaf) {
            curr = curr->children.front();
        }
        return curr->records.front();
    }

    void fill(Node* node, int idx) {
        if(idx != 0 && node->children[idx - 1]->records.size() >= minChild) {
            borrowFromPrev(node, idx);
        } else if(idx != node->records.size() && node->children[idx + 1]->records.size() >= minChild) {
            borrowFromNext(node, idx);
        } else {
            if(idx != node->records.size()) {
                merge(node, idx);
            }
            else {
                merge(node, idx - 1);
            }
        }
    }

    void borrowFromPrev(Node* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx - 1];

        child->records.insert(child->records.begin(), node->records[idx - 1]);
        if(!child->isLeaf) {
            child->children.insert(child->children.begin(), sibling->children.back());
        }

        node->records[idx - 1] = sibling->records.back();
        sibling->records.pop_back();
        if(!sibling->isLeaf) {
            sibling->children.pop_back();
        }
    }

    void borrowFromNext(Node* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx + 1];

        child->records.push_back(node->records[idx]);
        if(!child->isLeaf) {
            child->children.push_back(sibling->children.front());
        }

        node->records[idx] = sibling->records.front();
        sibling->records.erase(sibling->records.begin());
        if(!sibling->isLeaf) {
            sibling->children.erase(sibling->children.begin());
        }
    }

    void merge(Node* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx + 1];

        child->records.push_back(node->records[idx]);
        child->records.insert(child->records.end(), sibling->records.begin(), sibling->records.end());

        if(!child->isLeaf) {
            child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
        }

        node->records.erase(node->records.begin() + idx);
        node->children.erase(node->children.begin() + idx + 1);

        delete sibling;
    }

    void traverseLevelByLevel(Node* root) const {
        if(!root) {
            cout << "Tree is empty" << endl;
            return;
        }

        queue<Node*> q;
        q.push(root);

        while(!q.empty()) {
            for(int levelSize = q.size(); levelSize; --levelSize) {
                Node* curr = q.front();
                q.pop();
                
                cout << "[ ";
                for(int i = 0; i < curr->records.size(); ++i) {
                    cout << curr->records[i].id << " ";
                }
                cout << "] ";

                if(!curr->isLeaf) {
                    for (int i = 0; i < curr->children.size(); ++i) {
                        q.push(curr->children[i]);
                    }
                }
            }
            cout << endl;
        }
    }

    void destroyTree(Node* node) {
        if (!node) return;
        for (Node* child : node->children) {
            destroyTree(child);
        }
        delete node;
    }

    public:
        BTree(int order = 3) : table(nullptr), minChild(ceil((float)order / 2)) {}

        void insert(const Record& record) {
            if(!table) {
                table = new Node(true);
                table->records.push_back(record);
            } else {
                if(table->records.size() == 2 * minChild - 1) {
                    Node* newTable = new Node(false);
                    newTable->children.push_back(table);
                    splitChild(newTable, 0, table);
                    table = newTable;
                }
                insertNonFull(table, record);
            }
        }

        string search(int id) {
            return search(table, id);
        }

        void deleteNode(int id) {
            removeNode(table, id);
            if(table && table->records.empty()) {
                Node* oldTable = table;
                table = table->isLeaf ? nullptr : table->children[0];
                delete oldTable;
            }
        }

        void traverse() const {
            traverseLevelByLevel(table);
        }

        ~BTree() {
            destroyTree(table);
        }
};

vector<Record> generateDummyData(int size) {
    vector<Record> records;
    for(int i = 0; i < size; ++i) {
        records.emplace_back(i, "Name" + to_string(i), rand() % 100 + 1);
    }
    return records;
}

int main() {
    vector<int> sizes = {1000, 10000, 50000};
    int searchCount = 20;

    for(int size : sizes) {
        cout << "---- Testing with dataset size: " << size << " ----" << endl << endl;

        vector<Record> records = generateDummyData(size);

        // Binary Search Tree
        BinarySearchTree bst;
        auto start = high_resolution_clock::now();
        for(Record& record : records) {
            bst.insert(record);
        }
        auto end = high_resolution_clock::now();
        cout << "Average BST Insert Time: " << duration_cast<nanoseconds>(end - start).count() / size << " ns" << endl;

        start = high_resolution_clock::now();
        for(int i = 0; i < searchCount; ++i) {
            bst.search(records[rand() % size].id);
        }
        end = high_resolution_clock::now();
        cout << "Average BST Search Time: " << duration_cast<nanoseconds>(end - start).count() / searchCount << " ns" << endl;

        start = high_resolution_clock::now();
        for(int i = 0; i < searchCount; ++i) {
            bst.deleteNode(records[rand() % size].id);
        }
        end = high_resolution_clock::now();
        cout << "Average BST Delete Time: " << duration_cast<nanoseconds>(end - start).count() / searchCount << " ns" << endl << endl;

        // AVL Tree
        AVLTree avl;
        start = high_resolution_clock::now();
        for(Record& record : records) {
            avl.insert(record);
        }
        end = high_resolution_clock::now();
        cout << "Average AVL Insert Time: " << duration_cast<nanoseconds>(end - start).count() / size << " ns" << endl;

        start = high_resolution_clock::now();
        for(int i = 0; i < searchCount; ++i) {
            avl.search(records[rand() % size].id);
        }
        end = high_resolution_clock::now();
        cout << "Average AVL Search Time: " << duration_cast<nanoseconds>(end - start).count() / searchCount << " ns" << endl;

        start = high_resolution_clock::now();
        for(int i = 0; i < searchCount; ++i) {
            avl.deleteNode(records[rand() % size].id);
        }
        end = high_resolution_clock::now();
        cout << "Average AVL Delete Time: " << duration_cast<nanoseconds>(end - start).count() / searchCount << " ns" << endl << endl;

        // B-Tree
        BTree btree(4);
        start = high_resolution_clock::now();
        for(Record& record : records) {
            btree.insert(record);
        }
        end = high_resolution_clock::now();
        cout << "Average B-Tree Insert Time: " << duration_cast<nanoseconds>(end - start).count() / size << " ns" << endl;

        start = high_resolution_clock::now();
        for (int i = 0; i < searchCount; ++i) {
            btree.search(records[rand() % size].id);
        }
        end = high_resolution_clock::now();
        cout << "Average B-Tree Search Time: " << duration_cast<nanoseconds>(end - start).count() / searchCount << " ns" << endl;

        start = high_resolution_clock::now();
        for (int i = 0; i < searchCount; ++i) {
            btree.deleteNode(records[rand() % size].id);
        }
        end = high_resolution_clock::now();
        cout << "Average B-Tree Delete Time: " << duration_cast<nanoseconds>(end - start).count() / searchCount << " ns" << endl << endl << endl;
    }
    
    return 0;
}
