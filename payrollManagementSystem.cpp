#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Structure for Employee
struct Employee {
    char name[50];
    char designation[50];
    float salary, hra, da, allowances;
    int code;
    int workingHours; // Added number of working hours
};

// Array for storing employees
Employee emp[100];
int num = 0;

// Function to read employee data from Records.txt
void loadRecords() {
    ifstream inFile("Records.txt");
    if (!inFile) {
        cout << "Error: Could not open Records.txt file!\n";
        exit(1);
    }

    // Read data from the file
    while (inFile >> emp[num].name >> emp[num].designation >> emp[num].salary >>
           emp[num].hra >> emp[num].da >> emp[num].allowances >> emp[num].code >> emp[num].workingHours) {
        num++;
    }

    inFile.close();
}

// Function to display payslip for an employee
void displayPayslip() {
    int code;
    cout << "Enter Job Code to View Payslip: ";
    cin >> code;

    for (int i = 0; i < num; i++) {
        if (emp[i].code == code) {
            cout << "\nPayslip for: " << emp[i].name << "\n";
            cout << "Designation: " << emp[i].designation << "\n";
            cout << "Salary: " << emp[i].salary << "\n";
            cout << "HRA: " << emp[i].hra << "\n";
            cout << "DA: " << emp[i].da << "\n";
            cout << "Allowances: " << emp[i].allowances << "\n";
            cout << "Working Hours: " << emp[i].workingHours << "\n";
            return;
        }
    }
    cout << "Invalid Job Code. Please try again!\n";
}

// Main Function
int main() {
    cout << "Welcome to the Payroll Management System\n";
    cout << "----------------------------------------\n";

    // Load employee records from file
    loadRecords();

    char choice;
    do {
        displayPayslip();

        cout << "\nDo you want to view another payslip? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "Thank you for using the Payroll Management System. Goodbye!\n";
    return 0;
}
