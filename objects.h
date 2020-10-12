#pragma once
#include <string>
#include <iostream>
using namespace std;

class Bank{
    private:
        string accountNumber;
        double accountBalance;
        bool open; //bool to see if the account is open or not
        char risk; //L for low H for High
        double annualInterestRate;
        double annualService;
        char accountType; //for account type
    public:
        //contructor
        Bank(string aN="00000000", double aB=0.0, bool o=false, char r='L', double aI=0.0, double aS=0.0, char aT='N'){
            //default Number is 0000000, account Balance is 0, its closed, 0.0 interest rate, 0.0 annual charge
            //it starts at a low risk, it has N for none account type, and 0 annual service charge.
            accountNumber=aN;
            accountBalance=aB;
            open=o;
            risk =r;
            annualInterestRate=aI;
            annualService=aS;
            accountType=aT;

        }
        //getters
        string getAccountNumber(){
            return accountNumber;
        }
        double getAccountBalance(){
            return accountBalance;
        }
        bool getOpenStatus(){
            return open;
        }
        char getRisk(){
            return risk;
        }
        double getInterestRate(){
            return annualInterestRate;
        }
        double getService(){
            return annualService;
        }
        char getAccountType(){
            return accountType;
        }
        //setters
        void setAccountNumber(string aN){
            accountNumber=aN;
        }
        void setAccountBalance(double aB){
            accountBalance=aB;
        }
        void setOpenStatus(bool o){
            open=o;
        }
        void setRisk(char r){
            risk=r;
        }
        void setInterestRate(double aI){
            annualInterestRate=aI;
        }
        void setService(double aS){
            annualService=aS;
        }
        void setType(char aT){
            accountType=aT;
        }


        double withdrawl(double amount){
            if(open){
                if(amount>accountBalance){
                    cout<<"Withdrawl unsuccessful, insufficient amount!";
                }
                else{
                    accountBalance-=amount;
                    cout<<"Withdrawl successful! Current Balance: "<< accountBalance;
                }
            }
            else{
                cout<<"Account not open!";
            }
            return accountBalance;
        }

        double deposit(double amount){
            if(open){
                accountBalance+=amount;
                cout<<"Deposit successful! Current balance: "<< accountBalance;
            }
            else{
                cout<<"Account not open!";
            }
            return accountBalance;
        }

        double calcInt(){
            /*
            •Daily Interest Rate = (Annual interest rate / Number of days in the year)
            •Daily Interest = Balance * Daily Interest Rate
            •Balance = Balance + Daily Interest */
            double dailyInterestRate= annualInterestRate/365;
            double dailyInterest=accountBalance*dailyInterestRate;
            return accountBalance+dailyInterest;
        }
};
