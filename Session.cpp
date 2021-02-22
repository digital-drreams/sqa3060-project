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
                } else {

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

        }
};

int main() {
  Session x;

  x.login();
  x.logout();
  return 0;
}