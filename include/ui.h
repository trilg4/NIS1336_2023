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
    void showMenu() const;
    void showTasks() const;
    void addTask();
    void deleteTask();
    void showTasksByDate() const;
    void printReminder(const Task& task) const;
};

#endif // UI_H