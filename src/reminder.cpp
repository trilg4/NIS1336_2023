#include "../include/reminder.h"
#include <thread>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <cerrno>
#include <mutex>

extern std::mutex filemutex;
extern vector<Task> t_list;

Reminder::Reminder(const string& filename){
    Rem_Tasks = loadTasksFromFile(filename);
    re_filename = filename;
};
//define a reminder object with a filename
Reminder::Reminder(const vector<Task>& tlist){
    Rem_Tasks = tlist;
    re_filename = "";
}


void Reminder::reminderbyDuetime(){
    sort_by_reminderTime(Rem_Tasks);
    int numberofRem_Tasks = Rem_Tasks.size();
    for(int i =0;i<numberofRem_Tasks;i++){
        std::cout<<Rem_Tasks[i].getId()<<" "<<Rem_Tasks[i].getName()<<" "<<Rem_Tasks[i].getReminderTime()<<std::endl;
    }
}    
    
void Reminder::reminderbyId(){
    sort_by_id(Rem_Tasks);
    int numberofRem_Tasks = Rem_Tasks.size();
    for(int i = 0;i<numberofRem_Tasks;i++){
        std::cout<<Rem_Tasks[i].getId()<<" "<<Rem_Tasks[i].getName()<<std::endl;
    }
}



void Reminder::scan(){ //may check every 15 minutes
    
 
 while(true){
    this_thread::sleep_for(std::chrono::seconds(1));
    filemutex.lock();
    Rem_Tasks = t_list;
    int numberofTasks = Rem_Tasks.size();
    for(int i=0;i<numberofTasks;i++){
        if(compareTime(Rem_Tasks[i].getReminderTime(),getCurrentTime())&&!Rem_Tasks[i].isReminded())
        {
            std::cout<<Rem_Tasks[i].getId()<<" "<<Rem_Tasks[i].getName()<<" "<<Rem_Tasks[i].getReminderTime()<<std::endl;
            Rem_Tasks[i].setReminded(true);
        }
    }
    t_list = Rem_Tasks;
    filemutex.unlock();
    
 }  

};



const string Reminder::getCurrentTime() const{
    // Get the current system time
    std::time_t currentTime = std::time(nullptr);

    // Convert the system time to local time
    std::tm* localTime = std::localtime(&currentTime);

    // Format the time as MM/DD/hh/mm
    char formattedTime[20];
    std::strftime(formattedTime, sizeof(formattedTime), "%m/%d/%H/%M", localTime);

    // Print the formatted time
    return formattedTime; 
};


bool Reminder::compareTime(const string re_dueTime, const string re_currentTime){
    if(re_dueTime >= re_currentTime) {
        return false;// the task is not overdue
    }
    else 
    {return true;} //the task is overdue
}

bool Reminder::isFileLocked(const std::string& filePath) {
    int fd = open(filePath.c_str(), O_RDWR);
    if (fd == -1) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }

    // Attempt to acquire a non-blocking exclusive write lock
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
            // The file is already locked
            close(fd);
            return true;
        } else {
            // An error occurred while acquiring the lock
            std::cerr << "Failed to acquire the lock." << std::endl;
            close(fd);
            return false;
        }
    }

    // Release the lock
    if (flock(fd, LOCK_UN) == -1) {
        std::cerr << "Failed to release the lock." << std::endl;
    }

    close(fd);
    return false;
}