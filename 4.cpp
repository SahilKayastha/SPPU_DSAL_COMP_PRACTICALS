//Beginning with an empty binary search tree, Construct binary search tree by inserting the values in the order given. After constructing a binary tree - i. Insert new node, ii. Find number of nodes in longest path from root, iii. Minimum data value found in the tree, iv. Change a tree so that the roles of the left and right pointers are swapped at every node, v. Search a value
#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val): data(val), left(nullptr), right(nullptr){};
};

class BST{
    private:
        Node* root;

    public:

        Node* insert(Node*root, int value){
            if (root == nullptr){
                return new Node(value);
            }

            if(root->data > value){
                root->left = insert(root->left, value);
            } else{
                root->right = insert(root->right, value);
            }

            return root;
        }

        Node* Search(Node* root, int key){
            if(root == nullptr){
                return nullptr;
            }

            if (root->data == key){
                return root;
            } else if (root->data < key){
                return Search(root->right, key);
            } else {
                return Search(root->left, key);
            }
            
        }

        Node* findMin(Node *root){
            if(root == nullptr)
                return nullptr;
            while (root->left != nullptr)
            {
                root = root->left;
            }
            return root;
        }

        int longestPath(Node* root){
            if(root == nullptr)
                return 0;
            return 1 + max(longestPath(root->left), longestPath(root->right));
        }

        void swapChildren(Node* root){
            if(root == nullptr)
                return;
            Node* temp = root->left;
            root->left = root->right;
            root->right = temp;
            swapChildren(root->left);
            swapChildren(root->right);
        }

        void Inorder(Node*root){
            if (root == nullptr){
                return;
            }

            Inorder(root->left);
            cout<<root->data<<" -> ";
            Inorder(root->right);
        }

        Node* deleteNode(Node* root, int key) {
            if (root == nullptr) return root;
            if (key < root->data) {
                root->left = deleteNode(root->left, key);
            } else if (key > root->data) {
                root->right = deleteNode(root->right, key);
            } else {
                if (root->left == nullptr) {
                    Node* temp = root->right;
                    delete root;
                    return temp;
                } else if (root->right == nullptr) {
                    Node* temp = root->left;
                    delete root;
                    return temp;
                }
                Node* temp = findMin(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
            return root;
        }
};

int main(){
    BST bst;
    Node* root = nullptr;
    int choice;
    do{
        cout<<"1. Insert"<<endl;
        cout<<"2. Search"<<endl;
        cout<<"3. Find Minimum"<<endl;
        cout<<"4. Swap Children"<<endl;
        cout<<"5. Delete Node"<<endl;
        cout<<"6. Display"<<endl;
        cout<<"7. Exit"<<endl;
        cout<<"Enter choice: ";
        cin>> choice;

        switch(choice){
            case 1:
                int y;
                cout << "Enter data: ";
                cin >> y;
                root = bst.insert(root, y);
                break;
            case 2: 
                int x;
                cout<<"Enter data to search: ";
                cin>>x;
                if(bst.Search(root,x)){
                    cout<<"Node found";
                }else{
                    cout<<"Node not found";
                }
                break;
            case 3:
                if(root != nullptr) {
                    cout<<"Minimum value : "<<bst.findMin(root)->data<<endl;
                } else {
                    cout<<"Tree is empty"<<endl;
                }
                break;
            case 4:
                bst.swapChildren(root);
                cout<<"Children swapped successfully"<<endl;
                break;
            case 5:
                int delVal;
                cout<<"Enter value to delete: ";
                cin>>delVal;
                root = bst.deleteNode(root, delVal);
                cout<<"Node deleted successfully"<<endl;
                break;
            case 6:
                cout<<"Inorder Traversal: ";
                bst.Inorder(root);
                cout<<endl;
                break;
            case 7:
                cout<<"Exiting...";
                break;
            default:
                cout<<"Invalid choice"<<endl;
        }
    } while(choice != 7);
    return 0;
}
