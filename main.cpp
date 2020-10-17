/*
Jabez Nuetey M03270970, Sahejbir Bhatia M03322916, Mike Gegg
*/

#include "objects.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <sstream>
#include <cmath>

using namespace std;

void createAccounts();
bool allDigits(string s, int len);
bool isDigit(char c);
string getRandomAccountNum();
void readSavingsFile();
void updateSavingsFile();
void loginCheckingsAcc(string);
void loginSavingsAcc(string);
void readCheckingsFile();
void updateCheckingsFile();


//structure to handle date comparision
struct Date{
    int d,m,y;
};

Date getCurrentTime();
Date getOldTime(string file,string accountN);
int getDifference(Date dt1, Date dt2);
const int monthDays[12]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
vector <Bank> accounts; //maybe well use it probs not tho 
vector <Checking> checkingAccounts;
vector <Savings> savingsAccounts;

int countLeapYears(Date d);
int getInterestAmount(string file, string accountNum);
int getServiceAmount(string file, string accountNum);

int main(){

    readSavingsFile();
    readCheckingsFile();

    bool play = true;
    int choice;
    string tempAN;
    Bank tempAccount;
    while(play){
        //cout<<"Version 2.1"<<endl;
        cout<<"Welcome to the bank account system, would you like to: \n[1] Open an account\n[2] Login\n[3] exit \n:";
        cin >> choice;
        //got rid of the test checking objects - Mike
        
        if (choice==1||choice==2||choice==3){
            switch(choice){
                case 1:
                    createAccounts();
                    break;
                case 2:
                    cout<<"Enter your account number beginning with the type [C] Checkings [S] Savings: ";
                    cin>>tempAN;
                    // if(allDigits(tempAN.substr(1,tempAN.size()),8)){
                        //todo login stuffs;
                        if(tempAN.find("C") == 0)
                        {
                            //Jay's Part
                            loginCheckingsAcc(tempAN);
                        }
                        else if(tempAN.find("S") == 0)
                        {
                            //Sahej's part
                            loginSavingsAcc(tempAN);
                        }
                        break;
                case 3:
                    updateCheckingsFile();
                    updateSavingsFile();
                    
                    cout<<"Goodbye!"<<endl;
                    play=false;
                    break;
            }
        }
        else{
            cout<<"Invalid Input!, please choose valid option\n";
            play=true;
            continue;
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

    for(int i = 0; i < checkingAccounts.size(); i++)
    {
       if('C' + tempAccountNum == checkingAccounts[i].getAccountNumber() || 'C' + tempAccountNum + '*' == checkingAccounts[i].getAccountNumber())
        {
            tempAccountNum=getRandomAccountNum();
        }
    }
    for(int i = 0; i < savingsAccounts.size(); i++)
    {
        if('S' + tempAccountNum == savingsAccounts[i].getAccountNumber())
        {
            tempAccountNum=getRandomAccountNum();
        }
    }
    int intDep;
    char keepRunning;
    
    while (keepRunning != 'n')
    {
        cout<<"Please make an intial deposit of at least 50 dollars to activate your Saving account: "<<'\n';
        cin>>intDep;
        if(intDep >= 50)
        {
            tempSavings.deposit(intDep);
            break;
        }
        else
        {
            
            cout << '\n' << "Please enter a minimum of $50, would you like to enter another amount (y/n): " << '\n';
            cin >> keepRunning;

        }
    }
    if(keepRunning == 'n')
    {
        cout<<"Sorry cannot open account with less that $50 initial deposit for Savings Account"<<endl;
        return;
    }
    cout << '\n' << "Your checking account number is: " << 'C' + tempAccountNum << endl;
    cout << "Your savings account number is: "<<'S' + tempAccountNum << endl;
    tempChecking.setAccountNumber('C' + tempAccountNum);
    tempSavings.setAccountNumber('S' + tempAccountNum);
    checkingAccounts.push_back(tempChecking);
    savingsAccounts.push_back(tempSavings);

}


string getRandomAccountNum(){
    int max = 99999999;
    int min = 10000000;
    int output = min + (rand() % static_cast<int>(max - min + 1));
    string ranNum=to_string(output);
    return ranNum;

}

//From here down its functions relating to getting the time and comparing the time part of mike geggs stuff

// This function returns number of days between two given 
// dates 
int getDifference(Date dt1, Date dt2) 
{ 
    // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1' 
  
    // initialize count using years and day 
    long int n1 = dt1.y*365 + dt1.d; 
  
    // Add days for months in given date 
    for (int i=0; i<dt1.m - 1; i++) 
        n1 += monthDays[i]; 
  
    // Since every leap year is of 366 days, 
    // Add a day for every leap year 
    n1 += countLeapYears(dt1); 
  
    // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2' 
  
    long int n2 = dt2.y*365 + dt2.d; 
    for (int i=0; i<dt2.m - 1; i++) 
        n2 += monthDays[i]; 
    n2 += countLeapYears(dt2); 
  
    // return difference between two counts 
    return (n2 - n1); 
} 

int stringToInt(string s){
    int num=0;
    for(int i=0;i<s.size();i++){
        num+=(s[i]-48)*pow(10, (s.size()-i-1));
    }
    return num;
}

Date getCurrentTime(){
    time_t now = time(0);
    Date tempDate;
    vector <Date> storedDates;
    tm *ltm = localtime(&now);
    int year= 1900 + ltm->tm_year;
    int month= 1 + ltm->tm_mon;
    int day= ltm->tm_mday;
    tempDate.y=year;
    tempDate.m=month;
    tempDate.d=day;


    return tempDate;
}

vector <string> splitLines(string line, char delim){
    stringstream ss(line);//stringstream to work with getline
    vector <string> splitLine;
    string s;//temp local string variable
    while(getline(ss, s, delim)){
        splitLine.push_back(s);
    }
    return splitLine;
}

Date getOldTime(string file, string accountNum){
    Date tempDate;
    string text;
    string line;
    ifstream inFile(file);
    vector <string> lines;
    vector <string> firstDelimVec;
    vector <string> secondDelimVec;
    int lineCount=1;
    int locker;
    if(!inFile){
        cout<<"Cannot find the file. . ."<<endl;
    }
    else{
        while(getline(inFile,text)){
            lines.push_back(text);
            for(int i=0;i<lines.size();i++){
                if(lines[i].compare(accountNum)==0){
                    locker=i+1;
                }
            }
                line=lines[locker];
                firstDelimVec=splitLines(line,' ');
                secondDelimVec=splitLines(firstDelimVec[3],'/');            
        }
        tempDate.d=stringToInt(secondDelimVec[1]);
        tempDate.m=stringToInt(secondDelimVec[2]);
        tempDate.y=stringToInt(secondDelimVec[3]);


        
    }


    return tempDate;
}

int countLeapYears(Date d) 
{ 
    int years = d.y; 
  
    // Check if the current year needs to be considered 
    // for the count of leap years or not 
    if (d.m <= 2) 
        years--; 
  
    // An year is a leap year if it is a multiple of 4, 
    // multiple of 400 and not a multiple of 100. 
    return years / 4 - years / 100 + years / 400; 
} 

string formatDate(Date date){
    string formattedDate= "d/"+to_string(date.d)+"/"+to_string(date.m)+"/"+to_string(date.y);
    return formattedDate;
}

//end of time related function

//functions for interest and service charge



void loginCheckingsAcc(string tempAN)
{
    bool present;
    for (int i = 0; i < checkingAccounts.size(); i++)
    {
        if (tempAN == checkingAccounts[i].getAccountNumber() || tempAN + '*' == checkingAccounts[i].getAccountNumber())
        {
            cout << "......" << endl;
            present = true;
            int selection;
            cout << "[1] Deposit" << "\n[2] Withdraw" << "\n[3] Check Balance" << "\n[4] Go Back \n: ";
            cin >> selection;
            if (selection == 1 )
            {
                double depAmount;
                cout << "Enter deposit amount: ";
                cin >> depAmount;
                checkingAccounts[i].deposit(depAmount);
                break;
            }
            else if (selection == 2)
            {
                double withAmount;
                cout << "Enter withdraw amount: ";
                cin >> withAmount;
                checkingAccounts[i].withdraw(withAmount);
                break;
            }
            else if (selection == 3)
            {
                cout << "Your balance is: " << checkingAccounts[i].getAccountBalance() << endl;
                break;
            }
            else if (selection == 4)
            {
                break;
            }
            else
            {
                cout << "invalid input" << endl;
                break;
            }
        }
    }
    if(!present)
    {
        cout << "Please Enter valid account number \n" << endl;    
    }
    
}

void loginSavingsAcc(string tempAN)
{
    bool present;
    for(int i = 0; i < savingsAccounts.size(); i++)
    {
        if(tempAN == savingsAccounts[i].getAccountNumber())
        {
            present = true;
            int choice;
            bool run = true;
            double interest=savingsAccounts[i].calcInt(getDifference(getOldTime("Savings.txt",tempAN),getCurrentTime()));
            savingsAccounts[i].setAccountBalance(interest);
            cout<<"completed interest..."<<endl;
            double serviceFee=savingsAccounts[i].chargeService(getDifference(getOldTime("Savings.txt",tempAN),getCurrentTime()));
            savingsAccounts[i].setAccountBalance(serviceFee);

            while(run)
            {
                cout<<'\n'<<"Would you like to: "<<'\n'<<"[1] Deposit"<<'\n'<<"[2] Widthdraw"<<'\n'<<"[3] Check Account Balance"<<'\n'<<
                "[4] Go back"<<'\n';
                cin>>choice;
                if(choice==1||choice==2||choice==3||choice==4)
                {
                    switch (choice)
                    {
                        case 1:
                            double depAmt;                                     //Amount the user wants to deposit
                            cout<<"How much would you like to deposit?"<<'\n';
                            cin>>depAmt;
                            savingsAccounts[i].deposit(depAmt);
                            break;
                        case 2:
                            double widAmt;                                     //amount the user wants to widthdraw
                            cout<<"How much would you like to widthdraw?";
                            cin>>widAmt;
                            savingsAccounts[i].withdraw(widAmt);
                            break;
                        case 3:
                            cout<<"Your Account Balance is: "<<savingsAccounts[i].getAccountBalance()<<endl;
                            break;
                        case 4:
                            run = false;
                            break;
                    }
                                        
                }
                else
                {
                    cout<<"Invalid selection, please enter correct option"<<endl;
                    continue;
                }
            }
                                    
        }
        else
        {
            continue;
        }
    
    }
    if(!present)
        cout<<"Account not found"<<endl;
}


void readSavingsFile()
{
    cout << "Reading from savings file... ";
    ifstream inFile;                      //opens the Savings Account File
    inFile.open("Savings.txt");
    string text;


    if(inFile)
    {
        while(getline(inFile, text))
        {
            Savings currentAccount;

            if(text.find("S") == 0)
            {
                currentAccount.setAccountNumber(text);
                getline(inFile, text);

                double balance = stod(text.substr(0, text.find(" ")));
                currentAccount.setAccountBalance(balance);
                text = text.substr(text.find(" ") + 1, text.length());
                currentAccount.setOpenStatus(text.substr(0, text.find(" ")));
                text = text.substr(text.find(" ") + 1, text.length());
                currentAccount.setStatus(text.substr(0, text.find(" ")));
                text = text.substr(text.find(" ") + 1, text.length());
                currentAccount.setDate(text);

            }
            else
            {
                cout<<"Account not found"<<endl;
            }

            savingsAccounts.push_back(currentAccount);
        }
    }
    else
    {
        {
            cout<<"File not Found"<<endl;
        }
    }
    cout << "complete" << endl;
    inFile.close();
}


void updateSavingsFile()
{
    ofstream outFile;
    outFile.open("Savings.txt");

    
    for(int i = 0; i < savingsAccounts.size(); i++)
    {
        savingsAccounts[i].setDate(formatDate(getCurrentTime()));
        outFile<<savingsAccounts[i].getAccountNumber()<<'\n'<<savingsAccounts[i].getAccountBalance()<<" "<<
        savingsAccounts[i].getOpenStatus()<<" "<<savingsAccounts[i].getStatus()<<" "<< savingsAccounts[i].getDate()<<endl;

    }

    outFile.close();
    
}

//read from checking file
void readCheckingsFile()
{
    cout << "Reading from checkings file... ";
    ifstream inFile;                      //opens the checkings Account File
    inFile.open("checking.txt");
    string text;


    if(inFile)
    {
        while(getline(inFile, text))
        {
            Checking currentAccount;

            if(text.find("C") == 0)
            {
                currentAccount.setAccountNumber(text);
                getline(inFile, text);

                double balance = stod(text.substr(0, text.find(" ")));
                currentAccount.setAccountBalance(balance);
                text = text.substr(text.find(" ") + 1, text.length());
                currentAccount.setOpenStatus(text.substr(0, text.find(" ")));
                text = text.substr(text.find(" ") + 1, text.length());
                currentAccount.setFlag(text.substr(0, text.find(" ")));
                text = text.substr(text.find(" ") + 1, text.length());
                currentAccount.setDate(text);

            }
            else
            {
                cout<<"Account not found"<<endl;
            }

           checkingAccounts.push_back(currentAccount);
        }
    }
    else
    {
        {
            cout<<"File not Found"<<endl;
        }
    }
    cout << "complete" << endl;
    cout << " " << endl;
    inFile.close();
}

void updateCheckingsFile()
{
    ofstream outFile;
    outFile.open("checking.txt");
    for (int i = 0; i < checkingAccounts.size(); i++)
    {
        //checkingAccounts[i].setDate(formatDate(getCurrentTime()));
        checkingAccounts[i].setDate(formatDate(getCurrentTime()));
        outFile << checkingAccounts[i].getAccountNumber() << "\n" <<
        checkingAccounts[i].getAccountBalance() << " " << checkingAccounts[i].getOpenStatus() <<
        " " << checkingAccounts[i].getFlag()<<" "<< checkingAccounts[i].getDate()<<endl;
    }
    outFile.close();
}

