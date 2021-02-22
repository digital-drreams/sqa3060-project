#include <iostream>
#include <string>
#include <typeinfo>
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
			sessionLimit = 10000000.00;
			return true;
		} else if (sessionType == standardType){
			cout << "Session request successful." << endl;
			isPrivileged = false;
			isActive = true;
			handler = new Database();
			sessionLimit = 500.00;
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
		for (int i = 0; i < sizeof(transactionLog); i++){
			cout << transactionLog[i];
		}
		return true;
	} else {
		cout << "Error: Cannot logout outside of session." << endl;
		return false;
	}
}

bool Session::withdrawal(){
	string accountHolderName;
    int accountNumber;
    float withdrawValue;
	string floatType = "float";

    if (isPrivileged){ // if user is ADMIN, ask for name and account number
        cout << "Enter Account holder Name: ";
        cin >> accountHolderName;
        cout << "Enter Account Identification number: ";
        cin >> accountNumber;
        if (handler->verify(accountNumber, accountHolderName)){
            cout << "Enter amount to be withdrawn: ";
            cin >> withdrawValue;
			if (typeid(withdrawValue).name() != floatType){
				cout << "Amount entered must be set to base10." << endl;
				return false;
			} else {
				if (handler->changeBalance(accountNumber, username, -withdrawValue)){
					return true;
				} else {
					return false;
				}
			}
		} else {
			cout << "Invalid Account Identification number." << endl;
			return false;
		}
    } else { // if user is standard, ask for account number
        cout << "Enter Account Identification number: ";
        cin >> accountNumber;
        if (handler->verify(accountNumber, username)){
            cout << "Enter amount to be withdrawn: ";
            cin >> withdrawValue;
			if (typeid(withdrawValue).name() != floatType){
				cout << "Amount entered must be set to base10." << endl;
				return false;
			} else {
				if (withdrawValue <= sessionLimit){
					if (handler->changeBalance(accountNumber, username, -withdrawValue)){
						return true;
					} else {
						return false;
					}
				} else {
					cout << "Amount entered exceeds the limit." << endl;
					return false;
				}
			}
        } else {
            cout << "Invalid Account Identification number." << endl;
			return false;
        }
    }
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
        if (handler->verify(accountNumber, accountHolderName)){
            cout << "Enter amount to be deposited: ";
            cin >> depositValue;
			handler->changeBalance(accountNumber, accountHolderName, depositValue);
			return true;
		} else {
            cout << "Invalid Account Identification number." << endl;
			return false;
		}
    } else { // if user is standard, ask for account number
        cout << "Enter Account Identification number: ";
        cin >> accountNumber;
        if (handler->verify(accountNumber, username)){
            cout << "Enter amount to be deposited: ";
            cin >> depositValue;
			handler->changeBalance(accountNumber, username, depositValue);
			return true;
        } else {
            cout << "Invalid Account Identification number." << endl;
			return false;
        }
    }
	return true; 
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
			logLine = protocol + " " + accountHolderName + tab + to_string(accountNumber) + "00000.00" + stdAccountPlan;
			transactionLog.push_back(logLine);
		} else {
			logLine = protocol + " " + accountHolderName + tab + to_string(accountNumber) + "00000.00" + nonStdAccountPlan;
			transactionLog.push_back(logLine); 
		}
		return true;
	} else {
		return false;
	}
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
			}
			else {
				float balance;
				cout << "Enter initial balance: ";
				cin >> balance;

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
