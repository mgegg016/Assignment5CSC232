

#include "objects.h"
#include <string>
#include <iostream>
#include <vector>
#include <istream>
#include <ctime>

using namespace std;

void createNewAccount();
bool allDigits(string s, int len);
bool isDigit(char c);
string getRandomAccountNum();



//structure to handle date comparision
struct Date{
    int d,m,y;
};

vector <Date> getTime(vector <Date> dates);

const int monthDays[12]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
vector <Bank> accounts; //maybe well use it probs not tho 
vector <Checking> checkingAccounts;
vector <Savings> savingsAccounts;





int main(){
    bool play = true;
    int choice;
    string tempAN;
    Bank tempAccount;
    //readFile function needs to be called first
    while(play){
        //cout<<getRandomAccountNum()<<endl;
        cout<<"Version 1.?"<<endl;
        cout<<"Welcome to the bank account system, would you like to [1] Open an account, [2] Login, [3] exit: ";
        cin >> choice;
        //got rid of the test checking objects - Mike
        
        if (choice==1||choice==2||choice==3){
            switch(choice){
                case 1:
                    
                    break;
                case 2:
                    cout<<"Enter your account number beginning with the type [C] Checkings [S] Savings: ";
                    cin>>tempAN;
                    if(allDigits(tempAN.substr(1,tempAN.size()),8)){
                        //todo login stuffs;
                        if(tempAN.find("C") == 0)
                        {
                            //Jay's Part
                            for (int i = 0; i < checkingAccounts.size(); i++)
                            {
                                if (tempAN == checkingAccounts[i].getAccountNumber())
                                {
                                    
                                }
                            }
                        }
                        else if(tempAN.find("S") == 0)
                        {
                            //Sahej's part
                            for(int i = 0; i < savingsAccounts.size(); i++)
                            {
                                if(tempAN == savingsAccounts[i].getAccountNumber())
                                {
                                    int choice;
                                    bool run = true;
                                    cout<<"Would you like to: "<<'\n'<<"[1] Deposit"<<'\n'<<"[2] Widthdraw"<<'\n'<<"[3] Check Account Balance"<<'\n';
                                    cin>>choice;
                                    if(choice==1||choice==2||choice==3)
                                    {
                                        while(run)
                                        {
                                            switch (choice)
                                            {
                                            case 1:
                                                int depAmt;                                     //Amount the user wants to deposit
                                                cout<<"How much would you like to deposit?"<<'\n';
                                                cin>>depAmt;
                                                savingsAccounts[i].deposit(depAmt);
                                                break;
                                            case 2:
                                                int widAmt;                                     //amount the user wants to widthdraw
                                                cout<<"How much would you like to widthdraw?";
                                                cin>>widAmt;
                                                savingsAccounts[i].withdraw(widAmt);
                                                break;
                                            case 3:
                                                cout<<"Your Account Balance is: "<<savingsAccounts[i].getAccountBalance()<<endl;
                                                run = false;
                                                break;

                                            }
                                        
                                        }
                                    }
                                }
                            }
                        }
                    // }
                    // else{
                    //     cout<<"Invalid input!"<<endl;
                    //     play=true;
                    //     break;
                    // }
                case 3:
                    cout<<"Goodbye!"<<endl;
                    play=false;
                    break;
            }
        }
        else{
            cout<<"Invalid Input!";
            play=true;
            break;
        }
    }
    
    return 0;
}

bool isDigit(char ch) 
{ 
    if (ch >= '0' && ch <= '9') 
        return true; 
    return false; 
} 
bool allDigits(string str, int len) 
{ 
  
    // To mark the present digits 
    bool present[8] = { false }; 
    // For every character of the string 
    for (int i = 0; i < len; i++) { 
        // If the current character is a digit 
        if (isDigit(str[i])) { 
            // Mark the current digit as present 
            int digit = str[i] - '0'; 
            present[digit] = true; 
        } 
    } 
    // For every digit from 0 to 9 
    for (int i = 0; i < 8; i++) { 
        // If the current digit is 
        // not present in str 
        if (!present[i]) 
            return false; 
    } 
  
    return true; 
} 

void createAccounts(){
    Checking tempChecking;
    Savings tempSavings;
    string tempAccountNum=getRandomAccountNum();
    tempChecking.setAccountNumber(tempAccountNum);
    tempSavings.setAccountNumber(tempAccountNum);
    checkingAccounts.push_back(tempChecking);



}

string getRandomAccountNum(){
    int max = 99999999;
    int min = 10000000;
    int output = min + (rand() % static_cast<int>(max - min + 1));
    string ranNum=to_string(output);
    return ranNum;

}


//From here down its functions relating to getting the time and comparing the time for interest rates and 



vector <Date> getTime(vector <Date> dates){
    time_t now = time(0);
    
    tm *ltm = localtime(&now);
    int year= 1900 + ltm->tm_year;
    int month= 1 + ltm->tm_mon;
    int date= ltm->tm_mday;



}

