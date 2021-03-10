#include <iostream>
#include <string>
#include <typeinfo>
#include "frontend.h"
#include <fstream>
#include <vector>

using namespace std;

Session::Session() {
	string accountFileLocation = "accounts.txt";
	string transactFileLocation = "transact.txt";
};

Session::Session(string inLocation, string outLocation) {
	string accountFileLocation = inLocation;
	string transactFileLocation = outLocation;
};

string refactorUserInput(string prevString, string output) {
	// Checks to see if the end of the prevString has a new line whitespace
	// If the end of the previous string does not have a new line, append and a new line
	// to the start of the output string and return the resulting string
	if (prevString.length() > 2) {
		if (prevString.substr((prevString.length()-2), prevString.length()) != "\n") {
			return "\n" + output;
		}
		else {
			// If there is an existing newline whitespace at the end of the previous string,
			// return the output string as is
			return output;
		}
	}
	else {
		return "\n" + output;
	}
}

bool Session::login(){
	// function takes care of login requests and returns true if login is succesful
	if (!isActive){ // if user is not already logged into a session, create a new session by logging in
		string sessionType;
		string adminType = "admin";
		string standardType = "standard";
		const int ADMIN_BALANCE = 10000000.00;

		cout << "Welcome to the banking system." << endl;
		cout << "Enter session type: ";
		getline(cin, sessionType);
		sessionType = sessionType.substr(0, sessionType.find_last_not_of(char(13)) + 1);

		if (sessionType == adminType){ // check if user request is admin.
			isPrivileged = true;
			withdrawLimit = ADMIN_BALANCE;
			transferLimit = ADMIN_BALANCE;
			ECLimit = ADMIN_BALANCE;
			CQLimit = ADMIN_BALANCE;
			FILimit = ADMIN_BALANCE;

		} else if (sessionType == standardType){ // check if user request is standard.
			cout << refactorUserInput(sessionType, "Enter user identification: ");
			getline(cin, username);
			username = username.substr(0, username.find_last_not_of(char(13)) + 1);
			isPrivileged = false;
			withdrawLimit = 500.00;
			transferLimit = 1000.00;
			ECLimit = 2000.00;
			CQLimit = 2000.00;
			FILimit = 2000.00;
			
		} else { // if none of the above, return error
			cout << refactorUserInput(sessionType, "Invalid session type.") << endl;
			return false;
		}
		cout << refactorUserInput(sessionType, "Session request successful.") << endl;
		isActive = true;
		handler = new Database(accountFileLocation);
		return true;

	} else { // if user is already logged in, return error
		cout << "Session request failed." << endl;
		return false;
	}
}

bool Session::logout(){
	if (isActive){ // cehck if user is logged in
		isActive = false;
		cout << "Session terminated." << endl;
		transactionLog.push_back("00                      00000 00000.00   ");
		ofstream logFile(transactFileLocation);
		for (unsigned int i = 0; i < transactionLog.size(); i++){ // output transaction log file
			logFile << transactionLog.at(i) << endl;
		}
		logFile.close();
		return true;
	} else { // otherwise return error if user is not logged into a session
		cout << "Error: Cannot logout outside of session." << endl;
		return false;
	}
}

bool Session::withdrawal(){
	// function takes care of withdrawal requests and returns true if no issues have occured 
    int accountNumber;
    float withdrawValue;
	string floatType = "f";
	string temp;
	char* logLine = new char[41];

    if (isActive){ 
		if (isPrivileged) { // if user is ADMIN, ask for name
			cout << "Enter account holder name: ";
			getline(cin, username);
			username = username.substr(0, username.find_last_not_of(char(13)) + 1);
			cout << refactorUserInput(username, "Enter account identification number: ");
		}
		else {
			cout << "Enter account identification number: ";
		}

		getline(cin, temp);
		temp = temp.substr(0, temp.find_last_not_of(char(13)) + 1);
		accountNumber = stoi(temp);
        
		if (handler->verify(accountNumber, username)){ //verify account credentials
			cout << refactorUserInput(to_string(accountNumber), "Enter amount to be withdrawn: ");
            getline(cin, temp);
			temp = temp.substr(0, temp.find_last_not_of(char(13)) + 1);
			withdrawValue = stof(temp);

			if (typeid(withdrawValue).name() != floatType){
				cout << refactorUserInput(to_string(withdrawValue), "Amount entered must be in standard base10 numeric format (decimal accepted).") << endl;
				return false;
			} else {
				if (withdrawValue <= withdrawLimit) { // check if withdrawal amount is within standard limit
					if (handler->changeBalance(accountNumber, username, -withdrawValue)){ // withdraw requested amount if possible
						sprintf(logLine, "01 %-20s %05i %08.2f   ", username.data(), accountNumber, withdrawValue);
						transactionLog.push_back(string(logLine));
						withdrawLimit -= withdrawValue;
						return true;
					} else {
						cout << refactorUserInput(to_string(withdrawValue), "Amount entered cannot exceed the account balance.") << endl;
						return false;
					}
				}
				else {
					cout << refactorUserInput(to_string(withdrawValue), "Amount entered exceeds the limit.") << endl;
					return false;
				}
			}
		} else {
			cout << refactorUserInput(to_string(accountNumber), "Invalid account identification number.") << endl;
			return false;
		}
    } else {
		cout << "Error: Transaction not accepted outside of active session." << endl;
		return false;
	}
}

