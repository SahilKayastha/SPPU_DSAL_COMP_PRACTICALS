// A Dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry. Provide facility to display whole data sorted in ascending/ Descending order. Also find how many maximum comparisons may require for finding any keyword. Use Binary Search Tree for implementation
#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string key;
    string mean;
    Node *left;
    Node *right;

    Node(string key, string mean) : key(key), mean(mean), left(nullptr), right(nullptr) {}
};

class Dictionary
{
private:
    Node *root;
    int maxComparisons; // To store the maximum comparisons made during search

public:
    Dictionary() : root(nullptr), maxComparisons(0) {}

    Node *insert(Node *root, string keyword, string meaning)
    {
        if (root == nullptr)
        {
            return new Node(keyword, meaning);
        }

        if (keyword < root->key)
        {
            root->left = insert(root->left, keyword, meaning);
        }
        else if (keyword > root->key)
        {
            root->right = insert(root->right, keyword, meaning);
        }

        return root;
    }

    Node *search(Node *root, string toSearch)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        maxComparisons++; // Increment comparisons made

        if (toSearch == root->key)
        {
            return root;
        }
        else if (toSearch < root->key)
        {
            return search(root->left, toSearch);
        }
        else
        {
            return search(root->right, toSearch);
        }
    }

    void update(Node *root, string keyword, string newMeaning)
    {
        Node *node = search(root, keyword);
        if (node != nullptr)
        {
            node->mean = newMeaning;
            cout << "Meaning updated successfully." << endl;
        }
        else
        {
            cout << "Keyword not found in the dictionary." << endl;
        }
    }

    Node *findMin(Node *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    Node *deleteNode(Node *root, string toDelete)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        if (toDelete < root->key)
        {
            root->left = deleteNode(root->left, toDelete);
        }
        else if (toDelete > root->key)
        {
            root->right = deleteNode(root->right, toDelete);
        }
        else
        {
            if (root->left == nullptr)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }
            Node *temp = findMin(root->right);
            root->key = temp->key;
            root->mean = temp->mean;
            root->right = deleteNode(root->right, temp->key);
        }
        return root;
    }

    void inorder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        inorder(root->left);
        cout << root->key << " = " << root->mean << "   ";
        inorder(root->right);
    }

    void printSorted(Node *root, bool ascending)
    {
        if (root == nullptr)
            return;

        if (ascending)
        {
            printSorted(root->left, ascending);
            cout << root->key << " = " << root->mean << "   ";
            printSorted(root->right, ascending);
        }
        else
        {
            printSorted(root->right, ascending);
            cout << root->key << " = " << root->mean << "   ";
            printSorted(root->left, ascending);
        }
    }

    int getMaxComparisons()
    {
        return maxComparisons;
    }
};

int main()
{
    Dictionary dict;
    Node *root = nullptr; // Initialize root variable

    int choice;
    cout << "1.Insert Node" << endl;
    cout << "2.Search Key" << endl;
    cout << "3.Update value" << endl;
    cout << "4.Print Dictionary in Ascending Order" << endl;
    cout << "5.Print Dictionary in Descending Order" << endl;
    cout << "6.Find Max Comparisons for Search" << endl;
    cout << "7.Exit" << endl;

    do
    {
        cout << "Enter your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "-------Inserting Word in Dictionary-------" << endl;
            int nodes;
            cout << "How many nodes you want to insert?" << endl;
            cin >> nodes;
            for (int i = 0; i < nodes; i++)
            {
                string word, meaning;
                cout << "Enter The Keyword: ";
                cin >> word;
                cout << "Enter its Meaning: ";
                cin >> meaning;
                root = dict.insert(root, word, meaning);
            }
            break;
        }
        case 2:
        {
            cout << "-------Search the Given Word-------" << endl;
            string word;
            cout << "Enter The Keyword: ";
            cin >> word;
            if (dict.search(root, word) != nullptr)
            {
                cout << "Key present in Dictionary" << endl;
            }
            else
            {
                cout << "Key is not Present in Dictionary" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "-------Updating Meaning of Word-------" << endl;
            string word, newMeaning;
            cout << "Enter The Keyword to update: ";
            cin >> word;
            cout << "Enter New Meaning: ";
            cin >> newMeaning;
            dict.update(root, word, newMeaning);
            break;
        }
        case 4:
        {
            cout << "-------Dictionary in Ascending Order-------" << endl;
            dict.printSorted(root, true);
            cout << endl;
            break;
        }
        case 5:
        {
            cout << "-------Dictionary in Descending Order-------" << endl;
            dict.printSorted(root, false);
            cout << endl;
            break;
        }
        case 6:
        {
            cout << "-------Max Comparisons for Search-------" << endl;
            string word;
            cout << "Enter The Keyword to search: ";
            cin >> word;
            dict.search(root, word); // Search to update maxComparisons
            cout << "Maximum comparisons required: " << dict.getMaxComparisons() << endl;
            break;
        }
        case 7:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}

