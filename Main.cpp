#include <iostream>
#include <string>
#include <frontend.h>

using namespace std;

int main() {
	//Creates the session
	Session mySes;

	string in;

	//Loops for the time the atm would be active for
	while (true){
		//User enters the input for their 
		cin >> in;

		//Passes through user input: login
		if(in == "login"){
			mySes.login();
		}
		
		//Passes through user input: logout
		else if(in == "logout"){
			mySes.logout();
		}

		//Passes through user input: withdrawal
		else if(in == "withdrawal"){
			mySes.withdrawal();
		}

		//Passes through user input: transfer
		else if(in == "transfer"){
			mySes.transfer();
		}
		
		//Passes through user input: deposit
		else if(in == "deposit"){
			mySes.deposit();
		}

		//Passes through user input: changeplan
		else if(in == "changeplan"){
			mySes.changeplan();
		}

		//Passes through user input: delete
		else if(in == "delete"){
			mySes.discard();
		}

		//Passes through user input: disable
		else if(in == "disable"){
			mySes.disable();
		}

		//Passes through user input: changeplan
		else if(in == "create"){
			mySes.create();
		}

		//Outputs for an invalid input,
		else{
			cout << "Invalid input" << endl;
		}
		
	
	}

	return 0;
}