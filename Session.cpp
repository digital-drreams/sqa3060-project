#include <iostream>
#include <string>
#include "frontend.h"

using namespace std;



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
			handler = new Database();
			transactionLog = new std::string[0];
		} else if (sessionType == standardType){
			cout << "Session request successful." << endl;
			isPrivileged = false;
			isActive = true;
			handler = new Database();
			transactionLog = new std::string[0];
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
        if (!handler->verify(accountNumber, accountHolderName)){
            cout << "Enter amount to be deposited: ";
            cin >> depositValue;
			handler.changeBalance(accountNumber, accountHolderName, depositValue);
        } else {
            cout << "Invalid Account Identification number." << endl;
        }
    } else { // if user is standard, ask for account number
        cout << "Enter Account Identification number: ";
        cin >> accountNumber;
        if (!handler->verify(accountNumber, username)){
            cout << "Enter amount to be deposited: ";
            cin >> depositValue;
			handler.changeBalance(accountNumber, username, depositValue);
        } else {
            cout << "Invalid Account Identification number." << endl;
        }
    }
}

bool Session::changeplan(){
	string accountHolderName;
	int accountNumber;

	if (isPrivileged){
		cout << "Enter User Identification: ";
		cin >> accountHolderName;
		cout << "Enter account number: ";
		cin >> accountNumber;
		handler.changeplan(accountNumber, accountHolderName);
	}
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
				else { //Adds decimals if none were input
					buffer = buffer + ".00";
				}

				if (buffer.length() > 6) {
					cout << "Error: Amount input too long. Must be less than 100000.00";
				}
				


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
