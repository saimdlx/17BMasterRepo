// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: Bank Account Management
// ================================================================
// Program Description:
// Bank Account Hierarchy
// - Demonstrates inheritance and polymorphism with Account classes.
// - Supports Savings and Checking account types with specific rules
//   for withdrawals, deposits, and monthly processing.
// ================================================================
#include <iostream>
#include <iomanip>
using namespace std;

// ================================================================
// Class: Account
// - Base class representing a generic bank account.
// - Tracks balance, number of deposits/withdrawals, and interest.
// ================================================================
class Account{
    public:
        int deposits {};
        int withdrawals {};
        double serviceCharges {};
        double balance {};
        double annualInterestRate {};

        // ================================================================
        // Constructor: Account
        // - Initializes balance and annual interest rate.
        // ================================================================
        Account(double bal, double intRate) {
            this->balance = bal;
            this->annualInterestRate = intRate;
        }

        // ================================================================
        // Function: deposit
        // - Adds amount to balance and increments deposit count.
        // ================================================================
        virtual void deposit(double amt){
            balance += amt;
            deposits++;
        }

        // ================================================================
        // Function: withdraw
        // - Subtracts amount from balance and increments withdrawal count.
        // ================================================================
        virtual void withdraw(double amt){
            balance -= amt;
            withdrawals++;
        }

        // ================================================================
        // Function: calcInt
        // - Calculates monthly interest and adds it to the balance.
        // ================================================================
        virtual void calcInt(){
            double monthRate = (annualInterestRate / 12) * balance;
            balance += monthRate;
        }

        // ================================================================
        // Function: monthlyProc
        // - Deducts service charges, calculates interest, and resets counts.
        // ================================================================
        virtual void monthlyProc(){
            balance -= serviceCharges;
            calcInt();
            withdrawals = 0;
            deposits = 0;
            serviceCharges = 0;
        }

        // ================================================================
        // Function: stats
        // - Displays monthly statistics for the account.
        // ================================================================
        void stats(){
            cout << fixed << setprecision(2);
            cout << "Withdrawals: " << withdrawals << '\n';
            cout << "Deposits: " << deposits << '\n';
            cout << "Service charges: " << serviceCharges << '\n';
            cout << "Ending Balance: " << balance << '\n';
            cout << "Press enter to continue..." << endl;
        }
};  

// ================================================================
// Class: SavingsAccount (Derived from Account)
// - Represents a savings account with an "active" status logic.
// - Inactive if balance falls below $25.
// ================================================================
class SavingsAccount : public Account{
    public:
        bool status{};

        // ================================================================
        // Constructor: SavingsAccount
        // - Initializes via base constructor and sets initial status.
        // ================================================================
        SavingsAccount(double bal, double intRate, bool status) : Account(bal, intRate) {
            this->status = status;
        };  

        // ================================================================
        // Function: withdraw
        // - Overrides withdrawal to check for active status.
        // ================================================================
        void withdraw(double amt) override {
            if (status == false) {
                cout << "Account is inactive" << endl;
            }
            else{
                Account::withdraw(amt);
                if (balance < 25){
                    status = false;
                }
            }
        }

        // ================================================================
        // Function: deposit
        // - Overrides deposit to reactivate account if balance exceeds $25.
        // ================================================================
        void deposit(double amt) override {
            if (!status && (balance + amt > 25)){
                Account::deposit(amt);
                status = true;
            }
            else {
                Account::deposit(amt);
            }
        }

        // ================================================================
        // Function: monthlyProc
        // - Adds extra charges for excess withdrawals and checks status.
        // ================================================================
        void monthlyProc() override {
            if (withdrawals > 4) {
                serviceCharges += (withdrawals - 4);
            }
            Account::monthlyProc();

            if (balance < 25){
                status = false;
            }
        }

};

// ================================================================
// Class: CheckingAccount (Derived from Account)
// - Represents a checking account with overdraft fees.
// ================================================================
class CheckingAccount : public Account{
    public:

        CheckingAccount(double bal, double intRate) : Account(bal, intRate){};

        // ================================================================
        // Function: withdraw
        // - Overrides withdrawal to apply a $15 fee if balance goes below zero.
        // ================================================================
        void withdraw(double amt) override {
            if ((balance - amt) < 0){
                balance -= 15;
                cout << "Account balance below zero, withdraw request failed." << endl;
            }
            else{
                Account::withdraw(amt);
            }
        }

        // ================================================================
        // Function: monthlyProc
        // - Applies standard monthly fees and per-withdrawal charges.
        // ================================================================
        void monthlyProc() override {
            serviceCharges += (5 + (0.10 * withdrawals));
            Account::monthlyProc();
        }
};

