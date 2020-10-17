#pragma once
#include <string>
#include <iostream>
using namespace std;

class Bank {
protected:
    string accountNumber;
    double accountBalance;
    string open; //bool to see if the account is open or not
    double annualInterestRate;
    double annualService;
    string lastDate;

public:
    //contructor
    Bank(string aN = "00000000", double aB = 0.0, string o = "true", double aI = 2, double aS = 5, string d="d 0 0 0000") {
        //default Number is 0000000, account Balance is 0, its closed, 0.0 interest rate, 0.0 annual charge
        //it starts at a low risk, it has N for none account type, and 0 annual service charge.
        accountNumber = aN;
        accountBalance = aB;
        open = o;
        annualInterestRate = aI;
        annualService = aS;
        lastDate = d;
    }
    //getters
    string getAccountNumber() {
        return accountNumber;
    } 
    double getAccountBalance() {
        return accountBalance;
    }
    string getOpenStatus() {
        return open;
    }
    double getInterestRate() {
        return annualInterestRate;
    }
    double getService() {
        return annualService;
    }
    string getDate(){
        return lastDate;
    }

    //setters
    void setAccountNumber(string aN) {
        accountNumber = aN;
    }
    void setAccountBalance(double aB) {
        accountBalance = aB;
    }
    void setOpenStatus(string o) {
        open = o;
    }
    virtual void setInterestRate(double aI) {           //changed to virtual cause Saving accounts over writes
        annualInterestRate = aI;
    }
    void setService(double aS) {
        annualService = aS;
    }
    void setDate(string d){
        lastDate=d;
    }


    virtual double withdraw(double amount) {
        if (open == "true") {
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
        if (open == "true") {
            accountBalance += amount;
            cout << "Deposit successful! Current balance: " << accountBalance;
        }
        else {
            cout << "Account not open!";
        }
        return accountBalance;
    }

    double calcInt(int times) {
        /*
        •Daily Interest Rate = (Annual interest rate / Number of days in the year)
        •Daily Interest = Balance * Daily Interest Rate
        •Balance = Balance + Daily Interest 
        */
        double dailyInterestRate = annualInterestRate / 365;
        double dailyInterest = accountBalance * dailyInterestRate;
        if(times==0){
            return accountBalance;
        }
        else{
            for(int i=0;i<times;i++){
                accountBalance += dailyInterest;
            }
        }
        return accountBalance;
    }

    double chargeService(int times){
        int years;
        if(times==0){
            return accountBalance;
        }
        else{
            if(times<365){
                years=0;
            }
            else
                years=times/365;
            for(int i=0;i<years;i++){
                accountBalance-=annualService;
            }
        
        }
        return accountBalance;
    }

    virtual void closeAcc()
    {
        open = "false";
    }
};

//paste jay stuff
class Checking : public Bank
{
private:
    string flag;

public:
    //Default constructor
    Checking() : Bank()
    {
        flag = "L";
    }
    
    //function to set flag variable
    void setFlag(string f)
    {
        flag = f;
    }
    
    //accessor to flag
    string getFlag()
    {
        return flag;
    }
    
    //withdraw function
    double withdraw(double amount)
    {
        double fundCharge = -25.0;
        if (open == "true")
        {
            if (accountBalance - amount < 0)   //if the withdrawal amount will cause a negative, just deduct the $25 fundCharge from the balance.
            {
                accountBalance = fundCharge;
                flag = "H";   //assign flag as highrisk
                if (accountNumber.substr(accountNumber.find("*"), accountNumber.length()) == "*")
                {
                    accountNumber = accountNumber;
                }
                else
                {
                    accountNumber = accountNumber + "*";
                }
                cout << "You withdrew more than you had, fund charge has been applied!" << endl;
            }
            else
            {
                accountBalance -= amount;
                cout << "withdraw Successful!" << endl;
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
        if(open == "true")
        {
            if (amount > 9999.0)   //if the single deposit is more that 9999, flag it as a high risk account then add asterik to indicate.
            {
                flag = "H";
                if (accountNumber.substr(accountNumber.find("*"), accountNumber.length()) == "*")
                {
                    accountNumber = accountNumber;
                }
                else
                {
                    accountNumber = accountNumber + "*";   //high risk account indicator
                }
                accountBalance += amount;
                cout << "A $" << amount << " deposit has been made" << endl;
            }
            else    //else go ahead with normal functionality.
            {
            accountBalance += amount;
            cout << "A $" << amount << " deposit has been made" << endl;
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
            if(accountBalance >= 50)
                status = "Active";
            else if(accountBalance < 50)
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

        void setInterestRate(double aI) 
        {
            if(aI < 10 || aI > 0.1)
                annualInterestRate = aI;
            else 
                cout<<"Interest rate must be between 0.1% and 10%"<<endl;
        }

        double withdraw(double amount)
        {
            if(open == "true")
            {
                if(status == "Active")  //override part to check the status 
                {
                    if(amount>accountBalance)
                    {
                        cout<<"withdraw unsuccessful, insufficient amount!";
                    }
                    else
                    {
                        accountBalance-=amount;
                        cout<<"withdraw successful! Current Balance: "<< accountBalance<<'\n';
                        if(accountBalance < 50)
                        {
                            status = "Inactive";
                            serviceCharge = 5;
                            accountBalance = accountBalance - serviceCharge;
                            //cout<<accountBalance<<endl; //adds a service charge with
                        }
                        if(accountBalance < 1)
                        {
                            closeAcc();
                        }
                    }
                    
                }
                else
                {
                   cout<<"Account Balance less than $50, cannot withdraw from Savings Account"<<endl;
                }
            }
            else
            {
                cout<<"Account not open, cannot withdraw at this time"<<endl;
            }

            return accountBalance;
        }

        double deposit(double amount){
            if(open == "true")
            {
                accountBalance = accountBalance + amount;
                cout<<"Deposit successful! Current balance: "<< accountBalance<<'\n';
                if(accountBalance >= 50)
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
