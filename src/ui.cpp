
#include "../include/ui.h"
#include "../include/account.h"
#include "../include/task.h"
#include "../include/reminder.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <thread>
#include <sys/file.h>
#include <cerrno>
#include <mutex>
using namespace std;

extern std::mutex filemutex;
extern vector<Task> t_list;

void UI::run(){
    int userLoggedIn = userLogin();
    filename  = to_string(userLoggedIn) + ".txt" ;
    filemutex.lock();
    t_list = loadTasksFromFile(filename);
    filemutex.unlock();
    bool flag = true;
    int userOption = 0;
    Reminder reminder(filename);
    thread check(&Reminder::scan, &reminder);
    check.detach();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    while(flag){
        string command;
        showHelp();
        cin >> command;
        if(strcasecmp(command.c_str(), "addTask") == 0) userOption = 1;
        else if(strcasecmp(command.c_str(), "deleteTask") == 0) userOption = 2;
        else if(strcasecmp(command.c_str(), "viewTask") == 0) userOption = 3;
        else if(strcasecmp(command.c_str(), "viewTaskByDate") == 0) userOption = 4;
        else if(strcasecmp(command.c_str(), "doTask") == 0) userOption = 5;
        else if(strcasecmp(command.c_str(), "undoTask") == 0) userOption = 6;
        else if(strcasecmp(command.c_str(), "logOut") == 0) userOption = 7;
        switch(userOption){
            case 1:{
                ui_addTask();
                break;
            }
            case 2:{
                int tmp_id;
                cout<<"Please input the task id: "<<endl;
                cout<<endl;
                cin>>tmp_id;
                cout<<endl;
                ui_deleteTask(tmp_id);
                break;
            }
            case 3:{
                showTasks();
                break;
            }
            case 4:{
                showTasksByDate();
                break;
            }
            case 5:{
                doTask();
                break;
            }
            case 6:{
                undoTask();
                break;
            }
            case 7:{
                //check.join();
                saveTasksToFile(t_list,filename);
                return;
            }
        }
    }
}//TODO: write the main logic

int UI::login(){
    return userLogin();
}

void UI::showHelp(){
    cout << "Options:" << endl;
    cout << "addTask " << "deleteTask "
         << "viewTask " << "viewTaskByDate "
         << "undoTask " << "doTask " << "logOut" <<endl;
}

void UI::showTasks(){
    printTasks(t_list);
}

void UI::ui_addTask(){
    cout<<"please input task in this format: "<<endl;
    cout<<"name startTime priority category reminderTime"<<endl;
    cout<<"NOTE: \nTime Format: MM/DD/HH/mm M:month m:minute"<<endl;
    cout<<"Priority: 0-HIGH 1-MEDIUM 2-LOW"<<endl;
    cout<<"Categoty: 0-LEARNING 1-LIFE 2-ENTERTAINMENT"<<endl;
    string tmp_name;
    string tmp_startTime;
    int tmp_Priority;
    int tmp_Category;
    string tmp_reminderTime;
    cout<<endl;
    while(true){
        cin>> tmp_name >> tmp_startTime >> tmp_Priority >> tmp_Category >> tmp_reminderTime;
        if(isValidTime(tmp_startTime) && isValidTime(tmp_reminderTime) && isValidPriority(tmp_Priority) && isValidCategory(tmp_Category)){
            break;
        }
        else{
            cout<<"Format err. Please check your input."<<endl;
        }
    }
    cout<<endl;
    Task tmp(tmp_name, tmp_startTime, (Priority)tmp_Priority, (Category)tmp_Category, tmp_reminderTime);
    addTask(t_list, tmp);  
    saveTasksToFile(t_list, filename);
}

void UI::ui_deleteTask(int taskId){
    bool flag = deleteTask(t_list, taskId);
    if(flag){
        cout << "Successfully deleted task " << taskId << ". " << endl;
        saveTasksToFile(t_list, filename);
        return;
    }
    if(!flag){
        cout << "Failed to delete task " << taskId << ". " << "Please check your input. " << endl;
        return;
    }
}

void UI::showTasksByDate(){
    //doesn't chance the structure of the task file
    string dateStr;
    cout<<"Please input the date in this form: MM/DD"<<endl;
    cout<<endl;
    while(true){
        cin>>dateStr;
        if(isValidDate(dateStr)){
            break;
        }
        else{
            cout<<"Format err. Please check your input."<<endl;
        }
    }
    
    cout<<endl;
    vector<Task> tmp = getTasksByDate(t_list, dateStr);
    printTasks(tmp);

}

void UI::undoTask(){
    cout<<"Please input the task id: "<<endl;
    int id;
    cout<<endl;
    cin>>id;
    cout<<endl;
    filemutex.lock();
    for(auto it = t_list.begin() ; it < t_list.end() ; it++){
        if((*it).getId() == id){
            (*it).setReminded(false);
        }
    }
    filemutex.unlock();
    saveTasksToFile(t_list,filename);
}

void UI::doTask(){
    cout<<"Please input the task id: "<<endl;
    int id;
    cout<<endl;
    cin>>id;
    cout<<endl;
    filemutex.lock();
    for(auto it = t_list.begin() ; it < t_list.end() ; it++){
        if((*it).getId() == id){
            (*it).setReminded(true);
        }
    }
    filemutex.unlock();
    saveTasksToFile(t_list,filename);
}

bool isValidTime(const string& timeString){
    tm timeStruct = {};
    istringstream iss(timeString);

    // Set the input format as MM/DD/hh/mm
    iss >> get_time(&timeStruct, "%m/%d/%H/%M");

    // Check if the parsing was successful and the entire string was consumed
    return !iss.fail() && iss.eof();
}

bool isValidDate(const string& dateString){
    tm timeStruct = {};
    istringstream iss(dateString);

    // Set the input format as MM/DD/hh/mm
    iss >> get_time(&timeStruct, "%m/%d");

    // Check if the parsing was successful and the entire string was consumed
    return !iss.fail() && iss.eof();
}

bool main_doTask(vector<Task>& t_list, int taskId, string filename){
    bool flag = false;
    for(auto it = t_list.begin() ; it < t_list.end() ; it++){
        if((*it).getId() == taskId){
            (*it).setReminded(true);
            flag = true;
            break;
        }
    }
    saveTasksToFile(t_list,filename);
    return flag;
}

bool main_undoTask(vector<Task>& t_list, int taskId, string filename){
    bool flag = false;
    for(auto it = t_list.begin() ; it < t_list.end() ; it++){
        if((*it).getId() == taskId){
            (*it).setReminded(false);
            flag = true;
            break;
        }
    }
    saveTasksToFile(t_list,filename);
    return flag;
}

bool isValidPriority(int priority){
    if(priority >= 0 && priority <=2){
        return true;
    }
    else{
        return false;
    }
}

bool isValidCategory(int category){
    if(category >= 0 && category <=2){
        return true;
    }
    else{
        return false;
    }
}