// ================================================================
// Prototype: displayMenu
// - Displays the user interface menu options.
// ================================================================
void displayMenu();

// ================================================================
// Main Function:
// - Drives the bank account management system.
// - Handles user input to perform deposits, withdrawals, and updates.
// ================================================================
int main(){
    SavingsAccount svgacc(0, 0.05, false);
    CheckingAccount chkacc(0, 0.05);
    int option = 0;
    double amt = 0;
    
    displayMenu();
    cin >> option;
    while (option != 6){
        switch(option){
            // ================================================================
            // Case 1 & 2: Deposits
            // - Prompts for amount and updates respective account.
            // ================================================================
            case 1:
                cout << "Enter amount to deposit: ";
                cin >> amt;
                svgacc.deposit(amt);
                break;
            case 2:
                cout << "Enter amount to deposit: ";
                cin >> amt;
                chkacc.deposit(amt);
                break;
            // ================================================================
            // Case 3 & 4: Withdrawals
            // - Prompts for amount and checks constraints before processing.
            // ================================================================
            case 3:
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                svgacc.withdraw(amt);
                break;
            case 4:
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                chkacc.withdraw(amt);
                break;
            // ================================================================
            // Case 5: Update and Display Statistics
            // - Shows monthly totals and performs end-of-month calculations.
            // ================================================================
            case 5:
                cout << "SAVINGS ACCOUNT MONTHLY STATISTICS:" << '\n';
                svgacc.stats();
                svgacc.monthlyProc();
                cin.ignore();
                cin.get();

                cout << "CHECKING ACCOUNT MONTHLY STATISTICS:" << '\n';
                chkacc.stats();
                chkacc.monthlyProc();
                cin.get();
                break;
            case 6:
                return 0;
        }
        displayMenu();
        cin >> option;
    }
    return 0;
}

// ================================================================
// Function: displayMenu
// - Outputs the available bank actions to the console.
// ================================================================
void displayMenu(){
    cout << "******* BANK ACCOUNT MENU *******" << '\n';
    cout << "1. Savings Account Deposit" << '\n';
    cout << "2. Checking Account Deposit" << '\n';
    cout << "3. Savings Account Withdrawal" << '\n';
    cout << "4. Checking Account Withdrawal" << '\n';
    cout << "5. Update and Display Account Statistics" << '\n';
    cout << "6. Exit" << '\n';
    cout << "Your choice, please (1-6): ";
}

/*
Program Output using Sample Inputs
(base) sameelocal@saimbook Homework #3 % ./a.out
******* BANK ACCOUNT MENU *******
1. Savings Account Deposit
2. Checking Account Deposit
3. Savings Account Withdrawal
4. Checking Account Withdrawal
5. Update and Display Account Statistics
6. Exit
Your choice, please (1-6): 1
Enter amount to deposit: 1000.25
******* BANK ACCOUNT MENU *******
1. Savings Account Deposit
2. Checking Account Deposit
3. Savings Account Withdrawal
4. Checking Account Withdrawal
5. Update and Display Account Statistics
6. Exit
Your choice, please (1-6): 2
Enter amount to deposit: 563.25
******* BANK ACCOUNT MENU *******
1. Savings Account Deposit
2. Checking Account Deposit
3. Savings Account Withdrawal
4. Checking Account Withdrawal
5. Update and Display Account Statistics
6. Exit
Your choice, please (1-6): 3
Enter amount to withdraw: 53.98
******* BANK ACCOUNT MENU *******
1. Savings Account Deposit
2. Checking Account Deposit
3. Savings Account Withdrawal
4. Checking Account Withdrawal
5. Update and Display Account Statistics
6. Exit
Your choice, please (1-6): 4
Enter amount to withdraw: 257.36
******* BANK ACCOUNT MENU *******
1. Savings Account Deposit
2. Checking Account Deposit
3. Savings Account Withdrawal
4. Checking Account Withdrawal
5. Update and Display Account Statistics
6. Exit
Your choice, please (1-6): 5
SAVINGS ACCOUNT MONTHLY STATISTICS:
Withdrawals: 1
Deposits: 1
Service charges: 0.00
Ending Balance: 946.27
Press enter to continue...

CHECKING ACCOUNT MONTHLY STATISTICS:
Withdrawals: 1
Deposits: 1
Service charges: 0.00
Ending Balance: 305.89
Press enter to continue...

******* BANK ACCOUNT MENU *******
1. Savings Account Deposit
2. Checking Account Deposit
3. Savings Account Withdrawal
4. Checking Account Withdrawal
5. Update and Display Account Statistics
6. Exit
Your choice, please (1-6): 6
*/