#include <iostream>
#include "frontend.h"

using namespace std;

Database::Database(void) {
	// Initializes the head and tail account values
	head = NULL;
	tail = NULL;
	fileLocation = "accounts.txt";

	generateAccounts(fileLocation);
}

Database::Database(string bankLocation) {
	// Initializes the head and tail account values
	head = NULL;
	tail = NULL;
	fileLocation = bankLocation;

	generateAccounts(fileLocation);
}

Database::~Database(void) {
	// Variable Declaration
	accountNode* current = head;
	accountNode* prev = NULL;
	accountNode* temp;

	// Deletes all accounts from the database
	if (head != 0) {
		while (current != 0) {
			temp = current;
			head = current->next;
			delete temp;
			current = head;
		}
	}
}

bool Database::changeBalance(int id, string name, float amount) {
	// Obtains specified account from database
	accountNode* foundAccount = findAccount(id, name);
	if (verify(id, name) == true) {
		// Obtains current balance of the account
		float currentBalance = foundAccount->account->balance;
		// Returns false if the current transaction will cause the account balance
		// to have a negative balance
		if (currentBalance + amount < 0) {
			return false;
		}
		// Otherwise, perform transaction on account
		else {
			foundAccount->account->balance = currentBalance + amount;
			return true;
		}
	}

	return false;
}

int Database::create(string name, float initBalance) {
	// Creates a new instance of the account class using the
	// provided account holder name and initial balance

	if (tail != 0) {
		// Obtains account number of next account to be made
		int newID = tail->account->number + 1;
		// Creates a new instance of the account class
		Account* account = new Account(newID, name, initBalance);

		// Reassigns linked list node values to accomodate for the newly added account
		accountNode* tmp = new accountNode;
		tmp->account = account;

		tail->next = tmp;
		tail = tmp;

		// Returns the ID of the newly created account
		return newID;
	}
	else {
		// Creates a new instance of the account class
		Account *account = new Account(1, name, initBalance);
		// Reassigns linked list node values to accomodate for the newly added account
		accountNode* tmp = new accountNode;
		tmp->account = account;
		tmp->next = NULL;
		
		head = tmp;
		tail = tmp;

		// Returns the account number of the newly created account number
		return 1;
	}
}

int Database::create(string name, float initBalance, int accountNo) {
	// As above, but attempts to assign the accountNo given.
	// Returns the account number of the created account.

	Account* account = new Account(accountNo, name, initBalance);
	accountNode* tmp = new accountNode;
	tmp->account = account;

	if (tail != 0) {
		tail->next = tmp;
	}
	else {
		tmp->next = NULL;

		head = tmp;
	}

	tail = tmp;

	return accountNo;
}

bool Database::discard(int id, string name) {
	// Variable Declaration
	accountNode* current = head;
	accountNode* prev = NULL;
	accountNode* temp;

	// When accounts exist in the database, iterate through all the accounts to find a matching
	// account that is associated to the account name provided
	if (head != 0) {
		while (current != 0) {
			// Obtains account number of the current account
			int currentID = current->account->number;
			
			// Deletes the current account if and only if the current account number matches 
			// the provided account number, belongs to the provided account holder
			// and contains a zero balance
			if (currentID == id && current->account->balance == 0 && verify(id, name) == true) {
				if (prev != NULL) {
					temp = current;
					prev->next = current->next;
					current = prev->next;
					delete temp;
				}
				else {
					temp = current;
					head = current->next;
					delete temp;
					current = head;
				}
				// Returns true to indicate that the account was successfully deleted
				return true;
			}
			// Iterates to the next node in the database linked list
			else {
				prev = current;
				current = current->next;
			}
		}
		// Returns false indicating that an account was not deleted
		return false;
	}
	// Returns false when no accounts exist in the database
	else {
		return false;
	}
}

void Database::disable(int id, string name) {
	// Obtains specified account from database
	accountNode* foundAccount = findAccount(id, name);
	if (verify(id, name) == true) {
		// Sets account to a disabled state
		foundAccount->account->isDisabled = true;
	}
}

bool Database::changeplan(int id, string name) {
	// Obtains specified account from database
	accountNode* foundAccount = findAccount(id, name);
	if (verify(id, name) == true) {
		// Toggles the status of the account between student and non-student
		foundAccount->account->isStudent = !foundAccount->account->isStudent;

		// Returns current state of account
		return foundAccount->account->isStudent;
	}
	return foundAccount->account->isStudent;
}

bool Database::verify(int id, string name) {
	// Obtains specified account from database
	accountNode* foundAccount = findAccount(id, name);

	// Checks if account holder name of the found account matches the
	// provided name
	if (foundAccount != NULL && strcmp(const_cast<char*>(name.c_str()), const_cast<char*>(foundAccount->account->holder.c_str())) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Database::isDisabled(int id, string name) {
	// Obtains specified account from database
	accountNode* foundAccount = findAccount(id, name);
	if (foundAccount != NULL) {
		// Returns the disabled status of the found account
		return foundAccount->account->isDisabled;
	}
	return NULL;
	
}

bool Database::generateAccounts(string testType) {
	// Variable Declaration
	string line;
	
	// Opens and reads through the provided input file
	ifstream inputFile(fileLocation + testType + "_in.txt");
	
	// Iterates through each line in the input file and checks to see if
	// a transaction type was read
	if (inputFile.is_open())
	{
		while (getline(inputFile, line))
		{
			string name;
			int accountNo;
			float balance;

			if (name != "END_OF_FILE") {
				accountNo = stoi(line.substr(0, 5));
				name = line.substr(6, line.find_last_of(' ', 26));
				balance = stof(line.substr(29, 37));

				create(name, balance, accountNo);
			}
		}
		// Closes input file once read
		inputFile.close();
		return true;
	}
	// Returns false if file cannot be opened
	return false;
}

accountNode* Database::findAccount(int id, string name) {
	// Variable Declaration
	accountNode* current = head;

	// When the database contains accounts, iterate through each node in the accounts linked list
	// until an account that matches the provided account ID is found
	if (head != 0) {
		while (current != 0) {
			int currentID = current->account->number;
			
			if (currentID == id) {
				return current;
			}

			current = current->next;
		}
	}

	// Returns NULL if an account is not found
	return NULL;
}