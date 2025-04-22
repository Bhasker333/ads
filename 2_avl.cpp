#include<iostream>
using namespace std;

class AVL {
public:
    int score;       // Used as key
    int player_id;   // Extra info
    AVL *right, *left;
    int height;

    AVL() {
        score = 0;
        player_id = 0;
        right = NULL;
        left = NULL;
        height = 1;
    }

    AVL(int id, int s) {
        player_id = id;
        score = s;
        right = NULL;
        left = NULL;
        height = 1;
    }
};

int getHeight(AVL *root) {
    if (root == NULL)
        return 0;
    return root->height;
}

int getBalanceFactor(AVL *root) {
    if (root == NULL)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

AVL* rightRotation(AVL *y) {
    AVL *x = y->left;
    AVL *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVL* leftRotation(AVL *y) {
    AVL *x = y->right;
    AVL *t2 = x->left;

    x->left = y;
    y->right = t2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// ------- Keep Original Insert Logic ---------
AVL* insert(AVL *node, int score, int player_id) {
    if (node == NULL)
        return new AVL(player_id, score);

    if (score < node->score)
        node->left = insert(node->left, score, player_id);
    else if (score > node->score)
        node->right = insert(node->right, score, player_id);
    else
        return node; // No duplicates based on score

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int bf = getBalanceFactor(node);

    if (bf > 1 && score < node->left->score)
        return rightRotation(node);

    if (bf < -1 && score > node->right->score)
        return leftRotation(node);

    if (bf > 1 && score > node->left->score) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    if (bf < -1 && score < node->right->score) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    return node;
}

// -------- Keep Original Delete Logic --------
AVL* Delete(AVL *root, int score) {
    if (root == NULL)
        return root;

    if (score < root->score) {
        root->left = Delete(root->left, score);
    } else if (score > root->score) {
        root->right = Delete(root->right, score);
    } else {
        AVL* temp;
        if (root->left != NULL) {
            temp = root->left;
        } else {
            temp = root->right;
        }
        delete root;
        return temp;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);

    if (bf > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotation(root);

    if (bf < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotation(root);

    if (bf > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    if (bf < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
}

void inorder(AVL *root) {
    if (root != NULL) {
        inorder(root->left);
        cout << "Player ID: " << root->player_id << " | Score: " << root->score << endl;
        inorder(root->right);
    }
}

int main() {
    int choice;
    AVL *root = NULL;

    do {
        cout << "\n==== Multiplayer Game Menu ====\n";
        cout << "1. Player Registration\n2. Remove Player\n3. Display Leaderboard\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                int id, score;
                cout << "Enter Player ID: ";
                cin >> id;
                cout << "Enter Player Score: ";
                cin >> score;
                root = insert(root, score, id);
                break;
            }
            case 2: {
                int score;
                cout << "Enter Score of Player to Remove: ";
                cin >> score;
                root = Delete(root, score);
                break;
            }
            case 3: {
                cout << "\n--- Leaderboard (Inorder Traversal) ---\n";
                inorder(root);
                break;
            }
            case 4: {
                cout << "Exiting...\n";
                return 0;
            }
            default: {
                cout << "Invalid choice!\n";
            }
        }

        cout << "Continue? (1 = Yes, 0 = No): ";
        cin >> choice;
    } while(choice == 1);

    return 0;
}