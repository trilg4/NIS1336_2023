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

    bool login();
    void logout();
    void showMenu();
    void showTasks();
    void addTask();
    void deleteTask();
    void showTasksByDate();
    void printReminder(const Task task);
};

#endif // UI_H