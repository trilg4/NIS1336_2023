#ifndef REMINDER_H
#define REMINDER_H

#include <vector>
#include <string>
#include <chrono>
#include "task.h"
using namespace std;

class Reminder {
public:
    Reminder(const string& filename);
    void reminderbyId();
    void reminderbyDuetime();
    void scan();
    const string getCurrentTime() const;

private:
    vector<Task> Rem_tasks;
    bool compareTime(const string re_dueTime, const string re_currentTime);
    bool isFileLocked(const std::string& filename);
};

#endif // REMINDER_H