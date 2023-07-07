#include "../include/task.h"
#include <mutex>
using namespace std;
int Task::s_nextId = 1;

extern std::mutex filemutex;

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

bool Task::isReminded() const{
    return m_reminded;
}

void Task::setReminded(bool reminded){
    m_reminded = reminded;
}

void addTask(vector<Task>& tasks, const Task& task){
    //TODO: add a check to ensure task name and startTime is unique
    filemutex.lock();
    tasks.push_back(task);
    filemutex.unlock();
}

bool deleteTask(vector<Task>& tasks, int taskId){
    filemutex.lock();
    for(auto it = tasks.begin() ; it != tasks.end() ; it++){
        if((*it).getId() == taskId){
            tasks.erase(it);
            filemutex.unlock();
            return true;
        }
    }
    filemutex.unlock();
    return false;
}

vector<Task> loadTasksFromFile(const string& filename){
    vector<Task> t_list;
    ifstream infile("../data/" + filename);
    if(!infile){
        //ofstream outputfile("../data/"+filename);
        vector<Task> new_list;
        return new_list;
    }
    int tmp_id;
    string tmp_Name;
    string tmp_startTime;
    int tmp_priority;
    int tmp_category;
    string tmp_reminderTime;
    bool tmp_reminded;
    while(infile >> tmp_id >> tmp_Name >> tmp_startTime >> tmp_priority >> tmp_category >> tmp_reminderTime >> tmp_reminded){
        Task tmp(tmp_id, tmp_Name, tmp_startTime, (Priority)tmp_priority, (Category)tmp_category, tmp_reminderTime);
        t_list.push_back(tmp);
    }
    if(t_list.empty()){
        vector<Task> new_list;
        return new_list;
    }
    sort_by_id(t_list);
    setNextId((*(t_list.end()-1)).getId()+1);
    //unlockFile(fileDescriptor);
    //close(fileDescriptor);
    
    return t_list;
}

bool saveTasksToFile(const vector<Task>& tasks, const string& filename){
    ofstream outputFile;
    outputFile.open("../data/"+filename);
    if(outputFile.is_open()){
        for(const auto& tmp : tasks){
            outputFile
            << tmp.getId() << " "
            << tmp.getName() << " "
            << tmp.getStartTime() << " "
            << (int)tmp.getPriority() << " "
            << (int)tmp.getCategory() << " "
            << tmp.getReminderTime() << " " 
            << tmp.isReminded() << " " <<endl;
        }
        outputFile.close();
        return true;
    }
    return false;
}


void printTasks(const vector<Task>& tasks){
    cout<<setw(5)<<"Id"
        <<setw(10)<<"Name"
        <<setw(20)<<"Start Time"
        <<setw(10)<<"Priority"
        <<setw(10)<<"Category"
        <<setw(20)<<"Reminder Time"
        <<setw(10)<<"Reminded"
        <<endl;
    for(auto it = tasks.begin() ; it < tasks.end() ; it++){
        cout<<setw(5) << (*it).getId()
            <<setw(10) << (*it).getName()
            <<setw(20) << (*it).getStartTime()
            <<setw(10) << (int)(*it).getPriority()
            <<setw(10) << (int)(*it).getCategory()
            <<setw(20) << (*it).getReminderTime()
            <<setw(10) << (*it).isReminded()
            <<endl;
    }
}

vector<Task> getTasksByDate(const vector<Task>& tasks, const string& dateStr){
    vector<Task> tmp;
    for(auto it = tasks.begin() ; it < tasks.end() ; it++){
        string tmp_string = (*it).getReminderTime();
        string tmp_date_string = tmp_string.substr(0,5);
        if(tmp_date_string == dateStr){
            tmp.push_back((*it));
        }
    }
    return tmp;
}

//id compare函数
bool id_compare(Task a, Task b){
    return a.getId() < b.getId();
}
//按id从小到大排序
void sort_by_id(vector<Task>& tasks){
    sort(tasks.begin(), tasks.end(), id_compare);
}

//time compare函数
bool time_compare(Task a, Task b){
    return a.getReminderTime() < b.getReminderTime();
}
//按提醒时间从小到大排序
void sort_by_reminderTime(vector<Task>& tasks){
    sort(tasks.begin(), tasks.end(), time_compare);
}

void setNextId(const int next_id){
    Task::s_nextId = next_id;
}

bool lockFile(int fileDescriptor) {
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0; // Lock the entire file
    return fcntl(fileDescriptor, F_SETLK, &fl) != -1;
}

void unlockFile(int fileDescriptor) {
    struct flock fl;
    fl.l_type = F_UNLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0; // Unlock the entire file
    fcntl(fileDescriptor, F_SETLK, &fl);
}