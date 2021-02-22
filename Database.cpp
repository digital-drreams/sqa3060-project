#include <string>
#include <iostream>
//#include "Account.cpp"

using namespace std;

// struct accountNode
// {
// 	Account account;
// 	struct node* next;
//};

class Database {
	private:
		// accountNode* head, * tail;
		// Private Variable Declaration for account file location
		string fileLocation;

	public:
		Database(); // Constructor
		~Database(); // Deconstructor

		// Getter and Setter declaration for the account file location
		void setFileLocation(string location);
		string getFileLocation(void);

		// Method Declarations for Database Instance
		bool changeBalance(string accountHolder, int accountNumber, float amount);
		int create(string accountHolder, float initBalance);
		void discard();
		void disable();
		void changeplan();
		bool verify(int accountNumber, string accountName);
};

Database::Database() {
	//head = NULL;
	//tail = NULL;
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

	// if (tail != NULL) {
	//	cout << tail->number << endl;
	//	return 2;
	//}
	//else {
	//	Account account = new Account(1, accountHolder, initBalance);
	//	head = account;
	//	tail = account;

		// Returns the account number of the newly created account number
	//	return account.number;
	//}
}

void Database::discard() {
	//Account account = new Account(1, accountHolder, initBalance);
	//return account.number;
}

void Database::disable() {

}

void Database::changeplan() {

}

bool Database::verify(int accountNumber, string accountName) {
	return true;
}

/*int main() {
	Database obj;

	obj.changeBalance("Test Account 1", 100000000, 10.0);
	//obj.create("Test Account 1", 10.0);


	return 0;
}*/