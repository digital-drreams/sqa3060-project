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
 			// changed to a vector
			return true;
		} else if (sessionType == standardType){
			cout << "Session request successful." << endl;
			isPrivileged = false;
			isActive = true;
			handler = new Database();
 			// changed to a vector
			return true;
		} else {
			cout << "Invalid session type." << endl;
			return false;
		}
	} else {
		cout << "Already logged in to a session" << endl;
		return false;
	}
}

bool Session::logout(){
	if (isActive){
		isActive = false;
		cout << "Session terminated." << endl;
		for (unsigned i = 0; i < transactionLog.size(); i++){
			cout << transactionLog[i];
		}
		return true;
	} else {
		cout << "Error: Cannot logout outside of session." << endl;
		return false;
	}
}

bool Session::withdrawal(){
	return true;
}

bool Session::transfer(){
	return true;
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
			handler->changeBalance(accountNumber, accountHolderName, depositValue);
		} else {
            cout << "Invalid Account Identification number." << endl;
		}
    } else { // if user is standard, ask for account number
        cout << "Enter Account Identification number: ";
        cin >> accountNumber;
        if (!handler->verify(accountNumber, username)){
            cout << "Enter amount to be deposited: ";
            cin >> depositValue;
			handler->changeBalance(accountNumber, username, depositValue);
        } else {
            cout << "Invalid Account Identification number." << endl;
        }
    }
	return true; //Placeholder, arrange return properly when complete (consider changing returntype to void)
}

bool Session::changeplan(){
	// true if turned to student and false other3ise
	string accountHolderName;
	int accountNumber;
	string logLine;
	string protocol = "08";
	string tab = "\t\t ";
	string stdAccountPlan = "SP";
	string nonStdAccountPlan = "NP";

	if (isPrivileged){
		cout << "Enter User Identification: ";
		cin >> accountHolderName;
		cout << "Enter account number: ";
		cin >> accountNumber;
		if (handler->changeplan(accountNumber, accountHolderName)){
			logLine = protocol + " " + accountHolderName + tab + to_string(accountNumber) + "0000.00" + stdAccountPlan;
			transactionLog.push_back(logLine); // changed to vector
		} else {
			logLine = protocol + " " + accountHolderName + tab + to_string(accountNumber) + "0000.00" + nonStdAccountPlan;
			transactionLog.push_back(logLine); // changed to a vector
		}
	}
	return true; //Placeholder, arrange return properly when complete (consider changing returntype to void)
}

bool Session::discard(){
	return true;

}

bool Session::disable(){
	return true;
}

bool Session::create(){
	if (isActive) { //Is there a user logged in?
		if (isPrivileged) { //Are they an admin?
			string acc;
			cout << "Enter account holder name: ";
			cin >> acc;

			if (acc.length() > 20) { //Is the name format valid?
				cout << "Error: Account holder name must be 20 characters or less." << endl;
				return false;
			}
			else {
				float balance;
				cout << "Enter initial balance: ";
				cin >> balance;
				
				balance = floor(balance * 100.0) / 100.0; //Rounds to two decimal places
				
				if (balance >= 100000.00) { //Is the balance input too large?
					cout << "Error: Initial balance must be less than $100000.00." << endl;
					return false;
				}
				else {
					printf("Account created successfully; account #%05i", handler->create(acc, balance));
					cout << endl;
					return true;
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
	return true; //Placeholder, arrange return properly when complete (consider changing returntype to void)
}
