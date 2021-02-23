#include <iostream>
#include <string>
#include <typeinfo>
#include "frontend.h"

using namespace std;

bool Session::login(){
	// function takes care of login requests and returns true if login is succesful
	if (!isActive){ // if user is not already logged into a session, create a new session by logging in
		string sessionType;
		string adminType = "admin";
		string standardType = "standard";
		cout << "Welcome to the banking system." << endl;
		cout << "Enter session type: ";
		cin >> sessionType;
		if (sessionType == adminType){ // check if user request is admin.
			cout << "Session request successful." << endl;
			isPrivileged = true;
			isActive = true;
			handler = new Database();
			sessionLimit = 10000000.00;
			return true;
		} else if (sessionType == standardType){ // check if user request is standard.
			cout << "Session request successful." << endl;
			isPrivileged = false;
			isActive = true;
			handler = new Database();
			sessionLimit = 500.00;
			return true;
		} else { // if none of the above, return error
			cout << "Invalid session type." << endl;
			return false;
		}
	} else { // if user is already logged in, return error
		cout << "Already logged in to a session." << endl;
		return false;
	}
}

bool Session::logout(){
	if (isActive){ // cehck if user is logged in
		isActive = false;
		cout << "Session terminated." << endl;
		for (unsigned i = 0; i < transactionLog.size(); i++){ // output transaction log file
			cout << transactionLog[i];
		}
		return true;
	} else { // otherwise return error if user is not logged into a session
		cout << "Error: Cannot logout outside of session." << endl;
		return false;
	}
}

