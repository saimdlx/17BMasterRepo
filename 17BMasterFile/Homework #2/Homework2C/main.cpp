#include <iostream>
#include <vector>
using namespace std;

enum Condition
{
    STABLE = 1,
    SERIOUS = 2,
    CRITICAL = 3
};

struct Patient
{
    int pID = 0;
    string pName = "";
    Condition pCondition;
    double pAmount = 0.0;
};

typedef Patient *PatientPtr;

void displayMenu();
PatientPtr createPatient();
void addPatient(vector<PatientPtr> &);
void displayPatients(const vector<PatientPtr> &);
double calculateTotalBills(const vector<PatientPtr> &);
string conditionToString(Condition c);
void deleteAll(vector<PatientPtr> &);

// Program Execution Begins Here
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
            addPatient(patients);
            break;
        case 2:
            displayPatients(patients);
            break;
        case 3:
            cout << "Total Hospital Bills Pending: " << calculateTotalBills(patients) << '\n';
            break;
        case 4:
            cout << "Goodbye.";
            deleteAll(patients);
            return 0;
        }
    }
    return 0;
}

void displayMenu()
{
    cout << "==== Hospital System ====" << '\n';
    cout << "1. Add Patient" << '\n';
    cout << "2. Display Patients" << '\n';
    cout << "3. Show Total Hospital Bills" << '\n';
    cout << "4. Exit" << '\n';
    cout << "Enter choice: ";
}

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

void addPatient(vector<PatientPtr> &patients)
{
    cout << endl;
    PatientPtr nPatient = createPatient();
    patients.push_back(nPatient);
    cout << '\n'
         << "Patient added successfully!" << '\n';
    cout << endl;
}

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

double calculateTotalBills(const vector<PatientPtr> &patients)
{
    double billSum = 0;
    for (int i = 0; i < patients.size(); i++)
    {
        billSum += patients[i]->pAmount;
    }
    return billSum;
}

void deleteAll(vector<PatientPtr> &patients)
{
    for (PatientPtr pat : patients)
    {
        delete pat;
    }
    patients.clear();
}