#include <iostream>
#include "frontend.h"

using namespace std;

Database::Database(void) {
	head = NULL;
	tail = NULL;
	cout << "Database is being created" << endl;
}

Database::~Database(void) {
	cout << "Database is being deleted" << endl;
}

void Database::setFileLocation(string location) {
	fileLocation = location;
}

string Database::getFileLocation(void) {
	return fileLocation;
}

bool Database::changeBalance(int accountNumber, string accountHolder, float amount) {
	cout << "Changing Balance" << endl;

	return true;
}

int Database::create(string accountHolder, float initBalance) {
	// Creates a new instance of the account class using the
	// provided account holder name and initial balance

	if (tail != 0) {
		// Obtains account number of next account to be made
		int newID = tail->account->number + 1;
		// Creates a new instance of the account class
		Account* account = new Account(newID, accountHolder, initBalance);

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
		Account *account = new Account(1, accountHolder, initBalance);
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

void Database::discard(int id, string name) {
	// // Variable Declaration
	// accountNode* current = head;
	// accountNode* prev = NULL;
	// accountNode* temp;

	// // When the database contains accounts
	// if (head != 0) {
	// 	while (current != 0) {
	// 		int currentID = current->account->number;
	// 		cout << currentID << endl;

			
	// 		if (currentID == id) {
	// 			// TODO: use verify function to check if account holders name matches current account

	// 			temp = current;
	// 			prev->next = current->next;
	// 			cout << &temp << endl;
	// 			cout << &current << endl;
	// 			cout << &prev << endl;

	// 			cout << "DELETED" << endl;
	// 		}
	// 		else {
	// 			prev = current;
	// 		}

	// 		current = current->next;
	// 		delete temp;
	// 		cout << &temp << endl;
	// 		cout << &current << endl;
	// 	}
	// }
	// else {
	// 	cout << "No accounts available" << endl;
	// }
}

void Database::disable(int id, string name) {
	// Obtains specified account from database
	accountNode* foundAccount = findAccount(id, name);

	// Sets account to a disabled state
	foundAccount->account->isDisabled = true;
}

bool Database::changeplan(int id, string name) {
	// Obtains specified account from database
	accountNode* foundAccount = findAccount(id, name);

	// Toggles the status of the account between student and non-student
	foundAccount->account->isStudent = !foundAccount->account->isStudent;

	// Returns current state of account
	return foundAccount->account->isStudent;
}

bool Database::verify(int accountNumber, string accountName) {
	return true;
}

accountNode* Database::findAccount(int id, string name) {
	// Variable Declaration
	accountNode* current = head;

	// When the database contains accounts
	if (head != 0) {
		while (current != 0) {
			int currentID = current->account->number;
			
			if (currentID == id) {
				return current;
			}

			current = current->next;
		}
	}
	else {
		cout << "No accounts available" << endl;
	}

	return NULL;
}