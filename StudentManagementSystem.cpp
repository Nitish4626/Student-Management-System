#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Student
{
private:
    int rollNo;
    string name;
    string course;
    float marks;

public:
    void input()
    {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Course: ";
        getline(cin, course);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display()
    {
        cout << left
             << setw(12) << rollNo
             << setw(25) << name
             << setw(20) << course
             << setw(10) << marks
             << endl;
    }

    int getRollNo()
    {
        return rollNo;
    }

    void update()
    {
        cin.ignore();

        cout << "Enter New Student Name: ";
        getline(cin, name);

        cout << "Enter New Course: ";
        getline(cin, course);

        cout << "Enter New Marks: ";
        cin >> marks;
    }
};


// Add a new student
void addStudent()
{
    Student s;

    ofstream file("students.dat", ios::binary | ios::app);

    if (!file)
    {
        cout << "\nError opening file!";
        return;
    }

    s.input();

    file.write((char*)&s, sizeof(s));

    file.close();

    cout << "\nStudent added successfully!\n";
}


// Display all students
void displayStudents()
{
    Student s;

    ifstream file("students.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo student records found!\n";
        return;
    }

    cout << "\n================ STUDENT RECORDS ================\n";

    cout << left
         << setw(12) << "Roll No"
         << setw(25) << "Name"
         << setw(20) << "Course"
         << setw(10) << "Marks"
         << endl;

    cout << "---------------------------------------------------------------\n";

    while (file.read((char*)&s, sizeof(s)))
    {
        s.display();
    }

    file.close();
}


// Search student
void searchStudent()
{
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    ifstream file("students.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo student records found!\n";
        return;
    }

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.getRollNo() == roll)
        {
            cout << "\nStudent Found!\n\n";

            cout << left
                 << setw(12) << "Roll No"
                 << setw(25) << "Name"
                 << setw(20) << "Course"
                 << setw(10) << "Marks"
                 << endl;

            cout << "---------------------------------------------------------------\n";

            s.display();

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nStudent not found!\n";
    }
}


// Update student
void updateStudent()
{
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    fstream file("students.dat",
                 ios::binary | ios::in | ios::out);

    if (!file)
    {
        cout << "\nNo student records found!\n";
        return;
    }

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.getRollNo() == roll)
        {
            cout << "\nEnter new details:\n";

            s.update();

            // Move file pointer back to the beginning
            // of the current record.
            streampos position =
                file.tellg() - static_cast<streamoff>(sizeof(s));

            file.seekp(position);

            file.write((char*)&s, sizeof(s));

            found = true;

            cout << "\nStudent updated successfully!\n";
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nStudent not found!\n";
    }
}


// Delete student
void deleteStudent()
{
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    ifstream inFile("students.dat", ios::binary);

    if (!inFile)
    {
        cout << "\nNo student records found!\n";
        return;
    }

    ofstream outFile("temp.dat", ios::binary);

    while (inFile.read((char*)&s, sizeof(s)))
    {
        if (s.getRollNo() == roll)
        {
            found = true;
            continue;
        }

        outFile.write((char*)&s, sizeof(s));
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
    {
        cout << "\nStudent deleted successfully!\n";
    }
    else
    {
        cout << "\nStudent not found!\n";
    }
}


// Main menu
int main()
{
    int choice;

    do
    {
        cout << "\n\n";
        cout << "============================================\n";
        cout << "       STUDENT MANAGEMENT SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "============================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nThank you for using the system!\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
