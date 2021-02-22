#include <iostream>
#include <string> 

class Session {
    private:
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

        }
        
};