bool Session::transfer(){
	// function takes care of transfer requests and returns true if no issues have occured
    int sndrAccountNumber;
	int recpAccountNumber;
    float transferValue;
	char* logLine = new char[41];
	string temp; // used to aid input handling/casting


	if (isPrivileged && isActive){ // check if user is logged in as admin
		if (isPrivileged) {
			cout << "Enter user identification: ";
			getline(cin, username);
			username = username.substr(0, username.find_last_not_of(char(13)) + 1);
			cout << refactorUserInput(username, "Enter account number: ");
		}
		else {
        	cout << "Enter host account number: ";
		}

		getline(cin, temp);
		temp = temp.substr(0, temp.find_last_not_of(char(13)) + 1);
		sndrAccountNumber = stoi(temp);
        
		cout << refactorUserInput(to_string(sndrAccountNumber), "Enter recipient account number: ");
		getline(cin, temp);
		temp = temp.substr(0, temp.find_last_not_of(char(13)) + 1);
		recpAccountNumber = stoi(temp);
		
		if ((handler->verify(sndrAccountNumber, username)) && (handler->verify(recpAccountNumber, username))){
			cout << refactorUserInput(to_string(recpAccountNumber), "Enter amount to transfer: ");
			getline(cin, temp);
			temp = temp.substr(0, temp.find_last_not_of(char(13)) + 1);
			transferValue = stof(temp);
			if (transferValue > transferLimit){
				cout << refactorUserInput(to_string(transferValue), "Transfer failed: Amount exceeds session limit.") << endl;
			} else {
				if (handler->changeBalance(sndrAccountNumber, username, -transferValue)){ // check for sender balance, go ahead with transfer if possible
					handler->changeBalance(recpAccountNumber, username, transferValue); 
					sprintf(logLine, "04 %-20s %05i %08.2f   ", username.data(), sndrAccountNumber, transferValue);
					transactionLog.push_back(string(logLine));
					sprintf(logLine, "04 %-20s %05i %08.2f   ", username.data(), recpAccountNumber, transferValue);
					transactionLog.push_back(string(logLine));
					cout << refactorUserInput(to_string(transferValue), "Transfer successful.") << endl;
					return true;
				} else {
					cout << refactorUserInput(to_string(transferValue), "Amount entered cannot exceed the account balance.") << endl;
					return false;
				}
			}
		} else {
			cout << refactorUserInput(to_string(recpAccountNumber), "Account number invalid.") << endl;
			return false;
		}
	} else {
		cout << "Error: Transaction not accepted outside of active session." << endl;
		return false;
	}
}

bool Session::deposit(){
	// function takes care of deposit requests and returns true if no issues have occured.
    int accountNumber;
    float depositValue;
	char* logLine = new char[41];
	string temp; // used to aid input handling/casting

    if (isActive){ // check if user is admin, ask for name
		if (isPrivileged) {
			cout << "Enter account holder name: ";
			getline(cin, username);
			username = username.substr(0, username.find_last_not_of(char(13)) + 1);
			cout << refactorUserInput(username, "Enter account holder name: ");
		}
		else {
			cout << "Enter account identification number: ";
		}

		getline(cin, temp);
		temp = temp.substr(0, temp.find_last_not_of(char(13)) + 1);
		accountNumber = stoi(temp);

        if (handler->verify(accountNumber, username)){
			cout << refactorUserInput(to_string(accountNumber), "Enter amount to be deposited: ");
			getline(cin, temp);
			temp = temp.substr(0, temp.find_last_not_of(char(13)) + 1);
			depositValue = stof(temp);
            
			handler->changeBalance(accountNumber, username, depositValue); // deposit requested value
			sprintf(logLine, "04 %-20s %05i %08.2f   ", username.data(), accountNumber, depositValue);
			transactionLog.push_back(string(logLine));
			return true;
		} else {
			cout << refactorUserInput(to_string(accountNumber), "Invalid account identification number.") << endl;
			return false;
		}
    } else {
		cout << "Error: Transaction not accepted outside of active session." << endl;
		return false;
	} 
}

