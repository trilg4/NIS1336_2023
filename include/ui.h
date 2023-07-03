#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include "task.h"
using namespace std;

class UI {
public:
    void run();

private:
    string m_username;
    vector<Task> m_tasks;

    int login();
    void logout();
    void showHelp();
    void showTasks();
    void ui_addTask(const string& name,const string& startTime, Priority priority = Priority::MEDIUM, Category category = Category::LIFE, const string& reminderTime = "");
    void ui_deleteTask(int taskId);
    void showTasksByDate();
    void printReminder(const Task task);
};

#endif // UI_H