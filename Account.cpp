#include "frontend.h"

using namespace std;

Account::Account(int id, string name, float initBalance) {
	number = id;
	balance = initBalance;
	holder = name;
}