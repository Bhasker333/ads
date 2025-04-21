/*a. Implement B-Tree of order three and perform following operations: 
1. Insert 
2. Level order display 
3. Delete */

#include <iostream>
using namespace std;

const int ORDER = 3; // B-Tree of order 3 (max 2 keys per node)

class BTreeNode {
public:
    int keys[ORDER - 1];              // Store keys (max 2 keys in order 3)
    BTreeNode* children[ORDER];       // Store child pointers (max 3 children)
    int numKeys;
    bool isLeaf;

    BTreeNode(bool leaf) {
        isLeaf = leaf;
        numKeys = 0;
        for (int i = 0; i < ORDER; i++)
            children[i] = nullptr;
    }
};

class BTree {
private:
    BTreeNode* root;

    void splitChild(BTreeNode* parent, int i, BTreeNode* fullChild) {
        BTreeNode* newChild = new BTreeNode(fullChild->isLeaf);
        newChild->numKeys = 1;
        newChild->keys[0] = fullChild->keys[2];

        if (!fullChild->isLeaf) {
            newChild->children[0] = fullChild->children[2];
            newChild->children[1] = fullChild->children[3];
        }

        fullChild->numKeys = 1;

        for (int j = parent->numKeys; j >= i + 1; j--)
            parent->children[j + 1] = parent->children[j];
        parent->children[i + 1] = newChild;

        for (int j = parent->numKeys - 1; j >= i; j--)
            parent->keys[j + 1] = parent->keys[j];
        parent->keys[i] = fullChild->keys[1];
        parent->numKeys++;
    }

    void insertNonFull(BTreeNode* node, int key) {
        int i = node->numKeys - 1;

        if (node->isLeaf) {
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
            node->numKeys++;
        } else {
            while (i >= 0 && key < node->keys[i])
                i--;

            if (node->children[i + 1]->numKeys == ORDER - 1) {
                splitChild(node, i + 1, node->children[i + 1]);
                if (key > node->keys[i + 1])
                    i++;
            }
            insertNonFull(node->children[i + 1], key);
        }
    }

    void levelOrderTraversal(BTreeNode* root) {
        if (!root) return;

        BTreeNode* queue[100];
        int front = 0, rear = 0;
        queue[rear++] = root;

        while (front < rear) {
            BTreeNode* temp = queue[front++];
            cout << "[ ";
            for (int i = 0; i < temp->numKeys; i++)
                cout << temp->keys[i] << " ";
            cout << "] ";

            if (!temp->isLeaf) {
                for (int i = 0; i <= temp->numKeys; i++)
                    queue[rear++] = temp->children[i];
            }
        }
        cout << endl;
    }

    void merge(BTreeNode* parent, int index) {
        BTreeNode* child = parent->children[index];
        BTreeNode* sibling = parent->children[index + 1];

        child->keys[1] = parent->keys[index];
        child->keys[2] = sibling->keys[0];

        if (!child->isLeaf) {
            child->children[2] = sibling->children[0];
            child->children[3] = sibling->children[1];
        }

        for (int i = index; i < parent->numKeys - 1; i++)
            parent->keys[i] = parent->keys[i + 1];
        for (int i = index + 1; i < parent->numKeys; i++)
            parent->children[i] = parent->children[i + 1];

        child->numKeys = 2;
        parent->numKeys--;

        delete sibling;
    }

    void remove(BTreeNode* node, int key) {
        int idx = 0;
        while (idx < node->numKeys && key > node->keys[idx])
            idx++;

        if (idx < node->numKeys && node->keys[idx] == key) {
            if (node->isLeaf) {
                for (int i = idx; i < node->numKeys - 1; i++)
                    node->keys[i] = node->keys[i + 1];
                node->numKeys--;
            } else {
                node->keys[idx] = node->children[idx]->keys[node->children[idx]->numKeys - 1];
                remove(node->children[idx], node->keys[idx]);
            }
        } else {
            if (node->children[idx]->numKeys == 1) {
                if (idx != 0 && node->children[idx - 1]->numKeys > 1) {
                    node->children[idx]->keys[0] = node->keys[idx - 1];
                    node->keys[idx - 1] = node->children[idx - 1]->keys[node->children[idx - 1]->numKeys - 1];
                    node->children[idx]->numKeys++;
                    node->children[idx - 1]->numKeys--;
                } else if (idx != node->numKeys && node->children[idx + 1]->numKeys > 1) {
                    node->children[idx]->keys[1] = node->keys[idx];
                    node->keys[idx] = node->children[idx + 1]->keys[0];
                    node->children[idx]->numKeys++;
                    node->children[idx + 1]->numKeys--;
                } else {
                    merge(node, idx);
                }
            }

            remove(node->children[idx], key);
        }
    }

public:
    BTree() {
        root = nullptr;
    }

    void insert(int key) {
        if (!root) {
            root = new BTreeNode(true);
            root->keys[0] = key;
            root->numKeys = 1;
        } else {
            if (root->numKeys == ORDER - 1) {
                BTreeNode* newRoot = new BTreeNode(false);
                newRoot->children[0] = root;
                splitChild(newRoot, 0, root);
                root = newRoot;
            }
            insertNonFull(root, key);
        }
    }

    void deleteKey(int key) {
        if (!root) return;

        remove(root, key);

        if (root->numKeys == 0) {
            BTreeNode* temp = root;
            root = root->children[0];
            delete temp;
        }
    }

    void display() {
        cout << "B-Tree Level Order: ";
        levelOrderTraversal(root);
    }
};

int main() {
    BTree tree;
    int choice, key;

    do {
        cout << "\n1. Insert\n2. Display Level Order\n3. Delete\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                tree.insert(key);
                break;
            case 2:
                tree.display();
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                tree.deleteKey(key);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
