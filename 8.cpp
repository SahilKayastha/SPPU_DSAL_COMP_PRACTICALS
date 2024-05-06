//Given sequence k = k1 <k2 < … <kn of n sorted keys, with a search probability pi for each key ki . Build the Binary search tree that has the least search cost given the access probability for each key?

#include<iostream>
#include<climits>
#define MAX_KEYS 10;
using namespace std;

class OBST {
    private:
        int p[10];           // search probabilities
        int q[10];          // failure probabilities
        int keys[10];       // keys
        int n;              // number of keys

        int root[10][10];   // root of the tree
        int cost[10][10];   // cost of the tree
        int weight[10][10]; // weight of the tree

    public:
        void acceptInput(){
            cout<<"Enter the number of keys: ";
            cin>>n;

            cout<<"Enter the keys: ";
            for (int i = 1; i <= n; i++) {
                cin>>keys[i];
            }

            cout<<"Enter the search probabilities: ";
            for (int i = 1; i <= n; i++) {
                cin>>p[i];
            }

            cout<<"Enter the failure probabilities: ";
            for (int i = 0; i <= n; i++) {
                cin>>q[i];
            }
        }

        int min_val(int i, int j) {
           int m, k;
           int min = INT_MAX;
           for(m = root[i][j-1]; m <= root[i+1][j]; m++) {
               if(cost[i][m-1] + cost[m][j] < min) {
                   min = cost[i][m-1] + cost[m][j];
                   k = m;
               }
           }
              return k;
        }

        void constructOBST(){
            int i, j, k, m;
            for(i = 0; i <= n; i++) {
                weight[i][i] = q[i];
                root[i][i] = 0;
                cost[i][i] = 0;

                weight[i][i+1] = q[i] + q[i+1] + p[i+1];
                root[i][i+1] = i+1;
                cost[i][i+1] = q[i] + q[i+1] + p[i+1];
            }

            weight[n][n] = q[n];
            root[n][n] = 0;
            cost[n][n] = 0;
            
            for(m = 2; m <= n; m++) {
                for(i = 0; i <= n-m; i++) {
                    j = i + m;
                    weight[i][j] = weight[i][j-1] + p[j] + q[j];
                    k = min_val(i, j);
                    cost[i][j] = weight[i][j] + cost[i][k-1] + cost[k][j];
                    root[i][j] = k;
                }
            }
        }

void printTree() {
    cout << "Root is " << keys[root[0][n]] << endl;
    cout << "Cost is " << cost[0][n] << endl;
    cout << "\n\n\tNODE\tLEFT\tRIGHT\n\n";
    cout << "-----------------------------------------\n";
    printSubtree(root[0][n], 0, n);
}

void printSubtree(int rootIdx, int start, int end) {
    if (rootIdx == 0) {
        return;
    }
    cout << "\n\t" << rootIdx;
    int leftIdx = root[start][rootIdx - 1];
    int rightIdx = root[rootIdx][end];
    
    if (leftIdx == 0) {
        cout << "\t" << "-";
    } else {
        cout << "\t" << keys[leftIdx];
    }
    
    if (rightIdx == 0) {
        cout << "\t" << "-";
    } else {
        cout << "\t" << keys[rightIdx];
    }
    
    printSubtree(leftIdx, start, rootIdx - 1);
    printSubtree(rightIdx, rootIdx, end);
}
};

int main() {
    OBST obst;
    obst.acceptInput();
    obst.constructOBST();
    obst.printTree();
    return 0;
}
