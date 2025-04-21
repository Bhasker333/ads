#include <iostream>
using namespace std;

struct Player {
    int id;
    int score;
};

struct AVLNode {
    Player player;
    AVLNode *left, *right;
    int height;
};

// Utility to create a new node
AVLNode* createNode(int id, int score) {
    AVLNode* node = new AVLNode;
    node->player.id = id;
    node->player.score = score;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int getHeight(AVLNode* root) {
    return root ? root->height : 0;
}

int getBalanceFactor(AVLNode* root) {
    return root ? getHeight(root->left) - getHeight(root->right) : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Right Rotation
AVLNode* rightRotation(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left Rotation
AVLNode* leftRotation(AVLNode* y) {
    AVLNode* x = y->right;
    AVLNode* t2 = x->left;

    x->left = y;
    y->right = t2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Compare players for AVL ordering: sorted by score, then ID as tiebreaker
bool isLess(Player a, Player b) {
    return (a.score < b.score) || (a.score == b.score && a.id < b.id);
}

bool isEqual(Player a, Player b) {
    return a.score == b.score && a.id == b.id;
}

// Insert
AVLNode* insert(AVLNode* root, int id, int score) {
    if (!root)
        return createNode(id, score);

    Player newPlayer = {id, score};

    if (isLess(newPlayer, root->player))
        root->left = insert(root->left, id, score);
    else if (isLess(root->player, newPlayer))
        root->right = insert(root->right, id, score);
    else
        return root; // Duplicate player (same id and score)

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);

    if (bf > 1 && isLess(newPlayer, root->left->player))
        return rightRotation(root);
    if (bf < -1 && isLess(root->right->player, newPlayer))
        return leftRotation(root);
    if (bf > 1 && isLess(root->left->player, newPlayer)) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    if (bf < -1 && isLess(newPlayer, root->right->player)) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
}

// Find minimum value node in right subtree
AVLNode* findMin(AVLNode* root) {
    while (root->left)
        root = root->left;
    return root;
}

// Delete
AVLNode* Delete(AVLNode* root, int id, int score) {
    if (!root)
        return root;

    Player target = {id, score};

    if (isLess(target, root->player))
        root->left = Delete(root->left, id, score);
    else if (isLess(root->player, target))
        root->right = Delete(root->right, id, score);
    else {
        // Node found
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            AVLNode* temp = findMin(root->right);
            root->player = temp->player;
            root->right = Delete(root->right, temp->player.id, temp->player.score);
        }
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

// Inorder display
void inorder(AVLNode* root) {
    if (root) {
        inorder(root->left);
        cout << "Player ID: " << root->player.id << " | Score: " << root->player.score << endl;
        inorder(root->right);
    }
}

// Main Menu
int main() {
    AVLNode* root = NULL;
    int choice, id, score;

    do {
        cout << "\n1. Register Player\n2. Remove Player\n3. Display Leaderboard\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Player ID: ";
                cin >> id;
                cout << "Enter Score: ";
                cin >> score;
                root = insert(root, id, score);
                break;

            case 2:
                cout << "Enter Player ID to remove: ";
                cin >> id;
                cout << "Enter Score of player: ";
                cin >> score;
                root = Delete(root, id, score);
                break;

            case 3:
                cout << "\nLeaderboard (Sorted by Score):\n";
                inorder(root);
                break;

            case 4:
                cout << "Exiting Leaderboard System.\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
        }

        cout << "Continue? (1 for Yes / 0 for No): ";
        cin >> choice;

    } while (choice == 1);

    return 0;
}
