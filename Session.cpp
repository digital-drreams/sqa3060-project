#include <iostream>
#include <string>
#include "frontend.h"

using namespace std;

class Session {
    private:
        string username;
        bool isPrivileged;
        bool isActive = false;
        int transactionLogSize;
        std::string* transactionLog = new std::string[transactionLogSize];

    public:
        void login(){
            if (!isActive){
                string sessionType;
                string adminType = "admin";
                string standardType = "standard";
                cout << "Welcome to the banking system." << endl;
                cout << "Enter session type: ";
                cin >> sessionType;
                if (sessionType == adminType){
                    cout << "Session request successful." << endl;
                    isPrivileged = true;
                    isActive = true;
                } else if (sessionType == standardType){
                    cout << "Session request successful." << endl;
                    isPrivileged = false;
                    isActive = true;
                } else {
                    cout << "Invalid session type." << endl;
                }
            } else {
                cout << "Already logged in to a session" << endl;
            }
        }

        void logout(){
            if (isActive){
                isActive = false;
                cout << "Session terminated." << endl;
                for (int i = 0; i < transactionLogSize; i++){
                    cout << transactionLog[i];
                }
            } else {
                cout << "Error: Cannot logout outside of session." << endl;
            }
        }

        void withdrawal(){

        }

        void transfer(){

        }

        void deposit(){
            if (isPrivileged){
                string accountHolderName;
                int accountNumber;
                float depositValue;
                
                cout << "Enter Account holder Name: ";
                cin >> accountHolderName >> endl;
                cout << "Enter Account Identification number: ";
                cin >> accountNumber >> endl;
                if (!Database.verify(accountNumber, accountHolderName)){
                    cout << "Invalid Account Identification number." << endl;
                }

            }
        }

        void changeplan(){

        }

        void discard(){

        }

        void disable(){

        }

        void create(){
            if (isActive) { //Is there a user logged in?
                if (isPrivileged) { //Are they an admin?
                    string acc;
                    cout << "Enter account holder name: ";
                    cin >> acc;

                    if (acc.length() > 20) { //Is the name format valid?
                        cout << "Error: Account holder name must be 20 characters or less." << endl;
                    }
                    else {
                        float balance;
                        string buffer;
                        cout << "Enter initial balance: ";
                        cin >> buffer;
                        //WIP
                    }
                }
                else {
                    cout << "Permission denied." << endl;
                }
            }
            else {
                cout << "Error: Transaction not accepted outside of active session." << endl;
            }
        }
};
/*
int main() {
  Session x;

  x.login();
  x.logout();
  return 0;
}
*/
