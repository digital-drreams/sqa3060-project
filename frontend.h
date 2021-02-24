#ifndef __frontend_h__
#define __frontend_h__

#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>

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
	// Database Constructor
	Database();
	// Database Deconstructor
	~Database();

	// References first and last accounts stored in the database
	accountNode* head, * tail;

	// Method Declarations for Database Instance
	bool changeBalance(int id, string name, float amount);
	int create(string name, float initBalance);
	bool discard(int id, string name);
	void disable(int id, string name);
	bool changeplan(int id, string name);
	bool verify(int id, string name);
	bool isDisabled(int id, string name);

	// Helper function to find an account
	accountNode* findAccount(int id, string name);
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
	bool isActive = false;
	Database* handler;
	string username;
	vector<string> transactionLog;
	float withdrawLimit;
	float transferLimit;
	float ECLimit;
	float CQLimit;
	float FILimit;

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
	bool paybill();
};

#endif