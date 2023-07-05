
#include "../include/ui.h"
#include "account.h"
#include "task.h"
#include "reminder.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <fstream>
using namespace std;

extern void addTask(vector<Task>& tasks, const Task& task);
extern bool deleteTask(vector<Task>& tasks, int taskId);

string filename = "../data/tasks.json";
vector<Task> t_list;

void UI::run(){
    int userLoggedIn = 0;
    while (!userLoggedIn) {userLoggedIn = userLogin();}
    t_list = loadTasksFromFile(filename);
    bool flag = true;
    int userOption = 0;
    while(flag){
        string command;
        showHelp();
        cin >> command;
        if(strcasecmp(command.c_str(), "addTask") == 0) userOption = 1;
        else if(strcasecmp(command.c_str(), "deleteTask") == 0) userOption = 2;
        else if(strcasecmp(command.c_str(), "viewTask") == 0) userOption = 3;
        else if(strcasecmp(command.c_str(), "viewTaskByDate") == 0) userOption = 4;
        else if (strcasecmp(command.c_str(), "doTask") == 0) userOption = 5;
        else if (strcasecmp(command.c_str(), "undoTask") == 0) userOption = 6;
    }
}//TODO: write the main logic

int UI::login(){
    return userLogin();
}

void UI::logout(){
    //remain to be completed
}

void UI::showHelp(){
    cout << "Options:" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
}

void UI::showTasks(){
    printTasks(t_list);
}

void UI::ui_addTask(const string& name,const string& startTime, Priority priority , Category category , const string& reminderTime ){
    Task temp = Task(name, startTime, priority, category, reminderTime);
    //t_list.push_back(temp);
    addTask(t_list, temp);

}

void UI::ui_deleteTask(int taskId){
    bool flag = deleteTask(t_list, taskId);
    if(flag){
        cout << "Successfully deleted task " << taskId << ". " << endl;
        return;
    }
    if(!flag){
        cout << "Failed to delete task " << taskId << ". " << "Please check your input. " << endl;
        return;
    }
}

void UI::showTasksByDate(){

}

void UI::printReminder(const Task task){
    Reminder remind(t_list);
    //t_list.start();

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