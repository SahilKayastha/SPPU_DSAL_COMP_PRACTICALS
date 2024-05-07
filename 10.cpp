// Read the marks obtained by students of second year in an online examination of particular subject. Find out maximum and minimum marks obtained in that subject. Use heap data structure. Analyze the algorithm
#include <iostream>

using namespace std;

void buildMaxHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {  //n / 2 - 1 represents the index of the last non-leaf node in a binary heap of size n. 
        int parent = i;
        int leftChild = 2 * parent + 1;
        int rightChild = 2 * parent + 2;

        int largest = parent;

        if (leftChild < n && arr[leftChild] > arr[largest]) {
            largest = leftChild;
        }

        if (rightChild < n && arr[rightChild] > arr[largest]) {
            largest = rightChild;
        }

        if (largest != parent) {
            swap(arr[parent], arr[largest]);
        }
    }
}

void buildMinHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        int parent = i;
        int leftChild = 2 * parent + 1;
        int rightChild = 2 * parent + 2;

        int smallest = parent;

        if (leftChild < n && arr[leftChild] < arr[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < n && arr[rightChild] < arr[smallest]) {
            smallest = rightChild;
        }

        if (smallest != parent) {
            swap(arr[parent], arr[smallest]);
        }
    }
}

int main() {
    int numStudents;

    cout << "Enter the number of students: ";
    cin >> numStudents;

    int *marks = new int[numStudents];

    cout << "Enter marks obtained by each student:\n";
    for (int i = 0; i < numStudents; ++i) {
        cout << "Enter marks for student " << i + 1 << ": ";
        cin >> marks[i];
    }

    int choice;
    do {
        cout << "\nOptions:\n";
        cout << "1. Find maximum marks\n";
        cout << "2. Find minimum marks\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Building max heap
                buildMaxHeap(marks, numStudents);
                cout << "Maximum marks obtained: " << marks[0] << endl;
                break;
            case 2:
                // Building min heap
                buildMinHeap(marks, numStudents);
                cout << "Minimum marks obtained: " << marks[0] << endl;
                break;
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }
    } while (choice != 3);

    delete[] marks;

    return 0;
}
