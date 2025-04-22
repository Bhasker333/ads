#include<iostream>
using namespace std;

class tree {
public:
    string key;  
    string value;  
    tree* left;
    tree* right;

    tree() {
        key = "";
        value = "";
        left = NULL;
        right = NULL;
    }

    tree(string k, string v) { 
        key = k;
        value = v;
        left = NULL;
        right = NULL;
    }
};

tree* insert(tree* node, string key, string value) {
    if (node == NULL) {
        return new tree(key, value);
    }
    if (node->key == key) {
        node->value = value;  
        return node;
    }
    if (node->key > key) {
        node->left = insert(node->left, key, value);  
    } else {
        node->right = insert(node->right, key, value);  
    }
    return node;
}


tree* Delete(tree* root, string key) {
    if (root == NULL) {
        return root;  
    }

    if (root->key > key) {
        root->left = Delete(root->left, key);  
    } else if (root->key < key) {
        root->right = Delete(root->right, key); 
    } else {
        
        tree* temp;
        if (root->left == NULL) {
            temp = root->right;  
            delete root;
            return temp;
        } else if (root->right == NULL) {
            temp = root->left;   
            delete root;
            return temp;
        }

        // Node with two children: get the inorder successor
        temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }
        root->key = temp->key;  // Copy the inorder successor's key to this node
        root->value = temp->value;  // Copy the inorder successor's value
        root->right = Delete(root->right, temp->key); // Delete the inorder successor
    }
    return root;
}


void inorder(tree* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << "Key: " << root->key << ", Value: " << root->value << " | ";
        inorder(root->right);
    }
}


tree* search(tree* root, string key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (root->key > key) {
        return search(root->left, key);  
    } else {
        return search(root->right, key); 
    }
}

void display_level(tree* root) {
    if (root == NULL) {
        return;
    }
    cout << root->key << " ";  

    if (root->left != NULL) {
        cout << root->left->key << " ";  
    }
    if (root->right != NULL) {
        cout << root->right->key << " ";  
    }

    if (root->left != NULL) {
        display_level(root->left->left);  
        display_level(root->left->right);  
    }
    if (root->right != NULL) {
        display_level(root->right->left);  
        display_level(root->right->right);  
    }
}

int main() {
    tree* root = NULL;
    int choice;
    do {
        cout << "1.insert\n 2.inorderdisplay\n 3.searching\n 4.delete\n 5.levelwisedisplay\n 6.exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string key, value;
                cout << "Enter key to insert: ";
                cin >> key;
                cout << "Enter value associated with the key: ";
                cin >> value;
                root = insert(root, key, value); 
                break;
            }
            case 2: {
                cout << "Displaying inorder traversal: ";
                inorder(root);
                cout << endl;
                break;
            }
            case 3: {
                string key;
                cout << "Enter key to search: ";
                cin >> key;
                tree* found = search(root, key);
                if (found != NULL) {
                    cout << "Node found: Key = " << found->key << ", Value = " << found->value << endl;
                } else {
                    cout << "Node not found" << endl;
                }
                break;
            }
            case 4: {
                string key;
                cout << "Enter key to delete: ";
                cin >> key;
                root = Delete(root, key);  
                cout << "Tree after deletion: ";
                inorder(root);
                cout << endl;
                break;
            }
            case 5: {
                cout << "Level-wise display: ";
                display_level(root);
                cout << endl;
                break;
            }
            case 6: {
                cout << "Exiting...\n";
                break;
            }
        }
        cout << "Do you want to continue (1 for yes, any other key for no): ";
        cin >> choice;
    } while (choice == 1);

    return 0;
}