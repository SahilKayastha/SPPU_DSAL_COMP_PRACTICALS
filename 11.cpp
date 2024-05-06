//Department maintains a student information. The file contains roll number, name, division and address. Allow user to add, delete information of student. Display information of particular employee. If record of student does not exist an appropriate message is displayed. If it is, then the system displays the student details. Use sequential file to main the data

#include<iostream>
#include<fstream>
using namespace std;

struct Student
{
    int roll;
    char name[50];
    char div;
    char add[100];
};

void add(){
    ofstream outFile("student.dat", ios::binary|ios::app);
    if(!outFile){
        cerr<<"Error in Opening File."<<endl;
        return;
    }

    Student s;
    cout<<"Enter Roll no: ";
    cin>>s.roll;
    cout<<"Enter name: ";
    cin>>s.name;
    cout<<"Enter div: ";
    cin>>s.div;
    cout<<"Enter add: ";
    cin>>s.add;

    outFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
    outFile.close();
}

void Dele(int roll){
    ifstream InFile("student.dat", ios::binary);
    if(!InFile){
        cerr<<"Error in Opening file."<<endl;
        return;
    }

    ofstream OutFile("temp.dat", ios::binary);
    if(!OutFile){
        cerr<<"Error in Opening file."<<endl;
        return;
    }

    Student s;
    bool found = false;
    while(InFile.read(reinterpret_cast<char*>(&s), sizeof(Student))){
        if(s.roll == roll){
            found = true;
            continue;
        }

        OutFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
    }
    InFile.close();
    OutFile.close();

    remove("student.dat");
    rename("temp.dat","student.dat");

    if(found){
        cout<<"Student with roll number "<<roll<<" deleted successfully"<<endl;
    } else {
        cout<<"Student with roll number "<<roll<<" not Found"<<endl;
    }
}

void display(int rollnum){
    ifstream InFile("student.dat", ios::binary);
    if (!InFile){
        cerr<<"Error in opening file."<<endl;
    }

    Student s;
    bool found = false;
    while(InFile.read(reinterpret_cast<char*>(&s), sizeof(Student))){
        if(s.roll == rollnum){
            found = true;
            cout<<"Name of Student is: "<<s.name<<endl;
            cout<<"roll num of Student is: "<<s.roll<<endl;
            cout<<"div of Student is: "<<s.div<<endl;
            cout<<"address of Student is: "<<s.add<<endl;
            break;
        }
    }
    InFile.close();

    if(!found){
        cout<<"Student with roll number "<<rollnum<<"not found"<<endl;
    }
}

int main(){
    int choice, rollnum;

    do
    {
        cout << "\nStudent Information System\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                cout << "Enter Roll Number to delete: ";
                cin >> rollnum;
                Dele(rollnum);
                break;
            case 3:
                cout << "Enter Roll Number to display: ";
                cin >> rollnum;
                display(rollnum);
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    } while (choice != 4);
    
    return 0;
}
