#include <iostream>
#include <string>
#include "frontend.h"

using namespace std;

std::string* Session::transactionLog = new std::string[0];


bool Session::login(){
    if (!isActive){
        string sessionType;
        string adminType = "admin";
        string standardType = "standard";
        cout << "Welcome to the banking system." << endl;
        cout << "Enter session type: ";
        cin >> sessionType;
        if (sessionType == adminType){
            cout << "Session request successful." << endl;
            isPrivileged = true;
            isActive = true;
        } else if (sessionType == standardType){
            cout << "Session request successful." << endl;
            isPrivileged = false;
            isActive = true;
        } else {
            cout << "Invalid session type." << endl;
        }
    } else {
        cout << "Already logged in to a session" << endl;
    }
}

bool Session::logout(){
    if (isActive){
        isActive = false;
        cout << "Session terminated." << endl;
        for (int i = 0; i < sizeof(transactionLog); i++){
            cout << transactionLog[i];
        }
    } else {
        cout << "Error: Cannot logout outside of session." << endl;
    }
}

bool Session::withdrawal(){

}

bool Session::transfer(){

}

bool Session::deposit(){
        string accountHolderName;
        int accountNumber;
        float depositValue;
    if (isPrivileged){ // if user is ADMIN, ask for name and account number
        cout << "Enter Account holder Name: ";
        cin >> accountHolderName;
        cout << "Enter Account Identification number: ";
        cin >> accountNumber;
        // if (!Database.verify(accountNumber, accountHolderName)){
        //     cout << "Invalid Account Identification number." << endl;
        // }
    } else {
        cout << "Enter Account Identification number: ";
        cin >> accountNumber;
        if (!Database.verify(accountNumber, username)){
            cout << "Enter amount to be deposited: ";
            cout >> depositValue;
        }
    }
}

bool Session::changeplan(){

}

bool Session::discard(){

}

bool Session::disable(){

}

bool Session::create(){
    if (isActive) { //Is there a user logged in?
        if (isPrivileged) { //Are they an admin?
            string acc;
            cout << "Enter account holder name: ";
            cin >> acc;

            if (acc.length() > 20) { //Is the name format valid?
                cout << "Error: Account holder name must be 20 characters or less." << endl;
            }
            else {
                float balance;
                string buffer;
                cout << "Enter initial balance: ";
                cin >> buffer;
                        
                if (buffer.find('.') != -1) {
                    buffer = buffer.substr(0, buffer.find('.') + 2); //Truncates long decimals
                }
                else {

                }
                if (buffer.length() > 6)


            }
        }
        else {
            cout << "Permission denied." << endl;
        }
    }
    else {
        cout << "Error: Transaction not accepted outside of active session." << endl;
    }
}

/*
int main() {
  Session x;

  x.login();
  x.logout();
  return 0;
}
*/
