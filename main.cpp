#include <iostream>
#include <string>
#include <cstring>
#include "./include/account.h"
#include "./include/task.h"
#include "./include/reminder.h"
#include "./include/ui.h"

std::mutex filemutex;
vector<Task> t_list;

using namespace std;

extern int userLogin(string username, string password);
extern bool isValidTime(const string& timeString);
extern bool isValidDate(const string& dateString);
extern bool main_doTask(vector<Task> t_list, int taskId, string filename);
extern bool main_undoTask(vector<Task> t_list, int taskId, string filename);

int main(int argc, char* argv[]) {
    if(argc == 1){
    UI ui;
    ui.run();
    return 0;
    }
    else if(argc >= 2){
        string username, passwd, operation;
        username = argv[1];
        passwd = argv[2];
        passwd = toEncrypt(passwd);
        int curUser = userLogin(username, passwd);//TODO: Define another userLogin()
        if(curUser == -1){
            cout << "Incorrect credentials. Check your input." << endl;
            exit(401);
        }
        else{
            string filename = to_string(curUser) + ".txt";
            int userOption = 0;
            operation = argv[3];
            if(strcasecmp(operation.c_str(), "addTask") == 0) userOption = 1;
            else if(strcasecmp(operation.c_str(), "deleteTask") == 0) userOption = 2;
            else if(strcasecmp(operation.c_str(), "viewTask") == 0) userOption = 3;
            else if(strcasecmp(operation.c_str(), "viewTaskByDate") == 0) userOption = 4;
            else if (strcasecmp(operation.c_str(), "doTask") == 0) userOption = 5;
            else if (strcasecmp(operation.c_str(), "undoTask") == 0) userOption = 6;
            switch(userOption){
                case 0: {cout << "Command unknown. Plese check your input." << endl; exit(404); break;}
                case 1: {
                    string name, startTime, pri, cate, remindTime;
                    name = argv[4];
                    startTime = argv[5];
                    pri = argv[6];
                    cate = argv[7];
                    remindTime = argv[8];
                    if (!isValidTime(startTime) || !isValidTime(remindTime)){
                        cout << "Incorrect time format. The time format should be MM/DD/hh/mm."; exit(406); break;
                    }
                    Priority pr;
                    if(strcasecmp(pri.c_str(), "HIGH") == 0) pr = Priority::HIGH;
                    if(strcasecmp(pri.c_str(), "MEDIUM") == 0) pr = Priority::MEDIUM;
                    if(strcasecmp(pri.c_str(), "LOW") == 0) pr = Priority::LOW;
                    if(!(pr == Priority::HIGH || pr == Priority::MEDIUM || pr == Priority::LOW)){cout << "Incorrect priority syntax. " << endl; exit(406); break;}
                    Category cat;
                    if(strcasecmp(cate.c_str(), "LIFE") == 0) cat = Category::LIFE;
                    if(strcasecmp(cate.c_str(), "ENTERTAINMENT") == 0) cat = Category::ENTERTAINMENT;
                    if(strcasecmp(cate.c_str(), "LEARNING") == 0) cat = Category::LEARNING;
                    if(!(cat == Category::ENTERTAINMENT || cat == Category::LEARNING || cat == Category::LIFE)){cout << "Incorrect category syntax. " << endl; exit(406); break;}
                    //TODO: lock the database file
                    //cout<<"adsf"<<endl;
                    t_list = loadTasksFromFile(filename);
                    int cmd_next_id = 1;
                    if(t_list.empty()){
                        cmd_next_id = 1;
                    }
                    else{
                        cmd_next_id = (*(t_list.end()-1)).getId() + 1;
                    }
                    
                    Task temp = Task(cmd_next_id, name, startTime, pr, cat, remindTime);
                    //cout<<"adsf"<<endl;
                    addTask(t_list, temp);
                    saveTasksToFile(t_list, filename);
                    //TODO: unlock the database file
                    break;
                }
                case 2:{
                    int taskId;
                    cin >> taskId;
                    //TODO: lock the database file
                    vector<Task> t_list = loadTasksFromFile(filename);
                    bool status = deleteTask(t_list, taskId);
                    //TODO: unlock the database file
                    if(status) {cout << "Task " << taskId << " deleted successfully." << endl;}
                    else {cout << "Failed to delete task " << taskId << ". " << endl; exit(404);}
                    break;
                }
                case 3:{
                    //TODO: lock the database file
                    t_list = loadTasksFromFile(filename);
                    printTasks(t_list);
                    //TODO: unlock the database file
                    break;
                }
                case 4:{
                    string date;
                    cin >> date;
                    if(!isValidDate(date)){cout << "Incorrect date format. The date format should be MM/DD."; exit(406); break;}
                    //TODO: lock the database file
                    vector<Task> t_list = loadTasksFromFile(filename);
                    vector<Task> t_list_date = getTasksByDate(t_list, date);
                    printTasks(t_list_date);
                    if (t_list_date.empty()) cout << "No tasks for " << date << ". " << endl;
                    break;
                }
                case 5:{
                    int taskId;
                    cin >> taskId;
                    //TODO: add error handling
                    //TODO: lock the database file
                    vector<Task> t_list = loadTasksFromFile(filename);
                    bool flag = main_doTask(t_list, taskId, filename);
                    //TODO: unlock the database file
                    if(flag) {cout << "Successfully set task " << taskId << " as done. " << endl;}
                    else {cout << "Failed to set task " << taskId << "as done. Please check your input. "; exit(404);}
                    break;
                }
                case 6:{
                    int taskId;
                    cin >> taskId;
                    //TODO: add error handling
                    //TODO: lock the database file
                    t_list = loadTasksFromFile(filename);
                    bool flag = main_undoTask(t_list, taskId, filename);
                    //TODO: unlock the database file
                    if(flag) {cout << "Successfully set task " << taskId << " as undone. " << endl;}
                    else {cout << "Failed to set task " << taskId << "as undone. Please check your input. "; exit(404);}
                    break;
                }
                default:{{cout << "An error occurred. Plese check your input." << endl; exit(404); break;}}
            }
        }
    exit(0);
    }
}