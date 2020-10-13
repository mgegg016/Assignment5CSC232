#pragma once
#include <string>
#include <iostream>
using namespace std;

class Bank {
protected:
    string accountNumber;
    double accountBalance;
    bool open; //bool to see if the account is open or not
    double annualInterestRate;
    double annualService;

public:
    //contructor
    Bank(string aN = "00000000", double aB = 0.0, bool o = true, double aI = 0.0, double aS = 0.0) {
        //default Number is 0000000, account Balance is 0, its closed, 0.0 interest rate, 0.0 annual charge
        //it starts at a low risk, it has N for none account type, and 0 annual service charge.
        accountNumber = aN;
        accountBalance = aB;
        open = o;
        annualInterestRate = aI;
        annualService = aS;
    }
    //getters
    string getAccountNumber() {
        return accountNumber;
    }
    double getAccountBalance() {
        return accountBalance;
    }
    bool getOpenStatus() {
        return open;
    }
    double getInterestRate() {
        return annualInterestRate;
    }
    double getService() {
        return annualService;
    }

    //setters
    void setAccountNumber(string aN) {
        accountNumber = aN;
    }
    void setAccountBalance(double aB) {
        accountBalance = aB;
    }
    void setOpenStatus(bool o) {
        open = o;
    }
    void setInterestRate(double aI) {
        annualInterestRate = aI;
    }
    void setService(double aS) {
        annualService = aS;
    }

    virtual double withdrawl(double amount) {
        if (open) {
            if (amount > accountBalance) {
                cout << "Withdrawl unsuccessful, insufficient amount!";
            }
            else {
                accountBalance -= amount;
                cout << "Withdrawl successful! Current Balance: " << accountBalance;
            }
        }
        else {
            cout << "Account not open!";
        }
        return accountBalance;
    }

    virtual double deposit(double amount) {
        if (open) {
            accountBalance += amount;
            cout << "Deposit successful! Current balance: " << accountBalance;
        }
        else {
            cout << "Account not open!";
        }
        return accountBalance;
    }

    double calcInt() {
        /*
        •Daily Interest Rate = (Annual interest rate / Number of days in the year)
        •Daily Interest = Balance * Daily Interest Rate
        •Balance = Balance + Daily Interest */
        double dailyInterestRate = annualInterestRate / 365;
        double dailyInterest = accountBalance * dailyInterestRate;
        return accountBalance + dailyInterest;
    }

    virtual void closeAcc()
    {
        open = false;
    }
};