bool Session::withdrawal(){
	// function takes care of withdrawal requests and returns true if no issues have occured 
	string accountHolderName;
    int accountNumber;
    float withdrawValue;
	string floatType = "float";

    if (isPrivileged){ // if user is ADMIN, ask for name and account number
        cout << "Enter User Identification ";
        cin >> accountHolderName;
        cout << "Enter Account Identification number: ";
        cin >> accountNumber;
        if (handler->verify(accountNumber, accountHolderName)){ //verify account credentials
            cout << "Enter amount to be withdrawn: ";
            cin >> withdrawValue;
			if (typeid(withdrawValue).name() != floatType){
				cout << "Amount entered must be set to base10." << endl;
				return false;
			} else {
				if (handler->changeBalance(accountNumber, username, -withdrawValue)){ // withdraw requested amount if possible
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
				if (withdrawValue <= sessionLimit){ // check if withdrawal amount is within standard limit
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
	// function takes care of transfer requests and returns true if no issues have occured
	string accountHolderName;
    int sndrAccountNumber;
	int recpAccountNumber;
    float transferValue;
	string floatType = "float";
	float transferLimit = 1000.00; // session limit for standard login
	string logLine;
	string protocol = "04 ";
	string tab = "\t\t ";


	if (isPrivileged){ // check if user is logged in as admin
		cout << "Enter User Identification: ";
        cin >> accountHolderName;
        cout << "Enter host account number: ";
        cin >> sndrAccountNumber;
		cout << "Enter recipient account number: ";
		cin >> recpAccountNumber;
		if ((handler->verify(sndrAccountNumber, accountHolderName)) && (handler->verify(recpAccountNumber, accountHolderName))){
			cout << "Enter amount to transfer: ";
			cin >> transferValue;
			if (handler->changeBalance(sndrAccountNumber, accountHolderName, -transferValue)){ // check for sender balance, go ahead with transfer if possible
				handler->changeBalance(recpAccountNumber, accountHolderName, transferValue); 
				logLine  = protocol + accountHolderName + tab + to_string(recpAccountNumber) + " " + to_string(transferValue);
				transactionLog.push_back(logLine);
				return true;
			} else {
				cout << "Insufficient funds! Try again." << endl;
				return false;
			}
		} else {
			cout << "Account is invalid! Try again." << endl;
			return false;
		}

	} else { // if user is logged in as standard
		cout << "Enter host account number: ";
        cin >> sndrAccountNumber;
		cout << "Enter recipient account number: ";
		cin >> recpAccountNumber;
		if ((handler->verify(sndrAccountNumber, accountHolderName)) && (handler->verify(recpAccountNumber, accountHolderName))){
			cout << "Enter amount to transfer: ";
			cin >> transferValue;
			if (transferValue <= transferLimit){ // check if requested transfer value is within the standard limit for transfer
				if (handler->changeBalance(sndrAccountNumber, username, -transferValue)){ // check for sender balance, go ahead with transfer if possible
					handler->changeBalance(recpAccountNumber, username, transferValue);
					logLine  = protocol + username + tab + to_string(recpAccountNumber) + " " + to_string(transferValue);
					transactionLog.push_back(logLine);
					return true;
				} else {
					cout << "Insufficient funds! Try again." << endl;
					return false;
				}
			} else {
				cout << "Transfer failed! The amount exceeds the session limit at $1000.00." << endl;
				return false;
			}
		} else {
			cout << "Account is invalid! Try again." << endl;
			return false;
		}
	}
}

bool Session::deposit(){
	// function takes care of deposit requests and returns true if no issues have occured.
    string accountHolderName;
    int accountNumber;
    float depositValue;

    if (isPrivileged){ // check if user is admin, ask for name and account number
        cout << "Enter Account holder Name: ";
        cin >> accountHolderName;
        cout << "Enter Account Identification number: ";
        cin >> accountNumber;
        if (handler->verify(accountNumber, accountHolderName)){
            cout << "Enter amount to be deposited: ";
            cin >> depositValue;
			handler->changeBalance(accountNumber, accountHolderName, depositValue); // depositre requested value
			return true;
		} else {
            cout << "Invalid Account Identification number." << endl;
			return false;
		}
    } else { // check if user is standard, ask for account number
        cout << "Enter Account Identification number: ";
        cin >> accountNumber;
        if (handler->verify(accountNumber, username)){
            cout << "Enter amount to be deposited: ";
            cin >> depositValue;
			handler->changeBalance(accountNumber, username, depositValue); // deposit requested value
			return true;
        } else {
            cout << "Invalid Account Identification number." << endl;
			return false;
        }
    }
	return true; 
}

bool Session::changeplan(){
	// functions takes care of change plan requests, returns true if no issues have occured.
	string accountHolderName;
	int accountNumber;
	string logLine;
	string protocol = "08 ";
	string tab = "\t\t ";
	string stdAccountPlan = "SP";
	string nonStdAccountPlan = "NP";

	if (isPrivileged){ // check if user is logged in as admin, this is an admin operation only
		cout << "Enter User Identification: ";
		cin >> accountHolderName;
		cout << "Enter account number: ";
		cin >> accountNumber;
		if (handler->changeplan(accountNumber, accountHolderName)){ // change plan and output the change to the transaction log array
			logLine = protocol + accountHolderName + tab + to_string(accountNumber) + " 00000.00 " + stdAccountPlan;
			transactionLog.push_back(logLine);
		} else {
			logLine = protocol + " " + accountHolderName + tab + to_string(accountNumber) + " 00000.00 " + nonStdAccountPlan;
			transactionLog.push_back(logLine); 
		}
		return true;
	} else {
		return false;
	}
}

bool Session::discard(){
	if (isActive) { //Is there a user logged in?
		if (isPrivileged) { //Are they an admin?
			string name;
			cout << "Enter account holder name: ";
			cin >> name;

			if (name.length() > 20) { //Is the name format valid?
				cout << "Error: Account holder name must be 20 characters or less." << endl;
			}
			else {
				int id;
				cout << "Enter account identifiction number: ";
				cin >> id;

				if (handler->verify(id, name)) { //Does such an account exist?
					if (handler->discard(id, name)) { //Was the discard successful?
						cout << "Account deleted successfully." << endl;
						return true;
					}
					else {
						cout << "Account has a nonzero balance and cannot be deleted." << endl 
							 << "Please make a withdrawal or pay any outstanding fees first." << endl;
					}
				}
				else {
					cout << "Invalid account identification number." << endl;
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
	return false;
}

bool Session::disable(){
    string accountHolderName;//variable holders
	int accountNumber;
	if(isActive){ //checks if the user is active
		if(isPrivileged){ //Checks if the user is signed in on admin
			cout << "Enter User Identification: "; //User inputs their information
			cin >> accountHolderName;
			cout << "Enter account number: ";
			cin >> accountNumber;
			if(!handler->verify(accountNumber,accountHolderName)){ //Verify the account is owned by the user
				//Disable account
				handler->disable(accountNumber, accountHolderName);

				//Output for the user
				cout << "Account " << accountNumber << " disabled successfully" << endl;
			}
			//If the account doesn't belong to the user
			else{
				cout << "Error: Account " << accountNumber << " does not exist" << endl;
			}
		//If the user is not signed in on admin
		}else{
			cout << "Permission Denied: Must be an admin to disable an account" << endl;
		}
	}
	//Returns true after the function successfully executes
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
				
				balance = floor(balance * 100.0) / 100.0; //Rounds to two decimal places
				
				if (balance >= 100000.00) { //Is the balance input too large?
					cout << "Error: Initial balance must be less than $100000.00." << endl;
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
	return false;
}
