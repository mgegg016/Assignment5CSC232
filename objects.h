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
    virtual void setInterestRate(double aI) {           //changed to virtual cause Saving accounts over writes
        annualInterestRate = aI;
    }
    void setService(double aS) {
        annualService = aS;
    }

    virtual double withdraw(double amount) {
        if (open) {
            if (amount > accountBalance) {
                cout << "withdraw unsuccessful, insufficient amount!";
            }
            else {
                accountBalance -= amount;
                cout << "withdraw successful! Current Balance: " << accountBalance;
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
        accountBalance += dailyInterest;
        return accountBalance;
    }

    virtual void closeAcc()
    {
        open = false;
    }
};

//paste jay stuff
class Checking : public Bank
{
private:
    char flag;
    string accntNumber;

public:
    //Default constructor
    Checking() : Bank()
    {
        flag = 'L';
        accntNumber = "C" + accountNumber;
    }
    //Second constructor. Assigning checking parameters to bank parameters
    Checking(string checkingNum, double checkingBalance, bool checkingStat, double checkingInterest, double checkingAnnualService) 
    : Bank(checkingNum, checkingBalance, checkingStat, checkingInterest, checkingAnnualService)
    {
        accntNumber = "C" + checkingNum;   //assigning checking number to accntNumber but concatenating with C
    }

    //accessor to flag and accntnumber
    char getFlag()
    {
        return flag;
    }

    string getAccntNumber()
    {
        return accntNumber;
    }

    //withdraw function
    double withdraw(double amount)
    {
        double fundCharge = 25.0;
        if (open)
        {
            if (accountBalance - amount < 0)   //if the withdrawal amount will cause a negative, just deduct the $25 fundCharge from the balance.
            {
                accountBalance -= fundCharge;
                flag = 'H';   //assign flag as highrisk
                accntNumber = accntNumber + "*";   //high risk account indicator
            }
            else
            {
                accountBalance -= amount;
            }
        }
        else
        {
            cout << "Account not open!";
        }
        return accountBalance;
    }

    double deposit(double amount)   //a deposit function
    {
        if(open)
        {
            if (amount > 9999.0)   //if the single deposit is more that 9999, flag it as a high risk account then add asterik to indicate.
            {
            flag = 'H';
            accntNumber = accntNumber + "*";
            accountBalance += amount;
            }
            else    //else go ahead with normal functionality.
            {
            accountBalance += amount;
            }
        }
        else
        {
            cout << "Account not open!";
        }
        return accountBalance;
    
    }
};

//sahej stuff
class Savings : public Bank{
    private:
        string status;                      //a way to see if the account is active or inactive 
        double serviceCharge;           //if the account is inactive(balance is below 50) a service charge of 5 dollars is applied
    public:
        Savings() : Bank()
        {
            if(accountBalance > 50)
                status = "Active";
            else 
                status = "Inactive";
        }
        //returns the status
        string getStatus()
        {
            return status;
        }

        //sets the Status and checks that the annual intrest rate is not more than 10% or less than .1%
        void setStatus(string s)
        {
            status = s;
        }

        void setServiceCharge()      //Sets the service charge value to 5
        {
            serviceCharge = 5;
        }

        void setInterestRate(double aI) 
        {
            if(aI < 10 || aI > 0.1)
                annualInterestRate = aI;
            else 
                cout<<"Interest rate must be between 0.1% and 10%"<<endl;
        }

        double withdraw(double amount)
        {
            if(!open)
            {
                if(status == "Active")  //override part to check the status 
                {
                    if(amount>accountBalance)
                    {
                        cout<<"withdraw unsuccessful, insufficient amount!";
                    }
                }
                else
                {
                    accountBalance-=amount;
                    cout<<"withdraw successful! Current Balance: "<< accountBalance;
                    if(accountBalance < 50 && accountBalance >= 1)
                    {
                        status = "Inactive";
                        accountBalance = accountBalance - serviceCharge; //adds a service charge with
                    }
                    else if(accountBalance < 1)
                    {
                        closeAcc();
                    }
                }
            }
            else
            {
                cout<<"Account Balance less than $50, cannot withdraw from Savings Account"<<endl;
            }

            return accountBalance;
        }

        double deposit(double amount){
            if(open)
            {
                accountBalance = accountBalance + amount;
                cout<<"Deposit successful! Current balance: "<< accountBalance;
                if(accountBalance > 50)
                {
                    status = "Active";
                }
            }
            else{
                cout<<"Account not open!";
            }
            return accountBalance;
        }


};