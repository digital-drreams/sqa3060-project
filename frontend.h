#ifndef __frontend_h__
#define __frontend_h__

#include <iostream>

using namespace std;

class Account;

struct accountNode
{
	Account* account;
	accountNode* next;
};

class Database
{
private:
	string fileLocation;
	Account* data;

public:
	Database();
	~Database();

	accountNode* head, * tail;
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

	// bool changeBalance(int id, string name);
	// int create(string name, float initBalance);
	// void discard(int id, string name);
	// void disable(int id, string name);
	// void changeplan(int id, string name);
	// bool verify(int id, string name);
}; 

class Account
{
	friend Database;

protected:
	int number;
	string holder;
	float balance;
	bool isDisabled;
	bool isStudent;

public:
	Account(int id, string name, float initBalance);
};

class Session
{
private:
	bool isPrivileged;
	bool isActive;
	Database* handler;
	string username;
	string* transactionLog;

public:
	bool login();
	bool logout();
	bool withdrawal();
	bool transfer();
	bool deposit();
	bool changeplan();
	bool discard();
	bool disable();
	bool create();
};

#endif