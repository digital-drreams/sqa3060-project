#include <iostream>
#include <string>
using namespace std;
class Session {
    private:
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
                while (!isActive){
                    cout << "Enter session type: ";
                    cin >> sessionType;
                    if (sessionType == adminType){
                        isPrivileged = true;
                        cout << "Session request successful." << endl;
                        isActive = true;
                    } else if (sessionType == standardType){
                        isPrivileged = false;
                        cout << "Session request successful." << endl;
                        isActive = true;
                    } else {
                        cout << "Invalid session type." << endl;
                    }
                }
            } else {
                cout << "Already logged in to a session" << endl;
            }
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

        }
};
