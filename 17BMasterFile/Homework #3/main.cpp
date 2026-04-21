#include <iostream>
using namespace std;

/**
 * TASK LIST:
 * 1. Implement Base Account class:
 *    - Vars: balance, deposits, withdrawals, interestRate, serviceCharges
 *    - Virtual functions: deposit, withdraw, calcInt, monthlyProc
 * 2. Implement SavingsAccount (derived):
 *    - Var: status (active/inactive)
 *    - Logic: inactive if balance < $25
 *    - Override: withdraw (check status), deposit (reactivate if > $25), monthlyProc (excess withdrawal fees)
 * 3. Implement CheckingAccount (derived):
 *    - Override: withdraw (overdraft fee logic), monthlyProc (base fee + per-check fee)
 * 4. Implement main():
 *    - User input for deposits/withdrawals
 *    - Display monthly stats (start/end balance, total deposits/withdrawals, fees)
 */

class Account{
    public:
        int deposits {};
        int withdrawals {};
        int serviceCharges {};
        double balance {};
        double annualInterestRate {};

        Account(double bal, double intRate) {
            this->balance = bal;
            this->annualInterestRate = intRate;
        }

        virtual void deposit(double amt){
            balance += amt;
            deposits++;
        }

        virtual void withdraw(double amt){
            balance -= amt;
            withdrawals--;
        }

        virtual void calcInt(){
            double monthRate = (annualInterestRate / 12) * balance;
            balance += monthRate;
        }

        virtual void monthlyProc(){
            balance -= serviceCharges;
            calcInt();
            withdrawals = 0;
            deposits = 0;
            serviceCharges = 0;
        }
};  

class SavingsAccount : public Account{
    public:
        bool status{};

        void withdraw(double amt) override {
            if (status){
                withdraw(amt);
            }
        }

        void deposit(double amt) override {
            if (!status && (balance += amt > 25)) {
                status = true;
                deposit(amt);
            }
        }

        void monthlyProc(){
            if (withdrawals > 4) {
                serviceCharges += (withdrawals - 4);
                monthlyProc();
            }
            if (balance < 25){
                status = false;
            }
        }

};

class CheckingAccount : public Account{};


int main(){

    
    return 0;
}