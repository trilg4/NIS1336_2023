#include "task.h"

Task::Task(const string& name, const string& startTime, Priority priority = Priority::MEDIUM, Category category = Category::LIFE, const string& reminderTime = ""){
    m_name = name;
    m_startTime = startTime;
    m_priority = priority;
    m_category = category;
    m_reminderTime = reminderTime;
}

const string& Task::getName() const{
    return m_name;
}

const string& Task::getStartTime() const{
    return m_startTime;
}

Priority Task::getPriority() const{
    return m_priority;
}

Category Task::getCategory() const{
    return m_category;
}

const string& Task::getReminderTime() const{
    return m_reminderTime;
}

int Task::getId() const{
    return m_id;
}

void Task::setName(const string& name){
    m_name = name;
}

void Task::setStartTime(const string& startTime){
    m_startTime = startTime;
}

void Task::setPriority(Priority priority){
    m_priority = priority;
}

void Task::setCategory(Category category){
    m_category = category;
}

void Task::setReminderTime(const string& reminderTime){
    m_reminderTime = reminderTime;
}

void addTask(vector<Task>& tasks, const Task& task){
    tasks.push_back(task);
}

bool deleteTask(vector<Task>& tasks, int taskId){
    for(auto it = tasks.begin() ; it != tasks.end() ; it++){
        if((*it).getId() == taskId){
            tasks.erase(it);
            return true;
        }
    }
    return false;
}

vector<Task> loadTasksFromFile(const string& filename){
    ifstream infile(filename);
    if(!infile){
        cerr<<"ERROR opening file "<<filename<<std::endl;
        exit(-1);
    }
    int tmp_id;
    string tmp_name;
    string tmp_startTime;
    Priority tmp_priority;
    Category tmp_category;
    string tmp_reminderTime;
    while(infile >> tmp_id >> tmp_name >> tmp_startTime >> tmp_priority >> tmp_category >> tmp_reminderTime){
        T
    }

}