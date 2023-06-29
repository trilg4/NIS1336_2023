#include "task.h"
using namespace std;
int Task::s_nextId = 1;

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
    vector<Task> t_list;
    ifstream infile(filename);
    if(!infile){
        cerr<<"ERROR opening file "<<filename<<std::endl;
        exit(-1);
    }
    int tmp_id;
    string tmp_Name;
    string tmp_startTime;
    int tmp_priority;
    int tmp_category;
    string tmp_reminderTime;
    
    while(infile >> tmp_id >> tmp_Name >> tmp_startTime >> tmp_priority >> tmp_category >> tmp_reminderTime){
        Task tmp(tmp_id, tmp_Name, tmp_startTime, (Priority)tmp_priority, (Category)tmp_category, tmp_reminderTime);
        t_list.push_back(tmp);
    }
    return t_list;
}

bool saveTasksToFile(const vector<Task>& tasks, const string& filename){
    ofstream outputFile(filename);
    if(outputFile.is_open()){
        for(const auto& tmp : tasks){
            outputFile
            << tmp.getId() << " "
            << tmp.getName() << " "
            << tmp.getStartTime() << " "
            << (int)tmp.getPriority() << " "
            << (int)tmp.getCategory() << " "
            << tmp.getReminderTime() << " ";
        }
        outputFile.close();
        return true;
    }
    return false;
}


void printTasks(const vector<Task>& tasks){
    for(auto it = tasks.begin() ; it < tasks.end() ; it++){
        cout<<setw(5) << (*it).getId()
            <<setw(10) << (*it).getName()
            <<setw(15) << (*it).getStartTime()
            <<setw(3) << (int)(*it).getPriority()
            <<setw(3) << (int)(*it).getCategory()
            <<setw(15) << (*it).getReminderTime()
            <<endl;
    }
}