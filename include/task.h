#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
using namespace std;

enum class Priority { HIGH, MEDIUM, LOW };//TODO
enum class Category { LEARNING, LIFE, ENTERTAINMENT };//TODO

class Task {
public:
    Task(const string& name, const string& startTime, Priority priority = Priority::MEDIUM, Category category = Category::LIFE, const string& reminderTime = "");

    const string& getName() const;
    const string& getStartTime() const;
    Priority getPriority() const;
    Category getCategory() const;
    const string& getReminderTime() const;
    int getId() const;

    void setName(const string& name);
    void setStartTime(const string& startTime);
    void setPriority(Priority priority);
    void setCategory(Category category);
    void setReminderTime(const string& reminderTime);

private:
    static int s_nextId;
    int m_id;
    string m_name;
    string m_startTime;
    Priority m_priority;
    Category m_category;
    string m_reminderTime;
};

void addTask(vector<Task>& tasks, const Task& task);
bool deleteTask(vector<Task>& tasks, int taskId);
vector<Task> loadTasksFromFile(const string& filename);
bool saveTasksToFile(const vector<Task>& tasks, const string& filename);
vector<Task> getTasksByDate(const vector<Task>& tasks, const string& dateStr);
void printTasks(const vector<Task>& tasks);

#endif // TASK_H