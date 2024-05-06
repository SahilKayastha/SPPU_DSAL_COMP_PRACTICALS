//Beginning with an empty binary search tree, Construct binary search tree by inserting the values in the order given. After constructing a binary tree - i. Insert new node, ii. Find number of nodes in longest path from root, iii. Minimum data value found in the tree, iv. Change a tree so that the roles of the left and right pointers are swapped at every node, v. Search a value

#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node* right;
    Node* left;

    Node(int val): data(val), right(nullptr), left(nullptr){}
};

class BST{
    private:
        Node* root;
    
    public:
        BST(): root(nullptr){}

        Node* insert(Node* root, int value){
            if (root == nullptr){
                return new Node(value);
            }

            if (root->data > value){
                root ->left = insert(root->left, value);
            }
            if (root->data < value){
                root ->right = insert(root->right, value);
            }
            return root;
        }

        Node* Search(Node* root, int value){
            if (root == nullptr){
                return nullptr;
            }

            if (root->data == value){
                return root;
            } else if(value < root->data){
                return Search(root->left, value);
            } else{
                return Search(root->right, value);
            }
        }

        int findMin(Node* root){
            while(root->left != nullptr){
                root = root->left;
            }

            return root->data;
        }

        void PrintInorder(Node* root){
            if (root == nullptr){
                return;
            }

            PrintInorder(root->left);
            cout<<root->data<<" -> ";
            PrintInorder(root->right); 
        }

};

int main(){
    BST bst;
    Node* root = nullptr;
    int choice;
    do{
        cout<<"1.insert"<<endl;
        cout<<"2.s"<<endl;
        cout<<"3.iFind"<<endl;
        cout<<"4.display"<<endl;
        cout<<"exit"<<endl;
        cout<<"Eneter choice: ";
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
                cout<<"Enter data: ";
                cin>>x;
                if(bst.Search(root,x)){
                    cout<<"Node found at "<<bst.Search(root,x);
                }else{
                    cout<<"not found";
                }
                break;
            
            case 3:
                cout<<"min value : "<<bst.findMin(root);
                break;

            case 4:
                bst.PrintInorder(root);
                break;
        }
    }while(choice!=5);

    return 0 ;
}
