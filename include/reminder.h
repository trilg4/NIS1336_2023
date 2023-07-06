#ifndef REMINDER_H
#define REMINDER_H

#include <vector>
#include <string>
#include <chrono>
#include "task.h"
#include <mutex>

using namespace std;

extern std::mutex filemutex;
class Reminder {
public:
    Reminder(const string& filename);
    Reminder(const vector<Task>& tlist);
    void start();
    void reminderbyId();
    void reminderbyDuetime();
    void scan();
    const string getCurrentTime() const;
    
private:
    vector<Task> Rem_Tasks;
    bool compareTime(const string re_dueTime, const string re_currentTime);
    bool isFileLocked(const std::string& filePath);
    string re_filename;
};

#endif // REMINDER_H