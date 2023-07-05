#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include "task.h"
using namespace std;

class UI {
public:
    void run();
    vector<Task> t_list;
    string filename;

private:
    int login();
    void showHelp();
    void showTasks();
    void ui_addTask();
    void ui_deleteTask(int taskId);
    void showTasksByDate();
    void undoTask();
    void doTask();
};

#endif // UI_H