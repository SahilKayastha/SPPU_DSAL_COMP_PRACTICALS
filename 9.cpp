//A Dictionary stores keywords & its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry. Provide facility to display whole data sorted in ascending/ Descending order. Also find how many maximum comparisons may require for finding any keyword. Use Height balance tree and find the complexity for finding a keyword

#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    string key;
    string value;
    int height;
    Node* left;
    Node* right;

    Node(string k, string v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

class Dictionary {
private:
    Node* root;

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    Node* rotateLeft(Node* p) {
        Node* q = p->right;
        Node* T2 = q->left;

        q->left = p;
        p->right = T2;

        p->height = max(height(p->left), height(p->right)) + 1;
        q->height = max(height(q->left), height(q->right)) + 1;

        return q;
    }

    Node* rotateRight(Node* p) {
        Node* q = p->left;
        Node* T3 = q->right;

        q->right = p;
        p->left = T3;

        p->height = max(height(p->left), height(p->right)) + 1;
        q->height = max(height(q->left), height(q->right)) + 1;

        return q;
    }

    Node* insert(Node* node, string key, string value) {
        if (node == nullptr) {
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            node->value = value;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }

        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }

        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* remove(Node* node, string key) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }

            node->key = temp->key;
            node->value = temp->value;

            node->right = remove(node->right, temp->key);
        }

        if (node == nullptr) {
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void display(Node* node, bool isAscending) {
        if (node == nullptr) {
            return;
        }

        if (isAscending) {
            display(node->left, isAscending);
            cout << node->key << ": " << node->value << endl;
            display(node->right, isAscending);
        } else {
            display(node->right, isAscending);
            cout << node->key << ": " << node->value << endl;
            display(node->left, isAscending);
        }
    }

public:
    Dictionary() : root(nullptr) {}

    void addEntry(string key, string value) {
        root = insert(root, key, value);
    }

    void removeEntry(string key) {
        root = remove(root, key);
    }

    void displayAscending() {
        cout << "Displaying data in ascending order:" << endl;
        display(root, true);
    }

    void displayDescending() {
        cout << "Displaying data in descending order:" << endl;
        display(root, false);
    }
};

int main() {
    Dictionary dictionary;

    dictionary.addEntry("apple", "a fruit");
    dictionary.addEntry("banana", "a fruit");
    dictionary.addEntry("carrot", "a vegetable");

    cout << "After adding entries:" << endl;
    dictionary.displayAscending();
    dictionary.displayDescending();

    dictionary.removeEntry("banana");

    cout << "After removing 'banana':" << endl;
    dictionary.displayAscending();
    dictionary.displayDescending();

    return 0;
}