bool Session::changeplan(){
	// functions takes care of change plan requests, returns true if no issues have occured.
	int accountNumber;
	char* logLine = new char[41];
	string temp; // used to aid input handling/casting

	if (isPrivileged && isActive){ // check if user is logged in as admin, this is an admin operation only
		cout << "Enter account holder name: ";
		getline(cin, username);
		username = username.substr(0, username.find_last_not_of('\r'));
		if (username.length() > 20) { //Is the name format valid?
			cout << refactorUserInput(username, "Error: Account holder name must be 20 characters or less.") << endl;
			return false;
		}
		else {
			cout << "Enter account identification number: ";
			getline(cin, temp);
			temp = temp.substr(0, temp.find_last_not_of(char(13)) + 1);
			accountNumber = stoi(temp);

			string plan;
			if (handler->changeplan(accountNumber, username)) { // change plan and output the change to the transaction log array
				plan = "SP";
				cout << refactorUserInput(temp, "Your non-student payment plan has been changed to a student payment plan (SP).") << endl;
			}
			else {
				plan = "NP";
				cout << refactorUserInput(temp, "Your student payment plan has been changed to a non-student payment plan (NP).") << endl;
			}
			sprintf(logLine, "08 %-20s %05i %08.2f %2s", username.data(), accountNumber, 0.0, plan.data());
			transactionLog.push_back(string(logLine));
			return true;
		}
	} else if (!isPrivileged && isActive) {
		cout << "Must have Admin privilege." << endl;
		return false;
	} else {
		cout << "Error: Transaction not accepted outside of active session." << endl;
		return false;
	}
}

