// ================================================================
// Programmer: Saim Ahmed
// Class: CIS-17B
// Instructor: Med Mogasemi
// ================================================================
// Program: Hospital Management System
// ================================================================
// Program Description:
// Hospital Patient Management System
// - Demonstrates usage of structs, enums, vectors, and dynamic memory.
// - Allows adding patients, displaying their records, and calculating total bills.
// ================================================================
#include <iostream>
#include <vector>
using namespace std;

// ================================================================
// Enum: Condition
// - Represents the medical status of a patient.
// - Values: STABLE (1), SERIOUS (2), CRITICAL (3).
// ================================================================
enum Condition
{
    STABLE = 1,
    SERIOUS = 2,
    CRITICAL = 3
};

// ================================================================
// Struct: Patient
// - Encapsulates patient information:
// - pID: Unique identifier for the patient.
// - pName: Name of the patient.
// - pCondition: Current medical condition (Condition enum).
// - pAmount: Pending bill amount for the patient.
// ================================================================
struct Patient
{
    int pID = 0;
    string pName = "";
    Condition pCondition;
    double pAmount = 0.0;
};

// ================================================================
// Typedef: PatientPtr
// - Defines a pointer to a Patient struct for dynamic memory management.
// ================================================================
typedef Patient *PatientPtr;

// Function Prototypes
void displayMenu();
PatientPtr createPatient();
void addPatient(vector<PatientPtr> &);
void displayPatients(const vector<PatientPtr> &);
double calculateTotalBills(const vector<PatientPtr> &);
string conditionToString(Condition c);
void deleteAll(vector<PatientPtr> &);

// ================================================================
// Main Function:
// - Serves as the entry point for the Hospital System.
// - Provides a menu-driven interface for managing patient records.
// - Coordinates memory cleanup upon exit.
// ================================================================
int main()
{
    int input = 0;
    vector<PatientPtr> patients;

    while (input < 5)
    {
        displayMenu();
        cin >> input;
        switch (input)
        {
        case 1:
            // ================================================================
            // Add Patient Record:
            // - Prompts user for details and adds a new patient to the vector.
            // ================================================================
            addPatient(patients);
            break;
        case 2:
            // ================================================================
            // Display Patient Records:
            // - Iterates through the list and prints each patient's information.
            // ================================================================
            displayPatients(patients);
            break;
        case 3:
            // ================================================================
            // Calculate Total Bills:
            // - Sums up all pending bills and displays the total.
            // ================================================================
            cout << "Total Hospital Bills Pending: " << calculateTotalBills(patients) << '\n';
            break;
        case 4:
            // ================================================================
            // Exit Program:
            // - Displays goodbye message, frees memory, and terminates.
            // ================================================================
            cout << "Goodbye.";
            deleteAll(patients);
            return 0;
        }
    }
    return 0;
}

// ================================================================
// Function: displayMenu
// - Displays the interactive menu options to the console.
// ================================================================
void displayMenu()
{
    cout << "==== Hospital System ====" << '\n';
    cout << "1. Add Patient" << '\n';
    cout << "2. Display Patients" << '\n';
    cout << "3. Show Total Hospital Bills" << '\n';
    cout << "4. Exit" << '\n';
    cout << "Enter choice: ";
}

// ================================================================
// Function: createPatient
// - Allocates memory for a new Patient and populates it with user input.
// - Returns:
// - PatientPtr: Pointer to the newly created Patient object.
// ================================================================
PatientPtr createPatient()
{
    int inputID = 0;
    string inputName = "";
    int conditionMarker = 0;
    Condition inputCondition;
    double inputAmount = 0.0;

    cout << "Enter Patient ID: ";
    cin >> inputID;
    cout << "Enter Patient Name: ";
    cin >> inputName;
    cout << "Select Condition (1-3):" << '\n';
    cout << "1. STABLE" << '\n';
    cout << "2. SERIOUS" << '\n';
    cout << "3. CRITICAL" << '\n';
    cout << "Enter choice: ";
    cin >> conditionMarker;
    inputCondition = static_cast<Condition>(conditionMarker);
    cout << "Enter Bill Amount: ";
    cin >> inputAmount;

    PatientPtr freshPatient = new Patient;
    freshPatient->pID = inputID;
    freshPatient->pName = inputName;
    freshPatient->pCondition = inputCondition;
    freshPatient->pAmount = inputAmount;

    return freshPatient;
}

// ================================================================
// Function: conditionToString
// - Converts the Condition enum value to a human-readable string.
// - Parameters:
// - Condition c: The condition enum value to convert.
// - Returns:
// - string: The corresponding string representation.
// ================================================================
string conditionToString(Condition c)
{
    string result = "";
    switch (c)
    {
    case 1:
        result = "Stable";
        break;
    case 2:
        result = "Serious";
        break;
    case 3:
        result = "Critical";
        break;
    }
    return result;
}

// ================================================================
// Function: addPatient
// - Calls createPatient and stores the pointer in the patients vector.
// - Parameters:
// - vector<PatientPtr> &patients: Reference to the list of patients.
// ================================================================
void addPatient(vector<PatientPtr> &patients)
{
    cout << endl;
    PatientPtr nPatient = createPatient();
    patients.push_back(nPatient);
    cout << '\n'
         << "Patient added successfully!" << '\n';
    cout << endl;
}

// ================================================================
// Function: displayPatients
// - Displays all patient records currently in the system.
// - Parameters:
// - const vector<PatientPtr> &patients: Constant reference to patient list.
// ================================================================
void displayPatients(const vector<PatientPtr> &patients)
{
    for (int i = 0; i < patients.size(); i++)
    {
        cout << endl;
        cout << "Patient ID: " << patients[i]->pID << '\n';
        cout << "Patient Name: " << patients[i]->pName << '\n';
        cout << "Patient Condition: " << conditionToString(patients[i]->pCondition) << '\n';
        cout << "Patient Pending Bill: " << patients[i]->pAmount << '\n';
        cout << endl;
    }
}

// ================================================================
// Function: calculateTotalBills
// - Calculates the sum of all pending bills in the system.
// - Parameters:
// - const vector<PatientPtr> &patients: Constant reference to patient list.
// - Returns:
// - double: The total sum of bills.
// ================================================================
double calculateTotalBills(const vector<PatientPtr> &patients)
{
    double billSum = 0;
    for (int i = 0; i < patients.size(); i++)
    {
        billSum += patients[i]->pAmount;
    }
    return billSum;
}

// ================================================================
// Function: deleteAll
// - Frees all dynamically allocated memory for patient records.
// - Parameters:
// - vector<PatientPtr> &patients: Reference to the list of patients.
// ================================================================
void deleteAll(vector<PatientPtr> &patients)
{
    for (PatientPtr pat : patients)
    {
        delete pat;
    }
    patients.clear();
}
