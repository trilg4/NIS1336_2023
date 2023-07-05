#include <iostream>
#include <string>
#include <cstring>
#include "account.h"
#include "task.h"
#include "reminder.h"
#include "ui.h"
using namespace std;

extern int userLogin(string username, string password);

int main(int argc, char* argv[]) {
    if(argc == 1){
    UI ui;
    ui.run();
    return 0;
    }
    else if(argc >= 2){
        string username, passwd, operation;
        cin >> username >> passwd;
        int curUser = userLogin(username, passwd);//TODO: Define another userLogin()
        if(curUser == -1){
            cout << "Incorrect credentials. Check your input." << endl;
            exit(401);
        }
        else{
            int userOption = 0;
            cin >> operation;
            if(strcasecmp(operation.c_str(), "addTask") == 0) userOption = 1;
            else if(strcasecmp(operation.c_str(), "deleteTask") == 0) userOption = 2;
            else if(strcasecmp(operation.c_str(), "viewTask") == 0) userOption = 3;
            else if(strcasecmp(operation.c_str(), "viewTaskByDate") == 0) userOption = 4;
            else if (strcasecmp(operation.c_str(), "doTask") == 0) userOption = 5;
            else if (strcasecmp(operation.c_str(), "undoTask") == 0) userOption = 6;
            switch(userOption){
                case 0: cout << "Command unknown. Plese check your input." << endl; exit(404); break;
                case 1: {
                    
                }
            }
        }
    }
}