#include <iostream>
#include <string>
#include <frontend.h>

using namespace std;

int main() {
	Session mySes;

	char* in;

	while (true){
		cin >> in;
		if(strcmp(in, "login") == 0){
			mySes.login();
		}
		
		else if(strcmp(in,"logout") == 0){
			mySes.logout();
		}
	
		else if(strcmp(in,"withdrawal") == 0){
			mySes.withdrawal();
		}

		else if(strcmp(in,"transfer") == 0){
			mySes.transfer();
		}
		
		else if(strcmp(in,"deposit") == 0){
			mySes.deposit();
		}

		else if(strcmp(in,"changeplan") == 0){
			mySes.changeplan();
		}

		else if(strcmp(in,"delete") == 0){
			mySes.discard();
		}

		else if(strcmp(in,"disable") == 0){
			mySes.disable();
		}

		else if(strcmp(in,"create") == 0){
			mySes.create();
		}
		else{
			cout << "Invalid input" << endl;
		}
	
	}

	return 0;
}