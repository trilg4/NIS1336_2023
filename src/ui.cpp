#include "ui.h"
#include "account.h"
#include "task.h"
#include "reminder.h"
#include <iostream>
using namespace std;

string filename;
vector<Task> t_list;

void UI::run(){
    while (!userLoggedIn) userLogin();
    cout << "Please enter filename of task storage:" << endl;
    cin >> filename;
    t_list = loadTasksFromFile(filename);
}

bool UI::login(){
    return userLogin();
}

void UI::logout(){
    userLogout();
}

void UI::showMenu(){

}

void UI::showTasks(){

}

void UI::addTask(){

}

void UI::deleteTask(){


}

void UI::showTasksByDate(){

}

void UI::printReminder(const Task task){
    Reminder remind(t_list);
    //t_list.start();

}