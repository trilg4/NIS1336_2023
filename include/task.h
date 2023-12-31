#ifndef TASK_H
#define TASK_H
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
using namespace std;
/*-----------------------------*/
//在使用vector时必须先进行load的操作
enum class Priority { HIGH, MEDIUM, LOW };//TODO
enum class Category { LEARNING, LIFE, ENTERTAINMENT };//TODO

class Task {
public:
    //从文件读取Task直接复制原有的id
    Task(int id = -1, const string& name = "", const string& startTime = "" , Priority priority = Priority::MEDIUM, Category category = Category::LIFE, const string& reminderTime = "", bool reminded = false){
        m_id = id;
        m_name = name;
        m_startTime = startTime;
        m_priority = priority;
        m_category = category;
        m_reminderTime = reminderTime;
        m_reminded = reminded;
    }
    //创建Task生成新的id
    Task(const string& name = "",const string& startTime = "", Priority priority = Priority::MEDIUM, Category category = Category::LIFE, const string& reminderTime = "", bool reminded = false){
        m_id = s_nextId;
        s_nextId++;
        m_name = name;
        m_startTime = startTime;
        m_priority = priority;
        m_category = category;
        m_reminderTime = reminderTime;
        m_reminded = reminded;
    }
    const string& getName() const;
    const string& getStartTime() const;
    Priority getPriority() const;
    Category getCategory() const;
    const string& getReminderTime() const;
    int getId() const;
    bool isReminded () const;
    //更改task成员变量
    void setName(const string& name);
    void setStartTime(const string& startTime);
    void setPriority(Priority priority);
    void setCategory(Category category);
    void setReminderTime(const string& reminderTime);
    void setReminded(bool reminded);
    friend void setNextId(const int next_id);
private:
    static int s_nextId;
    int m_id;
    string m_name;
    string m_startTime;
    Priority m_priority;
    Category m_category;
    string m_reminderTime;

    bool m_reminded;
    //时间格式：06/30/07/59 MM/DD/HH/mm M:month m:minute //transform the date to the exact number of days, transform the hours and minutes to the exact 

    //文件格式：id name startTime priority category reminderTime
};

void addTask(vector<Task>& tasks, const Task& task);
bool deleteTask(vector<Task>& tasks, int taskId);
vector<Task> loadTasksFromFile(const string& filename); //保存，但会将数据由id排序
bool saveTasksToFile(const vector<Task>& tasks, const string& filename);
vector<Task> getTasksByDate(const vector<Task>& tasks, const string& dateStr); //获取某一天的所有任务
void printTasks(const vector<Task>& tasks); //打印所有任务信息
void sort_by_id(vector<Task>& tasks); //任务列表按id升序
void sort_by_reminderTime(vector<Task>& tasks); //任务列表按提醒时间升序
void setNextId(const int next_id);
bool lockFile(int fileDescriptor);
void unlockFile(int fileDescriptor);
#endif // TASK_H