bool Session::discard(){
	char* logLine = new char[41];
	int id;
	string temp; // used to aid input handling/casting

	if (isActive) { //Is there a user logged in?
		if (isPrivileged) { //Are they an admin?
			cout << "Enter account holder name: ";
			getline(cin, username);
			username = username.substr(0, username.find_last_not_of(char(13)) + 1);

			if (username.length() > 20) { //Is the name format valid?
				cout << refactorUserInput(username, "Error: Account holder name must be 20 characters or less.") << endl;
			}
			else {
				cout << refactorUserInput(username, "Enter account identifiction number: ");
				getline(cin, temp);
				temp = temp.substr(0, temp.find_last_not_of(char(13)) + 1);
				id = stoi(temp);

				if (handler->verify(id, username)) { //Does such an account exist?
					if (handler->discard(id, username)) { //Was the discard successful?
						sprintf(logLine, "06 %-20s %05i %08.2f   ", username.data(), id, 0.0);
						transactionLog.push_back(string(logLine));
						cout << refactorUserInput(to_string(id), "Account deleted successfully.") << endl;
						return true;
					}
					else {
						cout << refactorUserInput(to_string(id), "Given account has a nonzero balance and cannot be deleted.") << endl;
						cout << "Please make a withdrawal or pay any outstanding fees first." << endl;
					}
				}
				else {
					cout << refactorUserInput(to_string(id), "Invalid account identification number.") << endl;
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
    //variable holders
	char* logLine = new char[41];
	int accountNumber;
	string temp; // used to aid input handling/casting

	if(isActive){ //checks if the user is active
		if(isPrivileged){ //Checks if the user is signed in on admin
			cout << "Enter account holder name: "; //User inputs their information
			getline(cin, username);
			username = username.substr(0, username.find_last_not_of(char(13)) + 1);

			cout << refactorUserInput(username, "Enter account identification number: ");
			getline(cin, temp);
			temp = temp.substr(0, temp.find_last_not_of(char(13)) + 1);
			accountNumber = stoi(temp);

			if(handler->verify(accountNumber, username)){ //Verify the account is owned by the user
				//Disable account
				handler->disable(accountNumber, username);
				sprintf(logLine, "07 %-20s %05i %08.2f   ", username.data(), accountNumber, 0.0);
				transactionLog.push_back(string(logLine));

				//Output for the user
				cout << refactorUserInput(to_string(accountNumber), "Account disabled successfully.") << endl;
			}
			//If the account doesn't belong to the user, or doesn't exist
			else{
				cout << refactorUserInput(to_string(accountNumber), "Invalid account identification number.") << endl;
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
	string temp; // used to aid input handling/casting

	if (isActive) { //Is there a user logged in?
		if (isPrivileged) { //Are they an admin?
			cout << "Enter account holder name: ";
			getline(cin, username);
			username = username.substr(0, username.find_last_not_of(char(13)) + 1);

			if (username.length() > 20) { //Is the name format valid?
				cout << refactorUserInput(username, "Name must be shorter than 20 characters.") << endl;
			}
			else {
				float balance;

				cout << refactorUserInput(username, "Enter initial balance: ");
				getline(cin, temp);
				temp = temp.substr(0, temp.find_last_not_of(char(13)) + 1);
				balance = stof(temp);
				
				balance = floor(balance * 100.0) / 100.0; //Rounds to two decimal places
				
				if (balance >= 100000.00) { //Is the balance input too large?
					cout << refactorUserInput(to_string(balance), "Initial balance can be at most $99999.99.") << endl;
				}
				else {
					int num = handler->create(username, balance);
					if (to_string(balance).length() > 2 && to_string(balance).substr((to_string(balance).length()-2), to_string(balance).length()) != "\n") {
						printf("\nAccount created successfully; account #%05i", num);
					} else {
						printf("Account created successfully; account #%05i", num);
					}
					cout << endl;
					char* logLine = new char[41];
					sprintf(logLine, "05 %-20s %05i %08.2f   ", username.data(), num, balance);
					transactionLog.push_back(string(logLine));
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

bool Session::paybill() {
	string temp; // used to aid input handling/casting

	if (isActive) { //Is there a user logged in?
		if (isPrivileged) { //If they're an admin, get the account name
			cout << "Enter account holder name: ";
			getline(cin, username);
			username = username.substr(0, username.find_last_not_of(char(13)) + 1);

			if (username.length() > 20) { //Is the name format valid?
				cout << "Error: Account holder name must be 20 characters or less." << endl;
				return false;
			}
			cout << refactorUserInput(username, "Enter account number: ");
		}
		else {
			cout << "Enter account number: ";
		}

		int acc;
		cin >> acc;
		
		if (handler->verify(acc, username)) { //Verify the account is owned by the user
			string target;
			cout << refactorUserInput(to_string(acc), "Possible bill payees, [shorthands bracketed]:") << endl;
			cout << "The Bright Light Electric Company [EC]" << endl
				 << "Credit Card Company Q [CQ]" << endl << "Fast Internet, Inc. [FI]" << endl << "Enter bill holder to pay: ";
			getline(cin, target);
			target = target.substr(0, target.find_last_not_of(char(13)) + 1);
			
			if (target == "EC" || target == "CQ" || target == "FI") {
				float amount;

				cout << refactorUserInput(target, "Enter amount to pay: ");
				getline(cin, temp);
				temp = temp.substr(0, temp.find_last_not_of(char(13)) + 1);
				amount = stof(temp);

				if ((target == "EC" && ECLimit - amount >= 0.0) || (target == "CQ" && CQLimit - amount >= 0.0) || (target == "FI" && FILimit - amount >= 0.0)) {
					char* logLine = new char[41];
					
					if (handler->changeBalance(acc, username, -amount)) { // pay using requested amount, if possible
						sprintf(logLine, "03 %-20s %05i %08.2f %2s", username.data(), acc, amount, target.data());
						transactionLog.push_back(string(logLine));

						if (target == "EC") {
							ECLimit -= amount;
						}
						else if (target == "CQ") {
							CQLimit -= amount;
						}
						else if (target == "FI") {
							FILimit -= amount;
						}
						else { //It should be impossible to get here
							return false;
						}
						cout << refactorUserInput(to_string(amount), "Bill payment successful.") << endl;
					}
					else {
						cout << refactorUserInput(to_string(amount), "Amount entered exceeds current account balance.") << endl;
						return false;
					}
					return true;
				}
				else {
					cout << refactorUserInput(to_string(amount), "Amount exceeds session bill payment limit.") << endl;
				}
			}
			else {
				cout << refactorUserInput(target, "Invalid bill holder.") << endl;
			}
		}
		else {
			cout << refactorUserInput(to_string(acc), "Invalid account identification number.") << endl;
		}
	}
	else {
		cout << "Error: Transaction not accepted outside of active session." << endl;
	}
	return false;
}