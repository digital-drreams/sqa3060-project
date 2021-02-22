#include <iostream>
#include <string>
#include "frontend.h"

class Session {
    private:
        string username;
        bool isPrivileged;
        bool isActive = false;
        int transactionLogSize;
        std::string* transactionLog = new std::string[transactionLogSize];

    public:
        void login(){

        }

        void logout(){

        }

        void withdrawal(){

        }

        void transfer(){

        }

        void deposit(){

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