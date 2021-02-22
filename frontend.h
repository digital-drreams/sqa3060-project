#ifndef __frontend_h__
#define __frontend_h__

#include <iostream>

using namespace std;

class Session
{
private:
	bool isPrivileged;
	bool isActive;
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

class Database
{
private:
	string fileLocation;

public:
	Database();
	~Database();
	bool changeBalance(int id, string name);
	int create(string name, float initBalance);
	void discard(int id, string name);
	void disable(int id, string name);
	void changeplan(int id, string name);
	bool verify(int id, string name);
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

#endif