#include<iostream>
#include<string>
using namespace std;

struct TreeNode {
    string key;
    string value;
    TreeNode *left;
    TreeNode *right;

    TreeNode() {
        key = "";
        value = "";
        left = NULL;
        right = NULL;
    }

    TreeNode(string k, string v) {
        key = k;
        value = v;
        left = NULL;
        right = NULL;
    }
};

// Insert a node into BST (no duplicate keys allowed)
TreeNode* insert(TreeNode* node, string key, string value) {
    if (node == NULL) {
        return new TreeNode(key, value);
    }
    if (node->key == key) {
        cout << "Duplicate key. Insertion not allowed.\n";
        return node;
    }
    if (key < node->key) {
        node->left = insert(node->left, key, value);
    } else {
        node->right = insert(node->right, key, value);
    }
    return node;
}

// Search for a key
TreeNode* search(TreeNode* root, string key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

// Inorder traversal
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " : " << root->value << endl;
        inorder(root->right);
    }
}

// Preorder traversal
void preorder(TreeNode* root) {
    if (root != NULL) {
        cout << root->key << " : " << root->value << endl;
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal
void postorder(TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " : " << root->value << endl;
    }
}

// Delete a node
TreeNode* Delete(TreeNode* root, string key) {
    if (root == NULL) return root;

    if (key < root->key) {
        root->left = Delete(root->left, key);
    } else if (key > root->key) {
        root->right = Delete(root->right, key);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        } else {
            TreeNode* succ = root->right;
            while (succ->left != NULL)
                succ = succ->left;
            root->key = succ->key;
            root->value = succ->value;
            root->right = Delete(root->right, succ->key);
        }
    }
    return root;
}

// Mirror the dictionary
void mirror(TreeNode* root) {
    if (root == NULL) return;
    swap(root->left, root->right);
    mirror(root->left);
    mirror(root->right);
}

// Copy dictionary (Deep Copy)
TreeNode* copy(TreeNode* root) {
    if (root == NULL) return NULL;
    TreeNode* newRoot = new TreeNode(root->key, root->value);
    newRoot->left = copy(root->left);
    newRoot->right = copy(root->right);
    return newRoot;
}

// Level-wise display (simple recursive approximation)
void display_level(TreeNode* root) {
    if (root == NULL) return;

    cout << root->key << " : " << root->value << endl;
    if (root->left != NULL) {
        display_level(root->left);
    }
    if (root->right != NULL) {
        display_level(root->right);
    }
}

int main() {
    TreeNode* root = NULL;
    int choice;
    string key, value;

    do {
        cout << "1. Insert word\n2. Delete word\n3. Search word\n4. Display (Inorder)\n5. Mirror dictionary\n6. Copy dictionary\n7. Level-wise display\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter word: ";
                cin >> key;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, value);
                root = insert(root, key, value);
                break;
            case 2:
                cout << "Enter word to delete: ";
                cin >> key;
                root = Delete(root, key);
                cout << "Deleted (if existed).\n";
                break;
            case 3:
                cout << "Enter word to search: ";
                cin >> key;
                {
                    TreeNode* found = search(root, key);
                    if (found) {
                        cout << "Found: " << found->key << " : " << found->value << endl;
                    } else {
                        cout << "Word not found.\n";
                    }
                }
                break;
            case 4:
                inorder(root);
                break;
            case 5:
                mirror(root);
                break;
            case 6: {
                TreeNode* copyRoot = copy(root);
                inorder(copyRoot);
                break;
            }
            case 7:
                display_level(root);
                break;
            case 8:
                break;
            default:
        }
    } while (choice != 8);

    return 0;
}
