

#include "objects.h"
#include <string>
#include <iostream>
#include <vector>
#include <istream>

using namespace std;

void createNewAccount();
bool allDigits(string s, int len);
bool isDigit(char c);

int locker=0; //variable to lock in which 

vector <Bank> accounts;

int main(){
    bool play = true;
    int choice;
    string tempAN;
    Bank tempAccount;
    //readFile function needs to be called first
    //v1.6
    //jay test
    while(play){
        cout<<"Version 1.6"<<endl;
        cout<<"Welcome to the bank account system, would you like to [1] Open an account, [2] Login, [3] exit: ";
        cin >> choice;
        if (choice==1||choice==2||choice==3){
            switch(choice){
                case 1:
                    //todo creating a new account function
                    break;
                case 2:
                    cout<<"Enter your account number beginning with the type [C] Checkings [S] Savings: ";
                    cin>>tempAN;
                    if(allDigits(tempAN.substr(1,tempAN.size()),8)){
                        //todo login stuffs;
                    }
                    else{
                        cout<<"Invalid input!"<<endl;
                        play=true;
                        break;
                    }
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