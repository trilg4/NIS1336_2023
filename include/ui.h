#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include "task.h"
#include <mutex>

extern std::mutex filemutex;
using namespace std;

class UI {
public:
    void run();
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
bool ui_isFileLocked(const std::string& filePath);
#endif // UI_H