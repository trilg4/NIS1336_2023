#ifndef REMINDER_H
#define REMINDER_H

#include <vector>
#include <string>
#include <chrono>
#include "task.h"
using namespace std;

class Reminder {
public:
    Reminder(const vector<Task>& tasks);

    void start();

private:
    vector<Task> m_tasks;

    chrono::system_clock::time_point getCurrentTime() const;
};

#endif // REMINDER_H