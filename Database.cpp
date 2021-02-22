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

bool Database::changeBalance(string accountHolder, int accountNumber, float amount) {
	cout << "Changing Balance" << endl;

	return true;
}

int Database::create(string accountHolder, float initBalance) {
	// Creates a new instance of the account class using the
	// provided account holder name and initial balance

	if (tail != NULL) {
		//cout << tail->number << endl;
		return 2;
	}
	else {
		// accountNode *tmp = new accountNode;
		// Account *account = new Account(1, "Test Name", 100.0);
		// tmp->account = account;
		// accountNode->next = NULL;
		
		// head = tmp;
		// tail = tmp;

		// Returns the account number of the newly created account number
		return 1;
	}
}

void Database::discard() {
}

void Database::disable() {

}

void Database::changeplan() {

}

bool Database::verify(int accountNumber, string accountName) {
	return true;
}

int main() {
	Database obj;

	obj.changeBalance("Test Account 1", 100000000, 10.0);
	obj.create("Test Account 1", 10.0);


	return 0;
}