
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
    t_list = loadTasksFromFile(filename);
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
                cin>>tmp_id;
                filemutex.lock();
                ui_deleteTask(tmp_id);
                filemutex.unlock();
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
    cin>> tmp_name >> tmp_startTime >> tmp_Priority >> tmp_Category >> tmp_reminderTime;
    Task tmp(tmp_name, tmp_startTime, (Priority)tmp_Priority, (Category)tmp_Category, tmp_reminderTime);
    addTask(t_list, tmp);  
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
    cout<<"Please input the date in this form: MM/DD";
    cin>>dateStr;
    vector<Task> tmp = getTasksByDate(t_list, dateStr);
    printTasks(tmp);

}

void UI::undoTask(){
    cout<<"Please input the task id: "<<endl;
    int id;
    cin>>id;
    for(auto it = t_list.begin() ; it < t_list.end() ; it++){
        if((*it).getId() == id){
            (*it).setReminded(false);
        }
    }

    saveTasksToFile(t_list,filename);
}

void UI::doTask(){
    cout<<"Please input the task id: "<<endl;
    int id;
    cin>>id;
    for(auto it = t_list.begin() ; it < t_list.end() ; it++){
        if((*it).getId() == id){
            (*it).setReminded(true);
        }
    }
    saveTasksToFile(t_list,filename);
}

bool ui_isFileLocked(const std::string& filePath){
    int fd = open(filePath.c_str(), O_RDWR);
    if (fd == -1) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }

    // Attempt to acquire a non-blocking exclusive write lock
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
            // The file is already locked
            close(fd);
            return true;
        } else {
            // An error occurred while acquiring the lock
            std::cerr << "Failed to acquire the lock." << std::endl;
            close(fd);
            return false;
        }
    }

    // Release the lock
    if (flock(fd, LOCK_UN) == -1) {
        std::cerr << "Failed to release the lock." << std::endl;
    }

    close(fd);
    return false;
}
