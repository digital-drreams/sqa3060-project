#include <iostream>
#include <string>
#include <frontend.h>

using namespace std;

int main() {
	Session mySes;

	string in;

	while (true){
		cin >> in;
		if(in == "login"){
			cout << "Pass" << endl
		}

		if(in == "login"){
			mySes.login();
		}
		
		else if(in == "logout"){
			mySes.logout();
		}
	
		else if(in == "withdrawal"){
			mySes.withdrawal();
		}

		else if(in == "transfer"){
			mySes.transfer();
		}
		
		else if(in == "deposit"){
			mySes.deposit();
		}

		else if(in == "changeplan"){
			mySes.changeplan();
		}

		else if(in == "delete"){
			mySes.discard();
		}

		else if(in == "disable"){
			mySes.disable();
		}

		else if(in == "create"){
			mySes.create();
		}
		else{
			cout << "Invalid input" << endl;
		}
		
	
	}

	return 0;
}