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
		
		if(strcmp(in,"logout") == 0){
			mySes.logout();
		}
	
		if(strcmp(in,"withdrawal") == 0){
			mySes.withdrawal();
		}

		if(strcmp(in,"transfer") == 0){
			mySes.transfer();
		}
		
		if(strcmp(in,"deposit") == 0){
			mySes.deposit();
		}

		if(strcmp(in,"changeplan") == 0){
			mySes.changeplan();
		}

		if(strcmp(in,"delete") == 0){
			mySes.discard();
		}

		if(strcmp(in,"disable") == 0){
			mySes.disable();
		}

		if(strcmp(in,"create") == 0){
			mySes.create();
		}
	
	}

	return 0;
}